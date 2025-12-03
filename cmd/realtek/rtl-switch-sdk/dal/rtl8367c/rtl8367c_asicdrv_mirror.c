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
 * Feature : Port mirror related functions
 *
 */
#include "rtl8367c_asicdrv_mirror.h"
/* Function Name:
 *      rtl8367c_setAsicPortMirror
 * Description:
 *      Set port mirror function
 * Input:
 *      unit    - Unit ID
 *      source  - Source port
 *      monitor - Monitor (destination) port
 * Output:
 *      None
 * Return:
 *      RT_ERR_OK       - Success
 *      RT_ERR_SMI      - SMI access error
 *      RT_ERR_PORT_ID  - Invalid port number
 * Note:
 *      None
 */
ret_t rtl8367c_setAsicPortMirror(rtksw_uint32 unit, rtksw_uint32 source, rtksw_uint32 monitor)
{
    ret_t retVal;

    if((source > RTL8367C_PORTIDMAX) || (monitor > RTL8367C_PORTIDMAX))
        return RT_ERR_PORT_ID;

    retVal = rtl8367c_setAsicRegBits(unit, RTL8367C_MIRROR_CTRL_REG, RTL8367C_MIRROR_SOURCE_PORT_MASK, source);
    if(retVal != RT_ERR_OK)
        return retVal;


    return rtl8367c_setAsicRegBits(unit, RTL8367C_MIRROR_CTRL_REG, RTL8367C_MIRROR_MONITOR_PORT_MASK, monitor);
}
/* Function Name:
 *      rtl8367c_getAsicPortMirror
 * Description:
 *      Get port mirror function
 * Input:
 *      unit        - Unit ID
 *      pSource     - Source port
 *      pMonitor    - Monitor (destination) port
 * Output:
 *      None
 * Return:
 *      RT_ERR_OK       - Success
 *      RT_ERR_SMI      - SMI access error
 * Note:
 *      None
 */
ret_t rtl8367c_getAsicPortMirror(rtksw_uint32 unit, rtksw_uint32 *pSource, rtksw_uint32 *pMonitor)
{
    ret_t retVal;

    retVal = rtl8367c_getAsicRegBits(unit, RTL8367C_MIRROR_CTRL_REG, RTL8367C_MIRROR_SOURCE_PORT_MASK, pSource);
    if(retVal != RT_ERR_OK)
        return retVal;

    return rtl8367c_getAsicRegBits(unit, RTL8367C_MIRROR_CTRL_REG, RTL8367C_MIRROR_MONITOR_PORT_MASK, pMonitor);
}
/* Function Name:
 *      rtl8367c_setAsicPortMirrorRxFunction
 * Description:
 *      Set the mirror function on RX of the mirrored
 * Input:
 *      unit        - Unit ID
 *      enabled     - 1: enabled, 0: disabled
 * Output:
 *      None
 * Return:
 *      RT_ERR_OK       - Success
 *      RT_ERR_SMI      - SMI access error
 * Note:
 *      None
 */
ret_t rtl8367c_setAsicPortMirrorRxFunction(rtksw_uint32 unit, rtksw_uint32 enabled)
{
    return rtl8367c_setAsicRegBit(unit, RTL8367C_MIRROR_CTRL_REG, RTL8367C_MIRROR_RX_OFFSET, enabled);
}
/* Function Name:
 *      rtl8367c_getAsicPortMirrorRxFunction
 * Description:
 *      Get the mirror function on RX of the mirrored
 * Input:
 *      unit        - Unit ID
 *      pEnabled    - 1: enabled, 0: disabled
 * Output:
 *      None
 * Return:
 *      RT_ERR_OK       - Success
 *      RT_ERR_SMI      - SMI access error
 * Note:
 *      None
 */
