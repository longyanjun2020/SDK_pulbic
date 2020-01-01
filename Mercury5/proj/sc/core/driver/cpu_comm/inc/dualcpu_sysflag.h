#ifndef __DUAL_CPU_SYS_FLAG__
#define __DUAL_CPU_SYS_FLAG__

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

#if (CPU_ID==CPU_A)
void DualCpu_SysFlag_WaitCpuBInitDone(void);
void DualCpu_SysFlag_TerminateCpuB(void);
#endif

#if (CPU_ID == CPU_B)
void DualCpu_SysFlag_CpuBInitDone(void);
void DualCpu_SysFlag_WaitTerminateCmd(void);
#endif

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif
