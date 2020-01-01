#ifndef __KERNEL_DSP_H__
#define __KERNEL_DSP_H__

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
//yucnhu: Mapping redefined for B2 ROM codes. (B2 V3)
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
  u16           u16_BurstStatusConflictCount; // 0x06E
  u16           u16_BurstStatusNB0;  // 0x070

  u16           u16_RficRxWidth;   // 0x072 RX samples width in bits (min = 10; max = 16) depends on the radio //Modified by yunchu for B2 ROM codes

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

 u16      u16_C_I_Nb[4];           //0x65A - Signal to interference measurement //Modified by yunchu for B2 ROM codes
 u16      u16_PowerResult[4];       // 0x662 - Power measurement result //Modified by yunchu for B2 ROM codes



  u16     au16_DebugReg[32];    // 0x66A - Debug Registers
  ///////////////////// Audio or Appli Params ////////////////////
  u16     u16_AudioFir[32];         // 0x6AA - Audio Fir Param predistorsions coeff

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

 u16      u16_TxSymbValue; //0x736  //Modified by yunchu for B2 ROM codes
 u16      u16_TxNbPreSymbBurst0;   // 0x738
 u16      u16_TxNbPostSymbBurst0;  // 0x73A
 u8       au8_TxPreSeqBurst0[4];   // 0x73C
 u8       au8_TxPostSeqBurst0[4];  // 0x740
 u16      u16_TxNbPreSymbBurst1;   // 0x744
 u16      u16_TxNbPostSymbBurst1;  // 0x746
 u8       au8_TxPostSeqBurst1[4];  // 0x748
 u16      u16_TxNbPreSymbBurst2;   // 0x74C
 u16      u16_TxNbPostSymbBurst2;  // 0x74E
 u8       au8_TxPostSeqBurst2[4];  // 0x750
 u16      u16_TxNbPreSymbBurst3;   // 0x754
 u16      u16_TxNbPostSymbBurst3;  // 0x756
 u8       au8_TxPostSeqBurst3[4];  // 0x758
 u16      u16_HomingParam;         //0x75C //yunchu: Add this item back for the new DSP patch.
 u16      u16_debug_mode;          //0x75E
 u16      au16_NBCCHDummyPCHHardData[8]; //0x760
 u16      au16_ExtraPwrMeasResult[4]; //0x770
 u16      u16_ExtraPwrMeasStatus;  //0x778
 u16      au16_BlindEuclideanDistGSMK[2]; //0x77A
 u16      au16_BlindEuclideanDist8PSK[2]; //0x77E
 u16      au16_AdjacentDetMsg[8];  //0x782
 u16      au16_ChannelEstMsg_I[5]; //0x792
 u16      au16_ChannelEstMsg_Q[5]; //0x79C
 u16      au16_ChannelEstMsg_IQ_EDGE[18]; //0x7A6
 u16      u16_ComfortNoiseGain;    //0x7CA
 u8       u8_PcmDumpIndex;         // 0x7CC
 u8       u8_DumpCtrl;             // 0x7CD
 u16      u16_DpgaSetting;         // 0x7CE
 u16      u16_DpgaParameters[16];  // 0x7D0
 u16      u16_FchNewDcProcess;     // 0x7F0
 u16      au16_PwrMeasResult0[4];  // 0x7F2
 u16      au16_PwrMeasResult1[4];  // 0x7FA
 u16      au16_NbResult0[8];       // 0x802
 u16      au16_NbResult1[8];       // 0x812
 u16      au16_NbResult2[8];       // 0x822
 u16      au16_NbResult3[8];       // 0x832
 u16      au16_FbResult[8];        // 0x842
 u16      au16_SbResult[8];        // 0x852
 u16      u16_SbBuffer;            // 0x862
 u16      au16_SbInfo[2];          // 0x864
 u16      au16_AudioUlFir[16];     // 0x868
 u16      u16_DigitalUlFilterGain; // 0x888
 u16      u16_AudioRunCtrl2;       // 0x88A
 u16      u16_CTA_CTMode;          // 0x88C
 u16      au16_Free[184];          // 0x88E
 u16      u16_End;                 // 0x9FE
} W5Dpram_t;

/*** Structure to initialize the DPRAM ***/
typedef struct W5TabDpRam_s
{
 u16 Table[1024];  //AKO - 20/09/05: change from 512 to 1024 size of DPRAM (512 with FPGA, 1024 on G1)
} W5TabDpRam_t;

