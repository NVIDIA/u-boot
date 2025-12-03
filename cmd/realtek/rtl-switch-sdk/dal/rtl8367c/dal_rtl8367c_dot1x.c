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
#include "dal_rtl8367c_dot1x.h"
#include "dal_rtl8367c_vlan.h"
#include "rtl8367c_asicdrv.h"
#include "rtl8367c_asicdrv_dot1x.h"
#include "rtl8367c_asicdrv_rma.h"
#include "rtl8367c_asicdrv_lut.h"
#include "rtl8367c_asicdrv_vlan.h"

#include "../dal_mgmts.h"
#include "../../osal/lib.h"


/* Function Name:
 *      dal_rtl8367c_dot1x_unauthPacketOper_set
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
extern rtksw_api_ret_t dal_rtl8367c_dot1x_unauthPacketOper_set(rtksw_uint32 unit, rtksw_port_t port, rtksw_dot1x_unauth_action_t unauth_action)
{
    rtksw_api_ret_t retVal;

    /* Check initialization state */
    RTKSW_CHK_INIT_STATE(unit);

    /* Check port Valid */
    RTKSW_CHK_PORT_VALID(unit, port);

    if (unauth_action >= DOT1X_ACTION_END)
        return RT_ERR_DOT1X_PROC;

    if ((retVal = rtl8367c_setAsic1xProcConfig(unit, rtksw_switch_port_L2P_get(unit, port), unauth_action)) != RT_ERR_OK)
        return retVal;

    return RT_ERR_OK;
}

/* Function Name:
 *      dal_rtl8367c_dot1x_unauthPacketOper_get
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
rtksw_api_ret_t dal_rtl8367c_dot1x_unauthPacketOper_get(rtksw_uint32 unit, rtksw_port_t port, rtksw_dot1x_unauth_action_t *pUnauth_action)
{
    rtksw_api_ret_t retVal;

    /* Check initialization state */
    RTKSW_CHK_INIT_STATE(unit);

    /* Check port Valid */
    RTKSW_CHK_PORT_VALID(unit, port);

    if(NULL == pUnauth_action)
        return RT_ERR_NULL_POINTER;

    if ((retVal = rtl8367c_getAsic1xProcConfig(unit, rtksw_switch_port_L2P_get(unit, port), pUnauth_action)) != RT_ERR_OK)
        return retVal;

    return RT_ERR_OK;
}

/* Function Name:
 *      dal_rtl8367c_dot1x_eapolFrame2CpuEnable_set
 * Description:
 *      Set 802.1x EAPOL packet trap to CPU configuration
 * Input:
 *      unit        - Unit ID
 *      enable      - The status of 802.1x EAPOL packet.
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
rtksw_api_ret_t dal_rtl8367c_dot1x_eapolFrame2CpuEnable_set(rtksw_uint32 unit, rtksw_enable_t enable)
{
    rtksw_api_ret_t retVal;
    rtl8367c_rma_t rmacfg;

    /* Check initialization state */
    RTKSW_CHK_INIT_STATE(unit);

    if (enable >= RTKSW_ENABLE_END)
        return RT_ERR_ENABLE;

    if ((retVal = rtl8367c_getAsicRma(unit, 3, &rmacfg)) != RT_ERR_OK)
        return retVal;

    if (RTKSW_ENABLED == enable)
        rmacfg.operation = RMAOP_TRAP_TO_CPU;
    else if (RTKSW_DISABLED == enable)
        rmacfg.operation = RMAOP_FORWARD;

    if ((retVal = rtl8367c_setAsicRma(unit, 3, &rmacfg)) != RT_ERR_OK)
        return retVal;

    return RT_ERR_OK;
}

/* Function Name:
 *      dal_rtl8367c_dot1x_eapolFrame2CpuEnable_get
 * Description:
 *      Get 802.1x EAPOL packet trap to CPU configuration
 * Input:
 *      unit            - Unit ID
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
rtksw_api_ret_t dal_rtl8367c_dot1x_eapolFrame2CpuEnable_get(rtksw_uint32 unit, rtksw_enable_t *pEnable)
{
    rtksw_api_ret_t retVal;
    rtl8367c_rma_t rmacfg;

    /* Check initialization state */
    RTKSW_CHK_INIT_STATE(unit);

    if(NULL == pEnable)
        return RT_ERR_NULL_POINTER;

    if ((retVal = rtl8367c_getAsicRma(unit, 3, &rmacfg)) != RT_ERR_OK)
        return retVal;

    if (RMAOP_TRAP_TO_CPU == rmacfg.operation)
        *pEnable = RTKSW_ENABLED;
    else
        *pEnable = RTKSW_DISABLED;

    return RT_ERR_OK;
}

