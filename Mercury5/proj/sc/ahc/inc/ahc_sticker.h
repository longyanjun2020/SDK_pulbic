/**
 @file ahc_ptz.h
 @brief Header File for the ahc ptz(pan tilt zoom)API.
 @author 
 @version 1.0
*/

#ifndef _AHC_STICKER_H_
#define _AHC_STICKER_H_

/*===========================================================================
 * Include files
 *===========================================================================*/ 

#include "ahc_common.h"
#include "ahc_rtc.h"

/*===========================================================================
 * Macro define
 *===========================================================================*/ 

/*===========================================================================
 * Enum define
 *===========================================================================*/ 

/*===========================================================================
 * Structure define
 *===========================================================================*/ 

/*===========================================================================
 * Function prototype
 *===========================================================================*/
AHC_BOOL 	AHC_STICKER_TransRGB565toIndex8(UINT32 uiSrcAddr,  UINT32 uiSrcW,  UINT32 uiSrcH, 
									        UINT32 uiDestAddr, UINT32 uiDestW, UINT32 uiDestH,
									        UINT8  byForegroundColor, UINT8  byBackgroundColor);
AHC_BOOL 	AHC_STICKER_TransDateToString(AHC_RTC_TIME* psRtcTime, INT8* pbyDate, UINT8 byDateConfig, UINT8 byFormatConfig);


#endif // _AHC_STICKER_H_
