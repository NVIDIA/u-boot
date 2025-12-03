#ifndef _RTL8367C_ASICDRV_RLDP_H_
#define _RTL8367C_ASICDRV_RLDP_H_

#include "rtl8367c_asicdrv.h"

extern ret_t rtl8367c_setAsicRldp(rtksw_uint32 unit, rtksw_uint32 enabled);
extern ret_t rtl8367c_getAsicRldp(rtksw_uint32 unit, rtksw_uint32 *pEnabled);
extern ret_t rtl8367c_setAsicRldpEnable8051(rtksw_uint32 unit, rtksw_uint32 enabled);
extern ret_t rtl8367c_getAsicRldpEnable8051(rtksw_uint32 unit, rtksw_uint32 *pEnabled);
extern ret_t rtl8367c_setAsicRldpCompareRandomNumber(rtksw_uint32 unit, rtksw_uint32 enabled);
extern ret_t rtl8367c_getAsicRldpCompareRandomNumber(rtksw_uint32 unit, rtksw_uint32 *pEnabled);
extern ret_t rtl8367c_setAsicRldpIndicatorSource(rtksw_uint32 unit, rtksw_uint32 src);
extern ret_t rtl8367c_getAsicRldpIndicatorSource(rtksw_uint32 unit, rtksw_uint32 *pSrc);
extern ret_t rtl8367c_setAsicRldpCheckingStatePara(rtksw_uint32 unit, rtksw_uint32 retryCount, rtksw_uint32 retryPeriod);
extern ret_t rtl8367c_getAsicRldpCheckingStatePara(rtksw_uint32 unit, rtksw_uint32 *pRetryCount, rtksw_uint32 *pRetryPeriod);
extern ret_t rtl8367c_setAsicRldpLoopStatePara(rtksw_uint32 unit, rtksw_uint32 retryCount, rtksw_uint32 retryPeriod);
extern ret_t rtl8367c_getAsicRldpLoopStatePara(rtksw_uint32 unit, rtksw_uint32 *pRetryCount, rtksw_uint32 *pRetryPeriod);
extern ret_t rtl8367c_setAsicRldpTxPortmask(rtksw_uint32 unit, rtksw_uint32 portmask);
extern ret_t rtl8367c_getAsicRldpTxPortmask(rtksw_uint32 unit, rtksw_uint32 *pPortmask);
extern ret_t rtl8367c_setAsicRldpMagicNum(rtksw_uint32 unit, ether_addr_t seed);
extern ret_t rtl8367c_getAsicRldpMagicNum(rtksw_uint32 unit, ether_addr_t *pSeed);
extern ret_t rtl8367c_getAsicRldpLoopedPortmask(rtksw_uint32 unit, rtksw_uint32 *pPortmask);
extern ret_t rtl8367c_setAsicRldp8051Portmask(rtksw_uint32 unit, rtksw_uint32 portmask);
extern ret_t rtl8367c_getAsicRldp8051Portmask(rtksw_uint32 unit, rtksw_uint32 *pPortmask);


extern ret_t rtl8367c_getAsicRldpRandomNumber(rtksw_uint32 unit, ether_addr_t *pRandNumber);
extern ret_t rtl8367c_getAsicRldpLoopedPortPair(rtksw_uint32 unit, rtksw_uint32 port, rtksw_uint32 *pLoopedPair);
extern ret_t rtl8367c_setAsicRlppTrap8051(rtksw_uint32 unit, rtksw_uint32 enabled);
extern ret_t rtl8367c_getAsicRlppTrap8051(rtksw_uint32 unit, rtksw_uint32 *pEnabled);

extern ret_t rtl8367c_setAsicRldpLeaveLoopedPortmask(rtksw_uint32 unit, rtksw_uint32 portmask);
extern ret_t rtl8367c_getAsicRldpLeaveLoopedPortmask(rtksw_uint32 unit, rtksw_uint32 *pPortmask);

extern ret_t rtl8367c_setAsicRldpEnterLoopedPortmask(rtksw_uint32 unit, rtksw_uint32 portmask);
extern ret_t rtl8367c_getAsicRldpEnterLoopedPortmask(rtksw_uint32 unit, rtksw_uint32 *pPortmask);

extern ret_t rtl8367c_setAsicRldpTriggerMode(rtksw_uint32 unit, rtksw_uint32 enabled);
extern ret_t rtl8367c_getAsicRldpTriggerMode(rtksw_uint32 unit, rtksw_uint32 *pEnabled);

#endif /*_RTL8367C_ASICDRV_RLDP_H_*/

