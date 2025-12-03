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
 * Feature : Here is a list of all functions and variables in MIB module.
 *
 */

#include "../../rtk_switch.h"
#include "../../rtk_error.h"
#include "dal_rtl8367c_stat.h"

#include "rtl8367c_asicdrv.h"
#include "rtl8367c_asicdrv_mib.h"

#include "../dal_mgmts.h"

#define MIB_NOT_SUPPORT     (0xFFFF)
static rtksw_api_ret_t _get_asic_mib_idx(rtksw_stat_port_type_t cnt_idx, RTL8367C_MIBCOUNTER *pMib_idx)
{
    RTL8367C_MIBCOUNTER mib_asic_idx[STAT_PORT_CNTR_END]=
    {
        ifInOctets,                     /* STAT_IfInOctets */
        dot3StatsFCSErrors,             /* STAT_Dot3StatsFCSErrors */
        dot3StatsSymbolErrors,          /* STAT_Dot3StatsSymbolErrors */
        dot3InPauseFrames,              /* STAT_Dot3InPauseFrames */
        dot3ControlInUnknownOpcodes,    /* STAT_Dot3ControlInUnknownOpcodes */
        etherStatsFragments,            /* STAT_EtherStatsFragments */
        etherStatsJabbers,              /* STAT_EtherStatsJabbers */
        ifInUcastPkts,                  /* STAT_IfInUcastPkts */
        etherStatsDropEvents,           /* STAT_EtherStatsDropEvents */
        etherStatsOctets,               /* STAT_EtherStatsOctets */
        etherStatsUnderSizePkts,        /* STAT_EtherStatsUnderSizePkts */
        etherOversizeStats,             /* STAT_EtherOversizeStats */
        etherStatsPkts64Octets,         /* STAT_EtherStatsPkts64Octets */
        etherStatsPkts65to127Octets,    /* STAT_EtherStatsPkts65to127Octets */
        etherStatsPkts128to255Octets,   /* STAT_EtherStatsPkts128to255Octets */
        etherStatsPkts256to511Octets,   /* STAT_EtherStatsPkts256to511Octets */
        etherStatsPkts512to1023Octets,  /* STAT_EtherStatsPkts512to1023Octets */
        etherStatsPkts1024to1518Octets, /* STAT_EtherStatsPkts1024to1518Octets */
        ifInMulticastPkts,              /* STAT_EtherStatsMulticastPkts */
        ifInBroadcastPkts,              /* STAT_EtherStatsBroadcastPkts */
        ifOutOctets,                    /* STAT_IfOutOctets */
        dot3StatsSingleCollisionFrames, /* STAT_Dot3StatsSingleCollisionFrames */
        dot3StatMultipleCollisionFrames,/* STAT_Dot3StatsMultipleCollisionFrames */
        dot3sDeferredTransmissions,     /* STAT_Dot3StatsDeferredTransmissions */
        dot3StatsLateCollisions,        /* STAT_Dot3StatsLateCollisions */
        etherStatsCollisions,           /* STAT_EtherStatsCollisions */
        dot3StatsExcessiveCollisions,   /* STAT_Dot3StatsExcessiveCollisions */
        dot3OutPauseFrames,             /* STAT_Dot3OutPauseFrames */
        MIB_NOT_SUPPORT,                /* STAT_Dot1dBasePortDelayExceededDiscards */
        dot1dTpPortInDiscards,          /* STAT_Dot1dTpPortInDiscards */
        ifOutUcastPkts,                 /* STAT_IfOutUcastPkts */
        ifOutMulticastPkts,             /* STAT_IfOutMulticastPkts */
        ifOutBroadcastPkts,             /* STAT_IfOutBroadcastPkts */
        outOampduPkts,                  /* STAT_OutOampduPkts */
        inOampduPkts,                   /* STAT_InOampduPkts */
        MIB_NOT_SUPPORT,                /* STAT_PktgenPkts */
        inMldChecksumError,             /* STAT_InMldChecksumError */
        inIgmpChecksumError,            /* STAT_InIgmpChecksumError */
        inMldSpecificQuery,             /* STAT_InMldSpecificQuery */
        inMldGeneralQuery,              /* STAT_InMldGeneralQuery */
        inIgmpSpecificQuery,            /* STAT_InIgmpSpecificQuery */
        inIgmpGeneralQuery,             /* STAT_InIgmpGeneralQuery */
        inMldLeaves,                    /* STAT_InMldLeaves */
        inIgmpLeaves,                   /* STAT_InIgmpInterfaceLeaves */
        inIgmpJoinsSuccess,             /* STAT_InIgmpJoinsSuccess */
        inIgmpJoinsFail,                /* STAT_InIgmpJoinsFail */
        inMldJoinsSuccess,              /* STAT_InMldJoinsSuccess */
        inMldJoinsFail,                 /* STAT_InMldJoinsFail */
        inReportSuppressionDrop,        /* STAT_InReportSuppressionDrop */
        inLeaveSuppressionDrop,         /* STAT_InLeaveSuppressionDrop */
        outIgmpReports,                 /* STAT_OutIgmpReports */
        outIgmpLeaves,                  /* STAT_OutIgmpLeaves */
        outIgmpGeneralQuery,            /* STAT_OutIgmpGeneralQuery */
        outIgmpSpecificQuery,           /* STAT_OutIgmpSpecificQuery */
        outMldReports,                  /* STAT_OutMldReports */
        outMldLeaves,                   /* STAT_OutMldLeaves */
        outMldGeneralQuery,             /* STAT_OutMldGeneralQuery */
        outMldSpecificQuery,            /* STAT_OutMldSpecificQuery */
        inKnownMulticastPkts,           /* STAT_InKnownMulticastPkts */
        ifInMulticastPkts,              /* STAT_IfInMulticastPkts */
        ifInBroadcastPkts,              /* STAT_IfInBroadcastPkts */
        ifOutDiscards                   /* STAT_IfOutDiscards */
    };

    if(cnt_idx >= STAT_PORT_CNTR_END)
        return RT_ERR_STAT_INVALID_PORT_CNTR;

    if(mib_asic_idx[cnt_idx] == MIB_NOT_SUPPORT)
        return RT_ERR_CHIP_NOT_SUPPORTED;

    *pMib_idx = mib_asic_idx[cnt_idx];
    return RT_ERR_OK;
}

