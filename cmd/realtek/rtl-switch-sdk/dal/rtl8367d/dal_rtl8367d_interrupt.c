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
 * Feature : Here is a list of all functions and variables in Interrupt module.
 *
 */

#include "../../rtk_switch.h"
#include "../../rtk_error.h"
#include "dal_rtl8367d_interrupt.h"

#include "rtl8367d_asicdrv.h"

#include "../dal_mgmts.h"

/* Function Name:
 *      dal_rtl8367d_int_polarity_set
 * Description:
 *      Set interrupt polarity configuration.
 * Input:
 *      unit    - Unit ID
 *      type    - Interruptpolarity type.
 * Output:
 *      None
 * Return:
 *      RT_ERR_OK           - OK
 *      RT_ERR_FAILED       - Failed
 *      RT_ERR_SMI          - SMI access error
 *      RT_ERR_INPUT        - Invalid input parameters.
 * Note:
 *      The API can set interrupt polarity configuration.
 */
rtksw_api_ret_t dal_rtl8367d_int_polarity_set(rtksw_uint32 unit, rtksw_int_polarity_t type)
{
    rtksw_api_ret_t retVal;

    /* Check initialization state */
    RTKSW_CHK_INIT_STATE(unit);

    if(type >= INT_POLAR_END)
        return RT_ERR_INPUT;

    if ((retVal = rtl8367d_setAsicRegBit(unit, RTL8367D_REG_INTR_CTRL, RTL8367D_INTR_POLARITY_OFFSET, type)) != RT_ERR_OK)
        return retVal;

    return RT_ERR_OK;
}

/* Function Name:
 *      dal_rtl8367d_int_polarity_get
 * Description:
 *      Get interrupt polarity configuration.
 * Input:
 *      unit    - Unit ID
 * Output:
 *      pType - Interruptpolarity type.
 * Return:
 *      RT_ERR_OK           - OK
 *      RT_ERR_FAILED       - Failed
 *      RT_ERR_SMI          - SMI access error
 * Note:
 *      The API can get interrupt polarity configuration.
 */
rtksw_api_ret_t dal_rtl8367d_int_polarity_get(rtksw_uint32 unit, rtksw_int_polarity_t *pType)
{
    rtksw_api_ret_t retVal;

    /* Check initialization state */
    RTKSW_CHK_INIT_STATE(unit);

    if(NULL == pType)
        return RT_ERR_NULL_POINTER;

    if ((retVal = rtl8367d_getAsicRegBit(unit, RTL8367D_REG_INTR_CTRL, RTL8367D_INTR_POLARITY_OFFSET, pType)) != RT_ERR_OK)
        return retVal;

    return RT_ERR_OK;
}

/* Function Name:
 *      dal_rtl8367d_int_control_set
 * Description:
 *      Set interrupt trigger status configuration.
 * Input:
 *      unit    - Unit ID
 *      type    - Interrupt type.
 *      enable  - Interrupt status.
 * Output:
 *      None
 * Return:
 *      RT_ERR_OK           - OK
 *      RT_ERR_FAILED       - Failed
 *      RT_ERR_SMI          - SMI access error
 *      RT_ERR_INPUT        - Invalid input parameters.
 *      RT_ERR_ENABLE       - Invalid enable input.
 * Note:
 *      The API can set interrupt status configuration.
 *      The interrupt trigger status is shown in the following:
 *      - INT_TYPE_LINK_STATUS
 *      - INT_TYPE_METER_EXCEED
 *      - INT_TYPE_LEARN_LIMIT
 *      - INT_TYPE_LINK_SPEED
 *      - INT_TYPE_CONGEST
 *      - INT_TYPE_GREEN_FEATURE
 *      - INT_TYPE_LOOP_DETECT
 *      - INT_TYPE_8051,
 *      - INT_TYPE_CABLE_DIAG,
 *      - INT_TYPE_ACL,
 *      - INT_TYPE_SLIENT

 */
