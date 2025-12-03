#ifndef _RTL8367C_ASICDRV_DOT1X_H_
#define _RTL8367C_ASICDRV_DOT1X_H_

#include "rtl8367c_asicdrv.h"

enum DOT1X_UNAUTH_BEHAV
{
    DOT1X_UNAUTH_DROP = 0,
    DOT1X_UNAUTH_TRAP,
    DOT1X_UNAUTH_GVLAN,
    DOT1X_UNAUTH_END
};

extern ret_t rtl8367c_setAsic1xPBEnConfig(rtksw_uint32 unit, rtksw_uint32 port, rtksw_uint32 enabled);
extern ret_t rtl8367c_getAsic1xPBEnConfig(rtksw_uint32 unit, rtksw_uint32 port, rtksw_uint32 *pEnabled);
extern ret_t rtl8367c_setAsic1xPBAuthConfig(rtksw_uint32 unit, rtksw_uint32 port, rtksw_uint32 auth);
extern ret_t rtl8367c_getAsic1xPBAuthConfig(rtksw_uint32 unit, rtksw_uint32 port, rtksw_uint32 *pAuth);
extern ret_t rtl8367c_setAsic1xPBOpdirConfig(rtksw_uint32 unit, rtksw_uint32 port, rtksw_uint32 opdir);
extern ret_t rtl8367c_getAsic1xPBOpdirConfig(rtksw_uint32 unit, rtksw_uint32 port, rtksw_uint32 *pOpdir);
extern ret_t rtl8367c_setAsic1xMBEnConfig(rtksw_uint32 unit, rtksw_uint32 port, rtksw_uint32 enabled);
extern ret_t rtl8367c_getAsic1xMBEnConfig(rtksw_uint32 unit, rtksw_uint32 port, rtksw_uint32 *pEnabled);
extern ret_t rtl8367c_setAsic1xMBOpdirConfig(rtksw_uint32 unit, rtksw_uint32 opdir);
extern ret_t rtl8367c_getAsic1xMBOpdirConfig(rtksw_uint32 unit, rtksw_uint32 *pOpdir);
extern ret_t rtl8367c_setAsic1xProcConfig(rtksw_uint32 unit, rtksw_uint32 port, rtksw_uint32 proc);
extern ret_t rtl8367c_getAsic1xProcConfig(rtksw_uint32 unit, rtksw_uint32 port, rtksw_uint32 *pProc);
extern ret_t rtl8367c_setAsic1xGuestVidx(rtksw_uint32 unit, rtksw_uint32 index);
extern ret_t rtl8367c_getAsic1xGuestVidx(rtksw_uint32 unit, rtksw_uint32 *pIndex);
extern ret_t rtl8367c_setAsic1xGVOpdir(rtksw_uint32 unit, rtksw_uint32 enabled);
extern ret_t rtl8367c_getAsic1xGVOpdir(rtksw_uint32 unit, rtksw_uint32 *pEnabled);
extern ret_t rtl8367c_setAsic1xTrapPriority(rtksw_uint32 unit, rtksw_uint32 priority);
extern ret_t rtl8367c_getAsic1xTrapPriority(rtksw_uint32 unit, rtksw_uint32 *pPriority);


#endif /*_RTL8367C_ASICDRV_DOT1X_H_*/

