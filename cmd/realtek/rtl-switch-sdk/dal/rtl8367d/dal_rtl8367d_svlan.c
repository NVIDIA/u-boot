/*
 * Copyright (C) 2013 Realtek Semiconductor Corp.
 * All Rights Reserved.
 *
 * This program is the proprietary software of Realtek Semiconductor
 * Corporation and/or its licensors, and only be used, duplicated,
 * modified or distributed under the authorized license from Realtek.
 *
 * ANY USE OF THE SOFTWARE OTHER THAN AS AUTHORIZED UNDER
 * THIS LICENSE OR COPYRIGHT LAW IS PROHIBITED.
 *
 * $Revision$
 * $Date$
 *
 * Purpose : RTK switch high-level API for RTL8367/RTL8367D
 * Feature : Here is a list of all functions and variables in SVLAN module.
 *
 */

#include "../../rtk_switch.h"
#include "../../rtk_error.h"
#include "dal_rtl8367d_svlan.h"
#include "dal_rtl8367d_vlan.h"
#include "rtl8367d_asicdrv.h"

#include "../dal_mgmts.h"
#include "../../osal/lib.h"


/* Function Name:
 *      dal_rtl8367d_svlaninit
 * Description:
 *      Initialize SVLAN Configuration
 * Input:
 *      unit        - Unit ID
 * Output:
 *      None
 * Return:
 *      RT_ERR_OK           - OK
 *      RT_ERR_FAILED       - Failed
 *      RT_ERR_SMI          - SMI access error
 * Note:
 *      Ether type of S-tag in 802.1ad is 0x88a8 and there are existed ether type 0x9100 and 0x9200 for Q-in-Q SLAN design.
 *      User can set mathced ether type as service provider supported protocol.
 */
rtksw_api_ret_t dal_rtl8367d_svlaninit(rtksw_uint32 unit)
{
    rtksw_uint32 i;
    rtksw_api_ret_t retVal;

    /* Check initialization state */
    RTKSW_CHK_INIT_STATE(unit);

    /*default use C-priority*/
    if ((retVal = dal_rtl8367d_svlanpriorityRef_set(unit, REF_CTAG_PRI)) != RT_ERR_OK)
        return retVal;

    /*Drop SVLAN untag frame*/
    if ((retVal = dal_rtl8367d_svlanuntag_action_set(unit, UNTAG_DROP, 0)) != RT_ERR_OK)
        return retVal;

    /*Set TPID to 0x88a8*/
    if ((retVal = dal_rtl8367d_svlantpidEntry_set(unit, 0x88a8)) != RT_ERR_OK)
        return retVal;

    /*Clean Uplink Port Mask to none*/
    if ((retVal = rtl8367d_setAsicReg(unit, RTL8367D_REG_SVLAN_UPLINK_PORTMASK, 0)) != RT_ERR_OK)
        return retVal;

    /*Clean C2S Configuration*/
    for (i=0; i<= RTL8367D_C2SIDXMAX; i++)
    {
        if ((retVal = rtl8367d_setAsicRegBits(unit, RTL8367D_REG_SVLAN_C2SCFG0_CTRL0 + (i*3), RTL8367D_SVLAN_C2SCFG0_CTRL0_MASK, 0)) != RT_ERR_OK)
                return retVal;
        if ((retVal = rtl8367d_setAsicRegBits(unit, RTL8367D_REG_SVLAN_C2SCFG0_CTRL1 + (i*3), RTL8367D_SVLAN_C2SCFG0_CTRL1_MASK, 0)) != RT_ERR_OK)
                return retVal;
        if ((retVal = rtl8367d_setAsicRegBits(unit, RTL8367D_REG_SVLAN_C2SCFG0_CTRL2 + (i*3), RTL8367D_SVLAN_C2SCFG0_CTRL2_MASK, 0)) != RT_ERR_OK)
                return retVal;
    }

    return RT_ERR_OK;
}

/* Function Name:
 *      dal_rtl8367d_svlanservicePort_add
 * Description:
 *      Add one service port in the specified device
 * Input:
 *      unit        - Unit ID
 *      port        - Port id.
 * Output:
 *      None
 * Return:
 *      RT_ERR_OK           - OK
 *      RT_ERR_FAILED       - Failed
 *      RT_ERR_SMI          - SMI access error
 *      RT_ERR_PORT_ID      - Invalid port number.
 *      RT_ERR_INPUT        - Invalid input parameters.
 * Note:
 *      This API is setting which port is connected to provider switch. All frames receiving from this port must
 *      contain accept SVID in S-tag field.
 */
rtksw_api_ret_t dal_rtl8367d_svlanservicePort_add(rtksw_uint32 unit, rtksw_port_t port)
{
    rtksw_api_ret_t retVal;
    rtksw_uint32 pmsk;
    rtksw_uint32 phyPort;

    /* Check initialization state */
    RTKSW_CHK_INIT_STATE(unit);

    /* check port valid */
    RTKSW_CHK_PORT_VALID(unit, port);

    phyPort = rtksw_switch_port_L2P_get(unit, port);
    if (phyPort == UNDEFINE_PHY_PORT)
        return RT_ERR_PORT_ID;

    if ((retVal = rtl8367d_getAsicReg(unit, RTL8367D_REG_SVLAN_UPLINK_PORTMASK, &pmsk)) != RT_ERR_OK)
        return retVal;

    pmsk = pmsk | (1<<phyPort);

    if ((retVal = rtl8367d_setAsicReg(unit, RTL8367D_REG_SVLAN_UPLINK_PORTMASK, pmsk)) != RT_ERR_OK)
        return retVal;

    return RT_ERR_OK;
}

/* Function Name:
 *      dal_rtl8367d_svlanservicePort_get
 * Description:
 *      Get service ports in the specified device.
 * Input:
 *      unit        - Unit ID
 * Output:
 *      pSvlan_portmask - pointer buffer of svlan ports.
 * Return:
 *      RT_ERR_OK          - OK
 *      RT_ERR_FAILED      - Failed
 *      RT_ERR_SMI         - SMI access error
 * Note:
 *      This API is setting which port is connected to provider switch. All frames receiving from this port must
 *      contain accept SVID in S-tag field.
 */
rtksw_api_ret_t dal_rtl8367d_svlanservicePort_get(rtksw_uint32 unit, rtksw_portmask_t *pSvlan_portmask)
{
    rtksw_api_ret_t retVal;
    rtksw_uint32 phyMbrPmask;

    /* Check initialization state */
    RTKSW_CHK_INIT_STATE(unit);

    if(NULL == pSvlan_portmask)
        return RT_ERR_NULL_POINTER;

    if ((retVal = rtl8367d_getAsicReg(unit, RTL8367D_REG_SVLAN_UPLINK_PORTMASK, &phyMbrPmask)) != RT_ERR_OK)
        return retVal;


    if(rtksw_switch_portmask_P2L_get(unit, phyMbrPmask, pSvlan_portmask) != RT_ERR_OK)
        return RT_ERR_FAILED;


    return RT_ERR_OK;
}

