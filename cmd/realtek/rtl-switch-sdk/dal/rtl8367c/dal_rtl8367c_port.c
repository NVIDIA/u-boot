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
 * Feature : Here is a list of all functions and variables in Port module.
 *
 */

#include "../../rtk_switch.h"
#include "../../rtk_error.h"
#include "dal_rtl8367c_port.h"

#include "rtl8367c_asicdrv.h"
#include "rtl8367c_asicdrv_port.h"
#include "rtl8367c_asicdrv_misc.h"
#include "rtl8367c_asicdrv_portIsolation.h"
#include "rtl8367c_asicdrv_green.h"

#include "../dal_mgmts.h"
#include "../../osal/lib.h"

#define FIBER_INIT_SIZE 1817
CONST_T rtksw_uint8 Fiber[FIBER_INIT_SIZE] = {
0x02,0x05,0x5C,0xE4,0xF5,0xA8,
0xD2,0xAF,0x22,0x00,0x00,0x02,0x06,0x87,
0xE4,0x90,0x06,0x2A,0xF0,0x90,0x06,0x2D,
0xF0,0xFD,0x7C,0x01,0x7F,0x3F,0x7E,0x1D,
0x12,0x06,0xE5,0x7D,0x40,0x12,0x03,0x55,
0x80,0x08,0x12,0x06,0x5B,0x50,0x08,0x12,
0x06,0x48,0x12,0x06,0x6C,0x80,0xF3,0xE4,
0xF5,0xA8,0xD2,0xAF,0x7D,0x1F,0xFC,0x7F,
0x49,0x7E,0x13,0x12,0x06,0xE5,0x12,0x07,
0x0C,0x7D,0xFE,0x7C,0x00,0x7F,0xAA,0x7E,
0x12,0x12,0x06,0xE5,0x7D,0xD7,0x12,0x03,
0x20,0x7D,0x80,0x12,0x02,0xBC,0x7D,0x94,
0x7C,0xF9,0x12,0x03,0x4D,0x7D,0x81,0x12,
0x02,0xBC,0x7D,0xA2,0x7C,0x31,0x12,0x03,
0x4D,0x7D,0x82,0x12,0x02,0xD1,0x7D,0x60,
0x7C,0x69,0x12,0x03,0x63,0x7D,0x83,0x12,
0x02,0xD1,0x7D,0x28,0x7C,0x97,0x12,0x03,
0x63,0x7D,0x84,0x12,0x02,0xE6,0x7D,0x85,
0x7C,0x9D,0x12,0x03,0x7C,0x7D,0x23,0x12,
0x02,0xE6,0x7D,0x10,0x7C,0xD8,0x12,0x03,
0x7C,0x7D,0x24,0x7C,0x04,0x12,0x03,0x3A,
0x7D,0x00,0x12,0x03,0x20,0x7D,0x2F,0x12,
0x02,0xFB,0x7D,0x20,0x7C,0x0F,0x7F,0x02,
0x7E,0x66,0x12,0x06,0xE5,0x7D,0x01,0x12,
0x02,0xFB,0x7D,0x04,0x7C,0x00,0x7F,0x01,
0x7E,0x66,0x12,0x06,0xE5,0x7D,0x80,0x7C,
0x00,0x7F,0x00,0x7E,0x66,0x12,0x06,0xE5,
0x7F,0x02,0x7E,0x66,0x12,0x06,0xC1,0x12,
0x06,0x73,0x44,0x02,0xFF,0x12,0x06,0x73,
0x44,0x04,0x12,0x06,0x7C,0xFD,0x7F,0x02,
0x7E,0x66,0x12,0x06,0xE5,0x7D,0x04,0x7C,
0x00,0x12,0x03,0x3A,0x7D,0xB9,0x7C,0x15,
0x7F,0xEB,0x7E,0x13,0x12,0x06,0xE5,0x7D,
0x07,0x7C,0x00,0x7F,0xE7,0x7E,0x13,0x12,
0x06,0xE5,0x7D,0x40,0x7C,0x11,0x7F,0x00,
0x7E,0x62,0x12,0x06,0xE5,0x12,0x04,0x9D,
0x7D,0x41,0x12,0x03,0x55,0x80,0x08,0x12,
0x06,0x5B,0x50,0x08,0x12,0x06,0x48,0x12,
0x06,0x6C,0x80,0xF3,0xC2,0x00,0xC2,0x01,
0xD2,0xA9,0xD2,0x8C,0x12,0x03,0x2A,0xEE,
0x44,0x18,0x12,0x03,0x6B,0xE4,0xFF,0xFE,
0xFD,0x80,0x0C,0x7F,0xD0,0x7E,0x07,0x12,
0x06,0x5F,0x50,0x08,0x12,0x06,0x48,0x12,
0x06,0x6C,0x80,0xEF,0x7F,0x04,0x7E,0x62,
0x12,0x06,0xC1,0x12,0x06,0x73,0xEE,0x44,
0x01,0xFE,0xEF,0x44,0x80,0x12,0x06,0x7C,
0xFD,0x7F,0x04,0x7E,0x62,0x12,0x06,0xE5,
0xE4,0xFF,0xFE,0xFD,0x80,0x08,0x12,0x06,
0x5B,0x50,0x08,0x12,0x06,0x48,0x12,0x06,
0x6C,0x80,0xF3,0x12,0x03,0x2A,0xEE,0x54,
0xE7,0x12,0x03,0x6B,0x12,0x03,0x10,0x12,
0x03,0x10,0x30,0xE2,0x71,0x90,0x06,0x2D,
0xE0,0x64,0x01,0x70,0x62,0x7F,0xEA,0x7E,
0x13,0x12,0x06,0xC1,0x90,0x06,0x2B,0xEE,
0xF0,0xA3,0xEF,0xF0,0x54,0xEF,0xFF,0x90,
0x06,0x2B,0xEE,0xF0,0xA3,0xEF,0xF0,0xEE,
0x44,0x10,0x90,0x06,0x2B,0xF0,0xFC,0xA3,
0xEF,0xF0,0xFD,0x7F,0x16,0x7E,0x13,0x12,
0x06,0xE5,0xE4,0xFF,0xFE,0xFD,0x80,0x0D,
0xE4,0x7F,0xFF,0x7E,0x6F,0x12,0x06,0x60,
0x50,0x08,0x12,0x06,0x48,0x12,0x06,0x6C,
0x80,0xEE,0x90,0x06,0x2B,0xE0,0x54,0xEF,
0xFE,0xA3,0xE0,0x90,0x06,0x2B,0x12,0x06,
0x7F,0xAD,0x07,0x7F,0x16,0x7E,0x13,0x12,
0x06,0xE5,0xE4,0x90,0x06,0x2D,0xF0,0xE4,
0x90,0x06,0x2A,0xF0,0x80,0x86,0x90,0x06,
0x2A,0xE0,0x70,0x13,0x12,0x02,0x47,0x90,
0x06,0x2A,0x74,0x01,0xF0,0xE4,0x90,0x06,
0x30,0xF0,0xA3,0xF0,0x02,0x01,0x92,0xC3,
0x90,0x06,0x31,0xE0,0x94,0x64,0x90,0x06,
0x30,0xE0,0x94,0x00,0x50,0x03,0x02,0x01,
0x92,0xE4,0xF0,0xA3,0xF0,0x12,0x02,0x47,
0x90,0x06,0x2A,0x74,0x01,0xF0,0x02,0x01,
0x92,0x7F,0x56,0x7E,0x13,0x12,0x06,0xC1,
0x90,0x06,0x2B,0xEE,0xF0,0xA3,0xEF,0xF0,
0x54,0xEF,0xFF,0x90,0x06,0x2B,0xEE,0xF0,
0xA3,0xEF,0xF0,0xEE,0x44,0x10,0x90,0x06,
0x2B,0xF0,0xFC,0xA3,0xEF,0xF0,0xFD,0x7F,
0x16,0x7E,0x13,0x12,0x06,0xE5,0x90,0x06,
0x2D,0x74,0x01,0xF0,0x7D,0x04,0x7C,0x00,
0x7F,0x02,0x7E,0x66,0x12,0x06,0xE5,0x7D,
0x00,0x7C,0x04,0x7F,0x01,0x7E,0x66,0x12,
0x06,0xE5,0x7D,0xC0,0x7C,0x00,0x7F,0x00,
0x7E,0x66,0x12,0x06,0xE5,0xE4,0xFD,0xFC,
0x7F,0x02,0x7E,0x66,0x12,0x06,0xE5,0x7D,
0x00,0x7C,0x04,0x7F,0x01,0x7E,0x66,0x12,
0x06,0xE5,0x7D,0xC0,0x7C,0x00,0x7F,0x00,
0x7E,0x66,0x12,0x06,0xE5,0x22,0x7C,0x04,
0x7F,0x01,0x7E,0x66,0x12,0x06,0xE5,0x7D,
0xC0,0x7C,0x00,0x7F,0x00,0x7E,0x66,0x12,
0x06,0xE5,0x22,0x7C,0x04,0x7F,0x01,0x7E,
0x66,0x12,0x06,0xE5,0x7D,0xC0,0x7C,0x00,
0x7F,0x00,0x7E,0x66,0x12,0x06,0xE5,0x22,
0x7C,0x04,0x7F,0x01,0x7E,0x66,0x12,0x06,
0xE5,0x7D,0xC0,0x7C,0x00,0x7F,0x00,0x7E,
0x66,0x12,0x06,0xE5,0x22,0x7C,0x00,0x7F,
0x01,0x7E,0x66,0x12,0x06,0xE5,0x7D,0xC0,
0x7C,0x00,0x7F,0x00,0x7E,0x66,0x12,0x06,
0xE5,0x22,0x7F,0x01,0x7E,0x62,0x12,0x06,
0xC1,0x90,0x06,0x28,0xEE,0xF0,0xA3,0xEF,
0xF0,0x22,0x7C,0x04,0x7F,0x02,0x7E,0x66,
0x12,0x06,0xE5,0x22,0x7F,0xE7,0x7E,0x13,
0x12,0x06,0xC1,0x90,0x06,0x28,0xEE,0xF0,
0xA3,0xEF,0xF0,0x22,0x7F,0x01,0x7E,0x66,
0x12,0x06,0xE5,0x7D,0xC0,0x7C,0x00,0x7F,
0x00,0x7E,0x66,0x12,0x06,0xE5,0x22,0x7F,
0x02,0x7E,0x66,0x12,0x06,0xE5,0x22,0x7C,
0x00,0x7F,0x36,0x7E,0x13,0x12,0x06,0xE5,
0xE4,0xFF,0xFE,0xFD,0x22,0x7F,0x02,0x7E,
0x66,0x12,0x06,0xE5,0x22,0x90,0x06,0x28,
0xF0,0xFC,0xA3,0xEF,0xF0,0xFD,0x7F,0xE7,
0x7E,0x13,0x12,0x06,0xE5,0x22,0x7F,0x02,
0x7E,0x66,0x12,0x06,0xE5,0x22,0xC5,0xF0,
0xF8,0xA3,0xE0,0x28,0xF0,0xC5,0xF0,0xF8,
0xE5,0x82,0x15,0x82,0x70,0x02,0x15,0x83,
0xE0,0x38,0xF0,0x22,0x75,0xF0,0x08,0x75,
0x82,0x00,0xEF,0x2F,0xFF,0xEE,0x33,0xFE,
0xCD,0x33,0xCD,0xCC,0x33,0xCC,0xC5,0x82,
0x33,0xC5,0x82,0x9B,0xED,0x9A,0xEC,0x99,
0xE5,0x82,0x98,0x40,0x0C,0xF5,0x82,0xEE,
0x9B,0xFE,0xED,0x9A,0xFD,0xEC,0x99,0xFC,
0x0F,0xD5,0xF0,0xD6,0xE4,0xCE,0xFB,0xE4,
0xCD,0xFA,0xE4,0xCC,0xF9,0xA8,0x82,0x22,
0xB8,0x00,0xC1,0xB9,0x00,0x59,0xBA,0x00,
0x2D,0xEC,0x8B,0xF0,0x84,0xCF,0xCE,0xCD,
0xFC,0xE5,0xF0,0xCB,0xF9,0x78,0x18,0xEF,
0x2F,0xFF,0xEE,0x33,0xFE,0xED,0x33,0xFD,
0xEC,0x33,0xFC,0xEB,0x33,0xFB,0x10,0xD7,
0x03,0x99,0x40,0x04,0xEB,0x99,0xFB,0x0F,
0xD8,0xE5,0xE4,0xF9,0xFA,0x22,0x78,0x18,
0xEF,0x2F,0xFF,0xEE,0x33,0xFE,0xED,0x33,
0xFD,0xEC,0x33,0xFC,0xC9,0x33,0xC9,0x10,
0xD7,0x05,0x9B,0xE9,0x9A,0x40,0x07,0xEC,
0x9B,0xFC,0xE9,0x9A,0xF9,0x0F,0xD8,0xE0,
0xE4,0xC9,0xFA,0xE4,0xCC,0xFB,0x22,0x75,
0xF0,0x10,0xEF,0x2F,0xFF,0xEE,0x33,0xFE,
0xED,0x33,0xFD,0xCC,0x33,0xCC,0xC8,0x33,
0xC8,0x10,0xD7,0x07,0x9B,0xEC,0x9A,0xE8,
0x99,0x40,0x0A,0xED,0x9B,0xFD,0xEC,0x9A,
0xFC,0xE8,0x99,0xF8,0x0F,0xD5,0xF0,0xDA,
0xE4,0xCD,0xFB,0xE4,0xCC,0xFA,0xE4,0xC8,
0xF9,0x22,0xEB,0x9F,0xF5,0xF0,0xEA,0x9E,
0x42,0xF0,0xE9,0x9D,0x42,0xF0,0xE8,0x9C,
0x45,0xF0,0x22,0xE0,0xFC,0xA3,0xE0,0xFD,
0xA3,0xE0,0xFE,0xA3,0xE0,0xFF,0x22,0xE0,
0xF8,0xA3,0xE0,0xF9,0xA3,0xE0,0xFA,0xA3,
0xE0,0xFB,0x22,0xEC,0xF0,0xA3,0xED,0xF0,
0xA3,0xEE,0xF0,0xA3,0xEF,0xF0,0x22,0x12,
0x05,0x13,0x12,0x05,0x35,0x44,0x40,0x12,
0x05,0x2A,0x7D,0x03,0x7C,0x00,0x12,0x05,
0x3E,0x12,0x06,0xE5,0x12,0x05,0x13,0x12,
0x05,0x35,0x54,0xBF,0x12,0x05,0x2A,0x7D,
0x03,0x7C,0x00,0x12,0x04,0xEB,0x7F,0x02,
0x7E,0x66,0x12,0x06,0xC1,0xEF,0x54,0xFD,
0x54,0xFE,0x12,0x05,0x4E,0x12,0x04,0xEB,
0x7F,0x02,0x7E,0x66,0x12,0x06,0xC1,0xEF,
0x44,0x02,0x44,0x01,0x12,0x05,0x4E,0x12,
0x05,0x3E,0x02,0x06,0xE5,0x7F,0x01,0x7E,
0x66,0x12,0x06,0xE5,0x7D,0xC0,0x7C,0x00,
0x7F,0x00,0x7E,0x66,0x12,0x06,0xE5,0xE4,
0xFD,0xFC,0x7F,0x01,0x7E,0x66,0x12,0x06,
0xE5,0x7D,0x80,0x7C,0x00,0x7F,0x00,0x7E,
0x66,0x12,0x06,0xE5,0x22,0x7D,0x03,0x7C,
0x00,0x7F,0x01,0x7E,0x66,0x12,0x06,0xE5,
0x7D,0x80,0x7C,0x00,0x7F,0x00,0x7E,0x66,
0x12,0x06,0xE5,0x22,0xFD,0xAC,0x06,0x7F,
0x02,0x7E,0x66,0x12,0x06,0xE5,0x22,0x7F,
0x02,0x7E,0x66,0x12,0x06,0xC1,0xEF,0x22,
0x7F,0x01,0x7E,0x66,0x12,0x06,0xE5,0x7D,
0xC0,0x7C,0x00,0x7F,0x00,0x7E,0x66,0x22,
0xFD,0xAC,0x06,0x7F,0x02,0x7E,0x66,0x12,
0x06,0xE5,0xE4,0xFD,0xFC,0x22,0x78,0x7F,
0xE4,0xF6,0xD8,0xFD,0x75,0x81,0x3C,0x02,
0x05,0xA3,0x02,0x00,0x0E,0xE4,0x93,0xA3,
0xF8,0xE4,0x93,0xA3,0x40,0x03,0xF6,0x80,
0x01,0xF2,0x08,0xDF,0xF4,0x80,0x29,0xE4,
0x93,0xA3,0xF8,0x54,0x07,0x24,0x0C,0xC8,
0xC3,0x33,0xC4,0x54,0x0F,0x44,0x20,0xC8,
0x83,0x40,0x04,0xF4,0x56,0x80,0x01,0x46,
0xF6,0xDF,0xE4,0x80,0x0B,0x01,0x02,0x04,
0x08,0x10,0x20,0x40,0x80,0x90,0x07,0x01,
0xE4,0x7E,0x01,0x93,0x60,0xBC,0xA3,0xFF,
0x54,0x3F,0x30,0xE5,0x09,0x54,0x1F,0xFE,
0xE4,0x93,0xA3,0x60,0x01,0x0E,0xCF,0x54,
0xC0,0x25,0xE0,0x60,0xA8,0x40,0xB8,0xE4,
0x93,0xA3,0xFA,0xE4,0x93,0xA3,0xF8,0xE4,
0x93,0xA3,0xC8,0xC5,0x82,0xC8,0xCA,0xC5,
0x83,0xCA,0xF0,0xA3,0xC8,0xC5,0x82,0xC8,
0xCA,0xC5,0x83,0xCA,0xDF,0xE9,0xDE,0xE7,
0x80,0xBE,0x75,0x0F,0x80,0x75,0x0E,0x7E,
0x75,0x0D,0xAA,0x75,0x0C,0x83,0xE4,0xF5,
0x10,0x75,0x0B,0xA0,0x75,0x0A,0xAC,0x75,
0x09,0xB9,0x75,0x08,0x03,0x75,0x89,0x11,
0x7B,0x60,0x7A,0x09,0xF9,0xF8,0xAF,0x0B,
0xAE,0x0A,0xAD,0x09,0xAC,0x08,0x12,0x03,
0xD6,0xAD,0x07,0xAC,0x06,0xC3,0xE4,0x9D,
0xFD,0xE4,0x9C,0xFC,0x78,0x17,0xF6,0xAF,
0x05,0xEF,0x08,0xF6,0x18,0xE6,0xF5,0x8C,
0x08,0xE6,0xF5,0x8A,0x74,0x0D,0x2D,0xFD,
0xE4,0x3C,0x18,0xF6,0xAF,0x05,0xEF,0x08,
0xF6,0x75,0x88,0x10,0x53,0x8E,0xC7,0xD2,
0xA9,0x22,0x90,0x06,0x24,0x12,0x04,0x79,
0xEF,0x24,0x01,0xFF,0xE4,0x3E,0xFE,0xE4,
0x3D,0xFD,0xE4,0x3C,0x22,0x7F,0x20,0x7E,
0x4E,0xE4,0xFD,0xFC,0x90,0x06,0x24,0x12,
0x04,0x85,0xC3,0x02,0x04,0x68,0xFC,0x90,
0x06,0x24,0x02,0x04,0x91,0x90,0x06,0x28,
0xEE,0xF0,0xA3,0xEF,0xF0,0x22,0x90,0x06,
0x28,0xFF,0xEE,0xF0,0xFC,0xA3,0xEF,0xF0,
0x22,0xC0,0xE0,0xC0,0xF0,0xC0,0x83,0xC0,
0x82,0xC0,0xD0,0x75,0xD0,0x00,0xC0,0x00,
0x78,0x17,0xE6,0xF5,0x8C,0x78,0x18,0xE6,
0xF5,0x8A,0x90,0x06,0x2E,0xE4,0x75,0xF0,
0x01,0x12,0x03,0x84,0x90,0x06,0x30,0xE4,
0x75,0xF0,0x01,0x12,0x03,0x84,0xD0,0x00,
0xD0,0xD0,0xD0,0x82,0xD0,0x83,0xD0,0xF0,
0xD0,0xE0,0x32,0xC2,0xAF,0xAD,0x07,0xAC,
0x06,0x8C,0xA2,0x8D,0xA3,0x75,0xA0,0x01,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0xAE,0xA1,0xBE,0x00,0xF0,
0xAE,0xA6,0xAF,0xA7,0xD2,0xAF,0x22,0xC2,
0xAF,0xAB,0x07,0xAA,0x06,0x8A,0xA2,0x8B,
0xA3,0x8C,0xA4,0x8D,0xA5,0x75,0xA0,0x03,
0x00,0x00,0x00,0xAA,0xA1,0xBA,0x00,0xF8,
0xD2,0xAF,0x22,0x42,0x06,0x30,0x00,0x00,
0x42,0x06,0x2E,0x00,0x00,0x00,0x12,0x07,
0x15,0x12,0x05,0xE8,0x02,0x00,0x03,0xE4,
0xF5,0x8E,0x22};

