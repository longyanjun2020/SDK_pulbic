/**
* @file    mmi_srv_phb.h
* @brief
*
*/

#ifndef __MMI_SRV_PHB_H__
#define __MMI_SRV_PHB_H__

/*-----------------------------------------------------*/
#include "mmi_srv_client_commondefine.h"
#include "mmi_phbsrv.h"

typedef void (*SrvPhbQueryPhbStatusCB)(void *pThis,
                                            MmiPhbSrvFunId_e       s32PhbSrvFid,
                                            MmiPhbQueryPhbStatusCnf_t *ptCnf);
typedef void (*SrvPhbReadOneContactBySortingIdxCB)(void *pThis,
                                                        MmiPhbSrvFunId_e       s32PhbSrvFid,
                                                        MmiPhbReadOneContactBySortingIdxCnf_t *ptCnf);
typedef void (*SrvPhbReadOneContactByPhysicalIdxCB)(void *pThis,
                                                         MmiPhbSrvFunId_e       s32PhbSrvFid,
                                                         MmiPhbReadOneContactByPhysicalIdxCnf_t *ptCnf);
typedef void (*SrvPhbWriteOneNewContactCB)(void *pThis,
                                                MmiPhbSrvFunId_e       s32PhbSrvFid,
                                                MmiPhbWriteOneNewContactCnf_t *ptCnf);
typedef void (*SrvPhbWriteOneContactByPhysicalIdxCB)(void *pThis,
                                                          MmiPhbSrvFunId_e       s32PhbSrvFid,
                                                          MmiPhbWriteOneContactByPhysicalIdxCnf_t *ptCnf);
typedef void (*SrvPhbCopyOneContactByPhysicalIdxCB)(void *pThis,
                                                         MmiPhbSrvFunId_e       s32PhbSrvFid,
                                                         MmiPhbCopyOneContactByPhysicalIdxCnf_t *ptCnf);
typedef void (*SrvPhbCopyOneContactBySortingIdxCB)(void *pThis,
                                                        MmiPhbSrvFunId_e       s32PhbSrvFid,
                                                        MmiPhbCopyOneContactBySortingIdxCnf_t *ptCnf);
typedef void (*SrvPhbCopyAllContactCB)(void *pThis,
                                            MmiPhbSrvFunId_e       s32PhbSrvFid,
                                            MmiPhbCopyAllContactCnf_t *ptCnf);
typedef void (*SrvPhbDeleteOneContactByPhysicalIdxCB)(void *pThis,
                                                           MmiPhbSrvFunId_e       s32PhbSrvFid,
                                                           MmiPhbDeleteOneContactByPhysicalIdxCnf_t *ptCnf);
typedef void (*SrvPhbDeleteOneContactBySortingIdxCB)(void *pThis,
                                                          MmiPhbSrvFunId_e       s32PhbSrvFid,
                                                          MmiPhbDeleteOneContactBySortingIdxCnf_t *ptCnf);
typedef void (*SrvPhbDeleteAllContactCB)(void *pThis,
                                              MmiPhbSrvFunId_e       s32PhbSrvFid,
                                              MmiPhbDeleteAllContactCnf_t *ptCnf);
typedef void (*SrvPhbSearchContactByNameCB)(void *pThis,
                                                 MmiPhbSrvFunId_e       s32PhbSrvFid,
                                                 MmiPhbSearchContactByNameCnf_t *ptCnf);
typedef void (*SrvPhbSearchContactByNumberCB)(void *pThis,
												MmiPhbSrvFunId_e       s32PhbSrvFid,
												MmiPhbSearchContactByNumberCnf_t *ptCnf);
typedef void (*SrvPhbPhonebookReady_CB)(void *pThis);
typedef void (*SrvPhbADNMReady_CB)(void *pThis);
typedef void (*SrvPhbADNSReady_CB)(void *pThis);
typedef void (*SrvPhbPhoneFull_CB)(void *pThis);
typedef void (*SrvPhbExportImportContactResult_CB)(void *pThis, u32 ptImportExportReq, boolean bSuccess);


//===============================================================

/** SrvPhbSetPhonebookReadyCB
* @brief  The interface is used to Set CB which will trigger when contacts in phonebook ready.
*
* @param[in]      pfnCnfCB                a call back function which trigger when contacts in phonebook ready
*/
MAE_Ret SrvPhbSetPhonebookReadyCB(SrvPhbPhonebookReady_CB pfnCnfCB);

/** SrvPhbSetADNMReadyCB
* @brief  The interface of Service Client is used to Set CB which will trigger when contacts in ADN_Master  ready.
*
* @param[in]     pfnCnfCB                 Pointer to callback function which trigger when contacts in ADN_Master ready.
*/
MAE_Ret SrvPhbSetADNMReadyCB(SrvPhbADNMReady_CB pfnCnfCB);

/** SrvPhbSetADNSReadyCB
* @brief  The interface of Service Client is used to Set CB which will trigger when contacts in ADN_Slave ready.
*
* @param[in]     pfnCnfCB                 Pointer to callback function which trigger when contacts in ADN_Slave ready.
*/
MAE_Ret SrvPhbSetADNSReadyCB(SrvPhbADNSReady_CB pfnCnfCB);

/** SrvPhbSetPhoneFullCB
* @brief  The interface of Service Client is used to Set CB which will trigger when phone contacts is full
*
* @param[in]     pfnCnfCB                 Pointer to callback function which trigger when phone contacts full
*/
MAE_Ret SrvPhbSetPhoneFullCB(SrvPhbPhoneFull_CB pfnCnfCB);

/** SrvPhbImportExportContactResultAsync
* @brief  The interface of Service Client is used to Set CB which will trigger when import or export contacts finished
*
* @param[in]     pfnCnfCB                 Pointer to callback function which trigger when import or export contacts finished
*/
MAE_Ret SrvPhbExportImportContactResultAsync(SrvPhbExportImportContactResult_CB pfnCnfCB);

