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
 * Purpose : RTL8367/RTL8367C switch high-level API
 *
 * Feature : The file includes time module high-layer API defination
 *
 */

#ifndef __DAL_RTL8367C_PTP_H__
#define __DAL_RTL8367C_PTP_H__

#include "../../ptp.h"

/*
 * Symbol Definition
 */
#define DAL_RTL8367C_MAX_NUM_OF_NANO_SECOND                     0x3B9AC9FF
#define DAL_RTL8367C_PTP_INTR_MASK                                          0xFF
#define DAL_RTL8367C_MAX_NUM_OF_TPID                                    0xFFFF

/*
 * Data Declaration
 */

/*
 * Function Declaration
 */
/* Function Name:
 *      dal_rtl8367c_ptp_init
 * Description:
 *      PTP function initialization.
 * Input:
 *      unit        - Unit ID
 * Output:
 *      None
 * Return:
 *      RT_ERR_OK              - OK
 *      RT_ERR_FAILED          - Failed
 *      RT_ERR_SMI             - SMI access error
 * Note:
 *      This API is used to initialize EEE status.
 */
extern rtksw_api_ret_t dal_rtl8367c_ptp_init(rtksw_uint32 unit);

/* Function Name:
 *      dal_rtl8367c_ptp_mac_set
 * Description:
 *      Configure PTP mac address.
 * Input:
 *      unit    - Unit ID
 *      mac     - mac address to parser PTP packets.
 * Output:
 *      None
 * Return:
 *      RT_ERR_OK           - OK
 *      RT_ERR_FAILED       - Failed
 *      RT_ERR_SMI          - SMI access error
 *      RT_ERR_INPUT        - Invalid input parameter.
 * Note:
 *      None
 */
extern rtksw_api_ret_t dal_rtl8367c_ptp_mac_set(rtksw_uint32 unit, rtksw_mac_t mac);

/* Function Name:
 *      dal_rtl8367c_ptp_mac_get
 * Description:
 *      Get PTP mac address.
 * Input:
 *      unit        - Unit ID
 * Output:
 *      pMac - mac address to parser PTP packets.
 * Return:
 *      RT_ERR_OK           - OK
 *      RT_ERR_FAILED       - Failed
 *      RT_ERR_SMI          - SMI access error
 *      RT_ERR_INPUT        - Invalid input parameter.
 * Note:
 *      None
 */
extern rtksw_api_ret_t dal_rtl8367c_ptp_mac_get(rtksw_uint32 unit, rtksw_mac_t *pMac);

/* Function Name:
 *      dal_rtl8367c_ptp_tpid_set
 * Description:
 *      Configure PTP accepted outer & inner tag TPID.
 * Input:
 *      unit        - Unit ID
 *      outerId     - Ether type of S-tag frame parsing in PTP ports.
 *      innerId     - Ether type of C-tag frame parsing in PTP ports.
 * Output:
 *      None
 * Return:
 *      RT_ERR_OK           - OK
 *      RT_ERR_FAILED       - Failed
 *      RT_ERR_SMI          - SMI access error
 *      RT_ERR_INPUT        - Invalid input parameter.
 * Note:
 *      None
 */
extern rtksw_api_ret_t dal_rtl8367c_ptp_tpid_set(rtksw_uint32 unit, rtksw_ptp_tpid_t outerId, rtksw_ptp_tpid_t innerId);

/* Function Name:
 *      dal_rtl8367c_ptp_tpid_get
 * Description:
 *      Get PTP accepted outer & inner tag TPID.
 * Input:
 *      unit        - Unit ID
 * Output:
 *      pOuterId - Ether type of S-tag frame parsing in PTP ports.
 *      pInnerId - Ether type of C-tag frame parsing in PTP ports.
 * Return:
 *      RT_ERR_OK           - OK
 *      RT_ERR_FAILED       - Failed
 *      RT_ERR_SMI          - SMI access error
 * Note:
 *      None
 */
extern rtksw_api_ret_t dal_rtl8367c_ptp_tpid_get(rtksw_uint32 unit, rtksw_ptp_tpid_t *pOuterId, rtksw_ptp_tpid_t *pInnerId);

/* Function Name:
 *      dal_rtl8367c_ptp_refTime_set
 * Description:
 *      Set the reference time of the specified device.
 * Input:
 *      unit        - Unit ID
 *      timeStamp   - reference timestamp value
 * Output:
 *      None
 * Return:
 *      RT_ERR_OK
 *      RT_ERR_FAILED
 *      RT_ERR_INPUT    - invalid input parameter
 * Applicable:
 *      8390, 8380
 * Note:
 *      None
 */
