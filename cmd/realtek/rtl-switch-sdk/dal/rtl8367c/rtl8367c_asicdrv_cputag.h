#ifndef _RTL8367C_ASICDRV_CPUTAG_H_
#define _RTL8367C_ASICDRV_CPUTAG_H_

#include "rtl8367c_asicdrv.h"

enum CPUTAG_INSERT_MODE
{
    CPUTAG_INSERT_TO_ALL = 0,
    CPUTAG_INSERT_TO_TRAPPING,
    CPUTAG_INSERT_TO_NO,
    CPUTAG_INSERT_END
};

extern ret_t rtl8367c_setAsicCputagEnable(rtksw_uint32 unit, rtksw_uint32 enabled);
extern ret_t rtl8367c_getAsicCputagEnable(rtksw_uint32 unit, rtksw_uint32 *pEnabled);
extern ret_t rtl8367c_setAsicCputagTrapPort(rtksw_uint32 unit, rtksw_uint32 port);
extern ret_t rtl8367c_getAsicCputagTrapPort(rtksw_uint32 unit, rtksw_uint32 *pPort);
extern ret_t rtl8367c_setAsicCputagPortmask(rtksw_uint32 unit, rtksw_uint32 portmask);
extern ret_t rtl8367c_getAsicCputagPortmask(rtksw_uint32 unit, rtksw_uint32 *pPmsk);
extern ret_t rtl8367c_setAsicCputagInsertMode(rtksw_uint32 unit, rtksw_uint32 mode);
extern ret_t rtl8367c_getAsicCputagInsertMode(rtksw_uint32 unit, rtksw_uint32 *pMode);
extern ret_t rtl8367c_setAsicCputagPriorityRemapping(rtksw_uint32 unit, rtksw_uint32 srcPri, rtksw_uint32 newPri);
extern ret_t rtl8367c_getAsicCputagPriorityRemapping(rtksw_uint32 unit, rtksw_uint32 srcPri, rtksw_uint32 *pNewPri);
extern ret_t rtl8367c_setAsicCputagPosition(rtksw_uint32 unit, rtksw_uint32 postion);
extern ret_t rtl8367c_getAsicCputagPosition(rtksw_uint32 unit, rtksw_uint32* pPostion);
extern ret_t rtl8367c_setAsicCputagMode(rtksw_uint32 unit, rtksw_uint32 mode);
extern ret_t rtl8367c_getAsicCputagMode(rtksw_uint32 unit, rtksw_uint32 *pMode);
extern ret_t rtl8367c_setAsicCputagRxMinLength(rtksw_uint32 unit, rtksw_uint32 mode);
extern ret_t rtl8367c_getAsicCputagRxMinLength(rtksw_uint32 unit, rtksw_uint32 *pMode);

#endif /*#ifndef _RTL8367C_ASICDRV_CPUTAG_H_*/