/* Function Name:
 *      dal_rtl8367c_stat_global_reset
 * Description:
 *      Reset global MIB counter.
 * Input:
 *      unit    - Unid ID
 * Output:
 *      None
 * Return:
 *      RT_ERR_OK           - OK
 *      RT_ERR_FAILED       - Failed
 *      RT_ERR_SMI          - SMI access error
 * Note:
 *      Reset MIB counter of ports. API will use global reset while port mask is all-ports.
 */
rtksw_api_ret_t dal_rtl8367c_stat_global_reset(rtksw_uint32 unit)
{
    rtksw_api_ret_t retVal;

    /* Check initialization state */
    RTKSW_CHK_INIT_STATE(unit);

    if ((retVal = rtl8367c_setAsicMIBsCounterReset(unit, TRUE,FALSE, 0)) != RT_ERR_OK)
        return retVal;

    return RT_ERR_OK;
}

/* Function Name:
 *      dal_rtl8367c_stat_port_reset
 * Description:
 *      Reset per port MIB counter by port.
 * Input:
 *      unit    - Unid ID
 *      port    - port id.
 * Output:
 *      None
 * Return:
 *      RT_ERR_OK           - OK
 *      RT_ERR_FAILED       - Failed
 *      RT_ERR_SMI          - SMI access error
 * Note:
 *
 */
rtksw_api_ret_t dal_rtl8367c_stat_port_reset(rtksw_uint32 unit, rtksw_port_t port)
{
    rtksw_api_ret_t retVal;
    rtksw_uint32 phyPort;

    /* Check initialization state */
    RTKSW_CHK_INIT_STATE(unit);

    /* Check port valid */
    RTKSW_CHK_PORT_VALID(unit, port);

    phyPort = rtksw_switch_port_L2P_get(unit, port);
    if (phyPort == UNDEFINE_PHY_PORT)
        return RT_ERR_PORT_ID;

    if ((retVal = rtl8367c_setAsicMIBsCounterReset(unit, FALSE,FALSE,1 << phyPort)) != RT_ERR_OK)
        return retVal;

    return RT_ERR_OK;
}

/* Function Name:
 *      dal_rtl8367c_stat_queueManage_reset
 * Description:
 *      Reset queue manage MIB counter.
 * Input:
 *      unit    - Unid ID
 * Output:
 *      None
 * Return:
 *      RT_ERR_OK           - OK
 *      RT_ERR_FAILED       - Failed
 *      RT_ERR_SMI          - SMI access error
 * Note:
 *
 */
