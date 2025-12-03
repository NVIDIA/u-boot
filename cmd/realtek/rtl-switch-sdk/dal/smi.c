/*
* Copyright c                  Realtek Semiconductor Corporation, 2006
* All rights reserved.
*
* Program : Control smi connected RTL8366
* Abstract :
* Author : Yu-Mei Pan (ympan@realtek.com.cn)
*  $Id: smi.c,v 1.2 2008-04-10 03:04:19 shiehyy Exp $
*/

#include <common.h>
#include <command.h>
#include <dm.h>
#include <errno.h>
#include <asm/gpio.h>
#include <linux/delay.h>

#ifdef CONFIG_UBOOT_ENV
#include "../rtk_uboot_config.h"
#endif

#include "../rtk_types.h"
#include "smi.h"
#include "../rtk_error.h"

/*******************************************************************************/
/*  MDC/MDIO porting                                                           */
/*******************************************************************************/
#define RTL_GPIO_MDC	172  /* GPIO V4 */
#define RTL_GPIO_SDA	173  /* GPIO V5 */

/* RTL8363SC-VB Register Addresses */
#define RTL_REG_PHY_CTRL		0x00  /* PHY Control Register */
#define RTL_REG_PHY_STATUS		0x01  /* PHY Status Register */
#define RTL_REG_PHY_AN_ADV		0x04  /* Auto-Negotiation Advertisement */

/* MAC Control Registers (for EXT ports) - RTL8367C registers */
#define RTL_REG_MAC_FORCE_MODE		0x1311  /* MAC Force Mode Control */
#define RTL_REG_SGMII_NWAY		0x1d95  /* SGMII Nway Control */

/* Chip Identification Registers */
#define RTL_REG_CHIP_ID			0x1300  /* Chip ID Register */
#define RTL_REG_CHIP_VER		0x1301  /* Chip Version Register */
#define RTL_REG_CHIP_MODE		0x1302  /* Chip Mode Register */

/* MAC Force Mode Register Bits */
#define MAC_FORCE_EN			(1 << 12)  /* Force mode enable */
#define MAC_FORCE_LINK			(1 << 11)  /* Force link up */
#define MAC_FORCE_DUPLEX		(1 << 10)  /* Force full duplex */
#define MAC_FORCE_SPEED_MASK		(3 << 8)   /* Speed bits [9:8] */
#define MAC_FORCE_SPEED_10M		(0 << 8)
#define MAC_FORCE_SPEED_100M		(1 << 8)
#define MAC_FORCE_SPEED_1000M		(2 << 8)
#define MAC_NWAY_EN			(1 << 7)   /* MAC Nway enable */

/* SGMII Nway Register Bits */
#define SGMII_NWAY_EN			(1 << 1)   /* SGMII Nway enable */

/* PHY Control Register Bits */
#define PHY_CTRL_RESET			(1 << 15)
#define PHY_CTRL_SPEED_SEL_LSB		(1 << 13)  /* Speed Selection LSB */
#define PHY_CTRL_AN_ENABLE		(1 << 12)  /* Auto-Negotiation Enable */
#define PHY_CTRL_POWER_DOWN		(1 << 11)
#define PHY_CTRL_AN_RESTART		(1 << 9)
#define PHY_CTRL_DUPLEX			(1 << 8)   /* Full Duplex */
#define PHY_CTRL_SPEED_SEL_MSB		(1 << 6)   /* Speed Selection MSB */

/* Auto-Negotiation Advertisement Register Bits */
#define AN_ADV_100_FULL			(1 << 8)
#define AN_ADV_100_HALF			(1 << 7)
#define AN_ADV_10_FULL			(1 << 6)
#define AN_ADV_10_HALF			(1 << 5)

/* Speed values (using both MSB and LSB bits) */
#define SPEED_10M	0  /* MSB=0, LSB=0 */
#define SPEED_100M	1  /* MSB=0, LSB=1 */
#define SPEED_1000M	2  /* MSB=1, LSB=0 */

/* SMI Protocol Constants */
#define SMI_START_BITS		0xFFFFFFFF  /* 32 consecutive 1s */
#define SMI_START_CODE		0x01        /* Start of Frame: 01 */
#define SMI_READ_OP		0x02        /* Read operation: 10 */
#define SMI_WRITE_OP		0x01        /* Write operation: 01 */

