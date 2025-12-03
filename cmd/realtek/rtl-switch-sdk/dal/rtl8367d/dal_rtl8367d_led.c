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
 * Feature : Here is a list of all functions and variables in LED module.
 *
 */

#include "../../rtk_switch.h"
#include "../../rtk_error.h"
#include "dal_rtl8367d_led.h"

#include "rtl8367d_asicdrv.h"

#include "../dal_mgmts.h"

static rtksw_api_ret_t _dal_rtl8367e_led_parallelLEDRemap_set(rtksw_uint32 unit, rtksw_uint32 LEDPinNo, rtksw_port_t port, rtksw_led_group_t group)
{
    rtksw_uint32 ledRemapReg[] =
    {
        0x1b2b, 0x1b2b, 0x1b2b, 0x1b2c, 0x1b2c, 0x1b2c, 0x1b2d, 0x1b2d, 0x1b2d,
        0x1b2e, 0x1b2e, 0x1b2e, 0x1b2f, 0x1b2f, 0x1b2f, 0x1b33, 0x1b33, 0x1b33
    };
    rtksw_api_ret_t retVal;
	rtksw_uint32 phyPort;
	rtksw_uint32 regData;

    if (LEDPinNo > RTL8367E_MAX_LED_PIN_NO)
		return RT_ERR_INPUT;
	
	RTKSW_CHK_PORT_VALID(unit, port);

	if (group >= LED_GROUP_END)
		return RT_ERR_INPUT;

    phyPort = rtksw_switch_port_L2P_get(unit, port);
	regData = (phyPort * 3) + (rtksw_uint32)group;

    if ((retVal = rtl8367d_setAsicRegBits(unit, ledRemapReg[LEDPinNo], (0x001F << (5 * (LEDPinNo % 3))), regData)) != RT_ERR_OK)
        return retVal;

    return RT_ERR_OK;

}

static rtksw_api_ret_t _dal_rtl8367e_led_parallelLEDRemap_get(rtksw_uint32 unit, rtksw_uint32 LEDPinNo, rtksw_port_t *pPort, rtksw_led_group_t *pGroup)
{
    rtksw_uint32 ledRemapReg[] =
    {
        0x1b2b, 0x1b2b, 0x1b2b, 0x1b2c, 0x1b2c, 0x1b2c, 0x1b2d, 0x1b2d, 0x1b2d,
        0x1b2e, 0x1b2e, 0x1b2e, 0x1b2f, 0x1b2f, 0x1b2f, 0x1b33, 0x1b33, 0x1b33
    };
    rtksw_api_ret_t retVal;
	rtksw_uint32 phyPort;
	rtksw_uint32 regData;

    if (LEDPinNo > RTL8367E_MAX_LED_PIN_NO)
		return RT_ERR_INPUT;

    if ((pPort == NULL) || (pGroup == NULL))
        return RT_ERR_NULL_POINTER;

    if ((retVal = rtl8367d_getAsicRegBits(unit, ledRemapReg[LEDPinNo], (0x001F << (5 * (LEDPinNo % 3))), &regData)) != RT_ERR_OK)
        return retVal;

    phyPort = (regData / 3);
	*pPort = rtksw_switch_port_P2L_get(unit, phyPort);
	*pGroup = (rtksw_led_group_t)(regData % 3);

    return RT_ERR_OK;

}

static rtksw_api_ret_t _dal_rtl8367e_led_parallelLEDState_set(rtksw_uint32 unit, rtksw_uint32 LEDPinNo, rtksw_enable_t state)
{
    rtksw_uint32 ledStateReg[] =
    {
        0x1b24, 0x1b24, 0x1b25, 0x1b24, 0x1b24, 0x1b25, 0x1b24, 0x1b24, 0x1b25,
        0x1b24, 0x1b24, 0x1b25, 0x1b24, 0x1b24, 0x1b25, 0x1b24, 0x1b24, 0x1b25
    };
    rtksw_uint32 ledStateField[] = {0, 8, 0, 1, 9, 1, 2, 10, 2, 3, 11, 3, 4, 12, 4, 5, 13, 5};
    rtksw_api_ret_t retVal;
	rtksw_uint32 regData;

    /* Check initialization state */
    RTKSW_CHK_INIT_STATE(unit);

	if (LEDPinNo > RTL8367E_MAX_LED_PIN_NO)
		return RT_ERR_INPUT;

	if (state >= RTKSW_ENABLE_END)
		return RT_ERR_INPUT;

	regData = (state == RTKSW_ENABLED) ? 1 : 0;
	if ((retVal = rtl8367d_setAsicRegBit(unit, ledStateReg[LEDPinNo], ledStateField[LEDPinNo], regData)) != RT_ERR_OK)
		return retVal;

    return RT_ERR_OK;
}

static rtksw_api_ret_t _dal_rtl8367e_led_parallelLEDState_get(rtksw_uint32 unit, rtksw_uint32 LEDPinNo, rtksw_enable_t *pState)
{
    rtksw_uint32 ledStateReg[] =
    {
        0x1b24, 0x1b24, 0x1b25, 0x1b24, 0x1b24, 0x1b25, 0x1b24, 0x1b24, 0x1b25,
        0x1b24, 0x1b24, 0x1b25, 0x1b24, 0x1b24, 0x1b25, 0x1b24, 0x1b24, 0x1b25
    };
    rtksw_uint32 ledStateField[] = {0, 8, 0, 1, 9, 1, 2, 10, 2, 3, 11, 3, 4, 12, 4, 5, 13, 5};
    rtksw_api_ret_t retVal;
	rtksw_uint32 regData;

    /* Check initialization state */
    RTKSW_CHK_INIT_STATE(unit);

	if (LEDPinNo > RTL8367E_MAX_LED_PIN_NO)
		return RT_ERR_INPUT;

	if (pState == NULL)
		return RT_ERR_NULL_POINTER;

	if ((retVal = rtl8367d_getAsicRegBit(unit, ledStateReg[LEDPinNo], ledStateField[LEDPinNo], &regData)) != RT_ERR_OK)
		return retVal;

    *pState = (regData == 1) ? RTKSW_ENABLED : RTKSW_DISABLED;
    return RT_ERR_OK;
}

