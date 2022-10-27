// SPDX-License-Identifier: GPL-2.0
/*
 * Copyright 2022 IBM Corp.
 */

#include <common.h>
#include <dm/uclass.h>
#include <tpm-common.h>
#include <tpm-v2.h>

int board_late_init(void)
{
	int rc;
	struct udevice *dev;
	/*
	 * The digest is just an arbitrary sequence for now to ensure that the
	 * TPM gets "poisoned."
	 */
	const unsigned char digest[32] = {
		0x6e, 0x65, 0x76, 0x65, 0x72, 0x67, 0x6f, 0x6e,
		0x6e, 0x61, 0x67, 0x69, 0x76, 0x65, 0x79, 0x6f,
		0x75, 0x75, 0x70, 0x6e, 0x65, 0x76, 0x65, 0x72,
		0x67, 0x6f, 0x6e, 0x6e, 0x61, 0x6c, 0x65, 0x74
	};

	rc = uclass_first_device_err(UCLASS_TPM, &dev);
	if (rc)
		return 0;

	rc = tpm_init(dev);
	if (rc)
		return 0;

	rc = tpm2_startup(dev, TPM2_SU_CLEAR);
	if (rc)
		return 0;

	rc = tpm2_pcr_extend(dev, 0, digest);
	if (!rc)
		printf("TPM: PCR0 extended.\n");

	return 0;
}
