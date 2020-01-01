
#ifndef   __IFLAYER_DLCSS_H__
#define   __IFLAYER_DLCSS_H__

#include <ncc_types.h>

/**
 * Query to download css file.
 * \return
 */
void iflayer_dlCheckCss(void);

/**
 * Check contentType whether it is css file.
 * \param  contentType
 * \return  <ul>
 *          <li>TRUE</li>
 *          <li>FALSE</li>
 *          </ul>
 */
int32_t iflayer_isCss(int8_t * contentType);


#endif