#define FIBER_AUTO_INIT_SIZE 1937
CONST_T rtksw_uint8 Fiber_auto[FIBER_AUTO_INIT_SIZE] = {
0x02,0x05,0x7E,0xE4,0xF5,0xA8,
0xD2,0xAF,0x22,0x00,0x00,0x02,0x06,0xFF,
0xE4,0x90,0x06,0x2A,0xF0,0x90,0x06,0x2D,
0xF0,0xA3,0xF0,0xA3,0xF0,0xFD,0x7C,0x01,
0x7F,0x3F,0x7E,0x1D,0x12,0x07,0x5D,0x7D,
0x40,0x12,0x03,0x77,0x80,0x08,0x12,0x06,
0xD3,0x50,0x08,0x12,0x06,0xC0,0x12,0x06,
0xE4,0x80,0xF3,0xE4,0xF5,0xA8,0xD2,0xAF,
0x7D,0x1F,0xFC,0x7F,0x49,0x7E,0x13,0x12,
0x07,0x5D,0x12,0x07,0x84,0x7D,0xFE,0x7C,
0x00,0x7F,0xAA,0x7E,0x12,0x12,0x07,0x5D,
0x7D,0xD7,0x12,0x03,0x42,0x7D,0x80,0x12,
0x02,0xDE,0x7D,0x94,0x7C,0xF9,0x12,0x03,
0x6F,0x7D,0x81,0x12,0x02,0xDE,0x7D,0xA2,
0x7C,0x31,0x12,0x03,0x6F,0x7D,0x82,0x12,
0x02,0xF3,0x7D,0x60,0x7C,0x69,0x12,0x03,
0x85,0x7D,0x83,0x12,0x02,0xF3,0x7D,0x28,
0x7C,0x97,0x12,0x03,0x85,0x7D,0x84,0x12,
0x03,0x08,0x7D,0x85,0x7C,0x9D,0x12,0x03,
0x9E,0x7D,0x23,0x12,0x03,0x08,0x7D,0x10,
0x7C,0xD8,0x12,0x03,0x9E,0x7D,0x24,0x7C,
0x04,0x12,0x03,0x5C,0x7D,0x00,0x12,0x03,
0x42,0x7D,0x2F,0x12,0x03,0x1D,0x7D,0x20,
0x7C,0x0F,0x7F,0x02,0x7E,0x66,0x12,0x07,
0x5D,0x7D,0x01,0x12,0x03,0x1D,0x7D,0x04,
0x7C,0x00,0x7F,0x01,0x7E,0x66,0x12,0x07,
0x5D,0x7D,0x80,0x7C,0x00,0x7F,0x00,0x7E,
0x66,0x12,0x07,0x5D,0x7F,0x02,0x7E,0x66,
0x12,0x07,0x39,0x12,0x06,0xEB,0x44,0x02,
0xFF,0x12,0x06,0xEB,0x44,0x04,0x12,0x06,
0xF4,0xFD,0x7F,0x02,0x7E,0x66,0x12,0x07,
0x5D,0x7D,0x04,0x7C,0x00,0x12,0x03,0x5C,
0x7D,0xB8,0x7C,0x15,0x7F,0xEB,0x7E,0x13,
0x12,0x07,0x5D,0x7D,0x07,0x7C,0x00,0x7F,
0xE7,0x7E,0x13,0x12,0x07,0x5D,0x7D,0x40,
0x7C,0x11,0x7F,0x00,0x7E,0x62,0x12,0x07,
0x5D,0x12,0x04,0xBF,0x7D,0x41,0x12,0x03,
0x77,0x80,0x08,0x12,0x06,0xD3,0x50,0x08,
0x12,0x06,0xC0,0x12,0x06,0xE4,0x80,0xF3,
0xC2,0x00,0xC2,0x01,0xD2,0xA9,0xD2,0x8C,
0x12,0x03,0x4C,0xEE,0x44,0x18,0x12,0x03,
0x8D,0xE4,0xFF,0xFE,0xFD,0x80,0x0C,0x7F,
0xD0,0x7E,0x07,0x12,0x06,0xD7,0x50,0x08,
0x12,0x06,0xC0,0x12,0x06,0xE4,0x80,0xEF,
0x7F,0x04,0x7E,0x62,0x12,0x07,0x39,0x12,
0x06,0xEB,0xEE,0x44,0x01,0xFE,0xEF,0x44,
0x80,0x12,0x06,0xF4,0xFD,0x7F,0x04,0x7E,
0x62,0x12,0x07,0x5D,0xE4,0xFF,0xFE,0xFD,
0x80,0x08,0x12,0x06,0xD3,0x50,0x08,0x12,
0x06,0xC0,0x12,0x06,0xE4,0x80,0xF3,0x12,
0x03,0x4C,0xEE,0x54,0xE7,0x12,0x03,0x8D,
0x7D,0x80,0x7C,0x67,0x7F,0x40,0x7E,0x13,
0x12,0x07,0x5D,0x7F,0x43,0x7E,0x13,0x12,
0x07,0x39,0x90,0x06,0x2E,0xEE,0xF0,0xA3,
0xEF,0xF0,0x30,0xE3,0xE3,0x12,0x03,0x32,
0x12,0x03,0x32,0x30,0xE2,0x72,0x90,0x06,
0x2D,0xE0,0x64,0x01,0x70,0x62,0x7F,0xEA,
0x7E,0x13,0x12,0x07,0x39,0x90,0x06,0x2B,
0xEE,0xF0,0xA3,0xEF,0xF0,0x54,0xEF,0xFF,
0x90,0x06,0x2B,0xEE,0xF0,0xA3,0xEF,0xF0,
0xEE,0x44,0x10,0x90,0x06,0x2B,0xF0,0xFC,
0xA3,0xEF,0xF0,0xFD,0x7F,0x16,0x7E,0x13,
0x12,0x07,0x5D,0xE4,0xFF,0xFE,0xFD,0x80,
0x0D,0xE4,0x7F,0xFF,0x7E,0x6F,0x12,0x06,
0xD8,0x50,0x08,0x12,0x06,0xC0,0x12,0x06,
0xE4,0x80,0xEE,0x90,0x06,0x2B,0xE0,0x54,
0xEF,0xFE,0xA3,0xE0,0x90,0x06,0x2B,0x12,
0x06,0xF7,0xAD,0x07,0x7F,0x16,0x7E,0x13,
0x12,0x07,0x5D,0xE4,0x90,0x06,0x2D,0xF0,
0xE4,0x90,0x06,0x2A,0xF0,0x02,0x01,0x96,
0x90,0x06,0x2A,0xE0,0x70,0x13,0x12,0x02,
0x69,0x90,0x06,0x2A,0x74,0x01,0xF0,0xE4,
0x90,0x06,0x32,0xF0,0xA3,0xF0,0x02,0x01,
0x96,0xC3,0x90,0x06,0x33,0xE0,0x94,0x64,
0x90,0x06,0x32,0xE0,0x94,0x00,0x50,0x03,
0x02,0x01,0x96,0xE4,0xF0,0xA3,0xF0,0x12,
0x02,0x69,0x90,0x06,0x2A,0x74,0x01,0xF0,
0x02,0x01,0x96,0x7F,0x56,0x7E,0x13,0x12,
0x07,0x39,0x90,0x06,0x2B,0xEE,0xF0,0xA3,
0xEF,0xF0,0x54,0xEF,0xFF,0x90,0x06,0x2B,
0xEE,0xF0,0xA3,0xEF,0xF0,0xEE,0x44,0x10,
0x90,0x06,0x2B,0xF0,0xFC,0xA3,0xEF,0xF0,
0xFD,0x7F,0x16,0x7E,0x13,0x12,0x07,0x5D,
0x90,0x06,0x2D,0x74,0x01,0xF0,0x7D,0x04,
0x7C,0x00,0x7F,0x02,0x7E,0x66,0x12,0x07,
0x5D,0x7D,0x00,0x7C,0x04,0x7F,0x01,0x7E,
0x66,0x12,0x07,0x5D,0x7D,0xC0,0x7C,0x00,
0x7F,0x00,0x7E,0x66,0x12,0x07,0x5D,0xE4,
0xFD,0xFC,0x7F,0x02,0x7E,0x66,0x12,0x07,
0x5D,0x7D,0x00,0x7C,0x04,0x7F,0x01,0x7E,
0x66,0x12,0x07,0x5D,0x7D,0xC0,0x7C,0x00,
0x7F,0x00,0x7E,0x66,0x12,0x07,0x5D,0x22,
0x7C,0x04,0x7F,0x01,0x7E,0x66,0x12,0x07,
0x5D,0x7D,0xC0,0x7C,0x00,0x7F,0x00,0x7E,
0x66,0x12,0x07,0x5D,0x22,0x7C,0x04,0x7F,
0x01,0x7E,0x66,0x12,0x07,0x5D,0x7D,0xC0,
0x7C,0x00,0x7F,0x00,0x7E,0x66,0x12,0x07,
0x5D,0x22,0x7C,0x04,0x7F,0x01,0x7E,0x66,
0x12,0x07,0x5D,0x7D,0xC0,0x7C,0x00,0x7F,
0x00,0x7E,0x66,0x12,0x07,0x5D,0x22,0x7C,
0x00,0x7F,0x01,0x7E,0x66,0x12,0x07,0x5D,
0x7D,0xC0,0x7C,0x00,0x7F,0x00,0x7E,0x66,
0x12,0x07,0x5D,0x22,0x7F,0x01,0x7E,0x62,
0x12,0x07,0x39,0x90,0x06,0x28,0xEE,0xF0,
0xA3,0xEF,0xF0,0x22,0x7C,0x04,0x7F,0x02,
0x7E,0x66,0x12,0x07,0x5D,0x22,0x7F,0xE7,
0x7E,0x13,0x12,0x07,0x39,0x90,0x06,0x28,
0xEE,0xF0,0xA3,0xEF,0xF0,0x22,0x7F,0x01,
0x7E,0x66,0x12,0x07,0x5D,0x7D,0xC0,0x7C,
0x00,0x7F,0x00,0x7E,0x66,0x12,0x07,0x5D,
0x22,0x7F,0x02,0x7E,0x66,0x12,0x07,0x5D,
0x22,0x7C,0x00,0x7F,0x36,0x7E,0x13,0x12,
0x07,0x5D,0xE4,0xFF,0xFE,0xFD,0x22,0x7F,
0x02,0x7E,0x66,0x12,0x07,0x5D,0x22,0x90,
0x06,0x28,0xF0,0xFC,0xA3,0xEF,0xF0,0xFD,
0x7F,0xE7,0x7E,0x13,0x12,0x07,0x5D,0x22,
0x7F,0x02,0x7E,0x66,0x12,0x07,0x5D,0x22,
0xC5,0xF0,0xF8,0xA3,0xE0,0x28,0xF0,0xC5,
0xF0,0xF8,0xE5,0x82,0x15,0x82,0x70,0x02,
0x15,0x83,0xE0,0x38,0xF0,0x22,0x75,0xF0,
0x08,0x75,0x82,0x00,0xEF,0x2F,0xFF,0xEE,
0x33,0xFE,0xCD,0x33,0xCD,0xCC,0x33,0xCC,
0xC5,0x82,0x33,0xC5,0x82,0x9B,0xED,0x9A,
0xEC,0x99,0xE5,0x82,0x98,0x40,0x0C,0xF5,
0x82,0xEE,0x9B,0xFE,0xED,0x9A,0xFD,0xEC,
0x99,0xFC,0x0F,0xD5,0xF0,0xD6,0xE4,0xCE,
0xFB,0xE4,0xCD,0xFA,0xE4,0xCC,0xF9,0xA8,
0x82,0x22,0xB8,0x00,0xC1,0xB9,0x00,0x59,
0xBA,0x00,0x2D,0xEC,0x8B,0xF0,0x84,0xCF,
0xCE,0xCD,0xFC,0xE5,0xF0,0xCB,0xF9,0x78,
0x18,0xEF,0x2F,0xFF,0xEE,0x33,0xFE,0xED,
0x33,0xFD,0xEC,0x33,0xFC,0xEB,0x33,0xFB,
0x10,0xD7,0x03,0x99,0x40,0x04,0xEB,0x99,
0xFB,0x0F,0xD8,0xE5,0xE4,0xF9,0xFA,0x22,
0x78,0x18,0xEF,0x2F,0xFF,0xEE,0x33,0xFE,
0xED,0x33,0xFD,0xEC,0x33,0xFC,0xC9,0x33,
0xC9,0x10,0xD7,0x05,0x9B,0xE9,0x9A,0x40,
0x07,0xEC,0x9B,0xFC,0xE9,0x9A,0xF9,0x0F,
0xD8,0xE0,0xE4,0xC9,0xFA,0xE4,0xCC,0xFB,
0x22,0x75,0xF0,0x10,0xEF,0x2F,0xFF,0xEE,
0x33,0xFE,0xED,0x33,0xFD,0xCC,0x33,0xCC,
0xC8,0x33,0xC8,0x10,0xD7,0x07,0x9B,0xEC,
0x9A,0xE8,0x99,0x40,0x0A,0xED,0x9B,0xFD,
0xEC,0x9A,0xFC,0xE8,0x99,0xF8,0x0F,0xD5,
0xF0,0xDA,0xE4,0xCD,0xFB,0xE4,0xCC,0xFA,
0xE4,0xC8,0xF9,0x22,0xEB,0x9F,0xF5,0xF0,
0xEA,0x9E,0x42,0xF0,0xE9,0x9D,0x42,0xF0,
0xE8,0x9C,0x45,0xF0,0x22,0xE0,0xFC,0xA3,
0xE0,0xFD,0xA3,0xE0,0xFE,0xA3,0xE0,0xFF,
0x22,0xE0,0xF8,0xA3,0xE0,0xF9,0xA3,0xE0,
0xFA,0xA3,0xE0,0xFB,0x22,0xEC,0xF0,0xA3,
0xED,0xF0,0xA3,0xEE,0xF0,0xA3,0xEF,0xF0,
0x22,0x12,0x05,0x35,0x12,0x05,0x57,0x44,
0x40,0x12,0x05,0x4C,0x7D,0x03,0x7C,0x00,
0x12,0x05,0x60,0x12,0x07,0x5D,0x12,0x05,
0x35,0x12,0x05,0x57,0x54,0xBF,0x12,0x05,
0x4C,0x7D,0x03,0x7C,0x00,0x12,0x05,0x0D,
0x7F,0x02,0x7E,0x66,0x12,0x07,0x39,0xEF,
0x54,0xFD,0x54,0xFE,0x12,0x05,0x70,0x12,
0x05,0x0D,0x7F,0x02,0x7E,0x66,0x12,0x07,
0x39,0xEF,0x44,0x02,0x44,0x01,0x12,0x05,
0x70,0x12,0x05,0x60,0x02,0x07,0x5D,0x7F,
0x01,0x7E,0x66,0x12,0x07,0x5D,0x7D,0xC0,
0x7C,0x00,0x7F,0x00,0x7E,0x66,0x12,0x07,
0x5D,0xE4,0xFD,0xFC,0x7F,0x01,0x7E,0x66,
0x12,0x07,0x5D,0x7D,0x80,0x7C,0x00,0x7F,
0x00,0x7E,0x66,0x12,0x07,0x5D,0x22,0x7D,
0x03,0x7C,0x00,0x7F,0x01,0x7E,0x66,0x12,
0x07,0x5D,0x7D,0x80,0x7C,0x00,0x7F,0x00,
0x7E,0x66,0x12,0x07,0x5D,0x22,0xFD,0xAC,
0x06,0x7F,0x02,0x7E,0x66,0x12,0x07,0x5D,
0x22,0x7F,0x02,0x7E,0x66,0x12,0x07,0x39,
0xEF,0x22,0x7F,0x01,0x7E,0x66,0x12,0x07,
0x5D,0x7D,0xC0,0x7C,0x00,0x7F,0x00,0x7E,
0x66,0x22,0xFD,0xAC,0x06,0x7F,0x02,0x7E,
0x66,0x12,0x07,0x5D,0xE4,0xFD,0xFC,0x22,
0x78,0x7F,0xE4,0xF6,0xD8,0xFD,0x75,0x81,
0x3C,0x02,0x05,0xC5,0x02,0x00,0x0E,0xE4,
0x93,0xA3,0xF8,0xE4,0x93,0xA3,0x40,0x03,
0xF6,0x80,0x01,0xF2,0x08,0xDF,0xF4,0x80,
0x29,0xE4,0x93,0xA3,0xF8,0x54,0x07,0x24,
0x0C,0xC8,0xC3,0x33,0xC4,0x54,0x0F,0x44,
0x20,0xC8,0x83,0x40,0x04,0xF4,0x56,0x80,
0x01,0x46,0xF6,0xDF,0xE4,0x80,0x0B,0x01,
0x02,0x04,0x08,0x10,0x20,0x40,0x80,0x90,
0x07,0x79,0xE4,0x7E,0x01,0x93,0x60,0xBC,
0xA3,0xFF,0x54,0x3F,0x30,0xE5,0x09,0x54,
0x1F,0xFE,0xE4,0x93,0xA3,0x60,0x01,0x0E,
0xCF,0x54,0xC0,0x25,0xE0,0x60,0xA8,0x40,
0xB8,0xE4,0x93,0xA3,0xFA,0xE4,0x93,0xA3,
0xF8,0xE4,0x93,0xA3,0xC8,0xC5,0x82,0xC8,
0xCA,0xC5,0x83,0xCA,0xF0,0xA3,0xC8,0xC5,
0x82,0xC8,0xCA,0xC5,0x83,0xCA,0xDF,0xE9,
0xDE,0xE7,0x80,0xBE,0x75,0x0F,0x80,0x75,
0x0E,0x7E,0x75,0x0D,0xAA,0x75,0x0C,0x83,
0xE4,0xF5,0x10,0x75,0x0B,0xA0,0x75,0x0A,
0xAC,0x75,0x09,0xB9,0x75,0x08,0x03,0x75,
0x89,0x11,0x7B,0x60,0x7A,0x09,0xF9,0xF8,
0xAF,0x0B,0xAE,0x0A,0xAD,0x09,0xAC,0x08,
0x12,0x03,0xF8,0xAD,0x07,0xAC,0x06,0xC3,
0xE4,0x9D,0xFD,0xE4,0x9C,0xFC,0x78,0x17,
0xF6,0xAF,0x05,0xEF,0x08,0xF6,0x18,0xE6,
0xF5,0x8C,0x08,0xE6,0xF5,0x8A,0x74,0x0D,
0x2D,0xFD,0xE4,0x3C,0x18,0xF6,0xAF,0x05,
0xEF,0x08,0xF6,0x75,0x88,0x10,0x53,0x8E,
0xC7,0xD2,0xA9,0x22,0x7D,0x69,0x7C,0x0A,
0x7F,0x15,0x7E,0x1D,0x12,0x07,0x5D,0x7F,
0x00,0x12,0x06,0x98,0x74,0x20,0xFF,0xFE,
0x12,0x06,0xB1,0x7F,0x40,0x12,0x06,0x98,
0x7F,0x60,0x7E,0x20,0x12,0x06,0xB1,0x7D,
0x40,0x7C,0x13,0x7F,0x80,0x7E,0x20,0x02,
0x07,0x5D,0x7D,0x40,0x7C,0x13,0x7E,0x20,
0x12,0x07,0x5D,0x7D,0x69,0x7C,0x0A,0x7F,
0x15,0x7E,0x1D,0x12,0x07,0x5D,0x7D,0x40,
0x7C,0x13,0x22,0x12,0x07,0x5D,0x7D,0x69,
0x7C,0x0A,0x7F,0x15,0x7E,0x1D,0x12,0x07,
0x5D,0x22,0x90,0x06,0x24,0x12,0x04,0x9B,
0xEF,0x24,0x01,0xFF,0xE4,0x3E,0xFE,0xE4,
0x3D,0xFD,0xE4,0x3C,0x22,0x7F,0x20,0x7E,
0x4E,0xE4,0xFD,0xFC,0x90,0x06,0x24,0x12,
0x04,0xA7,0xC3,0x02,0x04,0x8A,0xFC,0x90,
0x06,0x24,0x02,0x04,0xB3,0x90,0x06,0x28,
0xEE,0xF0,0xA3,0xEF,0xF0,0x22,0x90,0x06,
0x28,0xFF,0xEE,0xF0,0xFC,0xA3,0xEF,0xF0,
0x22,0xC0,0xE0,0xC0,0xF0,0xC0,0x83,0xC0,
0x82,0xC0,0xD0,0x75,0xD0,0x00,0xC0,0x00,
0x78,0x17,0xE6,0xF5,0x8C,0x78,0x18,0xE6,
0xF5,0x8A,0x90,0x06,0x30,0xE4,0x75,0xF0,
0x01,0x12,0x03,0xA6,0x90,0x06,0x32,0xE4,
0x75,0xF0,0x01,0x12,0x03,0xA6,0xD0,0x00,
0xD0,0xD0,0xD0,0x82,0xD0,0x83,0xD0,0xF0,
0xD0,0xE0,0x32,0xC2,0xAF,0xAD,0x07,0xAC,
0x06,0x8C,0xA2,0x8D,0xA3,0x75,0xA0,0x01,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0xAE,0xA1,0xBE,0x00,0xF0,
0xAE,0xA6,0xAF,0xA7,0xD2,0xAF,0x22,0xC2,
0xAF,0xAB,0x07,0xAA,0x06,0x8A,0xA2,0x8B,
0xA3,0x8C,0xA4,0x8D,0xA5,0x75,0xA0,0x03,
0x00,0x00,0x00,0xAA,0xA1,0xBA,0x00,0xF8,
0xD2,0xAF,0x22,0x42,0x06,0x32,0x00,0x00,
0x42,0x06,0x30,0x00,0x00,0x00,0x12,0x07,
0x8D,0x12,0x06,0x0A,0x02,0x00,0x03,0xE4,
0xF5,0x8E,0x22};


static rtksw_api_ret_t _dal_rtl8367c_port_FiberModeAbility_set(rtksw_uint32 unit, rtksw_port_t port, rtksw_port_phy_ability_t *pAbility)
{
    rtksw_api_ret_t   retVal;
    rtksw_uint32      regData;

    /* Check Combo port or not */
    RTKSW_CHK_PORT_IS_COMBO(unit, port);

    if (pAbility->Full_2P5G == 1)
        return RT_ERR_PHY_SPEED;

    /* Flow Control */
    if ((retVal = rtl8367c_getAsicReg(unit, RTL8367C_REG_FIB0_CFG04, &regData)) != RT_ERR_OK)
        return retVal;

    if (pAbility->AsyFC == 1)
        regData |= (0x0001 << 8);
    else
        regData &= ~(0x0001 << 8);

    if (pAbility->FC == 1)
        regData |= (0x0001 << 7);
    else
        regData &= ~(0x0001 << 7);

    if ((retVal = rtl8367c_setAsicReg(unit, RTL8367C_REG_FIB0_CFG04, regData)) != RT_ERR_OK)
        return retVal;

    /* Speed ability */
    if( (pAbility->Full_1000 == 1) && (pAbility->Full_100 == 1) && (pAbility->AutoNegotiation == 1) )
    {
        if ((retVal = rtl8367c_setAsicRegBit(unit, RTL8367C_REG_FIBER_CFG_1, RTL8367C_SDS_FRC_MODE_OFFSET, 0)) != RT_ERR_OK)
            return retVal;

        if ((retVal = rtl8367c_setAsicRegBits(unit, RTL8367C_REG_FIBER_CFG_1, RTL8367C_SDS_MODE_MASK, 7)) != RT_ERR_OK)
            return retVal;

        if ((retVal = rtl8367c_setAsicReg(unit, RTL8367C_REG_FIB0_CFG00, 0x1140)) != RT_ERR_OK)
            return retVal;
    }
    else if(pAbility->Full_1000 == 1)
    {
        if ((retVal = rtl8367c_setAsicRegBit(unit, RTL8367C_REG_FIBER_CFG_1, RTL8367C_SDS_FRC_MODE_OFFSET, 1)) != RT_ERR_OK)
            return retVal;

        if ((retVal = rtl8367c_setAsicRegBits(unit, RTL8367C_REG_FIBER_CFG_1, RTL8367C_SDS_MODE_MASK, 4)) != RT_ERR_OK)
            return retVal;

        if(pAbility->AutoNegotiation == 1)
        {
            if ((retVal = rtl8367c_setAsicReg(unit, RTL8367C_REG_FIB0_CFG00, 0x1140)) != RT_ERR_OK)
                return retVal;
        }
        else
        {
            if ((retVal = rtl8367c_setAsicReg(unit, RTL8367C_REG_FIB0_CFG00, 0x0140)) != RT_ERR_OK)
                return retVal;
        }
    }
    else if(pAbility->Full_100 == 1)
    {
        if ((retVal = rtl8367c_setAsicRegBit(unit, RTL8367C_REG_FIBER_CFG_1, RTL8367C_SDS_FRC_MODE_OFFSET, 1)) != RT_ERR_OK)
            return retVal;

        if ((retVal = rtl8367c_setAsicRegBits(unit, RTL8367C_REG_FIBER_CFG_1, RTL8367C_SDS_MODE_MASK, 5)) != RT_ERR_OK)
            return retVal;

        if ((retVal = rtl8367c_setAsicReg(unit, RTL8367C_REG_FIB0_CFG00, 0x2100)) != RT_ERR_OK)
            return retVal;
    }

    /* Digital software reset */
    if ((retVal = rtl8367c_setAsicReg(unit, RTL8367C_REG_SDS_INDACS_ADR, 0x0003)) != RT_ERR_OK)
        return retVal;

    if ((retVal = rtl8367c_setAsicReg(unit, RTL8367C_REG_SDS_INDACS_CMD, 0x0080)) != RT_ERR_OK)
        return retVal;

    if ((retVal = rtl8367c_getAsicReg(unit, RTL8367C_REG_SDS_INDACS_DATA, &regData)) != RT_ERR_OK)
        return retVal;

    regData |= (0x0001 << 6);

    if ((retVal = rtl8367c_setAsicReg(unit, RTL8367C_REG_SDS_INDACS_DATA, regData)) != RT_ERR_OK)
        return retVal;

    if ((retVal = rtl8367c_setAsicReg(unit, RTL8367C_REG_SDS_INDACS_ADR, 0x0003)) != RT_ERR_OK)
        return retVal;

    if ((retVal = rtl8367c_setAsicReg(unit, RTL8367C_REG_SDS_INDACS_CMD, 0x00C0)) != RT_ERR_OK)
        return retVal;

    regData &= ~(0x0001 << 6);

    if ((retVal = rtl8367c_setAsicReg(unit, RTL8367C_REG_SDS_INDACS_DATA, regData)) != RT_ERR_OK)
        return retVal;

    if ((retVal = rtl8367c_setAsicReg(unit, RTL8367C_REG_SDS_INDACS_ADR, 0x0003)) != RT_ERR_OK)
        return retVal;

    if ((retVal = rtl8367c_setAsicReg(unit, RTL8367C_REG_SDS_INDACS_CMD, 0x00C0)) != RT_ERR_OK)
        return retVal;

    /* CDR reset */
    if ((retVal = rtl8367c_setAsicReg(unit, RTL8367C_REG_SDS_INDACS_DATA, 0x1401))!=RT_ERR_OK)
        return retVal;

    if ((retVal = rtl8367c_setAsicReg(unit, RTL8367C_REG_SDS_INDACS_ADR, 0x0000))!=RT_ERR_OK)
        return retVal;

    if ((retVal = rtl8367c_setAsicReg(unit, RTL8367C_REG_SDS_INDACS_CMD, 0x00C0))!=RT_ERR_OK)
        return retVal;

    if ((retVal = rtl8367c_setAsicReg(unit, RTL8367C_REG_SDS_INDACS_DATA, 0x1403))!=RT_ERR_OK)
        return retVal;

    if ((retVal = rtl8367c_setAsicReg(unit, RTL8367C_REG_SDS_INDACS_ADR, 0x0000))!=RT_ERR_OK)
        return retVal;

    if ((retVal = rtl8367c_setAsicReg(unit, RTL8367C_REG_SDS_INDACS_CMD, 0x00C0))!=RT_ERR_OK)
        return retVal;

    return RT_ERR_OK;
}

