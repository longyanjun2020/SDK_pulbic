//==============================================================================
//
//  File        : ahc_ddosd.h
//  Description : INCLUDE File for the AHC dynamic download OSD porting.
//  Author      : 
//  Revision    : 1.0
//
//==============================================================================

#ifndef _AHC_DDOSD_H_
#define _AHC_DDOSD_H_

/*===========================================================================
 * Include files
 *===========================================================================*/

#include "ahc_common.h"

/*===========================================================================
 * Enum define
 *===========================================================================*/

/*===========================================================================
 * Structure define
 *===========================================================================*/
typedef struct _DDOSD_OFFSET{
UINT16  IconNameLen;
UINT16  IconNameOffset;
UINT16  ColorsOffset;
UINT16  PictureDataOffset;
} DDOSD_OFFSET,*PDDOSD_OFFSET;


/*===========================================================================
 * Function prototype
 *===========================================================================*/
AHC_BOOL 	AHC_DDOSD_Init(void);
AHC_BOOL 	AHC_DDOSD_AddIcon(char *String, UINT StringLen);
AHC_BOOL 	AHC_DDOSD_Check(char *IconName, UINT *IconIntex);
AHC_BOOL 	AHC_DDSOD_UnInit(void);
AHC_BOOL 	AHC_DDOSD_DrawBitmap(UINT16 uwDisplayID, char *IconName, UINT16 uwX, UINT16 uwY);


#endif // _AHC_DDOSD_H_
