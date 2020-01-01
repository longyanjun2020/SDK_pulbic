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
* @file    mdl_vm_bin.h
* @version
* @brief
*
*/

#ifndef __MDL_VM_BIN_H__
#define __MDL_VM_BIN_H__

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
typedef enum
{
   VM_FMS_BIN_GSMSTACK,
   VM_FMS_BIN_OPENAT,
   VM_FMS_BIN_XMODEM
} vm_binType_e;

/*=============================================================*/
// Variable definition
/*=============================================================*/

/*=============================================================*/
// Global function definition
/*=============================================================*/
/****************************************************************************/
/*  Function:  vm_binGetOrigin                                             */
/*--------------------------------------------------------------------------*/
/*  Scope   :  Returns the origin address in flash memory of the            */
/*             selected code.                                               */
/*                                                                          */
/*  Return    : (s32) Address or error code                                 */
/*                                                                          */
/*  Interface :                                                             */
/*--------------------------------------------------------------------------*/
/*  Variable Name     |IN |OUT|GLB|  Use                                    */
/*--------------------+---+---+---+-----------------------------------------*/
/*  i__e_Type         | X |   |   |  Selected binary                        */
/*--------------------+---+---+---+-----------------------------------------*/
/****************************************************************************/
s32 vm_binGetOrigin(vm_binType_e i__e_Type);


/****************************************************************************/
/*  Function:  vm_binGetSize                                               */
/*--------------------------------------------------------------------------*/
/*  Scope   :  Returns the size of the selected binary                      */
/*                                                                          */
/*  Return    : (s32) Address or error code                                 */
/*                                                                          */
/*  Interface :                                                             */
/*--------------------------------------------------------------------------*/
/*  Variable Name     |IN |OUT|GLB|  Use                                    */
/*--------------------+---+---+---+-----------------------------------------*/
/*  i__e_Type         | X |   |   |  Selected binary                        */
/*--------------------+---+---+---+-----------------------------------------*/
/****************************************************************************/
s32 vm_binGetSize(vm_binType_e i__e_Type);



/****************************************************************************/
/*  Function: vm_binDestroy                                                */
/*--------------------------------------------------------------------------*/
/*  Scope   : Destroy the selected binary                                   */
/*                                                                          */
/*  Return    : (s32) VM_FMS_OK or error code                                  */
/*                                                                          */
/*  Interface :                                                             */
/*--------------------------------------------------------------------------*/
/*  Variable Name     |IN |OUT|GLB|  Use                                    */
/*--------------------+---+---+---+-----------------------------------------*/
/*  i__e_Type         | X |   |   |  Selected binary                        */
/*--------------------+---+---+---+-----------------------------------------*/
/****************************************************************************/
s32 vm_binDestroy(vm_binType_e i__e_Type);

#endif //__MDL_VM_BIN_H__

