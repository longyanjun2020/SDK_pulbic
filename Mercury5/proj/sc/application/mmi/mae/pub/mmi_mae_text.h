/**
 * @file mmi_mae_font.h
 *
 * @version $Id: mmi_mae_font.h 291 2009-02-27 13:08:01Z kenny.wu $
 */
#ifndef __MMI_MAE_TEXT_H__
#define __MMI_MAE_TEXT_H__
#include "mmi_mae_common_def.h"
#include "mmi_mae_interface_def.h"
#include "mmi_mae_font_forward.h"
#include "mmi_mae_text_types.h"

#define INHERIT_ITextTable(IName) \
    INHERIT_IBase(IName); \
    void     (*Clean)(ITextTable*); \
    MAERet_t (*AddLine)(ITextTable*, Text_LineData_t); \
    MAERet_t (*GetLine)(ITextTable*,u32,Text_LineData_t*); \
    MAERet_t (*OrderText)(ITextTable*,const MAE_WChar*,u32,boolean); \
    MAERet_t (*InsertText)(ITextTable*,const MAE_WChar*,u32,boolean); \
    u32      (*GetLineDispStr)(ITextTable*,u32,MAE_WChar**,u32*,boolean*,boolean); \
    u32      (*GetSize)(ITextTable*); \
    s32      (*GetLineCharPos)(ITextTable*,u32,u32,boolean,boolean); \
    u32      (*GetLineStrOffsetByXPos)(ITextTable*,u32,s32); \
    u32      (*GetLineStrWidth)(ITextTable*,u32,u32,u32); \
    MAERet_t (*ReorderLine)(ITextTable*,u32,const MAE_WChar*,u32); \
    MAERet_t (*CharIsRTL)(ITextTable*,u32,u32,boolean*); \
    MAERet_t (*GetFontInf)(ITextTable*,u32,u32,u32,FontInfo*); \
    MAERet_t (*GetLineOrderStrInputOffset)(ITextTable*,boolean,u32,u32,u32,u32*,u32*,boolean*,boolean*)
DEFINE_INTERFACE(ITextTable);

#define ITEXTTABLE_QueryInterface(pITextTable,id,pp,pOwner) \
            GET_FUNCTBL((pITextTable),ITextTable)->QueryInterface(pITextTable,id,pp,pOwner)
#define ITEXTTABLE_Clean(pITextTable) \
            GET_FUNCTBL((pITextTable),ITextTable)->Clean(pITextTable)
#define ITEXTTABLE_AddLine(pITextTable, sLineData) \
            GET_FUNCTBL((pITextTable),ITextTable)->AddLine(pITextTable, sLineData)
#define ITEXTTABLE_GetLine(pITextTable,u32Index,psLineData) \
            GET_FUNCTBL((pITextTable),ITextTable)->GetLine(pITextTable,u32Index,psLineData)

#define ITEXTTABLE_OrderText(pITextTable,pwStr,u32StrLen,bIsLangRTL) \
            GET_FUNCTBL((pITextTable),ITextTable)->OrderText(pITextTable,pwStr,u32StrLen,bIsLangRTL)

#define ITEXTTABLE_InsertText(pITextTable,pwStr,u32StrLen,bIsLangRTL) \
            GET_FUNCTBL((pITextTable),ITextTable)->InsertTex(pITextTable,pwStr,u32StrLen,bIsLangRTL)

#define ITEXTTABLE_GetLineDispStr(pITextTable,u32Index,ppwDispStr,pu32Width,pbRTL,bSkipSpaceAtLast) \
            GET_FUNCTBL((pITextTable),ITextTable)->GetLineDispStr(pITextTable,u32Index,ppwDispStr,pu32Width,pbRTL,bSkipSpaceAtLast)

#define ITEXTTABLE_GetLineOrderStrInputOffset(pITextTable,bIsRTLDisplayLang,nIndex,nInputStartOffset,nInputEndOffset,pSelectionStart,pSelectionEnd,pIsStartCharBeginPos,pIsEndCharBeginPos) \
            GET_FUNCTBL((pITextTable),ITextTable)->GetLineOrderStrInputOffset(pITextTable,bIsRTLDisplayLang,nIndex,nInputStartOffset,nInputEndOffset,pSelectionStart,pSelectionEnd,pIsStartCharBeginPos,pIsEndCharBeginPos)

