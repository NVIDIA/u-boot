#ifndef _RTL8367C_ASICDRV_GREEN_H_
#define _RTL8367C_ASICDRV_GREEN_H_

#include "rtl8367c_asicdrv.h"
#include "rtl8367c_asicdrv_phy.h"

#define PHY_POWERSAVING_REG                         24

extern ret_t rtl8367c_setAsicGreenTrafficType(rtksw_uint32 unit, rtksw_uint32 priority, rtksw_uint32 traffictype);
extern ret_t rtl8367c_getAsicGreenTrafficType(rtksw_uint32 unit, rtksw_uint32 priority, rtksw_uint32* pTraffictype);
extern ret_t rtl8367c_getAsicGreenPortPage(rtksw_uint32 unit, rtksw_uint32 port, rtksw_uint32* pPage);
extern ret_t rtl8367c_getAsicGreenHighPriorityTraffic(rtksw_uint32 unit, rtksw_uint32 port, rtksw_uint32* pIndicator);
extern ret_t rtl8367c_setAsicGreenHighPriorityTraffic(rtksw_uint32 unit, rtksw_uint32 port);
extern ret_t rtl8367c_setAsicGreenEthernet(rtksw_uint32 unit, rtksw_uint32 port, rtksw_uint32 green);
extern ret_t rtl8367c_getAsicGreenEthernet(rtksw_uint32 unit, rtksw_uint32 port, rtksw_uint32* green);
extern ret_t rtl8367c_setAsicPowerSaving(rtksw_uint32 unit, rtksw_uint32 phy, rtksw_uint32 enable);
extern ret_t rtl8367c_getAsicPowerSaving(rtksw_uint32 unit, rtksw_uint32 phy, rtksw_uint32* enable);
#endif /*#ifndef _RTL8367C_ASICDRV_GREEN_H_*/

