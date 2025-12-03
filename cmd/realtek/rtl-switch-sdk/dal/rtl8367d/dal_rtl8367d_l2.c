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
 * Feature : Here is a list of all functions and variables in L2 module.
 *
 */

#include "../../rtk_switch.h"
#include "../../rtk_error.h"
#include "dal_rtl8367d_l2.h"
#include "rtl8367d_asicdrv.h"

#include "../dal_mgmts.h"
#include "../../osal/lib.h"

static void _rtl8367d_fdbStUser2Smi( rtl8367d_luttb *pLutSt, rtksw_uint16 *pFdbSmi)
{
    /* L3 lookup */
    if(pLutSt->l3lookup)
    {
        pFdbSmi[0] = (pLutSt->sip & 0x0000FFFF);

        pFdbSmi[1] = (pLutSt->sip & 0xFFFF0000) >> 16;

        pFdbSmi[2] = (pLutSt->dip & 0x0000FFFF);

        pFdbSmi[3] = (pLutSt->dip & 0x0FFF0000) >> 16;
        pFdbSmi[3] |= (pLutSt->l3lookup & 0x0001) << 12;
        pFdbSmi[3] |= (pLutSt->mbr & 0x0003) << 14;

        pFdbSmi[4] |= (pLutSt->mbr & 0x00FC) >> 2;
        pFdbSmi[4] |= (pLutSt->nosalearn & 0x0001) << 6;
    }
    else if(pLutSt->mac.octet[0] & 0x01) /*Multicast L2 Lookup*/
    {
        pFdbSmi[0] |= pLutSt->mac.octet[5];
        pFdbSmi[0] |= pLutSt->mac.octet[4] << 8;

        pFdbSmi[1] |= pLutSt->mac.octet[3];
        pFdbSmi[1] |= pLutSt->mac.octet[2] << 8;

        pFdbSmi[2] |= pLutSt->mac.octet[1];
        pFdbSmi[2] |= pLutSt->mac.octet[0] << 8;

        pFdbSmi[3] |= pLutSt->cvid_fid;
        pFdbSmi[3] |= (pLutSt->l3lookup & 0x0001) << 12;
        pFdbSmi[3] |= (pLutSt->ivl_svl & 0x0001) << 13;
        pFdbSmi[3] |= (pLutSt->mbr & 0x0003) << 14;

        pFdbSmi[4] |= (pLutSt->mbr & 0x00FC) >> 2;
        pFdbSmi[4] |= (pLutSt->nosalearn & 0x0001) << 6;
    }
    else /*Asic auto-learning*/
    {
        pFdbSmi[0] |= pLutSt->mac.octet[5];
        pFdbSmi[0] |= pLutSt->mac.octet[4] << 8;

        pFdbSmi[1] |= pLutSt->mac.octet[3];
        pFdbSmi[1] |= pLutSt->mac.octet[2] << 8;

        pFdbSmi[2] |= pLutSt->mac.octet[1];
        pFdbSmi[2] |= pLutSt->mac.octet[0] << 8;

        pFdbSmi[3] |= pLutSt->cvid_fid;
        pFdbSmi[3] |= (pLutSt->l3lookup & 0x0001) << 12;
        pFdbSmi[3] |= (pLutSt->ivl_svl & 0x0001) << 13;
        pFdbSmi[3] |= (pLutSt->spa & 0x0003) << 14;

        pFdbSmi[4] |= (pLutSt->spa & 0x0004) >> 2;
        pFdbSmi[4] |= (pLutSt->age & 0x0007) << 1;
        pFdbSmi[4] |= (pLutSt->nosalearn & 0x0001) << 6;
    }
}


static void _rtl8367d_fdbStSmi2User( rtl8367d_luttb *pLutSt, rtksw_uint16 *pFdbSmi)
{
    /*L3 lookup*/
    if(pFdbSmi[3] & 0x1000)
    {
        pLutSt->sip             = pFdbSmi[0] | (pFdbSmi[1] << 16);
        pLutSt->dip             = 0xE0000000 | pFdbSmi[2] | ((pFdbSmi[3] & 0x0FFF) << 16);
        pLutSt->mbr             = ((pFdbSmi[4] & 0x003F) << 2) | ((pFdbSmi[3] & 0xC000) >> 14);
        pLutSt->l3lookup        = (pFdbSmi[3] & 0x1000) >> 12;
        pLutSt->nosalearn       = (pFdbSmi[4] & 0x0040) >> 6;
    }
    else if(pFdbSmi[2] & 0x0100) /*Multicast L2 Lookup*/
    {
        pLutSt->mac.octet[0]    = (pFdbSmi[2] & 0xFF00) >> 8;
        pLutSt->mac.octet[1]    = (pFdbSmi[2] & 0x00FF);
        pLutSt->mac.octet[2]    = (pFdbSmi[1] & 0xFF00) >> 8;
        pLutSt->mac.octet[3]    = (pFdbSmi[1] & 0x00FF);
        pLutSt->mac.octet[4]    = (pFdbSmi[0] & 0xFF00) >> 8;
        pLutSt->mac.octet[5]    = (pFdbSmi[0] & 0x00FF);

        pLutSt->cvid_fid        = pFdbSmi[3] & 0x0FFF;
        pLutSt->mbr             = ((pFdbSmi[4] & 0x003F) << 2) | ((pFdbSmi[3] & 0xC000) >> 14);

        pLutSt->l3lookup        = (pFdbSmi[3] & 0x1000) >> 12;
        pLutSt->ivl_svl         = (pFdbSmi[3] & 0x2000) >> 13;
        pLutSt->nosalearn       = (pFdbSmi[4] & 0x0040) >> 6;
    }
    else /*Asic auto-learning*/
    {
        pLutSt->mac.octet[0]    = (pFdbSmi[2] & 0xFF00) >> 8;
        pLutSt->mac.octet[1]    = (pFdbSmi[2] & 0x00FF);
        pLutSt->mac.octet[2]    = (pFdbSmi[1] & 0xFF00) >> 8;
        pLutSt->mac.octet[3]    = (pFdbSmi[1] & 0x00FF);
        pLutSt->mac.octet[4]    = (pFdbSmi[0] & 0xFF00) >> 8;
        pLutSt->mac.octet[5]    = (pFdbSmi[0] & 0x00FF);

        pLutSt->cvid_fid        = pFdbSmi[3] & 0x0FFF;

        pLutSt->spa             = ((pFdbSmi[4] & 0x0001) << 2) | ((pFdbSmi[3] & 0xC000) >> 14);
        pLutSt->age             = (pFdbSmi[4] & 0x000E) >> 1;

        pLutSt->l3lookup        = (pFdbSmi[3] & 0x1000) >> 12;
        pLutSt->ivl_svl         = (pFdbSmi[3] & 0x2000) >> 13;
        pLutSt->nosalearn       = (pFdbSmi[4] & 0x0040) >> 6;
    }
}


static rtksw_api_ret_t _rtl8367d_getL2LookupTb(rtksw_uint32 unit, rtksw_uint32 method, rtl8367d_luttb *pL2Table)
{
    ret_t retVal;
    rtksw_uint32 regData;
    rtksw_uint16* accessPtr;
    rtksw_uint32 i;
    rtksw_uint16 smil2Table[RTL8367D_LUT_TABLE_SIZE];
    rtksw_uint32 busyCounter;
    rtksw_uint32 tblCmd;

    if(pL2Table->wait_time == 0)
        busyCounter = RTL8367D_LUT_BUSY_CHECK_NO;
    else
        busyCounter = pL2Table->wait_time;

    while(busyCounter)
    {
        retVal = rtl8367d_getAsicRegBit(unit, RTL8367D_REG_TABLE_LUT_ADDR, RTL8367D_TABLE_LUT_ADDR_BUSY_FLAG_OFFSET,&regData);
        if(retVal != RT_ERR_OK)
            return retVal;

        pL2Table->lookup_busy = regData;
        if(!pL2Table->lookup_busy)
            break;

        busyCounter --;
        if(busyCounter == 0)
            return RT_ERR_BUSYWAIT_TIMEOUT;
    }


    tblCmd = (method << RTL8367D_ACCESS_METHOD_OFFSET) & RTL8367D_ACCESS_METHOD_MASK;

    switch(method)
    {
        case RTL8367D_LUTREADMETHOD_ADDRESS:
        case RTL8367D_LUTREADMETHOD_NEXT_ADDRESS:
        case RTL8367D_LUTREADMETHOD_NEXT_L2UC:
        case RTL8367D_LUTREADMETHOD_NEXT_L2MC:
        case RTL8367D_LUTREADMETHOD_NEXT_L3MC:
        case RTL8367D_LUTREADMETHOD_NEXT_L2L3MC:
            retVal = rtl8367d_setAsicReg(unit, RTL8367D_REG_TABLE_ACCESS_ADDR, pL2Table->address);
            if(retVal != RT_ERR_OK)
                return retVal;
            break;
        case RTL8367D_LUTREADMETHOD_MAC:
            osal_memset(smil2Table, 0x00, sizeof(rtksw_uint16) * RTL8367D_LUT_TABLE_SIZE);
            _rtl8367d_fdbStUser2Smi(pL2Table, smil2Table);

            accessPtr = smil2Table;
            regData = *accessPtr;
            for(i=0; i<RTL8367D_LUT_TABLE_SIZE; i++)
            {
                retVal = rtl8367d_setAsicReg(unit, RTL8367D_REG_TABLE_WRITE_DATA0 + i, regData);
                if(retVal != RT_ERR_OK)
                    return retVal;

                accessPtr ++;
                regData = *accessPtr;

            }
            break;
        case RTL8367D_LUTREADMETHOD_NEXT_L2UCSPA:
            retVal = rtl8367d_setAsicReg(unit, RTL8367D_REG_TABLE_ACCESS_ADDR, pL2Table->address);
            if(retVal != RT_ERR_OK)
                return retVal;

            tblCmd = tblCmd | ((pL2Table->spa << RTL8367D_TABLE_ACCESS_CTRL_SPA_OFFSET) & RTL8367D_TABLE_ACCESS_CTRL_SPA_MASK);

            break;
        default:
            return RT_ERR_INPUT;
    }

    tblCmd = tblCmd | ((RTL8367D_TABLE_ACCESS_REG_DATA(RTL8367D_TB_OP_READ,RTL8367D_TB_TARGET_L2)) & (RTL8367D_TABLE_TYPE_MASK  | RTL8367D_COMMAND_TYPE_MASK));
    /* Read Command */
    retVal = rtl8367d_setAsicReg(unit, RTL8367D_REG_TABLE_ACCESS_CTRL, tblCmd);
    if(retVal != RT_ERR_OK)
        return retVal;

    if(pL2Table->wait_time == 0)
        busyCounter = RTL8367D_LUT_BUSY_CHECK_NO;
    else
        busyCounter = pL2Table->wait_time;

    while(busyCounter)
    {
        retVal = rtl8367d_getAsicRegBit(unit, RTL8367D_REG_TABLE_LUT_ADDR, RTL8367D_TABLE_LUT_ADDR_BUSY_FLAG_OFFSET,&regData);
        if(retVal != RT_ERR_OK)
            return retVal;

        pL2Table->lookup_busy = regData;
        if(!pL2Table->lookup_busy)
            break;

        busyCounter --;
        if(busyCounter == 0)
            return RT_ERR_BUSYWAIT_TIMEOUT;
    }

    retVal = rtl8367d_getAsicRegBit(unit, RTL8367D_REG_TABLE_LUT_ADDR, RTL8367D_HIT_STATUS_OFFSET,&regData);
    if(retVal != RT_ERR_OK)
            return retVal;
    pL2Table->lookup_hit = regData;
    if(!pL2Table->lookup_hit)
        return RT_ERR_L2_ENTRY_NOTFOUND;

    /*Read access address*/
    retVal = rtl8367d_getAsicReg(unit, RTL8367D_REG_TABLE_LUT_ADDR, &regData);
    if(retVal != RT_ERR_OK)
        return retVal;

    pL2Table->address = (regData & 0xfff);

    /*read L2 entry */
    osal_memset(smil2Table, 0x00, sizeof(rtksw_uint16) * RTL8367D_LUT_TABLE_SIZE);

    accessPtr = smil2Table;

    for(i = 0; i < RTL8367D_LUT_TABLE_SIZE; i++)
    {
        retVal = rtl8367d_getAsicReg(unit, RTL8367D_REG_TABLE_READ_DATA0 + i, &regData);
        if(retVal != RT_ERR_OK)
            return retVal;

        *accessPtr = regData;

        accessPtr ++;
    }

    _rtl8367d_fdbStSmi2User(pL2Table, smil2Table);

    return RT_ERR_OK;
}

static rtksw_api_ret_t _rtl8367d_setL2LookupTb(rtksw_uint32 unit, rtl8367d_luttb *pL2Table)
{
    ret_t retVal;
    rtksw_uint32 regData;
    rtksw_uint16 *accessPtr;
    rtksw_uint32 i;
    rtksw_uint16 smil2Table[RTL8367D_LUT_TABLE_SIZE];
    rtksw_uint32 tblCmd;
    rtksw_uint32 busyCounter;

    osal_memset(smil2Table, 0x00, sizeof(rtksw_uint16) * RTL8367D_LUT_TABLE_SIZE);
    _rtl8367d_fdbStUser2Smi(pL2Table, smil2Table);

    if(pL2Table->wait_time == 0)
        busyCounter = RTL8367D_LUT_BUSY_CHECK_NO;
    else
        busyCounter = pL2Table->wait_time;

    while(busyCounter)
    {
        retVal = rtl8367d_getAsicRegBit(unit, RTL8367D_REG_TABLE_LUT_ADDR, RTL8367D_TABLE_LUT_ADDR_BUSY_FLAG_OFFSET,&regData);
        if(retVal != RT_ERR_OK)
            return retVal;

        pL2Table->lookup_busy = regData;
        if(!regData)
            break;

        busyCounter --;
        if(busyCounter == 0)
            return RT_ERR_BUSYWAIT_TIMEOUT;
    }

    accessPtr = smil2Table;

    for(i = 0; i < RTL8367D_LUT_TABLE_SIZE; i++)
    {
        regData = *(accessPtr + i);
        retVal = rtl8367d_setAsicReg(unit, RTL8367D_REG_TABLE_WRITE_DATA0 + i, regData);
        if(retVal != RT_ERR_OK)
            return retVal;
    }

    tblCmd = (RTL8367D_TABLE_ACCESS_REG_DATA(RTL8367D_TB_OP_WRITE,RTL8367D_TB_TARGET_L2)) & (RTL8367D_TABLE_TYPE_MASK  | RTL8367D_COMMAND_TYPE_MASK);
    /* Write Command */
    retVal = rtl8367d_setAsicReg(unit, RTL8367D_REG_TABLE_ACCESS_CTRL, tblCmd);
    if(retVal != RT_ERR_OK)
        return retVal;

    if(pL2Table->wait_time == 0)
        busyCounter = RTL8367D_LUT_BUSY_CHECK_NO;
    else
        busyCounter = pL2Table->wait_time;

    while(busyCounter)
    {
        retVal = rtl8367d_getAsicRegBit(unit, RTL8367D_REG_TABLE_LUT_ADDR, RTL8367D_TABLE_LUT_ADDR_BUSY_FLAG_OFFSET,&regData);
        if(retVal != RT_ERR_OK)
            return retVal;

        pL2Table->lookup_busy = regData;
        if(!regData)
            break;

        busyCounter --;
        if(busyCounter == 0)
            return RT_ERR_BUSYWAIT_TIMEOUT;
    }

    /*Read access status*/
    retVal = rtl8367d_getAsicRegBit(unit, RTL8367D_REG_TABLE_LUT_ADDR, RTL8367D_HIT_STATUS_OFFSET, &regData);
    if(retVal != RT_ERR_OK)
        return retVal;

    pL2Table->lookup_hit = regData;
    if(!pL2Table->lookup_hit)
        return RT_ERR_FAILED;

    /*Read access address*/
    retVal = rtl8367d_getAsicReg(unit, RTL8367D_REG_TABLE_LUT_ADDR, &regData);
    if(retVal != RT_ERR_OK)
        return retVal;

    pL2Table->address = (regData & 0xfff);
    pL2Table->lookup_busy = 0;

    return RT_ERR_OK;
}

