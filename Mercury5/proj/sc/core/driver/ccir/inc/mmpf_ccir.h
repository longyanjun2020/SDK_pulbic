#ifndef _MMPF_CCIR_H_
#define _MMPF_CCIR_H_

//==============================================================================
//
//                              INCLUDE FILE
//
//==============================================================================

//#include "config_fw.h"
#include "mmp_lib.h"
#include "mmp_display_inc.h"

//==============================================================================
//
//                              DATA TYPES
//
//==============================================================================

typedef void        (MMPF_CCIR_Callback) (MMP_ULONG);

//==============================================================================
//
//                              FUNCTION PROTOTYPE
//
//============================================================================== 

void MMPF_CCIR_RegisterCallback(MMPF_CCIR_Callback *cb);
MMP_ERR MMPF_CCIR_ConfigCCIR(MMP_CCIR_ATTR* pAttr);
MMP_ERR MMPF_CCIR_SetPedBufferAddr(MMP_ULONG ulStartAddr);
MMP_ERR MMPF_CCIR_SetRefresh(void);
MMP_ERR MMPF_CCIR_StartRefresh(void);
MMP_ERR MMPF_CCIR_StopRefresh(void);

#endif // _MMPF_CCIR_H_