///////////////////////////////////////////////////////////////////////////////////////////////
//*** Rfic Rx Width
#define DPRAM_RFIC_RX_WIDTH_12     12
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
#define DPRAM_AMR_THRESH_DISABLE_MSK    (0x0001<<DPRAM_AMR_THRESH_DISABLE_POS)
#define DPRAM_AMR_THRESH_DISABLE_POS    11
#define DPRAM_AMR_ACK_MSK               (0x0003<<DPRAM_AMR_ACK_POS)
#define DPRAM_AMR_ACK_OK                (0x0001<<DPRAM_AMR_ACK_POS)
#define DPRAM_AMR_ACK_ERROR             (0x0002<<DPRAM_AMR_ACK_POS)
#define DPRAM_AMR_ACK_UNKNOWN           (0x0003<<DPRAM_AMR_ACK_POS)
#define DPRAM_AMR_EVEN_PHASE            (0x0001<<10)
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
#define DPRAM_CMC_POS                           6
#define DPRAM_CMC_MSK                           (0x0007<<DPRAM_CMC_POS)
#define DPRAM_AMR_CMI_UP                     (0x0001<<9)
#define DPRAM_AMR_CMI_DOWN                (0x0001<<10)

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

//MST change for FACCH/H threshold {
#define DPRAM_FACCH_HR_DETECT_THRES          0xC8 /*-56 */
//MST change for FACCH/H threshold }


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
#define DPRAM_FR_CHECK_DISABLE    (0x0001<<2)
#define DPRAM_AEC_DUMP         (0x0001<<3)

// audio test mode
#define DPRAM_PCM_DUMP         (0x0001<<4)
#define DPRAM_FIFO_LOOP        (0x0001<<5)
#define DPRAM_MLS_MODE         (0x0001<<6)
#define DPRAM_MIXING_LOOP      (0x0001<<7)

/* u8_DumpCtrl */
#define DPRAM_DL_PCM_AFTER_PREDISTFIR    (0x0001 << ( 8 - 8))
#define DPRAM_DL_PCM_AFTER_SPDEC         (0x0001 << ( 9 - 8))
#define DPRAM_UL_PCM_AFTER_AEC           (0x0001 << (10 - 8))

#define DPRAM_PCM_DUMP_ALL                 \
          (  DPRAM_DL_PCM_AFTER_PREDISTFIR \
           | DPRAM_DL_PCM_AFTER_SPDEC      \
           | DPRAM_UL_PCM_AFTER_AEC        \
          )

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

//*** RxNBcchBuffer
#define DPRAM_RX_NBCCH_ERR_POS             8

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
#define DPRAM_DSP_ERROR_BAD_LOOP_COUNTER     (0x1 << 1)
#define DPRAM_DSP_ERROR_ICR_REG_ERROR     (0x1 << 2)
#define DPRAM_DSP_ERROR_CPU_REQUEST_ERROR     (0x1 << 3)
#define DPRAM_DSP_ERROR_EDGE_BURST_WITHOUT_INIT     (0x1 << 4)
#define DPRAM_DSP_ERROR_INT_DISABLED_IN_RXPORT_CTRL     (0x1 << 5)
#define DPRAM_DSP_ERROR_JUMP_TABLE_NOT_RELIABLE     (0x1 << 6)
#define DPRAM_DSP_ERROR_PREAMBLE_POSTAMBLE_FALSE_IN_8PSK     (0x1 << 7)

/*** MemoStatus ***/
#define DPRAM_MEMO_FDUPLEX               (0x0001<<0)
#define DPRAM_MEMO_RESET                 (0x0001<<1)
#define DPRAM_MEMO_RECORD                (0x0001<<2)
#define DPRAM_MEMO_PLAYBACK              (0x0001<<3)
#define DPRAM_MEMO_BUFFER_FULL           (0x0001<<4)

/*** Audio ***/
#define DPRAM_AUDIO_FIFO_TX_WORDS_SHIFT  5
#define DPRAM_AUDIO_FIFO_RX_WORDS_SHIFT  10

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
#define DPRAM_DIG_INGAIN_BOOST_FLAG      0x0400
#define DPRAM_EQUAL_ENABLE_FLAG          0x0800
#define DPRAM_DUAL_MIC_HF_ENABLE         0x1000
#define DPRAM_DIG_GAIN_INIT_FLAG_BIT     0x2000
#define DPRAM_STREAMING_AMR_ENABLE       0x4000
#define DPRAM_DIG_DPGA_ENABLE_FLAG       0x8000


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

