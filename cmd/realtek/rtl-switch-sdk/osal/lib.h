/*
 * Copyright (C) 2024 Realtek Semiconductor Corp.
 * All Rights Reserved.
 *
 * This program is the proprietary software of Realtek Semiconductor
 * Corporation and/or its licensors, and only be used, duplicated,
 * modified or distributed under the authorized license from Realtek.
 *
 * ANY USE OF THE SOFTWARE OTHER THAN AS AUTHORIZED UNDER
 * THIS LICENSE OR COPYRIGHT LAW IS PROHIBITED.
 *
 * $Revision$
 * $Date$
 *
 * Purpose : RTK switch OS Adaptation Layer
 *
 */


#ifndef __OSAL_H__
#define __OSAL_H__

#ifdef CONFIG_UBOOT_ENV
#include <common.h>
#include <linux/string.h>
#include "uboot_osal.h"
#else
#include <string.h>
#endif

#ifndef CONFIG_UBOOT_ENV
void *osal_memset(void *s, int c, size_t n);
void *osal_memcpy(void *d, void *s, size_t n);
#endif

#endif /* __OSAL_H__ */


