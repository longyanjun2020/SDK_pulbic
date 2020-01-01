#ifndef __VEN_CAM_MSGT_H__
#define __VEN_CAM_MSGT_H__

#ifndef __SDK_API_WAP_MMS_ONLY__

#include "ven_cam.h"
#include "ven_msg.h"
#include "ven_comdef_priv.h"


/****************************************************************************/
/*  Message :       I_VEN_CAM_OPEN_CAMERA_REQ                               */
/*--------------------------------------------------------------------------*/
/*                                                                          */
/*  From/to   : Vendor task to MMI                                          */
/*                                                                          */
/*  Scope     : The structure of the message with the purpose to open       */
/*              with the given camera id                                    */
/*                                                                          */
/*  Structure : iVen_cam_open_cam_req_t                                 */
/*                                                                          */
/*--------------------------------------------------------------------------*/
/*  Field             |    Type   |  Description                            */
/*--------------------+-----------+-----------------------------------------*/
/*                    |           |                                         */
/****************************************************************************/
typedef struct
{
    iVen_AsyncReq_BodyBase_t ReqBase;
    s32 *pCamHandle;
    ven_cam_open_param_t openParam;
    ven_cam_ret_t *pRetCode; //output: only useful if the ReqBase.bSync is TRUE
} iVen_cam_open_camera_req_t;

/****************************************************************************/
/*  Message :       I_VEN_CAM_OPEN_CAMERA_RSP                               */
/*--------------------------------------------------------------------------*/
/*                                                                          */
/*  From/to   : MMI to Vendor task                                          */
/*                                                                          */
/*  Scope     : The structure of the message with the result of             */
/*              opening camera                                              */
/*                                                                          */
/*  Structure : iVen_cam_open_camera_rsp_t                                 */
/*                                                                          */
/*--------------------------------------------------------------------------*/
/*  Field             |    Type   |  Description                            */
/*--------------------+-----------+-----------------------------------------*/
/*                    |           |                                         */
/****************************************************************************/
typedef struct
{
    iVen_AsyncRsp_BodyBase_t RspBase;
    s32 camHandle;
    ven_cam_ret_t retCode;
} iVen_cam_open_camera_rsp_t;

/****************************************************************************/
/*  Message :       I_VEN_CAM_CLOSE_CAMERA_REQ                              */
/*--------------------------------------------------------------------------*/
/*                                                                          */
/*  From/to   : Vendor task to MMI                                          */
/*                                                                          */
/*  Scope     : The structure of the message with the purpose to close a    */
/*              opened camera handle                                        */
/*                                                                          */
/*  Structure : iVen_cam_close_camera_req_t                                 */
/*                                                                          */
/*--------------------------------------------------------------------------*/
/*  Field             |    Type   |  Description                            */
/*--------------------+-----------+-----------------------------------------*/
/*                    |           |                                         */
/****************************************************************************/
typedef struct
{
    iVen_AsyncReq_BodyBase_t ReqBase;
    s32 camHandle;
    ven_cam_ret_t *pRetCode; //output: only useful if the ReqBase.bSync is TRUE
} iVen_cam_close_camera_req_t;

/****************************************************************************/
/*  Message :       I_VEN_CAM_CLOSE_CAMERA_RSP                               */
/*--------------------------------------------------------------------------*/
/*                                                                          */
/*  From/to   : MMI to Vendor task                                          */
/*                                                                          */
/*  Scope     : The structure of the message with the result of             */
/*              closing camera                                              */
/*                                                                          */
/*  Structure : iVen_cam_close_camera_rsp_t                                 */
/*                                                                          */
/*--------------------------------------------------------------------------*/
/*  Field             |    Type   |  Description                            */
/*--------------------+-----------+-----------------------------------------*/
/*                    |           |                                         */
/****************************************************************************/
typedef struct
{
    iVen_AsyncRsp_BodyBase_t RspBase;
    ven_cam_ret_t retCode;
} iVen_cam_close_camera_rsp_t;

