// SPDX-License-Identifier: GPL-2.0+
/*
 * Glacier ERoT I2C VDM Query for Factory Reset
 *
 * Queries Glacier's volatile data over I2C bus 15 using MCTP VDM
 * encapsulated in SMBus framing. If factory reset is requested,
 * sets U-Boot env flags for initramfs to act on.
 */

#include <common.h>
#include <dm.h>
#include <i2c.h>
#include <linux/crc8.h>

#define GLACIER_I2C_BUS  15
#define GLACIER_I2C_ADDR 0x52

#define VDM_RESPONSE_RETRIES 5
#define VDM_RESPONSE_POLL_MS 10

/* VDM command structure offsets */
#define VDM_CMD_OFFSET		  15
#define VDM_RESPONSE_CC_OFFSET	  17
#define VDM_VOLATILE_DATA_OFFSET 18
#define VDM_CMD_VOLATILE_QUERY	  0x1f
#define VDM_CMD_INVALID	  0xff

/* MCTP VDM Volatile Data Query command (18 bytes) */
static const u8 vdm_volatile_query[] = {
	0x0f,		/* SMBus command code (MCTP) */
	0x0f,		/* Byte count (15) */
	0x01,		/* Source slave address */
	0x01,		/* MCTP header version */
	0x00,		/* Destination EID (Glacier) */
	0x00,		/* Source EID (BMC) */
	0xc8,		/* Flags: SOM|EOM|TO */
	0x7f,		/* Message type: Vendor IANA */
	0x47, 0x16, 0x00, 0x00,	/* NVIDIA IANA (0x1647 LE) */
	0x81,		/* Rq=1, Instance=1 */
	0x01,		/* NVIDIA message type */
	0x1f,		/* Command: Volatile Data Query */
	0x01,		/* Message version */
	0x01,		/* Sub-cmd: Cmd_Query_Volatile_Data */
	0x00,		/* Checksum placeholder */
};

/* Read response command */
static const u8 vdm_read_response = 0x0d;

static u8 calc_smbus_checksum(u8 addr, const u8 *data, int len)
{
	u8 dest_addr = (addr << 1);
	u8 checksum;

	checksum = crc8(0, &dest_addr, 1);
	checksum = crc8(checksum, data, len);
	return checksum;
}

/*
 * Send I2C VDM command to Glacier using dm_i2c_xfer for raw SMBus access.
 * Returns 0 on success, negative on error.
 */
static int vdm_i2c_send(struct udevice *dev, const u8 *data, int len)
{
	struct i2c_msg msg;

	msg.addr = GLACIER_I2C_ADDR;
	msg.flags = 0;
	msg.len = len;
	msg.buf = (u8 *)data;

	return dm_i2c_xfer(dev, &msg, 1);
}

/*
 * Poll Glacier for VDM response. Retries until a valid response is
 * received or the retry limit is reached.
 * Returns 0 on success, negative on error.
 */
static int vdm_i2c_read_response(struct udevice *dev, u8 *buf, int len, u8 cmd)
{
	struct i2c_msg msgs[2];
	int ret;
	int i;

	/* Write: 0x0D (read response command) */
	msgs[0].addr = GLACIER_I2C_ADDR;
	msgs[0].flags = 0;
	msgs[0].len = 1;
	msgs[0].buf = (u8 *)&vdm_read_response;

	/* Read response */
	msgs[1].addr = GLACIER_I2C_ADDR;
	msgs[1].flags = I2C_M_RD;
	msgs[1].len = len;
	msgs[1].buf = buf;

	for (i = 0; i < VDM_RESPONSE_RETRIES; i++) {
		mdelay(VDM_RESPONSE_POLL_MS);
		ret = dm_i2c_xfer(dev, msgs, 2);
		if (ret)
			continue;
		if (buf[VDM_CMD_OFFSET] == cmd)
			return 0;
		if (buf[VDM_CMD_OFFSET] != VDM_CMD_INVALID)
			printf("Unexpected response cmd=0x%02x\n",
			       buf[VDM_CMD_OFFSET]);
	}

	return -ETIMEDOUT;
}

/*
 * Check if a secure factory reset been requested by querying Glacier over I2C.
 * Returns true if a secure factory reset is requested, false if not.
 */
bool glacier_check_factory_reset(void)
{
	struct udevice *bus, *dev;
	u8 cmd[sizeof(vdm_volatile_query)];
	u8 resp[32];
	u8 cc;
	u8 volatile_data;
	int ret;

	/* Get I2C bus 15 */
	ret = uclass_get_device_by_seq(UCLASS_I2C, GLACIER_I2C_BUS, &bus);
	if (ret) {
		printf("Glacier: Failed to get I2C bus %d (err=%d)\n",
		       GLACIER_I2C_BUS, ret);
		return false;
	}

	/* Get chip device at 0x52 with 0-byte offset */
	ret = i2c_get_chip(bus, GLACIER_I2C_ADDR, 0, &dev);
	if (ret) {
		printf("Glacier: Failed to get chip 0x%02x (err=%d)\n",
		       GLACIER_I2C_ADDR, ret);
		return false;
	}

	/* Build command with correct checksum */
	memcpy(cmd, vdm_volatile_query, sizeof(cmd));
	cmd[sizeof(cmd) - 1] = calc_smbus_checksum(GLACIER_I2C_ADDR, cmd,
						   sizeof(cmd) - 1);

	/* Send VDM Volatile Data Query */
	ret = vdm_i2c_send(dev, cmd, sizeof(cmd));
	if (ret) {
		printf("I2C send failed (err=%d)\n", ret);
		return false;
	}

	ret = vdm_i2c_read_response(dev, resp, sizeof(resp),
				    VDM_CMD_VOLATILE_QUERY);
	if (ret) {
		printf("I2C read response failed (err=%d)\n", ret);
		return false;
	}

	/* Extract completion code */
	cc = resp[VDM_RESPONSE_CC_OFFSET];

	if (cc != 0x00) {
		printf("Error: Query failed with CC=0x%02x\n", cc);
		return false;
	}

	/* Glacier returns volatile data: 0x01 = factory reset, 0x00 = ignore */
	volatile_data = resp[VDM_VOLATILE_DATA_OFFSET];
	if (volatile_data == 0x00) {
		// No factory reset requested
		return false;
	}

	if (volatile_data != 0x01) {
		printf("Got unexpected volatile data (0x%02x)\n",
		       volatile_data);
		return false;
	}

	puts("Secure factory reset requested\n");

	return true;
}
