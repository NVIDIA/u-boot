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
 * Feature : Here is a list of all functions and variables in OAM(802.3ah)  module.
 *
 */

#include "../../rtk_switch.h"
#include "../../rtk_error.h"
#include "dal_rtl8367c_oam.h"

#include "rtl8367c_asicdrv.h"
#include "rtl8367c_asicdrv_oam.h"

#include "../dal_mgmts.h"

/* Module Name : OAM */

/* Function Name:
 *      dal_rtl8367c_oam_init
 * Description:
 *      Initialize oam module.
 * Input:
 *      unit    - Unit ID
 * Output:
 *      None
 * Return:
 *      RT_ERR_OK
 *      RT_ERR_FAILED
 * Note:
 *      Must initialize oam module before calling any oam APIs.
 */
rtksw_api_ret_t dal_rtl8367c_oam_init(rtksw_uint32 unit)
{
    /* Skip warning */
    if (unit) {};

    return RT_ERR_OK;
}

/* Function Name:
 *      dal_rtl8367c_oam_state_set
 * Description:
 *      This API set OAM state.
 * Input:
 *      unit        - Unit ID
 *      enabled     - OAMstate
 * Output:
 *      None.
 * Return:
 *      RT_ERR_OK              - OK
 *      RT_ERR_FAILED          - Failed
 *      RT_ERR_SMI             - SMI access error
 *      RT_ERR_INPUT           - Error parameter
 * Note:
 *      This API set OAM state.
 */
rtksw_api_ret_t dal_rtl8367c_oam_state_set(rtksw_uint32 unit, rtksw_enable_t enabled)
{
    rtksw_api_ret_t retVal;

    /* Check initialization state */
    RTKSW_CHK_INIT_STATE(unit);

    if (enabled >= RTKSW_ENABLE_END)
        return RT_ERR_INPUT;

    if ((retVal = rtl8367c_setAsicOamEnable(unit, enabled))!=RT_ERR_OK)
        return retVal;

    return RT_ERR_OK;
}

/* Function Name:
 *      dal_rtl8367c_oam_state_get
 * Description:
 *      This API get OAM state.
 * Input:
 *      unit    - Unit ID
 * Output:
 *      pEnabled        - H/W IGMP state
 * Return:
 *      RT_ERR_OK              - OK
 *      RT_ERR_FAILED          - Failed
 *      RT_ERR_SMI             - SMI access error
 *      RT_ERR_INPUT           - Error parameter
 * Note:
 *      This API set current OAM state.
 */
rtksw_api_ret_t dal_rtl8367c_oam_state_get(rtksw_uint32 unit, rtksw_enable_t *pEnabled)
{
    rtksw_api_ret_t retVal;

    /* Check initialization state */
    RTKSW_CHK_INIT_STATE(unit);

    if ((retVal = rtl8367c_getAsicOamEnable(unit, pEnabled))!=RT_ERR_OK)
        return retVal;

    return RT_ERR_OK;
}

/* Function Name:
 *      dal_rtl8367c_oam_parserAction_set
 * Description:
 *      Set OAM parser action
 * Input:
 *      unit    - Unit ID
 *      port    - port id
 *      action  - parser action
 * Output:
 *      None
 * Return:
 *      RT_ERR_OK
 *      RT_ERR_FAILED
 *      RT_ERR_PORT_ID      - invalid port id
 * Note:
 *      None
 */
rtksw_api_ret_t  dal_rtl8367c_oam_parserAction_set(rtksw_uint32 unit, rtksw_port_t port, rtksw_oam_parser_act_t action)
{
    rtksw_api_ret_t retVal;

    /* Check initialization state */
    RTKSW_CHK_INIT_STATE(unit);

    /* Check Port Valid */
    RTKSW_CHK_PORT_VALID(unit, port);

    if (action >= OAM_PARSER_ACTION_END)
        return RT_ERR_INPUT;

    if ((retVal = rtl8367c_setAsicOamParser(unit, rtksw_switch_port_L2P_get(unit, port), action))!=RT_ERR_OK)
        return retVal;

    return RT_ERR_OK;
}

/* Function Name:
 *      dal_rtl8367c_oam_parserAction_set
 * Description:
 *      Get OAM parser action
 * Input:
 *      unit    - Unit ID
 *      port    - port id
 * Output:
 *      pAction  - parser action
 * Return:
 *      RT_ERR_OK
 *      RT_ERR_FAILED
 *      RT_ERR_PORT_ID      - invalid port id
 * Note:
 *      None
 */
rtksw_api_ret_t  dal_rtl8367c_oam_parserAction_get(rtksw_uint32 unit, rtksw_port_t port, rtksw_oam_parser_act_t *pAction)
{
    rtksw_api_ret_t retVal;

    /* Check initialization state */
    RTKSW_CHK_INIT_STATE(unit);

    /* Check Port Valid */
    RTKSW_CHK_PORT_VALID(unit, port);

    if ((retVal = rtl8367c_getAsicOamParser(unit, rtksw_switch_port_L2P_get(unit, port), pAction))!=RT_ERR_OK)
        return retVal;

    return RT_ERR_OK;
}

/* Function Name:
 *      dal_rtl8367c_oam_multiplexerAction_set
 * Description:
 *      Set OAM multiplexer action
 * Input:
 *      unit    - Unit ID
 *      port    - port id
 *      action  - parser action
 * Output:
 *      None
 * Return:
 *      RT_ERR_OK
 *      RT_ERR_FAILED
 *      RT_ERR_PORT_ID      - invalid port id
 * Note:
 *      None
 */
rtksw_api_ret_t  dal_rtl8367c_oam_multiplexerAction_set(rtksw_uint32 unit, rtksw_port_t port, rtksw_oam_multiplexer_act_t action)
{
    rtksw_api_ret_t retVal;

    /* Check initialization state */
    RTKSW_CHK_INIT_STATE(unit);

    /* Check Port Valid */
    RTKSW_CHK_PORT_VALID(unit, port);

    if (action >= OAM_MULTIPLEXER_ACTION_END)
        return RT_ERR_INPUT;

    if ((retVal = rtl8367c_setAsicOamMultiplexer(unit, rtksw_switch_port_L2P_get(unit, port), action))!=RT_ERR_OK)
        return retVal;

    return RT_ERR_OK;
}

/* Function Name:
 *      dal_rtl8367c_oam_parserAction_set
 * Description:
 *      Get OAM multiplexer action
 * Input:
 *      unit    - Unit ID
 *      port    - port id
 * Output:
 *      pAction  - parser action
 * Return:
 *      RT_ERR_OK
 *      RT_ERR_FAILED
 *      RT_ERR_PORT_ID      - invalid port id
 * Note:
 *      None
 */
rtksw_api_ret_t  dal_rtl8367c_oam_multiplexerAction_get(rtksw_uint32 unit, rtksw_port_t port, rtksw_oam_multiplexer_act_t *pAction)
{
    rtksw_api_ret_t retVal;

    /* Check initialization state */
    RTKSW_CHK_INIT_STATE(unit);

    /* Check Port Valid */
    RTKSW_CHK_PORT_VALID(unit, port);

    if ((retVal = rtl8367c_getAsicOamMultiplexer(unit, rtksw_switch_port_L2P_get(unit, port), pAction))!=RT_ERR_OK)
        return retVal;

    return RT_ERR_OK;
}

