#ifndef IMAGE_H
#define IMAGE_H

#include "avp_mvc_decoder.h"
#include "avp_avcPrivate.h"

void init_frame(AVC_HANDLE *hp);
int avc_slice_header(AVC_HANDLE *hp, VID_SETUP *setup);

void avc_slice_ec_begin(AVC_HANDLE *hp, int make_fake_pixels);
void avc_slice_ec_end(AVC_HANDLE *hp);
void avc_I_slice_and_macroblock_ec(AVC_HANDLE *hp, int end_mb_nr, int isBackward);

#endif