static rtksw_api_ret_t _rtl8367d_getLutIPMCGroup(rtksw_uint32 unit, rtksw_uint32 index, ipaddr_t *pGroup_addr, rtksw_uint32 *pPmask, rtksw_uint32 *pValid)
{
    rtksw_uint32      regAddr, regData, bitoffset;
    ipaddr_t    ipData;
    ret_t       retVal;

    if(index > RTL8367D_LUT_IPMCGRP_TABLE_MAX)
        return RT_ERR_INPUT;

    if (NULL == pGroup_addr)
        return RT_ERR_NULL_POINTER;

    if (NULL == pPmask)
        return RT_ERR_NULL_POINTER;

    /* Group address */
    regAddr = RTL8367D_REG_IPMC_GROUP_ENTRY0_H + (index * 2);
    if( (retVal = rtl8367d_getAsicReg(unit, regAddr, &regData)) != RT_ERR_OK)
        return retVal;

    *pGroup_addr = (((regData & 0x00000FFF) << 16) | 0xE0000000);

    regAddr++;
    if( (retVal = rtl8367d_getAsicReg(unit, regAddr, &regData)) != RT_ERR_OK)
        return retVal;

    ipData = (*pGroup_addr | (regData & 0x0000FFFF));
    *pGroup_addr = ipData;

    /* portmask */
    regAddr = RTL8367D_REG_IPMC_GROUP_PMSK_00 + index;
    if( (retVal = rtl8367d_getAsicReg(unit, regAddr, &regData)) != RT_ERR_OK)
        return retVal;

    *pPmask = regData;

    /* valid */
    regAddr = RTL8367D_REG_IPMC_GROUP_VALID_15_0 + (index / 16);
    bitoffset = index % 16;
    if( (retVal = rtl8367d_getAsicRegBit(unit, regAddr, bitoffset, &regData)) != RT_ERR_OK)
        return retVal;

    *pValid = regData;

    return RT_ERR_OK;
}

static rtksw_api_ret_t _rtl8367d_setLutIPMCGroup(rtksw_uint32 unit, rtksw_uint32 index, ipaddr_t group_addr, rtksw_uint32 pmask, rtksw_uint32 valid)
{
    rtksw_uint32  regAddr, regData, bitoffset;
    ipaddr_t    ipData;
    ret_t       retVal;

    if(index > RTL8367D_LUT_IPMCGRP_TABLE_MAX)
        return RT_ERR_INPUT;

    ipData = group_addr;

    if( (ipData & 0xF0000000) != 0xE0000000)    /* not in 224.0.0.0 ~ 239.255.255.255 */
        return RT_ERR_INPUT;

    /* Group Address */
    regAddr = RTL8367D_REG_IPMC_GROUP_ENTRY0_H + (index * 2);
    regData = ((ipData & 0x0FFFFFFF) >> 16);

    if( (retVal = rtl8367d_setAsicReg(unit, regAddr, regData)) != RT_ERR_OK)
        return retVal;

    regAddr++;
    regData = (ipData & 0x0000FFFF);

    if( (retVal = rtl8367d_setAsicReg(unit, regAddr, regData)) != RT_ERR_OK)
        return retVal;

    /* portmask */
    regAddr = RTL8367D_REG_IPMC_GROUP_PMSK_00 + index;
    regData = pmask;

    if( (retVal = rtl8367d_setAsicReg(unit, regAddr, regData)) != RT_ERR_OK)
        return retVal;

    /* valid */
    regAddr = RTL8367D_REG_IPMC_GROUP_VALID_15_0 + (index / 16);
    bitoffset = index % 16;
    if( (retVal = rtl8367d_setAsicRegBit(unit, regAddr, bitoffset, valid)) != RT_ERR_OK)
        return retVal;

    return RT_ERR_OK;
}


/* Function Name:
 *      dal_rtl8367d_l2_init
 * Description:
 *      Initialize l2 module of the specified device.
 * Input:
 *      unit    - Unit ID
 * Output:
 *      None
 * Return:
 *      RT_ERR_OK          - OK
 *      RT_ERR_FAILED      - Failed
 *      RT_ERR_SMI         - SMI access error
 * Note:
 *      Initialize l2 module before calling any l2 APIs.
 */
rtksw_api_ret_t dal_rtl8367d_l2_init(rtksw_uint32 unit)
{
    rtksw_api_ret_t retVal;
    rtksw_uint32 port;

    /* Check initialization state */
    RTKSW_CHK_INIT_STATE(unit);

    if ((retVal = rtl8367d_setAsicRegBit(unit, RTL8367D_REG_LUT_CFG, RTL8367D_LUT_IPMC_HASH_OFFSET, RTKSW_DISABLED)) != RT_ERR_OK)
        return retVal;

    /*Enable CAM Usage*/
    if ((retVal = rtl8367d_setAsicRegBit(unit, RTL8367D_REG_LUT_CFG, RTL8367D_BCAM_DISABLE_OFFSET, RTKSW_ENABLED ? 0 : 1)) != RT_ERR_OK)
        return retVal;

    if ((retVal = rtl8367d_setAsicReg(unit, RTL8367D_REG_LUT_CFG2, 3000)) != RT_ERR_OK)
        return retVal;

    RTKSW_SCAN_ALL_LOG_PORT(unit, port)
    {
        if ((retVal = rtl8367d_setAsicReg(unit, RTL8367D_REG_LUT_PORT0_LEARN_LIMITNO + rtksw_switch_port_L2P_get(unit, port), rtksw_switch_maxLutAddrNumber_get(unit))) != RT_ERR_OK)
            return retVal;
    }

    return RT_ERR_OK;
}

/* Function Name:
 *      dal_rtl8367d_l2_addr_add
 * Description:
 *      Add LUT unicast entry.
 * Input:
 *      unit        - Unit ID
 *      pMac        - 6 bytes unicast(I/G bit is 0) mac address to be written into LUT.
 *      pL2_data    - Unicast entry parameter
 * Output:
 *      None
 * Return:
 *      RT_ERR_OK               - OK
 *      RT_ERR_FAILED           - Failed
 *      RT_ERR_SMI              - SMI access error
 *      RT_ERR_PORT_ID          - Invalid port number.
 *      RT_ERR_MAC              - Invalid MAC address.
 *      RT_ERR_L2_FID           - Invalid FID .
 *      RT_ERR_L2_INDEXTBL_FULL - hashed index is full of entries.
 *      RT_ERR_INPUT            - Invalid input parameters.
 * Note:
 *      If the unicast mac address already existed in LUT, it will udpate the status of the entry.
 *      Otherwise, it will find an empty or asic auto learned entry to write. If all the entries
 *      with the same hash value can't be replaced, ASIC will return a RT_ERR_L2_INDEXTBL_FULL error.
 */
rtksw_api_ret_t dal_rtl8367d_l2_addr_add(rtksw_uint32 unit, rtksw_mac_t *pMac, rtksw_l2_ucastAddr_t *pL2_data)
{
    rtksw_api_ret_t retVal;
    rtksw_uint32 method;
    rtl8367d_luttb l2Table;

    /* Check initialization state */
    RTKSW_CHK_INIT_STATE(unit);

    /* must be unicast address */
    if ((pMac == NULL) || (pMac->octet[0] & 0x1))
        return RT_ERR_MAC;

    if(pL2_data == NULL)
        return RT_ERR_MAC;

    RTKSW_CHK_PORT_VALID(unit, pL2_data->port);

    if (pL2_data->ivl >= RTKSW_ENABLE_END)
        return RT_ERR_INPUT;

    if (pL2_data->cvid > RTL8367D_VIDMAX)
        return RT_ERR_L2_VID;

    if (pL2_data->fid > RTL8367D_FIDMAX)
        return RT_ERR_L2_FID;

    if (pL2_data->is_static>= RTKSW_ENABLE_END)
        return RT_ERR_INPUT;

    osal_memset(&l2Table, 0, sizeof(rtl8367d_luttb));

    /* fill key (MAC,FID) to get L2 entry */
    osal_memcpy(l2Table.mac.octet, pMac->octet, ETHER_ADDR_LEN);
    l2Table.ivl_svl     = pL2_data->ivl;
    l2Table.cvid_fid    = (pL2_data->ivl ? pL2_data->cvid : pL2_data->fid);
    method = RTL8367D_LUTREADMETHOD_MAC;
    retVal = _rtl8367d_getL2LookupTb(unit, method, &l2Table);
    if (RT_ERR_OK == retVal )
    {
        osal_memcpy(l2Table.mac.octet, pMac->octet, ETHER_ADDR_LEN);
        l2Table.ivl_svl     = pL2_data->ivl;
        l2Table.cvid_fid    = (pL2_data->ivl ? pL2_data->cvid : pL2_data->fid);
        l2Table.spa         = rtksw_switch_port_L2P_get(unit, pL2_data->port);
        l2Table.nosalearn   = pL2_data->is_static;
        l2Table.l3lookup    = 0;
        l2Table.age         = 6;
        if((retVal = _rtl8367d_setL2LookupTb(unit, &l2Table)) != RT_ERR_OK)
            return retVal;

        pL2_data->address = l2Table.address;
        return RT_ERR_OK;
    }
    else if (RT_ERR_L2_ENTRY_NOTFOUND == retVal )
    {
        osal_memset(&l2Table, 0, sizeof(rtl8367d_luttb));
        osal_memcpy(l2Table.mac.octet, pMac->octet, ETHER_ADDR_LEN);
        l2Table.ivl_svl     = pL2_data->ivl;
        l2Table.cvid_fid    = (pL2_data->ivl ? pL2_data->cvid : pL2_data->fid);
        l2Table.spa         = rtksw_switch_port_L2P_get(unit, pL2_data->port);
        l2Table.nosalearn   = pL2_data->is_static;
        l2Table.l3lookup    = 0;
        l2Table.age         = 6;

        if ((retVal = _rtl8367d_setL2LookupTb(unit, &l2Table)) != RT_ERR_OK)
            return retVal;

        pL2_data->address = l2Table.address;

        method = RTL8367D_LUTREADMETHOD_MAC;
        retVal = _rtl8367d_getL2LookupTb(unit, method, &l2Table);
        if (RT_ERR_L2_ENTRY_NOTFOUND == retVal )
            return RT_ERR_L2_INDEXTBL_FULL;
        else
            return retVal;
    }
    else
        return retVal;

}

/* Function Name:
 *      dal_rtl8367d_l2_addr_get
 * Description:
 *      Get LUT unicast entry.
 * Input:
 *      unit    - Unit ID
 *      pMac    - 6 bytes unicast(I/G bit is 0) mac address to be written into LUT.
 * Output:
 *      pL2_data - Unicast entry parameter
 * Return:
 *      RT_ERR_OK                   - OK
 *      RT_ERR_FAILED               - Failed
 *      RT_ERR_SMI                  - SMI access error
 *      RT_ERR_PORT_ID              - Invalid port number.
 *      RT_ERR_MAC                  - Invalid MAC address.
 *      RT_ERR_L2_FID               - Invalid FID .
 *      RT_ERR_L2_ENTRY_NOTFOUND    - No such LUT entry.
 *      RT_ERR_INPUT                - Invalid input parameters.
 * Note:
 *      If the unicast mac address existed in LUT, it will return the port and fid where
 *      the mac is learned. Otherwise, it will return a RT_ERR_L2_ENTRY_NOTFOUND error.
 */
rtksw_api_ret_t dal_rtl8367d_l2_addr_get(rtksw_uint32 unit, rtksw_mac_t *pMac, rtksw_l2_ucastAddr_t *pL2_data)
{
    rtksw_api_ret_t retVal;
    rtksw_uint32 method;
    rtl8367d_luttb l2Table;

    /* Check initialization state */
    RTKSW_CHK_INIT_STATE(unit);

    /* must be unicast address */
    if ((pMac == NULL) || (pMac->octet[0] & 0x1))
        return RT_ERR_MAC;

    if (pL2_data->ivl >= RTKSW_ENABLE_END)
        return RT_ERR_INPUT;

    if (pL2_data->ivl == 1)
    {
        if (pL2_data->cvid > RTL8367D_VIDMAX)
            return RT_ERR_L2_VID;
    }
    else
    {
        if (pL2_data->fid > RTL8367D_FIDMAX)
            return RT_ERR_L2_FID;
    }

    osal_memset(&l2Table, 0, sizeof(rtl8367d_luttb));

    osal_memcpy(l2Table.mac.octet, pMac->octet, ETHER_ADDR_LEN);
    l2Table.ivl_svl     = pL2_data->ivl;
    l2Table.cvid_fid    = (pL2_data->ivl ? pL2_data->cvid : pL2_data->fid);
    method = RTL8367D_LUTREADMETHOD_MAC;

    if ((retVal = _rtl8367d_getL2LookupTb(unit, method, &l2Table)) != RT_ERR_OK)
        return retVal;

    osal_memcpy(pL2_data->mac.octet, pMac->octet,ETHER_ADDR_LEN);
    pL2_data->port      = rtksw_switch_port_P2L_get(unit, l2Table.spa);
    pL2_data->ivl       = l2Table.ivl_svl;

    if (pL2_data->ivl == 1)
        pL2_data->cvid      = l2Table.cvid_fid;
    else
        pL2_data->fid       = l2Table.cvid_fid;

    pL2_data->is_static = l2Table.nosalearn;
    pL2_data->address   = l2Table.address;

    return RT_ERR_OK;
}

/* Function Name:
 *      dal_rtl8367d_l2_addr_next_get
 * Description:
 *      Get Next LUT unicast entry.
 * Input:
 *      unit            - Unit ID
 *      read_method     - The reading method.
 *      port            - The port number if the read_metohd is READMETHOD_NEXT_L2UCSPA
 *      pAddress        - The Address ID
 * Output:
 *      pL2_data - Unicast entry parameter
 * Return:
 *      RT_ERR_OK                   - OK
 *      RT_ERR_FAILED               - Failed
 *      RT_ERR_SMI                  - SMI access error
 *      RT_ERR_PORT_ID              - Invalid port number.
 *      RT_ERR_MAC                  - Invalid MAC address.
 *      RT_ERR_L2_FID               - Invalid FID .
 *      RT_ERR_L2_ENTRY_NOTFOUND    - No such LUT entry.
 *      RT_ERR_INPUT                - Invalid input parameters.
 * Note:
 *      Get the next unicast entry after the current entry pointed by pAddress.
 *      The address of next entry is returned by pAddress. User can use (address + 1)
 *      as pAddress to call this API again for dumping all entries is LUT.
 */