//===============================================================================

/** SrvPhbImportContactFromFileAsync
* @brief  The interface of Service Client is used to import the contacts from the file
*
* @param[in]     ptReq                    Pointer to request's parameters.
* @param[in]     pfnCnfCB                 Pointer to callback function which trigger when import contacts finished(bSuccess set True when import contacts success)
*
* @retval MAE_RET_SUCCESS                 Successful.
*/
MAE_Ret SrvPhbImportContactFromFileAsync(MmiPhbSrvImportReq_t *ptReq,
										 SrvPhbExportImportContactResult_CB pfnCnfCB);

/** SrvPhbExportContactToFileAsync
* @brief  The interface of Service Client is used to export the contacts to the file
*
* @param[in]      ptReq                   Pointer to request's parameters.
* @param[in]      bIsFull                 the memory is full or not
* @param[in]      pfnCnfCB                Pointer to callback function which trigger when export contacts finished(bSuccess set True when export contacts success)
*
* @retval MAE_RET_SUCCESS                 Successful.
*/
MAE_Ret SrvPhbExportContactToFileAsync(MmiPhbSrvExportReq_t *ptReq,
                                       boolean bIsFull,
                                       SrvPhbExportImportContactResult_CB pfnCnfCB);

//========================================================================

/** SrvPhbIsPhonebookReady
* @brief  The interface of Service Client is used to check phonebook service is ready or not.
*
* @retval boolean           ready or not.
*/
__SLDPM_FREE__ boolean SrvPhbIsPhonebookReady(void);

/** SrvPhbQueryPhbStatusAsync
* @brief  The interface of Service Client is used to query status of phonebook service.
*
* @param[in]      ptReq                   Pointer to request's parameters.
*     u32PhbCheckValue                    An unique number which get from SrvPhbGetCheckValue
*     s32PhbBookType                      User want to query ADN(SIM) or ADR(PHONE)
*     s32PhbGroup                         Which group the user wants to query
* @param[in]     pfnCallback              Pointer to callback function which trigger when get phb status
*
* @retval MAE_RET_SUCCESS                 Successful.
* @retval MAE_RET_BUSY                    Phonebook service is busy or not ready.
*/
MAE_Ret SrvPhbQueryPhbStatusAsync(MmiPhbQueryPhbStatusReq_t *ptReq, SrvPhbQueryPhbStatusCB   pfnCallback);

/** SrvPhbReadOneContactBySortingIdxAsync
* @brief  The interface of Service Client is used to read contact by sorting index.
*
* @param[in]      ptReq                   Pointer to request's parameters.
*     u32PhbCheckValue                    A unique number which get from SrvPhbGetCheckValue
*     s32PhbBookType                      User want to read the contact in ADN(SIM) or ADR(PHONE)
*     u16PhbSortingIdx                    The sorting index of the contact
*     s32PhbGroup                         Which group the user want to read
* @param[in]     pfnCallback              Pointer to callback function which trigger after read contact by sorting index
*
* @retval MAE_RET_SUCCESS                 Successful.
* @retval MAE_RET_BUSY                    Phonebook service is busy or not ready.
*/
__SLDPM_FREE__ MAE_Ret SrvPhbReadOneContactBySortingIdxAsync(MmiPhbReadOneContactBySortingIdxReq_t *ptReq,
                                              SrvPhbReadOneContactBySortingIdxCB   pfnCallback);

/** SrvPhbReadOneContactByPhysicalIdxAsync
* @brief  The interface of Service Client is used to read contact by physical index.
*
* @param[in]      ptReq                   Pointer to request's parameters.
*     u32PhbCheckValue                    A unique number which get from SrvPhbGetCheckValue
*     s32PhbBookType                      User want to read the contact in ADN(SIM) or ADR(PHONE)
*     u16PhbPhysicalIdx                   The physical index of the contact
* @param[in]     pfnCallback              Pointer to callback function which trigger after read contact by physical index.
*
* @retval MAE_RET_SUCCESS                 Successful.
* @retval MAE_RET_BUSY                    Phonebook service is busy or not ready.
*/
MAE_Ret SrvPhbReadOneContactByPhysicalIdxAsync(MmiPhbReadOneContactByPhysicalIdxReq_t *ptReq,
                                               SrvPhbReadOneContactByPhysicalIdxCB   pfnCallback);

/** SrvPhbWriteOneNewContactAsync
* @brief  The interface of Service Client is used to write one new contact.
*
* @param[in]      ptReq                   Pointer to request's parameters.
*     u32PhbCheckValue                    A unique number which get from SrvPhbGetCheckValue
*     s32PhbBookType                      User want to write the contact to ADN(SIM) or ADR(PHONE)
*     tPhbContactContent                  The content which be written
* @param[in]     pfnCallback              Pointer to callback function which trigger after write one new contact.
*
* @retval MAE_RET_SUCCESS                 Successful.
* @retval MAE_RET_BUSY                    Phonebook service is busy or not ready.
*/
__SLDPM_FREE__ MAE_Ret SrvPhbWriteOneNewContactAsync(MmiPhbWriteOneNewContactReq_t *ptReq,
                                      SrvPhbWriteOneNewContactCB    pfnCallback);

/** SrvPhbWriteOneContactByPhysicalIdxAsync
* @brief  The interface of Service Client is used to write contact by physical index.
*
* @param[in]      ptReq                   Pointer to request's parameters.
*     u32PhbCheckValue                    A unique number which get from SrvPhbGetCheckValue
*     s32PhbBookType                      User want to write the contact to ADN(SIM) or ADR(PHONE)
*     tPhbContactContent                  The content which be written
*     u16PhbPhysicalIdx                   The physical index of the written contact
* @param[in]     pfnCallback              Pointer to callback function which trigger after write one new contact by physical index.
*
* @retval MAE_RET_SUCCESS                 Successful.
* @retval MAE_RET_BUSY                    Phonebook service is busy or not ready.
*/
MAE_Ret SrvPhbWriteOneContactByPhysicalIdxAsync(MmiPhbWriteOneContactByPhysicalIdxReq_t *ptReq,
                                                SrvPhbWriteOneContactByPhysicalIdxCB pfnCallback);