rtksw_api_ret_t dal_rtl8367d_int_control_set(rtksw_uint32 unit, rtksw_int_type_t type, rtksw_enable_t enable)
{
    rtksw_api_ret_t retVal;
    rtksw_uint32 mask;

    /* Check initialization state */
    RTKSW_CHK_INIT_STATE(unit);

    if (type >= INT_TYPE_END)
        return RT_ERR_INPUT;

    if ((type == INT_TYPE_GREEN_FEATURE) || (type == INT_TYPE_PTP1588) || (type == INT_TYPE_THERMAL_METER_LOW) || (type == INT_TYPE_THERMAL_METER_HIGH))
        return RT_ERR_INPUT;

    if ((retVal = rtl8367d_getAsicReg(unit, RTL8367D_REG_INTR_IMR, &mask)) != RT_ERR_OK)
        return retVal;

    if (RTKSW_ENABLED == enable)
        mask = mask | (1<<type);
    else if (RTKSW_DISABLED == enable)
        mask = mask & ~(1<<type);
    else
        return RT_ERR_INPUT;

    if ((retVal = rtl8367d_setAsicReg(unit, RTL8367D_REG_INTR_IMR, mask)) != RT_ERR_OK)
        return retVal;


    return RT_ERR_OK;
}

/* Function Name:
 *      dal_rtl8367d_int_control_get
 * Description:
 *      Get interrupt trigger status configuration.
 * Input:
 *      unit    - Unit ID
 *      type    - Interrupt type.
 * Output:
 *      pEnable - Interrupt status.
 * Return:
 *      RT_ERR_OK           - OK
 *      RT_ERR_FAILED       - Failed
 *      RT_ERR_SMI          - SMI access error
 *      RT_ERR_INPUT        - Invalid input parameters.
 * Note:
 *      The API can get interrupt status configuration.
 *      The interrupt trigger status is shown in the following:
 *      - INT_TYPE_LINK_STATUS
 *      - INT_TYPE_METER_EXCEED
 *      - INT_TYPE_LEARN_LIMIT
 *      - INT_TYPE_LINK_SPEED
 *      - INT_TYPE_CONGEST
 *      - INT_TYPE_GREEN_FEATURE
 *      - INT_TYPE_LOOP_DETECT
 *      - INT_TYPE_8051,
 *      - INT_TYPE_CABLE_DIAG,
 *      - INT_TYPE_ACL,
 *      - INT_TYPE_UPS,
 *      - INT_TYPE_SLIENT

 */
rtksw_api_ret_t dal_rtl8367d_int_control_get(rtksw_uint32 unit, rtksw_int_type_t type, rtksw_enable_t *pEnable)
{
    rtksw_api_ret_t retVal;
    rtksw_uint32 mask;

    /* Check initialization state */
    RTKSW_CHK_INIT_STATE(unit);

    if(NULL == pEnable)
        return RT_ERR_NULL_POINTER;

    if ((type == INT_TYPE_GREEN_FEATURE) || (type == INT_TYPE_PTP1588) || (type == INT_TYPE_THERMAL_METER_LOW) || (type == INT_TYPE_THERMAL_METER_HIGH))
        return RT_ERR_INPUT;

    if ((retVal = rtl8367d_getAsicReg(unit, RTL8367D_REG_INTR_IMR, &mask)) != RT_ERR_OK)
        return retVal;

    if (0 == (mask&(1<<type)))
        *pEnable=RTKSW_DISABLED;
    else
        *pEnable=RTKSW_ENABLED;

    return RT_ERR_OK;
}

/* Function Name:
 *      dal_rtl8367d_int_status_set
 * Description:
 *      Set interrupt trigger status to clean.
 * Input:
 *      unit    - Unit ID
 * Output:
 *      pStatusMask - Interrupt status bit mask.
 * Return:
 *      RT_ERR_OK              - OK
 *      RT_ERR_FAILED          - Failed
 *      RT_ERR_SMI             - SMI access error
 *      RT_ERR_INPUT - Invalid input parameters.
 * Note:
 *      The API can clean interrupt trigger status when interrupt happened.
 *      The interrupt trigger status is shown in the following:
 *      - INT_TYPE_LINK_STATUS    (value[0] (Bit0))
 *      - INT_TYPE_METER_EXCEED   (value[0] (Bit1))
 *      - INT_TYPE_LEARN_LIMIT    (value[0] (Bit2))
 *      - INT_TYPE_LINK_SPEED     (value[0] (Bit3))
 *      - INT_TYPE_CONGEST        (value[0] (Bit4))
 *      - INT_TYPE_GREEN_FEATURE  (value[0] (Bit5))
 *      - INT_TYPE_LOOP_DETECT    (value[0] (Bit6))
 *      - INT_TYPE_8051           (value[0] (Bit7))
 *      - INT_TYPE_CABLE_DIAG     (value[0] (Bit8))
 *      - INT_TYPE_ACL            (value[0] (Bit9))
 *      - INT_TYPE_SLIENT         (value[0] (Bit11))
 *      The status will be cleared after execute this API.

 */
