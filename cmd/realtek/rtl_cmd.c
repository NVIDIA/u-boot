// SPDX-License-Identifier: GPL-2.0+
/*
 * Realtek Switch Control Commands for U-Boot
 * Using Realtek Switch SDK v1.5.4
 *
 * Copyright (C) 2024
 */

#include <common.h>
#include <command.h>
#include "./rtl-switch-sdk/rtk_switch.h"
#include "./rtl-switch-sdk/rtk_error.h"
#include "./rtl-switch-sdk/rtk_types.h"
#include "./rtl-switch-sdk/rtk_uboot_config.h"
#include "./rtl-switch-sdk/chip.h"
#include "./rtl-switch-sdk/port.h"
#include "./rtl-switch-sdk/vlan.h"
#include "./rtl-switch-sdk/stat.h"
#include "./rtl-switch-sdk/l2.h"
#include "./rtl-switch-sdk/osal/uboot_osal.h"
#include "./rtl-switch-sdk/led.h"
#include "./rtl-switch-sdk/dal/rtl8367c/rtl8367c_asicdrv.h"

/* Global unit ID */
static rtksw_uint32 g_unit = 0;
static int g_initialized = 0;

/*
 * Early boot initialization wrappers (called from board_late_init)
 * These functions provide a way to initialize the switch during
 * early boot without using the command line interface.
 */

/**
 * rtl_early_init - Initialize RTL switch during early boot
 * 
 * Returns: 0 on success, -1 on failure
 */
int rtl_early_init(void)
{
	rtksw_api_ret_t ret;

	printf("Realtek Switch SDK v1.5.4\n");
	printf("==========================\n\n");

	/* Step 1: Initialize GPIO */
	printf("Initializing GPIO for SMI...\n");
	ret = GPIO_INIT();
	if (ret != 0) {
		printf("ERROR: GPIO initialization failed (ret=%d)\n", ret);
		return -1;
	}
	printf("  GPIO initialized: MDC=%u, SDA=%u\n",
	       rtk_gpio_mdc_get(), rtk_gpio_sda_get());

	/* Step 2: Initialize switch */
	printf("\nInitializing switch...\n");
	ret = rtksw_switch_init(g_unit);
	if (ret != RT_ERR_OK) {
		printf("ERROR: Switch initialization failed (ret=%d)\n", ret);
		return -1;
	}

	printf("\nSwitch initialized successfully!\n");
	g_initialized = 1;

	return 0;
}

/**
 * rtl_port_mode_force - Force port speed and duplex mode
 * @port: Port number (typically 16 for EXT/CPU port)
 * @speed_mbps: Speed in Mbps (10, 100, or 1000)
 * @full_duplex: 1 for full duplex, 0 for half duplex
 * 
 * Returns: 0 on success, -1 on failure
 */
int rtl_port_mode_force(int port, int speed_mbps, int full_duplex)
{
	rtksw_api_ret_t ret;
	rtksw_port_mac_ability_t mac_ability;

	if (!g_initialized) {
		printf("ERROR: Switch not initialized\n");
		return -1;
	}

	/* Validate port */
	ret = rtksw_switch_logicalPortCheck(g_unit, port);
	if (ret != RT_ERR_OK) {
		printf("ERROR: Invalid port %d\n", port);
		return -1;
	}

	/* Setup MAC ability structure for forced mode */
	memset(&mac_ability, 0, sizeof(mac_ability));
	mac_ability.forcemode = 1;  /* Enable force mode */
	mac_ability.link = 1;        /* Force link up */
	mac_ability.duplex = full_duplex ? RTKSW_PORT_FULL_DUPLEX : RTKSW_PORT_HALF_DUPLEX;
	mac_ability.txpause = 1;
	mac_ability.rxpause = 1;

	/* Set speed based on input */
	switch (speed_mbps) {
	case 10:
		mac_ability.speed = RTKSW_PORT_SPEED_10M;
		break;
	case 100:
		mac_ability.speed = RTKSW_PORT_SPEED_100M;
		break;
	case 1000:
		mac_ability.speed = RTKSW_PORT_SPEED_1000M;
		break;
	default:
		printf("ERROR: Invalid speed %d (must be 10, 100, or 1000)\n", speed_mbps);
		return -1;
	}

	/* Apply configuration to port */
	ret = rtksw_port_macForceLinkExt_set(g_unit, port,
					     RTKSW_MODE_EXT_SGMII,
					     &mac_ability);
	if (ret != RT_ERR_OK) {
		printf("ERROR: Failed to configure port %d (ret=%d)\n", port, ret);
		return -1;
	}

	/* Disable SGMII Nway for forced mode */
	ret = rtksw_port_sgmiiNway_set(g_unit, port, RTKSW_DISABLED);
	if (ret != RT_ERR_OK) {
		printf("WARNING: Failed to disable SGMII nway (ret=%d)\n", ret);
		/* Continue anyway */
	}

	printf("Port %d configured successfully\n", port);
	printf("  Mode:   SGMII\n");
	printf("  Force:  Enabled\n");
	printf("  Speed:  %dM\n", speed_mbps);
	printf("  Duplex: %s\n", full_duplex ? "Full" : "Half");
	printf("  Link:   Up (forced)\n");

	return 0;
}

