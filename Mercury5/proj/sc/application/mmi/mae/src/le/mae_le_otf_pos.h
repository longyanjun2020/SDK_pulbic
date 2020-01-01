#ifndef __MAE_LE_OTF_POS_H__
#define __MAE_LE_OTF_POS_H__

#ifdef __FEATURE_VECTOR_FONT__

#include "mae_le_otf_common.h"

typedef enum
{
	LE_POS_LOOKUP_INVALID                     = 0,
	LE_POS_LOOKUP_SINGLE_ADJUSTMENT           = 1,
	LE_POS_LOOKUP_PAIR_ADJUSTMENT             = 2,
	LE_POS_LOOKUP_CURSIVE_ATTACHMENT          = 3,
	LE_POS_LOOKUP_MARKTOBASE_ATTACHMENT       = 4,
	LE_POS_LOOKUP_MARKTOLIGATURE_ATTACHEMENT  = 5,
	LE_POS_LOOKUP_MARKTOMARK_ATTACHEMENT      = 6,
	LE_POS_LOOKUP_CONTEXT					  = 7,
	LE_POS_LOOKUP_CHAINED_CONTEXT             = 8, 
	LE_POS_LOOKUP_EXTENSION                   = 9
} LE_PositionLookupType_e;

typedef struct
{
    LE_Version u32Version;
	LE_Offset ScriptListOffset;
	LE_Offset FeatureListOffset;
	LE_Offset LookupListOffset;
} LE_GPOSTable_t;

/*=============== SINGLE ADJUSTMENT POSITION Begin ==============*/
enum
{
    LE_SINGLE_ADJ_POS_FORMAT_INVALID = 0,
    LE_SINGLE_ADJ_POS_FORMAT_1 = 1,
	LE_SINGLE_ADJ_POS_FORMAT_2 = 2
};
typedef u16 LE_SingleAdjPositionFormat_e;

typedef struct
{
    u16 u16ValueFormat;
    LE_ValueRecord_t sValueRecord;
} LE_SingleAdjPositionFormat1_t;

typedef struct
{
    u16 u16ValueFormat;
    u16 u16ValueCount;
    LE_ValueRecord_t asValueRecord[LE_ARRAY_NUM];
} LE_SingleAdjPositionFormat2_t;

typedef struct
{
    u16 u16PosFormat;
	LE_Offset CoverageOffset;
    union
    {
        LE_SingleAdjPositionFormat1_t sData1;
    	LE_SingleAdjPositionFormat2_t sData2;
    } usData;
} LE_SingleAdjPosition_t;
/*=============== SINGLE ADJUSTMENT POSITION End ==============*/

/*=============== PARI ADJUSTMENT POSITION Begin ==============*/
enum
{
    LE_PAIR_ADJ_POS_FORMAT_INVALID = 0,
    LE_PAIR_ADJ_POS_FORMAT_1 = 1,
	LE_PAIR_ADJ_POS_FORMAT_2 = 2
};
typedef u16 LE_PairAdjPositionFormat_e;

typedef struct
{
    LE_GlyphId SecondGlyph;
    LE_ValueRecord_t sValueRecord1;
	/* LE_ValueRecord_t sValueRecord2 -- ignore here */
} LE_PairValueRecord_t;

typedef struct
{
    u16 u16PairValueCount;
    LE_PairValueRecord_t asPairValueRecord[LE_ARRAY_NUM];
} LE_PairSetTable_t;

typedef struct
{
    u16 u16ValueFormat1;
    u16 u16ValueFormat2;
    u16 u16PairSetCount;
    LE_Offset aPairSetTableOffset[LE_ARRAY_NUM];
} LE_PairAdjPositionFormat1_t;

typedef struct
{
    LE_ValueRecord_t sValueRecord1;
	/* LE_ValueRecord_t sValueRecord2 -- ignore here */
} LE_Class2Record;

typedef struct
{
    LE_Class2Record asClass2Record[LE_ARRAY_NUM];
} LE_Class1Record;

typedef struct
{
    u16 u16ValueFormat1;
    u16 u16ValueFormat2;
    LE_Offset ClassDef1Offset;
    LE_Offset ClassDef2Offset;
    u16 u16Class1Count;
    u16 u16Class2Count;
    LE_Class1Record asClass1Record[LE_ARRAY_NUM];
} LE_PairAdjPositionFormat2_t;

typedef struct
{
    u16 u16PosFormat;
	LE_Offset CoverageOffset;
    union
    {
        LE_PairAdjPositionFormat1_t sData1;
    	LE_PairAdjPositionFormat2_t sData2;
    } usData;
} LE_PairAdjPosition_t;
/*=============== PAIR ADJUSTMENT POSITION End ==============*/

