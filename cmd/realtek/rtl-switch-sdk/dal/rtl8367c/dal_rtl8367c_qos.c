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
 * Feature : Here is a list of all functions and variables in QoS module.
 *
 */

#include "../../rtk_switch.h"
#include "../../rtk_error.h"
#include "dal_rtl8367c_qos.h"

#include "rtl8367c_asicdrv.h"
#include "rtl8367c_asicdrv_qos.h"
#include "rtl8367c_asicdrv_fc.h"
#include "rtl8367c_asicdrv_scheduling.h"

#include "../dal_mgmts.h"

/* Function Name:
 *      dal_rtl8367c_qos_init
 * Description:
 *      Configure Qos default settings with queue number assigment to each port.
 * Input:
 *      unit        - Unit ID
 *      queueNum    - Queue number of each port.
 * Output:
 *      None
 * Return:
 *      RT_ERR_OK           - OK
 *      RT_ERR_FAILED       - Failed
 *      RT_ERR_SMI          - SMI access error
 *      RT_ERR_QUEUE_NUM    - Invalid queue number.
 *      RT_ERR_INPUT        - Invalid input parameters.
 * Note:
 *      This API will initialize related Qos setting with queue number assigment.
 *      The queue number is from 1 to 8.
 */
rtksw_api_ret_t dal_rtl8367c_qos_init(rtksw_uint32 unit, rtksw_queue_num_t queueNum)
{
    CONST_T rtksw_uint16 g_prioritytToQid[8][8]= {
            {0, 0,0,0,0,0,0,0},
            {0, 0,0,0,7,7,7,7},
            {0, 0,0,0,1,1,7,7},
            {0, 0,1,1,2,2,7,7},
            {0, 0,1,1,2,3,7,7},
            {0, 0,1,2,3,4,7,7},
            {0, 0,1,2,3,4,5,7},
            {0,1,2,3,4,5,6,7}
    };

    CONST_T rtksw_uint32 g_priorityDecision[8] = {0x01, 0x80,0x04,0x02,0x20,0x40,0x10,0x08};
    CONST_T rtksw_uint32 g_prioritytRemap[8] = {0,1,2,3,4,5,6,7};

    rtksw_api_ret_t retVal;
    rtksw_uint32 qmapidx;
    rtksw_uint32 priority;
    rtksw_uint32 priDec;
    rtksw_uint32 port;
    rtksw_uint32 dscp;

    /* Check initialization state */
    RTKSW_CHK_INIT_STATE(unit);

    if (queueNum <= 0 || queueNum > RTKSW_MAX_NUM_OF_QUEUE)
        return RT_ERR_QUEUE_NUM;

    /*Set Output Queue Number*/
    if (RTKSW_MAX_NUM_OF_QUEUE == queueNum)
        qmapidx = 0;
    else
        qmapidx = queueNum;

    RTKSW_SCAN_ALL_PHY_PORTMASK(unit, port)
    {
        if ((retVal = rtl8367c_setAsicOutputQueueMappingIndex(unit, port, qmapidx)) != RT_ERR_OK)
            return retVal;
    }

    /*Set Priority to Qid*/
    for (priority = 0; priority <= RTKSW_PRIMAX; priority++)
    {
        if ((retVal = rtl8367c_setAsicPriorityToQIDMappingTable(unit, queueNum - 1, priority, g_prioritytToQid[queueNum - 1][priority])) != RT_ERR_OK)
            return retVal;
    }

    /*Set Flow Control Type to Ingress Flow Control*/
    if ((retVal = rtl8367c_setAsicFlowControlSelect(unit, FC_INGRESS)) != RT_ERR_OK)
        return retVal;


    /*Priority Decision Order*/
    for (priDec = 0;priDec < PRIDEC_END;priDec++)
    {
        if ((retVal = rtl8367c_setAsicPriorityDecision(unit, PRIDECTBL_IDX0, priDec, g_priorityDecision[priDec])) != RT_ERR_OK)
            return retVal;
        if ((retVal = rtl8367c_setAsicPriorityDecision(unit, PRIDECTBL_IDX1, priDec, g_priorityDecision[priDec])) != RT_ERR_OK)
            return retVal;
    }

    /*Set Port-based Priority to 0*/
    RTKSW_SCAN_ALL_PHY_PORTMASK(unit, port)
    {
        if ((retVal = rtl8367c_setAsicPriorityPortBased(unit, port, 0)) != RT_ERR_OK)
            return retVal;
    }

    /*Disable 1p Remarking*/
    RTKSW_SCAN_ALL_PHY_PORTMASK(unit, port)
    {
        if ((retVal = rtl8367c_setAsicRemarkingDot1pAbility(unit, port, RTKSW_DISABLED)) != RT_ERR_OK)
            return retVal;
    }

    /*Disable DSCP Remarking*/
    if ((retVal = rtl8367c_setAsicRemarkingDscpAbility(unit, RTKSW_DISABLED)) != RT_ERR_OK)
        return retVal;

    /*Set 1p & DSCP  Priority Remapping & Remarking*/
    for (priority = 0; priority <= RTL8367C_PRIMAX; priority++)
    {
        if ((retVal = rtl8367c_setAsicPriorityDot1qRemapping(unit, priority, g_prioritytRemap[priority])) != RT_ERR_OK)
            return retVal;

        if ((retVal = rtl8367c_setAsicRemarkingDot1pParameter(unit, priority, 0)) != RT_ERR_OK)
            return retVal;

        if ((retVal = rtl8367c_setAsicRemarkingDscpParameter(unit, priority, 0)) != RT_ERR_OK)
            return retVal;
    }

    /*Set DSCP Priority*/
    for (dscp = 0; dscp <= 63; dscp++)
    {
        if ((retVal = rtl8367c_setAsicPriorityDscpBased(unit, dscp, 0)) != RT_ERR_OK)
            return retVal;
    }

    return RT_ERR_OK;
}

/* Function Name:
 *      dal_rtl8367c_qos_priSel_set
 * Description:
 *      Configure the priority order among different priority mechanism.
 * Input:
 *      unit        - Unit ID
 *      index       - Priority decision table index (0~1)
 *      pPriDec     - Priority assign for port, dscp, 802.1p, cvlan, svlan, acl based priority decision.
 * Output:
 *      None
 * Return:
 *      RT_ERR_OK                   - OK
 *      RT_ERR_FAILED               - Failed
 *      RT_ERR_SMI                  - SMI access error
 *      RT_ERR_QOS_SEL_PRI_SOURCE   - Invalid priority decision source parameter.
 * Note:
 *      ASIC will follow user priority setting of mechanisms to select mapped queue priority for receiving frame.
 *      If two priority mechanisms are the same, the ASIC will chose the highest priority from mechanisms to
 *      assign queue priority to receiving frame.
 *      The priority sources are:
 *      - PRIDEC_PORT
 *      - PRIDEC_ACL
 *      - PRIDEC_DSCP
 *      - PRIDEC_1Q
 *      - PRIDEC_1AD
 *      - PRIDEC_CVLAN
 *      - PRIDEC_DA
 *      - PRIDEC_SA
 */