rtksw_api_ret_t dal_rtl8367d_int_status_set(rtksw_uint32 unit, rtksw_int_status_t *pStatusMask)
{
    rtksw_api_ret_t retVal;

    /* Check initialization state */
    RTKSW_CHK_INIT_STATE(unit);

    if(NULL == pStatusMask)
        return RT_ERR_NULL_POINTER;

    if((pStatusMask->value[0] & (0x0001 << INT_TYPE_GREEN_FEATURE)) || (pStatusMask->value[0] & (0x0001 << INT_TYPE_PTP1588)) || (pStatusMask->value[0] & (0x0001 << INT_TYPE_THERMAL_METER_LOW)) || (pStatusMask->value[0] & (0x0001 << INT_TYPE_THERMAL_METER_HIGH)))
        return RT_ERR_INPUT;

    if(pStatusMask->value[0] >= (0x0001 << INT_TYPE_END))
        return RT_ERR_INPUT;

    if ((retVal = rtl8367d_setAsicReg(unit, RTL8367D_REG_INTR_IMS, (rtksw_uint32)pStatusMask->value[0]))!=RT_ERR_OK)
        return retVal;

    return RT_ERR_OK;
}

/* Function Name:
 *      dal_rtl8367d_int_status_get
 * Description:
 *      Get interrupt trigger status.
 * Input:
 *      unit    - Unit ID
 * Output:
 *      pStatusMask - Interrupt status bit mask.
 * Return:
 *      RT_ERR_OK           - OK
 *      RT_ERR_FAILED       - Failed
 *      RT_ERR_SMI          - SMI access error
 *      RT_ERR_INPUT        - Invalid input parameters.
 * Note:
 *      The API can get interrupt trigger status when interrupt happened.
 *      The interrupt trigger status is shown in the following:
 *      - INT_TYPE_LINK_STATUS    (value[0] (Bit0))
 *      - INT_TYPE_METER_EXCEED   (value[0] (Bit1))
 *      - INT_TYPE_LEARN_LIMIT    (value[0] (Bit2))
 *      - INT_TYPE_LINK_SPEED     (value[0] (Bit3))
 *      - INT_TYPE_CONGEST        (value[0] (Bit4))
 *      - INT_TYPE_GREEN_FEATURE  (value[0] (Bit5))
 *      - INT_TYPE_LOOP_DETECT    (value[0] (Bit6))
 *      - INT_TYPE_8051           (value[0] (Bit7))
 *      - INT_TYPE_CABLE_DIAG     (value[0] (Bit8))
 *      - INT_TYPE_ACL            (value[0] (Bit9))
 *      - INT_TYPE_SLIENT         (value[0] (Bit11))

 *
 */
rtksw_api_ret_t dal_rtl8367d_int_status_get(rtksw_uint32 unit, rtksw_int_status_t* pStatusMask)
{
    rtksw_api_ret_t   retVal;
    rtksw_uint32          ims_mask;

    /* Check initialization state */
    RTKSW_CHK_INIT_STATE(unit);

    if(NULL == pStatusMask)
        return RT_ERR_NULL_POINTER;

    if ((retVal = rtl8367d_getAsicReg(unit, RTL8367D_REG_INTR_IMS, &ims_mask)) != RT_ERR_OK)
        return retVal;

    pStatusMask->value[0] = (ims_mask & 0x00000FFF);
    return RT_ERR_OK;
}

