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
 * Feature : The file includes ACL module high-layer API defination
 *
 */

#ifndef __DAL_RTL8367C_ACL_H__
#define __DAL_RTL8367C_ACL_H__

#include "../../acl.h"

/* Function Name:
 *      dal_rtl8367c_filter_igrAcl_init
 * Description:
 *      ACL initialization function
 * Input:
 *      unit            - Unit ID
 * Output:
 *      None
 * Return:
 *      RT_ERR_OK           - OK
 *      RT_ERR_FAILED       - Failed
 *      RT_ERR_SMI          - SMI access error
 *      RT_ERR_NULL_POINTER - Pointer pFilter_field or pFilter_cfg point to NULL.
 * Note:
 *      This function enable and intialize ACL function
 */
extern rtksw_api_ret_t dal_rtl8367c_filter_igrAcl_init(rtksw_uint32 unit);

/* Function Name:
 *      dal_rtl8367c_filter_igrAcl_field_add
 * Description:
 *      Add comparison rule to an ACL configuration
 * Input:
 *      unit            - Unit ID
 *      pFilter_cfg     - The ACL configuration that this function will add comparison rule
 *      pFilter_field   - The comparison rule that will be added.
 * Output:
 *      None
 * Return:
 *      RT_ERR_OK               - OK
 *      RT_ERR_FAILED           - Failed
 *      RT_ERR_SMI              - SMI access error
 *      RT_ERR_NULL_POINTER     - Pointer pFilter_field or pFilter_cfg point to NULL.
 *      RT_ERR_INPUT            - Invalid input parameters.
 * Note:
 *      This function add a comparison rule (*pFilter_field) to an ACL configuration (*pFilter_cfg).
 *      Pointer pFilter_cfg points to an ACL configuration structure, this structure keeps multiple ACL
 *      comparison rules by means of linked list. Pointer pFilter_field will be added to linked
 *      list keeped by structure that pFilter_cfg points to.
 */
extern rtksw_api_ret_t dal_rtl8367c_filter_igrAcl_field_add(rtksw_uint32 unit, rtksw_filter_cfg_t *pFilter_cfg, rtksw_filter_field_t *pFilter_field);

/* Function Name:
 *      dal_rtl8367c_filter_igrAcl_cfg_add
 * Description:
 *      Add an ACL configuration to ASIC
 * Input:
 *      unit            - Unit ID
 *      filter_id       - Start index of ACL configuration.
 *      pFilter_cfg     - The ACL configuration that this function will add comparison rule
 *      pFilter_action  - Action(s) of ACL configuration.
 * Output:
 *      ruleNum - number of rules written in acl table
 * Return:
 *      RT_ERR_OK                               - OK
 *      RT_ERR_FAILED                           - Failed
 *      RT_ERR_SMI                              - SMI access error
 *      RT_ERR_NULL_POINTER                     - Pointer pFilter_field or pFilter_cfg point to NULL.
 *      RT_ERR_INPUT                            - Invalid input parameters.
 *      RT_ERR_ENTRY_INDEX                      - Invalid filter_id .
 *      RT_ERR_NULL_POINTER                     - Pointer pFilter_action or pFilter_cfg point to NULL.
 *      RT_ERR_FILTER_INACL_ACT_NOT_SUPPORT     - Action is not supported in this chip.
 *      RT_ERR_FILTER_INACL_RULE_NOT_SUPPORT    - Rule is not supported.
 * Note:
 *      This function store pFilter_cfg, pFilter_action into ASIC. The starting
 *      index(es) is filter_id.
 */
extern rtksw_api_ret_t dal_rtl8367c_filter_igrAcl_cfg_add(rtksw_uint32 unit, rtksw_filter_id_t filter_id, rtksw_filter_cfg_t *pFilter_cfg, rtksw_filter_action_t *pAction, rtksw_filter_number_t *ruleNum);

