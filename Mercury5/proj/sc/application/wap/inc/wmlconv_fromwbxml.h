
#ifndef __WMLCONV_FROMWBXML_H__
#define __WMLCONV_FROMWBXML_H__

#include <stdio.h>
#include <wmlconv_tqh.h>

#ifndef NULL
#define NULL             (void *)0
#endif

/* The IANA codes for known character sets */
#define IANA_ASCII       3
#define IANA_ISO_8859_1  4
#define IANA_UTF_8       106

/* WBXML byte codes */
/* Global Tokens    */
#define SWITCH_PAGE 0x00
#define END         0x01
#define ENTITY      0x02
#define STR_I       0x03
#define LITERAL     0x04
#define EXT_I_0     0x40
#define EXT_I_1     0x41
#define EXT_I_2     0x42
#ifdef PI
#undef PI
#endif  //
#define PI          0x43
#define LITERAL_C   0x44
#define EXT_T_0     0x80
#define EXT_T_1     0x81
#define EXT_T_2     0x82
#define STR_T       0x83
#define LITERAL_A   0x84
#define EXT_0       0xC0
#define EXT_1       0xC1
#define EXT_2       0xC2
#define OPAQUE      0xC3
#define LITERAL_AC  0xC4

/* Error codes */
#define WBXML_OK    0       /* no error */
#define WBXML_TRUNCATED 1   /* input was truncated */
#define WBXML_VERSION   2   /* unsupported version number */
#define WBXML_CHARSET   3   /* unsupported character set number */
#define WBXML_PUBID     4   /* unsupported public identifier */
#define WBXML_BADDATA   5   /* bad structure */
#define WBXML_UNIMP     6   /* EXT_? and OPAQUE not implemented */
#define WBXML_TOO_BIG   7   /* too much character data at once */
#define WBXML_NO_MEM    8   /* insufficient heap memory */

extern void init_outbuf(void);
extern void init_head(uint8_t *version,uint8_t *public_id);
extern uint32_t get_data_len(void);
extern uint8_t * wbxml(uint8_t *,uint32_t buf_len);

#endif /* __WMLCONV_FROMWBXML_H__*/
