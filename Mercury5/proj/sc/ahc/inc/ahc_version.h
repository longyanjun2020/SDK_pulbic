//==============================================================================
//
//  File        : ahc_version.h
//  Author      : Caesar Chang
//  Revision    : 1.0
//
//==============================================================================

#ifndef _AHC_VERSION_H_
#define _AHC_VERSION_H_

/*===========================================================================
 * Include files
 *===========================================================================*/

#include "ahc_common.h"

/*===========================================================================
 * Function prototype
 *===========================================================================*/

void AHC_GetHwVersion(BYTE* pbyChipVersion, BYTE* pbyEcoVersion, BYTE* pbyModel);

int  AHC_GetMinorVersion(void);

void AHC_GetFwVersion( UINT16* pulFwMajorVersion, 
      		           UINT16* pulFwMidVersion, 
                	   UINT16* pulFwMinorVersion, 
                	   UINT16* pulFwBranchVersion, 
                	   UINT16* puwFwTestVersion, 
                	   char** pszReleaseName );

void AHC_PrintFwVersion(void);
void AHC_PrintBuildTime(void);

#endif