#define ADV_NOT_SUPPORT (0xFFFF)
static rtksw_api_ret_t _rtksw_int_Advidx_get(rtksw_int_advType_t adv_type, rtksw_uint32 *pAsic_idx)
{
    rtksw_uint32 asic_idx[ADV_END] =
    {
        RTL8367D_INTRST_L2_LEARN,
        RTL8367D_INTRST_SPEED_CHANGE,
        RTL8367D_INTRST_SPECIAL_CONGESTION,
        RTL8367D_INTRST_RTKSW_PORT_LINKDOWN,
        RTL8367D_INTRST_RTKSW_PORT_LINKUP,
        ADV_NOT_SUPPORT,
        RTL8367D_INTRST_RLDP_LOOPED,
        RTL8367D_INTRST_RLDP_RELEASED,
    };

    if(adv_type >= ADV_END)
        return RT_ERR_INPUT;

    if(asic_idx[adv_type] == ADV_NOT_SUPPORT)
        return RT_ERR_CHIP_NOT_SUPPORTED;

    *pAsic_idx = asic_idx[adv_type];
    return RT_ERR_OK;
}

static rtksw_api_ret_t _rtl8367d_getInterruptRelatedStatus(rtksw_uint32 unit, rtksw_uint32 type, rtksw_uint32* pStatus)
{
    CONST rtksw_uint32 indicatorAddress[RTL8367D_INTRST_END] = {RTL8367D_REG_LEARN_OVER_INDICATOR,
                                                    RTL8367D_REG_SPEED_CHANGE_INDICATOR,
                                                    RTL8367D_REG_SPECIAL_CONGEST_INDICATOR,
                                                    RTL8367D_REG_RTKSW_PORT_LINKDOWN_INDICATOR,
                                                    RTL8367D_REG_RTKSW_PORT_LINKUP_INDICATOR,
                                                    RTL8367D_REG_METER_OVERRATE_INDICATOR0,
                                                    RTL8367D_REG_METER_OVERRATE_INDICATOR1,
                                                    RTL8367D_REG_METER_OVERRATE_INDICATOR2,
                                                    RTL8367D_REG_RLDP_LOOPED_INDICATOR,
                                                    RTL8367D_REG_RLDP_RELEASED_INDICATOR,
                                                    RTL8367D_REG_SYSTEM_LEARN_OVER_INDICATOR};

    if(type >= RTL8367D_INTRST_END )
        return RT_ERR_OUT_OF_RANGE;

    return rtl8367d_getAsicReg(unit, indicatorAddress[type], pStatus);
}

static rtksw_api_ret_t _rtl8367d_setInterruptRelatedStatus(rtksw_uint32 unit, rtksw_uint32 type, rtksw_uint32 status)
{
    CONST rtksw_uint32 indicatorAddress[RTL8367D_INTRST_END] = {RTL8367D_REG_LEARN_OVER_INDICATOR,
                                                    RTL8367D_REG_SPEED_CHANGE_INDICATOR,
                                                    RTL8367D_REG_SPECIAL_CONGEST_INDICATOR,
                                                    RTL8367D_REG_RTKSW_PORT_LINKDOWN_INDICATOR,
                                                    RTL8367D_REG_RTKSW_PORT_LINKUP_INDICATOR,
                                                    RTL8367D_REG_METER_OVERRATE_INDICATOR0,
                                                    RTL8367D_REG_METER_OVERRATE_INDICATOR1,
                                                    RTL8367D_REG_METER_OVERRATE_INDICATOR2,
                                                    RTL8367D_REG_RLDP_LOOPED_INDICATOR,
                                                    RTL8367D_REG_RLDP_RELEASED_INDICATOR,
                                                    RTL8367D_REG_SYSTEM_LEARN_OVER_INDICATOR};

    if(type >= RTL8367D_INTRST_END )
        return RT_ERR_OUT_OF_RANGE;

    return rtl8367d_setAsicReg(unit, indicatorAddress[type], status);
}


/* Function Name:
 *      dal_rtl8367d_int_advanceInfo_get
 * Description:
 *      Get interrupt advanced information.
 * Input:
 *      unit        - Unit ID
 *      adv_type    - Advanced interrupt type.
 * Output:
 *      info - Information per type.
 * Return:
 *      RT_ERR_OK           - OK
 *      RT_ERR_FAILED       - Failed
 *      RT_ERR_SMI          - SMI access error
 *      RT_ERR_INPUT        - Invalid input parameters.
 * Note:
 *      This API can get advanced information when interrupt happened.
 *      The status will be cleared after execute this API.
 */
