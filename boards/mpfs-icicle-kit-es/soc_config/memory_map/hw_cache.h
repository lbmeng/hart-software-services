/*******************************************************************************
 * Copyright 2019-2020 Microchip FPGA Embedded Systems Solutions.
 * 
 * SPDX-License-Identifier: MIT
 * 
 * @file hw_cache.h
 * @author Microchip-FPGA Embedded Systems Solutions
 * 
 * Generated using Libero version: 1.0
 * Libero design name: ICICLE_MSS
 * MPFS part number used in design: MPFS250T_ES
 * Date generated by Libero: 11-16-2020_19:07:30
 * Format version of XML description: 0.3.8
 * PolarFire SoC Configuration Generator version: 0.4.1
 * 
 * Note 1: This file should not be edited. If you need to modify a parameter,
 * without going through the Libero flow or editing the associated xml file,
 * the following method is recommended:
 *   1. edit the file platform//config//software//mpfs_hal//mss_sw_config.h
 *   2. define the value you want to override there. (Note: There is a 
 *      commented example in mss_sw_config.h)
 * Note 2: The definition in mss_sw_config.h takes precedence, as 
 * mss_sw_config.h is included prior to the hw_cache.h in the hal 
 * (see platform//mpfs_hal//mss_hal.h)
 *
 */ 

#ifndef HW_CACHE_H_
#define HW_CACHE_H_


