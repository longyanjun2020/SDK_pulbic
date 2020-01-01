/*****************************************************************************************
* @mapapp_view.h
*
* Comment:
*
* @version:0.0.2  @ 2009.12.01
*****************************************************************************************/
#ifndef __mapapp_view__H
#define __mapapp_view__H

#include "mmi_mapapp_view_id.h"

#define     MAP_OPTIONMENU_SETTINGS_CALL            0
#define     MAP_OPTIONMENU_SETTINGS_IP_CALL         1
#define     MAP_OPTIONMENU_SETTINGS_VIEW            2
#define     MAP_OPTIONMENU_SETTINGS_LBS             3
#define     MAP_OPTIONMENU_SETTINGS_POI_NEARBY      4
#define     MAP_OPTIONMENU_SETTINGS_SEARCH_POI      5
#define     MAP_OPTIONMENU_SETTINGS_SEARCH_LIST     6
#define     MAP_OPTIONMENU_SETTINGS_HISTORY         7
#define     MAP_OPTIONMENU_SETTINGS_MY_FAVORITE     8
#define     MAP_OPTIONMENU_SETTINGS_ADDTOFAVORITE   9
#define     MAP_OPTIONMENU_SETTINGS_SEND            10
#define     MAP_OPTIONMENU_SETTINGS_WHERE_AM_I      11
#define     MAP_OPTIONMENU_SETTINGS_SETTINGS        12
#define     MAP_OPTIONMENU_SETTINGS_ABOUT           13

#define     MAP_OPTIONMENU_OPTION_VIEWONMAP     0
#define     MAP_OPTIONMENU_OPTION_EDIT          1
#define     MAP_OPTIONMENU_OPTION_MARK          2
#define     MAP_OPTIONMENU_OPTION_MARKALL       3
#define     MAP_OPTIONMENU_OPTION_UNMARK        4
#define     MAP_OPTIONMENU_OPTION_UNMARKALL     5
#define     MAP_OPTIONMENU_OPTION_DELETE        6
#define     MAP_OPTIONMENU_OPTION_POI           7
#define     MAP_OPTIONMENU_OPTION_MYLOCATION    8

#define     MAP_OPTIONMENU_MAPVIEW_CALL          0
#define     MAP_OPTIONMENU_MAPVIEW_IP_CALL       1
#define     MAP_OPTIONMENU_MAPVIEW_VIEW          2
#define     MAP_OPTIONMENU_MAPVIEW_LBS           3
#define     MAP_OPTIONMENU_MAPVIEW_POI_NEARBY    4
#define     MAP_OPTIONMENU_MAPVIEW_SEARCH_POI    5
#define     MAP_OPTIONMENU_MAPVIEW_HISTORY       6
#define     MAP_OPTIONMENU_MAPVIEW_MY_FAVORITE   7
#define     MAP_OPTIONMENU_MAPVIEW_ADDTOFAVORITE 8
#define     MAP_OPTIONMENU_MAPVIEW_SEND          9
#define     MAP_OPTIONMENU_MAPVIEW_WHERE_AM_I    10
#define     MAP_OPTIONMENU_MAPVIEW_SETTINGS      11


typedef struct
{
    IWidget *pWdgContainer;
    IWidget *pWdgBitmap;
    IWidget *pWdgImgTitleBar;
    IWidget *pWdgTextTitleBar;
    IWidget *pWdgImgCenterFocus;
    IWidget *pWdgImgZoom;
    IWidget *pWdgImgZoomStatus;
    IWidget *pWdgZoomIn;
    IWidget *pWdgZoomOut;
    IWidget *pWdgSettings;
    IWidget *pWdgImgNotice;
    IWidget *pWdgFocusMode;
    IWidget *pWdgPrevMode;
    IWidget *pWdgNextMode;
    IWidget *pWdgLeftArrow;
    IWidget *pWdgRightArrow;
}MapMapViewWdgList_t;

MAE_Ret MapCreateMapView(HWIN hWin, MapMapViewWdgList_t *pWdgList);

//*******************************************************************//
enum //ID_MAPAPP_DATALIST_VIEW_enum
{
    eMAP_DATALIST_MENU = APP_WDG_START,
}; //ID_MAPAPP_DATALIST_VIEW_enum

typedef struct
{
    IWidget *pWdgMenu;
}MapDataListViewWdgList_t;

MAE_Ret MapCreateDataListView(HWIN hWin, MapDataListViewWdgList_t *pWdgList);

//*******************************************************************//
enum //ID_MAPAPP_MULTI_FIELD_INPUT_VIEW_enum
{
    eMAP_MULTI_FIELD_INPUT_MENU=APP_WDG_START,
}; //ID_MAPAPP_MULTI_FIELD_INPUT_VIEW_enum
typedef struct
{
    IWidget *pWdgMenu;
}MapMultiFieldInputViewWdgList_t;

MAE_Ret MapCreateMultiFieldInputView(HWIN hWin, MapMultiFieldInputViewWdgList_t *pWdgList);

//*******************************************************************//
enum //ID_MAPAPP_IMAGE_THUMB_VIEW_enum
{
    eMAP_THUMB_MENU=APP_WDG_START,
}; //ID_MAPAPP_IMAGE_THUMB_VIEW_enum
typedef struct ID_MAPAPP_IMAGE_THUMB_VIEW_WdgList_tag
{
    IWidget *pWdgMenu;
}MapImageThumbViewWdgList_t;

MAE_Ret MapCreateImageThumbView(HWIN hWin, MapImageThumbViewWdgList_t *pWdgList);

//*******************************************************************//
#endif //__mapapp_view__H
