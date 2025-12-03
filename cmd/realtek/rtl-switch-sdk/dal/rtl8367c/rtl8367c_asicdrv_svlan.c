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
 * Purpose : RTL8367C switch high-level API for RTL8367C
 * Feature : SVLAN related functions
 *
 */
#include "rtl8367c_asicdrv_svlan.h"

#include "../../osal/lib.h"

static void _rtl8367c_svlanConfStUser2Smi( rtl8367c_svlan_memconf_t *pUserSt, rtksw_uint16 *pSmiSt)
{
    pSmiSt[0] |= (pUserSt->vs_member & 0x00FF);
    pSmiSt[0] |= (pUserSt->vs_untag & 0x00FF) << 8;

    pSmiSt[1] |= (pUserSt->vs_fid_msti & 0x000F);
    pSmiSt[1] |= (pUserSt->vs_priority & 0x0007) << 4;
    pSmiSt[1] |= (pUserSt->vs_force_fid & 0x0001) << 7;

    pSmiSt[2] |= (pUserSt->vs_svid & 0x0FFF);
    pSmiSt[2] |= (pUserSt->vs_efiden & 0x0001) << 12;
    pSmiSt[2] |= (pUserSt->vs_efid & 0x0007) << 13;

    pSmiSt[3] |= ((pUserSt->vs_member & 0x0700) >> 8);
    pSmiSt[3] |= ((pUserSt->vs_untag & 0x0700) >> 8) << 8;
}

static void _rtl8367c_svlanConfStSmi2User( rtl8367c_svlan_memconf_t *pUserSt, rtksw_uint16 *pSmiSt)
{

    pUserSt->vs_member = (pSmiSt[0] & 0x00FF) | ((pSmiSt[3] & 0x0007) << 8);
    pUserSt->vs_untag = ((pSmiSt[0] & 0xFF00) >> 8) | (((pSmiSt[3] & 0x0700) >> 8) << 8);

    pUserSt->vs_fid_msti = (pSmiSt[1] & 0x000F);
    pUserSt->vs_priority = (pSmiSt[1] & 0x0070) >> 4;
    pUserSt->vs_force_fid = (pSmiSt[1] & 0x0080) >> 7;

    pUserSt->vs_svid = (pSmiSt[2] & 0x0FFF);
    pUserSt->vs_efiden = (pSmiSt[2] & 0x1000) >> 12;
    pUserSt->vs_efid = (pSmiSt[2] & 0xE000) >> 13;
}

static void _rtl8367c_svlanMc2sStUser2Smi(rtl8367c_svlan_mc2s_t *pUserSt, rtksw_uint16 *pSmiSt)
{
    pSmiSt[0] |= (pUserSt->svidx & 0x003F);
    pSmiSt[0] |= (pUserSt->format & 0x0001) << 6;
    pSmiSt[0] |= (pUserSt->valid & 0x0001) << 7;

    pSmiSt[1] = (rtksw_uint16)(pUserSt->smask & 0x0000FFFF);
    pSmiSt[2] = (rtksw_uint16)((pUserSt->smask & 0xFFFF0000) >> 16);

    pSmiSt[3] = (rtksw_uint16)(pUserSt->sdata & 0x0000FFFF);
    pSmiSt[4] = (rtksw_uint16)((pUserSt->sdata & 0xFFFF0000) >> 16);
}

static void _rtl8367c_svlanMc2sStSmi2User(rtl8367c_svlan_mc2s_t *pUserSt, rtksw_uint16 *pSmiSt)
{
    pUserSt->svidx = (pSmiSt[0] & 0x003F);
    pUserSt->format = (pSmiSt[0] & 0x0040) >> 6;
    pUserSt->valid = (pSmiSt[0] & 0x0080) >> 7;

    pUserSt->smask = pSmiSt[1] | (pSmiSt[2] << 16);
    pUserSt->sdata = pSmiSt[3] | (pSmiSt[4] << 16);
}

static void _rtl8367c_svlanSp2cStUser2Smi(rtl8367c_svlan_s2c_t *pUserSt, rtksw_uint16 *pSmiSt)
{
    pSmiSt[0] |= (pUserSt->dstport & 0x0007);
    pSmiSt[0] |= (pUserSt->svidx & 0x003F) << 3;
    pSmiSt[0] |= ((pUserSt->dstport & 0x0008) >> 3) << 9;

    pSmiSt[1] |= (pUserSt->vid & 0x0FFF);
    pSmiSt[1] |= (pUserSt->valid & 0x0001) << 12;
}

static void _rtl8367c_svlanSp2cStSmi2User(rtl8367c_svlan_s2c_t *pUserSt, rtksw_uint16 *pSmiSt)
{
    pUserSt->dstport = (((pSmiSt[0] & 0x0200) >> 9) << 3) | (pSmiSt[0] & 0x0007);
    pUserSt->svidx   = (pSmiSt[0] & 0x01F8) >> 3;
    pUserSt->vid     = (pSmiSt[1] & 0x0FFF);
    pUserSt->valid   = (pSmiSt[1] & 0x1000) >> 12;
}

/* Function Name:
 *      rtl8367c_setAsicSvlanUplinkPortMask
 * Description:
 *      Set uplink ports mask
 * Input:
 *      unit        - Unit ID
 *      portMask    - Uplink port mask setting
 * Output:
 *      None
 * Return:
 *      RT_ERR_OK   - Success
 *      RT_ERR_SMI  - SMI access error
 * Note:
 *      None
 */
