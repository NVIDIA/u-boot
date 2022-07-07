// SPDX-License-Identifier: GPL-2.0
/*
 * Copyright (c) 2022 Qualcomm Innovation Center, Inc. All rights reserved.
 */

#include <common.h>
#include <asm/gpio.h>

#define BMC_OK_GPIO "gpio@1e780000171"

static void gpio_init(void)
{
	struct gpio_desc desc;
	int ret;

	ret = dm_gpio_lookup_name(BMC_OK_GPIO, &desc);
	if (ret)
		return;
	ret = dm_gpio_request(&desc, "bmc_ok");
	if (ret)
		return;
	ret = dm_gpio_set_dir_flags(&desc, GPIOD_IS_OUT);
	if (ret)
		goto free_exit;

	dm_gpio_set_value(&desc, 0);

free_exit:
	dm_gpio_free(desc.dev, &desc);
}

int board_early_init_f(void)
{
	return 0;
}

int board_late_init(void)
{
	gpio_init();

	return 0;
}
