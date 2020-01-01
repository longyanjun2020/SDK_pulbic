////////////////////////////////////////////////////////////////////////////////
//
// Copyright (c) 2006-2011 MStar Semiconductor, Inc.
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
* @file    mdl_fms_types.h
* @version
* @brief
*
*/

#ifndef __MDL_FMS_TYPES_H__
#define __MDL_FMS_TYPES_H__

/*=============================================================*/
// Include files
/*=============================================================*/

/*=============================================================*/
// Extern definition
/*=============================================================*/

/*=============================================================*/
// Macro definition
/*=============================================================*/

/* Error codes */

#define FMS_OK             0
#define FMS_DELAYED        0x1   /* Returned by fms_XXX_Erase when erasure is suspended */
#define FMS_RETRY          0x2   /* Returned by fms_XXX_Erase when erasure needs retry */


#define FMS_BAD            0xFFFFFFFF
#define FMS_UNDEFINED      0xFFFFFFFF

#define FMS_BAD_ARGS       0xFFFFFFFE
#define FMS_BAD_FUNCTION   0xFFFFFFFD
#define FMS_FORBIDDEN      0xFFFFFFFC
#define FMS_HW_ERROR       0xFFFFFFFB
#define FMS_SEQUENCE_ERROR 0xFFFFFFFA
#define FMS_OVERFLOW       0xFFFFFFF9
#define FMS_CMD_FAILED     0xFFFFFFF8
#define FMS_TIMEOUT        0xFFFFFFF7
#define FMS_REACHED_END    0xFFFFFFF6
#define FMS_NOT_AVAILABLE  0xFFFFFFF5
#define FMS_DAMAGED        0xFFFFFFF4
#define FMS_CLEANING_REQD  0xFFFFFFF3
#define FMS_CMD_FAILED2    0xFFFFFFF2
#define FMS_NO_CHANGE      0xFFFFFFF1 // no change when trying to change an eeprom parameter
#define FMS_REACHED_GROUP_END    0xFFFFFFF0  /* No more elements to enumerate in current group */

/*=============================================================*/
// Data type definition
/*=============================================================*/

/*=============================================================*/
// Variable definition
/*=============================================================*/

/*=============================================================*/
// Global function definition
/*=============================================================*/

#endif //__MDL_FMS_TYPES_H__