/****************************************************************************/
/*  Message :       I_VEN_CAM_START_PREVIEW_REQ                             */
/*--------------------------------------------------------------------------*/
/*                                                                          */
/*  From/to   : Vendor task to MMI                                          */
/*                                                                          */
/*  Scope     : The structure of the message with the purpose to start      */
/*              camera preview                                              */
/*                                                                          */
/*  Structure : iVen_cam_start_preview_req_t                                */
/*                                                                          */
/*--------------------------------------------------------------------------*/
/*  Field             |    Type   |  Description                            */
/*--------------------+-----------+-----------------------------------------*/
/*                    |           |                                         */
/****************************************************************************/
typedef struct
{
    iVen_AsyncReq_BodyBase_t ReqBase;
    s32 camHandle;
    ven_cam_ret_t *pRetCode; //output: only useful if the ReqBase.bSync is TRUE
} iVen_cam_start_preview_req_t;

/****************************************************************************/
/*  Message :       I_VEN_CAM_START_PREVIEW_RSP                             */
/*--------------------------------------------------------------------------*/
/*                                                                          */
/*  From/to   : MMI to Vendor task                                          */
/*                                                                          */
/*  Scope     : The structure of the message with the result of             */
/*              starting camera preview                                     */
/*                                                                          */
/*  Structure : iVen_cam_start_preview_rsp_t                               */
/*                                                                          */
/*--------------------------------------------------------------------------*/
/*  Field             |    Type   |  Description                            */
/*--------------------+-----------+-----------------------------------------*/
/*                    |           |                                         */
/****************************************************************************/
typedef struct
{
    iVen_AsyncRsp_BodyBase_t RspBase;
    ven_cam_ret_t retCode;
} iVen_cam_start_preview_rsp_t;

/****************************************************************************/
/*  Message :       I_VEN_CAM_STOP_PREVIEW_REQ                              */
/*--------------------------------------------------------------------------*/
/*                                                                          */
/*  From/to   : Vendor task to MMI                                          */
/*                                                                          */
/*  Scope     : The structure of the message with the purpose to stop       */
/*              camera preview                                              */
/*                                                                          */
/*  Structure : iVen_cam_stop_preview_req_t                                 */
/*                                                                          */
/*--------------------------------------------------------------------------*/
/*  Field             |    Type   |  Description                            */
/*--------------------+-----------+-----------------------------------------*/
/*                    |           |                                         */
/****************************************************************************/
typedef struct
{
    iVen_AsyncReq_BodyBase_t ReqBase;
    s32 camHandle;
    ven_cam_ret_t *pRetCode; //output: only useful if the ReqBase.bSync is TRUE
} iVen_cam_stop_preview_req_t;

/****************************************************************************/
/*  Message :       I_VEN_CAM_STOP_PREVIEW_RSP                              */
/*--------------------------------------------------------------------------*/
/*                                                                          */
/*  From/to   : MMI to Vendor task                                          */
/*                                                                          */
/*  Scope     : The structure of the message with the result of             */
/*              stopping camera preview                                     */
/*                                                                          */
/*  Structure : iVen_cam_stop_preview_rsp_t                                 */
/*                                                                          */
/*--------------------------------------------------------------------------*/
/*  Field             |    Type   |  Description                            */
/*--------------------+-----------+-----------------------------------------*/
/*                    |           |                                         */
/****************************************************************************/
typedef struct
{
    iVen_AsyncRsp_BodyBase_t RspBase;
    ven_cam_ret_t retCode;
} iVen_cam_stop_preview_rsp_t;

/****************************************************************************/
/*  Message :       I_VEN_CAM_CAPTURE_IMAGE_REQ                             */
/*--------------------------------------------------------------------------*/
/*                                                                          */
/*  From/to   : Vendor task to MMI                                          */
/*                                                                          */
/*  Scope     : The structure of the message with the purpose to capture    */
/*              image                                                       */
/*                                                                          */
/*  Structure : iVen_cam_capture_image_req_t                                */
/*                                                                          */
/*--------------------------------------------------------------------------*/
/*  Field             |    Type   |  Description                            */
/*--------------------+-----------+-----------------------------------------*/
/*                    |           |                                         */
/****************************************************************************/
typedef struct
{
    iVen_AsyncReq_BodyBase_t ReqBase;
    s32 camHandle;
    ven_cam_capture_param_t param;
} iVen_cam_capture_image_req_t;

