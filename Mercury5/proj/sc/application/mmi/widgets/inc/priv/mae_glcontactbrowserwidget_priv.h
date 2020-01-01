/**
* @file mae_glcontactbrowser_priv.h
*
* @version $Id$
*/

#ifndef __MAE_GLCONTACTBROWSER_PRIV_H__
#define __MAE_GLCONTACTBROWSER_PRIV_H__

/*=============================================================*/
// include
/*=============================================================*/
#include "mae_glfotolistwidgetbase.h"
#include "mae_textlabel.h"
#include "PhbApp_img_data.h"
#include "CcApp_textlabel.h"

#include "mae_glwidget_common.h"
#include "mmi_mae_util_easing.h"
#include "mgl_Scene_NodeMgr.h"
#include "mgl_Core_shape.h"
#include "mgl_Scene_Environment.h"
#include "mgl_Egl.h"
#include "mmi_common_util.h"
#include "mmi_common_cfg.h"

/*=============================================================*/
// Enum
/*=============================================================*/
enum
{
    MMI_GCB_CONTACT_NODE_NUM	= 7,
    MMI_GCB_TAB_NODE_NUM		= 3,	/* Phone, SIM 1, SIM 2 */
    MMI_GCB_SK_NODE_NUM			= 4,	/* Call, MSG, Edit, Back */

    MMI_GCB_NODE_NUM_MAX		= 30,	/* Need update. */

    MMI_GCB_HALF_CIRCLE_ANGLE	= 180,
    MMI_GCB_FULL_CIRCLE_ANGLE	= 360,

    MMI_GCB_TOTAL_FRAME_MOVE	= 4,
    MMI_GCB_TOTAL_FRAME_PICK	= 8,
    MMI_GCB_TOTAL_FRAME_FLYIN	= 4,

    MMI_GCB_TIMER_MOVE			= 10,
    MMI_GCB_TIMER_PICK			= 10,
    MMI_GCB_TIMER_FLYIN			= 10,

    MMI_GCB_UNPICK				= 0xFF,

    MMI_GCB_BORDER				= 2,

    MMI_GCB_NAME_WIDTH			= 70,//45,
    MMI_GCB_NAME_HEIGHT			= 15,
    MMI_GCB_SK_HEIGHT			= 15
};


enum
{
    MMI_GCB_STATE_NEW						= 0,
    MMI_GCB_STATE_BROWSING					= 1,
    MMI_GCB_STATE_BROWSING_TO_BROWSING		= 2,
    MMI_GCB_STATE_BROWSING_TO_SHOW_DETAIL	= 3,
    MMI_GCB_STATE_SHOW_DETAIL				= 4,
    MMI_GCB_STATE_SHOW_DETAIL_TO_BROWSING	= 5
};
typedef u8 MMI_GCB_STATE_E;


enum
{
    MMI_GCB_SOFTKEY_CALL	= 0,
    MMI_GCB_SOFTKEY_MSG		= 1,
    MMI_GCB_SOFTKEY_EDIT	= 2,
    MMI_GCB_SOFTKEY_BACK	= 3
};
typedef u8 MMI_GCB_SOFTKEY_E;


/*=============================================================*/
// Constant
/*=============================================================*/
const Vertex3D GCBContactNodePos[] =
{
    {5,		35,		1},
    {45,	45,		20},
    {90,	75,		40},
    {85,	115,	60},
    {90,	155,	40},
    {45,	175,	20},
    {5,		195,	1}
};


const Vertex2D GCBContactNodeSize[] =
{
    {40, 40},
    {50, 50},
    {60, 60},
    {70, 70},
    {60, 60},
    {50, 50},
    {40, 40}
};


const Vertex3D GCBTabNodePos[] =
{
    {50,	5,	1},
    {100,	5,	1},
    {150,	5,	1}
};


const Vertex2D GCBTabNodeSize[] =
{
    {32, 22},
    {32, 22},
    {32, 22}
};


const Vertex3D GCBSKNodePos[] =
{
    {10,	260,	30},
    {67,	260,	30},
    {124,	260,	30},
    {180,	260,	30}
};


const Vertex2D GCBSKNodeSize[] =
{
    {50, 50},
    {50, 50},
    {50, 50},
    {50, 50}
};


const u32 GCBSKImgID[] =
{
    PHONEBOOK_IMG_DIAL_ICON,
    PHONEBOOK_IMG_MESSAGE_ICON,
    PHONEBOOK_IMG_PHONEBOOK_EDIT_ICON,
    PHONEBOOK_IMG_BACK_ICON
};


