#ifndef __MMI_MAE_TRANSITION_H__
#define __MMI_MAE_TRANSITION_H__

#include "mmi_mae_common_def.h"
#include "mmi_mae_forward.h"
#include "mmi_mae_graphic_forward.h"
#include "mmi_mae_graphic_types.h"

/* enum for TransitionType_t */
enum
{
	TRANSITION_FLY = 0,    ///< up, down, left, right
	TRANSITION_PUSH,       ///< up, down, left, right
	TRANSITION_FADE,       ///< no direction
	TRANSITION_BLINDS,     ///< up, down, left, right
	TRANSITION_DISSOLVE,   ///< not support yet
	TRANSITION_IRIS,       ///< in and out
	TRANSITION_FLASH,      ///< no direction
	TRANSITION_BARN,       ///< in and out
	TRANSITION_INSERT,     ///< not support yet
	TRANSITION_STRETCH,    ///< in and out
	TRANSITION_SPIRAL,     ///< not support yet
	TRANSITION_ZIGZAG,     ///< not support yet
	TRANSITION_STRIPS,     ///< not support yet
	TRANSITION_SQUEEZE,    ///< not support yet
	TRANSITION_ZOOM,       ///< not support yet
	TRANSITION_ROTATE,     ///< not support yet
	TRANSITION_FLIPPAPER,    ///< not support yet
    TRANSITION_FLIPOVER,     ///< not support yet
    TRANSITION_ROLLING,		///< up, down, left, right
    TRANSITION_REND,		///<
    TRANSITION_DOOR,
#if defined(__UI_STYLE_MMI_IFONE__) || defined(__UI_STYLE_MMI_ANDROID_IDLE__) || defined (__UI_STYLE_MMI_STYLE_SWITCH__)
	TRANSITION_IPHONE,      ///Add for Ifone style ui
#endif
    TRANSITION_SLIP,

	// TRANSLUCENT type transition, only transition main widget
	TRANSITION_TRANSLUCENT_TYPE_START,
	TRANSITION_TRANSLUCENT_PUSH = TRANSITION_TRANSLUCENT_TYPE_START,	///< push effect, up, down, left, right
	TRANSITION_TRANSLUCENT_FADEOUT_PUSH,	///< push and fadeout old frame effect, up, down, left, right
	TRANSITION_TRANSLUCENT_FLIPOVER,	///< flip effect, left, right, up, down
	TRANSITION_TRANSLUCENT_TYPE_END = TRANSITION_TRANSLUCENT_FLIPOVER,
	// end of TRANSLUCENT type

	TRANSITION_TOTAL
};
typedef u16 TransitionType_t;

/* enum for TransitionDirection_t */
enum
{
	TRANDIR_UP,
	TRANDIR_DOWN,
	TRANDIR_LEFT,
	TRANDIR_RIGHT,

	TRANDIR_IN,
	TRANDIR_OUT,
#if defined(__UI_STYLE_MMI_IFONE__) || defined(__UI_STYLE_MMI_ANDROID_IDLE__) || defined (__UI_STYLE_MMI_STYLE_SWITCH__)
	TRANDIR_STOP,            ///Add for Ifone style ui
#endif

	TRANDIR_TOTAL
};
typedef u16 TransitionDirection_t;

#if defined(__UI_STYLE_MMI_IFONE__) || defined (__UI_STYLE_MMI_ANDROID_IDLE__) || defined (__UI_STYLE_MMI_STYLE_SWITCH__)

enum
{
	WIDGET_NONE,
	FIRST_WIDGET_LEFT,
	SECOND_WIDGET_LEFT,
	THIRD_WIDGET_LEFT,

	FIRST_WIDGET_RIGHT,
	SECOND_WIDGET_RIGHT,
	THIRD_WIDGET_RIGHT,

	WIDGET_TOTAL
};
typedef u16 TransitionChildWdgExist_t;

#endif /*#ifdef __UI_STYLE_MMI_IFONE__*/ /* for ifone style ui end */
/*
	extra data for TRANSITION_ZOOM
*/
typedef struct
{
	Rect_t tExtRegion;    ///<   in=>start region; out=>end region
}TransitionZoomData_t;

/* structure of transition parameter */
typedef struct
{
	TransitionType_t TransitType;       ///< Transition type
	TransitionDirection_t TransitDir;   ///< Transition direction
	u8 nTotalSteps;           ///< Transition steps(frames)
	Rect_t tTransitRegion;    ///< Transition region
	union
	{
		TransitionZoomData_t  tZoom;
	}uExtraData;
}TransitionParam_t;


#endif /* __MAE_TRANSITION_H__ */
