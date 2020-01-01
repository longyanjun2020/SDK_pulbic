/***************************************************************************
 *  kernel_audio.h
 *--------------------------------------------------------------------------
 *  Scope: AUDIO(I2S) related definitions
 *
 ****************************************************************************/

#ifndef __KERNEL_AUDIO_H__
#define __KERNEL_AUDIO_H__

#include "cpu_mem_map.hc"

/****************************************************************************/
/*        AUDIO registers                                                   */
/****************************************************************************/
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

#define AUDIO_TIMER_MUX_B2             (0x0001<<18) // SDI_E/SDO_E is SDO_E pin
#define AUDIO_TIMER_MUX_B1             (0x0001<<19) // SDO_E/SDI_E is SDO_E pin
#define AUDIO_TIMER_MUX_M2             (0x0001<<20) // select input (2) = loopthrough mode
#define AUDIO_TIMER_MUX_M1             (0x0001<<21) //
//////#define AUDIO_TIMER_MUX_B4             (0x0001<<22) // SDI/SDO pin is SDO
//////##define AUDIO_TIMER_MUX_B3             (0x0001<<23) // SDO/SDI pin is SDO
#define AUDIO_TIMER_MUX_M4             (0x0001<<24) // select input (2) = loopthrough mode
//////##define AUDIO_TIMER_MUX_M3             (0x0001<<25) // select input (2) according to Figure 10

#define AUDIO_TIMER_I2S_SEL            26
#define AUDIO_TIMER_I2S_MSK            (0x0003<<26)
#define AUDIO_TIMER_I2S_2_SLAVE        (0x0000<<26)
#define AUDIO_TIMER_I2S_ESLAVE_SMASTER (0x0001<<26)
//////##define AUDIO_TIMER_I2S_EMASTER_SSLAVE (0x0002<<26)

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
//////#define AUDIO_TIMER_PCM_CLK_SEL_2048K                     (0x4 << 23)
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

//*** Int period register ***
#define AUDIO_TIMER_INT_PERIOD_MSK      (0x007F<<0)

//*** Codex int delay register ***
#define AUDIO_TIMER_CODEC_INT_DELAY_MSK (0x007F<<0)

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

extern volatile W5AudioTimer_t *  const g_ptW5AudioTimer;

#endif // __KERNEL_AUDIO_H__
