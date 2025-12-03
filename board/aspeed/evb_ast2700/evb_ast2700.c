// SPDX-License-Identifier: GPL-2.0+
/*
 * Copyright (C) ASPEED Technology Inc.
 */

#include <common.h>
#include <command.h>
#include <linux/delay.h>

/* External RTL switch initialization functions */
extern int rtl_early_init(void);
extern int rtl_port_mode_force(int port, int speed_mbps, int full_duplex);

int board_late_init(void)
{
	int ret;

	printf("\n");
	printf("************************************************************\n");
	printf("*** BOARD_LATE_INIT CALLED - EVB_AST2700                 ***\n");
	printf("************************************************************\n");
	printf("\n=== Early RTL Switch Initialization ===\n");

	/* Initialize the RTL switch */
	ret = rtl_early_init();
	if (ret != 0) {
		printf("Warning: RTL switch initialization failed\n");
		/* Don't fail boot, just continue */
		return 0;
	}

	/* Small delay to let switch stabilize */
	mdelay(100);

	/* Configure port 16 (EXT/CPU port) - force 1000M full duplex */
	printf("\nConfiguring port 16...\n");
	ret = rtl_port_mode_force(16, 1000, 1);
	if (ret != 0) {
		printf("Warning: Port 16 configuration failed\n");
	}

	printf("=== RTL Switch Initialization Complete ===\n\n");

	return 0;
}