/* Function Name:
 *      dal_rtl8367c_dot1x_portBasedEnable_set
 * Description:
 *      Set 802.1x port-based enable configuration
 * Input:
 *      unit        - Unit ID
 *      port        - Port id.
 *      enable      - The status of 802.1x port.
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
rtksw_api_ret_t dal_rtl8367c_dot1x_portBasedEnable_set(rtksw_uint32 unit, rtksw_port_t port, rtksw_enable_t enable)
{
    rtksw_api_ret_t retVal;

    /* Check initialization state */
    RTKSW_CHK_INIT_STATE(unit);

    /* Check port Valid */
    RTKSW_CHK_PORT_VALID(unit, port);

    if (enable >= RTKSW_ENABLE_END)
        return RT_ERR_ENABLE;

    if ((retVal = rtl8367c_setAsic1xPBEnConfig(unit, rtksw_switch_port_L2P_get(unit, port),enable)) != RT_ERR_OK)
        return retVal;

    return RT_ERR_OK;
}

/* Function Name:
 *      dal_rtl8367c_dot1x_portBasedEnable_get
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
rtksw_api_ret_t dal_rtl8367c_dot1x_portBasedEnable_get(rtksw_uint32 unit, rtksw_port_t port, rtksw_enable_t *pEnable)
{
    rtksw_api_ret_t retVal;

    /* Check initialization state */
    RTKSW_CHK_INIT_STATE(unit);

    /* Check port Valid */
    RTKSW_CHK_PORT_VALID(unit, port);

    if(NULL == pEnable)
        return RT_ERR_NULL_POINTER;

    if ((retVal = rtl8367c_getAsic1xPBEnConfig(unit, rtksw_switch_port_L2P_get(unit, port), pEnable)) != RT_ERR_OK)
        return retVal;

    return RT_ERR_OK;
}

/* Function Name:
 *      dal_rtl8367c_dot1x_portBasedAuthStatus_set
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
rtksw_api_ret_t dal_rtl8367c_dot1x_portBasedAuthStatus_set(rtksw_uint32 unit, rtksw_port_t port, rtksw_dot1x_auth_status_t port_auth)
{
    rtksw_api_ret_t retVal;

    /* Check initialization state */
    RTKSW_CHK_INIT_STATE(unit);

    /* Check port Valid */
    RTKSW_CHK_PORT_VALID(unit, port);

     if (port_auth >= AUTH_STATUS_END)
        return RT_ERR_DOT1X_PORTBASEDAUTH;

    if ((retVal = rtl8367c_setAsic1xPBAuthConfig(unit, rtksw_switch_port_L2P_get(unit, port), port_auth)) != RT_ERR_OK)
        return retVal;


    return RT_ERR_OK;
}

/* Function Name:
 *      dal_rtl8367c_dot1x_portBasedAuthStatus_get
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
rtksw_api_ret_t dal_rtl8367c_dot1x_portBasedAuthStatus_get(rtksw_uint32 unit, rtksw_port_t port, rtksw_dot1x_auth_status_t *pPort_auth)
{
    rtksw_api_ret_t retVal;

    /* Check initialization state */
    RTKSW_CHK_INIT_STATE(unit);

    if(NULL == pPort_auth)
        return RT_ERR_NULL_POINTER;

    /* Check port Valid */
    RTKSW_CHK_PORT_VALID(unit, port);

    if ((retVal = rtl8367c_getAsic1xPBAuthConfig(unit, rtksw_switch_port_L2P_get(unit, port), pPort_auth)) != RT_ERR_OK)
        return retVal;
    return RT_ERR_OK;
}

