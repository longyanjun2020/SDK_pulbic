////////////////////////////////////////////////////////////////////////////////
//
// Copyright (c) 2006-2009 MStar Semiconductor, Inc.
// All rights reserved.
//
// Unless otherwise stipulated in writing, any and all information contained
// herein regardless in any format shall remain the sole proprietary of
// MStar Semiconductor Inc. and be kept in strict confidence
// (¡§MStar Confidential Information¡¨) by the recipient.
// Any unauthorized act including without limitation unauthorized disclosure,
// copying, use, reproduction, sale, distribution, modification, disassembling,
// reverse engineering and compiling of the contents of MStar Confidential
// Information is unlawful and strictly prohibited. MStar hereby reserves the
// rights to any and all damages, losses, costs and expenses resulting therefrom.
//
////////////////////////////////////////////////////////////////////////////////

/**
* @file    mdl_cpu_pub.h
* @version
* @brief   cpu speed profile.
*
*/

#ifndef __MDL_CPU_PUB_H__
#define __MDL_CPU_PUB_H__



/*=============================================================*/
//  Includes Files
/*=============================================================*/
#include "vm_types.ht"

/*=============================================================*/
// Macro definition
/*=============================================================*/

/*=============================================================*/
// Data type definition
/*=============================================================*/

/**
 *  @brief The enumeration defines the CPU speed error code
 */
typedef enum{
  MDL_CPU_OK,            /**< Change cpu speed success */
  MDL_CPU_FAIL,          /**< Change cpu speed fail */
  MDL_CPU_REJECT,        /**< Change cpu speed reject (cpu speed is request by other user) */
} MdlCpuErrCode_e;

/**
 *  @brief The enumeration defines the requested CPU speed.
 */
typedef enum{
  MDL_CPU_SLOW,       /**< Slow CPU speed */
  MDL_CPU_MEDIUM,     /**< Medium CPU speed */
  MDL_CPU_FAST,       /**< Fast CPU speed */
  MDL_CPU_SUPFAST,    /**< Supper Fast CPU speed */
  MDL_CPU_LAST,       /**< The speed is supported, but not in speed profile */
  MDL_CPU_UNKNOWN,    /**< Cpu speed unknown */

  MDL_CPU_39MHZ    = 39000000,
  MDL_CPU_50MHZ    = 50000000,
  MDL_CPU_52MHZ    = 52000000,
  MDL_CPU_62P4MHZ  = 62400000,
  MDL_CPU_71P5MHZ  = 71500000,
  MDL_CPU_75MHZ    = 75000000,
  MDL_CPU_78MHZ    = 78000000,
  MDL_CPU_84P5MHZ  = 84500000,
  MDL_CPU_89P14MHZ = 89140000,
  MDL_CPU_91MHZ    = 91000000,
  MDL_CPU_100MHZ   = 100000000,
  MDL_CPU_104MHZ   = 104000000,
  MDL_CPU_117MHZ   = 117000000,
  MDL_CPU_130MHZ   = 130000000,
  MDL_CPU_143MHZ   = 143000000,
  MDL_CPU_150MHZ   = 150000000,
  MDL_CPU_156MHZ   = 156000000,
  MDL_CPU_169MHZ   = 169000000,
  MDL_CPU_182MHZ   = 182000000,
  MDL_CPU_200MHZ   = 200000000,
  MDL_CPU_208MHZ   = 208000000,
  MDL_CPU_234MHZ   = 234000000,
  MDL_CPU_247MHZ   = 247000000,
  MDL_CPU_250MHZ   = 250000000,
  MDL_CPU_260MHZ   = 260000000,
  MDL_CPU_286MHZ   = 286000000,
  MDL_CPU_299MHZ   = 299000000,
  MDL_CPU_300MHZ   = 300000000,
  MDL_CPU_312MHZ   = 312000000,
  MDL_CPU_338MHZ   = 338000000,
  MDL_CPU_350MHZ   = 350000000,
  MDL_CPU_364MHZ   = 364000000,
  MDL_CPU_400MHZ   = 400000000,
  MDL_CPU_416MHZ   = 416000000
} MdlCpuSpeed_e;