ret_t rtl8367c_getAsicPortMirrorRxFunction(rtksw_uint32 unit, rtksw_uint32* pEnabled)
{
    return rtl8367c_getAsicRegBit(unit, RTL8367C_MIRROR_CTRL_REG, RTL8367C_MIRROR_RX_OFFSET, pEnabled);
}
/* Function Name:
 *      rtl8367c_setAsicPortMirrorTxFunction
 * Description:
 *      Set the mirror function on TX of the mirrored
 * Input:
 *      unit        - Unit ID
 *      enabled     - 1: enabled, 0: disabled
 * Output:
 *      None
 * Return:
 *      RT_ERR_OK       - Success
 *      RT_ERR_SMI      - SMI access error
 * Note:
 *      None
 */
ret_t rtl8367c_setAsicPortMirrorTxFunction(rtksw_uint32 unit, rtksw_uint32 enabled)
{
    return rtl8367c_setAsicRegBit(unit, RTL8367C_MIRROR_CTRL_REG, RTL8367C_MIRROR_TX_OFFSET, enabled);
}
/* Function Name:
 *      rtl8367c_getAsicPortMirrorTxFunction
 * Description:
 *      Get the mirror function on TX of the mirrored
 * Input:
 *      unit        - Unit ID
 *      pEnabled    - 1: enabled, 0: disabled
 * Output:
 *      None
 * Return:
 *      RT_ERR_OK       - Success
 *      RT_ERR_SMI      - SMI access error
 * Note:
 *      None
 */
ret_t rtl8367c_getAsicPortMirrorTxFunction(rtksw_uint32 unit, rtksw_uint32* pEnabled)
{
    return rtl8367c_getAsicRegBit(unit, RTL8367C_MIRROR_CTRL_REG, RTL8367C_MIRROR_TX_OFFSET, pEnabled);
}
/* Function Name:
 *      rtl8367c_setAsicPortMirrorIsolation
 * Description:
 *      Set the traffic isolation on monitor port
 * Input:
 *      unit        - Unit ID
 *      enabled     - 1: enabled, 0: disabled
 * Output:
 *      None
 * Return:
 *      RT_ERR_OK       - Success
 *      RT_ERR_SMI      - SMI access error
 * Note:
 *      None
 */
ret_t rtl8367c_setAsicPortMirrorIsolation(rtksw_uint32 unit, rtksw_uint32 enabled)
{
    return rtl8367c_setAsicRegBit(unit, RTL8367C_MIRROR_CTRL_REG, RTL8367C_MIRROR_ISO_OFFSET, enabled);
}
/* Function Name:
 *      rtl8367c_getAsicPortMirrorIsolation
 * Description:
 *      Get the traffic isolation on monitor port
 * Input:
 *      unit        - Unit ID
 *      pEnabled    - 1: enabled, 0: disabled
 * Output:
 *      None
 * Return:
 *      RT_ERR_OK       - Success
 *      RT_ERR_SMI      - SMI access error
 * Note:
 *      None
 */
ret_t rtl8367c_getAsicPortMirrorIsolation(rtksw_uint32 unit, rtksw_uint32* pEnabled)
{
    return rtl8367c_getAsicRegBit(unit, RTL8367C_MIRROR_CTRL_REG, RTL8367C_MIRROR_ISO_OFFSET, pEnabled);
}

/* Function Name:
 *      rtl8367c_setAsicPortMirrorMask
 * Description:
 *      Set mirror source port mask
 * Input:
 *      unit            - Unit ID
 *      SourcePortmask  - Source Portmask
 * Output:
 *      None
 * Return:
 *      RT_ERR_OK       - Success
 *      RT_ERR_SMI      - SMI access error
 *      RT_ERR_PORT_MASK- Port Mask Error
 * Note:
 *      None
 */
ret_t rtl8367c_setAsicPortMirrorMask(rtksw_uint32 unit, rtksw_uint32 SourcePortmask)
{
    if( SourcePortmask > RTL8367C_PORTMASK)
        return RT_ERR_PORT_MASK;

    return rtl8367c_setAsicRegBits(unit, RTL8367C_REG_MIRROR_SRC_PMSK, RTL8367C_MIRROR_SRC_PMSK_MASK, SourcePortmask);
}

