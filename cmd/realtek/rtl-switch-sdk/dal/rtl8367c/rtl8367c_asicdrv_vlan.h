#ifndef _RTL8367C_ASICDRV_VLAN_H_
#define _RTL8367C_ASICDRV_VLAN_H_

/****************************************************************/
/* Header File inclusion                                        */
/****************************************************************/
#include "rtl8367c_asicdrv.h"

/****************************************************************/
/* Constant Definition                                          */
/****************************************************************/
#define RTL8367C_PROTOVLAN_GIDX_MAX 3
#define RTL8367C_PROTOVLAN_GROUPNO  4

#define RTL8367C_VLAN_BUSY_CHECK_NO     (10)

#define RTL8367C_VLAN_MBRCFG_LEN    (4)
#define RTL8367C_VLAN_4KTABLE_LEN   (3)

/****************************************************************/
/* Type Definition                                              */
/****************************************************************/
typedef struct  VLANCONFIGUSER
{
    rtksw_uint16  evid;
    rtksw_uint16  mbr;
    rtksw_uint16  fid_msti;
    rtksw_uint16  envlanpol;
    rtksw_uint16  meteridx;
    rtksw_uint16  vbpen;
    rtksw_uint16  vbpri;
}rtl8367c_vlanconfiguser;

typedef struct  USER_VLANTABLE{

    rtksw_uint16  vid;
    rtksw_uint16  mbr;
    rtksw_uint16  untag;
    rtksw_uint16  fid_msti;
    rtksw_uint16  envlanpol;
    rtksw_uint16  meteridx;
    rtksw_uint16  vbpen;
    rtksw_uint16  vbpri;
    rtksw_uint16  ivl_svl;

}rtl8367c_user_vlan4kentry;

typedef enum
{
    FRAME_TYPE_BOTH = 0,
    FRAME_TYPE_TAGGED_ONLY,
    FRAME_TYPE_UNTAGGED_ONLY,
    FRAME_TYPE_MAX_BOUND
} rtl8367c_accframetype;

typedef enum
{
    EG_TAG_MODE_ORI = 0,
    EG_TAG_MODE_KEEP,
    EG_TAG_MODE_PRI_TAG,
    EG_TAG_MODE_REAL_KEEP,
    EG_TAG_MODE_END
} rtl8367c_egtagmode;

typedef enum
{
    PPVLAN_RTKSW_FRAME_TYPE_ETHERNET = 0,
    PPVLAN_FRAME_TYPE_LLC,
    PPVLAN_RTKSW_FRAME_TYPE_RFC1042,
    PPVLAN_FRAME_TYPE_END
} rtl8367c_provlan_frametype;

enum RTL8367C_STPST
{
    STPST_RTKSW_DISABLED = 0,
    STPST_BLOCKING,
    STPST_LEARNING,
    STPST_FORWARDING
};

enum RTL8367C_RESVIDACT
{
    RES_VID_ACT_UNTAG = 0,
    RES_VID_ACT_TAG,
    RES_VID_ACT_END
};

typedef struct
{
    rtl8367c_provlan_frametype  frameType;
    rtksw_uint32                      etherType;
} rtl8367c_protocolgdatacfg;

typedef struct
{
    rtksw_uint32 valid;
    rtksw_uint32 vlan_idx;
    rtksw_uint32 priority;
} rtl8367c_protocolvlancfg;

