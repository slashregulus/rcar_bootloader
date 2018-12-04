/*
 * Copyright (c) 2015-2017, Renesas Electronics Corporation. All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#ifndef	__BOOT_INIT_DRAM_
#define	__BOOT_INIT_DRAM_

extern int32_t InitDram(void);
#define INITDRAM_OK (0)
#define INITDRAM_NG (0xffffffff)
#define INITDRAM_ERR_I (0xffffffff)
#define INITDRAM_ERR_O (0xfffffffe)
#define INITDRAM_ERR_T (0xfffffff0)

#endif /* __BOOT_INIT_DRAM_*/
