#ifndef __KERNEL_RF_H__
#define __KERNEL_RF_H__


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
  
  TBU_EVT_SET_TBUO8=39,  // SET signal for TBUOx
  TBU_EVT_SET_TBUO9=40,
  TBU_EVT_SET_ABB_TBUO=41,

  TBU_EVT_CLR_TBUO8=42,  // CLR signal for TBUOx
  TBU_EVT_CLR_TBUO9=43,
  TBU_EVT_CLR_ABB_TBUO=44,

  TBU_EVT_INV_TBUO8=45,  // INV signal for TBUOx
  TBU_EVT_INV_TBUO9=46,
  TBU_EVT_INV_ABB_TBUO=47,

#ifdef __TGGE_RF__
  TBU_EVT_RX_FILTER_PULSE=48,
  TBU_EVT_TX_FILTER_PULSE=49,
#endif

  TBU_EVT_DONOTHING=63
};

#define TBU_EVT_IMM_ORDER_0 0
#define TBU_EVT_IMM_ORDER_1 8
#define TBU_EVT_IMM_ORDER_2 16
#define TBU_EVT_IMM_ORDER_3 24

#define TBU_EVT_CLEAR 0xFFFFFFFF

#define TBU_CNT_TBUOX       11
#define TBU_CNT_DUAL_EVT    8
#define TBU_CNT_EXTEND_DUAL_EVT 16

#ifdef __TGGE_RF__
#define TBU_CNT_EXTEND2_DUAL_EVT 16
#define TBU_CNT_TOTAL_DUAL_EVT 30
#else
#define TBU_CNT_TOTAL_DUAL_EVT 24
#endif

#define TBU_CNT_SINGLE_EVT  56

#define TBUO_0      0
#define TBUO_1      1
#define TBUO_2      2
#define TBUO_3      3
#define TBUO_4      4
#define TBUO_5      5   
#define TBUO_6      6
#define TBUO_7      7
#define TBUO_8      8
#define TBUO_9      9
#define TBUO_ABB    10

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
  DEvt_t        DualEvt[TBU_CNT_DUAL_EVT];      // 8  double events
  SEvt_t        SingleEvt[TBU_CNT_SINGLE_EVT];  // 56 single events
  u32           u32_ImmEvt;     // 1
  u32           u32_EvtEn[2];
  u32           u32_DtxSens[2];
} W5TbuEvt_t;

typedef struct W5TbuExtendEvt_s
{
  DEvt_t        DualEvt[TBU_CNT_EXTEND_DUAL_EVT];      // 16  double events
  u32           u32_EvtEn;
  u32           u32_DtxSens;
#ifdef __TGGE_RF__
  u32           padding[6];
  DEvt_t        DualEvt2[TBU_CNT_EXTEND2_DUAL_EVT];     // 16  double events
#endif
} W5TbuExtendEvt_t;

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
  u32           u32_SleepTimeDuration;//0x128, AWAKE
  u32           u32_SleepTimeCounter; //0x12C, STC
  u16           u16_SleepTimeCounterVWIO;  //0x130
  u16           u16_Pad3;
  u32           u32_SleepTimeCal;        //0x134
  u32           u32_LockTime;       //0x138
  u32            u8_TbuoState:10;       //0x13C
  u32            u8_TbuoMask:10;        //0x13D
  u32            u8_TbuoPulseType:10;   //0x13E
  u32            u8_Pad0:2;  
  u32           u32_RawIntStatus;   //0x140
  u32           u32_IntCtrl;        //0x144
  u32           u32_IntStatus;      //0x148
  u32           u32_IntClear;       //0x14C
  u16           u16_calibNm1;       //0x150
  u16           u16_Pad1;           //0x152
  u8            u8_abbTbuo;         //0x154
  u8            u8_pad4;            //0x155
  u16           u16_Pad5;           //0x156
  u32           u32_spare;           //0x158
  u32           u32_TbuPwrCtl;       //0x15C
#ifdef __TGGE_RF__
  u32		    u32_pad1[18];           // Extended Doulbe Event 1
  u32		    u32_TbuEventWatch;      //0x1A8
  u32		    u32_TbuPwrFlow;         //0x1AC
  u32		    u32_StcDebugSleep;      //0x1B0
  u32           u32_StcDebugAwake;      //0x1B4
  u32           u32_StcStopPassword;    //0x1B8
  u32           u32_TbuDebugRead;       //0x1BC
  u32		    u32_pad2[16];           // Extended Doulbe Event 2
  u32           u32_RxDfeExtClcye;      //0x200
  u32           u32_TbuSaradc;          //0x204