/* Function Name:
 *      dal_rtl8367d_svlanservicePort_del
 * Description:
 *      Delete one service port in the specified device
 * Input:
 *      unit        - Unit ID
 *      port        - Port id.
 * Output:
 *      None
 * Return:
 *      RT_ERR_OK           - OK
 *      RT_ERR_FAILED       - Failed
 *      RT_ERR_SMI          - SMI access error
 *      RT_ERR_PORT_ID      - Invalid port number.
 * Note:
 *      This API is removing SVLAN service port in the specified device.
 */
rtksw_api_ret_t dal_rtl8367d_svlanservicePort_del(rtksw_uint32 unit, rtksw_port_t port)
{
    rtksw_api_ret_t retVal;
    rtksw_uint32 pmsk;
    rtksw_uint32 phyPort;

    /* Check initialization state */
    RTKSW_CHK_INIT_STATE(unit);

    /* check port valid */
    RTKSW_CHK_PORT_VALID(unit, port);

    phyPort = rtksw_switch_port_L2P_get(unit, port);
    if (phyPort == UNDEFINE_PHY_PORT)
        return RT_ERR_PORT_ID;

    if ((retVal = rtl8367d_getAsicReg(unit, RTL8367D_REG_SVLAN_UPLINK_PORTMASK, &pmsk)) != RT_ERR_OK)
        return retVal;

    pmsk = pmsk & ~(1<<phyPort);

    if ((retVal = rtl8367d_setAsicReg(unit, RTL8367D_REG_SVLAN_UPLINK_PORTMASK, pmsk)) != RT_ERR_OK)
        return retVal;

    return RT_ERR_OK;
}

/* Function Name:
 *      dal_rtl8367d_svlantpidEntry_set
 * Description:
 *      Configure accepted S-VLAN ether type.
 * Input:
 *      unit            - Unit ID
 *      svlan_tag_id    - Ether type of S-tag frame parsing in uplink ports.
 * Output:
 *      None
 * Return:
 *      RT_ERR_OK           - OK
 *      RT_ERR_FAILED       - Failed
 *      RT_ERR_SMI          - SMI access error
 *      RT_ERR_INPUT        - Invalid input parameter.
 * Note:
 *      Ether type of S-tag in 802.1ad is 0x88a8 and there are existed ether type 0x9100 and 0x9200 for Q-in-Q SLAN design.
 *      User can set mathced ether type as service provider supported protocol.
 */
rtksw_api_ret_t dal_rtl8367d_svlantpidEntry_set(rtksw_uint32 unit, rtksw_uint32 svlan_tag_id)
{
    rtksw_api_ret_t retVal;

    /* Check initialization state */
    RTKSW_CHK_INIT_STATE(unit);

    if (svlan_tag_id>RTKSW_MAX_NUM_OF_PROTO_TYPE)
        return RT_ERR_INPUT;

    if ((retVal = rtl8367d_setAsicReg(unit, RTL8367D_REG_VS_TPID, svlan_tag_id)) != RT_ERR_OK)
        return retVal;

    return RT_ERR_OK;
}

/* Function Name:
 *      dal_rtl8367d_svlantpidEntry_get
 * Description:
 *      Get accepted S-VLAN ether type setting.
 * Input:
 *      unit        - Unit ID
 * Output:
 *      pSvlan_tag_id -  Ether type of S-tag frame parsing in uplink ports.
 * Return:
 *      RT_ERR_OK           - OK
 *      RT_ERR_FAILED       - Failed
 *      RT_ERR_SMI          - SMI access error
 * Note:
 *      This API is setting which port is connected to provider switch. All frames receiving from this port must
 *      contain accept SVID in S-tag field.
 */
rtksw_api_ret_t dal_rtl8367d_svlantpidEntry_get(rtksw_uint32 unit, rtksw_uint32 *pSvlan_tag_id)
{
    rtksw_api_ret_t retVal;

    /* Check initialization state */
    RTKSW_CHK_INIT_STATE(unit);

    if(NULL == pSvlan_tag_id)
        return RT_ERR_NULL_POINTER;

    if ((retVal = rtl8367d_getAsicReg(unit, RTL8367D_REG_VS_TPID, pSvlan_tag_id)) != RT_ERR_OK)
        return retVal;

    return RT_ERR_OK;
}

/* Function Name:
 *      dal_rtl8367d_svlanpriorityRef_set
 * Description:
 *      Set S-VLAN upstream priority reference setting.
 * Input:
 *      unit        - Unit ID
 *      ref         - reference selection parameter.
 * Output:
 *      None
 * Return:
 *      RT_ERR_OK           - OK
 *      RT_ERR_FAILED       - Failed
 *      RT_ERR_SMI          - SMI access error
 *      RT_ERR_INPUT        - Invalid input parameter.
 * Note:
 *      The API can set the upstream SVLAN tag priority reference source. The related priority
 *      sources are as following:
 *      - REF_INTERNAL_PRI,
 *      - REF_CTAG_PRI,
 *      - REF_SVLAN_PRI,
 *      - REF_PB_PRI.
 */
rtksw_api_ret_t dal_rtl8367d_svlanpriorityRef_set(rtksw_uint32 unit, rtksw_svlan_pri_ref_t ref)
{
    rtksw_api_ret_t retVal;

    /* Check initialization state */
    RTKSW_CHK_INIT_STATE(unit);

    if (ref >= REF_PRI_END)
        return RT_ERR_INPUT;

    if ((retVal = rtl8367d_setAsicRegBits(unit, RTL8367D_REG_SVLAN_CFG, RTL8367D_VS_SPRISEL_MASK, ref)) != RT_ERR_OK)
        return retVal;

    return RT_ERR_OK;
}

/* Function Name:
 *      dal_rtl8367d_svlanpriorityRef_get
 * Description:
 *      Get S-VLAN upstream priority reference setting.
 * Input:
 *      unit        - Unit ID
 * Output:
 *      pRef - reference selection parameter.
 * Return:
 *      RT_ERR_OK           - OK
 *      RT_ERR_FAILED       - Failed
 *      RT_ERR_SMI          - SMI access error
 * Note:
 *      The API can get the upstream SVLAN tag priority reference source. The related priority
 *      sources are as following:
 *      - REF_INTERNAL_PRI,
 *      - REF_CTAG_PRI,
 *      - REF_SVLAN_PRI,
 *      - REF_PB_PRI
 */
rtksw_api_ret_t dal_rtl8367d_svlanpriorityRef_get(rtksw_uint32 unit, rtksw_svlan_pri_ref_t *pRef)
{
    rtksw_api_ret_t retVal;

    /* Check initialization state */
    RTKSW_CHK_INIT_STATE(unit);

    if(NULL == pRef)
        return RT_ERR_NULL_POINTER;

    if ((retVal = rtl8367d_getAsicRegBits(unit, RTL8367D_REG_SVLAN_CFG, RTL8367D_VS_SPRISEL_MASK, pRef)) != RT_ERR_OK)
        return retVal;

    return RT_ERR_OK;
}

