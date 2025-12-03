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
 * Feature : Here is a list of all functions and variables in Mirror module.
 *
 */

#include "../../rtk_switch.h"
#include "../../rtk_error.h"
#include "dal_rtl8367c_mirror.h"
#include "rtl8367c_asicdrv.h"
#include "rtl8367c_asicdrv_mirror.h"

#include "../dal_mgmts.h"

/* Function Name:
 *      dal_rtl8367c_mirror_portBased_set
 * Description:
 *      Set port mirror function.
 * Input:
 *      unit                    - Unit ID
 *      mirroring_port          - Monitor port.
 *      pMirrored_rx_portmask   - Rx mirror port mask.
 *      pMirrored_tx_portmask   - Tx mirror port mask.
 * Output:
 *      None
 * Return:
 *      RT_ERR_OK           - OK
 *      RT_ERR_FAILED       - Failed
 *      RT_ERR_SMI          - SMI access error
 *      RT_ERR_PORT_ID      - Invalid port number
 *      RT_ERR_PORT_MASK    - Invalid portmask.
 * Note:
 *      The API is to set mirror function of source port and mirror port.
 *      The mirror port can only be set to one port and the TX and RX mirror ports
 *      should be identical.
 */
rtksw_api_ret_t dal_rtl8367c_mirror_portBased_set(rtksw_uint32 unit, rtksw_port_t mirroring_port, rtksw_portmask_t *pMirrored_rx_portmask, rtksw_portmask_t *pMirrored_tx_portmask)
{
    rtksw_api_ret_t retVal;
    rtksw_enable_t mirRx, mirTx;
    rtksw_uint32 i, pmask;
    rtksw_port_t source_port;

    /* Check initialization state */
    RTKSW_CHK_INIT_STATE(unit);

    /* Check port valid */
    RTKSW_CHK_PORT_VALID(unit, mirroring_port);

    if(NULL == pMirrored_rx_portmask)
        return RT_ERR_NULL_POINTER;

    if(NULL == pMirrored_tx_portmask)
        return RT_ERR_NULL_POINTER;

    RTKSW_CHK_PORTMASK_VALID(unit, pMirrored_rx_portmask);

    RTKSW_CHK_PORTMASK_VALID(unit, pMirrored_tx_portmask);

    /*Mirror Sorce Port Mask Check*/
    if (pMirrored_tx_portmask->bits[0]!=pMirrored_rx_portmask->bits[0]&&pMirrored_tx_portmask->bits[0]!=0&&pMirrored_rx_portmask->bits[0]!=0)
        return RT_ERR_PORT_MASK;

     /*mirror port != source port*/
    if(RTKSW_PORTMASK_IS_PORT_SET((*pMirrored_tx_portmask), mirroring_port) || RTKSW_PORTMASK_IS_PORT_SET((*pMirrored_rx_portmask), mirroring_port))
        return RT_ERR_PORT_MASK;

    source_port = rtksw_switch_maxLogicalPort_get(unit);

    RTKSW_SCAN_ALL_LOG_PORT(unit, i)
    {
        if (pMirrored_tx_portmask->bits[0]&(1<<i))
        {
            source_port = i;
            break;
        }

        if (pMirrored_rx_portmask->bits[0]&(1<<i))
        {
            source_port = i;
            break;
        }
    }

    if ((retVal = rtl8367c_setAsicPortMirror(unit, rtksw_switch_port_L2P_get(unit, source_port), rtksw_switch_port_L2P_get(unit, mirroring_port))) != RT_ERR_OK)
        return retVal;
    if(pMirrored_rx_portmask->bits[0] != 0)
    {
        if ((retVal = rtksw_switch_portmask_L2P_get(unit, pMirrored_rx_portmask, &pmask)) != RT_ERR_OK)
            return retVal;
        if ((retVal = rtl8367c_setAsicPortMirrorMask(unit, pmask)) != RT_ERR_OK)
            return retVal;
    }
    else
    {
        if ((retVal = rtksw_switch_portmask_L2P_get(unit, pMirrored_tx_portmask, &pmask)) != RT_ERR_OK)
            return retVal;
        if ((retVal = rtl8367c_setAsicPortMirrorMask(unit, pmask)) != RT_ERR_OK)
            return retVal;
    }


    if (pMirrored_rx_portmask->bits[0])
        mirRx = RTKSW_ENABLED;
    else
        mirRx = RTKSW_DISABLED;

    if ((retVal = rtl8367c_setAsicPortMirrorRxFunction(unit, mirRx)) != RT_ERR_OK)
        return retVal;

    if (pMirrored_tx_portmask->bits[0])
        mirTx = RTKSW_ENABLED;
    else
        mirTx = RTKSW_DISABLED;

    if ((retVal = rtl8367c_setAsicPortMirrorTxFunction(unit, mirTx)) != RT_ERR_OK)
        return retVal;

    return RT_ERR_OK;

}

