#ifndef _RTL8367C_ASICDRV_MIRROR_H_
#define _RTL8367C_ASICDRV_MIRROR_H_

#include "rtl8367c_asicdrv.h"

extern ret_t rtl8367c_setAsicPortMirror(rtksw_uint32 unit, rtksw_uint32 source, rtksw_uint32 monitor);
extern ret_t rtl8367c_getAsicPortMirror(rtksw_uint32 unit, rtksw_uint32 *pSource, rtksw_uint32 *pMonitor);
extern ret_t rtl8367c_setAsicPortMirrorRxFunction(rtksw_uint32 unit, rtksw_uint32 enabled);
extern ret_t rtl8367c_getAsicPortMirrorRxFunction(rtksw_uint32 unit, rtksw_uint32* pEnabled);
extern ret_t rtl8367c_setAsicPortMirrorTxFunction(rtksw_uint32 unit, rtksw_uint32 enabled);
extern ret_t rtl8367c_getAsicPortMirrorTxFunction(rtksw_uint32 unit, rtksw_uint32* pEnabled);
extern ret_t rtl8367c_setAsicPortMirrorIsolation(rtksw_uint32 unit, rtksw_uint32 enabled);
extern ret_t rtl8367c_getAsicPortMirrorIsolation(rtksw_uint32 unit, rtksw_uint32* pEnabled);
extern ret_t rtl8367c_setAsicPortMirrorPriority(rtksw_uint32 unit, rtksw_uint32 priority);
extern ret_t rtl8367c_getAsicPortMirrorPriority(rtksw_uint32 unit, rtksw_uint32* pPriority);
extern ret_t rtl8367c_setAsicPortMirrorMask(rtksw_uint32 unit, rtksw_uint32 SourcePortmask);
extern ret_t rtl8367c_getAsicPortMirrorMask(rtksw_uint32 unit, rtksw_uint32 *pSourcePortmask);
extern ret_t rtl8367c_setAsicPortMirrorVlanRxLeaky(rtksw_uint32 unit, rtksw_uint32 enabled);
extern ret_t rtl8367c_getAsicPortMirrorVlanRxLeaky(rtksw_uint32 unit, rtksw_uint32* pEnabled);
extern ret_t rtl8367c_setAsicPortMirrorVlanTxLeaky(rtksw_uint32 unit, rtksw_uint32 enabled);
extern ret_t rtl8367c_getAsicPortMirrorVlanTxLeaky(rtksw_uint32 unit, rtksw_uint32* pEnabled);
extern ret_t rtl8367c_setAsicPortMirrorIsolationRxLeaky(rtksw_uint32 unit, rtksw_uint32 enabled);
extern ret_t rtl8367c_getAsicPortMirrorIsolationRxLeaky(rtksw_uint32 unit, rtksw_uint32* pEnabled);
extern ret_t rtl8367c_setAsicPortMirrorIsolationTxLeaky(rtksw_uint32 unit, rtksw_uint32 enabled);
extern ret_t rtl8367c_getAsicPortMirrorIsolationTxLeaky(rtksw_uint32 unit, rtksw_uint32* pEnabled);
extern ret_t rtl8367c_setAsicPortMirrorRealKeep(rtksw_uint32 unit, rtksw_uint32 mode);
extern ret_t rtl8367c_getAsicPortMirrorRealKeep(rtksw_uint32 unit, rtksw_uint32* pMode);
extern ret_t rtl8367c_setAsicPortMirrorOverride(rtksw_uint32 unit, rtksw_uint32 rxMirror, rtksw_uint32 txMirror, rtksw_uint32 aclMirror);
extern ret_t rtl8367c_getAsicPortMirrorOverride(rtksw_uint32 unit, rtksw_uint32 *pRxMirror, rtksw_uint32 *pTxMirror, rtksw_uint32 *pAclMirror);

#endif /*#ifndef _RTL8367C_ASICDRV_MIRROR_H_*/