/* Function Name:
 *      dal_rtl8367d_svlanmemberPortEntry_set
 * Description:
 *      Configure system SVLAN member content
 * Input:
 *      unit        - Unit ID
 *      svid        - SVLAN id
 *      psvlan_cfg  - SVLAN member configuration
 * Output:
 *      None
 * Return:
 *      RT_ERR_OK               - OK
 *      RT_ERR_FAILED           - Failed
 *      RT_ERR_SMI              - SMI access error
 *      RT_ERR_INPUT            - Invalid input parameter.
 *      RT_ERR_SVLAN_VID        - Invalid SVLAN VID parameter.
 *      RT_ERR_PORT_MASK        - Invalid portmask.
 *      RT_ERR_SVLAN_TABLE_FULL - SVLAN configuration is full.
 * Note:
 *      The API can set system 64 accepted s-tag frame format. Only 64 SVID S-tag frame will be accpeted
 *      to receiving from uplink ports. Other SVID S-tag frame or S-untagged frame will be droped by default setup.
 *      - rtksw_svlan_memberCfg_t->svid is SVID of SVLAN member configuration.
 *      - rtksw_svlan_memberCfg_t->memberport is member port mask of SVLAN member configuration.
 *      - rtksw_svlan_memberCfg_t->fid is filtering database of SVLAN member configuration.
 *      - rtksw_svlan_memberCfg_t->priority is priority of SVLAN member configuration.
 */
rtksw_api_ret_t dal_rtl8367d_svlanmemberPortEntry_set(rtksw_uint32 unit, rtksw_vlan_t svid, rtksw_svlan_memberCfg_t *pSvlan_cfg)
{
    rtksw_api_ret_t retVal;
    rtksw_uint32 phyMbrPmask, phyUntagPmask;
    dal_rtl8367d_user_vlan4kentry vlan4kEntry;

    /* Check initialization state */
    RTKSW_CHK_INIT_STATE(unit);

    if(NULL == pSvlan_cfg)
        return RT_ERR_NULL_POINTER;

    if(svid > RTL8367D_VIDMAX)
        return RT_ERR_SVLAN_VID;

    RTKSW_CHK_PORTMASK_VALID(unit, &(pSvlan_cfg->memberport));

    RTKSW_CHK_PORTMASK_VALID(unit, &(pSvlan_cfg->untagport));

    if (pSvlan_cfg->fid > RTL8367D_FIDMAX)
        return RT_ERR_L2_FID;

    if (pSvlan_cfg->chk_ivl_svl> RTKSW_ENABLED)
        return RT_ERR_INPUT;

    if (pSvlan_cfg->ivl_svl> RTKSW_ENABLED)
        return RT_ERR_INPUT;

    if (pSvlan_cfg->fiden !=0)
        return RT_ERR_CHIP_NOT_SUPPORTED;

    if (pSvlan_cfg->priority != 0)
        return RT_ERR_CHIP_NOT_SUPPORTED;

    if (pSvlan_cfg->efiden != 0)
        return RT_ERR_CHIP_NOT_SUPPORTED;

    if (pSvlan_cfg->efid != 0)
        return RT_ERR_CHIP_NOT_SUPPORTED;

    /* Get physical port mask */
    if(rtksw_switch_portmask_L2P_get(unit, &(pSvlan_cfg->memberport), &phyMbrPmask) != RT_ERR_OK)
        return RT_ERR_FAILED;
    if(rtksw_switch_portmask_L2P_get(unit, &(pSvlan_cfg->untagport), &phyUntagPmask) != RT_ERR_OK)
        return RT_ERR_FAILED;

    osal_memset(&vlan4kEntry, 0, sizeof(dal_rtl8367d_user_vlan4kentry));
    vlan4kEntry.vid = svid;
    if ((retVal = _dal_rtl8367d_getAsicVlan4kEntry(unit, &vlan4kEntry)) != RT_ERR_OK)
        return retVal;

    vlan4kEntry.vid = svid;
    vlan4kEntry.mbr = phyMbrPmask;
    vlan4kEntry.untag = phyUntagPmask;
    vlan4kEntry.svlan_chk_ivl_svl = pSvlan_cfg->chk_ivl_svl;
    vlan4kEntry.ivl_svl = pSvlan_cfg->ivl_svl;
    vlan4kEntry.fid_msti = pSvlan_cfg->fid;

    if ((retVal = _dal_rtl8367d_setAsicVlan4kEntry(unit, &vlan4kEntry)) != RT_ERR_OK)
        return retVal;

    return RT_ERR_OK;
}

/* Function Name:
 *      dal_rtl8367d_svlanmemberPortEntry_get
 * Description:
 *      Get SVLAN member Configure.
 * Input:
 *      unit        - Unit ID
 *      svid        - SVLAN id
 * Output:
 *      pSvlan_cfg - SVLAN member configuration
 * Return:
 *      RT_ERR_OK                       - OK
 *      RT_ERR_FAILED                   - Failed
 *      RT_ERR_SMI                      - SMI access error
 *      RT_ERR_SVLAN_ENTRY_NOT_FOUND    - specified svlan entry not found.
 *      RT_ERR_INPUT                    - Invalid input parameters.
 * Note:
 *      The API can get system 64 accepted s-tag frame format. Only 64 SVID S-tag frame will be accpeted
 *      to receiving from uplink ports. Other SVID S-tag frame or S-untagged frame will be droped.
 */
rtksw_api_ret_t dal_rtl8367d_svlanmemberPortEntry_get(rtksw_uint32 unit, rtksw_vlan_t svid, rtksw_svlan_memberCfg_t *pSvlan_cfg)
{
    rtksw_api_ret_t retVal;
    dal_rtl8367d_user_vlan4kentry vlan4kEntry;

    /* Check initialization state */
    RTKSW_CHK_INIT_STATE(unit);

    if(NULL == pSvlan_cfg)
        return RT_ERR_NULL_POINTER;

    if (svid > RTL8367D_VIDMAX)
        return RT_ERR_SVLAN_VID;

    osal_memset(&vlan4kEntry, 0, sizeof(dal_rtl8367d_user_vlan4kentry));
    vlan4kEntry.vid = svid;
    if ((retVal = _dal_rtl8367d_getAsicVlan4kEntry(unit, &vlan4kEntry)) != RT_ERR_OK)
        return retVal;

    osal_memset(pSvlan_cfg, 0, sizeof(rtksw_svlan_memberCfg_t));
    pSvlan_cfg->svid        = vlan4kEntry.vid;
    if(rtksw_switch_portmask_P2L_get(unit, vlan4kEntry.mbr,&(pSvlan_cfg->memberport)) != RT_ERR_OK)
        return RT_ERR_FAILED;
    if(rtksw_switch_portmask_P2L_get(unit, vlan4kEntry.untag,&(pSvlan_cfg->untagport)) != RT_ERR_OK)
        return RT_ERR_FAILED;
    pSvlan_cfg->chk_ivl_svl = vlan4kEntry.svlan_chk_ivl_svl;
    pSvlan_cfg->ivl_svl     = vlan4kEntry.ivl_svl;
    pSvlan_cfg->fid         = vlan4kEntry.fid_msti;

    return RT_ERR_OK;
}

/* Function Name:
 *      dal_rtl8367d_svlandefaultSvlan_set
 * Description:
 *      Configure default egress SVLAN.
 * Input:
 *      unit        - Unit ID
 *      port        - Source port
 *      svid        - SVLAN id
 * Output:
 *      None
 * Return:
 *      RT_ERR_OK                       - OK
 *      RT_ERR_FAILED                   - Failed
 *      RT_ERR_SMI                      - SMI access error
 *      RT_ERR_INPUT                    - Invalid input parameter.
 *      RT_ERR_SVLAN_VID                - Invalid SVLAN VID parameter.
 *      RT_ERR_SVLAN_ENTRY_NOT_FOUND    - specified svlan entry not found.
 * Note:
 *      The API can set port n S-tag format index while receiving frame from port n
 *      is transmit through uplink port with s-tag field
 */
