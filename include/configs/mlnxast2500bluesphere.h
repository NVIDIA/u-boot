// SPDX-License-Identifier: GPL-2.0+
/*
 * (C) Copyright 2022
 * NVIDIA Corporation <www.nvidia.com>
 */

#ifndef __MLNXAST2500BLUESPHERE_CONFIG_H
#define __MLNXAST2500BLUESPHERE_CONFIG_H

/*
 * High Level Configuration Options
 * (easy to change)
 */
#define CONFIG_ARCH_CPU_INIT
#define CONFIG_MACH_TYPE		MACH_TYPE_ASPEED

#include <asm/arch/platform.h>

/* Misc CPU related */
#define CONFIG_CMDLINE_TAG
#define CONFIG_SETUP_MEMORY_TAGS
#define CONFIG_INITRD_TAG



#define CONFIG_SYS_BOOTMAPSZ		(256 * 1024 * 1024)
/*
 * BOOTP options
 */
#define CONFIG_BOOTP_BOOTFILESIZE

/*
 * Miscellaneous configurable options
 */
#define CONFIG_SYS_BOOTM_LEN 		(0x800000 * 2)

#define CONFIG_ENV_SECT_SIZE	(4 << 10)

/*
 * Ethernet related
 */
#define PHY_ANEG_TIMEOUT		800

/* Uboot size */
#define CONFIG_SYS_MONITOR_LEN ((1024 - 64) * 1024)

#ifdef CONFIG_ENV_IS_IN_MMC
#define CONFIG_SYS_MMC_ENV_DEV		0
#define CONFIG_SYS_MMC_ENV_PART		0
#define CONFIG_ENV_OFFSET_REDUND	(CONFIG_ENV_OFFSET + CONFIG_ENV_SIZE)
#endif /* CONFIG_ENV_IS_IN_MMC */

/* Misc CPU related */
#define CONFIG_CMDLINE_TAG		/* enable passing of ATAGs */
#define CONFIG_SETUP_MEMORY_TAGS
#define CONFIG_INITRD_TAG

#define CONFIG_SYS_UBOOT_BASE		CONFIG_SYS_TEXT_BASE
#define BLUESPHERE_RAM_SIZE (1 * 1024 * 1024 * 1024) /* 1G */

/* Enable cache controller */
#define CONFIG_SYS_DCACHE_OFF	1
/* ------------------------------------------------------------------------- */
/* additions for new relocation code, must added to all boards */
#define CONFIG_SYS_SDRAM_BASE		(ASPEED_DRAM_BASE + CONFIG_ASPEED_SSP_RERV_MEM)

#define SYS_INIT_RAM_END \
	(CONFIG_SYS_INIT_RAM_ADDR + CONFIG_SYS_INIT_RAM_SIZE)
#define CONFIG_SYS_INIT_SP_ADDR \
	(SYS_INIT_RAM_END - GENERATED_GBL_DATA_SIZE)

#define CONFIG_SYS_INIT_RAM_ADDR	CONFIG_SYS_SDRAM_BASE /*(AST_DRAM_BASE)*/
#define CONFIG_SYS_INIT_RAM_SIZE	(32*1024)

#define SYS_INIT_RAM_END		(CONFIG_SYS_INIT_RAM_ADDR + CONFIG_SYS_INIT_RAM_SIZE)
#define CONFIG_SYS_INIT_SP_ADDR 	(SYS_INIT_RAM_END - GENERATED_GBL_DATA_SIZE)

#define CONFIG_NR_DRAM_BANKS		1

#define CONFIG_SYS_MEMTEST_START		CONFIG_SYS_SDRAM_BASE
#define CONFIG_SYS_MEMTEST_END      (CONFIG_SYS_MEMTEST_START + BLUESPHERE_RAM_SIZE)

/*-----------------------------------------------------------------------*/

#define CONFIG_SYS_TEXT_BASE            0x00000000
/*
 * Memory Info
 */
#define CONFIG_SYS_MALLOC_LEN   	(0x1000 + 4*1024*1024) /* malloc() len */

/*
 * NS16550 Configuration
 */
#define CONFIG_SYS_NS16550_SERIAL
#define CONFIG_SYS_NS16550_REG_SIZE		(-4)
#define CONFIG_SYS_NS16550_CLK			24000000
#define AST_UART0_BASE 0x1E784000
#define CONFIG_SYS_NS16550_COM1	AST_UART0_BASE
#define CONFIG_SYS_LOADS_BAUD_CHANGE
#define CONFIG_CONS_INDEX				1
#define CONFIG_BAUDRATE					115200


/*
 * Environment Config
 */
