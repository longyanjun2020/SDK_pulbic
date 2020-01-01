#ifndef __VEN_SENSOR_MSGT_H__
#define __VEN_SENSOR_MSGT_H__

#ifndef __SDK_API_WAP_MMS_ONLY__


#include "ven_sensor.h"
#include "ven_comdef_priv.h"

#if defined (__G_SENSOR__)
typedef struct
{
    iVen_AsyncReq_BodyBase_t ReqBase;
	ven_sen_gsensor_notify_delay_t nDelay;
	bool bListenOnPowerSavingMode;
	void *pGsensorNotify;
	u32 usrData;
    ven_sen_ret_t *pRetCode; //output: only useful if the ReqBase.bSync is TRUE
} iVen_sen_gsensor_reg_notify_req_t;

typedef struct
{
    iVen_AsyncRsp_BodyBase_t RspBase;
	ven_sen_gsensor_info_t gsensorInfo;
} iVen_sen_gsensor_reg_notify_ind_t;

typedef struct
{
    iVen_AsyncRsp_BodyBase_t RspBase;
    ven_sen_ret_t retCode;
} iVen_sen_gsensor_reg_notify_rsp_t;

typedef struct
{
    iVen_AsyncReq_BodyBase_t ReqBase;
	ven_sen_gsensor_devInfo_t *pDevInfo;
    ven_sen_ret_t *pRetCode; //output: only useful if the ReqBase.bSync is TRUE
} iVen_sen_gsensor_get_devinfo_req_t;

typedef struct
{
    iVen_AsyncRsp_BodyBase_t RspBase;
	ven_sen_gsensor_devInfo_t devInfo;
    ven_sen_ret_t retCode;
} iVen_sen_gsensor_get_devinfo_rsp_t;

typedef struct
{
    iVen_AsyncReq_BodyBase_t ReqBase;
	ven_sen_gsensor_motion_type_t type;
	bool bListenOnPowerSavingMode;
	void *pMotionListener;
	u32 usrData;
    ven_sen_ret_t *pRetCode; //output: only useful if the ReqBase.bSync is TRUE
} iVen_sen_gsensor_reg_motion_listener_req_t;

typedef struct
{
    iVen_AsyncRsp_BodyBase_t RspBase;
	u32 type;
	u32 value;
} iVen_sen_gsensor_reg_motion_listener_ind_t;

typedef struct
{
    iVen_AsyncRsp_BodyBase_t RspBase;
    ven_sen_ret_t retCode;
} iVen_sen_gsensor_reg_motion_listener_rsp_t;

typedef struct
{
    iVen_AsyncReq_BodyBase_t ReqBase;
	ven_sen_gsensor_motion_type_t type;
	u32 *pMotionInfo;
    ven_sen_ret_t *pRetCode; //output: only useful if the ReqBase.bSync is TRUE
} iVen_sen_gsensor_get_last_motion_req_t;

typedef struct
{
    iVen_AsyncRsp_BodyBase_t RspBase;
	u32 type;
	u32 motionInfo;
    ven_sen_ret_t retCode;
} iVen_sen_gsensor_get_last_motion_rsp_t;

#endif //#if defined (__G_SENSOR__)

typedef struct
{
    iVen_AsyncReq_BodyBase_t ReqBase;
	u16* pFileUrl;
	bool bIsDelete;
    ven_sen_ret_t *pRetCode; //output: only useful if the ReqBase.bSync is TRUE
} iVen_sen_btapp_send_file_req_t;

typedef struct
{
    iVen_AsyncRsp_BodyBase_t RspBase;
    ven_sen_ret_t retCode;
} iVen_sen_btapp_send_file_rsp_t;

#endif //#ifndef __SDK_API_WAP_MMS_ONLY__
#endif
