/**
 *
 * @file    ven_setting_stmsg.h
 * @brief   This file defines the structures for the setting module message
 * @author  Jorena.Ku
 * @version $Id: ven_setting_stmsg.h 36962 2009-07-31 13:59:22Z code.lin $
 *
 */

#ifndef __VEN_SETTING_STMSG_H__
#define __VEN_SETTING_STMSG_H__

#include "ven_setting.h"
#include "ven_comdef_priv.h"
#include "ven_socket.h"



enum
{
    VEN_SETTING_FILE_ATTR_URL = 0,
    VEN_SETTING_FILE_ATTR_DISPLAY_NAME,
};
typedef u8 iVen_setting_file_attr_t;

typedef struct
{
    iVen_AsyncReq_BodyBase_t ReqBase;
    ven_socket_t *VenSock;
} iVenReqHeader_t;

/****************************************************************************/
/*  Message :       I_VEN_SETTING_GET_FILE_STR_REQ                          */
/*--------------------------------------------------------------------------*/
/*                                                                          */
/*  From/to   : Vendor task to MMI                                          */
/*                                                                          */
/*  Scope     : Get the wallpaper or active ring tone URL or display name   */
/*                                                                          */
/*  Structure : iVen_setting_getFileStr_req_t                               */
/*                                                                          */
/*--------------------------------------------------------------------------*/
/*  Field             |    Type   |  Description                            */
/*--------------------+-----------+-----------------------------------------*/
/*                    |           |                                         */
/****************************************************************************/
typedef struct
{
    iVen_AsyncReq_BodyBase_t ReqBase;
    ven_setting_file_type_t Type;
    iVen_setting_file_attr_t Attr;
    ven_setting_ret_t *pRetCode;    //output: only useful if the ReqBase.bSync is TRUE
    u16 **ppFileStr; //output: only useful if the ReqBase.bSync is TRUE
    u16 *pStrLen;   //output: only useful if the ReqBase.bSync is TRUE
} iVen_setting_getFileStr_req_t;


/****************************************************************************/
/*  Message :       I_VEN_SETTING_GET_FILE_STR_RSP                          */
/*--------------------------------------------------------------------------*/
/*                                                                          */
/*  From/to   : MMI to Vendor task                                          */
/*                                                                          */
/*  Scope     :                                                             */
/*                                                                          */
/*  Structure : iVen_setting_getFileStr_rsp_t                               */
/*                                                                          */
/*--------------------------------------------------------------------------*/
/*  Field             |    Type   |  Description                            */
/*--------------------+-----------+-----------------------------------------*/
/*                    |           |                                         */
/****************************************************************************/
typedef struct
{
    iVen_AsyncRsp_BodyBase_t RspBase;
    ven_setting_ret_t RetCode;
    u16 FileStr[VEN_SETTING_MAX_URL_LEN+1];      //UCS2 format with null terminator
    u16 nStrLen;
    ven_setting_file_type_t Type;
    iVen_setting_file_attr_t Attr;
} iVen_setting_getFileStr_rsp_t;

/****************************************************************************/
/*  Message :       I_VEN_SETTING_SET_URL_REQ                               */
/*--------------------------------------------------------------------------*/
/*                                                                          */
/*  From/to   : Vendor task to MMI                                          */
/*                                                                          */
/*  Scope     :                                                             */
/*                                                                          */
/*  Structure : iVen_setting_setFileURL_req_t                               */
/*                                                                          */
/*--------------------------------------------------------------------------*/
/*  Field             |    Type   |  Description                            */
/*--------------------+-----------+-----------------------------------------*/
/*                    |           |                                         */
/****************************************************************************/
typedef struct
{
    iVen_AsyncReq_BodyBase_t ReqBase;
    u16 URL[VEN_SETTING_MAX_URL_LEN+1];      //UCS2 format with null terminator
    ven_setting_file_type_t Type;

    ven_setting_ret_t *pRetCode;    //output: only useful if the ReqBase.bSync is TRUE
} iVen_setting_setFileURL_req_t;


