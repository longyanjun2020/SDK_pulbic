#ifndef __ANGRYBIRD_INC__
#define __ANGRYBIRD_INC__

#include "mmi_baseapplet.h"
#include "mae_widgetbase.h"


typedef enum
{
#ifdef __G3D_MMI__
	SCENE_BG=0,
	SCENE_START,
#else
	SCENE_START=0,
#endif
	SCENE_MENU,
	SCENE_PLAY,
	SCENE_PICK,
	SCENE_LEVEL,
	SCENE_PAUSE,
	SCENE_MAX,
}SceneState_e;

typedef enum
{
	GAME_START=0,
	GAME_MENU,
	GAME_PLAY,
	GAME_PAUSE,
	PAUSE_IDLE,
	PAUSE_NEXT,
	PAUSE_AGAIN,
	PAUSE_MENU,
}GameState_e;

typedef struct
{
	APPLET_BASE_ELEMENTS;
	boolean	bTouched;
   
	u16     u16SceneHandleId;	
	u32     nodeID[SCENE_MAX];
	s32		nTS_CurrentX;
	s32		nTS_CurrentY;

    float   fCameraMoveX;
    float	fTouchMoveX;
    
    boolean bPickBird;
	boolean bSuspendMode;
	boolean bDraw;
	boolean	bStart;
	boolean	bPause;
	boolean bMenu;
	boolean bMusic;
	boolean	bReset;
	boolean bExit;
	boolean	bFireBird;
	
	u8		level;
	u32		score;
	u32		highscore[10];
	u32		GameState;
	u32		PauseState;

	s32		scale;	
	s32		birdInitX;
	s32		birdInitY;
	u8		curBirdidx;	

#ifndef __G3D_MMI__
	IWidget *pBgImgWdg;
#endif

}AngryBirdApp_t;


MAE_Ret AngryBirdWdg_Ctor(AngryBirdApp_t *pThis);
MAE_Ret AngryBirdWdg_Dtor(AngryBirdApp_t *pThis);
void AngryBirdWdg_Draw(AngryBirdApp_t *pWdg);
boolean AngryBirdWdg_DefHandleEvent(AngryBirdApp_t *pWdg, MAE_EventId evt, u32 P1, u32 P2);

#endif