/* Function Name:
 *      dal_rtl8367c_mirror_portBased_get
 * Description:
 *      Get port mirror function.
 * Input:
 *      unit                    - Unit ID
 * Output:
 *      pMirroring_port         - Monitor port.
 *      pMirrored_rx_portmask   - Rx mirror port mask.
 *      pMirrored_tx_portmask   - Tx mirror port mask.
 * Return:
 *      RT_ERR_OK           - OK
 *      RT_ERR_FAILED       - Failed
 *      RT_ERR_SMI          - SMI access error
 *      RT_ERR_INPUT        - Invalid input parameters.
 * Note:
 *      The API is to get mirror function of source port and mirror port.
 */
rtksw_api_ret_t dal_rtl8367c_mirror_portBased_get(rtksw_uint32 unit, rtksw_port_t *pMirroring_port, rtksw_portmask_t *pMirrored_rx_portmask, rtksw_portmask_t *pMirrored_tx_portmask)
{
    rtksw_api_ret_t retVal;
    rtksw_port_t source_port;
    rtksw_enable_t mirRx, mirTx;
    rtksw_uint32 sport, mport, pmask;

    /* Check initialization state */
    RTKSW_CHK_INIT_STATE(unit);

    if(NULL == pMirrored_rx_portmask)
        return RT_ERR_NULL_POINTER;

    if(NULL == pMirrored_tx_portmask)
        return RT_ERR_NULL_POINTER;

    if(NULL == pMirroring_port)
        return RT_ERR_NULL_POINTER;

    if ((retVal = rtl8367c_getAsicPortMirror(unit, &sport, &mport)) != RT_ERR_OK)
        return retVal;
    source_port = rtksw_switch_port_P2L_get(unit, sport);
    *pMirroring_port = rtksw_switch_port_P2L_get(unit, mport);

    if ((retVal = rtl8367c_getAsicPortMirrorRxFunction(unit, (rtksw_uint32*)&mirRx)) != RT_ERR_OK)
        return retVal;

    if ((retVal = rtl8367c_getAsicPortMirrorTxFunction(unit, (rtksw_uint32*)&mirTx)) != RT_ERR_OK)
        return retVal;

    if ((retVal = rtl8367c_getAsicPortMirrorMask(unit, &pmask)) != RT_ERR_OK)
        return retVal;

    if (RTKSW_DISABLED == mirRx)
        pMirrored_rx_portmask->bits[0]=0;
    else
    {
        if ((retVal = rtksw_switch_portmask_P2L_get(unit, pmask, pMirrored_rx_portmask)) != RT_ERR_OK)
            return retVal;
        pMirrored_rx_portmask->bits[0] |= 1<<source_port;
    }

     if (RTKSW_DISABLED == mirTx)
        pMirrored_tx_portmask->bits[0]=0;
    else
    {
        if ((retVal = rtksw_switch_portmask_P2L_get(unit, pmask, pMirrored_tx_portmask)) != RT_ERR_OK)
            return retVal;
        pMirrored_tx_portmask->bits[0] |= 1<<source_port;
    }

    return RT_ERR_OK;

}

/* Function Name:
 *      dal_rtl8367c_mirror_portIso_set
 * Description:
 *      Set mirror port isolation.
 * Input:
 *      unit    - Unit ID
 *      enable  - Mirror isolation status.
 * Output:
 *      None
 * Return:
 *      RT_ERR_OK           - OK
 *      RT_ERR_FAILED       - Failed
 *      RT_ERR_SMI          - SMI access error
 *      RT_ERR_ENABLE       - Invalid enable input
 * Note:
 *      The API is to set mirror isolation function that prevent normal forwarding packets to miror port.
 */
