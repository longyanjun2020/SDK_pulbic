/**
* @file mae_gadgetcontainer_priv.h
*
* @version $Id$
*/

/*=============================================================
File name: mae_gadgetcontainer_priv.h
Description:
=============================================================*/
#ifndef __MAE_GADGETCONTAINER_PRIV_H__
#define __MAE_GADGETCONTAINER_PRIV_H__

/*=============================================================*/
// include
/*=============================================================*/
#include "mmi_mae_common_def.h"
#include "mmi_mae_interface_def.h"
#include "mae_containerbase.h"
#include "mae_gadgetcontainer.h"
#include "mmi_wdg_shortcutbar.h"
#include "mae_abscontainerbase.h"
#include "img_data.h"

/*=============================================================*/
// type and define
/*=============================================================*/
#define CONTAINER_VIRTUAL_WIDTH_NUM 5	/* total width = CONTAINER_VIRTUAL_WIDTH_NUM*container width */
#define CONTAINER_GADGET_MOVE_BOUNDARY_OFFSET(containerWidth) (containerWidth/2)
#define CONTAINER_PAN_BY_WIDGET_MAX_OFFSET 7
#define CONTAINER_GADGET_GAP 11

#define GADGETCONTAINER_BAR_HEIGHT 65
#define GADGETCONTAINER_SK_HEIGHT 28
#define GADGETCONTAINER_SK_WIDTH 97
#define GADGETCONTAINER_SK_TEXT_WIDTH 75
#define GADGETCONTAINER_SK_EDGE_OFFSET 22
#define GADGETCONTAINER_NOTICEEBAR_HEIGHT 28

#define ICON_X_W 30
#define ICON_X_H 31

#define GADGETCONTAINER_POOL_AREA_H(totalH) ((totalH)-GADGETCONTAINER_BAR_HEIGHT-GADGETCONTAINER_SK_HEIGHT)

#define GADGETCONTAINER_ITEM_BEGIN_X  (CONTAINER_GADGET_GAP)
#define GADGETCONTAINER_ITEM_HEIGHT GADGETCONTAINER_BAR_HEIGHT
#define GADGETCONTAINER_ITEM_GAP 11
#define GADGETCONTAINER_ITEM_AREA_W(totalW)	(totalW)
#define GADGETCONTAINER_ITEM_BASELINE_TOP_OFFSET 33
#define GADGETCONTAINER_NOTICEBAR_ALPHA_VAL 0.5f
#define ANIM_GADGET_SHOW_ZOOM_Z_OFFSET 300
#define ANIM_GADGET_SHOW_ALPHA_VAL	0.3f
#define ANIM_GADGET_PICUP_SCAL_VAL	1.2f
#define ANIM_GADGET_PICUP_ALPHA_VAL	0.5f
#define ANIM_GADGET_CREATION_ALPHA_VAL	0.8f
#define GADGET_REFLECT_ALPHA_BEGIN 0.8f
#define GADGET_REFLECT_ALPHA_END 0.0f
#define GADGET_REFLECT_HEIGHT_RATIO 0.3f
#define GADGET_FLIP_BG_DARKEN_ALPHA	0.6f
#define GADGET_FLIP_REFLECT_LEAVE_OFFSET 100
#define GADGET_PRESS_DARKEN_COLOR_VAL	0.7f

#define GADGETBAR_DARKEN_COLOR 0.4f
#define TRASHCAN_ANIM_TOTAL_FRAMES 3
#define ANIM_INIT_MAX_COUNT	4

enum
{
	UICOMP_NONE = 0,
	UICOMP_GADGET_POOL,		/* Gadget pool area */
	UICOMP_GADGET_ICONS,	/* Small gadget icon list area */
	UICOMP_LSK,				/* Home */
	UICOMP_RSK,				/* Delete/Cancel */
	UICOMP_REMOVE_ICON
};
typedef u8 UIComp_e;

enum
{
	STATUS_HIDE,
	STATUS_SHOW,
	STATUS_GADGET_REMOVING,
	STATUS_GADGET_SETTING_PAGE,
	STATUS_ANIMATION_LOCK
};
typedef u8 GadgetContainerStatus_e;

