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
 * Purpose : RTL8367D switch high-level API for RTL8367D
 * Feature :
 *
 */

#include "rtl8367d_asicdrv.h"

#if defined(RTK_X86_ASICDRV)
#include "../I2Clib.h"
#else
#include "../dal_mgmts.h"
#include "../smi.h"
#endif

/*for driver verify testing only*/
#ifdef CONFIG_VIRTUAL_REG_ASICDRV_TEST
#define CLE_VIRTUAL_REG_SIZE        0x10000
rtksw_uint16 CleVirtualReg[CLE_VIRTUAL_REG_SIZE];
#endif

#if defined(CONFIG_RTL865X_CLE) || defined (RTK_X86_CLE)
extern rtksw_uint32 cleDebuggingDisplay;
#endif

/* Function Name:
 *      rtl8367d_setAsicRegBit
 * Description:
 *      Set a bit value of a specified register
 * Input:
 *      unit    - Unit ID
 *      reg     - register's address
 *      bit     - bit location
 *      value   - value to set. It can be value 0 or 1.
 * Output:
 *      None
 * Return:
 *      RT_ERR_OK       - Success
 *      RT_ERR_SMI      - SMI access error
 *      RT_ERR_INPUT    - Invalid input parameter
 * Note:
 *      Set a bit of a specified register to 1 or 0.
 */
ret_t rtl8367d_setAsicRegBit(rtksw_uint32 unit, rtksw_uint32 reg, rtksw_uint32 bit, rtksw_uint32 value)
{

#if defined(RTK_X86_ASICDRV)
    rtksw_uint32 regData;
    ret_t retVal;

    if(bit >= RTL8367D_REGBITLENGTH)
        return RT_ERR_INPUT;

    /* Skip warning */
    if (unit) {}

    retVal = Access_Read(reg, 2, &regData);
    if(TRUE != retVal)
        return RT_ERR_SMI;

    if(0x8367B == cleDebuggingDisplay)
        PRINT("R[0x%4.4x]=0x%4.4x\n", reg, regData);

    if(value)
        regData = regData | (1 << bit);
    else
        regData = regData & (~(1 << bit));

    retVal = Access_Write(reg,2, regData);
    if(TRUE != retVal)
        return RT_ERR_SMI;

    if(0x8367B == cleDebuggingDisplay)
        PRINT("W[0x%4.4x]=0x%4.4x\n", reg, regData);


#elif defined(CONFIG_VIRTUAL_REG_ASICDRV_TEST)

    if(bit >= RTL8367D_REGBITLENGTH)
        return RT_ERR_INPUT;

    else if(reg >= CLE_VIRTUAL_REG_SIZE)
        return RT_ERR_OUT_OF_RANGE;

    if(value)
    {
        CleVirtualReg[reg] =  CleVirtualReg[reg] | (1 << bit);
    }
    else
    {
        CleVirtualReg[reg] =  CleVirtualReg[reg] & (~(1 << bit));
    }

    if(0x8367B == cleDebuggingDisplay)
        PRINT("W[0x%4.4x]=0x%4.4x\n", reg, CleVirtualReg[reg]);

#else
    rtksw_uint32 regData;
    ret_t retVal;

    if(bit >= RTL8367D_REGBITLENGTH)
        return RT_ERR_INPUT;

    retVal = reg_smi_read(unit, reg, &regData);
    if(retVal != RT_ERR_OK)
        return RT_ERR_SMI;

  #ifdef CONFIG_RTL865X_CLE
    if(0x8367B == cleDebuggingDisplay)
        PRINT("R[0x%4.4x]=0x%4.4x\n", reg, regData);
  #endif
    if(value)
        regData = regData | (1 << bit);
    else
        regData = regData & (~(1 << bit));

    retVal = reg_smi_write(unit, reg, regData);
    if(retVal != RT_ERR_OK)
        return RT_ERR_SMI;

  #ifdef CONFIG_RTL865X_CLE
    if(0x8367B == cleDebuggingDisplay)
        PRINT("W[0x%4.4x]=0x%4.4x\n", reg, regData);
  #endif

#endif
    return RT_ERR_OK;
}
/* Function Name:
 *      rtl8367d_getAsicRegBit
 * Description:
 *      Get a bit value of a specified register
 * Input:
 *      unit    - Unit ID
 *      reg     - register's address
 *      bit     - bit location
 *      value   - value to get.
 * Output:
 *      None
 * Return:
 *      RT_ERR_OK       - Success
 *      RT_ERR_SMI      - SMI access error
 *      RT_ERR_INPUT    - Invalid input parameter
 * Note:
 *      None
 */
