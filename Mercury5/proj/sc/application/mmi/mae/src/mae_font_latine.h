/**
 * \file    mae_font_thai.h
 * \brief   The document describes the interface of Thai font
 * \author  christine.tai@mstarsemi.com
 * @version $Id: mae_font_latine.h 1756 2009-09-10 14:13:56Z bill.pan $
 */
#ifndef __MAE_FONT_LATINE_H__
#define __MAE_FONT_LATINE_H__

#define IS_COMBINE_MARK(__Code) (0x0300 <= __Code && __Code <= 0x036F)
#define MAX_LATINE_COMBINE_NUM 2


u16 _FontLatineGetNextCodes(const u16*, u32, u16*, u32, u32*);


#ifdef __FEATURE_VECTOR_FONT__
u16 _FontLatineVectorGetNextCodes(const u16*, u32, u16*, u32, u32*);
#endif // __FEATURE_VECTOR_FONT__

#endif /* __MAE_FONT_LATINE_H__ */
