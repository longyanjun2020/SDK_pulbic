/**
 * @file    mmi_wdg_petdesktop_priv.h
 * @brief   The internal structure of the petdesktopwidget

 */

#ifndef __MMI_WDG_PETDESKTOP_PRIV_H__
#define __MMI_WDG_PETDESKTOP_PRIV_H__

#include "mmi_mae_common_def.h"
#include "mmi_wdg_desktop.h"
#include "mmi_srv_header.h"
#include "rs_layout_id.h"
#include "mmi_desktopwidget_rs.h"
#include "DesktopWidgetPet_img_data.h"

#if defined(__GADGETS_MMI__) || defined(__3D_UI_IDLE_GADGETBAR__)
#ifdef __GADGETS_MMI_PET__

#define PETDESKTOPWDG_GESTURE_Z_THRESHOLD           20
#define PETDESKTOPWDG_GESTURE_C_THRESHOLD           25
#define PETDESKTOPWDG_GESTURE_LINE_THRESHOLD_Y      45
#define PETDESKTOPWDG_GESTURE_LINE_THRESHOLD_X      20
#define PETDESTOPWDG_FRAME_DELAY_TIME 250
#define PETDESTOPWDG_REVISION_ONE 1

#define PETDESTOPWDG_MULTIIMAGE_MAXCOUNT 10
#define PETDESTOPWDG_MULTIIMAGE

#ifndef PETDESTOPWDG_MULTIIMAGE

enum
{
    PetDesktopWdg_State_Lying_Bark,
    PetDesktopWdg_State_Lying,
#ifndef PETDESTOPWDG_REVISION_ONE
    PetDesktopWdg_State_Lying_ShakeHead,
#endif
    PetDesktopWdg_State_Lying_Tumble,
    //PetDesktopWdg_State_SitDown,
    //PetDesktopWdg_State_Sleep,
    PetDesktopWdg_State_LieDown,
    PetDesktopWdg_State_StandUp,
    PetDesktopWdg_State_Stand,
    PetDesktopWdg_State_Stand_ShakeHead,
    PetDesktopWdg_State_Stand_Tumble,
    PetDesktopWdg_State_Erect,
#ifdef PETDESTOPWDG_REVISION_ONE
    PetDesktopWdg_State_Stand_Bubble_R,
    PetDesktopWdg_State_Stand_Bubble_L,
    PetDesktopWdg_State_Bubble_Stand_R,
    PetDesktopWdg_State_Bubble_Stand_L,
    PetDesktopWdg_State_Stand_Touch,
    PetDesktopWdg_State_Touch_Lie,
    PetDesktopWdg_State_Lie_Sleep,
    PetDesktopWdg_State_Sleep_Stand,
#endif
	PetDesktopWdg_State_End,
};

#else //ifdef PETDESTOPWDG_MULTIIMAGE

enum
{
    PetDesktopWdg_State_Bubble_Stand,
    PetDesktopWdg_State_Erect,
    PetDesktopWdg_State_Lying,
    PetDesktopWdg_State_Lying_Bark,
    PetDesktopWdg_State_Lie_Sleep,
    PetDesktopWdg_State_Lying_Tumble,
    PetDesktopWdg_State_LieDown,
    PetDesktopWdg_State_Sleep_Stand,
    PetDesktopWdg_State_Stand,
    PetDesktopWdg_State_Stand_ShakeHead,
    PetDesktopWdg_State_Stand_Bubble,
    PetDesktopWdg_State_Stand_Touch,
    PetDesktopWdg_State_StandUp,
    PetDesktopWdg_State_Touch_Lie,

	PetDesktopWdg_State_End,
};

#endif //PETDESTOPWDG_MULTIIMAGE

typedef u16 PetDesktopWdg_State_e;



enum
{
    PetDesktopWdg_Play_Done,
    PetDesktopWdg_Gesture_Up,
    PetDesktopWdg_Gesture_Down,
    PetDesktopWdg_Gesture_Z,
    PetDesktopWdg_Gesture_C,
#ifdef PETDESTOPWDG_REVISION_ONE
    PetDesktopWdg_Gesture_Click,
    PetDesktopWdg_TimeUp,
#endif
    PetDesktopWdg_Event_End,

};
typedef u16 PetDesktopWdg_Event_e;