ret_t rtl8367c_setAsicSvlanUplinkPortMask(rtksw_uint32 unit, rtksw_uint32 portMask)
{
    return rtl8367c_setAsicReg(unit, RTL8367C_REG_SVLAN_UPLINK_PORTMASK, portMask);
}
/* Function Name:
 *      rtl8367c_getAsicSvlanUplinkPortMask
 * Description:
 *      Get uplink ports mask
 * Input:
 *      unit        - Unit ID
 *      pPortmask   - Uplink port mask setting
 * Output:
 *      None
 * Return:
 *      RT_ERR_OK   - Success
 *      RT_ERR_SMI  - SMI access error
 * Note:
 *      None
 */
ret_t rtl8367c_getAsicSvlanUplinkPortMask(rtksw_uint32 unit, rtksw_uint32* pPortmask)
{
    return rtl8367c_getAsicReg(unit, RTL8367C_REG_SVLAN_UPLINK_PORTMASK, pPortmask);
}
/* Function Name:
 *      rtl8367c_setAsicSvlanTpid
 * Description:
 *      Set accepted S-VLAN ether type. The default ether type of S-VLAN is 0x88a8
 * Input:
 *      unit            - Unit ID
 *      protocolType    - Ether type of S-tag frame parsing in uplink ports
 * Output:
 *      None
 * Return:
 *      RT_ERR_OK   - Success
 *      RT_ERR_SMI  - SMI access error
 * Note:
 *      Ether type of S-tag in 802.1ad is 0x88a8 and there are existed ether type 0x9100 and 0x9200
 *      for Q-in-Q SLAN design. User can set mathced ether type as service provider supported protocol
 */
ret_t rtl8367c_setAsicSvlanTpid(rtksw_uint32 unit, rtksw_uint32 protocolType)
{
    return rtl8367c_setAsicReg(unit, RTL8367C_REG_VS_TPID, protocolType);
}
/* Function Name:
 *      rtl8367c_getAsicReg
 * Description:
 *      Get accepted S-VLAN ether type. The default ether type of S-VLAN is 0x88a8
 * Input:
 *      unit            - Unit ID
 *      pProtocolType   - Ether type of S-tag frame parsing in uplink ports
 * Output:
 *      None
 * Return:
 *      RT_ERR_OK   - Success
 *      RT_ERR_SMI  - SMI access error
 * Note:
 *      None
 */
ret_t rtl8367c_getAsicSvlanTpid(rtksw_uint32 unit, rtksw_uint32* pProtocolType)
{
    return rtl8367c_getAsicReg(unit, RTL8367C_REG_VS_TPID, pProtocolType);
}
/* Function Name:
 *      rtl8367c_setAsicSvlanPrioritySel
 * Description:
 *      Set SVLAN priority field setting
 * Input:
 *      unit        - Unit ID
 *      priSel      - S-priority assignment method, 0:internal priority 1:C-tag priority 2:using Svlan member configuration
 * Output:
 *      None
 * Return:
 *      RT_ERR_OK       - Success
 *      RT_ERR_SMI      - SMI access error
 *      RT_ERR_INPUT    - Invalid input parameter
 * Note:
 *      None
 */
ret_t rtl8367c_setAsicSvlanPrioritySel(rtksw_uint32 unit, rtksw_uint32 priSel)
{
    if(priSel >= SPRISEL_END)
        return RT_ERR_QOS_INT_PRIORITY;

    return rtl8367c_setAsicRegBits(unit, RTL8367C_REG_SVLAN_CFG, RTL8367C_VS_SPRISEL_MASK, priSel);
}
/* Function Name:
 *      rtl8367c_getAsicSvlanPrioritySel
 * Description:
 *      Get SVLAN priority field setting
 * Input:
 *      unit        - Unit ID
 *      pPriSel     - S-priority assignment method, 0:internal priority 1:C-tag priority 2:using Svlan member configuration
 * Output:
 *      None
 * Return:
 *      RT_ERR_OK   - Success
 *      RT_ERR_SMI  - SMI access error
 * Note:
 *      None
 */
ret_t rtl8367c_getAsicSvlanPrioritySel(rtksw_uint32 unit, rtksw_uint32* pPriSel)
{
    return rtl8367c_getAsicRegBits(unit, RTL8367C_REG_SVLAN_CFG, RTL8367C_VS_SPRISEL_MASK, pPriSel);
}
/* Function Name:
 *      rtl8367c_setAsicSvlanTrapPriority
 * Description:
 *      Set trap to CPU priority assignment
 * Input:
 *      unit        - Unit ID
 *      priority    - Priority assignment
 * Output:
 *      None
 * Return:
 *      RT_ERR_OK               - Success
 *      RT_ERR_SMI              - SMI access error
 *      RT_ERR_QOS_INT_PRIORITY - Invalid priority
 * Note:
 *      None
 */
ret_t rtl8367c_setAsicSvlanTrapPriority(rtksw_uint32 unit, rtksw_uint32 priority)
{
    if(priority > RTL8367C_PRIMAX)
        return RT_ERR_QOS_INT_PRIORITY;

    return rtl8367c_setAsicRegBits(unit, RTL8367C_REG_QOS_TRAP_PRIORITY0, RTL8367C_SVLAN_PRIOIRTY_MASK, priority);
}
/* Function Name:
 *      rtl8367c_getAsicSvlanTrapPriority
 * Description:
 *      Get trap to CPU priority assignment
 * Input:
 *      unit        - Unit ID
 *      pPriority   - Priority assignment
 * Output:
 *      None
 * Return:
 *      RT_ERR_OK   - Success
 *      RT_ERR_SMI  - SMI access error
 * Note:
 *      None
 */
