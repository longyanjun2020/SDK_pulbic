/**
 * @file    mmi_cfgsrv_mitem_allow_mr_itemid.h
 *
 * @brief   This file is auto generate by XRG tool. Do not modify file directly
 *
 * @version $Id:$
 *
 * @time
 */

#ifndef __MMI_CFGSRV_MITEM_ALLOW_MR_ITEMID_H__
#define __MMI_CFGSRV_MITEM_ALLOW_MR_ITEMID_H__

/**---------------------------------*
 *	Platform Style Area				*
 *----------------------------------*/
#include "mmi_cfgsrv_common_table.h"
#include "mmi_common_storage_mgr_cfg.h"
#include "mmi_mainmenu_cfg.h"
#include "mmi_videoplayerapp_cfg.h"
#include "mmi_common_cfg.h"
#include "mmi_calendarapp_cfg.h"
#include "mmi_stopwatchapp_cfg.h"
#include "mmi_camapp_cfg.h"
#include "mmi_ebookapp_cfg.h"
#include "mmi_btsrv_cfg.h"
#include "mmi_emuapp_cfg.h"
#include "mmi_fmradioapp_cfg.h"
#include "mmi_idleapp_cfg.h"
#include "mmi_message_cfg.h"
#include "mmi_shortcutssrv_cfg.h"
#include "mmi_profilesrv_cfg.h"
#include "mmi_pedometersrv_cfg.h"
#include "mmi_sohuupdaterapp_cfg.h"
#include "mmi_kingmovieapp_cfg.h"
#include "mmi_sys_cfg.h"
#include "mmi_secapp_cfg.h"
#include "mmi_onoffapp_cfg.h"
#include "mmi_cdwapapp_cfg.h"
#include "mmi_mplayerapp_cfg.h"
#include "mmi_hamsterfightapp_cfg.h"

#ifndef __UI_STYLE_MMI_ANDROID_IDLE__
#define MITEM_TABLE \
                STORAGE_MGR_AMR_ALL_CONFIG \
                MAINMENUAPP_AMR_ALL_CONFIG \
                VIDEOPLAYERAPP_AMR_ALL_CONFIG \
                COMMON_AMR_ALL_CONFIG \
                CALENDAR_AMR_APP_CONFIG \
                STOPWATCH_AMR_APP_CONFIG \
                CAMAPP_AMR_ALL_CONFIG \
                EBOOKAPP_AMR_ALL_CONFIG \
                BTSRV_AMR_ALL_CONFIG \
                EMUAPP_AMR_ALL_CONFIG \
                FMRADIOAPP_AMR_ALL_CONFIG \
                IDLEAPP_AMR_ALL_CONFIG \
                MESSAGE_AMR_ALL_CONFIG \
                SHORTCUTSSRV_AMR_ALL_CONFIG \
                PROFILESRV_AMR_ALL_CONFIG \
                PEDOMETERSRV_AMR_ALL_CONFIG \
                SOHUUPDATERAPP_AMR_ALL_CONFIG\
                KINGMOVIEAPP_AMR_ALL_CONFIG\
                CDWAPAPP_AMR_ALL_CONFIG \
                MPLAYERAPP_AMR_ALL_CONFIG \
                ONOFFAPP_AMR_ALL_CONFIG \
		HAMSTERFIGHTAPP_AMR_ALL_CONFIG
#else

#define MITEM_TABLE \
                STORAGE_MGR_AMR_ALL_CONFIG \
                MAINMENUAPP_AMR_ALL_CONFIG \
                VIDEOPLAYERAPP_AMR_ALL_CONFIG \
                COMMON_AMR_ALL_CONFIG \
                CALENDAR_AMR_APP_CONFIG \
                STOPWATCH_AMR_APP_CONFIG \
                CAMAPP_AMR_ALL_CONFIG \
                EBOOKAPP_AMR_ALL_CONFIG \
                BTSRV_AMR_ALL_CONFIG \
                EMUAPP_AMR_ALL_CONFIG \
                FMRADIOAPP_AMR_ALL_CONFIG \
                MESSAGE_AMR_ALL_CONFIG \
                SHORTCUTSSRV_AMR_ALL_CONFIG \
                PROFILESRV_AMR_ALL_CONFIG \
                PEDOMETERSRV_AMR_ALL_CONFIG \
                SOHUUPDATERAPP_AMR_ALL_CONFIG\
                KINGMOVIEAPP_AMR_ALL_CONFIG\
                CDWAPAPP_AMR_ALL_CONFIG \
                MPLAYERAPP_AMR_ALL_CONFIG \
                ONOFFAPP_AMR_ALL_CONFIG\
                IDLEAPP_AMR_ALL_CONFIG \
		HAMSTERFIGHTAPP_AMR_ALL_CONFIG
#endif//__UI_STYLE_MMI_ANDROID_IDLE__

#undef CONFIG_DEFINE
#define CONFIG_DEFINE(cfgId, type, aryNum, ...) cfgId,


enum
{
CFGIT_MULTIPLE_ITEMS_FILE_ALLOW_MASTER_RESET_START=MULTIPLE_ITEMS_FILE_ALLOW_MASTER_RESET_START,

MITEM_TABLE

CFGIT_MULTIPLE_ITEMS_FILE_ALLOW_MASTER_RESET_END
};

#endif /* __MMI_CFGSRV_MITEM_ALLOW_MR_ITEMID_H__ */