rtksw_api_ret_t dal_rtl8367c_mirror_portIso_set(rtksw_uint32 unit, rtksw_enable_t enable)
{
    rtksw_api_ret_t retVal;

    /* Check initialization state */
    RTKSW_CHK_INIT_STATE(unit);

    if (enable >= RTKSW_ENABLE_END)
        return RT_ERR_ENABLE;

    if ((retVal = rtl8367c_setAsicPortMirrorIsolation(unit, enable)) != RT_ERR_OK)
        return retVal;

    return RT_ERR_OK;
}

/* Function Name:
 *      dal_rtl8367c_mirror_portIso_get
 * Description:
 *      Get mirror port isolation.
 * Input:
 *      unit                    - Unit ID
 * Output:
 *      pEnable |Mirror isolation status.
 * Return:
 *      RT_ERR_OK           - OK
 *      RT_ERR_FAILED       - Failed
 *      RT_ERR_SMI          - SMI access error
 *      RT_ERR_INPUT        - Invalid input parameters.
 * Note:
 *      The API is to get mirror isolation status.
 */
rtksw_api_ret_t dal_rtl8367c_mirror_portIso_get(rtksw_uint32 unit, rtksw_enable_t *pEnable)
{
    rtksw_api_ret_t retVal;

    /* Check initialization state */
    RTKSW_CHK_INIT_STATE(unit);

    if(NULL == pEnable)
        return RT_ERR_NULL_POINTER;

    if ((retVal = rtl8367c_getAsicPortMirrorIsolation(unit, pEnable)) != RT_ERR_OK)
        return retVal;

    return RT_ERR_OK;
}

/* Function Name:
 *      dal_rtl8367c_mirror_vlanLeaky_set
 * Description:
 *      Set mirror VLAN leaky.
 * Input:
 *      unit        - Unit ID
 *      txenable    - TX leaky enable.
 *      rxenable    - RX leaky enable.
 * Output:
 *      None
 * Return:
 *      RT_ERR_OK           - OK
 *      RT_ERR_FAILED       - Failed
 *      RT_ERR_SMI          - SMI access error
 *      RT_ERR_ENABLE       - Invalid enable input
 * Note:
 *      The API is to set mirror VLAN leaky function forwarding packets to miror port.
 */
rtksw_api_ret_t dal_rtl8367c_mirror_vlanLeaky_set(rtksw_uint32 unit, rtksw_enable_t txenable, rtksw_enable_t rxenable)
{
    rtksw_api_ret_t retVal;

    /* Check initialization state */
    RTKSW_CHK_INIT_STATE(unit);

    if ((txenable >= RTKSW_ENABLE_END) ||(rxenable >= RTKSW_ENABLE_END))
        return RT_ERR_ENABLE;

    if ((retVal = rtl8367c_setAsicPortMirrorVlanTxLeaky(unit, txenable)) != RT_ERR_OK)
        return retVal;

    if ((retVal = rtl8367c_setAsicPortMirrorVlanRxLeaky(unit, rxenable)) != RT_ERR_OK)
        return retVal;

    return RT_ERR_OK;
}

/* Function Name:
 *      dal_rtl8367c_mirror_vlanLeaky_get
 * Description:
 *      Get mirror VLAN leaky.
 * Input:
 *      unit                    - Unit ID
 * Output:
 *      pTxenable - TX leaky enable.
 *      pRxenable - RX leaky enable.
 * Return:
 *      RT_ERR_OK           - OK
 *      RT_ERR_FAILED       - Failed
 *      RT_ERR_SMI          - SMI access error
 *      RT_ERR_INPUT        - Invalid input parameters.
 * Note:
 *      The API is to get mirror VLAN leaky status.
 */
rtksw_api_ret_t dal_rtl8367c_mirror_vlanLeaky_get(rtksw_uint32 unit, rtksw_enable_t *pTxenable, rtksw_enable_t *pRxenable)
{
    rtksw_api_ret_t retVal;

    /* Check initialization state */
    RTKSW_CHK_INIT_STATE(unit);

    if( (NULL == pTxenable) || (NULL == pRxenable) )
        return RT_ERR_NULL_POINTER;

    if ((retVal = rtl8367c_getAsicPortMirrorVlanTxLeaky(unit, pTxenable)) != RT_ERR_OK)
        return retVal;

    if ((retVal = rtl8367c_getAsicPortMirrorVlanRxLeaky(unit, pRxenable)) != RT_ERR_OK)
        return retVal;

    return RT_ERR_OK;
}

