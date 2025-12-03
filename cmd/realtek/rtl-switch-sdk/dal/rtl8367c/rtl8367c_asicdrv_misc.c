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
 * Feature : Miscellaneous functions
 *
 */

#include "rtl8367c_asicdrv_misc.h"
/* Function Name:
 *      rtl8367c_setAsicMacAddress
 * Description:
 *      Set switch MAC address
 * Input:
 *      unit    - Unit ID
 *      mac     - switch mac
 * Output:
 *      None
 * Return:
 *      RT_ERR_OK       - Success
 *      RT_ERR_SMI      - SMI access error
 * Note:
 *      None
 */
ret_t rtl8367c_setAsicMacAddress(rtksw_uint32 unit, ether_addr_t mac)
{
    ret_t retVal;
    rtksw_uint32 regData;
    rtksw_uint8 *accessPtr;
    rtksw_uint32 i;

    accessPtr =  (rtksw_uint8*)&mac;

    for(i = 0; i <=2; i++)
    {
        regData = (*(accessPtr + (i*2)) << 8) | *(accessPtr + (i*2) + 1);
        retVal = rtl8367c_setAsicReg(unit, RTL8367C_REG_SWITCH_MAC2 - i, regData);
        if(retVal != RT_ERR_OK)
            return retVal;
    }

    return retVal;
}
/* Function Name:
 *      rtl8367c_getAsicMacAddress
 * Description:
 *      Get switch MAC address
 * Input:
 *      unit    - Unit ID
 *      pMac    - switch mac
 * Output:
 *      None
 * Return:
 *      RT_ERR_OK       - Success
 *      RT_ERR_SMI      - SMI access error
 * Note:
 *      None
 */
ret_t rtl8367c_getAsicMacAddress(rtksw_uint32 unit, ether_addr_t *pMac)
{
    ret_t retVal;
    rtksw_uint32 regData;
    rtksw_uint8 *accessPtr;
    rtksw_uint32 i;


    accessPtr = (rtksw_uint8*)pMac;

    for(i = 0; i <= 2; i++)
    {
        retVal = rtl8367c_getAsicReg(unit, RTL8367C_REG_SWITCH_MAC2 - i, &regData);
        if(retVal != RT_ERR_OK)
            return retVal;

        *accessPtr = (regData & 0xFF00) >> 8;
        accessPtr ++;
        *accessPtr = regData & 0xFF;
        accessPtr ++;
    }

    return retVal;
}
/* Function Name:
 *      rtl8367c_getAsicDebugInfo
 * Description:
 *      Get per-port packet forward debugging information
 * Input:
 *      unit        - Unit ID
 *      port        - Physical port number (0~7)
 *      pDebugifo   - per-port packet trap/drop/forward reason
 * Output:
 *      None
 * Return:
 *      RT_ERR_OK       - Success
 *      RT_ERR_SMI      - SMI access error
 *      RT_ERR_PORT_ID  - Invalid port number
 * Note:
 *      None
 */
ret_t rtl8367c_getAsicDebugInfo(rtksw_uint32 unit, rtksw_uint32 port, rtksw_uint32 *pDebugifo)
{
    if(port > RTL8367C_PORTIDMAX)
        return RT_ERR_PORT_ID;

    return rtl8367c_getAsicRegBits(unit, RTL8367C_DEBUG_INFO_REG(port), RTL8367C_DEBUG_INFO_MASK(port), pDebugifo);
}
/* Function Name:
 *      rtl8367c_setAsicPortJamMode
 * Description:
 *      Set half duplex flow control setting
 * Input:
 *      unit    - Unit ID
 *      mode    - 0: Back-Pressure 1: DEFER
 * Output:
 *      None
 * Return:
 *      RT_ERR_OK       - Success
 *      RT_ERR_SMI      - SMI access error
 * Note:
 *      None
 */
ret_t rtl8367c_setAsicPortJamMode(rtksw_uint32 unit, rtksw_uint32 mode)
{
    return rtl8367c_setAsicRegBit(unit, RTL8367C_REG_CFG_BACKPRESSURE, RTL8367C_LONGTXE_OFFSET,mode);
}
/* Function Name:
 *      rtl8367c_getAsicPortJamMode
 * Description:
 *      Get half duplex flow control setting
 * Input:
 *      unit    - Unit ID
 *      pMode   - 0: Back-Pressure 1: DEFER
 * Output:
 *      None
 * Return:
 *      RT_ERR_OK       - Success
 *      RT_ERR_SMI      - SMI access error
 * Note:
 *      None
 */