rtksw_api_ret_t dal_rtl8367c_qos_priSel_set(rtksw_uint32 unit, rtksw_qos_priDecTbl_t index, rtksw_priority_select_t *pPriDec)
{
    rtksw_api_ret_t retVal;
    rtksw_uint32 port_pow;
    rtksw_uint32 dot1q_pow;
    rtksw_uint32 dscp_pow;
    rtksw_uint32 acl_pow;
    rtksw_uint32 svlan_pow;
    rtksw_uint32 cvlan_pow;
    rtksw_uint32 smac_pow;
    rtksw_uint32 dmac_pow;
    rtksw_uint32 i;

    /* Check initialization state */
    RTKSW_CHK_INIT_STATE(unit);

    if (index < 0 || index >= PRIDECTBL_END)
        return RT_ERR_ENTRY_INDEX;

    if (pPriDec->port_pri >= 8 || pPriDec->dot1q_pri >= 8 || pPriDec->acl_pri >= 8 || pPriDec->dscp_pri >= 8 ||
       pPriDec->cvlan_pri >= 8 || pPriDec->svlan_pri >= 8 || pPriDec->dmac_pri >= 8 || pPriDec->smac_pri >= 8)
        return RT_ERR_QOS_SEL_PRI_SOURCE;

    port_pow = 1;
    for (i = pPriDec->port_pri; i > 0; i--)
        port_pow = (port_pow)*2;

    dot1q_pow = 1;
    for (i = pPriDec->dot1q_pri; i > 0; i--)
        dot1q_pow = (dot1q_pow)*2;

    acl_pow = 1;
    for (i = pPriDec->acl_pri; i > 0; i--)
        acl_pow = (acl_pow)*2;

    dscp_pow = 1;
    for (i = pPriDec->dscp_pri; i > 0; i--)
        dscp_pow = (dscp_pow)*2;

    svlan_pow = 1;
    for (i = pPriDec->svlan_pri; i > 0; i--)
        svlan_pow = (svlan_pow)*2;

    cvlan_pow = 1;
    for (i = pPriDec->cvlan_pri; i > 0; i--)
        cvlan_pow = (cvlan_pow)*2;

    dmac_pow = 1;
    for (i = pPriDec->dmac_pri; i > 0; i--)
        dmac_pow = (dmac_pow)*2;

    smac_pow = 1;
    for (i = pPriDec->smac_pri; i > 0; i--)
        smac_pow = (smac_pow)*2;

    if ((retVal = rtl8367c_setAsicPriorityDecision(unit, index, PRIDEC_PORT, port_pow)) != RT_ERR_OK)
        return retVal;

    if ((retVal = rtl8367c_setAsicPriorityDecision(unit, index, PRIDEC_ACL, acl_pow)) != RT_ERR_OK)
        return retVal;

    if ((retVal = rtl8367c_setAsicPriorityDecision(unit, index, PRIDEC_DSCP, dscp_pow)) != RT_ERR_OK)
        return retVal;

    if ((retVal = rtl8367c_setAsicPriorityDecision(unit, index, PRIDEC_1Q, dot1q_pow)) != RT_ERR_OK)
        return retVal;

    if ((retVal = rtl8367c_setAsicPriorityDecision(unit, index, PRIDEC_1AD, svlan_pow)) != RT_ERR_OK)
        return retVal;

    if ((retVal = rtl8367c_setAsicPriorityDecision(unit, index, PRIDEC_CVLAN, cvlan_pow)) != RT_ERR_OK)
        return retVal;

    if ((retVal = rtl8367c_setAsicPriorityDecision(unit, index, PRIDEC_DA, dmac_pow)) != RT_ERR_OK)
        return retVal;

    if ((retVal = rtl8367c_setAsicPriorityDecision(unit, index, PRIDEC_SA, smac_pow)) != RT_ERR_OK)
        return retVal;

    return RT_ERR_OK;
}

/* Function Name:
 *      dal_rtl8367c_qos_priSel_get
 * Description:
 *      Get the priority order configuration among different priority mechanism.
 * Input:
 *      unit        - Unit ID
 *      index       - Priority decision table index (0~1)
 * Output:
 *      pPriDec - Priority assign for port, dscp, 802.1p, cvlan, svlan, acl based priority decision .
 * Return:
 *      RT_ERR_OK           - OK
 *      RT_ERR_FAILED       - Failed
 *      RT_ERR_SMI          - SMI access error
 * Note:
 *      ASIC will follow user priority setting of mechanisms to select mapped queue priority for receiving frame.
 *      If two priority mechanisms are the same, the ASIC will chose the highest priority from mechanisms to
 *      assign queue priority to receiving frame.
 *      The priority sources are:
 *      - PRIDEC_PORT,
 *      - PRIDEC_ACL,
 *      - PRIDEC_DSCP,
 *      - PRIDEC_1Q,
 *      - PRIDEC_1AD,
 *      - PRIDEC_CVLAN,
 *      - PRIDEC_DA,
 *      - PRIDEC_SA,
 */
rtksw_api_ret_t dal_rtl8367c_qos_priSel_get(rtksw_uint32 unit, rtksw_qos_priDecTbl_t index, rtksw_priority_select_t *pPriDec)
{

    rtksw_api_ret_t retVal;
    rtksw_int32 i;
    rtksw_uint32 port_pow;
    rtksw_uint32 dot1q_pow;
    rtksw_uint32 dscp_pow;
    rtksw_uint32 acl_pow;
    rtksw_uint32 svlan_pow;
    rtksw_uint32 cvlan_pow;
    rtksw_uint32 smac_pow;
    rtksw_uint32 dmac_pow;

    /* Check initialization state */
    RTKSW_CHK_INIT_STATE(unit);

    if (index < 0 || index >= PRIDECTBL_END)
        return RT_ERR_ENTRY_INDEX;

    if ((retVal = rtl8367c_getAsicPriorityDecision(unit, index, PRIDEC_PORT, &port_pow)) != RT_ERR_OK)
        return retVal;

    if ((retVal = rtl8367c_getAsicPriorityDecision(unit, index, PRIDEC_ACL, &acl_pow)) != RT_ERR_OK)
        return retVal;

    if ((retVal = rtl8367c_getAsicPriorityDecision(unit, index, PRIDEC_DSCP, &dscp_pow)) != RT_ERR_OK)
        return retVal;

    if ((retVal = rtl8367c_getAsicPriorityDecision(unit, index, PRIDEC_1Q, &dot1q_pow)) != RT_ERR_OK)
        return retVal;

    if ((retVal = rtl8367c_getAsicPriorityDecision(unit, index, PRIDEC_1AD, &svlan_pow)) != RT_ERR_OK)
        return retVal;

    if ((retVal = rtl8367c_getAsicPriorityDecision(unit, index, PRIDEC_CVLAN, &cvlan_pow)) != RT_ERR_OK)
        return retVal;

    if ((retVal = rtl8367c_getAsicPriorityDecision(unit, index, PRIDEC_DA, &dmac_pow)) != RT_ERR_OK)
        return retVal;

    if ((retVal = rtl8367c_getAsicPriorityDecision(unit, index, PRIDEC_SA, &smac_pow)) != RT_ERR_OK)
        return retVal;

    for (i = 7; i >= 0; i--)
    {
        if (port_pow & (1 << i))
        {
            pPriDec->port_pri = i;
            break;
        }
    }

    for (i = 7; i >= 0; i--)
    {
        if (dot1q_pow & (1 << i))
        {
            pPriDec->dot1q_pri = i;
            break;
        }
    }

    for (i = 7; i >= 0; i--)
    {
        if (acl_pow & (1 << i))
        {
            pPriDec->acl_pri = i;
            break;
        }
    }

    for (i = 7; i >= 0; i--)
    {
        if (dscp_pow & (1 << i))
        {
            pPriDec->dscp_pri = i;
            break;
        }
    }

    for (i = 7; i >= 0; i--)
    {
        if (svlan_pow & (1 << i))
        {
            pPriDec->svlan_pri = i;
            break;
        }
    }

    for (i = 7;i  >= 0; i--)
    {
        if (cvlan_pow & (1 << i))
        {
            pPriDec->cvlan_pri = i;
            break;
        }
    }

    for (i = 7; i >= 0; i--)
    {
        if (dmac_pow&(1<<i))
        {
            pPriDec->dmac_pri = i;
            break;
        }
    }

    for (i = 7; i >= 0; i--)
    {
        if (smac_pow & (1 << i))
        {
            pPriDec->smac_pri = i;
            break;
        }
    }

    return RT_ERR_OK;
}

