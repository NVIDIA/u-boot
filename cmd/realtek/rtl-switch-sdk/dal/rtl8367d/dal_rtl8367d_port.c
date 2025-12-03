/*
 * Copyright (C) 2013 Realtek Semiconductor Corp.
 * All Rights Reserved.
 *
 * This program is the proprietary software of Realtek Semiconductor
 * Corporation and/or its licensors, and only be used, duplicated,
 * modified or distributed under the authorized license from Realtek.
 *
 * ANY USE OF THE SOFTWARE OTHER THAN AS AUTHORIZED UNDER
 * THIS LICENSE OR COPYRIGHT LAW IS PROHIBITED.
 *
 * $Revision$
 * $Date$
 *
 * Purpose : RTK switch high-level API for RTL8367/RTL8367D
 * Feature : Here is a list of all functions and variables in Port module.
 *
 */

#include "../../rtk_switch.h"
#include "../../rtk_error.h"
#include "dal_rtl8367d_port.h"
#include "rtl8367d_asicdrv.h"

#include "../dal_mgmts.h"
#include "../../osal/lib.h"

#define RTL8367D_PORT_SDS_MODE_DISABLE      0x1f
#define RTL8367D_PORT_SDS_MODE_SGMII        0x2
#define RTL8367D_PORT_SDS_MODE_HSGMII       0x12
#define RTL8367D_PORT_SDS_MODE_1000X        0x4
#define RTL8367D_PORT_SDS_MODE_100FX        0x5
#define RTL8367D_PORT_SDS_MODE_1000X_100FX  0x7
#define RTL8367D_PORT_SDS_MODE_FIBER_2P5G   0x16

#define RTL8367D_EXT_RTKSW_PORT_SPEED_10M         0x0
#define RTL8367D_EXT_RTKSW_PORT_SPEED_100M        0x1
#define RTL8367D_EXT_RTKSW_PORT_SPEED_1000M       0x2
#define RTL8367D_EXT_RTKSW_PORT_SPEED_500M        0x3
#define RTL8367D_EXT_RTKSW_PORT_SPEED_2500M       0x5

const rtksw_uint32 HSGCfg[][2] = { {0x0427, 0x4E0C}, {0x0428, 0xAA00}, {0x0425, 0x5189}, {0x0424, 0x8414}, {0x0423, 0x1020}, {0x0410, 0x0002}, {0x0504, 0x051B}, {0x0421, 0x8E13}, {0x0422, 0x1140}, {0x0004, 0x074F}};
const rtksw_uint32 SGCfg[][2] = { {0x0427, 0x4E0C}, {0x0428, 0xAA00}, {0x0425, 0x5189}, {0x0424, 0x8414}, {0x0423, 0x1020}, {0x0410, 0x0002}, {0x0484, 0x011B}, {0x0421, 0x8E13}, {0x0422, 0x1140}, {0x0004, 0x074F}};
const rtksw_uint32 Fiber1000M100MCfg[][2] = { {0x0427, 0x4E0C}, {0x0428, 0xAA00}, {0x0425, 0x5189}, {0x0424, 0x8414}, {0x0423, 0x1020}, {0x0410, 0x0002}, {0x0484, 0x011B}, {0x0421, 0x8E13}, {0x0422, 0x1140}, {0x0004, 0x074F}, {0x0040, 0x2100}, {0x0044, 0x0C01}, {0x0040, 0x1140}, {0x0044, 0x01A0}, {0x0001, 0x0F20}};
const rtksw_uint32 Fiber1000MCfg[][2] = { {0x0427, 0x4E0C}, {0x0428, 0xAA00}, {0x0425, 0x5189}, {0x0424, 0x8414}, {0x0423, 0x1020}, {0x0410, 0x0002}, {0x0484, 0x011B}, {0x0421, 0x8E13}, {0x0422, 0x1140}, {0x0004, 0x074F}, {0x0040, 0x1140}, {0x0044, 0x01A0}};
const rtksw_uint32 Fiber100MCfg[][2] = { {0x0427, 0x4E0C}, {0x0428, 0xAA00}, {0x0425, 0x5189}, {0x0424, 0x8414}, {0x0423, 0x1020}, {0x0410, 0x0002}, {0x0484, 0x011B}, {0x0421, 0x8E13}, {0x0422, 0x1140}, {0x0004, 0x074F}, {0x0040, 0x2100}, {0x0044, 0x0C01}};
const rtksw_uint32 Fiber2P5GCfg[][2] = { {0x0427, 0x4E0C}, {0x0428, 0xAA00}, {0x0425, 0x5189}, {0x0424, 0x8414}, {0x0423, 0x1020}, {0x0410, 0x0002}, {0x0504, 0x051B}, {0x0421, 0x8E13}, {0x0422, 0x1140}, {0x0040, 0x1140}, {0x0044, 0x01A0}};

const rtksw_uint32 RTCTPatch[][2] =
{
    {0xa436, 0x8160},  
    {0xa438, 0x50e7}, 
    {0xa436, 0x8162}, 
    {0xa438, 0xb23b}, 
    {0xa436, 0x8164}, 
    {0xa438, 0x35eb}, 
    {0xa436, 0x8166}, 
    {0xa438, 0xed20}, 
    {0xa436, 0x8174}, 
    {0xa438, 0x0400}, 
    {0xa436, 0x8176}, 
    {0xa438, 0x009a}, 
    {0xa436, 0x8178}, 
    {0xa438, 0xf5a9}, 
    {0xa436, 0x817a}, 
    {0xa438, 0xe69c}, 
    {0xa436, 0x8211}, 
    {0xa438, 0x0e21}, 
    {0xa436, 0x8213}, 
    {0xa438, 0xe660}, 
    {0xa436, 0x8215}, 
    {0xa438, 0x207f}, 
    {0xa436, 0x8217}, 
    {0xa438, 0xeb56}, 
    {0xa436, 0x819f}, 
    {0xa438, 0xc313}, 
    {0xa436, 0x81b5}, 
    {0xa438, 0x1010}, 
    {0xa436, 0x81b7}, 
    {0xa438, 0xea03}, 
    {0xa436, 0x8186}, 
    {0xa438, 0x3501}
};

#ifdef EASYSMART_SDK
static rtksw_api_ret_t _dal_rtl8367e_setAsicPHYOCPReg(rtksw_uint32 unit, rtksw_uint32 phyNo, rtksw_uint32 ocpAddr, rtksw_uint32 ocpData )
{
    ret_t retVal;
    rtksw_uint32 regAddr;
    rtksw_uint32 ocpAddrPrefix, ocpAddr9_6, ocpAddr5_1;

    ocpAddrPrefix = ((ocpAddr & 0xFC00) >> 10); /* ASIC */
    if((retVal = rtl8367d_setAsicRegBits(unit, RTL8367D_REG_GPHY_OCP_MSB_0, RTL8367D_CFG_DW8051_OCPADR_MSB_MASK, ocpAddrPrefix)) != RT_ERR_OK)
        return retVal;

    /*prepare access address*/
    ocpAddr9_6 = ((ocpAddr >> 6) & 0x000F);
    ocpAddr5_1 = ((ocpAddr >> 1) & 0x001F);
    regAddr = RTL8367D_PHY_BASE | (ocpAddr9_6 << 8) | (phyNo << RTL8367D_PHY_OFFSET) | ocpAddr5_1;
    retVal = rtl8367d_setAsicReg(unit, regAddr, ocpData);
    if(retVal != RT_ERR_OK)
        return retVal;

    return retVal;
}
#endif

#ifdef EASYSMART_SDK
static rtksw_api_ret_t _dal_rtl8367e_getAsicPHYOCPReg(rtksw_uint32 unit, rtksw_uint32 phyNo, rtksw_uint32 ocpAddr, rtksw_uint32 *pRegData )
{
    ret_t retVal;
    rtksw_uint32 regAddr, regData;
    rtksw_uint32 ocpAddrPrefix, ocpAddr9_6, ocpAddr5_1;

    ocpAddrPrefix = ((ocpAddr & 0xFC00) >> 10); /* ASIC */
    if((retVal = rtl8367d_setAsicRegBits(unit, RTL8367D_REG_GPHY_OCP_MSB_0, RTL8367D_CFG_DW8051_OCPADR_MSB_MASK, ocpAddrPrefix)) != RT_ERR_OK)
        return retVal;

    /*prepare access address*/
    ocpAddr9_6 = ((ocpAddr >> 6) & 0x000F);
    ocpAddr5_1 = ((ocpAddr >> 1) & 0x001F);
    regAddr = RTL8367D_PHY_BASE | (ocpAddr9_6 << 8) | (phyNo << RTL8367D_PHY_OFFSET) | ocpAddr5_1;
    retVal = rtl8367d_getAsicReg(unit, regAddr, &regData);
    if(retVal != RT_ERR_OK)
        return retVal;

    *pRegData = regData;
    return RT_ERR_OK;
}
#endif

static rtksw_api_ret_t _dal_rtl8367d_setAsicPHYOCPReg(rtksw_uint32 unit, rtksw_uint32 phyNo, rtksw_uint32 ocpAddr, rtksw_uint32 ocpData )
{
    ret_t retVal;
    rtksw_uint32 regData;
    rtksw_uint32 busyFlag, checkCounter;
    rtksw_uint32 ocpAddrPrefix, ocpAddr9_6, ocpAddr5_1;

#ifdef EASYSMART_SDK 
    if ((rtksw_switch_chipType_get(unit) == CHIP_RTL8367E) && (unit == 0))
    {
        return _dal_rtl8367e_setAsicPHYOCPReg(unit, phyNo, ocpAddr, ocpData);
    }
#endif

    /*Check internal phy access busy or not*/
    retVal = rtl8367d_getAsicReg(unit, RTL8367D_REG_INDRECT_ACCESS_STATUS, &busyFlag);
    if(retVal != RT_ERR_OK)
        return retVal;

    if(busyFlag)
        return RT_ERR_BUSYWAIT_TIMEOUT;

    ocpAddrPrefix = ((ocpAddr & 0xFC00) >> 10);
    if((retVal = rtl8367d_setAsicRegBits(unit, RTL8367D_REG_GPHY_OCP_MSB_0, RTL8367D_CFG_CPU_OCPADR_MSB_MASK, ocpAddrPrefix)) != RT_ERR_OK)
        return retVal;

    /*prepare access data*/
    retVal = rtl8367d_setAsicReg(unit, RTL8367D_REG_INDRECT_ACCESS_WRITE_DATA, ocpData);
    if(retVal != RT_ERR_OK)
        return retVal;

    /*prepare access address*/
    ocpAddr9_6 = ((ocpAddr >> 6) & 0x000F);
    ocpAddr5_1 = ((ocpAddr >> 1) & 0x001F);
    regData = RTL8367D_PHY_BASE | (ocpAddr9_6 << 8) | (phyNo << RTL8367D_PHY_OFFSET) | ocpAddr5_1;
    retVal = rtl8367d_setAsicReg(unit, RTL8367D_REG_INDRECT_ACCESS_ADDRESS, regData);
    if(retVal != RT_ERR_OK)
        return retVal;

    /*Set WRITE Command*/
    retVal = rtl8367d_setAsicReg(unit, RTL8367D_REG_INDRECT_ACCESS_CTRL, RTL8367D_CMD_MASK | RTL8367D_RW_MASK);

    checkCounter = 100;
    while(checkCounter)
    {
        retVal = rtl8367d_getAsicReg(unit, RTL8367D_REG_INDRECT_ACCESS_STATUS, &busyFlag);
        if((retVal != RT_ERR_OK) || busyFlag)
        {
            checkCounter --;
            if(0 == checkCounter)
                return RT_ERR_BUSYWAIT_TIMEOUT;
        }
        else
        {
            checkCounter = 0;
        }
    }

    return retVal;
}

static rtksw_api_ret_t _dal_rtl8367d_getAsicPHYOCPReg(rtksw_uint32 unit, rtksw_uint32 phyNo, rtksw_uint32 ocpAddr, rtksw_uint32 *pRegData )
{
    ret_t retVal;
    rtksw_uint32 regData;
    rtksw_uint32 busyFlag,checkCounter;
    rtksw_uint32 ocpAddrPrefix, ocpAddr9_6, ocpAddr5_1;

#ifdef EASYSMART_SDK 
    if ((rtksw_switch_chipType_get(unit) == CHIP_RTL8367E) && (unit == 0))
    {
        return _dal_rtl8367e_getAsicPHYOCPReg(unit, phyNo, ocpAddr, pRegData);
    }
#endif    

    /*Check internal phy access busy or not*/
    retVal = rtl8367d_getAsicReg(unit, RTL8367D_REG_INDRECT_ACCESS_STATUS, &busyFlag);
    if(retVal != RT_ERR_OK)
        return retVal;

    if(busyFlag)
        return RT_ERR_BUSYWAIT_TIMEOUT;

    ocpAddrPrefix = ((ocpAddr & 0xFC00) >> 10); /* ASIC */
    if((retVal = rtl8367d_setAsicRegBits(unit, RTL8367D_REG_GPHY_OCP_MSB_0, RTL8367D_CFG_CPU_OCPADR_MSB_MASK, ocpAddrPrefix)) != RT_ERR_OK)
        return retVal;

    /*prepare access address*/
    ocpAddr9_6 = ((ocpAddr >> 6) & 0x000F);
    ocpAddr5_1 = ((ocpAddr >> 1) & 0x001F);
    regData = RTL8367D_PHY_BASE | (ocpAddr9_6 << 8) | (phyNo << RTL8367D_PHY_OFFSET) | ocpAddr5_1;
    retVal = rtl8367d_setAsicReg(unit, RTL8367D_REG_INDRECT_ACCESS_ADDRESS, regData);
    if(retVal != RT_ERR_OK)
        return retVal;

    /*Set READ Command*/
    retVal = rtl8367d_setAsicReg(unit, RTL8367D_REG_INDRECT_ACCESS_CTRL, RTL8367D_CMD_MASK );
    if(retVal != RT_ERR_OK)
        return retVal;

    checkCounter = 100;
    while(checkCounter)
    {
        retVal = rtl8367d_getAsicReg(unit, RTL8367D_REG_INDRECT_ACCESS_STATUS, &busyFlag);
        if((retVal != RT_ERR_OK) || busyFlag)
        {
            checkCounter --;
            if(0 == checkCounter)
                return RT_ERR_FAILED;
        }
        else
        {
            checkCounter = 0;
        }
    }

    /*get PHY register*/
    retVal = rtl8367d_getAsicReg(unit, RTL8367D_REG_INDRECT_ACCESS_READ_DATA, &regData);
    if(retVal != RT_ERR_OK)
        return retVal;

    *pRegData = regData;
    return RT_ERR_OK;
}

static rtksw_api_ret_t _dal_rtl8367d_setAsicPHYReg(rtksw_uint32 unit, rtksw_uint32 phyNo, rtksw_uint32 phyAddr, rtksw_uint32 phyData )
{
    rtksw_uint32 ocp_addr;

    if(phyAddr > RTL8367D_PHY_REGNOMAX)
        return RT_ERR_PHY_REG_ID;

    ocp_addr = 0xa400 + phyAddr*2;

    return _dal_rtl8367d_setAsicPHYOCPReg(unit, phyNo, ocp_addr, phyData);
}

static rtksw_api_ret_t _dal_rtl8367d_getAsicPHYReg(rtksw_uint32 unit, rtksw_uint32 phyNo, rtksw_uint32 phyAddr, rtksw_uint32 *pRegData )
{
    rtksw_uint32 ocp_addr;

    if(phyAddr > RTL8367D_PHY_REGNOMAX)
        return RT_ERR_PHY_REG_ID;

    ocp_addr = 0xa400 + phyAddr*2;

    return _dal_rtl8367d_getAsicPHYOCPReg(unit, phyNo, ocp_addr, pRegData);
}

static rtksw_api_ret_t _dal_rtl8367d_setUtp4RgmiiMode(rtksw_uint32 unit, rtksw_port_t port, rtksw_mode_ext_t mode)
{
    rtksw_api_ret_t retVal;

    /* Only accept Port 4 & (RGMII or DIEABLE) */
    if (port != UTP_PORT4)
        return RT_ERR_PORT_ID;

    if ((mode != RTKSW_MODE_EXT_RGMII) && (mode != RTKSW_MODE_EXT_DISABLE))
        return RT_ERR_INPUT;

    /* Configure RGMII DP, DN, E2, MODE */
    if ((retVal = rtl8367d_setAsicRegBit(unit, RTL8367D_REG_CHIP_DEBUG0, RTL8367D_SEL33_EXT1_OFFSET, 1)) != RT_ERR_OK)
        return retVal;

    if ((retVal = rtl8367d_setAsicRegBit(unit, RTL8367D_REG_CHIP_DEBUG0, RTL8367D_DRI_EXT1_RG_OFFSET, 1)) != RT_ERR_OK)
        return retVal;

    if ((retVal = rtl8367d_setAsicRegBit(unit, RTL8367D_REG_CHIP_DEBUG0, RTL8367D_DRI_EXT1_OFFSET, 1)) != RT_ERR_OK)
        return retVal;

    if ((retVal = rtl8367d_setAsicRegBit(unit, RTL8367D_REG_CHIP_DEBUG0, RTL8367D_SLR_EXT1_OFFSET, 1)) != RT_ERR_OK)
        return retVal;

    if ((retVal = rtl8367d_setAsicRegBits(unit, RTL8367D_REG_CHIP_DEBUG1, RTL8367D_RG1_DN_MASK, 7)) != RT_ERR_OK)
        return retVal;

    if ((retVal = rtl8367d_setAsicRegBits(unit, RTL8367D_REG_CHIP_DEBUG1, RTL8367D_RG1_DP_MASK, 5)) != RT_ERR_OK)
        return retVal;

    if ((retVal = rtl8367d_setAsicRegBits(unit, RTL8367D_REG_EXT_TXC_DLY, RTL8367D_EXT1_RGMII_TX_DELAY_MASK, 0)) != RT_ERR_OK)
        return retVal;

    if ((retVal = rtl8367d_setAsicRegBits(unit, RTL8367D_REG_DIGITAL_INTERFACE_SELECT, RTL8367D_SELECT_GMII_1_MASK, mode)) != RT_ERR_OK)
        return retVal;

    return RT_ERR_OK;
}

static rtksw_api_ret_t _dal_rtl8367d_getUtp4RgmiiMode(rtksw_uint32 unit, rtksw_port_t port, rtksw_mode_ext_t *pMode)
{
    rtksw_api_ret_t retVal;

    /* Only accept Port 4 & (RGMII or DIEABLE) */
    if (port != UTP_PORT4)
        return RT_ERR_PORT_ID;

    if (pMode == NULL)
        return RT_ERR_NULL_POINTER;

    if ((retVal = rtl8367d_getAsicRegBits(unit, RTL8367D_REG_DIGITAL_INTERFACE_SELECT, RTL8367D_SELECT_GMII_1_MASK, pMode)) != RT_ERR_OK)
        return retVal;

    return RT_ERR_OK;
}

