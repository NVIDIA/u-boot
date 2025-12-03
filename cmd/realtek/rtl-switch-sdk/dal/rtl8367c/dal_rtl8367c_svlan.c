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
 * Purpose : RTK switch high-level API for RTL8367/RTL8367C
 * Feature : Here is a list of all functions and variables in SVLAN module.
 *
 */

#include "../../rtk_switch.h"
#include "../../rtk_error.h"
#include "dal_rtl8367c_svlan.h"
#include "dal_rtl8367c_vlan.h"

#include "rtl8367c_asicdrv.h"
#include "rtl8367c_asicdrv_svlan.h"

#include "../dal_mgmts.h"
#include "../../osal/lib.h"

rtksw_uint8               svlan_mbrCfgUsage[RTL8367C_SVIDXNO];
rtksw_uint16              svlan_mbrCfgVid[RTL8367C_SVIDXNO];
rtksw_svlan_lookupType_t  svlan_lookupType;


/* Function Name:
 *      dal_rtl8367c_svlan_init
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
rtksw_api_ret_t dal_rtl8367c_svlan_init(rtksw_uint32 unit)
{
    rtksw_uint32 i;
    rtksw_api_ret_t retVal;
    rtl8367c_svlan_memconf_t svlanMemConf;
    rtl8367c_svlan_s2c_t svlanSP2CConf;
    rtl8367c_svlan_mc2s_t svlanMC2SConf;
    rtksw_uint32 svidx;

    /* Check initialization state */
    RTKSW_CHK_INIT_STATE(unit);

    /*default use C-priority*/
    if ((retVal = rtl8367c_setAsicSvlanPrioritySel(unit, SPRISEL_CTAGPRI)) != RT_ERR_OK)
        return retVal;

    /*Drop SVLAN untag frame*/
    if ((retVal = rtl8367c_setAsicSvlanIngressUntag(unit, UNTAG_DROP)) != RT_ERR_OK)
        return retVal;

    /*Drop SVLAN unmatch frame*/
    if ((retVal = rtl8367c_setAsicSvlanIngressUnmatch(unit, UNMATCH_DROP)) != RT_ERR_OK)
        return retVal;

    /*Set TPID to 0x88a8*/
    if ((retVal = rtl8367c_setAsicSvlanTpid(unit, 0x88a8)) != RT_ERR_OK)
        return retVal;

    /*Clean Uplink Port Mask to none*/
    if ((retVal = rtl8367c_setAsicSvlanUplinkPortMask(unit, 0)) != RT_ERR_OK)
        return retVal;

    /*Clean SVLAN Member Configuration*/
    for (i=0; i<= RTL8367C_SVIDXMAX; i++)
    {
        osal_memset(&svlanMemConf, 0, sizeof(rtl8367c_svlan_memconf_t));
        if ((retVal = rtl8367c_setAsicSvlanMemberConfiguration(unit, i, &svlanMemConf)) != RT_ERR_OK)
            return retVal;
    }

    /*Clean C2S Configuration*/
    for (i=0; i<= RTL8367C_C2SIDXMAX; i++)
    {
        if ((retVal = rtl8367c_setAsicSvlanC2SConf(unit, i, 0,0,0)) != RT_ERR_OK)
            return retVal;
    }

    /*Clean SP2C Configuration*/
    for (i=0; i <= RTL8367C_SP2CMAX ; i++)
    {
        osal_memset(&svlanSP2CConf, 0, sizeof(rtl8367c_svlan_s2c_t));
        if ((retVal = rtl8367c_setAsicSvlanSP2CConf(unit, i, &svlanSP2CConf)) != RT_ERR_OK)
            return retVal;
    }

    /*Clean MC2S Configuration*/
    for (i=0 ; i<= RTL8367C_MC2SIDXMAX; i++)
    {
        osal_memset(&svlanMC2SConf, 0, sizeof(rtl8367c_svlan_mc2s_t));
        if ((retVal = rtl8367c_setAsicSvlanMC2SConf(unit, i, &svlanMC2SConf)) != RT_ERR_OK)
            return retVal;
    }


    if ((retVal = dal_rtl8367c_svlan_lookupType_set(unit, SVLAN_LOOKUP_S64MBRCGF)) != RT_ERR_OK)
        return retVal;


    for (svidx = 0; svidx <= RTL8367C_SVIDXMAX; svidx++)
    {
        svlan_mbrCfgUsage[svidx] = FALSE;
    }


    return RT_ERR_OK;
}

/* Function Name:
 *      dal_rtl8367c_svlan_servicePort_add
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
rtksw_api_ret_t dal_rtl8367c_svlan_servicePort_add(rtksw_uint32 unit, rtksw_port_t port)
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

    if ((retVal = rtl8367c_getAsicSvlanUplinkPortMask(unit, &pmsk)) != RT_ERR_OK)
        return retVal;

    pmsk = pmsk | (1 << phyPort);

    if ((retVal = rtl8367c_setAsicSvlanUplinkPortMask(unit, pmsk)) != RT_ERR_OK)
        return retVal;

    return RT_ERR_OK;
}

/* Function Name:
 *      dal_rtl8367c_svlan_servicePort_get
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
rtksw_api_ret_t dal_rtl8367c_svlan_servicePort_get(rtksw_uint32 unit, rtksw_portmask_t *pSvlan_portmask)
{
    rtksw_api_ret_t retVal;
    rtksw_uint32 phyMbrPmask;

    /* Check initialization state */
    RTKSW_CHK_INIT_STATE(unit);

    if(NULL == pSvlan_portmask)
        return RT_ERR_NULL_POINTER;

    if ((retVal = rtl8367c_getAsicSvlanUplinkPortMask(unit, &phyMbrPmask)) != RT_ERR_OK)
        return retVal;

    if(rtksw_switch_portmask_P2L_get(unit, phyMbrPmask, pSvlan_portmask) != RT_ERR_OK)
        return RT_ERR_FAILED;


    return RT_ERR_OK;
}

/* Function Name:
 *      dal_rtl8367c_svlan_servicePort_del
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
rtksw_api_ret_t dal_rtl8367c_svlan_servicePort_del(rtksw_uint32 unit, rtksw_port_t port)
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

    if ((retVal = rtl8367c_getAsicSvlanUplinkPortMask(unit, &pmsk)) != RT_ERR_OK)
        return retVal;

    pmsk = pmsk & ~(1<<phyPort);

    if ((retVal = rtl8367c_setAsicSvlanUplinkPortMask(unit, pmsk)) != RT_ERR_OK)
        return retVal;

    return RT_ERR_OK;
}

/* Function Name:
 *      dal_rtl8367c_svlan_tpidEntry_set
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
rtksw_api_ret_t dal_rtl8367c_svlan_tpidEntry_set(rtksw_uint32 unit, rtksw_uint32 svlan_tag_id)
{
    rtksw_api_ret_t retVal;

    /* Check initialization state */
    RTKSW_CHK_INIT_STATE(unit);

    if (svlan_tag_id>RTKSW_MAX_NUM_OF_PROTO_TYPE)
        return RT_ERR_INPUT;

    if ((retVal = rtl8367c_setAsicSvlanTpid(unit, svlan_tag_id)) != RT_ERR_OK)
        return retVal;

    return RT_ERR_OK;
}

/* Function Name:
 *      dal_rtl8367c_svlan_tpidEntry_get
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
rtksw_api_ret_t dal_rtl8367c_svlan_tpidEntry_get(rtksw_uint32 unit, rtksw_uint32 *pSvlan_tag_id)
{
    rtksw_api_ret_t retVal;

    /* Check initialization state */
    RTKSW_CHK_INIT_STATE(unit);

    if(NULL == pSvlan_tag_id)
        return RT_ERR_NULL_POINTER;

    if ((retVal = rtl8367c_getAsicSvlanTpid(unit, pSvlan_tag_id)) != RT_ERR_OK)
        return retVal;

    return RT_ERR_OK;
}

/* Function Name:
 *      dal_rtl8367c_svlan_priorityRef_set
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
rtksw_api_ret_t dal_rtl8367c_svlan_priorityRef_set(rtksw_uint32 unit, rtksw_svlan_pri_ref_t ref)
{
    rtksw_api_ret_t retVal;

    /* Check initialization state */
    RTKSW_CHK_INIT_STATE(unit);

    if (ref >= REF_PRI_END)
        return RT_ERR_INPUT;

    if ((retVal = rtl8367c_setAsicSvlanPrioritySel(unit, ref)) != RT_ERR_OK)
        return retVal;

    return RT_ERR_OK;
}

/* Function Name:
 *      dal_rtl8367c_svlan_priorityRef_get
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
rtksw_api_ret_t dal_rtl8367c_svlan_priorityRef_get(rtksw_uint32 unit, rtksw_svlan_pri_ref_t *pRef)
{
    rtksw_api_ret_t retVal;

    /* Check initialization state */
    RTKSW_CHK_INIT_STATE(unit);

    if(NULL == pRef)
        return RT_ERR_NULL_POINTER;

    if ((retVal = rtl8367c_getAsicSvlanPrioritySel(unit, pRef)) != RT_ERR_OK)
        return retVal;

    return RT_ERR_OK;
}

