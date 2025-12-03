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
 * Feature : Here is a list of all functions and variables in CPU module.
 *
 */

#include "../../rtk_switch.h"
#include "../../rtk_error.h"
#include "dal_rtl8367c_cpu.h"

#include "rtl8367c_asicdrv.h"
#include "rtl8367c_asicdrv_cputag.h"

#include "../dal_mgmts.h"

/* Function Name:
 *      dal_rtl8367c_cpu_enable_set
 * Description:
 *      Set CPU port function enable/disable.
 * Input:
 *      unit    - Unit ID
 *      enable  - CPU port function enable
 * Output:
 *      None
 * Return:
 *      RT_ERR_OK           - OK
 *      RT_ERR_FAILED       - Failed
 *      RT_ERR_SMI          - SMI access error
 *      RT_ERR_INPUT        - Invalid input parameter.
 *      RT_ERR_PORT_ID      - Invalid port number.
 * Note:
 *      The API can set CPU port function enable/disable.
 */
rtksw_api_ret_t dal_rtl8367c_cpu_enable_set(rtksw_uint32 unit, rtksw_enable_t enable)
{
    rtksw_api_ret_t retVal;

    /* Check initialization state */
    RTKSW_CHK_INIT_STATE(unit);

    if (enable >= RTKSW_ENABLE_END)
        return RT_ERR_ENABLE;

    if ((retVal = rtl8367c_setAsicCputagEnable(unit, enable)) != RT_ERR_OK)
        return retVal;

    if (RTKSW_DISABLED == enable)
    {
        if ((retVal = rtl8367c_setAsicCputagPortmask(unit, 0)) != RT_ERR_OK)
            return retVal;
    }

    return RT_ERR_OK;
}


/* Function Name:
 *      dal_rtl8367c_cpu_enable_get
 * Description:
 *      Get CPU port and its setting.
 * Input:
 *      unit    - Unit ID
 * Output:
 *      pEnable - CPU port function enable
 * Return:
 *      RT_ERR_OK               - OK
 *      RT_ERR_FAILED           - Failed
 *      RT_ERR_SMI              - SMI access error
 *      RT_ERR_INPUT            - Invalid input parameters.
 *      RT_ERR_L2_NO_CPU_PORT   - CPU port is not exist
 * Note:
 *      The API can get CPU port function enable/disable.
 */
rtksw_api_ret_t dal_rtl8367c_cpu_enable_get(rtksw_uint32 unit, rtksw_enable_t *pEnable)

{
    rtksw_api_ret_t retVal;

    /* Check initialization state */
    RTKSW_CHK_INIT_STATE(unit);

    if(NULL == pEnable)
        return RT_ERR_NULL_POINTER;

    if ((retVal = rtl8367c_getAsicCputagEnable(unit, pEnable)) != RT_ERR_OK)
        return retVal;

    return RT_ERR_OK;
}

/* Function Name:
 *      dal_rtl8367c_cpu_tagPort_set
 * Description:
 *      Set CPU port and CPU tag insert mode.
 * Input:
 *      unit    - Unit ID
 *      port    - Port id.
 *      mode    - CPU tag insert for packets egress from CPU port.
 * Output:
 *      None
 * Return:
 *      RT_ERR_OK           - OK
 *      RT_ERR_FAILED       - Failed
 *      RT_ERR_SMI          - SMI access error
 *      RT_ERR_INPUT        - Invalid input parameter.
 *      RT_ERR_PORT_ID      - Invalid port number.
 * Note:
 *      The API can set CPU port and inserting proprietary CPU tag mode (Length/Type 0x8899)
 *      to the frame that transmitting to CPU port.
 *      The inset cpu tag mode is as following:
 *      - CPU_INSERT_TO_ALL
 *      - CPU_INSERT_TO_TRAPPING
 *      - CPU_INSERT_TO_NONE
 */
rtksw_api_ret_t dal_rtl8367c_cpu_tagPort_set(rtksw_uint32 unit, rtksw_port_t port, rtksw_cpu_insert_t mode)
{
    rtksw_api_ret_t retVal;
    rtksw_uint32 phyPort;

    /* Check initialization state */
    RTKSW_CHK_INIT_STATE(unit);

    /* Check port Valid */
    RTKSW_CHK_PORT_VALID(unit, port);

    if (mode >= CPU_INSERT_END)
        return RT_ERR_INPUT;

    phyPort = rtksw_switch_port_L2P_get(unit, port);
    if (phyPort == UNDEFINE_PHY_PORT)
        return RT_ERR_PORT_ID;

    if ((retVal = rtl8367c_setAsicCputagPortmask(unit, 1<<phyPort)) != RT_ERR_OK)
        return retVal;

    if ((retVal = rtl8367c_setAsicCputagTrapPort(unit, phyPort)) != RT_ERR_OK)
        return retVal;

    if ((retVal = rtl8367c_setAsicCputagInsertMode(unit, mode)) != RT_ERR_OK)
        return retVal;

    return RT_ERR_OK;
}

