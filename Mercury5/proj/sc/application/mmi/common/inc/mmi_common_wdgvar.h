#ifndef __MMI_COMMON_WDGVAR_H__
#define __MMI_COMMON_WDGVAR_H__
#include "mmi_wdg_headers.h"

#define WndID     0
typedef struct
{
    u32 nImg;
	u32 nTxt;
}TitleVar_t;

//ThmTxtVar_t Txt={{TRUE,X,Y},{W,H},syle,data};
typedef struct
{
	Pos_t tPos;
	WidgetSize_t tSize;
	u32 nStyle;
	u32 nData;
}ThmTxtVar_t;

typedef struct
{
	Pos_t tPos;
	WidgetSize_t tSize;
	WdgMenuType_e eStyle;
}MenuVar_t;

//BtnVar_t Btn={{TRUE,X,Y},{W,H},{nStrID,nUnPressedID,nPressedID}};
typedef struct
{
	Pos_t tPos;
	WidgetSize_t tSize;
	WdgButtonDataID_t tData;
}BtnVar_t;

//ImgVar_t Img={{TRUE,X,Y},{W,H},{bAutoFit,bUpscale,nImageID,pScaleRotate},Data};


typedef struct
{
	Pos_t tPos;
	WidgetSize_t tSize;
}AbsContainerVar_t;

//TxtVar_t Txt={{TRUE,X,Y},{W,H},syle,data};
typedef struct
{
	Pos_t tPos;
	WidgetSize_t tSize;
	TextStyle_t tStyle;
	u32 nData;
}TxtVar_t;

typedef struct
{
	Pos_t tPos;
	WidgetSize_t tSize;
	WdgLayoutStyle_t tStyle;
}PropContainerVar_t;

/*
typedef struct
{
	Pos_t tPos;
	WidgetSize_t tSize;
}InputVar_t;
*/

typedef struct
{
	//要不要有id
	Pos_t tPos;
	WidgetSize_t tSize;
	u32 nCfg;
}ScrollVar_t;

typedef struct
{
	Pos_t tPos;
	WidgetSize_t tSize;
	u32 nStyle;
}NumericMenuVar_t;

typedef struct
{
	Pos_t tPos;
	WidgetSize_t tSize;
}MflContainerVar_t;

typedef struct
{
	Pos_t tPos;
	WidgetSize_t tSize;
}OSDVar_t;

typedef struct
{
	Pos_t tPos;
	WidgetSize_t tSize;
}AnimatedMenuVar_t;

typedef struct
{
	Pos_t tPos;
	WidgetSize_t tSize;
	u32 nStyle;
	WdgDoubleItemDBText_t tData;
}TxtLine2InfoVar_t;

typedef struct
{
	Pos_t tPos;
	WidgetSize_t tSize;
	u32 nStyle;
	WdgDoubleItemDBText_t tData;
}Line2InfoPickVar_t;

typedef struct
{
	Pos_t tPos;
	WidgetSize_t tSize;
	u32 nStyle;
}PopuSelectVar_t;

typedef struct
{
	Pos_t tPos;
	WidgetSize_t tSize;
	u32 nStyle;
	WdgImageConfigData_t tCfg;
	u32 nData;
}ThmImgVar_t;



typedef struct
{
	Pos_t tPos;
	WidgetSize_t tSize;
	u32 nData;
}BmpVar_t;

typedef struct
{
	Pos_t tPos;
	WidgetSize_t tSize;
	u32 nStyle;
	WdgDoubleItemDBText_t tData;
}TxtInputVar_t;

typedef struct
{
	Pos_t tPos;
	WidgetSize_t tSize;
	WdgDoubleItemDBText_t tData;
	DoubleItemStyle_e eStyle;
}TxtDoubleVar_t;

typedef struct
{
	Pos_t tPos;
	WidgetSize_t tSize;
	u32 nStyle;
	WdgDoubleItemTIT_t tData;
}ITTxtVar_t;

typedef struct
{
	Pos_t tPos;
	WidgetSize_t tSize;
	WdgTabInfo_t tData;
}TabVar_t;

typedef struct
{
	Pos_t tPos;
	WidgetSize_t tSize;
	u32 nStyle;
}GridVar_t;

typedef struct
{
	Pos_t tPos;
	WidgetSize_t tSize;
	u32 nStyle;
}ImgGridVar_t;

typedef struct
{
	Pos_t tPos;
	WidgetSize_t tSize;
	u32 nStyle;
}HorzMenuVar_t;

typedef struct
{
	Pos_t tPos;
	WidgetSize_t tSize;
}Transition_t;

typedef struct
{
	Pos_t tPos;
	WidgetSize_t tSize;
	u32 nStyle;
	WdgDoubleItemTIT_t tData;
}ITInputVar_t;

typedef struct
{
	Pos_t tPos;
	WidgetSize_t tSize;
	u32 nStyle;
	WdgDoubleItemTextTime_t tData;
}DateTxtVar_t;

typedef struct
{
	Pos_t tPos;
	WidgetSize_t tSize;
	u32 nStyle;
	WdgDoubleItemTextTime_t tData;
}TimeTxtVar_t;

typedef struct
{
	Pos_t tPos;
	WidgetSize_t tSize;
	u32 nCfg;
}VolumeVar_t;

typedef struct
{
	Pos_t tPos;
	WidgetSize_t tSize;
}DummyVar_t;

typedef struct
{
	Pos_t tPos;
	WidgetSize_t tSize;
	TimerFormatType_e eCfg;
	MAE_DateTime_t tData;
}TimeFormatVar_t;

