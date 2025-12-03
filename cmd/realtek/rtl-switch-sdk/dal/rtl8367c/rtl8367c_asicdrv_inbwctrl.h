#ifndef _RTL8367C_ASICDRV_INBWCTRL_H_
#define _RTL8367C_ASICDRV_INBWCTRL_H_

#include "rtl8367c_asicdrv.h"

extern ret_t rtl8367c_setAsicPortIngressBandwidth(rtksw_uint32 unit, rtksw_uint32 port, rtksw_uint32 bandwidth, rtksw_uint32 preifg, rtksw_uint32 enableFC);
extern ret_t rtl8367c_getAsicPortIngressBandwidth(rtksw_uint32 unit, rtksw_uint32 port, rtksw_uint32* pBandwidth, rtksw_uint32* pPreifg, rtksw_uint32* pEnableFC );
extern ret_t rtl8367c_setAsicPortIngressBandwidthBypass(rtksw_uint32 unit, rtksw_uint32 enabled);
extern ret_t rtl8367c_getAsicPortIngressBandwidthBypass(rtksw_uint32 unit, rtksw_uint32* pEnabled);


#endif /*_RTL8367C_ASICDRV_INBWCTRL_H_*/