static rtksw_api_ret_t _rtl8367d_setAsicPortExtMode(rtksw_uint32 unit, rtksw_uint32 id, rtksw_uint32 mode)
{
    rtksw_api_ret_t  retVal;
    rtksw_uint32     i;
    rtksw_port_media_t media_type;

    if ((id >= 3) || (id == 0))
        return RT_ERR_OUT_OF_RANGE;

    if( (mode == RTKSW_MODE_EXT_TMII_MAC) || (mode == RTKSW_MODE_EXT_TMII_PHY) )
    {
        if( (retVal = rtl8367d_setAsicRegBit(unit, RTL8367D_REG_BYPASS_LINE_RATE, id, 1)) != RT_ERR_OK)
            return retVal;
    }
    else
    {
        if( (retVal = rtl8367d_setAsicRegBit(unit, RTL8367D_REG_BYPASS_LINE_RATE, id, 0)) != RT_ERR_OK)
            return retVal;
    }

    if (id == 1)
    {
        if (mode == RTKSW_MODE_EXT_DISABLE)
        {
            if((retVal = rtl8367d_setAsicRegBits(unit, RTL8367D_REG_SDS_MISC, RTL8367D_CFG_SDS_MODE_MASK, RTL8367D_PORT_SDS_MODE_DISABLE)) != RT_ERR_OK)
                return retVal;

            if((retVal = rtl8367d_setAsicRegBit(unit, RTL8367D_REG_SDS_MISC, RTL8367D_MAC6_SEL_SDS0_OFFSET, 0)) != RT_ERR_OK)
                return retVal;

            if((retVal = rtl8367d_setAsicRegBits(unit, RTL8367D_REG_FIBER_CFG_2, RTL8367D_SDS_RX_DISABLE_MASK, 0)) != RT_ERR_OK)
                return retVal;
        }
        else if ((mode == RTKSW_MODE_EXT_SGMII) || (mode == RTKSW_MODE_EXT_HSGMII) || (mode == RTKSW_MODE_EXT_1000X_100FX) || (mode == RTKSW_MODE_EXT_1000X) || (mode == RTKSW_MODE_EXT_100FX) || (mode == RTKSW_MODE_EXT_FIBER_2P5G))
        {
            if ((retVal = dal_rtl8367d_port_phyComboPortMedia_get(unit, UTP_PORT4, &media_type)) != RT_ERR_OK)
                return retVal;

            if (media_type == RTKSW_PORT_MEDIA_FIBER)
            {
                /* SDS0 already used by port 4 */
                return RT_ERR_PORT_ID;
            }

            if((retVal = rtl8367d_setAsicRegBit(unit, RTL8367D_REG_SDS_MISC, RTL8367D_MAC6_SEL_SDS0_OFFSET, 1)) != RT_ERR_OK)
                return retVal;

            switch (mode)
            {
                case RTKSW_MODE_EXT_SGMII:
                    for(i = 0; i < sizeof(SGCfg) / (sizeof(rtksw_uint32) * 2); i++)
                    {
                        if( (retVal = rtl8367d_setAsicReg(unit, RTL8367D_REG_SDS_INDACS_DATA, SGCfg[i][1])) != RT_ERR_OK)
                            return retVal;

                        if( (retVal = rtl8367d_setAsicReg(unit, RTL8367D_REG_SDS_INDACS_ADR, SGCfg[i][0])) != RT_ERR_OK)
                            return retVal;

                        if( (retVal = rtl8367d_setAsicReg(unit, RTL8367D_REG_SDS_INDACS_CMD, 0x00CD)) != RT_ERR_OK)
                            return retVal;
                    }

                    if ((retVal = rtl8367d_setAsicRegBits(unit, RTL8367D_REG_FIBER_CFG_2, RTL8367D_SDS_RX_DISABLE_MASK, 0x1)) != RT_ERR_OK)
                        return retVal;

                    if ((retVal = rtl8367d_setAsicRegBit(unit, RTL8367D_REG_SDS_MISC, RTL8367D_PA12PC_EN_S0_OFFSET, 1)) != RT_ERR_OK)
                        return retVal;

                    if ((retVal = rtl8367d_setAsicRegBit(unit, RTL8367D_REG_SDS_MISC, RTL8367D_PA33PC_EN_S0_OFFSET, 1)) != RT_ERR_OK)
                        return retVal;

                    if ((retVal = rtl8367d_setAsicRegBits(unit, RTL8367D_REG_SDS_MISC, RTL8367D_CFG_SDS_MODE_MASK, RTL8367D_PORT_SDS_MODE_SGMII)) != RT_ERR_OK)
                        return retVal;

                    break;
                case RTKSW_MODE_EXT_HSGMII:
                    for(i = 0; i < sizeof(HSGCfg) / (sizeof(rtksw_uint32) * 2); i++)
                    {
                        if( (retVal = rtl8367d_setAsicReg(unit, RTL8367D_REG_SDS_INDACS_DATA, HSGCfg[i][1])) != RT_ERR_OK)
                            return retVal;

                        if( (retVal = rtl8367d_setAsicReg(unit, RTL8367D_REG_SDS_INDACS_ADR, HSGCfg[i][0])) != RT_ERR_OK)
                            return retVal;

                        if( (retVal = rtl8367d_setAsicReg(unit, RTL8367D_REG_SDS_INDACS_CMD, 0x00CD)) != RT_ERR_OK)
                            return retVal;
                    }

                    if ((retVal = rtl8367d_setAsicRegBits(unit, RTL8367D_REG_FIBER_CFG_2, RTL8367D_SDS_RX_DISABLE_MASK, 0x1)) != RT_ERR_OK)
                        return retVal;

                    if ((retVal = rtl8367d_setAsicRegBit(unit, RTL8367D_REG_SDS_MISC, RTL8367D_PA12PC_EN_S0_OFFSET, 1)) != RT_ERR_OK)
                        return retVal;

                    if ((retVal = rtl8367d_setAsicRegBit(unit, RTL8367D_REG_SDS_MISC, RTL8367D_PA33PC_EN_S0_OFFSET, 1)) != RT_ERR_OK)
                        return retVal;

                    if ((retVal = rtl8367d_setAsicRegBits(unit, RTL8367D_REG_SDS_MISC, RTL8367D_CFG_SDS_MODE_MASK, RTL8367D_PORT_SDS_MODE_HSGMII)) != RT_ERR_OK)
                        return retVal;

                    break;
                case RTKSW_MODE_EXT_1000X_100FX:
                    for(i = 0; i < sizeof(Fiber1000M100MCfg) / (sizeof(rtksw_uint32) * 2); i++)
                    {
                        if( (retVal = rtl8367d_setAsicReg(unit, RTL8367D_REG_SDS_INDACS_DATA, Fiber1000M100MCfg[i][1])) != RT_ERR_OK)
                            return retVal;

                        if( (retVal = rtl8367d_setAsicReg(unit, RTL8367D_REG_SDS_INDACS_ADR, Fiber1000M100MCfg[i][0])) != RT_ERR_OK)
                            return retVal;

                        if( (retVal = rtl8367d_setAsicReg(unit, RTL8367D_REG_SDS_INDACS_CMD, 0x00CD)) != RT_ERR_OK)
                            return retVal;
                    }

                    if( (retVal = rtl8367d_setAsicRegBits(unit, RTL8367D_REG_FIBER_CFG_2, RTL8367D_SDS_RX_DISABLE_MASK, 1)) != RT_ERR_OK)
                        return retVal;

                    if( (retVal = rtl8367d_setAsicRegBit(unit, RTL8367D_REG_SDS_MISC, RTL8367D_PA12PC_EN_S0_OFFSET, 1)) != RT_ERR_OK)
                        return retVal;

                    if( (retVal = rtl8367d_setAsicRegBit(unit, RTL8367D_REG_SDS_MISC, RTL8367D_PA33PC_EN_S0_OFFSET, 1)) != RT_ERR_OK)
                        return retVal;

                    if( (retVal = rtl8367d_setAsicRegBits(unit, RTL8367D_REG_SDS_MISC, RTL8367D_CFG_SDS_MODE_MASK, RTL8367D_PORT_SDS_MODE_1000X_100FX)) != RT_ERR_OK)
                        return retVal;

                    break;
                case RTKSW_MODE_EXT_1000X:
                    for(i = 0; i < sizeof(Fiber1000MCfg) / (sizeof(rtksw_uint32) * 2); i++)
                    {
                        if( (retVal = rtl8367d_setAsicReg(unit, RTL8367D_REG_SDS_INDACS_DATA, Fiber1000MCfg[i][1])) != RT_ERR_OK)
                            return retVal;

                        if( (retVal = rtl8367d_setAsicReg(unit, RTL8367D_REG_SDS_INDACS_ADR, Fiber1000MCfg[i][0])) != RT_ERR_OK)
                            return retVal;

                        if( (retVal = rtl8367d_setAsicReg(unit, RTL8367D_REG_SDS_INDACS_CMD, 0x00CD)) != RT_ERR_OK)
                            return retVal;
                    }

                    if( (retVal = rtl8367d_setAsicRegBits(unit, RTL8367D_REG_FIBER_CFG_2, RTL8367D_SDS_RX_DISABLE_MASK, 1)) != RT_ERR_OK)
                        return retVal;

                    if( (retVal = rtl8367d_setAsicRegBit(unit, RTL8367D_REG_SDS_MISC, RTL8367D_PA12PC_EN_S0_OFFSET, 1)) != RT_ERR_OK)
                        return retVal;

                    if( (retVal = rtl8367d_setAsicRegBit(unit, RTL8367D_REG_SDS_MISC, RTL8367D_PA33PC_EN_S0_OFFSET, 1)) != RT_ERR_OK)
                        return retVal;

                    if( (retVal = rtl8367d_setAsicRegBits(unit, RTL8367D_REG_SDS_MISC, RTL8367D_CFG_SDS_MODE_MASK, RTL8367D_PORT_SDS_MODE_1000X)) != RT_ERR_OK)
                        return retVal;

                    break;
                case RTKSW_MODE_EXT_100FX:
                    for(i = 0; i < sizeof(Fiber100MCfg) / (sizeof(rtksw_uint32) * 2); i++)
                    {
                        if( (retVal = rtl8367d_setAsicReg(unit, RTL8367D_REG_SDS_INDACS_DATA, Fiber100MCfg[i][1])) != RT_ERR_OK)
                            return retVal;

                        if( (retVal = rtl8367d_setAsicReg(unit, RTL8367D_REG_SDS_INDACS_ADR, Fiber100MCfg[i][0])) != RT_ERR_OK)
                            return retVal;

                        if( (retVal = rtl8367d_setAsicReg(unit, RTL8367D_REG_SDS_INDACS_CMD, 0x00CD)) != RT_ERR_OK)
                            return retVal;
                    }

                    if( (retVal = rtl8367d_setAsicRegBits(unit, RTL8367D_REG_FIBER_CFG_2, RTL8367D_SDS_RX_DISABLE_MASK, 1)) != RT_ERR_OK)
                        return retVal;

                    if( (retVal = rtl8367d_setAsicRegBit(unit, RTL8367D_REG_SDS_MISC, RTL8367D_PA12PC_EN_S0_OFFSET, 1)) != RT_ERR_OK)
                        return retVal;

                    if( (retVal = rtl8367d_setAsicRegBit(unit, RTL8367D_REG_SDS_MISC, RTL8367D_PA33PC_EN_S0_OFFSET, 1)) != RT_ERR_OK)
                        return retVal;

                    if( (retVal = rtl8367d_setAsicRegBits(unit, RTL8367D_REG_SDS_MISC, RTL8367D_CFG_SDS_MODE_MASK, RTL8367D_PORT_SDS_MODE_100FX)) != RT_ERR_OK)
                        return retVal;

                    break;
                case RTKSW_MODE_EXT_FIBER_2P5G:
                    for(i = 0; i < sizeof(Fiber2P5GCfg) / (sizeof(rtksw_uint32) * 2); i++)
                    {
                        if( (retVal = rtl8367d_setAsicReg(unit, RTL8367D_REG_SDS_INDACS_DATA, Fiber2P5GCfg[i][1])) != RT_ERR_OK)
                            return retVal;

                        if( (retVal = rtl8367d_setAsicReg(unit, RTL8367D_REG_SDS_INDACS_ADR, Fiber2P5GCfg[i][0])) != RT_ERR_OK)
                            return retVal;

                        if( (retVal = rtl8367d_setAsicReg(unit, RTL8367D_REG_SDS_INDACS_CMD, 0x00CD)) != RT_ERR_OK)
                            return retVal;
                    }

                    if( (retVal = rtl8367d_setAsicRegBits(unit, RTL8367D_REG_FIBER_CFG_2, RTL8367D_SDS_RX_DISABLE_MASK, 1)) != RT_ERR_OK)
                        return retVal;

                    if( (retVal = rtl8367d_setAsicRegBit(unit, RTL8367D_REG_SDS_MISC, RTL8367D_PA12PC_EN_S0_OFFSET, 1)) != RT_ERR_OK)
                        return retVal;

                    if( (retVal = rtl8367d_setAsicRegBit(unit, RTL8367D_REG_SDS_MISC, RTL8367D_PA33PC_EN_S0_OFFSET, 1)) != RT_ERR_OK)
                        return retVal;

                    if( (retVal = rtl8367d_setAsicRegBits(unit, RTL8367D_REG_SDS_MISC, RTL8367D_CFG_SDS_MODE_MASK, RTL8367D_PORT_SDS_MODE_FIBER_2P5G)) != RT_ERR_OK)
                        return retVal;

                    break;
                default:
                    return RT_ERR_INPUT;
            }
        }
        else
            return RT_ERR_INPUT;
    }

    if (id == 2)
    {
        if (mode == RTKSW_MODE_EXT_DISABLE)
        {
            if ((retVal = rtl8367d_setAsicRegBit(unit, RTL8367D_REG_TOP_CON0, RTL8367D_MAC7_SEL_EXT1_OFFSET, 0)) != RT_ERR_OK)
                return retVal;

            if ((retVal = rtl8367d_setAsicRegBits(unit, RTL8367D_REG_DIGITAL_INTERFACE_SELECT, RTL8367D_SELECT_GMII_1_MASK, 0x0)) != RT_ERR_OK)
                return retVal;

            if ((retVal = rtl8367d_setAsicRegBits(unit, RTL8367D_REG_SDS1_MISC0, RTL8367D_SDS1_MODE_MASK, RTL8367D_PORT_SDS_MODE_DISABLE)) != RT_ERR_OK)
                return retVal;
        }
        else if ((mode == RTKSW_MODE_EXT_RGMII) || (mode == RTKSW_MODE_EXT_MII_MAC) || (mode == RTKSW_MODE_EXT_MII_PHY) || (mode == RTKSW_MODE_EXT_TMII_MAC) ||
                 (mode == RTKSW_MODE_EXT_TMII_PHY) || (mode == RTKSW_MODE_EXT_RMII_MAC) || (mode == RTKSW_MODE_EXT_RMII_PHY))
        {
            /* Configure RGMII DP, DN, E2, MODE */
            if ((retVal = rtl8367d_setAsicRegBit(unit, RTL8367D_REG_CHIP_DEBUG0, RTL8367D_SEL33_EXT1_OFFSET, 1)) != RT_ERR_OK)
                return retVal;

            if ((retVal = rtl8367d_setAsicRegBit(unit, RTL8367D_REG_CHIP_DEBUG0, RTL8367D_DRI_EXT1_RG_OFFSET, 1)) != RT_ERR_OK)
                return retVal;

            if ((retVal = rtl8367d_setAsicRegBit(unit, RTL8367D_REG_CHIP_DEBUG0, RTL8367D_DRI_EXT1_OFFSET, 1)) != RT_ERR_OK)
                return retVal;

            if ((retVal = rtl8367d_setAsicRegBit(unit, RTL8367D_REG_CHIP_DEBUG0, RTL8367D_SLR_EXT1_OFFSET, 1)) != RT_ERR_OK)
                return retVal;

            if ((retVal = rtl8367d_setAsicRegBits(unit, RTL8367D_REG_CHIP_DEBUG1, RTL8367D_RG1_DN_MASK, 7)) != RT_ERR_OK)
                return retVal;

            if ((retVal = rtl8367d_setAsicRegBits(unit, RTL8367D_REG_CHIP_DEBUG1, RTL8367D_RG1_DP_MASK, 5)) != RT_ERR_OK)
                return retVal;

            if ((retVal = rtl8367d_setAsicRegBits(unit, RTL8367D_REG_EXT_TXC_DLY, RTL8367D_EXT1_RGMII_TX_DELAY_MASK, 0)) != RT_ERR_OK)
                return retVal;

            if ((retVal = rtl8367d_setAsicRegBit(unit, RTL8367D_REG_TOP_CON0, RTL8367D_MAC7_SEL_EXT1_OFFSET, 1)) != RT_ERR_OK)
                return retVal;

            if ((retVal = rtl8367d_setAsicRegBits(unit, RTL8367D_REG_DIGITAL_INTERFACE_SELECT, RTL8367D_SELECT_GMII_1_MASK, mode)) != RT_ERR_OK)
                return retVal;
        }
        else if ((mode == RTKSW_MODE_EXT_SGMII) || (mode == RTKSW_MODE_EXT_HSGMII) || (mode == RTKSW_MODE_EXT_1000X_100FX) || (mode == RTKSW_MODE_EXT_1000X) || (mode == RTKSW_MODE_EXT_100FX) || (mode == RTKSW_MODE_EXT_FIBER_2P5G))
        {
            if ((retVal = rtl8367d_setAsicRegBit(unit, RTL8367D_REG_TOP_CON0, RTL8367D_MAC7_SEL_EXT1_OFFSET, 0)) != RT_ERR_OK)
                return retVal;

            switch (mode)
            {
                case RTKSW_MODE_EXT_SGMII:
                    for(i = 0; i < sizeof(SGCfg) / (sizeof(rtksw_uint32) * 2); i++)
                    {
                        if( (retVal = rtl8367d_setAsicReg(unit, RTL8367D_REG_SDS_INDACS_DATA, SGCfg[i][1])) != RT_ERR_OK)
                            return retVal;

                        if( (retVal = rtl8367d_setAsicReg(unit, RTL8367D_REG_SDS_INDACS_ADR, SGCfg[i][0])) != RT_ERR_OK)
                            return retVal;

                        if( (retVal = rtl8367d_setAsicReg(unit, RTL8367D_REG_SDS_INDACS_CMD, 0x00CF)) != RT_ERR_OK)
                            return retVal;
                    }

                    if ((retVal = rtl8367d_setAsicRegBits(unit, RTL8367D_REG_FIBER_CFG_2, RTL8367D_SDS_RX_DISABLE_MASK, 1)) != RT_ERR_OK)
                        return retVal;

                    if((retVal = rtl8367d_setAsicRegBit(unit, RTL8367D_REG_SDS1_MISC0, RTL8367D_PA12PC_EN_S1_OFFSET, 1)) != RT_ERR_OK)
                        return retVal;

                    if((retVal = rtl8367d_setAsicRegBit(unit, RTL8367D_REG_SDS1_MISC0, RTL8367D_PA33PC_EN_S1_OFFSET, 1)) != RT_ERR_OK)
                        return retVal;

                    if ((retVal = rtl8367d_setAsicRegBits(unit, RTL8367D_REG_SDS1_MISC0, RTL8367D_SDS1_MODE_MASK, RTL8367D_PORT_SDS_MODE_SGMII)) != RT_ERR_OK)
                        return retVal;

                    break;
                case RTKSW_MODE_EXT_HSGMII:
                    for(i = 0; i < sizeof(HSGCfg) / (sizeof(rtksw_uint32) * 2); i++)
                    {
                        if( (retVal = rtl8367d_setAsicReg(unit, RTL8367D_REG_SDS_INDACS_DATA, HSGCfg[i][1])) != RT_ERR_OK)
                            return retVal;

                        if( (retVal = rtl8367d_setAsicReg(unit, RTL8367D_REG_SDS_INDACS_ADR, HSGCfg[i][0])) != RT_ERR_OK)
                            return retVal;

                        if( (retVal = rtl8367d_setAsicReg(unit, RTL8367D_REG_SDS_INDACS_CMD, 0x00CF)) != RT_ERR_OK)
                            return retVal;
                    }

                    if ((retVal = rtl8367d_setAsicRegBits(unit, RTL8367D_REG_FIBER_CFG_2, RTL8367D_SDS_RX_DISABLE_MASK, 1)) != RT_ERR_OK)
                        return retVal;

                    if((retVal = rtl8367d_setAsicRegBit(unit, RTL8367D_REG_SDS1_MISC0, RTL8367D_PA12PC_EN_S1_OFFSET, 1)) != RT_ERR_OK)
                        return retVal;

                    if((retVal = rtl8367d_setAsicRegBit(unit, RTL8367D_REG_SDS1_MISC0, RTL8367D_PA33PC_EN_S1_OFFSET, 1)) != RT_ERR_OK)
                        return retVal;

                    if ((retVal = rtl8367d_setAsicRegBits(unit, RTL8367D_REG_SDS1_MISC0, RTL8367D_SDS1_MODE_MASK, RTL8367D_PORT_SDS_MODE_HSGMII)) != RT_ERR_OK)
                        return retVal;
                    break;
                case RTKSW_MODE_EXT_1000X_100FX:
                    for(i = 0; i < sizeof(Fiber1000M100MCfg) / (sizeof(rtksw_uint32) * 2); i++)
                    {
                        if( (retVal = rtl8367d_setAsicReg(unit, RTL8367D_REG_SDS_INDACS_DATA, Fiber1000M100MCfg[i][1])) != RT_ERR_OK)
                            return retVal;

                        if( (retVal = rtl8367d_setAsicReg(unit, RTL8367D_REG_SDS_INDACS_ADR, Fiber1000M100MCfg[i][0])) != RT_ERR_OK)
                            return retVal;

                        if( (retVal = rtl8367d_setAsicReg(unit, RTL8367D_REG_SDS_INDACS_CMD, 0x00CF)) != RT_ERR_OK)
                            return retVal;
                    }

                    if ((retVal = rtl8367d_setAsicRegBits(unit, RTL8367D_REG_FIBER_CFG_2, RTL8367D_SDS_RX_DISABLE_MASK, 1)) != RT_ERR_OK)
                        return retVal;

                    if( (retVal = rtl8367d_setAsicRegBit(unit, RTL8367D_REG_SDS1_MISC0, RTL8367D_PA12PC_EN_S1_OFFSET, 1)) != RT_ERR_OK)
                        return retVal;

                    if( (retVal = rtl8367d_setAsicRegBit(unit, RTL8367D_REG_SDS1_MISC0, RTL8367D_PA33PC_EN_S1_OFFSET, 1)) != RT_ERR_OK)
                        return retVal;

                    if( (retVal = rtl8367d_setAsicRegBits(unit, RTL8367D_REG_SDS1_MISC0, RTL8367D_SDS1_MODE_MASK, RTL8367D_PORT_SDS_MODE_1000X_100FX)) != RT_ERR_OK)
                        return retVal;

                    break;
                case RTKSW_MODE_EXT_1000X:
                    for(i = 0; i < sizeof(Fiber1000MCfg) / (sizeof(rtksw_uint32) * 2); i++)
                    {
                        if( (retVal = rtl8367d_setAsicReg(unit, RTL8367D_REG_SDS_INDACS_DATA, Fiber1000MCfg[i][1])) != RT_ERR_OK)
                            return retVal;

                        if( (retVal = rtl8367d_setAsicReg(unit, RTL8367D_REG_SDS_INDACS_ADR, Fiber1000MCfg[i][0])) != RT_ERR_OK)
                            return retVal;

                        if( (retVal = rtl8367d_setAsicReg(unit, RTL8367D_REG_SDS_INDACS_CMD, 0x00CF)) != RT_ERR_OK)
                            return retVal;
                    }

                    if ((retVal = rtl8367d_setAsicRegBits(unit, RTL8367D_REG_FIBER_CFG_2, RTL8367D_SDS_RX_DISABLE_MASK, 1)) != RT_ERR_OK)
                        return retVal;

                    if( (retVal = rtl8367d_setAsicRegBit(unit, RTL8367D_REG_SDS1_MISC0, RTL8367D_PA12PC_EN_S1_OFFSET, 1)) != RT_ERR_OK)
                        return retVal;

                    if( (retVal = rtl8367d_setAsicRegBit(unit, RTL8367D_REG_SDS1_MISC0, RTL8367D_PA33PC_EN_S1_OFFSET, 1)) != RT_ERR_OK)
                        return retVal;

                    if( (retVal = rtl8367d_setAsicRegBits(unit, RTL8367D_REG_SDS1_MISC0, RTL8367D_SDS1_MODE_MASK, RTL8367D_PORT_SDS_MODE_1000X)) != RT_ERR_OK)
                        return retVal;

                    break;
                case RTKSW_MODE_EXT_100FX:
                    for(i = 0; i < sizeof(Fiber100MCfg) / (sizeof(rtksw_uint32) * 2); i++)
                    {
                        if( (retVal = rtl8367d_setAsicReg(unit, RTL8367D_REG_SDS_INDACS_DATA, Fiber100MCfg[i][1])) != RT_ERR_OK)
                            return retVal;

                        if( (retVal = rtl8367d_setAsicReg(unit, RTL8367D_REG_SDS_INDACS_ADR, Fiber100MCfg[i][0])) != RT_ERR_OK)
                            return retVal;

                        if( (retVal = rtl8367d_setAsicReg(unit, RTL8367D_REG_SDS_INDACS_CMD, 0x00CF)) != RT_ERR_OK)
                            return retVal;
                    }

                    if ((retVal = rtl8367d_setAsicRegBits(unit, RTL8367D_REG_FIBER_CFG_2, RTL8367D_SDS_RX_DISABLE_MASK, 1)) != RT_ERR_OK)
                        return retVal;

                    if( (retVal = rtl8367d_setAsicRegBit(unit, RTL8367D_REG_SDS1_MISC0, RTL8367D_PA12PC_EN_S1_OFFSET, 1)) != RT_ERR_OK)
                        return retVal;

                    if( (retVal = rtl8367d_setAsicRegBit(unit, RTL8367D_REG_SDS1_MISC0, RTL8367D_PA33PC_EN_S1_OFFSET, 1)) != RT_ERR_OK)
                        return retVal;

                    if( (retVal = rtl8367d_setAsicRegBits(unit, RTL8367D_REG_SDS1_MISC0, RTL8367D_SDS1_MODE_MASK, RTL8367D_PORT_SDS_MODE_100FX)) != RT_ERR_OK)
                        return retVal;

                    break;
                case RTKSW_MODE_EXT_FIBER_2P5G:
                    for(i = 0; i < sizeof(Fiber2P5GCfg) / (sizeof(rtksw_uint32) * 2); i++)
                    {
                        if( (retVal = rtl8367d_setAsicReg(unit, RTL8367D_REG_SDS_INDACS_DATA, Fiber2P5GCfg[i][1])) != RT_ERR_OK)
                            return retVal;

                        if( (retVal = rtl8367d_setAsicReg(unit, RTL8367D_REG_SDS_INDACS_ADR, Fiber2P5GCfg[i][0])) != RT_ERR_OK)
                            return retVal;

                        if( (retVal = rtl8367d_setAsicReg(unit, RTL8367D_REG_SDS_INDACS_CMD, 0x00CF)) != RT_ERR_OK)
                            return retVal;
                    }

                    if ((retVal = rtl8367d_setAsicRegBits(unit, RTL8367D_REG_FIBER_CFG_2, RTL8367D_SDS_RX_DISABLE_MASK, 1)) != RT_ERR_OK)
                        return retVal;

                    if( (retVal = rtl8367d_setAsicRegBit(unit, RTL8367D_REG_SDS1_MISC0, RTL8367D_PA12PC_EN_S1_OFFSET, 1)) != RT_ERR_OK)
                        return retVal;

                    if( (retVal = rtl8367d_setAsicRegBit(unit, RTL8367D_REG_SDS1_MISC0, RTL8367D_PA33PC_EN_S1_OFFSET, 1)) != RT_ERR_OK)
                        return retVal;

                    if( (retVal = rtl8367d_setAsicRegBits(unit, RTL8367D_REG_SDS1_MISC0, RTL8367D_SDS1_MODE_MASK, RTL8367D_PORT_SDS_MODE_FIBER_2P5G)) != RT_ERR_OK)
                        return retVal;

                    break;
                default:
                    return RT_ERR_INPUT;
            }
        }
        else
            return RT_ERR_INPUT;
    }

    return RT_ERR_OK;
}

static rtksw_api_ret_t _rtl8367e_setAsicPortExtMode_ID1(rtksw_uint32 unit, rtksw_uint32 mode)
{
    rtksw_api_ret_t retVal;
    rtksw_uint32 idx;

    rtksw_uint32 sds0HSGMII[][2] = {{0x1d11, 0x0e1f}, {0x6602, 0x3930}, {0x6601, 0x0427}, {0x6600, 0x00cd}, {0x6602, 0x7280}, {0x6601, 0x0428}, {0x6600, 0x00cd}, {0x6602, 0x0519},
                                    {0x6601, 0x0504}, {0x6600, 0x00cd}, {0x6602, 0x5b60}, {0x6601, 0x0425}, {0x6600, 0x00cd}, {0x6602, 0x8416}, {0x6601, 0x0424}, {0x6600, 0x00cd},
                                    {0x6602, 0x1080}, {0x6601, 0x0422}, {0x6600, 0x00cd}, {0x6602, 0x074f}, {0x6601, 0x0004}, {0x6600, 0x00cd}, {0x13e8, 0x3040}, {0x1d11, 0x0e12}};
    rtksw_uint32 sds0SGMII[][2] =  {{0x1d11, 0x0e1f}, {0x6602, 0x393c}, {0x6601, 0x0427}, {0x6600, 0x00cd}, {0x6602, 0x3280}, {0x6601, 0x0428}, {0x6600, 0x00cd}, {0x6602, 0x00a1},
                                    {0x6601, 0x0484}, {0x6600, 0x00cd}, {0x6602, 0x5b60}, {0x6601, 0x0425}, {0x6600, 0x00cd}, {0x6602, 0x8416}, {0x6601, 0x0424}, {0x6600, 0x00cd},
                                    {0x6602, 0x1080}, {0x6601, 0x0422}, {0x6600, 0x00cd}, {0x6602, 0x074f}, {0x6601, 0x0004}, {0x6600, 0x00cd}, {0x13e8, 0x3040}, {0x1d11, 0x0e02}};
    rtksw_uint32 sds0Fiber1000x100fx[][2] =
                                   {{0x1d11, 0x0e1f}, {0x6602, 0x393c}, {0x6601, 0x0427}, {0x6600, 0x00cd}, {0x6602, 0x3280}, {0x6601, 0x0428}, {0x6600, 0x00cd}, {0x6602, 0x00a1},
                                    {0x6601, 0x0484}, {0x6600, 0x00cd}, {0x6602, 0x5b60}, {0x6601, 0x0425}, {0x6600, 0x00cd}, {0x6602, 0x8416}, {0x6601, 0x0424}, {0x6600, 0x00cd}, 
                                    {0x6602, 0x1080}, {0x6601, 0x0422}, {0x6600, 0x00cd}, {0x6602, 0x074f}, {0x6601, 0x0004}, {0x6600, 0x00cd}, {0x6602, 0x2100}, {0x6601, 0x0040}, 
                                    {0x6600, 0x00cd}, {0x6602, 0x0c01}, {0x6601, 0x0044}, {0x6600, 0x00cd}, {0x6602, 0x1140}, {0x6601, 0x0040}, {0x6600, 0x00cd}, {0x6602, 0x01a0}, 
                                    {0x6601, 0x0044}, {0x6600, 0x00cd}, {0x6602, 0x0f20}, {0x6601, 0x0001}, {0x6600, 0x00cd}, {0x13e8, 0x3040}, {0x1d11, 0x0e07}};
    rtksw_uint32 sds0Fiber1000x[][2] =
                                   {{0x1d11, 0x0e1f}, {0x6602, 0x393c}, {0x6601, 0x0427}, {0x6600, 0x00cd}, {0x6602, 0x3280}, {0x6601, 0x0428}, {0x6600, 0x00cd}, {0x6602, 0x00a1},
                                    {0x6601, 0x0484}, {0x6600, 0x00cd}, {0x6602, 0x5b60}, {0x6601, 0x0425}, {0x6600, 0x00cd}, {0x6602, 0x8416}, {0x6601, 0x0424}, {0x6600, 0x00cd},
                                    {0x6602, 0x1080}, {0x6601, 0x0422}, {0x6600, 0x00cd}, {0x6602, 0x074f}, {0x6601, 0x0004}, {0x6600, 0x00cd}, {0x6602, 0x1140}, {0x6601, 0x0040},
                                    {0x6600, 0x00cd}, {0x6602, 0x01a0}, {0x6601, 0x0044}, {0x6600, 0x00cd}, {0x13e8, 0x3040}, {0x1d11, 0x0e04}};
    rtksw_uint32 sds0Fiber100fx[][2] =
                                   {{0x1d11, 0x0e1f}, {0x6602, 0x393c}, {0x6601, 0x0427}, {0x6600, 0x00cd}, {0x6602, 0x3280}, {0x6601, 0x0428}, {0x6600, 0x00cd}, {0x6602, 0x00a1}, 
                                    {0x6601, 0x0484}, {0x6600, 0x00cd}, {0x6602, 0x5b60}, {0x6601, 0x0425}, {0x6600, 0x00cd}, {0x6602, 0x8416}, {0x6601, 0x0424}, {0x6600, 0x00cd}, 
                                    {0x6602, 0x1080}, {0x6601, 0x0422}, {0x6600, 0x00cd}, {0x6602, 0x074f}, {0x6601, 0x0004}, {0x6600, 0x00cd}, {0x6602, 0x01a0}, {0x6601, 0x0044}, 
                                    {0x6600, 0x00cd}, {0x13e8, 0x3040}, {0x1d11, 0x0e05}, {0x6602, 0xa100}, {0x6601, 0x0040}, {0x6600, 0x00cd}, {0x6602, 0x2100}, {0x6601, 0x0040}, 
                                    {0x6600, 0x00cd}};
    rtksw_uint32 sds0Fiber2p5g[][2] =
                                   {{0x1d11, 0x0e1f}, {0x6602, 0x3930}, {0x6601, 0x0427}, {0x6600, 0x00cd}, {0x6602, 0x7280}, {0x6601, 0x0428}, {0x6600, 0x00cd}, {0x6602, 0x0519}, 
                                    {0x6601, 0x0504}, {0x6600, 0x00cd}, {0x6602, 0x5b60}, {0x6601, 0x0425}, {0x6600, 0x00cd}, {0x6602, 0x8416}, {0x6601, 0x0424}, {0x6600, 0x00cd}, 
                                    {0x6602, 0x1080}, {0x6601, 0x0422}, {0x6600, 0x00cd}, {0x6602, 0x074f}, {0x6601, 0x0004}, {0x6600, 0x00cd}, {0x6602, 0x1140}, {0x6601, 0x0040}, 
                                    {0x6600, 0x00cd}, {0x6602, 0x01a0}, {0x6601, 0x0044}, {0x6600, 0x00cd}, {0x13e8, 0x3040}, {0x1d11, 0x0e16}};   
    
    if (mode == RTKSW_MODE_EXT_DISABLE)
    {
        if ((retVal = rtl8367d_setAsicReg(unit, 0x1d11, 0x001f)) != RT_ERR_OK)
            return retVal;
    }
    else if (mode == RTKSW_MODE_EXT_HSGMII)
    {
        for(idx = 0; idx < sizeof(sds0HSGMII) / (sizeof(rtksw_uint32) * 2); idx++)
        {
            if ((retVal = rtl8367d_setAsicReg(unit, sds0HSGMII[idx][0], sds0HSGMII[idx][1])) != RT_ERR_OK)
                return retVal;
        }
    }
    else if(mode == RTKSW_MODE_EXT_SGMII)
    {
        for(idx = 0; idx < sizeof(sds0SGMII) / (sizeof(rtksw_uint32) * 2); idx++)
        {
            if ((retVal = rtl8367d_setAsicReg(unit, sds0SGMII[idx][0], sds0SGMII[idx][1])) != RT_ERR_OK)
                return retVal;
        }
    }
    else if(mode == RTKSW_MODE_EXT_1000X_100FX)
    {
        for(idx = 0; idx < sizeof(sds0Fiber1000x100fx) / (sizeof(rtksw_uint32) * 2); idx++)
        {
            if ((retVal = rtl8367d_setAsicReg(unit, sds0Fiber1000x100fx[idx][0], sds0Fiber1000x100fx[idx][1])) != RT_ERR_OK)
                return retVal;
        }
    }
    else if(mode == RTKSW_MODE_EXT_1000X)
    {
        for(idx = 0; idx < sizeof(sds0Fiber1000x) / (sizeof(rtksw_uint32) * 2); idx++)
        {
            if ((retVal = rtl8367d_setAsicReg(unit, sds0Fiber1000x[idx][0], sds0Fiber1000x[idx][1])) != RT_ERR_OK)
                return retVal;
        }
    }
    else if(mode == RTKSW_MODE_EXT_100FX)
    {
        for(idx = 0; idx < sizeof(sds0Fiber100fx) / (sizeof(rtksw_uint32) * 2); idx++)
        {
            if ((retVal = rtl8367d_setAsicReg(unit, sds0Fiber100fx[idx][0], sds0Fiber100fx[idx][1])) != RT_ERR_OK)
                return retVal;
        }
    }
    else if(mode == RTKSW_MODE_EXT_FIBER_2P5G)
    {
        for(idx = 0; idx < sizeof(sds0Fiber2p5g) / (sizeof(rtksw_uint32) * 2); idx++)
        {
            if ((retVal = rtl8367d_setAsicReg(unit, sds0Fiber2p5g[idx][0], sds0Fiber2p5g[idx][1])) != RT_ERR_OK)
                return retVal;
        }
    }

    return RT_ERR_OK;
}

static rtksw_api_ret_t _rtl8367e_setAsicPortExtMode_ID2(rtksw_uint32 unit, rtksw_uint32 mode)
{
    rtksw_api_ret_t retVal;
    rtksw_uint32 idx;

    rtksw_uint32 sds1HSGMII[][2] = {{0x1d78, 0x061f}, {0x6602, 0x3930}, {0x6601, 0x0427}, {0x6600, 0x00cf}, {0x6602, 0x7280}, {0x6601, 0x0428}, {0x6600, 0x00cf}, {0x6602, 0x0519}, 
                                    {0x6601, 0x0504}, {0x6600, 0x00cf}, {0x6602, 0x5b60}, {0x6601, 0x0425}, {0x6600, 0x00cf}, {0x6602, 0x8416}, {0x6601, 0x0424}, {0x6600, 0x00cf}, 
                                    {0x6602, 0x1080}, {0x6601, 0x0422}, {0x6600, 0x00cf}, {0x6602, 0x074f}, {0x6601, 0x0004}, {0x6600, 0x00cf}, {0x13e8, 0x3040}, {0x1d78, 0x0612}};
    rtksw_uint32 sds1SGMII[][2] =  {{0x1d78, 0x061f}, {0x6602, 0x393c}, {0x6601, 0x0427}, {0x6600, 0x00cf}, {0x6602, 0x3280}, {0x6601, 0x0428}, {0x6600, 0x00cf}, {0x6602, 0x00a1}, 
                                    {0x6601, 0x0484}, {0x6600, 0x00cf}, {0x6602, 0x5b60}, {0x6601, 0x0425}, {0x6600, 0x00cf}, {0x6602, 0x8416}, {0x6601, 0x0424}, {0x6600, 0x00cf}, 
                                    {0x6602, 0x1080}, {0x6601, 0x0422}, {0x6600, 0x00cf}, {0x6602, 0x074f}, {0x6601, 0x0004}, {0x6600, 0x00cf}, {0x13e8, 0x3040}, {0x1d78, 0x0602}};
    rtksw_uint32 sds1Fiber1000x100fx[][2] =
                                   {{0x1d78, 0x061f}, {0x6602, 0x393c}, {0x6601, 0x0427}, {0x6600, 0x00cf}, {0x6602, 0x3280}, {0x6601, 0x0428}, {0x6600, 0x00cf}, {0x6602, 0x00a1}, 
                                    {0x6601, 0x0484}, {0x6600, 0x00cf}, {0x6602, 0x5b60}, {0x6601, 0x0425}, {0x6600, 0x00cf}, {0x6602, 0x8416}, {0x6601, 0x0424}, {0x6600, 0x00cf}, 
                                    {0x6602, 0x1080}, {0x6601, 0x0422}, {0x6600, 0x00cf}, {0x6602, 0x074f}, {0x6601, 0x0004}, {0x6600, 0x00cf}, {0x6602, 0x2100}, {0x6601, 0x0040}, 
                                    {0x6600, 0x00cf}, {0x6602, 0x0c01}, {0x6601, 0x0044}, {0x6600, 0x00cf}, {0x6602, 0x1140}, {0x6601, 0x0040}, {0x6600, 0x00cf}, {0x6602, 0x01a0}, 
                                    {0x6601, 0x0044}, {0x6600, 0x00cf}, {0x6602, 0x0f20}, {0x6601, 0x0001}, {0x6600, 0x00cf}, {0x13e8, 0x3040}, {0x1d78, 0x0607}};
    rtksw_uint32 sds1Fiber1000x[][2] =
                                   {{0x1d78, 0x061f}, {0x6602, 0x393c}, {0x6601, 0x0427}, {0x6600, 0x00cf}, {0x6602, 0x3280}, {0x6601, 0x0428}, {0x6600, 0x00cf}, {0x6602, 0x00a1},
                                    {0x6601, 0x0484}, {0x6600, 0x00cf}, {0x6602, 0x5b60}, {0x6601, 0x0425}, {0x6600, 0x00cf}, {0x6602, 0x8416}, {0x6601, 0x0424}, {0x6600, 0x00cf}, 
                                    {0x6602, 0x1080}, {0x6601, 0x0422}, {0x6600, 0x00cf}, {0x6602, 0x074f}, {0x6601, 0x0004}, {0x6600, 0x00cf}, {0x6602, 0x1140}, {0x6601, 0x0040}, 
                                    {0x6600, 0x00cf}, {0x6602, 0x01a0}, {0x6601, 0x0044}, {0x6600, 0x00cf}, {0x13e8, 0x3040}, {0x1d78, 0x0604}};
    rtksw_uint32 sds1Fiber100fx[][2] =
                                   {{0x1d78, 0x061f}, {0x6602, 0x393c}, {0x6601, 0x0427}, {0x6600, 0x00cf}, {0x6602, 0x3280}, {0x6601, 0x0428}, {0x6600, 0x00cf}, {0x6602, 0x00a1}, 
                                    {0x6601, 0x0484}, {0x6600, 0x00cf}, {0x6602, 0x5b60}, {0x6601, 0x0425}, {0x6600, 0x00cf}, {0x6602, 0x8416}, {0x6601, 0x0424}, {0x6600, 0x00cf}, 
                                    {0x6602, 0x1080}, {0x6601, 0x0422}, {0x6600, 0x00cf}, {0x6602, 0x074f}, {0x6601, 0x0004}, {0x6600, 0x00cf}, {0x6602, 0x01a0}, {0x6601, 0x0044}, 
                                    {0x6600, 0x00cf}, {0x13e8, 0x3040}, {0x1d78, 0x0605}, {0x6602, 0xa100}, {0x6601, 0x0040}, {0x6600, 0x00cf}, {0x6602, 0x2100}, {0x6601, 0x0040}, 
                                    {0x6600, 0x00cf}};
    rtksw_uint32 sds1Fiber2p5g[][2] =
                                   {{0x1d78, 0x061f}, {0x6602, 0x3930}, {0x6601, 0x0427}, {0x6600, 0x00cf}, {0x6602, 0x7280}, {0x6601, 0x0428}, {0x6600, 0x00cf}, {0x6602, 0x0519}, 
                                    {0x6601, 0x0504}, {0x6600, 0x00cf}, {0x6602, 0x5b60}, {0x6601, 0x0425}, {0x6600, 0x00cf}, {0x6602, 0x8416}, {0x6601, 0x0424}, {0x6600, 0x00cf}, 
                                    {0x6602, 0x1080}, {0x6601, 0x0422}, {0x6600, 0x00cf}, {0x6602, 0x074f}, {0x6601, 0x0004}, {0x6600, 0x00cf}, {0x6602, 0x1140}, {0x6601, 0x0040}, 
                                    {0x6600, 0x00cf}, {0x6602, 0x01a0}, {0x6601, 0x0044}, {0x6600, 0x00cf}, {0x13e8, 0x3040}, {0x1d78, 0x0616}};

    if (mode == RTKSW_MODE_EXT_DISABLE)
    {
        if ((retVal = rtl8367d_setAsicReg(unit, 0x1d78, 0x001f)) != RT_ERR_OK)
            return retVal;
    }
    else if (mode == RTKSW_MODE_EXT_HSGMII)
    {
        for(idx = 0; idx < sizeof(sds1HSGMII) / (sizeof(rtksw_uint32) * 2); idx++)
        {
            if ((retVal = rtl8367d_setAsicReg(unit, sds1HSGMII[idx][0], sds1HSGMII[idx][1])) != RT_ERR_OK)
                return retVal;
        }
    }
    else if(mode == RTKSW_MODE_EXT_SGMII)
    {
        for(idx = 0; idx < sizeof(sds1SGMII) / (sizeof(rtksw_uint32) * 2); idx++)
        {
            if ((retVal = rtl8367d_setAsicReg(unit, sds1SGMII[idx][0], sds1SGMII[idx][1])) != RT_ERR_OK)
                return retVal;
        }
    }
    else if(mode == RTKSW_MODE_EXT_1000X_100FX)
    {
        for(idx = 0; idx < sizeof(sds1Fiber1000x100fx) / (sizeof(rtksw_uint32) * 2); idx++)
        {
            if ((retVal = rtl8367d_setAsicReg(unit, sds1Fiber1000x100fx[idx][0], sds1Fiber1000x100fx[idx][1])) != RT_ERR_OK)
                return retVal;
        }
    }
    else if(mode == RTKSW_MODE_EXT_1000X)
    {
        for(idx = 0; idx < sizeof(sds1Fiber1000x) / (sizeof(rtksw_uint32) * 2); idx++)
        {
            if ((retVal = rtl8367d_setAsicReg(unit, sds1Fiber1000x[idx][0], sds1Fiber1000x[idx][1])) != RT_ERR_OK)
                return retVal;
        }
    }
    else if(mode == RTKSW_MODE_EXT_100FX)
    {
        for(idx = 0; idx < sizeof(sds1Fiber100fx) / (sizeof(rtksw_uint32) * 2); idx++)
        {
            if ((retVal = rtl8367d_setAsicReg(unit, sds1Fiber100fx[idx][0], sds1Fiber100fx[idx][1])) != RT_ERR_OK)
                return retVal;
        }
    }
    else if(mode == RTKSW_MODE_EXT_FIBER_2P5G)
    {
        for(idx = 0; idx < sizeof(sds1Fiber2p5g) / (sizeof(rtksw_uint32) * 2); idx++)
        {
            if ((retVal = rtl8367d_setAsicReg(unit, sds1Fiber2p5g[idx][0], sds1Fiber2p5g[idx][1])) != RT_ERR_OK)
                return retVal;
        }
    }

    return RT_ERR_OK;
}

