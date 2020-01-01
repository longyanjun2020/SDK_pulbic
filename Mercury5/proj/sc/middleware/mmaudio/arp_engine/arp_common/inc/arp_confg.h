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
* @file    : arp_confg.h
* @version :
* @author  : CA.Wang
* @brief   : function and engine config.
*/

#ifndef __ARP_CONFG_H__
#define __ARP_CONFG_H__

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
//#define __OPT_ARP_RUN_ON_TARGET__
//#define __OPT_ARP_RUN_ON_SIMULATOR__

/*============================================================================*/
//                             Simulator Option
/*============================================================================*/
#if defined(__OPT_ARP_RUN_ON_SIMULATOR__)
//---------------------------------------------------------
// ARP Engine Option :
//---------------------------------------------------------
//#define __OPT_ARP_ENGINE_V001__
// #define __OPT_ARP_ENGINE_V002__
//#define __OPT_ARP_ENGINE_V101__
//#define __OPT_ARP_ENGINE_V201__
//#define __OPT_ARP_ENGINE_VFFE__
#define __OPT_ARP_ENGINE_VFFF__

//---------------------------------------------------------
// ARP IP Option :
//---------------------------------------------------------
#if defined(__OPT_ARP_ENGINE_V001__)
#define ARP_SW_AGC_ENABLE
#elif defined(__OPT_ARP_ENGINE_V002__)
#define ARP_SW_GAINCTR_ENABLE
#define ARP_SW_AGC_ENABLE
#elif defined(__OPT_ARP_ENGINE_V101__)
#define ARP_BIG3HW_AGC_ENABLE
#elif defined(__OPT_ARP_ENGINE_V201__)
#define ARP_G1HW_AGC_ENABLE
#elif defined(__OPT_ARP_ENGINE_VFFE__)
#define ARP_SW_GAINCTR_ENABLE
#define ARP_SW_AGC_ENABLE
#define ARP_BIG3HW_AGC_ENABLE
#define ARP_G1HW_AGC_ENABLE
#elif defined(__OPT_ARP_ENGINE_VFFF__)
#define ARP_SW_GAINCTR_ENABLE
#define ARP_SW_AGC_ENABLE
#define ARP_BIG3HW_AGC_ENABLE
#define ARP_G1HW_AGC_ENABLE
#endif

//---------------------------------------------------------
// Example Code Option
//---------------------------------------------------------
#if defined(__OPT_ARP_ENGINE_VFFF__)
//#define ARP_SW_GAINCTR_EXAMPLE
#define ARP_SW_AGC_EXAMPLE
//#define ARP_BIG3HW_AGC_EXAMPLE
//#define ARP_G1HW_AGC_EXAMPLE
#elif defined(__OPT_ARP_ENGINE_VFFE__)
#define ARP_TABLEGTR_EXAMPLE
#else
#define ARP_MGR_EXAMPLE
#endif

#endif

/*============================================================================*/
//                           Running Platform Definition
/*============================================================================*/
#if defined(__mips__)

#if defined(__OPT_ARP_RUN_ON_TARGET__)
#define ARP_ON_B2M3_MIPS_SYSTEM
#elif defined(__OPT_ARP_RUN_ON_SIMULATOR__)
#define ARP_ON_B2M3_MIPS_SIMULATOR
#else
#error Invalid Platform Option!!!
#endif

#elif defined(__arm__)|| defined(__arm)

#if defined(__OPT_ARP_RUN_ON_TARGET__)
#define ARP_ON_B3_ARM9_SYSTEM
#elif defined(__OPT_ARP_RUN_ON_SIMULATOR__)
#define ARP_ON_B3_ARM9_SIMULATOR
#else
#error Invalid Platform Option!!!
#endif

#elif defined(__aeon__) || defined(__i686__)

#if defined(__OPT_ARP_RUN_ON_TARGET__)
#define ARP_ON_G1_AEON_SYSTEM
#elif defined(__OPT_ARP_RUN_ON_SIMULATOR__)
#define ARP_ON_G1_AEON_SIMULATOR
#else
#error Invalid Platform Option!!!
#endif

#elif defined(_MSC_VER)

#if defined(__OPT_ARP_RUN_ON_TARGET__)
#define ARP_ON_MSC
#elif defined(__OPT_ARP_RUN_ON_SIMULATOR__)
#define ARP_ON_MSC
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
#define ARP_SW_GAINCTR_ID  0x0101
#define ARP_SW_AGC_ID      0x0201 // SW AGC
#define ARP_BIG2HW_AGC_ID  0x0202 // BIG2 HW AGC
#define ARP_BIG3HW_AGC_ID  0x0203 // BIG3 HW AGC
#define ARP_G1HW_AGC_ID    0x0204 // G1 HW AGC

//[0x5000~0x50FF] : External IP
//...

/*============================================================================*/
//                              Engine ID Definition
/*============================================================================*/
//[0xA001~0xADFF] : Internal Engine
#define ARP_V001_ENGINE_ID 0xA001 
#define ARP_V002_ENGINE_ID 0xA002 

#define ARP_V101_ENGINE_ID 0xA101 // BIG3 HW Engine
#define ARP_V201_ENGINE_ID 0xA201 // G1 HW Engine

//[0xAEO0~0xAEFF] : External Engine
//...

//[0xAF00~0xAFFF] : Others
#define ARP_VFFE_ENGINE_ID 0xAFFE // ARP Calibration Tool
#define ARP_VFFF_ENGINE_ID 0xAFFF // For Test

/*============================================================================*/
//                           Target Engine ID Definition
/*============================================================================*/
#if defined(__OPT_ARP_ENGINE_V001__)
#define ARP_TARGET_ENGINE ARP_V001_ENGINE_ID
#elif defined(__OPT_ARP_ENGINE_V002__)
#define ARP_TARGET_ENGINE ARP_V002_ENGINE_ID
#elif defined(__OPT_ARP_ENGINE_V101__)
#define ARP_TARGET_ENGINE ARP_V101_ENGINE_ID
#elif defined(__OPT_ARP_ENGINE_V201__)
#define ARP_TARGET_ENGINE ARP_V201_ENGINE_ID
#elif defined(__OPT_ARP_ENGINE_VFFE__)
#define ARP_TARGET_ENGINE ARP_VFFE_ENGINE_ID
#elif defined(__OPT_ARP_ENGINE_VFFF__)
#define ARP_TARGET_ENGINE ARP_VFFF_ENGINE_ID
#endif


#endif // __ARP_CONFG_H__