/****************************************************************************/
/*  Message :       I_VEN_SETTING_SET_URL_RSP                               */
/*--------------------------------------------------------------------------*/
/*                                                                          */
/*  From/to   : MMI to Vendor task                                          */
/*                                                                          */
/*  Scope     :                                                             */
/*                                                                          */
/*  Structure : iVen_setting_setFileURL_rsp_t                               */
/*                                                                          */
/*--------------------------------------------------------------------------*/
/*  Field             |    Type   |  Description                            */
/*--------------------+-----------+-----------------------------------------*/
/*                    |           |                                         */
/****************************************************************************/
typedef struct
{
    iVen_AsyncRsp_BodyBase_t RspBase;
    ven_setting_ret_t RetCode;
    ven_setting_file_type_t Type;
} iVen_setting_setFileURL_rsp_t;


/****************************************************************************/
/*  Message :       I_VEN_SETTING_GET_VOLUME_REQ                            */
/*--------------------------------------------------------------------------*/
/*                                                                          */
/*  From/to   : Vendor task to MMI                                          */
/*                                                                          */
/*  Scope     :                                                             */
/*                                                                          */
/*  Structure : iVen_setting_getVolume_req_t                                */
/*                                                                          */
/*--------------------------------------------------------------------------*/
/*  Field             |    Type   |  Description                            */
/*--------------------+-----------+-----------------------------------------*/
/*                    |           |                                         */
/****************************************************************************/
typedef struct
{
    iVen_AsyncReq_BodyBase_t ReqBase;
    ven_setting_profile_volume_type_t Type;

    ven_setting_ret_t *pRetCode; //output: only useful if the ReqBase.bSync is TRUE
    u8 *pVolume;    //output: only useful if the ReqBase.bSync is TRUE
} iVen_setting_getVolume_req_t;


/****************************************************************************/
/*  Message :       I_VEN_SETTING_GET_VOLUME_RSP                            */
/*--------------------------------------------------------------------------*/
/*                                                                          */
/*  From/to   : MMI to Vendor task                                          */
/*                                                                          */
/*  Scope     :                                                             */
/*                                                                          */
/*  Structure : iVen_setting_getVolume_rsp_t                                */
/*                                                                          */
/*--------------------------------------------------------------------------*/
/*  Field             |    Type   |  Description                            */
/*--------------------+-----------+-----------------------------------------*/
/*                    |           |                                         */
/****************************************************************************/
typedef struct
{
    iVen_AsyncRsp_BodyBase_t RspBase;
    ven_setting_ret_t RetCode;
    u8 nVolume;
    ven_setting_profile_volume_type_t Type;
} iVen_setting_getVolume_rsp_t;


/****************************************************************************/
/*  Message :       I_VEN_SETTING_GET_KEYPAD_TONE_REQ                       */
/*--------------------------------------------------------------------------*/
/*                                                                          */
/*  From/to   : Vendor task to MMI                                          */
/*                                                                          */
/*  Scope     :                                                             */
/*                                                                          */
/*  Structure : iVen_setting_getKeypadTone_req_t                            */
/*                                                                          */
/*--------------------------------------------------------------------------*/
/*  Field             |    Type   |  Description                            */
/*--------------------+-----------+-----------------------------------------*/
/*                    |           |                                         */
/****************************************************************************/
typedef struct
{
    iVen_AsyncReq_BodyBase_t ReqBase;

    ven_setting_ret_t *pRetCode; //output: only useful if the ReqBase.bSync is TRUE
    ven_setting_profile_keypad_tone_value_t *pValue;    //output: only useful if the ReqBase.bSync is TRUE
} iVen_setting_getKeypadTone_req_t;

/****************************************************************************/
/*  Message :       I_VEN_SETTING_GET_VOLUME_RSP                            */
/*--------------------------------------------------------------------------*/
/*                                                                          */
/*  From/to   : MMI to Vendor task                                          */
/*                                                                          */
/*  Scope     :                                                             */
/*                                                                          */
/*  Structure : iVen_setting_getVolume_rsp_t                                */
/*                                                                          */
/*--------------------------------------------------------------------------*/
/*  Field             |    Type   |  Description                            */
/*--------------------+-----------+-----------------------------------------*/
/*                    |           |                                         */
/****************************************************************************/
typedef struct
{
    iVen_AsyncRsp_BodyBase_t RspBase;
    ven_setting_ret_t RetCode;
    u8 nValue;
} iVen_setting_getKeypadTone_rsp_t;


