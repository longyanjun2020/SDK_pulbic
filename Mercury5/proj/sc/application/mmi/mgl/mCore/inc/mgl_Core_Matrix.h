/*-----------------------------------------------------------------------------
 *                                                                           
 * Copyright (c) 2008 MStar Semiconductor, Inc.  All rights reserved.
 *                                                                          
 *-----------------------------------------------------------------------------
 * FILE
 *      mgl_Core_Matrix.h
 *
 *
 * HISTORY
 *      2009.10.04       Golden Chen         Initial Version
 *                                          
 *----------------------------------------------------------------------------- 
 */

#ifndef __M_CORE_MATRIX_H__
#define __M_CORE_MATRIX_H__

/*------------------------------------------------------------------------------
    Include Files
-------------------------------------------------------------------------------*/
#include "mgl_Core_Types.h"
#include "mgl_Core_Transform.h"

/*------------------------------------------------------------------------------
    Data Type
-------------------------------------------------------------------------------*/
typedef struct Matrix4x4Float_tag
{
	mgl_float M[16];
}Matrix4x4Float;

typedef struct Matrix4x4Fixed_tag
{
	mgl_s32 M[16];
}Matrix4x4Fixed;

#if defined( __G3D_MMI__)
typedef Matrix4x4Float Matrix4x4;
#else 
typedef Matrix4x4Fixed Matrix4x4;
#endif

// function definition
typedef Matrix4x4 (*pfnGetRelativeTransformation)(mgl_void);

/*------------------------------------------------------------------------------
    Global Function
-------------------------------------------------------------------------------*/
mgl_void mgl_Matrix3x3_MultiBy3x3(mgl_float vecIn[3], mgl_float m[16], mgl_float vecOut[3]) ;

mgl_void mgl_Matrix4x4_Assign(Matrix4x4 *pDestM, const Matrix4x4 *pSrcM);

/* [MDest] = [M1] x [M2] */
mgl_void mgl_Matrix4x4_MultiBy4x4(const Matrix4x4 *pM1, const Matrix4x4 *pM2, Matrix4x4 *pMDest);

/* [VDest] = [V] x [M] */
mgl_void mgl_Matrix4x4_MultiBy1x4(const Vertex4D *pV, const Matrix4x4 *pM, Vertex4D *pVDest);

mgl_boolean mgl_Matrix4x4_GetInverse(Matrix4x4 *pIn, Matrix4x4 *pOut);
mgl_float   mgl_Matrix4x4_GetElement(Matrix4x4 *pM, s32 row, s32 col);   /* Row Major */
mgl_void mgl_Matrix4x4_Row2ColumnMajor(Matrix4x4 *pRowMatrix, Matrix4x4 *pColumnMatrix);
mgl_void mgl_Matrix4x4_MakeI(Matrix4x4 *pM);
mgl_void mgl_GetInverseModelViewVector(Vertex3D *pRay);
mgl_void mgl_QuatToMatrix4(Vertex4D *pQuatRot, Matrix4x4 *pMatrixRot);
mgl_void mgl_ApplyRotate(RotateInfo *pRotate, Matrix4x4 *pIn, Matrix4x4 *pOut);
mgl_void mgl_ApplyTranslate(TranslateInfo *pTranslate, Matrix4x4 *pIn, Matrix4x4 *pOut);
mgl_void mgl_ApplyScale(ScaleInfo *pScale, Matrix4x4 *pIn, Matrix4x4 *pOut);

#endif /* __M_CORE_MATRIX_H__ */

