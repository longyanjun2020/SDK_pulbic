#ifndef __MAE_LG_OTF_COMMON_H__
#define __MAE_LG_OTF_COMMON_H__

#ifdef __FEATURE_VECTOR_FONT__

#include "mae_le_types.h"
#include "mae_le_util.h"

typedef struct
{
    LE_GlyphId FirstGlyph;
    LE_GlyphId LastGlyph;
    u16 u16RangeValue;
} LE_GlyphRangeRecord_t;
#define LE_GlyphRangeRecord_SIZE (sizeof(LE_GlyphId) + sizeof(LE_GlyphId) + sizeof(u16))

/*=============== Language & Script List Table Begin ==============*/
typedef struct
{
    LE_Tag Tag;
    LE_Offset Offset;
} LE_LangSysRecord_t;

typedef struct
{
    LE_Offset LookupOrderOffset;
    u16 u16ReqFeatureIndex;
    u16 u16FeatureCount;
    u16 au16FeatureIndex[LE_ARRAY_NUM];
} LE_LangSysTable_t;

typedef struct
{
    LE_Offset DefaultLangSysTableOffset;
    u16 u16LangSysCount;
    LE_LangSysRecord_t asLangSysRecord[LE_ARRAY_NUM];
} LE_ScriptTable_t;

typedef struct
{
    LE_Tag Tag;
    LE_Offset Offset;
} LE_ScriptRecord_t;
#define LE_ScriptRecord_Size (sizeof(LE_Tag) + sizeof(LE_Offset))

typedef struct
{
    u16 u16ScriptCount;
    LE_ScriptRecord_t asScriptRecord[LE_ARRAY_NUM];
} LE_ScriptListTable_t;
/*=============== Language & Script List Table End ==============*/

/*=============== Feature List Table Begin ==============*/
typedef struct
{
    LE_Offset FeatureParamsOffset;
    u16 u16LookupCount;
    u16 au16LookupListIndex[LE_ARRAY_NUM];
} LE_FeatureTable_t;

typedef struct
{
    LE_Tag FeatureTag;
    LE_Offset FeatureTableOffset;
} LE_FeatureRecord_t;
#define LE_FeatureRecord_Size (sizeof(LE_Tag) + sizeof(LE_Offset))

typedef struct
{
    u16 u16FeatureCount;
    LE_FeatureRecord_t asFeatureRecord[LE_ARRAY_NUM];
} LE_FeatureListTable_t;
/*=============== Feature List Table End ==============*/

/*=============== Lookup Table Begin ==============*/
enum
{
    LE_LOOKUP_FLAG_RIGHTTOLEFT  		= 0x0001,
    LE_LOOKUP_FLAG_IGNORE_BASEGLYPHS    = 0x0002,
    LE_LOOKUP_FLAG_IGNORE_LIGATURES     = 0x0004,
    LE_LOOKUP_FLAG_IGNORE_MARKS         = 0x0008,
    LE_LOOKUP_FLAG_USE_MARKFILTERINGSET = 0x0010,
    LE_LOOKUP_FLAG_RESERVED 			= 0x00E0,
    LE_LOOKUP_FLAG_MARKATTACHMENTTYPE   = 0xFF00,
};
typedef u16 LE_LookupFlag_e;

typedef struct
{
    u16 u16SubtableFormat;
    LE_Offset CoverageTableOffset;
} LE_LookupSubtable_t;

typedef struct
{
    u16 u16LookupType;
	u16 u16LookupFlag;
	u16 u16SubtableCount;
    LE_Offset aSubtableOffset[LE_ARRAY_NUM];
} LE_LookupTable_t;

typedef struct
{
    u16 u16LookupCount;
    LE_Offset aLookupTableOffset[LE_ARRAY_NUM];
} LE_LookupListTable_t;
/*=============== Lookup Table End ==============*/