/* Function Name:
 *      dal_rtl8367c_qos_1pPriRemap_set
 * Description:
 *      Configure 1Q priorities mapping to internal absolute priority.
 * Input:
 *      unit        - Unit ID
 *      dot1p_pri   - 802.1p priority value.
 *      int_pri     - internal priority value.
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
 *      Priority of 802.1Q assignment for internal asic priority, and it is used for queue usage and packet scheduling.
 */
rtksw_api_ret_t dal_rtl8367c_qos_1pPriRemap_set(rtksw_uint32 unit, rtksw_pri_t dot1p_pri, rtksw_pri_t int_pri)
{
    rtksw_api_ret_t retVal;

    /* Check initialization state */
    RTKSW_CHK_INIT_STATE(unit);

    if (dot1p_pri > RTL8367C_PRIMAX || int_pri > RTL8367C_PRIMAX)
        return  RT_ERR_VLAN_PRIORITY;

    if ((retVal = rtl8367c_setAsicPriorityDot1qRemapping(unit, dot1p_pri, int_pri)) != RT_ERR_OK)
        return retVal;

    return RT_ERR_OK;
}

/* Function Name:
 *      dal_rtl8367c_qos_1pPriRemap_get
 * Description:
 *      Get 1Q priorities mapping to internal absolute priority.
 * Input:
 *      unit        - Unit ID
 *      dot1p_pri   - 802.1p priority value .
 * Output:
 *      pInt_pri - internal priority value.
 * Return:
 *      RT_ERR_OK               - OK
 *      RT_ERR_FAILED           - Failed
 *      RT_ERR_SMI              - SMI access error
 *      RT_ERR_VLAN_PRIORITY    - Invalid priority.
 *      RT_ERR_QOS_INT_PRIORITY - Invalid priority.
 * Note:
 *      Priority of 802.1Q assigment for internal asic priority, and it is uesed for queue usage and packet scheduling.
 */
rtksw_api_ret_t dal_rtl8367c_qos_1pPriRemap_get(rtksw_uint32 unit, rtksw_pri_t dot1p_pri, rtksw_pri_t *pInt_pri)
{
    rtksw_api_ret_t retVal;

    /* Check initialization state */
    RTKSW_CHK_INIT_STATE(unit);

    if (dot1p_pri > RTL8367C_PRIMAX)
        return  RT_ERR_QOS_INT_PRIORITY;

    if ((retVal = rtl8367c_getAsicPriorityDot1qRemapping(unit, dot1p_pri, pInt_pri)) != RT_ERR_OK)
        return retVal;

    return RT_ERR_OK;
}

/* Function Name:
 *      dal_rtl8367c_qos_dscpPriRemap_set
 * Description:
 *      Map dscp value to internal priority.
 * Input:
 *      unit        - Unit ID
 *      dscp        - Dscp value of receiving frame
 *      int_pri     - internal priority value .
 * Output:
 *      None
 * Return:
 *      RT_ERR_OK               - OK
 *      RT_ERR_FAILED           - Failed
 *      RT_ERR_SMI              - SMI access error
 *      RT_ERR_INPUT            - Invalid input parameters.
 *      RT_ERR_QOS_DSCP_VALUE   - Invalid DSCP value.
 *      RT_ERR_QOS_INT_PRIORITY - Invalid priority.
 * Note:
 *      The Differentiated Service Code Point is a selector for router's per-hop behaviors. As a selector, there is no implication that a numerically
 *      greater DSCP implies a better network service. As can be seen, the DSCP totally overlaps the old precedence field of TOS. So if values of
 *      DSCP are carefully chosen then backward compatibility can be achieved.
 */
rtksw_api_ret_t dal_rtl8367c_qos_dscpPriRemap_set(rtksw_uint32 unit, rtksw_dscp_t dscp, rtksw_pri_t int_pri)
{
    rtksw_api_ret_t retVal;

    /* Check initialization state */
    RTKSW_CHK_INIT_STATE(unit);

    if (int_pri > RTL8367C_PRIMAX )
        return RT_ERR_QOS_INT_PRIORITY;

    if (dscp > RTL8367C_DSCPMAX)
        return RT_ERR_QOS_DSCP_VALUE;

    if ((retVal = rtl8367c_setAsicPriorityDscpBased(unit, dscp, int_pri)) != RT_ERR_OK)
        return retVal;

    return RT_ERR_OK;
}

/* Function Name:
 *      dal_rtl8367c_qos_dscpPriRemap_get
 * Description:
 *      Get dscp value to internal priority.
 * Input:
 *      unit        - Unit ID
 *      dscp        - Dscp value of receiving frame
 * Output:
 *      pInt_pri - internal priority value.
 * Return:
 *      RT_ERR_OK               - OK
 *      RT_ERR_FAILED           - Failed
 *      RT_ERR_SMI              - SMI access error
 *      RT_ERR_QOS_DSCP_VALUE   - Invalid DSCP value.
 * Note:
 *      The Differentiated Service Code Point is a selector for router's per-hop behaviors. As a selector, there is no implication that a numerically
 *      greater DSCP implies a better network service. As can be seen, the DSCP totally overlaps the old precedence field of TOS. So if values of
 *      DSCP are carefully chosen then backward compatibility can be achieved.
 */
rtksw_api_ret_t dal_rtl8367c_qos_dscpPriRemap_get(rtksw_uint32 unit, rtksw_dscp_t dscp, rtksw_pri_t *pInt_pri)
{
    rtksw_api_ret_t retVal;

    /* Check initialization state */
    RTKSW_CHK_INIT_STATE(unit);

    if (dscp > RTL8367C_DSCPMAX)
        return RT_ERR_QOS_DSCP_VALUE;

    if ((retVal = rtl8367c_getAsicPriorityDscpBased(unit, dscp, pInt_pri)) != RT_ERR_OK)
        return retVal;

    return RT_ERR_OK;
}

