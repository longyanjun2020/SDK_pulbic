
#ifndef __CERT_SETCONVERT_H__
#define __CERT_SETCONVERT_H__

#include <ncc_types.h>

int8_t  strUtf8ToUcs2(uint8_t * utf8_code, uint16_t* ucs2_code,uint8_t  *count);
int16_t charUnicodToGB(uint16_t  iUnicode);
int32_t strUnicodToGB(int8_t *strSourcer, int8_t *strDest, int32_t n);

#endif  /* __CERT_SETCONVERT_H__ */
