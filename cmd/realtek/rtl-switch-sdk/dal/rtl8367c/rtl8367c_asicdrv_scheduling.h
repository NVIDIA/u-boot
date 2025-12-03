#ifndef _RTL8367C_ASICDRV_SCHEDULING_H_
#define _RTL8367C_ASICDRV_SCHEDULING_H_

#include "rtl8367c_asicdrv.h"

#define RTL8367C_QWEIGHTMAX    0x7F
#define RTL8367C_PORT_QUEUE_METER_INDEX_MAX    7

/* enum for queue type */
enum QUEUETYPE
{
    QTYPE_STRICT = 0,
    QTYPE_WFQ,
};
extern ret_t rtl8367c_setAsicLeakyBucketParameter(rtksw_uint32 unit, rtksw_uint32 tick, rtksw_uint32 token);
extern ret_t rtl8367c_getAsicLeakyBucketParameter(rtksw_uint32 unit, rtksw_uint32 *tick, rtksw_uint32 *token);
extern ret_t rtl8367c_setAsicAprMeter(rtksw_uint32 unit, rtksw_uint32 port, rtksw_uint32 qid, rtksw_uint32 apridx);
extern ret_t rtl8367c_getAsicAprMeter(rtksw_uint32 unit, rtksw_uint32 port, rtksw_uint32 qid, rtksw_uint32 *apridx);
extern ret_t rtl8367c_setAsicPprMeter(rtksw_uint32 unit, rtksw_uint32 port, rtksw_uint32 qid, rtksw_uint32 ppridx);
extern ret_t rtl8367c_getAsicPprMeter(rtksw_uint32 unit, rtksw_uint32 port, rtksw_uint32 qid, rtksw_uint32 *ppridx);
extern ret_t rtl8367c_setAsicAprEnable(rtksw_uint32 unit, rtksw_uint32 port, rtksw_uint32 aprEnable);
extern ret_t rtl8367c_getAsicAprEnable(rtksw_uint32 unit, rtksw_uint32 port, rtksw_uint32 *aprEnable);
extern ret_t rtl8367c_setAsicPprEnable(rtksw_uint32 unit, rtksw_uint32 port, rtksw_uint32 pprEnable);
extern ret_t rtl8367c_getAsicPprEnable(rtksw_uint32 unit, rtksw_uint32 port, rtksw_uint32 *pprEnable);

extern ret_t rtl8367c_setAsicWFQWeight(rtksw_uint32 unit, rtksw_uint32, rtksw_uint32 queueid, rtksw_uint32 weight );
extern ret_t rtl8367c_getAsicWFQWeight(rtksw_uint32 unit, rtksw_uint32, rtksw_uint32 queueid, rtksw_uint32 *weight );
extern ret_t rtl8367c_setAsicWFQBurstSize(rtksw_uint32 unit, rtksw_uint32 burstsize);
extern ret_t rtl8367c_getAsicWFQBurstSize(rtksw_uint32 unit, rtksw_uint32 *burstsize);

extern ret_t rtl8367c_setAsicQueueType(rtksw_uint32 unit, rtksw_uint32 port, rtksw_uint32 qid, rtksw_uint32 queueType);
extern ret_t rtl8367c_getAsicQueueType(rtksw_uint32 unit, rtksw_uint32 port, rtksw_uint32 qid, rtksw_uint32 *queueType);
extern ret_t rtl8367c_setAsicQueueRate(rtksw_uint32 unit, rtksw_uint32 port, rtksw_uint32 qid, rtksw_uint32 ppridx, rtksw_uint32 apridx );
extern ret_t rtl8367c_getAsicQueueRate(rtksw_uint32 unit, rtksw_uint32 port, rtksw_uint32 qid, rtksw_uint32* ppridx, rtksw_uint32* apridx );
extern ret_t rtl8367c_setAsicPortEgressRate(rtksw_uint32 unit, rtksw_uint32 port, rtksw_uint32 rate);
extern ret_t rtl8367c_getAsicPortEgressRate(rtksw_uint32 unit, rtksw_uint32 port, rtksw_uint32 *rate);
extern ret_t rtl8367c_setAsicPortEgressRateIfg(rtksw_uint32 unit, rtksw_uint32 ifg);
extern ret_t rtl8367c_getAsicPortEgressRateIfg(rtksw_uint32 unit, rtksw_uint32 *ifg);

#endif /*_RTL8367C_ASICDRV_SCHEDULING_H_*/

