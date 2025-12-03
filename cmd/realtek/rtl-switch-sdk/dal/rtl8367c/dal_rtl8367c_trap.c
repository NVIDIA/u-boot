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
 * Purpose : RTK switch high-level API for RTL8367/RTL8367C
 * Feature : Here is a list of all functions and variables in Trap module.
 *
 */

#include "../../rtk_switch.h"
#include "../../rtk_error.h"
#include "dal_rtl8367c_trap.h"

#include "rtl8367c_asicdrv.h"
#include "rtl8367c_asicdrv_port.h"
#include "rtl8367c_asicdrv_igmp.h"
#include "rtl8367c_asicdrv_rma.h"
#include "rtl8367c_asicdrv_eav.h"
#include "rtl8367c_asicdrv_oam.h"
#include "rtl8367c_asicdrv_svlan.h"
#include "rtl8367c_asicdrv_unknownMulticast.h"
#include "rtl8367c_asicdrv_dot1x.h"

#include "../dal_mgmts.h"

/* Function Name:
 *      rtksw_trap_unknownUnicastPktAction_set
 * Description:
 *      Set unknown unicast packet action configuration.
 * Input:
 *      unit            - Unit ID
 *      port            - ingress port ID for unknown unicast packet
 *      ucast_action    - Unknown unicast action.
 * Output:
 *      None
 * Return:
 *      RT_ERR_OK                  - OK
 *      RT_ERR_FAILED              - Failed
 *      RT_ERR_SMI                 - SMI access error
 *      RT_ERR_NOT_ALLOWED         - Invalid action.
 *      RT_ERR_INPUT               - Invalid input parameters.
 * Note:
 *      This API can set unknown unicast packet action configuration.
 *      The unknown unicast action is as following:
 *          - UCAST_ACTION_FORWARD_PMASK
 *          - UCAST_ACTION_DROP
 *          - UCAST_ACTION_TRAP2CPU
 *          - UCAST_ACTION_FLOODING
 */
rtksw_api_ret_t dal_rtl8367c_trap_unknownUnicastPktAction_set(rtksw_uint32 unit, rtksw_port_t port, rtksw_trap_ucast_action_t ucast_action)
{
    rtksw_api_ret_t retVal;

    /* Check initialization state */
    RTKSW_CHK_INIT_STATE(unit);

    /* check port valid */
    RTKSW_CHK_PORT_VALID(unit, port);

    if (ucast_action >= UCAST_ACTION_COPY28051)
        return RT_ERR_INPUT;

    if ((retVal = rtl8367c_setAsicPortUnknownDaBehavior(unit, rtksw_switch_port_L2P_get(unit, port), ucast_action)) != RT_ERR_OK)
        return retVal;

    return RT_ERR_OK;
}

/* Function Name:
 *      rtksw_trap_unknownUnicastPktAction_get
 * Description:
 *      Get unknown unicast packet action configuration.
 * Input:
 *      unit            - Unit ID
 *      port            - ingress port ID for unknown unicast packet
 * Output:
 *      pUcast_action   - Unknown unicast action.
 * Return:
 *      RT_ERR_OK                  - OK
 *      RT_ERR_FAILED              - Failed
 *      RT_ERR_SMI                 - SMI access error
 *      RT_ERR_NOT_ALLOWED         - Invalid action.
 *      RT_ERR_INPUT               - Invalid input parameters.
 *      RT_ERR_NULL_POINTER        - Null pointer
 * Note:
 *      This API can get unknown unicast packet action configuration.
 *      The unknown unicast action is as following:
 *          - UCAST_ACTION_FORWARD_PMASK
 *          - UCAST_ACTION_DROP
 *          - UCAST_ACTION_TRAP2CPU
 *          - UCAST_ACTION_FLOODING
 */
rtksw_api_ret_t dal_rtl8367c_trap_unknownUnicastPktAction_get(rtksw_uint32 unit, rtksw_port_t port, rtksw_trap_ucast_action_t *pUcast_action)
{
    rtksw_api_ret_t retVal;

    /* Check initialization state */
    RTKSW_CHK_INIT_STATE(unit);

    /* check port valid */
    RTKSW_CHK_PORT_VALID(unit, port);

    if (NULL == pUcast_action)
        return RT_ERR_NULL_POINTER;

    if ((retVal = rtl8367c_getAsicPortUnknownDaBehavior(unit, rtksw_switch_port_L2P_get(unit, port), pUcast_action)) != RT_ERR_OK)
        return retVal;

    return RT_ERR_OK;
}

/* Function Name:
 *      rtksw_trap_unknownMacPktAction_set
 * Description:
 *      Set unknown source MAC packet action configuration.
 * Input:
 *      unit            - Unit ID
 *      ucast_action    - Unknown source MAC action.
 * Output:
 *      None
 * Return:
 *      RT_ERR_OK                  - OK
 *      RT_ERR_FAILED              - Failed
 *      RT_ERR_SMI                 - SMI access error
 *      RT_ERR_NOT_ALLOWED         - Invalid action.
 *      RT_ERR_INPUT               - Invalid input parameters.
 * Note:
 *      This API can set unknown unicast packet action configuration.
 *      The unknown unicast action is as following:
 *          - UCAST_ACTION_FORWARD_PMASK
 *          - UCAST_ACTION_DROP
 *          - UCAST_ACTION_TRAP2CPU
 *          - UCAST_ACTION_COPY28051
 */
rtksw_api_ret_t dal_rtl8367c_trap_unknownMacPktAction_set(rtksw_uint32 unit, rtksw_trap_ucast_action_t ucast_action)
{
    rtksw_api_ret_t retVal;
    rtksw_uint32 behavior;

    /* Check initialization state */
    RTKSW_CHK_INIT_STATE(unit);

    switch (ucast_action)
    {
        case UCAST_ACTION_FORWARD_PMASK:
            behavior = L2_BEHAVE_SA_FLOODING;
            break;
        case UCAST_ACTION_DROP:
            behavior = L2_BEHAVE_SA_DROP;
            break;
        case UCAST_ACTION_TRAP2CPU:
            behavior = L2_BEHAVE_SA_TRAP;
            break;
        case UCAST_ACTION_COPY28051:
            behavior = L2_BEHAVE_SA_COPY28051;
            break;
        default:
            return RT_ERR_INPUT;
            break;
    }

    if ((retVal = rtl8367c_setAsicPortUnknownSaBehavior(unit, behavior)) != RT_ERR_OK)
        return retVal;

    return RT_ERR_OK;
}

