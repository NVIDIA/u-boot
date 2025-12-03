/* SPDX-License-Identifier: GPL-2.0+ */
/*
 * Realtek Switch SDK - Convenience Header
 * Copyright (C) 2024
 *
 * This header provides a single include point for common SDK functions
 */

#ifndef __RTK_SDK_H__
#define __RTK_SDK_H__

/* U-Boot configuration */
#include "rtk_uboot_config.h"

/* Core SDK headers */
#include "rtk_types.h"
#include "rtk_error.h"
#include "rtk_switch.h"
#include "chip.h"

/* Feature module headers */
#include "port.h"
#include "vlan.h"
#include "l2.h"
#include "stat.h"
#include "qos.h"
#include "rate.h"
#include "acl.h"
#include "mirror.h"
#include "trunk.h"
#include "led.h"
#include "igmp.h"

/* OSAL */
#include "osal/uboot_osal.h"

#endif /* __RTK_SDK_H__ */

