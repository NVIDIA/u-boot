#ifndef _RTL8367C_ASICDRV_QOS_H_
#define _RTL8367C_ASICDRV_QOS_H_

#include "rtl8367c_asicdrv.h"

#define RTL8367C_DECISIONPRIMAX    0xFF

/* enum Priority Selection Types */
enum PRIDECISION
{
    PRIDEC_PORT = 0,
    PRIDEC_ACL,
    PRIDEC_DSCP,
    PRIDEC_1Q,
    PRIDEC_1AD,
    PRIDEC_CVLAN,
    PRIDEC_DA,
    PRIDEC_SA,
    PRIDEC_END,
};

/* enum Priority Selection Index */
enum RTL8367C_PRIDEC_TABLE
{
    PRIDEC_IDX0 = 0,
    PRIDEC_IDX1,
    PRIDEC_IDX_END,
};

enum RTL8367C_DOT1P_PRISEL
{
    DOT1P_PRISEL_USER =  0,
    DOT1P_PRISEL_TAG,
    DOT1P_PRISEL_END
};

enum RTL8367C_DSCP_PRISEL
{
    DSCP_PRISEL_INTERNAL =  0,
    DSCP_PRISEL_DSCP,
    DSCP_PRISEL_USER ,
    DSCP_PRISEL_END
};


extern ret_t rtl8367c_setAsicRemarkingDot1pAbility(rtksw_uint32 unit, rtksw_uint32 port, rtksw_uint32 enabled);
extern ret_t rtl8367c_getAsicRemarkingDot1pAbility(rtksw_uint32 unit, rtksw_uint32 port, rtksw_uint32* pEnabled);
extern ret_t rtl8367c_setAsicRemarkingDot1pParameter(rtksw_uint32 unit, rtksw_uint32 priority, rtksw_uint32 newPriority );
extern ret_t rtl8367c_getAsicRemarkingDot1pParameter(rtksw_uint32 unit, rtksw_uint32 priority, rtksw_uint32 *pNewPriority );
extern ret_t rtl8367c_setAsicRemarkingDot1pSrc(rtksw_uint32 unit, rtksw_uint32 type);
extern ret_t rtl8367c_getAsicRemarkingDot1pSrc(rtksw_uint32 unit, rtksw_uint32 *pType);
extern ret_t rtl8367c_setAsicRemarkingDscpAbility(rtksw_uint32 unit, rtksw_uint32 enabled);
extern ret_t rtl8367c_getAsicRemarkingDscpAbility(rtksw_uint32 unit, rtksw_uint32* pEnabled);
extern ret_t rtl8367c_setAsicRemarkingDscpParameter(rtksw_uint32 unit, rtksw_uint32 priority, rtksw_uint32 newDscp );
extern ret_t rtl8367c_getAsicRemarkingDscpParameter(rtksw_uint32 unit, rtksw_uint32 priority, rtksw_uint32* pNewDscp );

extern ret_t rtl8367c_setAsicPriorityDot1qRemapping(rtksw_uint32 unit, rtksw_uint32 srcpriority, rtksw_uint32 priority );
extern ret_t rtl8367c_getAsicPriorityDot1qRemapping(rtksw_uint32 unit, rtksw_uint32 srcpriority, rtksw_uint32 *pPriority );
extern ret_t rtl8367c_setAsicPriorityDscpBased(rtksw_uint32 unit, rtksw_uint32 dscp, rtksw_uint32 priority );
extern ret_t rtl8367c_getAsicPriorityDscpBased(rtksw_uint32 unit, rtksw_uint32 dscp, rtksw_uint32 *pPriority );
extern ret_t rtl8367c_setAsicPriorityPortBased(rtksw_uint32 unit, rtksw_uint32 port, rtksw_uint32 priority );
extern ret_t rtl8367c_getAsicPriorityPortBased(rtksw_uint32 unit, rtksw_uint32 port, rtksw_uint32 *pPriority );
extern ret_t rtl8367c_setAsicPriorityDecision(rtksw_uint32 unit, rtksw_uint32 index, rtksw_uint32 prisrc, rtksw_uint32 decisionPri);
extern ret_t rtl8367c_getAsicPriorityDecision(rtksw_uint32 unit, rtksw_uint32 index, rtksw_uint32 prisrc, rtksw_uint32* pDecisionPri);
extern ret_t rtl8367c_setAsicPriorityToQIDMappingTable(rtksw_uint32 unit, rtksw_uint32 qnum, rtksw_uint32 priority, rtksw_uint32 qid );
extern ret_t rtl8367c_getAsicPriorityToQIDMappingTable(rtksw_uint32 unit, rtksw_uint32 qnum, rtksw_uint32 priority, rtksw_uint32* pQid);
extern ret_t rtl8367c_setAsicOutputQueueMappingIndex(rtksw_uint32 unit, rtksw_uint32 port, rtksw_uint32 qnum );
extern ret_t rtl8367c_getAsicOutputQueueMappingIndex(rtksw_uint32 unit, rtksw_uint32 port, rtksw_uint32 *pQnum );

extern ret_t rtl8367c_setAsicRemarkingDscpSrc(rtksw_uint32 unit, rtksw_uint32 type);
extern ret_t rtl8367c_getAsicRemarkingDscpSrc(rtksw_uint32 unit, rtksw_uint32 *pType);
extern ret_t rtl8367c_setAsicRemarkingDscp2Dscp(rtksw_uint32 unit, rtksw_uint32 dscp, rtksw_uint32 rmkDscp);
extern ret_t rtl8367c_getAsicRemarkingDscp2Dscp(rtksw_uint32 unit, rtksw_uint32 dscp, rtksw_uint32 *pRmkDscp);

extern ret_t rtl8367c_setAsicPortPriorityDecisionIndex(rtksw_uint32 unit, rtksw_uint32 port, rtksw_uint32 index );
extern ret_t rtl8367c_getAsicPortPriorityDecisionIndex(rtksw_uint32 unit, rtksw_uint32 port, rtksw_uint32 *pIndex );

#endif /*#ifndef _RTL8367C_ASICDRV_QOS_H_*/

