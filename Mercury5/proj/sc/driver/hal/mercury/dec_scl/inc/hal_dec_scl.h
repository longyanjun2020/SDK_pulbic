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
* @file    hal_scl.h
* @version
* @brief   This file contains the scl headers.
*
*/

#ifndef __HAL_SCL_H__
#define __HAL_SCL_H__

/*=============================================================*/
// Include files
/*=============================================================*/


/*=============================================================*/
// Extern definition
/*=============================================================*/

/*=============================================================*/
// Macro definition
/*=============================================================*/

typedef enum
{
    EN_DEC_OSDB_LOC_BYPASS_VIP=0,
    EN_DEC_OSDB_LOC_PASS_VIP,
}EN_DEC_OSDB_LOC;

/*=============================================================*/
// Data type definition
/*=============================================================*/
typedef struct
{
    u16  u16Y2R_COEFF_11;
    u16  u16Y2R_COEFF_12;
    u16  u16Y2R_COEFF_13;
    u16  u16Y2R_COEFF_21;
    u16  u16Y2R_COEFF_22;
    u16  u16Y2R_COEFF_23;
	u16  u16Y2R_COEFF_31;
    u16  u16Y2R_COEFF_32;
    u16  u16Y2R_COEFF_33;
}ST_VOP_CSC_MATRIX;

/*=============================================================*/
// Variable definition
/*=============================================================*/

/*=============================================================*/
// Global function definition
/*=============================================================*/
void HalSclInit(void);
U16 Hal_Dec_SclRegisterRead(U32 u32Addr);
void Hal_Dec_SclRegisterWrite(U32 u32Addr, U16 u16value);
void Hal_Dec_Scl_Set_OSDB_Loc(EN_DEC_OSDB_LOC bOsdbLoc);

#endif //__HAL_SCL_H__
