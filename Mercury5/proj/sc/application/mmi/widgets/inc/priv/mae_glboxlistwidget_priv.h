/**
* @file 	mae_glboxlistwidget_priv.h
* @brief   
*
* @version $Id: mae_glboxlistwidget_priv.h 37664 2010-02-12 09:36:01Z Elvis.Chen $
*/

#ifndef __MAE_GLBOXLISTWIDGET_PRIV_H__
#define __MAE_GLBOXLISTWIDGET_PRIV_H__

/*=============================================================*/
// include
/*=============================================================*/
#include "mmi_wdg_glboxlistwidget.h"
#include "mae_glfotolistwidgetbase.h"

#include "mgl_Scene_Environment.h"

//#define __GLBOXLIST_PRESS_BOX_AREA__
/*=============================================================*/
// type and define
/*=============================================================*/
typedef struct
{
	s32			nIdx;
    Vertex3D	tPos;
    Vertex2D	tSize;
    mgl_float	RotateX;
    mgl_float	RotateY;
    mgl_float   alpha;
    mgl_u32		nNodeID;
    mgl_u32		nRawDataId;	// returned RawDataId from mgl_DrawShape()

    u8 bUseDefaultPreImg;
    IImage *pPreImg; //If the image is register the IImage notify, Node keep the image.
} BoxNodeInfo_t;

enum {
	GLBOXLIST_ANI_NONE =0,
	GLBOXLIST_ANI_UP,
	GLBOXLIST_ANI_DOWN,
	GLBOXLIST_ANI_LEFT,
	GLBOXLIST_ANI_RIGHT,
	GLBOXLIST_ANI_BOX_START,
	GLBOXLIST_ANI_MSG_OPEN,
    GLBOXLIST_ANI_FLYIN,
	GLBOXLIST_ANI_NUM
};
typedef u8 BoxListAni_t; //Amimation

enum {
	BOX_FACE_FRONT = 0,
	BOX_FACE_RIGHT,
	BOX_FACE_BACK,
	BOX_FACE_LEFT,
	BOX_FACE_NUM
};
typedef u8 BoxFace_t;


typedef struct {
	GlFotoListWdgBase_t	FotoListWdgBase;///< It must be the 1st element of all GlFotoListWdg series
	
	// List
    u16                  nNodeCount; ///< count of foto nodes
	BoxNodeInfo_t		*pNodeList;	///< data of foto nodes
	mgl_u32 			*pNodeID;	///< foto node mgl_id list (it's used for RenderSceneNode & in size of nFotoNodeCount)
	
	// movement
    u16                  nPosOffset;     ///< How many positions to be moved of this movement.
    u16                  nPosMoved;
    u16                  nSteps;         ///< Current step to move to next position
    s16                  nPosFlip;
	BoxListAni_t		nAnimation;

	//Box
	GlBoxData_t BoxData;
    mgl_u32     nBoxLabelAniRawDataId;
    IWidget     *pBoxLabelAbsContainer;
    IWidget     *pBoxLabelImageTextWidget;
    IWidget     *pBoxLabelTextWidget;

	//Menu Item 
	IContainer *pItemContainer;
    IWidget     *pItemBGImgWdg;
    IContainer *pItemInfoContainer;
	IWidget *pItemTextWdg;
	IWidget *pItemPreImageWdg;
	IWidget *pItemInfoText1Wdg;
	IWidget *pItemInfoText2Wdg;
	IWidget *pItemInfoIcon1Wdg;
	IWidget *pItemInfoIcon2Wdg;
    IImage  *pItemDefaultPreImg;
    IWidget *pItemMMSIconWdg;
    IWidget *pItemMMSTextWdg;

    mgl_u32 nEmptyTextRawDataID;
    IWidget *pEmptyTextWdg;
    u32		nEmptyTextID;

    MAEEvent_t           nTouchEvt;
#ifdef __GLBOXLIST_PRESS_BOX_AREA__
    u8                   bPressBoxArea;
#endif

	//Widget X,Y offset
	s32 nDrawX;
	s32 nDrawY;

    s32 nPressX;
    s32 nPressY;
    s32 nReleaseX;
    s32 nReleaseY;

    u32 nAniFlyin;
    mgl_u32 aBoxLabelAniFlyinRawDataId[BOX_FACE_NUM];
    boolean bOpeningAnim;

    // panel position and size
    u32 nAniBox;
    Vertex3D	tEmptyPos;
}GlBoxListWdg_t;

/*=============================================================*/
// functions
/*=============================================================*/

/*------------------------------------------------------------------------------------------
* New function, Constructor and Destructor
------------------------------------------------------------------------------------------*/
MAE_Ret GlBoxListWdg_New(MAE_ClsId ClsID, void **ppObj);
MAE_Ret GlBoxListWdg_Ctor(GlBoxListWdg_t *pThis);
void GlBoxListWdg_Dtor(GlBoxListWdg_t *pThis);
static void GlBoxListWdg_WidgetFree(void *pData);

/*------------------------------------------------------------------------------------------
* For IHandler interface
------------------------------------------------------------------------------------------*/
static boolean GlBoxListWdg_DefHandleEvent(IWidget *pWdg, MAE_EventId evt, u32 P1, u32 P2);
boolean _GlBoxListWdg_SetProperty(GlBoxListWdg_t *pThis, u32 P1, u32 P2);
boolean _GlBoxListWdg_GetProperty(GlBoxListWdg_t *pThis, u32 P1, u32 P2);

/*------------------------------------------------------------------------------------------
* For IWidget interface
------------------------------------------------------------------------------------------*/
static void GlBoxListWdg_Draw(IWidget *pWdg, IDispCanvas *pDispCanvas, s32 x, s32 y);
void GlBoxListWdg_DataChangedCb(IWidget *pWdg, GlFotoListDataChangedEvt_t *pInfo);

#endif //__MAE_GLBOXLISTWIDGET_PRIV_H__