/*
 * Helper function to get chip name string
 */
static const char *rtl_chip_name(switch_chip_t chip)
{
	switch (chip) {
	case CHIP_RTL8367C:
		return "RTL8367C";
	case CHIP_RTL8367D:
		return "RTL8367D";
	case CHIP_RTL8367E:
		return "RTL8367E";
	case CHIP_RTL8371C:
		return "RTL8371C";
	case CHIP_RTL8370B:
		return "RTL8370B";
	case CHIP_RTL8370C:
		return "RTL8370C";
	case CHIP_RTL8364B:
		return "RTL8364B";
	case CHIP_RTL8363SC_VB:
		return "RTL8363SC-VB";
	default:
		return "Unknown";
	}
}

/*
 * Sub-command: init
 */
static int do_rtl_init(struct cmd_tbl *cmdtp, int flag, int argc, char *const argv[])
{
	rtksw_api_ret_t ret;
	switch_chip_t chip;

	printf("Realtek Switch SDK v1.5.4\n");
	printf("==========================\n\n");

	/* Step 1: Initialize GPIO */
	printf("Initializing GPIO for SMI...\n");
	ret = GPIO_INIT();
	if (ret != 0) {
		printf("ERROR: GPIO initialization failed (ret=%d)\n", ret);
		printf("Hint: Check GPIO pins and permissions\n");
		return CMD_RET_FAILURE;
	}
	printf("  GPIO initialized: MDC=%u, SDA=%u\n",
	       rtk_gpio_mdc_get(), rtk_gpio_sda_get());

	/* Step 2: Probe switch chip */
    /*
	printf("\nProbing switch chip...\n");
	ret = switch_probe(g_unit, &chip);
	if (ret != RT_ERR_OK) {
		printf("ERROR: Switch chip detection failed (ret=%d)\n", ret);
		printf("Hint: Check power, connections, and GPIO pins\n");
		return CMD_RET_FAILURE;
	}
	printf("  Chip detected: %s\n", rtl_chip_name(chip));
    */ 
	/* Step 3: Initialize switch */
	printf("\nInitializing switch...\n");
	ret = rtksw_switch_init(g_unit);
	if (ret != RT_ERR_OK) {
		printf("ERROR: Switch initialization failed (ret=%d)\n", ret);
		return CMD_RET_FAILURE;
	}

	printf("\nSwitch initialized successfully!\n");
	g_initialized = 1;

	return CMD_RET_SUCCESS;
}

/*
 * Sub-command: info
 */