ret_t rtl8367d_getAsicRegBit(rtksw_uint32 unit, rtksw_uint32 reg, rtksw_uint32 bit, rtksw_uint32 *pValue)
{

#if defined(RTK_X86_ASICDRV)

    rtksw_uint32 regData;
    ret_t retVal;

    if(bit >= RTL8367D_REGBITLENGTH)
        return RT_ERR_INPUT;

    /* Skip warning */
    if (unit) {}

    retVal = Access_Read(reg, 2, &regData);
    if(TRUE != retVal)
        return RT_ERR_SMI;

    *pValue = (regData & (0x1 << bit)) >> bit;

    if(0x8367B == cleDebuggingDisplay)
        PRINT("R[0x%4.4x]=0x%4.4x\n", reg, regData);

#elif defined(CONFIG_VIRTUAL_REG_ASICDRV_TEST)

    if(bit >= RTL8367D_REGBITLENGTH)
        return RT_ERR_INPUT;

    if(reg >= CLE_VIRTUAL_REG_SIZE)
        return RT_ERR_OUT_OF_RANGE;

    *pValue = (CleVirtualReg[reg] & (0x1 << bit)) >> bit;

    if(0x8367B == cleDebuggingDisplay)
        PRINT("R[0x%4.4x]=0x%4.4x\n", reg, CleVirtualReg[reg]);

#else
    rtksw_uint32 regData;
    ret_t retVal;

    retVal = reg_smi_read(unit, reg, &regData);
    if(retVal != RT_ERR_OK)
        return RT_ERR_SMI;

  #ifdef CONFIG_RTL865X_CLE
    if(0x8367B == cleDebuggingDisplay)
        PRINT("R[0x%4.4x]=0x%4.4x\n", reg, regData);
  #endif

    *pValue = (regData & (0x1 << bit)) >> bit;

#endif
    return RT_ERR_OK;
}
/* Function Name:
 *      rtl8367d_setAsicRegBits
 * Description:
 *      Set bits value of a specified register
 * Input:
 *      unit    - Unit ID
 *      reg     - register's address
 *      bits    - bits mask for setting
 *      value   - bits value for setting
 * Output:
 *      None
 * Return:
 *      RT_ERR_OK       - Success
 *      RT_ERR_SMI      - SMI access error
 *      RT_ERR_INPUT    - Invalid input parameter
 * Note:
 *      Set bits of a specified register to value. Both bits and value are be treated as bit-mask
 */
ret_t rtl8367d_setAsicRegBits(rtksw_uint32 unit, rtksw_uint32 reg, rtksw_uint32 bits, rtksw_uint32 value)
{

#if defined(RTK_X86_ASICDRV)

    rtksw_uint32 regData;
    ret_t retVal;
    rtksw_uint32 bitsShift;
    rtksw_uint32 valueShifted;

    if(bits >= (1 << RTL8367D_REGBITLENGTH) )
        return RT_ERR_INPUT;
    
    /* Skip warning */
    if (unit) {}

    bitsShift = 0;
    while(!(bits & (1 << bitsShift)))
    {
        bitsShift++;
        if(bitsShift >= RTL8367D_REGBITLENGTH)
            return RT_ERR_INPUT;
    }

    valueShifted = value << bitsShift;
    if(valueShifted > RTL8367D_REGDATAMAX)
        return RT_ERR_INPUT;

    retVal = Access_Read(reg, 2, &regData);
    if(TRUE != retVal)
        return RT_ERR_SMI;

    if(0x8367B == cleDebuggingDisplay)
        PRINT("R[0x%4.4x]=0x%4.4x\n", reg, regData);

    regData = regData & (~bits);
    regData = regData | (valueShifted & bits);

    retVal = Access_Write(reg,2, regData);
    if(TRUE != retVal)
        return RT_ERR_SMI;

    if(0x8367B == cleDebuggingDisplay)
        PRINT("W[0x%4.4x]=0x%4.4x\n", reg, regData);

#elif defined(CONFIG_VIRTUAL_REG_ASICDRV_TEST)
    rtksw_uint32 regData;
    rtksw_uint32 bitsShift;
    rtksw_uint32 valueShifted;

    if(bits >= (1 << RTL8367D_REGBITLENGTH) )
        return RT_ERR_INPUT;

    bitsShift = 0;
    while(!(bits & (1 << bitsShift)))
    {
        bitsShift++;
        if(bitsShift >= RTL8367D_REGBITLENGTH)
            return RT_ERR_INPUT;
    }
    valueShifted = value << bitsShift;

    if(valueShifted > RTL8367D_REGDATAMAX)
        return RT_ERR_INPUT;

    if(reg >= CLE_VIRTUAL_REG_SIZE)
        return RT_ERR_OUT_OF_RANGE;

    regData = CleVirtualReg[reg] & (~bits);
    regData = regData | (valueShifted & bits);

    CleVirtualReg[reg] = regData;

    if(0x8367B == cleDebuggingDisplay)
        PRINT("W[0x%4.4x]=0x%4.4x\n", reg, regData);

#else
    rtksw_uint32 regData;
    ret_t retVal;
    rtksw_uint32 bitsShift;
    rtksw_uint32 valueShifted;

    if(bits >= (1 << RTL8367D_REGBITLENGTH) )
        return RT_ERR_INPUT;

    bitsShift = 0;
    while(!(bits & (1 << bitsShift)))
    {
        bitsShift++;
        if(bitsShift >= RTL8367D_REGBITLENGTH)
            return RT_ERR_INPUT;
    }
    valueShifted = value << bitsShift;

    if(valueShifted > RTL8367D_REGDATAMAX)
        return RT_ERR_INPUT;

    retVal = reg_smi_read(unit, reg, &regData);
    if(retVal != RT_ERR_OK)
        return RT_ERR_SMI;
  #ifdef CONFIG_RTL865X_CLE
    if(0x8367B == cleDebuggingDisplay)
        PRINT("R[0x%4.4x]=0x%4.4x\n", reg, regData);
  #endif

    regData = regData & (~bits);
    regData = regData | (valueShifted & bits);

    retVal = reg_smi_write(unit, reg, regData);
    if(retVal != RT_ERR_OK)
        return RT_ERR_SMI;
  #ifdef CONFIG_RTL865X_CLE
    if(0x8367B == cleDebuggingDisplay)
        PRINT("W[0x%4.4x]=0x%4.4x\n", reg, regData);
  #endif
#endif
    return RT_ERR_OK;
}
/* Function Name:
 *      rtl8367d_getAsicRegBits
 * Description:
 *      Get bits value of a specified register
 * Input:
 *      unit    - Unit ID
 *      reg     - register's address
 *      bits    - bits mask for setting
 *      value   - bits value for setting
 * Output:
 *      None
 * Return:
 *      RT_ERR_OK       - Success
 *      RT_ERR_SMI      - SMI access error
 *      RT_ERR_INPUT    - Invalid input parameter
 * Note:
 *      None
 */