rtksw_api_ret_t dal_rtl8367c_stat_queueManage_reset(rtksw_uint32 unit)
{
    rtksw_api_ret_t retVal;

    /* Check initialization state */
    RTKSW_CHK_INIT_STATE(unit);

    if ((retVal = rtl8367c_setAsicMIBsCounterReset(unit, FALSE,TRUE,0)) != RT_ERR_OK)
        return retVal;

    return RT_ERR_OK;
}

/* Function Name:
 *      dal_rtl8367c_stat_global_get
 * Description:
 *      Get global MIB counter
 * Input:
 *      unit        - Unid ID
 *      cntr_idx    - global counter index.
 * Output:
 *      pCntr - global counter value.
 * Return:
 *      RT_ERR_OK           - OK
 *      RT_ERR_FAILED       - Failed
 *      RT_ERR_SMI          - SMI access error
 *      RT_ERR_INPUT        - Invalid input parameters.
 * Note:
 *      Get global MIB counter by index definition.
 */
rtksw_api_ret_t dal_rtl8367c_stat_global_get(rtksw_uint32 unit, rtksw_stat_global_type_t cntr_idx, rtksw_stat_counter_t *pCntr)
{
    rtksw_api_ret_t retVal;
    rtksw_uint64 cnt64;

    /* Check initialization state */
    RTKSW_CHK_INIT_STATE(unit);

    if(NULL == pCntr)
        return RT_ERR_NULL_POINTER;

    if (cntr_idx!=RTKSW_DOT1D_TP_LEARNED_ENTRY_DISCARDS_INDEX)
        return RT_ERR_STAT_INVALID_GLOBAL_CNTR;

    if ((retVal = rtl8367c_getAsicMIBsCounter(unit, 0, dot1dTpLearnedEntryDiscards, &cnt64)) != RT_ERR_OK)
        return retVal;

    *pCntr = (rtksw_stat_counter_t)cnt64;
    return RT_ERR_OK;
}

/* Function Name:
 *      dal_rtl8367c_stat_global_getAll
 * Description:
 *      Get all global MIB counter
 * Input:
 *      unit    - Unid ID
 * Output:
 *      pGlobal_cntrs - global counter structure.
 * Return:
 *      RT_ERR_OK           - OK
 *      RT_ERR_FAILED       - Failed
 *      RT_ERR_SMI          - SMI access error
 *      RT_ERR_INPUT        - Invalid input parameters.
 * Note:
 *      Get all global MIB counter by index definition.
 */
rtksw_api_ret_t dal_rtl8367c_stat_global_getAll(rtksw_uint32 unit, rtksw_stat_global_cntr_t *pGlobal_cntrs)
{
    rtksw_api_ret_t retVal;

    /* Check initialization state */
    RTKSW_CHK_INIT_STATE(unit);

    if(NULL == pGlobal_cntrs)
        return RT_ERR_NULL_POINTER;

    if ((retVal = rtl8367c_getAsicMIBsCounter(unit, 0, (RTL8367C_MIBCOUNTER)RTKSW_DOT1D_TP_LEARNED_ENTRY_DISCARDS_INDEX, &pGlobal_cntrs->dot1dTpLearnedEntryDiscards)) != RT_ERR_OK)
        return retVal;

    return RT_ERR_OK;
}

/* Function Name:
 *      dal_rtl8367c_stat_port_get
 * Description:
 *      Get per port MIB counter by index
 * Input:
 *      unit        - Unid ID
 *      port        - port id.
 *      cntr_idx    - port counter index.
 * Output:
 *      pCntr - MIB retrived counter.
 * Return:
 *      RT_ERR_OK           - OK
 *      RT_ERR_FAILED       - Failed
 *      RT_ERR_SMI          - SMI access error
 * Note:
 *      Get per port MIB counter by index definition.
 */
