/**
* @file    mmi_srv_vcalparser.h
* @brief   vCalendar parser service wrapper header file
*          
*/

#ifndef __MMI_SRV_VCALPARSER_H__
#define __MMI_SRV_VCALPARSER_H__

#ifdef __CALENDAR_SUPPORT_VCS_MMI__
/*=============================================================*/
// Include files
/*=============================================================*/

#include "mmi_srv_client_commondefine.h"
#include "mmi_vcalparsersrv.h"

/*=============================================================*/
// Type definition of callBack function
/*=============================================================*/

/*=============================================================*/
// Global function definition
/*=============================================================*/

/** SrvVParamInitParamById
@brief  Initialize a IVPARAM object with specified Id.
 
@param[in]      eParamId        param ID
@param[in]      nParamValue     param value

@retval  MAE_RET_SUCCESS        If successful.
@retval  MAE_RET_BAD_PARAM      If input parameter error. 
@retval  MAE_RET_OUT_OF_MEMORY  Memory is not enough to complete the operation.
@retval  MAE_RET_FAILED         If an error occurs.
*/
MAE_Ret SrvVParamInitParamById(VCALParameter_e eParamId, u32 nParamValue);

/** SrvVPropertyAddParam
@brief  Add a IVPARAM object to the given IVPROPERTY object.
 
@param[in]      pIVPARAM        pIVPARAM interface
 
@retval  MAE_RET_SUCCESS        If successful.
@retval  MAE_RET_BAD_PARAM      If input parameter error. 
@retval  MAE_RET_OUT_OF_MEMORY  Memory is not enough to complete the operation.
@retval  MAE_RET_FAILED         If an error occurs.
*/
MAE_Ret SrvVPropertyAddParam(IVPARAM *pIVPARAM);

/** SrvVPropertyGetPropertyId
@brief  Get the property Id.
 
@retval  Property ID
*/
VCALProperty_e SrvVPropertyGetPropertyId(void);

/** SrvVPropertyInitPropertyById
@brief  Initialize a IVPROPERTY object with a given Id.
 
@param[in]      ePropId         Property ID
@param[in]      pPropValue      Property value
@param[in]      nSize           Property size
@param[in]      pGroupName      group name

@retval  MAE_RET_SUCCESS        If successful.
@retval  MAE_RET_BAD_PARAM      If input parameter error or VCALPROPERTY_EXTENDED < nPropId. 
@retval  MAE_RET_OUT_OF_MEMORY  Memory is not enough to complete the operation.
@retval  MAE_RET_FAILED         If an error occurs.
*/
MAE_Ret SrvVPropertyInitPropertyById(VCALProperty_e ePropId, void *pPropValue, u32 nSize, u8 *pGroupName);

/** SrvVPropertyParseValue
@brief  Parse the value of the property into predefined data types.
 
@param[in]      pBuffer         buffer
@param[out]     pSize           size
 
@retval  MAE_RET_SUCCESS        If successful.
@retval  MAE_RET_BAD_PARAM      If input parameter error.
@retval  MAE_RET_OUT_OF_MEMORY  Memory is not enough to complete the operation.
@retval  MAE_RET_NOT_SUPPORTED  The propety is not supported.
@retval  MAE_RET_FAILED         If an error occurs.
*/
MAE_Ret SrvVPropertyParseValue(void *pBuffer, u32 *pSize);

/** SrvVEventAddProperty
@brief  Add a IVPROPERTY object to the IVEVENT object.
 
@param[in]      pIVProperty     pIVProperty
 
@retval  MAE_RET_SUCCESS        If successful.
@retval  MAE_RET_BAD_PARAM      If input parameter error.
@retval  MAE_RET_OUT_OF_MEMORY  Memory is not enough to complete the operation.
@retval  MAE_RET_FAILED         If an error occurs.
*/
MAE_Ret SrvVEventAddProperty(IVPROPERTY *pIVProperty);

/** SrvVEventGetProperty
@brief  Get a IVPROPERTY object corresponding to a property contained in the IVEVENT object.
 
@param[in]      nIndex          index
@param[out]     ppIVPROPERTY    ppIVProperty
 
@retval  MAE_RET_SUCCESS        If successful.
@retval  MAE_RET_BAD_PARAM      If input parameter error.
@retval  MAE_RET_OUT_OF_MEMORY  Memory is not enough to complete the operation.
@retval  MAE_RET_FAILED         If an error occurs.
*/
MAE_Ret SrvVEventGetProperty(u32 nIndex, IVPROPERTY **ppIVPROPERTY);

/** SrvVEventGetPropertyCount
@brief  Get the number of IVPROPERTY objects present in the given IVEVENT object.
 
@retval  property count
*/
s32 SrvVEventGetPropertyCount(void);

/** SrvVCalendarGetBuffer
@brief  Get the buffer for the given IVCALENDAR object.
 
@param[out]     pBuffer         buffer
@param[out]     pSize           size
 
@retval  MAE_RET_SUCCESS        If successful.
@retval  MAE_RET_BAD_PARAM      If input parameter error.
@retval  MAE_RET_OUT_OF_MEMORY  Memory is not enough to complete the operation.
@retval  MAE_RET_FAILED         If an error occurs.
*/
MAE_Ret SrvVCalendarGetBuffer(u8 *pBuffer, u32 *pSize);

/** SrvVCalendarSetBuffer
@brief  Set the buffer for the IVCALENDAR object. This is the buffer which will get parsed.
 
@param[in]      pBuffer         buffer
@param[in]      nSize           size
 
@retval  MAE_RET_SUCCESS        If successful.
@retval  MAE_RET_BAD_PARAM      If input parameter error.
@retval  MAE_RET_OUT_OF_MEMORY  Memory is not enough to complete the operation.
@retval  MAE_RET_NOT_SUPPORTED  If its version is not 1.0.
@retval  MAE_RET_FAILED         If an error occurs.
*/
MAE_Ret SrvVCalendarSetBuffer(u8 *pBuffer, u32 nSize);

/** SrvVCalendarAddEvent
@brief  Add a IVEVENT object to the IVCALENDAR object.
 
@param[in]      pIVEVENT        pIVEVENT
 
@retval  MAE_RET_SUCCESS        If successful.
@retval  MAE_RET_BAD_PARAM      If input parameter error.
@retval  MAE_RET_OUT_OF_MEMORY  Memory is not enough to complete the operation.
@retval  MAE_RET_FAILED         If an error occurs.
*/
MAE_Ret SrvVCalendarAddEvent(IVEVENT *pIVEVENT);

/** SrvVCalendarGetEvent
@brief  Get the IVEVENT object contained in the IVCALENDAR.
 
@param[in]      nIndex          index
@param[out]     ppIVEVENT       pIVEVENT

@retval  MAE_RET_SUCCESS        If successful.
@retval  MAE_RET_BAD_PARAM      If input parameter error.
@retval  MAE_RET_OUT_OF_MEMORY  Memory is not enough to complete the operation.
@retval  MAE_RET_FAILED         If an error occurs. 
*/
MAE_Ret SrvVCalendarGetEvent(u32 nIndex, IVEVENT **ppIVEVENT);

/** SrvVCalendarGetEventCount
@brief  Get the number of IVEVENT present in the given IVCALENDAR.
 
@retval  event count
*/
s32 SrvVCalendarGetEventCount(void);

#endif /* __CALENDAR_SUPPORT_VCS_MMI__ */
#endif /*__MMI_SRV_VCALPARSER_H__*/

