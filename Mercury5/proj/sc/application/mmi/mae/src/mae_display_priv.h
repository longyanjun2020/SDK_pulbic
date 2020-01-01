/**
 *  @file mae_display_priv.h
 *
 *  @version $Id: mae_display_priv.h 291 2009-02-27 13:08:01Z kenny.wu $
 */

#ifndef __MAE_DISPLAY_PRIV_H__
#define __MAE_DISPLAY_PRIV_H__

#include "mmi_mae_common_def.h"
#include "mmi_mae_forward.h"
#include "mmi_mae_dib_forward.h"
#include "mmi_mae_graphic_forward.h"
#include "mmi_mae_display.h"

//#define _MAE_DISP_HOOK_UPDATE_



/*
 *  User update function prototype.
 *
 *  @param  pData            [in]Pointer to the user data which was set to display before
 *  @param  pDib             [in]Pointer to DIB to update
 *  @param  pDA              [in]Pointer to the dirty area of the DIB
 *
 */
typedef void (*PfnDisp_Update)(void *pData, pDIB pDib, Rect_t *pDA);

/**
 *  Display_New(MAE_ClsId, void**)
 *
 *  @brief  This function gets the display id of the given IDisplay
 *
 *  @param  nClsID            [in]Class ID of the object to create
 *  @param  ppObj            [in]Pointer to the memory to store the pointer of the new allocated object
 *
 *  @retval MAE_RET_SUCCESS          Successful
 *  @retval MAE_RET_OUT_OF_MEMORY    Out of memory
 */
MAE_Ret Display_New(MAE_ClsId nClsID, void **ppObj);

/**
 *  Display_GetDisplayId(IDisplay *pDisp, MAEDispId_t *pID)
 *
 *  @brief  This function gets the display id of the given IDisplay
 *
 *  @param  pDisp            [in]Pointer to the IDisplay Object
 *  @param  pID              [in]Pointer to the memory to store the ID
 *
 *  @retval MAE_RET_SUCCESS   Successful
 */
MAE_Ret Display_GetDisplayId(IDISPLAY *pDisp, MAEDispId_t *pID);

#ifdef _MAE_DISP_HOOK_UPDATE_
/**
 *  Display_SetUpdateFunc(MAEDispId_t nDispID, DISP_UPDATE_FUNC_PTR pUpdFunc, void *pData, boolean bSet)
 *
 *  @brief  This function sets update function to the display of the given display id
 *
 *  @param  nDispID            [in]ID of display to set
 *  @param  pUpdFunc          [in]Pointer to the update to set/reset
 *  @param  pData             [in]Pointer to user data
 *  @param  bSet              [in]Set or reset the update function
 *
 *  @retval MAE_RET_SUCCESS   Successful
 */

MAE_Ret Display_SetUpdateFunc(MAEDispId_t nDispID, DISP_UPDATE_FUNC_PTR pUpdFunc, void *pData, boolean bSet);
#endif /* _MAE_DISP_HOOK_UPDATE_ */

/** 
 *  Display_EnableUpdate(MAEDispId_t DispID)
 *
 *  @brief  This function enables display to update screen
 *   
 *  @param  DispID            [in]ID of display to set
 *
 *  @retval MAE_RET_SUCCESS     Successful
 *  @retval MAE_RET_BAD_PARAM   Error display ID
 */
MAE_Ret Display_EnableUpdate(MAEDispId_t DispID);

/** 
 *  Display_DisableUpdate(MAEDispId_t DispID)
 *
 *  @brief  This function disables display to update screen
 *   
 *  @param  DispID            [in]ID of display to set
 *
 *  @retval MAE_RET_SUCCESS     Successful
 *  @retval MAE_RET_BAD_PARAM   Error display ID
 */
MAE_Ret Display_DisableUpdate(MAEDispId_t DispID);

/** 
 *  Display_UpdateDevice(MAEDispId_t id, boolean bPartial)
 *
 *  @brief  This function forces display to update screen
 *   
 *  @param  DispID            [in]ID of display to set
 *  @param  bPartial          [in]If do partial update
 *
 */
void Display_UpdateDevice(MAEDispId_t DispID, boolean bPartial);

#endif /* __MAE_DISPLAY_PRIV_H__ */