/* Function Name:
 *      dal_rtl8367c_filter_igrAcl_cfg_del
 * Description:
 *      Delete an ACL configuration from ASIC
 * Input:
 *      unit        - Unit ID
 *      filter_id   - Start index of ACL configuration.
 * Output:
 *      None
 * Return:
 *      RT_ERR_OK               - OK
 *      RT_ERR_FAILED           - Failed
 *      RT_ERR_SMI              - SMI access error
 *      RT_ERR_FILTER_ENTRYIDX  - Invalid filter_id.
 * Note:
 *      This function delete a group of ACL rules starting from filter_id.
 */
extern rtksw_api_ret_t dal_rtl8367c_filter_igrAcl_cfg_del(rtksw_uint32 unit, rtksw_filter_id_t filter_id);

/* Function Name:
 *      dal_rtl8367c_filter_igrAcl_cfg_delAll
 * Description:
 *      Delete all ACL entries from ASIC
 * Input:
 *      unit            - Unit ID
 * Output:
 *      None
 * Return:
 *      RT_ERR_OK           - OK
 *      RT_ERR_FAILED       - Failed
 *      RT_ERR_SMI          - SMI access error
 * Note:
 *      This function delete all ACL configuration from ASIC.
 */
extern rtksw_api_ret_t dal_rtl8367c_filter_igrAcl_cfg_delAll(rtksw_uint32 unit);

/* Function Name:
 *      dal_rtl8367c_filter_igrAcl_cfg_get
 * Description:
 *      Get one ingress acl configuration from ASIC.
 * Input:
 *      unit            - Unit ID
 *      filter_id       - Start index of ACL configuration.
 * Output:
 *      pFilter_cfg     - buffer pointer of ingress acl data
 *      pFilter_action  - buffer pointer of ingress acl action
 * Return:
 *      RT_ERR_OK               - OK
 *      RT_ERR_FAILED           - Failed
 *      RT_ERR_SMI              - SMI access error
 *      RT_ERR_NULL_POINTER     - Pointer pFilter_action or pFilter_cfg point to NULL.
 *      RT_ERR_FILTER_ENTRYIDX  - Invalid entry index.
 * Note:
 *      This function delete all ACL configuration from ASIC.
 */
extern rtksw_api_ret_t dal_rtl8367c_filter_igrAcl_cfg_get(rtksw_uint32 unit, rtksw_filter_id_t filter_id, rtksw_filter_cfg_raw_t *pFilter_cfg, rtksw_filter_action_t *pAction);

/* Function Name:
 *      dal_rtl8367c_filter_igrAcl_unmatchAction_set
 * Description:
 *      Set action to packets when no ACL configuration match
 * Input:
 *      unit    - Unit ID
 *      port    - Port id.
 *      action  - Action.
 * Output:
 *      None
 * Return:
 *      RT_ERR_OK           - OK
 *      RT_ERR_FAILED       - Failed
 *      RT_ERR_SMI          - SMI access error
 *      RT_ERR_PORT_ID      - Invalid port id.
 *      RT_ERR_INPUT        - Invalid input parameters.
 * Note:
 *      This function sets action of packets when no ACL configruation matches.
 */
extern rtksw_api_ret_t dal_rtl8367c_filter_igrAcl_unmatchAction_set(rtksw_uint32 unit, rtksw_port_t port, rtksw_filter_unmatch_action_t action);

/* Function Name:
 *      dal_rtl8367c_filter_igrAcl_unmatchAction_get
 * Description:
 *      Get action to packets when no ACL configuration match
 * Input:
 *      unit    - Unit ID
 *      port    - Port id.
 * Output:
 *      pAction - Action.
 * Return:
 *      RT_ERR_OK           - OK
 *      RT_ERR_FAILED       - Failed
 *      RT_ERR_SMI          - SMI access error
 *      RT_ERR_PORT_ID      - Invalid port id.
 *      RT_ERR_INPUT        - Invalid input parameters.
 * Note:
 *      This function gets action of packets when no ACL configruation matches.
 */
extern rtksw_api_ret_t dal_rtl8367c_filter_igrAcl_unmatchAction_get(rtksw_uint32 unit, rtksw_port_t port, rtksw_filter_unmatch_action_t* action);

