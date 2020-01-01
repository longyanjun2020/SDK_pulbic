////////////////////////////////////////////////////////////////////////////////
//
// Copyright (c) 2006-2009 MStar Semiconductor, Inc.
// All rights reserved.
//
// Unless otherwise stipulated in writing, any and all information contained
// herein regardless in any format shall remain the sole proprietary of
// MStar Semiconductor Inc. and be kept in strict confidence
// (¡§MStar Confidential Information¡¨) by the recipient.
// Any unauthorized act including without limitation unauthorized disclosure,
// copying, use, reproduction, sale, distribution, modification, disassembling,
// reverse engineering and compiling of the contents of MStar Confidential
// Information is unlawful and strictly prohibited. MStar hereby reserves the
// rights to any and all damages, losses, costs and expenses resulting therefrom.
//
////////////////////////////////////////////////////////////////////////////////

/**
* @file    srv_resmgr_mmlgame_types.h
* @version
* @brief
*
*/

#ifndef __SRV_RESMGR_MMLGAME_TYPES_H__
#define __SRV_RESMGR_MMLGAME_TYPES_H__

#ifdef __cplusplus
extern "C" {
#endif

#if defined (__SDK_SIMULATION__)
#define __packed
#endif

/** @defgroup MMLayerGame Game
    EMU Game
    @{
*/
    /** @defgroup MMLayerGameEmuGame EMU Game
        EMU Game
        @{
    */
    /** @} */

/** @} */

/*=============================================================*/
// Include files
/*=============================================================*/
#include "srv_resmgr_mml_forward.h"
#include "vm_types.ht"
#include "srv_resmgr_mmlcommon_types.h"

/*=============================================================*/
// Extern definition
/*=============================================================*/

/*=============================================================*/
// Macro definition
/*=============================================================*/

/*=============================================================*/
// Data type definition
/*=============================================================*/
/** @ingroup    MMLayerGame
    @brief      Use case IDs
*/
opaque_enum(MmlUseCaseGameId_e_)
{
    /* Game Init */
    MML_UCID_GAME_INIT_BASE = MML_GET_UCID_INIT_BASE(MML_UCGID_GAME),
    MML_UCID_GAME_REG_NOTIFY_CALLBACK = MML_UCID_GAME_INIT_BASE,            ///< 00050000 = Reg notify callback
    MML_UCID_GAME_UNREG_NOTIFY_CALLBACK,                                    ///< 00050001 = Unreg notify callback
    MML_UCID_GAME_INIT_CATEGORY,

    /* Game Get */
    MML_UCID_GAME_GET_BASE = MML_GET_UCID_GET_BASE(MML_UCGID_GAME),
    MML_UCID_GAME_GET_GAME_INFO = MML_UCID_GAME_GET_BASE,                   ///< 00050100 = Get game info
    MML_UCID_GAME_GET_GAME_CAPABILITY,                                      ///< 00050101 = Get game capability
    MML_UCID_GAME_GET_CATEGORY,

    /* Game Set */
    MML_UCID_GAME_SET_BASE = MML_GET_UCID_SET_BASE(MML_UCGID_GAME),
    MML_UCID_GAME_SEND_KEY_EVENT = MML_UCID_GAME_SET_BASE,                  ///< 00050200 = Send key event
    MML_UCID_GAME_CLEAN_UP,                                                 ///< 00050201 = Clean up game status save by middleware
    MML_UCID_GAME_SET_CATEGORY,

    /* Game Execute */
    MML_UCID_GAME_EXECUTE_BASE = MML_GET_UCID_EXE_BASE(MML_UCGID_GAME),
    MML_UCID_GAME_START_GAME = MML_UCID_GAME_EXECUTE_BASE,                  ///< 00050300 = Start game
    MML_UCID_GAME_STOP_GAME,                                                ///< 00050301 = Stop game
    MML_UCID_GAME_PAUSE_GAME,                                               ///< 00050302 = Pause game
    MML_UCID_GAME_RESUME_GAME,                                              ///< 00050303 = Resume game
    MML_UCID_GAME_EXECUTE_CATEGORY,

    /* Force ID to be at least 32-bits */
    MML_UCID_GAME_FORCE_U32 = 0x7FFFFFFF
};

/** @ingroup    MMLayerGame
    @brief      Response results
*/
typedef enum
{
    /* Common */
    GAME_ERROR_SUCCESS = 0,
    GAME_ERROR_FAIL,
    GAME_ERROR_PARAMETER_INVALID,
    GAME_ERROR_STATE_CHANGE,
    GAME_ERROR_ACCEPT,
    GAME_ERROR_IGNORE,
    GAME_ERROR_REJECT,
    GAME_ERROR_MEMORY_FAILURE,
    /* EMU Game */
    GAME_ERROR_OUT_OF_MEMORY,
    GAME_ERROR_DLM_VERSION_MISMATCH,
    GAME_ERROR_ROM_NOT_SUPPORT,
    GAME_ERROR_NO_EMU_ENGINE,
    GAME_ERROR_ROM_OPEN_FAIL,
    GAME_ERROR_ROM_READ_FAIL,
    GAME_ERROR_ROM_SEEK_FAIL,
    GAME_ERROR_LOAD_DLM_FAIL,
    /* */
    GAME_ERROR_NUM
} MmlGameResult_e;

/** @ingroup    MMLayerGame
    @brief      States
*/
typedef enum
{
    GAME_STATE_STOPPED = 0,
    GAME_STATE_PLAYING,
    GAME_STATE_FREEZE,
    /* */
    GAME_STATE_DONTCARE,
    GAME_STATE_NUM
} MmlGameState_e;

/** @ingroup    MMLayerGame
    @brief      Events
*/
typedef enum
{
    /* Common */
    GAME_EVENT_STATE_CHANGE = MML_GET_UCGEVENT_BASE(MML_UCGID_GAME),
    GAME_EVENT_RUNTIME_ERROR,
    /* EMU Game */
    /* */
    GAME_EVENT_DONTCARE,
    GAME_EVENT_ALL,
    GAME_EVENT_NUM
} MmlGameEvent_e;

/** @ingroup    MMLayerGame
    @brief      Game types
*/
typedef enum
{
    GAME_TYPE_EMU = 0,    ///< Game
    GAME_TYPE_UNKNOWN,    ///< Game type is unknown or not supported
    /* */
    GAME_TYPE_NUM
} MmlGameType_e;

/** @ingroup    MMLayerGame
    @brief      Emulator source types
*/
typedef enum
{
    GAME_EMULATOR_FILE = 0,    ///< Emulator from file-based source
    GAME_EMULATOR_MEMORY,      ///< Emulator from in-memory source
    /* */
    GAME_EMULATOR_NUM
} MmlGameEmulatorType_e;

/** @ingroup    MMLayerGame
    @brief      Rotation angles
*/
typedef enum
{
    GAME_ROTATION_0 = 0,
    GAME_ROTATION_90,
    GAME_ROTATION_180,
    GAME_ROTATION_270,
    /* */
    GAME_ROTATION_NUM
} MmlGameRotationAngle_e;

/** @ingroup    MMLayerGame
    @brief      Emulator types
*/
typedef enum
{
    GAME_EMULATOR_ENGINE_TYPE_EMU_8BIT = 0,
    GAME_EMULATOR_ENGINE_TYPE_EMU_16BIT,
    GAME_EMULATOR_ENGINE_TYPE_EMU_16BIT_MINI,
    GAME_EMULATOR_ENGINE_TYPE_NUM
} MmlGameEmulatorEngineType_e;

/** @ingroup    MMLayerGame
    @brief      File-based source
*/
typedef struct
{
    MmlFilenameFormat_e     eFilenameFormat;
    u16                     *pFileName;
    u16  	                nFileNameSize;
} MmlGameFileParam_t;

/** @ingroup    MMLayerGame
    @brief      In-memory source/destination, used to hold input/output data
*/
typedef	struct
{
    u8                      *pBuffer;       ///< Pointer to the data buffer
    u32                     nBufferSize;    ///< Size in bytes of the data buffer
    u32                     nDataSize;      ///< Read/Write size in bytes of data in the data buffer
} MmlGameMemoryParam_t;

/** @ingroup    MMLayerGame
    @brief      Rectangle
*/
typedef struct
{
    u16     nLeft;      ///< x-position of the top left corner of rectangle
    u16     nTop;       ///< y-position of the top left corner of rectangle
    u16     nWidth;     ///< Width of rectangle
    u16     nHeight;    ///< Height of rectangle
} MmlGameRectangle_t;

/** @ingroup    MMLayerGame
    @brief      Game info types
*/
typedef enum
{
    GAME_INFOTYPE_EMUGAMEHASHDATA = 0,    ///< EMU game identification (hash) data
    GAME_INFOTYPE_EMUGAMEVERSION,         ///< EMU game identification (hash) data + EMU game version number
    GAME_INFOTYPE_EMUGAMESTATUSDATASIZE,  ///< EMU game status data size in bytes
    GAME_INFOTYPE_EMUGAMEALL,             ///< All of the EMU game info
} MmlGameInfoType_e;

/** @ingroup    MMLayerGameEmuGame
    @brief      EMU ROM type
*/
typedef enum
{
    GAME_EMULATOR_ROM_TYPE_EMU_8BIT = 0,
    GAME_EMULATOR_ROM_TYPE_EMU_16BIT,
    GAME_EMULATOR_ROM_TYPE_NUM,
    GAME_EMULATOR_ROM_TYPE_UNKNOWN
} MmlGameEmulatorRomType_e;

/** @ingroup    MMLayerGameEmuGame
    @brief      EMU game info
*/
typedef	struct
{
    MmlGameInfoType_e   eInfoType;              ///< Indicate what type of the game info being contained
    u32                 nGameID;                ///< 32-bit game identification (hash) data
    u32                 nGameVersion;           ///< 32-bit game version number
    u32                 nEmulatorVersion;       ///< 32-bit emulator version number
    u32                 nGameStatusDataSize;    ///< 32-bit game status data size in bytes
    MmlGameEmulatorRomType_e    eEmuRomType;
    MmlGameEmulatorEngineType_e eEmuEngineType;
} MmlGameEmuGameInfo_t;

/** @ingroup    MMLayerGame
    @brief      Game info
*/
typedef struct
{
    MmlGameType_e    eType;    ///< What kind of game is this

    /// union of MmlGameGameInfo_t parameters
    union
    {
        MmlGameEmuGameInfo_t   tEmuGameInfo;  ///< Used with GAME_TYPE_EMU
 	} uParam;
} MmlGameGameInfo_t;

/** @ingroup    MMLayerGame
    @brief      State change info
*/
typedef	struct
{
    MmlGameState_e              eState;             ///< The new state after the transition
    MmlGameEvent_e	            eCause;             ///< The cause of state change, if any

    /// union of MmlGameStateChange_t parameters
    union
    {
        MmlGameMemoryParam_t    tGameStatusData;    ///< The game status buffer info
 	} uParam;
} MmlGameStateChange_t;

/** @ingroup    MMLayerGame
    @brief      Notification payload
*/
typedef struct
{
    MmlGameEvent_e	            eEvent;          ///< Specify the event you want to notify
    u32                         nHandle;         ///< 32-bit game handle

    /// union of MmlGameNotify_t parameters
    union
    {
        MmlGameStateChange_t    tStateChange;    ///< Used with GAME_EVENT_STATE_CHANGE event
        MmlGameResult_e         eErrCode;        ///< Used with GAME_EVENT_RUNTIME_ERROR event
 	} uParam;
} MmlGameNotify_t;

/** @ingroup    MMLayerGame
    @brief      Notification callback prototype
    @param      nSenderID      Sender's mailbox ID
    @param      nUserValue     Interface self-reference
    @param      pGameNotify    Pointer to the accompanying notification payload
*/
typedef void (*PfnMmlGameNotifyCallback)(u16 nSenderID, u32 nUserValue, MmlGameNotify_t *pGameNotify);

/** @ingroup    MMLayerGame
    @brief      Notification callback registration structure
*/
typedef struct
{
    u16                         nSenderID;           ///< Sender's mailbox ID
    u32                         nUserValue;          ///< Interface self-reference
    PfnMmlGameNotifyCallback    pfnNotifyCallback;   ///< Callback function your want to register
} MmlGameNotifyCallback_t;

/** @ingroup    MMLayerGame
    @brief      Response callback prototype
    @param      nSenderID        Sender's mailbox ID
    @param      nUserValue       Interface self-reference
    @param      eErrCode         Returned result (error code)
    @param      pGameResponse    Pointer to the returned response payload
*/
struct MmlGameResponse_t_;
typedef void (*PfnMmlGameResponseCallback)(u16 nSenderID, u32 nUserValue, MmlGameResult_e eErrCode, struct MmlGameResponse_t_ *pGameResponse);

/** @ingroup    MMLayerGame
    @brief      Response callback registration structure
*/
typedef struct
{
    u16                           nSenderID;              ///< Sender's mailbox ID
    u32                           nUserValue;             ///< Interface self-reference
    PfnMmlGameResponseCallback    pfnResponseCallback;    ///< Callback function your want to register
} MmlGameResponseCallback_t;

/** @ingroup    MMLayerGame
    @brief      Register notification callback
*/
typedef struct
{
    MmlGameEvent_e             eEvent;             ///< Specify which event you want to handle
    MmlGameNotifyCallback_t    tNotifyCallback;    ///< Registration data specifying the callback function' address
} MmlGameRegNotifyCallback_t;

/** @ingroup    MMLayerGame
    @brief      Get game info
*/
typedef struct
{
    MmlGameEmulatorType_e          eEmulatorType;         ///< Emulator source type
    MmlGameFileParam_t             tGameFileParam;        ///< Specify the filename of the game
    MmlGameInfoType_e              eInfoType;             ///< Indicate what type of the game info to get

    /// union of MmlGameGetGameInfo_t parameters
    union
    {
        MmlGameFileParam_t         tEmulatorFileParam;    ///< Specify the filename of the emulator
        MmlGameMemoryParam_t       tEmulatorMemoryParam;  ///< Specify the emulator buffer
	} uParam;
} MmlGameGetGameInfo_t;

/** @ingroup    MMLayerGame
    @brief      Start game
*/
typedef struct
{
    MmlGameEmulatorType_e          eEmulatorType;         ///< Emulator source type
    MmlGameFileParam_t             tGameFileParam;        ///< Specify the filename of the game
    MmlGameMemoryParam_t           tGameStatusData;       ///< Specify the game status data buffer
    MmlGameRotationAngle_e         eRotationAngle;        ///< 0, 90, 180, 270 degree
    MmlGameRectangle_t             tOutputWindow;         ///< Output window
    u16                            nOutputWindowPitch;    ///< Output window pitch

    /// union of MmlGameStartGame_t parameters
    union
    {
        MmlGameFileParam_t         tEmulatorFileParam;    ///< [in] Specify the filename of the emulator
        MmlGameMemoryParam_t       tEmulatorMemoryParam;  ///< [in] Specify the emulator buffer
	} uParam;
} MmlGameStartGame_t;

/** @ingroup    MMLayerGame
    @brief      Stop game
*/
typedef struct
{
    u32                     nHandle;            ///< [in] 32-bit game handle, used to indicate which game to be stopped
    MmlGameMemoryParam_t    tGameStatusData;    ///< [out] Specify the buffer to store the game status data
} MmlGameStopGame_t;

/** @ingroup    MMLayerGame
    @brief      Send key event
*/
typedef struct MmlGameSendKeyEvent_t_
{
    //u32                     nHandle;          ///< [in] 32-bit game handle, used to indicate which game to reveice
    u16                     nKeyEventMask;    ///< [in] 16-bit key event mask
} MmlGameSendKeyEvent_t;

/** @ingroup    MMLayerGame
    @brief      EMU engine capability
*/
typedef struct
{
    u16 *pEmulatorFileName;
    u32 nEmulatorFileNameLen;
    u32 nMaxRomSize;
    bool bSupported;
    MmlGameEmulatorEngineType_e eEngineType;
} MmlGameEmuCapability_t;

/** @ingroup    MMLayerGame
    @brief      Game capability
*/
typedef struct
{
    MmlGameEmuCapability_t  tEmuCapability[GAME_EMULATOR_ENGINE_TYPE_NUM];
} MmlGameCapability_t;

/** @ingroup    MMLayerGame
    @brief      Get game capability\n
                To make the interface backward compatible, the nVersion
                is used as the version number of interface input.
                Please set nVersion = current version.
*/
typedef struct
{
    u32     nVersion;             ///< Used for backward compatible (Current version = 0x0000, 2010/08/27)
} MmlGameGetGameCapability_t;

/** @ingroup    MMLayerGame
    @brief      Response payload
*/
typedef struct MmlGameResponse_t_
{
    MmlGameState_e              eState;          ///< Current state
    u32                         nHandle;         ///< 32-bit game handle

    /// union of MmlGameResponse_t parameters
	union
	{
        MmlGameStateChange_t    tStateChange;       ///< Used with 'GAME_ERROR_STATE_CHANGE' result
        MmlGameGameInfo_t       tGameInfo;          ///< Used with 'Get game info'
        //MmlGameMemoryParam_t    tGameStatusData;    ///< Used with 'Stop game'
        MmlGameCapability_t     tCapability;        ///< Used with 'Get game capability'
    } uParam;
} MmlGameResponse_t;

/** @ingroup    MMLayerGame
    @brief      Game use case parameters
*/
typedef struct
{
    /* No parameter: '' */

	u32                                nUseCaseID;            ///< Use case ID
	MmlGameResponseCallback_t          *pResponseCallback;    ///< Pointer to the response callback registration data
	MmlGameResponse_t                  *pResponse;            ///< Pointer to the response payload

    /// union of MmlGameUCParam_t parameters
    union
	{
	    u32                           nHandle;               ///< Used with 'Pause game, Resume game,
	    MmlGameGetGameInfo_t          tGetGameInfo;          ///< Used with 'Get game info'
        MmlGameStartGame_t            tStartGame;            ///< Used with 'Start game'
        MmlGameStopGame_t             tStopGame;             ///< Used with 'Stop game'
        MmlGameSendKeyEvent_t         tSendKeyEvent;         ///< Used with 'Send key event'
        MmlGameGetGameCapability_t    tGetGameCapability;    ///< Used with 'Get game capability'
	} uParam;

} MmlGameUCParam_t;
/*=============================================================*/
// Variable definition
/*=============================================================*/

/*=============================================================*/
// Global function definition
/*=============================================================*/

#ifdef __cplusplus
}
#endif

#endif //__SRV_RESMGR_MMLGAME_TYPES_H__
