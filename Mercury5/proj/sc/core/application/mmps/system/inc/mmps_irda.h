//==============================================================================
//
//  File        : mmps_IrDA.h
//  Description : INCLUDE File for the irda decode.
//  Author      : lei.qin
//  Revision    : 1.0
//
//==============================================================================

#ifndef _MMPS_IRDA_H_
#define _MMPS_IRDA_H_

//==============================================================================
//
//                              INCLUDE FILE
//
//==============================================================================

#include "mmp_lib.h"
#include "ait_config.h"

//==============================================================================
//
//                              FUNCTION PROTOTYPES
//
//==============================================================================

MMP_ERR MMPS_IrDA_Initialize(void);
MMP_ERR MMPS_IrDA_SetIrCb(void* IrCode0CB, void *IrCode1CB);
MMP_ERR MMPS_IrDA_SetIrEn(MMP_BOOL bEnable);

/// @}
#endif // _MMPS_IRDA_H_
