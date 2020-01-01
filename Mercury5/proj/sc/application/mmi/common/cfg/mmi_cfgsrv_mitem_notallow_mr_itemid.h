/**
 * @file    mmi_cfgsrv_mitem_notallow_mr_itemid.h
 *
 * @brief   This file is auto generate by XRG tool. Do not modify file directly
 *
 * @version $Id:$
 *
 * @time
 */

#ifndef __MMI_CFGSRV_MITEM_NOTALLOW_MR_ITEMID_H__
#define __MMI_CFGSRV_MITEM_NOTALLOW_MR_ITEMID_H__

/**---------------------------------*
 *	Platform Style Area				*
 *----------------------------------*/
#include "mmi_cfgsrv_common_table.h"
#include "mmi_common_notallow_cfg.h"
#include "mmi_alarmapp_cfg.h"
#include "mmi_btsrv_cfg.h"
#include "mmi_fmradioapp_cfg.h"
#include "mmi_filemgrapp_cfg.h"
#include "mmi_mplayerapp_cfg.h"
#include "mmi_phbsrv_cfg.h"
#include "mmi_secapp_cfg.h"
#include "mmi_simsrv_cfg.h"
#include "mmi_antistealapp_cfg.h"
#include "mmi_remotecontrolapp_cfg.h"
#include "mmi_azanapp_cfg.h"
#include "mmi_videoplayerapp_cfg.h"

#ifdef __APP_MMI_FM_SCHEDULE__
#include "mmi_fmsch_cfg.h"
#else
// No config on FM schedule structure.
#define FMSCHAPP_NAMR_ALL_CONFIG
#endif

#ifdef __APP_MMI_SOHU_UPDATER__
#include "mmi_alarmapp_cfg.h"
#else
// No config on FM schedule structure.
#define CONFIG_NAMR_SOHU_UPDATE_LIST
#endif

#define NO_ALLOW_MITEM_TABLE \
                    COMMON_NOTALLOW_ALL_CONFIG \
					ALARMAPP_NAMR_ALL_CONFIG \
					FMRADIOAPP_NAMR_ALL_CONFIG \
                    FMSCHAPP_NAMR_ALL_CONFIG \
                    CONFIG_NAMR_SOHU_UPDATE_LIST \
					FILEMGRAPP_NAMR_ALL_CONFIG \
					MPLAYER_NAMR_ALL_CONFIG \
					PHBSRV_NAMR_ALL_CONFIG \
					ANTISTEALAPP_AMR_ALL_CONFIG \
					REMOTECONTROL_AMR_ALL_CONFIG\
					SECURITY_NAMR_ALL_CONFIG \
					SIMSRV_NAMR_ALL_CONFIG \
                    AZANAPP_NAMR_ALL_CONFIG \
                    VIDEOPLAYERSRV_NAMR_ALL_CONFIG
                    
#undef CONFIG_DEFINE
#define CONFIG_DEFINE(cfgId, type, aryNum, ...) cfgId,

enum
{
CFGIT_MULTIPLE_ITEMS_FILE_NOTALLOW_MASTER_RESET_START=MULTIPLE_ITEMS_FILE_NOTALLOW_MASTER_RESET_START,

NO_ALLOW_MITEM_TABLE

CFGIT_MULTIPLE_ITEMS_FILE_NOTALLOW_MASTER_RESET_END
};


#endif /* __MMI_CFGSRV_MITEM_NOTALLOW_MR_ITEMID_H__ */