/* Function Name:
 *      dal_rtl8367d_led_enable_set
 * Description:
 *      Set Led enable congiuration
 * Input:
 *      unit        - Unit ID
 *      group       - LED group id.
 *      pPortmask   - LED enable port mask.
 * Output:
 *      None
 * Return:
 *      RT_ERR_OK           - OK
 *      RT_ERR_FAILED       - Failed
 *      RT_ERR_SMI          - SMI access error
 *      RT_ERR_INPUT        - Invalid input parameters.
 *      RT_ERR_PORT_MASK    - Error portmask
 * Note:
 *      The API can be used to enable LED per port per group.
 */
rtksw_api_ret_t dal_rtl8367d_led_enable_set(rtksw_uint32 unit, rtksw_led_group_t group, rtksw_portmask_t *pPortmask)
{
    rtksw_api_ret_t retVal;
    rtksw_uint32 pmask;
    rtksw_port_t port;
    rtksw_uint32 regAddr;
    rtksw_uint32 regDataMask;

    /* Check initialization state */
    RTKSW_CHK_INIT_STATE(unit);

    if (group >= LED_GROUP_END)
        return RT_ERR_INPUT;

    RTKSW_CHK_PORTMASK_VALID(unit, pPortmask);

    RTKSW_PORTMASK_SCAN((*pPortmask), port)
    {
        if(rtksw_switch_isCPUPort(unit, port) == RT_ERR_OK)
            return RT_ERR_PORT_MASK;
    }

    if((retVal = rtksw_switch_portmask_L2P_get(unit, pPortmask, &pmask)) != RT_ERR_OK)
        return retVal;

    regAddr = RTL8367D_REG_PARA_LED_IO_EN1 + group/2;
    regDataMask = 0xFF << ((group%2)*8);

    if ((retVal = rtl8367d_setAsicRegBits(unit, regAddr, regDataMask, pmask&0xff)) != RT_ERR_OK)
        return retVal;

    return RT_ERR_OK;
}

/* Function Name:
 *      dal_rtl8367d_led_enable_get
 * Description:
 *      Get Led enable congiuration
 * Input:
 *      unit        - Unit ID
 *      group       - LED group id.
 * Output:
 *      pPortmask - LED enable port mask.
 * Return:
 *      RT_ERR_OK           - OK
 *      RT_ERR_FAILED       - Failed
 *      RT_ERR_SMI          - SMI access error
 *      RT_ERR_INPUT        - Invalid input parameters.
 * Note:
 *      The API can be used to get LED enable status.
 */
rtksw_api_ret_t dal_rtl8367d_led_enable_get(rtksw_uint32 unit, rtksw_led_group_t group, rtksw_portmask_t *pPortmask)
{
    rtksw_api_ret_t retVal;
    rtksw_uint32 pmask;
    rtksw_uint32 regAddr;
    rtksw_uint32 regDataMask;

    /* Check initialization state */
    RTKSW_CHK_INIT_STATE(unit);

    if (group >= LED_GROUP_END)
        return RT_ERR_INPUT;

    regAddr = RTL8367D_REG_PARA_LED_IO_EN1 + group/2;
    regDataMask = 0xFF << ((group%2)*8);
    if ((retVal = rtl8367d_getAsicRegBits(unit, regAddr, regDataMask, &pmask)) != RT_ERR_OK)
        return retVal;

    if((retVal = rtksw_switch_portmask_P2L_get(unit, pmask, pPortmask)) != RT_ERR_OK)
        return retVal;

    return RT_ERR_OK;

}

/* Function Name:
 *      dal_rtl8367d_led_operation_set
 * Description:
 *      Set Led operation mode
 * Input:
 *      unit        - Unit ID
 *      mode        - LED operation mode.
 * Output:
 *      None
 * Return:
 *      RT_ERR_OK           - OK
 *      RT_ERR_FAILED       - Failed
 *      RT_ERR_SMI          - SMI access error
 *      RT_ERR_INPUT        - Invalid input parameters.
 * Note:
 *      The API can set Led operation mode.
 *      The modes that can be set are as following:
 *      - LED_OP_SCAN,
 *      - LED_OP_PARALLEL,
 *      - LED_OP_SERIAL,
 */
