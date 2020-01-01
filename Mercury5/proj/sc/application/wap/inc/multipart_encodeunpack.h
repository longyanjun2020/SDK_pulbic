
#ifndef __MULTIPART_ENCODEUNPACK_H__
#define __MULTIPART_ENCODEUNPACK_H__

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

#include <nccmultipart.h>
#include <multipart_innerapi.h>
#include <nccwsp.h>

/**
 * Parse encoded multipart package.
 * \param pM pointer to multipart package
 * \param packLen length of the multipart package
 * \return
 *      -Pointer of multipart Body when success
 *      -NULL when fail
 */
T_Multipart_BodyOrPart *multipart_encodeUnPack(uint8_t *pM, int32_t packLen);

/**
 * Parse parameter.
 * \param param pointer to parameter
 * \return
 *      -Pointer to parameter strcuture when success
 *      -NULL when fail
 */
T_Multipart_Parameter *multipart_parseEncodeParam(uint8_t *param);

/**
 * Decode octets to uint value.
 * \param pOctets the Octets's pointer
 * \return the uint32_t  value
 */
uint32_t multipart_octetsToUintvar(uint8_t **pOctets);

/**
 * Parse one field in header.
 * \param pack pointer to encoded package
 * \param packLen length of the package
 * \param length [out] record length of the field
 * \param pbp [out] pointer to pointer of a multipart body or part
 * \return
 *      -TRUE when parse successfully
 *      -FALSE when fail
 */
int32_t multipart_parseOneHeaderField(uint8_t *pack, uint32_t packLen, uint32_t *length, T_Multipart_BodyOrPart **pbp);

/**
 * Copy T_HEADER_PARAM structure's data to T_Multipart_Parameter structure.
 * \param pSrcParam pointer to the T_HEADER_PARAM structure
 * \return
 *      -pointer of T_Multipart_Parameter structure when success
 *      -NULL when fail
 */
T_Multipart_Parameter *multipart_copyAParameter(T_HEADER_PARAM *pSrcParam);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* __MULTIPART_ENCODEUNPACK_H__ */