/* Function Name:
 *      dal_rtl8367c_svlan_memberPortEntry_set
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
rtksw_api_ret_t dal_rtl8367c_svlan_memberPortEntry_set(rtksw_uint32 unit, rtksw_vlan_t svid, rtksw_svlan_memberCfg_t *pSvlan_cfg)
{
    rtksw_api_ret_t retVal;
    rtksw_int32 i;
    rtksw_uint32 empty_idx;
    rtl8367c_svlan_memconf_t svlanMemConf;
    rtksw_uint32 phyMbrPmask;
    rtksw_vlan_cfg_t vlanCfg;

    /* Check initialization state */
    RTKSW_CHK_INIT_STATE(unit);

    if(NULL == pSvlan_cfg)
        return RT_ERR_NULL_POINTER;

    if(svid > RTL8367C_VIDMAX)
        return RT_ERR_SVLAN_VID;

    RTKSW_CHK_PORTMASK_VALID(unit, &(pSvlan_cfg->memberport));

    RTKSW_CHK_PORTMASK_VALID(unit, &(pSvlan_cfg->untagport));

    if (pSvlan_cfg->fiden > RTKSW_ENABLED)
        return RT_ERR_ENABLE;

    if (pSvlan_cfg->fid > RTL8367C_FIDMAX)
        return RT_ERR_L2_FID;

    if (pSvlan_cfg->priority > RTL8367C_PRIMAX)
        return RT_ERR_VLAN_PRIORITY;

    if (pSvlan_cfg->efiden > RTKSW_ENABLED)
        return RT_ERR_ENABLE;

    if (pSvlan_cfg->efid > RTL8367C_EFIDMAX)
        return RT_ERR_L2_FID;

    if(SVLAN_LOOKUP_C4KVLAN == svlan_lookupType)
    {
        if ((retVal = dal_rtl8367c_vlan_get(unit, svid, &vlanCfg)) != RT_ERR_OK)
            return retVal;

        vlanCfg.mbr = pSvlan_cfg->memberport;
        vlanCfg.untag = pSvlan_cfg->untagport;

        if ((retVal = dal_rtl8367c_vlan_set(unit, svid, &vlanCfg)) != RT_ERR_OK)
            return retVal;

        empty_idx = 0xFF;

        for (i = 0; i<= RTL8367C_SVIDXMAX; i++)
        {
            if (svid == svlan_mbrCfgVid[i] && TRUE == svlan_mbrCfgUsage[i])
            {
                osal_memset(&svlanMemConf, 0, sizeof(rtl8367c_svlan_memconf_t));
                svlanMemConf.vs_svid        = svid;
                svlanMemConf.vs_efiden      = pSvlan_cfg->efiden;
                svlanMemConf.vs_efid        = pSvlan_cfg->efid;
                svlanMemConf.vs_priority    = pSvlan_cfg->priority;

                /*for create check*/
                if(0 == svlanMemConf.vs_efiden && 0 == svlanMemConf.vs_efid)
                    svlanMemConf.vs_efid = 1;

                if ((retVal = rtl8367c_setAsicSvlanMemberConfiguration(unit, i, &svlanMemConf)) != RT_ERR_OK)
                    return retVal;

                return RT_ERR_OK;
            }
            else if (FALSE == svlan_mbrCfgUsage[i] && 0xFF == empty_idx)
            {
                empty_idx = i;
            }
        }

        if (empty_idx != 0xFF)
        {
            svlan_mbrCfgUsage[empty_idx] = TRUE;
            svlan_mbrCfgVid[empty_idx] = svid;

            osal_memset(&svlanMemConf, 0, sizeof(rtl8367c_svlan_memconf_t));
            svlanMemConf.vs_svid        = svid;
            svlanMemConf.vs_efiden      = pSvlan_cfg->efiden;
            svlanMemConf.vs_efid        = pSvlan_cfg->efid;
            svlanMemConf.vs_priority    = pSvlan_cfg->priority;

            /*for create check*/
            if(0 == svlanMemConf.vs_efiden && 0 == svlanMemConf.vs_efid)
                svlanMemConf.vs_efid = 1;

            if ((retVal = rtl8367c_setAsicSvlanMemberConfiguration(unit, empty_idx, &svlanMemConf)) != RT_ERR_OK)
                return retVal;

        }

        return RT_ERR_OK;
    }


    empty_idx = 0xFF;

    for (i = 0; i<= RTL8367C_SVIDXMAX; i++)
    {
        /*
        if ((retVal = rtl8367c_getAsicSvlanMemberConfiguration(i, &svlanMemConf)) != RT_ERR_OK)
            return retVal;
        */
        if (svid == svlan_mbrCfgVid[i] && TRUE == svlan_mbrCfgUsage[i])
        {
            svlanMemConf.vs_svid = svid;

            if(rtksw_switch_portmask_L2P_get(unit, &(pSvlan_cfg->memberport), &phyMbrPmask) != RT_ERR_OK)
                return RT_ERR_FAILED;

            svlanMemConf.vs_member = phyMbrPmask;

            if(rtksw_switch_portmask_L2P_get(unit, &(pSvlan_cfg->untagport), &phyMbrPmask) != RT_ERR_OK)
                return RT_ERR_FAILED;

            svlanMemConf.vs_untag = phyMbrPmask;

            svlanMemConf.vs_force_fid   = pSvlan_cfg->fiden;
            svlanMemConf.vs_fid_msti    = pSvlan_cfg->fid;
            svlanMemConf.vs_priority    = pSvlan_cfg->priority;
            svlanMemConf.vs_efiden      = pSvlan_cfg->efiden;
            svlanMemConf.vs_efid        = pSvlan_cfg->efid;

            /*all items are reset means deleting*/
            if( 0 == svlanMemConf.vs_member &&
                0 == svlanMemConf.vs_untag &&
                0 == svlanMemConf.vs_force_fid &&
                0 == svlanMemConf.vs_fid_msti &&
                0 == svlanMemConf.vs_priority &&
                0 == svlanMemConf.vs_efiden &&
                0 == svlanMemConf.vs_efid)
            {
                svlan_mbrCfgUsage[i] = FALSE;
                svlan_mbrCfgVid[i] = 0;

                /* Clear SVID also */
                svlanMemConf.vs_svid = 0;
            }
            else
            {
                svlan_mbrCfgUsage[i] = TRUE;
                svlan_mbrCfgVid[i] = svlanMemConf.vs_svid;

                if(0 == svlanMemConf.vs_svid)
                {
                    /*for create check*/
                    if(0 == svlanMemConf.vs_efiden && 0 == svlanMemConf.vs_efid)
                    {
                        svlanMemConf.vs_efid = 1;
                    }
                }
            }

            if ((retVal = rtl8367c_setAsicSvlanMemberConfiguration(unit, i, &svlanMemConf)) != RT_ERR_OK)
                return retVal;

            return RT_ERR_OK;
        }
        else if (FALSE == svlan_mbrCfgUsage[i] && 0xFF == empty_idx)
        {
            empty_idx = i;
        }
    }

    if (empty_idx != 0xFF)
    {
        osal_memset(&svlanMemConf, 0, sizeof(rtl8367c_svlan_memconf_t));
        svlanMemConf.vs_svid = svid;

        if(rtksw_switch_portmask_L2P_get(unit, &(pSvlan_cfg->memberport), &phyMbrPmask) != RT_ERR_OK)
            return RT_ERR_FAILED;

        svlanMemConf.vs_member = phyMbrPmask;

        if(rtksw_switch_portmask_L2P_get(unit, &(pSvlan_cfg->untagport), &phyMbrPmask) != RT_ERR_OK)
            return RT_ERR_FAILED;

        svlanMemConf.vs_untag = phyMbrPmask;

        svlanMemConf.vs_force_fid   = pSvlan_cfg->fiden;
        svlanMemConf.vs_fid_msti    = pSvlan_cfg->fid;
        svlanMemConf.vs_priority    = pSvlan_cfg->priority;

        svlanMemConf.vs_efiden      = pSvlan_cfg->efiden;
        svlanMemConf.vs_efid        = pSvlan_cfg->efid;

        /*change efid for empty svid 0*/
        if(0 == svlanMemConf.vs_svid)
        {   /*for create check*/
            if(0 == svlanMemConf.vs_efiden && 0 == svlanMemConf.vs_efid)
            {
                svlanMemConf.vs_efid = 1;
            }
        }

        svlan_mbrCfgUsage[empty_idx] = TRUE;
        svlan_mbrCfgVid[empty_idx] = svlanMemConf.vs_svid;

        if ((retVal = rtl8367c_setAsicSvlanMemberConfiguration(unit, empty_idx, &svlanMemConf)) != RT_ERR_OK)
        {
            return retVal;
        }

        return RT_ERR_OK;
    }

    return RT_ERR_SVLAN_TABLE_FULL;
}

/* Function Name:
 *      dal_rtl8367c_svlan_memberPortEntry_get
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
rtksw_api_ret_t dal_rtl8367c_svlan_memberPortEntry_get(rtksw_uint32 unit, rtksw_vlan_t svid, rtksw_svlan_memberCfg_t *pSvlan_cfg)
{
    rtksw_api_ret_t retVal;
    rtksw_uint32 i;
    rtl8367c_svlan_memconf_t svlanMemConf;

    /* Check initialization state */
    RTKSW_CHK_INIT_STATE(unit);

    if(NULL == pSvlan_cfg)
        return RT_ERR_NULL_POINTER;

    if (svid > RTL8367C_VIDMAX)
        return RT_ERR_SVLAN_VID;


    for (i = 0; i<= RTL8367C_SVIDXMAX; i++)
    {
        if ((retVal = rtl8367c_getAsicSvlanMemberConfiguration(unit, i, &svlanMemConf)) != RT_ERR_OK)
            return retVal;

        if (svid == svlanMemConf.vs_svid)
        {
            pSvlan_cfg->svid        = svlanMemConf.vs_svid;

            if(rtksw_switch_portmask_P2L_get(unit, svlanMemConf.vs_member,&(pSvlan_cfg->memberport)) != RT_ERR_OK)
                return RT_ERR_FAILED;

            if(rtksw_switch_portmask_P2L_get(unit, svlanMemConf.vs_untag,&(pSvlan_cfg->untagport)) != RT_ERR_OK)
                return RT_ERR_FAILED;

            pSvlan_cfg->fiden       = svlanMemConf.vs_force_fid;
            pSvlan_cfg->fid         = svlanMemConf.vs_fid_msti;
            pSvlan_cfg->priority    = svlanMemConf.vs_priority;
            pSvlan_cfg->efiden      = svlanMemConf.vs_efiden;
            pSvlan_cfg->efid        = svlanMemConf.vs_efid;

            return RT_ERR_OK;
        }
    }

    return RT_ERR_SVLAN_ENTRY_NOT_FOUND;

}

