//==============================================================================
//
//  File        : mmp_snr_inc.h
//  Description : INCLUDE File for the Sensor Function
//  Author      : Alterman
//  Revision    : 1.0
//
//==============================================================================

#ifndef _MMP_SNR_INC_H_
#define _MMP_SNR_INC_H_

//==============================================================================
//
//                              CONSTANTS
//
//==============================================================================

#define PRM_SENSOR                  (0)     ///< Primary Cam Via VIF
#define SCD_SENSOR                  (1)     ///< Secondary Cam Via VIF
#define USBH_SENSOR                 (2)     ///< Rear Cam Via USBH
#define TRD_SENSOR                  (3)     ///< Third Cam Via VIF
#define UNDEF_SENSOR                (0xFF)
#define VIF_SENSOR_MAX_NUM          (2) // (3) TBD
#define USBH_SENSOR_MAX_NUM         (1)

#define SENSOR_DSC_MODE             (1)
#define SENSOR_VIDEO_MODE           (2)

#define MAX_AE_CONVERGE_FRAME_NUM   (30)
#define MIN_AE_CONVERGE_FRAME_NUM   (9)

// ISO
#define MMP_AE_ISO_AUTO             (0)
#define MMP_AE_ISO_100              (1)
#define MMP_AE_ISO_200              (2)
#define MMP_AE_ISO_400              (3)
#define MMP_AE_ISO_800              (4)
#define MMP_AE_ISO_1600             (5)
#define MMP_AE_ISO_3200             (6)
#define MMP_AE_ISO_ERROR            (0xFFFFFFFF)

// EV
#define MMP_AE_EV_M200              (0)
#define MMP_AE_EV_M166              (1)
#define MMP_AE_EV_M133              (2)
#define MMP_AE_EV_M100              (3)
#define MMP_AE_EV_M066              (4)
#define MMP_AE_EV_M033              (5)
#define MMP_AE_EV_0000              (6)
#define MMP_AE_EV_P033              (7)
#define MMP_AE_EV_P066              (8)
#define MMP_AE_EV_P100              (9)
#define MMP_AE_EV_P133              (10)
#define MMP_AE_EV_P166              (11)
#define MMP_AE_EV_P200              (12)
#define MMP_AE_EV_ERROR             (0xFFFFFFFF)

// Effect
#define MMP_IMG_EFFECT_NORMAL       (0)
#define MMP_IMG_EFFECT_GREY         (1)
#define MMP_IMG_EFFECT_SEPIA        (2)
#define MMP_IMG_EFFECT_NEGATIVE     (3)
#define MMP_IMG_EFFECT_ANTIQUE      (4)
#define MMP_IMG_EFFECT_WATERCOLOR   (5)
#define MMP_IMG_EFFECT_PORTRAIT     (6)
#define MMP_IMG_EFFECT_LANDSCAPE    (7)
#define MMP_IMG_EFFECT_SUNSET       (8)
#define MMP_IMG_EFFECT_DUSK         (9)
#define MMP_IMG_EFFECT_DAWN         (10)
#define MMP_IMG_EFFECT_RED          (11)
#define MMP_IMG_EFFECT_GREEN        (12)
#define MMP_IMG_EFFECT_BLUE         (13)
#define MMP_IMG_EFFECT_YELLOW       (14)
#define MMP_IMG_EFFECT_EMBOSS       (15)
#define MMP_IMG_EFFECT_OIL          (16)
#define MMP_IMG_EFFECT_BW           (17)
#define MMP_IMG_EFFECT_SKETCH       (18)
#define MMP_IMG_EFFECT_CRAYONE      (19)
#define MMP_IMG_EFFECT_WHITEBOARD   (20)
#define MMP_IMG_EFFECT_BLACKBOARD   (21)
#define MMP_IMG_EFFECT_VIVID        (22)
#define MMP_IMG_EFFECT_PALE         (23)
#define MMP_IMG_EFFECT_ERROR        (0xFFFFFFFF)

// WB
#define MMP_AWB_MODE_BYPASS                 (0)
#define MMP_AWB_MODE_AUTO                   (1)
#define MMP_AWB_MODE_DAYLIGHT               (2)
#define MMP_AWB_MODE_CLOUDY                 (3)
#define MMP_AWB_MODE_FLUORESCENT_WHITE      (4)
#define MMP_AWB_MODE_FLUORESCENT_NATURAL    (5)
#define MMP_AWB_MODE_FLUORESCENT_DAYLIGHT   (6)
#define MMP_AWB_MODE_INCANDESCENT           (7)
#define MMP_AWB_MODE_FLASH                  (8)
#define MMP_AWB_MODE_ONEPUSH                (9)
#define MMP_AWB_MODE_ERROR                  (0xFFFFFFFF)

//==============================================================================
//
//                              ENUMERATION
//
//==============================================================================

/* Sensor Parameter */
typedef enum _MMP_SNR_PARAM {
    MMP_SNR_PARAM_RAWPREVIEW_EN = 0,
    MMP_SNR_PARAM_ISP_FRAME_CNT,
    MMP_SNR_PARAM_CUR_PREVIEW_MODE,
    MMP_SNR_PARAM_CUR_CAPTURE_MODE,
    MMP_SNR_PARAM_CUR_FPSx10,
    MMP_SNR_PARAM_NUM
} MMP_SNR_PARAM;

