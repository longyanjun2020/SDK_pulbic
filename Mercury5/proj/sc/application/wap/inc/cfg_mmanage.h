
/**
 * @file
 * Config memory manage interfaces.
 */

#ifndef __CVS_CFG_MEMORYMANAGE_H__
#define __CVS_CFG_MEMORYMANAGE_H__

#include <cfg_internal.h>

#ifdef __cplusplus
extern "C"{
#endif

/**
 * Malloc a new memory and copy the pointed string into it.
 * \param   pBrowserConfig  Pointer to Browser running config structure.
 * \param   pSrc            Pointer to a string.
 * \return  <ul>
 *              <li> pointer to a address of string if sucessful.
 *              <li> NULL if failed.
 *          </ul>

 * \attention   pBrowserConfig has a member which is used to count the memory size.
 */
int8_t *cfg_safeStrdup(T_BROWSERCONFIG *pBrowserConfig, int8_t *pSrc);

/**
 * Malloc a new memory and copy the pointed string into it.
 * \param   pBrowserConfig  Pointer to Browser running config structure.
 * \param   pSrc            Pointer to a string.
 * \return  <ul>
 *              <li> pointer to a address of string if sucessful.
 *              <li> NULL if failed.
 *          </ul>

 * \attention   pBrowserConfig has a member which is used to count the memory size.
 */
void cfg_safeStrFree(T_BROWSERCONFIG *pBrowserConfig, int8_t *p);

/**
 * Malloc a new memory and copy the string content which has been pointed a size into it.
 * \param   pBrowserConfig  Pointer to Browser running config structure.
 * \param   pSrc            Pointer to a string.
 * \param   len             Copy length of string pSrc.
 * \return  <ul>
 *              <li> pointer to a address of string if sucessful.
 *              <li> NULL if failed.
 *          </ul>

 * \attention   pBrowserConfig has a member which is used to count the memory size.
 */
int8_t *cfg_strndup(T_BROWSERCONFIG *pBrowserConfig, int8_t *pSrc, int32_t len);

/**
 * Malloc a pointed size memory
 * \param   pBrowserConfig  Pointer to Browser running config structure.
 * \param   len             Size of memory.
 * \return  <ul>
 *              <li> pointer to a address of string if sucessful.
 *              <li> NULL if failed.
 *          </ul>

 * \attention   pBrowserConfig has a member which is used to count the memory size.
 */
void *cfg_malloc(T_BROWSERCONFIG *pBrowserConfig, int32_t len);

/**
 * Free a pointed size memory
 * \param   pBrowserConfig  Pointer to Browser running config structure.
 * \param   len             Size of memory.
 * \return  <ul>
 *              <li> pointer to a address of string if sucessful.
 *              <li> NULL if failed.
 *          </ul>

 * \attention   pBrowserConfig has a member which is used to count the memory size.
 */
void cfg_free(T_BROWSERCONFIG *pBrowserConfig, void *p, int32_t len);

#ifdef __cplusplus
}
#endif

#endif /* __CVS_CFG_MEMORYMANAGE_H__ */