extern rtksw_api_ret_t dal_rtl8367c_ptp_refTime_set(rtksw_uint32 unit, rtksw_ptp_timeStamp_t timeStamp);

/* Function Name:
 *      dal_rtl8367c_ptp_refTime_get
 * Description:
 *      Get the reference time of the specified device.
 * Input:
 *      unit        - Unit ID
 * Output:
 *      pTimeStamp - pointer buffer of the reference time
 * Return:
 *      RT_ERR_OK
 *      RT_ERR_FAILED
 *      RT_ERR_UNIT_ID      - invalid unit id
 *      RT_ERR_NOT_INIT     - The module is not initial
 *      RT_ERR_NULL_POINTER - input parameter may be null pointer
 * Applicable:
 *      8390, 8380
 * Note:
 *      None
 */
extern rtksw_api_ret_t dal_rtl8367c_ptp_refTime_get(rtksw_uint32 unit, rtksw_ptp_timeStamp_t *pTimeStamp);

/* Function Name:
 *      dal_rtl8367c_ptp_refTimeAdjust_set
 * Description:
 *      Adjust the reference time.
 * Input:
 *      unit        - Unit ID
 *      unit        - unit id
 *      sign        - significant
 *      timeStamp   - reference timestamp value
 * Output:
 *      None
 * Return:
 *      RT_ERR_OK
 *      RT_ERR_FAILED
 *      RT_ERR_UNIT_ID  - invalid unit id
 *      RT_ERR_NOT_INIT - The module is not initial
 *      RT_ERR_INPUT    - invalid input parameter
 * Note:
 *      sign=0 for positive adjustment, sign=1 for negative adjustment.
 */
extern rtksw_api_ret_t dal_rtl8367c_ptp_refTimeAdjust_set(rtksw_uint32 unit, rtksw_ptp_sys_adjust_t sign, rtksw_ptp_timeStamp_t timeStamp);

/* Function Name:
 *      dal_rtl8367c_ptp_refTimeEnable_set
 * Description:
 *      Set the enable state of reference time of the specified device.
 * Input:
 *      unit        - Unit ID
 *      enable      - status
 * Output:
 *      None
 * Return:
 *      RT_ERR_OK
 *      RT_ERR_FAILED
 *      RT_ERR_INPUT    - invalid input parameter
 * Note:
 *      None
 */
extern rtksw_api_ret_t dal_rtl8367c_ptp_refTimeEnable_set(rtksw_uint32 unit, rtksw_enable_t enable);

/* Function Name:
 *      dal_rtl8367c_ptp_refTimeEnable_get
 * Description:
 *      Get the enable state of reference time of the specified device.
 * Input:
 *      unit        - Unit ID
 * Output:
 *      pEnable - status
 * Return:
 *      RT_ERR_OK
 *      RT_ERR_FAILED
 *      RT_ERR_UNIT_ID      - invalid unit id
 *      RT_ERR_NOT_INIT     - The module is not initial
 *      RT_ERR_NULL_POINTER - input parameter may be null pointer
 * Applicable:
 *      8390, 8380
 * Note:
 *      None
 */
extern rtksw_api_ret_t dal_rtl8367c_ptp_refTimeEnable_get(rtksw_uint32 unit, rtksw_enable_t *pEnable);

/* Function Name:
 *      dal_rtl8367c_ptp_portEnable_set
 * Description:
 *      Set PTP status of the specified port.
 * Input:
 *      unit        - Unit ID
 *      port        - port id
 *      enable      - status
 * Output:
 *      None
 * Return:
 *      RT_ERR_OK
 *      RT_ERR_FAILED
 *      RT_ERR_PORT     - invalid port id
 *      RT_ERR_INPUT    - invalid input parameter
 * Note:
 *      None
 */
extern rtksw_api_ret_t dal_rtl8367c_ptp_portEnable_set(rtksw_uint32 unit, rtksw_port_t port, rtksw_enable_t enable);

/* Function Name:
 *      dal_rtl8367c_ptp_portEnable_get
 * Description:
 *      Get PTP status of the specified port.
 * Input:
 *      unit        - Unit ID
 *      port        - port id
 * Output:
 *      pEnable - status
 * Return:
 *      RT_ERR_OK
 *      RT_ERR_FAILED
 *      RT_ERR_PORT         - invalid port id
 *      RT_ERR_NULL_POINTER - input parameter may be null pointer
 * Note:
 *      None
 */
extern rtksw_api_ret_t dal_rtl8367c_ptp_portEnable_get(rtksw_uint32 unit, rtksw_port_t port, rtksw_enable_t *pEnable);

