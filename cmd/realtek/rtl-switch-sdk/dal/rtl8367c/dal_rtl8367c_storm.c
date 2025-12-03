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
 * Feature : Here is a list of all functions and variables in Storm module.
 *
 */

#include "../../rtk_switch.h"
#include "../../rtk_error.h"
#include "dal_rtl8367c_storm.h"
#include "rtl8367c_asicdrv.h"
#include "rtl8367c_asicdrv_storm.h"
#include "rtl8367c_asicdrv_meter.h"
#include "rtl8367c_asicdrv_rma.h"
#include "rtl8367c_asicdrv_igmp.h"

#include "../dal_mgmts.h"

/* Function Name:
 *      dal_rtl8367c_rate_stormControlMeterIdx_set
 * Description:
 *      Set the storm control meter index.
 * Input:
 *      unit        - Unit ID
 *      port        - port id
 *      storm_type  - storm group type
 *      index       - storm control meter index.
 * Output:
 *      None.
 * Return:
 *      RT_ERR_OK
 *      RT_ERR_FAILED
 *      RT_ERR_PORT_ID - Invalid port id
 *      RT_ERR_FILTER_METER_ID  - Invalid meter
 * Note:
 *
 */
rtksw_api_ret_t dal_rtl8367c_rate_stormControlMeterIdx_set(rtksw_uint32 unit, rtksw_port_t port, rtksw_rate_storm_group_t stormType, rtksw_uint32 index)
{
    rtksw_api_ret_t retVal;

    /* Check initialization state */
    RTKSW_CHK_INIT_STATE(unit);

    /* Check Port Valid */
    RTKSW_CHK_PORT_VALID(unit, port);

    if (stormType >= STORM_GROUP_END)
        return RT_ERR_SFC_UNKNOWN_GROUP;

    if (index > RTKSW_MAX_METER_ID)
        return RT_ERR_FILTER_METER_ID;

    switch (stormType)
    {
        case STORM_GROUP_UNKNOWN_UNICAST:
            if ((retVal = rtl8367c_setAsicStormFilterUnknownUnicastMeter(unit, rtksw_switch_port_L2P_get(unit, port), index))!=RT_ERR_OK)
                return retVal;
            break;
        case STORM_GROUP_UNKNOWN_MULTICAST:
            if ((retVal = rtl8367c_setAsicStormFilterUnknownMulticastMeter(unit, rtksw_switch_port_L2P_get(unit, port), index))!=RT_ERR_OK)
                return retVal;
            break;
        case STORM_GROUP_MULTICAST:
            if ((retVal = rtl8367c_setAsicStormFilterMulticastMeter(unit, rtksw_switch_port_L2P_get(unit, port), index))!=RT_ERR_OK)
                return retVal;
            break;
        case STORM_GROUP_BROADCAST:
            if ((retVal = rtl8367c_setAsicStormFilterBroadcastMeter(unit, rtksw_switch_port_L2P_get(unit, port), index))!=RT_ERR_OK)
                return retVal;
            break;
        default:
            break;
    }

    return RT_ERR_OK;
}

/* Function Name:
 *      dal_rtl8367c_rate_stormControlMeterIdx_get
 * Description:
 *      Get the storm control meter index.
 * Input:
 *      unit        - Unit ID
 *      port        - port id
 *      storm_type  - storm group type
 * Output:
 *      pIndex     - storm control meter index.
 * Return:
 *      RT_ERR_OK
 *      RT_ERR_FAILED
 *      RT_ERR_PORT_ID - Invalid port id
 *      RT_ERR_FILTER_METER_ID  - Invalid meter
 * Note:
 *
 */
