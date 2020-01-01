#ifndef __MAE_LE_OTF_SUBST_H__
#define __MAE_LE_OTF_SUBST_H__

#ifdef __FEATURE_VECTOR_FONT__

#include "mae_le_util.h"
#include "mae_le_otf_types.h"

typedef struct
{
    LE_Version u32Version;
	LE_Offset ScriptListOffset;
	LE_Offset FeatureListOffset;
	LE_Offset LookupListOffset;
} LE_GSUBTable_t;

enum
{
	LE_SUBST_LOOKUP_INVALID = 0,
	LE_SUBST_LOOKUP_SINGLE = 1,
	LE_SUBST_LOOKUP_MULTIPLE = 2,
	LE_SUBST_LOOKUP_ALTERNATE = 3,
	LE_SUBST_LOOKUP_LIGATURE = 4,
	LE_SUBST_LOOKUP_CONTEXT = 5,
	LE_SUBST_LOOKUP_CHAINING_CONTEXT = 6,
	LE_SUBST_LOOKUP_EXTENSION = 7
};
typedef u16 LE_SubstitutionLookupType_e;

/*=============== SINGLE SUBSTITUTION Begin ==============*/
enum
{
    LE_SINGLE_SUBST_FORMAT_INVALID = 0,
    LE_SINGLE_SUBST_FORMAT_1 = 1,
	LE_SINGLE_SUBST_FORMAT_2 = 2
};
typedef u16 LE_SingleSubstitutionFormat_e;

typedef struct
{
    s16 s16DeltaGlyphID;
} LE_SingleSubstitutionFormat1_t;

typedef struct
{
    u16 u16GlyphCount;
    LE_GlyphId asubst[LE_ARRAY_NUM/*u16GlyphCount*/];
} LE_SingleSubstitutionFormat2_t;

typedef struct
{
    u16 u16SubstFormat;
    LE_Offset CoverageOffset;
    union
    {
        LE_SingleSubstitutionFormat1_t sData1;
    	LE_SingleSubstitutionFormat2_t sData2;
    } usData;
} LE_SingleSubstitution_t;
/*=============== SINGLE SUBSTITUTION End ==============*/

/*=============== MULTIPLE SUBSTITUTION Begin ==============*/
typedef struct
{
    u16 u16GlyphCount;
    LE_GlyphId aSubst[LE_ARRAY_NUM/*u16GlyphCount*/];
} LE_SequenceTable_t;

typedef struct
{
    u16 u16SubstFormat;
	LE_Offset CoverageOffset;
    u16 u16SeqCount;
    LE_Offset aSeqTableOffset[LE_ARRAY_NUM/*u16SeqCount*/];
} LE_MultipleSubstitution_t;
/*=============== MULTIPLE SUBSTITUTION End ==============*/

/*=============== ALTERNATE SUBSTITUTION Begin ==============*/
typedef struct
{
    u16 u16GlyphCount;
    LE_GlyphId aAlternate[LE_ARRAY_NUM/*u16GlyphCount*/];
} LE_AlternateSetTable_t;

typedef struct
{
    u16 u16SubstFormat;
	LE_Offset CoverageOffset;
    u16 u16AltSetCount;
    LE_Offset aAltSetTableOffset[LE_ARRAY_NUM/*u16AltSetCount*/];
} LE_AlternateSubstitution_t;
/*=============== ALTERNATE SUBSTITUTION End ==============*/

/*=============== LIGATURE SUBSTITUTION Begin ==============*/
typedef struct
{
    LE_GlyphId LigGlyph;
    u16 u16CompCount;
    LE_GlyphId aComponent[LE_ARRAY_NUM/*u16CompCount*/];
} LE_LigatureTable_t;

typedef struct
{
    u16 u16LigCount;
    LE_Offset aLigTableOffset[LE_ARRAY_NUM/*u16LigCount*/];
} LE_LigatureSetTable_t;

typedef struct
{
    u16 u16SubstFormat;
	LE_Offset CoverageOffset;
    u16 u16LigSetCount;
    LE_Offset aLigSetTableOffset[LE_ARRAY_NUM];
} LE_LigatureSubstitution_t;
/*=============== LIGATURE SUBSTITUTION End ==============*/

typedef struct
{
    LE_ProcessSubstHeader_t sHeader;
	LE_ScriptTag_e eScript;
    const u8 *pGSUB;
	const u8 *pClassDefTable;
} LE_GSUBProcess_t;

boolean LeProcessSubstLookupTable( LE_GSUBProcess_t *psProcess, const u8 *pLookupTable, u16 u16SubtableIndex, u16 u16Position );
const u8* LeSubstGetScriptListTable( const u8 *pSubstTable );
const u8* LeSubstGetFeatureListTable( const u8 *pSubstTable );
const u8* LeSubstGetLookupListTable( const u8 *pSubstTable );

#endif //__FEATURE_VECTOR_FONT__
#endif //__MAE_LE_OTF_SUBST_H__
