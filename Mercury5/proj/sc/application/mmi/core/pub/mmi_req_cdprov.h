#ifndef __MMI_REQ_CDPROV_H__
#define __MMI_REQ_CDPROV_H__
#if defined(__MMS_MMI_CDMMS__) && defined(__WAP_MMI_CDWAP__)
#include "ms_prov.h"


typedef struct
{
    s32 msgIdx;
    s32 mailBox;
    u8  isRead;
} MMI_PROV_SetReadFlagReq_t;

typedef struct
{
    s32 msgIdx;
    s32 mailBox;
    s8  otaPW[MMI_PROV_PINCODE_MAX_LEN];
} MMI_PROV_VerifyOTAPWReq_t;


s32 mmi_prov_set_read_flag_req( MMI_PROV_SetReadFlagReq_t *pProvSetReadFlagReq );
s32 mmi_prov_verify_ota_pw_req( MMI_PROV_VerifyOTAPWReq_t *pProvVerifyOTAPWReq );
#endif
#endif //#ifndef __MMI_REQ_CDPROV_H__
