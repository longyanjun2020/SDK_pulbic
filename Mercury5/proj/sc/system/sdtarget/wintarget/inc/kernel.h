#ifndef __KERNEL_H__
#define __KERNEL_H__

#ifdef __G1__
#include "v2751.h"
#else // __G1__

/* B1 registers definition */

#include "vm_types.ht"
#include "cpu_mem_map.h"
#ifdef __B2__
#include "incense_reg.h"
#include "kernel_gpio.h"
#include "kernel_cmu.h"
#endif

#ifdef  __cplusplus
extern "C" {
#endif

#define MAIN_OFFSET 0x00000000

/************************************************/
/* EMI registers definition                   */
/************************************************/
#ifdef __B1__
typedef struct W5Emi_s
{
     u32 u32_cfg ;
     u32 u32_mem0_cfg1 ;
     u32 u32_mem0_cfg2 ;
     u32 u32_mem1_cfg1 ;
     u32 u32_mem1_cfg2 ;
     u32 u32_mem2_cfg1 ;
     u32 u32_mem2_cfg2 ;
     u32 u32_mem3_cfg1 ;
     u32 u32_mem3_cfg2 ;
     u32 u32_usr0_cfg ;
     u32 u32_usr1_cfg ;
     u32 u32_usr2_cfg ;
     u32 u32_spare ;
} W5Emi_t;

/*CFG */
#define EMI_CFG_DOUT_EN_VAL_OFFSET  0
#define EMI_CFG_DOUT_EN_VAL_MSK     (0x3<<EMI_CFG_DOUT_EN_VAL_OFFSET)
#define EMI_CFG_BCLK_EN_OFFSET      2
#define EMI_CFG_BCLK_EN_MSK         (1<<EMI_CFG_BCLK_EN_OFFSET)
#define EMI_CFG_BCLK_EDGE_OFFSET    3
#define EMI_CFG_BCLK_EDGE_MSK       (1<<EMI_CFG_BCLK_EDGE_OFFSET)
#define EMI_CFG_BCLK_DEF_OFFSET     4
#define EMI_CFG_BCLK_DEF_MSK        (1<<EMI_CFG_BCLK_DEF_OFFSET)
#define EMI_CFG_ADV_DEF_OFFSET      5
#define EMI_CFG_ADV_DEF_MSK         (1<<EMI_CFG_ADV_DEF_OFFSET)

/*----------- MEM_CFG1 definition --------*/
#define EMI_MEM_CFG1_MODE_OFFSET         0
#define EMI_MEM_CFG1_MODE_MSK            ((u32)0x3<<EMI_MEM_CFG1_MODE_OFFSET)
#define EMI_MEM_CFG1_BP_SIZE_OFFSET      2
#define EMI_MEM_CFG1_BP_SIZE_MSK         ((u32)0x3<<EMI_MEM_CFG1_BP_SIZE_OFFSET)
#define EMI_MEM_CFG1_WAIT_ACCT_OFFSET    4
#define EMI_MEM_CFG1_WAIT_ACCT_MSK       ((u32)0x0000000F<<EMI_MEM_CFG1_WAIT_ACCT_OFFSET)
#define EMI_MEM_CFG1_B_HOLD_OFFSET       8
#define EMI_MEM_CFG1_B_HOLD_MSK          ((u32)1<<EMI_MEM_CFG1_B_HOLD_OFFSET)
#define EMI_MEM_CFG1_WAIT_POL_OFFSET     9
#define EMI_MEM_CFG1_WAIT_POL_MSK        ((u32)1<<EMI_MEM_CFG1_WAIT_POL_OFFSET)
#define EMI_MEM_CFG1_WAIT_SHIFT_OFFSET   10
#define EMI_MEM_CFG1_WAIT_SHIFT_MSK      ((u32)1<<EMI_MEM_CFG1_WAIT_SHIFT_OFFSET)
#define EMI_MEM_CFG1_BP_ACCT_OFFSET      11
#define EMI_MEM_CFG1_BP_ACCT_MSK         ((u32)0x00000007<<EMI_MEM_CFG1_BP_ACCT_OFFSET)
#define EMI_MEM_CFG1_STRETCH_RDW_OFFSET  14
#define EMI_MEM_CFG1_STRETCH_RDW_MSK     ((u32)1<<EMI_MEM_CFG1_STRETCH_RDW_OFFSET)

/*----------- EMI_MEM_CFG2 definition --------*/
#define EMI_MEM_CFG2_WAIT_RD_OFFSET       0
#define EMI_MEM_CFG2_WAIT_RD_MSK          ((u32)0x0000001F<<EMI_MEM_CFG2_WAIT_RD_OFFSET)
#define EMI_MEM_CFG2_HALF0_RD_OFFSET      5
#define EMI_MEM_CFG2_HALF0_RD_MSK         ((u32)1<<EMI_MEM_CFG2_HALF0_RD_OFFSET)
#define EMI_MEM_CFG2_HALF1_RD_OFFSET      6
#define EMI_MEM_CFG2_HALF1_RD_MSK         ((u32)1<<EMI_MEM_CFG2_HALF1_RD_OFFSET)
#define EMI_MEM_CFG2_SETUP_RD_OFFSET      8
#define EMI_MEM_CFG2_SETUP_RD_MSK         ((u32)0x3<<EMI_MEM_CFG2_SETUP_RD_OFFSET)
#define EMI_MEM_CFG2_HOLD_RD_OFFSET       10
#define EMI_MEM_CFG2_HOLD_RD_MSK          ((u32)0x3<<EMI_MEM_CFG2_HOLD_RD_OFFSET)
#define EMI_MEM_CFG2_WAIT_WR_OFFSET       12
#define EMI_MEM_CFG2_WAIT_WR_MSK          ((u32)0x0000001F<<EMI_MEM_CFG2_WAIT_WR_OFFSET)
#define EMI_MEM_CFG2_HALF0_WR_OFFSET      17
#define EMI_MEM_CFG2_HALF0_WR_MSK         ((u32)1<<EMI_MEM_CFG2_HALF0_WR_OFFSET)
#define EMI_MEM_CFG2_HALF1_WR_OFFSET      18
#define EMI_MEM_CFG2_HALF1_WR_MSK         ((u32)1<<EMI_MEM_CFG2_HALF1_WR_OFFSET)
#define EMI_MEM_CFG2_SETUP_WR_OFFSET      20
#define EMI_MEM_CFG2_SETUP_WR_MSK         ((u32)0x3<<EMI_MEM_CFG2_SETUP_WR_OFFSET)
#define EMI_MEM_CFG2_HOLD_WR_OFFSET       22
#define EMI_MEM_CFG2_HOLD_WR_MSK          ((u32)0x3<<EMI_MEM_CFG2_HOLD_WR_OFFSET)
#define EMI_MEM_CFG2_BTA_OFFSET           24
#define EMI_MEM_CFG2_BTA_MSK              ((u32)0x00000007<<EMI_MEM_CFG2_BTA_OFFSET)
#define EMI_MEM_CFG2_RTOR_OFFSET          27
#define EMI_MEM_CFG2_RTOR_MSK             ((u32)0x3<<EMI_MEM_CFG2_RTOR_OFFSET)
#define EMI_MEM_CFG2_WTOW_OFFSET          29
#define EMI_MEM_CFG2_WTOW_MSK             ((u32)0x00000007<<EMI_MEM_CFG2_WTOW_OFFSET)

/*----------- EMI_USR_CFG definition --------*/
#define EMI_USR_CFG_WAIT_RD_OFFSET  0
#define EMI_USR_CFG_WAIT_RD_MSK (0x0000000F<<EMI_USR_CFG_WAIT_RD_OFFSET)
#define EMI_USR_CFG_SETUP_RD_OFFSET 4
#define EMI_USR_CFG_SETUP_RD_MSK    (0x3<<EMI_USR_CFG_SETUP_RD_OFFSET)
#define EMI_USR_CFG_HOLD_RD_OFFSET  6
#define EMI_USR_CFG_HOLD_RD_MSK (0x3<<EMI_USR_CFG_HOLD_RD_OFFSET)
#define EMI_USR_CFG_WAIT_WR_OFFSET  8
#define EMI_USR_CFG_WAIT_WR_MSK (0x0000000F<<EMI_USR_CFG_WAIT_WR_OFFSET)
#define EMI_USR_CFG_SETUP_WR_OFFSET 12
#define EMI_USR_CFG_SETUP_WR_MSK    (0x3<<EMI_USR_CFG_SETUP_WR_OFFSET)
#define EMI_USR_CFG_HOLD_WR_OFFSET  14
#define EMI_USR_CFG_HOLD_WR_MSK (0x3<<EMI_USR_CFG_HOLD_WR_OFFSET)
#define EMI_USR_CFG_TS_UNIT_OFFSET  16
#define EMI_USR_CFG_TS_UNIT_MSK (1<<EMI_USR_CFG_TS_UNIT_OFFSET)
#define EMI_USR_CFG_BTA_OFFSET  17
#define EMI_USR_CFG_BTA_MSK (0x00000007<<EMI_USR_CFG_BTA_OFFSET)
#define EMI_USR_CFG_WTOW_OFFSET 20
#define EMI_USR_CFG_WTOW_MSK    (0x00000007<<EMI_USR_CFG_WTOW_OFFSET)
#define EMI_USR_CFG_WR_POL_OFFSET   23
#define EMI_USR_CFG_WR_POL_MSK  (1<<EMI_USR_CFG_WR_POL_OFFSET)
#define EMI_USR_CFG_MODE_OFFSET 24
#define EMI_USR_CFG_MODE_MSK    (1<<EMI_USR_CFG_MODE_OFFSET)

typedef struct W5EmiArbitrer_s
{
     u32 u32_cfg ;
     u32 u32_spare ;
} W5EmiArbitrer_t;

/*sub register definitions */
#define EMI_ARBITER_CFG_MEM_RD_OFFSET         0
#define EMI_ARBITER_CFG_MEM_RD_MSK            ((u32)1<<EMI_ARBITER_CFG_MEM_RD_OFFSET)
#define EMI_ARBITER_CFG_BTA_OFFSET            0
#define EMI_ARBITER_CFG_BTA_MSK               ((u32)7<<EMI_ARBITER_CFG_BTA_OFFSET)
#define EMI_ARBITER_CFG_MEM_WR_OFFSET         1
#define EMI_ARBITER_CFG_MEM_WR_MSK            ((u32)1<<EMI_ARBITER_CFG_MEM_WR_OFFSET)
#define EMI_ARBITER_CFG_PRIORITY_OFFSET       3
#define EMI_ARBITER_CFG_PRIORITY_MSK          ((u32)1<<EMI_ARBITER_CFG_PRIORITY_OFFSET)
#define EMI_ARBITER_CFG_MEM_OFFSET            4
#define EMI_ARBITER_CFG_MEM_MSK               ((u32)3<<EMI_ARBITER_CFG_MEM_OFFSET)
#define EMI_ARBITER_CFG_MUX_CFG0_OFFSET       6
#define EMI_ARBITER_CFG_MUX_CFG0_MSK          ((u32)1<<EMI_ARBITER_CFG_MUX_CFG0_OFFSET)
#define EMI_ARBITER_CFG_MUX_CFG1_OFFSET       7
#define EMI_ARBITER_CFG_MUX_CFG1_MSK          ((u32)1<<EMI_ARBITER_CFG_MUX_CFG1_OFFSET)
#define EMI_ARBITER_CFG_MUX_CFG2_OFFSET       8
#define EMI_ARBITER_CFG_MUX_CFG2_MSK          ((u32)1<<EMI_ARBITER_CFG_MUX_CFG2_OFFSET)
#define EMI_ARBITER_CFG_MUX_CFG3_OFFSET       9
#define EMI_ARBITER_CFG_MUX_CFG3_MSK          ((u32)1<<EMI_ARBITER_CFG_MUX_CFG3_OFFSET)
#define EMI_ARBITER_CFG_OUT_DELAY_OFFSET      10
#define EMI_ARBITER_CFG_OUT_DELAY_MSK         ((u32)7<<EMI_ARBITER_CFG_OUT_DELAY_OFFSET)
#define EMI_ARBITER_CFG_EMI_IN_DELAY_OFFSET   13
#define EMI_ARBITER_CFG_EMI_IN_DELAY_MSK      ((u32)3<<EMI_ARBITER_CFG_EMI_IN_DELAY_OFFSET)
#define EMI_ARBITER_CFG_SDRAM_IN_DELAY_OFFSET 15
#define EMI_ARBITER_CFG_SDRAM_IN_DELAY_MSK    ((u32)3<<EMI_ARBITER_CFG_SDRAM_IN_DELAY_OFFSET)

typedef struct W5SdramCfg_s
{
     u32 u32_cfg ; // SDRAM configuration register (SCONR)
     u32 u32_timing_reg0; // SDRAM timing register0 (STMG0R)
     u32 u32_timing_reg1; // SDRAM timing register1 (STMG1R)
     u32 u32_ctrl; // SDRAM control register (SCTLR)
     u32 u32_refresh_interval; //SDRAM refresh interval register (SREFR)
     u32 u32_extended_mode_reg; // Extended mode register
     u32 u32_spare ;
} W5SdramCfg_t;

#define SDRAM_CFG_NB_BANK_ADDR_BITS_OFFSET  3
#define SDRAM_CFG_NB_BANK_ADDR_BITS_MSK     ((u32)3 << SDRAM_CFG_NB_BANK_ADDR_BITS_OFFSET) //= (n+1)*2 => 2 to 16 banks (2,4,8,16)
#define SDRAM_CFG_NB_ROW_ADDR_BITS_OFFSET   5
#define SDRAM_CFG_NB_ROW_ADDR_BITS_MSK      ((u32)0xF << SDRAM_CFG_NB_ROW_ADDR_BITS_OFFSET)
#define SDRAM_CFG_NB_COL_ADDR_BITS_OFFSET   9
#define SDRAM_CFG_NB_COL_ADDR_BITS_MSK      ((u32)0xF << SDRAM_CFG_NB_COL_ADDR_BITS_OFFSET)
#define SDRAM_CFG_DATA_BUS_WIDTH_OFFSET     13 //00: 16 bits.
#define SDRAM_CFG_DATA_BUS_WIDTH_MSK        ((u32)3 << SDRAM_CFG_DATA_BUS_WIDTH_OFFSET)

#define SDRAM_CFG_CAS_LATENCY_OFFSET        0 //00: 1 hclk
#define SDRAM_CFG_CAS_LATENCY_MSK           ((u32)3 << SDRAM_CFG_CAS_LATENCY_OFFSET)
#define SDRAM_CFG_TRAS_OFFSET               2
#define SDRAM_CFG_TRAS_MSK                  ((u32)0xF << SDRAM_CFG_TRAS_OFFSET)
#define SDRAM_CFG_TRCD_OFFSET               7
#define SDRAM_CFG_TRCD_MSK                  ((u32)3 << SDRAM_CFG_TRCD_OFFSET)
#define SDRAM_CFG_TRP_OFFSET                9
#define SDRAM_CFG_TRP_MSK                   ((u32)7 << SDRAM_CFG_TRP_OFFSET)
#define SDRAM_CFG_TWR_OFFSET                12
#define SDRAM_CFG_TWR_MSK                   ((u32)3 << SDRAM_CFG_TWR_OFFSET)
#define SDRAM_CFG_TRCAR_OFFSET              14
#define SDRAM_CFG_TRCAR_MSK                 ((u32)0xF << SDRAM_CFG_TRCAR_OFFSET)
#define SDRAM_CFG_TXSR_OFFSET               18
#define SDRAM_CFG_TXSR_MSK                  ((u32)0xF << SDRAM_CFG_TXSR_OFFSET)
#define SDRAM_CFG_TRC_OFFSET                22
#define SDRAM_CFG_TRC_MSK                   ((u32)0xF << SDRAM_CFG_TRC_OFFSET)

#define SDRAM_CFG_TINIT_OFFSET          0
#define SDRAM_CFG_TINIT_MSK             ((u32)0xFFFF << SDRAM_CFG_TINIT_OFFSET)
#define SDRAM_CFG_NUM_INIT_REF_OFFSET   16
#define SDRAM_CFG_NUM_INIT_REF_MSK      ((u32)0xF << SDRAM_CFG_NUM_INIT_REF_OFFSET)

#define SDRAM_CFG_INITIALIZE_OFFSET     0 // Initialize: enable the initialization sequence
#define SDRAM_CFG_INITIALIZE_MSK            ((u32)1 << SDRAM_CFG_INITIALIZE_OFFSET)
#define SDRAM_CFG_ENTER_SELF_REF_OFFSET 1 //Enter/exit self refresh mode
#define SDRAM_CFG_ENTER_SELF_REF_MSK        ((u32)1 << SDRAM_CFG_ENTER_SELF_REF_OFFSET)
#define SDRAM_CFG_PW_DWN_OFFSET         2 //Power down mode
#define SDRAM_CFG_PW_DWN_MSK            ((u32)1 << SDRAM_CFG_PW_DWN_OFFSET)
#define SDRAM_CFG_PRECHARGE_TYPE_OFFSET 3 //0: immediate precharge 1: delayed precharge
#define SDRAM_CFG_PRECHARGE_TYPE_MSK    ((u32)1 << SDRAM_CFG_PRECHARGE_TYPE_OFFSET)
#define SDRAM_CFG_REFRESH_ENTER_OFFSET  4 // 1: refresh all rows before entering self refresh 0: refresh one row before entering self refresh
#define SDRAM_CFG_REFRESH_ENTER_MSK     ((u32)1 << SDRAM_CFG_REFRESH_ENTER_OFFSET)
#define SDRAM_CFG_REFRESH_EXIT_OFFSET   5 // 1: refresh all rows before exiting self refresh 0: refresh one row before exiting self refresh
#define SDRAM_CFG_REFRESH_EXIT_MSK      ((u32)1 << SDRAM_CFG_REFRESH_EXIT_OFFSET)
#define SDRAM_CFG_NB_READ_PIPE_OFFSET   6 //Number of read pipe registers : 0 to 7
#define SDRAM_CFG_NB_READ_PIPE_MSK      ((u32)7 << SDRAM_CFG_NB_READ_PIPE_OFFSET)
#define SDRAM_CFG_FORCE_MODE_REG_OFFSET 9 //1: forces set mode register command to be executed. Cleared once the controller finishes the mode register update.
#define SDRAM_CFG_FORCE_MODE_REG_MSK    ((u32)1 << SDRAM_CFG_FORCE_MODE_REG_OFFSET)
#define SDRAM_CFG_SELF_REF_STAT_OFFSET  11 //Self refresh status. 1 indicates SDRAM in self refresh mode
#define SDRAM_CFG_SELF_REF_STAT_MSK     ((u32)1 << SDRAM_CFG_SELF_REF_STAT_OFFSET)
#define SDRAM_CFG_NB_BANKS_OFFSET       12 //Number of SDRAM internal banks to be opened. 0 to 15 banks.
#define SDRAM_CFG_NB_BANKS_MSK          ((u32)0x1F << SDRAM_CFG_NB_BANKS_OFFSET)
#define SDRAM_CFG_READ_DATA_RDY_OFFSET  17//SDRAM read data ready
#define SDRAM_CFG_READ_DATA_RDY_MSK     ((u32)1 << SDRAM_CFG_READ_DATA_RDY_OFFSET)
#define SDRAM_CFG_EXT_MODE_REG_OFFSET   18 //1: forces extended set mode register command  to be executed. Cleared once the controller finishes the extended mode register update.
#define SDRAM_CFG_EXT_MODE_REG_MSK      ((u32)1 << SDRAM_CFG_EXT_MODE_REG_OFFSET)

#define SDRAM_CFG_TREF_OFFSET            0 // tREF: number of clock cycles between consecutive refresh cycles. tREF = refresh period / hclk period.
#define SDRAM_CFG_TREF_MSK              ((u32)0xFFFF << SDRAM_CFG_TREF_OFFSET)
#define SDRAM_CFG_GPO_OFFSET            16 // General Purpose Outputs.
#define SDRAM_CFG_GPO_MSK               ((u32)0xFF << SDRAM_CFG_GPO_OFFSET)
#define SDRAM_CFG_GPI_OFFSET            24 //General Purpose Inputs.
#define SDRAM_CFG_GPI_MSK               ((u32)0xFF << SDRAM_CFG_GPI_OFFSET)

#define SDRAM_CFG_PASR_OFFSET           0 //Partial refresh for mobile SDRAM 00: 4 banks, 01: 2 banks, 10: 1 bank
#define SDRAM_CFG_PASR_MSK              ((u32)0x7 << SDRAM_CFG_GPI_OFFSET)
#define SDRAM_CFG_TCSR_OFFSET           3 //temperature compensated Self Refresh for mobile SDRAM
#define SDRAM_CFG_TCSR_MSK              ((u32)0x3 << SDRAM_CFG_GPI_OFFSET) //0: 70?1: 45?2: 15?3: 85?

#endif //__B1__

/************************************************/
/* DPRAM registers definition                   */
/************************************************/
typedef struct
{
  u16           u16_Status;
  u16           u16_Power;
  u16           u16_Energy;
  u16           u16_FinalMetric;
  s16           u16_Toi;
  s16           u16_Foi;
  s16           u16_DC_IOffset;
  s16           u16_DC_QOffset;
} WinRes_t;

typedef struct W5Dpram_s
{
  u16           u16_DspCodeVersion;       // 0x000 - Dsp code version
  u16           au16_DspErrorLabel[2];    // 0x002 - Dsp Error label array
  u16           u16_NbRxSamples2x;     // 0x006 - Number of received samples @2x
  u16           u16_NbRxSamples1x;    // 0x008 - Number of received samples @1x
  u16           u16_ChannelAttributes;    // 0x00A - TCH channel coding + DTX + Half Rate
  u16           u16_SacchStartFn;         // 0x00C - Sacch starting Frame
  u16           u16_AmrLnkCtrl;           // 0x00E - Amr UpLink Control - SDA : To be changed
  u16           u16_Amr_DownLnkCtrl;      // 0x010 - Amr DownLink Control
  u16           au16_AmrHysterThres[3];   // 0x012 - AMR hysteresis thresholds
  u16           u16_AmrRxCodecMode;       // 0x018 - AMR Rx Absolute Codec Mode
  u16           u16_AmrRxFrameType;       // 0x01A - AMR Rx Frame type
  u16           u16_AmrCIEstim;           // 0x01C - AMR C/I estimation
  u16           u16_AmrTxCodecMode;       // 0x01E - Amr Tx Codec Mode
  u16           u16_AmrTxFrameType;       // 0x020 - AMR Tx Frame type
  u16           u16_TchFlag;              // 0x022 - misc Tch flag
  u16           u16_FchEnergyThres;       // 0x024 - Energy threshold for FCH research
  u16           u16_FchFacchDetectThres;  // 0x026 - FCH and FACCH detection threshold
  u16           u16_ErrCntAndTchUfiThres; // 0x028 - TCH Error count threshold  + Half rate UFI threshold
  u16           u16_MsFoiThres;           // 0x02A - Multislot Foi computation threshold
  u32           au32_UsfEstimation[4];    // 0x02C - Usf estimation
  u16           u16_IrConfig;             // 0x03C - Incremental redundency  configuration register
  u16           u16_IrNbBlockMax;         // 0x03E - IR max block stored
  u16           u16_IrNbBlockUsed;        // 0x040 - IR Block used
  u16           u16_IrDspVQ;              // 0x042 - Ir Dsp VQ
  u16           u16_IrDspVR;              // 0x044 - Ir Dsp VR
  u16           u16_IrCpuVQ;              // 0x046 - Ir Cpu VQ
  u16           u16_IrCpuVR;              // 0x048 - Ir Cpu VR
  u16           u16_EdgeAlgoCtrl;         // 0x04A - Edge Algorithms Control
  u16           au16_InterfererCount[4];  // 0x04C - Interferer counter
  u16           u16_RxAutoCalCtrl;        // 0x054 - Rx auto calibration control register  ?
  u16           u16_RxAutoCalFlag;        // 0x056 - Rx auto calibration control flag  ?
  u16           au16_BlindDetectCount[4]; // 0x058 - Blind detection counter
  u16           u16_TrackingMju;          // 0x060 - Tracking Mju parametre
  u16           u16_TrackingStep;         // 0x062 - Tracking Step parametre
  u16           u16_MuteCtrlLoopBackMode; // 0x064 - Mute control + loopback mode
  u16           u16_CipherKeyLSB1;        // 0x066 - Ciphering key
  u16           u16_CipherKeyLSB2;        // 0x068 - Ciphering key
  u16           u16_CipherKeyMSB1;        // 0x06A - Ciphering key
  u16           u16_CipherKeyMSB2;        // 0x06C - Ciphering key
#ifdef __G1__
  u16           u16_PowerResult[3];       // 0x06E       - Power measurement result
  #else //__B1__
  u16           u16_spare_01[3];   // 0x06E
  #endif
  WinRes_t      RxWinNB[4];                 // 0x074       - Results for NB
  WinRes_t      RxWinFB;                  // 0x0B4       - Results for FCH
  WinRes_t      RxWinSB;                  // 0x0C4       - Results for SCH

  u16           u16_SchStatus;            // 0x0D4       - Bfi and ErrorCount for SB
  u16           au16_SchInfo[2];          // 0x0D6       - SCH data
  u16           u16_RxNBcchBuffer;        // 0x0DA       - Bfi and ErrorCount for NBCCH and PTCCH
  u16           au16_RxNBcchInfo[12];     // 0x0DC       - xCCH and PTCCH data
  u16           u16_RxTchBuffer0;         // 0x0F4        - Bfi,...
  u16           u16_RxErrorCount0;        // 0x0F6       - TCH and PDCH buffer 0 ErrorCount
  u16           u16_RxMeanBEP0;           // 0x0F8       - PDCH Mean Bit Error probability
  u16           u16_RxCvBEP0;             // 0x0FA       - PDCH CoVariance Bit Error probability
  u16           au16_RxTchInfo0[79];      // 0x0FC       - TCH and PDCH data buffer
  u16           u16_RxTchBuffer1;         // 0x19A       - Bfi,...
  u16           u16_RxErrorCount1;        // 0x19C       - TCH and PDCH buffer 0 ErrorCount
  u16           u16_RxMeanBEP1;           // 0x19E       - PDCH Mean Bit Error probability
  u16           u16_RxCvBEP1;             // 0x1A0       - PDCH CoVariance Bit Error probability
  u16           au16_RxTchInfo1[79];      // 0x1A2       - TCH and PDCH data buffer
  u16           u16_RxTchBuffer2;         // 0x240       - Bfi,...
  u16           u16_RxErrorCount2;        // 0x242       - TCH and PDCH buffer 0 ErrorCount
  u16           u16_RxMeanBEP2;           // 0x244       - PDCH Mean Bit Error probability
  u16           u16_RxCvBEP2;             // 0x246       - PDCH CoVariance Bit Error probability
  u16           au16_RxTchInfo2[79];      // 0x248       - TCH and PDCH data buffer
  u16           u16_RxTchBuffer3;         // 0x2E6 - Bfi,...
  u16           u16_RxErrorCount3;        // 0x2E8 - TCH and PDCH buffer 0 ErrorCount
  u16           u16_RxMeanBEP3;           // 0x2EA - PDCH Mean Bit Error probability
  u16           u16_RxCvBEP3;             // 0x2EC - PDCH CoVariance Bit Error probability
  u16           au16_RxTchInfo3[79];      // 0x2EE - TCH and PDCH data buffer
  u16           u16_RxFacchBuffer;        // 0x38C - Bfi and ErrorCount for FACCH
  u16           au16_RxFacchInfo[12];     // 0x38E - FACCH data
  u16           u16_TxRachInfo;           // 0x3A6 - RACH data
  u8             u8_TxRachBsic;           // 0x3A8 - RACH BSIC
  u8             u8_TxRachTs;           // 0x3A9 - RACH Training sequence
  u16           au16_TxNBcchInfo[12];     // 0x3AA - xCCH and PTCCH data
  u16           u16_TxTchBuffer0;         // 0x3C2 - Parameters for TCH and PDCH buffer 0
  u16           au16_TxTchInfo0[79];      // 0x3C4 - TCH data buffer
  u16           u16_TxTchBuffer1;         // 0x462 - Parameters for TCH and PDCH buffer 1
  u16           au16_TxTchInfo1[79];      // 0x464 - TCH data buffer
  u16           u16_TxTchBuffer2;         // 0x502 - Parameters for TCH and PDCH buffer 2
  u16           au16_TxTchInfo2[79];      // 0x504 - TCH data buffer
  u16           u16_TxTchBuffer3;         // 0x5A2 - Parameters for TCH and PDCH buffer 3
  u16           au16_TxTchInfo3[79];      // 0x5A4 - TCH data buffer
  u16           au16_TxFacchInfo[12];     // 0x642 - FACCH data
  u8             u8_TxFmtBurst0Pre;          // 0x65A - Number of symbols before burst 0
  u8             u8_TxFmtBurst0Post;         // 0x65B - Number of symbols after burst 0
  u8             u8_TxFmtBurst1Pre;         // 0x65C - Number of symbols before burst 1
  u8             u8_TxFmtBurst1Post;        // 0x65D - Number of symbols after burst 1
  u8             u8_TxFmtBurst2Pre;            // 0x65E - Number of symbols before burst 2
  u8             u8_TxFmtBurst2Post;              // 0x65F - Number of symbols after burst 2
  u8             u8_TxFmtBurst3Pre;             // 0x660 - Number of symbols before burst 3
  u8             u8_TxFmtBurst3Post;              // 0x661 - Number of symbols after burst 3
  #ifdef __G1__
  u16           u16_RficRxWidth;         // 0x662 - RX samples width in bits (min = 10; max = 16) depends on the radio
  u16           au16_DebugReg[32];        // 0x664 - Debug Registers
  ///////////////////// Audio or Appli Params ////////////////////
  u16           u16_AudioFir[32];         // 0x6A4 - Audio Fir Param predistorsions coeff
  u16           u16_SwIntCount;           // 0x6E4 - Idle Timing Control
  u16           u16_SwSwapPeriod;         // 0x6E6 - Dsp timer period
  u16           u16_AudioRunCtrl;         // 0x6E8 - Run Appli parameters
  u16           u16_DigitalGain[2];       // 0x6EA - Run Appli parameters
  u16           u16_AudioFifoCtrl;        // 0x6EE - Audio Samples transfer control
  u16           u16_MemoRecoStatus;       // 0x6F0 - Memo Status
  u16           u16_PlayAdd;              // 0x6F2 - Encoder speech adress source for playback
	u16					 u16_AecRunCtrl;						// 0x6F4
	u16					 u16_EcState;								// 0x6F6
	u16					 u16_NTaps;									// 0x6F8
	u16					 u16_DtThr;									// 0x6FA
	u16					 u16_NlpMin;								// 0x6FC
	u16					 u16_NlpShift;							// 0x6FE
	u16					 u16_MaxCng;								// 0x700
	u16					 u16_ToneDetThres;					// 0x702
	u16					 u16_NsMinWeight;						// 0x704
	u16					 u16_RefSmoothingMag;				// 0x706
	u16					 u16_DtSensThr;							// 0x708
	u16					 u16_InAgcMaxLevel;					// 0x70A
	u16				 	 u16_InAgcMinLevel;					// 0x70C
	u16					 u16_InAgcClippingLevel;		// 0x70E
	u16					 u16_InAgcPeriod;						// 0x710
	u16					 u16_InAgcMaxGainH;					// 0x712
	u16					 u16_InAgcMacGainL;					// 0x714
	u16					 u16_InAgcMinGainH;					// 0x716
	u16					 u16_InAgcMinGainL;					// 0x718
	u16					 u16_OutAgcMaxLevel;				// 0x71A
	u16					 u16_OutAgcMinLevel;				// 0x71C
	u16					 u16_OutAgcClippingLevel;		// 0x71E
	u16					 u16_OutAgcPeriod;					// 0x720
	u16					 u16_OutAgcMaxGain;					// 0x722
	u16					 u16_LpfCuttOff;						// 0x724
	u16					 u16_RapidDtThresH;					// 0x726
	u16					 u16_RapidDtThresL;					// 0x728
	u16					 u16_FreqDt;								// 0x72A
	u16					 u16_StreamingAmrAdd;				// 0x72C
  u16                                    u16_AudioTestMlsMask; //< @0x72E
  u16                                    u16_AudioTestConfig; //< @0x730
  u16                                    u16_MelVoices_2;     ///< @0x732 - Melody Mask for voices 16->31 (bit n set ==> voice 16+n not active)
  u16                                    u16_MelVoices_3;     ///< @0x734 - Melody Mask for voices 32->47 (bit n set ==> voice 32+n not active)
  u16                                    u16_MelVoices_4;     ///< @0x736 - Melody Mask for voices 48->63 (bit n set ==> voice 48+n not active)
  u8						 u8_TxFmtSymbGmsk;	// Value in DigRf format of the added symbols for GMSK modulation
    u8					 u8_TxFmtSymb8psk;	// Value in DigRf format of the added symbols for 8PSK modulation
  u16     u16_C_I_Nb[4]; // 0x73A
  u16     u16_PowerResultExt1[1]; // @0x742 - Power measurement result extension 1
  u16     au16_Free[93];//0x744
  #else //__B1__
  u8       u8_TxFmtSymbGmsk; // 0x662 - Value in DigRf format of the added symbols for GMSK modulation
  u8       u8_TxFmtSymb8psk;  // 0x663 - Value in DigRf format of the added symbols for 8PSK modulation
  u16     u16_RficRxWidth;         // 0x664 - RX samples width in bits (min = 10; max = 16) depends on the radio
  u16     au16_DebugReg[32];    // 0x666 - Debug Registers
  ///////////////////// Audio or Appli Params ////////////////////
  u16     u16_AudioFir[32];         // 0x6A6 - Audio Fir Param predistorsions coeff
  u16     u16_SwIntCount;           // 0x6E6 - Idle Timing Control
  u16     u16_SwSwapPeriod;         // 0x6E8 - Dsp timer period
  u16     u16_AudioRunCtrl;         // 0x6EA - Run Appli parameters
  u16     u16_DigitalGain[2];       // 0x6EC - Run Appli parameters
  u16     u16_AudioFifoCtrl;        // 0x6F0 - Audio Samples transfer control
  u16     u16_MemoRecoStatus;       // 0x6F2 - Memo Status
  u16     u16_PlayAdd;              // 0x6F4 - Encoder speech adress source for playback
 u16      u16_AecRunCtrl;      // 0x6F6
 u16      u16_EcState;        // 0x6F8
 u16      u16_NTaps;         // 0x6FA
 u16      u16_DtThr;         // 0x6FC
 u16      u16_NlpMin;        // 0x6FE
 u16      u16_NlpShift;       // 0x700
 u16      u16_MaxCng;        // 0x702
 u16      u16_ToneDetThres;     // 0x704
 u16      u16_NsMinWeight;      // 0x706
 u16      u16_RefSmoothingMag;    // 0x708
 u16      u16_DtSensThr;       // 0x70A
 u16      u16_InAgcMaxLevel;     // 0x70C
 u16       u16_InAgcMinLevel;     // 0x70E
 u16      u16_InAgcClippingLevel;  // 0x710
 u16      u16_InAgcPeriod;      // 0x712
 u16      u16_InAgcMaxGainH;     // 0x714
 u16      u16_InAgcMacGainL;     // 0x716
 u16      u16_InAgcMinGainH;     // 0x718
 u16      u16_InAgcMinGainL;     // 0x71A
 u16      u16_OutAgcMaxLevel;    // 0x71C
 u16      u16_OutAgcMinLevel;    // 0x71E
 u16      u16_OutAgcClippingLevel;  // 0x720
 u16      u16_OutAgcPeriod;     // 0x722
 u16      u16_OutAgcMaxGain;     // 0x724
 u16      u16_LpfCuttOff;      // 0x726
 u16      u16_RapidDtThresH;     // 0x728
 u16      u16_RapidDtThresL;     // 0x72A
 u16      u16_FreqDt;        // 0x72C
 u16      u16_StreamingAmrAdd;    // 0x72E
 u16      u16_AudioTestMlsMask; //0x730
 u16      u16_AudioTestConfig; //0x732
 u16      u16_AecDelayLineInit; //0x734
 u16      u16_C_I_Nb[4];           //0x736 - Signal to interference measurement
 u16      u16_PowerResult[4];       // 0x73E - Power measurement result
 u16      au16_Free[92]; // 0x746
  #endif //__G1__
} W5Dpram_t;

/*** Structure to initialize the DPRAM ***/
typedef struct W5TabDpRam_s
{
 u16 Table[1024];  //AKO - 20/09/05: change from 512 to 1024 size of DPRAM (512 with FPGA, 1024 on G1)
} W5TabDpRam_t;

///////////////////////////////////////////////////////////////////////////////////////////////
//*** Rfic Rx Width
#define DPRAM_RFIC_RX_WIDTH_13     13
#define DPRAM_RFIC_RX_WIDTH_16     16
//*** Channel attributes ****
#define DPRAM_TCH_CHANNEL_TYPE_MSK       (0x007F<<0)
#define DPRAM_TCH_FS                     (0x0002<<0)
#define DPRAM_TCH_HS                     (0x0003<<0)
#define DPRAM_TCH_AFS                    (0x0006<<0)
#define DPRAM_TCH_AHS                    (0x0007<<0)
#define DPRAM_TCH_F14_4                  (0x0008<<0)
#define DPRAM_TCH_F96                    (0x000A<<0)
#define DPRAM_TCH_F48                    (0x000C<<0)
#define DPRAM_TCH_F24                    (0x000E<<0)
#define DPRAM_TCH_H48                    (0x000B<<0)
#define DPRAM_TCH_H24                    (0x000D<<0)
#define DPRAM_DTXUPLNK                   (0x0001<<7)
#define DPRAM_DTXDWLNK                   (0x0001<<8)
#define DPRAM_HALFRATE_SCN1              (0x0001<<9)

// **** SacchStartFn *****
#define DPRAM_SACCH_START_FRAME_POS      0
#define DPRAM_SACCH_START_FRAME_MSK      (0x007F<<DPRAM_SACCH_START_FRAME_POS)
//*** AMR link control ***
#define DPRAM_AMR_ACS_MSK               (0x00FF<<0)
#define DPRAM_AMR_ICM_POS               8
#define DPRAM_AMR_ICM_MSK               (0x0003<<DPRAM_AMR_ICM_POS)
#define DPRAM_AMR_ACK_POS               10
#define DPRAM_AMR_ACK_MSK               (0x0003<<DPRAM_AMR_ACK_POS)
#define DPRAM_AMR_ACK_OK                (0x0001<<DPRAM_AMR_ACK_POS)
#define DPRAM_AMR_ACK_ERROR             (0x0002<<DPRAM_AMR_ACK_POS)
#define DPRAM_AMR_ACK_UNKNOWN           (0x0003<<DPRAM_AMR_ACK_POS)
#define DPRAM_AMR_EVEN_PHASE            (0x0001<<12)
#define DPRAM_AMR_RESET_TX              (0x0001<<13)
#define DPRAM_AMR_RESET_RX              (0x0001<<14)

//*** AMR Hysteresis & Threshold ***
#define DPRAM_AMR_THRESH_MSK            (0x003F<<0)
#define DPRAM_AMR_HYSTER_POS            6
#define DPRAM_AMR_HYSTER_MSK            (0x000F<<DPRAM_AMR_HYSTER_POS)

//*** AMR Rx codecs mode ***
#define DPRAM_AMR_CODEC_MSK             0x0007
#define DPRAM_AMR_CODEC_4K_75           0
#define DPRAM_AMR_CODEC_5K_15           1
#define DPRAM_AMR_CODEC_5K_9            2
#define DPRAM_AMR_CODEC_6K_7            3
#define DPRAM_AMR_CODEC_7K_4            4
#define DPRAM_AMR_CODEC_7K_95           5
#define DPRAM_AMR_CODEC_10K_2           6
#define DPRAM_AMR_CODEC_12K_2           7

//*** AMR Rx frame type ***/
#define DPRAM_AMR_RX_FRAMETYPE_MSK              0x000F
#define DPRAM_AMR_RX_SPEECH_GOOD                0
#define DPRAM_AMR_RX_SPEECH_PROBABLY_BAD        1
#define DPRAM_AMR_RX_SPEECH_SPARE               2
#define DPRAM_AMR_RX_SPEECH_BAD                 3
#define DPRAM_AMR_RX_SPEECH_SPEECH_SID_FIRST    4
#define DPRAM_AMR_RX_SPEECH_SID_UPDATE          5
#define DPRAM_AMR_RX_SPEECH_SID_BAD             6
#define DPRAM_AMR_RX_SPEECH_SPEECH_NO_DATA      7
#define DPRAM_AMR_RX_SPEECH_SPEECH_N_FRAMETYPES 8

//*** Tx Frame Type ***
#define DPRAM_AMR_TX_FRAMETYPE_MSK              0x000F
#define DPRAM_AMR_TX_SPEECH_GOOD                0
#define DPRAM_AMR_TX_SID_FIRST                  1
#define DPRAM_AMR_TX_SID_UPDATE                 2
#define DPRAM_AMR_TX_NO_DATA                    3
#define DPRAM_AMR_TX_SPEECH_DEGRADED            4
#define DPRAM_AMR_TX_SPEECH_BAD                 5
#define DPRAM_AMR_TX_SID_BAD                    6
#define DPRAM_AMR_TX_ONSET                      7
#define DPRAM_TX_N_FRAMETYPES                   8

// *** TCH miscellanous Flag ****
#define DPRAM_AMR_DRX                           (0x0001<<0)
#define DPRAM_DTX_USED                          (0x0001<<1)
#define DPRAM_SPEECH_DETECT_IND                 (0x0001<<2)
#define DPRAM_CMR_POS                           4
#define DPRAM_CMR_MSK                           (0x0003<<DPRAM_CMR_POS)

//*** FCH Energy Threshold ***
#define DPRAM_FCH_ENERGY_THRES_MSK              (0xFFFF<<0)

//*** FCH and FACCH Detection Threshold ***
#define DPRAM_FCH_DETECT_THRES_POS              0
#define DPRAM_FCH_DETECT_THRES_MSK              (0x000F<<DPRAM_FCH_DETECT_THRES_POS)
#define DPRAM_FACCH_DETECT_THRES_POS            8
#define DPRAM_FACCH_DETECT_THRES_MSK            (0x00FF<<DPRAM_FACCH_DETECT_THRES_POS)

//*** ErrCnt And TchUfiThres  ***
#define DPRAM_ERROR_COUNT_THRES_POS             0
#define DPRAM_ERROR_COUNT_THRES_MSK             0x00FF
#define DPRAM_HR_UFI_DETECT_THRES_POS           8
#define DPRAM_HR_UFI_DETECT_THRES_MSK           0xFF00

#define DPRAM_ERROR_COUNT_THRES                 0x0032 /* 50 */
#define DPRAM_HR_UFI_DETECT_THRES               0x0010 /* 16 */

// ***** Multi Slot Foi Thres ****
#define DPRAM_MS_FOI_THRES_MSK              (0xFFFF<<0)

// *** Incremental redundancy control *****
#define DPRAM_IR_RLC_WIN_LEN_MSK                0x03FF
#define DPRAM_IR_TFI_POS                        10
#define DPRAM_IR_TFI_MSK                        0x7C00
#define DPRAM_IR_SW_ON_POS                      15
#define DPRAM_IR_SW_ON                          0x8000

// **** IR Nb Block Max & IR Nb Block Used ****
#define DPRAM_IR_NB_BLOCK_MAX                   0x0083  /* max value = 131 */

// **** IR Counters *****
#define DPRAM_IR_CNT_MSK                        (0x07FF)

// **** IR Blnd detetction counters  *****
#define DPRAM_BLIND_DETECT_CNT__MSK             (0xFFFF)

// *** EDGE algo control
#define DPRAM_IR_TEST                    0x0001
#define DPRAM_MS_WMF                     0x0002
#define DPRAM_CSTS_NO_LOAD               0x0004
#define DPRAM_IR_BUFF_SPLIT              0x0008

// *** Rx CH Tracking (8PSK config) ***
#define DPRAM_RX_CH_TRACK_MJU            0x051F          /* 1311 */
#define DPRAM_RX_CH_TRACK_STEP           0x000F          /* 15 */
#define DPRAM_RX_CH_TRACK_NBUPDATE       0x0400          /* 4 << 8 */

// **** RX Auto calibration control  *****
#define DPRAM_RX_AUTOCAL_CTRL_N_MSK      (0x000F<<0)
#define DPRAM_RX_AUTOCAL_CTRL_ON         (0x0001<<4)

// *** u16_MuteCtrlLoopBackMode ***
// Mute Ctrl
#define DPRAM_MUTETX                     (0x0001<<0)
#define DPRAM_MUTERX                     (0x0001<<1)
#define DPRAM_UNMUTETX_MSK         0x0001
#define DPRAM_UNMUTERX_MSK         0x0002

// LoopBack Mode
#define DPRAM_LOOP_MSK                   (0x00FF<<8)
#define DPRAM_A_LOOP                     (0x0001<<8)
#define DPRAM_B_LOOP                     (0x0001<<9)
#define DPRAM_C_LOOP                     (0x0001<<10)
#define DPRAM_D_LOOP                     (0x0001<<11)
#define DPRAM_E_LOOP                     (0x0001<<12)
#define DPRAM_F_LOOP                     (0x0001<<13)
#define DPRAM_VOC_LOOP                   (0x0001<<14)
#define DPRAM_EDGE_LOOP                  (0x0001<<15)
#define DPRAM_FIFO_LOOP     (0x0001<<5)
#define DPRAM_MLS_MODE     (0x0001<<6)
#define DPRAM_MIXING_LOOP     (0x0001<<7)


// *** SchStatus ***
#define DPRAM_SCH_BFI                    (0x0001<<0)
#define DPRAM_SCH_ERRCNT_POS             8
#define DPRAM_SCH_ERRCNT_MSK             (0x00FF<<DPRAM_SCH_ERRCNT_POS)

/*** Rx buffers ***/
#define DPRAM_RX_CS_POS                  0
#define DPRAM_RX_CS_MSK                  0x000F
#define DPRAM_RX_CS1                     0x0000
#define DPRAM_RX_CS2                     0x0001
#define DPRAM_RX_CS3                     0x0002
#define DPRAM_RX_CS4                     0x0003
#define DPRAM_RX_MCS1                    0x0004
#define DPRAM_RX_MCS2                    0x0005
#define DPRAM_RX_MCS3                    0x0006
#define DPRAM_RX_MCS4                    0x0007
#define DPRAM_RX_MCS5                    0x0008
#define DPRAM_RX_MCS6                    0x0009
#define DPRAM_RX_MCS7                    0x000A
#define DPRAM_RX_MCS8                    0x000B
#define DPRAM_RX_MCS9                    0x000C

#define DPRAM_RX_TCH_BFI                 (0x0001<<4)
#define DPRAM_RX_TCH_BFI_POS             4
#define DPRAM_RX_E_BFI_1                 (0x0001<<5)
#define DPRAM_RX_E_BFI_1_POS             5
#define DPRAM_RX_E_BFI_2                 (0x0001<<6)
#define DPRAM_RX_E_BFI_2_POS             6
#define DPRAM_RX_TAF                     (0x0001<<7)
#define DPRAM_RX_SID_MSK                 (0x0003<<8)
#define DPRAM_RX_UFI                     (0x0001<<10)

//*** Rx TCH Error count ***
#define DPRAM_RX_ERR_CNT_MSK             (0x03FF<<0)

//*** RLC/MAC header
#define DPRAM_RX_HEADER_USF_MSK	   (0x0007 <<0)

//*** Mean bit error probabilty
#define DPRAM_RX_MEAN_BEP_MSK            (0xEFFF<<0)

//*** Co Variance bit error probabilty
#define DPRAM_RX_MEAN_BEP_MSK            (0xEFFF<<0)

// **** Decoded FACCH  informations
#define DPRAM_RX_FACCH_BFI               (0x0001<<0)
#define DPRAM_RX_FACCH_ERR_CNT_POS       8
#define DPRAM_RX_FACCH_ERR_CNT_MSK       (0x00FF<<DPRAM_RX_FACCH_ERR_CNT_POS)

// **** Acces Burst ****
#define DPRAM_TX_AB_INFO_MSK             (0x03FF<<0)
#define DPRAM_TX_AB_BSIC_MSK             (0x003F<<0)
#define DPRAM_TX_AB_TS_MSK                 (0x03)

#define DPRAM_TX_AB_TS0      0
#define DPRAM_TX_AB_TS1      1
#define DPRAM_TX_AB_TS2      2

/*** Tx TCH buffers ***/
#define DPRAM_TX_CS_POS                  0
#define DPRAM_TX_CS_MSK                  (0x000F<<DPRAM_TX_CS_POS)
#define DPRAM_TX_CS1                     (0x0000<<DPRAM_TX_CS_POS)
#define DPRAM_TX_CS2                     (0x0001<<DPRAM_TX_CS_POS)
#define DPRAM_TX_CS3                     (0x0002<<DPRAM_TX_CS_POS)
#define DPRAM_TX_CS4                     (0x0003<<DPRAM_TX_CS_POS)
#define DPRAM_TX_MCS1                    (0x0004<<DPRAM_TX_CS_POS)
#define DPRAM_TX_MCS2                    (0x0005<<DPRAM_TX_CS_POS)
#define DPRAM_TX_MCS3                    (0x0006<<DPRAM_TX_CS_POS)
#define DPRAM_TX_MCS4                    (0x0007<<DPRAM_TX_CS_POS)
#define DPRAM_TX_MCS5                    (0x0008<<DPRAM_TX_CS_POS)
#define DPRAM_TX_MCS6                    (0x0009<<DPRAM_TX_CS_POS)
#define DPRAM_TX_MCS7                    (0x000A<<DPRAM_TX_CS_POS)
#define DPRAM_TX_MCS8                    (0x000B<<DPRAM_TX_CS_POS)
#define DPRAM_TX_MCS9                    (0x000C<<DPRAM_TX_CS_POS)
#define DPRAM_TX_PADDING_EN              0x10
#define DPRAM_TX_PS1_POS                 5
#define DPRAM_TX_PS1_MSK                 (0x0003<<DPRAM_TX_PS1_POS)
#define DPRAM_TX_PS11                    (0x0000<<DPRAM_TX_PS1_POS)
#define DPRAM_TX_PS12                    (0x0001<<DPRAM_TX_PS1_POS)
#define DPRAM_TX_PS13                    (0x0002<<DPRAM_TX_PS1_POS)
#define DPRAM_TX_PS2_POS                 7
#define DPRAM_TX_PS2_MSK                 (0x0003<<DPRAM_TX_PS2_POS)
#define DPRAM_TX_PS21                    (0x0000<<DPRAM_TX_PS2_POS)
#define DPRAM_TX_PS22                    (0x0001<<DPRAM_TX_PS2_POS)
#define DPRAM_TX_PS23                    (0x0002<<DPRAM_TX_PS2_POS)
#define DPRAM_TX_AB_TYPE_POS             9
#define DPRAM_TX_AB_TYPE_MSK             (0x0003<<DPRAM_TX_AB_TYPE_POS)
#define DPRAM_TX_RACH                    (0x0001<<DPRAM_TX_AB_TYPE_POS)
#define DPRAM_TX_EXT_RACH                (0x0002<<DPRAM_TX_AB_TYPE_POS)
#define DPRAM_TX_TS_TYPE_POS		11
#define DPRAM_TX_TS_TYPE_MSK		(0x0001<<DPRAM_TX_TS_TYPE_POS)

/* PDCH Buffer Field info */
#define DPRAM_HEADERBUF_POS              0

#define DPRAM_RXEPDCH_E_FBI_BIT1_POS     3  /* u16 indexation */
#define DPRAM_TXEPDCH_E_TI_BIT1_POS      3  /* u16 indexation */
#define DPRAM_DATA1BUF_POS               4  /* u16 indexation */

#define DPRAM_RXEPDCH_E_FBI_BIT2_POS    41  /* u16 indexation */
#define DPRAM_TXEPDCH_E_TI_BIT2_POS     41  /* u16 indexation */
#define DPRAM_DATA2BUF_POS              42  /* u16 indexation */

// **** Guard bits ****
#define DPRAM_GUARD_BITS_PRE0_POS         0
#define DPRAM_GUARD_BITS_PRE1_POS         8
#define DPRAM_GUARD_BITS_PRE2_POS         0
#define DPRAM_GUARD_BITS_PRE3_POS         8
#define DPRAM_GUARD_BITS_POS3_POS         0
#define DPRAM_GUARD_BITS_NB_POS           8
#define DPRAM_GUARD_BITS_NB_SYM_MSK       (0x00FF)
#define DPRAM_GUARD_BITS_NB_PREUSE_MSK    (0x000F)

/*** Echo cancellation ***/
#define DPRAM_AEC_INIT_FLAG               (0x001 << 0)
#define DPRAM_NR_INIT_FLAG                (0x001 << 1)
#define DPRAM_AEC_FLAG_EN                 (0x001 << 2)
#define DPRAM_NR_FLAG_EN                  (0x001 << 3)
#define DPRAM_AEC_LEVEL_MSK               (0x03F << 0)
#define DPRAM_AEC_LEVEL_POS               0
#define DPRAM_AEC_FILTER_LEN_MSK          (0x1FF << 6)
#define DPRAM_AEC_FILTER_LEN_POS          6

/*** DSP Error Label ***/
#define DPRAM_DSP_ERROR_VOCODER           (0x1 << 0)
#define DPRAM_DSP_ERROR_CIPHERING_ALG     (0x1 << 1)
#define DPRAM_DSP_ERROR_CHANNEL_MODE      (0x1 << 2)
#define DPRAM_DSP_ERROR_TCH_TYPE          (0x1 << 3)
#define DPRAM_DSP_ERROR_SAMPLE_MIN        (0x1 << 4)
#define DPRAM_DSP_ERROR_SAMPLE_MAX        (0x1 << 5)
#define DPRAM_DSP_ERROR_RX_PROC_TYPE      (0x1 << 6)
#define DPRAM_DSP_ERROR_TX_PROC_TYPE      (0x1 << 8)
#define DPRAM_DSP_ERROR_NO_SACCH_ENC      (0x1 << 9)
#define DPRAM_DSP_ERROR_NO_TCH_ENC        (0x1 << 10)
#define DPRAM_DSP_ERROR_NO_RACH_ENC       (0x1 << 11)
#define DPRAM_DSP_ERROR_PCM               (0x1 << 12)
#define DPRAM_DSP_ERROR_PDCH_BITMAP       (0x1 << 12)
#define DPRAM_DSP_ERROR_PDCH_TX_CS        (0x1 << 13)
#define DPRAM_DSP_ERROR_PDCH_AB           (0x1 << 14)
#define DPRAM_DSP_ERROR_PDCH_NB           (0x1 << 15)

/*** DSP Error Label2 ***/
#define DPRAM_DSP_ERROR_REP0              (0x1 << 0)


/*** MemoStatus ***/
#define DPRAM_MEMO_FDUPLEX               (0x0001<<0)
#define DPRAM_MEMO_RESET                 (0x0001<<1)
#define DPRAM_MEMO_RECORD                (0x0001<<2)
#define DPRAM_MEMO_PLAYBACK              (0x0001<<3)
#define DPRAM_MEMO_BUFFER_FULL           (0x0001<<4)

/*** Audio ***/
#define DPRAM_AUDIO_FIFO_TX_WORDS_SHIFT  3
#define DPRAM_AUDIO_FIFO_RX_WORDS_SHIFT  8

/*** Audio run control ***/
#define DPRAM_I2S_SELECT_FLAG            0x0001
#define DPRAM_DECODE_CONTROL_FLAG        0x0002
#define DPRAM_MP3_ENABLE_FLAG            0x0004
#define DPRAM_AAC_ENABLE_FLAG            0x0008
#define DPRAM_MELODY_ENABLE_FLAG         0x0010
#define DPRAM_AEC_ENABLE_FLAG            0x0020
#define DPRAM_NR_ENABLE_FLAG             0x0040
#define DPRAM_PREDIST_ENABLE_FLAG        0x0080
#define DPRAM_DAI_LOOP_FLAG              0x0100
#define DPRAM_DIG_INGAIN_ENABLE_FLAG     0x0200
#define DPRAM_DIG_OUTGAIN_ENABLE_FLAG    0x0400
#define DPRAM_EQUAL_ENABLE_FLAG          0x0800
#define DPRAM_DUAL_MIC_HF_ENABLE         0x1000
#define DPRAM_DIG_GAIN_INIT_FLAG_BIT     0x2000
#define DPRAM_STREAMING_AMR_ENABLE       0x4000

/***  AEC run ctrl ***/
#define DPRAM_CNG_ON                     0x0001
#define DPRAM_TONE_DET_ON                0x0002
#define DPRAM_NS_ON                      0x0004
#define DPRAM_START_HALF_DUPLEX          0x0008
#define DPRAM_ANTI_HOWLING_ON            0x0010
#define DPRAM_REF_SMOOTHING_ON           0x0020
#define DPRAM_REDUCE_FE_GAIN_ON          0x0040
#define DPRAM_NOISE_SUPPR_ON             0x0080
#define DPRAM_RUN_IN_AGC                 0x0100
#define DPRAM_RUN_OUT_AGC                0x0200

/***  AEC states ***/
#define DPRAM_IAEC_DTDETECTED            0x0040
#define DPRAM_IAEC_ECCONVERGED           0x0080
#define DPRAM_IAEC_NLPENABLE             0x0020
#define DPRAM_IAEC_DTENABLE              0x0010
#define DPRAM_IAEC_UPDATEENABLE          0x0002
#define DPRAM_IAEC_FEACTIVE              0x0004
#define DPRAM_IAEC_HALFDUPLEXENABLE      0x0100

/* MLS Audio test */
#define DPRAM_MLS_ORDER_MSK           0x0F
#define DPRAM_PCM_GAIN_SHIFT_MSK 0xF0
#define DPRAM_PCM_GAIN_SHIFT_POS 4

// Melody Control flag
#define DPRAM_MELODY_CONTROL_TRANSFER_OK_FLAG (1<<12)
#define DPRAM_MELODY_TRANSFERT_WORDCOUNT_MASK ((1<<12)-1)

// Debug Reg not used for debug but for nominal software
#define DPRAM_NB0_TREATMENT_OK 0x0001

/************************************************/
/* Shared registers definition                  */
/************************************************/

typedef struct W5SReg_s
{
  u16           u16_CpuToDspInt;     // 0x000
  u16           u16_Unused0;         // 0x002
  u16           u16_Unused1;         // 0x004
  u16           u16_Unused2;         // 0x006
  u16           u16_DspEventMask;    // 0x008
  u16           u16_Unused3;         // 0x00A
  u16           u16_DspEventStatus;  // 0x00C
  u16           u16_Unused4;         // 0x00E
  u16           u16_DspEventClear;   // 0x010
  u16           u16_Unused5;         // 0x012
  u16           u16_Gpeb;            // 0x014
  u16           u16_Unused6;         // 0x016
  u16           u16_DsmaNbDoubleWord;// 0x018
  u16           u16_Unused7;         // 0x01A
  u16           u16_TxWinMod0;       // 0x01C
  u16           u16_TxWinMod1;       // 0x01E
  u16           u16_Algorithms;      // 0x020
  u16           u16_MsCtrl;          // 0x022
  u16           u16_MsRxBitMap;      // 0x024
  u16           u16_Pad0;            // 0x026
  u16           u16_MsTxBitMap;      // 0x028
  u16           u16_SoftCounters;    // 0x02A
  u16           u16_SwDer5;             // 0x02C
  u16           u16_SwDer6;             // 0x02E
  u16           u16_SwDer7;             // 0x030
  u16           u16_SwDer8;             // 0x032
  u16           u16_SwDer9;             // 0x034
  u16           u16_SwDer10;             // 0x036

  u16           u16_SwTrace0;        // 0x038
  u16           u16_SwTrace1;        // 0x03A
  u32           u32_PatchCtrl;       // 0x03C
  u32           u32_Break1;          // 0x040
  u32           u32_Break2;          // 0x044
  u32           u32_Break3;          // 0x048
  u32           u32_Break4;          // 0x04C
  u16           u16_BranchF1;        // 0x050
  u16           u16_BranchS1;        // 0x052
  u16           u16_BranchF2;        // 0x054
  u16           u16_BranchS2;        // 0x056
  u16           u16_BranchF3;        // 0x058
  u16           u16_BranchS3;        // 0x05A
  u16           u16_BranchF4;        // 0x05C
  u16           u16_BranchS4;        // 0x05E
  u32           u32_PriorityCtrl;    // 0x060
  u16           u16_Spare;            // 0x064
  u16           u16_Free[29];         // 0x066
#ifdef __G1__
  u16           u16_SoftTaskCtrl0;    // 0x0A0   or SHARED0
  u16           u16_SoftTaskCtrl1;    // 0x0A2   or SHARED1
  u16           u16_BurstStatus;      // 0x0A4   or SHARED2
  u16           u16_BufferCtrl;       // 0x0A6   or SHARED3
  u16           u16_BlockStatus;      // 0x0A8   or SHARED4
  u16           u16_BfiStatus;        // 0x0AA   or SHARED5
  u16           u16_Shared6;          // 0x0AC
  u16           u16_AudioInitCtrl;    // 0x0AE   or SHARED7
  u16           u16_Shared8;          // 0x0B0
  u16           u16_Shared9;          // 0x0B2
  u16           u16_Shared10;         // 0x0B4
  u16           u16_Shared11;         // 0x0B6
  u16           u16_Shared12;         // 0x0B8
  u16           u16_Shared13;         // 0x0BA
  u16           u16_Shared14;         // 0x0BC
  u16           u16_Shared15;         // 0x0BE
#else //__B1__
  u16           u16_SoftTaskCtrl0;    // 0x0A0   or SHARED0
  u16           u16_Shared1;            // 0x0A2
  u16           u16_SoftTaskCtrl1;    // 0x0A4   or SHARED2
  u16           u16_Shared3;            // 0x0A6
  u16           u16_BurstStatus;      // 0x0A8   or SHARED4
  u16           u16_Shared5;          // 0x0AA
  u16           u16_TxBufferCtrl;       // 0x0AC   or SHARED6
  u16           u16_Shared7;          // 0x0AE
  u16           u16_BlockStatus;      // 0x0B0   or SHARED8
  u16           u16_Shared9;          // 0x0B2
  u16           u16_BfiStatus;        // 0x0B4   or SHARED10
  u16           u16_Shared11;          // 0x0B6
  u16           u16_AudioInitCtrl;    // 0x0B8   or SHARED12
  u16           u16_Shared13;          // 0x0BA
  u16           u16_RxBufferCtrl;       // 0x0BC   or SHARED14
  u16           u16_Shared15;          // 0x0BE
#endif
} W5SReg_t;

/* CpuToDspInt register */
#define SREG_DSP_RESET_STOP_MODE            0
#define SREG_DSP_RESET_BOOT_MODE              1
#define SREG_DSP_RESET_IDLE_MODE         2
#define SREG_DSP_LOADREQ_DPRAM           3
#define SREG_DSP_DOWNLOADREQ_DSMA        4
#define SREG_DSP_DOWNLOADREQ_PAGE        5
#define SREG_DSP_UPLOADREQ_DSMA          6
#define SREG_DSP_UPLOADREQ_PAGE          7

/* DspEvent mask */
#define SREG_DSP_ITRESET_MSK             (1 << 0)
#define SREG_DSP_ITCPU_MSK               (1 << 1)
#define SREG_DSP_TXSRCPROC_MSK           (1 << 2)
#define SREG_DSP_RXSRCPROC_MSK           (1 << 3)
#define SREG_DSP_FBDETECT_MSK            (1 << 4)
#define SREG_DSP_RXWIN0_MSK              (1 << 5)
#define SREG_DSP_RXWIN1_MSK              (1 << 6)
#define SREG_DSP_RXWIN2_MSK              (1 << 7)
#define SREG_DSP_RXCHNPROC_MSK           (1 << 8)
#define SREG_DSP_TXCHNPROC_MSK           (1 << 9)
#define SREG_DSP_QUICKUSF_MSK            (1 << 10)
#define SREG_DSP_PWR_MEAS_MSK            (1 << 11)
#define SREG_DSP_ERR_CNT_MSK             (1 << 12)
#define SREG_DSP_RATSCCH_MSK             (1 << 13)
#define SREG_DSP_REDPAG_MSK              (1 << 14)

/* DspEvent status */
#define SREG_DSP_ITRESET_COMPL           (1 << 0)
#define SREG_DSP_ITCPU_COMPL             (1 << 1)
#define SREG_DSP_TXSRCPROC_COMPL         (1 << 2)
#define SREG_DSP_RXSRCPROC_COMPL         (1 << 3)
#define SREG_DSP_FBDETECT_COMPL          (1 << 4)
#define SREG_DSP_RXWIN0_COMPL            (1 << 5)
#define SREG_DSP_RXWIN1_COMPL            (1 << 6)
#define SREG_DSP_RXWIN2_COMPL            (1 << 7)
#define SREG_DSP_RXCHNPROC_COMPL         (1 << 8)
#define SREG_DSP_TXCHNPROC_COMPL         (1 << 9)
#define SREG_DSP_QUICKUSF_COMPL          (1 << 10)
#define SREG_DSP_PWR_MEAS_COMPL          (1 << 11)
#define SREG_DSP_USERIT2_COMPL           (1 << 12)
#define SREG_DSP_MULTIMEDIA_COMPL        (1 << 13)
#define SREG_DSP_USERIT4_COMPL           (1 << 14)
#define SREG_DSP_TIMERTICK_COMPL           (1 << 15)

/*  TxWinMod register */
#define SREG_TX_SWAP_IQ_BIT_POS          0
#define SREG_TX_SWAP_IQ                  (0x0001<<SREG_TX_SWAP_IQ_BIT_POS)
#define SREG_TX_PROCESSING_POS           1
#define SREG_TX_PROCESSING_MSK       (0x0007<<SREG_TX_PROCESSING_POS)
#define SREG_NO_PROCESSING               (0x0000<<SREG_TX_PROCESSING_POS)
#define SREG_ACCESS_BURST                 (0x0001<<SREG_TX_PROCESSING_POS)
#define SREG_NORMAL_BURST                (0x0002<<SREG_TX_PROCESSING_POS)
#define SREG_MULTISLOT_BURST           (0x0003<<SREG_TX_PROCESSING_POS)
#define SREG_EMULTISLOT_BURST         (0x0004<<SREG_TX_PROCESSING_POS)
#define SREG_TEST_BURST                     (0x0005<<SREG_TX_PROCESSING_POS) //usefull for Wirti tool
#define SREG_TX_TRAIN_SEQ_POS            4
#define SREG_TX_TRAIN_SEQ_MSK         (0x0007<<SREG_TX_TRAIN_SEQ_POS)

/* Algorithms */
#define SREG_CIPHER_ALGO_POS            0
#define SREG_CIPHER_ALGO_MSK          (0x0007<<SREG_CIPHER_ALGO_POS)
#define SREG_A51_ALGORITHM              (0x0000<<SREG_CIPHER_ALGO_POS)
#define SREG_A52_ALGORITHM              (0x0001<<SREG_CIPHER_ALGO_POS)
#define SREG_VOICECODEC_ALGO_POS        3
#define SREG_VOICECODEC_ALGO_MSK        (0x0007<<SREG_VOICECODEC_ALGO_POS)
#define SREG_FR_VOICE                   (0x0000<<SREG_VOICECODEC_ALGO_POS)
#define SREG_EFR_VOICE                  (0x0001<<SREG_VOICECODEC_ALGO_POS)
#define SREG_HR_VOICE                   (0x0002<<SREG_VOICECODEC_ALGO_POS)
#define SREG_AMR_VOICE                  (0x0004<<SREG_VOICECODEC_ALGO_POS)
#define SREG_CHANNEL_MODE_POS           6
#define SREG_CHANNEL_MODE_MSK    (0x0003<<SREG_CHANNEL_MODE_POS)
#define SREG_DEDIC_MODE                 (0x0001<<SREG_CHANNEL_MODE_POS)
#define SREG_IDLE_MODE                    (0x0002<<SREG_CHANNEL_MODE_POS)
#define SREG_NBCCH_FAST_DEC_POS             8
#define SREG_NBCCH_FAST_DEC             (0x0001<<SREG_NBCCH_FAST_DEC_POS)
#define SREG_FAST_ERROR_COUNT_POS           9
#define SREG_FAST_ERROR_COUNT           (0x0001<<SREG_FAST_ERROR_COUNT_POS)
#define SREG_TX_BUFFER_SWAP_POS         10
#define SREG_TX_BUFFER_SWAP             (0x0001<<SREG_TX_BUFFER_SWAP_POS)
#define SREG_CIR_CLEAN_POS                11

//*** GPRS control ***
#define SREG_ALLOC_MODE_MSK             (0x0003<<0)
#define SREG_FIXED_ALLOC                (0x0000<<0)
#define SREG_DYNAMIC_ALLOC              (0x0001<<0)
#define SREG_EXT_DYNAMIC_ALLOC          (0x0002<<0)
#define SREG_BLOCK_IT_CTRL_POS           2
#define SREG_BLOCK_IT_CTRL_MSK          (0x000F<<SREG_BLOCK_IT_CTRL_POS)
#define SREG_BLOCK0_DEC_IT              (0x0000<<SREG_BLOCK_IT_CTRL_POS)
#define SREG_BLOCK1_DEC_IT              (0x0001<<SREG_BLOCK_IT_CTRL_POS)
#define SREG_BLOCK2_DEC_IT              (0x0002<<SREG_BLOCK_IT_CTRL_POS)
#define SREG_BLOCK3_DEC_IT              (0x0003<<SREG_BLOCK_IT_CTRL_POS)
#define SREG_EXTRABIT_POS               6
#define SREG_EXTRABIT_MSK               (0x0003<<SREG_EXTRABIT_POS)
#define SREG_EXTRABIT_AFT_BURST1        (0x0000<<SREG_EXTRABIT_POS)
#define SREG_EXTRABIT_AFT_BURST2        (0x0001<<SREG_EXTRABIT_POS)
#define SREG_EXTRABIT_AFT_BURST3        (0x0002<<SREG_EXTRABIT_POS)
#define SREG_EXTRABIT_AFT_BURST4        (0x0003<<SREG_EXTRABIT_POS)
#define SREG_TA_POS                     8
#define SREG_TA_MSK                     (0x007F<<SREG_TA_POS)

//*** MultiSlot RX bitmaps ***
#define SREG_RX_BITMAP_POS              0
#define SREG_RX_BITMAP_MSK              (0x000F<<SREG_RX_BITMAP_POS)
#define SREG_RX_DECODEDATA_BITMAP_POS   4
#define SREG_RX_DECODEDATA_BITMAP_MSK   (0x000F<<SREG_RX_DECODEDATA_BITMAP_POS)
#define SREG_RX_QUICK_USF_BITMAP_POS    8
#define SREG_RX_QUICK_USF_BITMAP_MSK    (0x000F<<SREG_RX_QUICK_USF_BITMAP_POS)

//*** MultiSlot TX bitmaps ***
#define SREG_TX_NB_BITMAP_POS            0
#define SREG_TX_NB_BITMAP_MSK            (0x000F<<SREG_TX_NB_BITMAP_POS)
#define SREG_TX_AB_BITMAP_POS            4
#define SREG_TX_AB_BITMAP_MSK            (0x000F<<SREG_TX_AB_BITMAP_POS)
#define SREG_TX_MAP0_POS                 8
#define SREG_TX_MAP0_MSK                 (0x0003<<SREG_TX_MAP0_POS)
#define SREG_TX_MAP1_POS                 10
#define SREG_TX_MAP1_MSK                 (0x0003<<SREG_TX_MAP1_POS)
#define SREG_TX_MAP2_POS                 12
#define SREG_TX_MAP2_MSK                 (0x0003<<SREG_TX_MAP2_POS)
#define SREG_TX_MAP3_POS                 14
#define SREG_TX_MAP3_MSK                 (0x0003<<SREG_TX_MAP3_POS)

///* Tx block mapping for GPRS ****
#define SREG_TXTCHBUFFER0_FIRST_BLOCK_POS 8
#define SREG_FIRST_BLOCK_INDEX_MASK    0xFCFF
#define SREG_TXTCHBUFFER0_FIRST_BLOCK  (0<<SREG_TXTCHBUFFER0_FIRST_BLOCK_POS)
#define SREG_TXTCHBUFFER1_FIRST_BLOCK  (1<<SREG_TXTCHBUFFER0_FIRST_BLOCK_POS)
#define SREG_TXTCHBUFFER2_FIRST_BLOCK  (2<<SREG_TXTCHBUFFER0_FIRST_BLOCK_POS)
#define SREG_TXTCHBUFFER3_FIRST_BLOCK  (3<<SREG_TXTCHBUFFER0_FIRST_BLOCK_POS)
#define SREG_TXTCHBUFFER0_SECOND_BLOCK_POS 10
#define SREG_SECOND_BLOCK_INDEX_MASK   0xF3FF
#define SREG_TXTCHBUFFER0_SECOND_BLOCK (0<<SREG_TXTCHBUFFER0_SECOND_BLOCK_POS)
#define SREG_TXTCHBUFFER1_SECOND_BLOCK (1<<SREG_TXTCHBUFFER0_SECOND_BLOCK_POS)
#define SREG_TXTCHBUFFER2_SECOND_BLOCK (2<<SREG_TXTCHBUFFER0_SECOND_BLOCK_POS)
#define SREG_TXTCHBUFFER3_SECOND_BLOCK (3<<SREG_TXTCHBUFFER0_SECOND_BLOCK_POS)
#define SREG_TXTCHBUFFER0_THIRD_BLOCK_POS 12
#define SREG_THIRD_BLOCK_INDEX_MASK    0xCFFF
#define SREG_TXTCHBUFFER0_THIRD_BLOCK  (0<<SREG_TXTCHBUFFER0_THIRD_BLOCK_POS)
#define SREG_TXTCHBUFFER1_THIRD_BLOCK  (1<<SREG_TXTCHBUFFER0_THIRD_BLOCK_POS)
#define SREG_TXTCHBUFFER2_THIRD_BLOCK  (2<<SREG_TXTCHBUFFER0_THIRD_BLOCK_POS)
#define SREG_TXTCHBUFFER3_THIRD_BLOCK  (3<<SREG_TXTCHBUFFER0_THIRD_BLOCK_POS)
#define SREG_TXTCHBUFFER0_FOURTH_BLOCK_POS 14
#define SREG_FOURTH_BLOCK_INDEX_MASK   0x3FFF
#define SREG_TXTCHBUFFER0_FOURTH_BLOCK (0<<SREG_TXTCHBUFFER0_FOURTH_BLOCK_POS)
#define SREG_TXTCHBUFFER1_FOURTH_BLOCK (1<<SREG_TXTCHBUFFER0_FOURTH_BLOCK_POS)
#define SREG_TXTCHBUFFER2_FOURTH_BLOCK (2<<SREG_TXTCHBUFFER0_FOURTH_BLOCK_POS)
#define SREG_TXTCHBUFFER3_FOURTH_BLOCK (3<<SREG_TXTCHBUFFER0_FOURTH_BLOCK_POS)

//** Soft Counters ************
#define SREG_NBCCHRX_COUNTER_POS        0
#define SREG_NBCCHRX_COUNTER_MSK        (0x0003<<SREG_NBCCHRX_COUNTER_POS)
#define SREG_NBCCHTX_COUNTER_POS        4
#define SREG_NBCCHTX_COUNTER_MSK        (0x0003<<SREG_NBCCHTX_COUNTER_POS)

#define SREG_NBCCHRX_COUNTER_WORD       0
#define SREG_NBCCHTX_COUNTER_WORD       1

#define SREG_CNT_MULTISLOT              (0x0001<<2)

#define SREG_MASK_COUNT             0x0077
#define SREG_RST_RX_COUNT           0xFFF0
#define SREG_RST_TX_COUNT           0x000F
#define SREG_INCRTX                 0x0010

//** Information for the task status **
//** soft trace 0
#define SREG_TASK0_STATUS_IDLE       (0x0000<<0)
#define SREG_TASK0_STATUS_STOP0      (0x0001<<0)
#define SREG_TASK0_STATUS_STOP1      (0x0001<<1)
#define SREG_TASK0_STATUS_IDLE2      (0x0001<<2)
#define SREG_TASK0_STATUS_BOOT       (0x0001<<3)
#define SREG_TASK0_STATUS_PCM_AUDIO  (0x0001<<4)
#define SREG_TASK0_STATUS_RX_PROC    (0x0001<<5)
#define SREG_TASK0_STATUS_TX_PROC    (0x0001<<6)
#define SREG_TASK0_STATUS_ENCOD      (0x0001<<7)
#define SREG_TASK0_STATUS_DECOD      (0x0001<<8)
#define SREG_TASK0_STATUS_CPU        (0x0001<<9)
#define SREG_TASK0_STATUS_DSMA       (0x0001<<10)
#define SREG_TASK0_STATUS_RAM        (0x0001<<11)
#define SREG_TASK0_STATUS_ROM        (0x0001<<12)
#define SREG_TASK0_STATUS_ERR        (0x0001<<13)
#define SREG_TASK0_NOTUSED14_ERR     (0x0001<<14)
#define SREG_TASK0_NOTUSED15_ERR     (0x0001<<15)

//** soft trace 1
#define SREG_TASK1_STATUS_ETX_PROC        (0x0001<<0)
#define SREG_TASK1_STATUS_ERX_GMSK_PROC   (0x0001<<1)
#define SREG_TASK1_STATUS_ERX_8PSK_PROC   (0x0001<<2)
#define SREG_TASK1_STATUS_ERX_DEC_PROC    (0x0001<<3)

//** Patch Control Register **
#define SREG_PATCH_CTRL_ENA1   (0x0001<<0)
#define SREG_PATCH_CTRL_ENA2   (0x0001<<1)
#define SREG_PATCH_CTRL_ENA3   (0x0001<<2)
#define SREG_PATCH_CTRL_ENA4   (0x0001<<3)
#define SREG_PATCH_CTRL_ACESS  (0x0001<<4)

/*** Software task control 0 ***/
#define SREG_ENCRYPTION_EN              (0x0001<<0)
#define SREG_DECRYPTION_EN              (0x0001<<1)
#define SREG_FIREDECODING               (0x0001<<2)
#define SREG_TX_SOURCE_PROC             (0x0001<<3)
#define SREG_RX_SOURCE_PROC             (0x0001<<4)
#define SREG_TX_TCH_RESET               (0x0001<<5)
#define SREG_RX_TCH_RESET               (0x0001<<6)
#define SREG_TX_SRCPROC_RESET           (0x0001<<7)
#define SREG_RX_SRCPROC_RESET           (0x0001<<8)
#define SREG_ERROR_CONCEAL              (0x0001<<9)
#define SREG_STOP_MODE0                 (0x0001<<10)
#define SREG_STOP_MODE1                 (0x0001<<11)
#define SREG_TX_BUFFER_FILL             (0x0001<<12)
#define SREG_MX_DUMP		        (0x0001<<13)
#define SREG_MULTIMEDIA_PROC            (0x0001<<13)

/*** Software task control 1 ***/
#define SREG_TASK1_IR_RESET              (0x0001<<0)
#define SREG_TASK1_EDGE_SW_RESET  (0x0001<<1)
#define SREG_TASK1_AMR_RESET_TX     (0x0001<<2)
#define SREG_TASK1_AMR_RESET_RX     (0x0001<<3)

//** Burst status **
#ifdef __G1__
#define SREG_NB0_OK                     (0x0001<<0)
#define SREG_NB1_OK                     (0x0001<<1)
#define SREG_NB2_OK                     (0x0001<<2)
#define SREG_NB3_OK                     (0x0001<<3)
#define SREG_PWR_WIN0_OK                (0x0001<<4)
#define SREG_PWR_WIN1_OK                (0x0001<<5)
#define SREG_PWR_WIN2_OK                (0x0001<<6)
#define SREG_PWR_WIN3_OK                (0x0001<<9)
#define SREG_FB_OK                      (0x0001<<7)
#define SREG_SB_OK                      (0x0001<<8)
#else //__B1__
#define SREG_NB0_OK                     (0x0001<<0)
#define SREG_NB1_OK                     (0x0001<<1)
#define SREG_NB2_OK                     (0x0001<<2)
#define SREG_NB3_OK                     (0x0001<<3)
#define SREG_PWR_WIN0_OK          (0x0001<<4)
#define SREG_PWR_WIN1_OK          (0x0001<<5)
#define SREG_PWR_WIN2_OK          (0x0001<<6)
#define SREG_PWR_WIN3_OK          (0x0001<<7)
#define SREG_FB_OK                       (0x0001<<8)
#define SREG_SB_OK                       (0x0001<<9)
#endif

//** Tx Buffer Control **
#define SREG_TX_RACH_FULL               (0x0001<<0)
#define SREG_TX_ERACH_FULL              (0x0001<<1)
#define SREG_TX_NBCCH_FULL              (0x0001<<2)
#define SREG_TX_FACCH_FULL              (0x0001<<3)
#define SREG_TX_TCH0_FULL               (0x0001<<4)
#define SREG_TX_TCH1_FULL               (0x0001<<5)
#define SREG_TX_TCH2_FULL               (0x0001<<6)
#define SREG_TX_TCH3_FULL               (0x0001<<7)
#define SREG_TX_RATSCCH_FULL            (0x0001<<8)

//** Rx Buffer Control **
//Note : event if a new Rx buffer control is present on B1, Offset remain the same
// for complexity reduction in DSP software.
#define SREG_RX_TCH0_FULL               (0x0001<<9)
#define SREG_RX_TCH1_FULL               (0x0001<<10)
#define SREG_RX_TCH2_FULL               (0x0001<<11)
#define SREG_RX_TCH3_FULL               (0x0001<<12)
#define SREG_RX_RATSCCH_FULL            (0x0001<<13)

//** Block status **
#define SREG_RX_TCH0_OK                 (0x0001<<0)
#define SREG_RX_TCH1_OK                 (0x0001<<1)
#define SREG_RX_TCH2_OK                 (0x0001<<2)
#define SREG_RX_TCH3_OK                 (0x0001<<3)
#define SREG_RX_NBCCH_OK                (0x0001<<4)
#define SREG_RX_FACCH_OK                (0x0001<<5)

//** Bfi status **
#define SREG_SCH_BFI                    (0x0001<<0)
#define SREG_BCCH_BFI                   (0x0001<<1)
#define SREG_FACCH_BFI                  (0x0001<<2)
#define SREG_XCH0_BFI                   (0x0001<<3)
#define SREG_XCH1_BFI                   (0x0001<<4)
#define SREG_XCH2_BFI                   (0x0001<<5)
#define SREG_XCH3_BFI                   (0x0001<<6)

//** Audio init control **
#define SREG_COMVOC_INIT_FLAG           0x0001
#define SREG_MP3_INIT_FLAG              0x0002
#define SREG_AAC_INIT_FLAG              0x0004
#define SREG_MELODY_INIT_FLAG           0x0008
#define SREG_AEC_INIT_FLAG              0x0010
#define SREG_NR_INIT_FLAG               0x0020
#define SREG_PREDIST_INIT_FLAG          0x0040
#define SREG_DAI_LOOP_INIT_FLAG         0x0080
#define SREG_DIG_INGAIN_INIT_FLAG       0x0100
#define SREG_DIG_OUTGAIN_INIT_FLAG      0x0200
#define SREG_EQUAL_INIT_FLAG            0x0400
#define SREG_DUAL_MIC_HF_INIT_FLAG      0x0800

/****************************************************************************/
/*        Interrupt Controller (ITCTRL) registers                           */
/****************************************************************************/
typedef struct W5IrqControl_s
{
  u32 u32_Priority12;  // INT7[31:28]  to INT0[3:0] / Priority : (0 highest, 7 lowest)
  u32 u32_Priority34;  // INT15[31:28] to INT8[3:0]
  u32 u32_Priority56;  // INT16[31:28] to INT23[3:0]
  u32 u32_Priority78;  // INT24[31:28] to INT31[3:0]
  u32 u32_Priority910; // INT32[15:12] to INT39
  u32 u32_Mapping0; // INT0  to INT31 / 0=IRQ0n 1=IRQ1n
  u32 u32_Mapping1; // INT32 to INT39 / 0=IRQ0n 1=IRQ1n
  u32 u32_Mask0; // INT0  to INT31 / 0=masked 1=not masked
  u32 u32_Mask1; // INT32 to INT39 / 0=masked 1=not masked
  u32 u32_Sensitivity0; // 0=edge  1=level
  u32 u32_Sensitivity1; // 0=edge  1=level
  u32 u32_Polarity0; // 0=low,neg   1=high,pos
  u32 u32_Polarity1; // 0=low,neg 1=high,pos
  u32 u32_Reentrant0; // 0=not reentrant 1=reentrant
  u32 u32_Reentrant1; // 0=not reentrant  1=reentrant
  u16 u16_Pending_0; //  IRQ0n
  u16 u16_Pad_0; //  IRQ0n
  u16 u16_Pending_1; //  IRQ1n
  u16 u16_Pad_1; //  IRQ1n
  u32 u32_RawStatus0; // 0=not pending 1=pending (before mask)
  u32 u32_RawStatus1; // 0=not pending 1=pending (before mask)
  u32 u32_Status0; // 0=not pending 1=pending
  u32 u32_Status1; // 0=not pending 1=pending
  u32 u32_Clear0; // 0=no effect 1=clear interrupt (EOI for an it)
  u32 u32_Clear1; // 0=no effect 1=clear interrupt (EOI for an it)
  u32 u32_Ack0; // 0=no effect 1=acknowledge interrupt
  u32 u32_Ack1; // 0=no effect 1=acknowledge interrupt
  u32 u32_Service0; // 0=not in service 1=ack but not cleared
  u32 u32_Service1; // 0=not in service 1=ack but not cleared
  u32 u32_Pad[4]; // unused
  u32 u32_WakeUpMask0; // 0=masked 1=not masked
  u32 u32_WakeUpMask1; // 0=masked 1=not masked
  u32 u32_Config; // clear all pending it (EOI) or autoack config
} W5IrqControl_t;

#define IRQCTRL_INT_ON_FIQ   0
#define IRQCTRL_INT_ON_IRQ   1

#define IRQCTRL_CLR_IRQ_ALL  0xFFFFFFFF
#define IRQCTRL_CLEARALL     0x00000100
#define IRQCTRL_AUTOACK      0x00000001

#define TBU_WAKEUP_CPU_IT_POS 2
#define TBU_WAKEUP_CPU_IT_MSK ((u32)1 << TBU_WAKEUP_CPU_IT_POS)
#define SIM2_IT_POS           33
#define SIM2_IT_MSK           ((u32)1 << SIM2_IT_POS)
#define SIM1_IT_POS           32
#define SIM1_IT_MSK           ((u32)1 << SIM1_IT_POS)
#define EX_ICE_IT_POS         31
#define EX_ICE_IT_MSK         ((u32)1 << EX_ICE_IT_POS)
#define DMAC_IT_POS           30
#define DMAC_IT_MSK           ((u32)1 << DMAC_IT_POS)
#define CMU_IT_POS            27
#define CMU_IT_MSK            ((u32)1 << CMU_IT_POS)
#define SHIFACE_IT_POS        26
#define SHIFACE_IT_MSK        ((u32)1 << SHIFACE_IT_POS)
#define DSMA_IT_POS           25
#define DSMA_IT_MSK           ((u32)1 << DSMA_IT_POS)
#define AUDIO_IT_POS          24
#define AUDIO_IT_MSK          ((u32)1 << AUDIO_IT_POS)
#define RFDL_IT_POS 23
#define RFDL_IT_MSK           ((u32)1 << RFDL_IT_POS)
#define TBU_SINTA_IT_POS      22
#define TBU_SINTA_IT_MSK      ((u32)1 << TBU_SINTA_IT_POS)
#define TBU_FINT_IT_POS       21
#define TBU_FINT_IT_MSK       ((u32)1 << TBU_FINT_IT_POS)
#define TBU_SINT3_IT_POS      20
#define TBU_SINT3_IT_MSK      ((u32)1 << TBU_SINT3_IT_POS)
#define TBU_SINT2_IT_POS      19
#define TBU_SINT2_IT_MSK      ((u32)1 << TBU_SINT2_IT_POS)
#define TBU_SINT1_IT_POS      18
#define TBU_SINT1_IT_MSK      ((u32)1 << TBU_SINT1_IT_POS)
#define TBU_SINT0_IT_POS      17
#define TBU_SINT0_IT_MSK      ((u32)1 << TBU_SINT0_IT_POS)
#define TIMEOUT_IT_POS        15
#define TIMEOUT_IT_MSK        ((u32)1 << TIMEOUT_IT_POS)
#define OSTICK_IT_POS         14
#define OSTICK_IT_MSK         ((u32)1 << OSTICK_IT_POS)
#define TIMSOFT_IT_POS         13
#define TIMSOFT_IT_MSK        ((u32)1 << TIMSOFT_IT_POS)
#define KEYBOARD_IT_POS       12
#define KEYBOARD_IT_MSK       ((u32)1 << KEYBOARD_IT_POS)
#define UART2_IT_POS          11
#define UART2_IT_MSK          ((u32)1 << UART2_IT_POS)
#define UART1_IT_POS          10
#define UART1_IT_MSK          ((u32)1 << UART1_IT_POS)
#define I2C_TRANSFER_IT_POS   9
#define I2C_TRANSFER_IT_MSK   ((u32)1 << I2C_TRANSFER_IT_POS)
#define SPI3_IT_POS           7
#define SPI3_IT_MSK           ((u32)1 << SPI3_IT_POS)
#define SPI2_IT_POS           6
#define SPI2_IT_MSK           ((u32)1 << SPI2_IT_POS)
#define SPI1_IT_POS           5
#define SPI1_IT_MSK           ((u32)1 << SPI1_IT_POS)
#define I2C_STATUS_IT_POS     4
#define I2C_STATUS_IT_MSK     ((u32)1 << I2C_STATUS_IT_POS)
#define EXT3_IT_POS           3
#define EXT3_IT_MSK           ((u32)1 << EXT3_IT_POS)
#define EXT2_IT_POS           2
#define EXT2_IT_MSK           ((u32)1 << EXT2_IT_POS)
#define EXT1_IT_POS           1
#define EXT1_IT_MSK           ((u32)1 << EXT1_IT_POS)
#define RTC_IT_POS            0
#define RTC_IT_MSK ((u32)1 << RTC_IT_POS)

/****************************************************************************/
/*        External interrupt Controller registers                           */
/****************************************************************************/

typedef struct W5ExtInt_s
{
    u32 u32_clk_deb_cfg ;
    u32 u32_cfg0 ;
    u32 u32_cfg1 ;
    u32 u32_cfg2 ;
    u32 u32_cfg3 ;
    u32 u32_int_raw_status ;
    u32 u32_int_clear ;
    u32 u32_int_mask1 ;
    u32 u32_int_status1 ;
    u32 u32_int_mask2 ;
    u32 u32_int_status2 ;
    u32 u32_int_mask3 ;
    u32 u32_int_status3 ;
    u32 u32_spare ;
} W5ExtInt_t;

/*u32_cfg0 register definitions */
#define EXT_INT_CFG0_POL_0_OS   0
#define EXT_INT_CFG0_POL_0_MSK  ((u32)1<< EXT_INT_CFG0_POL_0_OS)
#define EXT_INT_CFG0_MODE_0_OS  1
#define EXT_INT_CFG0_MODE_0_MSK ((u32)3<< EXT_INT_CFG0_MODE_0_OS)
#define EXT_INT_CFG0_DEB_0_OS   3
#define EXT_INT_CFG0_DEB_0_MSK  ((u32)7<< EXT_INT_CFG0_DEB_0_OS)
#define EXT_INT_CFG0_POL_1_OS   6
#define EXT_INT_CFG0_POL_1_MSK  ((u32)1<< EXT_INT_CFG0_POL_1_OS)
#define EXT_INT_CFG0_MODE_1_OS  7
#define EXT_INT_CFG0_MODE_1_MSK ((u32)3<< EXT_INT_CFG0_MODE_1_OS)
#define EXT_INT_CFG0_DEB_1_OS   9
#define EXT_INT_CFG0_DEB_1_MSK  ((u32)7<< EXT_INT_CFG0_DEB_1_OS)
#define EXT_INT_CFG0_POL_2_OS   12
#define EXT_INT_CFG0_POL_2_MSK  ((u32)1<< EXT_INT_CFG0_POL_2_OS)
#define EXT_INT_CFG0_MODE_2_OS  13
#define EXT_INT_CFG0_MODE_2_MSK ((u32)3<< EXT_INT_CFG0_MODE_2_OS)
#define EXT_INT_CFG0_DEB_2_OS   15
#define EXT_INT_CFG0_DEB_2_MSK  ((u32)7<< EXT_INT_CFG0_DEB_2_OS)
#define EXT_INT_CFG0_POL_3_OS   18
#define EXT_INT_CFG0_POL_3_MSK  ((u32)1<< EXT_INT_CFG0_POL_3_OS)
#define EXT_INT_CFG0_MODE_3_OS  19
#define EXT_INT_CFG0_MODE_3_MSK ((u32)3<< EXT_INT_CFG0_MODE_3_OS)
#define EXT_INT_CFG0_DEB_3_OS   21
#define EXT_INT_CFG0_DEB_3_MSK  ((u32)7<< EXT_INT_CFG0_DEB_3_OS)
#define EXT_INT_CFG0_POL_4_OS   24
#define EXT_INT_CFG0_POL_4_MSK  ((u32)1<< EXT_INT_CFG0_POL_4_OS)
#define EXT_INT_CFG0_MODE_4_OS  25
#define EXT_INT_CFG0_MODE_4_MSK ((u32)3<< EXT_INT_CFG0_MODE_4_OS)
#define EXT_INT_CFG0_DEB_4_OS   27
#define EXT_INT_CFG0_DEB_4_MSK  ((u32)7<< EXT_INT_CFG0_DEB_4_OS)

/*u32_cfg1 register definitions */
#define EXT_INT_CFG1_POL_5_OS   0
#define EXT_INT_CFG1_POL_5_MSK  ((u32)1<< EXT_INT_CFG1_POL_5_OS)
#define EXT_INT_CFG1_MODE_5_OS  1
#define EXT_INT_CFG1_MODE_5_MSK ((u32)3<< EXT_INT_CFG1_MODE_5_OS)
#define EXT_INT_CFG1_DEB_5_OS   3
#define EXT_INT_CFG1_DEB_5_MSK  ((u32)7<< EXT_INT_CFG1_DEB_5_OS)
#define EXT_INT_CFG1_POL_6_OS   6
#define EXT_INT_CFG1_POL_6_MSK  ((u32)1<< EXT_INT_CFG1_POL_6_OS)
#define EXT_INT_CFG1_MODE_6_OS  7
#define EXT_INT_CFG1_MODE_6_MSK ((u32)3<< EXT_INT_CFG1_MODE_6_OS)
#define EXT_INT_CFG1_DEB_6_OS   9
#define EXT_INT_CFG1_DEB_6_MSK  ((u32)7<< EXT_INT_CFG1_DEB_6_OS)
#define EXT_INT_CFG1_POL_7_OS   12
#define EXT_INT_CFG1_POL_7_MSK  ((u32)1<< EXT_INT_CFG1_POL_7_OS)
#define EXT_INT_CFG1_MODE_7_OS  13
#define EXT_INT_CFG1_MODE_7_MSK ((u32)3<< EXT_INT_CFG1_MODE_7_OS)
#define EXT_INT_CFG1_DEB_7_OS   15
#define EXT_INT_CFG1_DEB_7_MSK  ((u32)7<< EXT_INT_CFG1_DEB_7_OS)
#define EXT_INT_CFG1_POL_8_OS   18
#define EXT_INT_CFG1_POL_8_MSK  ((u32)1<< EXT_INT_CFG1_POL_8_OS)
#define EXT_INT_CFG1_MODE_8_OS  19
#define EXT_INT_CFG1_MODE_8_MSK ((u32)3<< EXT_INT_CFG1_MODE_8_OS)
#define EXT_INT_CFG1_DEB_8_OS   21
#define EXT_INT_CFG1_DEB_8_MSK  ((u32)7<< EXT_INT_CFG1_DEB_8_OS)
#define EXT_INT_CFG1_POL_9_OS   24
#define EXT_INT_CFG1_POL_9_MSK  ((u32)1<< EXT_INT_CFG1_POL_9_OS)
#define EXT_INT_CFG1_MODE_9_OS  25
#define EXT_INT_CFG1_MODE_9_MSK ((u32)3<< EXT_INT_CFG1_MODE_9_OS)
#define EXT_INT_CFG1_DEB_9_OS   27
#define EXT_INT_CFG1_DEB_9_MSK  ((u32)7<< EXT_INT_CFG1_DEB_9_OS)

/*u32_cfg2 register definitions */
#define EXT_INT_CFG2_POL_10_OS  0
#define EXT_INT_CFG2_POL_10_MSK ((u32)1<< EXT_INT_CFG2_POL_10_OS)
#define EXT_INT_CFG2_MODE_10_OS 1
#define EXT_INT_CFG2_MODE_10_MSK    ((u32)3<< EXT_INT_CFG2_MODE_10_OS)
#define EXT_INT_CFG2_DEB_10_OS  3
#define EXT_INT_CFG2_DEB_10_MSK ((u32)7<< EXT_INT_CFG2_DEB_10_OS)
#define EXT_INT_CFG2_POL_11_OS  6
#define EXT_INT_CFG2_POL_11_MSK ((u32)1<< EXT_INT_CFG2_POL_11_OS)
#define EXT_INT_CFG2_MODE_11_OS 7
#define EXT_INT_CFG2_MODE_11_MSK    ((u32)3<< EXT_INT_CFG2_MODE_11_OS)
#define EXT_INT_CFG2_DEB_11_OS  9
#define EXT_INT_CFG2_DEB_11_MSK ((u32)7<< EXT_INT_CFG2_DEB_11_OS)
#define EXT_INT_CFG2_POL_12_OS  12
#define EXT_INT_CFG2_POL_12_MSK ((u32)1<< EXT_INT_CFG2_POL_12_OS)
#define EXT_INT_CFG2_MODE_12_OS 13
#define EXT_INT_CFG2_MODE_12_MSK    ((u32)3<< EXT_INT_CFG2_MODE_12_OS)
#define EXT_INT_CFG2_DEB_12_OS  15
#define EXT_INT_CFG2_DEB_12_MSK ((u32)7<< EXT_INT_CFG2_DEB_12_OS)
#define EXT_INT_CFG2_POL_13_OS  18
#define EXT_INT_CFG2_POL_13_MSK ((u32)1<< EXT_INT_CFG2_POL_13_OS)
#define EXT_INT_CFG2_MODE_13_OS 19
#define EXT_INT_CFG2_MODE_13_MSK    ((u32)3<< EXT_INT_CFG2_MODE_13_OS)
#define EXT_INT_CFG2_DEB_13_OS  21
#define EXT_INT_CFG2_DEB_13_MSK ((u32)7<< EXT_INT_CFG2_DEB_13_OS)
#define EXT_INT_CFG2_POL_14_OS  24
#define EXT_INT_CFG2_POL_14_MSK ((u32)1<< EXT_INT_CFG2_POL_14_OS)
#define EXT_INT_CFG2_MODE_14_OS 25
#define EXT_INT_CFG2_MODE_14_MSK    ((u32)3<< EXT_INT_CFG2_MODE_14_OS)
#define EXT_INT_CFG2_DEB_14_OS  27
#define EXT_INT_CFG2_DEB_14_MSK ((u32)7<< EXT_INT_CFG2_DEB_14_OS)

/*u32_cfg3 register definitions */
#define EXT_INT_CFG3_POL_15_OS  0
#define EXT_INT_CFG3_POL_15_MSK ((u32)1<< EXT_INT_CFG3_POL_15_OS)
#define EXT_INT_CFG3_MODE_15_OS 1
#define EXT_INT_CFG3_MODE_15_MSK    ((u32)3<< EXT_INT_CFG3_MODE_15_OS)
#define EXT_INT_CFG3_DEB_15_OS  3
#define EXT_INT_CFG3_DEB_15_MSK ((u32)7<< EXT_INT_CFG3_DEB_15_OS)

/****************************************************************************/
/*   UART registers and access macros                                       */
/****************************************************************************/
typedef struct W5Uart_s
{
  u32 u32_RecTranBuff;  // 0x00
  u32 u32_LineStatus;   // 0x04
  u32 u32_LineClear;    // 0x08
  u32 u32_ModemStatus;  // 0x0C

  u32 u32_DivisorLatch; // 0x10
  u32 u32_LineControl;  // 0x14
  u32 u32_FifoControl;  // 0x18
  u32 u32_DMA_Control;  // 0x1C

  u32 u32_IIR_Status;   // 0x20
  u32 u32_IIR_Mask;     // 0x24
  u32 u32_IIR_RawStatus;// 0x28
  u32 u32_IIR_Clear;    // 0x2C

  u32 u32_ModemControl;
  u32 u32_Scratch;
  u32 u32_ExtMode;
  u32 u32_ExtStatus;

  u32 u32_ExtClear;
  u32 u32_XON_1;
  u32 u32_XON_2;
  u32 u32_XOFF_1;

  u32 u32_XOFF_2;
  u32 u32_SpeCharRec;
  u32 u32_SpeCharRecMask;
  u32 u32_IrdaCfg;

} W5Uart_t;

/*** RBR register ***/
#define UART_RX_DATA_MSK       (0x00FF<<0)

/*** THR register ***/
#define UART_TX_DATA_MSK       (0x00FF<<0)

/*** IIR Masks register ***/
#define UART_OVERRUN_ERROR_INT_MASK   (0x0001<<0)
#define UART_PARITY_ERROR_INT_MASK    (0x0001<<1)
#define UART_FRAMING_ERROR_INT_MASK   (0x0001<<2)
#define UART_BREAK_DETECTED_INT_MASK  (0x0001<<3)
#define UART_RX_DATA_INT_MASK         (0x0001<<4)
#define UART_RX_CHAR_TIME_OUT_MASK    (0x0001<<5)
#define UART_THRE_SENDING_INT_MASK    (0x0001<<6)//and sending ended
#define UART_TSRE_INT_MASK            (0x0001<<7)//and sending ended
#define UART_MODEM_STATUS_INT_MASK    (0x0001<<8)
#define UART_RX_XOFF_INT_MASK         (0x0001<<9)
#define UART_SPEC_CHAR_INT_MASK       (0x0001<<10)
#define UART_AUTO_BAUD_INT_MASK       (0x0001<<11)
#define UART_AUTO_FRAM_INT_MASK       (0x0001<<12)

/*** IIR register ***/
#define UART_PENDING_INT_MSK   (0x0001<<0)
#define UART_INT_LEVEL_MSK     (0x0003<<1)
#define UART_INT_LEVEL_POS     1
#define UART_TIMEOUT_INT       (0x0001<<3)
#define UART_EXTENDED_FUNC_INT (0x0001<<4)

#define UART_RLS_INT           3
#define UART_RDA_INT           2
#define UART_CTI_INT           6
#define UART_THRE_INT          1
#define UART_TSRE_INT          9
#define UART_MODEM_INT         0
#define UART_EFS_INT           8

/*** FCR register ***/
#define UART_RX_FIFO_ENABLE    (0x0001<<0)
#define UART_RX_FIFO_RESET     (0x0001<<1)
#define UART_RX_FIFO_TRIG_MSK  (0x001F<<3)
#define UART_RX_FIFO_TRIG_POS  3

#define UART_TX_FIFO_ENABLE    (0x0001<<8)
#define UART_TX_FIFO_RESET     (0x0001<<9)

#define UART_TX_FIFO_TRIG_MSK  (0x001f<<11)
#define UART_TX_FIFO_TRIG_POS  11

#define UART_RX_TX_FIFO_ENA    (UART_RX_FIFO_ENABLE | UART_TX_FIFO_ENABLE)

/*** LCR register ***/
#define UART_WORD_LENGTH_MSK   (0x0003<<0)
#define UART_WORD_LENGTH_POS   0
#define UART_NB_STOP_BIT       (0x0001<<2)
#define UART_PARITY_ENA        (0x0001<<3)
#define UART_EVEN_PARITY_ENA   (0x0001<<4)
#define UART_STICK_PARITY_ENA  (0x0001<<5)
#define UART_BREAK_CTRL        (0x0001<<6)
#define UART_DIV_LATCH_ACCESS  (0x0001<<7)

/*** MCR register ***/
#define UART_DTR_ACTIVE        (0x0001<<0)
#define UART_RTS_ACTIVE        (0x0001<<1)
#define UART_LOOP_BACK         (0x0001<<4)
#define UART_AUTO_RTS_CTS      (0x0001<<5)

/*** Line Status register Mask ***/
#define UART_BREAK_DETECTED_MASK    (0x0001<<0)
#define UART_FRAMING_ERROR_MASK     (0x0001<<1)
#define UART_PARITY_ERROR_MASK      (0x0001<<2)
#define UART_OVERRUN_ERROR_MASK     (0x0001<<3)
#define UART_RX_FIFO_ERROR_MASK     (0x0001<<4)
// bits 5:7 reserved
#define UART_DELTA_CTS_MASK         (0x0001<<8)
#define UART_DELTA_DSR_MASK         (0x0001<<9)

/*** MSR register ***/
#define UART_DATA_READY        (0x0001<<0)
#define UART_RX_FIFO_EMP       (0x0001<<1)
#define UART_TX_FIFO_FULL      (0x0001<<2)
#define UART_RX_FIFO_FULL      (0x0001<<3)
#define UART_THR_EMPTY         (0x0001<<4)
#define UART_TRANSMITTER_EMPTY (0x0001<<5)
// bit 6 reserved
#define UART_RX_BUSY           (0x0001<<7)
#define UART_CTS_COMPLEMENT    (0x0001<<8)
#define UART_DSR_COMPLEMENT    (0x0001<<9)

/*** SCR register ***/
#define UART_SCRATCH_MSK       (0x00FF<<0)

/*** DLL register ***/
#define UART_DIV_LATCH_LSB_MSK (0x00FF<<0)

/*** DLM register ***/
#define UART_DIV_LATCH_MSB_MSK (0xFF00<<0)

/*** EFR register ***/
#define UART_AUTOFLOW_CTRL_MSK (0x0003<<0)
#define UART_AUTOFLOW_CTRL_POS 0
#define UART_CHAR_REC_ENA      (0x0001<<2)
#define UART_AUTO_BAUD_ENA     (0x0001<<3)
#define UART_AUTO_FRAM_ENA     (0x0001<<4)
#define UART_EXT_LOOP_BACK_ENA (0x0001<<5)

/*** EFS register ***/
#define UART_XOFF_STATUS_MSK   (0x0003<<0)
#define UART_XOFF_STATUS_POS   0
#define UART_SPEC_CHAR_RECVD   (0x0001<<2)
#define UART_AUTO_BAUD_COMPL   (0x0001<<3)
#define UART_AUTO_FRAM_COMPL   (0x0001<<4)
#define UART_GOOD_FRAMING      (0x0001<<5)

/*** XON1 register ***/
#define UART_XON1_VALUE_MSK    (0x00FF<<0)

/*** XON2 register ***/
#define UART_XON2_VALUE_MSK    (0x00FF<<0)

/*** XOFF1 register ***/
#define UART_XOFF1_VALUE_MSK   (0x00FF<<0)

/*** XOFF2 register ***/
#define UART_XOFF2_VALUE_MSK   (0x00FF<<0)

/*** SRC register ***/
#define UART_CHAR_REC_VALUE_MSK (0x00FF<<0)

/*** XON2 register ***/
#define UART_CHAR_REC_MSK_VALUE_MSK (0x00FF<<0)

/* To activate one of the 28 internal interrupts */
#define ACTIVATE_INT     *(int *)0x80000400

/* To activate one of the 16 external interrupts */
/* But it doesn't activate the EXTINT1-3 of IT CTRL*/
#define ACTIVATE_EXTINT  *(int *)0x80000404


/************************************************/
/* GEA coprocessor registers definition         */
/************************************************/

typedef struct W5Gea_s
{
  u16  au16_Kc[4];
  u16  u16_MsgKey0;
  u16  u16_MsgKey1;
  u16  u16_Ctrl;
  u16  u16_Status;
  u16  u16_S;
} W5Gea_t;

/*** GEA Ctrl register ***/
#define GEA_CTRL_STARTINIT    (0x0001<<0)
#define GEA_CTRL_DIRECTION    (0x0001<<1)

/*** GEA Status register ***/
#define GEA_STAT_STATUS       (0x0001<<0)

/*** GEA S register ***/
#define GEA_S_KEYSTRM_MSK     (0x00FF<<0)

/************************************************/
/* GEA2 coprocessor registers definition        */
/************************************************/

typedef struct W5Gea2_s
{
  u32  u32_Cfg;
  u32  u32_MsgKey;
  u32  au32_SecretKey[2];
  u32  u32_Ctrl;
  u32  u32_MsgOut;
} W5Gea2_t;

/*** GEA Config register  ***/
#define GEA2_CTRL_STARTINIT    (0x0001<<0)
#define GEA2_CTRL_DIRECTION    (0x0001<<1)

/*** GEA Control register ***/
#define GEA2_SW_START          (0x0001<<0)
#define GEA2_UNDER_RUN         (0x0001<<1)
#define GEA2_UNRUN_RESET       (0x0001<<2)
#define GEA2_WORKING_STATUS    (0x0001<<3)

/*** GEA MSG IN/OUT Masks ***/
#define GEA2_MSGIN_MSK         0xFFFF00FF
#define GEA2_MSGOUT_MSK        0xFFFFFF00


/************************************************/
/* FCS coprocessor registers definition         */
/************************************************/

typedef struct W5Fcs_s
{
  u32           u32_Gp;
  u32           u32_Fcs;
  u16           u16_DataByte;
  u16           u16_Init;
} W5Fcs_t;

/*** Init register ***/
#define FCS_DO_NOT_REVERSE_INPUT_DATA  (0x0001<<0)
#define FCS_GP_DEGREE_POS              1
#define FCS_GP_DEGREE_MSK              (0x001F<<1)
#define FCS_VALIDITY                   (0x0001<<6)


/************************************************/
/* DSP INT controler registers definition       */
/************************************************/

typedef struct W5DspIrqControl_s
{
  u16         u16_Nmi;         // 0x0
  u16         u16_Int0;        // 0x2
  u16         u16_Int1;        // 0x4
  u16         u16_Int2;        // 0x6
  u16         u16_VInt;         // 0x8
  u32         u32_VIntHandler;  // 0xa
} W5DspIrqControl_t;

/* Interrupt sources */
#define DSP_IRQCTRL_AUDIO_IN    (0x0001<<0)
#define DSP_IRQCTRL_AUDIO_OUT   (0x0001<<1)
#define DSP_IRQCTRL_SP_COD      (0x0001<<2)
#define DSP_IRQCTRL_SP_DEC      (0x0001<<3)
#define DSP_IRQCTRL_ST_DSP      (0x0001<<4)
#define DSP_IRQCTRL_RX          (0x0001<<5)
#define DSP_IRQCTRL_CPU         (0x0001<<6)
#define DSP_IRQCTRL_USER        (0x0001<<7)
#define DSP_IRQCTRL_E_DETECTO   (0x0001<<8)
#define DSP_IRQCTRL_E_VITERBI   (0x0001<<9)
#define DSP_IRQCTRL_E_PREFILTER (0x0001<<10)
#define DSP_IRQCTRL_DMA         (0x0001<<11)
#define DSP_IRQCTRL_SW          (0x0001<<12)


/************************************************/
/* COUNTERS registers definition                */
/************************************************/

typedef struct W5CntReg_s
{
  u32           u32_Ctrl;
  u32           u32_Fc1Mod;
  u32           u32_Fc2Mod;
  u32           u32_Fc3Mod;
  u32           u32_Fc4Mod;
  u32           u32_Fc1Count;
  u32           u32_Fc2Count;
  u32           u32_Fc3Count;
  u32           u32_Fc4Count;
} W5CntReg_t;

/*** Control register ***/
#define CNT_FC1_EN           (0x0001<<0)
#define CNT_FC2_EN           (0x0001<<1)
#define CNT_FC3_EN           (0x0001<<2)
#define CNT_FC4_EN           (0x0001<<3)
#define CNT_FC2_CLK_SEL      (0x0001<<4)
/*** Mod21 register mask ***/
/*#define CNT_FC21_MOD_FC1_MSK (0x00FF<<0)
#define CNT_FC21_MOD_FC1_POS 0
#define CNT_FC21_MOD_FC2_MSK (0x00FF<<8)
#define CNT_FC21_MOD_FC2_POS 8*/


/************************************************/
/* AUDIO registers definition                   */
/************************************************/
typedef struct W5AudioTimer_s
{
    u32 u32_AudioCtrl;
    u32 u32_Status;
    u32 u32_Clear;
    u32 u32_DtmfLevel;
    u32 u32_DtmfPhase;
    u32 u32_NbSamples;
    u32 u32_DtmfStart;
    u32 u32_PcmG711Ctrl;
    u32 u32_DspTimerCtrl;
    u16 u16_TxFifoDelay;
    u16 u16_RxFifoDelay;
    u16 u16_RxFifoPeriod;
    u16 u16_TxFifoPeriod;
    u16 u16_IntPeriod;
    u16 u16_CodecIntDelay;
    u32 u32_TickDelay;
    u32 u32_SideToneCtrl;
    u32 u32_ApbFifoIn;
    u32 u32_ApbFifoOut;
    u32 u32_FifoIntStatus;
    u32 u32_FifoIntMask;
    u32 u32_FifoIntRawStatus;
    u32 u32_FifoIntClear;
} W5AudioTimer_t;

/*** Ctrl register ***/
#define AUDIO_TIMER_MUX_MSK             (0x000F<<0)
#define AUDIO_TIMER_MUX_DSP_AB          (0x0000<<0)
#define AUDIO_TIMER_MUX_DSP_I2S         (0x0001<<0)
#define AUDIO_TIMER_MUX_DSP_G711        (0x0002<<0)
#define AUDIO_TIMER_MUX_DSP_DAI         (0x0003<<0)
#define AUDIO_TIMER_MUX_AB_G711         (0x0004<<0)
#define AUDIO_TIMER_MUX_AB_DAI          (0x0005<<0)
#define AUDIO_TIMER_MUX_LOOP_DAI        (0x0006<<0)
#define AUDIO_TIMER_MUX_LOOP_G711       (0x0007<<0)
#define AUDIO_TIMER_MUX_CPU_I2S         (0x0008<<0)

#define AUDIO_TIMER_1WAY_CPU_I2S        (0x0001<<4)

#define AUDIO_TIMER_DAI_MODE_SEL       5
#define AUDIO_TIMER_DAI_MODE_MSK       (0x0003<<5)
#define AUDIO_TIMER_DAI_MODE_NORM      (0x0000<<5)
#define AUDIO_TIMER_DAI_MODE_DWL       (0x0001<<5)
#define AUDIO_TIMER_DAI_MODE_UPL       (0x0002<<5)
#define AUDIO_TIMER_DAI_MODE_CODEC     (0x0003<<5)

#define AUDIO_TIMER_DAI_RESET_UNSYNC   (0x0001<<7)
#define AUDIO_TIMER_PCM_CLK_ASYNC      (0x0001<<8)
#define AUDIO_TIMER_DAI_SOFT_RESET     (0x0001<<9)
#define AUDIO_TIMER_EXT_MUX_SEL        10
#define AUDIO_TIMER_EXT_MUX_MSK        (0x0003<<10)
#define AUDIO_TIMER_EXT_MUX_DAI        (0x0000<<10)
#define AUDIO_TIMER_EXT_MUX_G711       (0x0001<<10)
#define AUDIO_TIMER_EXT_MUX_I2S        (0x0002<<10)

#define AUDIO_TIMER_DSP_MONO_SPL       (0x0001<<12)
#define AUDIO_TIMER_OUTPUT_SEL         13
#define AUDIO_TIMER_OUTPUT_MSK         (0x0003<<13)
#define AUDIO_TIMER_OUTPUT_LEFT        (0x0000<<13)
#define AUDIO_TIMER_OUTPUT_RIGHT       (0x0001<<13)
#define AUDIO_TIMER_OUTPUT_ALTERN      (0x0002<<13)

#define AUDIO_TIMER_INPUT_1WRD         (0x0001<<15)

#define AUDIO_TIMER_DSPTIMER_STOP      (0x0001<<16)

#define AUDIO_TIMER_CPU_LISTEN         (0x0001<<17)

#define AUDIO_TIMER_I2S_SEL            26
#define AUDIO_TIMER_I2S_MSK            (0x0003<<26)
#define AUDIO_TIMER_I2S_2_SLAVE        (0x0000<<26)
#define AUDIO_TIMER_I2S_ESLAVE_SMASTER (0x0001<<26)
#define AUDIO_TIMER_I2S_EMASTER_SSLAVE (0x0002<<26)

#define AUDIO_TIMER_MUX_B2             (0x0001<<18) // SDI_E/SDO_E is SDO_E pin
#define AUDIO_TIMER_MUX_B1             (0x0001<<19) // SDO_E/SDI_E is SDO_E pin
#define AUDIO_TIMER_MUX_M2             (0x0001<<20) // select input (2) = loopthrough mode
#define AUDIO_TIMER_MUX_M1             (0x0001<<21) //
#define AUDIO_TIMER_MUX_B4             (0x0001<<22) // SDI/SDO pin is SDO
#define AUDIO_TIMER_MUX_B3             (0x0001<<23) // SDO/SDI pin is SDO
#define AUDIO_TIMER_MUX_M4             (0x0001<<24) // select input (2) = loopthrough mode
#define AUDIO_TIMER_MUX_M3             (0x0001<<25) // select input (2) according to Figure 10

// *** Status & Clear *****
#define AUDIO_TIMER_STATUS_DAI_RUNNING (0x0001<<0)
#define AUDIO_TIMER_STATUS_DAI_ACK     (0x0001<<0)
// *** DTMF amplitude
#define AUDIO_TIMER_DTMF  0
#define AUDIO_TIMER_DTMF_START        (1<<0)

//*** PCM CTRL register ***/
#define AUDIO_TIMER_PCM_INV_MODE_ACTIVE               (0x1 << 0)
#define AUDIO_TIMER_PCM_COMPANDIG_MODE_MUTE    (0x0 << 1)
#define AUDIO_TIMER_PCM_COMPANDIG_MODE_ALAW    (0x1 << 1)
#define AUDIO_TIMER_PCM_COMPANDIG_MODE_ULAW    (0x2 << 1)
#define AUDIO_TIMER_PCM_COMPANDIG_MODE_LIN_16  (0x3 << 1)
#define AUDIO_TIMER_PCM_COMPANDIG_MODE_LIN_LB  (0x4 << 1)
#define AUDIO_TIMER_PCM_COMPANDIG_MODE_LIN_UB  (0x5 << 1)
#define AUDIO_TIMER_PCM_SWAP_MODE_MSB_FIRST      (0x0 << 4)
#define AUDIO_TIMER_PCM_STAR_VALUE_MSK                 (0xFF << 5)
#define AUDIO_TIMER_PCM_STAR_VALUE_POS                 5
#define AUDIO_TIMER_PCM_STOP_VALUE_MSK                 (0xFF << 13)
#define AUDIO_TIMER_PCM_STOP_VALUE_POS                 13
#define AUDIO_TIMER_PCM_MASTER                                 (0x0 << 21)
#define AUDIO_TIMER_PCM_SLAVE                                    (0x1 << 21)
#define AUDIO_TIMER_PCM_SYNC_MODE_8K                     (0x0 << 22)
#define AUDIO_TIMER_PCM_SYNC_MODE_16K                   (0x1 << 22)
#define AUDIO_TIMER_PCM_CLK_SEL_128K                       (0x0 << 23)
#define AUDIO_TIMER_PCM_CLK_SEL_256K                       (0x1 << 23)
#define AUDIO_TIMER_PCM_CLK_SEL_512K                       (0x2 << 23)
#define AUDIO_TIMER_PCM_CLK_SEL_1536K                     (0x3 << 23)
#define AUDIO_TIMER_PCM_CLK_SEL_2048K                     (0x4 << 23)
#define AUDIO_TIMER_PCM_SYNC_SORT                            (0x0 << 26)
#define AUDIO_TIMER_PCM_SYNC_LONG                            (0x1 << 26)

//***  DSP Timer registyers
#define AUDIO_TIMER_RESYNC              (0x0001<<0)
#define AUDIO_TIMER_CODEC_INT_AUTO_MODE (0x0001<<1)
#define AUDIO_TIMER_CODEC_SWAPPING      (0x0001<<2)
#define AUDIO_TIMER_TIMER_TICK_MASK     (0x0001<<3)
#define AUDIO_TIMER_TIMER_TICK_EVT      (0x0001<<4)

//*** PCM TX delay register ***
#define AUDIO_TIMER_PCM_TX_DELAY_MSK    (0x007F<<0)

//*** PCM RX delay register ***
#define AUDIO_TIMER_PCM_RX_DELAY_MSK    (0x007F<<0)

//*** Codex int delay register ***
#define AUDIO_TIMER_CODEC_INT_DELAY_MSK (0x007F<<0)

//*** Int period register ***
#define AUDIO_TIMER_INT_PERIOD_MSK      (0x007F<<0)

//*** Tick delay register ***
#define AUDIO_TIMER_TICK_DELAY_MSK      (0x007F<<0)

//*** SideTone register ***
#define AUDIO_TIMER_SIDETONE_ON         (0x0001<<0)
#define AUDIO_TIMER_SIDETONE_MONO       (0x0001<<1)
#define AUDIO_TIMER_SIDETONE_RIGHTMIC   (0x0001<<2)
#define AUDIO_TIMER_SIDETONE_SHIFT_SEL  4
#define AUDIO_TIMER_SIDETONE_SHIFT_MSK  (0x0007<<4)

//*** Fifo interrupt status register ***

#define AUDIO_TIMER_BURSTWI             ( 1 << 3) // Burst Write Interrupt if output fifo <= 1/2 empty
#define AUDIO_TIMER_SINGLEWI            ( 1 << 2) // Single Write Interrupt if output fifo != full
#define AUDIO_TIMER_BURSTRI             ( 1 << 1) // Burst Read Interrupt if input fifo >= 1/2 full
#define AUDIO_TIMER_SINGLERI                ( 1 << 0) // Single Read Interrupt if input fifo != empty

//*** Fifo interrupt mask register ***
#define AUDIO_TIMER_BURSTWM             ( 1 << 3) // mask burst write interrupt
#define AUDIO_TIMER_SINGLEWM                ( 1 << 2) // mask single write interrupt
#define AUDIO_TIMER_BURSTRM                 ( 1 << 1) // mask burst read interrupt
#define AUDIO_TIMER_SINGLERM                ( 1 << 0) // mask single read interrupt

//*** Fifo interrupt clear register ***
#define AUDIO_TIMER_BURSTWC             ( 1 << 3) // writing 1 clear the burst write interrupt
#define AUDIO_TIMER_SINGLEWC                ( 1 << 2) // writing 1 clear the single write interrupt
#define AUDIO_TIMER_BURSTRC                 ( 1 << 1) // writing 1 clear the burst read interrupt
#define AUDIO_TIMER_SINGLERC                ( 1 << 0) // writing 1 clear the single read interrupt

#define AUDIO_TIMER_FIFO_IN_SIZE                16 // 16 words of 32 bits
#define AUDIO_TIMER_FIFO_OUT_SIZE       16 // 16 words of 32 bits

/************************************************/
/* DSMA registers definition                    */
/************************************************/

typedef struct W5Dsma_s
{
  u32           u32_Base;           // 0x00
  u32           u32_CpuControl;     // 0x04
  u32           u32_Spare;          // 0x08
  u32           u32_RawIntStatus;   // 0x0C
  u32           u32_IntMask;        // 0x10
  u32           u32_IntStatus;      // 0x14
  u32           u32_IntClear;       // 0x18
} W5Dsma_t;

/*** Control/status register ***/
#define DSMA_TRANSFER_EN       (0x0001 << 0)
#define DSMA_ACCESS_WRITE      (0x0001 << 1)
#define DSMA_ACCESS_READ       (0x0000 << 1)
#define DSMA_MODE_ON_FLY       (0x0000 << 2)
#define DSMA_MODE_FULL_EMPTY   (0x0001 << 2)
#define DSMA_MODE_THRESHOLD    (0x0002 << 2)

#define DSMA_COMPLETED         (0x0001 << 0)
#define DSMA_ABORT             (0x0001 << 1)
#define DSMA_AHBERROR          (0x0001 << 2)

/************************************************/
/* FIR registers definition                     */
/************************************************/

typedef struct W5Fir_s
{
  u16           au16_Tap0Coeff[21]; // 0xB400E000 - 0xB400E028
  u16           au16_Dummy0[11];    // 0xB400E02A
  u16           au16_Tap1Coeff[21]; // 0xB400E040 - 0xB400E068
  u16           au16_Dummy1[11];    // 0xB400E06A
  u32           u16_Status;         // 0xB400E080
} W5Fir_t;

//Status Register
#define FIR_BYPASS                    (0x0001<<0)
#define FIR_TAP_SELECT_POS            1
#define FIR_TAP1_SELECT               (0x0001<<1)
#define FIR_DEC_FACT_POS              2
#define FIR_DEC_FACT_MSK              (0x0003<<2)
#define FIR_FIR_LENGTH_POS            4
#define FIR_FIR_LENGTH_MSK            (0x001F<<4)
#define FIR_OUT_LSB_ID_POS            9
#define FIR_OUT_LSB_ID_MSK            (0x003F<<9)
#define FIR_OUT_DELAY_POS             15
#define FIR_OUT_DELAY_MSK             (0x003F<<15)

/************************************************/
/* SYS TIMER registers definition               */
/************************************************/

typedef struct W5SysTimer_s
{
  u32	u32_SoftTimerCfg;     // 0x0
  u32           u32_OsTickConfig;     // 0x4
  u32           u32_OsTickCounter;    // 0x8
  u32           u32_WatchDog0Control; // 0xC
  u32           u32_WatchDog1Control; // 0x10
  u32           u32_TimeOutControl0;  // 0x16
  u32           u32_TimeOutControl1;  // 0x1A
  u32           u32_TimeOutControl2;  // 0x1F
  u32           u32_TimeOutControl3;  // 0x22
  u32           u32_SoftAck;          // 0x24
  u32           u32_RawIntStatus;     // 0x28
  u32           u32_IntMask;          // 0x2C
  u32           u32_IntStatus;        // 0x30
  u32           u32_IntClear;         // 0x34
  u32           u32_Unused[2];        // 0x38
  u32           u32_StdaConfig;       // 0x40
  u32           u32_StdaCounter;      // 0x44
  u32           u32_TimerSpare;       // 0x48
} W5SysTimer_t;

// SOFTTIMERCONTROL register
#define SYSTIMER_SOFTTIMER_ENA    (0x0001<<28)
#define SYSTIMER_SOFTTIMER_COUNTER_OFF    0
#define SYSTIMER_SOFTTIMER_COUNTER_MSK    ((u32)0x7FF<<SYSTIMER_SOFTTIMER_COUNTER_OFF)
#define SYSTIMER_SOFTTIMER_LENGTH_OFF    16
#define SYSTIMER_SOFTTIMER_LENGTH_MSK    ((u32)0x7FF<<SYSTIMER_SOFTTIMER_LENGTH_OFF)
//OSTICKCONFIG register
#define SYSTIMER_OSTICKLENGTH_MSK (0xFFFFFF<<0)
#define SYSTIMER_OSTICK_ENA       (0x0001<<28)
#define SYSTIMER_OSTICK_RESET     0
//OSTICKCONFIG Counter
#define SYSTIMER_OSTICKCOUNT_MSK (0xFFFFFF<<0)
//WatchDogControl register
#define SYSTIMER_WDOGCTRL_LEN_POS 0
#define SYSTIMER_WDOGCTRL_LEN_4_7s 0x400
#define SYSTIMER_WDOGCTRL_LEN_MSK (0x07FF<<SYSTIMER_WDOGCTRL_LEN_POS)
#define SYSTIMER_WDOGCTRL_ENA     (0x0001<<12)
//WatchDogAck register
#define SYSTIMER_WDOG_ACK         (0x0001<<16)
#define SYSTIMER_WDOG_TIMEOUT     (0x0001<<20)
// Raw Mask register
#define SYSTIMER_TIMOUT0_RAW_MASK (0x0001<<0)
#define SYSTIMER_TIMOUT1_RAW_MASK (0x0001<<1)
#define SYSTIMER_TIMOUT2_RAW_MASK (0x0001<<2)
#define SYSTIMER_TIMOUT3_RAW_MASK (0x0001<<3)
#define SYSTIMER_SOFTTIM_RAW_MASK (0x0001<<4)
#define SYSTIMER_OSTICK_RAW_MASK  (0x0001<<5)
// Int Mask register
#define SYSTIMER_TIMOUT0_MASK     (0x0001<<0)
#define SYSTIMER_TIMOUT1_MASK     (0x0001<<1)
#define SYSTIMER_TIMOUT2_MASK     (0x0001<<2)
#define SYSTIMER_TIMOUT3_MASK     (0x0001<<3)
#define SYSTIMER_SOFTTIM_MASK     (0x0001<<4)
#define SYSTIMER_OSTICK_MASK      (0x0001<<5)
// Int clear register
#define SYSTIMER_TIMOUT0_ACK      (0x0001<<0)
#define SYSTIMER_TIMOUT1_ACK      (0x0001<<1)
#define SYSTIMER_TIMOUT2_ACK      (0x0001<<2)
#define SYSTIMER_TIMOUT3_ACK      (0x0001<<3)
#define SYSTIMER_SOFTTIM_ACK      (0x0001<<4)
#define SYSTIMER_OSTICK_ACK       (0x0001<<5)


/************************************************/
/* TBU registers definition                     */
/************************************************/


enum
{
  TBU_EVT_SET_TBUO0 = 0,  // SET signal for TBUOx
  TBU_EVT_SET_TBUO1,
  TBU_EVT_SET_TBUO2,
  TBU_EVT_SET_TBUO3,
  TBU_EVT_SET_TBUO4,
  TBU_EVT_SET_TBUO5,
  TBU_EVT_SET_TBUO6,
  TBU_EVT_SET_TBUO7,

  TBU_EVT_CLR_TBUO0,      // RESET signal for TBUOx
  TBU_EVT_CLR_TBUO1,
  TBU_EVT_CLR_TBUO2,
  TBU_EVT_CLR_TBUO3,
  TBU_EVT_CLR_TBUO4,
  TBU_EVT_CLR_TBUO5,
  TBU_EVT_CLR_TBUO6,
  TBU_EVT_CLR_TBUO7,

  TBU_EVT_INV_TBUO0,      // INV signal for TBUOx
  TBU_EVT_INV_TBUO1,
  TBU_EVT_INV_TBUO2,
  TBU_EVT_INV_TBUO3,
  TBU_EVT_INV_TBUO4,
  TBU_EVT_INV_TBUO5,
  TBU_EVT_INV_TBUO6,
  TBU_EVT_INV_TBUO7,

  TBU_EVT_START_RXDATAWIN,  // RX Data Window
  TBU_EVT_STOP_RXDATAWIN,

  TBU_EVT_START_TXDATAWIN,  // TX Data Window
  TBU_EVT_STOP_TXDATAWIN,

  TBU_EVT_START_RXAGCWIN,   // AGC Window
  TBU_EVT_STOP_RXAGCWIN,

  TBU_EVT_SOCAL_PULSE,      // DC offset pulse

  TBU_EVT_RFDWL_PULSE,      // Pulse to send words to the RF transceiver
  TBU_EVT_RFUPL_PULSE,

  TBU_EVT_TXPR_PULSE,       // Pulse to send words to the RF transceiver, for power ramping pattenr

  TBU_EVT_SINT0,            // Synchronous interrupts, no acknowledge, lasts 1 QB
  TBU_EVT_SINT1,
  TBU_EVT_SINT2,
  TBU_EVT_SINT3,

  TBU_EVT_SINTA,            // Synchronous interrupt, acknowledge needed

  TBU_EVT_DONOTHING=63
};

#define TBU_EVT_IMM_ORDER_0 0
#define TBU_EVT_IMM_ORDER_1 8
#define TBU_EVT_IMM_ORDER_2 16
#define TBU_EVT_IMM_ORDER_3 24

#define TBU_EVT_CLEAR 0xFFFFFFFF

typedef struct
{
  u16 u16_Date;
  u8  u8_Code1;
  u8  u8_Code2;
} DEvt_t;

typedef struct
{
  u16 u16_Date;
  u8  u8_Code1;
  u8  u8_Pad0;
} SEvt_t;


typedef struct W5TbuEvt_s
{
  DEvt_t        DualEvt[8];     // 8  double events
  SEvt_t        SingleEvt[56];  // 56 single events
  u32           u32_ImmEvt;     // 1
  u32           u32_EvtEn[2];
  u32           u32_DtxSens[2];
} W5TbuEvt_t;

#define TBU_NOW 0x0FFAA



/************************************************/
/* TBU controler registers definitions          */
/************************************************/

typedef struct W5TbuC_s
{
  u32           u32_Control;          //0x114
  u16           u16_FrameLength;      //0x118
  u16           u16_Pad6;
  u16           u16_QbCnt;            //0x11C
  u16           u16_QbCntSave;        //0x11E
  u16           u16_SpeechCodPos;     //0x120
  u16           u16_ChannelCodPos;    //0x122
  u16           u16_Qb1Value;         //0x124
  u16           u16_Pad0;
  u32           u32_SleepTimeDuration;//0x128
  u32           u32_SleepTimeCounter; //0x12C
  u16           u16_SleepTimeCounterVWIO;  //0x130
  u16           u16_Pad3;
  u32           u32_SleepTimeCal;        //0x134
  u32           u32_LockTime;       //0x138
  u8            u8_TbuoState;       //0x13C
  u8            u8_TbuoMask;        //0x13D
  u8            u8_TbuoPulseType;   //0x13E
  u8            u8_Pad0;
  u32           u32_RawIntStatus;   //0x140
  u32           u32_IntCtrl;        //0x144
  u32           u32_IntStatus;      //0x148
  u32           u32_IntClear;       //0x14C
} W5TbuC_t;

// Control register
#define TBU_SS_CODEC_INT_ENA  (0x0001<<0)
#define TBU_CH_CODEC_INT_ENA  (0x0001<<1)
#define TBU_SOFTLATCH         (0x0001<<2)
#define TBU_CALI_ON           (0x0001<<3)
#define TBU_CALI_STATUS       (0x0001<<4)
#define TBU_WKUP_ASYNC        (0x0001<<5)
#define TBU_WKUP_STATUS       (0x0001<<6)
#define TBU_SM32K_FSM         (0x0007<<7)
#define TBU_SMD_REQ           (0x0001<<10)
#define TBU_SM32K_REQ         (0x0001<<11)
#define TBU_SM32K_STAT        (0x0001<<12)
#define TBU_QB_FRAC           (0x000F<<13)
#define TBU_QB_FRAC_READY     (0x0001<<17)
#define TBU_QB_SAVE_VALID     (0x0001<<18)
#define TBU_QB_SAVE_CLR       (0x0001<<19)
#define TBU_AWAKE_MODE       (0x0001<<20)
#define TBU_QB_FRAC_WR_POS       21
#define TBU_QB_FRAC_WR_MASK       (0x000F<<TBU_QB_FRAC_WR_POS)
#define TBU_SM32_RD       (0x0001<<25)
#define TBU_SM32_RD_CLEAR       (0x0001<<26)

#define TBU_DOUBLE_EVENT_NB 8
#define TBU_NBBIT_ENFIELD 32

// LOCKTIME register
#define TBU_PLL_LOCK_TIME     (0x000F<<0)
#define TBU_OSC_LOCK_TIME     (0x000F<<8)
#define TBU_SQR_LOCK_TIME     (0x000F<<16)
#define TBU_PLL_LOCK_TIME_POS 0
#define TBU_OSC_LOCK_TIME_POS 8
#define TBU_SQR_LOCK_TIME_POS 16
#define TBU_OSC_EN_DELAY_POS 24

// TBUO register
#define TBU_TBUO_STATUS       (0x000F<<0)
#define TBU_TBUO_MASK         (0x000F<<8)
#define TBU_TBUO_TYPE         (0x000F<<16)

// TBU raw Int Status register
#define TBU_FINT_RAW          (0x0001<<0)
#define TBU_SINTA_RAW         (0x0001<<1)

// TBU Int Control register
#define TBU_FINT_ENA          (0x0001<<0)
#define TBU_SINTA_ENA         (0x0001<<1)
#define CPU_WAKE_UP_INT_ENA (0x0001<<2)

// TBU Int Status register
#define TBU_FINT_ACTIV        (0x0001<<0)
#define TBU_SINTA_ACTIV       (0x0001<<1)
#define CPU_WAKE_UP_INT_ACTIV (0x0001<<2)

// TBU Int Clear register
#define TBU_FINT_ACK          (0x0001<<0)
#define TBU_SINTA_ACK         (0x0001<<1)
#define CPU_WAKE_UP_INT_ACK (0x0001<<2)

// TBU Codec Time Position
#define TBU_CH_CODEC_POS 325

/************************************************/
/* RfDwl registers definitions                  */
/************************************************/


typedef struct
{
  u16           u16_Prefix;
  u16           u16_Suffix;
} Amble_t;


typedef struct W5RfDwl_s
{
  u32           u32_PS2RamCtrl;
  u8            u8_PS2Control;
  u8            u8_ImmOrdPtr;
  u8            u8_ImmOrdSizeDest;
  u8            u8_Pad0;
  u16           u16_PtrBufDescr;
  u16           u16_Pad1;
  u16           u16_PtrAgcLut;
  u16           u16_Pad2;
  u16           u16_InitValAdd;
  u16           u16_Pad3;
  u16           u16_ReadValAdd;
  u16           u16_Pad4;
  u16           u16_PtrTxPwr;
  u16           u16_Pad5;
  u16           u16_PtrRxWin;
  u16           u16_Pad6;
  u32           u32_P2S0Cfg;
  u32           u32_P2S1Cfg;
  u32           u32_P2S0Sr;
  u32           u32_P2S1Sr;
  u32           u32_RfDwlIrqMask;
  u32           u32_RfDwlIrqStatus;
  u32           u32_RfDwlIrqClear;
  u32       u32_RfDwlIrqRawStatus;
  u16           u16_ColisionErrorCode;
  u16           u16_Pad7;
  u16           u16_GainControl;
  u16           u16_Pad8;
#ifdef __G1__
  Amble_t       Amble[3];
#else
  Amble_t    Amble[5];
  u32           u32_Arbiter_Cfg;
  u32           u32_Pad9;
  u32           u32_P2S0Cfg_2;
  u32           u32_P2S1Cfg_2;
#endif
} W5RfDwl_t;

//RAMcontrol register
#define RFDWL_RAM_WS		  (0x0001<<1)

//P2SControl register
#define RFDWL_SWSTART             (0x0001<<0)
#define RFDWL_IMM_UNRUN           (0x0001<<1)
#define RFDWL_IMM_CLEAR           (0x0001<<2)
#define RFDWL_IMM_DONE            (0x0001<<3)
#define RFDWL_P2S1_RNW            (0x0001<<4) // 1 = WRITE, 0 = READ
#define RFDWL_P2S0_WS             (0x0001<<5)
#define RFDWL_P2S1_WS             (0x0001<<6)
#define RFDWL_P2S1_MERGE          (0x0001<<7)
#define RFDWL_IMM_P2S_DST          (0x0001<<7) //1 = PS1, 0 = PS0


//P2SConfig register
#define RFDWL_CLKPOLARITY         (0x0001<<0)
#define RFDWL_CLKPHASE            (0x0001<<1)
#define RFDWL_WAITGUARDTIME_ENA   (0x0003<<2)
#define RFDWL_INTWORD             (0x0003<<4)
#define RFDWL_PULSE_TYPE_STROBE   (0x0001<<6)
#define RFDWL_PULSE_TYPE_POL      (0x0001<<7)
#define RFDWL_PULSE_BAUD_RATE     (0x0001<<8)
#define RFDWL_RDCLK_INV           (0x0001<<9)
#define RFDWL_WORD_LEN_POS        10
#define RFDWL_WORD_LEN_MSK        (0x001F<<RFDWL_WORD_LEN_POS)
#define RFDWL_4WIRE_BUS_MODE      (0x0001<<15)
#define RFDWL_READLEN_POS         16
#define RFDWL_READLEN_MSK         (0x003F<<RFDWL_READLEN_POS)
#define RFDWL_IVALLEN_POS         24
#define RFDWL_IVALLEN_MSK         (0x001F<<RFDWL_IVALLEN_POS)
#define RFDWL_COUNT_ENA           (0x0001<<29)
#define RFDWL_START_CLK           (0x0001<<30)
#define RFDWL_DATA_PULL_DOWN      ((u32)0x0001<<31)

//GainControl configuration register
#define RFDWL_P2S_SEL             (0x0001<<0)
#define RFDWL_PRELEN_POS          1
#define RFDWL_PRELEN_MSK          (0x001F<<RFDWL_PRELEN_POS)
#define RFDWL_ROOTLEN_POS         6
#define RFDWL_ROOTLEN_MSK         (0x001F<<RFDWL_ROOTLEN_POS)
#define RFDWL_POSTLEN_POS         11
#define RFDWL_POSTLEN_MSK         (0x001F<<RFDWL_POSTLEN_POS)
// SIF config register


/************************************************/
/* Automatic Gain Control                       */
/************************************************/
typedef struct
{
  u8            u8_Threshold;
  u8            u8_Start;
  u8            u8_Step;
  u8            u8_IndexResult;
} AgcCtrl_t;

typedef struct W5Agc_s
{
  u32           u32_Config;
#ifdef __G1__
  AgcCtrl_t     aControl[3];
#else
  AgcCtrl_t     aControl[5];
#endif
} W5Agc_t;

/* Config*/
#define AGC_DICHO_STEP_POS         0
#define AGC_DICHO_MOD             (0x0001<<AGC_DICHO_STEP_POS)
#define AGC_STEP_MOD                (0x0000<<AGC_DICHO_STEP_POS)
#define AGC_DECR_INC_POS             1
#define AGC_DECR_MODE             (0x0001<<AGC_DECR_INC_POS)
#define AGC_INC_MODE              (0x0000<<AGC_DECR_INC_POS)
#define AGC_NB_IQ_SKIP_POS        2
#define AGC_BYTE_SELECT_POS     10
#define AGC_0_7_BYTE              (0x0000 << AGC_BYTE_SELECT_POS)
#define AGC_8_15_BYTE            (0x0001 << AGC_BYTE_SELECT_POS)


/* Use to configure RFDWL Gain configuration Register*/
#define AGC_P2S_SEL_POS	        0
#define AGC_P2S_SEL_MSK	        0x0001
#define AGC_PRELEN_POS		1
#define AGC_PRELEN_MSK		0x003E
#define AGC_ROOTLEN_POS	        6
#define AGC_ROOTLEN_MSK	        0x07C0
#define AGC_POSTLEN_POS	        11
#define AGC_POSTLEN_MSK	        0xF800


/************************************************/
/* RX/TX Port                                   */
/************************************************/
typedef struct W5DigiRf_s
{
   u32 u32_TxPortCtrl;
   u32 u32_RxPortCtrl;
} W5DigiRf_t;

// Digi Rf Rx Control
#define DIGIRF_RXCTRL_MODE_POS                  0
#define DIGIRF_RXCTRL_MODE_MSK                  (0x0003)
#define DIGIRF_RXCTRL_MODE_13MHZ_1X_12BIT_24    (0x0000<<DIGIRF_RXCTRL_MODE_POS)
#define DIGIRF_RXCTRL_MODE_13MHZ_1X_16BIT_16    (0x0001<<DIGIRF_RXCTRL_MODE_POS)
#define DIGIRF_RXCTRL_MODE_13MHZ_2X_12BIT_0     (0x0002<<DIGIRF_RXCTRL_MODE_POS)
#define DIGIRF_RXCTRL_MODE_26MHZ_1X_12BIT_72    (0x0003<<DIGIRF_RXCTRL_MODE_POS)
#define DIGIRF_RXCTRL_MODE_26MHZ_1X_16BIT_64    (0x0004<<DIGIRF_RXCTRL_MODE_POS)
#define DIGIRF_RXCTRL_MODE_26MHZ_2X_12BIT_24    (0x0005<<DIGIRF_RXCTRL_MODE_POS)
#define DIGIRF_RXCTRL_MODE_26MHZ_2X_16BIT_16    (0x0006<<DIGIRF_RXCTRL_MODE_POS)
#define DIGIRF_RXCTRL_MODE_26MHZ_4X_12BIT_0     (0x0007<<DIGIRF_RXCTRL_MODE_POS)
#define DIGIRF_RXCTRL_BITREV                    (0x0001<<3)
#define DIGIRF_RXCTRL_ENTYPE_PULSE              (0x0001<<4)
#define DIGIRF_RXCTRL_CLK_INV                   (0x0001<<5)
#define DIGIRF_RXCTRL_CLK_SEL                   (0x0001<<6)
#define DIGIRF_RXCTRL_RXTXEN_PDDIS              (0x0001<<7)
#define DIGIRF_RXCTRL_RXTXDATA_PDDIS            (0x0001<<8)

// Digi Rf Tx Control
#define DIGIRF_TXCTRL_MODE_POS                  0
#define DIGIRF_TXCTRL_MODE_MSK                  (0x0003)
#define DIGIRF_TXCTRL_MODE_ENIN_CLKIN           (0<<DIGIRF_TXCTRL_MODE_POS)
#define DIGIRF_TXCTRL_MODE_ENOUT_CLKIN          (1<<DIGIRF_TXCTRL_MODE_POS)
#define DIGIRF_TXCTRL_MODE_ENOUT_CLKOUT         (2<<DIGIRF_TXCTRL_MODE_POS)
#define DIGIRF_TXCTRL_RATE_POS                  2
#define DIGIRF_TXCTRL_RATE_MSK                  (0x0003<<DIGIRF_TXCTRL_RATE_POS)
#define DIGIRF_TXCTRL_RATE_1                    (0<<DIGIRF_TXCTRL_RATE_POS)
#define DIGIRF_TXCTRL_RATE_24                   (1<<DIGIRF_TXCTRL_RATE_POS)
#define DIGIRF_TXCTRL_RATE_32                   (2<<DIGIRF_TXCTRL_RATE_POS)
#define DIGIRF_TXCTRL_RATE_96                   (3<<DIGIRF_TXCTRL_RATE_POS)
#define DIGIRF_TXCTRL_EXTRACT_POS               4
#define DIGIRF_TXCTRL_EXTRACT_MSK               (0x0003<<DIGIRF_TXCTRL_EXTRACT_POS)
#define DIGIRF_TXCTRL_EXTRACT_1                 (0<<DIGIRF_TXCTRL_EXTRACT_POS)
#define DIGIRF_TXCTRL_EXTRACT_24                (1<<DIGIRF_TXCTRL_EXTRACT_POS)
#define DIGIRF_TXCTRL_EXTRACT_32                (2<<DIGIRF_TXCTRL_EXTRACT_POS)
#define DIGIRF_TXCTRL_EXTRACT_96                (3<<DIGIRF_TXCTRL_EXTRACT_POS)
#define DIGIRF_TXCTRL_CLK_INV                   (0x0001<<6)
#define DIGIRF_TXCTRL_CLK_DIV                   (0x0001<<7)
#define DIGIRF_TXCTRL_RXTXEN_SEL                (0x0001<<8)
#define DIGIRF_TXCTRL_CLK_POS                   9
#define DIGIRF_TXCTRL_CLK_MSK                   (0x0003<<DIGIRF_TXCTRL_CLK_POS)
#define DIGIRF_TXCTRL_CLK_MAIN                  (0<<DIGIRF_TXCTRL_CLK_POS)
#define DIGIRF_TXCTRL_CLK_EXT_TXPORT            (1<<DIGIRF_TXCTRL_CLK_POS)
#define DIGIRF_TXCTRL_CLK_EXT_IQCLK             (2<<DIGIRF_TXCTRL_CLK_POS)

/************************************************/
/* Rf RAM                                       */
/************************************************/
// u16_DspJob
#define RXWIN_SWAP_IQ_BIT_POS            0
#define RXWIN_SWAP_IQ                    (0x0001<<0)
#define RXWIN_JOB_MSK                    (0x0007<<1)
#define RXWIN_POWER_MEASUREMENT_WIN     (0x0000<<1)
#define RXWIN_FB_DETECTION                           (0x0001<<1)
#define RXWIN_SB_RX_PROCESSING                   (0x0002<<1)
#define RXWIN_NB_RX_PROCESSING                   (0x0003<<1)
#define RXWIN_ENB_RX_PROCESSING                 (0x0004<<1)
#define RXWIN_EN_DC_OFFSET_PROCESSING    (0x0001<<4)
#define RXWIN_RX_TRAINING_SEQ_POS        5
#define RXWIN_RX_TRAINING_MSK            (0x0007<<5)

//FirConf Register
#define RXWIN_FIR_BYPASS                (0x0001<<0)
#define RXWIN_TAP1_SELECT               (0x0001<<1)
#define RXWIN_DEC_FACT_POS              2
#define RXWIN_DEC_FACT_MSK              (0x0003<<2)
#define RXWIN_FIR_LENGTH_POS            4
#define RXWIN_FIR_LENGTH_MSK            (0x001F<<4)
#define RXWIN_OUT_LSB_ID_POS            9
#define RXWIN_OUT_LSB_ID_MSK            (0x003F<<9)

#define RFRAM_RXWIN_NB          3                       // 3 Rx Win managed max
#define RFRAM_TXPWRRAMP_NBSTEP  16                      // 16 step Tx Pwr Ramps

// Size of each RFRAM struct
#define RFRAM_LUT_SIZE          (4*5)            // 3 Rx Win x 5 Gain steps (15)
#define RFRAM_PLLINITDWLSTR_SIZE 113 //nombre de mot max a l'init avec les rampes
#define RFRAM_PLLDWLSTR_SIZE 24 //GPRS : 2Rx 4 Tx = 22 mots + marge de 2 mots
#define RFRAM_PADINITDWLSTR_SIZE (RFRAM_PLLINITDWLSTR_SIZE - (RFRAM_PLLDWLSTR_SIZE*2))

#define RFRAM_RFMSG_NBMAX 22 /* Max nbr event for download in Renesas */

// Structure definition
// ****************
typedef struct
{
  u8  u8_Offs;
  u8  u8_Size;
} RfMsgDes_t;

#define RFLD_SIZE_MSK 0x7F

#if 0
// Structure TXPWR Ramp
typedef struct
{
  u8  u8_DataFormat;
  u8  u8_NbLevel;
  u16 u16_RfAdd;
  u16 au16_Level[RFRAM_PWRRAMP_SIZE];  // 1 header + 80 power levels (5 ramps of 16 levels)
} PwrRamp_t;
#endif

// Structure RxWinMode
typedef struct
{
  u16   u16_DspJob;
  u16   u16_FirConf;   //  FIR_BYPASS, TAP_SELECT, DEC_FACT, FIR_LENGTH and OUT_LSB_ID fields
} RxWinMod_t;

//WARNING : RfDevice_t Must be aligned with 32bits
typedef struct
{
  u32                  au32_PllDwlStr_01[RFRAM_PLLDWLSTR_SIZE]; //one for each frame in order to anticipate download
  u32                  au32_PllDwlStr_02[RFRAM_PLLDWLSTR_SIZE];
  u32                  au32_padinit[RFRAM_PADINITDWLSTR_SIZE];
  //PwrRamp_t       TxPwrRamp;
  u32  TxPwrRamp;
  u16                  au16_AgcLUT[RFRAM_LUT_SIZE];
  RxWinMod_t      RxWinMod[RFRAM_RXWIN_NB];
} RfDevice_t;


// The size of this dedicated memory is 256 * 32 bits = 1KB
typedef struct W5RfRam_s
{
    RfMsgDes_t  pRfMsgDesTable[RFRAM_RFMSG_NBMAX];
    RfDevice_t  Device;
} W5RfRam_t;

/************************************************/
/* I2C interface registers definition           */
/************************************************/

typedef struct W5I2c_s
{
  u16 u16_Con;
  u16 Pad0;
  u16 u16_Tar;
  u16 Pad1;
  u16 u16_Sar;
  u16 Pad2;
  u16 u16_HsMaddr;
  u16 Pad3;
  u16 u16_DataCmd;
  u16 Pad4;
  u16 u16_SsSclHcnt;
  u16 Pad5;
  u16 u16_SsSclLcnt;
  u16 Pad6;
  u16 u16_FsSclHcnt;
  u16 Pad7;
  u16 u16_FsSclLcnt;
  u16 Pad8;
  u16 u16_HsSclHcnt;
  u16 Pad9;
  u16 u16_HsSclLcnt;
  u16 Pad10;
  u16 u16_RawIntrStat;
  u16 Pad11;
  u16 u16_IntrMask;
  u16 Pad12;
  u16 u16_IntrStat;
  u16 Pad13;
  u16 u16_RxTl;
  u16 Pad14;
  u16 u16_TxTl;
  u16 Pad15;
  u16 u16_ClrIntr;
  u16 Pad16;
  u16 u16_ClrRxUnder;
  u16 Pad17;
  u16 u16_ClrRxOver;
  u16 Pad18;
  u16 u16_ClrTxOver;
  u16 Pad19;
  u16 u16_ClrRdReq;
  u16 Pad20;
  u16 u16_ClrTxAbrt;
  u16 Pad21;
  u16 u16_ClrRxDone;
  u16 Pad22;
  u16 u16_ClrActivity;
  u16 Pad23;
  u16 u16_ClrStopDet;
  u16 Pad24;
  u16 u16_ClrStartDet;
  u16 Pad25;
  u16 u16_ClrGenAll;
  u16 Pad26;
  u16 u16_Enable;
  u16 Pad27;
  u16 u16_Status;
  u16 Pad28;
  u32 u32_Txflr;
  u32 u32_Rxflr;
  u16 u16_Sreset;
  u16 Pad29;
  u16 u16_TxAbrtSource;
  u16 Pad30;
} W5I2c_t;

/**** CON register ****/
#define I2C_SLAVE_DISABLE              (1<<6)
#define I2C_RESTART_EN                 (1<<5)
#define I2C_10BITADDR_MASTER           (1<<4)
#define I2C_10BITADDR_SLAVE            (1<<3)
#define I2C_SPEED_STD                  (1<<1)
#define I2C_SPEED_FAST                 (2<<1)
#define I2C_SPEED_HIGH                 (3<<1)
#define I2C_MASTER_ENABLE              (1<<0)

/**** TAR register ****/
#define I2C_SPECIAL                    (1<<11)
#define I2C_START                      (1<<10)
#define I2C_TAR_MSK                    0x003F

/**** SAR register ****/
#define I2C_SAR_MSK                    0x003F

/**** HS MADDR register ****/
#define I2C_HS_MAR_MSK                 0x0007

/**** DATA CMD register ****/
#define I2C_CMD_READ                   (1<<8)
#define I2C_CMD_WRITE                  (0<<8)
#define I2C_DATA_MSK                   0x00FF

/**** SS SCL HCNT register ****/
#define I2C_SS_SCL_HCNT_MSK            0xFFFF

/**** SS SCL LCNT register ****/
#define I2C_SS_SCL_LCNT_MSK            0xFFFF

/**** FS SCL HCNT register ****/
#define I2C_FS_SCL_HCNT_MSK            0xFFFF

/**** FS SCL LCNT register ****/
#define I2C_FS_SCL_LCNT_MSK            0xFFFF

/**** HS SCL HCNT register ****/
#define I2C_HS_SCL_HCNT_MSK            0xFFFF

/**** HS SCL LCNT register ****/
#define I2C_HS_SCL_LCNT_MSK            0xFFFF

/**** RAW INTR STAT register ****/
/**** INTR MASK register     ****/
/**** INTR STAT register     ****/
#define I2C_IT_GEN_CALL_POS            (1<<11)
#define I2C_IT_START_DET_POS           (1<<10)
#define I2C_IT_STOP_DET_POS            (1<<9)
#define I2C_IT_ACTIVITY_POS            (1<<8)
#define I2C_IT_RX_DONE_POS             (1<<7)
#define I2C_IT_TX_ABRT_POS             (1<<6)
#define I2C_IT_RD_REQ_POS              (1<<5)
#define I2C_IT_TX_EMPTY_POS            (1<<4)
#define I2C_IT_TX_OVER_POS             (1<<3)
#define I2C_IT_RX_FULL_POS             (1<<2)
#define I2C_IT_RX_OVER_POS             (1<<1)
#define I2C_IT_RX_UNDER_POS            (1<<0)

/**** RX TL register ****/
#define I2C_RX_TL_MSK                  0x00FF

/**** TX TL register ****/
#define I2C_TX_TL_MSK                  0x00FF

/**** CLR INTR register ****/
#define I2C_CLR_INTR_POS               (1<<0)

/**** CLR RX UNDER register ****/
#define I2C_CLR_RX_UNDER_POS           (1<<0)

/**** CLR RX OVER register ****/
#define I2C_CLR_RX_OVER_POS            (1<<0)

/**** CLR TX OVER register ****/
#define I2C_CLR_TX_OVER_POS            (1<<0)

/**** CLR RD REQ  register ****/
#define I2C_CLR_RD_REQ_POS             (1<<0)

/**** CLR TX ABRT register ****/
#define I2C_CLR_TX_ABRT_POS            (1<<0)

/**** CLR RX DONE register ****/
#define I2C_CLR_RX_DONE_POS            (1<<0)

/**** CLR ACTIVITY register ****/
#define I2C_CLR_ACTIVITY_POS           (1<<0)

/**** CLR STOP DET register ****/
#define I2C_CLR_STOP_DET_POS           (1<<0)

/**** CLR START DET register ****/
#define I2C_CLR_START_DET_POS          (1<<0)

/**** CLR GEN CALL register ****/
#define I2C_CLR_GEN_CALL_POS           (1<<0)

/**** ENABLE register ****/
#define I2C_ENABLE                     (1<<0)

/**** STATUS register ****/
#define I2C_RFF_POS                    (1<<4)
#define I2C_RFNE_POS                   (1<<3)
#define I2C_TFE_POS                    (1<<2)
#define I2C_TFNF_POS                   (1<<1)
#define I2C_ACTIVITY_POS               (1<<0)

/**** SRESET register ****/
#define I2C_SLAVE_SRST                 (1<<2)
#define I2C_MASTER_SRST                (1<<1)
#define I2C_SRST                       (1<<0)

/**** TX ABRT SOURCE register ****/
#define I2C_ABRT_SLVRD_INTX_POS        (1<<15)
#define I2C_ABRT_SLV_ARBLOST_POS       (1<<14)
#define I2C_ABRT_SLVFLUSH_TXFIFO_POS   (1<<13)
#define I2C_ARB_LOST_POS               (1<<12)
#define I2C_ARB_MASTER_DIS_POS         (1<<11)
#define I2C_ABRT_10B_RD_NORSTRT_POS    (1<<10)
#define I2C_ABRT_SBYTE_NORSTRT_POS     (1<<9)
#define I2C_ABRT_HS_NORSTRT_POS        (1<<8)
#define I2C_ABRT_SBYTE_ACKDET_POS      (1<<7)
#define I2C_ABRT_HS_ACKDET_POS         (1<<6)
#define I2C_ABRT_GCALL_READ_POS        (1<<5)
#define I2C_ABRT_GCALL_NOACK_POS       (1<<4)
#define I2C_ABRT_TXDATA_NOACK_POS      (1<<3)
#define I2C_ABRT_10ADDR2_NOACK_POS     (1<<2)
#define I2C_ABRT_10ADDR1_NOACK_POS     (1<<1)
#define I2C_ABRT_7B_ADDR_NOACK_POS     (1<<0)

/************************************************/
/* GPIO registers definition                    */
/************************************************/
#ifdef __B1__
typedef struct KeGpio_s
{
	u32 u32_Mux6;
	u32 u32_Mux5;
	u32 u32_Mux4;
	u32 u32_Mux3;
	u32 u32_Mux2;
	u32 u32_Mux1;
	u32 u32_Mux0;
   	u32 u32_PullEn1;
   	u32 u32_PullEn0;
   	u32 u32_DataIn1;
   	u32 u32_DataIn0;
	u32 u32_Drive2;
	u32 u32_Drive1;
	u32 u32_Drive0;
   	u32 u32_DataOut1;
   	u32 u32_DataOut0;
  	u32 u32_Dir1;
  	u32 u32_Dir0;
} KeGpio_t;

/*** Data0 registers ***/
#define GPIO_DATA0_GPIO0_MSK                          ((u32)1<<0)
#define GPIO_DATA0_GPIO0_POS                          0
#define GPIO_DATA0_GPIO1_MSK                          ((u32)1<<1)
#define GPIO_DATA0_GPIO1_POS                          1
#define GPIO_DATA0_GPIO2_MSK                          ((u32)1<<2)
#define GPIO_DATA0_GPIO2_POS                          2
#define GPIO_DATA0_GPIO3_MSK                          ((u32)1<<3)
#define GPIO_DATA0_GPIO3_POS                          3
#define GPIO_DATA0_GPIO4_MSK                          ((u32)1<<4)
#define GPIO_DATA0_GPIO4_POS                          4
#define GPIO_DATA0_GPIO5_MSK                          ((u32)1<<5)
#define GPIO_DATA0_GPIO5_POS                          5
#define GPIO_DATA0_GPIO6_MSK                          ((u32)1<<6)
#define GPIO_DATA0_GPIO6_POS                          6
#define GPIO_DATA0_GPIO7_MSK                          ((u32)1<<7)
#define GPIO_DATA0_GPIO7_POS                          7
#define GPIO_DATA0_GPIO8_MSK                          ((u32)1<<8)
#define GPIO_DATA0_GPIO8_POS                          8
#define GPIO_DATA0_GPIO9_MSK                          ((u32)1<<9)
#define GPIO_DATA0_GPIO9_POS                          9
#define GPIO_DATA0_GPIO10_MSK                         ((u32)1<<10)
#define GPIO_DATA0_GPIO10_POS                         10
#define GPIO_DATA0_GPIO11_MSK                         ((u32)1<<11)
#define GPIO_DATA0_GPIO11_POS                         11
#define GPIO_DATA0_GPIO12_MSK                         ((u32)1<<12)
#define GPIO_DATA0_GPIO12_POS                         12
#define GPIO_DATA0_GPIO13_MSK                         ((u32)1<<13)
#define GPIO_DATA0_GPIO13_POS                         13
#define GPIO_DATA0_GPIO14_MSK                         ((u32)1<<14)
#define GPIO_DATA0_GPIO14_POS                         14
#define GPIO_DATA0_GPIO15_MSK                         ((u32)1<<15)
#define GPIO_DATA0_GPIO15_POS                         15
#define GPIO_DATA0_GPIO16_MSK                         ((u32)1<<16)
#define GPIO_DATA0_GPIO16_POS                         16
#define GPIO_DATA0_GPIO17_MSK                         ((u32)1<<17)
#define GPIO_DATA0_GPIO17_POS                         17
#define GPIO_DATA0_GPIO18_MSK                         ((u32)1<<18)
#define GPIO_DATA0_GPIO18_POS                         18
#define GPIO_DATA0_GPIO19_MSK                         ((u32)1<<19)
#define GPIO_DATA0_GPIO19_POS                         19
#define GPIO_DATA0_GPIO20_MSK                         ((u32)1<<20)
#define GPIO_DATA0_GPIO20_POS                         20
#define GPIO_DATA0_GPIO21_MSK                         ((u32)1<<21)
#define GPIO_DATA0_GPIO21_POS                         21
#define GPIO_DATA0_GPIO22_MSK                         ((u32)1<<22)
#define GPIO_DATA0_GPIO22_POS                         22
#define GPIO_DATA0_GPIO23_MSK                         ((u32)1<<23)
#define GPIO_DATA0_GPIO23_POS                         23
#define GPIO_DATA0_GPIO24_MSK                         ((u32)1<<24)
#define GPIO_DATA0_GPIO24_POS                         24
#define GPIO_DATA0_GPIO25_MSK                         ((u32)1<<25)
#define GPIO_DATA0_GPIO25_POS                         25
#define GPIO_DATA0_GPIO26_MSK                         ((u32)1<<26)
#define GPIO_DATA0_GPIO26_POS                         26
#define GPIO_DATA0_GPIO27_MSK                         ((u32)1<<27)
#define GPIO_DATA0_GPIO27_POS                         27
#define GPIO_DATA0_GPIO28_MSK                         ((u32)1<<28)
#define GPIO_DATA0_GPIO28_POS                         28
#define GPIO_DATA0_GPIO29_MSK                         ((u32)1<<29)
#define GPIO_DATA0_GPIO29_POS                         29
#define GPIO_DATA0_GPIO30_MSK                         ((u32)1<<30)
#define GPIO_DATA0_GPIO30_POS                         30
#define GPIO_DATA0_GPIO31_MSK                         ((u32)1<<31)
#define GPIO_DATA0_GPIO31_POS                         31

/*** DataH registers ***/
#define GPIO_DATA1_GPIO32_MSK                         ((u32)1<<0)
#define GPIO_DATA1_GPIO32_POS                         0
#define GPIO_DATA1_GPIO33_MSK                         ((u32)1<<1)
#define GPIO_DATA1_GPIO33_POS                         1
#define GPIO_DATA1_GPIO34_MSK                         ((u32)1<<2)
#define GPIO_DATA1_GPIO34_POS                         2
#define GPIO_DATA1_GPIO35_MSK                         ((u32)1<<3)
#define GPIO_DATA1_GPIO35_POS                         3
#define GPIO_DATA1_GPIO36_MSK                         ((u32)1<<4)
#define GPIO_DATA1_GPIO36_POS                         4
#define GPIO_DATA1_GPIO37_MSK                         ((u32)1<<5)
#define GPIO_DATA1_GPIO37_POS                         5

/*** Dir0 registers ***/
#define GPIO_DIR0_GPIO0_OUTPUT                        ((u32)0<<0)
#define GPIO_DIR0_GPIO0_INPUT                         ((u32)1<<0)
#define GPIO_DIR0_GPIO1_OUTPUT                        ((u32)0<<1)
#define GPIO_DIR0_GPIO1_INPUT                         ((u32)1<<1)
#define GPIO_DIR0_GPIO2_OUTPUT                        ((u32)0<<2)
#define GPIO_DIR0_GPIO2_INPUT                         ((u32)1<<2)
#define GPIO_DIR0_GPIO3_OUTPUT                        ((u32)0<<3)
#define GPIO_DIR0_GPIO3_INPUT                         ((u32)1<<3)
#define GPIO_DIR0_GPIO4_OUTPUT                        ((u32)0<<4)
#define GPIO_DIR0_GPIO4_INPUT                         ((u32)1<<4)
#define GPIO_DIR0_GPIO5_OUTPUT                        ((u32)0<<5)
#define GPIO_DIR0_GPIO5_INPUT                         ((u32)1<<5)
#define GPIO_DIR0_GPIO6_OUTPUT                        ((u32)0<<6)
#define GPIO_DIR0_GPIO6_INPUT                         ((u32)1<<6)
#define GPIO_DIR0_GPIO7_OUTPUT                        ((u32)0<<7)
#define GPIO_DIR0_GPIO7_INPUT                         ((u32)1<<7)
#define GPIO_DIR0_GPIO8_OUTPUT                        ((u32)0<<8)
#define GPIO_DIR0_GPIO8_INPUT                         ((u32)1<<8)
#define GPIO_DIR0_GPIO9_OUTPUT                        ((u32)0<<9)
#define GPIO_DIR0_GPIO9_INPUT                         ((u32)1<<9)
#define GPIO_DIR0_GPIO10_OUTPUT                       ((u32)0<<10)
#define GPIO_DIR0_GPIO10_INPUT                        ((u32)1<<10)
#define GPIO_DIR0_GPIO11_OUTPUT                       ((u32)0<<11)
#define GPIO_DIR0_GPIO11_INPUT                        ((u32)1<<11)
#define GPIO_DIR0_GPIO12_OUTPUT                       ((u32)0<<12)
#define GPIO_DIR0_GPIO12_INPUT                        ((u32)1<<12)
#define GPIO_DIR0_GPIO13_OUTPUT                       ((u32)0<<13)
#define GPIO_DIR0_GPIO13_INPUT                        ((u32)1<<13)
#define GPIO_DIR0_GPIO14_OUTPUT                       ((u32)0<<14)
#define GPIO_DIR0_GPIO14_INPUT                        ((u32)1<<14)
#define GPIO_DIR0_GPIO15_OUTPUT                       ((u32)0<<15)
#define GPIO_DIR0_GPIO15_INPUT                        ((u32)1<<15)
#define GPIO_DIR0_GPIO16_OUTPUT                       ((u32)0<<16)
#define GPIO_DIR0_GPIO16_INPUT                        ((u32)1<<16)
#define GPIO_DIR0_GPIO17_OUTPUT                       ((u32)0<<17)
#define GPIO_DIR0_GPIO17_INPUT                        ((u32)1<<17)
#define GPIO_DIR0_GPIO18_OUTPUT                       ((u32)0<<18)
#define GPIO_DIR0_GPIO18_INPUT                        ((u32)1<<18)
#define GPIO_DIR0_GPIO19_OUTPUT                       ((u32)0<<19)
#define GPIO_DIR0_GPIO19_INPUT                        ((u32)1<<19)
#define GPIO_DIR0_GPIO20_OUTPUT                       ((u32)0<<20)
#define GPIO_DIR0_GPIO20_INPUT                        ((u32)1<<20)
#define GPIO_DIR0_GPIO21_OUTPUT                       ((u32)0<<21)
#define GPIO_DIR0_GPIO21_INPUT                        ((u32)1<<21)
#define GPIO_DIR0_GPIO22_OUTPUT                       ((u32)0<<22)
#define GPIO_DIR0_GPIO22_INPUT                        ((u32)1<<22)
#define GPIO_DIR0_GPIO23_OUTPUT                       ((u32)0<<23)
#define GPIO_DIR0_GPIO23_INPUT                        ((u32)1<<23)
#define GPIO_DIR0_GPIO24_OUTPUT                       ((u32)0<<24)
#define GPIO_DIR0_GPIO24_INPUT                        ((u32)1<<24)
#define GPIO_DIR0_GPIO25_OUTPUT                       ((u32)0<<25)
#define GPIO_DIR0_GPIO25_INPUT                        ((u32)1<<25)
#define GPIO_DIR0_GPIO26_OUTPUT                       ((u32)0<<26)
#define GPIO_DIR0_GPIO26_INPUT                        ((u32)1<<26)
#define GPIO_DIR0_GPIO27_OUTPUT                       ((u32)0<<27)
#define GPIO_DIR0_GPIO27_INPUT                        ((u32)1<<27)
#define GPIO_DIR0_GPIO28_OUTPUT                       ((u32)0<<28)
#define GPIO_DIR0_GPIO28_INPUT                        ((u32)1<<28)
#define GPIO_DIR0_GPIO29_OUTPUT                       ((u32)0<<29)
#define GPIO_DIR0_GPIO29_INPUT                        ((u32)1<<29)
#define GPIO_DIR0_GPIO30_OUTPUT                       ((u32)0<<30)
#define GPIO_DIR0_GPIO30_INPUT                        ((u32)1<<30)
#define GPIO_DIR0_GPIO31_OUTPUT                       ((u32)0<<31)
#define GPIO_DIR0_GPIO31_INPUT                        ((u32)1<<31)

/*** Dir1 registers ***/
#define GPIO_DIR1_GPIO32_OUTPUT                       ((u32)0<<0)
#define GPIO_DIR1_GPIO32_INPUT                        ((u32)1<<0)
#define GPIO_DIR1_GPIO33_OUTPUT                       ((u32)0<<1)
#define GPIO_DIR1_GPIO33_INPUT                        ((u32)1<<1)
#define GPIO_DIR1_GPIO34_OUTPUT                       ((u32)0<<2)
#define GPIO_DIR1_GPIO34_INPUT                        ((u32)1<<2)
#define GPIO_DIR1_GPIO35_OUTPUT                       ((u32)0<<3)
#define GPIO_DIR1_GPIO35_INPUT                        ((u32)1<<3)
#define GPIO_DIR1_GPIO36_OUTPUT                       ((u32)0<<4)
#define GPIO_DIR1_GPIO36_INPUT                        ((u32)1<<4)
#define GPIO_DIR1_GPIO37_OUTPUT                       ((u32)0<<5)
#define GPIO_DIR1_GPIO37_INPUT                        ((u32)1<<5)

/*** Mux 0 register ***/
typedef struct MUX_0 {
    u32 ADD_25      : 1 ; // 0       ADD_25             SDRAM_CKE
    u32             : 2 ;
    u32 ADD_24      : 1 ; // 3       ADD_24             SDRAM_RAS
    u32             : 2 ;
    u32 ADD_23      : 1 ; // 6       ADD_23             SDRAM_WE
    u32             : 2 ;
    u32 ADD_22      : 1 ; // 9       ADD_22             SDRAM_BA1
    u32             : 2 ;
    u32 ADD_21      : 1 ; // 12      ADD_21             SDRAM_BA0
    u32             : 2 ;
    u32 ADD_20      : 1 ; // 15      ADD_20             SDRAM_LDQM
    u32             : 2 ;
    u32 ADD_19      : 1 ; // 18      ADD_19             SDRAM_CAS
    u32             : 2 ;
    u32 CS_MEM0     : 1 ; // 21      CS_MEM0            CS_SDRAM0
    u32             : 2 ;
    u32 CS_MEM1     : 1 ; // 24      CS_MEM1            CS_SDRAM1
    u32             : 2 ;
    u32 ADVN        : 1 ; // 27      ADVN               SDRAM_UDQM
    u32             : 4 ;
} KePadMux0_t;

#define GPIO_MUX_ADD_25_POS       0 //------------------------------- ADD_25
#define GPIO_MUX_ADD_25_MSK       ((u32)1<<GPIO_MUX_ADD_25_POS)
#define GPIO_MUX_ADD_25_ADD_25    0
#define GPIO_MUX_ADD_25_SDRAM_CKE 1
#define GPIO_MUX_ADD_24_POS       3 //------------------------------- ADD_24
#define GPIO_MUX_ADD_24_MSK       ((u32)1<<GPIO_MUX_ADD_24_POS)
#define GPIO_MUX_ADD_24_ADD_24    0
#define GPIO_MUX_ADD_24_SDRAM_RAS 1
#define GPIO_MUX_ADD_23_POS      6 //-------------------------------- ADD_23
#define GPIO_MUX_ADD_23_MSK      ((u32)1<<GPIO_MUX_ADD_23_POS)
#define GPIO_MUX_ADD_23_ADD_23   0
#define GPIO_MUX_ADD_23_SDRAM_WE 1
#define GPIO_MUX_ADD_22_POS       9 //------------------------------- ADD_22
#define GPIO_MUX_ADD_22_MSK       ((u32)1<<GPIO_MUX_ADD_22_POS)
#define GPIO_MUX_ADD_22_ADD_22    0
#define GPIO_MUX_ADD_22_SDRAM_BA1 1
#define GPIO_MUX_ADD_21_POS       12 //------------------------------ ADD_21
#define GPIO_MUX_ADD_21_MSK       ((u32)1<<GPIO_MUX_ADD_21_POS)
#define GPIO_MUX_ADD_21_ADD_21    0
#define GPIO_MUX_ADD_21_SDRAM_BA0 1
#define GPIO_MUX_ADD_20_POS        15 //----------------------------- ADD_20
#define GPIO_MUX_ADD_20_MSK        ((u32)1<<GPIO_MUX_ADD_20_POS)
#define GPIO_MUX_ADD_20_ADD_20     0
#define GPIO_MUX_ADD_20_SDRAM_LDQM 1
#define GPIO_MUX_ADD_19_POS       18 //------------------------------ ADD_19
#define GPIO_MUX_ADD_19_MSK       ((u32)1<<GPIO_MUX_ADD_19_POS)
#define GPIO_MUX_ADD_19_ADD_19    0
#define GPIO_MUX_ADD_19_SDRAM_CAS 1
#define GPIO_MUX_CS_MEM0_POS       21 //---------------------------- CS_MEM0
#define GPIO_MUX_CS_MEM0_MSK       ((u32)1<<GPIO_MUX_CS_MEM0_POS)
#define GPIO_MUX_CS_MEM0_CS_MEM0   0
#define GPIO_MUX_CS_MEM0_CS_SDRAM0 1
#define GPIO_MUX_CS_MEM1_POS       24 //---------------------------- CS_MEM1
#define GPIO_MUX_CS_MEM1_MSK       ((u32)1<<GPIO_MUX_CS_MEM1_POS)
#define GPIO_MUX_CS_MEM1_CS_MEM1   0
#define GPIO_MUX_CS_MEM1_CS_SDRAM1 1
#define GPIO_MUX_ADVN_POS        27 //--------------------------------- ADVN
#define GPIO_MUX_ADVN_MSK        ((u32)1<<GPIO_MUX_ADVN_POS)
#define GPIO_MUX_ADVN_ADVN       0
#define GPIO_MUX_ADVN_SDRAM_UDQM 1

/*** Mux 1 register ***/
typedef struct MUX_1 {
    u32             : 1 ;
    u32 EBI_A_0     : 2 ; // 2:1     EBI_A_0            DBG_EBI_20         EBI_A_0_PAD_IS_OFF
    u32             : 1 ;
    u32 EBI_D_15_12 : 2 ; // 5:4     EBI_D              DAI                DBG                OFF
                          //         ebi_d_15           dai_pcmin          dbg_ebi_15         ebi_d_15_pad_is_off
                          //         ebi_d_14           dai_pcmout         dbg_ebi_14         ebi_d_14_pad_is_off
                          //         ebi_d_13           dai_pcmclk         dbg_ebi_13         ebi_d_13_pad_is_off
                          //         ebi_d_12           dai_pcmrst         dbg_ebi_12         ebi_d_12_pad_is_off
    u32             : 1 ;
    u32 EBI_D_7_2   : 2 ; // 8:7     EBI_D              DBG                OFF
                          //         ebi_d_7            dbg_ebi_7          ebi_d_7_pad_is_off
                          //         ebi_d_6            dbg_ebi_6          ebi_d_6_pad_is_off
                          //         ebi_d_5            dbg_ebi_5          ebi_d_5_pad_is_off
                          //         ebi_d_4            dbg_ebi_4          ebi_d_4_pad_is_off
                          //         ebi_d_3            dbg_ebi_3          ebi_d_3_pad_is_off
                          //         ebi_d_2            dbg_ebi_2          ebi_d_2_pad_is_off
    u32             : 1 ;
    u32 EBI_D_1_0   : 2 ; // 11:10   EBI_D              SPI2               DBG                OFF
                          //         ebi_d_1            spi2_sdio          dbg_ebi_1          ebi_d_1_pad_is_off
                          //         ebi_d_0            spi2_sdo           dbg_ebi_0          ebi_d_0_pad_is_off
    u32             : 1 ;
    u32 EBI_CTRL    : 2 ; // 14:13   EBI_D              SPI2               DBG                OFF
                          //         ebi_rdn            spi2_sclk          dbg_ebi_19         ebi_rdn_pad_is_off
                          //         ebi_cs1            spi2_ssl1          dbg_ebi_17         ebi_cs1_pad_is_off
                          //         ebi_cs0            spi2_ssl0          dbg_ebi_16         ebi_cs0_pad_is_off
    u32 KEYPAD      : 2 ; // 16:15   KEYPAD             ETM                DBG
                          //         row_0              pipestat0          dbg_keypad_0
                          //         row_1              pipestat1          dbg_keypad_1
                          //         row_2              pipestat2          dbg_keypad_2
                          //         row_3              tracesync          dbg_keypad_3
                          //         row_4              trace_pkt_0        dbg_keypad_4
                          //         row_5              trace_pkt_1        dbg_keypad_5
                          //         col_0              trace_pkt_2        dbg_keypad_6
                          //         col_1              trace_pkt_3        dbg_keypad_7
                          //         col_2              trace_pkt_4        dbg_keypad_8
                          //         col_3              trace_pkt_5        dbg_keypad_9
                          //         col_4              trace_pkt_6        dbg_keypad_10
                          //         col_5              trace_pkt_7        dbg_keypad_11
    u32             : 1 ;
    u32 OSC_EN0     : 1 ; // 18      OSC_EN0            GPIO_0
    u32             : 2 ;
    u32 OSC_EN1     : 1 ; // 21      OSC_EN1            GPIO_0
    u32             : 2 ;
    u32 SPI_RF_IN   : 1 ; // 24      SPI_RF_IN          EXT_TXPORT_CLK
    u32             : 1 ;
    u32 TBUO1       : 1 ; // 26      TBUO1              GPIO_1
    u32             : 1 ;
    u32 TBUO6       : 1 ; // 28      TBUO6              GPIO_2
    u32             : 3 ;
} KePadMux1_t;

#define GPIO_MUX_EBI_A_0_POS                1 //-------------------- EBI_A_0
#define GPIO_MUX_EBI_A_0_MSK                ((u32)3<<GPIO_MUX_EBI_A_0_POS)
#define GPIO_MUX_EBI_A_0_EBI_A_0            0
#define GPIO_MUX_EBI_A_0_DBG_EBI_20         1
#define GPIO_MUX_EBI_A_0_EBI_A_0_PAD_IS_OFF 2
#define GPIO_MUX_EBI_D_15_12_POS   4 //------------------------- EBI_D_15_12
#define GPIO_MUX_EBI_D_15_12_MSK   ((u32)3<<GPIO_MUX_EBI_D_15_12_POS)
#define GPIO_MUX_EBI_D_15_12_EBI_D 0
#define GPIO_MUX_EBI_D_15_12_DAI   1
#define GPIO_MUX_EBI_D_15_12_DBG   2
#define GPIO_MUX_EBI_D_15_12_OFF   3
#define GPIO_MUX_EBI_D_7_2_POS   7 //----------------------------- EBI_D_7_2
#define GPIO_MUX_EBI_D_7_2_MSK   ((u32)3<<GPIO_MUX_EBI_D_7_2_POS)
#define GPIO_MUX_EBI_D_7_2_EBI_D 0
#define GPIO_MUX_EBI_D_7_2_DBG   1
#define GPIO_MUX_EBI_D_7_2_OFF   2
#define GPIO_MUX_EBI_D_1_0_POS   10 //---------------------------- EBI_D_1_0
#define GPIO_MUX_EBI_D_1_0_MSK   ((u32)3<<GPIO_MUX_EBI_D_1_0_POS)
#define GPIO_MUX_EBI_D_1_0_EBI_D 0
#define GPIO_MUX_EBI_D_1_0_SPI2  1
#define GPIO_MUX_EBI_D_1_0_DBG   2
#define GPIO_MUX_EBI_D_1_0_OFF   3
#define GPIO_MUX_EBI_CTRL_POS   13 //------------------------------ EBI_CTRL
#define GPIO_MUX_EBI_CTRL_MSK   ((u32)3<<GPIO_MUX_EBI_CTRL_POS)
#define GPIO_MUX_EBI_CTRL_EBI_D 0
#define GPIO_MUX_EBI_CTRL_SPI2  1
#define GPIO_MUX_EBI_CTRL_DBG   2
#define GPIO_MUX_EBI_CTRL_OFF   3
#define GPIO_MUX_KEYPAD_POS    15 //--------------------------------- KEYPAD
#define GPIO_MUX_KEYPAD_MSK    ((u32)3<<GPIO_MUX_KEYPAD_POS)
#define GPIO_MUX_KEYPAD_KEYPAD 0
#define GPIO_MUX_KEYPAD_ETM    1
#define GPIO_MUX_KEYPAD_DBG    2
#define GPIO_MUX_OSC_EN0_POS     18 //------------------------------ OSC_EN0
#define GPIO_MUX_OSC_EN0_MSK     ((u32)1<<GPIO_MUX_OSC_EN0_POS)
#define GPIO_MUX_OSC_EN0_OSC_EN0 0
#define GPIO_MUX_OSC_EN0_GPIO_0  1
#define GPIO_MUX_OSC_EN1_POS     21 //------------------------------ OSC_EN1
#define GPIO_MUX_OSC_EN1_MSK     ((u32)1<<GPIO_MUX_OSC_EN1_POS)
#define GPIO_MUX_OSC_EN1_OSC_EN1 0
#define GPIO_MUX_OSC_EN1_GPIO_0  1
#define GPIO_MUX_SPI_RF_IN_POS            24 //------------------- SPI_RF_IN
#define GPIO_MUX_SPI_RF_IN_MSK            ((u32)1<<GPIO_MUX_SPI_RF_IN_POS)
#define GPIO_MUX_SPI_RF_IN_SPI_RF_IN      0
#define GPIO_MUX_SPI_RF_IN_EXT_TXPORT_CLK 1
#define GPIO_MUX_TBUO1_POS    26 //----------------------------------- TBUO1
#define GPIO_MUX_TBUO1_MSK    ((u32)1<<GPIO_MUX_TBUO1_POS)
#define GPIO_MUX_TBUO1_TBUO1  0
#define GPIO_MUX_TBUO1_GPIO_1 1
#define GPIO_MUX_TBUO6_POS    28 //----------------------------------- TBUO6
#define GPIO_MUX_TBUO6_MSK    ((u32)1<<GPIO_MUX_TBUO6_POS)
#define GPIO_MUX_TBUO6_TBUO6  0
#define GPIO_MUX_TBUO6_GPIO_2 1

/*** Mux 2 register ***/
typedef struct MUX_2 {
    u32             : 2 ;
    u32 PCMG711     : 2 ; // 3:2     PCM                I2S                DAI                FDI
                          //         fdi_g711           i2s_sdi_e          dai_pcmin          fdi_g711_pad_is_off
                          //         fdo_g711           i2s_sdo_e          dai_pcmout         fdo_g711_pad_is_off
                          //         fbck_g711          i2s_sck_e          dai_pcmclk         fbck_g711_pad_is_off
                          //         fsy_g711           i2s_ws_e           dai_pcmrst         fsy_g711_pad_is_off
    u32             : 1 ;
    u32 GPIO_0      : 1 ; // 5       GPIO_0             SPI1_SCLK
    u32             : 2 ;
    u32 GPIO_1      : 1 ; // 8       GPIO_1             SPI1_SDO
    u32             : 2 ;
    u32 GPIO_2      : 1 ; // 11      GPIO_2             SPI1_SDIO
    u32             : 2 ;
    u32 GPIO_3      : 1 ; // 14      GPIO_3             SPI1_SSL0
    u32             : 2 ;
    u32 GPIO_4      : 2 ; // 18:17   GPIO_4             SPI1_SSL1          EXTINT0
    u32             : 1 ;
    u32 GPIO_5      : 2 ; // 21:20   GPIO_5             SPI2_SCLK          SPI_ABDL_CLK       I2S2_SCK
    u32             : 1 ;
    u32 GPIO_6      : 2 ; // 24:23   GPIO_6             SPI2_SDO           SPI_ABDL_IN
    u32             : 1 ;
    u32 GPIO_7      : 2 ; // 27:26   GPIO_7             SPI2_SDIO          SPI_ABDL_OUT       I2S2_SDO
    u32             : 1 ;
    u32 GPIO_8      : 2 ; // 30:29   GPIO_8             SPI2_SSL0          SPI_ABDL_EN        I2S2_WS
    u32             : 1 ;
} KePadMux2_t;

#define GPIO_MUX_PCMG711_POS 2 //----------------------------------- PCMG711
#define GPIO_MUX_PCMG711_MSK ((u32)3<<GPIO_MUX_PCMG711_POS)
#define GPIO_MUX_PCMG711_PCM 0
#define GPIO_MUX_PCMG711_I2S 1
#define GPIO_MUX_PCMG711_DAI 2
#define GPIO_MUX_PCMG711_FDI 3
#define GPIO_MUX_GPIO_0_POS       5 //------------------------------- GPIO_0
#define GPIO_MUX_GPIO_0_MSK       ((u32)1<<GPIO_MUX_GPIO_0_POS)
#define GPIO_MUX_GPIO_0_GPIO_0    0
#define GPIO_MUX_GPIO_0_SPI1_SCLK 1
#define GPIO_MUX_GPIO_1_POS      8 //-------------------------------- GPIO_1
#define GPIO_MUX_GPIO_1_MSK      ((u32)1<<GPIO_MUX_GPIO_1_POS)
#define GPIO_MUX_GPIO_1_GPIO_1   0
#define GPIO_MUX_GPIO_1_SPI1_SDO 1
#define GPIO_MUX_GPIO_2_POS       11 //------------------------------ GPIO_2
#define GPIO_MUX_GPIO_2_MSK       ((u32)1<<GPIO_MUX_GPIO_2_POS)
#define GPIO_MUX_GPIO_2_GPIO_2    0
#define GPIO_MUX_GPIO_2_SPI1_SDIO 1
#define GPIO_MUX_GPIO_3_POS       14 //------------------------------ GPIO_3
#define GPIO_MUX_GPIO_3_MSK       ((u32)1<<GPIO_MUX_GPIO_3_POS)
#define GPIO_MUX_GPIO_3_GPIO_3    0
#define GPIO_MUX_GPIO_3_SPI1_SSL0 1
#define GPIO_MUX_GPIO_4_POS       17 //------------------------------ GPIO_4
#define GPIO_MUX_GPIO_4_MSK       ((u32)3<<GPIO_MUX_GPIO_4_POS)
#define GPIO_MUX_GPIO_4_GPIO_4    0
#define GPIO_MUX_GPIO_4_SPI1_SSL1 1
#define GPIO_MUX_GPIO_4_EXTINT0   2
#define GPIO_MUX_GPIO_5_POS          20 //--------------------------- GPIO_5
#define GPIO_MUX_GPIO_5_MSK          ((u32)3<<GPIO_MUX_GPIO_5_POS)
#define GPIO_MUX_GPIO_5_GPIO_5       0
#define GPIO_MUX_GPIO_5_SPI2_SCLK    1
#define GPIO_MUX_GPIO_5_SPI_ABDL_CLK 2
#define GPIO_MUX_GPIO_5_I2S2_SCK     3
#define GPIO_MUX_GPIO_6_POS         23 //---------------------------- GPIO_6
#define GPIO_MUX_GPIO_6_MSK         ((u32)3<<GPIO_MUX_GPIO_6_POS)
#define GPIO_MUX_GPIO_6_GPIO_6      0
#define GPIO_MUX_GPIO_6_SPI2_SDO    1
#define GPIO_MUX_GPIO_6_SPI_ABDL_IN 2
#define GPIO_MUX_GPIO_7_POS          26 //--------------------------- GPIO_7
#define GPIO_MUX_GPIO_7_MSK          ((u32)3<<GPIO_MUX_GPIO_7_POS)
#define GPIO_MUX_GPIO_7_GPIO_7       0
#define GPIO_MUX_GPIO_7_SPI2_SDIO    1
#define GPIO_MUX_GPIO_7_SPI_ABDL_OUT 2
#define GPIO_MUX_GPIO_7_I2S2_SDO     3
#define GPIO_MUX_GPIO_8_POS         29 //---------------------------- GPIO_8
#define GPIO_MUX_GPIO_8_MSK         ((u32)3<<GPIO_MUX_GPIO_8_POS)
#define GPIO_MUX_GPIO_8_GPIO_8      0
#define GPIO_MUX_GPIO_8_SPI2_SSL0   1
#define GPIO_MUX_GPIO_8_SPI_ABDL_EN 2
#define GPIO_MUX_GPIO_8_I2S2_WS     3

/*** Mux 3 register ***/
typedef struct MUX_3 {
    u32 GPIO_9      : 2 ; // 1:0     GPIO_9             SPI2_SSL1          EXTINT1
    u32             : 1 ;
    u32 GPIO_11_10  : 1 ; // 3       GPIO               I2C
                          //         gpio_10            i2c_sda
                          //         gpio_11            i2c_sck
    u32             : 2 ;
    u32 EBI_D_11_8  : 2 ; // 7:6     EBI                DBG                OFF
                          //         ebi_d_11           dbg_ebi_11         ebi_d_11_pad_is_off
                          //         ebi_d_10           dbg_ebi_10         ebi_d_10_pad_is_off
                          //         ebi_d_9            dbg_ebi_9          ebi_d_9_pad_is_off
                          //         ebi_d_8            dbg_ebi_8          ebi_d_8_pad_is_off
    u32             : 1 ;
    u32 GPIO_12     : 2 ; // 10:9    GPIO_12            CS_USR0            CS_SDRAM0
    u32             : 1 ;
    u32 GPIO_13     : 2 ; // 13:12   GPIO_13            CS_MEM2            CS_SDRAM1
    u32             : 1 ;
    u32 GPIO_14     : 2 ; // 16:15   GPIO_14            CS_MEM3            SDRAM_UDQM
    u32             : 1 ;
    u32 GPIO_15     : 2 ; // 19:18   GPIO_15            EXTINT2            CS_USR1
    u32             : 1 ;
    u32 GPIO_16     : 2 ; // 22:21   GPIO_16            EXTINT3            CS_USR2
    u32             : 1 ;
    u32 GPIO_17     : 1 ; // 24      WDN                GPIO_17
    u32             : 2 ;
    u32 GPIO_18     : 2 ; // 28:27   GPIO_18            PERIPH1_CLK        CLK32K_OUT
    u32             : 3 ;
} KePadMux3_t;

#define GPIO_MUX_GPIO_9_POS       0 //------------------------------- GPIO_9
#define GPIO_MUX_GPIO_9_MSK       ((u32)3<<GPIO_MUX_GPIO_9_POS)
#define GPIO_MUX_GPIO_9_GPIO_9    0
#define GPIO_MUX_GPIO_9_SPI2_SSL1 1
#define GPIO_MUX_GPIO_9_EXTINT1   2
#define GPIO_MUX_GPIO_11_10_POS  3 //---------------------------- GPIO_11_10
#define GPIO_MUX_GPIO_11_10_MSK  ((u32)1<<GPIO_MUX_GPIO_11_10_POS)
#define GPIO_MUX_GPIO_11_10_GPIO 0
#define GPIO_MUX_GPIO_11_10_I2C  1
#define GPIO_MUX_EBI_D_11_8_POS 6 //----------------------------- EBI_D_11_8
#define GPIO_MUX_EBI_D_11_8_MSK ((u32)3<<GPIO_MUX_EBI_D_11_8_POS)
#define GPIO_MUX_EBI_D_11_8_EBI 0
#define GPIO_MUX_EBI_D_11_8_DBG 1
#define GPIO_MUX_EBI_D_11_8_OFF 2
#define GPIO_MUX_GPIO_12_POS       9 //----------------------------- GPIO_12
#define GPIO_MUX_GPIO_12_MSK       ((u32)3<<GPIO_MUX_GPIO_12_POS)
#define GPIO_MUX_GPIO_12_GPIO_12   0
#define GPIO_MUX_GPIO_12_CS_USR0   1
#define GPIO_MUX_GPIO_12_CS_SDRAM0 2
#define GPIO_MUX_GPIO_13_POS       12 //---------------------------- GPIO_13
#define GPIO_MUX_GPIO_13_MSK       ((u32)3<<GPIO_MUX_GPIO_13_POS)
#define GPIO_MUX_GPIO_13_GPIO_13   0
#define GPIO_MUX_GPIO_13_CS_MEM2   1
#define GPIO_MUX_GPIO_13_CS_SDRAM1 2
#define GPIO_MUX_GPIO_14_POS        15 //--------------------------- GPIO_14
#define GPIO_MUX_GPIO_14_MSK        ((u32)3<<GPIO_MUX_GPIO_14_POS)
#define GPIO_MUX_GPIO_14_GPIO_14    0
#define GPIO_MUX_GPIO_14_CS_MEM3    1
#define GPIO_MUX_GPIO_14_SDRAM_UDQM 2
#define GPIO_MUX_GPIO_15_POS     18 //------------------------------ GPIO_15
#define GPIO_MUX_GPIO_15_MSK     ((u32)3<<GPIO_MUX_GPIO_15_POS)
#define GPIO_MUX_GPIO_15_GPIO_15 0
#define GPIO_MUX_GPIO_15_EXTINT2 1
#define GPIO_MUX_GPIO_15_CS_USR1 2
#define GPIO_MUX_GPIO_16_POS     21 //------------------------------ GPIO_16
#define GPIO_MUX_GPIO_16_MSK     ((u32)3<<GPIO_MUX_GPIO_16_POS)
#define GPIO_MUX_GPIO_16_GPIO_16 0
#define GPIO_MUX_GPIO_16_EXTINT3 1
#define GPIO_MUX_GPIO_16_CS_USR2 2
#define GPIO_MUX_GPIO_17_POS     24 //------------------------------ GPIO_17
#define GPIO_MUX_GPIO_17_MSK     ((u32)1<<GPIO_MUX_GPIO_17_POS)
#define GPIO_MUX_GPIO_17_WDN     0
#define GPIO_MUX_GPIO_17_GPIO_17 1
#define GPIO_MUX_GPIO_18_POS         27 //-------------------------- GPIO_18
#define GPIO_MUX_GPIO_18_MSK         ((u32)3<<GPIO_MUX_GPIO_18_POS)
#define GPIO_MUX_GPIO_18_GPIO_18     0
#define GPIO_MUX_GPIO_18_PERIPH1_CLK 1
#define GPIO_MUX_GPIO_18_CLK32K_OUT  2

/*** Mux 4 register ***/
typedef struct MUX_4 {
    u32             : 1 ;
    u32 GPIO_20     : 3 ; // 3:1     GPIO_20            EXTINT5            EBI_WAIT0          DBG_EBI_29         GPIO_20_PAD_IS_OFF
    u32 GPIO_21     : 2 ; // 5:4     GPIO_21            DBG_EBI_30         GPIO_21_PAD_IS_OFF
    u32             : 1 ;
    u32 GPIO_22     : 2 ; // 8:7     GPIO_22            PERIPH2_CLK        CLK32K_OUT         GPIO_22_PAD_IS_OFF
    u32             : 1 ;
    u32 GPIO_23     : 2 ; // 11:10   GPIO_23            EBI_CS2            DBG_EBI_31         GPIO_23_PAD_IS_OFF
    u32             : 1 ;
    u32 GPIO_24     : 2 ; // 14:13   GPIO_24            UART1_RXD          TRACE_PKT_15
    u32             : 1 ;
    u32 GPIO_25     : 2 ; // 17:16   GPIO_25            UART1_TXD          BOOT_CTRL0         TRACE_PKT_14
    u32             : 1 ;
    u32 GPIO_26     : 2 ; // 20:19   GPIO_26            UART1_RTS          BOOT_CTRL1         TRACE_PKT_13
    u32             : 1 ;
    u32 GPIO_27     : 2 ; // 23:22   GPIO_27            UART1_CTS          TRACE_PKT_12
    u32             : 1 ;
    u32 GPIO_28     : 2 ; // 26:25   GPIO_28            UART1_DSR          TRACE_PKT_11
    u32             : 1 ;
    u32 GPIO_29     : 3 ; // 30:28   GPIO_29            UART1_DTR          BOOT_CTRL2         EXTINT6            TRACE_PKT_10
    u32             : 1 ;
} KePadMux4_t;

#define GPIO_MUX_GPIO_20_POS                1 //-------------------- GPIO_20
#define GPIO_MUX_GPIO_20_MSK                ((u32)7<<GPIO_MUX_GPIO_20_POS)
#define GPIO_MUX_GPIO_20_GPIO_20            0
#define GPIO_MUX_GPIO_20_EXTINT5            1
#define GPIO_MUX_GPIO_20_EBI_WAIT0          2
#define GPIO_MUX_GPIO_20_DBG_EBI_29         3
#define GPIO_MUX_GPIO_20_GPIO_20_PAD_IS_OFF 4
#define GPIO_MUX_GPIO_21_POS                4 //-------------------- GPIO_21
#define GPIO_MUX_GPIO_21_MSK                ((u32)3<<GPIO_MUX_GPIO_21_POS)
#define GPIO_MUX_GPIO_21_GPIO_21            0
#define GPIO_MUX_GPIO_21_DBG_EBI_30         1
#define GPIO_MUX_GPIO_21_GPIO_21_PAD_IS_OFF 2
#define GPIO_MUX_GPIO_22_POS                7 //-------------------- GPIO_22
#define GPIO_MUX_GPIO_22_MSK                ((u32)3<<GPIO_MUX_GPIO_22_POS)
#define GPIO_MUX_GPIO_22_GPIO_22            0
#define GPIO_MUX_GPIO_22_PERIPH2_CLK        1
#define GPIO_MUX_GPIO_22_CLK32K_OUT         2
#define GPIO_MUX_GPIO_22_GPIO_22_PAD_IS_OFF 3
#define GPIO_MUX_GPIO_23_POS                10 //------------------- GPIO_23
#define GPIO_MUX_GPIO_23_MSK                ((u32)3<<GPIO_MUX_GPIO_23_POS)
#define GPIO_MUX_GPIO_23_GPIO_23            0
#define GPIO_MUX_GPIO_23_EBI_CS2            1
#define GPIO_MUX_GPIO_23_DBG_EBI_31         2
#define GPIO_MUX_GPIO_23_GPIO_23_PAD_IS_OFF 3
#define GPIO_MUX_GPIO_24_POS          13 //------------------------- GPIO_24
#define GPIO_MUX_GPIO_24_MSK          ((u32)3<<GPIO_MUX_GPIO_24_POS)
#define GPIO_MUX_GPIO_24_GPIO_24      0
#define GPIO_MUX_GPIO_24_UART1_RXD    1
#define GPIO_MUX_GPIO_24_TRACE_PKT_15 2
#define GPIO_MUX_GPIO_25_POS          16 //------------------------- GPIO_25
#define GPIO_MUX_GPIO_25_MSK          ((u32)3<<GPIO_MUX_GPIO_25_POS)
#define GPIO_MUX_GPIO_25_GPIO_25      0
#define GPIO_MUX_GPIO_25_UART1_TXD    1
#define GPIO_MUX_GPIO_25_BOOT_CTRL0   2
#define GPIO_MUX_GPIO_25_TRACE_PKT_14 3
#define GPIO_MUX_GPIO_26_POS          19 //------------------------- GPIO_26
#define GPIO_MUX_GPIO_26_MSK          ((u32)3<<GPIO_MUX_GPIO_26_POS)
#define GPIO_MUX_GPIO_26_GPIO_26      0
#define GPIO_MUX_GPIO_26_UART1_RTS    1
#define GPIO_MUX_GPIO_26_BOOT_CTRL1   2
#define GPIO_MUX_GPIO_26_TRACE_PKT_13 3
#define GPIO_MUX_GPIO_27_POS          22 //------------------------- GPIO_27
#define GPIO_MUX_GPIO_27_MSK          ((u32)3<<GPIO_MUX_GPIO_27_POS)
#define GPIO_MUX_GPIO_27_GPIO_27      0
#define GPIO_MUX_GPIO_27_UART1_CTS    1
#define GPIO_MUX_GPIO_27_TRACE_PKT_12 2
#define GPIO_MUX_GPIO_28_POS          25 //------------------------- GPIO_28
#define GPIO_MUX_GPIO_28_MSK          ((u32)3<<GPIO_MUX_GPIO_28_POS)
#define GPIO_MUX_GPIO_28_GPIO_28      0
#define GPIO_MUX_GPIO_28_UART1_DSR    1
#define GPIO_MUX_GPIO_28_TRACE_PKT_11 2
#define GPIO_MUX_GPIO_29_POS          28 //------------------------- GPIO_29
#define GPIO_MUX_GPIO_29_MSK          ((u32)7<<GPIO_MUX_GPIO_29_POS)
#define GPIO_MUX_GPIO_29_GPIO_29      0
#define GPIO_MUX_GPIO_29_UART1_DTR    1
#define GPIO_MUX_GPIO_29_BOOT_CTRL2   2
#define GPIO_MUX_GPIO_29_EXTINT6      3
#define GPIO_MUX_GPIO_29_TRACE_PKT_10 4

/*** Mux 5 register ***/
typedef struct MUX_5 {
    u32             : 2 ;
    u32 GPIO_31     : 2 ; // 3:2     GPIO_31            UART2_TXD          BOOT_CTRL3
    u32             : 1 ;
    u32 GPIO_32     : 2 ; // 6:5     GPIO_32            UART2_RTS          BOOT_CLKSEL
    u32             : 1 ;
    u32 GPIO_33     : 1 ; // 8       GPIO_33            UART2_CTS
    u32             : 2 ;
    u32 GPIO_34     : 2 ; // 12:11   GPIO_34            PERIPH3_CLK        TRACECLK           CLK32K_OUT
    u32             : 1 ;
    u32 GPIO_35     : 2 ; // 15:14   GPIO_35            PWM_OUT0           USIM1PRES          TRACE_PKT_9
    u32             : 1 ;
    u32 GPIO_36     : 2 ; // 18:17   GPIO_36            PWM_OUT1           CLK8KHZ_OUT        TRACE_PKT_8
    u32             : 1 ;
    u32 GPIO_37     : 2 ; // 21:20   GPIO_37            EXTINT5            PERIPH3_CLK        BOOT_CTRL4
    u32             : 1 ;
    u32 EBI_WRN     : 2 ; // 24:23   EBI_WRN            DBG_EBI_18         EBI_WRN_PAD_IS_OFF
    u32             : 1 ;
    u32 EBI_A_7_1   : 2 ; // 27:26   EBI_A              SDRAM              DBG                OFF
                          //         ebi_a_7            sdram_cke          dbg_ebi_27         ebi_a_7_pad_is_off
                          //         ebi_a_6            sdram_ras          dbg_ebi_26         ebi_a_6_pad_is_off
                          //         ebi_a_5            sdram_we           dbg_ebi_25         ebi_a_5_pad_is_off
                          //         ebi_a_4            sdram_ba1          dbg_ebi_24         ebi_a_4_pad_is_off
                          //         ebi_a_3            sdram_ba0          dbg_ebi_23         ebi_a_3_pad_is_off
                          //         ebi_a_2            sdram_ldqm         dbg_ebi_22         ebi_a_2_pad_is_off
                          //         ebi_a_1            sdram_cas          dbg_ebi_21         ebi_a_1_pad_is_off
    u32             : 1 ;
    u32 TBUO7       : 2 ; // 30:29   TBUO7              QBSAVE             GPIO_3             BOOT_CTRL5
    u32             : 1 ;
} KePadMux5_t;

#define GPIO_MUX_GPIO_31_POS        2 //---------------------------- GPIO_31
#define GPIO_MUX_GPIO_31_MSK        ((u32)3<<GPIO_MUX_GPIO_31_POS)
#define GPIO_MUX_GPIO_31_GPIO_31    0
#define GPIO_MUX_GPIO_31_UART2_TXD  1
#define GPIO_MUX_GPIO_31_BOOT_CTRL3 2
#define GPIO_MUX_GPIO_32_POS         5 //--------------------------- GPIO_32
#define GPIO_MUX_GPIO_32_MSK         ((u32)3<<GPIO_MUX_GPIO_32_POS)
#define GPIO_MUX_GPIO_32_GPIO_32     0
#define GPIO_MUX_GPIO_32_UART2_RTS   1
#define GPIO_MUX_GPIO_32_BOOT_CLKSEL 2
#define GPIO_MUX_GPIO_33_POS       8 //----------------------------- GPIO_33
#define GPIO_MUX_GPIO_33_MSK       ((u32)1<<GPIO_MUX_GPIO_33_POS)
#define GPIO_MUX_GPIO_33_GPIO_33   0
#define GPIO_MUX_GPIO_33_UART2_CTS 1
#define GPIO_MUX_GPIO_34_POS         11 //-------------------------- GPIO_34
#define GPIO_MUX_GPIO_34_MSK         ((u32)3<<GPIO_MUX_GPIO_34_POS)
#define GPIO_MUX_GPIO_34_GPIO_34     0
#define GPIO_MUX_GPIO_34_PERIPH3_CLK 1
#define GPIO_MUX_GPIO_34_TRACECLK    2
#define GPIO_MUX_GPIO_34_CLK32K_OUT  3
#define GPIO_MUX_GPIO_35_POS         14 //-------------------------- GPIO_35
#define GPIO_MUX_GPIO_35_MSK         ((u32)3<<GPIO_MUX_GPIO_35_POS)
#define GPIO_MUX_GPIO_35_GPIO_35     0
#define GPIO_MUX_GPIO_35_PWM_OUT0    1
#define GPIO_MUX_GPIO_35_USIM1PRES   2
#define GPIO_MUX_GPIO_35_TRACE_PKT_9 3
#define GPIO_MUX_GPIO_36_POS         17 //-------------------------- GPIO_36
#define GPIO_MUX_GPIO_36_MSK         ((u32)3<<GPIO_MUX_GPIO_36_POS)
#define GPIO_MUX_GPIO_36_GPIO_36     0
#define GPIO_MUX_GPIO_36_PWM_OUT1    1
#define GPIO_MUX_GPIO_36_CLK8KHZ_OUT 2
#define GPIO_MUX_GPIO_36_TRACE_PKT_8 3
#define GPIO_MUX_GPIO_37_POS         20 //-------------------------- GPIO_37
#define GPIO_MUX_GPIO_37_MSK         ((u32)3<<GPIO_MUX_GPIO_37_POS)
#define GPIO_MUX_GPIO_37_GPIO_37     0
#define GPIO_MUX_GPIO_37_EXTINT5     1
#define GPIO_MUX_GPIO_37_PERIPH3_CLK 2
#define GPIO_MUX_GPIO_37_BOOT_CTRL4  3
#define GPIO_MUX_EBI_WRN_POS                23 //------------------- EBI_WRN
#define GPIO_MUX_EBI_WRN_MSK                ((u32)3<<GPIO_MUX_EBI_WRN_POS)
#define GPIO_MUX_EBI_WRN_EBI_WRN            0
#define GPIO_MUX_EBI_WRN_DBG_EBI_18         1
#define GPIO_MUX_EBI_WRN_EBI_WRN_PAD_IS_OFF 2
#define GPIO_MUX_EBI_A_7_1_POS   26 //---------------------------- EBI_A_7_1
#define GPIO_MUX_EBI_A_7_1_MSK   ((u32)3<<GPIO_MUX_EBI_A_7_1_POS)
#define GPIO_MUX_EBI_A_7_1_EBI_A 0
#define GPIO_MUX_EBI_A_7_1_SDRAM 1
#define GPIO_MUX_EBI_A_7_1_DBG   2
#define GPIO_MUX_EBI_A_7_1_OFF   3
#define GPIO_MUX_TBUO7_POS        29 //------------------------------- TBUO7
#define GPIO_MUX_TBUO7_MSK        ((u32)3<<GPIO_MUX_TBUO7_POS)
#define GPIO_MUX_TBUO7_TBUO7      0
#define GPIO_MUX_TBUO7_QBSAVE     1
#define GPIO_MUX_TBUO7_GPIO_3     2
#define GPIO_MUX_TBUO7_BOOT_CTRL5 3

/*** Mux 0 register ***/
typedef struct MUX_6 {
    u32 GPIO_19     : 2 ; // 1:0     GPIO_19            EXTINT4            DBG_EBI_28         GPIO_19_PAD_IS_OFF
    u32             : 1 ;
    u32 GPIO_30     : 1 ; // 3       GPIO_30            UART2_RXD
    u32             : 2 ;
    u32 AB_I2S      : 1 ; // 6       AB_I2S             I2S2
                          //         ab_i2s_sdo         i2s2_sdo
                          //         ab_i2s_sck         i2s2_sck
                          //         ab_i2s_ws          i2s2_ws
    u32             : 25;
} KePadMux6_t;

#define GPIO_MUX_GPIO_19_POS                0 //-------------------- GPIO_19
#define GPIO_MUX_GPIO_19_MSK                ((u32)3<<GPIO_MUX_GPIO_19_POS)
#define GPIO_MUX_GPIO_19_GPIO_19            0
#define GPIO_MUX_GPIO_19_EXTINT4            1
#define GPIO_MUX_GPIO_19_DBG_EBI_28         2
#define GPIO_MUX_GPIO_19_GPIO_19_PAD_IS_OFF 3
#define GPIO_MUX_GPIO_30_POS       3 //----------------------------- GPIO_30
#define GPIO_MUX_GPIO_30_MSK       ((u32)1<<GPIO_MUX_GPIO_30_POS)
#define GPIO_MUX_GPIO_30_GPIO_30   0
#define GPIO_MUX_GPIO_30_UART2_RXD 1
#define GPIO_MUX_AB_I2S_POS    6 //---------------------------------- AB_I2S
#define GPIO_MUX_AB_I2S_MSK    ((u32)1<<GPIO_MUX_AB_I2S_POS)
#define GPIO_MUX_AB_I2S_AB_I2S 0
#define GPIO_MUX_AB_I2S_I2S2   1

/*** Pull registers ***/
#define GPIO_PULL_DEACTIVATE_IO_0     		((u32)1<<0)
#define GPIO_PULL_DEACTIVATE_IO_1     		((u32)1<<1)
#define GPIO_PULL_DEACTIVATE_IO_2     		((u32)1<<2)
#define GPIO_PULL_DEACTIVATE_IO_3     		((u32)1<<3)
#define GPIO_PULL_DEACTIVATE_IO_4     		((u32)1<<4)
#define GPIO_PULL_DEACTIVATE_IO_5     		((u32)1<<5)
#define GPIO_PULL_DEACTIVATE_IO_7     		((u32)1<<7)
#define GPIO_PULL_DEACTIVATE_IO_13     		((u32)1<<13)
#define GPIO_PULL_DEACTIVATE_IO_14     		((u32)1<<14)
#define GPIO_PULL_DEACTIVATE_IO_15     		((u32)1<<15)
#define GPIO_PULL_DEACTIVATE_IO_16     		((u32)1<<16)
#define GPIO_PULL_DEACTIVATE_IO_17     		((u32)1<<17)
#define GPIO_PULL_DEACTIVATE_IO_29     		((u32)1<<29)
#define GPIO_PULL_DEACTIVATE_IO_30     		((u32)1<<30)
#define GPIO_PULL_DEACTIVATE_IO_31     		((u32)1<<31)
#define GPIO_PULL_DEACTIVATE_IO_32     		((u32)1<<0)
#define GPIO_PULL_DEACTIVATE_IO_33     		((u32)1<<1)
#define GPIO_PULL_DEACTIVATE_IO_35     		((u32)1<<3)
#define GPIO_PULL_DEACTIVATE_IO_36     		((u32)1<<4)
#define GPIO_PULL_DEACTIVATE_IO_37     		((u32)1<<5)
#define GPIO_PULL_DEACTIVATE_IO_38     		((u32)1<<6)
#define GPIO_PULL_DEACTIVATE_IO_40     		((u32)1<<8)
#define GPIO_PULL_DEACTIVATE_IO_41     		((u32)1<<9)
#define GPIO_PULL_DEACTIVATE_IO_46     		((u32)1<<14)
#define GPIO_PULL_DEACTIVATE_IO_48     		((u32)1<<16)
#define GPIO_PULL_DEACTIVATE_IO_49     		((u32)1<<17)
#define GPIO_PULL_DEACTIVATE_IO_50     		((u32)1<<18)
#define GPIO_PULL_DEACTIVATE_IO_51     		((u32)1<<19)
#define GPIO_PULL_DEACTIVATE_IO_52     		((u32)1<<20)
#define GPIO_PULL_DEACTIVATE_IO_53     		((u32)1<<21)
#define GPIO_PULL_DEACTIVATE_IO_54     		((u32)1<<22)
#define GPIO_PULL_DEACTIVATE_IO_55     		((u32)1<<23)
#define GPIO_PULL_DEACTIVATE_IO_56     		((u32)1<<24)
#define GPIO_PULL_DEACTIVATE_IO_57     		((u32)1<<25)
#define GPIO_PULL_DEACTIVATE_IO_58     		((u32)1<<26)
#define GPIO_PULL_DEACTIVATE_IO_59     		((u32)1<<27)
#define GPIO_PULL_DEACTIVATE_IO_60     		((u32)1<<28)
#define GPIO_PULL_DEACTIVATE_IO_61     		((u32)1<<29)
#define GPIO_PULL_DEACTIVATE_WAIT_N 		((u32)1<<0)
#define GPIO_PULL_DEACTIVATE_NAND_R_B	((u32)1<<8)
#define GPIO_PULL_DEACTIVATE_USB_0     		((u32)1<<16)
#define GPIO_PULL_DEACTIVATE_USB_1     		((u32)1<<17)
#define GPIO_PULL_DEACTIVATE_USB_2     		((u32)1<<18)
#define GPIO_PULL_DEACTIVATE_AUDIO_0		((u32)1<<24)
#define GPIO_PULL_DEACTIVATE_AUDIO_1		((u32)1<<25)
#define GPIO_PULL_DEACTIVATE_AUDIO_2		((u32)1<<26)
#define GPIO_PULL_DEACTIVATE_AUDIO_3		((u32)1<<27)
#endif //__B1__

/************************************************/
/* KEYPAD registers definition                  */
/************************************************/

typedef struct OKeyPad_s
{
    u16 u16_Config; // 0x00
    u16     u16_IoConfig;
    u16 u16_Data; // 0x04
    u16 u16_ColRowMode;
    u16 u16_InterruptStatus; // 0x08
    u16 u16_Spare1;
    u16 u16_InterruptClear; // 0x0C
    u16 u16_Spare2;
    u16 u16_Raw_Status;// 0x10
    u16 u16_Spare3;
    u16 u16_Status;// 0x14
} OKeyPad_t;

/*** Config register ***/
#define KEYPAD_DEBOUNCE_MSK     (0x003F<<0)
#define KEYPAD_DEBOUNCE_POS     0

/* IO mode configuration register */
#define KEYPAD_DIR_ROW_POS       0
#define KEYPAD_DIR_ROW_MSK      (0x003F<<KEYPAD_DIR_ROW_POS) // 1 = IN 0=OUT
#define KEYPAD_DIR_COL_POS       6
#define KEYPAD_DIR_COL_MSK      (0x003F<<KEYPAD_DIR_COL_POS)

/*** Data register ***/
#define KEYPAD_DATA_ROW_POS      0
#define KEYPAD_DATA_ROW_MSK     (0x003F<<KEYPAD_DATA_ROW_POS)
#define KEYPAD_DATA_COL_POS      6
#define KEYPAD_DATA_COL_MSK     (0x003F<<KEYPAD_DATA_COL_POS)


/*** Col Row Mode ***/
#define KEYPAD_MODE_ROW_POS 0  // 0=keyboard 1 =IO pads
#define KEYPAD_MODE_ROW_MSK (0x003f << KEYPAD_MODE_ROW_POS)
#define KEYPAD_MODE_COL_POS 6
#define KEYPAD_MODE_COL_MSK (0x003f << KEYPAD_MODE_COL_POS)


/*** Status register ***/
#define KEYPAD_ROW_PRESSED_POS   0
#define KEYPAD_ROW_PRESSED_MSK  (0x003F<<0) // 0 = pressed
#define KEYPAD_COL_PRESSED_POS   6
#define KEYPAD_COL_PRESSED_MSK  (0x003F<<KEYPAD_COL_PRESSED_POS)

#ifdef __B1__
/*****************************************************************************/
/* RTC Real Time Clock                                                       */
/*****************************************************************************/
typedef struct W5Rtc_s
{
  u32           Ctrl;
  u32           Time;
  u32           Date;
  u32           TimeAlarm;
  u32           CalendarAlarm;
  u32           Status;
  u32           Imr;
  u32           PwrCtrl;
  u16           u16_Cnt;
  u16           u16_pad;
} W5Rtc_t;

/* control register */
#define RTC_STOP_CNT                 (1 << 0)  // freeze the counter when highest
#define RTC_TIMEVTSEL_POS          1
#define RTC_TIMEVTSEL_MINUTE     (0 << RTC_TIMEVTSEL_POS)
#define RTC_TIMEVTSEL_HOUR        (1 << RTC_TIMEVTSEL_POS)
#define RTC_TIMEVTSEL_MIDNIGHT  (2 << RTC_TIMEVTSEL_POS)
#define RTC_TIMEVTSEL_NOON        (3 << RTC_TIMEVTSEL_POS)
#define RTC_TIMEVTSEL_MASK        (3 << RTC_TIMEVTSEL_POS)

#define RTC_CALEVTSEL_POS       3
#define RTC_CALEVTSEL_WEEK        (0 << RTC_CALEVTSEL_POS)
#define RTC_CALEVTSEL_MONTH        (1 << RTC_CALEVTSEL_POS)
#define RTC_CALEVTSEL_YEAR        (2 << RTC_CALEVTSEL_POS)
#define RTC_CALEVTSEL_MASK        (3 << RTC_CALEVTSEL_POS)

#define RTC_ALRCLR                    (1 << 8)   /* alarm event status clear */
#define RTC_SECCLR                    (1 << 9)   /* second event status clear */
#define RTC_TIMCLR                    (1 << 10) /* time event status clear */
#define RTC_CALCLR                    (1 << 11) /* time event status clear */

/* register time */
#define RTC_SEC_POS     0 /* second */
#define RTC_SEC_MASK   (0x3f << RTC_SEC_POS)
#define RTC_MIN_POS     8 /* minute */
#define RTC_MIN_MASK   (0x3f << RTC_MIN_POS)
#define RTC_HOUR_POS          16 /* hour */
#define RTC_HOUR_MASK (0x01f << RTC_HOUR_POS)

/* date register */
#define RTC_DATE_POS        0 /* 1 - 31 */
#define RTC_DATE_MASK        (0x1f << RTC_DATE_POS)
#define RTC_DAY_POS         8 /* day 1 - 7 */
#define RTC_DAY_MASK        (0x07 << RTC_DAY_POS)
#define RTC_MONTH_POS     12 /* month 1 - 12 */
#define RTC_MONTH_MASK        (0x0f << RTC_MONTH_POS)
#define RTC_YEAR_POS        16 /* year */
#define RTC_YEAR_MASK        (0x7f << RTC_YEAR_POS)
#define RTC_CENT_POS        24 /* century */
#define RTC_CENT_MASK        (0x1f << RTC_CENT_POS)

/* time alarm register */

#define RTC_ALRM_SEC_POS     0 /* second */
#define RTC_ALRM_SEC_MASK   (0x3f << RTC_ALRM_SEC_POS)
#define RTC_ALRM_SEC_EN       (1 << 7) /* second alarm enable */
#define RTC_ALRM_MIN_POS     8 /* minute */
#define RTC_ALRM_MIN_MASK   (0x3f << RTC_ALRM_MIN_POS)
#define RTC_ALRM_MIN_EN       (1 << 15) /* minute alarm enable */
#define RTC_ALRM_HOUR_POS          16 /* hour */
#define RTC_ALRM_HOUR_MASK (0x1f << RTC_ALRM_HOUR_POS)
#define RTC_ALRM_HOUR_EN       (1 << 23) /* hour alarm enable */

/* calendar alarm register */

#define RTC_ALRM_DATE_POS        0 /* 1 - 31 */
#define RTC_ALRM_DATE_MASK        (0x1f << RTC_DATE_POS)
#define RTC_ALRM_DATE_EN          (1 << 8) /* date alarm enable */
#define RTC_ALRM_MONTH_POS     12 /* month 1 - 12 */
#define RTC_ALRM_MONTH_MASK        (0x0f << RTC_MONTH_POS)
#define RTC_ALRM_MONTH_EN       (1 << 16) /* month alarm enable */

/* status register */
#define RTC_STATUS_CIA          (1 << 0) /* CPU interface active */
#define RTC_STATUS_ACKUPD       (1 << 1) /* updating time & date register available */
#define RTC_STATUS_ALREVT       (1 << 2) /* alarm event status*/
#define RTC_STATUS_SECEVT       (1 << 3) /* second event status*/
#define RTC_STATUS_TIMEVT       (1 << 4) /* time event status */
#define RTC_STATUS_CALEVT       (1 << 5) /* calendar event status */
#define RTC_STATUS_CTRL_RESY    (1 << 6) /* control register resynchronization */
#define RTC_STATUS_TIME_RESY    (1 << 7) /* time register resynchronization */
#define RTC_STATUS_DATE_RESY    (1 << 8) /* date register resynchronization */
#define RTC_STATUS_IMR_RESY     (1 << 9) /* imr register resynchronization */
#define RTC_STATUS_PWR_RESY     (1 << 10) /* power register resynchronization */
#define RTC_STATUS_TIMEALR_RESY (1 << 11) /* time alarm register resynchronization */
#define RTC_STATUS_CALALR_RESY  (1 << 12) /* calendar alarm register resynchronization */

/* imr register */
#define RTC_IMR_ALREN           (1 << 0)    /* enable alarm interrupt */
#define RTC_IMR_SECEN           (1 << 1) /* enable second interrupt */
#define RTC_IMR_TIMEEN          (1 << 2) /* enable time interrupt */
#define RTC_IMR_CALEN           (1 << 3) /* enable calendar interrupt */

/* power control register */
#define RTC_CPU_ITF_EN   ( 1 << 0) /* CPU interface enable */
#define RTC_PWR_EN       ( 1 << 1) /* power enable pads value for direct control */
#define RTC_ALR_SIG_EN   ( 1 << 2) /* RTC_PWR_EN pads is controlled by the alarm output */
#define RTC_SW_RST       ( 1 << 3) /* RTC module software reset */
#define RTC_CK32K_OUT_EN ( 1 << 4) /* clock 32 khz available to internal use */
#define RTC_LIFE_REG     ( 1 << 8)
#endif //__B1__
/************************************************/
/* SPI registers definition                     */
/************************************************/

typedef struct OSpi_s
{
    u32 Config;
    u32 Control;
    u32 NWord;
    u32 RxTx;
    u32 Status;
    u32 Spare;
    u32 InterruptMask;
    u32 InterruptStatus;
    u32 InterruptClear;
    u32 RawInterruptStatus;
} OSpi_t;



    /* configuration register */
#define SPI_DUPLEX_MODE_FULL ((u32)1 << 31) /* mode half/full duplex */
#define SPI_DUPLEX_MODE_HALF ((u32)0 << 31)
#define SPI_APDDIS ((u32)1 << 30) /* Auto Power Down Disable */
#define SPI_TFR_MODE_DMA ((u32)1 << 29) /* transfer mode */
#define SPI_TFR_MODE_CPU ((u32)0 << 29)
#define SPI_BIG_ENDIAN  ((u32)1 << 28) /* endian alignment */
#define SPI_LITTLE_ENDIAN ((u32)0 << 28)
#define SPI_DBL_MODE ((u32)1 << 27) /* double byte mode */
#define SPI_MLOUT ( (u32)1 << 26) /* MSB or LSB first transmitted data */
#define SPI_MLIN			((u32)1<< 25) /* MSB or LSB first received data */
#define SPI_SSL_DST_SSL0 ((u32)0 << 24) /* Slave Select Destination*/
#define SPI_SSL_DST_SSL1 ((u32)1 << 24) /* Slave Select Destination*/
#define SPI_SSL_MODE_SW ((u32) 0 << 23) /* Slave Select Mode software/hardware */
#define SPI_SSL_MODE_HW ((u32)1 << 23) /* Slave Select Mode software/hardware */
#define SPI_SSL_POL_LOW ( (u32)0 << 22) /* Slave Select Polarity low */
#define SPI_SSL_POL_HIGH ((u32) 1 << 22) /* Slave Select Polarity high */
/* inter word mode determines the ssl & sclk level between 2 consecutive words */
/* 0 SSL is keep active / SCLK is shut down */
/* 1 SSL becomes inactive / SCLK is remained */
/* 2 SSL becomes inactive / SCLK is shut down */
#define SPI_ITR_MODE_POS  20
#define SPI_ITR_MODE_MASK ( (u32)3 << SPI_ITR_MODE_POS)

#define SPI_ITR_DEL_POS  16 /* inter word delay */
#define SPI_ITR_DEL_MASK ((u32)0x0f << SPI_ITR_DEL_POS)
#define SPI_MODE_MASTER ( (u32)0<< 15) /* spi mode */
#define SPI_MODE_SLAVE ( (u32)1 << 15) /* spi mode */
#define SPI_BR_POS       12                                       /* data byte rate */
#define SPI_BR_MASK ( (u32)0x07 << SPI_BR_POS)

/*  Stop Clock Latency Indicates the number of SCLK advance or offset periods related to SSL starting*/
#define SPI_SPCL_POS    8
#define SPI_SPCL_MASK	( (u32)0x0f <<  SPI_SPCL_POS)

#define SPI_STCL_POS    4       /*  Start Clock Latency */
#define SPI_STCL_MASK	( (u32)0x0f <<  SPI_STCL_POS)
#define SPI_CSPPOS	((u32)1 << 3)			/* clock stop  */
#define SPI_CSTPOS	 ( (u32)1 << 2)			/* clock start */
#define SPI_CPHA			 ( (u32)1 << 1)			/* clock phase */
#define SPI_CPOL	 ( (u32)1 << 0)			/* clock polarity */

/* control register */
#define SPI_DTL_POS     3 /* data transfer length */
#define SPI_DTL_MASK	((u32)0x0f << SPI_DTL_POS) /* data transfer length */
#define SPI_CYCLE_STOP	((u32)1 << 2 ) /* cycle stop */
#define SPI_READ ( (u32)1 << 1) /* read transfer mode */
#define SPI_WRITE ( (u32)1 << 0) /* write  transfer mode */

/* NWORD register */
#define SPI_RX_NWORD_POS 16 /* number of word to receive */
#define SPI_RX_NWORD_MASK ( 0x7FFF <<SPI_RX_NWORD_POS) /* number of word to receive */
#define SPI_TX_NWORD_POS 0 /* number of word to transmit */
#define SPI_TX_NWORD_MASK (0x7FFF <<  SPI_TX_NWORD_POS) /* number of word to transmit */

/* SPI Status*/
    #define SPI_SPTE ( 1 << 1)  /* Transmit register empty */
    #define SPI_SPRF ( 1 << 0)  /* Receiver register full */

/* raw interrupt status */
#define SPI_RAW_WAKEUP (1 << 11) /* wake up required */
#define SPI_RAW_END    (1 << 10)       /* spi cycle end */
#define SPI_RAW_SSLSP  (1 << 9) /* ssl stop detect */
#define SPI_RAW_SSLST  (1 << 8) /* ssl start detect */
#define SPI_RAW_TX_OVR (1 << 7) /* Tx Overrun */
#define SPI_RAW_RX_OVR ( 1 << 6 ) /* Rx Overrun */
#define SPI_RAW_TX_OVF ( 1 << 5 ) /* Tx Overflow */
#define SPI_RAW_RX_OVF ( 1 << 4 ) /* Tx Overflow */
#define SPI_RAW_TX_NWC ( 1 << 3 ) /* Tx N word completed */
#define SPI_RAW_RX_NWC ( 1 << 2 ) /* Rx N word completed */
#define SPI_RAW_SPTE   (1 << 1)   /* Transmitter Register Empty */
#define SPI_RAW_SPRF   (1 << 0)       /* Receiver Register Full */

/* interrupt mask */
#define SPI_IMR_WAKEUP (1 << 11) /* wake up required */
#define SPI_IMR_END    (1 << 10)       /* spi cycle end */
#define SPI_IMR_SSLSP  (1 << 9) /* ssl stop detect */
#define SPI_IMR_SSLST  (1 << 8) /* ssl start detect */
#define SPI_IMR_TX_OVR (1 << 7) /* Tx Overrun */
#define SPI_IMR_RX_OVR ( 1 << 6 ) /* Rx Overrun */
#define SPI_IMR_TX_OVF ( 1 << 5 ) /* Tx Overflow */
#define SPI_IMR_RX_OVF ( 1 << 4 ) /* Tx Overflow */
#define SPI_IMR_TX_NWC ( 1 << 3 ) /* Tx N word completed */
#define SPI_IMR_RX_NWC ( 1 << 2 ) /* Rx N word completed */
#define SPI_IMR_SPTE   (1 << 1)   /* Transmitter Register Empty */
#define SPI_IMR_SPRF   (1 << 0)       /* Receiver Register Full */

/* interrupt status */
#define SPI_ISR_WAKEUP (1 << 11) /* wake up required */
#define SPI_ISR_END    (1 << 10)       /* spi cycle end */
#define SPI_ISR_SSLSP  (1 << 9) /* ssl stop detect */
#define SPI_ISR_SSLST  (1 << 8) /* ssl start detect */
#define SPI_ISR_TX_OVR (1 << 7) /* Tx Overrun */
#define SPI_ISR_RX_OVR ( 1 << 6 ) /* Rx Overrun */
#define SPI_ISR_TX_OVF ( 1 << 5 ) /* Tx Overflow */
#define SPI_ISR_RX_OVF ( 1 << 4 ) /* Tx Overflow */
#define SPI_ISR_TX_NWC ( 1 << 3 ) /* Tx N word completed */
#define SPI_ISR_RX_NWC ( 1 << 2 ) /* Rx N word completed */
#define SPI_ISR_SPTE   (1 << 1)   /* Transmitter Register Empty */
#define SPI_ISR_SPRF   (1 << 0)       /* Receiver Register Full */

/* interrupt clear */
#define SPI_ICR_WAKEUP (1 << 11) /* wake up required */
#define SPI_ICR_END    (1 << 10)       /* spi cycle end */
#define SPI_ICR_SSLSP  (1 << 9) /* ssl stop detect */
#define SPI_ICR_SSLST  (1 << 8) /* ssl start detect */
#define SPI_ICR_TX_OVR (1 << 7) /* Tx Overrun */
#define SPI_ICR_RX_OVR ( 1 << 6 ) /* Rx Overrun */
#define SPI_ICR_TX_OVF ( 1 << 5 ) /* Tx Overflow */
#define SPI_ICR_RX_OVF ( 1 << 4 ) /* Tx Overflow */
#define SPI_ICR_TX_NWC ( 1 << 3 ) /* Tx N word completed */
#define SPI_ICR_RX_NWC ( 1 << 2 ) /* Rx N word completed */
#define SPI_ICR_SPTE   (1 << 1)   /* Transmitter Register Empty */
#define SPI_ICR_SPRF   (1 << 0)       /* Receiver Register Full */

/************************************************/
/* SYSREG registers definition                  */
/************************************************/
typedef struct W5SysReg_s
{
    u32 u32_apbcfg ;   // 0x00
    u32 u32_ahbprio ;  // 0x04
    u32 u32_ahbcfg ;   // 0x08
    u32 u32_memcfg ;   // 0x0C
    u32 u32_lock_key ; // 0x10
    u32 u32_design_version ; // 0x14
    u32 u32_product_id ;     // 0x18
    u32 u32_chip_id0 ;       // 0x1C
    u32 u32_chip_id1 ;       // 0x20
} W5SysReg_t;

// SYSREG_APBCFG
#define APB0_RD_LATCH       (0x0001 << 0)  // when 1, the read pipe on the AHB2APB0 bridge is active and ine extra wait state is inserted for each read access
#define APB0_WR_BUFF        (0x0001 << 1)  // when 1, the write buffer on the AHB2APB0 is active and non-consecutive write accesses to this bridge are done without locking the CPU
#define APB1_RD_LATCH       (0x0001 << 2)  // when 1, the read pipe on the AHB2APB1 bridge is active and ine extra wait state is inserted for each read access
#define APB1_WR_BUFF        (0x0001 << 3)  // when 1, the write buffer on the AHB2APB1 is active and non-consecutive write accesses to this bridge are done without locking the CPU
#define APB2_RD_LATCH       (0x0001 << 4)  // when 1, the read pipe on the AHB2APB2 bridge is active and ine extra wait state is inserted for each read access
#define APB2_WR_BUFF        (0x0001 << 5)  // when 1, the write buffer on the AHB2APB2 is active and non-consecutive write accesses to this bridge are done without locking the CPU
#define APB3_RD_LATCH       (0x0001 << 6)  // when 1, the read pipe on the AHB2APB3 bridge is active and ine extra wait state is inserted for each read access
#define APB3_WR_BUFF        (0x0001 << 7)  // when 1, the write buffer on the AHB2APB3 is active and non-consecutive write accesses to this bridge are done without locking the CPU

// SYSREG_AHBPRIO
#define AHBPRIO_MASTER0     (0x0001 << 0)  // set the priority on the AHB multi-layer matrix for the master 0. the lowest value indicates the highest priority. only 2 different priority levels exist for all masters
#define AHBPRIO_MASTER1     (0x0001 << 1)  // set the priority on the AHB multi-layer matrix for the master 1. the lowest value indicates the highest priority. only 2 different priority levels exist for all masters
#define AHBPRIO_MASTER2     (0x0001 << 2)  // set the priority on the AHB multi-layer matrix for the master 2. the lowest value indicates the highest priority. only 2 different priority levels exist for all masters
#define AHBPRIO_MASTER3     (0x0001 << 3)  // set the priority on the AHB multi-layer matrix for the master 3. the lowest value indicates the highest priority. only 2 different priority levels exist for all masters
#define AHBPRIO_MASTER4     (0x0001 << 4)  // set the priority on the AHB multi-layer matrix for the master 4. the lowest value indicates the highest priority. only 2 different priority levels exist for all masters
#define AHBPRIO_MASTER5     (0x0001 << 5)  // set the priority on the AHB multi-layer matrix for the master 5. the lowest value indicates the highest priority. only 2 different priority levels exist for all masters

// SYSREG_AHBCFG
#define SLAVE0_RROBIN       (0x0001 << 0) // when 1 the round robin priority algorithm is active on the S0 slave port of the AHB multi-layer matrix
#define SLAVE1_RROBIN       (0x0001 << 1) // when 1 the round robin priority algorithm is active on the S1 slave port of the AHB multi-layer matrix
#define SLAVE2_RROBIN       (0x0001 << 2) // when 1 the round robin priority algorithm is active on the S2 slave port of the AHB multi-layer matrix
#define SLAVE3_RROBIN       (0x0001 << 3) // when 1 the round robin priority algorithm is active on the S3 slave port of the AHB multi-layer matrix
#define SLAVE4_RROBIN       (0x0001 << 4) // when 1 the round robin priority algorithm is active on the S4 slave port of the AHB multi-layer matrix
#define SLAVE5_RROBIN       (0x0001 << 5) // when 1 the round robin priority algorithm is active on the S5 slave port of the AHB multi-layer matrix
#define DEF_SLAVE_ERR       (0x0001 << 6) // 0: default slave never produces an eror response, 1: default slave indicates en erroneous request
#define IMI_HF              (0x0001 << 7) // when 1, the IMI is set in its high frequency mode and a wait state is inserted for each non sequenctial read access. No wia tstate is inserted for read sequential accesses

// SYSREG_MEMCFG
#define SYSREG_MEMCFG_BANK3_OFF 20
#define SYSREG_MEMCFG_BANK3_MSK (1<<SYSREG_MEMCFG_BANK3_OFF)
#define SYSREG_MEMCFG_BANK3_TO_CPU 1
#define SYSREG_MEMCFG_BANK3_TO_DSP 0

#define SYSREG_MEMCFG_BANK4_OFF 21
#define SYSREG_MEMCFG_BANK4_MSK (1<<SYSREG_MEMCFG_BANK4_OFF)
#define SYSREG_MEMCFG_BANK4_TO_CPU 1
#define SYSREG_MEMCFG_BANK4_TO_DSP 0

#define DSP_MEMMAP          (0x0001 << 0) // when 0 program ROM mapped @0000, when 1 program RAM mapped @0000
#define CPU_MEMMAP_POS      4
#define CPU_MEMMAP_MASK     (0x0007 << CPU_MEMMAP_POS)  // allows the remapping of one of the memory spaces to the common space, i.e. at the CPU @0000_0000
                                                        // when 000: none of the memory space is remapped to the common space
                                                        // when 001: internal RAM memory space is remapped to the common space
                                                        // when 010: external MEM1 memory space is remapped to the common space
                                                        // when 011: external MEM2 memory space is remapped to the common space
                                                        // when 100: external MEM3 memory space is remapped to the common space
                                                        // when 101: external SDRAM0 memory space is remapped to the common space (only the lower 64 MB of 128 MB is remapped)
                                                        // when 110: internal ROM memory space is remapped to the common space
                                                        // when 111: external MEM0 memory space is remapped to the common space

#define BOOT_CTRL_POS       8
#define BOOT_CTRL_MASK      (0x00FF << BOOT_CTRL_POS)       // represents the calues latched on the boot_ctrl# pins (GPIO[0], GPIO[9], GPIO[10]) during the rising edge of the hardware reset
                                                        // when 000: boot done in internal ROM memory space (boot ROM)
                                                        // when 001: boot done in external MEM0 memory space
                                                        // when 010: boot done in the DPRAM of the Nand Flash controller (8 bit, new generation NAND devices)
                                                        // when 011: boot done in the DPRAM of the Nand Flash controller (16 bit, new generation NAND devices)
                                                        // when 100: boot done in the DPRAM of the Nand Flash controller (8 bit, 4 address old generation NAND devices)
                                                        // when 101: boot done in the DPRAM of the Nand Flash controller (16 bit, 4 address old generation NAND devices)
                                                        // when 110: boot done in the DPRAM of the Nand Flash controller (8 bit, 5 address old generation NAND devices)
                                                        // when 111: boot done in the DPRAM of the Nand Flash controller (16 bit, 5 address old generation NAND devices)

#define VBR_DISABLE (0x0001 << 23) // When 1, the Virtual Rail mode of the IRAM is disabled. The virtual Rail mode allows dividing by 2 the leakage current of the IRAM chen the device is in sleep mode.


/************************************************/
/* CMU clock management unit                    */
/************************************************/
#ifdef __B1__
typedef struct W5Cmu_s
{
    u32 fixPll;             // 0x00
    u32 cpuPll;             // 0x04
    u32 dspPll;             // 0x08
    u32 auxSysCtrl;         // 0x0C
    u32 auxSysCfg;          // 0x10
    u32 fixSysCtrl;         // 0x14
    u32 fixSysCfg;          // 0x18
    u32 cpuSysCtrl;         // 0x1C
    u32 cpuClkCfg;          // 0x20
    u32 dspSysCtrl;         // 0x24
    u32 dspSysCfg;          // 0x28
    u32 rtcSysCtrl;         // 0x2C
    u32 cpuSysCfg;          // 0x30
    u32 cpuPeriphCfg;       // 0x34
    u32 cpuPeriphPwd;       // 0x38
    u32 cpuPeriphRst;       // 0x3C
    u32 cpuPeriphSmWait;    // 0x40
    u32 gssPwd;             // 0x44
    u32 gssRst;             // 0x48
    u32 gssSmWait;          // 0x4C
    u32 rfctrlPwd;          // 0x50
    u32 rfctrlRst;          // 0x54
    u32 rfctrlSmWait;       // 0x58
    u32 shifacePwd;         // 0x5C
    u32 shifaceRst;         // 0x60
    u32 shifaceSmWait;      // 0x64
    u32 cmuIrqMask;         // 0x68
    u32 cmuIrqStatus;       // 0x6C
    u32 cmuIrqClear;        // 0x70
    u32 cmuIrqRawStatus;    // 0x74
} W5Cmu_t;
#endif //__B1__

typedef struct OSim_s {
  u32           Control;
  u32           IrqMask;
  u32           Status;
  u32           StatusClear;
  u32           RawStatus;
  u32           RxTx;
  u32           TxCounter;
  u32           RxCounter;
  u32           DmaCounter;
  u32           WaitingTime;
  u32           EtuClockSpeed;
  u32           XWI;
  u32           NAD;
  u32           PCB;
  u32           EGT;
  u32           BWTRE;
  u32           TPWR;
  u32           TA;
  u32           TB;
  u32           TC1;
  u32           TC2;
} OSim_t;

#ifdef __B1__
// XXX_PLL register
#define PLL_REFAIL                  (0x0001<<0) // Pll has no clock signal input
#define TEST_ISON                   (0x0001<<1) // Pll is under test mode
#define PLL_RST                     (0x0001<<2) // reset
#define PLL_PWD                     (0x0001<<3) // power down
#define PLL_BYPASS                  (0x0001<<4) // PLL bypass
#define M_INPUT_DIV_FACTOR_POS      5 // input divider factor
#define M_INPUT_DIV_FACTOR_MASK     (0x000F<<M_INPUT_DIV_FACTOR_POS)
#define M_INPUT_DIV_FACTOR_13MO     0 // M value when internal clock is 13Mhz
#define M_INPUT_DIV_FACTOR_26MO     1 // M value when internal clock is 26Mhz
#define N_FDBACK_DIV_FACTOR_POS     9 // feedback divider factor
#define N_FDBACK_DIV_FACTOR_MASK    (0x003F<<N_FDBACK_DIV_FACTOR_POS)
#define N_FDBACK_DIV_FACTOR_52      1  // N value permitting to set a core clock to 26 MHz
#define N_FDBACK_DIV_FACTOR_208     7  // N value permitting to set a core clock to 208 MHz
#define N_FDBACK_DIV_FACTOR_234	    8  // N value permitting to set a core clock to 234 MHz
#define N_FDBACK_DIV_FACTOR_260     9  // N value permitting to set a core clock to 260 MHz
#define N_FDBACK_DIV_FACTOR_312     11 // N value permitting to set a core clock to 312 MHz
#define N_FDBACK_DIV_FACTOR_364     13 // N value permitting to set a core clock to 364 MHz
#define N_FDBACK_DIV_FACTOR_416     15 // N value permitting to set a core clock to 416 MHz
#define PHS_PWD                     (0x0001<<15) // phase shifter power down
#define PHS_BYPASS                  (0x0001<<16) // pahse shifter bypass
#define PHS_LOFREQ                  (0x0001<<17) // set to 1 if input clock is less than 300 Mhz
#define PHS_X_POS                   18 // phase shifter X coefficient
#define PHS_X_MASK                  (0x0007<<PHS_X_POS)
#define PHS_Y_POS                   21 // phase shifter Y coefficient
#define PHS_Y_MASK                  (0x000F<<PHS_Y_POS)
#define CSH_PWD                     (0x0001<<26) // clock shaper power down
#define CSH_BYPASS                  (0x0001<<27) // clock shaper bypass
#define CSH_INV                     (0x0001<<28) // clock shaper inverter

// AUX_SYS_CTRL register
#define AUX_INT_CLK_ON              (0x0001<<0)
#define AUX_INT_CLK_DIV_POS         1
#define AUX_INT_CLK_DIV_MASK        (0x0003<<AUX_INT_CLK_DIV_POS)

// AUX_SYS_CFG register
#define UART1_CLK_DIV_POS           0
#define UART1_CLK_DIV_MASK          (0x0003<<UART1_CLK_DIV_POS)
#define UART1_CKL_DIV_1_8432        0
#define UART1_CKL_DIV_14_7456       1
#define UART1_CKL_DIV_18_4320       2
#define UART2_CLK_DIV_POS           2
#define UART2_CLK_DIV_MASK          (0x0003<<UART2_CLK_DIV_POS)
#define UART2_CKL_DIV_1_8432        0
#define UART2_CKL_DIV_14_7456       1
#define UART2_CKL_DIV_18_4320       2


// FIX_SYS_CTRL register
#define FIX_INT_CLK_ON              (0x0001<<0)
#define FIX_INT_CLK_DIV_POS         1
#define FIX_INT_CLK_DIV_MASK        (0x0003<<FIX_INT_CLK_DIV_POS)

// FIX_SYS_CFG register
#define MMC_SAMPLE_DELAY_POS        0
#define MMC_SAMPLE_DELAY_MASK       (0x0003<<MMC_SAMPLE_DELAY_POS)
#define MMC_HOLD_DELAY_POS          2
#define MMC_HOLD_DELAY_MASK         (0x0003<<MMC_HOLD_DELAY_POS)
#define MMC_CLK_DIV_POS             4
#define MMC_CLK_DIV_MASK            (0x0007<<MMC_CLK_DIV_POS)

// CPU_SYS_CTRL register
#define CPU_INT_CLK_ON              (0x0001<<0)
#define CPU_INT_CLK_SEL_POS         1
#define CPU_INT_CLK_SEL_MASK		(0x0003<<CPU_INT_CLK_SEL_POS)
#define CPU_INT_CLK_SEL_CPU         0
#define CPU_INT_CLK_SEL_DSP         1
#define CPU_INT_CLK_SEL_FIX         2
#define CPU_INT_CLK_SEL_CLK_32K     3
#define CPU_INT_CLK_DIV_POS         4
#define CPU_INT_CLK_DIV_MASK        (0x0003<<CPU_INT_CLK_DIV_POS)
#define CPU_INT_CLK_DIV_1           0
#define CPU_INT_CLK_DIV_2           1
#define CPU_INT_CLK_DIV_4           2
#define CPU_INT_CLK_DIV_8           3
#define SYS_CLK_UPDATE              (0x0001<<6)

// CPU_CLK_CFG
#define APB0_CLK_DIV_POS            0
#define APB0_CLK_DIV_MASK           (0x000F<<APB0_CLK_DIV_POS)
#define APB1_CLK_DIV_POS            4
#define APB1_CLK_DIV_MASK           (0x000F<<APB1_CLK_DIV_POS)
#define APB2_CLK_DIV_POS            8
#define APB2_CLK_DIV_MASK           (0x000F<<APB2_CLK_DIV_POS)
#define APB3_CLK_DIV_POS            12
#define APB3_CLK_DIV_MASK           (0x000F<<APB3_CLK_DIV_POS)
#define AHB_CLK_DIV_POS             16
#define AHB_CLK_DIV_MASK            (0x000F<<AHB_CLK_DIV_POS)
#define BUS_CLK_DIV_1               0
#define BUS_CLK_DIV_2               1
#define BUS_CLK_DIV_3               2
#define BUS_CLK_DIV_4               3
#define BUS_CLK_DIV_5               4
#define BUS_CLK_DIV_6               5
#define BUS_CLK_DIV_7               6
#define BUS_CLK_DIV_8               7
#define BUS_CLK_DIV_9               8
#define BUS_CLK_DIV_10              9
#define BUS_CLK_DIV_11             10
#define BUS_CLK_DIV_12             11
#define BUS_CLK_DIV_13             12
#define BUS_CLK_DIV_14             13
#define BUS_CLK_DIV_15             14
#define BUS_CLK_DIV_16             15
#define CLK_26M_DIV_POS             20
#define CLK_26M_DIV_MASK            (0x000F<<CLK_26M_DIV_POS)
#define CPU_CLK_DIV_POS             24
#define CPU_CLK_DIV_MASK            (0x001F<<CPU_CLK_DIV_POS)
#define CPU_CLK_DIV_1               0
#define CPU_CLK_DIV_2               1
#define CPU_CLK_DIV_3               2
#define CPU_CLK_DIV_4               3
#define CPU_CLK_DIV_5               4
#define CPU_CLK_DIV_6               5
#define CPU_CLK_DIV_7               6
#define CPU_CLK_DIV_8               7
#define CPU_CLK_DIV_9               8
#define CPU_CLK_DIV_10              9
#define CPU_CLK_DIV_11             10
#define CPU_CLK_DIV_12             11
#define CPU_CLK_DIV_13             12
#define CPU_CLK_DIV_14             13
#define CPU_CLK_DIV_15             14
#define CPU_CLK_DIV_16             15
#define CPU_CLK_DIV_17             16
#define CPU_CLK_DIV_18             17
#define CPU_CLK_DIV_19             18
#define CPU_CLK_DIV_20             19
#define CPU_CLK_DIV_21             20
#define CPU_CLK_DIV_22             21
#define CPU_CLK_DIV_23             22
#define CPU_CLK_DIV_24             23
#define CPU_CLK_DIV_25             24
#define CPU_CLK_DIV_26             25
#define CPU_CLK_DIV_27             26
#define CPU_CLK_DIV_28             27
#define CPU_CLK_DIV_29             28
#define CPU_CLK_DIV_30             29
#define CPU_CLK_DIV_31             30
#define CPU_CLK_DIV_32             31


// DSP_SYS_CTRL
#define DSP_INT_CLK_ON              (0x0001<<0)
#define DSP_INT_CLK_SEL_POS         1
#define DSP_INT_CLK_SEL_MASK        (0x0003<<DSP_INT_CLK_SEL_POS)
#define DSP_INT_CLK_SEL_CPU         0
#define DSP_INT_CLK_SEL_DSP         1
#define DSP_INT_CLK_SEL_FIX         2
#define DSP_INT_CLK_SEL_CLK_32K     3
#define DSP_INT_CLK_DIV_POS         4
#define DSP_INT_CLK_DIV_MASK        (0x0003<<DSP_INT_CLK_DIV_POS)
#define DSP_INT_CLK_DIV_1           0
#define DSP_INT_CLK_DIV_2           1
#define DSP_INT_CLK_DIV_4           2
#define DSP_INT_CLK_DIV_8           3

// DSP_SYS_CFG
#define EDGE_CLK_DIV_POS            0
#define EDGE_CLK_DIV_MASK           (0x0003<<EDGE_CLK_DIV_POS)

// RTC_SYS_CTRL
#define RTC_INT_CLK_ON_MSK			(0x0001<<0)
#define RTC_INT_CLK_ON_32K_EXT	(0x0000<<0)
#define RTC_INT_CLK_ON_32K_INT		(0x0001<<0)
#define RTC_INT_CLK_DIV             (0x0001<<1)

// CPU_SYS_CFG
#define BOOT_FREQ                   (0x0001<<0) // when 1, the external oscillator frequency is 26Mhz otherwise 113 Mhz
#define VCXO_PWD                    (0x0001<<1) // when 1, the external 13/26 Mhz oscillator is switched off in sleep mode
#define WD_PERIPH_EN                (0x0001<<2) // watchdog out enabled
#define DSP_DBG_EN                  (0x0001<<3) // when 1, the DSP jtag is enabled
#define CPU_PERIPH_AUTO_PWD         (0x0001<<4)
#define GSS_AUTO_PWD                (0x0001<<5)
#define RF_AUTO_PWD                 (0x0001<<6)
#define SHIFACE_AUTO_PWD            (0x0001<<7)
#define DSP_PERIPH_AUTO_PWD         (0x0001<<8)
#define CPU_DBG_EN                  (0x0001<<9) // when 1, the CPU jtag is enabled
#define SM_WAIT_CPU_PWD             (0x0001<<11) // when 1, system clocks are only switched off in sleep mode if all selected devices are in power_down mode
#define ETM_TRACE_CLK_DEL_POS       12
#define ETM_TRACE_CLK_DEL_MASK      (0x0003<<ETM_TRACE_CLK_DEL_POS)
#define CHIP_DBG_EN                 (0x0001<<14) // when 1, the chip debug mode is enabled
#define CPU_DSP_RST                 (0x0001<<15) // when 1, a reset is applied on the DSP sub-system
#define CPU_DSP_PWD                 (0x0001<<16) // when 1, all DSP sub-system clocks are switched off

// CPU_PERIPH_CFG
#define I2C_CLK_DIV_POS             0
#define I2C_CLK_DIV_MASK            (0x000F<<I2C_CLK_DIV_POS)
#define NAND_CLK_DIV_POS            4
#define NAND_CLK_DIV_MASK           (0x0003<<NAND_CLK_DIV_POS)

// CPU_PERIPH_PWD
#define EXICE_PWD                   (0x0001<<0)
#define IMI_PWD                     (0x0001<<1)
#define AHB_ML_PWD                  (0x0001<<2)
#define AHB2APB1_PWD                (0x0001<<3)
#define AHB2APB2_PWD                (0x0001<<4)
#define AHB2APB3_PWD                (0x0001<<5)
#define DMA_PWD                     (0x0001<<6)
#define ITCTRL_PWD                  (0x0001<<7)
#define EXT_ITCTRL_PWD              (0x0001<<8)
#define FCS_PWD                     (0x0001<<9)
#define GEA_PWD                     (0x0001<<10)
#define GEA2_PWD                    (0x0001<<11)
#define UART1_PWD                   (0x0001<<12)
#define UART2_PWD                   (0x0001<<13)
#define SPI1_PWD                    (0x0001<<14)
#define SPI2_PWD                    (0x0001<<15)
#define SPI3_PWD                    (0x0001<<16)
#define SIM1_PWD                    (0x0001<<17)
#define SIM2_PWD                    (0x0001<<18)
#define PWM_PWD                     (0x0001<<19)
#define I2C_PWD                     (0x0001<<21)
#define SYSTIMER_PWD                (0x0001<<22)
#define EMI_PWD                     (0x0001<<23)
#define EMI_ARBITER_PWD             (0x0001<<24)
#define SDRAM_PWD                   (0x0001<<25)
#define NANDFLASH_PWD               (0x0001<<26)
#define AUDIO_PWD                   (0x0001<<27)
#define RTC_PWD                     (0x0001<<28) // when 1, switch off the CPU I/F clocks of the RTC but not the RTC itself
#define SDMMC_PWD                   (0x0001<<29)
#define USB_PWD                     (0x0001<<30)

// CPU_PERIPH_RST
#define EXICE_RST                   (0x0001<<0)
#define CPU_DSMA_RST                (0x0001<<6)
#define ITCTRL_RST                  (0x0001<<7)
#define EXT_ITCTRL_RST              (0x0001<<8)
#define FCS_RST                     (0x0001<<9)
#define GEA_RST                     (0x0001<<10)
#define GEA2_RST                    (0x0001<<11)
#define UART1_RST                   (0x0001<<12)
#define UART2_RST                   (0x0001<<13)
#define SPI1_RST                    (0x0001<<14)
#define SPI2_RST                    (0x0001<<15)
#define SPI3_RST                    (0x0001<<16)
#define SIM1_RST                    (0x0001<<17)
#define SIM2_RST                    (0x0001<<18)
#define PWM_RST                     (0x0001<<19)
#define I2C_RST                     (0x0001<<21)
#define SYSTIMER_RST                (0x0001<<22)
#define EMI_RST                     (0x0001<<23)
#define EMI_ARBITER_RST             (0x0001<<24)
#define SDRAM_RST                   (0x0001<<25)
#define NANDFLASH_RST               (0x0001<<26)
#define AUDIO_RST                   (0x0001<<27)
#define SDMMC_RST                   (0x0001<<29)
#define USB_RST                     (0x0001<<30)

// CPU_PERIPH_SM_WAIT
#define SM_WAIT_EXICE_PWD           (0x0001<<0)
#define SM_WAIT_IMI_PWD             (0x0001<<1)
#define SM_WAIT_AHB_ML_PWD          (0x0001<<2)
#define SM_WAIT_AHB2APB1_PWD        (0x0001<<3)
#define SM_WAIT_AHB2APB2_PWD        (0x0001<<4)
#define SM_WAIT_AHB2APB3_PWD        (0x0001<<5)
#define SM_WAIT_DMA_PWD             (0x0001<<6)
#define SM_WAIT_ITCTRL_PWD          (0x0001<<7)
#define SM_WAIT_EXT_ITCTRL_PWD      (0x0001<<8)
#define SM_WAIT_FCS_PWD             (0x0001<<9)
#define SM_WAIT_GEA_PWD             (0x0001<<10)
#define SM_WAIT_GEA2_PWD            (0x0001<<11)
#define SM_WAIT_UART1_PWD           (0x0001<<12)
#define SM_WAIT_UART2_PWD           (0x0001<<13)
#define SM_WAIT_SPI1_PWD            (0x0001<<14)
#define SM_WAIT_SPI2_PWD            (0x0001<<15)
#define SM_WAIT_SPI3_PWD            (0x0001<<16)
#define SM_WAIT_SIM1_PWD            (0x0001<<17)
#define SM_WAIT_SIM2_PWD            (0x0001<<18)
#define SM_WAIT_PWM_PWD             (0x0001<<19)
#define SM_WAIT_I2C_PWD             (0x0001<<21)
#define SM_WAIT_SYSTIMER_PWD        (0x0001<<22)
#define SM_WAIT_EMI_PWD             (0x0001<<23)
#define SM_WAIT_EMI_ARBITRER_PWD    (0x0001<<24)
#define SM_WAIT_SDRAM_PWD           (0x0001<<25)
#define SM_WAIT_NANDFLASH_PWD       (0x0001<<26)
#define SM_WAIT_AUDIO_PWD           (0x0001<<27)
#define SM_WAIT_RTC_PWD             (0x0001<<28) // only for the cpu I/F clocks of the RTC
#define SM_WAIT_SDMMC_PWD           (0x0001<<29)
#define SM_WAIT_USB_PWD             (0x0001<<30)

// GSS_PWD
#define GSS_PWD                     (0x0001<<0)
#define TWODGP_PWD                  (0x0001<<1)
#define CISI_PWD                    (0x0001<<2)
#define JPEG_PWD                    (0x0001<<3)
#define LCDC_PWD                    (0x0001<<4)

// GSS_RST
#define GSS_RST                     (0x0001<<0)
#define TWODGP_RST                  (0x0001<<1)
#define CISI_RST                    (0x0001<<2)
#define JPEG_RST                    (0x0001<<3)
#define LCDC_RST                    (0x0001<<4)

// GSS_SM_WAIT
#define SM_WAIT_GSS_PWD             (0x0001<<0)
#define SM_WAIT_2DGP_PWD            (0x0001<<1)
#define SM_WAIT_CISI_PWD            (0x0001<<2)
#define SM_WAIT_JPEG_PWD            (0x0001<<3)
#define SM_WAIT_LCDC_PWD            (0x0001<<4)

// RFCTRL_PWD
#define TBU_PWD                     (0x0001<<0)
#define RXPORT_PWD                  (0x0001<<1)
#define TXPORT_PWD                  (0x0001<<2)
#define AGC_PWD                     (0x0001<<3)
#define RFDL_PWD                    (0x0001<<4)
#define RFDL_P2S0_PWD               (0x0001<<5)
#define RFDL_P2S1_PWD               (0x0001<<6)

// RFCTRL_RST
#define TBU_RST                     (0x0001<<0)
#define RXPORT_RST                  (0x0001<<1)
#define TXPORT_RST                  (0x0001<<2)
#define AGC_RST                     (0x0001<<3)
#define RFDL_RST                    (0x0001<<4)
#define RFDL_P2S0_RST               (0x0001<<5)
#define RFDL_P2S1_RST               (0x0001<<6)

// RFCTRL_SM_WAIT
#define SM_WAIT_TBU_PWD            (0x0001<<0)
#define SM_WAIT_RXPORT_PWD         (0x0001<<1)
#define SM_WAIT_TXPORT_PWD         (0x0001<<2)
#define SM_WAIT_AGC_PWD            (0x0001<<3)
#define SM_WAIT_RFDL_PWD           (0x0001<<4)
#define SM_WAIT_RFDL_P2S0_PWD      (0x0001<<5)
#define SM_WAIT_RFDL_P2S1_PWD      (0x0001<<6)

// SHIFACE_PWD
#define SHIFACE_SHARE_REG_PWD      (0x0001<<0)
#define SHIFACE_DSMA_PWD           (0x0001<<1)
#define SHIFACE_FRAME_CNT_PWD      (0x0001<<2)
#define SHIFACE_DSP_PWD            (0x0001<<4)

// SHIFACE_RST
#define SHIFACE_SHARE_REG_RST      (0x0001<<0)
#define SHIFACE_DSMA_RST           (0x0001<<1)
#define SHIFACE_FRAME_CNT_RST      (0x0001<<2)
#define SHIFACE_DSP_RST            (0x0001<<4)

// SHIFACE_SM_WAIT
#define SM_WAIT_SHARE_REG_PWD      (0x0001<<0)
#define SM_WAIT_DSMA_PWD           (0x0001<<1)
#define SM_WAIT_FRAME_CNT_PWD      (0x0001<<2)
#define SM_WAIT_DSP_PWD            (0x0001<<4)

// CMU_IRQ_XXX
#define FIX_PLL_LOCK               (0x0001<<0)
#define CPU_PLL_LOCK               (0x0001<<1)
#define DSP_PLL_LOCK               (0x0001<<2)
#define FIX_PLL_UNLOCK             (0x0001<<3)
#define CPU_PLL_UNLOCK             (0x0001<<4)
#define DSP_PLL_UNLOCK             (0x0001<<5)
#endif //__B1__

/************************************************/
/* PROBE    FOR DEBUG PIN TEST                                                            	*/
/************************************************/
typedef struct W5Probe_s
{
	u8   u8_Activation_Add; 	 			// 0x00
	u8   u8_Unused1;                                   // 0x01
	u16 u16_Unused2;                                 // 0x02
	u16 u16_Shift_Number_Add;                // 0x04
	u16 u16_Unused3;                                // 0x06
	u8   u8_Shift_Control_Add;                  // 0x08
	u8   u8_Unused4;                                 // 0x09
	u16 u16_Unused5;                               // 0x0A
	u32 u32_Shift_Reg_Add;                    // 0x0C

} W5Probe_t;

/************************************************/
/* DMA controller                               	*/
/************************************************/

typedef struct W5Dmac_s
{
	u32 u32_DMAH_SAR_l; 	 			// 0x00
	u32 u32_DMAH_SAR_h; 	 			// 0x04
	u32 u32_DMAH_DAR_l; 	 			// 0x08
	u32 u32_DMAH_DAR_h; 	 			// 0x0C
	u32 u32_DMAH_LLP_l; 	 			// 0x10
	u32 u32_DMAH_LLP_h; 	 			// 0x14
	u32 u32_DMAH_CTL_l; 	 			// 0x18
	u32 u32_DMAH_CTL_h; 	 			// 0x1C
	u32 u32_DMAH_SSTAT_l; 	 			// 0x20
	u32 u32_DMAH_SSTAT_h; 	 		// 0x24
	u32 u32_DMAH_DSTAT_l; 	 			// 0x28
	u32 u32_DMAH_DSTAT_h; 	 		// 0x2C
	u32 u32_DMAH_SSTATAR; 	 		// 0x30
	u32 u32_DMAH_SSTATAR_h; 	 		// 0x34
	u32 u32_DMAH_DSTATAR_l; 	 		// 0x38
	u32 u32_DMAH_DSTATAR_h; 	 		// 0x3C
	u32 u32_DMAH_CFG_l; 	 			// 0x40
	u32 u32_DMAH_CFG_h; 	 			// 0x44
	u32 u32_DMAH_SGR_l; 	 			// 0x48
	u32 u32_DMAH_SGR_h; 	 			// 0x4C
	u32 u32_DMAH_DSR_l; 	 			// 0x50
	u32 u32_DMAH_DSR_h; 	 			// 0x54
}  W5Dmac_t ;

/************************************************/
/* Dma                     */
/************************************************/
#define DW_dmac_DMAH_CH0_START_ADDR              (DMAC_CFG_START_ADDRESS + 0x000)
#define DW_dmac_DMAH_CH1_START_ADDR              (DMAC_CFG_START_ADDRESS + 0x058)
#define DW_dmac_DMAH_CH2_START_ADDR              (DMAC_CFG_START_ADDRESS + 0x0b0)
#define DW_dmac_DMAH_CH3_START_ADDR              (DMAC_CFG_START_ADDRESS + 0x108)
#define DW_dmac_DMAH_CH4_START_ADDR              (DMAC_CFG_START_ADDRESS + 0x160)
#define DW_dmac_DMAH_CH5_START_ADDR              (DMAC_CFG_START_ADDRESS + 0x1b8)
#define DW_dmac_DMAH_CH6_START_ADDR              (DMAC_CFG_START_ADDRESS + 0x210)
#define DW_dmac_DMAH_CH7_START_ADDR              (DMAC_CFG_START_ADDRESS + 0x268)
#define DW_dmac_DMAH_COMMON_START_ADDR           (DMAC_CFG_START_ADDRESS + 0x2c0)

typedef struct W5Dma_s
{
	u32 p_sar;
	u32 unused1;
	u32 p_dar;
	u32 unused2;
	u32 p_llp;
	u32 unused3;
	u32 p_ctll;
	u32 p_ctlh;
	u32 p_sstat;
	u32 unused5;
	u32 p_dstat;
	u32 unused6;
	u32 p_sstatar;
	u32 unused7;
	u32 p_dstatar;
	u32 unused8;
	u32 p_cfgl;
	u32 p_cfgh;
	u32 p_sgr;
	u32 unused10;
	u32 p_dsr;
 } W5Dma_t;



typedef struct W5DmaCfg_s
{
	u32 p_rawftr;
	u32 unused1;
	u32 p_rawblock;
	u32 unused2;
	u32 p_rawsrctran;
	u32 unused3;
	u32 p_rawdsttran;
	u32 unused4;
	u32 p_rawerr;
	u32 unused5;
	u32 p_statustfr;
	u32 unused6;
	u32 p_statusblock;
	u32 unused7;
	u32 p_statussrctran;
	u32 unused8;
	u32 p_statusdsttran;
	u32 unused9;
	u32 p_statuserr;
	u32 unused10;
	u32 p_masktfr;
	u32 unused101;
	u32 p_maskblock;
	u32 unused102;
	u32 p_masksrctran;
	u32 unused103;
	u32 p_maskdsttran;
	u32 unused104;
	u32 p_maskerr;
	u32 unused105;
	u32 p_cleartfr;
	u32 unused11;
	u32 p_clearblock;
	u32 unused12;
	u32 p_clearsrctran;
	u32 unused13;
	u32 p_cleardsttran;
	u32 unused14;
	u32 p_clearerr;
	u32 unused15;
	u32 p_statusint;
	u32 unused16;
	u32 p_reqsrcreg;
	u32 unused17;
	u32 p_reqdstreg;
	u32 unused18;
	u32 p_sglrqsrcreg;
	u32 unused19;
	u32 p_sglrqdstreg;
	u32 unused20;
	u32 p_lstsrcreg;
	u32 unused21;
	u32 p_lstdstreg;
	u32 unused22;
	u32 p_dmacfgreg;
	u32 unused23;
	u32 p_chenreg;
	u32 unused24;
	u32 p_dmaidreg;
	u32 unused25;
	u32 p_dmatestreg;
	u32 unused26;
	u32 p_dmaversionid;
	u32 unused27;
 } W5DmaCfg_t;


/************************************************/
/* EBI: External Bus Interface                 	*/
/************************************************/

/*** EBI_GLOBAL_CFG register ***/
typedef struct EBI_GLOBAL_CFG {
    u32 cs0_cfg     : 4 ; //Chip select 0 configuration
    u32 cs1_cfg     : 4 ; //Chip select 1 configuration
    u32 cs2_cfg     : 4 ; //Chip select 2 configuration
    u32 cs3_cfg     : 4 ; //Chip select 3 configuration
    u32 dout_mode   : 2 ; //Data bus driving mode
    u32 ta          : 1 ; //Transfer Activity. Reflects if the EBI is doing read or write operation.
    u32             : 13 ; // reserved
} EbiGlobalCfg_t;

#define EBI_GLOBAL_CFG_USE_CF0 0x1 // CSn uses EBI_MAIN_CFG0, EBI_WR_CFG0 and EBI_RD_CFG0
#define EBI_GLOBAL_CFG_USE_CF1 0x2 // CSn uses EBI_MAIN_CFG1, EBI_WR_CFG1 and EBI_RD_CFG1
#define EBI_GLOBAL_CFG_USE_CF2 0x4 // CSn uses EBI_MAIN_CFG2, EBI_WR_CFG2 and EBI_RD_CFG2
#define EBI_GLOBAL_CFG_USE_CF3 0x8 // CSn uses EBI_MAIN_CFG3, EBI_WR_CFG3 and EBI_RD_CFG3

#define EBI_GLOBAL_CFG_DOUT_DRIVEN_WR               0x0 // data bus is driven only during write access
#define EBI_GLOBAL_CFG_DOUT_DRIVEN_WR_IDLE          0x1 // data bus is driven during write access and idle
#define EBI_GLOBAL_CFG_DOUT_DRIVEN_RW_8_BITS        0x2 // data bus is driven during write access and during read access for the unused 8-bit data (only with 8-bit device)
#define EBI_GLOBAL_CFG_DOUT_DRIVEN_RW_IDLE_8_BITS   0x3 // data bus is driven during write access, idle and during read access for the unused 8-bit data (only with 8-bit device)

#define EBI_GLOBAL_CFG_TA_NO_ACTIVITY 0 //No read or write activity
#define EBI_GLOBAL_CFG_TA_RW_ACTIVITY 1 // In read or write activity

/*** EBI_MAIN_CFGn register ***/
typedef struct EBI_MAIN_CFG {
    u32 opmode          : 1 ; // operating mode for configuration n
    u32 epol            : 1 ; // Enable signal polarity for the 68XX mode (i.e. when MODE = 0)
    u32 dataBusSize     : 2 ; // Device data bus size connected to the EBI
    u32                 : 4 ; // Reserved
    u32 addVal          : 8 ;   // Address Value. Define the value of the 8 LSB of
                                // the address bus (EBI_A) when ADDMODE=1. The other MSB
                                // of the address bus are set to 0.
    u32 dispFormat      : 4 ; // Display Formatter (when ? 0000, ADDMODE must be set to 1)
    u32 waitPol         : 1 ; // Wait signal polarity
    u32 waitEn          : 1 ; // Enables the WAIT function which allows peripheral to extend access time
    u32 waitPull        : 2 ; // Enables or disables pull resistor on the WAIT input
    u32 waitStatus      : 1 ; // Indicates the current value at the WAIT input pad
    u32                 : 6 ; // Reserved
} EbiMainCfg_t;

#define EBI_MAIN_CFG_OPMODE_I80 0 // I80XX mode
#define EBI_MAIN_CFG_OPMODE_M68 1 //  M68XX mode

#define EBI_MAIN_CFG_EPOL_ACT_LOW   0 // Enable is active low
#define EBI_MAIN_CFG_EPOL_ACT_HIGH  1 // Enable is active high

#define EBI_MAIN_CFG_DSZ_8BITS_LSB  0x0 // 8-bit device mapped on EBI_D[7:0]
#define EBI_MAIN_CFG_DSZ_8BITS_MSB  0x1 //: 8-bit device mapped on EBI_D[15:8]
#define EBI_MAIN_CFG_DSZ_16BITS     0x2 //: 16-bit device

#define EBI_MAIN_CFG_ADDMODE_AHB    0 // EBI address (EBI_A) is AHB address
#define EBI_MAIN_CFG_ADDMODE_ADDVAL 1 // EBI address is set by the ADDVAL configuration field

#define EBI_MAIN_CFG_DISPFORMAT_DISABLED   0x0  // Display formatter disabled
                                                // RGB565 to RGB565, 16-bit data/cycle, 1 cycles/pixel
                                                // RGB332 to RBG332, 8-bit data/cycle, 1 cycles/pixel
#define EBI_MAIN_CFG_DISPFORMAT_1   0x1 // RGB565 to RGB565, 8-bit data/cycle, 2 cycles/pixel
#define EBI_MAIN_CFG_DISPFORMAT_2   0x2 //: RGB565 to RGB666, 6-bit data/cycle, Right aligned, 3 cycles/pixel
#define EBI_MAIN_CFG_DISPFORMAT_3   0x3 //: RGB565 to RGB666, 6-bit data/cycle, Left aligned, 3 cycles/pixel
#define EBI_MAIN_CFG_DISPFORMAT_4   0x4 // RGB565 to RGB666, 12-bit data/cycle, 1.5 cycles/pixel
#define EBI_MAIN_CFG_DISPFORMAT_5   0x5 // RGB565 to RGB666, 12-bit data/cycle, 1.5 cycles/pixel
#define EBI_MAIN_CFG_DISPFORMAT_6   0x6 // RGB565 to RGB666, 9-bit data/cycle, 2 cycles/pixel
#define EBI_MAIN_CFG_DISPFORMAT_7   0x7 // RGB565 to RGB444, 8-bit data/cycle, 1.5 cycles/pixel
#define EBI_MAIN_CFG_DISPFORMAT_8   0x8 // RGB565 to RGB444, 12-bit data/cycle, 1 cycles/pixel

#define EBI_MAIN_CFG_WAITPOL_ACT_LOW    0 // Wait is active low
#define EBI_MAIN_CFG_WAITPOL_ACT_HIGH   1 // Wait is active high

#define EBI_MAIN_CFG_WAITEN_INACTIVE    0 // Wait function is inactive
#define EBI_MAIN_CFG_WAITEN_ACTIVE      1 // Wait function is active

#define EBI_MAIN_CFG_WAITPULL_NO_PULL   0 // No pull resistor
#define EBI_MAIN_CFG_WAITPULL_PULL_UP   1 // Pull-up resistor
#define EBI_MAIN_CFG_WAITPULL_PULL_DWN  2 // Pull-down resistor

#define EBI_MAIN_CFG_WAITSTATUS_LEVEL_LOW   0 // Wait input pad is currently at logic level 0
#define EBI_MAIN_CFG_WAITSTATUS_LEVEL_HIGH  1 // Wait input pad is currently at logic level 1

/*** EBI_WR_CFGn register ***/
typedef struct EBI_WR_CFG {
    u32 sawr          : 2 ; // Setup time for address bus during write access. Define the number of hclk cycles between the output of the address and the chip-select (CSN) falling edge. Minimum value is 0 hclk cycle.
                            // 00: 0 hclk cycle
                            // 11: 3 hclk cycles
    u32 sdwr          : 4 ; // Setup time for data bus during write access. Define the number of hclk cycles between the assertion of the chip-select (CSN) and the assertion of the write/enable signal (WN/E). Minimum value is 0 hclk cycle.
                            // 0000: 0 hclk cycle
                            // 1111: 15 hclk cycles
    u32 wdwr          : 6 ; // Wait states for data bus during write access. Define the number of hclk cycles when the write/enable signal is kept active. Minimum value is 1 hclk cycle.
                            // 000000: 1 hclk cycle
                            // 111111: 64 hclk cyles
    u32 hdwr          : 4 ; // Hold time for data bus during write access. Define the number of hclk cycles between the deassertion of the write/enable (WN/E) signal and the chip-select rising edge (CSN). Minimum value is 0 hclk cycle.
                            // 0000: 0 hclk cycle
                            // 1111: 15 hclk cycles
    u32 hawr          : 2 ; // Hold time for address bus during write access. Define the number of hclk cycles between the deassertion of the chip-select (CSN) and the end of the address/data valid time. Minimum value is 0 hclk cycle.
                            // 00: 0 hclk cycle
                            // 11: 3 hclk cycles
    u32 wr2wr         : 4 ; // Write to Write delay. Define the number of inactive cycles between two consecutive write accesses on the same chip-select. Minimum value is 0 hclk cycle.
                            // 0000: 0 hclk cycle
                            // 1111: 15 hclk cycles
    u32 btawr         : 4 ; // Bus Turnaround Time for write access. Define the number of inactive cycles between any accesses except consecutive write accesses on the same chip-select. Minimum value is 1 hclk cycle.
                            // 0000: 1 hclk cycle
                            // 1111: 16 hclk cyles
    u32               : 6 ; // Reserved
} EbiWrCfg_t;

/*** EBI_RD_CFGn register ***/
typedef struct EBI_RD_CFG {
    u32 sard          : 2 ; // Setup time for address bus during read access. Define the number of hclk cycles between the output of the address and the chip-select (CSN) falling edge. Minimum value is 0 hclk cycle.
                            // 00: 0 hclk cycle
                            // 11: 3 hclk cycles
    u32 sdrd          : 4 ; // Setup time for data bus during read access. Define the number of hclk cycles between the assertion of the chip-select (CSN) and the assertion of the write/enable signal (WN/E). Minimum value is 0 hclk cycle.
                            // 0000: 0 hclk cycle
                            // 1111: 15 hclk cycles
    u32 wdrd          : 6 ; // Wait states for data bus during read access. Define the number of hclk cycles when the write/enable signal is kept active. Minimum value is 1 hclk cycle.
                            // 000000: 1 hclk cycle
                            // 111111: 64 hclk cyles
    u32 hdrd          : 4 ; // Hold time for data bus during read access. Define the number of hclk cycles between the deassertion of the write/enable (WN/E) signal and the chip-select rising edge (CSN). Minimum value is 0 hclk cycle.
                            // 0000: 0 hclk cycle
                            // 1111: 15 hclk cycles
    u32 hard          : 2 ; // Hold time for address bus during read access. Define the number of hclk cycles between the deassertion of the chip-select (CSN) and the end of the address/data valid time. Minimum value is 0 hclk cycle.
                            // 00: 0 hclk cycle
                            // 11: 3 hclk cycles
    u32 rd2rd         : 4 ; // Write to Write delay. Define the number of inactive cycles between two consecutive read accesses on the same chip-select. Minimum value is 0 hclk cycle.
                            // 0000: 0 hclk cycle
                            // 1111: 15 hclk cycles
    u32 btard         : 4 ; // Bus Turnaround Time for read access. Define the number of inactive cycles between any accesses except consecutive read accesses on the same chip-select. Minimum value is 1 hclk cycle.
                            // 0000: 1 hclk cycle
                            // 1111: 16 hclk cyles
    u32               : 6 ; // Reserved
} EbiRdCfg_t;

typedef struct KeEbi_s
{
    EbiGlobalCfg_t  ebiGlobalCfg; //
    EbiMainCfg_t    ebiMainCfg0; //
    EbiWrCfg_t      ebiWrCfg0; //
    EbiRdCfg_t      ebiRdCfg0; //
    EbiMainCfg_t    ebiMainCfg1; //
    EbiWrCfg_t      ebiWrCfg1; //
    EbiRdCfg_t      ebiRdCfg1; //
    EbiMainCfg_t    ebiMainCfg2; //
    EbiWrCfg_t      ebiWrCfg2; //
    EbiRdCfg_t      ebiRdCfg2; //
    EbiMainCfg_t    ebiMainCfg3; //
    EbiWrCfg_t      ebiWrCfg3; //
    EbiRdCfg_t      ebiRdCfg3; //
} KeEbi_t;

extern volatile W5Probe_t* const W5Probe;
#ifdef __B1__
extern volatile W5Emi_t * const W5Emi;
extern volatile W5EmiArbitrer_t * const W5EmiArbitrer;
extern volatile W5SdramCfg_t * const W5SdramCfg;
#endif
extern volatile W5Dpram_t * const W5Dpram;
extern volatile W5TabDpRam_t * const W5TabDpRam;
extern volatile W5SReg_t *  const W5SReg;
extern volatile W5IrqControl_t *  const W5IrqControl;
extern volatile W5ExtInt_t *  const W5ExtInt;
extern volatile W5Uart_t *  const W5Uart1;
extern volatile W5Uart_t *  const W5Uart2;
extern volatile W5Gea_t *  const W5Gea;
extern volatile W5Gea2_t *  const W5Gea2;
extern volatile W5Fcs_t *  const W5Fcs;
extern volatile W5DspIrqControl_t *  const W5DspIrqControl;
extern volatile W5CntReg_t *  const W5CntReg;
extern volatile W5AudioTimer_t *  const W5AudioTimer;
extern volatile W5Dsma_t *  const W5Dsma;
extern volatile W5Fir_t *  const W5Fir;
extern volatile W5SysTimer_t * const W5SysTimer;
extern volatile W5TbuEvt_t *  const W5TbuEvt;
extern volatile W5TbuC_t *  const W5TbuC;
extern volatile W5RfDwl_t *  const W5RfDwl;
extern volatile W5Agc_t *  const W5Agc;
extern volatile W5DigiRf_t *  const W5DigiRf;
extern volatile W5RfRam_t *  const W5RfRam;
extern volatile W5I2c_t *  const W5I2c;
#ifdef __B1__
extern volatile KeGpio_t *  const KeGpio;
#endif //__B1__
extern volatile OKeyPad_t *  const OKeyPad;
#ifdef __B1__
extern volatile W5Rtc_t *  const W5Rtc;
#endif
extern volatile OSpi_t * const OSpi1;
extern volatile OSpi_t * const OSpi2;
extern volatile OSpi_t * const OSpi3;
extern volatile W5SysReg_t * const W5SysReg;
#ifdef __B1__
extern volatile W5Cmu_t * const W5Cmu;
#endif //__B1__
extern volatile OSim_t * const OSim1;
extern volatile OSim_t * const OSim2;
extern volatile W5Dmac_t * const W5Dmac0;
extern volatile W5Dmac_t * const W5Dmac1;
extern volatile W5Dmac_t * const W5Dmac2;
extern volatile W5Dmac_t * const W5Dmac3;
extern volatile W5Dmac_t * const W5Dmac4;
extern volatile W5Dmac_t * const W5Dmac5;
extern volatile W5Dmac_t * const W5Dmac6;
extern volatile W5Dmac_t * const W5Dmac7;
extern volatile W5Dma_t * const W5Dma0;
extern volatile W5Dma_t * const W5Dma1;
extern volatile W5Dma_t * const W5Dma2;
extern volatile W5Dma_t * const W5Dma3;
extern volatile W5Dma_t * const W5Dma4;
extern volatile W5Dma_t * const W5Dma5;
extern volatile W5Dma_t * const W5Dma6;
extern volatile W5Dma_t * const W5Dma7;
extern volatile W5DmaCfg_t * const  W5DmaCfg;
extern volatile KeEbi_t * const  KeEbi;

#ifdef  __cplusplus
}
#endif //__cplusplus

#endif // __G1__

#endif //__KERNEL_H__
