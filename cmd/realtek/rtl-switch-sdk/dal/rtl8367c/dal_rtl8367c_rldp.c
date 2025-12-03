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
#include "dal_rtl8367c_rldp.h"


#include "rtl8367c_asicdrv.h"
#include "rtl8367c_asicdrv_rldp.h"

#include "../dal_mgmts.h"
#include "../../osal/lib.h"

/* Function Name:
 *      dal_rtl8367c_rldp_config_set
 * Description:
 *      Set RLDP module configuration
 * Input:
 *      unit    - Unit ID
 *      pConfig - configuration structure of RLDP
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
rtksw_api_ret_t dal_rtl8367c_rldp_config_set(rtksw_uint32 unit, rtksw_rldp_config_t *pConfig)
{
    rtksw_api_ret_t retVal;
    ether_addr_t magic;
    rtksw_uint32 pmsk;

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

    if ((retVal = rtl8367c_getAsicRldpTxPortmask(unit, &pmsk))!=RT_ERR_OK)
        return retVal;

    if ((retVal = rtl8367c_setAsicRldpTxPortmask(unit, 0x00))!=RT_ERR_OK)
        return retVal;

    if ((retVal = rtl8367c_setAsicRldpTxPortmask(unit, pmsk))!=RT_ERR_OK)
        return retVal;

    if ((retVal = rtl8367c_setAsicRldp(unit, pConfig->rldp_enable))!=RT_ERR_OK)
        return retVal;

    if ((retVal = rtl8367c_setAsicRldpTriggerMode(unit, pConfig->trigger_mode))!=RT_ERR_OK)
        return retVal;

    osal_memcpy(&magic, &pConfig->magic, sizeof(ether_addr_t));
    if ((retVal = rtl8367c_setAsicRldpMagicNum(unit, magic))!=RT_ERR_OK)
        return retVal;

    if ((retVal = rtl8367c_setAsicRldpCompareRandomNumber(unit, pConfig->compare_type))!=RT_ERR_OK)
        return retVal;

    if ((retVal = rtl8367c_setAsicRldpCompareRandomNumber(unit, pConfig->compare_type))!=RT_ERR_OK)
        return retVal;

    if ((retVal = rtl8367c_setAsicRldpCheckingStatePara(unit, pConfig->num_check, pConfig->interval_check))!=RT_ERR_OK)
        return retVal;

    if ((retVal = rtl8367c_setAsicRldpLoopStatePara(unit, pConfig->num_loop, pConfig->interval_loop))!=RT_ERR_OK)
        return retVal;

    return RT_ERR_OK;
}

/* Function Name:
 *      dal_rtl8367c_rldp_config_get
 * Description:
 *      Get RLDP module configuration
 * Input:
 *      unit    - Unit ID
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
rtksw_api_ret_t dal_rtl8367c_rldp_config_get(rtksw_uint32 unit, rtksw_rldp_config_t *pConfig)
{
    rtksw_api_ret_t retVal;
    ether_addr_t magic;

    /* Check initialization state */
    RTKSW_CHK_INIT_STATE(unit);

    if ((retVal = rtl8367c_getAsicRldp(unit, &pConfig->rldp_enable))!=RT_ERR_OK)
        return retVal;

    if ((retVal = rtl8367c_getAsicRldpTriggerMode(unit, &pConfig->trigger_mode))!=RT_ERR_OK)
        return retVal;

    if ((retVal = rtl8367c_getAsicRldpMagicNum(unit, &magic))!=RT_ERR_OK)
        return retVal;
    osal_memcpy(&pConfig->magic, &magic, sizeof(ether_addr_t));

    if ((retVal = rtl8367c_getAsicRldpCompareRandomNumber(unit, &pConfig->compare_type))!=RT_ERR_OK)
        return retVal;

    if ((retVal = rtl8367c_getAsicRldpCompareRandomNumber(unit, &pConfig->compare_type))!=RT_ERR_OK)
        return retVal;

    if ((retVal = rtl8367c_getAsicRldpCheckingStatePara(unit, &pConfig->num_check, &pConfig->interval_check))!=RT_ERR_OK)
        return retVal;

    if ((retVal = rtl8367c_getAsicRldpLoopStatePara(unit, &pConfig->num_loop, &pConfig->interval_loop))!=RT_ERR_OK)
        return retVal;

    return RT_ERR_OK;
}