/* Function Name:
 *      dal_rtl8367c_qos_portPri_set
 * Description:
 *      Configure priority usage to each port.
 * Input:
 *      unit        - Unit ID
 *      port        - Port id.
 *      int_pri     - internal priority value.
 * Output:
 *      None
 * Return:
 *      RT_ERR_OK               - OK
 *      RT_ERR_FAILED           - Failed
 *      RT_ERR_SMI              - SMI access error
 *      RT_ERR_PORT_ID          - Invalid port number.
 *      RT_ERR_QOS_SEL_PORT_PRI - Invalid port priority.
 *      RT_ERR_QOS_INT_PRIORITY - Invalid priority.
 * Note:
 *      The API can set priority of port assignments for queue usage and packet scheduling.
 */
rtksw_api_ret_t dal_rtl8367c_qos_portPri_set(rtksw_uint32 unit, rtksw_port_t port, rtksw_pri_t int_pri)
{
    rtksw_api_ret_t retVal;

    /* Check initialization state */
    RTKSW_CHK_INIT_STATE(unit);

    /* Check Port Valid */
    RTKSW_CHK_PORT_VALID(unit, port);

    if (int_pri > RTL8367C_PRIMAX )
        return RT_ERR_QOS_INT_PRIORITY;

    if ((retVal = rtl8367c_setAsicPriorityPortBased(unit, rtksw_switch_port_L2P_get(unit, port), int_pri)) != RT_ERR_OK)
        return retVal;

    return RT_ERR_OK;
}

/* Function Name:
 *      dal_rtl8367c_qos_portPri_get
 * Description:
 *      Get priority usage to each port.
 * Input:
 *      unit        - Unit ID
 *      port        - Port id.
 * Output:
 *      pInt_pri - internal priority value.
 * Return:
 *      RT_ERR_OK           - OK
 *      RT_ERR_FAILED       - Failed
 *      RT_ERR_SMI          - SMI access error
 *      RT_ERR_PORT_ID      - Invalid port number.
 *      RT_ERR_INPUT        - Invalid input parameters.
 * Note:
 *      The API can get priority of port assignments for queue usage and packet scheduling.
 */
rtksw_api_ret_t dal_rtl8367c_qos_portPri_get(rtksw_uint32 unit, rtksw_port_t port, rtksw_pri_t *pInt_pri)
{
    rtksw_api_ret_t retVal;

    /* Check initialization state */
    RTKSW_CHK_INIT_STATE(unit);

    /* Check Port Valid */
    RTKSW_CHK_PORT_VALID(unit, port);

    if ((retVal = rtl8367c_getAsicPriorityPortBased(unit, rtksw_switch_port_L2P_get(unit, port), pInt_pri)) != RT_ERR_OK)
        return retVal;


    return RT_ERR_OK;
}

/* Function Name:
 *      dal_rtl8367c_qos_queueNum_set
 * Description:
 *      Set output queue number for each port.
 * Input:
 *      unit        - Unit ID
 *      port        - Port id.
 *      index       - Mapping queue number (1~8)
 * Output:
 *      None
 * Return:
 *      RT_ERR_OK           - OK
 *      RT_ERR_FAILED       - Failed
 *      RT_ERR_SMI          - SMI access error
 *      RT_ERR_PORT_ID      - Invalid port number.
 *      RT_ERR_QUEUE_NUM    - Invalid queue number.
 * Note:
 *      The API can set the output queue number of the specified port. The queue number is from 1 to 8.
 */
rtksw_api_ret_t dal_rtl8367c_qos_queueNum_set(rtksw_uint32 unit, rtksw_port_t port, rtksw_queue_num_t queue_num)
{
    rtksw_api_ret_t retVal;

    /* Check initialization state */
    RTKSW_CHK_INIT_STATE(unit);

    /* Check Port Valid */
    RTKSW_CHK_PORT_VALID(unit, port);

    if ((0 == queue_num) || (queue_num > RTKSW_MAX_NUM_OF_QUEUE))
        return RT_ERR_FAILED;

    if (RTKSW_MAX_NUM_OF_QUEUE == queue_num)
        queue_num = 0;

    if ((retVal = rtl8367c_setAsicOutputQueueMappingIndex(unit, rtksw_switch_port_L2P_get(unit, port), queue_num)) != RT_ERR_OK)
        return retVal;

    return RT_ERR_OK;
}

/* Function Name:
 *      dal_rtl8367c_qos_queueNum_get
 * Description:
 *      Get output queue number.
 * Input:
 *      unit        - Unit ID
 *      port        - Port id.
 * Output:
 *      pQueue_num - Mapping queue number
 * Return:
 *      RT_ERR_OK           - OK
 *      RT_ERR_FAILED       - Failed
 *      RT_ERR_SMI          - SMI access error
 *      RT_ERR_PORT_ID      - Invalid port number.
 * Note:
 *      The API will return the output queue number of the specified port. The queue number is from 1 to 8.
 */
rtksw_api_ret_t dal_rtl8367c_qos_queueNum_get(rtksw_uint32 unit, rtksw_port_t port, rtksw_queue_num_t *pQueue_num)
{
    rtksw_api_ret_t retVal;
    rtksw_uint32 qidx;

    /* Check initialization state */
    RTKSW_CHK_INIT_STATE(unit);

    /* Check Port Valid */
    RTKSW_CHK_PORT_VALID(unit, port);

    if ((retVal = rtl8367c_getAsicOutputQueueMappingIndex(unit, rtksw_switch_port_L2P_get(unit, port), &qidx)) != RT_ERR_OK)
        return retVal;

    if (0 == qidx)
        *pQueue_num = 8;
    else
        *pQueue_num = qidx;

    return RT_ERR_OK;
}

/* Function Name:
 *      dal_rtl8367c_qos_priMap_set
 * Description:
 *      Set output queue number for each port.
 * Input:
 *      unit        - Unit ID
 *      queue_num   - Queue number usage.
 *      pPri2qid    - Priority mapping to queue ID.
 * Output:
 *      None
 * Return:
 *      RT_ERR_OK               - OK
 *      RT_ERR_FAILED           - Failed
 *      RT_ERR_SMI              - SMI access error
 *      RT_ERR_INPUT            - Invalid input parameters.
 *      RT_ERR_QUEUE_NUM        - Invalid queue number.
 *      RT_ERR_QUEUE_ID         - Invalid queue id.
 *      RT_ERR_PORT_ID          - Invalid port number.
 *      RT_ERR_QOS_INT_PRIORITY - Invalid priority.
 * Note:
 *      ASIC supports priority mapping to queue with different queue number from 1 to 8.
 *      For different queue numbers usage, ASIC supports different internal available queue IDs.
 */