rtksw_api_ret_t dal_rtl8367c_rate_stormControlMeterIdx_get(rtksw_uint32 unit, rtksw_port_t port, rtksw_rate_storm_group_t stormType, rtksw_uint32 *pIndex)
{
    rtksw_api_ret_t retVal;

    /* Check initialization state */
    RTKSW_CHK_INIT_STATE(unit);

    /* Check Port Valid */
    RTKSW_CHK_PORT_VALID(unit, port);

    if (stormType >= STORM_GROUP_END)
        return RT_ERR_SFC_UNKNOWN_GROUP;

    if (NULL == pIndex )
        return RT_ERR_NULL_POINTER;

    switch (stormType)
    {
        case STORM_GROUP_UNKNOWN_UNICAST:
            if ((retVal = rtl8367c_getAsicStormFilterUnknownUnicastMeter(unit, rtksw_switch_port_L2P_get(unit, port), pIndex))!=RT_ERR_OK)
                return retVal;
            break;
        case STORM_GROUP_UNKNOWN_MULTICAST:
            if ((retVal = rtl8367c_getAsicStormFilterUnknownMulticastMeter(unit, rtksw_switch_port_L2P_get(unit, port), pIndex))!=RT_ERR_OK)
                return retVal;
            break;
        case STORM_GROUP_MULTICAST:
            if ((retVal = rtl8367c_getAsicStormFilterMulticastMeter(unit, rtksw_switch_port_L2P_get(unit, port), pIndex))!=RT_ERR_OK)
                return retVal;
            break;
        case STORM_GROUP_BROADCAST:
            if ((retVal = rtl8367c_getAsicStormFilterBroadcastMeter(unit, rtksw_switch_port_L2P_get(unit, port), pIndex))!=RT_ERR_OK)
                return retVal;
            break;
        default:
            break;
    }

    return RT_ERR_OK;
}

/* Function Name:
 *      dal_rtl8367c_rate_stormControlPortEnable_set
 * Description:
 *      Set enable status of storm control on specified port.
 * Input:
 *      unit        - Unit ID
 *      port        - port id
 *      stormType   - storm group type
 *      enable      - enable status of storm control
 * Output:
 *      None
 * Return:
 *      RT_ERR_OK
 *      RT_ERR_FAILED
 *      RT_ERR_NOT_INIT          - The module is not initial
 *      RT_ERR_PORT_ID           - invalid port id
 *      RT_ERR_INPUT             - invalid input parameter
 * Note:
 *
 */
rtksw_api_ret_t dal_rtl8367c_rate_stormControlPortEnable_set(rtksw_uint32 unit, rtksw_port_t port, rtksw_rate_storm_group_t stormType, rtksw_enable_t enable)
{
    rtksw_api_ret_t retVal;

    /* Check initialization state */
    RTKSW_CHK_INIT_STATE(unit);

    /* Check Port Valid */
    RTKSW_CHK_PORT_VALID(unit, port);

    if (stormType >= STORM_GROUP_END)
        return RT_ERR_SFC_UNKNOWN_GROUP;

    if (enable >= RTKSW_ENABLE_END)
        return RT_ERR_ENABLE;

    switch (stormType)
    {
        case STORM_GROUP_UNKNOWN_UNICAST:
            if ((retVal = rtl8367c_setAsicStormFilterUnknownUnicastEnable(unit, rtksw_switch_port_L2P_get(unit, port), enable)) != RT_ERR_OK)
                return retVal;
            break;
        case STORM_GROUP_UNKNOWN_MULTICAST:
            if ((retVal = rtl8367c_setAsicStormFilterUnknownMulticastEnable(unit, rtksw_switch_port_L2P_get(unit, port), enable)) != RT_ERR_OK)
                return retVal;
            break;
        case STORM_GROUP_MULTICAST:
            if ((retVal = rtl8367c_setAsicStormFilterMulticastEnable(unit, rtksw_switch_port_L2P_get(unit, port), enable)) != RT_ERR_OK)
                return retVal;
            break;
        case STORM_GROUP_BROADCAST:
            if ((retVal = rtl8367c_setAsicStormFilterBroadcastEnable(unit, rtksw_switch_port_L2P_get(unit, port), enable)) != RT_ERR_OK)
                return retVal;
            break;
        default:
            break;
    }

    return RT_ERR_OK;
}