/****************************************************************************/
/*  Message :       I_VEN_SETTING_GET_VIBRATION_REQ                         */
/*--------------------------------------------------------------------------*/
/*                                                                          */
/*  From/to   : Vendor task to MMI                                          */
/*                                                                          */
/*  Scope     :                                                             */
/*                                                                          */
/*  Structure : iVen_setting_getVibrate_req_t                               */
/*                                                                          */
/*--------------------------------------------------------------------------*/
/*  Field             |    Type   |  Description                            */
/*--------------------+-----------+-----------------------------------------*/
/*                    |           |                                         */
/****************************************************************************/
typedef struct
{
    iVen_AsyncReq_BodyBase_t ReqBase;
    ven_setting_profile_vibration_type_t Type;

    ven_setting_ret_t *pRetCode; //output: only useful if the ReqBase.bSync is TRUE
    ven_setting_profile_vibration_value_t *pValue;    //output: only useful if the ReqBase.bSync is TRUE
} iVen_setting_getVibrate_req_t;


/****************************************************************************/
/*  Message :       I_VEN_SETTING_GET_VIBRATION_RSP                         */
/*--------------------------------------------------------------------------*/
/*                                                                          */
/*  From/to   : MMI to Vendor task                                          */
/*                                                                          */
/*  Scope     :                                                             */
/*                                                                          */
/*  Structure : iVen_setting_getVibrate_rsp_t                               */
/*                                                                          */
/*--------------------------------------------------------------------------*/
/*  Field             |    Type   |  Description                            */
/*--------------------+-----------+-----------------------------------------*/
/*                    |           |                                         */
/****************************************************************************/
typedef struct
{
    iVen_AsyncRsp_BodyBase_t RspBase;
    ven_setting_ret_t RetCode;
    ven_setting_profile_vibration_value_t nValue;
    ven_setting_profile_vibration_type_t Type;
} iVen_setting_getVibrate_rsp_t;



/****************************************************************************/
/*  Message :       I_VEN_SETTING_GET_NETWORK_PROFILE_REQ                   */
/*--------------------------------------------------------------------------*/
/*                                                                          */
/*  From/to   : Vendor task to MMI                                          */
/*                                                                          */
/*  Scope     :                                                             */
/*                                                                          */
/*  Structure :iVen_setting_getNetworkProfile_req_t                         */
/*                                                                          */
/*--------------------------------------------------------------------------*/
/*  Field             |    Type   |  Description                            */
/*--------------------+-----------+-----------------------------------------*/
/*                    |           |                                         */
/****************************************************************************/
typedef struct
{
    iVen_AsyncReq_BodyBase_t ReqBase;
    ven_setting_network_profile_type_t Type;
    ven_common_sim_id_t SimID;
    ven_setting_ret_t *pRetCode; //output: only useful if the ReqBase.bSync is TRUE
    ven_setting_network_profile_t *pProfile;    //output: only useful if the ReqBase.bSync is TRUE
} iVen_setting_getNetworkProfile_req_t;

typedef struct
{
    iVen_AsyncReq_BodyBase_t ReqBase;
    ven_setting_network_profile_type_t Type;
    ven_common_sim_id_t SimID;
    ven_setting_ret_t *pRetCode; //output: only useful if the ReqBase.bSync is TRUE
    ven_setting_network_profile_ex_t *pProfile;    //output: only useful if the ReqBase.bSync is TRUE
} iVen_setting_getNetworkProfile_ex_req_t;