/* Function Name:
 *      rtl8367c_getAsicPortMirrorMask
 * Description:
 *      Get mirror source port mask
 * Input:
 *      unit                    - Unit ID
 * Output:
 *      pSourcePortmask     - Source Portmask
 * Return:
 *      RT_ERR_OK       - Success
 *      RT_ERR_SMI      - SMI access error
 *      RT_ERR_PORT_MASK- Port Mask Error
 * Note:
 *      None
 */
ret_t rtl8367c_getAsicPortMirrorMask(rtksw_uint32 unit, rtksw_uint32 *pSourcePortmask)
{
    return rtl8367c_getAsicRegBits(unit, RTL8367C_REG_MIRROR_SRC_PMSK, RTL8367C_MIRROR_SRC_PMSK_MASK, pSourcePortmask);
}

/* Function Name:
 *      rtl8367c_setAsicPortMirrorVlanRxLeaky
 * Description:
 *      Set the mirror function of VLAN RX leaky
 * Input:
 *      unit        - Unit ID
 *      enabled     - 1: enabled, 0: disabled
 * Output:
 *      None
 * Return:
 *      RT_ERR_OK       - Success
 *      RT_ERR_SMI      - SMI access error
 * Note:
 *      None
 */
ret_t rtl8367c_setAsicPortMirrorVlanRxLeaky(rtksw_uint32 unit, rtksw_uint32 enabled)
{
    return rtl8367c_setAsicRegBit(unit, RTL8367C_REG_MIRROR_CTRL2, RTL8367C_MIRROR_RX_VLAN_LEAKY_OFFSET, enabled);
}
/* Function Name:
 *      rtl8367c_getAsicPortMirrorVlanRxLeaky
 * Description:
 *      Get the mirror function of VLAN RX leaky
 * Input:
 *      unit        - Unit ID
 *      pEnabled    - 1: enabled, 0: disabled
 * Output:
 *      None
 * Return:
 *      RT_ERR_OK       - Success
 *      RT_ERR_SMI      - SMI access error
 * Note:
 *      None
 */
ret_t rtl8367c_getAsicPortMirrorVlanRxLeaky(rtksw_uint32 unit, rtksw_uint32* pEnabled)
{
    return rtl8367c_getAsicRegBit(unit, RTL8367C_REG_MIRROR_CTRL2, RTL8367C_MIRROR_RX_VLAN_LEAKY_OFFSET, pEnabled);
}

/* Function Name:
 *      rtl8367c_setAsicPortMirrorVlanTxLeaky
 * Description:
 *      Set the mirror function of VLAN TX leaky
 * Input:
 *      unit        - Unit ID
 *      enabled     - 1: enabled, 0: disabled
 * Output:
 *      None
 * Return:
 *      RT_ERR_OK       - Success
 *      RT_ERR_SMI      - SMI access error
 * Note:
 *      None
 */
ret_t rtl8367c_setAsicPortMirrorVlanTxLeaky(rtksw_uint32 unit, rtksw_uint32 enabled)
{
    return rtl8367c_setAsicRegBit(unit, RTL8367C_REG_MIRROR_CTRL2, RTL8367C_MIRROR_TX_VLAN_LEAKY_OFFSET, enabled);
}
/* Function Name:
 *      rtl8367c_getAsicPortMirrorVlanTxLeaky
 * Description:
 *      Get the mirror function of VLAN TX leaky
 * Input:
 *      unit        - Unit ID
 *      pEnabled    - 1: enabled, 0: disabled
 * Output:
 *      None
 * Return:
 *      RT_ERR_OK       - Success
 *      RT_ERR_SMI      - SMI access error
 * Note:
 *      None
 */
ret_t rtl8367c_getAsicPortMirrorVlanTxLeaky(rtksw_uint32 unit, rtksw_uint32* pEnabled)
{
    return rtl8367c_getAsicRegBit(unit, RTL8367C_REG_MIRROR_CTRL2, RTL8367C_MIRROR_TX_VLAN_LEAKY_OFFSET, pEnabled);
}