/* Function Name:
 *      dal_rtl8367c_rate_stormControlPortEnable_set
 * Description:
 *      Set enable status of storm control on specified port.
 * Input:
 *      unit        - Unit ID
 *      port        - port id
 *      stormType   - storm group type
 * Output:
 *      pEnable     - enable status of storm control
 * Return:
 *      RT_ERR_OK
 *      RT_ERR_FAILED
 *      RT_ERR_NOT_INIT          - The module is not initial
 *      RT_ERR_PORT_ID           - invalid port id
 *      RT_ERR_INPUT             - invalid input parameter
 * Note:
 *
 */
rtksw_api_ret_t dal_rtl8367c_rate_stormControlPortEnable_get(rtksw_uint32 unit, rtksw_port_t port, rtksw_rate_storm_group_t stormType, rtksw_enable_t *pEnable)
{
    rtksw_api_ret_t retVal;

    /* Check initialization state */
    RTKSW_CHK_INIT_STATE(unit);

    /* Check Port Valid */
    RTKSW_CHK_PORT_VALID(unit, port);

    if (stormType >= STORM_GROUP_END)
        return RT_ERR_SFC_UNKNOWN_GROUP;

    if (NULL == pEnable)
        return RT_ERR_ENABLE;

    switch (stormType)
    {
        case STORM_GROUP_UNKNOWN_UNICAST:
            if ((retVal = rtl8367c_getAsicStormFilterUnknownUnicastEnable(unit, rtksw_switch_port_L2P_get(unit, port), pEnable)) != RT_ERR_OK)
                return retVal;
            break;
        case STORM_GROUP_UNKNOWN_MULTICAST:
            if ((retVal = rtl8367c_getAsicStormFilterUnknownMulticastEnable(unit, rtksw_switch_port_L2P_get(unit, port), pEnable)) != RT_ERR_OK)
                return retVal;
            break;
        case STORM_GROUP_MULTICAST:
            if ((retVal = rtl8367c_getAsicStormFilterMulticastEnable(unit, rtksw_switch_port_L2P_get(unit, port), pEnable)) != RT_ERR_OK)
                return retVal;
            break;
        case STORM_GROUP_BROADCAST:
            if ((retVal = rtl8367c_getAsicStormFilterBroadcastEnable(unit, rtksw_switch_port_L2P_get(unit, port), pEnable)) != RT_ERR_OK)
                return retVal;
            break;
        default:
            break;
    }

    return RT_ERR_OK;
}

/* Function Name:
 *      dal_rtl8367c_storm_bypass_set
 * Description:
 *      Set bypass storm filter control configuration.
 * Input:
 *      unit        - Unit ID
 *      type        - Bypass storm filter control type.
 *      enable      - Bypass status.
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
 *      This API can set per-port bypass stomr filter control frame type including RMA and igmp.
 *      The bypass frame type is as following:
 *      - BYPASS_BRG_GROUP,
 *      - BYPASS_FD_PAUSE,
 *      - BYPASS_SP_MCAST,
 *      - BYPASS_1X_PAE,
 *      - BYPASS_UNDEF_BRG_04,
 *      - BYPASS_UNDEF_BRG_05,
 *      - BYPASS_UNDEF_BRG_06,
 *      - BYPASS_UNDEF_BRG_07,
 *      - BYPASS_PROVIDER_BRIDGE_GROUP_ADDRESS,
 *      - BYPASS_UNDEF_BRG_09,
 *      - BYPASS_UNDEF_BRG_0A,
 *      - BYPASS_UNDEF_BRG_0B,
 *      - BYPASS_UNDEF_BRG_0C,
 *      - BYPASS_PROVIDER_BRIDGE_GVRP_ADDRESS,
 *      - BYPASS_8021AB,
 *      - BYPASS_UNDEF_BRG_0F,
 *      - BYPASS_BRG_MNGEMENT,
 *      - BYPASS_UNDEFINED_11,
 *      - BYPASS_UNDEFINED_12,
 *      - BYPASS_UNDEFINED_13,
 *      - BYPASS_UNDEFINED_14,
 *      - BYPASS_UNDEFINED_15,
 *      - BYPASS_UNDEFINED_16,
 *      - BYPASS_UNDEFINED_17,
 *      - BYPASS_UNDEFINED_18,
 *      - BYPASS_UNDEFINED_19,
 *      - BYPASS_UNDEFINED_1A,
 *      - BYPASS_UNDEFINED_1B,
 *      - BYPASS_UNDEFINED_1C,
 *      - BYPASS_UNDEFINED_1D,
 *      - BYPASS_UNDEFINED_1E,
 *      - BYPASS_UNDEFINED_1F,
 *      - BYPASS_GMRP,
 *      - BYPASS_GVRP,
 *      - BYPASS_UNDEF_GARP_22,
 *      - BYPASS_UNDEF_GARP_23,
 *      - BYPASS_UNDEF_GARP_24,
 *      - BYPASS_UNDEF_GARP_25,
 *      - BYPASS_UNDEF_GARP_26,
 *      - BYPASS_UNDEF_GARP_27,
 *      - BYPASS_UNDEF_GARP_28,
 *      - BYPASS_UNDEF_GARP_29,
 *      - BYPASS_UNDEF_GARP_2A,
 *      - BYPASS_UNDEF_GARP_2B,
 *      - BYPASS_UNDEF_GARP_2C,
 *      - BYPASS_UNDEF_GARP_2D,
 *      - BYPASS_UNDEF_GARP_2E,
 *      - BYPASS_UNDEF_GARP_2F,
 *      - BYPASS_IGMP.
 *      - BYPASS_CDP.
 *      - BYPASS_CSSTP.
 *      - BYPASS_LLDP.
 */