/** SrvPhbCopyOneContactByPhysicalIdxAsync
* @brief  The interface of Service Client is used to copy contact by physical index.
*
* @param[in]      ptReq                   Pointer to request's parameters.
*     u32PhbCheckValue                    A unique number which get from SrvPhbGetCheckValue
*     s32PhbBookType_Source               Which source (ADN(SIM) or ADR(PHONE)) the user want to copy from
*     s32PhbBookType_Destination          Which destination (ADN(SIM) or ADR(PHONE)) the user want to copy to
*     u16PhbPhysicalIdx_Source            The physical index of the source contact
* @param[in]     pfnCallback              Pointer to callback function which trigger after copy one contact by physical index.
*
* @retval MAE_RET_SUCCESS                 Successful.
* @retval MAE_RET_BUSY                    Phonebook service is busy or not ready.
*/
MAE_Ret SrvPhbCopyOneContactByPhysicalIdxAsync(MmiPhbCopyOneContactByPhysicalIdxReq_t   *ptReq,
                                               SrvPhbCopyOneContactByPhysicalIdxCB      pfnCallback);

/** SrvPhbCopyOneContactBySortingIdxAsync
* @brief  The interface of Service Client is used to copy a contact by sorting index.
*
* @param[in]      ptReq                   Pointer to request's parameters.
*     u32PhbCheckValue                    A unique number which get from SrvPhbGetCheckValue
*     s32PhbBookType_Source               Which source (ADN(SIM) or ADR(PHONE)) the user want to copy from
*     s32PhbBookType_Destination          Which destination (ADN(SIM) or ADR(PHONE)) the user want to copy to
*     u16PhbSortingIdx_Source             The sorting index of the source contact
* @param[in]     pfnCallback              Pointer to callback function which trigger after copy a contact by sorting index
*
* @retval MAE_RET_SUCCESS                 Successful.
* @retval MAE_RET_BUSY                    Phonebook service is busy or not ready.
*/
MAE_Ret SrvPhbCopyOneContactBySortingIdxAsync(MmiPhbCopyOneContactBySortingIdxReq_t *ptReq,
                                              SrvPhbCopyOneContactBySortingIdxCB    pfnCallback);

/** SrvPhbCopyAllContactAsync
* @brief  The interface of Service Client is used to copy all contacts
*
* @param[in]      ptReq                   Pointer to request's parameters.
*     u32PhbCheckValue                    A unique number which get from SrvPhbGetCheckValue
*     s32PhbBookType_Source               Which source (ADN(SIM) or ADR(PHONE)) the user want to copy from
*     s32PhbBookType_Destination          Which destination (ADN(SIM) or ADR(PHONE)) the user want to copy to
* @param[in]     pfnCallback              Pointer to callback function which trigger after copied the all caontacts
*
* @retval MAE_RET_SUCCESS                 Successful.
* @retval MAE_RET_BUSY                    Phonebook service is busy or not ready.
*/
MAE_Ret SrvPhbCopyAllContactAsync(MmiPhbCopyAllContactReq_t *ptReq, SrvPhbCopyAllContactCB pfnCallback);

/** SrvPhbDeleteOneContactByPhysicalIdxAsync
* @brief  The interface of Service Client is used to delete contact by physical index.
*
* @param[in]      ptReq                   Pointer to request's parameters.
*     u32PhbCheckValue                    A unique number which get from SrvPhbGetCheckValue
*     s32PhbBookType                      User want to delete the contact from ADN(SIM) or ADR(PHONE)
*     u16PhbPhysicalIdx                   The physical index of the deleted contact
* @param[in]     pfnCallback              Pointer to callback function which trigger when delete contact by physical index.
*
* @retval MAE_RET_SUCCESS                 Successful.
* @retval MAE_RET_BUSY                    Phonebook service is busy or not ready.
*/
MAE_Ret SrvPhbDeleteOneContactByPhysicalIdxAsync(MmiPhbDeleteOneContactByPhysicalIdxReq_t *ptReq,
                                                 SrvPhbDeleteOneContactByPhysicalIdxCB pfnCallback);

/** SrvPhbDeleteOneContactBySortingIdxAsync
* @brief  The interface of Service Client is used to delete one contact by sorting index.
*
* @param[in]      ptReq                   Pointer to request's parameters.
*     u32PhbCheckValue                    A unique number which get from SrvPhbGetCheckValue
*     s32PhbBookType                      User want to delete the contact from ADN(SIM) or ADR(PHONE)
*     u16PhbSortingIdx                    The sorting index of the deleted contact
*     s32PhbGroup                         The user want to delete contact in which group
* @param[in]     pfnCallback              Pointer to callback function which trigger when delete contact by sorting index
*
* @retval MAE_RET_SUCCESS                 Successful.
* @retval MAE_RET_BUSY                    Phonebook service is busy or not ready.
*/
MAE_Ret SrvPhbDeleteOneContactBySortingIdxAsync(MmiPhbDeleteOneContactBySortingIdxReq_t *ptReq,
                                                SrvPhbDeleteOneContactBySortingIdxCB pfnCallback);

/** SrvPhbDeleteAllContactAsync
* @brief  The interface of Service Client is used to delete all contacts
*
* @param[in]      ptReq                   Pointer to request's parameters.
*     u32PhbCheckValue                    A unique number which get from SrvPhbGetCheckValue
*     s32PhbBookType                      User want to delete the contacts from ADN(SIM) or ADR(PHONE)
* @param[in]     pfnCallback              Pointer to callback function which trigger when delete all contacts
*
* @retval MAE_RET_SUCCESS                 Successful.
* @retval MAE_RET_BUSY                    Phonebook service is busy or not ready.
*/
MAE_Ret SrvPhbDeleteAllContactAsync(MmiPhbDeleteAllContactReq_t *ptReq, SrvPhbDeleteAllContactCB pfnCallback);

