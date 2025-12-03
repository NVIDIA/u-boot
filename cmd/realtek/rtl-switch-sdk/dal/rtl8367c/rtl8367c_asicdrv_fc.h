#ifndef _RTL8367C_ASICDRV_FC_H_
#define _RTL8367C_ASICDRV_FC_H_

#include "../../rtk_switch.h"
#include "rtl8367c_asicdrv.h"


enum FLOW_CONTROL_TYPE
{
    FC_EGRESS = 0,
    FC_INGRESS,
};

enum FC_JUMBO_SIZE
{
    FC_JUMBO_SIZE_3K = 0,
    FC_JUMBO_SIZE_4K,
    FC_JUMBO_SIZE_6K,
    FC_JUMBO_SIZE_9K,
    FC_JUMBO_SIZE_END,

};


extern ret_t rtl8367c_setAsicFlowControlSelect(rtksw_uint32 unit, rtksw_uint32 select);
extern ret_t rtl8367c_getAsicFlowControlSelect(rtksw_uint32 unit, rtksw_uint32 *pSelect);
extern ret_t rtl8367c_setAsicFlowControlJumboMode(rtksw_uint32 unit, rtksw_uint32 enabled);
extern ret_t rtl8367c_getAsicFlowControlJumboMode(rtksw_uint32 unit, rtksw_uint32* pEnabled);
extern ret_t rtl8367c_setAsicFlowControlJumboModeSize(rtksw_uint32 unit, rtksw_uint32 size);
extern ret_t rtl8367c_getAsicFlowControlJumboModeSize(rtksw_uint32 unit, rtksw_uint32* pSize);
extern ret_t rtl8367c_setAsicFlowControlQueueEgressEnable(rtksw_uint32 unit, rtksw_uint32 port, rtksw_uint32 qid, rtksw_uint32 enabled);
extern ret_t rtl8367c_getAsicFlowControlQueueEgressEnable(rtksw_uint32 unit, rtksw_uint32 port, rtksw_uint32 qid, rtksw_uint32* pEnabled);
extern ret_t rtl8367c_setAsicFlowControlDropAll(rtksw_uint32 unit, rtksw_uint32 dropall);
extern ret_t rtl8367c_getAsicFlowControlDropAll(rtksw_uint32 unit, rtksw_uint32* pDropall);
extern ret_t rtl8367c_setAsicFlowControlPauseAllThreshold(rtksw_uint32 unit, rtksw_uint32 threshold);
extern ret_t rtl8367c_getAsicFlowControlPauseAllThreshold(rtksw_uint32 unit, rtksw_uint32 *pThreshold);
extern ret_t rtl8367c_setAsicFlowControlSystemThreshold(rtksw_uint32 unit, rtksw_uint32 onThreshold, rtksw_uint32 offThreshold);
extern ret_t rtl8367c_getAsicFlowControlSystemThreshold(rtksw_uint32 unit, rtksw_uint32 *pOnThreshold, rtksw_uint32 *pOffThreshold);
extern ret_t rtl8367c_setAsicFlowControlSharedThreshold(rtksw_uint32 unit, rtksw_uint32 onThreshold, rtksw_uint32 offThreshold);
extern ret_t rtl8367c_getAsicFlowControlSharedThreshold(rtksw_uint32 unit, rtksw_uint32 *pOnThreshold, rtksw_uint32 *pOffThreshold);
extern ret_t rtl8367c_setAsicFlowControlPortThreshold(rtksw_uint32 unit, rtksw_uint32 onThreshold, rtksw_uint32 offThreshold);
extern ret_t rtl8367c_getAsicFlowControlPortThreshold(rtksw_uint32 unit, rtksw_uint32 *pOnThreshold, rtksw_uint32 *pOffThreshold);
extern ret_t rtl8367c_setAsicFlowControlPortPrivateThreshold(rtksw_uint32 unit, rtksw_uint32 onThreshold, rtksw_uint32 offThreshold);
extern ret_t rtl8367c_getAsicFlowControlPortPrivateThreshold(rtksw_uint32 unit, rtksw_uint32 *pOnThreshold, rtksw_uint32 *pOffThreshold);
extern ret_t rtl8367c_setAsicFlowControlSystemDropThreshold(rtksw_uint32 unit, rtksw_uint32 onThreshold, rtksw_uint32 offThreshold);
extern ret_t rtl8367c_getAsicFlowControlSystemDropThreshold(rtksw_uint32 unit, rtksw_uint32 *pOnThreshold, rtksw_uint32 *pOffThreshold);
extern ret_t rtl8367c_setAsicFlowControlSharedDropThreshold(rtksw_uint32 unit, rtksw_uint32 onThreshold, rtksw_uint32 offThreshold);
extern ret_t rtl8367c_getAsicFlowControlSharedDropThreshold(rtksw_uint32 unit, rtksw_uint32 *pOnThreshold, rtksw_uint32 *pOffThreshold);
extern ret_t rtl8367c_setAsicFlowControlPortDropThreshold(rtksw_uint32 unit, rtksw_uint32 onThreshold, rtksw_uint32 offThreshold);
extern ret_t rtl8367c_getAsicFlowControlPortDropThreshold(rtksw_uint32 unit, rtksw_uint32 *pOnThreshold, rtksw_uint32 *pOffThreshold);
extern ret_t rtl8367c_setAsicFlowControlPortPrivateDropThreshold(rtksw_uint32 unit, rtksw_uint32 onThreshold, rtksw_uint32 offThreshold);
extern ret_t rtl8367c_getAsicFlowControlPortPrivateDropThreshold(rtksw_uint32 unit, rtksw_uint32 *pOnThreshold, rtksw_uint32 *pOffThreshold);
extern ret_t rtl8367c_setAsicFlowControlSystemJumboThreshold(rtksw_uint32 unit, rtksw_uint32 onThreshold, rtksw_uint32 offThreshold);
extern ret_t rtl8367c_getAsicFlowControlSystemJumboThreshold(rtksw_uint32 unit, rtksw_uint32 *pOnThreshold, rtksw_uint32 *pOffThreshold);
extern ret_t rtl8367c_setAsicFlowControlSharedJumboThreshold(rtksw_uint32 unit, rtksw_uint32 onThreshold, rtksw_uint32 offThreshold);
extern ret_t rtl8367c_getAsicFlowControlSharedJumboThreshold(rtksw_uint32 unit, rtksw_uint32 *pOnThreshold, rtksw_uint32 *pOffThreshold);
extern ret_t rtl8367c_setAsicFlowControlPortJumboThreshold(rtksw_uint32 unit, rtksw_uint32 onThreshold, rtksw_uint32 offThreshold);
extern ret_t rtl8367c_getAsicFlowControlPortJumboThreshold(rtksw_uint32 unit, rtksw_uint32 *pOnThreshold, rtksw_uint32 *pOffThreshold);
extern ret_t rtl8367c_setAsicFlowControlPortPrivateJumboThreshold(rtksw_uint32 unit, rtksw_uint32 onThreshold, rtksw_uint32 offThreshold);
extern ret_t rtl8367c_getAsicFlowControlPortPrivateJumboThreshold(rtksw_uint32 unit, rtksw_uint32 *pOnThreshold, rtksw_uint32 *pOffThreshold);