static rtksw_api_ret_t _dal_rtl8367c_port_FiberModeAbility_get(rtksw_uint32 unit, rtksw_port_t port, rtksw_port_phy_ability_t *pAbility)
{
    rtksw_api_ret_t   retVal;
    rtksw_uint32      data, regData;

    /* Check Combo port or not */
    RTKSW_CHK_PORT_IS_COMBO(unit, port);

    osal_memset(pAbility, 0x00, sizeof(rtksw_port_phy_ability_t));

    /* Flow Control */
    if ((retVal = rtl8367c_setAsicRegBit(unit, RTL8367C_REG_FIBER_CFG_1, RTL8367C_SDS_FRC_REG4_OFFSET, 1)) != RT_ERR_OK)
        return retVal;

    if ((retVal = rtl8367c_setAsicRegBit(unit, RTL8367C_REG_FIBER_CFG_1, RTL8367C_SDS_FRC_REG4_FIB100_OFFSET, 0)) != RT_ERR_OK)
        return retVal;

    if ((retVal = rtl8367c_setAsicReg(unit, RTL8367C_REG_SDS_INDACS_ADR, 0x0044)) != RT_ERR_OK)
        return retVal;

    if ((retVal = rtl8367c_setAsicReg(unit, RTL8367C_REG_SDS_INDACS_CMD, 0x0080)) != RT_ERR_OK)
        return retVal;

    if ((retVal = rtl8367c_getAsicReg(unit, RTL8367C_REG_SDS_INDACS_DATA, &regData)) != RT_ERR_OK)
        return retVal;

    if(regData & (0x0001 << 8))
        pAbility->AsyFC = 1;

    if(regData & (0x0001 << 7))
        pAbility->FC = 1;

    /* Speed ability */
    if ((retVal = rtl8367c_getAsicRegBit(unit, RTL8367C_REG_FIBER_CFG_1, RTL8367C_SDS_FRC_MODE_OFFSET, &data)) != RT_ERR_OK)
            return retVal;

    if(data == 0)
    {
        pAbility->AutoNegotiation = 1;
        pAbility->Full_1000 = 1;
        pAbility->Full_100 = 1;
    }
    else
    {
        if ((retVal = rtl8367c_getAsicRegBits(unit, RTL8367C_REG_FIBER_CFG_1, RTL8367C_SDS_MODE_MASK, &data)) != RT_ERR_OK)
            return retVal;

        if(data == 4)
        {
            pAbility->Full_1000 = 1;

            if ((retVal = rtl8367c_getAsicReg(unit, RTL8367C_REG_FIB0_CFG00, &data)) != RT_ERR_OK)
                return retVal;

            if(data & 0x1000)
                pAbility->AutoNegotiation = 1;
            else
                pAbility->AutoNegotiation = 0;
        }
        else if(data == 5)
            pAbility->Full_100 = 1;
        else
            return RT_ERR_FAILED;
    }

    return RT_ERR_OK;
}

static rtksw_api_ret_t _dal_rtl8367c_port_phyComboPortMedia_get(rtksw_uint32 unit, rtksw_port_t port, rtksw_port_media_t *pMedia)
{
    rtksw_api_ret_t   retVal;
    rtksw_uint32      regData;
    rtksw_uint32      data;

    /* Check initialization state */
    RTKSW_CHK_INIT_STATE(unit);

    /* Check Port Valid */
    RTKSW_CHK_PORT_IS_UTP(unit, port);

    /* Check Combo Port ID */
    RTKSW_CHK_PORT_IS_COMBO(unit, port);

    if((retVal = rtl8367c_setAsicReg(unit, 0x13C2, 0x0249)) != RT_ERR_OK)
        return retVal;

    if((retVal = rtl8367c_getAsicReg(unit, 0x1300, &regData)) != RT_ERR_OK)
        return retVal;

    if((retVal = rtl8367c_setAsicReg(unit, 0x13C2, 0x0000)) != RT_ERR_OK)
        return retVal;

    if(regData != 0x6367)
    {
        *pMedia = RTKSW_PORT_MEDIA_COPPER;
    }
    else
    {
        if ((retVal = rtl8367c_getAsicRegBit(unit, RTL8367C_REG_UTP_FIB_DET, RTL8367C_UTP_FIB_DISAUTODET_OFFSET, &data))!=RT_ERR_OK)
                return retVal;
        if(data == 0)
        {
            *pMedia = RTKSW_PORT_MEDIA_AUTO;
        }
        else
        {
            if ((retVal = rtl8367c_getAsicRegBit(unit, RTL8367C_REG_UTP_FIB_DET, RTL8367C_UTP_FIRST_OFFSET, &data))!=RT_ERR_OK)
                    return retVal;

            if(data == 1)
                *pMedia = RTKSW_PORT_MEDIA_COPPER;
            else
                *pMedia = RTKSW_PORT_MEDIA_FIBER;
        }
    }

    return RT_ERR_OK;
}

/* Function Name:
 *      dal_rtl8367c_port_phyAutoNegoAbility_set
 * Description:
 *      Set ethernet PHY auto-negotiation desired ability.
 * Input:
 *      unit        - Unit ID
 *      port        - port id.
 *      pAbility    - Ability structure
 * Output:
 *      None
 * Return:
 *      RT_ERR_OK               - OK
 *      RT_ERR_FAILED           - Failed
 *      RT_ERR_SMI              - SMI access error
 *      RT_ERR_PORT_ID          - Invalid port number.
 *      RT_ERR_PHY_REG_ID       - Invalid PHY address
 *      RT_ERR_INPUT            - Invalid input parameters.
 *      RT_ERR_BUSYWAIT_TIMEOUT - PHY access busy
 * Note:
 *      If Full_1000 bit is set to 1, the AutoNegotiation will be automatic set to 1. While both AutoNegotiation and Full_1000 are set to 0, the PHY speed and duplex selection will
 *      be set as following 100F > 100H > 10F > 10H priority sequence.
 */
rtksw_api_ret_t dal_rtl8367c_port_phyAutoNegoAbility_set(rtksw_uint32 unit, rtksw_port_t port, rtksw_port_phy_ability_t *pAbility)
{
    rtksw_api_ret_t       retVal;
    rtksw_uint32          phyData;
    rtksw_uint32          phyEnMsk0;
    rtksw_uint32          phyEnMsk4;
    rtksw_uint32          phyEnMsk9;
    rtksw_port_media_t    media_type;

    /* Check initialization state */
    RTKSW_CHK_INIT_STATE(unit);

    /* Speed Check */
    if (pAbility->Full_2P5G == 1)
        return RT_ERR_PHY_SPEED;

    /* Check Port Valid */
    RTKSW_CHK_PORT_IS_UTP(unit, port);

    if(NULL == pAbility)
        return RT_ERR_NULL_POINTER;

    if (pAbility->Half_10 >= RTKSW_ENABLE_END || pAbility->Full_10 >= RTKSW_ENABLE_END ||
       pAbility->Half_100 >= RTKSW_ENABLE_END || pAbility->Full_100 >= RTKSW_ENABLE_END ||
       pAbility->Full_1000 >= RTKSW_ENABLE_END || pAbility->AutoNegotiation >= RTKSW_ENABLE_END ||
       pAbility->AsyFC >= RTKSW_ENABLE_END || pAbility->FC >= RTKSW_ENABLE_END)
        return RT_ERR_INPUT;

    if (rtksw_switch_isComboPort(unit, port) == RT_ERR_OK)
    {
        if ((retVal = _dal_rtl8367c_port_phyComboPortMedia_get(unit, port, &media_type)) != RT_ERR_OK)
            return retVal;

        if(media_type == RTKSW_PORT_MEDIA_FIBER)
        {
            return _dal_rtl8367c_port_FiberModeAbility_set(unit, port, pAbility);
        }
    }

    /*for PHY auto mode setup*/
    pAbility->AutoNegotiation = 1;

    phyEnMsk0 = 0;
    phyEnMsk4 = 0;
    phyEnMsk9 = 0;

    if (1 == pAbility->Half_10)
    {
        /*10BASE-TX half duplex capable in reg 4.5*/
        phyEnMsk4 = phyEnMsk4 | (1 << 5);

        /*Speed selection [1:0] */
        /* 11=Reserved*/
        /* 10= 1000Mpbs*/
        /* 01= 100Mpbs*/
        /* 00= 10Mpbs*/
        phyEnMsk0 = phyEnMsk0 & (~(1 << 6));
        phyEnMsk0 = phyEnMsk0 & (~(1 << 13));
    }

    if (1 == pAbility->Full_10)
    {
        /*10BASE-TX full duplex capable in reg 4.6*/
        phyEnMsk4 = phyEnMsk4 | (1 << 6);
        /*Speed selection [1:0] */
        /* 11=Reserved*/
        /* 10= 1000Mpbs*/
        /* 01= 100Mpbs*/
        /* 00= 10Mpbs*/
        phyEnMsk0 = phyEnMsk0 & (~(1 << 6));
        phyEnMsk0 = phyEnMsk0 & (~(1 << 13));

        /*Full duplex mode in reg 0.8*/
        phyEnMsk0 = phyEnMsk0 | (1 << 8);

    }

    if (1 == pAbility->Half_100)
    {
        /*100BASE-TX half duplex capable in reg 4.7*/
        phyEnMsk4 = phyEnMsk4 | (1 << 7);
        /*Speed selection [1:0] */
        /* 11=Reserved*/
        /* 10= 1000Mpbs*/
        /* 01= 100Mpbs*/
        /* 00= 10Mpbs*/
        phyEnMsk0 = phyEnMsk0 & (~(1 << 6));
        phyEnMsk0 = phyEnMsk0 | (1 << 13);
    }


    if (1 == pAbility->Full_100)
    {
        /*100BASE-TX full duplex capable in reg 4.8*/
        phyEnMsk4 = phyEnMsk4 | (1 << 8);
        /*Speed selection [1:0] */
        /* 11=Reserved*/
        /* 10= 1000Mpbs*/
        /* 01= 100Mpbs*/
        /* 00= 10Mpbs*/
        phyEnMsk0 = phyEnMsk0 & (~(1 << 6));
        phyEnMsk0 = phyEnMsk0 | (1 << 13);
        /*Full duplex mode in reg 0.8*/
        phyEnMsk0 = phyEnMsk0 | (1 << 8);
    }


    if (1 == pAbility->Full_1000)
    {
        /*1000 BASE-T FULL duplex capable setting in reg 9.9*/
        phyEnMsk9 = phyEnMsk9 | (1 << 9);

        /*Speed selection [1:0] */
        /* 11=Reserved*/
        /* 10= 1000Mpbs*/
        /* 01= 100Mpbs*/
        /* 00= 10Mpbs*/
        phyEnMsk0 = phyEnMsk0 | (1 << 6);
        phyEnMsk0 = phyEnMsk0 & (~(1 << 13));


        /*Auto-Negotiation setting in reg 0.12*/
        phyEnMsk0 = phyEnMsk0 | (1 << 12);

     }

    if (1 == pAbility->AutoNegotiation)
    {
        /*Auto-Negotiation setting in reg 0.12*/
        phyEnMsk0 = phyEnMsk0 | (1 << 12);
    }

    if (1 == pAbility->AsyFC)
    {
        /*Asymetric flow control in reg 4.11*/
        phyEnMsk4 = phyEnMsk4 | (1 << 11);
    }
    if (1 == pAbility->FC)
    {
        /*Flow control in reg 4.10*/
        phyEnMsk4 = phyEnMsk4 | (1 << 10);
    }

    /*1000 BASE-T control register setting*/
    if ((retVal = rtl8367c_getAsicPHYReg(unit, rtksw_switch_port_L2P_get(unit, port), PHY_1000_BASET_CONTROL_REG, &phyData)) != RT_ERR_OK)
        return retVal;

    phyData = (phyData & (~0x0200)) | phyEnMsk9 ;

    if ((retVal = rtl8367c_setAsicPHYReg(unit, rtksw_switch_port_L2P_get(unit, port), PHY_1000_BASET_CONTROL_REG, phyData)) != RT_ERR_OK)
        return retVal;

    /*Auto-Negotiation control register setting*/
    if ((retVal = rtl8367c_getAsicPHYReg(unit, rtksw_switch_port_L2P_get(unit, port), PHY_AN_ADVERTISEMENT_REG, &phyData)) != RT_ERR_OK)
        return retVal;

    phyData = (phyData & (~0x0DE0)) | phyEnMsk4;
    if ((retVal = rtl8367c_setAsicPHYReg(unit, rtksw_switch_port_L2P_get(unit, port), PHY_AN_ADVERTISEMENT_REG, phyData)) != RT_ERR_OK)
        return retVal;

    /*Control register setting and restart auto*/
    if ((retVal = rtl8367c_getAsicPHYReg(unit, rtksw_switch_port_L2P_get(unit, port), PHY_CONTROL_REG, &phyData)) != RT_ERR_OK)
        return retVal;

    phyData = (phyData & (~0x3140)) | phyEnMsk0;
    /*If have auto-negotiation capable, then restart auto negotiation*/
    if (1 == pAbility->AutoNegotiation)
    {
        phyData = phyData | (1 << 9);
    }

    if ((retVal = rtl8367c_setAsicPHYReg(unit, rtksw_switch_port_L2P_get(unit, port), PHY_CONTROL_REG, phyData)) != RT_ERR_OK)
        return retVal;

    return RT_ERR_OK;
}

/* Function Name:
 *      dal_rtl8367c_port_phyAutoNegoAbility_get
 * Description:
 *      Get PHY ability through PHY registers.
 * Input:
 *      unit    - Unit ID
 *      port    - Port id.
 * Output:
 *      pAbility - Ability structure
 * Return:
 *      RT_ERR_OK               - OK
 *      RT_ERR_FAILED           - Failed
 *      RT_ERR_SMI              - SMI access error
 *      RT_ERR_PORT_ID          - Invalid port number.
 *      RT_ERR_PHY_REG_ID       - Invalid PHY address
 *      RT_ERR_INPUT            - Invalid input parameters.
 *      RT_ERR_BUSYWAIT_TIMEOUT - PHY access busy
 * Note:
 *      Get the capablity of specified PHY.
 */
rtksw_api_ret_t dal_rtl8367c_port_phyAutoNegoAbility_get(rtksw_uint32 unit, rtksw_port_t port, rtksw_port_phy_ability_t *pAbility)
{
    rtksw_api_ret_t       retVal;
    rtksw_uint32          phyData0;
    rtksw_uint32          phyData4;
    rtksw_uint32          phyData9;
    rtksw_port_media_t    media_type;

    /* Check initialization state */
    RTKSW_CHK_INIT_STATE(unit);

    /* Check Port Valid */
    RTKSW_CHK_PORT_IS_UTP(unit, port);

    if(NULL == pAbility)
        return RT_ERR_NULL_POINTER;

    if (rtksw_switch_isComboPort(unit, port) == RT_ERR_OK)
    {
        if ((retVal = _dal_rtl8367c_port_phyComboPortMedia_get(unit, port, &media_type)) != RT_ERR_OK)
            return retVal;

        if(media_type == RTKSW_PORT_MEDIA_FIBER)
        {
            return _dal_rtl8367c_port_FiberModeAbility_get(unit, port, pAbility);
        }
    }

    /*Control register setting and restart auto*/
    if ((retVal = rtl8367c_getAsicPHYReg(unit,rtksw_switch_port_L2P_get(unit, port), PHY_CONTROL_REG, &phyData0)) != RT_ERR_OK)
        return retVal;

    /*Auto-Negotiation control register setting*/
    if ((retVal = rtl8367c_getAsicPHYReg(unit,rtksw_switch_port_L2P_get(unit, port), PHY_AN_ADVERTISEMENT_REG, &phyData4)) != RT_ERR_OK)
        return retVal;

    /*1000 BASE-T control register setting*/
    if ((retVal = rtl8367c_getAsicPHYReg(unit,rtksw_switch_port_L2P_get(unit, port), PHY_1000_BASET_CONTROL_REG, &phyData9)) != RT_ERR_OK)
        return retVal;

    osal_memset(pAbility, 0x00, sizeof(rtksw_port_phy_ability_t));

    if (phyData9 & (1 << 9))
        pAbility->Full_1000 = 1;
    else
        pAbility->Full_1000 = 0;

    if (phyData4 & (1 << 11))
        pAbility->AsyFC = 1;
    else
        pAbility->AsyFC = 0;

    if (phyData4 & (1 << 10))
        pAbility->FC = 1;
    else
        pAbility->FC = 0;


    if (phyData4 & (1 << 8))
        pAbility->Full_100 = 1;
    else
        pAbility->Full_100 = 0;

    if (phyData4 & (1 << 7))
        pAbility->Half_100 = 1;
    else
        pAbility->Half_100 = 0;

    if (phyData4 & (1 << 6))
        pAbility->Full_10 = 1;
    else
        pAbility->Full_10 = 0;

    if (phyData4 & (1 << 5))
        pAbility->Half_10 = 1;
    else
        pAbility->Half_10 = 0;


    if (phyData0 & (1 << 12))
        pAbility->AutoNegotiation = 1;
    else
        pAbility->AutoNegotiation = 0;

    return RT_ERR_OK;
}

/* Function Name:
 *      dal_rtl8367c_port_phyForceModeAbility_set
 * Description:
 *      Set the port speed/duplex mode/pause/asy_pause in the PHY force mode.
 * Input:
 *      unit        - Unit ID
 *      port        - port id.
 *      pAbility    - Ability structure
 * Output:
 *      None
 * Return:
 *      RT_ERR_OK               - OK
 *      RT_ERR_FAILED           - Failed
 *      RT_ERR_SMI              - SMI access error
 *      RT_ERR_PORT_ID          - Invalid port number.
 *      RT_ERR_PHY_REG_ID       - Invalid PHY address
 *      RT_ERR_INPUT            - Invalid input parameters.
 *      RT_ERR_BUSYWAIT_TIMEOUT - PHY access busy
 * Note:
 *      While both AutoNegotiation and Full_1000 are set to 0, the PHY speed and duplex selection will
 *      be set as following 100F > 100H > 10F > 10H priority sequence.
 *      This API can be used to configure combo port in fiber mode.
 *      The possible parameters in fiber mode are Full_1000 and Full 100.
 *      All the other fields in rtksw_port_phy_ability_t will be ignored in fiber port.
 */
rtksw_api_ret_t dal_rtl8367c_port_phyForceModeAbility_set(rtksw_uint32 unit, rtksw_port_t port, rtksw_port_phy_ability_t *pAbility)
{
     rtksw_api_ret_t      retVal;
     rtksw_uint32         phyData;
     rtksw_uint32         phyEnMsk0;
     rtksw_uint32         phyEnMsk4;
     rtksw_uint32         phyEnMsk9;
     rtksw_port_media_t   media_type;

     /* Check initialization state */
     RTKSW_CHK_INIT_STATE(unit);

     /* Speed Check */
    if (pAbility->Full_2P5G == 1)
        return RT_ERR_PHY_SPEED;

     /* Check Port Valid */
     RTKSW_CHK_PORT_IS_UTP(unit, port);

     if(NULL == pAbility)
        return RT_ERR_NULL_POINTER;

     if (pAbility->Half_10 >= RTKSW_ENABLE_END || pAbility->Full_10 >= RTKSW_ENABLE_END ||
        pAbility->Half_100 >= RTKSW_ENABLE_END || pAbility->Full_100 >= RTKSW_ENABLE_END ||
        pAbility->Full_1000 >= RTKSW_ENABLE_END || pAbility->AutoNegotiation >= RTKSW_ENABLE_END ||
        pAbility->AsyFC >= RTKSW_ENABLE_END || pAbility->FC >= RTKSW_ENABLE_END)
         return RT_ERR_INPUT;

     if (rtksw_switch_isComboPort(unit, port) == RT_ERR_OK)
     {
         if ((retVal = _dal_rtl8367c_port_phyComboPortMedia_get(unit,port, &media_type)) != RT_ERR_OK)
             return retVal;

         if(media_type == RTKSW_PORT_MEDIA_FIBER)
         {
             return _dal_rtl8367c_port_FiberModeAbility_set(unit, port, pAbility);
         }
     }

     if (1 == pAbility->Full_1000)
         return RT_ERR_INPUT;

     /*for PHY force mode setup*/
     pAbility->AutoNegotiation = 0;

     phyEnMsk0 = 0;
     phyEnMsk4 = 0;
     phyEnMsk9 = 0;

     if (1 == pAbility->Half_10)
     {
         /*10BASE-TX half duplex capable in reg 4.5*/
         phyEnMsk4 = phyEnMsk4 | (1 << 5);

         /*Speed selection [1:0] */
         /* 11=Reserved*/
         /* 10= 1000Mpbs*/
         /* 01= 100Mpbs*/
         /* 00= 10Mpbs*/
         phyEnMsk0 = phyEnMsk0 & (~(1 << 6));
         phyEnMsk0 = phyEnMsk0 & (~(1 << 13));
     }

     if (1 == pAbility->Full_10)
     {
         /*10BASE-TX full duplex capable in reg 4.6*/
         phyEnMsk4 = phyEnMsk4 | (1 << 6);
         /*Speed selection [1:0] */
         /* 11=Reserved*/
         /* 10= 1000Mpbs*/
         /* 01= 100Mpbs*/
         /* 00= 10Mpbs*/
         phyEnMsk0 = phyEnMsk0 & (~(1 << 6));
         phyEnMsk0 = phyEnMsk0 & (~(1 << 13));

         /*Full duplex mode in reg 0.8*/
         phyEnMsk0 = phyEnMsk0 | (1 << 8);

     }

     if (1 == pAbility->Half_100)
     {
         /*100BASE-TX half duplex capable in reg 4.7*/
         phyEnMsk4 = phyEnMsk4 | (1 << 7);
         /*Speed selection [1:0] */
         /* 11=Reserved*/
         /* 10= 1000Mpbs*/
         /* 01= 100Mpbs*/
         /* 00= 10Mpbs*/
         phyEnMsk0 = phyEnMsk0 & (~(1 << 6));
         phyEnMsk0 = phyEnMsk0 | (1 << 13);
     }


     if (1 == pAbility->Full_100)
     {
         /*100BASE-TX full duplex capable in reg 4.8*/
         phyEnMsk4 = phyEnMsk4 | (1 << 8);
         /*Speed selection [1:0] */
         /* 11=Reserved*/
         /* 10= 1000Mpbs*/
         /* 01= 100Mpbs*/
         /* 00= 10Mpbs*/
         phyEnMsk0 = phyEnMsk0 & (~(1 << 6));
         phyEnMsk0 = phyEnMsk0 | (1 << 13);
         /*Full duplex mode in reg 0.8*/
         phyEnMsk0 = phyEnMsk0 | (1 << 8);
     }

     if (1 == pAbility->AsyFC)
     {
         /*Asymetric flow control in reg 4.11*/
         phyEnMsk4 = phyEnMsk4 | (1 << 11);
     }
     if (1 == pAbility->FC)
     {
         /*Flow control in reg 4.10*/
         phyEnMsk4 = phyEnMsk4 | ((1 << 10));
     }

     /*1000 BASE-T control register setting*/
     if ((retVal = rtl8367c_getAsicPHYReg(unit, rtksw_switch_port_L2P_get(unit, port), PHY_1000_BASET_CONTROL_REG, &phyData)) != RT_ERR_OK)
         return retVal;

     phyData = (phyData & (~0x0200)) | phyEnMsk9 ;

     if ((retVal = rtl8367c_setAsicPHYReg(unit,rtksw_switch_port_L2P_get(unit, port), PHY_1000_BASET_CONTROL_REG, phyData)) != RT_ERR_OK)
         return retVal;

     /*Auto-Negotiation control register setting*/
     if ((retVal = rtl8367c_getAsicPHYReg(unit, rtksw_switch_port_L2P_get(unit, port), PHY_AN_ADVERTISEMENT_REG, &phyData)) != RT_ERR_OK)
         return retVal;

     phyData = (phyData & (~0x0DE0)) | phyEnMsk4;
     if ((retVal = rtl8367c_setAsicPHYReg(unit, rtksw_switch_port_L2P_get(unit, port), PHY_AN_ADVERTISEMENT_REG, phyData)) != RT_ERR_OK)
         return retVal;

     /*Control register setting and power off/on*/
     phyData = phyEnMsk0 & (~(1 << 12));
     phyData |= (1 << 11);   /* power down PHY, bit 11 should be set to 1 */
     if ((retVal = rtl8367c_setAsicPHYReg(unit, rtksw_switch_port_L2P_get(unit, port), PHY_CONTROL_REG, phyData)) != RT_ERR_OK)
         return retVal;

     phyData = phyData & (~(1 << 11));   /* power on PHY, bit 11 should be set to 0*/
     if ((retVal = rtl8367c_setAsicPHYReg(unit, rtksw_switch_port_L2P_get(unit, port), PHY_CONTROL_REG, phyData)) != RT_ERR_OK)
         return retVal;

     return RT_ERR_OK;
}

/* Function Name:
 *      dal_rtl8367c_port_phyForceModeAbility_get
 * Description:
 *      Get PHY ability through PHY registers.
 * Input:
 *      unit    - Unit ID
 *      port    - Port id.
 * Output:
 *      pAbility - Ability structure
 * Return:
 *      RT_ERR_OK               - OK
 *      RT_ERR_FAILED           - Failed
 *      RT_ERR_SMI              - SMI access error
 *      RT_ERR_PORT_ID          - Invalid port number.
 *      RT_ERR_PHY_REG_ID       - Invalid PHY address
 *      RT_ERR_INPUT            - Invalid input parameters.
 *      RT_ERR_BUSYWAIT_TIMEOUT - PHY access busy
 * Note:
 *      Get the capablity of specified PHY.
 */
