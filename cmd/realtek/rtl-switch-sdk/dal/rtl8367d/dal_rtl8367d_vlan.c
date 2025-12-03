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
 * Feature : Here is a list of all functions and variables in VLAN module.
 *
 */

#include "../../rtk_switch.h"
#include "../../rtk_error.h"
#include "dal_rtl8367d_vlan.h"
#include "rtl8367d_asicdrv.h"

#include "../dal_mgmts.h"
#include "../../osal/lib.h"

#if defined(CONFIG_RTL8367D_ASICDRV_TEST)
dal_rtl8367d_user_vlan4kentry Rtl8367dVirtualVlanTable[RTL8367D_VIDMAX + 1];
#endif

static void _dal_rtl8367d_Vlan4kStUser2Smi(dal_rtl8367d_user_vlan4kentry *pUserVlan4kEntry, rtksw_uint16 *pSmiVlan4kEntry)
{
    pSmiVlan4kEntry[0] |= (pUserVlan4kEntry->mbr & 0x00FF);
    pSmiVlan4kEntry[0] |= (pUserVlan4kEntry->untag & 0x00FF) << 8;

    pSmiVlan4kEntry[1] |= (pUserVlan4kEntry->fid_msti & 0x0003);
    pSmiVlan4kEntry[1] |= (pUserVlan4kEntry->svlan_chk_ivl_svl & 0x0001) << 2;
    pSmiVlan4kEntry[1] |= (pUserVlan4kEntry->ivl_svl & 0x0001) << 3;
}


static void _dal_rtl8367d_Vlan4kStSmi2User(rtksw_uint16 *pSmiVlan4kEntry, dal_rtl8367d_user_vlan4kentry *pUserVlan4kEntry)
{
    pUserVlan4kEntry->mbr               = (pSmiVlan4kEntry[0] & 0x00FF);
    pUserVlan4kEntry->untag             = (pSmiVlan4kEntry[0] & 0xFF00) >> 8;

    pUserVlan4kEntry->fid_msti          = (pSmiVlan4kEntry[1] & 0x0003);
    pUserVlan4kEntry->svlan_chk_ivl_svl = (pSmiVlan4kEntry[1] & 0x0004) >> 2;
    pUserVlan4kEntry->ivl_svl           = (pSmiVlan4kEntry[1] & 0x0008) >> 3;
}

ret_t _dal_rtl8367d_setAsicVlan4kEntry(rtksw_uint32 unit, dal_rtl8367d_user_vlan4kentry *pVlan4kEntry )
{
    rtksw_uint16              vlan_4k_entry[RTL8367D_VLAN_4KTABLE_LEN];
    rtksw_uint32              page_idx;
    rtksw_uint16              *tableAddr;
    ret_t                   retVal;
    rtksw_uint32              regData;

    if(pVlan4kEntry->vid > RTL8367D_VIDMAX)
        return RT_ERR_VLAN_VID;

    if(pVlan4kEntry->mbr > RTL8367D_PORTMASK)
        return RT_ERR_PORT_MASK;

    if(pVlan4kEntry->untag > RTL8367D_PORTMASK)
        return RT_ERR_PORT_MASK;

    if(pVlan4kEntry->fid_msti > RTL8367D_FIDMAX)
        return RT_ERR_L2_FID;

    if(pVlan4kEntry->ivl_svl> RTKSW_ENABLE_END)
        return RT_ERR_INPUT;

    if(pVlan4kEntry->svlan_chk_ivl_svl> RTKSW_ENABLE_END)
        return RT_ERR_INPUT;

    osal_memset(vlan_4k_entry, 0x00, sizeof(rtksw_uint16) * RTL8367D_VLAN_4KTABLE_LEN);
    _dal_rtl8367d_Vlan4kStUser2Smi(pVlan4kEntry, vlan_4k_entry);
    //PRINT("\n %s %d\n",__FUNCTION__,__LINE__);

    /* Prepare Data */
    tableAddr = vlan_4k_entry;
    for(page_idx = 0; page_idx < RTL8367D_VLAN_4KTABLE_LEN; page_idx++)
    {
        regData = *tableAddr;
        retVal = rtl8367d_setAsicReg(unit, RTL8367D_REG_TABLE_WRITE_DATA0 + page_idx, regData);
        if(retVal != RT_ERR_OK)
            return retVal;

        tableAddr++;
    }

    /* Write Address (VLAN_ID) */
    regData = pVlan4kEntry->vid;
    retVal = rtl8367d_setAsicReg(unit, RTL8367D_REG_TABLE_ACCESS_ADDR, regData);
    if(retVal != RT_ERR_OK)
        return retVal;

    /* Write Command */
    retVal = rtl8367d_setAsicRegBits(unit, RTL8367D_REG_TABLE_ACCESS_CTRL, RTL8367D_TABLE_TYPE_MASK | RTL8367D_COMMAND_TYPE_MASK, RTL8367D_TABLE_ACCESS_REG_DATA(RTL8367D_TB_OP_WRITE,RTL8367D_TB_TARGET_CVLAN));
    if(retVal != RT_ERR_OK)
        return retVal;

#if defined(CONFIG_RTL8367D_ASICDRV_TEST)
    osal_memcpy(&Rtl8367dVirtualVlanTable[pVlan4kEntry->vid], pVlan4kEntry, sizeof(dal_rtl8367d_user_vlan4kentry));
#endif

    return RT_ERR_OK;
}


ret_t _dal_rtl8367d_getAsicVlan4kEntry(rtksw_uint32 unit, dal_rtl8367d_user_vlan4kentry *pVlan4kEntry )
{
    rtksw_uint16                  vlan_4k_entry[RTL8367D_VLAN_4KTABLE_LEN];
    rtksw_uint32                  page_idx;
    rtksw_uint16                  *tableAddr;
    ret_t                       retVal;
    rtksw_uint32                  regData;
    rtksw_uint32                  busyCounter;

    if(pVlan4kEntry->vid > RTL8367D_VIDMAX)
        return RT_ERR_VLAN_VID;

    /* Polling status */
    busyCounter = RTL8367D_VLAN_BUSY_CHECK_NO;
    while(busyCounter)
    {
        retVal = rtl8367d_getAsicRegBit(unit, RTL8367D_REG_TABLE_LUT_ADDR, RTL8367D_TABLE_LUT_ADDR_BUSY_FLAG_OFFSET,&regData);
        if(retVal != RT_ERR_OK)
            return retVal;

        if(regData == 0)
            break;

        busyCounter --;
        if(busyCounter == 0)
            return RT_ERR_BUSYWAIT_TIMEOUT;
    }

    /* Write Address (VLAN_ID) */
    regData = pVlan4kEntry->vid;
    retVal = rtl8367d_setAsicReg(unit, RTL8367D_REG_TABLE_ACCESS_ADDR, regData);
    if(retVal != RT_ERR_OK)
        return retVal;

    /* Read Command */
    retVal = rtl8367d_setAsicRegBits(unit, RTL8367D_REG_TABLE_ACCESS_CTRL, RTL8367D_TABLE_TYPE_MASK | RTL8367D_COMMAND_TYPE_MASK, RTL8367D_TABLE_ACCESS_REG_DATA(RTL8367D_TB_OP_READ,RTL8367D_TB_TARGET_CVLAN));
    if(retVal != RT_ERR_OK)
        return retVal;

    /* Polling status */
    busyCounter = RTL8367D_VLAN_BUSY_CHECK_NO;
    while(busyCounter)
    {
        retVal = rtl8367d_getAsicRegBit(unit, RTL8367D_REG_TABLE_LUT_ADDR, RTL8367D_TABLE_LUT_ADDR_BUSY_FLAG_OFFSET,&regData);
        if(retVal != RT_ERR_OK)
            return retVal;

        if(regData == 0)
            break;

        busyCounter --;
        if(busyCounter == 0)
            return RT_ERR_BUSYWAIT_TIMEOUT;
    }

    /* Read VLAN data from register */
    tableAddr = vlan_4k_entry;
    for(page_idx = 0; page_idx < RTL8367D_VLAN_4KTABLE_LEN; page_idx++)
    {
        retVal = rtl8367d_getAsicReg(unit, RTL8367D_REG_TABLE_READ_DATA0 + page_idx, &regData);
        if(retVal != RT_ERR_OK)
            return retVal;

        *tableAddr = regData;
        tableAddr++;
    }

    _dal_rtl8367d_Vlan4kStSmi2User(vlan_4k_entry, pVlan4kEntry);

#if defined(CONFIG_RTL8367D_ASICDRV_TEST)
    osal_memcpy(pVlan4kEntry, &Rtl8367dVirtualVlanTable[pVlan4kEntry->vid], sizeof(dal_rtl8367d_user_vlan4kentry));
#endif

    return RT_ERR_OK;
}


