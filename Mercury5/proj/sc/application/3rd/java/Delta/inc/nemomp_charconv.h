#ifndef __NEMOMP_CHAR_CONV_H__
#define __NEMOMP_CHAR_CONV_H__

#include "nemomp.h"

extern int nemomp_get_code_type(const char* codePage);
extern int nemomp_charconv_to_ucs2(int src_codepage_id, char *src_buf, int src_size, char *dst_buf, int dst_size);
extern int nemomp_charconv_from_ucs2(int dst_codepage_id, char *src_buf, int src_size, char *dst_buf, int dst_size);
extern nm_bool nemomp_charconv_is_valid_codepage(const char* codePage);

extern void nemomp_charconv_ucs2_to_utf8(nm_char *utf8, nm_wchar *ucs2string);
extern void nemomp_charconv_utf8_to_ucs2(nm_wchar *ucs2string, nm_char *utf8);
extern int nemomp_get_ucs2_len(nm_wchar* ucs2string);

extern int nemomp_ven_std_utf8toucs2(nm_wchar *ucs2string, nm_char *utf8);
extern int nemomp_ven_std_ucs2toutf8(nm_char *utf8, nm_wchar *ucs2string);

#endif /* __NEMOMP_CHAR_CONV_H__ */