rtksw_api_ret_t dal_rtl8367d_led_operation_set(rtksw_uint32 unit, rtksw_led_operation_t mode)
{
    rtksw_api_ret_t retVal;

    /* Check initialization state */
    RTKSW_CHK_INIT_STATE(unit);

    if ( mode >= LED_OP_END)
      return RT_ERR_INPUT;

    switch (mode)
    {
        case LED_OP_PARALLEL:
            /* Enable Parallel LED */
            if((retVal = rtl8367d_setAsicRegBits(unit, RTL8367D_REG_PARA_LED_IO_EN1, RTL8367D_LED0_PARA_P04_00_MASK, 0x1F))!=  RT_ERR_OK)
                return retVal;
            if((retVal = rtl8367d_setAsicRegBits(unit, RTL8367D_REG_PARA_LED_IO_EN1, RTL8367D_LED1_PARA_P04_00_MASK, 0x1F))!=  RT_ERR_OK)
                return retVal;
            if((retVal = rtl8367d_setAsicRegBits(unit, RTL8367D_REG_PARA_LED_IO_EN2, RTL8367D_LED2_PARA_P04_00_MASK, 0x1F))!=  RT_ERR_OK)
                return retVal;

            if((retVal = rtl8367d_setAsicRegBit(unit, RTL8367D_REG_LED_SYS_CONFIG, RTL8367D_LED_SELECT_OFFSET, 0))!=  RT_ERR_OK)
                return retVal;
            /*Disable serial CLK mode*/
            if((retVal = rtl8367d_setAsicRegBit(unit, RTL8367D_REG_SCAN0_LED_IO_EN,RTL8367D_LED_SERI_CLK_EN_OFFSET, 0))!=  RT_ERR_OK)
                return retVal;
            /*Disable serial DATA mode*/
            if((retVal = rtl8367d_setAsicRegBit(unit, RTL8367D_REG_SCAN0_LED_IO_EN,RTL8367D_LED_SERI_DATA_EN_OFFSET, 0))!=  RT_ERR_OK)
                return retVal;
            break;
        case LED_OP_SERIAL:
            /* Disable Parallel LED */
            if((retVal = rtl8367d_setAsicRegBits(unit, RTL8367D_REG_PARA_LED_IO_EN1, RTL8367D_LED0_PARA_P04_00_MASK, 0))!=  RT_ERR_OK)
                return retVal;
            if((retVal = rtl8367d_setAsicRegBits(unit, RTL8367D_REG_PARA_LED_IO_EN1, RTL8367D_LED1_PARA_P04_00_MASK, 0))!=  RT_ERR_OK)
                return retVal;
            if((retVal = rtl8367d_setAsicRegBits(unit, RTL8367D_REG_PARA_LED_IO_EN2, RTL8367D_LED2_PARA_P04_00_MASK, 0))!=  RT_ERR_OK)
                return retVal;

            if((retVal = rtl8367d_setAsicRegBit(unit, RTL8367D_REG_LED_SYS_CONFIG, RTL8367D_LED_SELECT_OFFSET, 1))!=  RT_ERR_OK)
                return retVal;
            /*Enable serial CLK mode*/
            if((retVal = rtl8367d_setAsicRegBit(unit, RTL8367D_REG_SCAN0_LED_IO_EN,RTL8367D_LED_SERI_CLK_EN_OFFSET, 1))!=  RT_ERR_OK)
                return retVal;
            /*Enable serial DATA mode*/
            if((retVal = rtl8367d_setAsicRegBit(unit, RTL8367D_REG_SCAN0_LED_IO_EN,RTL8367D_LED_SERI_DATA_EN_OFFSET, 1))!=  RT_ERR_OK)
                return retVal;
            break;
        default:
            return RT_ERR_CHIP_NOT_SUPPORTED;
            break;
    }

    return RT_ERR_OK;
}

/* Function Name:
 *      dal_rtl8367d_led_operation_get
 * Description:
 *      Get Led operation mode
 * Input:
 *      unit        - Unit ID
 * Output:
 *      pMode - Support LED operation mode.
 * Return:
 *      RT_ERR_OK           - OK
 *      RT_ERR_FAILED       - Failed
 *      RT_ERR_SMI          - SMI access error
 *      RT_ERR_INPUT        - Invalid input parameters.
 * Note:
 *      The API can get Led operation mode.
 *      The modes that can be set are as following:
 *      - LED_OP_SCAN,
 *      - LED_OP_PARALLEL,
 *      - LED_OP_SERIAL,
 */
rtksw_api_ret_t dal_rtl8367d_led_operation_get(rtksw_uint32 unit, rtksw_led_operation_t *pMode)
{
    rtksw_api_ret_t retVal;
    rtksw_uint32 regData;

    /* Check initialization state */
    RTKSW_CHK_INIT_STATE(unit);

    if(NULL == pMode)
        return RT_ERR_NULL_POINTER;

    if((retVal = rtl8367d_getAsicRegBit(unit, RTL8367D_REG_LED_SYS_CONFIG, RTL8367D_LED_SELECT_OFFSET, &regData))!=  RT_ERR_OK)
        return retVal;

    if (regData == RTL8367D_LEDOP_SERIAL)
        *pMode = LED_OP_SERIAL;
    else if (regData == RTL8367D_LEDOP_PARALLEL)
        *pMode = LED_OP_PARALLEL;
    else
        return RT_ERR_FAILED;

    return RT_ERR_OK;
}

/* Function Name:
 *      dal_rtl8367d_led_modeForce_set
 * Description:
 *      Set Led group to congiuration force mode
 * Input:
 *      unit    - Unit ID
 *      port    - port ID
 *      group   - Support LED group id.
 *      mode    - Support LED force mode.
 * Output:
 *      None
 * Return:
 *      RT_ERR_OK           - OK
 *      RT_ERR_FAILED       - Failed
 *      RT_ERR_SMI          - SMI access error
 *      RT_ERR_INPUT        - Invalid input parameters.
 *      RT_ERR_PORT_ID      - Error Port ID
 * Note:
 *      The API can force to one force mode.
 *      The force modes that can be set are as following:
 *      - LED_FORCE_NORMAL,
 *      - LED_FORCE_BLINK,
 *      - LED_FORCE_OFF,
 *      - LED_FORCE_ON.
 */