/* Function Name:
 *      dal_rtl8367c_dot1x_portBasedDirection_set
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
rtksw_api_ret_t dal_rtl8367c_dot1x_portBasedDirection_set(rtksw_uint32 unit, rtksw_port_t port, rtksw_dot1x_direction_t port_direction)
{
    rtksw_api_ret_t retVal;

    /* Check initialization state */
    RTKSW_CHK_INIT_STATE(unit);

    /* Check port Valid */
    RTKSW_CHK_PORT_VALID(unit, port);

    if (port_direction >= DIRECTION_END)
        return RT_ERR_DOT1X_PORTBASEDOPDIR;

    if ((retVal = rtl8367c_setAsic1xPBOpdirConfig(unit, rtksw_switch_port_L2P_get(unit, port), port_direction)) != RT_ERR_OK)
        return retVal;

    return RT_ERR_OK;
}

/* Function Name:
 *      dal_rtl8367c_dot1x_portBasedDirection_get
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
rtksw_api_ret_t dal_rtl8367c_dot1x_portBasedDirection_get(rtksw_uint32 unit, rtksw_port_t port, rtksw_dot1x_direction_t *pPort_direction)
{
    rtksw_api_ret_t retVal;

    /* Check initialization state */
    RTKSW_CHK_INIT_STATE(unit);

    if(NULL == pPort_direction)
        return RT_ERR_NULL_POINTER;

    /* Check port Valid */
    RTKSW_CHK_PORT_VALID(unit, port);

    if ((retVal = rtl8367c_getAsic1xPBOpdirConfig(unit, rtksw_switch_port_L2P_get(unit, port), pPort_direction)) != RT_ERR_OK)
        return retVal;

    return RT_ERR_OK;
}

/* Function Name:
 *      dal_rtl8367c_dot1x_macBasedEnable_set
 * Description:
 *      Set 802.1x mac-based port enable configuration
 * Input:
 *      unit        - Unit ID
 *      port        - Port id.
 *      enable      - The status of 802.1x port.
 * Output:
 *      None
 * Return:
 *      RT_ERR_OK                   - OK
 *      RT_ERR_FAILED               - Failed
 *      RT_ERR_SMI                  - SMI access error
 *      RT_ERR_PORT_ID              - Invalid port number.
 *      RT_ERR_ENABLE               - Invalid enable input.
 *      RT_ERR_DOT1X_MACBASEDPNEN   - 802.1X mac-based enable error
 * Note:
 *      If a port is 802.1x MAC based network access control "enabled", the incoming packets should
 *       be authenticated so packets from that port won't be dropped or trapped to CPU.
 *      The status of 802.1x MAC-based network access control is as following:
 *      - RTKSW_DISABLED
 *      - RTKSW_ENABLED
 */
rtksw_api_ret_t dal_rtl8367c_dot1x_macBasedEnable_set(rtksw_uint32 unit, rtksw_port_t port, rtksw_enable_t enable)
{
    rtksw_api_ret_t retVal;

    /* Check initialization state */
    RTKSW_CHK_INIT_STATE(unit);

    /* Check port Valid */
    RTKSW_CHK_PORT_VALID(unit, port);

    if (enable >= RTKSW_ENABLE_END)
        return RT_ERR_ENABLE;

    if ((retVal = rtl8367c_setAsic1xMBEnConfig(unit, rtksw_switch_port_L2P_get(unit, port),enable)) != RT_ERR_OK)
        return retVal;

    return RT_ERR_OK;
}

/* Function Name:
 *      dal_rtl8367c_dot1x_macBasedEnable_get
 * Description:
 *      Get 802.1x mac-based port enable configuration
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
 *      If a port is 802.1x MAC based network access control "enabled", the incoming packets should
 *      be authenticated so packets from that port wont be dropped or trapped to CPU.
 *      The status of 802.1x MAC-based network access control is as following:
 *      - RTKSW_DISABLED
 *      - RTKSW_ENABLED
 */
rtksw_api_ret_t dal_rtl8367c_dot1x_macBasedEnable_get(rtksw_uint32 unit, rtksw_port_t port, rtksw_enable_t *pEnable)
{
    rtksw_api_ret_t retVal;

    /* Check initialization state */
    RTKSW_CHK_INIT_STATE(unit);

    if(NULL == pEnable)
        return RT_ERR_NULL_POINTER;

    /* Check port Valid */
    RTKSW_CHK_PORT_VALID(unit, port);

    if ((retVal = rtl8367c_getAsic1xMBEnConfig(unit, rtksw_switch_port_L2P_get(unit, port), pEnable)) != RT_ERR_OK)
        return retVal;

    return RT_ERR_OK;
}