/* Function Name:
 *      dal_rtl8367c_ptp_portTimestamp_get
 * Description:
 *      Get PTP timstamp according to the PTP identifier on the dedicated port from the specified device.
 * Input:
 *      unit        - Unit ID
 *      unit        - unit id
 *      port        - port id
 *      type        - PTP message type
 * Output:
 *      pInfo      - pointer buffer of sequence ID and timestamp
 * Return:
 *      RT_ERR_OK
 *      RT_ERR_FAILED
 *      RT_ERR_PORT_ID      - invalid port id
 *      RT_ERR_INPUT        - invalid input parameter
 *      RT_ERR_NULL_POINTER - input parameter may be null pointer
 * Applicable:
 *      8390, 8380
 * Note:
 *      None
 */
extern rtksw_api_ret_t dal_rtl8367c_ptp_portTimestamp_get(rtksw_uint32 unit, rtksw_port_t port, rtksw_ptp_msgType_t type, rtksw_ptp_info_t *pInfo);

/* Function Name:
 *      dal_rtl8367c_ptp_intControl_set
 * Description:
 *      Set PTP interrupt trigger status configuration.
 * Input:
 *      unit        - Unit ID
 *      type        - Interrupt type.
 *      enable      - Interrupt status.
 * Output:
 *      None
 * Return:
 *      RT_ERR_OK           - OK
 *      RT_ERR_FAILED       - Failed
 *      RT_ERR_SMI          - SMI access error
 *      RT_ERR_INPUT        - Invalid input parameters.
 *      RT_ERR_ENABLE       - Invalid enable input.
 * Note:
 *      The API can set PTP interrupt status configuration.
 *      The interrupt trigger status is shown in the following:
 *          RTKSW_PTP_INT_TYPE_TX_SYNC = 0,
 *          RTKSW_PTP_INT_TYPE_TX_DELAY_REQ,
 *          RTKSW_PTP_INT_TYPE_TX_PDELAY_REQ,
 *          RTKSW_PTP_INT_TYPE_TX_PDELAY_RESP,
 *          RTKSW_PTP_INT_TYPE_RX_SYNC,
 *          RTKSW_PTP_INT_TYPE_RX_DELAY_REQ,
 *          RTKSW_PTP_INT_TYPE_RX_PDELAY_REQ,
 *          RTKSW_PTP_INT_TYPE_RX_PDELAY_RESP,
 *          RTKSW_PTP_INT_TYPE_ALL,
 */
extern rtksw_api_ret_t dal_rtl8367c_ptp_intControl_set(rtksw_uint32 unit, rtksw_ptp_intType_t type, rtksw_enable_t enable);

/* Function Name:
 *      dal_rtl8367c_ptp_intControl_get
 * Description:
 *      Get PTP interrupt trigger status configuration.
 * Input:
 *      unit        - Unit ID
 *      type        - Interrupt type.
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
 *          RTKSW_PTP_INT_TYPE_TX_SYNC = 0,
 *          RTKSW_PTP_INT_TYPE_TX_DELAY_REQ,
 *          RTKSW_PTP_INT_TYPE_TX_PDELAY_REQ,
 *          RTKSW_PTP_INT_TYPE_TX_PDELAY_RESP,
 *          RTKSW_PTP_INT_TYPE_RX_SYNC,
 *          RTKSW_PTP_INT_TYPE_RX_DELAY_REQ,
 *          RTKSW_PTP_INT_TYPE_RX_PDELAY_REQ,
 *          RTKSW_PTP_INT_TYPE_RX_PDELAY_RESP,
 */
extern rtksw_api_ret_t dal_rtl8367c_ptp_intControl_get(rtksw_uint32 unit, rtksw_ptp_intType_t type, rtksw_enable_t *pEnable);


/* Function Name:
 *      dal_rtl8367c_ptp_intStatus_get
 * Description:
 *      Get PTP port interrupt trigger status.
 * Input:
 *      unit        - Unit ID
 *      port        - physical port
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
 *      - PORT 0  INT    (value[0] (Bit0))
 *      - PORT 1  INT    (value[0] (Bit1))
 *      - PORT 2  INT    (value[0] (Bit2))
 *      - PORT 3  INT    (value[0] (Bit3))
 *      - PORT 4  INT   (value[0] (Bit4))

 *
 */
extern rtksw_api_ret_t dal_rtl8367c_ptp_intStatus_get(rtksw_uint32 unit, rtksw_ptp_intStatus_t *pStatusMask);