/**
 *  @brief The enumeration defines the CPU speed request client
 */
#define CLIENT_OFFSET 0x0000
#define SUBCLIENT_OFFSET 0x0001

/*
 *  @internally use as shift indicator
 */
typedef enum {
  CPU_CLIENT_MMI = 0,
  CPU_CLIENT_MMP,
  CPU_CLIENT_GPD,
  CPU_CLIENT_IMGDECODE,
  CPU_CLIENT_FS,
  CPU_CLIENT_SDK,
  CPU_CLIENT_BT,
  CPU_CLIENT_RAI_ACCESS,
  CPU_CLIENT_DSR,
  CPU_CLIENT_MMIEXT,
  CPU_CLIENT_MM_VDO_PLAYER,
  CPU_CLIENT_MM_VDO_REOCRDER,
  CPU_CLIENT_MM_AUD_PLAYER,
  CPU_CLIENT_MM_AUD_RECORDER,
  CPU_CLIENT_MM_PREVIEWE,
  CPU_CLIENT_MM_IMG_CAPTURE,
  CPU_CLIENT_MM_HW_JPD,
  CPU_CLIENT_MM_USB,
  CPU_CLIENT_MM_NES,
  CPU_CLIENT_WIFI,
  CPU_CLIENT_FILE_MGR,
  CPU_CLIENT_FM,
  CPU_CLIENT_DALVIK,
  CPU_CLIENT_MM_AEC_PROC,

  CPU_CLIENT_MSRV,
  CPU_CLIENT_MTMO,
  CPU_CLIENT_WAP,
  CPU_CLIENT_SUPPLICANT,
  CPU_CLIENT_GSS,
  CPU_CLIENT_GPS,
  CPU_CLIENT_CTP,  /* __TOUCH_SCREEN_C_DRV__ || __TOUCH_SCREEN_R_C_COEXIST_DRV__ */
  CPU_CLIENT_DRM,
  CPU_CLIENT_GPS_MDL,

  CPU_CLIENT_MAX
} CpuClientIdx_e;
/*
 *  @used by driver/service equals to (shift indicator * 2)
 *   need to add both when add a client
 */