ret_t rtl8367c_getAsicSvlanTrapPriority(rtksw_uint32 unit, rtksw_uint32* pPriority)
{
    return rtl8367c_getAsicRegBits(unit, RTL8367C_REG_QOS_TRAP_PRIORITY0, RTL8367C_SVLAN_PRIOIRTY_MASK, pPriority);
}
/* Function Name:
 *      rtl8367c_setAsicSvlanDefaultVlan
 * Description:
 *      Set default egress SVLAN
 * Input:
 *      unit        - Unit ID
 *      port        - Physical port number (0~10)
 *      index       - index SVLAN member configuration
 * Output:
 *      None
 * Return:
 *      RT_ERR_OK                   - Success
 *      RT_ERR_SMI                  - SMI access error
 *      RT_ERR_PORT_ID              - Invalid port number
 *      RT_ERR_SVLAN_ENTRY_INDEX    - Invalid SVLAN index parameter
 * Note:
 *      None
 */
ret_t rtl8367c_setAsicSvlanDefaultVlan(rtksw_uint32 unit, rtksw_uint32 port, rtksw_uint32 index)
{
    ret_t retVal = RT_ERR_FAILED;

    if(port > RTL8367C_PORTIDMAX)
        return RT_ERR_PORT_ID;

    if(index > RTL8367C_SVIDXMAX)
        return RT_ERR_SVLAN_ENTRY_INDEX;

    if(port < 8)
    {
        if(port & 1)
            retVal = rtl8367c_setAsicRegBits(unit, RTL8367C_REG_SVLAN_PORTBASED_SVIDX_CTRL0 + (port >> 1), RTL8367C_VS_PORT1_SVIDX_MASK,index);
        else
            retVal = rtl8367c_setAsicRegBits(unit, RTL8367C_REG_SVLAN_PORTBASED_SVIDX_CTRL0 + (port >> 1), RTL8367C_VS_PORT0_SVIDX_MASK,index);
    }
    else
    {
        switch(port)
        {
            case 8:
                retVal = rtl8367c_setAsicRegBits(unit, RTL8367C_REG_SVLAN_PORTBASED_SVIDX_CTRL4, RTL8367C_VS_PORT8_SVIDX_MASK,index);
                break;
            case 9:
                retVal = rtl8367c_setAsicRegBits(unit, RTL8367C_REG_SVLAN_PORTBASED_SVIDX_CTRL4, RTL8367C_VS_PORT9_SVIDX_MASK,index);
                break;
            case 10:
                retVal = rtl8367c_setAsicRegBits(unit, RTL8367C_REG_SVLAN_PORTBASED_SVIDX_CTRL5, RTL8367C_SVLAN_PORTBASED_SVIDX_CTRL5_MASK,index);
                break;
            default:
                return RT_ERR_PORT_ID;
        }
    }

    return retVal;
}
/* Function Name:
 *      rtl8367c_getAsicSvlanDefaultVlan
 * Description:
 *      Get default egress SVLAN
 * Input:
 *      unit        - Unit ID
 *      port        - Physical port number (0~7)
 *      pIndex      - index SVLAN member configuration
 * Output:
 *      None
 * Return:
 *      RT_ERR_OK       - Success
 *      RT_ERR_SMI      - SMI access error
 *      RT_ERR_PORT_ID  - Invalid port number
 * Note:
 *      None
 */
ret_t rtl8367c_getAsicSvlanDefaultVlan(rtksw_uint32 unit, rtksw_uint32 port, rtksw_uint32* pIndex)
{
    ret_t retVal = RT_ERR_FAILED;

    if(port > RTL8367C_PORTIDMAX)
        return RT_ERR_PORT_ID;

    if(port < 8)
    {
        if(port & 1)
            retVal = rtl8367c_getAsicRegBits(unit, RTL8367C_REG_SVLAN_PORTBASED_SVIDX_CTRL0 + (port >> 1), RTL8367C_VS_PORT1_SVIDX_MASK,pIndex);
        else
            retVal = rtl8367c_getAsicRegBits(unit, RTL8367C_REG_SVLAN_PORTBASED_SVIDX_CTRL0 + (port >> 1), RTL8367C_VS_PORT0_SVIDX_MASK,pIndex);
    }
    else
    {
        switch(port)
        {
            case 8:
                retVal = rtl8367c_getAsicRegBits(unit, RTL8367C_REG_SVLAN_PORTBASED_SVIDX_CTRL4, RTL8367C_VS_PORT8_SVIDX_MASK,pIndex);
                break;
            case 9:
                retVal = rtl8367c_getAsicRegBits(unit, RTL8367C_REG_SVLAN_PORTBASED_SVIDX_CTRL4, RTL8367C_VS_PORT9_SVIDX_MASK,pIndex);
                break;
            case 10:
                retVal = rtl8367c_getAsicRegBits(unit, RTL8367C_REG_SVLAN_PORTBASED_SVIDX_CTRL5, RTL8367C_SVLAN_PORTBASED_SVIDX_CTRL5_MASK,pIndex);
                break;
            default:
                return RT_ERR_PORT_ID;
        }
    }

    return retVal;

}
/* Function Name:
 *      rtl8367c_setAsicSvlanIngressUntag
 * Description:
 *      Set action received un-Stag frame from unplink port
 * Input:
 *      unit        - Unit ID
 *      mode        - 0:Drop 1:Trap 2:Assign SVLAN
 * Output:
 *      None
 * Return:
 *      RT_ERR_OK   - Success
 *      RT_ERR_SMI  - SMI access error
 * Note:
 *      None
 */
