////////////////////////////////////////////////////////////////////////////////
//
// Copyright (c) 2006-2009 MStar Semiconductor, Inc.
// All rights reserved.
//
// Unless otherwise stipulated in writing, any and all information contained
// herein regardless in any format shall remain the sole proprietary of
// MStar Semiconductor Inc. and be kept in strict confidence
// (¡§MStar Confidential Information¡¨) by the recipient.
// Any unauthorized act including without limitation unauthorized disclosure,
// copying, use, reproduction, sale, distribution, modification, disassembling,
// reverse engineering and compiling of the contents of MStar Confidential
// Information is unlawful and strictly prohibited. MStar hereby reserves the
// rights to any and all damages, losses, costs and expenses resulting therefrom.
//
////////////////////////////////////////////////////////////////////////////////

/**
* @file    : app_confg.h
* @version :
* @author  : CA.Wang
* @brief   : function and engine config.
*/

#ifndef __APP_CONFG_H__
#define __APP_CONFG_H__

/*============================================================================*/
//                             Master Option
/*============================================================================*/

//---------------------------------------------------------
// DSP Option : This is default definiton in compiler
//
// __mpis__ : MIPS
// __arm__  : ARM
// __aeon__ : AEON
// _MSC_VER : PC MSVC
//
//---------------------------------------------------------
//#define __mpis__
//#define __arm__
//#define __aeon__
//#define _MSC_VER

//---------------------------------------------------------
// Running Platform Option : The definition need to add in
//                           make file or preprcessor
//
// __OPT_APP_RUN_ON_TARGET__    : RTK OS, ECOS OS,
// __OPT_APP_RUN_ON_SIMULATOR__ : MIPSim, ARMulater, MSVC...
//
//---------------------------------------------------------
//#define __OPT_APP_RUN_ON_TARGET__
//#define __OPT_APP_RUN_ON_SIMULATOR__

/*============================================================================*/
//                  APP Engine Definition (Only For Simulator)
/*============================================================================*/
#if defined(__OPT_APP_RUN_ON_SIMULATOR__)
//---------------------------------------------------------
// APP Engine Option :
//---------------------------------------------------------
//#define __OPT_APP_ENGINE_V001__
//#define __OPT_APP_ENGINE_V002__
//#define __OPT_APP_ENGINE_V003__
//#define __OPT_APP_ENGINE_V004__
//#define __OPT_APP_ENGINE_V005__
//#define __OPT_APP_ENGINE_V006__
//#define __OPT_APP_ENGINE_V007__
//#define __OPT_APP_ENGINE_V008__
//#define __OPT_APP_ENGINE_V009__
//#define __OPT_APP_ENGINE_V00A__
//#define __OPT_APP_ENGINE_V00B__
//#define __OPT_APP_ENGINE_V00C__
//#define __OPT_APP_ENGINE_V00D__
//#define __OPT_APP_ENGINE_V00E__
//#define __OPT_APP_ENGINE_V00F__
#define __OPT_APP_ENGINE_V010__
//#define __OPT_APP_ENGINE_V011__
//#define __OPT_APP_ENGINE_V012__
//#define __OPT_APP_ENGINE_V013__
//#define __OPT_APP_ENGINE_V014__
//#define __OPT_APP_ENGINE_V015__
//#define __OPT_APP_ENGINE_V016__
//#define __OPT_APP_ENGINE_V017__
//#define __OPT_APP_ENGINE_V018__
//#define __OPT_APP_ENGINE_V101__
//#define __OPT_APP_ENGINE_V201__
//#define __OPT_APP_ENGINE_VE01__
//#define __OPT_APP_ENGINE_VFFE__
//#define __OPT_APP_ENGINE_VFFF__

