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
 * Feature : Port trunking related functions
 *
 */

#include "rtl8367c_asicdrv_trunking.h"
/* Function Name:
 *      rtl8367c_setAsicTrunkingMode
 * Description:
 *      Set port trunking mode
 * Input:
 *      unit    - Unit ID
 *      mode    - 1:dumb 0:user defined
 * Output:
 *      None
 * Return:
 *      RT_ERR_OK   - Success
 *      RT_ERR_SMI  - SMI access error
 * Note:
 *      None
 */
ret_t rtl8367c_setAsicTrunkingMode(rtksw_uint32 unit, rtksw_uint32 mode)
{
    return rtl8367c_setAsicRegBit(unit, RTL8367C_REG_PORT_TRUNK_CTRL, RTL8367C_PORT_TRUNK_DUMB_OFFSET, mode);
}
/* Function Name:
 *      rtl8367c_getAsicTrunkingMode
 * Description:
 *      Get port trunking mode
 * Input:
 *      unit    - Unit ID
 *      pMode   - 1:dumb 0:user defined
 * Output:
 *      None
 * Return:
 *      RT_ERR_OK   - Success
 *      RT_ERR_SMI  - SMI access error
 * Note:
 *      None
 */
ret_t rtl8367c_getAsicTrunkingMode(rtksw_uint32 unit, rtksw_uint32* pMode)
{
    return rtl8367c_getAsicRegBit(unit, RTL8367C_REG_PORT_TRUNK_CTRL, RTL8367C_PORT_TRUNK_DUMB_OFFSET, pMode);
}
/* Function Name:
 *      rtl8367c_setAsicTrunkingFc
 * Description:
 *      Set port trunking flow control
 * Input:
 *      unit        - Unit ID
 *      group       - Trunk Group ID
 *      enabled     - 0:disable, 1:enable
 * Output:
 *      None
 * Return:
 *      RT_ERR_OK   - Success
 *      RT_ERR_SMI  - SMI access error
 * Note:
 *      None
 */
ret_t rtl8367c_setAsicTrunkingFc(rtksw_uint32 unit, rtksw_uint32 group, rtksw_uint32 enabled)
{
    ret_t       retVal;

    if(group > RTL8367C_MAX_TRUNK_GID)
        return RT_ERR_LA_TRUNK_ID;

    if((retVal = rtl8367c_setAsicRegBit(unit, RTL8367C_REG_PORT_TRUNK_DROP_CTRL, RTL8367C_PORT_TRUNK_DROP_CTRL_OFFSET, RTKSW_ENABLED)) != RT_ERR_OK)
        return retVal;

    return rtl8367c_setAsicRegBit(unit, RTL8367C_REG_PORT_TRUNK_FLOWCTRL, (RTL8367C_EN_FLOWCTRL_TG0_OFFSET + group), enabled);
}
/* Function Name:
 *      rtl8367c_getAsicTrunkingFc
 * Description:
 *      Get port trunking flow control
 * Input:
 *      unit        - Unit ID
 *      group       - Trunk Group ID
 *      pEnabled    - 0:disable, 1:enable
 * Output:
 *      None
 * Return:
 *      RT_ERR_OK   - Success
 *      RT_ERR_SMI  - SMI access error
 * Note:
 *      None
 */
ret_t rtl8367c_getAsicTrunkingFc(rtksw_uint32 unit, rtksw_uint32 group, rtksw_uint32* pEnabled)
{
    if(group > RTL8367C_MAX_TRUNK_GID)
        return RT_ERR_LA_TRUNK_ID;

    return rtl8367c_getAsicRegBit(unit, RTL8367C_REG_PORT_TRUNK_FLOWCTRL, (RTL8367C_EN_FLOWCTRL_TG0_OFFSET + group), pEnabled);
}
/* Function Name:
 *      rtl8367c_setAsicTrunkingGroup
 * Description:
 *      Set trunking group available port mask
 * Input:
 *      unit        - Unit ID
 *      group       - Trunk Group ID
 *      portmask    - Logic trunking enable port mask, max 4 ports
 * Output:
 *      None
 * Return:
 *      RT_ERR_OK   - Success
 *      RT_ERR_SMI  - SMI access error
 * Note:
 *      None
 */
