////////////////////////////////////////////////////////////////////////////////
//
// Copyright (c) 2006-2009 MStar Semiconductor, Inc.
// All rights reserved.
//
// Unless otherwise stipulated in writing, any and all information contained
// herein regardless in any format shall remain the sole proprietary of
// MStar Semiconductor Inc. and be kept in strict confidence
// (¡§MStar Confidential Information¡¨) by the recipient.
// Any unauthorized act including without limitation unauthorized disclosure,
// copying, use, reproduction, sale, distribution, modification, disassembling,
// reverse engineering and compiling of the contents of MStar Confidential
// Information is unlawful and strictly prohibited. MStar hereby reserves the
// rights to any and all damages, losses, costs and expenses resulting therefrom.
//
////////////////////////////////////////////////////////////////////////////////

/**
* @file    MsLzma.h
* @version
* @brief   This module defines the Scaler driver hal layer
*
*/



/*=============================================================*/
// Include files
/*=============================================================*/

/*=============================================================*/
// Extern definition
/*=============================================================*/

/*=============================================================*/
// Macro definition



/*=============================================================*/
// Data type definition
/*=============================================================*/


/*=============================================================*/
// Variable definition
/*=============================================================*/

/*=============================================================*/
// Global function definition
/*================================================*/
void MsLzmaInit(void);

unsigned int MsLzmaCompress(void *in_data, unsigned int in_len,
	      void *out_data, unsigned int out_len);
unsigned int MsLzmaDeCompress (void *in_data,  unsigned int in_len,
                void *out_data, unsigned int out_len, unsigned int parameter);


