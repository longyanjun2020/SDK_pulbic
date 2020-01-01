/**
* @file    mmi_wdg_dateicon_priv.h
* @version $Id: mmi_wdg_dateicon_priv.h 15067 2008-10-14 18:35:34Z lih.wang $
*
* @brief   
*
*/

#ifndef __MMI_WDG_DATEICON_PRIV_H__
#define __MMI_WDG_DATEICON_PRIV_H__

/*=============================================================*/
// include
/*=============================================================*/
#include "mae_widgetbase.h"
#include "mmi_mae_widget.h"
#include "mmi_mae_config.h"
#include "mmi_mae_clock_types.h"
#include "mmi_mae_resource.h"

/*=============================================================*/
// type and define
/*=============================================================*/
#define PI                       3.14159265
#define ANGLE_ARC   (PI / 180)

/*
* Lists the items of text to display
*/
enum {
	DATEICON_WDG_ITEM_TIME = 0,
	DATEICON_WDG_ITEM_MONTH = 0,
	DATEICON_WDG_ITEM_DAY,
	DATEICON_WDG_ITEM_NUM
};

typedef struct {
    RGBColor_t TextColor;		///< rgb text color.
    RGBColor_t OutlineColor;    ///< rgb text outline color.
} TxtColor_t;

typedef struct {
    FontType_t     FontType;	///< font type
    FontCategory_t FontCate;	///< font category
	u32            FontSize;    ///< font size
} FontStyle_t;


/**
* Defines the text color and font style that used in DateIcon-widget.
* Including two items for Month and Day.
*/
typedef struct {
	TxtColor_t    aTextColor[DATEICON_WDG_ITEM_NUM]; ///< color for month string and day string
	FontStyle_t   aFontStyle[DATEICON_WDG_ITEM_NUM]; ///< font style for month string and day string.
} _DateIconTextInfo_t;

enum {
	DATETIME_FORMAT_DATE,
	DATETIME_FORMAT_TIME,
	DATETIME_FORMAT_CLOCK,
};
/**
* The main structure for implementation of DateIcon widget.
*/
typedef struct {
	WidgetBaseEx_t      WdgBase;			///< Using WidgetBaseEx_t as base structure.
	ModelListener_t     MdlLsn;				///< Model listener for listening the data model change.
	IClock              *pIClock;			///< A clock to get current time
	ClockListener_t     ClockLsn;           ///< Clock listener for date change
    IImage             *pBgImg;			///< A IBitmap object for background icon to display.
	_DateIconTextInfo_t stTxtInfo;			///< Text color, font category, font type for all string we want to display.
	MAE_TimeFormat_e	eTimeFormat;
	u32                 nMonthHeight: 8;   ///< The height of displaying month area in pixels.
	u32                 nBGWidth: 8;   ///< The width of displaying area in pixels.
	u32                 nBGHeight: 8;   ///< The height of displaying area in pixels.
	u32                 AutoUpdate: 1;      ///<
	u32					bDisplayData: 1;
	u32					nDateIconFormat: 4;			// False for TimeIconFormat

	IBitmap             *pIconBmp[3];

	IWidget			    *pIImgIconMonthWidget;
	IWidget			    *pIImgIconDayWidget[2];

	IWidget			    *pIconHourHandImageWdg;
	IWidget			    *pIconMinHandImageWdg;
	s32                 nHrHandPosX;
	s32                 nHrHandPosY;
	s32                 nMinHandPosX;
	s32                 nMinHandPosY;
	boolean				bResLoaded;
} WdgDateIcon_t;


/*=============================================================*/
// functions
/*=============================================================*/
/*=============================================================*/
// New function and Event handler
/*=============================================================*/
MAE_Ret DateIconWidget_New(MAE_ClsId ClsID, void **ppObj);
boolean WdgDateIconDefHandleEvent(IWidget *pIWidget, MAE_EventId evt, u32 P1, u32 P2);


/*=============================================================*/
// Non-interface functions
/*=============================================================*/
static MAE_Ret _WdgDateIconConstructor(WdgDateIcon_t*);

void _WdgDateIconDestructor(WdgDateIcon_t *pThis);

void _WdgDateIconGetPreferredSize(IWidget *pIWidget,   ///< An IWidget object instance
										 WidgetSize_t *pSize  ///< A pointer of widget size to return preferred size
										 );

MAERet_t _WdgDateIconSetModel(IWidget *pIWidget,
									  IModel *pIModel,
									  IBase* pOwner
									  );

void _WdgDateIconDraw(IWidget *pIWidget, IDispCanvas *pIDispCanvas, s32 x, s32 y);

static void _WdgDateIconMdlLsn(void *pUsrData, ModelEvent_t *pMdlEvent);

static boolean _WdgDateIconSetProperty(WdgDateIcon_t *pThis, u32 P1, u32 P2);

static boolean _WdgDateIconGetProperty(WdgDateIcon_t *pThis, u32 P1, u32 P2);

static void _WdgDateIconDataModelFree(void *pData, IBase *pOwner);

static void _WdgDateIconClockLsn(void *pUsrData, MAEClkItemId_t id, void *pItemData);

static MAE_DateTime_t* _WdgDateIconGetDateFromModel(WdgDateIcon_t *pThis);

MAE_WChar* _WdgDateIconGetMonthString(WdgDateIcon_t *pThis, u8 Month);

void _WdgDateIconGetItemRect(WdgDateIcon_t *pThis, u32 ItemId, Rect_t *pItemRect);

void _WdgDateIconDrawItemString(WdgDateIcon_t *pThis,
								IDisplay *pIDisplay,
                                Rect_t *pDispRect,
                                Rect_t *pItemRect,
                                MAE_WChar *pDisplayStr,
								u32 ItemId,
								boolean b3D
                                );

static MAE_Ret _WdgDateIconSetDateToImage(WdgDateIcon_t* pThis, MAE_DateTime_t *dtToday);

static MAE_Ret _WdgDateIconDrawDateWidget(WdgDateIcon_t* pThis, IDispCanvas *pIDispCanvas, s32 x, s32 y);

static void _WdgDateIconSetAClockHandPos(WdgDateIcon_t* pThis, MAE_DateTime_t *pDateTime);

static MAE_Ret _WdgDateIconDrawAClockHand(WdgDateIcon_t* pThis, IDispCanvas *pIDispCanvas, s32 x, s32 y);

static MAE_Ret _WdgDateIconLoadImg(WdgDateIcon_t *pThis, IWidget *pImgWdg, u32 uBgImageId, ImgDecAngle_t eRotateAngle);

#endif //__MMI_WDG_DATEICON_PRIV_H__
/*=============================================================*/
// end of file
