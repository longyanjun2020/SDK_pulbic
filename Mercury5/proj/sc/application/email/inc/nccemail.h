/**
* @file nccemail.h
* NCC email module header files
*
* Top header file of NCC email
*
* <!-- #interface list begin -->
* <!-- #interface list end -->
*/

#ifndef __NCCEMAIL_H__
#define __NCCEMAIL_H__

#include <ncc_types.h>
//library for UI
#include <nccemail_prot.h>
#include <nccemail_fs.h>

//library2 for transmission
#include <nccemail_common.h>
#include <nccemail_esmtp.h>
#include <nccemail_pop3.h>

#ifndef CRTL_EMAIL_malloc
#define CRTL_EMAIL_malloc(sz)         (NCCCommon_malloc(sz))
#endif

#ifndef CRTL_EMAIL_free
#define CRTL_EMAIL_free(ad)           (NCCCommon_free(ad))
#endif

#ifdef __cplusplus
extern "C" {
#endif

#ifdef __cplusplus
}
#endif

#endif /* __NCCEMAIL_H__ */
