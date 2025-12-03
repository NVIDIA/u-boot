/* SPDX-License-Identifier: GPL-2.0+ */
/*
 * RTK Switch SDK - U-Boot OS Abstraction Layer Header
 * Copyright (C) 2024 Realtek Semiconductor Corp.
 */

#ifndef __UBOOT_OSAL_H__
#define __UBOOT_OSAL_H__

#include <common.h>
#include <linux/types.h>
#include <stdarg.h>

/* GPIO direction definitions */
#define GPIO_DIR_IN     0
#define GPIO_DIR_OUT    1

/* GPIO functions */
int gpio_init(void);
void gpio_cleanup(void);
void gpio_set_mdc_output(void);
void gpio_set_mdc_input(void);
void gpio_set_mdc(int value);
void gpio_set_sda_output(void);
void gpio_set_sda_input(void);
void gpio_set_sda(int value);
int gpio_read_sda(void);
unsigned int rtk_gpio_mdc_get(void);
unsigned int rtk_gpio_sda_get(void);

/* Helper wrappers for SDK compatibility */
void rtk_gpio_direction_set(unsigned int gpio_id, int direction);
void rtk_gpio_data_set(unsigned int gpio_id, int data);
int rtk_gpio_data_get(unsigned int gpio_id);



/* Memory operations */
void *osal_memset(void *s, int c, size_t n);
void *osal_memcpy(void *dest, const void *src, size_t n);
int osal_memcmp(const void *s1, const void *s2, size_t n);

/* Delay operations */
void osal_udelay(unsigned long usecs);
void osal_mdelay(unsigned long msecs);

/* Printf */
int osal_printf(const char *fmt, ...);

#endif /* __UBOOT_OSAL_H__ */



