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
* @file    mdl_fms.h
* @version
* @brief
*
*/

#ifndef __MDL_FMS_H__
#define __MDL_FMS_H__

/*=============================================================*/
// Include files
/*=============================================================*/

/*=============================================================*/
// Extern definition
/*=============================================================*/
//MST_CR_7899: prvent fetch data from flash during erasure
extern u32 *pnQbCntAddr;
//MST_CR_7899: prvent fetch data from flash during erasure
//#define FMS_WRITE_DEBUG

#ifdef FMS_WRITE_DEBUG
extern u32 testpath1;
extern u32 loopcount1;
#endif

/*=============================================================*/
// Macro definition
/*=============================================================*/

/*=============================================================*/
// Data type definition
/*=============================================================*/

/*=============================================================*/
// Variable definition
/*=============================================================*/

/*=============================================================*/
// Global function definition
/*=============================================================*/
/****************************************************************************/
/*  Function: fms_CoreAllowErasure                                          */
/*--------------------------------------------------------------------------*/
/*  Scope   : Counter-part of fms_CoreDenyErasure                           */
/*            Allows erase cycles again.                                    */
/*                                                                          */
/*  Return    : (void)                                                      */
/*                                                                          */
/*  Interface : n/a                                                         */
/****************************************************************************/
void fms_CoreAllowErasure(void);

/****************************************************************************/
/*  Function: fms_CoreDenyErasure                                           */
/*--------------------------------------------------------------------------*/
/*  Scope   : Used by the Hardware Layer's high priority interrupt handlers */
/*            to skip an erasure resume/suspend cycle, in order to service  */
/*            faster an incoming interrupt                                  */
/*  Return    : (void)                                                      */
/*                                                                          */
/*  Interface :  n/a                                                        */
/****************************************************************************/
void fms_CoreDenyErasure(void);

/****************************************************************************/
/*  Function: fms_ShutdownNandFlash                                         */
/*--------------------------------------------------------------------------*/
/*  Scope   : Shutdown NAND Flash                                           */
/*                                                                          */
/*  Return  : FMS error code                                                */
/*                                                                          */
/*--------------------------------------------------------------------------*/
/*  Variable Name     |IN |OUT|GLB|  Use                                    */
/*--------------------+---+---+---+-----------------------------------------*/
/****************************************************************************/
s32 fms_ShutdownNandFlash(void);

/****************************************************************************/
/*  Function: fms_Cleaner                                                   */
/*--------------------------------------------------------------------------*/
/*  Scope   : Invokes the cleaning routines of the services                 */
/*                                                                          */
/*  Return    : n/a                                                         */
/*                                                                          */
/*  Interface : n/a                                                         */
/****************************************************************************/
void fms_Cleaner(void);

/****************************************************************************/
/*  Function: fms_ServicesInit                                              */
/*--------------------------------------------------------------------------*/
/*  Scope   : Starts all the services                                       */
/*                                                                          */
/*                                                                          */
/*  Return    : void                                                        */
/*                                                                          */
/*  Interface : n/a                                                         */
/****************************************************************************/
void fms_ServicesInit(void);


#endif //__MDL_FMS_H__

