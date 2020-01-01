////////////////////////////////////////////////////////////////////////////////
//
// Copyright (c) 2006-2009 MStar Semiconductor, Inc.
// All rights reserved.
//
// Unless otherwise stipulated in writing, any and all information contained
// herein regardless in any format shall remain the sole proprietary of
// MStar Semiconductor Inc. and be kept in strict confidence
// (¡§MStar Confidential Information¡¨) by the recipient.
// Any unauthorized act including without limitation unauthorized disclosure,
// copying, use, reproduction, sale, distribution, modification, disassembling,
// reverse engineering and compiling of the contents of MStar Confidential
// Information is unlawful and strictly prohibited. MStar hereby reserves the
// rights to any and all damages, losses, costs and expenses resulting therefrom.
//
////////////////////////////////////////////////////////////////////////////////

/**
* @file    mmi_phbapp_callback.h
* @version $Id: mmi_phbapp_callback.h 2010-01-13 11:30:23Z shin.lin $
* @brief   Phonebook service callback functions header file
*
*/

#ifndef __MMI_PHBAP_CALLBACK_H__
#define __MMI_PHBAP_CALLBACK_H__

#include "mmi_srv_phb.h"
#include "mmi_srv_accessory.h"
#include "mmi_srv_usb.h"
#include "mmi_subject.h"

void PHBAPP_Init_PhonebookReady_CB(void* pUserdata);
void PHBAPP_Rebuild_PhonebookReady_CB(void* pUserdata);


void _PHB_ShowPHBContactList_QueryStatus_CB(void *UserData,
        MmiPhbSrvFunId_e       s32PhbSrvFid,
        MmiPhbQueryPhbStatusCnf_t *ptCnf);

void PHBAPP_ViewMemoryStatus_QueryStatus_CB(void *UserData,
        MmiPhbSrvFunId_e       s32PhbSrvFid,
        MmiPhbQueryPhbStatusCnf_t *ptCnf);

void PHBAPP_EdiContactShowEdit_QueryStatus_CB(void *UserData,
        MmiPhbSrvFunId_e       s32PhbSrvFid,
        MmiPhbQueryPhbStatusCnf_t *ptCnf);

#ifndef __MMI_PHBAP_DISABLE_GROUP__ 
void PHBAPP_ViewGroup_PrepareData_QueryStatus_CB(void *UserData,
        MmiPhbSrvFunId_e       s32PhbSrvFid,
        MmiPhbQueryPhbStatusCnf_t *ptCnf);
#endif 

void PHBAPP_MultiSelect_PrepareData_QueryStatus_CB(void *UserData,
        MmiPhbSrvFunId_e       s32PhbSrvFid,
        MmiPhbQueryPhbStatusCnf_t *ptCnf);

#ifndef __MMI_PHB_DISABLE_BLACKLIST__
void PHBAPP_ReadOneContactBySortingForAssignBK_CB(void *UserData,
        MmiPhbSrvFunId_e       s32PhbSrvFid,
        MmiPhbReadOneContactBySortingIdxCnf_t *pCnf);
#endif // #ifndef __MMI_PHB_DISABLE_BLACKLIST__

void PHBAPP_ViewPhbListGetDetails_ReadOneContactBySorting_CB(void *UserData,
        MmiPhbSrvFunId_e       s32PhbSrvFid,
        MmiPhbReadOneContactBySortingIdxCnf_t *pCnf);

void PHBAPP_ViewPhbListGetMultiDetails_ReadOneContactBySorting_CB(void *UserData,
        MmiPhbSrvFunId_e       s32PhbSrvFid,
        MmiPhbReadOneContactBySortingIdxCnf_t *pCnf);

void PHBAPP_ReadOneContactBySorting_CB(void *UserData,
        MmiPhbSrvFunId_e       s32PhbSrvFid,
        MmiPhbReadOneContactBySortingIdxCnf_t *pCnf);

void PHBAPP_MakeCallPrepareData_ReadOneContactBySorting_CB(void *UserData,
        MmiPhbSrvFunId_e       s32PhbSrvFid,
        MmiPhbReadOneContactBySortingIdxCnf_t *pCnf);

void PHBAPP_EditContactPrepareData_ReadOneContactBySorting_CB(void *UserData,
        MmiPhbSrvFunId_e       s32PhbSrvFid,
        MmiPhbReadOneContactBySortingIdxCnf_t *pCnf);
#ifdef __SXMENGINE__
void PHBAPP_VideoChat_ReadOneContactBySorting_CB(void *UserData,
        MmiPhbSrvFunId_e       s32PhbSrvFid,
        MmiPhbReadOneContactBySortingIdxCnf_t *pCnf);