rtksw_api_ret_t dal_rtl8367d_l2_addr_next_get(rtksw_uint32 unit, rtksw_l2_read_method_t read_method, rtksw_port_t port, rtksw_uint32 *pAddress, rtksw_l2_ucastAddr_t *pL2_data)
{
    rtksw_api_ret_t   retVal;
    rtksw_uint32      method;
    rtl8367d_luttb  l2Table;

    /* Check initialization state */
    RTKSW_CHK_INIT_STATE(unit);

    /* Error Checking */
    if ((pL2_data == NULL) || (pAddress == NULL))
        return RT_ERR_MAC;

    if(read_method == READMETHOD_NEXT_L2UC)
        method = RTL8367D_LUTREADMETHOD_NEXT_L2UC;
    else if(read_method == READMETHOD_NEXT_L2UCSPA)
        method = RTL8367D_LUTREADMETHOD_NEXT_L2UCSPA;
    else
        return RT_ERR_INPUT;

    if(read_method == READMETHOD_NEXT_L2UCSPA)
    {
        /* Check Port Valid */
        RTKSW_CHK_PORT_VALID(unit, port);
    }

    if(*pAddress > RTKSW_MAX_LUT_ADDR_ID )
        return RT_ERR_L2_L2UNI_PARAM;

    osal_memset(pL2_data, 0, sizeof(rtksw_l2_ucastAddr_t));
    osal_memset(&l2Table, 0, sizeof(rtl8367d_luttb));
    l2Table.address = *pAddress;

    if(read_method == READMETHOD_NEXT_L2UCSPA)
        l2Table.spa = rtksw_switch_port_L2P_get(unit, port);

    if ((retVal = _rtl8367d_getL2LookupTb(unit, method, &l2Table)) != RT_ERR_OK)
        return retVal;

    if(l2Table.address < *pAddress)
        return RT_ERR_L2_ENTRY_NOTFOUND;

    osal_memcpy(pL2_data->mac.octet, l2Table.mac.octet, ETHER_ADDR_LEN);
    pL2_data->port      = rtksw_switch_port_P2L_get(unit, l2Table.spa);
    pL2_data->ivl       = l2Table.ivl_svl;

    if (pL2_data->ivl == 1)
        pL2_data->cvid      = l2Table.cvid_fid;
    else
        pL2_data->fid       = l2Table.cvid_fid;

    pL2_data->is_static = l2Table.nosalearn;
    pL2_data->address   = l2Table.address;

    *pAddress = l2Table.address;

    return RT_ERR_OK;

}

/* Function Name:
 *      dal_rtl8367d_l2_addr_del
 * Description:
 *      Delete LUT unicast entry.
 * Input:
 *      unit    - Unit ID
 *      pMac    - 6 bytes unicast(I/G bit is 0) mac address to be written into LUT.
 *      fid     - Filtering database
 * Output:
 *      None
 * Return:
 *      RT_ERR_OK                   - OK
 *      RT_ERR_FAILED               - Failed
 *      RT_ERR_SMI                  - SMI access error
 *      RT_ERR_PORT_ID              - Invalid port number.
 *      RT_ERR_MAC                  - Invalid MAC address.
 *      RT_ERR_L2_FID               - Invalid FID .
 *      RT_ERR_L2_ENTRY_NOTFOUND    - No such LUT entry.
 *      RT_ERR_INPUT                - Invalid input parameters.
 * Note:
 *      If the mac has existed in the LUT, it will be deleted. Otherwise, it will return RT_ERR_L2_ENTRY_NOTFOUND.
 */
rtksw_api_ret_t dal_rtl8367d_l2_addr_del(rtksw_uint32 unit, rtksw_mac_t *pMac, rtksw_l2_ucastAddr_t *pL2_data)
{
    rtksw_api_ret_t retVal;
    rtksw_uint32 method;
    rtl8367d_luttb l2Table;

    /* Check initialization state */
    RTKSW_CHK_INIT_STATE(unit);

    /* must be unicast address */
    if ((pMac == NULL) || (pMac->octet[0] & 0x1))
        return RT_ERR_MAC;

    if (pL2_data->ivl >= RTKSW_ENABLE_END)
        return RT_ERR_INPUT;

    if (pL2_data->ivl == 1)
    {
        if (pL2_data->cvid > RTL8367D_VIDMAX)
            return RT_ERR_L2_VID;
    }
    else
    {
        if (pL2_data->fid > RTL8367D_FIDMAX)
            return RT_ERR_L2_FID;
    }

    osal_memset(&l2Table, 0, sizeof(rtl8367d_luttb));

    /* fill key (MAC,FID) to get L2 entry */
    osal_memcpy(l2Table.mac.octet, pMac->octet, ETHER_ADDR_LEN);
    l2Table.ivl_svl     = pL2_data->ivl;
    l2Table.cvid_fid    = (pL2_data->ivl ? pL2_data->cvid : pL2_data->fid);
    method = RTL8367D_LUTREADMETHOD_MAC;
    retVal = _rtl8367d_getL2LookupTb(unit, method, &l2Table);
    if (RT_ERR_OK ==  retVal)
    {
        osal_memcpy(l2Table.mac.octet, pMac->octet, ETHER_ADDR_LEN);
        l2Table.ivl_svl     = pL2_data->ivl;
        l2Table.cvid_fid    = (pL2_data->ivl ? pL2_data->cvid : pL2_data->fid);
        l2Table.spa         = 0;
        l2Table.nosalearn   = 0;
        l2Table.age         = 0;
        if((retVal = _rtl8367d_setL2LookupTb(unit, &l2Table)) != RT_ERR_OK)
            return retVal;

        pL2_data->address = l2Table.address;
        return RT_ERR_OK;
    }
    else
        return retVal;
}

/* Function Name:
 *      dal_rtl8367d_l2_mcastAddr_add
 * Description:
 *      Add LUT multicast entry.
 * Input:
 *      unit        - Unit ID
 *      pMcastAddr  - L2 multicast entry structure
 * Output:
 *      None
 * Return:
 *      RT_ERR_OK               - OK
 *      RT_ERR_FAILED           - Failed
 *      RT_ERR_SMI              - SMI access error
 *      RT_ERR_PORT_ID          - Invalid port number.
 *      RT_ERR_MAC              - Invalid MAC address.
 *      RT_ERR_L2_FID           - Invalid FID .
 *      RT_ERR_L2_VID           - Invalid VID .
 *      RT_ERR_L2_INDEXTBL_FULL - hashed index is full of entries.
 *      RT_ERR_PORT_MASK        - Invalid portmask.
 *      RT_ERR_INPUT            - Invalid input parameters.
 * Note:
 *      If the multicast mac address already existed in the LUT, it will udpate the
 *      port mask of the entry. Otherwise, it will find an empty or asic auto learned
 *      entry to write. If all the entries with the same hash value can't be replaced,
 *      ASIC will return a RT_ERR_L2_INDEXTBL_FULL error.
 */
rtksw_api_ret_t dal_rtl8367d_l2_mcastAddr_add(rtksw_uint32 unit, rtksw_l2_mcastAddr_t *pMcastAddr)
{
    rtksw_api_ret_t   retVal;
    rtksw_uint32      method;
    rtl8367d_luttb  l2Table;
    rtksw_uint32      pmask;

    /* Check initialization state */
    RTKSW_CHK_INIT_STATE(unit);

    if(NULL == pMcastAddr)
        return RT_ERR_NULL_POINTER;

    /* must be L2 multicast address */
    if( (pMcastAddr->mac.octet[0] & 0x01) != 0x01)
        return RT_ERR_MAC;

    RTKSW_CHK_PORTMASK_VALID(unit, &pMcastAddr->portmask);

    if(pMcastAddr->ivl == 1)
    {
        if (pMcastAddr->vid > RTL8367D_VIDMAX)
            return RT_ERR_L2_VID;
    }
    else if(pMcastAddr->ivl == 0)
    {
        if (pMcastAddr->fid > RTL8367D_FIDMAX)
            return RT_ERR_L2_FID;
    }
    else
        return RT_ERR_INPUT;

    /* Get physical port mask */
    if ((retVal = rtksw_switch_portmask_L2P_get(unit, &pMcastAddr->portmask, &pmask)) != RT_ERR_OK)
        return retVal;

    osal_memset(&l2Table, 0, sizeof(rtl8367d_luttb));

    /* fill key (MAC,FID) to get L2 entry */
    osal_memcpy(l2Table.mac.octet, pMcastAddr->mac.octet, ETHER_ADDR_LEN);
    l2Table.ivl_svl     = pMcastAddr->ivl;

    if(pMcastAddr->ivl)
        l2Table.cvid_fid    = pMcastAddr->vid;
    else
        l2Table.cvid_fid    = pMcastAddr->fid;

    method = RTL8367D_LUTREADMETHOD_MAC;
    retVal = _rtl8367d_getL2LookupTb(unit, method, &l2Table);
    if (RT_ERR_OK == retVal)
    {
        osal_memcpy(l2Table.mac.octet, pMcastAddr->mac.octet, ETHER_ADDR_LEN);
        l2Table.ivl_svl     = pMcastAddr->ivl;

        if(pMcastAddr->ivl)
            l2Table.cvid_fid    = pMcastAddr->vid;
        else
            l2Table.cvid_fid    = pMcastAddr->fid;

        l2Table.mbr         = pmask;
        l2Table.nosalearn   = 1;
        l2Table.l3lookup    = 0;
        if((retVal = _rtl8367d_setL2LookupTb(unit, &l2Table)) != RT_ERR_OK)
            return retVal;

        pMcastAddr->address = l2Table.address;
        return RT_ERR_OK;
    }
    else if (RT_ERR_L2_ENTRY_NOTFOUND == retVal)
    {
        osal_memset(&l2Table, 0, sizeof(rtl8367d_luttb));
        osal_memcpy(l2Table.mac.octet, pMcastAddr->mac.octet, ETHER_ADDR_LEN);
        l2Table.ivl_svl     = pMcastAddr->ivl;
        if(pMcastAddr->ivl)
            l2Table.cvid_fid    = pMcastAddr->vid;
        else
            l2Table.cvid_fid    = pMcastAddr->fid;

        l2Table.mbr         = pmask;
        l2Table.nosalearn   = 1;
        l2Table.l3lookup    = 0;
        if ((retVal = _rtl8367d_setL2LookupTb(unit, &l2Table)) != RT_ERR_OK)
            return retVal;

        pMcastAddr->address = l2Table.address;

        method = RTL8367D_LUTREADMETHOD_MAC;
        retVal = _rtl8367d_getL2LookupTb(unit, method, &l2Table);
        if (RT_ERR_L2_ENTRY_NOTFOUND == retVal)
            return     RT_ERR_L2_INDEXTBL_FULL;
        else
            return retVal;
    }
    else
        return retVal;

}

/* Function Name:
 *      dal_rtl8367d_l2_mcastAddr_get
 * Description:
 *      Get LUT multicast entry.
 * Input:
 *      unit        - Unit ID
 *      pMcastAddr  - L2 multicast entry structure
 * Output:
 *      pMcastAddr  - L2 multicast entry structure
 * Return:
 *      RT_ERR_OK                   - OK
 *      RT_ERR_FAILED               - Failed
 *      RT_ERR_SMI                  - SMI access error
 *      RT_ERR_MAC                  - Invalid MAC address.
 *      RT_ERR_L2_FID               - Invalid FID .
 *      RT_ERR_L2_VID               - Invalid VID .
 *      RT_ERR_L2_ENTRY_NOTFOUND    - No such LUT entry.
 *      RT_ERR_INPUT                - Invalid input parameters.
 * Note:
 *      If the multicast mac address existed in the LUT, it will return the port where
 *      the mac is learned. Otherwise, it will return a RT_ERR_L2_ENTRY_NOTFOUND error.
 */
rtksw_api_ret_t dal_rtl8367d_l2_mcastAddr_get(rtksw_uint32 unit, rtksw_l2_mcastAddr_t *pMcastAddr)
{
    rtksw_api_ret_t retVal;
    rtksw_uint32 method;
    rtl8367d_luttb l2Table;

    /* Check initialization state */
    RTKSW_CHK_INIT_STATE(unit);

    if(NULL == pMcastAddr)
        return RT_ERR_NULL_POINTER;

    /* must be L2 multicast address */
    if( (pMcastAddr->mac.octet[0] & 0x01) != 0x01)
        return RT_ERR_MAC;

    if(pMcastAddr->ivl == 1)
    {
        if (pMcastAddr->vid > RTL8367D_VIDMAX)
            return RT_ERR_L2_VID;
    }
    else if(pMcastAddr->ivl == 0)
    {
        if (pMcastAddr->fid > RTL8367D_FIDMAX)
            return RT_ERR_L2_FID;
    }
    else
        return RT_ERR_INPUT;

    osal_memset(&l2Table, 0, sizeof(rtl8367d_luttb));
    osal_memcpy(l2Table.mac.octet, pMcastAddr->mac.octet, ETHER_ADDR_LEN);
    l2Table.ivl_svl     = pMcastAddr->ivl;

    if(pMcastAddr->ivl)
        l2Table.cvid_fid    = pMcastAddr->vid;
    else
        l2Table.cvid_fid    = pMcastAddr->fid;

    method = RTL8367D_LUTREADMETHOD_MAC;

    if ((retVal = _rtl8367d_getL2LookupTb(unit, method, &l2Table)) != RT_ERR_OK)
        return retVal;

    pMcastAddr->address     = l2Table.address;

    /* Get Logical port mask */
    if ((retVal = rtksw_switch_portmask_P2L_get(unit, l2Table.mbr, &pMcastAddr->portmask)) != RT_ERR_OK)
        return retVal;

    return RT_ERR_OK;
}

/* Function Name:
 *      dal_rtl8367d_l2_mcastAddr_next_get
 * Description:
 *      Get Next L2 Multicast entry.
 * Input:
 *      unit        - Unit ID
 *      pAddress    - The Address ID
 * Output:
 *      pMcastAddr  - L2 multicast entry structure
 * Return:
 *      RT_ERR_OK                   - OK
 *      RT_ERR_FAILED               - Failed
 *      RT_ERR_SMI                  - SMI access error
 *      RT_ERR_L2_ENTRY_NOTFOUND    - No such LUT entry.
 *      RT_ERR_INPUT                - Invalid input parameters.
 * Note:
 *      Get the next L2 multicast entry after the current entry pointed by pAddress.
 *      The address of next entry is returned by pAddress. User can use (address + 1)
 *      as pAddress to call this API again for dumping all multicast entries is LUT.
 */
