#ifndef _RTL8367C_ASICDRV_EAV_H_
#define _RTL8367C_ASICDRV_EAV_H_

#include "rtl8367c_asicdrv.h"

typedef enum RTL8367C_PTP_TIME_CMD_E
{
    PTP_TIME_READ = 0,
    PTP_TIME_WRITE,
    PTP_TIME_INC,
    PTP_TIME_DEC,
    PTP_TIME_CMD_END
}RTL8367C_PTP_TIME_CMD;

typedef enum RTL8367C_PTP_TIME_ADJ_E
{
    PTP_TIME_ADJ_INC = 0,
    PTP_TIME_ADJ_DEC,
    PTP_TIME_ADJ_END
}RTL8367C_PTP_TIME_ADJ;

typedef enum RTL8367C_PTP_TIME_CTRL_E
{
    PTP_TIME_CTRL_STOP = 0,
    PTP_TIME_CTRL_START,
    PTP_TIME_CTRL_END
}RTL8367C_PTP_TIME_CTRL;

typedef enum RTL8367C_PTP_INTR_IMRS_E
{
    PTP_IMRS_TX_SYNC,
    PTP_IMRS_TX_DELAY_REQ,
    PTP_IMRS_TX_PDELAY_REQ,
    PTP_IMRS_TX_PDELAY_RESP,
    PTP_IMRS_RX_SYNC,
    PTP_IMRS_RX_DELAY_REQ,
    PTP_IMRS_RX_PDELAY_REQ,
    PTP_IMRS_RX_PDELAY_RESP,
    PTP_IMRS_END,
}RTL8367C_PTP_INTR_IMRS;


typedef enum RTL8367C_PTP_PKT_TYPE_E
{
    PTP_PKT_TYPE_TX_SYNC,
    PTP_PKT_TYPE_TX_DELAY_REQ,
    PTP_PKT_TYPE_TX_PDELAY_REQ,
    PTP_PKT_TYPE_TX_PDELAY_RESP,
    PTP_PKT_TYPE_RX_SYNC,
    PTP_PKT_TYPE_RX_DELAY_REQ,
    PTP_PKT_TYPE_RX_PDELAY_REQ,
    PTP_PKT_TYPE_RX_PDELAY_RESP,
    PTP_PKT_TYPE_END,
}RTL8367C_PTP_PKT_TYPE;

typedef struct  rtl8367c_ptp_time_stamp_s{
    rtksw_uint32 sequence_id;
    rtksw_uint32 second;
    rtksw_uint32 nano_second;
}rtl8367c_ptp_time_stamp_t;

#define RTL8367C_PTP_INTR_MASK        0xFF

#define RTL8367C_PTP_PORT_MASK        0x3FF

extern ret_t rtl8367c_setAsicEavMacAddress(rtksw_uint32 unit, ether_addr_t mac);
extern ret_t rtl8367c_getAsicEavMacAddress(rtksw_uint32 unit, ether_addr_t *pMac);
extern ret_t rtl8367c_setAsicEavTpid(rtksw_uint32 unit, rtksw_uint32 outerTag, rtksw_uint32 innerTag);
extern ret_t rtl8367c_getAsicEavTpid(rtksw_uint32 unit, rtksw_uint32* pOuterTag, rtksw_uint32* pInnerTag);
extern ret_t rtl8367c_setAsicEavSysTime(rtksw_uint32 unit, rtksw_uint32 second, rtksw_uint32 nanoSecond);
extern ret_t rtl8367c_getAsicEavSysTime(rtksw_uint32 unit, rtksw_uint32* pSecond, rtksw_uint32* pNanoSecond);
extern ret_t rtl8367c_setAsicEavSysTimeAdjust(rtksw_uint32 unit, rtksw_uint32 type, rtksw_uint32 second, rtksw_uint32 nanoSecond);
extern ret_t rtl8367c_setAsicEavSysTimeCtrl(rtksw_uint32 unit, rtksw_uint32 control);
extern ret_t rtl8367c_getAsicEavSysTimeCtrl(rtksw_uint32 unit, rtksw_uint32* pControl);
extern ret_t rtl8367c_setAsicEavInterruptMask(rtksw_uint32 unit, rtksw_uint32 imr);
extern ret_t rtl8367c_getAsicEavInterruptMask(rtksw_uint32 unit, rtksw_uint32* pImr);
extern ret_t rtl8367c_getAsicEavInterruptStatus(rtksw_uint32 unit, rtksw_uint32* pIms);
extern ret_t rtl8367c_setAsicEavPortInterruptStatus(rtksw_uint32 unit, rtksw_uint32 port, rtksw_uint32 ims);
extern ret_t rtl8367c_getAsicEavPortInterruptStatus(rtksw_uint32 unit, rtksw_uint32 port, rtksw_uint32* pIms);
extern ret_t rtl8367c_setAsicEavPortEnable(rtksw_uint32 unit, rtksw_uint32 port, rtksw_uint32 enabled);
extern ret_t rtl8367c_getAsicEavPortEnable(rtksw_uint32 unit, rtksw_uint32 port, rtksw_uint32 *pEnabled);
extern ret_t rtl8367c_getAsicEavPortTimeStamp(rtksw_uint32 unit, rtksw_uint32 port, rtksw_uint32 type, rtl8367c_ptp_time_stamp_t* timeStamp);

extern ret_t rtl8367c_setAsicEavTrap(rtksw_uint32 unit, rtksw_uint32 port, rtksw_uint32 enabled);
extern ret_t rtl8367c_getAsicEavTrap(rtksw_uint32 unit, rtksw_uint32 port, rtksw_uint32 *pEnabled);
extern ret_t rtl8367c_setAsicEavEnable(rtksw_uint32 unit, rtksw_uint32 port, rtksw_uint32 enabled);
extern ret_t rtl8367c_getAsicEavEnable(rtksw_uint32 unit, rtksw_uint32 port, rtksw_uint32 *pEnabled);
extern ret_t rtl8367c_setAsicEavPriRemapping(rtksw_uint32 unit, rtksw_uint32 srcpriority, rtksw_uint32 priority);
extern ret_t rtl8367c_getAsicEavPriRemapping(rtksw_uint32 unit, rtksw_uint32 srcpriority, rtksw_uint32 *pPriority);

#endif /*#ifndef _RTL8367C_ASICDRV_EAV_H_*/

