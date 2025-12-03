/*
 * Copyright (C) 2012 Realtek Semiconductor Corp.
 * All Rights Reserved.
 *
 * This program is the proprietary software of Realtek Semiconductor
 * Corporation and/or its licensors, and only be used, duplicated,
 * modified or distributed under the authorized license from Realtek.
 *
 * ANY USE OF THE SOFTWARE OTHER THAN AS AUTHORIZED UNDER
 * THIS LICENSE OR COPYRIGHT LAW IS PROHIBITED.
 *
 * $Revision: $
 * $Date: $
 *
 * Purpose : Declaration of RLDP and RLPP API
 *
 * Feature : The file have include the following module and sub-modules
 *           1) RLDP and RLPP configuration and status
 *
 */


/*
 * Include Files
 */
#include "../../rtk_switch.h"
#include "../../rtk_error.h"
#include "dal_rtl8367d_rldp.h"
#include "rtl8367d_asicdrv.h"

#include "../dal_mgmts.h"


/* Function Name:
 *      dal_rtl8367d_rldp_config_set
 * Description:
 *      Set RLDP module configuration
 * Input:
 *      unit        - Unit ID
 *      pConfig     - configuration structure of RLDP
 * Output:
 *      None
 * Return:
 *      RT_ERR_OK
 *      RT_ERR_FAILED
 *      RT_ERR_INPUT
 *      RT_ERR_NULL_POINTER
 * Note:
 *      None
 */
rtksw_api_ret_t dal_rtl8367d_rldp_config_set(rtksw_uint32 unit, rtksw_rldp_config_t *pConfig)
{
    rtksw_api_ret_t retVal;
    rtksw_uint16 *magic;
    rtksw_uint32 regData, i;

    /* Check initialization state */
    RTKSW_CHK_INIT_STATE(unit);

    if (pConfig->rldp_enable >= RTKSW_ENABLE_END)
        return RT_ERR_INPUT;

    if (pConfig->trigger_mode >= RTKSW_RLDP_TRIGGER_END)
        return RT_ERR_INPUT;

    if (pConfig->compare_type >= RTKSW_RLDP_CMPTYPE_END)
        return RT_ERR_INPUT;

    if (pConfig->num_check >= RTKSW_RLDP_NUM_MAX)
        return RT_ERR_INPUT;

    if (pConfig->interval_check >= RTKSW_RLDP_INTERVAL_MAX)
        return RT_ERR_INPUT;

    if (pConfig->num_loop >= RTKSW_RLDP_NUM_MAX)
        return RT_ERR_INPUT;

    if (pConfig->interval_loop >= RTKSW_RLDP_INTERVAL_MAX)
        return RT_ERR_INPUT;


    if ((retVal = rtl8367d_setAsicRegBit(unit, RTL8367D_REG_RLDP_CTRL0, RTL8367D_RLDP_ENABLE_OFFSET, pConfig->rldp_enable))!=RT_ERR_OK)
        return retVal;

    if ((retVal = rtl8367d_setAsicRegBit(unit, RTL8367D_REG_RLDP_CTRL0, RTL8367D_RLDP_TRIGGER_MODE_OFFSET, pConfig->trigger_mode))!=RT_ERR_OK)
        return retVal;

    magic = (rtksw_uint16*)&pConfig->magic;
    for (i = 0; i < 3; i++)
    {
        regData = *magic;
        retVal = rtl8367d_setAsicReg(unit, RTL8367D_REG_RLDP_MAGIC_NUM0 + i, regData);
        if(retVal != RT_ERR_OK)
            return retVal;

        magic++;
    }

    if ((retVal = rtl8367d_setAsicRegBit(unit, RTL8367D_REG_RLDP_CTRL0, RTL8367D_RLDP_COMP_ID_OFFSET, pConfig->compare_type))!=RT_ERR_OK)
        return retVal;

    if ((retVal = rtl8367d_setAsicRegBits(unit, RTL8367D_REG_RLDP_CTRL1, RTL8367D_RLDP_RETRY_COUNT_CHKSTATE_MASK, pConfig->num_check))!=RT_ERR_OK)
        return retVal;

    if ((retVal = rtl8367d_setAsicReg(unit, RTL8367D_REG_RLDP_CTRL3, pConfig->interval_check))!=RT_ERR_OK)
        return retVal;

    if ((retVal = rtl8367d_setAsicRegBits(unit, RTL8367D_REG_RLDP_CTRL1, RTL8367D_RLDP_RETRY_COUNT_LOOPSTATE_MASK, pConfig->num_loop))!=RT_ERR_OK)
        return retVal;

    if ((retVal = rtl8367d_setAsicReg(unit, RTL8367D_REG_RLDP_CTRL2, pConfig->interval_loop))!=RT_ERR_OK)
        return retVal;

    return RT_ERR_OK;
}