ret_t rtl8367c_setAsicSvlanIngressUntag(rtksw_uint32 unit, rtksw_uint32 mode)
{
    return rtl8367c_setAsicRegBits(unit, RTL8367C_REG_SVLAN_CFG, RTL8367C_VS_UNTAG_MASK, mode);
}
/* Function Name:
 *      rtl8367c_getAsicSvlanIngressUntag
 * Description:
 *      Get action received un-Stag frame from unplink port
 * Input:
 *      unit        - Unit ID
 *      pMode       - 0:Drop 1:Trap 2:Assign SVLAN
 * Output:
 *      None
 * Return:
 *      RT_ERR_OK   - Success
 *      RT_ERR_SMI  - SMI access error
 * Note:
 *      None
 */
ret_t rtl8367c_getAsicSvlanIngressUntag(rtksw_uint32 unit, rtksw_uint32* pMode)
{
    return rtl8367c_getAsicRegBits(unit, RTL8367C_REG_SVLAN_CFG, RTL8367C_VS_UNTAG_MASK, pMode);
}
/* Function Name:
 *      rtl8367c_setAsicSvlanIngressUnmatch
 * Description:
 *      Set action received unmatched Stag frame from unplink port
 * Input:
 *      unit        - Unit ID
 *      mode        - 0:Drop 1:Trap 2:Assign SVLAN
 * Output:
 *      None
 * Return:
 *      RT_ERR_OK   - Success
 *      RT_ERR_SMI  - SMI access error
 * Note:
 *      None
 */
ret_t rtl8367c_setAsicSvlanIngressUnmatch(rtksw_uint32 unit, rtksw_uint32 mode)
{
    return rtl8367c_setAsicRegBits(unit, RTL8367C_REG_SVLAN_CFG, RTL8367C_VS_UNMAT_MASK, mode);
}
/* Function Name:
 *      rtl8367c_getAsicSvlanIngressUnmatch
 * Description:
 *      Get action received unmatched Stag frame from unplink port
 * Input:
 *      unit        - Unit ID
 *      pMode       - 0:Drop 1:Trap 2:Assign SVLAN
 * Output:
 *      None
 * Return:
 *      RT_ERR_OK   - Success
 *      RT_ERR_SMI  - SMI access error
 * Note:
 *      None
 */
ret_t rtl8367c_getAsicSvlanIngressUnmatch(rtksw_uint32 unit, rtksw_uint32* pMode)
{
    return rtl8367c_getAsicRegBits(unit, RTL8367C_REG_SVLAN_CFG, RTL8367C_VS_UNMAT_MASK, pMode);

}
/* Function Name:
 *      rtl8367c_setAsicSvlanEgressUnassign
 * Description:
 *      Set unplink stream without egress SVID action
 * Input:
 *      unit        - Unit ID
 *      enabled     - 1:Trap egress unassigned frames to CPU, 0: Use SVLAN setup in VS_CPSVIDX as egress SVID
 * Output:
 *      None
 * Return:
 *      RT_ERR_OK   - Success
 *      RT_ERR_SMI  - SMI access error
 * Note:
 *      None
 */
ret_t rtl8367c_setAsicSvlanEgressUnassign(rtksw_uint32 unit, rtksw_uint32 enabled)
{
    return rtl8367c_setAsicRegBit(unit, RTL8367C_REG_SVLAN_CFG, RTL8367C_VS_UIFSEG_OFFSET, enabled);
}
/* Function Name:
 *      rtl8367c_getAsicSvlanEgressUnassign
 * Description:
 *      Get unplink stream without egress SVID action
 * Input:
 *      unit        - Unit ID
 *      pEnabled    - 1:Trap egress unassigned frames to CPU, 0: Use SVLAN setup in VS_CPSVIDX as egress SVID
 * Output:
 *      None
 * Return:
 *      RT_ERR_OK   - Success
 *      RT_ERR_SMI  - SMI access error
 * Note:
 *      None
 */
ret_t rtl8367c_getAsicSvlanEgressUnassign(rtksw_uint32 unit, rtksw_uint32* pEnabled)
{
    return rtl8367c_getAsicRegBit(unit, RTL8367C_REG_SVLAN_CFG, RTL8367C_VS_UIFSEG_OFFSET, pEnabled);
}


/* Function Name:
 *      rtl8367c_setAsicSvlanMemberConfiguration
 * Description:
 *      Set system 64 S-tag content
 * Input:
 *      unit            - Unit ID
 *      index           - index of 64 s-tag configuration
 *      pSvlanMemCfg    - SVLAN member configuration
 * Output:
 *      None
 * Return:
 *      RT_ERR_OK                   - Success
 *      RT_ERR_SMI                  - SMI access error
 *      RT_ERR_SVLAN_ENTRY_INDEX    - Invalid SVLAN index parameter
 * Note:
 *      None
 */
