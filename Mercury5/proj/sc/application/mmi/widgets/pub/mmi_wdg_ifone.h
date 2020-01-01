/**
 * @file    mmi_wdg_ifone.h
 * @version $Id: mmi_wdg_ifone.h  2009-09-01 ken.zhou $
 * @brief   This file defines the interface of IFONEWIDGET
 *
 * @CLS ID : CLSID_IFONEWIDGET
 */
#ifndef MMI_WDG_IFONE_H
#define MMI_WDG_IFONE_H


/*=============================================================*/
// include
/*=============================================================*/
#include "mmi_mae_propcontainer.h"
#include "mmi_mae_image.h"
#include "mmi_wdg_common_interface.h"
#include "mmi_mae_vectormodel.h"

enum
{
    MENUTYPE_APPLET,
    MENUTYPE_FOLDER,
    MENUTYPE_URL,
    MENUTYPE_JAVA,
    MENUTYPE_CALENDAR,    
    MENUTYPE_DIALER,
    MENUTYPE_MESSAGE,    
};
typedef u8 IfonIconType_e;

#define IFONE_WIDGET_MAXSTRING_LEN 20
#define IFONE_WIDGET_FILENAME_LEN 256
/*=============================================================*/
// type and define
/*=============================================================*/
typedef enum
{
	IFONE_WIDGET_DISPLAY_NORMAL = 0,
	IFONE_WIDGET_DISPLAY_FOCUS,
	IFONE_WIDGET_DISPLAY_DRAG,
	IFONE_WIDGET_DISPLAY_ANIM,
	IFONE_WIDGET_DISPLAY_TATOL,
}IFONEWDG_DESPLAY_STYLE_e;

typedef enum
{
	IFONEWDG_ANIMSTYLE_NONE,
	IFONEWDG_ANIMSTYLE_CHANGEANGLE,	// change image angle
	IFONEWDG_ANIMSTYLE_MOVE,	// move image position
}IFONEWDG_ANIMSTYLE_e;

typedef enum
{
	Direction_Left,
	Direction_Right,
	Direction_Up,
	Direction_Down,
	Direction_Center,
}IFONEWDG_ANIM_DIRECTION_e;

typedef struct
{
    IfonIconType_e eMenuItemType;   //menu type, ex:applet, folder, java, URL...
    u32 nFolderID;  //Menu in folder;
    boolean bUsePredefImage:1;
    boolean bUsePredefText:1;
    union
    {
        u32 nImageID;
        MAE_WChar pImageUrl[IFONE_WIDGET_FILENAME_LEN];
    }uMenuImage;
    union
    {
        u32 nTextID;
        MAE_WChar aString[IFONE_WIDGET_MAXSTRING_LEN+1];
    }uMenuString;
    union
    {
        struct
        {
        	u16	nClsId;		//class id
        	u32 nParam;		//start param
        }uAPLunchID;
        MAE_WChar strBrowserUrl[IFONE_WIDGET_FILENAME_LEN];
    }uFuncID;
}IfoneMenuItemData_t, *IfoneMenuItemData_p;

typedef struct
{
    IWidget *	pWdg;
    IfonIconType_e eMenuItemType;
} IFoneMenuItemSimpleData_t;

typedef union
{
    u32 color;
    struct
    {
        u8 Color_B;
        u8 Color_G;
        u8 Color_R;
        u8 nAlpha;
    }RGBColor;
}uColor_RGB8888;

__INLINE void WdgIfoneSetAnimationEx(IWidget* pIWidget, boolean bAnimtion, IFONEWDG_ANIMSTYLE_e eAnimstyle)
{
    WdgCommonHandleEvent(pIWidget, PROP_IFONE_WDG_SETANIMTION, (u32)bAnimtion, (u32)eAnimstyle);
}

__INLINE void WdgIfoneSetAnimation(IWidget* pIWidget, boolean bAnimtion)
{
    WdgIfoneSetAnimationEx(pIWidget, bAnimtion, IFONEWDG_ANIMSTYLE_CHANGEANGLE);
}

MAE_Ret WdgIfoneSetWidgetData(IWidget*pIWidget, IfoneMenuItemData_t *pWidgetData);

__INLINE MAE_Ret WdgIfoneGetWidgetData(IWidget*pIWidget, IfoneMenuItemData_t **ppWidgetData)
{
    return WdgCommonGetProperty(pIWidget, PROP_IFONE_WDG_WIDGETDATA, (u32*)ppWidgetData);
}


__INLINE boolean WdgIfoneAddChildWidget(IWidget*pIWidget, IWidget*pIChildWidget)
{
    boolean bAddSuccess = TRUE;
    WdgCommonHandleEvent(pIWidget, PROP_IFONE_WDG_ADDCHILD, (u32)pIChildWidget,(u32)&bAddSuccess);
    return bAddSuccess;
}

__INLINE void WdgIfoneSetDisplayStyle(IWidget* pIWidget, IFONEWDG_DESPLAY_STYLE_e eMode)
{
    WdgCommonSetProperty(pIWidget, PROP_IFONE_WDG_DISPLAY_STYLE, eMode);
}

__INLINE void WdgIfoneEnableShowShadow(IWidget* pIWidget, boolean bShowShadow)
{
    WdgCommonSetProperty(pIWidget, PROP_IFONE_WDG_SHOW_SHADOW, bShowShadow);
}

__INLINE u32 WdgIfoneGetChildNumber(IWidget* pIWidget)
{
    IVectorModel * pIVectorModel;
    WdgCommonGetProperty(pIWidget, PROP_IFONE_WDG_CHILDWDG_VECTOLMOLDEL,  (u32 *)&pIVectorModel);
    
    if(pIVectorModel)
    {
        return IVECTORMODEL_Size(pIVectorModel);
    }
    else
        return 0;
}

__INLINE void WdgIfoneSetFolderID(IWidget* pIWidget, u32 nFolderID)
{
    WdgCommonSetProperty(pIWidget, PROP_IFONE_WDG_FOLDERID, nFolderID);
}



#ifndef BREAKIF_NOTSUCCESS
#define BREAKIF_NOTSUCCESS(r) if(MAE_RET_SUCCESS != r) { break; }
#endif /* IF BREAKIF_NOTSUCCESS */

#ifndef BREAKIF_NULL 
#define BREAKIF_NULL(n,p) \
                        if( NULL == (p))\
                        {\
                            n = MAE_RET_OUT_OF_MEMORY;\
                            break;\
                        }
#endif


MAE_Ret IFoneWidget_New(MAE_ClsId ClsID, void **ppObj);
IWidget* WdgIfoneCreate(IfoneMenuItemData_p);
#endif	//MMI_WDG_IFONE_H
/*=============================================================*/
// end of file