rtksw_api_ret_t dal_rtl8367c_storm_bypass_set(rtksw_uint32 unit, rtksw_storm_bypass_t type, rtksw_enable_t enable)
{
    rtksw_api_ret_t retVal;
    rtl8367c_rma_t rmacfg;
    rtksw_uint32 tmp;

    /* Check initialization state */
    RTKSW_CHK_INIT_STATE(unit);

    if (type >= BYPASS_END)
        return RT_ERR_INPUT;

    if (enable >= RTKSW_ENABLE_END)
        return RT_ERR_INPUT;

    if (type >= 0 && type <= BYPASS_UNDEF_GARP_2F)
    {
        if ((retVal = rtl8367c_getAsicRma(unit, type, &rmacfg)) != RT_ERR_OK)
            return retVal;

        rmacfg.discard_storm_filter = enable;

        if ((retVal = rtl8367c_setAsicRma(unit, type, &rmacfg)) != RT_ERR_OK)
            return retVal;
    }
    else if(type == BYPASS_IGMP)
    {
        if ((retVal = rtl8367c_setAsicIGMPBypassStormCTRL(unit, enable)) != RT_ERR_OK)
            return retVal;
    }
    else if (type == BYPASS_CDP)
    {
        if ((retVal = rtl8367c_getAsicRmaCdp(unit, &rmacfg)) != RT_ERR_OK)
            return retVal;

        rmacfg.discard_storm_filter = enable;

        if ((retVal = rtl8367c_setAsicRmaCdp(unit, &rmacfg)) != RT_ERR_OK)
            return retVal;
    }
    else if (type  == BYPASS_CSSTP)
    {
        if ((retVal = rtl8367c_getAsicRmaCsstp(unit, &rmacfg)) != RT_ERR_OK)
            return retVal;

        rmacfg.discard_storm_filter = enable;

        if ((retVal = rtl8367c_setAsicRmaCsstp(unit, &rmacfg)) != RT_ERR_OK)
            return retVal;
    }
    else if (type  == BYPASS_LLDP)
    {
        if ((retVal = rtl8367c_getAsicRmaLldp(unit, &tmp, &rmacfg)) != RT_ERR_OK)
            return retVal;

        rmacfg.discard_storm_filter = enable;

        if ((retVal = rtl8367c_setAsicRmaLldp(unit, tmp, &rmacfg)) != RT_ERR_OK)
            return retVal;
    }
    else
        return RT_ERR_INPUT;

    return RT_ERR_OK;
}

