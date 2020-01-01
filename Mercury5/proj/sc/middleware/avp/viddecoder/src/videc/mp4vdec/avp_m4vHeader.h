#ifndef M4V_HEADER_H
#define M4V_HEADER_H

#include "avp_m4vPrivate.h"  //MP4_STREAM
#include "avp_h263Header.h"

#if defined(__TCS__)
#define use_intra_dc_vlc(quantizer, intra_dc_vlc_thr) ((intra_dc_vlc_thr==0) ||\
    ((intra_dc_vlc_thr!=7) && (quantizer < 11 + (intra_dc_vlc_thr*2)) ) )
#else
#define use_intra_dc_vlc(quantizer, intra_dc_vlc_thr) ((intra_dc_vlc_thr==0) ||\
    ((intra_dc_vlc_thr!=7) && (quantizer < 11 + (intra_dc_vlc_thr<<1)) ) )
#endif
//extern int use_intra_dc_vlc(int quantizer, int intra_dc_vlc_thr);

//#define REPORT_START_CODE(x) MY_PRINTF("START_CODE: " x "\n");
#define REPORT_START_CODE(x)

uchar *seek_start_code_prefix(uchar *bp, uchar *be);

int mp4v_getvophdr(M4V_HANDLE *hp);
void mp4v_reset_slice(M4V_HANDLE* hp);
int mp4v_getpackethdr(M4V_HANDLE *hp);
uchar *m4vParseStartCodes(M4V_HANDLE *hp, uchar *buf, int len, err_type *err_ret);

#endif // M4V_HEADER_H
