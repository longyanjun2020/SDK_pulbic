#ifndef __VEN_DBG_H__
#define __VEN_DBG_H__
/**
 *
 * @file    ven_dbg.h
 * @brief   This file defines the os interface definition.
 *
 * @author  Ming.Chen
 * @version $Id: ven_dbg.h 38996 2009-09-01 02:03:20Z code.lin $
 *
 */

#include "ven_sdk.h"

#define VEN_DBG_GROUP_0  ((u32)0x1C) ///< Diagnose group 0 (cus5)
#define VEN_DBG_GROUP_1  ((u32)0x34) ///< Diagnose group 1 (cus12)

#define VEN_DBG_GROUP_SDK_1  ((u32)0x4C) ///< Diagnose group for SDK task 1
#define VEN_DBG_GROUP_SDK_2  ((u32)0x4D) ///< Diagnose group for SDK task 2
#define VEN_DBG_GROUP_SDK_3  ((u32)0x4E) ///< Diagnose group for SDK task 3
#define VEN_DBG_GROUP_SDK_4  ((u32)0x4F) ///< Diagnose group for SDK task 4
#define VEN_DBG_GROUP_SDK_5  ((u32)0x50) ///< Diagnose group for SDK task 5

#define VEN_DBG_LEVEL_0  ((u32) (0x00 << 8)) ///< Diagnose level 0
#define VEN_DBG_LEVEL_1  ((u32) (0x01 << 8)) ///< Diagnose level 1
#define VEN_DBG_LEVEL_2  ((u32) (0x02 << 8)) ///< Diagnose level 2
#define VEN_DBG_LEVEL_3  ((u32) (0x03 << 8)) ///< Diagnose level 3
#define VEN_DBG_LEVEL_4  ((u32) (0x04 << 8)) ///< Diagnose level 4
#define VEN_DBG_LEVEL_5  ((u32) (0x05 << 8)) ///< Diagnose level 5
#define VEN_DBG_LEVEL_6  ((u32) (0x06 << 8)) ///< Diagnose level 6
#define VEN_DBG_LEVEL_7  ((u32) (0x07 << 8)) ///< Diagnose level 7
#define VEN_DBG_LEVEL_8  ((u32) (0x08 << 8)) ///< Diagnose level 8
#define VEN_DBG_LEVEL_9  ((u32) (0x09 << 8)) ///< Diagnose level 9
#define VEN_DBG_LEVEL_10 ((u32) (0x0A << 8)) ///< Diagnose level 10
#define VEN_DBG_LEVEL_11 ((u32) (0x0B << 8)) ///< Diagnose level 11
#define VEN_DBG_LEVEL_12 ((u32) (0x0C << 8)) ///< Diagnose level 12
#define VEN_DBG_LEVEL_13 ((u32) (0x0D << 8)) ///< Diagnose level 13
#define VEN_DBG_LEVEL_14 ((u32) (0x0E << 8)) ///< Diagnose level 14
#define VEN_DBG_LEVEL_15 ((u32) (0x0F << 8)) ///< Diagnose level 15
#define VEN_DBG_LEVEL_16 ((u32) (0x10 << 8)) ///< Diagnose level 16
#define VEN_DBG_LEVEL_17 ((u32) (0x11 << 8)) ///< Diagnose level 17
#define VEN_DBG_LEVEL_18 ((u32) (0x12 << 8)) ///< Diagnose level 18
#define VEN_DBG_LEVEL_19 ((u32) (0x13 << 8)) ///< Diagnose level 19
#define VEN_DBG_LEVEL_20 ((u32) (0x14 << 8)) ///< Diagnose level 20
#define VEN_DBG_LEVEL_21 ((u32) (0x15 << 8)) ///< Diagnose level 21
#define VEN_DBG_LEVEL_22 ((u32) (0x16 << 8)) ///< Diagnose level 22
#define VEN_DBG_LEVEL_23 ((u32) (0x17 << 8)) ///< Diagnose level 23
#define VEN_DBG_LEVEL_24 ((u32) (0x18 << 8)) ///< Diagnose level 24
#define VEN_DBG_LEVEL_25 ((u32) (0x19 << 8)) ///< Diagnose level 25
#define VEN_DBG_LEVEL_26 ((u32) (0x1A << 8)) ///< Diagnose level 26
#define VEN_DBG_LEVEL_27 ((u32) (0x1B << 8)) ///< Diagnose level 27
#define VEN_DBG_LEVEL_28 ((u32) (0x1C << 8)) ///< Diagnose level 28
#define VEN_DBG_LEVEL_29 ((u32) (0x1D << 8)) ///< Diagnose level 29
#define VEN_DBG_LEVEL_30 ((u32) (0x1E << 8)) ///< Diagnose level 30
#define VEN_DBG_LEVEL_31 ((u32) (0x1F << 8)) ///< Diagnose level 31

/**
 *  ven_dbg_trace
 *  @brief    This function is aimed at trace managing, the result string will be visualised by TMT : Target Monitoring Tool application
 *
 *  @param  level     [in] Value of group and level.
 *                         ex. VEN_DBG_GROUP_0 | VEN_DBG_LEVEL_0
 *                             VEN_DBG_GROUP_SDK_1 | VEN_DBG_LEVEL_2
 *  @param  strFormat [in] Pointer to debug string
 *
 *  @retval 0
 *
 */
s8 ven_dbg_trace(u32 grpLevel, char *strFormat, ...);

/**
 *  ven_dbg_traceEx
 *  @brief    This function is aimed at trace managing, the result string will be visualised by TMT : Target Monitoring Tool application
 *
 *  @param  VenID     [in] Vendor ap ID.
 *                         ex. VEN_DEFAULT
 *  @param  level     [in] Debug level
 *                         ex. VEN_DBG_LEVEL_0
 *  @param  strFormat [in] Pointer to debug string
 *
 *  @retval 0
 *
 */
s8 ven_dbg_traceEx(ven_app_id_t VenID, u32 level, char *strFormat, ...);

#endif // __VEN_DBG_H__

