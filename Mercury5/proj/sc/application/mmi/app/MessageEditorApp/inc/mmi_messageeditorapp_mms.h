#ifdef __MMS_MMI_CDMMS__

#ifndef __MMI_MESSAGEEDITORAPP_MMS_H__
#define __MMI_MESSAGEEDITORAPP_MMS_H__
#include "mmi_messageeditorapp.h"
#include "mmi_messageeditorapp_priv.h"
#include "mmi_message_cfg.h"

#define SEA_MMS_RECIPIENT_SEPERATOR L";"

#define SEA_MMS_OBJECTTYPE_MASK 0x0000FFFF

MAE_Ret  SEA_MmsSetEditorData(MMI_SEA* pThis, SEA_EDITOR_Info_t* info);
MAE_Ret SEA_MmsInitData(MMI_SEA *pThis);
void SEA_MmsReleaseData(MMI_SEA *pThis);
MAE_Ret SEA_MmsGetRestSize(MMI_SEA *pThis, u32 *nRetSize);

void SEA_MmsUpdateSizeDisplay(MMI_SEA *pThis);
MAE_Ret SEA_MmsUpdateEditorView(MMI_SEA *pThis, u32 nSlideIdx);
MAE_Ret SEA_MmsLoadFullEditor(MMI_SEA *pThis, SEA_InputType_e eEditorType);
MAE_Ret SEA_MmsUpdateObjectListView(MMI_SEA *pThis);
void SEA_MmsSetFocus(MMI_SEA *pThis, u32 nWidgetID, boolean bFocused);
#ifdef __USER_FILE_DELETER__
MAE_Ret SEA_MmsLaunchFileMangerDeleteApp(MMI_SEA *pThis, FileMgrApp_FilterType_e nFilterType);
#endif
#ifdef __MMS_MMI_CDMMS_TEMPLATE__
MAE_Ret SEA_MmsLoadTemplate( MMI_SEA *pThis, u32 nTemplateIdx );
MAE_Ret SEA_MmsOperationSaveTemplate( MMI_SEA *pThis );
MAE_Ret SEA_MmsGenerateObject(MMI_SEA *pThis, Msg_MmsTemplate_t *mms_temp, MMI_MmsObjectType_e type);
MAE_Ret SEA_MmsAddTemplateObject(MMI_SEA *pThis, Msg_MmsTemplate_t *mms_temp, MMI_MmsObjectType_e type);
#endif

u32  SEA_MmsObjectsAmountByCurrentSlide(MMI_SEA *pThis);
void SEA_MmsObjectListMenuAdaptGet(WdgDynamicMenuItemPtr_t *pItemDataPtr, HWIN hWin, WdgMenuItemType_e eItemType, IWidget *pMenu, u32 u32Index);
void SEA_MmsObjectListMenuFreeItem(WdgDynamicMenuItemPtr_t *pItemDataPtr, void *pOwner, WdgMenuItemType_e eItemType);
void SEA_MmsObjectListInfoFreeItem(void* pData, void* pOwner);
void SEA_MmsObjectListMenuSoftKeyHandleCB(void *pApplet, void *pUsrData, WidgetEvtCode_t nEvtCode, HistoryInfo_t *pHistoryInfo, IWidget *pWidget);
void SEA_MmsObjectListOptionMenuSoftKeyHandleCB(void *pApplet, void *pUsrData, WidgetEvtCode_t nEvtCode, HistoryInfo_t *pHistoryInfo, IWidget *pWidget);
void SEA_AudioStopCB(void *pData, MediaSrvErrCode_e eErrorCode);

void SEA_MmsFullEditorOptMenuSoftKeyHandleCB(void *pApplet, void *pUsrData, WidgetEvtCode_t nEvtCode, HistoryInfo_t *pHistoryInfo, IWidget *pWidget);

void SEA_MmsSlideMenuSoftKeyHandleCB(void *pApplet, void *pUsrData, WidgetEvtCode_t nEvtCode, HistoryInfo_t *pHistoryInfo, IWidget *pWidget);
void SEA_MmsSlideMenuGetItem(WdgDynamicMenuItemPtr_t *pItemDataPtr, HWIN hWin, WdgMenuItemType_e eItemType, IWidget *pMenu, u32 u32Index);
void SEA_MmsSlideMenuFreeItem(WdgDynamicMenuItemPtr_t *pItemDataPtr, void *pOwner, WdgMenuItemType_e eItemType);

// launch ap
MAE_Ret SEA_MmsLaunchFileMangerApp(MMI_SEA *pThis, FileMgrApp_FilterType_e nFilterType, u32 nSizeLimitation);