/* Function Name:
 *      dal_rtl8367c_dot1x_macBasedAuthMac_add
 * Description:
 *      Add an authenticated MAC to ASIC
 * Input:
 *      unit        - Unit ID
 *      port        - Port id.
 *      pAuth_mac   - The authenticated MAC.
 *      fid         - filtering database.
 * Output:
 *      None
 * Return:
 *      RT_ERR_OK                   - OK
 *      RT_ERR_FAILED               - Failed
 *      RT_ERR_SMI                  - SMI access error
 *      RT_ERR_PORT_ID              - Invalid port number.
 *      RT_ERR_ENABLE               - Invalid enable input.
 *      RT_ERR_DOT1X_MACBASEDPNEN   - 802.1X mac-based enable error
 * Note:
 *      The API can add a 802.1x authenticated MAC address to port. If the MAC does not exist in LUT,
 *      user can't add this MAC to auth status.
 */
rtksw_api_ret_t dal_rtl8367c_dot1x_macBasedAuthMac_add(rtksw_uint32 unit, rtksw_port_t port, rtksw_mac_t *pAuth_mac, rtksw_fid_t fid)
{
    rtksw_api_ret_t retVal;
    rtksw_uint32 method;
    rtl8367c_luttb l2Table;

    /* Check initialization state */
    RTKSW_CHK_INIT_STATE(unit);

    /* must be unicast address */
    if ((pAuth_mac == NULL) || (pAuth_mac->octet[0] & 0x1))
        return RT_ERR_MAC;

    /* Check port Valid */
    RTKSW_CHK_PORT_VALID(unit, port);

    if (fid > RTL8367C_FIDMAX)
        return RT_ERR_L2_FID;

    osal_memset(&l2Table, 0, sizeof(rtl8367c_luttb));

    /* fill key (MAC,FID) to get L2 entry */
    osal_memcpy(l2Table.mac.octet, pAuth_mac->octet, ETHER_ADDR_LEN);
    l2Table.fid = fid;
    method = LUTREADMETHOD_MAC;
    retVal = rtl8367c_getAsicL2LookupTb(unit, method, &l2Table);
    if ( RT_ERR_OK == retVal)
    {
        if (l2Table.spa != rtksw_switch_port_L2P_get(unit, port))
            return RT_ERR_DOT1X_MAC_PORT_MISMATCH;

        osal_memcpy(l2Table.mac.octet, pAuth_mac->octet, ETHER_ADDR_LEN);
        l2Table.fid = fid;
        l2Table.efid = 0;
        l2Table.auth = 1;
        retVal = rtl8367c_setAsicL2LookupTb(unit, &l2Table);
        return retVal;
    }
    else
        return retVal;

}

/* Function Name:
 *      dal_rtl8367c_dot1x_macBasedAuthMac_del
 * Description:
 *      Delete an authenticated MAC to ASIC
 * Input:
 *      unit        - Unit ID
 *      port        - Port id.
 *      pAuth_mac   - The authenticated MAC.
 *      fid         - filtering database.
 * Output:
 *      None
 * Return:
 *      RT_ERR_OK           - OK
 *      RT_ERR_FAILED       - Failed
 *      RT_ERR_SMI          - SMI access error
 *      RT_ERR_MAC          - Invalid MAC address.
 *      RT_ERR_PORT_ID      - Invalid port number.
 * Note:
 *      The API can delete a 802.1x authenticated MAC address to port. It only change the auth status of
 *      the MAC and won't delete it from LUT.
 */