const Vertex3D GCBIconSKBGPos	= {0, 260, 10};
const Vertex2D GCBIconSKBGSize	= {240, 60};


const Vertex3D GCBDetailPos		= {60, 60, 80};
const Vertex2D GCBDetailSize	= {120, 120};


const Vertex3D GCBDetailBGPos	= {20, 40, 80};
const Vertex2D GCBDetailBGSize	= {200, 200};


const Vertex3D GCBDetailNamePos		= {20, 40, 80};
const Vertex2D GCBDetailNameSize	= {200, 15};


const Vertex3D GCBCallIconNodePos	= {20, 215, 100};
const Vertex2D GCBCallIconNodeSize	= {50, 20};


const Vertex3D GCBMSGIconNodePos	= {90, 215, 100};
const Vertex2D GCBMSGIconNodeSize	= {50, 20};


const Vertex3D GCBDetailIconNodePos		= {160, 215, 100};
const Vertex2D GCBDetailIconNodeSize	= {50, 20};

#define GCB_MIDDLE_NODE_INDEX ((sizeof(GCBContactNodePos) / sizeof(Vertex3D)) >> 1)

/*=============================================================*/
// Structure
/*=============================================================*/
typedef struct
{
    mgl_u32		u32NodeID;
    mgl_u32		u32RawID;
}GlRawDataID_t;

typedef struct
{
    GlFotoListWdgBase_t	FotoListWdgBase;///< It must be the 1st element of all GlFotoListWdg series

    MMI_GCB_STATE_E		eGCBState;
    mgl_u16				u16SceneHandleId;
    mgl_u32				aryu32ContactNodeID[MMI_GCB_CONTACT_NODE_NUM];
    GlRawDataID_t		aryNameRawDataID[MMI_GCB_CONTACT_NODE_NUM];		/* Store the RAW ID after first draw. */
    mgl_u32				aryu32TabNodeID[MMI_GCB_TAB_NODE_NUM];
    mgl_u32				aryu32SKNodeID[MMI_GCB_SK_NODE_NUM];
    mgl_u32				u32BackgroundNodeID;

    mgl_u32				u32CallNodeID;
    mgl_u32				u32CallRawDataID;

    mgl_u32				u32MessageNodeID;
    mgl_u32				u32MessageRawDataID;

    mgl_u32				u32DetailNodeID;
    mgl_u32				u32DetailRawDataID;

    mgl_u32				u32EmptyNodeID;
    mgl_u32				u32EmptyRawDataID;

    mgl_u32             u32TabIndex;
    mgl_u8				aryu8TabStatus[MMI_GCB_TAB_NODE_NUM];

    IImage				*pIImage_Decoding;
    boolean				bIsDecoding;

    mgl_u32				u32GCBFrame;

    MAE_EventId			eEventId;
    mgl_u32				u32HighlightedID;	/* 0 ~ size of menu model */
    mgl_u32				u32PickedID;		/* 0 ~ (MMI_GCB_CONTACT_NODE_NUM-1) */
#ifdef __TOUCH_SCREEN_MMI__
    ModelListener_t     VMListener;
#endif
} GlContactBrowserWdg_t;


/*=============================================================*/
// functions
/*=============================================================*/

/*------------------------------------------------------------------------------------------
* New function, Constructor and Destructor
------------------------------------------------------------------------------------------*/
MAE_Ret GlContactBrowserWdg_New(MAE_ClsId ClsID, void **ppObj);
MAE_Ret GlContactBrowserWdg_Ctor(GlContactBrowserWdg_t *pThis);
void GlContactBrowserWdg_Dtor(GlContactBrowserWdg_t *pThis);
static void GlContactBrowserWdg_WidgetFree(void *pData);

/*------------------------------------------------------------------------------------------
* For IHandler interface
------------------------------------------------------------------------------------------*/
static boolean GlContactBrowserWdg_DefHandleEvent(IWidget *pWdg, MAE_EventId evt, u32 P1, u32 P2);

/*------------------------------------------------------------------------------------------
* For IWidget interface
------------------------------------------------------------------------------------------*/
static void GlContactBrowserWdg_Draw(IWidget *pWdg, IDispCanvas *pDispCanvas, s32 x, s32 y);
boolean _GlContactBrowserWdg_SetProperty(GlContactBrowserWdg_t *pThis, u32 P1, u32 P2);
boolean _GlContactBrowserWdg_GetProperty(GlContactBrowserWdg_t *pThis, u32 P1, u32 P2);


#endif //__MAE_GLCONTACTBROWSER_PRIV_H__