typedef enum {
  MDL_CPU_MMI             = (CPU_CLIENT_MMI << 1)       		    + CLIENT_OFFSET,    //  0 (00000000 00000000 00000001)
  MDL_CPU_MMI_ON          = (CPU_CLIENT_MMI << 1)               + SUBCLIENT_OFFSET, //  1 (00000000 00000000 00000002)
  MDL_CPU_MMP             = (CPU_CLIENT_MMP << 1)       		    + CLIENT_OFFSET,    //  2 (00000000 00000000 00000004)
  MDL_CPU_GPD             = (CPU_CLIENT_GPD << 1)				+ CLIENT_OFFSET,    //  4 (00000000 00000000 00000010)
  MDL_CPU_IMGDECODE       = (CPU_CLIENT_IMGDECODE << 1)			+ CLIENT_OFFSET,    //  6 (00000000 00000000 00000040)
  MDL_CPU_VFS             = (CPU_CLIENT_FS << 1) 				+ CLIENT_OFFSET,    //  8 (00000000 00000000 00000100)
  MDL_CPU_EFAT            = (CPU_CLIENT_FS << 1) 				+ SUBCLIENT_OFFSET, //  9 (00000000 00000000 00000200)
  MDL_CPU_SDK             = (CPU_CLIENT_SDK << 1) 				+ CLIENT_OFFSET,    // 10 (00000000 00000000 00000400)
  MDL_CPU_BT              = (CPU_CLIENT_BT << 1) 				+ CLIENT_OFFSET,    // 12 (00000000 00000000 00001000)
  MDL_CPU_BT_MAC          = (CPU_CLIENT_BT << 1) 				+ SUBCLIENT_OFFSET, // 13 (00000000 00000000 00002000)
  MDL_CPU_RAI_ACCESS      = (CPU_CLIENT_RAI_ACCESS << 1) 		+ CLIENT_OFFSET,    // 14 (00000000 00000000 00004000)
  MDL_CPU_DSR             = (CPU_CLIENT_DSR << 1) 				+ CLIENT_OFFSET,    // 16 (00000000 00000000 00010000)
  MDL_CPU_MMIEXT          = (CPU_CLIENT_MMIEXT << 1) 			+ CLIENT_OFFSET,    // 18 (00000000 00000000 00040000)
  MDL_CPU_MM_VDO_PLAYER   = (CPU_CLIENT_MM_VDO_PLAYER << 1) 	    + CLIENT_OFFSET,    // 20 (00000000 00000000 00100000)
  MDL_CPU_MM_VDO_REOCRDER = (CPU_CLIENT_MM_VDO_REOCRDER << 1) 	+ CLIENT_OFFSET,    // 22 (00000000 00000000 00400000)
  MDL_CPU_MM_AUD_PLAYER   = (CPU_CLIENT_MM_AUD_PLAYER << 1) 	    + CLIENT_OFFSET,    // 24 (00000000 00000000 01000000)
  MDL_CPU_MM_AUD_RECORDER = (CPU_CLIENT_MM_AUD_RECORDER << 1) 	+ CLIENT_OFFSET,    // 26 (00000000 00000000 04000000)
  MDL_CPU_MM_PREVIEWE     = (CPU_CLIENT_MM_PREVIEWE << 1) 		+ CLIENT_OFFSET,    // 28 (00000000 00000000 10000000)
  MDL_CPU_MM_IMG_CAPTURE  = (CPU_CLIENT_MM_IMG_CAPTURE << 1) 	+ CLIENT_OFFSET,    // 30 (00000000 00000000 40000000)
  MDL_CPU_MM_HW_JPD       = (CPU_CLIENT_MM_HW_JPD << 1) 		    + CLIENT_OFFSET,    // 32 (00000000 00000001 00000000)
  MDL_CPU_MM_USB          = (CPU_CLIENT_MM_USB << 1) 			+ CLIENT_OFFSET,    // 34 (00000000 00000004 00000000)
  MDL_CPU_MM_NES          = (CPU_CLIENT_MM_NES << 1) 			+ CLIENT_OFFSET,    // 36 (00000000 00000010 00000000)
  MDL_CPU_WIFI            = (CPU_CLIENT_WIFI << 1) 				+ CLIENT_OFFSET,    // 38 (00000000 00000040 00000000)
  MDL_CPU_FILE_MGR        = (CPU_CLIENT_FILE_MGR << 1) 			+ CLIENT_OFFSET,    // 40 (00000000 00000100 00000000)
  MDL_CPU_FM              = (CPU_CLIENT_FM << 1) 				+ CLIENT_OFFSET,    // 42 (00000000 00000400 00000000)
  MDL_CPU_DALVIK          = (CPU_CLIENT_DALVIK << 1) 			+ CLIENT_OFFSET,    // 44 (00000000 00001000 00000000)
  MDL_CPU_MM_AEC_PROC          = (CPU_CLIENT_MM_AEC_PROC << 1) 	+ CLIENT_OFFSET,    // 46 (00000000 00004000 00000000)
  MDL_CPU_MSRV            = (CPU_CLIENT_MSRV << 1) 				+ CLIENT_OFFSET,    // 48 (00000000 00010000 00000000)
  MDL_CPU_MTMO            = (CPU_CLIENT_MTMO << 1) 				+ CLIENT_OFFSET,    // 50 (00000000 00040000 00000000)
  MDL_CPU_WAP             = (CPU_CLIENT_WAP << 1) 				+ CLIENT_OFFSET,    // 52 (00000000 00100000 00000000)
  MDL_CPU_SUPPLICANT      = (CPU_CLIENT_SUPPLICANT << 1) 		+ CLIENT_OFFSET,    // 54 (00000000 00400000 00000000)
  MDL_CPU_GSS             = (CPU_CLIENT_GSS << 1) 				+ CLIENT_OFFSET,    // 56 (00000000 01000000 00000000)
  MDL_CPU_GPS             = (CPU_CLIENT_GPS << 1) 				+ CLIENT_OFFSET,    // 58 (00000000 04000000 00000000)
  MDL_CPU_CTP             = (CPU_CLIENT_CTP << 1)               + CLIENT_OFFSET,    // 60 (00000000 10000000 00000000)
  MDL_CPU_DRM             = (CPU_CLIENT_DRM << 1) 				+ CLIENT_OFFSET,    // 62 (00000000 40000000 00000000)
  MDL_CPU_GPS_MDL         = (CPU_CLIENT_GPS_MDL << 1) 		    + CLIENT_OFFSET,    // 64 (00000001 00000000 00000000)
  MDL_CPU_MAX             = (CPU_CLIENT_MAX << 1) 				+ CLIENT_OFFSET,
} MdlCpuClient_e;

