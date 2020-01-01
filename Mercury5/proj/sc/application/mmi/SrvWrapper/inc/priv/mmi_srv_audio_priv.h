/**
* @file    mmi_srv_audio_priv.h
* @brief
*
*
* @author
* @version $Id: mmi_srv_audio_priv.h 33169 2009-06-12 05:19:42Z johnson.yeh $
*/

#ifndef __MMI_SRV_AUDIO_PRIV_H__
#define __MMI_SRV_AUDIO_PRIV_H__


/*-----------------------------------------------------*/
#include "mmi_srv_client_commondefine.h"

/** SrvAudioCreate
* @brief  The interface is use to create Service Body, Only used for Srv_Client.c;
*
* @param[in]        pClient             Pointer to the Audio service client.
* @param[in]        pData               Init used data // non use in MAE
*
* @return MAE_RET_SUCCESS         If successful.
* @return MAE_RET_FAILED          If an error happen.
*/
MAE_Ret SrvAudioCreate(SrvClient_t *pClient, s32 *pData);

/** SrvAudioDestroy
* @brief  The interface is use to Destroy Service Body, Only used for Srv_Client.c;
*
* @param[in]        pClient             Pointer to the Audio service client.
* @param[in]        pData               Release used data // non use in MAE
*
* @return MAE_RET_SUCCESS         If successful.
* @return MAE_RET_FAILED          If an error happen.
*/
MAE_Ret SrvAudioDestroy(SrvClient_t *pClient, s32 *pData);

/*-----------------------------------------------------*/
#endif //__MMI_SRV_AUDIO_PRIV_H__