/* Function Name:
 *      dal_rtl8367d_vlan_init
 * Description:
 *      Initialize VLAN.
 * Input:
 *      unit        - Unit ID
  * Output:
 *      None
 * Return:
 *      RT_ERR_OK           - OK
 *      RT_ERR_FAILED       - Failed
 *      RT_ERR_SMI          - SMI access error
 * Note:
 *      VLAN is disabled by default. User has to call this API to enable VLAN before
 *      using it. And It will set a default VLAN(vid 1) including all ports and set
 *      all ports PVID to the default VLAN.
 */
rtksw_api_ret_t dal_rtl8367d_vlan_init(rtksw_uint32 unit)
{
    rtksw_api_ret_t retVal;
    rtksw_uint32 i;
    dal_rtl8367d_user_vlan4kentry vlan4K;

    /* Check initialization state */
    RTKSW_CHK_INIT_STATE(unit);

    /* Set a default VLAN with vid 1 to 4K table for all ports */
    osal_memset(&vlan4K, 0, sizeof(dal_rtl8367d_user_vlan4kentry));
    vlan4K.vid = 1;
    vlan4K.mbr = RTKSW_PHY_PORTMASK_ALL;
    vlan4K.untag = RTKSW_PHY_PORTMASK_ALL;
    vlan4K.fid_msti = 0;
    if ((retVal = _dal_rtl8367d_setAsicVlan4kEntry(unit, &vlan4K)) != RT_ERR_OK)
        return retVal;

    /* Set all ports PVID to default VLAN and tag-mode to original */
    RTKSW_SCAN_ALL_LOG_PORT(unit, i)
    {
        if ((retVal = dal_rtl8367d_vlan_portPvid_set(unit, i, 1, 0)) != RT_ERR_OK)
            return retVal;
        if ((retVal = dal_rtl8367d_vlan_tagMode_set(unit, i, RTKSW_VLAN_TAG_MODE_ORIGINAL)) != RT_ERR_OK)
            return retVal;
    }

    /* Enable Ingress filter */
    RTKSW_SCAN_ALL_LOG_PORT(unit, i)
    {
        if ((retVal = dal_rtl8367d_vlan_portIgrFilterEnable_set(unit, i, RTKSW_ENABLED)) != RT_ERR_OK)
            return retVal;
    }

    /* enable VLAN */
    if ((retVal = dal_rtl8367d_vlan_egrFilterEnable_set(unit, RTKSW_ENABLED)) != RT_ERR_OK)
        return retVal;

    return RT_ERR_OK;
}

/* Function Name:
 *      dal_rtl8367d_vlan_set
 * Description:
 *      Set a VLAN entry.
 * Input:
 *      unit        - Unit ID
 *      vid         - VLAN ID to configure.
 *      pVlanCfg    - VLAN Configuration
 * Output:
 *      None
 * Return:
 *      RT_ERR_OK                   - OK
 *      RT_ERR_FAILED               - Failed
 *      RT_ERR_SMI                  - SMI access error
 *      RT_ERR_INPUT                - Invalid input parameters.
 *      RT_ERR_L2_FID               - Invalid FID.
 *      RT_ERR_VLAN_PORT_MBR_EXIST  - Invalid member port mask.
 *      RT_ERR_VLAN_VID             - Invalid VID parameter.
 * Note:
 *
 */
rtksw_api_ret_t dal_rtl8367d_vlan_set(rtksw_uint32 unit, rtksw_vlan_t vid, rtksw_vlan_cfg_t *pVlanCfg)
{
    rtksw_api_ret_t retVal;
    rtksw_uint32 phyMbrPmask;
    rtksw_uint32 phyUntagPmask;
    dal_rtl8367d_user_vlan4kentry vlan4K;

    /* Check initialization state */
    RTKSW_CHK_INIT_STATE(unit);

    /* vid must be 0~8191 */
    if (vid > RTL8367D_VIDMAX)
        return RT_ERR_VLAN_VID;

    /* Null pointer check */
    if(NULL == pVlanCfg)
        return RT_ERR_NULL_POINTER;

    /* Check port mask valid */
    RTKSW_CHK_PORTMASK_VALID(unit, &(pVlanCfg->mbr));

    /* Check untag port mask valid */
    RTKSW_CHK_PORTMASK_VALID(unit, &(pVlanCfg->untag));

    /* IVL_EN */
    if(pVlanCfg->ivl_en >= RTKSW_ENABLE_END)
        return RT_ERR_ENABLE;

    /* fid must be 0~3 */
    if(pVlanCfg->fid_msti > RTL8367D_FIDMAX)
        return RT_ERR_L2_FID;

    /* Policing,  Meter ID ,  VLAN based priority ar not supported in RTL8367D*/
    if((pVlanCfg->envlanpol != 0)||(pVlanCfg->meteridx != 0) || (pVlanCfg->vbpen != 0) ||(pVlanCfg->vbpri != 0))
        return RT_ERR_INPUT;

    /* Get physical port mask */
    if(rtksw_switch_portmask_L2P_get(unit, &(pVlanCfg->mbr), &phyMbrPmask) != RT_ERR_OK)
        return RT_ERR_FAILED;

    if(rtksw_switch_portmask_L2P_get(unit, &(pVlanCfg->untag), &phyUntagPmask) != RT_ERR_OK)
        return RT_ERR_FAILED;

    /* update 4K table */
    osal_memset(&vlan4K, 0, sizeof(dal_rtl8367d_user_vlan4kentry));
    vlan4K.vid = vid;

    vlan4K.mbr    = (phyMbrPmask & 0xFFFF);
    vlan4K.untag  = (phyUntagPmask & 0xFFFF);

    vlan4K.ivl_svl      = pVlanCfg->ivl_en;
    vlan4K.fid_msti     = pVlanCfg->fid_msti;

    if ((retVal = _dal_rtl8367d_setAsicVlan4kEntry(unit, &vlan4K)) != RT_ERR_OK)
        return retVal;

    return RT_ERR_OK;
}

/* Function Name:
 *      dal_rtl8367d_vlan_get
 * Description:
 *      Get a VLAN entry.
 * Input:
 *      unit        - Unit ID
 *      vid         - VLAN ID to configure.
 * Output:
 *      pVlanCfg - VLAN Configuration
 * Return:
 *      RT_ERR_OK           - OK
 *      RT_ERR_FAILED       - Failed
 *      RT_ERR_SMI          - SMI access error
 *      RT_ERR_INPUT        - Invalid input parameters.
 *      RT_ERR_VLAN_VID     - Invalid VID parameter.
 * Note:
 *
 */