#endif
} W5TbuC_t;

// Control register
#define TBU_SS_CODEC_INT_ENA  (0x0001<<0) // CPU to DSP interrupts
#define TBU_CH_CODEC_INT_ENA  (0x0001<<1) // TBU to DSP Tx interrupts 
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

#define TBU_DOUBLE_EVENT_NB   TBU_CNT_DUAL_EVT
#define TBU_NBBIT_ENFIELD 32

// LOCKTIME register
#define TBU_PLL_LOCK_TIME     (0x000F<<0)
#define TBU_OSC_LOCK_TIME     (0x000F<<8)
#define TBU_SQR_LOCK_TIME     (0x000F<<16)
#define TBU_PLL_LOCK_TIME_POS 0
#define TBU_PLL_START_TIME_POS 8
#define TBU_OSC_LOCK_TIME_POS 16
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

// TBU Power Control register
#define TBU_CPU_RECALL_TIME_POS (0)
#define TBU_CPU_RECALL_TIME_MSK (0x00FF<<TBU_CPU_RECALL_TIME_POS)
#define TBU_MTC_ON_TIME_POS     (8)
#define TBU_MTC_ON_TIME_MSK     (0x00FF<<TBU_MTC_ON_TIME_POS)
#define TBU_PF_OFF_TIME_POS     (16)
#define TBU_PF_OFF_TIME_POS     (16)
#define TBU_CPU_RECALL_SET_ENA  (0x0001<<24)

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
  u32           u32_PS2RamCtrl;//0x00
  u8            u8_PS2Control;//0x04
  u8            u8_ImmOrdPtr;
  u8            u8_ImmOrdSizeDest;
  u8            u8_P2SItrWrdX8;//[leon] B2
  u16           u16_PtrBufDescr;//0x08
  u16           u16_Pad1;
#ifdef __TGGE_RF__
  u16           u16_DpramReadAdd;          // 0x0C [9:0]
#else
  u16           u16_PtrAgcLut;//0x0c
#endif
  u16           u16_Pad2;
  u16           u16_InitValAdd;//0x10
  u16           u16_Pad3;
  u16           u16_ReadValAdd;
  u16           u16_Pad4;
#ifdef __TGGE_RF__
  u16           u16_PtrTxFliterDesc;    // 0x18 [11:0]
#else
  u16           u16_PtrTxPwr;
#endif
  u16           u16_Pad5;
#ifdef __TGGE_RF__
  u16           u16_PtrRxFliterDesc;    // 0x1C [11:0]
#else
  u16           u16_PtrRxWin;
#endif
  u16           u16_Pad6;
  u32           u32_P2S0Cfg;//0x20
  u32           u32_P2S1Cfg;//0x24
  u32           u32_P2S0Sr;//0x28
  u32           u32_P2S1Sr;//0x2C
  u32           u32_RfDwlIrqMask;
  u32           u32_RfDwlIrqStatus;
  u32           u32_RfDwlIrqClear;
  u32       u32_RfDwlIrqRawStatus;
  u16           u16_ColisionErrorCode;
  u16           u16_Pad7;
  u16           u16_GainControl;
  u16           u16_Pad8;
  Amble_t    Amble[5];
  u32           u32_Arbiter_Cfg;
  u32           u32_Pad9;
  u32           u32_P2S0Cfg_2;
  u32           u32_P2S1Cfg_2;
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

//leon
#define RFDWL_P2S0_ITR_WRD_X8      (0x0001<<0)
#define RFDWL_P2S1_ITR_WRD_X8      (0x0001<<1)

//P2SConfig register
#define RFDWL_CLKPOLARITY         (0x0001<<0)
#define RFDWL_CLKPHASE            (0x0001<<1)
#define RFDWL_EN_WGT_START        (0x0001<<2)
#define RFDWL_EN_WGT_END          (0x0002<<2)
#define RFDWL_EN_WGT_START_END    (0x0003<<2)
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
#define RFDWL_DATA_PULL_DOWN      ((u32)(0x0001<<31))