/* Function Name:
 *      dal_rtl8367c_svlan_memberPortEntry_adv_set
 * Description:
 *      Configure system SVLAN member by index
 * Input:
 *      unit        - Unit ID
 *      idx         - Index (0 ~ 63)
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
 *      The API can set system 64 accepted s-tag frame format by index.
 *      - rtksw_svlan_memberCfg_t->svid is SVID of SVLAN member configuration.
 *      - rtksw_svlan_memberCfg_t->memberport is member port mask of SVLAN member configuration.
 *      - rtksw_svlan_memberCfg_t->fid is filtering database of SVLAN member configuration.
 *      - rtksw_svlan_memberCfg_t->priority is priority of SVLAN member configuration.
 */
rtksw_api_ret_t dal_rtl8367c_svlan_memberPortEntry_adv_set(rtksw_uint32 unit, rtksw_uint32 idx, rtksw_svlan_memberCfg_t *pSvlan_cfg)
{
    rtksw_api_ret_t retVal;
    rtl8367c_svlan_memconf_t svlanMemConf;
    rtksw_uint32 phyMbrPmask;

    /* Check initialization state */
    RTKSW_CHK_INIT_STATE(unit);

    if(NULL == pSvlan_cfg)
        return RT_ERR_NULL_POINTER;

    if (idx > RTL8367C_SVIDXMAX)
        return RT_ERR_SVLAN_ENTRY_INDEX;

    if (pSvlan_cfg->svid>RTL8367C_VIDMAX)
        return RT_ERR_SVLAN_VID;

    RTKSW_CHK_PORTMASK_VALID(unit, &(pSvlan_cfg->memberport));

    RTKSW_CHK_PORTMASK_VALID(unit, &(pSvlan_cfg->untagport));

    if (pSvlan_cfg->fiden > RTKSW_ENABLED)
        return RT_ERR_ENABLE;

    if (pSvlan_cfg->fid > RTL8367C_FIDMAX)
        return RT_ERR_L2_FID;

    if (pSvlan_cfg->priority > RTL8367C_PRIMAX)
        return RT_ERR_VLAN_PRIORITY;

    if (pSvlan_cfg->efiden > RTKSW_ENABLED)
        return RT_ERR_ENABLE;

    if (pSvlan_cfg->efid > RTL8367C_EFIDMAX)
        return RT_ERR_L2_FID;

    osal_memset(&svlanMemConf, 0, sizeof(rtl8367c_svlan_memconf_t));
    svlanMemConf.vs_svid        = pSvlan_cfg->svid;
    if(rtksw_switch_portmask_L2P_get(unit, &(pSvlan_cfg->memberport), &phyMbrPmask) != RT_ERR_OK)
        return RT_ERR_FAILED;

    svlanMemConf.vs_member = phyMbrPmask;

    if(rtksw_switch_portmask_L2P_get(unit, &(pSvlan_cfg->untagport), &phyMbrPmask) != RT_ERR_OK)
        return RT_ERR_FAILED;

    svlanMemConf.vs_untag = phyMbrPmask;


    svlanMemConf.vs_force_fid   = pSvlan_cfg->fiden;
    svlanMemConf.vs_fid_msti    = pSvlan_cfg->fid;
    svlanMemConf.vs_priority    = pSvlan_cfg->priority;
    svlanMemConf.vs_efiden      = pSvlan_cfg->efiden;
    svlanMemConf.vs_efid        = pSvlan_cfg->efid;

    if(0 == svlanMemConf.vs_svid &&
        0 == svlanMemConf.vs_member &&
        0 == svlanMemConf.vs_untag &&
        0 == svlanMemConf.vs_force_fid &&
        0 == svlanMemConf.vs_fid_msti &&
        0 == svlanMemConf.vs_priority &&
        0 == svlanMemConf.vs_efiden &&
        0 == svlanMemConf.vs_efid)
    {
        svlan_mbrCfgUsage[idx] = FALSE;
        svlan_mbrCfgVid[idx] = 0;
    }
    else
    {
        svlan_mbrCfgUsage[idx] = TRUE;
        svlan_mbrCfgVid[idx] = svlanMemConf.vs_svid;
    }

    if ((retVal = rtl8367c_setAsicSvlanMemberConfiguration(unit, idx, &svlanMemConf)) != RT_ERR_OK)
        return retVal;


    return RT_ERR_OK;
}

/* Function Name:
 *      dal_rtl8367c_svlan_memberPortEntry_adv_get
 * Description:
 *      Get SVLAN member Configure by index.
 * Input:
 *      unit        - Unit ID
 *      idx         - Index (0 ~ 63)
 * Output:
 *      pSvlan_cfg  - SVLAN member configuration
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
rtksw_api_ret_t dal_rtl8367c_svlan_memberPortEntry_adv_get(rtksw_uint32 unit, rtksw_uint32 idx, rtksw_svlan_memberCfg_t *pSvlan_cfg)
{
    rtksw_api_ret_t retVal;
    rtl8367c_svlan_memconf_t svlanMemConf;

    /* Check initialization state */
    RTKSW_CHK_INIT_STATE(unit);

    if(NULL == pSvlan_cfg)
        return RT_ERR_NULL_POINTER;

    if (idx > RTL8367C_SVIDXMAX)
        return RT_ERR_SVLAN_ENTRY_INDEX;

    if ((retVal = rtl8367c_getAsicSvlanMemberConfiguration(unit, idx, &svlanMemConf)) != RT_ERR_OK)
        return retVal;

    pSvlan_cfg->svid        = svlanMemConf.vs_svid;
    if(rtksw_switch_portmask_P2L_get(unit, svlanMemConf.vs_member,&(pSvlan_cfg->memberport)) != RT_ERR_OK)
        return RT_ERR_FAILED;

    if(rtksw_switch_portmask_P2L_get(unit, svlanMemConf.vs_untag,&(pSvlan_cfg->untagport)) != RT_ERR_OK)
        return RT_ERR_FAILED;

    pSvlan_cfg->fiden       = svlanMemConf.vs_force_fid;
    pSvlan_cfg->fid         = svlanMemConf.vs_fid_msti;
    pSvlan_cfg->priority    = svlanMemConf.vs_priority;
    pSvlan_cfg->efiden      = svlanMemConf.vs_efiden;
    pSvlan_cfg->efid        = svlanMemConf.vs_efid;

    return RT_ERR_OK;

}

/* Function Name:
 *      dal_rtl8367c_svlan_defaultSvlan_set
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
rtksw_api_ret_t dal_rtl8367c_svlan_defaultSvlan_set(rtksw_uint32 unit, rtksw_port_t port, rtksw_vlan_t svid)
{
    rtksw_api_ret_t retVal;
    rtksw_uint32 i;
    rtl8367c_svlan_memconf_t svlanMemConf;

    /* Check initialization state */
    RTKSW_CHK_INIT_STATE(unit);

    /* Check port Valid */
    RTKSW_CHK_PORT_VALID(unit, port);

    /* svid must be 0~4095 */
    if (svid > RTL8367C_VIDMAX)
        return RT_ERR_SVLAN_VID;

    for (i = 0; i < RTL8367C_SVIDXNO; i++)
    {
        if ((retVal = rtl8367c_getAsicSvlanMemberConfiguration(unit, i, &svlanMemConf)) != RT_ERR_OK)
            return retVal;

        if (svid == svlanMemConf.vs_svid)
        {
            if ((retVal = rtl8367c_setAsicSvlanDefaultVlan(unit, rtksw_switch_port_L2P_get(unit, port), i)) != RT_ERR_OK)
                return retVal;

            return RT_ERR_OK;
        }
    }

    return RT_ERR_SVLAN_ENTRY_NOT_FOUND;
}

/* Function Name:
 *      dal_rtl8367c_svlan_defaultSvlan_get
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
rtksw_api_ret_t dal_rtl8367c_svlan_defaultSvlan_get(rtksw_uint32 unit, rtksw_port_t port, rtksw_vlan_t *pSvid)
{
    rtksw_api_ret_t retVal;
    rtksw_uint32 idx;
    rtl8367c_svlan_memconf_t svlanMemConf;

    /* Check initialization state */
    RTKSW_CHK_INIT_STATE(unit);

    if(NULL == pSvid)
        return RT_ERR_NULL_POINTER;

    /* Check port Valid */
    RTKSW_CHK_PORT_VALID(unit, port);

    if ((retVal = rtl8367c_getAsicSvlanDefaultVlan(unit, rtksw_switch_port_L2P_get(unit, port), &idx)) != RT_ERR_OK)
        return retVal;

    if ((retVal = rtl8367c_getAsicSvlanMemberConfiguration(unit, idx, &svlanMemConf)) != RT_ERR_OK)
        return retVal;

    *pSvid = svlanMemConf.vs_svid;

    return RT_ERR_OK;
}

