#ifndef H263DEC_H
#define H263DEC_H

#include <stdint.h>
#include "avp_videc_s.h"

uint8_t *h263_parse_start_code(uint8_t *buf, int len);
int      h263_decode_short_header(VID_HANDLE *hp);

#endif /* H263DEC_H */