/* Function Name:
 *      rtksw_trap_unknownMacPktAction_get
 * Description:
 *      Get unknown source MAC packet action configuration.
 * Input:
 *      unit            - Unit ID
 * Output:
 *      pUcast_action   - Unknown source MAC action.
 * Return:
 *      RT_ERR_OK                  - OK
 *      RT_ERR_FAILED              - Failed
 *      RT_ERR_SMI                 - SMI access error
 *      RT_ERR_NULL_POINTER        - Null Pointer.
 *      RT_ERR_INPUT               - Invalid input parameters.
 * Note:
 *
 */
rtksw_api_ret_t dal_rtl8367c_trap_unknownMacPktAction_get(rtksw_uint32 unit, rtksw_trap_ucast_action_t *pUcast_action)
{
    rtksw_api_ret_t retVal;
    rtksw_uint32 behavior;

    /* Check initialization state */
    RTKSW_CHK_INIT_STATE(unit);

    if(NULL == pUcast_action)
        return RT_ERR_NULL_POINTER;

    if ((retVal = rtl8367c_getAsicPortUnknownSaBehavior(unit, &behavior)) != RT_ERR_OK)
        return retVal;

    switch (behavior)
    {
        case L2_BEHAVE_SA_FLOODING:
            *pUcast_action = UCAST_ACTION_FORWARD_PMASK;
            break;
        case L2_BEHAVE_SA_DROP:
            *pUcast_action = UCAST_ACTION_DROP;
            break;
        case L2_BEHAVE_SA_TRAP:
            *pUcast_action = UCAST_ACTION_TRAP2CPU;
            break;
        case L2_BEHAVE_SA_COPY28051:
            *pUcast_action = UCAST_ACTION_COPY28051;
            break;
        default:
            return RT_ERR_FAILED;
            break;
    }

    return RT_ERR_OK;
}

/* Function Name:
 *      rtksw_trap_unmatchMacPktAction_set
 * Description:
 *      Set unmatch source MAC packet action configuration.
 * Input:
 *      unit            - Unit ID
 *      ucast_action    - Unknown source MAC action.
 * Output:
 *      None
 * Return:
 *      RT_ERR_OK                  - OK
 *      RT_ERR_FAILED              - Failed
 *      RT_ERR_SMI                 - SMI access error
 *      RT_ERR_NOT_ALLOWED         - Invalid action.
 *      RT_ERR_INPUT               - Invalid input parameters.
 * Note:
 *      This API can set unknown unicast packet action configuration.
 *      The unknown unicast action is as following:
 *          - UCAST_ACTION_FORWARD_PMASK
 *          - UCAST_ACTION_DROP
 *          - UCAST_ACTION_TRAP2CPU
 *          - UCAST_ACTION_COPY28051
 */
rtksw_api_ret_t dal_rtl8367c_trap_unmatchMacPktAction_set(rtksw_uint32 unit, rtksw_trap_ucast_action_t ucast_action)
{
    rtksw_api_ret_t retVal;
    rtksw_uint32 behavior;

    /* Check initialization state */
    RTKSW_CHK_INIT_STATE(unit);

    switch (ucast_action)
    {
        case UCAST_ACTION_FORWARD_PMASK:
            behavior = L2_BEHAVE_SA_FLOODING;
            break;
        case UCAST_ACTION_DROP:
            behavior = L2_BEHAVE_SA_DROP;
            break;
        case UCAST_ACTION_TRAP2CPU:
            behavior = L2_BEHAVE_SA_TRAP;
            break;
        case UCAST_ACTION_COPY28051:
            behavior = L2_BEHAVE_SA_COPY28051;
            break;
        default:
            return RT_ERR_INPUT;
            break;
    }

    if ((retVal = rtl8367c_setAsicPortUnmatchedSaBehavior(unit, behavior)) != RT_ERR_OK)
        return retVal;

    return RT_ERR_OK;
}

/* Function Name:
 *      rtksw_trap_unmatchMacPktAction_get
 * Description:
 *      Get unmatch source MAC packet action configuration.
 * Input:
 *      unit            - Unit ID
 * Output:
 *      pUcast_action   - Unknown source MAC action.
 * Return:
 *      RT_ERR_OK                  - OK
 *      RT_ERR_FAILED              - Failed
 *      RT_ERR_SMI                 - SMI access error
 *      RT_ERR_NOT_ALLOWED         - Invalid action.
 *      RT_ERR_INPUT               - Invalid input parameters.
 * Note:
 *      This API can set unknown unicast packet action configuration.
 *      The unknown unicast action is as following:
 *          - UCAST_ACTION_FORWARD_PMASK
 *          - UCAST_ACTION_DROP
 *          - UCAST_ACTION_TRAP2CPU
 */
rtksw_api_ret_t dal_rtl8367c_trap_unmatchMacPktAction_get(rtksw_uint32 unit, rtksw_trap_ucast_action_t *pUcast_action)
{
    rtksw_api_ret_t retVal;
    rtksw_uint32 behavior;

    /* Check initialization state */
    RTKSW_CHK_INIT_STATE(unit);

    if(NULL == pUcast_action)
        return RT_ERR_NULL_POINTER;

    if ((retVal = rtl8367c_getAsicPortUnmatchedSaBehavior(unit, &behavior)) != RT_ERR_OK)
        return retVal;

    switch (behavior)
    {
        case L2_BEHAVE_SA_FLOODING:
            *pUcast_action = UCAST_ACTION_FORWARD_PMASK;
            break;
        case L2_BEHAVE_SA_DROP:
            *pUcast_action = UCAST_ACTION_DROP;
            break;
        case L2_BEHAVE_SA_TRAP:
            *pUcast_action = UCAST_ACTION_TRAP2CPU;
            break;
        case L2_BEHAVE_SA_COPY28051:
            *pUcast_action = UCAST_ACTION_COPY28051;
            break;
        default:
            return RT_ERR_FAILED;
            break;
    }

    return RT_ERR_OK;
}

/* Function Name:
 *      rtksw_trap_unmatchMacMoving_set
 * Description:
 *      Set unmatch source MAC packet moving state.
 * Input:
 *      unit            - Unit ID
 *      port            - Port ID.
 *      enable          - RTKSW_ENABLED: allow SA moving, DISABLE: don't allow SA moving.
 * Output:
 *      None
 * Return:
 *      RT_ERR_OK                  - OK
 *      RT_ERR_FAILED              - Failed
 *      RT_ERR_SMI                 - SMI access error
 *      RT_ERR_NOT_ALLOWED         - Invalid action.
 *      RT_ERR_INPUT               - Invalid input parameters.
 * Note:
 */
