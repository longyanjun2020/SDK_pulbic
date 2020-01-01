/**
 * @file mmi_emuapp_keypad.h
 *
 * EmuApp Keypad Object
 */

#ifndef __MMI_EMUAPP_KEYPAD_H__
#define __MMI_EMUAPP_KEYPAD_H__

/*=============================================================*/
// Include files
/*=============================================================*/
#include "mmi_wdg_headers.h"
#include "mmi_mae_touchsrv_types.h"

/*=============================================================*/
// Macro definition
/*=============================================================*/
#define EMUAPP_VIRTUAL_KEYPAD_OBJ_BASE_ELEMENT \
    EmuAppVirtualKeypadEventHandle pfnEventHandle; \
    u32 nObjType; \
    Point_t tRegionP1; \
    Point_t tRegionP2; \
    EmuAppVirtualKeypadObjState_e eState; \
    u32 nObjID; \
    u32 nActiveCounter

#define EMUAPP_VIRTUAL_KEYPAD_OBJ_GET_TYPE(__ObjBase)   ((__ObjBase)->nObjType)
#define EMUAPP_VIRTUAL_KEYPAD_OBJ_GET_STATE(__ObjBase)  ((__ObjBase)->eState)
#define EMUAPP_VIRTUAL_KEYPAD_OBJ_GET_ID(__ObjBase)     ((__ObjBase)->nObjID)

#define EMUAPP_VIRTUAL_KEYPAD_ACTIVE_OBJ_NULL_ID        (0xFFFF)
#define EMUAPP_VIRTUAL_KEYPAD_POINT_NULL_ID             (0xFF)
#define EMUAPP_VIRTUAL_KEYPAD_ACTIVE_COUNTER_UNSET      (0xFF)
#define EMUAPP_VIRTUAL_KEYPAD_POINT_NULL_POSITION       (-1)

#define EMUAPP_TS_MULTI_TOUCH_MAX_TOUCH     (MAE_TS_MAX_TOUCH)

#define EMUAPP_TS_FOCUSED_KEYPAD_DISPLACEMENT_THRESHOLD (20)    // 40 pixel

/*=============================================================*/
// Data type definition
/*=============================================================*/
typedef boolean (*EmuAppVirtualKeypadEventHandle)(void *pApplet, u32 nEvtCode, u32 nParam1, u32 nParam2, void *pObj);

enum
{
    EMU_VIRTUAL_KEYPAD_TYPE_BUTTON = 0,
    EMU_VIRTUAL_KEYPAD_TYPE_JOYSTICK,
    EMU_VIRTUAL_KEYPAD_TYPE_MAX
};

typedef enum
{
    EMU_VIRTUAL_KEYPAD_OBJ_STATE_ACTIVE = 0,
    EMU_VIRTUAL_KEYPAD_OBJ_STATE_INACTIVE,
    EMU_VIRTUAL_KEYPAD_OBJ_STATE_MAX
} EmuAppVirtualKeypadObjState_e;

typedef struct _EMU_VIRTUAL_KEYPAD_FINGER_INFO_TAG_
{
    struct MultiTouchData_t_ tPoint[MAE_TS_MAX_TOUCH];
    u32 nActiveKeypadObjID[MAE_TS_MAX_TOUCH];
} EmuAppVirtualKeypadFingerInfo_t;

typedef struct _EMU_VIRTUAL_KEYPAD_BASE_TAG_
{
    EMUAPP_VIRTUAL_KEYPAD_OBJ_BASE_ELEMENT;
} EmuAppVirtualKeypadBase_t;

typedef struct _EMU_VIRTUAL_KEYPAD_BUTTON_TAG_
{
    EMUAPP_VIRTUAL_KEYPAD_OBJ_BASE_ELEMENT;
    IWidget *pWdgImg;
} EmuAppVirtualKeypadButton_t;

typedef struct _EMU_VIRTUAL_KEYPAD_JOYSTICK_TAG_
{
    EMUAPP_VIRTUAL_KEYPAD_OBJ_BASE_ELEMENT;
    IWidget *pWdgCtnrJoystick;
    IWidget *pWdgImgJoystick;
    Point_t tCenter;
    u32 nRadiusInnerBound;
    u32 nRadiusOuterBound;
} EmuAppVirtualKeypadJoystick_t;

/*=============================================================*/
// Variable definition
/*=============================================================*/

/*=============================================================*/
// Global function definition
/*=============================================================*/

/**
 * @name    EmuAppVirtualKeypadButtonHandle
 * @brief   Keypad object button's event handler
 * @param   pApplet             app data
 * @param   nEvtCode            touch event
 * @param   nParam1             touch event param1 from MAE
 * @param   nParam2             touch event param2 from MAE
 * @param   pKeypadObj          the keypad object to handle this event
 */
