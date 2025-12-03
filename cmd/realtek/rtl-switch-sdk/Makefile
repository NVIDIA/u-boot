# SPDX-License-Identifier: GPL-2.0+
#
# Makefile for Realtek Switch SDK in U-Boot
#
# Copyright (C) 2024 Realtek Semiconductor Corp.

# U-Boot build system integration
# Core SDK modules
obj-y := \
	rtk_switch.o \
	chip.o \
	acl.o \
	cpu.o \
	dot1x.o \
	eee.o \
	gpio.o \
	i2c.o \
	igmp.o \
	interrupt.o \
	l2.o \
	leaky.o \
	led.o \
	mirror.o \
	oam.o \
	port.o \
	ptp.o \
	qos.o \
	rate.o \
	rldp.o \
	stat.o \
	storm.o \
	svlan.o \
	trap.o \
	trunk.o \
	vlan.o \
	wol.o

# DAL layer
obj-y += \
	dal/dal_mgmts.o \
	dal/smi.o \
	dal/reg.o

# OSAL layer (u-boot specific)
obj-y += \
	osal/lib.o \
	osal/uboot_osal.o

# RTL8367C chip support
obj-y += \
	dal/rtl8367c/dal_rtl8367c_mapper.o \
	dal/rtl8367c/dal_rtl8367c_switch.o \
	dal/rtl8367c/dal_rtl8367c_port.o \
	dal/rtl8367c/dal_rtl8367c_vlan.o \
	dal/rtl8367c/dal_rtl8367c_l2.o \
	dal/rtl8367c/dal_rtl8367c_qos.o \
	dal/rtl8367c/dal_rtl8367c_stat.o \
	dal/rtl8367c/dal_rtl8367c_rate.o \
	dal/rtl8367c/dal_rtl8367c_acl.o \
	dal/rtl8367c/dal_rtl8367c_cpu.o \
	dal/rtl8367c/dal_rtl8367c_dot1x.o \
	dal/rtl8367c/dal_rtl8367c_eee.o \
	dal/rtl8367c/dal_rtl8367c_gpio.o \
	dal/rtl8367c/dal_rtl8367c_i2c.o \
	dal/rtl8367c/dal_rtl8367c_igmp.o \
	dal/rtl8367c/dal_rtl8367c_interrupt.o \
	dal/rtl8367c/dal_rtl8367c_leaky.o \
	dal/rtl8367c/dal_rtl8367c_led.o \
	dal/rtl8367c/dal_rtl8367c_mirror.o \
	dal/rtl8367c/dal_rtl8367c_oam.o \
	dal/rtl8367c/dal_rtl8367c_ptp.o \
	dal/rtl8367c/dal_rtl8367c_rldp.o \
	dal/rtl8367c/dal_rtl8367c_storm.o \
	dal/rtl8367c/dal_rtl8367c_svlan.o \
	dal/rtl8367c/dal_rtl8367c_trap.o \
	dal/rtl8367c/dal_rtl8367c_trunk.o \
	dal/rtl8367c/dal_rtl8367c_wol.o

# RTL8367C ASIC drivers
obj-y += \
	dal/rtl8367c/rtl8367c_asicdrv.o \
	dal/rtl8367c/rtl8367c_asicdrv_acl.o \
	dal/rtl8367c/rtl8367c_asicdrv_cputag.o \
	dal/rtl8367c/rtl8367c_asicdrv_dot1x.o \
	dal/rtl8367c/rtl8367c_asicdrv_eav.o \
	dal/rtl8367c/rtl8367c_asicdrv_eee.o \
	dal/rtl8367c/rtl8367c_asicdrv_fc.o \
	dal/rtl8367c/rtl8367c_asicdrv_green.o \
	dal/rtl8367c/rtl8367c_asicdrv_hsb.o \
	dal/rtl8367c/rtl8367c_asicdrv_i2c.o \
	dal/rtl8367c/rtl8367c_asicdrv_igmp.o \
	dal/rtl8367c/rtl8367c_asicdrv_inbwctrl.o \
	dal/rtl8367c/rtl8367c_asicdrv_interrupt.o \
	dal/rtl8367c/rtl8367c_asicdrv_led.o \
	dal/rtl8367c/rtl8367c_asicdrv_lut.o \
	dal/rtl8367c/rtl8367c_asicdrv_meter.o \
	dal/rtl8367c/rtl8367c_asicdrv_mib.o \
	dal/rtl8367c/rtl8367c_asicdrv_mirror.o \
	dal/rtl8367c/rtl8367c_asicdrv_misc.o \
	dal/rtl8367c/rtl8367c_asicdrv_oam.o \
	dal/rtl8367c/rtl8367c_asicdrv_phy.o \
	dal/rtl8367c/rtl8367c_asicdrv_port.o \
	dal/rtl8367c/rtl8367c_asicdrv_portIsolation.o \
	dal/rtl8367c/rtl8367c_asicdrv_qos.o \
	dal/rtl8367c/rtl8367c_asicdrv_rldp.o \
	dal/rtl8367c/rtl8367c_asicdrv_rma.o \
	dal/rtl8367c/rtl8367c_asicdrv_scheduling.o \
	dal/rtl8367c/rtl8367c_asicdrv_storm.o \
	dal/rtl8367c/rtl8367c_asicdrv_svlan.o \
	dal/rtl8367c/rtl8367c_asicdrv_trunking.o \
	dal/rtl8367c/rtl8367c_asicdrv_unknownMulticast.o \
	dal/rtl8367c/rtl8367c_asicdrv_vlan.o

# Compiler flags
ccflags-y += -I$(src)
ccflags-y += -I$(src)/dal
ccflags-y += -I$(src)/dal/rtl8367c
ccflags-y += -I$(src)/dal/rtl8367d
ccflags-y += -I$(src)/dal/rtl8371c
ccflags-y += -I$(src)/osal
ccflags-y += -DCONFIG_UBOOT_ENV
ccflags-y += -DCONFIG_DAL_RTL8367C
ccflags-y += -DFORCE_PROBE_RTL8363SC_VB
ccflags-y += -Wno-unused-function
ccflags-y += -Wno-unused-variable

# Handle stack usage files: U-Boot adds -fstack-usage globally
# Create directories so .su files can be written (they're informational only)
$(shell mkdir -p $(obj)/dal/rtl8367c $(obj)/dal/rtl8367d $(obj)/dal/rtl8371c $(obj)/osal)
ccflags-y += -Wno-stack-usage
ccflags-y += -DEMBEDDED_SUPPORT

