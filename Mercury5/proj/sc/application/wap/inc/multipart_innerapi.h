
#ifndef __MULTIPART_INNERAPI_H__
#define __MULTIPART_INNERAPI_H__

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

#include <nccmultipart.h>

#define MULTIPART_SKIPWHITESPACE(bp)    while( (*(bp) == ' ')       \
                                            || (*(bp) == '\t')      \
                                            || (*(bp) == '\r')      \
                                            || (*(bp) == '\n') )    \
                                                bp++
#define MULTIPART_PARATAIL(bp)  while( (*bp != '\0')                \
                                    && (*bp != ';') )               \
                                        bp++
#define EQUALSCASE(str1, str2, n)   !CRTL_strnicmp(str1, str2, n)
#define MULTIPART_SKIPSEMICOLON(bp) while( (*(bp) == ' ')           \
                                        || (*(bp) == ';') )         \
                                            bp++
#define MULTIPART_FRONTQUOTATIONMARK(bp) while(*bp != '"')          \
                                            bp++
#define MULTIPART_BACKQUOTATIONMARK(bp) while(*bp != '"')           \
                                            bp--

#define FIRST_MALLOC_SIZE 10240 /* 10K */
#define GROW_STEP 5120 /* 5K */
#define BOUNDARY_LEN 29
#define HEADER_GROW_STEP 1024 /* 1K */

#define MULTIPART_STR_ALTERNATIVE "multipart/alternative"
#define MULTIPART_STR_MIXED "multipart/mixed"
#define MULTIPART_STR_FORMDATA "multipart/form-data"
#define MULTIPART_STR_DIGEST "multipart/digest"
#define MULTIPART_STR_PARALLEL "multipart/parallel"
#define MULTIPART_STR_RELATED "multipart/related"
#define MULTIPART_STR_VND_MIXED "application/vnd.wap.multipart.mixed"
#define MULTIPART_STR_VND_RELATED "application/vnd.wap.multipart.related"
#define MULTIPART_STR_VND_ALTERNATIVE "application/vnd.wap.multipart.alertnative"
#define MULTIPART_STR_BASE64 "base64"
#define MULTIPART_STR_QP "quoted-printable"
#define MULTIPART_STR_8BIT "8bit"
#define MULTIPART_STR_7BIT "7bit"
#define MULTIPART_STR_BINARY "binary"
#define MULTIPART_STR_NEWLINE1 "\r\n"
#define MULTIPART_STR_NEWLINE12 "\n"
#define MULTIPART_STR_NEWLINE2 "--\r\n"
#define MULTIPART_STR_NEWLINE3 "\r\n\r\n"
#define MULTIPART_STR_NEWLINE32 "\n\n"

#define MULTIPART_STR_TWO_SHORT_LINE "--"
#define MULTIPART_STR_CONTENT_TYPE1 "Content-Type: "
#define MULTIPART_STR_CONTENT_DISPOSITION1 "Content-Disposition: "
#define MULTIPART_STR_CONTENT_TRAN_ENCODING1 "Content-Transfer-Encoding: "
#define MULTIPART_STR_CONTENT_ID1 "Content-ID: "
#define MULTIPART_STR_CONTENT_DESCRIPTION1 "Content-Description: "
#define MULTIPART_STR_CONTENT_TYPE2 "Content-Type:"
#define MULTIPART_STR_CONTENT_DISPOSITION2 "Content-Disposition:"
#define MULTIPART_STR_CONTENT_TRAN_ENCODING2 "Content-Transfer-Encoding:"
#define MULTIPART_STR_CONTENT_ID2 "Content-ID:"
#define MULTIPART_STR_CONTENT_DESCRIPTION2 "Content-Description:"
#define MULTIPART_STR_BASE_BOUNDARY "--=_Nextpart_01C2BCB0_00000.x"
#define MULTIPART_STR_BOUNDARY_EQUAL "boundary="
#define MULTIPART_STR_COLON ";"
#define MULTIPART_STR_DISPOSITION_FORMDATA "form-data"
#define MULTIPART_STR_DISPOSITION_ATTACHMENT "attachment"
#define MULTIPART_STR_DISPOSITION_INLINE "inline"

