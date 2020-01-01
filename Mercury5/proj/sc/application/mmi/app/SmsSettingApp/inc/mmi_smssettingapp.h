/**
* @file mmi_smssettingapp.h
** 
*
* @version $Id$
*/
#ifndef __MMI_SMSSETTINGAPP_H__

#define __MMI_SMSSETTINGAPP_H__

#include "mmi_mae_common_def.h"
#include "mmi_mae_applet.h"
#include "mmi_mae_class.h"

#define MSASmsSCMaxByte MSG_SMS_SERVICE_CENTER_MAX_CHAR*sizeof(MAE_WChar)



#define MSA_EVT_APP_Close				(CLSID_MSA << 16 | 11)

MAE_Ret MsaNew(MAE_ClsId id, void **ppObj);
void MsaPreNew(void);


enum
{
    MSA_E_START_SETTINGMENU = 0,
    MSA_E_START_SENDOPTIONS,
    MSA_E_START_TYPE_TOTAL
};
typedef u8 MsaStartType_e;

typedef struct
{    
    u8 SelectSIM;  
} MsaStart_t;

void MSA_StartAPFree(IBase *pIssuer, u32 Param);

#endif /* __MMI_SMSSETTINGAPP_H__ */