/*** Audio Downlink Dynamic Range Control, DSP v17.2.0 patch */
#define DPRAM_HOMINGPARAM_DRC_BIT_POS   12
#define DPRAM_HOMINGPARAM_DRC_BIT_MSK   (0x3<<DPRAM_HOMINGPARAM_DRC_BIT_POS)

// Debug Reg not used for debug but for nominal software
#define DPRAM_NB0_TREATMENT_OK 0x0001

/****** Tx Symbols and Sequence ******/
#define DPRAM_ADD_SYM_MSK        0x000F
#define DPRAM_ADD_SYM_8PSK_OFF   8
#define DPRAM_NB_ADD_SYM_MSK     0x00FF
#define DPRAM_NB_ADD_SEQ_MSK     0x000F
#define DPRAM_NB_ADD_PRESEQ_OFF  8
#define DPRAM_NB_ADD_POSTSEQ_OFF 8
#define DPRAM_ADD_SEQ_MSK        0x0F
#define DPRAM_ADD_SEQ_HIGH_OFF   4
#define DPRAM_DIGRF_RED_BIT_POS 12
#define DPRAM_DIGRF_RED_BIT_MSK (1<<DPRAM_DIGRF_RED_BIT_POS)

/****** Debug Mode Setting *****/
#define DPRAM_NBCCH_DUMMYPCH_FLAG     (1<<0)
#define DPRAM_CRC_FLAG     (1<<1)
#define DPRAM_CHANNEL_EST_DBG     (1<<4)
#define DPRAM_SOFT_BIT_DBG     (1<<5)
#define DPRAM_PREFILTER_DBG     (1<<6)
#define DPRAM_ADJACENT_DET_DBG     (1<<7)
#define DPRAM_FACCH_ACC_DBG     (1<<8)
#define DPRAM_BLIND_DETECTION_DBG     (1<<9)

/*****Extra PwrMeas Status ****/
#define DPRAM_PWR_WIN_4_OK     (1<<0)
#define DPRAM_PWR_WIN_5_OK     (1<<1)
#define DPRAM_PWR_WIN_6_OK     (1<<2)
#define DPRAM_PWR_WIN_7_OK     (1<<3)

/***** Dump Ctrl *****/
#define DPRAM_DUMP_COUNTER_MASK    (0xFF)
#define DPRAM_DUMP_DL_OUTPUT_AEC_ENABLE     (0x1<<8)
#define DPRAM_DUMP_DL_SPEECH_OUT_ENABLE     (0x1<<9)
#define DPRAM_DUMP_UL_SPEECH_IN_ENABLE     (0x1<<10)

/*** Audio run control2 ***/
#define DPRAM_UL_FIR_ENABLE_FLAG          0x0001
#define DPRAM_DL_HPF                        0x0002
#define DPRAM_UL_HPF                        0x0004
#define DPRAM_UL_MSTARAGC_ENABLE_FLAG     0x0008
#define DPRAM_UL_MSTARDRC_ENABLE_FLAG     0x0010
#define DPRAM_DL_MSTARDRC_ENABLE_FLAG     0x0020
#define DPRAM_UL_MSTARTPS_ENABLE_FLAG     0x0040

/*** u16_ComfortNoiseGain usage ***/
#define DPRAM_OFFSET_COMFORT_NOISE_LEVEL      0
#define DPRAM_MASK_COMFORT_NOISE_LEVEL        (0x7)<<DPRAM_OFFSET_COMFORT_NOISE_LEVEL
#define DPRAM_OFFSET_COMFORT_NOISE_GAIN       3
#define DPRAM_MASK_COMFORT_NOISE_GAIN         (0x7F)<<DPRAM_OFFSET_COMFORT_NOISE_GAIN
#define DPRAM_MASK_CNG_CONTROL                 (0xFF)<<DPRAM_OFFSET_COMFORT_NOISE_GAIN
#define DPRAM_OFFSET_DL_DRC_NG_ENABLE         10
#define DPRAM_MASK_DL_DRC_NG_ENABLE           (0x1)<<DPRAM_OFFSET_DL_DRC_NG_ENABLE

