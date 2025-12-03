/* Copyright (C) 2013 Realtek Semiconductor Corp.
 * All Rights Reserved.
 *
 * This program is the proprietary software of Realtek Semiconductor
 * Corporation and/or its licensors, and only be used, duplicated,
 * modified or distributed under the authorized license from Realtek.
 *
 * ANY USE OF THE SOFTWARE OTHER THAN AS AUTHORIZED UNDER
 * THIS LICENSE OR COPYRIGHT LAW IS PROHIBITED.
 *
 * $Revision: 63932 $
 * $Date: 2015-12-08 14:06:29 +0800 (周二, 08 十二月 2015) $
 *
 * Purpose : RTK switch high-level API for RTL8367/RTL8367C
 * Feature : Here is a list of all functions and variables in i2c module.
 *
 */

#include "../../rtk_switch.h"
#include "../../rtk_error.h"
#include "../../port.h"
#include "rtl8367c_reg.h"

#include "rtl8367c_asicdrv_i2c.h"
#include "../../chip.h"
#include "rtl8367c_asicdrv.h"
#include "../../rtk_types.h"
#include "dal_rtl8367c_i2c.h"

#include "../dal_mgmts.h"

static rtksw_I2C_16bit_mode_t rtksw_i2c_mode = I2C_LSB_16BIT_MODE;


/* Function Name:
 *      dal_rtl8367c_i2c_init
 * Description:
 *      I2C smart function initialization.
 * Input:
 *      unit        - Unit ID
 * Output:
 *      None
 * Return:
 *      RT_ERR_OK           - OK
 *      RT_ERR_FAILED       - Failed
 * Note:
 *      This API is used to initialize EEE status.
 *      need used GPIO pins
 *      OpenDrain and clock
 */
rtksw_api_ret_t dal_rtl8367c_i2c_init(rtksw_uint32 unit)
{
    rtksw_uint32 retVal;

    /* Check initialization state */
    RTKSW_CHK_INIT_STATE(unit);

    /* probe switch */
    if(rtksw_switch_chipType_get(unit) == CHIP_RTL8370B )
    {
        /*set GPIO8, GPIO9, OpenDrain as I2C, clock = 124KHZ   */
        if((retVal = rtl8367c_setAsicReg(unit, RTL8367C_REG_M_I2C_SYS_CTL, 0x5c3f)) != RT_ERR_OK)
            return retVal;
    }
    else
        return RT_ERR_FAILED;

  return  RT_ERR_OK;
}

/* Function Name:
 *      dal_rtl8367c_i2c_mode_set
 * Description:
 *      Set I2C data byte-order.
 * Input:
 *      unit        - Unit ID
 *      i2cmode     - byte-order mode
 * Output:
 *      None
 * Return:
 *      RT_ERR_OK           - OK
 *      RT_ERR_FAILED       - Failed
 *      RT_ERR_INPUT        - Invalid input parameter.
 * Note:
 *      This API can set I2c traffic's byte-order .
 */
rtksw_api_ret_t dal_rtl8367c_i2c_mode_set(rtksw_uint32 unit, rtksw_I2C_16bit_mode_t i2cmode )
{
    /* Check initialization state */
    RTKSW_CHK_INIT_STATE(unit);

    if(i2cmode >= I2C_Mode_END)
        return RT_ERR_INPUT;

    rtksw_i2c_mode = i2cmode;
    return RT_ERR_OK;
}

/* Function Name:
 *      dal_rtl8367c_i2c_mode_get
 * Description:
 *      Get i2c traffic byte-order setting.
 * Input:
 *      unit        - Unit ID
 * Output:
 *      pI2cMode - i2c byte-order
 * Return:
 *      RT_ERR_OK               - OK
 *      RT_ERR_FAILED           - Failed
 *      RT_ERR_NULL_POINTER     - input parameter is null pointer
 * Note:
 *      The API can get i2c traffic byte-order setting.
 */