/** SrvPhbSuspendExportImportContact
* @brief  The interface of Service Client is used to suspend the importing, exporting
*
* @retval MAE_RET_SUCCESS           Successful.
*/
MAE_Ret SrvPhbSuspendExportImportContact(void);

/** SrvPhbResumeExportImportContact
* @brief  The interface of Service Client is used to resume the importing, exporting
*
* @retval MAE_RET_SUCCESS           Successful.
* @retval MAE_RET_NOT_READY         current status is not MMI_PHB_EXPORT_IMPORT_SUSPEND.
*/
MAE_Ret SrvPhbResumeExportImportContact(void);

/** SrvPhbStopExportImportContact
* @brief  The interface of Service Client is used to stop the importing, exporting
*
* @retval MAE_RET_SUCCESS           Successful.
* @retval MAE_RET_NOT_READY         current status is MMI_PHB_EXPORT_IMPORT_NONE.
*/
MAE_Ret SrvPhbStopExportImportContact(void);

/** SrvPhbSearchContactByNameAsync
* @brief  The interface of Service Client is used to search the contact by the name.
*
* @param[in]     ptReq                    Pointer to request's parameters.
*     u32PhbCheckValue                    A unique number which get from SrvPhbGetCheckValue
*     s32PhbBookType                      User want to search the contact from ADN(SIM) or ADR(PHONE)
*     tPhbSearchName                      The query name
* @param[in]     pfnCallback              Pointer to callback function which trigger after search the contact by the name.
*
* @retval MAE_RET_SUCCESS                 Successful.
* @retval MAE_RET_BUSY                    Phonebook service is busy or not ready.
*/
MAE_Ret SrvPhbSearchContactByNameAsync(MmiPhbSearchContactByNameReq_t *ptReq,
                                       SrvPhbSearchContactByNameCB pfnCallback);

/** SrvPhbSearchContactByName
* @brief  The interface of Service Client is used to search the contact by the name.
*
* @param[in]     ePhbBookType             Book type of change mode.ADN(SIM), ADR(PHONEBOOK) and ADN_ADR
* @param[in]     u8NameLen				  The length of name
* @param[in]     pu8NameStr               The name which wants to search
* @param[out]     pu16SortingIdx           Pointer to sorting index
*
* @retval MAE_RET_SUCCESS                 Successful.
* @retval MAE_RET_BUSY                    Phonebook service is busy or not ready.
*/
MAE_Ret SrvPhbSearchContactByName(MmiPhbBookType_e  s32PhbBookType,
                                                              const u8            u8NameLen,
                                                              const u8 *pu8NameStr,
                                                              u16 *pu16SortingIdx );
/** SrvPhbSearchContactByNumberAsync
* @brief  The interface of Service Client is used to search the contact by the number.
*
* @param[in]     ptReq                    Pointer to request's parameters.
*     u32PhbCheckValue                    A unique number which get from SrvPhbGetCheckValue
*     s32PhbBookType                      User want to search the contact from ADN(SIM) or ADR(PHONE)
*     tPhbSearchNumber                    The query number
* @param[in]     pfnCallback              Pointer to callback function which trigger after search the contact by the name.
*
* @retval MAE_RET_SUCCESS                 Successful.
* @retval MAE_RET_BUSY                    Phonebook service is busy or not ready.
*/
MAE_Ret SrvPhbSearchContactByNumberAsync(MmiPhbSearchContactByNumberReq_t *ptReq,
                                         SrvPhbSearchContactByNumberCB pfnCallback);

/** SrvPhbSearchContactByNumber
* @brief  The interface of Service Client is used to search contact by number.
*
* @param[in]     ptReq                    Pointer to request's parameters.
*     u32PhbCheckValue                    A unique number which get from SrvPhbGetCheckValue
*     s32PhbBookType                      User want to search the contact from ADN(SIM) or ADR(PHONE)
*     tPhbSearchNumber                    The query number
* @param[out]    ptCnf					  Pointer to the result contact's content
*
* @retval MAE_RET_SUCCESS                 Successful.
* @retval MAE_RET_BUSY                    Phonebook service is busy or not ready.
* @retval MAE_RET_NOT_FOUND               If the length of number is 0
*/
MAE_Ret SrvPhbSearchContactByNumber(MmiPhbSearchContactByNumberReq_t *ptReq,
							        MmiPhbSearchContactByNumberCnf_t *ptCnf);

/** SrvPhbSearchContactFieldByNumber
* @brief  The interface of Service Client is used to search contact fields by number.
*
* @param[in]     ptReq                    Pointer to request's parameters.
*     u32PhbCheckValue                    A unique number which get from SrvPhbGetCheckValue
*     s32PhbBookType                      User want to search the contact from ADN(SIM) or ADR(PHONE)
*     tPhbSearchNumber                    The query number
* @param[out]    ptCnf					  Pointer to the result contact's content
*
* @retval MAE_RET_SUCCESS                 Successful.
* @retval MAE_RET_BUSY                    Phonebook service is busy or not ready.
* @retval MAE_RET_NOT_FOUND               If the length of number is 0
*/

MAE_Ret SrvPhbSearchContactFieldByNumber(PHBContactFieldMask_e eMask,
                                    MmiPhbSearchContactByNumberReq_t *ptReq,
                                    MmiPhbSearchContactByNumberCnf_t *ptCnf);

/** SrvPhbSearchContactByEmail
* @brief  The interface of Service Client is used to search contact by email.
*
* @param[in]      ptEmail                 Pointer to the email address.
* @param[out]     ptOutContact            Pointer to the contact's which in search result content.
*
* @retval MAE_RET_SUCCESS                 Successful.
* @retval MAE_RET_BUSY                    Phonebook service is busy or not ready.
*/
MAE_Ret SrvPhbSearchContactByEmail(const MmiPhbEmail_t *ptEmail, MmiPhbContactContent_t *ptOutContact);