#define CONFIG_BOOTFILE		"uImage"

/*
 * Miscellaneous configurable options
 */
#define CONFIG_SYS_CBSIZE	256		/* Console I/O Buffer Size */

/* Print Buffer Size */
#define CONFIG_SYS_PBSIZE	(CONFIG_SYS_CBSIZE + sizeof(CONFIG_SYS_PROMPT) + 16)
#define CONFIG_SYS_MAXARGS	16		/* max number of command args */
#define CONFIG_SYS_BARGSIZE	CONFIG_SYS_CBSIZE /* Boot Argument Buffer Size */

#define BOOTARGS_SINGLE_DPU	"console=ttyS4,115200n8"
#define BOOTARGS_DUAL_DPU		"console=tty0"

#define CONFIG_SYS_MONITOR_BASE	CONFIG_SYS_FLASH_BASE
#define CONFIG_SYS_FLASH_BASE AST_SPI1_CS0_BASE

#define AST_SPI1_CS0_BASE		0x38000000 /* SPI 3 Flash CS 0 Memory */
#define AST_SPI1_CS1_BASE		0x3a000000 /* SPI 3 Flash CS 1 Memory */
#define AST_FMC_BASE			0x1E620000 /* NEW SMC CONTROLLER */
#define AST_FMC_SPI0_BASE		0x1E630000 /* NEW SMC CONTROLLER */
#define AST_FMC_SPI1_BASE		0x1E631000 /* NEW SMC CONTROLLER */
#define AST_FMC_CS0_BASE		0x20000000 /* CS0 */
#define AST_FMC_CS1_BASE		0x28000000 /* CS1 */
#define AST_FMC_CS2_BASE		0x2a000000 /* CS2 */

#define FMC_CS			2
#define CONFIG_SYS_MAX_FLASH_BANKS 	(FMC_CS)

#define CONFIG_SYS_MAX_FLASH_SECT	(8192)		/* max number of sectors on one chip */

#define CONFIG_ENV_ADDR			(AST_SPI1_CS0_BASE)

#define CONFIG_SYS_LOAD_ADDR    0x80000000  /* default load address */

#define CONFIG_ENV_OFFSET 0x0 /* environment starts here  */
#define CONFIG_ENV_SIZE 0x20000     /* Total Size of Environment Sector */

#define CONFIG_BOOTCOMMAND	"run post_mtest1 post_mtest2 bootcmd_string"
#define CONFIG_ENV_OVERWRITE

#define ENV_LINUX_LOAD_ADDR "0x200e0000"
#define ENV_BOOTSTRING_DUAL_DPU ("bootm " ENV_LINUX_LOAD_ADDR "#conf-aspeed-bmc-nvidia-bluesphere-dual-dpu.dtb")
#define ENV_BOOTSTRING_SINGLE_DPU ("bootm " ENV_LINUX_LOAD_ADDR "#conf-aspeed-bmc-nvidia-bluesphere.dtb")
#define MAC2_RCLK_DELAY 0
#define CONFIG_DISABLE_CONSOLE
#define CONFIG_SILENT_CONSOLE

#define CONFIG_EXTRA_ENV_SETTINGS \
   "ethrotate=no\0" \
   "gatewayip=10.15.8.1\0" \
   "netmask=255.255.255.0\0" \
   "post_mtest1=mtest 0x80000000 0x80001000 0xaaaaaaaa 1\0" \
   "post_mtest2=mtest 0x87FFF000 0x88000000 0x55555555 1\0" \
   "recovery_mode=mw 0x1e785024 0x00\0" \
   "serverip=10.15.2.73\0" \
   "spi_dma=yes\0" \
   "stderr=serial\0" \
   "stdin=serial\0" \
   "stdout=serial\0" \
   "verify=yes\0" \
   "dual_dpu_mode=0\0" \
   "dual_dpu_mode_updated=0\0" \
   "cec_exist=1\0"

/* ------------------------------------------------------------------------- */

/* Ethernet */
#ifdef CONFIG_CMD_MII
#define CONFIG_MII 1
#define CONFIG_PHY_GIGE
#define CONFIG_PHYLIB
#define CONFIG_PHY_ADDR 0
#define CONFIG_FIXED_PHY
#define CONFIG_PHY_FIXED
#endif /*CONFIG_CMD_MII*/
#ifdef CONFIG_CMD_NET
#define CONFIG_FTGMAC100
#define CONFIG_PHY_GIGE
#endif /*CONFIG_CMD_NET*/

/* The 'late init' function will process env vars */
#define CONFIG_BOARD_LATE_INIT
#endif	/* __MLNXAST2500BLUESPHERE_CONFIG_H */
