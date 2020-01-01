//------------------------------------------------------------------------------
//
//  File        : ldc_cfg.h
//  Description : Header file of LDC configuration
//  Author      : Eroy
//  Revision    : 0.1
//
//------------------------------------------------------------------------------

#ifndef _LDC_CFG_H_
#define _LDC_CFG_H_

//==============================================================================
//
//                              INCLUDE FILE
//
//==============================================================================

#include "lib_retina.h"

//==============================================================================
//
//                              ENUMERATION
//
//==============================================================================

typedef enum {
	LDC_RUN_MODE_LB_SINGLE,
	LDC_RUN_MODE_LB_MULTI,
	LDC_RUN_MODE_MULTISLICE,
	LDC_RUN_MODE_DISABLE,
	LDC_RUN_MODE_NUM
} LDC_RUN_MODE;

//==============================================================================
//
//                              STRUCTURES
//
//==============================================================================

typedef struct {
    MMP_BOOL				bVidSupport;
    MMP_BOOL				bDscSupport;
    LDC_RUN_MODE			sVidRunMode;
    LDC_RUN_MODE			sDscRunMode;
} LDC_CFG;

//==============================================================================
//
//                              EXTERN VARIABLES
//
//==============================================================================

extern LDC_CFG gsLdcCfg;

//==============================================================================
//
//                              Function
//
//==============================================================================

MMP_BOOL MMP_IsVidLdcSupport(void);
MMP_BOOL MMP_IsDscLdcSupport(void);
MMP_UBYTE MMP_GetVidLdcRunMode(void);
MMP_UBYTE MMP_GetDscLdcRunMode(void);

#endif // _LDC_CFG_H_

