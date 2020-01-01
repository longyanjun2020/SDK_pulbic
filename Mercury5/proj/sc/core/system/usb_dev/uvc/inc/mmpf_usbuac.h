#ifndef USBUAC_H
#define USBUAC_H

//==============================================================================
//
//                              INCLUDE FILE
//
//==============================================================================

#include "config_fw.h"
#include "mmpf_audio_ctl.h"

//==============================================================================
//
//                              CONSTANTS
//
//==============================================================================

// audiostreaming endpoint control selectors
#define ASE_CONTROL_UNDEFINED       0x00
#define ASE_SAMPLING_FREQ_CONTROL   0x01
#define ASE_PITCH_CONTROL           0x02

// feature unit control selectors
#define FU_CONTROL_UNDEFINED            0x00
#define FU_MUTE_CONTROL                 0x01
#define FU_VOLUME_CONTROL               0x02
#define FU_BASS_CONTROL                 0x03
#define FU_MID_CONTROL                  0x04
#define FU_TREBLE_CONTROL               0x05
#define FU_GRAPHIC_EQUALIZER_CONTROL    0x06
#define FU_AUTOMATIC_GAIN_CONTROL       0x07
#define FU_DELAY_CONTROL                0x08
#define FU_BASS_BOOST_CONTROL           0x09
#define FU_LOUDNESS_CONTROL             0x0A

// Terminal/Unit ID
#define UAC_IT_ID   (0x01)
#define UAC_OT_ID   (0x03)
#define UAC_FU_ID   (0x05)

#define VOL_MAX     (50 * 256)  // +50 dB
#define VOL_MIN     (20 * 256)  // +20 dB
#define VOL_DEF     (42 * 256)  // 
#define VOL_RES     (128)       // 2 db gap. (ait analog gain limitation)

#define VOL_MUTE    (0x8000)
#define SAM_MAX     (16000)
#define SAM_MIN     (16000)
#define SAM_RES     (8000)
#define SAM_DEF     (UAC_AUDIN_SAMPLERATE)

#define MUTE_MAX    (1)
#define MUTE_MIN    (0)
#define MUTE_RES    (1)
#define MUTE_DEF    (0)

// UAC samples transfer configuration
#define UAC_FRAME_TIME          (1)     /* in unit of ms */
#define UAC_BUF_FRAME_CNT       (16)    /* the buffer can hold 16 frames, the
                                         * frame size is the number of samples
                                         * within UAC_FRAME_TIME ms.
                                         */
#define UAC_BUF_LOWBOUND        (4)     /* the low bound of frame count to
                                         * decrease one Tx sample
                                         */
#define UAC_BUF_UPBOUND         (12)    /* the up bound of frame count to
                                         * send one extra Tx sample
                                         */
#define UAC_BUF_INIT_FRAME_CNT  (8)     /* filled buf 8 zero frames initially
                                         */

//==============================================================================
//
//                              STRUCTURE
//
//==============================================================================

// UAC configurations
typedef struct _USB_UAC_CFG {
    MMP_ULONG ulFrameSize;      ///< number of samples in one frame
    MMP_ULONG ulBufUpBound;     ///< Up bound of frame buffer to increase sample
    MMP_ULONG ulBufLowBound;    ///< Low bound of frame buffer to decrease sample
    MMP_ULONG ulSampleRate;     ///< sample rate
    MMP_SHORT sVolume;          ///< volume in dB
    MMP_BOOL  bMute;            ///< mute or not
} USB_UAC_CFG;

//==============================================================================
//
//                              FUNCTIONS
//
//==============================================================================

void uac_init(void);
USB_UAC_CFG *uac_get_cfg(void);
void usb_ac_req_proc(MMP_UBYTE req);
void usb_ac_out_data(void);

extern void usb_uac_start_preview(MMP_ULONG ulSamprate);
extern void usb_uac_stop_preview(void);
extern void usb_uac_set_pktsize(MMP_BOOL bAsyncMode);
extern void usb_uac_set_samplerate(MMP_ULONG ulSamprate);
extern void usb_uac_set_mute(MMP_BOOL bMute);
extern void usb_uac_set_volume(MMP_SHORT sVolume);

#endif