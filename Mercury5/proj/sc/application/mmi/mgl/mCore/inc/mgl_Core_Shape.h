/*-----------------------------------------------------------------------------
 *                                                                           
 * Copyright (c) 2008 MStar Semiconductor, Inc.  All rights reserved.
 *                                                                          
 *-----------------------------------------------------------------------------
 * FILE
 *      mgl_Core_Shape.h
 *
 *
 * HISTORY
 *      2009.10.04       Golden Chen         Initial Version
 *                                          
 *----------------------------------------------------------------------------- 
 */

#ifndef __M_CORE_SHAPE_H__
#define __M_CORE_SHAPE_H__

/*------------------------------------------------------------------------------
    Include Files
-------------------------------------------------------------------------------*/
#include "mmi_mae_image.h"
#include "mgl_Core_Types.h"
#include "mgl_Core_Matrix.h"
#include "mgl_Effect_BezierSurface.h"
#include "mgl_Effect_WaterWave.h"
#include "mgl_Effect_BumpMapping.h"
#include "mgl_Effect_FishEye.h"
#include "mgl_Effect_Magnify.h"
#include "mgl_Effect_ClothModeling.h"
#include "mgl_Scene_NodeMgr.h"
#include "mgl_Animation_loader.h"
#include "mgl_ErrCode.h"

/*------------------------------------------------------------------------------
    Data Type
-------------------------------------------------------------------------------*/
typedef struct CubeTex_tag
{
	mgl_u32 FrontImgID;
	mgl_u32 BackImgID;
	mgl_u32 TopImgID;
	mgl_u32 BottomImgID;
	mgl_u32 LeftImgID;
	mgl_u32 RightImgID;
}CubeImgID;

typedef struct CubeAlpha_tag
{
	mgl_float FrontAlpha;
	mgl_float BackAlpha;
	mgl_float TopAlpha;
	mgl_float BottomAlpha;
	mgl_float LeftAlpha;
	mgl_float RightAlpha;
}CubeAlpha;

enum
{
    FrontFace = 0,
    BackFace,    	
    TopFace,
    BottomFace,
    LeftFace,
    RightFace,
    CubeFaceNum
};
typedef mgl_u16 CubeFace;

enum
{
	MGL_TRIANGLES = 0,
	MGL_TRIANGLE_STRIP,	
	MGL_TRIANGLE_FAN
};
typedef mgl_u16 PolygonType;

enum
{
	MGL_LINES = 0,
	MGL_LINE_STRIP,
	MGL_LINE_LOOP,
};
typedef mgl_u16 LineType;

typedef struct CubeColor_tag
{
	Color4f FrontCol;
	Color4f BackCol;
	Color4f TopCol;
	Color4f BottomCol;
	Color4f LeftCol;
	Color4f RightCol;
}CubeColor;

typedef struct SmoothPlaneColorInfo_tag
{
	Color4f RightBottomPtCol;
	Color4f RightUpPtCol;
	Color4f LeftBottomPtCol;
	Color4f LeftUpPtCol;
}SmoothPlaneColorInfo;

typedef struct TexRawDataInfo_Tag
{
    mgl_u32                *pRawDataID;            
    mgl_void               *pRawData;
}TexRawDataInfo;

typedef struct TextureInfo_Tag
{
    mgl_float               alpha;       
    TextureSrc            srcFormat;
    union
    {
        mgl_u32                imgID;          
        mgl_u16                *pFileName;
        TexRawDataInfo    rawDataInfo;
#ifdef __FREETYPE_VECTOR_FONT__                    
        T_TEXTURE_FONT_DATA fontData;
#endif
    }srcData;
}TextureInfo;