rtksw_api_ret_t dal_rtl8367d_vlan_get(rtksw_uint32 unit, rtksw_vlan_t vid, rtksw_vlan_cfg_t *pVlanCfg)
{
    rtksw_api_ret_t retVal;
    rtksw_uint32 phyMbrPmask;
    rtksw_uint32 phyUntagPmask;
    dal_rtl8367d_user_vlan4kentry vlan4K;

    /* Check initialization state */
    RTKSW_CHK_INIT_STATE(unit);

    /* vid must be 0~8191 */
    if (vid > RTL8367D_VIDMAX)
        return RT_ERR_VLAN_VID;

    /* Null pointer check */
    if(NULL == pVlanCfg)
        return RT_ERR_NULL_POINTER;

    vlan4K.vid = vid;

    if ((retVal = _dal_rtl8367d_getAsicVlan4kEntry(unit, &vlan4K)) != RT_ERR_OK)
        return retVal;

    phyMbrPmask   = vlan4K.mbr;
    phyUntagPmask = vlan4K.untag;
    if(rtksw_switch_portmask_P2L_get(unit, phyMbrPmask, &(pVlanCfg->mbr)) != RT_ERR_OK)
        return RT_ERR_FAILED;

    if(rtksw_switch_portmask_P2L_get(unit, phyUntagPmask, &(pVlanCfg->untag)) != RT_ERR_OK)
        return RT_ERR_FAILED;

    pVlanCfg->ivl_en    = vlan4K.ivl_svl;
    pVlanCfg->fid_msti  = vlan4K.fid_msti;

    return RT_ERR_OK;
}

/* Function Name:
 *      dal_rtl8367d_vlan_egrFilterEnable_set
 * Description:
 *      Set VLAN egress filter.
 * Input:
 *      unit        - Unit ID
 *      egrFilter   - Egress filtering
 * Output:
 *      None.
 * Return:
 *      RT_ERR_OK           - OK
 *      RT_ERR_FAILED       - Failed
 *      RT_ERR_SMI          - SMI access error
 *      RT_ERR_ENABLE       - Invalid input parameters.
 * Note:
 *
 */
rtksw_api_ret_t dal_rtl8367d_vlan_egrFilterEnable_set(rtksw_uint32 unit, rtksw_enable_t egrFilter)
{
    rtksw_api_ret_t retVal;

    /* Check initialization state */
    RTKSW_CHK_INIT_STATE(unit);

    if(egrFilter >= RTKSW_ENABLE_END)
        return RT_ERR_ENABLE;

    /* enable VLAN */
    if ((retVal = rtl8367d_setAsicRegBit(unit, RTL8367D_REG_VLAN_CTRL, RTL8367D_VLAN_CTRL_OFFSET, egrFilter)) != RT_ERR_OK)
        return retVal;

    return RT_ERR_OK;
}

/* Function Name:
 *      dal_rtl8367d_vlan_egrFilterEnable_get
 * Description:
 *      Get VLAN egress filter.
 * Input:
 *      unit        - Unit ID
 *      pEgrFilter  - Egress filtering
 * Output:
 *      None.
 * Return:
 *      RT_ERR_OK           - OK
 *      RT_ERR_FAILED       - Failed
 *      RT_ERR_SMI          - SMI access error
 *      RT_ERR_NULL_POINTER - NULL Pointer.
 * Note:
 *
 */
rtksw_api_ret_t dal_rtl8367d_vlan_egrFilterEnable_get(rtksw_uint32 unit, rtksw_enable_t *pEgrFilter)
{
    rtksw_api_ret_t retVal;
    rtksw_uint32 state;

    /* Check initialization state */
    RTKSW_CHK_INIT_STATE(unit);

    if(NULL == pEgrFilter)
        return RT_ERR_NULL_POINTER;

    /* enable VLAN */
    if ((retVal = rtl8367d_getAsicRegBit(unit, RTL8367D_REG_VLAN_CTRL, RTL8367D_VLAN_CTRL_OFFSET, &state)) != RT_ERR_OK)
        return retVal;

    *pEgrFilter = (rtksw_enable_t)state;
    return RT_ERR_OK;
}

/* Function Name:
 *     dal_rtl8367d_vlan_portPvid_set
 * Description:
 *      Set port to specified VLAN ID(PVID).
 * Input:
 *      unit        - Unit ID
 *      port        - Port id.
 *      pvid        - Specified VLAN ID.
 *      priority    - 802.1p priority for the PVID.
 * Output:
 *      None
 * Return:
 *      RT_ERR_OK                   - OK
 *      RT_ERR_FAILED               - Failed
 *      RT_ERR_SMI                  - SMI access error
 *      RT_ERR_PORT_ID              - Invalid port number.
 *      RT_ERR_VLAN_PRIORITY        - Invalid priority.
 *      RT_ERR_VLAN_ENTRY_NOT_FOUND - VLAN entry not found.
 *      RT_ERR_VLAN_VID             - Invalid VID parameter.
 * Note:
 *       The API is used for Port-based VLAN. The untagged frame received from the
 *       port will be classified to the specified VLAN and assigned to the specified priority.
 */
rtksw_api_ret_t dal_rtl8367d_vlan_portPvid_set(rtksw_uint32 unit, rtksw_port_t port, rtksw_vlan_t pvid, rtksw_pri_t priority)
{
    rtksw_api_ret_t retVal;

    /* Check initialization state */
    RTKSW_CHK_INIT_STATE(unit);

    /* Check Port Valid */
    RTKSW_CHK_PORT_VALID(unit, port);

    /* vid must be 0~8191 */
    if (pvid > RTL8367D_VIDMAX)
        return RT_ERR_VLAN_VID;

    /* priority is not supported in RTL8367D */
    if (priority > 0)
        return RT_ERR_INPUT;

    retVal = rtl8367d_setAsicRegBits(unit, RTL8367D_REG_VLAN_PVID_CTRL0 + rtksw_switch_port_L2P_get(unit, port), RTL8367D_VLAN_PVID_CTRL0_MASK, pvid);
    if(retVal != RT_ERR_OK)
        return retVal;

    return RT_ERR_OK;
}

/* Function Name:
 *      dal_rtl8367d_vlan_portPvid_get
 * Description:
 *      Get VLAN ID(PVID) on specified port.
 * Input:
 *      unit        - Unit ID
 *      port        - Port id.
 * Output:
 *      pPvid - Specified VLAN ID.
 *      pPriority - 802.1p priority for the PVID.
 * Return:
 *      RT_ERR_OK           - OK
 *      RT_ERR_FAILED       - Failed
 *      RT_ERR_SMI          - SMI access error
 *      RT_ERR_INPUT        - Invalid input parameters.
 *      RT_ERR_PORT_ID      - Invalid port number.
 * Note:
 *     The API can get the PVID and 802.1p priority for the PVID of Port-based VLAN.
 */
rtksw_api_ret_t dal_rtl8367d_vlan_portPvid_get(rtksw_uint32 unit, rtksw_port_t port, rtksw_vlan_t *pPvid, rtksw_pri_t *pPriority)
{
    rtksw_api_ret_t retVal;

    /* Check initialization state */
    RTKSW_CHK_INIT_STATE(unit);

    /* Check Port Valid */
    RTKSW_CHK_PORT_VALID(unit, port);

    if(NULL == pPvid)
        return RT_ERR_NULL_POINTER;

    if(NULL == pPriority)
        return RT_ERR_NULL_POINTER;

    *pPriority = 0;

    retVal = rtl8367d_getAsicRegBits(unit, RTL8367D_REG_VLAN_PVID_CTRL0 + rtksw_switch_port_L2P_get(unit, port), RTL8367D_VLAN_PVID_CTRL0_MASK, pPvid);
    if(retVal != RT_ERR_OK)
        return retVal;

    return RT_ERR_OK;
}

