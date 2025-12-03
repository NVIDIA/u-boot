/*
 * Copyright (C) 2019 Realtek Semiconductor Corp.
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
 * Feature : Here is a list of all functions and variables in GPIO module.
 *
 */

#include "../../rtk_switch.h"
#include "../../rtk_error.h"
#include "rtl8367d_asicdrv.h"
#include "dal_rtl8367d_gpio.h"

#include "../dal_mgmts.h"

/* Function Name:
 *      dal_rtl8367d_gpio_input_get
 * Description:
 *      Get gpio input
 * Input:
 *      unit        - Unit ID
 *      pin 		- GPIO pin
 * Output:
 *      pInput 		- GPIO input
 * Return:
 *      RT_ERR_OK 				- Success
 *      RT_ERR_SMI  			- SMI access error
 *      RT_ERR_OUT_OF_RANGE 	- input out of range.
 *      RT_ERR_NULL_POINTER 	- input parameter is null pointer.
 * Note:
 *      None
 */
rtksw_api_ret_t dal_rtl8367d_gpio_input_get(rtksw_uint32 unit, rtksw_uint32 pin, rtksw_uint32 *pInput)
{
    rtksw_api_ret_t retVal;

    /* Check initialization state */
    RTKSW_CHK_INIT_STATE(unit);

	if(pin >= RTL8367D_GPIOPINNO)
		return RT_ERR_OUT_OF_RANGE;

    if(NULL == pInput)
        return RT_ERR_NULL_POINTER;
    
    if ((retVal = rtl8367d_getAsicRegBit(unit, RTL8367D_REG_GPIO_67C_I_X0 + (pin / 16), (pin % 16), pInput)) != RT_ERR_OK)
        return retVal;

    return RT_ERR_OK;
}

/* Function Name:
 *      dal_rtl8367d_gpio_output_set
 * Description:
 *      Set GPIO output value.
 * Input:
 *      unit    - Unit ID
 *      pin     - GPIO pin
 *      output  - 1 or 0
 * Output:
 *      None
 * Return:
 *      RT_ERR_OK            - OK
 *      RT_ERR_FAILED        - Failed
 *      RT_ERR_SMI           - SMI access error
 *      RT_ERR_INPUT         - Invalid input parameter.
 *      RT_ERR_OUT_OF_RANGE  - input parameter out of range.
 * Note:
 *      The API can set GPIO pin output 1 or 0.
 */
rtksw_api_ret_t dal_rtl8367d_gpio_output_set(rtksw_uint32 unit, rtksw_uint32 pin, rtksw_uint32 output)
{
    rtksw_api_ret_t retVal;

    /* Check initialization state */
    RTKSW_CHK_INIT_STATE(unit);

	if(pin >= RTL8367D_GPIOPINNO)
		return RT_ERR_OUT_OF_RANGE;

    if (output > 1)
        return RT_ERR_INPUT;

    if ((retVal = rtl8367d_setAsicRegBit(unit, RTL8367D_REG_GPIO_67C_O_X0 + (pin / 16), (pin % 16), output)) != RT_ERR_OK)
        return retVal;

    return RT_ERR_OK;
}

/* Function Name:
 *      dal_rtl8367d_gpio_output_get
 * Description:
 *      Get GPIO output.
 * Input:
 *      unit        - Unit ID
 *      pin         - GPIO pin
 * Output:
 *      pOutput  - GPIO output
 * Return:
 *      RT_ERR_OK               - OK
 *      RT_ERR_FAILED           - Failed
 *      RT_ERR_SMI              - SMI access error
 *      RT_ERR_INPUT            - Invalid input parameters.
 *      RT_ERR_OUT_OF_RANGE     - input parameter out of range.
 *      RT_ERR_NULL_POINTER 	- input parameter is null pointer.
 * Note:
 *      The API can get GPIO output.
 */
rtksw_api_ret_t dal_rtl8367d_gpio_output_get(rtksw_uint32 unit, rtksw_uint32 pin, rtksw_uint32 *pOutput)
{
    rtksw_api_ret_t retVal;

    /* Check initialization state */
    RTKSW_CHK_INIT_STATE(unit);

	if(pin >= RTL8367D_GPIOPINNO)
		return RT_ERR_OUT_OF_RANGE;

    if(NULL == pOutput)
        return RT_ERR_NULL_POINTER;

    if ((retVal = rtl8367d_getAsicRegBit(unit, RTL8367D_REG_GPIO_67C_O_X0 + (pin / 16), (pin % 16), pOutput)) != RT_ERR_OK)
        return retVal;

    return RT_ERR_OK;
}