ret_t rtl8367d_getAsicRegBits(rtksw_uint32 unit, rtksw_uint32 reg, rtksw_uint32 bits, rtksw_uint32 *pValue)
{

#if defined(RTK_X86_ASICDRV)

    rtksw_uint32 regData;
    ret_t retVal;
    rtksw_uint32 bitsShift;

    if(bits >= (1 << RTL8367D_REGBITLENGTH) )
        return RT_ERR_INPUT;
    
    /* Skip warning */
    if (unit) {}

    bitsShift = 0;
    while(!(bits & (1 << bitsShift)))
    {
        bitsShift++;
        if(bitsShift >= RTL8367D_REGBITLENGTH)
            return RT_ERR_INPUT;
    }

    retVal = Access_Read(reg, 2, &regData);
    if(TRUE != retVal)
        return RT_ERR_SMI;

    *pValue = (regData & bits) >> bitsShift;

    if(0x8367B == cleDebuggingDisplay)
        PRINT("R[0x%4.4x]=0x%4.4x\n", reg, regData);

#elif defined(CONFIG_VIRTUAL_REG_ASICDRV_TEST)
    rtksw_uint32 bitsShift;

    if(bits >= (1 << RTL8367D_REGBITLENGTH) )
        return RT_ERR_INPUT;

    bitsShift = 0;
    while(!(bits & (1 << bitsShift)))
    {
        bitsShift++;
        if(bitsShift >= RTL8367D_REGBITLENGTH)
            return RT_ERR_INPUT;
    }

    if(reg >= CLE_VIRTUAL_REG_SIZE)
        return RT_ERR_OUT_OF_RANGE;

     *pValue = (CleVirtualReg[reg] & bits) >> bitsShift;

    if(0x8367B == cleDebuggingDisplay)
        PRINT("R[0x%4.4x]=0x%4.4x\n", reg, CleVirtualReg[reg]);

#else
    rtksw_uint32 regData;
    ret_t retVal;
    rtksw_uint32 bitsShift;

    if(bits>= (1<<RTL8367D_REGBITLENGTH) )
        return RT_ERR_INPUT;

    bitsShift = 0;
    while(!(bits & (1 << bitsShift)))
    {
        bitsShift++;
        if(bitsShift >= RTL8367D_REGBITLENGTH)
            return RT_ERR_INPUT;
    }

    retVal = reg_smi_read(unit, reg, &regData);
    if(retVal != RT_ERR_OK) return RT_ERR_SMI;

    *pValue = (regData & bits) >> bitsShift;
  #ifdef CONFIG_RTL865X_CLE
    if(0x8367B == cleDebuggingDisplay)
        PRINT("R[0x%4.4x]=0x%4.4x\n",reg, regData);
  #endif

#endif
    return RT_ERR_OK;
}
/* Function Name:
 *      rtl8367d_setAsicReg
 * Description:
 *      Set content of asic register
 * Input:
 *      unit    - Unit ID
 *      reg     - register's address
 *      value   - Value setting to register
 * Output:
 *      None
 * Return:
 *      RT_ERR_OK       - Success
 *      RT_ERR_SMI      - SMI access error
 * Note:
 *      The value will be set to ASIC mapping address only and it is always return RT_ERR_OK while setting un-mapping address registers
 */
