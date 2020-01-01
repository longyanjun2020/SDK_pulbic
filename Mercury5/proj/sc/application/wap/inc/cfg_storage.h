
/**
 * @file
 * Storage operation interfaces for config file.
 */

#ifndef __CFG_STORAGE_H__
#define __CFG_STORAGE_H__

#include <nccport_browser_mem.h> /**< for realloc operations */
#include <cfg_internal.h>

#ifdef __cplusplus
extern "C"{
#endif

/**
 * Open config file and init Browser running config.
 * \param   pBrowserConfig  Pointer to Browser running config structure.
 * \return  <ul>
 *              <li> pointer to a address of string if sucessful.
 *              <li> NULL if failed.
 *          </ul>
 */
T_BROWSERCONFIG * cfg_initBrowserConfig(int8_t * fileName);

/**
 * Save browser running config to config file.
 * \param   pBrowserConfig  Pointer to Browser running config structure.
 * \param   fileName        File name which config is saved to.
 * \return  <ul>
 *              <li> TRUE   if sucessful.
 *              <li> FALSE  if failed.
 *          </ul>
 */
int32_t cfg_saveBrowserConfig(T_BROWSERCONFIG *pBrowserConfig, int8_t * fileName);

/**
 * Free all memory which are malloc() for browser running config.
 * \param   pBrowserConfig  Pointer to Browser running config structure.
 */
void cfg_destroyBrowserConfig(T_BROWSERCONFIG *pBrowserConfig);

/**
 * Copy all history records saved in browser running config into a storage buffer.
 * \param   pStorageBuf     Storage buffer
 * \param   pBrowserConfig  Pointer to Browser running config structure.
 * \return  Length of history records
 */
int32_t copyHistories2StorageBuf(int8_t *pStorageBuf, T_BROWSERCONFIG *pBrowserConfig);

/**
 * Copy all bookmarks saved in browser running config into a storage buffer.
 * \param   pStorageBuf     Storage buffer
 * \param   pBrowserConfig  Pointer to Browser running config structure.
 * \return  Length of bookmarks
 */
int32_t copyBookmark2StorageBuf(int8_t *pStorageBuf, T_BROWSERCONFIG *pBrowserConfig);

/**
 * Copy all protocol setting saved in browser running config into a storage buffer.
 * \param   pStorageBuf     Storage buffer
 * \param   pBrowserConfig  Pointer to Browser running config structure.
 * \return  Length of protocol setting
 */
int32_t copyProtocolHeader2StorageBuf(int8_t *pStorageBuf, T_BROWSERCONFIG *pBrowserConfig);

/**
 * Restore the default config.
 * \param   pBrowserConfig  Pointer to Browser running config structure.
 */
void cfg_restoreDefaultCfg(T_BROWSERCONFIG *pBrowserconfig);

#ifdef __cplusplus
}
#endif

#endif /* __CFG_STORAGE_H__ */
