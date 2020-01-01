//==============================================================================
//
//  File        : ahc_callback.h
//  Description : INCLUDE File for the AHC Callback function porting.
//  Author      : 
//  Revision    : 1.0
//
//==============================================================================

#ifndef _AHC_CALLBCAK_H_
#define _AHC_CALLBCAK_H_

/*===========================================================================
 * Include files
 *===========================================================================*/
#include "ahc_common.h" 


/*===========================================================================
 * Macro define
 *===========================================================================*/



/*===========================================================================
 * Enum define
 *===========================================================================*/



/*===========================================================================
 * Structure define
 *===========================================================================*/



/*===========================================================================
 * Function prototype
 *===========================================================================*/

void AHC_PostInitISP( void );
void AHC_PostEmergencyDone(void);
void AHC_FormatFreeConfigInfo( void );
void AHC_FormatFreeFileNameCB( MMP_ULONG ulFolderIndex, MMP_ULONG ulFileIndex, MMP_BYTE byFileName[] );

void AHC_PostDualRecdDone(void);
void AHC_UF_CreateShareFileCB(UINT8 *NeedFileNum);
#endif //_AHC_CALLBCAK_H_
