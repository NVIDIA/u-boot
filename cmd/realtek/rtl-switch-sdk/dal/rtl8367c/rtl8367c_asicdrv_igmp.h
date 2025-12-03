#ifndef _RTL8367C_ASICDRV_IGMP_H_
#define _RTL8367C_ASICDRV_IGMP_H_

/****************************************************************/
/* Header File inclusion                                        */
/****************************************************************/
#include "rtl8367c_asicdrv.h"

#define RTL8367C_MAX_LEAVE_TIMER        (7)
#define RTL8367C_MAX_QUERY_INT          (0xFFFF)
#define RTL8367C_MAX_ROB_VAR            (7)

#define RTL8367C_IGMP_GOUP_NO           (256)
#define RTL8367C_IGMP_MAX_GOUP          (0xFF)
#define RTL8367C_IGMP_GRP_BLEN          (3)
#define RTL8367C_ROUTER_PORT_INVALID    (0xF)

enum RTL8367C_IGMPTABLE_FULL_OP
{
    TABLE_FULL_FORWARD = 0,
    TABLE_FULL_DROP,
    TABLE_FULL_TRAP,
    TABLE_FULL_OP_END
};

enum RTL8367C_CRC_ERR_OP
{
    CRC_ERR_DROP = 0,
    CRC_ERR_TRAP,
    CRC_ERR_FORWARD,
    CRC_ERR_OP_END
};

enum RTL8367C_IGMP_MLD_PROTOCOL_OP
{
    PROTOCOL_OP_ASIC = 0,
    PROTOCOL_OP_FLOOD,
    PROTOCOL_OP_TRAP,
    PROTOCOL_OP_DROP,
    PROTOCOL_OP_END
};

enum RTL8367C_IGMP_MLD_BYPASS_GROUP
{
    BYPASS_224_0_0_X = 0,
    BYPASS_224_0_1_X,
    BYPASS_239_255_255_X,
    BYPASS_IPV6_00XX,
    BYPASS_GROUP_END
};

typedef struct
{
    rtksw_uint32 p0_timer;
    rtksw_uint32 p1_timer;
    rtksw_uint32 p2_timer;
    rtksw_uint32 p3_timer;
    rtksw_uint32 p4_timer;
    rtksw_uint32 p5_timer;
    rtksw_uint32 p6_timer;
    rtksw_uint32 p7_timer;
    rtksw_uint32 p8_timer;
    rtksw_uint32 p9_timer;
    rtksw_uint32 p10_timer;
    rtksw_uint32 report_supp_flag;

}rtl8367c_igmpgroup;


