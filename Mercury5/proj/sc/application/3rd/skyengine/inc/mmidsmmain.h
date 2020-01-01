#ifdef __MMI_DSM__
#ifndef __SDK_SIMULATION__
#include "mmi_log.h"
#endif

#define DSM_MEM_SIZE  (1024*650)
//#define DSM_FACTORY_ID  "mstar"
#define DSM_FACTORY_ID  "ykqcom"
#define DSM_HANDSET_ID  "ms240"


#define DSM_ROOT_DRV    "/CARD"
#define MMI_SYSTEM_DRV  "/CARD"
#define MMI_CARD_DRV    "/CARD"
#define DSM_DRV_A		"/NOR0"


#define DSM_ROOT_PATH   ".system/mythroad"


typedef enum
{
	DSM_STOP,
	DSM_RUN,
	DSM_PAUSE,
	DSM_BACK_RUN,
}T_DSM_STATE;

enum{
    AP_CC,
    AP_SMS,
    AP_SMSEX,
    AP_FILE_BROWSER,
    AP_PHB_BROWSER,
    AP_PLAY_VIDEO,
    AP_EDIT_EX,
    AP_PHB_ADD_CONTACT,
    AP_MSG_EDITOR,
    AP_WAP_OPEN_BROWSER,
};

typedef struct{
    u8 APType;
    u32 Data1;
    u32 Data2;
}ven_ap_cb_data_t;

#include "ven_file.h"
#include "ven_msg.h"
#include "ven_cc.h"
#include "ven_phb.h"
#include "ven_editor.h"
#include "ven_wap.h"
#endif

