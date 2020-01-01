/**
* @file    mmi_srv_ClientTable.h
* @brief   
*          
*
* @author  
* @version $Id: mmi_common_dialog.h 33169 2009-06-12 05:19:42Z collin.chiang $
*/

#ifndef __MMI_SRV_CLIENT_TABLE_H__
#define __MMI_SRV_CLIENT_TABLE_H__

#include "mmi_srv_client_commondefine.h"
#include "mmi_srv_client_platformdefines.h"
#include "mmi_mae_common_def.h"


/*-----------------------------------------------------*/
/*================================================
For AP use Service Event to control Client Table
=================================================*/
//For AP ClientTable.h

//IsRun
void *SrvClientTableGet(void *pData, ServiceType_e eServiceType);
//Set
MAE_Ret SrvClientTableSetData(void *pData, ServiceType_e eServiceType, void *pSrvClient);
//Clear
MAE_Ret SrvClientTableClearData(void *pData, ServiceType_e eServiceType);
//ClearAll
MAE_Ret SrvClientTableClearAllData(void *pData);

/*================================================
For AP use Client Table Generic API
=================================================*/

/**
SrvClientCreateClientTable
@brief  The interface of Client Table is use to Create the client table.

@param[in]      eServiceType            the Service type of client want to create
@param[in]      pSrvClient              the point to the Service client owner's Module
@param[in]      pData                   Point to data if Create Service need init data

@return SrvClient_t*                        Point to a New Service Client. Have afddress vaule If successful. If Null, init have some error
*/
void *SrvClientTableCreateClientTable(u32 size);

//Service Client Table Generic DestroyAPI
/**
SrvClientTableCreateClientTable
@brief  The interface of Client Table is use to Create the client table.

@param[in]      pData                   Point to data if Release Service need data

@return SRVTABLE_RET_SUCCESS            If successful.
@return SRVTABLE_RET_FAILED             If an error happen. 
@return SRVTABLE_RET_BAD_PARAM          If input parameter error. 
*/

MAE_Ret SrvClientTableDestroyClientTable(void *pData);


#endif// __MMI_SRV_CLIENT_TABLE_H__
/*-----------------------------------------------------*/