/* Function Name:
 *      rtksw_ptp_portIntStatus_set
 * Description:
 *      Set PTP port interrupt trigger status to clean.
 * Input:
 *      unit        - Unit ID
 *      port        - physical port
 *      statusMask  - Interrupt status bit mask.
 * Output:
 *      None
 * Return:
 *      RT_ERR_OK              - OK
 *      RT_ERR_FAILED          - Failed
 *      RT_ERR_SMI             - SMI access error
 *      RT_ERR_INPUT - Invalid input parameters.
 * Note:
 *      The API can clean interrupt trigger status when interrupt happened.
 *      The interrupt trigger status is shown in the following:
 *      - RTKSW_PTP_INT_TYPE_TX_SYNC              (value[0] (Bit0))
 *      - RTKSW_PTP_INT_TYPE_TX_DELAY_REQ      (value[0] (Bit1))
 *      - RTKSW_PTP_INT_TYPE_TX_PDELAY_REQ    (value[0] (Bit2))
 *      - RTKSW_PTP_INT_TYPE_TX_PDELAY_RESP   (value[0] (Bit3))
 *      - RTKSW_PTP_INT_TYPE_RX_SYNC              (value[0] (Bit4))
 *      - RTKSW_PTP_INT_TYPE_RX_DELAY_REQ      (value[0] (Bit5))
 *      - RTKSW_PTP_INT_TYPE_RX_PDELAY_REQ    (value[0] (Bit6))
 *      - RTKSW_PTP_INT_TYPE_RX_PDELAY_RESP   (value[0] (Bit7))
 *      The status will be cleared after execute this API.
 */
extern rtksw_api_ret_t dal_rtl8367c_ptp_portIntStatus_set(rtksw_uint32 unit, rtksw_port_t port, rtksw_ptp_intStatus_t statusMask);

/* Function Name:
 *      dal_rtl8367c_ptp_portIntStatus_get
 * Description:
 *      Get PTP port interrupt trigger status.
 * Input:
 *      unit        - Unit ID
 *      port        - physical port
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
 *      - RTKSW_PTP_INT_TYPE_TX_SYNC              (value[0] (Bit0))
 *      - RTKSW_PTP_INT_TYPE_TX_DELAY_REQ      (value[0] (Bit1))
 *      - RTKSW_PTP_INT_TYPE_TX_PDELAY_REQ    (value[0] (Bit2))
 *      - RTKSW_PTP_INT_TYPE_TX_PDELAY_RESP   (value[0] (Bit3))
 *      - RTKSW_PTP_INT_TYPE_RX_SYNC              (value[0] (Bit4))
 *      - RTKSW_PTP_INT_TYPE_RX_DELAY_REQ      (value[0] (Bit5))
 *      - RTKSW_PTP_INT_TYPE_RX_PDELAY_REQ    (value[0] (Bit6))
 *      - RTKSW_PTP_INT_TYPE_RX_PDELAY_RESP   (value[0] (Bit7))
 *
 */
extern rtksw_api_ret_t dal_rtl8367c_ptp_portIntStatus_get(rtksw_uint32 unit, rtksw_port_t port, rtksw_ptp_intStatus_t *pStatusMask);

/* Function Name:
 *      dal_rtl8367c_ptp_portTrap_set
 * Description:
 *      Set PTP packet trap of the specified port.
 * Input:
 *      unit        - Unit ID
 *      port        - port id
 *      enable      - status
 * Output:
 *      None
 * Return:
 *      RT_ERR_OK
 *      RT_ERR_FAILED
 *      RT_ERR_PORT     - invalid port id
 *      RT_ERR_INPUT    - invalid input parameter
 * Note:
 *      None
 */
extern rtksw_api_ret_t dal_rtl8367c_ptp_portTrap_set(rtksw_uint32 unit, rtksw_port_t port, rtksw_enable_t enable);

/* Function Name:
 *      dal_rtl8367c_ptp_portTrap_get
 * Description:
 *      Get PTP packet trap of the specified port.
 * Input:
 *      unit        - Unit ID
 *      port        - port id
 * Output:
 *      pEnable - status
 * Return:
 *      RT_ERR_OK
 *      RT_ERR_FAILED
 *      RT_ERR_PORT         - invalid port id
 *      RT_ERR_NULL_POINTER - input parameter may be null pointer
 * Note:
 *      None
 */
extern rtksw_api_ret_t dal_rtl8367c_ptp_portTrap_get(rtksw_uint32 unit, rtksw_port_t port, rtksw_enable_t *pEnable);

#endif /* __DAL_RTL8367C_PTP_H__ */
