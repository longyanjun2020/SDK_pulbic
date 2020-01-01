#ifndef __MAE_LE_OTF_DEF_H__
#define __MAE_LE_OTF_DEF_H__

#ifdef __FEATURE_VECTOR_FONT__

#include "mae_le_otf_common.h"

typedef struct
{
    u32 u32Version;
    s32 s32GlyphClassDefOffset;
    s32 s32AttachDefOffset;
    s32 s32LigCaretDefOffset;
    s32 s32MarkAttachClassDefOffset;
} LE_GDEFTable_t;

/*=============== Attachment Definition Begin ==============*/
typedef struct
{
    s32 s32CoverageTableOffset;
    u16 u16GlyphCount;
    s32 as32AttachPointTableOffset[LE_ARRAY_NUM];
} LE_AttachmentDefinition_t;

typedef struct
{
    u16 u16PointCount;
    u16 au16PointIndex[LE_ARRAY_NUM];
} LE_AttachmentPointTable_t;
/*=============== Attachment Definition End ==============*/

/*=============== Ligature caret Definition Begin ==============*/
typedef struct
{
    s32 s32CoverageTableOffset;
    u16 u16LigGlyphCount;
    s32 as32LigGlyphTableOffset[LE_ARRAY_NUM];
} LE_LigatureCaretDefinition_t;

typedef struct
{
    u16 u16CaretCount;
    s32 as32CaretValueTableOffset[LE_ARRAY_NUM];
} LE_LigatureGlyphTable_t;

typedef enum
{
    LE_CARETVALUE_TABLE_FORMAT_INVALID = 0,
    LE_CARETVALUE_TABLE_FORMAT_1 = 1,
	LE_CARETVALUE_TABLE_FORMAT_2 = 2,
	LE_CARETVALUE_TABLE_FORMAT_3 = 3
} LE_CaretValueTableFormat_e;

typedef struct
{
    u16 u16Coordinate;
} LE_CaretValueTableFormat1_t;

typedef struct
{
    u16 u16CaretValuePoint;
} LE_CaretValueTableFormat2_t;

typedef struct
{
    u16 u16Coordinate;
    s32 s32DeviceTableOffset;
} LE_CaretValueTableFormat3_t;

typedef struct
{
    u16 u16CaretValueTableFormat;
    union
    {
        LE_CaretValueTableFormat1_t sData1;
    	LE_CaretValueTableFormat2_t sData2;
		LE_CaretValueTableFormat3_t sData3;
    } usData;
} LE_CaretValueTable_t;
/*=============== Caret Value Definition End ==============*/

const u8* LeGDEFGetClassDefinitionTable( const u8 *pDefTable );
const u8* LeGDEFGetAttachmentDefinitionTable( const u8 *pDefTable );
const u8* LeGDEFGetLigatureCaretDefinitionTable( const u8 *pDefTable );
const u8* LeGDEFGetMarkAttachClassDefinitionTable( const u8 *pDefTable );

#endif //__FEATURE_VECTOR_FONT__
#endif //__MAE_LE_OTF_DEF_H__
