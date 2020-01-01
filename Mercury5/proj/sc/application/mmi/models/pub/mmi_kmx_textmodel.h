/*
 * Copyright (C) 2010 Beijing Komoxo Inc.
 * All rights reserved.
 * @author ghd
 * @version  1
 */

#ifdef __MMI_SCRIPT_EASY_EDITOR__

#ifndef __KMX_TEXTMODEL_H__
#define __KMX_TEXTMODEL_H__

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
    ModelEvent_t MEvtBase;      ///< model event base structure
	TextInfo textInfo;
} KMX_TextModelEvent_t;

typedef struct
{
	MAE_WChar *pwText; 
	u32 nTextLen;
} KMX_TEXT_PARAM;

typedef struct
{
	u32 nSelectionStart;
	u32 nSelectionEnd;
} KMX_SELECTION_PARAM;

typedef struct
{
	u32 nUnderlineStart;
	u32 nUnderlineEnd;
} KMX_UNDERLINE_PARAM;

typedef struct
{
	u32 nCursorPos;
} KMX_CURSOR_POS_PARAM;

typedef struct
{
    Model_t MdlBase;
	TextInfo textInfo;
	u32 nBufByteSize; // the size (byte size) of textInfo.pwText buffer 

} KMX_TextModel_t;


/*=============================================================*/
// functions
/*=============================================================*/

#endif //__KMX_TEXTMODEL_H__

#endif/*__MMI_SCRIPT_EASY_EDITOR__*/
/*=============================================================*/
// end of file