rtksw_api_ret_t dal_rtl8367c_trap_unmatchMacMoving_set(rtksw_uint32 unit, rtksw_port_t port, rtksw_enable_t enable)
{
    rtksw_api_ret_t retVal;

    /* Check initialization state */
    RTKSW_CHK_INIT_STATE(unit);

    /* check port valid */
    RTKSW_CHK_PORT_VALID(unit, port);

    if(enable >= RTKSW_ENABLE_END)
        return RT_ERR_INPUT;

    if ((retVal = rtl8367c_setAsicPortUnmatchedSaMoving(unit, rtksw_switch_port_L2P_get(unit, port), enable)) != RT_ERR_OK)
        return retVal;

    return RT_ERR_OK;
}

/* Function Name:
 *      rtksw_trap_unmatchMacMoving_get
 * Description:
 *      Set unmatch source MAC packet moving state.
 * Input:
 *      unit        - Unit ID
 *      port        - Port ID.
 * Output:
 *      pEnable     - RTKSW_ENABLED: allow SA moving, DISABLE: don't allow SA moving.
 * Return:
 *      RT_ERR_OK                  - OK
 *      RT_ERR_FAILED              - Failed
 *      RT_ERR_SMI                 - SMI access error
 *      RT_ERR_NOT_ALLOWED         - Invalid action.
 *      RT_ERR_INPUT               - Invalid input parameters.
 * Note:
 */
rtksw_api_ret_t dal_rtl8367c_trap_unmatchMacMoving_get(rtksw_uint32 unit, rtksw_port_t port, rtksw_enable_t *pEnable)
{
    rtksw_api_ret_t retVal;

    /* Check initialization state */
    RTKSW_CHK_INIT_STATE(unit);

    /* check port valid */
    RTKSW_CHK_PORT_VALID(unit, port);

    if(NULL == pEnable)
        return RT_ERR_NULL_POINTER;

    if ((retVal = rtl8367c_getAsicPortUnmatchedSaMoving(unit, rtksw_switch_port_L2P_get(unit, port), pEnable)) != RT_ERR_OK)
        return retVal;

    return RT_ERR_OK;
}

/* Function Name:
 *      rtksw_trap_unknownMcastPktAction_set
 * Description:
 *      Set behavior of unknown multicast
 * Input:
 *      unit            - Unit ID
 *      port            - Port id.
 *      type            - unknown multicast packet type.
 *      mcast_action    - unknown multicast action.
 * Output:
 *      None
 * Return:
 *      RT_ERR_OK           - OK
 *      RT_ERR_FAILED       - Failed
 *      RT_ERR_SMI          - SMI access error
 *      RT_ERR_PORT_ID         - Invalid port number.
 *      RT_ERR_NOT_ALLOWED     - Invalid action.
 *      RT_ERR_INPUT         - Invalid input parameters.
 * Note:
 *      When receives an unknown multicast packet, switch may trap, drop or flood this packet
 *      (1) The unknown multicast packet type is as following:
 *          - MCAST_L2
 *          - MCAST_IPV4
 *          - MCAST_IPV6
 *      (2) The unknown multicast action is as following:
 *          - MCAST_ACTION_FORWARD
 *          - MCAST_ACTION_DROP
 *          - MCAST_ACTION_TRAP2CPU
 */
rtksw_api_ret_t dal_rtl8367c_trap_unknownMcastPktAction_set(rtksw_uint32 unit, rtksw_port_t port, rtksw_mcast_type_t type, rtksw_trap_mcast_action_t mcast_action)
{
    rtksw_api_ret_t retVal;
    rtksw_uint32 rawAction;

    /* Check initialization state */
    RTKSW_CHK_INIT_STATE(unit);

    /* Check Port Valid */
    RTKSW_CHK_PORT_VALID(unit, port);

    if (type >= MCAST_END)
        return RT_ERR_INPUT;

    if (mcast_action >= MCAST_ACTION_END)
        return RT_ERR_INPUT;


    switch (type)
    {
        case MCAST_L2:
            if (MCAST_ACTION_ROUTER_PORT == mcast_action)
                return RT_ERR_INPUT;
            else if(MCAST_ACTION_DROP_EX_RMA == mcast_action)
                rawAction = L2_UNKOWN_MULTICAST_DROP_EXCLUDE_RMA;
            else
                rawAction = (rtksw_uint32)mcast_action;

            if ((retVal = rtl8367c_setAsicUnknownL2MulticastBehavior(unit, rtksw_switch_port_L2P_get(unit, port), rawAction)) != RT_ERR_OK)
                return retVal;

            break;
        case MCAST_IPV4:
            if (MCAST_ACTION_DROP_EX_RMA == mcast_action)
                return RT_ERR_INPUT;
            else
                rawAction = (rtksw_uint32)mcast_action;

            if ((retVal = rtl8367c_setAsicUnknownIPv4MulticastBehavior(unit, rtksw_switch_port_L2P_get(unit, port), rawAction)) != RT_ERR_OK)
                return retVal;

            break;
        case MCAST_IPV6:
            if (MCAST_ACTION_DROP_EX_RMA == mcast_action)
                return RT_ERR_INPUT;
            else
                rawAction = (rtksw_uint32)mcast_action;

            if ((retVal = rtl8367c_setAsicUnknownIPv6MulticastBehavior(unit, rtksw_switch_port_L2P_get(unit, port), rawAction)) != RT_ERR_OK)
                return retVal;

            break;
        default:
            break;
    }

    return RT_ERR_OK;
}

/* Function Name:
 *      rtksw_trap_unknownMcastPktAction_get
 * Description:
 *      Get behavior of unknown multicast
 * Input:
 *      unit            - Unit ID
 *      type            - unknown multicast packet type.
 * Output:
 *      pMcast_action - unknown multicast action.
 * Return:
 *      RT_ERR_OK                  - OK
 *      RT_ERR_FAILED              - Failed
 *      RT_ERR_SMI                 - SMI access error
 *      RT_ERR_PORT_ID             - Invalid port number.
 *      RT_ERR_NOT_ALLOWED         - Invalid operation.
 *      RT_ERR_INPUT             - Invalid input parameters.
 * Note:
 *      When receives an unknown multicast packet, switch may trap, drop or flood this packet
 *      (1) The unknown multicast packet type is as following:
 *          - MCAST_L2
 *          - MCAST_IPV4
 *          - MCAST_IPV6
 *      (2) The unknown multicast action is as following:
 *          - MCAST_ACTION_FORWARD
 *          - MCAST_ACTION_DROP
 *          - MCAST_ACTION_TRAP2CPU
 */