rtksw_api_ret_t dal_rtl8367c_stat_port_get(rtksw_uint32 unit, rtksw_port_t port, rtksw_stat_port_type_t cntr_idx, rtksw_stat_counter_t *pCntr)
{
    rtksw_api_ret_t       retVal;
    RTL8367C_MIBCOUNTER mib_idx;
    rtksw_stat_counter_t  second_cnt;

    /* Check initialization state */
    RTKSW_CHK_INIT_STATE(unit);

    if(NULL == pCntr)
        return RT_ERR_NULL_POINTER;

    /* Check port valid */
    RTKSW_CHK_PORT_VALID(unit, port);

    if (cntr_idx>=STAT_PORT_CNTR_END)
        return RT_ERR_STAT_INVALID_PORT_CNTR;

    if((retVal = _get_asic_mib_idx(cntr_idx, &mib_idx)) != RT_ERR_OK)
        return retVal;

    if(mib_idx == MIB_NOT_SUPPORT)
        return RT_ERR_CHIP_NOT_SUPPORTED;

    rtksw_uint64 cnt64;
    if ((retVal = rtl8367c_getAsicMIBsCounter(unit, rtksw_switch_port_L2P_get(unit, port), mib_idx, &cnt64)) != RT_ERR_OK)
        return retVal;
    *pCntr = (rtksw_stat_counter_t)cnt64;

    if(cntr_idx == STAT_EtherStatsMulticastPkts)
    {
        if((retVal = _get_asic_mib_idx(STAT_IfOutMulticastPkts, &mib_idx)) != RT_ERR_OK)
            return retVal;

        if((retVal = rtl8367c_getAsicMIBsCounter(unit, rtksw_switch_port_L2P_get(unit, port), mib_idx, &cnt64)) != RT_ERR_OK)
            return retVal;

        *pCntr += (rtksw_stat_counter_t)cnt64;
    }

    if(cntr_idx == STAT_EtherStatsBroadcastPkts)
    {
        if((retVal = _get_asic_mib_idx(STAT_IfOutBroadcastPkts, &mib_idx)) != RT_ERR_OK)
            return retVal;

        if((retVal = rtl8367c_getAsicMIBsCounter(unit, rtksw_switch_port_L2P_get(unit, port), mib_idx, &cnt64)) != RT_ERR_OK)
            return retVal;

        *pCntr += (rtksw_stat_counter_t)cnt64;
    }

    return RT_ERR_OK;
}

/* Function Name:
 *      dal_rtl8367c_stat_port_getAll
 * Description:
 *      Get all counters of one specified port in the specified device.
 * Input:
 *      unit    - Unid ID
 *      port    - port id.
 * Output:
 *      pPort_cntrs - buffer pointer of counter value.
 * Return:
 *      RT_ERR_OK           - OK
 *      RT_ERR_FAILED       - Failed
 *      RT_ERR_SMI          - SMI access error
 *      RT_ERR_INPUT        - Invalid input parameters.
 * Note:
 *      Get all MIB counters of one port.
 */
rtksw_api_ret_t dal_rtl8367c_stat_port_getAll(rtksw_uint32 unit, rtksw_port_t port, rtksw_stat_port_cntr_t *pPort_cntrs)
{
    rtksw_api_ret_t retVal;
    rtksw_uint32 mibIndex;
    rtksw_uint64 mibCounter;
    rtksw_uint32 *accessPtr;
    /* address offset to MIBs counter */
    CONST_T rtksw_uint16 mibLength[STAT_PORT_CNTR_END]= {
        2,1,1,1,1,1,1,1,1,
        2,1,1,1,1,1,1,1,1,1,1,
        2,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
        1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1};

    /* Check initialization state */
    RTKSW_CHK_INIT_STATE(unit);

    if(NULL == pPort_cntrs)
        return RT_ERR_NULL_POINTER;

    /* Check port valid */
    RTKSW_CHK_PORT_VALID(unit, port);

    accessPtr = (rtksw_uint32*)pPort_cntrs;
    for (mibIndex=0;mibIndex<STAT_PORT_CNTR_END;mibIndex++)
    {
        if ((retVal = dal_rtl8367c_stat_port_get(unit, port, mibIndex, &mibCounter)) != RT_ERR_OK)
        {
            if (retVal == RT_ERR_CHIP_NOT_SUPPORTED)
                mibCounter = 0;
            else
                return retVal;
        }

        if (2 == mibLength[mibIndex])
            *(rtksw_uint64*)accessPtr = mibCounter;
        else if (1 == mibLength[mibIndex])
            *accessPtr = mibCounter;
        else
            return RT_ERR_FAILED;

        accessPtr+=mibLength[mibIndex];
    }

    return RT_ERR_OK;
}

