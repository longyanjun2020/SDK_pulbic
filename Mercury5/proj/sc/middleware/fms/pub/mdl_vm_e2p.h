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
* @file    mdl_vm_e2p.h
* @version
* @brief
*
*/

#ifndef __MDL_VM_E2P_H__
#define __MDL_VM_E2P_H__

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

/*=============================================================*/
// Variable definition
/*=============================================================*/

/*=============================================================*/
// Global function definition
/*=============================================================*/
/****************************************************************************/
/*  Function: opic_e2pTranslateAddress                                      */
/*--------------------------------------------------------------------------*/
/*  Scope   :  Translates the logical address of the supplied parameter     */
/*             into its address within the simulated eeprom                 */
/*                                                                          */
/*  Return    :  (s32) Parameter address or ERROR                           */
/*                                                                          */
/*  Interface :                                                             */
/*--------------------------------------------------------------------------*/
/*  Variable Name     |IN |OUT|GLB|  Use                                    */
/*--------------------+---+---+---+-----------------------------------------*/
/*  i__u32_Address    | X |   |   |  Address of the parameter to check      */
/*  i__u32_Size       | X |   |   |  Its size                               */
/*  i__s32_Operation  | X |   |   |  Operation to check                     */
/*--------------------+---+---+---+-----------------------------------------*/
/****************************************************************************/
s32 opic_e2pTranslateAddress(u32 i__u32_Address, u32 i__u32_Size, s32 i__s32_Operation);

/**
 *
 * \fn    const s32 vm_e2pRead(u32 E2pToReadAdress, u32 Size, void *pDest);
 * \brief Reads a parameter in the Open EEPROM.            
 *            The Open EEPROM is divided into 3 areas:                   
 *               (*) the stack area                                        
 *               (*) the lib area                                          
 *               (*) the applicative software dedicated area.             
 *            The function vm_e2pRead will retrieve data from one of        
 *            these areas, depending on the most significant byte of     
 *            the given virtual address (\ref VM_E2P_STACK_FOR_CUST_AREA,
 *            \ref VM_E2P_LIB_AREA, \ref VM_E2P_APPL_AREA).        
 *                                                                       
 * \param [in] E2pToReadAdress  Virtual address of the data to read
 * \param [in] Size  Size of the data to read (in bytes)
 * \param [out] pDest  Allocated buffer for reading data
 * \return <0 if error, >=0 otherwise
 */
s32 vm_e2pRead(u32 i__u32_Address, u32 i__u32_Size, void *o__p_Buffer);

/**
 *
 * \fn    const s32 vm_e2pReadMirror(u32 i__u32_ParamAddr, u32 i__u32_ParamSize, void* o__p_Buffer);
 * \brief Reads a parameter in the Mirror of Open EEPROM.            
 *            The Open EEPROM is divided into 3 areas:                   
 *               (*) the stack area                                        
 *               (*) the lib area                                          
 *               (*) the applicative software dedicated area.             
 *            The function fms_E2pReadMirror will retrieve data from one of        
 *            these areas, depending on the most significant byte of     
 *            the given virtual address (\ref VM_E2P_STACK_FOR_CUST_AREA,
 *            \ref VM_E2P_LIB_AREA, \ref VM_E2P_APPL_AREA).        
 *                                                                       
 * \param [in] i__u32_ParamAddr  Virtual address of the data to read
 * \param [in] i__u32_ParamSize  Size of the data to read (in bytes)
 * \param [out] o__p_Buffer  Allocated buffer for reading data
 * \return <0 if error, >=0 otherwise
 */
s32 vm_e2pReadMirror(u32 i__u32_ParamAddr, u32 i__u32_ParamSize, void* o__p_Buffer);

/**
 * \fn     const s32 vm_e2pWrite(u32 E2pToWriteAdress,  u32 Size, const void *pSrc);
 * \brief Writes the given parameter in the Open EEPROM
 * \param [in] E2pToWriteAdress  Virtual address of the data to read
 * \param [in] Size  Size of the data to write (in bytes)
 * \param [out] pSrc  Buffer contains data to write
 * \return <0 if error, >=0 otherwise
 */
s32 vm_e2pWrite(u32 i__u32_Address, u32 i__u32_Size, const void *i__p_Buffer);

/**
  * \fn		const s32 vm_e2pSaveOneParameter(u32 i__u32_Address, u32 i__u32_Size);
  * \brief	Save the given parameter in the WM mirror and in the Customer mirror
  * \param	[in] i__u32_Address  Virtual address of the parameter
  * \param	[in] i__u32_Size  Number of bytes to save
  * \return <0 if error, >=0 otherwise
  */
s32 vm_e2pSaveOneParameter(u32 i__u32_Address, u32 i__u32_Size);

/**
  * \fn		const s32 vm_e2pSetProtection(void);
  * \brief	Enables the EEPROM special parameters protection mechanism.
  *         Some parameters of the GSM stack are protected against
  *         any modification when the protection mechanism is active.
  * \return <0 if error, >=0 otherwise
  */
s32 vm_e2pSetProtection(void);

/**
  * \fn		const s32 vm_e2pUnsetProtection(void);
  * \brief	Disables the EEPROM special parameters protection mechanism.
  *         This is required to update some critical parameters.
  *         Do not use unless you know what you are doing!
  *         Do not forget to set back the protection once you've made your modifications.
  *         
  * \return <0 if error, >=0 otherwise
  */
s32 vm_e2pUnsetProtection(void);

#endif //__MDL_VM_E2P_H__