//---------------------------------------------------------
// APP IP Option :
//---------------------------------------------------------
#if defined(__OPT_APP_ENGINE_V001__)
#define ENABLE_3D_SURROUND
#define ENABLE_USER_PEQ
#define ENABLE_SPEAKER_PEQ
#define ENABLE_DRC_LIMITER
#elif defined(__OPT_APP_ENGINE_V002__)
#define ENABLE_3D_SURROUND
#define ENABLE_USER_PEQ
#define ENABLE_SPEAKER_PEQ
#define ENABLE_VOL_CONTROL_EXP
#define ENABLE_DRC_LIMITER
#elif defined(__OPT_APP_ENGINE_V003__)
#define ENABLE_3D_SURROUND
#define ENABLE_USER_PEQ
#define ENABLE_SPEAKER_PEQ
#define ENABLE_VOL_CONTROL_EXP
#define ENABLE_LOOKAHEAD_DRC_LIMITER
#elif defined(__OPT_APP_ENGINE_V004__)
#define ENABLE_3D_SURROUND
#define ENABLE_USER_PEQ
#define ENABLE_SPEAKER_PEQ
#define ENABLE_VOL_CONTROL_EXP
#define ENABLE_HARD_LIMITER
#elif defined(__OPT_APP_ENGINE_V005__)
#define ENABLE_3D_SURROUND
#define ENABLE_USER_PEQ
#define ENABLE_SPEAKER_PEQ
#define ENABLE_VOL_CONTROL_EXP
#define ENABLE_DRC_LIMITER
#define ENABLE_SC_FADE
#elif defined(__OPT_APP_ENGINE_V006__)
#define ENABLE_3D_SURROUND
#define ENABLE_USER_PEQ
#define ENABLE_SPEAKER_PEQ
#define ENABLE_VOL_CONTROL_EXP
#define ENABLE_LOOKAHEAD_DRC_LIMITER
#define ENABLE_SC_FADE
#elif defined(__OPT_APP_ENGINE_V007__)
#define ENABLE_3D_SURROUND
#define ENABLE_USER_PEQ
#define ENABLE_SPEAKER_PEQ
#define ENABLE_VOL_CONTROL_EXP
#define ENABLE_HARD_LIMITER
#define ENABLE_SC_FADE
#elif defined(__OPT_APP_ENGINE_V008__)
#define ENABLE_3D_SURROUND
#define ENABLE_USER_PEQ
#define ENABLE_SPEAKER_PEQ
#define ENABLE_VOL_CONTROL_EXP
#define ENABLE_DRC_LIMITER
#define ENABLE_SC_FADE
#define ENABLE_TIME_STRETCH
#elif defined(__OPT_APP_ENGINE_V009__)
#define ENABLE_3D_SURROUND
#define ENABLE_USER_PEQ
#define ENABLE_SPEAKER_PEQ
#define ENABLE_VOL_CONTROL_EXP
#define ENABLE_DRC_LIMITER
#define ENABLE_SC_FADE
#define ENABLE_TIMEPITCH_STRETCH
#elif defined(__OPT_APP_ENGINE_V00A__)
#define ENABLE_SPEAKER_PEQ
#define ENABLE_DRC_LIMITER
#elif defined(__OPT_APP_ENGINE_V00B__)
#define ENABLE_SPEAKER_PEQ
#define ENABLE_DRC_LIMITER
#define ENABLE_3D_SURROUND
#define ENABLE_SC_FADE
#elif defined(__OPT_APP_ENGINE_V00C__)
#define ENABLE_3D_SURROUND
#define ENABLE_USER_PEQ
#define ENABLE_SPEAKER_PEQ
#define ENABLE_VOL_CONTROL_EXP
#define ENABLE_DRC_LIMITER
#define ENABLE_SC_FADE
#define ENABLE_REVERB
#elif defined(__OPT_APP_ENGINE_V00D__)
#define ENABLE_3D_SURROUND
#define ENABLE_USER_PEQ
#define ENABLE_SPEAKER_PEQ
#define ENABLE_VOL_CONTROL_EXP
#define ENABLE_DRC_LIMITER
#define ENABLE_SC_FADE
#define ENABLE_REVERB
#define ENABLE_TIMEPITCH_STRETCH
#elif defined(__OPT_APP_ENGINE_V00E__)
#define ENABLE_3D_SURROUND
#define ENABLE_USER_PEQ
#define ENABLE_SPEAKER_PEQ
#define ENABLE_VOL_CONTROL_EXP
#define ENABLE_DRC_LIMITER
#define ENABLE_SC_FADE
#define ENABLE_REVERB
#define ENABLE_TIME_STRETCH
#elif defined(__OPT_APP_ENGINE_V00F__)
#define ENABLE_3D_SURROUND
#define ENABLE_USER_PEQ
#define ENABLE_SPEAKER_PEQ
#define ENABLE_VOL_CONTROL_EXP
#define ENABLE_DRC_LIMITER
#define ENABLE_SC_FADE
#define ENABLE_REVERB
#define ENABLE_TIME_STRETCH
#define ENABLE_TIMEPITCH_STRETCH
#elif defined(__OPT_APP_ENGINE_V010__)
#define ENABLE_SPEAKER_PEQ
#define ENABLE_DRC_LIMITER_V2
#elif defined(__OPT_APP_ENGINE_V011__)
#define ENABLE_3D_SURROUND
#define ENABLE_USER_PEQ
#define ENABLE_SPEAKER_PEQ
#define ENABLE_VOL_CONTROL_EXP
#define ENABLE_DRC_LIMITER_V2
#define ENABLE_SC_FADE
#elif defined(__OPT_APP_ENGINE_V012__)
#define ENABLE_3D_SURROUND
#define ENABLE_USER_PEQ
#define ENABLE_SPEAKER_PEQ
#define ENABLE_VOL_CONTROL_EXP
#define ENABLE_DRC_LIMITER_V2
#define ENABLE_SC_FADE
#define ENABLE_TIMEPITCH_STRETCH
#elif defined(__OPT_APP_ENGINE_V013__)
#define ENABLE_3D_SURROUND
#define ENABLE_USER_PEQ
#define ENABLE_SPEAKER_PEQ
#define ENABLE_VOL_CONTROL_EXP
#define ENABLE_DRC_LIMITER_V2
#define ENABLE_SC_FADE
#define ENABLE_TIME_STRETCH
#elif defined(__OPT_APP_ENGINE_V014__)
#define ENABLE_3D_SURROUND
#define ENABLE_USER_PEQ
#define ENABLE_SPEAKER_PEQ
#define ENABLE_VOL_CONTROL_EXP
#define ENABLE_DRC_LIMITER_V2
#define ENABLE_SC_FADE
#define ENABLE_TIME_STRETCH
#define ENABLE_TIMEPITCH_STRETCH
#elif defined(__OPT_APP_ENGINE_V015__)
#define ENABLE_3D_SURROUND
#define ENABLE_USER_PEQ
#define ENABLE_SPEAKER_PEQ
#define ENABLE_VOL_CONTROL_EXP
#define ENABLE_DRC_LIMITER_V2
#define ENABLE_SC_FADE
#define ENABLE_REVERB
#elif defined(__OPT_APP_ENGINE_V016__)
#define ENABLE_3D_SURROUND
#define ENABLE_USER_PEQ
#define ENABLE_SPEAKER_PEQ
#define ENABLE_VOL_CONTROL_EXP
#define ENABLE_DRC_LIMITER_V2
#define ENABLE_SC_FADE
#define ENABLE_REVERB
#define ENABLE_TIMEPITCH_STRETCH
#elif defined(__OPT_APP_ENGINE_V017__)
#define ENABLE_3D_SURROUND
#define ENABLE_USER_PEQ
#define ENABLE_SPEAKER_PEQ
#define ENABLE_VOL_CONTROL_EXP
#define ENABLE_DRC_LIMITER_V2
#define ENABLE_SC_FADE
#define ENABLE_REVERB
#define ENABLE_TIME_STRETCH
#elif defined(__OPT_APP_ENGINE_V018__)
#define ENABLE_3D_SURROUND
#define ENABLE_USER_PEQ
#define ENABLE_SPEAKER_PEQ
#define ENABLE_VOL_CONTROL_EXP
#define ENABLE_DRC_LIMITER_V2
#define ENABLE_SC_FADE
#define ENABLE_REVERB
#define ENABLE_TIME_STRETCH
#define ENABLE_TIMEPITCH_STRETCH
#elif defined(__OPT_APP_ENGINE_V01A__)
#define ENABLE_SPEAKER_PEQ
#define ENABLE_VOL_CONTROL_EXP
#define ENABLE_DRC_LIMITER
#elif defined(__OPT_APP_ENGINE_V020__)
#define ENABLE_3D_SURROUND
#define ENABLE_USER_PEQ
#define ENABLE_SPEAKER_PEQ
#define ENABLE_VOL_CONTROL_EXP
#define ENABLE_DRC_LIMITER_V2
#define ENABLE_SC_FADE
#define ENABLE_REVERB
#define ENABLE_TIME_STRETCH
#define ENABLE_TIMEPITCH_STRETCH
#define ENABLE_BASS
#define ENABLE_SRSWOWHD
#elif defined(__OPT_APP_ENGINE_V021__)
#define ENABLE_3D_SURROUND
#define ENABLE_USER_PEQ
#define ENABLE_SPEAKER_PEQ
#define ENABLE_VOL_CONTROL_EXP
#define ENABLE_DRC_LIMITER
#define ENABLE_SC_FADE
#define ENABLE_BASS
#elif defined(__OPT_APP_ENGINE_V022__)
#define ENABLE_3D_SURROUND
#define ENABLE_USER_PEQ
#define ENABLE_SPEAKER_PEQ
#define ENABLE_VOL_CONTROL_EXP
#define ENABLE_DRC_LIMITER
#define ENABLE_SC_FADE
#define ENABLE_TIMEPITCH_STRETCH
#define ENABLE_BASS
#elif defined(__OPT_APP_ENGINE_V023__)
#define ENABLE_3D_SURROUND
#define ENABLE_USER_PEQ
#define ENABLE_SPEAKER_PEQ
#define ENABLE_VOL_CONTROL_EXP
#define ENABLE_DRC_LIMITER_V2
#define ENABLE_SC_FADE
#define ENABLE_TIME_STRETCH
#define ENABLE_BASS
#elif defined(__OPT_APP_ENGINE_V024__)
#define ENABLE_3D_SURROUND
#define ENABLE_USER_PEQ
#define ENABLE_SPEAKER_PEQ
#define ENABLE_VOL_CONTROL_EXP
#define ENABLE_DRC_LIMITER_V2
#define ENABLE_SC_FADE
#define ENABLE_TIME_STRETCH
#define ENABLE_TIMEPITCH_STRETCH
#define ENABLE_BASS
#elif defined(__OPT_APP_ENGINE_V025__)
#define ENABLE_3D_SURROUND
#define ENABLE_USER_PEQ
#define ENABLE_SPEAKER_PEQ
#define ENABLE_VOL_CONTROL_EXP
#define ENABLE_DRC_LIMITER_V2
#define ENABLE_SC_FADE
#define ENABLE_REVERB
#define ENABLE_BASS
#elif defined(__OPT_APP_ENGINE_V026__)
#define ENABLE_3D_SURROUND
#define ENABLE_USER_PEQ
#define ENABLE_SPEAKER_PEQ
#define ENABLE_VOL_CONTROL_EXP
#define ENABLE_DRC_LIMITER_V2
#define ENABLE_SC_FADE
#define ENABLE_REVERB
#define ENABLE_TIMEPITCH_STRETCH
#define ENABLE_BASS
#elif defined(__OPT_APP_ENGINE_V027__)
#define ENABLE_3D_SURROUND
#define ENABLE_USER_PEQ
#define ENABLE_SPEAKER_PEQ
#define ENABLE_VOL_CONTROL_EXP
#define ENABLE_DRC_LIMITER_V2
#define ENABLE_SC_FADE
#define ENABLE_REVERB
#define ENABLE_TIME_STRETCH
#define ENABLE_BASS
#elif defined(__OPT_APP_ENGINE_V028__)
#define ENABLE_3D_SURROUND
#define ENABLE_USER_PEQ
#define ENABLE_SPEAKER_PEQ
#define ENABLE_VOL_CONTROL_EXP
#define ENABLE_DRC_LIMITER_V2
#define ENABLE_SC_FADE
#define ENABLE_REVERB
#define ENABLE_TIME_STRETCH
#define ENABLE_TIMEPITCH_STRETCH
#define ENABLE_BASS


