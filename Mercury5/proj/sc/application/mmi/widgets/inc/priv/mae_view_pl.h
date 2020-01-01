/**
 * @file    mae_view_pl.h
 * 
 * @version $Id: mae_view_pl.h 36985 2009-08-02 11:46:27Z steve.lee $
 */
#ifndef __MAE_VIEWPL_H__
#define __MAE_VIEWPL_H__

#include "mmi_mae_transition.h"
#include "mmi_mae_view.h"
#include "mmi_mae_model.h"
#include "mmi_mae_widget.h"
#include "mmi_mae_softkeymodel.h"

// widget property to set IME Assist Model
extern const u32 nWdgProp_InputAssistModel;

// widget property to set softkey data
extern const u32 nWdgProp_SkData;

// default status bar visibility
extern const ViewSBVisType_t nDefaultSBVisType;

// default status bar background transparent
extern const u8 bDefaultSBTransp;

// Get transition data by transition ID
//ViewTransition_t* ViewPl_GetViewTransitionDataByID(u32 id);

// Get softkey data structure size
__SLDPM_FREE__ u32 ViewPl_GetSKDataSize(void);

// Set softkey data to the given softkey wodget
void ViewPl_SetSkDataToSkWdg(IWidget *pSkWdg, void *pSkData);

// Get one softkey ID by the given type and softkey data structure
MAE_Ret ViewPl_GetSkData(void *pSkData, u16 skType, u32 *pId);

// Set initial IDs to  softkey data and softkey model
__SLDPM_FREE__ void ViewPl_ResetSkData(void *pSkData, ISoftkeyModel *pSkMdl);

// Update new softkey type's ID to the given softkey data structure and set to the given softkey widget
void ViewPl_UpdateSkData(void *pSkData, IWidget *pSkWdg, u16 skType, u32 id);

// Update all softkey IDs to the given softkey data structure and softkey widget from the given model event
void ViewPl_UpdateSkByMdlChange(void *pSkData, IWidget *pSkWdg, ModelEvent_t *pEvent);

// update softkey data to softkey model
void ViewPl_UpdateSkModel(ISoftkeyModel *pSkMdl, u16 skType, u32 id);

// duplicate transition data
//void ViewPl_DuplicateTransitionData(ViewTransition_t **pDst, const ViewTransition_t*pSrc);

#endif /* __MAE_VIEWTRANSITION_H__ */

