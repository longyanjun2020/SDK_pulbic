#ifndef COPYBLKF_H
#define COPYBLKF_H

#include "avp_mvc_types.h"

/********************************************************************
    MC routines prototypes
*********************************************************************/
typedef void (CopyAreaProc)(const uchar * Src, uchar * Dst, int Stride, int by);
typedef CopyAreaProc* CopyAreaProcPtr;

void average_block(uint8 *dst, const uint8 *src, int stride, int bw, int bh);
void copy_block_hv(uint8 *dst, const uint8 *src, int stride, int32 type, uint32 round);

#define Copy8F      Copy8_16_F
#define Copy16F     Copy8_16_F

#define Copy8H      Copy8_16_H
#define Copy16H     Copy8_16_H

#define Copy8HR      Copy8_16_HR
#define Copy16HR     Copy8_16_HR

#define Copy8V      Copy8_16_V
#define Copy16V     Copy8_16_V

#define Copy8VR      Copy8_16_VR
#define Copy16VR     Copy8_16_VR

#define Copy8HV     Copy8_16_HV
#define Copy16HV    Copy8_16_HV

#define Copy8HVR    Copy8_16_HVR
#define Copy16HVR   Copy8_16_HVR

void Copy8_16_F(const uchar *Src, uchar * Dst, int Stride, int by);
void Copy8_16_H(const uchar *Src, uchar * Dst, int Stride, int by);
void Copy8_16_HR(const uchar *Src, uchar *Dst, int Stride, int by);
void Copy8_16_V(const uchar *Src, uchar * Dst, int Stride, int by);
void Copy8_16_HV(const uchar *Src, uchar * Dst, int Stride, int by);
void Copy8_16_VR(const uchar *Src, uchar *Dst, int Stride, int by);
void Copy8_16_HVR(const uchar *Src, uchar *Dst, int Stride, int by);


/* field MC */
void Copy16x8Full(const uchar *Src, uchar * Dst, int Stride);
void Copy16x8H(const uchar *Src, uchar * Dst, int Stride);
void Copy16x8V(const uchar *Src, uchar * Dst, int Stride);
void Copy16x8HV(const uchar *Src, uchar * Dst, int Stride);
void Copy16x8HR(const uchar *Src, uchar * Dst, int Stride);
void Copy16x8VR(const uchar *Src, uchar * Dst, int Stride);
void Copy16x8HVR(const uchar *Src, uchar * Dst, int Stride);

void Copy8x4Full(const uchar *Src, uchar * Dst, int Stride);
void Copy8x4H(const uchar *Src, uchar * Dst, int Stride);
void Copy8x4V(const uchar *Src, uchar * Dst, int Stride);
void Copy8x4HV(const uchar *Src, uchar * Dst, int Stride);
void Copy8x4HR(const uchar *Src, uchar * Dst, int Stride);
void Copy8x4VR(const uchar *Src, uchar * Dst, int Stride);
void Copy8x4HVR(const uchar *Src, uchar * Dst, int Stride);

#endif /* COPYBLKF_H */