rtksw_api_ret_t dal_rtl8367d_l2_mcastAddr_next_get(rtksw_uint32 unit, rtksw_uint32 *pAddress, rtksw_l2_mcastAddr_t *pMcastAddr)
{
    rtksw_api_ret_t   retVal;
    rtl8367d_luttb  l2Table;

    /* Check initialization state */
    RTKSW_CHK_INIT_STATE(unit);

    /* Error Checking */
    if ((pAddress == NULL) || (pMcastAddr == NULL))
        return RT_ERR_INPUT;

    if(*pAddress > RTKSW_MAX_LUT_ADDR_ID )
        return RT_ERR_L2_L2UNI_PARAM;

    osal_memset(pMcastAddr, 0, sizeof(rtksw_l2_mcastAddr_t));
    osal_memset(&l2Table, 0, sizeof(rtl8367d_luttb));
    l2Table.address = *pAddress;

    if ((retVal = _rtl8367d_getL2LookupTb(unit, RTL8367D_LUTREADMETHOD_NEXT_L2MC, &l2Table)) != RT_ERR_OK)
        return retVal;

    if(l2Table.address < *pAddress)
        return RT_ERR_L2_ENTRY_NOTFOUND;

    osal_memcpy(pMcastAddr->mac.octet, l2Table.mac.octet, ETHER_ADDR_LEN);
    pMcastAddr->ivl     = l2Table.ivl_svl;

    if(pMcastAddr->ivl)
        pMcastAddr->vid = l2Table.cvid_fid;
    else
        pMcastAddr->fid = l2Table.cvid_fid;

    pMcastAddr->address     = l2Table.address;

    /* Get Logical port mask */
    if ((retVal = rtksw_switch_portmask_P2L_get(unit, l2Table.mbr, &pMcastAddr->portmask)) != RT_ERR_OK)
        return retVal;

    *pAddress = l2Table.address;

    return RT_ERR_OK;
}

/* Function Name:
 *      dal_rtl8367d_l2_mcastAddr_del
 * Description:
 *      Delete LUT multicast entry.
 * Input:
 *      unit        - Unit ID
 *      pMcastAddr  - L2 multicast entry structure
 * Output:
 *      None
 * Return:
 *      RT_ERR_OK                   - OK
 *      RT_ERR_FAILED               - Failed
 *      RT_ERR_SMI                  - SMI access error
 *      RT_ERR_MAC                  - Invalid MAC address.
 *      RT_ERR_L2_FID               - Invalid FID .
 *      RT_ERR_L2_VID               - Invalid VID .
 *      RT_ERR_L2_ENTRY_NOTFOUND    - No such LUT entry.
 *      RT_ERR_INPUT                - Invalid input parameters.
 * Note:
 *      If the mac has existed in the LUT, it will be deleted. Otherwise, it will return RT_ERR_L2_ENTRY_NOTFOUND.
 */
rtksw_api_ret_t dal_rtl8367d_l2_mcastAddr_del(rtksw_uint32 unit, rtksw_l2_mcastAddr_t *pMcastAddr)
{
    rtksw_api_ret_t retVal;
    rtksw_uint32 method;
    rtl8367d_luttb l2Table;

    /* Check initialization state */
    RTKSW_CHK_INIT_STATE(unit);

    if(NULL == pMcastAddr)
        return RT_ERR_NULL_POINTER;

    /* must be L2 multicast address */
    if( (pMcastAddr->mac.octet[0] & 0x01) != 0x01)
        return RT_ERR_MAC;

    if(pMcastAddr->ivl == 1)
    {
        if (pMcastAddr->vid > RTL8367D_VIDMAX)
            return RT_ERR_L2_VID;
    }
    else if(pMcastAddr->ivl == 0)
    {
        if (pMcastAddr->fid > RTL8367D_FIDMAX)
            return RT_ERR_L2_FID;
    }
    else
        return RT_ERR_INPUT;

    osal_memset(&l2Table, 0, sizeof(rtl8367d_luttb));

    /* fill key (MAC,FID) to get L2 entry */
    osal_memcpy(l2Table.mac.octet, pMcastAddr->mac.octet, ETHER_ADDR_LEN);
    l2Table.ivl_svl     = pMcastAddr->ivl;

    if(pMcastAddr->ivl)
        l2Table.cvid_fid    = pMcastAddr->vid;
    else
        l2Table.cvid_fid    = pMcastAddr->fid;

    method = RTL8367D_LUTREADMETHOD_MAC;
    retVal = _rtl8367d_getL2LookupTb(unit, method, &l2Table);
    if (RT_ERR_OK == retVal)
    {
        osal_memcpy(l2Table.mac.octet, pMcastAddr->mac.octet, ETHER_ADDR_LEN);
        l2Table.ivl_svl     = pMcastAddr->ivl;

        if(pMcastAddr->ivl)
            l2Table.cvid_fid    = pMcastAddr->vid;
        else
            l2Table.cvid_fid    = pMcastAddr->fid;

        l2Table.mbr         = 0;
        l2Table.nosalearn   = 0;
//        l2Table.sa_block    = 0;
        l2Table.l3lookup    = 0;
        if((retVal = _rtl8367d_setL2LookupTb(unit, &l2Table)) != RT_ERR_OK)
            return retVal;

        pMcastAddr->address = l2Table.address;
        return RT_ERR_OK;
    }
    else
        return retVal;
}

/* Function Name:
 *      dal_rtl8367d_l2_ipMcastAddr_add
 * Description:
 *      Add Lut IP multicast entry
 * Input:
 *      unit            - Unit ID
 *      pIpMcastAddr    - IP Multicast entry
 * Output:
 *      None
 * Return:
 *      RT_ERR_OK               - OK
 *      RT_ERR_FAILED           - Failed
 *      RT_ERR_SMI              - SMI access error
 *      RT_ERR_PORT_ID          - Invalid port number.
 *      RT_ERR_L2_INDEXTBL_FULL - hashed index is full of entries.
 *      RT_ERR_PORT_MASK        - Invalid portmask.
 *      RT_ERR_INPUT            - Invalid input parameters.
 * Note:
 *      System supports L2 entry with IP multicast DIP/SIP to forward IP multicasting frame as user
 *      desired. If this function is enabled, then system will be looked up L2 IP multicast entry to
 *      forward IP multicast frame directly without flooding.
 */
rtksw_api_ret_t dal_rtl8367d_l2_ipMcastAddr_add(rtksw_uint32 unit, rtksw_l2_ipMcastAddr_t *pIpMcastAddr)
{
    rtksw_api_ret_t retVal;
    rtksw_uint32 method;
    rtl8367d_luttb l2Table;
    rtksw_uint32 pmask;

    /* Check initialization state */
    RTKSW_CHK_INIT_STATE(unit);

    if(NULL == pIpMcastAddr)
        return RT_ERR_NULL_POINTER;

    /* check port mask */
    RTKSW_CHK_PORTMASK_VALID(unit, &pIpMcastAddr->portmask);

    if( (pIpMcastAddr->dip & 0xF0000000) != 0xE0000000)
        return RT_ERR_INPUT;

    /* Get Physical port mask */
    if ((retVal = rtksw_switch_portmask_L2P_get(unit, &pIpMcastAddr->portmask, &pmask)) != RT_ERR_OK)
        return retVal;

    osal_memset(&l2Table, 0x00, sizeof(rtl8367d_luttb));
    l2Table.sip = pIpMcastAddr->sip;
    l2Table.dip = pIpMcastAddr->dip;
    l2Table.l3lookup = 1;
    method = RTL8367D_LUTREADMETHOD_MAC;
    retVal = _rtl8367d_getL2LookupTb(unit, method, &l2Table);
    if (RT_ERR_OK == retVal)
    {
        l2Table.sip = pIpMcastAddr->sip;
        l2Table.dip = pIpMcastAddr->dip;
        l2Table.mbr = pmask;
        l2Table.nosalearn = 1;
        l2Table.l3lookup = 1;
        if((retVal = _rtl8367d_setL2LookupTb(unit, &l2Table)) != RT_ERR_OK)
            return retVal;

        pIpMcastAddr->address = l2Table.address;
        return RT_ERR_OK;
    }
    else if (RT_ERR_L2_ENTRY_NOTFOUND == retVal)
    {
        osal_memset(&l2Table, 0, sizeof(rtl8367d_luttb));
        l2Table.sip = pIpMcastAddr->sip;
        l2Table.dip = pIpMcastAddr->dip;
        l2Table.mbr = pmask;
        l2Table.nosalearn = 1;
        l2Table.l3lookup = 1;
        if ((retVal = _rtl8367d_setL2LookupTb(unit, &l2Table)) != RT_ERR_OK)
            return retVal;

        pIpMcastAddr->address = l2Table.address;

        method = RTL8367D_LUTREADMETHOD_MAC;
        retVal = _rtl8367d_getL2LookupTb(unit, method, &l2Table);
        if (RT_ERR_L2_ENTRY_NOTFOUND == retVal)
            return     RT_ERR_L2_INDEXTBL_FULL;
        else
            return retVal;

    }
    else
        return retVal;

}

/* Function Name:
 *      dal_rtl8367d_l2_ipMcastAddr_get
 * Description:
 *      Get LUT IP multicast entry.
 * Input:
 *      unit            - Unit ID
 *      pIpMcastAddr    - IP Multicast entry
 * Output:
 *      pIpMcastAddr    - IP Multicast entry
 * Return:
 *      RT_ERR_OK                   - OK
 *      RT_ERR_FAILED               - Failed
 *      RT_ERR_SMI                  - SMI access error
 *      RT_ERR_L2_ENTRY_NOTFOUND    - No such LUT entry.
 *      RT_ERR_INPUT                - Invalid input parameters.
 * Note:
 *      The API can get Lut table of IP multicast entry.
 */
rtksw_api_ret_t dal_rtl8367d_l2_ipMcastAddr_get(rtksw_uint32 unit, rtksw_l2_ipMcastAddr_t *pIpMcastAddr)
{
    rtksw_api_ret_t retVal;
    rtksw_uint32 method;
    rtl8367d_luttb l2Table;

    /* Check initialization state */
    RTKSW_CHK_INIT_STATE(unit);

    if(NULL == pIpMcastAddr)
        return RT_ERR_NULL_POINTER;

    if( (pIpMcastAddr->dip & 0xF0000000) != 0xE0000000)
        return RT_ERR_INPUT;

    osal_memset(&l2Table, 0x00, sizeof(rtl8367d_luttb));
    l2Table.sip = pIpMcastAddr->sip;
    l2Table.dip = pIpMcastAddr->dip;
    l2Table.l3lookup = 1;
    method = RTL8367D_LUTREADMETHOD_MAC;
    if ((retVal = _rtl8367d_getL2LookupTb(unit, method, &l2Table)) != RT_ERR_OK)
        return retVal;

    /* Get Logical port mask */
    if ((retVal = rtksw_switch_portmask_P2L_get(unit, l2Table.mbr, &pIpMcastAddr->portmask)) != RT_ERR_OK)
        return retVal;

    pIpMcastAddr->address       = l2Table.address;

    return RT_ERR_OK;
}

/* Function Name:
 *      dal_rtl8367d_l2_ipMcastAddr_next_get
 * Description:
 *      Get Next IP Multicast entry.
 * Input:
 *      unit            - Unit ID
 *      pAddress        - The Address ID
 * Output:
 *      pIpMcastAddr    - IP Multicast entry
 * Return:
 *      RT_ERR_OK                   - OK
 *      RT_ERR_FAILED               - Failed
 *      RT_ERR_SMI                  - SMI access error
 *      RT_ERR_L2_ENTRY_NOTFOUND    - No such LUT entry.
 *      RT_ERR_INPUT                - Invalid input parameters.
 * Note:
 *      Get the next IP multicast entry after the current entry pointed by pAddress.
 *      The address of next entry is returned by pAddress. User can use (address + 1)
 *      as pAddress to call this API again for dumping all IP multicast entries is LUT.
 */
rtksw_api_ret_t dal_rtl8367d_l2_ipMcastAddr_next_get(rtksw_uint32 unit, rtksw_uint32 *pAddress, rtksw_l2_ipMcastAddr_t *pIpMcastAddr)
{
    rtksw_api_ret_t   retVal;
    rtl8367d_luttb  l2Table;

    /* Check initialization state */
    RTKSW_CHK_INIT_STATE(unit);

    /* Error Checking */
    if ((pAddress == NULL) || (pIpMcastAddr == NULL) )
        return RT_ERR_INPUT;

    if(*pAddress > RTKSW_MAX_LUT_ADDR_ID )
        return RT_ERR_L2_L2UNI_PARAM;

    osal_memset(pIpMcastAddr, 0, sizeof(rtksw_l2_ipMcastAddr_t));
    osal_memset(&l2Table, 0, sizeof(rtl8367d_luttb));
    l2Table.address = *pAddress;

    if ((retVal = _rtl8367d_getL2LookupTb(unit, RTL8367D_LUTREADMETHOD_NEXT_L3MC, &l2Table)) != RT_ERR_OK)
        return retVal;

    if(l2Table.address < *pAddress)
        return RT_ERR_L2_ENTRY_NOTFOUND;

    pIpMcastAddr->sip = l2Table.sip;
    pIpMcastAddr->dip = l2Table.dip;

    /* Get Logical port mask */
    if ((retVal = rtksw_switch_portmask_P2L_get(unit, l2Table.mbr, &pIpMcastAddr->portmask)) != RT_ERR_OK)
        return retVal;

    pIpMcastAddr->address       = l2Table.address;
    *pAddress = l2Table.address;

    return RT_ERR_OK;
}

/* Function Name:
 *      dal_rtl8367d_l2_ipMcastAddr_del
 * Description:
 *      Delete a ip multicast address entry from the specified device.
 * Input:
 *      unit            - Unit ID
 *      pIpMcastAddr    - IP Multicast entry
 * Output:
 *      None
 * Return:
 *      RT_ERR_OK                   - OK
 *      RT_ERR_FAILED               - Failed
 *      RT_ERR_SMI                  - SMI access error
 *      RT_ERR_L2_ENTRY_NOTFOUND    - No such LUT entry.
 *      RT_ERR_INPUT                - Invalid input parameters.
 * Note:
 *      The API can delete a IP multicast address entry from the specified device.
 */
rtksw_api_ret_t dal_rtl8367d_l2_ipMcastAddr_del(rtksw_uint32 unit, rtksw_l2_ipMcastAddr_t *pIpMcastAddr)
{
    rtksw_api_ret_t retVal;
    rtksw_uint32 method;
    rtl8367d_luttb l2Table;

    /* Check initialization state */
    RTKSW_CHK_INIT_STATE(unit);

    /* Error Checking */
    if (pIpMcastAddr == NULL)
        return RT_ERR_INPUT;

    if( (pIpMcastAddr->dip & 0xF0000000) != 0xE0000000)
        return RT_ERR_INPUT;

    osal_memset(&l2Table, 0x00, sizeof(rtl8367d_luttb));
    l2Table.sip = pIpMcastAddr->sip;
    l2Table.dip = pIpMcastAddr->dip;
    l2Table.l3lookup = 1;
    method = RTL8367D_LUTREADMETHOD_MAC;
    retVal = _rtl8367d_getL2LookupTb(unit, method, &l2Table);
    if (RT_ERR_OK == retVal)
    {
        l2Table.sip = pIpMcastAddr->sip;
        l2Table.dip = pIpMcastAddr->dip;
        l2Table.mbr = 0;
        l2Table.nosalearn = 0;
        l2Table.l3lookup = 1;
        if((retVal = _rtl8367d_setL2LookupTb(unit, &l2Table)) != RT_ERR_OK)
            return retVal;

        pIpMcastAddr->address = l2Table.address;
        return RT_ERR_OK;
    }
    else
        return retVal;
}