/* Function Name:
 *      dal_rtl8367d_vlan_portIgrFilterEnable_set
 * Description:
 *      Set VLAN ingress for each port.
 * Input:
 *      unit        - Unit ID
 *      port        - Port id.
 *      igr_filter  - VLAN ingress function enable status.
 * Output:
 *      None
 * Return:
 *      RT_ERR_OK           - OK
 *      RT_ERR_FAILED       - Failed
 *      RT_ERR_SMI          - SMI access error
 *      RT_ERR_PORT_ID      - Invalid port number
 *      RT_ERR_ENABLE       - Invalid enable input
 * Note:
 *      The status of vlan ingress filter is as following:
 *      - RTKSW_DISABLED
 *      - RTKSW_ENABLED
 *      While VLAN function is enabled, ASIC will decide VLAN ID for each received frame and get belonged member
 *      ports from VLAN table. If received port is not belonged to VLAN member ports, ASIC will drop received frame if VLAN ingress function is enabled.
 */
rtksw_api_ret_t dal_rtl8367d_vlan_portIgrFilterEnable_set(rtksw_uint32 unit, rtksw_port_t port, rtksw_enable_t igr_filter)
{
    rtksw_api_ret_t retVal;

    /* Check initialization state */
    RTKSW_CHK_INIT_STATE(unit);

    /* Check Port Valid */
    RTKSW_CHK_PORT_VALID(unit, port);

    if (igr_filter >= RTKSW_ENABLE_END)
        return RT_ERR_ENABLE;

    if ((retVal = rtl8367d_setAsicRegBit(unit, RTL8367D_REG_VLAN_INGRESS, rtksw_switch_port_L2P_get(unit, port), igr_filter)) != RT_ERR_OK)
        return retVal;

    return RT_ERR_OK;
}

/* Function Name:
 *      dal_rtl8367d_vlan_portIgrFilterEnable_get
 * Description:
 *      Get VLAN Ingress Filter
 * Input:
 *      unit        - Unit ID
 *      port        - Port id.
 * Output:
 *      pIgr_filter - VLAN ingress function enable status.
 * Return:
 *      RT_ERR_OK           - OK
 *      RT_ERR_FAILED       - Failed
 *      RT_ERR_SMI          - SMI access error
 *      RT_ERR_INPUT        - Invalid input parameters.
 *      RT_ERR_PORT_ID      - Invalid port number.
 * Note:
 *     The API can Get the VLAN ingress filter status.
 *     The status of vlan ingress filter is as following:
 *     - RTKSW_DISABLED
 *     - RTKSW_ENABLED
 */
rtksw_api_ret_t dal_rtl8367d_vlan_portIgrFilterEnable_get(rtksw_uint32 unit, rtksw_port_t port, rtksw_enable_t *pIgr_filter)
{
    rtksw_api_ret_t retVal;

    /* Check initialization state */
    RTKSW_CHK_INIT_STATE(unit);

    /* Check Port Valid */
    RTKSW_CHK_PORT_VALID(unit, port);

    if(NULL == pIgr_filter)
        return RT_ERR_NULL_POINTER;

    if ((retVal = rtl8367d_getAsicRegBit(unit, RTL8367D_REG_VLAN_INGRESS, rtksw_switch_port_L2P_get(unit, port), pIgr_filter)) != RT_ERR_OK)
        return retVal;

    return RT_ERR_OK;
}

/* Function Name:
 *      dal_rtl8367d_vlan_portAcceptFrameType_set
 * Description:
 *      Set VLAN accept_frame_type
 * Input:
 *      unit                - Unit ID
 *      port                - Port id.
 *      accept_frame_type   - accept frame type
 * Output:
 *      None
 * Return:
 *      RT_ERR_OK                       - OK
 *      RT_ERR_FAILED                   - Failed
 *      RT_ERR_SMI                      - SMI access error
 *      RT_ERR_PORT_ID                  - Invalid port number.
 *      RT_ERR_VLAN_ACCEPT_FRAME_TYPE   - Invalid frame type.
 * Note:
 *      The API is used for checking 802.1Q tagged frames.
 *      The accept frame type as following:
 *      - RTKSW_ACCEPT_FRAME_TYPE_ALL
 *      - RTKSW_ACCEPT_FRAME_TYPE_TAG_ONLY
 *      - RTKSW_ACCEPT_FRAME_TYPE_UNTAG_ONLY
 */
rtksw_api_ret_t dal_rtl8367d_vlan_portAcceptFrameType_set(rtksw_uint32 unit, rtksw_port_t port, rtksw_vlan_acceptFrameType_t accept_frame_type)
{
    rtksw_api_ret_t retVal;
    rtksw_uint32 mask;

    /* Check initialization state */
    RTKSW_CHK_INIT_STATE(unit);

    /* Check Port Valid */
    RTKSW_CHK_PORT_VALID(unit, port);

    if (accept_frame_type >= RTKSW_ACCEPT_FRAME_TYPE_END)
        return RT_ERR_VLAN_ACCEPT_FRAME_TYPE;

    mask = RTL8367D_PORT0_FRAME_TYPE_MASK << ((rtksw_switch_port_L2P_get(unit, port) & 0x7) << 1);
    if ((retVal = rtl8367d_setAsicRegBits(unit, RTL8367D_REG_VLAN_ACCEPT_FRAME_TYPE_CTRL0, mask, accept_frame_type)) != RT_ERR_OK)
        return retVal;

    return RT_ERR_OK;
}

/* Function Name:
 *      dal_rtl8367d_vlan_portAcceptFrameType_get
 * Description:
 *      Get VLAN accept_frame_type
 * Input:
 *      unit        - Unit ID
 *      port        - Port id.
 * Output:
 *      pAccept_frame_type - accept frame type
 * Return:
 *      RT_ERR_OK           - OK
 *      RT_ERR_FAILED       - Failed
 *      RT_ERR_SMI          - SMI access error
 *      RT_ERR_INPUT        - Invalid input parameters.
 *      RT_ERR_PORT_ID      - Invalid port number.
 * Note:
 *     The API can Get the VLAN ingress filter.
 *     The accept frame type as following:
 *     - RTKSW_ACCEPT_FRAME_TYPE_ALL
 *     - RTKSW_ACCEPT_FRAME_TYPE_TAG_ONLY
 *     - RTKSW_ACCEPT_FRAME_TYPE_UNTAG_ONLY
 */
rtksw_api_ret_t dal_rtl8367d_vlan_portAcceptFrameType_get(rtksw_uint32 unit, rtksw_port_t port, rtksw_vlan_acceptFrameType_t *pAccept_frame_type)
{
    rtksw_api_ret_t retVal;
    rtksw_uint32 mask;
    rtksw_uint32 type;

    /* Check initialization state */
    RTKSW_CHK_INIT_STATE(unit);

    /* Check Port Valid */
    RTKSW_CHK_PORT_VALID(unit, port);

    if(NULL == pAccept_frame_type)
        return RT_ERR_NULL_POINTER;

    mask = RTL8367D_PORT0_FRAME_TYPE_MASK << ((rtksw_switch_port_L2P_get(unit, port) & 0x7) << 1);
    if((retVal = rtl8367d_getAsicRegBits(unit, RTL8367D_REG_VLAN_ACCEPT_FRAME_TYPE_CTRL0, mask, &type)) != RT_ERR_OK)
        return retVal;

    *pAccept_frame_type = (rtksw_vlan_acceptFrameType_t)type;

    return RT_ERR_OK;
}