/* Function Name:
 *      dal_rtl8367c_storm_bypass_get
 * Description:
 *      Get bypass storm filter control configuration.
 * Input:
 *      unit    - Unit ID
 *      type    - Bypass storm filter control type.
 * Output:
 *      pEnable - Bypass status.
 * Return:
 *      RT_ERR_OK           - OK
 *      RT_ERR_FAILED       - Failed
 *      RT_ERR_SMI          - SMI access error
 *      RT_ERR_INPUT        - Invalid input parameters.
 * Note:
 *      This API can get per-port bypass stomr filter control frame type including RMA and igmp.
 *      The bypass frame type is as following:
 *      - BYPASS_BRG_GROUP,
 *      - BYPASS_FD_PAUSE,
 *      - BYPASS_SP_MCAST,
 *      - BYPASS_1X_PAE,
 *      - BYPASS_UNDEF_BRG_04,
 *      - BYPASS_UNDEF_BRG_05,
 *      - BYPASS_UNDEF_BRG_06,
 *      - BYPASS_UNDEF_BRG_07,
 *      - BYPASS_PROVIDER_BRIDGE_GROUP_ADDRESS,
 *      - BYPASS_UNDEF_BRG_09,
 *      - BYPASS_UNDEF_BRG_0A,
 *      - BYPASS_UNDEF_BRG_0B,
 *      - BYPASS_UNDEF_BRG_0C,
 *      - BYPASS_PROVIDER_BRIDGE_GVRP_ADDRESS,
 *      - BYPASS_8021AB,
 *      - BYPASS_UNDEF_BRG_0F,
 *      - BYPASS_BRG_MNGEMENT,
 *      - BYPASS_UNDEFINED_11,
 *      - BYPASS_UNDEFINED_12,
 *      - BYPASS_UNDEFINED_13,
 *      - BYPASS_UNDEFINED_14,
 *      - BYPASS_UNDEFINED_15,
 *      - BYPASS_UNDEFINED_16,
 *      - BYPASS_UNDEFINED_17,
 *      - BYPASS_UNDEFINED_18,
 *      - BYPASS_UNDEFINED_19,
 *      - BYPASS_UNDEFINED_1A,
 *      - BYPASS_UNDEFINED_1B,
 *      - BYPASS_UNDEFINED_1C,
 *      - BYPASS_UNDEFINED_1D,
 *      - BYPASS_UNDEFINED_1E,
 *      - BYPASS_UNDEFINED_1F,
 *      - BYPASS_GMRP,
 *      - BYPASS_GVRP,
 *      - BYPASS_UNDEF_GARP_22,
 *      - BYPASS_UNDEF_GARP_23,
 *      - BYPASS_UNDEF_GARP_24,
 *      - BYPASS_UNDEF_GARP_25,
 *      - BYPASS_UNDEF_GARP_26,
 *      - BYPASS_UNDEF_GARP_27,
 *      - BYPASS_UNDEF_GARP_28,
 *      - BYPASS_UNDEF_GARP_29,
 *      - BYPASS_UNDEF_GARP_2A,
 *      - BYPASS_UNDEF_GARP_2B,
 *      - BYPASS_UNDEF_GARP_2C,
 *      - BYPASS_UNDEF_GARP_2D,
 *      - BYPASS_UNDEF_GARP_2E,
 *      - BYPASS_UNDEF_GARP_2F,
 *      - BYPASS_IGMP.
 *      - BYPASS_CDP.
 *      - BYPASS_CSSTP.
 *      - BYPASS_LLDP.
 */
