/**
 *  @file mae_font_hebrew.h
 *  @brief This file takes care of Hebrew strings.

 *  @version $Id: mae_font_hebrew.h ken.zhou  $
 */

#ifndef __MAE_FONT_HEBREW_H__
#define __MAE_FONT_HEBREW_H__

#ifdef __HEBREW_FONT__
u16 TextHebrewGetNextCodes(const u16 *pInText, u32 InLen, u16 *pOutText, u32 OutLen, u32 *paConsumed);
#ifdef __FEATURE_VECTOR_FONT__
u16 TextHebrewVectorGetNextCodes(const u16 *pInText, u32 InLen, u16 *pOutText, u32 OutLen, u32 *paConsumed);
#endif //__FEATURE_VECTOR_FONT__
#endif

#endif
