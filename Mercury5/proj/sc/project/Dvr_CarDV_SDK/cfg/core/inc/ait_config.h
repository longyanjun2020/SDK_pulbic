///@ait_only
/** @file ait_config.h
*/

#ifndef _AIT_CONFIG_H_
#define _AIT_CONFIG_H_

//==============================================================================
//
//                              INCLUDE FILE
//
//==============================================================================

#include "mmp_lib.h"

//==============================================================================
//
//                              MACRO DEFINE
//
//==============================================================================

/** @name DSC
@{ */

    #define DSC_QTABLE_MAX_NUM          (3)         ///< maximum quality control mode

    #define DSC_NORMAL_PREVIEW_MODE     (0)
    #define DSC_FULL_PREVIEW_MODE       (1)
    #define DSC_TV_NTSC_PREVIEW_MODE    (2)
    #define DSC_TV_PAL_PREVIEW_MODE     (3)
    #define DSC_HDMI_PREVIEW_MODE       (4)
    #define DSC_CCIR_PREVIEW_MODE       (5)
    #define DSC_PREV_MODE_MAX_NUM       (6)         ///< maximum preview mode   

    #define DSC_NORMAL_DECODE_MODE      (0)
    #define DSC_FULL_DECODE_MODE        (1)
    #define DSC_TV_NTSC_DECODE_MODE     (2)
    #define DSC_TV_PAL_DECODE_MODE      (3)
    #define DSC_HDMI_DECODE_MODE        (4)
    #define DSC_CCIR_DECODE_MODE        (5)
    #define DSC_DECODE_MODE_MAX_NUM     (6)         ///< maximum decode mode

    #define DSC_JPEG_RESOL_3264x2448    (0)
    #define DSC_JPEG_RESOL_3200x2400    (1)
    #define DSC_JPEG_RESOL_3264x1836    (2)
    #define DSC_JPEG_RESOL_2816x2112    (3)
    #define DSC_JPEG_RESOL_2560x1920    (4)
    #define DSC_JPEG_RESOL_2048x1536    (5)
    #define DSC_JPEG_RESOL_2016x1512    (6)
    #define DSC_JPEG_RESOL_1600x1200    (7)
    #define DSC_JPEG_RESOL_1280x960     (8)
    #define DSC_JPEG_RESOL_640x480      (9)
    #define DSC_RESOL_MAX_NUM           (10)         ///< maximum capture resolution number
    #define DSC_RESOL_IDX_UNDEF         (0xFFFF)
    
/** @} */ // end of DSC