rtksw_api_ret_t dal_rtl8367c_qos_priMap_set(rtksw_uint32 unit, rtksw_queue_num_t queue_num, rtksw_qos_pri2queue_t *pPri2qid)
{
    rtksw_api_ret_t retVal;
    rtksw_uint32 pri;

    /* Check initialization state */
    RTKSW_CHK_INIT_STATE(unit);

    if ((0 == queue_num) || (queue_num > RTKSW_MAX_NUM_OF_QUEUE))
        return RT_ERR_QUEUE_NUM;

    for (pri = 0; pri <= RTKSW_PRIMAX; pri++)
    {
        if (pPri2qid->pri2queue[pri] > RTKSW_QIDMAX)
            return RT_ERR_QUEUE_ID;

        if ((retVal = rtl8367c_setAsicPriorityToQIDMappingTable(unit, queue_num - 1, pri, pPri2qid->pri2queue[pri])) != RT_ERR_OK)
            return retVal;
    }

    return RT_ERR_OK;
}

/* Function Name:
 *      dal_rtl8367c_qos_priMap_get
 * Description:
 *      Get priority to queue ID mapping table parameters.
 * Input:
 *      unit        - Unit ID
 *      queue_num   - Queue number usage.
 * Output:
 *      pPri2qid - Priority mapping to queue ID.
 * Return:
 *      RT_ERR_OK           - OK
 *      RT_ERR_FAILED       - Failed
 *      RT_ERR_SMI          - SMI access error
 *      RT_ERR_INPUT        - Invalid input parameters.
 *      RT_ERR_QUEUE_NUM    - Invalid queue number.
 * Note:
 *      The API can return the mapping queue id of the specified priority and queue number.
 *      The queue number is from 1 to 8.
 */
rtksw_api_ret_t dal_rtl8367c_qos_priMap_get(rtksw_uint32 unit, rtksw_queue_num_t queue_num, rtksw_qos_pri2queue_t *pPri2qid)
{
    rtksw_api_ret_t retVal;
    rtksw_uint32 pri;

    /* Check initialization state */
    RTKSW_CHK_INIT_STATE(unit);

    if ((0 == queue_num) || (queue_num > RTKSW_MAX_NUM_OF_QUEUE))
        return RT_ERR_QUEUE_NUM;

    for (pri = 0; pri <= RTKSW_PRIMAX; pri++)
    {
        if ((retVal = rtl8367c_getAsicPriorityToQIDMappingTable(unit, queue_num-1, pri, &pPri2qid->pri2queue[pri])) != RT_ERR_OK)
            return retVal;
    }

    return RT_ERR_OK;
}

/* Function Name:
 *      dal_rtl8367c_qos_schedulingQueue_set
 * Description:
 *      Set weight and type of queues in dedicated port.
 * Input:
 *      unit        - Unit ID
 *      port        - Port id.
 *      pQweights   - The array of weights for WRR/WFQ queue (0 for STRICT_PRIORITY queue).
 * Output:
 *      None
 * Return:
 *      RT_ERR_OK               - OK
 *      RT_ERR_FAILED           - Failed
 *      RT_ERR_SMI              - SMI access error
 *      RT_ERR_PORT_ID          - Invalid port number.
 *      RT_ERR_QOS_QUEUE_WEIGHT - Invalid queue weight.
 * Note:
 *      The API can set weight and type, strict priority or weight fair queue (WFQ) for
 *      dedicated port for using queues. If queue id is not included in queue usage,
 *      then its type and weight setting in dummy for setting. There are priorities
 *      as queue id in strict queues. It means strict queue id 5 carrying higher priority
 *      than strict queue id 4. The WFQ queue weight is from 1 to 127, and weight 0 is
 *      for strict priority queue type.
 */
rtksw_api_ret_t dal_rtl8367c_qos_schedulingQueue_set(rtksw_uint32 unit, rtksw_port_t port, rtksw_qos_queue_weights_t *pQweights)
{
    rtksw_api_ret_t retVal;
    rtksw_uint32 qid;

    /* Check initialization state */
    RTKSW_CHK_INIT_STATE(unit);

    /* Check Port Valid */
    RTKSW_CHK_PORT_VALID(unit, port);

    for (qid = 0; qid < RTL8367C_QUEUENO; qid ++)
    {

        if (pQweights->weights[qid] > QOS_WEIGHT_MAX)
            return RT_ERR_QOS_QUEUE_WEIGHT;

        if (0 == pQweights->weights[qid])
        {
            if ((retVal = rtl8367c_setAsicQueueType(unit, rtksw_switch_port_L2P_get(unit, port), qid, QTYPE_STRICT)) != RT_ERR_OK)
                return retVal;
        }
        else
        {
            if ((retVal = rtl8367c_setAsicQueueType(unit, rtksw_switch_port_L2P_get(unit, port), qid, QTYPE_WFQ)) != RT_ERR_OK)
                return retVal;

            if ((retVal = rtl8367c_setAsicWFQWeight(unit, rtksw_switch_port_L2P_get(unit, port),qid, pQweights->weights[qid])) != RT_ERR_OK)
                return retVal;
        }
    }

    return RT_ERR_OK;
}

/* Function Name:
 *      dal_rtl8367c_qos_schedulingQueue_get
 * Description:
 *      Get weight and type of queues in dedicated port.
 * Input:
 *      unit        - Unit ID
 *      port        - Port id.
 * Output:
 *      pQweights - The array of weights for WRR/WFQ queue (0 for STRICT_PRIORITY queue).
 * Return:
 *      RT_ERR_OK           - OK
 *      RT_ERR_FAILED       - Failed
 *      RT_ERR_SMI          - SMI access error
 *      RT_ERR_INPUT        - Invalid input parameters.
 *      RT_ERR_PORT_ID      - Invalid port number.
 * Note:
 *      The API can get weight and type, strict priority or weight fair queue (WFQ) for dedicated port for using queues.
 *      The WFQ queue weight is from 1 to 127, and weight 0 is for strict priority queue type.
 */
rtksw_api_ret_t dal_rtl8367c_qos_schedulingQueue_get(rtksw_uint32 unit, rtksw_port_t port, rtksw_qos_queue_weights_t *pQweights)
{
    rtksw_api_ret_t retVal;
    rtksw_uint32 qid,qtype,qweight;

    /* Check initialization state */
    RTKSW_CHK_INIT_STATE(unit);

    /* Check Port Valid */
    RTKSW_CHK_PORT_VALID(unit, port);

    for (qid = 0; qid < RTL8367C_QUEUENO; qid++)
    {
        if ((retVal = rtl8367c_getAsicQueueType(unit, rtksw_switch_port_L2P_get(unit, port), qid, &qtype)) != RT_ERR_OK)
            return retVal;

        if (QTYPE_STRICT == qtype)
        {
            pQweights->weights[qid] = 0;
        }
        else if (QTYPE_WFQ == qtype)
        {
            if ((retVal = rtl8367c_getAsicWFQWeight(unit, rtksw_switch_port_L2P_get(unit, port), qid, &qweight)) != RT_ERR_OK)
                return retVal;
            pQweights->weights[qid] = qweight;
        }
    }
    return RT_ERR_OK;
}