/* Timing delays (microseconds) */
#define SMI_DELAY_US		2

/* Port mapping for RTL8363SC-VB */
#define UTP_PORT2		2   /* Logical port 2 -> Physical port 1 */
#define UTP_PORT3		3   /* Logical port 3 -> Physical port 3 */
#define EXT_PORT16		16  /* Logical port 16 -> Physical port 6 (CPU/SGMII) */

/* Port types */
#define PORT_TYPE_UTP		0
#define PORT_TYPE_EXT		1

/* SMI timing - matches Realtek SDK (DELAY=10000 loop iterations) */
#define SMI_DELAY_US 2
#define CLK_DURATION() udelay(SMI_DELAY_US)

/* _smi_start - Matches Realtek SDK _smi_start() */
static void _smi_start(void)
{
	/* Ensure both pins are outputs */
	gpio_set_mdc_output();
	gpio_set_mdc(0);
	gpio_set_sda_output();

	/* Initial state: SCK: 0, SDA: 1 */
	gpio_set_mdc(0);
	gpio_set_sda(1);
	CLK_DURATION();

	/* CLK 1: 0 -> 1, 1 -> 0 */
	gpio_set_mdc(1);
	CLK_DURATION();
	gpio_set_mdc(0);
	CLK_DURATION();

	/* CLK 2: */
	gpio_set_mdc(1);
	CLK_DURATION();
	gpio_set_sda(0);
	CLK_DURATION();
	gpio_set_mdc(0);
	CLK_DURATION();
	gpio_set_sda(1);
}

/* _smi_writeBit - Matches Realtek SDK _smi_writeBit() */
static void _smi_writeBit(u16 signal, u32 bit_len)
{
	int i;

	for (i = bit_len - 1; i >= 0; i--) {
		CLK_DURATION();

		/* Prepare data */
		if (signal & (1 << i))
			gpio_set_sda(1);
		else
			gpio_set_sda(0);
		CLK_DURATION();

		/* Clocking */
		gpio_set_mdc(1);
		CLK_DURATION();
		gpio_set_mdc(0);
	}
}

/* _smi_readBit - Matches Realtek SDK _smi_readBit() */
static void _smi_readBit(u32 bit_len, u32 *rData)
{
	u32 u;
	int i;

	*rData = 0;

	/* Change SDA to input for reading */
	gpio_set_sda_input();

	for (i = bit_len - 1; i >= 0; i--) {
		CLK_DURATION();

		/* Clocking */
		gpio_set_mdc(1);
		CLK_DURATION();
		u = gpio_read_sda();
		gpio_set_mdc(0);

		*rData |= (u << i);
	}

	/* Change SDA back to output */
	gpio_set_sda_output();
}

/* _smi_stop - Matches Realtek SDK _smi_stop() */
static void _smi_stop(void)
{
	/* Ensure SDA is output */
	gpio_set_sda_output();

	CLK_DURATION();
	gpio_set_sda(0);
	gpio_set_mdc(1);
	CLK_DURATION();
	gpio_set_sda(1);
	CLK_DURATION();
	gpio_set_mdc(1);
	CLK_DURATION();
	gpio_set_mdc(0);
	CLK_DURATION();
	gpio_set_mdc(1);

	/* Add a click */
	CLK_DURATION();
	gpio_set_mdc(0);
	CLK_DURATION();
	gpio_set_mdc(1);

	/* Change GPIO pins back to Input (idle state) */
	gpio_set_sda_input();
	gpio_set_mdc_input();
}

/* I2C-like Protocol Implementation - Matches Realtek SDK reg_i2c_read/write */
#define ACK_TIMER 5  /* ACK retry count */

