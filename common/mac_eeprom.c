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

#define MAC_ADDR_LEN 6
#define MAX_ETH_NUM 6

/* read MAC from EEPROM at an offset location, before call to this function,
 * make sure the output array ethaddr[] has been allocated properly.
 */
int get_mac_eeprom(const char *ethaddr_name, unsigned char *ethaddr) {
  struct udevice *dev;
  unsigned int mac_offset[MAX_ETH_NUM];
  unsigned int offset;
  size_t sz = MAX_ETH_NUM;
  char c;
  int ret;

  if (uclass_first_device_err(UCLASS_I2C_EEPROM, &dev))
    return -ENODEV;

  /* read offset value from dts eeprom property */
  ret = dev_read_u32_array(dev, "eth2macoffset", mac_offset, sz);
  if (ret)
    return ret;

  /* get offset val from array */
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
    return -EINVAL;
    break;
  }

  /* 0xff is an invalid offset */
  if (ethaddr && offset != 0xff) {
    if (i2c_eeprom_read(dev, offset, ethaddr, MAC_ADDR_LEN))
      return -EINVAL;
    else
      return (is_valid_ethaddr(ethaddr)) ? 0 : (-EINVAL);
  } else
    return -EINVAL;
}

int eth_env_update_enetaddr_eeprom(const char *name, unsigned char *enetaddr) {
  const int ETH_ADDR_LEN = 6;
  unsigned char ethaddr_eeprom[ETH_ADDR_LEN];
  int ret;
  char ethaddr_eeprom_mac[ARP_HLEN_ASCII + 1];
  char *env_mac;

  ret = get_mac_eeprom(name, ethaddr_eeprom);
  if (ret)
    return ret;

  sprintf(ethaddr_eeprom_mac, "%pM", ethaddr_eeprom);

  env_mac = env_get(name);
  /* if cannot find the env variable or the existing env is not the same as in
   * eeprom */
  if (env_mac == NULL ||
      strncmp(ethaddr_eeprom_mac, env_mac, (ARP_HLEN_ASCII + 1)) != 0) {
    ret = env_set_mac_force(name, ethaddr_eeprom_mac);
    if (!ret) {
      printf("Saving MAC address %s from EEPROM to %s ...\n",
             ethaddr_eeprom_mac, name);
      return (env_save());
    }
  }

  return 0;
}