/* Function Name:
 *      dal_rtl8367d_l2_ucastAddr_flush
 * Description:
 *      Flush L2 mac address by type in the specified device (both dynamic and static).
 * Input:
 *      unit    - Unit ID
 *      pConfig - flush configuration
 * Output:
 *      None
 * Return:
 *      RT_ERR_OK           - OK
 *      RT_ERR_FAILED       - Failed
 *      RT_ERR_SMI          - SMI access error
 *      RT_ERR_PORT_ID      - Invalid port number.
 *      RT_ERR_VLAN_VID     - Invalid VID parameter.
 *      RT_ERR_INPUT        - Invalid input parameters.
 * Note:
 *      flushByVid          - 1: Flush by VID, 0: Don't flush by VID
 *      vid                 - VID (0 ~ 4095)
 *      flushByFid          - 1: Flush by FID, 0: Don't flush by FID
 *      fid                 - FID (0 ~ 15)
 *      flushByPort         - 1: Flush by Port, 0: Don't flush by Port
 *      port                - Port ID
 *      flushByMac          - Not Supported
 *      ucastAddr           - Not Supported
 *      flushStaticAddr     - 1: Flush both Static and Dynamic entries, 0: Flush only Dynamic entries
 *      flushAddrOnAllPorts - 1: Flush VID-matched entries at all ports, 0: Flush VID-matched entries per port.
 */
rtksw_api_ret_t dal_rtl8367d_l2_ucastAddr_flush(rtksw_uint32 unit, rtksw_l2_flushCfg_t *pConfig)
{
    rtksw_api_ret_t   retVal;
    rtksw_uint32 phyPort;

    /* Check initialization state */
    RTKSW_CHK_INIT_STATE(unit);

    if(pConfig == NULL)
        return RT_ERR_NULL_POINTER;

    if(pConfig->flushByVid >= RTKSW_ENABLE_END)
        return RT_ERR_ENABLE;

    if(pConfig->flushByFid >= RTKSW_ENABLE_END)
        return RT_ERR_ENABLE;

    if(pConfig->flushByPort >= RTKSW_ENABLE_END)
        return RT_ERR_ENABLE;

    if(pConfig->flushByMac >= RTKSW_ENABLE_END)
        return RT_ERR_ENABLE;

    if(pConfig->flushStaticAddr >= RTKSW_ENABLE_END)
        return RT_ERR_ENABLE;

    if(pConfig->flushAddrOnAllPorts >= RTKSW_ENABLE_END)
        return RT_ERR_ENABLE;

    if(pConfig->vid > RTL8367D_VIDMAX)
        return RT_ERR_VLAN_VID;

    if(pConfig->fid > RTL8367D_FIDMAX)
        return RT_ERR_INPUT;

    /* check port valid */
    RTKSW_CHK_PORT_VALID(unit, pConfig->port);

    phyPort = rtksw_switch_port_L2P_get(unit, pConfig->port);
    if (phyPort == UNDEFINE_PHY_PORT)
        return RT_ERR_PORT_ID;

    if(pConfig->flushByVid == RTKSW_ENABLED)
    {
        if ((retVal = rtl8367d_setAsicRegBits(unit, RTL8367D_REG_L2_FLUSH_CTRL2, RTL8367D_LUT_FLUSH_MODE_MASK, RTL8367D_FLUSHMDOE_VID)) != RT_ERR_OK)
            return retVal;

        if ((retVal = rtl8367d_setAsicRegBits(unit, RTL8367D_REG_L2_FLUSH_CTRL1, RTL8367D_LUT_FLUSH_VID_MASK, pConfig->vid)) != RT_ERR_OK)
                return retVal;

        if ((retVal = rtl8367d_setAsicRegBit(unit, RTL8367D_REG_L2_FLUSH_CTRL2, RTL8367D_LUT_FLUSH_TYPE_OFFSET,((pConfig->flushStaticAddr == RTKSW_ENABLED) ? RTL8367D_FLUSHTYPE_BOTH : RTL8367D_FLUSHTYPE_DYNAMIC))) != RT_ERR_OK)
            return retVal;

        if(pConfig->flushAddrOnAllPorts == RTKSW_ENABLED)
        {
            if ((retVal = rtl8367d_setAsicRegBits(unit, RTL8367D_REG_FORCE_FLUSH, RTL8367D_FORCE_FLUSH_PORTMASK_MASK, RTL8367D_PORTMASK)) != RT_ERR_OK)
                return retVal;
        }
        else if(pConfig->flushByPort == RTKSW_ENABLED)
        {
            if ((retVal = rtl8367d_setAsicRegBits(unit, RTL8367D_REG_FORCE_FLUSH, RTL8367D_FORCE_FLUSH_PORTMASK_MASK, (1 << phyPort) & 0xff)) != RT_ERR_OK)
                return retVal;
        }
        else
            return RT_ERR_INPUT;
    }
    else if(pConfig->flushByFid == RTKSW_ENABLED)
    {
        if ((retVal = rtl8367d_setAsicRegBits(unit, RTL8367D_REG_L2_FLUSH_CTRL2, RTL8367D_LUT_FLUSH_MODE_MASK, RTL8367D_FLUSHMDOE_FID)) != RT_ERR_OK)
            return retVal;

        if ((retVal = rtl8367d_setAsicRegBits(unit, RTL8367D_REG_L2_FLUSH_CTRL1, RTL8367D_LUT_FLUSH_FID_MASK, pConfig->fid)) != RT_ERR_OK)
                return retVal;

        if ((retVal = rtl8367d_setAsicRegBit(unit, RTL8367D_REG_L2_FLUSH_CTRL2, RTL8367D_LUT_FLUSH_TYPE_OFFSET,((pConfig->flushStaticAddr == RTKSW_ENABLED) ? RTL8367D_FLUSHTYPE_BOTH : RTL8367D_FLUSHTYPE_DYNAMIC))) != RT_ERR_OK)
            return retVal;

        if(pConfig->flushAddrOnAllPorts == RTKSW_ENABLED)
        {
            if ((retVal = rtl8367d_setAsicRegBits(unit, RTL8367D_REG_FORCE_FLUSH, RTL8367D_FORCE_FLUSH_PORTMASK_MASK, RTL8367D_PORTMASK)) != RT_ERR_OK)
                return retVal;
        }
        else if(pConfig->flushByPort == RTKSW_ENABLED)
        {
            if ((retVal = rtl8367d_setAsicRegBits(unit, RTL8367D_REG_FORCE_FLUSH, RTL8367D_FORCE_FLUSH_PORTMASK_MASK, (1 << phyPort) & 0xff)) != RT_ERR_OK)
                return retVal;
        }
        else
            return RT_ERR_INPUT;
    }
    else if(pConfig->flushByPort == RTKSW_ENABLED)
    {
        if ((retVal = rtl8367d_setAsicRegBit(unit, RTL8367D_REG_L2_FLUSH_CTRL2, RTL8367D_LUT_FLUSH_TYPE_OFFSET,((pConfig->flushStaticAddr == RTKSW_ENABLED) ? RTL8367D_FLUSHTYPE_BOTH : RTL8367D_FLUSHTYPE_DYNAMIC))) != RT_ERR_OK)
            return retVal;

        if ((retVal = rtl8367d_setAsicRegBits(unit, RTL8367D_REG_L2_FLUSH_CTRL2, RTL8367D_LUT_FLUSH_MODE_MASK, RTL8367D_FLUSHMDOE_PORT)) != RT_ERR_OK)
            return retVal;

        if ((retVal = rtl8367d_setAsicRegBits(unit, RTL8367D_REG_FORCE_FLUSH, RTL8367D_FORCE_FLUSH_PORTMASK_MASK, (1 << phyPort) & 0xff)) != RT_ERR_OK)
            return retVal;
    }
    else if(pConfig->flushByMac == RTKSW_ENABLED)
    {
        /* Should use API "rtksw_l2_addr_del" to remove a specified entry*/
        return RT_ERR_CHIP_NOT_SUPPORTED;
    }
    else
        return RT_ERR_INPUT;

    return RT_ERR_OK;
}

/* Function Name:
 *      dal_rtl8367d_l2_table_clear
 * Description:
 *      Flush all static & dynamic entries in LUT.
 * Input:
 *      unit    - Unit ID
 * Output:
 *      None
 * Return:
 *      RT_ERR_OK           - OK
 *      RT_ERR_FAILED       - Failed
 *      RT_ERR_SMI          - SMI access error
 * Note:
 *
 */
rtksw_api_ret_t dal_rtl8367d_l2_table_clear(rtksw_uint32 unit)
{
    rtksw_api_ret_t   retVal;

    /* Check initialization state */
    RTKSW_CHK_INIT_STATE(unit);

    if ((retVal = rtl8367d_setAsicRegBit(unit, RTL8367D_REG_L2_FLUSH_CTRL3, RTL8367D_L2_FLUSH_CTRL3_OFFSET, 1)) != RT_ERR_OK)
        return retVal;

    return RT_ERR_OK;
}

/* Function Name:
 *      dal_rtl8367d_l2_table_clearStatus_get
 * Description:
 *      Get table clear status
 * Input:
 *      unit    - Unit ID
 * Output:
 *      pStatus - Clear status, 1:Busy, 0:finish
 * Return:
 *      RT_ERR_OK           - OK
 *      RT_ERR_FAILED       - Failed
 *      RT_ERR_SMI          - SMI access error
 * Note:
 *
 */
rtksw_api_ret_t dal_rtl8367d_l2_table_clearStatus_get(rtksw_uint32 unit, rtksw_l2_clearStatus_t *pStatus)
{
    rtksw_api_ret_t   retVal;

    /* Check initialization state */
    RTKSW_CHK_INIT_STATE(unit);

    if(NULL == pStatus)
        return RT_ERR_NULL_POINTER;

    if ((retVal = rtl8367d_getAsicRegBit(unit, RTL8367D_REG_L2_FLUSH_CTRL3, RTL8367D_L2_FLUSH_CTRL3_OFFSET, (rtksw_uint32 *)pStatus)) != RT_ERR_OK)
        return retVal;

    return RT_ERR_OK;
}

/* Function Name:
 *      dal_rtl8367d_l2_flushLinkDownPortAddrEnable_set
 * Description:
 *      Set HW flush linkdown port mac configuration of the specified device.
 * Input:
 *      unit    - Unit ID
 *      port    - Port id.
 *      enable  - link down flush status
 * Output:
 *      None
 * Return:
 *      RT_ERR_OK           - OK
 *      RT_ERR_FAILED       - Failed
 *      RT_ERR_SMI          - SMI access error
 *      RT_ERR_PORT_ID      - Invalid port number.
 *      RT_ERR_ENABLE       - Invalid enable input.
 * Note:
 *      The status of flush linkdown port address is as following:
 *      - RTKSW_DISABLED
 *      - RTKSW_ENABLED
 */
rtksw_api_ret_t dal_rtl8367d_l2_flushLinkDownPortAddrEnable_set(rtksw_uint32 unit, rtksw_port_t port, rtksw_enable_t enable)
{
    rtksw_api_ret_t retVal;

    /* Check initialization state */
    RTKSW_CHK_INIT_STATE(unit);

    if (port != RTKSW_WHOLE_SYSTEM)
        return RT_ERR_PORT_ID;

    if (enable >= RTKSW_ENABLE_END)
        return RT_ERR_ENABLE;

    if ((retVal = rtl8367d_setAsicRegBit(unit, RTL8367D_REG_LUT_CFG, RTL8367D_LINKDOWN_AGEOUT_OFFSET, enable ? 0 : 1)) != RT_ERR_OK)
        return retVal;


    return RT_ERR_OK;
}

/* Function Name:
 *      dal_rtl8367d_l2_flushLinkDownPortAddrEnable_get
 * Description:
 *      Get HW flush linkdown port mac configuration of the specified device.
 * Input:
 *      unit    - Unit ID
 *      port    - Port id.
 * Output:
 *      pEnable - link down flush status
 * Return:
 *      RT_ERR_OK           - OK
 *      RT_ERR_FAILED       - Failed
 *      RT_ERR_SMI          - SMI access error
 *      RT_ERR_PORT_ID      - Invalid port number.
 * Note:
 *      The status of flush linkdown port address is as following:
 *      - RTKSW_DISABLED
 *      - RTKSW_ENABLED
 */
rtksw_api_ret_t dal_rtl8367d_l2_flushLinkDownPortAddrEnable_get(rtksw_uint32 unit, rtksw_port_t port, rtksw_enable_t *pEnable)
{
    rtksw_api_ret_t retVal;
    rtksw_uint32  value;

    /* Check initialization state */
    RTKSW_CHK_INIT_STATE(unit);

    if (port != RTKSW_WHOLE_SYSTEM)
        return RT_ERR_PORT_ID;

    if(NULL == pEnable)
        return RT_ERR_NULL_POINTER;

    if ((retVal = rtl8367d_getAsicRegBit(unit, RTL8367D_REG_LUT_CFG, RTL8367D_LINKDOWN_AGEOUT_OFFSET, &value)) != RT_ERR_OK)
        return retVal;

    *pEnable = value ? 0 : 1;

    return RT_ERR_OK;
}

/* Function Name:
 *      dal_rtl8367d_l2_agingEnable_set
 * Description:
 *      Set L2 LUT aging status per port setting.
 * Input:
 *      unit    - Unit ID
 *      port    - Port id.
 *      enable  - Aging status
 * Output:
 *      None
 * Return:
 *      RT_ERR_OK           - OK
 *      RT_ERR_FAILED       - Failed
 *      RT_ERR_SMI          - SMI access error
 *      RT_ERR_PORT_ID      - Invalid port number.
 *      RT_ERR_ENABLE       - Invalid enable input.
 * Note:
 *      This API can be used to set L2 LUT aging status per port.
 */
rtksw_api_ret_t dal_rtl8367d_l2_agingEnable_set(rtksw_uint32 unit, rtksw_port_t port, rtksw_enable_t enable)
{
    rtksw_api_ret_t retVal;

    /* Check initialization state */
    RTKSW_CHK_INIT_STATE(unit);

    /* check port valid */
    RTKSW_CHK_PORT_VALID(unit, port);

    if (enable >= RTKSW_ENABLE_END)
        return RT_ERR_ENABLE;

    if(enable == 1)
        enable = 0;
    else
        enable = 1;

    if ((retVal = rtl8367d_setAsicRegBit(unit, RTL8367D_REG_LUT_AGEOUT_CTRL, rtksw_switch_port_L2P_get(unit, port), enable)) != RT_ERR_OK)
        return retVal;

    return RT_ERR_OK;
}

/* Function Name:
 *      dal_rtl8367d_l2_agingEnable_get
 * Description:
 *      Get L2 LUT aging status per port setting.
 * Input:
 *      unit    - Unit ID
 *      port    - Port id.
 * Output:
 *      pEnable - Aging status
 * Return:
 *      RT_ERR_OK           - OK
 *      RT_ERR_FAILED       - Failed
 *      RT_ERR_SMI          - SMI access error
 *      RT_ERR_PORT_ID      - Invalid port number.
 * Note:
 *      This API can be used to get L2 LUT aging function per port.
 */
rtksw_api_ret_t dal_rtl8367d_l2_agingEnable_get(rtksw_uint32 unit, rtksw_port_t port, rtksw_enable_t *pEnable)
{
    rtksw_api_ret_t retVal;

    /* Check initialization state */
    RTKSW_CHK_INIT_STATE(unit);

    /* check port valid */
    RTKSW_CHK_PORT_VALID(unit, port);

    if(NULL == pEnable)
        return RT_ERR_NULL_POINTER;

    if ((retVal = rtl8367d_getAsicRegBit(unit, RTL8367D_REG_LUT_AGEOUT_CTRL, rtksw_switch_port_L2P_get(unit, port), pEnable)) != RT_ERR_OK)
        return retVal;

    if(*pEnable == 1)
        *pEnable = 0;
    else
        *pEnable = 1;

    return RT_ERR_OK;
}