/* header encoded value */
#define     MULTIPART_HDR_ACCEPT              0x00
#define     MULTIPART_HDR_ACCEPint8_tSET1     0x01
#define     MULTIPART_HDR_ACCEPT_ENCODING1    0x02
#define     MULTIPART_HDR_LANG                    0x03
#define     MULTIPART_HDR_RANGES              0x04
#define     MULTIPART_HDR_AGE                 0x05
#define     MULTIPART_HDR_ALLOW               0x06
#define     MULTIPART_HDR_AUTHT               0x07
#define     MULTIPART_HDR_CACHE_CONTROL1      0x08
#define     MULTIPART_HDR_CONN                    0x09
#define     MULTIPART_HDR_CONT_BASE           0x0a
#define     MULTIPART_HDR_CONT_EN         0x0b
#define     MULTIPART_HDR_CONT_LANG       0x0c
#define     MULTIPART_HDR_CONT_LENGTH     0x0d
#define     MULTIPART_HDR_CONT_LOC            0x0e
#define     MULTIPART_HDR_CONT_MD5            0x0f
#define     MULTIPART_HDR_CONT_RANGE1     0x10
#define     MULTIPART_HDR_CONT_TYPE       0x11
#define     MULTIPART_HDR_DATE                0x12
#define     MULTIPART_HDR_ETAG                0x13
#define     MULTIPART_HDR_EXPIRES         0x14
#define     MULTIPART_HDR_FROM                0x15
#define     MULTIPART_HDR_HOST                0x16
#define     MULTIPART_HDR_IF_MODIFY_SINCE 0x17
#define     MULTIPART_HDR_IF_MATCH            0x18
#define     MULTIPART_HDR_IF_NONE_MATCH   0x19
#define     MULTIPART_HDR_IF_RANGE            0x1a
#define     MULTIPART_HDR_IF_UNMODIFIED_SINCE     0x1b
#define     MULTIPART_HDR_LOC             0x1c
#define     MULTIPART_HDR_LAST_MODIFY     0x1d
#define     MULTIPART_HDR_MAX_FORWORD 0x1e
#define     MULTIPART_HDR_PRAGMA          0x1f
#define     MULTIPART_HDR_PROXY_AUTH      0x20
#define     MULTIPART_HDR_PROXY_AUTHT     0x21
#define     MULTIPART_HDR_PUBLIC          0x22
#define     MULTIPART_HDR_RANGE           0x23
#define     MULTIPART_HDR_PEFERER         0x24
#define     MULTIPART_HDR_RETRY_AFTER     0x25
#define     MULTIPART_HDR_SERVER          0x26
#define     MULTIPART_HDR_TRANS_ENC       0x27
#define     MULTIPART_HDR_UPGRADE         0x28
#define     MULTIPART_HDR_UA              0x29
#define     MULTIPART_HDR_VARY                0x2a
#define     MULTIPART_HDR_VIA             0x2b
#define     MULTIPART_HDR_WARNING         0x2c
#define     MULTIPART_HDR_WWW_AUTH        0x2d
#define     MULTIPART_HDR_CONT_DISPOSITION1       0x2e
#define     MULTIPART_HDR_WAP_APP_ID      0x2f
#define     MULTIPART_HDR_WAP_CONT_URL    0x30
#define     MULTIPART_HDR_WAP_INIT_URL    0x31
#define     MULTIPART_HDR_ACCEPT_APP      0x32
#define     MULTIPART_HDR_BEARER_INDICATION       0x33
#define     MULTIPART_HDR_PUSH_FLAG       0x34
#define     MULTIPART_HDR_PROFILE         0x35
#define     MULTIPART_HDR_PROFILE_DIFF    0x36
#define     MULTIPART_HDR_PROFILE_WARNING1        0x37
#define     MULTIPART_HDR_EXPECT          0x38
#define     MULTIPART_HDR_TE              0x39
#define     MULTIPART_HDR_TRAILER         0x3a
#define     MULTIPART_HDR_ACCEPint8_tSET2 0x3b
#define     MULTIPART_HDR_ACCEPT_ENCODING2    0x3c
#define     MULTIPART_HDR_CACHE_CONTROL2  0x3d
#define     MULTIPART_HDR_CONT_RANGE2     0x3e
#define     MULTIPART_HDR_WAP_TOD         0x3f
#define     MULTIPART_HDR_CONT_ID         0x40
#define     MULTIPART_HDR_SET_COOKIE      0x41
#define     MULTIPART_HDR_COOKIE          0x42
#define     MULTIPART_HDR_ENC_VER         0x43
#define     MULTIPART_HDR_PROFILE_WARNING2    0x44
#define     MULTIPART_HDR_CONT_DISPOSITION2   0x45
#define     MULTIPART_HDR_WAP_SECURITY        0x46
#define     MULTIPART_HDR_CACHE_CONTROL3      0x47

/**
 * Check parameter's validity.
 * \param fieldType type of header field
 * \param fieldParamType type of parameter
 * \return
 *      -TRUE when the parameter is valid
 *      -FALSE when invalid
 */
int32_t multipart_judgeParam(uint32_t fieldType, uint32_t fieldParamType);

/**
 * Create an extra header.
 * \return
 *      -pointer of an extra header when create successfully
 *      -NULL when fail
 */
T_Multipart_ExtraHeader *multipart_initExtraHeader();

/**
 * To free an extra header.
 * \param extraHeader pointer of the extra header
 * \return
 *      -TRUE when free successfully
 *      -FALSE when fail
 */
int32_t multipart_freeExtraHeader(T_Multipart_ExtraHeader **extraHeader);

/**
 * To free an extra header list.
 * \param extraHeader A structure pointer of the extra header list
 * \return
 *      -TRUE when free successfully
 *      -FALSE when fail
 */