static int do_rtl_info(struct cmd_tbl *cmdtp, int flag, int argc, char *const argv[])
{
	switch_chip_t chip;
	rtksw_uint32 port_mask;
	rtksw_port_t port;
	int ext_port_count = 0;
	rtksw_api_ret_t ret;
	rtksw_uint32 chip_id = 0, chip_ver = 0;
/*
	if (!g_initialized) {
		printf("ERROR: Switch not initialized. Run 'rtlinit' first.\n");
		return CMD_RET_FAILURE;
	}
*/
	chip = rtksw_switch_chipType_get(g_unit);
	port_mask = rtksw_switch_phyPortMask_get(g_unit);

	/* Read actual chip ID and version from hardware registers */
	/* Unlock chip ID registers */
	ret = rtl8367c_setAsicReg(g_unit, 0x13C2, 0x0249);
	if (ret == RT_ERR_OK) {
		/* Read chip ID (register 0x1300) */
		ret = rtl8367c_getAsicReg(g_unit, 0x1300, &chip_id);
		if (ret == RT_ERR_OK) {
			/* Read chip version (register 0x1301) */
			rtl8367c_getAsicReg(g_unit, 0x1301, &chip_ver);
		}
		/* Lock chip ID registers */
		rtl8367c_setAsicReg(g_unit, 0x13C2, 0x0000);
	}

	printf("Switch Information:\n");
	printf("===================\n");
	printf("Chip Type:      %s\n", rtl_chip_name(chip));
	
	/* Display raw chip ID and version if read successfully */
	if (ret == RT_ERR_OK) {
		printf("Chip ID:        0x%04X\n", chip_id);
		printf("Chip Version:   0x%04X\n", chip_ver);
	} else {
		printf("Chip ID:        <read failed>\n");
		printf("Chip Version:   <read failed>\n");
	}
	
	printf("Unit ID:        %u\n", g_unit);
	printf("Port Mask:      0x%08X\n", port_mask);
	printf("Max Port:       %u\n", rtksw_switch_maxLogicalPort_get(g_unit));
	printf("Max Meter ID:   %u\n", rtksw_switch_maxMeterId_get(g_unit));

	/* List EXT ports */
	printf("\nEXT Ports (CPU/MAC):\n");
	for (port = 16; port <= 18; port++) {
		if (rtksw_switch_isExtPort(g_unit, port) == RT_ERR_OK) {
			printf("  Port %u (EXT_PORT%u)\n", port, port - 16);
			ext_port_count++;
		}
	}
	if (ext_port_count == 0) {
		printf("  None configured\n");
	}

	return CMD_RET_SUCCESS;
}

/*
 * Sub-command: port
 */
static int do_rtl_port(struct cmd_tbl *cmdtp, int flag, int argc, char *const argv[])
{
	rtksw_api_ret_t ret;
	rtksw_port_t port;
	rtksw_port_linkStatus_t link_status;
	rtksw_port_speed_t speed;
	rtksw_port_duplex_t duplex;
	int show_all = 1;
	rtksw_port_t start_port, end_port;

	if (!g_initialized) {
		printf("ERROR: Switch not initialized. Run 'rtlinit' first.\n");
		return CMD_RET_FAILURE;
	}

	/* Parse arguments */
	if (argc > 1) {
		port = simple_strtoul(argv[1], NULL, 10);
		show_all = 0;
		start_port = port;
		end_port = port;
	} else {
		start_port = 0;
		end_port = RTKSW_PORT_MAX;
	}

	printf("\nPort Status:\n");
	printf("============================================================\n");
	printf("Port  Link     Speed      Duplex     PHY Addr\n");
	printf("----  -------  ---------  ---------  --------\n");

	for (port = start_port; port <= end_port; port++) {
		/* Check if port is valid */
		ret = rtksw_switch_logicalPortCheck(g_unit, port);
		if (ret != RT_ERR_OK)
			continue;

		printf("%-4d  ", port);

		/* Check if it's a UTP port */
		if (rtksw_switch_isUtpPort(g_unit, port) == RT_ERR_OK) {
			/* UTP port - use PHY status API */
			ret = rtksw_port_phyStatus_get(g_unit, port, &link_status, &speed, &duplex);
			if (ret == RT_ERR_OK) {
				if (link_status == RTKSW_PORT_LINKUP) {
					printf("%-7s  ", "UP");

					switch (speed) {
					case RTKSW_PORT_SPEED_10M:
						printf("%-9s  ", "10M");
						break;
					case RTKSW_PORT_SPEED_100M:
						printf("%-9s  ", "100M");
						break;
					case RTKSW_PORT_SPEED_1000M:
						printf("%-9s  ", "1000M");
						break;
					default:
						printf("%-9s  ", "Unknown");
						break;
					}

					printf("%-9s  ",
					       (duplex == RTKSW_PORT_FULL_DUPLEX) ? "Full" : "Half");
				} else {
					printf("%-7s  %-9s  %-9s  ", "DOWN", "-", "-");
				}
			} else {
				printf("%-7s  %-9s  %-9s  ", "ERR", "-", "-");
			}
		} else {
			/* EXT/MAC port - use MAC status API */
			rtksw_port_mac_ability_t mac_status;
			ret = rtksw_port_macStatus_get(g_unit, port, &mac_status);
			if (ret == RT_ERR_OK && mac_status.link) {
				printf("%-7s  ", "UP");
				switch (mac_status.speed) {
				case 0:
					printf("%-9s  ", "10M");
					break;
				case 1:
					printf("%-9s  ", "100M");
					break;
				case 2:
					printf("%-9s  ", "1000M");
					break;
				default:
					printf("%-9s  ", "Unknown");
					break;
				}
				printf("%-9s  ", mac_status.duplex ? "Full" : "Half");
			} else {
				printf("%-7s  %-9s  %-9s  ", "DOWN", "-", "-");
			}
		}

		/* Get physical port address */
		printf("%u\n", rtksw_switch_port_L2P_get(g_unit, port));
	}

	printf("\n");
	return CMD_RET_SUCCESS;
}