/*=============== CURSIVE ATTACHMENT POSITION Begin ==============*/
typedef struct
{
    LE_Offset EntryAnchor;
    LE_Offset ExitAnchor;
} LE_EntryExitRecord_t;
#define LE_EntryExitRecord_Size (sizeof(LE_Offset) + sizeof(LE_Offset))

typedef struct
{
    u16 u16PosFormat;
	LE_Offset CoverageOffset;
    u16 u16EntryExitCount;
    LE_EntryExitRecord_t asEntryExitRecords[LE_ARRAY_NUM];
} LE_CursiveAttPosition_t;
/*=============== CURSIVE ATTACHMENT  POSITION End ==============*/

typedef struct
{
    LE_Offset BaseCoverageTableOffset;
    u16 u16ClassCount;
    LE_Offset MarkArrayOffset;
    LE_Offset BaseArrayOffset;
} LE_AttachmentPositionTable_t;

/*=============== MARKTOBASE ATTACHMENT POSITION Begin ==============*/
typedef struct
{
    LE_Offset aBaseAnchorTableOffset[LE_ARRAY_NUM];
} LE_BaseRecord_t;

typedef struct
{
    s16 s16BaseRecordCount;
    LE_BaseRecord_t asBaseRecord[LE_ARRAY_NUM];
} LE_BaseArray_t;

typedef struct
{
    u16 u16PosFormat;
	LE_Offset MarkCoverageOffset;
	LE_Offset BaseCoverageOffset;
	u16 u16ClassCount;
	LE_Offset MarkArrayOffset;
	LE_Offset BaseArrayOffset;
} LE_MarkToBaseAttPositionTable_t;
/*=============== MARKTOBASE ATTACHMENT  POSITION End ==============*/

/*=============== MARKTOLIGATURE ATTACHMENT POSITION Begin ==============*/
typedef struct
{
    LE_Offset as32LigatureAnchorTableOffset[LE_ARRAY_NUM];
} LE_ComponentRecord_t;

typedef struct
{
    u16 u16ComponentCount;
    LE_ComponentRecord_t asComponentRecord[LE_ARRAY_NUM];
} LE_LigatureAttachTable_t;

typedef struct
{
    u16 u16LigatureCount;
    LE_Offset aLigatureAttachTableOffset[LE_ARRAY_NUM];
} LE_LigatureArray_t;

typedef struct
{
    u16 u16PosFormat;
	LE_Offset MarkCoverageOffset;
	LE_Offset LigatureCoverageOffset;
	u16 u16ClassCount;
	LE_Offset MarkArrayOffset;
	LE_Offset LigatureArrayOffset;
} LE_MarkToLigatureAttPositionTable_t;
/*=============== MARKTOLIGATURE ATTACHMENT  POSITION End ==============*/

/*=============== MARKTOMARK ATTACHMENT POSITION Begin ==============*/
typedef struct
{
    LE_Offset aMark2AnchorTableOffset[LE_ARRAY_NUM];
} LE_Mark2Record_t;

typedef struct
{
    u16 u16Mark2RecordCount;
    LE_Mark2Record_t asMark2Record[LE_ARRAY_NUM];
} LE_Mark2Array_t;

typedef struct
{
    u16 u16PosFormat;
	LE_Offset Mark1CoverageOffset;
	LE_Offset Mark2CoverageOffset;
	u16 u16ClassCount;
	LE_Offset Mark1ArrayOffset;
	LE_Offset Mark2ArrayOffset;
} LE_MarkToMarkAttPositionTable_t;
/*=============== MARKTOMARK ATTACHMENT  POSITION End ==============*/

typedef struct
{
    s32 s32XPlacementAdjustment;
    s32 s32YPlacementAdjustment;
    s32 s32XAdvanceAdjustment;
    s32 s32YAdvanceAdjustment;
	LE_Points_t sEntryAnchor;
	LE_Points_t sExitAnchor;
} LE_PosInf_t;

typedef struct
{
    LE_ProcessPosHeader_t sHeader;
	LE_ScriptTag_e eScript;
    const u8 *pGPOS;
	const u8 *pClassDefTable;
	LE_FontInstanceInf_t sFontInstanceInf;
	LE_PosInf_t sPosInf;
	LE_PosInf_t sNextPosInf;
} LE_GPOSProcess_t;

boolean LeProcessPosLookupTable( LE_GPOSProcess_t *psProcess, const u8 *pLookupTable, u16 u16SubtableIndex, u16 u16Position );
const u8* LePosGetScriptListTable( const u8 *pPosTable );
const u8* LePosGetFeatureListTable( const u8 *pPosTable );
const u8* LePosGetLookupListTable( const u8 *pPosTable );

#endif //__FEATURE_VECTOR_FONT__
#endif //__MAE_LE_OTF_POS_H__
