/**
* @file    mmi_srv_vcalparser_priv.h
* @brief   vCalendar parser service wrapper private header file
*          
*/

#ifndef __MMI_SRV_VCALPARSER_PRIV_H__
#define __MMI_SRV_VCALPARSER_PRIV_H__

#ifdef __CALENDAR_SUPPORT_VCS_MMI__
/*=============================================================*/
// Include files
/*=============================================================*/

#include "mmi_srv_client_commondefine.h"

/*=============================================================*/
// Global function definition
/*=============================================================*/

/** SrvVParamCreate
@brief  The interface is used to create Service Body, Only used for Srv_Client.c;

@param[in]      pClient                 Pointer to the Srv VParam client.
@param[in]      pData                   init used data // non use in MAE

@return MAE_RET_SUCCESS                 If successful.
@return MAE_RET_FAILED                  If an error happen.
*/
MAE_Ret SrvVParamCreate(SrvClient_t *pClient, s32 *pData);

/** SrvVPropertyCreate
@brief  The interface is used to create Service Body, Only used for Srv_Client.c;

@param[in]      pClient                 Pointer to the Srv VProperty client.
@param[in]      pData                   init used data // non use in MAE

@return MAE_RET_SUCCESS                 If successful.
@return MAE_RET_FAILED                  If an error happen.
*/
MAE_Ret SrvVPropertyCreate(SrvClient_t *pClient, s32 *pData);

/** SrvVEventCreate
@brief  The interface is used to create Service Body, Only used for Srv_Client.c;

@param[in]      pClient                 Pointer to the Srv VEvent client.
@param[in]      pData                   init used data // non use in MAE

@return MAE_RET_SUCCESS                 If successful.
@return MAE_RET_FAILED                  If an error happen.
*/
MAE_Ret SrvVEventCreate(SrvClient_t *pClient, s32 *pData);

/** SrvVCalendarCreate
@brief  The interface is used to create Service Body, Only used for Srv_Client.c;

@param[in]      pClient                 Pointer to the Srv VCalendar client.
@param[in]      pData                   init used data // non use in MAE

@return MAE_RET_SUCCESS                 If successful.
@return MAE_RET_FAILED                  If an error happen.
*/
MAE_Ret SrvVCalendarCreate(SrvClient_t *pClient, s32 *pData);

/** SrvVParamDestroy
@brief  The interface is used to Destroy Service Body, Only used for Srv_Client.c;

@param[in]      pClient                 Pointer to the Srv VParam client.
@param[in]      pData                   close used data // non use in MAE

@return MAE_RET_SUCCESS                 If successful.
@return MAE_RET_FAILED                  If an error happen.
*/
MAE_Ret SrvVParamDestroy(SrvClient_t *pClient, s32 *pData);

/** SrvVPropertyDestroy
@brief  The interface is used to Destroy Service Body, Only used for Srv_Client.c;

@param[in]      pClient                 Pointer to the Srv VProperty client.
@param[in]      pData                   close used data // non use in MAE

@return MAE_RET_SUCCESS                 If successful.
@return MAE_RET_FAILED                  If an error happen.
*/
MAE_Ret SrvVPropertyDestroy(SrvClient_t *pClient, s32 *pData);

/** SrvVEventDestroy
@brief  The interface is used to Destroy Service Body, Only used for Srv_Client.c;

@param[in]      pClient                 Pointer to the Srv VEvent client.
@param[in]      pData                   close used data // non use in MAE

@return MAE_RET_SUCCESS                 If successful.
@return MAE_RET_FAILED                  If an error happen.
*/
MAE_Ret SrvVEventDestroy(SrvClient_t *pClient, s32 *pData);

/** SrvVCalendarDestroy
@brief  The interface is used to Destroy Service Body, Only used for Srv_Client.c;

@param[in]      pClient                 Pointer to the Srv VCalendar client.
@param[in]      pData                   close used data // non use in MAE

@return MAE_RET_SUCCESS                 If successful.
@return MAE_RET_FAILED                  If an error happen.
*/
MAE_Ret SrvVCalendarDestroy(SrvClient_t *pClient, s32 *pData);

/*-----------------------------------------------------*/
#endif // __CALENDAR_SUPPORT_VCS_MMI__
#endif //__MMI_SRV_VCALPARSER_PRIV_H__