/* Function Name:
 *      dal_rtl8367c_mirror_isolationLeaky_set
 * Description:
 *      Set mirror Isolation leaky.
 * Input:
 *      unit        - Unit ID
 *      txenable    - TX leaky enable.
 *      rxenable    - RX leaky enable.
 * Output:
 *      None
 * Return:
 *      RT_ERR_OK           - OK
 *      RT_ERR_FAILED       - Failed
 *      RT_ERR_SMI          - SMI access error
 *      RT_ERR_ENABLE       - Invalid enable input
 * Note:
 *      The API is to set mirror VLAN leaky function forwarding packets to miror port.
 */
rtksw_api_ret_t dal_rtl8367c_mirror_isolationLeaky_set(rtksw_uint32 unit, rtksw_enable_t txenable, rtksw_enable_t rxenable)
{
    rtksw_api_ret_t retVal;

    /* Check initialization state */
    RTKSW_CHK_INIT_STATE(unit);

    if ((txenable >= RTKSW_ENABLE_END) ||(rxenable >= RTKSW_ENABLE_END))
        return RT_ERR_ENABLE;

    if ((retVal = rtl8367c_setAsicPortMirrorIsolationTxLeaky(unit, txenable)) != RT_ERR_OK)
        return retVal;

    if ((retVal = rtl8367c_setAsicPortMirrorIsolationRxLeaky(unit, rxenable)) != RT_ERR_OK)
        return retVal;

    return RT_ERR_OK;
}

/* Function Name:
 *      dal_rtl8367c_mirror_isolationLeaky_get
 * Description:
 *      Get mirror isolation leaky.
 * Input:
 *      unit      - Unit ID
 * Output:
 *      pTxenable - TX leaky enable.
 *      pRxenable - RX leaky enable.
 * Return:
 *      RT_ERR_OK           - OK
 *      RT_ERR_FAILED       - Failed
 *      RT_ERR_SMI          - SMI access error
 *      RT_ERR_INPUT        - Invalid input parameters.
 * Note:
 *      The API is to get mirror isolation leaky status.
 */
rtksw_api_ret_t dal_rtl8367c_mirror_isolationLeaky_get(rtksw_uint32 unit, rtksw_enable_t *pTxenable, rtksw_enable_t *pRxenable)
{
    rtksw_api_ret_t retVal;

    /* Check initialization state */
    RTKSW_CHK_INIT_STATE(unit);

    if( (NULL == pTxenable) || (NULL == pRxenable) )
        return RT_ERR_NULL_POINTER;

    if ((retVal = rtl8367c_getAsicPortMirrorIsolationTxLeaky(unit, pTxenable)) != RT_ERR_OK)
        return retVal;

    if ((retVal = rtl8367c_getAsicPortMirrorIsolationRxLeaky(unit, pRxenable)) != RT_ERR_OK)
        return retVal;

    return RT_ERR_OK;
}

/* Function Name:
 *      dal_rtl8367c_mirror_keep_set
 * Description:
 *      Set mirror packet format keep.
 * Input:
 *      unit    - Unit ID
 *      mode    - mirror keep mode.
 * Output:
 *      None
 * Return:
 *      RT_ERR_OK           - OK
 *      RT_ERR_FAILED       - Failed
 *      RT_ERR_SMI          - SMI access error
 *      RT_ERR_ENABLE       - Invalid enable input
 * Note:
 *      The API is to set  -mirror keep mode.
 *      The mirror keep mode is as following:
 *      - MIRROR_FOLLOW_VLAN
 *      - MIRROR_KEEP_ORIGINAL
 *      - MIRROR_KEEP_END
 */
rtksw_api_ret_t dal_rtl8367c_mirror_keep_set(rtksw_uint32 unit, rtksw_mirror_keep_t mode)
{
    rtksw_api_ret_t retVal;

    /* Check initialization state */
    RTKSW_CHK_INIT_STATE(unit);

    if (mode >= MIRROR_KEEP_END)
        return RT_ERR_ENABLE;

    if ((retVal = rtl8367c_setAsicPortMirrorRealKeep(unit, mode)) != RT_ERR_OK)
        return retVal;

    return RT_ERR_OK;
}

