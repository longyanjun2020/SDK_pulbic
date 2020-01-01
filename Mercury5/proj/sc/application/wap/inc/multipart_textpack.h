
#ifndef __MULTIPART_TEXTPACK_H__
#define __MULTIPART_TEXTPACK_H__

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

#include <nccmultipart.h>
#include <multipart_innerapi.h>

/**
 * Collect all data and pack into a plaintext format multipart package.
 * \param pBody pointer of the first body in multipart link
 * \return
 *      -pointer of T_Multipart_Buffer structure when success
 *      -NULL when fail
 */
T_Multipart_Buffer *multipart_textPack(T_Multipart_BodyOrPart *pBody);

/**
 * Collect all data and pack into a multipart package.
 * \param pBody pointer of the first body in multipart link
 * \param buffer store multipart package
 * \return
 *      -TRUE when success
 *      -FALSE when fail
 */
int32_t multipart_collectTextData(T_Multipart_BodyOrPart *pBody, T_Multipart_Buffer *pBuffer);

/**
 * Add header content to buffer.
 * \param pbp pointer of a part or a body
 * \param pBuffer pointer of T_Multipart_Buffer structure
 * \return
 *      -TRUE when success
 *      -FALSE when fail
 */
int32_t multipart_collectTextHeader(T_Multipart_BodyOrPart *pbp, T_Multipart_Buffer *pBuffer);

/**
 * Add extra header content to buffer.
 * \param pbp pointer of a part or a body
 * \param pBuffer pointer of T_Multipart_Buffer structure
 * \return
 *      -TRUE when success
 *      -FALSE when fail
 */
int32_t multipart_collectTextExtraHeader(T_Multipart_BodyOrPart *pbp, T_Multipart_Buffer *pBuffer);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* __MULTIPART_TEXTPACK_H__ */
