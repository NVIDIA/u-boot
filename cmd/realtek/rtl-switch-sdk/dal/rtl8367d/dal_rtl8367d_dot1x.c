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
 * Feature : Here is a list of all functions and variables in 1X module.
 *
 */

#include "../../rtk_switch.h"
#include "../../rtk_error.h"
#include "dal_rtl8367d_dot1x.h"
#include "dal_rtl8367d_vlan.h"
#include "rtl8367d_asicdrv.h"
#include "../../trap.h"

#include "../dal_mgmts.h"

/* Function Name:
 *      dal_rtl8367d_dot1x_unauthPacketOper_set
 * Description:
 *      Set 802.1x unauth action configuration.
 * Input:
 *      unit            - Unit ID
 *      port            - Port id.
 *      unauth_action   - 802.1X unauth action.
 * Output:
 *      None
 * Return:
 *      RT_ERR_OK           - OK
 *      RT_ERR_FAILED       - Failed
 *      RT_ERR_SMI          - SMI access error
 *      RT_ERR_PORT_ID      - Invalid port number.
 *      RT_ERR_INPUT        - Invalid input parameter.
 * Note:
 *      This API can set 802.1x unauth action configuration.
 *      The unauth action is as following:
 *      - DOT1X_ACTION_DROP
 *      - DOT1X_ACTION_TRAP2CPU
 *      - DOT1X_ACTION_GUESTVLAN
 */
rtksw_api_ret_t dal_rtl8367d_dot1x_unauthPacketOper_set(rtksw_uint32 unit, rtksw_port_t port, rtksw_dot1x_unauth_action_t unauth_action)
{
    rtksw_api_ret_t retVal;
    rtksw_uint32 phyPort;

    /* Check initialization state */
    RTKSW_CHK_INIT_STATE(unit);

    /* Check port Valid */
    RTKSW_CHK_PORT_VALID(unit, port);

    if (unauth_action >= DOT1X_ACTION_GUESTVLAN)
        return RT_ERR_DOT1X_PROC;

    phyPort = rtksw_switch_port_L2P_get(unit, port);
    if (phyPort == UNDEFINE_PHY_PORT)
        return RT_ERR_PORT_ID;

    if ((retVal = rtl8367d_setAsicRegBits(unit, RTL8367D_REG_DOT1X_UNAUTH_ACT_W0, RTL8367D_DOT1X_PORT0_UNAUTHBH_MASK << phyPort, unauth_action)) != RT_ERR_OK)
        return retVal;

    return RT_ERR_OK;
}

/* Function Name:
 *      dal_rtl8367d_dot1x_unauthPacketOper_get
 * Description:
 *      Get 802.1x unauth action configuration.
 * Input:
 *      unit    - Unit ID
 *      port    - Port id.
 * Output:
 *      pUnauth_action - 802.1X unauth action.
 * Return:
 *      RT_ERR_OK           - OK
 *      RT_ERR_FAILED       - Failed
 *      RT_ERR_SMI          - SMI access error
 *      RT_ERR_INPUT        - Invalid input parameters.
 *      RT_ERR_PORT_ID      - Invalid port number.
 * Note:
 *      This API can get 802.1x unauth action configuration.
 *      The unauth action is as following:
 *      - DOT1X_ACTION_DROP
 *      - DOT1X_ACTION_TRAP2CPU
 *      - DOT1X_ACTION_GUESTVLAN
 */
rtksw_api_ret_t dal_rtl8367d_dot1x_unauthPacketOper_get(rtksw_uint32 unit, rtksw_port_t port, rtksw_dot1x_unauth_action_t *pUnauth_action)
{
    rtksw_api_ret_t retVal;
    rtksw_uint32 phyPort;

    /* Check initialization state */
    RTKSW_CHK_INIT_STATE(unit);

    /* Check port Valid */
    RTKSW_CHK_PORT_VALID(unit, port);

    if(NULL == pUnauth_action)
        return RT_ERR_NULL_POINTER;

    phyPort = rtksw_switch_port_L2P_get(unit, port);
    if (phyPort == UNDEFINE_PHY_PORT)
        return RT_ERR_PORT_ID;

    if ((retVal = rtl8367d_getAsicRegBits(unit, RTL8367D_REG_DOT1X_UNAUTH_ACT_W0, RTL8367D_DOT1X_PORT0_UNAUTHBH_MASK << phyPort, pUnauth_action)) != RT_ERR_OK)
        return retVal;


    return RT_ERR_OK;
}