rtksw_api_ret_t dal_rtl8367c_i2c_mode_get(rtksw_uint32 unit, rtksw_I2C_16bit_mode_t * pI2cMode)
{
    /* Check initialization state */
    RTKSW_CHK_INIT_STATE(unit);

    if(NULL == pI2cMode)
        return RT_ERR_NULL_POINTER;
    if(rtksw_i2c_mode == I2C_70B_LSB_16BIT_MODE)
        *pI2cMode = 1;
    else if ((rtksw_i2c_mode == I2C_LSB_16BIT_MODE))
        *pI2cMode = 0;
    else
        return RT_ERR_FAILED;
    return RT_ERR_OK;
}

/* Function Name:
 *      dal_rtl8367c_i2c_gpioPinGroup_set
 * Description:
 *      Set i2c SDA & SCL used GPIO pins group.
 * Input:
 *      unit        - Unit ID
 *      pins_group  - GPIO pins group
 * Output:
 *      None
 * Return:
 *      RT_ERR_OK               - OK
 *      RT_ERR_FAILED           - Failed
 *      RT_ERR_INPUT        - Invalid input parameter.
 * Note:
 *      The API can set i2c used gpio pins group.
 *      There are three group pins could be used
 */
rtksw_api_ret_t dal_rtl8367c_i2c_gpioPinGroup_set(rtksw_uint32 unit, rtksw_I2C_gpio_pin_t pins_group )
{
    rtksw_uint32 retVal;

    /* Check initialization state */
    RTKSW_CHK_INIT_STATE(unit);

    if( ( pins_group > I2C_GPIO_PIN_END )|| ( pins_group < I2C_GPIO_PIN_8_9) )
        return RT_ERR_INPUT;

    if( (retVal = rtl8367c_setAsicI2CGpioPinGroup(unit, pins_group) ) != RT_ERR_OK )
        return retVal ;

    return RT_ERR_OK;
}

/* Function Name:
 *      dal_rtl8367c_i2c_gpioPinGroup_get
 * Description:
 *      Get i2c SDA & SCL used GPIO pins group.
 * Input:
 *      unit        - Unit ID
 * Output:
 *      pPins_group - GPIO pins group
 * Return:
 *      RT_ERR_OK               - OK
 *      RT_ERR_NULL_POINTER     - input parameter is null pointer
 * Note:
 *      The API can get i2c used gpio pins group.
 *      There are three group pins could be used
 */
rtksw_api_ret_t dal_rtl8367c_i2c_gpioPinGroup_get(rtksw_uint32 unit, rtksw_I2C_gpio_pin_t * pPins_group )
{
    rtksw_uint32 retVal;

    /* Check initialization state */
    RTKSW_CHK_INIT_STATE(unit);

    if(NULL == pPins_group)
        return RT_ERR_NULL_POINTER;
    if( (retVal = rtl8367c_getAsicI2CGpioPinGroup(unit, pPins_group) ) != RT_ERR_OK )
        return retVal;

    return RT_ERR_OK;
}

/* Function Name:
 *      dal_rtl8367c_i2c_data_read
 * Description:
 *      read i2c slave device register.
 * Input:
 *      unit         - Unit ID
 *      deviceAddr   -   access Slave device address
 *      slaveRegAddr -   access Slave register address
 * Output:
 *      pRegData     -   read data
 * Return:
 *      RT_ERR_OK               - OK
 *      RT_ERR_NULL_POINTER     - input parameter is null pointer
 * Note:
 *      The API can access i2c slave and read i2c slave device register.
 */
