
#ifndef __MULTIPART_TEXTUNPACK_H__
#define __MULTIPART_TEXTUNPACK_H__

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

#include <nccmultipart.h>
#include <multipart_innerapi.h>

#define MULTIPART_BODY 1
#define MULTIPART_PART 2

#define CONTENT_TYPE_LEN 8

/**
 * Parse one Line of multipart head.
 * \param pbp pointer of a part or a body.
 * \param pLine
 * \param pbpType show type of php. MULTIPART_BODY : body; MULTIPART_PART : part
 * \return
 *      -TRUE when success
 *      -FALSE when fail
 */
int32_t multipart_parseHeaderLine(T_Multipart_BodyOrPart *pbp, int8_t *pLine, int32_t pbpType);

/**
 * Add extra header to a part or a body
 * \param pbp pointer of a part or a body
 * \param value extra content
 * \return
 *      -TRUE when add successfully
 *      -FALSE when fail
 */
int32_t multipart_addExtraHeadField(T_Multipart_BodyOrPart *pbp, int8_t *value);

/**
 * Split input value of header field
 * \param extraHeader pointer of a extra header
 * \param fieldValue value of the header field
 * \return
 *      -TRUE when success
 *      -FALSE when fail
 */
int32_t multipart_splitHeaderField(T_Multipart_ExtraHeader *extraHeader, int8_t *fieldValue);

/**
 * Paser body or part header
 * \param pMultipart structure of body or part, to save the headers
 * \param pData headers data
 * \param type body or part, possible value is:
 *                                                  MULTIPART_BODY,
 *                                                  MULTIPART_PART
 * \return
 *      -TRUE when success
 *      -FALSE when fail
 */
int32_t multipart_parseEachHeader(T_Multipart_BodyOrPart * pMultipart, uint8_t * pData, int32_t type);

/**
 * Decode content to binary
 * \param pPart structure of part, input the content-transfer-encoding value, output binary content
 * \param pData encoding content data
 * \param dataLen content data length
 * \return
 *      -TRUE when success
 *      -FALSE when fail
 */
int32_t multipart_decodeContent(T_Multipart_BodyOrPart * pPart, uint8_t * pData, int32_t dataLen);

/**
 * Unpack text plain format multipart data
 * \param pData text plain format data
 * \param dataLen data length
 * \return
 *      -when success, return the first body structure
 *      -when failed, return NULL
 */
T_Multipart_BodyOrPart * multipart_textUnPack(uint8_t * pData, int32_t dataLen);

/**
 * Returns a pointer to the first occurrence of strSearch in the len area in str.
 * \param str Null-terminated string to search
 * \param strSearch Null-terminated string to search for
 * \param len number of characters to be searched
 * \return
 *      -when success, return a pointer to the first occurrence of strSearch in str
 *      -when failed, return NULL
 */
uint8_t * multipart_strnstr(uint8_t * str, uint8_t * strSearch, int32_t len);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* __MULTIPART_TEXTUNPACK_H__ */
