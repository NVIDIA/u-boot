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
 * Feature : Unkown multicast related functions
 *
 */
#include "rtl8367c_asicdrv_unknownMulticast.h"
/* Function Name:
 *      rtl8367c_setAsicUnknownL2MulticastBehavior
 * Description:
 *      Set behavior of L2 multicast
 * Input:
 *      unit    - Unit ID
 *      port    - Physical port number (0~7)
 *      behave  - 0: flooding, 1: drop, 2: trap
 * Output:
 *      None
 * Return:
 *      RT_ERR_OK           - Success
 *      RT_ERR_SMI          - SMI access error
 *      RT_ERR_PORT_ID      - Invalid port number
 *      RT_ERR_NOT_ALLOWED  - Invalid operation
 * Note:
 *      None
 */
ret_t rtl8367c_setAsicUnknownL2MulticastBehavior(rtksw_uint32 unit, rtksw_uint32 port, rtksw_uint32 behave)
{
    ret_t retVal;

    if(port >  RTL8367C_PORTIDMAX)
        return RT_ERR_PORT_ID;

    if(behave >= L2_UNKOWN_MULTICAST_END)
        return RT_ERR_NOT_ALLOWED;
    if(port < 8)
    {
        retVal = rtl8367c_setAsicRegBits(unit, RTL8367C_UNKNOWN_L2_MULTICAST_REG(port), RTL8367C_UNKNOWN_L2_MULTICAST_MASK(port), behave);
        if(retVal != RT_ERR_OK)
            return retVal;
    }
    else
    {
        retVal = rtl8367c_setAsicRegBits(unit, RTL8367C_REG_UNKNOWN_L2_MULTICAST_CTRL1, 3 << ((port - 8) << 1), behave);
        if(retVal != RT_ERR_OK)
            return retVal;
    }

    return RT_ERR_OK;
}
/* Function Name:
 *      rtl8367c_getAsicUnknownL2MulticastBehavior
 * Description:
 *      Get behavior of L2 multicast
 * Input:
 *      unit        - Unit ID
 *      port        - Physical port number (0~7)
 *      pBehave     - 0: flooding, 1: drop, 2: trap
 * Output:
 *      None
 * Return:
 *      RT_ERR_OK       - Success
 *      RT_ERR_SMI      - SMI access error
 *      RT_ERR_PORT_ID  - Invalid port number
 * Note:
 *      None
 */
ret_t rtl8367c_getAsicUnknownL2MulticastBehavior(rtksw_uint32 unit, rtksw_uint32 port, rtksw_uint32 *pBehave)
{
    ret_t retVal;

    if(port >  RTL8367C_PORTIDMAX)
        return RT_ERR_PORT_ID;

    if(port < 8)
    {
        retVal = rtl8367c_getAsicRegBits(unit, RTL8367C_UNKNOWN_L2_MULTICAST_REG(port), RTL8367C_UNKNOWN_L2_MULTICAST_MASK(port), pBehave);
        if (retVal != RT_ERR_OK)
            return retVal;
    }
    else
    {
        retVal = rtl8367c_getAsicRegBits(unit, RTL8367C_REG_UNKNOWN_L2_MULTICAST_CTRL1, 3 << ((port - 8) << 1), pBehave);
        if (retVal != RT_ERR_OK)
            return retVal;
    }

    return RT_ERR_OK;
}
/* Function Name:
 *      rtl8367c_setAsicUnknownIPv4MulticastBehavior
 * Description:
 *      Set behavior of IPv4 multicast
 * Input:
 *      unit        - Unit ID
 *      port        - Physical port number (0~7)
 *      behave      - 0: flooding, 1: drop, 2: trap
 * Output:
 *      None
 * Return:
 *      RT_ERR_OK           - Success
 *      RT_ERR_SMI          - SMI access error
 *      RT_ERR_PORT_ID      - Invalid port number
 *      RT_ERR_NOT_ALLOWED  - Invalid operation
 * Note:
 *      None
 */
ret_t rtl8367c_setAsicUnknownIPv4MulticastBehavior(rtksw_uint32 unit, rtksw_uint32 port, rtksw_uint32 behave)
{
    if(port >  RTL8367C_PORTIDMAX)
        return RT_ERR_PORT_ID;

    if(behave >= L3_UNKOWN_MULTICAST_END)
        return RT_ERR_NOT_ALLOWED;

    return rtl8367c_setAsicRegBits(unit, RTL8367C_UNKNOWN_IPV4_MULTICAST_REG(port), RTL8367C_UNKNOWN_IPV4_MULTICAST_MASK(port), behave);
}
/* Function Name:
 *      rtl8367c_getAsicUnknownIPv4MulticastBehavior
 * Description:
 *      Get behavior of IPv4 multicast
 * Input:
 *      unit        - Unit ID
 *      port        - Physical port number (0~7)
 *      pBehave     - 0: flooding, 1: drop, 2: trap
 * Output:
 *      None
 * Return:
 *      RT_ERR_OK       - Success
 *      RT_ERR_SMI      - SMI access error
 *      RT_ERR_PORT_ID  - Invalid port number
 * Note:
 *      None
 */