#elif defined(__OPT_APP_ENGINE_V101__)
#define ENABLE_3D_SURROUND
#define ENABLE_VOL_CONTROL_EXP
#define ENABLE_BIG3HW_GEQ
#define ENABLE_BIG3HW_PEQ
#define ENABLE_BIG3HW_DRC
#define ENABLE_SC_FADE
#elif defined(__OPT_APP_ENGINE_V201__)
#define ENABLE_3D_SURROUND
#define ENABLE_VOL_CONTROL_EXP
#define ENABLE_G1HW_GEQ
#define ENABLE_G1HW_PEQ
#define ENABLE_G1HW_DRC
#define ENABLE_SC_FADE
#elif defined(__OPT_APP_ENGINE_VE01__)
#define ENABLE_VOL_CONTROL_EXP
#define ENABLE_SC_FADE
#define ENABLE_DM2
#elif defined(__OPT_APP_ENGINE_VE02__)
#define ENABLE_SPEAKER_PEQ
#define ENABLE_VOL_CONTROL_EXP
#define ENABLE_SC_FADE
#define ENABLE_SRSWOWHD
#elif defined(__OPT_APP_ENGINE_VFFE__) // For Table Generator (Include All IP)
#define ENABLE_TIME_STRETCH
#define ENABLE_TIMEPITCH_STRETCH
#define ENABLE_3D_SURROUND
#define ENABLE_USER_PEQ
#define ENABLE_BIG3HW_GEQ
#define ENABLE_G1HW_GEQ
#define ENABLE_SPEAKER_PEQ
#define ENABLE_BIG3HW_PEQ
#define ENABLE_G1HW_PEQ
#define ENABLE_VOL_CONTROL_EXP
#define ENABLE_DRC_LIMITER
#define ENABLE_DRC_LIMITER_V2
#define ENABLE_LOOKAHEAD_DRC_LIMITER
#define ENABLE_HARD_LIMITER
#define ENABLE_BIG3HW_DRC
#define ENABLE_G1HW_DRC
#define ENABLE_SC_FADE
#define ENABLE_DM2
#define ENABLE_REVERB
#define ENABLE_SRSWOWHD
#elif defined(__OPT_APP_ENGINE_VFFF__) // For Example Test
#define ENABLE_TIME_STRETCH
#define ENABLE_TIMEPITCH_STRETCH
#define ENABLE_3D_SURROUND
#define ENABLE_USER_PEQ
#define ENABLE_BIG3HW_GEQ
#define ENABLE_G1HW_GEQ
#define ENABLE_SPEAKER_PEQ
#define ENABLE_BIG3HW_PEQ
#define ENABLE_G1HW_PEQ
#define ENABLE_VOL_CONTROL_EXP
#define ENABLE_DRC_LIMITER
#define ENABLE_DRC_LIMITER_V2
#define ENABLE_LOOKAHEAD_DRC_LIMITER
#define ENABLE_HARD_LIMITER
#define ENABLE_BIG3HW_DRC
#define ENABLE_G1HW_DRC
#define ENABLE_SC_FADE
#define ENABLE_DM2
#define ENABLE_REVERB
#define ENABLE_SRSWOWHD
#endif

