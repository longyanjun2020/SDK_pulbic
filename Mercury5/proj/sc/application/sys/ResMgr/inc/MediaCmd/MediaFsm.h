/**
* @file MediaFsm.h
*
* This header file defines the APIs of media state machines
*
*/

#ifndef __MEDIAFSM_H__
#define __MEDIAFSM_H__

/*=============================================================*/
// Include Files
/*=============================================================*/
#include "ResMgr_Common.h"
#include "MediaFsmItf.h"
#include "MediaCmdItf.h"
#include "StateMachineItf.h"

/*=============================================================*/
// Macro Definitions
/*=============================================================*/

/*=============================================================*/
// Type Declarations
/*=============================================================*/
typedef enum MediaStateMachineType_e_
{
    MEDIA_FSM__AUDIO,
    MEDIA_FSM__AUDIO_REC,
    MEDIA_FSM__AUDIO_VOC,
    MEDIA_FSM__VIDEO,
    MEDIA_FSM__CAMERA,
    MEDIA_FSM__FM_RADIO,
    MEDIA_FSM__USB,
    MEDIA_FSM__TV,
    MEDIA_FSM__CODEC,
    MEDIA_FSM__VFS,
    MEDIA_FSM__VDOCHAT,
    MEDIA_FSM__GPS,
    MEDIA_FSM__AUDIO_DEV_CTRL,
    MEDIA_FSM__FM_RADIO_DEV_CTRL,
    MEDIA_FSM__VIDEO_DEV_CTRL,
    MEDIA_FSM__CAMERA_DEV_CTRL,
    MEDIA_FSM__USB_DEV_CTRL,
    MEDIA_FSM__CODEC_CTRL,
    MEDIA_FSM__VTM,
    MEDIA_FSM__NUM
} MediaStateMachineType_e;

typedef struct MediaStateMachine_t_
{
    StateMachine_t tCmdStMachine;
    MediaStateMachineType_e eType;
    bool bWaitRsp;
    bool bFromInitState;
    bool bSeekFromPause;
    u32 uStateData;
} MediaStateMachine_t;

typedef struct MediaFsmCreator_t_
{
    InitStateMachine InitFSM;
    UninitStateMachine UninitFSM;
    GenericState_AcceptAct AcceptAct;
} MediaFsmCreator_t;

/*=============================================================*/
// Function Declarations
/*=============================================================*/

#endif //__MEDIAFSM_H__

