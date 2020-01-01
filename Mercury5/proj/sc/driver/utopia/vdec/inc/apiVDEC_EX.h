//<MStar Software>
//******************************************************************************
// MStar Software
// Copyright (c) 2010 - 2012 MStar Semiconductor, Inc. All rights reserved.
// All software, firmware and related documentation herein ("MStar Software") are
// intellectual property of MStar Semiconductor, Inc. ("MStar") and protected by
// law, including, but not limited to, copyright law and international treaties.
// Any use, modification, reproduction, retransmission, or republication of all
// or part of MStar Software is expressly prohibited, unless prior written
// permission has been granted by MStar.
//
// By accessing, browsing and/or using MStar Software, you acknowledge that you
// have read, understood, and agree, to be bound by below terms ("Terms") and to
// comply with all applicable laws and regulations:
//
// 1. MStar shall retain any and all right, ownership and interest to MStar
//    Software and any modification/derivatives thereof.
//    No right, ownership, or interest to MStar Software and any
//    modification/derivatives thereof is transferred to you under Terms.
//
// 2. You understand that MStar Software might include, incorporate or be
//    supplied together with third party`s software and the use of MStar
//    Software may require additional licenses from third parties.
//    Therefore, you hereby agree it is your sole responsibility to separately
//    obtain any and all third party right and license necessary for your use of
//    such third party`s software.
//
// 3. MStar Software and any modification/derivatives thereof shall be deemed as
//    MStar`s confidential information and you agree to keep MStar`s
//    confidential information in strictest confidence and not disclose to any
//    third party.
//
// 4. MStar Software is provided on an "AS IS" basis without warranties of any
//    kind. Any warranties are hereby expressly disclaimed by MStar, including
//    without limitation, any warranties of merchantability, non-infringement of
//    intellectual property rights, fitness for a particular purpose, error free
//    and in conformity with any international standard.  You agree to waive any
//    claim against MStar for any loss, damage, cost or expense that you may
//    incur related to your use of MStar Software.
//    In no event shall MStar be liable for any direct, indirect, incidental or
//    consequential damages, including without limitation, lost of profit or
//    revenues, lost or damage of data, and unauthorized system use.
//    You agree that this Section 4 shall still apply without being affected
//    even if MStar Software has been modified by MStar in accordance with your
//    request or instruction for your use, except otherwise agreed by both
//    parties in writing.
//
// 5. If requested, MStar may from time to time provide technical supports or
//    services in relation with MStar Software to you for your use of
//    MStar Software in conjunction with your or your customer`s product
//    ("Services").
//    You understand and agree that, except otherwise agreed by both parties in
//    writing, Services are provided on an "AS IS" basis and the warranty
//    disclaimer set forth in Section 4 above shall apply.
//
// 6. Nothing contained herein shall be construed as by implication, estoppels
//    or otherwise:
//    (a) conferring any license or right to use MStar name, trademark, service
//        mark, symbol or any other identification;
//    (b) obligating MStar or any of its affiliates to furnish any person,
//        including without limitation, you and your customers, any assistance
//        of any kind whatsoever, or any information; or
//    (c) conferring any license or right under any intellectual property right.
//
// 7. These terms shall be governed by and construed in accordance with the laws
//    of Taiwan, R.O.C., excluding its conflict of law rules.
//    Any and all dispute arising out hereof or related hereto shall be finally
//    settled by arbitration referred to the Chinese Arbitration Association,
//    Taipei in accordance with the ROC Arbitration Law and the Arbitration
//    Rules of the Association by three (3) arbitrators appointed in accordance
//    with the said Rules.
//    The place of arbitration shall be in Taipei, Taiwan and the language shall
//    be English.
//    The arbitration award shall be final and binding to both parties.
//
//******************************************************************************
//<MStar Software>
////////////////////////////////////////////////////////////////////////////////
//
// Copyright (c) 2008-2009 MStar Semiconductor, Inc.
// All rights reserved.
//
// Unless otherwise stipulated in writing, any and all information contained
// herein regardless in any format shall remain the sole proprietary of
// MStar Semiconductor Inc. and be kept in strict confidence
// ("MStar Confidential Information") by the recipient.
// Any unauthorized act including without limitation unauthorized disclosure,
// copying, use, reproduction, sale, distribution, modification, disassembling,
// reverse engineering and compiling of the contents of MStar Confidential
// Information is unlawful and strictly prohibited. MStar hereby reserves the
// rights to any and all damages, losses, costs and expenses resulting therefrom.
//
////////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////////////////////////
///
/// @file   apiVDEC_EX.h
/// @brief  VDEC EXTENSION API FOR DUAL STREAMS
/// @author MStar Semiconductor Inc.
///////////////////////////////////////////////////////////////////////////////////////////////////

/*! \defgroup VDEC VDEC Modules
   <b> VDEC Arch for HW IP </b> \n
   \image html VDEC_Arch_layer.PNG

   <b> VDEC API rule for Get Free Stream  </b> \n
   \image html GetFreeStreamID_pic.PNG

   <b> VDEC API call flow for DTV </b> \n
   \image html VDEC_DTV_pic1.PNG

   <b> VDEC API call flow in SN vdplayer </b> \n
   \image html apiVDEC_EX_SN_MM.png

   <b> VDEC TEE API call flow in HK and Secure R2 </b> \n
   \image html apiVDEC_EX_TEE.png

   <b> VDEC TEE API call flow in MSTplayer </b> \n
   \image html apiVDEC_EX_Mstplayer.png

*! \defgroup VDEC_Init VDEC_Init
*  \ingroup VDEC
*! \defgroup VDEC_Normal_decode VDEC Normal decode
*  \ingroup VDEC
*! \defgroup Decode Decode
*  \ingroup VDEC
*! \defgroup VDEC_Display_Q_Control VDEC Display Q_Control
*  \ingroup VDEC
*! \defgroup VDEC_ES_buffer_manage VDEC ES buffer manage
*  \ingroup VDEC
*! \defgroup VDEC_Flush_pattern VDEC Flush pattern
*  \ingroup VDEC
*! \defgroup Get_information Getinformation
*  \ingroup VDEC
*! \defgroup VdecEventGroup Vdec Event Group
*  \ingroup VDEC
*! \defgroup VDEC_Hardware VDEC Hardware
*  \ingroup VDEC
*! \defgroup VDEC_Enhanced VDEC Enhanced
*  \ingroup VDEC
*! \defgroup VDEC_DS VDEC DS
*  \ingroup VDEC
*! \defgroup VDEC_MHEG_DECODE_I_Frame VDEC MHEG DECODE I Frame
*  \ingroup VDEC
*! \defgroup VdecDebug Vdec Debug
*  \ingroup VDEC
*! \defgroup VDEC_TEE VDEC TEE
*  \ingroup VDEC
*! \defgroup VdecCloseCaption Vdec Close Caption
*  \ingroup VDEC
*/

#ifndef _API_VDEC_EX_H_
#define _API_VDEC_EX_H_


#include "UFO.h"