/** SrvPhbStartPhonebookInit
* @brief  The interface of Service Client is used to start phonebook init.
*
* @param[in]      ePhbBookType            Book type of start initialize.
* @param[in]      bIsRefresh              Is need refresh sorting table or not.
*/
void SrvPhbStartPhonebookInit(MmiPhbBookType_e     ePhbBookType, boolean                 bIsRefresh);

/** SrvPhbStopPhonebookInit
* @brief  The interface of Service Client is used to stop phonebook init.
*
* @param[in]      ePhbBookType            Book type of stop initialize.
*/
void SrvPhbStopPhonebookInit(MmiPhbBookType_e     ePhbBookType);


MAE_Ret SrvPhbStartAutoWriteBKSortingTable(boolean bIsBK,boolean bIsWriteNow);


/** SrvPhbStartAutoWriteSortingTable
* @brief  The interface of Service Client is used to start auto write sorting table.
*
* @param[in]      bIsWriteNow             Is need write sorting table right now or not.
*
* @retval MAE_RET_SUCCESS                 Successful.
* @retval MAE_RET_BUSY                    Phonebook service is busy or not ready.
*/

MAE_Ret SrvPhbStartAutoWriteSortingTable(boolean bIsWriteNow);


/** SrvPhbStopAutoWriteSortingTable
* @brief  The interface of Service Client is used to stop auto write sorting table.
*
* @retval MAE_RET_SUCCESS                 Successful.
* @retval MAE_RET_BUSY                    Phonebook service is busy or not ready.
*/

MAE_Ret SrvPhbStopAutoWriteSortingTable(void);

/** SrvPhbIsInGroup
* @brief  The interface of Service Client is used to check the contact is in this group or not.
*
* @param[in]      ePhbGroup               Group that want to check.
* @param[in]      pcontactContent         The contact to be checked
* @param[out]     ptGroupContent          Pointer to the group content if it is in group, alloc/free by caller.
*
* @retval boolean is in group or not.
*/
boolean SrvPhbIsInGroup(MmiPhbGroup_e         ePhbGroup,
                        MmiPhbContactContent_t *pcontactContent,
                        MmiPhbGroupContent_t *ptGroupContent);

/** SrvPhbSetOneContactToGroup
* @brief  The interface of Service Client is used to set one contact to group.
*
* @param[in]    contactContent         The contact to be set.
* @param[in]    s32PhbGroup           The group which contact set to.
*
*/
void SrvPhbSetOneContactToGroup(MmiPhbContactContent_t *contactContent,
	    			  		    MmiPhbGroup_e  s32PhbGroup);

/** SrvPhbRemoveOneContactFromGroup
* @brief  The interface of Service Client is used to remove the contact from the group.
*
* @param[in]    contactContent         The contact to be removed.
* @param[in]    s32PhbGroup           The group which contact removed from.
*
*/
void SrvPhbRemoveOneContactFromGroup(MmiPhbContactContent_t *contactContent,
	   							     MmiPhbGroup_e  s32PhbGroup);

/** SrvPhbChangeModeNotify
* @brief  The interface of Service Client is used to notify phonebook service when mode changes.
*
* @param[in]      ePhbBookType            Book type of change mode.
*/
void SrvPhbChangeModeNotify(MmiPhbBookType_e ePhbBookType);

/** SrvPhbCopyAllSIMContact
* @brief  The interface of Service Client is used to copy all SIM contacts to phone.
*
* @param[in]      ePhbBookType            Copy from ADN_M(SIM1) or ADN_S(SIM2)
*/
void SrvPhbCopyAllSIMContact(MmiPhbBookType_e ePhbBookType);

/** SrvPhbRebuild
* @brief  The interface of Service Client is used to request phonebook service to rebuild sorting table.
*/
void SrvPhbRebuild(void);

/** SrvPhbGetPartialPhbStatus
* @brief  The interface of Service Client is used to get the max number of contacts,the used number of contacts,the max length of names,and the max length of numbers
*
* @param[in]      ePhbBookType            Book type of change mode.
* @param[in]      ePhbGroup               Group of contact.
* @param[out]     pMaxContacts            Pointer to the result with the max number of contacts
* @param[out]     pUsedContacts           Pointer to the result with the used number of contacts
* @param[out]     pnMaxNameLen            Pointer to the result with the max length of names
* @param[out]     pnMaxNumberLen          Pointer to the result with the max length of numbers
*/
void SrvPhbGetPartialPhbStatus(MmiPhbBookType_e ePhbBookType,
                               MmiPhbGroup_e ePhbGroup,
                               u16 *pMaxContacts,
                               u16 *pUsedContacts,
                               u8 *pnMaxNameLen,
                               u8 *pnMaxNumberLen);

#ifdef __3G_RIL_MMI__
/** SrvPhbGetPartialPhbStatusEx
* @brief  The interface of Service Client is used to get the max number of contacts,the used number of contacts,the max length of names,the max length of numbers, and the max length of email
*
* @param[in]      ePhbBookType            Book type of change mode.
* @param[in]      ePhbGroup               Group of contact.
* @param[out]     pMaxContacts            Pointer to the result with the max number of contacts
* @param[out]     pUsedContacts           Pointer to the result with the used number of contacts
* @param[out]     pnMaxNameLen            Pointer to the result with the max length of names
* @param[out]     pnMaxNumberLen          Pointer to the result with the max length of numbers
* @param[out]     pnMaxNumberLen          Pointer to the result with the max length of email
*/
void SrvPhbGetPartialPhbStatusEx(MmiPhbBookType_e ePhbBookType,
                               MmiPhbGroup_e ePhbGroup,
                               u16 *pMaxContacts,
                               u16 *pUsedContacts,
                               u8 *pnMaxNameLen,
                               u8 *pnMaxNumberLen,
                               u8 *pnMaxMailLen);
