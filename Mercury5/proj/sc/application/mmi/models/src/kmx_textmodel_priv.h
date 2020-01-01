/*
 * Copyright (C) 2010 Beijing Komoxo Inc.
 * All rights reserved.
 * @author ghd
 * @version  1
 */

#ifdef __MMI_SCRIPT_EASY_EDITOR__

#ifndef __KMX_TEXTMODEL_PRIV_H__
#define __KMX_TEXTMODEL_PRIV_H__

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

/*=============================================================*/
// functions
/*=============================================================*/

u32 kmx_TextModel_Release( ITextModel *pITextModel );
MAE_Ret kmx_TextModel_QueryInterface( ITextModel *pITextModel, MAE_IId iId, void **ppObj, IBase *pOwner );

MAE_Ret kmx_TextModel_New( MAE_ClsId ClsID, void **ppObj );
void kmx_TextModelStrucInit( KMX_TextModel_t *pThis, const FUNCTBL( ITextModel ) * FtblPtr );

MAE_Ret kmx_TextModel_SetInitText( ITextModel *pITextModel, MAE_WChar *pwText, u32 nTextLen );
void kmx_TextModel_SetSelection( ITextModel *pITextModel, u32 nSelectionStart, u32 nSelectionEnd );
u32 kmx_TextModel_GetSelectText( ITextModel *pITextModel, MAE_WChar *pwText, u32 nTextLen );
MAE_Ret kmx_TextModel_ReplaceSelectText( ITextModel *pITextModel, MAE_WChar *pwText, u32 nTextLen );
void kmx_TextModel_SetUnderline( ITextModel *pITextModel, u32 nUnderlineStart, u32 nUnderlineEnd );
u32 kmx_TextModel_GetUnderlineText( ITextModel *pITextModel, MAE_WChar *pwText, u32 nTextLen );


void kmx_TextModel_SetCursorPos( ITextModel *pITextModel, u32 nPos );
void kmx_TextModel_GetTextInfo( ITextModel *pITextModel, TextInfo *pTextInfo );


#endif //__KMX_TEXTMODEL_PRIV_H__

#endif/*__MMI_SCRIPT_EASY_EDITOR__*/
/*=============================================================*/
// end of file