/* Function Name:
 *      dal_rtl8367d_dot1x_eapolFrame2CpuEnable_set
 * Description:
 *      Set 802.1x EAPOL packet trap to CPU configuration
 * Input:
 *      unit    - Unit ID
 *      enable  - The status of 802.1x EAPOL packet.
 * Output:
 *      None
 * Return:
 *      RT_ERR_OK           - OK
 *      RT_ERR_FAILED       - Failed
 *      RT_ERR_SMI          - SMI access error
 *      RT_ERR_ENABLE       - Invalid enable input.
 * Note:
 *      To support 802.1x authentication functionality, EAPOL frame (ether type = 0x888E) has to
 *      be trapped to CPU.
 *      The status of EAPOL frame trap to CPU is as following:
 *      - RTKSW_DISABLED
 *      - RTKSW_ENABLED
 */
rtksw_api_ret_t dal_rtl8367d_dot1x_eapolFrame2CpuEnable_set(rtksw_uint32 unit, rtksw_enable_t enable)
{
    rtksw_api_ret_t retVal;
    rtksw_uint32 action;

    /* Check initialization state */
    RTKSW_CHK_INIT_STATE(unit);

    if (enable >= RTKSW_ENABLE_END)
        return RT_ERR_ENABLE;

    if ((retVal = rtl8367d_getAsicRegBits(unit, RTL8367D_REG_RMA_CTRL03,RTL8367D_RMA_CTRL03_OPERATION_MASK, &action)) != RT_ERR_OK)
        return retVal;

    if (RTKSW_ENABLED == enable)
        action = RMA_ACTION_TRAP2CPU;
    else if (RTKSW_DISABLED == enable)
    {
        if (RMA_ACTION_TRAP2CPU == action)
        action = RMA_ACTION_FORWARD;
    }

    if ((retVal = rtl8367d_setAsicRegBits(unit, RTL8367D_REG_RMA_CTRL03,RTL8367D_RMA_CTRL03_OPERATION_MASK, action)) != RT_ERR_OK)
        return retVal;

    return RT_ERR_OK;
}

/* Function Name:
 *      dal_rtl8367d_dot1x_eapolFrame2CpuEnable_get
 * Description:
 *      Get 802.1x EAPOL packet trap to CPU configuration
 * Input:
 *      unit    - Unit ID
 * Output:
 *      pEnable - The status of 802.1x EAPOL packet.
 * Return:
 *      RT_ERR_OK           - OK
 *      RT_ERR_FAILED       - Failed
 *      RT_ERR_SMI          - SMI access error
 *      RT_ERR_INPUT        - Invalid input parameters.
 * Note:
 *      To support 802.1x authentication functionality, EAPOL frame (ether type = 0x888E) has to
 *      be trapped to CPU.
 *      The status of EAPOL frame trap to CPU is as following:
 *      - RTKSW_DISABLED
 *      - RTKSW_ENABLED
 */
rtksw_api_ret_t dal_rtl8367d_dot1x_eapolFrame2CpuEnable_get(rtksw_uint32 unit, rtksw_enable_t *pEnable)
{
    rtksw_api_ret_t retVal;
    rtksw_uint32 action;

    /* Check initialization state */
    RTKSW_CHK_INIT_STATE(unit);

    if(NULL == pEnable)
        return RT_ERR_NULL_POINTER;

    if ((retVal = rtl8367d_getAsicRegBits(unit, RTL8367D_REG_RMA_CTRL03,RTL8367D_RMA_CTRL03_OPERATION_MASK, &action)) != RT_ERR_OK)
        return retVal;

    if (RMA_ACTION_TRAP2CPU == action)
        *pEnable = RTKSW_ENABLED;
    else
        *pEnable = RTKSW_DISABLED;

    return RT_ERR_OK;
}

/* Function Name:
 *      dal_rtl8367d_dot1x_portBasedEnable_set
 * Description:
 *      Set 802.1x port-based enable configuration
 * Input:
 *      unit    - Unit ID
 *      port    - Port id.
 *      enable  - The status of 802.1x port.
 * Output:
 *      None
 * Return:
 *      RT_ERR_OK                   - OK
 *      RT_ERR_FAILED               - Failed
 *      RT_ERR_SMI                  - SMI access error
 *      RT_ERR_PORT_ID              - Invalid port number.
 *      RT_ERR_ENABLE               - Invalid enable input.
 *      RT_ERR_DOT1X_PORTBASEDPNEN  - 802.1X port-based enable error
 * Note:
 *      The API can update the port-based port enable register content. If a port is 802.1x
 *      port based network access control "enabled", it should be authenticated so packets
 *      from that port won't be dropped or trapped to CPU.
 *      The status of 802.1x port-based network access control is as following:
 *      - RTKSW_DISABLED
 *      - RTKSW_ENABLED
 */
