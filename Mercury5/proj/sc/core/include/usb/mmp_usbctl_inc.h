//==============================================================================
//
//  File        : mmp_usbctl_inc.h
//  Description : INCLUDE File for the USB Controller Function
//  Author      : Bruce Chien
//  Revision    : 1.0
//
//==============================================================================

#ifndef _MMP_USBCTL_INC_H_
#define _MMP_USBCTL_INC_H_

//==============================================================================
//
//                              INCLUDE FILE
//
//==============================================================================

#include "lib_retina.h"

//==============================================================================
//
//                              CONSTANT
//
//==============================================================================
/*
 * Definition for USB host & device controller
 */


//==============================================================================
//
//                              ENUMERATION
//
//==============================================================================

/// BG Option 2 (INDEX=02h)
/// USB PHY BG Vref Tune
typedef enum _MMP_USBPHY_VREF {
    MMP_USB_VREF_412mV = 0,
    MMP_USB_VREF_400mV,
    MMP_USB_VREF_392mV,
    MMP_USB_VREF_385mV,
    MMP_USB_VREF_MAX
} MMP_USBPHY_VREF;

/// USB PHY BG TRCV Bias Current Option
typedef enum _MMP_USBPHY_BIAS_CURRENT {
    MMP_USB_BIAS_CURRENT_29d84375uA = 0,
    MMP_USB_BIAS_CURRENT_29d6875uA  = 1,
    MMP_USB_BIAS_CURRENT_29d53125uA = 2,
    MMP_USB_BIAS_CURRENT_29d375uA   = 3,
    MMP_USB_BIAS_CURRENT_29d21875uA = 4,
    MMP_USB_BIAS_CURRENT_29d0625uA  = 5,
    MMP_USB_BIAS_CURRENT_28d90625uA = 6,
    MMP_USB_BIAS_CURRENT_28d75uA    = 7,
    MMP_USB_BIAS_CURRENT_28d59375uA = 8,
    MMP_USB_BIAS_CURRENT_28d4375uA  = 9,
    MMP_USB_BIAS_CURRENT_28d28125uA = 10,
    MMP_USB_BIAS_CURRENT_28d125uA   = 11,
    MMP_USB_BIAS_CURRENT_27d96875uA = 12,
    MMP_USB_BIAS_CURRENT_27d8125uA  = 13,
    MMP_USB_BIAS_CURRENT_27d65625uA = 14,
    MMP_USB_BIAS_CURRENT_27d5uA     = 15,
    MMP_USB_BIAS_CURRENT_27d34375uA = 16,
    MMP_USB_BIAS_CURRENT_27d1875uA  = 17,
    MMP_USB_BIAS_CURRENT_27d03125uA = 18,
    MMP_USB_BIAS_CURRENT_26d875uA   = 19,
    MMP_USB_BIAS_CURRENT_26d71875uA = 20,
    MMP_USB_BIAS_CURRENT_26d5625uA  = 21,
    MMP_USB_BIAS_CURRENT_26d40625uA = 22,
    MMP_USB_BIAS_CURRENT_26d25uA    = 23,
    MMP_USB_BIAS_CURRENT_26d09375uA = 24,
    MMP_USB_BIAS_CURRENT_25d9375uA  = 25,
    MMP_USB_BIAS_CURRENT_25d78125uA = 26,
    MMP_USB_BIAS_CURRENT_25d625uA   = 27,
    MMP_USB_BIAS_CURRENT_25d46875uA = 28,
    MMP_USB_BIAS_CURRENT_25d3125uA  = 29,
    MMP_USB_BIAS_CURRENT_25d15625uA = 30,
    MMP_USB_BIAS_CURRENT_25uA       = 31,
    MMP_USB_BIAS_CURRENT_24d84375uA = 32,
    MMP_USB_BIAS_CURRENT_24d6875uA  = 33,
    MMP_USB_BIAS_CURRENT_24d53125uA = 34,
    MMP_USB_BIAS_CURRENT_24d375uA   = 35,
    MMP_USB_BIAS_CURRENT_24d21875uA = 36,
    MMP_USB_BIAS_CURRENT_24d0625uA  = 37,
    MMP_USB_BIAS_CURRENT_23d90625uA = 38,
    MMP_USB_BIAS_CURRENT_23d75uA    = 39,
    MMP_USB_BIAS_CURRENT_23d59375uA = 40,
    MMP_USB_BIAS_CURRENT_23d4375uA  = 41,
    MMP_USB_BIAS_CURRENT_23d28125uA = 42,
    MMP_USB_BIAS_CURRENT_23d125uA   = 43,
    MMP_USB_BIAS_CURRENT_22d96875uA = 44,
    MMP_USB_BIAS_CURRENT_22d8125uA  = 45,
    MMP_USB_BIAS_CURRENT_22d65625uA = 46,
    MMP_USB_BIAS_CURRENT_22d5uA     = 47,
    MMP_USB_BIAS_CURRENT_22d34375uA = 48,
    MMP_USB_BIAS_CURRENT_22d1875uA  = 49,
    MMP_USB_BIAS_CURRENT_22d03125uA = 50,
    MMP_USB_BIAS_CURRENT_21d875uA   = 51,
    MMP_USB_BIAS_CURRENT_21d71875uA = 52,
    MMP_USB_BIAS_CURRENT_21d5625uA  = 53,
    MMP_USB_BIAS_CURRENT_21d40625uA = 54,
    MMP_USB_BIAS_CURRENT_21d25uA    = 55,
    MMP_USB_BIAS_CURRENT_21d09375uA = 56,
    MMP_USB_BIAS_CURRENT_20d9375uA  = 57,
    MMP_USB_BIAS_CURRENT_20d78125uA = 58,
    MMP_USB_BIAS_CURRENT_20d625uA   = 59,
    MMP_USB_BIAS_CURRENT_20d46875uA = 60,
    MMP_USB_BIAS_CURRENT_20d3125uA  = 61,
    MMP_USB_BIAS_CURRENT_20d15625uA = 62,
    MMP_USB_BIAS_CURRENT_20uA       = 63,
    MMP_USB_BIAS_CURRENT_MAX
} MMP_USBPHY_BIAS_CURRENT;

