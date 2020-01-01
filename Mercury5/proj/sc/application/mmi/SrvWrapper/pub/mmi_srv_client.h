/**
* @file    mmi_srv_client.h
* @brief   
*          
*
* @author  
* @version $Id: mmi_common_dialog.h 33169 2009-06-12 05:19:42Z collin.chiang $
*/

#ifndef __MMI_SRV_CLIENT_H__
#define __MMI_SRV_CLIENT_H__

#include "mmi_srv_client_commondefine.h"
#include "mmi_srv_client_platformdefines.h"
//#include "mmi_srv_client_priv.h"
#include "mmi_mae_common_def.h"

/*-----------------------------------------------------*/
/*================================================
For AP use Service Event to call back List Module Generic API
=================================================*/
//For AP cleint.h
//Create
SrvCBListModule_t *SrvClientAppCreateCBListModule( void );
//Destroy
void SrvClientAppDestroyCBListModule( SrvCBListModule_t *pCBModule );
//set
MAE_Ret SrvClientSetCB( SrvClient_t *pClient,
                          SrvCBListModule_t *pModule,
                          u32 IndType,
                          void *pfnEvToCB,
                          void *pfnEvCastParaToCB );
//clear
MAE_Ret SrvClientClearCB( SrvClient_t *pClient, SrvCBListModule_t *pModule, u32 IndType );

//Search Event in table
boolean SrvClientAppSearchEvtInModule( IHandler *pThis,
                                         SrvCBListModule_t *pCBModule,
                                         MAEEvent_t nEvt,
                                         u32 Param1,
                                         u32 Param2 );
//Just for Test App to get Service Instance
u32 * SrvClientGetServiceInstanceFromAP(ServiceType_e eServiceType);
/*================================================
For AP use Service Client Generic API
=================================================*/
/**
SrvClientInitTaskClientRootArray
@brief  The interface of Service Client is use to Init each task who will like to used the Service Client to used the Service.

@param[in]      eTask                       Init task eSrv_TaskID.

@return none
*/
void SrvClientInitTaskClientRootArray( Srv_TaskId_e eTask );

/**
SrvClientCreateServiceClient
@brief  The interface of Service Client is use to Create the service client and Service.

@param[in]      eSrvAppID               Owner's eSrvAppID.
@param[in]      eSrvType                the Service type of client want to create
@param[in]      pInstance               the point to the Service client owner
@param[in]      pAppCbModule        the point to the Service client owner's CB Module
@param[in]      nSrvClientFlag      Service client Special Flag //non used now
@param[in]      pData                   Point to data if Create Service need init data //non used now

@return SrvClient_t*                        Point to a New Service Client. Have afddress vaule If successful. If Null, init have some error
*/
SrvClient_t *SrvClientCreateServiceClient( ServiceType_e              eServiceType,
                                             Srv_AppId_e                   eSrvAppID,
                                             void *pInstance,
                                             SrvCBListModule_t *pAppCbModule,
                                             u32                                nSrvClientFlag,
                                             s32 *pData );


//Service Client Generic DestroyAPI
/**
SrvClientDestroyServiceClient
@brief  The interface of Service Client is use to destroy the service client and Service.

@param[in]      eServiceType            the Service type of client want to Delete
@param[in]      pClient                 Pointer to the Service client.
@param[in]      pData                   Point to data if Release Service need data //non used now

@return MAE_RET_SUCCESS                 If successful.
@return MAE_RET_FAILED                  If an error happen.
@return MAE_RET_BAD_PARAM               If input parameter error. 
*/

MAE_Ret SrvClientDestroyServiceClient( ServiceType_e  eServiceType, SrvClient_t *pClient, s32 *pData );


#endif// __MMI_SRV_CLIENT_H__
/*-----------------------------------------------------*/
