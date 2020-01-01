/**
 * \file sys_sys_mem.h
 * \brief Specific SRAM/NOR driver for B1
*/

#ifndef __SYS_SYS_MEM_H__
#define __SYS_SYS_MEM_H__

#include "vm_types.ht"
#include "drv_emi_sram_nor_pub.h"

#define INTEL_PSRAM_BURST_LENGTH_OFF 	0
#define INTEL_PSRAM_BURST_LENGTH_MSK 	(0x7<<INTEL_PSRAM_BURST_LENGTH_OFF)
#define INTEL_PSRAM_BURST_WRAP_OFF 		3
#define INTEL_PSRAM_BURST_WRAP_MSK 		(0x1<<INTEL_PSRAM_BURST_WRAP_OFF)
#define INTEL_PSRAM_DRIVE_STRENGTH_OFF 		4
#define INTEL_PSRAM_DRIVE_STRENGTH_MSK 		(0x3<<INTEL_PSRAM_DRIVE_STRENGTH_OFF)
#define INTEL_PSRAM_WAIT_CFG_OFF 			8
#define INTEL_PSRAM_WAIT_CFG_MSK 			(0x1<<INTEL_PSRAM_WAIT_CFG_OFF)
#define INTEL_PSRAM_WAIT_POL_OFF 			10
#define INTEL_PSRAM_WAIT_POL_MSK 			(0x1<<INTEL_PSRAM_WAIT_POL_OFF)
#define INTEL_PSRAM_LATENCY_MODE_OFF 	11
#define INTEL_PSRAM_LATENCY_MODE_MSK 	(0x7<<INTEL_PSRAM_LATENCY_MODE_OFF)
#define INTEL_PSRAM_OP_MODE_OFF 			15
#define INTEL_PSRAM_OP_MODE_MSK 			(0x1<<INTEL_PSRAM_OP_MODE_OFF)

#define INTEL_SYNC_MODE    0
#define INTEL_ASYNC_MODE   1

#define INTEL_NOR_RM_OFF 	15
#define INTEL_NOR_RM_MSK 	(0x1<<INTEL_NOR_RM_OFF)
#define INTEL_NOR_LC_OFF 	11
#define INTEL_NOR_LC_MSK 	(0x7<<INTEL_NOR_LC_OFF)
#define INTEL_NOR_WP_OFF 	10
#define INTEL_NOR_WP_MSK 	(0x1<<INTEL_NOR_WP_OFF)
#define INTEL_NOR_DH_OFF 	9
#define INTEL_NOR_DH_MSK 	(0x1<<INTEL_NOR_DH_OFF)
#define INTEL_NOR_WD_OFF 	8
#define INTEL_NOR_WD_MSK 	(0x1<<INTEL_NOR_WD_OFF)
#define INTEL_NOR_BS_OFF 	7
#define INTEL_NOR_BS_MSK 	(0x1<<INTEL_NOR_BS_OFF)
#define INTEL_NOR_CE_OFF 	6
#define INTEL_NOR_CE_MSK 	(0x1<<INTEL_NOR_CE_OFF)
#define INTEL_NOR_BW_OFF 	3
#define INTEL_NOR_BW_MSK 	(0x1<<INTEL_NOR_BW_OFF)
#define INTEL_NOR_BL_OFF 	0
#define INTEL_NOR_BL_MSK 	(0x7<<INTEL_NOR_BL_OFF)

typedef struct {
	u32 RM:1; //Read Mode (RM) 0 = Synchronous burst-mode read 1 = Asynchronous page-mode read (default)
	u32 LC:3; //Latency Count (LC[2:0]) 010 =Code 2 011 =Code 3 100 =Code 4 101 =Code 5 110 =Code 6 111 =Code 7 (default)
	u32 WP:1; // Wait Polarity (WP) 0 =WAIT signal is active low 1 =WAIT signal is active high (default)
	u32 DH:1; //Data Hold (DH) 0 =Data held for a 1-clock data cycle 1 =Data held for a 2-clock data cycle (default)
	u32 WD:1; // Wait Delay (WD) 0 =WAIT deasserted with valid data 1 =WAIT deasserted one data cycle before valid data (default)
	u32 BS:1; // Burst Sequence (BS) 0 =Reserved 1 =Linear (default)
	u32 CE:1; //Clock Edge (CE) 0 = Falling edge 1 = Rising edge (default)
	u32 BW:1; // Burst Wrap (BW) 0 =Wrap; Burst accesses wrap within burst length set by BL[2:0] 1 =No Wrap; Burst accesses do not wrap within burst length (default)
	u32 BL:3; // Burst Length (BL[2:0]) 001 =4-word burst 010 =8-word burst 011 =16-word burst 111 =Continuous-word burst (default)
} sys_IntelReadCtrlReg_t;

typedef enum {
    SYS_MEM_NOR = 0,    ///< NOR flash, on MEM0
    SYS_MEM_SRAM        ///< SRAM flash, on MEM1
} sys_memDevice_t;

typedef struct {
    u32 flash_id;                   ///< Jedec ID of the Flash
    emi_SramNorCfg_t *nor_config;   ///< Array of configurations versus AHB frequency (EMI_CFG_NB configurations)
    emi_SramNorCfg_t *sram_config;  ///< Array of configurations versus AHB frequency (EMI_CFG_NB configurations)
} sys_memEmiParams_t;

typedef struct
{
	bool         isNor ;
	emi_flash_type_e	flash_type;
	emi_mode_e   psram_OpMode ;
	emi_mode_e   nor_OpMode ;
}sys_McpOpMode;




emi_SramNorCfg_t* sys_MemGetEmiConfiguration(sys_memDevice_t device);

#ifdef MCP_CONFIG_TABLE
emi_mcpConfig_new* sys_GetEmiConfiguration(u32 Flash_ID);
#else
sys_EmiParams_t * sys_GetEmiConfiguration(u32 Flash_ID);
#endif

void sys_SramSetCtrlReg(bool burst, emi_Port_e portNo, sys_IntelBusCtrlReg_t *BCR, emi_SramNorCfg_t *config);
void sys_NorSetReadCtrlReg(emi_Port_e portNo, sys_IntelReadCtrlReg_t  *RCR, emi_SramNorCfg_t *config);

void emi_psram_set_page_mode(emi_Port_e portNo, u32 pagemode);

u32 sys_GetM3RamAddress(void);

void sys_ActivateBurstNor(bool enable);
void sys_ActivateBurstRam(bool enable);
void sys_MemInit(void);

void sys_EmiPoolProtectInit(void);
void sys_EmiSetBW(u32 en, u32 blockid, u32 start, u32 end, u32 cluster_size, u32 resideu, u32 pattern);
void sys_EmiStopBW(void);
void sys_MemProtectAt(u32 en, u32 blockid, u32 addr, u32 pattern);
void sys_IMIProtectAt(u32 en, u32 blockid, u32 addr, u32 pattern);
void sys_GetMcpInformation(sys_McpOpMode* mcp_OpMode);
void sys_MemClockInit_first(void);
void sys_MemClockInit_Second(void);

#endif //__SYS_SYS_MEM_H__

