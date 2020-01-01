#ifndef __MS_PROV_H__
#define __MS_PROV_H__
#if defined(__MMS_MMI_CDMMS__) && defined(__WAP_MMI_CDWAP__) && defined(__WAP_MMI_OTA_PROV__)
#include "vm_types.ht"
#include "sys_vm_dbg.ho"
#include "vm_stdio.ho"
#include "cus_os.hc"
#include "ms_defs.h"
#include "vm_msgof.hc"

#include "ncc_types.h"
#include "nccprov.h"
#include "prov.h"
#include "nccmms_par.h"
#include "nccmms_fs.h"


#define MMI_PROV_PINCODE_MAX_LEN    80

#define MMI_IMSI_MAX_LEN	        9

#define PROV_SECTYPE_NOT_USED       -1
#define PROV_SECTYPE_NETWPIN        0
#define PROV_SECTYPE_USERPIN        1
#define PROV_SECTYPE_USERNETWPIN    2
#define PROV_SECTYPE_USERPINMAC     3

#define PROV_STATUS_SUCCESS          0
#define PROV_STATUS_FAIL            -1
#define PROV_STATUS_WRONG_PASSWORD  -2
#define PROV_STATUS_NO_BUFFER       -3
#define PROV_STATUS_UNSUPPORTED_FORMAT     -4


typedef struct PROV_NAP_t
{
    s8 name[PROV_LENGTH_NAME + 1];
    s8 apn[PROV_LENGTH_NAP_ADDRESS];
    s8 username[PROV_LENGTH_AUTHNAME + 1];
    s8 password[PROV_LENGTH_AUTHSECRET + 1];
    s8 dns[PROV_LENGTH_DNS_ADDR + 1];
    s8 authType;
} PROV_NAP_t;

typedef enum
{
    PROV_SETTINGS_TYPE_MMS,
    PROV_SETTINGS_TYPE_WAP,
    PROV_SETTINGS_TYPE_EMAIL,
    PROV_SETTINGS_TYPE_UNKNOWN
} PROV_SETTINGS_TYPE;

typedef struct _PROV_Settings_t
{
    s32 type; // PROV_SETTINGS_TYPE

    PROV_NAP_t *pApn;
    s8 profileName[PROV_LENGTH_NAME + 1];
    s8 homepage[PROV_LENGTH_ADDR + 1]; // for MMS, it is mmsc; for WAP it is startpage
    s8 proxyIP[PROV_LENGTH_ADDR + 1];
    s32 proxyPort;

    struct _PROV_Settings_t *next;
} PROV_Settings_t;


typedef struct
{
    s32 msgIdx;
    s32 mailBox;
    u8  isRead;
} PROV_SetReadFlagReq_t;

typedef struct
{
    s32 msgIdx;
    s32 mailBox;
    s8  otaPW[MMI_PROV_PINCODE_MAX_LEN];
} PROV_VerifyOTAPWReq_t;

typedef struct
{
    s32             status;
    PROV_Settings_t *pSettingsList;
} PROV_VerifyOTAPWCnf_t;


void PROV_CallBack( void *pMessage );
char *PROV_GetProfileName( MMS_FS_MAILBOX mailBox, s32 msgIdx );
#endif
#endif