rtksw_api_ret_t dal_rtl8367c_trap_unknownMcastPktAction_get(rtksw_uint32 unit, rtksw_port_t port, rtksw_mcast_type_t type, rtksw_trap_mcast_action_t *pMcast_action)
{
    rtksw_api_ret_t retVal;
    rtksw_uint32 rawAction;

    /* Check initialization state */
    RTKSW_CHK_INIT_STATE(unit);

    /* Check Port Valid */
    RTKSW_CHK_PORT_VALID(unit, port);

    if (type >= MCAST_END)
        return RT_ERR_INPUT;

    if(NULL == pMcast_action)
        return RT_ERR_NULL_POINTER;

    switch (type)
    {
        case MCAST_L2:
            if ((retVal = rtl8367c_getAsicUnknownL2MulticastBehavior(unit, rtksw_switch_port_L2P_get(unit, port), &rawAction)) != RT_ERR_OK)
                return retVal;

            if(L2_UNKOWN_MULTICAST_DROP_EXCLUDE_RMA == rawAction)
                *pMcast_action = MCAST_ACTION_DROP_EX_RMA;
            else
                *pMcast_action = (rtksw_trap_mcast_action_t)rawAction;

            break;
        case MCAST_IPV4:
            if ((retVal = rtl8367c_getAsicUnknownIPv4MulticastBehavior(unit, rtksw_switch_port_L2P_get(unit, port), &rawAction)) != RT_ERR_OK)
                return retVal;

            *pMcast_action = (rtksw_trap_mcast_action_t)rawAction;
            break;
        case MCAST_IPV6:
            if ((retVal = rtl8367c_getAsicUnknownIPv6MulticastBehavior(unit, rtksw_switch_port_L2P_get(unit, port), &rawAction)) != RT_ERR_OK)
                return retVal;

            *pMcast_action = (rtksw_trap_mcast_action_t)rawAction;
            break;
        default:
            break;
    }

    return RT_ERR_OK;
}

/* Function Name:
 *      rtksw_trap_lldpEnable_set
 * Description:
 *      Set LLDP enable.
 * Input:
 *      unit            - Unit ID
 *      enabled         - LLDP enable, 0: follow RMA, 1: use LLDP action.
 * Output:
 *      None
 * Return:
 *      RT_ERR_OK                  - OK
 *      RT_ERR_FAILED              - Failed
 *      RT_ERR_SMI                 - SMI access error
 *      RT_ERR_NOT_ALLOWED         - Invalid action.
 *      RT_ERR_INPUT             - Invalid input parameters.
 * Note:
 *      - DMAC                                                 Assignment
 *      - 01:80:c2:00:00:0e ethertype = 0x88CC    LLDP
 *      - 01:80:c2:00:00:03 ethertype = 0x88CC
 *      - 01:80:c2:00:00:00 ethertype = 0x88CC

 */
rtksw_api_ret_t dal_rtl8367c_trap_lldpEnable_set(rtksw_uint32 unit, rtksw_enable_t enabled)
{
    rtksw_api_ret_t retVal;
    rtl8367c_rma_t rmacfg;
    rtksw_enable_t tmp;

    /* Check initialization state */
    RTKSW_CHK_INIT_STATE(unit);

    if (enabled >= RTKSW_ENABLE_END)
        return RT_ERR_ENABLE;

    if ((retVal = rtl8367c_getAsicRmaLldp(unit, &tmp, &rmacfg)) != RT_ERR_OK)
        return retVal;

    if ((retVal = rtl8367c_setAsicRmaLldp(unit, enabled, &rmacfg)) != RT_ERR_OK)
        return retVal;

    return RT_ERR_OK;
}

/* Function Name:
 *      rtksw_trap_lldpEnable_get
 * Description:
 *      Get LLDP status.
 * Input:
 *      unit            - Unit ID
 * Output:
 *      pEnabled - LLDP enable, 0: follow RMA, 1: use LLDP action.
 * Return:
 *      RT_ERR_OK           - OK
 *      RT_ERR_FAILED       - Failed
 *      RT_ERR_SMI          - SMI access error
 *      RT_ERR_INPUT         - Invalid input parameters.
 * Note:
 *      LLDP is as following definition.
 *      - DMAC                                                 Assignment
 *      - 01:80:c2:00:00:0e ethertype = 0x88CC    LLDP
 *      - 01:80:c2:00:00:03 ethertype = 0x88CC
 *      - 01:80:c2:00:00:00 ethertype = 0x88CC
 */
rtksw_api_ret_t dal_rtl8367c_trap_lldpEnable_get(rtksw_uint32 unit, rtksw_enable_t *pEnabled)
{
    rtksw_api_ret_t retVal;
    rtl8367c_rma_t rmacfg;

    /* Check initialization state */
    RTKSW_CHK_INIT_STATE(unit);

    if(NULL == pEnabled)
        return RT_ERR_NULL_POINTER;

    if ((retVal = rtl8367c_getAsicRmaLldp(unit, pEnabled, &rmacfg)) != RT_ERR_OK)
        return retVal;

    return RT_ERR_OK;
}

/* Function Name:
 *      rtksw_trap_reasonTrapToCpuPriority_set
 * Description:
 *      Set priority value of a packet that trapped to CPU port according to specific reason.
 * Input:
 *      unit            - Unit ID
 *      type            - reason that trap to CPU port.
 *      priority        - internal priority that is going to be set for specific trap reason.
 * Output:
 *      None.
 * Return:
 *      RT_ERR_OK
 *      RT_ERR_FAILED
 *      RT_ERR_NOT_INIT - The module is not initial
 *      RT_ERR_INPUT    - Invalid input parameter
 * Note:
 *      Currently the trap reason that supported are listed as follows:
 *      - TRAP_REASON_RMA
 *      - TRAP_REASON_OAM
 *      - TRAP_REASON_1XUNAUTH
 *      - TRAP_REASON_VLANSTACK
 *      - TRAP_REASON_UNKNOWNMC
 */
