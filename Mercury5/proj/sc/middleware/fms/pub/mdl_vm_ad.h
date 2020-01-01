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
* @file    mdl_vm_ad.h
* @version
* @brief
*
*/

#ifndef __MDL_VM_AD_H__
#define __MDL_VM_AD_H__

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
  * \brief Opaque handle 
  */
typedef struct 
{
   u32 opaque[4];
} vm_adHandle_t;

/**
  * \brief Opaque iterator 
  */
typedef struct
{
   u32 opaque[4];
} vm_adIterator_t;

/**
  * \brief Information structure 
  */
typedef struct
{
   u32   identifier;       ///< identifier 
   u32   size;             ///< entry size 
   void  *data;            ///< pointer to stored data 
   u32   remaining;        ///< remaining writable space unless finalised 
   bool  finalised;        ///< TRUE if entry is finalised 
} vm_adInfo_t;

/**
  * \brief Volume state 
  */
typedef struct
{
   u32 freemem;         ///< avalilable space in bytes
   u32 deletedmem;      ///< deleted space
   u32 totalmem;        ///< total space of the volume
   u16 numobjects;      ///< number of cells
   u16 numdeleted;      ///< number of deleted cells
   bool need_recovery;  ///< if TRUE, the volume recompaction is not finished  
} vm_adStats_t;

/**
  * \brief Volume state 
  */
typedef enum
{
   VM_FMS_AD_ERROR,     ///< Error, volume does not exist 
   VM_FMS_AD_READY,     ///< Volume is usable 
   VM_FMS_AD_NOTAVAIL,  ///< Volume not available 
   VM_FMS_AD_REPAIR,    ///< Volume under compaction or needing compaction recovery 
   VM_FMS_AD_TO_FORMAT, ///< Volume needs to be formatted to be operational
   VM_FMS_AD_FORMATTED  ///< Volume undergoing a format operation
} vm_adState_e;

/** 
 * \brief Operation modes for wm_adFormat2 function
 */
typedef enum
{
   VM_FMS_AD_FORMAT_INIT,        ///< To initialise the format process
   VM_FMS_AD_FORMAT_CONTINUE,    ///< To actually run the format process
   VM_FMS_AD_FORMAT_ABORT        ///< To abort the format process
} vm_adFormatMode_e;

/** 
 * \brief list of available volumes
 */
typedef enum
{
   VM_FMS_CUSTO_VOLUME,
   VM_FMS_JAVASTORE_VOLUME,
   VM_FMS_JAVAEXEC_VOLUME,
   VM_FMS_DOTA_VOLUME,
   VM_FMS_SOUND_VOLUME
} vm_adToken_e;


/** 
 * \brief volume IOCTL control codes (to use with \ref vm_adVolumeIoControl)
 */
typedef enum
{
   VM_FMS_AD_DELETE_ALL_UNCOMPLETE,
   VM_FMS_AD_GET_FIRSTCELL_CONTENTSPTR
} vm_adVolumeCtrlCode_e;

/*=============================================================*/
// Variable definition
/*=============================================================*/

/*=============================================================*/
// Global function definition
/*=============================================================*/
s32 vm_adAllocate(vm_adToken_e i__e_Token, u32 i__u32_Ident, u32 i__u32_Size, vm_adHandle_t *o__ps_Handle);
s32 vm_adWrite(vm_adHandle_t *i__ps_Handle, u32 i__u32_Size, void *i__p_Buffer);
s32 vm_adResume(vm_adHandle_t *io__ps_Handle);
s32 vm_adFinalise(vm_adHandle_t *i__ps_Handle);
s32 vm_adRetrieve(vm_adToken_e i__e_Token, u32 i__u32_Ident, vm_adHandle_t *o__ps_Handle);
s32 vm_adFindInit(vm_adToken_e i__e_Token, u32 i__u32_Min, u32 i__u32_Max, vm_adIterator_t *o__ps_Browse);
s32 vm_adFindNext(vm_adHandle_t *o__ps_Handle, vm_adIterator_t *io__ps_Browse);
s32 vm_adInfo(vm_adHandle_t *i__ps_Handle, vm_adInfo_t *o__ps_Info);
s32 vm_adStats(vm_adToken_e i__e_Token, vm_adStats_t *o__ps_Stats);
s32 vm_adDelete(vm_adHandle_t *i__ps_Handle);
s32 vm_adFormat(vm_adToken_e i__e_Token);
s32 vm_adRecompactInit(vm_adToken_e i__e_Token);
s32 vm_adRecompact(vm_adToken_e i__e_Token);
vm_adState_e vm_adVolumeState(vm_adToken_e i__e_Token);
s32 vm_adVolumeIoControl( vm_adToken_e i__e_Token, 
                           vm_adVolumeCtrlCode_e i__e_ControlCode,
                           void *io__p_Buffer,
                           u32 i__u32_BufferSize);
s32 vm_adFormat2( vm_adToken_e        i__e_Token,
                  vm_adFormatMode_e   i__e_Mode, 
                  u32                *io__pu32_Handle,
                  u32                *o__pu32_Progress);

#endif //__MDL_VM_AD_H__