rtksw_api_ret_t dal_rtl8367c_port_phyForceModeAbility_get(rtksw_uint32 unit, rtksw_port_t port, rtksw_port_phy_ability_t *pAbility)
{
    rtksw_api_ret_t       retVal;
    rtksw_uint32          phyData0;
    rtksw_uint32          phyData4;
    rtksw_uint32          phyData9;
    rtksw_port_media_t    media_type;

    /* Check initialization state */
    RTKSW_CHK_INIT_STATE(unit);

    /* Check Port Valid */
     RTKSW_CHK_PORT_IS_UTP(unit, port);

     if(NULL == pAbility)
        return RT_ERR_NULL_POINTER;

     if (rtksw_switch_isComboPort(unit, port) == RT_ERR_OK)
     {
         if ((retVal = _dal_rtl8367c_port_phyComboPortMedia_get(unit, port, &media_type)) != RT_ERR_OK)
             return retVal;

         if(media_type == RTKSW_PORT_MEDIA_FIBER)
         {
             return _dal_rtl8367c_port_FiberModeAbility_get(unit, port, pAbility);
         }
     }

    /*Control register setting and restart auto*/
    if ((retVal = rtl8367c_getAsicPHYReg(unit, rtksw_switch_port_L2P_get(unit, port), PHY_CONTROL_REG, &phyData0)) != RT_ERR_OK)
        return retVal;

    /*Auto-Negotiation control register setting*/
    if ((retVal = rtl8367c_getAsicPHYReg(unit, rtksw_switch_port_L2P_get(unit, port), PHY_AN_ADVERTISEMENT_REG, &phyData4)) != RT_ERR_OK)
        return retVal;

    /*1000 BASE-T control register setting*/
    if ((retVal = rtl8367c_getAsicPHYReg(unit, rtksw_switch_port_L2P_get(unit, port), PHY_1000_BASET_CONTROL_REG, &phyData9)) != RT_ERR_OK)
        return retVal;

    osal_memset(pAbility, 0x00, sizeof(rtksw_port_phy_ability_t));
    
    if (phyData9 & (1 << 9))
        pAbility->Full_1000 = 1;
    else
        pAbility->Full_1000 = 0;

    if (phyData4 & (1 << 11))
        pAbility->AsyFC = 1;
    else
        pAbility->AsyFC = 0;

    if (phyData4 & ((1 << 10)))
        pAbility->FC = 1;
    else
        pAbility->FC = 0;


    if (phyData4 & (1 << 8))
        pAbility->Full_100 = 1;
    else
        pAbility->Full_100 = 0;

    if (phyData4 & (1 << 7))
        pAbility->Half_100 = 1;
    else
        pAbility->Half_100 = 0;

    if (phyData4 & (1 << 6))
        pAbility->Full_10 = 1;
    else
        pAbility->Full_10 = 0;

    if (phyData4 & (1 << 5))
        pAbility->Half_10 = 1;
    else
        pAbility->Half_10 = 0;


    if (phyData0 & (1 << 12))
        pAbility->AutoNegotiation = 1;
    else
        pAbility->AutoNegotiation = 0;

    return RT_ERR_OK;
}

/* Function Name:
 *      dal_rtl8367c_port_phyStatus_get
 * Description:
 *      Get ethernet PHY linking status
 * Input:
 *      unit    - Unit ID
 *      port    - Port id.
 * Output:
 *      linkStatus  - PHY link status
 *      speed       - PHY link speed
 *      duplex      - PHY duplex mode
 * Return:
 *      RT_ERR_OK               - OK
 *      RT_ERR_FAILED           - Failed
 *      RT_ERR_SMI              - SMI access error
 *      RT_ERR_PORT_ID          - Invalid port number.
 *      RT_ERR_PHY_REG_ID       - Invalid PHY address
 *      RT_ERR_INPUT            - Invalid input parameters.
 *      RT_ERR_BUSYWAIT_TIMEOUT - PHY access busy
 * Note:
 *      API will return auto negotiation status of phy.
 */
rtksw_api_ret_t dal_rtl8367c_port_phyStatus_get(rtksw_uint32 unit, rtksw_port_t port, rtksw_port_linkStatus_t *pLinkStatus, rtksw_port_speed_t *pSpeed, rtksw_port_duplex_t *pDuplex)
{
    rtksw_api_ret_t retVal;
    rtksw_uint32 phyData;

    /* Check initialization state */
    RTKSW_CHK_INIT_STATE(unit);

    /* Check Port Valid */
    RTKSW_CHK_PORT_IS_UTP(unit, port);

    if( (NULL == pLinkStatus) || (NULL == pSpeed) || (NULL == pDuplex) )
        return RT_ERR_NULL_POINTER;

    /*Get PHY resolved register*/
    if ((retVal = rtl8367c_getAsicPHYReg(unit, rtksw_switch_port_L2P_get(unit, port), PHY_RESOLVED_REG, &phyData)) != RT_ERR_OK)
        return retVal;

    /*check link status*/
    if (phyData & (1<<2))
    {
        *pLinkStatus = 1;

        /*check link speed*/
        *pSpeed = (phyData&0x0030) >> 4;

        /*check link duplex*/
        *pDuplex = (phyData&0x0008) >> 3;
    }
    else
    {
        *pLinkStatus = 0;
        *pSpeed = 0;
        *pDuplex = 0;
    }

    return RT_ERR_OK;
}

/* Function Name:
 *      dal_rtl8367c_port_macForceLink_set
 * Description:
 *      Set port force linking configuration.
 * Input:
 *      unit            - Unit ID
 *      port            - port id.
 *      pPortability    - port ability configuration
 * Output:
 *      None
 * Return:
 *      RT_ERR_OK           - OK
 *      RT_ERR_FAILED       - Failed
 *      RT_ERR_SMI          - SMI access error
 *      RT_ERR_PORT_ID      - Invalid port number.
 * Note:
 *      This API can set Port/MAC force mode properties.
 */
rtksw_api_ret_t dal_rtl8367c_port_macForceLink_set(rtksw_uint32 unit, rtksw_port_t port, rtksw_port_mac_ability_t *pPortability)
{
    rtksw_api_ret_t retVal;
    rtl8367c_port_ability_t ability;
    rtksw_uint32 ext_id;

    /* Check initialization state */
    RTKSW_CHK_INIT_STATE(unit);

    /* Check Port Valid */
    RTKSW_CHK_PORT_VALID(unit, port);

    if(NULL == pPortability)
        return RT_ERR_NULL_POINTER;

    if (pPortability->forcemode >1|| pPortability->speed > 2 || pPortability->duplex > 1 ||
       pPortability->link > 1 || pPortability->nway > 1 || pPortability->txpause > 1 || pPortability->rxpause > 1)
        return RT_ERR_INPUT;

    if (rtksw_switch_isUtpPort(unit, port) == RT_ERR_OK)
    {
        if ((retVal = rtl8367c_getAsicPortForceLink(unit, rtksw_switch_port_L2P_get(unit, port), &ability)) != RT_ERR_OK)
            return retVal;

        ability.forcemode = pPortability->forcemode;
        ability.speed     = pPortability->speed;
        ability.duplex    = pPortability->duplex;
        ability.link      = pPortability->link;
        ability.nway      = pPortability->nway;
        ability.txpause   = pPortability->txpause;
        ability.rxpause   = pPortability->rxpause;

        if ((retVal = rtl8367c_setAsicPortForceLink(unit, rtksw_switch_port_L2P_get(unit, port), &ability)) != RT_ERR_OK)
            return retVal;
    }
    else
    {
        ext_id = port - 15;
        if ((retVal = rtl8367c_getAsicPortForceLinkExt(unit, ext_id, &ability)) != RT_ERR_OK)
            return retVal;

        ability.forcemode = pPortability->forcemode;
        ability.speed     = pPortability->speed;
        ability.duplex    = pPortability->duplex;
        ability.link      = pPortability->link;
        ability.nway      = pPortability->nway;
        ability.txpause   = pPortability->txpause;
        ability.rxpause   = pPortability->rxpause;  

        if ((retVal = rtl8367c_setAsicPortForceLinkExt(unit, ext_id, &ability)) != RT_ERR_OK)
            return retVal;
    }

    return RT_ERR_OK;
}

/* Function Name:
 *      dal_rtl8367c_port_macForceLink_get
 * Description:
 *      Get port force linking configuration.
 * Input:
 *      unit    - Unit ID
 *      port    - Port id.
 * Output:
 *      pPortability - port ability configuration
 * Return:
 *      RT_ERR_OK           - OK
 *      RT_ERR_FAILED       - Failed
 *      RT_ERR_SMI          - SMI access error
 *      RT_ERR_PORT_ID      - Invalid port number.
 *      RT_ERR_INPUT        - Invalid input parameters.
 * Note:
 *      This API can get Port/MAC force mode properties.
 */
rtksw_api_ret_t dal_rtl8367c_port_macForceLink_get(rtksw_uint32 unit, rtksw_port_t port, rtksw_port_mac_ability_t *pPortability)
{
    rtksw_api_ret_t retVal;
    rtl8367c_port_ability_t ability;
    rtksw_uint32 ext_id;

    /* Check initialization state */
    RTKSW_CHK_INIT_STATE(unit);

    /* Check Port Valid */
    RTKSW_CHK_PORT_VALID(unit, port);

    if(NULL == pPortability)
        return RT_ERR_NULL_POINTER;

    if (rtksw_switch_isUtpPort(unit, port) == RT_ERR_OK)
    {
        if ((retVal = rtl8367c_getAsicPortForceLink(unit, rtksw_switch_port_L2P_get(unit, port), &ability)) != RT_ERR_OK)
            return retVal;
    }
    else
    {
        ext_id = port - 15;
        if ((retVal = rtl8367c_getAsicPortForceLinkExt(unit, ext_id, &ability)) != RT_ERR_OK)
            return retVal;
    }

    pPortability->forcemode = ability.forcemode;
    pPortability->speed     = ability.speed;
    pPortability->duplex    = ability.duplex;
    pPortability->link      = ability.link;
    pPortability->nway      = ability.nway;
    pPortability->txpause   = ability.txpause;
    pPortability->rxpause   = ability.rxpause;

    return RT_ERR_OK;
}

/* Function Name:
 *      dal_rtl8367c_port_macForceLinkExt_set
 * Description:
 *      Set external interface force linking configuration.
 * Input:
 *      unit            - Unit ID
 *      port            - external port ID
 *      mode            - external interface mode
 *      pPortability    - port ability configuration
 * Output:
 *      None
 * Return:
 *      RT_ERR_OK           - OK
 *      RT_ERR_FAILED       - Failed
 *      RT_ERR_SMI          - SMI access error
 *      RT_ERR_INPUT        - Invalid input parameters.
 * Note:
 *      This API can set external interface force mode properties.
 *      The external interface can be set to:
 *      - RTKSW_MODE_EXT_DISABLE,
 *      - RTKSW_MODE_EXT_RGMII,
 *      - RTKSW_MODE_EXT_MII_MAC,
 *      - RTKSW_MODE_EXT_MII_PHY,
 *      - RTKSW_MODE_EXT_TMII_MAC,
 *      - RTKSW_MODE_EXT_TMII_PHY,
 *      - RTKSW_MODE_EXT_GMII,
 *      - RTKSW_MODE_EXT_RMII_MAC,
 *      - RTKSW_MODE_EXT_RMII_PHY,
 *      - RTKSW_MODE_EXT_SGMII,
 *      - RTKSW_MODE_EXT_HSGMII,
 *      - RTKSW_MODE_EXT_1000X_100FX,
 *      - RTKSW_MODE_EXT_1000X,
 *      - RTKSW_MODE_EXT_100FX,
 */
rtksw_api_ret_t dal_rtl8367c_port_macForceLinkExt_set(rtksw_uint32 unit, rtksw_port_t port, rtksw_mode_ext_t mode, rtksw_port_mac_ability_t *pPortability)
{
    rtksw_api_ret_t retVal;
    rtl8367c_port_ability_t ability;
    rtksw_uint32 ext_id = 0;
    switch_chip_t chipID = 0;

    /* Check initialization state */
    RTKSW_CHK_INIT_STATE(unit);

    /* Check Port Valid */
    RTKSW_CHK_PORT_IS_EXT(unit, port);

    if(NULL == pPortability)
        return RT_ERR_NULL_POINTER;

    if ((mode >= RTKSW_MODE_EXT_END) || (mode >= RTKSW_MODE_EXT_10GR))
        return RT_ERR_INPUT;

    chipID = rtksw_switch_chipType_get(unit);
    if (chipID == CHIP_RTL8367C)
    {
        if (mode == RTKSW_MODE_EXT_FIBER_2P5G)
            return RT_ERR_CHIP_NOT_SUPPORTED;
    }
    
    if ( ((mode == RTKSW_MODE_EXT_HSGMII) || (mode == RTKSW_MODE_EXT_FIBER_2P5G)) && ((chipID != CHIP_RTL8370C) || (pPortability->forcemode != MAC_NORMAL)) )
    {
        if (pPortability->forcemode > 1 || pPortability->speed != RTKSW_PORT_SPEED_2500M || pPortability->duplex != RTKSW_PORT_FULL_DUPLEX ||
           pPortability->link >= RTKSW_PORT_LINKSTATUS_END || pPortability->nway > 1 || pPortability->txpause > 1 || pPortability->rxpause > 1)
            return RT_ERR_INPUT;

        if(rtksw_switch_isHsgPort(unit, port) != RT_ERR_OK)
            return RT_ERR_PORT_ID;
    }
    else if (mode != RTKSW_MODE_EXT_DISABLE)
    {
        if (pPortability->forcemode > 1 || pPortability->speed > RTKSW_PORT_SPEED_1000M || pPortability->duplex >= RTKSW_PORT_DUPLEX_END ||
           pPortability->link >= RTKSW_PORT_LINKSTATUS_END || pPortability->nway > 1 || pPortability->txpause > 1 || pPortability->rxpause > 1)
            return RT_ERR_INPUT;
    }

    ext_id = port - 15;

    if(mode == RTKSW_MODE_EXT_DISABLE)
    {
        osal_memset(&ability, 0x00, sizeof(rtl8367c_port_ability_t));
        if ((retVal = rtl8367c_setAsicPortForceLinkExt(unit, ext_id, &ability)) != RT_ERR_OK)
            return retVal;

        if ((retVal = rtl8367c_setAsicPortExtMode(unit, ext_id, mode)) != RT_ERR_OK)
            return retVal;
    }
    else
    {
        if ((retVal = rtl8367c_setAsicPortExtMode(unit, ext_id, mode)) != RT_ERR_OK)
            return retVal;

        if ((retVal = rtl8367c_getAsicPortForceLinkExt(unit, ext_id, &ability)) != RT_ERR_OK)
            return retVal;

        ability.forcemode = pPortability->forcemode;       
        ability.duplex    = pPortability->duplex;
        ability.link      = pPortability->link;
        ability.nway      = pPortability->nway;
        ability.txpause   = pPortability->txpause;
        ability.rxpause   = pPortability->rxpause;
        
        if (chipID == CHIP_RTL8370C)
        {
            if((mode == RTKSW_MODE_EXT_HSGMII) || (mode == RTKSW_MODE_EXT_FIBER_2P5G))
                ability.speed = 5; //5:RTKSW_PORT_SPEED_2500M
            else
                ability.speed = pPortability->speed;
        }            
        else                
            ability.speed     = ((mode == RTKSW_MODE_EXT_HSGMII) || (mode == RTKSW_MODE_EXT_FIBER_2P5G)) ? RTKSW_PORT_SPEED_1000M : pPortability->speed;

        if ((retVal = rtl8367c_setAsicPortForceLinkExt(unit, ext_id, &ability)) != RT_ERR_OK)
            return retVal;
    }

    return RT_ERR_OK;
}

/* Function Name:
 *      dal_rtl8367c_port_macForceLinkExt_get
 * Description:
 *      Set external interface force linking configuration.
 * Input:
 *      unit            - Unit ID
 *      port            - external port ID
 * Output:
 *      pMode           - external interface mode
 *      pPortability    - port ability configuration
 * Return:
 *      RT_ERR_OK           - OK
 *      RT_ERR_FAILED       - Failed
 *      RT_ERR_SMI          - SMI access error
 *      RT_ERR_INPUT        - Invalid input parameters.
 * Note:
 *      This API can get external interface force mode properties.
 */
rtksw_api_ret_t dal_rtl8367c_port_macForceLinkExt_get(rtksw_uint32 unit, rtksw_port_t port, rtksw_mode_ext_t *pMode, rtksw_port_mac_ability_t *pPortability)
{
    rtksw_api_ret_t retVal;
    rtl8367c_port_ability_t ability;
    rtksw_uint32 ext_id;
    printf("dal_rtl8367c_port_macForceLinkExt_get\n");
    /* Check initialization state */
    RTKSW_CHK_INIT_STATE(unit);

    /* Check Port Valid */
    RTKSW_CHK_PORT_IS_EXT(unit, port);

    if(NULL == pMode)
        return RT_ERR_NULL_POINTER;

    if(NULL == pPortability)
        return RT_ERR_NULL_POINTER;

    ext_id = port - 15;
    printf("ext_id: %d\n", ext_id);
    if ((retVal = rtl8367c_getAsicPortExtMode(unit, ext_id, (rtksw_uint32 *)pMode)) != RT_ERR_OK)
        return retVal;
    printf("pMode: %d\n", *pMode);
    if ((retVal = rtl8367c_getAsicPortForceLinkExt(unit, ext_id, &ability)) != RT_ERR_OK)
        return retVal;
    printf("ability.speed: %d\n", ability.speed);
    pPortability->speed     = ((*pMode == RTKSW_MODE_EXT_HSGMII) || (*pMode == RTKSW_MODE_EXT_FIBER_2P5G)) ? RTKSW_PORT_SPEED_2500M : ability.speed;
    pPortability->forcemode = ability.forcemode;
    pPortability->duplex    = ability.duplex;
    pPortability->link      = ability.link;
    pPortability->nway      = ability.nway;
    pPortability->txpause   = ability.txpause;
    pPortability->rxpause   = ability.rxpause;

    return RT_ERR_OK;

}

/* Function Name:
 *      dal_rtl8367c_port_macStatus_get
 * Description:
 *      Get port link status.
 * Input:
 *      unit    - Unit ID
 *      port    - Port id.
 * Output:
 *      pPortstatus - port ability configuration
 * Return:
 *      RT_ERR_OK           - OK
 *      RT_ERR_FAILED       - Failed
 *      RT_ERR_SMI          - SMI access error
 *      RT_ERR_PORT_ID      - Invalid port number.
 * Note:
 *      This API can get Port/PHY properties.
 */
rtksw_api_ret_t dal_rtl8367c_port_macStatus_get(rtksw_uint32 unit, rtksw_port_t port, rtksw_port_mac_ability_t *pPortstatus)
{
    rtksw_api_ret_t retVal;
    rtl8367c_port_status_t status;
    rtksw_uint32 hsgsel;

    /* Check initialization state */
    RTKSW_CHK_INIT_STATE(unit);

    /* Check Port Valid */
    RTKSW_CHK_PORT_VALID(unit, port);

    if(NULL == pPortstatus)
        return RT_ERR_NULL_POINTER;

    if ((retVal = rtl8367c_getAsicPortStatus(unit, rtksw_switch_port_L2P_get(unit, port), &status)) != RT_ERR_OK)
        return retVal;


    pPortstatus->duplex    = status.duplex;
    pPortstatus->link      = status.link; 
    pPortstatus->nway      = status.nway;
    pPortstatus->txpause   = status.txpause;
    pPortstatus->rxpause   = status.rxpause;
    
    if (rtksw_switch_chipType_get(unit) == CHIP_RTL8370C)
    {
        if(status.speed >= 4)
        {
            if(status.speed ==5 || status.speed ==8)
                pPortstatus->speed = RTKSW_PORT_SPEED_2500M;
            else if(status.speed ==4)
                return RT_ERR_FAILED;
            else if(status.speed ==7)
                pPortstatus->speed = RTKSW_PORT_SPEED_1000M;
            else
                pPortstatus->speed = status.speed; 
        }
        else
            pPortstatus->speed = status.speed; 
    }     
    else
    {
        if( (retVal = rtl8367c_getAsicRegBit(unit, RTL8367C_REG_SDS_MISC, RTL8367C_CFG_MAC8_SEL_HSGMII_OFFSET, &hsgsel)) != RT_ERR_OK)
                return retVal;

        if( (rtksw_switch_isHsgPort(unit, port) == RT_ERR_OK) && (hsgsel == 1) )
            pPortstatus->speed = RTKSW_PORT_SPEED_2500M;
        else
            pPortstatus->speed = status.speed;   
    }

    return RT_ERR_OK;
}

/* Function Name:
 *      dal_rtl8367c_port_macLocalLoopbackEnable_set
 * Description:
 *      Set Port Local Loopback. (Redirect TX to RX.)
 * Input:
 *      unit    - Unit ID
 *      port    - Port id.
 *      enable  - Loopback state, 0:disable, 1:enable
 * Output:
 *      None.
 * Return:
 *      RT_ERR_OK           - OK
 *      RT_ERR_FAILED       - Failed
 *      RT_ERR_SMI          - SMI access error
 *      RT_ERR_PORT_ID      - Invalid port number.
 * Note:
 *      This API can enable/disable Local loopback in MAC.
 *      For UTP port, This API will also enable the digital
 *      loopback bit in PHY register for sync of speed between
 *      PHY and MAC. For EXT port, users need to force the
 *      link state by themself.
 */
rtksw_api_ret_t dal_rtl8367c_port_macLocalLoopbackEnable_set(rtksw_uint32 unit, rtksw_port_t port, rtksw_enable_t enable)
{
    rtksw_api_ret_t   retVal;
    rtksw_uint32      data;

    /* Check initialization state */
    RTKSW_CHK_INIT_STATE(unit);

    /* Check Port Valid */
    RTKSW_CHK_PORT_VALID(unit, port);

    if(enable >= RTKSW_ENABLE_END)
        return RT_ERR_INPUT;

    if ((retVal = rtl8367c_setAsicPortLoopback(unit, rtksw_switch_port_L2P_get(unit, port), enable)) != RT_ERR_OK)
        return retVal;

    if(rtksw_switch_isUtpPort(unit, port) == RT_ERR_OK)
    {
        if ((retVal = rtl8367c_getAsicPHYReg(unit, rtksw_switch_port_L2P_get(unit, port), PHY_CONTROL_REG, &data)) != RT_ERR_OK)
            return retVal;

        if(enable == RTKSW_ENABLED)
            data |= (0x0001 << 14);
        else
            data &= ~(0x0001 << 14);

        if ((retVal = rtl8367c_setAsicPHYReg(unit, rtksw_switch_port_L2P_get(unit, port), PHY_CONTROL_REG, data)) != RT_ERR_OK)
            return retVal;
    }

    return RT_ERR_OK;
}

/* Function Name:
 *      dal_rtl8367c_port_macLocalLoopbackEnable_get
 * Description:
 *      Get Port Local Loopback. (Redirect TX to RX.)
 * Input:
 *      unit    - Unit ID
 *      port    - Port id.
 * Output:
 *      pEnable  - Loopback state, 0:disable, 1:enable
 * Return:
 *      RT_ERR_OK           - OK
 *      RT_ERR_FAILED       - Failed
 *      RT_ERR_SMI          - SMI access error
 *      RT_ERR_PORT_ID      - Invalid port number.
 * Note:
 *      None.
 */
rtksw_api_ret_t dal_rtl8367c_port_macLocalLoopbackEnable_get(rtksw_uint32 unit, rtksw_port_t port, rtksw_enable_t *pEnable)
{
    rtksw_api_ret_t retVal;

    /* Check initialization state */
    RTKSW_CHK_INIT_STATE(unit);

    /* Check Port Valid */
    RTKSW_CHK_PORT_VALID(unit, port);

    if(NULL == pEnable)
        return RT_ERR_NULL_POINTER;

    if ((retVal = rtl8367c_getAsicPortLoopback(unit, rtksw_switch_port_L2P_get(unit, port), pEnable)) != RT_ERR_OK)
        return retVal;

    return RT_ERR_OK;
}

/* Function Name:
 *      dal_rtl8367c_port_phyReg_set
 * Description:
 *      Set PHY register data of the specific port.
 * Input:
 *      unit    - Unit ID
 *      port    - port id.
 *      reg     - Register id
 *      regData - Register data
 * Output:
 *      None
 * Return:
 *      RT_ERR_OK               - OK
 *      RT_ERR_FAILED           - Failed
 *      RT_ERR_SMI              - SMI access error
 *      RT_ERR_PORT_ID          - Invalid port number.
 *      RT_ERR_PHY_REG_ID       - Invalid PHY address
 *      RT_ERR_BUSYWAIT_TIMEOUT - PHY access busy
 * Note:
 *      This API can set PHY register data of the specific port.
 */
rtksw_api_ret_t dal_rtl8367c_port_phyReg_set(rtksw_uint32 unit, rtksw_port_t port, rtksw_port_phy_reg_t reg, rtksw_port_phy_data_t regData)
{
    rtksw_api_ret_t retVal;

    /* Check initialization state */
    RTKSW_CHK_INIT_STATE(unit);

    /* Check Port Valid */
    RTKSW_CHK_PORT_IS_UTP(unit, port);

    if ((retVal = rtl8367c_setAsicPHYReg(unit, rtksw_switch_port_L2P_get(unit, port), reg, regData)) != RT_ERR_OK)
        return retVal;

    return RT_ERR_OK;
}

/* Function Name:
 *      dal_rtl8367c_port_phyReg_get
 * Description:
 *      Get PHY register data of the specific port.
 * Input:
 *      unit    - Unit ID
 *      port    - Port id.
 *      reg     - Register id
 * Output:
 *      pData   - Register data
 * Return:
 *      RT_ERR_OK               - OK
 *      RT_ERR_FAILED           - Failed
 *      RT_ERR_SMI              - SMI access error
 *      RT_ERR_PORT_ID          - Invalid port number.
 *      RT_ERR_PHY_REG_ID       - Invalid PHY address
 *      RT_ERR_BUSYWAIT_TIMEOUT - PHY access busy
 * Note:
 *      This API can get PHY register data of the specific port.
 */