ret_t rtl8367c_setAsicTrunkingGroup(rtksw_uint32 unit, rtksw_uint32 group, rtksw_uint32 portmask)
{
    if(group > RTL8367C_MAX_TRUNK_GID)
        return RT_ERR_LA_TRUNK_ID;
    return rtl8367c_setAsicRegBits(unit, RTL8367C_REG_PORT_TRUNK_GROUP_MASK, RTL8367C_PORT_TRUNK_GROUP0_MASK_MASK << (group * 4), portmask);
}
/* Function Name:
 *      rtl8367c_getAsicTrunkingGroup
 * Description:
 *      Get trunking group available port mask
 * Input:
 *      unit    - Unit ID
 *      group       - Trunk Group ID
 * Output:
 *      pPortmask   - Logic trunking enable port mask, max 4 ports
 * Return:
 *      RT_ERR_OK   - Success
 *      RT_ERR_SMI  - SMI access error
 * Note:
 *      None
 */
ret_t rtl8367c_getAsicTrunkingGroup(rtksw_uint32 unit, rtksw_uint32 group, rtksw_uint32* pPortmask)
{
    if(group > RTL8367C_MAX_TRUNK_GID)
        return RT_ERR_LA_TRUNK_ID;

    return rtl8367c_getAsicRegBits(unit, RTL8367C_REG_PORT_TRUNK_GROUP_MASK, RTL8367C_PORT_TRUNK_GROUP0_MASK_MASK << (group * 4), pPortmask);
}
/* Function Name:
 *      rtl8367c_setAsicTrunkingFlood
 * Description:
 *      Set port trunking flood function
 * Input:
 *      unit        - Unit ID
 *      enabled     - Port trunking flooding function 0:disable 1:enable
 * Output:
 *      None
 * Return:
 *      RT_ERR_OK   - Success
 *      RT_ERR_SMI  - SMI access error
 * Note:
 *      None
 */
ret_t rtl8367c_setAsicTrunkingFlood(rtksw_uint32 unit, rtksw_uint32 enabled)
{
    return rtl8367c_setAsicRegBit(unit, RTL8367C_REG_PORT_TRUNK_CTRL, RTL8367C_PORT_TRUNK_FLOOD_OFFSET, enabled);
}
/* Function Name:
 *      rtl8367c_getAsicTrunkingFlood
 * Description:
 *      Get port trunking flood function
 * Input:
 *      unit        - Unit ID
 *      pEnabled    - Port trunking flooding function 0:disable 1:enable
 * Output:
 *      None
 * Return:
 *      RT_ERR_OK   - Success
 *      RT_ERR_SMI  - SMI access error
 * Note:
 *      None
 */
ret_t rtl8367c_getAsicTrunkingFlood(rtksw_uint32 unit, rtksw_uint32* pEnabled)
{
    return rtl8367c_getAsicRegBit(unit, RTL8367C_REG_PORT_TRUNK_CTRL, RTL8367C_PORT_TRUNK_FLOOD_OFFSET, pEnabled);
}
/* Function Name:
 *      rtl8367c_setAsicTrunkingHashSelect
 * Description:
 *      Set port trunking hash select sources
 * Input:
 *      unit        - Unit ID
 *      hashsel     - hash sources mask
 * Output:
 *      None
 * Return:
 *      RT_ERR_OK   - Success
 *      RT_ERR_SMI  - SMI access error
 * Note:
 *      7 bits mask for link aggregation group0 hash parameter selection {DIP, SIP, DMAC, SMAC, SPA}
 *      0b0000001: SPA
 *      0b0000010: SMAC
 *      0b0000100: DMAC
 *      0b0001000: SIP
 *      0b0010000: DIP
 *      0b0100000: TCP/UDP Source Port
 *      0b1000000: TCP/UDP Destination Port
 */
