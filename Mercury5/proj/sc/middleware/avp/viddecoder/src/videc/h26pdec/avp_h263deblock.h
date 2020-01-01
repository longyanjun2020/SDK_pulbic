#ifndef H263DEBLOCK_H
#define H263DEBLOCK_H

#include "avp_m4vPrivate.h"  //MP4_STREAM

void h263_filter_mb_row_intra(M4V_HANDLE *hp, int by);
void h263_filter_mb_row_inter(M4V_HANDLE *hp, int by);

#endif