//---------------------------------------------------------
// Example Code Option
//---------------------------------------------------------
#if defined(__OPT_APP_ENGINE_VFFF__)
//#define TIME_STRETCH_EXAMPLE
//#define TIMEPITCH_STRETCH_EXAMPLE
//#define SURROUND_EXAMPLE
//#define USER_PEQ_EXAMPLE
//#define BIG3HW_GEQ_EXAMPLE
//#define G1HW_GEQ_EXAMPLE
//#define SPEAKER_PEQ_EXAMPLE
//#define BIG3HW_PEQ_EXAMPLE
//#define G1HW_PEQ_EXAMPLE
//#define EXP_VOL_EXAMPLE
//#define DRCLIMITER_EXAMPLE
#define DRCLIMITER_V2_EXAMPLE
//#define LOOKAHEADDRCLIMITER_EXAMPLE
//#define HARDLIMITER_EXAMPLE
//#define BIG3HW_DRC_EXAMPLE
//#define G1HW_DRC_EXAMPLE
//#define SC_FADE_EXAMPLE
#elif defined(__OPT_APP_ENGINE_VFFE__)
#define POSTPROCTABLEGTR_EXAMPLE
//#define POSTPROCTABLEGTR_PEQFREQZ_EXAMPLE
#else
//#define POSTPROCMGR_EXAMPLE
#define POSTPROCMGR_SHELL_EXAMPLE
#endif