/* Function Name:
 *      dal_rtl8367d_vlan_tagMode_set
 * Description:
 *      Set CVLAN egress tag mode
 * Input:
 *      unit        - Unit ID
 *      port        - Port id.
 *      tag_mode    - The egress tag mode.
 * Output:
 *      None
 * Return:
 *      RT_ERR_OK           - OK
 *      RT_ERR_FAILED       - Failed
 *      RT_ERR_SMI          - SMI access error
 *      RT_ERR_PORT_ID      - Invalid port number.
 *      RT_ERR_INPUT        - Invalid input parameter.
 *      RT_ERR_ENABLE       - Invalid enable input.
 * Note:
 *      The API can set Egress tag mode. There are 4 mode for egress tag:
 *      - RTKSW_VLAN_TAG_MODE_ORIGINAL,
 *      - RTKSW_VLAN_TAG_MODE_KEEP_FORMAT,
 *      - RTKSW_VLAN_TAG_MODE_PRI.
 *      - RTKSW_VLAN_TAG_MODE_REAL_KEEP_FORMAT,
 */
rtksw_api_ret_t dal_rtl8367d_vlan_tagMode_set(rtksw_uint32 unit, rtksw_port_t port, rtksw_vlan_tagMode_t tag_mode)
{
    rtksw_api_ret_t retVal;
    rtksw_uint32 addr;

    /* Check initialization state */
    RTKSW_CHK_INIT_STATE(unit);

    /* Check Port Valid */
    RTKSW_CHK_PORT_VALID(unit, port);

    if (tag_mode >= RTKSW_VLAN_TAG_MODE_END)
        return RT_ERR_PORT_ID;

    addr = (RTL8367D_REG_PORT0_MISC_CFG + (rtksw_switch_port_L2P_get(unit, port) << 5));
    if ((retVal = rtl8367d_setAsicRegBits(unit, addr, RTL8367D_PORT0_MISC_CFG_VLAN_EGRESS_MODE_MASK, tag_mode)) != RT_ERR_OK)
        return retVal;

    return RT_ERR_OK;
}

/* Function Name:
 *      dal_rtl8367d_vlan_tagMode_get
 * Description:
 *      Get CVLAN egress tag mode
 * Input:
 *      unit        - Unit ID
 *      port        - Port id.
 * Output:
 *      pTag_mode - The egress tag mode.
 * Return:
 *      RT_ERR_OK           - OK
 *      RT_ERR_FAILED       - Failed
 *      RT_ERR_SMI          - SMI access error
 *      RT_ERR_INPUT        - Invalid input parameters.
 *      RT_ERR_PORT_ID      - Invalid port number.
 * Note:
 *      The API can get Egress tag mode. There are 4 mode for egress tag:
 *      - RTKSW_VLAN_TAG_MODE_ORIGINAL,
 *      - RTKSW_VLAN_TAG_MODE_KEEP_FORMAT,
 *      - RTKSW_VLAN_TAG_MODE_PRI.
 *      - RTKSW_VLAN_TAG_MODE_REAL_KEEP_FORMAT,
 */
rtksw_api_ret_t dal_rtl8367d_vlan_tagMode_get(rtksw_uint32 unit, rtksw_port_t port, rtksw_vlan_tagMode_t *pTag_mode)
{
    rtksw_api_ret_t retVal;
    rtksw_uint32  mode;
    rtksw_uint32 addr;

    /* Check initialization state */
    RTKSW_CHK_INIT_STATE(unit);

    /* Check Port Valid */
    RTKSW_CHK_PORT_VALID(unit, port);

    if(NULL == pTag_mode)
        return RT_ERR_NULL_POINTER;

    addr = (RTL8367D_REG_PORT0_MISC_CFG + (rtksw_switch_port_L2P_get(unit, port) << 5));
    if ((retVal = rtl8367d_getAsicRegBits(unit, addr, RTL8367D_PORT0_MISC_CFG_VLAN_EGRESS_MODE_MASK, &mode)) != RT_ERR_OK)
        return retVal;

    *pTag_mode = (rtksw_vlan_tagMode_t)mode;
    return RT_ERR_OK;
}

/* Function Name:
 *      dal_rtl8367d_vlan_transparent_set
 * Description:
 *      Set VLAN transparent mode
 * Input:
 *      unit            - Unit ID
 *      egr_port        - Egress Port id.
 *      pIgr_pmask      - Ingress Port Mask.
 * Output:
 *      None.
 * Return:
 *      RT_ERR_OK           - OK
 *      RT_ERR_FAILED       - Failed
 *      RT_ERR_SMI          - SMI access error
 *      RT_ERR_INPUT        - Invalid input parameters.
 *      RT_ERR_PORT_ID      - Invalid port number.
 * Note:
 *      None.
 */
rtksw_api_ret_t dal_rtl8367d_vlan_transparent_set(rtksw_uint32 unit, rtksw_port_t egr_port, rtksw_portmask_t *pIgr_pmask)
{
     rtksw_api_ret_t retVal;
     rtksw_uint32    pmask;

     /* Check initialization state */
     RTKSW_CHK_INIT_STATE(unit);

     /* Check Port Valid */
     RTKSW_CHK_PORT_VALID(unit, egr_port);

     if(NULL == pIgr_pmask)
        return RT_ERR_NULL_POINTER;

     RTKSW_CHK_PORTMASK_VALID(unit, pIgr_pmask);

     if(rtksw_switch_portmask_L2P_get(unit, pIgr_pmask, &pmask) != RT_ERR_OK)
        return RT_ERR_FAILED;

     if ((retVal = rtl8367d_setAsicRegBits(unit, RTL8367D_REG_VLAN_EGRESS_TRANS_CTRL0 + rtksw_switch_port_L2P_get(unit, egr_port), RTL8367D_VLAN_EGRESS_TRANS_CTRL0_MASK, pmask)) != RT_ERR_OK)
         return retVal;

     return RT_ERR_OK;
}

/* Function Name:
 *      dal_rtl8367d_vlan_transparent_get
 * Description:
 *      Get VLAN transparent mode
 * Input:
 *      unit            - Unit ID
 *      egr_port        - Egress Port id.
 * Output:
 *      pIgr_pmask      - Ingress Port Mask
 * Return:
 *      RT_ERR_OK           - OK
 *      RT_ERR_FAILED       - Failed
 *      RT_ERR_SMI          - SMI access error
 *      RT_ERR_INPUT        - Invalid input parameters.
 *      RT_ERR_PORT_ID      - Invalid port number.
 * Note:
 *      None.
 */
rtksw_api_ret_t dal_rtl8367d_vlan_transparent_get(rtksw_uint32 unit, rtksw_port_t egr_port, rtksw_portmask_t *pIgr_pmask)
{
     rtksw_api_ret_t retVal;
     rtksw_uint32    pmask;

     /* Check initialization state */
     RTKSW_CHK_INIT_STATE(unit);

     /* Check Port Valid */
     RTKSW_CHK_PORT_VALID(unit, egr_port);

     if(NULL == pIgr_pmask)
        return RT_ERR_NULL_POINTER;

     if ((retVal = rtl8367d_getAsicRegBits(unit, RTL8367D_REG_VLAN_EGRESS_TRANS_CTRL0 + rtksw_switch_port_L2P_get(unit, egr_port), RTL8367D_VLAN_EGRESS_TRANS_CTRL0_MASK, &pmask)) != RT_ERR_OK)
         return retVal;

     if(rtksw_switch_portmask_P2L_get(unit, pmask, pIgr_pmask) != RT_ERR_OK)
        return RT_ERR_FAILED;

     return RT_ERR_OK;
}