/* reg_i2c_read - Matches Realtek SDK implementation */
rtksw_api_ret_t reg_i2c_read(rtksw_uint32 mAddrs, rtksw_uint32 *rData)
{
	u32 rawData = 0, ACK;
	u8 con;
	rtksw_api_ret_t ret = RT_ERR_OK;
	u16 reg_addr = (u16)(mAddrs & 0xFFFF);
	u16 data;

	*rData = 0;

	_smi_start();                          /* Start SMI */

	_smi_writeBit(0x0b, 4);                /* CTRL code: 4'b1011 for RTL8370 */
	_smi_writeBit(0x4, 3);                 /* CTRL code: 3'b100 */
	_smi_writeBit(0x1, 1);                 /* 1: issue READ command */

	con = 0;
	do {
		con++;
		_smi_readBit(1, &ACK);         /* ACK for issuing READ command */
	} while ((ACK != 0) && (con < ACK_TIMER));

	if (ACK != 0) ret = RT_ERR_FAILED;

	_smi_writeBit((reg_addr & 0xff), 8);   /* Set reg_addr[7:0] */

	con = 0;
	do {
		con++;
		_smi_readBit(1, &ACK);         /* ACK for setting reg_addr[7:0] */
	} while ((ACK != 0) && (con < ACK_TIMER));

	if (ACK != 0) ret = RT_ERR_FAILED;

	_smi_writeBit((reg_addr >> 8), 8);     /* Set reg_addr[15:8] */

	con = 0;
	do {
		con++;
		_smi_readBit(1, &ACK);         /* ACK by RTL8369 */
	} while ((ACK != 0) && (con < ACK_TIMER));

	if (ACK != 0) ret = RT_ERR_FAILED;

	_smi_readBit(8, &rawData);             /* Read DATA [7:0] */
	data = rawData & 0xff;

	_smi_writeBit(0x00, 1);                /* ACK by CPU */

	_smi_readBit(8, &rawData);             /* Read DATA [15:8] */

	_smi_writeBit(0x01, 1);                /* ACK by CPU */
	data |= (rawData << 8);

	_smi_stop();

	*rData = (rtksw_uint32)data;
	return ret;
}

/* reg_i2c_write - Matches Realtek SDK implementation */
rtksw_api_ret_t reg_i2c_write(rtksw_uint32 mAddrs, rtksw_uint32 rData)
{
	u8 con;
	u32 ACK;
	rtksw_api_ret_t ret = RT_ERR_OK;
	u16 reg_addr = (u16)(mAddrs & 0xFFFF);
	u16 wData = (u16)(rData & 0xFFFF);

	_smi_start();                          /* Start SMI */

	_smi_writeBit(0x0b, 4);                /* CTRL code: 4'b1011 for RTL8370 */
	_smi_writeBit(0x4, 3);                 /* CTRL code: 3'b100 */
	_smi_writeBit(0x0, 1);                 /* 0: issue WRITE command */

	con = 0;
	do {
		con++;
		_smi_readBit(1, &ACK);         /* ACK for issuing WRITE command */
	} while ((ACK != 0) && (con < ACK_TIMER));

	if (ACK != 0) ret = RT_ERR_FAILED;

	_smi_writeBit((reg_addr & 0xff), 8);   /* Set reg_addr[7:0] */

	con = 0;
	do {
		con++;
		_smi_readBit(1, &ACK);         /* ACK for setting reg_addr[7:0] */
	} while ((ACK != 0) && (con < ACK_TIMER));

	if (ACK != 0) ret = RT_ERR_FAILED;

	_smi_writeBit((reg_addr >> 8), 8);     /* Set reg_addr[15:8] */

	con = 0;
	do {
		con++;
		_smi_readBit(1, &ACK);         /* ACK for setting reg_addr[15:8] */
	} while ((ACK != 0) && (con < ACK_TIMER));

	if (ACK != 0) ret = RT_ERR_FAILED;

	_smi_writeBit((wData & 0xff), 8);      /* Write DATA [7:0] */

	con = 0;
	do {
		con++;
		_smi_readBit(1, &ACK);         /* ACK for writing data [7:0] */
	} while ((ACK != 0) && (con < ACK_TIMER));

	if (ACK != 0) ret = RT_ERR_FAILED;

	_smi_writeBit((wData >> 8), 8);        /* Write DATA [15:8] */

	con = 0;
	do {
		con++;
		_smi_readBit(1, &ACK);         /* ACK for writing data [15:8] */
	} while ((ACK != 0) && (con < ACK_TIMER));

	if (ACK != 0) ret = RT_ERR_FAILED;

	_smi_stop();

	return ret;
}

rtksw_api_ret_t reg_mdcmdio_read(rtksw_uint32 mAddrs, rtksw_uint32 *rData)
{
    return RT_ERR_OK;
}