rtksw_api_ret_t dal_rtl8367d_led_modeForce_set(rtksw_uint32 unit, rtksw_port_t port, rtksw_led_group_t group, rtksw_led_force_mode_t mode)
{
    rtksw_api_ret_t retVal;
    rtksw_uint16 regAddr;
    rtksw_uint32 phyPort;

    /* Check initialization state */
    RTKSW_CHK_INIT_STATE(unit);

    /* Check Port Valid */
    RTKSW_CHK_PORT_VALID(unit, port);

    /* No LED for CPU port */
    if(rtksw_switch_isCPUPort(unit, port) == RT_ERR_OK)
        return RT_ERR_PORT_ID;

    if (group >= LED_GROUP_END)
        return RT_ERR_INPUT;

    if (mode >= LED_FORCE_END)
        return RT_ERR_NOT_ALLOWED;

    phyPort = rtksw_switch_port_L2P_get(unit, port);
    if (phyPort == UNDEFINE_PHY_PORT)
        return RT_ERR_PORT_ID;

    /* Set Related Registers */
    regAddr = RTL8367D_LED_FORCE_MODE_BASE + (group << 1);
    if((retVal = rtl8367d_setAsicRegBits(unit, regAddr, 0x3 << (phyPort * 2), mode)) != RT_ERR_OK)
        return retVal;

    return RT_ERR_OK;
}

/* Function Name:
 *      dal_rtl8367d_led_modeForce_get
 * Description:
 *      Get Led group to congiuration force mode
 * Input:
 *      unit  - Unit ID
 *      port  - port ID
 *      group - Support LED group id.
 *      pMode - Support LED force mode.
 * Output:
 *      None
 * Return:
 *      RT_ERR_OK           - OK
 *      RT_ERR_FAILED       - Failed
 *      RT_ERR_SMI          - SMI access error
 *      RT_ERR_INPUT        - Invalid input parameters.
 *      RT_ERR_PORT_ID      - Error Port ID
 * Note:
 *      The API can get forced Led group mode.
 *      The force modes that can be set are as following:
 *      - LED_FORCE_NORMAL,
 *      - LED_FORCE_BLINK,
 *      - LED_FORCE_OFF,
 *      - LED_FORCE_ON.
 */
rtksw_api_ret_t dal_rtl8367d_led_modeForce_get(rtksw_uint32 unit, rtksw_port_t port, rtksw_led_group_t group, rtksw_led_force_mode_t *pMode)
{
    rtksw_api_ret_t retVal;
    rtksw_uint16 regAddr;
    rtksw_uint32 phyPort;

    /* Check initialization state */
    RTKSW_CHK_INIT_STATE(unit);

    /* Check Port Valid */
    RTKSW_CHK_PORT_VALID(unit, port);

    /* No LED for CPU port */
    if(rtksw_switch_isCPUPort(unit, port) == RT_ERR_OK)
        return RT_ERR_PORT_ID;

    if (group >= LED_GROUP_END)
        return RT_ERR_INPUT;

    if (NULL == pMode)
        return RT_ERR_NULL_POINTER;

    phyPort = rtksw_switch_port_L2P_get(unit, port);
    if (phyPort == UNDEFINE_PHY_PORT)
        return RT_ERR_PORT_ID;

    /* Get Related Registers */
    regAddr = RTL8367D_LED_FORCE_MODE_BASE + (group << 1);
    if((retVal = rtl8367d_getAsicRegBits(unit, regAddr, 0x3 << (phyPort * 2), pMode)) != RT_ERR_OK)
        return retVal;

    return RT_ERR_OK;
}

/* Function Name:
 *      dal_rtl8367d_led_blinkRate_set
 * Description:
 *      Set LED blinking rate
 * Input:
 *      unit        - Unit ID
 *      blinkRate   - blinking rate.
 * Output:
 *      None
 * Return:
 *      RT_ERR_OK           - OK
 *      RT_ERR_FAILED       - Failed
 *      RT_ERR_SMI          - SMI access error
 *      RT_ERR_INPUT        - Invalid input parameters.
 * Note:
 *      The API configure LED blinking rate:
 *      - LED_BLINKRATE_32MS
 *      - LED_BLINKRATE_64MS,
 *      - LED_BLINKRATE_128MS,
 *      - LED_BLINKRATE_256MS,
 *      - LED_BLINKRATE_512MS,
 *      - LED_BLINKRATE_1024MS,
 *      - LED_BLINKRATE_48MS,
 *      - LED_BLINKRATE_96MS,
 */
rtksw_api_ret_t dal_rtl8367d_led_blinkRate_set(rtksw_uint32 unit, rtksw_led_blink_rate_t blinkRate)
{
    rtksw_api_ret_t retVal;

    /* Check initialization state */
    RTKSW_CHK_INIT_STATE(unit);

    if (blinkRate >= LED_BLINKRATE_END)
        return RT_ERR_FAILED;

    if ((retVal = rtl8367d_setAsicRegBits(unit, RTL8367D_REG_LED_MODE, RTL8367D_SEL_LEDRATE_MASK, blinkRate)) != RT_ERR_OK)
        return retVal;

    return RT_ERR_OK;
}