rtksw_api_ret_t dal_rtl8367c_port_phyReg_get(rtksw_uint32 unit, rtksw_port_t port, rtksw_port_phy_reg_t reg, rtksw_port_phy_data_t *pData)
{
    rtksw_api_ret_t retVal;

    /* Check initialization state */
    RTKSW_CHK_INIT_STATE(unit);

    /* Check Port Valid */
    RTKSW_CHK_PORT_IS_UTP(unit, port);

    if ((retVal = rtl8367c_getAsicPHYReg(unit, rtksw_switch_port_L2P_get(unit, port), reg, pData)) != RT_ERR_OK)
        return retVal;

    return RT_ERR_OK;
}

/* Function Name:
 *      dal_rtl8367c_port_phyOCPReg_set
 * Description:
 *      Set PHY OCP register
 * Input:
 *      unit        - Unit ID
 *      port        - PHY ID
 *      ocpAddr     - OCP register address
 *      ocpData     - OCP Data.
 * Output:
 *      None.
 * Return:
 *      RT_ERR_OK                               - OK
 *      RT_ERR_FAILED                           - Failed
 *      RT_ERR_BUSYWAIT_TIMEOUT                 - Timeout
 * Note:
 *      None.
 */
rtksw_api_ret_t dal_rtl8367c_port_phyOCPReg_set(rtksw_uint32 unit, rtksw_port_t port, rtksw_uint32 ocpAddr, rtksw_uint32 ocpData )
{
    rtksw_api_ret_t retVal;

    /* Check initialization state */
    RTKSW_CHK_INIT_STATE(unit);

    /* Check Port Valid */
    RTKSW_CHK_PORT_IS_UTP(unit, port);

    if ((retVal = rtl8367c_setAsicPHYOCPReg(unit, rtksw_switch_port_L2P_get(unit, port), ocpAddr, ocpData)) != RT_ERR_OK)
        return retVal;

    return RT_ERR_OK;
}

/* Function Name:
 *      dal_rtl8367c_port_phyOCPReg_get
 * Description:
 *      Set PHY OCP register
 * Input:
 *      unit        - Unit ID
 *      phyNo       - PHY ID
 *      ocpAddr     - OCP register address
 * Output:
 *      pRegData    - OCP data.
 * Return:
 *      RT_ERR_OK                               - OK
 *      RT_ERR_FAILED                           - Failed
 *      RT_ERR_NULL_POINTER                     - Null pointer
 * Note:
 *      None.
 */
rtksw_api_ret_t dal_rtl8367c_port_phyOCPReg_get(rtksw_uint32 unit, rtksw_port_t port, rtksw_uint32 ocpAddr, rtksw_uint32 *pRegData )
{
    rtksw_api_ret_t retVal;

    /* Check initialization state */
    RTKSW_CHK_INIT_STATE(unit);

    /* Check Port Valid */
    RTKSW_CHK_PORT_IS_UTP(unit, port);

    if (pRegData == NULL)
        return RT_ERR_NULL_POINTER;

    if ((retVal = rtl8367c_getAsicPHYOCPReg(unit, rtksw_switch_port_L2P_get(unit, port), ocpAddr, pRegData)) != RT_ERR_OK)
        return retVal;

    return RT_ERR_OK;
}

/* Function Name:
 *      dal_rtl8367c_port_backpressureEnable_set
 * Description:
 *      Set the half duplex backpressure enable status of the specific port.
 * Input:
 *      unit    - Unit ID
 *      port    - port id.
 *      enable  - Back pressure status.
 * Output:
 *      None
 * Return:
 *      RT_ERR_OK           - OK
 *      RT_ERR_FAILED       - Failed
 *      RT_ERR_SMI          - SMI access error
 *      RT_ERR_PORT_ID      - Invalid port number.
 *      RT_ERR_ENABLE       - Invalid enable input.
 * Note:
 *      This API can set the half duplex backpressure enable status of the specific port.
 *      The half duplex backpressure enable status of the port is as following:
 *      - DISABLE(Defer)
 *      - ENABLE (Backpressure)
 */
rtksw_api_ret_t dal_rtl8367c_port_backpressureEnable_set(rtksw_uint32 unit, rtksw_port_t port, rtksw_enable_t enable)
{
    rtksw_api_ret_t retVal;

    /* Check initialization state */
    RTKSW_CHK_INIT_STATE(unit);

    if (port != RTKSW_WHOLE_SYSTEM)
        return RT_ERR_PORT_ID;

    if (enable >= RTKSW_ENABLE_END)
        return RT_ERR_INPUT;

    if ((retVal = rtl8367c_setAsicPortJamMode(unit, !enable)) != RT_ERR_OK)
        return retVal;

    return RT_ERR_OK;
}

/* Function Name:
 *      dal_rtl8367c_port_backpressureEnable_get
 * Description:
 *      Get the half duplex backpressure enable status of the specific port.
 * Input:
 *      unit    - Unit ID
 *      port    - Port id.
 * Output:
 *      pEnable - Back pressure status.
 * Return:
 *      RT_ERR_OK           - OK
 *      RT_ERR_FAILED       - Failed
 *      RT_ERR_SMI          - SMI access error
 *      RT_ERR_PORT_ID      - Invalid port number.
 * Note:
 *      This API can get the half duplex backpressure enable status of the specific port.
 *      The half duplex backpressure enable status of the port is as following:
 *      - DISABLE(Defer)
 *      - ENABLE (Backpressure)
 */
rtksw_api_ret_t dal_rtl8367c_port_backpressureEnable_get(rtksw_uint32 unit, rtksw_port_t port, rtksw_enable_t *pEnable)
{
    rtksw_api_ret_t retVal;
    rtksw_uint32 regData;

    /* Check initialization state */
    RTKSW_CHK_INIT_STATE(unit);

    if (port != RTKSW_WHOLE_SYSTEM)
        return RT_ERR_PORT_ID;

    if(NULL == pEnable)
        return RT_ERR_NULL_POINTER;

    if ((retVal = rtl8367c_getAsicPortJamMode(unit, &regData)) != RT_ERR_OK)
        return retVal;

    *pEnable = !regData;

    return RT_ERR_OK;
}

/* Function Name:
 *      dal_rtl8367c_port_adminEnable_set
 * Description:
 *      Set port admin configuration of the specific port.
 * Input:
 *      unit    - Unit ID
 *      port    - port id.
 *      enable  - Back pressure status.
 * Output:
 *      None
 * Return:
 *      RT_ERR_OK           - OK
 *      RT_ERR_FAILED       - Failed
 *      RT_ERR_SMI          - SMI access error
 *      RT_ERR_PORT_ID      - Invalid port number.
 *      RT_ERR_ENABLE       - Invalid enable input.
 * Note:
 *      This API can set port admin configuration of the specific port.
 *      The port admin configuration of the port is as following:
 *      - DISABLE
 *      - ENABLE
 */
rtksw_api_ret_t dal_rtl8367c_port_adminEnable_set(rtksw_uint32 unit, rtksw_port_t port, rtksw_enable_t enable)
{
    rtksw_api_ret_t retVal;
    rtksw_uint32      data;

    /* Check initialization state */
    RTKSW_CHK_INIT_STATE(unit);

    /* Check Port Valid */
    RTKSW_CHK_PORT_IS_UTP(unit, port);

    if (enable >= RTKSW_ENABLE_END)
        return RT_ERR_INPUT;

    if ((retVal = rtl8367c_getAsicPHYReg(unit, rtksw_switch_port_L2P_get(unit, port), PHY_CONTROL_REG, &data)) != RT_ERR_OK)
        return retVal;

    if (RTKSW_ENABLED == enable)
    {
        data &= 0xF7FF;
        data |= 0x0200;
    }
    else if (RTKSW_DISABLED == enable)
    {
        data |= 0x0800;
    }

    if ((retVal = rtl8367c_setAsicPHYReg(unit, rtksw_switch_port_L2P_get(unit, port), PHY_CONTROL_REG, data)) != RT_ERR_OK)
        return retVal;

    return RT_ERR_OK;
}

/* Function Name:
 *      dal_rtl8367c_port_adminEnable_get
 * Description:
 *      Get port admin configurationof the specific port.
 * Input:
 *      unit    - Unit ID
 *      port    - Port id.
 * Output:
 *      pEnable - Back pressure status.
 * Return:
 *      RT_ERR_OK           - OK
 *      RT_ERR_FAILED       - Failed
 *      RT_ERR_SMI          - SMI access error
 *      RT_ERR_PORT_ID      - Invalid port number.
 * Note:
 *      This API can get port admin configuration of the specific port.
 *      The port admin configuration of the port is as following:
 *      - DISABLE
 *      - ENABLE
 */
rtksw_api_ret_t dal_rtl8367c_port_adminEnable_get(rtksw_uint32 unit, rtksw_port_t port, rtksw_enable_t *pEnable)
{
    rtksw_api_ret_t retVal;
    rtksw_uint32      data;

    /* Check initialization state */
    RTKSW_CHK_INIT_STATE(unit);

    /* Check Port Valid */
    RTKSW_CHK_PORT_IS_UTP(unit, port);

    if(NULL == pEnable)
        return RT_ERR_NULL_POINTER;

    if ((retVal = rtl8367c_getAsicPHYReg(unit, port, PHY_CONTROL_REG, &data)) != RT_ERR_OK)
        return retVal;

    if ( (data & 0x0800) == 0x0800)
    {
        *pEnable = RTKSW_DISABLED;
    }
    else
    {
        *pEnable = RTKSW_ENABLED;
    }

    return RT_ERR_OK;
}

/* Function Name:
 *      dal_rtl8367c_port_isolation_set
 * Description:
 *      Set permitted port isolation portmask
 * Input:
 *      unit        - Unit ID
 *      port        - port id.
 *      pPortmask   - Permit port mask
 * Output:
 *      None
 * Return:
 *      RT_ERR_OK           - OK
 *      RT_ERR_FAILED       - Failed
 *      RT_ERR_SMI          - SMI access error
 *      RT_ERR_PORT_ID      - Invalid port number.
 *      RT_ERR_PORT_MASK    - Invalid portmask.
 * Note:
 *      This API set the port mask that a port can trasmit packet to of each port
 *      A port can only transmit packet to ports included in permitted portmask
 */
rtksw_api_ret_t dal_rtl8367c_port_isolation_set(rtksw_uint32 unit, rtksw_port_t port, rtksw_portmask_t *pPortmask)
{
    rtksw_api_ret_t retVal;
    rtksw_uint32 pmask;

    /* Check initialization state */
    RTKSW_CHK_INIT_STATE(unit);

    /* Check Port Valid */
    RTKSW_CHK_PORT_VALID(unit, port);

    if(NULL == pPortmask)
        return RT_ERR_NULL_POINTER;

    /* check port mask */
    RTKSW_CHK_PORTMASK_VALID(unit, pPortmask);

    if ((retVal = rtksw_switch_portmask_L2P_get(unit, pPortmask, &pmask)) != RT_ERR_OK)
        return retVal;

    if ((retVal = rtl8367c_setAsicPortIsolationPermittedPortmask(unit, rtksw_switch_port_L2P_get(unit, port), pmask)) != RT_ERR_OK)
        return retVal;

    return RT_ERR_OK;
}

/* Function Name:
 *      dal_rtl8367c_port_isolation_get
 * Description:
 *      Get permitted port isolation portmask
 * Input:
 *      unit    - Unit ID
 *      port    - Port id.
 * Output:
 *      pPortmask - Permit port mask
 * Return:
 *      RT_ERR_OK           - OK
 *      RT_ERR_FAILED       - Failed
 *      RT_ERR_SMI          - SMI access error
 *      RT_ERR_PORT_ID      - Invalid port number.
 * Note:
 *      This API get the port mask that a port can trasmit packet to of each port
 *      A port can only transmit packet to ports included in permitted portmask
 */
rtksw_api_ret_t dal_rtl8367c_port_isolation_get(rtksw_uint32 unit, rtksw_port_t port, rtksw_portmask_t *pPortmask)
{
    rtksw_api_ret_t retVal;
    rtksw_uint32 pmask;

    /* Check initialization state */
    RTKSW_CHK_INIT_STATE(unit);

    /* Check Port Valid */
    RTKSW_CHK_PORT_VALID(unit, port);

    if(NULL == pPortmask)
        return RT_ERR_NULL_POINTER;

    if ((retVal = rtl8367c_getAsicPortIsolationPermittedPortmask(unit, rtksw_switch_port_L2P_get(unit, port), &pmask)) != RT_ERR_OK)
        return retVal;

    if ((retVal = rtksw_switch_portmask_P2L_get(unit, pmask, pPortmask)) != RT_ERR_OK)
        return retVal;

    return RT_ERR_OK;
}

/* Function Name:
 *      dal_rtl8367c_port_rgmiiDelayExt_set
 * Description:
 *      Set RGMII interface delay value for TX and RX.
 * Input:
 *      unit    - Unit ID
 *      txDelay - TX delay value, 1 for delay 2ns and 0 for no-delay
 *      rxDelay - RX delay value, 0~7 for delay setup.
 * Output:
 *      None
 * Return:
 *      RT_ERR_OK           - OK
 *      RT_ERR_FAILED       - Failed
 *      RT_ERR_SMI          - SMI access error
 *      RT_ERR_INPUT        - Invalid input parameters.
 * Note:
 *      This API can set external interface 2 RGMII delay.
 *      In TX delay, there are 2 selection: no-delay and 2ns delay.
 *      In RX dekay, there are 8 steps for delay tunning. 0 for no-delay, and 7 for maximum delay.
 *      Note. This API should be called before rtksw_port_macForceLinkExt_set().
 */
rtksw_api_ret_t dal_rtl8367c_port_rgmiiDelayExt_set(rtksw_uint32 unit, rtksw_port_t port, rtksw_data_t txDelay, rtksw_data_t rxDelay)
{
    rtksw_api_ret_t retVal;
    rtksw_uint32 regAddr, regData;

    /* Check initialization state */
    RTKSW_CHK_INIT_STATE(unit);

    /* Check Port Valid */
    RTKSW_CHK_PORT_IS_EXT(unit, port);

    if ((txDelay > 1) || (rxDelay > 7))
        return RT_ERR_INPUT;

    if(port == EXT_PORT0)
        regAddr = RTL8367C_REG_EXT1_RGMXF;
    else if(port == EXT_PORT1)
        regAddr = RTL8367C_REG_EXT2_RGMXF;
    else
        return RT_ERR_INPUT;

    if ((retVal = rtl8367c_getAsicReg(unit, regAddr, &regData)) != RT_ERR_OK)
        return retVal;

    regData = (regData & 0xFFF0) | ((txDelay << 3) & 0x0008) | (rxDelay & 0x0007);

    if ((retVal = rtl8367c_setAsicReg(unit, regAddr, regData)) != RT_ERR_OK)
        return retVal;

    return RT_ERR_OK;
}

/* Function Name:
 *      dal_rtl8367c_port_rgmiiDelayExt_get
 * Description:
 *      Get RGMII interface delay value for TX and RX.
 * Input:
 *      unit    - Unit ID
 *      port    - Port ID
 * Output:
 *      pTxDelay - TX delay value
 *      pRxDelay - RX delay value
 * Return:
 *      RT_ERR_OK           - OK
 *      RT_ERR_FAILED       - Failed
 *      RT_ERR_SMI          - SMI access error
 *      RT_ERR_INPUT        - Invalid input parameters.
 * Note:
 *      This API can set external interface 2 RGMII delay.
 *      In TX delay, there are 2 selection: no-delay and 2ns delay.
 *      In RX dekay, there are 8 steps for delay tunning. 0 for n0-delay, and 7 for maximum delay.
 */
rtksw_api_ret_t dal_rtl8367c_port_rgmiiDelayExt_get(rtksw_uint32 unit, rtksw_port_t port, rtksw_data_t *pTxDelay, rtksw_data_t *pRxDelay)
{
    rtksw_api_ret_t retVal;
    rtksw_uint32 regAddr, regData;

    /* Check initialization state */
    RTKSW_CHK_INIT_STATE(unit);

    /* Check Port Valid */
    RTKSW_CHK_PORT_IS_EXT(unit, port);

    if( (NULL == pTxDelay) || (NULL == pRxDelay) )
        return RT_ERR_NULL_POINTER;

    if(port == EXT_PORT0)
        regAddr = RTL8367C_REG_EXT1_RGMXF;
    else if(port == EXT_PORT1)
        regAddr = RTL8367C_REG_EXT2_RGMXF;
    else
        return RT_ERR_INPUT;

    if ((retVal = rtl8367c_getAsicReg(unit, regAddr, &regData)) != RT_ERR_OK)
        return retVal;

    *pTxDelay = (regData & 0x0008) >> 3;
    *pRxDelay = regData & 0x0007;

    return RT_ERR_OK;
}

/* Function Name:
 *      dal_rtl8367c_port_phyEnableAll_set
 * Description:
 *      Set all PHY enable status.
 * Input:
 *      unit    - Unit ID
 *      enable  - PHY Enable State.
 * Output:
 *      None
 * Return:
 *      RT_ERR_OK           - OK
 *      RT_ERR_FAILED       - Failed
 *      RT_ERR_SMI          - SMI access error
 *      RT_ERR_ENABLE       - Invalid enable input.
 * Note:
 *      This API can set all PHY status.
 *      The configuration of all PHY is as following:
 *      - DISABLE
 *      - ENABLE
 */
rtksw_api_ret_t dal_rtl8367c_port_phyEnableAll_set(rtksw_uint32 unit, rtksw_enable_t enable)
{
    rtksw_api_ret_t retVal;
    rtksw_uint32 data;
    rtksw_uint32 port;

    /* Check initialization state */
    RTKSW_CHK_INIT_STATE(unit);

    if (enable >= RTKSW_ENABLE_END)
        return RT_ERR_ENABLE;

    if ((retVal = rtl8367c_setAsicPortEnableAll(unit, enable)) != RT_ERR_OK)
        return retVal;

    RTKSW_SCAN_ALL_LOG_PORT(unit, port)
    {
        if(rtksw_switch_isUtpPort(unit, port) == RT_ERR_OK)
        {
            if ((retVal = dal_rtl8367c_port_phyReg_get(unit, port, PHY_CONTROL_REG, &data)) != RT_ERR_OK)
                return retVal;

            if (RTKSW_ENABLED == enable)
            {
                data &= 0xF7FF;
                data |= 0x0200;
            }
            else
            {
                data |= 0x0800;
            }

            if ((retVal = dal_rtl8367c_port_phyReg_set(unit, port, PHY_CONTROL_REG, data)) != RT_ERR_OK)
                return retVal;
        }
    }

    return RT_ERR_OK;

}

/* Function Name:
 *      dal_rtl8367c_port_phyEnableAll_get
 * Description:
 *      Get all PHY enable status.
 * Input:
 *      unit    - Unit ID
 * Output:
 *      pEnable - PHY Enable State.
 * Return:
 *      RT_ERR_OK           - OK
 *      RT_ERR_FAILED       - Failed
 *      RT_ERR_SMI          - SMI access error
 * Note:
 *      This API can set all PHY status.
 *      The configuration of all PHY is as following:
 *      - DISABLE
 *      - ENABLE
 */
rtksw_api_ret_t dal_rtl8367c_port_phyEnableAll_get(rtksw_uint32 unit, rtksw_enable_t *pEnable)
{
    rtksw_api_ret_t retVal;

    /* Check initialization state */
    RTKSW_CHK_INIT_STATE(unit);

    if(NULL == pEnable)
        return RT_ERR_NULL_POINTER;

    if ((retVal = rtl8367c_getAsicPortEnableAll(unit, pEnable)) != RT_ERR_OK)
        return retVal;

    return RT_ERR_OK;
}

/* Function Name:
 *      dal_rtl8367c_port_efid_set
 * Description:
 *      Set port-based enhanced filtering database
 * Input:
 *      unit    - Unit ID
 *      port    - Port id.
 *      efid    - Specified enhanced filtering database.
 * Output:
 *      None
 * Return:
 *      RT_ERR_OK              - OK
 *      RT_ERR_FAILED          - Failed
 *      RT_ERR_SMI             - SMI access error
 *      RT_ERR_L2_FID - Invalid fid.
 *      RT_ERR_INPUT - Invalid input parameter.
 *      RT_ERR_PORT_ID - Invalid port ID.
 * Note:
 *      The API can set port-based enhanced filtering database.
 */
rtksw_api_ret_t dal_rtl8367c_port_efid_set(rtksw_uint32 unit, rtksw_port_t port, rtksw_data_t efid)
{
    rtksw_api_ret_t retVal;

    /* Check initialization state */
    RTKSW_CHK_INIT_STATE(unit);

    /* Check Port Valid */
    RTKSW_CHK_PORT_VALID(unit, port);

    /* efid must be 0~7 */
    if (efid > RTL8367C_EFID_MAX)
        return RT_ERR_INPUT;

    if ((retVal = rtl8367c_setAsicPortIsolationEfid(unit, rtksw_switch_port_L2P_get(unit, port), efid))!=RT_ERR_OK)
        return retVal;

    return RT_ERR_OK;
}

/* Function Name:
 *      dal_rtl8367c_port_efid_get
 * Description:
 *      Get port-based enhanced filtering database
 * Input:
 *      unit    - Unit ID
 *      port    - Port id.
 * Output:
 *      pEfid   - Specified enhanced filtering database.
 * Return:
 *      RT_ERR_OK              - OK
 *      RT_ERR_FAILED          - Failed
 *      RT_ERR_SMI             - SMI access error
 *      RT_ERR_INPUT - Invalid input parameters.
 *      RT_ERR_PORT_ID - Invalid port ID.
 * Note:
 *      The API can get port-based enhanced filtering database status.
 */
rtksw_api_ret_t dal_rtl8367c_port_efid_get(rtksw_uint32 unit, rtksw_port_t port, rtksw_data_t *pEfid)
{
    rtksw_api_ret_t retVal;

    /* Check initialization state */
    RTKSW_CHK_INIT_STATE(unit);

    /* Check Port Valid */
    RTKSW_CHK_PORT_VALID(unit, port);

    if(NULL == pEfid)
        return RT_ERR_NULL_POINTER;

    if ((retVal = rtl8367c_getAsicPortIsolationEfid(unit, rtksw_switch_port_L2P_get(unit, port), pEfid))!=RT_ERR_OK)
        return retVal;

    return RT_ERR_OK;
}

/* Function Name:
 *      dal_rtl8367c_port_phyComboPortMedia_set
 * Description:
 *      Set Combo port media type
 * Input:
 *      unit    - Unit ID
 *      port    - Port id.
 *      media   - Media (COPPER or FIBER or AUTO)
 * Output:
 *      None.
 * Return:
 *      RT_ERR_OK               - OK
 *      RT_ERR_FAILED           - Failed
 *      RT_ERR_SMI              - SMI access error
 *      RT_ERR_INPUT            - Invalid input parameters.
 *      RT_ERR_PORT_ID          - Invalid port ID.
 * Note:
 *      The API can Set Combo port media type.
 */