ret_t rtl8367c_setAsicSvlanMemberConfiguration(rtksw_uint32 unit, rtksw_uint32 index, rtl8367c_svlan_memconf_t* pSvlanMemCfg)
{
    ret_t retVal;
    rtksw_uint32 regAddr = 0, regData;
    rtksw_uint16 *accessPtr;
    rtksw_uint32 i;
    rtksw_uint16 smiSvlanMemConf[RTL8367C_SVLAN_MEMCONF_LEN];

    if(index > RTL8367C_SVIDXMAX)
        return RT_ERR_SVLAN_ENTRY_INDEX;

    osal_memset(smiSvlanMemConf, 0x00, sizeof(rtksw_uint16) * RTL8367C_SVLAN_MEMCONF_LEN);
    _rtl8367c_svlanConfStUser2Smi(pSvlanMemCfg, smiSvlanMemConf);

    accessPtr = smiSvlanMemConf;

    regData = *accessPtr;
    for(i = 0; i < 3; i++)
    {
        retVal = rtl8367c_setAsicReg(unit, RTL8367C_SVLAN_MEMBERCFG_BASE_REG(index) + i, regData);
        if(retVal != RT_ERR_OK)
            return retVal;

        accessPtr ++;
        regData = *accessPtr;
    }

    if(index < 63)
        regAddr = RTL8367C_REG_SVLAN_MEMBERCFG0_CTRL4+index;
    else if(index == 63)
        regAddr = RTL8367C_REG_SVLAN_MEMBERCFG63_CTRL4;

    retVal = rtl8367c_setAsicReg(unit, regAddr, regData);
    if(retVal != RT_ERR_OK)
        return retVal;

    return RT_ERR_OK;

}
/* Function Name:
 *      rtl8367c_getAsicSvlanMemberConfiguration
 * Description:
 *      Get system 64 S-tag content
 * Input:
 *      unit            - Unit ID
 *      index           - index of 64 s-tag configuration
 *      pSvlanMemCfg    - SVLAN member configuration
 * Output:
 *      None
 * Return:
 *      RT_ERR_OK                   - Success
 *      RT_ERR_SMI                  - SMI access error
 *      RT_ERR_SVLAN_ENTRY_INDEX    - Invalid SVLAN index parameter
 * Note:
 *      None
 */
ret_t rtl8367c_getAsicSvlanMemberConfiguration(rtksw_uint32 unit, rtksw_uint32 index,rtl8367c_svlan_memconf_t* pSvlanMemCfg)
{
    ret_t retVal;
    rtksw_uint32 regAddr = 0,regData;
    rtksw_uint16 *accessPtr;
    rtksw_uint32 i;
    rtksw_uint16 smiSvlanMemConf[RTL8367C_SVLAN_MEMCONF_LEN];

    if(index > RTL8367C_SVIDXMAX)
        return RT_ERR_SVLAN_ENTRY_INDEX;

    osal_memset(smiSvlanMemConf, 0x00, sizeof(rtksw_uint16) * RTL8367C_SVLAN_MEMCONF_LEN);

    accessPtr = smiSvlanMemConf;

    for(i = 0; i < 3; i++)
    {
        retVal = rtl8367c_getAsicReg(unit, RTL8367C_SVLAN_MEMBERCFG_BASE_REG(index) + i, &regData);
        if(retVal != RT_ERR_OK)
            return retVal;

        *accessPtr = regData;

        accessPtr ++;
    }

    if(index < 63)
        regAddr = RTL8367C_REG_SVLAN_MEMBERCFG0_CTRL4+index;
    else if(index == 63)
        regAddr = RTL8367C_REG_SVLAN_MEMBERCFG63_CTRL4;

    retVal = rtl8367c_getAsicReg(unit, regAddr, &regData);
    if(retVal != RT_ERR_OK)
        return retVal;

    *accessPtr = regData;

    _rtl8367c_svlanConfStSmi2User(pSvlanMemCfg, smiSvlanMemConf);

    return RT_ERR_OK;
}
/* Function Name:
 *      rtl8367c_setAsicSvlanC2SConf
 * Description:
 *      Set SVLAN C2S table
 * Input:
 *      unit        - Unit ID
 *      index       - index of 128 Svlan C2S configuration
 *      evid        - Enhanced VID
 *      portmask    - available c2s port mask
 *      svidx       - index of 64 Svlan member configuration
 * Output:
 *      None
 * Return:
 *      RT_ERR_OK           - Success
 *      RT_ERR_SMI          - SMI access error
 *      RT_ERR_ENTRY_INDEX  - Invalid entry index
 * Note:
 *      ASIC will check upstream's VID and assign related SVID to mathed packet
 */
ret_t rtl8367c_setAsicSvlanC2SConf(rtksw_uint32 unit, rtksw_uint32 index, rtksw_uint32 evid, rtksw_uint32 portmask, rtksw_uint32 svidx)
{
    ret_t retVal;

    if(index > RTL8367C_C2SIDXMAX)
        return RT_ERR_ENTRY_INDEX;

    retVal = rtl8367c_setAsicReg(unit, RTL8367C_SVLAN_C2SCFG_BASE_REG(index), svidx);
    if(retVal != RT_ERR_OK)
        return retVal;

    retVal = rtl8367c_setAsicReg(unit, RTL8367C_SVLAN_C2SCFG_BASE_REG(index) + 1, portmask);
    if(retVal != RT_ERR_OK)
        return retVal;

    retVal = rtl8367c_setAsicReg(unit, RTL8367C_SVLAN_C2SCFG_BASE_REG(index) + 2, evid);
    if(retVal != RT_ERR_OK)
        return retVal;

    return RT_ERR_OK;
}
/* Function Name:
 *      rtl8367c_getAsicSvlanC2SConf
 * Description:
 *      Get SVLAN C2S table
 * Input:
 *      unit        - Unit ID
 *      index       - index of 128 Svlan C2S configuration
 *      pEvid       - Enhanced VID
 *      pPortmask   - available c2s port mask
 *      pSvidx      - index of 64 Svlan member configuration
 * Output:
 *      None
 * Return:
 *      RT_ERR_OK           - Success
 *      RT_ERR_SMI          - SMI access error
 *      RT_ERR_ENTRY_INDEX  - Invalid entry index
 * Note:
 *      None
 */