/* Function Name:
 *      dal_rtl8367d_l2_limitLearningCnt_set
 * Description:
 *      Set per-Port auto learning limit number
 * Input:
 *      unit    - Unit ID
 *      port    - Port id.
 *      mac_cnt - Auto learning entries limit number
 * Output:
 *      None
 * Return:
 *      RT_ERR_OK                   - OK
 *      RT_ERR_FAILED               - Failed
 *      RT_ERR_SMI                  - SMI access error
 *      RT_ERR_PORT_ID              - Invalid port number.
 *      RT_ERR_LIMITED_L2ENTRY_NUM  - Invalid auto learning limit number
 * Note:
 *      The API can set per-port ASIC auto learning limit number from 0(disable learning)
 *      to 2112.
 */
rtksw_api_ret_t dal_rtl8367d_l2_limitLearningCnt_set(rtksw_uint32 unit, rtksw_port_t port, rtksw_mac_cnt_t mac_cnt)
{
    rtksw_api_ret_t retVal;

    /* Check initialization state */
    RTKSW_CHK_INIT_STATE(unit);

    /* check port valid */
    RTKSW_CHK_PORT_VALID(unit, port);

    if (mac_cnt > rtksw_switch_maxLutAddrNumber_get(unit))
        return RT_ERR_LIMITED_L2ENTRY_NUM;

    if ((retVal = rtl8367d_setAsicReg(unit, RTL8367D_REG_LUT_PORT0_LEARN_LIMITNO + rtksw_switch_port_L2P_get(unit, port), mac_cnt)) != RT_ERR_OK)
        return retVal;

    return RT_ERR_OK;
}

/* Function Name:
 *      dal_rtl8367d_l2_limitLearningCnt_get
 * Description:
 *      Get per-Port auto learning limit number
 * Input:
 *      unit    - Unit ID
 *      port    - Port id.
 * Output:
 *      pMac_cnt - Auto learning entries limit number
 * Return:
 *      RT_ERR_OK           - OK
 *      RT_ERR_FAILED       - Failed
 *      RT_ERR_SMI          - SMI access error
 *      RT_ERR_PORT_ID      - Invalid port number.
 * Note:
 *      The API can get per-port ASIC auto learning limit number.
 */
rtksw_api_ret_t dal_rtl8367d_l2_limitLearningCnt_get(rtksw_uint32 unit, rtksw_port_t port, rtksw_mac_cnt_t *pMac_cnt)
{
    rtksw_api_ret_t retVal;
    rtksw_uint32 regData;

    /* Check initialization state */
    RTKSW_CHK_INIT_STATE(unit);

    /* check port valid */
    RTKSW_CHK_PORT_VALID(unit, port);

    if(NULL == pMac_cnt)
        return RT_ERR_NULL_POINTER;

    if ((retVal = rtl8367d_getAsicReg(unit, RTL8367D_REG_LUT_PORT0_LEARN_LIMITNO + rtksw_switch_port_L2P_get(unit, port), &regData)) != RT_ERR_OK)
        return retVal;

    *pMac_cnt = (rtksw_mac_cnt_t)((regData > rtksw_switch_maxLutAddrNumber_get(unit)) ? rtksw_switch_maxLutAddrNumber_get(unit) : regData);
    return RT_ERR_OK;
}

/* Function Name:
 *      dal_rtl8367d_l2_limitSystemLearningCnt_set
 * Description:
 *      Set System auto learning limit number
 * Input:
 *      unit    - Unit ID
 *      mac_cnt - Auto learning entries limit number
 * Output:
 *      None
 * Return:
 *      RT_ERR_OK                   - OK
 *      RT_ERR_FAILED               - Failed
 *      RT_ERR_SMI                  - SMI access error
 *      RT_ERR_LIMITED_L2ENTRY_NUM  - Invalid auto learning limit number
 * Note:
 *      The API can set system ASIC auto learning limit number from 0(disable learning)
 *      to 2112.
 */
rtksw_api_ret_t dal_rtl8367d_l2_limitSystemLearningCnt_set(rtksw_uint32 unit, rtksw_mac_cnt_t mac_cnt)
{
    rtksw_api_ret_t retVal;

    /* Check initialization state */
    RTKSW_CHK_INIT_STATE(unit);

    if (mac_cnt > rtksw_switch_maxLutAddrNumber_get(unit))
        return RT_ERR_LIMITED_L2ENTRY_NUM;

    if ((retVal = rtl8367d_setAsicReg(unit, RTL8367D_REG_LUT_SYS_LEARN_LIMITNO, mac_cnt)) != RT_ERR_OK)
        return retVal;

    return RT_ERR_OK;
}

/* Function Name:
 *      dal_rtl8367d_l2_limitSystemLearningCnt_get
 * Description:
 *      Get System auto learning limit number
 * Input:
 *      unit    - Unit ID
 * Output:
 *      pMac_cnt - Auto learning entries limit number
 * Return:
 *      RT_ERR_OK           - OK
 *      RT_ERR_FAILED       - Failed
 *      RT_ERR_SMI          - SMI access error
 *      RT_ERR_PORT_ID      - Invalid port number.
 * Note:
 *      The API can get system ASIC auto learning limit number.
 */
rtksw_api_ret_t dal_rtl8367d_l2_limitSystemLearningCnt_get(rtksw_uint32 unit, rtksw_mac_cnt_t *pMac_cnt)
{
    rtksw_api_ret_t retVal;

    /* Check initialization state */
    RTKSW_CHK_INIT_STATE(unit);

    if(NULL == pMac_cnt)
        return RT_ERR_NULL_POINTER;

    if ((retVal = rtl8367d_getAsicReg(unit, RTL8367D_REG_LUT_SYS_LEARN_LIMITNO, pMac_cnt)) != RT_ERR_OK)
        return retVal;

    return RT_ERR_OK;
}

/* Function Name:
 *      dal_rtl8367d_l2_limitLearningCntAction_set
 * Description:
 *      Configure auto learn over limit number action.
 * Input:
 *      unit    - Unit ID
 *      port    - Port id.
 *      action  - Auto learning entries limit number
 * Output:
 *      None
 * Return:
 *      RT_ERR_OK           - OK
 *      RT_ERR_FAILED       - Failed
 *      RT_ERR_SMI          - SMI access error
 *      RT_ERR_PORT_ID      - Invalid port number.
 *      RT_ERR_NOT_ALLOWED  - Invalid learn over action
 * Note:
 *      The API can set SA unknown packet action while auto learn limit number is over
 *      The action symbol as following:
 *      - RTKSW_LIMIT_LEARN_CNT_ACTION_DROP,
 *      - RTKSW_LIMIT_LEARN_CNT_ACTION_FORWARD,
 *      - RTKSW_LIMIT_LEARN_CNT_ACTION_TO_CPU,
 */
rtksw_api_ret_t dal_rtl8367d_l2_limitLearningCntAction_set(rtksw_uint32 unit, rtksw_port_t port, rtksw_l2_limitLearnCntAction_t action)
{
    rtksw_api_ret_t retVal;
    rtksw_uint32 data;

    /* Check initialization state */
    RTKSW_CHK_INIT_STATE(unit);

    if (port != RTKSW_WHOLE_SYSTEM)
        return RT_ERR_PORT_ID;

    if ( RTKSW_LIMIT_LEARN_CNT_ACTION_DROP == action )
        data = 1;
    else if ( RTKSW_LIMIT_LEARN_CNT_ACTION_FORWARD == action )
        data = 0;
    else if ( RTKSW_LIMIT_LEARN_CNT_ACTION_TO_CPU == action )
        data = 2;
    else
        return RT_ERR_NOT_ALLOWED;

    if ((retVal = rtl8367d_setAsicRegBits(unit, RTL8367D_REG_PORT_SECURITY_CTRL, RTL8367D_PORT_SECURITY_CTRL_MASK, data)) != RT_ERR_OK)
        return retVal;

    return RT_ERR_OK;
}

/* Function Name:
 *      dal_rtl8367d_l2_limitLearningCntAction_get
 * Description:
 *      Get auto learn over limit number action.
 * Input:
 *      unit    - Unit ID
 *      port    - Port id.
 * Output:
 *      pAction - Learn over action
 * Return:
 *      RT_ERR_OK           - OK
 *      RT_ERR_FAILED       - Failed
 *      RT_ERR_SMI          - SMI access error
 *      RT_ERR_PORT_ID      - Invalid port number.
 * Note:
 *      The API can get SA unknown packet action while auto learn limit number is over
 *      The action symbol as following:
 *      - RTKSW_LIMIT_LEARN_CNT_ACTION_DROP,
 *      - RTKSW_LIMIT_LEARN_CNT_ACTION_FORWARD,
 *      - RTKSW_LIMIT_LEARN_CNT_ACTION_TO_CPU,
 */
rtksw_api_ret_t dal_rtl8367d_l2_limitLearningCntAction_get(rtksw_uint32 unit, rtksw_port_t port, rtksw_l2_limitLearnCntAction_t *pAction)
{
    rtksw_api_ret_t retVal;
    rtksw_uint32 action;

    /* Check initialization state */
    RTKSW_CHK_INIT_STATE(unit);

    if (port != RTKSW_WHOLE_SYSTEM)
        return RT_ERR_PORT_ID;

    if(NULL == pAction)
        return RT_ERR_NULL_POINTER;

    if ((retVal = rtl8367d_getAsicRegBits(unit, RTL8367D_REG_PORT_SECURITY_CTRL, RTL8367D_PORT_SECURITY_CTRL_MASK, &action)) != RT_ERR_OK)
        return retVal;

    if ( 1 == action )
        *pAction = RTKSW_LIMIT_LEARN_CNT_ACTION_DROP;
    else if ( 0 == action )
        *pAction = RTKSW_LIMIT_LEARN_CNT_ACTION_FORWARD;
    else if ( 2 == action )
        *pAction = RTKSW_LIMIT_LEARN_CNT_ACTION_TO_CPU;
    else
    *pAction = action;

    return RT_ERR_OK;
}

/* Function Name:
 *      dal_rtl8367d_l2_limitSystemLearningCntAction_set
 * Description:
 *      Configure system auto learn over limit number action.
 * Input:
 *      unit    - Unit ID
 *      port    - Port id.
 *      action  - Auto learning entries limit number
 * Output:
 *      None
 * Return:
 *      RT_ERR_OK           - OK
 *      RT_ERR_FAILED       - Failed
 *      RT_ERR_SMI          - SMI access error
 *      RT_ERR_PORT_ID      - Invalid port number.
 *      RT_ERR_NOT_ALLOWED  - Invalid learn over action
 * Note:
 *      The API can set SA unknown packet action while auto learn limit number is over
 *      The action symbol as following:
 *      - RTKSW_LIMIT_LEARN_CNT_ACTION_DROP,
 *      - RTKSW_LIMIT_LEARN_CNT_ACTION_FORWARD,
 *      - RTKSW_LIMIT_LEARN_CNT_ACTION_TO_CPU,
 */
rtksw_api_ret_t dal_rtl8367d_l2_limitSystemLearningCntAction_set(rtksw_uint32 unit, rtksw_l2_limitLearnCntAction_t action)
{
    rtksw_api_ret_t retVal;
    rtksw_uint32 data;

    /* Check initialization state */
    RTKSW_CHK_INIT_STATE(unit);

    if ( RTKSW_LIMIT_LEARN_CNT_ACTION_DROP == action )
        data = 1;
    else if ( RTKSW_LIMIT_LEARN_CNT_ACTION_FORWARD == action )
        data = 0;
    else if ( RTKSW_LIMIT_LEARN_CNT_ACTION_TO_CPU == action )
        data = 2;
    else
        return RT_ERR_NOT_ALLOWED;

    if ((retVal = rtl8367d_setAsicRegBits(unit, RTL8367D_REG_LUT_LRN_SYS_LMT_CTRL, RTL8367D_LUT_SYSTEM_LEARN_OVER_ACT_MASK, data)) != RT_ERR_OK)
        return retVal;

    return RT_ERR_OK;
}

/* Function Name:
 *      dal_rtl8367d_l2_limitSystemLearningCntAction_get
 * Description:
 *      Get system auto learn over limit number action.
 * Input:
 *      unit    - Unit ID
 * Output:
 *      pAction - Learn over action
 * Return:
 *      RT_ERR_OK           - OK
 *      RT_ERR_FAILED       - Failed
 *      RT_ERR_SMI          - SMI access error
 *      RT_ERR_PORT_ID      - Invalid port number.
 * Note:
 *      The API can get SA unknown packet action while auto learn limit number is over
 *      The action symbol as following:
 *      - RTKSW_LIMIT_LEARN_CNT_ACTION_DROP,
 *      - RTKSW_LIMIT_LEARN_CNT_ACTION_FORWARD,
 *      - RTKSW_LIMIT_LEARN_CNT_ACTION_TO_CPU,
 */
rtksw_api_ret_t dal_rtl8367d_l2_limitSystemLearningCntAction_get(rtksw_uint32 unit, rtksw_l2_limitLearnCntAction_t *pAction)
{
    rtksw_api_ret_t retVal;
    rtksw_uint32 action;

    /* Check initialization state */
    RTKSW_CHK_INIT_STATE(unit);

    if(NULL == pAction)
        return RT_ERR_NULL_POINTER;

    if ((retVal = rtl8367d_getAsicRegBits(unit, RTL8367D_REG_LUT_LRN_SYS_LMT_CTRL, RTL8367D_LUT_SYSTEM_LEARN_OVER_ACT_MASK, &action)) != RT_ERR_OK)
        return retVal;

    if ( 1 == action )
        *pAction = RTKSW_LIMIT_LEARN_CNT_ACTION_DROP;
    else if ( 0 == action )
        *pAction = RTKSW_LIMIT_LEARN_CNT_ACTION_FORWARD;
    else if ( 2 == action )
        *pAction = RTKSW_LIMIT_LEARN_CNT_ACTION_TO_CPU;
    else
    *pAction = action;

    return RT_ERR_OK;
}

/* Function Name:
 *      dal_rtl8367d_l2_limitSystemLearningCntPortMask_set
 * Description:
 *      Configure system auto learn portmask
 * Input:
 *      unit        - Unit ID
 *      pPortmask   - Port Mask
 * Output:
 *      None
 * Return:
 *      RT_ERR_OK           - OK
 *      RT_ERR_FAILED       - Failed
 *      RT_ERR_SMI          - SMI access error
 *      RT_ERR_PORT_MASK    - Invalid port mask.
 * Note:
 *
 */
rtksw_api_ret_t dal_rtl8367d_l2_limitSystemLearningCntPortMask_set(rtksw_uint32 unit, rtksw_portmask_t *pPortmask)
{
    rtksw_api_ret_t retVal;
    rtksw_uint32 pmask;

    /* Check initialization state */
    RTKSW_CHK_INIT_STATE(unit);

    if(NULL == pPortmask)
        return RT_ERR_NULL_POINTER;

    /* Check port mask */
    RTKSW_CHK_PORTMASK_VALID(unit, pPortmask);

    if ((retVal = rtksw_switch_portmask_L2P_get(unit, pPortmask, &pmask)) != RT_ERR_OK)
        return retVal;

    if ((retVal = rtl8367d_setAsicRegBits(unit, RTL8367D_REG_LUT_LRN_SYS_LMT_CTRL, RTL8367D_LUT_SYSTEM_LEARN_PMASK_MASK, pmask & 0xff)) != RT_ERR_OK)
        return retVal;

    return RT_ERR_OK;
}

