#ifndef __MAE_LG_OTF_H__
#define __MAE_LG_OTF_H__

#ifdef __FEATURE_VECTOR_FONT__

#include "mae_le_types.h"
#include "mae_le_otf_types.h"
#include "mae_le_util.h"
#include "mae_le_otf_subst.h"
#include "mae_le_otf_pos.h"

LE_GSUBProcess_t* LeCreateGsubProcess( LE_OTF_ScriptTag_e eScript, const u8 *pGSUB, const u8 *pGDEF );
void LeFreeGsubProcess( u8 *psProcess );
u16 LeGsubProcessGlyphs( LE_GSUBProcess_t *psProcess, const LE_OTF_FeatureRecord_t *pasFeatureMap, u16 u16FeatureMapSize, u32 u32FeatureTags );
LE_GPOSProcess_t* LeCreateGposProcess( LE_OTF_ScriptTag_e eScript, const u8 *pGPOS, const u8 *pGDEF, LE_FontInstanceInf_t *psFontInf );
void LeFreeGposProcess( u8 *psProcess );
boolean LeGposProcessGlyphs( LE_GPOSProcess_t *psProcess, const LE_OTF_FeatureRecord_t *pasFeatureMap, u16 u16FeatureMapSize, u32 u32FeatureTags );

#endif //__FEATURE_VECTOR_FONT__
#endif //__MAE_LG_OTF_H__