ret_t rtl8367c_setAsicTrunkingHashSelect(rtksw_uint32 unit, rtksw_uint32 hashsel)
{
    return rtl8367c_setAsicRegBits(unit, RTL8367C_REG_PORT_TRUNK_CTRL, RTL8367C_PORT_TRUNK_HASH_MASK, hashsel);
}
/* Function Name:
 *      rtl8367c_getAsicTrunkingHashSelect
 * Description:
 *      Get port trunking hash select sources
 * Input:
 *      unit        - Unit ID
 *      pHashsel    - hash sources mask
 * Output:
 *      None
 * Return:
 *      RT_ERR_OK   - Success
 *      RT_ERR_SMI  - SMI access error
 * Note:
 *      None
 */
ret_t rtl8367c_getAsicTrunkingHashSelect(rtksw_uint32 unit, rtksw_uint32* pHashsel)
{
    return rtl8367c_getAsicRegBits(unit, RTL8367C_REG_PORT_TRUNK_CTRL, RTL8367C_PORT_TRUNK_HASH_MASK, pHashsel);
}
/* Function Name:
 *      rtl8367c_getAsicQeueuEmptyStatus
 * Description:
 *      Get current output queue if empty status
 * Input:
 *      unit        - Unit ID
 *      portmask    - queue empty port mask
 * Output:
 *      None
 * Return:
 *      RT_ERR_OK   - Success
 *      RT_ERR_SMI  - SMI access error
 * Note:
 *      None
 */
ret_t rtl8367c_getAsicQeueuEmptyStatus(rtksw_uint32 unit, rtksw_uint32* portmask)
{
    return rtl8367c_getAsicReg(unit, RTL8367C_REG_PORT_QEMPTY, portmask);
}
/* Function Name:
 *      rtl8367c_setAsicTrunkingHashTable
 * Description:
 *      Set port trunking hash value mapping table
 * Input:
 *      unit        - Unit ID
 *      hashval     - hashing value 0-15
 *      portId      - trunking port id 0-3
 * Output:
 *      None
 * Return:
 *      RT_ERR_OK           - Success
 *      RT_ERR_SMI          - SMI access error
 *      RT_ERR_PORT_ID      - Invalid port number
 *      RT_ERR_OUT_OF_RANGE - Invalid hashing value (0-15)
 * Note:
 *      None
 */
ret_t rtl8367c_setAsicTrunkingHashTable(rtksw_uint32 unit, rtksw_uint32 hashval, rtksw_uint32 portId)
{
    if(hashval > RTL8367C_TRUNKING_HASHVALUE_MAX)
        return RT_ERR_OUT_OF_RANGE;

    if(portId >= RTL8367C_TRUNKING_PORTNO)
        return RT_ERR_PORT_ID;

    if(hashval >= 8)
        return rtl8367c_setAsicRegBits(unit, RTL8367C_REG_PORT_TRUNK_HASH_MAPPING_CTRL1, RTL8367C_PORT_TRUNK_HASH_MAPPING_CTRL1_HASH8_MASK<<((hashval-8)*2), portId);
    else
        return rtl8367c_setAsicRegBits(unit, RTL8367C_REG_PORT_TRUNK_HASH_MAPPING_CTRL0, RTL8367C_PORT_TRUNK_HASH_MAPPING_CTRL0_HASH0_MASK<<(hashval*2), portId);
}
/* Function Name:
 *      rtl8367c_getAsicTrunkingHashTable
 * Description:
 *      Get port trunking hash value mapping table
 * Input:
 *      unit        - Unit ID
 *      hashval     - hashing value 0-15
 *      pPortId     - trunking port id 0-3
 * Output:
 *      None
 * Return:
 *      RT_ERR_OK           - Success
 *      RT_ERR_SMI          - SMI access error
 *      RT_ERR_OUT_OF_RANGE - Invalid hashing value (0-15)
 * Note:
 *      None
 */