//GainControl configuration register
#define RFDWL_P2S_SEL             (0x0001<<0)
#define RFDWL_PRELEN_POS          1
#define RFDWL_PRELEN_MSK          (0x001F<<RFDWL_PRELEN_POS)
#define RFDWL_ROOTLEN_POS         6
#define RFDWL_ROOTLEN_MSK         (0x001F<<RFDWL_ROOTLEN_POS)
#define RFDWL_POSTLEN_POS         11
#define RFDWL_POSTLEN_MSK         (0x001F<<RFDWL_POSTLEN_POS)
// SIF config register

//leon
//ARBITER_CFG
#define RFDWL_B2_MODE_SEL         (0x0001<<22)
#define RFDWL_BIG2_MODE_SEL       (0X0001<<23)
#ifdef __TGGE_RF__
#define RFDL_READ_RFSRAM_AUTO_INC   (0X0001<<24)
#define RFDL_READ_DPRAM_AUTO_INC    (0X0001<<25)
#define RFDL_TX_FILTER_AUTO_INC     (0X0001<<26)
#define RFDL_RX_FILTER_AUTO_INC     (0X0001<<27)
#endif


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
  AgcCtrl_t     aControl[5];
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
#define AGC_0_7_BYTE              (0 << AGC_BYTE_SELECT_POS)
#define AGC_4_11_BYTE            (4 << AGC_BYTE_SELECT_POS)
#define AGC_5_12_BYTE            (5 << AGC_BYTE_SELECT_POS)
#define AGC_8_15_BYTE            (8 << AGC_BYTE_SELECT_POS)


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
   u32 u32_TxPortCtrl; //0x00
   u32 u32_RxPortCtrl; //0x04
   u32 u32_RfDataPortCtrl;//0x08
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
#define DIGIRF_RXCTRL_BITREV                    (0x0001<<3)// 0: MSB first, 1: LSB first
#define DIGIRF_RXCTRL_ENTYPE_PULSE              (0x0001<<4)// 0: enable type(active high), 1: pulse type 
#define DIGIRF_RXCTRL_CLK_INV                   (0x0001<<5)// 0: rising latch, 1: falling latch
#define DIGIRF_RXCTRL_CLK_MAIN                  (0x0000<<6)// 0: IQRX_CLK = MAIN_CLK, 1: IQRX_CLK = EXT_OR_INT_IQ_CLK
#define DIGIRF_RXCTRL_CLK_EXT_INT_CLK           (0x0001<<6)// 0: IQRX_CLK = MAIN_CLK, 1: IQRX_CLK = EXT_OR_INT_IQ_CLK
#define DIGIRF_RXCTRL_CLK_SEL                   DIGIRF_RXCTRL_CLK_EXT_INT_CLK
#define DIGIRF_RXCTRL_RXTXEN_PDDIS              (0x0001<<7)// 0: have a pull down, 1: pull down is disabled
#define DIGIRF_RXCTRL_RXTXDATA_PDDIS            (0x0001<<8)// 0: have a pull down, 1: pull down is disabled