/* Function Name:
 *      dal_rtl8367c_filter_igrAcl_state_set
 * Description:
 *      Set state of ingress ACL.
 * Input:
 *      unit    - Unit ID
 *      port    - Port id.
 *      state   - Ingress ACL state.
 * Output:
 *      None
 * Return:
 *      RT_ERR_OK           - OK
 *      RT_ERR_FAILED       - Failed
 *      RT_ERR_SMI          - SMI access error
 *      RT_ERR_PORT_ID      - Invalid port id.
 *      RT_ERR_INPUT        - Invalid input parameters.
 * Note:
 *      This function gets action of packets when no ACL configruation matches.
 */
extern rtksw_api_ret_t dal_rtl8367c_filter_igrAcl_state_set(rtksw_uint32 unit, rtksw_port_t port, rtksw_filter_state_t state);

/* Function Name:
 *      dal_rtl8367c_filter_igrAcl_state_get
 * Description:
 *      Get state of ingress ACL.
 * Input:
 *      unit    - Unit ID
 *      port    - Port id.
 * Output:
 *      pState  - Ingress ACL state.
 * Return:
 *      RT_ERR_OK           - OK
 *      RT_ERR_FAILED       - Failed
 *      RT_ERR_SMI          - SMI access error
 *      RT_ERR_PORT_ID      - Invalid port id.
 *      RT_ERR_INPUT        - Invalid input parameters.
 * Note:
 *      This function gets action of packets when no ACL configruation matches.
 */
extern rtksw_api_ret_t dal_rtl8367c_filter_igrAcl_state_get(rtksw_uint32 unit, rtksw_port_t port, rtksw_filter_state_t* state);

/* Function Name:
 *      dal_rtl8367c_filter_igrAcl_template_set
 * Description:
 *      Set template of ingress ACL.
 * Input:
 *      unit        - Unit ID
 *      template    - Ingress ACL template
 * Output:
 *      None
 * Return:
 *      RT_ERR_OK              - OK
 *      RT_ERR_FAILED          - Failed
 *      RT_ERR_SMI             - SMI access error
 *      RT_ERR_INPUT           - Invalid input parameters.
 * Note:
 *      This function set ACL template.
 */
extern rtksw_api_ret_t dal_rtl8367c_filter_igrAcl_template_set(rtksw_uint32 unit, rtksw_filter_template_t *aclTemplate);

/* Function Name:
 *      dal_rtl8367c_filter_igrAcl_template_get
 * Description:
 *      Get template of ingress ACL.
 * Input:
 *      unit        - Unit ID
 *      template    - Ingress ACL template
 * Output:
 *      None
 * Return:
 *      RT_ERR_OK              - OK
 *      RT_ERR_FAILED          - Failed
 *      RT_ERR_SMI             - SMI access error
 * Note:
 *      This function gets template of ACL.
 */
extern rtksw_api_ret_t dal_rtl8367c_filter_igrAcl_template_get(rtksw_uint32 unit, rtksw_filter_template_t *aclTemplate);

/* Function Name:
 *      dal_rtl8367c_filter_igrAcl_field_sel_set
 * Description:
 *      Set user defined field selectors in HSB
 * Input:
 *      unit        - Unit ID
 *      index       - index of field selector 0-15
 *      format      - Format of field selector
 *      offset      - Retrieving data offset
 * Output:
 *      None
 * Return:
 *      RT_ERR_OK              - OK
 *      RT_ERR_FAILED          - Failed
 *      RT_ERR_SMI             - SMI access error
 * Note:
 *      System support 16 user defined field selctors.
 *      Each selector can be enabled or disable.
 *      User can defined retrieving 16-bits in many predefiend
 *      standard l2/l3/l4 payload.
 */
extern rtksw_api_ret_t dal_rtl8367c_filter_igrAcl_field_sel_set(rtksw_uint32 unit, rtksw_uint32 index, rtksw_field_sel_t format, rtksw_uint32 offset);