/* Function Name:
 *      dal_rtl8367d_rldp_config_get
 * Description:
 *      Get RLDP module configuration
 * Input:
 *      unit        - Unit ID
 * Output:
 *      pConfig - configuration structure of RLDP
 * Return:
 *      RT_ERR_OK
 *      RT_ERR_FAILED
 *      RT_ERR_INPUT
 *      RT_ERR_NULL_POINTER
 * Note:
 *      None
 */
rtksw_api_ret_t dal_rtl8367d_rldp_config_get(rtksw_uint32 unit, rtksw_rldp_config_t *pConfig)
{
    rtksw_api_ret_t retVal;
    rtksw_uint16 *magic;
    rtksw_uint32 regData, i;

    /* Check initialization state */
    RTKSW_CHK_INIT_STATE(unit);

    if ((retVal = rtl8367d_getAsicRegBit(unit, RTL8367D_REG_RLDP_CTRL0, RTL8367D_RLDP_ENABLE_OFFSET, &pConfig->rldp_enable))!=RT_ERR_OK)
        return retVal;

    if ((retVal = rtl8367d_getAsicRegBit(unit, RTL8367D_REG_RLDP_CTRL0, RTL8367D_RLDP_TRIGGER_MODE_OFFSET, &pConfig->trigger_mode))!=RT_ERR_OK)
        return retVal;

    magic = (rtksw_uint16*)&pConfig->magic;
    for (i = 0; i < 3; i++)
    {
        retVal = rtl8367d_getAsicReg(unit, RTL8367D_REG_RLDP_MAGIC_NUM0 + i, &regData);
        if(retVal != RT_ERR_OK)
            return retVal;

        *magic = regData;
        magic++;
    }

    if ((retVal = rtl8367d_getAsicRegBit(unit, RTL8367D_REG_RLDP_CTRL0, RTL8367D_RLDP_COMP_ID_OFFSET, &pConfig->compare_type))!=RT_ERR_OK)
        return retVal;

    if ((retVal = rtl8367d_getAsicRegBits(unit, RTL8367D_REG_RLDP_CTRL1, RTL8367D_RLDP_RETRY_COUNT_CHKSTATE_MASK, &pConfig->num_check))!=RT_ERR_OK)
        return retVal;

    if ((retVal = rtl8367d_getAsicReg(unit, RTL8367D_REG_RLDP_CTRL3, &pConfig->interval_check))!=RT_ERR_OK)
        return retVal;

    if ((retVal = rtl8367d_getAsicRegBits(unit, RTL8367D_REG_RLDP_CTRL1, RTL8367D_RLDP_RETRY_COUNT_LOOPSTATE_MASK, &pConfig->num_loop))!=RT_ERR_OK)
        return retVal;

    if ((retVal = rtl8367d_getAsicReg(unit, RTL8367D_REG_RLDP_CTRL2, &pConfig->interval_loop))!=RT_ERR_OK)
        return retVal;

    return RT_ERR_OK;
}