rtksw_api_ret_t dal_rtl8367d_svlandefaultSvlan_set(rtksw_uint32 unit, rtksw_port_t port, rtksw_vlan_t svid)
{
    rtksw_api_ret_t retVal;

    /* Check initialization state */
    RTKSW_CHK_INIT_STATE(unit);

    /* Check port Valid */
    RTKSW_CHK_PORT_VALID(unit, port);

    /* svid must be 0~4095 */
    if (svid > RTL8367D_VIDMAX)
        return RT_ERR_SVLAN_VID;

    if ((retVal = rtl8367d_setAsicRegBits(unit, RTL8367D_REG_SVLAN_PORTBASED_SVID_CTRL0 + rtksw_switch_port_L2P_get(unit, port), RTL8367D_SVLAN_PORTBASED_SVID_CTRL0_MASK, svid)) != RT_ERR_OK)
        return retVal;

    return RT_ERR_OK;
}

/* Function Name:
 *      dal_rtl8367d_svlandefaultSvlan_get
 * Description:
 *      Get the configure default egress SVLAN.
 * Input:
 *      unit        - Unit ID
 *      port        - Source port
 * Output:
 *      pSvid - SVLAN VID
 * Return:
 *      RT_ERR_OK           - OK
 *      RT_ERR_FAILED       - Failed
 *      RT_ERR_SMI          - SMI access error
 *      RT_ERR_INPUT        - Invalid input parameters.
 * Note:
 *      The API can get port n S-tag format index while receiving frame from port n
 *      is transmit through uplink port with s-tag field
 */
rtksw_api_ret_t dal_rtl8367d_svlandefaultSvlan_get(rtksw_uint32 unit, rtksw_port_t port, rtksw_vlan_t *pSvid)
{
    rtksw_api_ret_t retVal;

    /* Check initialization state */
    RTKSW_CHK_INIT_STATE(unit);

    if(NULL == pSvid)
        return RT_ERR_NULL_POINTER;

    /* Check port Valid */
    RTKSW_CHK_PORT_VALID(unit, port);

    if ((retVal = rtl8367d_getAsicRegBits(unit, RTL8367D_REG_SVLAN_PORTBASED_SVID_CTRL0 + rtksw_switch_port_L2P_get(unit, port), RTL8367D_SVLAN_PORTBASED_SVID_CTRL0_MASK, pSvid)) != RT_ERR_OK)
        return retVal;

    return RT_ERR_OK;
}

/* Function Name:
 *      dal_rtl8367d_svlanc2s_add
 * Description:
 *      Configure SVLAN C2S table
 * Input:
 *      unit        - Unit ID
 *      vid         - VLAN ID
 *      src_port    - Ingress Port
 *      svid        - SVLAN VID
 * Output:
 *      None
 * Return:
 *      RT_ERR_OK           - OK
 *      RT_ERR_FAILED       - Failed
 *      RT_ERR_SMI          - SMI access error
 *      RT_ERR_PORT_ID      - Invalid port ID.
 *      RT_ERR_SVLAN_VID    - Invalid SVLAN VID parameter.
 *      RT_ERR_VLAN_VID     - Invalid VID parameter.
 *      RT_ERR_OUT_OF_RANGE - input out of range.
 *      RT_ERR_INPUT        - Invalid input parameters.
 * Note:
 *      The API can set system C2S configuration. ASIC will check upstream's VID and assign related
 *      SVID to mathed packet. There are 128 SVLAN C2S configurations.
 */
rtksw_api_ret_t dal_rtl8367d_svlanc2s_add(rtksw_uint32 unit, rtksw_vlan_t vid, rtksw_port_t src_port, rtksw_vlan_t svid)
{
    rtksw_api_ret_t retVal, i;
    rtksw_uint32 empty_idx;
    rtksw_port_t phyPort;
    rtksw_uint16 doneFlag;
    rtksw_uint32 idx_svid, idx_pmsk, idx_cvid;


    /* Check initialization state */
    RTKSW_CHK_INIT_STATE(unit);


    if (vid > RTL8367D_VIDMAX)
        return RT_ERR_VLAN_VID;

    if (svid > RTL8367D_VIDMAX)
        return RT_ERR_SVLAN_VID;

    /* Check port Valid */
    RTKSW_CHK_PORT_VALID(unit, src_port);

    phyPort = rtksw_switch_port_L2P_get(unit, src_port);
    if (phyPort == UNDEFINE_PHY_PORT)
        return RT_ERR_PORT_ID;

    empty_idx = 0xFFFF;
    doneFlag = FALSE;

    for (i = RTL8367D_C2SIDXMAX; i>=0; i--)
    {
        if ((retVal = rtl8367d_getAsicRegBits(unit, RTL8367D_REG_SVLAN_C2SCFG0_CTRL0 + (i*3), RTL8367D_SVLAN_C2SCFG0_CTRL0_MASK, &idx_svid)) != RT_ERR_OK)
                return retVal;

        if ((retVal = rtl8367d_getAsicRegBits(unit, RTL8367D_REG_SVLAN_C2SCFG0_CTRL1 + (i*3), RTL8367D_SVLAN_C2SCFG0_CTRL1_MASK, &idx_pmsk)) != RT_ERR_OK)
                return retVal;

        if ((retVal = rtl8367d_getAsicRegBits(unit, RTL8367D_REG_SVLAN_C2SCFG0_CTRL2 + (i*3), RTL8367D_SVLAN_C2SCFG0_CTRL2_MASK, &idx_cvid)) != RT_ERR_OK)
                return retVal;

        if (idx_pmsk != 0) /* Valid entry */
        {
            if (idx_cvid == vid)
            {
                /* Check Src_port */
                if(idx_pmsk & (1 << phyPort))
                {
                    /* Check SVIDX */
                    if(idx_svid == svid)
                    {
                        /* All the same, do nothing */
                        return RT_ERR_OK;
                    }
                    else
                    {
                        /* New svidx, remove src_port and find a new slot to add a new enrty */
                        idx_pmsk = idx_pmsk & ~(1 << phyPort);
                        if(idx_pmsk == 0)
                        {
                            idx_svid = 0;
                            idx_cvid = 0;
                        }

                        if ((retVal = rtl8367d_setAsicRegBits(unit, RTL8367D_REG_SVLAN_C2SCFG0_CTRL0 + (i*3), RTL8367D_SVLAN_C2SCFG0_CTRL0_MASK, idx_svid)) != RT_ERR_OK)
                            return retVal;

                        if ((retVal = rtl8367d_setAsicRegBits(unit, RTL8367D_REG_SVLAN_C2SCFG0_CTRL1 + (i*3), RTL8367D_SVLAN_C2SCFG0_CTRL1_MASK, idx_pmsk)) != RT_ERR_OK)
                            return retVal;

                        if ((retVal = rtl8367d_setAsicRegBits(unit, RTL8367D_REG_SVLAN_C2SCFG0_CTRL2 + (i*3), RTL8367D_SVLAN_C2SCFG0_CTRL2_MASK, idx_cvid)) != RT_ERR_OK)
                            return retVal;
                    }
                }
                else
                {
                    if(idx_svid == svid && doneFlag == FALSE)
                    {
                        idx_pmsk = idx_pmsk | (1 << phyPort);
                        if ((retVal = rtl8367d_setAsicRegBits(unit, RTL8367D_REG_SVLAN_C2SCFG0_CTRL1 + (i*3), RTL8367D_SVLAN_C2SCFG0_CTRL1_MASK, idx_pmsk)) != RT_ERR_OK)
                            return retVal;

                        doneFlag = TRUE;
                    }
                }
            }
        }
        else /* Empty entry */
        {
            empty_idx = i;
        }
    }

    if (0xFFFF != empty_idx && doneFlag ==FALSE)
    {
       if ((retVal = rtl8367d_setAsicRegBits(unit, RTL8367D_REG_SVLAN_C2SCFG0_CTRL0 + (empty_idx*3), RTL8367D_SVLAN_C2SCFG0_CTRL0_MASK, svid)) != RT_ERR_OK)
               return retVal;

       if ((retVal = rtl8367d_setAsicRegBits(unit, RTL8367D_REG_SVLAN_C2SCFG0_CTRL1 + (empty_idx*3), RTL8367D_SVLAN_C2SCFG0_CTRL1_MASK, (1<<phyPort))) != RT_ERR_OK)
               return retVal;

       if ((retVal = rtl8367d_setAsicRegBits(unit, RTL8367D_REG_SVLAN_C2SCFG0_CTRL2 + (empty_idx*3), RTL8367D_SVLAN_C2SCFG0_CTRL2_MASK, vid)) != RT_ERR_OK)
               return retVal;

       return RT_ERR_OK;
    }
    else if(doneFlag == TRUE)
    {
        return RT_ERR_OK;
    }

    return RT_ERR_OUT_OF_RANGE;
}