extern ret_t rtl8367c_setAsicEgressFlowControlPortDropGap(rtksw_uint32 unit, rtksw_uint32 gap);
extern ret_t rtl8367c_getAsicEgressFlowControlPortDropGap(rtksw_uint32 unit, rtksw_uint32 *pGap);
extern ret_t rtl8367c_setAsicEgressFlowControlQueueDropGap(rtksw_uint32 unit, rtksw_uint32 gap);
extern ret_t rtl8367c_getAsicEgressFlowControlQueueDropGap(rtksw_uint32 unit, rtksw_uint32 *pGap);
extern ret_t rtl8367c_setAsicEgressFlowControlPortDropThreshold(rtksw_uint32 unit, rtksw_uint32 port, rtksw_uint32 threshold);
extern ret_t rtl8367c_getAsicEgressFlowControlPortDropThreshold(rtksw_uint32 unit, rtksw_uint32 port, rtksw_uint32 *pThreshold);
extern ret_t rtl8367c_setAsicEgressFlowControlQueueDropThreshold(rtksw_uint32 unit, rtksw_uint32 qid, rtksw_uint32 threshold);
extern ret_t rtl8367c_getAsicEgressFlowControlQueueDropThreshold(rtksw_uint32 unit, rtksw_uint32 qid, rtksw_uint32 *pThreshold);
extern ret_t rtl8367c_getAsicEgressQueueEmptyPortMask(rtksw_uint32 unit, rtksw_uint32 *pPortmask);
extern ret_t rtl8367c_getAsicTotalPage(rtksw_uint32 unit, rtksw_uint32 *pPageCount);
extern ret_t rtl8367c_getAsicPulbicPage(rtksw_uint32 unit, rtksw_uint32 *pPageCount);
extern ret_t rtl8367c_getAsicMaxTotalPage(rtksw_uint32 unit, rtksw_uint32 *pPageCount);
extern ret_t rtl8367c_getAsicMaxPulbicPage(rtksw_uint32 unit, rtksw_uint32 *pPageCount);
extern ret_t rtl8367c_getAsicPortPage(rtksw_uint32 unit, rtksw_uint32 port, rtksw_uint32 *pPageCount);
extern ret_t rtl8367c_getAsicPortPageMax(rtksw_uint32 unit, rtksw_uint32 port, rtksw_uint32 *pPageCount);
extern ret_t rtl8367c_setAsicFlowControlEgressPortIndep(rtksw_uint32 unit, rtksw_uint32 port, rtksw_uint32 enable);
extern ret_t rtl8367c_getAsicFlowControlEgressPortIndep(rtksw_uint32 unit, rtksw_uint32 port, rtksw_uint32 *pEnable);

#endif /*_RTL8367C_ASICDRV_FC_H_*/