/* Function Name:
 *      dal_rtl8367d_gpio_state_set
 * Description:
 *      Set GPIO control.
 * Input:
 *      unit    - Unit ID
 *      pin     - GPIO pin
 *      state   - GPIO enable
 * Output:
 *      None
 * Return:
 *      RT_ERR_OK            - OK
 *      RT_ERR_FAILED        - Failed
 *      RT_ERR_SMI           - SMI access error
 *      RT_ERR_INPUT         - Invalid input parameter.
 *      RT_ERR_OUT_OF_RANGE  - input parameter out of range.
 *      RT_ERR_ENABLE        - invalid enable parameter .
 * Note:
 *      The API can set GPIO pin output 1 or 0.
 */
rtksw_api_ret_t dal_rtl8367d_gpio_state_set(rtksw_uint32 unit, rtksw_uint32 pin, rtksw_enable_t state)
{
    rtksw_api_ret_t retVal;
    rtksw_uint32 gpioState;

    /* Check initialization state */
    RTKSW_CHK_INIT_STATE(unit);

    if(pin >= RTL8367D_GPIOPINNO)
        return RT_ERR_OUT_OF_RANGE;

    switch (state)
    {
        case RTKSW_DISABLED:
            gpioState = 0;
            break;
        case RTKSW_ENABLED:
            gpioState = 1;
            break;
        default:
            return RT_ERR_ENABLE;
    }
    
    if ((retVal = rtl8367d_setAsicRegBit(unit, RTL8367D_REG_GPIO_MODE_67C_X0 + (pin / 16), (pin % 16), gpioState)) != RT_ERR_OK)
        return retVal;

    return RT_ERR_OK;
}

/* Function Name:
 *      dal_rtl8367d_gpio_state_get
 * Description:
 *      Get GPIO enable state.
 * Input:
 *      unit        - Unit ID
 *      pin         - GPIO pin
 * Output:
 *      pState   - GPIO enable
 * Return:
 *      RT_ERR_OK               - OK
 *      RT_ERR_FAILED           - Failed
 *      RT_ERR_SMI              - SMI access error
 *      RT_ERR_INPUT            - Invalid input parameters.
 *      RT_ERR_OUT_OF_RANGE     - input parameter out of range.
 *      RT_ERR_NULL_POINTER 	- input parameter is null pointer.
 * Note:
 *      The API can get GPIO enable state.
 */
rtksw_api_ret_t dal_rtl8367d_gpio_state_get(rtksw_uint32 unit, rtksw_uint32 pin, rtksw_enable_t *pState)
{
    rtksw_api_ret_t retVal;
    rtksw_uint32 gpioState;

    /* Check initialization state */
    RTKSW_CHK_INIT_STATE(unit);

	if(pin >= RTL8367D_GPIOPINNO)
		return RT_ERR_OUT_OF_RANGE;

    if(NULL == pState)
        return RT_ERR_NULL_POINTER;

    if ((retVal = rtl8367d_getAsicRegBit(unit, RTL8367D_REG_GPIO_MODE_67C_X0 + (pin / 16), (pin % 16), &gpioState)) != RT_ERR_OK)
        return retVal;

    switch (gpioState)
    {
        case 0:
            *pState = RTKSW_DISABLED;
            break;
        case 1:
            *pState = RTKSW_ENABLED;
            break;
        default:
            return RT_ERR_FAILED;
    }

    return RT_ERR_OK;
}

/* Function Name:
 *      dal_rtl8367d_gpio_mode_set
 * Description:
 *      Set GPIO mode.
 * Input:
 *      unit    - Unit ID
 *      pin     - GPIO pin
 *      mode    - 1 or 0
 * Output:
 *      None
 * Return:
 *      RT_ERR_OK            - OK
 *      RT_ERR_FAILED        - Failed
 *      RT_ERR_SMI           - SMI access error
 *      RT_ERR_INPUT         - Invalid input parameter.
 *      RT_ERR_OUT_OF_RANGE  - input parameter out of range.
 * Note:
 *      The API can set GPIO  to input or output mode.
 */
rtksw_api_ret_t dal_rtl8367d_gpio_mode_set(rtksw_uint32 unit, rtksw_uint32 pin, rtksw_gpio_mode_t mode)
{
    rtksw_api_ret_t retVal;
    rtksw_uint32 gpioMode;

    /* Check initialization state */
    RTKSW_CHK_INIT_STATE(unit);

	if(pin >= RTL8367D_GPIOPINNO)
		return RT_ERR_OUT_OF_RANGE;

    switch (mode)
    {
        case GPIO_MODE_OUTPUT:
            gpioMode = 1;
            break;
        case GPIO_MODE_INPUT:
            gpioMode = 0;
            break;
        default:
            return RT_ERR_INPUT;
    }
    
    if ((retVal = rtl8367d_setAsicRegBit(unit, RTL8367D_REG_GPIO_67C_OE_X0 + (pin / 16), (pin % 16), gpioMode)) != RT_ERR_OK)
        return retVal;

    return RT_ERR_OK;
}

