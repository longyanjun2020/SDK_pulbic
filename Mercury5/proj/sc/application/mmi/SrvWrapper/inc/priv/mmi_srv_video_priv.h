/**
* @file    mmi_srv_video_priv.h
* @brief
*
*
* @author
* @version $Id: mmi_srv_video_priv.h 33169 2010-03-22 14:41:42Z john.bai $
*/

#ifndef __MMI_SRV_VIDEO_PRIV_H__
#define __MMI_SRV_VIDEO_PRIV_H__


/*-----------------------------------------------------*/
#include "mmi_srv_client_commondefine.h"

/** SrvVideoCreate
* @brief  The interface is use to create Service Body, Only used for Srv_Client.c;
*
* @param[in]        pClient             Pointer to the Video service client.
* @param[in]        pData               Init used data // non use in MAE
*
* @return MAE_RET_SUCCESS         If successful.
* @return MAE_RET_FAILED          If an error happen.
*/
MAE_Ret SrvVideoCreate(SrvClient_t *pClient, s32 *pData);

/** SrvVideoDestroy
* @brief  The interface is use to Destroy Service Body, Only used for Srv_Client.c;
*
* @param[in]        pClient             Pointer to the Video service client.
* @param[in]        pData               Release used data // non use in MAE
*
* @return MAE_RET_SUCCESS         If successful.
* @return MAE_RET_FAILED          If an error happen.
*/
MAE_Ret SrvVideoDestroy(SrvClient_t *pClient, s32 *pData);

/*-----------------------------------------------------*/
#endif //__MMI_SRV_VIDEO_PRIV_H__
