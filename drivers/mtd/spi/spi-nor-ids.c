// SPDX-License-Identifier: GPL-2.0+
/*
 *
 * Copyright (C) 2013 Jagannadha Sutradharudu Teki, Xilinx Inc.
 * Copyright (C) 2016 Jagan Teki <jagan@openedev.com>
 * Copyright (C) 2018 Texas Instruments Incorporated - http://www.ti.com/
 */

#include <common.h>
#include <spi.h>
#include <spi_flash.h>

#include "sf_internal.h"

/* Exclude chip names for SPL to save space */
#if !CONFIG_IS_ENABLED(SPI_FLASH_TINY)
#define INFO_NAME(_name) .name = _name,
#else
#define INFO_NAME(_name)
#endif

/* Used when the "_ext_id" is two bytes at most */
#define INFO(_name, _jedec_id, _ext_id, _sector_size, _n_sectors, _flags)	\
		INFO_NAME(_name)					\
		.id = {							\
			((_jedec_id) >> 16) & 0xff,			\
			((_jedec_id) >> 8) & 0xff,			\
			(_jedec_id) & 0xff,				\
			((_ext_id) >> 8) & 0xff,			\
			(_ext_id) & 0xff,				\
			},						\
		.id_len = (!(_jedec_id) ? 0 : (3 + ((_ext_id) ? 2 : 0))),	\
		.sector_size = (_sector_size),				\
		.n_sectors = (_n_sectors),				\
		.page_size = 256,					\
		.flags = (_flags),

#define INFO6(_name, _jedec_id, _ext_id, _sector_size, _n_sectors, _flags)	\
		INFO_NAME(_name)					\
		.id = {							\
			((_jedec_id) >> 16) & 0xff,			\
			((_jedec_id) >> 8) & 0xff,			\
			(_jedec_id) & 0xff,				\
			((_ext_id) >> 16) & 0xff,			\
			((_ext_id) >> 8) & 0xff,			\
			(_ext_id) & 0xff,				\
			},						\
		.id_len = 6,						\
		.sector_size = (_sector_size),				\
		.n_sectors = (_n_sectors),				\
		.page_size = 256,					\
		.flags = (_flags),

/* NOTE: double check command sets and memory organization when you add
 * more nor chips.  This current list focusses on newer chips, which
 * have been converging on command sets which including JEDEC ID.
 *
 * All newly added entries should describe *hardware* and should use SECT_4K
 * (or SECT_4K_PMC) if hardware supports erasing 4 KiB sectors. For usage
 * scenarios excluding small sectors there is config option that can be
 * disabled: CONFIG_MTD_SPI_NOR_USE_4K_SECTORS.
 * For historical (and compatibility) reasons (before we got above config) some
 * old entries may be missing 4K flag.
 */
