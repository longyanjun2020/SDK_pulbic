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
* @file    mdl_vm_rai.h
* @version
* @brief
*
*/

#ifndef __MDL_VM_RAI_ID_H__
#define __MDL_VM_RAI_ID_H__

/*=============================================================*/
// Include files
/*=============================================================*/

/*=============================================================*/
// Extern definition
/*=============================================================*/

/*=============================================================*/
// Macro definition
/*=============================================================*/

/*=============================================================*/
// Data type definition
/*=============================================================*/

/**
  * \brief	global RAI id definition
  *
  */
/* MAE */
#define MAE_FS_RAI_START_ID 					0x01000000
#define MAE_FS_RAI_END_ID 						0x01FFFFFF
/* MMI */
#define MMI_FS_RAI_START_ID 					0x02000000
#define MMI_FS_RAI_END_ID 						0x02FFFFFF
/* VEN */
#define VEN_FS_RAI_START_ID						0x03000000
#define VEN_FS_RAI_END_ID							0x03FFFFFF
/* DRM KEY */
#define DRM_KEY_RAI_START_ID						0x04000000
#define DRM_KEY_RAI_END_ID							0x04FFFFFF
#define DRM_KEY_RAI_SIZE                            (100)
/* System DPM */
#define SYS_DPM_RAI_START_ID            0x05000000
#define SYS_DPM_RAI_END_ID              0x05FFFFFF
/* VML */
#define VML_VM_RAI_START_ID						0x10000000 /* Please do not change, need to sync to vm_vml_obj.h */
#define VML_VM_PLMN_RAI_START_ID			0x1FFF0000 /* Please do not change, need to sync to vm_vml_obj.h */
#define VML_VM_RAI_END_ID							0x1FFFFFFF /* Please do not change, need to sync to vm_vml_obj.h */


/* TV Driver */
#define DRV_TV_RAI_START_ID           0x20000000
#define DRV_TV_RAI_ATV_START_ID       0x20000000
#define DRV_TV_RAI_ATV_END_ID         0x20FFFFFF
#define DRV_TV_RAI_DTV_START_ID       0x21000000
#define DRV_TV_RAI_DTV_END_ID         0x21FFFFFF
#define DRV_TV_RAI_END_ID             0x21FFFFFF

/* NOR FAT */
#define FAT_OBJECT_RAI_START_ID				0xCAA00000 /* visul fs partiton */
#define FAT_OBJECT_RAI_START_ID2      		0xCAB00000 /* hidden fs partition */
/* VML */
#define VML_INFOS_RAI_START_ID 				0xFFFD0000 /* Please do not change, need to sync to mmt_afo.c */
#define VML_INFOS_RAI_END_ID 					0xFFFDFFFF
#define VML_SORTS_RAI_START_ID 				0xFFFE0000 /* Please do not change, need to sync to mmt_afo.c */
#define VML_SORTS_RAI_END_ID 					0xFFFEFFFF
#define VML_UNKNOWN_RAI_START_ID 			0xFFFF0000 /* Please do not change, need to sync to mmt_afo.c */
#define VML_UNKNOWN_RAI_END_ID 				0xFFFFFFFF

/*=============================================================*/
// Variable definition
/*=============================================================*/

/*=============================================================*/
// Global function definition
/*=============================================================*/

#endif //__MDL_VM_RAI_ID_H__

