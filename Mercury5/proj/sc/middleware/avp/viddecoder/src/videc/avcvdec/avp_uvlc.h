#ifndef UVLC_H
#define UVLC_H

#include "avp_getbits.h"

int uese_v(BITSBUF *bs, int u);
int uese_v_pair(BITSBUF *bs, int u);

#define ue_v(bs) ((unsigned int) uese_v(bs, 1))
#define se_v(bs) ((         int) uese_v(bs, 0))

#define ue_v_pair(bs) ((unsigned int) uese_v_pair(bs, 1))
#define se_v_pair(bs) ((         int) uese_v_pair(bs, 0))

#define u_v(bs, len) getbits(bs, len)
#define u_1(bs) getbits(bs, 1)

#endif