/* Function Name:
 *      dal_rtl8367d_rldp_portConfig_set
 * Description:
 *      Set per port RLDP module configuration
 * Input:
 *      unit        - Unit ID
 *      port        - port number to be configured
 *      pPortConfig - per port configuration structure of RLDP
 * Output:
 *      None
 * Return:
 *      RT_ERR_OK
 *      RT_ERR_FAILED
 *      RT_ERR_INPUT
 *      RT_ERR_NULL_POINTER
 * Note:
 *      None
 */
rtksw_api_ret_t dal_rtl8367d_rldp_portConfig_set(rtksw_uint32 unit, rtksw_port_t port, rtksw_rldp_portConfig_t *pPortConfig)
{
    rtksw_api_ret_t retVal;
    rtksw_uint32 portmask;
    rtksw_uint32 phy_port;

    /* Check initialization state */
    RTKSW_CHK_INIT_STATE(unit);

    /* Check Port Valid */
    RTKSW_CHK_PORT_VALID(unit, port);

    if (pPortConfig->tx_enable>= RTKSW_ENABLE_END)
        return RT_ERR_INPUT;

    phy_port = rtksw_switch_port_L2P_get(unit, port);
    if (phy_port == UNDEFINE_PHY_PORT)
        return RT_ERR_PORT_ID;

    if ((retVal = rtl8367d_getAsicRegBits(unit, RTL8367D_REG_RLDP_CTRL4, RTL8367D_RLDP_CTRL4_MASK, &portmask))!=RT_ERR_OK)
        return retVal;

    if (pPortConfig->tx_enable)
    {
         portmask |=(1<<phy_port);
    }
    else
    {
         portmask &= ~(1<<phy_port);
    }

    if ((retVal = rtl8367d_setAsicRegBits(unit, RTL8367D_REG_RLDP_CTRL4, RTL8367D_RLDP_CTRL4_MASK, portmask))!=RT_ERR_OK)
        return retVal;

    return RT_ERR_OK;

}

/* Function Name:
 *      dal_rtl8367d_rldp_portConfig_get
 * Description:
 *      Get per port RLDP module configuration
 * Input:
 *      unit        - Unit ID
 *      port        - port number to be get
 * Output:
 *      pPortConfig - per port configuration structure of RLDP
 * Return:
 *      RT_ERR_OK
 *      RT_ERR_FAILED
 *      RT_ERR_INPUT
 *      RT_ERR_NULL_POINTER
 * Note:
 *      None
 */
rtksw_api_ret_t dal_rtl8367d_rldp_portConfig_get(rtksw_uint32 unit, rtksw_port_t port, rtksw_rldp_portConfig_t *pPortConfig)
{
    rtksw_api_ret_t retVal;
    rtksw_uint32 portmask;
    rtksw_portmask_t logicalPmask;

    /* Check initialization state */
    RTKSW_CHK_INIT_STATE(unit);

    /* Check Port Valid */
    RTKSW_CHK_PORT_VALID(unit, port);

    if ((retVal = rtl8367d_getAsicRegBits(unit, RTL8367D_REG_RLDP_CTRL4, RTL8367D_RLDP_CTRL4_MASK, &portmask))!=RT_ERR_OK)
        return retVal;

    if ((retVal = rtksw_switch_portmask_P2L_get(unit, portmask, &logicalPmask)) != RT_ERR_OK)
        return retVal;


    if (logicalPmask.bits[0] & (1<<port))
    {
         pPortConfig->tx_enable = RTKSW_ENABLED;
    }
    else
    {
         pPortConfig->tx_enable = RTKSW_DISABLED;
    }

    return RT_ERR_OK;
}



/* Function Name:
 *      dal_rtl8367d_rldp_status_get
 * Description:
 *      Get RLDP module status
 * Input:
 *      unit        - Unit ID
 * Output:
 *      pStatus - status structure of RLDP
 * Return:
 *      RT_ERR_OK
 *      RT_ERR_FAILED
 *      RT_ERR_NULL_POINTER
 * Note:
 *      None
 */