rtksw_api_ret_t dal_rtl8367c_trap_reasonTrapToCpuPriority_set(rtksw_uint32 unit, rtksw_trap_reason_type_t type, rtksw_pri_t priority)
{
    rtksw_api_ret_t retVal;
    rtl8367c_rma_t rmacfg;

    /* Check initialization state */
    RTKSW_CHK_INIT_STATE(unit);

    if (type >= TRAP_REASON_END)
        return RT_ERR_INPUT;

    if (priority > RTL8367C_PRIMAX)
        return  RT_ERR_QOS_INT_PRIORITY;

    switch (type)
    {
        case TRAP_REASON_RMA:
            if ((retVal = rtl8367c_getAsicRma(unit, 0, &rmacfg)) != RT_ERR_OK)
                return retVal;
            rmacfg.trap_priority= priority;
            if ((retVal = rtl8367c_setAsicRma(unit, 0, &rmacfg)) != RT_ERR_OK)
                return retVal;

            break;
        case TRAP_REASON_OAM:
            if ((retVal = rtl8367c_setAsicOamCpuPri(unit, priority)) != RT_ERR_OK)
                return retVal;

            break;
        case TRAP_REASON_1XUNAUTH:
            if ((retVal = rtl8367c_setAsic1xTrapPriority(unit, priority)) != RT_ERR_OK)
                return retVal;

            break;
        case TRAP_REASON_VLANSTACK:
            if ((retVal = rtl8367c_setAsicSvlanTrapPriority(unit, priority)) != RT_ERR_OK)
                return retVal;

            break;
        case TRAP_REASON_UNKNOWNMC:
            if ((retVal = rtl8367c_setAsicUnknownMulticastTrapPriority(unit, priority)) != RT_ERR_OK)
                return retVal;

            break;
        default:
            return RT_ERR_CHIP_NOT_SUPPORTED;
    }


    return RT_ERR_OK;
}

/* Function Name:
 *      rtksw_trap_reasonTrapToCpuPriority_get
 * Description:
 *      Get priority value of a packet that trapped to CPU port according to specific reason.
 * Input:
 *      unit            - Unit ID
 *      type            - reason that trap to CPU port.
 * Output:
 *      pPriority - configured internal priority for such reason.
 * Return:
 *      RT_ERR_OK
 *      RT_ERR_FAILED
 *      RT_ERR_NOT_INIT     - The module is not initial
 *      RT_ERR_INPUT        - Invalid input parameter
 *      RT_ERR_NULL_POINTER - NULL pointer
 * Note:
 *      Currently the trap reason that supported are listed as follows:
 *      - TRAP_REASON_RMA
 *      - TRAP_REASON_OAM
 *      - TRAP_REASON_1XUNAUTH
 *      - TRAP_REASON_VLANSTACK
 *      - TRAP_REASON_UNKNOWNMC
 */
rtksw_api_ret_t dal_rtl8367c_trap_reasonTrapToCpuPriority_get(rtksw_uint32 unit, rtksw_trap_reason_type_t type, rtksw_pri_t *pPriority)
{
    rtksw_api_ret_t retVal;
    rtl8367c_rma_t rmacfg;

    /* Check initialization state */
    RTKSW_CHK_INIT_STATE(unit);

    if (type >= TRAP_REASON_END)
        return RT_ERR_INPUT;

    if(NULL == pPriority)
        return RT_ERR_NULL_POINTER;

    switch (type)
    {
        case TRAP_REASON_RMA:
            if ((retVal = rtl8367c_getAsicRma(unit, 0, &rmacfg)) != RT_ERR_OK)
                return retVal;
            *pPriority = rmacfg.trap_priority;

            break;
        case TRAP_REASON_OAM:
            if ((retVal = rtl8367c_getAsicOamCpuPri(unit, pPriority)) != RT_ERR_OK)
                return retVal;

            break;
        case TRAP_REASON_1XUNAUTH:
            if ((retVal = rtl8367c_getAsic1xTrapPriority(unit, pPriority)) != RT_ERR_OK)
                return retVal;

            break;
        case TRAP_REASON_VLANSTACK:
            if ((retVal = rtl8367c_getAsicSvlanTrapPriority(unit, pPriority)) != RT_ERR_OK)
                return retVal;

            break;
        case TRAP_REASON_UNKNOWNMC:
            if ((retVal = rtl8367c_getAsicUnknownMulticastTrapPriority(unit, pPriority)) != RT_ERR_OK)
                return retVal;

            break;
        default:
            return RT_ERR_CHIP_NOT_SUPPORTED;

    }

    return RT_ERR_OK;
}

/* Function Name:
 *      rtksw_trap_rmaAction_set
 * Description:
 *      Set Reserved multicast address action configuration.
 * Input:
 *      unit            - Unit ID
 *      type            - rma type.
 *      rma_action      - RMA action.
 * Output:
 *      None
 * Return:
 *      RT_ERR_OK           - OK
 *      RT_ERR_FAILED       - Failed
 *      RT_ERR_SMI          - SMI access error
 *      RT_ERR_INPUT        - Invalid input parameters.
 * Note:
 *
 *      There are 48 types of Reserved Multicast Address frame for application usage.
 *      (1)They are as following definition.
 *      - TRAP_BRG_GROUP,
 *      - TRAP_FD_PAUSE,
 *      - TRAP_SP_MCAST,
 *      - TRAP_1X_PAE,
 *      - TRAP_UNDEF_BRG_04,
 *      - TRAP_UNDEF_BRG_05,
 *      - TRAP_UNDEF_BRG_06,
 *      - TRAP_UNDEF_BRG_07,
 *      - TRAP_PROVIDER_BRIDGE_GROUP_ADDRESS,
 *      - TRAP_UNDEF_BRG_09,
 *      - TRAP_UNDEF_BRG_0A,
 *      - TRAP_UNDEF_BRG_0B,
 *      - TRAP_UNDEF_BRG_0C,
 *      - TRAP_PROVIDER_BRIDGE_GVRP_ADDRESS,
 *      - TRAP_8021AB,
 *      - TRAP_UNDEF_BRG_0F,
 *      - TRAP_BRG_MNGEMENT,
 *      - TRAP_UNDEFINED_11,
 *      - TRAP_UNDEFINED_12,
 *      - TRAP_UNDEFINED_13,
 *      - TRAP_UNDEFINED_14,
 *      - TRAP_UNDEFINED_15,
 *      - TRAP_UNDEFINED_16,
 *      - TRAP_UNDEFINED_17,
 *      - TRAP_UNDEFINED_18,
 *      - TRAP_UNDEFINED_19,
 *      - TRAP_UNDEFINED_1A,
 *      - TRAP_UNDEFINED_1B,
 *      - TRAP_UNDEFINED_1C,
 *      - TRAP_UNDEFINED_1D,
 *      - TRAP_UNDEFINED_1E,
 *      - TRAP_UNDEFINED_1F,
 *      - TRAP_GMRP,
 *      - TRAP_GVRP,
 *      - TRAP_UNDEF_GARP_22,
 *      - TRAP_UNDEF_GARP_23,
 *      - TRAP_UNDEF_GARP_24,
 *      - TRAP_UNDEF_GARP_25,
 *      - TRAP_UNDEF_GARP_26,
 *      - TRAP_UNDEF_GARP_27,
 *      - TRAP_UNDEF_GARP_28,
 *      - TRAP_UNDEF_GARP_29,
 *      - TRAP_UNDEF_GARP_2A,
 *      - TRAP_UNDEF_GARP_2B,
 *      - TRAP_UNDEF_GARP_2C,
 *      - TRAP_UNDEF_GARP_2D,
 *      - TRAP_UNDEF_GARP_2E,
 *      - TRAP_UNDEF_GARP_2F,
 *      - TRAP_CDP.
 *      - TRAP_CSSTP.
 *      - TRAP_LLDP.
 *      (2) The RMA action is as following:
 *      - RMA_ACTION_FORWARD
 *      - RMA_ACTION_TRAP2CPU
 *      - RMA_ACTION_DROP
 *      - RMA_ACTION_FORWARD_EXCLUDE_CPU
 */
