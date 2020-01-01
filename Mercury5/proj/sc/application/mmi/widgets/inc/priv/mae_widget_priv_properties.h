/**
* @file    mae_widget_priv_properties.h
* @version $Id: mae_widget_priv_properties.h 31865 2009-05-25 17:04:57Z sho.ding $
* @brief   This file is the collection of widget private property definitions.
*          The private properties can be used between widgets, but can NOT be used by Application.
*/
#ifndef __MAE_WIDGET_PRIV_PROPERTIES_H__
#define __MAE_WIDGET_PRIV_PROPERTIES_H__

/*=============================================================*/
// include
/*=============================================================*/
#include "mmi_mae_widget_properties.h"

/*=============================================================*/
// type and define
/*=============================================================*/

// widget private properties
enum
{
	PROP_WIDGET_PRIV_BEGIN = WDG_PROP_RESERVED_START,

	//input widget's private properties
	PROP_INPUT_WDG_CARETXYPOS = PROP_WIDGET_PRIV_BEGIN, //Get property. P2: Address of WPos_t
	PROP_INPUT_WDG_NEW_MODEL,                             //Set Property. When a new model is set, input widget will inform input controller this information.
	PROP_INPUT_WDG_CURSOR_POS_AFTER_MOVE_UP,              //Get Property. P2: New Cursor Position
	PROP_INPUT_WDG_CURSOR_POS_AFTER_MOVE_DOWN,            //Get Property. P2: New Cursor Position
	PROP_INPUT_WDG_HIDE_CURSOR,                           //hide the cursor
	PROP_INPUT_WDG_IGNORE_SELECT_WHEN_RECALCULATE_DISPLINES,//Set property. for view only mode to ignore select position in text model. (The selection range will be reset by AP.)
	PROP_INPUT_WDG_ENABLE_INVALIDATE_BY_TEXTMODEL_EVENT,
	PROP_INPUT_WDG_ENTER_CHINESE_ASSOCIATION_STATE_WITH_CHINESE_CANDIDATE,
	PROP_INPUT_WDG_GET_CURSOR_POSITION_MODIFIED_BY_TS,		//Get Property. P2 :True/False.
	PROP_INPUT_WDG_SET_FOCUS,
	PROP_INPUT_WDG_COPY_ALL,
	PROP_INPUT_WDG_DRAW_POPUP,
	PROP_INPUTCANDIDATE_WDG_GET_SPELL_NUM_PER_PAGE,
	PROP_INPUTCANDIDATE_WDG_GET_SPELL_FIRST_IDX,	
	PROP_INPUTCANDIDATE_WDG_GET_SEPLL_LIST,  //Get Property. P2: Spell List Widget pointer
	PROP_INPUTCANDIDATE_WDG_GET_CANDIDATE_LIST,  //Get Property. P2: Candidate List Widget pointer
	PROP_INPUTHELPER_WDG_LOAD_BG_IMG,
	PROP_WIDGET_PRIV_END
};






#endif //__MAE_WIDGET_PRIV_PROPERTIES_H__
/*=============================================================*/
// end of file
