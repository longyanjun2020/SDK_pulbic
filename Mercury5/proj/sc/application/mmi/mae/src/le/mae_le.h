#ifndef __MAE_LG_H__
#define __MAE_LG_H__

#ifdef __FEATURE_VECTOR_FONT__

#include "mae_le_types.h"
#include "mae_le_otf_types.h"

LE_ClassDefinitionType_e LE_GetGlyphClass( u16 u16GlyphId );

u16 LE_SubstProcessGlyphs( u8 *psProcess, const LE_OTF_FeatureRecord_t *pasFeatureMap, u16 u16FeatureMapSize, u32 u32FeatureTags, u16 *pau16Glyph, u16 *pu16OffsetInOutput, u16 *pu16OffsetInComposed, u16 *pau16ComposedSize );
u8* LE_CreateSubstProcess( LE_OTF_ScriptTag_e eScript, u16 *pau16Str, u16 u16StrLen, u16 u16CharIndex, u16 *pau16Consumed, u16 *pau16CharFeatures );
void LE_FreeSubstProcess( u8 *psProcess );

u8* LE_CreatePosProcess( LE_OTF_ScriptTag_e eScript, u16 *pau16Str, u16 u16StrLen, u16 u16BaseOffset, u16 u16NextOffset );
void LE_FreePosProcess( u8 *psProcess );
boolean LE_PosProcessGlyphs( u8 *psProcess, const LE_OTF_FeatureRecord_t *pasFeatureMap, u16 u16FeatureMapSize, u32 u32FeatureTags, u16 *pu16BaseOffset, s16 *ps16XOffset );

#endif //__FEATURE_VECTOR_FONT__
#endif //__MAE_LG_H__