rtksw_api_ret_t dal_rtl8367c_trap_rmaAction_set(rtksw_uint32 unit, rtksw_trap_type_t type, rtksw_trap_rma_action_t rma_action)
{
    rtksw_api_ret_t retVal;
    rtl8367c_rma_t rmacfg;
    rtksw_uint32 tmp;

    /* Check initialization state */
    RTKSW_CHK_INIT_STATE(unit);

    if (type >= TRAP_END)
        return RT_ERR_INPUT;

    if (rma_action >= RMA_ACTION_END)
        return RT_ERR_RMA_ACTION;

    if (type >= 0 && type <= TRAP_UNDEF_GARP_2F)
    {
        if ((retVal = rtl8367c_getAsicRma(unit, type, &rmacfg)) != RT_ERR_OK)
            return retVal;

        rmacfg.operation = rma_action;

        if ((retVal = rtl8367c_setAsicRma(unit, type, &rmacfg)) != RT_ERR_OK)
            return retVal;
    }
    else if (type == TRAP_CDP)
    {
        if ((retVal = rtl8367c_getAsicRmaCdp(unit, &rmacfg)) != RT_ERR_OK)
            return retVal;

        rmacfg.operation = rma_action;

        if ((retVal = rtl8367c_setAsicRmaCdp(unit, &rmacfg)) != RT_ERR_OK)
            return retVal;
    }
    else if (type  == TRAP_CSSTP)
    {
        if ((retVal = rtl8367c_getAsicRmaCsstp(unit, &rmacfg)) != RT_ERR_OK)
            return retVal;

        rmacfg.operation = rma_action;

        if ((retVal = rtl8367c_setAsicRmaCsstp(unit, &rmacfg)) != RT_ERR_OK)
            return retVal;
    }
    else if (type  == TRAP_LLDP)
    {
        if ((retVal = rtl8367c_getAsicRmaLldp(unit, &tmp, &rmacfg)) != RT_ERR_OK)
            return retVal;

        rmacfg.operation = rma_action;

        if ((retVal = rtl8367c_setAsicRmaLldp(unit, tmp, &rmacfg)) != RT_ERR_OK)
            return retVal;
    }
    else
        return RT_ERR_INPUT;

    return RT_ERR_OK;
}

/* Function Name:
 *      rtksw_trap_rmaAction_get
 * Description:
 *      Get Reserved multicast address action configuration.
 * Input:
 *      unit            - Unit ID
 *      type            - rma type.
 * Output:
 *      pRma_action - RMA action.
 * Return:
 *      RT_ERR_OK           - OK
 *      RT_ERR_FAILED       - Failed
 *      RT_ERR_SMI          - SMI access error
 *      RT_ERR_INPUT        - Invalid input parameters.
 * Note:
 *      There are 48 types of Reserved Multicast Address frame for application usage.
 *      (1)They are as following definition.
 *      - TRAP_BRG_GROUP,
 *      - TRAP_FD_PAUSE,
 *      - TRAP_SP_MCAST,
 *      - TRAP_1X_PAE,
 *      - TRAP_UNDEF_BRG_04,
 *      - TRAP_UNDEF_BRG_05,
 *      - TRAP_UNDEF_BRG_06,
 *      - TRAP_UNDEF_BRG_07,
 *      - TRAP_PROVIDER_BRIDGE_GROUP_ADDRESS,
 *      - TRAP_UNDEF_BRG_09,
 *      - TRAP_UNDEF_BRG_0A,
 *      - TRAP_UNDEF_BRG_0B,
 *      - TRAP_UNDEF_BRG_0C,
 *      - TRAP_PROVIDER_BRIDGE_GVRP_ADDRESS,
 *      - TRAP_8021AB,
 *      - TRAP_UNDEF_BRG_0F,
 *      - TRAP_BRG_MNGEMENT,
 *      - TRAP_UNDEFINED_11,
 *      - TRAP_UNDEFINED_12,
 *      - TRAP_UNDEFINED_13,
 *      - TRAP_UNDEFINED_14,
 *      - TRAP_UNDEFINED_15,
 *      - TRAP_UNDEFINED_16,
 *      - TRAP_UNDEFINED_17,
 *      - TRAP_UNDEFINED_18,
 *      - TRAP_UNDEFINED_19,
 *      - TRAP_UNDEFINED_1A,
 *      - TRAP_UNDEFINED_1B,
 *      - TRAP_UNDEFINED_1C,
 *      - TRAP_UNDEFINED_1D,
 *      - TRAP_UNDEFINED_1E,
 *      - TRAP_UNDEFINED_1F,
 *      - TRAP_GMRP,
 *      - TRAP_GVRP,
 *      - TRAP_UNDEF_GARP_22,
 *      - TRAP_UNDEF_GARP_23,
 *      - TRAP_UNDEF_GARP_24,
 *      - TRAP_UNDEF_GARP_25,
 *      - TRAP_UNDEF_GARP_26,
 *      - TRAP_UNDEF_GARP_27,
 *      - TRAP_UNDEF_GARP_28,
 *      - TRAP_UNDEF_GARP_29,
 *      - TRAP_UNDEF_GARP_2A,
 *      - TRAP_UNDEF_GARP_2B,
 *      - TRAP_UNDEF_GARP_2C,
 *      - TRAP_UNDEF_GARP_2D,
 *      - TRAP_UNDEF_GARP_2E,
 *      - TRAP_UNDEF_GARP_2F,
 *      - TRAP_CDP.
 *      - TRAP_CSSTP.
 *      - TRAP_LLDP.
 *      (2) The RMA action is as following:
 *      - RMA_ACTION_FORWARD
 *      - RMA_ACTION_TRAP2CPU
 *      - RMA_ACTION_DROP
 *      - RMA_ACTION_FORWARD_EXCLUDE_CPU
 */
