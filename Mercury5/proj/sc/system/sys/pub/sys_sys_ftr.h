#ifndef __SYS_SYS_FTR_H__
#define __SYS_SYS_FTR_H__

#include "sys_sys_vm_ftr.h"

#include "sys_sys_ftr.h"

#ifndef __INFINITY__
#include "hwll1_ftr.h"
#include "l1c_ftr.ho"
#include "dat_ftr.ho"
#include "sim_ftr.ho"
#include "rr_ftr.ho"
#include "cc_ftr.ho"
#include "mm_ftr.ho"
#endif
#include "mmi_ftr.ho"
#include "cus_ftr.ho"

#define GLOBAL_FTR(Wd) (  HWL_FTR(Wd)   \
                        & L1C_FTR(Wd)   \
                        & DAT_FTR(Wd)   \
                        & SIM_FTR(Wd)   \
                        & RR_FTR(Wd)    \
                        & MM_FTR(Wd)    \
                        & CC_FTR(Wd)    \
                        & MMI_FTR(Wd)   \
                        & CUS_FTR(Wd))
                        
#endif // __SYS_SYS_FTR_H__

