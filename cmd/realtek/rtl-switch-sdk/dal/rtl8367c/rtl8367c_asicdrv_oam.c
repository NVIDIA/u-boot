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
 * $Revision: 42321 $
 * $Date: 2013-08-26 13:51:29 +0800 (週一, 26 八月 2013) $
 *
 * Purpose : RTL8367C switch high-level API for RTL8367C
 * Feature : OAM related functions
 *
 */

#include "rtl8367c_asicdrv_oam.h"
/* Function Name:
 *      rtl8367c_setAsicOamParser
 * Description:
 *      Set OAM parser state
 * Input:
 *      unit    - Unit ID
 *      port    - Physical port number (0~7)
 *      parser  - Per-Port OAM parser state
 * Output:
 *      None
 * Return:
 *      RT_ERR_OK           - Success
 *      RT_ERR_SMI          - SMI access error
 *      RT_ERR_PORT_ID      - Invalid port number
 *      RT_ERR_NOT_ALLOWED  - Invalid paser state
 * Note:
 *      None
 */
ret_t rtl8367c_setAsicOamParser(rtksw_uint32 unit, rtksw_uint32 port, rtksw_uint32 parser)
{
    if(port >= RTL8367C_PORTNO)
        return RT_ERR_PORT_ID;

    if(parser > OAM_PARFWDCPU)
        return RT_ERR_NOT_ALLOWED;

    return rtl8367c_setAsicRegBits(unit, RTL8367C_REG_OAM_PARSER_CTRL0 + port/8, RTL8367C_OAM_PARSER_MASK(port % 8), parser);
}
/* Function Name:
 *      rtl8367c_getAsicOamParser
 * Description:
 *      Get OAM parser state
 * Input:
 *      unit    - Unit ID
 *      port    - Physical port number (0~7)
 *      pParser - Per-Port OAM parser state
 * Output:
 *      None
 * Return:
 *      RT_ERR_OK       - Success
 *      RT_ERR_SMI      - SMI access error
 *      RT_ERR_PORT_ID  - Invalid port number
 * Note:
 *      None
 */
ret_t rtl8367c_getAsicOamParser(rtksw_uint32 unit, rtksw_uint32 port, rtksw_uint32* pParser)
{
    if(port >= RTL8367C_PORTNO)
        return RT_ERR_PORT_ID;

    return rtl8367c_getAsicRegBits(unit, RTL8367C_REG_OAM_PARSER_CTRL0 + port/8, RTL8367C_OAM_PARSER_MASK(port%8), pParser);
}
/* Function Name:
 *      rtl8367c_setAsicOamMultiplexer
 * Description:
 *      Set OAM multiplexer state
 * Input:
 *      unit        - Unit ID
 *      port        - Physical port number (0~7)
 *      multiplexer - Per-Port OAM multiplexer state
 * Output:
 *      None
 * Return:
 *      RT_ERR_OK           - Success
 *      RT_ERR_SMI          - SMI access error
 *      RT_ERR_PORT_ID      - Invalid port number
 *      RT_ERR_NOT_ALLOWED  - Invalid multiplexer state
 * Note:
 *      None
 */
ret_t rtl8367c_setAsicOamMultiplexer(rtksw_uint32 unit, rtksw_uint32 port, rtksw_uint32 multiplexer)
{
    if(port >= RTL8367C_PORTNO)
        return RT_ERR_PORT_ID;

    if(multiplexer > OAM_MULCPU)
        return RT_ERR_NOT_ALLOWED;

    return rtl8367c_setAsicRegBits(unit, RTL8367C_REG_OAM_MULTIPLEXER_CTRL0 + port/8, RTL8367C_OAM_MULTIPLEXER_MASK(port%8), multiplexer);
}
/* Function Name:
 *      rtl8367c_getAsicOamMultiplexer
 * Description:
 *      Get OAM multiplexer state
 * Input:
 *      unit            - Unit ID
 *      port            - Physical port number (0~7)
 *      pMultiplexer    - Per-Port OAM multiplexer state
 * Output:
 *      None
 * Return:
 *      RT_ERR_OK       - Success
 *      RT_ERR_SMI      - SMI access error
 *      RT_ERR_PORT_ID  - Invalid port number
 * Note:
 *      None
 */
