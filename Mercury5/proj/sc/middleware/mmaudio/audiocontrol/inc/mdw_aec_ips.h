
#ifndef _MSTARAEC_IPS_H
#define _MSTARAEC_IPS_H

extern u32 MdlAudAECULIPsInit(aecplay_s * gpAECtask);
extern u32 MdlAudAECDLIPsInit(aecplay_s * gpAECtask);

extern u32 MdlAudAECULIPsProcess(aecplay_s * gpAECtask,short*  mixed_pcm,short*  reference);
extern u32 MdlAudAECDLIPsProcess(aecplay_s * gpAECtask,S16 * pcmbuf, U32 u32FrameSz);

extern u32 MdlAudAECULIPsReconfigure(aecplay_s * gpAECtask);
extern u32 MdlAudAECDLIPsReconfigure(aecplay_s * gpAECtask);

extern u32 MdlAudAECULIPsClose(aecplay_s * gpAECtask);
extern u32 MdlAudAECDLIPsClose(aecplay_s * gpAECtask);

#endif