#ifdef __cplusplus
extern  "C" {
#endif

#if !defined (LIBERO_SETTING_WAY_ENABLE)
/*Way indexes less than or equal to this register value may be used by the 
cache */ 
#define LIBERO_SETTING_WAY_ENABLE    0x00000007UL
    /* WAY_ENABLE                        [0:8]   RW value= 0x7 */ 
#endif
#if !defined (LIBERO_SETTING_WAY_MASK_M0)
/*Way mask register master 0 (hart0) */ 
#define LIBERO_SETTING_WAY_MASK_M0    0x00000000UL
    /* WAY_MASK_0                        [0:1]   RW value= 0x0 */ 
    /* WAY_MASK_1                        [1:1]   RW value= 0x0 */ 
    /* WAY_MASK_2                        [2:1]   RW value= 0x0 */ 
    /* WAY_MASK_3                        [3:1]   RW value= 0x0 */ 
    /* WAY_MASK_4                        [4:1]   RW value= 0x0 */ 
    /* WAY_MASK_5                        [5:1]   RW value= 0x0 */ 
    /* WAY_MASK_6                        [6:1]   RW value= 0x0 */ 
    /* WAY_MASK_7                        [7:1]   RW value= 0x0 */ 
    /* WAY_MASK_8                        [8:1]   RW value= 0x0 */ 
    /* WAY_MASK_9                        [9:1]   RW value= 0x0 */ 
    /* WAY_MASK_10                       [10:1]  RW value= 0x0 */ 
    /* WAY_MASK_11                       [11:1]  RW value= 0x0 */ 
    /* WAY_MASK_12                       [12:1]  RW value= 0x0 */ 
    /* WAY_MASK_13                       [13:1]  RW value= 0x0 */ 
    /* WAY_MASK_14                       [14:1]  RW value= 0x0 */ 
    /* WAY_MASK_15                       [15:1]  RW value= 0x0 */ 
#endif
#if !defined (LIBERO_SETTING_WAY_MASK_M1)
/*Way mask register master 1 (hart1) */ 
#define LIBERO_SETTING_WAY_MASK_M1    0x00000000UL
    /* WAY_MASK_0                        [0:1]   RW value= 0x0 */ 
    /* WAY_MASK_1                        [1:1]   RW value= 0x0 */ 
    /* WAY_MASK_2                        [2:1]   RW value= 0x0 */ 
    /* WAY_MASK_3                        [3:1]   RW value= 0x0 */ 
    /* WAY_MASK_4                        [4:1]   RW value= 0x0 */ 
    /* WAY_MASK_5                        [5:1]   RW value= 0x0 */ 
    /* WAY_MASK_6                        [6:1]   RW value= 0x0 */ 
    /* WAY_MASK_7                        [7:1]   RW value= 0x0 */ 
    /* WAY_MASK_8                        [8:1]   RW value= 0x0 */ 
    /* WAY_MASK_9                        [9:1]   RW value= 0x0 */ 
    /* WAY_MASK_10                       [10:1]  RW value= 0x0 */ 
    /* WAY_MASK_11                       [11:1]  RW value= 0x0 */ 
    /* WAY_MASK_12                       [12:1]  RW value= 0x0 */ 
    /* WAY_MASK_13                       [13:1]  RW value= 0x0 */ 
    /* WAY_MASK_14                       [14:1]  RW value= 0x0 */ 
    /* WAY_MASK_15                       [15:1]  RW value= 0x0 */ 
#endif
#if !defined (LIBERO_SETTING_WAY_MASK_M2)
/*Way mask register master 2 (hart2) */ 
#define LIBERO_SETTING_WAY_MASK_M2    0x00000000UL
    /* WAY_MASK_0                        [0:1]   RW value= 0x0 */ 
    /* WAY_MASK_1                        [1:1]   RW value= 0x0 */ 
    /* WAY_MASK_2                        [2:1]   RW value= 0x0 */ 
    /* WAY_MASK_3                        [3:1]   RW value= 0x0 */ 
    /* WAY_MASK_4                        [4:1]   RW value= 0x0 */ 
    /* WAY_MASK_5                        [5:1]   RW value= 0x0 */ 
    /* WAY_MASK_6                        [6:1]   RW value= 0x0 */ 
    /* WAY_MASK_7                        [7:1]   RW value= 0x0 */ 
    /* WAY_MASK_8                        [8:1]   RW value= 0x0 */ 
    /* WAY_MASK_9                        [9:1]   RW value= 0x0 */ 
    /* WAY_MASK_10                       [10:1]  RW value= 0x0 */ 
    /* WAY_MASK_11                       [11:1]  RW value= 0x0 */ 
    /* WAY_MASK_12                       [12:1]  RW value= 0x0 */ 
    /* WAY_MASK_13                       [13:1]  RW value= 0x0 */ 
    /* WAY_MASK_14                       [14:1]  RW value= 0x0 */ 
    /* WAY_MASK_15                       [15:1]  RW value= 0x0 */ 
#endif
#if !defined (LIBERO_SETTING_WAY_MASK_M3)
/*Way mask register master 3 (hart3) */ 
#define LIBERO_SETTING_WAY_MASK_M3    0x00000000UL
    /* WAY_MASK_0                        [0:1]   RW value= 0x0 */ 
    /* WAY_MASK_1                        [1:1]   RW value= 0x0 */ 
    /* WAY_MASK_2                        [2:1]   RW value= 0x0 */ 
    /* WAY_MASK_3                        [3:1]   RW value= 0x0 */ 
    /* WAY_MASK_4                        [4:1]   RW value= 0x0 */ 
    /* WAY_MASK_5                        [5:1]   RW value= 0x0 */ 
    /* WAY_MASK_6                        [6:1]   RW value= 0x0 */ 
    /* WAY_MASK_7                        [7:1]   RW value= 0x0 */ 
    /* WAY_MASK_8                        [8:1]   RW value= 0x0 */ 
    /* WAY_MASK_9                        [9:1]   RW value= 0x0 */ 
    /* WAY_MASK_10                       [10:1]  RW value= 0x0 */ 
    /* WAY_MASK_11                       [11:1]  RW value= 0x0 */ 
    /* WAY_MASK_12                       [12:1]  RW value= 0x0 */ 
    /* WAY_MASK_13                       [13:1]  RW value= 0x0 */ 
    /* WAY_MASK_14                       [14:1]  RW value= 0x0 */ 
    /* WAY_MASK_15                       [15:1]  RW value= 0x0 */ 
#endif
#if !defined (LIBERO_SETTING_WAY_MASK_M4)
/*Way mask register master 4 (hart4) */ 
#define LIBERO_SETTING_WAY_MASK_M4    0x00000000UL
    /* WAY_MASK_0                        [0:1]   RW value= 0x0 */ 
    /* WAY_MASK_1                        [1:1]   RW value= 0x0 */ 
    /* WAY_MASK_2                        [2:1]   RW value= 0x0 */ 
    /* WAY_MASK_3                        [3:1]   RW value= 0x0 */ 
    /* WAY_MASK_4                        [4:1]   RW value= 0x0 */ 
    /* WAY_MASK_5                        [5:1]   RW value= 0x0 */ 
    /* WAY_MASK_6                        [6:1]   RW value= 0x0 */ 
    /* WAY_MASK_7                        [7:1]   RW value= 0x0 */ 
    /* WAY_MASK_8                        [8:1]   RW value= 0x0 */ 
    /* WAY_MASK_9                        [9:1]   RW value= 0x0 */ 
    /* WAY_MASK_10                       [10:1]  RW value= 0x0 */ 
    /* WAY_MASK_11                       [11:1]  RW value= 0x0 */ 
    /* WAY_MASK_12                       [12:1]  RW value= 0x0 */ 
    /* WAY_MASK_13                       [13:1]  RW value= 0x0 */ 
    /* WAY_MASK_14                       [14:1]  RW value= 0x0 */ 
    /* WAY_MASK_15                       [15:1]  RW value= 0x0 */ 
#endif

#ifdef __cplusplus
}
#endif


#endif /* #ifdef HW_CACHE_H_ */

