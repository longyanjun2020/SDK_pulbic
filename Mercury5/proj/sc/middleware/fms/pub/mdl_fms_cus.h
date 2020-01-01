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
* @file    mdl_fms_cus.h
* @version
* @brief
*
*/

#ifndef __MDL_FMS_CUS_H__
#define __MDL_FMS_CUS_H__

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
/* Opaque handle */
typedef struct
{
   u32 opaque[4];
} fms_AdHandle_t;

/* Opaque iterator */
typedef struct
{
   u32 opaque[4];
} fms_AdIterator_t;

/* Information structure */
typedef struct
{
   u32   identifier;       /* identifier */
   u32   size;             /* entry size */
   void  *data;            /* pointer to stored data */
   u32   remaining;        /* remaining writable space unless finalised */
   bool  finalised;        /* TRUE if entry is finalised */
} fms_AdInfo_t;

/****************************************************************************/
/* VOLUMES ENUMERATION                                                      */
/****************************************************************************/
typedef enum
{
   FMS_CUSTO_VOLUME,
   FMS_JAVASTORE_VOLUME,
   FMS_JAVAEXEC_VOLUME,
   FMS_DOTA_VOLUME,
   FMS_SOUND_VOLUME
} fms_AdToken_e;

typedef s32 (*callback_t)(u32 offset, u32 size, void *pParam);

typedef struct
{
    u32 __unaligned_buffer; //< private member. Used to remember the memory address without aligned

    u32 id; //< identification of this CUS
    u32 offset;
    u32 size;
    u8 *pData;
    u8 used;
} fms_CusHandle_t;

/**
 * Callback function type for fms_CusIterate
 * when a CUS is found. A CUS is passed to the callback function along with a pointer to parameter
 */

typedef s32 (*fms_CusCallback_t)(fms_CusHandle_t *handle, void *pParam);

/*=============================================================*/
// Variable definition
/*=============================================================*/

/*=============================================================*/
// Global function definition
/*=============================================================*/

/**
 * @brief Iterate through all of the CUS with `id'
 *
 * @param id       : the CUS id
 * @param callback : callback function to be invoked when such a CUS is found
 * @param pParam   : a void pointer that will be passed into callback function
 *
 * @retval         : < 0 failure code
 * @retval         : 0   OK
 */
s32 fms_CusIterate(u32 id, fms_CusCallback_t callback, void *pParam);

/****************************************************************************/
/*  Function: fms_AdFindInit                                                */
/*--------------------------------------------------------------------------*/
/*  Scope   : Starts a search on the given range of identifiers             */
/*            and initialises the iterator accordingly.                     */
/*                                                                          */
/*                                                                          */
/*  Return    : (s32) FMS_OK or error code                                  */
/*                                                                          */
/*  Interface :                                                             */
/*--------------------------------------------------------------------------*/
/*  Variable Name     |IN |OUT|GLB|  Use                                    */
/*--------------------+---+---+---+-----------------------------------------*/
/*  i__e_Token        | X |   |   |  Identification of the used volume      */
/*  i__u32_Min        | X |   |   |  Min value for wanted identifiers       */
/*  i__u32_Max        | X |   |   |  Max value                              */
/*  o__ps_Browse      |   | X |   |  Iterator to initialise                 */
/*--------------------+---+---+---+-----------------------------------------*/
/****************************************************************************/
s32 fms_AdFindInit(fms_AdToken_e i__e_Token, u32 i__u32_Min, u32 i__u32_Max, fms_AdIterator_t *o__ps_Browse);

/****************************************************************************/
/*  Function: fms_AdFindNext                                                */
/*--------------------------------------------------------------------------*/
/*  Scope   : Get the next record in a search using the iterator            */
/*            previously initialised by fms_AdFindInit.                     */
/*                                                                          */
/*  Return    : (s32) FMS_OK or error code                                  */
/*                                                                          */
/*  Interface :                                                             */
/*--------------------------------------------------------------------------*/
/*  Variable Name     |IN |OUT|GLB|  Use                                    */
/*--------------------+---+---+---+-----------------------------------------*/
/*  o__ps_Handle      |   | X |   |  Handle to set                          */
/*  io__ps_Browse     | X |   |   |  Iterator to use                        */
/*--------------------+---+---+---+-----------------------------------------*/
/****************************************************************************/
s32 fms_AdFindNext(fms_AdHandle_t *o__ps_Handle, fms_AdIterator_t *io__ps_Browse);

/****************************************************************************/
/*  Function: fms_AdInfo                                                    */
/*--------------------------------------------------------------------------*/
/*  Scope   : Gets information about a record.                              */
/*            The given handle must have been set by fms_AdFindNext         */
/*            or fms_AdAllocate                                             */
/*                                                                          */
/*  Return    :  (s32) FMS_OK or error code                                 */
/*                                                                          */
/*  Interface :                                                             */
/*--------------------------------------------------------------------------*/
/*  Variable Name     |IN |OUT|GLB|  Use                                    */
/*--------------------+---+---+---+-----------------------------------------*/
/*  i__ps_Handle      | X |   |   |  Handle to the record to query          */
/*  o__ps_Info        |   | X |   |  Information structure to fill          */
/*--------------------+---+---+---+-----------------------------------------*/
/****************************************************************************/
s32 fms_AdInfo(fms_AdHandle_t *i__ps_Handle, fms_AdInfo_t *o__ps_Info);

s32 fms_AdIterate(u32 id, callback_t callback, void *pParam);

s32 fms_AdIterateLow(u32 id, callback_t callback, void *pParam);

/****************************************************************************/
/*  Function: fms_AdLoadData                                                */
/*--------------------------------------------------------------------------*/
/*  Scope   : Load CUS data.                                                */
/*            The given handle must have been set by fms_AdFindNext         */
/*            or fms_AdAllocate                                             */
/*                                                                          */
/*  Return    :  (s32) FMS_OK or error code                                 */
/*                                                                          */
/*  Interface :                                                             */
/*--------------------------------------------------------------------------*/
/*  Variable Name     |IN |OUT|GLB|  Use                                    */
/*--------------------+---+---+---+-----------------------------------------*/
/*  offset            | X |   |   |  Offset of data                         */
/*  pBuf              | X |   |   |  Data buffer                            */
/*  length            | X |   |   |  Data length                            */
/*--------------------+---+---+---+-----------------------------------------*/
/****************************************************************************/
s32 fms_AdLoadData(u32 offset, u8 *pBuf, u32 length);

#endif //__MDL_FMS_CUS_H__

