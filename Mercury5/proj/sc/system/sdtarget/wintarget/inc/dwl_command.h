#ifndef _DWL_COMMAND_H_
#define _DWL_COMMAND_H_

typedef enum
{
	e_CMD_ERASE = 0x00000001,
	e_CMD_BINARY,
	e_CMD_E2P,
	e_CMD_NVRAM_RO,
	e_CMD_NVRAM_RW,
	e_CMD_RTC,
	e_CMD_UPLD,
	e_CMD_EXIT,
	e_CMD_CUS,
	e_CMD_PATCH,
	e_CMD_FMSMAP
#ifdef __SDTARGET__
        ,
	e_CMD_MEMPRM
#endif
}CmdType_e;



typedef struct{
    u32 u32_command_type;
    u32 u32_TargetCode;
    u32 u32_Origin;
    u32 u32_Length;
}dwl_command_t;

#endif

