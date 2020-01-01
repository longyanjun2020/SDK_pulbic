/**
* @file mmi_mmssettingapp.h
* 
*
* @version $Id$
*/
#ifndef __MMI_MMSSETTINGAPP_H__
#define __MMI_MMSSETTINGAPP_H__



#include "mmi_mae_common_def.h"
#include "mmi_mae_applet.h"

#ifdef __MMS_MMI_CDMMS__

#define MMSA_DURATIONSIZE_BYTE  6
//#define MMSA_EDITOR_HEIGHT                  (MAIN_LCD_ONELINE_HEIGHT*7)

/**
 * Functions
 */


MAE_Ret MMSA_New(MAE_ClsId id, void **ppObj);

enum{
    MMSA_E_START_SETTINGMENU = 0,
    MMSA_E_START_PAGESETTING,
    MMSA_E_START_SENDOPTIONS,
    MMSA_E_START_TYPE_TOTAL
};
typedef u8 MmsaStartType_e;

enum 
{
    MMSA_E_SIM_MASTER,
    MMSA_E_SIM_SLAVE,
    MMSA_E_SIM_UNKNOW
};
typedef u8 MmsaSelectSim_e;

typedef struct
{
    MmsaStartType_e StartType;
    MmsaSelectSim_e SelectSIM;
    u32 nDuration;   
} MmsaStart_t;

void MMSA_StartAPFree(IBase *pIssuer, u32 Param);


#endif // __MMS_MMI_CDMMS__
#endif /* __MMI_MMSSETTINGAPP_H__ */
