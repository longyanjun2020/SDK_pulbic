/**
 * @file    mmi_drmagent_util.h
 * @brief   The file is contain some utilities for DRMAGENTSRV.
 * @author
 *
 * @version $Id:
 */

#ifndef __MMI_DRMAGENTSRV_UTIL_H__
#define __MMI_DRMAGENTSRV_UTIL_H__

#ifdef __MMI_OMA_DRM_V1__

#include "mmi_mae_helper.h"
#include "mmi_drmagentsrv_def.h"
#include "prov_xml.h"   //for REL Parser and WBXML Parser
#include "mmi_mae_rightsdb.h"
#include "mdl_drm_util.h"
#include "mmi_launcher_filemanager.h"


/*=============================================================*/
// Local function prototype declaration and definition
/*=============================================================*/
static char* _GetHeaderValue(/*[in]*/void *pStream, u32 nStreamSize, char *pHeaderName,/*[out]*/char **ppValue);
static char* _SetHeaderValue(/*[in]*/void *pStream, u32 nStreamSize, char *pHeaderName,char *pValue);
static char* _GetOneByteValue(char *pBuffer, u8 *pValue);
static char* _SetOneByteValue(char *pBuffer, u8 nValue);
static char* _GetStringByLen(char *pBuffer, char **ppValue, u32 nLen);
static char* _SetStringByLen(char *pBuffer, char *pValue, u32 nLen);
static int _GetUintvarValue(u8 **uintvar,u32 *value);
static int _SetUintvarValue(u8 **uintvar, u32 value);
static int _GetUintvarLen(u32 value);
static char* _MoveToNextBoundary(/*[in]*/void *pStream, u32 nStreamSize,const char *pBoundary);
static MAE_Ret _VerifyDrmFile_DM(DRM_ContentField_DM_t *pDMData);
static boolean _IsDMFormatWithRights(void* pStream, u32 nStreamSize);
static boolean _DRMSRV_SetWriteBufferWithoutMediaContent(char *pWriteBuffer, u32 nMaxBufferSize, DRM_ContentField_DCF_t *pDCFData, u32 nOffset, u32 *pWriteSize);

//DRM Message Parser(DM/DCF)
u32 mmi_DRMSRV_GetHeaderLen(DRM_Headers_t *pHeaders);
MAE_Ret mmi_DRMSRV_GetContentType_DCF(void* pStream, u32 nStreamSize,/*[out]*/ char **ppValue);
DRM_FileType_e mmi_DRMAGENTSRV_GetDrmFileType(MAE_WChar *pFileURL);
DRM_FileType_e mmi_DRMAGENTSRV_GetDrmFileTypeByBuffer(u8 *pStream, u32 nStreamSize);
MAE_Ret mmi_DRMAGENTSRV_CheckDrmFileRights(MAE_WChar *pFileURL, DrmAction_e eAtion, IBase *pOwner);
MAE_Ret mmi_DRMAGENTSRV_CheckDrmFileRightsByBuffer(u8 *pStream, u32 nStreamSize, DrmAction_e eAtion, IBase *pOwner);
MAE_Ret mmi_DRMAGENTSRV_ConsumeDrmFile(MAE_WChar *pFileURL, DrmAction_e eAtion, IBase *pOwner);
MAE_Ret mmi_DRMAGENTSRV_ConsumeDrmFileByBuffer(u8 *pStream, u32 nStreamSize, DrmAction_e eAtion, IBase *pOwner);
boolean mmi_DRMAGENTSRV_IsDCFFormat(MAE_WChar *pFileURL, char **ppCid, char **ppRightsIssuer);
boolean mmi_DRMAGENTSRV_IsDCFFormatByMediaMgrPath(const u16* const pName, char **ppCid, char **ppRightsIssuer);
boolean mmi_DRMAGENTSRV_IsDCFFormatByBuffer(u8 *pStream, u32 nStreamSize, char **ppCid, char **ppRightsIssuer);
MAE_Ret mmi_DRMAGENTSRV_SyncRead_DM(void *pStream, u32 nStreamSize, u32 nFileSize,char *pBoundary,/*[out]*/ DRM_ContentField_DM_t *pDMData);
MAE_Ret mmi_DRMAGENTSRV_SyncRead_DCF(void *pStream, u32 nStreamSize, DRM_ContentField_DCF_t *pDCFData ,u32 *pReadLen);
MAE_Ret mmi_DRMAGENTSRV_SyncWrite_DCFWithoutMediaContent(void* pFStream, DRM_ContentField_DCF_t *pDCFData ,u32 *WriteBytes);
void mmi_DRMAGENTSRV_Free_DM(DRM_ContentField_DM_t *pDMData);
void mmi_DRMAGENTSRV_Free_DCF(DRM_ContentField_DCF_t *pDCFData);

MAE_Ret MMI_DRMAGENTSRV_IsDrmFileCanBeUsedAs(MAE_WChar *pFullPath, DRM_UsageType_e nUsage);
MAE_Ret MMI_DRMSRV_GetDcfHeaderString(const u16* const pName, char *pHeaderName,/*[out]*/ char **ppValue);
MAE_Ret MMI_DRMAGENTSRV_MakeFLFile(MAE_WChar *pwSrcURL, MAE_WChar *pwDestURL);