ret_t rtl8367c_getAsicPortJamMode(rtksw_uint32 unit, rtksw_uint32* pMode)
{
    return rtl8367c_getAsicRegBit(unit, RTL8367C_REG_CFG_BACKPRESSURE, RTL8367C_LONGTXE_OFFSET, pMode);
}

/* Function Name:
 *      rtl8367c_setAsicMaxLengthCfg
 * Description:
 *      Set Max packet length configuration
 * Input:
 *      unit        - Unit ID
 *      cfgId       - Configuration ID
 *      maxLength   - Max Length
 * Output:
 *      None
 * Return:
 *      RT_ERR_OK       - Success
 *      RT_ERR_SMI      - SMI access error
 * Note:
 *      None
 */
ret_t rtl8367c_setAsicMaxLengthCfg(rtksw_uint32 unit, rtksw_uint32 cfgId, rtksw_uint32 maxLength)
{
    return rtl8367c_setAsicRegBits(unit, RTL8367C_REG_MAX_LEN_RX_TX_CFG0 + cfgId, RTL8367C_MAX_LEN_RX_TX_CFG0_MASK, maxLength);
}

/* Function Name:
 *      rtl8367c_getAsicMaxLengthCfg
 * Description:
 *      Get Max packet length configuration
 * Input:
 *      unit    - Unit ID
 *      cfgId       - Configuration ID
 *      maxLength   - Max Length
 * Output:
 *      None
 * Return:
 *      RT_ERR_OK       - Success
 *      RT_ERR_SMI      - SMI access error
 * Note:
 *      None
 */
ret_t rtl8367c_getAsicMaxLengthCfg(rtksw_uint32 unit, rtksw_uint32 cfgId, rtksw_uint32 *pMaxLength)
{
    return rtl8367c_getAsicRegBits(unit, RTL8367C_REG_MAX_LEN_RX_TX_CFG0 + cfgId, RTL8367C_MAX_LEN_RX_TX_CFG0_MASK, pMaxLength);
}

/* Function Name:
 *      rtl8367c_setAsicMaxLength
 * Description:
 *      Set Max packet length
 * Input:
 *      unit        - Unit ID
 *      port        - port ID
 *      type        - 0: 10M/100M speed, 1: giga speed
 *      cfgId       - Configuration ID
 * Output:
 *      None
 * Return:
 *      RT_ERR_OK       - Success
 *      RT_ERR_SMI      - SMI access error
 * Note:
 *      None
 */
ret_t rtl8367c_setAsicMaxLength(rtksw_uint32 unit, rtksw_uint32 port, rtksw_uint32 type, rtksw_uint32 cfgId)
{
    ret_t retVal;

    if(port < 8)
    {
        retVal = rtl8367c_setAsicRegBit(unit, RTL8367C_REG_MAX_LENGTH_CFG, (type * 8) + port, cfgId);
        if(retVal != RT_ERR_OK)
            return retVal;
    }
    else
    {
        retVal = rtl8367c_setAsicRegBit(unit, RTL8367C_REG_MAX_LENGTH_CFG_EXT, (type * 3) + port - 8, cfgId);
        if(retVal != RT_ERR_OK)
            return retVal;
    }

    return RT_ERR_OK;
}

/* Function Name:
 *      rtl8367c_getAsicMaxLength
 * Description:
 *      Get Max packet length
 * Input:
 *      unit        - Unit ID
 *      port        - port ID
 *      type        - 0: 10M/100M speed, 1: giga speed
 *      cfgId       - Configuration ID
 * Output:
 *      None
 * Return:
 *      RT_ERR_OK       - Success
 *      RT_ERR_SMI      - SMI access error
 * Note:
 *      None
 */
ret_t rtl8367c_getAsicMaxLength(rtksw_uint32 unit, rtksw_uint32 port, rtksw_uint32 type, rtksw_uint32 *pCfgId)
{
    ret_t retVal;

    if(port < 8)
    {
        retVal = rtl8367c_getAsicRegBit(unit, RTL8367C_REG_MAX_LENGTH_CFG, (type * 8) + port, pCfgId);
        if(retVal != RT_ERR_OK)
            return retVal;
    }
    else
    {
        retVal = rtl8367c_getAsicRegBit(unit, RTL8367C_REG_MAX_LENGTH_CFG_EXT, (type * 3) + port - 8, pCfgId);
        if(retVal != RT_ERR_OK)
            return retVal;
    }
    return RT_ERR_OK;
}