/** @name Video Recorder
@{ */

    #define VIDRECD_QLEVEL_MAX_NUM      (3)         ///< Video quality from LOW to HIGH
    #define VIDRECD_QUALITY_HIGH        (0)         ///< Video bit rate quality, high level
    #define VIDRECD_QUALITY_MID         (1)         ///< Video bit rate quality, middle level
    #define VIDRECD_QUALITY_LOW         (2)         ///< Video bit rate quality, low level

    #define VIDRECD_NORMAL_PREVIEW_MODE (0)
    #define VIDRECD_FULL_PREVIEW_MODE   (1)
    #define VIDRECD_NTSC_PREVIEW_MODE   (2)
    #define VIDRECD_PAL_PREVIEW_MODE    (3)
    #define VIDRECD_HDMI_PREVIEW_MODE   (4)
    #define VIDRECD_CCIR_PREVIEW_MODE   (5)
    #define VIDRECD_PREV_MODE_MAX_NUM   (6)         ///< maximum preview mode

    #define VIDRECD_FPS_MAX_NUM         (13)        ///< Video FPS from 7.5 to 120
    #define VIDRECD_FRAMERATE_7d5FPS    (0)         ///< Video frame rate, 7.5 fps
    #define VIDRECD_FRAMERATE_10FPS     (1)         ///< Video frame rate, 10 fps
    #define VIDRECD_FRAMERATE_12FPS     (2)         ///< Video frame rate, 12 fps
    #define VIDRECD_FRAMERATE_12d5FPS   (3)         ///< Video frame rate, 12.5 fps
    #define VIDRECD_FRAMERATE_15FPS     (4)         ///< Video frame rate, 15 fps
    #define VIDRECD_FRAMERATE_20FPS     (5)         ///< Video frame rate, 20 fps
    #define VIDRECD_FRAMERATE_24FPS     (6)         ///< Video frame rate, 24 fps
    #define VIDRECD_FRAMERATE_25FPS     (7)         ///< Video frame rate, 25 fps 
    #define VIDRECD_FRAMERATE_30FPS     (8)         ///< Video frame rate, 30 fps
    #define VIDRECD_FRAMERATE_50FPS     (9)         ///< Video frame rate, 50 fps
    #define VIDRECD_FRAMERATE_60FPS     (10)        ///< Video frame rate, 60 fps
    #define VIDRECD_FRAMERATE_100FPS    (11)        ///< Video frame rate, 100 fps
    #define VIDRECD_FRAMERATE_120FPS    (12)        ///< Video frame rate, 120 fps

    #define VIDRECD_RESOL_MAX_NUM       (20)
    #define VIDRECD_RESOL_640x368       (0)
    #define VIDRECD_RESOL_640x480       (1)
    #define VIDRECD_RESOL_720x480       (2)
    #define VIDRECD_RESOL_848x480       (3)
    #define VIDRECD_RESOL_960x720       (4)
    #define VIDRECD_RESOL_1024x576      (5)    
    #define VIDRECD_RESOL_1280x720      (6)
    #define VIDRECD_RESOL_1280x960      (7)
    #define VIDRECD_RESOL_1472x736      (8)
    #define VIDRECD_RESOL_1440x1088     (9)
    #define VIDRECD_RESOL_1600x900     	(10)
    #define VIDRECD_RESOL_1920x960    	(11)
    #define VIDRECD_RESOL_1920x1088    	(12)
    #define VIDRECD_RESOL_2304x1296     (13)
    #define VIDRECD_RESOL_2560x1280     (14)
    #define VIDRECD_RESOL_2560x1440     (15)
    #define VIDRECD_RESOL_2704x1536     (16)
    #define VIDRECD_RESOL_3008x1504     (17)
    #define VIDRECD_RESOL_3200x1808     (18)
    #define VIDRECD_RESOL_3840x2160     (19)

/** @} */ // end of video Recorder

/** @name Video Player
@{ */
    /// Preset 3GP Play mode configuration
    typedef enum MMPC_3GPPLAY_MODE {
        VIDEOPLAY_MODE_STD_LCD, 		///< Standard LCD out, fit width for demo
        VIDEOPLAY_MODE_FULLSCREEN_LCD, 	///< Full screen mode for LCD
        VIDEOPLAY_MODE_ZOOM_LCD, 		///< rotate 180
        VIDEOPLAY_MODE_ACTUAL_LCD, 		///< Full screen mode for LCD, rotate 270
        VIDEOPLAY_MODE_NTSC_TV,  		///< NTSC TV out, fullyfilled
        VIDEOPLAY_MODE_PAL_TV,  		///< PAL TV out, fullyfilled
        VIDEOPLAY_MODE_HDMI,			///< HDMI out
        VIDEOPLAY_MODE_CCIR,			///< CCIR out
        VIDEOPLAY_MODE_MAX///< used for number of play mode structure
	}MMPC_3GPPLAY_MODE;
   
/** @} */ // end of video player

/** @name MMP_AUDIO
@{ */

    /// Enable audio host parser
    #define MP3_HOST_PARSER_EN  (1)
    #define AAC_HOST_PARSER_EN  (0)
    #define WMA_HOST_PARSER_EN  (0)
    #define WAV_HOST_PARSER_EN  (0)
    #define AMR_HOST_PARSER_EN  (0)
    #define OGG_HOST_PARSER_EN  (0)
    #define RA_HOST_PARSER_EN   (0)

    /// Enable audio host database
    #define AUDIO_HOST_DB_EN    (0)

    /// Enable MP3HD decode supporting
    #define MP3HD_DEC_EN        (1)

    /// Enable Gapless playback
    #define GAPLESS_PLAY_EN     (1)

/** @} */ /* end of AUDIO */

//==============================================================================
//
//                              FUNCTION PROTOTYPES
//
//==============================================================================

MMP_BOOL MMPC_System_InitConfig(void);
MMP_BOOL MMPC_Display_InitConfig(void);
MMP_BOOL MMPC_DSC_InitConfig(void);
MMP_BOOL MMPC_3gpRecd_InitConfig(void);
MMP_BOOL MMPC_3gpPlay_InitConfig(void);
MMP_BOOL MMPC_Audio_InitConfig(void);

#endif //_AIT_CONFIG_H_

///@end_ait_only
