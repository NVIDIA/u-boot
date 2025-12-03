#ifndef _RTL8367C_ASICDRV_RMA_H_
#define _RTL8367C_ASICDRV_RMA_H_

#include "rtl8367c_asicdrv.h"

#define RTL8367C_RMAMAX                     0x2F

enum RTL8367C_RMAOP
{
    RMAOP_FORWARD = 0,
    RMAOP_TRAP_TO_CPU,
    RMAOP_DROP,
    RMAOP_FORWARD_EXCLUDE_CPU,
    RMAOP_END
};


typedef struct  rtl8367c_rma_s{

    rtksw_uint16 operation;
    rtksw_uint16 discard_storm_filter;
    rtksw_uint16 trap_priority;
    rtksw_uint16 keep_format;
    rtksw_uint16 vlan_leaky;
    rtksw_uint16 portiso_leaky;

}rtl8367c_rma_t;


extern ret_t rtl8367c_setAsicRma(rtksw_uint32 unit, rtksw_uint32 index, rtl8367c_rma_t* pRmacfg);
extern ret_t rtl8367c_getAsicRma(rtksw_uint32 unit, rtksw_uint32 index, rtl8367c_rma_t* pRmacfg);
extern ret_t rtl8367c_setAsicRmaCdp(rtksw_uint32 unit, rtl8367c_rma_t* pRmacfg);
extern ret_t rtl8367c_getAsicRmaCdp(rtksw_uint32 unit, rtl8367c_rma_t* pRmacfg);
extern ret_t rtl8367c_setAsicRmaCsstp(rtksw_uint32 unit, rtl8367c_rma_t* pRmacfg);
extern ret_t rtl8367c_getAsicRmaCsstp(rtksw_uint32 unit, rtl8367c_rma_t* pRmacfg);
extern ret_t rtl8367c_setAsicRmaLldp(rtksw_uint32 unit, rtksw_uint32 enabled, rtl8367c_rma_t* pRmacfg);
extern ret_t rtl8367c_getAsicRmaLldp(rtksw_uint32 unit, rtksw_uint32 *pEnabled, rtl8367c_rma_t* pRmacfg);

#endif /*#ifndef _RTL8367C_ASICDRV_RMA_H_*/

