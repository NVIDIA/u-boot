#ifndef _RTL8367C_ASICDRV_PORTISOLATION_H_
#define _RTL8367C_ASICDRV_PORTISOLATION_H_

#include "rtl8367c_asicdrv.h"

extern ret_t rtl8367c_setAsicPortIsolationPermittedPortmask(rtksw_uint32 unit, rtksw_uint32 port, rtksw_uint32 permitPortmask);
extern ret_t rtl8367c_getAsicPortIsolationPermittedPortmask(rtksw_uint32 unit, rtksw_uint32 port, rtksw_uint32 *pPermitPortmask);
extern ret_t rtl8367c_setAsicPortIsolationEfid(rtksw_uint32 unit, rtksw_uint32 port, rtksw_uint32 efid);
extern ret_t rtl8367c_getAsicPortIsolationEfid(rtksw_uint32 unit, rtksw_uint32 port, rtksw_uint32 *pEfid);

#endif /*_RTL8367C_ASICDRV_PORTISOLATION_H_*/