// Digi Rf Tx Control
#define DIGIRF_TXCTRL_MODE_POS                  0
#define DIGIRF_TXCTRL_MODE_MSK                  (0x0003)
#define DIGIRF_TXCTRL_MODE_ENIN_CLKIN           (0<<DIGIRF_TXCTRL_MODE_POS)
#define DIGIRF_TXCTRL_MODE_ENOUT_CLKIN          (1<<DIGIRF_TXCTRL_MODE_POS)//DigRF mode, TXPORT_CLK is an input
#define DIGIRF_TXCTRL_MODE_ENOUT_CLKOUT         (2<<DIGIRF_TXCTRL_MODE_POS)//RF type 2 mode, TXPORT_CLK is an output
#define DIGIRF_TXCTRL_RATE_POS                  2
#define DIGIRF_TXCTRL_RATE_MSK                  (0x0003<<DIGIRF_TXCTRL_RATE_POS)
#define DIGIRF_TXCTRL_RATE_1                    (0<<DIGIRF_TXCTRL_RATE_POS)//block mode(TXPORT_CLK)
#define DIGIRF_TXCTRL_RATE_24                   (1<<DIGIRF_TXCTRL_RATE_POS)//stream mode(TXPORT_CLK/24)
#define DIGIRF_TXCTRL_RATE_32                   (2<<DIGIRF_TXCTRL_RATE_POS)//stream mode(TXPORT_CLK/32)
#define DIGIRF_TXCTRL_RATE_96                   (3<<DIGIRF_TXCTRL_RATE_POS)//stream mode(TXPORT_CLK/96)
#define DIGIRF_TXCTRL_EXTRACT_POS               4
#define DIGIRF_TXCTRL_EXTRACT_MSK               (0x0003<<DIGIRF_TXCTRL_EXTRACT_POS)
#define DIGIRF_TXCTRL_EXTRACT_1                 (0<<DIGIRF_TXCTRL_EXTRACT_POS)// all 4bits/symbol are transmitted
#define DIGIRF_TXCTRL_EXTRACT_24                (1<<DIGIRF_TXCTRL_EXTRACT_POS)// only b[1]/symbol is transmitted
#define DIGIRF_TXCTRL_EXTRACT_32                (2<<DIGIRF_TXCTRL_EXTRACT_POS)// only b[3:1]/symbol are transmitted
#define DIGIRF_TXCTRL_EXTRACT_96                (3<<DIGIRF_TXCTRL_EXTRACT_POS)
#define DIGIRF_TXCTRL_CLK_INV                   (0x0001<<6)
#define DIGIRF_TXCTRL_CLK_DIV                   (0x0001<<7)
#define DIGIRF_TXCTRL_RXTXEN_SEL                (0x0001<<8)
#define DIGIRF_TXCTRL_CLK_POS                   9
#define DIGIRF_TXCTRL_CLK_MSK                   (0x0003<<DIGIRF_TXCTRL_CLK_POS)
#define DIGIRF_TXCTRL_CLK_MAIN                  (0<<DIGIRF_TXCTRL_CLK_POS)
#define DIGIRF_TXCTRL_CLK_EXT_TXPORT            (1<<DIGIRF_TXCTRL_CLK_POS)
#define DIGIRF_TXCTRL_CLK_EXT_IQCLK             (2<<DIGIRF_TXCTRL_CLK_POS)


// Digi Rf Data Control
#define DIGRF_ABB_RFDATA_EN_POS 0
#define DIGRF_ABB_RFDATA_EN     (0x1<<DIGRF_ABB_RFDATA_EN_POS)//  Enable RF Data path towards ABB

#define DIGRF_EXT_INT_CLK_SEL_POS 1
#define DIGRF_EXT_INT_CLK_SEL     (0x1<<DIGRF_EXT_INT_CLK_SEL_POS)//Choose between analog or digital radio(1:ext_iq_clk(digital RF), 0:int_iq_clk(analog RF))


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
#define RXWIN_SWAP_IQ_DSP                (0x0001<<8)
#ifdef __TGGE_RF__
#define RXWIN_PWR_MEAS_INT				(0x0001<<9)
#define RXWIN_TONE_REMOVER 				(0x0001<<10)
#define RXWIN_IQME_EN               	(0x0001<<11)
#endif


//FirConf Register
#define RXWIN_FIR_BYPASS                (0x0001<<0)
#define RXWIN_TAP1_SELECT               (0x0001<<1)
#define RXWIN_DEC_FACT_POS              2
#define RXWIN_DEC_FACT_MSK              (0x0003<<2)
#define RXWIN_FIR_LENGTH_POS            4
#define RXWIN_FIR_LENGTH_MSK            (0x001F<<4)
#define RXWIN_OUT_LSB_ID_POS            9
#define RXWIN_OUT_LSB_ID_MSK            (0x003F<<9)

#define RFRAM_RXWIN_NB                   4      // This is the maximum Rx window managed by the DSP per frame
#define RFRAM_TXPWRRAMP_NBSTEP           16     // A power ramp is constitued by 16 value

