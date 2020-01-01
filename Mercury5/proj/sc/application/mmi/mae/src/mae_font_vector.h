#ifndef __MAE_FONT_VECTOR_H__
#define __MAE_FONT_VECTOR_H__

#ifdef __FEATURE_VECTOR_FONT__

#include "mmi_mae_font_base.h"

extern boolean _FontBaseIsControlChar(u32 u32Unicode);

typedef struct
{
    s32  fontfrom;
    s32  faceIndex;
    s32  cmapIndex;
	const u8 *pGDEF;
	const u8 *pGPOS;
	const u8 *pGSUB;
	const u8 *pMort;
	const u8 *pKern;
	u16 u16UnitsPerEM; 
}TFont, *PFont;

typedef struct TTF_Bitmap_
{
    s32 rows;
    s32 width;
    s32 pitch;
    u8* buffer;
    s32 x;
    s32 y;
	s32 xadvance;
    s32 yadvance;
    s32 gidx;
	s32 s32PreGap;
	s32 s32PosGap;
	s32 s32ZeroWidth;
	s32 iOutLineWidth; //iOutLineWidth = 0 is mean that no outline
    s32 irows;
    s32 iwidth;
    s32 ipitch;
    u8* ibuffer;
} TTF_Bitmap;

typedef struct  TTF_BmpCacheInfo_
{
    s8 width;
    s8 left;
    s8 top;
    s8 xadvance;
    s8 yadvance;
} TTF_BmpCacheInfo;

typedef struct TTF_Vector_
{
    s32 x;
    s32 y;
} TTF_Vector;

typedef struct TTF_FaceInf_
{
    s32 ascender;
	s32 descender;
	s32 height;
    s32 yMax;
	s32 yScale;
} TTF_FaceInf;

typedef struct
{
    void *pUserData;
    void *pIFStream;
	u8 *pCardTTFontData;
	u32 nCardTTFontSize;
	Change_Font_Result_CB pResultCB;
}TTF_Card_Data_t;

MAE_Ret FONTBASE_VectorFontSetCategory(void);
void FONTBASE_VectorFontSetSizeMap( void );
void FONTBASE_VectorFontSetExist(void);
void FONTBASE_VectorFontSetCombineBitmap(void);
boolean FONTBASE_VectorFontIsForceBitmapFont(u32 nFontCate);
void FONTBASE_VectorFontInit( void );
void FONTBASE_VectorFontUnInit( void );
void FONTBASE_VectorFontFree( void );
boolean FONTBASE_VectorFontIsMapToCategory( u32 nBitmapFontCategory );
u16 FONTBASE_GetVectorFontSize( void );
u16 FONTBASE_GetVectorMapFontSize( u32 u32Category ); 
u32 FONTBASE_VectorFontGetGlyphId(u32 u32UcsCode);
MAE_Ret FONTBASE_VectorFontGetTFGlyphInfAllocate(u32 u32GlyphId, TTF_Bitmap **pTTFBitmap);
void FONTBASE_VectorFontTFBitmapFree(TTF_Bitmap *pTFBitmap);
MAE_Ret FONTBASE_VectorFontGetFaceInf( TTF_FaceInf *pFaceInf, u32 u32FontSize);

const u8* FONTBASE_VectorFontGetGDEFTable( void );
const u8* FONTBASE_VectorFontGetGPOSTable( void );
const u8* FONTBASE_VectorFontGetGSUBTable( void );
//const u8* FONTBASE_VectorFontGetKernTable( void );
//const u8* FONTBASE_VectorFontGetMortTable( void );
u16 FONTBASE_VectorFontGetUnitPerEM( void );
s32 FONTBASE_VectorFontGetXScaleFactor( void );
s32 FONTBASE_VectorFontGetYScaleFactor( void );
// vector font from sd card
MAE_Ret FONTBASE_CreateVectorFont_FromFile(void);
MAE_Ret FONTBASE_CreateVectorFont_FromMemory(const void* data, u32 size);
MAE_Ret FONTBASE_CreateVectorFont_FromCus( void );

MAE_Ret FONTBASE_Vector_MeasureText(u32 nFontSize, 
                                    const u16 *pText,                    // text buffer pointer
                                    u32 nChars,                          // number of text character
                                    u32 nOffset,                         // 0
                                    u32 nSubLen,                         // still number of text character
                                    u32 nMaxWidth,
                                    u32 *pFits,                          // [out]
                                    u32 *pPixels,                        // [out]
                                    u32 nType,
                                    u32 bSkip,
                                    boolean bDispStr );                   // FALSE

MAE_Ret FONTBASE_Vector_DrawText(u32 FontSize,              // Size
                                 BitmapBase_t *pDst,        // Destination BitmapBase
                                 s32 xStart,                // start x
                                 s32 yStart,                // start y
                                 const u16 *pText,          // text buffer pointer
                                 u32 nChars,                // number of text character
                                 RGBColor_t ClrFG,          // foreground color
                                 RGBColor_t ClrOL,          // background color
                                 Rect_t *pCARect,           // Client area
                                 u32 nType,                  // Type
                                 u32 *pColors,              // Color table for the random FG. (Random FG for each character. if this parameter is set the ClrFG param will be ignored)
                                 u8 nNumColor);

MAE_Ret FONTBASE_Vector_GetInfo(u32 nFontSize, u32 Type, FontInfo *pinfo);

MAE_Ret FONTBASE_Vector_CreateGlyphDib(u32 nFontSize, u32 Type, u16 Code, pDIB *ppDib);       

void FONTBASE_Vector_InsertHindiCache(u32 u32Offset, u16* pau16Cluster, u16 u16ClusterLen, u16 *pu16OutCode, u16 u16OutCodeLen, u32 *pau32Consumed, u32 u32Features);
void* FONTBASE_Vector_SearchHindiCache(u16 *pu16Cluster, u16 u16CluserSize);

#endif //__FEATURE_VECTOR_FONT__

#endif //__MAE_FONT_VECTOR_H__