rtksw_api_ret_t dal_rtl8367c_i2c_data_read(rtksw_uint32 unit, rtksw_uint8 deviceAddr, rtksw_uint32 slaveRegAddr, rtksw_uint32 *pRegData)
{
     rtksw_uint32 retVal, counter=0;
     rtksw_uint8 controlByte_W, controlByte_R;
     rtksw_uint8 slaveRegAddr_L, slaveRegAddr_H = 0x0, temp;
     rtksw_uint8 regData_L, regData_H;

     /* Check initialization state */
    RTKSW_CHK_INIT_STATE(unit);

   /* control byte :deviceAddress + W,  deviceAddress + R   */
    controlByte_W = (rtksw_uint8)(deviceAddr << 1) ;
    controlByte_R = (rtksw_uint8)(controlByte_W | 0x1);

    slaveRegAddr_L = (rtksw_uint8) (slaveRegAddr & 0x00FF) ;
    slaveRegAddr_H = (rtksw_uint8) (slaveRegAddr >>8) ;

    if( rtksw_i2c_mode == I2C_70B_LSB_16BIT_MODE)
    {
        temp = slaveRegAddr_L ;
        slaveRegAddr_L = slaveRegAddr_H;
        slaveRegAddr_H = temp;
    }


  /*check bus state: idle*/
  for(counter = 3000; counter>0; counter--)
  {
    if ( (retVal = rtl8367c_setAsicI2C_checkBusIdle(unit) ) == RT_ERR_OK)
         break;
  }
  if( counter ==0 )
      return retVal; /*i2c is busy*/

   /*tx Start cmd*/
   if( (retVal = rtl8367c_setAsicI2CStartCmd(unit) ) != RT_ERR_OK )
       return retVal ;


  /*tx control _W*/
   if( (retVal = rtl8367c_setAsicI2CTxOneCharCmd(unit, controlByte_W))!= RT_ERR_OK )
      return retVal ;


  /*check if RX ack from slave*/
   if( (retVal = rtl8367c_setAsicI2CcheckRxAck(unit)) != RT_ERR_OK )
        return retVal;

    /* tx slave buffer address low 8 bits */
   if( (retVal = rtl8367c_setAsicI2CTxOneCharCmd(unit, slaveRegAddr_L))!= RT_ERR_OK )
         return retVal  ;

   /*check if RX ack from slave*/
   if( (retVal = rtl8367c_setAsicI2CcheckRxAck(unit)) != RT_ERR_OK )
        return retVal;



        /* tx slave buffer address high 8 bits */
   if( (retVal = rtl8367c_setAsicI2CTxOneCharCmd(unit, slaveRegAddr_H))!= RT_ERR_OK )
         return retVal  ;


   /*check if RX ack from slave*/
   if( (retVal = rtl8367c_setAsicI2CcheckRxAck(unit)) != RT_ERR_OK )
        return retVal;


   /*tx Start cmd*/
   if( (retVal = rtl8367c_setAsicI2CStartCmd(unit) ) != RT_ERR_OK )
       return retVal ;

      /*tx control _R*/
   if( (retVal = rtl8367c_setAsicI2CTxOneCharCmd(unit, controlByte_R))!= RT_ERR_OK )
       return retVal ;


  /*check if RX ack from slave*/
   if( (retVal = rtl8367c_setAsicI2CcheckRxAck(unit)) != RT_ERR_OK )
        return retVal;


    /* rx low 8bit data*/
   if( ( retVal = rtl8367c_setAsicI2CRxOneCharCmd(unit, &regData_L) ) != RT_ERR_OK )
        return retVal;



    /* tx ack to slave, keep receive */
    if( (retVal = rtl8367c_setAsicI2CTxAckCmd(unit)) != RT_ERR_OK )
        return retVal;

     /* rx high 8bit data*/
    if( ( retVal = rtl8367c_setAsicI2CRxOneCharCmd(unit, &regData_H) ) != RT_ERR_OK )
        return retVal;



    /* tx Noack to slave, Stop receive */
     if( (retVal = rtl8367c_setAsicI2CTxNoAckCmd(unit)) != RT_ERR_OK )
        return retVal;


    /*tx Stop cmd */
    if( (retVal = rtl8367c_setAsicI2CStopCmd(unit)) != RT_ERR_OK )
        return retVal;

    *pRegData = (regData_H << 8) | regData_L;

    return RT_ERR_OK;
}

/* Function Name:
 *      dal_rtl8367c_i2c_data_write
 * Description:
 *      write data to i2c slave device register
 * Input:
 *      unit         - Unit ID
 *      deviceAddr   -   access Slave device address
 *      slaveRegAddr -   access Slave register address
 *      regData      -   data to set
 * Output:
 *      None
 * Return:
 *      RT_ERR_OK               - OK
 * Note:
 *      The API can access i2c slave and setting i2c slave device register.
 */