/*
@brief - To get the table's size(number of items).
@param - [in]pITextTable: a pointer of text table.
@return - [out]u32: table's size.
*/
#define ITEXTTABLE_GetSize(pITextTable) \
            GET_FUNCTBL((pITextTable),ITextTable)->GetSize(pITextTable)

#define ITEXTTABLE_GetLineCharPos(pITextTable,u32Line,u32LineOffset,bIsCharBeginPos,bIsPosOnChar) \
            GET_FUNCTBL((pITextTable),ITextTable)->GetLineCharPos(pITextTable,u32Line,u32LineOffset,bIsCharBeginPos,bIsPosOnChar)

#define ITEXTTABLE_GetLineStrOffsetByXPos(pITextTable,u32Line,s32XPos) \
            GET_FUNCTBL((pITextTable),ITextTable)->GetLineStrOffsetByXPos(pITextTable,u32Line,s32XPos)

#define ITEXTTABLE_GetLineStrWidth(pITextTable,u32Line,u32Offset,u32SubStrLen) \
            GET_FUNCTBL((pITextTable),ITextTable)->GetLineStrWidth(pITextTable,u32Line,u32Offset,u32SubStrLen)

#define ITEXTTABLE_ReorderLine(pITextTable,u32Offset,pwStr,u32StrLen) \
            GET_FUNCTBL((pITextTable),ITextTable)->ReorderLine(pITextTable,u32Offset,pwStr,u32StrLen)

#define ITEXTTABLE_CharIsRTL(pITextTable,u32LineIndex,u32CharOffsetInLine,pbIsRTL) \
            GET_FUNCTBL((pITextTable),ITextTable)->CharIsRTL(pITextTable,u32LineIndex,u32CharOffsetInLine,pbIsRTL)

#define ITEXTTABLE_GetFontInf(pITextTable,u32FontCate,u32FontSize,u32FontType,pFontInf) \
            GET_FUNCTBL((pITextTable),ITextTable)->GetFontInf(pITextTable,u32FontCate,u32FontSize,u32FontType,pFontInf)

#define INHERIT_IText(IName) \
    INHERIT_IBase(IName); \
    ITextTable*       (*CreateLineTable)(IText*,const MAE_WChar*,u32,boolean,boolean, Text_MeasureInf_t*,IBase*); \
    u32               (*GetStrLineLength)(IText*,const MAE_WChar*,u32,Text_MeasureInf_t*); \
    u32               (*GetLineStrOffsetByXPos)(IText*,const MAE_WChar*,u32,boolean,s32,Text_MeasureInf_t); \
    s32               (*GetLineCharPos)(IText*,const MAE_WChar*,u32,boolean,u32,Text_MeasureInf_t); \
    u32               (*GetLineStrWidth)(IText*,const MAE_WChar*,u32,boolean,u32,u32,Text_MeasureInf_t)
DEFINE_INTERFACE(IText);

#define ITEXT_QueryInterface(pIText,id,pp,pOwner) \
            GET_FUNCTBL((pIText),IText)->QueryInterface(pIText,id,pp,pOwner)

/*
@brief - To create a display line table.
@param - [in]pIText: a pointer of text object.
@param - [in]pu16String: a ucs2 string
@param - [in]pu32StrLen: the length of ucs2 string
@param - [in]bIsRTL: the display direction of the string. (in Arabic language, the bIsRTL should be TRUE)
@param - [in]psMeasureInf: information about user split lines. split line function will dependence it to split lines.
                           If the measure information is NULL, use default meausure line function.
@param - [in]pOwner: the table's owner
@return - [out]ITextTable*: the pointer of line table.
*/
#define ITEXT_CreateLineTable(pIText,pwString,u32StrLen,bUseBidiRule, bWithoutBidi, psMeasureInf,pOwner) \
            GET_FUNCTBL((pIText),IText)->CreateLineTable(pIText,pwString,u32StrLen,bUseBidiRule,bWithoutBidi,psMeasureInf,pOwner)