rtksw_api_ret_t dal_rtl8367c_dot1x_macBasedAuthMac_del(rtksw_uint32 unit, rtksw_port_t port, rtksw_mac_t *pAuth_mac, rtksw_fid_t fid)
{
    rtksw_api_ret_t retVal;
    rtksw_uint32 method;
    rtl8367c_luttb l2Table;

    /* Check initialization state */
    RTKSW_CHK_INIT_STATE(unit);

    /* must be unicast address */
    if ((pAuth_mac == NULL) || (pAuth_mac->octet[0] & 0x1))
        return RT_ERR_MAC;

    /* Check port Valid */
    RTKSW_CHK_PORT_VALID(unit, port);

    if (fid > RTL8367C_FIDMAX)
        return RT_ERR_L2_FID;

    osal_memset(&l2Table, 0, sizeof(rtl8367c_luttb));

    /* fill key (MAC,FID) to get L2 entry */
    osal_memcpy(l2Table.mac.octet, pAuth_mac->octet, ETHER_ADDR_LEN);
    l2Table.fid = fid;
    method = LUTREADMETHOD_MAC;
    retVal = rtl8367c_getAsicL2LookupTb(unit, method, &l2Table);
    if (RT_ERR_OK == retVal)
    {
        if (l2Table.spa != rtksw_switch_port_L2P_get(unit, port))
            return RT_ERR_DOT1X_MAC_PORT_MISMATCH;

        osal_memcpy(l2Table.mac.octet, pAuth_mac->octet, ETHER_ADDR_LEN);
        l2Table.fid = fid;
        l2Table.auth = 0;
        retVal = rtl8367c_setAsicL2LookupTb(unit, &l2Table);
        return retVal;
    }
    else
        return retVal;

}

/* Function Name:
 *      dal_rtl8367c_dot1x_macBasedDirection_set
 * Description:
 *      Set 802.1x mac-based operational direction configuration
 * Input:
 *      unit            - Unit ID
 *      mac_direction   - Operation direction
 * Output:
 *      None
 * Return:
 *      RT_ERR_OK                   - OK
 *      RT_ERR_FAILED               - Failed
 *      RT_ERR_SMI                  - SMI access error
 *      RT_ERR_INPUT                - Invalid input parameter.
 *      RT_ERR_DOT1X_MACBASEDOPDIR  - 802.1X mac-based operation direction error
 * Note:
 *      The operate controlled direction of 802.1x mac-based network access control is as following:
 *      - BOTH
 *      - IN
 */
rtksw_api_ret_t dal_rtl8367c_dot1x_macBasedDirection_set(rtksw_uint32 unit, rtksw_dot1x_direction_t mac_direction)
{
    rtksw_api_ret_t retVal;

    /* Check initialization state */
    RTKSW_CHK_INIT_STATE(unit);

    if (mac_direction >= DIRECTION_END)
        return RT_ERR_DOT1X_MACBASEDOPDIR;

    if ((retVal = rtl8367c_setAsic1xMBOpdirConfig(unit, mac_direction)) != RT_ERR_OK)
        return retVal;

    return RT_ERR_OK;
}

/* Function Name:
 *      dal_rtl8367c_dot1x_macBasedDirection_get
 * Description:
 *      Get 802.1x mac-based operational direction configuration
 * Input:
 *      unit    - Unit ID
 *      port    - Port id.
 * Output:
 *      pMac_direction - Operation direction
 * Return:
 *      RT_ERR_OK           - OK
 *      RT_ERR_FAILED       - Failed
 *      RT_ERR_SMI          - SMI access error
 *      RT_ERR_INPUT        - Invalid input parameters.
 * Note:
 *      The API can get 802.1x mac-based operational direction information.
 */
rtksw_api_ret_t dal_rtl8367c_dot1x_macBasedDirection_get(rtksw_uint32 unit, rtksw_dot1x_direction_t *pMac_direction)
{
    rtksw_api_ret_t retVal;

    /* Check initialization state */
    RTKSW_CHK_INIT_STATE(unit);

    if(NULL == pMac_direction)
        return RT_ERR_NULL_POINTER;

    if ((retVal = rtl8367c_getAsic1xMBOpdirConfig(unit, pMac_direction)) != RT_ERR_OK)
        return retVal;

    return RT_ERR_OK;
}

/* Function Name:
 *      Set 802.1x guest VLAN configuration
 * Description:
 *      Set 802.1x mac-based operational direction configuration
 * Input:
 *      unit    - Unit ID
 *      vid     - 802.1x guest VLAN ID
 * Output:
 *      None
 * Return:
 *      RT_ERR_OK           - OK
 *      RT_ERR_FAILED       - Failed
 *      RT_ERR_SMI          - SMI access error
 *      RT_ERR_INPUT        - Invalid input parameter.
 * Note:
 *      The operate controlled 802.1x guest VLAN
 */
