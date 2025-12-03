#ifndef _RTL8367C_ASICDRV_MISC_H_
#define _RTL8367C_ASICDRV_MISC_H_

#include "rtl8367c_asicdrv.h"

extern ret_t rtl8367c_setAsicMacAddress(rtksw_uint32 unit, ether_addr_t mac);
extern ret_t rtl8367c_getAsicMacAddress(rtksw_uint32 unit, ether_addr_t *pMac);
extern ret_t rtl8367c_getAsicDebugInfo(rtksw_uint32 unit, rtksw_uint32 port, rtksw_uint32 *pDebugifo);
extern ret_t rtl8367c_setAsicPortJamMode(rtksw_uint32 unit, rtksw_uint32 mode);
extern ret_t rtl8367c_getAsicPortJamMode(rtksw_uint32 unit, rtksw_uint32* pMode);
extern ret_t rtl8367c_setAsicMaxLengthCfg(rtksw_uint32 unit, rtksw_uint32 cfgId, rtksw_uint32 maxLength);
extern ret_t rtl8367c_getAsicMaxLengthCfg(rtksw_uint32 unit, rtksw_uint32 cfgId, rtksw_uint32 *pMaxLength);
extern ret_t rtl8367c_setAsicMaxLength(rtksw_uint32 unit, rtksw_uint32 port, rtksw_uint32 type, rtksw_uint32 cfgId);
extern ret_t rtl8367c_getAsicMaxLength(rtksw_uint32 unit, rtksw_uint32 port, rtksw_uint32 type, rtksw_uint32 *pCfgId);

#endif /*_RTL8367C_ASICDRV_MISC_H_*/

