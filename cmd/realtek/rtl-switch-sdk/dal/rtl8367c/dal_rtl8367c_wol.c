
#include "rtl8367c_asicdrv.h"

#include "dal_rtl8367c_wol.h"
#include "../../rtk_error.h"

#include "../dal_mgmts.h"

/* Function Name:
 *      dal_rtl8367c_wol_init
 * Description:
 *      Initial WoL function.
 * Input:
 *      unit        - Unit ID
 * Output:
 *      None.
 * Return:
 *      RT_ERR_OK               - OK
 *      RT_ERR_FAILED           - Failed
 * Note:
 *      This API initialize the WoL function.
 *
 *      After initialization, rtksw_wol_enable_set can be used to turn on or turn off WoL function.
 */
rtksw_api_ret_t dal_rtl8367c_wol_init(rtksw_uint32 unit)
{
  rtksw_api_ret_t retVal;

    if( (retVal = rtl8367c_setAsicRegBit(unit, 0x1322, 4, 1)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicRegBit(unit, 0x130C, 5, 1)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicRegBit(unit, 0x1336, 1, 1)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicRegBit(unit, 0x1336, 2, 0)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE000, 0x0002)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE001, 0x000B)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE002, 0x000F)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE003, 0x0000)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE004, 0x0000)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE005, 0x0000)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE006, 0x0000)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE007, 0x0000)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE008, 0x0000)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE009, 0x0000)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE00A, 0x0000)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE00B, 0x0002)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE00C, 0x000B)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE00D, 0x009B)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE00E, 0x0000)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE00F, 0x0000)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE010, 0x0000)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE011, 0x0000)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE012, 0x0000)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE013, 0x0002)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE014, 0x000B)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE015, 0x00D9)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE016, 0x00E4)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE017, 0x0090)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE018, 0x0008)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE019, 0x0031)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE01A, 0x00F0)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE01B, 0x00A3)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE01C, 0x00F0)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE01D, 0x0090)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE01E, 0x0008)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE01F, 0x0037)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE020, 0x0012)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE021, 0x0008)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE022, 0x0043)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE023, 0x0000)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE024, 0x0000)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE025, 0x0000)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE026, 0x0000)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE027, 0x00E4)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE028, 0x0090)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE029, 0x0008)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE02A, 0x003D)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE02B, 0x00F0)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE02C, 0x00A3)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE02D, 0x00F0)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE02E, 0x007D)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE02F, 0x0001)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE030, 0x00FC)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE031, 0x007F)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE032, 0x0036)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE033, 0x007E)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE034, 0x0013)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE035, 0x0012)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE036, 0x000B)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE037, 0x00F9)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE038, 0x0012)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE039, 0x0009)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE03A, 0x007F)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE03B, 0x0012)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE03C, 0x000A)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE03D, 0x006A)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE03E, 0x007D)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE03F, 0x0080)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE040, 0x007C)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE041, 0x0000)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE042, 0x007F)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE043, 0x000F)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE044, 0x007E)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE045, 0x001A)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE046, 0x0012)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE047, 0x000B)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE048, 0x00F9)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE049, 0x007D)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE04A, 0x0002)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE04B, 0x007C)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE04C, 0x0000)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE04D, 0x007F)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE04E, 0x0032)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE04F, 0x007E)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE050, 0x001D)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE051, 0x0012)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE052, 0x000B)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE053, 0x00F9)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE054, 0x00E4)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE055, 0x00F5)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE056, 0x00A8)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE057, 0x00D2)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE058, 0x00AF)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE059, 0x00F5)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE05A, 0x008E)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE05B, 0x0012)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE05C, 0x0008)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE05D, 0x0085)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE05E, 0x007D)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE05F, 0x0004)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE060, 0x007C)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE061, 0x0040)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE062, 0x007F)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE063, 0x00E0)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE064, 0x007E)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE065, 0x0018)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE066, 0x0012)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE067, 0x000B)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE068, 0x00F9)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE069, 0x007D)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE06A, 0x007F)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE06B, 0x007C)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE06C, 0x0000)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE06D, 0x007F)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE06E, 0x0090)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE06F, 0x007E)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE070, 0x0008)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE071, 0x0012)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE072, 0x000B)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE073, 0x00F9)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE074, 0x007D)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE075, 0x007F)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE076, 0x007C)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE077, 0x0000)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE078, 0x007F)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE079, 0x0091)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE07A, 0x007E)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE07B, 0x0008)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE07C, 0x0012)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE07D, 0x000B)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE07E, 0x00F9)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE07F, 0x007D)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE080, 0x007F)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE081, 0x007C)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE082, 0x0000)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE083, 0x007F)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE084, 0x0092)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE085, 0x007E)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE086, 0x0008)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE087, 0x0012)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE088, 0x000B)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE089, 0x00F9)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE08A, 0x00E4)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE08B, 0x00FD)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE08C, 0x00FC)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE08D, 0x007F)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE08E, 0x00A0)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE08F, 0x007E)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE090, 0x0013)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE091, 0x0012)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE092, 0x000B)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE093, 0x00F9)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE094, 0x00E4)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE095, 0x0090)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE096, 0x0008)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE097, 0x002E)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE098, 0x00F0)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE099, 0x00A3)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE09A, 0x00F0)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE09B, 0x0012)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE09C, 0x000C)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE09D, 0x0015)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE09E, 0x00EF)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE09F, 0x0070)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE0A0, 0x0003)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE0A1, 0x0002)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE0A2, 0x0003)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE0A3, 0x0075)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE0A4, 0x007B)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE0A5, 0x0001)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE0A6, 0x007A)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE0A7, 0x0000)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE0A8, 0x0079)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE0A9, 0x0002)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE0AA, 0x007F)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE0AB, 0x0000)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE0AC, 0x007E)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE0AD, 0x0008)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE0AE, 0x007D)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE0AF, 0x0000)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE0B0, 0x007C)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE0B1, 0x0000)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE0B2, 0x0012)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE0B3, 0x0004)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE0B4, 0x003F)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE0B5, 0x0090)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE0B6, 0x0008)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE0B7, 0x0030)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE0B8, 0x00EF)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE0B9, 0x00F0)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE0BA, 0x00E4)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE0BB, 0x0090)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE0BC, 0x0008)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE0BD, 0x0035)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE0BE, 0x00F0)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE0BF, 0x00A3)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE0C0, 0x00F0)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE0C1, 0x0090)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE0C2, 0x0008)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE0C3, 0x0018)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE0C4, 0x00E0)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE0C5, 0x00FF)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE0C6, 0x00A3)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE0C7, 0x00E0)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE0C8, 0x0090)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE0C9, 0x0008)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE0CA, 0x0031)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE0CB, 0x00CF)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE0CC, 0x00F0)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE0CD, 0x00A3)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE0CE, 0x00EF)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE0CF, 0x00F0)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE0D0, 0x0090)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE0D1, 0x0008)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE0D2, 0x003D)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE0D3, 0x00E0)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE0D4, 0x0070)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE0D5, 0x0004)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE0D6, 0x00A3)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE0D7, 0x00E0)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE0D8, 0x0064)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE0D9, 0x0001)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE0DA, 0x0060)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE0DB, 0x0003)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE0DC, 0x0002)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE0DD, 0x0003)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE0DE, 0x0056)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE0DF, 0x00C3)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE0E0, 0x0090)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE0E1, 0x0008)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE0E2, 0x0032)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE0E3, 0x00E0)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE0E4, 0x0094)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE0E5, 0x0072)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE0E6, 0x0090)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE0E7, 0x0008)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE0E8, 0x0031)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE0E9, 0x00E0)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE0EA, 0x0094)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE0EB, 0x0000)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE0EC, 0x0050)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE0ED, 0x0003)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE0EE, 0x0002)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE0EF, 0x0003)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE0F0, 0x0056)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE0F1, 0x0090)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE0F2, 0x0008)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE0F3, 0x0033)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE0F4, 0x00E4)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE0F5, 0x00F0)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE0F6, 0x00A3)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE0F7, 0x0074)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE0F8, 0x0014)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE0F9, 0x00F0)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE0FA, 0x0090)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE0FB, 0x0008)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE0FC, 0x0032)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE0FD, 0x00E0)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE0FE, 0x0024)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE0FF, 0x00A2)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE100, 0x00FF)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE101, 0x0090)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE102, 0x0008)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE103, 0x0031)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE104, 0x00E0)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE105, 0x0034)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE106, 0x00FF)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE107, 0x00FE)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE108, 0x0090)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE109, 0x0008)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE10A, 0x0033)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE10B, 0x00E0)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE10C, 0x00FC)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE10D, 0x00A3)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE10E, 0x00E0)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE10F, 0x00FD)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE110, 0x00D3)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE111, 0x009F)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE112, 0x00EC)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE113, 0x009E)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE114, 0x0040)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE115, 0x0003)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE116, 0x0002)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE117, 0x0003)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE118, 0x0056)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE119, 0x0074)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE11A, 0x0002)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE11B, 0x002D)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE11C, 0x00F5)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE11D, 0x0082)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE11E, 0x0074)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE11F, 0x0000)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE120, 0x003C)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE121, 0x00F5)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE122, 0x0083)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE123, 0x00E0)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE124, 0x00F4)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE125, 0x0060)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE126, 0x0003)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE127, 0x0002)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE128, 0x0003)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE129, 0x0045)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE12A, 0x0074)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE12B, 0x0003)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE12C, 0x002D)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE12D, 0x00F5)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE12E, 0x0082)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE12F, 0x0074)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE130, 0x0000)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE131, 0x003C)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE132, 0x00F5)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE133, 0x0083)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE134, 0x00E0)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE135, 0x00F4)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE136, 0x0060)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE137, 0x0003)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE138, 0x0002)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE139, 0x0003)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE13A, 0x0045)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE13B, 0x0074)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE13C, 0x0004)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE13D, 0x002D)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE13E, 0x00F5)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE13F, 0x0082)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE140, 0x0074)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE141, 0x0000)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE142, 0x003C)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE143, 0x00F5)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE144, 0x0083)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE145, 0x00E0)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE146, 0x00F4)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE147, 0x0060)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE148, 0x0003)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE149, 0x0002)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE14A, 0x0003)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE14B, 0x0045)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE14C, 0x0074)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE14D, 0x0005)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE14E, 0x002D)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE14F, 0x00F5)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE150, 0x0082)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE151, 0x0074)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE152, 0x0000)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE153, 0x003C)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE154, 0x00F5)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE155, 0x0083)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE156, 0x00E0)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE157, 0x00F4)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE158, 0x0060)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE159, 0x0003)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE15A, 0x0002)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE15B, 0x0003)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE15C, 0x0045)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE15D, 0x0074)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE15E, 0x0006)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE15F, 0x002D)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE160, 0x00F5)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE161, 0x0082)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE162, 0x0074)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE163, 0x0000)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE164, 0x003C)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE165, 0x00F5)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE166, 0x0083)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE167, 0x00E0)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE168, 0x00F4)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE169, 0x0060)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE16A, 0x0003)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE16B, 0x0002)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE16C, 0x0003)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE16D, 0x0045)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE16E, 0x0074)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE16F, 0x0007)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE170, 0x002D)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE171, 0x00F5)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE172, 0x0082)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE173, 0x0074)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE174, 0x0000)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE175, 0x003C)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE176, 0x00F5)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE177, 0x0083)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE178, 0x00E0)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE179, 0x00F4)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE17A, 0x0060)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE17B, 0x0003)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE17C, 0x0002)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE17D, 0x0003)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE17E, 0x0045)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE17F, 0x0090)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE180, 0x0008)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE181, 0x0035)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE182, 0x00F0)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE183, 0x00A3)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE184, 0x0004)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE185, 0x00F0)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE186, 0x007F)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE187, 0x00A1)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE188, 0x007E)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE189, 0x0013)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE18A, 0x0012)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE18B, 0x000C)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE18C, 0x0031)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE18D, 0x0090)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE18E, 0x0008)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE18F, 0x003B)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE190, 0x00EE)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE191, 0x00F0)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE192, 0x00A3)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE193, 0x00EF)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE194, 0x00F0)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE195, 0x0090)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE196, 0x0008)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE197, 0x003B)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE198, 0x00E0)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE199, 0x00FC)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE19A, 0x00A3)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE19B, 0x00E0)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE19C, 0x00FD)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE19D, 0x00EC)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE19E, 0x0090)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE19F, 0x0008)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE1A0, 0x0004)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE1A1, 0x00F0)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE1A2, 0x00ED)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE1A3, 0x00A3)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE1A4, 0x00F0)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE1A5, 0x007F)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE1A6, 0x00A2)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE1A7, 0x007E)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE1A8, 0x0013)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE1A9, 0x0012)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE1AA, 0x000C)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE1AB, 0x0031)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE1AC, 0x0090)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE1AD, 0x0008)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE1AE, 0x003B)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE1AF, 0x00EE)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE1B0, 0x00F0)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE1B1, 0x00A3)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE1B2, 0x00EF)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE1B3, 0x00F0)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE1B4, 0x0090)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE1B5, 0x0008)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE1B6, 0x003B)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE1B7, 0x00E0)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE1B8, 0x00FC)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE1B9, 0x00A3)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE1BA, 0x00E0)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE1BB, 0x00FD)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE1BC, 0x00EC)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE1BD, 0x0090)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE1BE, 0x0008)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE1BF, 0x0006)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE1C0, 0x00F0)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE1C1, 0x00ED)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE1C2, 0x00A3)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE1C3, 0x00F0)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE1C4, 0x007F)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE1C5, 0x00A3)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE1C6, 0x007E)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE1C7, 0x0013)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE1C8, 0x0012)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE1C9, 0x000C)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE1CA, 0x0031)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE1CB, 0x0090)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE1CC, 0x0008)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE1CD, 0x003B)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE1CE, 0x00EE)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE1CF, 0x00F0)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE1D0, 0x00A3)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE1D1, 0x00EF)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE1D2, 0x00F0)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE1D3, 0x0090)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE1D4, 0x0008)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE1D5, 0x003B)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE1D6, 0x00E0)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE1D7, 0x00FC)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE1D8, 0x00A3)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE1D9, 0x00E0)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE1DA, 0x00FD)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE1DB, 0x00EC)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE1DC, 0x0090)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE1DD, 0x0008)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE1DE, 0x0008)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE1DF, 0x00F0)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE1E0, 0x00ED)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE1E1, 0x00A3)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE1E2, 0x00F0)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE1E3, 0x00E4)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE1E4, 0x00FF)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE1E5, 0x00FE)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE1E6, 0x0090)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE1E7, 0x0008)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE1E8, 0x0033)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE1E9, 0x00E0)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE1EA, 0x00FC)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE1EB, 0x00A3)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE1EC, 0x00E0)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE1ED, 0x00FD)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE1EE, 0x008F)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE1EF, 0x0082)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE1F0, 0x008E)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE1F1, 0x0083)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE1F2, 0x0074)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE1F3, 0x0006)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE1F4, 0x0012)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE1F5, 0x0008)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE1F6, 0x0074)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE1F7, 0x00E5)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE1F8, 0x0082)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE1F9, 0x002D)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE1FA, 0x00F5)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE1FB, 0x0082)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE1FC, 0x00E5)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE1FD, 0x0083)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE1FE, 0x003C)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE1FF, 0x00F5)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE200, 0x0083)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE201, 0x00E5)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE202, 0x0082)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE203, 0x0024)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE204, 0x0008)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE205, 0x00F5)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE206, 0x0082)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE207, 0x00E5)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE208, 0x0083)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE209, 0x0034)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE20A, 0x0000)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE20B, 0x00F5)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE20C, 0x0083)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE20D, 0x00E0)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE20E, 0x00FB)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE20F, 0x0090)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE210, 0x0008)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE211, 0x0004)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE212, 0x00E0)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE213, 0x00FA)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE214, 0x00EB)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE215, 0x006A)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE216, 0x0060)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE217, 0x0003)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE218, 0x0002)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE219, 0x0003)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE21A, 0x0003)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE21B, 0x008F)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE21C, 0x0082)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE21D, 0x008E)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE21E, 0x0083)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE21F, 0x0074)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE220, 0x0006)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE221, 0x0012)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE222, 0x0008)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE223, 0x0074)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE224, 0x00E5)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE225, 0x0082)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE226, 0x002D)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE227, 0x00F5)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE228, 0x0082)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE229, 0x00E5)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE22A, 0x0083)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE22B, 0x003C)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE22C, 0x00F5)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE22D, 0x0083)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE22E, 0x00E5)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE22F, 0x0082)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE230, 0x0024)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE231, 0x0009)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE232, 0x00F5)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE233, 0x0082)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE234, 0x00E5)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE235, 0x0083)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE236, 0x0034)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE237, 0x0000)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE238, 0x00F5)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE239, 0x0083)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE23A, 0x00E0)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE23B, 0x00FD)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE23C, 0x0090)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE23D, 0x0008)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE23E, 0x0005)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE23F, 0x00E0)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE240, 0x00FC)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE241, 0x00ED)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE242, 0x006C)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE243, 0x0060)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE244, 0x0003)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE245, 0x0002)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE246, 0x0003)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE247, 0x0003)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE248, 0x0090)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE249, 0x0008)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE24A, 0x0033)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE24B, 0x00E0)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE24C, 0x00FC)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE24D, 0x00A3)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE24E, 0x00E0)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE24F, 0x00FD)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE250, 0x008F)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE251, 0x0082)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE252, 0x008E)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE253, 0x0083)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE254, 0x0074)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE255, 0x0006)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE256, 0x0012)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE257, 0x0008)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE258, 0x0074)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE259, 0x00E5)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE25A, 0x0082)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE25B, 0x002D)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE25C, 0x00F5)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE25D, 0x0082)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE25E, 0x00E5)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE25F, 0x0083)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE260, 0x003C)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE261, 0x00F5)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE262, 0x0083)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE263, 0x00E5)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE264, 0x0082)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE265, 0x0024)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE266, 0x000A)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE267, 0x00F5)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE268, 0x0082)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE269, 0x00E5)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE26A, 0x0083)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE26B, 0x0034)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE26C, 0x0000)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE26D, 0x00F5)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE26E, 0x0083)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE26F, 0x00E0)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE270, 0x00FB)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE271, 0x0090)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE272, 0x0008)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE273, 0x0006)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE274, 0x00E0)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE275, 0x00FA)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE276, 0x00EB)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE277, 0x006A)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE278, 0x0060)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE279, 0x0003)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE27A, 0x0002)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE27B, 0x0003)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE27C, 0x0003)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE27D, 0x008F)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE27E, 0x0082)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE27F, 0x008E)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE280, 0x0083)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE281, 0x0074)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE282, 0x0006)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE283, 0x0012)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE284, 0x0008)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE285, 0x0074)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE286, 0x00E5)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE287, 0x0082)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE288, 0x002D)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE289, 0x00F5)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE28A, 0x0082)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE28B, 0x00E5)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE28C, 0x0083)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE28D, 0x003C)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE28E, 0x00F5)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE28F, 0x0083)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE290, 0x00E5)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE291, 0x0082)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE292, 0x0024)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE293, 0x000B)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE294, 0x00F5)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE295, 0x0082)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE296, 0x00E5)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE297, 0x0083)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE298, 0x0034)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE299, 0x0000)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE29A, 0x00F5)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE29B, 0x0083)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE29C, 0x00E0)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE29D, 0x00FD)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE29E, 0x0090)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE29F, 0x0008)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE2A0, 0x0007)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE2A1, 0x00E0)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE2A2, 0x00FC)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE2A3, 0x00ED)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE2A4, 0x006C)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE2A5, 0x0070)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE2A6, 0x005C)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE2A7, 0x0090)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE2A8, 0x0008)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE2A9, 0x0033)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE2AA, 0x00E0)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE2AB, 0x00FC)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE2AC, 0x00A3)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE2AD, 0x00E0)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE2AE, 0x00FD)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE2AF, 0x008F)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE2B0, 0x0082)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE2B1, 0x008E)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE2B2, 0x0083)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE2B3, 0x0074)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE2B4, 0x0006)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE2B5, 0x0012)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE2B6, 0x0008)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE2B7, 0x0074)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE2B8, 0x00E5)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE2B9, 0x0082)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE2BA, 0x002D)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE2BB, 0x00F5)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE2BC, 0x0082)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE2BD, 0x00E5)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE2BE, 0x0083)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE2BF, 0x003C)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE2C0, 0x00F5)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE2C1, 0x0083)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE2C2, 0x00E5)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE2C3, 0x0082)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE2C4, 0x0024)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE2C5, 0x000C)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE2C6, 0x00F5)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE2C7, 0x0082)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE2C8, 0x00E5)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE2C9, 0x0083)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE2CA, 0x0034)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE2CB, 0x0000)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE2CC, 0x00F5)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE2CD, 0x0083)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE2CE, 0x00E0)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE2CF, 0x00FB)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE2D0, 0x0090)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE2D1, 0x0008)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE2D2, 0x0008)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE2D3, 0x00E0)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE2D4, 0x00FA)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE2D5, 0x00EB)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE2D6, 0x00B5)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE2D7, 0x0002)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE2D8, 0x002A)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE2D9, 0x008F)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE2DA, 0x0082)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE2DB, 0x008E)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE2DC, 0x0083)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE2DD, 0x0074)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE2DE, 0x0006)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE2DF, 0x0012)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE2E0, 0x0008)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE2E1, 0x0074)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE2E2, 0x00E5)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE2E3, 0x0082)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE2E4, 0x002D)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE2E5, 0x00F5)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE2E6, 0x0082)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE2E7, 0x00E5)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE2E8, 0x0083)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE2E9, 0x003C)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE2EA, 0x00F5)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE2EB, 0x0083)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE2EC, 0x00E5)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE2ED, 0x0082)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE2EE, 0x0024)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE2EF, 0x000D)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE2F0, 0x00F5)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE2F1, 0x0082)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE2F2, 0x00E5)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE2F3, 0x0083)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE2F4, 0x0034)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE2F5, 0x0000)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE2F6, 0x00F5)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE2F7, 0x0083)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE2F8, 0x00E0)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE2F9, 0x00FD)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE2FA, 0x0090)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE2FB, 0x0008)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE2FC, 0x0009)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE2FD, 0x00E0)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE2FE, 0x00FC)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE2FF, 0x00ED)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE300, 0x006C)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE301, 0x0060)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE302, 0x0009)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE303, 0x00E4)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE304, 0x0090)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE305, 0x0008)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE306, 0x0035)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE307, 0x00F0)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE308, 0x00A3)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE309, 0x00F0)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE30A, 0x0080)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE30B, 0x000E)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE30C, 0x000F)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE30D, 0x00BF)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE30E, 0x0000)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE30F, 0x0001)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE310, 0x000E)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE311, 0x00EF)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE312, 0x0064)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE313, 0x0010)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE314, 0x004E)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE315, 0x0060)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE316, 0x0003)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE317, 0x0002)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE318, 0x0001)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE319, 0x00E6)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE31A, 0x0090)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE31B, 0x0008)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE31C, 0x0035)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE31D, 0x00E0)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE31E, 0x0070)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE31F, 0x0004)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE320, 0x00A3)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE321, 0x00E0)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE322, 0x0064)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE323, 0x0001)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE324, 0x0070)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE325, 0x001F)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE326, 0x007F)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE327, 0x0002)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE328, 0x007E)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE329, 0x0011)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE32A, 0x0012)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE32B, 0x000C)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE32C, 0x0031)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE32D, 0x0090)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE32E, 0x0008)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE32F, 0x003B)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE330, 0x00EE)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE331, 0x00F0)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE332, 0x00A3)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE333, 0x00EF)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE334, 0x00F0)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE335, 0x0020)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE336, 0x00E7)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE337, 0x001E)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE338, 0x007D)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE339, 0x0001)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE33A, 0x007C)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE33B, 0x0000)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE33C, 0x007F)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE33D, 0x001A)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE33E, 0x007E)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE33F, 0x0011)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE340, 0x0012)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE341, 0x000B)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE342, 0x00F9)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE343, 0x0080)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE344, 0x0011)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE345, 0x0090)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE346, 0x0008)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE347, 0x0034)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE348, 0x00E0)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE349, 0x0004)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE34A, 0x00F0)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE34B, 0x0070)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE34C, 0x0006)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE34D, 0x0090)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE34E, 0x0008)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE34F, 0x0033)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE350, 0x00E0)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE351, 0x0004)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE352, 0x00F0)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE353, 0x0002)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE354, 0x0000)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE355, 0x00FA)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE356, 0x0090)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE357, 0x0008)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE358, 0x0037)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE359, 0x00E0)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE35A, 0x00FC)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE35B, 0x00A3)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE35C, 0x00E0)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE35D, 0x00FD)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE35E, 0x00A3)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE35F, 0x00E0)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE360, 0x00FE)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE361, 0x00A3)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE362, 0x00E0)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE363, 0x0024)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE364, 0x0001)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE365, 0x00FF)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE366, 0x00E4)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE367, 0x003E)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE368, 0x00FE)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE369, 0x00E4)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE36A, 0x003D)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE36B, 0x00FD)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE36C, 0x00E4)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE36D, 0x003C)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE36E, 0x00FC)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE36F, 0x0090)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE370, 0x0008)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE371, 0x0037)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE372, 0x0012)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE373, 0x0008)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE374, 0x0037)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE375, 0x0020)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE376, 0x0001)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE377, 0x0003)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE378, 0x0002)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE379, 0x0000)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE37A, 0x009B)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE37B, 0x00C2)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE37C, 0x0001)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE37D, 0x0090)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE37E, 0x0008)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE37F, 0x002F)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE380, 0x00E0)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE381, 0x0004)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE382, 0x00F0)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE383, 0x0070)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE384, 0x0006)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE385, 0x0090)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE386, 0x0008)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE387, 0x002E)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE388, 0x00E0)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE389, 0x0004)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE38A, 0x00F0)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE38B, 0x0090)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE38C, 0x0008)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE38D, 0x002E)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE38E, 0x00E0)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE38F, 0x00FC)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE390, 0x00A3)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE391, 0x00E0)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE392, 0x00FD)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE393, 0x007F)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE394, 0x00A4)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE395, 0x007E)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE396, 0x0013)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE397, 0x0012)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE398, 0x000B)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE399, 0x00F9)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE39A, 0x007F)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE39B, 0x00A0)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE39C, 0x007E)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE39D, 0x0013)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE39E, 0x0012)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE39F, 0x000C)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE3A0, 0x0031)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE3A1, 0x0090)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE3A2, 0x0008)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE3A3, 0x003B)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE3A4, 0x00EE)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE3A5, 0x00F0)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE3A6, 0x00A3)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE3A7, 0x00EF)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE3A8, 0x00F0)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE3A9, 0x0030)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE3AA, 0x00E0)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE3AB, 0x003E)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE3AC, 0x00A3)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE3AD, 0x00E0)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE3AE, 0x0070)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE3AF, 0x0002)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE3B0, 0x00A3)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE3B1, 0x00E0)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE3B2, 0x0070)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE3B3, 0x0036)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE3B4, 0x0090)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE3B5, 0x0008)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE3B6, 0x003D)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE3B7, 0x00F0)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE3B8, 0x00A3)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE3B9, 0x0004)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE3BA, 0x00F0)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE3BB, 0x007D)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE3BC, 0x00FF)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE3BD, 0x007C)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE3BE, 0x0000)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE3BF, 0x007F)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE3C0, 0x0090)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE3C1, 0x007E)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE3C2, 0x0008)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE3C3, 0x0012)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE3C4, 0x000B)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE3C5, 0x00F9)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE3C6, 0x007D)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE3C7, 0x00FF)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE3C8, 0x007C)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE3C9, 0x0000)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE3CA, 0x007F)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE3CB, 0x0091)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE3CC, 0x007E)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE3CD, 0x0008)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE3CE, 0x0012)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE3CF, 0x000B)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE3D0, 0x00F9)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE3D1, 0x007D)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE3D2, 0x00FF)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE3D3, 0x007C)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE3D4, 0x0000)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE3D5, 0x007F)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE3D6, 0x0092)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE3D7, 0x007E)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE3D8, 0x0008)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE3D9, 0x0012)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE3DA, 0x000B)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE3DB, 0x00F9)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE3DC, 0x007D)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE3DD, 0x0080)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE3DE, 0x007C)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE3DF, 0x0000)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE3E0, 0x007F)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE3E1, 0x0001)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE3E2, 0x007E)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE3E3, 0x0011)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE3E4, 0x0012)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE3E5, 0x000B)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE3E6, 0x00F9)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE3E7, 0x0002)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE3E8, 0x0000)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE3E9, 0x009B)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE3EA, 0x0090)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE3EB, 0x0008)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE3EC, 0x003C)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE3ED, 0x00E0)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE3EE, 0x0030)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE3EF, 0x00E0)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE3F0, 0x0003)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE3F1, 0x0002)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE3F2, 0x0000)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE3F3, 0x009B)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE3F4, 0x00A3)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE3F5, 0x00E0)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE3F6, 0x0070)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE3F7, 0x0004)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE3F8, 0x00A3)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE3F9, 0x00E0)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE3FA, 0x0064)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE3FB, 0x0001)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE3FC, 0x0060)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE3FD, 0x0003)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE3FE, 0x0002)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE3FF, 0x0000)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE400, 0x009B)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE401, 0x0090)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE402, 0x0008)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE403, 0x003D)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE404, 0x00F0)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE405, 0x00A3)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE406, 0x00F0)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE407, 0x007D)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE408, 0x007F)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE409, 0x00FC)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE40A, 0x007F)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE40B, 0x0090)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE40C, 0x007E)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE40D, 0x0008)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE40E, 0x0012)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE40F, 0x000B)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE410, 0x00F9)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE411, 0x007D)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE412, 0x007F)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE413, 0x007C)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE414, 0x0000)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE415, 0x007F)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE416, 0x0091)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE417, 0x007E)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE418, 0x0008)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE419, 0x0012)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE41A, 0x000B)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE41B, 0x00F9)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE41C, 0x007D)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE41D, 0x007F)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE41E, 0x007C)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE41F, 0x0000)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE420, 0x007F)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE421, 0x0092)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE422, 0x007E)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE423, 0x0008)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE424, 0x0012)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE425, 0x000B)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE426, 0x00F9)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE427, 0x007D)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE428, 0x0080)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE429, 0x007C)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE42A, 0x0000)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE42B, 0x007F)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE42C, 0x0002)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE42D, 0x007E)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE42E, 0x0011)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE42F, 0x0012)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE430, 0x000B)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE431, 0x00F9)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE432, 0x00E4)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE433, 0x00FD)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE434, 0x00FC)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE435, 0x007F)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE436, 0x0001)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE437, 0x007E)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE438, 0x0011)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE439, 0x0012)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE43A, 0x000B)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE43B, 0x00F9)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE43C, 0x0002)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE43D, 0x0000)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE43E, 0x009B)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE43F, 0x0090)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE440, 0x0008)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE441, 0x003F)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE442, 0x00EB)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE443, 0x00F0)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE444, 0x00A3)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE445, 0x00EA)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE446, 0x00F0)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE447, 0x00A3)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE448, 0x00E9)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE449, 0x00F0)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE44A, 0x00A3)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE44B, 0x0012)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE44C, 0x0008)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE44D, 0x0037)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE44E, 0x00E4)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE44F, 0x0090)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE450, 0x0008)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE451, 0x0048)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE452, 0x00F0)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE453, 0x00A3)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE454, 0x00F0)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE455, 0x007F)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE456, 0x0051)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE457, 0x007E)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE458, 0x001A)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE459, 0x0012)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE45A, 0x000C)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE45B, 0x0031)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE45C, 0x00EF)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE45D, 0x007D)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE45E, 0x0000)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE45F, 0x00FC)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE460, 0x00C0)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE461, 0x0005)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE462, 0x00C0)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE463, 0x0004)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE464, 0x007F)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE465, 0x0050)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE466, 0x007E)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE467, 0x001A)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE468, 0x0012)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE469, 0x000C)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE46A, 0x0031)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE46B, 0x00D0)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE46C, 0x00E0)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE46D, 0x004E)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE46E, 0x00FE)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE46F, 0x00D0)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE470, 0x00E0)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE471, 0x004F)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE472, 0x0078)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE473, 0x0003)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE474, 0x00C3)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE475, 0x0033)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE476, 0x00CE)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE477, 0x0033)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE478, 0x00CE)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE479, 0x00D8)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE47A, 0x00F9)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE47B, 0x00FF)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE47C, 0x0090)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE47D, 0x0008)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE47E, 0x0046)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE47F, 0x00EE)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE480, 0x00F0)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE481, 0x00FC)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE482, 0x00A3)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE483, 0x00EF)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE484, 0x00F0)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE485, 0x00FD)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE486, 0x0090)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE487, 0x0008)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE488, 0x003F)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE489, 0x00A3)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE48A, 0x00E0)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE48B, 0x00FA)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE48C, 0x00A3)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE48D, 0x00E0)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE48E, 0x00F5)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE48F, 0x00B3)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE490, 0x00EA)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE491, 0x00F5)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE492, 0x00B4)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE493, 0x00AF)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE494, 0x0005)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE495, 0x00EF)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE496, 0x00F5)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE497, 0x00B5)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE498, 0x00AE)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE499, 0x0004)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE49A, 0x00EE)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE49B, 0x00F5)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE49C, 0x00B6)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE49D, 0x0075)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE49E, 0x00B7)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE49F, 0x0001)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE4A0, 0x00E5)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE4A1, 0x00B7)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE4A2, 0x0070)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE4A3, 0x00FC)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE4A4, 0x0090)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE4A5, 0x0008)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE4A6, 0x003F)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE4A7, 0x00E0)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE4A8, 0x00FB)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE4A9, 0x00A3)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE4AA, 0x00E0)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE4AB, 0x00FA)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE4AC, 0x00A3)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE4AD, 0x00E0)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE4AE, 0x00F9)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE4AF, 0x0090)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE4B0, 0x0000)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE4B1, 0x0006)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE4B2, 0x0012)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE4B3, 0x0006)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE4B4, 0x00C3)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE4B5, 0x00FE)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE4B6, 0x0090)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE4B7, 0x0000)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE4B8, 0x0007)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE4B9, 0x0012)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE4BA, 0x0006)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE4BB, 0x00C3)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE4BC, 0x00FD)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE4BD, 0x00ED)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE4BE, 0x00FF)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE4BF, 0x0090)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE4C0, 0x0008)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE4C1, 0x0018)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE4C2, 0x00EE)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE4C3, 0x00F0)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE4C4, 0x00A3)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE4C5, 0x00EF)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE4C6, 0x00F0)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE4C7, 0x0090)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE4C8, 0x0008)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE4C9, 0x0018)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE4CA, 0x00E0)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE4CB, 0x00FE)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE4CC, 0x00A3)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE4CD, 0x00E0)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE4CE, 0x00FF)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE4CF, 0x00E4)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE4D0, 0x00FC)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE4D1, 0x00FD)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE4D2, 0x0090)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE4D3, 0x0008)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE4D4, 0x0042)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE4D5, 0x00E0)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE4D6, 0x00F8)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE4D7, 0x00A3)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE4D8, 0x00E0)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE4D9, 0x00F9)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE4DA, 0x00A3)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE4DB, 0x00E0)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE4DC, 0x00FA)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE4DD, 0x00A3)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE4DE, 0x00E0)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE4DF, 0x00FB)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE4E0, 0x00C3)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE4E1, 0x0012)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE4E2, 0x0008)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE4E3, 0x0013)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE4E4, 0x0050)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE4E5, 0x000B)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE4E6, 0x007D)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE4E7, 0x0003)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE4E8, 0x007C)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE4E9, 0x0000)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE4EA, 0x007F)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE4EB, 0x00A1)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE4EC, 0x007E)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE4ED, 0x000B)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE4EE, 0x0012)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE4EF, 0x000B)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE4F0, 0x00F9)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE4F1, 0x0090)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE4F2, 0x0008)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE4F3, 0x003F)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE4F4, 0x00E0)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE4F5, 0x00FB)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE4F6, 0x00A3)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE4F7, 0x00E0)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE4F8, 0x00FA)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE4F9, 0x00A3)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE4FA, 0x00E0)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE4FB, 0x00F9)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE4FC, 0x0090)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE4FD, 0x0000)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE4FE, 0x0001)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE4FF, 0x0012)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE500, 0x0006)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE501, 0x00C3)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE502, 0x00FE)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE503, 0x0012)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE504, 0x0006)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE505, 0x00AA)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE506, 0x00FD)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE507, 0x00EE)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE508, 0x00FC)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE509, 0x0090)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE50A, 0x0000)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE50B, 0x0002)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE50C, 0x0012)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE50D, 0x0006)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE50E, 0x00C3)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE50F, 0x007E)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE510, 0x0000)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE511, 0x0078)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE512, 0x0010)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE513, 0x00C3)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE514, 0x0033)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE515, 0x00CE)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE516, 0x0033)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE517, 0x00CE)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE518, 0x00D8)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE519, 0x00F9)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE51A, 0x00FF)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE51B, 0x00EC)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE51C, 0x004E)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE51D, 0x00FC)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE51E, 0x00ED)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE51F, 0x004F)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE520, 0x00FD)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE521, 0x0090)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE522, 0x0000)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE523, 0x0003)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE524, 0x0012)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE525, 0x0006)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE526, 0x00C3)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE527, 0x007E)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE528, 0x0000)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE529, 0x0078)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE52A, 0x0018)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE52B, 0x00C3)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE52C, 0x0033)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE52D, 0x00CE)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE52E, 0x0033)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE52F, 0x00CE)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE530, 0x00D8)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE531, 0x00F9)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE532, 0x00FF)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE533, 0x00EC)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE534, 0x004E)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE535, 0x00FE)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE536, 0x00ED)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE537, 0x004F)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE538, 0x00FF)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE539, 0x00E4)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE53A, 0x00FC)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE53B, 0x00FD)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE53C, 0x0090)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE53D, 0x0008)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE53E, 0x0012)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE53F, 0x0012)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE540, 0x0008)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE541, 0x0037)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE542, 0x0090)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE543, 0x0008)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE544, 0x0012)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE545, 0x00A3)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE546, 0x00A3)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE547, 0x00A3)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE548, 0x00E0)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE549, 0x00FB)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE54A, 0x00E4)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE54B, 0x00FA)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE54C, 0x00F9)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE54D, 0x00F8)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE54E, 0x0090)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE54F, 0x0008)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE550, 0x0010)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE551, 0x00E0)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE552, 0x00FF)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE553, 0x00E4)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE554, 0x00FC)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE555, 0x00FD)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE556, 0x00FE)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE557, 0x00C3)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE558, 0x0012)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE559, 0x0008)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE55A, 0x0013)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE55B, 0x0060)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE55C, 0x000B)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE55D, 0x007D)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE55E, 0x0001)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE55F, 0x007C)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE560, 0x0000)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE561, 0x007F)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE562, 0x00A1)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE563, 0x007E)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE564, 0x000B)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE565, 0x0012)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE566, 0x000B)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE567, 0x00F9)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE568, 0x0090)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE569, 0x0008)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE56A, 0x003F)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE56B, 0x00E0)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE56C, 0x00FB)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE56D, 0x00A3)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE56E, 0x00E0)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE56F, 0x00FA)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE570, 0x00A3)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE571, 0x00E0)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE572, 0x00F9)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE573, 0x0012)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE574, 0x0006)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE575, 0x00AA)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE576, 0x00FD)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE577, 0x007C)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE578, 0x0000)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE579, 0x007F)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE57A, 0x00A4)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE57B, 0x007E)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE57C, 0x000B)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE57D, 0x0012)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE57E, 0x000B)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE57F, 0x00F9)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE580, 0x0090)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE581, 0x0008)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE582, 0x003F)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE583, 0x00E0)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE584, 0x00FB)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE585, 0x00A3)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE586, 0x00E0)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE587, 0x00FA)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE588, 0x00A3)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE589, 0x00E0)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE58A, 0x00F9)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE58B, 0x0090)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE58C, 0x0000)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE58D, 0x0001)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE58E, 0x0012)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE58F, 0x0006)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE590, 0x00C3)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE591, 0x00FD)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE592, 0x007C)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE593, 0x0000)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE594, 0x007F)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE595, 0x00A5)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE596, 0x007E)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE597, 0x000B)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE598, 0x0012)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE599, 0x000B)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE59A, 0x00F9)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE59B, 0x0090)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE59C, 0x0008)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE59D, 0x003F)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE59E, 0x00E0)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE59F, 0x00FB)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE5A0, 0x00A3)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE5A1, 0x00E0)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE5A2, 0x00FA)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE5A3, 0x00A3)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE5A4, 0x00E0)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE5A5, 0x00F9)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE5A6, 0x0090)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE5A7, 0x0000)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE5A8, 0x0002)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE5A9, 0x0012)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE5AA, 0x0006)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE5AB, 0x00C3)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE5AC, 0x00FD)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE5AD, 0x007C)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE5AE, 0x0000)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE5AF, 0x007F)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE5B0, 0x00A6)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE5B1, 0x007E)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE5B2, 0x000B)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE5B3, 0x0012)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE5B4, 0x000B)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE5B5, 0x00F9)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE5B6, 0x0090)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE5B7, 0x0008)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE5B8, 0x003F)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE5B9, 0x00E0)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE5BA, 0x00FB)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE5BB, 0x00A3)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE5BC, 0x00E0)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE5BD, 0x00FA)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE5BE, 0x00A3)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE5BF, 0x00E0)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE5C0, 0x00F9)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE5C1, 0x0090)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE5C2, 0x0000)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE5C3, 0x0003)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE5C4, 0x0012)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE5C5, 0x0006)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE5C6, 0x00C3)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE5C7, 0x00FD)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE5C8, 0x007C)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE5C9, 0x0000)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE5CA, 0x007F)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE5CB, 0x00A7)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE5CC, 0x007E)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE5CD, 0x000B)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE5CE, 0x0012)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE5CF, 0x000B)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE5D0, 0x00F9)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE5D1, 0x0090)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE5D2, 0x0008)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE5D3, 0x0010)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE5D4, 0x00E0)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE5D5, 0x0004)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE5D6, 0x00F0)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE5D7, 0x0090)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE5D8, 0x0008)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE5D9, 0x0047)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE5DA, 0x00E0)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE5DB, 0x0024)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE5DC, 0x0008)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE5DD, 0x00FF)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE5DE, 0x0090)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE5DF, 0x0008)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE5E0, 0x0046)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE5E1, 0x00E0)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE5E2, 0x0034)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE5E3, 0x0000)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE5E4, 0x00FE)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE5E5, 0x007C)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE5E6, 0x0018)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE5E7, 0x007D)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE5E8, 0x0000)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE5E9, 0x0012)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE5EA, 0x0006)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE5EB, 0x00F0)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE5EC, 0x00EC)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE5ED, 0x00F0)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE5EE, 0x00A3)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE5EF, 0x00ED)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE5F0, 0x00F0)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE5F1, 0x0090)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE5F2, 0x0008)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE5F3, 0x003F)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE5F4, 0x00A3)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE5F5, 0x00E0)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE5F6, 0x00FA)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE5F7, 0x00A3)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE5F8, 0x00E0)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE5F9, 0x0024)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE5FA, 0x0008)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE5FB, 0x00F9)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE5FC, 0x00E4)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE5FD, 0x003A)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE5FE, 0x00FA)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE5FF, 0x00E9)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE600, 0x00F5)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE601, 0x00B3)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE602, 0x00AE)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE603, 0x0002)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE604, 0x00EE)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE605, 0x00F5)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE606, 0x00B4)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE607, 0x00AF)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE608, 0x0005)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE609, 0x00EF)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE60A, 0x00F5)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE60B, 0x00B5)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE60C, 0x00AE)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE60D, 0x0004)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE60E, 0x00EE)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE60F, 0x00F5)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE610, 0x00B6)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE611, 0x0090)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE612, 0x0008)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE613, 0x0019)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE614, 0x00E0)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE615, 0x0024)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE616, 0x0007)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE617, 0x00FF)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE618, 0x0090)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE619, 0x0008)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE61A, 0x0018)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE61B, 0x00E0)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE61C, 0x0034)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE61D, 0x0000)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE61E, 0x00FE)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE61F, 0x00EF)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE620, 0x0078)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE621, 0x0003)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE622, 0x00CE)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE623, 0x00C3)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE624, 0x0013)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE625, 0x00CE)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE626, 0x0013)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE627, 0x00D8)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE628, 0x00F9)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE629, 0x00F5)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE62A, 0x00B7)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE62B, 0x00E5)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE62C, 0x00B7)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE62D, 0x0070)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE62E, 0x00FC)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE62F, 0x007D)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE630, 0x0001)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE631, 0x007C)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE632, 0x0000)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE633, 0x007F)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE634, 0x000C)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE635, 0x007E)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE636, 0x001A)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE637, 0x0012)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE638, 0x000B)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE639, 0x00F9)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE63A, 0x0090)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE63B, 0x0008)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE63C, 0x000A)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE63D, 0x00E0)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE63E, 0x00FC)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE63F, 0x00A3)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE640, 0x00E0)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE641, 0x00FD)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE642, 0x00A3)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE643, 0x00E0)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE644, 0x00FE)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE645, 0x00A3)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE646, 0x00E0)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE647, 0x0024)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE648, 0x0001)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE649, 0x00FF)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE64A, 0x00E4)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE64B, 0x003E)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE64C, 0x00FE)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE64D, 0x00E4)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE64E, 0x003D)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE64F, 0x00FD)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE650, 0x00E4)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE651, 0x003C)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE652, 0x00FC)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE653, 0x0090)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE654, 0x0008)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE655, 0x000A)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE656, 0x0012)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE657, 0x0008)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE658, 0x0037)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE659, 0x0090)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE65A, 0x0008)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE65B, 0x000A)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE65C, 0x00A3)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE65D, 0x00A3)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE65E, 0x00E0)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE65F, 0x00FE)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE660, 0x00A3)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE661, 0x00E0)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE662, 0x00FF)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE663, 0x00E4)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE664, 0x00AD)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE665, 0x0007)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE666, 0x00AC)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE667, 0x0006)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE668, 0x007F)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE669, 0x00A7)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE66A, 0x007E)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE66B, 0x0013)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE66C, 0x0012)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE66D, 0x000B)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE66E, 0x00F9)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE66F, 0x0090)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE670, 0x0008)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE671, 0x000A)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE672, 0x00E0)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE673, 0x00FC)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE674, 0x00A3)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE675, 0x00E0)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE676, 0x00FD)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE677, 0x00A3)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE678, 0x00E0)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE679, 0x00FE)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE67A, 0x00A3)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE67B, 0x00E0)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE67C, 0x00FF)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE67D, 0x0078)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE67E, 0x0010)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE67F, 0x0012)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE680, 0x0008)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE681, 0x0024)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE682, 0x00AD)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE683, 0x0007)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE684, 0x00AC)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE685, 0x0006)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE686, 0x007F)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE687, 0x00A6)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE688, 0x007E)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE689, 0x0013)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE68A, 0x0012)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE68B, 0x000B)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE68C, 0x00F9)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE68D, 0x007F)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE68E, 0x0004)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE68F, 0x007E)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE690, 0x001A)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE691, 0x0012)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE692, 0x000C)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE693, 0x0031)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE694, 0x00EF)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE695, 0x004E)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE696, 0x0070)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE697, 0x000F)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE698, 0x007F)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE699, 0x0005)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE69A, 0x007E)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE69B, 0x001A)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE69C, 0x0012)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE69D, 0x000C)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE69E, 0x0031)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE69F, 0x00EF)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE6A0, 0x004E)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE6A1, 0x0070)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE6A2, 0x0004)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE6A3, 0x00C2)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE6A4, 0x0000)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE6A5, 0x00D2)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE6A6, 0x00AA)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE6A7, 0x007F)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE6A8, 0x0000)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE6A9, 0x0022)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE6AA, 0x00BB)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE6AB, 0x0001)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE6AC, 0x0006)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE6AD, 0x0089)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE6AE, 0x0082)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE6AF, 0x008A)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE6B0, 0x0083)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE6B1, 0x00E0)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE6B2, 0x0022)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE6B3, 0x0050)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE6B4, 0x0002)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE6B5, 0x00E7)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE6B6, 0x0022)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE6B7, 0x00BB)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE6B8, 0x00FE)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE6B9, 0x0002)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE6BA, 0x00E3)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE6BB, 0x0022)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE6BC, 0x0089)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE6BD, 0x0082)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE6BE, 0x008A)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE6BF, 0x0083)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE6C0, 0x00E4)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE6C1, 0x0093)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE6C2, 0x0022)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE6C3, 0x00BB)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE6C4, 0x0001)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE6C5, 0x000C)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE6C6, 0x00E5)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE6C7, 0x0082)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE6C8, 0x0029)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE6C9, 0x00F5)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE6CA, 0x0082)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE6CB, 0x00E5)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE6CC, 0x0083)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE6CD, 0x003A)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE6CE, 0x00F5)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE6CF, 0x0083)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE6D0, 0x00E0)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE6D1, 0x0022)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE6D2, 0x0050)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE6D3, 0x0006)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE6D4, 0x00E9)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE6D5, 0x0025)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE6D6, 0x0082)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE6D7, 0x00F8)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE6D8, 0x00E6)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE6D9, 0x0022)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE6DA, 0x00BB)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE6DB, 0x00FE)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE6DC, 0x0006)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE6DD, 0x00E9)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE6DE, 0x0025)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE6DF, 0x0082)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE6E0, 0x00F8)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE6E1, 0x00E2)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE6E2, 0x0022)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE6E3, 0x00E5)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE6E4, 0x0082)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE6E5, 0x0029)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE6E6, 0x00F5)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE6E7, 0x0082)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE6E8, 0x00E5)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE6E9, 0x0083)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE6EA, 0x003A)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE6EB, 0x00F5)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE6EC, 0x0083)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE6ED, 0x00E4)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE6EE, 0x0093)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE6EF, 0x0022)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE6F0, 0x00BC)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE6F1, 0x0000)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE6F2, 0x000B)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE6F3, 0x00BE)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE6F4, 0x0000)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE6F5, 0x0029)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE6F6, 0x00EF)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE6F7, 0x008D)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE6F8, 0x00F0)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE6F9, 0x0084)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE6FA, 0x00FF)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE6FB, 0x00AD)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE6FC, 0x00F0)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE6FD, 0x0022)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE6FE, 0x00E4)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE6FF, 0x00CC)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE700, 0x00F8)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE701, 0x0075)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE702, 0x00F0)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE703, 0x0008)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE704, 0x00EF)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE705, 0x002F)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE706, 0x00FF)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE707, 0x00EE)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE708, 0x0033)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE709, 0x00FE)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE70A, 0x00EC)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE70B, 0x0033)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE70C, 0x00FC)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE70D, 0x00EE)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE70E, 0x009D)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE70F, 0x00EC)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE710, 0x0098)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE711, 0x0040)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE712, 0x0005)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE713, 0x00FC)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE714, 0x00EE)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE715, 0x009D)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE716, 0x00FE)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE717, 0x000F)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE718, 0x00D5)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE719, 0x00F0)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE71A, 0x00E9)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE71B, 0x00E4)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE71C, 0x00CE)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE71D, 0x00FD)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE71E, 0x0022)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE71F, 0x00ED)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE720, 0x00F8)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE721, 0x00F5)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE722, 0x00F0)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE723, 0x00EE)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE724, 0x0084)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE725, 0x0020)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE726, 0x00D2)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE727, 0x001C)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE728, 0x00FE)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE729, 0x00AD)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE72A, 0x00F0)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE72B, 0x0075)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE72C, 0x00F0)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE72D, 0x0008)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE72E, 0x00EF)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE72F, 0x002F)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE730, 0x00FF)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE731, 0x00ED)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE732, 0x0033)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE733, 0x00FD)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE734, 0x0040)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE735, 0x0007)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE736, 0x0098)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE737, 0x0050)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE738, 0x0006)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE739, 0x00D5)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE73A, 0x00F0)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE73B, 0x00F2)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE73C, 0x0022)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE73D, 0x00C3)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE73E, 0x0098)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE73F, 0x00FD)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE740, 0x000F)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE741, 0x00D5)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE742, 0x00F0)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE743, 0x00EA)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE744, 0x0022)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE745, 0x0075)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE746, 0x00F0)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE747, 0x0008)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE748, 0x0075)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE749, 0x0082)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE74A, 0x0000)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE74B, 0x00EF)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE74C, 0x002F)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE74D, 0x00FF)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE74E, 0x00EE)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE74F, 0x0033)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE750, 0x00FE)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE751, 0x00CD)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE752, 0x0033)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE753, 0x00CD)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE754, 0x00CC)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE755, 0x0033)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE756, 0x00CC)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE757, 0x00C5)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE758, 0x0082)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE759, 0x0033)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE75A, 0x00C5)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE75B, 0x0082)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE75C, 0x009B)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE75D, 0x00ED)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE75E, 0x009A)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE75F, 0x00EC)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE760, 0x0099)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE761, 0x00E5)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE762, 0x0082)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE763, 0x0098)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE764, 0x0040)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE765, 0x000C)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE766, 0x00F5)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE767, 0x0082)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE768, 0x00EE)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE769, 0x009B)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE76A, 0x00FE)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE76B, 0x00ED)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE76C, 0x009A)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE76D, 0x00FD)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE76E, 0x00EC)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE76F, 0x0099)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE770, 0x00FC)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE771, 0x000F)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE772, 0x00D5)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE773, 0x00F0)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE774, 0x00D6)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE775, 0x00E4)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE776, 0x00CE)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE777, 0x00FB)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE778, 0x00E4)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE779, 0x00CD)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE77A, 0x00FA)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE77B, 0x00E4)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE77C, 0x00CC)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE77D, 0x00F9)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE77E, 0x00A8)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE77F, 0x0082)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE780, 0x0022)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE781, 0x00B8)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE782, 0x0000)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE783, 0x00C1)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE784, 0x00B9)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE785, 0x0000)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE786, 0x0059)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE787, 0x00BA)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE788, 0x0000)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE789, 0x002D)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE78A, 0x00EC)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE78B, 0x008B)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE78C, 0x00F0)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE78D, 0x0084)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE78E, 0x00CF)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE78F, 0x00CE)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE790, 0x00CD)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE791, 0x00FC)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE792, 0x00E5)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE793, 0x00F0)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE794, 0x00CB)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE795, 0x00F9)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE796, 0x0078)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE797, 0x0018)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE798, 0x00EF)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE799, 0x002F)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE79A, 0x00FF)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE79B, 0x00EE)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE79C, 0x0033)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE79D, 0x00FE)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE79E, 0x00ED)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE79F, 0x0033)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE7A0, 0x00FD)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE7A1, 0x00EC)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE7A2, 0x0033)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE7A3, 0x00FC)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE7A4, 0x00EB)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE7A5, 0x0033)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE7A6, 0x00FB)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE7A7, 0x0010)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE7A8, 0x00D7)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE7A9, 0x0003)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE7AA, 0x0099)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE7AB, 0x0040)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE7AC, 0x0004)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE7AD, 0x00EB)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE7AE, 0x0099)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE7AF, 0x00FB)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE7B0, 0x000F)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE7B1, 0x00D8)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE7B2, 0x00E5)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE7B3, 0x00E4)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE7B4, 0x00F9)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE7B5, 0x00FA)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE7B6, 0x0022)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE7B7, 0x0078)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE7B8, 0x0018)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE7B9, 0x00EF)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE7BA, 0x002F)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE7BB, 0x00FF)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE7BC, 0x00EE)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE7BD, 0x0033)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE7BE, 0x00FE)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE7BF, 0x00ED)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE7C0, 0x0033)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE7C1, 0x00FD)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE7C2, 0x00EC)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE7C3, 0x0033)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE7C4, 0x00FC)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE7C5, 0x00C9)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE7C6, 0x0033)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE7C7, 0x00C9)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE7C8, 0x0010)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE7C9, 0x00D7)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE7CA, 0x0005)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE7CB, 0x009B)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE7CC, 0x00E9)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE7CD, 0x009A)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE7CE, 0x0040)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE7CF, 0x0007)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE7D0, 0x00EC)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE7D1, 0x009B)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE7D2, 0x00FC)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE7D3, 0x00E9)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE7D4, 0x009A)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE7D5, 0x00F9)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE7D6, 0x000F)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE7D7, 0x00D8)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE7D8, 0x00E0)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE7D9, 0x00E4)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE7DA, 0x00C9)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE7DB, 0x00FA)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE7DC, 0x00E4)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE7DD, 0x00CC)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE7DE, 0x00FB)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE7DF, 0x0022)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE7E0, 0x0075)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE7E1, 0x00F0)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE7E2, 0x0010)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE7E3, 0x00EF)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE7E4, 0x002F)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE7E5, 0x00FF)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE7E6, 0x00EE)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE7E7, 0x0033)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE7E8, 0x00FE)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE7E9, 0x00ED)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE7EA, 0x0033)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE7EB, 0x00FD)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE7EC, 0x00CC)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE7ED, 0x0033)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE7EE, 0x00CC)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE7EF, 0x00C8)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE7F0, 0x0033)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE7F1, 0x00C8)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE7F2, 0x0010)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE7F3, 0x00D7)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE7F4, 0x0007)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE7F5, 0x009B)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE7F6, 0x00EC)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE7F7, 0x009A)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE7F8, 0x00E8)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE7F9, 0x0099)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE7FA, 0x0040)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE7FB, 0x000A)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE7FC, 0x00ED)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE7FD, 0x009B)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE7FE, 0x00FD)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE7FF, 0x00EC)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE800, 0x009A)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE801, 0x00FC)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE802, 0x00E8)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE803, 0x0099)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE804, 0x00F8)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE805, 0x000F)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE806, 0x00D5)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE807, 0x00F0)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE808, 0x00DA)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE809, 0x00E4)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE80A, 0x00CD)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE80B, 0x00FB)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE80C, 0x00E4)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE80D, 0x00CC)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE80E, 0x00FA)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE80F, 0x00E4)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE810, 0x00C8)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE811, 0x00F9)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE812, 0x0022)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE813, 0x00EB)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE814, 0x009F)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE815, 0x00F5)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE816, 0x00F0)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE817, 0x00EA)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE818, 0x009E)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE819, 0x0042)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE81A, 0x00F0)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE81B, 0x00E9)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE81C, 0x009D)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE81D, 0x0042)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE81E, 0x00F0)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE81F, 0x00E8)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE820, 0x009C)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE821, 0x0045)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE822, 0x00F0)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE823, 0x0022)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE824, 0x00E8)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE825, 0x0060)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE826, 0x000F)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE827, 0x00EC)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE828, 0x00C3)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE829, 0x0013)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE82A, 0x00FC)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE82B, 0x00ED)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE82C, 0x0013)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE82D, 0x00FD)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE82E, 0x00EE)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE82F, 0x0013)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE830, 0x00FE)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE831, 0x00EF)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE832, 0x0013)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE833, 0x00FF)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE834, 0x00D8)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE835, 0x00F1)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE836, 0x0022)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE837, 0x00EC)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE838, 0x00F0)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE839, 0x00A3)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE83A, 0x00ED)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE83B, 0x00F0)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE83C, 0x00A3)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE83D, 0x00EE)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE83E, 0x00F0)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE83F, 0x00A3)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE840, 0x00EF)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE841, 0x00F0)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE842, 0x0022)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE843, 0x00A8)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE844, 0x0082)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE845, 0x0085)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE846, 0x0083)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE847, 0x00F0)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE848, 0x00D0)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE849, 0x0083)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE84A, 0x00D0)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE84B, 0x0082)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE84C, 0x0012)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE84D, 0x0008)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE84E, 0x005A)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE84F, 0x0012)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE850, 0x0008)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE851, 0x005A)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE852, 0x0012)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE853, 0x0008)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE854, 0x005A)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE855, 0x0012)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE856, 0x0008)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE857, 0x005A)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE858, 0x00E4)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE859, 0x0073)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE85A, 0x00E4)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE85B, 0x0093)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE85C, 0x00A3)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE85D, 0x00C5)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE85E, 0x0083)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE85F, 0x00C5)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE860, 0x00F0)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE861, 0x00C5)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE862, 0x0083)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE863, 0x00C8)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE864, 0x00C5)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE865, 0x0082)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE866, 0x00C8)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE867, 0x00F0)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE868, 0x00A3)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE869, 0x00C5)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE86A, 0x0083)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE86B, 0x00C5)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE86C, 0x00F0)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE86D, 0x00C5)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE86E, 0x0083)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE86F, 0x00C8)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE870, 0x00C5)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE871, 0x0082)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE872, 0x00C8)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE873, 0x0022)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE874, 0x00F5)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE875, 0x00F0)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE876, 0x00C5)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE877, 0x0082)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE878, 0x00A4)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE879, 0x00C5)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE87A, 0x0082)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE87B, 0x00C5)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE87C, 0x00F0)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE87D, 0x00C5)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE87E, 0x0083)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE87F, 0x00A4)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE880, 0x0025)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE881, 0x0083)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE882, 0x00F5)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE883, 0x0083)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE884, 0x0022)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE885, 0x0075)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE886, 0x0089)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE887, 0x0011)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE888, 0x007F)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE889, 0x0036)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE88A, 0x007E)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE88B, 0x0013)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE88C, 0x0012)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE88D, 0x000C)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE88E, 0x0031)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE88F, 0x00EF)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE890, 0x0054)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE891, 0x0070)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE892, 0x00FF)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE893, 0x00E4)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE894, 0x00C4)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE895, 0x00F8)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE896, 0x0054)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE897, 0x00F0)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE898, 0x00C8)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE899, 0x0068)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE89A, 0x00FE)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE89B, 0x00EF)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE89C, 0x00C4)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE89D, 0x0054)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE89E, 0x000F)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE89F, 0x0048)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE8A0, 0x00FF)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE8A1, 0x00EE)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE8A2, 0x0070)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE8A3, 0x0045)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE8A4, 0x00EF)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE8A5, 0x0024)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE8A6, 0x00F0)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE8A7, 0x0060)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE8A8, 0x001C)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE8A9, 0x0024)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE8AA, 0x00F0)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE8AB, 0x0060)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE8AC, 0x0024)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE8AD, 0x0024)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE8AE, 0x00E0)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE8AF, 0x0060)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE8B0, 0x002C)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE8B1, 0x0024)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE8B2, 0x00F0)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE8B3, 0x0060)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE8B4, 0x0034)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE8B5, 0x0024)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE8B6, 0x0050)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE8B7, 0x0070)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE8B8, 0x0030)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE8B9, 0x0090)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE8BA, 0x0008)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE8BB, 0x003F)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE8BC, 0x0012)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE8BD, 0x0008)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE8BE, 0x0043)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE8BF, 0x000B)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE8C0, 0x00EB)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE8C1, 0x00C2)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE8C2, 0x0000)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE8C3, 0x0080)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE8C4, 0x002E)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE8C5, 0x0090)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE8C6, 0x0008)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE8C7, 0x003F)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE8C8, 0x0012)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE8C9, 0x0008)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE8CA, 0x0043)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE8CB, 0x0007)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE8CC, 0x0073)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE8CD, 0x0059)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE8CE, 0x0040)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE8CF, 0x0080)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE8D0, 0x0022)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE8D1, 0x0090)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE8D2, 0x0008)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE8D3, 0x003F)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE8D4, 0x0012)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE8D5, 0x0008)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE8D6, 0x0043)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE8D7, 0x0005)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE8D8, 0x00F5)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE8D9, 0x00E1)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE8DA, 0x0000)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE8DB, 0x0080)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE8DC, 0x0016)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE8DD, 0x0090)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE8DE, 0x0008)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE8DF, 0x003F)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE8E0, 0x0012)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE8E1, 0x0008)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE8E2, 0x0043)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE8E3, 0x0003)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE8E4, 0x00B9)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE8E5, 0x00AC)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE8E6, 0x00A0)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE8E7, 0x0080)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE8E8, 0x000A)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE8E9, 0x0090)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE8EA, 0x0008)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE8EB, 0x003F)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE8EC, 0x0012)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE8ED, 0x0008)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE8EE, 0x0043)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE8EF, 0x0001)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE8F0, 0x003D)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE8F1, 0x0062)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE8F2, 0x0000)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE8F3, 0x00E4)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE8F4, 0x007B)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE8F5, 0x00B0)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE8F6, 0x007A)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE8F7, 0x0004)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE8F8, 0x00F9)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE8F9, 0x00F8)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE8FA, 0x0090)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE8FB, 0x0008)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE8FC, 0x003F)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE8FD, 0x00E0)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE8FE, 0x00FC)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE8FF, 0x00A3)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE900, 0x00E0)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE901, 0x00FD)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE902, 0x00A3)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE903, 0x00E0)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE904, 0x00FE)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE905, 0x00A3)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE906, 0x00E0)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE907, 0x00FF)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE908, 0x0012)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE909, 0x0007)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE90A, 0x0081)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE90B, 0x00C3)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE90C, 0x00E4)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE90D, 0x009F)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE90E, 0x00FF)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE90F, 0x00E4)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE910, 0x009E)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE911, 0x00FE)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE912, 0x0074)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE913, 0x0001)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE914, 0x009D)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE915, 0x00FD)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE916, 0x00E4)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE917, 0x009C)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE918, 0x00FC)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE919, 0x00E4)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE91A, 0x00FB)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE91B, 0x007A)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE91C, 0x0001)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE91D, 0x00F9)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE91E, 0x00F8)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE91F, 0x0012)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE920, 0x0007)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE921, 0x0081)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE922, 0x0090)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE923, 0x0008)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE924, 0x0002)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE925, 0x00EF)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE926, 0x00F0)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE927, 0x00E4)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE928, 0x007B)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE929, 0x00B0)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE92A, 0x007A)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE92B, 0x0004)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE92C, 0x00F9)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE92D, 0x00F8)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE92E, 0x0090)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE92F, 0x0008)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE930, 0x003F)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE931, 0x00E0)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE932, 0x00FC)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE933, 0x00A3)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE934, 0x00E0)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE935, 0x00FD)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE936, 0x00A3)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE937, 0x00E0)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE938, 0x00FE)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE939, 0x00A3)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE93A, 0x00E0)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE93B, 0x00FF)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE93C, 0x0012)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE93D, 0x0007)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE93E, 0x0081)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE93F, 0x00C3)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE940, 0x00E4)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE941, 0x009F)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE942, 0x00FF)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE943, 0x00E4)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE944, 0x009E)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE945, 0x0074)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE946, 0x0001)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE947, 0x009D)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE948, 0x00E4)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE949, 0x009C)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE94A, 0x00E4)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE94B, 0x0090)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE94C, 0x0008)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE94D, 0x0003)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE94E, 0x00EF)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE94F, 0x00F0)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE950, 0x0090)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE951, 0x0008)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE952, 0x0002)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE953, 0x00E0)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE954, 0x00F5)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE955, 0x008C)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE956, 0x008F)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE957, 0x008A)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE958, 0x00AF)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE959, 0x008C)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE95A, 0x00EF)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE95B, 0x00FD)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE95C, 0x007C)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE95D, 0x0000)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE95E, 0x007F)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE95F, 0x00A7)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE960, 0x007E)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE961, 0x0013)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE962, 0x0012)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE963, 0x000B)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE964, 0x00F9)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE965, 0x00AF)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE966, 0x008A)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE967, 0x00EF)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE968, 0x00FD)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE969, 0x007C)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE96A, 0x0000)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE96B, 0x007F)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE96C, 0x00A6)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE96D, 0x007E)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE96E, 0x0013)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE96F, 0x0012)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE970, 0x000B)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE971, 0x00F9)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE972, 0x00C2)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE973, 0x0001)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE974, 0x0075)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE975, 0x0088)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE976, 0x0010)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE977, 0x0053)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE978, 0x008E)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE979, 0x00C7)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE97A, 0x00D2)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE97B, 0x00A9)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE97C, 0x00D2)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE97D, 0x008C)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE97E, 0x0022)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE97F, 0x007D)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE980, 0x0004)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE981, 0x007C)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE982, 0x0000)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE983, 0x007F)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE984, 0x0032)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE985, 0x007E)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE986, 0x001D)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE987, 0x0012)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE988, 0x000B)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE989, 0x00F9)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE98A, 0x00E4)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE98B, 0x00F5)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE98C, 0x00A8)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE98D, 0x00D2)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE98E, 0x00AF)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE98F, 0x0075)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE990, 0x00C8)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE991, 0x0034)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE992, 0x0075)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE993, 0x0098)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE994, 0x0050)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE995, 0x007F)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE996, 0x0036)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE997, 0x007E)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE998, 0x0013)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE999, 0x0012)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE99A, 0x000C)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE99B, 0x0031)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE99C, 0x00EE)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE99D, 0x00C4)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE99E, 0x00F8)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE99F, 0x0054)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE9A0, 0x00F0)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE9A1, 0x00C8)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE9A2, 0x00EF)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE9A3, 0x00C4)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE9A4, 0x0054)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE9A5, 0x000F)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE9A6, 0x0048)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE9A7, 0x007E)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE9A8, 0x0000)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE9A9, 0x0054)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE9AA, 0x0007)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE9AB, 0x00FF)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE9AC, 0x00EE)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE9AD, 0x0070)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE9AE, 0x0045)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE9AF, 0x00EF)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE9B0, 0x0024)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE9B1, 0x00F0)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE9B2, 0x0060)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE9B3, 0x001C)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE9B4, 0x0024)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE9B5, 0x00F0)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE9B6, 0x0060)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE9B7, 0x0024)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE9B8, 0x0024)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE9B9, 0x00E0)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE9BA, 0x0060)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE9BB, 0x002C)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE9BC, 0x0024)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE9BD, 0x00F0)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE9BE, 0x0060)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE9BF, 0x0034)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE9C0, 0x0024)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE9C1, 0x0050)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE9C2, 0x0070)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE9C3, 0x0030)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE9C4, 0x0090)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE9C5, 0x0008)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE9C6, 0x003F)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE9C7, 0x0012)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE9C8, 0x0008)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE9C9, 0x0043)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE9CA, 0x000B)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE9CB, 0x00EB)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE9CC, 0x00C2)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE9CD, 0x0000)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE9CE, 0x0080)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE9CF, 0x002E)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE9D0, 0x0090)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE9D1, 0x0008)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE9D2, 0x003F)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE9D3, 0x0012)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE9D4, 0x0008)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE9D5, 0x0043)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE9D6, 0x0007)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE9D7, 0x0073)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE9D8, 0x0059)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE9D9, 0x0040)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE9DA, 0x0080)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE9DB, 0x0022)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE9DC, 0x0090)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE9DD, 0x0008)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE9DE, 0x003F)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE9DF, 0x0012)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE9E0, 0x0008)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE9E1, 0x0043)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE9E2, 0x0005)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE9E3, 0x00F5)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE9E4, 0x00E1)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE9E5, 0x0000)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE9E6, 0x0080)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE9E7, 0x0016)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE9E8, 0x0090)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE9E9, 0x0008)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE9EA, 0x003F)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE9EB, 0x0012)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE9EC, 0x0008)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE9ED, 0x0043)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE9EE, 0x0003)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE9EF, 0x00B9)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE9F0, 0x00AC)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE9F1, 0x00A0)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE9F2, 0x0080)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE9F3, 0x000A)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE9F4, 0x0090)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE9F5, 0x0008)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE9F6, 0x003F)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE9F7, 0x0012)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE9F8, 0x0008)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE9F9, 0x0043)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE9FA, 0x0001)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE9FB, 0x003D)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE9FC, 0x0062)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE9FD, 0x0000)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE9FE, 0x007B)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xE9FF, 0x0000)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xEA00, 0x007A)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xEA01, 0x0020)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xEA02, 0x0079)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xEA03, 0x001C)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xEA04, 0x0078)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xEA05, 0x0000)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xEA06, 0x0090)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xEA07, 0x0008)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xEA08, 0x003F)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xEA09, 0x00E0)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xEA0A, 0x00FC)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xEA0B, 0x00A3)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xEA0C, 0x00E0)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xEA0D, 0x00FD)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xEA0E, 0x00A3)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xEA0F, 0x00E0)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xEA10, 0x00FE)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xEA11, 0x00A3)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xEA12, 0x00E0)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xEA13, 0x00FF)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xEA14, 0x0012)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xEA15, 0x0007)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xEA16, 0x0081)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xEA17, 0x00C3)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xEA18, 0x00E4)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xEA19, 0x009F)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xEA1A, 0x00FF)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xEA1B, 0x00E4)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xEA1C, 0x009E)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xEA1D, 0x00FE)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xEA1E, 0x0074)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xEA1F, 0x0001)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xEA20, 0x009D)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xEA21, 0x00FD)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xEA22, 0x00E4)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xEA23, 0x009C)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xEA24, 0x00FC)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xEA25, 0x0090)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xEA26, 0x0008)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xEA27, 0x003F)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xEA28, 0x0012)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xEA29, 0x0008)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xEA2A, 0x0037)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xEA2B, 0x0090)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xEA2C, 0x0008)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xEA2D, 0x003F)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xEA2E, 0x00A3)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xEA2F, 0x00A3)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xEA30, 0x00A3)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xEA31, 0x00E0)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xEA32, 0x00FF)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xEA33, 0x008F)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xEA34, 0x00CA)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xEA35, 0x0090)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xEA36, 0x0008)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xEA37, 0x003F)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xEA38, 0x00A3)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xEA39, 0x00A3)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xEA3A, 0x00E0)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xEA3B, 0x00FE)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xEA3C, 0x00A3)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xEA3D, 0x00E4)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xEA3E, 0x00FF)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xEA3F, 0x00E4)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xEA40, 0x00FD)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xEA41, 0x00FC)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xEA42, 0x0078)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xEA43, 0x0008)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xEA44, 0x0012)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xEA45, 0x0008)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xEA46, 0x0024)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xEA47, 0x008F)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xEA48, 0x00CB)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xEA49, 0x00AF)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xEA4A, 0x00CB)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xEA4B, 0x00EF)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xEA4C, 0x00AD)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xEA4D, 0x00CA)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xEA4E, 0x00FC)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xEA4F, 0x00ED)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xEA50, 0x007F)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xEA51, 0x00A0)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xEA52, 0x007E)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xEA53, 0x0013)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xEA54, 0x0012)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xEA55, 0x000B)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xEA56, 0x00F9)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xEA57, 0x00D2)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xEA58, 0x0099)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xEA59, 0x00C2)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xEA5A, 0x0098)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xEA5B, 0x00E4)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xEA5C, 0x00FF)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xEA5D, 0x00FE)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xEA5E, 0x000F)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xEA5F, 0x00BF)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xEA60, 0x0000)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xEA61, 0x0001)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xEA62, 0x000E)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xEA63, 0x00BE)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xEA64, 0x008F)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xEA65, 0x00F8)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xEA66, 0x00BF)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xEA67, 0x00FF)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xEA68, 0x00F5)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xEA69, 0x0022)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xEA6A, 0x00E4)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xEA6B, 0x0090)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xEA6C, 0x0008)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xEA6D, 0x0010)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xEA6E, 0x00F0)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xEA6F, 0x00A3)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xEA70, 0x00F0)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xEA71, 0x007D)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xEA72, 0x00F5)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xEA73, 0x00FC)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xEA74, 0x007F)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xEA75, 0x00C4)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xEA76, 0x007E)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xEA77, 0x0013)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xEA78, 0x0012)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xEA79, 0x000B)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xEA7A, 0x00F9)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xEA7B, 0x007D)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xEA7C, 0x0001)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xEA7D, 0x007C)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xEA7E, 0x0000)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xEA7F, 0x007F)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xEA80, 0x00C3)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xEA81, 0x007E)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xEA82, 0x0013)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xEA83, 0x0012)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xEA84, 0x000B)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xEA85, 0x00F9)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xEA86, 0x007F)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xEA87, 0x0022)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xEA88, 0x007E)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xEA89, 0x0013)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xEA8A, 0x0012)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xEA8B, 0x000C)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xEA8C, 0x0031)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xEA8D, 0x00EF)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xEA8E, 0x0044)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xEA8F, 0x0020)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xEA90, 0x00FD)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xEA91, 0x00AC)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xEA92, 0x0006)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xEA93, 0x007F)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xEA94, 0x0022)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xEA95, 0x007E)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xEA96, 0x0013)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xEA97, 0x0012)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xEA98, 0x000B)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xEA99, 0x00F9)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xEA9A, 0x007F)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xEA9B, 0x000C)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xEA9C, 0x007E)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xEA9D, 0x0013)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xEA9E, 0x0012)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xEA9F, 0x000C)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xEAA0, 0x0031)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xEAA1, 0x00EE)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xEAA2, 0x0044)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xEAA3, 0x0004)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xEAA4, 0x00AD)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xEAA5, 0x0007)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xEAA6, 0x00FC)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xEAA7, 0x007F)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xEAA8, 0x000C)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xEAA9, 0x007E)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xEAAA, 0x0013)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xEAAB, 0x0012)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xEAAC, 0x000B)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xEAAD, 0x00F9)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xEAAE, 0x007D)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xEAAF, 0x00FF)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xEAB0, 0x007C)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xEAB1, 0x0000)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xEAB2, 0x007F)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xEAB3, 0x0046)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xEAB4, 0x007E)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xEAB5, 0x001A)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xEAB6, 0x0012)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xEAB7, 0x000B)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xEAB8, 0x00F9)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xEAB9, 0x007D)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xEABA, 0x0002)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xEABB, 0x007C)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xEABC, 0x0000)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xEABD, 0x007F)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xEABE, 0x0047)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xEABF, 0x007E)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xEAC0, 0x001A)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xEAC1, 0x0012)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xEAC2, 0x000B)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xEAC3, 0x00F9)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xEAC4, 0x007D)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xEAC5, 0x00FE)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xEAC6, 0x007C)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xEAC7, 0x0000)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xEAC8, 0x007F)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xEAC9, 0x0044)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xEACA, 0x007E)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xEACB, 0x001A)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xEACC, 0x0012)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xEACD, 0x000B)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xEACE, 0x00F9)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xEACF, 0x007D)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xEAD0, 0x0003)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xEAD1, 0x007C)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xEAD2, 0x0000)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xEAD3, 0x007F)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xEAD4, 0x0045)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xEAD5, 0x007E)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xEAD6, 0x001A)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xEAD7, 0x0012)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xEAD8, 0x000B)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xEAD9, 0x00F9)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xEADA, 0x007D)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xEADB, 0x0004)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xEADC, 0x007C)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xEADD, 0x0000)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xEADE, 0x007F)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xEADF, 0x0048)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xEAE0, 0x007E)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xEAE1, 0x001A)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xEAE2, 0x0012)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xEAE3, 0x000B)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xEAE4, 0x00F9)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xEAE5, 0x00E4)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xEAE6, 0x00FD)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xEAE7, 0x00FC)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xEAE8, 0x007F)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xEAE9, 0x0017)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xEAEA, 0x007E)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xEAEB, 0x001A)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xEAEC, 0x0012)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xEAED, 0x000B)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xEAEE, 0x00F9)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xEAEF, 0x00E4)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xEAF0, 0x00FD)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xEAF1, 0x00FC)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xEAF2, 0x007F)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xEAF3, 0x005C)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xEAF4, 0x007E)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xEAF5, 0x001A)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xEAF6, 0x0012)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xEAF7, 0x000B)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xEAF8, 0x00F9)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xEAF9, 0x007D)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xEAFA, 0x0001)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xEAFB, 0x007C)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xEAFC, 0x0000)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xEAFD, 0x007F)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xEAFE, 0x0016)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xEAFF, 0x007E)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xEB00, 0x001A)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xEB01, 0x0012)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xEB02, 0x000B)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xEB03, 0x00F9)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xEB04, 0x007D)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xEB05, 0x001D)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xEB06, 0x007C)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xEB07, 0x0000)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xEB08, 0x007F)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xEB09, 0x0015)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xEB0A, 0x007E)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xEB0B, 0x001A)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xEB0C, 0x0002)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xEB0D, 0x000B)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xEB0E, 0x00F9)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xEB0F, 0x0078)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xEB10, 0x007F)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xEB11, 0x00E4)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xEB12, 0x00F6)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xEB13, 0x00D8)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xEB14, 0x00FD)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xEB15, 0x0075)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xEB16, 0x0081)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xEB17, 0x0020)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xEB18, 0x0002)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xEB19, 0x000B)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xEB1A, 0x0056)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xEB1B, 0x0002)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xEB1C, 0x0000)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xEB1D, 0x0016)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xEB1E, 0x00E4)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xEB1F, 0x0093)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xEB20, 0x00A3)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xEB21, 0x00F8)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xEB22, 0x00E4)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xEB23, 0x0093)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xEB24, 0x00A3)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xEB25, 0x0040)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xEB26, 0x0003)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xEB27, 0x00F6)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xEB28, 0x0080)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xEB29, 0x0001)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xEB2A, 0x00F2)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xEB2B, 0x0008)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xEB2C, 0x00DF)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xEB2D, 0x00F4)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xEB2E, 0x0080)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xEB2F, 0x0029)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xEB30, 0x00E4)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xEB31, 0x0093)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xEB32, 0x00A3)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xEB33, 0x00F8)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xEB34, 0x0054)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xEB35, 0x0007)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xEB36, 0x0024)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xEB37, 0x000C)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xEB38, 0x00C8)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xEB39, 0x00C3)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xEB3A, 0x0033)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xEB3B, 0x00C4)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xEB3C, 0x0054)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xEB3D, 0x000F)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xEB3E, 0x0044)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xEB3F, 0x0020)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xEB40, 0x00C8)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xEB41, 0x0083)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xEB42, 0x0040)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xEB43, 0x0004)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xEB44, 0x00F4)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xEB45, 0x0056)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xEB46, 0x0080)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xEB47, 0x0001)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xEB48, 0x0046)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xEB49, 0x00F6)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xEB4A, 0x00DF)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xEB4B, 0x00E4)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xEB4C, 0x0080)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xEB4D, 0x000B)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xEB4E, 0x0001)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xEB4F, 0x0002)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xEB50, 0x0004)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xEB51, 0x0008)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xEB52, 0x0010)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xEB53, 0x0020)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xEB54, 0x0040)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xEB55, 0x0080)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xEB56, 0x0090)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xEB57, 0x000C)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xEB58, 0x004C)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xEB59, 0x00E4)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xEB5A, 0x007E)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xEB5B, 0x0001)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xEB5C, 0x0093)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xEB5D, 0x0060)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xEB5E, 0x00BC)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xEB5F, 0x00A3)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xEB60, 0x00FF)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xEB61, 0x0054)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xEB62, 0x003F)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xEB63, 0x0030)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xEB64, 0x00E5)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xEB65, 0x0009)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xEB66, 0x0054)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xEB67, 0x001F)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xEB68, 0x00FE)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xEB69, 0x00E4)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xEB6A, 0x0093)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xEB6B, 0x00A3)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xEB6C, 0x0060)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xEB6D, 0x0001)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xEB6E, 0x000E)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xEB6F, 0x00CF)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xEB70, 0x0054)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xEB71, 0x00C0)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xEB72, 0x0025)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xEB73, 0x00E0)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xEB74, 0x0060)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xEB75, 0x00A8)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xEB76, 0x0040)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xEB77, 0x00B8)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xEB78, 0x00E4)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xEB79, 0x0093)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xEB7A, 0x00A3)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xEB7B, 0x00FA)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xEB7C, 0x00E4)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xEB7D, 0x0093)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xEB7E, 0x00A3)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xEB7F, 0x00F8)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xEB80, 0x00E4)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xEB81, 0x0093)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xEB82, 0x00A3)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xEB83, 0x00C8)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xEB84, 0x00C5)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xEB85, 0x0082)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xEB86, 0x00C8)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xEB87, 0x00CA)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xEB88, 0x00C5)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xEB89, 0x0083)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xEB8A, 0x00CA)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xEB8B, 0x00F0)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xEB8C, 0x00A3)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xEB8D, 0x00C8)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xEB8E, 0x00C5)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xEB8F, 0x0082)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xEB90, 0x00C8)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xEB91, 0x00CA)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xEB92, 0x00C5)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xEB93, 0x0083)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xEB94, 0x00CA)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xEB95, 0x00DF)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xEB96, 0x00E9)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xEB97, 0x00DE)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xEB98, 0x00E7)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xEB99, 0x0080)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xEB9A, 0x00BE)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xEB9B, 0x00C0)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xEB9C, 0x00E0)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xEB9D, 0x00C0)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xEB9E, 0x0083)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xEB9F, 0x00C0)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xEBA0, 0x0082)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xEBA1, 0x00C0)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xEBA2, 0x00D0)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xEBA3, 0x0090)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xEBA4, 0x0008)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xEBA5, 0x0002)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xEBA6, 0x00E0)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xEBA7, 0x00F5)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xEBA8, 0x008C)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xEBA9, 0x00A3)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xEBAA, 0x00E0)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xEBAB, 0x00F5)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xEBAC, 0x008A)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xEBAD, 0x0090)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xEBAE, 0x0000)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xEBAF, 0x0001)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xEBB0, 0x00E0)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xEBB1, 0x0004)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xEBB2, 0x00F0)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xEBB3, 0x0070)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xEBB4, 0x0006)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xEBB5, 0x0090)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xEBB6, 0x0000)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xEBB7, 0x0000)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xEBB8, 0x00E0)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xEBB9, 0x0004)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xEBBA, 0x00F0)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xEBBB, 0x00C3)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xEBBC, 0x0090)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xEBBD, 0x0000)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xEBBE, 0x0001)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xEBBF, 0x00E0)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xEBC0, 0x0094)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xEBC1, 0x0064)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xEBC2, 0x0090)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xEBC3, 0x0000)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xEBC4, 0x0000)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xEBC5, 0x00E0)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xEBC6, 0x0094)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xEBC7, 0x0000)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xEBC8, 0x0040)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xEBC9, 0x0006)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xEBCA, 0x00E4)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xEBCB, 0x00F0)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xEBCC, 0x00A3)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xEBCD, 0x00F0)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xEBCE, 0x00D2)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xEBCF, 0x0001)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xEBD0, 0x00D0)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xEBD1, 0x00D0)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xEBD2, 0x00D0)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xEBD3, 0x0082)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xEBD4, 0x00D0)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xEBD5, 0x0083)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xEBD6, 0x00D0)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xEBD7, 0x00E0)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xEBD8, 0x0032)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xEBD9, 0x00C2)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xEBDA, 0x00AA)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xEBDB, 0x0075)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xEBDC, 0x00A2)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xEBDD, 0x001A)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xEBDE, 0x0075)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xEBDF, 0x00A3)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xEBE0, 0x000E)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xEBE1, 0x0075)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xEBE2, 0x00A5)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xEBE3, 0x0080)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xEBE4, 0x0075)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xEBE5, 0x00A0)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xEBE6, 0x0003)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xEBE7, 0x0075)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xEBE8, 0x00A2)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xEBE9, 0x0012)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xEBEA, 0x0075)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xEBEB, 0x00A3)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xEBEC, 0x0002)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xEBED, 0x0075)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xEBEE, 0x00A4)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xEBEF, 0x0080)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xEBF0, 0x0075)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xEBF1, 0x00A5)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xEBF2, 0x0080)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xEBF3, 0x0075)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xEBF4, 0x00A0)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xEBF5, 0x0003)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xEBF6, 0x00D2)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xEBF7, 0x0000)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xEBF8, 0x0032)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xEBF9, 0x00AB)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xEBFA, 0x0007)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xEBFB, 0x00AA)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xEBFC, 0x0006)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xEBFD, 0x008A)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xEBFE, 0x00A2)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xEBFF, 0x0000)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xEC00, 0x008B)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xEC01, 0x00A3)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xEC02, 0x0000)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xEC03, 0x008C)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xEC04, 0x00A4)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xEC05, 0x0000)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xEC06, 0x008D)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xEC07, 0x00A5)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xEC08, 0x0000)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xEC09, 0x0075)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xEC0A, 0x00A0)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xEC0B, 0x0003)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xEC0C, 0x0000)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xEC0D, 0x0000)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xEC0E, 0x00AA)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xEC0F, 0x00A1)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xEC10, 0x0000)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xEC11, 0x00BA)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xEC12, 0x0000)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xEC13, 0x00F9)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xEC14, 0x0022)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xEC15, 0x007F)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xEC16, 0x0004)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xEC17, 0x007E)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xEC18, 0x001A)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xEC19, 0x0012)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xEC1A, 0x000C)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xEC1B, 0x0031)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xEC1C, 0x00EF)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xEC1D, 0x004E)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xEC1E, 0x0070)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xEC1F, 0x000B)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xEC20, 0x007F)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xEC21, 0x0005)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xEC22, 0x007E)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xEC23, 0x001A)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xEC24, 0x0012)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xEC25, 0x000C)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xEC26, 0x0031)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xEC27, 0x00EF)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xEC28, 0x004E)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xEC29, 0x0060)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xEC2A, 0x0003)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xEC2B, 0x007F)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xEC2C, 0x0001)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xEC2D, 0x0022)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xEC2E, 0x007F)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xEC2F, 0x0000)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xEC30, 0x0022)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xEC31, 0x00AD)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xEC32, 0x0007)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xEC33, 0x00AC)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xEC34, 0x0006)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xEC35, 0x008C)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xEC36, 0x00A2)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xEC37, 0x0000)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xEC38, 0x008D)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xEC39, 0x00A3)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xEC3A, 0x0000)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xEC3B, 0x0075)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xEC3C, 0x00A0)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xEC3D, 0x0001)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xEC3E, 0x0000)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xEC3F, 0x00AE)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xEC40, 0x00A1)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xEC41, 0x0000)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xEC42, 0x00BE)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xEC43, 0x0000)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xEC44, 0x00F9)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xEC45, 0x0000)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xEC46, 0x00AE)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xEC47, 0x00A6)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xEC48, 0x0000)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xEC49, 0x00AF)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xEC4A, 0x00A7)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xEC4B, 0x0022)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xEC4C, 0x00C1)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xEC4D, 0x0000)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xEC4E, 0x0042)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xEC4F, 0x0000)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xEC50, 0x0000)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xEC51, 0x0000)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xEC52, 0x0000)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xEC53, 0x0042)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xEC54, 0x0008)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xEC55, 0x002C)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xEC56, 0x0000)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xEC57, 0x0000)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xEC58, 0x0044)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xEC59, 0x0008)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xEC5A, 0x000A)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xEC5B, 0x0000)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xEC5C, 0x0000)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xEC5D, 0x0000)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xEC5E, 0x0000)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xEC5F, 0x0000)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xEC60, 0x00FF)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicReg(unit, 0xEC61, 0x00FF)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicRegBit(unit, 0x1336, 2, 0)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicRegBit(unit, 0x1336, 1, 0)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicRegBit(unit, 0x1322, 4, 0)) != RT_ERR_OK)
        return retVal;
    if( (retVal = rtl8367c_setAsicRegBit(unit, 0x1336, 9, 0)) != RT_ERR_OK)
        return retVal;

    return RT_ERR_OK;
}

