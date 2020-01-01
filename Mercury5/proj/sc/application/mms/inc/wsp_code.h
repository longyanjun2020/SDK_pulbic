
#ifndef __WSP_CODE_H__
#define __WSP_CODE_H__

#ifdef __cplusplus
extern "C" {
#endif

#include <ncc_types.h>
#include <nccport_browser_mem.h>

#define WSP_MALLOC  CRTL_malloc
#define WSP_FREE    CRTL_free

#define HDR_ERROR   -1

#define WSP_IS_SHORT_INTEGER(x)         ( (x) & 0x80 )
#define WSP_IS_LONG_INTEGER(x)          ( (x) <= 30 )
#define WSP_IS_QUOTED_LENGTH(x)         ( (x) == 0x1f)
#define WSP_IS_DATE_VALUE(x)            WSP_IS_LONG_INTEGER(x)
#define WSP_IS_INTEGER_VALUE(x)         (WSP_IS_SHORT_INTEGER(x) || WSP_IS_LONG_INTEGER(x))
#define WSP_IS_DELTA_SECONDS_VALUE(x)   WSP_IS_INTEGER_VALUE(x)

/* Text string == *TEXT 0x00, thus also an empty string matches the rule! */
#define WSP_IS_TEXT_STRING(x)           ( ((x) == 0) || ( ((x) >= 32) && ((x) <= 127)) )
#define WSP_IS_QUOTED_STRING(x)         ( (x) == 0x22 ) /* " */
#define WSP_IS_TOKEN_TEXT(x)            WSP_IS_TEXT_STRING(x)
#define WSP_IS_TEXT_VALUE(x)            WSP_IS_TEXT_STRING(x)
#define WSP_IS_URI_VALUE(x)             WSP_IS_TEXT_STRING(x)

/*header encoded value*/
#define     WSP_HDR_ACCEPT              0x00
#define     WSP_HDR_ACCEPT_CHARSET1     0x01
#define     WSP_HDR_ACCEPT_ENCODING1    0x02
#define     WSP_HDR_LANG                0x03
#define     WSP_HDR_RANGES              0x04
#define     WSP_HDR_AGE                 0x05
#define     WSP_HDR_ALLOW               0x06
#define     WSP_HDR_AUTHT               0x07
#define     WSP_HDR_CACHE_CONTROL1      0x08
#define     WSP_HDR_CONN                0x09
#define     WSP_HDR_CONT_BASE           0x0a
#define     WSP_HDR_CONT_EN             0x0b
#define     WSP_HDR_CONT_LANG           0x0c
#define     WSP_HDR_CONT_LENGTH         0x0d
#define     WSP_HDR_CONT_LOC            0x0e
#define     WSP_HDR_CONT_MD5            0x0f
#define     WSP_HDR_CONT_RANGE1         0x10
#define     WSP_HDR_CONT_TYPE           0x11
#define     WSP_HDR_DATE                0x12
#define     WSP_HDR_ETAG                0x13
#define     WSP_HDR_EXPIRES             0x14
#define     WSP_HDR_FROM                0x15
#define     WSP_HDR_HOST                0x16
#define     WSP_HDR_IF_MODIFY_SINCE     0x17
#define     WSP_HDR_IF_MATCH            0x18
#define     WSP_HDR_IF_NONE_MATCH       0x19
#define     WSP_HDR_IF_RANGE            0x1a
#define     WSP_HDR_IF_UNMODIFIED_SINCE 0x1b
#define     WSP_HDR_LOC                 0x1c
#define     WSP_HDR_LAST_MODIFY         0x1d
#define     WSP_HDR_MAX_FORWORD         0x1e
#define     WSP_HDR_PRAGMA              0x1f
#define     WSP_HDR_PROXY_AUTH          0x20
#define     WSP_HDR_PROXY_AUTHT         0x21
#define     WSP_HDR_PUBLIC              0x22
#define     WSP_HDR_RANGE               0x23
#define     WSP_HDR_PEFERER             0x24
#define     WSP_HDR_RETRY_AFTER         0x25
#define     WSP_HDR_SERVER              0x26
#define     WSP_HDR_TRANS_ENC           0x27
#define     WSP_HDR_UPGRADE             0x28
#define     WSP_HDR_UA                  0x29
#define     WSP_HDR_VARY                0x2a
#define     WSP_HDR_VIA                 0x2b
#define     WSP_HDR_WARNING             0x2c
#define     WSP_HDR_WWW_AUTH            0x2d
#define     WSP_HDR_CONT_DISPOSITION1   0x2e
#define     WSP_HDR_WAP_APP_ID          0x2f
#define     WSP_HDR_WAP_CONT_URL        0x30
#define     WSP_HDR_WAP_INIT_URL        0x31
#define     WSP_HDR_ACCEPT_APP          0x32
#define     WSP_HDR_BEARER_INDICATION   0x33
#define     WSP_HDR_PUSH_FLAG           0x34
#define     WSP_HDR_PROFILE             0x35
#define     WSP_HDR_PROFILE_DIFF        0x36
#define     WSP_HDR_PROFILE_WARNING1    0x37
#define     WSP_HDR_EXPECT              0x38
#define     WSP_HDR_TE                  0x39
#define     WSP_HDR_TRAILER             0x3a
#define     WSP_HDR_ACCEPT_CHARSET2     0x3b
#define     WSP_HDR_ACCEPT_ENCODING2    0x3c
#define     WSP_HDR_CACHE_CONTROL2      0x3d
#define     WSP_HDR_CONT_RANGE2         0x3e
#define     WSP_HDR_WAP_TOD             0x3f
#define     WSP_HDR_CONT_ID             0x40
#define     WSP_HDR_SET_COOKIE          0x41
#define     WSP_HDR_COOKIE              0x42
#define     WSP_HDR_ENC_VER             0x43
#define     WSP_HDR_PROFILE_WARNING2    0x44
#define     WSP_HDR_CONT_DISPOSITION2   0x45
#define     WSP_HDR_WAP_SECURITY        0x46
#define     WSP_HDR_CACHE_CONTROL3      0x47

/*content type encoded value*/
#define     WSP_CT_ALL_ALL                  0x00
#define     WSP_CT_TXT_ALL                  0x01
#define     WSP_CT_HTML                     0x02
#define     WSP_CT_PLIAN                    0x03
#define     WSP_CT_HDML                     0x04
#define     WSP_CT_TTML                     0x05
#define     WSP_CT_VCANLENDER               0x06
#define     WSP_CT_VCARD                    0x07
#define     WSP_CT_WAP_WML                  0x08
#define     WSP_CT_WAP_WML_SCRIPT           0x09
#define     WSP_CT_WAP_CATC                 0x0a
#define     WSP_CT_MULTIPART_ALL            0x0b
#define     WSP_CT_MULTIPART_MIXED          0x0c
#define     WSP_CT_MULTIPART_FORM_DATA      0x0d
#define     WSP_CT_MULTIPART_BYTERANGES     0x0e
#define     WSP_CT_MULTIPART_ALTERNATIVE    0x0f
#define     WSP_CT_APP_ALL                  0x10
#define     WSP_CT_VM                       0x11
#define     WSP_CT_WWW_FORM_URLENCODED      0x12
#define     WSP_CT_HDMLC                    0x13
#define     WSP_CT_WMLC                     0x14
#define     WSP_CT_WML_SCRIPTC              0x15
#define     WSP_CT_WSIC                     0x16
#define     WSP_CT_UAPROF                   0x17
#define     WSP_CT_WTLS_CA_CERT             0x18
#define     WSP_CT_WTLS_USER_CERT           0x19
#define     WSP_CT_X509_CA_CERT             0x1a
#define     WSP_CT_X509_USER_CERT           0x1b
#define     WSP_CT_IMG_ALL                  0x1c
#define     WSP_CT_GIF                      0x1d
#define     WSP_CT_JPEG                     0x1e
#define     WSP_CT_TIFF                     0x1f
#define     WSP_CT_PNG                      0x20
#define     WSP_CT_WBMP                     0x21
#define     WSP_CT_WAP_MULTIPART_ALL        0x22
#define     WSP_CT_WAP_MULTIPART_MIXED      0x23
#define     WSP_CT_WAP_MULTIPART_FORM_DATA  0x24
#define     WSP_CT_WAP_MULTIPART_BYTERANGES 0x25
#define     WSP_CT_WAP_MULTIPART_ALTER      0x26
#define     WSP_CT_APP_XML                  0x27
#define     WSP_CT_TXT_XML                  0x28
#define     WSP_CT_WB                       0x29
#define     WSP_CT_X968_CROSS_CERT          0x2a
#define     WSP_CT_X968_CA_CERT             0x2b
#define     WSP_CT_X968_USER_CERT           0x2c
#define     WSP_CT_SI                       0x2d
#define     WSP_CT_SIC                      0x2e
#define     WSP_CT_SL                       0x2f
#define     WSP_CT_SLC                      0x30
#define     WSP_CT_CO                       0x31
#define     WSP_CT_COC                      0x32
#define     WSP_CT_WAP_MULTIPART_RELATED    0x33
#define     WSP_CT_SIA                      0x34
#define     WSP_CT_CONN_XML                 0x35
#define     WSP_CT_CONN_WB                  0x36
#define     WSP_CT_PKCS7                    0x37
#define     WSP_CT_HASH_CERT                0x38
#define     WSP_CT_SIGNED_CERT              0x39
#define     WSP_CT_CERT_RESP                0x3a
#define     WSP_CT_XHTML_XML                0x3b
#define     WSP_CT_WML_XML                  0x3c
#define     WSP_CT_CSS                      0x3d
#define     WSP_CT_MMS                      0x3e
#define     WSP_CT_ROLLOVER_CERT            0x3f
#define     WSP_CT_LOCC_WB                  0x40
#define     WSP_CT_LOC_XML                  0x41
#define     WSP_CT_SYNCML_WBXML             0x42
#define     WSP_CT_SYNCML_XML               0x43
#define     WSP_CT_SYNCML_NOTIF             0x44
#define     WSP_CT_XHTML_XML_WAP            0x45
#define     WSP_CT_WV_CSP_CIR               0x46
#define     WSP_CT_OMA_DD_XML               0x47
#define     WSP_CT_OMA_DRM_MESSAGE          0x48
#define     WSP_CT_OMA_DRM_CONTENT          0x49
#define     WSP_CT_OMA_DRM_RIGHTS_XML       0x4a
#define     WSP_CT_OMA_DRM_RIGHTS_WB        0x4b
#define     WSP_CT_WV_CSP_XML               0x4c
#define     WSP_CT_WV_CSP_WB                0x4d

/*charset index value*/
#define     WSP_CS_ALL                      0x00
#define     WSP_CS_01                       0x01
#define     WSP_CS_02                       0x02
#define     WSP_CS_BIG5                     0x10
#define     WSP_CS_ISO10646_US2             0x0f
#define     WSP_CS_ISO1                     0x04
#define     WSP_CS_ISO2                     0x05
#define     WSP_CS_ISO3                     0x06
#define     WSP_CS_ISO4                     0x07
#define     WSP_CS_ISO5                     0x08
#define     WSP_CS_ISO6                     0x09
#define     WSP_CS_ISO7                     0x0a
#define     WSP_CS_ISO8                     0x0b
#define     WSP_CS_ISO9                     0x0c
#define     WSP_CS_SHIFT_JIS                0x0d
#define     WSP_CS_ASCII                    0x03
#define     WSP_CS_UTF8                     0x0e

#define WSP_RES_STAT_RESERVED                            0x00
#define WSP_RES_STAT_CONTINUE                            0x10
#define WSP_RES_STAT_SWITCHING_PROTOCOLS     0x11
#define WSP_RES_STAT_OK                                         0x20
#define WSP_RES_STAT_PARTIAL_CONTENT              0x26
#define WSP_RES_STAT_MULTIPLE_CHOICES             0x30
#define WSP_RES_STAT_TEMPORARY_REDIRECT        0x37
#define WSP_RES_STAT_BAD_REQUEST                     0x40
#define WSP_RES_STAT_UNSUPPORTED_MEDIA_TYPE 0x4F
#define WSP_RES_STAT_RANGE_ERROR                    0x50
#define WSP_RES_STAT_EXPECTATION_FAILED       0x51
#define WSP_RES_STAT_SERVER_ERROR                   0x60
#define WSP_RES_STAT_VERSION_ERROR                 0x65

/* parameter encode value */
#define WSP_PAR_Q 0x00
#define WSP_PAR_CHARSET 0x01
#define WSP_PAR_LEVEL 0x02
#define WSP_PAR_TYPE1 0x03
#define WSP_PAR_NAME1 0x05
#define WSP_PAR_FILENAME1 0x06
#define WSP_PAR_DIFFERENCES 0x07
#define WSP_PAR_PADDING 0x08
#define WSP_PAR_TYPE2 0x09
#define WSP_PAR_START1 0x0A
#define WSP_PAR_STARTINFO1 0x0B
#define WSP_PAR_COMMENT1 0x0C
#define WSP_PAR_DOMAIN1 0x0D
#define WSP_PAR_MAXAGE 0x0E
#define WSP_PAR_PATH1 0x0F
#define WSP_PAR_SECURE 0x10
#define WSP_PAR_SEC 0x11
#define WSP_PAR_MAC 0x12
#define WSP_PAR_CREATIONDATE 0x13
#define WSP_PAR_MODIFICATIONDATE 0x14
#define WSP_PAR_READDATE 0x15
#define WSP_PAR_SIZE 0x16
#define WSP_PAR_NAME2 0x17
#define WSP_PAR_FILENAME2 0x18
#define WSP_PAR_START2 0x19
#define WSP_PAR_STARTINFO2 0x1A
#define WSP_PAR_COMMENT2 0x1B
#define WSP_PAR_DOMAIN2 0x1C
#define WSP_PAR_PATH2 0x1D

/**
 * Get the length of string.
 * \param *pStr The pointer of the string pdu.
 * \param pduLen The length of the string pdu.
 * \return
 *      -If successful,then return#The length of string pdu.
 *      -If unsuccessful,then return#.
 */
int32_t wsp_strlen(int8_t *pStr);

/**
 * Get Integer-Value.
 * \param **buf The pointer of pdu.
 * \param *len The length of pdu.
 * \param *value The value of Integer-value.
 * \return
 *      -If successful,then return the length of Integer-Value.
 *      -If unsuccessful,then return#HDR_ERROR
 */
int32_t wsp_getIntValue(uint8_t **buf,int32_t *len,int32_t *value);

/**
 * Get the value of uintvar(variable length unsigned integer).
 * \param **chvalue The pointer of the pdu.
 * \param *chlen The length of the pdu.
 * \param *value The value of uintvar(variable length unsigned integer).
 * \return
 *      -If successful,then return#the bytes of uintvar.
 *      -If unsuccessful,then return#HDR_ERROR
 */
int32_t wsp_expandUintVar (uint8_t **chvalue,uint32_t *chlen,uint32_t * value);

/**
 * Allocate storage space for a copy of str and then copies str to the allocated space.
 * \param str Null-terminated source string
 * \return
 *      -a pointer to the storage location for the copied string when success
 *      -NULL if storage cannot be allocated
 */
uint8_t *wsp_strdup(uint8_t *str);

#ifdef __cplusplus
}
#endif

#endif /* __WSP_CODE_H__ */
