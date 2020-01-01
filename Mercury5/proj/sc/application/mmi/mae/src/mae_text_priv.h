/**
 * \file    mae_text_priv.h
 * \brief   The document describes the private data structure used in mae_text.c
 *
 * @version
 */

#ifndef __MAE_TEXT_PRIV_H__
#define __MAE_TEXT_PRIV_H__

/******************************/
/*        INCLUDE             */
/******************************/
#include "mmi_mae_forward.h"
#include "mmi_mae_text.h"

/******************************/
/*        DEFINITION          */
/******************************/
typedef struct
{
    DECLARE_FUNCTBL(ITextTable);
    u32   nRefCnt;
    IFONT *pIFont;
    void  *pBidiHandler;
    Text_MeasureInf_t tMeasureInf;
} Mae_TextTable_t;

static void _TextTableFreeItem( void *pData, IBase *pOwner );

typedef struct
{
    DECLARE_FUNCTBL(IText);
    u32    nRefCnt;
    IFONT *pIFont;
} Mae_Text_t;

static u32 _TextTableAddRef( ITextTable *pITextTable );
static u32 _TextTableRelease( ITextTable *pITextTable );
static MAE_Ret _TextTableQueryInterface( ITextTable *pITextTable, MAE_IId nIId, void **ppObj, IBase *pOwner );
static void _TextTableClean( ITextTable *pITextTable );
static MAERet_t _TextTableAddLine( ITextTable *pITextTable, Text_LineData_t tLineData );
static MAERet_t _TextTableGetLine( ITextTable *pITextTable, u32 nIndex, Text_LineData_t *pLineData );
static MAERet_t _TextTableOrderText( ITextTable *pITextTable, const MAE_WChar *pStr, u32 nStrLen, boolean bIsLangRTL );
static MAERet_t _TextTableInsertText( ITextTable *pITextTable, const MAE_WChar *pStr, u32 nStrLen, boolean bIsLangRTL );
static u32 _TextTableGetLineDispStr( ITextTable *pITextTable, u32 nIndex, MAE_WChar **ppDispStr, u32 *pWidth, boolean *pRTL, boolean bSkipSpaceAtLast );
static u32 _TextTableGetSize( ITextTable *pITextTable );
static s32 _TextTableGetLineCharPos( ITextTable *pITextTable, u32 nLine, u32 nLineRealOffset, boolean bIsCharBeginPos, boolean bIsPosOnChar );
static u32 _TextTableGetLineStrOffsetByXPos( ITextTable *pITextTable, u32 nLine, s32 nXPos );
static u32 _TextTableGetLineStrWidth( ITextTable *pITextTable, u32 nLine, u32 nLineRealOffset, u32 nSubStrLen );

static u32 _TextAddRef( IText *pIText );
static u32 _TextRelease( IText *pIText );
static MAE_Ret _TextQueryInterface( IText *pIText, MAE_IId nIId, void **ppObj, IBase *pOwner );
static ITextTable* _TextCreateLineTable( IText *pIText, const MAE_WChar *pString, u32 nStrLen, boolean bUseBidiRule,boolean bWithoutBidi, Text_MeasureInf_t *pMeasureInf, IBase *pOwner );
static u32 _TextGetStrLineLength( IText *pIText, const MAE_WChar *pString, u32 nStrLen, Text_MeasureInf_t *pMeasureInf );
static u32 _TextGetLineStrOffsetByXPos( IText *pIText, const MAE_WChar *pString, u32 nStrLen, boolean bStrRTL, s32 nXPos, Text_MeasureInf_t tMeasureInf );
static s32 _TextGetLineCharPos( IText *pIText, const MAE_WChar *pString, u32 nStrLen, boolean bStrRTL, u32 nOffset, Text_MeasureInf_t tMeasureInf );
static u32 _TextGetLineStrWidth( IText *pIText, const MAE_WChar *pString, u32 nStrLen, boolean bStrRTL, u32 nOffset, u32 nSubStrLen, Text_MeasureInf_t tMeasureInf );
static MAERet_t _TextTableReorderLine( ITextTable *pITextTable, u32 nOffset, const MAE_WChar *pStr, u32 nStrLen );
static MAERet_t _TextTableCharIsRTL( ITextTable *pITextTable, u32 u32LineIndex, u32 u32CharOffsetInLine, boolean *pbIsRTL );
static MAERet_t _TextTableGetFontInf( ITextTable *pITextTable, u32 u32FontCate, u32 u32FontSize, u32 u32FontType, FontInfo *pFontInf );
static MAERet_t _TextTableGetLineOrderStrInputOffset(ITextTable *pITextTable, 
	boolean bIsRTLDisplayLang, 
	u32 nIndex, 
	u32 nInputStartOffset,
	u32 nInputEndOffset,
	u32 *pSelectionStart,
	u32 *pSelectionEnd,
	boolean *pIsStartCharBeginPos,
	boolean *pIsEndCharBeginPos);

/********************/
/* Private functions*/
/********************/
static boolean _TextTableReplaceLine( Mae_TextTable_t *pThis, u32 nLine, Text_LineData_t tLineData );
static u32 _TextTableGetLineOrderStr( Mae_TextTable_t *pThis, u32 nIndex, MAE_WChar **ppOrderStr, u16 **ppu16OrderSeq, boolean *pRTL );
static u32 _TextTableGetLineCharLevel( Mae_TextTable_t *pThis, u32 nIndex, u8 **ppCharLevel );
static boolean _TextTableGetStrWidth( Mae_TextTable_t *pThis, MAE_WChar *pOrderStr, u32 nStrLen, boolean bRTL, u32 *pStrWidth, boolean bSkipSpaceAtLast );
static s32 _TextOffsetToPos(  IFONT *pIFont, const MAE_WChar *pOrderStr, u32 nStrLen, u32 nStrWidth, const u16 *pSeqPos, const u8 *pCharLevel, u32 nStrOffset, Text_MeasureInf_t tMeasureInf, boolean bIsCharBeginPos, boolean bIsPosOnChar );
static u32 _TextXPosToOffset( IFONT *pIFont, const MAE_WChar *pOrderStr, u32 nStrLen, u32 nStrWidth, const u16 *pSeqPos, const u8 *pCharLevel, s32 nXPos, Text_MeasureInf_t tMeasureInf );
static u32 _TextStrWidth( IFONT *pIFont, const MAE_WChar *pOrderStr, u32 nStrLen, const u16 *pSeqPos, const u8 *pCharLevel, u32 nOffset, u32 nSubStrLen, Text_MeasureInf_t tMeasureInf );

#endif