/*=============== Value Record Begin ==============*/
enum
{
    LE_VALUE_X_PLACEMENT        = 0x0001,
    LE_VALUE_Y_PLACEMENT        = 0x0002,
    LE_VALUE_X_ADVANCE          = 0x0004,
    LE_VALUE_Y_ADVANCE          = 0x0008,
    LE_VALUE_X_PLACEMENT_DEVICE = 0x0010,
    LE_VALUE_Y_PLACEMENT_DEVICE = 0x0020,
    LE_VALUE_X_ADVANCE_DEVICE   = 0x0040,
    LE_VALUE_Y_ADVANCE_DEVICE   = 0x0080,
    LE_VALUE_RESERVED           = 0xFF00,
    LE_VALUE_ANY_DEVICE         = LE_VALUE_X_PLACEMENT_DEVICE + LE_VALUE_Y_PLACEMENT_DEVICE + LE_VALUE_X_ADVANCE_DEVICE + LE_VALUE_Y_ADVANCE_DEVICE
};
typedef u16 LE_ValueFormat_e;

typedef struct
{
    s16 as16Value[LE_ARRAY_NUM];
} LE_ValueRecord_t;	
/*=============== Value Record End ==============*/

/*=============== Device Table Begin ==============*/
typedef struct
{
    u16 u16StartSize;
    u16 u16EndSize;
    u16 u16DeltaFormat;
    u16 u16DeltaValues[LE_ARRAY_NUM];
} LE_DeviceTable_t;
/*=============== Device Table End ==============*/

/*=============== COVERAGE Table Begin ==============*/
enum
{
    LE_COVERAGE_TABLE_FORMAT_INVALID = 0,
    LE_COVERAGE_TABLE_FORMAT_1 = 1,
	LE_COVERAGE_TABLE_FORMAT_2 = 2
};
typedef u16 LE_CoverageTableFormat_e;

typedef struct
{
    u16 u16GlyphCount;
    u16 au16Glyph[LE_ARRAY_NUM];
} LE_CoverageTableFormat1_t;

typedef struct
{
    u16 u16RangeCount;
    LE_GlyphRangeRecord_t asRangeRecord[LE_ARRAY_NUM];
} LE_CoverageTableFormat2_t;

typedef struct
{
    u16 u16CoverageFormat;
    union
    {
        LE_CoverageTableFormat1_t sData1;
    	LE_CoverageTableFormat2_t sData2;
    } usData;
} LE_CoverageTable_t;
/*=============== COVERAGE Table End ==============*/

/*=============== CLASS DEFINITION Table Begin ==============*/
enum
{
    LE_CLASS_DEFINITION_FORMAT_INVALID = 0,
    LE_CLASS_DEFINITION_FORMAT_1 = 1,
	LE_CLASS_DEFINITION_FORMAT_2 = 2
};
typedef u16 LE_ClassDefinitionFormat_e;

typedef struct
{
    u16 u16StartGlyph;
    u16 u16GlyphCount;
    u16 au16ClassValue[LE_ARRAY_NUM];
} LE_ClassDefinitionFormat1_t;

typedef struct
{
    u16 u16ClassRangeCount;
    LE_GlyphRangeRecord_t asClassRangeRecord[LE_ARRAY_NUM];
} LE_ClassDefinitionFormat2_t;

typedef struct
{
    u16 u16ClassFormat;
    union
    {
        LE_ClassDefinitionFormat1_t sData1;
    	LE_ClassDefinitionFormat2_t sData2;
    } usData;
} LE_ClassDefinition_t;
/*=============== CLASS DEFINITION Table End ==============*/

/*=============== Anchor Table Begin ==============*/
enum
{
    LE_ANCHOR_TABLE_FORMAT_INVALID = 0,
    LE_ANCHOR_TABLE_FORMAT_1 = 1,
	LE_ANCHOR_TABLE_FORMAT_2 = 2,
	LE_ANCHOR_TABLE_FORMAT_3 = 3
};
typedef u16 LE_AnchorTableFormat_e;

typedef struct
{
    s16 s16XCoordinate;
    s16 s16YCoordinate;
} LE_AnchorTableFormat1_t;

typedef struct
{
    s16 s16XCoordinate;
    s16 s16YCoordinate;
    u16 u16AnchorPoint;
} LE_AnchorTableFormat2_t;

typedef struct
{
    s16 s16XCoordinate;
    s16 s16YCoordinate;
    LE_Offset XDeviceTableOffset;
    LE_Offset YDeviceTableOffset;
} LE_AnchorTableFormat3_t;

typedef struct
{
    u16 u16AnchorFormat;
    union
    {
        LE_AnchorTableFormat1_t sData1;
        LE_AnchorTableFormat2_t sData2;
    	LE_AnchorTableFormat3_t sData3;
    } usData;
} LE_AnchorTable_t;
/*=============== Anchor Table End ==============*/