typedef struct
{
	PetDesktopWdg_State_e eState;
	u32 u32ImageId;

    u8  u8FrameNum;
    u8  u8ColNum;
    u8  u8RowNum;

    u8  u8RepeatStart;
    u8  u8RepeatEnd;
	u8  u8RepeatTimes;

    u16 u16FrameDelay;
} PetDesktopWdg_Behavior_t;

typedef struct
{
	PetDesktopWdg_State_e eState;
    u8  u8ImageCount;
	u8  u8RepeatTimes;
    u16 u16FrameDelay;
	u32 u32ImageId[PETDESTOPWDG_MULTIIMAGE_MAXCOUNT];
} PetWdg_Behavior_t;


typedef struct
{
	PetDesktopWdg_State_e	eSrcState;
	PetDesktopWdg_Event_e	eEvent;
	PetDesktopWdg_State_e	eNextState;
}PetDesktopWdg_State_Change_t;

#ifndef PETDESTOPWDG_MULTIIMAGE 

const PetDesktopWdg_Behavior_t PetDesktopWdgBehaviorTable[] =
{       // the oreder must map to PetDesktopWdg_State_e
	/*---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------*/
	/* eState  |  u32ImageId | u8FrameNum, ColNum, RowNum, RepeateStartFrame, RptEndFrame, RptTimes, FrameDleayTime*/
	/*----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------*/
	{PetDesktopWdg_State_Lying_Bark,  			    PET_IMG_LIE_BARK,           8, 2, 4,  0, 0, 0,  PETDESTOPWDG_FRAME_DELAY_TIME},
	{PetDesktopWdg_State_Lying,   				    PET_IMG_LIE,                1, 1, 1,  0, 0, 0,  PETDESTOPWDG_FRAME_DELAY_TIME},
#ifndef PETDESTOPWDG_REVISION_ONE
	{PetDesktopWdg_State_Lying_ShakeHead,			PET_IMG_LIE_SHAKE_HEAD,     9, 2, 5,  2, 4, 1,  PETDESTOPWDG_FRAME_DELAY_TIME},
#endif
	{PetDesktopWdg_State_Lying_Tumble, 				PET_IMG_LIE_TUMBLE,         9, 2, 5,  3, 5, 1,  PETDESTOPWDG_FRAME_DELAY_TIME},
	{PetDesktopWdg_State_LieDown,   				PET_IMG_LIEDOWN,            4, 2, 2,  0, 0, 0,  PETDESTOPWDG_FRAME_DELAY_TIME},
	{PetDesktopWdg_State_StandUp,   				PET_IMG_STANDUP,            4, 2, 2,  0, 0, 0,  PETDESTOPWDG_FRAME_DELAY_TIME},
	//{PetDesktopWdg_State_Sleep,                     PET_IMG_2D_SLEEP,           2, 2, 1,  0, 1,20, 1000},
	{PetDesktopWdg_State_Stand,                     PET_IMG_STAND,              2, 2, 1,  0, 1, 0,  PETDESTOPWDG_FRAME_DELAY_TIME},
	{PetDesktopWdg_State_Stand_ShakeHead,   		PET_IMG_STAND_SHAKE_HEAD,   8, 2, 4,  4, 5, 1,  PETDESTOPWDG_FRAME_DELAY_TIME},
	{PetDesktopWdg_State_Stand_Tumble, 				PET_IMG_STAND_TUMBLE,      12, 2, 6,  5, 7, 1,  PETDESTOPWDG_FRAME_DELAY_TIME},
	{PetDesktopWdg_State_Erect,       			    PET_IMG_ERECT,              6, 2, 3,  0, 5, 0,  PETDESTOPWDG_FRAME_DELAY_TIME},
#ifdef PETDESTOPWDG_REVISION_ONE
	{PetDesktopWdg_State_Stand_Bubble_R,            PET_IMG_STAND_TO_BUBBLE_R,  6, 2, 3, 4, 5, 3,   PETDESTOPWDG_FRAME_DELAY_TIME},
	{PetDesktopWdg_State_Stand_Bubble_L,            PET_IMG_STAND_TO_BUBBLE_L,  6, 2, 3, 4, 5, 3,   PETDESTOPWDG_FRAME_DELAY_TIME},
	{PetDesktopWdg_State_Bubble_Stand_R,            PET_IMG_BUBBLE_TO_STAND_R,  5, 2, 3, 0, 0, 0,   PETDESTOPWDG_FRAME_DELAY_TIME},
	{PetDesktopWdg_State_Bubble_Stand_L,            PET_IMG_BUBBLE_TO_STAND_L,  5, 2, 3, 0, 0, 0,   PETDESTOPWDG_FRAME_DELAY_TIME},
	{PetDesktopWdg_State_Stand_Touch,               PET_IMG_STAND_TO_TOUCH,     7, 2, 4, 5, 6, 3,   PETDESTOPWDG_FRAME_DELAY_TIME},
	{PetDesktopWdg_State_Touch_Lie,                 PET_IMG_TOUCH_TO_LIE,       6, 2, 3, 0, 0, 0,   PETDESTOPWDG_FRAME_DELAY_TIME},
	{PetDesktopWdg_State_Lie_Sleep,                 PET_IMG_LIE_TO_SLEEP,       7, 2, 4, 0, 0, 0,   PETDESTOPWDG_FRAME_DELAY_TIME},
	{PetDesktopWdg_State_Sleep_Stand,               PET_IMG_SLEEP_TO_STAND,     8, 2, 4, 0, 0, 0,   PETDESTOPWDG_FRAME_DELAY_TIME},
#endif
};