/*** CTA Ctrl ***/
#define DPRAM_CTA_CTA_ENHANCE_ENABLE_BIT	    (1<<0)
#define	DPRAM_CTA_CTA_BPF_INIT_FLAG		        (1<<1)
#define DPRAM_CTA_CTA_STMUTE_FLAG	            (1<<2)
#define DPRAM_CTA_CHAMBER_DET_FLAG		        (1<<3)
#define DPRAM_CTA_PARAM_READ_CTRL_BIT		    (1<<4)
#define DPRAM_CTA_ENVDET_LESSNOISE_FLAG		    (1<<5)
#define DPRAM_CTA_ENVDET_MASSNOISE_FLAG		    (1<<6)
#define DPRAM_CTA_NORMAL_TRANSIT_CHAMBER_BIT   (1<<7)
#define DPRAM_CTA_CHAMDET_DISABLE_BIT		    (1<<8)
#define DPRAM_CTA_ENVDET_ENABLE_BIT		        (1<<9)
#define DPRAM_CTA_CHAMCAL_ENABLE_BIT            (1<<10)
#define DPRAM_CTA_CHAMCAL_FINISH_BIT            (1<<11)
#define DPRAM_CTA_DONE		                    (1<<12)

/*** DPRAM "u16_TxTchBuffer1" offset usage ***/
#define DPRAM_OFFSET_BUFFER_TO_INFO         -1
#define DPRAM_OFFSET_AGC_TARGET              0
#define DPRAM_OFFSET_AGC_MAX_GAIN            1
#define DPRAM_OFFSET_AGC_MIN_GAIN            2
#define DPRAM_OFFSET_AGC_ATTACK              3
#define DPRAM_OFFSET_AGC_DECAY               4
#define DPRAM_OFFSET_DRC_AT_RATE             5
#define DPRAM_OFFSET_DRC_RT_RATE             6
#define DPRAM_OFFSET_DRC_X_0                  7
#define DPRAM_OFFSET_DRC_X_1                  8
#define DPRAM_OFFSET_DRC_X_2                  9
#define DPRAM_OFFSET_DRC_X_3                 10
#define DPRAM_OFFSET_DRC_Y_0                 11
#define DPRAM_OFFSET_DRC_Y_1                 12
#define DPRAM_OFFSET_DRC_Y_2                 13
#define DPRAM_OFFSET_DRC_Y_3                 14
#define DPRAM_OFFSET_CTA_CHBDET_COUNTER1	15
#define DPRAM_OFFSET_CTA_CHBDET_COUNTER2	16
#define DPRAM_OFFSET_CTA_CHBDET_COUNTER3	17
#define DPRAM_OFFSET_CTA_BPF_STATE0_0		18
#define DPRAM_OFFSET_CTA_BPF_STATE0_1		19
#define DPRAM_OFFSET_CTA_BPF_STATE0_2		20
#define DPRAM_OFFSET_CTA_BPF_STATE1_0		21
#define DPRAM_OFFSET_CTA_BPF_STATE1_1		22
#define DPRAM_OFFSET_CTA_BPF_STATE1_2		23
#define DPRAM_OFFSET_CTA_ICNS_DETTHD        24
#define DPRAM_OFFSET_CTA_BPF_UPDETTHD       25
#define DPRAM_OFFSET_CTA_DRC_DETTHD         26
#define DPRAM_OFFSET_CTA_NODRC_DETTHD       27
#define DPRAM_OFFSET_TPS_RATE                28
#define DPRAM_OFFSET_CTA_INITCHK_PRD        29
#define DPRAM_OFFSET_CTA_INITCHK_CND        30
#define DPRAM_OFFSET_CTA_SUBCHK_PRD         31
#define DPRAM_OFFSET_CTA_SUBCHK_CND         32
#define DPRAM_OFFSET_CTA_EL_ATT_GAIN        33
#define DPRAM_OFFSET_CTA_ICNS_ATT_GAIN      34
#define DPRAM_OFFSET_CTA_MASSNOISE_THD      35
#define DPRAM_OFFSET_CTA_LESSNOISE_THD      36
#define DPRAM_OFFSET_CTA_ENVDET_COUNTER1	37
#define DPRAM_OFFSET_CTA_ENVDET_COUNTER2	38
#define DPRAM_OFFSET_CTA_ENVDET_COUNTER3	39
#define DPRAM_OFFSET_CTA_CHBCAL_COUNTER		40
#define DPRAM_OFFSET_CTA_ESTIMATED_NOISE    41