rtksw_api_ret_t dal_rtl8367c_i2c_data_write(rtksw_uint32 unit, rtksw_uint8 deviceAddr, rtksw_uint32 slaveRegAddr, rtksw_uint32 regData)
{
     rtksw_uint32 retVal,counter;
     rtksw_uint8 controlByte_W;
     rtksw_uint8 slaveRegAddr_L, slaveRegAddr_H = 0x0, temp;
     rtksw_uint8 regData_L, regData_H;

     /* Check initialization state */
    RTKSW_CHK_INIT_STATE(unit);

  /* control byte :deviceAddress + W    */
    controlByte_W = (rtksw_uint8)(deviceAddr<< 1) ;

    slaveRegAddr_L = (rtksw_uint8) (slaveRegAddr & 0x00FF) ;
    slaveRegAddr_H = (rtksw_uint8) (slaveRegAddr >>8) ;

    regData_H   = (rtksw_uint8) (regData>> 8);
    regData_L   = (rtksw_uint8) (regData & 0x00FF);

    if( rtksw_i2c_mode == I2C_70B_LSB_16BIT_MODE)
    {
        temp = slaveRegAddr_L ;
        slaveRegAddr_L = slaveRegAddr_H;
        slaveRegAddr_H = temp;
    }


  /*check bus state: idle*/
  for(counter = 3000; counter>0; counter--)
  {
    if ( (retVal = rtl8367c_setAsicI2C_checkBusIdle(unit) ) == RT_ERR_OK)
        break;
  }

  if( counter ==0 )
      return retVal; /*i2c is busy*/


   /*tx Start cmd*/
   if( (retVal = rtl8367c_setAsicI2CStartCmd(unit) ) != RT_ERR_OK )
       return retVal ;


  /*tx control _W*/
   if( (retVal = rtl8367c_setAsicI2CTxOneCharCmd(unit, controlByte_W))!= RT_ERR_OK )
      return retVal ;


  /*check if RX ack from slave*/
   if( (retVal = rtl8367c_setAsicI2CcheckRxAck(unit)) != RT_ERR_OK )
        return retVal;


    /* tx slave buffer address low 8 bits */
   if( (retVal = rtl8367c_setAsicI2CTxOneCharCmd(unit, slaveRegAddr_L))!= RT_ERR_OK )
        return retVal;


   /*check if RX ack from slave*/
   if( (retVal = rtl8367c_setAsicI2CcheckRxAck(unit)) != RT_ERR_OK )
        return retVal;


   /* tx slave buffer address high 8 bits */
   if( (retVal = rtl8367c_setAsicI2CTxOneCharCmd(unit, slaveRegAddr_H))!= RT_ERR_OK )
        return retVal;


   /*check if RX ack from slave*/
   if( (retVal = rtl8367c_setAsicI2CcheckRxAck(unit)) != RT_ERR_OK )
        return retVal;


     /*tx Datavlue LSB*/
   if( (retVal = rtl8367c_setAsicI2CTxOneCharCmd(unit, regData_L))!= RT_ERR_OK )
        return retVal;


   /*check if RX ack from slave*/
   if( (retVal = rtl8367c_setAsicI2CcheckRxAck(unit)) != RT_ERR_OK )
        return retVal;


   /*tx Datavlue MSB*/
   if( (retVal = rtl8367c_setAsicI2CTxOneCharCmd(unit, regData_H))!= RT_ERR_OK )
        return retVal;


   /*check if RX ack from slave*/
   if( (retVal = rtl8367c_setAsicI2CcheckRxAck(unit)) != RT_ERR_OK )
        return retVal;


    /*tx Stop cmd */
    if( (retVal = rtl8367c_setAsicI2CStopCmd(unit)) != RT_ERR_OK )
        return retVal;

    return RT_ERR_OK;
}

