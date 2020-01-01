/**
 * @file mmi_mae_text_forward.h
 *
 * @version $Id: mmi_mae_text_forward.h $
 */
#ifndef __MMI_MAE_TEXT_FORWARD_H__
#define __MMI_MAE_TEXT_FORWARD_H__
#include "mmi_mae_common_def.h"

/*
@brief - a register measure line function type.
@param - [in]pu16String: a ucs2 string
@param - [in]pu32StrLen: the length of ucs2 string
@param - [in]u32Width: a max width of a line can be.
@param - [in]u32FontSize: the font size of text.
@param - [in]u32FontType: the font type of text.
@param - [in]bDiffDirChangeLine: Need to change line when meet a mixed string on a line.
@param - [out]pu32FitLen: a line string length that can fit in a line.
@param - [out]pu32FitWidth: a line string width that can fit in a line.
@param - [in]u32Data: a user assign data that hopt handle in this function.
*/
typedef boolean (*PfnTEXT_MEASURELINE_FUNC_PTR) ( const MAE_WChar *pu16Text, \
                                            u32 u32TextLen, \
                                            u32 u32Width, \
                                            u32 u32FontCat, \
                                            u32 u32FontSize, \
                                            u32 u32FontType, \
                                            boolean bDiffDirChangeLine, \
                                            u32 *pu32FitLen, \
                                            u32 u32Data);

/*
@brief - structure of text font type.
*/
typedef struct Text_FontInf_t_ Text_FontInf_t;

/*
@brief - structure for regist user measure line information.
*/
typedef struct Text_MeasureInf_t_ Text_MeasureInf_t;

/*
@brief - structure of table line's data.
*/
typedef struct Text_LineData_t_ Text_LineData_t;

#endif /* __MMI_MAE_TEXT_FORWARD_H__ */
