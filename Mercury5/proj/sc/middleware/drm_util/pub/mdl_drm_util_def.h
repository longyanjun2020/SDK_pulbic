/**
* @file mdl_drm_util_def.h
*
* DRMAGENTSRV structure definition
*
* $Id: $
*/
#ifndef __MDL_DRM_UTIL_DEF_H__
#define __MDL_DRM_UTIL_DEF_H__

#include "vm_types.ht"
/*=============================================================*/
// Macro definition
/*=============================================================*/

#define MDL_DRM_CRLF                           "\r\n"
#define MDL_DRM_STRLEN_CRLF                    strlen(MDL_DRM_CRLF)
#define MAX_DCF_HDR_SIZE 512
#define MAX_STATIC_BUF_SIZE 64


//AES codec parameters
#define BLOCK_SIZE 16 //bytes
#define KEY_SIZE 16 //bytes

#define Nb 4
#if (KEY_SIZE==16)
#define Nr 10
#define Nk 4
#elif (KEY_SIZE==24)
#define Nr 12
#define Nk 6
#elif (KEY_SIZE==32)
#define Nr 14
#define Nk 8
#endif

#define ROUND_KEY_SIZE ((Nr+1)*KEY_SIZE)

//1 Define DRM Header
#define MDL_DRM_HEADERS_ENCRYPTION          "Encryption-Method: "
#define MDL_DRM_HEADERS_CONTENTNAME         "Content-Name: "
#define MDL_DRM_HEADERS_RIGHTSISSUER        "Rights-Issuer: "
#define MDL_DRM_HEADERS_CONTENTDESCRIPTION  "Content-Description: "
#define MDL_DRM_HEADERS_CONTENTVENDOR       "Content-Vendor: "
#define MDL_DRM_HEADERS_ICONURI             "Icon-Uri: "

/*=============================================================*/
// Data type definition
/*=============================================================*/

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
}MDL_DRM_Headers_t;

typedef struct
{
    u8 nVersion;
    u8 nContentTypeLen;         //mimetype format ex. img/jpg...
    u8 nContentUriLen;          // cid:xxxxx.xxxx
    char *pContentType;         //Content-type //define the original MIME media type
    char *pContentUri;          //Content-URI  //contain a unique identifier for this DRM protected content object
    u32 nHeadersLen;            // Uintvar
    u32 nDataLen;               // Uintvar
    MDL_DRM_Headers_t tHeaders;
    char *pData;

}MDL_DRM_ContentField_DCF_t;

typedef enum _E_AES_MODE_
{
    AES_128_ECB = 0,
    AES_128_CBC
} E_AES_MODE;

typedef enum _E_AES_DIR_
{
    AES_ENC = 0,
    AES_DEC
} E_AES_DIR;

typedef enum _E_AES_BUF_MODE_
{
    AES_TWO_BUF = 0,
    AES_IN_PLACE_BUF
} E_AES_BUF_MODE;


typedef struct _AES_HANDLE_
{
    u8 *pRoundKey;
}AES_HANDLE;

typedef struct _AES_ENCRYPT_PARAMS_
{
    E_AES_DIR eDir;
    E_AES_MODE eMode;
    u8 *pSrc;
    u8 *pDest;
    u32 nDataLen;
    u8 *pIV;
    E_AES_BUF_MODE eBufMode;
}AES_ENCRYPT_PARAMS;

#endif /* __MDL_DRM_UTIL_DEF_H__ */