rtksw_api_ret_t dal_rtl8367d_dot1x_portBasedEnable_set(rtksw_uint32 unit, rtksw_port_t port, rtksw_enable_t enable)
{
    rtksw_api_ret_t retVal;

    /* Check initialization state */
    RTKSW_CHK_INIT_STATE(unit);

    /* Check port Valid */
    RTKSW_CHK_PORT_VALID(unit, port);

    if (enable >= RTKSW_ENABLE_END)
        return RT_ERR_ENABLE;

    if ((retVal = rtl8367d_setAsicRegBit(unit, RTL8367D_REG_DOT1X_PORT_ENABLE, rtksw_switch_port_L2P_get(unit, port), enable)) != RT_ERR_OK)
        return retVal;

    return RT_ERR_OK;
}

/* Function Name:
 *      dal_rtl8367d_dot1x_portBasedEnable_get
 * Description:
 *      Get 802.1x port-based enable configuration
 * Input:
 *      unit    - Unit ID
 *      port    - Port id.
 * Output:
 *      pEnable - The status of 802.1x port.
 * Return:
 *      RT_ERR_OK           - OK
 *      RT_ERR_FAILED       - Failed
 *      RT_ERR_SMI          - SMI access error
 *      RT_ERR_INPUT        - Invalid input parameters.
 *      RT_ERR_PORT_ID      - Invalid port number.
 * Note:
 *      The API can get the 802.1x port-based port status.
 */
rtksw_api_ret_t dal_rtl8367d_dot1x_portBasedEnable_get(rtksw_uint32 unit, rtksw_port_t port, rtksw_enable_t *pEnable)
{
    rtksw_api_ret_t retVal;

    /* Check initialization state */
    RTKSW_CHK_INIT_STATE(unit);

    /* Check port Valid */
    RTKSW_CHK_PORT_VALID(unit, port);

    if(NULL == pEnable)
        return RT_ERR_NULL_POINTER;

    if ((retVal = rtl8367d_getAsicRegBit(unit, RTL8367D_REG_DOT1X_PORT_ENABLE, rtksw_switch_port_L2P_get(unit, port), pEnable)) != RT_ERR_OK)
        return retVal;

    return RT_ERR_OK;
}

/* Function Name:
 *      dal_rtl8367d_dot1x_portBasedAuthStatus_set
 * Description:
 *      Set 802.1x port-based auth. port configuration
 * Input:
 *      unit        - Unit ID
 *      port        - Port id.
 *      port_auth   - The status of 802.1x port.
 * Output:
 *      None
 * Return:
 *      RT_ERR_OK                   - OK
 *      RT_ERR_FAILED               - Failed
 *      RT_ERR_SMI                  - SMI access error
 *      RT_ERR_PORT_ID              - Invalid port number.
 *     RT_ERR_DOT1X_PORTBASEDAUTH   - 802.1X port-based auth error
 * Note:
 *      The authenticated status of 802.1x port-based network access control is as following:
 *      - UNAUTH
 *      - AUTH
 */
rtksw_api_ret_t dal_rtl8367d_dot1x_portBasedAuthStatus_set(rtksw_uint32 unit, rtksw_port_t port, rtksw_dot1x_auth_status_t port_auth)
{
    rtksw_api_ret_t retVal;

    /* Check initialization state */
    RTKSW_CHK_INIT_STATE(unit);

    /* Check port Valid */
    RTKSW_CHK_PORT_VALID(unit, port);

     if (port_auth >= AUTH_STATUS_END)
        return RT_ERR_DOT1X_PORTBASEDAUTH;

    if ((retVal = rtl8367d_setAsicRegBit(unit, RTL8367D_REG_DOT1X_PORT_AUTH, rtksw_switch_port_L2P_get(unit, port), port_auth)) != RT_ERR_OK)
        return retVal;

    return RT_ERR_OK;
}