boolean EmuAppVirtualKeypadButtonHandle(void *pApplet, u32 nEvtCode, u32 nParam1, u32 nParam2, void *pKeypadObj);

/**
 * @name    EmuAppVirtualKeypadJoystickHandle
 * @brief   Keypad object joystick's event handler
 * @param   pApplet             app data
 * @param   nEvtCode            touch event
 * @param   nParam1             touch event param1 from MAE
 * @param   nParam2             touch event param2 from MAE
 * @param   pKeypadObj          the keypad object to handle this event
 */
boolean EmuAppVirtualKeypadJoystickHandle(void *pApplet, u32 nEvtCode, u32 nParam1, u32 nParam2, void *pKeypadObj);

/**
 * @name    EmuAppVirtualKeypadObjInit
 * @brief   Initilize keypad object
 * @param   pApplet             app data
 * @param   tP1                 the left-top point of this keypad object
 * @param   tP2                 the right-bottom point of this keypad object
 * @param   nObjID              the keypad object's ID
 * @param   nObjType            the keypad object's type (button or joystick)
 */
void EmuAppVirtualKeypadObjInit(void *pApplet, Point_t tP1, Point_t tP2, u32 nObjID, u32 nObjType);

/**
 * @name    EmuAppCalculateDistanceWithKeypadObj
 * @brief   Calculate the distance between the indicated point(x, y) and keypad object
 * @param   pApplet             app data
 * @param   nX                  the indicated point's x-coordinate
 * @param   nY                  the indicated point's y-coordinate
 * @param   pKeypadObj          the indicated keypad object
 */
u32 EmuAppCalculateDistanceWithKeypadObj(void *pApplet, s32 nX, s32 nY, EmuAppVirtualKeypadBase_t *pKeypadObj);

/**
 * @name    EmuAppVirtualKeypadGetActiveKeypadObjectNum
 * @brief   Calculate the active keypad object number in the finger info
 * @param   pApplet             app data
 */
u32 EmuAppVirtualKeypadGetActiveKeypadObjectNum(void *pApplet);

/**
 * @name    EmuAppTSReleaseAllKeypadObject
 * @brief   Send a release event to each keypad object with active counter larger than 0
 * @param   pApplet             app data
 */
void EmuAppTSReleaseAllKeypadObject(void *pApplet);

/**
 * @name    EmuAppTSSendEventToEachKeypadObject
 * @brief   Send a touch screen event to each keypad object
 * @param   pApplet             app data
 * @param   nEvt                touch screen event
 * @param   nX                  event point's x-coordinate
 * @param   nY                  event point's y-coordinate
 * @param   bHandleOnce         TRUE: if this event is handled by one keypad object, stop to send to reminded keypad objects
 *                              FALSE: send to all keypad objects
 * @param   bUpdateFingerInfo   TRUE: update finger info
 *                              FALSE: don't update finger info
 * @param   nID                 point ID, for update finger info
 * @param   nUpdateIndex        finger info array index, for update finger info
 * @param   nActiveCounter      to reset keypad objects's active counter or not
 */
boolean EmuAppTSSendEventToEachKeypadObject(void *pApplet, u32 nEvt, s32 nX, s32 nY, boolean bHandleOnce, boolean bUpdateFingerInfo, u8 nID, u32 nUpdateIndex, u32 nActiveCounter);

/**
 * @name    EmuAppTSSendEventToOneKeypadObject
 * @brief   Send a touch screen event to the indicated keypad object
 * @param   pApplet         app data
 * @param   nEvt            touch screen event
 * @param   nParam1         touch event param1 from MAE
 * @param   nParam2         touch event param2 from MAE
 * @param   nKeypadID       the keypad object's ID to handle this event
 * @param   nActiveCounter  to reset keypad object's active counter or not
 */
boolean EmuAppTSSendEventToOneKeypadObject(void *pApplet, u32 nEvt, u32 nParam1, u32 nParam2, u32 nKeypadID, u32 nActiveCounter);

/**
 * @name    EmuAppTSUpdateFingerInfo
 * @brief   Update one finger info
 * @param   pApplet         app data
 * @param   nUpdateIndex    finger info index to be update
 * @param   nX              finger's x-coordinate
 * @param   nY              finger's y-coordinate
 * @param   nID             point ID
 * @param   nKeypadID       keypad object ID which is focused by this finger
 */
void EmuAppTSUpdateFingerInfo(void *pApplet, u8 nUpdateIndex, s32 nX, s32 nY, u8 nID, u32 nKeypadID);

/**
 * @name    EmuAppTSResetFingerInfo
 * @brief   Reset all finger info
 * @param   pApplet         app data
 * @param   nResetIndex     finger info index to be reset
 */
void EmuAppTSResetFingerInfo(void *pApplet, u8 nResetIndex);

#endif // __MMI_EMUAPP_KEYPAD_H__

