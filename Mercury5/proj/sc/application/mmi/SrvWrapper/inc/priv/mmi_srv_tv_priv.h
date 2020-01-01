/**
* @file    mmi_srv_tv_priv.h
* @brief
*
*/

#ifndef __MMI_SRV_TV_PRIV_H__
#define __MMI_SRV_TV_PRIV_H__


/*-----------------------------------------------------*/
#include "mmi_srv_client_commondefine.h"


MAE_Ret SrvTvCreate(SrvClient_t *pClient, s32 *pData);
MAE_Ret SrvTvDestroy(SrvClient_t *pClient, s32 *pData);
/*-----------------------------------------------------*/
#endif //__MMI_SRV_TV_PRIV_H__