static rtksw_api_ret_t _rtl8367e_setAsicPortExtMode(rtksw_uint32 unit, rtksw_uint32 id, rtksw_uint32 mode)
{
    rtksw_api_ret_t retVal;

    if ((mode != RTKSW_MODE_EXT_DISABLE) && (mode != RTKSW_MODE_EXT_SGMII) && (mode != RTKSW_MODE_EXT_HSGMII) && (mode != RTKSW_MODE_EXT_1000X_100FX) && (mode != RTKSW_MODE_EXT_1000X) && (mode != RTKSW_MODE_EXT_100FX) && (mode != RTKSW_MODE_EXT_FIBER_2P5G))
            return RT_ERR_INPUT;

    if (id == 1)
    {
        if ((retVal = _rtl8367e_setAsicPortExtMode_ID1(unit, mode)) != RT_ERR_OK)
            return retVal;
    }
    else if(id == 2)
    {
        if ((retVal = _rtl8367e_setAsicPortExtMode_ID2(unit, mode)) != RT_ERR_OK)
            return retVal;
    }
    else
        return RT_ERR_INPUT;

    return RT_ERR_OK;
}

static rtksw_api_ret_t _dal_rtl8367d_setAsicPortExtMode(rtksw_uint32 unit, rtksw_uint32 id, rtksw_uint32 mode)
{
    rtksw_api_ret_t retVal;

    switch (rtksw_switch_chipType_get(unit))
    {
        case CHIP_RTL8367D:
            if ((retVal = _rtl8367d_setAsicPortExtMode(unit, id, mode)) != RT_ERR_OK)
                return retVal;
            break;
        case CHIP_RTL8367E:
            if ((retVal = _rtl8367e_setAsicPortExtMode(unit, id, mode)) != RT_ERR_OK)
                return retVal;
            break;
        default:
            return RT_ERR_FAILED;
    }

    return RT_ERR_OK;
}

static rtksw_api_ret_t _rtl8367d_getAsicPortExtMode(rtksw_uint32 unit, rtksw_uint32 id, rtksw_uint32 *pMode)
{
    rtksw_api_ret_t retVal;
    rtksw_uint32 regData;

    switch (id)
    {
        case 1:
            if( (retVal = rtl8367d_getAsicRegBits(unit, RTL8367D_REG_SDS_MISC, RTL8367D_CFG_SDS_MODE_MASK, &regData)) != RT_ERR_OK)
                return retVal;
            break;
        case 2:
            if( (retVal = rtl8367d_getAsicRegBits(unit, RTL8367D_REG_SDS1_MISC0, RTL8367D_SDS1_MODE_MASK, &regData)) != RT_ERR_OK)
                return retVal;
            break;
        default:
            return RT_ERR_OUT_OF_RANGE;
    }

    switch (regData)
    {
        case RTL8367D_PORT_SDS_MODE_SGMII:
            *pMode = RTKSW_MODE_EXT_SGMII;
            break;
        case RTL8367D_PORT_SDS_MODE_HSGMII:
            *pMode = RTKSW_MODE_EXT_HSGMII;
            break;
        case RTL8367D_PORT_SDS_MODE_1000X:
            *pMode = RTKSW_MODE_EXT_1000X;
            break;
        case RTL8367D_PORT_SDS_MODE_100FX:
            *pMode = RTKSW_MODE_EXT_100FX;
            break;
        case RTL8367D_PORT_SDS_MODE_1000X_100FX:
            *pMode = RTKSW_MODE_EXT_1000X_100FX;
            break;
        case RTL8367D_PORT_SDS_MODE_FIBER_2P5G:
            *pMode = RTKSW_MODE_EXT_FIBER_2P5G;
            break;
        case RTL8367D_PORT_SDS_MODE_DISABLE:
            if(id == 2)
            {
                if ((retVal = rtl8367d_getAsicRegBits(unit, RTL8367D_REG_DIGITAL_INTERFACE_SELECT, RTL8367D_SELECT_GMII_1_MASK, pMode)) != RT_ERR_OK)
                    return retVal;
            }
            else
                *pMode = RTKSW_MODE_EXT_DISABLE;
            break;
        default:
            return RT_ERR_FAILED;
    }

    return RT_ERR_OK;
}

static rtksw_api_ret_t _rtl8367e_getAsicPortExtMode(rtksw_uint32 unit, rtksw_uint32 id, rtksw_uint32 *pMode)
{
    rtksw_api_ret_t retVal;
    rtksw_uint32 regData;

    switch (id)
    {
        case 1:
            if( (retVal = rtl8367d_getAsicRegBits(unit, RTL8367D_REG_SDS_MISC, RTL8367D_CFG_SDS_MODE_MASK, &regData)) != RT_ERR_OK)
                return retVal;
            break;
        case 2:
            if( (retVal = rtl8367d_getAsicRegBits(unit, RTL8367D_REG_SDS1_MISC0, RTL8367D_SDS1_MODE_MASK, &regData)) != RT_ERR_OK)
                return retVal;
            break;
        default:
            return RT_ERR_OUT_OF_RANGE;
    }

    switch (regData)
    {
        case RTL8367D_PORT_SDS_MODE_SGMII:
            *pMode = RTKSW_MODE_EXT_SGMII;
            break;
        case RTL8367D_PORT_SDS_MODE_HSGMII:
            *pMode = RTKSW_MODE_EXT_HSGMII;
            break;
        case RTL8367D_PORT_SDS_MODE_1000X:
            *pMode = RTKSW_MODE_EXT_1000X;
            break;
        case RTL8367D_PORT_SDS_MODE_100FX:
            *pMode = RTKSW_MODE_EXT_100FX;
            break;
        case RTL8367D_PORT_SDS_MODE_1000X_100FX:
            *pMode = RTKSW_MODE_EXT_1000X_100FX;
            break;
        case RTL8367D_PORT_SDS_MODE_FIBER_2P5G:
            *pMode = RTKSW_MODE_EXT_FIBER_2P5G;
            break;
        case RTL8367D_PORT_SDS_MODE_DISABLE:
            *pMode = RTKSW_MODE_EXT_DISABLE;
            break;
        default:
            return RT_ERR_FAILED;
    }

    return RT_ERR_OK;
}

static rtksw_api_ret_t _dal_rtl8367d_getAsicPortExtMode(rtksw_uint32 unit, rtksw_uint32 id, rtksw_uint32 *pMode)
{
    rtksw_api_ret_t retVal;

    switch (rtksw_switch_chipType_get(unit))
    {
        case CHIP_RTL8367D:
            if ((retVal = _rtl8367d_getAsicPortExtMode(unit, id, pMode)) != RT_ERR_OK)
                return retVal;
            break;
        case CHIP_RTL8367E:
            if ((retVal = _rtl8367e_getAsicPortExtMode(unit, id, pMode)) != RT_ERR_OK)
                return retVal;
            break;
        default:
            return RT_ERR_FAILED;
    }

    return RT_ERR_OK;
}

static rtksw_api_ret_t _dal_rtl8367d_port_sds_reset(rtksw_uint32 unit, rtksw_port_t port)
{
    rtksw_api_ret_t retVal;
    rtksw_uint32 serdesAddr;

    switch (port)
    {
        case EXT_PORT0:
            serdesAddr = 0x0D;
            break;
        case EXT_PORT1:
            serdesAddr = 0x0F;
            break;
        default:
            return RT_ERR_PORT_ID;
    }

    if ((retVal = rtl8367d_setAsicReg(unit, 0x6601, 0x0000)) != RT_ERR_OK)
        return retVal;

    if ((retVal = rtl8367d_setAsicReg(unit, 0x6602, 0x1401)) != RT_ERR_OK)
        return retVal;

    if ((retVal = rtl8367d_setAsicReg(unit, 0x6600, 0x00C0 | serdesAddr)) != RT_ERR_OK)
        return retVal;

    if ((retVal = rtl8367d_setAsicReg(unit, 0x6601, 0x0000)) != RT_ERR_OK)
        return retVal;

    if ((retVal = rtl8367d_setAsicReg(unit, 0x6602, 0x1403)) != RT_ERR_OK)
        return retVal;

    if ((retVal = rtl8367d_setAsicReg(unit, 0x6600, 0x00C0 | serdesAddr)) != RT_ERR_OK)
        return retVal;

    return RT_ERR_OK;
}

static rtksw_api_ret_t _dal_rtl8367d_port_sgmiiLinkStatus_get(rtksw_uint32 unit, rtksw_port_t port, rtksw_data_t *pSignalDetect, rtksw_data_t *pSync, rtksw_port_linkStatus_t *pLink)
{
    rtksw_api_ret_t retVal;
    rtksw_uint32 regValue;

    /* Check Port Valid */
    if(rtksw_switch_isSgmiiPort(unit, port) != RT_ERR_OK)
        return RT_ERR_PORT_ID;

    if(NULL == pSignalDetect)
        return RT_ERR_NULL_POINTER;

    if(NULL == pSync)
        return RT_ERR_NULL_POINTER;

    if(NULL == pLink)
        return RT_ERR_NULL_POINTER;

    switch (port)
    {
        case EXT_PORT0:
            if ((retVal = rtl8367d_setAsicReg(unit, 0x6601, 0x003D)) != RT_ERR_OK)
                break;

            if ((retVal = rtl8367d_setAsicReg(unit, 0x6600, 0x008D)) != RT_ERR_OK)
                break;

            if ((retVal = rtl8367d_getAsicReg(unit, 0x6602, &regValue)) != RT_ERR_OK)
                break;
            break;
        case EXT_PORT1:
            if ((retVal = rtl8367d_setAsicReg(unit, 0x6601, 0x003D)) != RT_ERR_OK)
                break;

            if ((retVal = rtl8367d_setAsicReg(unit, 0x6600, 0x008F)) != RT_ERR_OK)
                break;

            if ((retVal = rtl8367d_getAsicReg(unit, 0x6602, &regValue)) != RT_ERR_OK)
                break;
            break;
        default:
            retVal = RT_ERR_PORT_ID;
    }

    if (retVal == RT_ERR_OK)
    {
        *pSignalDetect = (regValue & 0x0100) ? 1 : 0;
        *pSync = (regValue & 0x0001) ? 1 : 0;
        *pLink = (regValue & 0x0010) ? 1 : 0;
    }

    return retVal;
}

static rtksw_api_ret_t _dal_rtl8367d_port_sgmiiNway_set(rtksw_uint32 unit, rtksw_port_t port, rtksw_enable_t state)
{
    rtksw_api_ret_t retVal;
    rtksw_uint32 regValue;
    rtksw_uint32 serdesAddr;

    /* Check Port Valid */
    if(rtksw_switch_isSgmiiPort(unit, port) != RT_ERR_OK)
        return RT_ERR_PORT_ID;

    if(state >= RTKSW_ENABLE_END)
        return RT_ERR_INPUT;

    switch (port)
    {
        case EXT_PORT0:
            serdesAddr = 0x0D;
            break;
        case EXT_PORT1:
            serdesAddr = 0x0F;
            break;
        default:
            return RT_ERR_PORT_ID;
    }

    if ((retVal = rtl8367d_setAsicReg(unit, 0x6601, 0x0002)) != RT_ERR_OK)
        return retVal;

    if ((retVal = rtl8367d_setAsicReg(unit, 0x6600, 0x0080 | serdesAddr)) != RT_ERR_OK)
        return retVal;

    if ((retVal = rtl8367d_getAsicReg(unit, 0x6602, &regValue)) != RT_ERR_OK)
        return retVal;

    if(state)
        regValue |= 0x0200;
    else
        regValue &= ~0x0200;

    regValue |= 0x0100;

    if ((retVal = rtl8367d_setAsicReg(unit, 0x6602, regValue)) != RT_ERR_OK)
        return retVal;

    if ((retVal = rtl8367d_setAsicReg(unit, 0x6601, 0x0002)) != RT_ERR_OK)
        return retVal;

    if ((retVal = rtl8367d_setAsicReg(unit, 0x6600, 0x00C0 | serdesAddr)) != RT_ERR_OK)
        return retVal;

    return RT_ERR_OK;
}

static rtksw_api_ret_t _dal_rtl8367d_port_sgmiiNway_get(rtksw_uint32 unit, rtksw_port_t port, rtksw_enable_t *pState)
{
    rtksw_api_ret_t retVal;
    rtksw_uint32 regValue;
    rtksw_uint32 serdesAddr;

    /* Check Port Valid */
    if(rtksw_switch_isSgmiiPort(unit, port) != RT_ERR_OK)
        return RT_ERR_PORT_ID;

    if(NULL == pState)
        return RT_ERR_NULL_POINTER;

    switch (port)
    {
        case EXT_PORT0:
            serdesAddr = 0x0D;
            break;
        case EXT_PORT1:
            serdesAddr = 0x0F;
            break;
        default:
            return RT_ERR_PORT_ID;
    }

    if ((retVal = rtl8367d_setAsicReg(unit, 0x6601, 0x0002)) != RT_ERR_OK)
        return retVal;

    if ((retVal = rtl8367d_setAsicReg(unit, 0x6600, 0x0080 | serdesAddr)) != RT_ERR_OK)
        return retVal;

    if ((retVal = rtl8367d_getAsicReg(unit, 0x6602, &regValue)) != RT_ERR_OK)
        return retVal;

    if((regValue & 0x0300) == 0x0300)
        *pState = RTKSW_ENABLED;
    else if((regValue & 0x0300) == 0x0000)
        *pState = RTKSW_ENABLED;
    else
        *pState = RTKSW_DISABLED;

    return RT_ERR_OK;
}

static rtksw_api_ret_t _dal_rtl8367d_port_fiberAbility_set(rtksw_uint32 unit, rtksw_port_t port, rtksw_port_fiber_ability_t *pAbility)
{
    rtksw_api_ret_t retVal;
    rtksw_port_media_t media_type;
    rtksw_mode_ext_t mode;
    rtksw_port_mac_ability_t portAbility;
    rtksw_uint32 regData;
    rtksw_uint32 sdsId;
    rtksw_uint32 i;

    /* Check Port Valid and the port is already configured to fiber mode*/
    if (port == UTP_PORT4)
    {
        if ((retVal = dal_rtl8367d_port_phyComboPortMedia_get(unit, port, &media_type)) != RT_ERR_OK)
            return retVal;

        if (media_type != RTKSW_PORT_MEDIA_FIBER)
            return RT_ERR_PORT_ID;

        sdsId = 0xD;
    }
    else if (port == EXT_PORT0)
    {
        if ((retVal = dal_rtl8367d_port_macForceLinkExt_get(unit, port, &mode, &portAbility)) != RT_ERR_OK)
            return retVal;

        if ((mode != RTKSW_MODE_EXT_1000X_100FX) && (mode != RTKSW_MODE_EXT_1000X) && (mode != RTKSW_MODE_EXT_100FX) && (mode != RTKSW_MODE_EXT_FIBER_2P5G))
            return RT_ERR_PORT_ID;

        sdsId = 0xD;
    }
    else if (port == EXT_PORT1)
    {
        if ((retVal = dal_rtl8367d_port_macForceLinkExt_get(unit, port, &mode, &portAbility)) != RT_ERR_OK)
            return retVal;

        if ((mode != RTKSW_MODE_EXT_1000X_100FX) && (mode != RTKSW_MODE_EXT_1000X) && (mode != RTKSW_MODE_EXT_100FX) && (mode != RTKSW_MODE_EXT_FIBER_2P5G))
            return RT_ERR_PORT_ID;

        sdsId = 0xF;
    }
    else
        return RT_ERR_PORT_ID;

    /* NULL pointer checking */
    if (pAbility == NULL)
        return RT_ERR_NULL_POINTER;

    /* UTP_PORT4 doesn't support 2.5G Fiber */
    if ((port == UTP_PORT4) && (pAbility->Full_2P5G == 1))
        return RT_ERR_PORT_ID;

    /* if 2.5G is set, all other speed should be cleared */
    if (pAbility->Full_2P5G == 1)
    {
        if ((pAbility->Full_1000 == 1) || (pAbility->Full_100 == 1))
            return RT_ERR_INPUT;
    }

    /* if Full_100 is the only speed set, AutoNegotiation & FC+AsyFC should be cleared */
    if ((pAbility->Full_100 == 1) && (pAbility->Full_1000 == 0) && (pAbility->Full_2P5G == 0))
    {
        if ((pAbility->AutoNegotiation == 1) || (pAbility->FC == 1) || (pAbility->AsyFC == 1))
            return RT_ERR_INPUT;
    }

    /* Speed ability & Flow Control */
    if (pAbility->Full_2P5G == 1)
    {
        for (i = 0; i < sizeof(Fiber2P5GCfg) / (sizeof(rtksw_uint32) * 2); i++)
        {
            regData = Fiber2P5GCfg[i][1];
            if (regData == 0x01A0)
            {
                if (pAbility->AsyFC == 0)
                    regData &= ~(0x0001 << 8);

                if (pAbility->FC == 0)
                    regData &= ~(0x0001 << 7);
            }

            if( (retVal = rtl8367d_setAsicReg(unit, RTL8367D_REG_SDS_INDACS_DATA, regData)) != RT_ERR_OK)
                return retVal;

            if( (retVal = rtl8367d_setAsicReg(unit, RTL8367D_REG_SDS_INDACS_ADR, Fiber2P5GCfg[i][0])) != RT_ERR_OK)
                return retVal;

            if( (retVal = rtl8367d_setAsicReg(unit, RTL8367D_REG_SDS_INDACS_CMD, (0x00C0 | sdsId))) != RT_ERR_OK)
                return retVal;
        }

        if (sdsId == 0xD)
        {
            if ((retVal = rtl8367d_setAsicRegBits(unit, RTL8367D_REG_SDS_MISC, RTL8367D_CFG_SDS_MODE_MASK, RTL8367D_PORT_SDS_MODE_FIBER_2P5G)) != RT_ERR_OK)
                return retVal;
        }
        else
        {
            if ((retVal = rtl8367d_setAsicRegBits(unit, RTL8367D_REG_SDS1_MISC0, RTL8367D_SDS1_MODE_MASK, RTL8367D_PORT_SDS_MODE_FIBER_2P5G)) != RT_ERR_OK)
                return retVal;
        }
    }
    else if ((pAbility->Full_1000 == 1) && (pAbility->Full_100 == 1))
    {
        for(i = 0; i < sizeof(Fiber1000M100MCfg) / (sizeof(rtksw_uint32) * 2); i++)
        {
            regData = Fiber1000M100MCfg[i][1];
            if (regData == 0x0C01)
            {
                if (pAbility->AsyFC == 0)
                    regData &= ~(0x0001 << 11);

                if (pAbility->FC == 0)
                    regData &= ~(0x0001 << 10);
            }

            if (regData == 0x01A0)
            {
                if (pAbility->AsyFC == 0)
                    regData &= ~(0x0001 << 8);

                if (pAbility->FC == 0)
                    regData &= ~(0x0001 << 7);
            }

            if( (retVal = rtl8367d_setAsicReg(unit, RTL8367D_REG_SDS_INDACS_DATA, regData)) != RT_ERR_OK)
                return retVal;

            if( (retVal = rtl8367d_setAsicReg(unit, RTL8367D_REG_SDS_INDACS_ADR, Fiber1000M100MCfg[i][0])) != RT_ERR_OK)
                return retVal;

            if( (retVal = rtl8367d_setAsicReg(unit, RTL8367D_REG_SDS_INDACS_CMD, (0x00C0 | sdsId))) != RT_ERR_OK)
                return retVal;
        }

        if (sdsId == 0xD)
        {
            if ((retVal = rtl8367d_setAsicRegBits(unit, RTL8367D_REG_SDS_MISC, RTL8367D_CFG_SDS_MODE_MASK, RTL8367D_PORT_SDS_MODE_1000X_100FX)) != RT_ERR_OK)
                return retVal;
        }
        else
        {
            if ((retVal = rtl8367d_setAsicRegBits(unit, RTL8367D_REG_SDS1_MISC0, RTL8367D_SDS1_MODE_MASK, RTL8367D_PORT_SDS_MODE_1000X_100FX)) != RT_ERR_OK)
                return retVal;
        }
    }
    else if(pAbility->Full_1000 == 1)
    {
        for(i = 0; i < sizeof(Fiber1000MCfg) / (sizeof(rtksw_uint32) * 2); i++)
        {
            regData = Fiber1000MCfg[i][1];
            if (regData == 0x01A0)
            {
                if (pAbility->AsyFC == 0)
                    regData &= ~(0x0001 << 8);

                if (pAbility->FC == 0)
                    regData &= ~(0x0001 << 7);
            }

            if( (retVal = rtl8367d_setAsicReg(unit, RTL8367D_REG_SDS_INDACS_DATA, regData)) != RT_ERR_OK)
                return retVal;

            if( (retVal = rtl8367d_setAsicReg(unit, RTL8367D_REG_SDS_INDACS_ADR, Fiber1000MCfg[i][0])) != RT_ERR_OK)
                return retVal;

            if( (retVal = rtl8367d_setAsicReg(unit, RTL8367D_REG_SDS_INDACS_CMD, (0x00C0 | sdsId))) != RT_ERR_OK)
                return retVal;
        }

        if (sdsId == 0xD)
        {
            if ((retVal = rtl8367d_setAsicRegBits(unit, RTL8367D_REG_SDS_MISC, RTL8367D_CFG_SDS_MODE_MASK, RTL8367D_PORT_SDS_MODE_1000X)) != RT_ERR_OK)
                return retVal;
        }
        else
        {
            if ((retVal = rtl8367d_setAsicRegBits(unit, RTL8367D_REG_SDS1_MISC0, RTL8367D_SDS1_MODE_MASK, RTL8367D_PORT_SDS_MODE_1000X)) != RT_ERR_OK)
                return retVal;
        }
    }
    else if(pAbility->Full_100 == 1)
    {
        for(i = 0; i < sizeof(Fiber100MCfg) / (sizeof(rtksw_uint32) * 2); i++)
        {
            regData = Fiber100MCfg[i][1];
            if (regData == 0x0C01)
            {
                if (pAbility->AsyFC == 0)
                    regData &= ~(0x0001 << 11);

                if (pAbility->FC == 0)
                    regData &= ~(0x0001 << 10);
            }

            if( (retVal = rtl8367d_setAsicReg(unit, RTL8367D_REG_SDS_INDACS_DATA, regData)) != RT_ERR_OK)
                return retVal;

            if( (retVal = rtl8367d_setAsicReg(unit, RTL8367D_REG_SDS_INDACS_ADR, Fiber100MCfg[i][0])) != RT_ERR_OK)
                return retVal;

            if( (retVal = rtl8367d_setAsicReg(unit, RTL8367D_REG_SDS_INDACS_CMD, (0x00C0 | sdsId))) != RT_ERR_OK)
                return retVal;
        }

        if (sdsId == 0xD)
        {
            if ((retVal = rtl8367d_setAsicRegBits(unit, RTL8367D_REG_SDS_MISC, RTL8367D_CFG_SDS_MODE_MASK, RTL8367D_PORT_SDS_MODE_100FX)) != RT_ERR_OK)
                return retVal;
        }
        else
        {
            if ((retVal = rtl8367d_setAsicRegBits(unit, RTL8367D_REG_SDS1_MISC0, RTL8367D_SDS1_MODE_MASK, RTL8367D_PORT_SDS_MODE_100FX)) != RT_ERR_OK)
                return retVal;
        }
    }

    /* Restart N-way & AutoNegotiation */
    if ((retVal = rtl8367d_setAsicReg(unit, RTL8367D_REG_SDS_INDACS_ADR, 0x0040)) != RT_ERR_OK)
        return retVal;

    if ((retVal = rtl8367d_setAsicReg(unit, RTL8367D_REG_SDS_INDACS_CMD, (0x0080 | sdsId))) != RT_ERR_OK)
        return retVal;

    if ((retVal = rtl8367d_getAsicReg(unit, RTL8367D_REG_SDS_INDACS_DATA, &regData)) != RT_ERR_OK)
        return retVal;

    /* AutoNegotiation */
    if (pAbility->AutoNegotiation == 1)
        regData |= (0x0001 << 12);
    else
        regData &= ~(0x0001 << 12);

    /* Restart N-way */
    regData |= (0x0001 << 9);

    if ((retVal = rtl8367d_setAsicReg(unit, RTL8367D_REG_SDS_INDACS_DATA, regData)) != RT_ERR_OK)
        return retVal;

    if ((retVal = rtl8367d_setAsicReg(unit, RTL8367D_REG_SDS_INDACS_ADR, 0x0040)) != RT_ERR_OK)
        return retVal;

    if ((retVal = rtl8367d_setAsicReg(unit, RTL8367D_REG_SDS_INDACS_CMD, (0x00C0 | sdsId))) != RT_ERR_OK)
        return retVal;

    return RT_ERR_OK;
}