/*
 * Sub-command: stats
 */
static int do_rtl_stats(struct cmd_tbl *cmdtp, int flag, int argc, char *const argv[])
{
	rtksw_api_ret_t ret;
	rtksw_port_t port;
	rtksw_stat_port_cntr_t counters;

	if (!g_initialized) {
		printf("ERROR: Switch not initialized. Run 'rtlinit' first.\n");
		return CMD_RET_FAILURE;
	}

	if (argc < 2) {
		printf("Usage: rtlstats <port>\n");
		return CMD_RET_USAGE;
	}

	port = simple_strtoul(argv[1], NULL, 10);

	/* Validate port */
	ret = rtksw_switch_logicalPortCheck(g_unit, port);
	if (ret != RT_ERR_OK) {
		printf("ERROR: Invalid port %u\n", port);
		return CMD_RET_FAILURE;
	}

	/* Get statistics */
	ret = rtksw_stat_port_getAll(g_unit, port, &counters);
	if (ret != RT_ERR_OK) {
		printf("ERROR: Failed to get statistics (ret=%d)\n", ret);
		return CMD_RET_FAILURE;
	}

	printf("\nPort %u Statistics:\n", port);
	printf("===================\n\n");

	printf("RX Statistics:\n");
	printf("  Unicast packets:     %llu\n", (unsigned long long)counters.ifInUcastPkts);
	printf("  Multicast packets:   %llu\n", (unsigned long long)counters.ifInMulticastPkts);
	printf("  Broadcast packets:   %llu\n", (unsigned long long)counters.ifInBroadcastPkts);
	printf("  Octets:              %llu\n", (unsigned long long)counters.ifInOctets);

	printf("\nTX Statistics:\n");
	printf("  Unicast packets:     %llu\n", (unsigned long long)counters.ifOutUcastPkts);
	printf("  Multicast packets:   %llu\n", (unsigned long long)counters.ifOutMulticastPkts);
	printf("  Broadcast packets:   %llu\n", (unsigned long long)counters.ifOutBrocastPkts);
	printf("  Octets:              %llu\n", (unsigned long long)counters.ifOutOctets);

	printf("\nErrors:\n");
	printf("  RX errors:           %u\n", counters.dot3StatsSymbolErrors);
	printf("  TX collisions:       %u\n", counters.dot3StatsSingleCollisionFrames);
	printf("  CRC errors:          %u\n", counters.dot3StatsFCSErrors);

	printf("\n");
	return CMD_RET_SUCCESS;
}

/*
 * Sub-command: vlan
 */
