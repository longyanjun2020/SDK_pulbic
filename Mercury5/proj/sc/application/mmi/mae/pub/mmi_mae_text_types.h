/**
 * @file mmi_mae_font_types.h
 *
 * @version $Id: mmi_mae_text_types.h $
 */
#ifndef __MMI_MAE_TEXT_TYPES_H__
#define __MMI_MAE_TEXT_TYPES_H__
#include "mmi_mae_common_def.h"
#include "mmi_mae_text_forward.h"

/*
@brief - structure of text font type.
*/
struct Text_FontInf_t_
{
	u32 nFontCate;
    u32 nFontSize;  /* The display font size of text */
    u32 nFontType;  /* The display font type of text */
};

/*
@brief - structure for regist user measure line information.
*/
struct Text_MeasureInf_t_
{
    Text_FontInf_t tFontData;               /* structure about font information */
    u32             nWidth;                /* the max width of a line */
    boolean         bDiffDirChangeLine;      /* decide to change line when a string mixed different
                                                direction character in a line */
    PfnTEXT_MEASURELINE_FUNC_PTR pfnMeasureLine; /* a register measure line function, assign to null is
                                                means to use bidi default measure line rule */
    u32 nFunctionData;                     /* a data for register measure line function handle */
};

/*
@brief - structure of table line's data.
*/
struct Text_LineData_t_
{
    boolean bRTL;                  /* is a right-to-left direction string */
    u32     nOffset;             /* the offset(begin index) of this string in original full text */
    u32     nLength;             /* the length of string */
};

#endif /* __MMI_MAE_TEXT_TYPES_H__ */
