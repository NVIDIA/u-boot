#ifndef _RTL8367C_ASICDRV_INTERRUPT_H_
#define _RTL8367C_ASICDRV_INTERRUPT_H_

#include "rtl8367c_asicdrv.h"

typedef enum RTL8367C_INTR_IMRS_E
{
    IMRS_LINK_CHANGE,
    IMRS_METER_EXCEED,
    IMRS_L2_LEARN,
    IMRS_SPEED_CHANGE,
    IMRS_SPECIAL_CONGESTION,
    IMRS_GREEN_FEATURE,
    IMRS_LOOP_DETECTION,
    IMRS_8051,
    IMRS_CABLE_DIAG,
    IMRS_ACL,
    IMRS_PTP1588,
    IMRS_SLIENT,
    IMRS_THERMAL,
    IMRS_THERMAL_METER_LOW,
    IMRS_THERMAL_METER_HIGH,
    IMRS_END,
}RTL8367C_INTR_IMRS;

typedef enum RTL8367C_INTR_INDICATOR_E
{
    INTRST_L2_LEARN = 0,
    INTRST_SPEED_CHANGE,
    INTRST_SPECIAL_CONGESTION,
    INTRST_RTKSW_PORT_LINKDOWN,
    INTRST_RTKSW_PORT_LINKUP,
    INTRST_METER0_15,
    INTRST_METER16_31,
    INTRST_RLDP_LOOPED,
    INTRST_RLDP_RELEASED,
    INTRST_SYS_LEARN,
    INTRST_END,
}RTL8367C_INTR_INDICATOR;

extern ret_t rtl8367c_setAsicInterruptPolarity(rtksw_uint32 unit, rtksw_uint32 polarity);
extern ret_t rtl8367c_getAsicInterruptPolarity(rtksw_uint32 unit, rtksw_uint32* pPolarity);
extern ret_t rtl8367c_setAsicInterruptMask(rtksw_uint32 unit, rtksw_uint32 imr);
extern ret_t rtl8367c_getAsicInterruptMask(rtksw_uint32 unit, rtksw_uint32* pImr);
extern ret_t rtl8367c_setAsicInterruptStatus(rtksw_uint32 unit, rtksw_uint32 ims);
extern ret_t rtl8367c_getAsicInterruptStatus(rtksw_uint32 unit, rtksw_uint32* pIms);
extern ret_t rtl8367c_setAsicInterruptRelatedStatus(rtksw_uint32 unit, rtksw_uint32 type, rtksw_uint32 status);
extern ret_t rtl8367c_getAsicInterruptRelatedStatus(rtksw_uint32 unit, rtksw_uint32 type, rtksw_uint32* pStatus);


#endif /*#ifndef _RTL8367C_ASICDRV_INTERRUPT_H_*/