rtksw_api_ret_t dal_rtl8367c_trap_rmaAction_get(rtksw_uint32 unit, rtksw_trap_type_t type, rtksw_trap_rma_action_t *pRma_action)
{
    rtksw_api_ret_t retVal;
    rtl8367c_rma_t rmacfg;
    rtksw_uint32 tmp;

    /* Check initialization state */
    RTKSW_CHK_INIT_STATE(unit);

    if (type >= TRAP_END)
        return RT_ERR_INPUT;

    if(NULL == pRma_action)
        return RT_ERR_NULL_POINTER;

    if (type >= 0 && type <= TRAP_UNDEF_GARP_2F)
    {
        if ((retVal = rtl8367c_getAsicRma(unit, type, &rmacfg)) != RT_ERR_OK)
            return retVal;

        *pRma_action = rmacfg.operation;
    }
    else if (type == TRAP_CDP)
    {
        if ((retVal = rtl8367c_getAsicRmaCdp(unit, &rmacfg)) != RT_ERR_OK)
            return retVal;

        *pRma_action = rmacfg.operation;
    }
    else if (type == TRAP_CSSTP)
    {
        if ((retVal = rtl8367c_getAsicRmaCsstp(unit, &rmacfg)) != RT_ERR_OK)
            return retVal;

        *pRma_action = rmacfg.operation;
    }
    else if (type == TRAP_LLDP)
    {
        if ((retVal = rtl8367c_getAsicRmaLldp(unit, &tmp,&rmacfg)) != RT_ERR_OK)
            return retVal;

        *pRma_action = rmacfg.operation;
    }
    else
        return RT_ERR_INPUT;

    return RT_ERR_OK;
}

/* Function Name:
 *      rtksw_trap_rmaKeepFormat_set
 * Description:
 *      Set Reserved multicast address keep format configuration.
 * Input:
 *      unit            - Unit ID
 *      type            - rma type.
 *      enable          - enable keep format.
 * Output:
 *      None
 * Return:
 *      RT_ERR_OK           - OK
 *      RT_ERR_FAILED       - Failed
 *      RT_ERR_SMI          - SMI access error
 *      RT_ERR_INPUT        - Invalid input parameters.
 *      RT_ERR_ENABLE       - Invalid IFG parameter
 * Note:
 *
 *      There are 48 types of Reserved Multicast Address frame for application usage.
 *      They are as following definition.
 *      - TRAP_BRG_GROUP,
 *      - TRAP_FD_PAUSE,
 *      - TRAP_SP_MCAST,
 *      - TRAP_1X_PAE,
 *      - TRAP_UNDEF_BRG_04,
 *      - TRAP_UNDEF_BRG_05,
 *      - TRAP_UNDEF_BRG_06,
 *      - TRAP_UNDEF_BRG_07,
 *      - TRAP_PROVIDER_BRIDGE_GROUP_ADDRESS,
 *      - TRAP_UNDEF_BRG_09,
 *      - TRAP_UNDEF_BRG_0A,
 *      - TRAP_UNDEF_BRG_0B,
 *      - TRAP_UNDEF_BRG_0C,
 *      - TRAP_PROVIDER_BRIDGE_GVRP_ADDRESS,
 *      - TRAP_8021AB,
 *      - TRAP_UNDEF_BRG_0F,
 *      - TRAP_BRG_MNGEMENT,
 *      - TRAP_UNDEFINED_11,
 *      - TRAP_UNDEFINED_12,
 *      - TRAP_UNDEFINED_13,
 *      - TRAP_UNDEFINED_14,
 *      - TRAP_UNDEFINED_15,
 *      - TRAP_UNDEFINED_16,
 *      - TRAP_UNDEFINED_17,
 *      - TRAP_UNDEFINED_18,
 *      - TRAP_UNDEFINED_19,
 *      - TRAP_UNDEFINED_1A,
 *      - TRAP_UNDEFINED_1B,
 *      - TRAP_UNDEFINED_1C,
 *      - TRAP_UNDEFINED_1D,
 *      - TRAP_UNDEFINED_1E,
 *      - TRAP_UNDEFINED_1F,
 *      - TRAP_GMRP,
 *      - TRAP_GVRP,
 *      - TRAP_UNDEF_GARP_22,
 *      - TRAP_UNDEF_GARP_23,
 *      - TRAP_UNDEF_GARP_24,
 *      - TRAP_UNDEF_GARP_25,
 *      - TRAP_UNDEF_GARP_26,
 *      - TRAP_UNDEF_GARP_27,
 *      - TRAP_UNDEF_GARP_28,
 *      - TRAP_UNDEF_GARP_29,
 *      - TRAP_UNDEF_GARP_2A,
 *      - TRAP_UNDEF_GARP_2B,
 *      - TRAP_UNDEF_GARP_2C,
 *      - TRAP_UNDEF_GARP_2D,
 *      - TRAP_UNDEF_GARP_2E,
 *      - TRAP_UNDEF_GARP_2F,
 *      - TRAP_CDP.
 *      - TRAP_CSSTP.
 *      - TRAP_LLDP.
 */