/*=============== Mark Array Begin ==============*/
typedef struct
{
    u16 u16MarkClass;
    LE_Offset MarkAnchorTableOffset;
} LE_MarkRecord_t;
#define LE_MarkRecord_Size (sizeof(u16) + sizeof(LE_Offset))

typedef struct
{
    u16 u16MarkCount;
    LE_MarkRecord_t asMarkRecord[LE_ARRAY_NUM];
} LE_MarkArray_t;
/*=============== Mark Array End ==============*/

/*=============== CONTEXT Begin ==============*/
enum
{
    LE_CONTEXT_FORMAT_INVALID = 0,
    LE_CONTEXT_FORMAT_1 = 1,
	LE_CONTEXT_FORMAT_2 = 2,
	LE_CONTEXT_FORMAT_3 = 3
};
typedef u16 LE_ContextFormat_e;

typedef struct
{
    u16 u16SeqIndex;
	u16 u16LookupListIndex;
} LE_LookupRecord_t;
#define LE_LookupRecord_Size (sizeof(u16) + sizeof(u16))

typedef struct
{
    u16 u16GlyphCount;
    u16 u16Count;
    LE_GlyphId aInputGlyph[LE_ARRAY_NUM/*u16Count - 1*/];
    /*LE_LookupRecord_t SubstLookupRecord[u16Count];*/
} LE_RuleTable_t;

typedef struct
{
    u16 u16RuleCount;
    LE_Offset aRuleTableOffset[LE_ARRAY_NUM];
} LE_RuleSetTable_t;

typedef struct
{
    u16 u16RuleSetCount;
    LE_Offset aRuleSetTableOffset[LE_ARRAY_NUM];
} LE_ContextFormat1_t;

typedef struct
{
    u16 u16GlyphCount;
    u16 u16Count;
    u16 au16Class[LE_ARRAY_NUM];
} LE_ClassRuleTable_t;

typedef struct
{
    u16 u16ClassRuleCount;
    LE_Offset aClassRuleTableOffset[LE_ARRAY_NUM];
} LE_ClassSetTable_t;

typedef struct
{
    LE_Offset ClassDefTableOffset;
    u16 u16ClassSetCount;
    LE_Offset aClassSetTableOffset[LE_ARRAY_NUM];
} LE_ContextFormat2_t;

typedef struct
{
    u16 u16GlyphCount;
    u16 u16Count;
    LE_Offset aCoverageTableOffset[LE_ARRAY_NUM];
} LE_ContextFormat3_t;

typedef union
{
    u16 u16Format;
	LE_Offset CoverageOffset;
    union
    {
        LE_ContextFormat1_t sData1;
    	LE_ContextFormat2_t sData2;
		LE_ContextFormat3_t sData3;
    } usData;
} LE_Context_t;
/*=============== CONTEXT End ==============*/

/*=============== CHAINING CONTEXT Begin ==============*/
enum
{
    LE_CHAININGCONTEXT_FORMAT_INVALID = 0,
    LE_CHAININGCONTEXT_FORMAT_1 = 1,
	LE_CHAININGCONTEXT_FORMAT_2 = 2,
	LE_CHAININGCONTEXT_FORMAT_3 = 3
};
typedef u16 LE_ChainingContextFormat_e;

typedef struct
{
    u16 u16BacktrackGlyphCount;
    LE_GlyphId aBacktrackGlyph[LE_ARRAY_NUM/*u16BacktrackGlyphCount*/];
	/*u16 InputGlyphCount;*/
	/*LE_GlyphId 	Input[InputGlyphCount - 1];*/
	/* u16 LookaheadGlyphCount;*/
	/*LE_GlyphId 	LookAhead[LookaheadGlyphCount];*/
	/* u16 SubstCount;*/
	/*LE_LookupRecord_t SubstLookupRecord[SubstCount];*/
} LE_ChainRuleTable_t;

typedef struct
{
    u16 u16ChainRuleCount;
    u16 au16ChainRuleTableOffset[LE_ARRAY_NUM];
} LE_ChainRuleSetTable_t;

typedef struct
{
    u16 u16ChainRuleSetCount;
    LE_Offset aChainRuleSetTableOffset[LE_ARRAY_NUM];
} LE_ChainingContextFormat1_t;