/* Function Name:
 *      rtl8367c_setAsicPortMirrorIsolationRxLeaky
 * Description:
 *      Set the mirror function of  Isolation RX leaky
 * Input:
 *      unit        - Unit ID
 *      enabled     - 1: enabled, 0: disabled
 * Output:
 *      None
 * Return:
 *      RT_ERR_OK       - Success
 *      RT_ERR_SMI      - SMI access error
 * Note:
 *      None
 */
ret_t rtl8367c_setAsicPortMirrorIsolationRxLeaky(rtksw_uint32 unit, rtksw_uint32 enabled)
{
    return rtl8367c_setAsicRegBit(unit, RTL8367C_REG_MIRROR_CTRL2, RTL8367C_MIRROR_RX_ISOLATION_LEAKY_OFFSET, enabled);
}
/* Function Name:
 *      rtl8367c_getAsicPortMirrorIsolationRxLeaky
 * Description:
 *      Get the mirror function of VLAN RX leaky
 * Input:
 *      unit        - Unit ID
 *      pEnabled    - 1: enabled, 0: disabled
 * Output:
 *      None
 * Return:
 *      RT_ERR_OK       - Success
 *      RT_ERR_SMI      - SMI access error
 * Note:
 *      None
 */
ret_t rtl8367c_getAsicPortMirrorIsolationRxLeaky(rtksw_uint32 unit, rtksw_uint32* pEnabled)
{
    return rtl8367c_getAsicRegBit(unit, RTL8367C_REG_MIRROR_CTRL2, RTL8367C_MIRROR_RX_ISOLATION_LEAKY_OFFSET, pEnabled);
}

/* Function Name:
 *      rtl8367c_setAsicPortMirrorIsolationTxLeaky
 * Description:
 *      Set the mirror function of Isolation TX leaky
 * Input:
 *      unit        - Unit ID
 *      enabled     - 1: enabled, 0: disabled
 * Output:
 *      None
 * Return:
 *      RT_ERR_OK       - Success
 *      RT_ERR_SMI      - SMI access error
 * Note:
 *      None
 */
ret_t rtl8367c_setAsicPortMirrorIsolationTxLeaky(rtksw_uint32 unit, rtksw_uint32 enabled)
{
    return rtl8367c_setAsicRegBit(unit, RTL8367C_REG_MIRROR_CTRL2, RTL8367C_MIRROR_TX_ISOLATION_LEAKY_OFFSET, enabled);
}
/* Function Name:
 *      rtl8367c_getAsicPortMirrorIsolationTxLeaky
 * Description:
 *      Get the mirror function of VLAN TX leaky
 * Input:
 *      unit        - Unit ID
 *      pEnabled    - 1: enabled, 0: disabled
 * Output:
 *      None
 * Return:
 *      RT_ERR_OK       - Success
 *      RT_ERR_SMI      - SMI access error
 * Note:
 *      None
 */
ret_t rtl8367c_getAsicPortMirrorIsolationTxLeaky(rtksw_uint32 unit, rtksw_uint32* pEnabled)
{
    return rtl8367c_getAsicRegBit(unit, RTL8367C_REG_MIRROR_CTRL2, RTL8367C_MIRROR_TX_ISOLATION_LEAKY_OFFSET, pEnabled);
}

/* Function Name:
 *      rtl8367c_setAsicPortMirrorRealKeep
 * Description:
 *      Set the mirror function of keep format
 * Input:
 *      unit    - Unit ID
 *      mode    - 1: keep original format, 0: follow VLAN config
 * Output:
 *      None
 * Return:
 *      RT_ERR_OK       - Success
 *      RT_ERR_SMI      - SMI access error
 * Note:
 *      None
 */
ret_t rtl8367c_setAsicPortMirrorRealKeep(rtksw_uint32 unit, rtksw_uint32 mode)
{
    return rtl8367c_setAsicRegBit(unit, RTL8367C_REG_MIRROR_CTRL2, RTL8367C_MIRROR_REALKEEP_EN_OFFSET, mode);
}
/* Function Name:
 *      rtl8367c_getAsicPortMirrorRealKeep
 * Description:
 *      Get the mirror function of keep format
 * Input:
 *      unit    - Unit ID
 *      pMode   - 1: keep original format, 0: follow VLAN config
 * Output:
 *      None
 * Return:
 *      RT_ERR_OK       - Success
 *      RT_ERR_SMI      - SMI access error
 * Note:
 *      None
 */