enum
{
	ANIM_NONE = 0,
	ANIM_GADGET_LIST_PAN,
	ANIM_GADGET_LIST_INTERTIA_MOVE,
	ANIM_GADGET_LIST_BOUNDARY_JIGGLE,
	ANIM_GADGET_PICKUP,
	ANIM_GADGET_PUTDOWN,
	ANIM_GADGET_TRASHOUT,
	ANIM_GADGET_MOVEMENT,
	ANIM_GADGET_FLIP_IN,
	ANIM_GADGET_FLIP_OUT,
	ANIM_GADGET_CREATION,
	ANIM_GADGET_COLLISION_MOVE,
	ANIM_CONTAINER_PAN,
	ANIM_CONTAINER_PAN_BY_GADGET,
	ANIM_CONTAINER_INTERTIA_MOVE,
	ANIM_CONTAINER_BOUNDARY_JIGGLE,
	ANIM_CONTAINER_SHOW_X,
	ANIM_CONTAINER_SHOW,
	ANIM_CONTAINER_GADGET_RESTORE
};

enum
{
	CONTAINER_TEXT_NONE = 0,
	CONTAINER_TEXT_SK_HOME,
	CONTAINER_TEXT_SK_DELETE,
	CONTAINER_TEXT_SK_CANCEL,
	CONTAINER_TEXT_NUM,
};

enum
{
	CONTAINER_TEXTURE_BG = 0,
	CONTAINER_TEXTURE_DOWN_BG,
	CONTAINER_TEXTURE_SK_BG,
	CONTAINER_TEXTURE_X,
	CONTAINER_TEXTURE_NUM,
};
enum
{
	GADGET_TEXTURE_CALENDARD = 0,
	GADGET_TEXTURE_ANALOG_CLOCK_1,
	GADGET_TEXTURE_ANALOG_CLOCK_2,
	GADGET_TEXTURE_DIGITAL_CLOCK_1,
//	GADGET_TEXTURE_DIGITAL_CLOCK_2,
	GADGET_TEXTURE_FM_RADIO,
	GADGET_TEXTURE_MEDIA_PLAYER,
	GADGET_TEXTURE_OPERATOR,
	GADGET_TEXTURE_PROFILE,
	GADGET_TEXTURE_NUM
};

typedef struct UITexture_s
{	
	GLuint textureId;
	GLuint maskTextureId;
	GLfloat wRatio;
	GLfloat hRatio;
}UITexture_st;

typedef struct
{
	u32 iconId;
	MAE_ClsId classId;
	s16 w;
	s16 h;
	u8 bMultiInstance;
}StaticGadgetsInfo_st;

typedef struct
{
	u32 id;
	u32 usageCount;
}RegGadget_st;

typedef struct  
{
	u16 count;
	u16 maxCount;
	u32 maxID;
	RegGadget_st *pRegGadgets;
}RegGadgetSet;

typedef struct 
{
	WidgetCell_t *pCell;
	Rect_t origRect;
	Rect_t targetRect;
	u8 isDirectHit;
	u8 isIndirectHit;
	u8 hitBy;
}GadgetCollisionItem_st;

typedef struct 
{
	u32 id;
	boolean bFire;
	u8 animId;				// animation id
	u16 step;			// current step 
	u16 totalSteps;		// total steps for this animation
	GLfloat curScalVal;
	GLfloat curAlpha;
	GLfloat curRefAlpha;
	GLshort curRefOffset;
	// Movement
	Point_t stMoveBeginPos;	
	s32 stepMoveOffset;
	s32 targetOffset;
	s32 origOffset;
	// Gadget flip
	Vertex3D fgFrom[4];
	Vertex3D fgTo[4];
	Vertex3D bgFrom[4];
	Vertex3D bgTo[4];
	// Target
	WidgetCell_t *pAnimWdgCell;
}Animation_st;

typedef struct  
{
	u32 maxID;
	u16 count;
	u16 maxCount;
	Animation_st *pAnimations;
	boolean bPlaying;
}AnimationSet_st;

typedef struct 
{
    Vertex3D pos;
    Vertex2D size;
    GLfloat alpha;
	Color4f color;
}GadgetTextureInfo_st;

typedef struct 
{
	Vertex3D pos;
	Vertex2D size;
	Color4f color;
}PlaneInfo_st;

typedef struct  
{
	s16 *pWaveHeight;
 	u16 w;
	u16 h;
	Rect_t dropArea;
	u8 curHeightBuf;
	u8 bDropped;
}WaterwaveEffect_st;

typedef struct  
{
	u8 textId;
	u8 bPressed;
}SKInfo;

typedef struct  
{
	u32 id;
	Point_t location;
}LiveGadgetInfo_st;

typedef struct 
{
	s32 viewOffset;
	u16 numOfRegGadget;
	u16 numOfAliveGadget;
}GadgetSerializeData_st;

