#ifndef __M_TEXTURE_IMGMGR_H__
#define __M_TEXTURE_IMGMGR_H__
/*-----------------------------------------------------------------------------
 *                                                                           
 * Copyright (c) 2008 MStar Semiconductor, Inc.  All rights reserved.
 *                                                                          
 *-----------------------------------------------------------------------------
 * FILE
 *      mgl_Texture_ImgMgr.h
 *
 *
 * HISTORY
 *      2009.09.24       Chunwei Wang         Initial Version
 *                                          
 *----------------------------------------------------------------------------- 
 */


/*------------------------------------------------------------------------------
    Include Files
-------------------------------------------------------------------------------*/
#include "mmi_mae_common_def.h"
#include "mgl_Utility_common.h"
#include "mgl_Utility_hash.h"

/*------------------------------------------------------------------------------
    Macro
-------------------------------------------------------------------------------*/
#define MAX_TEXTURE_COUNT (10)
#define NOT_FOUND_TEXTURE (MAX_TEXTURE_COUNT + 1)

/*------------------------------------------------------------------------------
    Data Type
-------------------------------------------------------------------------------*/
typedef  struct _T_TEXTURE_TAG
{
    mgl_u32     textureID;
    mgl_u32     textureMaskID;
    mgl_u16     u16Width;
    mgl_u16     u16Height;
    mgl_u16     u16ImageWidth;
    mgl_u16     u16ImageHeight;
    mgl_float   fLeftX;
    mgl_float   fRightX;
    mgl_float   fBottomY;
    mgl_float   fTopY;
    mgl_float   wRatio;
    mgl_float   hRatio;
    mgl_void    *pTexMem;
    mgl_void    *pAlphaTexMem;
    mgl_u16     cbxPitch; /* dummy if G3D */
    mgl_u16     cbyPitch; /* dummy if G3D */    
    mgl_u32     format; /* < Do NOT modify manually */ /* dummy if G3D */
} T_TEXTURE_ATTR_DATA, *T_TEXTURE_ATTR_PTR;

typedef enum TextureSrc_Tag
{
    TEXTURE_FROM_UNKNOWN = 0, 
    TEXTURE_FROM_IMG_ID,
    TEXTURE_FROM_FILE_NAME,
    TEXTURE_FROM_RAW_DATA,
#ifdef __FREETYPE_VECTOR_FONT__                
    TEXTURE_FROM_VECTOR_FONT,
#endif    
}TextureSrc;

#ifdef __FREETYPE_VECTOR_FONT__            
typedef struct T_TEXTURE_FONT_TAG T_TEXTURE_FONT_DATA, *T_TEXTURE_FONT_PTR;
struct T_TEXTURE_FONT_TAG
{
    mgl_u16 wChar;
    mgl_u16 fontSize;
};
#endif

typedef struct T_TEXTURE_SOURCE_TAG T_TEXTURE_SOURCE_DATA, *T_TEXTURE_SOURCE_PTR;
struct T_TEXTURE_SOURCE_TAG
{
    TextureSrc            srcFormat;
    union
    {
        mgl_u32                imgID;  
        mgl_u32                rawDataID;    
        mgl_u16                *pFileName;
#ifdef __FREETYPE_VECTOR_FONT__                    
        T_TEXTURE_FONT_DATA fontData;
#endif
    }srcData;
};

typedef struct T_TEXTURE_ELEMENT_TAG T_TEXTURE_ELEMENT_DATA, *T_TEXTURE_ELEMENT_PTR;
struct T_TEXTURE_ELEMENT_TAG
{
    T_TEXTURE_SOURCE_DATA data;
    T_TEXTURE_ATTR_PTR   ptIconAttr;
};

typedef struct T_TEXTURE_TAG T_TEXTURE_DATA, *T_TEXTURE_PTR;
struct T_TEXTURE_TAG
{
    T_TEXTURE_PTR       ptHashNext;    
    T_TEXTURE_ELEMENT_DATA element;
    T_TEXTURE_PTR       ptPrev;
    T_TEXTURE_PTR       ptNext;
};
  
typedef struct T_TEXTURE_HASH_TAG T_TEXTURE_HASH_DATA, *T_TEXTURE_HASH_PTR;
struct T_TEXTURE_HASH_TAG
{       
    pMGL_Hash_st         ptHash;
    T_TEXTURE_PTR        ptFirst;
    T_TEXTURE_PTR        ptLast;    
};

/*------------------------------------------------------------------------------
    Global Function
-------------------------------------------------------------------------------*/
mgl_u16 mgl_ImgMgr_Init(mgl_void);
mgl_boolean mgl_ImgMgr_GetTexture(mgl_u16 handleID, T_TEXTURE_SOURCE_DATA TexSoureData, T_TEXTURE_ATTR_PTR ptIconAttr, mgl_void *pRawData);
mgl_void mgl_ImgMgr_DeleteTexture(mgl_u16 handleID, T_TEXTURE_SOURCE_DATA TexSoureData);
mgl_void mgl_ImgMgr_End(mgl_u16 handleID);

#endif /* __M_TEXTURE_IMGMGR_H__ */