ret_t rtl8367c_getAsicSvlanC2SConf(rtksw_uint32 unit, rtksw_uint32 index, rtksw_uint32* pEvid, rtksw_uint32* pPortmask, rtksw_uint32* pSvidx)
{
    ret_t retVal;

    if(index > RTL8367C_C2SIDXMAX)
        return RT_ERR_ENTRY_INDEX;

    retVal = rtl8367c_getAsicReg(unit, RTL8367C_SVLAN_C2SCFG_BASE_REG(index), pSvidx);
    if(retVal != RT_ERR_OK)
        return retVal;

    retVal = rtl8367c_getAsicReg(unit, RTL8367C_SVLAN_C2SCFG_BASE_REG(index) + 1, pPortmask);
    if(retVal != RT_ERR_OK)
        return retVal;

    retVal = rtl8367c_getAsicReg(unit, RTL8367C_SVLAN_C2SCFG_BASE_REG(index) + 2, pEvid);
    if(retVal != RT_ERR_OK)
        return retVal;

    return RT_ERR_OK;
}

/* Function Name:
 *      rtl8367c_setAsicSvlanMC2SConf
 * Description:
 *      Set system MC2S content
 * Input:
 *      unit            - Unit ID
 *      index           - index of 32 SVLAN 32 MC2S configuration
 *      pSvlanMc2sCfg   - SVLAN Multicast to SVLAN member configuration
 * Output:
 *      None
 * Return:
 *      RT_ERR_OK           - Success
 *      RT_ERR_SMI          - SMI access error
 *      RT_ERR_ENTRY_INDEX  - Invalid entry index
 * Note:
 *      If upstream packet is L2 multicast or IPv4 multicast packet and DMAC/DIP is matched MC2S
 *      configuration, ASIC will assign egress SVID to the packet
 */
ret_t rtl8367c_setAsicSvlanMC2SConf(rtksw_uint32 unit, rtksw_uint32 index,rtl8367c_svlan_mc2s_t* pSvlanMc2sCfg)
{
    ret_t retVal;
    rtksw_uint32 regData;
    rtksw_uint16 *accessPtr;
    rtksw_uint32 i;
    rtksw_uint16 smiSvlanMC2S[RTL8367C_SVLAN_MC2S_LEN];

    if(index > RTL8367C_MC2SIDXMAX)
        return RT_ERR_ENTRY_INDEX;

    osal_memset(smiSvlanMC2S, 0x00, sizeof(rtksw_uint16) * RTL8367C_SVLAN_MC2S_LEN);
    _rtl8367c_svlanMc2sStUser2Smi(pSvlanMc2sCfg, smiSvlanMC2S);

    accessPtr = smiSvlanMC2S;

    for(i = 0; i < 5; i++)
    {
        regData = *(accessPtr + i);
        retVal = rtl8367c_setAsicReg(unit, RTL8367C_SVLAN_MCAST2S_ENTRY_BASE_REG(index) + i, regData);
        if(retVal != RT_ERR_OK)
            return retVal;
    }

    return retVal;
}
/* Function Name:
 *      rtl8367c_getAsicSvlanMC2SConf
 * Description:
 *      Get system MC2S content
 * Input:
 *      unit            - Unit ID
 *      index           - index of 32 SVLAN 32 MC2S configuration
 *      pSvlanMc2sCfg   - SVLAN Multicast to SVLAN member configuration
 * Output:
 *      None
 * Return:
 *      RT_ERR_OK           - Success
 *      RT_ERR_SMI          - SMI access error
 *      RT_ERR_ENTRY_INDEX  - Invalid entry index
 * Note:
 *      None
 */
ret_t rtl8367c_getAsicSvlanMC2SConf(rtksw_uint32 unit, rtksw_uint32 index, rtl8367c_svlan_mc2s_t* pSvlanMc2sCfg)
{
    ret_t retVal;
    rtksw_uint32 regData;
    rtksw_uint16 *accessPtr;
    rtksw_uint32 i;
    rtksw_uint16 smiSvlanMC2S[RTL8367C_SVLAN_MC2S_LEN];

    if(index > RTL8367C_MC2SIDXMAX)
        return RT_ERR_ENTRY_INDEX;

    osal_memset(smiSvlanMC2S, 0x00, sizeof(rtksw_uint16) * RTL8367C_SVLAN_MC2S_LEN);

    accessPtr = smiSvlanMC2S;

    for(i = 0; i < 5; i++)
    {
        retVal = rtl8367c_getAsicReg(unit, RTL8367C_SVLAN_MCAST2S_ENTRY_BASE_REG(index) + i, &regData);
        if(retVal != RT_ERR_OK)
            return retVal;

        *accessPtr = regData;
        accessPtr ++;
    }


    _rtl8367c_svlanMc2sStSmi2User(pSvlanMc2sCfg, smiSvlanMC2S);

    return RT_ERR_OK;
}

