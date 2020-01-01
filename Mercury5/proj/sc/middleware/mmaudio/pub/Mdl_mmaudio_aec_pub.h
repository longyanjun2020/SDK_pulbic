#ifndef _PUB_AUDCTL_H
#define _PUB_AUDCTL_H
#include<stdint.h>

extern int32_t fnAEC_DL_PreProcess_Init(void);
extern int32_t fnAEC_DL_PreProcess(int16_t* pcmbuf, uint32_t u32FrameSz);
extern int32_t fnAEC_DL_PreProcess_Close(void);
#endif