#else // #ifdef PETDESTOPWDG_MULTIIMAGE

const PetWdg_Behavior_t PetWdgBehaviorTable[] = 
{
	/*---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------*/
	/* eState  | ImageCount | RptTimes  | FrameDleayTime | u32ImageId[10] | */
	/*----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------*/
    {PetDesktopWdg_State_Bubble_Stand,      4, 0, PETDESTOPWDG_FRAME_DELAY_TIME, PET_IMG_A7, PET_IMG_A8, PET_IMG_A9, PET_IMG_A10},
    {PetDesktopWdg_State_Erect,             6, 0, PETDESTOPWDG_FRAME_DELAY_TIME, PET_IMG_A11, PET_IMG_A16, PET_IMG_A17, PET_IMG_A18, PET_IMG_A19, PET_IMG_A20},
    {PetDesktopWdg_State_Lying,             1, 0, PETDESTOPWDG_FRAME_DELAY_TIME, PET_IMG_A6},
    {PetDesktopWdg_State_Lying_Bark,        8, 0, PETDESTOPWDG_FRAME_DELAY_TIME, PET_IMG_A26, PET_IMG_A27, PET_IMG_A28, PET_IMG_A29, PET_IMG_A30, PET_IMG_A31, PET_IMG_A32, PET_IMG_A33},
    {PetDesktopWdg_State_Lie_Sleep,         7, 0, PETDESTOPWDG_FRAME_DELAY_TIME, PET_IMG_A6, PET_IMG_A39, PET_IMG_A40, PET_IMG_A41, PET_IMG_A42, PET_IMG_A48, PET_IMG_A43},
    {PetDesktopWdg_State_Lying_Tumble,      8, 1, PETDESTOPWDG_FRAME_DELAY_TIME, PET_IMG_A25, PET_IMG_A34, PET_IMG_A35, PET_IMG_A36, PET_IMG_A37 ,PET_IMG_A38, PET_IMG_A35, PET_IMG_A34},
    {PetDesktopWdg_State_LieDown,           4, 0, PETDESTOPWDG_FRAME_DELAY_TIME, PET_IMG_A11, PET_IMG_A44, PET_IMG_A45, PET_IMG_A6},
    {PetDesktopWdg_State_Sleep_Stand,       6, 0, PETDESTOPWDG_FRAME_DELAY_TIME, PET_IMG_A43, PET_IMG_A46, PET_IMG_A47, PET_IMG_A48, PET_IMG_A49, PET_IMG_A50},
    {PetDesktopWdg_State_Stand,             2, 0, PETDESTOPWDG_FRAME_DELAY_TIME, PET_IMG_A51, PET_IMG_A52},
    {PetDesktopWdg_State_Stand_ShakeHead,   8, 1, PETDESTOPWDG_FRAME_DELAY_TIME, PET_IMG_A11, PET_IMG_A52, PET_IMG_A53, PET_IMG_A54, PET_IMG_A55, PET_IMG_A56, PET_IMG_A54, PET_IMG_A52},
    {PetDesktopWdg_State_Stand_Bubble,      8, 1, PETDESTOPWDG_FRAME_DELAY_TIME, PET_IMG_A26, PET_IMG_A27, PET_IMG_A28, PET_IMG_A29, PET_IMG_A30, PET_IMG_A31, PET_IMG_A32, PET_IMG_A33},
    {PetDesktopWdg_State_Stand_Touch,       7, 2, PETDESTOPWDG_FRAME_DELAY_TIME, PET_IMG_A11, PET_IMG_A59, PET_IMG_A3, PET_IMG_A2, PET_IMG_A60, PET_IMG_A1, PET_IMG_A61},
    {PetDesktopWdg_State_StandUp,           4, 0, PETDESTOPWDG_FRAME_DELAY_TIME, PET_IMG_A6, PET_IMG_A45, PET_IMG_A44, PET_IMG_A11},
    {PetDesktopWdg_State_Touch_Lie,         6, 0, PETDESTOPWDG_FRAME_DELAY_TIME, PET_IMG_A1, PET_IMG_A2, PET_IMG_A3, PET_IMG_A4, PET_IMG_A5, PET_IMG_A6},
};

