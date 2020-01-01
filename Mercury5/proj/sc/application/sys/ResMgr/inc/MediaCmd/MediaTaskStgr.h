/**
* @file MediaTaskStgr.h
*
* This header file defines the interfaces of media task command
* tStgr
*/

#ifndef __MEDIATASKSTGR_H__
#define __MEDIATASKSTGR_H__

/*=============================================================*/
// Include Files
/*=============================================================*/
#include "MediaTaskStgrItf.h"
#include "ListenerItf.h"
#include "MediaCmd.h"
#include "mediacmn.h"
#include "MediaTaskClientMgrItf.h"
#include "DListItf.h"
/*=============================================================*/
// Macro Definitions
/*=============================================================*/

/*=============================================================*/
// Type Declarations
/*=============================================================*/
typedef MediaExecCheckRes_e (*MediaTaskStgr_CheckResConflict)(CmdMgrStgrHdl_t pStgrHdl, ResMgr_CmdHdl_t pCurCmdHdl);

typedef struct MediaTaskStgr_CheckConflict_t_
{
    MediaTaskStgr_CheckResConflict DirectResConflict;
    MediaTaskStgr_CheckResConflict IndirectResConflict;
} MediaTaskStgr_CheckConflict_t;

typedef struct MediaTaskStgr_t_
{
    ResMgr_TaskStgr_t tTaskStgr;
    ListenerHdl_t pCmdListenerHdl;
    ResCtrlHandle_t pMmpResCtrlHdl;
    ResCtrlHandle_t pChanResCtrlHdl;
    ResCtrlHandle_t pPseduoDevResCtrlHdl;
    struct
    {
        ResCtrlHandle_t pMmpResCtrl;
        ResCtrlHandle_t pChanResCtrl;
        ResCtrlHandle_t pPseduoDevResCtrl;
    } tConflictResCtrls;
    struct
    {
        MediaCmd_t *pFindCmd;
        ResMgr_AppId_e eAppId;
        MediaCmdType_e eFindCmdType;
        MediaCmdActType_e eActType;
        MediaResInfo_e eResInfo;
        MediaCmdFindOpt_e eFindOpt;
    } tFindCmdParams;
    struct
    {
        ResMgr_AppId_e eAppId;
        AudPath_e ePath;
    } tSyncPrefPathCmdParams;
    DList_t *pPrefPathList;
    MediaTaskClientMgr_t *pMediaClientMgr;
    Media_Capability_t tMediaCap;
    struct
    {
        AudPath_e ePath;
        AudChannel_e eChannel;
        MediaConfigParm_t tConfigParm;
        MediaARPConfigParm_t tARPConfigParm;
    } tMediaEnvInfo;
    struct
    {
        void *pRspData;
        bool bRestart;
    } tBtA2dpInfo;
    struct
    {
        bool bBtStatusChg;
        DevMedType_e eLastConnectedDevice;
    } tDevStatusChgParams;
    struct
    {
        ResMgr_AppId_e eAppId;
    } tFinalizeParams;
    struct
    {
        ResMgr_AppId_e eAppId;
    } tForceResumeParams;
    struct
    {
        u8 *pVolume;
        u8 *pRange;
    } tSyncBackgroundParams;
    struct
    {
        ResMgr_AppId_e eAppId;
        AudChannel_e eChannel;
    } tTransverseParams;
    struct
    {
        bool bIsVisitCurCmd;
    } tCheckPriCmdParams;
    struct
    {
        MediaCmd_t *pMergeCmd;
    } tMergeCmdParams;
    struct
    {
        u8 nOutputType;
        MediaCmd_t *pPlayCmd;
        MediaCmd_t *pMasterCmd;
        u8 nIsAudPaused;
        void *pAudCb;
        u16 nAudCbSize;
    } tRestartResume;
    struct
    {
        bool bIsHWScalarOccupied;
    } tCheckHWScalarParams;
} MediaTaskStgr_t;

/*=============================================================*/
// Function Declarations
/*=============================================================*/

#endif //__MEDIATASKSTGR_H__