ret_t rtl8367c_getAsicPortMirrorRealKeep(rtksw_uint32 unit, rtksw_uint32* pMode)
{
    return rtl8367c_getAsicRegBit(unit, RTL8367C_REG_MIRROR_CTRL2, RTL8367C_MIRROR_REALKEEP_EN_OFFSET, pMode);
}

/* Function Name:
 *      rtl8367c_setAsicPortMirrorOverride
 * Description:
 *      Set the mirror function of override
 * Input:
 *      unit        - Unit ID
 *      rxMirror    - 1: output rx Mirror format, 0: output forward format
 *      txMirror    - 1: output tx Mirror format, 0: output forward format
 *      aclMirror   - 1: output ACL Mirror format, 0: output forward format
 * Output:
 *      None
 * Return:
 *      RT_ERR_OK       - Success
 *      RT_ERR_SMI      - SMI access error
 * Note:
 *      None
 */
ret_t rtl8367c_setAsicPortMirrorOverride(rtksw_uint32 unit, rtksw_uint32 rxMirror, rtksw_uint32 txMirror, rtksw_uint32 aclMirror)
{
    ret_t retVal;

    if((retVal = rtl8367c_setAsicRegBit(unit, RTL8367C_REG_MIRROR_CTRL3, RTL8367C_MIRROR_RX_OVERRIDE_EN_OFFSET, rxMirror)) != RT_ERR_OK)
        return retVal;

    if((retVal = rtl8367c_setAsicRegBit(unit, RTL8367C_REG_MIRROR_CTRL3, RTL8367C_MIRROR_TX_OVERRIDE_EN_OFFSET, txMirror)) != RT_ERR_OK)
        return retVal;

    if((retVal = rtl8367c_setAsicRegBit(unit, RTL8367C_REG_MIRROR_CTRL3, RTL8367C_MIRROR_ACL_OVERRIDE_EN_OFFSET, aclMirror)) != RT_ERR_OK)
        return retVal;

    return RT_ERR_OK;
}

/* Function Name:
 *      rtl8367c_getAsicPortMirrorOverride
 * Description:
 *      Get the mirror function of override
 * Input:
 *      unit                    - Unit ID
 * Output:
 *      pRxMirror   - 1: output rx Mirror format, 0: output forward format
 *      pTxMirror   - 1: output tx Mirror format, 0: output forward format
 *      pAclMirror  - 1: output ACL Mirror format, 0: output forward format
 * Return:
 *      RT_ERR_OK       - Success
 *      RT_ERR_SMI      - SMI access error
 * Note:
 *      None
 */
ret_t rtl8367c_getAsicPortMirrorOverride(rtksw_uint32 unit, rtksw_uint32 *pRxMirror, rtksw_uint32 *pTxMirror, rtksw_uint32 *pAclMirror)
{
    ret_t retVal;

    if((retVal = rtl8367c_getAsicRegBit(unit, RTL8367C_REG_MIRROR_CTRL3, RTL8367C_MIRROR_RX_OVERRIDE_EN_OFFSET, pRxMirror)) != RT_ERR_OK)
        return retVal;

    if((retVal = rtl8367c_getAsicRegBit(unit, RTL8367C_REG_MIRROR_CTRL3, RTL8367C_MIRROR_TX_OVERRIDE_EN_OFFSET, pTxMirror)) != RT_ERR_OK)
        return retVal;

    if((retVal = rtl8367c_getAsicRegBit(unit, RTL8367C_REG_MIRROR_CTRL3, RTL8367C_MIRROR_ACL_OVERRIDE_EN_OFFSET, pAclMirror)) != RT_ERR_OK)
        return retVal;

    return RT_ERR_OK;
}
