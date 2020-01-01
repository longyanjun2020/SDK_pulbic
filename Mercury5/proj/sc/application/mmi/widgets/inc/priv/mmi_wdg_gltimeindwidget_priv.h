/**
* @file 	mmi_wdg_gltimeindwidget_priv.h
* @brief
*
* @version $Id:$
*/

#ifndef __MMI_WDG_GLTIMEINDWIDGET_PRIV_H__
#define __MMI_WDG_GLTIMEINDWIDGET_PRIV_H__

#if defined(__3D_UI_IDLE_MULTIPAGE__) || defined(__3D_UI_IDLE_SIMPLE__)
/*=============================================================*/
// include
/*=============================================================*/
#include "mmi_wdg_gltimeindwidget.h"
#include "mgl_core_types.h"
#include "mgl_utility_common.h"
#include "mae_widgetbase.h"
#include "mmi_mae_clock.h"
//#include "mmi_cfgsrv_setting.h"

#include "mmi_coresrv.h"
#include "mmi_cfgsrv.h"


/*=============================================================*/
// type and define
/*=============================================================*/
typedef struct
{
    mgl_float	self;	// self rotate, zero base
    mgl_float	scene;	// revolution rotate, zero base
}NodeRotate_t;

enum
{
	GLTIMEWDG_ELMT_HOUR1,
	GLTIMEWDG_ELMT_HOUR2,
	GLTIMEWDG_ELMT_MINUTE1,
	GLTIMEWDG_ELMT_MINUTE2,
	GLTIMEWDG_ELMT_MAX_DIGT,
};
typedef u8 GlTimeWdg_Elmt_t;

typedef struct
{
	Vertex3D                pos;		    //position
	mgl_float               rotateFactor;
	u8                      u8CurDigit;		//Current
	u8                      u8NextDigit;	//
	u8                      u8DestDigit;	//
	u8                      u8MaxDigit;		//Maxium
	u8                      u8MinDigit;		//Minium
	boolean                 bIsFlip;
    boolean                 bIncDigit;
} mgl_Digit_tt;


typedef struct {
	WidgetBaseEx_t          WdgBase;
	ModelListener_t         MdlLsnr;

	ClockListener_t	        IClockListener;
	IClock     		        *pIClock;
	SetPhoneTimeFormat_e    ePhoneTimeFormat;
    GlTimeIndWidget_Style_e eLayoutStyle;
    GlTimeIndWidget_Date_e  eDateTxtStyle;
    GlTimeIndWidget_Animation_Type eAnimationType;
    u8                      nAniFrame;

	/* Core Srv*/
	ICORESRV	            *pICoreSrv;
    ICFGSrv                 *pICFGSrv;

	/*Display */
	mgl_Digit_tt            tWdgElmt[GLTIMEWDG_ELMT_MAX_DIGT];
    u8                      u8FlipDigit[GLTIMEWDG_ELMT_MAX_DIGT];

	/* Time */
	Vertex3D                pos;
	MAE_DateTime_t          tTime;
	boolean                 bAM;
	boolean                 bIsFlip;
	mgl_float               rotateFactor;
    IWidget                 *pBgWdg;
    IWidget                 *pBgUpWdg;
    IWidget                 *pBgDownWdg;
    IWidget                 *pDigitWdg;
//	IWidget	                *pDateWdg;
	IWidget                 *pAMWdg;
	IWidget                 *pPMWdg;
//  u32                     nBgTextureId;
//  u32                     nDateTextureId;
//  u32                     nAMTextureId;
//  u32                     nPMTextureId;
    u32                     u32TimeIndTextureId;
    IDispCanvas             *pTimeindDispCanvas;
    IBitmap                 *pTimeindBitmap;
    boolean                 bTimeindBitmapInvalidate;
    boolean                 bDrawByMGL;
    boolean                 bPauseAnim;
    IDispCanvas             *pDispCanvas;

	/* MGL part */
	mgl_u16					u16SceneHandleId;	///< MGL scene id
	u32     				nTimeNodeId;
    u8                      u8AlphaLevel;   // 0~100
    u16                     u16RotateDegree;

}GlTimeIndWdg_t;


/*=============================================================*/
// functions
/*=============================================================*/


/*------------------------------------------------------------------------------------------
* New function, Constructor and Destructor
------------------------------------------------------------------------------------------*/
MAE_Ret GlTimeIndWdg_New(MAE_ClsId ClsID, void **ppObj);
MAE_Ret GlTimeIndWdg_Ctor(GlTimeIndWdg_t *pThis);
static void GlTimeIndWdg_Dtor(GlTimeIndWdg_t *pThis);

/*------------------------------------------------------------------------------------------
* For IHandler interface
------------------------------------------------------------------------------------------*/
static boolean GlTimeIndWdg_DefHandleEvent(IWidget *pWdg, MAE_EventId evt, u32 P1, u32 P2);

/*------------------------------------------------------------------------------------------
* For IWidget interface
------------------------------------------------------------------------------------------*/
static void GlTimeIndWdg_Draw(IWidget *pWdg, IDispCanvas *pDispCanvas, s32 x, s32 y);
boolean _GlTimeIndWdg_SetProperty(GlTimeIndWdg_t *pThis, u32 P1, u32 P2);
boolean _GlTimeIndWdg_GetProperty(GlTimeIndWdg_t *pThis, u32 P1, u32 P2);

#endif //#if defined(__3D_UI_IDLE_MULTIPAGE__)
#endif //__MMI_WDG_GLTIMEINDWIDGET_PRIV_H__