rtksw_api_ret_t dal_rtl8367c_port_phyComboPortMedia_set(rtksw_uint32 unit, rtksw_port_t port, rtksw_port_media_t media)
{
    rtksw_api_ret_t retVal;
    rtksw_uint32 regData;
    rtksw_uint32 idx;

    /* Check initialization state */
    RTKSW_CHK_INIT_STATE(unit);

    /* Check Port Valid */
    RTKSW_CHK_PORT_IS_UTP(unit, port);

    /* Check Combo Port ID */
    RTKSW_CHK_PORT_IS_COMBO(unit, port);

    if((retVal = rtl8367c_setAsicReg(unit, 0x13C2, 0x0249)) != RT_ERR_OK)
        return retVal;

    if((retVal = rtl8367c_getAsicReg(unit, 0x1300, &regData)) != RT_ERR_OK)
        return retVal;

    if((retVal = rtl8367c_setAsicReg(unit, 0x13C2, 0x0000)) != RT_ERR_OK)
        return retVal;

    if(regData != 0x6367)
        return RT_ERR_CHIP_NOT_SUPPORTED;

    if(media == RTKSW_PORT_MEDIA_FIBER)
    {
        /* software init */
        if ((retVal = rtl8367c_setAsicRegBit(unit, RTL8367C_REG_CHIP_RESET, RTL8367C_DW8051_RST_OFFSET, 1)) != RT_ERR_OK)
            return retVal;

        if ((retVal = rtl8367c_setAsicRegBit(unit, RTL8367C_REG_MISCELLANEOUS_CONFIGURE0, RTL8367C_DW8051_EN_OFFSET, 1)) != RT_ERR_OK)
            return retVal;

        if ((retVal = rtl8367c_setAsicRegBit(unit, RTL8367C_REG_DW8051_RDY, RTL8367C_ACS_IROM_ENABLE_OFFSET, 1)) != RT_ERR_OK)
            return retVal;

        if ((retVal = rtl8367c_setAsicRegBit(unit, RTL8367C_REG_DW8051_RDY, RTL8367C_IROM_MSB_OFFSET, 0)) != RT_ERR_OK)
            return retVal;

        for(idx = 0; idx < FIBER_INIT_SIZE; idx++)
        {
            if ((retVal = rtl8367c_setAsicReg(unit, 0xE000 + idx, (rtksw_uint32)Fiber[idx])) != RT_ERR_OK)
                return retVal;
        }

        if ((retVal = rtl8367c_setAsicRegBit(unit, RTL8367C_REG_DW8051_RDY, RTL8367C_IROM_MSB_OFFSET, 0)) != RT_ERR_OK)
            return retVal;

        if ((retVal = rtl8367c_setAsicRegBit(unit, RTL8367C_REG_DW8051_RDY, RTL8367C_ACS_IROM_ENABLE_OFFSET, 0)) != RT_ERR_OK)
            return retVal;

        if ((retVal = rtl8367c_setAsicRegBit(unit, RTL8367C_REG_CHIP_RESET, RTL8367C_DW8051_RST_OFFSET, 0)) != RT_ERR_OK)
            return retVal;
    }
    else if(media == RTKSW_PORT_MEDIA_AUTO)
    {
        /* software init */
        if ((retVal = rtl8367c_setAsicRegBit(unit, RTL8367C_REG_CHIP_RESET, RTL8367C_DW8051_RST_OFFSET, 1)) != RT_ERR_OK)
            return retVal;

        if ((retVal = rtl8367c_setAsicRegBit(unit, RTL8367C_REG_MISCELLANEOUS_CONFIGURE0, RTL8367C_DW8051_EN_OFFSET, 1)) != RT_ERR_OK)
            return retVal;

        if ((retVal = rtl8367c_setAsicRegBit(unit, RTL8367C_REG_DW8051_RDY, RTL8367C_ACS_IROM_ENABLE_OFFSET, 1)) != RT_ERR_OK)
            return retVal;

        if ((retVal = rtl8367c_setAsicRegBit(unit, RTL8367C_REG_DW8051_RDY, RTL8367C_IROM_MSB_OFFSET, 0)) != RT_ERR_OK)
            return retVal;

        for(idx = 0; idx < FIBER_AUTO_INIT_SIZE; idx++)
        {
            if ((retVal = rtl8367c_setAsicReg(unit, 0xE000 + idx, (rtksw_uint32)Fiber_auto[idx])) != RT_ERR_OK)
                return retVal;
        }

        if ((retVal = rtl8367c_setAsicRegBit(unit, RTL8367C_REG_DW8051_RDY, RTL8367C_IROM_MSB_OFFSET, 0)) != RT_ERR_OK)
            return retVal;

        if ((retVal = rtl8367c_setAsicRegBit(unit, RTL8367C_REG_DW8051_RDY, RTL8367C_ACS_IROM_ENABLE_OFFSET, 0)) != RT_ERR_OK)
            return retVal;

        if ((retVal = rtl8367c_setAsicRegBit(unit, RTL8367C_REG_CHIP_RESET, RTL8367C_DW8051_RST_OFFSET, 0)) != RT_ERR_OK)
            return retVal;
    }
    else if(media == RTKSW_PORT_MEDIA_COPPER)
    {
        if ((retVal = rtl8367c_setAsicRegBit(unit, RTL8367C_REG_UTP_FIB_DET, RTL8367C_UTP_FIRST_OFFSET, 1))!=RT_ERR_OK)
            return retVal;

        if ((retVal = rtl8367c_setAsicRegBit(unit, RTL8367C_REG_DW8051_RDY, RTL8367C_DW8051_READY_OFFSET, 0)) != RT_ERR_OK)
            return retVal;
    }
    else
        return RT_ERR_INPUT;

    return RT_ERR_OK;
}

/* Function Name:
 *      dal_rtl8367c_port_phyComboPortMedia_get
 * Description:
 *      Get Combo port media type
 * Input:
 *      unit    - Unit ID
 *      port    - Port id.
 * Output:
 *      pMedia  - Media (COPPER or FIBER or AUTO)
 * Return:
 *      RT_ERR_OK               - OK
 *      RT_ERR_FAILED           - Failed
 *      RT_ERR_SMI              - SMI access error
 *      RT_ERR_INPUT            - Invalid input parameters.
 *      RT_ERR_PORT_ID          - Invalid port ID.
 * Note:
 *      The API can Set Combo port media type.
 */
rtksw_api_ret_t dal_rtl8367c_port_phyComboPortMedia_get(rtksw_uint32 unit, rtksw_port_t port, rtksw_port_media_t *pMedia)
{
    rtksw_api_ret_t   retVal;
    rtksw_uint32      regData;
    rtksw_uint32      data;

    /* Check initialization state */
    RTKSW_CHK_INIT_STATE(unit);

    /* Check Port Valid */
    RTKSW_CHK_PORT_IS_UTP(unit, port);

    /* Check Combo Port ID */
    RTKSW_CHK_PORT_IS_COMBO(unit, port);

    if((retVal = rtl8367c_setAsicReg(unit, 0x13C2, 0x0249)) != RT_ERR_OK)
        return retVal;

    if((retVal = rtl8367c_getAsicReg(unit, 0x1300, &regData)) != RT_ERR_OK)
        return retVal;

    if((retVal = rtl8367c_setAsicReg(unit, 0x13C2, 0x0000)) != RT_ERR_OK)
        return retVal;

    if(regData != 0x6367)
    {
        *pMedia = RTKSW_PORT_MEDIA_COPPER;
    }
    else
    {
        if ((retVal = rtl8367c_getAsicRegBit(unit, RTL8367C_REG_UTP_FIB_DET, RTL8367C_UTP_FIB_DISAUTODET_OFFSET, &data))!=RT_ERR_OK)
                return retVal;
        if(data == 0)
        {
            *pMedia = RTKSW_PORT_MEDIA_AUTO;
        }
        else
        {
            if ((retVal = rtl8367c_getAsicRegBit(unit, RTL8367C_REG_UTP_FIB_DET, RTL8367C_UTP_FIRST_OFFSET, &data))!=RT_ERR_OK)
                    return retVal;

            if(data == 1)
                *pMedia = RTKSW_PORT_MEDIA_COPPER;
            else
                *pMedia = RTKSW_PORT_MEDIA_FIBER;
        }
    }

    return RT_ERR_OK;
}

/* Function Name:
 *      dal_rtl8367c_port_rtctEnable_set
 * Description:
 *      Enable RTCT test
 * Input:
 *      unit        - Unit ID
 *      pPortmask   - Port mask of RTCT enabled port
 * Output:
 *      None
 * Return:
 *      RT_ERR_OK               - OK
 *      RT_ERR_FAILED           - Failed
 *      RT_ERR_SMI              - SMI access error
 *      RT_ERR_PORT_MASK        - Invalid port mask.
 * Note:
 *      The API can enable RTCT Test
 */
rtksw_api_ret_t dal_rtl8367c_port_rtctEnable_set(rtksw_uint32 unit, rtksw_portmask_t *pPortmask)
{
    rtksw_api_ret_t   retVal;

    /* Check initialization state */
    RTKSW_CHK_INIT_STATE(unit);

    /* Check Port Mask Valid */
    RTKSW_CHK_PORTMASK_VALID_ONLY_UTP(unit, pPortmask);

    if ((retVal = rtl8367c_setAsicPortRTCTEnable(unit, pPortmask->bits[0]))!=RT_ERR_OK)
        return retVal;

    return RT_ERR_OK;
}

/* Function Name:
 *      dal_rtl8367c_port_rtctDisable_set
 * Description:
 *      Disable RTCT test
 * Input:
 *      unit        - Unit ID
 *      pPortmask   - Port mask of RTCT disabled port
 * Output:
 *      None
 * Return:
 *      RT_ERR_OK               - OK
 *      RT_ERR_FAILED           - Failed
 *      RT_ERR_SMI              - SMI access error
 *      RT_ERR_PORT_MASK        - Invalid port mask.
 * Note:
 *      The API can disable RTCT Test
 */
rtksw_api_ret_t dal_rtl8367c_port_rtctDisable_set(rtksw_uint32 unit, rtksw_portmask_t *pPortmask)
{
    rtksw_api_ret_t   retVal;

    /* Check initialization state */
    RTKSW_CHK_INIT_STATE(unit);

    /* Check Port Mask Valid */
    RTKSW_CHK_PORTMASK_VALID_ONLY_UTP(unit, pPortmask);

    if ((retVal = rtl8367c_setAsicPortRTCTDisable(unit, pPortmask->bits[0]))!=RT_ERR_OK)
        return retVal;

    return RT_ERR_OK;
}

/* Function Name:
 *      dal_rtl8367c_port_rtctResult_get
 * Description:
 *      Get the result of RTCT test
 * Input:
 *      unit    - Unit ID
 *      port    - Port ID
 * Output:
 *      pRtctResult - The result of RTCT result
 * Return:
 *      RT_ERR_OK                   - OK
 *      RT_ERR_FAILED               - Failed
 *      RT_ERR_SMI                  - SMI access error
 *      RT_ERR_PORT_ID              - Invalid port ID.
 *      RT_ERR_PHY_RTCT_NOT_FINISH  - Testing does not finish.
 * Note:
 *      The API can get RTCT test result.
 *      RTCT test may takes 4.8 seconds to finish its test at most.
 *      Thus, if this API return RT_ERR_PHY_RTCT_NOT_FINISH or
 *      other error code, the result can not be referenced and
 *      user should call this API again until this API returns
 *      a RT_ERR_OK.
 *      The result is stored at pRtctResult->ge_result
 *      pRtctResult->linkType is unused.
 *      The unit of channel length is 2.5cm. Ex. 300 means 300 * 2.5 = 750cm = 7.5M
 */
rtksw_api_ret_t dal_rtl8367c_port_rtctResult_get(rtksw_uint32 unit, rtksw_port_t port, rtksw_rtctResult_t *pRtctResult)
{
    rtksw_api_ret_t               retVal;
    rtl8367c_port_rtct_result_t result;

    /* Check initialization state */
    RTKSW_CHK_INIT_STATE(unit);

    /* Check Port Valid */
    RTKSW_CHK_PORT_IS_UTP(unit, port);

    osal_memset(pRtctResult, 0x00, sizeof(rtksw_rtctResult_t));
    if ((retVal = rtl8367c_getAsicPortRTCTResult(unit, port, &result))!=RT_ERR_OK)
        return retVal;

    pRtctResult->result.ge_result.channelALen = result.channelALen;
    pRtctResult->result.ge_result.channelBLen = result.channelBLen;
    pRtctResult->result.ge_result.channelCLen = result.channelCLen;
    pRtctResult->result.ge_result.channelDLen = result.channelDLen;

    pRtctResult->result.ge_result.channelALinedriver = result.channelALinedriver;
    pRtctResult->result.ge_result.channelBLinedriver = result.channelBLinedriver;
    pRtctResult->result.ge_result.channelCLinedriver = result.channelCLinedriver;
    pRtctResult->result.ge_result.channelDLinedriver = result.channelDLinedriver;

    pRtctResult->result.ge_result.channelAMismatch = result.channelAMismatch;
    pRtctResult->result.ge_result.channelBMismatch = result.channelBMismatch;
    pRtctResult->result.ge_result.channelCMismatch = result.channelCMismatch;
    pRtctResult->result.ge_result.channelDMismatch = result.channelDMismatch;

    pRtctResult->result.ge_result.channelAOpen = result.channelAOpen;
    pRtctResult->result.ge_result.channelBOpen = result.channelBOpen;
    pRtctResult->result.ge_result.channelCOpen = result.channelCOpen;
    pRtctResult->result.ge_result.channelDOpen = result.channelDOpen;

    pRtctResult->result.ge_result.channelAShort = result.channelAShort;
    pRtctResult->result.ge_result.channelBShort = result.channelBShort;
    pRtctResult->result.ge_result.channelCShort = result.channelCShort;
    pRtctResult->result.ge_result.channelDShort = result.channelDShort;

    return RT_ERR_OK;
}

/* Function Name:
 *      dal_rtl8367c_port_sds_reset
 * Description:
 *      Reset Serdes
 * Input:
 *      unit    - Unit ID
 *      port    - Port ID
 * Output:
 *      None.
 * Return:
 *      RT_ERR_OK                   - OK
 *      RT_ERR_FAILED               - Failed
 *      RT_ERR_SMI                  - SMI access error
 *      RT_ERR_PORT_ID              - Invalid port ID.
 * Note:
 *      The API can reset Serdes
 */
rtksw_api_ret_t dal_rtl8367c_port_sds_reset(rtksw_uint32 unit, rtksw_port_t port)
{
    rtksw_uint32 ext_id;

    /* Check initialization state */
    RTKSW_CHK_INIT_STATE(unit);

    /* Check Port Valid */
    if(rtksw_switch_isSgmiiPort(unit, port) != RT_ERR_OK)
        return RT_ERR_PORT_ID;

    ext_id = port - 15;
    return rtl8367c_sdsReset(unit, ext_id);
}

/* Function Name:
 *      dal_rtl8367c_port_sgmiiLinkStatus_get
 * Description:
 *      Get SGMII status
 * Input:
 *      unit        - Unit ID
 *      port        - Port ID
 * Output:
 *      pSignalDetect   - Signal detect
 *      pSync           - Sync
 *      pLink           - Link
 * Return:
 *      RT_ERR_OK                   - OK
 *      RT_ERR_FAILED               - Failed
 *      RT_ERR_SMI                  - SMI access error
 *      RT_ERR_PORT_ID              - Invalid port ID.
 * Note:
 *      The API can reset Serdes
 */
rtksw_api_ret_t dal_rtl8367c_port_sgmiiLinkStatus_get(rtksw_uint32 unit, rtksw_port_t port, rtksw_data_t *pSignalDetect, rtksw_data_t *pSync, rtksw_port_linkStatus_t *pLink)
{
    rtksw_uint32 ext_id;

    /* Check initialization state */
    RTKSW_CHK_INIT_STATE(unit);

    /* Check Port Valid */
    if(rtksw_switch_isSgmiiPort(unit, port) != RT_ERR_OK)
        return RT_ERR_PORT_ID;

    if(NULL == pSignalDetect)
        return RT_ERR_NULL_POINTER;

    if(NULL == pSync)
        return RT_ERR_NULL_POINTER;

    if(NULL == pLink)
        return RT_ERR_NULL_POINTER;

    ext_id = port - 15;
    return rtl8367c_getSdsLinkStatus(unit, ext_id, (rtksw_uint32 *)pSignalDetect, (rtksw_uint32 *)pSync, (rtksw_uint32 *)pLink);
}

/* Function Name:
 *      dal_rtl8367c_port_sgmiiNway_set
 * Description:
 *      Configure SGMII/HSGMII port Nway state
 * Input:
 *      unit        - Unit ID
 *      port        - Port ID
 *      state       - Nway state
 * Output:
 *      None.
 * Return:
 *      RT_ERR_OK                   - OK
 *      RT_ERR_FAILED               - Failed
 *      RT_ERR_SMI                  - SMI access error
 *      RT_ERR_PORT_ID              - Invalid port ID.
 * Note:
 *      The API configure SGMII/HSGMII port Nway state
 */
rtksw_api_ret_t dal_rtl8367c_port_sgmiiNway_set(rtksw_uint32 unit, rtksw_port_t port, rtksw_enable_t state)
{
    rtksw_uint32 ext_id;

     /* Check initialization state */
    RTKSW_CHK_INIT_STATE(unit);

    /* Check Port Valid */
    if(rtksw_switch_isSgmiiPort(unit, port) != RT_ERR_OK)
        return RT_ERR_PORT_ID;

    if(state >= RTKSW_ENABLE_END)
        return RT_ERR_INPUT;

    ext_id = port - 15;
    return rtl8367c_setSgmiiNway(unit, ext_id, (rtksw_uint32)state);
}

/* Function Name:
 *      dal_rtl8367c_port_sgmiiNway_get
 * Description:
 *      Get SGMII/HSGMII port Nway state
 * Input:
 *      unit        - Unit ID
 *      port        - Port ID
 * Output:
 *      pState      - Nway state
 * Return:
 *      RT_ERR_OK                   - OK
 *      RT_ERR_FAILED               - Failed
 *      RT_ERR_SMI                  - SMI access error
 *      RT_ERR_PORT_ID              - Invalid port ID.
 * Note:
 *      The API can get SGMII/HSGMII port Nway state
 */
rtksw_api_ret_t dal_rtl8367c_port_sgmiiNway_get(rtksw_uint32 unit, rtksw_port_t port, rtksw_enable_t *pState)
{
    rtksw_uint32 ext_id;

     /* Check initialization state */
    RTKSW_CHK_INIT_STATE(unit);

    /* Check Port Valid */
    if(rtksw_switch_isSgmiiPort(unit, port) != RT_ERR_OK)
        return RT_ERR_PORT_ID;

    if(NULL == pState)
        return RT_ERR_NULL_POINTER;

    ext_id = port - 15;
    return rtl8367c_getSgmiiNway(unit, ext_id, (rtksw_uint32 *)pState);
}


/* Function Name:
 *      dal_rtl8367c_port_fiberAbilityExt_set
 * Description:
 *      Get SGMII/HSGMII port Nway state
 * Input:
 *      unit        - Unit ID
 *      port        - Port ID
 *      pause       - pause state
 *      asypause    - asypause state
 * Output:
 *      None
 * Return:
 *      RT_ERR_OK                   - OK
 *      RT_ERR_FAILED               - Failed
 *      RT_ERR_SMI                  - SMI access error
 *      RT_ERR_PORT_ID              - Invalid port ID.
 * Note:
 *      The API can get SGMII/HSGMII port Nway state
 */
rtksw_api_ret_t dal_rtl8367c_port_fiberAbilityExt_set(rtksw_uint32 unit, rtksw_port_t port, rtksw_uint32 pause, rtksw_uint32 asypause)
{
    rtksw_uint32 ext_id;

    ext_id = port - 15;

    return rtl8367c_setFiberAbilityExt(unit, ext_id, pause, asypause);

}

/* Function Name:
 *      dal_rtl8367c_port_fiberAbilityExt_get
 * Description:
 *      Get SGMII/HSGMII port Nway state
 * Input:
 *      unit    - Unit ID
 *      port    - Port ID
 * Output:
 *      pPause      -pause state
 *      pAsypause -asypause state
 * Return:
 *      RT_ERR_OK                   - OK
 *      RT_ERR_FAILED               - Failed
 *      RT_ERR_SMI                  - SMI access error
 *      RT_ERR_PORT_ID              - Invalid port ID.
 * Note:
 *      The API can get SGMII/HSGMII port Nway state
 */
rtksw_api_ret_t dal_rtl8367c_port_fiberAbilityExt_get(rtksw_uint32 unit, rtksw_port_t port, rtksw_uint32* pPause, rtksw_uint32* pAsypause)
{
    rtksw_uint32 ext_id;

    ext_id = port - 15;

    return rtl8367c_getFiberAbilityExt(unit, ext_id, pPause, pAsypause);

}

/* Function Name:
 *      dal_rtl8367c_port_autoDos_set
 * Description:
 *      Set Auto Dos state
 * Input:
 *      unit        - Unit ID
 *      type        - Auto DoS type
 *      state       - 1: Eanble(Drop), 0: Disable(Forward)
 * Output:
 *      None
 * Return:
 *      RT_ERR_OK                   - OK
 *      RT_ERR_FAILED               - Failed
 *      RT_ERR_SMI                  - SMI access error
 * Note:
 *      The API can set Auto Dos state
 */
rtksw_api_ret_t dal_rtl8367c_port_autoDos_set(rtksw_uint32 unit, rtksw_port_autoDosType_t type, rtksw_enable_t state)
{
    rtksw_api_ret_t retVal;

    /* Check initialization state */
    RTKSW_CHK_INIT_STATE(unit);

    if (type >= AUTODOS_END)
        return RT_ERR_INPUT;

    if (state >= RTKSW_ENABLE_END)
        return RT_ERR_INPUT;

    if ((retVal = rtl8367c_setAsicRegBit(unit, RTL8367C_REG_DOS_CFG, RTL8367C_DROP_DAEQSA_OFFSET + type, (state == RTKSW_ENABLED) ? 1 : 0)) != RT_ERR_OK)
        return retVal;

    return RT_ERR_OK;
}

/* Function Name:
 *      dal_rtl8367c_port_autoDos_get
 * Description:
 *      Get Auto Dos state
 * Input:
 *      unit        - Unit ID
 *      type        - Auto DoS type
 * Output:
 *      pState      - 1: Eanble(Drop), 0: Disable(Forward)
 * Return:
 *      RT_ERR_OK                   - OK
 *      RT_ERR_FAILED               - Failed
 *      RT_ERR_SMI                  - SMI access error
 *      RT_ERR_NULL_POINTER         - Null Pointer
 * Note:
 *      The API can get Auto Dos state
 */
rtksw_api_ret_t dal_rtl8367c_port_autoDos_get(rtksw_uint32 unit, rtksw_port_autoDosType_t type, rtksw_enable_t *pState)
{
    rtksw_api_ret_t retVal;
    rtksw_uint32 regData;

    /* Check initialization state */
    RTKSW_CHK_INIT_STATE(unit);

    if (type >= AUTODOS_END)
        return RT_ERR_INPUT;

    if (pState == NULL)
        return RT_ERR_NULL_POINTER;

    if ((retVal = rtl8367c_getAsicRegBit(unit, RTL8367C_REG_DOS_CFG, RTL8367C_DROP_DAEQSA_OFFSET + type, &regData)) != RT_ERR_OK)
        return retVal;

    *pState = (regData == 1) ? RTKSW_ENABLED : RTKSW_DISABLED;
    return RT_ERR_OK;
}

/* Function Name:
 *      dal_rtl8367c_port_phyMdx_set
 * Description:
 *      Set PHY MDI/MDIX state
 * Input:
 *      unit        - Unit ID
 *      port        - port ID
 *      mode        - PHY MDI/MDIX mode
 * Output:
 *      None
 * Return:
 *      RT_ERR_OK                   - OK
 *      RT_ERR_FAILED               - Failed
 *      RT_ERR_SMI                  - SMI access error
 * Note:
 *      The API can set PHY MDI/MDIX state
 */
rtksw_api_ret_t dal_rtl8367c_port_phyMdx_set(rtksw_uint32 unit, rtksw_port_t port, rtksw_port_phy_mdix_mode_t mode)
{
    rtksw_uint32 regData;
    rtksw_api_ret_t retVal;

    /* Check initialization state */
    RTKSW_CHK_INIT_STATE(unit);

    /* Check Port Valid */
    RTKSW_CHK_PORT_IS_UTP(unit, port);

    switch (mode)
    {
        case PHY_AUTO_CROSSOVER_MODE:
            if ((retVal = rtl8367c_getAsicPHYReg(unit, rtksw_switch_port_L2P_get(unit, port), 24, &regData))!=RT_ERR_OK)
                return retVal;

            regData &= ~(0x0001 << 9);

            if ((retVal = rtl8367c_setAsicPHYReg(unit, rtksw_switch_port_L2P_get(unit, port), 24, regData))!=RT_ERR_OK)
                return retVal;
            break;
        case PHY_FORCE_MDI_MODE:
            if ((retVal = rtl8367c_getAsicPHYReg(unit, rtksw_switch_port_L2P_get(unit, port), 24, &regData))!=RT_ERR_OK)
                return retVal;

            regData |= (0x0001 << 9);
            regData |= (0x0001 << 8);

            if ((retVal = rtl8367c_setAsicPHYReg(unit, rtksw_switch_port_L2P_get(unit, port), 24, regData))!=RT_ERR_OK)
                return retVal;
            break;
        case PHY_FORCE_MDIX_MODE:
            if ((retVal = rtl8367c_getAsicPHYReg(unit, rtksw_switch_port_L2P_get(unit, port), 24, &regData))!=RT_ERR_OK)
                return retVal;

            regData |= (0x0001 << 9);
            regData &= ~(0x0001 << 8);

            if ((retVal = rtl8367c_setAsicPHYReg(unit, rtksw_switch_port_L2P_get(unit, port), 24, regData))!=RT_ERR_OK)
                return retVal;
            break;
        default:
            return RT_ERR_INPUT;
            break;
    }

    /* Restart N-way */
    if ((retVal = rtl8367c_getAsicPHYReg(unit, rtksw_switch_port_L2P_get(unit, port), 0, &regData))!=RT_ERR_OK)
        return retVal;

    regData |= (0x0001 << 9);

    if ((retVal = rtl8367c_setAsicPHYReg(unit, rtksw_switch_port_L2P_get(unit, port), 0, regData))!=RT_ERR_OK)
        return retVal;

    return RT_ERR_OK;
}

/* Function Name:
 *      dal_rtl8367c_port_phyMdx_get
 * Description:
 *      Get PHY MDI/MDIX state
 * Input:
 *      unit        - Unit ID
 *      port        - port ID
 * Output:
 *      pMode       - PHY MDI/MDIX mode
 * Return:
 *      RT_ERR_OK                   - OK
 *      RT_ERR_FAILED               - Failed
 *      RT_ERR_SMI                  - SMI access error
 * Note:
 *      The API can get PHY MDI/MDIX state
 */
rtksw_api_ret_t dal_rtl8367c_port_phyMdx_get(rtksw_uint32 unit, rtksw_port_t port, rtksw_port_phy_mdix_mode_t *pMode)
{
    rtksw_uint32 regData;
    rtksw_api_ret_t retVal;

    if ((retVal = rtl8367c_getAsicPHYReg(unit, rtksw_switch_port_L2P_get(unit, port), 24, &regData))!=RT_ERR_OK)
        return retVal;

    if(regData & (0x0001 << 9))
    {
        if(regData & (0x0001 << 8))
            *pMode = PHY_FORCE_MDI_MODE;
        else
            *pMode = PHY_FORCE_MDIX_MODE;
    }
    else
        *pMode = PHY_AUTO_CROSSOVER_MODE;

    return RT_ERR_OK;
}