#endif // #endif  PETDESTOPWDG_MULTIIMAGE

const PetDesktopWdg_State_Change_t PetDesktopWdgStateChangeTable[] =
{
	/*---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------*/
	/* eSrcState  |  eEvent | eNextState  */
	/*----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------*/

#ifdef PETDESTOPWDG_MULTIIMAGE

    {PetDesktopWdg_State_Bubble_Stand,      PetDesktopWdg_Play_Done,    PetDesktopWdg_State_Stand},
    {PetDesktopWdg_State_Stand,             PetDesktopWdg_Gesture_Up,   PetDesktopWdg_State_Erect},
    {PetDesktopWdg_State_Erect,             PetDesktopWdg_Gesture_Up,   PetDesktopWdg_State_Erect},
    {PetDesktopWdg_State_Erect,             PetDesktopWdg_Play_Done,    PetDesktopWdg_State_Stand},
    {PetDesktopWdg_State_Stand,             PetDesktopWdg_Gesture_Z,    PetDesktopWdg_State_Stand_ShakeHead},
    {PetDesktopWdg_State_Stand_ShakeHead,   PetDesktopWdg_Gesture_Z,    PetDesktopWdg_State_Stand_ShakeHead},
    {PetDesktopWdg_State_Stand_ShakeHead,   PetDesktopWdg_Play_Done,    PetDesktopWdg_State_Stand},
    {PetDesktopWdg_State_Stand,             PetDesktopWdg_Gesture_Down, PetDesktopWdg_State_LieDown},
    {PetDesktopWdg_State_LieDown,           PetDesktopWdg_Play_Done,    PetDesktopWdg_State_Lying},
    {PetDesktopWdg_State_Lying,             PetDesktopWdg_Gesture_Up,   PetDesktopWdg_State_StandUp},
    {PetDesktopWdg_State_StandUp,           PetDesktopWdg_Play_Done,    PetDesktopWdg_State_Stand},
    {PetDesktopWdg_State_Lying,             PetDesktopWdg_Gesture_Z,    PetDesktopWdg_State_Lying_Tumble},
    {PetDesktopWdg_State_Lying_Tumble,      PetDesktopWdg_Gesture_Z,    PetDesktopWdg_State_Lying_Tumble},
    {PetDesktopWdg_State_Lying,             PetDesktopWdg_Play_Done,    PetDesktopWdg_State_Lying},
    {PetDesktopWdg_State_Lying,             PetDesktopWdg_Gesture_Down, PetDesktopWdg_State_Lying_Bark},
    {PetDesktopWdg_State_Lying_Bark,        PetDesktopWdg_Gesture_Down, PetDesktopWdg_State_Lying_Bark},
    {PetDesktopWdg_State_Lying_Bark,        PetDesktopWdg_Play_Done,    PetDesktopWdg_State_Lying},
    //{PetDesktopWdg_State_Lying,             PetDesktopWdg_TimeUp,       PetDesktopWdg_State_Lie_Sleep},
    {PetDesktopWdg_State_Lie_Sleep,         PetDesktopWdg_Gesture_Up,   PetDesktopWdg_State_Sleep_Stand},
    {PetDesktopWdg_State_Lie_Sleep,         PetDesktopWdg_Gesture_Z,    PetDesktopWdg_State_Sleep_Stand},
    {PetDesktopWdg_State_Lie_Sleep,         PetDesktopWdg_Gesture_Click,PetDesktopWdg_State_Sleep_Stand},
    {PetDesktopWdg_State_Sleep_Stand,       PetDesktopWdg_Play_Done,    PetDesktopWdg_State_Stand},
    //{PetDesktopWdg_State_Stand,             PetDesktopWdg_TimeUp,       PetDesktopWdg_State_Bubble_Stand},
    {PetDesktopWdg_State_Bubble_Stand,      PetDesktopWdg_Play_Done,    PetDesktopWdg_State_Stand},
    {PetDesktopWdg_State_Stand_Touch,       PetDesktopWdg_Play_Done,    PetDesktopWdg_State_Touch_Lie},
    {PetDesktopWdg_State_Stand_Touch,       PetDesktopWdg_Gesture_Click,    PetDesktopWdg_State_Touch_Lie},

#else // #ifdef PETDESTOPWDG_MULTIIMAGE
	{PetDesktopWdg_State_Stand,  		    PetDesktopWdg_Gesture_Down,    PetDesktopWdg_State_LieDown},
	{PetDesktopWdg_State_Lying,			    PetDesktopWdg_Gesture_Down,    PetDesktopWdg_State_Lying_Bark},
	{PetDesktopWdg_State_Stand,    			PetDesktopWdg_Gesture_Z,    PetDesktopWdg_State_Stand_ShakeHead},
#ifndef PETDESTOPWDG_REVISION_ONE
	{PetDesktopWdg_State_Lying,   		    PetDesktopWdg_Gesture_Z,    PetDesktopWdg_State_Lying_ShakeHead},
#endif
	{PetDesktopWdg_State_Stand_ShakeHead,		PetDesktopWdg_Gesture_Z,    PetDesktopWdg_State_Stand_ShakeHead},
#ifndef PETDESTOPWDG_REVISION_ONE
	{PetDesktopWdg_State_Lying_ShakeHead,		PetDesktopWdg_Gesture_Z,    PetDesktopWdg_State_Lying_ShakeHead},
#endif
	{PetDesktopWdg_State_Stand_Tumble,            PetDesktopWdg_Gesture_Z,    PetDesktopWdg_State_Stand_Tumble},
	{PetDesktopWdg_State_Lying_Tumble,            PetDesktopWdg_Gesture_Z,    PetDesktopWdg_State_Lying_Tumble},
	{PetDesktopWdg_State_Stand,             PetDesktopWdg_Gesture_Up,    PetDesktopWdg_State_Erect},
	{PetDesktopWdg_State_Lying,             PetDesktopWdg_Gesture_Up,    PetDesktopWdg_State_StandUp},
	{PetDesktopWdg_State_Erect,             PetDesktopWdg_Gesture_Up,    PetDesktopWdg_State_Erect},
	//{PetDesktopWdg_State_Tumble,   			PetDesktopWdg_Gesture_Up,    PetDesktopWdg_State_Lying},
	{PetDesktopWdg_State_Stand,             PetDesktopWdg_Gesture_C,     PetDesktopWdg_State_Stand_Tumble},
	{PetDesktopWdg_State_Lying,             PetDesktopWdg_Gesture_C,    PetDesktopWdg_State_Lying_Tumble},
	//{PetDesktopWdg_State_SitDown,   		PetDesktopWdg_Gesture_Click, PetDesktopWdg_State_Stand},
	//{PetDesktopWdg_State_Sleep,			    PetDesktopWdg_Gesture_Click, PetDesktopWdg_State_Lying},

	//{PetDesktopWdg_State_Stand,  		    PetDesktopWdg_Play_Done,    PetDesktopWdg_State_Stand},
	//{PetDesktopWdg_State_Lying,			    PetDesktopWdg_Play_Done,    PetDesktopWdg_State_Lying},
	{PetDesktopWdg_State_LieDown,   		PetDesktopWdg_Play_Done,    PetDesktopWdg_State_Lying},
	{PetDesktopWdg_State_StandUp,   		PetDesktopWdg_Play_Done,    PetDesktopWdg_State_Stand},
	{PetDesktopWdg_State_Stand_ShakeHead,  		PetDesktopWdg_Play_Done,    PetDesktopWdg_State_Stand},
	{PetDesktopWdg_State_Stand_Tumble,  		PetDesktopWdg_Play_Done,    PetDesktopWdg_State_Lying},
	{PetDesktopWdg_State_Erect,  		    PetDesktopWdg_Play_Done,    PetDesktopWdg_State_Stand},
	//{PetDesktopWdg_State_Sleep,			PetDesktopWdg_Play_Done,    PetDesktopWdg_State_Lying},
	{PetDesktopWdg_State_Lying_Bark,	    PetDesktopWdg_Play_Done,    PetDesktopWdg_State_Lying},
#ifndef PETDESTOPWDG_REVISION_ONE
	{PetDesktopWdg_State_Lying_ShakeHead,	    PetDesktopWdg_Play_Done,    PetDesktopWdg_State_Lying},
#endif
	{PetDesktopWdg_State_Lying_Tumble,	        PetDesktopWdg_Play_Done,    PetDesktopWdg_State_Lying},
#ifdef PETDESTOPWDG_REVISION_ONE
	{PetDesktopWdg_State_Stand,  		    PetDesktopWdg_TimeUp,    PetDesktopWdg_State_Stand_Bubble_R},
	{PetDesktopWdg_State_Stand,  		    PetDesktopWdg_TimeUp,    PetDesktopWdg_State_Stand_Bubble_L},
	{PetDesktopWdg_State_Stand_Bubble_R,  		    PetDesktopWdg_Play_Done,    PetDesktopWdg_State_Bubble_Stand_R},
	{PetDesktopWdg_State_Stand_Bubble_L,  		    PetDesktopWdg_Play_Done,    PetDesktopWdg_State_Bubble_Stand_L},
	{PetDesktopWdg_State_Bubble_Stand_R,  		    PetDesktopWdg_Play_Done,    PetDesktopWdg_State_Stand},
	{PetDesktopWdg_State_Bubble_Stand_L,  		    PetDesktopWdg_Play_Done,    PetDesktopWdg_State_Stand},
	{PetDesktopWdg_State_Stand,  		    PetDesktopWdg_Gesture_Click,    PetDesktopWdg_State_Stand_Touch},
	{PetDesktopWdg_State_Stand_Touch,  		    PetDesktopWdg_Play_Done,    PetDesktopWdg_State_Touch_Lie},
	{PetDesktopWdg_State_Touch_Lie,  		    PetDesktopWdg_Play_Done,    PetDesktopWdg_State_Lying},
	{PetDesktopWdg_State_Lying,                      PetDesktopWdg_TimeUp,                PetDesktopWdg_State_Lie_Sleep},
	{PetDesktopWdg_State_Lie_Sleep,                      PetDesktopWdg_Gesture_Click,                PetDesktopWdg_State_Sleep_Stand},
	{PetDesktopWdg_State_Sleep_Stand,                      PetDesktopWdg_Play_Done,                PetDesktopWdg_State_Stand},
#endif

#endif // #endif PETDESTOPWDG_MULTIIMAGE

};


