/* SPDX-License-Identifier: GPL-2.0+ */
/*
 * RTK Switch SDK - U-Boot Configuration Header
 * Copyright (C) 2024 Realtek Semiconductor Corp.
 *
 * This file provides configuration macros for building the
 * Realtek Switch SDK in the u-boot environment
 */

#ifndef __RTK_UBOOT_CONFIG_H__
#define __RTK_UBOOT_CONFIG_H__

/* Build configuration */
#define CONFIG_UBOOT_ENV        1
#define CONFIG_DAL_RTL8367C     1
#define CONFIG_DAL_RTL8367D     1
#define CONFIG_DAL_RTL8371C     1

/* Disable features not needed in u-boot */
#undef RTK_X86_CLE
#undef CONFIG_MSSDK

/* Multi-unit support (typically only 1 in u-boot) */
#define DAL_MGMT_MAX_UNIT   1

/* Memory constraints */
#define RTK_UBOOT_STATIC_ALLOC  1

/* Disable dynamic memory allocation */
#define osal_malloc(size)       NULL
#define osal_free(ptr)          do {} while(0)

/* Map standard library functions to u-boot equivalents */
#include <common.h>
#include <linux/types.h>
#include <linux/string.h>
#include <linux/delay.h>

/* Override lib.h includes for u-boot */
#define memset(s, c, n)     osal_memset(s, c, n)
#define memcpy(d, s, n)     osal_memcpy(d, s, n)
#define memcmp(s1, s2, n)   osal_memcmp(s1, s2, n)

/* GPIO macros for SMI interface */
#include "osal/uboot_osal.h"

extern unsigned int smi_SCK;
extern unsigned int smi_SDA;

#define GPIO_INIT()                     gpio_init()
#define GPIO_CLEANUP()                  gpio_cleanup()
#define GPIO_DIRECTION_SET(gpio_id, dir) rtk_gpio_direction_set(gpio_id, dir)
#define GPIO_DATA_SET(gpio_id, data)     rtk_gpio_data_set(gpio_id, data)
#define GPIO_DATA_GET(gpio_id, pData)    (*(pData) = rtk_gpio_data_get(gpio_id))



/* Delay macros */
#define CLK_DURATION(t)     osal_udelay(t)
#define DELAY               2  /* microseconds */

/* Printf macro */
#ifdef DEBUG
#define RTK_DEBUG(fmt, ...)     printf("[RTK] " fmt, ##__VA_ARGS__)
#else
#define RTK_DEBUG(fmt, ...)     do {} while(0)
#endif

#define PRINT                   printf

#endif /* __RTK_UBOOT_CONFIG_H__ */

