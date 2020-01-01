#ifndef COPYBLKQ_H
#define COPYBLKQ_H

#include "avp_common.h"

/********************************************************************
    MC routines prototypes
*********************************************************************/
void CopyBlockQFull_8_8(const uchar *src, uchar *dst, int stride, int rounding, int f_idx);
void CopyBlockQH1_8_8  (const uchar *src, uchar *dst, int stride, int rounding, int f_idx);
void CopyBlockQH2_8_8  (const uchar *src, uchar *dst, int stride, int rounding, int f_idx);
void CopyBlockQH3_8_8  (const uchar *src, uchar *dst, int stride, int rounding, int f_idx);

void CopyBlockQV1_8_8  (const uchar *src, uchar *dst, int stride, int rounding, int f_idx);
void CopyBlockQH1V1_8_8(const uchar *src, uchar *dst, int stride, int rounding, int f_idx);
void CopyBlockQH2V1_8_8(const uchar *src, uchar *dst, int stride, int rounding, int f_idx);
void CopyBlockQH3V1_8_8(const uchar *src, uchar *dst, int stride, int rounding, int f_idx);

void CopyBlockQV2_8_8  (const uchar *src, uchar *dst, int stride, int rounding, int f_idx);
void CopyBlockQH1V2_8_8(const uchar *src, uchar *dst, int stride, int rounding, int f_idx);
void CopyBlockQH2V2_8_8(const uchar *src, uchar *dst, int stride, int rounding, int f_idx);
void CopyBlockQH3V2_8_8(const uchar *src, uchar *dst, int stride, int rounding, int f_idx);

void CopyBlockQV3_8_8  (const uchar *src, uchar *dst, int stride, int rounding, int f_idx);
void CopyBlockQH1V3_8_8(const uchar *src, uchar *dst, int stride, int rounding, int f_idx);
void CopyBlockQH2V3_8_8(const uchar *src, uchar *dst, int stride, int rounding, int f_idx);
void CopyBlockQH3V3_8_8(const uchar *src, uchar *dst, int stride, int rounding, int f_idx);

/*********************************************************************/

void CopyBlockQFull_16_8(const uchar *src, uchar *dst, int stride, int rounding);
void CopyBlockQH1_16_8  (const uchar *src, uchar *dst, int stride, int rounding);
void CopyBlockQH2_16_8  (const uchar *src, uchar *dst, int stride, int rounding);
void CopyBlockQH3_16_8  (const uchar *src, uchar *dst, int stride, int rounding);

void CopyBlockQV1_16_8  (const uchar *src, uchar *dst, int stride, int rounding);
void CopyBlockQH1V1_16_8(const uchar *src, uchar *dst, int stride, int rounding);
void CopyBlockQH2V1_16_8(const uchar *src, uchar *dst, int stride, int rounding);
void CopyBlockQH3V1_16_8(const uchar *src, uchar *dst, int stride, int rounding);

void CopyBlockQV2_16_8  (const uchar *src, uchar *dst, int stride, int rounding);
void CopyBlockQH1V2_16_8(const uchar *src, uchar *dst, int stride, int rounding);
void CopyBlockQH2V2_16_8(const uchar *src, uchar *dst, int stride, int rounding);
void CopyBlockQH3V2_16_8(const uchar *src, uchar *dst, int stride, int rounding);

void CopyBlockQV3_16_8  (const uchar *src, uchar *dst, int stride, int rounding);
void CopyBlockQH1V3_16_8(const uchar *src, uchar *dst, int stride, int rounding);
void CopyBlockQH2V3_16_8(const uchar *src, uchar *dst, int stride, int rounding);
void CopyBlockQH3V3_16_8(const uchar *src, uchar *dst, int stride, int rounding);

/*********************************************************************/

void CopyBlockQFull_16_16(const uchar *src, uchar *dst, int stride, int rounding);
void CopyBlockQH1_16_16  (const uchar *src, uchar *dst, int stride, int rounding);
void CopyBlockQH2_16_16  (const uchar *src, uchar *dst, int stride, int rounding);
void CopyBlockQH3_16_16  (const uchar *src, uchar *dst, int stride, int rounding);

void CopyBlockQV1_16_16  (const uchar *src, uchar *dst, int stride, int rounding);
void CopyBlockQH1V1_16_16(const uchar *src, uchar *dst, int stride, int rounding);
void CopyBlockQH2V1_16_16(const uchar *src, uchar *dst, int stride, int rounding);
void CopyBlockQH3V1_16_16(const uchar *src, uchar *dst, int stride, int rounding);

void CopyBlockQV2_16_16  (const uchar *src, uchar *dst, int stride, int rounding);
void CopyBlockQH1V2_16_16(const uchar *src, uchar *dst, int stride, int rounding);
void CopyBlockQH2V2_16_16(const uchar *src, uchar *dst, int stride, int rounding);
void CopyBlockQH3V2_16_16(const uchar *src, uchar *dst, int stride, int rounding);

void CopyBlockQV3_16_16  (const uchar *src, uchar *dst, int stride, int rounding);
void CopyBlockQH1V3_16_16(const uchar *src, uchar *dst, int stride, int rounding);
void CopyBlockQH2V3_16_16(const uchar *src, uchar *dst, int stride, int rounding);
void CopyBlockQH3V3_16_16(const uchar *src, uchar *dst, int stride, int rounding);

#endif /* COPYBLKQ_H */