/* Function Name:
 *      dal_rtl8367d_svlanc2s_del
 * Description:
 *      Delete one C2S entry
 * Input:
 *      unit        - Unit ID
 *      vid         - VLAN ID
 *      src_port    - Ingress Port
 *      svid        - SVLAN VID
 * Output:
 *      None
 * Return:
 *      RT_ERR_OK               - OK
 *      RT_ERR_FAILED           - Failed
 *      RT_ERR_SMI              - SMI access error
 *      RT_ERR_VLAN_VID         - Invalid VID parameter.
 *      RT_ERR_PORT_ID          - Invalid port ID.
 *      RT_ERR_OUT_OF_RANGE     - input out of range.
 * Note:
 *      The API can delete system C2S configuration. There are 128 SVLAN C2S configurations.
 */
rtksw_api_ret_t dal_rtl8367d_svlanc2s_del(rtksw_uint32 unit, rtksw_vlan_t vid, rtksw_port_t src_port)
{
    rtksw_api_ret_t retVal;
    rtksw_uint32 i;
    rtksw_port_t phyPort;
    rtksw_uint32 idx_svid, idx_pmsk, idx_cvid;

    /* Check initialization state */
    RTKSW_CHK_INIT_STATE(unit);

    if (vid > RTL8367D_VIDMAX)
        return RT_ERR_VLAN_VID;

    /* Check port Valid */
    RTKSW_CHK_PORT_VALID(unit, src_port);
    phyPort = rtksw_switch_port_L2P_get(unit, src_port);
    if (phyPort == UNDEFINE_PHY_PORT)
        return RT_ERR_PORT_ID;

    for (i = 0; i <= RTL8367D_C2SIDXMAX; i++)
    {
        if ((retVal = rtl8367d_getAsicRegBits(unit, RTL8367D_REG_SVLAN_C2SCFG0_CTRL0 + (i*3), RTL8367D_SVLAN_C2SCFG0_CTRL0_MASK, &idx_svid)) != RT_ERR_OK)
                return retVal;

        if ((retVal = rtl8367d_getAsicRegBits(unit, RTL8367D_REG_SVLAN_C2SCFG0_CTRL1 + (i*3), RTL8367D_SVLAN_C2SCFG0_CTRL1_MASK, &idx_pmsk)) != RT_ERR_OK)
                return retVal;

        if ((retVal = rtl8367d_getAsicRegBits(unit, RTL8367D_REG_SVLAN_C2SCFG0_CTRL2 + (i*3), RTL8367D_SVLAN_C2SCFG0_CTRL2_MASK, &idx_cvid)) != RT_ERR_OK)
                return retVal;

        if (idx_cvid == vid)
        {
            if(idx_pmsk & (1 << phyPort))
            {
                idx_pmsk = idx_pmsk & ~(1 << phyPort);
                if(idx_pmsk == 0)
                {
                    idx_cvid = 0;
                    idx_svid = 0;
                }

                if ((retVal = rtl8367d_setAsicRegBits(unit, RTL8367D_REG_SVLAN_C2SCFG0_CTRL0 + (i*3), RTL8367D_SVLAN_C2SCFG0_CTRL0_MASK, idx_svid)) != RT_ERR_OK)
                        return retVal;

                if ((retVal = rtl8367d_setAsicRegBits(unit, RTL8367D_REG_SVLAN_C2SCFG0_CTRL1 + (i*3), RTL8367D_SVLAN_C2SCFG0_CTRL1_MASK, idx_pmsk)) != RT_ERR_OK)
                        return retVal;

                if ((retVal = rtl8367d_setAsicRegBits(unit, RTL8367D_REG_SVLAN_C2SCFG0_CTRL2 + (i*3), RTL8367D_SVLAN_C2SCFG0_CTRL2_MASK, idx_cvid)) != RT_ERR_OK)
                        return retVal;

                return RT_ERR_OK;
            }
        }
    }

    return RT_ERR_OUT_OF_RANGE;
}

/* Function Name:
 *      dal_rtl8367d_svlanc2s_get
 * Description:
 *      Get configure SVLAN C2S table
 * Input:
 *      unit        - Unit ID
 *      vid         - VLAN ID
 *      src_port    - Ingress Port
 * Output:
 *      pSvid - SVLAN ID
 * Return:
 *      RT_ERR_OK           - OK
 *      RT_ERR_FAILED       - Failed
 *      RT_ERR_SMI          - SMI access error
 *      RT_ERR_INPUT        - Invalid input parameters.
 *      RT_ERR_PORT_ID      - Invalid port ID.
 *      RT_ERR_OUT_OF_RANGE - input out of range.
 * Note:
 *     The API can get system C2S configuration. There are 128 SVLAN C2S configurations.
 */