/* Function Name:
 *      dal_rtl8367d_vlan_keep_set
 * Description:
 *      Set VLAN egress keep mode
 * Input:
 *      unit            - Unit ID
 *      egr_port        - Egress Port id.
 *      pIgr_pmask      - Ingress Port Mask.
 * Output:
 *      None.
 * Return:
 *      RT_ERR_OK           - OK
 *      RT_ERR_FAILED       - Failed
 *      RT_ERR_SMI          - SMI access error
 *      RT_ERR_INPUT        - Invalid input parameters.
 *      RT_ERR_PORT_ID      - Invalid port number.
 * Note:
 *      None.
 */
rtksw_api_ret_t dal_rtl8367d_vlan_keep_set(rtksw_uint32 unit, rtksw_port_t egr_port, rtksw_portmask_t *pIgr_pmask)
{
     rtksw_api_ret_t retVal;
     rtksw_uint32    pmask;
     rtksw_uint32    regAddr, bitMask;

     /* Check initialization state */
     RTKSW_CHK_INIT_STATE(unit);

     /* Check Port Valid */
     RTKSW_CHK_PORT_VALID(unit, egr_port);

     if(NULL == pIgr_pmask)
        return RT_ERR_NULL_POINTER;

     RTKSW_CHK_PORTMASK_VALID(unit, pIgr_pmask);

     if(rtksw_switch_portmask_L2P_get(unit, pIgr_pmask, &pmask) != RT_ERR_OK)
        return RT_ERR_FAILED;

     regAddr = RTL8367D_REG_VLAN_EGRESS_KEEP_CTRL0 + (rtksw_switch_port_L2P_get(unit, egr_port)>>1);
     bitMask = RTL8367D_PORT0_VLAN_KEEP_MASK_MASK<<((rtksw_switch_port_L2P_get(unit, egr_port)&1)*8);
     retVal = rtl8367d_setAsicRegBits(unit, regAddr, bitMask, pmask);
     if(retVal != RT_ERR_OK)
         return retVal;

     return RT_ERR_OK;
}

/* Function Name:
 *      dal_rtl8367d_vlan_keep_get
 * Description:
 *      Get VLAN egress keep mode
 * Input:
 *      unit            - Unit ID
 *      egr_port        - Egress Port id.
 * Output:
 *      pIgr_pmask      - Ingress Port Mask
 * Return:
 *      RT_ERR_OK           - OK
 *      RT_ERR_FAILED       - Failed
 *      RT_ERR_SMI          - SMI access error
 *      RT_ERR_INPUT        - Invalid input parameters.
 *      RT_ERR_PORT_ID      - Invalid port number.
 * Note:
 *      None.
 */
rtksw_api_ret_t dal_rtl8367d_vlan_keep_get(rtksw_uint32 unit, rtksw_port_t egr_port, rtksw_portmask_t *pIgr_pmask)
{
     rtksw_api_ret_t retVal;
     rtksw_uint32    pmask;
     rtksw_uint32    regAddr, bitMask;

     /* Check initialization state */
     RTKSW_CHK_INIT_STATE(unit);

     /* Check Port Valid */
     RTKSW_CHK_PORT_VALID(unit, egr_port);

     if(NULL == pIgr_pmask)
        return RT_ERR_NULL_POINTER;

     regAddr = RTL8367D_REG_VLAN_EGRESS_KEEP_CTRL0 + (rtksw_switch_port_L2P_get(unit, egr_port)>>1);
     bitMask = RTL8367D_PORT0_VLAN_KEEP_MASK_MASK<<((rtksw_switch_port_L2P_get(unit, egr_port)&1)*8);
     retVal = rtl8367d_getAsicRegBits(unit, regAddr, bitMask, &pmask);
     if(retVal != RT_ERR_OK)
         return retVal;

     if(rtksw_switch_portmask_P2L_get(unit, pmask, pIgr_pmask) != RT_ERR_OK)
        return RT_ERR_FAILED;

     return RT_ERR_OK;
}

/* Function Name:
 *      dal_rtl8367d_vlan_stg_set
 * Description:
 *      Set spanning tree group instance of the vlan to the specified device
 * Input:
 *      unit        - Unit ID
 *      vid         - Specified VLAN ID.
 *      stg         - spanning tree group instance.
 * Output:
 *      None
 * Return:
 *      RT_ERR_OK           - OK
 *      RT_ERR_FAILED       - Failed
 *      RT_ERR_SMI          - SMI access error
 *      RT_ERR_MSTI         - Invalid msti parameter
 *      RT_ERR_INPUT        - Invalid input parameter.
 *      RT_ERR_VLAN_VID     - Invalid VID parameter.
 * Note:
 *      The API can set spanning tree group instance of the vlan to the specified device.
 */
rtksw_api_ret_t dal_rtl8367d_vlan_stg_set(rtksw_uint32 unit, rtksw_vlan_t vid, rtksw_stp_msti_id_t stg)
{
    rtksw_api_ret_t retVal;
    dal_rtl8367d_user_vlan4kentry vlan4K;

    /* Check initialization state */
    RTKSW_CHK_INIT_STATE(unit);

    /* vid must be 0~4095 */
    if (vid > RTL8367D_VIDMAX)
        return RT_ERR_VLAN_VID;

    /* stg must be 0~3 */
    if (stg > RTL8367D_MSTIMAX)
        return RT_ERR_MSTI;

    /* update 4K table */
    vlan4K.vid = vid;
    if ((retVal = _dal_rtl8367d_getAsicVlan4kEntry(unit, &vlan4K)) != RT_ERR_OK)
        return retVal;

    vlan4K.fid_msti= stg;
    if ((retVal = _dal_rtl8367d_setAsicVlan4kEntry(unit, &vlan4K)) != RT_ERR_OK)
        return retVal;

    return RT_ERR_OK;
}

/* Function Name:
 *      dal_rtl8367d_vlan_stg_get
 * Description:
 *      Get spanning tree group instance of the vlan to the specified device
 * Input:
 *      unit        - Unit ID
 *      vid         - Specified VLAN ID.
 * Output:
 *      pStg - spanning tree group instance.
 * Return:
 *      RT_ERR_OK           - OK
 *      RT_ERR_FAILED       - Failed
 *      RT_ERR_SMI          - SMI access error
 *      RT_ERR_INPUT        - Invalid input parameters.
 *      RT_ERR_VLAN_VID     - Invalid VID parameter.
 * Note:
 *      The API can get spanning tree group instance of the vlan to the specified device.
 */
rtksw_api_ret_t dal_rtl8367d_vlan_stg_get(rtksw_uint32 unit, rtksw_vlan_t vid, rtksw_stp_msti_id_t *pStg)
{
    rtksw_api_ret_t retVal;
    dal_rtl8367d_user_vlan4kentry vlan4K;

    /* Check initialization state */
    RTKSW_CHK_INIT_STATE(unit);

    /* vid must be 0~4095 */
    if (vid > RTL8367D_VIDMAX)
        return RT_ERR_VLAN_VID;

    if(NULL == pStg)
        return RT_ERR_NULL_POINTER;

    /* update 4K table */
    vlan4K.vid = vid;
    if ((retVal = _dal_rtl8367d_getAsicVlan4kEntry(unit, &vlan4K)) != RT_ERR_OK)
        return retVal;

    *pStg = vlan4K.fid_msti;

    return RT_ERR_OK;
}