/* Function Name:
 *      dal_rtl8367c_cpu_tagPort_get
 * Description:
 *      Get CPU port and CPU tag insert mode.
 * Input:
 *      unit    - Unit ID
 * Output:
 *      pPort - Port id.
 *      pMode - CPU tag insert for packets egress from CPU port, 0:all insert 1:Only for trapped packets 2:no insert.
 * Return:
 *      RT_ERR_OK               - OK
 *      RT_ERR_FAILED           - Failed
 *      RT_ERR_SMI              - SMI access error
 *      RT_ERR_INPUT            - Invalid input parameters.
 *      RT_ERR_L2_NO_CPU_PORT   - CPU port is not exist
 * Note:
 *      The API can get configured CPU port and its setting.
 *      The inset cpu tag mode is as following:
 *      - CPU_INSERT_TO_ALL
 *      - CPU_INSERT_TO_TRAPPING
 *      - CPU_INSERT_TO_NONE
 */
rtksw_api_ret_t dal_rtl8367c_cpu_tagPort_get(rtksw_uint32 unit, rtksw_port_t *pPort, rtksw_cpu_insert_t *pMode)
{
    rtksw_api_ret_t retVal;
    rtksw_uint32 pmsk, port;

    /* Check initialization state */
    RTKSW_CHK_INIT_STATE(unit);

    if(NULL == pPort)
        return RT_ERR_NULL_POINTER;

    if(NULL == pMode)
        return RT_ERR_NULL_POINTER;

    if ((retVal = rtl8367c_getAsicCputagPortmask(unit, &pmsk)) != RT_ERR_OK)
        return retVal;

    if ((retVal = rtl8367c_getAsicCputagTrapPort(unit, &port)) != RT_ERR_OK)
        return retVal;

    *pPort = rtksw_switch_port_P2L_get(unit, port);

    if ((retVal = rtl8367c_getAsicCputagInsertMode(unit, pMode)) != RT_ERR_OK)
        return retVal;

    return RT_ERR_OK;
}

/* Function Name:
 *      dal_rtl8367c_cpu_awarePort_set
 * Description:
 *      Set CPU aware port mask.
 * Input:
 *      unit        - Unit ID
 *      portmask    - Port mask.
 * Output:
 *      None
 * Return:
 *      RT_ERR_OK           - OK
 *      RT_ERR_FAILED       - Failed
 *      RT_ERR_SMI          - SMI access error
 *      RT_ERR_PORT_MASK      - Invalid port mask.
 * Note:
 *      The API can set configured CPU aware port mask.
 */
rtksw_api_ret_t dal_rtl8367c_cpu_awarePort_set(rtksw_uint32 unit, rtksw_portmask_t *pPortmask)
{
    rtksw_api_ret_t retVal;
    rtksw_uint32 phyMbrPmask;

    /* Check initialization state */
    RTKSW_CHK_INIT_STATE(unit);

    /* Check Valid port mask */
    if(NULL == pPortmask)
        return RT_ERR_NULL_POINTER;

    /* Check port mask valid */
    RTKSW_CHK_PORTMASK_VALID(unit, pPortmask);

    if(rtksw_switch_portmask_L2P_get(unit, pPortmask, &phyMbrPmask) != RT_ERR_OK)
        return RT_ERR_FAILED;

    if ((retVal = rtl8367c_setAsicCputagPortmask(unit, phyMbrPmask)) != RT_ERR_OK)
        return retVal;

    return RT_ERR_OK;
}

/* Function Name:
 *      dal_rtl8367c_cpu_awarePort_get
 * Description:
 *      Get CPU aware port mask.
 * Input:
 *      unit    - Unit ID
 * Output:
 *      pPortmask - Port mask.
 * Return:
 *      RT_ERR_OK               - OK
 *      RT_ERR_FAILED           - Failed
 *      RT_ERR_SMI              - SMI access error
 * Note:
 *      The API can get configured CPU aware port mask.
 */
rtksw_api_ret_t dal_rtl8367c_cpu_awarePort_get(rtksw_uint32 unit, rtksw_portmask_t *pPortmask)
{
    rtksw_api_ret_t retVal;
    rtksw_uint32 pmsk;

    /* Check initialization state */
    RTKSW_CHK_INIT_STATE(unit);

    if(NULL == pPortmask)
        return RT_ERR_NULL_POINTER;

    if ((retVal = rtl8367c_getAsicCputagPortmask(unit, &pmsk)) != RT_ERR_OK)
        return retVal;

    if(rtksw_switch_portmask_P2L_get(unit, pmsk, pPortmask) != RT_ERR_OK)
        return RT_ERR_FAILED;

    return RT_ERR_OK;
}

