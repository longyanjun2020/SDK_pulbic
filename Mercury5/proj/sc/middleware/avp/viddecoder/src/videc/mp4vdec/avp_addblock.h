#ifndef ADDBLOCK_H
#define ADDBLOCK_H

#include "avp_m4vPrivate.h"  //M4V_HANDLE

#ifdef DST_8x8x6
void ReconsVOPIntraB(int16 *resbuf, M4V_HANDLE *hp, int comp /*uchar *Dst, int stride*/);
void ReconsVOPInterB(int16 *resbuf, uchar *mcbuf, M4V_HANDLE *hp, int comp /*uchar *Dst, int stride*/);
void ReconsVOPInterB_NOT_CODED(uchar *mcbuf, M4V_HANDLE *hp, int comp /*uchar *Dst, int stride*/);
#else
extern void addblockIntra (M4V_HANDLE *hp, int16 bp[64], int comp, int bx, int by);
extern void addblockInter (M4V_HANDLE *hp, int16 bp[64], int comp, int bx, int by);
#endif

#ifdef MERGED_B_VOP_INTERPOLATION
void ReconsVOPInterB_b_vop(int16 *resbuf, uchar *mcbuf1, uchar *mcbuf2, M4V_HANDLE *hp, int comp /*uchar *Dst, int stride*/);
void ReconsVOPInterB_b_vop_NOT_CODED(uchar *mcbuf1, uchar *mcbuf2, M4V_HANDLE *hp, int comp /*uchar *Dst, int stride*/);
#endif

void invert_block(int16* RESTRICT blk);

#endif // ADDBLOCK_H