const struct flash_info spi_nor_ids[] = {
#ifdef CONFIG_SPI_FLASH_ATMEL		/* ATMEL */
	/* Atmel -- some are (confusingly) marketed as "DataFlash" */
	{ INFO("at26df321",	0x1f4700, 0, 64 * 1024, 64, SECT_4K) },
	{ INFO("at25df321a",	0x1f4701, 0, 64 * 1024, 64, SECT_4K) },

	{ INFO("at45db011d",	0x1f2200, 0, 64 * 1024,   4, SECT_4K) },
	{ INFO("at45db021d",	0x1f2300, 0, 64 * 1024,   8, SECT_4K) },
	{ INFO("at45db041d",	0x1f2400, 0, 64 * 1024,   8, SECT_4K) },
	{ INFO("at45db081d",	0x1f2500, 0, 64 * 1024,  16, SECT_4K) },
	{ INFO("at45db161d",	0x1f2600, 0, 64 * 1024,  32, SECT_4K) },
	{ INFO("at45db321d",	0x1f2700, 0, 64 * 1024,  64, SECT_4K) },
	{ INFO("at45db641d",	0x1f2800, 0, 64 * 1024, 128, SECT_4K) },
	{ INFO("at26df081a", 	0x1f4501, 0, 64 * 1024,  16, SECT_4K) },
#endif
#ifdef CONFIG_SPI_FLASH_EON		/* EON */
	/* EON -- en25xxx */
	{ INFO("en25q32b",   0x1c3016, 0, 64 * 1024,   64, 0) },
	{ INFO("en25q64",    0x1c3017, 0, 64 * 1024,  128, SECT_4K) },
	{ INFO("en25qh128",  0x1c7018, 0, 64 * 1024,  256, 0) },
	{ INFO("en25s64",    0x1c3817, 0, 64 * 1024,  128, SECT_4K) },
#endif
#ifdef CONFIG_SPI_FLASH_GIGADEVICE	/* GIGADEVICE */
#ifndef CONFIG_SPI_FLASH_ONLY_SINGLE_READ
	/* GigaDevice */
	{
		INFO("gd25q16", 0xc84015, 0, 64 * 1024,  32,
			SECT_4K | SPI_NOR_DUAL_READ | SPI_NOR_QUAD_READ |
			SPI_NOR_HAS_LOCK | SPI_NOR_HAS_TB)
	},
	{
		INFO("gd25q32", 0xc84016, 0, 64 * 1024,  64,
			SECT_4K | SPI_NOR_DUAL_READ | SPI_NOR_QUAD_READ |
			SPI_NOR_HAS_LOCK | SPI_NOR_HAS_TB)
	},
	{
		INFO("gd25lq32", 0xc86016, 0, 64 * 1024, 64,
			SECT_4K | SPI_NOR_DUAL_READ | SPI_NOR_QUAD_READ |
			SPI_NOR_HAS_LOCK | SPI_NOR_HAS_TB)
	},
	{
		INFO("gd25q64", 0xc84017, 0, 64 * 1024, 128,
			SECT_4K | SPI_NOR_DUAL_READ | SPI_NOR_QUAD_READ |
			SPI_NOR_HAS_LOCK | SPI_NOR_HAS_TB)
	},
	{
		INFO("gd25q256c", 0xc84019, 0, 64 * 1024, 512,
			SECT_4K | SPI_NOR_DUAL_READ | SPI_NOR_QUAD_READ |
			SPI_NOR_HAS_LOCK | SPI_NOR_HAS_TB)
	},
	{
		INFO("gd25b512m", 0xc8471a, 0, 64 * 1024, 1024,
			SECT_4K | SPI_NOR_DUAL_READ | SPI_NOR_QUAD_READ |
			SPI_NOR_HAS_LOCK | SPI_NOR_HAS_TB)
	},
	{
		INFO("gd55b512m", 0xc8401a, 0, 64 * 1024, 1024,
			SECT_4K | SPI_NOR_DUAL_READ | SPI_NOR_QUAD_READ |
			SPI_NOR_HAS_LOCK | SPI_NOR_HAS_TB)
	},
	{
		INFO("gd55b01gf", 0xc8401b, 0, 64 * 1024, 2048,
		     SECT_4K | SPI_NOR_DUAL_READ | SPI_NOR_QUAD_READ |
		     SPI_NOR_HAS_LOCK | SPI_NOR_HAS_TB)
	},
	{
		INFO("gd55b02gf", 0xc8401c, 0, 64 * 1024, 4096,
		     SECT_4K | SPI_NOR_DUAL_READ | SPI_NOR_QUAD_READ |
		     SPI_NOR_HAS_LOCK | SPI_NOR_HAS_TB)
	},
	{
		INFO("gd55b01ge", 0xc8471b, 0, 64 * 1024, 2048,
			SECT_4K | SPI_NOR_QUAD_READ |
			SPI_NOR_HAS_LOCK | SPI_NOR_HAS_TB)
	},
	{
		INFO("gd55b02ge", 0xc8471c, 0, 64 * 1024, 4096,
			SECT_4K | SPI_NOR_QUAD_READ |
			SPI_NOR_HAS_LOCK | SPI_NOR_HAS_TB)
	},
#else
	{
		INFO("gd25q16", 0xc84015, 0, 64 * 1024,  32,
			SECT_4K | SPI_NOR_HAS_LOCK | SPI_NOR_HAS_TB)
	},
	{
		INFO("gd25q32", 0xc84016, 0, 64 * 1024,  64,
			SECT_4K | SPI_NOR_HAS_LOCK | SPI_NOR_HAS_TB)
	},
	{
		INFO("gd25lq32", 0xc86016, 0, 64 * 1024, 64,
			SECT_4K | SPI_NOR_HAS_LOCK | SPI_NOR_HAS_TB)
	},
	{
		INFO("gd25q64", 0xc84017, 0, 64 * 1024, 128,
			SECT_4K | SPI_NOR_HAS_LOCK | SPI_NOR_HAS_TB)
	},
	{
		INFO("gd25q256c", 0xc84019, 0, 64 * 1024, 512,
			SECT_4K | SPI_NOR_HAS_LOCK | SPI_NOR_HAS_TB)
	},
	{
		INFO("gd25b512m", 0xc8471a, 0, 64 * 1024, 1024,
			SECT_4K | SPI_NOR_HAS_LOCK | SPI_NOR_HAS_TB)
	},
	{
		INFO("gd55b512m", 0xc8401a, 0, 64 * 1024, 1024,
			SECT_4K | SPI_NOR_HAS_LOCK | SPI_NOR_HAS_TB)
	},
	{
		INFO("gd55b01gf", 0xc8401b, 0, 64 * 1024, 2048,
			SECT_4K | SPI_NOR_HAS_LOCK | SPI_NOR_HAS_TB)
	},
	{
		INFO("gd55b02gf", 0xc8401c, 0, 64 * 1024, 4096,
			SECT_4K | SPI_NOR_HAS_LOCK | SPI_NOR_HAS_TB)
	},
	{
		INFO("gd55b01ge", 0xc8471b, 0, 64 * 1024, 2048,
			SECT_4K | SPI_NOR_HAS_LOCK | SPI_NOR_HAS_TB)
	},
	{
		INFO("gd55b02ge", 0xc8471c, 0, 64 * 1024, 4096,
			SECT_4K | SPI_NOR_HAS_LOCK | SPI_NOR_HAS_TB)
	},
#endif // CONFIG_SPI_FLASH_ONLY_SINGLE_READ
#endif // CONFIG_SPI_FLASH_GIGADEVICE
#ifdef CONFIG_SPI_FLASH_ISSI		/* ISSI */
	/* ISSI */
	{ INFO("is25lp032",	0x9d6016, 0, 64 * 1024,  64, 0) },
	{ INFO("is25lp064",	0x9d6017, 0, 64 * 1024, 128, 0) },
#ifndef CONFIG_SPI_FLASH_ONLY_SINGLE_READ
	{ INFO("is25lq040b", 0x9d4013, 0, 64 * 1024,   8,
			SECT_4K | SPI_NOR_DUAL_READ | SPI_NOR_QUAD_READ) },
	{ INFO("is25lp128",  0x9d6018, 0, 64 * 1024, 256,
			SECT_4K | SPI_NOR_DUAL_READ) },
	{ INFO("is25lp256",  0x9d6019, 0, 64 * 1024, 512,
			SECT_4K | SPI_NOR_DUAL_READ) },
	{ INFO("is25lp512m",  0x9d601a, 0, 64 * 1024, 1024,
			SECT_4K | SPI_NOR_DUAL_READ | SPI_NOR_QUAD_READ) },
	{ INFO("is25lp512",  0x9d601a, 0, 64 * 1024, 512,
			SECT_4K | SPI_NOR_DUAL_READ | SPI_NOR_QUAD_READ) },
	{ INFO("is25lp01g",  0x9d601b, 0, 64 * 1024, 2048,
			SECT_4K | SPI_NOR_DUAL_READ | SPI_NOR_QUAD_READ) },
	{ INFO("is25wp032",  0x9d7016, 0, 64 * 1024,  64,
			SECT_4K | SPI_NOR_DUAL_READ | SPI_NOR_QUAD_READ) },
	{ INFO("is25wp064",  0x9d7017, 0, 64 * 1024, 128,
			SECT_4K | SPI_NOR_DUAL_READ | SPI_NOR_QUAD_READ) },
	{ INFO("is25wp128",  0x9d7018, 0, 64 * 1024, 256,
			SECT_4K | SPI_NOR_DUAL_READ | SPI_NOR_QUAD_READ) },
#else
	{ INFO("is25lq040b", 0x9d4013, 0, 64 * 1024,   8, SECT_4K) },
	{ INFO("is25lp128",  0x9d6018, 0, 64 * 1024, 256, SECT_4K) },
	{ INFO("is25lp256",  0x9d6019, 0, 64 * 1024, 512, SECT_4K) },
	{ INFO("is25lp512m", 0x9d601a, 0, 64 * 1024, 1024,SECT_4K) },
	{ INFO("is25lp512",  0x9d601a, 0, 64 * 1024, 512, SECT_4K) },
	{ INFO("is25lp01g",  0x9d601b, 0, 64 * 1024, 2048,SECT_4K) },
	{ INFO("is25wp032",  0x9d7016, 0, 64 * 1024,  64, SECT_4K) },
	{ INFO("is25wp064",  0x9d7017, 0, 64 * 1024, 128, SECT_4K) },
	{ INFO("is25wp128",  0x9d7018, 0, 64 * 1024, 256, SECT_4K) },
#endif // CONFIG_SPI_FLASH_ONLY_SINGLE_READ
#endif // CONFIG_SPI_FLASH_ISSI
#ifdef CONFIG_SPI_FLASH_MACRONIX	/* MACRONIX */
	/* Macronix */
	{ INFO("mx25l2005a",  0xc22012, 0, 64 * 1024,   4, SECT_4K) },
	{ INFO("mx25l4005a",  0xc22013, 0, 64 * 1024,   8, SECT_4K) },
	{ INFO("mx25l8005",   0xc22014, 0, 64 * 1024,  16, 0) },
	{ INFO("mx25l1606e",  0xc22015, 0, 64 * 1024,  32, SECT_4K) },
	{ INFO("mx25l3205d",  0xc22016, 0, 64 * 1024,  64, SECT_4K) },
	{ INFO("mx25l6405d",  0xc22017, 0, 64 * 1024, 128, SECT_4K) },
	{ INFO("mx25u2033e",  0xc22532, 0, 64 * 1024,   4, SECT_4K) },
	{ INFO("mx25u1635e",  0xc22535, 0, 64 * 1024,  32, SECT_4K) },
	{ INFO("mx25u6435f",  0xc22537, 0, 64 * 1024, 128, SECT_4K) },
	{ INFO("mx25l12805d", 0xc22018, 0, 64 * 1024, 256, 0) },
	{ INFO("mx25l12855e", 0xc22618, 0, 64 * 1024, 256, 0) },
	{ INFO("mx25u25635f", 0xc22539, 0, 64 * 1024, 512, SECT_4K | SPI_NOR_4B_OPCODES) },
	{ INFO("mx25l25655e", 0xc22619, 0, 64 * 1024, 512, 0) },
#ifndef CONFIG_SPI_FLASH_ONLY_SINGLE_READ
	{ INFO("mx25l25635e", 0xc22019, 0, 64 * 1024, 512, SPI_NOR_DUAL_READ | SPI_NOR_QUAD_READ) },
	{ INFO("mx66l51235l", 0xc2201a, 0, 64 * 1024, 1024, SPI_NOR_DUAL_READ | SPI_NOR_QUAD_READ | SPI_NOR_4B_OPCODES) },
	{ INFO("mx66u51235f", 0xc2253a, 0, 64 * 1024, 1024, SECT_4K | SPI_NOR_DUAL_READ | SPI_NOR_QUAD_READ | SPI_NOR_4B_OPCODES) },
	{ INFO("mx66l1g45g",  0xc2201b, 0, 64 * 1024, 2048, SECT_4K | SPI_NOR_DUAL_READ | SPI_NOR_QUAD_READ) },
	{ INFO("mx66l2g45g",  0xc2201c, 0, 64 * 1024, 4096, SECT_4K | SPI_NOR_DUAL_READ | SPI_NOR_QUAD_READ) },
	{ INFO("mx25l1633e", 0xc22415, 0, 64 * 1024,   32, SPI_NOR_QUAD_READ | SPI_NOR_4B_OPCODES | SECT_4K) },
#else 
	{ INFO("mx25l25635e", 0xc22019, 0, 64 * 1024, 512, 0) },
	{ INFO("mx66l51235l", 0xc2201a, 0, 64 * 1024, 1024, SPI_NOR_4B_OPCODES) },
	{ INFO("mx66u51235f", 0xc2253a, 0, 64 * 1024, 1024, SECT_4K | SPI_NOR_4B_OPCODES) },
	{ INFO("mx66l1g45g",  0xc2201b, 0, 64 * 1024, 2048, SECT_4K) },
	{ INFO("mx66l2g45g",  0xc2201c, 0, 64 * 1024, 4096, SECT_4K) },
	{ INFO("mx25l1633e",  0xc22415, 0, 64 * 1024,   32, SPI_NOR_4B_OPCODES | SECT_4K) },
#endif // CONFIG_SPI_FLASH_ONLY_SINGLE_READ
#endif // CONFIG_SPI_FLASH_MACRONIX

#ifdef CONFIG_SPI_FLASH_STMICRO		/* STMICRO */
#ifndef CONFIG_SPI_FLASH_ONLY_SINGLE_READ
	/* Micron */
	{ INFO("n25q016a",	 0x20bb15, 0, 64 * 1024,   32, SECT_4K | SPI_NOR_QUAD_READ) },
	{ INFO("n25q032",	 0x20ba16, 0, 64 * 1024,   64, SPI_NOR_QUAD_READ) },
	{ INFO("n25q032a",	0x20bb16, 0, 64 * 1024,   64, SPI_NOR_QUAD_READ) },
	{ INFO("n25q064",     0x20ba17, 0, 64 * 1024,  128, SECT_4K | SPI_NOR_QUAD_READ) },
	{ INFO("n25q064a",    0x20bb17, 0, 64 * 1024,  128, SECT_4K | SPI_NOR_QUAD_READ) },
	{ INFO("n25q128a11",  0x20bb18, 0, 64 * 1024,  256, SECT_4K | SPI_NOR_QUAD_READ) },
	{ INFO("n25q128a13",  0x20ba18, 0, 64 * 1024,  256, SECT_4K | SPI_NOR_QUAD_READ) },
	{ INFO("n25q256a",    0x20ba19, 0, 64 * 1024,  512, SECT_4K | SPI_NOR_DUAL_READ | SPI_NOR_QUAD_READ | SPI_NOR_4B_OPCODES) },
	{ INFO("n25q256ax1",  0x20bb19, 0, 64 * 1024,  512, SECT_4K | SPI_NOR_QUAD_READ | SPI_NOR_4B_OPCODES) },
	{ INFO("n25q512a",    0x20bb20, 0, 64 * 1024, 1024, SECT_4K | USE_FSR | SPI_NOR_QUAD_READ | SPI_NOR_4B_OPCODES) },
	{ INFO("n25q512ax3",  0x20ba20, 0, 64 * 1024, 1024, SECT_4K | USE_FSR | SPI_NOR_QUAD_READ | SPI_NOR_4B_OPCODES) },
	{ INFO("n25q00",      0x20ba21, 0, 64 * 1024, 2048, SECT_4K | USE_FSR | SPI_NOR_QUAD_READ | NO_CHIP_ERASE) },
	{ INFO("mt25ql02g",   0x20ba22, 0, 64 * 1024, 4096, SECT_4K | USE_FSR | SPI_NOR_QUAD_READ | NO_CHIP_ERASE) },
	{ INFO("n25q00a",     0x20bb21, 0, 64 * 1024, 2048, SECT_4K | USE_FSR | SPI_NOR_QUAD_READ | NO_CHIP_ERASE) },
	{ INFO("mt25qu02g",   0x20bb22, 0, 64 * 1024, 4096, SECT_4K | USE_FSR | SPI_NOR_QUAD_READ | NO_CHIP_ERASE) },
#else
	{ INFO("n25q016a",    0x20bb15, 0, 64 * 1024,   32, SECT_4K) },
	{ INFO("n25q032",     0x20ba16, 0, 64 * 1024,   64, 0) },
	{ INFO("n25q032a",    0x20bb16, 0, 64 * 1024,   64, 0) },
	{ INFO("n25q064",     0x20ba17, 0, 64 * 1024,  128, SECT_4K) },
	{ INFO("n25q064a",    0x20bb17, 0, 64 * 1024,  128, SECT_4K) },
	{ INFO("n25q128a11",  0x20bb18, 0, 64 * 1024,  256, SECT_4K) },
	{ INFO("n25q128a13",  0x20ba18, 0, 64 * 1024,  256, SECT_4K) },
	{ INFO("n25q256a",    0x20ba19, 0, 64 * 1024,  512, SECT_4K | SPI_NOR_4B_OPCODES) },
	{ INFO("n25q256ax1",  0x20bb19, 0, 64 * 1024,  512, SECT_4K | SPI_NOR_4B_OPCODES) },
	{ INFO("n25q512a",    0x20bb20, 0, 64 * 1024, 1024, SECT_4K | USE_FSR | SPI_NOR_4B_OPCODES) },
	{ INFO("n25q512ax3",  0x20ba20, 0, 64 * 1024, 1024, SECT_4K | USE_FSR | SPI_NOR_4B_OPCODES) },
	{ INFO("n25q00",      0x20ba21, 0, 64 * 1024, 2048, SECT_4K | USE_FSR | NO_CHIP_ERASE) },
	{ INFO("mt25ql02g",   0x20ba22, 0, 64 * 1024, 4096, SECT_4K | USE_FSR | NO_CHIP_ERASE) },
	{ INFO("n25q00a",     0x20bb21, 0, 64 * 1024, 2048, SECT_4K | USE_FSR | NO_CHIP_ERASE) },
	{ INFO("mt25qu02g",   0x20bb22, 0, 64 * 1024, 4096, SECT_4K | USE_FSR | NO_CHIP_ERASE) },
#endif // CONFIG_SPI_FLASH_ONLY_SINGLE_READ
#endif // CONFIG_SPI_FLASH_STMICRO
#ifdef CONFIG_SPI_FLASH_SPANSION	/* SPANSION */
	/* Spansion/Cypress -- single (large) sector size only, at least
	 * for the chips listed here (without boot sectors).
	 */
	{ INFO("s25fl256s0", 0x010219, 0x4d00, 256 * 1024, 128, USE_CLSR) },
	{ INFO("s25sl12800", 0x012018, 0x0300, 256 * 1024,  64, 0) },
	{ INFO("s25sl12801", 0x012018, 0x0301,  64 * 1024, 256, 0) },
	{ INFO("s25sl008a",  0x010213,      0,  64 * 1024,  16, 0) },
	{ INFO("s25sl016a",  0x010214,      0,  64 * 1024,  32, 0) },
	{ INFO("s25sl032a",  0x010215,      0,  64 * 1024,  64, 0) },
	{ INFO("s25sl064a",  0x010216,      0,  64 * 1024, 128, 0) },
	{ INFO("s25fl164k",  0x014017,      0,  64 * 1024, 128, SECT_4K) },
#ifndef CONFIG_SPI_FLASH_ONLY_SINGLE_READ
	{ INFO("s25sl032p",  0x010215, 0x4d00,  64 * 1024,  64, SPI_NOR_DUAL_READ | SPI_NOR_QUAD_READ) },
	{ INFO("s25sl064p",  0x010216, 0x4d00,  64 * 1024, 128, SPI_NOR_DUAL_READ | SPI_NOR_QUAD_READ) },
	{ INFO("s25fl256s1", 0x010219, 0x4d01,  64 * 1024, 512, SPI_NOR_DUAL_READ | SPI_NOR_QUAD_READ | USE_CLSR) },
	{ INFO6("s25fl512s",  0x010220, 0x4d0081, 256 * 1024, 256, SPI_NOR_DUAL_READ | SPI_NOR_QUAD_READ | USE_CLSR) },
	{ INFO("s25fl512s_256k",  0x010220, 0x4d00, 256 * 1024, 256, SPI_NOR_DUAL_READ | SPI_NOR_QUAD_READ | USE_CLSR) },
	{ INFO("s25fl512s_64k",  0x010220, 0x4d01, 64 * 1024, 1024, SPI_NOR_DUAL_READ | SPI_NOR_QUAD_READ | USE_CLSR) },
	{ INFO("s25fl512s_512k", 0x010220, 0x4f00, 256 * 1024, 256, SPI_NOR_DUAL_READ | SPI_NOR_QUAD_READ | USE_CLSR) },
	{ INFO6("s25fl128s",  0x012018, 0x4d0180, 64 * 1024, 256, SPI_NOR_DUAL_READ | SPI_NOR_QUAD_READ | USE_CLSR) },
	{ INFO("s25fl129p0", 0x012018, 0x4d00, 256 * 1024,  64, SPI_NOR_DUAL_READ | SPI_NOR_QUAD_READ | USE_CLSR) },
	{ INFO("s25fl129p1", 0x012018, 0x4d01,  64 * 1024, 256, SPI_NOR_DUAL_READ | SPI_NOR_QUAD_READ | USE_CLSR) },
	{ INFO("s25fl116k",  0x014015,      0,  64 * 1024,  32, SECT_4K | SPI_NOR_DUAL_READ | SPI_NOR_QUAD_READ) },
	{ INFO("s25fl208k",  0x014014,      0,  64 * 1024,  16, SECT_4K | SPI_NOR_DUAL_READ) },
	{ INFO("s25fl128l",  0x016018,      0,  64 * 1024, 256, SECT_4K | SPI_NOR_DUAL_READ | SPI_NOR_QUAD_READ | SPI_NOR_4B_OPCODES) },
	{ INFO("s25fl256l",  0x016019,      0,  64 * 1024, 512, SECT_4K | SPI_NOR_DUAL_READ | SPI_NOR_QUAD_READ | SPI_NOR_4B_OPCODES) },
	/* S25HL/HS-T (Semper Flash with Quad SPI) Family has overlaid 4KB
	 * sectors at top and/or bottom, depending on the device configuration.
	 * To support this, an erase hook makes overlaid sectors appear as
	 * uniform sectors.
	 */
	{ INFO6("s25hl256t",  0x342a19, 0x0f0390, 256 * 1024, 128, SPI_NOR_DUAL_READ | SPI_NOR_QUAD_READ | SPI_NOR_4B_OPCODES |	USE_CLSR) },
	{ INFO6("s25hl512t",  0x342a1a, 0x0f0390, 256 * 1024, 256, SPI_NOR_DUAL_READ | SPI_NOR_QUAD_READ | SPI_NOR_4B_OPCODES | USE_CLSR) },
	{ INFO6("s25hl01gt",  0x342a1b, 0x0f0390, 256 * 1024, 512, SPI_NOR_DUAL_READ | SPI_NOR_QUAD_READ | SPI_NOR_4B_OPCODES |	USE_CLSR) },
	{ INFO6("s25hs256t",  0x342b19, 0x0f0390, 256 * 1024, 128, SPI_NOR_DUAL_READ | SPI_NOR_QUAD_READ | SPI_NOR_4B_OPCODES |	USE_CLSR) },
	{ INFO6("s25hs512t",  0x342b1a, 0x0f0390, 256 * 1024, 256, SPI_NOR_DUAL_READ | SPI_NOR_QUAD_READ | SPI_NOR_4B_OPCODES |	USE_CLSR) },
	{ INFO6("s25hs01gt",  0x342b1b, 0x0f0390, 256 * 1024, 512, SPI_NOR_DUAL_READ | SPI_NOR_QUAD_READ | SPI_NOR_4B_OPCODES |	USE_CLSR) },
#else
	{ INFO("s25sl032p",  0x010215, 0x4d00,  64 * 1024,  64, 0) },
	{ INFO("s25sl064p",  0x010216, 0x4d00,  64 * 1024, 128, 0) },
	{ INFO("s25fl256s1", 0x010219, 0x4d01,  64 * 1024, 512, USE_CLSR) },
	{ INFO6("s25fl512s",  0x010220, 0x4d0081, 256 * 1024, 256, USE_CLSR) },
	{ INFO("s25fl512s_256k",  0x010220, 0x4d00, 256 * 1024, 256, USE_CLSR) },
	{ INFO("s25fl512s_64k",  0x010220, 0x4d01, 64 * 1024, 1024, USE_CLSR) },
	{ INFO("s25fl512s_512k", 0x010220, 0x4f00, 256 * 1024, 256, USE_CLSR) },
	{ INFO6("s25fl128s",  0x012018, 0x4d0180, 64 * 1024, 256, USE_CLSR) },
	{ INFO("s25fl129p0", 0x012018, 0x4d00, 256 * 1024,  64, USE_CLSR) },
	{ INFO("s25fl129p1", 0x012018, 0x4d01,  64 * 1024, 256, USE_CLSR) },
	{ INFO("s25fl116k",  0x014015,      0,  64 * 1024,  32, SECT_4K) },
	{ INFO("s25fl208k",  0x014014,      0,  64 * 1024,  16, SECT_4K) },
	{ INFO("s25fl128l",  0x016018,      0,  64 * 1024, 256, SECT_4K | SPI_NOR_4B_OPCODES) },
	{ INFO("s25fl256l",  0x016019,      0,  64 * 1024, 512, SECT_4K | SPI_NOR_4B_OPCODES) },
	{ INFO6("s25hl256t",  0x342a19, 0x0f0390, 256 * 1024, 128, SPI_NOR_4B_OPCODES | USE_CLSR) },
	{ INFO6("s25hl512t",  0x342a1a, 0x0f0390, 256 * 1024, 256, SPI_NOR_4B_OPCODES | USE_CLSR) },
	{ INFO6("s25hl01gt",  0x342a1b, 0x0f0390, 256 * 1024, 512, SPI_NOR_4B_OPCODES | USE_CLSR) },
	{ INFO6("s25hs256t",  0x342b19, 0x0f0390, 256 * 1024, 128, SPI_NOR_4B_OPCODES | USE_CLSR) },
	{ INFO6("s25hs512t",  0x342b1a, 0x0f0390, 256 * 1024, 256, SPI_NOR_4B_OPCODES | USE_CLSR) },
	{ INFO6("s25hs01gt",  0x342b1b, 0x0f0390, 256 * 1024, 512, SPI_NOR_4B_OPCODES | USE_CLSR) },
#endif // CONFIG_SPI_FLASH_ONLY_SINGLE_READ
#endif // CONFIG_SPI_FLASH_SPANSION
#ifdef CONFIG_SPI_FLASH_SST		/* SST */
	/* SST -- large erase sizes are "overlays", "sectors" are 4K */
	{ INFO("sst25vf040b", 0xbf258d, 0, 64 * 1024,  8, SECT_4K | SST_WRITE) },
	{ INFO("sst25vf080b", 0xbf258e, 0, 64 * 1024, 16, SECT_4K | SST_WRITE) },
	{ INFO("sst25vf016b", 0xbf2541, 0, 64 * 1024, 32, SECT_4K | SST_WRITE) },
	{ INFO("sst25vf032b", 0xbf254a, 0, 64 * 1024, 64, SECT_4K | SST_WRITE) },
	{ INFO("sst25vf064c", 0xbf254b, 0, 64 * 1024, 128, SECT_4K) },
	{ INFO("sst25wf512",  0xbf2501, 0, 64 * 1024,  1, SECT_4K | SST_WRITE) },
	{ INFO("sst25wf010",  0xbf2502, 0, 64 * 1024,  2, SECT_4K | SST_WRITE) },
	{ INFO("sst25wf020",  0xbf2503, 0, 64 * 1024,  4, SECT_4K | SST_WRITE) },
	{ INFO("sst25wf020a", 0x621612, 0, 64 * 1024,  4, SECT_4K) },
	{ INFO("sst25wf040b", 0x621613, 0, 64 * 1024,  8, SECT_4K) },
	{ INFO("sst25wf040",  0xbf2504, 0, 64 * 1024,  8, SECT_4K | SST_WRITE) },
	{ INFO("sst25wf080",  0xbf2505, 0, 64 * 1024, 16, SECT_4K | SST_WRITE) },
	{ INFO("sst26wf016",  0xbf2651, 0, 64 * 1024,  32, SECT_4K) },
	{ INFO("sst26wf032",  0xbf2622, 0, 64 * 1024,  64, SECT_4K) },
	{ INFO("sst26wf064",  0xbf2643, 0, 64 * 1024, 128, SECT_4K) },
#ifndef CONFIG_SPI_FLASH_ONLY_SINGLE_READ
	{ INFO("sst26vf064b", 0xbf2643, 0, 64 * 1024, 128, SECT_4K | SPI_NOR_DUAL_READ | SPI_NOR_QUAD_READ) },
#else
	{ INFO("sst26vf064b", 0xbf2643, 0, 64 * 1024, 128, SECT_4K) },
#endif // CONFIG_SPI_FLASH_ONLY_SINGLE_READ
#endif // CONFIG_SPI_FLASH_SPANSION
#ifdef CONFIG_SPI_FLASH_STMICRO		/* STMICRO */
	/* ST Microelectronics -- newer production may have feature updates */
	{ INFO("m25p10",  0x202011,  0,  32 * 1024,   4, 0) },
	{ INFO("m25p20",  0x202012,  0,  64 * 1024,   4, 0) },
	{ INFO("m25p40",  0x202013,  0,  64 * 1024,   8, 0) },
	{ INFO("m25p80",  0x202014,  0,  64 * 1024,  16, 0) },
	{ INFO("m25p16",  0x202015,  0,  64 * 1024,  32, 0) },
	{ INFO("m25p32",  0x202016,  0,  64 * 1024,  64, 0) },
	{ INFO("m25p64",  0x202017,  0,  64 * 1024, 128, 0) },
	{ INFO("m25p128", 0x202018,  0, 256 * 1024,  64, 0) },
	{ INFO("m25pe16", 0x208015,  0, 64 * 1024, 32, SECT_4K) },
	{ INFO("m25px64",    0x207117,  0, 64 * 1024, 128, 0) },
#ifndef CONFIG_SPI_FLASH_ONLY_SINGLE_READ
	{ INFO("m25px16",    0x207115,  0, 64 * 1024, 32, SECT_4K | SPI_NOR_DUAL_READ | SPI_NOR_QUAD_READ) },
#else
	{ INFO("m25px16",    0x207115,  0, 64 * 1024, 32, SECT_4K) },
#endif // CONFIG_SPI_FLASH_ONLY_SINGLE_READ
#endif // CONFIG_SPI_FLASH_STMICRO
#ifdef CONFIG_SPI_FLASH_WINBOND		/* WINBOND */
	/* Winbond -- w25x "blocks" are 64K, "sectors" are 4KiB */
	{ INFO("w25p80", 0xef2014, 0x0,	64 * 1024,    16, 0) },
	{ INFO("w25p16", 0xef2015, 0x0,	64 * 1024,    32, 0) },
	{ INFO("w25p32", 0xef2016, 0x0,	64 * 1024,    64, 0) },
	{ INFO("w25x05", 0xef3010, 0, 64 * 1024,  1,  SECT_4K) },
	{ INFO("w25x40", 0xef3013, 0, 64 * 1024,  8,  SECT_4K) },
	{ INFO("w25x16", 0xef3015, 0, 64 * 1024,  32, SECT_4K) },
	{ INFO("w25x32", 0xef3016, 0, 64 * 1024,  64, SECT_4K) },
	{ INFO("w25q20cl", 0xef4012, 0, 64 * 1024,  4, SECT_4K) },
	{ INFO("w25q20bw", 0xef5012, 0, 64 * 1024,  4, SECT_4K) },
	{ INFO("w25q20ew", 0xef6012, 0, 64 * 1024,  4, SECT_4K) },
	{ INFO("w25q80", 0xef5014, 0, 64 * 1024,  16, SECT_4K) },
	{ INFO("w25x64", 0xef3017, 0, 64 * 1024, 128, SECT_4K) },
#ifndef CONFIG_SPI_FLASH_ONLY_SINGLE_READ
	{ INFO("w25q16dw", 0xef6015, 0, 64 * 1024,  32,
			SECT_4K | SPI_NOR_DUAL_READ | SPI_NOR_QUAD_READ |
			SPI_NOR_HAS_LOCK | SPI_NOR_HAS_TB) },
	{ INFO("w25q32", 0xef4016, 0, 64 * 1024,  64,
			SECT_4K | SPI_NOR_DUAL_READ | SPI_NOR_QUAD_READ) },
	{ INFO("w25q32dw", 0xef6016, 0, 64 * 1024,  64,
			SECT_4K | SPI_NOR_DUAL_READ | SPI_NOR_QUAD_READ |
			SPI_NOR_HAS_LOCK | SPI_NOR_HAS_TB) },
	{ INFO("w25q32jv", 0xef7016, 0, 64 * 1024,  64,
			SECT_4K | SPI_NOR_DUAL_READ | SPI_NOR_QUAD_READ |
			SPI_NOR_HAS_LOCK | SPI_NOR_HAS_TB) },
	{ INFO("w25q64dw", 0xef6017, 0, 64 * 1024, 128,
			SECT_4K | SPI_NOR_DUAL_READ | SPI_NOR_QUAD_READ |
			SPI_NOR_HAS_LOCK | SPI_NOR_HAS_TB) },
	{ INFO("w25q64jv", 0xef7017, 0, 64 * 1024, 128,
			SECT_4K | SPI_NOR_DUAL_READ | SPI_NOR_QUAD_READ |
			SPI_NOR_HAS_LOCK | SPI_NOR_HAS_TB) },
	{ INFO("w25q128fw", 0xef6018, 0, 64 * 1024, 256,
			SECT_4K | SPI_NOR_DUAL_READ | SPI_NOR_QUAD_READ |
			SPI_NOR_HAS_LOCK | SPI_NOR_HAS_TB) },
	{ INFO("w25q128jv", 0xef7018, 0, 64 * 1024, 256,
			SECT_4K | SPI_NOR_DUAL_READ | SPI_NOR_QUAD_READ |
			SPI_NOR_HAS_LOCK | SPI_NOR_HAS_TB) },
	{ INFO("w25q256fw", 0xef6019, 0, 64 * 1024, 512,
			SECT_4K | SPI_NOR_DUAL_READ | SPI_NOR_QUAD_READ |
			SPI_NOR_HAS_LOCK | SPI_NOR_HAS_TB) },
	{ INFO("w25q256fm", 0xef7019, 0, 64 * 1024, 512,
			SECT_4K | SPI_NOR_DUAL_READ | SPI_NOR_QUAD_READ |
			SPI_NOR_HAS_LOCK | SPI_NOR_HAS_TB) },
	{ INFO("w25q512jv", 0xef4020, 0, 64 * 1024, 1024,
			SECT_4K | SPI_NOR_DUAL_READ | SPI_NOR_QUAD_READ |
			SPI_NOR_HAS_LOCK | SPI_NOR_HAS_TB) },
	{ INFO("w25q512jvfm", 0xef7020, 0, 64 * 1024, 1024,
			SECT_4K | SPI_NOR_DUAL_READ | SPI_NOR_QUAD_READ |
			SPI_NOR_HAS_LOCK | SPI_NOR_HAS_TB) },
	{ INFO("w25q01jv", 0xef4021, 0, 64 * 1024, 2048,
			SECT_4K | SPI_NOR_DUAL_READ | SPI_NOR_QUAD_READ |
			SPI_NOR_HAS_LOCK | SPI_NOR_HAS_TB) },
	{ INFO("w25q02jv", 0xef7022, 0, 64 * 1024, 4096,
			SECT_4K | SPI_NOR_DUAL_READ | SPI_NOR_QUAD_READ |
			SPI_NOR_HAS_LOCK | SPI_NOR_HAS_TB) },
	{ INFO("w25q01jvfim", 0xef7021, 0, 64 * 1024, 2048,
			SECT_4K | SPI_NOR_DUAL_READ | SPI_NOR_QUAD_READ |
			SPI_NOR_HAS_LOCK | SPI_NOR_HAS_TB) },
	{ INFO("w25q80bl", 0xef4014, 0, 64 * 1024,  16, SECT_4K | SPI_NOR_DUAL_READ | SPI_NOR_QUAD_READ) },
	{ INFO("w25q16cl", 0xef4015, 0, 64 * 1024,  32, SECT_4K | SPI_NOR_DUAL_READ | SPI_NOR_QUAD_READ) },
	{ INFO("w25q64cv", 0xef4017, 0, 64 * 1024, 128, SECT_4K | SPI_NOR_DUAL_READ | SPI_NOR_QUAD_READ) },
	{ INFO("w25q128",  0xef4018, 0, 64 * 1024, 256, SECT_4K | SPI_NOR_DUAL_READ | SPI_NOR_QUAD_READ) },
	{ INFO("w25q256",  0xef4019, 0, 64 * 1024, 512, SECT_4K | SPI_NOR_DUAL_READ | SPI_NOR_QUAD_READ) },
	{ INFO("w25m512jv",0xef7119, 0, 64 * 1024, 1024,SECT_4K | SPI_NOR_QUAD_READ | SPI_NOR_DUAL_READ) },
#else
	{ INFO("w25q16dw", 0xef6015, 0, 64 * 1024,  32,
			SECT_4K | SPI_NOR_HAS_LOCK | SPI_NOR_HAS_TB) },
	{ INFO("w25q32", 0xef4016, 0, 64 * 1024,  64, SECT_4K) },
	{ INFO("w25q32dw", 0xef6016, 0, 64 * 1024,  64,
			SECT_4K | SPI_NOR_HAS_LOCK | SPI_NOR_HAS_TB) },
	{ INFO("w25q32jv", 0xef7016, 0, 64 * 1024,  64,
			SECT_4K | SPI_NOR_HAS_LOCK | SPI_NOR_HAS_TB) },
	{ INFO("w25q64dw", 0xef6017, 0, 64 * 1024, 128,
			SECT_4K | SPI_NOR_HAS_LOCK | SPI_NOR_HAS_TB) },
	{ INFO("w25q64jv", 0xef7017, 0, 64 * 1024, 128,
			SECT_4K | SPI_NOR_HAS_LOCK | SPI_NOR_HAS_TB) },
	{ INFO("w25q128fw", 0xef6018, 0, 64 * 1024, 256,
			SECT_4K | SPI_NOR_HAS_LOCK | SPI_NOR_HAS_TB) },
	{ INFO("w25q128jv", 0xef7018, 0, 64 * 1024, 256,
			SECT_4K | SPI_NOR_HAS_LOCK | SPI_NOR_HAS_TB) },
	{ INFO("w25q256fw", 0xef6019, 0, 64 * 1024, 512,
			SECT_4K | SPI_NOR_HAS_LOCK | SPI_NOR_HAS_TB) },
	{ INFO("w25q256fm", 0xef7019, 0, 64 * 1024, 512,
			SECT_4K | SPI_NOR_HAS_LOCK | SPI_NOR_HAS_TB) },
	{ INFO("w25q512jv", 0xef4020, 0, 64 * 1024, 1024,
			SECT_4K | SPI_NOR_HAS_LOCK | SPI_NOR_HAS_TB) },
	{ INFO("w25q512jvfm", 0xef7020, 0, 64 * 1024, 1024,
			SECT_4K | SPI_NOR_HAS_LOCK | SPI_NOR_HAS_TB) },
	{ INFO("w25q01jv", 0xef4021, 0, 64 * 1024, 2048,
			SECT_4K | SPI_NOR_HAS_LOCK | SPI_NOR_HAS_TB) },
	{ INFO("w25q02jv", 0xef7022, 0, 64 * 1024, 4096,
			SECT_4K | SPI_NOR_HAS_LOCK | SPI_NOR_HAS_TB) },
	{ INFO("w25q01jvfim", 0xef7021, 0, 64 * 1024, 2048,
			SECT_4K | SPI_NOR_HAS_LOCK | SPI_NOR_HAS_TB) },
	{ INFO("w25q80bl", 0xef4014, 0, 64 * 1024,  16, SECT_4K) },
	{ INFO("w25q16cl", 0xef4015, 0, 64 * 1024,  32, SECT_4K) },
	{ INFO("w25q64cv", 0xef4017, 0, 64 * 1024, 128, SECT_4K) },
	{ INFO("w25q128",  0xef4018, 0, 64 * 1024, 256, SECT_4K) },
	{ INFO("w25q256",  0xef4019, 0, 64 * 1024, 512, SECT_4K) },
	{ INFO("w25m512jv",0xef7119, 0, 64 * 1024, 1024,SECT_4K) },
#endif // CONFIG_SPI_FLASH_ONLY_SINGLE_READ
#endif // CONFIG_SPI_FLASH_WINBOND
#ifdef CONFIG_SPI_FLASH_XMC
	/* XMC (Wuhan Xinxin Semiconductor Manufacturing Corp.) */
#ifndef CONFIG_SPI_FLASH_ONLY_SINGLE_READ
	{ INFO("XM25QH64A", 0x207017, 0, 64 * 1024, 128, SECT_4K | SPI_NOR_DUAL_READ | SPI_NOR_QUAD_READ) },
	{ INFO("XM25QH128A", 0x207018, 0, 64 * 1024, 256, SECT_4K | SPI_NOR_DUAL_READ | SPI_NOR_QUAD_READ) },
#else
	{ INFO("XM25QH64A", 0x207017, 0, 64 * 1024, 128, SECT_4K) },
	{ INFO("XM25QH128A", 0x207018, 0, 64 * 1024, 256, SECT_4K) },
#endif // CONFIG_SPI_FLASH_ONLY_SINGLE_READ
#endif // CONFIG_SPI_FLASH_XMC
	{ },
};