/* Function Name:
 *      dal_rtl8367c_stat_logging_counterCfg_set
 * Description:
 *      Set the type and mode of Logging Counter
 * Input:
 *      unit    - Unid ID
 *      idx     - The index of Logging Counter. Should be even number only.(0,2,4,6,8.....30)
 *      mode    - 32 bits or 64 bits mode
 *      type    - Packet counter or byte counter
 * Output:
 *      None.
 * Return:
 *      RT_ERR_OK           - OK
 *      RT_ERR_OUT_OF_RANGE - Out of range.
 *      RT_ERR_FAILED       - Failed
 *      RT_ERR_SMI          - SMI access error
 *      RT_ERR_INPUT        - Invalid input parameters.
 * Note:
 *      Set the type and mode of Logging Counter.
 */
rtksw_api_ret_t dal_rtl8367c_stat_logging_counterCfg_set(rtksw_uint32 unit, rtksw_uint32 idx, rtksw_logging_counter_mode_t mode, rtksw_logging_counter_type_t type)
{
    rtksw_api_ret_t retVal;

    /* Check initialization state */
    RTKSW_CHK_INIT_STATE(unit);

    if(idx > RTL8367C_MIB_MAX_LOG_CNT_IDX)
        return RT_ERR_OUT_OF_RANGE;

    if((idx % 2) == 1)
        return RT_ERR_INPUT;

    if(mode >= LOGGING_MODE_END)
        return RT_ERR_OUT_OF_RANGE;

    if(type >= LOGGING_TYPE_END)
        return RT_ERR_OUT_OF_RANGE;

    if((retVal = rtl8367c_setAsicMIBsLoggingType(unit, (idx / 2), (rtksw_uint32)type)) != RT_ERR_OK)
        return retVal;

    if((retVal = rtl8367c_setAsicMIBsLoggingMode(unit, (idx / 2), (rtksw_uint32)mode)) != RT_ERR_OK)
        return retVal;

    return RT_ERR_OK;
}

/* Function Name:
 *      dal_rtl8367c_stat_logging_counterCfg_get
 * Description:
 *      Get the type and mode of Logging Counter
 * Input:
 *      unit    - Unid ID
 *      idx     - The index of Logging Counter. Should be even number only.(0,2,4,6,8.....30)
 * Output:
 *      pMode   - 32 bits or 64 bits mode
 *      pType   - Packet counter or byte counter
 * Return:
 *      RT_ERR_OK           - OK
 *      RT_ERR_OUT_OF_RANGE - Out of range.
 *      RT_ERR_FAILED       - Failed
 *      RT_ERR_NULL_POINTER - NULL Pointer
 *      RT_ERR_SMI          - SMI access error
 *      RT_ERR_INPUT        - Invalid input parameters.
 * Note:
 *      Get the type and mode of Logging Counter.
 */
rtksw_api_ret_t dal_rtl8367c_stat_logging_counterCfg_get(rtksw_uint32 unit, rtksw_uint32 idx, rtksw_logging_counter_mode_t *pMode, rtksw_logging_counter_type_t *pType)
{
    rtksw_api_ret_t   retVal;
    rtksw_uint32      type, mode;

    /* Check initialization state */
    RTKSW_CHK_INIT_STATE(unit);

    if(idx > RTL8367C_MIB_MAX_LOG_CNT_IDX)
        return RT_ERR_OUT_OF_RANGE;

    if((idx % 2) == 1)
        return RT_ERR_INPUT;

    if(pMode == NULL)
        return RT_ERR_NULL_POINTER;

    if(pType == NULL)
        return RT_ERR_NULL_POINTER;

    if((retVal = rtl8367c_getAsicMIBsLoggingType(unit, (idx / 2), &type)) != RT_ERR_OK)
        return retVal;

    if((retVal = rtl8367c_getAsicMIBsLoggingMode(unit, (idx / 2), &mode)) != RT_ERR_OK)
        return retVal;

    *pMode = (rtksw_logging_counter_mode_t)mode;
    *pType = (rtksw_logging_counter_type_t)type;

    return RT_ERR_OK;
}

/* Function Name:
 *      dal_rtl8367c_stat_logging_counter_reset
 * Description:
 *      Reset Logging Counter
 * Input:
 *      unit    - Unid ID
 *      idx     - The index of Logging Counter. (0~31)
 * Output:
 *      None.
 * Return:
 *      RT_ERR_OK           - OK
 *      RT_ERR_OUT_OF_RANGE - Out of range.
 *      RT_ERR_FAILED       - Failed
 *      RT_ERR_SMI          - SMI access error
 * Note:
 *      Reset Logging Counter.
 */
