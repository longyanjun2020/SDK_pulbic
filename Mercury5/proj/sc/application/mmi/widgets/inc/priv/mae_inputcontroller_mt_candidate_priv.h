/**
 * @file mae_inputcontroller_mtcandidate_priv.h
 * @brief This file defines the data structure of InputWidget
 *
 * @version $Id: mae_inputcontroller_mt_candidate_priv.h 16998 2008-11-23 16:00:13Z alison.chen $
 */
#ifndef __MAE_INPUTCONTROLLER_MT_CANDIDATE_PRIV_H__
#define __MAE_INPUTCONTROLLER_MT_CANDIDATE_PRIV_H__

/*=============================================================*/
// include
/*=============================================================*/
#include "mmi_mae_inputcontroller.h"
#include "mmi_mae_controller.h"
#include "mmi_mae_common_def.h"
#include "mmi_mae_langcode.h"
/*=============================================================*/
// type and define
/*=============================================================*/

#ifdef __QWERTY_KEYPAD_INPUTMETHOD__
#define MT_KEY_NUM	(29)    
#else
#define MT_KEY_NUM	(12)
#endif    /*__QWERTY_KEYPAD_INPUTMETHOD__*/
typedef struct {
	const MAE_WChar * keyMappingCandidateAry_U[MT_KEY_NUM];
	const MAE_WChar * keyMappingCandidateAry_L[MT_KEY_NUM];
	const MAE_WChar * keyMappingPhoneBook[MT_KEY_NUM];
	u32 nLanguageCode;
} MTData_t;


/*=============================================================*/
// functions
/*=============================================================*/




#endif //__MAE_INPUTCONTROLLER_MT_CANDIDATE_PRIV_H__
/*=============================================================*/
// end of file

