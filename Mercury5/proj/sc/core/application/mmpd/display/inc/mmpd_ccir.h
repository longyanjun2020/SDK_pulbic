//==============================================================================
//
//  File        : mmpd_ccir.h
//  Description : INCLUDE File for the CCIR driver function
//  Author      : Alterman
//  Revision    : 1.0
//
//==============================================================================

#ifndef _MMPD_CCIR_H_
#define _MMPD_CCIR_H_

//==============================================================================
//
//                              INCLUDE FILE
//
//==============================================================================

#include "mmpf_ccir.h"
#include "mmp_scal_inc.h"
#include "mmp_display_inc.h"

/** @addtogroup MMPD_CCIR
 *  @{
 */

//==============================================================================
//
//                              FUNCTION PROTOTYPES
//
//==============================================================================

MMP_ERR MMPD_Display_SetCCIROutput( MMP_DISPLAY_CONTROLLER  controller,
                                    MMP_CCIR_ATTR           ccirAttr);
MMP_ERR MMPD_CCIR_SetDisplayBufAddr(MMP_ULONG ulBaseAddr);
MMP_ERR MMPD_CCIR_SetDisplayRefresh(void);
MMP_ERR MMPD_CCIR_DisableDisplay(void);

/// @}
#endif // _MMPD_CCIR_H_