rtksw_api_ret_t dal_rtl8367d_svlanc2s_get(rtksw_uint32 unit, rtksw_vlan_t vid, rtksw_port_t src_port, rtksw_vlan_t *pSvid)
{
    rtksw_api_ret_t retVal;
    rtksw_uint32 i;
    rtksw_uint32 idx_svid, idx_pmsk, idx_cvid;
    rtksw_port_t phyPort;

    /* Check initialization state */
    RTKSW_CHK_INIT_STATE(unit);

    if(NULL == pSvid)
        return RT_ERR_NULL_POINTER;

    if (vid > RTL8367D_VIDMAX)
        return RT_ERR_VLAN_VID;

    /* Check port Valid */
    RTKSW_CHK_PORT_VALID(unit, src_port);
    phyPort = rtksw_switch_port_L2P_get(unit, src_port);
    if (phyPort == UNDEFINE_PHY_PORT)
        return RT_ERR_PORT_ID;

    for (i = 0; i <= RTL8367D_C2SIDXMAX; i++)
    {
        if ((retVal = rtl8367d_getAsicRegBits(unit, RTL8367D_REG_SVLAN_C2SCFG0_CTRL0 + (i*3), RTL8367D_SVLAN_C2SCFG0_CTRL0_MASK, &idx_svid)) != RT_ERR_OK)
                return retVal;

        if ((retVal = rtl8367d_getAsicRegBits(unit, RTL8367D_REG_SVLAN_C2SCFG0_CTRL1 + (i*3), RTL8367D_SVLAN_C2SCFG0_CTRL1_MASK, &idx_pmsk)) != RT_ERR_OK)
                return retVal;

        if ((retVal = rtl8367d_getAsicRegBits(unit, RTL8367D_REG_SVLAN_C2SCFG0_CTRL2 + (i*3), RTL8367D_SVLAN_C2SCFG0_CTRL2_MASK, &idx_cvid)) != RT_ERR_OK)
                return retVal;

        if (idx_cvid == vid)
        {
            if(idx_pmsk & (1 << phyPort))
            {
                *pSvid = idx_svid;
                return RT_ERR_OK;
            }
        }
    }

    return RT_ERR_OUT_OF_RANGE;
}

/* Function Name:
 *      dal_rtl8367d_svlan_sp2c_add
 * Description:
 *      Add system SP2C configuration
 * Input:
 *      unit        - Unit ID
 *      cvid        - VLAN ID
 *      dst_port    - Destination port of SVLAN to CVLAN configuration
 *      svid        - SVLAN VID
 *
 * Output:
 *      None
 * Return:
 *      RT_ERR_OK           - OK
 *      RT_ERR_FAILED       - Failed
 *      RT_ERR_SMI          - SMI access error
 *      RT_ERR_PORT_ID      - Invalid port number.
 *      RT_ERR_SVLAN_VID    - Invalid SVLAN VID parameter.
 *      RT_ERR_VLAN_VID     - Invalid VID parameter.
 *      RT_ERR_OUT_OF_RANGE - input out of range.
 *      RT_ERR_INPUT        - Invalid input parameters.
 * Note:
 *      The API can add SVID & Destination Port to CVLAN configuration. The downstream frames with assigned
 *      SVID will be add C-tag with assigned CVID if the output port is the assigned destination port.
 *      There are 128 SP2C configurations.
 */
rtksw_api_ret_t dal_rtl8367d_svlan_sp2c_add(rtksw_uint32 unit, rtksw_vlan_t svid, rtksw_port_t dst_port, rtksw_vlan_t cvid)
{
    rtksw_api_ret_t retVal, i;
    rtksw_uint32 empty_idx;
    rtksw_port_t port;
    rtksw_uint32 idx_svid, idx_port;
    rtksw_uint32 valid_flag;

    /* Check initialization state */
    RTKSW_CHK_INIT_STATE(unit);

    if (svid > RTL8367D_VIDMAX)
        return RT_ERR_SVLAN_VID;

    if (cvid > RTL8367D_VIDMAX)
        return RT_ERR_VLAN_VID;

    /* Check port Valid */
    RTKSW_CHK_PORT_VALID(unit, dst_port);
    port = rtksw_switch_port_L2P_get(unit, dst_port);
    empty_idx = 0xFFFF;

    for (i = RTL8367D_SP2CMAX; i>=0; i--)
    {
        if ((retVal = rtl8367d_getAsicRegBits(unit, RTL8367D_REG_SVLAN_SP2C_ENTRY0_CTRL0 + (i*2), RTL8367D_SVLAN_SP2C_ENTRY0_CTRL0_SVID_MASK, &idx_svid)) != RT_ERR_OK)
                return retVal;

        if ((retVal = rtl8367d_getAsicRegBits(unit, RTL8367D_REG_SVLAN_SP2C_ENTRY0_CTRL0 + (i*2), RTL8367D_SVLAN_SP2C_ENTRY0_CTRL0_DST_PORT_MASK, &idx_port)) != RT_ERR_OK)
                return retVal;

        if ((retVal = rtl8367d_getAsicRegBit(unit, RTL8367D_REG_SVLAN_SP2C_ENTRY0_CTRL1 + (i*2), RTL8367D_SVLAN_SP2C_ENTRY0_CTRL1_VALID_OFFSET, &valid_flag)) != RT_ERR_OK)
                return retVal;

        if ( (idx_svid == svid) && (idx_port == port) && (valid_flag == 1))
        {
            empty_idx = i;
            break;
        }
        else if (valid_flag == 0)
        {
            empty_idx = i;
        }

    }

    if (empty_idx!=0xFFFF)
    {
        valid_flag = 1;

        if ((retVal = rtl8367d_setAsicRegBits(unit, RTL8367D_REG_SVLAN_SP2C_ENTRY0_CTRL0 + (empty_idx*2), RTL8367D_SVLAN_SP2C_ENTRY0_CTRL0_SVID_MASK, svid)) != RT_ERR_OK)
                return retVal;

        if ((retVal = rtl8367d_setAsicRegBits(unit, RTL8367D_REG_SVLAN_SP2C_ENTRY0_CTRL0 + (empty_idx*2), RTL8367D_SVLAN_SP2C_ENTRY0_CTRL0_DST_PORT_MASK, port)) != RT_ERR_OK)
                return retVal;

        if ((retVal = rtl8367d_setAsicRegBits(unit, RTL8367D_REG_SVLAN_SP2C_ENTRY0_CTRL1 + (empty_idx*2), RTL8367D_SVLAN_SP2C_ENTRY0_CTRL1_VID_MASK, cvid)) != RT_ERR_OK)
                return retVal;

        if ((retVal = rtl8367d_setAsicRegBit(unit, RTL8367D_REG_SVLAN_SP2C_ENTRY0_CTRL1 + (empty_idx*2), RTL8367D_SVLAN_SP2C_ENTRY0_CTRL1_VALID_OFFSET, valid_flag)) != RT_ERR_OK)
                return retVal;

        return RT_ERR_OK;
    }

    return RT_ERR_OUT_OF_RANGE;

}

/* Function Name:
 *      dal_rtl8367d_svlan_sp2c_get
 * Description:
 *      Get configure system SP2C content
 * Input:
 *      unit        - Unit ID
 *      svid        - SVLAN VID
 *      dst_port    - Destination port of SVLAN to CVLAN configuration
 * Output:
 *      pCvid - VLAN ID
 * Return:
 *      RT_ERR_OK           - OK
 *      RT_ERR_FAILED       - Failed
 *      RT_ERR_SMI          - SMI access error
 *      RT_ERR_INPUT        - Invalid input parameters.
 *      RT_ERR_OUT_OF_RANGE - input out of range.
 *      RT_ERR_PORT_ID      - Invalid port number.
 *      RT_ERR_SVLAN_VID    - Invalid SVLAN VID parameter.
 * Note:
 *     The API can get SVID & Destination Port to CVLAN configuration. There are 128 SP2C configurations.
 */