/* Function Name:
 *      dal_rtl8367d_led_blinkRate_get
 * Description:
 *      Get LED blinking rate at mode 0 to mode 3
 * Input:
 *      unit        - Unit ID
 * Output:
 *      pBlinkRate - blinking rate.
 * Return:
 *      RT_ERR_OK           - OK
 *      RT_ERR_FAILED       - Failed
 *      RT_ERR_SMI          - SMI access error
 *      RT_ERR_INPUT        - Invalid input parameters.
 * Note:
 *      The API get LED blinking rate:
 *      - LED_BLINKRATE_32MS
 *      - LED_BLINKRATE_64MS,
 *      - LED_BLINKRATE_128MS,
 *      - LED_BLINKRATE_256MS,
 *      - LED_BLINKRATE_512MS,
 *      - LED_BLINKRATE_1024MS,
 *      - LED_BLINKRATE_48MS,
 *      - LED_BLINKRATE_96MS,
 */
rtksw_api_ret_t dal_rtl8367d_led_blinkRate_get(rtksw_uint32 unit, rtksw_led_blink_rate_t *pBlinkRate)
{
    rtksw_api_ret_t retVal;

    /* Check initialization state */
    RTKSW_CHK_INIT_STATE(unit);

    if(NULL == pBlinkRate)
        return RT_ERR_NULL_POINTER;

    if ((retVal = rtl8367d_getAsicRegBits(unit, RTL8367D_REG_LED_MODE, RTL8367D_SEL_LEDRATE_MASK, pBlinkRate)) != RT_ERR_OK)
        return retVal;

    return RT_ERR_OK;
}

/* Function Name:
 *      dal_rtl8367d_led_groupConfig_set
 * Description:
 *      Set per group Led to congiuration mode
 * Input:
 *      unit    - Unit ID
 *      group   - LED group.
 *      config  - LED configuration
 * Output:
 *      None
 * Return:
 *      RT_ERR_OK           - OK
 *      RT_ERR_FAILED       - Failed
 *      RT_ERR_SMI          - SMI access error
 *      RT_ERR_INPUT        - Invalid input parameters.
 * Note:
 *      The API can set LED indicated information configuration for each LED group with 1 to 1 led mapping to each port.
 *      - Definition  LED Statuses      Description
 *      - 0000        LED_Off           LED pin Tri-State.
 *      - 0001        Dup/Col           Collision, Full duplex Indicator.
 *      - 0010        Link/Act          Link, Activity Indicator.
 *      - 0011        Spd1000           1000Mb/s Speed Indicator.
 *      - 0100        Spd100            100Mb/s Speed Indicator.
 *      - 0101        Spd10             10Mb/s Speed Indicator.
 *      - 0110        Spd1000/Act       1000Mb/s Speed/Activity Indicator.
 *      - 0111        Spd100/Act        100Mb/s Speed/Activity Indicator.
 *      - 1000        Spd10/Act         10Mb/s Speed/Activity Indicator.
 *      - 1001        Spd100 (10)/Act   10/100Mb/s Speed/Activity Indicator.
 *      - 1010        LoopDetect        LoopDetect Indicator.
 *      - 1011        EEE               EEE Indicator.
 *      - 1100        Link/Rx           Link, Activity Indicator.
 *      - 1101        Link/Tx           Link, Activity Indicator.
 *      - 1110        Master            Link on Master Indicator.
 *      - 1111        Act               Activity Indicator. Low for link established.
 */
rtksw_api_ret_t dal_rtl8367d_led_groupConfig_set(rtksw_uint32 unit, rtksw_led_group_t group, rtksw_led_config_t config)
{
    rtksw_api_ret_t retVal;
    CONST rtksw_uint16 bits[RTL8367D_LEDGROUPNO] = {RTL8367D_LED0_CFG_MASK, RTL8367D_LED1_CFG_MASK, RTL8367D_LED2_CFG_MASK};

    /* Check initialization state */
    RTKSW_CHK_INIT_STATE(unit);

    if (LED_GROUP_END <= group)
        return RT_ERR_FAILED;

    if (LED_CONFIG_END <= config)
        return RT_ERR_FAILED;

    if ((retVal = rtl8367d_setAsicRegBit(unit, RTL8367D_REG_LED_CONFIGURATION, RTL8367D_LED_CONFIG_SEL_OFFSET, 0)) != RT_ERR_OK)
         return retVal;

    if ((retVal = rtl8367d_setAsicRegBits(unit, RTL8367D_REG_LED_CONFIGURATION, bits[group], config)) != RT_ERR_OK)
         return retVal;

    return RT_ERR_OK;
}

/* Function Name:
 *      dal_rtl8367d_led_groupConfig_get
 * Description:
 *      Get Led group congiuration mode
 * Input:
 *      unit    - Unit ID
 *      group   - LED group.
 * Output:
 *      pConfig - LED configuration.
 * Return:
 *      RT_ERR_OK           - OK
 *      RT_ERR_FAILED       - Failed
 *      RT_ERR_SMI          - SMI access error
 *      RT_ERR_INPUT        - Invalid input parameters.
 * Note:
 *       The API can get LED indicated information configuration for each LED group.
 */