/* Function Name:
 *      dal_rtl8367c_port_phyMdxStatus_get
 * Description:
 *      Get PHY MDI/MDIX status
 * Input:
 *      unit        - Unit ID
 *      port        - port ID
 * Output:
 *      pStatus     - PHY MDI/MDIX status
 * Return:
 *      RT_ERR_OK                   - OK
 *      RT_ERR_FAILED               - Failed
 *      RT_ERR_SMI                  - SMI access error
 * Note:
 *      The API can get PHY MDI/MDIX status
 */
rtksw_api_ret_t dal_rtl8367c_port_phyMdxStatus_get(rtksw_uint32 unit, rtksw_port_t port, rtksw_port_phy_mdix_status_t *pStatus)
{
    rtksw_uint32 regData;
    rtksw_api_ret_t retVal;

    if ((retVal = rtl8367c_getAsicPHYReg(unit, rtksw_switch_port_L2P_get(unit, port), 24, &regData))!=RT_ERR_OK)
        return retVal;

    if (regData & (0x0001 << 9))
    {
        if (regData & (0x0001 << 8))
            *pStatus = PHY_STATUS_FORCE_MDI_MODE;
        else
            *pStatus = PHY_STATUS_FORCE_MDIX_MODE;
    }
    else
    {
        if ((retVal = rtl8367c_getAsicPHYReg(unit, rtksw_switch_port_L2P_get(unit, port), 26, &regData))!=RT_ERR_OK)
            return retVal;

        if (regData & (0x0001 << 1))
            *pStatus = PHY_STATUS_AUTO_MDI_MODE;
        else
            *pStatus = PHY_STATUS_AUTO_MDIX_MODE;
    }

    return RT_ERR_OK;
}

/* Function Name:
 *      dal_rtl8367c_port_phyTestMode_set
 * Description:
 *      Set PHY in test mode.
 * Input:
 *      unit    - Unit ID
 *      port    - port id.
 *      mode    - PHY test mode 0:normal 1:test mode 1 2:test mode 2 3: test mode 3 4:test mode 4 5~7:reserved
 * Output:
 *      None
 * Return:
 *      RT_ERR_OK               - OK
 *      RT_ERR_FAILED           - Failed
 *      RT_ERR_SMI              - SMI access error
 *      RT_ERR_PORT_ID          - Invalid port number.
 *      RT_ERR_BUSYWAIT_TIMEOUT - PHY access busy
 *      RT_ERR_NOT_ALLOWED      - The Setting is not allowed, caused by set more than 1 port in Test mode.
 * Note:
 *      Set PHY in test mode and only one PHY can be in test mode at the same time.
 *      It means API will return FAILED if other PHY is in test mode.
 *      This API only provide test mode 1 & 4 setup.
 */
rtksw_api_ret_t dal_rtl8367c_port_phyTestMode_set(rtksw_uint32 unit, rtksw_port_t port, rtksw_port_phy_test_mode_t mode)
{
    rtksw_uint32          data, regData, i;
    rtksw_api_ret_t       retVal;

    RTKSW_CHK_PORT_IS_UTP(unit, port);

    if(mode >= RTKSW_PHY_2P5G_TEST_MODE_1)
        return RT_ERR_INPUT;

    if( (mode == RTKSW_PHY_TEST_MODE_2) || (mode == RTKSW_PHY_TEST_MODE_3) )
        return RT_ERR_INPUT;

    if (RTKSW_PHY_TEST_MODE_NORMAL != mode)
    {
        /* Other port should be Normal mode */
        RTKSW_SCAN_ALL_LOG_PORT(unit, i)
        {
            if(rtksw_switch_isUtpPort(unit, i) == RT_ERR_OK)
            {
                if(i != port)
                {
                    if ((retVal = rtl8367c_getAsicPHYReg(unit, rtksw_switch_port_L2P_get(unit, i), 9, &data)) != RT_ERR_OK)
                        return retVal;

                    if((data & 0xE000) != 0)
                        return RT_ERR_NOT_ALLOWED;
                }
            }
        }
    }

    if (RTKSW_PHY_TEST_MODE_4 == mode)
    {
        if((retVal = rtl8367c_setAsicReg(unit, 0x13C2, 0x0249)) != RT_ERR_OK)
            return retVal;

        if((retVal = rtl8367c_getAsicReg(unit, 0x1300, &regData)) != RT_ERR_OK)
            return retVal;

        if(regData == 0x6511)
        {
            if ((retVal = rtl8367c_setAsicPHYOCPReg(unit, rtksw_switch_port_L2P_get(unit, port), 0xa436, 0x8081)) != RT_ERR_OK)
                return retVal;

            if ((retVal = rtl8367c_setAsicPHYOCPReg(unit, rtksw_switch_port_L2P_get(unit, port), 0xa438, 0x7e00)) != RT_ERR_OK)
                return retVal;
        }
    }

    if ((retVal = rtl8367c_getAsicPHYReg(unit, rtksw_switch_port_L2P_get(unit, port), 9, &data)) != RT_ERR_OK)
        return retVal;

    data &= ~0xE000;
    data |= (mode << 13);
    if ((retVal = rtl8367c_setAsicPHYReg(unit, rtksw_switch_port_L2P_get(unit, port), 9, data)) != RT_ERR_OK)
        return retVal;

    if (RTKSW_PHY_TEST_MODE_4 == mode)
    {
        if((retVal = rtl8367c_setAsicReg(unit, 0x13C2, 0x0249)) != RT_ERR_OK)
            return retVal;

        if((retVal = rtl8367c_getAsicReg(unit, 0x1300, &regData)) != RT_ERR_OK)
            return retVal;

        if( (regData == 0x0276) || (regData == 0x0597) )
        {
            if ((retVal = rtl8367c_setAsicPHYOCPReg(unit, rtksw_switch_port_L2P_get(unit, port), 0xbcc2, 0xF4F4)) != RT_ERR_OK)
                return retVal;
        }

        if( (regData == 0x6367) )
        {
            if ((retVal = rtl8367c_setAsicPHYOCPReg(unit, rtksw_switch_port_L2P_get(unit, port), 0xa436, 0x80c1)) != RT_ERR_OK)
                return retVal;

            if ((retVal = rtl8367c_setAsicPHYOCPReg(unit, rtksw_switch_port_L2P_get(unit, port), 0xa438, 0xfe00)) != RT_ERR_OK)
                return retVal;
        }
    }

    return RT_ERR_OK;
}

/* Function Name:
 *      dal_rtl8367c_port_phyTestMode_get
 * Description:
 *      Get PHY in which test mode.
 * Input:
 *      unit    - Unit ID
 *      port    - Port id.
 * Output:
 *      mode - PHY test mode 0:normal 1:test mode 1 2:test mode 2 3: test mode 3 4:test mode 4 5~7:reserved
 * Return:
 *      RT_ERR_OK               - OK
 *      RT_ERR_FAILED           - Failed
 *      RT_ERR_SMI              - SMI access error
 *      RT_ERR_PORT_ID          - Invalid port number.
 *      RT_ERR_INPUT            - Invalid input parameters.
 *      RT_ERR_BUSYWAIT_TIMEOUT - PHY access busy
 * Note:
 *      Get test mode of PHY from register setting 9.15 to 9.13.
 */
rtksw_api_ret_t dal_rtl8367c_port_phyTestMode_get(rtksw_uint32 unit, rtksw_port_t port, rtksw_port_phy_test_mode_t *pMode)
{
    rtksw_uint32      data;
    rtksw_api_ret_t   retVal;

    RTKSW_CHK_PORT_IS_UTP(unit, port);

    if (pMode == NULL)
        return RT_ERR_NULL_POINTER;

    if ((retVal = rtl8367c_getAsicPHYReg(unit, rtksw_switch_port_L2P_get(unit, port), 9, &data)) != RT_ERR_OK)
        return retVal;

    *pMode = (data & 0xE000) >> 13;

    return RT_ERR_OK;
}

/* Function Name:
 *      dal_rtl8367c_port_phyGreenEthernet_set
 * Description:
 *      Set Ports Green Ethernet state.
 * Input:
 *      unit    - Unit ID
 *      port    - port ID
 *      state   - Green Ethernet state.
 * Output:
 *      None
 * Return:
 *      RT_ERR_OK       - OK
 *      RT_ERR_FAILED   - Failed
 *      RT_ERR_SMI      - SMI access error
 *      RT_ERR_ENABLE   - Invalid enable input.
 * Note:
 *      This API can set Port Green Ethernet state.
 *      The configuration is as following:
 *      - DISABLE
 *      - ENABLE
 */
rtksw_api_ret_t dal_rtl8367c_port_phyGreenEthernet_set(rtksw_uint32 unit, rtksw_port_t port, rtksw_enable_t state)
{
    rtksw_api_ret_t retVal;

    /* Check initialization state */
    RTKSW_CHK_INIT_STATE(unit);

    /* Check Port Valid */
    RTKSW_CHK_PORT_IS_UTP(unit, port);

    if (state >= RTKSW_ENABLE_END)
        return RT_ERR_ENABLE;

    if ((retVal = rtl8367c_setAsicGreenEthernet(unit, rtksw_switch_port_L2P_get(unit, port), state))!=RT_ERR_OK)
        return retVal;

    return retVal;
}

/* Function Name:
 *      dal_rtl8367c_port_phyGreenEthernet_get
 * Description:
 *      Get Ports Green Ethernet state.
 * Input:
 *      unit    - Unit ID
 *      port    - port ID
 * Output:
 *      pState  - Green Ethernet state.
 * Return:
 *      RT_ERR_OK              - OK
 *      RT_ERR_FAILED          - Failed
 *      RT_ERR_SMI             - SMI access error
 * Note:
 *      This API can get Green Ethernet state.
 */
rtksw_api_ret_t dal_rtl8367c_port_phyGreenEthernet_get(rtksw_uint32 unit, rtksw_port_t port, rtksw_enable_t *pState)
{
    rtksw_api_ret_t retVal;

    /* Check initialization state */
    RTKSW_CHK_INIT_STATE(unit);

    /* Check Port Valid */
    RTKSW_CHK_PORT_IS_UTP(unit, port);

    if (pState == NULL)
        return RT_ERR_NULL_POINTER;
    
    if ((retVal = rtl8367c_getAsicGreenEthernet(unit, rtksw_switch_port_L2P_get(unit, port), pState))!=RT_ERR_OK)
        return retVal;

    return retVal;
}

/* Function Name:
 *      dal_rtl8367c_port_phyLinkDownPowerSaving_set
 * Description:
 *      Set Ports Link Down Power Saving state.
 * Input:
 *      unit    - Unit ID
 *      port    - port ID
 *      state   - Link Down Power Saving state.
 * Output:
 *      None
 * Return:
 *      RT_ERR_OK       - OK
 *      RT_ERR_FAILED   - Failed
 *      RT_ERR_SMI      - SMI access error
 *      RT_ERR_ENABLE   - Invalid enable input.
 * Note:
 *      This API can set Port Link Down Power Saving state.
 *      The configuration is as following:
 *      - DISABLE
 *      - ENABLE
 */
rtksw_api_ret_t dal_rtl8367c_port_phyLinkDownPowerSaving_set(rtksw_uint32 unit, rtksw_port_t port, rtksw_enable_t state)
{
    rtksw_api_ret_t retVal;

    /* Check initialization state */
    RTKSW_CHK_INIT_STATE(unit);

    /* Check Port Valid */
    RTKSW_CHK_PORT_IS_UTP(unit, port);

    if (state >= RTKSW_ENABLE_END)
        return RT_ERR_ENABLE;

    if ((retVal = rtl8367c_setAsicPowerSaving(unit, rtksw_switch_port_L2P_get(unit, port), state))!=RT_ERR_OK)
        return retVal;        

    return retVal;
}

/* Function Name:
 *      dal_rtl8367c_port_phyLinkDownPowerSaving_get
 * Description:
 *      Get Ports Link Down Power Saving state.
 * Input:
 *      unit    - Unit ID
 *      port    - port ID
 * Output:
 *      pState  - Link Down Power Saving state.
 * Return:
 *      RT_ERR_OK              - OK
 *      RT_ERR_FAILED          - Failed
 *      RT_ERR_SMI             - SMI access error
 * Note:
 *      This API can get Link Down Power Saving state.
 */
rtksw_api_ret_t dal_rtl8367c_port_phyLinkDownPowerSaving_get(rtksw_uint32 unit, rtksw_port_t port, rtksw_enable_t *pState)
{
    rtksw_api_ret_t retVal;

    /* Check initialization state */
    RTKSW_CHK_INIT_STATE(unit);

    /* Check Port Valid */
    RTKSW_CHK_PORT_IS_UTP(unit, port);

    if (pState == NULL)
        return RT_ERR_NULL_POINTER;

    if ((retVal = rtl8367c_getAsicPowerSaving(unit, rtksw_switch_port_L2P_get(unit, port), pState))!=RT_ERR_OK)
        return retVal; 

    return retVal;
}

/* Function Name:
 *      dal_rtl8367c_port_serdesReg_set
 * Description:
 *      Set Serdes register data of the specific port.
 * Input:
 *      unit    - Unit ID
 *      port    - port id.
 *      page    - Page id.
 *      reg     - Register id
 *      regData - Register data
 * Output:
 *      None
 * Return:
 *      RT_ERR_OK               - OK
 *      RT_ERR_FAILED           - Failed
 *      RT_ERR_SMI              - SMI access error
 *      RT_ERR_INPUT            - Error input
 *      RT_ERR_BUSYWAIT_TIMEOUT - Access busy
 * Note:
 *      This API can set serdes register data of the specific sdsID.
 */
rtksw_api_ret_t dal_rtl8367c_port_serdesReg_set(rtksw_uint32 unit, rtksw_uint32 sdsID, rtksw_uint32 page, rtksw_uint32 reg, rtksw_uint32 regData)
{
    rtksw_api_ret_t retVal;
    rtksw_uint32 cmdData;
    rtksw_uint32 busy;
    rtksw_uint32 pollingCnt = 0;

    /* Check initialization state */
    RTKSW_CHK_INIT_STATE(unit);

    if (page > RTL8367C_MAX_SDS_PAGE)
        return RT_ERR_INPUT;
    
    if (reg > RTL8367C_MAX_SDS_REGISTER)
        return RT_ERR_INPUT;

    if (regData > 0xFFFF)
        return RT_ERR_INPUT;

    switch (sdsID)
    {
        case 0:
            cmdData = 0x00C0;
            break;
        case 1:
            if ((rtksw_switch_chipType_get(unit) != CHIP_RTL8370B) && (rtksw_switch_chipType_get(unit) != CHIP_RTL8370C))
                return RT_ERR_INPUT;
            cmdData = 0x00C1;
            break;
        default:
            return RT_ERR_INPUT;
    }

    if ((retVal = rtl8367c_setAsicReg(unit, RTL8367C_REG_SDS_INDACS_DATA, regData)) != RT_ERR_OK)
        return retVal;

    if ((retVal = rtl8367c_setAsicReg(unit, RTL8367C_REG_SDS_INDACS_ADR, (page << 5) | reg)) != RT_ERR_OK)
        return retVal;

    if ((retVal = rtl8367c_setAsicReg(unit, RTL8367C_REG_SDS_INDACS_CMD, cmdData)) != RT_ERR_OK)
        return retVal;

    do
    {
        if (pollingCnt > 100)
            return RT_ERR_BUSYWAIT_TIMEOUT;

        if ((retVal = rtl8367c_getAsicRegBit(unit, RTL8367C_REG_SDS_INDACS_CMD, RTL8367C_SDS_CMD_BUSY_OFFSET, &busy)) != RT_ERR_OK)
            return retVal;
        
        pollingCnt++;
    } while (busy == 1);

    return RT_ERR_OK;
}

/* Function Name:
 *      dal_rtl8367c_port_serdesReg_get
 * Description:
 *      Get Serdes register data of the specific port.
 * Input:
 *      unit    - Unit ID
 *      port    - Port id.
 *      page    - Page id.
 *      reg     - Register id
 * Output:
 *      pData   - Register data
 * Return:
 *      RT_ERR_OK               - OK
 *      RT_ERR_FAILED           - Failed
 *      RT_ERR_SMI              - SMI access error
 *      RT_ERR_INPUT            - Error input
 *      RT_ERR_NULL_POINTER     - NULL pointer
 *      RT_ERR_BUSYWAIT_TIMEOUT - Access busy
 * Note:
 *      This API can get Serdes register data of the specific sdsID.
 */
rtksw_api_ret_t dal_rtl8367c_port_serdesReg_get(rtksw_uint32 unit, rtksw_uint32 sdsID, rtksw_uint32 page, rtksw_uint32 reg, rtksw_uint32 *pData)
{
    rtksw_api_ret_t retVal;
    rtksw_uint32 cmdData;
    rtksw_uint32 busy;
    rtksw_uint32 pollingCnt = 0;

    /* Check initialization state */
    RTKSW_CHK_INIT_STATE(unit);

    if (page > RTL8367C_MAX_SDS_PAGE)
        return RT_ERR_INPUT;
    
    if (reg > RTL8367C_MAX_SDS_REGISTER)
        return RT_ERR_INPUT;

    if (pData == NULL)
        return RT_ERR_NULL_POINTER;

    switch (sdsID)
    {
        case 0:
            cmdData = 0x0080;
            break;
        case 1:
            if ((rtksw_switch_chipType_get(unit) != CHIP_RTL8370B) && (rtksw_switch_chipType_get(unit) != CHIP_RTL8370C))
                return RT_ERR_INPUT;
                
            cmdData = 0x0081;
            break;
        default:
            return RT_ERR_INPUT;
    }

    if ((retVal = rtl8367c_setAsicReg(unit, RTL8367C_REG_SDS_INDACS_ADR, (page << 5) | reg)) != RT_ERR_OK)
        return retVal;

    if ((retVal = rtl8367c_setAsicReg(unit, RTL8367C_REG_SDS_INDACS_CMD, cmdData)) != RT_ERR_OK)
        return retVal;

    do
    {
        if (pollingCnt > 100)
            return RT_ERR_BUSYWAIT_TIMEOUT;

        if ((retVal = rtl8367c_getAsicRegBit(unit, RTL8367C_REG_SDS_INDACS_CMD, RTL8367C_SDS_CMD_BUSY_OFFSET, &busy)) != RT_ERR_OK)
            return retVal;
        
        pollingCnt++;
    } while (busy == 1);
    
    if ((retVal = rtl8367c_getAsicReg(unit, RTL8367C_REG_SDS_INDACS_DATA, pData)) != RT_ERR_OK)
        return retVal;

    return RT_ERR_OK;
}

/* Function Name:
 *      dal_rtl8367c_port_serdesPolarity_set
 * Description:
 *      Set Serdes polarity.
 * Input:
 *      unit            - Unit ID
 *      sdsID           - Serdes id.
 *      inputPolarity   - Input Polarity.
 *      outputPolarity  - Output Polarity
 * Output:
 *      None
 * Return:
 *      RT_ERR_OK               - OK
 *      RT_ERR_FAILED           - Failed
 *      RT_ERR_SMI              - SMI access error
 *      RT_ERR_INPUT            - Error input
 * Note:
 *      This API can set serdes polarity of the specific sdsID.
 */
rtksw_api_ret_t dal_rtl8367c_port_serdesPolarity_set(rtksw_uint32 unit, rtksw_uint32 sdsID, rtksw_port_sdsPolarity_t inputPolarity, rtksw_port_sdsPolarity_t outputPolarity)
{
    rtksw_api_ret_t retVal;
    rtksw_uint32 regData;

    /* Check initialization state */
    RTKSW_CHK_INIT_STATE(unit);

    if ((inputPolarity >= SDS_POLARITY_END) || (outputPolarity >= SDS_POLARITY_END))
        return RT_ERR_INPUT;

    if ((retVal = dal_rtl8367c_port_serdesReg_get(unit, sdsID, 0, 0, &regData)) != RT_ERR_OK)
        return retVal;

    if (inputPolarity == SDS_POLARITY_NORMAL)
        regData &= ~(0x0001 << 9);
    else
        regData |= (0x0001 << 9);

    if (outputPolarity == SDS_POLARITY_NORMAL)
        regData &= ~(0x0001 << 8);
    else
        regData |= (0x0001 << 8);

    if ((retVal = dal_rtl8367c_port_serdesReg_set(unit, sdsID, 0, 0, regData)) != RT_ERR_OK)
        return retVal;

    return RT_ERR_OK;
}

/* Function Name:
 *      dal_rtl8367c_port_serdesPolarity_get
 * Description:
 *      Get Serdes polarity.
 * Input:
 *      unit            - Unit ID
 *      sdsID           - Serdes id.
 * Output:
 *      pInputPolarity  - Input Polarity.
 *      pOutputPolarity - Output Polarity
 * Return:
 *      RT_ERR_OK               - OK
 *      RT_ERR_FAILED           - Failed
 *      RT_ERR_SMI              - SMI access error
 *      RT_ERR_INPUT            - Error input
 *      RT_ERR_NULL_POINTER     - Null pointer
 * Note:
 *      This API can set serdes polarity of the specific sdsID.
 */
rtksw_api_ret_t dal_rtl8367c_port_serdesPolarity_get(rtksw_uint32 unit, rtksw_uint32 sdsID, rtksw_port_sdsPolarity_t *pInputPolarity, rtksw_port_sdsPolarity_t *pOutputPolarity)
{
    rtksw_api_ret_t retVal;
    rtksw_uint32 regData;

    /* Check initialization state */
    RTKSW_CHK_INIT_STATE(unit);

    if ((pInputPolarity == NULL) || (pOutputPolarity == NULL))
        return RT_ERR_NULL_POINTER;

    if ((retVal = dal_rtl8367c_port_serdesReg_get(unit, sdsID, 0, 0, &regData)) != RT_ERR_OK)
        return retVal;

    if ((regData & (0x0001 << 9)) == 0)
        *pInputPolarity = SDS_POLARITY_NORMAL;
    else
        *pInputPolarity = SDS_POLARITY_REVERSE;

    if ((regData & (0x0001 << 8)) == 0)
        *pOutputPolarity = SDS_POLARITY_NORMAL;
    else
        *pOutputPolarity = SDS_POLARITY_REVERSE;

    return RT_ERR_OK;
}

/* Function Name:
 *      dal_rtl8367c_port_extPhyAutoPollingCfg_set
 * Description:
 *      Set External PHY auto polling function.
 * Input:
 *      unit            - Unit ID
 *      port            - Port id.
 *      pCfg            - Auto polling configuration
 * Output:
 *      None.
 * Return:
 *      RT_ERR_OK               - OK
 *      RT_ERR_FAILED           - Failed
 *      RT_ERR_SMI              - SMI access error
 *      RT_ERR_INPUT            - Error input
 *      RT_ERR_NULL_POINTER     - Null pointer
 * Note:
 *      This API can set External PHY auto polling function.
 */
rtksw_api_ret_t dal_rtl8367c_port_extPhyAutoPollingCfg_set(rtksw_uint32 unit, rtksw_port_t port, rtksw_port_extPhyAutoPollingCfg_t *pCfg)
{
    rtksw_api_ret_t retVal;
    switch_chip_t chipID = 0;
    rtksw_uint32 physicalPort;
    rtksw_uint32 extid;

    /* Check initialization state */
    RTKSW_CHK_INIT_STATE(unit);

    chipID = rtksw_switch_chipType_get(unit);
    if (chipID != CHIP_RTL8370C)
        return RT_ERR_CHIP_NOT_SUPPORTED;

    /* Check Port Valid */
    RTKSW_CHK_PORT_IS_EXT(unit, port);

    if (pCfg == NULL)
        return RT_ERR_OK;
    
    if (pCfg->state >= RTKSW_ENABLE_END)
        return RT_ERR_ENABLE;

    if ((pCfg->extPhyType != PHY_TYPE_10G_2500M_PHY) && (pCfg->extPhyType != PHY_TYPE_FEPHY) && (pCfg->extPhyType != PHY_TYPE_GPHY))
        return RT_ERR_INPUT;

    if (pCfg->extPhyID > 31)
        return RT_ERR_INPUT; 

    physicalPort = rtksw_switch_port_L2P_get(unit, port);
    if (physicalPort == 0xFF)
        return RT_ERR_FAILED;
    
    extid = physicalPort - 8;

    /* State */
    if ((retVal = rtl8367c_setAsicRegBit(unit, 0x1e00, (extid + 12), (pCfg->state == RTKSW_ENABLED) ? 1 : 0))!=RT_ERR_OK)
        return retVal;

    /* PHY type */
    if ((retVal = rtl8367c_setAsicRegBits(unit, 0x1e00, 0x3 << (extid * 2 + 8), (pCfg->extPhyType & 0x3)))!=RT_ERR_OK)
        return retVal;    

    /* PHY ID */
    if ((retVal = rtl8367c_setAsicRegBits(unit, 0x1e01, 0x1F << extid * 5, pCfg->extPhyID))!=RT_ERR_OK)
        return retVal;

    return RT_ERR_OK;
}