rtksw_api_ret_t dal_rtl8367d_svlan_sp2c_get(rtksw_uint32 unit, rtksw_vlan_t svid, rtksw_port_t dst_port, rtksw_vlan_t *pCvid)
{
    rtksw_api_ret_t retVal;
    rtksw_uint32 i;
    rtksw_uint32 idx_svid, idx_cvid, idx_port;
    rtksw_uint32 valid_flag;

    /* Check initialization state */
    RTKSW_CHK_INIT_STATE(unit);

    if(NULL == pCvid)
        return RT_ERR_NULL_POINTER;

    if (svid > RTL8367D_VIDMAX)
        return RT_ERR_SVLAN_VID;

    /* Check port Valid */
    RTKSW_CHK_PORT_VALID(unit, dst_port);
    dst_port = rtksw_switch_port_L2P_get(unit, dst_port);

    for (i = 0; i <= RTL8367D_SP2CMAX; i++)
    {
        if ((retVal = rtl8367d_getAsicRegBits(unit, RTL8367D_REG_SVLAN_SP2C_ENTRY0_CTRL0 + (i*2), RTL8367D_SVLAN_SP2C_ENTRY0_CTRL0_SVID_MASK, &idx_svid)) != RT_ERR_OK)
                return retVal;

        if ((retVal = rtl8367d_getAsicRegBits(unit, RTL8367D_REG_SVLAN_SP2C_ENTRY0_CTRL0 + (i*2), RTL8367D_SVLAN_SP2C_ENTRY0_CTRL0_DST_PORT_MASK, &idx_port)) != RT_ERR_OK)
                return retVal;

        if ((retVal = rtl8367d_getAsicRegBit(unit, RTL8367D_REG_SVLAN_SP2C_ENTRY0_CTRL1 + (i*2), RTL8367D_SVLAN_SP2C_ENTRY0_CTRL1_VALID_OFFSET, &valid_flag)) != RT_ERR_OK)
                return retVal;

        if ( (idx_svid == svid) && (idx_port == dst_port) && (valid_flag == 1))
        {
            if ((retVal = rtl8367d_getAsicRegBits(unit, RTL8367D_REG_SVLAN_SP2C_ENTRY0_CTRL1 + (i*2), RTL8367D_SVLAN_SP2C_ENTRY0_CTRL1_VID_MASK, &idx_cvid)) != RT_ERR_OK)
                    return retVal;

            *pCvid = idx_cvid;
            return RT_ERR_OK;
        }
    }

    return RT_ERR_OUT_OF_RANGE;
}

/* Function Name:
 *      dal_rtl8367d_svlan_sp2c_del
 * Description:
 *      Delete system SP2C configuration
 * Input:
 *      unit        - Unit ID
 *      svid        - SVLAN VID
 *      dst_port    - Destination port of SVLAN to CVLAN configuration
 * Output:
 *      None
 * Return:
 *      RT_ERR_OK           - OK
 *      RT_ERR_FAILED       - Failed
 *      RT_ERR_SMI          - SMI access error
 *      RT_ERR_PORT_ID      - Invalid port number.
 *      RT_ERR_SVLAN_VID    - Invalid SVLAN VID parameter.
 *      RT_ERR_OUT_OF_RANGE - input out of range.
 * Note:
 *      The API can delete SVID & Destination Port to CVLAN configuration. There are 128 SP2C configurations.
 */
rtksw_api_ret_t dal_rtl8367d_svlan_sp2c_del(rtksw_uint32 unit, rtksw_vlan_t svid, rtksw_port_t dst_port)
{
    rtksw_api_ret_t retVal;
    rtksw_uint32 i;
    rtksw_uint32 idx_svid, idx_port;
    rtksw_uint32 valid_flag;

    /* Check initialization state */
    RTKSW_CHK_INIT_STATE(unit);

    if (svid > RTL8367D_VIDMAX)
        return RT_ERR_SVLAN_VID;

    /* Check port Valid */
    RTKSW_CHK_PORT_VALID(unit, dst_port);
    dst_port = rtksw_switch_port_L2P_get(unit, dst_port);



    for (i = 0; i <= RTL8367D_SP2CMAX; i++)
    {
        if ((retVal = rtl8367d_getAsicRegBits(unit, RTL8367D_REG_SVLAN_SP2C_ENTRY0_CTRL0 + (i*2), RTL8367D_SVLAN_SP2C_ENTRY0_CTRL0_SVID_MASK, &idx_svid)) != RT_ERR_OK)
                return retVal;

        if ((retVal = rtl8367d_getAsicRegBits(unit, RTL8367D_REG_SVLAN_SP2C_ENTRY0_CTRL0 + (i*2), RTL8367D_SVLAN_SP2C_ENTRY0_CTRL0_DST_PORT_MASK, &idx_port)) != RT_ERR_OK)
                return retVal;

        if ((retVal = rtl8367d_getAsicRegBit(unit, RTL8367D_REG_SVLAN_SP2C_ENTRY0_CTRL1 + (i*2), RTL8367D_SVLAN_SP2C_ENTRY0_CTRL1_VALID_OFFSET, &valid_flag)) != RT_ERR_OK)
                return retVal;

        if ( (idx_svid == svid) && (idx_port == dst_port) && (valid_flag == 1))
        {
            if ((retVal = rtl8367d_setAsicReg(unit, RTL8367D_REG_SVLAN_SP2C_ENTRY0_CTRL0 + (i*2), 0)) != RT_ERR_OK)
                    return retVal;

            if ((retVal = rtl8367d_setAsicReg(unit, RTL8367D_REG_SVLAN_SP2C_ENTRY0_CTRL1 + (i*2), 0)) != RT_ERR_OK)
                    return retVal;

            return RT_ERR_OK;
        }

    }

    return RT_ERR_OUT_OF_RANGE;
}




/* Function Name:
 *      dal_rtl8367d_svlanuntag_action_set
 * Description:
 *      Configure Action of downstream Un-Stag packet
 * Input:
 *      unit        - Unit ID
 *      action      - Action for UnStag
 *      svid        - The SVID assigned to UnStag packet
 * Output:
 *      None
 * Return:
 *      RT_ERR_OK                       - OK
 *      RT_ERR_FAILED                   - Failed
 *      RT_ERR_SMI                      - SMI access error
 *      RT_ERR_SVLAN_VID                - Invalid SVLAN VID parameter.
 *      RT_ERR_SVLAN_ENTRY_NOT_FOUND    - specified svlan entry not found.
 *      RT_ERR_OUT_OF_RANGE             - input out of range.
 *      RT_ERR_INPUT                    - Invalid input parameters.
 * Note:
 *      The API can configure action of downstream Un-Stag packet. A SVID assigned
 *      to the un-stag is also supported by this API. The parameter of svid is
 *      only referenced when the action is set to UNTAG_ASSIGN
 */
