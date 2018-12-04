/*
 * Copyright (c) 2015-2017, Renesas Electronics Corporation. All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#ifndef	RCAR_PRINTF_H__
#define	RCAR_PRINTF_H__

#include <string.h>

void		rcar_set_log_time(void);
int32_t		rcar_set_log_data(int32_t c);
int32_t		rcar_log_init(void);

#if IMAGE_BL31
extern uint64_t rcar_stack_generic_timer[5];
#endif

#endif	/* RCAR_PRINTF_H__	*/