/// HS_TX Option (INDEX=08h)
/// USB PHY HS-TX Current Coarse Tuning Option
typedef enum _MMP_USBPHY_TX_CUR {
    MMP_USB_TX_CUR_200mV = 0,
    MMP_USB_TX_CUR_240mV,
    MMP_USB_TX_CUR_280mV,
    MMP_USB_TX_CUR_320mV,
    MMP_USB_TX_CUR_360mV,
    MMP_USB_TX_CUR_400mV,
    MMP_USB_TX_CUR_440mV,
    MMP_USB_TX_CUR_480mV,
    MMP_USB_TX_CUR_MAX
} MMP_USBPHY_TX_CUR;

/// USB PHY HS-TX Current Fine Tuning Option
typedef enum _MMP_USBPHY_TX_CUR_PLUS {
    MMP_USB_TX_CUR_PLUS_00mV = 0,
    MMP_USB_TX_CUR_PLUS_10mV = 1,
    MMP_USB_TX_CUR_PLUS_20mV = 3,
    MMP_USB_TX_CUR_PLUS_30mV = 5,
    MMP_USB_TX_CUR_PLUS_40mV = 7,
    MMP_USB_TX_CUR_PLUS_MAX
} MMP_USBPHY_TX_CUR_PLUS;

/// SQ Option (INDEX=09h)
/// USB PHY Squelch Level Tuning Option
typedef enum _MMP_USBPHY_SQ {
    MMP_USB_SQ_62d5mV = 0,
    MMP_USB_SQ_75mV,
    MMP_USB_SQ_87d5mV,
    MMP_USB_SQ_100mV,
    MMP_USB_SQ_112d5mV,
    MMP_USB_SQ_125mV,
    MMP_USB_SQ_137d5mV,
    MMP_USB_SQ_150mV,
    MMP_USB_SQ_LEVEL_MAX
} MMP_USBPHY_SQ;

//==============================================================================
//
//                              DATA TYPES
//
//==============================================================================


//==============================================================================
//
//                              STRUCTURE
//
//==============================================================================


//==============================================================================
//
//                              EXTERN VARIABLE
//
//==============================================================================


#endif //_MMP_USBCTL_INC_H_