/* Sensor Device Driver Parameter */
typedef enum _MMP_SNR_DRV_PARAM {
    MMP_SNR_DRV_PARAM_SCAL_IN_RES = 0,
    MMP_SNR_DRV_PARAM_PREVIEW_RES_NUM,
    MMP_SNR_DRV_PARAM_DEF_PREVIEW_RES,
    MMP_SNR_DRV_PARAM_FPSx10,
    MMP_SNR_DRV_PARAM_NUM
} MMP_SNR_DRV_PARAM;

/* Sensor Preview Mode */
typedef enum _MMP_SNR_MODE {
    MMP_SNR_DSC_PRW_MODE = 1,
    MMP_SNR_VID_PRW_MODE = 2
} MMP_SNR_MODE;

/* Sensor Priority */
typedef enum _MMP_SNR_PRIO {
    MMP_SNR_PRIO_PRM = 0,
    MMP_SNR_PRIO_SCD
} MMP_SNR_PRIO;

/* Sensor Function Mode */
typedef enum _MMP_SNR_FUNCTION_MODE {
    MMP_SNR_PREV_MODE = 0,
    MMP_SNR_CAPT_MODE
} MMP_SNR_FUNCTION_MODE;

/* Sensor Deband Mode */
typedef enum _MMP_SNR_DEBAND_MODE {
    MMP_SNR_DEBAND_DSC_60HZ = 0,
    MMP_SNR_DEBAND_DSC_50HZ,
    MMP_SNR_DEBAND_VIDEO_60HZ,
    MMP_SNR_DEBAND_VIDEO_50HZ
} MMP_SNR_DEBAND_MODE;

/* TV Decoder Sensor Type */
typedef enum _MMP_SNR_ANADEC_SRC_TYPE {
    MMP_SNR_ANADEC_SRC_NO_READY = 0,
    MMP_SNR_ANADEC_SRC_PAL,
    MMP_SNR_ANADEC_SRC_NTSC,
    MMP_SNR_ANADEC_SRC_HD,   // Remove Later
    MMP_SNR_ANADEC_SRC_FHD,  // Remove Later
    MMP_SNR_ANADEC_SRC_DISCNT,
    MMP_SNR_ANADEC_SRC_NUM
} MMP_SNR_ANADEC_SRC_TYPE;

/* YUV Sensor Type */
typedef enum _MMP_SNR_YUV_SRC_TYPE {
    MMP_SNR_YUV_SRC_HD = 0,
    MMP_SNR_YUV_SRC_FHD,
    MMP_SNR_YUV_SRC_DISCNT,
    MMP_SNR_YUV_SRC_NUM
} MMP_SNR_YUV_SRC_TYPE;

/* Sensor Event */
typedef enum _MMP_SNR_EVENT {
    MMP_SNR_EVENT_ANADEC_SRC_TYPE = 0,
    MMP_SNR_EVENT_YUV_SRC_TYPE,
    MMP_SNR_EVENT_NUM
} MMP_SNR_EVENT;

/* ISP IQ Function */
typedef enum _MMP_ISP_IQ_FUNC {
    MMP_ISP_IQ_FUNC_SET_SHARPNESS = 0,
    MMP_ISP_IQ_FUNC_SET_EFFECT,
    MMP_ISP_IQ_FUNC_SET_GAMMA,
    MMP_ISP_IQ_FUNC_SET_CONTRAST,
    MMP_ISP_IQ_FUNC_SET_SATURATION,
    MMP_ISP_IQ_FUNC_SET_WDR,
    MMP_ISP_IQ_FUNC_SET_HUE,
    MMP_ISP_IQ_FUNC_NUM
} MMP_ISP_IQ_FUNC;

/* ISP 3A Function */
typedef enum _MMP_ISP_3A_FUNC {
    MMP_ISP_3A_FUNC_SET_AF_ENABLE = 0,
    MMP_ISP_3A_FUNC_SET_AF_MODE,
    MMP_ISP_3A_FUNC_SET_AF_POS,
    MMP_ISP_3A_FUNC_SET_AE_ENABLE,
    MMP_ISP_3A_FUNC_SET_EV,
    MMP_ISP_3A_FUNC_SET_ISO,
    MMP_ISP_3A_FUNC_SET_AE_FAST_MODE,
    MMP_ISP_3A_FUNC_SET_AE_FLICKER_MODE,
    MMP_ISP_3A_FUNC_SET_AE_METER_MODE,
    MMP_ISP_3A_FUNC_SET_AE_SYS_MODE,
    MMP_ISP_3A_FUNC_SET_AWB_ENABLE,
    MMP_ISP_3A_FUNC_SET_AWB_MODE,
    MMP_ISP_3A_FUNC_SET_AWB_FAST_MODE,
    MMP_ISP_3A_FUNC_SET_AWB_COLOR_TEMP,
    MMP_ISP_3A_FUNC_SET_3A_ENABLE,
    MMP_ISP_3A_FUNC_NUM
} MMP_ISP_3A_FUNC;

typedef enum
{
    MMP_SNR_ORIT_M0F0,                  /**< mirror, flip unchanged */
    MMP_SNR_ORIT_M1F0,                  /**< mirror changed, flip unchanged */
    MMP_SNR_ORIT_M0F1,                  /**< mirror unchanged, flip changed */
    MMP_SNR_ORIT_M1F1,                  /**< mirror and flip changed */
} MMP_SNR_ORIT; //sync with CUS_CAMSENSOR_ORIT

#endif //_MMP_SNR_INC_H_
