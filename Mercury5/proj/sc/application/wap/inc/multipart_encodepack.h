
#ifndef __MULTIPART_ENCODEPACK_H__
#define __MULTIPART_ENCODEPACK_H__

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

#include <nccmultipart.h>
#include <multipart_innerapi.h>

/**
 * Collect all data and pack into a encode format multipart package.
 * \param pBody pointer of the first body in multipart link
 * \return
 *      -pointer of T_Multipart_Buffer structure when success
 *      -NULL when fail
 */
T_Multipart_Buffer *multipart_encodePack(T_Multipart_BodyOrPart *pBody);

/**
 * Collect all data and pack into a multipart package.
 * \param pBody pointer of the first body in multipart link
 * \param pBuffer store multipart package
 * \return
 *      -TRUE when success
 *      -FALSE when fail
 */
int32_t multipart_collectEncodeData(T_Multipart_BodyOrPart *pBody, T_Multipart_Buffer *pBuffer);

/**
 * Add header content to buffer.
 * \param pbp pointer of a part or a body
 * \param pBuffer pointer of T_Multipart_Buffer structure
 * \return
 *      -TRUE when success
 *      -FALSE when fail
 */
int32_t multipart_collectEncodeHeader(T_Multipart_BodyOrPart *pbp, T_Multipart_Buffer *pBuffer);

/**
 * Add extra header content to buffer.
 * \param value pointer of a extraheader's value
 * \param pBuffer pointer of T_Multipart_Buffer structure
 * \return
 *      -TRUE when success
 *      -FALSE when fail
 */
int32_t multipart_collectEncodeExtraHeader(uint8_t *value, T_Multipart_Buffer *pBuffer);

/**
 * Add parameters to buffer.
 * \param param      parameters to be added
 * \param pBuffer    pointer of T_Multipart_Buffer structure
 * \return
 *      -TRUE when success
 *      -FALSE when fail
 */
int32_t multipart_collectEncodeParam(uint8_t *param, T_Multipart_Buffer *pBuffer);

/**
 * Convert the uint value to octets.
 * \param chvalue pointer of store space
 * \param value the uint's value
 * \return
 *      -the number of octets
 */
int8_t multipart_compactUintvar (uint8_t * chvalue,int32_t value);

/**
 * Add each header field's content to buffer.
 * \param pbp pointer of a body or a part
 * \param pBufffer pointer of T_Multipart_Buffer structure
 * \param headerType type of the header field
 * \return
 *      -TRUE when success
 *      -FALSE when fail
 */
int32_t multipart_collectHeaderField(T_Multipart_BodyOrPart *pbp,
                                     T_Multipart_Buffer *pBuffer,
                                     T_MULTIPART_HEADER_TYPES headerType);

/**
 * Split every extra header's name value and params.
 * \param extraHeader The structure pointer of extra header
 * \param value A extra header string
 * \param len The value's length
 * \return
 *      -TRUE when success
 *      -FALSE when fail
 */
int32_t multipart_splitExtraHeaderNameValueParam(T_Multipart_ExtraHeader * extraHeader,
                                                 uint8_t * value,
                                                 int32_t len);

/**
 * Split each extra header to a structure list.
 * \param value The string of extra header, include name, value and params
 * \return
 *      -A structure header pointer, when success
 *      -NULL, when fail
 */
T_Multipart_ExtraHeader * multipart_splitEachExtraHeader(uint8_t * value);

/**
 * Encode well-known header field.
 * \param pBuffer pointer to T_Multipart_Buffer structure
 * \param value value of this header
 * \param param pointer to the parameter of this header
 * \param headerType type of the header
 * \return
 *      -TRUE when success
 *      -FALSE when fail
 */
int32_t multipart_encodeWellKnownHeader(T_Multipart_Buffer *pBuffer, int8_t *value, int8_t *param, int32_t headerType);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* __MULTIPART_ENCODEPACK_H__ */