rtksw_api_ret_t dal_rtl8367c_storm_bypass_get(rtksw_uint32 unit, rtksw_storm_bypass_t type, rtksw_enable_t *pEnable)
{
    rtksw_api_ret_t retVal;
    rtl8367c_rma_t rmacfg;
    rtksw_uint32 tmp;

    /* Check initialization state */
    RTKSW_CHK_INIT_STATE(unit);

    if (type >= BYPASS_END)
        return RT_ERR_INPUT;

    if(NULL == pEnable)
        return RT_ERR_NULL_POINTER;

    if (type >= 0 && type <= BYPASS_UNDEF_GARP_2F)
    {
        if ((retVal = rtl8367c_getAsicRma(unit, type, &rmacfg)) != RT_ERR_OK)
            return retVal;

        *pEnable = rmacfg.discard_storm_filter;
    }
    else if(type == BYPASS_IGMP)
    {
        if ((retVal = rtl8367c_getAsicIGMPBypassStormCTRL(unit, pEnable)) != RT_ERR_OK)
            return retVal;
    }
    else if (type == BYPASS_CDP)
    {
        if ((retVal = rtl8367c_getAsicRmaCdp(unit, &rmacfg)) != RT_ERR_OK)
            return retVal;

        *pEnable = rmacfg.discard_storm_filter;
    }
    else if (type == BYPASS_CSSTP)
    {
        if ((retVal = rtl8367c_getAsicRmaCsstp(unit, &rmacfg)) != RT_ERR_OK)
            return retVal;

        *pEnable = rmacfg.discard_storm_filter;
    }
    else if (type == BYPASS_LLDP)
    {
        if ((retVal = rtl8367c_getAsicRmaLldp(unit, &tmp,&rmacfg)) != RT_ERR_OK)
            return retVal;

        *pEnable = rmacfg.discard_storm_filter;
    }
    else
        return RT_ERR_INPUT;

    return RT_ERR_OK;
}

/* Function Name:
 *      dal_rtl8367c_rate_stormControlExtPortmask_set
 * Description:
 *      Set externsion storm control port mask
 * Input:
 *      unit        - Unit ID
 *      pPortmask   - port mask
 * Output:
 *      None
 * Return:
 *      RT_ERR_OK
 *      RT_ERR_FAILED
 *      RT_ERR_NOT_INIT          - The module is not initial
 *      RT_ERR_INPUT             - invalid input parameter
 * Note:
 *
 */
rtksw_api_ret_t dal_rtl8367c_rate_stormControlExtPortmask_set(rtksw_uint32 unit, rtksw_portmask_t *pPortmask)
{
    rtksw_api_ret_t retVal;
    rtksw_uint32 pmask;

    /* Check initialization state */
    RTKSW_CHK_INIT_STATE(unit);

    if(NULL == pPortmask)
        return RT_ERR_NULL_POINTER;

    if ((retVal = rtksw_switch_portmask_L2P_get(unit, pPortmask, &pmask)) != RT_ERR_OK)
        return retVal;

    if ((retVal = rtl8367c_setAsicStormFilterExtEnablePortMask(unit, pmask)) != RT_ERR_OK)
        return retVal;

    return RT_ERR_OK;
}

/* Function Name:
 *      dal_rtl8367c_rate_stormControlExtPortmask_get
 * Description:
 *      Set externsion storm control port mask
 * Input:
 *      unit        - Unit ID
 * Output:
 *      pPortmask  - port mask
 * Return:
 *      RT_ERR_OK
 *      RT_ERR_FAILED
 *      RT_ERR_NOT_INIT          - The module is not initial
 *      RT_ERR_INPUT             - invalid input parameter
 * Note:
 *
 */
rtksw_api_ret_t dal_rtl8367c_rate_stormControlExtPortmask_get(rtksw_uint32 unit, rtksw_portmask_t *pPortmask)
{
    rtksw_api_ret_t retVal;
    rtksw_uint32 pmask;

    /* Check initialization state */
    RTKSW_CHK_INIT_STATE(unit);

    if(NULL == pPortmask)
        return RT_ERR_NULL_POINTER;

    if ((retVal = rtl8367c_getAsicStormFilterExtEnablePortMask(unit, &pmask)) != RT_ERR_OK)
        return retVal;

    if ((retVal = rtksw_switch_portmask_P2L_get(unit, pmask, pPortmask)) != RT_ERR_OK)
        return retVal;

    return RT_ERR_OK;
}

/* Function Name:
 *      dal_rtl8367c_rate_stormControlExtEnable_set
 * Description:
 *      Set externsion storm control state
 * Input:
 *      unit        - Unit ID
 *      stormType   - storm group type
 *      enable      - externsion storm control state
 * Output:
 *      None
 * Return:
 *      RT_ERR_OK
 *      RT_ERR_FAILED
 *      RT_ERR_NOT_INIT          - The module is not initial
 *      RT_ERR_INPUT             - invalid input parameter
 * Note:
 *
 */