/* Function Name:
 *      dal_rtl8367c_svlan_c2s_add
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
rtksw_api_ret_t dal_rtl8367c_svlan_c2s_add(rtksw_uint32 unit, rtksw_vlan_t vid, rtksw_port_t src_port, rtksw_vlan_t svid)
{
    rtksw_api_ret_t retVal, i;
    rtksw_uint32 empty_idx;
    rtksw_uint32 evid, pmsk, svidx, c2s_svidx;
    rtl8367c_svlan_memconf_t svlanMemConf;
    rtksw_port_t phyPort;
    rtksw_uint16 doneFlag;


    /* Check initialization state */
    RTKSW_CHK_INIT_STATE(unit);


    if (vid > RTL8367C_VIDMAX)
        return RT_ERR_VLAN_VID;

    if (svid > RTL8367C_VIDMAX)
        return RT_ERR_SVLAN_VID;

    /* Check port Valid */
    RTKSW_CHK_PORT_VALID(unit, src_port);

    phyPort = rtksw_switch_port_L2P_get(unit, src_port);

    empty_idx = 0xFFFF;
    svidx = 0xFFFF;
    doneFlag = FALSE;

    for (i = 0; i<= RTL8367C_SVIDXMAX; i++)
    {
        if ((retVal = rtl8367c_getAsicSvlanMemberConfiguration(unit, i, &svlanMemConf)) != RT_ERR_OK)
            return retVal;

        if (svid == svlanMemConf.vs_svid)
        {
            svidx = i;
            break;
        }
    }

    if (0xFFFF == svidx)
        return RT_ERR_SVLAN_VID;

    for (i=RTL8367C_C2SIDXMAX; i>=0; i--)
    {
        if ((retVal = rtl8367c_getAsicSvlanC2SConf(unit, i, &evid, &pmsk, &c2s_svidx)) != RT_ERR_OK)
                return retVal;

        if (pmsk != 0) /* Valid entry */
        {
            if (evid == vid)
            {
                /* Check Src_port */
                if(pmsk & (1 << phyPort))
                {
                    /* Check SVIDX */
                    if(c2s_svidx == svidx)
                    {
                        /* All the same, do nothing */
                        return RT_ERR_OK;
                    }
                    else
                    {
                        /* New svidx, remove src_port and find a new slot to add a new enrty */
                        pmsk = pmsk & ~(1 << phyPort);
                        if(pmsk == 0)
                        {
                            evid = 0;
                            c2s_svidx = 0;
                        }

                        if ((retVal = rtl8367c_setAsicSvlanC2SConf(unit, i, evid, pmsk, c2s_svidx)) != RT_ERR_OK)
                            return retVal;
                    }
                }
                else
                {
                    if(c2s_svidx == svidx && doneFlag == FALSE)
                    {
                        pmsk = pmsk | (1 << phyPort);
                        if ((retVal = rtl8367c_setAsicSvlanC2SConf(unit, i, evid, pmsk, svidx)) != RT_ERR_OK)
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
       if ((retVal = rtl8367c_setAsicSvlanC2SConf(unit, empty_idx, vid, (1<<phyPort), svidx)) != RT_ERR_OK)
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
 *      dal_rtl8367c_svlan_c2s_del
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
rtksw_api_ret_t dal_rtl8367c_svlan_c2s_del(rtksw_uint32 unit, rtksw_vlan_t vid, rtksw_port_t src_port)
{
    rtksw_api_ret_t retVal;
    rtksw_uint32 i;
    rtksw_uint32 evid, pmsk, svidx;
    rtksw_port_t phyPort;

    /* Check initialization state */
    RTKSW_CHK_INIT_STATE(unit);

    if (vid > RTL8367C_EVIDMAX)
        return RT_ERR_VLAN_VID;

    /* Check port Valid */
    RTKSW_CHK_PORT_VALID(unit, src_port);
    phyPort = rtksw_switch_port_L2P_get(unit, src_port);
    if (phyPort == UNDEFINE_PHY_PORT)
        return RT_ERR_PORT_ID;

    for (i = 0; i <= RTL8367C_C2SIDXMAX; i++)
    {
        if ((retVal = rtl8367c_getAsicSvlanC2SConf(unit, i, &evid, &pmsk, &svidx)) != RT_ERR_OK)
            return retVal;

        if (evid == vid)
        {
            if(pmsk & (1 << phyPort))
            {
                pmsk = pmsk & ~(1 << phyPort);
                if(pmsk == 0)
                {
                    vid = 0;
                    svidx = 0;
                }

                if ((retVal = rtl8367c_setAsicSvlanC2SConf(unit, i, vid, pmsk, svidx)) != RT_ERR_OK)
                    return retVal;

                return RT_ERR_OK;
            }
        }
    }

    return RT_ERR_OUT_OF_RANGE;
}

/* Function Name:
 *      dal_rtl8367c_svlan_c2s_get
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
rtksw_api_ret_t dal_rtl8367c_svlan_c2s_get(rtksw_uint32 unit, rtksw_vlan_t vid, rtksw_port_t src_port, rtksw_vlan_t *pSvid)
{
    rtksw_api_ret_t retVal;
    rtksw_uint32 i;
    rtksw_uint32 evid, pmsk, svidx;
    rtl8367c_svlan_memconf_t svlanMemConf;
    rtksw_port_t phyPort;

    /* Check initialization state */
    RTKSW_CHK_INIT_STATE(unit);

    if(NULL == pSvid)
        return RT_ERR_NULL_POINTER;

    if (vid > RTL8367C_VIDMAX)
        return RT_ERR_VLAN_VID;

    /* Check port Valid */
    RTKSW_CHK_PORT_VALID(unit, src_port);
    phyPort = rtksw_switch_port_L2P_get(unit, src_port);
    if (phyPort == UNDEFINE_PHY_PORT)
        return RT_ERR_PORT_ID;

    for (i = 0; i <= RTL8367C_C2SIDXMAX; i++)
    {
        if ((retVal = rtl8367c_getAsicSvlanC2SConf(unit, i, &evid, &pmsk, &svidx)) != RT_ERR_OK)
            return retVal;

        if (evid == vid)
        {
            if(pmsk & (1 << phyPort))
            {
                if ((retVal = rtl8367c_getAsicSvlanMemberConfiguration(unit, svidx, &svlanMemConf)) != RT_ERR_OK)
                    return retVal;

                *pSvid = svlanMemConf.vs_svid;
                return RT_ERR_OK;
            }
        }
    }

    return RT_ERR_OUT_OF_RANGE;
}

/* Function Name:
 *      dal_rtl8367c_svlan_untag_action_set
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
rtksw_api_ret_t dal_rtl8367c_svlan_untag_action_set(rtksw_uint32 unit, rtksw_svlan_untag_action_t action, rtksw_vlan_t svid)
{
    rtksw_api_ret_t   retVal;
    rtksw_uint32      i;
    rtl8367c_svlan_memconf_t svlanMemConf;

    /* Check initialization state */
    RTKSW_CHK_INIT_STATE(unit);

    if (action >= UNTAG_END)
        return RT_ERR_OUT_OF_RANGE;

    if(action == UNTAG_ASSIGN)
    {
        if (svid > RTL8367C_VIDMAX)
            return RT_ERR_SVLAN_VID;
    }

    if ((retVal = rtl8367c_setAsicSvlanIngressUntag(unit, (rtksw_uint32)action)) != RT_ERR_OK)
        return retVal;

    if(action == UNTAG_ASSIGN)
    {
        for (i = 0; i < RTL8367C_SVIDXNO; i++)
        {
            if ((retVal = rtl8367c_getAsicSvlanMemberConfiguration(unit, i, &svlanMemConf)) != RT_ERR_OK)
                return retVal;

            if (svid == svlanMemConf.vs_svid)
            {
                if ((retVal = rtl8367c_setAsicSvlanUntagVlan(unit, i)) != RT_ERR_OK)
                    return retVal;

                return RT_ERR_OK;
            }
        }

        return RT_ERR_SVLAN_ENTRY_NOT_FOUND;
    }

    return RT_ERR_OK;
}

/* Function Name:
 *      dal_rtl8367c_svlan_untag_action_get
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
rtksw_api_ret_t dal_rtl8367c_svlan_untag_action_get(rtksw_uint32 unit, rtksw_svlan_untag_action_t *pAction, rtksw_vlan_t *pSvid)
{
    rtksw_api_ret_t   retVal;
    rtksw_uint32      svidx;
    rtl8367c_svlan_memconf_t svlanMemConf;

    /* Check initialization state */
    RTKSW_CHK_INIT_STATE(unit);

    if(NULL == pAction || NULL == pSvid)
        return RT_ERR_NULL_POINTER;

    if ((retVal = rtl8367c_getAsicSvlanIngressUntag(unit, pAction)) != RT_ERR_OK)
        return retVal;

    if(*pAction == UNTAG_ASSIGN)
    {
        if ((retVal = rtl8367c_getAsicSvlanUntagVlan(unit, &svidx)) != RT_ERR_OK)
            return retVal;

        if ((retVal = rtl8367c_getAsicSvlanMemberConfiguration(unit, svidx, &svlanMemConf)) != RT_ERR_OK)
            return retVal;

        *pSvid = svlanMemConf.vs_svid;
    }

    return RT_ERR_OK;
}

/* Function Name:
 *      dal_rtl8367c_svlan_unmatch_action_set
 * Description:
 *      Configure Action of downstream Unmatch packet
 * Input:
 *      unit        - Unit ID
 *      action      - Action for Unmatch
 *      svid        - The SVID assigned to Unmatch packet
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
 *      The API can configure action of downstream Un-match packet. A SVID assigned
 *      to the un-match is also supported by this API. The parameter od svid is
 *      only refernced when the action is set to UNMATCH_ASSIGN
 */
rtksw_api_ret_t dal_rtl8367c_svlan_unmatch_action_set(rtksw_uint32 unit, rtksw_svlan_unmatch_action_t action, rtksw_vlan_t svid)
{
    rtksw_api_ret_t   retVal;
    rtksw_uint32      i;
    rtl8367c_svlan_memconf_t svlanMemConf;

    /* Check initialization state */
    RTKSW_CHK_INIT_STATE(unit);

    if (action >= UNMATCH_END)
        return RT_ERR_OUT_OF_RANGE;

    if (action == UNMATCH_ASSIGN)
    {
        if (svid > RTL8367C_VIDMAX)
            return RT_ERR_SVLAN_VID;
    }

    if ((retVal = rtl8367c_setAsicSvlanIngressUnmatch(unit, (rtksw_uint32)action)) != RT_ERR_OK)
        return retVal;

    if(action == UNMATCH_ASSIGN)
    {
        for (i = 0; i < RTL8367C_SVIDXNO; i++)
        {
            if ((retVal = rtl8367c_getAsicSvlanMemberConfiguration(unit, i, &svlanMemConf)) != RT_ERR_OK)
                return retVal;

            if (svid == svlanMemConf.vs_svid)
            {
                if ((retVal = rtl8367c_setAsicSvlanUnmatchVlan(unit, i)) != RT_ERR_OK)
                    return retVal;

                return RT_ERR_OK;
            }
        }

        return RT_ERR_SVLAN_ENTRY_NOT_FOUND;
    }

    return RT_ERR_OK;
}

/* Function Name:
 *      dal_rtl8367c_svlan_unmatch_action_get
 * Description:
 *      Get Action of downstream Unmatch packet
 * Input:
 *      unit        - Unit ID
 * Output:
 *      pAction  - Action for Unmatch
 *      pSvid    - The SVID assigned to Unmatch packet
 * Return:
 *      RT_ERR_OK                       - OK
 *      RT_ERR_FAILED                   - Failed
 *      RT_ERR_SMI                      - SMI access error
 *      RT_ERR_SVLAN_VID                - Invalid SVLAN VID parameter.
 *      RT_ERR_SVLAN_ENTRY_NOT_FOUND    - specified svlan entry not found.
 *      RT_ERR_OUT_OF_RANGE             - input out of range.
 *      RT_ERR_INPUT                    - Invalid input parameters.
 * Note:
 *      The API can Get action of downstream Un-match packet. A SVID assigned
 *      to the un-match is also retrieved by this API. The parameter pSvid is
 *      only refernced when the action is UNMATCH_ASSIGN
 */
rtksw_api_ret_t dal_rtl8367c_svlan_unmatch_action_get(rtksw_uint32 unit, rtksw_svlan_unmatch_action_t *pAction, rtksw_vlan_t *pSvid)
{
    rtksw_api_ret_t   retVal;
    rtksw_uint32      svidx;
    rtl8367c_svlan_memconf_t svlanMemConf;

    /* Check initialization state */
    RTKSW_CHK_INIT_STATE(unit);

    if(NULL == pAction || NULL == pSvid)
        return RT_ERR_NULL_POINTER;

    if ((retVal = rtl8367c_getAsicSvlanIngressUnmatch(unit, pAction)) != RT_ERR_OK)
        return retVal;

    if(*pAction == UNMATCH_ASSIGN)
    {
        if ((retVal = rtl8367c_getAsicSvlanUnmatchVlan(unit, &svidx)) != RT_ERR_OK)
            return retVal;

        if ((retVal = rtl8367c_getAsicSvlanMemberConfiguration(unit, svidx, &svlanMemConf)) != RT_ERR_OK)
            return retVal;

        *pSvid = svlanMemConf.vs_svid;
    }

    return RT_ERR_OK;
}



/* Function Name:
 *      dal_rtl8367c_svlan_unassign_action_set
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
rtksw_api_ret_t dal_rtl8367c_svlan_unassign_action_set(rtksw_uint32 unit, rtksw_svlan_unassign_action_t action)
{
    rtksw_api_ret_t   retVal;

    /* Check initialization state */
    RTKSW_CHK_INIT_STATE(unit);

    if (action >= UNASSIGN_END)
        return RT_ERR_OUT_OF_RANGE;

    retVal = rtl8367c_setAsicSvlanEgressUnassign(unit, (rtksw_uint32)action);

    return retVal;
}

/* Function Name:
 *      dal_rtl8367c_svlan_unassign_action_get
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
rtksw_api_ret_t dal_rtl8367c_svlan_unassign_action_get(rtksw_uint32 unit, rtksw_svlan_unassign_action_t *pAction)
{
    rtksw_api_ret_t   retVal;

    /* Check initialization state */
    RTKSW_CHK_INIT_STATE(unit);

    if(NULL == pAction)
        return RT_ERR_NULL_POINTER;

    retVal = rtl8367c_getAsicSvlanEgressUnassign(unit, pAction);

    return retVal;
}

