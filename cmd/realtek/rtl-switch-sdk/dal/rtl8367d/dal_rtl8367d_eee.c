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
 * Feature : Here is a list of all functions and variables in EEE module.
 *
 */

#include "../../rtk_switch.h"
#include "../../rtk_error.h"
#include "dal_rtl8367d_eee.h"
#include "dal_rtl8367d_port.h"

#include "rtl8367d_asicdrv.h"

#include "../dal_mgmts.h"

/* Function Name:
 *      dal_rtl8367d_eee_portEnable_set
 * Description:
 *      Set enable status of EEE function.
 * Input:
 *      unit    - Unit ID
 *      port    - port id.
 *      enable  - enable EEE status.
 * Output:
 *      None
 * Return:
 *      RT_ERR_OK              - OK
 *      RT_ERR_FAILED          - Failed
 *      RT_ERR_SMI             - SMI access error
 *      RT_ERR_PORT_ID - Invalid port number.
 *      RT_ERR_ENABLE - Invalid enable input.
 * Note:
 *      This API can set EEE function to the specific port.
 *      The configuration of the port is as following:
 *      - DISABLE
 *      - ENABLE
 */
rtksw_api_ret_t dal_rtl8367d_eee_portEnable_set(rtksw_uint32 unit, rtksw_port_t port, rtksw_enable_t enable)
{
    rtksw_api_ret_t retVal;
    rtksw_uint32 regData;

    /* Check initialization state */
    RTKSW_CHK_INIT_STATE(unit);

    /* Check port is UTP port */
    RTKSW_CHK_PORT_IS_UTP(unit, port);

    if (enable >= RTKSW_ENABLE_END)
        return RT_ERR_INPUT;

    if((retVal = dal_rtl8367d_port_phyOCPReg_get(unit, port, 0xA5D0, &regData)) != RT_ERR_OK)
        return retVal;

    if(enable)
    {
        regData |= (0x0001 << 1);
        regData |= (0x0001 << 2);
    }
    else
    {
        regData &= ~(0x0001 << 1);
        regData &= ~(0x0001 << 2);
    }

    if((retVal = dal_rtl8367d_port_phyOCPReg_set(unit, port, 0xA5D0, regData)) != RT_ERR_OK)
        return retVal;

    /* Restart Nway */
    if ((retVal = dal_rtl8367d_port_phyReg_get(unit, port, 0, &regData))!=RT_ERR_OK)
        return retVal;

    regData |= 0x0200;
    if ((retVal = dal_rtl8367d_port_phyReg_set(unit, port, 0, regData))!=RT_ERR_OK)
        return retVal;

    return RT_ERR_OK;
}

/* Function Name:
 *      dal_rtl8367d_eee_portEnable_get
 * Description:
 *      Get enable status of EEE function
 * Input:
 *      unit    - Unit ID
 *      port    - Port id.
 * Output:
 *      pEnable - Back pressure status.
 * Return:
 *      RT_ERR_OK              - OK
 *      RT_ERR_FAILED          - Failed
 *      RT_ERR_SMI             - SMI access error
 *      RT_ERR_PORT_ID - Invalid port number.
 * Note:
 *      This API can get EEE function to the specific port.
 *      The configuration of the port is as following:
 *      - DISABLE
 *      - ENABLE
 */
rtksw_api_ret_t dal_rtl8367d_eee_portEnable_get(rtksw_uint32 unit, rtksw_port_t port, rtksw_enable_t *pEnable)
{
    rtksw_api_ret_t retVal;
    rtksw_uint32 regData;

    /* Check initialization state */
    RTKSW_CHK_INIT_STATE(unit);

    /* Check port is UTP port */
    RTKSW_CHK_PORT_IS_UTP(unit, port);

    if(NULL == pEnable)
        return RT_ERR_NULL_POINTER;

    if((retVal = dal_rtl8367d_port_phyOCPReg_get(unit, port, 0xA5D0, &regData)) != RT_ERR_OK)
        return retVal;

    if ((regData & 0x0006) == 0x0006)
        *pEnable = RTKSW_ENABLED;
    else
        *pEnable = RTKSW_DISABLED;

    return RT_ERR_OK;
}