rtksw_api_ret_t dal_rtl8367c_rate_stormControlExtEnable_set(rtksw_uint32 unit, rtksw_rate_storm_group_t stormType, rtksw_enable_t enable)
{
    rtksw_api_ret_t retVal;

    /* Check initialization state */
    RTKSW_CHK_INIT_STATE(unit);

    if (stormType >= STORM_GROUP_END)
        return RT_ERR_SFC_UNKNOWN_GROUP;

    if (enable >= RTKSW_ENABLE_END)
        return RT_ERR_ENABLE;

    switch (stormType)
    {
        case STORM_GROUP_UNKNOWN_UNICAST:
            if ((retVal = rtl8367c_setAsicStormFilterExtUnknownUnicastEnable(unit, enable)) != RT_ERR_OK)
                return retVal;
            break;
        case STORM_GROUP_UNKNOWN_MULTICAST:
            if ((retVal = rtl8367c_setAsicStormFilterExtUnknownMulticastEnable(unit, enable)) != RT_ERR_OK)
                return retVal;
            break;
        case STORM_GROUP_MULTICAST:
            if ((retVal = rtl8367c_setAsicStormFilterExtMulticastEnable(unit, enable)) != RT_ERR_OK)
                return retVal;
            break;
        case STORM_GROUP_BROADCAST:
            if ((retVal = rtl8367c_setAsicStormFilterExtBroadcastEnable(unit, enable)) != RT_ERR_OK)
                return retVal;
            break;
        default:
            break;
    }

    return RT_ERR_OK;
}

/* Function Name:
 *      dal_rtl8367c_rate_stormControlExtEnable_get
 * Description:
 *      Get externsion storm control state
 * Input:
 *      unit        - Unit ID
 *      stormType   - storm group type
 * Output:
 *      pEnable     - externsion storm control state
 * Return:
 *      RT_ERR_OK
 *      RT_ERR_FAILED
 *      RT_ERR_NOT_INIT          - The module is not initial
 *      RT_ERR_INPUT             - invalid input parameter
 * Note:
 *
 */
rtksw_api_ret_t dal_rtl8367c_rate_stormControlExtEnable_get(rtksw_uint32 unit, rtksw_rate_storm_group_t stormType, rtksw_enable_t *pEnable)
{
    rtksw_api_ret_t retVal;

    /* Check initialization state */
    RTKSW_CHK_INIT_STATE(unit);

    if (stormType >= STORM_GROUP_END)
        return RT_ERR_SFC_UNKNOWN_GROUP;

    if (NULL == pEnable)
        return RT_ERR_NULL_POINTER;

    switch (stormType)
    {
        case STORM_GROUP_UNKNOWN_UNICAST:
            if ((retVal = rtl8367c_getAsicStormFilterExtUnknownUnicastEnable(unit, (rtksw_uint32 *)pEnable)) != RT_ERR_OK)
                return retVal;
            break;
        case STORM_GROUP_UNKNOWN_MULTICAST:
            if ((retVal = rtl8367c_getAsicStormFilterExtUnknownMulticastEnable(unit, (rtksw_uint32 *)pEnable)) != RT_ERR_OK)
                return retVal;
            break;
        case STORM_GROUP_MULTICAST:
            if ((retVal = rtl8367c_getAsicStormFilterExtMulticastEnable(unit, (rtksw_uint32 *)pEnable)) != RT_ERR_OK)
                return retVal;
            break;
        case STORM_GROUP_BROADCAST:
            if ((retVal = rtl8367c_getAsicStormFilterExtBroadcastEnable(unit, (rtksw_uint32 *)pEnable)) != RT_ERR_OK)
                return retVal;
            break;
        default:
            break;
    }

    return RT_ERR_OK;
}

