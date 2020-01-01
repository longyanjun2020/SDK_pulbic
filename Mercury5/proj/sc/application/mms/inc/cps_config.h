
/**
 * @file
 * NCC mms composer config
 *
 * config macros of the NCC mms
 *
 */

#ifndef __CPS_CONFIG_H__
#define __CPS_CONFIG_H__

#include <ncc_types.h>

#ifdef __cplusplus
extern "C" {
#endif

/* System Config Info ,can be config by the user's require */
#define CPS_MAX_TEXT_LENGTH_PERSLIDE                         0xFA0    /**< the max byte number of every slide can support  */
#define CPS_MAX_SIZE                                         0xC800   /**<the max size of the mms (50*1024) */

#define COMPOSER_DEFAULT_MEDIA_BEGIN                         0x0        /**< the beginning time of every media */
#define COMPOSER_DEFAULT_MEDIA_END                           0xBB8    /**<the ending time of every media*/

#define CPS_USE_MEMORY_COPY

#ifdef __cplusplus
}
#endif

#endif /* __CPS_CONFIG_H__ */
