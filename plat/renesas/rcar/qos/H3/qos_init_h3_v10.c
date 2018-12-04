/*
 * Copyright (c) 2015-2017, Renesas Electronics Corporation. All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include <stdint.h>
#include <debug.h>
#include "../qos_common.h"
#include "qos_init_h3_v10.h"


#define	RCAR_QOS_VERSION		"rev.0.36"

#define	RCAR_QOS_NONE			(3U)
#define	RCAR_QOS_TYPE_DEFAULT		(0U)

#define	RCAR_DRAM_SPLIT_LINEAR		(0U)
#define	RCAR_DRAM_SPLIT_4CH		(1U)
#define	RCAR_DRAM_SPLIT_2CH		(2U)
#define	RCAR_DRAM_SPLIT_AUTO		(3U)

#define	AXI_BASE			(0xE6784000U)
#define	AXI_ADSPLCR0			(AXI_BASE + 0x0008U)
#define	AXI_ADSPLCR1			(AXI_BASE + 0x000CU)
#define	AXI_ADSPLCR2			(AXI_BASE + 0x0010U)
#define	AXI_ADSPLCR3			(AXI_BASE + 0x0014U)
#define	ADSPLCR0_ADRMODE_DEFAULT	((uint32_t)0U << 31U)
#define	ADSPLCR0_ADRMODE_GEN2		((uint32_t)1U << 31U)
#define	ADSPLCR0_SPLITSEL(x)		((uint32_t)(x) << 16U)
#define	ADSPLCR0_AREA(x)		((uint32_t)(x) <<  8U)
#define	ADSPLCR0_SWP			(0x0CU)

#define	MSTAT_BASE			(0xE67E0000U)
#define	MSTAT_FIX_QOS_BANK0		(MSTAT_BASE + 0x0000U)
#define	MSTAT_FIX_QOS_BANK1		(MSTAT_BASE + 0x1000U)
#define	MSTAT_BE_QOS_BANK0		(MSTAT_BASE + 0x2000U)
#define	MSTAT_BE_QOS_BANK1		(MSTAT_BASE + 0x3000U)
#define	MSTAT_SL_INIT			(MSTAT_BASE + 0x8000U)
#define	MSTAT_REF_ARS			(MSTAT_BASE + 0x8004U)
#define	MSTAT_STATQC			(MSTAT_BASE + 0x8008U)

#define	RALLOC_BASE			(0xE67F0000U)
#define	RALLOC_RAS			(RALLOC_BASE + 0x0000U)
#define	RALLOC_FIXTH			(RALLOC_BASE + 0x0004U)
#define	RALLOC_RAEN			(RALLOC_BASE + 0x0018U)
#define	RALLOC_REGGD			(RALLOC_BASE + 0x0020U)
#define	RALLOC_DANN			(RALLOC_BASE + 0x0030U)
#define	RALLOC_DANT			(RALLOC_BASE + 0x0038U)
#define	RALLOC_EC			(RALLOC_BASE + 0x003CU)
#define	RALLOC_EMS			(RALLOC_BASE + 0x0040U)
#define	RALLOC_INSFC			(RALLOC_BASE + 0x0050U)
#define	RALLOC_BERR			(RALLOC_BASE + 0x0054U)


#if RCAR_QOS_TYPE  == RCAR_QOS_TYPE_DEFAULT
static const mstat_slot_t mstat_fix[] = {
	{0x0000U, 0x0000000000000000UL},
	{0x0008U, 0x0000000000000000UL},
	{0x0010U, 0x0000000000000000UL},
	{0x0018U, 0x0000000000000000UL},
	{0x0020U, 0x0000000000000000UL},
	{0x0028U, 0x0000000000000000UL},
	{0x0030U, 0x0000000000000000UL},
	{0x0038U, 0x0000000000000000UL},
	{0x0040U, 0x00140C050000FFFFUL},
	{0x0048U, 0x0000000000000000UL},
	{0x0050U, 0x0000000000000000UL},
	{0x0058U, 0x001404030000FFFFUL},
	{0x0060U, 0x001408060000FFFFUL},
	{0x0068U, 0x0000000000000000UL},
	{0x0070U, 0x0000000000000000UL},
	{0x0078U, 0x0000000000000000UL},
	{0x0080U, 0x0000000000000000UL},
	{0x0088U, 0x00140C050000FFFFUL},
	{0x0090U, 0x001408060000FFFFUL},
	{0x0098U, 0x001404020000FFFFUL},
	{0x00A0U, 0x0000000000000000UL},
	{0x00A8U, 0x0000000000000000UL},
	{0x00B0U, 0x0000000000000000UL},
	{0x00B8U, 0x0000000000000000UL},
	{0x00C0U, 0x0000000000000000UL},
	{0x00C8U, 0x0000000000000000UL},
	{0x00D0U, 0x0000000000000000UL},
	{0x00D8U, 0x0000000000000000UL},
	{0x00E0U, 0x0000000000000000UL},
	{0x00E8U, 0x0000000000000000UL},
	{0x00F0U, 0x0000000000000000UL},
	{0x00F8U, 0x0000000000000000UL},
	{0x0100U, 0x0000000000000000UL},
	{0x0108U, 0x0000000000000000UL},
	{0x0110U, 0x0000000000000000UL},
	{0x0118U, 0x0000000000000000UL},
	{0x0120U, 0x0000000000000000UL},
	{0x0128U, 0x0000000000000000UL},
	{0x0130U, 0x0000000000000000UL},
	{0x0138U, 0x001004020000FFFFUL},
	{0x0140U, 0x001004020000FFFFUL},
	{0x0148U, 0x001004020000FFFFUL},
	{0x0150U, 0x001008050000FFFFUL},
	{0x0158U, 0x001008050000FFFFUL},
	{0x0160U, 0x001008050000FFFFUL},
	{0x0168U, 0x001008050000FFFFUL},
	{0x0170U, 0x001008050000FFFFUL},
	{0x0178U, 0x001004030000FFFFUL},
	{0x0180U, 0x001004030000FFFFUL},
	{0x0188U, 0x001004030000FFFFUL},
	{0x0190U, 0x001014140000FFFFUL},
	{0x0198U, 0x001014140000FFFFUL},
	{0x01A0U, 0x001008060000FFFFUL},
	{0x01A8U, 0x001008060000FFFFUL},
	{0x01B0U, 0x001008060000FFFFUL},
	{0x01B8U, 0x0000000000000000UL},
	{0x01C0U, 0x0000000000000000UL},
	{0x01C8U, 0x0000000000000000UL},
	{0x01D0U, 0x0000000000000000UL},
	{0x01D8U, 0x0000000000000000UL},
	{0x01E0U, 0x0000000000000000UL},
	{0x01E8U, 0x0000000000000000UL},
	{0x01F0U, 0x0000000000000000UL},
	{0x01F8U, 0x0000000000000000UL},
	{0x0200U, 0x0000000000000000UL},
	{0x0208U, 0x0000000000000000UL},
	{0x0210U, 0x0000000000000000UL},
	{0x0218U, 0x0000000000000000UL},
	{0x0220U, 0x0000000000000000UL},
	{0x0228U, 0x0000000000000000UL},
	{0x0230U, 0x0000000000000000UL},
	{0x0238U, 0x0000000000000000UL},
	{0x0240U, 0x0000000000000000UL},
	{0x0248U, 0x0000000000000000UL},
	{0x0250U, 0x0000000000000000UL},
	{0x0258U, 0x0000000000000000UL},
	{0x0260U, 0x0000000000000000UL},
	{0x0268U, 0x0000000000000000UL},
	{0x0270U, 0x0000000000000000UL},
	{0x0278U, 0x0000000000000000UL},
	{0x0280U, 0x0000000000000000UL},
	{0x0288U, 0x0000000000000000UL},
	{0x0290U, 0x0000000000000000UL},
	{0x0298U, 0x0000000000000000UL},
	{0x02A0U, 0x0000000000000000UL},
	{0x02A8U, 0x0000000000000000UL},
	{0x02B0U, 0x0000000000000000UL},
	{0x02B8U, 0x0000000000000000UL},
	{0x02C0U, 0x0000000000000000UL},
	{0x02C8U, 0x0000000000000000UL},
	{0x02D0U, 0x0000000000000000UL},
	{0x02D8U, 0x0000000000000000UL},
	{0x02E0U, 0x0000000000000000UL},
	{0x02E8U, 0x0000000000000000UL},
	{0x02F0U, 0x0000000000000000UL},
	{0x02F8U, 0x0000000000000000UL},
	{0x0300U, 0x0000000000000000UL},
	{0x0308U, 0x0000000000000000UL},
	{0x0310U, 0x0000000000000000UL},
	{0x0318U, 0x0000000000000000UL},
	{0x0320U, 0x0000000000000000UL},
	{0x0328U, 0x0000000000000000UL},
	{0x0330U, 0x0000000000000000UL},
	{0x0338U, 0x0000000000000000UL},
};

static const mstat_slot_t mstat_be[] = {
	{0x0000U, 0x001000100C8FFC01UL},
	{0x0008U, 0x001000100C8FFC01UL},
	{0x0010U, 0x001000100C8FFC01UL},
	{0x0018U, 0x001000100C8FFC01UL},
	{0x0020U, 0x001000100C8FFC01UL},
	{0x0028U, 0x001000100C8FFC01UL},
	{0x0030U, 0x001000100C8FFC01UL},
	{0x0038U, 0x001000100C8FFC01UL},
	{0x0040U, 0x0000000000000000UL},
	{0x0048U, 0x0000000000000000UL},
	{0x0050U, 0x001000100C8FFC01UL},
	{0x0058U, 0x0000000000000000UL},
	{0x0060U, 0x0000000000000000UL},
	{0x0068U, 0x001000100C8FFC01UL},
	{0x0070U, 0x001000100C8FFC01UL},
	{0x0078U, 0x001000100C8FFC01UL},
	{0x0080U, 0x001000100C8FFC01UL},
	{0x0088U, 0x0000000000000000UL},
	{0x0090U, 0x0000000000000000UL},
	{0x0098U, 0x0000000000000000UL},
	{0x00A0U, 0x001000100C8FFC01UL},
	{0x00A8U, 0x001000100C8FFC01UL},
	{0x00B0U, 0x001000100C8FFC01UL},
	{0x00B8U, 0x001000100C8FFC01UL},
	{0x00C0U, 0x001000100C8FFC01UL},
	{0x00C8U, 0x001000100C8FFC01UL},
	{0x00D0U, 0x001000100C8FFC01UL},
	{0x00D8U, 0x002000200C8FFC01UL},
	{0x00E0U, 0x002000200C8FFC01UL},
	{0x00E8U, 0x001000100C8FFC01UL},
	{0x00F0U, 0x001000100C8FFC01UL},
	{0x00F8U, 0x001000100C8FFC01UL},
	{0x0100U, 0x0000000000000000UL},
	{0x0108U, 0x002000200C8FFC01UL},
	{0x0110U, 0x001000100C8FFC01UL},
	{0x0118U, 0x001000100C8FFC01UL},
	{0x0120U, 0x0000000000000000UL},
	{0x0128U, 0x002000200C8FFC01UL},
	{0x0130U, 0x001000100C8FFC01UL},
	{0x0138U, 0x0000000000000000UL},
	{0x0140U, 0x0000000000000000UL},
	{0x0148U, 0x0000000000000000UL},
	{0x0150U, 0x0000000000000000UL},
	{0x0158U, 0x0000000000000000UL},
	{0x0160U, 0x0000000000000000UL},
	{0x0168U, 0x0000000000000000UL},
	{0x0170U, 0x0000000000000000UL},
	{0x0178U, 0x0000000000000000UL},
	{0x0180U, 0x0000000000000000UL},
	{0x0188U, 0x0000000000000000UL},
	{0x0190U, 0x0000000000000000UL},
	{0x0198U, 0x0000000000000000UL},
	{0x01A0U, 0x0000000000000000UL},
	{0x01A8U, 0x0000000000000000UL},
	{0x01B0U, 0x0000000000000000UL},
	{0x01B8U, 0x001000100C8FFC01UL},
	{0x01C0U, 0x001000200C8FFC01UL},
	{0x01C8U, 0x001000200C8FFC01UL},
	{0x01D0U, 0x001000200C8FFC01UL},
	{0x01D8U, 0x001000200C8FFC01UL},
	{0x01E0U, 0x001000100C8FFC01UL},
	{0x01E8U, 0x001000100C8FFC01UL},
	{0x01F0U, 0x001000100C8FFC01UL},
	{0x01F8U, 0x001000100C8FFC01UL},
	{0x0200U, 0x001000100C8FFC01UL},
	{0x0208U, 0x001000100C8FFC01UL},
	{0x0210U, 0x001000100C8FFC01UL},
	{0x0218U, 0x001000100C8FFC01UL},
	{0x0220U, 0x001000100C8FFC01UL},
	{0x0228U, 0x001000100C8FFC01UL},
	{0x0230U, 0x001000100C8FFC01UL},
	{0x0238U, 0x001000100C8FFC01UL},
	{0x0240U, 0x001000100C8FFC01UL},
	{0x0248U, 0x001000100C8FFC01UL},
	{0x0250U, 0x001000100C8FFC01UL},
	{0x0258U, 0x001000100C8FFC01UL},
	{0x0260U, 0x001000100C8FFC01UL},
	{0x0268U, 0x001000100C8FFC01UL},
	{0x0270U, 0x001000100C8FFC01UL},
	{0x0278U, 0x001000100C8FFC01UL},
	{0x0280U, 0x001000100C8FFC01UL},
	{0x0288U, 0x001000100C8FFC01UL},
	{0x0290U, 0x001000100C8FFC01UL},
	{0x0298U, 0x001000100C8FFC01UL},
	{0x02A0U, 0x001000100C8FFC01UL},
	{0x02A8U, 0x001000100C8FFC01UL},
	{0x02B0U, 0x001000100C8FFC01UL},
	{0x02B8U, 0x001000100C8FFC01UL},
	{0x02C0U, 0x001000100C8FFC01UL},
	{0x02C8U, 0x001000100C8FFC01UL},
	{0x02D0U, 0x001000100C8FFC01UL},
	{0x02D8U, 0x001000100C8FFC01UL},
	{0x02E0U, 0x001000100C8FFC01UL},
	{0x02E8U, 0x001000100C8FFC01UL},
	{0x02F0U, 0x001000200C8FFC01UL},
	{0x02F8U, 0x001000300C8FFC01UL},
	{0x0300U, 0x0000000000000000UL},
	{0x0308U, 0x001000200C8FFC01UL},
	{0x0310U, 0x001000300C8FFC01UL},
	{0x0318U, 0x0000000000000000UL},
	{0x0320U, 0x001000200C8FFC01UL},
	{0x0328U, 0x001000300C8FFC01UL},
	{0x0330U, 0x001000200C8FFC01UL},
	{0x0338U, 0x001000300C8FFC01UL},
};
#endif


void qos_init_h3_v10(void)
{
	/* DRAM Split Address mapping */