ret_t rtl8367d_setAsicReg(rtksw_uint32 unit, rtksw_uint32 reg, rtksw_uint32 value)
{
#if defined(RTK_X86_ASICDRV)/*RTK-CNSD2-NickWu-20061222: for x86 compile*/

    ret_t retVal;

    /* Skip warning */
    if (unit) {}

    retVal = Access_Write(reg,2,value);
    if(TRUE != retVal) return RT_ERR_SMI;

    if(0x8367B == cleDebuggingDisplay)
        PRINT("W[0x%4.4x]=0x%4.4x\n",reg,value);

#elif defined(CONFIG_VIRTUAL_REG_ASICDRV_TEST)

    /*MIBs emulating*/
    if(reg == RTL8367D_REG_MIB_ADDRESS)
    {
        CleVirtualReg[RTL8367D_REG_MIB_COUNTER0] = 0x1;
        CleVirtualReg[RTL8367D_REG_MIB_COUNTER0+1] = 0x2;
        CleVirtualReg[RTL8367D_REG_MIB_COUNTER0+2] = 0x3;
        CleVirtualReg[RTL8367D_REG_MIB_COUNTER0+3] = 0x4;
    }

    if(reg >= CLE_VIRTUAL_REG_SIZE)
        return RT_ERR_OUT_OF_RANGE;

    CleVirtualReg[reg] = value;

    if(0x8367B == cleDebuggingDisplay)
        PRINT("W[0x%4.4x]=0x%4.4x\n",reg,CleVirtualReg[reg]);

#else
    ret_t retVal;

    retVal = reg_smi_write(unit, reg, value);
    if(retVal != RT_ERR_OK)
        return RT_ERR_SMI;
  #ifdef CONFIG_RTL865X_CLE
    if(0x8367B == cleDebuggingDisplay)
        PRINT("W[0x%4.4x]=0x%4.4x\n",reg,value);
  #endif

#endif

    return RT_ERR_OK;
}
/* Function Name:
 *      rtl8367d_getAsicReg
 * Description:
 *      Get content of asic register
 * Input:
 *      unit    - Unit ID
 *      reg     - register's address
 *      value   - Value setting to register
 * Output:
 *      None
 * Return:
 *      RT_ERR_OK       - Success
 *      RT_ERR_SMI      - SMI access error
 * Note:
 *      Value 0x0000 will be returned for ASIC un-mapping address
 */
ret_t rtl8367d_getAsicReg(rtksw_uint32 unit, rtksw_uint32 reg, rtksw_uint32 *pValue)
{

#if defined(RTK_X86_ASICDRV)

    rtksw_uint32 regData;
    ret_t retVal;

    /* Skip warning */
    if (unit) {}

    retVal = Access_Read(reg, 2, &regData);
    if(TRUE != retVal)
        return RT_ERR_SMI;

    *pValue = regData;

    if(0x8367B == cleDebuggingDisplay)
        PRINT("R[0x%4.4x]=0x%4.4x\n", reg, regData);

#elif defined(CONFIG_VIRTUAL_REG_ASICDRV_TEST)
    if(reg >= CLE_VIRTUAL_REG_SIZE)
        return RT_ERR_OUT_OF_RANGE;

    *pValue = CleVirtualReg[reg];

    if(0x8367B == cleDebuggingDisplay)
        PRINT("R[0x%4.4x]=0x%4.4x\n", reg, CleVirtualReg[reg]);

#else
    rtksw_uint32 regData;
    ret_t retVal;

    retVal = reg_smi_read(unit, reg, &regData);
    if(retVal != RT_ERR_OK)
        return RT_ERR_SMI;

    *pValue = regData;
  #ifdef CONFIG_RTL865X_CLE
    if(0x8367B == cleDebuggingDisplay)
        PRINT("R[0x%4.4x]=0x%4.4x\n", reg, regData);
  #endif

#endif

    return RT_ERR_OK;
}

