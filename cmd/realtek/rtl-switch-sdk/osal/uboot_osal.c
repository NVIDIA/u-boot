// SPDX-License-Identifier: GPL-2.0+
/*
 * RTK Switch SDK - U-Boot OS Abstraction Layer
 * Copyright (C) 2024 Realtek Semiconductor Corp.
 *
 * Provides u-boot compatible implementations of OS-specific functions
 */

#include <common.h>
#include <linux/delay.h>
#include <linux/types.h>
#include <asm/gpio.h>
#include "uboot_osal.h"

/* GPIO Configuration for AST2700 - RTL Switch Control */
#define RTL_GPIO_MDC	172  /* GPIO V4 - SMI Clock */
#define RTL_GPIO_SDA	173  /* GPIO V5 - SMI Data */

/* External GPIO variables for SMI (defined in smi.c) */
extern unsigned int smi_SCK;
extern unsigned int smi_SDA;

/* GPIO handles */
static int gpio_mdc = -1;
static int gpio_sda = -1;

/* Initialize GPIO pins for SMI communication */
static int gpio_init_with_pins(int mdc_pin, int sda_pin)
{
	int ret;
	unsigned int mdc_gpio, sda_gpio;
	char mdc_str[16], sda_str[16];

	printf("RTL Switch: Initializing GPIOs (MDC=%d, SDA=%d)\n", mdc_pin, sda_pin);

	/* Convert pin numbers to strings for gpio_lookup_name() */
	snprintf(mdc_str, sizeof(mdc_str), "%d", mdc_pin);
	snprintf(sda_str, sizeof(sda_str), "%d", sda_pin);

	/* Lookup MDC GPIO - this properly resolves the GPIO across all controllers */
	ret = gpio_lookup_name(mdc_str, NULL, NULL, &mdc_gpio);
	if (ret) {
		printf("Error: Failed to lookup GPIO %d (MDC), error=%d\n", mdc_pin, ret);
		printf("Note: Try running 'gpio status' to see available GPIOs\n");
		return ret;
	}
	printf("RTL Switch: MDC GPIO %d resolved to global GPIO %u\n", mdc_pin, mdc_gpio);

	/* Lookup SDA GPIO */
	ret = gpio_lookup_name(sda_str, NULL, NULL, &sda_gpio);
	if (ret) {
		printf("Error: Failed to lookup GPIO %d (SDA), error=%d\n", sda_pin, ret);
		printf("Try running 'gpio status' to see available GPIOs\n");
		return ret;
	}
	printf("RTL Switch: SDA GPIO %d resolved to global GPIO %u\n", sda_pin, sda_gpio);

	/* Request MDC pin */
	ret = gpio_request(mdc_gpio, "rtl_mdc");
	if (ret && ret != -EBUSY) {
		printf("Error: Failed to request GPIO %u (MDC), error=%d\n", mdc_gpio, ret);
		return ret;
	}
	gpio_mdc = mdc_gpio;
	printf("RTL Switch: MDC GPIO %u requested successfully\n", mdc_gpio);

	/* Request SDA pin */
	ret = gpio_request(sda_gpio, "rtl_sda");
	if (ret && ret != -EBUSY) {
		printf("Error: Failed to request GPIO %u (SDA), error=%d\n", sda_gpio, ret);
		gpio_free(mdc_gpio);
		return ret;
	}
	gpio_sda = sda_gpio;
	printf("RTL Switch: SDA GPIO %u requested successfully\n", sda_gpio);

	/* Initialize GPIOs to known state (both as outputs, both high) */
	printf("RTL Switch: Initializing GPIO directions and values...\n");
	ret = gpio_direction_output(gpio_mdc, 1);
	if (ret) {
		printf("Error: Failed to set MDC direction, error=%d\n", ret);
		gpio_free(sda_gpio);
		gpio_free(mdc_gpio);
		return ret;
	}
	printf("RTL Switch: MDC set as output=1\n");

	ret = gpio_direction_output(gpio_sda, 1);
	if (ret) {
		printf("Error: Failed to set SDA direction, error=%d\n", ret);
		gpio_free(sda_gpio);
		gpio_free(mdc_gpio);
		return ret;
	}
	printf("RTL Switch: SDA set as output=1\n");

	/* Small delay to stabilize */
	udelay(100);
	printf("RTL Switch: GPIO initialization complete\n");

	return 0;
}