/* Function Name:
 *      dal_rtl8367c_svlan_dmac_vidsel_set
 * Description:
 *      Set DMAC CVID selection
 * Input:
 *      unit        - Unit ID
 *      port        - Port
 *      enable      - state of DMAC CVID Selection
 * Output:
 *      None.
 * Return:
 *      RT_ERR_OK                       - OK
 *      RT_ERR_FAILED                   - Failed
 *      RT_ERR_SMI                      - SMI access error
 *      RT_ERR_SVLAN_VID                - Invalid SVLAN VID parameter.
 *      RT_ERR_SVLAN_ENTRY_NOT_FOUND    - specified svlan entry not found.
 *      RT_ERR_OUT_OF_RANGE             - input out of range.
 *      RT_ERR_INPUT                    - Invalid input parameters.
 * Note:
 *      This API can set DMAC CVID Selection state
 */
rtksw_api_ret_t dal_rtl8367c_svlan_dmac_vidsel_set(rtksw_uint32 unit, rtksw_port_t port, rtksw_enable_t enable)
{
    rtksw_api_ret_t   retVal;

    /* Check initialization state */
    RTKSW_CHK_INIT_STATE(unit);

    /* Check port Valid */
    RTKSW_CHK_PORT_VALID(unit, port);

    if (enable >= RTKSW_ENABLE_END)
        return RT_ERR_ENABLE;

    if ((retVal = rtl8367c_setAsicSvlanDmacCvidSel(unit, rtksw_switch_port_L2P_get(unit, port), enable)) != RT_ERR_OK)
            return retVal;

    return RT_ERR_OK;
}

/* Function Name:
 *      dal_rtl8367c_svlan_dmac_vidsel_get
 * Description:
 *      Get DMAC CVID selection
 * Input:
 *      unit        - Unit ID
 *      port        - Port
 * Output:
 *      pEnable - state of DMAC CVID Selection
 * Return:
 *      RT_ERR_OK                       - OK
 *      RT_ERR_FAILED                   - Failed
 *      RT_ERR_SMI                      - SMI access error
 *      RT_ERR_SVLAN_VID                - Invalid SVLAN VID parameter.
 *      RT_ERR_SVLAN_ENTRY_NOT_FOUND    - specified svlan entry not found.
 *      RT_ERR_OUT_OF_RANGE             - input out of range.
 *      RT_ERR_INPUT                    - Invalid input parameters.
 * Note:
 *      This API can get DMAC CVID Selection state
 */
rtksw_api_ret_t dal_rtl8367c_svlan_dmac_vidsel_get(rtksw_uint32 unit, rtksw_port_t port, rtksw_enable_t *pEnable)
{
    rtksw_api_ret_t   retVal;

    /* Check initialization state */
    RTKSW_CHK_INIT_STATE(unit);

    if(NULL == pEnable)
        return RT_ERR_NULL_POINTER;

    /* Check port Valid */
    RTKSW_CHK_PORT_VALID(unit, port);

    if ((retVal = rtl8367c_getAsicSvlanDmacCvidSel(unit, rtksw_switch_port_L2P_get(unit, port), pEnable)) != RT_ERR_OK)
            return retVal;

    return RT_ERR_OK;
}
/* Function Name:
 *      dal_rtl8367c_svlan_ipmc2s_add
 * Description:
 *      add ip multicast address to SVLAN
 * Input:
 *      unit        - Unit ID
 *      svid        - SVLAN VID
 *      ipmc        - ip multicast address
 *      ipmcMsk     - ip multicast mask
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
 *      The API can set IP mutlicast to SVID configuration. If upstream packet is IPv4 multicast
 *      packet and DIP is matched MC2S configuration, ASIC will assign egress SVID to the packet.
 *      There are 32 SVLAN multicast configurations for IP and L2 multicast.
 */
