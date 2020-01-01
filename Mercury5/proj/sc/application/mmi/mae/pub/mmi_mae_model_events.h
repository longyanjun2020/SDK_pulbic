/**
* @file    mmi_mae_model_events.h
* @brief   This file is the collection of model event definitions.
*
* @version $Id: mmi_mae_model_events.h 291 2009-02-27 13:08:01Z kenny.wu $
*/
#ifndef __MMI_MAE_MODEL_EVENTS_H__
#define __MMI_MAE_MODEL_EVENTS_H__

/*=============================================================*/
// include
/*=============================================================*/



/*=============================================================*/
// type and define
/*=============================================================*/

#define EVT_MODEL_GROUP             0x10000
//#define EVT_MODEL_BEGIN           0x10000
//#define EVT_MODEL_END             0x1FFFF


#define EVT_DATAMDL_GRUOP           0x10100
#define EVT_INTERFACEMDL_GROUP      0x10200
#define EVT_LISTMDL_GROUP           0x10300

// reserve for future using
#define EVT_MDL_RESERVE_GROUP1           0x10400
#define EVT_MDL_RESERVE_GROUP2           0x10500
#define EVT_MDL_RESERVE_GROUP3           0x10600
#define EVT_MDL_RESERVE_GROUP4           0x10700
#define EVT_MDL_RESERVE_GROUP5           0x10800

//#define EVT_USRMDL_BEGIN      0x11800
//#define EVT_ARRAYMDL_BEGIN          0x11200 //deprecated, use EVT_LISTMDL_BEGIN
//#define EVT_VECTORMDL_BEGIN         0x11200 //deprecated, use EVT_LISTMDL_BEGIN


#define EVT_TEXTMDL_GROUP           0x11000  // 255 events group
#define EVT_MENUMDL_GROUP           0x11100  // 255 events group
#define EVT_TIMEMDL_GROUP         	0x11200  // 255 events group
#define EVT_SKMDL_GROUP             0x11300  // 255 events group
#define EVT_IMEASSTMDL_GROUP        0x11400  // 255 events group

/////////////////////////////////////////////////////
//datamodel event, from 0x1000 to 0x10FF
//interface model event, from 0x1100 to 0x11FF
//text model event, from 0x1200 to 0x12FF
//vector model event, from 0x1300 to 0x13FF
//menu model event, from 0x1400 to 0x14FF


typedef u32 ModelEvtCode_t;
enum
{
    EVT_MDL_BEGIN = EVT_MODEL_GROUP,

	//data model event
	EVT_DATAMDL_BEGIN = EVT_DATAMDL_GRUOP,
	EVT_MDL_DATA_CHANGE,
	EVT_MDL_FORMATINPUT_DATA_UPDATE,                      ///< data updated by format input widget according to user's input
	EVT_MDL_FCDATETIME_DATA_UPDATE,

	//interface model event
	EVT_INTERFACEMDL_BEGIN = EVT_INTERFACEMDL_GROUP,
	EVT_MDL_INTERFACE_CHANGE,

	//list model event
	EVT_LISTMDL_BEGIN = EVT_LISTMDL_GROUP,
	EVT_LISTMDL_CHANGE,
    EVT_LISTMDL_ITEMDATA_CHANGE,
	//vector model event
	//EVT_VECTORMDL_CHANGE = EVT_VECTORMDL_BEGIN, //deprecated, use EVT_LISTMDL_CHANGE



	//text model event
	EVT_TEXTMDL_BEGIN = EVT_TEXTMDL_GROUP,
	EVT_TEXTMDL_SELECT,
	EVT_TEXTMDL_UNDERLINE,
	EVT_TEXTMDL_CURSOR,
	EVT_TEXTMDL_TEXTCHANGE,
	EVT_TEXTMDL_TEXTADDED,//for input widget in password mode only, show the latest insert single world

#ifdef __MMI_SCRIPT_EASY_EDITOR__
	EVT_TEXTMDL_KMX_GETTEXTINFO,
	EVT_TEXTMDL_KMX_SETINITTEXT,
	EVT_TEXTMDL_KMX_SETSELECTION,
	EVT_TEXTMDL_KMX_GETSELTEXT,
	EVT_TEXTMDL_KMX_REPSELTEXT,
#endif /*__MMI_SCRIPT_EASY_EDITOR__*/
	//menu model event
	EVT_MENUMDL_BEGIN = EVT_MENUMDL_GROUP,
	EVT_MENUMDL_CHANGE,
	EVT_MENUMDL_FLAG_CHANGE,

	//check model event
	//EVT_CHECKMDL_CHECKCHANGE = EVT_CHECKMDL_BEGIN,

	//time model event
	EVT_CLOCK_BEGIN = EVT_TIMEMDL_GROUP,
	EVT_CLOCK_MINUTETICK,
	EVT_CLOCK_DATETICK,
	EVT_CLOCK_SYSTIMECHANGE,
	EVT_CLOCK_SYSTIMEZONECHANGE,

	//softkey model event
	EVT_SOFTKEYMDL_BEGIN = EVT_SKMDL_GROUP,
	EVT_SKMDL_SKCHANGE,   ///< use (MASK_LEFT_SOFTKEY_CHANGE|MASK_MIDDLE_SOFTKEY_CHANGE|MASK_RIGHT_SOFTKEY_CHANGE)+ as event data

	EVT_IMEASSTMDL_BEGIN = EVT_IMEASSTMDL_GROUP,
	EVT_IMEASSTMDL_CHANGE_WDG_LAYOUT  ///< use IMEASST_COMPNT_MSK(id0) | IMEASST_COMPNT_MSK(id1) |...
};

#endif //__MAE_MODEL_EVENTS_H__
/*=============================================================*/
// end of file