static rtksw_api_ret_t _dal_rtl8367d_port_fiberAbility_get(rtksw_uint32 unit, rtksw_port_t port, rtksw_port_fiber_ability_t *pAbility)
{
    rtksw_api_ret_t retVal;
    rtksw_port_media_t media_type;
    rtksw_mode_ext_t mode;
    rtksw_port_mac_ability_t portAbility;
    rtksw_uint32 regData;
    rtksw_uint32 sdsId;
    rtksw_uint32 sdsMode;

    /* Check Port Valid and the port is already configured to fiber mode*/
    if (port == UTP_PORT4)
    {
        if ((retVal = dal_rtl8367d_port_phyComboPortMedia_get(unit, port, &media_type)) != RT_ERR_OK)
            return retVal;

        if (media_type != RTKSW_PORT_MEDIA_FIBER)
            return RT_ERR_PORT_ID;

        sdsId = 0xD;
    }
    else if (port == EXT_PORT0)
    {
        if ((retVal = dal_rtl8367d_port_macForceLinkExt_get(unit, port, &mode, &portAbility)) != RT_ERR_OK)
            return retVal;

        if ((mode != RTKSW_MODE_EXT_1000X_100FX) && (mode != RTKSW_MODE_EXT_1000X) && (mode != RTKSW_MODE_EXT_100FX) && (mode != RTKSW_MODE_EXT_FIBER_2P5G))
            return RT_ERR_PORT_ID;

        sdsId = 0xD;
    }
    else if (port == EXT_PORT1)
    {
        if ((retVal = dal_rtl8367d_port_macForceLinkExt_get(unit, port, &mode, &portAbility)) != RT_ERR_OK)
            return retVal;

        if ((mode != RTKSW_MODE_EXT_1000X_100FX) && (mode != RTKSW_MODE_EXT_1000X) && (mode != RTKSW_MODE_EXT_100FX) && (mode != RTKSW_MODE_EXT_FIBER_2P5G))
            return RT_ERR_PORT_ID;

        sdsId = 0xF;
    }
    else
        return RT_ERR_PORT_ID;

    /* NULL pointer checking */
    if (pAbility == NULL)
        return RT_ERR_NULL_POINTER;

    osal_memset(pAbility, 0x00, sizeof(rtksw_port_fiber_ability_t));

    /* Speed */
    if ((port == UTP_PORT4) || (port == EXT_PORT0))
    {
        if ((retVal = rtl8367d_getAsicRegBits(unit, RTL8367D_REG_SDS_MISC, RTL8367D_CFG_SDS_MODE_MASK, &sdsMode)) != RT_ERR_OK)
            return retVal;
    }
    else
    {
        if ((retVal = rtl8367d_getAsicRegBits(unit, RTL8367D_REG_SDS1_MISC0, RTL8367D_SDS1_MODE_MASK, &sdsMode)) != RT_ERR_OK)
            return retVal;
    }

    switch (sdsMode)
    {
        case RTL8367D_PORT_SDS_MODE_FIBER_2P5G:
            pAbility->Full_2P5G = 1;
            break;
        case RTL8367D_PORT_SDS_MODE_1000X_100FX:
            pAbility->Full_1000 = 1;
            pAbility->Full_100 = 1;
            break;
        case RTL8367D_PORT_SDS_MODE_1000X:
            pAbility->Full_1000 = 1;
            break;
        case RTL8367D_PORT_SDS_MODE_100FX:
            pAbility->Full_100 = 1;
            break;
        default:
            return RT_ERR_FAILED;
    }

    /* AutoNegotiation */
    if ((retVal = rtl8367d_setAsicReg(unit, RTL8367D_REG_SDS_INDACS_ADR, 0x0040)) != RT_ERR_OK)
        return retVal;

    if ((retVal = rtl8367d_setAsicReg(unit, RTL8367D_REG_SDS_INDACS_CMD, (0x0080 | sdsId))) != RT_ERR_OK)
        return retVal;

    if ((retVal = rtl8367d_getAsicReg(unit, RTL8367D_REG_SDS_INDACS_DATA, &regData)) != RT_ERR_OK)
        return retVal;

    if(regData & 0x1000)
        pAbility->AutoNegotiation = 1;
    else
        pAbility->AutoNegotiation = 0;

    /* Flow Control */
    if ((retVal = rtl8367d_setAsicReg(unit, RTL8367D_REG_SDS_INDACS_ADR, 0x0044)) != RT_ERR_OK)
        return retVal;

    if ((retVal = rtl8367d_setAsicReg(unit, RTL8367D_REG_SDS_INDACS_CMD, (0x0080 | sdsId))) != RT_ERR_OK)
        return retVal;

    if ((retVal = rtl8367d_getAsicReg(unit, RTL8367D_REG_SDS_INDACS_DATA, &regData)) != RT_ERR_OK)
        return retVal;

    if (sdsMode == RTL8367D_PORT_SDS_MODE_100FX)
    {
        if (regData & (0x0001 << 11))
            pAbility->AsyFC = 1;

        if(regData & (0x0001 << 10))
            pAbility->FC = 1;
    }
    else
    {
        if (regData & (0x0001 << 8))
            pAbility->AsyFC = 1;

        if(regData & (0x0001 << 7))
            pAbility->FC = 1;
    }

    return RT_ERR_OK;
}

static rtksw_api_ret_t _dal_rtl8367e_port_maxPacketLength_set(rtksw_uint32 unit, rtksw_port_t port, rtksw_uint32 length)
{
    rtksw_api_ret_t retVal;

    /* Check initialization state */
    RTKSW_CHK_INIT_STATE(unit);

    /* Check Port Valid */
    RTKSW_CHK_PORT_VALID(unit, port);

    if (length > RTL8367D_MAX_PACKET_LENGTH)
        return RT_ERR_INPUT;

    if ((retVal = rtl8367d_setAsicReg(unit, RTL8367D_REG_PORT0_PKTMAXLEN + (rtksw_switch_port_L2P_get(unit, port) * 0x20), length)) != RT_ERR_OK)
        return retVal;

    return RT_ERR_OK;
}

static rtksw_api_ret_t _dal_rtl8367e_port_maxPacketLength_get(rtksw_uint32 unit, rtksw_port_t port, rtksw_uint32 *pLength)
{
    rtksw_api_ret_t retVal;
    
    /* Check initialization state */
    RTKSW_CHK_INIT_STATE(unit);

    /* Check Port Valid */
    RTKSW_CHK_PORT_VALID(unit, port);

    if (pLength == NULL)
        return RT_ERR_NULL_POINTER;

    if ((retVal = rtl8367d_getAsicReg(unit, RTL8367D_REG_PORT0_PKTMAXLEN + (rtksw_switch_port_L2P_get(unit, port) * 0x20), pLength)) != RT_ERR_OK)
        return retVal;

    return RT_ERR_OK;
}

static rtksw_api_ret_t _dal_rtl8367d_port_rtctEnable_set(rtksw_uint32 unit, rtksw_portmask_t *pPortmask)
{
    rtksw_api_ret_t retVal;
    rtksw_port_t port;
    rtksw_uint32 regData;
    rtksw_uint32 i;

    /* Check initialization state */
    RTKSW_CHK_INIT_STATE(unit);

    /* Check Port Mask Valid */
    RTKSW_CHK_PORTMASK_VALID_ONLY_UTP(unit, pPortmask);

    RTKSW_PORTMASK_SCAN((*pPortmask), port)
    {
        /* Initialize RTCT */
        for(i = 0; i < sizeof(RTCTPatch) / (sizeof(rtksw_uint32) * 2); i++)
        {
            if( (retVal = dal_rtl8367d_port_phyOCPReg_set(unit, port, RTCTPatch[i][0], RTCTPatch[i][1])) != RT_ERR_OK)
                return retVal;
        }

        regData = 0x00F2; /*RTCT set to echo response mode*/
        if((retVal = dal_rtl8367d_port_phyOCPReg_set(unit, port, 0xa422, regData)) != RT_ERR_OK)
            return retVal;

        regData = 0x00F3;
        if((retVal = dal_rtl8367d_port_phyOCPReg_set(unit, port, 0xa422, regData)) != RT_ERR_OK)
            return retVal;
    }

    return RT_ERR_OK;
}

static rtksw_api_ret_t _dal_rtl8367e_port_rtctEnable_set(rtksw_uint32 unit, rtksw_portmask_t *pPortmask)
{
    rtksw_api_ret_t retVal;
    rtksw_port_t port;
    rtksw_uint32 regData;

    /* Check initialization state */
    RTKSW_CHK_INIT_STATE(unit);

    /* Check Port Mask Valid */
    RTKSW_CHK_PORTMASK_VALID_ONLY_UTP(unit, pPortmask);

    RTKSW_PORTMASK_SCAN((*pPortmask), port)
    {
        /* Initialize RTCT */
        /* 0xA468[1:0] = 0x1 */
        if((retVal = dal_rtl8367d_port_phyOCPReg_get(unit, port, 0xA468, &regData)) != RT_ERR_OK)
            return retVal;
        
        regData &= ~0x0003;
        regData |= 0x1;
        if((retVal = dal_rtl8367d_port_phyOCPReg_set(unit, port, 0xA468, regData)) != RT_ERR_OK)
            return retVal;

        /* 0xA422[0] = 0x0 */
        if((retVal = dal_rtl8367d_port_phyOCPReg_get(unit, port, 0xA422, &regData)) != RT_ERR_OK)
            return retVal;
        
        regData &= ~0x0001;
        if((retVal = dal_rtl8367d_port_phyOCPReg_set(unit, port, 0xA422, regData)) != RT_ERR_OK)
            return retVal;

        /* 0xC010[10:9] = 0x2 */
        if((retVal = dal_rtl8367d_port_phyOCPReg_get(unit, port, 0xC010, &regData)) != RT_ERR_OK)
            return retVal;
        
        regData &= ~0x0600;
        regData |= 0x0400;
        if((retVal = dal_rtl8367d_port_phyOCPReg_set(unit, port, 0xC010, regData)) != RT_ERR_OK)
            return retVal;

        /* 0xC010[14:12] = 0x1 */
        if((retVal = dal_rtl8367d_port_phyOCPReg_get(unit, port, 0xC010, &regData)) != RT_ERR_OK)
            return retVal;
        
        regData &= ~0x7000;
        regData |= 0x1000;
        if((retVal = dal_rtl8367d_port_phyOCPReg_set(unit, port, 0xC010, regData)) != RT_ERR_OK)
            return retVal;

        /* 0xC000[0] = 0x0 */
        if((retVal = dal_rtl8367d_port_phyOCPReg_get(unit, port, 0xC000, &regData)) != RT_ERR_OK)
            return retVal;
        
        regData &= ~0x0001;
        if((retVal = dal_rtl8367d_port_phyOCPReg_set(unit, port, 0xC000, regData)) != RT_ERR_OK)
            return retVal;

        /* 0xC020[3:0] = 0x1 */
        if((retVal = dal_rtl8367d_port_phyOCPReg_get(unit, port, 0xC020, &regData)) != RT_ERR_OK)
            return retVal;
        
        regData &= ~0x000F;
        regData |= 0x0001;
        if((retVal = dal_rtl8367d_port_phyOCPReg_set(unit, port, 0xC020, regData)) != RT_ERR_OK)
            return retVal;

        /* 0xA422[1] = 0x1 */
        if((retVal = dal_rtl8367d_port_phyOCPReg_get(unit, port, 0xA422, &regData)) != RT_ERR_OK)
            return retVal;
        
        regData |= 0x0002;
        if((retVal = dal_rtl8367d_port_phyOCPReg_set(unit, port, 0xA422, regData)) != RT_ERR_OK)
            return retVal;

        /* 0xA422[7:4] = 0xF */
        if((retVal = dal_rtl8367d_port_phyOCPReg_get(unit, port, 0xA422, &regData)) != RT_ERR_OK)
            return retVal;
        
        regData |= 0x00F0;
        if((retVal = dal_rtl8367d_port_phyOCPReg_set(unit, port, 0xA422, regData)) != RT_ERR_OK)
            return retVal;
        
        /* 0xA436[15:0] = 0x81C7 */
        if((retVal = dal_rtl8367d_port_phyOCPReg_set(unit, port, 0xA436, 0x81C7)) != RT_ERR_OK)
            return retVal;

        /* 0xA438[15:0] = 0x1001 */
        if((retVal = dal_rtl8367d_port_phyOCPReg_set(unit, port, 0xA438, 0x1001)) != RT_ERR_OK)
            return retVal;

        /* 0xA438[15:0] = 0x0041 */
        if((retVal = dal_rtl8367d_port_phyOCPReg_set(unit, port, 0xA438, 0x0041)) != RT_ERR_OK)
            return retVal;

        /* 0xA438[15:0] = 0x84ED */
        if((retVal = dal_rtl8367d_port_phyOCPReg_set(unit, port, 0xA438, 0x84ED)) != RT_ERR_OK)
            return retVal;

        /* 0xA438[15:0] = 0x6A01 */
        if((retVal = dal_rtl8367d_port_phyOCPReg_set(unit, port, 0xA438, 0x6A01)) != RT_ERR_OK)
            return retVal;

        /* 0xA438[15:0] = 0x00F8 */
        if((retVal = dal_rtl8367d_port_phyOCPReg_set(unit, port, 0xA438, 0x00F8)) != RT_ERR_OK)
            return retVal;

        /* 0xA438[15:0] = 0xCE00 */
        if((retVal = dal_rtl8367d_port_phyOCPReg_set(unit, port, 0xA438, 0xCE00)) != RT_ERR_OK)
            return retVal;

        /* 0xA438[15:0] = 0x002E */
        if((retVal = dal_rtl8367d_port_phyOCPReg_set(unit, port, 0xA438, 0x002E)) != RT_ERR_OK)
            return retVal;

        /* 0xA438[15:0] = 0x8010 */
        if((retVal = dal_rtl8367d_port_phyOCPReg_set(unit, port, 0xA438, 0x8010)) != RT_ERR_OK)
            return retVal;

        /* 0xA438[15:0] = 0x0 */
        if((retVal = dal_rtl8367d_port_phyOCPReg_set(unit, port, 0xA438, 0x0000)) != RT_ERR_OK)
            return retVal;

        /* 0xA438[15:0] = 0x0 */
        if((retVal = dal_rtl8367d_port_phyOCPReg_set(unit, port, 0xA438, 0x0000)) != RT_ERR_OK)
            return retVal;

        /* 0xA438[15:0] = 0x0 */
        if((retVal = dal_rtl8367d_port_phyOCPReg_set(unit, port, 0xA438, 0x0000)) != RT_ERR_OK)
            return retVal;

        /* 0xA438[15:0] = 0x0 */
        if((retVal = dal_rtl8367d_port_phyOCPReg_set(unit, port, 0xA438, 0x0000)) != RT_ERR_OK)
            return retVal;

        /* 0xA438[15:0] = 0x0 */
        if((retVal = dal_rtl8367d_port_phyOCPReg_set(unit, port, 0xA438, 0x0000)) != RT_ERR_OK)
            return retVal;

        /* 0xA436[15:0] = 0x82D2 */
        if((retVal = dal_rtl8367d_port_phyOCPReg_set(unit, port, 0xA436, 0x82D2)) != RT_ERR_OK)
            return retVal;

        /* 0xA438[15:0] = 0x0 */
        if((retVal = dal_rtl8367d_port_phyOCPReg_set(unit, port, 0xA438, 0x0000)) != RT_ERR_OK)
            return retVal;

        /* 0xA438[15:8] = 0x0 */
        if((retVal = dal_rtl8367d_port_phyOCPReg_get(unit, port, 0xA438, &regData)) != RT_ERR_OK)
            return retVal;
        
        regData &= ~0xFF00;
         if((retVal = dal_rtl8367d_port_phyOCPReg_set(unit, port, 0xA438, regData)) != RT_ERR_OK)
            return retVal;

        /* Run */
        /* 0xA46A[1] = 0x1 */
        if((retVal = dal_rtl8367d_port_phyOCPReg_get(unit, port, 0xA46A, &regData)) != RT_ERR_OK)
            return retVal;
        
        regData |= 0x0002;
         if((retVal = dal_rtl8367d_port_phyOCPReg_set(unit, port, 0xA46A, regData)) != RT_ERR_OK)
            return retVal;
        
        /* 0xA422[15:0] = 0xF3 */
        if((retVal = dal_rtl8367d_port_phyOCPReg_set(unit, port, 0xA422, 0x00F3)) != RT_ERR_OK)
            return retVal;
    }

    return RT_ERR_OK;
}

static rtksw_api_ret_t _dal_rtl8367d_port_rtctDisable_set(rtksw_uint32 unit, rtksw_portmask_t *pPortmask)
{
    rtksw_api_ret_t retVal;
    rtksw_port_t port;
    rtksw_uint32 regData;

    /* Check initialization state */
    RTKSW_CHK_INIT_STATE(unit);

    /* Check Port Mask Valid */
    RTKSW_CHK_PORTMASK_VALID_ONLY_UTP(unit, pPortmask);

    RTKSW_PORTMASK_SCAN((*pPortmask), port)
    {
        if((retVal = dal_rtl8367d_port_phyOCPReg_get(unit, port, 0xa422, &regData)) != RT_ERR_OK)
             return retVal;

         regData &= 0x7FFF;
         if((retVal = dal_rtl8367d_port_phyOCPReg_set(unit, port, 0xa422, regData)) != RT_ERR_OK)
             return retVal;

         regData |= 0x00F0;
         if((retVal = dal_rtl8367d_port_phyOCPReg_set(unit, port, 0xa422, regData)) != RT_ERR_OK)
             return retVal;

         regData &= ~0x0001;
         if((retVal = dal_rtl8367d_port_phyOCPReg_set(unit, port, 0xa422, regData)) != RT_ERR_OK)
             return retVal;
    }

    return RT_ERR_OK;
}

static rtksw_api_ret_t _dal_rtl8367d_port_rtctResult_get(rtksw_uint32 unit, rtksw_port_t port, rtksw_rtctResult_t *pRtctResult)
{
    rtksw_api_ret_t retVal;
    rtksw_uint32 regData, finish = 1;

    /* Check initialization state */
    RTKSW_CHK_INIT_STATE(unit);

    /* Check Port Valid */
    RTKSW_CHK_PORT_IS_UTP(unit, port);

    if((retVal = dal_rtl8367d_port_phyOCPReg_get(unit, port, 0xa422, &regData)) != RT_ERR_OK)
        return retVal;

    if((regData & 0x8000) == 0x8000)
    {
        /* Channel A */
        if((retVal = dal_rtl8367d_port_phyOCPReg_set(unit, port, 0xa436, 0x802b)) != RT_ERR_OK)
            return retVal;

        if((retVal = dal_rtl8367d_port_phyOCPReg_get(unit, port, 0xa438, &regData)) != RT_ERR_OK)
            return retVal;

        pRtctResult->result.ge_result.channelAOpen       = (regData == 0x0048) ? 1 : 0;
        pRtctResult->result.ge_result.channelAShort      = (regData == 0x0050) ? 1 : 0;
        pRtctResult->result.ge_result.channelAMismatch   = ((regData == 0x0042) || (regData == 0x0044)) ? 1 : 0;
        pRtctResult->result.ge_result.channelALinedriver = (regData == 0x0041) ? 1 : 0;

        /* Channel B */
        if((retVal = dal_rtl8367d_port_phyOCPReg_set(unit, port, 0xa436, 0x802f)) != RT_ERR_OK)
            return retVal;

        if((retVal = dal_rtl8367d_port_phyOCPReg_get(unit, port, 0xa438, &regData)) != RT_ERR_OK)
            return retVal;

        pRtctResult->result.ge_result.channelBOpen       = (regData == 0x0048) ? 1 : 0;
        pRtctResult->result.ge_result.channelBShort      = (regData == 0x0050) ? 1 : 0;
        pRtctResult->result.ge_result.channelBMismatch   = ((regData == 0x0042) || (regData == 0x0044)) ? 1 : 0;
        pRtctResult->result.ge_result.channelBLinedriver = (regData == 0x0041) ? 1 : 0;

        /* Channel C */
        if((retVal = dal_rtl8367d_port_phyOCPReg_set(unit, port, 0xa436, 0x8033)) != RT_ERR_OK)
            return retVal;

        if((retVal = dal_rtl8367d_port_phyOCPReg_get(unit, port, 0xa438, &regData)) != RT_ERR_OK)
            return retVal;

        pRtctResult->result.ge_result.channelCOpen       = (regData == 0x0048) ? 1 : 0;
        pRtctResult->result.ge_result.channelCShort      = (regData == 0x0050) ? 1 : 0;
        pRtctResult->result.ge_result.channelCMismatch   = ((regData == 0x0042) || (regData == 0x0044)) ? 1 : 0;
        pRtctResult->result.ge_result.channelCLinedriver = (regData == 0x0041) ? 1 : 0;

        /* Channel D */
        if((retVal = dal_rtl8367d_port_phyOCPReg_set(unit, port, 0xa436, 0x8037)) != RT_ERR_OK)
            return retVal;

        if((retVal = dal_rtl8367d_port_phyOCPReg_get(unit, port, 0xa438, &regData)) != RT_ERR_OK)
            return retVal;

        pRtctResult->result.ge_result.channelDOpen       = (regData == 0x0048) ? 1 : 0;
        pRtctResult->result.ge_result.channelDShort      = (regData == 0x0050) ? 1 : 0;
        pRtctResult->result.ge_result.channelDMismatch   = ((regData == 0x0042) || (regData == 0x0044)) ? 1 : 0;
        pRtctResult->result.ge_result.channelDLinedriver = (regData == 0x0041) ? 1 : 0;

        /* Channel A Length */
        if((retVal = dal_rtl8367d_port_phyOCPReg_set(unit, port, 0xa436, 0x802d)) != RT_ERR_OK)
            return retVal;

        if((retVal = dal_rtl8367d_port_phyOCPReg_get(unit, port, 0xa438, &regData)) != RT_ERR_OK)
            return retVal;

       pRtctResult->result.ge_result.channelALen = (regData / 2);

        /* Channel B Length */
        if((retVal = dal_rtl8367d_port_phyOCPReg_set(unit, port, 0xa436, 0x8031)) != RT_ERR_OK)
            return retVal;

        if((retVal = dal_rtl8367d_port_phyOCPReg_get(unit, port, 0xa438, &regData)) != RT_ERR_OK)
            return retVal;

        pRtctResult->result.ge_result.channelBLen = (regData / 2);

        /* Channel C Length */
        if((retVal = dal_rtl8367d_port_phyOCPReg_set(unit, port, 0xa436, 0x8035)) != RT_ERR_OK)
            return retVal;

        if((retVal = dal_rtl8367d_port_phyOCPReg_get(unit, port, 0xa438, &regData)) != RT_ERR_OK)
            return retVal;

        pRtctResult->result.ge_result.channelCLen = (regData / 2);

        /* Channel D Length */
        if((retVal = dal_rtl8367d_port_phyOCPReg_set(unit, port, 0xa436, 0x8039)) != RT_ERR_OK)
            return retVal;

        if((retVal = dal_rtl8367d_port_phyOCPReg_get(unit, port, 0xa438, &regData)) != RT_ERR_OK)
            return retVal;

        pRtctResult->result.ge_result.channelDLen = (regData / 2);
    }
    else
        finish = 0;

    if(finish == 0)
        return RT_ERR_PHY_RTCT_NOT_FINISH;
    else
        return RT_ERR_OK;
}

static rtksw_api_ret_t _dal_rtl8367e_port_rtctResult_get(rtksw_uint32 unit, rtksw_port_t port, rtksw_rtctResult_t *pRtctResult)
{
    rtksw_api_ret_t retVal;
    rtksw_uint32 regData, finish = 1;

    /* Check initialization state */
    RTKSW_CHK_INIT_STATE(unit);

    /* Check Port Valid */
    RTKSW_CHK_PORT_IS_UTP(unit, port);

    if((retVal = dal_rtl8367d_port_phyOCPReg_get(unit, port, 0xa422, &regData)) != RT_ERR_OK)
        return retVal;

    if((regData & 0x8000) == 0x8000)
    {
        /* Channel A */
        if((retVal = dal_rtl8367d_port_phyOCPReg_set(unit, port, 0xa436, 0x802e)) != RT_ERR_OK)
            return retVal;

        if((retVal = dal_rtl8367d_port_phyOCPReg_get(unit, port, 0xa438, &regData)) != RT_ERR_OK)
            return retVal;

        regData = regData >> 8;
        pRtctResult->result.ge_result.channelAOpen       = (regData == 0x0048) ? 1 : 0;
        pRtctResult->result.ge_result.channelAShort      = (regData == 0x0050) ? 1 : 0;
        pRtctResult->result.ge_result.channelAMismatch   = ((regData == 0x0042) || (regData == 0x0044)) ? 1 : 0;
        pRtctResult->result.ge_result.channelALinedriver = 0;

        /* Channel B */
        if((retVal = dal_rtl8367d_port_phyOCPReg_set(unit, port, 0xa436, 0x8032)) != RT_ERR_OK)
            return retVal;

        if((retVal = dal_rtl8367d_port_phyOCPReg_get(unit, port, 0xa438, &regData)) != RT_ERR_OK)
            return retVal;

        regData = regData >> 8;
        pRtctResult->result.ge_result.channelBOpen       = (regData == 0x0048) ? 1 : 0;
        pRtctResult->result.ge_result.channelBShort      = (regData == 0x0050) ? 1 : 0;
        pRtctResult->result.ge_result.channelBMismatch   = ((regData == 0x0042) || (regData == 0x0044)) ? 1 : 0;
        pRtctResult->result.ge_result.channelBLinedriver = 0;

        /* Channel C */
        if((retVal = dal_rtl8367d_port_phyOCPReg_set(unit, port, 0xa436, 0x8036)) != RT_ERR_OK)
            return retVal;

        if((retVal = dal_rtl8367d_port_phyOCPReg_get(unit, port, 0xa438, &regData)) != RT_ERR_OK)
            return retVal;

        regData = regData >> 8;
        pRtctResult->result.ge_result.channelCOpen       = (regData == 0x0048) ? 1 : 0;
        pRtctResult->result.ge_result.channelCShort      = (regData == 0x0050) ? 1 : 0;
        pRtctResult->result.ge_result.channelCMismatch   = ((regData == 0x0042) || (regData == 0x0044)) ? 1 : 0;
        pRtctResult->result.ge_result.channelCLinedriver = 0;

        /* Channel D */
        if((retVal = dal_rtl8367d_port_phyOCPReg_set(unit, port, 0xa436, 0x803A)) != RT_ERR_OK)
            return retVal;

        if((retVal = dal_rtl8367d_port_phyOCPReg_get(unit, port, 0xa438, &regData)) != RT_ERR_OK)
            return retVal;

        regData = regData >> 8;
        pRtctResult->result.ge_result.channelDOpen       = (regData == 0x0048) ? 1 : 0;
        pRtctResult->result.ge_result.channelDShort      = (regData == 0x0050) ? 1 : 0;
        pRtctResult->result.ge_result.channelDMismatch   = ((regData == 0x0042) || (regData == 0x0044)) ? 1 : 0;
        pRtctResult->result.ge_result.channelDLinedriver = 0;

        /* Channel A Length */
        if((retVal = dal_rtl8367d_port_phyOCPReg_set(unit, port, 0xa436, 0x802f)) != RT_ERR_OK)
            return retVal;

        if((retVal = dal_rtl8367d_port_phyOCPReg_get(unit, port, 0xa438, &regData)) != RT_ERR_OK)
            return retVal;

       pRtctResult->result.ge_result.channelALen = (regData >= 120) ? (regData - 120) * 40 * 10 / 768 : 0;

        /* Channel B Length */
        if((retVal = dal_rtl8367d_port_phyOCPReg_set(unit, port, 0xa436, 0x8033)) != RT_ERR_OK)
            return retVal;

        if((retVal = dal_rtl8367d_port_phyOCPReg_get(unit, port, 0xa438, &regData)) != RT_ERR_OK)
            return retVal;

        pRtctResult->result.ge_result.channelBLen = (regData >= 120) ? (regData - 120) * 40 * 10 / 768 : 0;

        /* Channel C Length */
        if((retVal = dal_rtl8367d_port_phyOCPReg_set(unit, port, 0xa436, 0x8037)) != RT_ERR_OK)
            return retVal;

        if((retVal = dal_rtl8367d_port_phyOCPReg_get(unit, port, 0xa438, &regData)) != RT_ERR_OK)
            return retVal;

        pRtctResult->result.ge_result.channelCLen = (regData >= 120) ? (regData - 120) * 40 * 10 / 768 : 0;

        /* Channel D Length */
        if((retVal = dal_rtl8367d_port_phyOCPReg_set(unit, port, 0xa436, 0x803b)) != RT_ERR_OK)
            return retVal;

        if((retVal = dal_rtl8367d_port_phyOCPReg_get(unit, port, 0xa438, &regData)) != RT_ERR_OK)
            return retVal;

        pRtctResult->result.ge_result.channelDLen = (regData >= 120) ? (regData - 120) * 40 * 10 / 768 : 0;
    }
    else
        finish = 0;

    if(finish == 0)
        return RT_ERR_PHY_RTCT_NOT_FINISH;
    else
        return RT_ERR_OK;
}

/* Function Name:
 *      dal_rtl8367d_port_phyAutoNegoAbility_set
 * Description:
 *      Set ethernet PHY auto-negotiation desired ability.
 * Input:
 *      unit        - Unit ID
 *      port        - port id.
 *      pAbility    - Ability structure
 * Output:
 *      None
 * Return:
 *      RT_ERR_OK               - OK
 *      RT_ERR_FAILED           - Failed
 *      RT_ERR_SMI              - SMI access error
 *      RT_ERR_PORT_ID          - Invalid port number.
 *      RT_ERR_PHY_REG_ID       - Invalid PHY address
 *      RT_ERR_INPUT            - Invalid input parameters.
 *      RT_ERR_BUSYWAIT_TIMEOUT - PHY access busy
 * Note:
 *      If Full_1000 bit is set to 1, the AutoNegotiation will be automatic set to 1. While both AutoNegotiation and Full_1000 are set to 0, the PHY speed and duplex selection will
 *      be set as following 100F > 100H > 10F > 10H priority sequence.
 */