static int do_rtl_vlan(struct cmd_tbl *cmdtp, int flag, int argc, char *const argv[])
{
	rtksw_api_ret_t ret;

	if (!g_initialized) {
		printf("ERROR: Switch not initialized. Run 'rtlinit' first.\n");
		return CMD_RET_FAILURE;
	}

	if (argc < 2) {
		return CMD_RET_USAGE;
	}

	if (strcmp(argv[1], "init") == 0) {
		/* Initialize VLAN */
		ret = rtksw_vlan_init(g_unit);
		if (ret != RT_ERR_OK) {
			printf("ERROR: VLAN initialization failed (ret=%d)\n", ret);
			return CMD_RET_FAILURE;
		}
		printf("VLAN initialized successfully\n");

	} else if (strcmp(argv[1], "create") == 0) {
		rtksw_vlan_t vid;
		rtksw_vlan_cfg_t cfg;
		rtksw_uint32 port_bits;

		if (argc < 4) {
			printf("Usage: rtlvlan create <vid> <port_mask>\n");
			printf("Example: rtlvlan create 100 0x07  (ports 0,1,2)\n");
			return CMD_RET_USAGE;
		}

		vid = simple_strtoul(argv[2], NULL, 10);
		port_bits = simple_strtoul(argv[3], NULL, 0);

		memset(&cfg, 0, sizeof(cfg));
		cfg.mbr.bits[0] = port_bits;
		cfg.untag.bits[0] = port_bits;

		ret = rtksw_vlan_set(g_unit, vid, &cfg);
		if (ret != RT_ERR_OK) {
			printf("ERROR: Failed to create VLAN %u (ret=%d)\n", vid, ret);
			return CMD_RET_FAILURE;
		}

		printf("VLAN %u created with ports 0x%08X\n", vid, port_bits);

	} else {
		return CMD_RET_USAGE;
	}

	return CMD_RET_SUCCESS;
}

/*
 * Sub-command: mode get - Get port mode configuration (EXT ports only)
 */
static int do_rtl_mode_get(struct cmd_tbl *cmdtp, int flag, int argc, char *const argv[])
{
	rtksw_api_ret_t ret;
	rtksw_port_t port;
	rtksw_mode_ext_t ext_mode;
	rtksw_port_mac_ability_t mac_ability;
	rtksw_enable_t sgmii_nway;

	if (!g_initialized) {
		printf("ERROR: Switch not initialized. Run 'rtl init' first.\n");
		return CMD_RET_FAILURE;
	}

	if (argc < 2) {
		printf("Usage: rtl mode get <port>\n");
		return CMD_RET_USAGE;
	}

	port = simple_strtoul(argv[1], NULL, 10);

	/* Validate port */
	ret = rtksw_switch_logicalPortCheck(g_unit, port);
	if (ret != RT_ERR_OK) {
		printf("ERROR: Invalid port %u\n", port);
		return CMD_RET_FAILURE;
	}

	/* Check if it's an EXT port (CPU port) */
	if (rtksw_switch_isUtpPort(g_unit, port) == RT_ERR_OK) {
		printf("ERROR: Port %u is UTP port. This command is for EXT ports only.\n", port);
		printf("Note: Use 'rtl port' to check UTP port status.\n");
		return CMD_RET_FAILURE;
	}

	/* Verify it's actually an EXT port */
	ret = rtksw_switch_isExtPort(g_unit, port);
	if (ret != RT_ERR_OK) {
		printf("ERROR: Port %u is not a valid EXT port.\n", port);
		printf("Valid EXT ports are typically: 16 (EXT_PORT0), 17 (EXT_PORT1), 18 (EXT_PORT2)\n");
		printf("Use 'rtl info' to check available ports.\n");
		return CMD_RET_FAILURE;
	}

	/* Get EXT port configuration */
	ret = rtksw_port_macForceLinkExt_get(g_unit, port, &ext_mode, &mac_ability);
	if (ret != RT_ERR_OK) {
		printf("ERROR: Failed to get port mode (ret=%d)\n", ret);
		if (ret == RT_ERR_NOT_INIT) {
			printf("Hint: Switch may not be initialized. Run 'rtl init' first.\n");
		}
		return CMD_RET_FAILURE;
	}

	printf("\nPort %u Mode Configuration (EXT/CPU Port):\n", port);
	printf("=========================================\n");

	/* Display interface mode */
	printf("Interface:    ");
	switch (ext_mode) {
	case RTKSW_MODE_EXT_DISABLE:
		printf("Disabled\n");
		break;
	case RTKSW_MODE_EXT_RGMII:
		printf("RGMII\n");
		break;
	case RTKSW_MODE_EXT_SGMII:
		printf("SGMII\n");
		break;
	case RTKSW_MODE_EXT_GMII:
		printf("GMII\n");
		break;
	default:
		printf("Unknown\n");
		break;
	}

	/* Get SGMII nway status for SGMII mode */
	if (ext_mode == RTKSW_MODE_EXT_SGMII) {
		ret = rtksw_port_sgmiiNway_get(g_unit, port, &sgmii_nway);
		if (ret == RT_ERR_OK && sgmii_nway == RTKSW_ENABLED) {
			printf("Mode:         Auto-Negotiation (SGMII Nway)\n");
		} else {
			printf("Mode:         Force Mode\n");
		}
	} else {
		printf("Mode:         %s\n", mac_ability.forcemode ? "Force Mode" : "Auto");
	}

	/* Display speed */
	printf("Speed:        ");
	switch (mac_ability.speed) {
	case RTKSW_PORT_SPEED_10M:
		printf("10M\n");
		break;
	case RTKSW_PORT_SPEED_100M:
		printf("100M\n");
		break;
	case RTKSW_PORT_SPEED_1000M:
		printf("1000M\n");
		break;
	default:
		printf("Unknown\n");
		break;
	}

	printf("Duplex:       %s\n", mac_ability.duplex ? "Full" : "Half");
	printf("Link:         %s\n", mac_ability.link ? "Up" : "Down");

	if (ext_mode == RTKSW_MODE_EXT_SGMII) {
		printf("SGMII Nway:   %s\n",
		       (sgmii_nway == RTKSW_ENABLED) ? "Enabled" : "Disabled");
	}

	printf("\n");
	return CMD_RET_SUCCESS;
}