extern ret_t rtl8367c_setAsicVlanMemberConfig(rtksw_uint32 unit, rtksw_uint32 index, rtl8367c_vlanconfiguser *pVlanCg);
extern ret_t rtl8367c_getAsicVlanMemberConfig(rtksw_uint32 unit, rtksw_uint32 index, rtl8367c_vlanconfiguser *pVlanCg);
extern ret_t rtl8367c_setAsicVlan4kEntry(rtksw_uint32 unit, rtl8367c_user_vlan4kentry *pVlan4kEntry );
extern ret_t rtl8367c_getAsicVlan4kEntry(rtksw_uint32 unit, rtl8367c_user_vlan4kentry *pVlan4kEntry );
extern ret_t rtl8367c_setAsicVlanAccpetFrameType(rtksw_uint32 unit, rtksw_uint32 port, rtl8367c_accframetype frameType);
extern ret_t rtl8367c_getAsicVlanAccpetFrameType(rtksw_uint32 unit, rtksw_uint32 port, rtl8367c_accframetype *pFrameType);
extern ret_t rtl8367c_setAsicVlanIngressFilter(rtksw_uint32 unit, rtksw_uint32 port, rtksw_uint32 enabled);
extern ret_t rtl8367c_getAsicVlanIngressFilter(rtksw_uint32 unit, rtksw_uint32 port, rtksw_uint32 *pEnable);
extern ret_t rtl8367c_setAsicVlanEgressTagMode(rtksw_uint32 unit, rtksw_uint32 port, rtl8367c_egtagmode tagMode);
extern ret_t rtl8367c_getAsicVlanEgressTagMode(rtksw_uint32 unit, rtksw_uint32 port, rtl8367c_egtagmode *pTagMode);
extern ret_t rtl8367c_setAsicVlanPortBasedVID(rtksw_uint32 unit, rtksw_uint32 port, rtksw_uint32 index, rtksw_uint32 pri);
extern ret_t rtl8367c_getAsicVlanPortBasedVID(rtksw_uint32 unit, rtksw_uint32 port, rtksw_uint32 *pIndex, rtksw_uint32 *pPri);
extern ret_t rtl8367c_setAsicVlanProtocolBasedGroupData(rtksw_uint32 unit, rtksw_uint32 index, rtl8367c_protocolgdatacfg *pPbCfg);
extern ret_t rtl8367c_getAsicVlanProtocolBasedGroupData(rtksw_uint32 unit, rtksw_uint32 index, rtl8367c_protocolgdatacfg *pPbCfg);
extern ret_t rtl8367c_setAsicVlanPortAndProtocolBased(rtksw_uint32 unit, rtksw_uint32 port, rtksw_uint32 index, rtl8367c_protocolvlancfg *pPpbCfg);
extern ret_t rtl8367c_getAsicVlanPortAndProtocolBased(rtksw_uint32 unit, rtksw_uint32 port, rtksw_uint32 index, rtl8367c_protocolvlancfg *pPpbCfg);
extern ret_t rtl8367c_setAsicVlanFilter(rtksw_uint32 unit, rtksw_uint32 enabled);
extern ret_t rtl8367c_getAsicVlanFilter(rtksw_uint32 unit, rtksw_uint32* pEnabled);

extern ret_t rtl8367c_setAsicPortBasedFid(rtksw_uint32 unit, rtksw_uint32 port, rtksw_uint32 fid);
extern ret_t rtl8367c_getAsicPortBasedFid(rtksw_uint32 unit, rtksw_uint32 port, rtksw_uint32* pFid);
extern ret_t rtl8367c_setAsicPortBasedFidEn(rtksw_uint32 unit, rtksw_uint32 port, rtksw_uint32 enabled);
extern ret_t rtl8367c_getAsicPortBasedFidEn(rtksw_uint32 unit, rtksw_uint32 port, rtksw_uint32* pEnabled);
extern ret_t rtl8367c_setAsicSpanningTreeStatus(rtksw_uint32 unit, rtksw_uint32 port, rtksw_uint32 msti, rtksw_uint32 state);
extern ret_t rtl8367c_getAsicSpanningTreeStatus(rtksw_uint32 unit, rtksw_uint32 port, rtksw_uint32 msti, rtksw_uint32* pState);
extern ret_t rtl8367c_setAsicVlanUntagDscpPriorityEn(rtksw_uint32 unit, rtksw_uint32 enabled);
extern ret_t rtl8367c_getAsicVlanUntagDscpPriorityEn(rtksw_uint32 unit, rtksw_uint32* enabled);
extern ret_t rtl8367c_setAsicVlanTransparent(rtksw_uint32 unit, rtksw_uint32 port, rtksw_uint32 portmask);
extern ret_t rtl8367c_getAsicVlanTransparent(rtksw_uint32 unit, rtksw_uint32 port, rtksw_uint32 *pPortmask);
extern ret_t rtl8367c_setAsicVlanEgressKeep(rtksw_uint32 unit, rtksw_uint32 port, rtksw_uint32 portmask);
extern ret_t rtl8367c_getAsicVlanEgressKeep(rtksw_uint32 unit, rtksw_uint32 port, rtksw_uint32* pPortmask);
extern ret_t rtl8367c_setReservedVidAction(rtksw_uint32 unit, rtksw_uint32 vid0Action, rtksw_uint32 vid4095Action);
extern ret_t rtl8367c_getReservedVidAction(rtksw_uint32 unit, rtksw_uint32 *pVid0Action, rtksw_uint32 *pVid4095Action);
extern ret_t rtl8367c_setRealKeepRemarkEn(rtksw_uint32 unit, rtksw_uint32 enabled);
extern ret_t rtl8367c_getRealKeepRemarkEn(rtksw_uint32 unit, rtksw_uint32 *pEnabled);
extern ret_t rtl8367c_resetVlan(rtksw_uint32 unit);

#endif /*#ifndef _RTL8367C_ASICDRV_VLAN_H_*/