#if (RCAR_DRAM_SPLIT == RCAR_DRAM_SPLIT_4CH) || \
    (RCAR_DRAM_SPLIT == RCAR_DRAM_SPLIT_AUTO)
	NOTICE("BL2: DRAM Split is 4ch\n");
	io_write_32(AXI_ADSPLCR0, ADSPLCR0_ADRMODE_DEFAULT
				  | ADSPLCR0_SPLITSEL(0xFFU)
				  | ADSPLCR0_AREA(0x1BU)
				  | ADSPLCR0_SWP);
	io_write_32(AXI_ADSPLCR1, 0x00000000U);
	io_write_32(AXI_ADSPLCR2, 0xA8A90000U);
	io_write_32(AXI_ADSPLCR3, 0x00000000U);
#elif RCAR_DRAM_SPLIT == RCAR_DRAM_SPLIT_2CH
	NOTICE("BL2: DRAM Split is 2ch\n");
	io_write_32(AXI_ADSPLCR0, 0x00000000U);
	io_write_32(AXI_ADSPLCR1, ADSPLCR0_ADRMODE_DEFAULT
				  | ADSPLCR0_SPLITSEL(0xFFU)
				  | ADSPLCR0_AREA(0x1BU)
				  | ADSPLCR0_SWP);
	io_write_32(AXI_ADSPLCR2, 0x00000000U);
	io_write_32(AXI_ADSPLCR3, 0x00000000U);
