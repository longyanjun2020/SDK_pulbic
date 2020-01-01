#ifndef __DWL_PARAM_H__
#define __DWL_PARAM_H__

#ifdef __DWL_PARAM_C__
#define INTERFACE
#else
#define INTERFACE extern
#endif

INTERFACE s32 dwl_RecevieParameters(void);
INTERFACE u32 get_nand_erase_timeout(void);
INTERFACE u32 get_cis_check_timeout(void);

#undef INTERFACE
#endif

