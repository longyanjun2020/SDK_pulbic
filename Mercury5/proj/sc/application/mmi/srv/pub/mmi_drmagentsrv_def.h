/**
* @file mmi_drmagentsrv_def.h
*
* DRMAGENTSRV structure definition
*
* $Id: $
*/
#ifndef __MMI_DRMAGENTSRV_DEF_H__
#define __MMI_DRMAGENTSRV_DEF_H__

#ifdef __MMI_OMA_DRM_V1__

/*=============================================================*/
// Macro definition
/*=============================================================*/

#define DRM_CRLF                           "\r\n"
#define DRM_STRLEN_CRLF                    STRLEN(DRM_CRLF)
#define MAX_DCF_HDR_SIZE 512

#define DRM_TAG_STACK_MAX                  10      /* the max longth of stack */
#define DRM_TAG_EMPTY_STACK                -1      /* empty stack flag */
#define DRM_TAG_DESTROYED_STACK            -2      /* the stack has been destroyed */

#define FIND_CONTENTTYPE_SIZE              100
#define OPEN_FILE_BUFFER_SIZE              4992
#define OPEN_BASE64_FIRST_BUFFER_SIZE      854
#define OPEN_BINARY_FIRST_BUFFER_SIZE      624

#define DRM_TYPE_FL                     "m_ForwardLock"
#define DRM_TYPE_CD                     "m_ConbinedDelivery"
#define AESPE_LEN                       "624"

#define DRM_WRITE_MAXBUFFERSZ 512 //must larger than HeaderLen of DCF file

#define DRM_RIGHTS_CONTENTTYPE "application/vnd.oma.drm.rights+xml"
#define DRM_MSG_CONTENTTYPE    "application/vnd.oma.drm.message"    // unsupport media content type

//1 Define DRM headers name
//read
#define DRM_HEADERS_CONTENTTYPE         "content-type: "
#define DRM_HEADERS_CONTENTID           "content-id: "
#define DRM_HEADERS_ENCODING            "content-transfer-encoding: "
#define DRM_HEADERS_READ_ENCRYPTION     "encryption-method: "
#define DRM_HEADERS_READ_CONTENTNAME    "content-name: "
#define DRM_HEADERS_READ_RIGHTSISSUER   "rights-issuer: "
//write 
#define DRM_HEADERS_ENCRYPTION          "Encryption-Method: "
#define DRM_HEADERS_CONTENTNAME         "Content-Name: "
#define DRM_HEADERS_RIGHTSISSUER        "Rights-Issuer: "
#define DRM_HEADERS_CONTENTDESCRIPTION  "Content-Description: "
#define DRM_HEADERS_CONTENTVENDOR       "Content-Vendor: "
#define DRM_HEADERS_ICONURI             "Icon-Uri: "
#define DRM_CID                         "cid:"

#define drm_atof(n)     atof(n)
#define drm_atoi(n)     atoi(n)
#define drm_strlen(n)   strlen(n)
#define drm_isdigit(n)  isdigit(n)
#define DRM_GETDIGITS(n, digit) {   u32 nNum = n; digit = 0;   \
								    do{   \
									    nNum /= 10; digit++;    \
								    }while(0 != nNum);    \
								}

/*=============================================================*/
// Data type definition
/*=============================================================*/
typedef void (*Drm_Write_Finish_CB) (void *pUser, MAE_WChar *pwDrmFilePath, MAE_Ret nRetDRM);

/*=============================================================*/
// Variable definition
/*=============================================================*/
typedef struct
{
    char *pContentType;         //Content-type
    char *pContentID;           //Content-ID
    char *pContentTransferEncoding;
    char *pEncryptionMethod;
    char *pContentName;
    char *pRightsIssuer;
    char *pContentDescription;
    char *pContentVendor;
    char *pIconUri;
}DRM_Headers_t;

typedef struct
{
    u32 nSize;
    char *pBuffer;
}DRM_Content_t;

typedef struct
{
    u32 nOffsetFromHead;     //offset of content
    DRM_Headers_t tHeaders;
    DRM_Content_t tContent;
}DRM_Block_t;

//1 DRM Message Format
typedef struct
{
    boolean bIsWithRights;
    DRM_Block_t tRights;
    DRM_Block_t tMediaContent;
}DRM_ContentField_DM_t;

typedef struct
{
    u8 nVersion;
    u8 nContentTypeLen;         // mimetype format ex. img/jpg...
    u8 nContentUriLen;          // cid:xxxxx.xxxx
    char *pContentType;         // Content-type //define the original MIME media type
    char *pContentUri;          // Content-URI  //contain a unique identifier for this DRM protected content object
    u32 nHeadersLen;            // Uintvar
    u32 nDataLen;               // Uintvar
    DRM_Headers_t tHeaders;
    char *pData;
}DRM_ContentField_DCF_t;

typedef enum
{
    DRM_None,
    DRM_ForwardLock,
    DRM_ConbinedDelivery,
    DRM_SeparatedDelivery,
}DRM_FileType_e;


typedef enum
{
    DRM_Rights_None,
	DRM_Rights_Version,
	DRM_Rights_Uid,
	DRM_Rights_KeyValue
}DRM_RightsTag_e;

typedef enum
{
    DRM_Permission_None,
	DRM_Permission_Play,
	DRM_Permission_Display,
	DRM_Permission_Execute,
	DRM_Permission_Print
}DRM_PermissionTag_e;

typedef enum
{
    DRM_Constraint_None,
	DRM_Constraint_Count,
	DRM_Constraint_Start,
	DRM_Constraint_End,
	DRM_Constraint_Interval
}DRM_ConstraintTag_e;

typedef enum
{
    DRM_Usage_None,
    DRM_Usage_Send,
    DRM_Usage_SetAs,
    DRM_Usage_All,
}DRM_UsageType_e;

typedef struct
{
    boolean bPermission;
    char *pCount;
	char *pStart;
	char *pEnd;
	char *pInterval;
}DRM_Constraint_t;

typedef struct
{
    DRM_RightsTag_e eRightsTag;
    DRM_PermissionTag_e ePermissionTag;
	DRM_ConstraintTag_e eConstraintTag;
    char *pVersion;
	char *pUid;
	u8 *pKeyValue;	
	DRM_Constraint_t tPlay;
	DRM_Constraint_t tDisplay;
	DRM_Constraint_t tExecute;
	DRM_Constraint_t tPrint;
}DRM_RightsData_t;

typedef struct
{
    u8 stack[DRM_TAG_STACK_MAX];
    s8 top;
}DRM_Tag_Stack;

typedef struct
{
    void *pUser;
	void *pIFStream;
	void *pSaveIFStream;
    void *pAesHandle;
	void *pEncParams;
	u8 *pFileData;
	u8 *pBase64DecodeData;
	u32 nContentSize;
	u32 nCurContentReadSize;
	u32 nOpenSize;
	boolean bIsBase64Encode;
	MAE_WChar *pOldFileURL;
	MAE_WChar *pNewSaveFileURL;
	Drm_Write_Finish_CB pFinishCB;
    boolean bIsPartialEncrypt;
}DRM_Async_Write_Data_t;

#endif

#endif /* __MMI_DRMAGENTSRV_DEF_H__ */