rtksw_api_ret_t dal_rtl8367d_int_advanceInfo_get(rtksw_uint32 unit, rtksw_int_advType_t adv_type, rtksw_int_info_t *pInfo)
{
    rtksw_api_ret_t   retVal;
    rtksw_uint32      data;
    rtksw_uint32      intAdvType;

    /* Check initialization state */
    RTKSW_CHK_INIT_STATE(unit);

    if(adv_type >= ADV_END)
        return RT_ERR_INPUT;

    if(NULL == pInfo)
        return RT_ERR_NULL_POINTER;

    if(adv_type != ADV_METER_EXCEED_MASK)
    {
        if((retVal = _rtksw_int_Advidx_get(adv_type, &intAdvType)) != RT_ERR_OK)
            return retVal;
    }

    switch(adv_type)
    {
        case ADV_L2_LEARN_PORT_MASK:
            /* Get physical portmask */
            if((retVal = _rtl8367d_getInterruptRelatedStatus(unit, intAdvType, &data)) != RT_ERR_OK)
                return retVal;

            /* Clear Advanced Info */
            if((retVal = _rtl8367d_setInterruptRelatedStatus(unit, intAdvType, 0xFFFF)) != RT_ERR_OK)
                return retVal;

            /* Translate to logical portmask */
            if((retVal = rtksw_switch_portmask_P2L_get(unit, data, &(pInfo->portMask))) != RT_ERR_OK)
                return retVal;

            /* Get system learn */
            if((retVal = _rtl8367d_getInterruptRelatedStatus(unit, RTL8367D_INTRST_SYS_LEARN, &data)) != RT_ERR_OK)
                return retVal;

            /* Clear system learn */
            if((retVal = _rtl8367d_setInterruptRelatedStatus(unit, RTL8367D_INTRST_SYS_LEARN, 0x0001)) != RT_ERR_OK)
                return retVal;

            pInfo->systemLearnOver = data;
            break;
        case ADV_SPEED_CHANGE_PORT_MASK:
        case ADV_SPECIAL_CONGESTION_PORT_MASK:
        case ADV_PORT_LINKDOWN_PORT_MASK:
        case ADV_PORT_LINKUP_PORT_MASK:
        case ADV_RLDP_LOOPED:
        case ADV_RLDP_RELEASED:
            /* Get physical portmask */
            if((retVal = _rtl8367d_getInterruptRelatedStatus(unit, intAdvType, &data)) != RT_ERR_OK)
                return retVal;

            /* Clear Advanced Info */
            if((retVal = _rtl8367d_setInterruptRelatedStatus(unit, intAdvType, 0xFFFF)) != RT_ERR_OK)
                return retVal;

            /* Translate to logical portmask */
            if((retVal = rtksw_switch_portmask_P2L_get(unit, data, &(pInfo->portMask))) != RT_ERR_OK)
                return retVal;

            break;
        case ADV_METER_EXCEED_MASK:
            /* Get Meter Mask */
            if((retVal = _rtl8367d_getInterruptRelatedStatus(unit, RTL8367D_INTRST_METER0_15, &data)) != RT_ERR_OK)
                return retVal;

            /* Clear Advanced Info */
            if((retVal = _rtl8367d_setInterruptRelatedStatus(unit, RTL8367D_INTRST_METER0_15, 0xFFFF)) != RT_ERR_OK)
                return retVal;

            pInfo->meterMask[0] = data & 0xFFFF;

            /* Get Meter Mask */
            if((retVal = _rtl8367d_getInterruptRelatedStatus(unit, RTL8367D_INTRST_METER16_31, &data)) != RT_ERR_OK)
                return retVal;

            /* Clear Advanced Info */
            if((retVal = _rtl8367d_setInterruptRelatedStatus(unit, RTL8367D_INTRST_METER16_31, 0xFFFF)) != RT_ERR_OK)
                return retVal;

            pInfo->meterMask[0] = pInfo->meterMask[0] | ((data << 16) & 0xFFFF0000);

            /* Get Meter Mask */
            if((retVal = _rtl8367d_getInterruptRelatedStatus(unit, RTL8367D_INTRST_METER32_39, &data)) != RT_ERR_OK)
                return retVal;

            /* Clear Advanced Info */
            if((retVal = _rtl8367d_setInterruptRelatedStatus(unit, RTL8367D_INTRST_METER32_39, 0xFFFF)) != RT_ERR_OK)
                return retVal;

            pInfo->meterMask[1] = data & 0x00FF;

            break;
        default:
            return RT_ERR_INPUT;
    }

    return RT_ERR_OK;
}