typedef struct
{
    u32         id;
    IWidget*    wdg;
    u32         texid;
} WidgetInfo_t;

static const StaticGadgetsInfo_st BUILD_IN_GADGETS[] =
{
	{WIDGET_IMG_ICON_CALENDAR,			CLSID_CALENDARDESKTOPWIDGET, 42, 42, FALSE},	/* GADGET_TEXTURE_CALENDARD */
	{WIDGET_IMG_ICON_ANALOG_CLOCK_01,	CLSID_ACLOCKDESKTOPWIDGET, 44, 43, FALSE},	/* GADGET_TEXTURE_ANALOG_CLOCK_1 */
	{WIDGET_IMG_ICON_ANALOG_CLOCK_02,	CLSID_ACLOCKDESKTOPWIDGET, 42, 44, FALSE},	/* GADGET_TEXTURE_ANALOG_CLOCK_2 */
	{WIDGET_IMG_ICON_DIGITAL_CLOCK_01,	CLSID_DCLOCKDESKTOPWIDGET, 63, 30, FALSE},	/* GADGET_TEXTURE_DIGITAL_CLOCK_1 */
	//{WIDGET_IMG_ICON_DIGITAL_CLOCK_02,	CLSID_DCLOCKDESKTOPWIDGET, 59, 39, TRUE},	/* GADGET_TEXTURE_DIGITAL_CLOCK_2 */
	{WIDGET_IMG_ICON_FM_RADIO,		CLSID_FMDESKTOPWIDGET, 62, 36, FALSE},	/* GADGET_TEXTURE_FM_RADIO */
	{WIDGET_IMG_ICON_MUSIC_PLAYER,	CLSID_MPDESKTOPWIDGET, 62, 37, FALSE},	/* GADGET_TEXTURE_MEDIA_PLAYER */
	{WIDGET_IMG_ICON_OPERATOR,		CLSID_OPDESKTOPWIDGET, 50, 33, FALSE},	/* GADGET_TEXTURE_OPERATOR */
	{WIDGET_IMG_ICON_PROFILE,		CLSID_PROFILE_WIDGET, 46, 44, FALSE}	/* GADGET_TEXTURE_PROFILE */
};
#define BUILD_IN_GADGETS_COUNT	(sizeof(BUILD_IN_GADGETS)/sizeof(StaticGadgetsInfo_st))

//structure for a gadget-container
typedef struct {
	AbsContainerBase_t AbsCntrBase;
	// ABOVE is FIXED, do not change
	GadgetContainerStatus_e status;
	RegGadgetSet regGadgetSet;
	SKInfo skInfo[2];
	u8 aliveGadgetCount;
	u8 isGadgetIconDisabled;
	GadgetSerializeData_st *pSaveData;
	LiveGadgetInfo_st *pLiveGadgetInfo;
	IWidget *pNewGadget;
	u32 newGadgetIdx;

	u8 bHookTouchEvt;
	UIComp_e hookTouchEvtUIComp;
	s32 viewOffset;			// Pool area view offset
	s32 lastViewOffset;
	s32 lastLastViewOffset;
	s32 gadgetMinX;
	s32 gadgetMaxX;
	s16 gadgetListOffset;	// Gadget list area view offset
	s16 lastGadgetListOffset;
	s16 lastLastGadgetListOffset;
	s16 totalGadgetIconWidth;
	
	// animations
	AnimationSet_st animSet;
	Animation_st directAnim;
	boolean bDirectAnimPlaying;
	u32 gadgetCollisionAnimId;
	u32 panByGadgetAnimId;
	u32 gadgetListMoveAnimId;
	u32 containerMoveAnimId;
	u32 containerBoundaryJiggleAnimId;
	u32 gadgetListBoundaryJiggleAnimId;
	
	// for gadget pressed 
	WidgetCell_t *pPressedCell;

	// for water wave
	IBitmap *pWaterwaveBitmap;
	WaterwaveEffect_st *pWaterwave;
	u16 *pSnapshotRaw;
	u8 bShowWaterwave;

    boolean bSingleGadgetCreated[GADGET_TEXTURE_NUM];

	UITexture_st flipGadgetTexture; // Texture for flip gadget
	GadgetTextureInfo_st textureInfo[CONTAINER_TEXTURE_NUM];
	GadgetTextureInfo_st gadgetIconTexInfo[GADGET_TEXTURE_NUM];
	GadgetTextureInfo_st skBGTexInfo[2];
	PlaneInfo_st noticeTextInfo;
	GadgetTextureInfo_st darkTexInfo;    
	GadgetTextureInfo_st wdgTexinfo;
	u32 textID[CONTAINER_TEXT_NUM];
	u32 flipGadgetID;
	u32 nodeID;
	u16 handleID;
	
	// gadget collision calculation
	GadgetCollisionItem_st *pGadgetCollisionItems;


	IDisplay *pIDisplay;
#ifdef __TOUCH_SCREEN_MMI__
	ITouchSrv *pITouchSrv;  //< Touch service
#endif //__TOUCH_SCREEN_MMI__

    WidgetInfo_t s_active_wdg[BUILD_IN_GADGETS_COUNT];
    u32 s_active_wdg_count;

} GadgetContainer_t;