/* Function Name:
 *      rtl8367c_setAsicSvlanSP2CConf
 * Description:
 *      Set system 128 SP2C content
 * Input:
 *      unit        - Unit ID
 *      index           - index of 128 SVLAN & Port to CVLAN configuration
 *      pSvlanSp2cCfg   - SVLAN & Port to CVLAN configuration
 * Output:
 *      None
 * Return:
 *      RT_ERR_OK           - Success
 *      RT_ERR_SMI          - SMI access error
 *      RT_ERR_ENTRY_INDEX  - Invalid entry index
 * Note:
 *      None
 */
ret_t rtl8367c_setAsicSvlanSP2CConf(rtksw_uint32 unit, rtksw_uint32 index, rtl8367c_svlan_s2c_t* pSvlanSp2cCfg)
{
    ret_t retVal;
    rtksw_uint32 regData;
    rtksw_uint16 *accessPtr;
    rtksw_uint32 i;
    rtksw_uint16 smiSvlanSP2C[RTL8367C_SVLAN_SP2C_LEN];

    if(index > RTL8367C_SP2CMAX)
        return RT_ERR_ENTRY_INDEX;

    osal_memset(smiSvlanSP2C, 0x00, sizeof(rtksw_uint16) * RTL8367C_SVLAN_SP2C_LEN);
    _rtl8367c_svlanSp2cStUser2Smi(pSvlanSp2cCfg,smiSvlanSP2C);

    accessPtr = smiSvlanSP2C;

    for(i = 0; i < 2; i++)
    {
        regData = *(accessPtr + i);
        retVal = rtl8367c_setAsicReg(unit, RTL8367C_SVLAN_S2C_ENTRY_BASE_REG(index) + i, regData);
        if(retVal != RT_ERR_OK)
            return retVal;
    }

    return retVal;
}
/* Function Name:
 *      rtl8367c_getAsicSvlanSP2CConf
 * Description:
 *      Get system 128 SP2C content
 * Input:
 *      unit            - Unit ID
 *      index           - index of 128 SVLAN & Port to CVLAN configuration
 *      pSvlanSp2cCfg   - SVLAN & Port to CVLAN configuration
 * Output:
 *      None
 * Return:
 *      RT_ERR_OK           - Success
 *      RT_ERR_SMI          - SMI access error
 *      RT_ERR_ENTRY_INDEX  - Invalid entry index
 * Note:
 *      None
 */
ret_t rtl8367c_getAsicSvlanSP2CConf(rtksw_uint32 unit, rtksw_uint32 index,rtl8367c_svlan_s2c_t* pSvlanSp2cCfg)
{
    ret_t retVal;
    rtksw_uint32 regData;
    rtksw_uint16 *accessPtr;
    rtksw_uint32 i;
    rtksw_uint16 smiSvlanSP2C[RTL8367C_SVLAN_SP2C_LEN];

    if(index > RTL8367C_SP2CMAX)
        return RT_ERR_ENTRY_INDEX;

    osal_memset(smiSvlanSP2C, 0x00, sizeof(rtksw_uint16) * RTL8367C_SVLAN_SP2C_LEN);

    accessPtr = smiSvlanSP2C;

    for(i = 0; i < 2; i++)
    {
        retVal = rtl8367c_getAsicReg(unit, RTL8367C_SVLAN_S2C_ENTRY_BASE_REG(index) + i, &regData);
        if(retVal != RT_ERR_OK)
            return retVal;

        *accessPtr = regData;

        accessPtr ++;
    }

    _rtl8367c_svlanSp2cStSmi2User(pSvlanSp2cCfg, smiSvlanSP2C);

    return RT_ERR_OK;
}
/* Function Name:
 *      rtl8367c_setAsicSvlanDmacCvidSel
 * Description:
 *      Set downstream CVID decision by DMAC
 * Input:
 *      unit        - Unit ID
 *      port        - Physical port number (0~7)
 *      enabled     - 0:disabled, 1:enabled
 * Output:
 *      None
 * Return:
 *      RT_ERR_OK       - Success
 *      RT_ERR_SMI      - SMI access error
 *      RT_ERR_PORT_ID  - Invalid port number
 * Note:
 *      None
 */
ret_t rtl8367c_setAsicSvlanDmacCvidSel(rtksw_uint32 unit, rtksw_uint32 port, rtksw_uint32 enabled)
{
    if(port > RTL8367C_PORTIDMAX)
        return RT_ERR_PORT_ID;

    if(port < 8)
        return rtl8367c_setAsicRegBit(unit, RTL8367C_REG_SVLAN_CFG, RTL8367C_VS_PORT0_DMACVIDSEL_OFFSET + port, enabled);
    else
        return rtl8367c_setAsicRegBit(unit, RTL8367C_REG_SVLAN_CFG_EXT, RTL8367C_VS_PORT8_DMACVIDSEL_OFFSET + (port-8), enabled);
}
/* Function Name:
 *      rtl8367c_getAsicSvlanDmacCvidSel
 * Description:
 *      Get downstream CVID decision by DMAC
 * Input:
 *      unit        - Unit ID
 *      port        - Physical port number (0~7)
 *      pEnabled    - 0:disabled, 1:enabled
 * Output:
 *      None
 * Return:
 *      RT_ERR_OK       - Success
 *      RT_ERR_SMI      - SMI access error
 *      RT_ERR_PORT_ID  - Invalid port number
 * Note:
 *      None
 */