/************************************************/
/* Shared registers definition                  */
/************************************************/

typedef struct W5SReg_s
{
  u16           u16_CpuToDspInt;     // 0x000
  u16           u16_Unused0;         // 0x002
  u16           u16_DspRawStatus;    // 0x004
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
#define SREG_DSP_PCMDUMP_MSK             (1 << 15)


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
#define SREG_NBCCH_DUMMYPCH_POS    12
#define SREG_NBCCH_DUMMYPCH_ENABLE (0x0001<<SREG_NBCCH_DUMMYPCH_POS)
#define SREG_REPEATED_FACCH_POS    13
#define SREG_REPEATED_FACCH_ENABLE (0x0001<<SREG_REPEATED_FACCH_POS)

/* Burst IQ dump */
#define SREG_BURST_IQ_DUMP_POS          14
#define SREG_BURST_IQ_DUMP_ENABLE       (0x0001 << SREG_BURST_IQ_DUMP_POS)


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
#define SREG_RX_WIRTI		            (0x0001<<14)
//#define SREG_MULTIMEDIA_PROC            (0x0001<<13)
#define SREG_RESET_REPEATED_FACCH       (0x0001<<15)


/*** Software task control 1 ***/
#define SREG_TASK1_IR_RESET                        (0x0001<<0)
#define SREG_TASK1_EDGE_SW_RESET            (0x0001<<1)
#define SREG_TASK1_AMR_RESET_TX               (0x0001<<2)
#define SREG_TASK1_AMR_RESET_RX               (0x0001<<3)
#define SREG_TASK1_RX_DUMP_IQ                   (0x0001<<4)
#define SREG_TASK1_CRC16CORCS2                  (0x0001<<5)
#define SREG_TASK1_CRC16CORCS3                  (0x0001<<6)
#define SREG_TASK1_CRC16CORCS4                  (0x0001<<7)
/* 20101110: To avoid problems when sending racch and facch */
#define SREG_TASK1_TX_RACCH_FULL                  (0x0001<<8)
#define SREG_TASK1_TX_EXTRACH_FULL                (0x0001<<9)
#define SREG_TASK1_TX_NBCCH_FULL                  (0x0001<<10)
#define SREG_TASK1_TX_FACCH_FULL                  (0x0001<<11)
/* End of 20101110 */

//** Burst status **
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
#define SREG_REPEATED_FACCH_CCOMBINING  (0x0001<<7)

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

/* JMC: DSP patch 18.43.0 fixed the bug of pre-distortion filter application.
**      SREG_PREDISTORTION_INIT_FLAG is for modifying filter coefficient
**      on-the-fly.
*/
#define SREG_PREDISTORTION_INIT_FLAG    0x1000


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
// For DSP_NMI
#define DSP_IRQCTRL_AUDIO_IN    (0x0001<<0)// Audio Tx(input) INT...1: enable, 0:disable
#define DSP_IRQCTRL_AUDIO_OUT   (0x0001<<1)// Audio Rx(output) INT
#define DSP_IRQCTRL_SP_COD      (0x0001<<2)// speech coding INT
#define DSP_IRQCTRL_SP_DEC      (0x0001<<3)// speech decoding INT
#define DSP_IRQCTRL_ST_DSP      (0x0001<<4)// Tx processing INT
#define DSP_IRQCTRL_RX          (0x0001<<5)// Rx processing INT
#define DSP_IRQCTRL_CPU         (0x0001<<6)// CPU INT
#define DSP_IRQCTRL_USER        (0x0001<<7)// reserver
#define DSP_IRQCTRL_E_DETECTO   (0x0001<<8)// EDGE Detector INT
#define DSP_IRQCTRL_E_VITERBI   (0x0001<<9)// EDGE Viterbi INT
#define DSP_IRQCTRL_E_PREFILTER (0x0001<<10)// EDGE Prefilter INT
#define DSP_IRQCTRL_DMA         (0x0001<<11)// DSMA INT
#define DSP_IRQCTRL_SW          (0x0001<<12)// SW programmable INT


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

#define DSP_RESET_OFFSET       (15)
#define DSP_RESET_MASK         (0x01 << DSP_RESET_OFFSET)

#endif