/* Function Name:
 *      dal_rtl8367c_cpu_tagPosition_set
 * Description:
 *      Set CPU tag position.
 * Input:
 *      unit        - Unit ID
 *      position    - CPU tag position.
 * Output:
 *      None
 * Return:
 *      RT_ERR_OK           - OK
 *      RT_ERR_FAILED       - Failed
 *      RT_ERR_SMI          - SMI access error
 *      RT_ERR_INPUT      - Invalid input.
 * Note:
 *      The API can set CPU tag position.
 */
rtksw_api_ret_t dal_rtl8367c_cpu_tagPosition_set(rtksw_uint32 unit, rtksw_cpu_position_t position)
{
    rtksw_api_ret_t retVal;

    /* Check initialization state */
    RTKSW_CHK_INIT_STATE(unit);

    if (position >= CPU_POS_END)
        return RT_ERR_INPUT;

    if ((retVal = rtl8367c_setAsicCputagPosition(unit, position)) != RT_ERR_OK)
        return retVal;

    return RT_ERR_OK;
}

/* Function Name:
 *      dal_rtl8367c_cpu_tagPosition_get
 * Description:
 *      Get CPU tag position.
 * Input:
 *      unit    - Unit ID
 * Output:
 *      pPosition - CPU tag position.
 * Return:
 *      RT_ERR_OK           - OK
 *      RT_ERR_FAILED       - Failed
 *      RT_ERR_SMI          - SMI access error
 *      RT_ERR_INPUT      - Invalid input.
 * Note:
 *      The API can get CPU tag position.
 */
rtksw_api_ret_t dal_rtl8367c_cpu_tagPosition_get(rtksw_uint32 unit, rtksw_cpu_position_t *pPosition)
{
    rtksw_api_ret_t retVal;

    /* Check initialization state */
    RTKSW_CHK_INIT_STATE(unit);

    if(NULL == pPosition)
        return RT_ERR_NULL_POINTER;

    if ((retVal = rtl8367c_getAsicCputagPosition(unit, pPosition)) != RT_ERR_OK)
        return retVal;

    return RT_ERR_OK;
}

/* Function Name:
 *      dal_rtl8367c_cpu_tagLength_set
 * Description:
 *      Set CPU tag length.
 * Input:
 *      unit    - Unit ID
 *      length  - CPU tag length.
 * Output:
 *      None
 * Return:
 *      RT_ERR_OK           - OK
 *      RT_ERR_FAILED       - Failed
 *      RT_ERR_SMI          - SMI access error
 *      RT_ERR_INPUT      - Invalid input.
 * Note:
 *      The API can set CPU tag length.
 */
rtksw_api_ret_t dal_rtl8367c_cpu_tagLength_set(rtksw_uint32 unit, rtksw_cpu_tag_length_t length)
{
    rtksw_api_ret_t retVal;

    /* Check initialization state */
    RTKSW_CHK_INIT_STATE(unit);

    if (length >= CPU_LEN_4BYTES_PRIORITY)
        return RT_ERR_INPUT;

    if ((retVal = rtl8367c_setAsicCputagMode(unit, length)) != RT_ERR_OK)
        return retVal;

    return RT_ERR_OK;
}

/* Function Name:
 *      dal_rtl8367c_cpu_tagLength_get
 * Description:
 *      Get CPU tag length.
 * Input:
 *      unit    - Unit ID
 * Output:
 *      pLength - CPU tag length.
 * Return:
 *      RT_ERR_OK           - OK
 *      RT_ERR_FAILED       - Failed
 *      RT_ERR_SMI          - SMI access error
 *      RT_ERR_INPUT      - Invalid input.
 * Note:
 *      The API can get CPU tag length.
 */
rtksw_api_ret_t dal_rtl8367c_cpu_tagLength_get(rtksw_uint32 unit, rtksw_cpu_tag_length_t *pLength)
{
    rtksw_api_ret_t retVal;

    /* Check initialization state */
    RTKSW_CHK_INIT_STATE(unit);

    if(NULL == pLength)
        return RT_ERR_NULL_POINTER;

    if ((retVal = rtl8367c_getAsicCputagMode(unit, pLength)) != RT_ERR_OK)
        return retVal;

    return RT_ERR_OK;
}

/* Function Name:
 *      dal_rtl8367c_cpu_priRemap_set
 * Description:
 *      Configure CPU priorities mapping to internal absolute priority.
 * Input:
 *      unit        - Unit ID
 *      int_pri     - internal priority value.
 *      new_pri     - new internal priority value.
 * Output:
 *      None
 * Return:
 *      RT_ERR_OK               - OK
 *      RT_ERR_FAILED           - Failed
 *      RT_ERR_SMI              - SMI access error
 *      RT_ERR_INPUT            - Invalid input parameters.
 *      RT_ERR_VLAN_PRIORITY    - Invalid 1p priority.
 *      RT_ERR_QOS_INT_PRIORITY - Invalid priority.
 * Note:
 *      Priority of CPU tag assignment for internal asic priority, and it is used for queue usage and packet scheduling.
 */