#endif //__3G_RIL_MMI__

/** SrvPhbQueryPhbStatus
* @brief  The interface of Service Client is used to Query phb status.
*
* @param[in]      ptReq                   Pointer to request's parameters.
* @param[out]     ptCnf                   Pointer to the contact's information.
*
* @retval MAE_RET_SUCCESS                 Successful.
* @retval MAE_RET_BUSY                    Phonebook service is busy or not ready.
*/
MAE_Ret SrvPhbQueryPhbStatus(MmiPhbQueryPhbStatusReq_t *ptReq, MmiPhbQueryPhbStatusCnf_t *ptCnf);

/** SrvPhbReadOneContactByPhysicalIdx
* @brief  The interface of Service Client is used to read one contact by the physical index.
*
* @param[in]      ptReq                   Pointer to request's parameters.
* @param[in]      bIsNeedFullContent      Set "TRUE" if need image index and ring index
* @param[out]     ptCnf                   Pointer to the contact's information.
*
* @retval MAE_RET_SUCCESS           Successful.
* @retval MAE_RET_NOT_FOUND         Not found.
*/
MAE_Ret SrvPhbReadOneContactByPhysicalIdx(MmiPhbReadOneContactByPhysicalIdxReq_t *ptReq,
                                          MmiPhbReadOneContactByPhysicalIdxCnf_t *ptCnf,
                                          boolean                                 bIsNeedFullContent);

/** SrvPhbReadOneContactPartialBySortingIdx
* @brief  The interface of Service Client is used to read one contact by the sorting index.
*
* @param[in]      ptReq                   Pointer to request's parameters.
* @param[out]     ptCnf                   Pointer to the result with the contact's information
*
* @retval MAE_RET_SUCCESS                 Successful.
*/
MAE_Ret SrvPhbReadOneContactPartialBySortingIdx(MmiPhbReadPartialBySortingIdxReq_t *ptReq,
                                                MmiPhbReadPartialBySortingIdxCnf_t *ptCnf);

/** SrvPhbConvertToPhysicalIdx
* @brief  The interface of Service Client is used to convert sorting index to physical index.
*
* @param[in]      ePhbBookType            Book type of contact.
* @param[in]      ePhbGroup               Group of contact.
* @param[in]      nPhbSortingIdx          Sorting index of contact.
* @param[out]     pnPhbPhysicalIdx        qPointer to the physical index of contact.
*
* @retval MAE_RET_SUCCESS                 Successful.
* @retval MAE_RET_FAILED                  Fail.
*/
MAE_Ret SrvPhbConvertToPhysicalIdx(MmiPhbBookType_e   ePhbBookType,
                                   MmiPhbGroup_e       ePhbGroup,
                                   u16                   nPhbSortingIdx,
                                   u16                   *pnPhbPhysicalIdx);

/** SrvPhbConvertToSortingIdx
* @brief  The interface of Service Client is used to convert physical index to sorting index.
*
* @param[in]      ePhbBookType            Book type of contact.
* @param[in]      ePhbGroup               Group of contact.
* @param[in]      nPhbPhysicalIdx         Physical index of contact.
* @param[out]     pnPhbSortingIdx         Pointer to the sorting index of contact.
*
* @retval MAE_RET_SUCCESS                 Successful.
* @retval MAE_RET_FAILED                  Fail.
* @retval MAE_RET_NOT_FOUND               Not found.
*/
MAE_Ret SrvPhbConvertToSortingIdx(MmiPhbBookType_e   ePhbBookType,
                                  MmiPhbGroup_e       ePhbGroup,
                                  u16                   nPhbPhysicalIdx,
                                  u16 *pnPhbSortingIdx);

/** SrvPhbGetContactsInGroupStatusArray
* @brief  The interface of Service Client is used to get check status of phonebook service for mark mode.
*
* @param[in]      ePhbBookType            Book type of contact.
* @param[in]      ePhbGroup               Group of contact.
* @param[out]     pbSrvCheckStatus        Check status of phonebook service for mark mode.
*
* @retval MAE_RET_SUCCESS                 Successful.
* @retval MAE_RET_BAD_PARAM               If ePhbBookType is not MMI_PHB_BOOK_TYPE_ADR.
*/
MAE_Ret SrvPhbGetContactsInGroupStatusArray(MmiPhbBookType_e     ePhbBookType,
                                            MmiPhbGroup_e         ePhbGroup,
                                            boolean *pbSrvCheckStatus);

/** SrvPhbUpdateOneContactGroupByPhysicalIdx
* @brief  The interface of Service Client is used to update one contact's group.
*
* @param[in]      nPhbPhysicalIdx         Physical index of contact.
* @param[in]      ePhbGroup               Group of contact.
* @param[in]      bIsAdd                  Is add to this group or remove.
*
* @retval MAE_RET_SUCCESS                 Successful.
* @retval MAE_RET_FAILED                  Fail.
*/
MAE_Ret SrvPhbUpdateOneContactGroupByPhysicalIdx(u16                 nPhbPhysicalIdx,
                                                 MmiPhbGroup_e     ePhbGroup,
                                                 boolean             bIsAdd);

/** SrvPhbGetBJXTable
* @brief  The interface of Service Client is used to get BJX table.
*
* @param[in]      ePhbBookType            Book type of contact.
* @param[in]      ePhbGroup               Group type of contact.
*
* @retval       Pointer to the BJX table.
*/
MmiPhbBJX_t * SrvPhbGetBJXTable(MmiPhbBookType_e ePhbBookType, MmiPhbGroup_e ePhbGroup);

/** SrvPhbSetRecoveryFlag
* @brief  The interface of Service Client is used to set recovery flag.
*         This flag is use to check if the sorting table has be write back to RAI successfully.
*         If not, we need rebuild sorting table at next power on.
*
* @param[in]     eRecoveryFlag            Recovery flag of sorting table.
*/
void SrvPhbSetRecoveryFlag(MMI_PHB_Recovery_Flag_e eRecoveryFlag);

