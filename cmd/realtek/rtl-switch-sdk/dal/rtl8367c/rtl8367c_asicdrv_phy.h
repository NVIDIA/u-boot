#ifndef _RTL8367C_ASICDRV_PHY_H_
#define _RTL8367C_ASICDRV_PHY_H_

#include "rtl8367c_asicdrv.h"

#define RTL8367C_PHY_REGNOMAX           0x1F
#define RTL8367C_PHY_EXTERNALMAX        0x7

#define RTL8367C_PHY_BASE               0x2000
#define RTL8367C_PHY_EXT_BASE           0xA000

#define RTL8367C_PHY_OFFSET             5
#define RTL8367C_PHY_EXT_OFFSET         9

#define RTL8367C_PHY_PAGE_ADDRESS       31


extern ret_t rtl8367c_setAsicPHYReg(rtksw_uint32 uint, rtksw_uint32 phyNo, rtksw_uint32 phyAddr, rtksw_uint32 regData );
extern ret_t rtl8367c_getAsicPHYReg(rtksw_uint32 uint, rtksw_uint32 phyNo, rtksw_uint32 phyAddr, rtksw_uint32* pRegData );
extern ret_t rtl8367c_setAsicPHYOCPReg(rtksw_uint32 uint, rtksw_uint32 phyNo, rtksw_uint32 ocpAddr, rtksw_uint32 ocpData );
extern ret_t rtl8367c_getAsicPHYOCPReg(rtksw_uint32 uint, rtksw_uint32 phyNo, rtksw_uint32 ocpAddr, rtksw_uint32 *pRegData );
extern ret_t rtl8367c_setAsicSdsReg(rtksw_uint32 uint, rtksw_uint32 sdsId, rtksw_uint32 sdsReg, rtksw_uint32 sdsPage,  rtksw_uint32 value);
extern ret_t rtl8367c_getAsicSdsReg(rtksw_uint32 uint, rtksw_uint32 sdsId, rtksw_uint32 sdsReg, rtksw_uint32 sdsPage, rtksw_uint32 *value);
extern ret_t rtl8367c_setAsicPHYSram(rtksw_uint32 uint, rtksw_uint32 phyNo, rtksw_uint32 sramAddr, rtksw_uint32 sramData );


#endif /*#ifndef _RTL8367C_ASICDRV_PHY_H_*/

