#ifndef COPYBLKE_H
#define COPYBLKE_H

#include "avp_mvc_types.h"
#include "avp_common.h"

#if !defined(_AG_V64_)

void copy_block_bilinear_eighth(const uint8 * RESTRICT src1, uint8 * RESTRICT dst1,
                                const uint8 * RESTRICT src2, uint8 * RESTRICT dst2,
                                int bw, int bh, int stride, int frac);

#define copy_block_bilinear_eighth_4(src1, dst1, src2, dst2, bh, stride, frac) \
        copy_block_bilinear_eighth  (src1, dst1, src2, dst2, 4, bh, stride, frac)

#define copy_block_bilinear_eighth_8(src1, dst1, src2, dst2, bh, stride, frac) \
        copy_block_bilinear_eighth  (src1, dst1, src2, dst2, 8, bh, stride, frac)

#else /* _AG_V64_ */

void copy_block_bilinear_eighth_4(const uint8 * RESTRICT src1, uint8 * RESTRICT dst1,
                                  const uint8 * RESTRICT src2, uint8 * RESTRICT dst2,
                                  int bh, int stride, int frac);
void copy_block_bilinear_eighth_8(const uint8 * RESTRICT src1, uint8 * RESTRICT dst1,
                                  const uint8 * RESTRICT src2, uint8 * RESTRICT dst2,
                                  int bh, int stride, int frac);

#endif /* _AG_V64_ */

void copy_block_bilinear_quarter(const uint8 * RESTRICT src1, uint8 * RESTRICT dst1,
                                 const uint8 * RESTRICT src2, uint8 * RESTRICT dst2,
                                 int bw, int bh, int stride, int frac);

void copy_block_bilinear_quarter_cif(const uint8 * RESTRICT src1, uint8 * RESTRICT dst1,
                                     const uint8 * RESTRICT src2, uint8 * RESTRICT dst2,
                                     int bw, int bh, int stride, int frac);

void copy_block_bilinear_quarter_d1(const uint8 * RESTRICT src1, uint8 * RESTRICT dst1,
                                    const uint8 * RESTRICT src2, uint8 * RESTRICT dst2,
                                     int bw, int bh, int stride, int frac);

#endif /* COPYBLKE_H */