rtksw_api_ret_t dal_rtl8367d_led_groupConfig_get(rtksw_uint32 unit, rtksw_led_group_t group, rtksw_led_config_t *pConfig)
{
    rtksw_api_ret_t retVal;
    CONST rtksw_uint16 bits[RTL8367D_LEDGROUPNO]= {RTL8367D_LED0_CFG_MASK, RTL8367D_LED1_CFG_MASK, RTL8367D_LED2_CFG_MASK};

    /* Check initialization state */
    RTKSW_CHK_INIT_STATE(unit);

    if (LED_GROUP_END <= group)
        return RT_ERR_FAILED;

    if(NULL == pConfig)
        return RT_ERR_NULL_POINTER;

    if ((retVal = rtl8367d_getAsicRegBits(unit, RTL8367D_REG_LED_CONFIGURATION, bits[group], pConfig)) != RT_ERR_OK)
        return retVal;

    return RT_ERR_OK;
}

/* Function Name:
 *      dal_rtl8367d_led_groupAbility_set
 * Description:
 *      Configure per group Led ability
 * Input:
 *      unit        - Unit ID
 *      group       - LED group.
 *      pAbility    - LED ability
 * Output:
 *      None
 * Return:
 *      RT_ERR_OK           - OK
 *      RT_ERR_FAILED       - Failed
 *      RT_ERR_SMI          - SMI access error
 *      RT_ERR_INPUT        - Invalid input parameters.
 * Note:
 *      None.
 */

rtksw_api_ret_t dal_rtl8367d_led_groupAbility_set(rtksw_uint32 unit, rtksw_led_group_t group, rtksw_led_ability_t *pAbility)
{
    rtksw_api_ret_t retVal;
    rtksw_uint32 regData;

    /* Check initialization state */
    RTKSW_CHK_INIT_STATE(unit);

    if (LED_GROUP_END <= group)
        return RT_ERR_FAILED;

    if(pAbility == NULL)
        return RT_ERR_NULL_POINTER;

    if( (pAbility->link_10m >= RTKSW_ENABLE_END) || (pAbility->link_100m >= RTKSW_ENABLE_END) ||
        (pAbility->link_500m >= RTKSW_ENABLE_END) || (pAbility->link_1000m >= RTKSW_ENABLE_END) || (pAbility->link_2500m >= RTKSW_ENABLE_END) ||
        (pAbility->act_rx >= RTKSW_ENABLE_END) || (pAbility->act_tx >= RTKSW_ENABLE_END) )
    {
        return RT_ERR_INPUT;
    }

    if ((retVal = rtl8367d_getAsicReg(unit, RTL8367D_REG_LED0_DATA_CTRL + (rtksw_uint32)group, &regData)) != RT_ERR_OK)
        return retVal;

    if(pAbility->link_10m == RTKSW_ENABLED)
        regData |= 0x0001;
    else
        regData &= ~0x0001;

    if(pAbility->link_100m == RTKSW_ENABLED)
        regData |= 0x0002;
    else
        regData &= ~0x0002;

    if(pAbility->link_500m == RTKSW_ENABLED)
        regData |= 0x0004;
    else
        regData &= ~0x0004;

    if(pAbility->link_1000m == RTKSW_ENABLED)
        regData |= 0x0008;
    else
        regData &= ~0x0008;

    if(pAbility->link_2500m == RTKSW_ENABLED)
        regData |= 0x0010;
    else
        regData &= ~0x0010;

    if(pAbility->act_rx == RTKSW_ENABLED)
        regData |= 0x0020;
    else
        regData &= ~0x0020;

    if(pAbility->act_tx == RTKSW_ENABLED)
        regData |= 0x0040;
    else
        regData &= ~0x0040;

    regData |= (0x0001 << 7);

    if ((retVal = rtl8367d_setAsicReg(unit, RTL8367D_REG_LED0_DATA_CTRL + (rtksw_uint32)group, regData)) != RT_ERR_OK)
        return retVal;

    return RT_ERR_OK;
}

/* Function Name:
 *      dal_rtl8367d_led_groupAbility_get
 * Description:
 *      Get per group Led ability
 * Input:
 *      unit        - Unit ID
 *      group       - LED group.
 *      pAbility    - LED ability
 * Output:
 *      None
 * Return:
 *      RT_ERR_OK           - OK
 *      RT_ERR_FAILED       - Failed
 *      RT_ERR_SMI          - SMI access error
 *      RT_ERR_INPUT        - Invalid input parameters.
 * Note:
 *      None.
 */

rtksw_api_ret_t dal_rtl8367d_led_groupAbility_get(rtksw_uint32 unit, rtksw_led_group_t group, rtksw_led_ability_t *pAbility)
{
    rtksw_api_ret_t retVal;
    rtksw_uint32 regData;

    /* Check initialization state */
    RTKSW_CHK_INIT_STATE(unit);

    if (LED_GROUP_END <= group)
        return RT_ERR_FAILED;

    if(pAbility == NULL)
        return RT_ERR_NULL_POINTER;

    if ((retVal = rtl8367d_getAsicReg(unit, RTL8367D_REG_LED0_DATA_CTRL + (rtksw_uint32)group, &regData)) != RT_ERR_OK)
        return retVal;

    pAbility->link_10m = (regData & 0x0001) ? RTKSW_ENABLED : RTKSW_DISABLED;
    pAbility->link_100m = (regData & 0x0002) ? RTKSW_ENABLED : RTKSW_DISABLED;
    pAbility->link_500m = (regData & 0x0004) ? RTKSW_ENABLED : RTKSW_DISABLED;
    pAbility->link_1000m = (regData & 0x0008) ? RTKSW_ENABLED : RTKSW_DISABLED;
    pAbility->link_2500m = (regData & 0x0010) ? RTKSW_ENABLED : RTKSW_DISABLED;
    pAbility->act_rx = (regData & 0x0020) ? RTKSW_ENABLED : RTKSW_DISABLED;
    pAbility->act_tx = (regData & 0x0040) ? RTKSW_ENABLED : RTKSW_DISABLED;

    return RT_ERR_OK;
}