ret_t rtl8367c_getAsicSvlanDmacCvidSel(rtksw_uint32 unit, rtksw_uint32 port, rtksw_uint32* pEnabled)
{
    if(port > RTL8367C_PORTIDMAX)
        return RT_ERR_PORT_ID;

    if(port < 8)
        return rtl8367c_getAsicRegBit(unit, RTL8367C_REG_SVLAN_CFG, RTL8367C_VS_PORT0_DMACVIDSEL_OFFSET + port, pEnabled);
    else
        return rtl8367c_getAsicRegBit(unit, RTL8367C_REG_SVLAN_CFG_EXT, RTL8367C_VS_PORT8_DMACVIDSEL_OFFSET + (port-8), pEnabled);
}
/* Function Name:
 *      rtl8367c_setAsicSvlanUntagVlan
 * Description:
 *      Set default ingress untag SVLAN
 * Input:
 *      unit        - Unit ID
 *      index       - index SVLAN member configuration
 * Output:
 *      None
 * Return:
 *      RT_ERR_OK                   - Success
 *      RT_ERR_SMI                  - SMI access error
 *      RT_ERR_SVLAN_ENTRY_INDEX    - Invalid SVLAN index parameter
 * Note:
 *      None
 */
ret_t rtl8367c_setAsicSvlanUntagVlan(rtksw_uint32 unit, rtksw_uint32 index)
{
    if(index > RTL8367C_SVIDXMAX)
        return RT_ERR_SVLAN_ENTRY_INDEX;

    return rtl8367c_setAsicRegBits(unit, RTL8367C_REG_SVLAN_UNTAG_UNMAT_CFG, RTL8367C_VS_UNTAG_SVIDX_MASK, index);
}
/* Function Name:
 *      rtl8367c_getAsicSvlanUntagVlan
 * Description:
 *      Get default ingress untag SVLAN
 * Input:
 *      unit        - Unit ID
 *      pIndex      - index SVLAN member configuration
 * Output:
 *      None
 * Return:
 *      RT_ERR_OK       - Success
 *      RT_ERR_SMI      - SMI access error
 * Note:
 *      None
 */
ret_t rtl8367c_getAsicSvlanUntagVlan(rtksw_uint32 unit, rtksw_uint32* pIndex)
{
    return rtl8367c_getAsicRegBits(unit, RTL8367C_REG_SVLAN_UNTAG_UNMAT_CFG, RTL8367C_VS_UNTAG_SVIDX_MASK, pIndex);
}

/* Function Name:
 *      rtl8367c_setAsicSvlanUnmatchVlan
 * Description:
 *      Set default ingress unmatch SVLAN
 * Input:
 *      unit        - Unit ID
 *      index       - index SVLAN member configuration
 * Output:
 *      None
 * Return:
 *      RT_ERR_OK                   - Success
 *      RT_ERR_SMI                  - SMI access error
 *      RT_ERR_SVLAN_ENTRY_INDEX    - Invalid SVLAN index parameter
 * Note:
 *      None
 */
ret_t rtl8367c_setAsicSvlanUnmatchVlan(rtksw_uint32 unit, rtksw_uint32 index)
{
    if(index > RTL8367C_SVIDXMAX)
        return RT_ERR_SVLAN_ENTRY_INDEX;

    return rtl8367c_setAsicRegBits(unit, RTL8367C_REG_SVLAN_UNTAG_UNMAT_CFG, RTL8367C_VS_UNMAT_SVIDX_MASK, index);
}
/* Function Name:
 *      rtl8367c_getAsicSvlanUnmatchVlan
 * Description:
 *      Get default ingress unmatch SVLAN
 * Input:
 *      unit        - Unit ID
 *      pIndex      - index SVLAN member configuration
 * Output:
 *      None
 * Return:
 *      RT_ERR_OK       - Success
 *      RT_ERR_SMI      - SMI access error
 * Note:
 *      None
 */
ret_t rtl8367c_getAsicSvlanUnmatchVlan(rtksw_uint32 unit, rtksw_uint32* pIndex)
{
    return rtl8367c_getAsicRegBits(unit, RTL8367C_REG_SVLAN_UNTAG_UNMAT_CFG, RTL8367C_VS_UNMAT_SVIDX_MASK, pIndex);
}


/* Function Name:
 *      rtl8367c_setAsicSvlanLookupType
 * Description:
 *      Set svlan lookup table selection
 * Input:
 *      unit        - Unit ID
 *      type        - lookup type
 * Output:
 *      None
 * Return:
 *      RT_ERR_OK                   - Success
 *      RT_ERR_SMI                  - SMI access error
 * Note:
 *      None
 */
ret_t rtl8367c_setAsicSvlanLookupType(rtksw_uint32 unit, rtksw_uint32 type)
{
    return rtl8367c_setAsicRegBit(unit, RTL8367C_REG_SVLAN_LOOKUP_TYPE, RTL8367C_SVLAN_LOOKUP_TYPE_OFFSET, type);
}

/* Function Name:
 *      rtl8367c_getAsicSvlanLookupType
 * Description:
 *      Get svlan lookup table selection
 * Input:
 *      unit        - Unit ID
 *      pType       - lookup type
 * Output:
 *      None
 * Return:
 *      RT_ERR_OK                   - Success
 *      RT_ERR_SMI                  - SMI access error
 * Note:
 *      None
 */
ret_t rtl8367c_getAsicSvlanLookupType(rtksw_uint32 unit, rtksw_uint32* pType)
{
    return rtl8367c_getAsicRegBit(unit, RTL8367C_REG_SVLAN_LOOKUP_TYPE, RTL8367C_SVLAN_LOOKUP_TYPE_OFFSET, pType);
}


