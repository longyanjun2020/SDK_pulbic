/**
* @file    mmi_srv_client_priv.h
* @brief   
*          
*
* @author  
* @version $Id: mmi_common_dialog.h 33169 2009-06-12 05:19:42Z collin.chiang $
*/

#ifndef __MMI_SRV_CLIENT_PRIV_H__
#define __MMI_SRV_CLIENT_PRIV_H__

#include "mmi_srv_client_commondefine.h"
#include "mmi_srv_client_platformdefines.h"
#include "mmi_mae_common_def.h"
#include "mmi_mae_log.h"

/*-----------------------------------------------------*/
/*================================================
For Service Wrapper Set/Clear Service Event to call back List Module
=================================================*/
//set
MAE_Ret SrvClientSetCBNode( SrvCBListModule_t *pModule, u32 IndType, void *pfnEvToCB, void *pfnEvCastParaToCB );
//clear
MAE_Ret SrvClientClearCBNode( SrvCBListModule_t *pModule, u32 IndType );
// get extern info for Event CB Node
MAE_Ret SrvClientGetCBNodeExternInfo( SrvCBListModule_t *pModule, u32 IndType, u32 *nInfo );
// set extern info for Event CB Node
MAE_Ret SrvClientSetCBNodeExternInfo( SrvCBListModule_t *pModule, u32 IndType, u32 nInfo );
// find the CB by module
SrvCBNode_t * SrvClientFindCBNode( SrvCBListModule_t *pModule, u32 IndType );
/*================================================
For Service Wrapper Generic Client API Func
=================================================*/
/**
SrvClientCreateClient
@brief  The interface of Service Client is use to get client form AppClient table
        if not find, Create the new service client to task service root.

@param[in]      eSrvType                the Service type of client want to create

@return SrvClient_t*                    Point to a New Service Client. Have afddress vaule If successful. If Null, init have some error
*/
SrvClient_t *SrvClientGetClientFomAP( ServiceType_e eServiceType );

/**
SrvClientCreateClient
@brief  The interface of Service Client is use to Create the service client to task service root.

@param[in]      eSrvAppID               Owner's eSrvAppID.
@param[in]      eSrvType                the Service type of client want to create
@param[in]      pInstance               the point to the Service client owner
@param[in]      pAppCbModule        the point to the Service client owner's CB modeule
@param[in]      nSrvClientFlag      Service client Special Flag             //non used now

@return SrvClient_t*                    Point to a New Service Client. Have afddress vaule If successful. If Null, init have some error
*/
SrvClient_t *SrvClientCreateClient( Srv_AppId_e               eSrvAppID,
                                      ServiceType_e            eSrvtype,
                                      void *pInstance,
                                      SrvCBListModule_t *pAppCbModule,
                                      u32                         nSrvClientFlag );


/** SrvClientDesrotyClient
@brief  The interface of Service Client is use to destory the Accessory service client.

@param[in]      eSrvAppID               Owner eSrvAPPID.
@param[in]      eSrvType                the Service type of client want to create
@param[in]      pClient                 Pointer to the Srv  client.

@return MAE_RET_SUCCESS                 If successful.
@return MAE_RET_FAILED                  If an error happen. 
@return MAE_RET_BAD_PARAM               If input parameter error. 
*/
MAE_Ret SrvClientDesrotyClient( Srv_AppId_e           eSrvAppID, ServiceType_e        eSrvtype, SrvClient_t *pClient );


/**
SrvClientGetSrvClientRootbyTaskID
@brief  The interface of Service Client is use to get the special service ClientRoot in special task.

@param[in]      eSrvAppID           Owner eSrvAPPID.
@param[in]      pInstance           Pointer to the Srv ACCESSORY client Owner.

@return SrvClientRoot_t*            Point to a Service Client Root. Have afddress vaule If successful. If Null, do not find the root
*/
SrvClientRoot_t *SrvClientGetSrvClientRootbyTaskID( Srv_TaskId_e  eSrvTaskID, ServiceType_e   eSrvtype );


/**
SrvClientFindClient
@brief  The interface of Service Client is use to Find the speical clinet is in special task service root or not.

@param[in]      eSrvAppID               Owner eSrvAPPID.
@param[in]      eSrvType                the Service type of the client
@param[in]      pInstance               Pointer to the Service Client.

@return MAE_RET_SUCCESS                 If successful.
@return MAE_RET_FAILED                  If an error happen. 
*/
MAE_Ret SrvClientFindClient( Srv_AppId_e  eSrvAppID, ServiceType_e eSrvtype, SrvClient_t *pClient );

/**
SrvClientIsListenerMaskClear
@brief  The interface of Service Client is use to check the compare mask is clear or not.

@param[in]      pClient                 Pointer to the Srv  client.
@param[in]      nSetMask                Set mask 

@return TRUE            If mask is clear
@return FALSE           If mask is not clear 
*/
boolean SrvClientIsListenerMaskClear( SrvClient_t *pClient, u32               nCompareMask );

/**
SrvClientSetListenerMask
@brief  The interface of Service Client is use to Set the listener mask.

@param[in]      pClient                 Pointer to the Srv  client.
@param[in]      nSetMask                Set mask 

@return MAE_RET_SUCCESS                 If successful.
@return MAE_RET_FAILED                  If an error happen. 
*/
MAE_Ret SrvClientSetListenerMask( SrvClient_t *pClient, u32 nClearMask );

/**
SrvClientClearListenerMask
@brief  The interface of Service Client is use to Clear the listener mask.

@param[in]      pClient             Pointer to the Srv  client.
@param[in]      nClearMask          Clear mask 

@return MAE_RET_SUCCESS             If successful.
@return MAE_RET_FAILED              If an error happen. 
*/
MAE_Ret SrvClientClearListenerMask( SrvClient_t *pClient, u32 nClearMask );

#endif// __MMI_SRV_CLIENT_PRIV_H__
/*-----------------------------------------------------*/
