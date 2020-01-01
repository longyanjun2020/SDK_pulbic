//------------------------------------------------------------------------------
//
//  File        : agc_cfg.h
//  Description : Header file of AGC configuration
//  Author      : Pohan Chen
//  Revision    : 0.0
//
//------------------------------------------------------------------------------
#ifndef _AGC_CFG_H_
#define _AGC_CFG_H_

#define AGC_USE_2MS_TEST_USED                        1
#define DEFAULT_AGC_MAX_GAIN					    (60) 
#define DEFAULT_AGC_MIN_GAIN					    (0)
#define DEFAULT_TARGET_LEVEL					    (-7)
#define DEFAULT_HOLD_TIME						    (12)

#if AGC_USE_2MS_TEST_USED
    #define         DEFAULT_AGC_BlockSize       32
    #define         DEFAULT_AGCDurationMs       2
    #define         DEFAULT_AGCSatDropGain      1
#else
    #define         DEFAULT_AGC_BlockSize       64
    #define         DEFAULT_AGCDurationMs       4
    #define         DEFAULT_AGCSatDropGain      4
#endif

extern  short  gsAGCBlockSize;
extern  short  gsAGCDurationMs;
extern  short  gsAGCSatDropGain;
extern  short  gsAGCMaxGain;
extern  short  gsAGCMinGain;
extern  short  gsAGCTargetLevel;
extern  short  gsAGCHoldTime;
 
#endif // _AGC_CFG_H_

