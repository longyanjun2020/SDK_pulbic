//------------------------------------------------------------------------------
//
//  File        : ldc_cfg.c
//  Description : Source file of LDC configuration
//  Author      : Eroy
//  Revision    : 0.1
//
//------------------------------------------------------------------------------

//==============================================================================
//
//                              INCLUDE FILE
//
//==============================================================================

//#include "Customer_config.h"
#include "ldc_cfg.h"

//==============================================================================
//
//                              VARIABLES
//
//==============================================================================

/*
 * Configure of LDC
 */
LDC_CFG gsLdcCfg = {
	MMP_FALSE,					// bVidSupport
	MMP_FALSE,					// bDscSupport
	LDC_RUN_MODE_DISABLE,	    // sVidRunMode
	LDC_RUN_MODE_DISABLE,	    // sDscRunMode
};

//==============================================================================
//
//                              FUNCTIONS
//
//==============================================================================

MMP_BOOL MMP_IsVidLdcSupport(void)
{
    return gsLdcCfg.bVidSupport;
}

MMP_BOOL MMP_IsDscLdcSupport(void)
{
    return gsLdcCfg.bDscSupport;
}

MMP_UBYTE MMP_GetVidLdcRunMode(void)
{
	return gsLdcCfg.sVidRunMode;
}

MMP_UBYTE MMP_GetDscLdcRunMode(void)
{
	return gsLdcCfg.sDscRunMode;
}