typedef struct{
    u32 *pData;
    u8 Size;
} MdlCpuReportData_t;
/*=============================================================*/
// Variable definition
/*=============================================================*/

/*=============================================================*/
//  Local function definition
/*=============================================================*/

/*=============================================================*/
// Global Function definition
/*=============================================================*/

/**
 * @brief Force speed in Auto cpu speed.
 *
 * @param eClient    : Request function.
 * @param isForce    : Force speed or release. TRUE: Force, FALSE: Release.
 *
 * @return MDL_CPU_OK      : Force cpu speed success.
 * @return MDL_CPU_FAIL    : Force cpu speed fail.
 * @return MDL_CPU_REJECT  : Force cpu speed reject.
 */
MdlCpuErrCode_e MdlCpuAutoSpeedForce(MdlCpuClient_e eClient, bool isForce);

/**
 * @brief Request the CPU speed.
 *
 * @param eClient    : Request function.
 * @param speed      : Request CPU speed.
 *
 * @return MDL_CPU_OK      : Change cpu speed success.
 * @return MDL_CPU_FAIL    : Change cpu speed fail.
 * @return MDL_CPU_REJECT  : Change cpu speed reject (cpu speed is request by other user).
 */
MdlCpuErrCode_e MdlCpuRequestSpeed(MdlCpuClient_e eClient, MdlCpuSpeed_e eSpeed);

/**
 * @brief Request the CPU speed.
 *
 * @param         eClinet    : Request function.
 * @param         speed      : Request CPU speed.
 *
 * @return MDL_CPU_OK      : Get cpu speed success.
 * @return MDL_CPU_FAIL    : Get cpu speed fail.
 * @return MDL_CPU_UNKNOWN : Unknown cpu speed
 */
MdlCpuErrCode_e MdlCpuQuerySpeed(MdlCpuSpeed_e *epSpeed);

/**
 * @brief Update report table.
 *
 * @return MDL_CPU_OK      : Get cpu speed success.
 * @return MDL_CPU_FAIL    : Get cpu speed fail.
 * @return MDL_CPU_UNKNOWN : Unknown cpu speed
 */
MdlCpuErrCode_e MdlCpuUpdateReportTbl(void);

/**
 * @brief Get report table
 *
 * @param         pTble    : Report table
 * @param         pCnt     : Table size;
 *
 * @return MDL_CPU_OK      : Get cpu speed success.
 * @return MDL_CPU_FAIL    : Get cpu speed fail.
 * @return MDL_CPU_UNKNOWN : Unknown cpu speed
 */
MdlCpuErrCode_e MdlCpuGetReportTbl(u32 **pTbl, u32 *pCnt);

#endif /* __MDL_CPU_PUB_H__ */