/* Function Name:
 *      dal_rtl8367c_mirror_keep_get
 * Description:
 *      Get mirror packet format keep.
 * Input:
 *      unit            - Unit ID
 * Output:
 *      pMode - mirror keep mode.
 * Return:
 *      RT_ERR_OK           - OK
 *      RT_ERR_FAILED       - Failed
 *      RT_ERR_SMI          - SMI access error
 *      RT_ERR_INPUT        - Invalid input parameters.
 * Note:
 *      The API is to get mirror keep mode.
 *      The mirror keep mode is as following:
 *      - MIRROR_FOLLOW_VLAN
 *      - MIRROR_KEEP_ORIGINAL
 *      - MIRROR_KEEP_END
 */
rtksw_api_ret_t dal_rtl8367c_mirror_keep_get(rtksw_uint32 unit, rtksw_mirror_keep_t *pMode)
{
    rtksw_api_ret_t retVal;

    /* Check initialization state */
    RTKSW_CHK_INIT_STATE(unit);

    if(NULL == pMode)
        return RT_ERR_NULL_POINTER;

    if ((retVal = rtl8367c_getAsicPortMirrorRealKeep(unit, pMode)) != RT_ERR_OK)
        return retVal;

    return RT_ERR_OK;
}

/* Function Name:
 *      dal_rtl8367c_mirror_override_set
 * Description:
 *      Set port mirror override function.
 * Input:
 *      unit            - Unit ID
 *      rxMirror        - 1: output mirrored packet, 0: output normal forward packet
 *      txMirror        - 1: output mirrored packet, 0: output normal forward packet
 *      aclMirror       - 1: output mirrored packet, 0: output normal forward packet
 * Output:
 *      None
 * Return:
 *      RT_ERR_OK           - OK
 *      RT_ERR_FAILED       - Failed
 *      RT_ERR_SMI          - SMI access error
 * Note:
 *      The API is to set mirror override function.
 *      This function control the output format when a port output
 *      normal forward & mirrored packet at the same time.
 */
rtksw_api_ret_t dal_rtl8367c_mirror_override_set(rtksw_uint32 unit, rtksw_enable_t rxMirror, rtksw_enable_t txMirror, rtksw_enable_t aclMirror)
{
    rtksw_api_ret_t retVal;

    if( (rxMirror >= RTKSW_ENABLE_END) || (txMirror >= RTKSW_ENABLE_END) || (aclMirror >= RTKSW_ENABLE_END))
        return RT_ERR_ENABLE;

    if ((retVal = rtl8367c_setAsicPortMirrorOverride(unit, (rtksw_uint32)rxMirror, (rtksw_uint32)txMirror, (rtksw_uint32)aclMirror)) != RT_ERR_OK)
        return retVal;

    return RT_ERR_OK;
}

/* Function Name:
 *      dal_rtl8367c_mirror_override_get
 * Description:
 *      Get port mirror override function.
 * Input:
 *      unit            - Unit ID
 * Output:
 *      pRxMirror       - 1: output mirrored packet, 0: output normal forward packet
 *      pTxMirror       - 1: output mirrored packet, 0: output normal forward packet
 *      pAclMirror      - 1: output mirrored packet, 0: output normal forward packet
 * Return:
 *      RT_ERR_OK           - OK
 *      RT_ERR_FAILED       - Failed
 *      RT_ERR_SMI          - SMI access error
 *      RT_ERR_NULL_POINTER - Null Pointer
 * Note:
 *      The API is to Get mirror override function.
 *      This function control the output format when a port output
 *      normal forward & mirrored packet at the same time.
 */
rtksw_api_ret_t dal_rtl8367c_mirror_override_get(rtksw_uint32 unit, rtksw_enable_t *pRxMirror, rtksw_enable_t *pTxMirror, rtksw_enable_t *pAclMirror)
{
    rtksw_api_ret_t retVal;

    if( (pRxMirror == NULL) || (pTxMirror == NULL) || (pAclMirror == NULL))
        return RT_ERR_ENABLE;

    if ((retVal = rtl8367c_getAsicPortMirrorOverride(unit, (rtksw_uint32 *)pRxMirror, (rtksw_uint32 *)pTxMirror, (rtksw_uint32 *)pAclMirror)) != RT_ERR_OK)
        return retVal;

    return RT_ERR_OK;
}


