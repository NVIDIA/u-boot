#ifndef _RTL8367C_ASICDRV_PORTSECURITY_H_
#define _RTL8367C_ASICDRV_PORTSECURITY_H_

#include "rtl8367c_asicdrv.h"
#include "rtl8367c_asicdrv_unknownMulticast.h"
#include "rtl8367c_asicdrv_phy.h"

/****************************************************************/
/* Type Definition                                              */
/****************************************************************/

#define RTL8367C_MAC7       7
#define RTL8367C_EXTNO       3

#define RTL8367C_RTCT_PAGE          (11)
#define RTL8367C_RTCT_RESULT_A_REG  (27)
#define RTL8367C_RTCT_RESULT_B_REG  (28)
#define RTL8367C_RTCT_RESULT_C_REG  (29)
#define RTL8367C_RTCT_RESULT_D_REG  (30)
#define RTL8367C_RTCT_STATUS_REG    (26)

enum L2_SECURITY_BEHAVE
{
    L2_BEHAVE_FLOODING = 0,
    L2_BEHAVE_DROP,
    L2_BEHAVE_TRAP,
    L2_BEHAVE_END
};

enum L2_UNDA_BEHAVE
{
    L2_UNDA_BEHAVE_FLOODING_PMASK = 0,
    L2_UNDA_BEHAVE_DROP,
    L2_UNDA_BEHAVE_TRAP,
    L2_UNDA_BEHAVE_FLOODING,
    L2_UNDA_BEHAVE_END
};

enum L2_SECURITY_SA_BEHAVE
{
    L2_BEHAVE_SA_FLOODING = 0,
    L2_BEHAVE_SA_DROP,
    L2_BEHAVE_SA_TRAP,
    L2_BEHAVE_SA_COPY28051,
    L2_BEHAVE_SA_END
};

/* enum for port current link speed */
enum SPEEDMODE
{
    SPD_10M = 0,
    SPD_100M,
    SPD_1000M,
    SPD_2500M
};

/* enum for mac link mode */
enum LINKMODE
{
    MAC_NORMAL = 0,
    MAC_FORCE,
};

/* enum for port current link duplex mode */
enum DUPLEXMODE
{
    HALF_DUPLEX = 0,
    FULL_DUPLEX
};

/* enum for port current MST mode */
enum MSTMODE
{
    SLAVE_MODE= 0,
    MASTER_MODE
};


enum EXTMODE
{
    EXT_DISABLE = 0,
    EXT_RGMII,
    EXT_MII_MAC,
    EXT_MII_PHY,
    EXT_TMII_MAC,
    EXT_TMII_PHY,
    EXT_GMII,
    EXT_RMII_MAC,
    EXT_RMII_PHY,
    EXT_SGMII,
    EXT_HSGMII,
    EXT_1000X_100FX,
    EXT_1000X,
    EXT_100FX,
    EXT_RGMII_2,
    EXT_MII_MAC_2,
    EXT_MII_PHY_2,
    EXT_TMII_MAC_2,
    EXT_TMII_PHY_2,
    EXT_RMII_MAC_2,
    EXT_RMII_PHY_2,
    EXT_FIBER_2P5G,
    EXT_END
};

typedef struct  rtl8367c_port_ability_s{
    rtksw_uint16 forcemode;
    rtksw_uint16 mstfault;
    rtksw_uint16 mstmode;
    rtksw_uint16 nway;
    rtksw_uint16 txpause;
    rtksw_uint16 rxpause;
    rtksw_uint16 link;
    rtksw_uint16 duplex;
    rtksw_uint16 speed;
}rtl8367c_port_ability_t;

typedef struct  rtl8367c_port_status_s{

    rtksw_uint16 lpi1000;
    rtksw_uint16 lpi100;
    rtksw_uint16 mstfault;
    rtksw_uint16 mstmode;
    rtksw_uint16 nway;
    rtksw_uint16 txpause;
    rtksw_uint16 rxpause;
    rtksw_uint16 link;
    rtksw_uint16 duplex;
    rtksw_uint16 speed;

}rtl8367c_port_status_t;

typedef struct rtct_result_s
{
    rtksw_uint32      channelAShort;
    rtksw_uint32      channelBShort;
    rtksw_uint32      channelCShort;
    rtksw_uint32      channelDShort;

    rtksw_uint32      channelAOpen;
    rtksw_uint32      channelBOpen;
    rtksw_uint32      channelCOpen;
    rtksw_uint32      channelDOpen;

    rtksw_uint32      channelAMismatch;
    rtksw_uint32      channelBMismatch;
    rtksw_uint32      channelCMismatch;
    rtksw_uint32      channelDMismatch;

    rtksw_uint32      channelALinedriver;
    rtksw_uint32      channelBLinedriver;
    rtksw_uint32      channelCLinedriver;
    rtksw_uint32      channelDLinedriver;

    rtksw_uint32      channelALen;
    rtksw_uint32      channelBLen;
    rtksw_uint32      channelCLen;
    rtksw_uint32      channelDLen;
} rtl8367c_port_rtct_result_t;