/****************************************************************************/
/*  Message :       I_VEN_SETTING_GET_NETWORK_PROFILE_RSP                   */
/*--------------------------------------------------------------------------*/
/*                                                                          */
/*  From/to   : MMI to Vendor task                                          */
/*                                                                          */
/*  Scope     :                                                             */
/*                                                                          */
/*  Structure : iVen_setting_getNetworkProfile_rsp_t                        */
/*                                                                          */
/*--------------------------------------------------------------------------*/
/*  Field             |    Type   |  Description                            */
/*--------------------+-----------+-----------------------------------------*/
/*                    |           |                                         */
/****************************************************************************/
typedef struct
{
    iVen_AsyncRsp_BodyBase_t RspBase;
    ven_setting_ret_t RetCode;
    ven_setting_network_profile_t Profile;
    ven_setting_network_profile_type_t Type;
    ven_common_sim_id_t SimID;
} iVen_setting_getNetworkProfile_rsp_t;

typedef struct
{
    iVen_AsyncRsp_BodyBase_t RspBase;
    ven_setting_ret_t RetCode;
    ven_setting_network_profile_ex_t Profile;
    ven_setting_network_profile_type_t Type;
    ven_common_sim_id_t SimID;
} iVen_setting_getNetworkProfile_ex_rsp_t;


/****************************************************************************/
/*  Message :       I_VEN_SETTING_SET_NETWORK_PROFILE_REQ                   */
/*--------------------------------------------------------------------------*/
/*                                                                          */
/*  From/to   : Vendor task to MMI                                          */
/*                                                                          */
/*  Scope     :                                                             */
/*                                                                          */
/*  Structure : iVen_setting_setNetworkProfile_req_t                        */
/*                                                                          */
/*--------------------------------------------------------------------------*/
/*  Field             |    Type   |  Description                            */
/*--------------------+-----------+-----------------------------------------*/
/*                    |           |                                         */
/****************************************************************************/
typedef struct
{
    iVen_AsyncReq_BodyBase_t ReqBase;
    ven_setting_network_profile_type_t Type;
    ven_common_sim_id_t SimID;
    ven_setting_network_profile_t Profile;
    ven_setting_ret_t *pRetCode; //output: only useful if the ReqBase.bSync is TRUE
} iVen_setting_setNetworkProfile_req_t;

typedef struct
{
    iVen_AsyncReq_BodyBase_t ReqBase;
    ven_setting_network_profile_type_t Type;
    ven_common_sim_id_t SimID;
    ven_setting_network_profile_ex_t Profile;
    ven_setting_ret_t *pRetCode; //output: only useful if the ReqBase.bSync is TRUE
} iVen_setting_setNetworkProfile_ex_req_t;


/****************************************************************************/
/*  Message :       I_VEN_SETTING_SET_NETWORK_PROFILE_RSP                   */
/*--------------------------------------------------------------------------*/
/*                                                                          */
/*  From/to   : MMI to Vendor task                                          */
/*                                                                          */
/*  Scope     :                                                             */
/*                                                                          */
/*  Structure : iVen_setting_setNetworkProfile_rsp_t                        */
/*                                                                          */
/*--------------------------------------------------------------------------*/
/*  Field             |    Type   |  Description                            */
/*--------------------+-----------+-----------------------------------------*/
/*                    |           |                                         */
/****************************************************************************/
typedef struct
{
    iVen_AsyncRsp_BodyBase_t RspBase;
    ven_setting_ret_t RetCode;
    ven_setting_network_profile_type_t Type;
    ven_common_sim_id_t SimID;
} iVen_setting_setNetworkProfile_rsp_t;


/****************************************************************************/
/*  Message :       I_VEN_SETTING_GET_SELECT_SIM_REQ                        */
/*--------------------------------------------------------------------------*/
/*                                                                          */
/*  From/to   : Vendor task to MMI                                          */
/*                                                                          */
/*  Scope     :                                                             */
/*                                                                          */
/*  Structure : iVen_setting_getSelectSIM_req_t                             */
/*                                                                          */
/*--------------------------------------------------------------------------*/
/*  Field             |    Type   |  Description                            */
/*--------------------+-----------+-----------------------------------------*/
/*                    |           |                                         */
/****************************************************************************/
typedef struct
{
    iVen_AsyncReq_BodyBase_t ReqBase;
    ven_setting_sim_function_type_t Type;
    ven_setting_ret_t *pRetCode;    //output: only useful if the ReqBase.bSync is TRUE
    ven_common_sim_id_t *pSimID;    //output: only useful if the ReqBase.bSync is TRUE
} iVen_setting_getSelectSIM_req_t;