/* Function Name:
 *      dal_rtl8367c_port_extPhyAutoPollingCfg_get
 * Description:
 *      Get External PHY auto polling function.
 * Input:
 *      unit            - Unit ID
 *      port            - Port id.
 * Output:
 *      pCfg            - Auto polling configuration
 * Return:
 *      RT_ERR_OK               - OK
 *      RT_ERR_FAILED           - Failed
 *      RT_ERR_SMI              - SMI access error
 *      RT_ERR_INPUT            - Error input
 *      RT_ERR_NULL_POINTER     - Null pointer
 * Note:
 *      This API can get External PHY auto polling function.
 */
rtksw_api_ret_t dal_rtl8367c_port_extPhyAutoPollingCfg_get(rtksw_uint32 unit, rtksw_port_t port, rtksw_port_extPhyAutoPollingCfg_t *pCfg)
{
    rtksw_api_ret_t retVal;
    switch_chip_t chipID = 0;
    rtksw_uint32 physicalPort;
    rtksw_uint32 extid;
    rtksw_uint32 regData;

    /* Check initialization state */
    RTKSW_CHK_INIT_STATE(unit);

    chipID = rtksw_switch_chipType_get(unit);
    if (chipID != CHIP_RTL8370C)
        return RT_ERR_CHIP_NOT_SUPPORTED;

    /* Check Port Valid */
    RTKSW_CHK_PORT_IS_EXT(unit, port);

    if (pCfg == NULL)
        return RT_ERR_OK;

    physicalPort = rtksw_switch_port_L2P_get(unit, port);
    if (physicalPort == 0xFF)
        return RT_ERR_FAILED;
    
    extid = physicalPort - 8;

    /* State */
    if ((retVal = rtl8367c_getAsicRegBit(unit, 0x1e00, (extid + 12), &regData))!=RT_ERR_OK)
        return retVal;
    
    pCfg->state = (regData == 1) ? RTKSW_ENABLED : RTKSW_DISABLED;

    /* PHY type */
    if ((retVal = rtl8367c_getAsicRegBits(unit, 0x1e00, 0x3 << (extid * 2 + 8), &regData))!=RT_ERR_OK)
        return retVal;    

    pCfg->extPhyType = (rtksw_port_phy_type_t)regData;

    /* PHY ID */
    if ((retVal = rtl8367c_getAsicRegBits(unit, 0x1e01, 0x1F << extid * 5, &regData))!=RT_ERR_OK)
        return retVal;

    pCfg->extPhyID = regData;

    return RT_ERR_OK;
}

/* Function Name:
 *      dal_rtl8367c_port_extPhySmiState_set
 * Description:
 *      Enable/Disable SMI master for accessing external MDC/MDIO slave device.
 * Input:
 *      unit    - Unit ID
 *      state   - SMI master state.
 * Output:
 *      None.
 * Return:
 *      RT_ERR_OK                   - OK
 *      RT_ERR_FAILED               - Failed
 *      RT_ERR_SMI                  - SMI access error
 *      RT_ERR_ENABLE               - Error input
 *      RT_ERR_CHIP_NOT_SUPPORTED   - Function not supported by this chip model 
 * Note:
 *      This API can set the state of SMI master.
 */
rtksw_api_ret_t dal_rtl8367c_port_extPhySmiState_set(rtksw_uint32 unit, rtksw_enable_t state)
{
    rtksw_api_ret_t retVal;
    switch_chip_t chipID = 0;

    /* Check initialization state */
    RTKSW_CHK_INIT_STATE(unit);

    chipID = rtksw_switch_chipType_get(unit);
    if (chipID != CHIP_RTL8370C)
        return RT_ERR_CHIP_NOT_SUPPORTED;

    if(state >= RTKSW_ENABLE_END)
        return RT_ERR_ENABLE;
    
    if (state == RTKSW_ENABLED)
    {
        if ((retVal = rtl8367c_setAsicReg(unit, 0x1e48, 4))!=RT_ERR_OK)
            return retVal;
    }
    else
    {
        if ((retVal = rtl8367c_setAsicReg(unit, 0x1e48, 0))!=RT_ERR_OK)
            return retVal;
    }

    return RT_ERR_OK;
}

/* Function Name:
 *      dal_rtl8367c_port_extPhySmiState_get
 * Description:
 *      Get state of SMI master for accessing external MDC/MDIO slave device.
 * Input:
 *      unit    - Unit ID
 * Output:
 *      pState  - SMI master state.
 * Return:
 *      RT_ERR_OK                   - OK
 *      RT_ERR_FAILED               - Failed
 *      RT_ERR_SMI                  - SMI access error
 *      RT_ERR_NULL_POINTER         - Null pointer
 *      RT_ERR_CHIP_NOT_SUPPORTED   - Function not supported by this chip model
 * Note:
 *      This API can set the state of SMI master.
 */
rtksw_api_ret_t dal_rtl8367c_port_extPhySmiState_get(rtksw_uint32 unit, rtksw_enable_t *pState)
{
    rtksw_api_ret_t retVal;
    switch_chip_t chipID = 0;
    rtksw_uint32 regData;

    /* Check initialization state */
    RTKSW_CHK_INIT_STATE(unit);

    chipID = rtksw_switch_chipType_get(unit);
    if (chipID != CHIP_RTL8370C)
        return RT_ERR_CHIP_NOT_SUPPORTED;

    if (pState == NULL)
        return RT_ERR_NULL_POINTER;

    if ((retVal = rtl8367c_getAsicReg(unit, 0x1e48, &regData))!=RT_ERR_OK)
        return retVal;

    *pState = (regData != 0) ? RTKSW_ENABLED : RTKSW_DISABLED;
    return RT_ERR_OK;
}

/* Function Name:
 *      dal_rtl8367c_port_extPhyReg_set
 * Description:
 *      Set register of external MDC/MDIO slave device.
 * Input:
 *      unit        - Unit ID
 *      phyID       - External device ID
 *      page        - Page. For accessing stardard register 0-15, keep this parameter as 0.
 *      reg         - Register of external device
 *      data        - The data value which is written into register
 * Output:
 *      None.
 * Return:
 *      RT_ERR_OK                   - OK
 *      RT_ERR_FAILED               - Failed
 *      RT_ERR_SMI                  - SMI access error
 *      RT_ERR_CHIP_NOT_SUPPORTED   - Function not supported by this chip model
 * Note:
 *      This API can set register of external MDC/MDIO slave device.
 */
rtksw_api_ret_t dal_rtl8367c_port_extPhyReg_set(rtksw_uint32 unit, rtksw_uint32 phyID, rtksw_port_phy_page_t page, rtksw_port_phy_reg_t reg, rtksw_port_phy_data_t data)
{
    rtksw_api_ret_t retVal;
    rtksw_uint32 regData, errInfo = 0, phyMsk = 0;
    rtksw_uint32 busyCounter = 0xFFF;
    switch_chip_t chipID = 0;
    rtksw_uint32 auto_polling8;
    rtksw_uint32 auto_polling9;
    rtksw_uint32 phyID8;
    rtksw_uint32 phyID9;
    rtksw_uint32 slot;

    /* Check initialization state */
    RTKSW_CHK_INIT_STATE(unit);

    if ((phyID > 31) || (page > 0xFFF) || (reg > 31) || (data > 0xFFFF))
        return RT_ERR_INPUT;

    chipID = rtksw_switch_chipType_get(unit);
    if (chipID != CHIP_RTL8370C)
        return RT_ERR_CHIP_NOT_SUPPORTED;
    
    if ((retVal = rtl8367c_setAsicRegBits(unit, 0x1e10, 0xFFF, page)) != RT_ERR_OK)
        return retVal;

    /* Auto parking back to page 0 */
    if ((retVal = rtl8367c_setAsicRegBits(unit, 0x1e0f, 0x1F, 0)) != RT_ERR_OK)
        return retVal;

    if ((retVal = rtl8367c_setAsicReg(unit, 0x1e13, data)) != RT_ERR_OK)
        return retVal;

    /* Looking for empty slot */
    if ((retVal = rtl8367c_getAsicReg(unit, 0x1e00, &regData))!=RT_ERR_OK)
        return retVal;

    auto_polling8 = (regData & 0x1000) ? 1 : 0;
    auto_polling9 = (regData & 0x2000) ? 1 : 0;

    if ((retVal = rtl8367c_getAsicReg(unit, 0x1e01, &regData))!=RT_ERR_OK)
        return retVal;

    phyID8 = regData & 0x001F;
    phyID9 = (regData & 0x03E0) >> 5;

    if ((auto_polling8 == 0) || ((auto_polling8 == 1) && (phyID8 == phyID)))
        slot = 0;
    else if ((auto_polling9 == 0) || ((auto_polling9 == 1) && (phyID9 == phyID)))
        slot = 1;
    else
        return RT_ERR_PHY_SMI_INDIRECT_ACCESS; /* No empty slot */

    /* Make sure phyID is written into correct slot */
    if (slot == 0)
    {
        if (phyID8 != phyID)
        {
            regData &= ~0x001F;
            regData |= phyID;
            if ((retVal = rtl8367c_setAsicReg(unit, 0x1e01, regData))!=RT_ERR_OK)
                return retVal;
        }
    }
    else /* slot == 1 */
    {
        if (phyID9 != phyID)
        {
            regData &= ~0x003E;
            regData |= (phyID << 5);
            if ((retVal = rtl8367c_setAsicReg(unit, 0x1e01, regData))!=RT_ERR_OK)
                return retVal;
        }
    }

    /* Config to C22 mode */
    if ((retVal = rtl8367c_setAsicRegBits(unit, 0x1e00, 0x3 << (slot * 2 + 8), 0x3))!=RT_ERR_OK)
        return retVal;

    phyMsk = 0x0001 << slot;
    regData = (reg<<8) + (phyMsk << 3) + 5; 
    if ((retVal = rtl8367c_setAsicReg(unit, 0x1e0e, regData)) != RT_ERR_OK)
        return retVal;

    /* Polling status */
    while(busyCounter)
    {
        retVal = rtl8367c_getAsicRegBit(unit, 0x1e0e, 0, &regData);
        if(retVal != RT_ERR_OK)
            return retVal;

        if(regData == 0)
            break;

        busyCounter --;
        if(busyCounter == 0)
            return RT_ERR_BUSYWAIT_TIMEOUT;
    }

    if ((retVal = rtl8367c_getAsicRegBits(unit, 0x1e10, 0x7000, &errInfo)) != RT_ERR_OK)
        return retVal;

    if (errInfo != 0)
        return RT_ERR_PHY_SMI_INDIRECT_ACCESS;

    return RT_ERR_OK;

}

/* Function Name:
 *      dal_rtl8367c_port_extPhyReg_get
 * Description:
 *      Get register of external MDC/MDIO slave device.
 * Input:
 *      unit        - Unit ID
 *      phyID       - External device ID
 *      page        - Page. For accessing stardard register 0-15, keep this parameter as 0.
 *      reg         - Register of external device
 * Output:
 *      pData       - The data value which is read from register
 * Return:
 *      RT_ERR_OK                   - OK
 *      RT_ERR_FAILED               - Failed
 *      RT_ERR_SMI                  - SMI access error
 *      RT_ERR_NULL_POINTER         - Null pointer
 *      RT_ERR_CHIP_NOT_SUPPORTED   - Function not supported by this chip model
 * Note:
 *      This API can set register of external MDC/MDIO slave device.
 */
rtksw_api_ret_t dal_rtl8367c_port_extPhyReg_get(rtksw_uint32 unit, rtksw_uint32 phyID, rtksw_port_phy_page_t page, rtksw_port_phy_reg_t reg, rtksw_port_phy_data_t *pData)
{
    rtksw_api_ret_t retVal;
    rtksw_uint32 regData, errInfo = 0;
    rtksw_uint32 busyCounter = 0xFFF;
    switch_chip_t chipID = 0;
    rtksw_uint32 auto_polling8;
    rtksw_uint32 auto_polling9;
    rtksw_uint32 phyID8;
    rtksw_uint32 phyID9;
    rtksw_uint32 slot;

    /* Check initialization state */
    RTKSW_CHK_INIT_STATE(unit);

    if ((phyID > 31) || (page > 0xFFF) || (reg > 31))
        return RT_ERR_INPUT;

    if (pData == NULL)
        return RT_ERR_NULL_POINTER;

    chipID = rtksw_switch_chipType_get(unit);
    if (chipID != CHIP_RTL8370C)
        return RT_ERR_CHIP_NOT_SUPPORTED;

    /* Looking for empty slot */
    if ((retVal = rtl8367c_getAsicReg(unit, 0x1e00, &regData))!=RT_ERR_OK)
        return retVal;

    auto_polling8 = (regData & 0x1000) ? 1 : 0;
    auto_polling9 = (regData & 0x2000) ? 1 : 0;

    if ((retVal = rtl8367c_getAsicReg(unit, 0x1e01, &regData))!=RT_ERR_OK)
        return retVal;

    phyID8 = regData & 0x001F;
    phyID9 = (regData & 0x03E0) >> 5;

    if ((auto_polling8 == 0) || ((auto_polling8 == 1) && (phyID8 == phyID)))
        slot = 0;
    else if ((auto_polling9 == 0) || ((auto_polling9 == 1) && (phyID9 == phyID)))
        slot = 1;
    else
        return RT_ERR_PHY_SMI_INDIRECT_ACCESS; /* No empty slot */

    /* Make sure phyID is written into correct slot */
    if (slot == 0)
    {
        if (phyID8 != phyID)
        {
            regData &= ~0x001F;
            regData |= phyID;
            if ((retVal = rtl8367c_setAsicReg(unit, 0x1e01, regData))!=RT_ERR_OK)
                return retVal;
        }
    }
    else /* slot == 1 */
    {
        if (phyID9 != phyID)
        {
            regData &= ~0x003E;
            regData |= (phyID << 5);
            if ((retVal = rtl8367c_setAsicReg(unit, 0x1e01, regData))!=RT_ERR_OK)
                return retVal;
        }
    }

    /* Config to C22 mode */
    if ((retVal = rtl8367c_setAsicRegBits(unit, 0x1e00, 0x3 << (slot * 2 + 8), 0x3))!=RT_ERR_OK)
        return retVal;

    if ((retVal = rtl8367c_setAsicReg(unit, 0x1e13, slot + 8)) != RT_ERR_OK)
        return retVal;
    
    if ((retVal = rtl8367c_setAsicRegBits(unit, 0x1e10, 0xFFF, page)) != RT_ERR_OK)
        return retVal;

    /* Auto parking back to page 0 */
    if ((retVal = rtl8367c_setAsicRegBits(unit, 0x1e0f, 0x1F, 0)) != RT_ERR_OK)
        return retVal;

    if ((retVal = rtl8367c_setAsicReg(unit, 0x1e0e, (reg << 8) + 0x1)) != RT_ERR_OK)
        return retVal;

    /* Polling status */
    while(busyCounter)
    {
        retVal = rtl8367c_getAsicRegBit(unit, 0x1e0e, 0, &regData);
        if(retVal != RT_ERR_OK)
            return retVal;

        if(regData == 0)
            break;

        busyCounter --;
        if(busyCounter == 0)
            return RT_ERR_BUSYWAIT_TIMEOUT;
    }
    
    if ((retVal = rtl8367c_getAsicRegBits(unit, 0x1e10, 0x7000, &errInfo)) != RT_ERR_OK)
        return retVal;

    if (errInfo !=0)
        return RT_ERR_PHY_SMI_INDIRECT_ACCESS;

    if ((retVal = rtl8367c_getAsicReg(unit, 0x1e12, &regData)) != RT_ERR_OK)
        return retVal;

    *pData = regData;
    return RT_ERR_OK;

}

/* Function Name:
 *      dal_rtl8367c_port_extC45PhyReg_set
 * Description:
 *      Set register of external C45 MDC/MDIO slave device.
 * Input:
 *      unit        - Unit ID
 *      phyID       - External device ID
 *      mmd         - MMD.
 *      reg         - Register of external device
 *      data        - The data value which is written into register
 * Output:
 *      None.
 * Return:
 *      RT_ERR_OK                   - OK
 *      RT_ERR_FAILED               - Failed
 *      RT_ERR_SMI                  - SMI access error
 *      RT_ERR_CHIP_NOT_SUPPORTED   - Function not supported by this chip model
 * Note:
 *      This API can set register of external C45 MDC/MDIO slave device.
 */
rtksw_api_ret_t dal_rtl8367c_port_extC45PhyReg_set(rtksw_uint32 unit, rtksw_uint32 phyID, rtksw_uint32 mmd, rtksw_port_phy_reg_t reg, rtksw_port_phy_data_t data)
{
      
    rtksw_api_ret_t retVal;
    rtksw_uint32 regData, phyMsk = 0;
    rtksw_uint32 errInfo = 0; 
    rtksw_uint32 busyCounter = 0xFFF;
    switch_chip_t chipID = 0;
    rtksw_uint32 auto_polling8;
    rtksw_uint32 auto_polling9;
    rtksw_uint32 phyID8;
    rtksw_uint32 phyID9;
    rtksw_uint32 slot;

    /* Check initialization state */
    RTKSW_CHK_INIT_STATE(unit);

    if ((phyID > 31) || (mmd > 31) || (reg > 0xFFFF) || (data > 0xFFFF))
        return RT_ERR_INPUT;

    chipID = rtksw_switch_chipType_get(unit);
    if (chipID != CHIP_RTL8370C)
        return RT_ERR_CHIP_NOT_SUPPORTED;

    if ((retVal = rtl8367c_setAsicRegBits(unit, 0x1e0f, 0x3E0, mmd)) != RT_ERR_OK)
        return retVal;

    if ((retVal = rtl8367c_setAsicReg(unit, 0x1e11, reg)) != RT_ERR_OK)
        return retVal;

    if ((retVal = rtl8367c_setAsicReg(unit, 0x1e13, data)) != RT_ERR_OK)
        return retVal;

    /* Looking for empty slot */
    if ((retVal = rtl8367c_getAsicReg(unit, 0x1e00, &regData))!=RT_ERR_OK)
        return retVal;

    auto_polling8 = (regData & 0x1000) ? 1 : 0;
    auto_polling9 = (regData & 0x2000) ? 1 : 0;

    if ((retVal = rtl8367c_getAsicReg(unit, 0x1e01, &regData))!=RT_ERR_OK)
        return retVal;

    phyID8 = regData & 0x001F;
    phyID9 = (regData & 0x03E0) >> 5;

    if ((auto_polling8 == 0) || ((auto_polling8 == 1) && (phyID8 == phyID)))
        slot = 0;
    else if ((auto_polling9 == 0) || ((auto_polling9 == 1) && (phyID9 == phyID)))
        slot = 1;
    else
        return RT_ERR_PHY_SMI_INDIRECT_ACCESS; /* No empty slot */

    /* Make sure phyID is written into correct slot */
    if (slot == 0)
    {
        if (phyID8 != phyID)
        {
            regData &= ~0x001F;
            regData |= phyID;
            if ((retVal = rtl8367c_setAsicReg(unit, 0x1e01, regData))!=RT_ERR_OK)
                return retVal;
        }
    }
    else /* slot == 1 */
    {
        if (phyID9 != phyID)
        {
            regData &= ~0x003E;
            regData |= (phyID << 5);
            if ((retVal = rtl8367c_setAsicReg(unit, 0x1e01, regData))!=RT_ERR_OK)
                return retVal;
        }
    }

    /* Config to C45 mode */
    if ((retVal = rtl8367c_setAsicRegBits(unit, 0x1e00, 0x3 << (slot * 2 + 8), 0x1))!=RT_ERR_OK)
        return retVal;

    phyMsk = 1 << slot;
    regData = (phyMsk << 3) + 7;
    if ((retVal = rtl8367c_setAsicReg(unit, 0x1e0e, regData)) != RT_ERR_OK)
        return retVal;

    /* Polling status */
    while(busyCounter)
    {
        retVal = rtl8367c_getAsicRegBit(unit, 0x1e0e, 0, &regData);
        if(retVal != RT_ERR_OK)
            return retVal;

        if(regData == 0)
            break;

        busyCounter --;
        if(busyCounter == 0)
            return RT_ERR_BUSYWAIT_TIMEOUT;
    }
    
    if ((retVal = rtl8367c_getAsicRegBits(unit, 0x1e10, 0x7000, &errInfo)) != RT_ERR_OK)
        return retVal;

    if (errInfo !=0)
        return RT_ERR_PHY_SMI_INDIRECT_ACCESS;

    return RT_ERR_OK;
}

/* Function Name:
 *      dal_rtl8367c_port_extC45PhyReg_get
 * Description:
 *      Get register of external C45 MDC/MDIO slave device.
 * Input:
 *      unit        - Unit ID
 *      phyID       - External device ID
 *      mmd         - MMD.
 *      reg         - Register of external device
 * Output:
 *      pData       - The data value which is read from register
 * Return:
 *      RT_ERR_OK                   - OK
 *      RT_ERR_FAILED               - Failed
 *      RT_ERR_SMI                  - SMI access error
 *      RT_ERR_NULL_POINTER         - Null pointer
 *      RT_ERR_CHIP_NOT_SUPPORTED   - Function not supported by this chip model
 * Note:
 *      This API can set register of external C45 MDC/MDIO slave device.
 */
rtksw_api_ret_t dal_rtl8367c_port_extC45PhyReg_get(rtksw_uint32 unit, rtksw_uint32 phyID, rtksw_uint32 mmd, rtksw_port_phy_reg_t reg, rtksw_port_phy_data_t *pData)
{
    rtksw_api_ret_t retVal;
    rtksw_uint32 regData, errInfo = 0;
    rtksw_uint32 busyCounter = 0xFFF;
    switch_chip_t chipID = 0;
    rtksw_uint32 auto_polling8;
    rtksw_uint32 auto_polling9;
    rtksw_uint32 phyID8;
    rtksw_uint32 phyID9;
    rtksw_uint32 slot;

    /* Check initialization state */
    RTKSW_CHK_INIT_STATE(unit);

    if ((phyID > 31) || (mmd > 31) || (reg > 0xFFFF))
        return RT_ERR_INPUT;
    
    if (pData == NULL)
        return RT_ERR_NULL_POINTER;

    chipID = rtksw_switch_chipType_get(unit);
    if (chipID != CHIP_RTL8370C)
        return RT_ERR_CHIP_NOT_SUPPORTED;

    /* Looking for empty slot */
    if ((retVal = rtl8367c_getAsicReg(unit, 0x1e00, &regData))!=RT_ERR_OK)
        return retVal;

    auto_polling8 = (regData & 0x1000) ? 1 : 0;
    auto_polling9 = (regData & 0x2000) ? 1 : 0;

    if ((retVal = rtl8367c_getAsicReg(unit, 0x1e01, &regData))!=RT_ERR_OK)
        return retVal;

    phyID8 = regData & 0x001F;
    phyID9 = (regData & 0x03E0) >> 5;

    if ((auto_polling8 == 0) || ((auto_polling8 == 1) && (phyID8 == phyID)))
        slot = 0;
    else if ((auto_polling9 == 0) || ((auto_polling9 == 1) && (phyID9 == phyID)))
        slot = 1;
    else
        return RT_ERR_PHY_SMI_INDIRECT_ACCESS; /* No empty slot */

    /* Make sure phyID is written into correct slot */
    if (slot == 0)
    {
        if (phyID8 != phyID)
        {
            regData &= ~0x001F;
            regData |= phyID;
            if ((retVal = rtl8367c_setAsicReg(unit, 0x1e01, regData))!=RT_ERR_OK)
                return retVal;
        }
    }
    else /* slot == 1 */
    {
        if (phyID9 != phyID)
        {
            regData &= ~0x003E;
            regData |= (phyID << 5);
            if ((retVal = rtl8367c_setAsicReg(unit, 0x1e01, regData))!=RT_ERR_OK)
                return retVal;
        }
    }

    /* Config to C45 mode */
    if ((retVal = rtl8367c_setAsicRegBits(unit, 0x1e00, 0x3 << (slot * 2 + 8), 0x1))!=RT_ERR_OK)
        return retVal;

    if ((retVal = rtl8367c_setAsicReg(unit, 0x1e48, 0x4)) != RT_ERR_OK)
        return retVal;

    if ((retVal = rtl8367c_setAsicReg(unit, 0x1e13, slot + 8)) != RT_ERR_OK)
        return retVal;

    if ((retVal = rtl8367c_setAsicRegBits(unit, 0x1e0f, 0x3E0, mmd)) != RT_ERR_OK)
        return retVal;

    if ((retVal = rtl8367c_setAsicReg(unit, 0x1e11, reg)) != RT_ERR_OK)
        return retVal;

    if ((retVal = rtl8367c_setAsicReg(unit, 0x1e0e, 0x3)) != RT_ERR_OK)
        return retVal;

    /* Polling status */
    while(busyCounter)
    {
        retVal = rtl8367c_getAsicRegBit(unit, 0x1e0e, 0, &regData);
        if(retVal != RT_ERR_OK)
            return retVal;

        if(regData == 0)
            break;

        busyCounter --;
        if(busyCounter == 0)
            return RT_ERR_BUSYWAIT_TIMEOUT;
    }

    if ((retVal = rtl8367c_getAsicRegBits(unit, 0x1e10, 0x7000, &errInfo)) != RT_ERR_OK)
        return retVal;

    if (errInfo !=0)
        return RT_ERR_PHY_SMI_INDIRECT_ACCESS;

    if ((retVal = rtl8367c_getAsicReg(unit, 0x1e12, &regData)) != RT_ERR_OK)
        return retVal;

    *pData = regData;
    return RT_ERR_OK;

}
