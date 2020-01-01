/**
 * @file mae_gestureengine.h
 *
 * @brief  the gesture engine for recognition
 *
 * @version $Id: mae_gestureengine.h 2010-06-30 12:00:00z $
 */

#ifndef __MAE_GESTUREENGINE_H__
#define __MAE_GESTUREENGINE_H__
//////////////////////////////////////////////////////////////////////////
//==========Includes=======================
#include "mmi_mae_common_def.h"
//////////////////////////////////////////////////////////////////////////
//==========Types&Data=====================
typedef enum {
    GESTURE_SLIDE_UP,
    GESTURE_SLIDE_DOWN,
    GESTURE_SLIDE_LEFT,
    GESTURE_SLIDE_RIGHT,
    GESTURE_CLICK,
    GESTURE_DBCLICK,
    GESTURE_HOLD,
    GESTURE_PINCH_IN,
    GESTURE_PINCH_OUT,
    GESTURE_ROTATE_CKW,
    GESTURE_ROTATE_ACKW,
    GESTURE_DBL_SLIDE_UP,
    GESTURE_DBL_SLIDE_DOWN,
    GESTURE_DBL_SLIDE_LEFT,
    GESTURE_DBL_SLIDE_RIGHT,
    GESTURE_MT_NAVIGATE,
    GESTURE_UNDEF
}GestureType_e;

#define GESTURE_HW_RECOG	0		//hardware recog
#define GESTURE_SW_RECOG	1		//software recog


/*
#define MAX_TOUCH_POINT_SUPPORT 2	//finger number
typedef struct
{
    u16 Row;
	u16 Col;
} vm_TouchPoint_t;

typedef struct
{
    u8       function;
    u8       KeyMode;         //< Key mode define: 1: touch release 2: touch press
    u8       FingerNum;       //< Finger number (0,1,2)
    vm_TouchPoint_t point[MAX_TOUCH_POINT_SUPPORT];
} vm_Touchscreen_info_t;
*/
typedef union
{
    u32 GestureInfo;
    float fDistance;
    float fAngle;
}GestureInfo_t;

typedef void* HRECOG;
typedef int (*PFN_Recognize)(HRECOG hRecog);


HRECOG engine_init(PFN_Recognize pfnRecogCB, void *data);
void engine_uninit(HRECOG  hRecog);

#endif //__MAE_GESTUREENGINE_H__

