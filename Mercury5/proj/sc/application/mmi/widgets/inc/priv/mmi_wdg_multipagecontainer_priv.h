/**
* @file    mmi_wdg_multipagecontainer_priv.h
* @version $Id: mmi_wdg_multipagecontainer_priv.h
* @brief   This is the private header file for mmi_wdg_multipagecontainer.c
*/
#ifndef __MMI_WDG_MULTIPAGECONTAINER_PRIV_H__
#define __MMI_WDG_MULTIPAGECONTAINER_PRIV_H__

#if defined(__FEATURE_MGL__) && defined(__3D_UI_IDLE_MULTIPAGE__)
/*=============================================================*/
// include
/*=============================================================*/
#include "mae_abscontainerbase.h"
#include "mmi_wdg_animationcontainer.h"
#include "mmi_wdg_multipagecontainer.h"
#include "mgl_Egl.h"
#include "mgl_Scene_NodeMgr.h"
#include "mgl_Scene_Environment.h"
#include "mgl_Core_shape.h"
#include "mgl_Core_types.h"
#include "mgl_utility_common.h"

/*=============================================================*/
// type and define
/*=============================================================*/
#define PAGE_MAX_NUMBER                                 IDLEAPP_LAYOUT_MULTIPAGE_PAGE_NUMBER
#define PAGE_PAGE_OVERLAP_RATIO_INVERSE                 IDLEAPP_LAYOUT_MULTIPAGE_PAGE_PAGE_OVERLAP_RATIO_INVERSE
#define PAGE_PAGE_ANGLE                                 (360.0f/(IDLEAPP_LAYOUT_MULTIPAGE_PAGE_NUMBER+1))
#define PAGE_TRANSFER_ANIMATION_TIME_INTERVAL           IDLEAPP_LAYOUT_MULTIPAGE_PAGE_ANIMATION_INTERVAL
#define PAGE_TRANSFER_ANIMATION_FULL_FRAME              IDLEAPP_LAYOUT_MULTIPAGE_PAGE_ANIMATION_FRAME
#define PAGE_TRANSFER_ANIMATION_FAST_FRAME              (IDLEAPP_LAYOUT_MULTIPAGE_PAGE_ANIMATION_FRAME-2)
#define PAGE_BGIMAGE_EXTRA_PIXEL                        6
#define DEFAULT_CELL_SIZE_WIDTH                         IDLEAPP_LAYOUT_MULTIPAGE_PAGE_CELL_W
#define DEFAULT_CELL_SIZE_HEIGHT                        IDLEAPP_LAYOUT_MULTIPAGE_PAGE_CELL_H

typedef enum
{
    SHIFT_CONDITION_NONE,

    SHIFT_CONDITION_TO_LEFT,
    SHIFT_CONDITION_TO_RIGHT,
    SHIFT_CONDITION_LAST_LEFT,
    SHIFT_CONDITION_LAST_RIGHT,    
}MultipageContainerShiftCondition_e;

///structure for multipage-container
typedef struct {
    AbsContainerBase_t    AbsCntrBase;

    u8      u8TotalPageCount;
    u8      u8CurrentPage;
    u16     u16PageWidth;
    u16     u16PageHeight;

    boolean bAutoAnimation;
    boolean bAnimating;
    u32     u32AnimationFrame;
    u32     u32TotalFrame;

    MultipageContainerShiftCondition_e      eCondition;

    mgl_u16 u16SceneHandleId;
    mgl_u32 u32ContainerNodeID;

    boolean bAutoAlignment;
    WidgetSize_t tCellSize;
    WPos_t  stMoveBeginPos;
    Rect_t  stPageAddRegion;
    IDispCanvas * pBufCanvas;

} MultipageContainer_t;


///structure of widget cell used in multipage-container
typedef struct MultipageCntrWidgetCell_Tag {
    AbsWidgetCell_t absWCell;
    u32             u32ItemTextureId;       // a MGL texture id

} MultipageCntrWidgetCell_t;

/*=============================================================*/
// New function and Event handler
/*=============================================================*/
//new function
MAE_Ret MultipageContainer_New(MAE_ClsId ClsID, void **ppObj);
boolean WdgMultipageContainerDefHandleEvent(void *pIMultipageContainer, MAE_EventId evt, u32 P1, u32 P2);

/*=============================================================*/
// Non-interface functions
/*=============================================================*/
MAE_Ret WdgMultipageContainerConstructor(MultipageContainer_t *pThis);
void WdgMultipageContainerDestructor(MultipageContainer_t *pThis);

void MultipageContainerAnimationTimerCB(void * pUser);

#endif //__FEATURE_MGL__ && __3D_UI_IDLE_MULTIPAGE__
#endif //__MMI_WDG_MULTIPAGECONTAINER_PRIV_H__
/*=============================================================*/
// end of file