rtksw_api_ret_t dal_rtl8367c_trap_rmaKeepFormat_set(rtksw_uint32 unit, rtksw_trap_type_t type, rtksw_enable_t enable)
{
    rtksw_api_ret_t retVal;
    rtl8367c_rma_t rmacfg;
    rtksw_uint32 tmp;

    /* Check initialization state */
    RTKSW_CHK_INIT_STATE(unit);

    if (type >= TRAP_END)
        return RT_ERR_INPUT;

    if (enable >= RTKSW_ENABLE_END)
        return RT_ERR_INPUT;

    if (type >= 0 && type <= TRAP_UNDEF_GARP_2F)
    {
        if ((retVal = rtl8367c_getAsicRma(unit, type, &rmacfg)) != RT_ERR_OK)
            return retVal;

        rmacfg.keep_format = enable;

        if ((retVal = rtl8367c_setAsicRma(unit, type, &rmacfg)) != RT_ERR_OK)
            return retVal;
    }
    else if (type == TRAP_CDP)
    {
        if ((retVal = rtl8367c_getAsicRmaCdp(unit, &rmacfg)) != RT_ERR_OK)
            return retVal;

        rmacfg.keep_format = enable;

        if ((retVal = rtl8367c_setAsicRmaCdp(unit, &rmacfg)) != RT_ERR_OK)
            return retVal;
    }
    else if (type  == TRAP_CSSTP)
    {
        if ((retVal = rtl8367c_getAsicRmaCsstp(unit, &rmacfg)) != RT_ERR_OK)
            return retVal;

        rmacfg.keep_format = enable;

        if ((retVal = rtl8367c_setAsicRmaCsstp(unit, &rmacfg)) != RT_ERR_OK)
            return retVal;
    }
    else if (type  == TRAP_LLDP)
    {
        if ((retVal = rtl8367c_getAsicRmaLldp(unit, &tmp, &rmacfg)) != RT_ERR_OK)
            return retVal;

        rmacfg.keep_format = enable;

        if ((retVal = rtl8367c_setAsicRmaLldp(unit, tmp, &rmacfg)) != RT_ERR_OK)
            return retVal;
    }
    else
        return RT_ERR_INPUT;

    return RT_ERR_OK;
}

/* Function Name:
 *      rtksw_trap_rmaKeepFormat_get
 * Description:
 *      Get Reserved multicast address action configuration.
 * Input:
 *      unit            - Unit ID
 *      type            - rma type.
 * Output:
 *      pEnable - keep format status.
 * Return:
 *      RT_ERR_OK           - OK
 *      RT_ERR_FAILED       - Failed
 *      RT_ERR_SMI          - SMI access error
 *      RT_ERR_INPUT        - Invalid input parameters.
 * Note:
 *      There are 48 types of Reserved Multicast Address frame for application usage.
 *      They are as following definition.
 *      - TRAP_BRG_GROUP,
 *      - TRAP_FD_PAUSE,
 *      - TRAP_SP_MCAST,
 *      - TRAP_1X_PAE,
 *      - TRAP_UNDEF_BRG_04,
 *      - TRAP_UNDEF_BRG_05,
 *      - TRAP_UNDEF_BRG_06,
 *      - TRAP_UNDEF_BRG_07,
 *      - TRAP_PROVIDER_BRIDGE_GROUP_ADDRESS,
 *      - TRAP_UNDEF_BRG_09,
 *      - TRAP_UNDEF_BRG_0A,
 *      - TRAP_UNDEF_BRG_0B,
 *      - TRAP_UNDEF_BRG_0C,
 *      - TRAP_PROVIDER_BRIDGE_GVRP_ADDRESS,
 *      - TRAP_8021AB,
 *      - TRAP_UNDEF_BRG_0F,
 *      - TRAP_BRG_MNGEMENT,
 *      - TRAP_UNDEFINED_11,
 *      - TRAP_UNDEFINED_12,
 *      - TRAP_UNDEFINED_13,
 *      - TRAP_UNDEFINED_14,
 *      - TRAP_UNDEFINED_15,
 *      - TRAP_UNDEFINED_16,
 *      - TRAP_UNDEFINED_17,
 *      - TRAP_UNDEFINED_18,
 *      - TRAP_UNDEFINED_19,
 *      - TRAP_UNDEFINED_1A,
 *      - TRAP_UNDEFINED_1B,
 *      - TRAP_UNDEFINED_1C,
 *      - TRAP_UNDEFINED_1D,
 *      - TRAP_UNDEFINED_1E,
 *      - TRAP_UNDEFINED_1F,
 *      - TRAP_GMRP,
 *      - TRAP_GVRP,
 *      - TRAP_UNDEF_GARP_22,
 *      - TRAP_UNDEF_GARP_23,
 *      - TRAP_UNDEF_GARP_24,
 *      - TRAP_UNDEF_GARP_25,
 *      - TRAP_UNDEF_GARP_26,
 *      - TRAP_UNDEF_GARP_27,
 *      - TRAP_UNDEF_GARP_28,
 *      - TRAP_UNDEF_GARP_29,
 *      - TRAP_UNDEF_GARP_2A,
 *      - TRAP_UNDEF_GARP_2B,
 *      - TRAP_UNDEF_GARP_2C,
 *      - TRAP_UNDEF_GARP_2D,
 *      - TRAP_UNDEF_GARP_2E,
 *      - TRAP_UNDEF_GARP_2F,
 *      - TRAP_CDP.
 *      - TRAP_CSSTP.
 *      - TRAP_LLDP.
 */
rtksw_api_ret_t dal_rtl8367c_trap_rmaKeepFormat_get(rtksw_uint32 unit, rtksw_trap_type_t type, rtksw_enable_t *pEnable)
{
    rtksw_api_ret_t retVal;
    rtl8367c_rma_t rmacfg;
    rtksw_uint32 tmp;

    /* Check initialization state */
    RTKSW_CHK_INIT_STATE(unit);

    if (type >= TRAP_END)
        return RT_ERR_INPUT;

    if(NULL == pEnable)
        return RT_ERR_NULL_POINTER;

    if (type >= 0 && type <= TRAP_UNDEF_GARP_2F)
    {
        if ((retVal = rtl8367c_getAsicRma(unit, type, &rmacfg)) != RT_ERR_OK)
            return retVal;

        *pEnable = rmacfg.keep_format;
    }
    else if (type == TRAP_CDP)
    {
        if ((retVal = rtl8367c_getAsicRmaCdp(unit, &rmacfg)) != RT_ERR_OK)
            return retVal;

        *pEnable = rmacfg.keep_format;
    }
    else if (type == TRAP_CSSTP)
    {
        if ((retVal = rtl8367c_getAsicRmaCsstp(unit, &rmacfg)) != RT_ERR_OK)
            return retVal;

        *pEnable = rmacfg.keep_format;
    }
    else if (type == TRAP_LLDP)
    {
        if ((retVal = rtl8367c_getAsicRmaLldp(unit, &tmp,&rmacfg)) != RT_ERR_OK)
            return retVal;

        *pEnable = rmacfg.keep_format;
    }
    else
        return RT_ERR_INPUT;

    return RT_ERR_OK;
}