enum 
{
    LINE_WITH_COLOR = 0,
    PLANE_WITH_COLOR,
    PLANE_WITH_TEXTURE,
    PLANE_WITH_COLOR_TEXTURE,
    SMOOTH_PLANE_WITH_COLOR,              /* dummy if MGLS*/
    SMOOTH_PLANE_WITH_TEXTURE,
    CUBE_WITH_MULTI_COLOR,
    CUBE_WITH_SINGLE_TEXTURE,
    CUBE_WITH_MULTI_TEXTURE,
    POLYGON_WITH_COLOR,
    POLYGON_WITH_TEXTURE,  
    POLYGON_WITH_COLOR_TEXTURE,
    BEZIER_WITH_TEXTURE,
    WATER_WAVE_WITH_TEXTURE,
    BUMPMAPPING_WITH_TEXTURE,
#ifdef __FREETYPE_VECTOR_FONT__    
    VECTOR_FONT, 
#endif    
    SPRITE_POINT,
    SPHERE_WITH_TEXTURE,
    FISHEYE_WITH_TEXTURE,    
    MAGNIFY_2D,
    CLOTH_MODELING_WITH_TEXTURE,   
    UNKNOWN_SHAPE_TYPE,
};
typedef mgl_u32 ShapeType;

typedef struct LineColor_tag
{
	ShapeType type;
	LineType    lineType;
	Vertex3D   *pVertex;
	Color4f      *pColor;
	mgl_u32    verNum;	
	mgl_u8      width;
}LineColor;

typedef struct PlaneColor_tag
{
    ShapeType type;
    Vertex3D  pos;
    Vertex2D  size;
    Color4f  color;
}PlaneColor;

typedef struct SmoothPlaneColor_tag
{
    ShapeType type;
    Vertex3D  pos;
    Vertex2D  size;
    SmoothPlaneColorInfo  color;
}SmoothPlaneColor;

typedef struct PlaneColorTexture_tag
{
    ShapeType type;
    Vertex3D pos;
    Vertex2D size;
    TextureInfo TexInfo;
    Color4f  color;
}PlaneColorTexture;

typedef struct PlaneTexture_tag
{
    ShapeType type;
    Vertex3D  pos;
    Vertex2D  size;
    TextureInfo TexInfo;
}PlaneTexture;

typedef struct SmoothPlaneTexture_tag
{
    ShapeType type;
    Vertex3D pos;
    Vertex2D  size;
    TextureInfo TexInfo;  
    SmoothPlaneColorInfo  color;
    mgl_float mirrorRatio;
}SmoothPlaneTexture;

typedef struct CubeMultiColor_tag
{
    ShapeType type;
    Vertex3D pos;
    Vertex3D size;
    CubeColor color;
}CubeMultiColor;

typedef struct CubeSingleTexture_tag
{
    ShapeType type;
    Vertex3D  pos;
    Vertex3D  size;
    TextureInfo TexInfo;
}CubeSingleTexture;


enum
{
	MGL_CUBE_TEXTURE_HORIZON = 0,
	MGL_CUBE_TEXTURE_VERTICLE,	
};
typedef mgl_u16 CubeTextureOrientation;

typedef struct CubeMultiTexture_tag
{
    ShapeType type;
    Vertex3D  pos;
    Vertex3D  size;
    TextureInfo TexInfo[CubeFaceNum];
    CubeTextureOrientation orientation;   /* dummy if MGLS */ 
}CubeMultiTexture;

typedef struct PolygonColor_tag
{
    ShapeType type;
    PolygonType  polygon;
    Vertex3D *pVertex;
    mgl_u32  verNum;
    Color4f  color;
}PolygonColor;

typedef struct PolygonTexture_tag
{
    ShapeType type;
    PolygonType polygon;
    Vertex3D *pVertex;
    Vertex2D *pTexCoord;
    mgl_u32 verNum;
    TextureInfo TexInfo;     
}PolygonTexture;

typedef struct PolygonColorTexture_tag
{
    ShapeType type;
    PolygonType polygon;
    Vertex3D *pVertex;
    Vertex2D *pTexCoord;
    Color4f  color;
    mgl_u32 verNum;
    TextureInfo TexInfo;     
}PolygonColorTexture;

