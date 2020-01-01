
#include <nccwhttp.h>

#ifndef __WHTTP_COOKIE_H__
#define __WHTTP_COOKIE_H__

#ifdef __cplusplus
extern "C" {
#endif

/************************ Macro Definition ****************************/

/************************ Structure Definition ****************************/
typedef struct HTCookie {
        int8_t      *hostname;
        int8_t      *hostpath;
        int8_t      *name;
        int8_t      *value;
        int8_t      *domain;
        int8_t      *path;
        int32_t      expiration;
        int32_t      secureflag;
        int8_t      *comment;
        int8_t      *commenturl;
        int32_t      discard;
        int32_t      discardflag;
        int8_t      *portlist;
        int32_t      version;
        int32_t      versionflag;
        int32_t      maxage;
        int32_t      maxageflag;
        int32_t      cookietype;
        int32_t      secure;
}HTCOOKIE;

typedef struct HTCOOKIEvaluepath HTCOOKIEVALUEPATH;
struct HTCOOKIEvaluepath{
    int8_t *value;
    int8_t *path;
    HTCOOKIEVALUEPATH *next;
};

int32_t fnHTTP_CookieValid(CommonList *cookie_list,HTCOOKIE *cki);
int32_t fnHTTP_DelOneCookie(CommonList *cookie_list,HTCOOKIE *cki);

#ifdef __cplusplus
}
#endif

#endif /* __WHTTP_COOKIE_H__ */
