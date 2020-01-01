
/**
 * @file
 * Bookmark config interfaces.
 */

#ifndef __CVS_CFG_BOOKMARK_H__
#define __CVS_CFG_BOOKMARK_H__

#include <cfg_internal.h>

#ifdef __cplusplus
extern "C"{
#endif

/**
 * Get total favorte items number from browser running config.
 * \param   pBrowserConfig Pointer to Browser running config structure.
 * \return  total number of favorte items.
 */
int32_t cfg_getFavoriteCount(T_BROWSERCONFIG *pBrowserConfig);

/**
 * Get one Favorte item according to the index given from browser running config.
 * \param   pBrowserConfig  Pointer to Browser running config structure.
 * \param   index           Index of the favorite items array in browser running config.
 * \param   ppName          Pointer to pointer to the name of a favorite item.
 * \param   ppWebsite       Pointer to pointer to the website of a favorite item.
 * \return  <ul>
 *              <li> TRUE   if sucessful.
 *              <li> FALSE  if failed.
 *          </ul>
 * \attention   Here ppName and ppWebsite is used to point to the address, don't give address of an array.
 */
int32_t cfg_getFavoriteItem(T_BROWSERCONFIG *pBrowserConfig,
                                int32_t index,
                                int8_t **ppName,
                                int8_t **ppWebsite);
/**
 * Add one Favorte item into browser running config.
 * \param   pBrowserConfig  Pointer to Browser running config structure.
 * \param   pName           Pointer to the name which will be saved.
 * \param   pWebsite        Pointer to the website which will be saved.
 * \return  <ul>
 *              <li> TRUE   if sucessful.
 *              <li> FALSE  if failed.
 *          </ul>
 */
int32_t cfg_addFavoriteItem(T_BROWSERCONFIG *pBrowserConfig,
                                int8_t *pName,
                                int8_t *pWebsite);

/**
 * Change one Favorte item which have saved in browser running config.
 * \param   pBrowserConfig  Pointer to Browser running config structure.
 * \param   index           Index of the favorite items array in browser running config.
 * \param   pName           Pointer to the name which will be changed.
 * \param   pWebsite        Pointer to the website which will be changed.
 * \return  <ul>
 *              <li> TRUE   if sucessful.
 *              <li> FALSE  if failed.
 *          </ul>
 */
int32_t cfg_changeFavoriteItem(T_BROWSERCONFIG *pBrowserConfig,
                                int32_t index,
                                int8_t *pName,
                                int8_t *pWebsite);

/**
 * Delete one Favorte item which have saved in browser running config.
 *
 * \param   pBrowserConfig  Pointer to Browser running config structure.
 * \param   index           Index of the favorite items array in browser running config.
 * \return  <ul>
 *              <li> TRUE   if sucessful.
 *              <li> FALSE  if failed.
 *          </ul>
 */
int32_t cfg_deleteFavoriteItem(T_BROWSERCONFIG *pBrowserConfig,
                                int32_t index);

/**
 * Set some fixed Favorte items which may be provided by ISP into browser running config.
 * \param   pBrowserConfig  Pointer to Browser running config structure.
 * \return  <ul>
 *              <li> TRUE   if sucessful.
 *              <li> FALSE  if failed.
 *          </ul>
 */
int32_t cfg_fitFixedFavorites(T_BROWSERCONFIG *pBrowserConfig);

/**
 * Free all Favorte items which have malloc in browser running config.
 *
 * \param   pBrowserConfig  Pointer to Browser running config structure.
 * \return
 */
void cfg_freeFavorites(T_BROWSERCONFIG *pBrowserConfig);

int32_t cfg_backupFavorite(T_BROWSERCONFIG *pBrowserConfig);

int32_t cfg_restoreFavorite(T_BROWSERCONFIG *pBrowserConfig);

void cfg_freeBackupFavorites();

#ifdef __cplusplus
}
#endif

#endif /* __CFG_BOOKMARK_H__ */