#endif

/*============================================================================*/
//                           Running Platform Definition
/*============================================================================*/
#if defined(__mips__)

#if defined(__OPT_APP_RUN_ON_TARGET__)
#define APP_ON_B2M3_MIPS_SYSTEM
#elif defined(__OPT_APP_RUN_ON_SIMULATOR__)
#define APP_ON_B2M3_MIPS_SIMULATOR
#else
#error Invalid Platform Option!!!
#endif

#elif defined(__arm__) || defined(__arm)

#if defined(__OPT_APP_RUN_ON_TARGET__)
#define APP_ON_B3_ARM9_SYSTEM
#elif defined(__OPT_APP_RUN_ON_SIMULATOR__)
#define APP_ON_B3_ARM9_SIMULATOR
#else
#error Invalid Platform Option!!!
#endif

#elif defined(__aeon__) || defined(__i686__)

#if defined(__OPT_APP_RUN_ON_TARGET__)
#define APP_ON_G1_AEON_SYSTEM
#elif defined(__OPT_APP_RUN_ON_SIMULATOR__)
#define APP_ON_G1_AEON_SIMULATOR
#else
#error Invalid Platform Option!!!
#endif

#elif defined(_MSC_VER)

#if defined(__OPT_APP_RUN_ON_TARGET__)
#define APP_ON_MSC
#elif defined(__OPT_APP_RUN_ON_SIMULATOR__)
#define APP_ON_MSC
#else
#error Invalid Platform Option!!!
#endif