/* Function Name:
 *      dal_rtl8367c_rate_stormControlExtMeterIdx_set
 * Description:
 *      Set externsion storm control meter index
 * Input:
 *      unit        - Unit ID
 *      stormType   - storm group type
 *      index       - externsion storm control state
 * Output:
 *      None
 * Return:
 *      RT_ERR_OK
 *      RT_ERR_FAILED
 *      RT_ERR_NOT_INIT          - The module is not initial
 *      RT_ERR_INPUT             - invalid input parameter
 * Note:
 *
 */
rtksw_api_ret_t dal_rtl8367c_rate_stormControlExtMeterIdx_set(rtksw_uint32 unit, rtksw_rate_storm_group_t stormType, rtksw_uint32 index)
{
    rtksw_api_ret_t retVal;

    /* Check initialization state */
    RTKSW_CHK_INIT_STATE(unit);

    if (stormType >= STORM_GROUP_END)
        return RT_ERR_SFC_UNKNOWN_GROUP;

    if (index > RTKSW_MAX_METER_ID)
        return RT_ERR_FILTER_METER_ID;

    switch (stormType)
    {
        case STORM_GROUP_UNKNOWN_UNICAST:
            if ((retVal = rtl8367c_setAsicStormFilterExtUnknownUnicastMeter(unit, index))!=RT_ERR_OK)
                return retVal;
            break;
        case STORM_GROUP_UNKNOWN_MULTICAST:
            if ((retVal = rtl8367c_setAsicStormFilterExtUnknownMulticastMeter(unit, index))!=RT_ERR_OK)
                return retVal;
            break;
        case STORM_GROUP_MULTICAST:
            if ((retVal = rtl8367c_setAsicStormFilterExtMulticastMeter(unit, index))!=RT_ERR_OK)
                return retVal;
            break;
        case STORM_GROUP_BROADCAST:
            if ((retVal = rtl8367c_setAsicStormFilterExtBroadcastMeter(unit, index))!=RT_ERR_OK)
                return retVal;
            break;
        default:
            break;
    }

    return RT_ERR_OK;
}

/* Function Name:
 *      dal_rtl8367c_rate_stormControlExtMeterIdx_get
 * Description:
 *      Get externsion storm control meter index
 * Input:
 *      unit        - Unit ID
 *      stormType   - storm group type
 *      pIndex      - externsion storm control state
 * Output:
 *      None
 * Return:
 *      RT_ERR_OK
 *      RT_ERR_FAILED
 *      RT_ERR_NOT_INIT          - The module is not initial
 *      RT_ERR_INPUT             - invalid input parameter
 * Note:
 *
 */
rtksw_api_ret_t dal_rtl8367c_rate_stormControlExtMeterIdx_get(rtksw_uint32 unit, rtksw_rate_storm_group_t stormType, rtksw_uint32 *pIndex)
{
    rtksw_api_ret_t retVal;

    /* Check initialization state */
    RTKSW_CHK_INIT_STATE(unit);

    if (stormType >= STORM_GROUP_END)
        return RT_ERR_SFC_UNKNOWN_GROUP;

    if(NULL == pIndex)
        return RT_ERR_NULL_POINTER;

    switch (stormType)
    {
        case STORM_GROUP_UNKNOWN_UNICAST:
            if ((retVal = rtl8367c_getAsicStormFilterExtUnknownUnicastMeter(unit, pIndex))!=RT_ERR_OK)
                return retVal;
            break;
        case STORM_GROUP_UNKNOWN_MULTICAST:
            if ((retVal = rtl8367c_getAsicStormFilterExtUnknownMulticastMeter(unit, pIndex))!=RT_ERR_OK)
                return retVal;
            break;
        case STORM_GROUP_MULTICAST:
            if ((retVal = rtl8367c_getAsicStormFilterExtMulticastMeter(unit, pIndex))!=RT_ERR_OK)
                return retVal;
            break;
        case STORM_GROUP_BROADCAST:
            if ((retVal = rtl8367c_getAsicStormFilterExtBroadcastMeter(unit, pIndex))!=RT_ERR_OK)
                return retVal;
            break;
        default:
            break;
    }

    return RT_ERR_OK;
}

