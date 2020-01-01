
#ifndef __MAE_FONT_PL_H__
#define __MAE_FONT_PL_H__



typedef struct Map2VectorFont_t_
{
	u32 nCategory;
	u32 nFontSize;
}Map2VectorFont_t;


void MaePl_MapToVectorFontInit(void);
u32 MaePl_GetMapToVectorSize(void);
u32 MaePl_GetFTCacheSize(void);
u32 MaePl_GetFTBufferSize(void);
u32 MaePl_GetFTCacheMinSize(void);
u32 MaePl_GetFTBufferMinSize(void);
Map2VectorFont_t *MaePl_GetMapToVector(void);
u32 MaePl_FontBaseVectorTransferToBitmapFontCate( u32 u32FontCate, u32 u32FontSize );

#endif //__MAE_FONT_PL_H__

