/*-----------------------------------------------------------------------------
 *                                                                           
 * Copyright (c) 2008 MStar Semiconductor, Inc.  All rights reserved.
 *                                                                          
 *-----------------------------------------------------------------------------
 * FILE
 *      mgl_Core_Types.h
 *
 *
 * HISTORY
 *      2009.10.04       Golden Chen         Initial Version
 *                                          
 *----------------------------------------------------------------------------- 
 */

#ifndef __M_CORE_TYPES_H__
#define __M_CORE_TYPES_H__

/*------------------------------------------------------------------------------
    Include Files
-------------------------------------------------------------------------------*/
#include "mgl_Utility_common.h"
#include "mgl_Core_Fixed.h"

/*------------------------------------------------------------------------------
    Macro
-------------------------------------------------------------------------------*/
#define MGL_PI	  (3.14159265359f)
#define DEGTORAD  (MGL_PI/180.0f)

#define MGL_RGB16_8to5(c)       ((c)&0xF8)
#define MGL_RGB16_8to6(c)       ((c)&0xFC)

#define MGL_RGB16_MASK_R (0xF800)
#define MGL_RGB16_MASK_G (0x07E0)
#define MGL_RGB16_MASK_B (0x001F)

#define MGL_RGB16_GET_RED(c)    (((c&MGL_RGB16_MASK_R)>>11)<<3)
#define MGL_RGB16_GET_GREEN(c)  (((c&MGL_RGB16_MASK_G)>>5)<<2)
#define MGL_RGB16_GET_BLUE(c)   ((c&MGL_RGB16_MASK_B)<<3)
#define MGL_RGB_TO_RGB16(r,g,b) (u16)((((u16)MGL_RGB16_8to5(r))<<8)|(((u16)MGL_RGB16_8to6(g))<<3)|(((u16)MGL_RGB16_8to5(b))>>3))

/*------------------------------------------------------------------------------
    Data Type
-------------------------------------------------------------------------------*/

/* Color */
typedef struct Color4f_tag
{
	mgl_float r;
	mgl_float g;
	mgl_float b;
	mgl_float a;
}Color4f;

typedef struct Color4ub_tag
{
	mgl_u8 r;
	mgl_u8 g;
	mgl_u8 b;
	mgl_u8 a;		
}Color4ub;

/* Vertex */
typedef struct Vertex2D_tag
{
	mgl_float x;
	mgl_float y;	
}Vertex2D;

typedef struct Vertex3D_tag
{
	mgl_float x;
	mgl_float y;
	mgl_float z;
}Vertex3D;

typedef struct Vertex4D_tag
{
	mgl_float x;
	mgl_float y;
	mgl_float z;
	mgl_float w;
}Vertex4D;

typedef struct TexCoord_tag
{
	mgl_float u;
	mgl_float v;
}TexCoord;

/* Ray */
typedef struct Ray2D_tag
{
	Vertex2D Start;
	Vertex2D End;
}Ray2D;

typedef struct Ray3D_tag
{
	Vertex3D Start;
	Vertex3D End;
}Ray3D;

/* Bounding Box */
typedef struct AABBox3D_tag
{
	Vertex3D MinPoint;
	Vertex3D MaxPoint;
}AABBox3D;

/*------------------------------------------------------------------------------
    Global Macro
-------------------------------------------------------------------------------*/
/* Color */
#define mgl_Color4f_Set(_c_, _r_, _g_, _b_, _a_) { (_c_).r=(_r_); (_c_).g=(_g_); (_c_).b=(_b_); (_c_).a=(_a_); }

/* Vertex */
#define mgl_Vertex2D_Set(_v_, _x_, _y_) { (_v_).x = (_x_); (_v_).y = (_y_); }
#define mgl_Vertex3D_Set(_v_, _x_, _y_, _z_) { (_v_).x = (_x_); (_v_).y = (_y_); (_v_).z = (_z_); }
#define mgl_Vertex4D_Set(_v_, _x_, _y_, _z_, _w_) { (_v_).x = (_x_); (_v_).y = (_y_); (_v_).z = (_z_); (_v_).w = (_w_);}
#define mgl_TexCoord_Set(_t_, _u_, _v_) { (_t_).u = (_u_); (_t_).v = (_v_); }

/* Ray */
#define mgl_Ray2D_Set(_r_, _s_, _e_) { (_r_).Start = (_s_); (_r_).End = (_e_); }
#define mgl_Ray3D_Set(_r_, _s_, _e_) { (_r_).Start = (_s_); (_r_).End = (_e_); }

/* Bounding Box */
#define mgl_AABBox3D_Set(_b_, _min_, _max_) { (_b_).MinPoint = (_min_); (_b_).MaxPoint = (_max_); }

/*------------------------------------------------------------------------------
    Global inline Function
-------------------------------------------------------------------------------*/
static __inline Vertex3D mgl_PointMinus(Vertex3D p, Vertex3D q) 
{
	p.x -= q.x;		p.y -= q.y;		p.z -= q.z;
	return p;
}

static __inline Vertex3D mgl_PointAdd(Vertex3D p, Vertex3D q) 
{
	p.x += q.x;		p.y += q.y;		p.z += q.z;
	return p;
}

static __inline Vertex3D mgl_PointTimes(mgl_float c, Vertex3D p) 
{
	p.x *= c;	p.y *= c;	p.z *= c;
	return p;
}

static __inline Vertex3D mgl_PointLerp(mgl_float s, Vertex3D p, Vertex3D q)
{
	return mgl_PointAdd(p, mgl_PointTimes(s, mgl_PointMinus(q, p)));
}

/*------------------------------------------------------------------------------
    Global Function
-------------------------------------------------------------------------------*/
/* Vertex */
Vertex3D mgl_Vertex_Get3DFrom4D(const Vertex4D *pV4);
Vertex4D mgl_Vertex_Get4DFrom3D(const Vertex3D *pV3);

/* Ray */
Vertex3D mgl_Ray3D_GetVector(const Ray3D *pR);
mgl_float    mgl_Ray3D_GetLength(const Ray3D *pR);

/* Bounding Box */
mgl_void    mgl_AABBox_Reset(AABBox3D *pBbox);
mgl_void    mgl_AABBox_AddInternalPoint(AABBox3D *pBbox, const Vertex3D *p);
mgl_boolean mgl_AABBox_IntersectsWithRay(const AABBox3D *pBbox, const Ray3D *pR);

/* Common Utility */
mgl_float mgl_SquareRootFloat(mgl_float number);
mgl_float mgl_Vertex3D_Length(const Vertex3D *pV);
mgl_float mgl_Vertex3D_Dot(Vertex3D *pV0, const Vertex3D *pV1);
mgl_void  mgl_Vertex3D_Cross(const Vertex3D *pV0, const Vertex3D *pV1, Vertex3D *pR);
mgl_void  mgl_Vertex3D_Normalize(Vertex3D *pV);
mgl_void  mgl_Vertex3D_Scale01(Vertex3D *pV);
mgl_boolean mgl_ArcBallClick(Vertex2D *pDownPt, mgl_u32 boundWidth, mgl_u32 boundHeight);
mgl_boolean mgl_ArcBallDrag(Vertex2D *pDragPt, mgl_u32 boundWidth, mgl_u32 boundHeight, Vertex4D *pQuatRot);

#endif /* __M_CORE_TYPES_H__ */