#else

#error Invalid Platform Option!!!

#endif

/*============================================================================*/
//                                IP ID Definition
/*============================================================================*/
//[0x0100~0x4FFF] : Internal IP
#define APP_BASIC_SURROUND_ID         0x0101
#define APP_REVERB_ID                 0x0102
#define APP_USER_PEQ_ID               0x0201
#define APP_BIG3HW_GEQ_ID             0x0202 // BIG3 HW
#define APP_G1HW_GEQ_ID               0x0203 // G1 HW
#define APP_SPEAKER_PEQ_ID            0x0301
#define APP_BIG3HW_PEQ_ID             0x0302 // BIG3 HW
#define APP_G1HW_PEQ_ID               0x0303 // G1 HW
#define APP_DRC_LIMITER_ID            0x0401
#define APP_LOOKAHEAD_DRC_LIMITER_ID  0x0402
#define APP_HARD_LIMITER_ID           0x0403
#define APP_BIG3HW_DRC_ID             0x0404 // BIG3 HW
#define APP_G1HW_DRC_ID               0x0405 // G1 HW
#define APP_DRC_LIMITER_V2_ID         0x0406
#define APP_EXP_VOL_ID                0x0501
#define APP_SC_FADE_ID                0x0601
#define APP_TIME_STRETCH_ID           0x0701
#define APP_TIMEPITCH_STRETCH_ID      0x0702
#define APP_BASS_ID                     0x0801

//[0x5000~0x9FFF] : External IP
#define APP_DM2_ID                    0x5101
#define APP_SRSWOWHD_ID               0x5201