rtksw_api_ret_t dal_rtl8367d_rldp_status_get(rtksw_uint32 unit, rtksw_rldp_status_t *pStatus)
{
    rtksw_api_ret_t retVal;
    rtksw_uint32 regData;
    rtksw_uint16 *accessPtr;
    rtksw_uint32 i;

    /* Check initialization state */
    RTKSW_CHK_INIT_STATE(unit);

    accessPtr = (rtksw_uint16*)&pStatus->id;
    for(i = 0; i < 3; i++)
    {
        retVal = rtl8367d_getAsicReg(unit, RTL8367D_REG_RLDP_RAND_NUM0+ i, &regData);
        if(retVal != RT_ERR_OK)
            return retVal;

        *accessPtr = regData;
        accessPtr++;
    }

    return RT_ERR_OK;
}

/* Function Name:
 *      dal_rtl8367d_rldp_portStatus_get
 * Description:
 *      Get RLDP module status
 * Input:
 *      unit        - Unit ID
 *      port        - port number to be get
 * Output:
 *      pPortStatus - per port status structure of RLDP
 * Return:
 *      RT_ERR_OK
 *      RT_ERR_FAILED
 *      RT_ERR_INPUT
 *      RT_ERR_NULL_POINTER
 * Note:
 *      None
 */
rtksw_api_ret_t dal_rtl8367d_rldp_portStatus_get(rtksw_uint32 unit, rtksw_port_t port, rtksw_rldp_portStatus_t *pPortStatus)
{
    rtksw_api_ret_t retVal;
    rtksw_uint32 portmask;
    rtksw_portmask_t logicalPmask;

    /* Check initialization state */
    RTKSW_CHK_INIT_STATE(unit);

    /* Check Port Valid */
    RTKSW_CHK_PORT_VALID(unit, port);

    if ((retVal = rtl8367d_getAsicRegBits(unit, RTL8367D_REG_RLDP_LOOPSTATUS_INDICATOR, RTL8367D_RLDP_LOOPSTATUS_INDICATOR_MASK, &portmask))!=RT_ERR_OK)
        return retVal;

    if ((retVal = rtksw_switch_portmask_P2L_get(unit, portmask, &logicalPmask)) != RT_ERR_OK)
        return retVal;

    if (logicalPmask.bits[0] & (1<<port))
    {
         pPortStatus->loop_status = RTKSW_RLDP_LOOPSTS_LOOPING;
    }
    else
    {
         pPortStatus->loop_status  = RTKSW_RLDP_LOOPSTS_NONE;
    }

    if ((retVal = rtl8367d_getAsicRegBits(unit, RTL8367D_REG_RLDP_LOOPED_INDICATOR, RTL8367D_RLDP_LOOPED_INDICATOR_MASK, &portmask))!=RT_ERR_OK)
        return retVal;
    if ((retVal = rtksw_switch_portmask_P2L_get(unit, portmask, &logicalPmask)) != RT_ERR_OK)
        return retVal;

    if (logicalPmask.bits[0] & (1<<port))
    {
         pPortStatus->loop_enter = RTKSW_RLDP_LOOPSTS_LOOPING;
    }
    else
    {
         pPortStatus->loop_enter  = RTKSW_RLDP_LOOPSTS_NONE;
    }

    if ((retVal = rtl8367d_getAsicRegBits(unit, RTL8367D_REG_RLDP_RELEASED_INDICATOR, RTL8367D_RLDP_RELEASED_INDICATOR_MASK, &portmask))!=RT_ERR_OK)
        return retVal;
    if ((retVal = rtksw_switch_portmask_P2L_get(unit, portmask, &logicalPmask)) != RT_ERR_OK)
        return retVal;

    if (logicalPmask.bits[0] & (1<<port))
    {
         pPortStatus->loop_leave = RTKSW_RLDP_LOOPSTS_LOOPING;
    }
    else
    {
         pPortStatus->loop_leave  = RTKSW_RLDP_LOOPSTS_NONE;
    }

    return RT_ERR_OK;
}