/* Function Name:
 *      dal_rtl8367c_qos_1pRemarkEnable_set
 * Description:
 *      Set 1p Remarking state
 * Input:
 *      unit        - Unit ID
 *      port        - Port id.
 *      enable      - State of per-port 1p Remarking
 * Output:
 *      None
 * Return:
 *      RT_ERR_OK           - OK
 *      RT_ERR_FAILED       - Failed
 *      RT_ERR_SMI          - SMI access error
 *      RT_ERR_PORT_ID      - Invalid port number.
 *      RT_ERR_ENABLE       - Invalid enable parameter.
 * Note:
 *      The API can enable or disable 802.1p remarking ability for whole system.
 *      The status of 802.1p remark:
 *      - RTKSW_DISABLED
 *      - RTKSW_ENABLED
 */
rtksw_api_ret_t dal_rtl8367c_qos_1pRemarkEnable_set(rtksw_uint32 unit, rtksw_port_t port, rtksw_enable_t enable)
{
    rtksw_api_ret_t retVal;

    /* Check initialization state */
    RTKSW_CHK_INIT_STATE(unit);

    /* Check Port Valid */
    RTKSW_CHK_PORT_VALID(unit, port);

    if (enable >= RTKSW_ENABLE_END)
        return RT_ERR_INPUT;

    if ((retVal = rtl8367c_setAsicRemarkingDot1pAbility(unit, rtksw_switch_port_L2P_get(unit, port), enable)) != RT_ERR_OK)
        return retVal;

    return RT_ERR_OK;
}

/* Function Name:
 *      dal_rtl8367c_qos_1pRemarkEnable_get
 * Description:
 *      Get 802.1p remarking ability.
 * Input:
 *      unit        - Unit ID
 *      port        - Port id.
 * Output:
 *      pEnable - Status of 802.1p remark.
 * Return:
 *      RT_ERR_OK           - OK
 *      RT_ERR_FAILED       - Failed
 *      RT_ERR_SMI          - SMI access error
 *      RT_ERR_PORT_ID      - Invalid port number.
 * Note:
 *      The API can get 802.1p remarking ability.
 *      The status of 802.1p remark:
 *      - RTKSW_DISABLED
 *      - RTKSW_ENABLED
 */
rtksw_api_ret_t dal_rtl8367c_qos_1pRemarkEnable_get(rtksw_uint32 unit, rtksw_port_t port, rtksw_enable_t *pEnable)
{
    rtksw_api_ret_t retVal;

    /* Check initialization state */
    RTKSW_CHK_INIT_STATE(unit);

    /* Check Port Valid */
    RTKSW_CHK_PORT_VALID(unit, port);

    if ((retVal = rtl8367c_getAsicRemarkingDot1pAbility(unit, rtksw_switch_port_L2P_get(unit, port), pEnable)) != RT_ERR_OK)
        return retVal;

    return RT_ERR_OK;
}

/* Function Name:
 *      dal_rtl8367c_qos_1pRemark_set
 * Description:
 *      Set 802.1p remarking parameter.
 * Input:
 *      unit        - Unit ID
 *      int_pri     - Internal priority value.
 *      dot1p_pri   - 802.1p priority value.
 * Output:
 *      None
 * Return:
 *      RT_ERR_OK               - OK
 *      RT_ERR_FAILED           - Failed
 *      RT_ERR_SMI              - SMI access error
 *      RT_ERR_VLAN_PRIORITY    - Invalid 1p priority.
 *      RT_ERR_QOS_INT_PRIORITY - Invalid priority.
 * Note:
 *      The API can set 802.1p parameters source priority and new priority.
 */
rtksw_api_ret_t dal_rtl8367c_qos_1pRemark_set(rtksw_uint32 unit, rtksw_pri_t int_pri, rtksw_pri_t dot1p_pri)
{
    rtksw_api_ret_t retVal;

    /* Check initialization state */
    RTKSW_CHK_INIT_STATE(unit);

    if (int_pri > RTL8367C_PRIMAX )
        return RT_ERR_QOS_INT_PRIORITY;

    if (dot1p_pri > RTL8367C_PRIMAX)
        return RT_ERR_VLAN_PRIORITY;

    if ((retVal = rtl8367c_setAsicRemarkingDot1pParameter(unit, int_pri, dot1p_pri)) != RT_ERR_OK)
        return retVal;

    return RT_ERR_OK;
}

/* Function Name:
 *      dal_rtl8367c_qos_1pRemark_get
 * Description:
 *      Get 802.1p remarking parameter.
 * Input:
 *      unit        - Unit ID
 *      int_pri     - Internal priority value.
 * Output:
 *      pDot1p_pri - 802.1p priority value.
 * Return:
 *      RT_ERR_OK               - OK
 *      RT_ERR_FAILED           - Failed
 *      RT_ERR_SMI              - SMI access error
 *      RT_ERR_QOS_INT_PRIORITY - Invalid priority.
 * Note:
 *      The API can get 802.1p remarking parameters. It would return new priority of ingress priority.
 */
rtksw_api_ret_t dal_rtl8367c_qos_1pRemark_get(rtksw_uint32 unit, rtksw_pri_t int_pri, rtksw_pri_t *pDot1p_pri)
{
    rtksw_api_ret_t retVal;

    /* Check initialization state */
    RTKSW_CHK_INIT_STATE(unit);

    if (int_pri > RTL8367C_PRIMAX )
        return RT_ERR_QOS_INT_PRIORITY;

    if ((retVal = rtl8367c_getAsicRemarkingDot1pParameter(unit, int_pri, pDot1p_pri)) != RT_ERR_OK)
        return retVal;

    return RT_ERR_OK;
}

/* Function Name:
 *      dal_rtl8367c_qos_1pRemarkSrcSel_set
 * Description:
 *      Set remarking source of 802.1p remarking.
 * Input:
 *      unit        - Unit ID
 *      type        - remarking source
 * Output:
 *      None
 * Return:
 *      RT_ERR_OK
 *      RT_ERR_FAILED
 *      RT_ERR_NOT_INIT         - The module is not initial
 *      RT_ERR_PORT_ID  - invalid port id
 *      RT_ERR_INPUT            - invalid input parameter

 * Note:
 *      The API can configure 802.1p remark functionality to map original 802.1p value or internal
 *      priority to TX DSCP value.
 */
rtksw_api_ret_t dal_rtl8367c_qos_1pRemarkSrcSel_set(rtksw_uint32 unit, rtksw_qos_1pRmkSrc_t type)
{
    rtksw_api_ret_t retVal;

    /* Check initialization state */
    RTKSW_CHK_INIT_STATE(unit);

    if (type >= DOT1P_RMK_SRC_END )
        return RT_ERR_QOS_INT_PRIORITY;

    if ((retVal = rtl8367c_setAsicRemarkingDot1pSrc(unit, type)) != RT_ERR_OK)
        return retVal;

    return RT_ERR_OK;
}

