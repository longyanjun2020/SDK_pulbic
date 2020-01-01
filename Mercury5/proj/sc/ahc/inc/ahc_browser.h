/**
 @file ahc_browser.h
 @brief Header File for the AHC browser API.
 @author 
 @version 1.0
*/

#ifndef _AHC_BROWSER_H_
#define _AHC_BROWSER_H_

/*===========================================================================
 * Include files
 *===========================================================================*/ 

#include "ahc_common.h"
#include "ahc_gui.h"
#include "aihc_protection_inc.h"

/*===========================================================================
 * Macro define
 *===========================================================================*/ 

#define TIME_SEC(TotalTime)        (((TotalTime)/1000)%60) // Round it up if total time is over then 500
#define TIME_MIN(TotalTime)        (((TotalTime)/1000/60)%60)
#define TIME_HOUR(TotalTime)       ((TotalTime)/1000/(60*60))

/*===========================================================================
 * Structure define
 *===========================================================================*/

typedef struct _AHC_THUMB_CFG
{
    UINT16 uwTHMPerLine;
    UINT16 uwTHMPerColume;
    UINT16 uwHGap;
    UINT16 uwVGap;
    UINT32 byBkColor;       // Thumbnail Page Background Color
    UINT32 byFocusColor;    // Thumbnail Page Focus Color

    UINT32 u32DispStartX;   // Thumbnail Display Area Start X-Pos
    UINT32 u32DispStartY;   // Thumbnail Display Area Start Y-Pos
    UINT32 u32DispAreaW;    // Thumbnail Display Area Width
    UINT32 u32DispAreaH;    // Thumbnail Display Area Height
} AHC_THUMB_CFG;

/*===========================================================================
 * Function prototype
 *===========================================================================*/ 

/** @addtogroup AHC_BROWSER
@{
*/
AHC_BOOL AHC_Thumb_Config(AHC_THUMB_CFG *pConfig, AHC_BOOL bKeephumbIndex);
AHC_BOOL AHC_Thumb_GetConfig(AHC_THUMB_CFG *pConfig);
AHC_BOOL AHC_Thumb_IsFileProtect(UINT32 wDcfObjIdx);
AHC_BOOL AHC_Thumb_IsFileLocked(UINT32 wDcfObjIdx);
AHC_BOOL AHC_Thumb_ProtectKey(void);
AHC_BOOL AHC_Thumb_Rewind(UINT8 byNum);
AHC_BOOL AHC_Thumb_Forward(UINT8 byNum);
AHC_BOOL AHC_Thumb_GetFirstIdxCurPage(UINT16 *pwIndex);
AHC_BOOL AHC_Thumb_RewindPage(void);
AHC_BOOL AHC_Thumb_ForwardPage(void);
AHC_BOOL AHC_Thumb_GetCurIdx(UINT32 *puiIdx);
AHC_BOOL AHC_Thumb_GetCurPos(UINT32 *puiPos);
AHC_BOOL AHC_Thumb_GetCurPage(UINT16 *puwPage);
AHC_BOOL AHC_Thumb_GetTotalPages(UINT16 *puwPages);
AHC_BOOL AHC_Thumb_GetMaxNumPerPage(UINT32  *ObjNumPerPage);
AHC_BOOL AHC_Thumb_GetCountCurPage(UINT16 *ulObjCount);
AHC_BOOL AHC_Thumb_GetCurPosCurPage(UINT16 *ulObjIndex);
AHC_BOOL AHC_Thumb_DrawPage(AHC_BOOL bForce);
AHC_BOOL AHC_Thumb_SetCurrentIdx(UINT16 uiIndex);
AHC_BOOL AHC_Thumb_SetCurIdx(UINT32 uiIdx);

/// @}

#endif //_AHC_BROWSER_H_