/* Function Name:
 *      dal_rtl8367d_gpio_mode_get
 * Description:
 *      Get GPIO mode.
 * Input:
 *      unit        - Unit ID
 *      pin         - GPIO pin
 * Output:
 *      pMode    - GPIO mode
 * Return:
 *      RT_ERR_OK               - OK
 *      RT_ERR_FAILED           - Failed
 *      RT_ERR_SMI              - SMI access error
 *      RT_ERR_INPUT            - Invalid input parameters.
 *      RT_ERR_OUT_OF_RANGE     - input parameter out of range.
 *      RT_ERR_NULL_POINTER 	- input parameter is null pointer.
 * Note:
 *      The API can get GPIO mode.
 */
rtksw_api_ret_t dal_rtl8367d_gpio_mode_get(rtksw_uint32 unit, rtksw_uint32 pin, rtksw_gpio_mode_t *pMode)
{
    rtksw_api_ret_t retVal;
    rtksw_uint32 gpioMode;

    /* Check initialization state */
    RTKSW_CHK_INIT_STATE(unit);

	if(pin >= RTL8367D_GPIOPINNO)
		return RT_ERR_OUT_OF_RANGE;

    if(NULL == pMode)
        return RT_ERR_NULL_POINTER;
    
    if ((retVal = rtl8367d_getAsicRegBit(unit, RTL8367D_REG_GPIO_67C_OE_X0 + (pin / 16), (pin % 16), &gpioMode)) != RT_ERR_OK)
        return retVal;

    switch (gpioMode)
    {
        case 0:
            *pMode = GPIO_MODE_INPUT;
            break;
        case 1:
            *pMode = GPIO_MODE_OUTPUT;
            break;
        default:
            return RT_ERR_FAILED;
    }

    return RT_ERR_OK;
}

/* Function Name:
 *      dal_rtl8367d_gpio_aclEnClear_set
 * Description:
 *      Set GPIO acl clear.
 * Input:
 *      unit    - Unit ID
 *      pin     - GPIO pin
 * Output:
 *      None
 * Return:
 *      RT_ERR_OK            - OK
 *      RT_ERR_FAILED        - Failed
 *      RT_ERR_SMI           - SMI access error
 *      RT_ERR_INPUT         - Invalid input parameter.
 *      RT_ERR_OUT_OF_RANGE  - input parameter out of range.
 * Note:
 *      The API can set GPIO ACL clear.
 */
rtksw_api_ret_t dal_rtl8367d_gpio_aclEnClear_set(rtksw_uint32 unit, rtksw_uint32 pin)
{
    rtksw_api_ret_t retVal;

    /* Check initialization state */
    RTKSW_CHK_INIT_STATE(unit);

    if(pin >= RTL8367D_GPIOPINNO)
        return RT_ERR_OUT_OF_RANGE;
    
    /* ACL clear */
    if((retVal = rtl8367d_setAsicRegBit(unit, RTL8367D_REG_ACL_GPIO0 + (pin / 16),  (pin % 16), 1)) != RT_ERR_OK)
        return retVal;

    return RT_ERR_OK;
}

/* Function Name:
 *      dal_rtl8367d_gpio_aclEnClear_get
 * Description:
 *      Get GPIO acl clear.
 * Input:
 *      unit        - Unit ID
 *      pin         - GPIO pin
 * Output:
 *      pAclEn   - GPIO acl enable
 * Return:
 *      RT_ERR_OK               - OK
 *      RT_ERR_FAILED           - Failed
 *      RT_ERR_SMI              - SMI access error
 *      RT_ERR_INPUT            - Invalid input parameters.
 *      RT_ERR_OUT_OF_RANGE     - input parameter out of range.
 *      RT_ERR_NULL_POINTER 	- input parameter is null pointer.
 * Note:
 *      The API can get GPIO acl enable clear.
 */
rtksw_api_ret_t dal_rtl8367d_gpio_aclEnClear_get(rtksw_uint32 unit, rtksw_uint32 pin, rtksw_enable_t *pAclEn)
{
    rtksw_api_ret_t retVal;

    /* Check initialization state */
    RTKSW_CHK_INIT_STATE(unit);

	if(pin >= RTL8367D_GPIOPINNO)
		return RT_ERR_OUT_OF_RANGE;

    if(NULL == pAclEn)
        return RT_ERR_NULL_POINTER;
    
    if ((retVal = rtl8367d_getAsicRegBit(unit, RTL8367D_REG_ACL_GPIO0 + (pin / 16), (pin % 16), (rtksw_uint32 *)pAclEn)) != RT_ERR_OK)
        return retVal;

    return RT_ERR_OK;
}

