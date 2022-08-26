/*
 * (C) Copyright ASPEED Technology Inc.
 *
 * SPDX-License-Identifier:	GPL-2.0+
 */
#include <common.h>
#include <debug_uart.h>
#include <spl.h>
#include <dm.h>
#include <mmc.h>
#include <xyzModem.h>
#include <asm/io.h>
#include <asm/arch/aspeed_verify.h>

DECLARE_GLOBAL_DATA_PTR;

#define AST_BOOTMODE_SPI	0
#define AST_BOOTMODE_EMMC	1
#define AST_BOOTMODE_UART	2

#define SCU_BASE		0x1e6e2000
#define SCU_SMP_SEC_ENTRY	(SCU_BASE + 0x1bc)
#define SCU_WPROT2		(SCU_BASE + 0xf04)

u32 aspeed_bootmode(void);
void aspeed_mmc_init(void);
static void spl_boot_from_uart_wdt_disable(void);

void board_init_f(ulong dummy)
{
#ifndef CONFIG_SPL_TINY
	struct udevice *dev;
	spl_early_init();
	timer_init();
	uclass_get_device(UCLASS_PINCTRL, 0, &dev);
	preloader_console_init();
	dram_init();
	aspeed_mmc_init();
	spl_boot_from_uart_wdt_disable();
#endif
}

#ifdef CONFIG_SPL_BOARD_INIT
void spl_board_init(void)
{
	struct udevice *dev;

	if ((IS_ENABLED(CONFIG_ASPEED_HACE_V1) || IS_ENABLED(CONFIG_ASPEED_HACE)) &&
	    uclass_get_device_by_driver(UCLASS_MISC,
					DM_GET_DRIVER(aspeed_hace),
					&dev)) {
		debug("Warning: HACE initialization failure\n");
	}
}
#endif

u32 spl_boot_device(void)
{
#ifdef CONFIG_ASPEED_LOADERS
	switch (aspeed_bootmode()) {
	case AST_BOOTMODE_EMMC:
		return (IS_ENABLED(CONFIG_ASPEED_SECURE_BOOT))?
			ASPEED_SECBOOT_DEVICE_MMC : ASPEED_BOOT_DEVICE_MMC;
	case AST_BOOTMODE_SPI:
		return (IS_ENABLED(CONFIG_ASPEED_SECURE_BOOT))?
			ASPEED_SECBOOT_DEVICE_RAM : ASPEED_BOOT_DEVICE_RAM;
	case AST_BOOTMODE_UART:
		return (IS_ENABLED(CONFIG_ASPEED_SECURE_BOOT))?
			ASPEED_SECBOOT_DEVICE_UART : ASPEED_BOOT_DEVICE_UART;
	default:
		break;
	}
#else
	switch (aspeed_bootmode()) {
	case AST_BOOTMODE_EMMC:
		return BOOT_DEVICE_MMC1;
	case AST_BOOTMODE_SPI:
		return BOOT_DEVICE_RAM;
	case AST_BOOTMODE_UART:
		return BOOT_DEVICE_UART;
	default:
		break;
	}
#endif

	return BOOT_DEVICE_NONE;
}

void board_boot_order(u32 *spl_boot_list)
{
	spl_boot_list[0] = spl_boot_device();
	spl_boot_list[1] = ASPEED_BOOT_DEVICE_UART;
}

#ifdef CONFIG_SPL_OS_BOOT
int spl_start_uboot(void)
{
	/* boot linux */
	return 0;
}
#endif

void board_fit_image_post_process(const void *fit, int node, void **p_image, size_t *p_size)
{
	ulong s_ep;
	uint8_t os;

	fit_image_get_os(fit, node, &os);

	/* skip if no TEE */
	if (os != IH_OS_TEE)
		return;

	fit_image_get_entry(fit, node, &s_ep);

	/* set & lock secure entrypoint for secondary cores */
	writel(s_ep, SCU_SMP_SEC_ENTRY);
	writel(BIT(17) | BIT(18) | BIT(19), SCU_WPROT2);
}

int board_fit_config_name_match(const char *name)
{
	/* we always use the default configuration */
	debug("%s: %s\n", __func__, name);
	return 0;
}

struct image_header *spl_get_load_buffer(ssize_t offset, size_t size)
{
	return (struct image_header *)(CONFIG_SYS_LOAD_ADDR);
}

static void spl_boot_from_uart_wdt_disable(void)
{
	int boot_mode = aspeed_bootmode();

	/* Disable ABR WDT for SPI flash and eMMC ABR. */
	if (boot_mode == AST_BOOTMODE_UART) {
		writel(0, 0x1e620064);
		writel(0, 0x1e6f20a0);
	}
}
