#ifndef _RTL8367C_ASICDRV_I2C_H_
#define _RTL8367C_ASICDRV_I2C_H_
#include "../../rtk_types.h"
#include "rtl8367c_asicdrv.h"


#define TIMEROUT_FOR_MICROSEMI (0x400)

#define GPIO_INPUT 1
#define GPIO_OUTPUT 2

extern ret_t rtl8367c_setAsicI2C_checkBusIdle(rtksw_uint32 unit);
extern ret_t rtl8367c_setAsicI2CStartCmd(rtksw_uint32 unit);
extern ret_t rtl8367c_setAsicI2CStopCmd(rtksw_uint32 unit);
extern ret_t rtl8367c_setAsicI2CTxOneCharCmd(rtksw_uint32 unit, rtksw_uint8 oneChar);
extern ret_t rtl8367c_setAsicI2CcheckRxAck(rtksw_uint32 unit);
extern ret_t rtl8367c_setAsicI2CRxOneCharCmd(rtksw_uint32 unit, rtksw_uint8 *pValue);
extern ret_t rtl8367c_setAsicI2CTxAckCmd(rtksw_uint32 unit);
extern ret_t rtl8367c_setAsicI2CTxNoAckCmd(rtksw_uint32 unit);
extern ret_t rtl8367c_setAsicI2CSoftRSTseqCmd(rtksw_uint32 unit);
extern ret_t rtl8367c_setAsicI2CGpioPinGroup(rtksw_uint32 unit, rtksw_uint32 pinGroup_ID);
extern ret_t rtl8367c_getAsicI2CGpioPinGroup(rtksw_uint32 unit, rtksw_uint32 *pPinGroup_ID);





#endif /*#ifndef _RTL8367C_ASICDRV_I2C_H_*/