ret_t rtl8367c_setAsicIgmp(rtksw_uint32 unit, rtksw_uint32 enabled);
ret_t rtl8367c_getAsicIgmp(rtksw_uint32 unit, rtksw_uint32 *pEnabled);
ret_t rtl8367c_setAsicIpMulticastVlanLeaky(rtksw_uint32 unit, rtksw_uint32 port, rtksw_uint32 enabled );
ret_t rtl8367c_getAsicIpMulticastVlanLeaky(rtksw_uint32 unit, rtksw_uint32 port, rtksw_uint32 *pEnabled );
ret_t rtl8367c_setAsicIGMPTableFullOP(rtksw_uint32 unit, rtksw_uint32 operation);
ret_t rtl8367c_getAsicIGMPTableFullOP(rtksw_uint32 unit, rtksw_uint32 *pOperation);
ret_t rtl8367c_setAsicIGMPCRCErrOP(rtksw_uint32 unit, rtksw_uint32 operation);
ret_t rtl8367c_getAsicIGMPCRCErrOP(rtksw_uint32 unit, rtksw_uint32 *pOperation);
ret_t rtl8367c_setAsicIGMPFastLeaveEn(rtksw_uint32 unit, rtksw_uint32 enabled);
ret_t rtl8367c_getAsicIGMPFastLeaveEn(rtksw_uint32 unit, rtksw_uint32 *pEnabled);
ret_t rtl8367c_setAsicIGMPLeaveTimer(rtksw_uint32 unit, rtksw_uint32 leave_timer);
ret_t rtl8367c_getAsicIGMPLeaveTimer(rtksw_uint32 unit, rtksw_uint32 *pLeave_timer);
ret_t rtl8367c_setAsicIGMPQueryInterval(rtksw_uint32 unit, rtksw_uint32 interval);
ret_t rtl8367c_getAsicIGMPQueryInterval(rtksw_uint32 unit, rtksw_uint32 *pInterval);
ret_t rtl8367c_setAsicIGMPRobVar(rtksw_uint32 unit, rtksw_uint32 rob_var);
ret_t rtl8367c_getAsicIGMPRobVar(rtksw_uint32 unit, rtksw_uint32 *pRob_var);
ret_t rtl8367c_setAsicIGMPStaticRouterPort(rtksw_uint32 unit, rtksw_uint32 pmsk);
ret_t rtl8367c_getAsicIGMPStaticRouterPort(rtksw_uint32 unit, rtksw_uint32 *pMsk);
ret_t rtl8367c_setAsicIGMPAllowDynamicRouterPort(rtksw_uint32 unit, rtksw_uint32 pmsk);
ret_t rtl8367c_getAsicIGMPAllowDynamicRouterPort(rtksw_uint32 unit, rtksw_uint32 *pPmsk);
ret_t rtl8367c_getAsicIGMPdynamicRouterPort1(rtksw_uint32 unit, rtksw_uint32 *pPort, rtksw_uint32 *pTimer);
ret_t rtl8367c_getAsicIGMPdynamicRouterPort2(rtksw_uint32 unit, rtksw_uint32 *pPort, rtksw_uint32 *pTimer);
ret_t rtl8367c_setAsicIGMPSuppression(rtksw_uint32 unit, rtksw_uint32 report_supp_enabled, rtksw_uint32 leave_supp_enabled);
ret_t rtl8367c_getAsicIGMPSuppression(rtksw_uint32 unit, rtksw_uint32 *pReport_supp_enabled, rtksw_uint32 *pLeave_supp_enabled);
ret_t rtl8367c_setAsicIGMPQueryRX(rtksw_uint32 unit, rtksw_uint32 port, rtksw_uint32 allow_query);
ret_t rtl8367c_getAsicIGMPQueryRX(rtksw_uint32 unit, rtksw_uint32 port, rtksw_uint32 *pAllow_query);
ret_t rtl8367c_setAsicIGMPReportRX(rtksw_uint32 unit, rtksw_uint32 port, rtksw_uint32 allow_report);
ret_t rtl8367c_getAsicIGMPReportRX(rtksw_uint32 unit, rtksw_uint32 port, rtksw_uint32 *pAllow_report);
ret_t rtl8367c_setAsicIGMPLeaveRX(rtksw_uint32 unit, rtksw_uint32 port, rtksw_uint32 allow_leave);
ret_t rtl8367c_getAsicIGMPLeaveRX(rtksw_uint32 unit, rtksw_uint32 port, rtksw_uint32 *pAllow_leave);
ret_t rtl8367c_setAsicIGMPMRPRX(rtksw_uint32 unit, rtksw_uint32 port, rtksw_uint32 allow_mrp);
ret_t rtl8367c_getAsicIGMPMRPRX(rtksw_uint32 unit, rtksw_uint32 port, rtksw_uint32 *pAllow_mrp);
ret_t rtl8367c_setAsicIGMPMcDataRX(rtksw_uint32 unit, rtksw_uint32 port, rtksw_uint32 allow_mcdata);
ret_t rtl8367c_getAsicIGMPMcDataRX(rtksw_uint32 unit, rtksw_uint32 port, rtksw_uint32 *pAllow_mcdata);
ret_t rtl8367c_setAsicIGMPv1Opeartion(rtksw_uint32 unit, rtksw_uint32 port, rtksw_uint32 igmpv1_op);
ret_t rtl8367c_getAsicIGMPv1Opeartion(rtksw_uint32 unit, rtksw_uint32 port, rtksw_uint32 *pIgmpv1_op);
ret_t rtl8367c_setAsicIGMPv2Opeartion(rtksw_uint32 unit, rtksw_uint32 port, rtksw_uint32 igmpv2_op);
ret_t rtl8367c_getAsicIGMPv2Opeartion(rtksw_uint32 unit, rtksw_uint32 port, rtksw_uint32 *pIgmpv2_op);
ret_t rtl8367c_setAsicIGMPv3Opeartion(rtksw_uint32 unit, rtksw_uint32 port, rtksw_uint32 igmpv3_op);
ret_t rtl8367c_getAsicIGMPv3Opeartion(rtksw_uint32 unit, rtksw_uint32 port, rtksw_uint32 *pIgmpv3_op);
ret_t rtl8367c_setAsicMLDv1Opeartion(rtksw_uint32 unit, rtksw_uint32 port, rtksw_uint32 mldv1_op);
ret_t rtl8367c_getAsicMLDv1Opeartion(rtksw_uint32 unit, rtksw_uint32 port, rtksw_uint32 *pMldv1_op);
ret_t rtl8367c_setAsicMLDv2Opeartion(rtksw_uint32 unit, rtksw_uint32 port, rtksw_uint32 mldv2_op);
ret_t rtl8367c_getAsicMLDv2Opeartion(rtksw_uint32 unit, rtksw_uint32 port, rtksw_uint32 *pMldv2_op);
ret_t rtl8367c_setAsicIGMPPortMAXGroup(rtksw_uint32 unit, rtksw_uint32 port, rtksw_uint32 max_group);
ret_t rtl8367c_getAsicIGMPPortMAXGroup(rtksw_uint32 unit, rtksw_uint32 port, rtksw_uint32 *pMax_group);
ret_t rtl8367c_getAsicIGMPPortCurrentGroup(rtksw_uint32 unit, rtksw_uint32 port, rtksw_uint32 *pCurrent_group);
ret_t rtl8367c_getAsicIGMPGroup(rtksw_uint32 unit, rtksw_uint32 idx, rtksw_uint32 *pValid, rtl8367c_igmpgroup *pGrp);
ret_t rtl8367c_setAsicIpMulticastPortIsoLeaky(rtksw_uint32 unit, rtksw_uint32 port, rtksw_uint32 enabled);
ret_t rtl8367c_getAsicIpMulticastPortIsoLeaky(rtksw_uint32 unit, rtksw_uint32 port, rtksw_uint32 *pEnabled);
ret_t rtl8367c_setAsicIGMPReportLeaveFlood(rtksw_uint32 unit, rtksw_uint32 flood);
ret_t rtl8367c_getAsicIGMPReportLeaveFlood(rtksw_uint32 unit, rtksw_uint32 *pFlood);
ret_t rtl8367c_setAsicIGMPDropLeaveZero(rtksw_uint32 unit, rtksw_uint32 drop);
ret_t rtl8367c_getAsicIGMPDropLeaveZero(rtksw_uint32 unit, rtksw_uint32 *pDrop);
ret_t rtl8367c_setAsicIGMPBypassStormCTRL(rtksw_uint32 unit, rtksw_uint32 bypass);
ret_t rtl8367c_getAsicIGMPBypassStormCTRL(rtksw_uint32 unit, rtksw_uint32 *pBypass);
ret_t rtl8367c_setAsicIGMPIsoLeaky(rtksw_uint32 unit, rtksw_uint32 leaky);
ret_t rtl8367c_getAsicIGMPIsoLeaky(rtksw_uint32 unit, rtksw_uint32 *pLeaky);
ret_t rtl8367c_setAsicIGMPVLANLeaky(rtksw_uint32 unit, rtksw_uint32 leaky);
ret_t rtl8367c_getAsicIGMPVLANLeaky(rtksw_uint32 unit, rtksw_uint32 *pLeaky);
ret_t rtl8367c_setAsicIGMPBypassGroup(rtksw_uint32 unit, rtksw_uint32 bypassType, rtksw_uint32 enabled);
ret_t rtl8367c_getAsicIGMPBypassGroup(rtksw_uint32 unit, rtksw_uint32 bypassType, rtksw_uint32 *pEnabled);

#endif /*#ifndef _RTL8367C_ASICDRV_IGMP_H_*/

