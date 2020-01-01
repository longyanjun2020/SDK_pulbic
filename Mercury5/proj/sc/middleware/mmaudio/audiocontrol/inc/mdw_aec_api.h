
#ifndef _MSTARAEC_H
#define _MSTARAEC_H

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
//#include "MML_Audio.h"
#include "srv_resmgr_mml_forward.h"
#include "srv_resmgr_mmlaudio_types.h" // Lib release stage1's workaround
#include "srv_ResMgr_Aud.h"

#define ENABLE_DRC
#define ENABLE_FIR

typedef struct _aecplay_s_
{
    MmlAECSetting_t aecplay_setting;
    MdlAudPath_e eAudPath;
    S16 OutBuf[32];
    u8 u8AudULPathChange;
    u8 u8AudDLPathChange;
    
#ifdef ENABLE_FIR
    void * gpULFirHandle;
    u8 u8EnableULFir;
    void * gpDLFirHandle;
    u8 u8EnableDLFir;
#endif
#ifdef ENABLE_AECPROC
    void * gpULAecHandle;
    u8 u8EnableULAec;
    void * gpDLAecHandle;
    u8 u8EnableDLAec;
#endif
#ifdef NSPROC
    void * gpULNsHandle;
    u8 u8EnableULNs;
    void * gpDLNsHandle;
    u8 u8EnableDLNs;
#endif

#ifdef ENABLE_DRC
    void * gpULDrcHandle;
    u8 u8EnableULDrc;
    void * gpDLDrcHandle;
    u8 u8EnableDLDrc;
#endif
}  aecplay_s;

extern void MdlAudAECProcess(u8 aecBufferID);

extern void MdlAudAECReconfigure(MdlAudPath_e eAudPath);

extern void MdlAudAECClose();

#endif