/* Function Name:
 *      dal_rtl8367d_led_serialMode_set
 * Description:
 *      Set Led serial mode active congiuration
 * Input:
 *      unit        - Unit ID
 *      active      - LED group.
 * Output:
 *      None
 * Return:
 *      RT_ERR_OK           - OK
 *      RT_ERR_FAILED       - Failed
 *      RT_ERR_SMI          - SMI access error
 *      RT_ERR_INPUT        - Invalid input parameters.
 * Note:
 *      The API can set LED serial mode active congiuration.
 */
rtksw_api_ret_t dal_rtl8367d_led_serialMode_set(rtksw_uint32 unit, rtksw_led_active_t active)
{
    rtksw_api_ret_t retVal;

    /* Check initialization state */
    RTKSW_CHK_INIT_STATE(unit);

    if ( active >= RTKSW_LED_ACTIVE_END)
        return RT_ERR_INPUT;

    /* Set Active High or Low */
    if((retVal = rtl8367d_setAsicRegBit(unit, RTL8367D_REG_LED_SYS_CONFIG, RTL8367D_SERI_LED_ACT_LOW_OFFSET, active)) !=  RT_ERR_OK)
        return retVal;

    /*set to 8G mode (not 16G mode)*/
    if((retVal = rtl8367d_setAsicRegBit(unit, RTL8367D_REG_LED_MODE, RTL8367D_DLINK_TIME_OFFSET, 1))!=  RT_ERR_OK)
        return retVal;

    return RT_ERR_OK;
}

/* Function Name:
 *      dal_rtl8367d_led_serialMode_get
 * Description:
 *      Get Led group congiuration mode
 * Input:
 *      unit        - Unit ID
 *      group       - LED group.
 * Output:
 *      pConfig - LED configuration.
 * Return:
 *      RT_ERR_OK           - OK
 *      RT_ERR_FAILED       - Failed
 *      RT_ERR_SMI          - SMI access error
 *      RT_ERR_INPUT        - Invalid input parameters.
 * Note:
 *       The API can get LED serial mode active configuration.
 */
rtksw_api_ret_t dal_rtl8367d_led_serialMode_get(rtksw_uint32 unit, rtksw_led_active_t *pActive)
{
    rtksw_api_ret_t retVal;

    /* Check initialization state */
    RTKSW_CHK_INIT_STATE(unit);

    if(NULL == pActive)
        return RT_ERR_NULL_POINTER;

    if((retVal = rtl8367d_getAsicRegBit(unit, RTL8367D_REG_LED_SYS_CONFIG, RTL8367D_SERI_LED_ACT_LOW_OFFSET, pActive))!=  RT_ERR_OK)
        return retVal;

    return RT_ERR_OK;
}

/* Function Name:
 *      dal_rtl8367d_led_OutputEnable_set
 * Description:
 *      This API set LED I/O state.
 * Input:
 *      unit        - Unit ID
 *      enabled     - LED I/O state
 * Output:
 *      None.
 * Return:
 *      RT_ERR_OK              - OK
 *      RT_ERR_FAILED          - Failed
 *      RT_ERR_SMI             - SMI access error
 *      RT_ERR_INPUT           - Error parameter
 * Note:
 *      This API set LED I/O state.
 */
rtksw_api_ret_t dal_rtl8367d_led_OutputEnable_set(rtksw_uint32 unit, rtksw_enable_t state)
{
    rtksw_api_ret_t retVal;
    rtksw_uint32 regdata;

    /* Check initialization state */
    RTKSW_CHK_INIT_STATE(unit);

    if (state >= RTKSW_ENABLE_END)
        return RT_ERR_INPUT;

    if (state == 1)
        regdata = 0;
    else
        regdata = 1;

    if ((retVal = rtl8367d_setAsicRegBit(unit, RTL8367D_REG_LED_SYS_CONFIG, RTL8367D_LED_IO_DISABLE_OFFSET, regdata))!=RT_ERR_OK)
        return retVal;

    return RT_ERR_OK;
}

/* Function Name:
 *      dal_rtl8367d_led_OutputEnable_get
 * Description:
 *      This API get LED I/O state.
 * Input:
 *      unit        - Unit ID
 * Output:
 *      pEnabled        - LED I/O state
 * Return:
 *      RT_ERR_OK              - OK
 *      RT_ERR_FAILED          - Failed
 *      RT_ERR_SMI             - SMI access error
 *      RT_ERR_INPUT           - Error parameter
 * Note:
 *      This API set current LED I/O  state.
 */
rtksw_api_ret_t dal_rtl8367d_led_OutputEnable_get(rtksw_uint32 unit, rtksw_enable_t *pState)
{
    rtksw_api_ret_t retVal;
    rtksw_uint32 regdata;

    /* Check initialization state */
    RTKSW_CHK_INIT_STATE(unit);

    if(pState == NULL)
        return RT_ERR_NULL_POINTER;


    if ((retVal = rtl8367d_getAsicRegBit(unit, RTL8367D_REG_LED_SYS_CONFIG, RTL8367D_LED_IO_DISABLE_OFFSET, &regdata))!=RT_ERR_OK)
        return retVal;

    if (regdata == 1)
        *pState = 0;
    else
        *pState = 1;

    return RT_ERR_OK;

}