#ifdef __TGGE_RF__
#define RFRAM_TXPWRRAMP_NB              5       // 8 power are needed per frame in the case of 4 Tx (NB + AB) with TA different from 0. However, by spec, the possible max ramping profile is 5 (4 Tx, ramp up + down + 3 interramp).
#else
#define RFRAM_TXPWRRAMP_NB               4      // 4 power are needed per frame in the case of 2 Tx (NB + AB) with TA different from 0
#endif
#ifdef __TXPR_USED__
#define RFRAM_TXPWRRAMP_SIZE             ((RFRAM_TXPWRRAMP_NBSTEP * RFRAM_TXPWRRAMP_NB) + 1) //One extra word for TXPR configuration
#else
#define RFRAM_TXPWRRAMP_SIZE             (RFRAM_TXPWRRAMP_NBSTEP * RFRAM_TXPWRRAMP_NB)
#endif
#define RFRAM_LUT_SIZE          14            // 7 Gains Max x 2 Band (14)

#ifdef __TGGE_RF__
#define RFRAM_RFDL_BUFFDESC_SIZE        75      //The max RFDL event per frame
#define RFRAM_RFDL_DATA_SIZE            179// allocate all remainder to read data //RFRAM_RFDL_BUFFDESC_SIZE	//The max number of word to send on 3-wire bus
#define RFRAM_RFDL_READ_DESC_SIZE       8// 8 
#define RFRAM_RFDL_READ_DATA_SIZE       18// 24
#define RFRAM_RFDL_FIR_DESC_SIZE        1// 2 
#define RFRAM_RFDL_READBACK_SIZE       6//RFRAM_RFDL_READ_DATA_SIZE
#else
#define RFRAM_RFDL_DATA_SIZE             45     //38, for 1 more event and 1 more codeword for Apus 33 The max number of word to send on 3-wire bus
#define RFRAM_RFDL_BUFFDESC_SIZE         24     //38, 33 The max RFDL event per frame
#define RFRAM_RFDL_READ_OP_SIZE          3     // Take one element out of descriptor & data size = u32 + u16 = 6 byte; two identical fram buffer -> 6x2=12 bytes=u32*3
#endif

#ifdef __TGGE_RF__
//TX shaping filter
#define RFDL_FIR_DESC_RF_LEN_POS        25
#define RFDL_FIR_DESC_RF_ADDR_POS       16
#define RFDL_FIR_DESC_DP_LEN_POS        10

#define RFDL_FIR_DESC_RF_LEN_MASK       0x7F
#define RFDL_FIR_DESC_RF_ADDR_MASK      0x1FF
#define RFDL_FIR_DESC_DP_LEN_MASK       0x3F
#define RFDL_FIR_DESC_DP_OFF_MASK       0x3FF
#endif

// Structure definition
// ****************
#ifdef __TGGE_RF__
typedef struct
{
  u16  u16_Offs;        // Data offset
  u16  u16_Size;        // Size and destination (PS0 / PS1)
} RfMsgDes_t;


typedef struct
{
  u32  u32_SrcBase:12;        // command base
  u32  u32_padding:4;
  u32  u32_DestBase:12;          // destination base
  u32  u32_BurstLen:4;		    // number of command -1
} RfRdMsgDes_t;


#define RFDL_SIZE_MSK     0x7FFF    // [30:16] 15bits
#define RFDL_DST_MSK      0x1
#define RFDL_DST_POS      15

//for RFDL read descriptor
#define RFDL_READ_SRC_BASE	0 // bit [11:0]
#define RFDL_READ_SRC_MASK	0xFFF
#define RFDL_READ_DST_BASE	16 // bit [27:16]
#define RFDL_READ_DST_MASK	0xFFF
#define RFDL_READ_BURST_LEN	28 // bit [31:28]
#define RFDL_READ_BURST_LEN_MASK 0xF

#define BLSM_RFDL_RD_DEST_CHK_BIT               0x8000

#else
typedef struct
{
  u8  u8_Offs;        // Data offset
  u8  u8_Size;        // Size and destination (PS0 / PS1)
} RfMsgDes_t;

#define RFDL_SIZE_MSK     0x7F
#define RFDL_DST_MSK      0x1
#define RFDL_DST_POS      7
#endif

#define RFDL_DST_PS0      0       // Must be 0
#define RFDL_DST_PS1      1       // Must be 1


// Structure RxWinMode
typedef struct
{
  u16   u16_DspJob;
  u16   u16_FirConf;   //  FIR_BYPASS, TAP_SELECT, DEC_FACT, FIR_LENGTH and OUT_LSB_ID fields
} RxWinMod_t;