/*============================================================================*/
//                              Engine ID Definition
/*============================================================================*/
//[0xA001~0xADFF] : Internal Engine
#define APP_V001_ENGINE_ID 0xA001
#define APP_V002_ENGINE_ID 0xA002
#define APP_V003_ENGINE_ID 0xA003
#define APP_V004_ENGINE_ID 0xA004
#define APP_V005_ENGINE_ID 0xA005
#define APP_V006_ENGINE_ID 0xA006
#define APP_V007_ENGINE_ID 0xA007
#define APP_V008_ENGINE_ID 0xA008
#define APP_V009_ENGINE_ID 0xA009
#define APP_V00A_ENGINE_ID 0xA00A
#define APP_V00B_ENGINE_ID 0xA00B
#define APP_V00C_ENGINE_ID 0xA00C
#define APP_V00D_ENGINE_ID 0xA00D
#define APP_V00E_ENGINE_ID 0xA00E
#define APP_V00F_ENGINE_ID 0xA00F

#define APP_V010_ENGINE_ID 0xA010
#define APP_V011_ENGINE_ID 0xA011
#define APP_V012_ENGINE_ID 0xA012
#define APP_V013_ENGINE_ID 0xA013
#define APP_V014_ENGINE_ID 0xA014
#define APP_V015_ENGINE_ID 0xA015
#define APP_V016_ENGINE_ID 0xA016
#define APP_V017_ENGINE_ID 0xA017
#define APP_V018_ENGINE_ID 0xA018
#define APP_V01A_ENGINE_ID 0xA01A
#define APP_V020_ENGINE_ID 0xA020
#define APP_V021_ENGINE_ID 0xA021
#define APP_V022_ENGINE_ID 0xA022
#define APP_V023_ENGINE_ID 0xA023
#define APP_V024_ENGINE_ID 0xA024
#define APP_V025_ENGINE_ID 0xA025
#define APP_V026_ENGINE_ID 0xA026
#define APP_V027_ENGINE_ID 0xA027
#define APP_V028_ENGINE_ID 0xA028

#define APP_V101_ENGINE_ID 0xA101 // BIG3 HW Engine
#define APP_V201_ENGINE_ID 0xA201 // G1 HW Engine

//[0xAEO0~0xAEFF] : External Engine
#define APP_VE01_ENGINE_ID 0xAE01 // 3RD MD2 Engine
#define APP_VE02_ENGINE_ID 0xAE02 // 3RD SRSWOWHD Engine

//[0xAF00~0xAFFF] : Others
#define APP_VFFE_ENGINE_ID 0xAFFE // For Calibration Tool
#define APP_VFFF_ENGINE_ID 0xAFFF // For Test

/*============================================================================*/
//                           Target Engine ID Definition
/*============================================================================*/
#if defined(__OPT_APP_ENGINE_V001__)
#define TARGET_ENGINE APP_V001_ENGINE_ID
#elif defined(__OPT_APP_ENGINE_V002__)
#define TARGET_ENGINE APP_V002_ENGINE_ID
#elif defined(__OPT_APP_ENGINE_V003__)
#define TARGET_ENGINE APP_V003_ENGINE_ID
#elif defined(__OPT_APP_ENGINE_V004__)
#define TARGET_ENGINE APP_V004_ENGINE_ID
#elif defined(__OPT_APP_ENGINE_V005__)
#define TARGET_ENGINE APP_V005_ENGINE_ID
#elif defined(__OPT_APP_ENGINE_V006__)
#define TARGET_ENGINE APP_V006_ENGINE_ID
#elif defined(__OPT_APP_ENGINE_V007__)
#define TARGET_ENGINE APP_V007_ENGINE_ID
#elif defined(__OPT_APP_ENGINE_V008__)
#define TARGET_ENGINE APP_V008_ENGINE_ID
#elif defined(__OPT_APP_ENGINE_V009__)
#define TARGET_ENGINE APP_V009_ENGINE_ID
#elif defined(__OPT_APP_ENGINE_V00A__)
#define TARGET_ENGINE APP_V00A_ENGINE_ID
#elif defined(__OPT_APP_ENGINE_V00B__)
#define TARGET_ENGINE APP_V00B_ENGINE_ID
#elif defined(__OPT_APP_ENGINE_V00C__)
#define TARGET_ENGINE APP_V00C_ENGINE_ID
#elif defined(__OPT_APP_ENGINE_V00D__)
#define TARGET_ENGINE APP_V00D_ENGINE_ID
#elif defined(__OPT_APP_ENGINE_V00E__)
#define TARGET_ENGINE APP_V00E_ENGINE_ID
#elif defined(__OPT_APP_ENGINE_V00F__)
#define TARGET_ENGINE APP_V00F_ENGINE_ID