/* Function Name:
 *      dal_rtl8367c_filter_igrAcl_field_sel_get
 * Description:
 *      Get user defined field selectors in HSB
 * Input:
 *      unit        - Unit ID
 *      index       - index of field selector 0-15
 * Output:
 *      pFormat     - Format of field selector
 *      pOffset     - Retrieving data offset
 * Return:
 *      RT_ERR_OK              - OK
 *      RT_ERR_FAILED          - Failed
 *      RT_ERR_SMI             - SMI access error
 * Note:
 *      None.
 */
extern rtksw_api_ret_t dal_rtl8367c_filter_igrAcl_field_sel_get(rtksw_uint32 unit, rtksw_uint32 index, rtksw_field_sel_t *pFormat, rtksw_uint32 *pOffset);

/* Function Name:
 *      dal_rtl8367c_filter_iprange_set
 * Description:
 *      Set IP Range check
 * Input:
 *      unit        - Unit ID
 *      index       - index of IP Range 0-15
 *      type        - IP Range check type, 0:Delete a entry, 1: IPv4_SIP, 2: IPv4_DIP, 3:IPv6_SIP, 4:IPv6_DIP
 *      upperIp     - The upper bound of IP range
 *      lowerIp     - The lower Bound of IP range
 * Output:
 *      None.
 * Return:
 *      RT_ERR_OK              - OK
 *      RT_ERR_FAILED          - Failed
 *      RT_ERR_SMI             - SMI access error
 *      RT_ERR_OUT_OF_RANGE    - The parameter is out of range
 *      RT_ERR_INPUT           - Input error
 * Note:
 *      upperIp must be larger or equal than lowerIp.
 */
extern rtksw_api_ret_t dal_rtl8367c_filter_iprange_set(rtksw_uint32 unit, rtksw_uint32 index, rtksw_filter_iprange_t type, ipaddr_t upperIp, ipaddr_t lowerIp);

/* Function Name:
 *      dal_rtl8367c_filter_iprange_get
 * Description:
 *      Set IP Range check
 * Input:
 *      unit         - Unit ID
 *      index        - index of IP Range 0-15
 * Output:
 *      pType        - IP Range check type, 0:Delete a entry, 1: IPv4_SIP, 2: IPv4_DIP, 3:IPv6_SIP, 4:IPv6_DIP
 *      pUpperIp     - The upper bound of IP range
 *      pLowerIp     - The lower Bound of IP range
 * Return:
 *      RT_ERR_OK              - OK
 *      RT_ERR_FAILED          - Failed
 *      RT_ERR_SMI             - SMI access error
 *      RT_ERR_OUT_OF_RANGE    - The parameter is out of range
 * Note:
 *      upperIp must be larger or equal than lowerIp.
 */
extern rtksw_api_ret_t dal_rtl8367c_filter_iprange_get(rtksw_uint32 unit, rtksw_uint32 index, rtksw_filter_iprange_t *pType, ipaddr_t *pUpperIp, ipaddr_t *pLowerIp);

/* Function Name:
 *      dal_rtl8367c_filter_vidrange_set
 * Description:
 *      Set VID Range check
 * Input:
 *      unit        - Unit ID
 *      index       - index of VID Range 0-15
 *      type        - IP Range check type, 0:Delete a entry, 1: CVID, 2: SVID
 *      upperVid    - The upper bound of VID range
 *      lowerVid    - The lower Bound of VID range
 * Output:
 *      None.
 * Return:
 *      RT_ERR_OK              - OK
 *      RT_ERR_FAILED          - Failed
 *      RT_ERR_SMI             - SMI access error
 *      RT_ERR_OUT_OF_RANGE    - The parameter is out of range
 *      RT_ERR_INPUT           - Input error
 * Note:
 *      upperVid must be larger or equal than lowerVid.
 */
extern rtksw_api_ret_t dal_rtl8367c_filter_vidrange_set(rtksw_uint32 unit, rtksw_uint32 index, rtksw_filter_vidrange_t type, rtksw_uint32 upperVid, rtksw_uint32 lowerVid);