int gpio_init(void)
{
	return gpio_init_with_pins(RTL_GPIO_MDC, RTL_GPIO_SDA);
}

void gpio_cleanup(void)
{
	if (gpio_mdc >= 0) {
		gpio_free(gpio_mdc);
		gpio_mdc = -1;
	}
	if (gpio_sda >= 0) {
		gpio_free(gpio_sda);
		gpio_sda = -1;
	}
}

/* SMI Bit-Banging Functions - Matches Realtek SDK Implementation */

/* Helper functions to set GPIO without delays 
 * Note: gpio_set_value() is faster than gpio_direction_output() when 
 * the pin is already configured as output
 */
void gpio_set_mdc_output(void)
{
	gpio_direction_output(gpio_mdc, 1);
}

void gpio_set_mdc_input(void)
{
	gpio_direction_input(gpio_mdc);
}

void gpio_set_mdc(int value)
{
	gpio_set_value(gpio_mdc, value);
}

void gpio_set_sda_output(void)
{
	gpio_direction_output(gpio_sda, 1);
}

void gpio_set_sda_input(void)
{
	gpio_direction_input(gpio_sda);
}

void gpio_set_sda(int value)
{
	gpio_set_value(gpio_sda, value);
}

int gpio_read_sda(void)
{
	return gpio_get_value(gpio_sda);
}

/* Getter functions for GPIO pin numbers */
unsigned int rtk_gpio_mdc_get(void)
{
	return (unsigned int)gpio_mdc;
}

unsigned int rtk_gpio_sda_get(void)
{
	return (unsigned int)gpio_sda;
}

/* Wrapper functions for SDK compatibility 
 * These allow the SDK to use GPIO IDs dynamically
 */
void rtk_gpio_direction_set(unsigned int gpio_id, int direction)
{
	if (gpio_id == smi_SCK) {
		if (direction == GPIO_DIR_OUT) {
			gpio_set_mdc_output();
		} else {
			/* SCK is typically always output, but set to high if input requested */
			gpio_set_mdc(1);
		}
	} else if (gpio_id == smi_SDA) {
		if (direction == GPIO_DIR_OUT) {
			gpio_set_sda_output();
		} else {
			gpio_set_sda_input();
		}
	}
}

void rtk_gpio_data_set(unsigned int gpio_id, int data)
{
	if (gpio_id == smi_SCK) {
		gpio_set_mdc(data);
	} else if (gpio_id == smi_SDA) {
		gpio_set_sda(data);
	}
}

int rtk_gpio_data_get(unsigned int gpio_id)
{
	if (gpio_id == smi_SDA) {
		return gpio_read_sda();
	}
	return 0;
}

/* Memory operations - map to u-boot functions */
void *osal_memset(void *s, int c, size_t n)
{
    return memset(s, c, n);
}

void *osal_memcpy(void *dest, const void *src, size_t n)
{
    return memcpy(dest, src, n);
}

int osal_memcmp(const void *s1, const void *s2, size_t n)
{
    return memcmp(s1, s2, n);
}

/* Delay operations - map to u-boot delay functions */
void osal_udelay(unsigned long usecs)
{
    udelay(usecs);
}

void osal_mdelay(unsigned long msecs)
{
    mdelay(msecs);
}

/* Printf - map to u-boot printf */
int osal_printf(const char *fmt, ...)
{
    va_list args;
    int ret;
    
    va_start(args, fmt);
    ret = vprintf(fmt, args);
    va_end(args);
    
    return ret;
}

