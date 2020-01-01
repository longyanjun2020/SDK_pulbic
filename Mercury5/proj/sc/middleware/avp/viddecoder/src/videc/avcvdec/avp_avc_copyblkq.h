#ifndef AVC_COPYBLKQ_H
#define AVC_COPYBLKQ_H

#include "avp_mvc_types.h"
#include "avp_common.h"

extern void (* const avc_CopyBlkQFunc_16_16[16])(const uchar * RESTRICT src, uchar * RESTRICT dst, int stride, int type);
extern void (* const avc_CopyBlkQFunc_16_8 [16])(const uchar * RESTRICT src, uchar * RESTRICT dst, int stride, int type);
extern void (* const avc_CopyBlkQFunc_8_16 [16])(const uchar * RESTRICT src, uchar * RESTRICT dst, int stride, int type);
extern void (* const avc_CopyBlkQFunc_8_8  [16])(const uchar * RESTRICT src, uchar * RESTRICT dst, int stride, int type);
extern void (* const avc_CopyBlkQFunc_8_4  [16])(const uchar * RESTRICT src, uchar * RESTRICT dst, int stride, int type);
extern void (* const avc_CopyBlkQFunc_4_8  [16])(const uchar * RESTRICT src, uchar * RESTRICT dst, int stride, int type);
extern void (* const avc_CopyBlkQFunc_4_4  [16])(const uchar * RESTRICT src, uchar * RESTRICT dst, int stride, int type);

#endif
