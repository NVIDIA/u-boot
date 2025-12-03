#ifndef _RTL8367C_ASICDRV_LUT_H_
#define _RTL8367C_ASICDRV_LUT_H_

#include "rtl8367c_asicdrv.h"

#define RTL8367C_LUT_AGETIMERMAX        (7)
#define RTL8367C_LUT_AGESPEEDMAX        (3)
#define RTL8367C_LUT_LEARNLIMITMAX      (0x1040)
#define RTL8367C_LUT_ADDRMAX            (0x103F)
#define RTL8367C_LUT_IPMCGRP_TABLE_MAX  (0x3F)
#define RTL8367C_LUT_ENTRY_SIZE         (6)
#define RTL8367C_LUT_BUSY_CHECK_NO      (10)

#define RTL8367C_LUT_TABLE_SIZE         (6)

enum RTL8367C_LUTHASHMETHOD{

    LUTHASHMETHOD_SVL=0,
    LUTHASHMETHOD_IVL,
    LUTHASHMETHOD_END,
};


enum RTL8367C_LRNOVERACT{

    LRNOVERACT_FORWARD=0,
    LRNOVERACT_DROP,
    LRNOVERACT_TRAP,
    LRNOVERACT_END,
};

enum RTL8367C_LUTREADMETHOD{

    LUTREADMETHOD_MAC =0,
    LUTREADMETHOD_ADDRESS,
    LUTREADMETHOD_NEXT_ADDRESS,
    LUTREADMETHOD_NEXT_L2UC,
    LUTREADMETHOD_NEXT_L2MC,
    LUTREADMETHOD_NEXT_L3MC,
    LUTREADMETHOD_NEXT_L2L3MC,
    LUTREADMETHOD_NEXT_L2UCSPA,
};

enum RTL8367C_FLUSHMODE
{
    FLUSHMDOE_PORT = 0,
    FLUSHMDOE_VID,
    FLUSHMDOE_FID,
    FLUSHMDOE_END,
};

enum RTL8367C_FLUSHTYPE
{
    FLUSHTYPE_DYNAMIC = 0,
    FLUSHTYPE_BOTH,
    FLUSHTYPE_END,
};


typedef struct LUTTABLE{

    ipaddr_t sip;
    ipaddr_t dip;
    ether_addr_t mac;
    rtksw_uint16 ivl_svl:1;
    rtksw_uint16 cvid_fid:12;
    rtksw_uint16 fid:4;
    rtksw_uint16 efid:3;

    rtksw_uint16 nosalearn:1;
    rtksw_uint16 da_block:1;
    rtksw_uint16 sa_block:1;
    rtksw_uint16 auth:1;
    rtksw_uint16 lut_pri:3;
    rtksw_uint16 sa_en:1;
    rtksw_uint16 fwd_en:1;
    rtksw_uint16 mbr:11;
    rtksw_uint16 spa:4;
    rtksw_uint16 age:3;
    rtksw_uint16 l3lookup:1;
    rtksw_uint16 igmp_asic:1;
    rtksw_uint16 igmpidx:8;

    rtksw_uint16 lookup_hit:1;
    rtksw_uint16 lookup_busy:1;
    rtksw_uint16 address:13;

    rtksw_uint16 l3vidlookup:1;
    rtksw_uint16 l3_vid:12;

    rtksw_uint16 wait_time;

}rtl8367c_luttb;