/* Function Name:
 *      dal_rtl8367d_l2_limitSystemLearningCntPortMask_get
 * Description:
 *      get system auto learn portmask
 * Input:
 *      unit    - Unit ID
 * Output:
 *      pPortmask - Port Mask
 * Return:
 *      RT_ERR_OK           - OK
 *      RT_ERR_FAILED       - Failed
 *      RT_ERR_SMI          - SMI access error
 *      RT_ERR_NULL_POINTER - Null pointer.
 * Note:
 *
 */
rtksw_api_ret_t dal_rtl8367d_l2_limitSystemLearningCntPortMask_get(rtksw_uint32 unit, rtksw_portmask_t *pPortmask)
{
    rtksw_api_ret_t retVal;
    rtksw_uint32 pmask;

    /* Check initialization state */
    RTKSW_CHK_INIT_STATE(unit);

    if(NULL == pPortmask)
        return RT_ERR_NULL_POINTER;

    if ((retVal = rtl8367d_getAsicRegBits(unit, RTL8367D_REG_LUT_LRN_SYS_LMT_CTRL, RTL8367D_LUT_SYSTEM_LEARN_PMASK_MASK, &pmask)) != RT_ERR_OK)
        return retVal;

    if ((retVal = rtksw_switch_portmask_P2L_get(unit, pmask, pPortmask)) != RT_ERR_OK)
        return retVal;

    return RT_ERR_OK;
}

/* Function Name:
 *      dal_rtl8367d_l2_learningCnt_get
 * Description:
 *      Get per-Port current auto learning number
 * Input:
 *      unit    - Unit ID
 *      port    - Port id.
 * Output:
 *      pMac_cnt - ASIC auto learning entries number
 * Return:
 *      RT_ERR_OK           - OK
 *      RT_ERR_FAILED       - Failed
 *      RT_ERR_SMI          - SMI access error
 *      RT_ERR_PORT_ID      - Invalid port number.
 * Note:
 *      The API can get per-port ASIC auto learning number
 */
rtksw_api_ret_t dal_rtl8367d_l2_learningCnt_get(rtksw_uint32 unit, rtksw_port_t port, rtksw_mac_cnt_t *pMac_cnt)
{
    rtksw_api_ret_t retVal;

    /* Check initialization state */
    RTKSW_CHK_INIT_STATE(unit);

    /* check port valid */
    RTKSW_CHK_PORT_VALID(unit, port);

    if(NULL == pMac_cnt)
        return RT_ERR_NULL_POINTER;

    if ((retVal = rtl8367d_getAsicReg(unit, RTL8367D_REG_L2_LRN_CNT_CTRL0 + rtksw_switch_port_L2P_get(unit, port), pMac_cnt)) != RT_ERR_OK)
        return retVal;

    return RT_ERR_OK;
}

/* Function Name:
 *      dal_rtl8367d_l2_floodPortMask_set
 * Description:
 *      Set flooding portmask
 * Input:
 *      unit            - Unit ID
 *      type            - flooding type.
 *      pFlood_portmask - flooding porkmask
 * Output:
 *      None
 * Return:
 *      RT_ERR_OK           - OK
 *      RT_ERR_FAILED       - Failed
 *      RT_ERR_SMI          - SMI access error
 *      RT_ERR_PORT_MASK    - Invalid portmask.
 *      RT_ERR_INPUT        - Invalid input parameters.
 * Note:
 *      This API can set the flooding mask.
 *      The flooding type is as following:
 *      - FLOOD_UNKNOWNDA
 *      - FLOOD_UNKNOWNMC
 *      - FLOOD_BC
 */
rtksw_api_ret_t dal_rtl8367d_l2_floodPortMask_set(rtksw_uint32 unit, rtksw_l2_flood_type_t floood_type, rtksw_portmask_t *pFlood_portmask)
{
    rtksw_api_ret_t retVal;
    rtksw_uint32 pmask;

    /* Check initialization state */
    RTKSW_CHK_INIT_STATE(unit);

    if (floood_type >= FLOOD_END)
        return RT_ERR_INPUT;

    /* check port valid */
    RTKSW_CHK_PORTMASK_VALID(unit, pFlood_portmask);

    /* Get Physical port mask */
    if ((retVal = rtksw_switch_portmask_L2P_get(unit, pFlood_portmask, &pmask))!=RT_ERR_OK)
        return retVal;

    switch (floood_type)
    {
        case FLOOD_UNKNOWNDA:
            if ((retVal = rtl8367d_setAsicReg(unit, RTL8367D_REG_UNDA_FLOODING_PMSK, pmask)) != RT_ERR_OK)
                return retVal;
            break;
        case FLOOD_UNKNOWNMC:
            if ((retVal = rtl8367d_setAsicReg(unit, RTL8367D_REG_UNMCAST_FLOADING_PMSK, pmask)) != RT_ERR_OK)
                return retVal;
            break;
        case FLOOD_BC:
            if ((retVal = rtl8367d_setAsicReg(unit, RTL8367D_REG_BCAST_FLOADING_PMSK, pmask)) != RT_ERR_OK)
                return retVal;
            break;
        default:
            break;
    }

    return RT_ERR_OK;
}

/* Function Name:
 *      dal_rtl8367d_l2_floodPortMask_get
 * Description:
 *      Get flooding portmask
 * Input:
 *      unit    - Unit ID
 *      type    - flooding type.
 * Output:
 *      pFlood_portmask - flooding porkmask
 * Return:
 *      RT_ERR_OK           - OK
 *      RT_ERR_FAILED       - Failed
 *      RT_ERR_SMI          - SMI access error
 *      RT_ERR_PORT_ID      - Invalid port number.
 * Note:
 *      This API can get the flooding mask.
 *      The flooding type is as following:
 *      - FLOOD_UNKNOWNDA
 *      - FLOOD_UNKNOWNMC
 *      - FLOOD_BC
 */
rtksw_api_ret_t dal_rtl8367d_l2_floodPortMask_get(rtksw_uint32 unit, rtksw_l2_flood_type_t floood_type, rtksw_portmask_t *pFlood_portmask)
{
    rtksw_api_ret_t retVal;
    rtksw_uint32 pmask;

    /* Check initialization state */
    RTKSW_CHK_INIT_STATE(unit);

    if (floood_type >= FLOOD_END)
        return RT_ERR_INPUT;

    if(NULL == pFlood_portmask)
        return RT_ERR_NULL_POINTER;

    switch (floood_type)
    {
        case FLOOD_UNKNOWNDA:
            if ((retVal = rtl8367d_getAsicReg(unit, RTL8367D_REG_UNDA_FLOODING_PMSK, &pmask)) != RT_ERR_OK)
                return retVal;
            break;
        case FLOOD_UNKNOWNMC:
            if ((retVal = rtl8367d_getAsicReg(unit, RTL8367D_REG_UNMCAST_FLOADING_PMSK, &pmask)) != RT_ERR_OK)
                return retVal;
            break;
        case FLOOD_BC:
            if ((retVal = rtl8367d_getAsicReg(unit, RTL8367D_REG_BCAST_FLOADING_PMSK, &pmask)) != RT_ERR_OK)
                return retVal;
            break;
        default:
            break;
    }

    /* Get Logical port mask */
    if ((retVal = rtksw_switch_portmask_P2L_get(unit, pmask, pFlood_portmask))!=RT_ERR_OK)
        return retVal;

    return RT_ERR_OK;
}

/* Function Name:
 *      dal_rtl8367d_l2_localPktPermit_set
 * Description:
 *      Set permittion of frames if source port and destination port are the same.
 * Input:
 *      unit    - Unit ID
 *      port    - Port id.
 *      permit  - permittion status
 * Output:
 *      None
 * Return:
 *      RT_ERR_OK           - OK
 *      RT_ERR_FAILED       - Failed
 *      RT_ERR_SMI          - SMI access error
 *      RT_ERR_PORT_ID      - Invalid port number.
 *      RT_ERR_ENABLE       - Invalid permit value.
 * Note:
 *      This API is setted to permit frame if its source port is equal to destination port.
 */
rtksw_api_ret_t dal_rtl8367d_l2_localPktPermit_set(rtksw_uint32 unit, rtksw_port_t port, rtksw_enable_t permit)
{
    rtksw_api_ret_t retVal;

    /* Check initialization state */
    RTKSW_CHK_INIT_STATE(unit);

    /* check port valid */
    RTKSW_CHK_PORT_VALID(unit, port);

    if (permit >= RTKSW_ENABLE_END)
        return RT_ERR_ENABLE;

    if ((retVal = rtl8367d_setAsicRegBit(unit, RTL8367D_REG_SOURCE_PORT_PERMIT, rtksw_switch_port_L2P_get(unit, port), permit)) != RT_ERR_OK)
        return retVal;

    return RT_ERR_OK;
}

/* Function Name:
 *      dal_rtl8367d_l2_localPktPermit_get
 * Description:
 *      Get permittion of frames if source port and destination port are the same.
 * Input:
 *      unit    - Unit ID
 *      port    - Port id.
 * Output:
 *      pPermit - permittion status
 * Return:
 *      RT_ERR_OK           - OK
 *      RT_ERR_FAILED       - Failed
 *      RT_ERR_SMI          - SMI access error
 *      RT_ERR_PORT_ID      - Invalid port number.
 * Note:
 *      This API is to get permittion status for frames if its source port is equal to destination port.
 */
rtksw_api_ret_t dal_rtl8367d_l2_localPktPermit_get(rtksw_uint32 unit, rtksw_port_t port, rtksw_enable_t *pPermit)
{
    rtksw_api_ret_t retVal;

    /* Check initialization state */
    RTKSW_CHK_INIT_STATE(unit);

    /* check port valid */
    RTKSW_CHK_PORT_VALID(unit, port);

    if(NULL == pPermit)
        return RT_ERR_NULL_POINTER;

    if ((retVal = rtl8367d_getAsicRegBit(unit, RTL8367D_REG_SOURCE_PORT_PERMIT, rtksw_switch_port_L2P_get(unit, port), pPermit)) != RT_ERR_OK)
        return retVal;

    return RT_ERR_OK;
}

/* Function Name:
 *      dal_rtl8367d_l2_aging_set
 * Description:
 *      Set LUT agging out speed
 * Input:
 *      unit        - Unit ID
 *      aging_time  - Agging out time.
 * Output:
 *      None
 * Return:
 *      RT_ERR_OK               - OK
 *      RT_ERR_FAILED           - Failed
 *      RT_ERR_SMI              - SMI access error
 *      RT_ERR_OUT_OF_RANGE     - input out of range.
 * Note:
 *      The API can set LUT agging out period for each entry and the range is from 45s to 458s.
 */
rtksw_api_ret_t dal_rtl8367d_l2_aging_set(rtksw_uint32 unit, rtksw_l2_age_time_t aging_time)
{
    rtksw_api_ret_t retVal;

    if(aging_time > RTL8367D_LUTAGINGTIMER_MAX)
        return RT_ERR_OUT_OF_RANGE;

    if((retVal = rtl8367d_setAsicReg(unit, RTL8367D_REG_LUT_CFG2, aging_time * 10)) != RT_ERR_OK)
        return retVal;

    return RT_ERR_OK;
}

/* Function Name:
 *      dal_rtl8367d_l2_aging_get
 * Description:
 *      Get LUT agging out time
 * Input:
 *      unit    - Unit ID
 * Output:
 *      pEnable - Aging status
 * Return:
 *      RT_ERR_OK           - OK
 *      RT_ERR_FAILED       - Failed
 *      RT_ERR_SMI          - SMI access error
 *      RT_ERR_PORT_ID      - Invalid port number.
 * Note:
 *      The API can get LUT agging out period for each entry.
 */
rtksw_api_ret_t dal_rtl8367d_l2_aging_get(rtksw_uint32 unit, rtksw_l2_age_time_t *pAging_time)
{
    rtksw_api_ret_t retVal;
    rtksw_uint32 pAge;

    if((retVal = rtl8367d_getAsicReg(unit, RTL8367D_REG_LUT_CFG2, &pAge)) != RT_ERR_OK)
        return retVal;

    *pAging_time = pAge / 10;

    return RT_ERR_OK;
}

/* Function Name:
 *      dal_rtl8367d_l2_ipMcastAddrLookup_set
 * Description:
 *      Set Lut IP multicast lookup function
 * Input:
 *      unit    - Unit ID
 *      type    - Lookup type for IPMC packet.
 * Output:
 *      None.
 * Return:
 *      RT_ERR_OK          - OK
 *      RT_ERR_FAILED      - Failed
 *      RT_ERR_SMI         - SMI access error
 * Note:
 *      LOOKUP_MAC      - Lookup by MAC address
 *      LOOKUP_IP       - Lookup by IP address
 */
rtksw_api_ret_t dal_rtl8367d_l2_ipMcastAddrLookup_set(rtksw_uint32 unit, rtksw_l2_ipmc_lookup_type_t type)
{
    rtksw_api_ret_t retVal;

    /* Check initialization state */
    RTKSW_CHK_INIT_STATE(unit);

    if(type == LOOKUP_MAC)
    {
        if((retVal = rtl8367d_setAsicRegBit(unit, RTL8367D_REG_LUT_CFG, RTL8367D_LUT_IPMC_HASH_OFFSET, RTKSW_DISABLED)) != RT_ERR_OK)
            return retVal;
    }
    else if(type == LOOKUP_IP)
    {
        if((retVal = rtl8367d_setAsicRegBit(unit, RTL8367D_REG_LUT_CFG, RTL8367D_LUT_IPMC_HASH_OFFSET, RTKSW_ENABLED)) != RT_ERR_OK)
            return retVal;
    }
    else
        return RT_ERR_INPUT;

    return RT_ERR_OK;
}

/* Function Name:
 *      dal_rtl8367d_l2_ipMcastAddrLookup_get
 * Description:
 *      Get Lut IP multicast lookup function
 * Input:
 *      unit    - Unit ID
 * Output:
 *      pType - Lookup type for IPMC packet.
 * Return:
 *      RT_ERR_OK          - OK
 *      RT_ERR_FAILED      - Failed
 *      RT_ERR_SMI         - SMI access error
 * Note:
 *      None.
 */
rtksw_api_ret_t dal_rtl8367d_l2_ipMcastAddrLookup_get(rtksw_uint32 unit, rtksw_l2_ipmc_lookup_type_t *pType)
{
    rtksw_api_ret_t       retVal;
    rtksw_uint32          enabled;

    /* Check initialization state */
    RTKSW_CHK_INIT_STATE(unit);

    if(NULL == pType)
        return RT_ERR_NULL_POINTER;

    if((retVal = rtl8367d_getAsicRegBit(unit, RTL8367D_REG_LUT_CFG, RTL8367D_LUT_IPMC_HASH_OFFSET, &enabled)) != RT_ERR_OK)
        return retVal;

    if(enabled == RTKSW_ENABLED)
        *pType = LOOKUP_IP;
    else
        *pType = LOOKUP_MAC;

    return RT_ERR_OK;
}