rtksw_api_ret_t dal_rtl8367c_dot1x_guestVlan_set(rtksw_uint32 unit, rtksw_vlan_t vid)
{
    rtksw_api_ret_t retVal;
    rtksw_uint32 index;

    /* Check initialization state */
    RTKSW_CHK_INIT_STATE(unit);

    /* vid must be 0~4095 */
    if (vid > RTL8367C_VIDMAX)
        return RT_ERR_VLAN_VID;

    if((retVal = dal_rtl8367c_vlan_checkAndCreateMbr(unit, vid, &index)) != RT_ERR_OK)
        return retVal;

    if ((retVal = rtl8367c_setAsic1xGuestVidx(unit, index)) != RT_ERR_OK)
        return retVal;

    return RT_ERR_OK;
}

/* Function Name:
 *      dal_rtl8367c_dot1x_guestVlan_get
 * Description:
 *      Get 802.1x guest VLAN configuration
 * Input:
 *      unit            - Unit ID
 * Output:
 *      pVid - 802.1x guest VLAN ID
 * Return:
 *      RT_ERR_OK           - OK
 *      RT_ERR_FAILED       - Failed
 *      RT_ERR_SMI          - SMI access error
 *      RT_ERR_INPUT        - Invalid input parameters.
 * Note:
 *      The API can get 802.1x guest VLAN information.
 */
rtksw_api_ret_t dal_rtl8367c_dot1x_guestVlan_get(rtksw_uint32 unit, rtksw_vlan_t *pVid)
{
    rtksw_api_ret_t retVal;
    rtksw_uint32 gvidx;
    rtl8367c_vlanconfiguser vlanMC;

    /* Check initialization state */
    RTKSW_CHK_INIT_STATE(unit);

    if(NULL == pVid)
        return RT_ERR_NULL_POINTER;

    if ((retVal = rtl8367c_getAsic1xGuestVidx(unit, &gvidx)) != RT_ERR_OK)
        return retVal;

    if ((retVal = rtl8367c_getAsicVlanMemberConfig(unit, gvidx, &vlanMC)) != RT_ERR_OK)
        return retVal;

    *pVid = vlanMC.evid;

    return RT_ERR_OK;
}

/* Function Name:
 *      dal_rtl8367c_dot1x_guestVlan2Auth_set
 * Description:
 *      Set 802.1x guest VLAN to auth host configuration
 * Input:
 *      unit    - Unit ID
 *      enable  - The status of guest VLAN to auth host.
 * Output:
 *      None
 * Return:
 *      RT_ERR_OK           - OK
 *      RT_ERR_FAILED       - Failed
 *      RT_ERR_SMI          - SMI access error
 *      RT_ERR_INPUT        - Invalid input parameter.
 * Note:
 *      The operational direction of 802.1x guest VLAN to auth host control is as following:
 *      - RTKSW_ENABLED
 *      - RTKSW_DISABLED
 */
rtksw_api_ret_t dal_rtl8367c_dot1x_guestVlan2Auth_set(rtksw_uint32 unit, rtksw_enable_t enable)
{
    rtksw_api_ret_t retVal;

    /* Check initialization state */
    RTKSW_CHK_INIT_STATE(unit);

    if (enable >= RTKSW_ENABLE_END)
        return RT_ERR_ENABLE;

    if ((retVal = rtl8367c_setAsic1xGVOpdir(unit, enable)) != RT_ERR_OK)
        return retVal;

    return RT_ERR_OK;
}

/* Function Name:
 *      dal_rtl8367c_dot1x_guestVlan2Auth_get
 * Description:
 *      Get 802.1x guest VLAN to auth host configuration
 * Input:
 *      unit            - Unit ID
 * Output:
 *      pEnable - The status of guest VLAN to auth host.
 * Return:
 *      RT_ERR_OK           - OK
 *      RT_ERR_FAILED       - Failed
 *      RT_ERR_SMI          - SMI access error
 *      RT_ERR_INPUT        - Invalid input parameters.
 * Note:
 *      The API can get 802.1x guest VLAN to auth host information.
 */
rtksw_api_ret_t dal_rtl8367c_dot1x_guestVlan2Auth_get(rtksw_uint32 unit, rtksw_enable_t *pEnable)
{
    rtksw_api_ret_t retVal;

    /* Check initialization state */
    RTKSW_CHK_INIT_STATE(unit);

    if(NULL == pEnable)
        return RT_ERR_NULL_POINTER;

    if ((retVal = rtl8367c_getAsic1xGVOpdir(unit, pEnable)) != RT_ERR_OK)
        return retVal;

    return RT_ERR_OK;
}