ret_t rtl8367c_getAsicOamMultiplexer(rtksw_uint32 unit, rtksw_uint32 port, rtksw_uint32* pMultiplexer)
{
    if(port >= RTL8367C_PORTNO)
        return RT_ERR_PORT_ID;

    return rtl8367c_getAsicRegBits(unit, RTL8367C_REG_OAM_MULTIPLEXER_CTRL0 + port/8, RTL8367C_OAM_MULTIPLEXER_MASK(port%8), pMultiplexer);
}
/* Function Name:
 *      rtl8367c_setAsicOamCpuPri
 * Description:
 *      Set trap priority for OAM packet
 * Input:
 *      unit        - Unit ID
 *      priority    - priority (0~7)
 * Output:
 *      None
 * Return:
 *      RT_ERR_OK                   - Success
 *      RT_ERR_SMI                  - SMI access error
 *      RT_ERR_QOS_INT_PRIORITY     - Invalid priority
 * Note:
 *      None
 */
ret_t rtl8367c_setAsicOamCpuPri(rtksw_uint32 unit, rtksw_uint32 priority)
{
    if(priority > RTL8367C_PRIMAX)
        return RT_ERR_QOS_INT_PRIORITY;

    return rtl8367c_setAsicRegBits(unit, RTL8367C_REG_QOS_TRAP_PRIORITY0, RTL8367C_OAM_PRIOIRTY_MASK, priority);
}
/* Function Name:
 *      rtl8367c_getAsicOamCpuPri
 * Description:
 *      Get trap priority for OAM packet
 * Input:
 *      unit        - Unit ID
 *      pPriority   - priority (0~7)
 * Output:
 *      None
 * Return:
 *      RT_ERR_OK   - Success
 *      RT_ERR_SMI  - SMI access error
 * Note:
 *      None
 */
ret_t rtl8367c_getAsicOamCpuPri(rtksw_uint32 unit, rtksw_uint32 *pPriority)
{
    return rtl8367c_getAsicRegBits(unit, RTL8367C_REG_QOS_TRAP_PRIORITY0, RTL8367C_OAM_PRIOIRTY_MASK, pPriority);
}
/* Function Name:
 *      rtl8367c_setAsicOamEnable
 * Description:
 *      Set OAM function state
 * Input:
 *      unit        - Unit ID
 *      enabled     - OAM function usage 1:enable, 0:disabled
 * Output:
 *      None
 * Return:
 *      RT_ERR_OK   - Success
 *      RT_ERR_SMI  - SMI access error
 * Note:
 *      None
 */
ret_t rtl8367c_setAsicOamEnable(rtksw_uint32 unit, rtksw_uint32 enabled)
{
    return rtl8367c_setAsicRegBit(unit, RTL8367C_REG_OAM_CTRL, RTL8367C_OAM_CTRL_OFFSET, enabled);
}
/* Function Name:
 *      rtl8367c_getAsicOamEnable
 * Description:
 *      Get OAM function state
 * Input:
 *      unit        - Unit ID
 *      pEnabled    - OAM function usage 1:enable, 0:disabled
 * Output:
 *      None
 * Return:
 *      RT_ERR_OK   - Success
 *      RT_ERR_SMI  - SMI access error
 * Note:
 *      None
 */
ret_t rtl8367c_getAsicOamEnable(rtksw_uint32 unit, rtksw_uint32 *pEnabled)
{
    return rtl8367c_getAsicRegBit(unit, RTL8367C_REG_OAM_CTRL, RTL8367C_OAM_CTRL_OFFSET, pEnabled);
}