rtksw_api_ret_t dal_rtl8367c_svlan_ipmc2s_add(rtksw_uint32 unit, ipaddr_t ipmc, ipaddr_t ipmcMsk, rtksw_vlan_t svid)
{
    rtksw_api_ret_t retVal, i;
    rtksw_uint32 empty_idx;
    rtksw_uint32 svidx;
    rtl8367c_svlan_memconf_t svlanMemConf;
    rtl8367c_svlan_mc2s_t svlanMC2SConf;

    /* Check initialization state */
    RTKSW_CHK_INIT_STATE(unit);

    if (svid > RTL8367C_VIDMAX)
        return RT_ERR_SVLAN_VID;

    if ((ipmc&0xF0000000)!=0xE0000000)
        return RT_ERR_INPUT;

    svidx = 0xFFFF;

    for (i = 0; i < RTL8367C_SVIDXNO; i++)
    {
        if ((retVal = rtl8367c_getAsicSvlanMemberConfiguration(unit, i, &svlanMemConf)) != RT_ERR_OK)
            return retVal;

        if (svid == svlanMemConf.vs_svid)
        {
            svidx = i;
            break;
        }
    }

    if (0xFFFF == svidx)
            return RT_ERR_SVLAN_ENTRY_NOT_FOUND;


    empty_idx = 0xFFFF;

    for (i = RTL8367C_MC2SIDXMAX; i >= 0; i--)
    {
        if ((retVal = rtl8367c_getAsicSvlanMC2SConf(unit, i, &svlanMC2SConf)) != RT_ERR_OK)
            return retVal;

        if (TRUE == svlanMC2SConf.valid)
        {
            if (svlanMC2SConf.format == SVLAN_MC2S_MODE_IP &&
                svlanMC2SConf.sdata==ipmc&&
                svlanMC2SConf.smask==ipmcMsk)
            {
                svlanMC2SConf.svidx = svidx;
                if ((retVal = rtl8367c_setAsicSvlanMC2SConf(unit, i, &svlanMC2SConf)) != RT_ERR_OK)
                    return retVal;
            }
        }
        else
        {
            empty_idx = i;
        }
    }

    if (empty_idx!=0xFFFF)
    {
        svlanMC2SConf.valid = TRUE;
        svlanMC2SConf.svidx = svidx;
        svlanMC2SConf.format = SVLAN_MC2S_MODE_IP;
        svlanMC2SConf.sdata = ipmc;
        svlanMC2SConf.smask = ipmcMsk;
        if ((retVal = rtl8367c_setAsicSvlanMC2SConf(unit, empty_idx, &svlanMC2SConf)) != RT_ERR_OK)
            return retVal;
        return RT_ERR_OK;
    }

    return RT_ERR_OUT_OF_RANGE;

}

/* Function Name:
 *      dal_rtl8367c_svlan_ipmc2s_del
 * Description:
 *      delete ip multicast address to SVLAN
 * Input:
 *      unit        - Unit ID
 *      ipmc        - ip multicast address
 *      ipmcMsk     - ip multicast mask
 * Output:
 *      None
 * Return:
 *      RT_ERR_OK               - OK
 *      RT_ERR_FAILED           - Failed
 *      RT_ERR_SMI              - SMI access error
 *      RT_ERR_SVLAN_VID        - Invalid SVLAN VID parameter.
 *      RT_ERR_OUT_OF_RANGE     - input out of range.
 * Note:
 *      The API can delete IP mutlicast to SVID configuration. There are 32 SVLAN multicast configurations for IP and L2 multicast.
 */
rtksw_api_ret_t dal_rtl8367c_svlan_ipmc2s_del(rtksw_uint32 unit, ipaddr_t ipmc, ipaddr_t ipmcMsk)
{
    rtksw_api_ret_t retVal;
    rtksw_uint32 i;
    rtl8367c_svlan_mc2s_t svlanMC2SConf;

    /* Check initialization state */
    RTKSW_CHK_INIT_STATE(unit);

    if ((ipmc&0xF0000000)!=0xE0000000)
        return RT_ERR_INPUT;

    for (i = 0; i <= RTL8367C_MC2SIDXMAX; i++)
    {
        if ((retVal = rtl8367c_getAsicSvlanMC2SConf(unit, i, &svlanMC2SConf)) != RT_ERR_OK)
            return retVal;

        if (TRUE == svlanMC2SConf.valid)
        {
            if (svlanMC2SConf.format == SVLAN_MC2S_MODE_IP &&
                svlanMC2SConf.sdata==ipmc&&
                svlanMC2SConf.smask==ipmcMsk)
            {
                osal_memset(&svlanMC2SConf, 0, sizeof(rtl8367c_svlan_mc2s_t));
                if ((retVal = rtl8367c_setAsicSvlanMC2SConf(unit, i, &svlanMC2SConf)) != RT_ERR_OK)
                    return retVal;
                return RT_ERR_OK;
            }
        }
    }

    return RT_ERR_OUT_OF_RANGE;
}

/* Function Name:
 *      dal_rtl8367c_svlan_ipmc2s_get
 * Description:
 *      Get ip multicast address to SVLAN
 * Input:
 *      unit        - Unit ID
 *      ipmc        - ip multicast address
 *      ipmcMsk     - ip multicast mask
 * Output:
 *      pSvid - SVLAN VID
 * Return:
 *      RT_ERR_OK           - OK
 *      RT_ERR_FAILED       - Failed
 *      RT_ERR_SMI          - SMI access error
 *      RT_ERR_INPUT        - Invalid input parameters.
 *      RT_ERR_OUT_OF_RANGE - input out of range.
 * Note:
 *      The API can get IP mutlicast to SVID configuration. There are 32 SVLAN multicast configurations for IP and L2 multicast.
 */
rtksw_api_ret_t dal_rtl8367c_svlan_ipmc2s_get(rtksw_uint32 unit, ipaddr_t ipmc, ipaddr_t ipmcMsk, rtksw_vlan_t *pSvid)
{
    rtksw_api_ret_t retVal;
    rtksw_uint32 i;
    rtl8367c_svlan_memconf_t svlanMemConf;
    rtl8367c_svlan_mc2s_t svlanMC2SConf;

    /* Check initialization state */
    RTKSW_CHK_INIT_STATE(unit);

    if(NULL == pSvid)
        return RT_ERR_NULL_POINTER;

    if ((ipmc&0xF0000000)!=0xE0000000)
        return RT_ERR_INPUT;

    for (i = 0; i <= RTL8367C_MC2SIDXMAX; i++)
    {
        if ((retVal = rtl8367c_getAsicSvlanMC2SConf(unit, i, &svlanMC2SConf)) != RT_ERR_OK)
            return retVal;

        if (TRUE == svlanMC2SConf.valid &&
            svlanMC2SConf.format == SVLAN_MC2S_MODE_IP &&
            svlanMC2SConf.sdata == ipmc &&
            svlanMC2SConf.smask == ipmcMsk)
        {
            if ((retVal = rtl8367c_getAsicSvlanMemberConfiguration(unit, svlanMC2SConf.svidx, &svlanMemConf)) != RT_ERR_OK)
                return retVal;
            *pSvid = svlanMemConf.vs_svid;
            return RT_ERR_OK;
        }
    }

    return RT_ERR_OUT_OF_RANGE;
}

/* Function Name:
 *      dal_rtl8367c_svlan_l2mc2s_add
 * Description:
 *      Add L2 multicast address to SVLAN
 * Input:
 *      unit        - Unit ID
 *      mac         - L2 multicast address
 *      macMsk      - L2 multicast address mask
 *      svid        - SVLAN VID
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
 *      The API can set L2 Mutlicast to SVID configuration. If upstream packet is L2 multicast
 *      packet and DMAC is matched, ASIC will assign egress SVID to the packet. There are 32
 *      SVLAN multicast configurations for IP and L2 multicast.
 */
rtksw_api_ret_t dal_rtl8367c_svlan_l2mc2s_add(rtksw_uint32 unit, rtksw_mac_t mac, rtksw_mac_t macMsk, rtksw_vlan_t svid)
{
    rtksw_api_ret_t retVal, i;
    rtksw_uint32 empty_idx;
    rtksw_uint32 svidx, l2add, l2Mask;
    rtl8367c_svlan_memconf_t svlanMemConf;
    rtl8367c_svlan_mc2s_t svlanMC2SConf;

    /* Check initialization state */
    RTKSW_CHK_INIT_STATE(unit);

    if (svid > RTL8367C_VIDMAX)
        return RT_ERR_SVLAN_VID;

    if (mac.octet[0]!= 1&&mac.octet[1]!=0)
        return RT_ERR_INPUT;

    l2add = (mac.octet[2] << 24) | (mac.octet[3] << 16) | (mac.octet[4] << 8) | mac.octet[5];
    l2Mask = (macMsk.octet[2] << 24) | (macMsk.octet[3] << 16) | (macMsk.octet[4] << 8) | macMsk.octet[5];

    svidx = 0xFFFF;

    for (i = 0; i < RTL8367C_SVIDXNO; i++)
    {
        if ((retVal = rtl8367c_getAsicSvlanMemberConfiguration(unit, i, &svlanMemConf)) != RT_ERR_OK)
            return retVal;

        if (svid == svlanMemConf.vs_svid)
        {
            svidx = i;
            break;
        }
    }

    if (0xFFFF == svidx)
        return RT_ERR_SVLAN_ENTRY_NOT_FOUND;

    empty_idx = 0xFFFF;

    for (i = RTL8367C_MC2SIDXMAX; i >=0; i--)
    {
        if ((retVal = rtl8367c_getAsicSvlanMC2SConf(unit, i, &svlanMC2SConf)) != RT_ERR_OK)
            return retVal;

        if (TRUE == svlanMC2SConf.valid)
        {
            if (svlanMC2SConf.format == SVLAN_MC2S_MODE_MAC &&
                svlanMC2SConf.sdata==l2add&&
                svlanMC2SConf.smask==l2Mask)
            {
                svlanMC2SConf.svidx = svidx;
                if ((retVal = rtl8367c_setAsicSvlanMC2SConf(unit, i, &svlanMC2SConf)) != RT_ERR_OK)
                    return retVal;
            }
        }
        else
        {
            empty_idx = i;
        }
    }

    if (empty_idx!=0xFFFF)
    {
        svlanMC2SConf.valid = TRUE;
        svlanMC2SConf.svidx = svidx;
        svlanMC2SConf.format = SVLAN_MC2S_MODE_MAC;
        svlanMC2SConf.sdata = l2add;
        svlanMC2SConf.smask = l2Mask;

        if ((retVal = rtl8367c_setAsicSvlanMC2SConf(unit, empty_idx, &svlanMC2SConf)) != RT_ERR_OK)
            return retVal;
        return RT_ERR_OK;
    }

    return RT_ERR_OUT_OF_RANGE;
}

