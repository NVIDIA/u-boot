// SPDX-License-Identifier: GPL-2.0+
/*
 * Copyright (C) 2022 AMI Inc
 *		      Hongwei Zhang <hongewiz@ami.com>
 */

#include <common.h>
#include <dm.h>
#include <environment.h>
#include <i2c_eeprom.h>
#include <netdev.h>

#define MAC_ADDR_LEN		6
#define MAX_ETH_NUM             6

int eth_env_update_enetaddr_eeprom(const char *name, unsigned char *enetaddr);

/* read MAC from EEPROM at an offset location, before call to this function,
 * make sure the output array ethaddr[] has been allocated properly.
 */
int get_mac_eeprom(const char *ethaddr_name, unsigned char *ethaddr)
{
	struct udevice *dev;
	unsigned int mac_offset[MAX_ETH_NUM];
	unsigned int offset;
	size_t sz = MAX_ETH_NUM;
	char c;
	int ret;
	int i;

	ret = uclass_first_device_err(UCLASS_I2C_EEPROM, &dev);

	if (ret)
		return ret;

	/* read offset value from dts eeprom property */
	ret = dev_read_u32_array(dev, "macoffset", mac_offset, sz);

	if (ret)
		return ret;

	c = *(ethaddr_name + 3);
	switch (c) {
	case 'a':
		offset = mac_offset[0];
		break;
	case '1':
		offset = mac_offset[1];
		break;
	case '2':
		offset = mac_offset[2];
		break;
	case '3':
		offset = mac_offset[3];
		break;
	case '4':
		offset = mac_offset[4];
		break;
	case '5':
		offset = mac_offset[5];
		break;
	default:
		ret = -EINVAL;
		break;
	}

	/* get offset val from array */
	if (ethaddr && offset != 0xff)
		ret = i2c_eeprom_read(dev, offset, ethaddr, MAC_ADDR_LEN);

	if (ret)
		return ret;

	return 0;
}

int eth_env_update_enetaddr_eeprom(const char *name, unsigned char *enetaddr)
{
	const int ETH_ADDR_LEN = 6;
	unsigned char ethaddr_eeprom[ETH_ADDR_LEN];
	char buf[ARP_HLEN_ASCII + 1];
	bool match = true;
	int ret;
	int i;

	char c;

	ret = get_mac_eeprom(name, ethaddr_eeprom);
	if (ret)
		return ret;

	/* check MAC address */
	for (i = 0; i < ETH_ADDR_LEN; i++) {
		if (ethaddr_eeprom[i] != enetaddr[i]) {
			match = false;
			break;
		}
	}

	if (match == false) {
		sprintf(buf, "%pM", ethaddr_eeprom);
		return env_set(name, buf);
	}

	return 0;
}