int32_t multipart_freeExtraHeaderList(T_Multipart_ExtraHeader **extraHeader);

/**
 * Free a body or a part.
 * \param pbp pointer of a body or a part which will be free.
 * \return
 *      -TRUE when free successfully
 *      -FALSE when fail
 */
int32_t multipart_freeBodyOrPart(T_Multipart_BodyOrPart **pbp);

/**
 * Allocate the size of a memory block.
 * \param size size in bytes
 * \return
 *      -a pointer to the allocated memory block when success
 *      -NULL if there is insufficient memory available
 */
void *multipart_malloc(int32_t size);

/**
 * Changes the size of an allocated memory block.
 * \param memblock pointer to previously allocated memory block
 * \param reSize new size in bytes
 * \return
 *      -a pointer to the reallocated (and possibly moved) memory block when success
 *      -NULL if there is insufficient memory available
 */
void *multipart_realloc(void *memblock, int32_t reSize);

/**
 * Free a pointer.
 * \param p a pointer
 * \return void
 */
void multipart_free(void **p);

/**
 * Allocate storage space for a copy of str and then copies str to the allocated space.
 * \param str Null-terminated source string
 * \return
 *      -a pointer to the storage location for the copied string when success
 *      -NULL if storage cannot be allocated
 */
uint8_t *multipart_strdup(uint8_t *str);

/**
 * Allocate storage space for a copy of str and then copies str to the allocated space.
 * \param str source string
 * \param len number of characters to be copied
 * \return
 *      -a pointer to the storage location for the copied string when success
 *      -NULL if storage cannot be allocated
 */
uint8_t *multipart_strndup(uint8_t *str, int32_t len);

/**
 * Append a string to T_Multipart_Buffer structure's buffer.
 * \param buf pointer to T_Multipart_Buffer structure
 * \param str source string
 * \param strLen length of the str
 * \return
 *      -TRUE when success
 *      -FALSE when fail
 */
int32_t multipart_strcat(T_Multipart_Buffer *buf, int8_t *str, int32_t strLen);

/**
 * Copies bytes to T_Multipart_Buffer structure's buffer.
 * \param buf pointer to T_Multipart_Buffer structure
 * \param src source string
 * \param srcLen length of the src
 * \return
 *      -TRUE when success
 *      -FALSE when fail
 */
int32_t multipart_memcpy(T_Multipart_Buffer *buf, int8_t *src, int32_t srcLen);

/**
 * Copies one byte to T_Multipart_Buffer structure's buffer.
 * \param buf pointer to T_Multipart_Buffer structure
 * \param data source byte
 * \return
 *      -TRUE when success
 *      -FALSE when fail
 */
int32_t multipart_addOneByte(T_Multipart_Buffer *buf, uint16_t data);

/**
 * Init a T_Multipart_Buffer structure.
 * \param bufferSize T_Multipart_Buffer structure's buffer size
 * \return
 *      -pointer to a T_Multipart_Buffer structure when success
 *      -NULL when fail
 */
T_Multipart_Buffer *multipart_initMulBuffer(int32_t bufferSize);

/**
 * Free T_Multipart_Buffer structure.
 * \param buffer pointer to pointer of T_Multipart_Buffer structure which will be freed
 * \return
 *      -TRUE when seccuss
 *      -FALSE when fail
 */
int32_t multipart_freeMulBuffer(T_Multipart_Buffer *buffer);

/**
 * Get a line's parameter name and value
 * \param pParam             a param structure pointer to save the name and value
 * \param string             a line string to parse
 * \return
 *      -TRUE when success
 *      -FALSE when fail
 */
int32_t multipart_getNameAndValue(T_Multipart_Parameter * pParam, uint8_t * string);

/**
 * Parse parameters to a structure list
 * \param param             parameters data
 * \return
 *      -when success, return the header pointer of the structure
 *      -when failed, return NULL
 */
T_Multipart_Parameter * multipart_parseTextParam(uint8_t * param);

/**
 * Generate a boundary
 * \return
 *      -pointer of boundary when success
 *      -NULL when fail
 */
int8_t *multipart_generateBoundary();

#define MULSTRCAT(buf, str, strLen) if(!multipart_strcat(buf, str, (strLen))) return FALSE
#define MULMEMCPY(buf, src, srcLen) if(!multipart_memcpy(buf, src, (srcLen))) return FALSE
#define MULADDONEBYTE(buf, data) if(!multipart_addOneByte(buf, data)) return FALSE
#define MULMEMCPY_FREEBUF(buf, src, srcLen, pTemp) if(!multipart_memcpy(buf, src, srcLen)){multipart_freeMulBuffer(pTemp); return FALSE;}
#define MULADDONEBYTE_FREEBUF(buf, data, pTemp) if(!multipart_addOneByte(buf, data)){multipart_freeMulBuffer(pTemp); return FALSE;}

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* __MULTIPART_INNERAPI_H__ */