/*
 * Sub-command: mode set - Set port mode configuration (EXT ports only)
 */
static int do_rtl_mode_set(struct cmd_tbl *cmdtp, int flag, int argc, char *const argv[])
{
	rtksw_api_ret_t ret;
	rtksw_port_t port;
	const char *mode_str;
	rtksw_port_mac_ability_t mac_ability;

	if (!g_initialized) {
		printf("ERROR: Switch not initialized. Run 'rtl init' first.\n");
		return CMD_RET_FAILURE;
	}

	// INSERT_YOUR_CODE
	int i;
	printf("argv elements:\n");
	for (i = 0; i < argc; i++) {
		printf("  argv[%d]: %s\n", i, argv[i]);
	}

	if (argc < 3) {
		printf("Usage: rtl mode set <port> <autoneg|force> [speed] [duplex]\n");
		printf("  autoneg - Enable SGMII auto-negotiation\n");
		printf("  force - Force specific speed/duplex\n");
		printf("    speed: 10M | 100M | 1000M (required for force)\n");
		printf("    duplex: half | full (required for force)\n");
		printf("Example: rtl mode set 2 force 1000M full\n");
		return CMD_RET_USAGE;
	}

	port = simple_strtoul(argv[1], NULL, 10);
	mode_str = argv[2];

	/* Validate port */
	ret = rtksw_switch_logicalPortCheck(g_unit, port);
	if (ret != RT_ERR_OK) {
		printf("ERROR: Invalid port %u\n", port);
		return CMD_RET_FAILURE;
	}

	/* Check if it's an EXT port (CPU port) */
	if (rtksw_switch_isUtpPort(g_unit, port) == RT_ERR_OK) {
		printf("ERROR: Port %u is UTP port. This command is for EXT ports only.\n", port);
		return CMD_RET_FAILURE;
	}

	if (strcmp(mode_str, "autoneg") == 0) {
		/* Enable SGMII auto-negotiation */
		memset(&mac_ability, 0, sizeof(mac_ability));

		mac_ability.forcemode = 0;  /* Disable force mode */
		mac_ability.nway = 1;       /* Enable nway */
		mac_ability.speed = RTKSW_PORT_SPEED_1000M;
		mac_ability.duplex = RTKSW_PORT_FULL_DUPLEX;
		mac_ability.link = 1;
		mac_ability.txpause = 1;
		mac_ability.rxpause = 1;

		/* Set SGMII mode with auto-negotiation */
		ret = rtksw_port_macForceLinkExt_set(g_unit, port,
						     RTKSW_MODE_EXT_SGMII,
						     &mac_ability);
		if (ret != RT_ERR_OK) {
			printf("ERROR: Failed to configure SGMII auto mode (ret=%d)\n", ret);
			return CMD_RET_FAILURE;
		}

		/* Enable SGMII Nway */
		ret = rtksw_port_sgmiiNway_set(g_unit, port, RTKSW_ENABLED);
		if (ret != RT_ERR_OK) {
			printf("ERROR: Failed to enable SGMII nway (ret=%d)\n", ret);
			return CMD_RET_FAILURE;
		}

		printf("Port %u: SGMII auto-negotiation enabled\n", port);
		printf("  Mode:   SGMII\n");
		printf("  Nway:   Enabled\n");
		printf("  Speed:  1000M (negotiated)\n");

	} else if (strcmp(mode_str, "force") == 0) {
		/* Force mode */
		const char *speed_str, *duplex_str;
		rtksw_port_speed_t port_speed;
		int is_full_duplex;

		if (argc < 5) {
			printf("ERROR: Force mode requires speed and duplex\n");
			printf("Usage: rtl mode set <port> force <speed> <duplex>\n");
			printf("  speed: 10M | 100M | 1000M\n");
			printf("  duplex: half | full\n");
			return CMD_RET_USAGE;
		}

		speed_str = argv[3];
		duplex_str = argv[4];

		/* Parse speed */
		if (strcmp(speed_str, "10M") == 0) {
			port_speed = RTKSW_PORT_SPEED_10M;
		} else if (strcmp(speed_str, "100M") == 0) {
			port_speed = RTKSW_PORT_SPEED_100M;
		} else if (strcmp(speed_str, "1000M") == 0) {
			port_speed = RTKSW_PORT_SPEED_1000M;
		} else {
			printf("ERROR: Invalid speed '%s'. Use: 10M, 100M, or 1000M\n", speed_str);
			return CMD_RET_FAILURE;
		}

		/* Parse duplex */
		if (strcmp(duplex_str, "full") == 0) {
			is_full_duplex = 1;
		} else if (strcmp(duplex_str, "half") == 0) {
			is_full_duplex = 0;
		} else {
			printf("ERROR: Invalid duplex '%s'. Use: full or half\n", duplex_str);
			return CMD_RET_FAILURE;
		}

		/* Step 1: Disable SGMII nway first */
		ret = rtksw_port_sgmiiNway_set(g_unit, port, RTKSW_DISABLED);
		if (ret != RT_ERR_OK) {
			printf("ERROR: Failed to disable SGMII nway (ret=%d)\n", ret);
			return CMD_RET_FAILURE;
		}

		/* Step 2: Configure MAC force mode */
		memset(&mac_ability, 0, sizeof(mac_ability));

		mac_ability.forcemode = 1;
		mac_ability.speed = port_speed;
		mac_ability.duplex = is_full_duplex ? RTKSW_PORT_FULL_DUPLEX : RTKSW_PORT_HALF_DUPLEX;
		mac_ability.link = 1;      /* Force link up */
		mac_ability.nway = 0;      /* Disable nway */
		mac_ability.txpause = 0;
		mac_ability.rxpause = 0;

		/* Step 3: Set SGMII force mode */
		ret = rtksw_port_macForceLinkExt_set(g_unit, port,
						     RTKSW_MODE_EXT_SGMII,
						     &mac_ability);
		if (ret != RT_ERR_OK) {
			printf("ERROR: Failed to set SGMII force mode (ret=%d)\n", ret);
			return CMD_RET_FAILURE;
		}

		printf("Port %u: SGMII force mode configured\n", port);
		printf("  Mode:   SGMII Force\n");
		printf("  Speed:  %s\n", speed_str);
		printf("  Duplex: %s\n", duplex_str);
		printf("  Nway:   Disabled\n");

	} else {
		printf("ERROR: Invalid mode '%s'. Use: autoneg or force\n", mode_str);
		return CMD_RET_USAGE;
	}

	return CMD_RET_SUCCESS;
}

