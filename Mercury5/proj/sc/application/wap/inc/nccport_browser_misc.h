
/**
 * @file
 * Wap OS Porting Layer
 *
 * Basic support functions that are needed by wap.
 *
 * <!-- #interface list begin -->
 * \section cpl_wapos_misc Interface
 * - NCCPort_brwmisc_initFileDirProperties()
 * - NCCPort_brwmisc_freeFileDirProperties()
 * - NCCPort_brwmisc_getProperty()
 * - NCCPort_brwmisc_checkObject()
 * <!-- #interface list end -->
 */

#ifndef __NCCPORT_BROWSER_MISC_H__
#define __NCCPORT_BROWSER_MISC_H__

#ifdef __cplusplus
extern  "C" {
#endif

#include "ncc_types.h" /**<common wap include file*/

typedef enum _DIR_FLAG{
    DIR_ROOT = 0,
    DIR_CACHE,
    DIR_PUSH,
    DIR_CERT,
    DIR_CACHE_CONF,
    DIR_COOKIE,
    DIR_CFG_CONF,
    DIR_CERT_CONF,
    DIR_RECORD,
    DIR_SIZE
}DIR_FLAG;

#ifdef NCC_BROWSER_CACHE
#define FILENAMELEN 100
#define CACHEDIRECTORY NCCPort_brwmisc_getProperty(DIR_CACHE)
#define CONFIGURATIONFILE NCCPort_brwmisc_getProperty(DIR_CACHE_CONF)
#endif /* NCC_BROWSER_CACHE */

#define CERT_DIRECTORY  NCCPort_brwmisc_getProperty(DIR_CERT)
#define CERT_FILE       NCCPort_brwmisc_getProperty(DIR_CERT_CONF)

/**directory to save the push*/
#define PUSHDIRECTORY NCCPort_brwmisc_getProperty(DIR_PUSH)

/**File name to save the cookie*/
#define DB_COOKIE_FULLNAME NCCPort_brwmisc_getProperty(DIR_COOKIE)

/* config file name */
#define NCC_CFG_CONFIGFILE  NCCPort_brwmisc_getProperty(DIR_CFG_CONF)

/* config file name */
#define DB_RECORDFILE  NCCPort_brwmisc_getProperty(DIR_RECORD)
/**
 *
 */
int32_t NCCPort_brwmisc_makeDeepDir(int8_t *fileName);

/**
 * Initialize all file dir properties the browser needs,
 * such as: cache dir, hreflist dir, cookie, cfg configuration.
 */
int32_t NCCPort_brwmisc_initFileDirProperties(int8_t *sysPath);

/**
 * Free all all file dir properties.
 */
void NCCPort_brwmisc_freeFileDirProperties(void);

/**
 * Return a property value.
 * \param key is the property index.
 * \return the property value as a UTF8 string, or NULL if not found.
 */
int8_t *NCCPort_brwmisc_getProperty(uint32_t key);

/**
 * Check whether user can support this object by classid and type.
 * \param classid Classid to Check.
 * \param type Type to check.
 * \return TRUE: support; FALSE: not support.
 */
int32_t NCCPort_brwmisc_checkObject(uint8_t *classid, uint8_t * type);

#ifdef __cplusplus
}
#endif

#endif /* __NCCPORT_BROWSER_MISC_H__ */