rtksw_api_ret_t dal_rtl8367c_stat_logging_counter_reset(rtksw_uint32 unit, rtksw_uint32 idx)
{
    rtksw_api_ret_t   retVal;

    /* Check initialization state */
    RTKSW_CHK_INIT_STATE(unit);

    if(idx > RTL8367C_MIB_MAX_LOG_CNT_IDX)
        return RT_ERR_OUT_OF_RANGE;

    if((retVal = rtl8367c_setAsicMIBsResetLoggingCounter(unit, idx)) != RT_ERR_OK)
        return retVal;

    return RT_ERR_OK;
}

/* Function Name:
 *      dal_rtl8367c_stat_logging_counter_get
 * Description:
 *      Get Logging Counter
 * Input:
 *      unit    - Unid ID
 *      idx     - The index of Logging Counter. (0~31)
 * Output:
 *      pCnt    - Logging counter value
 * Return:
 *      RT_ERR_OK           - OK
 *      RT_ERR_OUT_OF_RANGE - Out of range.
 *      RT_ERR_FAILED       - Failed
 *      RT_ERR_SMI          - SMI access error
 * Note:
 *      Get Logging Counter.
 */
rtksw_api_ret_t dal_rtl8367c_stat_logging_counter_get(rtksw_uint32 unit, rtksw_uint32 idx, rtksw_uint32 *pCnt)
{
    rtksw_api_ret_t   retVal;

    /* Check initialization state */
    RTKSW_CHK_INIT_STATE(unit);

    if(NULL == pCnt)
        return RT_ERR_NULL_POINTER;

    if(idx > RTL8367C_MIB_MAX_LOG_CNT_IDX)
        return RT_ERR_OUT_OF_RANGE;

    if((retVal = rtl8367c_getAsicMIBsLogCounter(unit, idx, pCnt)) != RT_ERR_OK)
        return retVal;

    return RT_ERR_OK;
}

/* Function Name:
 *      dal_rtl8367c_stat_lengthMode_set
 * Description:
 *      Set Legnth mode.
 * Input:
 *      unit        - Unid ID
 *      txMode      - The length counting mode
 *      rxMode      - The length counting mode
 * Output:
 *      None.
 * Return:
 *      RT_ERR_OK           - OK
 *      RT_ERR_INPUT        - Out of range.
 *      RT_ERR_FAILED       - Failed
 *      RT_ERR_SMI          - SMI access error
 * Note:
 *
 */
rtksw_api_ret_t dal_rtl8367c_stat_lengthMode_set(rtksw_uint32 unit, rtksw_stat_lengthMode_t txMode, rtksw_stat_lengthMode_t rxMode)
{
    rtksw_api_ret_t   retVal;

    /* Check initialization state */
    RTKSW_CHK_INIT_STATE(unit);

    if(txMode >= LENGTH_MODE_END)
        return RT_ERR_INPUT;

    if(rxMode >= LENGTH_MODE_END)
        return RT_ERR_INPUT;

    if((retVal = rtl8367c_setAsicMIBsLength(unit, (rtksw_uint32)txMode, (rtksw_uint32)rxMode)) != RT_ERR_OK)
        return retVal;

    return RT_ERR_OK;
}

/* Function Name:
 *      dal_rtl8367c_stat_lengthMode_get
 * Description:
 *      Get Legnth mode.
 * Input:
 *      unit    - Unid ID
 * Output:
 *      pTxMode       - The length counting mode
 *      pRxMode       - The length counting mode
 * Return:
 *      RT_ERR_OK           - OK
 *      RT_ERR_INPUT        - Out of range.
 *      RT_ERR_FAILED       - Failed
 *      RT_ERR_SMI          - SMI access error
 * Note:
 */
rtksw_api_ret_t dal_rtl8367c_stat_lengthMode_get(rtksw_uint32 unit, rtksw_stat_lengthMode_t *pTxMode, rtksw_stat_lengthMode_t *pRxMode)
{
    rtksw_api_ret_t   retVal;

    /* Check initialization state */
    RTKSW_CHK_INIT_STATE(unit);

    if(NULL == pTxMode)
        return RT_ERR_NULL_POINTER;

    if(NULL == pRxMode)
        return RT_ERR_NULL_POINTER;

    if((retVal = rtl8367c_getAsicMIBsLength(unit, (rtksw_uint32 *)pTxMode, (rtksw_uint32 *)pRxMode)) != RT_ERR_OK)
        return retVal;

    return RT_ERR_OK;
}