/* Function Name:
 *      dal_rtl8367c_qos_1pRemarkSrcSel_get
 * Description:
 *      Get remarking source of 802.1p remarking.
 * Input:
 *      unit        - Unit ID
 * Output:
 *      pType      - remarking source
 * Return:
 *      RT_ERR_OK
 *      RT_ERR_FAILED
 *      RT_ERR_NOT_INIT         - The module is not initial
 *      RT_ERR_PORT_ID          - invalid port id
 *      RT_ERR_INPUT            - invalid input parameter
 *      RT_ERR_NULL_POINTER     - input parameter may be null pointer

 * Note:
 *      None
 */
rtksw_api_ret_t dal_rtl8367c_qos_1pRemarkSrcSel_get(rtksw_uint32 unit, rtksw_qos_1pRmkSrc_t *pType)
{
    rtksw_api_ret_t retVal;

    /* Check initialization state */
    RTKSW_CHK_INIT_STATE(unit);

    if ((retVal = rtl8367c_getAsicRemarkingDot1pSrc(unit, pType)) != RT_ERR_OK)
        return retVal;

    return RT_ERR_OK;
}

/* Function Name:
 *      dal_rtl8367c_qos_dscpRemarkEnable_set
 * Description:
 *      Set DSCP remarking ability.
 * Input:
 *      unit        - Unit ID
 *      port        - Port id.
 *      enable      - status of DSCP remark.
 * Output:
 *      None
 * Return:
 *      RT_ERR_OK               - OK
 *      RT_ERR_FAILED           - Failed
 *      RT_ERR_SMI              - SMI access error
 *      RT_ERR_PORT_ID          - Invalid port number.
 *      RT_ERR_QOS_INT_PRIORITY - Invalid priority.
 *      RT_ERR_ENABLE           - Invalid enable parameter.
 * Note:
 *      The API can enable or disable DSCP remarking ability for whole system.
 *      The status of DSCP remark:
 *      - RTKSW_DISABLED
 *      - RTKSW_ENABLED
 */
rtksw_api_ret_t dal_rtl8367c_qos_dscpRemarkEnable_set(rtksw_uint32 unit, rtksw_port_t port, rtksw_enable_t enable)
{
    rtksw_api_ret_t retVal;

    /* Check initialization state */
    RTKSW_CHK_INIT_STATE(unit);

    /*for whole system function, the port value should be 0xFF*/
    if (port != RTKSW_WHOLE_SYSTEM)
        return RT_ERR_PORT_ID;

    if (enable >= RTKSW_ENABLE_END)
        return RT_ERR_INPUT;

    if ((retVal = rtl8367c_setAsicRemarkingDscpAbility(unit, enable)) != RT_ERR_OK)
        return retVal;

    return RT_ERR_OK;
}

/* Function Name:
 *      dal_rtl8367c_qos_dscpRemarkEnable_get
 * Description:
 *      Get DSCP remarking ability.
 * Input:
 *      unit        - Unit ID
 *      port        - Port id.
 * Output:
 *      pEnable - status of DSCP remarking.
 * Return:
 *      RT_ERR_OK           - OK
 *      RT_ERR_FAILED       - Failed
 *      RT_ERR_SMI          - SMI access error
 *      RT_ERR_PORT_ID      - Invalid port number.
 * Note:
 *      The API can get DSCP remarking ability.
 *      The status of DSCP remark:
 *      - RTKSW_DISABLED
 *      - RTKSW_ENABLED
 */
rtksw_api_ret_t dal_rtl8367c_qos_dscpRemarkEnable_get(rtksw_uint32 unit, rtksw_port_t port, rtksw_enable_t *pEnable)
{
    rtksw_api_ret_t retVal;

    /* Check initialization state */
    RTKSW_CHK_INIT_STATE(unit);

    /*for whole system function, the port value should be 0xFF*/
    if (port != RTKSW_WHOLE_SYSTEM)
        return RT_ERR_PORT_ID;

    if ((retVal = rtl8367c_getAsicRemarkingDscpAbility(unit, pEnable)) != RT_ERR_OK)
        return retVal;

    return RT_ERR_OK;
}

/* Function Name:
 *      dal_rtl8367c_qos_dscpRemark_set
 * Description:
 *      Set DSCP remarking parameter.
 * Input:
 *      unit        - Unit ID
 *      int_pri     - Internal priority value.
 *      dscp        - DSCP value.
 * Output:
 *      None
 * Return:
 *      RT_ERR_OK               - OK
 *      RT_ERR_FAILED           - Failed
 *      RT_ERR_SMI              - SMI access error
 *      RT_ERR_QOS_INT_PRIORITY - Invalid priority.
 *      RT_ERR_QOS_DSCP_VALUE   - Invalid DSCP value.
 * Note:
 *      The API can set DSCP value and mapping priority.
 */
rtksw_api_ret_t dal_rtl8367c_qos_dscpRemark_set(rtksw_uint32 unit, rtksw_pri_t int_pri, rtksw_dscp_t dscp)
{
    rtksw_api_ret_t retVal;

    /* Check initialization state */
    RTKSW_CHK_INIT_STATE(unit);

    if (int_pri > RTKSW_PRIMAX )
        return RT_ERR_QOS_INT_PRIORITY;

    if (dscp > RTKSW_DSCPMAX)
        return RT_ERR_QOS_DSCP_VALUE;

    if ((retVal = rtl8367c_setAsicRemarkingDscpParameter(unit, int_pri, dscp)) != RT_ERR_OK)
        return retVal;

    return RT_ERR_OK;
}

/* Function Name:
 *      dal_rtl8367c_qos_dscpRemark_get
 * Description:
 *      Get DSCP remarking parameter.
 * Input:
 *      unit        - Unit ID
 *      int_pri     - Internal priority value.
 * Output:
 *      Dscp - DSCP value.
 * Return:
 *      RT_ERR_OK               - OK
 *      RT_ERR_FAILED           - Failed
 *      RT_ERR_SMI              - SMI access error
 *      RT_ERR_QOS_INT_PRIORITY - Invalid priority.
 * Note:
 *      The API can get DSCP parameters. It would return DSCP value for mapping priority.
 */

rtksw_api_ret_t dal_rtl8367c_qos_dscpRemark_get(rtksw_uint32 unit, rtksw_pri_t int_pri, rtksw_dscp_t *pDscp)
{
    rtksw_api_ret_t retVal;

    /* Check initialization state */
    RTKSW_CHK_INIT_STATE(unit);

    if (int_pri > RTKSW_PRIMAX )
        return RT_ERR_QOS_INT_PRIORITY;

    if ((retVal = rtl8367c_getAsicRemarkingDscpParameter(unit, int_pri, pDscp)) != RT_ERR_OK)
        return retVal;

    return RT_ERR_OK;
}

/* Function Name:
 *      dal_rtl8367c_qos_dscpRemarkSrcSel_set
 * Description:
 *      Set remarking source of DSCP remarking.
 * Input:
 *      unit        - Unit ID
 *      type        - remarking source
 * Output:
 *      None
 * Return:
 *      RT_ERR_OK
 *      RT_ERR_FAILED
 *      RT_ERR_NOT_INIT         - The module is not initial
 *      RT_ERR_PORT_ID  - invalid port id
 *      RT_ERR_INPUT            - invalid input parameter

 * Note:
 *      The API can configure DSCP remark functionality to map original DSCP value or internal
 *      priority to TX DSCP value.
 */
