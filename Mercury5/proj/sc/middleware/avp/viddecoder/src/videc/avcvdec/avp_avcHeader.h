#ifndef AVC_HEADER_H
#define AVC_HEADER_H

#include "avp_mvc_decoder.h"
#include "avp_videc_s.h"
#include "avp_defines.h"
#include "avp_avcPrivate.h"

err_type avcDecVop(AVC_HANDLE *hp, VID_SETUP *setup);

uchar * avc_decode_start_code_prefix(uchar *bp, int len);
int getavcslicehdr(AVC_HANDLE *hp, avc_header *hdra);
err_type decoding_poc(AVC_HANDLE *hp, avc_header *hdra);

uint32 avc_slice_data_mbaff(AVC_HANDLE *hp);
uint32 avc_slice_data_cabac_mbaff(AVC_HANDLE *hp);
uint32 avc_slice_data(AVC_HANDLE *hp);
uint32 avc_slice_data_cabac(AVC_HANDLE *hp);

void copy_comps(uchar *src, uchar *dst, int data_width, int data_height, int stride);

int more_rbsp_data(AVC_HANDLE *hp, BITSBUF *bs);
int more_rbsp_data_PPS(AVC_HANDLE *hp, BITSBUF *bs);
int more_rbsp_data_cabac(AVC_HANDLE *hp, avc_header *hdra, BITSBUF *bs);


typedef void (*func_get_block)(AVC_HANDLE *, avc_header *, StorablePicture *[][ALLOC_STOREABLE_PIC_POOL]);
extern const func_get_block get_block_nxn[5+1];
//extern const void (*get_block_nxn[5+1])(AVC_HANDLE *hp, avc_header *hdra, StorablePicture *listX[][ALLOC_STOREABLE_PIC_POOL]);
extern void (*get_block_nxn_mbaff[5+1])(AVC_HANDLE *hp, avc_header *hdra, StorablePicture *listX[][ALLOC_STOREABLE_PIC_POOL]);

uchar *avcParseStartCodes(VID_HANDLE *hp, VID_SETUP *setup, uchar *buf, int len, int init_seq, int pic_start, err_type *err_ret);
#ifdef NO_NAL_PEEK
int avcNextAUIsSOP(uchar* bp);
#else
int avcSkipToNextAU(AVC_HANDLE *hp, VID_SETUP *setup);
#endif

#endif // AVC_HEADER_H
