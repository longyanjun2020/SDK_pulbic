/**
* @file 	mae_glalbumslidewidget_priv.h
* @brief
*
* @version $Id:$
*/

#ifndef __MAE_GLALBUMSLIDEWIDGET_PRIV_H__
#define __MAE_GLALBUMSLIDEWIDGET_PRIV_H__


/*=============================================================*/
// include
/*=============================================================*/
#include "mmi_wdg_glAlbumSlidewidget.h"
#include "mae_widgetbase.h"
#include "mmi_common_util.h"
#include "mgl_Core_shape.h"

/*=============================================================*/
// type and define
/*=============================================================*/
#define GL_ALBUMSLIDEFFECT_TIMER 5
#define GLALBUMSLIDE_LEFTNODE_ROTATE_RATIO    1
#define GLALBUMSLIDE_LEFTNODE_TRANSLATE_MOVE    1

#define GLALBUMSLIDE_X_TAXIS 120
#define GLALBUMSLIDE_Y_TAXIS 20
#define GLALBUMSLIDE_Z_TAXIS 120

#define GLALBUMSLIDE_X_OFFSET 240
#define GLALBUMSLIDE_Y_OFFSET 60
#define GLALBUMSLIDE_Z_OFFSET 120

/*enum
{
    GLALBUMSLIDEWDG_DIR_NONE,
    GLALBUMSLIDEWDG_DIR_LEFT,
    GLALBUMSLIDEWDG_DIR_RIGHT
};
typedef u8 FotoZAxisDir_t;
*/

typedef struct
{
	WidgetBaseEx_t WdgBase;
	ModelListener_t MdlLsnr;
	s32 nDrawX;
	s32 nDrawY;
	Vertex2D size;
	boolean	bTouched;
	u16     u16SceneHandleId;
	u32     nodeID;
	mgl_u32         nRawDataID;
	s32		nTS_CurrentX, nTS_CurrentY;
	s32		nTS_MoveX, nTS_MoveY;

	float t;
	float	fTS_X, fTS_Y;

	SmoothPlaneTexture	*pLeftPlane;
	PlaneTexture		*pRightPlane;
	IADirection_e      nZAxis;
	Vertex3D  m_LeftPos, m_RightPos;
	mgl_float               fLeftalpha, fRightalpha;

	mgl_u32        nLeftRawDataId;
	mgl_u32        nRightRawDataId;
	mgl_float        nItemScale;
	mgl_float 	nLeftRatio, nRightRatio;
	mgl_float 	nLeftMove, nRightMove;
	mgl_u32         nLeftRawDataID;
	mgl_u32         nRightRawDataID;
	IBitmap         *pCurCacheScreenBmp;
	IBitmap         *pNextCacheScreenBmp;
	Vertex2D  m_CurSize, m_NextSize;
	mgl_float         nCurFrameIdx;

} AlbumSlideWdg_t;

/*=============================================================*/
// functions
/*=============================================================*/


/*------------------------------------------------------------------------------------------
* New function, Constructor and Destructor
------------------------------------------------------------------------------------------*/
MAE_Ret GlAlbumSlideWdg_New(MAE_ClsId ClsID, void **ppObj);
MAE_Ret GlAlbumSlideWdg_Ctor(AlbumSlideWdg_t *pThis);
static void GlAlbumSlideWdg_Dtor(AlbumSlideWdg_t *pThis);

/*------------------------------------------------------------------------------------------
* For IHandler interface
------------------------------------------------------------------------------------------*/
static boolean GlAlbumSlideWdg_DefHandleEvent(IWidget *pWdg, MAE_EventId evt, u32 P1, u32 P2);

/*------------------------------------------------------------------------------------------
* For IWidget interface
------------------------------------------------------------------------------------------*/
static void GlAlbumSlideWdg_Draw(IWidget *pWdg, IDispCanvas *pDispCanvas, s32 x, s32 y);
boolean _GlAlbumSlideWdg_SetProperty(AlbumSlideWdg_t *pThis, u32 P1, u32 P2);
boolean _GlAlbumSlideWdg_GetProperty(AlbumSlideWdg_t *pThis, u32 P1, u32 P2);

#endif //__MAE_GLAlbumSlideWIDGET_PRIV_H__