/*
@brief - To get the string length that fit in a line.
@param - [in]pIText: a pointer of text object.
@param - [in]pu16String: a ucs2 string
@param - [in]pu32StrLen: the length of ucs2 string
@param - [in]bIsRTL: the display direction of the string. (in Arabic language, the bIsRTL should be TRUE)
@param - [in]s32XPos: the position in the string. If the postion is small than 0, the return index will be first
                      character. If the postion is larger than last character position, the return index will be
                      the last character in this line.
@param - [in]psMeasureInf: information about user split lines. split line function will dependence it to split lines.
                           If the measure information is NULL, use default meausure line function.
@return - [out]u32: the index of the string.
*/
#define ITEXT_GetStrLineLength(pIText,pwString,u32StrLen,psMeasureInf) \
            GET_FUNCTBL((pIText),IText)->GetStrLineLength(pIText,pwString,u32StrLen,psMeasureInf)

/*
@brief - To get index of line string by a x position.
@param - [in]pIText: a pointer of text object.
@param - [in]pu16String: a ucs2 string
@param - [in]pu32StrLen: the length of ucs2 string
@param - [in]bIsRTL: the display direction of the string. (in Arabic language, the bIsRTL should be TRUE)
@param - [in]s32XPos: the position in the string. If the postion is small than 0, the return index will be first
                      character. If the postion is larger than last character position, the return index will be
                      the last character in this line.
@param - [in]psMeasureInf: information about user split lines. split line function will dependence it to split lines.
                           If the measure information is NULL, use default meausure line function.
@return - [out]u32: the index of the string.
*/
#define ITEXT_GetLineStrOffsetByXPos(pIText,pwString,u32StrLen,bStrRTL,s32XPos,sMeasureInf) \
            GET_FUNCTBL((pIText),IText)->GetLineStrOffsetByXPos(pIText,pwString,u32StrLen,bStrRTL,s32XPos,sMeasureInf)

/*
@brief - To get a x position in string by the index. the return x position is on the right of character in
         RTL string. and the left position of character in LTR string.
@param - [in]pIText: a pointer of text object.
@param - [in]pu16String: a ucs2 string
@param - [in]pu32StrLen: the length of ucs2 string
@param - [in]bIsRTL: the display direction of the string. (in Arabic language, the bIsRTL should be TRUE)
@param - [in]u32Index: the index of character in string that want to get the position.
@param - [in]psMeasureInf: information about user split lines. split line function will dependence it to split lines.
                           If the measure information is NULL, use default meausure line function.
@return - [out]s32: x position of the character. If the return value is small than 0, it means that an incorrect result.
*/
#define ITEXT_GetLineCharPos(pIText,pwString,u32StrLen,bStrRTL,u32Offset,sMeasureInf) \
            GET_FUNCTBL((pIText),IText)->GetLineCharPos(pIText,pwString,u32StrLen,bStrRTL,u32Offset,sMeasureInf)

/*
@brief - To get a part of string's display width in line.
@param - [in]pIText: a pointer of text object.
@param - [in]pu16String: a ucs2 string
@param - [in]pu32StrLen: the length of ucs2 string
@param - [in]bIsRTL: the display direction of the string. (in Arabic language, the bIsRTL should be TRUE)
@param - [in]u32Index: the offset of the string (start to calculate width here).
@param - [in]u32SubStrLen: the length of calculating string.
@param - [in]psMeasureInf: information about user split lines. split line function will dependence it to split lines.
                           If the measure information is NULL, use default meausure line function.
@return - [out]u32: the sub string width. if the sub string larger than input string length. the return
                    width is calculated from index to last character.
*/
#define ITEXT_GetLineStrWidth(pIText,pwString,u32StrLen,bStrRTL,u32Offset,u32SubStrLen,sMeasureInf) \
            GET_FUNCTBL((pIText),IText)->GetLineStrWidth(pIText,pwString,u32StrLen,bStrRTL,u32Offset,u32SubStrLen,sMeasureInf)

MAE_Ret TextTable_New( void **ppITextTable, Text_MeasureInf_t *psMeasureInf, IBase *pOwner );

#endif /* __MMI_MAE_TEXT_H__ */
