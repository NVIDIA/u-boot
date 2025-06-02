#include <common.h>
#include <asm/io.h>
#include <dm.h>
#include <i2c.h>
#include <environment.h>

#define SCU_BASE 0x1e6e2000
#define ESPI_BASE 0x1e6ee000

#define I2C_BUS_MUX_DETECT 5
#define I2C_MUX_ADDR_71 0x71

static void __maybe_unused espi_init(void)
{
	u32 reg;

	/* skip eSPI init if LPC mode is selected */
	reg = readl(SCU_BASE + 0x510);
	if (reg & BIT(6))
		return;

	/*
	 * Aspeed STRONGLY NOT recommend to use eSPI early init.
	 *
	 * This eSPI early init sequence merely set OOB_FREE. It
	 * is NOT able to actually handle OOB requests from PCH.
	 *
	 * During the power on stage, PCH keep waiting OOB_FREE
	 * to continue its booting. In general, OOB_FREE is set
	 * when BMC firmware is ready. That is, the eSPI kernel
	 * driver is mounted and ready to serve eSPI. However,
	 * it means that PCH must wait until BMC kernel ready.
	 *
	 * For customers that request PCH booting as soon as
	 * possible. You may use this early init to set OOB_FREE
	 * to prevent PCH from blocking by OOB_FREE before BMC
	 * kernel ready.
	 *
	 * If you are not sure what you are doing, DO NOT use it.
	 */
	reg = readl(ESPI_BASE + 0x000);
	reg |= 0xef;
	writel(reg, ESPI_BASE + 0x000);

	writel(0x0, ESPI_BASE + 0x110);
	writel(0x0, ESPI_BASE + 0x114);

	reg = readl(ESPI_BASE + 0x00c);
	reg |= 0x80000000;
	writel(reg, ESPI_BASE + 0x00c);

	writel(0xffffffff, ESPI_BASE + 0x094);
	writel(0x1, ESPI_BASE + 0x100);
	writel(0x1, ESPI_BASE + 0x120);

	reg = readl(ESPI_BASE + 0x080);
	reg |= 0x50;
	writel(reg, ESPI_BASE + 0x080);

	reg = readl(ESPI_BASE + 0x000);
	reg |= 0x10;
	writel(reg, ESPI_BASE + 0x000);
}

int board_early_init_f(void)
{
	espi_init();
	return 0;
}

int board_late_init(void)
{
	int ret;
	struct udevice *bus;
	struct udevice *dev;
	char *bootcmd_curr;
	char *bootcmd_dft;
	char bootcmd[128];
	const char *bootcmd_cxx = "bootm 20100000#conf-aspeed-bmc-nvidia-hgxb300-hmc-cxx.dtb";

	// Select device tree for kernel
	// aspeed-bmc-nvidia-hgxb300-hmc-cxx.dtb is used for
	// board rev < E00 && device detected at 0x71 on bus 5
	// default cfg is used for all other cases, i.e E00 and after revs
	// or no device detected at 0x71 on bus 5 (modified board)
	bootcmd_dft = env_get_default("bootcmd");
	bootcmd_curr = env_get("bootcmd");
	// Todo: read HW strap ffrom FPGA for Board rev,
	// Only do I2C mux detection if board rev is C00 or C01 or prior
	ret = uclass_get_device_by_seq(UCLASS_I2C, I2C_BUS_MUX_DETECT, &bus);
	if (ret)
	{
		printf("Failed to get I2C bus %d, skip mux detection\n", I2C_BUS_MUX_DETECT);
		return ret;
	}

	ret = dm_i2c_probe(bus, I2C_MUX_ADDR_71, 0, &dev);
	if (ret == 0)
	{
		printf("I2C: found mux at %x on bus %d\n", I2C_MUX_ADDR_71, I2C_BUS_MUX_DETECT);

		// Only update bootcmd if it was not changed from default
		// If it is changed, assume user has a reason and don't override
		if (bootcmd_curr && strcmp(bootcmd_curr, bootcmd_dft) == 0)
		{
			// fallback to dft bootcmd if updated cmd fails
			if ((strlen(bootcmd_cxx) + strlen(bootcmd_dft) + 1) > sizeof(bootcmd))
			{
				printf("bootcmd is too long, can not update\n");
			}
			else
			{
				snprintf(bootcmd, sizeof(bootcmd), "%s; %s", bootcmd_cxx, bootcmd_dft);
				env_set("bootcmd", bootcmd);
			}
		}
	}
	else
	{
		if (bootcmd_curr && strncmp(bootcmd_curr, bootcmd_cxx, sizeof(bootcmd_cxx)) == 0)
		{
			if (bootcmd_dft)
			{
				env_set("bootcmd", bootcmd_dft);
			}
			else
			{
				env_set("bootcmd", "bootm 20100000");
			}
		}
	}
	printf("bootcmd: %s, default: %s\n", env_get("bootcmd"), bootcmd_dft);
	return 0;
}