//AES 128 codec(ECB/CBC)
void mmi_DRMAGENTSRV_AES128Init(u8 *pKey, AES_HANDLE **ppAesHandle);
MAE_Ret mmi_DRMAGENTSRV_AES128Encrypt(AES_HANDLE *pAesHandle, AES_ENCRYPT_PARAMS *pEncParams);
void mmi_DRMAGENTSRV_AES128Close(AES_HANDLE *pAesHandle);

//REL Parser and WBXML Parser
MAE_Ret mmi_DRMAGENTSRV_REL_GetRightsData(char *pBuffer, DRM_RightsData_t **pRightsData);
void mmi_DRMAGENTSRV_FreeRightsData(DRM_RightsData_t *pRightsData);
MAE_Ret mmi_DRMAGENTSRV_WBXML_GetRightsData(char *pBuffer, u32 nBufferSize, DRM_RightsData_t **pRightsData);

static XML_BOOL _DRMSRV_REL_StartElementHandler(int8_t *name);
static XML_BOOL _DRMSRV_REL_EndElementHandler(int8_t *name);
static XML_BOOL _DRMSRV_REL_AttrHandler(int8_t *name, int8_t *value);
static XML_BOOL _DRMSRV_REL_ValueHandler(int8_t *value);

static XML_BOOL _DRMSRV_WBXML_GetTagHandler(int32_t codePage, uint8_t tagChar, int8_t *name);
static XML_BOOL _DRMSRV_WBXML_GetAttrHandler(int32_t codePage, uint8_t tagChar, int8_t attrChar, int8_t *name, int8_t *value);
static XML_BOOL _DRMSRV_WBXML_StartElementHandler(int8_t *name);
static XML_BOOL _DRMSRV_WBXML_EndElementHandler(int8_t *name);
static XML_BOOL _DRMSRV_WBXML_AttrHandler(int8_t *name, int8_t *value);
static XML_BOOL _DRMSRV_WBXML_ValueHandler(int8_t *value);

static void _DRMSRV_WBXML_InitStack(void);
static void _DRMSRV_WBXML_DestroyStack(void);
static boolean _DRMSRV_WBXML_PushStack(u8 tagChar);
static boolean _DRMSRV_WBXML_PopStack(u8 *tagChar);

//Rights Interface
MAE_Ret mmi_DRMAGENTSRV_CreateRightsObject(MAE_WChar *pFilename, DRM_RightsData_t *pRightsData, DrmRightsObject_t *pRightsObject);
boolean mmi_DRMAGENTSRV_CheckRights(DrmActionRights_t *pActionRights);
boolean mmi_DRMAGENTSRV_IsValidRights(DrmActionRights_t *pActionRights);


MAE_Ret mmi_DRMAGENTSRV_DM_Generate_DRM_File(const MAE_WChar *pFileURL, char *pBoundary, Drm_Write_Finish_CB pFinishCB, void *pUser, void **ppFileMgrCbData);
MAE_Ret mmi_DRMAGENTSRV_DCF_Generate_DRM_File(const MAE_WChar *pFileURL, char *pBoundary, MAE_WChar **ppSaveFileURL);
MAE_Ret mmi_DRMAGENTSRV_Write_RightsData_To_RAI(const MAE_WChar *pFileURL);
MAE_Ret mmi_DRMAGENTSRV_Cancel_DM_Async_Write(void *pFileMgrCbData);

MAE_Ret mmi_DRMAGENTSRV_SyncDecode_DrmFile(u8 *pSrcBuffer, u32 nBufferSize, IBase *pOwner);
static MAE_Ret _DRMSRV_DCF_Generate_DRM_File(const MAE_WChar *pFileURL, u16 *pFileName, MAE_WChar **ppSaveFileURL);
static MAE_Ret _DRMSRV_DM_Generate_DRM_File(const MAE_WChar *pFileURL, u16 *pFileName, u32 nFileSize, char *pBoundary, Drm_Write_Finish_CB pFinishCB, void *pUser, void **ppFileMgrCbData);
static MAE_Ret _DRMSRV_Input_DCF_Header_Parameter(void* pFStream, u8 *pFileData, DRM_ContentField_DCF_t *pDCFData, DRM_ContentField_DM_t *pDMData, char *pRightsUid, boolean bPartialEncrypt);
static MAE_Ret _DRMSRV_Generate_SaveFile_URL(const MAE_WChar *pFileURL, char *pContentType, MAE_WChar *pFilename, MAE_WChar **ppSaveFileURL, MAE_WChar **ppNewFileName);
static MAE_Ret _DRMSRV_URL_Check_And_Rename(MAE_WChar **pFileURL);
void _DRMSRV_Async_Write_DRM_Data(void *pUser, void *pInfo);

void FileMgrFilterDrmUsageSetAsCb(FileManagerFileInfo_t *sFileInfo, boolean *pbReject, u32 *pnWarningMsgTextId);
void FileMgrFilterDrmUsageSendCb(FileManagerFileInfo_t *sFileInfo, boolean *pbReject, u32 *pnWarningMsgTextId);

#endif

#endif // __MMI_DRMAGENTSRV_UTIL_H__

