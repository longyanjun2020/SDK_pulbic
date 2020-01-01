#ifndef _SPEC_TOOL_H_
#define _SPEC_TOOL_H_

#include "swvenc_deftypes.h"
#include "swvenc_h263_me_mgr.h"

// ----------------------------------------------------------------------------
//                         Public Functions
// ----------------------------------------------------------------------------
void GetInterMbVar(short *pBuf, int* pVar, int* pSum, int blk_idx, int blk_idx2);

// ----------------------------------------------------------------------------
//                                Internal Functions
// ----------------------------------------------------------------------------
int ModeDecisionWithYMC(MBINFO_t* pMbInfo, uint8 *ref, int16* DctBuf, int nStrideDstSrc,int nStrideDst, int nStrideRef);

#endif