/*
 * Sub-command: mode - Port mode get/set dispatcher
 */
static int do_rtl_mode(struct cmd_tbl *cmdtp, int flag, int argc, char *const argv[])
{
	const char *subcmd;

	if (argc < 2) {
		printf("Usage: rtl mode <get|set> <port> ...\n");
		return CMD_RET_USAGE;
	}

	/* Skip to sub-sub-command */
	argc--;
	argv++;
	subcmd = argv[0];

	if (strcmp(subcmd, "get") == 0) {
		return do_rtl_mode_get(cmdtp, flag, argc, argv);
	} else if (strcmp(subcmd, "set") == 0) {
		return do_rtl_mode_set(cmdtp, flag, argc, argv);
	}

	printf("Unknown mode sub-command: %s\n", subcmd);
	return CMD_RET_USAGE;
}

/*
 * Sub-command: reset
 */
static int do_rtl_reset(struct cmd_tbl *cmdtp, int flag, int argc, char *const argv[])
{
	rtksw_api_ret_t ret;

	if (!g_initialized) {
		printf("ERROR: Switch not initialized. Run 'rtlinit' first.\n");
		return CMD_RET_FAILURE;
	}

	printf("Resetting switch...\n");
	ret = rtksw_switch_reset(g_unit);
	if (ret != RT_ERR_OK) {
		printf("ERROR: Switch reset failed (ret=%d)\n", ret);
		return CMD_RET_FAILURE;
	}

	printf("Switch reset successfully\n");
	printf("Note: You may need to run 'rtlinit' again\n");
	g_initialized = 0;

	return CMD_RET_SUCCESS;
}