typedef struct BezierTexture_tag
{
    ShapeType type;
    BezierInfo bezierInfo;
    TextureInfo TexInfo;             
    TextureInfo TexInfo_Back;
}BezierTexture;

typedef struct WaterWaveTexture_tag
{
    ShapeType type;
    WaterWaveInfo waterInfo;
    TextureInfo TexInfo;
}WaterWaveTexture;

typedef struct BumpMappingTexture_tag
{
    ShapeType type;
    BumpMappingInfo bumpMappingInfo;
    TextureInfo TexInfoBaseMap;
    TextureInfo TexInfoNormalMap;
}BumpMappingTexture;

#ifdef __FREETYPE_VECTOR_FONT__    
typedef struct VectorFontInfo_tag
{
    ShapeType type;
    Vertex3D  pos;    
    Color4f  color;
    mgl_u16 *pWStr;
    mgl_u16 fontSize;
}VectorFontInfo;
#endif

typedef struct SphereTexture_Tag
{
    ShapeType type;
    Color4f color;        
    Vertex3D  center;    
    mgl_float radius;
    TextureInfo TexInfo;     
}SphereTexture;

typedef struct Magnify2D_Tag
{
	ShapeType type;
	MagnifyData MagnifyInfo;
	TextureInfo TexInfo;	
}Magnify2D;

typedef struct FishEyeTexture_tag
{
    ShapeType type;
    FishEyeInfo tFishEyeInfo;
    TextureInfo tTexInfo;
}FishEyeTexture;

typedef struct ClothModelingTexture_tag
{
    ShapeType type;
    ClothModelingInfo clothInfo;
    TextureInfo TexInfo;
}ClothModelingTexture;

typedef struct SpritePointInfo_tag
{
    ShapeType type;
    Vertex3D *pVertex;
    Color4f *pColor;
    mgl_u16 particleNum;
    mgl_u16 particleSize;                    /* 1~32767 is ok */
    TextureInfo TexInfo;     
}SpritePointInfo;

/*------------------------------------------------------------------------------
    Global Function
-------------------------------------------------------------------------------*/
/* MGL state control */
mgl_void mgl_EnableVertexArray(mgl_void);
mgl_void mgl_DisableVertexArray(mgl_void);
mgl_void mgl_EnableTexture0(mgl_void);
mgl_void mgl_DisableTexture0(mgl_void);
mgl_void mgl_EnableTexture1(mgl_void);
mgl_void mgl_DisableTexture1(mgl_void);
mgl_void mgl_EnableColorArray(mgl_void);
mgl_void mgl_DisableColorArray(mgl_void);
mgl_void mgl_EnableBlending(mgl_void);
mgl_void mgl_DisableBlending(mgl_void);
mgl_void mgl_EnableMGLState(mgl_void);
mgl_void mgl_DisableMGLState(mgl_void);
mgl_void mgl_EnableFog(mgl_void); /* dummy if MGLS */
mgl_void mgl_DisableFog(mgl_void); /* dummy if MGLS */
/* for picking */
mgl_void mgl_Shape_DrawBBoxInBackBuffer(mgl_u32 nodeID, AABBox3D *pBbox, Matrix4x4 *pMatrix);
/* for bind texture */
mgl_boolean mgl_BindTexture(T_TEXTURE_ATTR_PTR pTexAttri); /* dummy if G3D */

/* Shape Utility */
mgl_ErrCode mgl_GetCenterOfShape(mgl_void *pShapeData, Vertex3D *pCenterPoint);

/* create shape and draw shape */
mgl_ErrCode mgl_CreateShape(ShapeType type, mgl_void **ppShapeData);
mgl_ErrCode mgl_DrawShape(mgl_u32 nodeID, mgl_void *pShapeData);
mgl_ErrCode mgl_FreeShape(mgl_void *pShapeData);
#endif /* __M_CORE_SHAPE_H__ */

