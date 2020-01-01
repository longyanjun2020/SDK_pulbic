/****************************************************************************\
  \file     em_itf_audio_pub_api.h
  \brief    prototype of EM API and other definitions
  \date     2007/10/03
  \version  1.00
  \author   Peterwei Wang
  \warning

--------------------------------------------------------------------------
  Historical :
-----------------------------------------------------------------------------
    Date  | Author  | Err  |  Modification
----------+---------+------+-----------------------------------------------
----------+---------+------+-----------------------------------------------
\****************************************************************************/

#include "vm_audio_forward.h"
#include "em_itf_pub_forward.h"

void em_audioTest(u8 on, vm_AudioInput_e uInDevice, s32 uInGain, vm_AudioOutput_e uOutDevice, s32 uOutGain);

void em_VoiceSetInGain(s8 gain);
s8   em_VoiceGetInGain(void);
void em_VoiceSetOutGain(s8 gain);
s8   em_VoiceGetOutGain(void);
void em_VoiceSetAecParam(em_VoiceAecCfg_e cfg, em_VoiceAecParam_e param, u16 value);
u16  em_VoiceGetAecParam(em_VoiceAecCfg_e cfg, em_VoiceAecParam_e param);
void em_VoiceGetAudioInfo(void);

void em_AudioRegDump(void);
void em_AudioSramDump(void);

