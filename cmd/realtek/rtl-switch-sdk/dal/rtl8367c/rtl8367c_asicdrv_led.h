#ifndef _RTL8367C_ASICDRV_LED_H_
#define _RTL8367C_ASICDRV_LED_H_

#include "rtl8367c_asicdrv.h"

#define RTL8367C_LEDGROUPNO                 3
#define RTL8367C_LEDGROUPMASK               0x7
#define RTL8367C_LED_FORCE_MODE_BASE        RTL8367C_REG_CPU_FORCE_LED0_CFG0
#define RTL8367C_LED_FORCE_CTRL             RTL8367C_REG_CPU_FORCE_LED_CFG

enum RTL8367C_LEDOP{

    LEDOP_SCAN0=0,
    LEDOP_SCAN1,
    LEDOP_PARALLEL,
    LEDOP_SERIAL,
    LEDOP_END,
};

enum RTL8367C_LEDSERACT{

    LEDSERACT_HIGH=0,
    LEDSERACT_LOW,
    LEDSERACT_MAX,
};

enum RTL8367C_LEDSER{

    LEDSER_16G=0,
    LEDSER_8G,
    LEDSER_MAX,
};

enum RTL8367C_LEDCONF{

    LEDCONF_LEDOFF=0,
    LEDCONF_DUPCOL,
    LEDCONF_LINK_ACT,
    LEDCONF_SPD1000,
    LEDCONF_SPD100,
    LEDCONF_SPD10,
    LEDCONF_SPD1000ACT,
    LEDCONF_SPD100ACT,
    LEDCONF_SPD10ACT,
    LEDCONF_SPD10010ACT,
    LEDCONF_LOOPDETECT,
    LEDCONF_EEE,
    LEDCONF_LINKRX,
    LEDCONF_LINKTX,
    LEDCONF_MASTER,
    LEDCONF_ACT,
    LEDCONF_END
};

enum RTL8367C_LEDBLINKRATE{

    LEDBLINKRATE_32MS=0,
    LEDBLINKRATE_64MS,
    LEDBLINKRATE_128MS,
    LEDBLINKRATE_256MS,
    LEDBLINKRATE_512MS,
    LEDBLINKRATE_1024MS,
    LEDBLINKRATE_48MS,
    LEDBLINKRATE_96MS,
    LEDBLINKRATE_END,
};

enum RTL8367C_LEDFORCEMODE{

    LEDFORCEMODE_NORMAL=0,
    LEDFORCEMODE_BLINK,
    LEDFORCEMODE_OFF,
    LEDFORCEMODE_ON,
    LEDFORCEMODE_END,
};

enum RTL8367C_LEDFORCERATE{

    LEDFORCERATE_512MS=0,
    LEDFORCERATE_1024MS,
    LEDFORCERATE_2048MS,
    LEDFORCERATE_NORMAL,
    LEDFORCERATE_END,

};

enum RTL8367C_LEDMODE
{
    RTL8367C_LED_MODE_0 = 0,
    RTL8367C_LED_MODE_1,
    RTL8367C_LED_MODE_2,
    RTL8367C_LED_MODE_3,
    RTL8367C_LED_MODE_END
};

extern ret_t rtl8367c_setAsicLedIndicateInfoConfig(rtksw_uint32 unit, rtksw_uint32 ledno, rtksw_uint32 config);
extern ret_t rtl8367c_getAsicLedIndicateInfoConfig(rtksw_uint32 unit, rtksw_uint32 ledno, rtksw_uint32* pConfig);
extern ret_t rtl8367c_setAsicForceLed(rtksw_uint32 unit, rtksw_uint32 port, rtksw_uint32 group, rtksw_uint32 mode);
extern ret_t rtl8367c_getAsicForceLed(rtksw_uint32 unit, rtksw_uint32 port, rtksw_uint32 group, rtksw_uint32* pMode);
extern ret_t rtl8367c_setAsicForceGroupLed(rtksw_uint32 unit, rtksw_uint32 groupmask, rtksw_uint32 mode);
extern ret_t rtl8367c_getAsicForceGroupLed(rtksw_uint32 unit, rtksw_uint32* groupmask, rtksw_uint32* pMode);
extern ret_t rtl8367c_setAsicLedBlinkRate(rtksw_uint32 unit, rtksw_uint32 blinkRate);
extern ret_t rtl8367c_getAsicLedBlinkRate(rtksw_uint32 unit, rtksw_uint32* pBlinkRate);
extern ret_t rtl8367c_setAsicLedForceBlinkRate(rtksw_uint32 unit, rtksw_uint32 blinkRate);
extern ret_t rtl8367c_getAsicLedForceBlinkRate(rtksw_uint32 unit, rtksw_uint32* pBlinkRate);
extern ret_t rtl8367c_setAsicLedGroupMode(rtksw_uint32 unit, rtksw_uint32 mode);
extern ret_t rtl8367c_getAsicLedGroupMode(rtksw_uint32 unit, rtksw_uint32* pMode);
extern ret_t rtl8367c_setAsicLedGroupEnable(rtksw_uint32 unit, rtksw_uint32 group, rtksw_uint32 portmask);
extern ret_t rtl8367c_getAsicLedGroupEnable(rtksw_uint32 unit, rtksw_uint32 group, rtksw_uint32 *portmask);
extern ret_t rtl8367c_setAsicLedOperationMode(rtksw_uint32 unit, rtksw_uint32 mode);
extern ret_t rtl8367c_getAsicLedOperationMode(rtksw_uint32 unit, rtksw_uint32 *mode);
extern ret_t rtl8367c_setAsicLedSerialModeConfig(rtksw_uint32 unit, rtksw_uint32 active, rtksw_uint32 serimode);
extern ret_t rtl8367c_getAsicLedSerialModeConfig(rtksw_uint32 unit, rtksw_uint32 *active, rtksw_uint32 *serimode);
extern ret_t rtl8367c_setAsicLedOutputEnable(rtksw_uint32 unit, rtksw_uint32 enabled);
extern ret_t rtl8367c_getAsicLedOutputEnable(rtksw_uint32 unit, rtksw_uint32 *ptr_enabled);
extern ret_t rtl8367c_setAsicLedSerialOutput(rtksw_uint32 unit, rtksw_uint32 output, rtksw_uint32 pmask);
extern ret_t rtl8367c_getAsicLedSerialOutput(rtksw_uint32 unit, rtksw_uint32 *pOutput, rtksw_uint32 *pPmask);


#endif /*#ifndef _RTL8367C_ASICDRV_LED_H_*/

