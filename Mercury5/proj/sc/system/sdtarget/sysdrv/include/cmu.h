
#ifndef __CMU_H__
#define __CMU_H__

#ifdef __CMU_C__
#define INTERFACE
#else
#define INTERFACE extern
#endif

typedef enum
{
    CPU_FAST=0,
    CPU_ORIGNAL    
} CPUSpeed_e;

INTERFACE void DrvCPUSpeedChange(CPUSpeed_e speed);

#endif

