#ifndef AVCDEC_H
#define AVCDEC_H

#include <stdint.h>
#include "avp_mvc_decoder.h"
#include "avp_videc_s.h"

int avc_init_decoder(VID_HANDLE *handle, VID_SETUP *setup, uint8_t *decbuf, int size, int *used);
int avc_get_handle_size(void);

#endif /* AVCDEC_H */