rtksw_api_ret_t dal_rtl8367d_port_phyAutoNegoAbility_set(rtksw_uint32 unit, rtksw_port_t port, rtksw_port_phy_ability_t *pAbility)
{
    rtksw_api_ret_t       retVal;
    rtksw_uint32          phyData;
    rtksw_uint32          phyEnMsk0;
    rtksw_uint32          phyEnMsk4;
    rtksw_uint32          phyEnMsk9;
    rtksw_port_media_t    media_type;
    rtksw_port_fiber_ability_t fiberAbility;

    /* Check initialization state */
    RTKSW_CHK_INIT_STATE(unit);

    /* Speed Check */
    if (pAbility->Full_2P5G == 1)
        return RT_ERR_PHY_SPEED;

    /* Check Port Valid */
    RTKSW_CHK_PORT_IS_UTP(unit, port);

    if(NULL == pAbility)
        return RT_ERR_NULL_POINTER;

    if (pAbility->Half_10 >= RTKSW_ENABLE_END || pAbility->Full_10 >= RTKSW_ENABLE_END ||
       pAbility->Half_100 >= RTKSW_ENABLE_END || pAbility->Full_100 >= RTKSW_ENABLE_END ||
       pAbility->Full_1000 >= RTKSW_ENABLE_END || pAbility->AutoNegotiation >= RTKSW_ENABLE_END ||
       pAbility->AsyFC >= RTKSW_ENABLE_END || pAbility->FC >= RTKSW_ENABLE_END)
        return RT_ERR_INPUT;

    if (rtksw_switch_isComboPort(unit, port) == RT_ERR_OK)
    {
        if ((retVal = dal_rtl8367d_port_phyComboPortMedia_get(unit, port, &media_type)) != RT_ERR_OK)
            return retVal;

        if(media_type == RTKSW_PORT_MEDIA_FIBER)
        {
            osal_memset(&fiberAbility, 0x00, sizeof(rtksw_port_fiber_ability_t));
            fiberAbility.AutoNegotiation = pAbility->AutoNegotiation;
            fiberAbility.AsyFC = pAbility->AsyFC;
            fiberAbility.FC = pAbility->FC;
            fiberAbility.Full_1000 = pAbility->Full_1000;
            fiberAbility.Full_100 = pAbility->Full_100;
            return dal_rtl8367d_port_fiberAbility_set(unit, port, &fiberAbility);
        }
        else if (media_type == RTKSW_PORT_MEDIA_RGMII)
            return RT_ERR_PORT_ID;
    }

    /*for PHY auto mode setup*/
    pAbility->AutoNegotiation = 1;

    phyEnMsk0 = 0;
    phyEnMsk4 = 0;
    phyEnMsk9 = 0;

    if (1 == pAbility->Half_10)
    {
        /*10BASE-TX half duplex capable in reg 4.5*/
        phyEnMsk4 = phyEnMsk4 | (1 << 5);

        /*Speed selection [1:0] */
        /* 11=Reserved*/
        /* 10= 1000Mpbs*/
        /* 01= 100Mpbs*/
        /* 00= 10Mpbs*/
        phyEnMsk0 = phyEnMsk0 & (~(1 << 6));
        phyEnMsk0 = phyEnMsk0 & (~(1 << 13));
    }

    if (1 == pAbility->Full_10)
    {
        /*10BASE-TX full duplex capable in reg 4.6*/
        phyEnMsk4 = phyEnMsk4 | (1 << 6);
        /*Speed selection [1:0] */
        /* 11=Reserved*/
        /* 10= 1000Mpbs*/
        /* 01= 100Mpbs*/
        /* 00= 10Mpbs*/
        phyEnMsk0 = phyEnMsk0 & (~(1 << 6));
        phyEnMsk0 = phyEnMsk0 & (~(1 << 13));

        /*Full duplex mode in reg 0.8*/
        phyEnMsk0 = phyEnMsk0 | (1 << 8);

    }

    if (1 == pAbility->Half_100)
    {
        /*100BASE-TX half duplex capable in reg 4.7*/
        phyEnMsk4 = phyEnMsk4 | (1 << 7);
        /*Speed selection [1:0] */
        /* 11=Reserved*/
        /* 10= 1000Mpbs*/
        /* 01= 100Mpbs*/
        /* 00= 10Mpbs*/
        phyEnMsk0 = phyEnMsk0 & (~(1 << 6));
        phyEnMsk0 = phyEnMsk0 | (1 << 13);
    }


    if (1 == pAbility->Full_100)
    {
        /*100BASE-TX full duplex capable in reg 4.8*/
        phyEnMsk4 = phyEnMsk4 | (1 << 8);
        /*Speed selection [1:0] */
        /* 11=Reserved*/
        /* 10= 1000Mpbs*/
        /* 01= 100Mpbs*/
        /* 00= 10Mpbs*/
        phyEnMsk0 = phyEnMsk0 & (~(1 << 6));
        phyEnMsk0 = phyEnMsk0 | (1 << 13);
        /*Full duplex mode in reg 0.8*/
        phyEnMsk0 = phyEnMsk0 | (1 << 8);
    }


    if (1 == pAbility->Full_1000)
    {
        /*1000 BASE-T FULL duplex capable setting in reg 9.9*/
        phyEnMsk9 = phyEnMsk9 | (1 << 9);

        /*Speed selection [1:0] */
        /* 11=Reserved*/
        /* 10= 1000Mpbs*/
        /* 01= 100Mpbs*/
        /* 00= 10Mpbs*/
        phyEnMsk0 = phyEnMsk0 | (1 << 6);
        phyEnMsk0 = phyEnMsk0 & (~(1 << 13));


        /*Auto-Negotiation setting in reg 0.12*/
        phyEnMsk0 = phyEnMsk0 | (1 << 12);

     }

    if (1 == pAbility->AutoNegotiation)
    {
        /*Auto-Negotiation setting in reg 0.12*/
        phyEnMsk0 = phyEnMsk0 | (1 << 12);
    }

    if (1 == pAbility->AsyFC)
    {
        /*Asymetric flow control in reg 4.11*/
        phyEnMsk4 = phyEnMsk4 | (1 << 11);
    }
    if (1 == pAbility->FC)
    {
        /*Flow control in reg 4.10*/
        phyEnMsk4 = phyEnMsk4 | (1 << 10);
    }

    /*1000 BASE-T control register setting*/
    if ((retVal = _dal_rtl8367d_getAsicPHYReg(unit, rtksw_switch_port_L2P_get(unit, port), PHY_1000_BASET_CONTROL_REG, &phyData)) != RT_ERR_OK)
        return retVal;

    phyData = (phyData & (~0x0200)) | phyEnMsk9 ;

    if ((retVal = _dal_rtl8367d_setAsicPHYReg(unit, rtksw_switch_port_L2P_get(unit, port), PHY_1000_BASET_CONTROL_REG, phyData)) != RT_ERR_OK)
        return retVal;

    /*Auto-Negotiation control register setting*/
    if ((retVal = _dal_rtl8367d_getAsicPHYReg(unit, rtksw_switch_port_L2P_get(unit, port), PHY_AN_ADVERTISEMENT_REG, &phyData)) != RT_ERR_OK)
        return retVal;

    phyData = (phyData & (~0x0DE0)) | phyEnMsk4;
    if ((retVal = _dal_rtl8367d_setAsicPHYReg(unit, rtksw_switch_port_L2P_get(unit, port), PHY_AN_ADVERTISEMENT_REG, phyData)) != RT_ERR_OK)
        return retVal;

    /*Control register setting and restart auto*/
    if ((retVal = _dal_rtl8367d_getAsicPHYReg(unit, rtksw_switch_port_L2P_get(unit, port), PHY_CONTROL_REG, &phyData)) != RT_ERR_OK)
        return retVal;

    phyData = (phyData & (~0x3140)) | phyEnMsk0;
    /*If have auto-negotiation capable, then restart auto negotiation*/
    if (1 == pAbility->AutoNegotiation)
    {
        phyData = phyData | (1 << 9);
    }

    if ((retVal = _dal_rtl8367d_setAsicPHYReg(unit, rtksw_switch_port_L2P_get(unit, port), PHY_CONTROL_REG, phyData)) != RT_ERR_OK)
        return retVal;

    return RT_ERR_OK;
}

/* Function Name:
 *      dal_rtl8367d_port_phyAutoNegoAbility_get
 * Description:
 *      Get PHY ability through PHY registers.
 * Input:
 *      unit    - Unit ID
 *      port    - Port id.
 * Output:
 *      pAbility - Ability structure
 * Return:
 *      RT_ERR_OK               - OK
 *      RT_ERR_FAILED           - Failed
 *      RT_ERR_SMI              - SMI access error
 *      RT_ERR_PORT_ID          - Invalid port number.
 *      RT_ERR_PHY_REG_ID       - Invalid PHY address
 *      RT_ERR_INPUT            - Invalid input parameters.
 *      RT_ERR_BUSYWAIT_TIMEOUT - PHY access busy
 * Note:
 *      Get the capablity of specified PHY.
 */
rtksw_api_ret_t dal_rtl8367d_port_phyAutoNegoAbility_get(rtksw_uint32 unit, rtksw_port_t port, rtksw_port_phy_ability_t *pAbility)
{
    rtksw_api_ret_t       retVal;
    rtksw_uint32          phyData0;
    rtksw_uint32          phyData4;
    rtksw_uint32          phyData9;
    rtksw_port_media_t    media_type;
    rtksw_port_fiber_ability_t fiberAbility;

    /* Check initialization state */
    RTKSW_CHK_INIT_STATE(unit);

    /* Check Port Valid */
    RTKSW_CHK_PORT_IS_UTP(unit, port);

    if(NULL == pAbility)
        return RT_ERR_NULL_POINTER;

    if (rtksw_switch_isComboPort(unit, port) == RT_ERR_OK)
    {
        if ((retVal = dal_rtl8367d_port_phyComboPortMedia_get(unit, port, &media_type)) != RT_ERR_OK)
            return retVal;

        if(media_type == RTKSW_PORT_MEDIA_FIBER)
        {
            osal_memset(&fiberAbility, 0x00, sizeof(rtksw_port_fiber_ability_t));
            if ((retVal = dal_rtl8367d_port_fiberAbility_get(unit, port,  &fiberAbility)) != RT_ERR_OK)
                return retVal;

            osal_memset(pAbility, 0x00, sizeof(rtksw_port_phy_ability_t));
            pAbility->AutoNegotiation = fiberAbility.AutoNegotiation;
            pAbility->AsyFC = fiberAbility.AsyFC;
            pAbility->FC = fiberAbility.FC;
            pAbility->Full_1000 = fiberAbility.Full_1000;
            pAbility->Full_100 = fiberAbility.Full_100;
            return RT_ERR_OK;
        }
    }

    /*Control register setting and restart auto*/
    if ((retVal = _dal_rtl8367d_getAsicPHYReg(unit, rtksw_switch_port_L2P_get(unit, port), PHY_CONTROL_REG, &phyData0)) != RT_ERR_OK)
        return retVal;

    /*Auto-Negotiation control register setting*/
    if ((retVal = _dal_rtl8367d_getAsicPHYReg(unit, rtksw_switch_port_L2P_get(unit, port), PHY_AN_ADVERTISEMENT_REG, &phyData4)) != RT_ERR_OK)
        return retVal;

    /*1000 BASE-T control register setting*/
    if ((retVal = _dal_rtl8367d_getAsicPHYReg(unit, rtksw_switch_port_L2P_get(unit, port), PHY_1000_BASET_CONTROL_REG, &phyData9)) != RT_ERR_OK)
        return retVal;

    osal_memset(pAbility, 0x00, sizeof(rtksw_port_phy_ability_t));

    if (phyData9 & (1 << 9))
        pAbility->Full_1000 = 1;
    else
        pAbility->Full_1000 = 0;

    if (phyData4 & (1 << 11))
        pAbility->AsyFC = 1;
    else
        pAbility->AsyFC = 0;

    if (phyData4 & (1 << 10))
        pAbility->FC = 1;
    else
        pAbility->FC = 0;


    if (phyData4 & (1 << 8))
        pAbility->Full_100 = 1;
    else
        pAbility->Full_100 = 0;

    if (phyData4 & (1 << 7))
        pAbility->Half_100 = 1;
    else
        pAbility->Half_100 = 0;

    if (phyData4 & (1 << 6))
        pAbility->Full_10 = 1;
    else
        pAbility->Full_10 = 0;

    if (phyData4 & (1 << 5))
        pAbility->Half_10 = 1;
    else
        pAbility->Half_10 = 0;


    if (phyData0 & (1 << 12))
        pAbility->AutoNegotiation = 1;
    else
        pAbility->AutoNegotiation = 0;

    return RT_ERR_OK;
}

/* Function Name:
 *      dal_rtl8367d_port_phyForceModeAbility_set
 * Description:
 *      Set the port speed/duplex mode/pause/asy_pause in the PHY force mode.
 * Input:
 *      unit        - Unit ID
 *      port        - port id.
 *      pAbility    - Ability structure
 * Output:
 *      None
 * Return:
 *      RT_ERR_OK               - OK
 *      RT_ERR_FAILED           - Failed
 *      RT_ERR_SMI              - SMI access error
 *      RT_ERR_PORT_ID          - Invalid port number.
 *      RT_ERR_PHY_REG_ID       - Invalid PHY address
 *      RT_ERR_INPUT            - Invalid input parameters.
 *      RT_ERR_BUSYWAIT_TIMEOUT - PHY access busy
 * Note:
 *      While both AutoNegotiation and Full_1000 are set to 0, the PHY speed and duplex selection will
 *      be set as following 100F > 100H > 10F > 10H priority sequence.
 *      This API can be used to configure combo port in fiber mode.
 *      The possible parameters in fiber mode are Full_1000 and Full 100.
 *      All the other fields in rtksw_port_phy_ability_t will be ignored in fiber port.
 */
rtksw_api_ret_t dal_rtl8367d_port_phyForceModeAbility_set(rtksw_uint32 unit, rtksw_port_t port, rtksw_port_phy_ability_t *pAbility)
{
     rtksw_api_ret_t      retVal;
     rtksw_uint32         phyData;
     rtksw_uint32         phyEnMsk0;
     rtksw_uint32         phyEnMsk4;
     rtksw_uint32         phyEnMsk9;
     rtksw_port_media_t   media_type;
     rtksw_port_fiber_ability_t fiberAbility;

     /* Check initialization state */
     RTKSW_CHK_INIT_STATE(unit);

     /* Speed Check */
    if (pAbility->Full_2P5G == 1)
        return RT_ERR_PHY_SPEED;

     /* Check Port Valid */
     RTKSW_CHK_PORT_IS_UTP(unit, port);

     if(NULL == pAbility)
        return RT_ERR_NULL_POINTER;

     if (pAbility->Half_10 >= RTKSW_ENABLE_END || pAbility->Full_10 >= RTKSW_ENABLE_END ||
        pAbility->Half_100 >= RTKSW_ENABLE_END || pAbility->Full_100 >= RTKSW_ENABLE_END ||
        pAbility->Full_1000 >= RTKSW_ENABLE_END || pAbility->AutoNegotiation >= RTKSW_ENABLE_END ||
        pAbility->AsyFC >= RTKSW_ENABLE_END || pAbility->FC >= RTKSW_ENABLE_END)
         return RT_ERR_INPUT;

     if (rtksw_switch_isComboPort(unit, port) == RT_ERR_OK)
     {
         if ((retVal = dal_rtl8367d_port_phyComboPortMedia_get(unit, port, &media_type)) != RT_ERR_OK)
             return retVal;

         if(media_type == RTKSW_PORT_MEDIA_FIBER)
         {
             osal_memset(&fiberAbility, 0x00, sizeof(rtksw_port_fiber_ability_t));
             fiberAbility.AutoNegotiation = pAbility->AutoNegotiation;
             fiberAbility.AsyFC = pAbility->AsyFC;
             fiberAbility.FC = pAbility->FC;
             fiberAbility.Full_1000 = pAbility->Full_1000;
             fiberAbility.Full_100 = pAbility->Full_100;
             return dal_rtl8367d_port_fiberAbility_set(unit, port, &fiberAbility);
         }
     }

     if (1 == pAbility->Full_1000)
         return RT_ERR_INPUT;

     /*for PHY force mode setup*/
     pAbility->AutoNegotiation = 0;

     phyEnMsk0 = 0;
     phyEnMsk4 = 0;
     phyEnMsk9 = 0;

     if (1 == pAbility->Half_10)
     {
         /*10BASE-TX half duplex capable in reg 4.5*/
         phyEnMsk4 = phyEnMsk4 | (1 << 5);

         /*Speed selection [1:0] */
         /* 11=Reserved*/
         /* 10= 1000Mpbs*/
         /* 01= 100Mpbs*/
         /* 00= 10Mpbs*/
         phyEnMsk0 = phyEnMsk0 & (~(1 << 6));
         phyEnMsk0 = phyEnMsk0 & (~(1 << 13));
     }

     if (1 == pAbility->Full_10)
     {
         /*10BASE-TX full duplex capable in reg 4.6*/
         phyEnMsk4 = phyEnMsk4 | (1 << 6);
         /*Speed selection [1:0] */
         /* 11=Reserved*/
         /* 10= 1000Mpbs*/
         /* 01= 100Mpbs*/
         /* 00= 10Mpbs*/
         phyEnMsk0 = phyEnMsk0 & (~(1 << 6));
         phyEnMsk0 = phyEnMsk0 & (~(1 << 13));

         /*Full duplex mode in reg 0.8*/
         phyEnMsk0 = phyEnMsk0 | (1 << 8);

     }

     if (1 == pAbility->Half_100)
     {
         /*100BASE-TX half duplex capable in reg 4.7*/
         phyEnMsk4 = phyEnMsk4 | (1 << 7);
         /*Speed selection [1:0] */
         /* 11=Reserved*/
         /* 10= 1000Mpbs*/
         /* 01= 100Mpbs*/
         /* 00= 10Mpbs*/
         phyEnMsk0 = phyEnMsk0 & (~(1 << 6));
         phyEnMsk0 = phyEnMsk0 | (1 << 13);
     }


     if (1 == pAbility->Full_100)
     {
         /*100BASE-TX full duplex capable in reg 4.8*/
         phyEnMsk4 = phyEnMsk4 | (1 << 8);
         /*Speed selection [1:0] */
         /* 11=Reserved*/
         /* 10= 1000Mpbs*/
         /* 01= 100Mpbs*/
         /* 00= 10Mpbs*/
         phyEnMsk0 = phyEnMsk0 & (~(1 << 6));
         phyEnMsk0 = phyEnMsk0 | (1 << 13);
         /*Full duplex mode in reg 0.8*/
         phyEnMsk0 = phyEnMsk0 | (1 << 8);
     }

     if (1 == pAbility->AsyFC)
     {
         /*Asymetric flow control in reg 4.11*/
         phyEnMsk4 = phyEnMsk4 | (1 << 11);
     }
     if (1 == pAbility->FC)
     {
         /*Flow control in reg 4.10*/
         phyEnMsk4 = phyEnMsk4 | ((1 << 10));
     }

     /*1000 BASE-T control register setting*/
     if ((retVal = _dal_rtl8367d_getAsicPHYReg(unit, rtksw_switch_port_L2P_get(unit, port), PHY_1000_BASET_CONTROL_REG, &phyData)) != RT_ERR_OK)
         return retVal;

     phyData = (phyData & (~0x0200)) | phyEnMsk9 ;

     if ((retVal = _dal_rtl8367d_setAsicPHYReg(unit, rtksw_switch_port_L2P_get(unit, port), PHY_1000_BASET_CONTROL_REG, phyData)) != RT_ERR_OK)
         return retVal;

     /*Auto-Negotiation control register setting*/
     if ((retVal = _dal_rtl8367d_getAsicPHYReg(unit, rtksw_switch_port_L2P_get(unit, port), PHY_AN_ADVERTISEMENT_REG, &phyData)) != RT_ERR_OK)
         return retVal;

     phyData = (phyData & (~0x0DE0)) | phyEnMsk4;
     if ((retVal = _dal_rtl8367d_setAsicPHYReg(unit, rtksw_switch_port_L2P_get(unit, port), PHY_AN_ADVERTISEMENT_REG, phyData)) != RT_ERR_OK)
         return retVal;

     /*Control register setting and power off/on*/
     phyData = phyEnMsk0 & (~(1 << 12));
     phyData |= (1 << 11);   /* power down PHY, bit 11 should be set to 1 */
     if ((retVal = _dal_rtl8367d_setAsicPHYReg(unit, rtksw_switch_port_L2P_get(unit, port), PHY_CONTROL_REG, phyData)) != RT_ERR_OK)
         return retVal;

     phyData = phyData & (~(1 << 11));   /* power on PHY, bit 11 should be set to 0*/
     if ((retVal = _dal_rtl8367d_setAsicPHYReg(unit, rtksw_switch_port_L2P_get(unit, port), PHY_CONTROL_REG, phyData)) != RT_ERR_OK)
         return retVal;

     return RT_ERR_OK;
}

/* Function Name:
 *      dal_rtl8367d_port_phyForceModeAbility_get
 * Description:
 *      Get PHY ability through PHY registers.
 * Input:
 *      unit    - Unit ID
 *      port    - Port id.
 * Output:
 *      pAbility - Ability structure
 * Return:
 *      RT_ERR_OK               - OK
 *      RT_ERR_FAILED           - Failed
 *      RT_ERR_SMI              - SMI access error
 *      RT_ERR_PORT_ID          - Invalid port number.
 *      RT_ERR_PHY_REG_ID       - Invalid PHY address
 *      RT_ERR_INPUT            - Invalid input parameters.
 *      RT_ERR_BUSYWAIT_TIMEOUT - PHY access busy
 * Note:
 *      Get the capablity of specified PHY.
 */
rtksw_api_ret_t dal_rtl8367d_port_phyForceModeAbility_get(rtksw_uint32 unit, rtksw_port_t port, rtksw_port_phy_ability_t *pAbility)
{
    rtksw_api_ret_t       retVal;
    rtksw_uint32          phyData0;
    rtksw_uint32          phyData4;
    rtksw_uint32          phyData9;
    rtksw_port_media_t    media_type;
    rtksw_port_fiber_ability_t fiberAbility;

    /* Check initialization state */
    RTKSW_CHK_INIT_STATE(unit);

    /* Check Port Valid */
     RTKSW_CHK_PORT_IS_UTP(unit, port);

     if(NULL == pAbility)
        return RT_ERR_NULL_POINTER;

     if (rtksw_switch_isComboPort(unit, port) == RT_ERR_OK)
     {
         if ((retVal = dal_rtl8367d_port_phyComboPortMedia_get(unit, port, &media_type)) != RT_ERR_OK)
             return retVal;

         if(media_type == RTKSW_PORT_MEDIA_FIBER)
         {
             osal_memset(&fiberAbility, 0x00, sizeof(rtksw_port_fiber_ability_t));
             if ((retVal = dal_rtl8367d_port_fiberAbility_get(unit, port, &fiberAbility)) != RT_ERR_OK)
                 return retVal;

             osal_memset(pAbility, 0x00, sizeof(rtksw_port_phy_ability_t));
             pAbility->AutoNegotiation = fiberAbility.AutoNegotiation;
             pAbility->AsyFC = fiberAbility.AsyFC;
             pAbility->FC = fiberAbility.FC;
             pAbility->Full_1000 = fiberAbility.Full_1000;
             pAbility->Full_100 = fiberAbility.Full_100;
             return RT_ERR_OK;
         }
     }

    /*Control register setting and restart auto*/
    if ((retVal = _dal_rtl8367d_getAsicPHYReg(unit, rtksw_switch_port_L2P_get(unit, port), PHY_CONTROL_REG, &phyData0)) != RT_ERR_OK)
        return retVal;

    /*Auto-Negotiation control register setting*/
    if ((retVal = _dal_rtl8367d_getAsicPHYReg(unit, rtksw_switch_port_L2P_get(unit, port), PHY_AN_ADVERTISEMENT_REG, &phyData4)) != RT_ERR_OK)
        return retVal;

    /*1000 BASE-T control register setting*/
    if ((retVal = _dal_rtl8367d_getAsicPHYReg(unit, rtksw_switch_port_L2P_get(unit, port), PHY_1000_BASET_CONTROL_REG, &phyData9)) != RT_ERR_OK)
        return retVal;

    osal_memset(pAbility, 0x00, sizeof(rtksw_port_phy_ability_t));
    
    if (phyData9 & (1 << 9))
        pAbility->Full_1000 = 1;
    else
        pAbility->Full_1000 = 0;

    if (phyData4 & (1 << 11))
        pAbility->AsyFC = 1;
    else
        pAbility->AsyFC = 0;

    if (phyData4 & ((1 << 10)))
        pAbility->FC = 1;
    else
        pAbility->FC = 0;


    if (phyData4 & (1 << 8))
        pAbility->Full_100 = 1;
    else
        pAbility->Full_100 = 0;

    if (phyData4 & (1 << 7))
        pAbility->Half_100 = 1;
    else
        pAbility->Half_100 = 0;

    if (phyData4 & (1 << 6))
        pAbility->Full_10 = 1;
    else
        pAbility->Full_10 = 0;

    if (phyData4 & (1 << 5))
        pAbility->Half_10 = 1;
    else
        pAbility->Half_10 = 0;


    if (phyData0 & (1 << 12))
        pAbility->AutoNegotiation = 1;
    else
        pAbility->AutoNegotiation = 0;

    return RT_ERR_OK;
}

/* Function Name:
 *      dal_rtl8367d_port_phyStatus_get
 * Description:
 *      Get ethernet PHY linking status
 * Input:
 *      unit        - Unit ID
 *      port        - Port id.
 * Output:
 *      linkStatus  - PHY link status
 *      speed       - PHY link speed
 *      duplex      - PHY duplex mode
 * Return:
 *      RT_ERR_OK               - OK
 *      RT_ERR_FAILED           - Failed
 *      RT_ERR_SMI              - SMI access error
 *      RT_ERR_PORT_ID          - Invalid port number.
 *      RT_ERR_PHY_REG_ID       - Invalid PHY address
 *      RT_ERR_INPUT            - Invalid input parameters.
 *      RT_ERR_BUSYWAIT_TIMEOUT - PHY access busy
 * Note:
 *      API will return auto negotiation status of phy.
 */
rtksw_api_ret_t dal_rtl8367d_port_phyStatus_get(rtksw_uint32 unit, rtksw_port_t port, rtksw_port_linkStatus_t *pLinkStatus, rtksw_port_speed_t *pSpeed, rtksw_port_duplex_t *pDuplex)
{
    rtksw_api_ret_t retVal;
    rtksw_uint32 phyData;

    /* Check initialization state */
    RTKSW_CHK_INIT_STATE(unit);

    /* Check Port Valid */
    RTKSW_CHK_PORT_IS_UTP(unit, port);

    if( (NULL == pLinkStatus) || (NULL == pSpeed) || (NULL == pDuplex) )
        return RT_ERR_NULL_POINTER;

    /*Get PHY resolved register*/
    if ((retVal = _dal_rtl8367d_getAsicPHYReg(unit, rtksw_switch_port_L2P_get(unit, port), PHY_RESOLVED_REG, &phyData)) != RT_ERR_OK)
        return retVal;

    /*check link status*/
    if (phyData & (1<<2))
    {
        *pLinkStatus = 1;

        /*check link speed*/
        *pSpeed = (phyData&0x0030) >> 4;

        /*check link duplex*/
        *pDuplex = (phyData&0x0008) >> 3;
    }
    else
    {
        *pLinkStatus = 0;
        *pSpeed = 0;
        *pDuplex = 0;
    }

    return RT_ERR_OK;
}

/* Function Name:
 *      dal_rtl8367d_port_macForceLink_set
 * Description:
 *      Set port force linking configuration.
 * Input:
 *      unit            - Unit ID
 *      port            - port id.
 *      pPortability    - port ability configuration
 * Output:
 *      None
 * Return:
 *      RT_ERR_OK           - OK
 *      RT_ERR_FAILED       - Failed
 *      RT_ERR_SMI          - SMI access error
 *      RT_ERR_PORT_ID      - Invalid port number.
 * Note:
 *      This API can set Port/MAC force mode properties.
 */
rtksw_api_ret_t dal_rtl8367d_port_macForceLink_set(rtksw_uint32 unit, rtksw_port_t port, rtksw_port_mac_ability_t *pPortability)
{
    rtksw_api_ret_t retVal;
    rtksw_uint32 reg_data = 0;
    rtksw_uint32 reg_data2;
    rtksw_uint32 rtl8367d_speed;

    /* Check initialization state */
    RTKSW_CHK_INIT_STATE(unit);

    if(NULL == pPortability)
        return RT_ERR_NULL_POINTER;

    if (pPortability->forcemode >1|| pPortability->speed >= RTKSW_PORT_SPEED_5G || pPortability->duplex > 1 ||
       pPortability->link > 1 || pPortability->nway > 1 || pPortability->txpause > 1 || pPortability->rxpause > 1)
        return RT_ERR_INPUT;

    switch (pPortability->speed)
    {
        case RTKSW_PORT_SPEED_10M:
            rtl8367d_speed = RTL8367D_EXT_RTKSW_PORT_SPEED_10M;
            break;
        case RTKSW_PORT_SPEED_100M:
            rtl8367d_speed = RTL8367D_EXT_RTKSW_PORT_SPEED_100M;
            break;
        case RTKSW_PORT_SPEED_1000M:
            rtl8367d_speed = RTL8367D_EXT_RTKSW_PORT_SPEED_1000M;
            break;
        case RTKSW_PORT_SPEED_500M:
            rtl8367d_speed = RTL8367D_EXT_RTKSW_PORT_SPEED_500M;
            break;
        case RTKSW_PORT_SPEED_2500M:
            rtl8367d_speed = RTL8367D_EXT_RTKSW_PORT_SPEED_2500M;
            break;
        default:
            return RT_ERR_INPUT;
    }

    reg_data |= ((rtl8367d_speed & 0x0C) >> 2) << 12;
    reg_data |= pPortability->nway << 7;
    reg_data |= pPortability->txpause << 6;
    reg_data |= pPortability->rxpause << 5;
    reg_data |= pPortability->link << 4;
    reg_data |= pPortability->duplex << 2;
    reg_data |= rtl8367d_speed & 0x03;

    if(pPortability->forcemode)
        reg_data2 = 0xFFFF;
    else
        reg_data2 = 0;

    /* Link down */
    if((retVal = rtl8367d_setAsicRegBit(unit, RTL8367D_REG_MAC0_FORCE_SELECT + rtksw_switch_port_L2P_get(unit, port), RTL8367D_MAC0_FORCE_SELECT_LINK_ABLTY_OFFSET, 0)) != RT_ERR_OK)
        return retVal;

    /* Configure ability without link */
    if((retVal = rtl8367d_setAsicReg(unit, RTL8367D_REG_MAC0_FORCE_SELECT + rtksw_switch_port_L2P_get(unit, port), reg_data & ~(0x0010))) != RT_ERR_OK)
        return retVal;

    if((retVal = rtl8367d_setAsicReg(unit, RTL8367D_REG_MAC0_FORCE_SELECT_EN + rtksw_switch_port_L2P_get(unit, port), reg_data2)) != RT_ERR_OK)
        return retVal;

    /* Link up */
    if (pPortability->link == 1)
    {
        if((retVal = rtl8367d_setAsicReg(unit, RTL8367D_REG_MAC0_FORCE_SELECT + rtksw_switch_port_L2P_get(unit, port), reg_data)) != RT_ERR_OK)
            return retVal;
    }

    return RT_ERR_OK;
}

/* Function Name:
 *      dal_rtl8367d_port_macForceLink_get
 * Description:
 *      Get port force linking configuration.
 * Input:
 *      unit        - Unit ID
 *      port        - Port id.
 * Output:
 *      pPortability - port ability configuration
 * Return:
 *      RT_ERR_OK           - OK
 *      RT_ERR_FAILED       - Failed
 *      RT_ERR_SMI          - SMI access error
 *      RT_ERR_PORT_ID      - Invalid port number.
 *      RT_ERR_INPUT        - Invalid input parameters.
 * Note:
 *      This API can get Port/MAC force mode properties.
 */
rtksw_api_ret_t dal_rtl8367d_port_macForceLink_get(rtksw_uint32 unit, rtksw_port_t port, rtksw_port_mac_ability_t *pPortability)
{
    rtksw_api_ret_t retVal;
    rtksw_uint32 reg_data;
    rtksw_uint32 reg_data2;
    rtksw_uint32 rtl8367d_speed;

    /* Check initialization state */
    RTKSW_CHK_INIT_STATE(unit);

    if(NULL == pPortability)
        return RT_ERR_NULL_POINTER;

    if((retVal = rtl8367d_getAsicReg(unit, RTL8367D_REG_MAC0_FORCE_SELECT + rtksw_switch_port_L2P_get(unit, port), &reg_data)) != RT_ERR_OK)
        return retVal;

    if((retVal = rtl8367d_getAsicReg(unit, RTL8367D_REG_MAC0_FORCE_SELECT_EN + rtksw_switch_port_L2P_get(unit, port), &reg_data2)) != RT_ERR_OK)
        return retVal;

    if ((reg_data == 0x1000) && (reg_data2 == 0x3000) && (rtksw_switch_isExtPort(unit, port) == RT_ERR_OK))
    {
        pPortability->forcemode = 0;
        pPortability->nway      = 0;
        pPortability->txpause   = 0;
        pPortability->rxpause   = 0;
        pPortability->link      = 0;
        pPortability->duplex    = 0;
        return RT_ERR_OK;
    }

    pPortability->forcemode = (reg_data2 == 0) ? 0 : 1;
    pPortability->nway      = (reg_data >> 7) & 0x0001;
    pPortability->txpause   = (reg_data >> 6) & 0x0001;
    pPortability->rxpause   = (reg_data >> 5) & 0x0001;
    pPortability->link      = (reg_data >> 4) & 0x0001;
    pPortability->duplex    = (reg_data >> 2) & 0x0001;

    rtl8367d_speed          = (reg_data & 0x0003) | (((reg_data & 0x3000) >> 12) << 2);
    switch (rtl8367d_speed)
    {
        case RTL8367D_EXT_RTKSW_PORT_SPEED_10M:
            pPortability->speed = RTKSW_PORT_SPEED_10M;
            break;
        case RTL8367D_EXT_RTKSW_PORT_SPEED_100M:
            pPortability->speed = RTKSW_PORT_SPEED_100M;
            break;
        case RTL8367D_EXT_RTKSW_PORT_SPEED_1000M:
            pPortability->speed = RTKSW_PORT_SPEED_1000M;
            break;
        case RTL8367D_EXT_RTKSW_PORT_SPEED_500M:
            pPortability->speed = RTKSW_PORT_SPEED_500M;
            break;
        case RTL8367D_EXT_RTKSW_PORT_SPEED_2500M:
            pPortability->speed = RTKSW_PORT_SPEED_2500M;
            break;
        default:
            return RT_ERR_INPUT;
    }

    return RT_ERR_OK;
}