/* Function Name:
 *      dal_rtl8367c_rldp_portConfig_set
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
rtksw_api_ret_t dal_rtl8367c_rldp_portConfig_set(rtksw_uint32 unit, rtksw_port_t port, rtksw_rldp_portConfig_t *pPortConfig)
{
    rtksw_api_ret_t retVal;
    rtksw_uint32 pmsk;
    rtksw_uint32 phyPort;

    /* Check initialization state */
    RTKSW_CHK_INIT_STATE(unit);

    /* Check Port Valid */
    RTKSW_CHK_PORT_VALID(unit, port);

    if (pPortConfig->tx_enable>= RTKSW_ENABLE_END)
        return RT_ERR_INPUT;

    phyPort = rtksw_switch_port_L2P_get(unit, port);
    if (phyPort == UNDEFINE_PHY_PORT)
        return RT_ERR_PORT_ID;

    if ((retVal = rtl8367c_getAsicRldpTxPortmask(unit, &pmsk))!=RT_ERR_OK)
        return retVal;

    if (pPortConfig->tx_enable)
    {
         pmsk |=(1<<phyPort);
    }
    else
    {
         pmsk &= ~(1<<phyPort);
    }

    if ((retVal = rtl8367c_setAsicRldpTxPortmask(unit, pmsk))!=RT_ERR_OK)
        return retVal;

    return RT_ERR_OK;

}

/* Function Name:
 *      dal_rtl8367c_rldp_portConfig_get
 * Description:
 *      Get per port RLDP module configuration
 * Input:
 *      unit    - Unit ID
 *      port    - port number to be get
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
rtksw_api_ret_t dal_rtl8367c_rldp_portConfig_get(rtksw_uint32 unit, rtksw_port_t port, rtksw_rldp_portConfig_t *pPortConfig)
{
    rtksw_api_ret_t retVal;
    rtksw_uint32 pmsk;
    rtksw_portmask_t logicalPmask;

    /* Check initialization state */
    RTKSW_CHK_INIT_STATE(unit);

    /* Check Port Valid */
    RTKSW_CHK_PORT_VALID(unit, port);

    if ((retVal = rtl8367c_getAsicRldpTxPortmask(unit, &pmsk))!=RT_ERR_OK)
        return retVal;

    if ((retVal = rtksw_switch_portmask_P2L_get(unit, pmsk, &logicalPmask)) != RT_ERR_OK)
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
 *      dal_rtl8367c_rldp_status_get
 * Description:
 *      Get RLDP module status
 * Input:
 *      unit    - Unit ID
 * Output:
 *      pStatus - status structure of RLDP
 * Return:
 *      RT_ERR_OK
 *      RT_ERR_FAILED
 *      RT_ERR_NULL_POINTER
 * Note:
 *      None
 */
rtksw_api_ret_t dal_rtl8367c_rldp_status_get(rtksw_uint32 unit, rtksw_rldp_status_t *pStatus)
{
    rtksw_api_ret_t retVal;
    ether_addr_t seed;

    /* Check initialization state */
    RTKSW_CHK_INIT_STATE(unit);

    if ((retVal = rtl8367c_getAsicRldpRandomNumber(unit, &seed))!=RT_ERR_OK)
        return retVal;
    osal_memcpy(&pStatus->id, &seed, sizeof(ether_addr_t));

    return RT_ERR_OK;
}