/* Function Name:
 *      dal_rtl8367d_vlan_portFid_set
 * Description:
 *      Set port-based filtering database
 * Input:
 *      unit        - Unit ID
 *      port        - Port id.
 *      enable      - ebable port-based FID
 *      fid         - Specified filtering database.
 * Output:
 *      None
 * Return:
 *      RT_ERR_OK              - OK
 *      RT_ERR_FAILED          - Failed
 *      RT_ERR_SMI             - SMI access error
 *      RT_ERR_L2_FID - Invalid fid.
 *      RT_ERR_INPUT - Invalid input parameter.
 *      RT_ERR_PORT_ID - Invalid port ID.
 * Note:
 *      The API can set port-based filtering database. If the function is enabled, all input
 *      packets will be assigned to the port-based fid regardless vlan tag.
 */
rtksw_api_ret_t dal_rtl8367d_vlan_portFid_set(rtksw_uint32 unit, rtksw_port_t port, rtksw_enable_t enable, rtksw_fid_t fid)
{
    rtksw_api_ret_t retVal;

    /* Check initialization state */
    RTKSW_CHK_INIT_STATE(unit);

    /* Check Port Valid */
    RTKSW_CHK_PORT_VALID(unit, port);

    if (enable>=RTKSW_ENABLE_END)
        return RT_ERR_ENABLE;

    /* fid must be 0~3 */
    if (fid > RTL8367D_FIDMAX)
        return RT_ERR_L2_FID;

    if ((retVal = rtl8367d_setAsicRegBit(unit, RTL8367D_REG_PORT_PBFIDEN, rtksw_switch_port_L2P_get(unit, port), enable))!=RT_ERR_OK)
        return retVal;

    if ((retVal = rtl8367d_setAsicReg(unit, RTL8367D_REG_PORT0_PBFID + rtksw_switch_port_L2P_get(unit, port), fid))!=RT_ERR_OK)
        return retVal;

    return RT_ERR_OK;
}

/* Function Name:
 *      dal_rtl8367d_vlan_portFid_get
 * Description:
 *      Get port-based filtering database
 * Input:
 *      unit        - Unit ID
 *      port        - Port id.
 * Output:
 *      pEnable - ebable port-based FID
 *      pFid - Specified filtering database.
 * Return:
 *      RT_ERR_OK              - OK
 *      RT_ERR_FAILED          - Failed
 *      RT_ERR_SMI             - SMI access error
 *      RT_ERR_INPUT - Invalid input parameters.
 *      RT_ERR_PORT_ID - Invalid port ID.
 * Note:
 *      The API can get port-based filtering database status. If the function is enabled, all input
 *      packets will be assigned to the port-based fid regardless vlan tag.
 */
rtksw_api_ret_t dal_rtl8367d_vlan_portFid_get(rtksw_uint32 unit, rtksw_port_t port, rtksw_enable_t *pEnable, rtksw_fid_t *pFid)
{
    rtksw_api_ret_t retVal;

    /* Check initialization state */
    RTKSW_CHK_INIT_STATE(unit);

    /* Check Port Valid */
    RTKSW_CHK_PORT_VALID(unit, port);

    if(NULL == pEnable)
        return RT_ERR_NULL_POINTER;

    if(NULL == pFid)
        return RT_ERR_NULL_POINTER;

    if ((retVal = rtl8367d_getAsicRegBit(unit, RTL8367D_REG_PORT_PBFIDEN, rtksw_switch_port_L2P_get(unit, port), pEnable))!=RT_ERR_OK)
        return retVal;

    if ((retVal = rtl8367d_getAsicReg(unit, RTL8367D_REG_PORT0_PBFID + rtksw_switch_port_L2P_get(unit, port), pFid))!=RT_ERR_OK)
        return retVal;

    return RT_ERR_OK;
}

/*Spanning Tree*/
/* Function Name:
 *      dal_rtl8367d_stp_mstpState_set
 * Description:
 *      Configure spanning tree state per each port.
 * Input:
 *      unit        - Unit ID
 *      port        - Port id
 *      msti        - Multiple spanning tree instance.
 *      stp_state   - Spanning tree state for msti
 * Output:
 *      None
 * Return:
 *      RT_ERR_OK           - OK
 *      RT_ERR_FAILED       - Failed
 *      RT_ERR_SMI          - SMI access error
 *      RT_ERR_PORT_ID      - Invalid port number.
 *      RT_ERR_MSTI         - Invalid msti parameter.
 *      RT_ERR_MSTP_STATE   - Invalid STP state.
 * Note:
 *      System supports per-port multiple spanning tree state for each msti.
 *      There are four states supported by ASIC.
 *      - RTKSW_STP_STATE_DISABLED
 *      - RTKSW_STP_STATE_BLOCKING
 *      - RTKSW_STP_STATE_LEARNING
 *      - RTKSW_STP_STATE_FORWARDING
 */
rtksw_api_ret_t dal_rtl8367d_stp_mstpState_set(rtksw_uint32 unit, rtksw_stp_msti_id_t msti, rtksw_port_t port, rtksw_stp_state_t stp_state)
{
    rtksw_api_ret_t retVal;
    rtksw_uint32 bitMask;
    rtksw_uint32 phyPort;

    /* Check initialization state */
    RTKSW_CHK_INIT_STATE(unit);

    /* Check Port Valid */
    RTKSW_CHK_PORT_VALID(unit, port);

    if (msti > RTL8367D_MSTIMAX)
        return RT_ERR_MSTI;

    if (stp_state >= RTKSW_STP_STATE_END)
        return RT_ERR_MSTP_STATE;

    phyPort = rtksw_switch_port_L2P_get(unit, port);
    if (phyPort == UNDEFINE_PHY_PORT)
        return RT_ERR_PORT_ID;

    bitMask = RTL8367D_VLAN_MSTI0_CTRL0_PORT0_STATE_MASK << (phyPort * 2);
    if ((retVal = rtl8367d_setAsicRegBits(unit, RTL8367D_REG_VLAN_MSTI0_CTRL0 + (msti * 2), bitMask, stp_state)) != RT_ERR_OK)
        return retVal;

    return RT_ERR_OK;
}

/* Function Name:
 *      dal_rtl8367d_stp_mstpState_get
 * Description:
 *      Get spanning tree state per each port.
 * Input:
 *      unit        - Unit ID
 *      port        - Port id.
 *      msti        - Multiple spanning tree instance.
 * Output:
 *      pStp_state - Spanning tree state for msti
 * Return:
 *      RT_ERR_OK           - OK
 *      RT_ERR_FAILED       - Failed
 *      RT_ERR_SMI          - SMI access error
 *      RT_ERR_PORT_ID      - Invalid port number.
 *      RT_ERR_MSTI         - Invalid msti parameter.
 * Note:
 *      System supports per-port multiple spanning tree state for each msti.
 *      There are four states supported by ASIC.
 *      - RTKSW_STP_STATE_DISABLED
 *      - RTKSW_STP_STATE_BLOCKING
 *      - RTKSW_STP_STATE_LEARNING
 *      - RTKSW_STP_STATE_FORWARDING
 */
