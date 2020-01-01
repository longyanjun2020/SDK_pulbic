#ifndef _MDW_ENC_PLUGIN_H_
#define _MDW_ENC_PLUGIN_H_

#include "vm_types.ht"
#include "srv_resmgr_mmlaudio_types.h" // Lib release stage1's workaround


s32 fnRecorder_setAddr(void *recorder, s32 data_fmt);
u32 _MdlGetRemainingRecordTime(MmlAudioGetRecordingInfo_t *pRecordingInfo);
void fnMAR_WTHDInit(void);
void fnMAR_FreeMemory(void);
void fnMAR_FreeFileName(void *martask, void* marw_task );



#endif
