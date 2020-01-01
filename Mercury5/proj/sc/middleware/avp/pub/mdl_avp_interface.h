////////////////////////////////////////////////////////////////////////////////
//
// Copyright (c) 2009-2010 MStar Semiconductor, Inc.
// All rights reserved.
//
// Unless otherwise stipulated in writing, any and all information contained
// herein regardless in any format shall remain the sole proprietary of
// MStar Semiconductor Inc. and be kept in strict confidence
// ("MStar Confidential Information") by the recipient.
// Any unauthorized act including without limitation unauthorized disclosure,
// copying, use, reproduction, sale, distribution, modification, disassembling,
// reverse engineering and compiling of the contents of MStar Confidential
// Information is unlawful and strictly prohibited. MStar hereby reserves the
// rights to any and all damages, losses, costs and expenses resulting therefrom.
//
////////////////////////////////////////////////////////////////////////////////

#ifndef _MDL_AVP_INTERFACE_H_
#define _MDL_AVP_INTERFACE_H_

#include <stdint.h>

void MDLVidPlayCtlInit(void);
void MDLVidPlayCtlProc(void *pMessage);

void MdlAvpParseUseCase(void *pUseCaseParam, uint32_t nUseCaseParamSize, uint32_t nUserData);
#endif