/****************************************************************/
/* Driver Proto Type Definition                                 */
/****************************************************************/
extern ret_t rtl8367c_setAsicPortUnknownDaBehavior(rtksw_uint32 unit, rtksw_uint32 port, rtksw_uint32 behavior);
extern ret_t rtl8367c_getAsicPortUnknownDaBehavior(rtksw_uint32 unit, rtksw_uint32 port, rtksw_uint32 *pBehavior);
extern ret_t rtl8367c_setAsicPortUnknownSaBehavior(rtksw_uint32 unit, rtksw_uint32 behavior);
extern ret_t rtl8367c_getAsicPortUnknownSaBehavior(rtksw_uint32 unit, rtksw_uint32 *pBehavior);
extern ret_t rtl8367c_setAsicPortUnmatchedSaBehavior(rtksw_uint32 unit, rtksw_uint32 behavior);
extern ret_t rtl8367c_getAsicPortUnmatchedSaBehavior(rtksw_uint32 unit, rtksw_uint32 *pBehavior);
extern ret_t rtl8367c_setAsicPortUnmatchedSaMoving(rtksw_uint32 unit, rtksw_uint32 port, rtksw_uint32 enabled);
extern ret_t rtl8367c_getAsicPortUnmatchedSaMoving(rtksw_uint32 unit, rtksw_uint32 port, rtksw_uint32 *pEnabled);
extern ret_t rtl8367c_setAsicPortUnknownDaFloodingPortmask(rtksw_uint32 unit, rtksw_uint32 portmask);
extern ret_t rtl8367c_getAsicPortUnknownDaFloodingPortmask(rtksw_uint32 unit, rtksw_uint32 *pPortmask);
extern ret_t rtl8367c_setAsicPortUnknownMulticastFloodingPortmask(rtksw_uint32 unit, rtksw_uint32 portmask);
extern ret_t rtl8367c_getAsicPortUnknownMulticastFloodingPortmask(rtksw_uint32 unit, rtksw_uint32 *pPortmask);
extern ret_t rtl8367c_setAsicPortBcastFloodingPortmask(rtksw_uint32 unit, rtksw_uint32 portmask);
extern ret_t rtl8367c_getAsicPortBcastFloodingPortmask(rtksw_uint32 unit, rtksw_uint32 *pPortmask);
extern ret_t rtl8367c_setAsicPortBlockSpa(rtksw_uint32 unit, rtksw_uint32 port, rtksw_uint32 block);
extern ret_t rtl8367c_getAsicPortBlockSpa(rtksw_uint32 unit, rtksw_uint32 port, rtksw_uint32 *pBlock);
extern ret_t rtl8367c_setAsicPortForceLink(rtksw_uint32 unit, rtksw_uint32 port, rtl8367c_port_ability_t *pPortAbility);
extern ret_t rtl8367c_getAsicPortForceLink(rtksw_uint32 unit, rtksw_uint32 port, rtl8367c_port_ability_t *pPortAbility);
extern ret_t rtl8367c_getAsicPortStatus(rtksw_uint32 unit, rtksw_uint32 port, rtl8367c_port_status_t *pPortStatus);
extern ret_t rtl8367c_setAsicPortForceLinkExt(rtksw_uint32 unit, rtksw_uint32 id, rtl8367c_port_ability_t *pPortAbility);
extern ret_t rtl8367c_getAsicPortForceLinkExt(rtksw_uint32 unit, rtksw_uint32 id, rtl8367c_port_ability_t *pPortAbility);
extern ret_t rtl8367c_setAsicPortExtMode(rtksw_uint32 unit, rtksw_uint32 id, rtksw_uint32 mode);
extern ret_t rtl8367c_getAsicPortExtMode(rtksw_uint32 unit, rtksw_uint32 id, rtksw_uint32 *pMode);
extern ret_t rtl8367c_setAsicPortEnableAll(rtksw_uint32 unit, rtksw_uint32 enable);
extern ret_t rtl8367c_getAsicPortEnableAll(rtksw_uint32 unit, rtksw_uint32 *pEnable);
extern ret_t rtl8367c_setAsicPortSmallIpg(rtksw_uint32 unit, rtksw_uint32 port, rtksw_uint32 enable);
extern ret_t rtl8367c_getAsicPortSmallIpg(rtksw_uint32 unit, rtksw_uint32 port, rtksw_uint32* pEnable);
extern ret_t rtl8367c_setAsicPortLoopback(rtksw_uint32 unit, rtksw_uint32 port, rtksw_uint32 enable);
extern ret_t rtl8367c_getAsicPortLoopback(rtksw_uint32 unit, rtksw_uint32 port, rtksw_uint32 *pEnable);
extern ret_t rtl8367c_setAsicPortRTCTEnable(rtksw_uint32 unit, rtksw_uint32 portmask);
extern ret_t rtl8367c_setAsicPortRTCTDisable(rtksw_uint32 unit, rtksw_uint32 portmask);
extern ret_t rtl8367c_getAsicPortRTCTResult(rtksw_uint32 unit, rtksw_uint32 port, rtl8367c_port_rtct_result_t *pResult);
extern ret_t rtl8367c_sdsReset(rtksw_uint32 unit, rtksw_uint32 id);
extern ret_t rtl8367c_getSdsLinkStatus(rtksw_uint32 unit, rtksw_uint32 ext_id, rtksw_uint32 *pSignalDetect, rtksw_uint32 *pSync, rtksw_uint32 *pLink);
extern ret_t rtl8367c_setSgmiiNway(rtksw_uint32 unit, rtksw_uint32 ext_id, rtksw_uint32 state);
extern ret_t rtl8367c_getSgmiiNway(rtksw_uint32 unit, rtksw_uint32 ext_id, rtksw_uint32 *pState);
extern ret_t rtl8367c_setFiberAbilityExt(rtksw_uint32 unit, rtksw_uint32 ext_id, rtksw_uint32 pause, rtksw_uint32 asypause);
extern ret_t rtl8367c_getFiberAbilityExt(rtksw_uint32 unit, rtksw_uint32 ext_id, rtksw_uint32* pPause, rtksw_uint32* pAsypause);

#endif /*_RTL8367C_ASICDRV_PORTSECURITY_H_*/