rtksw_api_ret_t dal_rtl8367c_qos_dscpRemarkSrcSel_set(rtksw_uint32 unit, rtksw_qos_dscpRmkSrc_t type)
{
    rtksw_api_ret_t retVal;

    /* Check initialization state */
    RTKSW_CHK_INIT_STATE(unit);

    if (type >= DSCP_RMK_SRC_END )
        return RT_ERR_QOS_INT_PRIORITY;

    if ((retVal = rtl8367c_setAsicRemarkingDscpSrc(unit, type)) != RT_ERR_OK)
        return retVal;

    return RT_ERR_OK;
}

/* Function Name:
 *      dal_rtl8367c_qos_dscpRemarkSrcSel_get
 * Description:
 *      Get remarking source of DSCP remarking.
 * Input:
 *      unit        - Unit ID
 * Output:
 *      pType      - remarking source
 * Return:
 *      RT_ERR_OK
 *      RT_ERR_FAILED
 *      RT_ERR_NOT_INIT         - The module is not initial
 *      RT_ERR_PORT_ID          - invalid port id
 *      RT_ERR_INPUT            - invalid input parameter
 *      RT_ERR_NULL_POINTER     - input parameter may be null pointer

 * Note:
 *      None
 */
rtksw_api_ret_t dal_rtl8367c_qos_dscpRemarkSrcSel_get(rtksw_uint32 unit, rtksw_qos_dscpRmkSrc_t *pType)
{
    rtksw_api_ret_t retVal;

    /* Check initialization state */
    RTKSW_CHK_INIT_STATE(unit);

    if ((retVal = rtl8367c_getAsicRemarkingDscpSrc(unit, pType)) != RT_ERR_OK)
        return retVal;

    return RT_ERR_OK;
}

/* Function Name:
 *      dal_rtl8367c_qos_dscpRemark2Dscp_set
 * Description:
 *      Set DSCP to remarked DSCP mapping.
 * Input:
 *      unit        - Unit ID
 *      dscp        - DSCP value
 *      rmkDscp     - remarked DSCP value
 * Output:
 *      None.
 * Return:
 *      RT_ERR_OK
 *      RT_ERR_FAILED
 *      RT_ERR_QOS_DSCP_VALUE   - Invalid dscp value
 * Note:
 *      dscp parameter can be DSCP value or internal priority according to configuration of API
 *      dal_apollomp_qos_dscpRemarkSrcSel_set(), because DSCP remark functionality can map original DSCP
 *      value or internal priority to TX DSCP value.
 */
rtksw_api_ret_t dal_rtl8367c_qos_dscpRemark2Dscp_set(rtksw_uint32 unit, rtksw_dscp_t dscp, rtksw_dscp_t rmkDscp)
{
    rtksw_api_ret_t retVal;

    /* Check initialization state */
    RTKSW_CHK_INIT_STATE(unit);

    if ((dscp > RTKSW_DSCPMAX) || (rmkDscp > RTKSW_DSCPMAX))
        return RT_ERR_QOS_DSCP_VALUE;

    if ((retVal = rtl8367c_setAsicRemarkingDscp2Dscp(unit, dscp, rmkDscp)) != RT_ERR_OK)
        return retVal;

    return RT_ERR_OK;
}

/* Function Name:
 *      dal_rtl8367c_qos_dscpRemark2Dscp_get
 * Description:
 *      Get DSCP to remarked DSCP mapping.
 * Input:
 *      unit        - Unit ID
 *      dscp        - DSCP value
 * Output:
 *      pDscp   - remarked DSCP value
 * Return:
 *      RT_ERR_OK
 *      RT_ERR_FAILED
 *      RT_ERR_QOS_DSCP_VALUE   - Invalid dscp value
 *      RT_ERR_NULL_POINTER     - NULL pointer
 * Note:
 *      None.
 */
rtksw_api_ret_t dal_rtl8367c_qos_dscpRemark2Dscp_get(rtksw_uint32 unit, rtksw_dscp_t dscp, rtksw_dscp_t *pDscp)
{
    rtksw_api_ret_t retVal;

    /* Check initialization state */
    RTKSW_CHK_INIT_STATE(unit);

    if (dscp > RTKSW_DSCPMAX)
        return RT_ERR_QOS_DSCP_VALUE;

    if ((retVal = rtl8367c_getAsicRemarkingDscp2Dscp(unit, dscp, pDscp)) != RT_ERR_OK)
        return retVal;

    return RT_ERR_OK;
}

/* Function Name:
 *      dal_rtl8367c_qos_portPriSelIndex_set
 * Description:
 *      Configure priority decision index to each port.
 * Input:
 *      unit        - Unit ID
 *      port        - Port id.
 *      index       - priority decision index.
 * Output:
 *      None
 * Return:
 *      RT_ERR_OK               - OK
 *      RT_ERR_FAILED           - Failed
 *      RT_ERR_SMI              - SMI access error
 *      RT_ERR_PORT_ID          - Invalid port number.
 *      RT_ERR_ENTRY_INDEX - Invalid entry index.
 * Note:
 *      The API can set priority of port assignments for queue usage and packet scheduling.
 */
rtksw_api_ret_t dal_rtl8367c_qos_portPriSelIndex_set(rtksw_uint32 unit, rtksw_port_t port, rtksw_qos_priDecTbl_t index)
{
    rtksw_api_ret_t retVal;

    /* Check initialization state */
    RTKSW_CHK_INIT_STATE(unit);

    /* Check Port Valid */
    RTKSW_CHK_PORT_VALID(unit, port);

    if (index >= PRIDECTBL_END )
        return RT_ERR_ENTRY_INDEX;

    if ((retVal = rtl8367c_setAsicPortPriorityDecisionIndex(unit, rtksw_switch_port_L2P_get(unit, port), index)) != RT_ERR_OK)
        return retVal;

    return RT_ERR_OK;
}

/* Function Name:
 *      dal_rtl8367c_qos_portPriSelIndex_get
 * Description:
 *      Get priority decision index from each port.
 * Input:
 *      unit        - Unit ID
 *      port        - Port id.
 * Output:
 *      pIndex - priority decision index.
 * Return:
 *      RT_ERR_OK           - OK
 *      RT_ERR_FAILED       - Failed
 *      RT_ERR_SMI          - SMI access error
 *      RT_ERR_PORT_ID      - Invalid port number.
 * Note:
 *      The API can get priority of port assignments for queue usage and packet scheduling.
 */
rtksw_api_ret_t dal_rtl8367c_qos_portPriSelIndex_get(rtksw_uint32 unit, rtksw_port_t port, rtksw_qos_priDecTbl_t *pIndex)
{
    rtksw_api_ret_t retVal;

    /* Check initialization state */
    RTKSW_CHK_INIT_STATE(unit);

    /* Check Port Valid */
    RTKSW_CHK_PORT_VALID(unit, port);

    if ((retVal = rtl8367c_getAsicPortPriorityDecisionIndex(unit, rtksw_switch_port_L2P_get(unit, port), pIndex)) != RT_ERR_OK)
        return retVal;

    return RT_ERR_OK;
}