/* Function Name:
 *      dal_rtl8367c_svlan_l2mc2s_del
 * Description:
 *      delete L2 multicast address to SVLAN
 * Input:
 *      unit        - Unit ID
 *      mac         - L2 multicast address
 *      macMsk      - L2 multicast address mask
 * Output:
 *      None
 * Return:
 *      RT_ERR_OK               - OK
 *      RT_ERR_FAILED           - Failed
 *      RT_ERR_SMI              - SMI access error
 *      RT_ERR_SVLAN_VID        - Invalid SVLAN VID parameter.
 *      RT_ERR_OUT_OF_RANGE     - input out of range.
 * Note:
 *      The API can delete Mutlicast to SVID configuration. There are 32 SVLAN multicast configurations for IP and L2 multicast.
 */
rtksw_api_ret_t dal_rtl8367c_svlan_l2mc2s_del(rtksw_uint32 unit, rtksw_mac_t mac, rtksw_mac_t macMsk)
{
    rtksw_api_ret_t retVal;
    rtksw_uint32 i;
    rtksw_uint32 l2add, l2Mask;
    rtl8367c_svlan_mc2s_t svlanMC2SConf;

    /* Check initialization state */
    RTKSW_CHK_INIT_STATE(unit);

    if (mac.octet[0]!= 1&&mac.octet[1]!=0)
        return RT_ERR_INPUT;

    l2add = (mac.octet[2] << 24) | (mac.octet[3] << 16) | (mac.octet[4] << 8) | mac.octet[5];
    l2Mask = (macMsk.octet[2] << 24) | (macMsk.octet[3] << 16) | (macMsk.octet[4] << 8) | macMsk.octet[5];

    for (i = 0; i <= RTL8367C_MC2SIDXMAX; i++)
    {
        if ((retVal = rtl8367c_getAsicSvlanMC2SConf(unit, i, &svlanMC2SConf)) != RT_ERR_OK)
            return retVal;

        if (TRUE == svlanMC2SConf.valid)
        {
            if (svlanMC2SConf.format == SVLAN_MC2S_MODE_MAC &&
                svlanMC2SConf.sdata==l2add&&
                svlanMC2SConf.smask==l2Mask)
            {
                osal_memset(&svlanMC2SConf, 0, sizeof(rtl8367c_svlan_mc2s_t));
                if ((retVal = rtl8367c_setAsicSvlanMC2SConf(unit, i, &svlanMC2SConf)) != RT_ERR_OK)
                    return retVal;
                return RT_ERR_OK;
            }
        }
    }

    return RT_ERR_OUT_OF_RANGE;
}

/* Function Name:
 *      dal_rtl8367c_svlan_l2mc2s_get
 * Description:
 *      Get L2 multicast address to SVLAN
 * Input:
 *      unit        - Unit ID
 *      mac         - L2 multicast address
 *      macMsk      - L2 multicast address mask
 * Output:
 *      pSvid   - SVLAN VID
 * Return:
 *      RT_ERR_OK               - OK
 *      RT_ERR_FAILED           - Failed
 *      RT_ERR_SMI              - SMI access error
 *      RT_ERR_INPUT            - Invalid input parameters.
 *      RT_ERR_OUT_OF_RANGE     - input out of range.
 * Note:
 *      The API can get L2 mutlicast to SVID configuration. There are 32 SVLAN multicast configurations for IP and L2 multicast.
 */
rtksw_api_ret_t dal_rtl8367c_svlan_l2mc2s_get(rtksw_uint32 unit, rtksw_mac_t mac, rtksw_mac_t macMsk, rtksw_vlan_t *pSvid)
{
    rtksw_api_ret_t retVal;
    rtksw_uint32 i;
    rtksw_uint32 l2add,l2Mask;
    rtl8367c_svlan_memconf_t svlanMemConf;
    rtl8367c_svlan_mc2s_t svlanMC2SConf;

    /* Check initialization state */
    RTKSW_CHK_INIT_STATE(unit);

    if(NULL == pSvid)
        return RT_ERR_NULL_POINTER;

    if (mac.octet[0]!= 1&&mac.octet[1]!=0)
        return RT_ERR_INPUT;

    l2add = (mac.octet[2] << 24) | (mac.octet[3] << 16) | (mac.octet[4] << 8) | mac.octet[5];
    l2Mask = (macMsk.octet[2] << 24) | (macMsk.octet[3] << 16) | (macMsk.octet[4] << 8) | macMsk.octet[5];

    for (i = 0; i <= RTL8367C_MC2SIDXMAX; i++)
    {
        if ((retVal = rtl8367c_getAsicSvlanMC2SConf(unit, i, &svlanMC2SConf)) != RT_ERR_OK)
            return retVal;

        if (TRUE == svlanMC2SConf.valid)
        {
            if (svlanMC2SConf.format == SVLAN_MC2S_MODE_MAC &&
                svlanMC2SConf.sdata==l2add&&
                svlanMC2SConf.smask==l2Mask)
            {
                if ((retVal = rtl8367c_getAsicSvlanMemberConfiguration(unit, svlanMC2SConf.svidx, &svlanMemConf)) != RT_ERR_OK)
                    return retVal;
                *pSvid = svlanMemConf.vs_svid;

                return RT_ERR_OK;
            }
        }
    }

    return RT_ERR_OUT_OF_RANGE;
}

/* Function Name:
 *      dal_rtl8367c_svlan_sp2c_add
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
rtksw_api_ret_t dal_rtl8367c_svlan_sp2c_add(rtksw_uint32 unit, rtksw_vlan_t svid, rtksw_port_t dst_port, rtksw_vlan_t cvid)
{
    rtksw_api_ret_t retVal, i;
    rtksw_uint32 empty_idx, svidx;
    rtl8367c_svlan_memconf_t svlanMemConf;
    rtl8367c_svlan_s2c_t svlanSP2CConf;
    rtksw_port_t port;

    /* Check initialization state */
    RTKSW_CHK_INIT_STATE(unit);

    if (svid > RTL8367C_VIDMAX)
        return RT_ERR_SVLAN_VID;

    if (cvid > RTL8367C_VIDMAX)
        return RT_ERR_VLAN_VID;

    /* Check port Valid */
    RTKSW_CHK_PORT_VALID(unit, dst_port);
    port = rtksw_switch_port_L2P_get(unit, dst_port);

    svidx = 0xFFFF;

    for (i = 0; i < RTL8367C_SVIDXNO; i++)
    {
        if ((retVal = rtl8367c_getAsicSvlanMemberConfiguration(unit, i, &svlanMemConf)) != RT_ERR_OK)
            return retVal;

        if (svid == svlanMemConf.vs_svid)
        {
            svidx = i;
            break;
        }
    }

    if (0xFFFF == svidx)
        return RT_ERR_SVLAN_ENTRY_NOT_FOUND;

    empty_idx = 0xFFFF;

    for (i=RTL8367C_SP2CMAX; i >=0 ; i--)
    {
        if ((retVal = rtl8367c_getAsicSvlanSP2CConf(unit, i, &svlanSP2CConf)) != RT_ERR_OK)
            return retVal;

        if ( (svlanSP2CConf.svidx == svidx) && (svlanSP2CConf.dstport == port) && (svlanSP2CConf.valid == 1))
        {
            empty_idx = i;
            break;
        }
        else if (svlanSP2CConf.valid == 0)
        {
            empty_idx = i;
        }
    }

    if (empty_idx!=0xFFFF)
    {
        svlanSP2CConf.valid     = 1;
        svlanSP2CConf.vid       = cvid;
        svlanSP2CConf.svidx     = svidx;
        svlanSP2CConf.dstport   = port;

        if ((retVal = rtl8367c_setAsicSvlanSP2CConf(unit, empty_idx, &svlanSP2CConf)) != RT_ERR_OK)
            return retVal;
        return RT_ERR_OK;
    }

    return RT_ERR_OUT_OF_RANGE;

}

