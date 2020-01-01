/*  $Workfile::   fms_core_detect.h                                       $ */
/*--------------------------------------------------------------------------*/
/*  Scope   :  Flash Memory Services - Common core routines                 */
/*                 Hardware detection and descriptor initialisation         */
/*                                                                          */
/****************************************************************************/



#ifndef _6ce936a45cce05dcef3474f8dfc0307e_INCLUDED_FMS_CORE_DETECT_H
#define _6ce936a45cce05dcef3474f8dfc0307e_INCLUDED_FMS_CORE_DETECT_H

#include "drv_flash_lowl_ho_pub.h"
/****************************************************************************/
/* FUNCTIONS EXPORTED WITHIN FMS CORE                                       */
/****************************************************************************/

/****************************************************************************/
/*  Function: fms_CoreStaticDetect                                          */
/*--------------------------------------------------------------------------*/
/*  Scope   : Initialises a flash device descriptor                         */
/*            if the device at the supplied address is statically registered*/
/*                                                                          */
/*  Return    : (s32) FMS_OK or error code                                  */
/*                                                                          */
/*  Interface :                                                             */
/*--------------------------------------------------------------------------*/
/*  Variable Name     |IN |OUT|GLB|  Use                                    */
/*--------------------+---+---+---+-----------------------------------------*/
/*  i__u32_Address    | X |   |   |  Base address of the device             */
/*  o__ps_Descriptor  |   | X |   |  Descriptor to initialise               */
/*--------------------+---+---+---+-----------------------------------------*/
/****************************************************************************/
s32 fms_CoreStaticDetect(u32 i__u32_Address, FlashDeviceDescriptor_t *o__ps_Descriptor);
void fms_CoreStaticDetectEx(void);


/****************************************************************************/
/*  Function: fms_CoreGetDeviceName                                         */
/*--------------------------------------------------------------------------*/
/*  Scope   : Returns the name of the device at the specified address       */
/*                                                                          */
/*  Return    : (s32) FMS_OK or error code                                  */
/*                                                                          */
/*  Interface :                                                             */
/*--------------------------------------------------------------------------*/
/*  Variable Name     |IN |OUT|GLB|  Use                                    */
/*--------------------+---+---+---+-----------------------------------------*/
/*  i__u32_Address    | X |   |   |  Base address of the device             */
/*  o__ppsz_OutName   |   | X |   |  Output string pointer                  */
/*--------------------+---+---+---+-----------------------------------------*/
/****************************************************************************/
s32 fms_CoreGetDeviceName(u32 i__u32_Address, char **o__ppsz_OutName);

/****************************************************************************/
/*  Function: fms_CoreSelectDevice                                          */
/*--------------------------------------------------------------------------*/
/*  Scope   : Returns the pointer to the device descriptor to use           */
/*            for the address given as parameter                            */
/*                                                                          */
/*  Return    : (FlashDeviceDescriptor_t*) Pointer to descriptor or NULL    */
/*                                                                          */
/*  Interface :                                                             */
/*--------------------------------------------------------------------------*/
/*  Variable Name     |IN |OUT|GLB|  Use                                    */
/*--------------------+---+---+---+-----------------------------------------*/
/*  i__u32_Address    | X |   |   |  Address of the incoming operation      */
/*--------------------+---+---+---+-----------------------------------------*/
/****************************************************************************/
FlashDeviceDescriptor_t *fms_CoreSelectDevice(u32 i__u32_Address);
FlashDeviceDescriptor_t *fms_CoreSelectDeviceEx(u32 i__u32_Address);

const FlashConstDeviceDescriptor_t *fms_CoreGetDescriptor(u32 i__u32_FlashIdent);
s32 fms_CoreSpawnDeviceDescriptor(
      const FlashConstDeviceDescriptor_t *i__ps_ConstDevDesc,
      FlashDeviceDescriptor_t *o__ps_DevDesc);

#endif /* ! _6ce936a45cce05dcef3474f8dfc0307e_INCLUDED_FMS_CORE_DETECT_H   */
