
#ifdef __MMI_SCRIPT_EASY__

#ifndef __MMI_MAE_FONT_KMX_H__
#define __MMI_MAE_FONT_KMX_H__

#include "mmi_mae_interface_def.h"
#include "mmi_mae_bitmap_base.h"
#include "mmi_mae_font_base.h"
#include "scripteasy.h"


int kmx_mstar_fontsize_se(u32 fontCate, u32 fontFize);
secolor kmx_mstar_color_se(RGBColor_t RGBColor);
RGBColor_t kmx_secolor_mstar(secolor se_color);

MAE_Ret kmx_scripteasy_init(void);
void kmx_scripteasy_release(void);

void secallback_draw_pixel(void *device_data, int x, int y, secolor se_color);
void secallback_draw_bitmap(void* device_data,
								   int x_dst,
								   int y_dst,
								   const SeBitmap* se_bitmap,
								   int x_src,
								   int y_src,
								   int width,
								   int height,
								   secolor se_color);
void secallback_draw_rect(void* device_data, const SeRectangle* rect, secolor se_color);
void secallback_revert_rect(void *device_data, const SeRectangle* rect);

MAERet_t KmxFont_DrawText(SeDeviceContext *dc, BitmapBase_t *pDst, u32 fontCate, u32 fontSize, u32 fontType, int x, int y, 
						  const MAE_WChar *pcText, int nChars, RGBColor_t fg, RGBColor_t bg, const Rect_t *prcClip);

MAE_Ret KmxFont_MeasureText(SeDeviceContext *dc, u32 fontCate, u32 fontSize, u32 fontType, const MAE_WChar *pcText, u32 nChars, 
							u32 nMaxWidth, u32 *pnFits, u32 *pnPixels);

MAE_Ret KmxFont_GetInfo(SeDeviceContext *dc, u32 fontCate, u32 fontSize, u32 fontType, FontInfo_t *pinfo);
MAE_Ret KmxFont_CreateGlyphDib(SeDeviceContext *kmxdc, u32 FontCate, u32 nFontSize, u32 Type, u16 Code, pDIB *ppDib);

#endif //#ifndef __MMI_MAE_FONT_KMX_H__

#endif  //#ifdef __MMI_SCRIPT_EASY__

