/**
 * @file mae_inputcontroller_guobi_priv.h
 * @brief This file defines the data structure of InputWidget
 *
 * @version $Id: mae_inputcontroller_guobi_priv.h 12030 2008-06-26 06:22:26Z alison.chen $
 */
#ifndef __MAE_INPUTCONTROLLER_SG_PRIV_H__
#define __MAE_INPUTCONTROLLER_SG_PRIV_H__

#ifdef __IME_MMI_SG__
/*=============================================================*/
// include
/*=============================================================*/
#include "mmi_mae_controller.h"
#include "mmi_mae_inputcontroller.h"
#include "mmi_mae_common_def.h"
#include "mae_widgetbase.h"
#include "mmi_mae_langcode.h"
#include "mmi_common_cfg.h"
//#include "myapi.h"
#include "mae_ime.h"
#include "WD_Def.h"
/*=============================================================*/
// include
/*=============================================================*/
#include "mmi_mae_controller.h"
#include "mmi_mae_inputcontroller.h"
#include "mmi_mae_common_def.h"
#include "mae_widgetbase.h"
#include "mmi_mae_langcode.h"
#include "mmi_common_cfg.h"
#include "mae_ime.h"

/*=============================================================*/
// type and define
/*=============================================================*/
#define MY_BASE_ZHUYIN		128
#define MY_ZHUYIN_NUM		37
#define SG_MAX_ASSOCIATE_BUF    64
#define SG_MAX_ASSOCIATE_NUM    24
#define SG_MAX_ASSOCIATE_PAGE   20          

typedef struct{
    MAE_LANG_CODE_e lang;
    int  imeLang;
}SgLdbData_t;

typedef struct
{
    int nStarPos;
    int nPageSize;
    int nSelect;
}SgPage_t;

typedef struct
{
    int nCurPage;
    int nTotalPage;
    SgPage_t SgPage[SG_MAX_ASSOCIATE_PAGE];
    WD_UINT16 selecting[SG_MAX_ASSOCIATE_BUF];
}SgAsssociateCandidate_t;

typedef struct{
	Chinese_LayoutSetting_t sLayoutSetting;
	WD_imeResult	imeResult;
    MAE_LANG_CODE_e  curLang;
	int  nLastdisplay;
    int  nIsHandwriting;
    SgAsssociateCandidate_t SgAsssociateCandidate;
} MYData_t;


/*=============================================================*/
// functions
/*=============================================================*/


#endif //__IME_MMI_MY__

#endif //__MAE_INPUTCONTROLLER_MY_PRIV_H__
/*=============================================================*/
// end of file
