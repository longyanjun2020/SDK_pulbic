
#ifndef  __IFLAYER_DLERRORPAGE_H__
#define  __IFLAYER_DLERRORPAGE_H__

#include <ncc_types.h>
#include <wap_config.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef enum _Error_Page_Type
{
    E_ERRORPAGE_NOTFOUND,
    E_ERRORPAGE_NOTFOUND_CHS,
    E_ERRORPAGE_DNSERROR,
    E_ERRORPAGE_DNSERROR_CHS,
    E_ERRORPAGE_CONTENTERROR,
    E_ERRORPAGE_CONTENTERROR_CHS,
    E_ERRORPAGE_URLERROR,
    E_ERRORPAGE_URLERROR_CHS,
    E_ERRORPAGE_NOTSUPPORTSSLERROR,
    E_ERRORPAGE_NOTSUPPORTSSLERROR_CHS
}T_Error_Page_Type;

/**
 * Get pointer and length of Error page.
 * \param  type     type of error page
 * \param  length   get length of error page
 * \return  <ul>
 *          <li>NUll:failed</li>
 *          <li>>0:success</li>
 *          </ul>
 */
int8_t * iflayer_getErrorPage(T_Error_Page_Type type,int32_t * length);

typedef enum _Wml_Error_Page_Type
{
	E_WMLERRORPAGE_NOTFOUND,
    E_WMLERRORPAGE_NOTFOUND_CHS,
	E_WMLERRORPAGE_URLERROR,
	E_WMLERRORPAGE_URLERROR_CHS,
	E_WMLERRORPAGE_DNSERROR,
	E_WMLERRORPAGE_DNSERROR_CHS,
	E_WMLERRORPAGE_CONTENTERROR,
	E_WMLERRORPAGE_CONTENTERROR_CHS,
	E_WMLERRORPAGE_NOTSUPPORTSSL,
	E_WMLERRORPAGE_NOTSUPPORTSSL_CHS
}T_WmlError_Page_Type;

// When not support html, use wml version.
const int8_t * iflayer_getWmlErrorPage(T_WmlError_Page_Type type,int32_t * length);

#ifdef __cplusplus
}
#endif

#endif /* __IFLAYER_DLERRORPAGE_H__ */