ret_t rtl8367c_getAsicUnknownIPv4MulticastBehavior(rtksw_uint32 unit, rtksw_uint32 port, rtksw_uint32 *pBehave)
{
    if(port >  RTL8367C_PORTIDMAX)
        return RT_ERR_PORT_ID;

    return rtl8367c_getAsicRegBits(unit, RTL8367C_UNKNOWN_IPV4_MULTICAST_REG(port), RTL8367C_UNKNOWN_IPV4_MULTICAST_MASK(port), pBehave);
}
/* Function Name:
 *      rtl8367c_setAsicUnknownIPv6MulticastBehavior
 * Description:
 *      Set behavior of IPv6 multicast
 * Input:
 *      unit    - Unit ID
 *      port    - Physical port number (0~7)
 *      behave  - 0: flooding, 1: drop, 2: trap
 * Output:
 *      None
 * Return:
 *      RT_ERR_OK           - Success
 *      RT_ERR_SMI          - SMI access error
 *      RT_ERR_PORT_ID      - Invalid port number
 *      RT_ERR_NOT_ALLOWED  - Invalid operation
 * Note:
 *      None
 */
ret_t rtl8367c_setAsicUnknownIPv6MulticastBehavior(rtksw_uint32 unit, rtksw_uint32 port, rtksw_uint32 behave)
{
    if(port >  RTL8367C_PORTIDMAX)
        return RT_ERR_PORT_ID;

    if(behave >= L3_UNKOWN_MULTICAST_END)
        return RT_ERR_NOT_ALLOWED;

    return rtl8367c_setAsicRegBits(unit, RTL8367C_UNKNOWN_IPV6_MULTICAST_REG(port), RTL8367C_UNKNOWN_IPV6_MULTICAST_MASK(port), behave);
}
/* Function Name:
 *      rtl8367c_getAsicUnknownIPv6MulticastBehavior
 * Description:
 *      Get behavior of IPv6 multicast
 * Input:
 *      unit        - Unit ID
 *      port        - Physical port number (0~7)
 *      pBehave     - 0: flooding, 1: drop, 2: trap
 * Output:
 *      None
 * Return:
 *      RT_ERR_OK       - Success
 *      RT_ERR_SMI      - SMI access error
 *      RT_ERR_PORT_ID  - Invalid port number
 * Note:
 *      None
 */
ret_t rtl8367c_getAsicUnknownIPv6MulticastBehavior(rtksw_uint32 unit, rtksw_uint32 port, rtksw_uint32 *pBehave)
{
    if(port >  RTL8367C_PORTIDMAX)
        return RT_ERR_PORT_ID;

    return rtl8367c_getAsicRegBits(unit, RTL8367C_UNKNOWN_IPV6_MULTICAST_REG(port), RTL8367C_UNKNOWN_IPV6_MULTICAST_MASK(port), pBehave);
}
/* Function Name:
 *      rtl8367c_setAsicUnknownMulticastTrapPriority
 * Description:
 *      Set trap priority of unknown multicast frame
 * Input:
 *      unit        - Unit ID
 *      priority    - priority (0~7)
 * Output:
 *      None
 * Return:
 *      RT_ERR_OK               - Success
 *      RT_ERR_SMI              - SMI access error
 *      RT_ERR_QOS_INT_PRIORITY - Invalid priority
 * Note:
 *      None
 */
ret_t rtl8367c_setAsicUnknownMulticastTrapPriority(rtksw_uint32 unit, rtksw_uint32 priority)
{
    if(priority > RTL8367C_PRIMAX)
        return RT_ERR_QOS_INT_PRIORITY;

    return rtl8367c_setAsicRegBits(unit, RTL8367C_QOS_TRAP_PRIORITY_CTRL0_REG, RTL8367C_UNKNOWN_MC_PRIORTY_MASK, priority);
}
/* Function Name:
 *      rtl8367c_getAsicUnknownMulticastTrapPriority
 * Description:
 *      Get trap priority of unknown multicast frame
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
ret_t rtl8367c_getAsicUnknownMulticastTrapPriority(rtksw_uint32 unit, rtksw_uint32 *pPriority)
{
    return rtl8367c_getAsicRegBits(unit, RTL8367C_QOS_TRAP_PRIORITY_CTRL0_REG, RTL8367C_UNKNOWN_MC_PRIORTY_MASK, pPriority);
}