/* Function Name:
 *      dal_rtl8367c_rldp_portStatus_get
 * Description:
 *      Get RLDP module status
 * Input:
 *      unit    - Unit ID
 *      port    - port number to be get
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
rtksw_api_ret_t dal_rtl8367c_rldp_portStatus_get(rtksw_uint32 unit, rtksw_port_t port, rtksw_rldp_portStatus_t *pPortStatus)
{
    rtksw_api_ret_t retVal;
    rtksw_uint32 pmsk;
    rtksw_portmask_t logicalPmask;

    /* Check initialization state */
    RTKSW_CHK_INIT_STATE(unit);

    /* Check Port Valid */
    RTKSW_CHK_PORT_VALID(unit, port);

    if ((retVal = rtl8367c_getAsicRldpLoopedPortmask(unit, &pmsk))!=RT_ERR_OK)
        return retVal;
    if ((retVal = rtksw_switch_portmask_P2L_get(unit, pmsk, &logicalPmask)) != RT_ERR_OK)
        return retVal;

    if (logicalPmask.bits[0] & (1<<port))
    {
         pPortStatus->loop_status = RTKSW_RLDP_LOOPSTS_LOOPING;
    }
    else
    {
         pPortStatus->loop_status  = RTKSW_RLDP_LOOPSTS_NONE;
    }

    if ((retVal = rtl8367c_getAsicRldpEnterLoopedPortmask(unit, &pmsk))!=RT_ERR_OK)
        return retVal;
    if ((retVal = rtksw_switch_portmask_P2L_get(unit, pmsk, &logicalPmask)) != RT_ERR_OK)
        return retVal;

    if (logicalPmask.bits[0] & (1<<port))
    {
         pPortStatus->loop_enter = RTKSW_RLDP_LOOPSTS_LOOPING;
    }
    else
    {
         pPortStatus->loop_enter  = RTKSW_RLDP_LOOPSTS_NONE;
    }

    if ((retVal = rtl8367c_getAsicRldpLeaveLoopedPortmask(unit, &pmsk))!=RT_ERR_OK)
        return retVal;
    if ((retVal = rtksw_switch_portmask_P2L_get(unit, pmsk, &logicalPmask)) != RT_ERR_OK)
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
 *      dal_rtl8367c_rldp_portStatus_clear
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
rtksw_api_ret_t dal_rtl8367c_rldp_portStatus_set(rtksw_uint32 unit, rtksw_port_t port, rtksw_rldp_portStatus_t *pPortStatus)
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
    if ((retVal = rtl8367c_setAsicRldpEnterLoopedPortmask(unit, pmsk))!=RT_ERR_OK)
        return retVal;

    pmsk = (pPortStatus->loop_leave) << phyPort;
    if ((retVal = rtl8367c_setAsicRldpLeaveLoopedPortmask(unit, pmsk))!=RT_ERR_OK)
        return retVal;

    return RT_ERR_OK;
}


/* Function Name:
 *      dal_rtl8367c_rldp_portLoopPair_get
 * Description:
 *      Get RLDP port loop pairs
 * Input:
 *      unit    - Unit ID
 *      port    - port number to be get
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
rtksw_api_ret_t dal_rtl8367c_rldp_portLoopPair_get(rtksw_uint32 unit, rtksw_port_t port, rtksw_portmask_t *pPortmask)
{
    rtksw_api_ret_t retVal;
    rtksw_uint32 pmsk;

    /* Check initialization state */
    RTKSW_CHK_INIT_STATE(unit);

    /* Check Port Valid */
    RTKSW_CHK_PORT_VALID(unit, port);

    if ((retVal = rtl8367c_getAsicRldpLoopedPortPair(unit, rtksw_switch_port_L2P_get(unit, port), &pmsk))!=RT_ERR_OK)
        return retVal;

    if ((retVal = rtksw_switch_portmask_P2L_get(unit, pmsk, pPortmask)) != RT_ERR_OK)
        return retVal;

    return RT_ERR_OK;
}

