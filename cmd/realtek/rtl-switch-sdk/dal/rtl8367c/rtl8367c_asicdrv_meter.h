#ifndef _RTL8367C_ASICDRV_METER_H_
#define _RTL8367C_ASICDRV_METER_H_

#include "rtl8367c_asicdrv.h"


extern ret_t rtl8367c_setAsicShareMeter(rtksw_uint32 unit, rtksw_uint32 index, rtksw_uint32 rate, rtksw_uint32 ifg);
extern ret_t rtl8367c_getAsicShareMeter(rtksw_uint32 unit, rtksw_uint32 index, rtksw_uint32 *pRate, rtksw_uint32 *pIfg);
extern ret_t rtl8367c_setAsicShareMeterBucketSize(rtksw_uint32 unit, rtksw_uint32 index, rtksw_uint32 lbThreshold);
extern ret_t rtl8367c_getAsicShareMeterBucketSize(rtksw_uint32 unit, rtksw_uint32 index, rtksw_uint32 *pLbThreshold);
extern ret_t rtl8367c_setAsicShareMeterType(rtksw_uint32 unit, rtksw_uint32 index, rtksw_uint32 type);
extern ret_t rtl8367c_getAsicShareMeterType(rtksw_uint32 unit, rtksw_uint32 index, rtksw_uint32 *pType);
extern ret_t rtl8367c_setAsicMeterExceedStatus(rtksw_uint32 unit, rtksw_uint32 index);
extern ret_t rtl8367c_getAsicMeterExceedStatus(rtksw_uint32 unit, rtksw_uint32 index, rtksw_uint32* pStatus);

#endif /*_RTL8367C_ASICDRV_FC_H_*/