#ifdef __cplusplus
extern "C"
{
#endif

#if (!defined(MSOS_TYPE_NUTTX) && !defined(MSOS_TYPE_OPTEE)) || defined(SUPPORT_X_MODEL_FEATURE)
//#define UFO_PUBLIC_HEADER_212
//-------------------------------------------------------------------------------------------------
//  Macro and Define
//-------------------------------------------------------------------------------------------------
#define MSIF_VDEC_EX_LIB_CODE      {'V','E','X','_'}
#define MSIF_VDEC_EX_LIBVER        {'0','5'}
#define MSIF_VDEC_EX_BUILDNUM      {'0','3'}
#define MSIF_VDEC_EX_CHANGELIST    {'0','0','6','9','3','0','7','7'}

/// Version string.
#define VDEC_EX_API_VERSION                /* Character String for DRV/API version             */  \
    MSIF_TAG,                           /* 'MSIF'                                           */  \
    MSIF_CLASS,                         /* '00'                                             */  \
    MSIF_CUS,                           /* 0x0000                                           */  \
    MSIF_MOD,                           /* 0x0000                                           */  \
    MSIF_CHIP,                                                                                  \
    MSIF_CPU,                                                                                   \
    MSIF_VDEC_EX_LIB_CODE,                 /* IP__                                             */  \
    MSIF_VDEC_EX_LIBVER,                   /* 0.0 ~ Z.Z                                        */  \
    MSIF_VDEC_EX_BUILDNUM,                 /* 00 ~ 99                                          */  \
    MSIF_VDEC_EX_CHANGELIST,               /* CL#                                              */  \
    MSIF_OS

#define VDEC_EX_DEFAULT_DBG_MSG_LEVEL  E_VDEC_EX_DBG_LEVEL_DBG
#define VDEC_EX_RVD_BROKEN_BY_US   0x80000000
#define VDEC_EX_MVD_PIC_START_FLAG 0x40000000
#if defined(UFO_PUBLIC_HEADER_300)
#define VDEC_EX_BIT(_bit_)                  (1 << (_bit_))
#define VDEC_CAP_REPORT_SCAN_TYPE
#define VDEC_CAP_MULTI_DECODE
#define VDEC_CAP_HEVC_HDR //enable HDR
#define VDEC_CAP_HEVC_HDR_V2 //enable HDR version2
#define VDEC_CAP_HEVC_HDR_V3
#define VDEC_CAP_FRAME_INFO_EXT_V4
#define VDEC_CAP_FRAME_INFO_EXT_V5
#elif defined(UFO_PUBLIC_HEADER_212)
#define VDEC_EX_BIT(_bit_)                  (1 << (_bit_))
#define VDEC_CAP_REPORT_SCAN_TYPE
#define VDEC_CAP_DYNAMIC_CMA
#define VDEC_CAP_GET_CODEC_INFO //enable codec cap info
#define VDEC_CAP_HEVC_DV //enable HEVC dolby vision
#define VDEC_CAP_DISABLE_HEVC_10BITS    // MApi_VDEC_EX_PreSetControl((VDEC_StreamId *)pHandle, E_VDEC_EX_USER_CMD_VDEC_FEATURE, E_VDEC_EX_FEATURE_FORCE_MAIN_PROFILE);
#define VDEC_CAP_MULTI_DECODE
#define VDEC_CAP_TVOS20_DTV_MODE
#elif defined(UFO_PUBLIC_HEADER_500_3)
#define VDEC_EX_BIT(_bit_)                  (1 << (_bit_))
#define VDEC_CAP_REPORT_QOS_INFO // Enable VDEC FW to calculate qos info caps
#define VDEC_CAP_REPORT_SCAN_TYPE //Report Scan type on OMX
#define VDEC_CAP_DYNAMIC_CMA //enable Dynamic Cma
#define VDEC_CAP_HEVC_HDR  //enable HDR
#define VDEC_CAP_HEVC_HDR_V2 //enable HDR version2
#define VDEC_CAP_HEVC_HDR_V3 //enable HDR version3
#define VDEC_CAP_FRAME_INFO_EXT_V4
#define VDEC_CAP_FRAME_INFO_EXT_V5
#define VDEC_CAP_FRAME_INFO_EXT_V6
#define VDEC_CAP_GET_CODEC_INFO //enable codec cap info
#define VDEC_CAP_HEVC_DV_XC_SHM_ADDR //enable OMX init VDEC/XC share memory
#define VDEC_CAP_DISABLE_HEVC_10BITS    // MApi_VDEC_EX_PreSetControl((VDEC_StreamId *)pHandle, E_VDEC_EX_USER_CMD_VDEC_FEATURE, E_VDEC_EX_FEATURE_FORCE_MAIN_PROFILE);
#define VDEC_CAP_MULTI_DECODE //Support N decode
#define VDEC_CAP_TVOS20_DTV_MODE //Support TVOS 2.0 for DTV mode
#define VDEC_CAP_SUPPORT_REAL_FRAMERATE //All codec support GetRealFrameRate
#define VDEC_CAP_SUPPORT_ADJUST_DECODER_FREQUENCY //Adjust decoder frequency
#else
#define VDEC_EX_BIT(_bit_)                  (1 << (_bit_))
#define VDEC_CAP_REPORT_QOS_INFO // Enable VDEC FW to calculate qos info caps
#define VDEC_CAP_REPORT_SCAN_TYPE
#define VDEC_CAP_DYNAMIC_CMA
#define VDEC_CAP_GET_CODEC_INFO //enable codec cap info
#define VDEC_CAP_HEVC_DV //enable HEVC dolby vision
#if defined(UFO_PUBLIC_HEADER_700)
#define VDEC_CAP_AVC_DV //enable AVC dolby vision
#endif
#define VDEC_CAP_DISABLE_HEVC_10BITS    // MApi_VDEC_EX_PreSetControl((VDEC_StreamId *)pHandle, E_VDEC_EX_USER_CMD_VDEC_FEATURE, E_VDEC_EX_FEATURE_FORCE_MAIN_PROFILE);
#define VDEC_CAP_HEVC_HDR //enable HDR
#define VDEC_CAP_HEVC_HDR_V2 //enable HDR version2
#define VDEC_CAP_HEVC_HDR_V3
#define VDEC_CAP_FRAME_INFO_EXT_V4
#if defined(UFO_PUBLIC_HEADER_700)
#define VDEC_CAP_FRAME_INFO_EXT_V5
#define VDEC_CAP_FRAME_INFO_EXT_V6//V6: for new DV display path(by XC shm)
#endif
#define VDEC_CAP_HEVC_DV_XC_SHM_ADDR //enable OMX init VDEC/XC share memory
#define VDEC_CAP_BUFFER_INFO         //enable set buffer info API
#define VDEC_CAP_HDR10_PERFRAME        //enable hdr per frame API
#define VDEC_CAP_MULTI_DECODE
#define VDEC_CAP_DV_OTT_API
#if defined(UFO_PUBLIC_HEADER_700)||defined(UFO_PUBLIC_HEADER_500)
#define VDEC_CAP_SYSTEM_PREGET_API
#define VDEC_CAP_DV_OTT_API_V2
#endif
#if defined(UFO_PUBLIC_HEADER_500)
#define VDEC_CAP_VP9_HDR
#endif
#endif
#ifndef VDEC_CAP_SYSTEM_PREGET_FB_MEM_USAGE_SIZE
#define VDEC_CAP_SYSTEM_PREGET_FB_MEM_USAGE_SIZE
#endif
#define VDEC_CAP_GET_SEQ_INFO  // enable for E_VDEC_EX_USER_CMD_GET_SEQ_INFO
#define VDEC_CAP_REPORT_STR
//-------------------------------------------------------------------------------------------------
//  Type and Structure
//-------------------------------------------------------------------------------------------------

#define VDEC_EX_FPA_TYPE_CHECKERBOARD_INTERLEAVING  0 /// FPA type: checker board interleaving
#define VDEC_EX_FPA_TYPE_COLUMN_INTERLEAVEING       1 /// FPA type: column interleaving
#define VDEC_EX_FPA_TYPE_ROW_INTERLEAVEING          2 /// FPA type: row interleaving
#define VDEC_EX_FPA_TYPE_SIDE_BY_SIDE_PACKING       3 /// FPA type: side by side packing
#define VDEC_EX_FPA_TYPE_TOP_BOTTOM_PACKING         4 /// FPA type: Top bottom packing
#define VDEC_EX_FPA_TYPE_TEMPORAL_INTERLEAVING_FRM  5 /// FPA type: temporal interleaving frame

#define VDEC_MAX_DEC_NUM 2

typedef enum
{
    E_VDEC_EX_MAIN_STREAM = 0,
    E_VDEC_EX_SUB_STREAM,
    E_VDEC_EX_N_STREAM,
} VDEC_EX_Stream;

typedef enum
{
    E_VDEC_EX_INPUT_TSP_0 = 0,
    E_VDEC_EX_INPUT_TSP_1,
    E_VDEC_EX_INPUT_TSP_2,
    E_VDEC_EX_INPUT_TSP_3,

    E_VDEC_EX_INPUT_TSP_NONE = 0xFF,
} VDEC_EX_INPUT_TSP;

typedef enum
{
    E_VDEC_EX_DISPLAY_PATH_MVOP_MAIN = 0,
    E_VDEC_EX_DISPLAY_PATH_MVOP_SUB,

    E_VDEC_EX_DISPLAY_PATH_NONE = 0xFF,
} VDEC_EX_DISPLAY_PATH;

typedef struct
{
    MS_BOOL bConnect; ///Status for Display path
    VDEC_EX_DISPLAY_PATH eMvopPath;///MVOP Display path
} VDEC_EX_DynmcDispPath;///Dynamic setup Display path

typedef enum
{
    E_VDEC_EX_DISPLAY_MODE_MCU,
    E_VDEC_EX_DISPLAY_MODE_HARDWIRE,
} VDEC_EX_DISPLAY_MODE;

typedef enum
{
    E_VDEC_EX_SPEC_DEFAULT,
    E_VDEC_EX_SPEC_HEVC_HD_LEVEL41 = 0x100,
    E_VDEC_EX_SPEC_HEVC_FHD_LEVEL41 = 0x120,
    E_VDEC_EX_SPEC_HEVC_FHD_LEVEL51,
    E_VDEC_EX_SPEC_HEVC_UHD_LEVEL51 = 0x140,
    E_VDEC_EX_SPEC_H264_HD_LEVEL40 = 0x200,
    E_VDEC_EX_SPEC_H264_FHD_LEVEL40 = 0x220,
    E_VDEC_EX_SPEC_H264_UHD_LEVEL50 = 0x240
} VDEC_EX_TASK_SPEC;

/// decoder event enumerator.
typedef enum
{
    /// turn off all event
    E_VDEC_EX_EVENT_OFF                = 0x00,
    /// display one frame/field
    E_VDEC_EX_EVENT_DISP_ONE           = VDEC_EX_BIT(0),
    /// repeat one frame/field
    E_VDEC_EX_EVENT_DISP_REPEAT        = VDEC_EX_BIT(1),
    /// one CC data should be displayed
    E_VDEC_EX_EVENT_DISP_WITH_CC       = VDEC_EX_BIT(2),
    /// decode one frame
    E_VDEC_EX_EVENT_DEC_ONE            = VDEC_EX_BIT(3),
    /// decode one I frame
    E_VDEC_EX_EVENT_DEC_I              = VDEC_EX_BIT(4),
    /// decode error
    E_VDEC_EX_EVENT_DEC_ERR            = VDEC_EX_BIT(5),
    /// display information is changed
    E_VDEC_EX_EVENT_DISP_INFO_CHG      = VDEC_EX_BIT(6),
    /// find user data
    E_VDEC_EX_EVENT_USER_DATA_FOUND    = VDEC_EX_BIT(7),
    /// display information ready after be changed
    E_VDEC_EX_EVENT_DISP_INFO_RDY      = VDEC_EX_BIT(8),
    /// first frame decoded
    E_VDEC_EX_EVENT_FIRST_FRAME        = VDEC_EX_BIT(9),
    /// first picture found
    E_VDEC_EX_EVENT_PIC_FOUND          = VDEC_EX_BIT(10),
    /// video is ready to display (no garbage and avsync done)
    E_VDEC_EX_EVENT_VIDEO_UNMUTE       = VDEC_EX_BIT(11),
    /// new sequence header found
    E_VDEC_EX_EVENT_SEQ_HDR_FOUND      = VDEC_EX_BIT(12),
    /// active format description found
    E_VDEC_EX_EVENT_AFD_FOUND          = VDEC_EX_BIT(13),
    // ES data invalid
    E_VDEC_EX_EVENT_ES_DATA_ERR        = VDEC_EX_BIT(14),
    /// speed up the un-mute screen on XC.
    E_VDEC_EX_EVENT_XC_LOW_DEALY          = VDEC_EX_BIT(16),
    /// VDEC FW need driver to handle CMA action(allocate/release)
    E_VDEC_EX_EVENT_DEC_CMA_ACTION      = VDEC_EX_BIT(17),
    /// PTS_DISCONTINUE.
    E_VDEC_EX_EVENT_PTS_DISCONTINUE    = VDEC_EX_BIT(18),
    /// Display finish
    E_VDEC_EX_EVENT_DISP_FINISH        = VDEC_EX_BIT(19),
} VDEC_EX_EventFlag;

//define VDEC CB type
typedef enum
{
    E_VDEC_EX_CB_MAIN  = 0,
    E_VDEC_EX_CB_SUB,
} VDEC_EX_CB_TYPE;

/// codec type enumerator
typedef enum
{
    ///unsupported codec type
    E_VDEC_EX_CODEC_TYPE_NONE = 0,
    ///MPEG 1/2
    E_VDEC_EX_CODEC_TYPE_MPEG2,
    ///H263 (short video header)
    E_VDEC_EX_CODEC_TYPE_H263,
    ///MPEG4 (default)
    E_VDEC_EX_CODEC_TYPE_MPEG4,
    ///MPEG4 (Divx311)
    E_VDEC_EX_CODEC_TYPE_DIVX311,
    ///MPEG4 (Divx412)
    E_VDEC_EX_CODEC_TYPE_DIVX412,
    ///FLV
    E_VDEC_EX_CODEC_TYPE_FLV,
    ///VC1 advanced profile (VC1)
    E_VDEC_EX_CODEC_TYPE_VC1_ADV,
    ///VC1 main profile (RCV)
    E_VDEC_EX_CODEC_TYPE_VC1_MAIN,
    ///Real Video version 8
    E_VDEC_EX_CODEC_TYPE_RV8,
    ///Real Video version 9 and 10
    E_VDEC_EX_CODEC_TYPE_RV9,
    ///H264
    E_VDEC_EX_CODEC_TYPE_H264,
    ///AVS
    E_VDEC_EX_CODEC_TYPE_AVS,
    ///MJPEG
    E_VDEC_EX_CODEC_TYPE_MJPEG,
    ///MVC
    E_VDEC_EX_CODEC_TYPE_MVC,
    ///VP8
    E_VDEC_EX_CODEC_TYPE_VP8,
    ///HEVC
    E_VDEC_EX_CODEC_TYPE_HEVC,
    ///VP9
    E_VDEC_EX_CODEC_TYPE_VP9,
    ///HEVC_DV
    E_VDEC_EX_CODEC_TYPE_HEVC_DV,
    ///AVC_DV
    E_VDEC_EX_CODEC_TYPE_H264_DV,

    E_VDEC_EX_CODEC_TYPE_NUM
} VDEC_EX_CodecType;

/// input source select enumerator
typedef enum
{
    ///DTV mode
    E_VDEC_EX_SRC_MODE_DTV = 0,
    ///TS file mode
    E_VDEC_EX_SRC_MODE_TS_FILE,
    ///generic file mode
    E_VDEC_EX_SRC_MODE_FILE,
    /// TS file and dual ES buffer mode
    E_VDEC_EX_SRC_MODE_TS_FILE_DUAL_ES,
    ///generic file and dual ES buffer mode
    E_VDEC_EX_SRC_MODE_FILE_DUAL_ES,
} VDEC_EX_SrcMode;

/// function return enumerator
typedef enum
{
    ///failed
    E_VDEC_EX_FAIL = 0,
    ///success
    E_VDEC_EX_OK,
    ///invalid parameter
    E_VDEC_EX_RET_INVALID_PARAM,
    ///access not allow
    E_VDEC_EX_RET_ILLEGAL_ACCESS,
    ///hardware abnormal
    E_VDEC_EX_RET_HARDWARE_BREAKDOWN,
     ///unsupported
    E_VDEC_EX_RET_UNSUPPORTED,
     ///timeout
    E_VDEC_EX_RET_TIMEOUT,
    ///not ready
    E_VDEC_EX_RET_NOT_READY,
    ///not initial
    E_VDEC_EX_RET_NOT_INIT,
    ///not exit after last initialization
    E_VDEC_EX_RET_NOT_EXIT,
    ///not running, counter does not change
    E_VDEC_EX_RET_NOT_RUNNING,
    ///max value
    E_VDEC_EX_RET_NUM,
} VDEC_EX_Result;

/// Action enumerator of display commands
typedef enum
{
    /// Action- display frame
    E_VDEC_EX_DISP_ACTION_DISPLAY   = 1,
    /// Action - release frame
    E_VDEC_EX_DISP_ACTION_RELEASE,
} VDEC_EX_DispCmdAction;

/// Freeze picture select after flush decoder
typedef enum
{
    /// Freeze at current display picture
    E_VDEC_EX_FREEZE_AT_CUR_PIC = 1,
    /// freeze at the latest decode picture
    E_VDEC_EX_FREEZE_AT_LAST_PIC,
    /// freeze current display picture and clear decode info
    E_VDEC_EX_FREEZE_AT_CUR_PIC_AND_CLEAR_DECODE_INFO,
} VDEC_EX_FreezePicSelect;

/// error code enumerator
typedef enum
{
    E_VDEC_EX_ERR_CODE_BASE = 0x01000000,
    E_VDEC_EX_ERR_CODE_NOT_SUPPORT,
    E_VDEC_EX_ERR_CODE_ILLEGAL_ACCESS,
    E_VDEC_EX_ERR_CODE_FRMRATE_NOT_SUPPORT,
    E_VDEC_EX_ERR_CODE_DIVX_PLUS_UNSUPPORTED,
    E_VDEC_EX_ERR_CODE_EXCEED_HW_CAP, ///over hw capability ex : avc 4k + avc 4k
    E_VDEC_EX_ERR_CODE_CODEC_COMPARE_CASE1, ///Hash key error
    E_VDEC_EX_ERR_CODE_CODEC_COMPARE_CASE2, ///Hash key error
    E_VDEC_EX_ERR_CODE_STR_RESUME_WAIT_RESET, ///str mm not support yet, need ap reset vdec
    

    E_VDEC_EX_MVD_ERR_CODE_BASE = 0x02000000,
        E_VDEC_EX_MVD_ERR_CODE_SHAPE,
        E_VDEC_EX_MVD_ERR_CODE_USED_SPRITE,
        E_VDEC_EX_MVD_ERR_CODE_NOT_8_BIT,         //error_status : bits per pixel
        E_VDEC_EX_MVD_ERR_CODE_NERPRED_ENABLE,
        E_VDEC_EX_MVD_ERR_CODE_REDUCED_RES_ENABLE,
        E_VDEC_EX_MVD_ERR_CODE_SCALABILITY,
        E_VDEC_EX_MVD_ERR_CODE_OTHER,
        E_VDEC_EX_MVD_ERR_CODE_H263_ERROR,
        E_VDEC_EX_MVD_ERR_CODE_RES_NOT_SUPPORT,   //error_status : none
        E_VDEC_EX_MVD_ERR_CODE_MPEG4_NOT_SUPPORT, //error_status : none
        E_VDEC_EX_MVD_ERR_CODE_PROFILE_NOT_SUPPORT  , ///< error_status : none
        E_VDEC_EX_MVD_ERR_CODE_RCV_ERROR_OCCUR,
        E_VDEC_EX_MVD_ERR_CODE_VC1_NOT_SUPPORT,   //error_status : none
        E_VDEC_EX_MVD_ERR_CODE_UNKNOW_CODEC_NOT_SUPPORT  ,   ///< error_status : none
        E_VDEC_EX_MVD_ERR_CODE_SLQ_TBL_NOT_SUPPORT  , ///< error_status : none
        E_VDEC_EX_MVD_ERR_CODE_FRAME_BUF_NOT_ENOUGH , ///< error_status : none

    E_VDEC_EX_HVD_ERR_CODE_BASE = 0x03000000,
        E_VDEC_EX_HVD_ERR_CODE_GENERAL_BASE = (0x0000|E_VDEC_EX_HVD_ERR_CODE_BASE),
        E_VDEC_EX_HVD_ERR_CODE_OUT_OF_SPEC ,
        E_VDEC_EX_HVD_ERR_CODE_UNKNOW_ERR,
        E_VDEC_EX_HVD_ERR_CODE_HW_BREAK_DOWN,
        E_VDEC_EX_HVD_ERR_CODE_HW_DEC_TIMEOUT,
        E_VDEC_EX_HVD_ERR_CODE_OUT_OF_MEMORY,
        E_VDEC_EX_HVD_ERR_CODE_UNKNOWN_CODEC,
        E_VDEC_EX_HVD_ERR_CODE_RES_NOT_SUPPORT, //resoultion not support
        // AVC
        E_VDEC_EX_HVD_ERR_CODE_AVC_BASE = (0x1000|E_VDEC_EX_HVD_ERR_CODE_BASE),
        E_VDEC_EX_HVD_ERR_CODE_AVC_SPS_BROKEN,
        E_VDEC_EX_HVD_ERR_CODE_AVC_SPS_NOT_IN_SPEC,
        E_VDEC_EX_HVD_ERR_CODE_AVC_SPS_NOT_ENOUGH_FRM,   // DPB size at specified level is smaller than the specified number of reference frames. This is not allowed
        E_VDEC_EX_HVD_ERR_CODE_AVC_PPS_BROKEN,           // PPS is not valid
        E_VDEC_EX_HVD_ERR_CODE_AVC_REF_LIST,
        E_VDEC_EX_HVD_ERR_CODE_AVC_NO_REF,
        E_VDEC_EX_HVD_ERR_CODE_AVC_RES,             // out of supported resolution
        // AVS
        E_VDEC_EX_HVD_ERR_CODE_AVS_BASE = (0x2000|E_VDEC_EX_HVD_ERR_CODE_BASE),
        E_VDEC_EX_HVD_ERR_CODE_AVS_RES,             // out of supported resolution
        // RM
        E_VDEC_EX_HVD_ERR_CODE_RM_BASE = (0x3000|E_VDEC_EX_HVD_ERR_CODE_BASE),
        E_VDEC_EX_HVD_ERR_CODE_RM_PACKET_HEADER,
        E_VDEC_EX_HVD_ERR_CODE_RM_FRAME_HEADER,
        E_VDEC_EX_HVD_ERR_CODE_RM_SLICE_HEADER,
        E_VDEC_EX_HVD_ERR_CODE_RM_BYTE_CNT,
        E_VDEC_EX_HVD_ERR_CODE_RM_DISP_TIMEOUT,
        E_VDEC_EX_HVD_ERR_CODE_RM_NO_REF,
        E_VDEC_EX_HVD_ERR_CODE_RM_RES,              // out of supported resolution
        E_VDEC_EX_HVD_ERR_CODE_RM_VLC,
        E_VDEC_EX_HVD_ERR_CODE_RM_SIZE_OUT_FB_LAYOUT,

    E_VDEC_EX_RVD_ERR_CODE_BASE = 0x04000000,
        E_VDEC_EX_RVD_ERR_CODE_PACKET_HEADER, ///< packet header version error
        E_VDEC_EX_RVD_ERR_CODE_FRAME_HEADER,  ///< frame type error
        E_VDEC_EX_RVD_ERR_CODE_SLICE_HEADER,  ///<slice header error
        E_VDEC_EX_RVD_ERR_CODE_DECODE_TIMEOUT,///< decode MB timeout
        E_VDEC_EX_RVD_ERR_CODE_OUT_OF_MEMORY, ///< frame buffer is out of memory
        E_VDEC_EX_RVD_ERR_CODE_BYTE_POS,      ///< can not find in ID table
        E_VDEC_EX_RVD_ERR_CODE_DISPLAY_TIMEOUT,

    E_VDEC_EX_MJPEG_ERR_CODE_BASE = 0x05000000,
        E_VDEC_EX_HVD_ERR_CODE_MJPEG_RES,
} VDEC_EX_ErrCode;

/// frame rate conversion mode enumerator
typedef enum
{
    /// disable FRC mode.
    E_VDEC_EX_FRC_NORMAL = 0,
    /// output rate is twice of input rate (ex. 30p to 60p)
    E_VDEC_EX_FRC_DISP_TWICE,
    /// 3:2 pulldown mode (ex. 24p to 60i or 60p)
    E_VDEC_EX_FRC_3_2_PULLDOWN,
    /// PAL to NTSC conversion (50i to 60i)
    E_VDEC_EX_FRC_PAL_TO_NTSC,
    /// NTSC to PAL conversion (60i to 50i)
    E_VDEC_EX_FRC_NTSC_TO_PAL,
    /// output rate 50P ->60P
    E_VDEC_EX_FRC_MODE_50P_60P,
    /// output rate 60P ->50P
    E_VDEC_EX_FRC_MODE_60P_50P,
} VDEC_EX_FrcMode;

/// trick decode mode enumerator
typedef enum
{
    /// decode all frame
    E_VDEC_EX_TRICK_DEC_ALL = 0,
    /// decode all except of non-reference frame
    E_VDEC_EX_TRICK_DEC_IP,
    /// only decode I frame
    E_VDEC_EX_TRICK_DEC_I,
    E_VDEC_EX_TRICK_DEC_NUM
} VDEC_EX_TrickDec;

/// display speed setting enumerator
typedef enum
{
    /// default speed type
    E_VDEC_EX_SPEED_DEFAULT = 0,
    /// fast display
    E_VDEC_EX_SPEED_FAST,
    /// slow display
    E_VDEC_EX_SPEED_SLOW,
} VDEC_EX_SpeedType;

/// The display speed enumerator
typedef enum
{
    /// Normal display speed.
    E_VDEC_EX_DISP_SPEED_1X = 1,
    /// 2X
    E_VDEC_EX_DISP_SPEED_2X = 2,
    /// 4X
    E_VDEC_EX_DISP_SPEED_4X = 4,
    /// 8X
    E_VDEC_EX_DISP_SPEED_8X = 8,
    /// 16X
    E_VDEC_EX_DISP_SPEED_16X = 16,
    /// 32X
    E_VDEC_EX_DISP_SPEED_32X = 32,
} VDEC_EX_DispSpeed;

/// motion JPEG down scale factor enumerator
typedef enum
{
    ///original size
    E_VDEC_EX_MJPEG_SCALE_1to1 = 0,
    ///down scale to 1/2
    E_VDEC_EX_MJPEG_SCALE_2to1,
    ///down scale to 1/4
    E_VDEC_EX_MJPEG_SCALE_4to1,
    ///down scale to 1/8
    E_VDEC_EX_MJPEG_SCALE_8to1,
} VDEC_EX_MJpegScaleFactor;

/// timestamp type of command queue
typedef enum
{
    ///without timestamp information
    E_VDEC_EX_TIME_STAMP_NONE = 0,
    ///PTS (Presentation Time Stamp)
    E_VDEC_EX_TIME_STAMP_PTS,
    ///DTS (Decode Time Stamp)
    E_VDEC_EX_TIME_STAMP_DTS,
    ///STS (Sorted Time Stamp)
    E_VDEC_EX_TIME_STAMP_STS,
    ///PTS_RVU (Presentation Time Stamp)
    E_VDEC_EX_TIME_STAMP_PTS_MPEG_DIRECTV_SD,
    ///DTS_RVU (Decode Time Stamp)
    E_VDEC_EX_TIME_STAMP_DTS_MPEG_DIRECTV_SD,
} VDEC_EX_TimeStampType;

/// The debug level of VDEC
typedef enum
{
    /// disable all uart message.
    E_VDEC_EX_DBG_LEVEL_NONE = 0,
    /// Only output error message
    E_VDEC_EX_DBG_LEVEL_ERR,
    /// output general message, and above.
    E_VDEC_EX_DBG_LEVEL_INFO,
    /// output debug message, and above.
    E_VDEC_EX_DBG_LEVEL_DBG,
    /// output function tracing message, and above.
    E_VDEC_EX_DBG_LEVEL_TRACE,
    /// output FW message.
    E_VDEC_EX_DBG_LEVEL_FW,
} VDEC_EX_DbgLevel;

/// Type of FW source
typedef enum
{
    E_VDEC_EX_FW_SOURCE_NONE,
    E_VDEC_EX_FW_SOURCE_DRAM,
    E_VDEC_EX_FW_SOURCE_FLASH,
}VDEC_EX_FWSourceType;

/// Format of CC (Closed Caption)
typedef enum
{
    E_VDEC_EX_CC_NONE       = 0x00,
    E_VDEC_EX_CC_608        = 0x01, //For CC608 or 157
    E_VDEC_EX_CC_708        = 0x02, //For CC708
    E_VDEC_EX_CC_UNPACKED   = 0x03,
} VDEC_EX_CCFormat;

/// Type of CC
typedef enum
{
    E_VDEC_EX_CC_TYPE_NONE = 0,
    E_VDEC_EX_CC_TYPE_NTSC_FIELD1 = 1,
    E_VDEC_EX_CC_TYPE_NTSC_FIELD2 = 2,
    E_VDEC_EX_CC_TYPE_DTVCC = 3,
    E_VDEC_EX_CC_TYPE_NTSC_TWOFIELD = 4,
} VDEC_EX_CCType;

typedef enum
{
    E_VDEC_EX_CC_GET_BUFF_START = 0x1,
    E_VDEC_EX_CC_GET_BUFF_SIZE,
    E_VDEC_EX_CC_GET_708_ENABLE
} VDEC_EX_CCInfoCmd;

typedef enum
{
    E_VDEC_EX_STAGE_STOP = 0,
    E_VDEC_EX_STAGE_INIT,
    E_VDEC_EX_STAGE_PLAY,
    E_VDEC_EX_STAGE_PAUSE,
} VDEC_EX_Stage;


typedef enum
{
    /// Used before MApi_VDEC_EX_Flush().
    E_VDEC_EX_PATTERN_FLUSH = 0,
    /// Used after MApi_VDEC_EX_EnableLastFrameShow().
    E_VDEC_EX_PATTERN_FILEEND,
}VDEC_EX_PatternType;

typedef enum
{
    E_VDEC_EX_FW_STATUS_FLAG_NONE       = 0,
    E_VDEC_EX_FW_STATUS_FLAG_SEEK_TO_I  = VDEC_EX_BIT(0),
}VDEC_EX_FW_STATUS_FLAG;

typedef struct DLL_PACKED
{
    MS_BOOL bInit;
    MS_BOOL bIdle;
    VDEC_EX_Stage  eStage;
} VDEC_EX_Status;

typedef struct DLL_PACKED
{
    MS_U32 u32Tmp;
} VDEC_EX_Info;

/// VDEC set info of total buffer
typedef struct DLL_PACKED
{
    MS_BOOL bSetTotalBuf;     /// TRUE: Set, FALSE: None set
    MS_PHY  phyTotalBufAddr;  /// Total buffer start address
    MS_SIZE szTotalBufSize;   /// Total buffer size

} VDEC_EX_TotalBufRange;

/// VDEC define set buffer type
typedef enum
{
    E_VDEC_EX_BUFFERTYPE_FB_BASE = 0x0000,          /// 0x0000 : Frame Buffer Type Base
    E_VDEC_EX_BUFFERTYPE_FB_MAIN,                   /// 0x0001 : Frame Buffer Main
    E_VDEC_EX_BUFFERTYPE_FB_SUB,                    /// 0x0002 : Frame Buffer Sub
    E_VDEC_EX_BUFFERTYPE_FB_BW,                     /// 0x0003 : Frame Buffer Bandwidth Balance
    E_VDEC_EX_BUFFERTYPE_FB_NUM,                    /// Number of Frame Buffer Type

    E_VDEC_EX_BUFFERTYPE_BS_BASE = 0x0100,          /// 0x0100 : Bitstream Buffer Type Base
    E_VDEC_EX_BUFFERTYPE_BS_MAIN,                   /// 0x0101 : Bitstream Buffer Main
    E_VDEC_EX_BUFFERTYPE_BS_SUB,                    /// 0x0102 : Bitstream Buffer Sub
    E_VDEC_EX_BUFFERTYPE_BS_NUM,                    /// Number of Bitstream Buffer Type

    E_VDEC_EX_BUFFERTYPE_HDRSHM_BASE = 0x0200,      /// 0x0200 : HDR Share Mem Type Base
    E_VDEC_EX_BUFFERTYPE_HDRSHM_MAIN,               /// 0x0201 : HDR Share Mem Main
    E_VDEC_EX_BUFFERTYPE_HDRSHM_SUB,                /// 0x0202 : HDR Share Mem Sub
    E_VDEC_EX_BUFFERTYPE_HDRSHM_NUM,                /// Number of HDR Share Mem Type

    E_VDEC_EX_BUFFERTYPE_NONE = 0xFFFF,             /// Undefine Buffer Type
} VDEC_EX_BufferType;

/// VDEC define get buffer type
typedef enum
{
    E_VDEC_EX_GET_BUFFERTYPE_ALLOC_BASE = 0x0000,   /// 0x0000 : Allocate Buffer Type Base
    E_VDEC_EX_GET_BUFFERTYPE_ALLOC_BS,              /// 0x0001 : Allocate Bitstream Buffer
    E_VDEC_EX_GET_BUFFERTYPE_ALLOC_DRVPROC,         /// 0x0002 : Allocate Driver Processing Buffer
    E_VDEC_EX_GET_BUFFERTYPE_ALLOC_NUM,             /// Number of Allocate Buffer Type

    E_VDEC_EX_GET_BUFFERTYPE_NONE = 0xFFFF,         /// Undefine Buffer Type
} VDEC_EX_GetBufferType;

/// VDEC set buffer info
typedef struct DLL_PACKED
{
    VDEC_EX_BufferType eType;  /// Buffer type
    MS_PHY  phyAddr;           /// Buffer start address
    MS_SIZE szSize;            /// Buffer size
    MS_U32  u32Config;         /// Buffer config
} VDEC_EX_BufferInfo;

typedef enum
{
    E_VDEC_EX_FRM_TYPE_I = 0,
    E_VDEC_EX_FRM_TYPE_P,
    E_VDEC_EX_FRM_TYPE_B,
    E_VDEC_EX_FRM_TYPE_OTHER,
    E_VDEC_EX_FRM_TYPE_NUM
} VDEC_EX_FrameType;
/// Frame buffer tile mode
typedef enum
{
    /// Tile mode
    E_VDEC_EX_TILEMODE_NONE = 0,
    /// Frame buffer tile mode 16 x 16
    E_VDEC_EX_TILEMODE_16x16,
    /// Frame buffer tile mode 16 x 32
    E_VDEC_EX_TILEMODE_16x32,
    /// Frame buffer tile mode 32 x 16
    E_VDEC_EX_TILEMODE_32x16,
    /// Frame buffer tile mode 32 x 32
    E_VDEC_EX_TILEMODE_32x32,
    /// Frame buffer tile mode num
    E_VDEC_EX_TILEMODE_NUM
} VDEC_EX_TileMode;

typedef enum
{
    ///< no field.
    E_VDEC_EX_FIELDTYPE_NONE,
    ///< Top field only.
    E_VDEC_EX_FIELDTYPE_TOP,
    ///< Bottom field only.
    E_VDEC_EX_FIELDTYPE_BOTTOM,
    ///< Both fields.
    E_VDEC_EX_FIELDTYPE_BOTH,
    E_VDEC_EX_FIELDTYPE_NUM
} VDEC_EX_FieldType;

typedef enum
{
    E_VDEC_EX_PATTERN_BEFORE_FRM = 0,
    E_VDEC_EX_PATTERN_AFTER_FRM,
    E_VDEC_EX_PATTERN_SKIP_DATA,
} VDEC_EX_PatchPattern;

typedef enum
{
    E_VDEC_EX_PIC_STRUCTURE_RSV = 0, //reserved
    E_VDEC_EX_PIC_STRUCTURE_TOP,
    E_VDEC_EX_PIC_STRUCTURE_BOT,
    E_VDEC_EX_PIC_STRCUTURE_FRM,
} VDEC_EX_PicStructure;

//VDEC FB reduction type
typedef enum
{
    VDEC_EX_FB_REDUCTION_NONE  = 0,
    VDEC_EX_FB_REDUCTION_1_2,
    VDEC_EX_FB_REDUCTION_1_4
} VDEC_EX_FBReductionType;

//VDEC XC_LOW_DELAY
typedef enum
{
    // no any XC_LOW_DELAY event happened.
    VDEC_EX_XC_LOW_DELAY_NONE              = 0x00,
    // XC_LOW_DELAY event for disable black screen.
    VDEC_EX_XC_DISABLE_BLACK_SCREEN        = VDEC_EX_BIT(0),
    // XC_LOW_DELAY event for release force_read_bank.
    VDEC_EX_XC_RELEASE_FORCE_READ_BANK     = VDEC_EX_BIT(1),
    // XC_LOW_DELAY event for release bob_mode.
    VDEC_EX_XC_RELEASE_BOB_MODE            = VDEC_EX_BIT(2),
} VDEC_EX_XcLowDelayType;



// VDEC SEQ change info
typedef enum
{
    // seq change due to first sequence
    VDEC_EX_SEQ_CHANGE_FIRST_TIME        = VDEC_EX_BIT(0),
    // seq chagne due to resolution
    VDEC_EX_SEQ_CHANGE_RESOLUTION        = VDEC_EX_BIT(1),
    // seq chagne due to picture type
    VDEC_EX_SEQ_CHANGE_PICTURE_TYPE      = VDEC_EX_BIT(2),
    // seq chagne due to aspect ratio
    VDEC_EX_SEQ_CHANGE_ASPECT_RATIO      = VDEC_EX_BIT(3),
    // seq chagne due to frame rate
    VDEC_EX_SEQ_CHANGE_FRAME_RATE        = VDEC_EX_BIT(4),
    // seq chagne due to HDR info
    VDEC_EX_SEQ_CHANGE_HDR_INFO          = VDEC_EX_BIT(5),
} VDEC_EX_SeqChangeInfo;






//VDEC set debug mode
typedef enum
{
    E_VDEC_EX_DBG_MODE_BYPASS_INSERT_START_CODE = 0,    /// for  UT
    E_VDEC_EX_DBG_MODE_BYPASS_DIVX_MC_PATCH,            /// for  UT
    E_VDEC_EX_DBG_MODE_NUM
} VDEC_EX_DbgMode;

//VDEC set clock speed
typedef enum
{
    E_VDEC_EX_CLOCK_SPEED_NONE = 0,
    E_VDEC_EX_CLOCK_SPEED_HIGHEST,
    E_VDEC_EX_CLOCK_SPEED_HIGH,
    E_VDEC_EX_CLOCK_SPEED_MEDIUM,
    E_VDEC_EX_CLOCK_SPEED_LOW,
    E_VDEC_EX_CLOCK_SPEED_LOWEST,
    E_VDEC_EX_CLOCK_SPEED_DEFAULT,
} VDEC_EX_ClockSpeed;


//VDEC set secure mode
typedef enum
{
    E_VDEC_EX_SECURE_MODE_NONE = 0,
    E_VDEC_EX_SECURE_MODE_TRUSTZONE
} VDEC_EX_SecureMode;

//VDEC set smooth rewind
typedef enum
{
    E_VDEC_EX_SMOOTH_REWIND_DISABLE = 0,
    E_VDEC_EX_SMOOTH_REWIND_SUPPORT, // memory at lastest 300mb
    E_VDEC_EX_SMOOTH_REWIND_ENABLE,
}VDEC_EX_Smooth_rewind_mode;

typedef struct DLL_PACKED
{
    MS_BOOL bEnable;
    MS_U8   u8Tolerance;
}VDEC_EX_Err_Tolerance;

///2X trick mode
typedef enum
{
/// 2x mode count vsync
    E_VDEC_EX_TRICKPLAY2X_COUNTVSYNC = 0,
/// 2x mode with av sync
    E_VDEC_EX_TRICKPLAY2X_AVSYNC
}VDEC_EX_TrickPlay2xMode;
///VP9 HDR10 Info
typedef struct
{
//VP9 HDR Version info
    MS_U32  u32Version;
//VP9 HDR MatrixCoefficients
    MS_U8   u8MatrixCoefficients;
//VP9 HDR BitsPerChannel
    MS_U8   u8BitsPerChannel;
//VP9 HDR ChromaSubsamplingHorz
    MS_U8   u8ChromaSubsamplingHorz;
//VP9 HDR ChromaSubsamplingVert
    MS_U8   u8ChromaSubsamplingVert;
//VP9 HDR CbSubsamplingHorz
    MS_U8   u8CbSubsamplingHorz;
//VP9 HDR CbSubsamplingVert
    MS_U8   u8CbSubsamplingVert;
//VP9 HDR ChromaSitingHorz
    MS_U8   u8ChromaSitingHorz;
//VP9 HDR ChromaSitingVert
    MS_U8   u8ChromaSitingVert;
//VP9 HDR ColorRange
    MS_U8   u8ColorRange;
// VP9 HDR TransferCharacteristics
    MS_U8   u8TransferCharacteristics;
// VP9 HDR ColourPrimaries
    MS_U8   u8ColourPrimaries;
// VP9 HDR Max Content Light Level
    MS_U16  u16MaxCLL;
// VP9 HDR Max Frame Average Light Level
    MS_U16  u16MaxFALL;
// VP9 HDR Primaries
    MS_U16  u16Primaries[3][2];
// VP9 HDR WhitePoint
    MS_U16  u16WhitePoint[2];
// VP9 HDR MaxLuminance
    MS_U32  u32MaxLuminance;
// VP9 HDR MinLuminance
    MS_U32  u32MinLuminance;
} VDEC_EX_Config_VP9HDR10;
//Codec Config type
typedef enum
{
// TYPE_NONE
    E_VDEC_EX_CONFIG_TYPE_NONE = 0,
// TYPE_VP9HDR10
    E_VDEC_EX_CONFIG_TYPE_VP9HDR10,
} VDEC_EX_ConfigType;

//Codec config
typedef struct
{
// Codec_Config Type
    VDEC_EX_ConfigType config_type;
// Codec_Config Addr
    MS_VIRT config_addr;
// Codec_Config Size
    MS_U32  config_size;
} VDEC_EX_Codec_Config;

//VDEC set MFcodec Mode
typedef enum
{
    E_VDEC_EX_MFCODEC_DEFAULT = 0,
    E_VDEC_EX_MFCODEC_FORCE_ENABLE,
    E_VDEC_EX_MFCODEC_FORCE_DISABLE,
} VDEC_EX_MFCodec_mode;

typedef enum
{
    E_VDEC_EX_FEATURE_DEFAULT = 0,
    E_VDEC_EX_FEATURE_FORCE_MAIN_PROFILE = VDEC_EX_BIT(0), // BIT0=1: HEVC Only support Main profile decode
    E_VDEC_EX_FEATURE_DISABLE_TEMPORAL_SCALABILITY = VDEC_EX_BIT(1), // BIT1=1: do not support temporal scalibity
} VDEC_EX_Feature;
/// VDEC setting customer mode
typedef enum
{
    /// Default 0, Customer mode not set
    E_VDEC_EX_CUSTOMER_DEFAULT = 0,
    /// BIT0=1: Run NDS code flow
    E_VDEC_EX_CUSTOMER_ENABLE_NDS = VDEC_EX_BIT(0), // BIT0=1: Run NDS code flow
} VDEC_EX_Customer_Mode;

typedef struct
{
    MS_U8   u8RepeatPeriod;
    MS_U8   u8DropPeriod;
}VDEC_EX_Slow_Sync;
/// VDEC control decoder frequency
typedef enum
{
    /// VDEC control decoder frequency down
    VDEC_EX_DECODER_FREQUENCY_DOWN = 0,
    /// VDEC control decoder frequency up
    VDEC_EX_DECODER_FREQUENCY_UP,
    /// VDEC control decoder frequency to minimum
    VDEC_EX_DECODER_FREQUENCY_MIN,
    /// VDEC control decoder frequency to maximum
    VDEC_EX_DECODER_FREQUENCY_MAX,
} VDEC_EX_Decoder_Frequency;

//VDEC user command id
typedef enum
{
    //Group1:Set Control command================================
    E_VDEC_EX_USER_CMD_SET_CONTROL_BASE  = 0x0000,
    E_VDEC_EX_USER_CMD_REPEAT_LAST_FIELD,               // Param: 1(ON), 0(OFF)
    E_VDEC_EX_USER_CMD_AVSYNC_REPEAT_TH,                // Param:0x01 ~ 0xFF(repeat times), 0xFF:always repeat when av is not sync
    E_VDEC_EX_USER_CMD_DISP_ONE_FIELD,                  // Param: 1(ON), 0(OFF)
    E_VDEC_EX_USER_CMD_FD_MASK_DELAY_COUNT,             // Param: unit is in vsync base for mute the fd_mask
    E_VDEC_EX_USER_CMD_FRC_OUTPUT,                      // Param: the address of VDEC_FRC_OutputParam
    E_VDEC_EX_USER_CMD_FRC_DROP_TYPE,                   // Param: 1(FRC_DROP_FIELD), 0(FRC_DROP_FRAME), default:0
    E_VDEC_EX_USER_CMD_FAST_DISPLAY,                    // Param: TRUE(Fast display), FALSE(Display until synced)
    E_VDEC_EX_USER_CMD_IGNORE_ERR_REF,                  // Param: TRUE(Ignore error reference), FALSE(Enable error reference handle)
    E_VDEC_EX_USER_CMD_FORCE_FOLLOW_DTV_SPEC,           // Param: 1(ON), 0(OFF)
    E_VDEC_EX_USER_CMD_AVC_MIN_FRM_GAP,                 // Param: Set the theshold of H264 frame gap, 0xFFFFFFFF don't care frame gap
    E_VDEC_EX_USER_CMD_DISABLE_SEQ_CHG,                 // Param: 1(Disable), 0(Enable)
    E_VDEC_EX_USER_CMD_SET_DISP_OUTSIDE_CTRL_MODE,      // Param: 1(ON) used for Openmax, 0(OFF) used for mstreamer and mm mode ,default : off
    E_VDEC_EX_USER_CMD_SET_DTV_USER_DATA_MODE,          // Param: 0(Support normal DVB CC, default case), 1(Support ATSC DirectTV CC), 2,3,4(Reserved)
    E_VDEC_EX_USER_CMD_SET_SINGLE_TASK_MODE,
    E_VDEC_EX_USER_CMD_AVC_DISABLE_ANTI_VDEAD,
    E_VDEC_EX_USER_CMD_DTV_RESET_MVD_PARSER,            // Param: 0(Disable), 1(Enable)
    E_VDEC_EX_USER_CMD_PVR_FLUSH_FRAME_BUFFER,
    E_VDEC_EX_USER_CMD_FORCE_INTERLACE_MODE,
    E_VDEC_EX_USER_CMD_RELEASE_FD_MASK,                 // Param: 1 to release fd mask when zooming or slow motion
    E_VDEC_EX_USER_CMD_SET_DECODE_MODE,
    E_VDEC_EX_USER_CMD_SUPPORT_AVC_TO_MVC,              // Param: 0(Do not support), 1(Support AVC to MVC)
    E_VDEC_EX_USER_CMD_3DLR_VIEW_EXCHANGE,              // Param: 0(Disable), 1(View L/R exhange)
    E_VDEC_EX_USER_CMD_SET_VSIZE_ALIGN,                 // Param: 0(Disable), 1(Enable)
    E_VDEC_EX_USER_CMD_SHOW_DECODE_ORDER,               // Param: 0(Disable), 1(Enable)
    E_VDEC_EX_USER_CMD_AVC_DISP_IGNORE_CROP,            // Param: 0(Disable), 1(Enable)
    E_VDEC_EX_USER_CMD_SET_DISP_FINISH_MODE,
    E_VDEC_EX_USER_CMD_SET_AVSYNC_MODE,
    E_VDEC_EX_USER_CMD_SUSPEND_DYNAMIC_SCALE,           // Param: 0(Disable, non-suspend DS), 1(Enable, suspend DS)
    E_VDEC_EX_USER_CMD_FORCE_AUTO_MUTE,
    E_VDEC_EX_USER_CMD_AVC_NEW_SLOW_MOTION,             // Param: 0(Disable), 1(Enable)
    E_VDEC_EX_USER_CMD_PUSH_DISPQ_WITH_REF_NUM,         // Param: 0(Disable), 1(Enable)
    E_VDEC_EX_USER_CMD_DS_RESV_N_BUFFER,                // Param: 0(Disable), 1(Enable)
    E_VDEC_EX_USER_CMD_RM_ENABLE_PTS_TBL,               // Param: 0(Disable), 1(Enable)
    E_VDEC_EX_USER_CMD_FLUSH_PTS_BUF,
    E_VDEC_EX_USER_CMD_SET_IDCT_MODE,                   // Param: 0(Original), 1(new IDCT)
    E_VDEC_EX_USER_CMD_DROP_ERR_FRAME,                  // Param: 0(Disable), 1(Enable)
    E_VDEC_EX_USER_CMD_SET_CC608_INFO_ENHANCE_MODE,
    E_VDEC_EX_USER_CMD_IGNORE_PIC_OVERRUN,              // Param: 0(Disable), 1(Enable)
    E_VDEC_EX_USER_CMD_SET_SELF_SEQCHANGE,
    E_VDEC_EX_USER_CMD_AUTO_EXHAUST_ES_MODE,            // Param: set the upper bound (arg[31:16]), and lower bound (arg[15:0])of ES level, Unit = 1KBytes, Auto drop display to consume ES data as soon as possible when ES level is higher than upper bound
    E_VDEC_EX_USER_CMD_CTL_SPEED_IN_DISP_ONLY,          // Param: 0(Original: Dec and disp time), 1(In Disp only)
    E_VDEC_EX_USER_CMD_AVC_SUPPORT_REF_NUM_OVER_MAX_DPB_SIZE, // Param: 0(Disable), 1(Enable)
    E_VDEC_EX_USER_CMD_RETURN_INVALID_AFD,              // Param: 0(Disable), 1(Enable)
    E_VDEC_EX_USER_CMD_FIELD_POLARITY_DISPLAY_ONE_FIELD,// Param : VDEC_EX_Field_Polarity
    E_VDEC_EX_USER_CMD_AVC_FORCE_BROKEN_BY_US,          // Param: 0(Disable), 1(Enable)
    E_VDEC_EX_USER_CMD_SHOW_FIRST_FRAME_DIRECT,         // Param: 0(Disable), 1(Enable), Push first frame to display queue directly..
    E_VDEC_EX_USER_CMD_AVC_RESIZE_DOS_DISP_PEND_BUF,    // Param:  size of AVC display pending buffer for display outside mode
    E_VDEC_EX_USER_CMD_SET_XC_LOW_DELAY_PARA,           // Param: arg0 for diff_field_number...
    E_VDEC_EX_USER_CMD_SET_SECURE_MODE,                 // Param: use enum VDEC_EX_SecureMode
    E_VDEC_EX_USER_CMD_RVU_SETTING_MODE,                // Param: 0(Disable), 1(drop B-frame and force IDR)
    E_VDEC_EX_USER_CMD_FRAMERATE_HANDLING,              // Arg 0~60000, 0: Disable, 1000 ~ 60000: Used the arg to set frame rate when the sequence did not have frame rate info. and arg is not zero. (The frame unit is (arg/1000)fps, Exp: 30000 = 30.000 fps), others: Do not thing.
    E_VDEC_EX_USER_CMD_DUAL_NON_BLOCK_MODE,             // Param: 0(Disable), 1(Enable)
    E_VDEC_EX_USER_CMD_IGNORE_PIC_STRUCT_DISPLAY,       // Param: 0(Disable), 1(Enable) Ignore Pic_struct when display progressive frame.
    E_VDEC_EX_USER_CMD_INPUT_PTS_FREERUN_MODE,          // Param: 0(Disable), 1(Enable) Video free run when the difference between input PTS and current STC is large than E_HVD_CMD_FREERUN_THRESHOLD + 1s;
    E_VDEC_EX_USER_CMD_ERR_CONCEAL_SLICE_1ST_MB,        // Param: 0(disable), Error concealment from current/last MB position; 1(enale) Error concealment from current slice first MB.(Need enable E_HVD_CMD_ERR_CONCEAL)
    E_VDEC_EX_USER_CMD_SET_EXTERNAL_DS_BUFFER,          // Param: External DS Buffer info.
    E_VDEC_EX_USER_CMD_SET_MIN_TSP_DATA_SIZE,           // Param: Resize HVD_FW_AVC_ES_MIN_TSP_DATA_SIZE
    E_VDEC_EX_USER_CMD_SET_DMX_FRAMERATE,
    E_VDEC_EX_USER_CMD_SET_DMX_FRAMERATEBASE,
    E_VDEC_EX_USER_CMD_ENABLE_CC_608_EXTERNAL_BUFFER,   // Param: u32_ccinfo 32bits-->([31:8]+[7:0] = addr+size), addr is kb unit, if u32_ccinfo ==0, it will turn off this feature
    E_VDEC_EX_USER_CMD_ENABLE_CC_708_EXTERNAL_BUFFER,   // Param: u32_ccinfo 32bits-->([31:8]+[7:0] = addr+size), addr is kb unit, if u32_ccinfo ==0, it will turn off this feature
    E_VDEC_EX_USER_CMD_SET_TIME_INC_PREDICT_PARA,
    E_VDEC_EX_USER_CMD_ENABLE_DECODE_ENGINE_TIMEOUT,    // Param: Enable/Disable decode timeout solution, timeout value unit:ms (VDEC_EX_Decode_Timeout_Param)
    E_VDEC_EX_USER_CMD_AUTO_FREE_ES,                    // Param: 0(Disable), 1(Enable)
    E_VDEC_EX_USER_CMD_FRAMEBUFFER_AUTO_MODE,           // Param: 0(Disable),1(Enable), this cmd is used for MVD.
    E_VDEC_EX_USER_CMD_SET_SMOOTH_REWIND,               // enable/disable or support smooth rewind
    E_VDEC_EX_USER_CMD_SET_ERROR_TOLERANCE,
    E_VDEC_EX_USER_CMD_AUTO_DROP_DISPLAY_QUEUE,         // Param: 0(Disable), N = 1~16: Drop display queue when display queue above than N frames.
    E_VDEC_EX_USER_CMD_USE_CPB_REMOVAL_DEALY,           // Param: 0(Disable), 1(Enable)
    E_VDEC_EX_USER_CMD_SKIP_N_FRAME,                    // Param: 0:disable, N = 1~63. Skip N frame.
    E_VDEC_EX_USER_CMD_SET_PTS_US_MODE,                 // Param: 1(enable), 0(disable ) PTS output by micro second level,
    E_VDEC_EX_USER_CMD_AUTO_INSERT_DUMMY_DATA,          // Param: 1(enable),0(disable), Enable/Disable utopia auto insert dummy pattern in SLQ/BBU mode.
    E_VDEC_EX_USER_CMD_DROP_ONE_PTS,
    E_VDEC_EX_USER_CMD_PVR_TIMESHIFT_SEAMLESS_MODE,
    E_VDEC_EX_USER_CMD_AUTO_REDUCE_ES_DATA,
    E_VDEC_EX_USER_CMD_RM_FORCE_MCU_MODE_ES,            // Param: 0(Disable), 1(Enable)
    E_VDEC_EX_USER_CMD_FORCE_PROGRESSIVE_MODE,          // Param: 1(enable),0(disable), Enable/Disable force progressive mode
    E_VDEC_EX_USER_CMD_SET_FRAMEBUFF2,                  // Param[0]=Addr and Param[1]=size for the second frame buffer

#if defined(UFO_PUBLIC_HEADER_700)
    E_VDEC_EX_USER_CMD_ENABLE_PTS_DECTECTOR,            // Param: 1(ON), 0(OFF)
    E_VDEC_EX_USER_CMD_SET_DV_XC_SHM_ADDR,              // Param: PHY Addr for communicating with XC Dolby Vision DM/Comp
    E_VDEC_EX_USER_CMD_SET_ENABLE_HDR,                  // Param: 0(Disable), 1(Enable)
    E_VDEC_EX_USER_CMD_DISABLE_PBFRAME_MODE,            // Param: 1(Disable), 0(Enable)
    E_VDEC_EX_USER_CMD_SET_DV_INFO,
    E_VDEC_EX_USER_CMD_SET_TRICKPLAY_2X_MODE,           // Param:0(vsync),1(avsync)
    E_VDEC_EX_USER_CMD_FRC_ONLY_SHOW_TOP_FIELD,         // Param: 0(Disable), 1(Enable) only show top filed for FRC mode
    E_VDEC_EX_USER_CMD_DIRECT_STC_MODE,                 // Param: stc in ms; 0x0~0x1FFFFFFFF/90, vdec fw use this value as stc; 0xFFFFFFFF, disable ths feature
    E_VDEC_EX_USER_CMD_DISABLE_ES_FULL_STOP,            // Param: 0(Enable), 1(Disable) ES FULL STOP mode
    E_VDEC_EX_USER_CMD_SET_SLOW_SYNC,
    E_VDEC_EX_USER_CMD_SET_DYNAMIC_DISP_PATH,
    E_VDEC_EX_USER_CMD_SET_AVSYNC_DISP_AUTO_DROP,
#endif
#if defined(UFO_PUBLIC_HEADER_500)
    E_VDEC_EX_USER_CMD_ENABLE_PTS_DECTECTOR,            // Param: 1(ON), 0(OFF)
    E_VDEC_EX_USER_CMD_SET_DV_XC_SHM_ADDR,              // Param: PHY Addr for communicating with XC Dolby Vision DM/Comp
    E_VDEC_EX_USER_CMD_SET_ENABLE_HDR,                  // Param: 0(Disable), 1(Enable)
    E_VDEC_EX_USER_CMD_DISABLE_PBFRAME_MODE,            // Param: 1(Disable), 0(Enable)
    E_VDEC_EX_USER_CMD_SET_SLOW_SYNC,                   // Param: VDEC_EX_Slow_Sync, u8RepeatPeriod: 0(disable), 1~0xFF(Repeat Period, repeat one every u8RepeatPeriod display),  u8DropPeriod: 0(disable), 1~0xFF(Drop Period, Drop one every u8DropPeriod display)
    E_VDEC_EX_USER_CMD_SET_DV_INFO,
    E_VDEC_EX_USER_CMD_SET_TRICKPLAY_2X_MODE,           //Param:0(vsync),1(avsync)
    E_VDEC_EX_USER_CMD_FRC_ONLY_SHOW_TOP_FIELD,
    E_VDEC_EX_USER_CMD_DIRECT_STC_MODE,
    E_VDEC_EX_USER_CMD_DISABLE_ES_FULL_STOP,
    E_VDEC_EX_USER_CMD_SET_AVSYNC_DISP_AUTO_DROP,
    E_VDEC_EX_USER_CMD_SET_DYNAMIC_DISP_PATH,
#endif
#if defined(UFO_PUBLIC_HEADER_500_3)
    E_VDEC_EX_USER_CMD_SET_TRICKPLAY_2X_MODE,           // Param:0(vsync),1(avsync)
    E_VDEC_EX_USER_CMD_FRC_ONLY_SHOW_TOP_FIELD,         // Param: 0(Disable), 1(Enable) only show top filed for FRC mode
    E_VDEC_EX_USER_CMD_DIRECT_STC_MODE,                 // Param: stc in ms; 0x0~0x1FFFFFFFF/90, vdec fw use this value as stc; 0xFFFFFFFF, disable ths feature
    E_VDEC_EX_USER_CMD_ENABLE_PTS_DECTECTOR,            // Param: 1(ON), 0(OFF) ,enable PTS detector mode
    E_VDEC_EX_USER_CMD_DISABLE_ES_FULL_STOP,            // Param: 0(Enable), 1(Disable) ES FULL STOP mode
    E_VDEC_EX_USER_CMD_SET_DV_XC_SHM_ADDR,              // Param: PHY Addr for communicating with XC Dolby Vision DM/Comp
    E_VDEC_EX_USER_CMD_SET_SLOW_SYNC,                   // Param: VDEC_EX_Slow_Sync, u8RepeatPeriod: 0(disable), 1~0xFF(Repeat Period, repeat one every u8RepeatPeriod display),  u8DropPeriod: 0(disable), 1~0xFF(Drop Period, Drop one every u8DropPeriod display)
    E_VDEC_EX_USER_CMD_SET_ENABLE_HDR,                  // Param: 0(Disable), 1(Enable)
    E_VDEC_EX_USER_CMD_DISABLE_PBFRAME_MODE,            // Param: 1(Disable), 0(Enable)
    E_VDEC_EX_USER_CMD_SET_DV_INFO,
    E_VDEC_EX_USER_CMD_SET_AVSYNC_DISP_AUTO_DROP,       // AV sync drop display frame
    E_VDEC_EX_USER_CMD_SET_DYNAMIC_DISP_PATH,           // Dynamic config for display path dip or mvop
#endif
#if defined(UFO_PUBLIC_HEADER_300)
    E_VDEC_EX_USER_CMD_ENABLE_PTS_DECTECTOR,            // Param: 1(ON), 0(OFF)
    E_VDEC_EX_USER_CMD_SET_AVSYNC_DISP_AUTO_DROP,
    E_VDEC_EX_USER_CMD_SET_DYNAMIC_DISP_PATH,
    E_VDEC_EX_USER_CMD_SET_DV_XC_SHM_ADDR,              // Param: PHY Addr for communicating with XC Dolby Vision DM/Comp
    E_VDEC_EX_USER_CMD_SET_TRICKPLAY_2X_MODE,           //Param:0(vsync),1(avsync)
    E_VDEC_EX_USER_CMD_SET_ENABLE_HDR,                  // Param: 0(Disable), 1(Enable)
    E_VDEC_EX_USER_CMD_DISABLE_PBFRAME_MODE,            // Param: 1(Disable), 0(Enable)
    E_VDEC_EX_USER_CMD_SET_DV_INFO,
    E_VDEC_EX_USER_CMD_FRC_ONLY_SHOW_TOP_FIELD,         // Param: 0(Disable), 1(Enable) only show top filed for FRC mode
    E_VDEC_EX_USER_CMD_DIRECT_STC_MODE,                 // Param: stc in ms; 0x0~0x1FFFFFFFF/90, vdec fw use this value as stc; 0xFFFFFFFF, disable ths feature
    E_VDEC_EX_USER_CMD_DISABLE_ES_FULL_STOP,            // Param: 0(Enable), 1(Disable) ES FULL STOP mode
    E_VDEC_EX_USER_CMD_SET_SLOW_SYNC,                   // Param: VDEC_EX_Slow_Sync, u8RepeatPeriod: 0(disable), 1~0xFF(Repeat Period, repeat one every u8RepeatPeriod display),  u8DropPeriod: 0(disable), 1~0xFF(Drop Period, Drop one every u8DropPeriod display)
#endif

#if defined(UFO_PUBLIC_HEADER_212)
    E_VDEC_EX_USER_CMD_SET_TRICKPLAY_2X_MODE,           //Param:0(vsync),1(avsync)
    E_VDEC_EX_USER_CMD_FRC_ONLY_SHOW_TOP_FIELD,   // Param: 0(Disable), 1(Enable) only show top filed for FRC mode
    E_VDEC_EX_USER_CMD_DISABLE_ES_FULL_STOP,      // Param: 0(Enable), 1(Disable) ES FULL STOP mode
    E_VDEC_EX_USER_CMD_DIRECT_STC_MODE,                 // Param: stc in ms; 0x0~0x1FFFFFFFF/90, vdec fw use this value as stc; 0xFFFFFFFF, disable ths feature
    E_VDEC_EX_USER_CMD_ENABLE_PTS_DECTECTOR,            // Param: 1(ON), 0(OFF)
    E_VDEC_EX_USER_CMD_SET_SLOW_SYNC,              //Param: VDEC_EX_Slow_Sync, u8RepeatPeriod: 0(disable), 1~0xFF(Repeat Period, repeat one every u8RepeatPeriod display),  u8DropPeriod: 0(disable), 1~0xFF(Drop Period, Drop one every u8DropPeriod display)
    E_VDEC_EX_USER_CMD_SET_ENABLE_HDR,
    E_VDEC_EX_USER_CMD_DISABLE_PBFRAME_MODE,
    E_VDEC_EX_USER_CMD_SET_DV_XC_SHM_ADDR,
    E_VDEC_EX_USER_CMD_SET_DV_INFO,
    E_VDEC_EX_USER_CMD_SET_AVSYNC_DISP_AUTO_DROP,
    E_VDEC_EX_USER_CMD_SET_DYNAMIC_DISP_PATH,
#endif
    E_VDEC_EX_USER_CMD_SET_CODEC_CONFIG,			//setip codec type for vp9
    E_VDEC_EX_USER_CMD_ENABLE_QOS_INFO,                        // Enable VDEC FW to calculate qos info
    E_VDEC_EX_USER_CMD_ADJUST_DECODER_FREQUENCY,           // VDEC_EX_Decoder_Frequency;  VDEC_EX_DECODER_FREQUENCY_DOWN, VDEC_EX_DECODER_FREQUENCY_UP, VDEC_EX_DECODER_FREQUENCY_MAX, VDEC_EX_DECODER_FREQUENCY_MIN

    E_VDEC_EX_USER_CMD_MVC_SET_CMD_BASE  = 0x0800,
    E_VDEC_EX_USER_CMD_MVC_BBU2_PUSH_PACKET,            // Param: Packet Info.
    E_VDEC_EX_USER_CMD_MVC_BBU2_FIRE_DECCMD,            // Param: Non

    E_VDEC_EX_USER_CMD_UT_SET_CMD_BASE = 0x0900,
    E_VDEC_EX_USER_CMD_UT_SET_DBG_MODE,                    // Param: for enable the specify dbg mode for UT
    E_VDEC_EX_USER_CMD_UT_CLR_DBG_MODE,                    // Param: for disable the specify dbg mode for UT

    //Group2:Get Control command================================
    E_VDEC_EX_USER_CMD_GET_CONTROL_BASE  = 0x1000,
    E_VDEC_EX_USER_CMD_GET_CHROMA_TYPE,
    E_VDEC_EX_USER_CMD_GET_REAL_FRAMERATE,              // Get Real FrameRate reported by decoder
    E_VDEC_EX_USER_CMD_GET_COLOR_MATRIX,                // Get color matrix coefficients reported by decoder
    E_VDEC_EX_USER_CMD_GET_MAIN_STREAM_ID,              // Get activated main stream ID
    E_VDEC_EX_USER_CMD_GET_SUB_STREAM_ID,               // Get activated sub stream ID
    E_VDEC_EX_USER_CMD_GET_DYNSCALE_ENABLED,
    E_VDEC_EX_USER_CMD_GET_FPA_SEI,                     //Get SEI info
    E_VDEC_EX_USER_CMD_GET_U64PTS,
    E_VDEC_EX_USER_CMD_GET_ORI_INTERLACE_MODE,
    E_VDEC_EX_USER_CMD_GET_MBS_ONLY_FLAG,
    E_VDEC_EX_USER_CMD_GET_CRC_VALUE,                   //Get frame Y/UV crc value
    E_VDEC_EX_USER_CMD_GET_BBU_Q_NUM,
    E_VDEC_EX_USER_CMD_GET_DISP_FRAME_NUM,
    E_VDEC_EX_USER_CMD_GET_FPA_SEI_EX,                  //Get SEI info(enhancement)
    E_VDEC_EX_USER_CMD_GET_ES_BUFFER_STATUS,            //Get ES buffer over/under flow status
    E_VDEC_EX_USER_CMD_GET_CODEC_TYPE,                  // Get Codec type
    E_VDEC_EX_USER_CMD_GET_SHAREMEMORY_BASE,
    E_VDEC_EX_USER_CMD_GET_IS_LEAST_DISPQ_SIZE_FLAG,
    E_VDEC_EX_USER_CMD_GET_FIELD_PIC_FLAG,              // Param: Get Field Pic Flag
    E_VDEC_EX_USER_CMD_GET_SUPPORT_2ND_MVOP_INTERFACE,  // Param: TRUE : support, FALSE : not support
    E_VDEC_EX_USER_CMD_GET_FB_USAGE_MEM,                // Get FrameBuufer Size needed by decoder
    E_VDEC_EX_USER_CMD_GET_XC_LOW_DELAY_INT_STATE,      // Get xc_low_delay int state...
    E_VDEC_EX_USER_CMD_GET_VSYNC_BRIDGE_ADDR,
    E_VDEC_EX_USER_CMD_GET_FRAME_INFO_EX,
    E_VDEC_EX_USER_CMD_GET_FLUSH_PATTEN_ENTRY_NUM,
    E_VDEC_EX_USER_CMD_GET_DS_BUF_MIU_SEL,              //For those chips which has 3 MIU, use this get control to get correct miu select of DS buffer
    E_VDEC_EX_USER_CMD_GET_FW_STATUS_FLAG,
    E_VDEC_EX_USER_CMD_GET_HW_MAX_PIXEL,
#if defined(UFO_PUBLIC_HEADER_700)
    E_VDEC_EX_USER_CMD_GET_FLOW_CONTROL_U64PTS_DIFF,    // based on PTS table Rdptr and Wrptr, support TSP mode only
    E_VDEC_EX_USER_CMD_GET_NEXT_DISP_FRAME_INFO_EXT,    // replace of E_VDEC_EX_USER_CMD_GET_FRAME_INFO_EX
    E_VDEC_EX_USER_CMD_GET_VSYNC_BRIDGE_EXT_ADDR,       //get vsync bridge ext addr
    E_VDEC_EX_USER_CMD_GET_DCV_SEI,
    E_VDEC_EX_USER_CMD_GET_VUI_DISP_INFO,
    E_VDEC_EX_USER_CMD_GET_CODEC_CAP,
    E_VDEC_EX_USER_CMD_GET_PRE_PAS_U64PTS,                  //Get Pre-parsing PTS
    E_VDEC_EX_USER_CMD_GET_CLLI_SEI,                    //Content light level Info
    E_VDEC_EX_USER_CMD_GET_PVRSEAMLESS_INFO,
    E_VDEC_EX_USER_CMD_GET_SEQ_CHANGE_INFO,             // Get the reason why seq changes, parameter is MS_U32, definition is VDEC_EX_SeqChangeInfo
    E_VDEC_EX_USER_CMD_GET_DISP_QUEUE_EMPTY,
    E_VDEC_EX_USER_CMD_GET_NOT_SUPPORT_INFO,
    E_VDEC_EX_USER_CMD_GET_BUFFER_INFO,                        // Param: VDEC_EX_BufferInfo
    E_VDEC_EX_USER_CMD_GET_MIN_TSP_DATA_SIZE,   //Get Min tsp data size from FW side  ,avoid data no enough case in PVR mode
#endif
#if defined(UFO_PUBLIC_HEADER_500)
    E_VDEC_EX_USER_CMD_GET_FLOW_CONTROL_U64PTS_DIFF,    // based on PTS table Rdptr and Wrptr, support TSP mode only
    E_VDEC_EX_USER_CMD_GET_NEXT_DISP_FRAME_INFO_EXT,    // replace of E_VDEC_EX_USER_CMD_GET_FRAME_INFO_EX
    E_VDEC_EX_USER_CMD_GET_VSYNC_BRIDGE_EXT_ADDR,       //get vsync bridge ext addr
    E_VDEC_EX_USER_CMD_GET_DCV_SEI,
    E_VDEC_EX_USER_CMD_GET_VUI_DISP_INFO,
    E_VDEC_EX_USER_CMD_GET_CODEC_CAP,
    E_VDEC_EX_USER_CMD_GET_PRE_PAS_U64PTS,              //Get Pre-parsing PTS
    E_VDEC_EX_USER_CMD_GET_CLLI_SEI,                    //Content light level Info
    E_VDEC_EX_USER_CMD_GET_SEQ_CHANGE_INFO,             // Get the reason why seq changes, parameter is MS_U32, definition is VDEC_EX_SeqChangeInfo
    E_VDEC_EX_USER_CMD_GET_PVRSEAMLESS_INFO,
    E_VDEC_EX_USER_CMD_GET_DISP_QUEUE_EMPTY,
    E_VDEC_EX_USER_CMD_GET_NOT_SUPPORT_INFO,
    E_VDEC_EX_USER_CMD_GET_BUFFER_INFO,                 // Param: VDEC_EX_BufferInfo
    E_VDEC_EX_USER_CMD_GET_MIN_TSP_DATA_SIZE,   //Get Min tsp data size from FW side  ,avoid data no enough case in PVR mode
#endif
#if defined(UFO_PUBLIC_HEADER_500_3)
    E_VDEC_EX_USER_CMD_GET_FLOW_CONTROL_U64PTS_DIFF,    // based on PTS table Rdptr and Wrptr, support TSP mode only
    E_VDEC_EX_USER_CMD_GET_NEXT_DISP_FRAME_INFO_EXT,    // replace of E_VDEC_EX_USER_CMD_GET_FRAME_INFO_EX
    E_VDEC_EX_USER_CMD_GET_VSYNC_BRIDGE_EXT_ADDR,       //get vsync bridge ext addr
    E_VDEC_EX_USER_CMD_GET_DCV_SEI,
    E_VDEC_EX_USER_CMD_GET_VUI_DISP_INFO,
    E_VDEC_EX_USER_CMD_GET_CODEC_CAP,
    E_VDEC_EX_USER_CMD_GET_PRE_PAS_U64PTS,              //Get Pre-parsing PTS
    E_VDEC_EX_USER_CMD_GET_PVRSEAMLESS_INFO,
    E_VDEC_EX_USER_CMD_GET_CLLI_SEI,                    //Content light level Info
    E_VDEC_EX_USER_CMD_GET_SEQ_CHANGE_INFO,             // Get the reason why seq changes, parameter is MS_U32, definition is VDEC_EX_SeqChangeInfo
    E_VDEC_EX_USER_CMD_GET_DISP_QUEUE_EMPTY,
    E_VDEC_EX_USER_CMD_GET_NOT_SUPPORT_INFO,
    E_VDEC_EX_USER_CMD_GET_MIN_TSP_DATA_SIZE,   //Get Min tsp data size from FW side  ,avoid data no enough case in PVR mode
    E_VDEC_EX_USER_CMD_GET_BUFFER_INFO,                 // Param: VDEC_EX_BufferInfo
#endif
#if defined(UFO_PUBLIC_HEADER_300)
    E_VDEC_EX_USER_CMD_GET_VSYNC_BRIDGE_EXT_ADDR,       //get vsync bridge ext addr
    E_VDEC_EX_USER_CMD_GET_FLOW_CONTROL_U64PTS_DIFF,    // based on PTS table Rdptr and Wrptr, support TSP mode only
    E_VDEC_EX_USER_CMD_GET_PRE_PAS_U64PTS,               //Get Pre-parsing PTS
    E_VDEC_EX_USER_CMD_GET_SEQ_CHANGE_INFO,             // Get the reason why seq changes, parameter is MS_U32, definition is VDEC_EX_SeqChangeInfo
    E_VDEC_EX_USER_CMD_GET_NEXT_DISP_FRAME_INFO_EXT,    // replace of E_VDEC_EX_USER_CMD_GET_FRAME_INFO_EX
    E_VDEC_EX_USER_CMD_GET_CODEC_CAP,
    E_VDEC_EX_USER_CMD_GET_DCV_SEI,
    E_VDEC_EX_USER_CMD_GET_VUI_DISP_INFO,
    E_VDEC_EX_USER_CMD_GET_CLLI_SEI,                    //Content light level Info
    E_VDEC_EX_USER_CMD_GET_PVRSEAMLESS_INFO,
    E_VDEC_EX_USER_CMD_GET_DISP_QUEUE_EMPTY,
    E_VDEC_EX_USER_CMD_GET_NOT_SUPPORT_INFO,
    E_VDEC_EX_USER_CMD_GET_BUFFER_INFO,                 // Param: VDEC_EX_BufferInfo
    E_VDEC_EX_USER_CMD_GET_MIN_TSP_DATA_SIZE,   //Get Min tsp data size from FW side  ,avoid data no enough case in PVR mode
#endif
#if defined(UFO_PUBLIC_HEADER_212)
    E_VDEC_EX_USER_CMD_GET_PVRSEAMLESS_INFO,
    E_VDEC_EX_USER_CMD_GET_FLOW_CONTROL_U64PTS_DIFF,    // based on PTS table Rdptr and Wrptr, support TSP mode only
    E_VDEC_EX_USER_CMD_GET_PRE_PAS_U64PTS,              // Get Pre-parsing PTS
    E_VDEC_EX_USER_CMD_GET_NEXT_DISP_FRAME_INFO_EXT,    // replace of E_VDEC_EX_USER_CMD_GET_FRAME_INFO_EX
    E_VDEC_EX_USER_CMD_GET_VSYNC_BRIDGE_EXT_ADDR,       //get vsync bridge ext addr
    E_VDEC_EX_USER_CMD_GET_DCV_SEI,
    E_VDEC_EX_USER_CMD_GET_VUI_DISP_INFO,
    E_VDEC_EX_USER_CMD_GET_CODEC_CAP,
    E_VDEC_EX_USER_CMD_GET_SEQ_CHANGE_INFO,             // Get the reason why seq changes, parameter is MS_U32, definition is VDEC_EX_SeqChangeInfo
    E_VDEC_EX_USER_CMD_GET_NOT_SUPPORT_INFO,
    E_VDEC_EX_USER_CMD_GET_MIN_TSP_DATA_SIZE,
    E_VDEC_EX_USER_CMD_GET_CLLI_SEI,
    E_VDEC_EX_USER_CMD_GET_DISP_QUEUE_EMPTY,
    E_VDEC_EX_USER_CMD_GET_BUFFER_INFO, // Param: VDEC_EX_BufferInfo
#endif
    E_VDEC_EX_USER_CMD_GET_NEXT_DISP_FRAME_QOS_INFO,  // Get qos info
    E_VDEC_EX_USER_CMD_GET_SEQ_INFO,  //Get sequence header info
    E_VDEC_EX_USER_CMD_GET_EXTEND_DISP_INFO,            // Get ExtendDispInfo

    //MVC Get Control command================================
    E_VDEC_EX_USER_CMD_MVC_GET_CMD_BASE  = 0x1800,
    E_VDEC_EX_USER_CMD_GET_MVC_SUB_FRAME_DISP_INFO,     // Param: VDEC_FrameInfo pointer.
    E_VDEC_EX_USER_CMD_GET_MVC_BBU2_DECQ_VACANCY,       // Param: BBU2 Dec Q Vacancy.
    E_VDEC_EX_USER_CMD_GET_MVC_ES2_READ_PTR,            // Param: ES2 read pointer.
    E_VDEC_EX_USER_CMD_GET_MVC_ES2_WRITE_PTR,           // Param: ES2 Write pointer.
    E_VDEC_EX_USER_CMD_GET_ES_QUANTITY,                 // Param: Get ES buffer Level.
    E_VDEC_EX_USER_CMD_GET_ES2_QUANTITY,                // Param: Get ES2 buffer Level.


    //Group3:System Preset Control command======================
    //Group3-1:Common system Preset Control command
    E_VDEC_EX_USER_CMD_SYSTEM_PRESET_CONTROL_BASE   = 0x2000,
    E_VDEC_EX_USER_CMD_SYSTEM_PRESET_VPU_CLOCK,         //Param: VDEC_EX_ClockSpeed

    //Group3-2:HVD System Preset Control command
    E_VDEC_EX_USER_CMD_SYSTEM_PRESET_HVD_BASE       = 0x2100,
    E_VDEC_EX_USER_CMD_SYSTEM_PRESET_HVD_CLOCK,         //Param: VDEC_EX_ClockSpeed

    //Group3-3:MVD System Preset Control command
    E_VDEC_EX_USER_CMD_SYSTEM_PRESET_MVD_BASE       = 0x2200,
    E_VDEC_EX_USER_CMD_SYSTEM_PRESET_MVD_CLOCK,         //Param: VDEC_EX_ClockSpeed
    E_VDEC_EX_USER_CMD_VPU_SECURITY_MODE,               //Param: 0:disable,1:enable

    //Group3-4:Preset Control command=============================
    E_VDEC_EX_USER_CMD_PRESET_CONTROL_BASE          = 0x2300,
    E_VDEC_EX_USER_CMD_HVD_ONE_PENDING_BUFFER_MODE,  //Param: 0(Disable), 1(Enable), use only one pending buffer instead of two for HVD
    E_VDEC_EX_USER_CMD_MVD_HWBUFFER_REMAPPING_MODE,  //Param: 0(Disable), 1(Enable),Allcate HW buffer to start of frame buffer
    E_VDEC_EX_USER_CMD_SET_SHAREMEMORY_BASE,
    E_VDEC_EX_USER_CMD_HVD_COL_BBU_MODE,                //Param: HVD use colocated BBU mode, 0: disable, 1: enable /*johnny.ko*/
    E_VDEC_EX_USER_CMD_HVD_IAPGN_BUF_SHARE_BW_MODE,     //Param: HVD IAP GN Buffer address,
    /***/E_VDEC_EX_USER_CMD_DTV_DEBUG_MODE,
    E_VDEC_EX_USER_CMD_HVD_TS_IN_BBU_MODE,
    E_VDEC_EX_USER_CMD_AUTO_ARRANGE_FRAMEBUFFER_USAGE,  //Param: 0:disable,1:enable, address:PA,size:unit is byte
    E_VDEC_EX_USER_CMD_THUMBNAIL_MODE,                  //Param: 0(Disable), 1(Enable), use small frame buffer to decdoe thumbnail
    E_VDEC_EX_USER_CMD_FORCE_8BIT_DEC_MODE,             //Param: force 8bit decode mode, 0: disable, 1: enable
#if defined(UFO_PUBLIC_HEADER_700)
    E_VDEC_EX_USER_CMD_MFCODEC_MODE,                    //Param: VDEC_EX_MFCodec_mode
    E_VDEC_EX_USER_CMD_VDEC_FEATURE,                 //AP control VDEC features
    E_VDEC_EX_USER_CMD_DYNAMIC_CMA_MODE,             //enable dynamic cma features
    E_VDEC_EX_USER_CMD_CONNECT_INPUT_TSP,               //Param: VDEC_EX_INPUT_TSP, 0(Disable), 1(TSP 0)
    E_VDEC_EX_USER_CMD_CONNECT_DISPLAY_PATH,            //Param: 0(display by DIP), 1(MVOP MAIN), 2(MVOP SUB)
    E_VDEC_EX_USER_CMD_SET_DISPLAY_MODE,                //Param: 0(MCU MODE), 1(HARDWIRE)
    E_VDEC_EX_USER_CMD_BITSTREAMBUFFER_MONOPOLY,        //Param: TRUE : support, FALSE : not support
    E_VDEC_EX_USER_CMD_FRAMEBUFFER_MONOPOLY,            //Param: TRUE : support, FALSE : not support
    E_VDEC_EX_USER_CMD_SPECIFY_TASK_SPEC,               //Param: VDEC_EX_TASK_SPEC
    E_VDEC_EX_USER_CMD_SET_TOTALRANGE_BITSTREAMBUFFER,  //Param: VDEC_EX_TotalBufRange
    E_VDEC_EX_USER_CMD_SET_TOTALRANGE_FRAMEBUFFER1,     //Param: VDEC_EX_TotalBufRange
    E_VDEC_EX_USER_CMD_SET_TOTALRANGE_FRAMEBUFFER2,     //Param: VDEC_EX_TotalBufRange
    E_VDEC_EX_USER_CMD_PRESET_STC,                      //set STC index
    E_VDEC_EX_USER_CMD_CAL_FRAMERATE,
#endif
#if (defined(UFO_PUBLIC_HEADER_500)||defined(UFO_PUBLIC_HEADER_500_3))
    E_VDEC_EX_USER_CMD_MFCODEC_MODE,                    //Param: VDEC_EX_MFCodec_mode
    E_VDEC_EX_USER_CMD_VDEC_FEATURE,                 //AP control VDEC features
    E_VDEC_EX_USER_CMD_DYNAMIC_CMA_MODE,             //enable dynamic cma features
    E_VDEC_EX_USER_CMD_CONNECT_INPUT_TSP,               //Param: VDEC_EX_INPUT_TSP, 0(Disable), 1(TSP 0)
    E_VDEC_EX_USER_CMD_CONNECT_DISPLAY_PATH,            //Param: 0(display by DIP), 1(MVOP MAIN), 2(MVOP SUB)
    E_VDEC_EX_USER_CMD_SET_DISPLAY_MODE,                //Param: 0(MCU MODE), 1(HARDWIRE)
    E_VDEC_EX_USER_CMD_BITSTREAMBUFFER_MONOPOLY,        //Param: TRUE : support, FALSE : not support
    E_VDEC_EX_USER_CMD_FRAMEBUFFER_MONOPOLY,            //Param: TRUE : support, FALSE : not support
    E_VDEC_EX_USER_CMD_SPECIFY_TASK_SPEC,               //Param: VDEC_EX_TASK_SPEC
    E_VDEC_EX_USER_CMD_PRESET_STC,                      //set STC index
    E_VDEC_EX_USER_CMD_CAL_FRAMERATE,                   //Param: 0(Disable), 1(Enable)
    E_VDEC_EX_USER_CMD_SET_TOTALRANGE_BITSTREAMBUFFER,  //Param: VDEC_EX_TotalBufRange
    E_VDEC_EX_USER_CMD_SET_TOTALRANGE_FRAMEBUFFER1,     //Param: VDEC_EX_TotalBufRange
    E_VDEC_EX_USER_CMD_SET_TOTALRANGE_FRAMEBUFFER2,     //Param: VDEC_EX_TotalBufRange
#endif
#if defined(UFO_PUBLIC_HEADER_300)
    E_VDEC_EX_USER_CMD_CONNECT_DISPLAY_PATH,            //Param: 0(display by DIP), 1(MVOP MAIN), 2(MVOP SUB)
    E_VDEC_EX_USER_CMD_CONNECT_INPUT_TSP,               //Param: VDEC_EX_INPUT_TSP, 0(Disable), 1(TSP 0)
    E_VDEC_EX_USER_CMD_SET_DISPLAY_MODE,                //Param: 0(MCU MODE), 1(HARDWIRE)
    E_VDEC_EX_USER_CMD_BITSTREAMBUFFER_MONOPOLY,        //Param: TRUE : support, FALSE : not support
    E_VDEC_EX_USER_CMD_FRAMEBUFFER_MONOPOLY,            //Param: TRUE : support, FALSE : not support
    E_VDEC_EX_USER_CMD_SPECIFY_TASK_SPEC,               //Param: VDEC_EX_TASK_SPEC
    E_VDEC_EX_USER_CMD_SET_TOTALRANGE_BITSTREAMBUFFER,  //Param: VDEC_EX_TotalBufRange
    E_VDEC_EX_USER_CMD_SET_TOTALRANGE_FRAMEBUFFER1,     //Param: VDEC_EX_TotalBufRange
    E_VDEC_EX_USER_CMD_SET_TOTALRANGE_FRAMEBUFFER2,     //Param: VDEC_EX_TotalBufRange
    E_VDEC_EX_USER_CMD_CAL_FRAMERATE,                   //Param: 0(Disable), 1(Enable)
    E_VDEC_EX_USER_CMD_VDEC_FEATURE,                 //AP control VDEC features
    E_VDEC_EX_USER_CMD_DYNAMIC_CMA_MODE,             //enable dynamic cma features
    E_VDEC_EX_USER_CMD_MFCODEC_MODE,
    E_VDEC_EX_USER_CMD_PRESET_STC,
#endif
#if defined(UFO_PUBLIC_HEADER_212)
    E_VDEC_EX_USER_CMD_MFCODEC_MODE,                    //Param: VDEC_EX_MFCodec_mode
    E_VDEC_EX_USER_CMD_VDEC_FEATURE,                 //AP control VDEC features
    E_VDEC_EX_USER_CMD_DYNAMIC_CMA_MODE,             //enable dynamic cma features
    E_VDEC_EX_USER_CMD_CONNECT_DISPLAY_PATH,            //Param: 0(display by DIP), 1(MVOP MAIN), 2(MVOP SUB)
    E_VDEC_EX_USER_CMD_CONNECT_INPUT_TSP,               //Param: VDEC_EX_INPUT_TSP, 0(Disable), 1(TSP 0)
    E_VDEC_EX_USER_CMD_SET_DISPLAY_MODE,                //Param: 0(MCU MODE), 1(HARDWIRE)
    E_VDEC_EX_USER_CMD_BITSTREAMBUFFER_MONOPOLY,        //Param: TRUE : support, FALSE : not support
    E_VDEC_EX_USER_CMD_FRAMEBUFFER_MONOPOLY,            //Param: TRUE : support, FALSE : not support
    E_VDEC_EX_USER_CMD_SPECIFY_TASK_SPEC,               //Param: VDEC_EX_TASK_SPEC
    E_VDEC_EX_USER_CMD_PRESET_STC,
    E_VDEC_EX_USER_CMD_CAL_FRAMERATE,                   //Param: 0(Disable), 1(Enable)
    E_VDEC_EX_USER_CMD_SET_TOTALRANGE_BITSTREAMBUFFER,  //Param: VDEC_EX_TotalBufRange
    E_VDEC_EX_USER_CMD_SET_TOTALRANGE_FRAMEBUFFER1,     //Param: VDEC_EX_TotalBufRange
    E_VDEC_EX_USER_CMD_SET_TOTALRANGE_FRAMEBUFFER2,     //Param: VDEC_EX_TotalBufRange
#endif
    E_VDEC_EX_USER_CMD_SET_BUFFER_INFO,                 // Set specific buffer (VDEC_EX_BufferType) info
    E_VDEC_EX_USER_CMD_HDR10_UPDATE_PERFRAME,   // update hdr10 info per frame
    E_VDEC_EX_USER_CMD_SET_VP94K2KCHECK,             // Param : 1(enable) 4k2k file not supported
    E_VDEC_EX_USER_CMD_SET_CUSTOMER_MODE,               //Param: VDEC_EX_Customer_Mode. For specific customer behavior

    //Group4:System Postset Control command======================
    E_VDEC_EX_USER_CMD_SYSTEM_POSTSET_CONTROL_BASE  = 0x3000,
    E_VDEC_EX_USER_CMD_SYSTEM_POSTSET_CLEAR_PROCESS_RELATED,

    //Group5:System PreGet Control command======================
    //Group5-1:Common system Preget Control command
    E_VDEC_EX_USER_CMD_SYSTEM_PREGET_CONTROL_BASE  = 0x4000,
    E_VDEC_EX_USER_CMD_SYSTEM_PREGET_FB_MEMORY_USAGE_SIZE,


    E_VDEC_EX_USER_CMD_SYSTEM_PREGET_DV_SUPPORT_PROFILE,
    E_VDEC_EX_USER_CMD_SYSTEM_PREGET_DV_SUPPORT_LEVEL,


} VDEC_EX_User_Cmd;

//VDEC FW TYPE
typedef enum
{
    E_VDEC_EX_FW_TYPE_MVD = 0,
    E_VDEC_EX_FW_TYPE_HVD,
} VDEC_EX_FwType;

/// DecodeMode for f/w tasks
typedef enum
{
    E_VDEC_EX_DEC_MODE_DUAL_INDIE = 0,                     ///< Two independent tasks
    E_VDEC_EX_DEC_MODE_DUAL_3D,                        ///< Two dependent tasks for 3D
    E_VDEC_EX_DEC_MODE_SINGLE,                         ///< One task use the whole SRAM
    E_VDEC_EX_DEC_MODE_MVC = E_VDEC_EX_DEC_MODE_SINGLE,
} VDEC_EX_DEC_MODE;


typedef enum
{
    E_VDEC_EX_CODEC_PROFILE_NONE,

    E_VDEC_EX_CODEC_PROFILE_MP2_MAIN,

    E_VDEC_EX_CODEC_PROFILE_MP4_ASP,

    E_VDEC_EX_CODEC_PROFILE_H263_BASELINE,

    E_VDEC_EX_CODEC_PROFILE_VC1_AP,

    E_VDEC_EX_CODEC_PROFILE_RCV_MAIN,

    E_VDEC_EX_CODEC_PROFILE_VP9_0,
    E_VDEC_EX_CODEC_PROFILE_VP9_2,

    E_VDEC_EX_CODEC_PROFILE_H264_CBP,
    E_VDEC_EX_CODEC_PROFILE_H264_BP,
    E_VDEC_EX_CODEC_PROFILE_H264_XP,
    E_VDEC_EX_CODEC_PROFILE_H264_MP,
    E_VDEC_EX_CODEC_PROFILE_H264_HIP,
    E_VDEC_EX_CODEC_PROFILE_H264_PHIP,
    E_VDEC_EX_CODEC_PROFILE_H264_CHIP,
    E_VDEC_EX_CODEC_PROFILE_H264_HI10P,
    E_VDEC_EX_CODEC_PROFILE_H264_HI422P,
    E_VDEC_EX_CODEC_PROFILE_H264_HI444PP,

    E_VDEC_EX_CODEC_PROFILE_H265_MAIN,
    E_VDEC_EX_CODEC_PROFILE_H265_MAIN_10,
    E_VDEC_EX_CODEC_PROFILE_H265_MAIN_12,
    E_VDEC_EX_CODEC_PROFILE_H265_MAIN_422_10,
    E_VDEC_EX_CODEC_PROFILE_H265_MAIN_422_12,
    E_VDEC_EX_CODEC_PROFILE_H265_MAIN_444,
    E_VDEC_EX_CODEC_PROFILE_H265_MAIN_444_10,
    E_VDEC_EX_CODEC_PROFILE_H265_MAIN_444_12,


} VDEC_EX_CODEC_CAP_PROFILE_INFO;

typedef enum
{
    E_VDEC_EX_CODEC_LEVEL_NONE,

    E_VDEC_EX_CODEC_LEVEL_MP2_HIGH,

    E_VDEC_EX_CODEC_LEVEL_MP4_L5,

    E_VDEC_EX_CODEC_LEVEL_VC1_L3,

    E_VDEC_EX_CODEC_LEVEL_RCV_HIGH,


    E_VDEC_EX_CODEC_LEVEL_H264_1,
    E_VDEC_EX_CODEC_LEVEL_H264_1B,
    E_VDEC_EX_CODEC_LEVEL_H264_1_1,
    E_VDEC_EX_CODEC_LEVEL_H264_1_2,
    E_VDEC_EX_CODEC_LEVEL_H264_1_3,
    E_VDEC_EX_CODEC_LEVEL_H264_2,
    E_VDEC_EX_CODEC_LEVEL_H264_2_1,
    E_VDEC_EX_CODEC_LEVEL_H264_2_2,
    E_VDEC_EX_CODEC_LEVEL_H264_3,
    E_VDEC_EX_CODEC_LEVEL_H264_3_1,
    E_VDEC_EX_CODEC_LEVEL_H264_3_2,
    E_VDEC_EX_CODEC_LEVEL_H264_4,
    E_VDEC_EX_CODEC_LEVEL_H264_4_1,
    E_VDEC_EX_CODEC_LEVEL_H264_4_2,
    E_VDEC_EX_CODEC_LEVEL_H264_5,
    E_VDEC_EX_CODEC_LEVEL_H264_5_1,
    E_VDEC_EX_CODEC_LEVEL_H264_5_2,

    E_VDEC_EX_CODEC_LEVEL_H265_1,
    E_VDEC_EX_CODEC_LEVEL_H265_2,
    E_VDEC_EX_CODEC_LEVEL_H265_2_1,
    E_VDEC_EX_CODEC_LEVEL_H265_3,
    E_VDEC_EX_CODEC_LEVEL_H265_3_1,
    E_VDEC_EX_CODEC_LEVEL_H265_4_MT,
    E_VDEC_EX_CODEC_LEVEL_H265_4_HT,
    E_VDEC_EX_CODEC_LEVEL_H265_4_1_MT,
    E_VDEC_EX_CODEC_LEVEL_H265_4_1_HT,
    E_VDEC_EX_CODEC_LEVEL_H265_5_MT,
    E_VDEC_EX_CODEC_LEVEL_H265_5_HT,
    E_VDEC_EX_CODEC_LEVEL_H265_5_1_MT,
    E_VDEC_EX_CODEC_LEVEL_H265_5_1_HT,
    E_VDEC_EX_CODEC_LEVEL_H265_5_2_MT,
    E_VDEC_EX_CODEC_LEVEL_H265_5_2_HT,
    E_VDEC_EX_CODEC_LEVEL_H265_6_MT,
    E_VDEC_EX_CODEC_LEVEL_H265_6_HT,
    E_VDEC_EX_CODEC_LEVEL_H265_6_1_MT,
    E_VDEC_EX_CODEC_LEVEL_H265_6_1_HT,
    E_VDEC_EX_CODEC_LEVEL_H265_6_2_MT,
    E_VDEC_EX_CODEC_LEVEL_H265_6_2_HT

} VDEC_EX_CODEC_CAP_LEVEL_INFO;


typedef enum
{
    E_VDEC_EX_CODEC_VERSION_NONE,

    E_VDEC_EX_CODEC_VERSION_DIVX_311,
    E_VDEC_EX_CODEC_VERSION_DIVX_4,
    E_VDEC_EX_CODEC_VERSION_DIVX_5,
    E_VDEC_EX_CODEC_VERSION_DIVX_6,

    E_VDEC_EX_CODEC_VERSION_FLV_1,

    E_VDEC_EX_CODEC_VERSION_H263_1,

} VDEC_EX_CODEC_CAP_VERSION_INFO;


#ifdef VDEC_CAP_DV_OTT_API
typedef enum
{
    E_VDEC_EX_DV_META_REORDER_DEFAULT,
    E_VDEC_EX_DV_META_REORDER_FOLLOW_BL,
    E_VDEC_EX_DV_META_REORDER_FOLLOW_EL,
} VDEC_EX_DV_METADATA_REORDER;

typedef enum
{
    E_VDEC_EX_GET_DV_SUPPORT_PROFILE = 0,
    E_VDEC_EX_GET_DV_SUPPORT_LEVEL,
    E_VDEC_EX_SET_DV_INFO,//set profile and level
} VDEC_EX_DV_CMD_TYPE;

typedef enum
{
    E_VDEC_EX_DV_STREAM_PROFILE_ID_UNSUPPORTED = 0x0,
    E_VDEC_EX_DV_STREAM_PROFILE_ID_DVAV_PER    = 0x1,
    E_VDEC_EX_DV_STREAM_PROFILE_ID_DVAV_PEN    = 0x2,
    E_VDEC_EX_DV_STREAM_PROFILE_ID_DVHE_DER    = 0x4,
    E_VDEC_EX_DV_STREAM_PROFILE_ID_DVHE_DEN    = 0x8,
    E_VDEC_EX_DV_STREAM_PROFILE_ID_DVHE_DTR    = 0x10,
    E_VDEC_EX_DV_STREAM_PROFILE_ID_DVHE_STN    = 0x20,
    E_VDEC_EX_DV_STREAM_PROFILE_ID_DVHE_DTH    = 0x40,
} VDEC_EX_DV_Stream_Profile;

typedef enum
{
    E_VDEC_EX_DV_STREAM_LEVEL_ID_UNSUPPORTED = 0,
    E_VDEC_EX_DV_STREAM_LEVEL_ID_HD24,
    E_VDEC_EX_DV_STREAM_LEVEL_ID_HD30,
    E_VDEC_EX_DV_STREAM_LEVEL_ID_FHD24,
    E_VDEC_EX_DV_STREAM_LEVEL_ID_FHD30,
    E_VDEC_EX_DV_STREAM_LEVEL_ID_FHD60,
    E_VDEC_EX_DV_STREAM_LEVEL_ID_UHD24,
    E_VDEC_EX_DV_STREAM_LEVEL_ID_UHD30,
    E_VDEC_EX_DV_STREAM_LEVEL_ID_UHD48,
    E_VDEC_EX_DV_STREAM_LEVEL_ID_UHD60,
} VDEC_EX_DV_Stream_Highest_Level;
#endif

//Not support info enum
typedef enum
{
    E_VDEC_EX_NOT_SUPPORT_PROFILE      = VDEC_EX_BIT(0), ///Profile not support
    E_VDEC_EX_NOT_SUPPORT_SPS_ID        = VDEC_EX_BIT(1), ///SPS ID not support
    E_VDEC_EX_NOT_SUPPORT_CHROMA_FORMAT = VDEC_EX_BIT(2),///Chroma format not support
    E_VDEC_EX_NOT_SUPPORT_MAX_FRAME_NUM = VDEC_EX_BIT(3),///Max frame number not support
} VDEC_EX_NotSupportInfo;

typedef struct DLL_PACKED
{
    VDEC_EX_Stream    eStream;
    VDEC_EX_CodecType eCodecType;
} VDEC_EX_CodecInfo;

/// Configurations of f/w decode mode
typedef struct DLL_PACKED
{
    VDEC_EX_DEC_MODE    eDecMod;
    VDEC_EX_CodecInfo   pstCodecInfo[VDEC_MAX_DEC_NUM];
    MS_U8  u8CodecCnt;
    MS_U8  u8ArgSize;
    MS_U32 u32Arg;  //ref VDEC_EX_DEC_MODE_ARG enum
} VDEC_EX_DecModCfg;

///STC mode enum
typedef enum
{
    E_VDEC_EX_STC0=0, ///STC Sync mode , sync with STC 0
    E_VDEC_EX_STC1,   ///STC Sync mode , sync with STC 1
    E_VDEC_EX_STC2,   ///STC Sync mode , sync with STC 2
    E_VDEC_EX_STC3,   ///STC Sync mode , sync with STC 3
}VDEC_EX_STCMode;

typedef struct DLL_PACKED
{
    MS_BOOL bEnable;      // 0 : disable   ,  1:enable
    MS_U8   u8DisplayTop; // 0: display top,  1: display bottom
}VDEC_EX_Field_Polarity;

/// argument of DecodeMode structure for f/w tasks
typedef enum
{
    //Group1:Set Korea3DTV mode
    E_VDEC_EX_DEC_KR3D_MODE_BASE  = 0x0000,
    E_VDEC_EX_DEC_KR3D_INTERLACE_MODE = E_VDEC_EX_DEC_KR3D_MODE_BASE,
    E_VDEC_EX_DEC_KR3D_FORCE_P_MODE,
    E_VDEC_EX_DEC_KR3D_INTERLACE_TWO_PITCH,
    E_VDEC_EX_DEC_KR3D_FORCE_P_TWO_PITCH,

    //Group2:Set PIP mode
    E_VDEC_EX_DEC_PIP_MODE_BASE = 0x1000,
    E_VDEC_EX_DEC_PIP_SYNC_INDIE = E_VDEC_EX_DEC_PIP_MODE_BASE,
    E_VDEC_EX_DEC_PIP_SYNC_MAIN_STC,
    E_VDEC_EX_DEC_PIP_SYNC_SWITCH
} VDEC_EX_DEC_MODE_ARG;

typedef enum
{
    E_VDEC_EX_DIU_DRAM = 0,  //MCU mode
    E_VDEC_EX_DIU_HVD = 1,
    E_VDEC_EX_DIU_MVD  = 2,
    E_VDEC_EX_DIU_HVD_3DLR = 3,  //MVC
    E_VDEC_EX_DIU_MVD_3DLR = 4,  //Korea3D, WMV3D
    E_VDEC_EX_DIU_UNKNOWN = -1
} VDEC_EX_DIU;

typedef struct DLL_PACKED
{
    MS_U32 u32version;
    MS_U32 u32size;
} VDEC_EX_VerCtl;

/// Data structure of CC Configuration
typedef struct DLL_PACKED
{
    VDEC_EX_CCFormat eFormat;
    VDEC_EX_CCType   eType;
    MS_VIRT      u32BufStAdd;
    MS_U32       u32BufSize;
} VDEC_EX_CCCfg;


typedef struct DLL_PACKED
{
    MS_U64 u64PTS;
    MS_U32 u32POC;
    MS_U8 u8FrameType;
} VDEC_EX_PVR_Seamless_Info;


/// information for display setting
typedef struct DLL_PACKED
{
    ///bitstream horizontal size
    MS_U16 u16HorSize;
    ///bitstream vertical size
    MS_U16 u16VerSize;
    ///frame rate
    MS_U32 u32FrameRate;
    ///interlace flag
    MS_U8 u8Interlace;
    ///active frame code
    MS_U8 u8AFD;
    ///Sample aspect rate width
    MS_U16 u16SarWidth;
    ///Sample aspect rate height
    MS_U16 u16SarHeight;
    ///right cropping
    MS_U16 u16CropRight;
    ///left cropping
    MS_U16 u16CropLeft;
    ///bottom cropping
    MS_U16 u16CropBottom;
    ///top cropping
    MS_U16 u16CropTop;
    ///pitch
    MS_U16 u16Pitch;
    ///interval of PTS
    MS_U16 u16PTSInterval;
    ///MPEG1 flag
    MS_U8 u8MPEG1;
    ///play mode (fixme)
    MS_U8 u8PlayMode;
    ///FRC mode
    MS_U8 u8FrcMode;
    ///aspect ratio code
    MS_U8 u8AspectRate;
    ///if FALSE, set VOP as mono mode (only for H264)
    MS_BOOL bWithChroma;
    /// if true, color space is xvYCC (Y from 16 to 235 and Cb , Cr from 16 to 240).
    /// if false, color space is BT.601/709 (Y from  0 to 255 and Cb , Cr from  0 to 255).
    /// only MPEG might be with BT.601/709
    MS_BOOL bColorInXVYCC;
    ///Dynamic scaling buffer address
    MS_VIRT u32DynScalingAddr;
    ///Dynamic scaling buffer size
    MS_U32 u32DynScalingSize;
    ///Dynamic scaling depth
    MS_U8 u8DynScalingDepth;
    ///Dynamic scaling DS buffer on miu1 or miu0
    MS_BOOL bEnableMIUSel;
    ///Display width
    MS_U32 u32AspectWidth;
    ///Display height
    MS_U32 u32AspectHeight;
} VDEC_EX_DispInfo;

/// system configuration
typedef struct DLL_PACKED
{
    ///FW binary start address
    MS_PHY u32FWBinaryAddr;
    ///FW binary size
    MS_SIZE u32FWBinarySize;
    ///FW code buffer start address
    MS_PHY u32CodeBufAddr;
    ///FW code buffer size
    MS_SIZE u32CodeBufSize;
    ///frame buffer start address
    MS_PHY u32FrameBufAddr;
    ///frame buffer size
    MS_SIZE u32FrameBufSize;
    ///bitstream buffer start address
    MS_PHY u32BitstreamBufAddr;
    ///bitstream buffer size
    MS_SIZE u32BitstreamBufSize;
    ///driver process buffer start address
    MS_PHY u32DrvProcBufAddr;
    ///driver process buffer size
    MS_SIZE u32DrvProcBufSize;
    ///vlc table Binary address (RM only)
    MS_PHY u32VlcBinarySrcAddr;
    ///vld table Binary size
    MS_SIZE u32VlcTabBinarySize;
    ///debug level setting
    VDEC_EX_DbgLevel eDbgMsgLevel;
    ///debug level setting
    VDEC_EX_FWSourceType eFWSourceType;
} VDEC_EX_SysCfg;

/// video information
typedef struct DLL_PACKED
{
    ///input source mode
    VDEC_EX_SrcMode   eSrcMode;
    /// timestamp type of command queue
    VDEC_EX_TimeStampType      eTimeStampType;
    ///MJPEG scale factor
    VDEC_EX_MJpegScaleFactor   eMJpegScaleFactor;
    /// should be TRUE when codec type is H264 and container is MKV and MP4(MOV)
    MS_BOOL bWithoutNalStCode;
    /// needness when CodecType is MJPEG and divx311
    //MS_U16  u16FrameRate;
    MS_U32 u32FrameRate;
    MS_U32 u32FrameRateBase;
    /// if divx311; use u16Width[0]; only need other elements when RV8
    MS_U16  u16Width[8];
    /// if divx311; use u16Height[0]; only need other elements when RV8
    MS_U16  u16Height[8];
    /// video number sizes (for RM)
    MS_U16  u16NumSizes;
} VDEC_EX_VideoInfo;

/// frame information
typedef struct DLL_PACKED
{
    /// frame buffer base + the start offset of current displayed luma data. Unit: byte.
    MS_PHY u32LumaAddr;
    /// frame buffer base + the start offset of current displayed chroma data. Unit: byte.
    MS_PHY u32ChromaAddr;
    /// Time stamp(DTS, PTS) of current displayed frame. Unit: ms (todo: 90khz)
    MS_U32 u32TimeStamp;
    /// low part of ID number
    MS_U32 u32ID_L;
    /// high part of ID number
    MS_U32 u32ID_H;
    /// pitch
    MS_U16 u16Pitch;
    /// width
    MS_U16 u16Width;
    /// hight
    MS_U16 u16Height;
    ///< Frame type: I, P, B frame
    VDEC_EX_FrameType eFrameType;
    ///< Field type: Top, Bottom, Both
    VDEC_EX_FieldType eFieldType;
} VDEC_EX_FrameInfo;

typedef struct DLL_PACKED
{
    /// frame Info 1st version
    VDEC_EX_FrameInfo sFrameInfo;
    /// Luma LSB address of 10bits. (8bit + 2bit seperate)
    MS_PHY u32LumaAddr_2bit;
    /// Chroma LSB address of 10bits. (8bit + 2bit seperate)
    MS_PHY u32ChromaAddr_2bit;
    /// Luma data bitdepth, support 8~10bits now
    MS_U8 u8LumaBitdepth;
    /// chroma data bitdepth, support 8~10bits now
    MS_U8 u8ChromaBitdepth;
    /// pitch of 2bits frame buffer
    MS_U16 u16Pitch_2bit;
    /// future usage
    MS_U8 u8Reserved[64];
} VDEC_EX_FrameInfoEX;
///Qos info
typedef struct DLL_PACKED
{
    /// VDEC_EX_FrameQoSInfo version control: 0, 1, 2...etc
    VDEC_EX_VerCtl  stVerCtl;
    /// The minimum QP value of a picture
    MS_S16 s16MinQp;
    /// The average QP value of a picture
    MS_S16 s16AvgQp;
    /// The maximum QP value of a picture
    MS_S16 s16MaxQp;
    /// The minimum MV value of a picture
    MS_S16 s16MinMV;
    /// The average  MV value of a picture
    MS_S16 s16AvgMV;
    /// The maximum MV value of a picture
    MS_S16 s16MaxMV;
    /// The number of skip MV of a picture
    MS_U32 u32SkipMV;
    /// The number of non-skip MV of a picture
    MS_U32 u32NonSkipMV;
} VDEC_EX_FrameQoSInfo;

typedef struct
{
    MS_BOOL bUsed;
    MS_BOOL bContentLightLevelEnabled;
    MS_U16  u16MaxContentLightLevel;
    MS_U16  u16MaxPicAverageLightLevel;
} VDEC_EX_ContentLightLevelInfo_SEI;


#ifdef VDEC_CAP_DV_OTT_API
typedef struct
{
    MS_U32 u32DVSupportProfiles;
    VDEC_EX_DV_Stream_Profile eDVProfile;
    VDEC_EX_DV_Stream_Highest_Level eDVLevel;
#ifdef VDEC_CAP_DV_OTT_API_V2
    VDEC_EX_DV_METADATA_REORDER eDVMetaReorder;
#else
    VDEC_EX_DV_CMD_TYPE eDVCmdType;
#endif
}VDEC_EX_DV_Info;
#endif


//Extension of frame info(VDEC_EX_FrameInfoEX)
typedef struct DLL_PACKED
{
    /// VDEC_EX_FrameInfoExt version control: 0, 1, 2...etc
    VDEC_EX_VerCtl  stVerCtl;
    /// FrameInfo structure
    VDEC_EX_FrameInfo sFrameInfo;
    /// physical address of Luma LSB 2bit buffer (Main10 profile)
    MS_PHY u32LumaAddr_2bit;
    /// physical address of Chroma LSB 2bit buffer (Main10 profile)
    MS_PHY u32ChromaAddr_2bit;
    /// physical address of Luma bottom field (interlace)
    MS_PHY u32LumaAddrI;
    /// physical address of Luma LSB 2bit bottom field (interlace)
    MS_PHY u32LumaAddrI_2bit;
    /// physical address of Chroma bottom field (interlace)
    MS_PHY u32ChromaAddrI;
    /// physical address of Chroma LSB 2bit bottom field (interlace)
    MS_PHY u32ChromaAddrI_2bit;
    /// Mstar Frame buffer Codec Information
    MS_U32 u32MFCodecInfo;
    /// MFcodec bitlen buffer address of Luma
    MS_U32 u32LumaMFCbitlen;
    /// MFcodec bitlen buffer address of Chroma
    MS_U32 u32ChromaMFCbitlen;
    /// pitch of 2bits frame buffer
    MS_U16 u16Pitch_2bit;
    /// Luma Frame bitdepth, support 8~10bits now
    MS_U8 u8LumaBitdepth;
    /// Chroma Frame bitdepth, support 8~10bits now
    MS_U8 u8ChromaBitdepth;
#ifdef VDEC_CAP_HEVC_HDR
    /// HVD_MasteringDisplayColourVolume start
    MS_U32 maxLuminance;
    MS_U32 minLuminance;
    MS_U16 primaries[3][2];
    MS_U16 whitePoint[2];
    ///bit[1]: SEI_Enabled,  bit[0]: colur_description_present_flag
    MS_U8 Frm_Info_Ext_avail;
    //colour_description start//
    MS_U8 colour_primaries;
    MS_U8 transfer_characteristics;
    MS_U8 matrix_coefficients;
    //colour_description end//
#endif
} VDEC_EX_FrameInfoExt;
#if !(defined(UFO_PUBLIC_HEADER_500)||defined(UFO_PUBLIC_HEADER_212)||defined(UFO_PUBLIC_HEADER_500_3))
typedef struct DLL_PACKED
{
    VDEC_EX_VerCtl  stVerCtl;   /// version : 0,
    VDEC_EX_FrameInfo sFrameInfo;
    MS_PHY u32LumaAddr_2bit;
    MS_PHY u32ChromaAddr_2bit;
    MS_PHY u32LumaAddrI;
    MS_PHY u32LumaAddrI_2bit;
    MS_PHY u32ChromaAddrI;
    MS_PHY u32ChromaAddrI_2bit;
    MS_U32 u32MFCodecInfo;
    MS_U32 u32LumaMFCbitlen;
    MS_U32 u32ChromaMFCbitlen;
    MS_U16 u16Pitch_2bit;
    MS_U8 u8LumaBitdepth;
    MS_U8 u8ChromaBitdepth;
} VDEC_EX_FrameInfoExt_version0;
#endif

typedef struct DLL_PACKED
{
    MS_BOOL bUsed;
    MS_BOOL bColourVolumeSEIEnabled;
    MS_U32  u32MaxLuminance;
    MS_U32  u32MinLuminance;
    MS_U16  u16Primaries[3][2];
    MS_U16  u16WhitePoint[2];
}VDEC_EX_DisplayColourVolume_SEI;

#ifdef VDEC_CAP_HEVC_HDR_V2
typedef struct DLL_PACKED
{
    VDEC_EX_FrameInfoExt sFrameInfoExt;
    ////HVD_MasteringDisplayColourVolume//
    VDEC_EX_DisplayColourVolume_SEI sDisplay_colour_volume;
    MS_U8 u8Frm_Info_Ext_avail; ///bit[1]: SEI_Enabled,  bit[0]: colur_description_present_flag
    ////colour_description////////////
    MS_U8 u8Colour_primaries;                            // u(8)
    MS_U8 u8Transfer_characteristics;                    // u(8)
    MS_U8 u8Matrix_coefficients;                         // u(8)
} VDEC_EX_FrameInfoExt_v2;
#endif

#ifdef VDEC_CAP_HEVC_HDR_V3
typedef struct DLL_PACKED
{
    VDEC_EX_FrameInfoExt sFrameInfoExt;
    ////HVD_MasteringDisplayColourVolume//
    VDEC_EX_DisplayColourVolume_SEI sDisplay_colour_volume;
    MS_U8 u8Frm_Info_Ext_avail; ///bit[1]: SEI_Enabled,  bit[0]: colur_description_present_flag
    ////colour_description////////////
    MS_U8 u8Colour_primaries;                            // u(8)
    MS_U8 u8Transfer_characteristics;                    // u(8)
    MS_U8 u8Matrix_coefficients;                         // u(8)
    ////Dolby_Vision////////////
    MS_U8 u8DVMode; // bit[0:1] 0: Disable 1:Single layer 2: Dual layer, bit[2] 0:Base Layer 1:Enhance Layer
    MS_PHY u32DVMetaDataAddr;
    MS_U32 u32DVMetaDataSize;;
} VDEC_EX_FrameInfoExt_v3;
#endif

#ifdef VDEC_CAP_FRAME_INFO_EXT_V4
typedef struct DLL_PACKED
{
    VDEC_EX_FrameInfoExt_v3 sFrameInfoExt_v3;
    //// Dolby Vision HDR ////////////
    MS_U8  u8CurrentIndex;
    MS_PHY u32HDRRegAddr;
    MS_U32 u32HDRRegSize;
    MS_PHY u32HDRLutAddr;
    MS_U32 u32HDRLutSize;
    MS_BOOL bDMEnable;
    MS_BOOL bCompEnable;
    // decoder complexity level //
    MS_U8 u8ComplexityLevel;
} VDEC_EX_FrameInfoExt_v4;
#endif


#ifdef VDEC_CAP_FRAME_INFO_EXT_V5
typedef struct DLL_PACKED
{
    VDEC_EX_FrameInfoExt_v4 sFrameInfoExt_v4;

    MS_U32 u32ParWidth;
    MS_U32 u32ParHeight;
    MS_U16 u16CropRight;
    MS_U16 u16CropLeft;
    MS_U16 u16CropBottom;
    MS_U16 u16CropTop;
} VDEC_EX_FrameInfoExt_v5;
#endif

#ifdef VDEC_CAP_FRAME_INFO_EXT_V6
///V6: for new DV display path(by XC srm)
typedef struct DLL_PACKED
{
    /// FrameInfo structure
    VDEC_EX_FrameInfoExt_v5 sFrameInfoExt_v5;

    /// Tile Mode
    VDEC_EX_TileMode eTileMode;
    /// Profiling / benchmark
    MS_U16 u16MIUBandwidth;
    /// Bit rate
    MS_U16 u16Bitrate;
    /// HTLB Table ID
    MS_U8  u8HTLBTableId;
    /// HTLB Entries Size
    MS_U8  u8HTLBEntriesSize;
    /// HTLB Entries Addr
    MS_PHY u32HTLBEntriesAddr;
} VDEC_EX_FrameInfoExt_v6;
#endif

/// Extension display information
typedef struct DLL_PACKED
{
    /// vertical size from sequene_display_extension
    MS_U16 u16VSize;
    /// horizontal size from sequene_display_extension
    MS_U16 u16HSize;
    /// vertical offset from picture_display_extension
    MS_S16 s16VOffset;
    /// horizontal offset from picture_display_extension
    MS_S16 s16HOffset;
} VDEC_EX_ExtDispInfo;

/// display frame information
typedef struct DLL_PACKED
{
    ///< frame information
    VDEC_EX_FrameInfo stFrmInfo;
    ///< firmware private data
    MS_U32 u32PriData;
    ///< index used by apiVDEC to manage VDEC_DispQ[][]
    MS_U32 u32Idx;
} VDEC_EX_DispFrame;

/// time code structure
typedef struct DLL_PACKED
{
    ///  time_code_hours
    MS_U8   u8TimeCodeHr;
    ///  time_code_minutes
    MS_U8   u8TimeCodeMin;
    ///  time_code_seconds
    MS_U8   u8TimeCodeSec;
    ///  time_code_pictures
    MS_U8   u8TimeCodePic;
    ///  drop_frame_flag
    MS_U8   u8DropFrmFlag;
    ///  reserved fields for 4-byte alignment
    MS_U8   u8Reserved[3];
} VDEC_EX_TimeCode;

/// vdec frame buffer reduction
typedef struct DLL_PACKED
{
    VDEC_EX_FBReductionType eLumaFBReduction;
    VDEC_EX_FBReductionType eChromaFBReduction;
    MS_BOOL              bEnableAutoMode;   /// 0: Disable, 1: Enable
} VDEC_EX_FBReduction;

/// Initial parameter
typedef struct DLL_PACKED
{
    /// init param version : 0
    MS_U32          u32Version;
    /// codec type
    VDEC_EX_CodecType   eCodecType;
    /// system configuration
    VDEC_EX_SysCfg      SysConfig;
    /// video information from container
    VDEC_EX_VideoInfo   VideoInfo;
    /// dynamic scaling control bit
    MS_BOOL             EnableDynaScale;
    /// switch for display decode error frame or not
    MS_BOOL             bDisableDropErrFrame;
    /// switch for error concealment
    MS_BOOL             bDisableErrConceal;
    /// enable repeat last field when repeat happened at interlace stream
    MS_BOOL             bRepeatLastField;
    /// threshold to judge error frame
    MS_U8               u8ErrThreshold;
    /// dynamic scaling virtual box Width
    MS_U32              u32DSVirtualBoxWidth;
    /// dynamic scaling virtual box Height
    MS_U32              u32DSVirtualBoxHeight;
    /// vdec frame buffer reduction setting
    VDEC_EX_FBReduction stFBReduction;
} VDEC_EX_InitParam;

/// Decode Command
typedef struct DLL_PACKED
{
    /// ID (high 4-bytes)
    MS_U32  u32ID_H;
    /// ID (low 4-bytes)
    MS_U32  u32ID_L;
    /// start address of payload
    MS_VIRT  u32StAddr;
    /// size of payload
    MS_U32  u32Size;
    /// timestamp of payload
    MS_U32  u32Timestamp;
} VDEC_EX_DecCmd;

/// Display Command
typedef struct DLL_PACKED
{
    /// ID (high 4-bytes)
    MS_U32  u32ID_H;
    /// ID (low 4-bytes)
    MS_U32  u32ID_L;
    /// action of command
    VDEC_EX_DispCmdAction  eAction;
} VDEC_EX_DispCmd;

typedef struct DLL_PACKED
{
    MS_U32                  u32Version;
    /// top, bottom or frame
    VDEC_EX_PicStructure    u8PicStructure;
    MS_U8                   u8TopFieldFirst;
    MS_U16                  u16TempRef;
    MS_U32                  u32Pts;
    /// address of cc data
    MS_U32                  u32UserDataBuf;
    /// size of cc data
    MS_U32                  u32UserDataSize;
    ///< Frame type: I, P, B frame
    VDEC_EX_FrameType eFrameType;
} VDEC_EX_CC_Info;

///CC input parameters for mstar proprietary CC library
typedef struct DLL_PACKED
{
    MS_U32 u32Ver;      ///version of this structure
    MS_VIRT u32Val;
} VDEC_EX_CC_InputPara;

typedef struct DLL_PACKED
{
    MS_U32      u32OutputFrameRate; ///< output frame rate, unit:vsync count
    MS_U8       u8Interlace;        ///< output scan:0:progress, 1:interlace
} VDEC_EX_FRC_OutputParam;

typedef struct DLL_PACKED
{
    MS_U32 u32Version;
    MS_U32 u32Id;
} VDEC_StreamId;

typedef void (*VDEC_EX_EventCb)(MS_U32 eFlag, void *param);

typedef struct DLL_PACKED
{
    MS_U8   u8Frm_packing_arr_cnl_flag;
    MS_U8   u8Frm_packing_arr_type;
    MS_U8   u8content_interpretation_type;
    MS_U8   u1Quincunx_sampling_flag;

    MS_U8   u1Spatial_flipping_flag;
    MS_U8   u1Frame0_flipping_flag;
    MS_U8   u1Field_views_flag;
    MS_U8   u1Current_frame_is_frame0_flag;

    MS_U8   u1Frame0_self_contained_flag;
    MS_U8   u1Frame1_self_contained_flag;
    MS_U8   u4Frame0_grid_position_x;
    MS_U8   u4Frame0_grid_position_y;

    MS_U8   u4Frame1_grid_position_x;
    MS_U8   u4Frame1_grid_position_y;
    MS_U8   u8Reserved01;
    MS_U8   u8Reserved02;
}VDEC_EX_Frame_packing_SEI;

typedef struct DLL_PACKED
{
    VDEC_EX_VerCtl  stVerCtl;   /// version : 0,
                                /// size : sizeof(VDEC_EX_Frame_packing_SEI_EX)
    MS_BOOL bIsCropInfo;
    MS_BOOL bValid;
    MS_BOOL bUsed;
    MS_U8   u8Frm_packing_arr_cnl_flag;
    MS_U8   u8Frm_packing_arr_type;
    MS_U8   u8content_interpretation_type;
    MS_U8   u1Quincunx_sampling_flag;
    MS_U8   u1Spatial_flipping_flag;
    MS_U8   u1Frame0_flipping_flag;
    MS_U8   u1Field_views_flag;
    MS_U8   u1Current_frame_is_frame0_flag;
    MS_U8   u1Frame0_self_contained_flag;
    MS_U8   u1Frame1_self_contained_flag;
    MS_U8   u4Frame0_grid_position_x;
    MS_U8   u4Frame0_grid_position_y;
    MS_U8   u4Frame1_grid_position_x;
    MS_U8   u4Frame1_grid_position_y;
    MS_U32  u32DataBuff;
    MS_U32  u32DataSize;
    MS_U32  left;
    MS_U32  right;
    MS_U32  top;
    MS_U32  bottom;
} VDEC_EX_Frame_packing_SEI_EX;

typedef struct DLL_PACKED
{
    /// is aspect ratio info exist 1 for yes, 0 for no
    MS_BOOL bAspect_ratio_info_present_flag;            // u(1)
    /// Aspect ratio mapping table index: HEVC_ASPECT_RATIO[17][2]
    MS_U8   u8Aspect_ratio_idc;                            // u(8)
    /// Sample aspect ratio width
    MS_U16  u16Sar_width;                                  // u(16)
    /// Sample aspect ratio height
    MS_U16  u16Sar_height;                                 // u(16)
    /// is overscan info exist?
    MS_BOOL bOverscan_info_present_flag;                // u(1)
    /// is the cropped decoded pictures output are suitable for display using overscan
    MS_BOOL bOverscan_appropriate_flag;                 // u(1)
    /// is video signal type exist or not?
    MS_BOOL bVideo_signal_type_present_flag;            // u(1)
    /// 0: component, 1: PAL, 2:NTSC  3:SECAM  4:MAC  5:unspecified
    MS_U8   u8Video_format;                                // u(3)
    /// video pixel value is 0~255 or 16~235
    MS_BOOL bVideo_full_range_flag;                     // u(1)
    /// is colour description exist: u8Colour_primaries, u8Transfer_characteristics, and u8Matrix_coefficients
    MS_BOOL bColour_description_present_flag;           // u(1)
    MS_U8   u8Colour_primaries;                            // u(8)
    MS_U8   u8Transfer_characteristics;                    // u(8)
    MS_U8   u8Matrix_coefficients;                         // u(8)
    /// u8Chroma_sample_loc_type_top_field and u8Chroma_sample_loc_type_bottom_field exist or not
    MS_BOOL bChroma_location_info_present_flag;         // u(1)
    MS_U8   u8Chroma_sample_loc_type_top_field;            // ue(v) 0~5
    MS_U8   u8Chroma_sample_loc_type_bottom_field;         // ue(v) 0~5
    /// timing info exist or not
    MS_BOOL bTiming_info_present_flag;                  // u(1)
    MS_BOOL bFixed_frame_rate_flag;                     // u(1)
    //fps=time_scale/num_units_in_tick, vui_time_scale=27000000, vui_num_units_in_tick=1080000
    MS_U32  u32Num_units_in_tick;                          // u(32)
    MS_U32  u32Time_scale;                                 // u(32)
} VDEC_EX_AVC_VUI_DISP_INFO;

//CRC value
typedef struct DLL_PACKED
{
    MS_U32 u32HorSize;
    MS_U32 u32VerSize;
    MS_U32 u32Strip;
    MS_VIRT u32LumaStartAddr;
    MS_VIRT u32ChromaStartAddr;
}VDEC_EX_CrcIn;

typedef struct DLL_PACKED
{
    MS_U32 u32LumaCRC;
    MS_U32 u32ChromaCRC;
}VDEC_EX_CrcOut;

typedef struct DLL_PACKED
{
    VDEC_EX_CrcIn stCrcIn;
    VDEC_EX_CrcOut stCrcOut;
}VDEC_EX_CrcValue;

typedef struct DLL_PACKED
{
    MS_VIRT  u32DSBufAddr;       // Buffer Address
    MS_U32  u32DSBufSize;       // Buffer Size
}VDEC_EX_EXTERNAL_DS_BUFFER;

typedef struct DLL_PACKED
{
    MS_BOOL  bEnable;           // Enable/Disable
    MS_U32  u32Timeout;       // Timeout value, unit : ms
}VDEC_EX_Decode_Timeout_Param;



typedef struct DLL_PACKED
{
  MS_BOOL bEnable;
  MS_PHY u32IapGnBufAddr;
  MS_U32 u32IapGnBufSize;
} VDEC_EX_IapGnBufShareBWMode;

typedef struct DLL_PACKED
{
  MS_BOOL bEnableFramebufferCtrl;
  MS_PHY u32FramebufferAddress;  // physical address
  MS_U32 u32FramebufferTotalsize; // unit is byte
} VDEC_Framebuffer_Ctrl;



#define API_HWCAP_VERSION 1

typedef struct DLL_PACKED
{
    MS_U32  u32ApiHW_Version;   //<Version of current structure>
    MS_U16  u16ApiHW_Length;    //<Length of this structure>

    MS_U8   u8Cap_Support_Decoder_Num;

    MS_BOOL bCap_Support_MPEG2;
    MS_BOOL bCap_Support_H263;
    MS_BOOL bCap_Support_MPEG4;
    MS_BOOL bCap_Support_DIVX311;
    MS_BOOL bCap_Support_DIVX412;
    MS_BOOL bCap_Support_FLV;
    MS_BOOL bCap_Support_VC1ADV;
    MS_BOOL bCap_Support_VC1MAIN;

    MS_BOOL bCap_Support_RV8;
    MS_BOOL bCap_Support_RV9;
    MS_BOOL bCap_Support_H264;
    MS_BOOL bCap_Support_AVS;
    MS_BOOL bCap_Support_AVS_PLUS;
    MS_BOOL bCap_Support_MJPEG;
    MS_BOOL bCap_Support_MVC;
    MS_BOOL bCap_Support_VP8;
    MS_BOOL bCap_Support_VP9;
    MS_BOOL bCap_Support_HEVC;

    /*New HW Cap and Feature add in struct at the end*/
}VDEC_HwCap;

typedef struct DLL_PACKED
{
    MS_U32  u32Version;
    MS_U32  u32Addr;
    MS_U32  u32Size;
    MS_U8   reserved[32];
} VDEC_FRAMEBuff;

typedef struct DLL_PACKED
{
    MS_U16 u16CodecCapWidth;
    MS_U16 u16CodecCapHeight;
    MS_U8  u8CodecCapFrameRate;
    VDEC_EX_CODEC_CAP_PROFILE_INFO  u8CodecCapProfile;
    VDEC_EX_CODEC_CAP_VERSION_INFO  u8CodecCapVersion;
    VDEC_EX_CODEC_CAP_LEVEL_INFO  u8CodecCapLevel;
    MS_U32 u32CodecType;
    MS_U32 u32Reserved1;
}VDEC_EX_CODEC_CAP_INFO;

typedef struct DLL_PACKED
{
    VDEC_EX_CodecType eCodecType;
    MS_PHY  u32DataAddr;
    MS_U32  u32MemUsageSize;
    MS_U16  u16DataSize;
} VDEC_EX_FbMemUsage_Param;

//-------------------------------------------------------------------------------------------------
//  Function and Variable
//-------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------
/// Get VDEC version
/// @ingroup Get_information
/// @param eStream \b IN : stream type
/// @return VDEC_EX_Result
//------------------------------------------------------------------------------
VDEC_EX_Result MApi_VDEC_EX_GetLibVer(const MSIF_Version **ppVersion);
//------------------------------------------------------------------------------
/// Get VDEC info
/// @ingroup Get_information
/// @param eStream \b IN : stream type
/// @return VDEC_EX_Result
//------------------------------------------------------------------------------
VDEC_EX_Result MApi_VDEC_EX_GetInfo(const VDEC_EX_Info **ppInfo);
//------------------------------------------------------------------------------
/// Get VDEC status
/// @ingroup Get_information
/// @param eStream \b IN : stream type
/// @param pStatus \b OUT : vdec status
/// @return VDEC_EX_Result
//------------------------------------------------------------------------------
MS_BOOL MApi_VDEC_EX_GetStatus(VDEC_StreamId *pStreamId, VDEC_EX_Status *pStatus);
//------------------------------------------------------------------------------
/// Enable turbo mode for VDEC
/// @ingroup VDEC_Enhanced
/// @param bEnable \b IN : enable turbo mode
/// @return VDEC_EX_Result
//------------------------------------------------------------------------------
VDEC_EX_Result MApi_VDEC_EX_EnableTurboMode(MS_BOOL bEnable);
//------------------------------------------------------------------------------
/// Check VDEC capbility
/// @ingroup Get_information
/// @param eStream \b IN : stream type
/// @param eCodecType \b OUT : vdec codec type
/// @return VDEC_EX_Result
MS_BOOL MApi_VDEC_EX_CheckCaps(VDEC_StreamId *pStreamId, VDEC_EX_CodecType eCodecType);

//used for decoder speed up when single decode
//------------------------------------------------------------------------------
/// Set single decode mode to not create controller task in FW
/// @ingroup VDEC_Enhanced
/// @param bEnable \b IN : enable single decode mode
/// @return VDEC_EX_Result
//------------------------------------------------------------------------------
VDEC_EX_Result MApi_VDEC_EX_SetSingleDecode(MS_BOOL bEnable);
//used for init
//-------------------------------------------------------------------------------------------------
/// Get Stream ID from VDEC.
/// @ingroup VDEC_Init
/// @param pInfo \b IN : pointer to VDEC_StreamId
/// @param u32Size \b IN : size of VDEC_StreamId
/// @param eStream \b IN : stream type
/// @param eCodecType \b IN : codec type
/// @return VDEC_EX_Result
///     - E_VDEC_EX_OK: success
///     - E_VDEC_EX_FAIL: failed
///     - E_VDEC_EX_RET_NOT_EXIT: not ext after last initialization
///     - E_VDEC_EX_RET_INVALID_PARAM: input parameter is invalid
//-------------------------------------------------------------------------------------------------
VDEC_EX_Result MApi_VDEC_EX_GetFreeStream(void *pInfo, MS_U32 u32Size, VDEC_EX_Stream eStreamType, VDEC_EX_CodecType eCodecType);
//------------------------------------------------------------------------------
///Map context for multi process use
/// @param eStream \b IN : stream type
/// @return VDEC_EX_Result
///     - E_VDEC_EX_OK: success
///     - E_VDEC_EX_FAIL: failed
///     - E_VDEC_EX_RET_NOT_EXIT: not ext after last initialization
///     - E_VDEC_EX_RET_INVALID_PARAM: input parameter is invalid
//------------------------------------------------------------------------------
VDEC_EX_Result MApi_VDEC_EX_GetConfig(VDEC_EX_Stream eStreamType);
//-------------------------------------------------------------------------------------------------
/// Initial VDEC.
/// @ingroup VDEC_Init
/// @param pStreamId \b IN : the pointer to stream ID
/// @param pInitParam \b IN : pointer to initial parameter
/// @return VDEC_EX_Result
///     - E_VDEC_EX_OK: success
///     - E_VDEC_EX_FAIL: failed
///     - E_VDEC_EX_RET_NOT_EXIT: not ext after last initialization
///     - E_VDEC_EX_RET_INVALID_PARAM: input parameter is invalid
//-------------------------------------------------------------------------------------------------
VDEC_EX_Result MApi_VDEC_EX_Init(VDEC_StreamId *eStreamId, VDEC_EX_InitParam *pInitParam);
//-------------------------------------------------------------------------------------------------
/// Reset VDEC.
/// @ingroup VDEC_Init
/// @param pStreamId \b IN : the pointer to stream ID
/// @return VDEC_EX_Result
//-------------------------------------------------------------------------------------------------
VDEC_EX_Result MApi_VDEC_EX_Rst(VDEC_StreamId *pStreamId);
//-------------------------------------------------------------------------------------------------
/// Exit VDEC.
/// @ingroup VDEC_Init
/// @param pStreamId \b IN : the pointer to stream ID
/// @return VDEC_EX_Result
//-------------------------------------------------------------------------------------------------
VDEC_EX_Result MApi_VDEC_EX_Exit(VDEC_StreamId *pStreamId);
//-------------------------------------------------------------------------------------------------
/// Check if information for display setting is ready or not
/// @ingroup VDEC_Init
/// @param pStreamId \b IN : the pointer to stream ID
/// @return VDEC_EX_Result
//-------------------------------------------------------------------------------------------------
VDEC_EX_Result MApi_VDEC_EX_CheckDispInfoRdy(VDEC_StreamId *pStreamId);
//-------------------------------------------------------------------------------------------------
/// Set up frame rate conversion mode
/// @ingroup VDEC_Normal_decode
/// @param pStreamId \b IN : the pointer to stream ID
/// @param eFrcMode \b IN : frame rate conversion mode
/// @return VDEC_EX_Result
//-------------------------------------------------------------------------------------------------
VDEC_EX_Result MApi_VDEC_EX_SetFrcMode(VDEC_StreamId *pStreamId, VDEC_EX_FrcMode eFrcMode);
//------------------------------------------------------------------------------
/// Set up some parameters about dynamic scaling in FW
/// @ingroup VDEC_DS
/// @param eStream \b IN : stream type
/// @param u32Addr \b IN : the physical start address of parameter set
/// @param u32Size \b IN : the size of parameter set
/// @return VDEC_EX_Result
//------------------------------------------------------------------------------
VDEC_EX_Result MApi_VDEC_EX_SetDynScalingParams(VDEC_StreamId *pStreamId, MS_PHY u32Addr, MS_U32 u32Size);
//Used for debug
//------------------------------------------------------------------------------
/// Set up debug message level
/// @param eStream \b IN : stream type
/// @param eDbgLevel \b IN : message level
/// @ingroup VdecDebug
/// @return VDEC_EX_Result
///     - E_VDEC_EX_OK: Success
///     - E_VDEC_EX_FAIL: Failed
//------------------------------------------------------------------------------
VDEC_EX_Result MApi_VDEC_EX_SetDbgLevel(VDEC_StreamId *pStreamId, VDEC_EX_DbgLevel eDbgLevel);

//-------------------------------------------------------------------------------------------------
/// Start playback
/// @ingroup Decode
/// @param pStreamId \b IN : the pointer to stream ID
/// @return return VDEC_EX_Result
//-------------------------------------------------------------------------------------------------
VDEC_EX_Result MApi_VDEC_EX_Play(VDEC_StreamId *pStreamId);
//-------------------------------------------------------------------------------------------------
/// Pause decode and display
/// @ingroup Decode
/// @param pStreamId \b IN : the pointer to stream ID
/// @return return VDEC_EX_Result
//-------------------------------------------------------------------------------------------------
VDEC_EX_Result MApi_VDEC_EX_Pause(VDEC_StreamId *pStreamId);
//-------------------------------------------------------------------------------------------------
/// Resume decode and display
/// @ingroup Decode
/// @param pStreamId \b IN : the pointer to stream ID
/// @return return VDEC_EX_Result
//-------------------------------------------------------------------------------------------------
VDEC_EX_Result MApi_VDEC_EX_Resume(VDEC_StreamId *pStreamId);
//-------------------------------------------------------------------------------------------------
/// Trigger to display one frame (background may still decoding)
/// @ingroup Decode
/// @param pStreamId \b IN : the pointer to stream ID
/// @return return VDEC_EX_Result
//-------------------------------------------------------------------------------------------------
VDEC_EX_Result MApi_VDEC_EX_StepDisp(VDEC_StreamId *pStreamId);
//-------------------------------------------------------------------------------------------------
/// Check if step play done or not
/// @ingroup Decode
/// @param pStreamId \b IN : the pointer to stream ID
/// @return return VDEC_EX_Result
///     - E_VDEC_EX_OK: step display done
///     - E_VDEC_EX_FAIL: not yet
///     - E_VDEC_EX_RET_NOT_INIT: not initial yet
///     - E_VDEC_EX_RET_UNSUPPORTED: not supported with current decoder configuration
//-------------------------------------------------------------------------------------------------
VDEC_EX_Result MApi_VDEC_EX_IsStepDispDone(VDEC_StreamId *pStreamId);
//-------------------------------------------------------------------------------------------------
/// Trigger VDEC to decode one frame
/// @ingroup Decode
/// @param pStreamId \b IN : the pointer to stream ID
/// @return return VDEC_EX_Result
//-------------------------------------------------------------------------------------------------
VDEC_EX_Result MApi_VDEC_EX_StepDecode(VDEC_StreamId *pStreamId);
//-------------------------------------------------------------------------------------------------
/// Check if step decode done or not
/// @ingroup Decode
/// @param pStreamId \b IN : the pointer to stream ID
/// @return return VDEC_EX_Result
///     - E_VDEC_EX_OK: step decode done
///     - E_VDEC_EX_FAIL: not yet
///     - E_VDEC_EX_RET_NOT_INIT: not initial yet
///     - E_VDEC_EX_RET_UNSUPPORTED: not supported with current decoder configuration
//-------------------------------------------------------------------------------------------------
VDEC_EX_Result MApi_VDEC_EX_IsStepDecodeDone(VDEC_StreamId *pStreamId);
//-------------------------------------------------------------------------------------------------
/// Set up trick decode mode for decode I, decode IP and decode all.
/// @ingroup Decode
/// @param pStreamId \b IN : the pointer to stream ID
/// @param eTrickDec \b IN : trick decode mode
/// @return return VDEC_EX_Result
//-------------------------------------------------------------------------------------------------
VDEC_EX_Result MApi_VDEC_EX_SetTrickMode(VDEC_StreamId *pStreamId, VDEC_EX_TrickDec eTrickDec);
//-------------------------------------------------------------------------------------------------
/// Push decode command queue
/// @ingroup Decode
/// @param pStreamId \b IN : the pointer to stream ID
/// @param pCmd \b IN : the pointer to decode command
/// @return return VDEC_EX_Result
//-------------------------------------------------------------------------------------------------
VDEC_EX_Result MApi_VDEC_EX_PushDecQ(VDEC_StreamId *pStreamId, VDEC_EX_DecCmd *pCmd);
//-------------------------------------------------------------------------------------------------
/// Flush command queue and internal data of decoder
/// @ingroup Decode
/// @param pStreamId \b IN : the pointer to stream ID
/// @return return VDEC_EX_Result
//-------------------------------------------------------------------------------------------------
VDEC_EX_Result MApi_VDEC_EX_Flush(VDEC_StreamId *pStreamId, VDEC_EX_FreezePicSelect eFreezePic);
//-------------------------------------------------------------------------------------------------
/// Enable to let decoder force to display all decoded frame when out of input data
/// @ingroup Decode
/// @param pStreamId \b IN : the pointer to stream ID
/// @param bEnable \b IN : TRUE - enable; FALSE - disable
/// @return return VDEC_EX_Result
//-------------------------------------------------------------------------------------------------
VDEC_EX_Result MApi_VDEC_EX_EnableLastFrameShow(VDEC_StreamId *pStreamId, MS_BOOL bEnable);
//-------------------------------------------------------------------------------------------------
/// Set up display speed
/// @ingroup Decode
/// @param pStreamId \b IN : the pointer to stream ID
/// @param eSpeedType \b IN : display speed type
/// @param eSpeed \b IN : multiple
/// @return return VDEC_EX_Result
//-------------------------------------------------------------------------------------------------
VDEC_EX_Result MApi_VDEC_EX_SetSpeed(VDEC_StreamId *pStreamId, VDEC_EX_SpeedType eSpeedType, VDEC_EX_DispSpeed eSpeed);
//-------------------------------------------------------------------------------------------------
/// Let FW stop updating frames when vsync, but decoding process is still going.
/// @ingroup Decode
/// @param pStreamId \b IN : the pointer to stream ID
/// @param bEnable \b IN : Enable/Disable
/// @return -The result of command freeze image.
//-------------------------------------------------------------------------------------------------
VDEC_EX_Result MApi_VDEC_EX_SetFreezeDisp(VDEC_StreamId *pStreamId, MS_BOOL bEnable);
//-------------------------------------------------------------------------------------------------
/// Set blue screen on/off
/// @ingroup Decode
/// @param pStreamId \b IN : the pointer to stream ID
/// @param bOn \b IN : turn on / off blue screen
/// @return VDEC_EX_Result
//-------------------------------------------------------------------------------------------------
VDEC_EX_Result MApi_VDEC_EX_SetBlueScreen(VDEC_StreamId *pStreamId, MS_BOOL bOn);
//-------------------------------------------------------------------------------------------------
/// Reset PTS
/// @ingroup Decode
/// @param pStreamId \b IN : the pointer to stream ID
/// @param u32PtsBase \b IN : new PTS base value
/// @return VDEC_EX_Result
//-------------------------------------------------------------------------------------------------
VDEC_EX_Result MApi_VDEC_EX_ResetPTS(VDEC_StreamId *pStreamId, MS_U32 u32PtsBase);
//-------------------------------------------------------------------------------------------------
/// Switch AV sync on/off
/// @ingroup Decode
/// @param pStreamId \b IN : the pointer to stream ID
/// @param bOn \b IN : on/off
/// @param u32SyncDelay \b IN : delay value
/// @param u16SyncTolerance \b IN : tolerance value
/// @return VDEC_EX_Result
//-------------------------------------------------------------------------------------------------
VDEC_EX_Result MApi_VDEC_EX_AVSyncOn(VDEC_StreamId *pStreamId, MS_BOOL bOn, MS_U32 u32SyncDelay, MS_U16 u16SyncTolerance);
//-------------------------------------------------------------------------------------------------
/// Switch AV sync free run threshold
/// @ingroup Decode
/// @param pStreamId \b IN : the pointer to stream ID
/// @param u32Threshold \b IN : threshold value
/// @return VDEC_EX_Result
//-------------------------------------------------------------------------------------------------
VDEC_EX_Result MApi_VDEC_EX_SetAVSyncFreerunThreshold(VDEC_StreamId *pStreamId, MS_U32 u32Threshold );

//------------------------------------------------------------------------------
/// Get display information
/// @ingroup Get_information
/// @param eStream \b IN : stream type
/// @param pDispinfo \b OUT : pointer to display setting information
/// @return VDEC_EX_Result
//------------------------------------------------------------------------------
VDEC_EX_Result MApi_VDEC_EX_GetDispInfo(VDEC_StreamId *pStreamId, VDEC_EX_DispInfo *pDispinfo);
/// Get video av sync on/off status
/// @ingroup Get_information
/// @param eStream \b IN : stream type
/// @return VDEC_EX_Result
//------------------------------------------------------------------------------
VDEC_EX_Result MApi_VDEC_EX_IsAVSyncOn(VDEC_StreamId *pStreamId);
//------------------------------------------------------------------------------
/// Get video valid stream flag
/// @ingroup Get_information
/// @param eStream \b IN : stream type
/// @return VDEC_EX_Result
//------------------------------------------------------------------------------
VDEC_EX_Result MApi_VDEC_EX_IsWithValidStream(VDEC_StreamId *pStreamId);
//------------------------------------------------------------------------------
/// Get video display finish status
/// @ingroup Get_information
/// @param eStream \b IN : stream type
/// @return VDEC_EX_Result
//------------------------------------------------------------------------------
VDEC_EX_Result MApi_VDEC_EX_IsDispFinish(VDEC_StreamId *pStreamId);
//------------------------------------------------------------------------------
/// Get video frame ready status
/// @ingroup Get_information
/// @param eStream \b IN : stream type
/// @return VDEC_EX_Result
//------------------------------------------------------------------------------
VDEC_EX_Result MApi_VDEC_EX_IsFrameRdy(VDEC_StreamId *pStreamId);
//------------------------------------------------------------------------------
/// Get I frame found status
/// @ingroup Get_information
/// @param eStream \b IN : stream type
/// @return VDEC_EX_Result
//------------------------------------------------------------------------------
VDEC_EX_Result MApi_VDEC_EX_IsIFrameFound(VDEC_StreamId *pStreamId);
//------------------------------------------------------------------------------
/// Get video sequence change status
/// @ingroup Get_information
/// @param eStream \b IN : stream type
/// @return VDEC_EX_Result
//------------------------------------------------------------------------------
VDEC_EX_Result MApi_VDEC_EX_IsSeqChg(VDEC_StreamId *pStreamId);
//------------------------------------------------------------------------------
/// Get video active source mode
/// @ingroup Get_information
/// @param eStream \b IN : stream type
/// @return VDEC_EX_SrcMode
//------------------------------------------------------------------------------
VDEC_EX_SrcMode MApi_VDEC_EX_GetActiveSrcMode(VDEC_StreamId *pStreamId);
//------------------------------------------------------------------------------
/// Get video reach sync status
/// @ingroup Get_information
/// @param eStream \b IN : stream type
/// @return VDEC_EX_Result
//------------------------------------------------------------------------------
VDEC_EX_Result MApi_VDEC_EX_IsReachSync(VDEC_StreamId *pStreamId);
//------------------------------------------------------------------------------
/// Get video start sync status
/// @ingroup Get_information
/// @param eStream \b IN : stream type
/// @return VDEC_EX_Result
//------------------------------------------------------------------------------
VDEC_EX_Result MApi_VDEC_EX_IsStartSync(VDEC_StreamId *pStreamId);
//------------------------------------------------------------------------------
/// Get video free run status
/// @ingroup Get_information
/// @param eStream \b IN : stream type
/// @return VDEC_EX_Result
//------------------------------------------------------------------------------
VDEC_EX_Result MApi_VDEC_EX_IsFreerun(VDEC_StreamId *pStreamId);
//------------------------------------------------------------------------------
/// Get video low delay status
/// @ingroup Get_information
/// @param eStream \b IN : stream type
/// @return VDEC_EX_Result
//------------------------------------------------------------------------------
VDEC_EX_Result MApi_VDEC_EX_IsWithLowDelay(VDEC_StreamId *pStreamId);
//------------------------------------------------------------------------------
/// Get video all buffer empty status
/// @ingroup Get_information
/// @param eStream \b IN : stream type
/// @return VDEC_EX_Result
//------------------------------------------------------------------------------
VDEC_EX_Result MApi_VDEC_EX_IsAllBufferEmpty(VDEC_StreamId *pStreamId);
//------------------------------------------------------------------------------
/// Get the extension information of decoded frame.
/// @ingroup Get_information
/// @param eStream \b IN : stream type
/// @param pExtDispinfo \b IN : the extension information of decoded frame.
/// @return VDEC_EX_Result
//------------------------------------------------------------------------------
VDEC_EX_Result MApi_VDEC_EX_GetExtDispInfo(VDEC_StreamId *pStreamId, VDEC_EX_ExtDispInfo *pExtDispinfo);
//------------------------------------------------------------------------------
/// Get the information of the latest decoded frame.
/// @ingroup Get_information
/// @param eStream \b IN : stream type
/// @param pFrmInfo \b IN : the information of the latest decoded frame
/// @return VDEC_EX_Result
//------------------------------------------------------------------------------
VDEC_EX_Result MApi_VDEC_EX_GetDecFrameInfo(VDEC_StreamId *pStreamId, VDEC_EX_FrameInfo *pFrmInfo);
//------------------------------------------------------------------------------
/// Get the information of current displaying frame.
/// @ingroup Get_information
/// @param eStream \b IN : stream type
/// @param pFrmInfo \b IN : the information of displaying frame
/// @return VDEC_EX_Result
//------------------------------------------------------------------------------
VDEC_EX_Result MApi_VDEC_EX_GetDispFrameInfo(VDEC_StreamId *pStreamId, VDEC_EX_FrameInfo *pFrmInfo);
//------------------------------------------------------------------------------
/// Get the time_code of the latest decoded frame.
/// @ingroup Get_information
/// @param eStream \b IN : stream type
/// @param pTimeCode \b IN : the time_code of the latest decoded frame
/// @return VDEC_EX_Result
//------------------------------------------------------------------------------
VDEC_EX_Result MApi_VDEC_EX_GetDecTimeCode(VDEC_StreamId *pStreamId, VDEC_EX_TimeCode* pTimeCode);
//------------------------------------------------------------------------------
/// Get the time_code of the latest displayed frame.
/// @ingroup Get_information
/// @param eStream \b IN : stream type
/// @param pTimeCode \b IN : the time_code of the latest displayed frame
/// @return VDEC_EX_Result
//------------------------------------------------------------------------------
VDEC_EX_Result MApi_VDEC_EX_GetDispTimeCode(VDEC_StreamId *pStreamId, VDEC_EX_TimeCode* pTimeCode);
//Event Group
//-------------------------------------------------------------------------------------------------
/// Set decoder event and register it's callback function
/// @param eStream \b IN : stream type
/// @param u32EventFlag \b In : the events want to be turned on/off
/// @param pfn \b In : callback function
/// @param param \b In : parameter for callback function
/// @ingroup VdecEventGroup
/// @return -VDEC_EX_Result
//-------------------------------------------------------------------------------------------------
VDEC_EX_Result MApi_VDEC_EX_SetEvent(VDEC_StreamId *pStreamId, MS_U32 u32EventFlag, VDEC_EX_EventCb pfn, void* param);
//-------------------------------------------------------------------------------------------------
/// MApi_VDEC_EX_UnsetEvent
/// @ingroup VdecEventGroup
/// @return None
//-------------------------------------------------------------------------------------------------
VDEC_EX_Result MApi_VDEC_EX_UnsetEvent(VDEC_StreamId *pStreamId, MS_U32 u32EventFlag);
//-------------------------------------------------------------------------------------------------
/// Set decoder event and register it's callback function
/// @param eStream \b IN : stream type
/// @param u32EventFlag \b In : the events want to be turned on/off
/// @param pfn \b In : callback function
/// @param param \b In : parameter for callback function
/// @ingroup VdecEventGroup
/// @return -VDEC_EX_Result
//-------------------------------------------------------------------------------------------------
VDEC_EX_Result MApi_VDEC_EX_SetEvent_MultiCallback(VDEC_StreamId *pStreamId, VDEC_EX_CB_TYPE cb_type, MS_U32 u32EventFlag, VDEC_EX_EventCb pfn, void *param);
//-------------------------------------------------------------------------------------------------
/// MApi_VDEC_EX_UnsetEvent_MultiCallback
/// @ingroup VdecEventGroup
/// @return VDEC_EX_Result
//-------------------------------------------------------------------------------------------------
VDEC_EX_Result MApi_VDEC_EX_UnsetEvent_MultiCallback(VDEC_StreamId *pStreamId, VDEC_EX_CB_TYPE cb_type, MS_U32 u32EventFlag);
//-------------------------------------------------------------------------------------------------
/// Get ISR event status
/// @param eStream \b IN : stream type
/// @param u32EventFlag \b OUT : vdec event bitmap
/// @ingroup VdecEventGroup
/// @return status
//-------------------------------------------------------------------------------------------------
VDEC_EX_Result MApi_VDEC_EX_GetEventInfo(VDEC_StreamId *pStreamId, MS_U32* u32EventFlag);
//-------------------------------------------------------------------------------------------------
/// Fire the decode command which be pushed since last fired
/// @ingroup Decode
/// @param pStreamId \b IN : the pointer to stream ID
/// @return VDEC_EX_Result
//-------------------------------------------------------------------------------------------------
VDEC_EX_Result MApi_VDEC_EX_FireDecCmd(VDEC_StreamId *pStreamId);
//-------------------------------------------------------------------------------------------------
/// Decoder will start decode with full  speed until target PTS is reached (equal or larger) then pause.
/// @ingroup Decode
/// @param pStreamId \b IN : the pointer to stream ID
/// @param u32PTS \b IN : target PTS
/// @return VDEC_EX_Result
//-------------------------------------------------------------------------------------------------
VDEC_EX_Result MApi_VDEC_EX_SeekToPTS(VDEC_StreamId *pStreamId, MS_U32 u32PTS);
//-------------------------------------------------------------------------------------------------
/// Decoder will skip all frames before target PTS, and start decode with full  speed after target PTS is reached.
/// @ingroup Decode
/// @param pStreamId \b IN : the pointer to stream ID
/// @param u32PTS \b IN : target PTS
/// @return VDEC_EX_Result
//-------------------------------------------------------------------------------------------------
VDEC_EX_Result MApi_VDEC_EX_SkipToPTS(VDEC_StreamId *pStreamId, MS_U32 u32PTS);

// Advanced Settings / Mode
//------------------------------------------------------------------------------
/// Set deblocking process on/off
/// @ingroup VDEC_Hardware
/// @param eStream \b IN : stream type
/// @param bOn \b IN : turn on / off deblocking process
/// @return VDEC_EX_Result
//------------------------------------------------------------------------------
VDEC_EX_Result MApi_VDEC_EX_DisableDeblocking(VDEC_StreamId *pStreamId, MS_BOOL bDisable);


//------------------------------------------------------------------------------
/// Set Quarter Pixel process on/off
/// @ingroup VDEC_Hardware
/// @param eStream \b IN : stream type
/// @param bOn \b IN : turn on / off Quarter Pixel process
/// @return VDEC_EX_Result
//------------------------------------------------------------------------------
VDEC_EX_Result MApi_VDEC_EX_DisableQuarterPixel(VDEC_StreamId *pStreamId, MS_BOOL bDisable);


//------------------------------------------------------------------------------
/// Turn on/off Auto Remove Last Zero Byte process
/// @ingroup VDEC_Enhanced
/// @param eStream \b IN : stream type
/// @param bOn \b IN : turn on / off Auto Remove Last Zero Byte process
/// @return VDEC_EX_Result
//------------------------------------------------------------------------------
VDEC_EX_Result MApi_VDEC_EX_SetAutoRmLstZeroByte(VDEC_StreamId *pStreamId, MS_BOOL bOn);
//------------------------------------------------------------------------------
/// Set the parameters of Balancing BW
/// @ingroup VDEC_Hardware
/// @param eStream \b IN : stream type
/// @param u8QuarPixelTH \b IN : set Quarter pixel threshold
/// @param u8DeBlockingTH \b IN : set deblocking threshold
/// @param u8UpperBound \b IN : set upper boundary of BW control counter
/// @param u8SafeCoef \b IN : set safety coeffecient of average MB tick.
/// @return VDEC_EX_Result
//------------------------------------------------------------------------------
VDEC_EX_Result MApi_VDEC_EX_SetBalanceBW(VDEC_StreamId *pStreamId,
                                        MS_U8 u8QuarPixelTH, MS_U8 u8DeBlockingTH, MS_U8 u8UpperBound, MS_U8 u8SafeCoef);
//------------------------------------------------------------------------------
/// Get stream active format which decoder retrieved
/// @ingroup Get_information
/// @param eStream \b IN : stream type
/// @return active format ID
//------------------------------------------------------------------------------
MS_U8 MApi_VDEC_EX_GetActiveFormat(VDEC_StreamId *pStreamId);
//------------------------------------------------------------------------------
/// Get stream colour primaries
/// @ingroup Get_information
/// @param eStream \b IN : stream type
/// @return stream colour primaries
//------------------------------------------------------------------------------
MS_U8 MApi_VDEC_EX_GetColourPrimaries(VDEC_StreamId *pStreamId);
//------------------------------------------------------------------------------
/// Get VDEC fw version
/// @ingroup Get_information
/// @param eStream \b IN : stream type
/// @param eFwType \b OUT : vdec fw type
/// @return VDEC_EX_Result
//------------------------------------------------------------------------------
MS_U32 MApi_VDEC_EX_GetFwVersion(VDEC_StreamId *pStreamId, VDEC_EX_FwType eFwType);
//------------------------------------------------------------------------------
/// Get picture counter of current GOP
/// @ingroup Get_information
/// @param eStream \b IN : stream type
/// @return picture counter
//------------------------------------------------------------------------------
MS_U8 MApi_VDEC_EX_GetGOPCnt(VDEC_StreamId *pStreamId);
//Get Decoder status
//------------------------------------------------------------------------------
/// Get ES Buffer Write pointer
/// @ingroup Get_information
/// @param eStream \b IN : stream type
/// @return ES Buffer write pointer
//------------------------------------------------------------------------------
MS_U32 MApi_VDEC_EX_GetESWritePtr(VDEC_StreamId *pStreamId);
//------------------------------------------------------------------------------
/// Get ES Buffer Read pointer
/// @ingroup Get_information
/// @param eStream \b IN : stream type
/// @return ES Buffer read pointer
//------------------------------------------------------------------------------
MS_U32 MApi_VDEC_EX_GetESReadPtr(VDEC_StreamId *pStreamId);
//------------------------------------------------------------------------------
/// Get the PTS of current displayed frame
/// @ingroup Get_information
/// @param eStream \b IN : stream type
/// @return PTS
//------------------------------------------------------------------------------
MS_U32 MApi_VDEC_EX_GetPTS(VDEC_StreamId *pStreamId);
//------------------------------------------------------------------------------
/// Get the PTS of next displayed frame
/// @ingroup Get_information
/// @param eStream \b IN : stream type
/// @return next PTS (unit:ms)
//------------------------------------------------------------------------------
MS_U32 MApi_VDEC_EX_GetNextPTS(VDEC_StreamId *pStreamId);
//------------------------------------------------------------------------------
/// Get Video Delta of Video PTS and STC
/// @ingroup Get_information
/// @param eStream \b IN : stream type
/// @return the value of PTS - STC for video
//------------------------------------------------------------------------------
MS_S64 MApi_VDEC_EX_GetVideoPtsStcDelta(VDEC_StreamId *pStreamId);
//------------------------------------------------------------------------------
/// Get Video Error code
/// @ingroup Get_information
/// @param eStream \b IN : stream type
/// @return error code
//------------------------------------------------------------------------------
MS_U32 MApi_VDEC_EX_GetErrCode(VDEC_StreamId *pStreamId);
//------------------------------------------------------------------------------
/// Get Video decode frame error count
/// @ingroup Get_information
/// @param eStream \b IN : stream type
/// @return Video decode frame error count
//------------------------------------------------------------------------------
MS_U32 MApi_VDEC_EX_GetErrCnt(VDEC_StreamId *pStreamId);
//------------------------------------------------------------------------------
/// Get bitrate which decoder retrieved from stream
/// @ingroup Get_information
/// @param eStream \b IN : stream type
/// @return bitrate
//------------------------------------------------------------------------------
MS_U32 MApi_VDEC_EX_GetBitsRate(VDEC_StreamId *pStreamId);
//------------------------------------------------------------------------------
/// Get Video decode frame count
/// @ingroup Get_information
/// @param eStream \b IN : stream type
/// @return Video decode frame count
//------------------------------------------------------------------------------
MS_U32 MApi_VDEC_EX_GetFrameCnt(VDEC_StreamId *pStreamId);
//------------------------------------------------------------------------------
/// Get Video decode frame skip count
/// @ingroup Get_information
/// @param eStream \b IN : stream type
/// @return Video decode frame skip count
//------------------------------------------------------------------------------
MS_U32 MApi_VDEC_EX_GetSkipCnt(VDEC_StreamId *pStreamId);
//------------------------------------------------------------------------------
/// Get Video decode frame drop count
/// @ingroup Get_information
/// @param eStream \b IN : stream type
/// @return Video decode frame drop count
//------------------------------------------------------------------------------
MS_U32 MApi_VDEC_EX_GetDropCnt(VDEC_StreamId *pStreamId);
//------------------------------------------------------------------------------
/// Get Video decode frame display count
/// @ingroup Get_information
/// @param eStream \b IN : stream type
/// @return Video decode frame display count
//------------------------------------------------------------------------------
MS_U32 MApi_VDEC_EX_GetDispCnt(VDEC_StreamId *pStreamId);
//------------------------------------------------------------------------------
/// Get vacancy of BBU/SLQ entry table
/// @ingroup Get_information
/// @param eStream \b IN : stream type
/// @return vacancy number
//------------------------------------------------------------------------------
MS_U32 MApi_VDEC_EX_GetDecQVacancy(VDEC_StreamId *pStreamId);
//------------------------------------------------------------------------------
/// Get video 3:2 pulldown flag
/// @ingroup Get_information
/// @param eStream \b IN : stream type
/// @return TRUE/FALSE
//------------------------------------------------------------------------------
MS_BOOL MApi_VDEC_EX_Is32PullDown(VDEC_StreamId *pStreamId);
//------------------------------------------------------------------------------
/// Get video alive status
/// @ingroup Get_information
/// @param eStream \b IN : stream type
/// @return VDEC_EX_Result
//------------------------------------------------------------------------------
VDEC_EX_Result MApi_VDEC_EX_IsAlive(VDEC_StreamId *pStreamId);
//close caption
//-------------------------------------------------------------------------------------------------
/// Check cc is available.
/// @param eStream \b IN : stream type
/// @ingroup VdecCloseCaption
/// @return VDEC_EX_Result: TRUE or NOT
//-------------------------------------------------------------------------------------------------
MS_BOOL MApi_VDEC_EX_IsCCAvailable(VDEC_StreamId *pStreamId);
//-------------------------------------------------------------------------------------------------
/// Get cc info.
/// @param eStream \b IN : stream type
/// @ingroup VdecCloseCaption
/// @return VDEC_EX_Result:
//-------------------------------------------------------------------------------------------------
VDEC_EX_Result MApi_VDEC_EX_GetCCInfo(VDEC_StreamId *pStreamId, void *pInfo, MS_U32 u32Size);
//------------------------------------------------------------------------------
/// Get video trick mode status
/// @ingroup Get_information
/// @param eStream \b IN : stream type
/// @return VDEC_EX_TrickDec
//------------------------------------------------------------------------------
VDEC_EX_TrickDec MApi_VDEC_EX_GetTrickMode(VDEC_StreamId *pStreamId);
//------------------------------------------------------------------------------
/// Get active codec type
/// @ingroup Get_information
/// @param eStream \b IN : stream type
/// @return VDEC_EX_Result
//------------------------------------------------------------------------------
VDEC_EX_CodecType MApi_VDEC_EX_GetActiveCodecType(VDEC_StreamId *pStreamId);
//-------------------------------------------------------------------------------------------------
/// Generate a special pattern to work with specific functions
/// @ingroup VDEC_Flush_pattern
/// @param eStream \b IN : stream type
/// @param ePatternType \b IN : Pattern type
/// @param u32Addr \b IN : Pattern buffer physical start address
/// @param u32Size \b IN,OUT : Pattern buffer size
///                             IN: Pattern buffer size
///                             OUT: Used Pattern buffer size
/// @return VDEC_EX_Result
//-------------------------------------------------------------------------------------------------
VDEC_EX_Result MApi_VDEC_EX_GenPattern(VDEC_StreamId *pStreamId,
                                    VDEC_EX_PatternType ePatternType,
                                    MS_PHY u32Addr,
                                    MS_U32* u32Size);
//-------------------------------------------------------------------------------------------------
/// Get the information of the least length of pattern used for specific function
/// @ingroup VDEC_Flush_pattern
/// @param eStream \b IN : stream type
/// @param pFrmInfo \b IN : the information of the least length of pattern used for specific function
/// @return VDEC_EX_Result
//-------------------------------------------------------------------------------------------------
MS_U32 MApi_VDEC_EX_GetPatternLeastLength(VDEC_StreamId *pStreamId, VDEC_EX_PatternType ePatternType);
//Used for MHEG Decode iI frame
//-------------------------------------------------------------------------------------------------
/// For MHEG5 MW, decode one I frame
/// @ingroup VDEC_MHEG_DECODE_I_Frame
/// @param eStream \b IN : stream type
/// @param u32FrameBufAddr \b IN : output buffer address
/// @param u32SrcSt \b IN : source start address
/// @param u32SrcEnd \b IN : source end address
/// @return VDEC_EX_Result
//-------------------------------------------------------------------------------------------------
VDEC_EX_Result MApi_VDEC_EX_MHEG_DecodeIFrame(VDEC_StreamId *pStreamId,
                                            MS_PHY u32FrameBufAddr,
                                            MS_PHY u32SrcSt,
                                            MS_PHY u32SrcEnd);

//-------------------------------------------------------------------------------------------------
/// For MHEG5 MW, check if I frame decode done
/// @ingroup VDEC_MHEG_DECODE_I_Frame
/// @param eStream \b IN : stream type
/// @return VDEC_EX_Result
///     - E_VDEC_EX_OK: decode done
///     - E_VDEC_EX_FAIL: not yet
///     - E_VDEC_EX_RET_NOT_INIT: not initial yet
///     - E_VDEC_EX_RET_UNSUPPORTED: not supported with current decoder configuration
//-------------------------------------------------------------------------------------------------
VDEC_EX_Result MApi_VDEC_EX_MHEG_IsIFrameDecoding(VDEC_StreamId *pStreamId);
//-------------------------------------------------------------------------------------------------
/// For MHEG5 MW, reset decoder after I frame decode done
/// @ingroup VDEC_MHEG_DECODE_I_Frame
/// @param eStream \b IN : stream type
/// @return VDEC_EX_Result
//-------------------------------------------------------------------------------------------------
VDEC_EX_Result MApi_VDEC_EX_MHEG_RstIFrameDec(VDEC_StreamId *pStreamId);

//ATSC Closed Caption control
//------------------------------------------------------------------------------
/// [Obsolete] Start CC data parsing.
/// @param eStream \b IN : stream type
/// @param pCCParam \b IN : CC configuration
/// @ingroup VdecCloseCaption
/// @return -VDEC_EX_Result
//------------------------------------------------------------------------------
VDEC_EX_Result MApi_VDEC_EX_CC_StartParsing(VDEC_StreamId *pStreamId, VDEC_EX_CCCfg *pCCParam);
//------------------------------------------------------------------------------
/// [Obsolete] Stop CC data parsing.
/// @param eStream \b IN : stream type
/// @ingroup VdecCloseCaption
/// @return -VDEC_EX_Result
//------------------------------------------------------------------------------
VDEC_EX_Result MApi_VDEC_EX_CC_StopParsing(VDEC_StreamId *pStreamId);
//------------------------------------------------------------------------------
/// [Obsolete] Get write pointer of CC data buffer.
/// @param eStream \b IN : stream type
/// @param pu32Write \b OUT : current write pointer
/// @ingroup VdecCloseCaption
/// @return -VDEC_EX_Result
//------------------------------------------------------------------------------
VDEC_EX_Result MApi_VDEC_EX_CC_GetWritePtr(VDEC_StreamId *pStreamId, MS_U32 *pu32Write);
//------------------------------------------------------------------------------
/// [Obsolete] Get the read pointer of CC data buffer.
/// @param eStream \b IN : stream type
/// @param pu32Read \b OUT : current read pointer
/// @ingroup VdecCloseCaption
/// @return -VDEC_EX_Result
//------------------------------------------------------------------------------
VDEC_EX_Result MApi_VDEC_EX_CC_GetReadPtr(VDEC_StreamId *pStreamId, MS_U32 *pu32Read);
//------------------------------------------------------------------------------
/// [Obsolete] Update the read pointer of CC data buffer.
/// @param eStream \b IN : stream type
/// @param u32EachPacketSize \b IN : new read pointer
/// @ingroup VdecCloseCaption
/// @return -VDEC_EX_Result
//------------------------------------------------------------------------------
VDEC_EX_Result MApi_VDEC_EX_CC_UpdateReadPtr(VDEC_StreamId *pStreamId, MS_U32 u32EachPacketSize);
//------------------------------------------------------------------------------
/// [Obsolete] Get if CC data buffer is overflow.
/// @param eStream \b IN : stream type
/// @param pbOverflow \b OUT : overflow flag
/// @ingroup VdecCloseCaption
/// @return -VDEC_EX_Result
//------------------------------------------------------------------------------
VDEC_EX_Result MApi_VDEC_EX_CC_GetIsOverflow(VDEC_StreamId *pStreamId, MS_BOOL *pbOverflow);
//------------------------------------------------------------------------------
/// Set up debug command
/// @param eStream \b IN : stream type
/// @param u8Cmd \b IN : debug command
/// @param u32CmdArg \b IN : command arg
/// @ingroup VdecDebug
/// @return VDEC_EX_Result
///     - E_VDEC_EX_OK: Success
///     - E_VDEC_EX_FAIL: Failed
//------------------------------------------------------------------------------
VDEC_EX_Result MApi_VDEC_EX_DbgCmd(VDEC_StreamId *pStreamId, MS_U32 u8Cmd, MS_U32 u32CmdArg);
//------------------------------------------------------------------------------
/// Set debug data
/// @param eStream \b IN : stream type
/// @param u32Addr \b IN : data addr
/// @param u32Data \b IN : data
/// @ingroup VdecDebug
/// @return VDEC_EX_Result
///     - E_VDEC_EX_OK: Success
///     - E_VDEC_EX_FAIL: Failed
//------------------------------------------------------------------------------
VDEC_EX_Result MApi_VDEC_EX_DbgSetData(VDEC_StreamId *pStreamId, MS_VIRT u32Addr, MS_U32 u32Data);
//------------------------------------------------------------------------------
/// Get debug data
/// @param eStream \b IN : stream type
/// @param u32Addr \b IN : data addr
/// @param u32Data \b IN : data
/// @ingroup VdecDebug
/// @return VDEC_EX_Result
///     - E_VDEC_EX_OK: Success
///     - E_VDEC_EX_FAIL: Failed
//------------------------------------------------------------------------------
VDEC_EX_Result MApi_VDEC_EX_DbgGetData(VDEC_StreamId *pStreamId, MS_VIRT u32Addr, MS_U32 *u32Data);
//-------------------------------------------------------------------------------------------------
/// Set command to decode
/// @ingroup Decode
/// @param eStream \b IN : stream type
/// @param cmd_id \b IN : command id
/// @param param \b IN : parameter
/// @return VDEC_EX_Result
//-------------------------------------------------------------------------------------------------
VDEC_EX_Result MApi_VDEC_EX_SetControl(VDEC_StreamId *pStreamId, VDEC_EX_User_Cmd cmd_id, MS_VIRT param);
//-------------------------------------------------------------------------------------------------
/// Set command to decode
/// @ingroup Decode
/// @param eStream \b IN : stream type
/// @param cmd_id \b IN : command id
/// @param param \b OUT : get current status/parameters
/// @return VDEC_EX_Result
//-------------------------------------------------------------------------------------------------
VDEC_EX_Result MApi_VDEC_EX_GetControl(VDEC_StreamId *pStreamId, VDEC_EX_User_Cmd cmd_id, MS_U32 *param);

//------------------------------------------------------------------------------
/// No corresponding functino body, we should remove it
//------------------------------------------------------------------------------
VDEC_EX_Result MApi_VDEC_EX_EnableDispOneField(VDEC_StreamId *pStreamId, MS_BOOL bEnable);
//------------------------------------------------------------------------------
/// Get VDEC HW key
/// @ingroup Get_information
/// @param eStream \b IN : stream type
/// @param pu8Key \b OUT : HW key
/// @return VDEC_EX_Result
//------------------------------------------------------------------------------
VDEC_EX_Result MApi_VDEC_EX_GetHWKey(VDEC_StreamId *pStreamId, MS_U8 *pu8Key);
//------------------------------------------------------------------------------
/// Dump debug status
/// @param eStream \b IN : stream type
/// @ingroup VdecDebug
/// @return VDEC_EX_Result
///     - E_VDEC_EX_OK: Success
///     - E_VDEC_EX_FAIL: Failed
//------------------------------------------------------------------------------
void MApi_VDEC_EX_DbgDumpStatus(VDEC_StreamId *pStreamId);
//------------------------------------------------------------------------------
/// Get program count
/// @ingroup VdecDebug
/// @return VDEC_EX_Result
///     - E_VDEC_EX_OK: Success
///     - E_VDEC_EX_FAIL: Failed
//------------------------------------------------------------------------------
MS_U32 MApi_VDEC_EX_DbgGetProgCnt(void);

//-------------------------------------------------------------------------------------------------
/// Enable Display Queue controller(Gstreamer,Uniplayer)
/// @ingroup VDEC_Display_Q_Control
/// @param eStream \b IN : stream type
/// @param bEnable \b IN : enable/disable
/// @return VDEC_EX_Result
//-------------------------------------------------------------------------------------------------
VDEC_EX_Result MApi_VDEC_EX_SetBlockDisplay(VDEC_StreamId *pStreamId, MS_BOOL bEnable);

//-------------------------------------------------------------------------------------------------
/// Enable Es buffer memory allocate
/// @ingroup VDEC_ES_buffer_manage
/// @param eStream \b IN : stream type
/// @param bEnable \b IN : enable/disable
/// @return VDEC_EX_Result
//-------------------------------------------------------------------------------------------------
VDEC_EX_Result MApi_VDEC_EX_EnableESBuffMalloc(VDEC_StreamId *pStreamId, MS_BOOL bEnable);
//-------------------------------------------------------------------------------------------------
/// Get difference between ES buffer read/write pointer
/// @ingroup VDEC_ES_buffer_manage
/// @param eStream \b IN : stream type
/// @param pData \b OUT : vacancy
/// @return VDEC_EX_Result
//-------------------------------------------------------------------------------------------------
MS_U32 MApi_VDEC_EX_GetESBuffVacancy(VDEC_StreamId *pStreamId, void *pData);
//-------------------------------------------------------------------------------------------------
/// Get ES buffer to put data
/// @ingroup VDEC_ES_buffer_manage
/// @param eStream \b IN : stream type
/// @param u32ReqSize \b IN : request size
/// @param u32AvailSize \b IN :available size
/// @param u32Addr \b IN : address of ES buffer space
/// @return VDEC_EX_Result
//-------------------------------------------------------------------------------------------------
VDEC_EX_Result  MApi_VDEC_EX_GetESBuff(VDEC_StreamId *pStreamId, MS_U32 u32ReqSize, MS_U32 *u32AvailSize, MS_PHY *u32Addr);
//-------------------------------------------------------------------------------------------------
/// Get next display frame
/// @ingroup VDEC_Display_Q_Control
/// @param eStream \b IN : stream type
/// @param ppDispFrm \b OUT : display frame
/// @return VDEC_EX_Result
//-------------------------------------------------------------------------------------------------
VDEC_EX_Result  MApi_VDEC_EX_GetNextDispFrame(VDEC_StreamId *pStreamId, VDEC_EX_DispFrame **ppDispFrm);
//-------------------------------------------------------------------------------------------------
/// Show display frame
/// @ingroup VDEC_Display_Q_Control
/// @param eStream \b IN : stream type
/// @param pDispFrm \b IN : display frame
/// @return VDEC_EX_Result
//-------------------------------------------------------------------------------------------------
VDEC_EX_Result  MApi_VDEC_EX_DisplayFrame(VDEC_StreamId *pStreamId, VDEC_EX_DispFrame *pDispFrm);
//-------------------------------------------------------------------------------------------------
/// Release display frame
/// @ingroup VDEC_Display_Q_Control
/// @param eStream \b IN : stream type
/// @param pDispFrm \b IN : display frame
/// @return VDEC_EX_Result
//-------------------------------------------------------------------------------------------------
VDEC_EX_Result  MApi_VDEC_EX_ReleaseFrame(VDEC_StreamId *pStreamId, VDEC_EX_DispFrame *pDispFrm);
//-------------------------------------------------------------------------------------------------
/// Capture display frame
/// @ingroup VDEC_Display_Q_Control
/// @param eStream \b IN : stream type
/// @param u32FrmPriData \b IN : specify the freezed frame index
/// @param bEnable \b IN : enable/disable the freeze function
/// @return VDEC_EX_Result
//-------------------------------------------------------------------------------------------------
VDEC_EX_Result  MApi_VDEC_EX_CaptureFrame(VDEC_StreamId *pStreamId, MS_U32 u32FrmPriData, MS_BOOL bEnable);

//used for mstar close caption group
//------------------------------------------------------------------------------
/// Init mstar CC
/// @param eStream \b IN : stream type
/// @ingroup VdecCloseCaption
/// @return VDEC_EX_Result
///     - E_VDEC_EX_OK: Success
///     - E_VDEC_EX_FAIL: Failed
//------------------------------------------------------------------------------
VDEC_EX_Result MApi_VDEC_EX_CC_Init(VDEC_StreamId *pStreamId, MS_U32 *pIn);
//------------------------------------------------------------------------------
/// Set mstar CC config
/// @param eStream \b IN : stream type
/// @param eFmt \b IN : cc format
/// @param eType \b IN : cc type
/// @ingroup VdecCloseCaption
/// @return VDEC_EX_Result
///     - E_VDEC_EX_OK: Success
///     - E_VDEC_EX_FAIL: Failed
//------------------------------------------------------------------------------
VDEC_EX_Result MApi_VDEC_EX_CC_SetCfg(VDEC_StreamId *pStreamId, VDEC_EX_CCFormat eFmt, VDEC_EX_CCType eType, MS_U32 *pIn);
//------------------------------------------------------------------------------
/// Set mstar CC start addr
/// @param eStream \b IN : stream type
/// @param eFmt \b IN : cc format
/// @ingroup VdecCloseCaption
/// @return VDEC_EX_Result
///     - E_VDEC_EX_OK: Success
///     - E_VDEC_EX_FAIL: Failed
//------------------------------------------------------------------------------
VDEC_EX_Result MApi_VDEC_EX_CC_SetBuffStartAdd(VDEC_StreamId *pStreamId, VDEC_EX_CCFormat eFmt, MS_U32 *pIn);
//------------------------------------------------------------------------------
/// Update mstar CC write addr
/// @param eStream \b IN : stream type
/// @param eFmt \b IN : cc format
/// @ingroup VdecCloseCaption
/// @return VDEC_EX_Result
///     - E_VDEC_EX_OK: Success
///     - E_VDEC_EX_FAIL: Failed
//------------------------------------------------------------------------------
VDEC_EX_Result MApi_VDEC_EX_CC_UpdateWriteAdd(VDEC_StreamId *pStreamId, VDEC_EX_CCFormat eFmt, MS_U32 *pIn);
//------------------------------------------------------------------------------
/// Update mstar CC read addr
/// @param eStream \b IN : stream type
/// @param eFmt \b IN : cc format
/// @ingroup VdecCloseCaption
/// @return VDEC_EX_Result
///     - E_VDEC_EX_OK: Success
///     - E_VDEC_EX_FAIL: Failed
//------------------------------------------------------------------------------
VDEC_EX_Result MApi_VDEC_EX_CC_UpdateReadAdd(VDEC_StreamId *pStreamId, VDEC_EX_CCFormat eFmt, MS_U32 *pIn);
//------------------------------------------------------------------------------
/// Disable mstar CC parsing
/// @param eStream \b IN : stream type
/// @param eFmt \b IN : cc format
/// @ingroup VdecCloseCaption
/// @return VDEC_EX_Result
///     - E_VDEC_EX_OK: Success
///     - E_VDEC_EX_FAIL: Failed
//------------------------------------------------------------------------------
VDEC_EX_Result MApi_VDEC_EX_CC_DisableParsing(VDEC_StreamId *pStreamId, VDEC_EX_CCFormat eFmt);
//------------------------------------------------------------------------------
/// Get mstar CC info
/// @param eStream \b IN : stream type
/// @param eFmt \b IN : cc format
/// @ingroup VdecCloseCaption
/// @return VDEC_EX_Result
///     - E_VDEC_EX_OK: Success
///     - E_VDEC_EX_FAIL: Failed
//------------------------------------------------------------------------------
VDEC_EX_Result MApi_VDEC_EX_CC_GetInfo(VDEC_StreamId *pStreamId, VDEC_EX_CCFormat eFmt, VDEC_EX_CCInfoCmd eCmd, MS_U32 *pOut);
//------------------------------------------------------------------------------
/// Check mstar CC is RST done
/// @param eStream \b IN : stream type
/// @param eFmt \b IN : cc format
/// @ingroup VdecCloseCaption
/// @return VDEC_EX_Result
///     - E_VDEC_EX_OK: Success
///     - E_VDEC_EX_FAIL: Failed
//------------------------------------------------------------------------------
VDEC_EX_Result MApi_VDEC_EX_CC_GetIsRstDone(VDEC_StreamId *pStreamId, VDEC_EX_CCFormat eFmt);
//------------------------------------------------------------------------------
/// Check mstar CC is overflow
/// @param eStream \b IN : stream type
/// @param eFmt \b IN : cc format
/// @ingroup VdecCloseCaption
/// @return VDEC_EX_Result
///     - E_VDEC_EX_OK: Success
///     - E_VDEC_EX_FAIL: Failed
//------------------------------------------------------------------------------
VDEC_EX_Result MApi_VDEC_EX_CC_GetIsBuffOverflow(VDEC_StreamId *pStreamId, VDEC_EX_CCFormat eFmt);
//------------------------------------------------------------------------------
/// Get mstar CC write addr
/// @param eStream \b IN : stream type
/// @param eFmt \b IN : cc format
/// @ingroup VdecCloseCaption
/// @return VDEC_EX_Result
///     - E_VDEC_EX_OK: Success
///     - E_VDEC_EX_FAIL: Failed
//------------------------------------------------------------------------------
MS_PHY MApi_VDEC_EX_CC_GetWriteAdd(VDEC_StreamId *pStreamId, VDEC_EX_CCFormat eFmt);
//------------------------------------------------------------------------------
/// Get mstar CC read addr
/// @param eStream \b IN : stream type
/// @param eFmt \b IN : cc format
/// @ingroup VdecCloseCaption
/// @return VDEC_EX_Result
///     - E_VDEC_EX_OK: Success
///     - E_VDEC_EX_FAIL: Failed
//------------------------------------------------------------------------------
MS_PHY MApi_VDEC_EX_CC_GetReadAdd(VDEC_StreamId *pStreamId, VDEC_EX_CCFormat eFmt);

//System preseting function, it should be called when system init.
VDEC_EX_Result MApi_VDEC_EX_SystemPreSetControl(VDEC_EX_User_Cmd cmd_id, void *pParam);
#ifdef VDEC_CAP_SYSTEM_PREGET_API
VDEC_EX_Result MApi_VDEC_EX_SystemPreGetControl(VDEC_EX_User_Cmd cmd_id, void* pParam);
#endif
VDEC_EX_Result MApi_VDEC_EX_SystemPostSetControl(VDEC_EX_User_Cmd cmd_id, void *pParam);
VDEC_EX_Result MApi_VDEC_EX_PreSetControl(VDEC_StreamId *pStreamId, VDEC_EX_User_Cmd cmd_id, MS_U32 param);
#ifdef AUTO_ASSIGN_FRAMEBUFFER
void MApi_VDEC_EX_SetFrameBuffer(MS_U32 u32FrmBufAddr,MS_U32 u32FrmBufSize);
void MApi_VDEC_EX_GetFrmInfoByTask(MS_U8 u8TaskId,MS_BOOL bUHD,MS_BOOL bFileMode,MS_U32* u32FrmBufAddr,MS_U32* u32FrmBufSize);
#endif

#else

#define PROTECTBUFFER_MAX_NUM  3
typedef struct
{
    MS_PHY u32Addr;    // PA
    MS_U32 u32Size;    // unit : byte

} VDEC_EX_TEE_ProtectBufferInfo;


typedef struct
{
    MS_PHY  u32VPUStartAddr;    // PA
    MS_U32  u32VPUCodeSize;     // unit : byte
    MS_PHY  u32FrameBuffertartAddrMain;    // PA
    MS_U32  u32FrameBufferSizeMain;     // unit : byte
    MS_PHY  u32BitstreamStartAddrMain; // PA
    MS_U32  u32BitstreamSizeMain;     // unit : byte
    MS_PHY  u32FrameBuffertartAddrSub;    // PA
    MS_U32  u32FrameBufferSizeSub;     // unit : byte
    MS_PHY  u32BitstreamStartAddrSub; // PA
    MS_U32  u32BitstreamSizeSub;     // unit : byte

    MS_PHY  u32VPUSHMAddr;    // PA
    MS_U32  u32VPUSHMSize;    // unit : byte
    MS_PHY  u32MIU1StartAddr; // PA

    MS_U32  u32ProtectNum;
    VDEC_EX_TEE_ProtectBufferInfo ProtectInfo[PROTECTBUFFER_MAX_NUM];
} VDEC_EX_TEE_VPU_Param;
//Used for OP-TEE
typedef struct
{
   MS_U32 ID[4];//id[3]: 0, id[2]=address_h, id[1]=address_l, id[0]=length
}VDEC_EX_RESOURCE;

typedef enum
{
    ///Setup VDEC relatived buffer
    E_VDEC_EX_SET_VPU_SETTING,
    ///Get VPU Protect start addr
    E_VDEC_EX_GET_VPU_PROTECT_START_ADDR,
    ///VPU Load code in secure world
    E_VDEC_EX_SET_VPU_LOADCODE,
    ///Setup secure buffer
    E_VDEC_EX_SET_SECURE_BUFFER,
    ///Setup secure frame buffer 2
    E_VDEC_EX_SET_SECURE_FB2,
} VDEC_EX_TEE_USER_CMD;
///OP TEE used buffer
typedef enum
{  ///OP-TEE VPU ADDR
    E_VDEC_VPU,
    ///OP-TEE Bitstream Buffer ADDR
    E_VDEC_BS,
    ///OP-TEE Frame Buffer
    E_VDEC_FB,
    ///OP-TEE Frame Buffer 2 ADDR
    E_VDEC_FB2,
} VDEC_EX_OPTEE_Buffer;

//Used for TEE
//------------------------------------------------------------------------------
/// GetControl for TEE
/// @ingroup VDEC_TEE
/// @param cmd \b IN : TEE user cmd
/// @param param \b IN : TEE VPU parameters
/// @return MS_BOOL
//------------------------------------------------------------------------------
MS_BOOL MApi_VDEC_EX_TEE_GetControl(VDEC_EX_TEE_USER_CMD cmd,void* param);


//------------------------------------------------------------------------------
/// SetControl for TEE
/// @ingroup VDEC_TEE
/// @param cmd \b IN : TEE user cmd
/// @param param \b IN : TEE VPU parameters
/// @return MS_BOOL
//------------------------------------------------------------------------------
MS_BOOL MApi_VDEC_EX_TEE_SetControl(VDEC_EX_TEE_USER_CMD cmd,void* param);

//------------------------------------------------------------------------------
/// request a handle mapped to ES buffer with specified size
/// @ingroup VDEC_TEE
/// @param u64PipeID \b IN : handle
/// @param u32ReqSize \b IN : the size needed for this handle
/// @param pu32EsHandle \b OUT : output ES handle
/// @return MS_U32, UTOPIA_STATUS_SUCCESS or UTOPIA_STATUS_FAIL
//------------------------------------------------------------------------------
MS_U32 MApi_VDEC_EX_TEE_AllocateESBufHandle(MS_U64 u64PipeID, MS_U32 u32ReqSize, MS_U32 *pu32EsHandle);

//------------------------------------------------------------------------------
/// get ES relative offset corresponding to an ES handle. This value of this offset is with in
/// 0 and ES buffer size
/// @ingroup VDEC_TEE
/// @param u64PipeID \b IN : handle
/// @param u32EsHandle \b IN : handle
/// @param pPhyAddr \b OUT : address of the buffer mapped with this handle
/// @return MS_U32, UTOPIA_STATUS_SUCCESS or UTOPIA_STATUS_FAIL
//------------------------------------------------------------------------------
MS_U32 MApi_VDEC_EX_TEE_GetESBufByHandle(MS_U64 u64PipeID, MS_U32 u32EsHandle, MS_PHY *pPhyAddr);

//------------------------------------------------------------------------------
/// GetControl for TEE
/// @ingroup VDEC_TEE
/// @return MS_BOOL
//------------------------------------------------------------------------------
MS_BOOL MApi_VDEC_EX_Create_Tee_System(void);
#if defined(UFO_PUBLIC_HEADER_700) || defined(UFO_PUBLIC_HEADER_500)
//------------------------------------------------------------------------------
/// Get address for TEE    //Used for OP-TEE
/// @ingroup VDEC_TEE
/// @param u64PipeID \b IN : stream id
/// @param ResEnum \b IN : TEE lock buffer
/// @param pResouce \b IN : TEE lock buffer parameters
/// @return MS_U32
//------------------------------------------------------------------------------
MS_U32 MDrv_VDEC_GetResourceByPipeNNum(MS_U64 u64PipeID, VDEC_EX_OPTEE_Buffer ResEnum, VDEC_EX_RESOURCE* pResouce);
//------------------------------------------------------------------------------
/// Get address for TEE    //Used for OP-TEE
/// @ingroup VDEC_TEE
/// @param u64PipeID \b IN : stream id
/// @param U32MaxNRetResNum \b IN : TEE number of lock buffers
/// @param pResouce \b IN : TEE lock buffer parameters
/// @return MS_U32
//------------------------------------------------------------------------------
MS_U32 MDrv_VDEC_GetResourceByPipeID(MS_U64 u64PipeID, MS_U32*  U32MaxNRetResNum, VDEC_EX_RESOURCE* pResouce);
//------------------------------------------------------------------------------
/// Check lock status    //Used for OP-TEE
/// @ingroup VDEC_TEE
/// @param u64PipeID \b IN : stream id
/// @param u32SecureDMA \b IN : enable TEE lock
/// @param u32OperationMode \b IN : enable TEE lock
/// @return MS_U32
//------------------------------------------------------------------------------
MS_U32 MDrv_VDEC_ConfigPipe(MS_U64 u64PipeID, MS_U32 u32SecureDMA, MS_U32 u32OperationMode);
//------------------------------------------------------------------------------
/// Check lock status    //Used for OP-TEE
/// @ingroup VDEC_TEE
/// @param u64PipeID \b IN : stream id
/// @param u32SecureDMA \b IN : enable TEE lock
/// @param u32OperationMode \b IN : enable TEE lock
/// @return MS_U32
//------------------------------------------------------------------------------
MS_U32 MDrv_VDEC_CheckPipe(MS_U64 u64PipeID, MS_U32 u32SecureDMA, MS_U32 u32OperationMode);
#endif



#endif

#ifdef __cplusplus
}
#endif


#endif // _API_VDEC_EX_H_