///structure of widget cell used in GadgetContainer
typedef struct GadgetWidgetCell_Tag
{
    AbsWidgetCell_t AbsWCellBase;
    Point_t frontSideWdgLoc;
    u32 gadgetCellID;
    GLfloat wRatio;
    GLfloat hRatio;    
    ModelListener_t listener;
    u32 id;
	u32 gadgetAnimId;
	u8 bDirty;
	u8 bLoaded;
} GadgetWidgetCell_t;

/*=============================================================*/
// functions
/*=============================================================*/

//new function, constructor and destructor
MAE_Ret GadgetContainer_New(MAE_ClsId ClsID, void **ppObj);

MAE_Ret GadgetContainer_Ctor(GadgetContainer_t *pThis);

void GadgetContainer_Dtor(GadgetContainer_t *pThis);

/*------------------------------------------------------------------------------------------
* For IBase interface
------------------------------------------------------------------------------------------*/
//add reference function => use the function in container base

//release function
u32 GadgetContainer_Release(IGadgetContainer *pIGadgetContaine);

//query interface function
MAE_Ret GadgetContainer_QueryInterface (IGadgetContainer *pIGadgetContainer, MAE_IId iId, void **ppObj, IBase *pOwner);

/*------------------------------------------------------------------------------------------
* For IWidget interface
------------------------------------------------------------------------------------------*/
void GadgetContainer_SetSize(IGadgetContainer *pIGadgetContainer, WidgetSize_t *pSize);
void GadgetContainer_GetPreferredSize(IGadgetContainer *pIGadgetContainer, WidgetSize_t *pSize);
void GadgetContainer_Draw(IGadgetContainer *pIContainer, IDispCanvas *pIDispCanvas, s32 x, s32 y);

/*------------------------------------------------------------------------------------------
* For IContainer interface
------------------------------------------------------------------------------------------*/
MAE_Ret GadgetContainer_Add(IGadgetContainer *pIContainer, IWidget *WidgetPtr, IWidget *RefWidgetPtr, boolean isUpper, const void *DescPtr);
MAE_Ret GadgetContainer_DeleteCell(IGadgetContainer *pIContainer, WidgetCell_t *pWCell);
MAE_Ret GadgetContainer_Delete(IGadgetContainer *pIContainer, IWidget *WidgetPtr);
void GadgetContainer_Invalidate(IGadgetContainer *pIContainer, IWidget *WidgetPtr, const Rect_t *WRectPtr, InvFlag_t Flags);
MAE_Ret GadgetContainer_Locate(IGadgetContainer *pIContainer, IWidget *WidgetPtr, IContainer **ppRoot, Rect_t *RelativeRectPtr, IBase *pOwner);
/*------------------------------------------------------------------------------------------
* For IAbsContainer interface
------------------------------------------------------------------------------------------*/

MAE_Ret GadgetContainer_SetPos(IGadgetContainer *pIGadgetContainer, IWidget *pIWidget, const WPos_t *WPosPtr);
MAE_Ret GadgetContainer_GetPos(IGadgetContainer *pIGadgetContainer, IWidget *pIWidget, WPos_t *WPosPtr);



/*------------------------------------------------------------------------------------------
* For other functions
------------------------------------------------------------------------------------------*/
//layout function
void GadgetContainer_DoLayout(ContainerBase_t *pThis, WidgetCell_t *pWCell, Rect_t* pInvRect);

//default event handler for gadgetcontainer.
boolean GadgetContainer_DefHandleEvent(IGadgetContainer *pIGadgetContainer, MAE_EventId evt, u32 P1, u32 P2);

#endif //__MAE_GADGETCONTAINER_PRIV_H__
/*=============================================================*/
// end of file