/* Function Name:
 *      dal_rtl8367c_svlan_sp2c_get
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
rtksw_api_ret_t dal_rtl8367c_svlan_sp2c_get(rtksw_uint32 unit, rtksw_vlan_t svid, rtksw_port_t dst_port, rtksw_vlan_t *pCvid)
{
    rtksw_api_ret_t retVal;
    rtksw_uint32 i, svidx;
    rtl8367c_svlan_memconf_t svlanMemConf;
    rtl8367c_svlan_s2c_t svlanSP2CConf;

    /* Check initialization state */
    RTKSW_CHK_INIT_STATE(unit);

    if(NULL == pCvid)
        return RT_ERR_NULL_POINTER;

    if (svid > RTL8367C_VIDMAX)
        return RT_ERR_SVLAN_VID;

    /* Check port Valid */
    RTKSW_CHK_PORT_VALID(unit, dst_port);
    dst_port = rtksw_switch_port_L2P_get(unit, dst_port);

    svidx = 0xFFFF;

    for (i = 0; i < RTL8367C_SVIDXNO; i++)
    {
        if ((retVal = rtl8367c_getAsicSvlanMemberConfiguration(unit, i, &svlanMemConf)) != RT_ERR_OK)
            return retVal;

        if (svid == svlanMemConf.vs_svid)
        {
            svidx = i;
            break;
        }
    }

    if (0xFFFF == svidx)
        return RT_ERR_SVLAN_ENTRY_NOT_FOUND;

    for (i = 0; i <= RTL8367C_SP2CMAX; i++)
    {
        if ((retVal = rtl8367c_getAsicSvlanSP2CConf(unit, i, &svlanSP2CConf)) != RT_ERR_OK)
            return retVal;

        if ( (svlanSP2CConf.svidx == svidx) && (svlanSP2CConf.dstport == dst_port) && (svlanSP2CConf.valid == 1) )
        {
            *pCvid = svlanSP2CConf.vid;
            return RT_ERR_OK;
        }
    }

    return RT_ERR_OUT_OF_RANGE;
}

/* Function Name:
 *      dal_rtl8367c_svlan_sp2c_del
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
rtksw_api_ret_t dal_rtl8367c_svlan_sp2c_del(rtksw_uint32 unit, rtksw_vlan_t svid, rtksw_port_t dst_port)
{
    rtksw_api_ret_t retVal;
    rtksw_uint32 i, svidx;
    rtl8367c_svlan_memconf_t svlanMemConf;
    rtl8367c_svlan_s2c_t svlanSP2CConf;

    /* Check initialization state */
    RTKSW_CHK_INIT_STATE(unit);

    if (svid > RTL8367C_VIDMAX)
        return RT_ERR_SVLAN_VID;

    /* Check port Valid */
    RTKSW_CHK_PORT_VALID(unit, dst_port);
    dst_port = rtksw_switch_port_L2P_get(unit, dst_port);

    svidx = 0xFFFF;

    for (i = 0; i < RTL8367C_SVIDXNO; i++)
    {
        if ((retVal = rtl8367c_getAsicSvlanMemberConfiguration(unit, i, &svlanMemConf)) != RT_ERR_OK)
            return retVal;

        if (svid == svlanMemConf.vs_svid)
        {
            svidx = i;
            break;
        }
    }

    if (0xFFFF == svidx)
        return RT_ERR_SVLAN_ENTRY_NOT_FOUND;

    for (i = 0; i <= RTL8367C_SP2CMAX; i++)
    {
        if ((retVal = rtl8367c_getAsicSvlanSP2CConf(unit, i, &svlanSP2CConf)) != RT_ERR_OK)
            return retVal;

        if ( (svlanSP2CConf.svidx == svidx) && (svlanSP2CConf.dstport == dst_port) && (svlanSP2CConf.valid == 1) )
        {
            svlanSP2CConf.valid     = 0;
            svlanSP2CConf.vid       = 0;
            svlanSP2CConf.svidx     = 0;
            svlanSP2CConf.dstport   = 0;

            if ((retVal = rtl8367c_setAsicSvlanSP2CConf(unit, i, &svlanSP2CConf)) != RT_ERR_OK)
                return retVal;
            return RT_ERR_OK;
        }

    }

    return RT_ERR_OUT_OF_RANGE;
}

/* Function Name:
 *      dal_rtl8367c_svlan_lookupType_set
 * Description:
 *      Set lookup type of SVLAN
 * Input:
 *      unit        - Unit ID
 *      type        - lookup type
 * Output:
 *      None
 * Return:
 *      RT_ERR_OK
 *      RT_ERR_FAILED
 * Note:
 *      none
 */
rtksw_api_ret_t dal_rtl8367c_svlan_lookupType_set(rtksw_uint32 unit, rtksw_svlan_lookupType_t type)
{
    rtksw_api_ret_t   retVal;

    /* Check initialization state */
    RTKSW_CHK_INIT_STATE(unit);

    if (type >= SVLAN_LOOKUP_END)
        return RT_ERR_CHIP_NOT_SUPPORTED;


    svlan_lookupType = type;

    retVal = rtl8367c_setAsicSvlanLookupType(unit, (rtksw_uint32)type);

    return retVal;
}

/* Function Name:
 *      dal_rtl8367c_svlan_lookupType_get
 * Description:
 *      Get lookup type of SVLAN
 * Input:
 *      unit        - Unit ID
 *      pType       - lookup type
 * Output:
 *      None
 * Return:
 *      RT_ERR_OK
 *      RT_ERR_FAILED
 * Note:
 *      none
 */
rtksw_api_ret_t dal_rtl8367c_svlan_lookupType_get(rtksw_uint32 unit, rtksw_svlan_lookupType_t *pType)
{
    rtksw_api_ret_t   retVal;

    /* Check initialization state */
    RTKSW_CHK_INIT_STATE(unit);

    if(NULL == pType)
        return RT_ERR_NULL_POINTER;

    retVal = rtl8367c_getAsicSvlanLookupType(unit, pType);

    svlan_lookupType = *pType;

    return retVal;
}

/* Function Name:
 *      dal_rtl8367c_svlan_trapPri_set
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
rtksw_api_ret_t dal_rtl8367c_svlan_trapPri_set(rtksw_uint32 unit, rtksw_pri_t priority)
{
    rtksw_api_ret_t   retVal;

    RTKSW_CHK_INIT_STATE(unit);

    if(priority > RTL8367C_PRIMAX)
        return RT_ERR_OUT_OF_RANGE;

    retVal = rtl8367c_setAsicSvlanTrapPriority(unit, priority);

    return retVal;
}

/* Function Name:
 *      dal_rtl8367c_svlan_trapPri_get
 * Description:
 *      Get svlan trap priority
 * Input:
 *      unit        - Unit ID
 *      None
 * Output:
 *      pPriority - priority for trap packets
 * Return:
 *      RT_ERR_OK
 *      RT_ERR_FAILED
 *      RT_ERR_NULL_POINTER - input parameter may be null pointer
 * Note:
 *      None
 */
rtksw_api_ret_t dal_rtl8367c_svlan_trapPri_get(rtksw_uint32 unit, rtksw_pri_t *pPriority)
{
    rtksw_api_ret_t   retVal;

    RTKSW_CHK_INIT_STATE(unit);

    if(NULL == pPriority)
        return RT_ERR_NULL_POINTER;

    retVal = rtl8367c_getAsicSvlanTrapPriority(unit, pPriority);

    return retVal;
}   /* end of rtksw_svlan_trapPri_get */


/*Don't lock mutex in following API*/


/* Function Name:
 *      dal_rtl8367c_svlan_checkAndCreateMbr
 * Description:
 *      Check and create Member configuration and return index
 * Input:
 *      unit        - Unit ID
 *      vid         - VLAN id.
 * Output:
 *      pIndex  - Member configuration index
 * Return:
 *      RT_ERR_OK           - OK
 *      RT_ERR_FAILED       - Failed
 *      RT_ERR_SMI          - SMI access error
 *      RT_ERR_VLAN_VID     - Invalid VLAN ID.
 *      RT_ERR_TBL_FULL     - Member Configuration table full
 * Note:
 *
 */
rtksw_api_ret_t dal_rtl8367c_svlan_checkAndCreateMbr(rtksw_uint32 unit, rtksw_vlan_t vid, rtksw_uint32 *pIndex)
{
    rtksw_api_ret_t retVal;
    rtksw_uint32 svidx;
    rtksw_uint32 empty_idx = 0xFFFF;
    rtl8367c_svlan_memconf_t svlan_cfg;

    /* Check initialization state */
    RTKSW_CHK_INIT_STATE(unit);

    /* vid must be 0~4095 */
    if (vid > RTL8367C_VIDMAX)
        return RT_ERR_VLAN_VID;

    /* Null pointer check */
    if(NULL == pIndex)
        return RT_ERR_NULL_POINTER;

    /* Search exist entry */
    for (svidx = 0; svidx <= RTL8367C_SVIDXMAX; svidx++)
    {
        if(svlan_mbrCfgUsage[svidx] == TRUE)
        {
            if(svlan_mbrCfgVid[svidx] == vid)
            {
                /* Found! return index */
                *pIndex = svidx;
                return RT_ERR_OK;
            }
        }
        else if(empty_idx == 0xFFFF)
        {
            empty_idx = svidx;
        }

    }

    if(empty_idx == 0xFFFF)
    {
        /* No empty index */
        return RT_ERR_TBL_FULL;
    }

    svlan_mbrCfgUsage[empty_idx] = TRUE;
    svlan_mbrCfgVid[empty_idx] = vid;

    osal_memset(&svlan_cfg, 0, sizeof(rtl8367c_svlan_memconf_t));

    svlan_cfg.vs_svid = vid;
    /*for create check*/
    if(vid == 0)
    {
        svlan_cfg.vs_efid = 1;
    }

    if((retVal = rtl8367c_setAsicSvlanMemberConfiguration(unit, empty_idx, &svlan_cfg)) != RT_ERR_OK)
        return retVal;

    *pIndex = empty_idx;
    return RT_ERR_OK;
}