/* Function Name:
 *      dal_rtl8367d_port_macForceLinkExt_set
 * Description:
 *      Set external interface force linking configuration.
 * Input:
 *      unit            - Unit ID
 *      port            - external port ID
 *      mode            - external interface mode
 *      pPortability    - port ability configuration
 * Output:
 *      None
 * Return:
 *      RT_ERR_OK           - OK
 *      RT_ERR_FAILED       - Failed
 *      RT_ERR_SMI          - SMI access error
 *      RT_ERR_INPUT        - Invalid input parameters.
 * Note:
 *      This API can set external interface force mode properties.
 *      The external interface can be set to:
 *      - RTKSW_MODE_EXT_DISABLE,
 *      - RTKSW_MODE_EXT_RGMII,
 *      - RTKSW_MODE_EXT_MII_MAC,
 *      - RTKSW_MODE_EXT_MII_PHY,
 *      - RTKSW_MODE_EXT_TMII_MAC,
 *      - RTKSW_MODE_EXT_TMII_PHY,
 *      - RTKSW_MODE_EXT_GMII,
 *      - RTKSW_MODE_EXT_RMII_MAC,
 *      - RTKSW_MODE_EXT_RMII_PHY,
 *      - RTKSW_MODE_EXT_SGMII,
 *      - RTKSW_MODE_EXT_HSGMII,
 */
rtksw_api_ret_t dal_rtl8367d_port_macForceLinkExt_set(rtksw_uint32 unit, rtksw_port_t port, rtksw_mode_ext_t mode, rtksw_port_mac_ability_t *pPortability)
{
    rtksw_api_ret_t retVal;
    rtksw_port_mac_ability_t ability;
    rtksw_uint32 ext_id;
    rtksw_port_media_t media_type;

    /* Check initialization state */
    RTKSW_CHK_INIT_STATE(unit);

    /* Check Port Valid */
    if (port == UTP_PORT4)
    {
        if (mode != RTKSW_MODE_EXT_RGMII)
            return RT_ERR_INPUT;

        if ((retVal = dal_rtl8367d_port_phyComboPortMedia_get(unit, port, &media_type)) != RT_ERR_OK)
            return retVal;

        if (media_type != RTKSW_PORT_MEDIA_RGMII)
            return RT_ERR_PORT_ID;
    }
    else
    {
        RTKSW_CHK_PORT_IS_EXT(unit, port);

        if ((port == EXT_PORT1) && (mode == RTKSW_MODE_EXT_RGMII))
        {
            if ((retVal = dal_rtl8367d_port_phyComboPortMedia_get(unit, UTP_PORT4, &media_type)) != RT_ERR_OK)
                return retVal;

            if (media_type == RTKSW_PORT_MEDIA_RGMII)
                return RT_ERR_PORT_ID;
        }
    }

    if (NULL == pPortability)
        return RT_ERR_NULL_POINTER;

    if ((mode > RTKSW_MODE_EXT_100FX) && (mode != RTKSW_MODE_EXT_FIBER_2P5G))
        return RT_ERR_INPUT;

    if ((mode == RTKSW_MODE_EXT_GMII) || (mode >= RTKSW_MODE_EXT_10GR))
        return RT_ERR_INPUT;

    if(mode == RTKSW_MODE_EXT_HSGMII)
    {
        if (pPortability->forcemode > 1 || pPortability->speed != RTKSW_PORT_SPEED_2500M || pPortability->duplex != RTKSW_PORT_FULL_DUPLEX ||
           pPortability->link >= RTKSW_PORT_LINKSTATUS_END || pPortability->nway > 1 || pPortability->txpause > 1 || pPortability->rxpause > 1)
            return RT_ERR_INPUT;

        if(rtksw_switch_isHsgPort(unit, port) != RT_ERR_OK)
            return RT_ERR_PORT_ID;
    }
    else if (mode == RTKSW_MODE_EXT_RGMII)
    {
        if (pPortability->forcemode > 1 || pPortability->speed > RTKSW_PORT_SPEED_1000M || pPortability->duplex >= RTKSW_PORT_DUPLEX_END ||
           pPortability->link >= RTKSW_PORT_LINKSTATUS_END || pPortability->nway > 1 || pPortability->txpause > 1 || pPortability->rxpause > 1)
            return RT_ERR_INPUT;
    }
    else if (mode != RTKSW_MODE_EXT_DISABLE)
    {
        if (pPortability->forcemode > 1 || pPortability->speed > RTKSW_PORT_SPEED_1000M || pPortability->duplex >= RTKSW_PORT_DUPLEX_END ||
           pPortability->link >= RTKSW_PORT_LINKSTATUS_END || pPortability->nway > 1 || pPortability->txpause > 1 || pPortability->rxpause > 1)
            return RT_ERR_INPUT;
    }

    if ((port == UTP_PORT4) && (mode == RTKSW_MODE_EXT_RGMII))
    {
        if ((retVal = _dal_rtl8367d_setUtp4RgmiiMode(unit, port, mode)) != RT_ERR_OK)
            return retVal;
    }
    else
    {
        ext_id = port - 15;

        /* Configure EXT port mode */
        if ((retVal = _dal_rtl8367d_setAsicPortExtMode(unit, ext_id, mode)) != RT_ERR_OK)
            return retVal;
    }

    /* Configure Ability */
    osal_memset(&ability, 0x00, sizeof(rtksw_port_mac_ability_t));
    if ((retVal = dal_rtl8367d_port_macForceLink_get(unit, port, &ability)) != RT_ERR_OK)
        return retVal;

    if (pPortability->link == 0)
    {
        if (mode == RTKSW_MODE_EXT_FIBER_2P5G)
        {
            if((retVal = rtl8367d_setAsicReg(unit, RTL8367D_REG_MAC0_FORCE_SELECT + rtksw_switch_port_L2P_get(unit, port), 0x1000)) != RT_ERR_OK)
                return retVal;

            if((retVal = rtl8367d_setAsicReg(unit, RTL8367D_REG_MAC0_FORCE_SELECT_EN + rtksw_switch_port_L2P_get(unit, port), 0x3000)) != RT_ERR_OK)
                return retVal;
        }
        else
        {
            ability.forcemode = pPortability->forcemode;
            ability.duplex    = pPortability->duplex;
            ability.link      = pPortability->link;
            ability.nway      = pPortability->nway;
            ability.txpause   = pPortability->txpause;
            ability.rxpause   = pPortability->rxpause;
            ability.speed     = pPortability->speed;

            if ((retVal = dal_rtl8367d_port_macForceLink_set(unit, port, &ability)) != RT_ERR_OK)
                return retVal;
        }
    }
    else
    {
        ability.forcemode = pPortability->forcemode;
        ability.duplex    = pPortability->duplex;
        ability.link      = pPortability->link;
        ability.nway      = pPortability->nway;
        ability.txpause   = pPortability->txpause;
        ability.rxpause   = pPortability->rxpause;
        ability.speed     = pPortability->speed;

        if ((retVal = dal_rtl8367d_port_macForceLink_set(unit, port, &ability)) != RT_ERR_OK)
            return retVal;
    }


    return RT_ERR_OK;
}

/* Function Name:
 *      dal_rtl8367d_port_macForceLinkExt_get
 * Description:
 *      Set external interface force linking configuration.
 * Input:
 *      unit            - Unit ID
 *      port            - external port ID
 * Output:
 *      pMode           - external interface mode
 *      pPortability    - port ability configuration
 * Return:
 *      RT_ERR_OK           - OK
 *      RT_ERR_FAILED       - Failed
 *      RT_ERR_SMI          - SMI access error
 *      RT_ERR_INPUT        - Invalid input parameters.
 * Note:
 *      This API can get external interface force mode properties.
 */
rtksw_api_ret_t dal_rtl8367d_port_macForceLinkExt_get(rtksw_uint32 unit, rtksw_port_t port, rtksw_mode_ext_t *pMode, rtksw_port_mac_ability_t *pPortability)
{
    rtksw_api_ret_t retVal;
    rtksw_port_mac_ability_t ability;
    rtksw_uint32 ext_id;
    rtksw_port_media_t media_type;

    /* Check initialization state */
    RTKSW_CHK_INIT_STATE(unit);

    if (NULL == pMode)
        return RT_ERR_NULL_POINTER;

    if (NULL == pPortability)
        return RT_ERR_NULL_POINTER;

    /* Check Port Valid */
    if (port == UTP_PORT4)
    {
        if ((retVal = _dal_rtl8367d_getUtp4RgmiiMode(unit, port, pMode)) != RT_ERR_OK)
            return retVal;
    }
    else
    {
        RTKSW_CHK_PORT_IS_EXT(unit, port);
        ext_id = port - 15;

        if ((retVal = _dal_rtl8367d_getAsicPortExtMode(unit, ext_id, (rtksw_uint32 *)pMode)) != RT_ERR_OK)
            return retVal;

        if ( (ext_id == 1) && ((*pMode == RTKSW_MODE_EXT_1000X_100FX) || (*pMode == RTKSW_MODE_EXT_1000X) || (*pMode == RTKSW_MODE_EXT_100FX)) )
        {
            if ((retVal = dal_rtl8367d_port_phyComboPortMedia_get(unit, UTP_PORT4, &media_type)) != RT_ERR_OK)
                return retVal;

            if (media_type == RTKSW_PORT_MEDIA_FIBER)
            {
                *pMode = RTKSW_MODE_EXT_DISABLE;
            }
        }

        if ((ext_id == 2) && (*pMode == RTKSW_MODE_EXT_RGMII))
        {
            if ((retVal = dal_rtl8367d_port_phyComboPortMedia_get(unit, UTP_PORT4, &media_type)) != RT_ERR_OK)
                return retVal;

            if (media_type == RTKSW_PORT_MEDIA_RGMII)
                *pMode = RTKSW_MODE_EXT_DISABLE;
        }
    }

    osal_memset(&ability, 0x00, sizeof(rtksw_port_mac_ability_t));
    if ((retVal = dal_rtl8367d_port_macForceLink_get(unit, port, &ability)) != RT_ERR_OK)
        return retVal;

    pPortability->forcemode = ability.forcemode;
    pPortability->duplex    = ability.duplex;
    pPortability->link      = ability.link;
    pPortability->nway      = ability.nway;
    pPortability->txpause   = ability.txpause;
    pPortability->rxpause   = ability.rxpause;
    pPortability->speed     = ability.speed;

    return RT_ERR_OK;

}

/* Function Name:
 *      dal_rtl8367d_port_macStatus_get
 * Description:
 *      Get port link status.
 * Input:
 *      unit        - Unit ID
 *      port        - Port id.
 * Output:
 *      pPortstatus - port ability configuration
 * Return:
 *      RT_ERR_OK           - OK
 *      RT_ERR_FAILED       - Failed
 *      RT_ERR_SMI          - SMI access error
 *      RT_ERR_PORT_ID      - Invalid port number.
 * Note:
 *      This API can get Port/PHY properties.
 */
rtksw_api_ret_t dal_rtl8367d_port_macStatus_get(rtksw_uint32 unit, rtksw_port_t port, rtksw_port_mac_ability_t *pPortstatus)
{
    rtksw_api_ret_t retVal;
    rtksw_uint32 regData;
    rtksw_uint32 rtl8367d_speed;

    /* Check initialization state */
    RTKSW_CHK_INIT_STATE(unit);

    /* Check Port Valid */
    RTKSW_CHK_PORT_VALID(unit, port);

    if(NULL == pPortstatus)
        return RT_ERR_NULL_POINTER;

    if ((retVal = rtl8367d_getAsicReg(unit, RTL8367D_REG_PORT0_STATUS+rtksw_switch_port_L2P_get(unit, port), &regData)) != RT_ERR_OK)
        return retVal;

    osal_memset(pPortstatus, 0x00, sizeof(rtksw_port_mac_ability_t));
    pPortstatus->link = (regData >> 4) & 0x0001;

    if (pPortstatus->link == 1)
    {
        pPortstatus->duplex    = (regData >> 2) & 0x0001;
        pPortstatus->nway      = (regData >> 7) & 0x0001;
        pPortstatus->txpause   = (regData >> 6) & 0x0001;
        pPortstatus->rxpause   = (regData >> 5) & 0x0001;

        rtl8367d_speed = (regData & 0x0003) | (((regData & 0x3000) >> 12) << 2);
        switch (rtl8367d_speed)
        {
            case RTL8367D_EXT_RTKSW_PORT_SPEED_10M:
                pPortstatus->speed = RTKSW_PORT_SPEED_10M;
                break;
            case RTL8367D_EXT_RTKSW_PORT_SPEED_100M:
                pPortstatus->speed = RTKSW_PORT_SPEED_100M;
                break;
            case RTL8367D_EXT_RTKSW_PORT_SPEED_1000M:
                pPortstatus->speed = RTKSW_PORT_SPEED_1000M;
                break;
            case RTL8367D_EXT_RTKSW_PORT_SPEED_500M:
                pPortstatus->speed = RTKSW_PORT_SPEED_500M;
                break;
            case RTL8367D_EXT_RTKSW_PORT_SPEED_2500M:
                pPortstatus->speed = RTKSW_PORT_SPEED_2500M;
                break;
            default:
                return RT_ERR_INPUT;
        }
    }

    return RT_ERR_OK;
}

/* Function Name:
 *      dal_rtl8367d_port_macLocalLoopbackEnable_set
 * Description:
 *      Set Port Local Loopback. (Redirect TX to RX.)
 * Input:
 *      unit        - Unit ID
 *      port        - Port id.
 *      enable      - Loopback state, 0:disable, 1:enable
 * Output:
 *      None.
 * Return:
 *      RT_ERR_OK           - OK
 *      RT_ERR_FAILED       - Failed
 *      RT_ERR_SMI          - SMI access error
 *      RT_ERR_PORT_ID      - Invalid port number.
 * Note:
 *      This API can enable/disable Local loopback in MAC.
 *      For UTP port, This API will also enable the digital
 *      loopback bit in PHY register for sync of speed between
 *      PHY and MAC. For EXT port, users need to force the
 *      link state by themself.
 */
rtksw_api_ret_t dal_rtl8367d_port_macLocalLoopbackEnable_set(rtksw_uint32 unit, rtksw_port_t port, rtksw_enable_t enable)
{
    rtksw_api_ret_t   retVal;
    rtksw_uint32      data;

    /* Check initialization state */
    RTKSW_CHK_INIT_STATE(unit);

    /* Check Port Valid */
    RTKSW_CHK_PORT_VALID(unit, port);

    if(enable >= RTKSW_ENABLE_END)
        return RT_ERR_INPUT;

    if ((retVal = rtl8367d_setAsicRegBit(unit, RTL8367D_REG_PORT0_MISC_CFG + (rtksw_switch_port_L2P_get(unit, port) << 5), RTL8367D_PORT0_MISC_CFG_MAC_LOOPBACK_OFFSET, (enable == RTKSW_ENABLED) ? 1 : 0)) != RT_ERR_OK)
        return retVal;

    if(rtksw_switch_isUtpPort(unit, port) == RT_ERR_OK)
    {
        if ((retVal = _dal_rtl8367d_getAsicPHYReg(unit, rtksw_switch_port_L2P_get(unit, port), PHY_CONTROL_REG, &data)) != RT_ERR_OK)
            return retVal;

        if(enable == RTKSW_ENABLED)
            data |= (0x0001 << 14);
        else
            data &= ~(0x0001 << 14);

        if ((retVal = _dal_rtl8367d_setAsicPHYReg(unit, rtksw_switch_port_L2P_get(unit, port), PHY_CONTROL_REG, data)) != RT_ERR_OK)
            return retVal;
    }

    return RT_ERR_OK;
}

/* Function Name:
 *      dal_rtl8367d_port_macLocalLoopbackEnable_get
 * Description:
 *      Get Port Local Loopback. (Redirect TX to RX.)
 * Input:
 *      unit        - Unit ID
 *      port        - Port id.
 * Output:
 *      pEnable  - Loopback state, 0:disable, 1:enable
 * Return:
 *      RT_ERR_OK           - OK
 *      RT_ERR_FAILED       - Failed
 *      RT_ERR_SMI          - SMI access error
 *      RT_ERR_PORT_ID      - Invalid port number.
 * Note:
 *      None.
 */
rtksw_api_ret_t dal_rtl8367d_port_macLocalLoopbackEnable_get(rtksw_uint32 unit, rtksw_port_t port, rtksw_enable_t *pEnable)
{
    rtksw_api_ret_t retVal;
    rtksw_uint32 regData;

    /* Check initialization state */
    RTKSW_CHK_INIT_STATE(unit);

    /* Check Port Valid */
    RTKSW_CHK_PORT_VALID(unit, port);

    if (NULL == pEnable)
        return RT_ERR_NULL_POINTER;

    if ((retVal = rtl8367d_getAsicRegBit(unit, RTL8367D_REG_PORT0_MISC_CFG + (rtksw_switch_port_L2P_get(unit, port) << 5), RTL8367D_PORT0_MISC_CFG_MAC_LOOPBACK_OFFSET, &regData)) != RT_ERR_OK)
        return retVal;

    *pEnable = (regData == 1) ? RTKSW_ENABLED : RTKSW_DISABLED;
    return RT_ERR_OK;
}

/* Function Name:
 *      dal_rtl8367d_port_phyReg_set
 * Description:
 *      Set PHY register data of the specific port.
 * Input:
 *      unit        - Unit ID
 *      port        - port id.
 *      reg         - Register id
 *      regData     - Register data
 * Output:
 *      None
 * Return:
 *      RT_ERR_OK               - OK
 *      RT_ERR_FAILED           - Failed
 *      RT_ERR_SMI              - SMI access error
 *      RT_ERR_PORT_ID          - Invalid port number.
 *      RT_ERR_PHY_REG_ID       - Invalid PHY address
 *      RT_ERR_BUSYWAIT_TIMEOUT - PHY access busy
 * Note:
 *      This API can set PHY register data of the specific port.
 */
rtksw_api_ret_t dal_rtl8367d_port_phyReg_set(rtksw_uint32 unit, rtksw_port_t port, rtksw_port_phy_reg_t reg, rtksw_port_phy_data_t regData)
{
    rtksw_api_ret_t retVal;

    /* Check initialization state */
    RTKSW_CHK_INIT_STATE(unit);

    /* Check Port Valid */
    RTKSW_CHK_PORT_IS_UTP(unit, port);

    if ((retVal = _dal_rtl8367d_setAsicPHYReg(unit, rtksw_switch_port_L2P_get(unit, port), reg, regData)) != RT_ERR_OK)
        return retVal;

    return RT_ERR_OK;
}

/* Function Name:
 *      dal_rtl8367d_port_phyReg_get
 * Description:
 *      Get PHY register data of the specific port.
 * Input:
 *      unit        - Unit ID
 *      port        - Port id.
 *      reg         - Register id
 * Output:
 *      pData   - Register data
 * Return:
 *      RT_ERR_OK               - OK
 *      RT_ERR_FAILED           - Failed
 *      RT_ERR_SMI              - SMI access error
 *      RT_ERR_PORT_ID          - Invalid port number.
 *      RT_ERR_PHY_REG_ID       - Invalid PHY address
 *      RT_ERR_BUSYWAIT_TIMEOUT - PHY access busy
 * Note:
 *      This API can get PHY register data of the specific port.
 */
rtksw_api_ret_t dal_rtl8367d_port_phyReg_get(rtksw_uint32 unit, rtksw_port_t port, rtksw_port_phy_reg_t reg, rtksw_port_phy_data_t *pData)
{
    rtksw_api_ret_t retVal;

    /* Check initialization state */
    RTKSW_CHK_INIT_STATE(unit);

    /* Check Port Valid */
    RTKSW_CHK_PORT_IS_UTP(unit, port);

    if ((retVal = _dal_rtl8367d_getAsicPHYReg(unit, rtksw_switch_port_L2P_get(unit, port), reg, pData)) != RT_ERR_OK)
        return retVal;

    return RT_ERR_OK;
}


/* Function Name:
 *      dal_rtl8367d_port_phyOCPReg_set
 * Description:
 *      Set PHY OCP register
 * Input:
 *      unit        - Unit ID
 *      port        - PHY ID
 *      ocpAddr     - OCP register address
 *      ocpData     - OCP Data.
 * Output:
 *      None.
 * Return:
 *      RT_ERR_OK                               - OK
 *      RT_ERR_FAILED                           - Failed
 *      RT_ERR_BUSYWAIT_TIMEOUT                 - Timeout
 * Note:
 *      None.
 */
rtksw_api_ret_t dal_rtl8367d_port_phyOCPReg_set(rtksw_uint32 unit, rtksw_port_t port, rtksw_uint32 ocpAddr, rtksw_uint32 ocpData )
{
    rtksw_api_ret_t retVal;

    /* Check initialization state */
    RTKSW_CHK_INIT_STATE(unit);

    /* Check Port Valid */
    RTKSW_CHK_PORT_IS_UTP(unit, port);

    if ((retVal = _dal_rtl8367d_setAsicPHYOCPReg(unit, rtksw_switch_port_L2P_get(unit, port), ocpAddr, ocpData)) != RT_ERR_OK)
        return retVal;

    return RT_ERR_OK;
}

/* Function Name:
 *      dal_rtl8367d_port_phyOCPReg_get
 * Description:
 *      Set PHY OCP register
 * Input:
 *      unit        - Unit ID
 *      phyNo       - PHY ID
 *      ocpAddr     - OCP register address
 * Output:
 *      pRegData    - OCP data.
 * Return:
 *      RT_ERR_OK                               - OK
 *      RT_ERR_FAILED                           - Failed
 *      RT_ERR_NULL_POINTER                     - Null pointer
 * Note:
 *      None.
 */
rtksw_api_ret_t dal_rtl8367d_port_phyOCPReg_get(rtksw_uint32 unit, rtksw_port_t port, rtksw_uint32 ocpAddr, rtksw_uint32 *pRegData )
{
    rtksw_api_ret_t retVal;

    /* Check initialization state */
    RTKSW_CHK_INIT_STATE(unit);

    /* Check Port Valid */
    RTKSW_CHK_PORT_IS_UTP(unit, port);

    if (pRegData == NULL)
        return RT_ERR_NULL_POINTER;

    if ((retVal = _dal_rtl8367d_getAsicPHYOCPReg(unit, rtksw_switch_port_L2P_get(unit, port), ocpAddr, pRegData)) != RT_ERR_OK)
        return retVal;

    return RT_ERR_OK;
}


/* Function Name:
 *      dal_rtl8367d_port_backpressureEnable_set
 * Description:
 *      Set the half duplex backpressure enable status of the specific port.
 * Input:
 *      unit        - Unit ID
 *      port        - port id.
 *      enable      - Back pressure status.
 * Output:
 *      None
 * Return:
 *      RT_ERR_OK           - OK
 *      RT_ERR_FAILED       - Failed
 *      RT_ERR_SMI          - SMI access error
 *      RT_ERR_PORT_ID      - Invalid port number.
 *      RT_ERR_ENABLE       - Invalid enable input.
 * Note:
 *      This API can set the half duplex backpressure enable status of the specific port.
 *      The half duplex backpressure enable status of the port is as following:
 *      - DISABLE(Defer)
 *      - ENABLE (Backpressure)
 */
rtksw_api_ret_t dal_rtl8367d_port_backpressureEnable_set(rtksw_uint32 unit, rtksw_port_t port, rtksw_enable_t enable)
{
    rtksw_api_ret_t retVal;

    /* Check initialization state */
    RTKSW_CHK_INIT_STATE(unit);

    if (port != RTKSW_WHOLE_SYSTEM)
        return RT_ERR_PORT_ID;

    if (enable >= RTKSW_ENABLE_END)
        return RT_ERR_INPUT;

    if ((retVal = rtl8367d_setAsicRegBit(unit, RTL8367D_REG_CFG_BACKPRESSURE, RTL8367D_LONGTXE_OFFSET, (enable == RTKSW_ENABLED) ? 0 : 1)) != RT_ERR_OK)
        return retVal;

    return RT_ERR_OK;
}

/* Function Name:
 *      dal_rtl8367d_port_backpressureEnable_get
 * Description:
 *      Get the half duplex backpressure enable status of the specific port.
 * Input:
 *      unit        - Unit ID
 *      port        - Port id.
 * Output:
 *      pEnable - Back pressure status.
 * Return:
 *      RT_ERR_OK           - OK
 *      RT_ERR_FAILED       - Failed
 *      RT_ERR_SMI          - SMI access error
 *      RT_ERR_PORT_ID      - Invalid port number.
 * Note:
 *      This API can get the half duplex backpressure enable status of the specific port.
 *      The half duplex backpressure enable status of the port is as following:
 *      - DISABLE(Defer)
 *      - ENABLE (Backpressure)
 */
rtksw_api_ret_t dal_rtl8367d_port_backpressureEnable_get(rtksw_uint32 unit, rtksw_port_t port, rtksw_enable_t *pEnable)
{
    rtksw_api_ret_t retVal;
    rtksw_uint32 regData;

    /* Check initialization state */
    RTKSW_CHK_INIT_STATE(unit);

    if (port != RTKSW_WHOLE_SYSTEM)
        return RT_ERR_PORT_ID;

    if(NULL == pEnable)
        return RT_ERR_NULL_POINTER;

    if ((retVal = rtl8367d_getAsicRegBit(unit, RTL8367D_REG_CFG_BACKPRESSURE, RTL8367D_LONGTXE_OFFSET, &regData)) != RT_ERR_OK)
        return retVal;

    *pEnable = (regData == 1) ? RTKSW_DISABLED : RTKSW_ENABLED;
    return RT_ERR_OK;
}

/* Function Name:
 *      dal_rtl8367d_port_adminEnable_set
 * Description:
 *      Set port admin configuration of the specific port.
 * Input:
 *      unit        - Unit ID
 *      port        - port id.
 *      enable      - Back pressure status.
 * Output:
 *      None
 * Return:
 *      RT_ERR_OK           - OK
 *      RT_ERR_FAILED       - Failed
 *      RT_ERR_SMI          - SMI access error
 *      RT_ERR_PORT_ID      - Invalid port number.
 *      RT_ERR_ENABLE       - Invalid enable input.
 * Note:
 *      This API can set port admin configuration of the specific port.
 *      The port admin configuration of the port is as following:
 *      - DISABLE
 *      - ENABLE
 */
rtksw_api_ret_t dal_rtl8367d_port_adminEnable_set(rtksw_uint32 unit, rtksw_port_t port, rtksw_enable_t enable)
{
    rtksw_api_ret_t retVal;
    rtksw_uint32      data;

    /* Check initialization state */
    RTKSW_CHK_INIT_STATE(unit);

    /* Check Port Valid */
    RTKSW_CHK_PORT_IS_UTP(unit, port);

    if (enable >= RTKSW_ENABLE_END)
        return RT_ERR_INPUT;

    if ((retVal = _dal_rtl8367d_getAsicPHYReg(unit, rtksw_switch_port_L2P_get(unit, port), PHY_CONTROL_REG, &data)) != RT_ERR_OK)
        return retVal;

    if (RTKSW_ENABLED == enable)
    {
        data &= 0xF7FF;
        data |= 0x0200;
    }
    else if (RTKSW_DISABLED == enable)
    {
        data |= 0x0800;
    }

    if ((retVal = _dal_rtl8367d_setAsicPHYReg(unit, rtksw_switch_port_L2P_get(unit, port), PHY_CONTROL_REG, data)) != RT_ERR_OK)
        return retVal;

    return RT_ERR_OK;
}

/* Function Name:
 *      dal_rtl8367d_port_adminEnable_get
 * Description:
 *      Get port admin configurationof the specific port.
 * Input:
 *      unit        - Unit ID
 *      port        - Port id.
 * Output:
 *      pEnable - Back pressure status.
 * Return:
 *      RT_ERR_OK           - OK
 *      RT_ERR_FAILED       - Failed
 *      RT_ERR_SMI          - SMI access error
 *      RT_ERR_PORT_ID      - Invalid port number.
 * Note:
 *      This API can get port admin configuration of the specific port.
 *      The port admin configuration of the port is as following:
 *      - DISABLE
 *      - ENABLE
 */
rtksw_api_ret_t dal_rtl8367d_port_adminEnable_get(rtksw_uint32 unit, rtksw_port_t port, rtksw_enable_t *pEnable)
{
    rtksw_api_ret_t retVal;
    rtksw_uint32      data;

    /* Check initialization state */
    RTKSW_CHK_INIT_STATE(unit);

    /* Check Port Valid */
    RTKSW_CHK_PORT_IS_UTP(unit, port);

    if(NULL == pEnable)
        return RT_ERR_NULL_POINTER;

    if ((retVal = _dal_rtl8367d_getAsicPHYReg(unit, port, PHY_CONTROL_REG, &data)) != RT_ERR_OK)
        return retVal;

    if ( (data & 0x0800) == 0x0800)
    {
        *pEnable = RTKSW_DISABLED;
    }
    else
    {
        *pEnable = RTKSW_ENABLED;
    }

    return RT_ERR_OK;
}

/* Function Name:
 *      dal_rtl8367d_port_isolation_set
 * Description:
 *      Set permitted port isolation portmask
 * Input:
 *      unit        - Unit ID
 *      port        - port id.
 *      pPortmask   - Permit port mask
 * Output:
 *      None
 * Return:
 *      RT_ERR_OK           - OK
 *      RT_ERR_FAILED       - Failed
 *      RT_ERR_SMI          - SMI access error
 *      RT_ERR_PORT_ID      - Invalid port number.
 *      RT_ERR_PORT_MASK    - Invalid portmask.
 * Note:
 *      This API set the port mask that a port can trasmit packet to of each port
 *      A port can only transmit packet to ports included in permitted portmask
 */
rtksw_api_ret_t dal_rtl8367d_port_isolation_set(rtksw_uint32 unit, rtksw_port_t port, rtksw_portmask_t *pPortmask)
{
    rtksw_api_ret_t retVal;
    rtksw_uint32 pmask;

    /* Check initialization state */
    RTKSW_CHK_INIT_STATE(unit);

    /* Check Port Valid */
    RTKSW_CHK_PORT_VALID(unit, port);

    if(NULL == pPortmask)
        return RT_ERR_NULL_POINTER;

    /* check port mask */
    RTKSW_CHK_PORTMASK_VALID(unit, pPortmask);

    if ((retVal = rtksw_switch_portmask_L2P_get(unit, pPortmask, &pmask)) != RT_ERR_OK)
        return retVal;

    if ((retVal = rtl8367d_setAsicReg(unit, RTL8367D_REG_PORT_ISOLATION_PORT0_MASK + rtksw_switch_port_L2P_get(unit, port), pmask)) != RT_ERR_OK)
        return retVal;

    return RT_ERR_OK;
}