/****************************************************************************/
/*  Message :       I_VEN_SETTING_GET_SELECT_SIM_RSP                        */
/*--------------------------------------------------------------------------*/
/*                                                                          */
/*  From/to   : MMI to Vendor task                                          */
/*                                                                          */
/*  Scope     :                                                             */
/*                                                                          */
/*  Structure : iVen_setting_getSelectSIM_rsp_t                             */
/*                                                                          */
/*--------------------------------------------------------------------------*/
/*  Field             |    Type   |  Description                            */
/*--------------------+-----------+-----------------------------------------*/
/*                    |           |                                         */
/****************************************************************************/
typedef struct
{
    iVen_AsyncRsp_BodyBase_t RspBase;
    ven_setting_ret_t RetCode;
    ven_common_sim_id_t SimID;
    ven_setting_sim_function_type_t Type;
} iVen_setting_getSelectSIM_rsp_t;

/****************************************************************************/
/*  Message :       I_VEN_SETTING_GET_DEFAULT_SIM_REQ                       */
/*--------------------------------------------------------------------------*/
/*                                                                          */
/*  From/to   : Vendor task to MMI                                          */
/*                                                                          */
/*  Scope     :                                                             */
/*                                                                          */
/*  Structure : iVen_setting_getSelectSIM_req_t                             */
/*                                                                          */
/*--------------------------------------------------------------------------*/
/*  Field             |    Type   |  Description                            */
/*--------------------+-----------+-----------------------------------------*/
/*                    |           |                                         */
/****************************************************************************/
typedef struct
{
    iVen_AsyncReq_BodyBase_t ReqBase;
    ven_setting_sim_function_type_t Type;
    ven_setting_ret_t *pRetCode;    //output: only useful if the ReqBase.bSync is TRUE
    ven_common_sim_id_t *pSimID;    //output: only useful if the ReqBase.bSync is TRUE
} iVen_setting_getDefaultSIM_req_t;


/****************************************************************************/
/*  Message :       I_VEN_SETTING_GET_DEFAULT_SIM_RSP                       */
/*--------------------------------------------------------------------------*/
/*                                                                          */
/*  From/to   : MMI to Vendor task                                          */
/*                                                                          */
/*  Scope     :                                                             */
/*                                                                          */
/*  Structure : iVen_setting_getSelectSIM_rsp_t                             */
/*                                                                          */
/*--------------------------------------------------------------------------*/
/*  Field             |    Type   |  Description                            */
/*--------------------+-----------+-----------------------------------------*/
/*                    |           |                                         */
/****************************************************************************/
typedef struct
{
    iVen_AsyncRsp_BodyBase_t RspBase;
    ven_setting_ret_t RetCode;
    ven_common_sim_id_t SimID;
    ven_setting_sim_function_type_t Type;
} iVen_setting_getDefaultSIM_rsp_t;

/****************************************************************************/
/*  Message :       I_VEN_SETTING_GET_SIM_ICCID_REQ                        */
/*--------------------------------------------------------------------------*/
/*                                                                          */
/*  From/to   : Vendor task to MMI                                          */
/*                                                                          */
/*  Scope     :                                                             */
/*                                                                          */
/*  Structure : iVen_setting_getSIMIccId_req_t                             */
/*                                                                          */
/*--------------------------------------------------------------------------*/
/*  Field             |    Type   |  Description                            */
/*--------------------+-----------+-----------------------------------------*/
/*                    |           |                                         */
/****************************************************************************/
typedef struct
{
    iVen_AsyncReq_BodyBase_t    ReqBase;
    ven_common_sim_id_t         SimID;
    ven_setting_ret_t           *pRetCode;
    ven_setting_SIMIccID_t      *pIccID;
} iVen_setting_getSIMIccId_req_t;
typedef struct
{
    iVen_AsyncReq_BodyBase_t ReqBase;
    ven_setting_sim_status_t *eStatus;    //output: only useful if the ReqBase.bSync is TRUE
    ven_setting_ret_t *pRetCode;    //output: only useful if the ReqBase.bSync is TRUE
} iVen_setting_getSIMStatus_req_t;