/* Function Name:
 *      dal_rtl8367d_l2_ipMcastGroupEntry_add
 * Description:
 *      Add an IP Multicast entry to group table
 * Input:
 *      unit        - Unit ID
 *      ip_addr     - IP address
 *      vid         - VLAN ID
 *      pPortmask   - portmask
 * Output:
 *      None.
 * Return:
 *      RT_ERR_OK          - OK
 *      RT_ERR_FAILED      - Failed
 *      RT_ERR_SMI         - SMI access error
 *      RT_ERR_TBL_FULL    - Table Full
 * Note:
 *      Add an entry to IP Multicast Group table.
 */
rtksw_api_ret_t dal_rtl8367d_l2_ipMcastGroupEntry_add(rtksw_uint32 unit, ipaddr_t ip_addr, rtksw_uint32 vid, rtksw_portmask_t *pPortmask)
{
    rtksw_uint32      empty_idx = 0xFFFF;
    rtksw_int32       index;
    ipaddr_t        group_addr;
    rtksw_uint32      pmask;
    rtksw_uint32      valid;
    rtksw_uint32      physicalPortmask;
    rtksw_api_ret_t   retVal;

    /* Check initialization state */
    RTKSW_CHK_INIT_STATE(unit);

    if(vid)//remove warning
    {
    }

    if(NULL == pPortmask)
        return RT_ERR_NULL_POINTER;

    if((ip_addr & 0xF0000000) != 0xE0000000)
        return RT_ERR_INPUT;

    /* Get Physical port mask */
    if ((retVal = rtksw_switch_portmask_L2P_get(unit, pPortmask, &physicalPortmask))!=RT_ERR_OK)
        return retVal;

    for(index = 0; index <= RTL8367D_LUT_IPMCGRP_TABLE_MAX; index++)
    {
        if ((retVal = _rtl8367d_getLutIPMCGroup(unit, (rtksw_uint32)index, &group_addr, &pmask, &valid))!=RT_ERR_OK)
            return retVal;

        if( (valid == RTKSW_ENABLED) && (group_addr == ip_addr))
        {
            if(pmask != physicalPortmask)
            {
                pmask = physicalPortmask;
                if ((retVal = _rtl8367d_setLutIPMCGroup(unit, index, ip_addr, pmask, valid))!=RT_ERR_OK)
                    return retVal;
            }

            return RT_ERR_OK;
        }

        if( (valid == RTKSW_DISABLED) && (empty_idx == 0xFFFF) ) /* Unused */
            empty_idx = (rtksw_uint32)index;
    }

    if(empty_idx == 0xFFFF)
        return RT_ERR_TBL_FULL;

    pmask = physicalPortmask;
    if ((retVal = _rtl8367d_setLutIPMCGroup(unit, empty_idx, ip_addr, pmask, RTKSW_ENABLED))!=RT_ERR_OK)
        return retVal;

    return RT_ERR_OK;
}

/* Function Name:
 *      dal_rtl8367d_l2_ipMcastGroupEntry_del
 * Description:
 *      Delete an entry from IP Multicast group table
 * Input:
 *      unit        - Unit ID
 *      ip_addr     - IP address
 *      vid         - VLAN ID
 * Output:
 *      None.
 * Return:
 *      RT_ERR_OK          - OK
 *      RT_ERR_FAILED      - Failed
 *      RT_ERR_SMI         - SMI access error
 *      RT_ERR_TBL_FULL    - Table Full
 * Note:
 *      Delete an entry from IP Multicast group table.
 */
rtksw_api_ret_t dal_rtl8367d_l2_ipMcastGroupEntry_del(rtksw_uint32 unit, ipaddr_t ip_addr, rtksw_uint32 vid)
{
    rtksw_int32       index;
    ipaddr_t        group_addr;
    rtksw_uint32      pmask;
    rtksw_uint32      valid;
    rtksw_api_ret_t   retVal;

    /* Check initialization state */
    RTKSW_CHK_INIT_STATE(unit);

    if(vid)//remove warning
    {
    }

    if((ip_addr & 0xF0000000) != 0xE0000000)
        return RT_ERR_INPUT;

    for(index = 0; index <= RTL8367D_LUT_IPMCGRP_TABLE_MAX; index++)
    {
        if ((retVal = _rtl8367d_getLutIPMCGroup(unit, (rtksw_uint32)index, &group_addr, &pmask, &valid))!=RT_ERR_OK)
            return retVal;

        if( (valid == RTKSW_ENABLED) && (group_addr == ip_addr) )
        {
            group_addr = 0xE0000000;
            pmask = 0;
            if ((retVal = _rtl8367d_setLutIPMCGroup(unit, index, group_addr, pmask, RTKSW_DISABLED))!=RT_ERR_OK)
                return retVal;

            return RT_ERR_OK;
        }
    }

    return RT_ERR_FAILED;
}

/* Function Name:
 *      dal_rtl8367d_l2_ipMcastGroupEntry_get
 * Description:
 *      get an entry from IP Multicast group table
 * Input:
 *      unit        - Unit ID
 *      ip_addr     - IP address
 *      vid         - VLAN ID
 * Output:
 *      pPortmask   - member port mask
 * Return:
 *      RT_ERR_OK          - OK
 *      RT_ERR_FAILED      - Failed
 *      RT_ERR_SMI         - SMI access error
 *      RT_ERR_TBL_FULL    - Table Full
 * Note:
 *      Delete an entry from IP Multicast group table.
 */
rtksw_api_ret_t dal_rtl8367d_l2_ipMcastGroupEntry_get(rtksw_uint32 unit, ipaddr_t ip_addr, rtksw_uint32 vid, rtksw_portmask_t *pPortmask)
{
    rtksw_int32       index;
    ipaddr_t        group_addr;
    rtksw_uint32      valid;
    rtksw_uint32      pmask;
    rtksw_api_ret_t   retVal;

    /* Check initialization state */
    RTKSW_CHK_INIT_STATE(unit);

    if(vid)//remove warning
    {
    }

    if((ip_addr & 0xF0000000) != 0xE0000000)
        return RT_ERR_INPUT;

    if(NULL == pPortmask)
        return RT_ERR_NULL_POINTER;

    for(index = 0; index <= RTL8367D_LUT_IPMCGRP_TABLE_MAX; index++)
    {
        if ((retVal = _rtl8367d_getLutIPMCGroup(unit, (rtksw_uint32)index, &group_addr, &pmask, &valid))!=RT_ERR_OK)
            return retVal;

        if( (valid == RTKSW_ENABLED) && (group_addr == ip_addr) )
        {
            if ((retVal = rtksw_switch_portmask_P2L_get(unit, pmask, pPortmask))!=RT_ERR_OK)
                return retVal;

            return RT_ERR_OK;
        }
    }

    return RT_ERR_FAILED;
}

/* Function Name:
 *      dal_rtl8367d_l2_entry_get
 * Description:
 *      Get LUT unicast entry.
 * Input:
 *      unit        - Unit ID
 *      pL2_entry   - Index field in the structure.
 * Output:
 *      pL2_entry - other fields such as MAC, port, age...
 * Return:
 *      RT_ERR_OK               - OK
 *      RT_ERR_FAILED           - Failed
 *      RT_ERR_SMI              - SMI access error
 *      RT_ERR_L2_EMPTY_ENTRY   - Empty LUT entry.
 *      RT_ERR_INPUT            - Invalid input parameters.
 * Note:
 *      This API is used to get address by index from 0~2111.
 */
rtksw_api_ret_t dal_rtl8367d_l2_entry_get(rtksw_uint32 unit, rtksw_l2_addr_table_t *pL2_entry)
{
    rtksw_api_ret_t retVal;
    rtksw_uint32 method;
    rtl8367d_luttb l2Table;

    /* Check initialization state */
    RTKSW_CHK_INIT_STATE(unit);

    if (pL2_entry->index >= rtksw_switch_maxLutAddrNumber_get(unit))
        return RT_ERR_INPUT;

    osal_memset(&l2Table, 0x00, sizeof(rtl8367d_luttb));
    l2Table.address= pL2_entry->index;
    method = RTL8367D_LUTREADMETHOD_ADDRESS;
    if ((retVal = _rtl8367d_getL2LookupTb(unit, method, &l2Table)) != RT_ERR_OK)
        return retVal;

    if ((pL2_entry->index>0x800)&&(l2Table.lookup_hit==0))
         return RT_ERR_L2_EMPTY_ENTRY;

    if(l2Table.l3lookup)
    {
        osal_memset(&pL2_entry->mac, 0, sizeof(rtksw_mac_t));
        pL2_entry->is_ipmul  = l2Table.l3lookup;
        pL2_entry->sip       = l2Table.sip;
        pL2_entry->dip       = l2Table.dip;
        pL2_entry->is_static = l2Table.nosalearn;

        /* Get Logical port mask */
        if ((retVal = rtksw_switch_portmask_P2L_get(unit, l2Table.mbr, &(pL2_entry->portmask)))!=RT_ERR_OK)
            return retVal;

        pL2_entry->fid       = 0;
        pL2_entry->age       = 0;
        pL2_entry->sa_block  = 0;
        pL2_entry->is_ipvidmul = 0;
        pL2_entry->l3_vid      = 0;

    }
    else if(l2Table.mac.octet[0]&0x01)
    {
        osal_memset(&pL2_entry->sip, 0, sizeof(ipaddr_t));
        osal_memset(&pL2_entry->dip, 0, sizeof(ipaddr_t));
        pL2_entry->mac.octet[0] = l2Table.mac.octet[0];
        pL2_entry->mac.octet[1] = l2Table.mac.octet[1];
        pL2_entry->mac.octet[2] = l2Table.mac.octet[2];
        pL2_entry->mac.octet[3] = l2Table.mac.octet[3];
        pL2_entry->mac.octet[4] = l2Table.mac.octet[4];
        pL2_entry->mac.octet[5] = l2Table.mac.octet[5];
        pL2_entry->is_ipmul  = l2Table.l3lookup;
        pL2_entry->is_static = l2Table.nosalearn;

        /* Get Logical port mask */
        if ((retVal = rtksw_switch_portmask_P2L_get(unit, l2Table.mbr, &(pL2_entry->portmask)))!=RT_ERR_OK)
            return retVal;

        pL2_entry->ivl       = l2Table.ivl_svl;
        if(l2Table.ivl_svl == 1) /* IVL */
        {
            pL2_entry->cvid      = l2Table.cvid_fid;
            pL2_entry->fid       = 0;
        }
        else /* SVL*/
        {
            pL2_entry->cvid      = 0;
            pL2_entry->fid       = l2Table.cvid_fid;
        }
        pL2_entry->age       = 0;
        pL2_entry->is_ipvidmul = 0;
        pL2_entry->l3_vid      = 0;
    }
    else if((l2Table.age != 0)||(l2Table.nosalearn == 1))
    {
        osal_memset(&pL2_entry->sip, 0, sizeof(ipaddr_t));
        osal_memset(&pL2_entry->dip, 0, sizeof(ipaddr_t));
        pL2_entry->mac.octet[0] = l2Table.mac.octet[0];
        pL2_entry->mac.octet[1] = l2Table.mac.octet[1];
        pL2_entry->mac.octet[2] = l2Table.mac.octet[2];
        pL2_entry->mac.octet[3] = l2Table.mac.octet[3];
        pL2_entry->mac.octet[4] = l2Table.mac.octet[4];
        pL2_entry->mac.octet[5] = l2Table.mac.octet[5];
        pL2_entry->is_ipmul  = l2Table.l3lookup;
        pL2_entry->is_static = l2Table.nosalearn;

        /* Get Logical port mask */
        if ((retVal = rtksw_switch_portmask_P2L_get(unit, 1<<(l2Table.spa), &(pL2_entry->portmask)))!=RT_ERR_OK)
            return retVal;

        pL2_entry->ivl       = l2Table.ivl_svl;
        if(l2Table.ivl_svl == 1) /* IVL */
        {
            pL2_entry->cvid      = l2Table.cvid_fid;
            pL2_entry->fid       = 0;
        }
        else /* SVL*/
        {
            pL2_entry->cvid      = 0;
            pL2_entry->fid       = l2Table.cvid_fid;
        }

        pL2_entry->age       = l2Table.age;
        pL2_entry->is_ipvidmul = 0;
        pL2_entry->l3_vid      = 0;
    }
    else
       return RT_ERR_L2_EMPTY_ENTRY;

    return RT_ERR_OK;
}

/* Function Name:
 *      dal_rtl8367d_l2_lookupHitIsolationAction_set
 * Description:
 *      Set action of lookup hit & isolation.
 * Input:
 *      unit        - Unit ID
 *      action      - The action
 * Output:
 *      None.
 * Return:
 *      RT_ERR_OK                   - OK
 *      RT_ERR_FAILED               - Failed
 *      RT_ERR_SMI                  - SMI access error
 *      RT_ERR_INPUT                - Invalid input parameters.
 * Note:
 *      This API is used to configure the action of packet which is lookup hit
 *      in L2 table but the destination port/portmask are not in the port isolation
 *      group.
 */
rtksw_api_ret_t dal_rtl8367d_l2_lookupHitIsolationAction_set(rtksw_uint32 unit, rtksw_l2_lookupHitIsolationAction_t action)
{
    rtksw_api_ret_t retVal;
    rtksw_uint32 regData;

    /* Check initialization state */
    RTKSW_CHK_INIT_STATE(unit);

    switch (action)
    {
        case L2_LOOKUPHIT_ISOACTION_NOP:
            regData = 0;
            break;
        case L2_LOOKUPHIT_ISOACTION_UNKNOWN:
            regData = 1;
            break;
        default:
            return RT_ERR_INPUT;
    }

    if ((retVal = rtl8367d_setAsicRegBit(unit, RTL8367D_REG_LOOKUP_HIT_ISO_ACT, RTL8367D_LOOKUP_HIT_ISO_ACT_OFFSET, regData)) != RT_ERR_OK)
        return retVal;

    return RT_ERR_OK;
}

/* Function Name:
 *      dal_rtl8367d_l2_lookupHitIsolationAction_get
 * Description:
 *      Get action of lookup hit & isolation.
 * Input:
 *      unit    - Unit ID
 * Output:
 *      pAction         - The action
 * Return:
 *      RT_ERR_OK                   - OK
 *      RT_ERR_FAILED               - Failed
 *      RT_ERR_NULL_POINTER         - Null pointer
 *      RT_ERR_SMI                  - SMI access error
 *      RT_ERR_INPUT                - Invalid input parameters.
 * Note:
 *      This API is used to get the action of packet which is lookup hit
 *      in L2 table but the destination port/portmask are not in the port isolation
 *      group.
 */
rtksw_api_ret_t dal_rtl8367d_l2_lookupHitIsolationAction_get(rtksw_uint32 unit, rtksw_l2_lookupHitIsolationAction_t *pAction)
{
    rtksw_api_ret_t retVal;
    rtksw_uint32 regData;

    /* Check initialization state */
    RTKSW_CHK_INIT_STATE(unit);

    if (pAction == NULL)
        return RT_ERR_NULL_POINTER;

    if ((retVal = rtl8367d_getAsicRegBit(unit, RTL8367D_REG_LOOKUP_HIT_ISO_ACT, RTL8367D_LOOKUP_HIT_ISO_ACT_OFFSET, &regData)) != RT_ERR_OK)
        return retVal;

    switch (regData)
    {
        case 0:
            *pAction = L2_LOOKUPHIT_ISOACTION_NOP;
            break;
        case 1:
            *pAction = L2_LOOKUPHIT_ISOACTION_UNKNOWN;
            break;
        default:
            return RT_ERR_FAILED;
    }

    return RT_ERR_OK;
}
