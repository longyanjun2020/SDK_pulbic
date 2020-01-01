/**
* @file    mmi_util_handwriting.h
* @brief   This file
*
* @version $Id: mmi_util_handwriting.h 25372 2009-03-11 08:10:22Z mark.yang $
*/

#ifndef __MMI_UTIL_HANDWRITING_H__
#define __MMI_UTIL_HANDWRITING_H__

#ifdef __HANDWRITING_MMI__
#ifdef __TOUCH_SCREEN_MMI__

#include "mmi_mae_common_def.h"

#define MAE_HW_STROKE_MAX_DURATION          1000 // default value for maximum duration between 2 strokes in a given drawing
#define MAE_HW_STROKE_AUTO_VALIDATION_TIMER 2000 // default timer for automatic validation

//#define MAE_HW_MAX_CHINESE_CAND                9
//#define MAE_HW_MAX_LATIN_CAND                  9
#define MAE_HW_MAX_CAND                        9

typedef struct
{
  u16 nX;
  u16 nY;
} MAE_Stroke_point_t;

typedef struct
{
  u16                    nStrokeCnt;    ///< Number of strokes
  u16                   *pPointCnt;     ///< Array of number of Points for all strokes
  MAE_Stroke_point_t    *pPoints;       ///< Array of all points
} MAE_Stroke_t;

typedef enum /* Hand writing recognition mode */
{
   MAE_HW_RECOG_MODE_NONE,
   MAE_HW_RECOG_MODE_CHINESE, //Both big5 and GB
   MAE_HW_RECOG_MODE_NUMBER,  //0~9
   MAE_HW_RECOG_MODE_ALPHA_CAPITAL, //ABC
   MAE_HW_RECOG_MODE_ALPHA_LOWERCASE,  //abc
   MAE_HW_RECOG_MODE_PUNCTUATION,  //punctuations
   MAE_HW_RECOG_MODE_SYMBOLS, //ABC + abc
   MAE_HW_RECOG_MODE_GESTURE, // Gestures
   MAE_HW_RECOG_MODE_ALPHA_CAPITAL_NUMBER, // ABC + 0~9
   MAE_HW_RECOG_MODE_ALPHA_LOWERCASE_NUMBER, //abc + 0~9
   MAE_HW_RECOG_MODE_SYMBOL_NUMBER, // ABC + abc + 0~9
   MAE_HW_RECOG_MODE_CHINESE_GB, //Chinese GB Only
   MAE_HW_RECOG_MODE_CHINESE_BIG5,  //Chinese Big5 Only
   MAE_HW_RECOG_MODE_END 
} MAE_HW_Recog_Mode_e;

MAE_Ret MAE_HW_Init(void);
void MAE_HW_Exit(void);
void MAE_HW_SetMode(MAE_HW_Recog_Mode_e nMode);
void MAE_HW_SetMaxCandidates(u8 nMaxCand);
s32 MAE_HW_StartRecognition(MAE_Stroke_t* pStrokeList, MAE_WChar *pOutputCandBuffer);

#endif //__TOUCH_SCREEN_MMI__
#endif
#endif
