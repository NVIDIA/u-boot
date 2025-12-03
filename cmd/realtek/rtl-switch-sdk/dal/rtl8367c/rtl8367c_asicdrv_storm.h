#ifndef _RTL8367C_ASICDRV_STORM_H_
#define _RTL8367C_ASICDRV_STORM_H_

#include "rtl8367c_asicdrv.h"

extern ret_t rtl8367c_setAsicStormFilterBroadcastEnable(rtksw_uint32 unit, rtksw_uint32 port, rtksw_uint32 enabled);
extern ret_t rtl8367c_getAsicStormFilterBroadcastEnable(rtksw_uint32 unit, rtksw_uint32 port, rtksw_uint32 *pEnabled);
extern ret_t rtl8367c_setAsicStormFilterBroadcastMeter(rtksw_uint32 unit, rtksw_uint32 port, rtksw_uint32 meter);
extern ret_t rtl8367c_getAsicStormFilterBroadcastMeter(rtksw_uint32 unit, rtksw_uint32 port, rtksw_uint32 *pMeter);
extern ret_t rtl8367c_setAsicStormFilterMulticastEnable(rtksw_uint32 unit, rtksw_uint32 port, rtksw_uint32 enabled);
extern ret_t rtl8367c_getAsicStormFilterMulticastEnable(rtksw_uint32 unit,rtksw_uint32 port, rtksw_uint32 *pEnabled);
extern ret_t rtl8367c_setAsicStormFilterMulticastMeter(rtksw_uint32 unit, rtksw_uint32 port, rtksw_uint32 meter);
extern ret_t rtl8367c_getAsicStormFilterMulticastMeter(rtksw_uint32 unit, rtksw_uint32 port, rtksw_uint32 *pMeter);
extern ret_t rtl8367c_setAsicStormFilterUnknownMulticastEnable(rtksw_uint32 unit, rtksw_uint32 port, rtksw_uint32 enabled);
extern ret_t rtl8367c_getAsicStormFilterUnknownMulticastEnable(rtksw_uint32 unit, rtksw_uint32 port, rtksw_uint32 *pEnabled);
extern ret_t rtl8367c_setAsicStormFilterUnknownMulticastMeter(rtksw_uint32 unit, rtksw_uint32 port, rtksw_uint32 meter);
extern ret_t rtl8367c_getAsicStormFilterUnknownMulticastMeter(rtksw_uint32 unit, rtksw_uint32 port, rtksw_uint32 *pMeter);
extern ret_t rtl8367c_setAsicStormFilterUnknownUnicastEnable(rtksw_uint32 unit, rtksw_uint32 port, rtksw_uint32 enabled);
extern ret_t rtl8367c_getAsicStormFilterUnknownUnicastEnable(rtksw_uint32 unit, rtksw_uint32 port, rtksw_uint32 *pEnabled);
extern ret_t rtl8367c_setAsicStormFilterUnknownUnicastMeter(rtksw_uint32 unit, rtksw_uint32 port, rtksw_uint32 meter);
extern ret_t rtl8367c_getAsicStormFilterUnknownUnicastMeter(rtksw_uint32 unit, rtksw_uint32 port, rtksw_uint32 *pMeter);
extern ret_t rtl8367c_setAsicStormFilterExtBroadcastMeter(rtksw_uint32 unit, rtksw_uint32 meter);
extern ret_t rtl8367c_getAsicStormFilterExtBroadcastMeter(rtksw_uint32 unit, rtksw_uint32 *pMeter);
extern ret_t rtl8367c_setAsicStormFilterExtMulticastMeter(rtksw_uint32 unit, rtksw_uint32 meter);
extern ret_t rtl8367c_getAsicStormFilterExtMulticastMeter(rtksw_uint32 unit, rtksw_uint32 *pMeter);
extern ret_t rtl8367c_setAsicStormFilterExtUnknownMulticastMeter(rtksw_uint32 unit, rtksw_uint32 meter);
extern ret_t rtl8367c_getAsicStormFilterExtUnknownMulticastMeter(rtksw_uint32 unit, rtksw_uint32 *pMeter);
extern ret_t rtl8367c_setAsicStormFilterExtUnknownUnicastMeter(rtksw_uint32 unit, rtksw_uint32 meter);
extern ret_t rtl8367c_getAsicStormFilterExtUnknownUnicastMeter(rtksw_uint32 unit, rtksw_uint32 *pMeter);
extern ret_t rtl8367c_setAsicStormFilterExtBroadcastEnable(rtksw_uint32 unit, rtksw_uint32 enabled);
extern ret_t rtl8367c_getAsicStormFilterExtBroadcastEnable(rtksw_uint32 unit, rtksw_uint32 *pEnabled);
extern ret_t rtl8367c_setAsicStormFilterExtMulticastEnable(rtksw_uint32 unit, rtksw_uint32 enabled);
extern ret_t rtl8367c_getAsicStormFilterExtMulticastEnable(rtksw_uint32 unit, rtksw_uint32 *pEnabled);
extern ret_t rtl8367c_setAsicStormFilterExtUnknownMulticastEnable(rtksw_uint32 unit, rtksw_uint32 enabled);
extern ret_t rtl8367c_getAsicStormFilterExtUnknownMulticastEnable(rtksw_uint32 unit, rtksw_uint32 *pEnabled);
extern ret_t rtl8367c_setAsicStormFilterExtUnknownUnicastEnable(rtksw_uint32 unit, rtksw_uint32 enabled);
extern ret_t rtl8367c_getAsicStormFilterExtUnknownUnicastEnable(rtksw_uint32 unit, rtksw_uint32 *pEnabled);
extern ret_t rtl8367c_setAsicStormFilterExtEnablePortMask(rtksw_uint32 unit, rtksw_uint32 portmask);
extern ret_t rtl8367c_getAsicStormFilterExtEnablePortMask(rtksw_uint32 unit, rtksw_uint32 *pPortmask);


#endif /*_RTL8367C_ASICDRV_STORM_H_*/