rtksw_api_ret_t dal_rtl8367c_cpu_priRemap_set(rtksw_uint32 unit, rtksw_pri_t int_pri, rtksw_pri_t new_pri)
{
    rtksw_api_ret_t retVal;

    /* Check initialization state */
    RTKSW_CHK_INIT_STATE(unit);

    if (new_pri > RTL8367C_PRIMAX || int_pri > RTL8367C_PRIMAX)
        return  RT_ERR_VLAN_PRIORITY;

    if ((retVal = rtl8367c_setAsicCputagPriorityRemapping(unit, int_pri, new_pri)) != RT_ERR_OK)
        return retVal;

    return RT_ERR_OK;
}

/* Function Name:
 *      dal_rtl8367c_cpu_priRemap_get
 * Description:
 *      Configure CPU priorities mapping to internal absolute priority.
 * Input:
 *      unit        - Unit ID
 *      int_pri     - internal priority value.
 * Output:
 *      pNew_pri    - new internal priority value.
 * Return:
 *      RT_ERR_OK               - OK
 *      RT_ERR_FAILED           - Failed
 *      RT_ERR_SMI              - SMI access error
 *      RT_ERR_INPUT            - Invalid input parameters.
 *      RT_ERR_VLAN_PRIORITY    - Invalid 1p priority.
 *      RT_ERR_QOS_INT_PRIORITY - Invalid priority.
 * Note:
 *      Priority of CPU tag assignment for internal asic priority, and it is used for queue usage and packet scheduling.
 */
rtksw_api_ret_t dal_rtl8367c_cpu_priRemap_get(rtksw_uint32 unit, rtksw_pri_t int_pri, rtksw_pri_t *pNew_pri)
{
    rtksw_api_ret_t retVal;

    /* Check initialization state */
    RTKSW_CHK_INIT_STATE(unit);

    if(NULL == pNew_pri)
        return RT_ERR_NULL_POINTER;

    if (int_pri > RTL8367C_PRIMAX)
        return  RT_ERR_QOS_INT_PRIORITY;

    if ((retVal = rtl8367c_getAsicCputagPriorityRemapping(unit, int_pri, pNew_pri)) != RT_ERR_OK)
        return retVal;

    return RT_ERR_OK;
}

/* Function Name:
 *      dal_rtl8367c_cpu_acceptLength_set
 * Description:
 *      Set CPU accept  length.
 * Input:
 *      unit    - Unit ID
 *      length  - CPU tag length.
 * Output:
 *      None
 * Return:
 *      RT_ERR_OK           - OK
 *      RT_ERR_FAILED       - Failed
 *      RT_ERR_SMI          - SMI access error
 *      RT_ERR_INPUT      - Invalid input.
 * Note:
 *      The API can set CPU accept length.
 */
rtksw_api_ret_t dal_rtl8367c_cpu_acceptLength_set(rtksw_uint32 unit, rtksw_cpu_rx_length_t length)
{
    rtksw_api_ret_t retVal;

    /* Check initialization state */
    RTKSW_CHK_INIT_STATE(unit);

    if (length >= CPU_RX_END)
        return RT_ERR_INPUT;

    if ((retVal = rtl8367c_setAsicCputagRxMinLength(unit, length)) != RT_ERR_OK)
        return retVal;

    return RT_ERR_OK;
}

/* Function Name:
 *      dal_rtl8367c_cpu_acceptLength_get
 * Description:
 *      Get CPU accept length.
 * Input:
 *      unit    - Unit ID
 * Output:
 *      pLength - CPU tag length.
 * Return:
 *      RT_ERR_OK           - OK
 *      RT_ERR_FAILED       - Failed
 *      RT_ERR_SMI          - SMI access error
 *      RT_ERR_INPUT      - Invalid input.
 * Note:
 *      The API can get CPU accept length.
 */
rtksw_api_ret_t dal_rtl8367c_cpu_acceptLength_get(rtksw_uint32 unit, rtksw_cpu_rx_length_t *pLength)
{
    rtksw_api_ret_t retVal;

    /* Check initialization state */
    RTKSW_CHK_INIT_STATE(unit);

    if(NULL == pLength)
        return RT_ERR_NULL_POINTER;

    if ((retVal = rtl8367c_getAsicCputagRxMinLength(unit, pLength)) != RT_ERR_OK)
        return retVal;

    return RT_ERR_OK;
}

