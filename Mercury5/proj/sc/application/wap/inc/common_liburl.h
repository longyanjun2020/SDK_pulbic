/*
 * Copyright 2005-2006 NCC Inc. All Rights Reserved.
 * $Id: //depot/dev/base/inc/uapps/common/common_liburl.h#1 $
 */

#ifndef __COMMON_LIBURL_H__
#define __COMMON_LIBURL_H__

#include <ncc_types.h>
#include <string.h>

#ifdef __cplusplus
extern "C" {
#endif

/************************ Structure Definition ****************************/
typedef struct {
    int8_t *scheme;     /* scheme ("http"/"ftp"/...) */
    int8_t *hostinfo;   /* combined [user[:password]@]host[:port] */
    int8_t *user;       /* user name, as in http://user:passwd@host:port/ */
    int8_t *password;   /* password, as in http://user:passwd@host:port/ */
    int8_t *hostname;   /* hostname from URI (or from Host: header) */
    int8_t *port_str;   /* port string (integer representation is in "port") */
    int8_t *path;       /* the request path (or "/" if only scheme://host was given) */
    int8_t *query;      /* Everything after a '?' in the path, if present */
    int8_t *fragment;   /* Trailing "#fragment" string, if present */
    int8_t *parameter;  /* /xxx;parameter/xxxx;parameter/..... */
} uri_components;

#ifdef __cplusplus
}
#endif

#endif /* __COMMON_LIBURL_H__ */