/* Function Name:
 *      dal_rtl8367d_port_isolation_get
 * Description:
 *      Get permitted port isolation portmask
 * Input:
 *      unit        - Unit ID
 *      port        - Port id.
 * Output:
 *      pPortmask - Permit port mask
 * Return:
 *      RT_ERR_OK           - OK
 *      RT_ERR_FAILED       - Failed
 *      RT_ERR_SMI          - SMI access error
 *      RT_ERR_PORT_ID      - Invalid port number.
 * Note:
 *      This API get the port mask that a port can trasmit packet to of each port
 *      A port can only transmit packet to ports included in permitted portmask
 */
rtksw_api_ret_t dal_rtl8367d_port_isolation_get(rtksw_uint32 unit, rtksw_port_t port, rtksw_portmask_t *pPortmask)
{
    rtksw_api_ret_t retVal;
    rtksw_uint32 pmask;

    /* Check initialization state */
    RTKSW_CHK_INIT_STATE(unit);

    /* Check Port Valid */
    RTKSW_CHK_PORT_VALID(unit, port);

    if(NULL == pPortmask)
        return RT_ERR_NULL_POINTER;

    if ((retVal = rtl8367d_getAsicReg(unit, RTL8367D_REG_PORT_ISOLATION_PORT0_MASK + rtksw_switch_port_L2P_get(unit, port), &pmask)) != RT_ERR_OK)
        return retVal;

    if ((retVal = rtksw_switch_portmask_P2L_get(unit, pmask, pPortmask)) != RT_ERR_OK)
        return retVal;

    return RT_ERR_OK;
}

/* Function Name:
 *      dal_rtl8367d_port_rgmiiDelayExt_set
 * Description:
 *      Set RGMII interface delay value for TX and RX.
 * Input:
 *      unit        - Unit ID
 *      txDelay     - TX delay value, 1 for delay 2ns and 0 for no-delay
 *      rxDelay     - RX delay value, 0~7 for delay setup.
 * Output:
 *      None
 * Return:
 *      RT_ERR_OK           - OK
 *      RT_ERR_FAILED       - Failed
 *      RT_ERR_SMI          - SMI access error
 *      RT_ERR_INPUT        - Invalid input parameters.
 * Note:
 *      This API can set external interface 2 RGMII delay.
 *      In TX delay, there are 2 selection: no-delay and 2ns delay.
 *      In RX dekay, there are 8 steps for delay tunning. 0 for no-delay, and 7 for maximum delay.
 *      Note. This API should be called before rtksw_port_macForceLinkExt_set().
 */
rtksw_api_ret_t dal_rtl8367d_port_rgmiiDelayExt_set(rtksw_uint32 unit, rtksw_port_t port, rtksw_data_t txDelay, rtksw_data_t rxDelay)
{
    rtksw_api_ret_t retVal;
    rtksw_uint32 regData;

    /* Check initialization state */
    RTKSW_CHK_INIT_STATE(unit);

    /* Check Port Valid */
    if ((port != EXT_PORT1) && (port != UTP_PORT4))
        return RT_ERR_PORT_ID;

    if ((txDelay > 1) || (rxDelay > 7))
        return RT_ERR_INPUT;

    if ((retVal = rtl8367d_getAsicReg(unit, RTL8367D_REG_EXT1_RGMXF, &regData)) != RT_ERR_OK)
        return retVal;

    regData = (regData & 0xFFF0) | ((txDelay << 3) & 0x0008) | (rxDelay & 0x0007);

    if ((retVal = rtl8367d_setAsicReg(unit, RTL8367D_REG_EXT1_RGMXF, regData)) != RT_ERR_OK)
        return retVal;

    return RT_ERR_OK;
}

/* Function Name:
 *      dal_rtl8367d_port_rgmiiDelayExt_get
 * Description:
 *      Get RGMII interface delay value for TX and RX.
 * Input:
 *      unit        - Unit ID
 * Output:
 *      pTxDelay - TX delay value
 *      pRxDelay - RX delay value
 * Return:
 *      RT_ERR_OK           - OK
 *      RT_ERR_FAILED       - Failed
 *      RT_ERR_SMI          - SMI access error
 *      RT_ERR_INPUT        - Invalid input parameters.
 * Note:
 *      This API can set external interface 2 RGMII delay.
 *      In TX delay, there are 2 selection: no-delay and 2ns delay.
 *      In RX dekay, there are 8 steps for delay tunning. 0 for n0-delay, and 7 for maximum delay.
 */
rtksw_api_ret_t dal_rtl8367d_port_rgmiiDelayExt_get(rtksw_uint32 unit, rtksw_port_t port, rtksw_data_t *pTxDelay, rtksw_data_t *pRxDelay)
{
    rtksw_api_ret_t retVal;
    rtksw_uint32 regData;

    /* Check initialization state */
    RTKSW_CHK_INIT_STATE(unit);

    /* Check Port Valid */
    if ((port != EXT_PORT1) && (port != UTP_PORT4))
        return RT_ERR_PORT_ID;

    if( (NULL == pTxDelay) || (NULL == pRxDelay) )
        return RT_ERR_NULL_POINTER;

    if ((retVal = rtl8367d_getAsicReg(unit, RTL8367D_REG_EXT1_RGMXF, &regData)) != RT_ERR_OK)
        return retVal;

    *pTxDelay = (regData & 0x0008) >> 3;
    *pRxDelay = regData & 0x0007;

    return RT_ERR_OK;
}

/* Function Name:
 *      dal_rtl8367d_port_phyEnableAll_set
 * Description:
 *      Set all PHY enable status.
 * Input:
 *      unit        - Unit ID
 *      enable      - PHY Enable State.
 * Output:
 *      None
 * Return:
 *      RT_ERR_OK           - OK
 *      RT_ERR_FAILED       - Failed
 *      RT_ERR_SMI          - SMI access error
 *      RT_ERR_ENABLE       - Invalid enable input.
 * Note:
 *      This API can set all PHY status.
 *      The configuration of all PHY is as following:
 *      - DISABLE
 *      - ENABLE
 */
rtksw_api_ret_t dal_rtl8367d_port_phyEnableAll_set(rtksw_uint32 unit, rtksw_enable_t enable)
{
    rtksw_api_ret_t retVal;
    rtksw_uint32 data;
    rtksw_uint32 port;

    /* Check initialization state */
    RTKSW_CHK_INIT_STATE(unit);

    if (enable >= RTKSW_ENABLE_END)
        return RT_ERR_ENABLE;

    RTKSW_SCAN_ALL_LOG_PORT(unit, port)
    {
        if(rtksw_switch_isUtpPort(unit, port) == RT_ERR_OK)
        {
            if ((retVal = _dal_rtl8367d_getAsicPHYReg(unit, port, PHY_CONTROL_REG, &data)) != RT_ERR_OK)
                return retVal;

            if (RTKSW_ENABLED == enable)
            {
                data &= 0xF7FF;
                data |= 0x0200;
            }
            else
            {
                data |= 0x0800;
            }

            if ((retVal = _dal_rtl8367d_setAsicPHYReg(unit, port, PHY_CONTROL_REG, data)) != RT_ERR_OK)
                return retVal;
        }
    }

    return RT_ERR_OK;

}

/* Function Name:
 *      dal_rtl8367d_port_phyEnableAll_get
 * Description:
 *      Get all PHY enable status.
 * Input:
 *      unit        - Unit ID
 * Output:
 *      pEnable - PHY Enable State.
 * Return:
 *      RT_ERR_OK           - OK
 *      RT_ERR_FAILED       - Failed
 *      RT_ERR_SMI          - SMI access error
 * Note:
 *      This API can set all PHY status.
 *      The configuration of all PHY is as following:
 *      - DISABLE
 *      - ENABLE
 */
rtksw_api_ret_t dal_rtl8367d_port_phyEnableAll_get(rtksw_uint32 unit, rtksw_enable_t *pEnable)
{
    rtksw_api_ret_t retVal;
    rtksw_uint32 data;
    rtksw_uint32 port;

    /* Check initialization state */
    RTKSW_CHK_INIT_STATE(unit);

    if(NULL == pEnable)
        return RT_ERR_NULL_POINTER;

    RTKSW_SCAN_ALL_LOG_PORT(unit, port)
    {
        if(rtksw_switch_isUtpPort(unit, port) == RT_ERR_OK)
        {
            if ((retVal = _dal_rtl8367d_getAsicPHYReg(unit, port, PHY_CONTROL_REG, &data)) != RT_ERR_OK)
                return retVal;

            if (data & 0x0800)
            {
                *pEnable = RTKSW_DISABLED;
                return RT_ERR_OK;
            }
        }
    }

    *pEnable = RTKSW_ENABLED;
    return RT_ERR_OK;
}

/* Function Name:
 *      dal_rtl8367d_port_phyComboPortMedia_set
 * Description:
 *      Set Combo port media type
 * Input:
 *      unit        - Unit ID
 *      port        - Port id.
 *      media       - Media (COPPER or FIBER or AUTO)
 * Output:
 *      None.
 * Return:
 *      RT_ERR_OK               - OK
 *      RT_ERR_FAILED           - Failed
 *      RT_ERR_SMI              - SMI access error
 *      RT_ERR_INPUT            - Invalid input parameters.
 *      RT_ERR_PORT_ID          - Invalid port ID.
 * Note:
 *      The API can Set Combo port media type.
 */
rtksw_api_ret_t dal_rtl8367d_port_phyComboPortMedia_set(rtksw_uint32 unit, rtksw_port_t port, rtksw_port_media_t media)
{
    rtksw_api_ret_t retVal;
    rtksw_uint32 i;
    rtksw_uint32 mux;
    rtksw_port_media_t currentMedia;
    rtksw_uint32 regData;

    /* Check initialization state */
    RTKSW_CHK_INIT_STATE(unit);

    /* Check Port Valid */
    RTKSW_CHK_PORT_IS_UTP(unit, port);

    /* Check Combo Port ID */
    RTKSW_CHK_PORT_IS_COMBO(unit, port);

    if ((retVal = dal_rtl8367d_port_phyComboPortMedia_get(unit, port, &currentMedia)) != RT_ERR_OK)
        return retVal;

    if (media == currentMedia)
        return RT_ERR_OK;

    /* if SDS0 used by EXT_PORT0, can't configure combo = Fiber*/
    if (media == RTKSW_PORT_MEDIA_FIBER)
    {
        if( (retVal = rtl8367d_getAsicRegBits(unit, RTL8367D_REG_SDS_MISC, RTL8367D_CFG_SDS_MODE_MASK, &regData)) != RT_ERR_OK)
            return retVal;

        if (regData != RTL8367D_PORT_SDS_MODE_DISABLE)
            return RT_ERR_INPUT;
    }

    /* Different media type, always set to copper then set to new media type */
    if (currentMedia == RTKSW_PORT_MEDIA_FIBER)
    {
        if( (retVal = rtl8367d_setAsicRegBits(unit, RTL8367D_REG_FIBER_CFG_2, RTL8367D_SDS_RX_DISABLE_MASK, 0)) != RT_ERR_OK)
            return retVal;

        if( (retVal = rtl8367d_setAsicRegBit(unit, RTL8367D_REG_SDS_MISC, RTL8367D_PA12PC_EN_S0_OFFSET, 0)) != RT_ERR_OK)
            return retVal;

        if( (retVal = rtl8367d_setAsicRegBit(unit, RTL8367D_REG_SDS_MISC, RTL8367D_PA33PC_EN_S0_OFFSET, 0)) != RT_ERR_OK)
            return retVal;

        if( (retVal = rtl8367d_setAsicRegBits(unit, RTL8367D_REG_SDS_MISC, RTL8367D_CFG_SDS_MODE_MASK, RTL8367D_PORT_SDS_MODE_DISABLE)) != RT_ERR_OK)
           return retVal;

        /* Clear Fiber mux setting */
        if( (retVal = rtl8367d_setAsicRegBits(unit, RTL8367D_REG_UTP_FIB_DET, RTL8367D_FORCE_SEL_FIBER_MASK, 0)) != RT_ERR_OK)
            return retVal;

        /* Clear Force Link down MAC6 setting */
        if ((retVal = rtl8367d_setAsicReg(unit, RTL8367D_REG_MAC6_FORCE_SELECT, 0x0000)) != RT_ERR_OK)
           return retVal;

        if ((retVal = rtl8367d_setAsicReg(unit, RTL8367D_REG_MAC6_FORCE_SELECT_EN, 0x0000)) != RT_ERR_OK)
           return retVal;
    }
    else if (currentMedia == RTKSW_PORT_MEDIA_RGMII)
    {
        /* Disable RGMII */
        if ((retVal = rtl8367d_setAsicRegBits(unit, RTL8367D_REG_DIGITAL_INTERFACE_SELECT, RTL8367D_SELECT_GMII_1_MASK, 0)) != RT_ERR_OK)
            return retVal;

        /* Clear MAC4 force ability */
        if ((retVal = rtl8367d_setAsicReg(unit, RTL8367D_REG_MAC4_FORCE_SELECT, 0)) != RT_ERR_OK)
            return retVal;

        if ((retVal = rtl8367d_setAsicReg(unit, RTL8367D_REG_MAC4_FORCE_SELECT_EN, 0)) != RT_ERR_OK)
            return retVal;

        /* Clear RGMII/MII mux setting */
        if ((retVal = rtl8367d_setAsicRegBit(unit, RTL8367D_REG_TOP_CON0, RTL8367D_MAC4_SEL_EXT1_OFFSET, 0)) != RT_ERR_OK)
            return retVal;
    }

    /* Configure new medida type */
    if(media == RTKSW_PORT_MEDIA_FIBER)
    {
        for(i = 0; i < sizeof(Fiber1000M100MCfg) / (sizeof(rtksw_uint32) * 2); i++)
        {
            if( (retVal = rtl8367d_setAsicReg(unit, RTL8367D_REG_SDS_INDACS_DATA, Fiber1000M100MCfg[i][1])) != RT_ERR_OK)
                return retVal;

            if( (retVal = rtl8367d_setAsicReg(unit, RTL8367D_REG_SDS_INDACS_ADR, Fiber1000M100MCfg[i][0])) != RT_ERR_OK)
                return retVal;

            if( (retVal = rtl8367d_setAsicReg(unit, RTL8367D_REG_SDS_INDACS_CMD, 0x00CD)) != RT_ERR_OK)
                return retVal;
        }

        if( (retVal = rtl8367d_setAsicRegBits(unit, RTL8367D_REG_FIBER_CFG_2, RTL8367D_SDS_RX_DISABLE_MASK, 1)) != RT_ERR_OK)
            return retVal;

        if( (retVal = rtl8367d_setAsicRegBits(unit, RTL8367D_REG_UTP_FIB_DET, RTL8367D_FORCE_SEL_FIBER_MASK, 0x3)) != RT_ERR_OK)
            return retVal;

        if( (retVal = rtl8367d_setAsicRegBit(unit, RTL8367D_REG_SDS_MISC, RTL8367D_PA12PC_EN_S0_OFFSET, 1)) != RT_ERR_OK)
            return retVal;

        if( (retVal = rtl8367d_setAsicRegBit(unit, RTL8367D_REG_SDS_MISC, RTL8367D_PA33PC_EN_S0_OFFSET, 1)) != RT_ERR_OK)
            return retVal;

        if( (retVal = rtl8367d_setAsicRegBit(unit, RTL8367D_REG_SDS_MISC, RTL8367D_MAC6_SEL_SDS0_OFFSET, 0)) != RT_ERR_OK)
            return retVal;

        if( (retVal = rtl8367d_setAsicRegBits(unit, RTL8367D_REG_SDS_MISC, RTL8367D_CFG_SDS_MODE_MASK, RTL8367D_PORT_SDS_MODE_1000X_100FX)) != RT_ERR_OK)
           return retVal;

        /* Force Link down MAC6 */
        if ((retVal = rtl8367d_setAsicReg(unit, RTL8367D_REG_MAC6_FORCE_SELECT, 0x0000)) != RT_ERR_OK)
           return retVal;

        if ((retVal = rtl8367d_setAsicReg(unit, RTL8367D_REG_MAC6_FORCE_SELECT_EN, 0xFFFF)) != RT_ERR_OK)
           return retVal;

    }
    else if(media == RTKSW_PORT_MEDIA_RGMII)
    {
        /* Make sure RGMII/MII mux is not at port 7 */
        if ((retVal = rtl8367d_getAsicRegBit(unit, RTL8367D_REG_TOP_CON0, RTL8367D_MAC7_SEL_EXT1_OFFSET, &mux)) != RT_ERR_OK)
            return retVal;

        if (mux == 1)
            return RT_ERR_INPUT;

        /* Configure RGMII DP, DN, E2, MODE */
        if ((retVal = rtl8367d_setAsicRegBit(unit, RTL8367D_REG_CHIP_DEBUG0, RTL8367D_SEL33_EXT1_OFFSET, 1)) != RT_ERR_OK)
            return retVal;

        if ((retVal = rtl8367d_setAsicRegBit(unit, RTL8367D_REG_CHIP_DEBUG0, RTL8367D_DRI_EXT1_RG_OFFSET, 1)) != RT_ERR_OK)
            return retVal;

        if ((retVal = rtl8367d_setAsicRegBit(unit, RTL8367D_REG_CHIP_DEBUG0, RTL8367D_DRI_EXT1_OFFSET, 1)) != RT_ERR_OK)
            return retVal;

        if ((retVal = rtl8367d_setAsicRegBit(unit, RTL8367D_REG_CHIP_DEBUG0, RTL8367D_SLR_EXT1_OFFSET, 1)) != RT_ERR_OK)
            return retVal;

        if ((retVal = rtl8367d_setAsicRegBits(unit, RTL8367D_REG_CHIP_DEBUG1, RTL8367D_RG1_DN_MASK, 7)) != RT_ERR_OK)
            return retVal;

        if ((retVal = rtl8367d_setAsicRegBits(unit, RTL8367D_REG_CHIP_DEBUG1, RTL8367D_RG1_DP_MASK, 5)) != RT_ERR_OK)
            return retVal;

        /* Configure RGMII/MII mux to port 4 */
        if ((retVal = rtl8367d_setAsicRegBit(unit, RTL8367D_REG_TOP_CON0, RTL8367D_MAC4_SEL_EXT1_OFFSET, 1)) != RT_ERR_OK)
            return retVal;

        if ((retVal = rtl8367d_setAsicRegBits(unit, RTL8367D_REG_DIGITAL_INTERFACE_SELECT, RTL8367D_SELECT_GMII_1_MASK, 1)) != RT_ERR_OK)
            return retVal;
    }
    else if (media == RTKSW_PORT_MEDIA_COPPER)
    {
        /* Do nothing */
    }
    else
        return RT_ERR_INPUT;

    return RT_ERR_OK;
}

/* Function Name:
 *      dal_rtl8367d_port_phyComboPortMedia_get
 * Description:
 *      Get Combo port media type
 * Input:
 *      unit        - Unit ID
 *      port        - Port id.
 * Output:
 *      pMedia  - Media (COPPER or FIBER or AUTO)
 * Return:
 *      RT_ERR_OK               - OK
 *      RT_ERR_FAILED           - Failed
 *      RT_ERR_SMI              - SMI access error
 *      RT_ERR_INPUT            - Invalid input parameters.
 *      RT_ERR_PORT_ID          - Invalid port ID.
 * Note:
 *      The API can Set Combo port media type.
 */
rtksw_api_ret_t dal_rtl8367d_port_phyComboPortMedia_get(rtksw_uint32 unit, rtksw_port_t port, rtksw_port_media_t *pMedia)
{
    rtksw_api_ret_t   retVal;
    rtksw_uint32      data;

    /* Check initialization state */
    RTKSW_CHK_INIT_STATE(unit);

    /* Check Port Valid */
    RTKSW_CHK_PORT_IS_UTP(unit, port);

    /* Check Combo Port ID */
    RTKSW_CHK_PORT_IS_COMBO(unit, port);

    if ((retVal = rtl8367d_getAsicRegBit(unit, RTL8367D_REG_TOP_CON0, RTL8367D_MAC4_SEL_EXT1_OFFSET, &data)) != RT_ERR_OK)
        return retVal;

    if (data == 1)
        *pMedia = RTKSW_PORT_MEDIA_RGMII;
    else
    {
        if( (retVal = rtl8367d_getAsicRegBits(unit, RTL8367D_REG_UTP_FIB_DET, RTL8367D_FORCE_SEL_FIBER_MASK, &data)) != RT_ERR_OK)
            return retVal;

        if (data == 3)
            *pMedia = RTKSW_PORT_MEDIA_FIBER;
        else
            *pMedia = RTKSW_PORT_MEDIA_COPPER;
    }

    return RT_ERR_OK;
}

/* Function Name:
 *      dal_rtl8367d_port_rtctEnable_set
 * Description:
 *      Enable RTCT test
 * Input:
 *      unit        - Unit ID
 *      pPortmask   - Port mask of RTCT enabled port
 * Output:
 *      None
 * Return:
 *      RT_ERR_OK               - OK
 *      RT_ERR_FAILED           - Failed
 *      RT_ERR_SMI              - SMI access error
 *      RT_ERR_PORT_MASK        - Invalid port mask.
 * Note:
 *      The API can enable RTCT Test
 */
rtksw_api_ret_t dal_rtl8367d_port_rtctEnable_set(rtksw_uint32 unit, rtksw_portmask_t *pPortmask)
{
    rtksw_api_ret_t retVal;

    /* Check initialization state */
    RTKSW_CHK_INIT_STATE(unit);

    switch (rtksw_switch_chipType_get(unit))
    {
        case CHIP_RTL8367D:
            if ((retVal = _dal_rtl8367d_port_rtctEnable_set(unit, pPortmask)) != RT_ERR_OK)
                return retVal;
            break;
        case CHIP_RTL8367E:
            if ((retVal = _dal_rtl8367e_port_rtctEnable_set(unit, pPortmask)) != RT_ERR_OK)
                return retVal;
            break;
        default:
            return RT_ERR_FAILED;
    }

    return RT_ERR_OK;
}

/* Function Name:
 *      dal_rtl8367d_port_rtctDisable_set
 * Description:
 *      Disable RTCT test
 * Input:
 *      unit        - Unit ID
 *      pPortmask   - Port mask of RTCT disabled port
 * Output:
 *      None
 * Return:
 *      RT_ERR_OK               - OK
 *      RT_ERR_FAILED           - Failed
 *      RT_ERR_SMI              - SMI access error
 *      RT_ERR_PORT_MASK        - Invalid port mask.
 * Note:
 *      The API can disable RTCT Test
 */
rtksw_api_ret_t dal_rtl8367d_port_rtctDisable_set(rtksw_uint32 unit, rtksw_portmask_t *pPortmask)
{
    rtksw_api_ret_t retVal;

    /* Check initialization state */
    RTKSW_CHK_INIT_STATE(unit);

    switch (rtksw_switch_chipType_get(unit))
    {
        case CHIP_RTL8367D:
            if ((retVal = _dal_rtl8367d_port_rtctDisable_set(unit, pPortmask)) != RT_ERR_OK)
                return retVal;
            break;
        case CHIP_RTL8367E:
            return RT_ERR_CHIP_NOT_SUPPORTED;
            break;
        default:
            return RT_ERR_FAILED;
    }

    return RT_ERR_OK;
}

/* Function Name:
 *      dal_rtl8367d_port_rtctResult_get
 * Description:
 *      Get the result of RTCT test
 * Input:
 *      unit        - Unit ID
 *      port        - Port ID
 * Output:
 *      pRtctResult - The result of RTCT result
 * Return:
 *      RT_ERR_OK                   - OK
 *      RT_ERR_FAILED               - Failed
 *      RT_ERR_SMI                  - SMI access error
 *      RT_ERR_PORT_ID              - Invalid port ID.
 *      RT_ERR_PHY_RTCT_NOT_FINISH  - Testing does not finish.
 * Note:
 *      The API can get RTCT test result.
 *      RTCT test may takes 4.8 seconds to finish its test at most.
 *      Thus, if this API return RT_ERR_PHY_RTCT_NOT_FINISH or
 *      other error code, the result can not be referenced and
 *      user should call this API again until this API returns
 *      a RT_ERR_OK.
 *      The result is stored at pRtctResult->ge_result
 *      pRtctResult->linkType is unused.
 *      The unit of channel length is 2.5cm. Ex. 300 means 300 * 2.5 = 750cm = 7.5M
 */
rtksw_api_ret_t dal_rtl8367d_port_rtctResult_get(rtksw_uint32 unit, rtksw_port_t port, rtksw_rtctResult_t *pRtctResult)
{
    rtksw_api_ret_t retVal;

    /* Check initialization state */
    RTKSW_CHK_INIT_STATE(unit);

    switch (rtksw_switch_chipType_get(unit))
    {
        case CHIP_RTL8367D:
            if ((retVal = _dal_rtl8367d_port_rtctResult_get(unit, port, pRtctResult)) != RT_ERR_OK)
                return retVal;
            break;
        case CHIP_RTL8367E:
            if ((retVal = _dal_rtl8367e_port_rtctResult_get(unit, port, pRtctResult)) != RT_ERR_OK)
                return retVal;
            break;
        default:
            return RT_ERR_FAILED;
    }

    return RT_ERR_OK;
}

/* Function Name:
 *      dal_rtl8367d_port_sds_reset
 * Description:
 *      Reset Serdes
 * Input:
 *      unit        - Unit ID
 *      port        - Port ID
 * Output:
 *      None.
 * Return:
 *      RT_ERR_OK                   - OK
 *      RT_ERR_FAILED               - Failed
 *      RT_ERR_SMI                  - SMI access error
 *      RT_ERR_PORT_ID              - Invalid port ID.
 * Note:
 *      The API can reset Serdes
 */
rtksw_api_ret_t dal_rtl8367d_port_sds_reset(rtksw_uint32 unit, rtksw_port_t port)
{
    rtksw_api_ret_t retVal;
    rtksw_api_ret_t retVal2;
    rtksw_uint32 running;

    /* Check initialization state */
    RTKSW_CHK_INIT_STATE(unit);

    /* Check Port Valid */
    if(rtksw_switch_isSgmiiPort(unit, port) != RT_ERR_OK)
        return RT_ERR_PORT_ID;

    if ((retVal = rtl8367d_getAsicRegBit(unit, 0x130c, 5, &running))!=RT_ERR_OK)
        return retVal;

    if (running == 1)
    {
        if ((retVal = rtl8367d_setAsicRegBit(unit, 0x130c, 5, 0))!=RT_ERR_OK)
            return retVal;
    }

    retVal = _dal_rtl8367d_port_sds_reset(unit, port);

    if (running == 1)
    {
        if ((retVal2 = rtl8367d_setAsicRegBit(unit, 0x130c, 5, 1))!=RT_ERR_OK)
            return retVal2;
    }

    return retVal;
}


/* Function Name:
 *      dal_rtl8367d_port_sgmiiLinkStatus_get
 * Description:
 *      Get SGMII status
 * Input:
 *      unit        - Unit ID
 *      port        - Port ID
 * Output:
 *      pSignalDetect   - Signal detect
 *      pSync           - Sync
 *      pLink           - Link
 * Return:
 *      RT_ERR_OK                   - OK
 *      RT_ERR_FAILED               - Failed
 *      RT_ERR_SMI                  - SMI access error
 *      RT_ERR_PORT_ID              - Invalid port ID.
 * Note:
 *      The API can reset Serdes
 */
rtksw_api_ret_t dal_rtl8367d_port_sgmiiLinkStatus_get(rtksw_uint32 unit, rtksw_port_t port, rtksw_data_t *pSignalDetect, rtksw_data_t *pSync, rtksw_port_linkStatus_t *pLink)
{
    rtksw_api_ret_t retVal, retVal2;
    rtksw_uint32 running;

    /* Check initialization state */
    RTKSW_CHK_INIT_STATE(unit);

    if ((retVal = rtl8367d_getAsicRegBit(unit, 0x130c, 5, &running))!=RT_ERR_OK)
        return retVal;

    if (running == 1)
    {
        if ((retVal = rtl8367d_setAsicRegBit(unit, 0x130c, 5, 0))!=RT_ERR_OK)
            return retVal;
    }

    retVal = _dal_rtl8367d_port_sgmiiLinkStatus_get(unit, port, pSignalDetect, pSync, pLink);

    if (running == 1)
    {
        if ((retVal2 = rtl8367d_setAsicRegBit(unit, 0x130c, 5, 1))!=RT_ERR_OK)
            return retVal2;
    }

    return retVal;
}

/* Function Name:
 *      dal_rtl8367d_port_sgmiiNway_set
 * Description:
 *      Configure SGMII/HSGMII port Nway state
 * Input:
 *      unit        - Unit ID
 *      port        - Port ID
 *      state       - Nway state
 * Output:
 *      None.
 * Return:
 *      RT_ERR_OK                   - OK
 *      RT_ERR_FAILED               - Failed
 *      RT_ERR_SMI                  - SMI access error
 *      RT_ERR_PORT_ID              - Invalid port ID.
 * Note:
 *      The API configure SGMII/HSGMII port Nway state
 */
rtksw_api_ret_t dal_rtl8367d_port_sgmiiNway_set(rtksw_uint32 unit, rtksw_port_t port, rtksw_enable_t state)
{
    rtksw_api_ret_t retVal, retVal2;
    rtksw_uint32 running;

    /* Check initialization state */
    RTKSW_CHK_INIT_STATE(unit);

    if ((retVal = rtl8367d_getAsicRegBit(unit, 0x130c, 5, &running))!=RT_ERR_OK)
        return retVal;

    if (running == 1)
    {
        if ((retVal = rtl8367d_setAsicRegBit(unit, 0x130c, 5, 0))!=RT_ERR_OK)
            return retVal;
    }

    retVal = _dal_rtl8367d_port_sgmiiNway_set(unit, port, state);

    if (running == 1)
    {
        if ((retVal2 = rtl8367d_setAsicRegBit(unit, 0x130c, 5, 1))!=RT_ERR_OK)
            return retVal2;
    }

    return retVal;
}

/* Function Name:
 *      dal_rtl8367d_port_sgmiiNway_get
 * Description:
 *      Get SGMII/HSGMII port Nway state
 * Input:
 *      unit        - Unit ID
 *      port        - Port ID
 * Output:
 *      pState      - Nway state
 * Return:
 *      RT_ERR_OK                   - OK
 *      RT_ERR_FAILED               - Failed
 *      RT_ERR_SMI                  - SMI access error
 *      RT_ERR_PORT_ID              - Invalid port ID.
 * Note:
 *      The API can get SGMII/HSGMII port Nway state
 */