rtksw_api_ret_t dal_rtl8367d_svlanuntag_action_set(rtksw_uint32 unit, rtksw_svlan_untag_action_t action, rtksw_vlan_t svid)
{
    rtksw_api_ret_t   retVal;

    /* Check initialization state */
    RTKSW_CHK_INIT_STATE(unit);

    if (action >= UNTAG_END)
        return RT_ERR_OUT_OF_RANGE;

    if(action == UNTAG_ASSIGN)
    {
        if (svid > RTL8367D_VIDMAX)
            return RT_ERR_SVLAN_VID;
    }

    if ((retVal = rtl8367d_setAsicRegBits(unit, RTL8367D_REG_SVLAN_CFG, RTL8367D_VS_UNTAG_MASK, action)) != RT_ERR_OK)
        return retVal;

    if(action == UNTAG_ASSIGN)
    {
        if ((retVal = rtl8367d_setAsicRegBits(unit, RTL8367D_REG_SVLAN_UNTAG_UNMAT_CFG, RTL8367D_SVLAN_UNTAG_UNMAT_CFG_MASK, svid)) != RT_ERR_OK)
            return retVal;
    }

    return RT_ERR_OK;
}

/* Function Name:
 *      dal_rtl8367d_svlanuntag_action_get
 * Description:
 *      Get Action of downstream Un-Stag packet
 * Input:
 *      unit        - Unit ID
 * Output:
 *      pAction  - Action for UnStag
 *      pSvid    - The SVID assigned to UnStag packet
 * Return:
 *      RT_ERR_OK                       - OK
 *      RT_ERR_FAILED                   - Failed
 *      RT_ERR_SMI                      - SMI access error
 *      RT_ERR_SVLAN_VID                - Invalid SVLAN VID parameter.
 *      RT_ERR_SVLAN_ENTRY_NOT_FOUND    - specified svlan entry not found.
 *      RT_ERR_OUT_OF_RANGE             - input out of range.
 *      RT_ERR_INPUT                    - Invalid input parameters.
 * Note:
 *      The API can Get action of downstream Un-Stag packet. A SVID assigned
 *      to the un-stag is also retrieved by this API. The parameter pSvid is
 *      only refernced when the action is UNTAG_ASSIGN
 */
rtksw_api_ret_t dal_rtl8367d_svlanuntag_action_get(rtksw_uint32 unit, rtksw_svlan_untag_action_t *pAction, rtksw_vlan_t *pSvid)
{
    rtksw_api_ret_t   retVal;

    /* Check initialization state */
    RTKSW_CHK_INIT_STATE(unit);

    if(NULL == pAction || NULL == pSvid)
        return RT_ERR_NULL_POINTER;

    if ((retVal = rtl8367d_getAsicRegBits(unit, RTL8367D_REG_SVLAN_CFG, RTL8367D_VS_UNTAG_MASK, pAction)) != RT_ERR_OK)
        return retVal;

    if(*pAction == UNTAG_ASSIGN)
    {
        if ((retVal = rtl8367d_getAsicRegBits(unit, RTL8367D_REG_SVLAN_UNTAG_UNMAT_CFG, RTL8367D_SVLAN_UNTAG_UNMAT_CFG_MASK, pSvid)) != RT_ERR_OK)
            return retVal;
    }

    return RT_ERR_OK;
}



/* Function Name:
 *      dal_rtl8367d_svlanunassign_action_set
 * Description:
 *      Configure Action of upstream without svid assign action
 * Input:
 *      unit        - Unit ID
 *      action      - Action for Un-assign
 * Output:
 *      None
 * Return:
 *      RT_ERR_OK                       - OK
 *      RT_ERR_FAILED                   - Failed
 *      RT_ERR_OUT_OF_RANGE             - input out of range.
 *      RT_ERR_INPUT                    - Invalid input parameters.
 * Note:
 *      The API can configure action of upstream Un-assign svid packet. If action is not
 *      trap to CPU, the port-based SVID sure be assign as system need
 */
rtksw_api_ret_t dal_rtl8367d_svlanunassign_action_set(rtksw_uint32 unit, rtksw_svlan_unassign_action_t action)
{
    rtksw_api_ret_t   retVal;

    /* Check initialization state */
    RTKSW_CHK_INIT_STATE(unit);

    if (action >= UNASSIGN_END)
        return RT_ERR_OUT_OF_RANGE;

    retVal = rtl8367d_setAsicRegBit(unit, RTL8367D_REG_SVLAN_CFG, RTL8367D_VS_UIFSEG_OFFSET, action);

    return retVal;
}

/* Function Name:
 *      dal_rtl8367d_svlanunassign_action_get
 * Description:
 *      Get action of upstream without svid assignment
 * Input:
 *      unit        - Unit ID
 * Output:
 *      pAction  - Action for Un-assign
 * Return:
 *      RT_ERR_OK                       - OK
 *      RT_ERR_FAILED                   - Failed
 * Note:
 *      None
 */
rtksw_api_ret_t dal_rtl8367d_svlanunassign_action_get(rtksw_uint32 unit, rtksw_svlan_unassign_action_t *pAction)
{
    rtksw_api_ret_t   retVal;

    /* Check initialization state */
    RTKSW_CHK_INIT_STATE(unit);

    if(NULL == pAction)
        return RT_ERR_NULL_POINTER;

    retVal = rtl8367d_getAsicRegBit(unit, RTL8367D_REG_SVLAN_CFG, RTL8367D_VS_UIFSEG_OFFSET, pAction);

    return retVal;
}

/* Function Name:
 *      dal_rtl8367d_svlantrapPri_set
 * Description:
 *      Set svlan trap priority
 * Input:
 *      unit        - Unit ID
 *      priority    - priority for trap packets
 * Output:
 *      None
 * Return:
 *      RT_ERR_OK
 *      RT_ERR_FAILED
 *      RT_ERR_QOS_INT_PRIORITY
 * Note:
 *      None
 */
rtksw_api_ret_t dal_rtl8367d_svlantrapPri_set(rtksw_uint32 unit, rtksw_pri_t priority)
{
    rtksw_api_ret_t   retVal;

    RTKSW_CHK_INIT_STATE(unit);

    if(priority > RTL8367D_PRIMAX)
        return RT_ERR_OUT_OF_RANGE;

    retVal = rtl8367d_setAsicRegBits(unit, RTL8367D_REG_QOS_TRAP_PRIORITY0, RTL8367D_SVLAN_PRIOIRTY_MASK, priority);

    return retVal;
}

/* Function Name:
 *      dal_rtl8367d_svlantrapPri_get
 * Description:
 *      Get svlan trap priority
 * Input:
 *      unit        - Unit ID
 * Output:
 *      pPriority - priority for trap packets
 * Return:
 *      RT_ERR_OK
 *      RT_ERR_FAILED
 *      RT_ERR_NULL_POINTER - input parameter may be null pointer
 * Note:
 *      None
 */
rtksw_api_ret_t dal_rtl8367d_svlantrapPri_get(rtksw_uint32 unit, rtksw_pri_t *pPriority)
{
    rtksw_api_ret_t   retVal;

    RTKSW_CHK_INIT_STATE(unit);

    if(NULL == pPriority)
        return RT_ERR_NULL_POINTER;

    retVal = rtl8367d_getAsicRegBits(unit, RTL8367D_REG_QOS_TRAP_PRIORITY0, RTL8367D_SVLAN_PRIOIRTY_MASK, pPriority);

    return retVal;
}   /* end of rtksw_svlan_trapPri_get */

