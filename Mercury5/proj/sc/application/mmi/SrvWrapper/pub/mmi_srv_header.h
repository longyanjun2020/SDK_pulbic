
////////////////////////////////////////////////////////////////////////////////
//
// Copyright (c) 2006-2009 MStar Semiconductor, Inc.
// All rights reserved.
//
// Unless otherwise stipulated in writing, any and all information contained
// herein regardless in any format shall remain the sole proprietary of
// MStar Semiconductor Inc. and be kept in strict confidence
// ("MStar Confidential Information") by the recipient.
// Any unauthorized act including without limitation unauthorized disclosure,
// copying, use, reproduction, sale, distribution, modification, disassembling,
// reverse engineering and compiling of the contents of MStar Confidential
// Information is unlawful and strictly prohibited. MStar hereby reserves the
// rights to any and all damages, losses, costs and expenses resulting therefrom.
//
////////////////////////////////////////////////////////////////////////////////

#ifndef        __MMI_SRV_HEADER_H__
#define        __MMI_SRV_HEADER_H__
#include		"mmi_srv_accessory.h"
#include		"mmi_srv_alarm.h"
#include		"mmi_srv_alivewdg.h"
#include		"mmi_srv_audio.h"
#include		"mmi_srv_audioenv.h"
#include		"mmi_srv_audioplayer.h"
#include		"mmi_srv_audiorecorder.h"
#include		"mmi_srv_battery.h"
#include		"mmi_srv_bt.h"
#include		"mmi_srv_btobex.h"
#include		"mmi_srv_calllog.h"
#include		"mmi_srv_camcoder.h"
#include		"mmi_srv_camera.h"
#include		"mmi_srv_cbs.h"
#include		"mmi_srv_cc.h"
#include		"mmi_srv_cfg.h"
#include		"mmi_srv_client.h"
#include		"mmi_srv_clipboard.h"
#include		"mmi_srv_clock.h"
#include		"mmi_srv_codec.h"
#include		"mmi_srv_config.h"
#include		"mmi_srv_core.h"
#include		"mmi_srv_cphs.h"
#include		"mmi_srv_encoding.h"
#include		"mmi_srv_eventdb.h"
#include		"mmi_srv_evtcenter.h"
#include		"mmi_srv_fdn.h"
#include		"mmi_srv_filemgr.h"
#include		"mmi_srv_fmradio.h"
#include		"mmi_srv_fstream.h"
#include		"mmi_srv_gps.h"
#include		"mmi_srv_imagemaker.h"
#include		"mmi_srv_java.h"
#include		"mmi_srv_mci.h"
#include		"mmi_srv_mms.h"
#include		"mmi_srv_mmstx.h"
#include		"mmi_srv_mobilitymgr.h"
#include		"mmi_srv_moi.h"
#ifdef __CALLER_LOCATION__
#include        "mmi_srv_cl.h"
#endif // __CALLER_LOCATION__

#include		"mmi_srv_motiondetector.h"
#include		"mmi_srv_msgmgr.h"
#include		"mmi_srv_emugame.h"
#include		"mmi_srv_objprocessing.h"
#include		"mmi_srv_pedometer.h"
#include		"mmi_srv_phb.h"
#include		"mmi_srv_playlist.h"
#include		"mmi_srv_previewline2.h"
#include		"mmi_srv_profile.h"
#include		"mmi_srv_sensormgr.h"
#include		"mmi_srv_shortcut.h"
#include		"mmi_srv_sim.h"
#include		"mmi_srv_sms.h"
#include		"mmi_srv_smstx.h"
#include		"mmi_srv_socket.h"
#include		"mmi_srv_ss.h"
#include		"mmi_srv_stk.h"
#include		"mmi_srv_taskdb.h"
#include		"mmi_srv_taskdbmgr.h"
#include		"mmi_srv_touch.h"
#include		"mmi_srv_touchshortcut.h"
#include		"mmi_srv_tv.h"
#include		"mmi_srv_usb.h"
#include		"mmi_srv_vcalparser.h"
#include		"mmi_srv_vcalstore.h"
#include		"mmi_srv_vendor.h"
#include		"mmi_srv_videoplayer.h"
#include		"mmi_srv_voicecall.h"
#ifdef __WLAN_MMI__
#include		"mmi_srv_wlan.h"
#endif
#ifdef __VT_3G324M__
#include		"mmi_srv_vtcc.h"
#endif
#include        "mmi_srv_countdowntimer.h"
#include "mmi_UrlSrvUtil.h"
#include "mmi_UrlSrvUtilUrl.h"
#include "mmi_UrlSrvClientHelper.h"

#ifdef __EMAIL_MMI__
#include "mmi_srv_email.h"
#endif

#ifdef __NCCQQ_MMI__
#include "mmi_srv_qq.h"
#endif

#include        "mmi_srv_privateprotect.h"

#endif /*__MMI_SRV_HEADER_H__*/
