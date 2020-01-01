
/**
 * @file
 * History record config interfaces.
 */

#ifndef __CFG_HISTORY_H__
#define __CFG_HISTORY_H__

#include <cfg_internal.h>

#ifdef __cplusplus
extern "C"{
#endif

/**
 * Get one total history records number and current start index from browser running config
 * \param   pBrowserConfig  Pointer to Browser running config structure.
 * \param   pIndex          Pointer to start index of the history record array in browser running config
 * \return  total number of history records
 */
int32_t cfg_getHistoryCount(T_BROWSERCONFIG *pBrowserConfig);

/**
 * Get one history record according to the index given from browser running config
 * \param   pBrowserConfig  Pointer to Browser running config structure.
 * \param   pIndex          Pointer to start index of the history record array in browser running config
 * \param   ppWebsite       Pointer to pointer to the website of a history item.
 * \return  <ul>
 *              <li> TRUE   if sucessful.
 *              <li> FALSE  if failed.
 *          </ul>
 *
 * \attention   Here ppWebsite is used to point to the address, don't give address of an array.
 */
int32_t cfg_getHistoryItem(T_BROWSERCONFIG *pBrowserConfig,
                                int32_t index,
								int8_t **ppName,
                                int8_t **pWebsite);
/**
 * Add one history record into browser running config
 * \param   pBrowserConfig  Pointer to Browser running config structure.
 * \param   ppWebsite       Pointer to pointer to the website of a history item.
 * \return  <ul>
 *              <li> TRUE   if sucessful.
 *              <li> FALSE  if failed.
 *          </ul>
 */
int32_t cfg_addHistoryItem(T_BROWSERCONFIG *pBrowserConfig,
								int8_t *pName,
                                int8_t *pWebsite);
/**
 * Clear all history records in browser running config
 * \param   pBrowserConfig  Pointer to Browser running config structure.
 */

int32_t cfg_deleteHistoryItem(T_BROWSERCONFIG *pBrowserConfig, int32_t index);

void cfg_clearHistoryItems(T_BROWSERCONFIG *pBrowserConfig);

void cfg_freeHistorys(T_BROWSERCONFIG *pBrowserConfig);

int32_t cfg_backupHistory(T_BROWSERCONFIG *pBrowserConfig);

int32_t cfg_restoreHistory(T_BROWSERCONFIG *pBrowserConfig);

void cfg_freeBackupHistory();

#ifdef __cplusplus
}
#endif

#endif /* __CFG_HISTORY_H__ */
