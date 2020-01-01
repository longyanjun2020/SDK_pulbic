/**
 * @file mae_textmodel_priv.h
 * @brief This file defines the data structure of a text model and function prototype for implementation.
 *
 * @version $Id: mae_textmodel_priv.h 35226 2009-07-06 13:59:38Z steve.lee $
 */

#ifndef __MAE_TEXTMODEL_PRIV_H__
#define __MAE_TEXTMODEL_PRIV_H__

/*=============================================================*/
// include
/*=============================================================*/
#include "mmi_mae_common_def.h"
#include "mmi_mae_modelbase.h"
#include "mmi_mae_textmodel.h"

/*=============================================================*/
// type and define
/*=============================================================*/
/* the main structure for a Text Model */

typedef struct
{
    Model_t MdlBase;
    TextInfo textInfo;
    u32 nBufByteSize; // the size (byte size) of textInfo.pwText buffer 
} TextModel_t;


/*=============================================================*/
// functions
/*=============================================================*/
u32 TextModel_Release( ITextModel *pITextModel );
MAE_Ret TextModel_QueryInterface( ITextModel *pITextModel, MAE_IId iId, void **ppObj, IBase *pOwner );

MAE_Ret TextModel_New( MAE_ClsId ClsID, void **ppObj );
void TextModelStrucInit( TextModel_t *pThis, const FUNCTBL( ITextModel ) * FtblPtr );

MAE_Ret TextModel_SetInitText( ITextModel *pITextModel, MAE_WChar *pwText, u32 nTextLen );
void TextModel_SetSelection( ITextModel *pITextModel, u32 nSelectionStart, u32 nSelectionEnd );
u32 TextModel_GetSelectText( ITextModel *pITextModel, MAE_WChar *pwText, u32 nTextLen );
MAE_Ret TextModel_ReplaceSelectText( ITextModel *pITextModel, MAE_WChar *pwText, u32 nTextLen );
void TextModel_SetUnderline( ITextModel *pITextModel, u32 nUnderlineStart, u32 nUnderlineEnd );
u32 TextModel_GetUnderlineText( ITextModel *pITextModel, MAE_WChar *pwText, u32 nTextLen );

/** 
 *    Cursor Position
 *    Underline or Selection Start, End 
 * 
 *      0   1   2   3   4   5   6   7   8   9   0   1   2   3   4   5   6   7
 *      ---------------------------------------------------------------------------
 *      | S | n | o | o | p | y |   | i | s |   | s | o |   | c | u | t | e |
 *      -------------------------------------------------------------------------
 *      ^               |       ^
 *     start = 0    Cursor=4   end = 6
 *
 *    =>Select or Underline "Snoopy"
 *    =>Selection or Underline  Length = end-start
 *    =>Selection or Underline String = pwText[0~5]  => pwText [start ~ (end-1)]
 *    =>Cursor Position = 4 means that cursor before the char pwText[4]  ('p') 
 *   
 */
void TextModel_SetCursorPos( ITextModel *pITextModel, u32 nPos );
void TextModel_GetTextInfo( ITextModel *pITextModel, TextInfo *pTextInfo );

#endif //__MAE_TEXTMODEL_PRIV_H__
/*=============================================================*/
// end of file
