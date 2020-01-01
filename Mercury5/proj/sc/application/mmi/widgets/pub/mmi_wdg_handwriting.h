/**
 * @file    mmi_wdg_handwriting.h
 * @author  christoph.kuo@mstarsemi.com
 * 
 * @version $Id: mmi_wdg_handwriting.h 25372 2009-03-11 08:10:22Z mark.yang $
 *
 *
 * @brief   
 */
#ifndef __MMI_WDG_HANDWRITING_H__
#define __MMI_WDG_HANDWRITING_H__

#ifdef __TOUCH_SCREEN_MMI__
#ifdef __HANDWRITING_MMI__

#include "mmi_util_handwriting.h"
#include "mmi_wdg_common_interface.h"

//Do not change order and data type
//Mapping with mmi_cfgsrv_setting.h HW_Stroke_Duration_e
enum                  
{                     
	HW_STROKE_MIN_DURATION	= 400,
	HW_STROKE_MEDIUM_DURATION = 600,
	HW_STROKE_MAX_DURATION = 1000
};       
typedef u32 HW_Stroke_Duration_e;

enum 
{
	HW_FUNC_RECOGNITION,
	HW_FUNC_DRAW_STROKE_ONLY,
	HW_FUNC_END
};
typedef u32 HW_Function_e;

typedef struct{
	HW_Function_e eHWFunction;
	u32 pData;
}HW_ModelData_t;

/*=============================================================*/
// Interface functions
/*=============================================================*/
/** WdgHandWritingCreate
* @brief        Create HandWriting widget
*
*
* @retval       The pointer of HandWriting Success.
* @retval       NULL                Failed.
*
*/
IWidget* WdgHandWritingCreate
(
    void
);

/** WdgHandWritingSetRecogntionMode
* @brief        Set the recognition mode of handwriting
*
* @param[in]    pWDG          Pointer to the handwriting widget
* @param[in]    eMode			The recognition mode, ref. MAE_HW_Recog_Mode_e
*
* @retval       None
*
*/
__INLINE void WdgHandWritingSetRecogntionMode
(
    IWidget                 *pWDG,
    MAE_HW_Recog_Mode_e   eMode
)
{
    WdgCommonSetProperty(pWDG, PROP_HW_RECOGNITION_MODE, (u32)eMode);
}

/** WdgHandWritingSetLockScreen
* @brief        HW widget will lock screen if user enter strokes.
*
* @param[in]    pWDG          Pointer to the handwriting widget
* @param[in]    bLock			TRUE/FALSE
*
* @retval       None
*
*/
__INLINE void WdgHandWritingSetLockScreen
(
    IWidget                 *pWDG,
    boolean					bLock
)
{
    WdgCommonSetProperty(pWDG, PROP_HW_WDG_LOCKSCR, (u32)bLock);
}

/** WdgHandWritingResetStroke
* @brief        HW widget will reset enter strokes.
*
* @param[in]    pWDG          Pointer to the handwriting widget
*
* @retval       None
*
*/
__INLINE void WdgHandWritingResetStroke
(
    IWidget                 *pWDG
)
{
    WdgCommonSetProperty(pWDG, PROP_HW_WDG_RESET_STROKE, TRUE);
}

#endif
#endif
#endif /*__MMI_WDG_HANDWRITING_H__ */