/* Function Name:
 *      dal_rtl8367d_dot1x_portBasedAuthStatus_get
 * Description:
 *      Get 802.1x port-based auth. port configuration
 * Input:
 *      unit    - Unit ID
 *      port    - Port id.
 * Output:
 *      pPort_auth - The status of 802.1x port.
 * Return:
 *      RT_ERR_OK           - OK
 *      RT_ERR_FAILED       - Failed
 *      RT_ERR_SMI          - SMI access error
 *      RT_ERR_INPUT        - Invalid input parameters.
 *      RT_ERR_PORT_ID      - Invalid port number.
 * Note:
 *      The API can get 802.1x port-based port auth.information.
 */
rtksw_api_ret_t dal_rtl8367d_dot1x_portBasedAuthStatus_get(rtksw_uint32 unit, rtksw_port_t port, rtksw_dot1x_auth_status_t *pPort_auth)
{
    rtksw_api_ret_t retVal;

    /* Check initialization state */
    RTKSW_CHK_INIT_STATE(unit);

    if(NULL == pPort_auth)
        return RT_ERR_NULL_POINTER;

    /* Check port Valid */
    RTKSW_CHK_PORT_VALID(unit, port);

    if ((retVal = rtl8367d_getAsicRegBit(unit, RTL8367D_REG_DOT1X_PORT_AUTH, rtksw_switch_port_L2P_get(unit, port), pPort_auth)) != RT_ERR_OK)
        return retVal;

    return RT_ERR_OK;
}

/* Function Name:
 *      dal_rtl8367d_dot1x_portBasedDirection_set
 * Description:
 *      Set 802.1x port-based operational direction configuration
 * Input:
 *      unit            - Unit ID
 *      port            - Port id.
 *      port_direction  - Operation direction
 * Output:
 *      None
 * Return:
 *      RT_ERR_OK                   - OK
 *      RT_ERR_FAILED               - Failed
 *      RT_ERR_SMI                  - SMI access error
 *      RT_ERR_PORT_ID              - Invalid port number.
 *      RT_ERR_DOT1X_PORTBASEDOPDIR - 802.1X port-based operation direction error
 * Note:
 *      The operate controlled direction of 802.1x port-based network access control is as following:
 *      - BOTH
 *      - IN
 */
rtksw_api_ret_t dal_rtl8367d_dot1x_portBasedDirection_set(rtksw_uint32 unit, rtksw_port_t port, rtksw_dot1x_direction_t port_direction)
{
    rtksw_api_ret_t retVal;

    /* Check initialization state */
    RTKSW_CHK_INIT_STATE(unit);

    /* Check port Valid */
    RTKSW_CHK_PORT_VALID(unit, port);

    if (port_direction >= DIRECTION_END)
        return RT_ERR_DOT1X_PORTBASEDOPDIR;

    if ((retVal = rtl8367d_setAsicRegBit(unit, RTL8367D_REG_DOT1X_PORT_OPDIR, rtksw_switch_port_L2P_get(unit, port), port_direction)) != RT_ERR_OK)
        return retVal;

    return RT_ERR_OK;
}

/* Function Name:
 *      dal_rtl8367d_dot1x_portBasedDirection_get
 * Description:
 *      Get 802.1X port-based operational direction configuration
 * Input:
 *      unit    - Unit ID
 *      port    - Port id.
 * Output:
 *      pPort_direction - Operation direction
 * Return:
 *      RT_ERR_OK           - OK
 *      RT_ERR_FAILED       - Failed
 *      RT_ERR_SMI          - SMI access error
 *      RT_ERR_INPUT        - Invalid input parameters.
 *      RT_ERR_PORT_ID      - Invalid port number.
 * Note:
 *      The API can get 802.1x port-based operational direction information.
 */
rtksw_api_ret_t dal_rtl8367d_dot1x_portBasedDirection_get(rtksw_uint32 unit, rtksw_port_t port, rtksw_dot1x_direction_t *pPort_direction)
{
    rtksw_api_ret_t retVal;

    /* Check initialization state */
    RTKSW_CHK_INIT_STATE(unit);

    if(NULL == pPort_direction)
        return RT_ERR_NULL_POINTER;

    /* Check port Valid */
    RTKSW_CHK_PORT_VALID(unit, port);

    if ((retVal = rtl8367d_getAsicRegBit(unit, RTL8367D_REG_DOT1X_PORT_OPDIR, rtksw_switch_port_L2P_get(unit, port), pPort_direction)) != RT_ERR_OK)
        return retVal;

    return RT_ERR_OK;
}

