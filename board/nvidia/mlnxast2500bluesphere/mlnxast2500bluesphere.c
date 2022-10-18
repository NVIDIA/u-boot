// SPDX-License-Identifier: GPL-2.0+
/*
 * (C) Copyright 2022
 * NVIDIA Corporation <www.nvidia.com>
 */

#include <common.h>
#include <environment.h>
#include <asm/io.h>
#include <dm/uclass.h>
#include <asm/gpio.h>

DECLARE_GLOBAL_DATA_PTR;
#ifndef CONFIG_RAM
#define SDMC_CONFIG_VRAM_GET(x)		((x >> 2) & 0x3)
#define SDMC_CONFIG_MEM_GET(x)		(x & 0x3)
#define AST_GPIO_BASE		(0x1E780000)
#define AST_SCU_BASE			(0x1E6E2000)
#define AST_SCU_MISC1_CTRL	0x2C
#define GPIO_NR(A, N)		((A - 'A') * 8 + N)
/* Check CEC is exist or not
 * if GPIOB5 = 0 => CEC not exist
 * if GPIOB5 = 1 => CEC exist
 */
#define CEC_MODE_GPIO GPIO_NR('B', 5)
/* Check single DPU vs dual DPU mode
 * if GPION6 = 0 => single DPU mode
 * if GPION6 = 1 => dual DPU mode
 */
#define DPU_MODE_GPIO GPIO_NR('N', 6)

extern u32 ast_sdmc_get_mem_size(void);

static const u32 aspeed_vram_table[] = {
	0x00800000,	//8MB
	0x01000000,	//16MB
	0x02000000,	//32MB
	0x04000000,	//64MB
};

static u32 ast_sdmc_get_vram_size(void)
{
	u32 size_conf = SDMC_CONFIG_VRAM_GET(readl(0x1e6e0004));
	return aspeed_vram_table[size_conf];
}
#endif
#if defined(CONFIG_SHOW_BOOT_PROGRESS)
void show_boot_progress(int progress)
{
	printf("Boot reached stage %d\n", progress);
}
#endif

int bluesphere_dual_dpu_mode;
int cec_exist;

int board_init(void)
{
	int i;
	int ret;
	struct udevice *dev;

	gd->bd->bi_boot_params = CONFIG_SYS_SDRAM_BASE + 0x100;

	/*
	 * Loop over all MISC and WDT uclass drivers to call the comphy code
	 * and init all CP110 devices enabled in the DT
	 */
	i = 0;
	while (1) {
		/* Call the comphy code via the MISC uclass driver */
		ret = uclass_get_device(UCLASS_MISC, i++, &dev);

		/* We're done, once no further CP110 device is found */
		if (ret)
			break;
	}

	i = 0;
	while (1) {
		/* Call the comphy code via the WDT uclass driver */
		ret = uclass_get_device(UCLASS_WDT, i++, &dev);
		/* We're done, once no further CP110 device is found */
		if (ret)
			break;
	}

	/* address of boot parameters */
	gd->bd->bi_boot_params = CONFIG_SYS_SDRAM_BASE + 0x100;
	gd->flags &= (~(GD_FLG_SILENT | GD_FLG_DISABLE_CONSOLE));
	gd->env_valid = 1;

	gpio_request(CEC_MODE_GPIO, "CEC Mode");
	gpio_request(DPU_MODE_GPIO, "DPU Mode");

	if (gpio_get_value(DPU_MODE_GPIO)) {
		u32 reg = readl(AST_SCU_BASE + AST_SCU_MISC1_CTRL);

		printf("Operating Mode: Dual DPU mode\n");
		bluesphere_dual_dpu_mode = 1;

		reg |= 0x400; // set bit 10
		writel(reg, AST_SCU_BASE + AST_SCU_MISC1_CTRL);
		/* disable debug logs */
		gd->flags |= (GD_FLG_SILENT | GD_FLG_DISABLE_CONSOLE);
	} else {
		printf("Operating Mode: Single DPU mode\n");
	}

	if (gpio_get_value(CEC_MODE_GPIO)) {
		printf("CEC Status: CEC Exist\n");
		cec_exist = 1;
	} else {
		printf("CEC Status: CEC Not Exist\n");
		cec_exist = 0;
		/* Push logic 1 through GPIOB5 to enable USB current limiter */
		gpio_direction_output(CEC_MODE_GPIO, 1);
	}

	return 0;
}

#ifdef CONFIG_BOARD_LATE_INIT
/* The 'late init' logic runs after env vars are imported, very important */
int board_late_init(void)
{
	int env_updated = 0;
	char *existing_dual_dpu_mode;
	char current_dual_dpu_mode[2] = "0\0";
	char *existing_cec_status;
	char current_cec_status[2] = "0\0";
	phys_size_t mem_test_ram_size = 0x00, prev_mem_test_ram_size = 0x00;

	/* update mem test result */
	prev_mem_test_ram_size = env_get_hex("mem_test_ram_size", 0x00);
	mem_test_ram_size = get_ram_size((void *)CONFIG_SYS_MEMTEST_START,
						BLUESPHERE_RAM_SIZE);
	env_set_hex("mem_test_ram_size", mem_test_ram_size);
	if (prev_mem_test_ram_size != mem_test_ram_size)
		env_updated = 1;

	/* update dual dpu mode in uboot env */
	existing_dual_dpu_mode = env_get("dual_dpu_mode");
	env_set("bootcmd_string", ENV_BOOTSTRING_SINGLE_DPU);
	env_set("bootargs", BOOTARGS_SINGLE_DPU);
	if (bluesphere_dual_dpu_mode) {
		/* disable kernel logs in dual dpu mode */
		env_set("bootargs", BOOTARGS_DUAL_DPU);
		/* select dual dpu device tree */
		env_set("bootcmd_string", ENV_BOOTSTRING_DUAL_DPU);
		current_dual_dpu_mode[0] = '1';
	}
	if (strncmp(existing_dual_dpu_mode, current_dual_dpu_mode, 1) != 0) {
		env_set("dual_dpu_mode_updated", "1");
		env_set("dual_dpu_mode", current_dual_dpu_mode);
		env_updated = 1;
	}

	/* update cec status in uboot env */
	existing_cec_status = env_get("cec_exist");
	if (cec_exist)
		current_cec_status[0] = '1';

	if (strncmp(existing_cec_status, current_cec_status, 1) != 0) {
		env_set("cec_exist", current_cec_status);
		env_updated = 1;
	}

	if (env_updated)
		env_save();

	return 0;
}
#endif

int dram_init(void)
{
#ifdef CONFIG_RAM
	struct udevice *dev;
	struct ram_info ram;
	int ret;

	ret = uclass_get_device(UCLASS_RAM, 0, &dev);
	if (ret) {
		debug("DRAM FAIL1\r\n");
		return ret;
	}

	ret = ram_get_info(dev, &ram);
	if (ret) {
		debug("DRAM FAIL2\r\n");
		return ret;
	}

	gd->ram_size = ram.size;
#else
	u32 vga = ast_sdmc_get_vram_size();
	u32 dram = ast_sdmc_get_mem_size();
	gd->ram_size = (dram - vga);
#endif
	return 0;
}