/* Function Name:
 *      dal_rtl8367d_led_parallelLEDRemap_set
 * Description:
 *      This API configure parallel LED output remapping
 * Input:
 *      unit        - Unit ID
 *      LEDPinNo    - LED pin number
 *      port        - port
 *      group       - LED group
 * Output:
 *      None.
 * Return:
 *      RT_ERR_OK              - OK
 *      RT_ERR_FAILED          - Failed
 *      RT_ERR_SMI             - SMI access error
 *      RT_ERR_INPUT           - Error parameter
 * Note:
 *      None.
 */
rtksw_api_ret_t dal_rtl8367d_led_parallelLEDRemap_set(rtksw_uint32 unit, rtksw_uint32 LEDPinNo, rtksw_port_t port, rtksw_led_group_t group)
{
    rtksw_api_ret_t retVal;

	/* Check initialization state */
    RTKSW_CHK_INIT_STATE(unit);

    switch (rtksw_switch_chipType_get(unit))
    {
        case CHIP_RTL8367D:
            return RT_ERR_CHIP_NOT_SUPPORTED;
        case CHIP_RTL8367E:
            if ((retVal = _dal_rtl8367e_led_parallelLEDRemap_set(unit, LEDPinNo, port, group)) != RT_ERR_OK)
                return retVal;
            break;
        default:
            return RT_ERR_CHIP_NOT_FOUND;
    }

	return RT_ERR_OK;
}

/* Function Name:
 *      dal_rtl8367d_led_parallelLEDRemap_get
 * Description:
 *      This API get parallel LED output remapping
 * Input:
 *      unit        - Unit ID
 *      LEDPinNo    - LED pin number
 * Output:
 *      pPort       - port
 *      pGroup      - LED group
 * Return:
 *      RT_ERR_OK              - OK
 *      RT_ERR_FAILED          - Failed
 *      RT_ERR_SMI             - SMI access error
 *      RT_ERR_INPUT           - Error parameter
 * Note:
 *      None.
 */
rtksw_api_ret_t dal_rtl8367d_led_parallelLEDRemap_get(rtksw_uint32 unit, rtksw_uint32 LEDPinNo, rtksw_port_t *pPort, rtksw_led_group_t *pGroup)
{
    rtksw_api_ret_t retVal;

    /* Check initialization state */
    RTKSW_CHK_INIT_STATE(unit);

    switch (rtksw_switch_chipType_get(unit))
    {
        case CHIP_RTL8367D:
            return RT_ERR_CHIP_NOT_SUPPORTED;
        case CHIP_RTL8367E:
            if ((retVal = _dal_rtl8367e_led_parallelLEDRemap_get(unit, LEDPinNo, pPort, pGroup)) != RT_ERR_OK)
                return retVal;
            break;
        default:
            return RT_ERR_CHIP_NOT_FOUND;
    }

	return RT_ERR_OK;
}

/* Function Name:
 *      dal_rtl8367d_led_parallelLEDState_set
 * Description:
 *      This API configure parallel LED state
 * Input:
 *      unit        - Unit ID
 *      LEDPinNo    - LED pin number
 *      state       - enable or disable
 * Output:
 *      None.
 * Return:
 *      RT_ERR_OK              - OK
 *      RT_ERR_FAILED          - Failed
 *      RT_ERR_SMI             - SMI access error
 *      RT_ERR_INPUT           - Error parameter
 * Note:
 *      None.
 */
rtksw_api_ret_t dal_rtl8367d_led_parallelLEDState_set(rtksw_uint32 unit, rtksw_uint32 LEDPinNo, rtksw_enable_t state)
{
    rtksw_api_ret_t retVal;

	/* Check initialization state */
    RTKSW_CHK_INIT_STATE(unit);

    switch (rtksw_switch_chipType_get(unit))
    {
        case CHIP_RTL8367D:
            return RT_ERR_CHIP_NOT_SUPPORTED;
        case CHIP_RTL8367E:
            if ((retVal = _dal_rtl8367e_led_parallelLEDState_set(unit, LEDPinNo, state)) != RT_ERR_OK)
                return retVal;
            break;
        default:
            return RT_ERR_CHIP_NOT_FOUND;
    }

	return RT_ERR_OK;
}

/* Function Name:
 *      dal_rtl8367d_led_parallelLEDState_get
 * Description:
 *      This API configure parallel LED state
 * Input:
 *      unit        - Unit ID
 *      LEDPinNo    - LED pin number
 * Output:
 *      pState      - enable or disable.
 * Return:
 *      RT_ERR_OK              - OK
 *      RT_ERR_FAILED          - Failed
 *      RT_ERR_SMI             - SMI access error
 *      RT_ERR_INPUT           - Error parameter
 * Note:
 *      None.
 */
rtksw_api_ret_t dal_rtl8367d_led_parallelLEDState_get(rtksw_uint32 unit, rtksw_uint32 LEDPinNo, rtksw_enable_t *pState)
{
    rtksw_api_ret_t retVal;

    /* Check initialization state */
    RTKSW_CHK_INIT_STATE(unit);

    switch (rtksw_switch_chipType_get(unit))
    {
        case CHIP_RTL8367D:
            return RT_ERR_CHIP_NOT_SUPPORTED;
        case CHIP_RTL8367E:
            if ((retVal = _dal_rtl8367e_led_parallelLEDState_get(unit, LEDPinNo, pState)) != RT_ERR_OK)
                return retVal;
            break;
        default:
            return RT_ERR_CHIP_NOT_FOUND;
    }

	return RT_ERR_OK;
}