#endif

void  PHBAPP_ViewPhbListGetDetails_WriteOneContactByPhysical_CB(void *UserData,
        MmiPhbSrvFunId_e       s32PhbSrvFid,
        MmiPhbWriteOneContactByPhysicalIdxCnf_t *pCnf);

void  PHBAPP_SelectNumToSaveSave_WriteOneContactByPhysical_CB(void *UserData,
        MmiPhbSrvFunId_e       s32PhbSrvFid,
        MmiPhbWriteOneContactByPhysicalIdxCnf_t *pCnf);

void  PHBAPP_SelectImageRingID_ShowChangeMenu_WriteOneContactByPhysical_CB(void *UserData,
        MmiPhbSrvFunId_e       s32PhbSrvFid,
        MmiPhbWriteOneContactByPhysicalIdxCnf_t *pCnf);

void  PHBAPP_SelectImageRingID_SelectNew_WriteOneContactByPhysical_CB(void *UserData,
        MmiPhbSrvFunId_e       s32PhbSrvFid,
        MmiPhbWriteOneContactByPhysicalIdxCnf_t *pCnf);

#ifndef __MMI_PHBAP_DISABLE_GROUP__ 
void  PHBAPP_SelectGroup_ListGroup_WriteOneContactByPhysical_CB(void *UserData,
        MmiPhbSrvFunId_e       s32PhbSrvFid,
        MmiPhbWriteOneContactByPhysicalIdxCnf_t *pCnf);
#endif // #ifndef __MMI_PHBAP_DISABLE_GROUP__ 

void  PHBAPP_EditContact_Save_WriteOneContactByPhysical_CB(void *UserData,
        MmiPhbSrvFunId_e       s32PhbSrvFid,
        MmiPhbWriteOneContactByPhysicalIdxCnf_t *pCnf);

void  PHBAPP_EditContact_Save_WriteOneNewContact_CB(void *UserData,
        MmiPhbSrvFunId_e       s32PhbSrvFid,
        MmiPhbWriteOneNewContactCnf_t *pCnf);

void PHBAPP_CheckWriteContactResult(void *UserData, MmiPhbResult_e s32PhbResult, u16 u16PhbPhysicalIdx);

void  PHBAPP_DeleteContact_DeleteOneContactBySorting_CB(void *UserData,
        MmiPhbSrvFunId_e       s32PhbSrvFid,
        MmiPhbDeleteOneContactBySortingIdxCnf_t *pCnf);

void  PHBAPP_MultiSelectStartMultiDelete_DeleteOneContactBySortingI_CB(void *UserData,
        MmiPhbSrvFunId_e       s32PhbSrvFid,
        MmiPhbDeleteOneContactBySortingIdxCnf_t *pCnf);

void  PHBAPP_CopyContacts_CopyOneContactBySorting_CB(void *UserData,
        MmiPhbSrvFunId_e       s32PhbSrvFid,
        MmiPhbCopyOneContactBySortingIdxCnf_t *pCnf);

void  PHBAPP_MultiSelectCopyContacts_CopyOneContactBySorting_CB(void *UserData,
        MmiPhbSrvFunId_e       s32PhbSrvFid,
        MmiPhbCopyOneContactBySortingIdxCnf_t *pCnf);

#ifndef __MMI_PHB_DISABLE_IMPORT_EXPORT__
void  PHBAPP_ExportContacts_ImportExportContactResult_CB(void *UserData,u32 pExportReq, boolean bSuccess);

void  PHBAPP_ImportContacts_ImportExportContactResult_CB(void *UserData,u32 pImportReq, boolean bSuccess);
#endif // #ifndef __MMI_PHB_DISABLE_IMPORT_EXPORT__

void mmi_PHBAP_AccessoryPlugStatusChange_CB(void *pThis, ACCDeviceType_e eDevice, boolean bPlug, ExtCardAccInfo_e eCardinfo);

void mmi_PHBAP_USBStatusChangedCB(void *pData, MMI_USB_STATUS_E eUSBStatus);

#if defined(__APP_MMI_CHECKDISK__)
void mmi_PHBAP_CheckDiskStatusListener(char *pSbjName, SubjectStatus_e nSbjStatus, void *pUser);
#endif

void mmi_PHBAP_MultiDeleteTimeout_CB(void* data);

#ifdef __SIM_NO_RSP_HANDLING__
void _PhbAppSIMNoRspCB(void *pApplet, u8 nActiveSIM);
#endif

#endif /* __MMI_PHBAPP_CALLBACK_H__ */
