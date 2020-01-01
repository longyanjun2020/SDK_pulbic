#ifndef __MMI_IF_CDPROV_H__
#define __MMI_IF_CDPROV_H__
#if defined(__MMS_MMI_CDMMS__) && defined(__WAP_MMI_CDWAP__)
#include "mmi_mae_common_def.h"
#include "mmi_mae_shell.h"
#include "mmi_if_def.h"
#include "mmi_common_mms.h"
#include "ms_prov.h"


typedef struct {
    s32 status;
} MMI_PROV_GetSettingsCnf_t;

typedef struct
{
    s32             status;
    PROV_Settings_t *pSettingsList;
} MMI_PROV_VerifyOTAPWCnf_t;


void mmi_cdprov_msg_parser( IBase *pRecipient, vm_msg_t *pData );

void mmi_prov_verify_ota_pw_cnf( IBase *pRecipient, vm_msg_t *pData );
#endif
#endif //#ifndef __MMI_IF_CDPROV_H__