typedef struct
{
	Pos_t tPos;
	WidgetSize_t tSize;
	u32 nStyle;
}VertVar_t;



typedef struct
{
	Pos_t tPos;
	WidgetSize_t tSize;
	u32 nStyle;
}HorzListVar_t;

typedef struct
{
	Pos_t tPos;
	WidgetSize_t tSize;
	u32 nStyle;  //ITI_STYLE_IMAGETEXT
	WdgITIStyleITInfo_t tData;
}ImgTxtVar_t;

typedef struct
{
	Pos_t tPos;
	WidgetSize_t tSize;
	u32 nStyle;
	IndicatorData_t tData;
}IndicatorVar_t;

typedef struct
{
	Pos_t tPos;
	WidgetSize_t tSize;
	u32 nStyle;
}OptionVar_t;

//softkey commonCreate
typedef struct
{
	Pos_t tPos;
	WidgetSize_t tSize;
}SoftkeyVar_t;

typedef struct
{
	Pos_t tPos;
	WidgetSize_t tSize;
	u32 nStyle;
	MAE_DateTime_t tCfg;
	MAE_DateTime_t tData;
}CountDownVar_t;

typedef struct
{
	Pos_t tPos;
	WidgetSize_t tSize;
}HandWriteVar_t;

typedef struct
{
	Pos_t tPos;
	WidgetSize_t tSize;
}IMEVar_t;

typedef struct
{
	Pos_t tPos;
	WidgetSize_t tSize;
	u32 nStyle; //WDG_LIST_TYPE_ONELINE
}OnelineVar_t;

typedef struct
{
	Pos_t tPos;
	WidgetSize_t tSize;
	WdgScrlIndCfgData_t tCfg;
}ScrollIndVar_t;

typedef struct
{
	Pos_t tPos;
	WidgetSize_t tSize;
}ShorCutVar_t;

typedef struct
{
	Pos_t tPos;
	WidgetSize_t tSize;
}SlideVar_t;

typedef struct
{
	Pos_t tPos;
	WidgetSize_t tSize;
}ViewContainerVar_t;

typedef struct
{
	Pos_t tPos;
	WidgetSize_t tSize;
}PullDownVar_t;

typedef struct
{
	Pos_t tPos;
	WidgetSize_t tSize;
}TimeVar_t;

typedef struct
{
	Pos_t tPos;
	WidgetSize_t tSize;
	CommonPickStyle_e   ePick_style;
}ComPickVar_t;

typedef struct
{
	Pos_t tPos;
	WidgetSize_t tSize;
	DoubleItemStyle_e   eDoubleItemStyle;
}DubItemVar_t;

typedef struct
{
	Pos_t tPos;
	WidgetSize_t tSize;
	u32 nStyle;
	WdgImageConfigData_t tCfg;
	u32 nData;
}ImgVar_t;


// ***************************************************************************************************
typedef struct
{
	Pos_t tPos;
	WidgetSize_t tSize;
	u32   nStyle;
}CommonVar_t;

typedef struct
{
	Pos_t tPos;
	WidgetSize_t tSize;
	WdgInputConfigData_t tCfg;
}InputVar_t;

typedef struct
{
	Pos_t tPos;
	WidgetSize_t tSize;
	u16 nCfgStep;
	u32 nCfgAlignment;
}ViewportVar_t;

typedef struct
{
	Pos_t tPos;
	WidgetSize_t tSize;
	ImageStyle_t nStyle;
	WdgImageConfigData_t tCfg;
}ImageVar_t;


typedef struct
{
	Pos_t tPos;
	WidgetSize_t tSize;
	WdgSwitchIconAttrId_t tCfg;
}SwIconVar_t;

typedef struct
{
	Pos_t tPos;
	WidgetSize_t tSize;
    WdgProgressCfgData_t tCfg;
}Progress_t;

typedef struct
{
	Pos_t tPos;
	WidgetSize_t tSize;
    FadeoutLevel_t tCfg;
}FadeVar_t;

typedef struct
{
	Pos_t tPos;
	WidgetSize_t tSize;
	MAE_DateTime_t tDateTime;
}FcDateVar_t;

typedef struct
{
	Pos_t tPos;
	WidgetSize_t tSize;
	MAE_DateTime_t tDateValue;
}DateVar_t;

typedef struct
{
	Pos_t tPos;
	WidgetSize_t tSize;
	FCTimeStyle_t eStyle;
	MAE_DateTime_t tDateTime;
}FcTimeVar_t;

typedef struct
{
	WdgTabInfo_t    *pTabInfo;
    u32             nItemNum;
}TabDataVar_t;

typedef struct
{
	Pos_t tPos;
	WidgetSize_t tSize;
	u32 nIPValue;
}IPVar_t;

typedef struct
{
	Pos_t tPos;
	WidgetSize_t tSize;
	boolean bDirectToogle;
}PickVar_t;

typedef struct
{
    u32 nFocusIndex;
    WdgCommonPickInfo_t tTitleDispData;
}CommPickVar_t;

//WndSetAllSoftkey
typedef struct
{
    u32 nLeftSKID;
    u32 nMiddleSKID;
    u32 nRightSKID;
}AllSoftkeyVar_t;

//WndSetSoftkey
typedef struct
{
    u32 nSkType;
    u32 nSKID;
}SetSoftkeyVar_t;


enum {
    CHILD_FIRST_ORDER = 0,
    CHILD_SECOND_ORDER,
    CHILD_THIRD_ORDER
};


#endif //__MMI_COMMON_WDGVAR_H__