typedef struct
{
    iVen_AsyncRsp_BodyBase_t RspBase;
    ven_setting_ret_t RetCode;
    ven_setting_sim_status_t eStatus;
} iVen_setting_getSIMStatus_rsp_t;


/****************************************************************************/
/*  Message :       I_VEN_SETTING_GET_LANGUAGE_REQ                          */
/*--------------------------------------------------------------------------*/
/*                                                                          */
/*  From/to   : Vendor task to MMI                                          */
/*                                                                          */
/*  Scope     :                                                             */
/*                                                                          */
/*  Structure : iVen_setting_getLanguage_req_t                              */
/*                                                                          */
/*--------------------------------------------------------------------------*/
/*  Field             |    Type   |  Description                            */
/*--------------------+-----------+-----------------------------------------*/
/*                    |           |                                         */
/****************************************************************************/
typedef struct
{
    iVen_AsyncReq_BodyBase_t ReqBase;
    ven_setting_ret_t *pRetCode;    //output: only useful if the ReqBase.bSync is TRUE
    ven_setting_lang_t *pLang;      //output: only useful if the ReqBase.bSync is TRUE
} iVen_setting_getLanguage_req_t;


/****************************************************************************/
/*  Message :       I_VEN_SETTING_GET_LANGUAGE_RSP                          */
/*--------------------------------------------------------------------------*/
/*                                                                          */
/*  From/to   : MMI to Vendor task                                          */
/*                                                                          */
/*  Scope     :                                                             */
/*                                                                          */
/*  Structure : iVen_setting_getLanguage_rsp_t                              */
/*                                                                          */
/*--------------------------------------------------------------------------*/
/*  Field             |    Type   |  Description                            */
/*--------------------+-----------+-----------------------------------------*/
/*                    |           |                                         */
/****************************************************************************/
typedef struct
{
    iVen_AsyncRsp_BodyBase_t RspBase;
    ven_setting_ret_t RetCode;
    ven_setting_lang_t Lang;
} iVen_setting_getLanguage_rsp_t;

/****************************************************************************/
/*  Message :       I_VEN_SETTING_GET_NETWORK_PROFILE_NUM_REQ               */
/*--------------------------------------------------------------------------*/
/*                                                                          */
/*  From/to   : Vendor task to MMI                                          */
/*                                                                          */
/*  Scope     :                                                             */
/*                                                                          */
/*  Structure :iVen_setting_getNetworkProfileNum_req_t                      */
/*                                                                          */
/*--------------------------------------------------------------------------*/
/*  Field             |    Type   |  Description                            */
/*--------------------+-----------+-----------------------------------------*/
/*                    |           |                                         */
/****************************************************************************/
typedef struct
{
    iVen_AsyncReq_BodyBase_t ReqBase;
    ven_setting_network_profile_type_t Type;
    ven_setting_ret_t *pRetCode; //output: only useful if the ReqBase.bSync is TRUE
    u8 *pNum;   // output: only useful if the ReqBase.bSync is TRUE
} iVen_setting_getNetworkProfileNum_req_t;

/****************************************************************************/
/*  Message :       I_VEN_SETTING_GET_NETWORK_PROFILE_BY_IDX_REQ            */
/*--------------------------------------------------------------------------*/
/*                                                                          */
/*  From/to   : Vendor task to MMI                                          */
/*                                                                          */
/*  Scope     :                                                             */
/*                                                                          */
/*  Structure :iVen_setting_getNetworkProfileByIdx_req_t                    */
/*                                                                          */
/*--------------------------------------------------------------------------*/
/*  Field             |    Type   |  Description                            */
/*--------------------+-----------+-----------------------------------------*/
/*                    |           |                                         */
/****************************************************************************/
typedef struct
{
    iVen_AsyncReq_BodyBase_t ReqBase;
    ven_setting_network_profile_type_t type;
    u8 idx;
    ven_setting_ret_t *pRetCode; //output: only useful if the ReqBase.bSync is TRUE
    ven_setting_network_profile_t *pProfile;    //output: only useful if the ReqBase.bSync is TRUE
} iVen_setting_getNetworkProfileByIdx_req_t;

