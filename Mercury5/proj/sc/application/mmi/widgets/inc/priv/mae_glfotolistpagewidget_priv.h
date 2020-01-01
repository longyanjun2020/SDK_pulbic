/**
* @file     mae_GLFOTOLISTPAGEWIDGET_priv.h
* @brief
*
* @version $Id:$
*/

#ifndef __MAE_GLFOTOLISTPAGEWIDGET_PRIV_H__
#define __MAE_GLFOTOLISTPAGEWIDGET_PRIV_H__

/*=============================================================*/
// include
/*=============================================================*/
#include "mmi_wdg_glfotolistpagewidget.h"
#include "mae_abscontainerbase.h"
#include "mgl_core_types.h"
#include "mgl_utility_common.h"
#include "mae_widgetbase.h"
#include "mgl_3DS_loader.h"

#include "mmi_common_dialog_id.h"
#include "mmi_common_content.h"
#include "mmi_base_util.h"
#include "mmi_mae_image.h"

/*=============================================================*/
// type and define
/*=============================================================*/
//#define _3DLOADER_INTER_TEXT_ 1
#define TOTAL_3D_OBJIMAGE  5
#define SCREEN_OBJ_NUM 3
#define PRE_DECODE_OBJ_OFFSETIDX 2
#define NEXT_CHANGIMG_FRAME_STAMP 15
#define PRE_CHANGIMG_FRAME_STAMP 35

#define FILE_NAME_TXT_HEIGHT 40

#define MIDDLE_FRAME_IDX 15
#define GL_EFFECT_TIMER 5
#define PICTURE_BATCH_SEARCH_FILE_NUM 100
#define PICTURE_MAX_NUM 300
#define FILE_URL_LIST_SIZE  9
#define NEXT_PAGE_STEP 5
#define LAST_PAGE_STEP -5
#define MIN_FRAME_NUM 5
#define MAX_FRAME_NUM 30
#define PLANE_TEXT_IDX 6
#define ANIM_MOVE_THRESHOLD 10

//3dloader layout.
#define PLANE_TEXTINFO_BG_X 0
#define PLANE_TEXTINFO_BG_Y 0
#define PLANE_TEXTINFO_BG_WIDTH 194
#define PLANE_TEXTINFO_BG_HEIGHT 38

#define PLANE_TEXTINFO_NAME_X 0
#define PLANE_TEXTINFO_NAME_Y 8
#define PLANE_TEXTINFO_NAME_WIDTH 138
#define PLANE_TEXTINFO_NAME_HEIGHT 20

#define PLANE_TEXTINFO_NUM_X 138
#define PLANE_TEXTINFO_NUM_Y 8
#define PLANE_TEXTINFO_NUM_WIDTH 56
#define PLANE_TEXTINFO_NUM_HEIGHT 20

enum
{
    DIR_PREV = -1,//DIR_LEFT
    DIR_NONE,
    DIR_NEXT = 1,//DIR_RIGHT
    FLY_OUT = 2,
    FLY_IN = 3,
    READY = 4
};
typedef s8 FotoPageDir_t;

enum
{
    FOTOPAGE_SCREEITEM_UPPER = 0,
    FOTOPAGE_SCREEITEM_MEDDLE,
    FOTOPAGE_SCREEITEM_LOWER,
    FOTOPAGE_SCREEITEM_MAX_NUM
};
typedef u8 FotoPageScreenItem_e;

enum
{
    FOTOPAGE_IMAGE_FROM_PHONE = 0,
    FOTOPAGE_IMAGE_FROM_CARD1,
#if defined(__DUAL_CARD__)    
    FOTOPAGE_IMAGE_FROM_CARD2,
#endif    
    FOTOPAGE_IMAGE_FROM_ALL
};
typedef u8 FotoPageImageFrom_e;

typedef enum
{
	PHOTOSLIDE_Portrait = 0,
	PHOTOSLIDE_Landscape,	
} PhotoSlideType_e;

typedef struct {
    AbsContainerBase_t  PCntrBase;
    ModelListener_t MdlLsnr;

    Pos_t tTsPos;
    Vertex2D size;
    u32 nTotalNumOfObj;
#ifdef __TOUCH_SCREEN_MMI__     
    ITouchSrv *pITouchSrv;
#endif
    u8 nUnderDecodingNum;
    IImage *pItemImg[FOTOPAGE_SCREEITEM_MAX_NUM];
    IBitmap *pBmpListOfObj[TOTAL_3D_OBJIMAGE];
    IBitmap *pBmpText;
    u32 nCurrentIdx;

    u32 nDecodeIdx; //file index that put into start decode process   :0 ~ nTotalNumOfObj
    u32 nCurDecodedIdx; //Decode Notify index. :0 ~ nTotalNumOfObj
    u32 nFocusObjIdx; //Decode Notify index. :0 ~ nTotalNumOfObj
    u32 nCurrentFrame;
    boolean bFileInited;
    u32 nInitObj;
    u8 nFileSortDone;
    u8 nFileListDone;    
    boolean bRunOpenEffect;

    //FILE
    u32     nPhoneFileHandle;
    u32     nPhoneFileNum;
    u32     nCardFileHandle;
    u32     nCardFileNum;    
#if defined(__DUAL_CARD__)
    u32     nCard2FileHandle;
    u32     nCard2FileNum;
#endif

    u32     nFileNum;

    MAE_WChar    pItemUrl[FILEMGR_MAX_FILEPATH_SIZE];

	//decode resource.
	IWidget *GlLoaderWdg;
	u32 nTempdecodeIdx;
	u32 nBgResId;
	boolean bAnimEnd;
	boolean bDecodeErrorHandle;
	FotoPageDir_t eAdjustDir;

	IWidget *GlPhtoSlideWdg;
	VectorClass_t	*pPhotoBmpVectorClass;	  // The VectorClass keeps the cover bitmaps
	PhotoSlideType_e slideType ;
}GlFotoListPageWdg_t;


/*=============================================================*/
// functions
/*=============================================================*/


/*------------------------------------------------------------------------------------------
* New function, Constructor and Destructor
------------------------------------------------------------------------------------------*/
MAE_Ret GlFotoListPageWdg_New(MAE_ClsId ClsID, void **ppObj);
MAE_Ret GlFotoListPageWdg_Ctor(GlFotoListPageWdg_t *pThis);
void GlFotoListPageWdg_Dtor(GlFotoListPageWdg_t *pThis);

/*------------------------------------------------------------------------------------------
* For IHandler interface
------------------------------------------------------------------------------------------*/
boolean GlFotoListPageWdg_DefHandleEvent(IAbsContainer *pWdg, MAE_EventId evt, u32 P1, u32 P2);

/*------------------------------------------------------------------------------------------
* For IWidget interface
------------------------------------------------------------------------------------------*/
boolean _GlFotoListPageWdg_SetProperty(GlFotoListPageWdg_t *pThis, u32 P1, u32 P2);
boolean _GlFotoListPageWdg_GetProperty(GlFotoListPageWdg_t *pThis, u32 P1, u32 P2);

#if defined(__3D_UI_PHOTOSLIDE_MMI__)
void _GlfotoBmpElementVectorClassFree(void *pData, void *pOwner);
static void _GlFotoListPage_StatusChangeCB(void *pApplet, void *pUsrData, WidgetEvtCode_t nEvtCode, u32 dwParam, IWidget *pWidget);
#endif

#endif //__MAE_GLFOTOLISTPAGEWIDGET_PRIV_H__