rtksw_api_ret_t dal_rtl8367d_stp_mstpState_get(rtksw_uint32 unit, rtksw_stp_msti_id_t msti, rtksw_port_t port, rtksw_stp_state_t *pStp_state)
{
    rtksw_api_ret_t retVal;
    rtksw_uint32 bitMask;
    rtksw_uint32 phyPort;

    /* Check initialization state */
    RTKSW_CHK_INIT_STATE(unit);

    /* Check Port Valid */
    RTKSW_CHK_PORT_VALID(unit, port);

    if (msti > RTL8367D_MSTIMAX)
        return RT_ERR_MSTI;

    if(NULL == pStp_state)
        return RT_ERR_NULL_POINTER;

    phyPort = rtksw_switch_port_L2P_get(unit, port);
    if (phyPort == UNDEFINE_PHY_PORT)
        return RT_ERR_PORT_ID;

    bitMask = RTL8367D_VLAN_MSTI0_CTRL0_PORT0_STATE_MASK << (phyPort * 2);
    if ((retVal = rtl8367d_getAsicRegBits(unit, RTL8367D_REG_VLAN_MSTI0_CTRL0 + (msti * 2), bitMask, pStp_state)) != RT_ERR_OK)
        return retVal;

    return RT_ERR_OK;
}


/* Function Name:
 *      dal_rtl8367d_vlan_reservedVidAction_set
 * Description:
 *      Set Action of VLAN ID = 0 & 4095 tagged packet
 * Input:
 *      unit            - Unit ID
 *      action_vid0     - Action for VID 0.
 *      action_vid4095  - Action for VID 4095.
 * Output:
 *      None.
 * Return:
 *      RT_ERR_OK           - OK
 *      RT_ERR_FAILED       - Failed
 *      RT_ERR_SMI          - SMI access error
 *      RT_ERR_INPUT        - Error Input
 * Note:
 *
 */
rtksw_api_ret_t dal_rtl8367d_vlan_reservedVidAction_set(rtksw_uint32 unit, rtksw_vlan_resVidAction_t action_vid0, rtksw_vlan_resVidAction_t action_vid4095)
{
    rtksw_api_ret_t retVal;

    /* Check initialization state */
    RTKSW_CHK_INIT_STATE(unit);

    if(action_vid0 >= RTKSW_RESVID_ACTION_END)
        return RT_ERR_INPUT;

    if(action_vid4095 >= RTKSW_RESVID_ACTION_END)
        return RT_ERR_INPUT;

    if((retVal = rtl8367d_setAsicRegBit(unit, RTL8367D_REG_VLAN_EXT_CTRL, RTL8367D_VLAN_VID0_TYPE_OFFSET, action_vid0)) != RT_ERR_OK)
        return retVal;

    if((retVal = rtl8367d_setAsicRegBit(unit, RTL8367D_REG_VLAN_EXT_CTRL, RTL8367D_VLAN_VID4095_TYPE_OFFSET, action_vid4095)) != RT_ERR_OK)
        return retVal;

    return RT_ERR_OK;
}

/* Function Name:
 *      dal_rtl8367d_vlan_reservedVidAction_get
 * Description:
 *      Get Action of VLAN ID = 0 & 4095 tagged packet
 * Input:
 *      unit            - Unit ID
 *      pAction_vid0    - Action for VID 0.
 *      pAction_vid4095 - Action for VID 4095.
 * Output:
 *      None.
 * Return:
 *      RT_ERR_OK           - OK
 *      RT_ERR_FAILED       - Failed
 *      RT_ERR_SMI          - SMI access error
 *      RT_ERR_NULL_POINTER - NULL Pointer
 * Note:
 *
 */
rtksw_api_ret_t dal_rtl8367d_vlan_reservedVidAction_get(rtksw_uint32 unit, rtksw_vlan_resVidAction_t *pAction_vid0, rtksw_vlan_resVidAction_t *pAction_vid4095)
{
    rtksw_api_ret_t retVal;

    /* Check initialization state */
    RTKSW_CHK_INIT_STATE(unit);

    if(pAction_vid0 == NULL)
        return RT_ERR_NULL_POINTER;

    if(pAction_vid4095 == NULL)
        return RT_ERR_NULL_POINTER;

    if((retVal = rtl8367d_getAsicRegBit(unit, RTL8367D_REG_VLAN_EXT_CTRL, RTL8367D_VLAN_VID0_TYPE_OFFSET, (rtksw_uint32 *)pAction_vid0)) != RT_ERR_OK)
        return retVal;

    if((retVal = rtl8367d_getAsicRegBit(unit, RTL8367D_REG_VLAN_EXT_CTRL, RTL8367D_VLAN_VID4095_TYPE_OFFSET, (rtksw_uint32 *)pAction_vid4095)) != RT_ERR_OK)
        return retVal;

    return RT_ERR_OK;
}

/* Function Name:
 *      dal_rtl8367d_vlan_realKeepRemarkEnable_set
 * Description:
 *      Set Real keep 1p remarking feature
 * Input:
 *      unit        - Unit ID
 *      enabled     - State of 1p remarking at real keep packet
 * Output:
 *      None.
 * Return:
 *      RT_ERR_OK           - OK
 *      RT_ERR_FAILED       - Failed
 *      RT_ERR_SMI          - SMI access error
 *      RT_ERR_INPUT        - Error Input
 * Note:
 *
 */
rtksw_api_ret_t dal_rtl8367d_vlan_realKeepRemarkEnable_set(rtksw_uint32 unit, rtksw_enable_t enabled)
{
    rtksw_api_ret_t retVal;

    /* Check initialization state */
    RTKSW_CHK_INIT_STATE(unit);

    if(enabled >= RTKSW_ENABLE_END)
        return RT_ERR_INPUT;

    if((retVal = rtl8367d_setAsicRegBit(unit, RTL8367D_REG_VLAN_EXT_CTRL, RTL8367D_VLAN_1P_REMARK_BYPASS_REALKEEP_OFFSET, enabled)) != RT_ERR_OK)
        return retVal;

    return RT_ERR_OK;
}

/* Function Name:
 *      dal_rtl8367d_vlan_realKeepRemarkEnable_get
 * Description:
 *      Get Real keep 1p remarking feature
 * Input:
 *      unit        - Unit ID
 * Output:
 *      pEnabled     - State of 1p remarking at real keep packet
 * Return:
 *      RT_ERR_OK           - OK
 *      RT_ERR_FAILED       - Failed
 *      RT_ERR_SMI          - SMI access error
 *      RT_ERR_INPUT        - Error Input
 * Note:
 *
 */
rtksw_api_ret_t dal_rtl8367d_vlan_realKeepRemarkEnable_get(rtksw_uint32 unit, rtksw_enable_t *pEnabled)
{
    rtksw_api_ret_t retVal;

    /* Check initialization state */
    RTKSW_CHK_INIT_STATE(unit);

    if(NULL == pEnabled)
        return RT_ERR_NULL_POINTER;

    if((retVal = rtl8367d_getAsicRegBit(unit, RTL8367D_REG_VLAN_EXT_CTRL, RTL8367D_VLAN_1P_REMARK_BYPASS_REALKEEP_OFFSET, (rtksw_uint32 *)pEnabled)) != RT_ERR_OK)
        return retVal;

    return RT_ERR_OK;
}


/* Function Name:
 *      dal_rtl8367d_vlan_reset
 * Description:
 *      Reset VLAN
 * Input:
 *      unit        - Unit ID
 * Output:
 *      None.
 * Return:
 *      RT_ERR_OK           - OK
 *      RT_ERR_FAILED       - Failed
 *      RT_ERR_SMI          - SMI access error
 *      RT_ERR_INPUT        - Error Input
 * Note:
 *
 */
rtksw_api_ret_t dal_rtl8367d_vlan_reset(rtksw_uint32 unit)
{
    rtksw_api_ret_t retVal;

    /* Check initialization state */
    RTKSW_CHK_INIT_STATE(unit);

    if((retVal = rtl8367d_setAsicRegBit(unit, RTL8367D_REG_VLAN_EXT_CTRL2, RTL8367D_VLAN_EXT_CTRL2_OFFSET, 1)) != RT_ERR_OK)
        return retVal;

    return RT_ERR_OK;
}



