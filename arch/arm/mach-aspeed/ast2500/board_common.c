// SPDX-License-Identifier: GPL-2.0+
/*
 * Copyright (c) 2016 Google, Inc
 */
#include <common.h>
#include <dm.h>
#include <ram.h>
#include <timer.h>
#include <asm/io.h>
#include <asm/arch/platform.h>
#include <asm/arch/scu_ast2500.h>
#include <asm/arch/sdram_ast2500.h>
#include <asm/arch/timer.h>
#include <linux/err.h>
#include <dm/uclass.h>

DECLARE_GLOBAL_DATA_PTR;

#define AST_LPC_HICR5 0x080
# define LPC_HICR5_ENFWH BIT(10)
#define AST_LPC_HICRB 0x100
# define LPC_HICRB_SIO_ILPC2AHB_DIS BIT(6)

# define AST_SDMC_PROTECT 0x00
# define AST_SDMC_GFX_PROT 0x08
#  define SDMC_GFX_PROT_VGA_CURSOR BIT(0)
#  define SDMC_GFX_PROT_VGA_CG_READ BIT(1)
#  define SDMC_GFX_PROT_VGA_ASCII_READ BIT(2)
#  define SDMC_GFX_PROT_VGA_CRT BIT(3)
#  define SDMC_GFX_PROT_PCIE BIT(16)
#  define SDMC_GFX_PROT_XDMA BIT(17)

static void isolate_bmc(void)
{
	bool sdmc_unlocked;
	u32 val;

	/* iLPC2AHB */
#if !defined(CONFIG_ASPEED_ENABLE_SUPERIO)
	val = readl(ASPEED_HW_STRAP1);
	val |= SCU_HWSTRAP_LPC_SIO_DEC_DIS;
	writel(val, ASPEED_HW_STRAP1);
#endif

	val = readl(ASPEED_LPC_CTRL + AST_LPC_HICRB);
	val |= LPC_HICRB_SIO_ILPC2AHB_DIS;
	writel(val, ASPEED_LPC_CTRL + AST_LPC_HICRB);

	/* P2A, PCIe BMC */
	val = readl(ASPEED_PCIE_CONFIG_SET);
	val &= ~(SCU_PCIE_CONFIG_SET_BMC_DMA
	         | SCU_PCIE_CONFIG_SET_BMC_MMIO
	         | SCU_PCIE_CONFIG_SET_BMC_EN
	         | SCU_PCIE_CONFIG_SET_VGA_MMIO);
	writel(val, ASPEED_PCIE_CONFIG_SET);

	/* Debug UART */
#if !defined(CONFIG_ASPEED_ENABLE_DEBUG_UART)
	val = readl(ASPEED_MISC1_CTRL);
	val |= SCU_MISC_DEBUG_UART_DISABLE;
	writel(val, ASPEED_MISC1_CTRL);
#endif

	/* X-DMA */
	sdmc_unlocked = readl(ASPEED_SDRAM_CTRL + AST_SDMC_PROTECT);
	if (!sdmc_unlocked)
		writel(SDRAM_UNLOCK_KEY, ASPEED_SDRAM_CTRL + AST_SDMC_PROTECT);

	val = readl(ASPEED_SDRAM_CTRL + AST_SDMC_GFX_PROT);
	val |= (SDMC_GFX_PROT_VGA_CURSOR
	        | SDMC_GFX_PROT_VGA_CG_READ
	        | SDMC_GFX_PROT_VGA_ASCII_READ
	        | SDMC_GFX_PROT_VGA_CRT
	        | SDMC_GFX_PROT_PCIE
	        | SDMC_GFX_PROT_XDMA);
	writel(val, ASPEED_SDRAM_CTRL + AST_SDMC_GFX_PROT);

	if (!sdmc_unlocked)
		writel(~SDRAM_UNLOCK_KEY, ASPEED_SDRAM_CTRL + AST_SDMC_PROTECT);

	/* LPC2AHB */
	val = readl(ASPEED_LPC_CTRL + AST_LPC_HICR5);
	val &= ~LPC_HICR5_ENFWH;
	writel(val, ASPEED_LPC_CTRL + AST_LPC_HICR5);
}

__weak int board_init(void)
{
	struct udevice *dev;
	int i;
	int ret;

	isolate_bmc();

	gd->bd->bi_boot_params = CONFIG_SYS_SDRAM_BASE + 0x100;

	/*
	 * Loop over all MISC uclass drivers to call the comphy code
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

	return 0;
}

#define SDMC_CONFIG_VRAM_GET(x)		((x >> 2) & 0x3)
#define SDMC_CONFIG_MEM_GET(x)		(x & 0x3)
#define SDMC_CONFIG_ECC_STATUS_GET(x)	((x) & BIT(7))

static const u32 ast2500_dram_table[] = {
	0x08000000,	//128MB
	0x10000000,	//256MB
	0x20000000,	//512MB
	0x40000000,	//1024MB
};

u32
ast_sdmc_get_mem_size(void)
{
	u32 size = 0;
	u32 size_conf = SDMC_CONFIG_MEM_GET(readl(0x1e6e0004));

	size = ast2500_dram_table[size_conf];

	return size;

}

static const u32 aspeed_vram_table[] = {
	0x00800000,	//8MB
	0x01000000,	//16MB
	0x02000000,	//32MB
	0x04000000,	//64MB
};

static u32
ast_sdmc_get_vram_size(void)
{
	u32 size_conf = SDMC_CONFIG_VRAM_GET(readl(0x1e6e0004));
	return aspeed_vram_table[size_conf];
}

static bool ast_sdmc_is_ecc_on(void)
{
	u32 ecc_status = SDMC_CONFIG_ECC_STATUS_GET(readl(0x1e6e0004));

	return !!ecc_status;
}

static u32 ast_sdmc_get_ecc_size(void)
{
	if (ast_sdmc_is_ecc_on())
		return readl(0x1e6e0054) + (1 << 20);
	else
		return 0;
}

__weak int dram_init(void)
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

#ifdef CONFIG_ARCH_FIXUP_FDT_MEMORY
	/*
	 * U-boot will fixup the memory node in kernel's DT.  The ECC redundancy
	 * is unable to handle now, just report the ECC size as the ram size.
	 */
	if (ast_sdmc_is_ecc_on())
		gd->ram_size = ast_sdmc_get_ecc_size();
	else
		gd->ram_size = dram - vga;
#else
	/*
	 * Report the memory size regardless the ECC redundancy, let kernel
	 * handle the ram paritions
	 */
	gd->ram_size = dram - vga;
#endif /* end of "#ifdef CONFIG_ARCH_FIXUP_FDT_MEMORY" */
#endif /* end of "#ifdef CONFIG_RAM" */
	return 0;
}

void board_add_ram_info(int use_default)
{
	u32 act_size = ast_sdmc_get_mem_size() >> 20;
	u32 vga_rsvd = ast_sdmc_get_vram_size() >> 20;
	u32 ecc_size = ast_sdmc_get_ecc_size() >> 20;
	bool ecc_on = ast_sdmc_is_ecc_on();

	printf(" (capacity:%d MiB, VGA:%d MiB, ECC:%s", act_size, vga_rsvd,
	       ecc_on ? "on" : "off");

	if (ecc_on)
		printf(", ECC size:%d MiB", ecc_size);

	printf(")");
}

int arch_early_init_r(void)
{
#ifdef CONFIG_DM_PCI
	/* Trigger PCIe devices detection */
	pci_init();
#endif

	return 0;
}

