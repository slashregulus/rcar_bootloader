#pragma once
#include <stdint.h>

#ifndef	__DDR_INIT_E3_
#define	__DDR_INIT_E3_

#define RCAR_E3_DDR_VERSION    "rev.0.06"

#ifdef ddr_qos_init_setting
   #define REFRESH_RATE  3900               // Average periodic refresh interval[ns]. Support 3900,7800
#else
   #if RCAR_REF_INT == 0
      #define REFRESH_RATE  3900
   #elif RCAR_REF_INT == 1
      #define REFRESH_RATE  7800
   #else
      #define REFRESH_RATE  3900
   #endif
#endif

#ifdef ddr_qos_init_setting
extern uint32_t init_ddr_e31866(void);
extern uint32_t init_ddr_e31600(void);
//#define INITDRAM_OK (0)
#define INITDRAM_OK (1)
//#define INITDRAM_NG (0xffffffff)
#define INITDRAM_NG (0)
#define INITDRAM_ERR_I (0xffffffff)
#else
extern int32_t InitDram(void);
#define INITDRAM_OK (0)
#define INITDRAM_NG (0xffffffff)
#define INITDRAM_ERR_I (0xffffffff)
#define INITDRAM_ERR_O (0xfffffffe)
#define INITDRAM_ERR_T (0xfffffff0)
#endif

#endif /* __DDR_INIT_E3_ */
