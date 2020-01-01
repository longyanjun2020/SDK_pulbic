
#ifndef  __IFLAYER_DLBGSOUND_H__
#define  __IFLAYER_DLBGSOUND_H__

#include <ncc_types.h>

/**
 * Query to download BgSound file.
 * \return
 */
void iflayer_dlCheckBgSound(void);

/**
 * Check contentType whether it is bgsound.
 * \param contentType
 * \return  <ul>
 *          <li>TRUE</li>
 *          <li>FALSE</li>
 *          </ul>
 */
int32_t iflayer_isBgSound(int8_t * contentType);

#endif
