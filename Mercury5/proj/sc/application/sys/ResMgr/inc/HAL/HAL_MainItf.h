/**
* @file HWL_MainItf.h
*
* This header file defines the interfaces of hardware adaptor layer
* generic APIs
*/

#ifndef __HAL_MAINITF_H__
#define __HAL_MAINITF_H__

/*=============================================================*/
// Include Files
/*=============================================================*/
#include "ResMgr_Common.h"
#include "HAL_AudResCtrl.h"
#include "MediaCtrlItf.h"

/*=============================================================*/
// Macro Definitions
/*=============================================================*/
#define HWL_SUCCESS     0

/*=============================================================*/
// Type Declarations
/*=============================================================*/
typedef s16 (*HWL_AudSetPath) (AudChannel_e eChannel, AudPath_e ePath);
typedef s16 (*HWL_AudSetVol) (AudChannel_e eChannel, u8 uVol, u8 uRange);
typedef s16 (*HWL_AudSetBalance) (AudChannel_e eChannel, s8 sBalance);
typedef s16 (*HWL_AudSeMediaARPConfig) (MediaARPConfigParm_t *pMediaARPConfigParm);
typedef s16 (*HWL_AudSeMediaConfig) (MediaConfigParm_t *pMediaConfigParm, bool bResetAudBuffer);
typedef s16 (*HWL_AudEnableLocalTone)(bool bEnable);
typedef s16 (*HWL_StartBt) (void *pParam);
typedef s16 (*HWL_PauseBt) (void *pParam);
typedef s16 (*HWL_ResumeBt) (void *pParam);
typedef s16 (*HWL_StopBt) (void *pParam);
typedef s16 (*HWL_EndBt) (void *pParam);
typedef s16 (*HWL_ForceStopBt) (void *pParam);
typedef s16 (*HWL_ForceStopM2) (void *pParam);

typedef void (*HWL_RequestHighCpuSpeed) (void);
typedef void (*HWL_RequestLowCpuSpeed) (void);
typedef bool (*HWL_IsAllowCpuSleepInFM) (void);
typedef s16 (*HWL_MmpGetCapability) (u8 *pStrucAddr, u32 uStrucLen);
typedef ResMgr_ErrorCode_e (*HWL_MmlGetPlatformCapability) (u32 *pStrucAddr);
typedef ResMgr_ErrorCode_e (*HWL_MmlGetPlatformChipType) (u32 *pStrucAddr);

typedef struct HWL_AudItf_t_
{
    HWL_AudSetPath SetPath;
    HWL_AudSetVol SetVolume;
    HWL_AudSetBalance SetBalance;
    HWL_AudSeMediaConfig SetMediaConfig;
    HWL_AudSeMediaARPConfig SetMediaARPConfig;
    HWL_AudEnableLocalTone EnableLocalTone;
} HWL_AudItf_t;

typedef struct HWL_BtItf_t_
{
    HWL_StartBt StartBt;
    HWL_PauseBt PauseBt;
    HWL_ResumeBt ResumeBt;
    HWL_StopBt StopBt;
    HWL_EndBt EndBt;
    HWL_ForceStopBt ForceStopBt;
    HWL_ForceStopM2 ForceStopM2;
} HWL_BtItf_t;

typedef struct HWL_SysItf_t_
{
    HWL_RequestHighCpuSpeed HighCpuSpeed;
    HWL_RequestLowCpuSpeed LowCpuSpeed;
    HWL_IsAllowCpuSleepInFM IsCpuSleepInFM; //Please kindly rename me
} HWL_SysItf_t;

typedef struct HWL_MmpItf_t_
{
    HWL_MmpGetCapability GetCapability;
    HWL_MmlGetPlatformCapability GetPlatCapability;
    HWL_MmlGetPlatformChipType GetPlatChipType;
} HWL_MmpItf_t;

/*=============================================================*/
// Public Function Declarations
/*=============================================================*/
void HWL_InitAudItf(const HWL_AudItf_t *pAudItf);
const HWL_AudItf_t* HWL_GetAudItf(void);

void HWL_InitMmpItf(const HWL_MmpItf_t *pMmpItf);
const HWL_MmpItf_t* HWL_GetMmpItf(void);
void HWL_InitBtItf(const HWL_BtItf_t *pBtItf);
const HWL_BtItf_t* HWL_GetBtItf(void);
void HWL_InitSysItf(const HWL_SysItf_t *pSysItf);
const HWL_SysItf_t* HWL_GetSysItf(void);
#endif //__HAL_MAINITF_H__

