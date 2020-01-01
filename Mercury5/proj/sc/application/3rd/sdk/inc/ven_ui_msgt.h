/**
 * @file ven_ui_msgt.h
 *
 * @brief  This file defines the UI related message structure
 *
 * @author  steve.lee
 *
 * @version $Id: ven_ui_msgt.h 38996 2009-09-01 02:03:20Z code.lin $
 *
 */

#ifndef __VEN_UI_MSGT_H__
#define __VEN_UI_MSGT_H__

#include "ven_ui.h"
#include "ven_comdef_priv.h"

enum
{
    IVEN_UI_SHOW_MENU,
    IVEN_UI_SHOW_DIALOG,
    IVEN_UI_SHOW_TEXTVIEWER,
    IVEN_UI_SHOW_SOFTKEY,

    IVEN_UI_SHOW_SUM,
};
typedef u8 iVen_ui_show_type_t;

typedef struct
{
    iVen_AsyncReq_BodyBase_t ReqBase;
    iVen_ui_show_type_t contentType;
    u32 transID;
    void *pContent;                               ///< Pointer to content of menu/dialog/textviewer
    void *ptRet;                                  ///< Sync only, for user rsp data
    ven_ui_ret_t *pRetCode;                       ///< Sync only, command return code
} iVen_ui_show_comp_req_t;


typedef struct
{
    iVen_AsyncRsp_BodyBase_t RspBase;
    ven_ui_ret_t RetCode;                         ///< Return code for async mode
} iVen_ui_get_applet_status_rsp_t;


typedef struct
{
    iVen_AsyncReq_BodyBase_t ReqBase;
    iVen_ui_applet_id appletID;                   ///< Applet ID to query the status
    iVen_ui_applet_status_t *pAppletStatus;       ///< Pointer to content of menu/dialog/textviewer
    ven_ui_ret_t *pSyncRetCode;                   ///< Return code for sync mode
} iVen_ui_get_applet_status_req_t;

typedef iVen_ui_show_comp_req_t iVen_ui_update_comp_req_t;

typedef struct
{
    iVen_AsyncReq_BodyBase_t ReqBase;
    iVen_ui_show_type_t contentType;
    u32 transID;
    u32 *pSyncRetCode;
} iVen_ui_close_comp_req_t;

typedef struct
{
    iVen_AsyncRsp_BodyBase_t RspBase;
    iVen_ui_show_type_t contentType;
    void *pContent;                        ///< Pointer to content of menu/dialog/textviewer
    u32 transID;
    u32 index;                             ///< user selected index, valid when retCode is success
    ven_ui_ret_t retCode;                  ///< operation return code
    ven_ui_usr_rsp_t usrRspCode;           ///< user return code, valid when retCode is success
} iVen_ui_show_comp_rsp_t;

typedef struct
{
    iVen_AsyncReq_BodyBase_t ReqBase;
    ven_ui_interrupt_level_t intLevel;
} iVen_ui_set_interrupt_level_req_t;

typedef struct
{
    iVen_AsyncRsp_BodyBase_t RspBase;
    ven_ui_ret_t retCode;   ///< operation return code
} iVen_ui_set_interrupt_level_rsp_t;

typedef struct
{
    iVen_AsyncReq_BodyBase_t ReqBase;
    u32 nIconIndex;
    u32 nDataSize;
    u8* pRawData;
} iVen_ui_statusbar_draw_icon_req_t;

typedef struct
{
    iVen_AsyncReq_BodyBase_t ReqBase;
    u32 nIconIndex;
    u8 nStatusbarImage;
} iVen_ui_statusbar_draw_image_req_t;

typedef struct
{
    iVen_AsyncReq_BodyBase_t ReqBase;
    ven_ui_backlight_behavior_t blkBehavior;
    ven_ui_ret_t *pRetCode;    ///< Sync only, command return code
} iVen_ui_set_backlight_behavior_req_t;

typedef struct
{
    iVen_AsyncReq_BodyBase_t ReqBase;
    ven_ui_backlight_level_t blkLevel;
    ven_ui_backlight_duration_t blkDuration;
    ven_ui_ret_t *pRetCode;    ///< Sync only, command return code
} iVen_ui_set_backlight_req_t;

typedef struct
{
    iVen_AsyncRsp_BodyBase_t RspBase;
    ven_ui_ret_t retCode;                       ///< operation return code
} iVen_ui_set_backlight_behavior_rsp_t;

typedef struct
{
    iVen_AsyncReq_BodyBase_t ReqBase;
	bool bEnableLaunch;
    ven_ui_ret_t *pRetCode;    ///< Sync only, command return code
} iVen_ui_enable_launch_keyguard_req_t;

typedef struct
{
    iVen_AsyncRsp_BodyBase_t RspBase;
    ven_ui_ret_t retCode;   ///< operation return code
} iVen_ui_enable_launch_keyguard_rsp_t;

typedef struct
{
    iVen_AsyncRsp_BodyBase_t RspBase;
    bool bBacklightOn;                          ///< backlight on/off
} iVen_ui_backlight_ind_t;

typedef struct
{
    iVen_AsyncReq_BodyBase_t ReqBase;
    ven_ui_backlight_info *pbklInfo;//output: only useful if the ReqBase.bSync is TRUE
    ven_ui_ret_t *pRetCode; //output: only useful if the ReqBase.bSync is TRUE
} iVen_ui_get_backlight_info_req_t;

typedef struct
{
    iVen_AsyncRsp_BodyBase_t RspBase;
    ven_ui_backlight_info bklInfo;
    ven_ui_ret_t RetCode;
} iVen_ui_get_backlight_info_rsp_t;

#endif /* __VEN_UI_MSGT_H__ */