/** SrvPhbOpenSortingTable
* @brief  The API is used to keep the sorting table from being freed during some long-span operation.
*             The API needs to be paired with the SrvPhbCloseSortingTable API.
* 
* 
*/
__SLDPM_FREE__ void SrvPhbOpenSortingTable(void);

/** SrvPhbCloseSortingTable
* @brief  The API is used to let phbsrv know the sorting table can be freed when no other clients are locking it.
*             The API needs to be paired with the SrvPhbOpenSortingTable API.
* 
*/
void SrvPhbCloseSortingTable(void);

/** SrvPhbGetNextExistedIdx
* @brief  The interface of Service Client is used to get next index of exist contact.
*
* @param[in]      ePhbBookType            Book type of contact.
* @param[in]      nCurrentIdx             Current physical index.
*
* @retval         Next index of exist contact.
*/
u16 SrvPhbGetNextExistedIdx(MmiPhbBookType_e ePhbBookType, u16 nCurrentIdx);

/** SrvPhbGetModifySerialNo
* @brief  The interface of Service Client is used to get modify serial number.
*         This number is use to check the data that caller got is newest or not.
*
*         Example:
*             1. AP get modify serial number and store it when AP be interrupt.
*             2. When AP resume, get modify serial number again.
*             3. Then AP check modify serial number is change or not.
*
* @retval  Current modify serial number.
*/
__SLDPM_FREE__ u16 SrvPhbGetModifySerialNo(void);

/** SrvPhbMultiWordPrefixSearch
* @brief  The interface of Service Client is used to search contact by multiple word prefix.
*         [Note]The data will alloc and copy to ppatSearchResult; Remember to Free ppatSearchResult by AP self
*
* @param[in]      ePhbBookType            Book type of contact.
* @param[in]      ePhbGroup               Group of contact.
* @param[in]      pwcSearchStr            Search string.
* @param[out]     ppatSearchResult        Result of search.
*
*                 *ppatSearchResult is NULL for the first time search.
*                 The function will MALLOC memory to store result and return it to the caller AP.
*                 AP need use it as parameter when second (and more) time search.
*
* @param[out]     pnSearchResultTotal   Total of search.
*
* @retval MAE_RET_SUCCESS                 Successful.
*/
MAE_Ret SrvPhbMultiWordPrefixSearch(MmiPhbBookType_e     ePhbBookType,
                                    MmiPhbGroup_e         ePhbGroup,
                                    MAE_WChar *pwcSearchStr,
                                    MmiPhbSearchResult_t **ppatSearchResult,
                                    u16 *pnSearchResultTotal,
                                    MMI_PHB_SEARCH_TYPE_E eSearchType);

#ifndef __SMALL_PHB_MMI__
/** SrvPhbSearchContactsByField
* @brief  The interface of Service Client is used to search by filed, such as email, url...etc.
*         [Note]The data will alloc and copy to ppatSearchResult; Remember to Free ppatSearchResult by AP self
*
* @param[in]      eSearch_Data            Search field.
* @param[out]     ppatSearchResult        Result of search.
* @param[out]     pnSearchResultTotal     Total of search.
*
* @retval MAE_RET_SUCCESS                 Successful.
*/
MAE_Ret SrvPhbSearchContactsByField(MmiPhbContactItemDataID_e   eSearch_Data,
                                    MmiPhbSearchResult_t **ppatSearchResult,
                                    u16 *pnSearchResultTotal);
#endif

/**SrvPhbFuzzySearchContactsByNumber
* @brief:  Search the PhbBook contacts by number
* @param[in]  s32PhbBookType    Search record by the phone book type
* @param[in]  s32PhbGroup       Search record in the phone book group
* @param[in]  pwcSearchStr      Pointer to the search string
* @param[in]  pIVCalllog        Pointer to the vector class (the vector class stroe call log search result)
* @param[out] ppatSearchResult  Pointer to the search result by phone book
* @param[out] pu16SearchResultTotal  Pointer to the search result items number
* @return     MMI_PHB_RESULT_OK     if successful
*/
MAE_Ret SrvPhbFuzzySearchContactsByNumber( MmiPhbBookType_e		                    s32PhbBookType,
                    										 MmiPhbGroup_e            s32PhbGroup,
                    										 MAE_WChar                  *pwcSearchStr,
                    										 VectorClass_t               *pIVCalllog,
                    										 MmiPhbSearchResultForNum_t **ppatSearchResult,
                    										 u16                        *pu16SearchResultTotal);
//===============================================================

/** SrvPhbWriteBlackListNew
* @brief  The interface of Service Client is used to write one new black list member.
*
* @param[in]      ptPhbContactContent    Pointer to the contact's content.
* @param[out]     pnIdx                  Pointer to the physical index of new black list member.

* @retval MAE_RET_SUCCESS                 Successful.
* @retval MAE_RET_FAILED                  Fail.
*/
MAE_Ret SrvPhbWriteBlackListNew(MmiPhbBlackListMemberContent_t *ptPhbContactContent, u16 *pnIdx);


/** SrvPhbWriteBlackListNewFromPhysicalIdx
* @brief  The interface of Service Client is used to write one new black list member
*         by copying the contact by a physical Idx.
*
* @param[in]      u16PhbPhysicalIdx      The physical Idx of the contact's content.
* @param[out]     pnIdx                  Pointer to the physical index of new black list member.
*
* @retval MAE_RET_SUCCESS                 Successful.
* @retval MAE_RET_FAILED                  Fail.
* @retval MAE_RET_NOT_FOUND               Not found.
*/
MAE_Ret SrvPhbWriteBlackListNewFromPhysicalIdx(u16 u16PhbPhysicalIdx, u16 *pnIdx);

