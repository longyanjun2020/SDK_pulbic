#ifndef __SYS_SYS_DPM_TMPL_H__
#define __SYS_SYS_DPM_TMPL_H__

#if defined (__RTK_OVER_R2__)
#include "vm_types.ht"
#include "osdefs.hc"
#include "mdl_vfs_file.ho"
#include "cpu_mem_map.hc"
#include "sys_MsWrapper_cus_os_mem.h"
#include "sys_sys_r2.h"
#include "sys_sys_dpm_mgr.h"

#define _CONCAT_TOKEN(x, y)     x##y
#define CONCAT_TOKEN(x, y)      _CONCAT_TOKEN(x, y)
#define _TO_STR(x)              #x
#define TO_STR(x)               _TO_STR(x)

extern DpmAppRegEntry_t         DpmAppRegTable[];
extern DpmSlotRegEntry_t        DpmSlotRegTable[];

#define DPM_PARAM
#include TO_STR(DPM_INTF_FILE_NAME)
#undef DPM_PARAM

u8 CONCAT_TOKEN(DPM_NAME, _func_tbl_init)(pFunc_t* tmpJmpTbl)
{
    #define INIT_JMPTBL
    #include TO_STR(DPM_INTF_FILE_NAME)
    #undef INIT_JMPTBL

    return TRUE;
}
#endif
#endif //__SYS_SYS_DPM_TMPL_H__