/* Function Name:
 *      dal_rtl8367d_rldp_portStatus_clear
 * Description:
 *      Clear RLDP module status
 * Input:
 *      unit        - Unit ID
 *      port        - port number to be clear
 *      pPortStatus - per port status structure of RLDP
 * Output:
 *      None
 * Return:
 *      RT_ERR_OK
 *      RT_ERR_FAILED
 *      RT_ERR_INPUT
 *      RT_ERR_NULL_POINTER
 * Note:
 *      Clear operation effect loop_enter and loop_leave only, other field in
 *      the structure are don't care
 */
rtksw_api_ret_t dal_rtl8367d_rldp_portStatus_set(rtksw_uint32 unit, rtksw_port_t port, rtksw_rldp_portStatus_t *pPortStatus)
{
    rtksw_api_ret_t retVal;
    rtksw_uint32 pmsk;
    rtksw_uint32 phyPort;

    /* Check initialization state */
    RTKSW_CHK_INIT_STATE(unit);

    /* Check Port Valid */
    RTKSW_CHK_PORT_VALID(unit, port);

    phyPort = rtksw_switch_port_L2P_get(unit, port);
    if (phyPort == UNDEFINE_PHY_PORT)
        return RT_ERR_PORT_ID;

    pmsk = (pPortStatus->loop_enter) << phyPort;
    if ((retVal = rtl8367d_setAsicRegBits(unit, RTL8367D_REG_RLDP_LOOPED_INDICATOR, RTL8367D_RLDP_LOOPED_INDICATOR_MASK, pmsk))!=RT_ERR_OK)
        return retVal;
    pmsk = (pPortStatus->loop_leave) << phyPort;
    if ((retVal = rtl8367d_setAsicRegBits(unit, RTL8367D_REG_RLDP_RELEASED_INDICATOR, RTL8367D_RLDP_RELEASED_INDICATOR_MASK, pmsk))!=RT_ERR_OK)
        return retVal;


    return RT_ERR_OK;
}


/* Function Name:
 *      dal_rtl8367d_rldp_portLoopPair_get
 * Description:
 *      Get RLDP port loop pairs
 * Input:
 *      unit        - Unit ID
 *      port        - port number to be get
 * Output:
 *      pPortmask - per port related loop ports
 * Return:
 *      RT_ERR_OK
 *      RT_ERR_FAILED
 *      RT_ERR_INPUT
 *      RT_ERR_NULL_POINTER
 * Note:
 *      None
 */
rtksw_api_ret_t dal_rtl8367d_rldp_portLoopPair_get(rtksw_uint32 unit, rtksw_port_t port, rtksw_portmask_t *pPortmask)
{
    rtksw_api_ret_t retVal;
    rtksw_uint32 pmsk;
    rtksw_uint32 phy_port;
    rtksw_uint32 loopedPair;

    /* Check initialization state */
    RTKSW_CHK_INIT_STATE(unit);

    /* Check Port Valid */
    RTKSW_CHK_PORT_VALID(unit, port);

    phy_port = rtksw_switch_port_L2P_get(unit, port);

    if ((retVal = rtl8367d_getAsicRegBits(unit, RTL8367D_REG_RLDP_LOOP_PORT_REG0 + (phy_port>>1), RTL8367D_RLDP_LOOP_PORT_00_MASK<<((phy_port&1)<<3), &loopedPair))!=RT_ERR_OK)
        return retVal;

    pmsk = 1 << loopedPair;
    if ((retVal = rtksw_switch_portmask_P2L_get(unit, pmsk, pPortmask)) != RT_ERR_OK)
        return retVal;

    return RT_ERR_OK;
}