/****************************************************************************/
/*  Message :       I_VEN_SETTING_GET_DATA_ACCOUNT_NUM_REQ                  */
/*--------------------------------------------------------------------------*/
/*                                                                          */
/*  From/to   : Vendor task to MMI                                          */
/*                                                                          */
/*  Scope     :                                                             */
/*                                                                          */
/*  Structure :iVen_setting_getDataAccountNum_req_t                         */
/*                                                                          */
/*--------------------------------------------------------------------------*/
/*  Field             |    Type   |  Description                            */
/*--------------------+-----------+-----------------------------------------*/
/*                    |           |                                         */
/****************************************************************************/
typedef struct
{
    iVen_AsyncReq_BodyBase_t ReqBase;
    ven_setting_ret_t *pRetCode; //output: only useful if the ReqBase.bSync is TRUE
    u8 *pNum;   // output: only useful if the ReqBase.bSync is TRUE
} iVen_setting_getDataAccountNum_req_t;

/****************************************************************************/
/*  Message :       I_VEN_SETTING_GET_DATA_ACCOUNT_BY_IDX_REQ               */
/*--------------------------------------------------------------------------*/
/*                                                                          */
/*  From/to   : Vendor task to MMI                                          */
/*                                                                          */
/*  Scope     :                                                             */
/*                                                                          */
/*  Structure :iVen_setting_getDataAccountByIdx_req_t                       */
/*                                                                          */
/*--------------------------------------------------------------------------*/
/*  Field             |    Type   |  Description                            */
/*--------------------+-----------+-----------------------------------------*/
/*                    |           |                                         */
/****************************************************************************/
typedef struct
{
    iVen_AsyncReq_BodyBase_t ReqBase;
    u8 idx;
    ven_setting_ret_t *pRetCode; //output: only useful if the ReqBase.bSync is TRUE
    ven_setting_data_account_t *pAccount;    //output: only useful if the ReqBase.bSync is TRUE
} iVen_setting_getDataAccountByIdx_req_t;

/****************************************************************************/
/*  Message :       I_VEN_SETTING_QUERY_AIRPLANE_MODE_REQ                   */
/*--------------------------------------------------------------------------*/
/*                                                                          */
/*  From/to   : Vendor task to MMI                                          */
/*                                                                          */
/*  Scope     :                                                             */
/*                                                                          */
/*  Structure : iVen_setting_queryAirplaneMode_req_t                        */
/*                                                                          */
/*--------------------------------------------------------------------------*/
/*  Field             |    Type   |  Description                            */
/*--------------------+-----------+-----------------------------------------*/
/*                    |           |                                         */
/****************************************************************************/
typedef struct
{
    iVen_AsyncReq_BodyBase_t ReqBase;
    bool *pbRet;    //output: only useful if the ReqBase.bSync is TRUE
} iVen_setting_queryAirplaneMode_req_t;

/****************************************************************************/
/*  Message :       I_VEN_SETTING_GET_DEFAULT_CAM_REQ                       */
/*--------------------------------------------------------------------------*/
/*                                                                          */
/*  From/to   : Vendor task to MMI                                          */
/*                                                                          */
/*  Scope     :                                                             */
/*                                                                          */
/*  Structure : iVen_setting_getDefaultCam_req_t                            */
/*                                                                          */
/*--------------------------------------------------------------------------*/
/*  Field             |    Type   |  Description                            */
/*--------------------+-----------+-----------------------------------------*/
/*                    |           |                                         */
/****************************************************************************/
#ifndef __SDK_API_WAP_MMS_ONLY__
typedef struct
{
    iVen_AsyncReq_BodyBase_t ReqBase;
    ven_setting_ret_t *pRetCode;    //output: only useful if the ReqBase.bSync is TRUE
    ven_cam_id_t *pCamID;    //output: only useful if the ReqBase.bSync is TRUE
} iVen_setting_getDefaultCam_req_t;
#endif
#endif //__VEN_SETTING_STMSG_H__

