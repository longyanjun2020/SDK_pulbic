/*-----------------------------------------------------------------------------
 *                                                                           
 * Copyright (c) 2009 MStar Semiconductor, Inc.  All rights reserved.
 *                                                                          
 *-----------------------------------------------------------------------------
 * FILE
 *      rm_IniReader.h
 *
 * DESCRIPTION
 *      This file provides the local functions to read from ini file
 *
 * HISTORY
 *      2009.03.01       Donald Hung     Initial Version
 *----------------------------------------------------------------------------- 
 */


#ifndef _FW_INIREADER_H_
#define _FW_INIREADER_H_

/*------------------------------------------------------------------------------
    Include Files
-------------------------------------------------------------------------------*/
#include "fw_util.h"

typedef enum _T_IniAttr_TAG 
{
    eIniReadErrorEOF = 0,
    eIniComment = 1,
    eIniSectionName,
    eIniString,
    eIniStringEnd
} e_Ini_Attr;

#ifdef __cpluscplus
extern "C" {
#endif

MBOOL        fw_IniOpenFile(PU16 psFileName);
e_Ini_Attr   fw_IniGetNextToken(PU16 *ptsLValue, const PU16 ptsDelmStr, MBOOL bDelimCheck);
PU16         fw_IniFGets(MVOID);
MVOID        fw_IniCloseFile(MVOID);

#ifdef __cpluscplus
}
#endif


#endif