typedef struct
{
    u16 u16BacktrackGlyphCount;
    u16 au16BacktrackClass[LE_ARRAY_NUM];
} LE_ChainClassRuleTable_t;

typedef struct
{
    u16 u16ChainClassRuleCount;
    LE_Offset aChainClassRuleTableOffset[LE_ARRAY_NUM];
} LE_ChainClassSetTable_t;

typedef struct
{
    LE_Offset BacktrackClassDefTableOffset;
    LE_Offset InputClassDefTableOffset;
    LE_Offset LookaheadClassDefTableOffset;
    u16 u16ChainClassSetCount;
    LE_Offset aChainClassSetTableOffset[LE_ARRAY_NUM];
} LE_ChainingContextFormat2_t;

typedef struct
{
    u16 u16BacktrackGlyphCount;
    LE_Offset aBacktrackCoverageTableOffset[LE_ARRAY_NUM];
} LE_ChainingContextFormat3_t;

typedef union
{
	u16 u16SubstFormat;
	LE_Offset CoverageOffset;
    union
    {
        LE_ChainingContextFormat1_t sData1;
    	LE_ChainingContextFormat1_t sData2;
		LE_ChainingContextFormat1_t sData3;
    } usData;
} LE_ChainingContext_t;
/*=============== CHAINING CONTEXT End ==============*/

/*=============== EXTENSION Begin ==============*/
typedef struct
{
    u16 u16SubstFormat;
    u16 u16ExtensionLookupType;
    LE_Offset ExtensionOffset;
} LE_Extension_t;
/*=============== EXTENSION End ==============*/

s32 LeGetGlyphCoverage( const u8 *psCover, u16 u16GlyphId );
s32 LeGetGlyphClass( const u8 *pDefTable, u16 u16GlyphId );
boolean LeHasGlyphClass( const u8 *pDefTable, s32 s32GlyphClass );
s16 LeValueGetFieldCount( LE_ValueFormat_e eValueFormat );
s16 LeValueGetSize( LE_ValueFormat_e eValueFormat );
s16 LeValueGetFieldIndex( LE_ValueFormat_e eValueFormat, s16 s16Field );
u16 LeValueGetFieldValue( const u8 *pValueRecord,LE_ValueFormat_e eValueFormat, s16 s16Field );
s16 LeDeviceTableGetAdjustment( const u8 *pDeviceTable, u16 u16PixelsPerEM );
boolean LeGetAnchor( const u8 *pAnchorTable, u16 u16GlyphId, LE_Points_t *pAnchor, LE_FontInstanceInf_t *pFontInstanceInf );
s32 LeMarkArrayGetMarkClass(const u8 *pMarks, u16 u16GlyphId, s32 s32CoverageIndex, LE_Points_t *pAnchor, LE_FontInstanceInf_t *pFontInstance);
u16 LeContextTableGetLookupRecord( const u8 *psContext, const u32 *paGlyphId, u16 u16GlyphLen, u16 u16Position, const u8 **ppasRecords );
u16 LeChainingContextTableGetLookupRecord( const u8 *psChainingContext, const u32 *paGlyphId, u16 u16GlyphLen, u16 u16Position, const u8 **ppasRecords );
const u8* LeGetFeatureTable( const u8 *pFeatureList, u32 u32FeatureTag, u16 *pu16LookupCount );
boolean LeFeatureTableGetLookupIndexs( const u8 *pFeature, u16 *pau16Index, u16 u16ArraySize );
const u8* LeLookupListTableGetLookupTable( const u8 *pLookupList, u16 u16Index, u16 *pu16SubtableCount );
const u8* LeLookupTableGetLookupSubtable( const u8 *pLookup, u16 u16Index );
const u8* LeFindScript( const u8 *pScriptList, LE_ScriptTag_e eScriptTag );

u16 LeGlyphStrGetNext( const u32 *paGlyphId, u16 u16GlyphLen, u16 u16Position, u16 u16NextCount, u16 *pu16NextPosition, const u8 *pDefTable, LE_LookupFlag_e eLookupFlags, boolean bIgnoreFFFE );

#endif //__FEATURE_VECTOR_FONT__

#endif //__MAE_LG_OTF_COMMON_H__