/* Function Name:
 *      dal_rtl8367c_wol_state_set
 * Description:
 *      Enable/Disable WoL function.
 * Input:
 *      unit    - Unit ID
 *      state   - The state of WoL function
 * Output:
 *      None.
 * Return:
 *      RT_ERR_OK               - OK
 *      RT_ERR_FAILED           - Failed
 * Note:
 *      This API enable/disable the WoL function.
 */
rtksw_api_ret_t dal_rtl8367c_wol_state_set(rtksw_uint32 unit, rtksw_enable_t state)
{
    if(state >= RTKSW_ENABLE_END)
        return RT_ERR_INPUT;

    return rtl8367c_setAsicRegBit(unit, 0x13A0, 0, state);
}

/* Function Name:
 *      dal_rtl8367c_wol_systemMac_set
 * Description:
 *      Set WOL system MAC address.
 * Input:
 *      unit   - Unit ID
 *      pMac   - System MAC
 * Output:
 *      None.
 * Return:
 *      RT_ERR_OK           - OK
 *      RT_ERR_FAILED       - Failed
 *      RT_ERR_INPUT        - Error Input
 *      RT_ERR_SMI          - SMI access error
 * Note:
 *      This API enable/disable the WoL function.
 */
rtksw_api_ret_t dal_rtl8367c_wol_systemMac_set(rtksw_uint32 unit, rtksw_mac_t *pMac)
{
    rtksw_uint32      regData;
    rtksw_api_ret_t   retVal;

    if(pMac == NULL)
        return RT_ERR_INPUT;

    regData = ((pMac->octet[0] << 8) | pMac->octet[1]);
    if( (retVal = rtl8367c_setAsicReg(unit, RTL8367C_REG_DW8051_PRO_REG1, regData)) != RT_ERR_OK)
        return retVal;

    regData = ((pMac->octet[2] << 8) | pMac->octet[3]);
    if( (retVal = rtl8367c_setAsicReg(unit, RTL8367C_REG_DW8051_PRO_REG2, regData)) != RT_ERR_OK)
        return retVal;

    regData = ((pMac->octet[4] << 8) | pMac->octet[5]);
    if( (retVal = rtl8367c_setAsicReg(unit, RTL8367C_REG_DW8051_PRO_REG3, regData)) != RT_ERR_OK)
        return retVal;

    return RT_ERR_OK;
}