#else
	NOTICE("BL2: DRAM Split is OFF\n");
#endif

#if !(RCAR_QOS_TYPE == RCAR_QOS_NONE)
#if RCAR_QOS_TYPE  == RCAR_QOS_TYPE_DEFAULT
	NOTICE("BL2: QoS is default setting(%s)\n", RCAR_QOS_VERSION);
#endif

	/* AR Cache setting */
	io_write_32(0xE67D1000U, 0x00000100U);
	io_write_32(0xE67D1008U, 0x00000100U);

	/* Resource Alloc setting */
	io_write_32(RALLOC_RAS,   0x00000040U);
	io_write_32(RALLOC_FIXTH, 0x000F0005U);
	io_write_32(RALLOC_REGGD, 0x00000004U);
	io_write_64(RALLOC_DANN,  0x0202000004040404UL);
	io_write_32(RALLOC_DANT,  0x003C1110U);
	io_write_32(RALLOC_EC,    0x00080001U);	/* need for H3 v1.* */
	io_write_64(RALLOC_EMS,   0x0000000000000000UL);
	io_write_32(RALLOC_INSFC, 0xC7840001U);
	io_write_32(RALLOC_BERR,  0x00000000U);

	/* MSTAT setting */
	io_write_32(MSTAT_SL_INIT, SL_INIT_REFFSSLOT | SL_INIT_SLOTSSLOT | SL_INIT_SSLOTCLK);
	io_write_32(MSTAT_REF_ARS, 0x00330000U);

	/* MSTAT SRAM setting */
	{
	uint32_t i;

	for (i = 0U; i < ARRAY_SIZE(mstat_fix); i++) {
		io_write_64(MSTAT_FIX_QOS_BANK0 + mstat_fix[i].addr,
				mstat_fix[i].value);
		io_write_64(MSTAT_FIX_QOS_BANK1 + mstat_fix[i].addr,
				mstat_fix[i].value);
	}
	for (i = 0U; i < ARRAY_SIZE(mstat_be); i++) {
		io_write_64(MSTAT_BE_QOS_BANK0 + mstat_be[i].addr,
				mstat_be[i].value);
		io_write_64(MSTAT_BE_QOS_BANK1 + mstat_be[i].addr,
				mstat_be[i].value);
	}
	}

	/* 3DG bus Leaf setting */
	io_write_32(0xFD820808U, 0x00001234U);
	io_write_32(0xFD820800U, 0x0000003FU);
	io_write_32(0xFD821800U, 0x0000003FU);
	io_write_32(0xFD822800U, 0x0000003FU);
	io_write_32(0xFD823800U, 0x0000003FU);
	io_write_32(0xFD824800U, 0x0000003FU);
	io_write_32(0xFD825800U, 0x0000003FU);
	io_write_32(0xFD826800U, 0x0000003FU);
	io_write_32(0xFD827800U, 0x0000003FU);

	/* Resource Alloc start */
	io_write_32(RALLOC_RAEN,  0x00000001U);

	/* MSTAT start */
	io_write_32(MSTAT_STATQC, 0x00000001U);
#else
	NOTICE("BL2: QoS is None\n");

	/* Resource Alloc setting */
	io_write_32(RALLOC_EC,    0x00080001U);	/* need for H3 v1.* */
#endif /* !(RCAR_QOS_TYPE == RCAR_QOS_NONE) */
}