ret_t rtl8367c_getAsicTrunkingHashTable(rtksw_uint32 unit, rtksw_uint32 hashval, rtksw_uint32* pPortId)
{
    if(hashval > RTL8367C_TRUNKING_HASHVALUE_MAX)
        return RT_ERR_OUT_OF_RANGE;

    if(hashval >= 8)
        return rtl8367c_getAsicRegBits(unit, RTL8367C_REG_PORT_TRUNK_HASH_MAPPING_CTRL1, RTL8367C_PORT_TRUNK_HASH_MAPPING_CTRL1_HASH8_MASK<<((hashval-8)*2), pPortId);
    else
        return rtl8367c_getAsicRegBits(unit, RTL8367C_REG_PORT_TRUNK_HASH_MAPPING_CTRL0, RTL8367C_PORT_TRUNK_HASH_MAPPING_CTRL0_HASH0_MASK<<(hashval*2), pPortId);
}

/* Function Name:
 *      rtl8367c_setAsicTrunkingHashTable1
 * Description:
 *      Set port trunking hash value mapping table
 * Input:
 *      unit        - Unit ID
 *      hashval     - hashing value 0-15
 *      portId      - trunking port id 0-3
 * Output:
 *      None
 * Return:
 *      RT_ERR_OK           - Success
 *      RT_ERR_SMI          - SMI access error
 *      RT_ERR_PORT_ID      - Invalid port number
 *      RT_ERR_OUT_OF_RANGE - Invalid hashing value (0-15)
 * Note:
 *      None
 */
ret_t rtl8367c_setAsicTrunkingHashTable1(rtksw_uint32 unit, rtksw_uint32 hashval, rtksw_uint32 portId)
{
    if(hashval > RTL8367C_TRUNKING_HASHVALUE_MAX)
        return RT_ERR_OUT_OF_RANGE;

    if(portId >= RTL8367C_TRUNKING1_PORTN0)
        return RT_ERR_PORT_ID;

    if(hashval >= 8)
        return rtl8367c_setAsicRegBits(unit, RTL8367C_REG_PORT_TRUNK_HASH_MAPPING_CTRL3, RTL8367C_PORT_TRUNK_HASH_MAPPING_CTRL3_HASH8_MASK<<((hashval-8)*2), portId);
    else
        return rtl8367c_setAsicRegBits(unit, RTL8367C_REG_PORT_TRUNK_HASH_MAPPING_CTRL2, RTL8367C_PORT_TRUNK_HASH_MAPPING_CTRL2_HASH0_MASK<<(hashval*2), portId);
}
/* Function Name:
 *      rtl8367c_getAsicTrunkingHashTable1
 * Description:
 *      Get port trunking hash value mapping table
 * Input:
 *      unit        - Unit ID
 *      hashval     - hashing value 0-15
 *      pPortId     - trunking port id 0-3
 * Output:
 *      None
 * Return:
 *      RT_ERR_OK           - Success
 *      RT_ERR_SMI          - SMI access error
 *      RT_ERR_OUT_OF_RANGE - Invalid hashing value (0-15)
 * Note:
 *      None
 */
ret_t rtl8367c_getAsicTrunkingHashTable1(rtksw_uint32 unit, rtksw_uint32 hashval, rtksw_uint32* pPortId)
{
    if(hashval > RTL8367C_TRUNKING_HASHVALUE_MAX)
        return RT_ERR_OUT_OF_RANGE;

    if(hashval >= 8)
        return rtl8367c_getAsicRegBits(unit, RTL8367C_REG_PORT_TRUNK_HASH_MAPPING_CTRL3, RTL8367C_PORT_TRUNK_HASH_MAPPING_CTRL3_HASH8_MASK<<((hashval-8)*2), pPortId);
    else
        return rtl8367c_getAsicRegBits(unit, RTL8367C_REG_PORT_TRUNK_HASH_MAPPING_CTRL2, RTL8367C_PORT_TRUNK_HASH_MAPPING_CTRL2_HASH0_MASK<<(hashval*2), pPortId);
}