/*
 * Main command handler - dispatches to sub-commands
 */
static int do_rtl(struct cmd_tbl *cmdtp, int flag, int argc, char *const argv[])
{
	const char *cmd;

	/* Need at least one argument (the sub-command) */
	if (argc < 2)
		return CMD_RET_USAGE;

	/* Skip command name, point to sub-command */
	argc--;
	argv++;
	cmd = argv[0];

	/* Dispatch to appropriate sub-command */
	if (strcmp(cmd, "init") == 0) {
		return do_rtl_init(cmdtp, flag, argc, argv);
	} else if (strcmp(cmd, "info") == 0) {
		return do_rtl_info(cmdtp, flag, argc, argv);
	} else if (strcmp(cmd, "port") == 0) {
		return do_rtl_port(cmdtp, flag, argc, argv);
	} else if (strcmp(cmd, "stats") == 0) {
		return do_rtl_stats(cmdtp, flag, argc, argv);
	} else if (strcmp(cmd, "vlan") == 0) {
		return do_rtl_vlan(cmdtp, flag, argc, argv);
	} else if (strcmp(cmd, "mode") == 0) {
		return do_rtl_mode(cmdtp, flag, argc, argv);
	} else if (strcmp(cmd, "reset") == 0) {
		return do_rtl_reset(cmdtp, flag, argc, argv);
	}

	printf("Unknown sub-command: %s\n", cmd);
	return CMD_RET_USAGE;
}

U_BOOT_CMD(
	rtl, 7, 0, do_rtl,
	"Realtek switch control",
	"init                           - Initialize switch (GPIO, detect chip, init)\n"
	"rtl info                           - Display switch information\n"
	"rtl port [port]                    - Display port status (all or specific port)\n"
	"rtl stats <port>                   - Display port statistics\n"
	"rtl vlan init                      - Initialize VLAN subsystem\n"
	"rtl vlan create <vid> <mask>       - Create VLAN (e.g., rtl vlan create 100 0x07)\n"
	"rtl mode get <port>                - Get EXT port mode configuration\n"
	"rtl mode set <port> autoneg        - Enable SGMII auto-negotiation\n"
	"rtl mode set <port> force <s> <d>  - Force mode (s=10M|100M|1000M, d=half|full)\n"
	"rtl reset                          - Reset switch chip"
);