#elif defined(__OPT_APP_ENGINE_V010__)
#define TARGET_ENGINE APP_V010_ENGINE_ID
#elif defined(__OPT_APP_ENGINE_V011__)
#define TARGET_ENGINE APP_V011_ENGINE_ID
#elif defined(__OPT_APP_ENGINE_V012__)
#define TARGET_ENGINE APP_V012_ENGINE_ID
#elif defined(__OPT_APP_ENGINE_V013__)
#define TARGET_ENGINE APP_V013_ENGINE_ID
#elif defined(__OPT_APP_ENGINE_V014__)
#define TARGET_ENGINE APP_V014_ENGINE_ID
#elif defined(__OPT_APP_ENGINE_V015__)
#define TARGET_ENGINE APP_V015_ENGINE_ID
#elif defined(__OPT_APP_ENGINE_V016__)
#define TARGET_ENGINE APP_V016_ENGINE_ID
#elif defined(__OPT_APP_ENGINE_V017__)
#define TARGET_ENGINE APP_V017_ENGINE_ID
#elif defined(__OPT_APP_ENGINE_V018__)
#define TARGET_ENGINE APP_V018_ENGINE_ID
#elif defined(__OPT_APP_ENGINE_V01A__)
#define TARGET_ENGINE APP_V01A_ENGINE_ID
#elif defined(__OPT_APP_ENGINE_V020__)
#define TARGET_ENGINE APP_V020_ENGINE_ID
#elif defined(__OPT_APP_ENGINE_V021__)
#define TARGET_ENGINE APP_V021_ENGINE_ID
#elif defined(__OPT_APP_ENGINE_V022__)
#define TARGET_ENGINE APP_V022_ENGINE_ID
#elif defined(__OPT_APP_ENGINE_V023__)
#define TARGET_ENGINE APP_V023_ENGINE_ID
#elif defined(__OPT_APP_ENGINE_V024__)
#define TARGET_ENGINE APP_V024_ENGINE_ID
#elif defined(__OPT_APP_ENGINE_V025__)
#define TARGET_ENGINE APP_V025_ENGINE_ID
#elif defined(__OPT_APP_ENGINE_V026__)
#define TARGET_ENGINE APP_V026_ENGINE_ID
#elif defined(__OPT_APP_ENGINE_V027__)
#define TARGET_ENGINE APP_V027_ENGINE_ID
#elif defined(__OPT_APP_ENGINE_V028__)
#define TARGET_ENGINE APP_V028_ENGINE_ID

#elif defined(__OPT_APP_ENGINE_V101__)
#define TARGET_ENGINE APP_V101_ENGINE_ID
#elif defined(__OPT_APP_ENGINE_V201__)
#define TARGET_ENGINE APP_V201_ENGINE_ID

#elif defined(__OPT_APP_ENGINE_VE01__)
#define TARGET_ENGINE APP_VE01_ENGINE_ID
#elif defined(__OPT_APP_ENGINE_VE02__)
#define TARGET_ENGINE APP_VE02_ENGINE_ID

#elif defined(__OPT_APP_ENGINE_VFFE__)
#define TARGET_ENGINE APP_VFFE_ENGINE_ID
#elif defined(__OPT_APP_ENGINE_VFFF__)
#define TARGET_ENGINE APP_VFFF_ENGINE_ID
#endif



#endif // __APP_CONFG_H__

