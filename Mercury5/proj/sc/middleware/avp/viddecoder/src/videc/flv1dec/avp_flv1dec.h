#ifndef FLV1DEC_H
#define FLV1DEC_H

#include <stdint.h>
#include "avp_videc_s.h"

uint8_t *flv1_parse_start_code(uint8_t *buf, int len);
int      flv1_decode_picture_header(VID_HANDLE *hp);

#endif /* FLV1DEC_H */