/************pMMSData->pMsl related funtion*****************/
MAE_Ret SEA_MmsDelSlide(MMI_SEA *pThis, u8 nSlideIdx);
MAE_Ret SEA_MmsAddSlide(MMI_SEA *pThis,u32 *nIdx);
MAE_Ret SEA_MmsInsertSlideAt(MMI_SEA *pThis,u32 idx);
MAE_Ret SEA_MmsDeleteObjectAtCurrentSlide(MMI_SEA *pThis, MMI_MmsObjectType_e eDelType);
MAE_Ret SEA_MmsSetSlideDuration(MMI_SEA *pThis,u32 nSlideIdx,u32 nDuration);
MAE_Ret SEA_MmsGetSlideDuration(MMI_SEA *pThis, u32 nSlide, u32 *nDuration);
#ifdef __MMS_SUPPORT_RESIZE_IMAGE__
MAE_Ret SEA_MmsAddImageWithScalingCotrol( MMI_SEA *pThis, MAE_WChar *pURL );
#endif
MAE_Ret SEA_MmsAddObject( MMI_SEA *pThis, u32 *pSlideIdx, MAE_WChar *pURL, u8 *pAsciiName, u8 *pData, u32 nDataSize, u8 *pMIMETypeStr, MMI_MmsObjectType_e eInsertType );
MAE_Ret SEA_MmsGetSlideTextLoc(MMI_SEA *pThis, u32 nSlideIdx, MSG_MMS_TEXT_LOCATION_e *eTextLoc);
MAE_Ret SEA_MmsSetSlideTextLoc(MMI_SEA *pThis,u32 nSlideIdx,MSG_MMS_TEXT_LOCATION_e eTextLoc);
MAE_Ret SEA_MmsGetSlideImageSize (MMI_SEA *pThis, u32 nSlideIdx, MSG_MMS_IMAGE_SIZE_e *eImageSize);
MAE_Ret SEA_MmsSetSlideImageSize(MMI_SEA *pThis,u32 nSlideIdx,MSG_MMS_IMAGE_SIZE_e eImageSize);


/**************pMMSData->pMal attachment list************************/
MAE_Ret SEA_MmsAddAttachment( MMI_SEA *pThis, MAE_WChar *pURL, u8 *pAsciiName, u8 *pData, u32 nDataSize, u8 *pMIMETypeStr );
static void SEA_MmsDelAttachment(MMI_SEA *pThis, u32 nIdx);
static void SEA_MmsFreeAttList(void *pData, IBase *pOwner);
void SEA_MmsDeregisterAllCB(MMI_SEA *pThis);
MAE_Ret SEA_MmsCheckObjctBySlide(MMI_SEA *pThis,u32 nSlideIdx);

/**************pMMSData->pMr recipient list************************/
void SEA_MmsTransRecipientModelIntoMMSData(MMI_SEA *pThis,VectorClass_t *pRecipientList);


MAE_Ret SEA_MmsSetSubject(MMI_SEA *pThis, MAE_WChar *pSubject);
MAE_Ret SEA_MmsSetText(MMI_SEA *pThis, u32 nSlideIdx, MAE_WChar *pContent);
MAE_Ret SEA_MmsAddText(MMI_SEA *pThis, u32 nSlideIdx, MAE_WChar *pContent);

// file handle
void SEA_MmsAddRecipientFromSrv(MMI_SEA *pThis, u32 nNum, u8 *ptrStart,SEA_RecipientType_e eType);
boolean SEA_MmsObjectListSoftKeyHandleEvent(void* pUserData, MAE_EventId evt, u32 param1, u32 param2);
boolean SEA_MmsIsValidEmail(u8* pEmailStr,u32 emailLen);
MAE_Ret SEA_MmsUtilWstrToUtf8(MAE_WChar* pWStr, u8** ppUTF8Str, u32 *pUTF8Size);
MAE_WChar* SEA_MmsGetAvailableName(MMI_SEA *pThis, MAE_WChar *pFileName, u8 *pMIMETypeStr, u8 *pOriExtStr, MMI_MmsObjectType_e eInsertType, u8 nIndex );
void SEA_FilemgrSelectObject_ContentFilterCb(FileManagerFileInfo_t *sFileInfo, boolean *pbReject, u32 *pnWarningMsgTextId);

void SEA_MmsStartMmsaPageSetting(IBase *pObj, u32 Param);
void SEA_MmsaMdlListener(void *pUsrData, ModelEvent_t *pMdlEvent);
void SEA_StopPlayHandler(MMI_SEA *pThis);

void SEA_MmsOperationRemoveObj(MMI_SEA *pThis);
void SEA_MmsOperationPlayMusic(MMI_SEA *pThis);
void SEA_MmsOperationOpenObj(MMI_SEA *pThis);
MAE_Ret SEA_MmsOperationConverToSMS(MMI_SEA *pThis);
MAE_Ret SEA_MmsOperationSendMMS(MMI_SEA *pThis);
MAE_Ret SEA_MmsOperationSaveMMS(MMI_SEA *pThis);
MAE_Ret SEA_MmsSendMsg(MMI_SEA *pThis);

void SEA_MmsLeftButtonClickHandleCb(void *pApplet, void *pUsrData, WidgetEvtCode_t nEvtCode, u32 dwParam,IWidget *pWidget);
void SEA_MmsRightButtonClickHandleCb(void *pApplet, void *pUsrData, WidgetEvtCode_t nEvtCode, u32 dwParam,IWidget *pWidget);
boolean SEA_MmsScrollbarWdgHandleEvent(void* pUserData, MAE_EventId evt, u32 param1, u32 param2);
void SEA_MmsScrollbarWdgHandleEventFree(MMI_SEA *pThis);

#endif // __ .h
#endif // __MMS_MMI_CDMMS__
