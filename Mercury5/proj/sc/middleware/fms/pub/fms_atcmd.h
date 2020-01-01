#ifndef __FMS_ATCMD_H__
#define __FMS_ATCMD_H__

#ifdef __FMS_ATCMD_C__
#define INTERFACE
#else
#define INTERFACE extern
#endif

#define __MCP_VALIDATION_TEST__         0 // <-@@@

#ifdef __FMS_RAI_DEBUG__
#define __NRAI_CHECKSUM_DEBUG__         1
#define NRAICacheDebug 1
#else
#define __NRAI_CHECKSUM_DEBUG__         0
#define NRAICacheDebug 0
#endif
#define NRAICACHEFROMSTATIC 1
#define NRAIFLUSHDEBUG 0

#if __NRAI_CHECKSUM_DEBUG__
#define __USE_UART_TRACE__              0
#define __NRAI_BLUE_SCREEN_ASSERT__     0
#else
#define __USE_UART_TRACE__              0
#define __NRAI_BLUE_SCREEN_ASSERT__     0
#endif

#if __MCP_VALIDATION_TEST__

#include "Wmh_e2p_stack.ho"
#include "e2p_stck.ho"
#include "e2p_defs.hi"
//#include "hwl_aud.h"
#include "sys_rm_trc.ho"
#include "vm_e2p_lib.ho"
#include "vm_e2p_app.ho"
#include "e2p_abst.h"

#define __MCP_RAI_STRESS_TEST__         1
#define __FLASH_RAI_STRESS_TEST__       1
#define __FALSH_E2P_STRESS_TEST__       0
#define __AT_COMMAND_TEST__             1
#undef  __USE_UART_TRACE__
#define __USE_UART_TRACE__              1

INTERFACE u32 flash_gc_cnt;
INTERFACE u32 flash_erase_cnt;
INTERFACE u32 flash_suspend_cnt;
INTERFACE u32 flash_resume_cnt;
INTERFACE u32 flash_e2p_stress_test_flag;
INTERFACE u32 fms_rai_stress_test_flag;

INTERFACE void DumpE2PData(void);
INTERFACE void NRAIStressTest(void);

#else
#define __MCP_RAI_STRESS_TEST__         0
#define __FLASH_RAI_STRESS_TEST__       0
#define __FALSH_E2P_STRESS_TEST__       0
#define __AT_COMMAND_TEST__             0
#endif

#if __MCP_VALIDATION_TEST__
INTERFACE s8 MCPAtCmd(void *pParams);
#else
#define MCPAtCmd(x)
#endif

#if __FALSH_E2P_STRESS_TEST__
INTERFACE void fms_e2p_stress_test(void);
INTERFACE void fms_toggle_e2p_stress_test(void);
#else
#define fms_e2p_stress_test()
#define fms_toggle_e2p_stress_test()
#endif

#if __FLASH_RAI_STRESS_TEST__
#define STRESS_TEST_RAI_ID   0xAAAAAAAA
#define RAI_STRESS_TEST_SIZE 10240
INTERFACE u16 fms_rai_read_buf[RAI_STRESS_TEST_SIZE/2];
INTERFACE void fms_rai_stress_test(void);
INTERFACE void fms_toggle_rai_stress_test(void);
INTERFACE void fms_rai_read_stress_test_result(void);
#else
#define fms_rai_stress_test()
#define fms_toggle_rai_stress_test(x)
#define fms_rai_read_stress_test_result()
#endif

#if __MCP_VALIDATION_TEST__
extern s8 UartSendTrace(const char *strFormat, ...); //can be marked
//extern void DumpEMIParams(void);
//extern bool DUMPEMIPARAMS;
#endif


#if __AT_COMMAND_TEST__

#define E2P_DUMMY_DATA NULL, NULL

typedef struct
{
    u32  vm_offset;
    u32  vm_size;
    u32  offset;
    u32  size;
} E2PDATA_t;

typedef enum
{
    CALE2P = 0,
    ROSTACK,
    ROLIB,
    RWSTACK,
    RWLIB,
    RWAPP
} E2PDataEnum_t;


typedef struct
{
    E2PDataEnum_t E2PDataType;
    E2PDATA_t * E2PData;
    u32         StartAddress;
    u32         E2PDataNo;
} E2PGroup_t;
#endif //__AT_COMMAND_TEST__


#undef INTERFACE
#endif