typedef struct
{
	DECLARE_BASECLASS_DESKTOPWIDGET

    u8  nAnimationPhase;
    u8  nAnimFrameIdx;
    u8  nRepeatTimes;
    PetDesktopWdg_State_e eCurState;
    //PetDesktopWdg_State_e eNextState;
    PetDesktopWdg_Event_e   eInputEvent;
	s16				nTS_PressPosX;
	s16				nTS_PressPosY;
	s16				nTS_CurrentX;
	s16				nTS_CurrentY;

    s16             nTS_MaxRightX;
    s16             nTS_MaxRightY;
    s16             nTS_MaxLeftX;
    s16             nTS_MaxLeftY;
    s16             nTS_MaxTopX;
    s16             nTS_MaxTopY;
    s16             nTS_MaxBottonX;
    s16             nTS_MaxBottonY;

    s16             nTS_Dir1OffsetX;
    s16             nTS_Dir2OffsetX;
    s16             nTS_Dir3OffsetX;
    boolean         bGestureUpRecognized;
    boolean         bGestureDownRecognized;

    boolean         bTimerRunning;
#ifdef PETDESTOPWDG_REVISION_ONE
    boolean         bTimeUpTimerRunning;
    boolean         bSuspend;
#endif
} PetDesktopWdg_t;

#endif //__GADGETS_MMI_PET__
#endif // defined(__GADGETS_MMI__) || defined(__3D_UI_IDLE_GADGETBAR__)
#endif //__MMI_WDG_PETDESKTOP_PRIV_H__
/*=============================================================*/
// end of file