rtksw_api_ret_t dal_rtl8367d_port_sgmiiNway_get(rtksw_uint32 unit, rtksw_port_t port, rtksw_enable_t *pState)
{
    rtksw_api_ret_t retVal, retVal2;
    rtksw_uint32 running;

    /* Check initialization state */
    RTKSW_CHK_INIT_STATE(unit);

    if ((retVal = rtl8367d_getAsicRegBit(unit, 0x130c, 5, &running))!=RT_ERR_OK)
        return retVal;

    if (running == 1)
    {
        if ((retVal = rtl8367d_setAsicRegBit(unit, 0x130c, 5, 0))!=RT_ERR_OK)
            return retVal;
    }

    retVal = _dal_rtl8367d_port_sgmiiNway_get(unit, port, pState);

    if (running == 1)
    {
        if ((retVal2 = rtl8367d_setAsicRegBit(unit, 0x130c, 5, 1))!=RT_ERR_OK)
            return retVal2;
    }

    return retVal;
}

/* Function Name:
 *      dal_rtl8367d_port_autoDos_set
 * Description:
 *      Set Auto Dos state
 * Input:
 *      unit        - Unit ID
 *      type        - Auto DoS type
 *      state       - 1: Eanble(Drop), 0: Disable(Forward)
 * Output:
 *      None
 * Return:
 *      RT_ERR_OK                   - OK
 *      RT_ERR_FAILED               - Failed
 *      RT_ERR_SMI                  - SMI access error
 * Note:
 *      The API can set Auto Dos state
 */
rtksw_api_ret_t dal_rtl8367d_port_autoDos_set(rtksw_uint32 unit, rtksw_port_autoDosType_t type, rtksw_enable_t state)
{
    rtksw_api_ret_t retVal;

    /* Check initialization state */
    RTKSW_CHK_INIT_STATE(unit);

    if (type >= AUTODOS_END)
        return RT_ERR_INPUT;

    if (state >= RTKSW_ENABLE_END)
        return RT_ERR_INPUT;

    if ((retVal = rtl8367d_setAsicRegBit(unit, RTL8367D_REG_DOS_CFG, RTL8367D_DROP_DAEQSA_OFFSET + type, (state == RTKSW_ENABLED) ? 1 : 0)) != RT_ERR_OK)
        return retVal;

    return RT_ERR_OK;
}

/* Function Name:
 *      dal_rtl8367d_port_autoDos_get
 * Description:
 *      Get Auto Dos state
 * Input:
 *      unit        - Unit ID
 *      type        - Auto DoS type
 * Output:
 *      pState      - 1: Eanble(Drop), 0: Disable(Forward)
 * Return:
 *      RT_ERR_OK                   - OK
 *      RT_ERR_FAILED               - Failed
 *      RT_ERR_SMI                  - SMI access error
 *      RT_ERR_NULL_POINTER         - Null Pointer
 * Note:
 *      The API can get Auto Dos state
 */
rtksw_api_ret_t dal_rtl8367d_port_autoDos_get(rtksw_uint32 unit, rtksw_port_autoDosType_t type, rtksw_enable_t *pState)
{
    rtksw_api_ret_t retVal;
    rtksw_uint32 regData;

    /* Check initialization state */
    RTKSW_CHK_INIT_STATE(unit);

    if (type >= AUTODOS_END)
        return RT_ERR_INPUT;

    if (pState == NULL)
        return RT_ERR_NULL_POINTER;

    if ((retVal = rtl8367d_getAsicRegBit(unit, RTL8367D_REG_DOS_CFG, RTL8367D_DROP_DAEQSA_OFFSET + type, &regData)) != RT_ERR_OK)
        return retVal;

    *pState = (regData == 1) ? RTKSW_ENABLED : RTKSW_DISABLED;
    return RT_ERR_OK;
}


/* Function Name:
 *      dal_rtl8367d_port_fiberAbility_set
 * Description:
 *      Configure fiber port ability
 * Input:
 *      unit        - Unit ID
 *      port        - Port ID
 *      pAbility    - Fiber port ability
 * Output:
 *      None
 * Return:
 *      RT_ERR_OK                   - OK
 *      RT_ERR_FAILED               - Failed
 *      RT_ERR_SMI                  - SMI access error
 *      RT_ERR_PORT_ID              - Invalid port ID.
 * Note:
 *      The API can configure fiber port ability
 */
rtksw_api_ret_t dal_rtl8367d_port_fiberAbility_set(rtksw_uint32 unit, rtksw_port_t port, rtksw_port_fiber_ability_t *pAbility)
{
    rtksw_api_ret_t retVal, retVal2;
    rtksw_uint32 running;

    /* Check initialization state */
    RTKSW_CHK_INIT_STATE(unit);

    if (pAbility == NULL)
        return RT_ERR_NULL_POINTER;
    
    if ((pAbility->Full_5G == 1) || (pAbility->Full_10G == 1))
        return RT_ERR_INPUT;

    if ((retVal = rtl8367d_getAsicRegBit(unit, 0x130c, 5, &running))!=RT_ERR_OK)
        return retVal;

    if (running == 1)
    {
        if ((retVal = rtl8367d_setAsicRegBit(unit, 0x130c, 5, 0))!=RT_ERR_OK)
            return retVal;
    }

    retVal = _dal_rtl8367d_port_fiberAbility_set(unit, port, pAbility);

    if (running == 1)
    {
        if ((retVal2 = rtl8367d_setAsicRegBit(unit, 0x130c, 5, 1))!=RT_ERR_OK)
            return retVal2;
    }

    return retVal;
}


/* Function Name:
 *      dal_rtl8367d_port_fiberAbility_get
 * Description:
 *      Get fiber port ability
 * Input:
 *      unit        - Unit ID
 *      port        - Port ID
 * Output:
 *      pAbility    - Fiber port ability
 * Return:
 *      RT_ERR_OK                   - OK
 *      RT_ERR_FAILED               - Failed
 *      RT_ERR_SMI                  - SMI access error
 *      RT_ERR_PORT_ID              - Invalid port ID.
 * Note:
 *      The API can get fiber port ability
 */
rtksw_api_ret_t dal_rtl8367d_port_fiberAbility_get(rtksw_uint32 unit, rtksw_port_t port, rtksw_port_fiber_ability_t *pAbility)
{
    rtksw_api_ret_t retVal, retVal2;
    rtksw_uint32 running;

    /* Check initialization state */
    RTKSW_CHK_INIT_STATE(unit);

    if ((retVal = rtl8367d_getAsicRegBit(unit, 0x130c, 5, &running))!=RT_ERR_OK)
        return retVal;

    if (running == 1)
    {
        if ((retVal = rtl8367d_setAsicRegBit(unit, 0x130c, 5, 0))!=RT_ERR_OK)
            return retVal;
    }

    retVal = _dal_rtl8367d_port_fiberAbility_get(unit, port, pAbility);

    if (running == 1)
    {
        if ((retVal2 = rtl8367d_setAsicRegBit(unit, 0x130c, 5, 1))!=RT_ERR_OK)
            return retVal2;
    }

    return retVal;
}

/* Function Name:
 *      dal_rtl8367d_port_phyMdx_set
 * Description:
 *      Set PHY MDI/MDIX state
 * Input:
 *      unit        - Unit ID
 *      port        - port ID
 *      mode        - PHY MDI/MDIX mode
 * Output:
 *      None
 * Return:
 *      RT_ERR_OK                   - OK
 *      RT_ERR_FAILED               - Failed
 *      RT_ERR_SMI                  - SMI access error
 * Note:
 *      The API can set PHY MDI/MDIX state
 */
rtksw_api_ret_t dal_rtl8367d_port_phyMdx_set(rtksw_uint32 unit, rtksw_port_t port, rtksw_port_phy_mdix_mode_t mode)
{
    rtksw_uint32 regData;
    rtksw_api_ret_t retVal;

    /* Check initialization state */
    RTKSW_CHK_INIT_STATE(unit);

    /* Check Port Valid */
    RTKSW_CHK_PORT_IS_UTP(unit, port);

    if ((retVal = dal_rtl8367d_port_phyOCPReg_get(unit, port, 0xa430, &regData))!=RT_ERR_OK)
        return retVal;

    switch (mode)
    {
        case PHY_AUTO_CROSSOVER_MODE:
            regData &= ~(0x0001 << 9);
            break;
        case PHY_FORCE_MDI_MODE:
            regData |= (0x0001 << 9);
            regData |= (0x0001 << 8);
            break;
        case PHY_FORCE_MDIX_MODE:
            regData |= (0x0001 << 9);
            regData &= ~(0x0001 << 8);
            break;
        default:
            return RT_ERR_INPUT;
            break;
    }

    if ((retVal = dal_rtl8367d_port_phyOCPReg_set(unit, port, 0xa430, regData))!=RT_ERR_OK)
        return retVal;

    /* Restart N-way */
    if ((retVal = dal_rtl8367d_port_phyReg_get(unit, port, 0, &regData))!=RT_ERR_OK)
        return retVal;

    regData |= (0x0001 << 9);

    if ((retVal = dal_rtl8367d_port_phyReg_set(unit, port, 0, regData))!=RT_ERR_OK)
        return retVal;

    return RT_ERR_OK;
}

/* Function Name:
 *      dal_rtl8367d_port_phyMdx_get
 * Description:
 *      Get PHY MDI/MDIX state
 * Input:
 *      unit        - Unit ID
 *      port        - port ID
 * Output:
 *      pMode       - PHY MDI/MDIX mode
 * Return:
 *      RT_ERR_OK                   - OK
 *      RT_ERR_FAILED               - Failed
 *      RT_ERR_SMI                  - SMI access error
 * Note:
 *      The API can get PHY MDI/MDIX state
 */
rtksw_api_ret_t dal_rtl8367d_port_phyMdx_get(rtksw_uint32 unit, rtksw_port_t port, rtksw_port_phy_mdix_mode_t *pMode)
{
    rtksw_uint32 regData;
    rtksw_api_ret_t retVal;

    /* Check initialization state */
    RTKSW_CHK_INIT_STATE(unit);

    /* Check Port Valid */
    RTKSW_CHK_PORT_IS_UTP(unit, port);

    if (pMode == NULL)
        return RT_ERR_NULL_POINTER;

    if ((retVal = dal_rtl8367d_port_phyOCPReg_get(unit, port, 0xa430, &regData))!=RT_ERR_OK)
        return retVal;

    if(regData & (0x0001 << 9))
    {
        if(regData & (0x0001 << 8))
            *pMode = PHY_FORCE_MDI_MODE;
        else
            *pMode = PHY_FORCE_MDIX_MODE;
    }
    else
        *pMode = PHY_AUTO_CROSSOVER_MODE;

    return RT_ERR_OK;
}

/* Function Name:
 *      dal_rtl8367d_port_phyMdxStatus_get
 * Description:
 *      Get PHY MDI/MDIX status
 * Input:
 *      unit        - Unit ID
 *      port        - port ID
 * Output:
 *      pStatus     - PHY MDI/MDIX status
 * Return:
 *      RT_ERR_OK                   - OK
 *      RT_ERR_FAILED               - Failed
 *      RT_ERR_SMI                  - SMI access error
 * Note:
 *      The API can get PHY MDI/MDIX status
 */
rtksw_api_ret_t dal_rtl8367d_port_phyMdxStatus_get(rtksw_uint32 unit, rtksw_port_t port, rtksw_port_phy_mdix_status_t *pStatus)
{
    rtksw_uint32 regData;
    rtksw_api_ret_t retVal;

    /* Check initialization state */
    RTKSW_CHK_INIT_STATE(unit);

    /* Check Port Valid */
    RTKSW_CHK_PORT_IS_UTP(unit, port);

    if (pStatus == NULL)
        return RT_ERR_NULL_POINTER;

    if ((retVal = dal_rtl8367d_port_phyOCPReg_get(unit, port, 0xa430, &regData))!=RT_ERR_OK)
        return retVal;

    if (regData & (0x0001 << 9))
    {
        if (regData & (0x0001 << 8))
            *pStatus = PHY_STATUS_FORCE_MDI_MODE;
        else
            *pStatus = PHY_STATUS_FORCE_MDIX_MODE;
    }
    else
    {
        if ((retVal = dal_rtl8367d_port_phyOCPReg_get(unit, port, 0xa434, &regData))!=RT_ERR_OK)
            return retVal;

        if (regData & (0x0001 << 1))
            *pStatus = PHY_STATUS_AUTO_MDI_MODE;
        else
            *pStatus = PHY_STATUS_AUTO_MDIX_MODE;
    }

    return RT_ERR_OK;
}

/* Function Name:
 *      dal_rtl8367d_port_phyTestMode_set
 * Description:
 *      Set PHY in test mode.
 * Input:
 *      unit        - Unit ID
 *      port        - port id.
 *      mode        - PHY test mode 0:normal 1:test mode 1 2:test mode 2 3: test mode 3 4:test mode 4 5~7:reserved
 * Output:
 *      None
 * Return:
 *      RT_ERR_OK               - OK
 *      RT_ERR_FAILED           - Failed
 *      RT_ERR_SMI              - SMI access error
 *      RT_ERR_PORT_ID          - Invalid port number.
 *      RT_ERR_BUSYWAIT_TIMEOUT - PHY access busy
 *      RT_ERR_NOT_ALLOWED      - The Setting is not allowed, caused by set more than 1 port in Test mode.
 * Note:
 *      Set PHY in test mode and only one PHY can be in test mode at the same time.
 *      It means API will return FAILED if other PHY is in test mode.
 *      This API only provide test mode 1 & 4 setup.
 */
rtksw_api_ret_t dal_rtl8367d_port_phyTestMode_set(rtksw_uint32 unit, rtksw_port_t port, rtksw_port_phy_test_mode_t mode)
{
    rtksw_uint32          data, i;
    rtksw_api_ret_t       retVal;

    /* Check initialization state */
    RTKSW_CHK_INIT_STATE(unit);

    /* Check Port Valid */
    RTKSW_CHK_PORT_IS_UTP(unit, port);

    if(mode >= RTKSW_PHY_2P5G_TEST_MODE_1)
        return RT_ERR_INPUT;

    if( (mode == RTKSW_PHY_TEST_MODE_2) || (mode == RTKSW_PHY_TEST_MODE_3) )
        return RT_ERR_INPUT;

    if (RTKSW_PHY_TEST_MODE_NORMAL != mode)
    {
        /* Other port should be Normal mode */
        RTKSW_SCAN_ALL_LOG_PORT(unit, i)
        {
            if(rtksw_switch_isUtpPort(unit, i) == RT_ERR_OK)
            {
                if(i != port)
                {
                    if ((retVal = dal_rtl8367d_port_phyReg_get(unit, i, 9, &data)) != RT_ERR_OK)
                        return retVal;

                    if((data & 0xE000) != 0)
                        return RT_ERR_NOT_ALLOWED;
                }
            }
        }
    }


    if ((retVal = dal_rtl8367d_port_phyReg_get(unit, port, 9, &data)) != RT_ERR_OK)
        return retVal;

    data &= ~0xE000;
    data |= (mode << 13);
    if ((retVal = dal_rtl8367d_port_phyReg_set(unit, port, 9, data)) != RT_ERR_OK)
        return retVal;

    return RT_ERR_OK;
}

/* Function Name:
 *      dal_rtl8367d_port_phyTestMode_get
 * Description:
 *      Get PHY in which test mode.
 * Input:
 *      unit        - Unit ID
 *      port        - Port id.
 * Output:
 *      mode - PHY test mode 0:normal 1:test mode 1 2:test mode 2 3: test mode 3 4:test mode 4 5~7:reserved
 * Return:
 *      RT_ERR_OK               - OK
 *      RT_ERR_FAILED           - Failed
 *      RT_ERR_SMI              - SMI access error
 *      RT_ERR_PORT_ID          - Invalid port number.
 *      RT_ERR_INPUT            - Invalid input parameters.
 *      RT_ERR_BUSYWAIT_TIMEOUT - PHY access busy
 * Note:
 *      Get test mode of PHY from register setting 9.15 to 9.13.
 */
rtksw_api_ret_t dal_rtl8367d_port_phyTestMode_get(rtksw_uint32 unit, rtksw_port_t port, rtksw_port_phy_test_mode_t *pMode)
{
    rtksw_uint32      data;
    rtksw_api_ret_t   retVal;

    /* Check initialization state */
    RTKSW_CHK_INIT_STATE(unit);

    /* Check Port Valid */
    RTKSW_CHK_PORT_IS_UTP(unit, port);

    if (pMode == NULL)
        return RT_ERR_NULL_POINTER;

    if ((retVal = dal_rtl8367d_port_phyReg_get(unit, port, 9, &data)) != RT_ERR_OK)
        return retVal;

    *pMode = (data & 0xE000) >> 13;

    return RT_ERR_OK;
}

/* Function Name:
 *      dal_rtl8367d_port_maxPacketLength_set
 * Description:
 *      Set Max packet length per port
 * Input:
 *      unit        - Unit ID
 *      port        - Port id.
 *      length      - Max packet length.
 * Output:
 *      None.
 * Return:
 *      RT_ERR_OK              - OK
 *      RT_ERR_FAILED          - Failed
 *      RT_ERR_SMI             - SMI access error
 *      RT_ERR_OUT_OF_RANGE    - The parameter is out of range
 *      RT_ERR_INPUT           - Input error
 * Note:
 *      None.
 */
rtksw_api_ret_t dal_rtl8367d_port_maxPacketLength_set(rtksw_uint32 unit, rtksw_port_t port, rtksw_uint32 length)
{
    rtksw_api_ret_t retVal;

    switch (rtksw_switch_chipType_get(unit))
    {
        case CHIP_RTL8367D:
            return RT_ERR_DRIVER_NOT_FOUND;
        case CHIP_RTL8367E:
            if ((retVal = _dal_rtl8367e_port_maxPacketLength_set(unit, port, length)) != RT_ERR_OK)
                return retVal;
            break;
        default:
            return RT_ERR_FAILED;
    }
    
    return RT_ERR_OK;
}

/* Function Name:
 *      dal_rtl8367d_port_maxPacketLength_get
 * Description:
 *      Get Max packet length per port
 * Input:
 *      unit        - Unit ID
 *      port        - Port id.
 * Output:
 *      pLength - Pointer of Max packet length.
 * Return:
 *      RT_ERR_OK              - OK
 *      RT_ERR_FAILED          - Failed
 *      RT_ERR_SMI             - SMI access error
 *      RT_ERR_OUT_OF_RANGE    - The parameter is out of range
 *      RT_ERR_INPUT           - Input error
 * Note:
 *      None.
 */
rtksw_api_ret_t dal_rtl8367d_port_maxPacketLength_get(rtksw_uint32 unit, rtksw_port_t port, rtksw_uint32 *pLength)
{
    rtksw_api_ret_t retVal;

    switch (rtksw_switch_chipType_get(unit))
    {
        case CHIP_RTL8367D:
            return RT_ERR_DRIVER_NOT_FOUND;
        case CHIP_RTL8367E:
            if ((retVal = _dal_rtl8367e_port_maxPacketLength_get(unit, port, pLength)) != RT_ERR_OK)
                return retVal;
            break;
        default:
            return RT_ERR_FAILED;
    }
    
    return RT_ERR_OK;
}

/* Function Name:
 *      dal_rtl8367d_port_phyLinkDownPowerSaving_set
 * Description:
 *      Set Ports Link Down Power Saving state.
 * Input:
 *      unit    - Unit ID
 *      port    - port ID
 *      state   - Link Down Power Saving state.
 * Output:
 *      None
 * Return:
 *      RT_ERR_OK       - OK
 *      RT_ERR_FAILED   - Failed
 *      RT_ERR_SMI      - SMI access error
 *      RT_ERR_ENABLE   - Invalid enable input.
 * Note:
 *      This API can set Port Link Down Power Saving state.
 *      The configuration is as following:
 *      - DISABLE
 *      - ENABLE
 */
rtksw_api_ret_t dal_rtl8367d_port_phyLinkDownPowerSaving_set(rtksw_uint32 unit, rtksw_port_t port, rtksw_enable_t state)
{
    rtksw_api_ret_t retVal;
    rtksw_uint32 ocpData;

    /* Check initialization state */
    RTKSW_CHK_INIT_STATE(unit);

    /* Check Port Valid */
    RTKSW_CHK_PORT_IS_UTP(unit, port);

    if (state >= RTKSW_ENABLE_END)
        return RT_ERR_ENABLE;

    if ((retVal = _dal_rtl8367d_getAsicPHYOCPReg(unit, rtksw_switch_port_L2P_get(unit, port), 0xA430, &ocpData)) != RT_ERR_OK)
        return retVal;

    if (state == RTKSW_ENABLED)
        ocpData |= (0x0001 << 2);
    else
        ocpData &= ~(0x0001 << 2);

     if ((retVal = _dal_rtl8367d_setAsicPHYOCPReg(unit, rtksw_switch_port_L2P_get(unit, port), 0xA430, ocpData)) != RT_ERR_OK)
        return retVal;   

    return retVal;
}

/* Function Name:
 *      dal_rtl8367d_port_phyLinkDownPowerSaving_get
 * Description:
 *      Get Ports Link Down Power Saving state.
 * Input:
 *      unit        - Unit ID
 *      port        - port ID
 * Output:
 *      pState  - Link Down Power Saving state.
 * Return:
 *      RT_ERR_OK              - OK
 *      RT_ERR_FAILED          - Failed
 *      RT_ERR_SMI             - SMI access error
 * Note:
 *      This API can get Link Down Power Saving state.
 */
rtksw_api_ret_t dal_rtl8367d_port_phyLinkDownPowerSaving_get(rtksw_uint32 unit, rtksw_port_t port, rtksw_enable_t *pState)
{
    rtksw_api_ret_t retVal;
    rtksw_uint32 ocpData;

    /* Check initialization state */
    RTKSW_CHK_INIT_STATE(unit);

    /* Check Port Valid */
    RTKSW_CHK_PORT_IS_UTP(unit, port);

    if (pState == NULL)
        return RT_ERR_NULL_POINTER;

    if ((retVal = _dal_rtl8367d_getAsicPHYOCPReg(unit, rtksw_switch_port_L2P_get(unit, port), 0xA430, &ocpData)) != RT_ERR_OK)
        return retVal;

    *pState = (ocpData & (0x0001 << 2)) == (0x0001 << 2) ? RTKSW_ENABLED : RTKSW_DISABLED;
    return retVal;
}

/* Function Name:
 *      dal_rtl8367d_port_serdesReg_set
 * Description:
 *      Set Serdes register data of the specific port.
 * Input:
 *      unit    - Unit ID
 *      port    - port id.
 *      page    - Page id.
 *      reg     - Register id
 *      regData - Register data
 * Output:
 *      None
 * Return:
 *      RT_ERR_OK               - OK
 *      RT_ERR_FAILED           - Failed
 *      RT_ERR_SMI              - SMI access error
 *      RT_ERR_INPUT            - Error input
 *      RT_ERR_BUSYWAIT_TIMEOUT - Access busy
 * Note:
 *      This API can set serdes register data of the specific sdsID.
 */
rtksw_api_ret_t dal_rtl8367d_port_serdesReg_set(rtksw_uint32 unit, rtksw_uint32 sdsID, rtksw_uint32 page, rtksw_uint32 reg, rtksw_uint32 regData)
{
    rtksw_api_ret_t retVal;
    rtksw_uint32 cmdData;
    rtksw_uint32 busy;
    rtksw_uint32 pollingCnt = 0;

    /* Check initialization state */
    RTKSW_CHK_INIT_STATE(unit);

    if (page > RTL8367D_MAX_SDS_PAGE)
        return RT_ERR_INPUT;
    
    if (reg > RTL8367D_MAX_SDS_REGISTER)
        return RT_ERR_INPUT;

    if (regData > 0xFFFF)
        return RT_ERR_INPUT;

    switch (sdsID)
    {
        case 0:
            cmdData = 0x00CD;
            break;
        case 1:
            cmdData = 0x00CF;
            break;
        default:
            return RT_ERR_INPUT;
    }

    if ((retVal = rtl8367d_setAsicReg(unit, RTL8367D_REG_SDS_INDACS_DATA, regData)) != RT_ERR_OK)
        return retVal;

    if ((retVal = rtl8367d_setAsicReg(unit, RTL8367D_REG_SDS_INDACS_ADR, (page << 5) | reg)) != RT_ERR_OK)
        return retVal;

    if ((retVal = rtl8367d_setAsicReg(unit, RTL8367D_REG_SDS_INDACS_CMD, cmdData)) != RT_ERR_OK)
        return retVal;

    do
    {
        if (pollingCnt > 100)
            return RT_ERR_BUSYWAIT_TIMEOUT;

        if ((retVal = rtl8367d_getAsicRegBit(unit, RTL8367D_REG_SDS_INDACS_CMD, RTL8367D_SDS_CMD_BUSY_OFFSET, &busy)) != RT_ERR_OK)
            return retVal;
        
        pollingCnt++;
    } while (busy == 1);

    return RT_ERR_OK;
}

/* Function Name:
 *      dal_rtl8367d_port_serdesReg_get
 * Description:
 *      Get Serdes register data of the specific port.
 * Input:
 *      unit        - Unit ID
 *      port        - Port id.
 *      page        - Page id.
 *      reg         - Register id
 * Output:
 *      pData   - Register data
 * Return:
 *      RT_ERR_OK               - OK
 *      RT_ERR_FAILED           - Failed
 *      RT_ERR_SMI              - SMI access error
 *      RT_ERR_INPUT            - Error input
 *      RT_ERR_NULL_POINTER     - NULL pointer
 *      RT_ERR_BUSYWAIT_TIMEOUT - Access busy
 * Note:
 *      This API can get Serdes register data of the specific sdsID.
 */
rtksw_api_ret_t dal_rtl8367d_port_serdesReg_get(rtksw_uint32 unit, rtksw_uint32 sdsID, rtksw_uint32 page, rtksw_uint32 reg, rtksw_uint32 *pData)
{
    rtksw_api_ret_t retVal;
    rtksw_uint32 cmdData;
    rtksw_uint32 busy;
    rtksw_uint32 pollingCnt = 0;

    /* Check initialization state */
    RTKSW_CHK_INIT_STATE(unit);

    if (page > RTL8367D_MAX_SDS_PAGE)
        return RT_ERR_INPUT;
    
    if (reg > RTL8367D_MAX_SDS_REGISTER)
        return RT_ERR_INPUT;

    if (pData == NULL)
        return RT_ERR_NULL_POINTER;

    switch (sdsID)
    {
        case 0:
            cmdData = 0x008D;
            break;
        case 1:
            cmdData = 0x008F;
            break;
        default:
            return RT_ERR_INPUT;
    }

    if ((retVal = rtl8367d_setAsicReg(unit, RTL8367D_REG_SDS_INDACS_ADR, (page << 5) | reg)) != RT_ERR_OK)
        return retVal;

    if ((retVal = rtl8367d_setAsicReg(unit, RTL8367D_REG_SDS_INDACS_CMD, cmdData)) != RT_ERR_OK)
        return retVal;

    do
    {
        if (pollingCnt > 100)
            return RT_ERR_BUSYWAIT_TIMEOUT;

        if ((retVal = rtl8367d_getAsicRegBit(unit, RTL8367D_REG_SDS_INDACS_CMD, RTL8367D_SDS_CMD_BUSY_OFFSET, &busy)) != RT_ERR_OK)
            return retVal;
        
        pollingCnt++;
    } while (busy == 1);
    
    if ((retVal = rtl8367d_getAsicReg(unit, RTL8367D_REG_SDS_INDACS_DATA, pData)) != RT_ERR_OK)
        return retVal;

    return RT_ERR_OK;
}

/* Function Name:
 *      dal_rtl8367d_port_serdesPolarity_set
 * Description:
 *      Set Serdes polarity.
 * Input:
 *      unit            - Unit ID
 *      sdsID           - Serdes id.
 *      inputPolarity   - Input Polarity.
 *      outputPolarity  - Output Polarity
 * Output:
 *      None
 * Return:
 *      RT_ERR_OK               - OK
 *      RT_ERR_FAILED           - Failed
 *      RT_ERR_SMI              - SMI access error
 *      RT_ERR_INPUT            - Error input
 * Note:
 *      This API can set serdes polarity of the specific sdsID.
 */
rtksw_api_ret_t dal_rtl8367d_port_serdesPolarity_set(rtksw_uint32 unit, rtksw_uint32 sdsID, rtksw_port_sdsPolarity_t inputPolarity, rtksw_port_sdsPolarity_t outputPolarity)
{
    rtksw_api_ret_t retVal;
    rtksw_uint32 regData;

    /* Check initialization state */
    RTKSW_CHK_INIT_STATE(unit);

    if ((inputPolarity >= SDS_POLARITY_END) || (outputPolarity >= SDS_POLARITY_END))
        return RT_ERR_INPUT;

    if ((retVal = dal_rtl8367d_port_serdesReg_get(unit, sdsID, 0, 0, &regData)) != RT_ERR_OK)
        return retVal;

    if (inputPolarity == SDS_POLARITY_NORMAL)
        regData &= ~(0x0001 << 9);
    else
        regData |= (0x0001 << 9);

    if (outputPolarity == SDS_POLARITY_NORMAL)
        regData &= ~(0x0001 << 8);
    else
        regData |= (0x0001 << 8);

    if ((retVal = dal_rtl8367d_port_serdesReg_set(unit, sdsID, 0, 0, regData)) != RT_ERR_OK)
        return retVal;

    return RT_ERR_OK;
}

/* Function Name:
 *      dal_rtl8367d_port_serdesPolarity_get
 * Description:
 *      Get Serdes polarity.
 * Input:
 *      unit            - Unit ID
 *      sdsID           - Serdes id.
 * Output:
 *      pInputPolarity  - Input Polarity.
 *      pOutputPolarity - Output Polarity
 * Return:
 *      RT_ERR_OK               - OK
 *      RT_ERR_FAILED           - Failed
 *      RT_ERR_SMI              - SMI access error
 *      RT_ERR_INPUT            - Error input
 *      RT_ERR_NULL_POINTER     - Null pointer
 * Note:
 *      This API can set serdes polarity of the specific sdsID.
 */
rtksw_api_ret_t dal_rtl8367d_port_serdesPolarity_get(rtksw_uint32 unit, rtksw_uint32 sdsID, rtksw_port_sdsPolarity_t *pInputPolarity, rtksw_port_sdsPolarity_t *pOutputPolarity)
{
    rtksw_api_ret_t retVal;
    rtksw_uint32 regData;

    /* Check initialization state */
    RTKSW_CHK_INIT_STATE(unit);

    if ((pInputPolarity == NULL) || (pOutputPolarity == NULL))
        return RT_ERR_NULL_POINTER;

    if ((retVal = dal_rtl8367d_port_serdesReg_get(unit, sdsID, 0, 0, &regData)) != RT_ERR_OK)
        return retVal;

    if ((regData & (0x0001 << 9)) == 0)
        *pInputPolarity = SDS_POLARITY_NORMAL;
    else
        *pInputPolarity = SDS_POLARITY_REVERSE;

    if ((regData & (0x0001 << 8)) == 0)
        *pOutputPolarity = SDS_POLARITY_NORMAL;
    else
        *pOutputPolarity = SDS_POLARITY_REVERSE;

    return RT_ERR_OK;
}
