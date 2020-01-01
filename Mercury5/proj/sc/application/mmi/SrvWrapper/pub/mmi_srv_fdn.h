/**
* @file    mmi_srv_fdn.h
* @brief   
*          
*/

#ifndef __MMI_SrvFdnH__
#define __MMI_SrvFdnH__


/*-----------------------------------------------------*/
#include "mmi_srv_client_commondefine.h"
#include "mmi_fdnsrv.h"


/*=============================================================*/
// Callback Function Declaration
/*=============================================================*/

///Note: 
///The cnf data structure May be destroyed after the callback is finished.
///so please make a copy of it if you need it.

typedef void (*SrvFdnSetFDNStatusCB)(void *pThis, Mmi_FDNSrvSetFDNStatusCnf_t *ptCnf);

typedef void (*SrvFdnWriteOneContactCB)(void *pThis, Mmi_FDNSrvWriteOneFDNCnf_t *ptCnf);

typedef void (*SrvFdnDeleteOneContactCB)(void *pThis, Mmi_FDNSrvDeleteOneFDNCnf_t *ptCnf);

/**
SRV_FDN EV and Callback Function descript
@brief  The interface of Service Client is use to set the indicator-callback to CB module

MMI_FDNSRV_Notify_Mask_ContactReady
Group1:SrvFdnContactReadyCB
FDNSRV_EVT_ContactReady
*/

typedef void (* SrvFdnContactReadyCB)(void *pThis);
/** SrvFdnContactReadyCB
@brief  The interface of Service Client is use to set CB to listen the ready

@param[in]      pfnCallBack             CORESRV_EVT_BACKLIGHT_ON_CB Call back function point
*/
void SrvFdnSetContactReadyCB(SrvFdnContactReadyCB pfnCallBack);

/** SrvFdnSetFDNStatusAsync
@brief  The interface of Service Client is used to provide to set FDN status.

@param[in]      ptReq                   Pointer to set FDN status data.(Cannot be null)
@param[in]      pfnCallback             Pointer to callback function

@retval MAE_RET_SUCCESS                 If successful.
@retval MAE_RET_BUSY                    If Fdn Srv is already terminated. 
*/
MAE_Ret SrvFdnSetFDNStatusAsync(Mmi_FDNSrvSetFDNStatusReq_t *ptReq, SrvFdnSetFDNStatusCB pfnCallback);

/** SrvFdnGetFDNNameByNumber
@brief  The interface of Service Client is used to provid to get the name of FDN contact .

@param[in]      ptReq                   Pointer to request data.(Cannot be null. Mallocate/Free by function caller)
@param[out]     ptCnf                   Pointer to the result data.(Cannot be null. Mallocate/Free by function caller)

@retval MAE_RET_SUCCESS                 If successful.
@retval MAE_RET_BUSY                    If Fdn Srv is already terminated. 
@retval MAE_RET_NOT_FOUND               If doesn't find the FDN contact. 
*/
MAE_Ret SrvFdnGetFDNNameByNumber(Mmi_FDNSrvGetFDNNameByNumberReq_t *ptReq, Mmi_FDNSrvGetFDNNameByNumberCnf_t *ptCnf);

/** SrvFdnGetFDNStatusFullInfo
@brief  The interface of Service Client is used to get the FDN status full info of specific SIM.

@param[out]     ptFDNStatus             Pointer to return the FDN status data.
@param[in]      eDualMode               The SIM module id of the request.

@retval MAE_RET_SUCCESS                 If successful.
@retval MAE_RET_BUSY                    If Fdn Srv is already terminated. 
*/
MAE_Ret SrvFdnGetFDNStatusFullInfo(Mmi_FDNSrvFDNStatus_t *ptFDNStatus, MAE_DualMode_t eDualMode);

/** SrvFdnGetFDNContact
@brief  The interface of Service Client is used to get the FDN contact of specific SIM.

@param[out]     ptContact               Pointer to return the FDN contact.
@param[in]      eDualMode               The SIM module id of the request.
@param[in]      nIdx                    The contact index of the request.

@retval MAE_RET_SUCCESS                 If successful.
@retval MAE_RET_BUSY                    If Fdn Srv is already terminated. 
*/
MAE_Ret SrvFdnGetFDNContact(MmiPhbDhFDNBackupData_t *ptContact,
                            MAE_DualMode_t          eDualMode,
                            u8                      nIdx);

/** SrvFdnWriteOneContactAsync
@brief  The interface of Service Client is used to write a FDN contact.

@param[in]      ptReq                   Pointer to set FDN status data.(Cannot be null)
@param[in]      pfnCallback             Pointer to callback function

@retval MAE_RET_SUCCESS                 If successful.
@retval MAE_RET_BUSY                    If Fdn Srv is already terminated. 
*/
MAE_Ret SrvFdnWriteOneContactAsync(Mmi_FDNSrvWriteOneFDNReq_t *ptReq, SrvFdnWriteOneContactCB pfnCallback);

/** SrvFdnDeleteOneContactAsync
@brief  The interface of Service Client is used to delete one FDN contact.

@param[in]      ptReq                   Pointer to set FDN status data.(Cannot be null)
@param[in]      pfnCallback             Pointer to callback function

@retval MAE_RET_SUCCESS                 If successful.
@retval MAE_RET_BUSY                    If Fdn Srv is already terminated. 
*/
MAE_Ret SrvFdnDeleteOneContactAsync(Mmi_FDNSrvDeleteOneFDNReq_t *ptReq, SrvFdnDeleteOneContactCB pfnCallback);

/** SrvFdnIsFDNReady
@brief  The interface of Service Client is used to check the FDN contacts is ready or not.

@retval TRUE                If ready.
@retval FALSE               If not ready. 
*/
boolean SrvFdnIsFDNReady(void);

/** SrvFdnWriteOneNewContactAsync
@brief  The interface of Service Client is used to write a new FDN contact .

@param[in]      ptReq                   Pointer to set FDN status data.(Cannot be null)
@param[in]      pfnCallback             Pointer to callback function

@retval MAE_RET_SUCCESS                 If successful.
@retval MAE_RET_BUSY                    If Fdn Srv is already terminated. 
*/
MAE_Ret SrvFdnWriteOneNewContactAsync(Mmi_FDNSrvWriteOneFDNReq_t *ptReq, SrvFdnWriteOneContactCB pfnCallback);

/** SrvFdnGetFDNStatus
@brief  The interface of Service Client is used to get the FDN status of specific SIM.

@param[in]      eDualMode               The SIM module id of the request.

@retval MMI_FDNSRV_FDN_STATUS_NONE      SIM inactive  
@retval MMI_FDNSRV_FDN_STATUS_WAIT      FDNSrv is busy to get FDN status
@retval MMI_FDNSRV_FDN_STATUS_ACTIVE    FDN active
@retval MMI_FDNSRV_FDN_STATUS_INACTIVE  FDN inactive
*/
__SLDPM_FREE__ MMI_FDNSRV_FDN_STATUS_E SrvFdnGetFDNStatus(MAE_DualMode_t eDualMode);

/*-----------------------------------------------------*/

#endif /* __MMI_SrvFdnH__ */