extern ret_t rtl8367c_setAsicLutIpMulticastLookup(rtksw_uint32 unit, rtksw_uint32 enabled);
extern ret_t rtl8367c_getAsicLutIpMulticastLookup(rtksw_uint32 unit, rtksw_uint32* pEnabled);
extern ret_t rtl8367c_setAsicLutIpMulticastVidLookup(rtksw_uint32 unit, rtksw_uint32 enabled);
extern ret_t rtl8367c_getAsicLutIpMulticastVidLookup(rtksw_uint32 unit, rtksw_uint32* pEnabled);
extern ret_t rtl8367c_setAsicLutAgeTimerSpeed(rtksw_uint32 unit, rtksw_uint32 timer, rtksw_uint32 speed);
extern ret_t rtl8367c_getAsicLutAgeTimerSpeed(rtksw_uint32 unit, rtksw_uint32* pTimer, rtksw_uint32* pSpeed);
extern ret_t rtl8367c_setAsicLutCamTbUsage(rtksw_uint32 unit, rtksw_uint32 enabled);
extern ret_t rtl8367c_getAsicLutCamTbUsage(rtksw_uint32 unit, rtksw_uint32* pEnabled);
extern ret_t rtl8367c_getAsicLutCamType(rtksw_uint32 unit, rtksw_uint32* pType);
extern ret_t rtl8367c_setAsicLutLearnLimitNo(rtksw_uint32 unit, rtksw_uint32 port, rtksw_uint32 number);
extern ret_t rtl8367c_getAsicLutLearnLimitNo(rtksw_uint32 unit, rtksw_uint32 port, rtksw_uint32* pNumber);
extern ret_t rtl8367c_setAsicSystemLutLearnLimitNo(rtksw_uint32 unit, rtksw_uint32 number);
extern ret_t rtl8367c_getAsicSystemLutLearnLimitNo(rtksw_uint32 unit, rtksw_uint32 *pNumber);
extern ret_t rtl8367c_setAsicLutLearnOverAct(rtksw_uint32 unit, rtksw_uint32 action);
extern ret_t rtl8367c_getAsicLutLearnOverAct(rtksw_uint32 unit, rtksw_uint32* pAction);
extern ret_t rtl8367c_setAsicSystemLutLearnOverAct(rtksw_uint32 unit, rtksw_uint32 action);
extern ret_t rtl8367c_getAsicSystemLutLearnOverAct(rtksw_uint32 unit, rtksw_uint32 *pAction);
extern ret_t rtl8367c_setAsicSystemLutLearnPortMask(rtksw_uint32 unit, rtksw_uint32 portmask);
extern ret_t rtl8367c_getAsicSystemLutLearnPortMask(rtksw_uint32 unit, rtksw_uint32 *pPortmask);
extern ret_t rtl8367c_setAsicL2LookupTb(rtksw_uint32 unit, rtl8367c_luttb *pL2Table);
extern ret_t rtl8367c_getAsicL2LookupTb(rtksw_uint32 unit, rtksw_uint32 method, rtl8367c_luttb *pL2Table);
extern ret_t rtl8367c_getAsicLutLearnNo(rtksw_uint32 unit, rtksw_uint32 port, rtksw_uint32* pNumber);
extern ret_t rtl8367c_setAsicLutIpLookupMethod(rtksw_uint32 unit, rtksw_uint32 type);
extern ret_t rtl8367c_getAsicLutIpLookupMethod(rtksw_uint32 unit, rtksw_uint32* pType);
extern ret_t rtl8367c_setAsicLutForceFlush(rtksw_uint32 unit, rtksw_uint32 portmask);
extern ret_t rtl8367c_getAsicLutForceFlushStatus(rtksw_uint32 unit, rtksw_uint32 *pPortmask);
extern ret_t rtl8367c_setAsicLutFlushMode(rtksw_uint32 unit, rtksw_uint32 mode);
extern ret_t rtl8367c_getAsicLutFlushMode(rtksw_uint32 unit, rtksw_uint32* pMode);
extern ret_t rtl8367c_setAsicLutFlushType(rtksw_uint32 unit, rtksw_uint32 type);
extern ret_t rtl8367c_getAsicLutFlushType(rtksw_uint32 unit, rtksw_uint32* pType);
extern ret_t rtl8367c_setAsicLutFlushVid(rtksw_uint32 unit, rtksw_uint32 vid);
extern ret_t rtl8367c_getAsicLutFlushVid(rtksw_uint32 unit, rtksw_uint32* pVid);
extern ret_t rtl8367c_setAsicLutFlushFid(rtksw_uint32 unit, rtksw_uint32 fid);
extern ret_t rtl8367c_getAsicLutFlushFid(rtksw_uint32 unit, rtksw_uint32* pFid);
extern ret_t rtl8367c_setAsicLutDisableAging(rtksw_uint32 unit, rtksw_uint32 port, rtksw_uint32 disabled);
extern ret_t rtl8367c_getAsicLutDisableAging(rtksw_uint32 unit, rtksw_uint32 port, rtksw_uint32 *pDisabled);
extern ret_t rtl8367c_setAsicLutIPMCGroup(rtksw_uint32 unit, rtksw_uint32 index, ipaddr_t group_addr, rtksw_uint32 vid, rtksw_uint32 pmask, rtksw_uint32 valid);
extern ret_t rtl8367c_getAsicLutIPMCGroup(rtksw_uint32 unit, rtksw_uint32 index, ipaddr_t *pGroup_addr, rtksw_uint32 *pVid, rtksw_uint32 *pPmask, rtksw_uint32 *pValid);
extern ret_t rtl8367c_setAsicLutLinkDownForceAging(rtksw_uint32 unit, rtksw_uint32 enable);
extern ret_t rtl8367c_getAsicLutLinkDownForceAging(rtksw_uint32 unit, rtksw_uint32 *pEnable);
extern ret_t rtl8367c_setAsicLutFlushAll(rtksw_uint32 unit);
extern ret_t rtl8367c_getAsicLutFlushAllStatus(rtksw_uint32 unit, rtksw_uint32 *pBusyStatus);
extern ret_t rtl8367c_setAsicLutIpmcFwdRouterPort(rtksw_uint32 unit, rtksw_uint32 enable);
extern ret_t rtl8367c_getAsicLutIpmcFwdRouterPort(rtksw_uint32 unit, rtksw_uint32 *pEnable);

#endif /*_RTL8367C_ASICDRV_LUT_H_*/