/* Function Name:
 *      dal_rtl8367c_filter_vidrange_get
 * Description:
 *      Get VID Range check
 * Input:
 *      unit         - Unit ID
 *      index        - index of VID Range 0-15
 * Output:
 *      pType        - IP Range check type, 0:Unused, 1: CVID, 2: SVID
 *      pUpperVid    - The upper bound of VID range
 *      pLowerVid    - The lower Bound of VID range
 * Return:
 *      RT_ERR_OK              - OK
 *      RT_ERR_FAILED          - Failed
 *      RT_ERR_SMI             - SMI access error
 *      RT_ERR_OUT_OF_RANGE    - The parameter is out of range
 * Note:
 *      None.
 */
extern rtksw_api_ret_t dal_rtl8367c_filter_vidrange_get(rtksw_uint32 unit, rtksw_uint32 index, rtksw_filter_vidrange_t *pType, rtksw_uint32 *pUpperVid, rtksw_uint32 *pLowerVid);

/* Function Name:
 *      dal_rtl8367c_filter_portrange_set
 * Description:
 *      Set Port Range check
 * Input:
 *      unit        - Unit ID
 *      index       - index of Port Range 0-15
 *      type        - IP Range check type, 0:Delete a entry, 1: Source Port, 2: Destnation Port
 *      upperPort   - The upper bound of Port range
 *      lowerPort   - The lower Bound of Port range
 * Output:
 *      None.
 * Return:
 *      RT_ERR_OK              - OK
 *      RT_ERR_FAILED          - Failed
 *      RT_ERR_SMI             - SMI access error
 *      RT_ERR_OUT_OF_RANGE    - The parameter is out of range
 *      RT_ERR_INPUT           - Input error
 * Note:
 *      upperPort must be larger or equal than lowerPort.
 */
extern rtksw_api_ret_t dal_rtl8367c_filter_portrange_set(rtksw_uint32 unit, rtksw_uint32 index, rtksw_filter_portrange_t type, rtksw_uint32 upperPort, rtksw_uint32 lowerPort);

/* Function Name:
 *      dal_rtl8367c_filter_portrange_get
 * Description:
 *      Set Port Range check
 * Input:
 *      unit        - Unit ID
 *      index       - index of Port Range 0-15
 * Output:
 *      pType       - IP Range check type, 0:Delete a entry, 1: Source Port, 2: Destnation Port
 *      pUpperPort  - The upper bound of Port range
 *      pLowerPort  - The lower Bound of Port range
 * Return:
 *      RT_ERR_OK              - OK
 *      RT_ERR_FAILED          - Failed
 *      RT_ERR_SMI             - SMI access error
 *      RT_ERR_OUT_OF_RANGE    - The parameter is out of range
 *      RT_ERR_INPUT           - Input error
 * Note:
 *      None.
 */
extern rtksw_api_ret_t dal_rtl8367c_filter_portrange_get(rtksw_uint32 unit, rtksw_uint32 index, rtksw_filter_portrange_t *pType, rtksw_uint32 *pUpperPort, rtksw_uint32 *pLowerPort);

/* Function Name:
 *      dal_rtl8367c_filter_igrAclPolarity_set
 * Description:
 *      Set ACL Goip control palarity
 * Input:
 *      unit            - Unit ID
 *      polarity        - 1: High, 0: Low
 * Output:
 *      None
 * Return:
 *      RT_ERR_OK       - Success
 *      RT_ERR_SMI      - SMI access error
 * Note:
 *      none
 */
extern rtksw_api_ret_t dal_rtl8367c_filter_igrAclPolarity_set(rtksw_uint32 unit, rtksw_uint32 polarity);

/* Function Name:
 *      dal_rtl8367c_filter_igrAclPolarity_get
 * Description:
 *      Get ACL Goip control palarity
 * Input:
 *      unit            - Unit ID
 *      pPolarity       - 1: High, 0: Low
 * Output:
 *      None
 * Return:
 *      RT_ERR_OK       - Success
 *      RT_ERR_SMI      - SMI access error
 * Note:
 *      none
 */
extern rtksw_api_ret_t dal_rtl8367c_filter_igrAclPolarity_get(rtksw_uint32 unit, rtksw_uint32* pPolarity);


#endif /* __DAL_RTL8367C_ACL_H__ */
