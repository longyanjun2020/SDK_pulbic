/*-----------------------------------------------------------------------------
 *                                                                           
 * Copyright (c) 2008 MStar Semiconductor, Inc.  All rights reserved.
 *                                                                          
 *-----------------------------------------------------------------------------
 * FILE
 *      fw_file.h
 *
 * DESCRIPTION
 *      MStar Framework file functions. 
 *
 * HISTORY
 *      2008.05.01       Mickey Chiang         Initial Version
 *      2008.10.03       Jimmy Hsu             Restructure
 *                                          
 *----------------------------------------------------------------------------- 
 */
#ifndef FW_FILE_H
#define FW_FILE_H

/*------------------------------------------------------------------------------
    Include Files
-------------------------------------------------------------------------------*/
#include <stdlib.h>


// for framework definition
#include "fw_std.h"

  
/*------------------------------------------------------------------------------
    EXTERN definition
-------------------------------------------------------------------------------*/

/*------------------------------------------------------------------------------
    Constant
-------------------------------------------------------------------------------*/

/*------------------------------------------------------------------------------
    Data Type
-------------------------------------------------------------------------------*/
enum
{
    E_SEEK_SET=0,
    E_SEEK_CUR=1,
    E_SEEK_END=2
};

/*------------------------------------------------------------------------------
    Variable
-------------------------------------------------------------------------------*/

/*------------------------------------------------------------------------------
    Macro
-------------------------------------------------------------------------------*/
#if defined(XMMI)
  #define IsDIR(x) mfFILEIsDirectory(x)
#elif defined(WIN32)||defined(WINCE)
    #define IsDIR(x)    ((x).st_mode&_S_IFDIR)
#else  
    #define IsDIR(x)    (S_ISDIR((x).st_mode))
#endif 

/*------------------------------------------------------------------------------
    Global Function
-------------------------------------------------------------------------------*/
MHANDLE mfFILEOpen(const PU16 pwszFilename, const PS8 pszMode);
S32 mfFILEClose(MHANDLE hHandle);
S32 mfFILERead(MHANDLE hHandle, PMVOID pvBuffer, S32 s32Size);
S32 mfFILEWrite(MHANDLE hHandle, const PMVOID pvBuffer, S32 s32Size);
S32 mfFILESeek(MHANDLE hHandle, S32 s32Offset, S32 s32Where);
S32 mfFILETell(MHANDLE hHandle);
S32 mfFILEGetSize(const PU16 pwszFilename);
S32 mfFILEGetInfo(const PU16 pwszFilename,  void  *output_info);
MBOOL mfFILEIsDirectory(void *info);
S32 mfFILEDelet(const PU16 pwszFilename);
S32 mfDirMake(const PU16 pwszFilename);
S32 mfFILERename(const PU16 pwszOldFilename, const PU16 pwszNewFilename);
U32 mfFILEGetFreeSpace(const u8 u8VFSType);
S32 mfFileCopy(const PU16 pwszOldFilename, const PU16 pwszNewFilename);

#endif /* FW_FILE_H */