/** SrvPhbWriteBlackListBySortingIdx
* @brief  The interface of Service Client is used to write black list member by sorting index.
*
* @param[in]      ptPhbContactContent     Pointer to the contact's content.
* @param[in]      nPhBlackListRaiIdx      Sorting index of contact.
*
* @retval MAE_RET_SUCCESS                 Successful.
* @retval MAE_RET_FAILED                  Fail.
*/
MAE_Ret SrvPhbWriteBlackListBySortingIdx(MmiPhbBlackListMemberContent_t *ptPhbContactContent,
                                         u16                             nPhBlackListRaiIdx);

/** SrvPhbReadBlackListBySortingIdx
* @brief  The interface of Service Client is used to read black list member by sorting index.
*
* @param[in]      ptReq                   Pointer to the sorting number
* @param[out]     ptCnf                   Pointer to the contact's content.
*
* @retval MAE_RET_SUCCESS                 Successful.
* @retval MAE_RET_NOT_FOUND               Not found.
*/
MAE_Ret SrvPhbReadBlackListBySortingIdx(MmiPhbReadBlackListByRaiIdxReq_t *ptReq,
                                        MmiPhbReadBlackListByRaiIdxCnf_t *ptCnf);

/** SrvPhbDeleteOneBlackListBySortingIdx
* @brief  The interface of Service Client is used to delete black list member by sorting index.
*
* @param[in]      nPhBlackListRaiIdx      Sorting index of contact.
*
* @retval MAE_RET_SUCCESS                 Successful.
* @retval MAE_RET_NOT_FOUND               Not found.
*/
MAE_Ret SrvPhbDeleteOneBlackListBySortingIdx(u16 nPhBlackListRaiIdx);

/** SrvPhbIsInBlackList
* @brief  The interface of Service Client is used to test this number is in black list or not
*
* @param[in]      ptNumber                The number which want to test
* @param[out]     pbBlock                 Reference to the result,TRUE : In black list,FALSE : not in black list
*
* @retval MAE_RET_SUCCESS                 Successful.
* @retval MAE_RET_FAILED                  Fail.
*/
MAE_Ret SrvPhbIsInBlackList(boolean *pbBlock, MmiPhbNumber_t *ptNumber);

/** SrvPhbGetBlackListNumber
* @brief  The interface of Service Client is used to get the compare number of black list.
*
* @param[out]     pnPhbBlackListCmpNumber     reference to the result with the compare number of black list.
*
* @retval MAE_RET_SUCCESS                 Successful.
*/
MAE_Ret SrvPhbGetBlackListNumber(u8 *pnPhbBlackListCmpNumber);

/** SrvPhbLoopUrl
* @brief  The interface of  Service Client is used to get data url from RegKey ID.
*
* @param[in]    u32RegId	Hash Key ID
* @param[out]   pszUrl		Data url
*
* @retval MAE_RET_SUCCESS                 Successful.
*/
MAE_Ret SrvPhbLoopUrl(u32 u32RegId, MAE_WChar *pszUrl);

/** SrvPhbConvertLocalSortingIdxToTotal
* @brief  The interface of  Service Client is used to convert local sorting index to total index
*
* @param[in]    s32PhbBookType	: local book type
* @param[in]    s32PhbGroup	: local group type
* @param[in]    u16PhbSortingIdx: local sorting index
*
* @retval u16                 total index.
*/
u16 SrvPhbConvertLocalSortingIdxToTotal(MmiPhbBookType_e	s32PhbBookType, 
													 MmiPhbGroup_e		s32PhbGroup, 
													 u16				u16PhbSortingIdx);

/**
SrvPhbGetBlackListNumber
@brief  The interface of Service Client is use to Register the Hash data and get the hash key ID .

@param[in]	pInputUrl		Reg Data for Hash to get the hash key ID
@param[out] pOutputHashID	Hash Key ID

@return MAE_RET_SUCCESS                 Successful.
@return MAE_RET_FAILED                  Fail, cause of phone do not have enough sapce.
*/
MAE_Ret SrvPhbRegHashID(MAE_WChar *pInputUrl, u32 *pOutputHashID);

/**
SrvPhbDeregHashID
@brief  The interface of Service Client is use to Deregister the Hash data.

@param[in] pOutputHashID	register Key ID

@return MAE_RET_SUCCESS                 Successful.
@return MAE_RET_FAILED                  Fail.
*/
MAE_Ret SrvPhbDeregHashID(u32 *pOutputHashID);

MAE_Ret SrvPhbSearchPhyIdxByNumber(MmiPhbBookType_e s32PhbBookType, const MmiPhbNumber_t	*ptNumber, u16 *pu16PhyIdx);

#if defined(__MMI_PHB_SMART_ALPHABET_FILTER_SUPPORT__) || defined(__MMI_PHB_SMART_NUMBER_FILTER_SUPPORT__)
/**
SrvPhbSetFuzzySearchType
@brief  Set the fuzzy search type for searching and write it to RAI.

@param[in] eFuzzySearchType	            Fuzzy search type.

@return MAE_RET_SUCCESS                 Successful.
@return MAE_RET_WRITE_ERROR             Fail to write to RAI.
*/
MAE_Ret SrvPhbSetFuzzySearchType(MmiPhbSrvFuzzySearchType_e eFuzzySearchType);

MmiPhbSrvFuzzySearchType_e SrvPhbGetFuzzySearchType(void);

#endif

MAE_Ret SrvPhbMasterRestore(void);

void SrvPhbSetADNStatusEx(MmiPhbBookType_e s32PhbBookType, u16 u16MaxEmailNum, u16 u16UsedEmailNum, u16 u16MaxExtNum, u16 u16UsedExtNum);
void SrvPhbGetADNStatusEx(MmiPhbBookType_e s32PhbBookType, u16 *pu16MaxEmailNum, u16 *pu16UsedEmailNum, u16 *pu16MaxExtNum, u16 *pu16UsedExtNum);

#endif //__MMI_SRV_PHB_H__