rtksw_api_ret_t reg_mdcmdio_write(rtksw_uint32 mAddrs, rtksw_uint32 rData)
{
    return RT_ERR_OK;
}

rtksw_api_ret_t reg_spi_read(rtksw_uint32 mAddrs, rtksw_uint32 *rData)
{
    return RT_ERR_OK;
}

rtksw_api_ret_t reg_spi_write(rtksw_uint32 mAddrs, rtksw_uint32 rData)
{
    return RT_ERR_OK;
}

#ifdef EASYSMART_SDK
rtksw_api_ret_t reg_soc_read(rtksw_uint32 mAddrs, rtksw_uint32 *rData)
{
    rtksw_uint32 regData;

    if(mAddrs > 0xFFFF)
        return RT_ERR_INPUT;

    if(rData == NULL)
        return RT_ERR_NULL_POINTER;

    /* SoC address = ((switch register << 2) | 0x02000000) */
    /* SoC data = switch data [7:0] [15:8] [23:16] [31:24] */
    regData = REG32((mAddrs << 2) | 0x02000000);
    *rData = ((regData & 0xFF000000) >> 24) | ((regData & 0x00FF0000) >> 8);

    return RT_ERR_OK;
}

rtksw_api_ret_t reg_soc_write(rtksw_uint32 mAddrs, rtksw_uint32 rData)
{
    rtksw_uint32 regData;

    if(mAddrs > 0xFFFF)
        return RT_ERR_INPUT;

    if(rData > 0xFFFF)
        return RT_ERR_INPUT;

    /* SoC address = ((switch register << 2) | 0x02000000) */
    /* SoC data = switch data [7:0] [15:8] [23:16] [31:24] */
    regData = ((rData & 0x000000FF) << 24) | ((rData & 0x0000FF00) << 8);
    REG32((mAddrs << 2) | 0x02000000) = regData;

    return RT_ERR_OK;
}
#endif

rtksw_api_ret_t reg_smi_read(rtksw_uint32 unit, rtksw_uint32 mAddrs, rtksw_uint32 *rData)
{
    rtksw_api_ret_t retVal;
#if defined(CONFIG_MSSDK)
    retVal = ioal_mem32_read(unit, mAddrs, rData);
    return retVal;
#else
    /* User should maintain this switch-case sample code.         */
    /* Make sure that each unit can call correct I2C/SPI/MDC_MDIO */
    /* register reading & writing function. This sample code      */
    /* shows that unit 0 is controlled by I2C interface.          */
    switch (unit)
    {
        case 0:
#ifdef EASYSMART_SDK
            if ((retVal = reg_soc_read(mAddrs, rData)) != RT_ERR_OK)
                return retVal;
#else
            if ((retVal = reg_i2c_read(mAddrs, rData)) != RT_ERR_OK)
                return retVal;
#endif
            break;
#if 0
        case 1:
            break;
        case 2:
            break;
        case 3:
            break;
#endif            
        default:
            return RT_ERR_UNIT_ID;
    }

    return RT_ERR_OK;
#endif
}


rtksw_api_ret_t reg_smi_write(rtksw_uint32 unit, rtksw_uint32 mAddrs, rtksw_uint32 rData)
{
    rtksw_api_ret_t retVal;
#if defined(CONFIG_MSSDK)
    retVal = ioal_mem32_write(unit, mAddrs, rData);
    return retVal;
#else
    /* User should maintain this switch-case sample code.         */
    /* Make sure that each unit can call correct I2C/SPI/MDC_MDIO */
    /* register reading & writing function. This sample code      */
    /* shows that unit 0 is controlled by I2C interface.          */
    switch (unit)
    {
        case 0:
#ifdef EASYSMART_SDK
            if ((retVal = reg_soc_write(mAddrs, rData)) != RT_ERR_OK)
                return retVal;
#else
            if ((retVal = reg_i2c_write(mAddrs, rData)) != RT_ERR_OK)
                return retVal;
#endif
            break;
#if 0
        case 1:
            break;
        case 2:
            break;
        case 3:
            break;
#endif
        default:
            return RT_ERR_UNIT_ID;
    }

    return RT_ERR_OK;
#endif
}