/****************************************************************************/
/*  Message :       I_VEN_CAM_CAPTURE_IMAGE_RSP                             */
/*--------------------------------------------------------------------------*/
/*                                                                          */
/*  From/to   : MMI to Vendor task                                          */
/*                                                                          */
/*  Scope     : The structure of the message with the result of             */
/*              image capture                                               */
/*                                                                          */
/*  Structure : iVen_cam_stop_preview_rsp_t                                 */
/*                                                                          */
/*--------------------------------------------------------------------------*/
/*  Field             |    Type   |  Description                            */
/*--------------------+-----------+-----------------------------------------*/
/*                    |           |                                         */
/****************************************************************************/
typedef struct
{
    iVen_AsyncRsp_BodyBase_t RspBase;
    ven_cam_ret_t retCode;
} iVen_cam_capture_image_rsp_t;

/****************************************************************************/
/*  Message :       I_VEN_CAM_CONVERT_IMAGE_REQ                             */
/*--------------------------------------------------------------------------*/
/*                                                                          */
/*  From/to   : Vendor task to MMI                                          */
/*                                                                          */
/*  Scope     : The structure of the message with the purpose to converting */
/*              image                                                       */
/*                                                                          */
/*  Structure : iVen_cam_capture_image_req_t                                */
/*                                                                          */
/*--------------------------------------------------------------------------*/
/*  Field             |    Type   |  Description                            */
/*--------------------+-----------+-----------------------------------------*/
/*                    |           |                                         */
/****************************************************************************/
typedef struct
{
    iVen_AsyncReq_BodyBase_t ReqBase;
    s32 camHandle;
    ven_cam_source_buffer_param_t sourceParam;
    ven_cam_destination_buffer_param_t destParam;
} iVen_cam_convert_image_req_t;

/****************************************************************************/
/*  Message :       I_VEN_CAM_CONVERT_IMAGE_RSP                             */
/*--------------------------------------------------------------------------*/
/*                                                                          */
/*  From/to   : MMI to Vendor task                                          */
/*                                                                          */
/*  Scope     : The structure of the message with the result of             */
/*              converting capture                                          */
/*                                                                          */
/*  Structure : iVen_cam_stop_preview_rsp_t                                 */
/*                                                                          */
/*--------------------------------------------------------------------------*/
/*  Field             |    Type   |  Description                            */
/*--------------------+-----------+-----------------------------------------*/
/*                    |           |                                         */
/****************************************************************************/
typedef struct
{
    iVen_AsyncRsp_BodyBase_t RspBase;
    ven_cam_ret_t retCode;
} iVen_cam_convert_image_rsp_t;

/****************************************************************************/
/*  Message :       I_VEN_CAM_LAUNCH_APP_REQ                                */
/*--------------------------------------------------------------------------*/
/*                                                                          */
/*  From/to   : Vendor task to MMI                                          */
/*                                                                          */
/*  Scope     : The structure of the message with the purpose to launch MMI camera applet */
/*                                                                          */
/*  Structure : iVen_cam_launch_app_req_t                                   */
/*                                                                          */
/*--------------------------------------------------------------------------*/
/*  Field             |    Type   |  Description                            */
/*--------------------+-----------+-----------------------------------------*/
/*                    |           |                                         */
/****************************************************************************/
typedef struct
{
    iVen_AsyncReq_BodyBase_t ReqBase;
	ven_cam_launch_app_req_t *pLaunch_AP_Req;
} iVen_cam_launch_app_req_t;

/****************************************************************************/
/*  Message :       I_VEN_CAM_LAUNCH_APP_RSP                                */
/*--------------------------------------------------------------------------*/
/*                                                                          */
/*  From/to   : MMI to Vendor task                                          */
/*                                                                          */
/*  Scope     : The structure of the message with the result of             */
/*              launch MMI camera applet                                    */
/*                                                                          */
/*  Structure : iVen_cam_launch_app_rsp_t                                */
/*                                                                          */
/*--------------------------------------------------------------------------*/
/*  Field             |    Type   |  Description                            */
/*--------------------+-----------+-----------------------------------------*/
/*                    |           |                                         */
/****************************************************************************/
typedef struct
{
    iVen_AsyncRsp_BodyBase_t RspBase;
    u8        nNumOfPhotoOrVideo;
    u16       *pFileName;
} iVen_cam_launch_app_rsp_t;

#endif //#ifndef __SDK_API_WAP_MMS_ONLY__

#endif //__VEN_CAM_MSGT_H__