#ifdef __TGGE_RF__
// Todo,
// 1. will re-arrange RFRAM structure if we need to read back from DFE/AFE to
// not only to DPRAM but RF driver.
// 2. Will going to take off Ramping Data section. they can be placed in
// original data section
// The size of this dedicated memory is 576 * 32 bits = 2.25KB
typedef struct W5RfRam_s
{
    RfMsgDes_t      pRfDwlBuffDesc1[RFRAM_RFDL_BUFFDESC_SIZE];  // 75
    u32             au32_RfDwlBuffData1[RFRAM_RFDL_DATA_SIZE];
    //u32             au32_TxPwrRampData1[RFRAM_TXPWRRAMP_SIZE];
    RfMsgDes_t      pRfDwlBuffDesc2[RFRAM_RFDL_BUFFDESC_SIZE];	//75
    u32             au32_RfDwlBuffData2[RFRAM_RFDL_DATA_SIZE];
    //u32             au32_TxPwrRampData2[RFRAM_TXPWRRAMP_SIZE];
    RfRdMsgDes_t    au32_RdDescData1[RFRAM_RFDL_READ_DESC_SIZE];	// 8
    u32             au32_RdData1[RFRAM_RFDL_READ_DATA_SIZE];			// 18	
    RfRdMsgDes_t    au32_RdDescData2[RFRAM_RFDL_READ_DESC_SIZE];	// 8
    u32             au32_RdData2[RFRAM_RFDL_READ_DATA_SIZE];			// 18
    u32				au32_TxFirDesc1[RFRAM_RFDL_FIR_DESC_SIZE];	// 1
    u32				au32_TxFirDesc2[RFRAM_RFDL_FIR_DESC_SIZE]; // 1
    u32				au32_RxFirDesc1[RFRAM_RFDL_FIR_DESC_SIZE];	// 1
    u32				au32_RxFirDesc2[RFRAM_RFDL_FIR_DESC_SIZE];	// 1
    u32             au32_RdBack1[RFRAM_RFDL_READBACK_SIZE];	// 6
    u32             au32_RdBack2[RFRAM_RFDL_READBACK_SIZE];	// 6
} W5RfRam_t;
#else
// The size of this dedicated memory is 256 * 32 bits = 1KB
typedef struct W5RfRam_s
{
    RfMsgDes_t       pRfDwlBuffDesc1[RFRAM_RFDL_BUFFDESC_SIZE];
    u32                  au32_RfDwlBuffData1[RFRAM_RFDL_DATA_SIZE];
    u32                  au32_TxPwrRampData1[RFRAM_TXPWRRAMP_SIZE];
    RfMsgDes_t       pRfDwlBuffDesc2[RFRAM_RFDL_BUFFDESC_SIZE];
    u32                  au32_RfDwlBuffData2[RFRAM_RFDL_DATA_SIZE];
    u32                  au32_TxPwrRampData2[RFRAM_TXPWRRAMP_SIZE];
    u32				au32_ReadData[RFRAM_RFDL_READ_OP_SIZE];
  u16                  au16_AgcLUT[RFRAM_LUT_SIZE];
  RxWinMod_t      RxWinMod[RFRAM_RXWIN_NB];
} W5RfRam_t;
#endif

/************************************************/
/* FIR registers definition                     */
/************************************************/

typedef struct W5Fir_s
{
  u16           au16_Tap0Coeff[21]; // 0x3400A000 - 0x3400A028
  u16           au16_Dummy0[11];    // 0x3400A02A
  u16           au16_Tap1Coeff[21]; // 0x3400A040 - 0x3400A068
  u16           au16_Dummy1[11];    // 0x3400A06A
  u32           u16_Status;         // 0x3400A080
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

extern volatile W5Fir_t *  const g_ptW5Fir;
extern volatile W5TbuEvt_t *  const g_ptW5TbuEvt;
extern volatile W5TbuExtendEvt_t        * const g_ptW5TbuExtendEvt;
extern volatile W5TbuC_t *  const g_ptW5TbuC;
extern volatile W5RfDwl_t *  const g_ptW5RfDwl;
extern volatile W5Agc_t *  const g_ptW5Agc;
extern volatile W5DigiRf_t *  const g_ptW5DigiRf;
extern volatile W5RfRam_t *  const g_ptW5RfRam;

#endif /*__KERNEL_RF_H__*/

