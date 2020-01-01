#ifndef DEQUANT_H
#define DEQUANT_H
//#define NANOBLAZE
#define LAST_COEF_SYM 0x8001
#ifdef NANOBLAZE
//#include "avp_nb.h"
#include "avp_nb_lib.h"
#define ADDK(rD, rA, rB)    {asm volatile ("addk %0,%1,%2": "=r" (rD): "r" (rA), "r" (rB));} 
#define ADDC(rD, rA, rB)    {asm volatile ("addc %0,%1,%2": "=r" (rD): "r" (rA), "r" (rB));} 
#define BSRL(rD, rA, rB)    {asm volatile ("bsrl %0,%1,%2": "=r" (rD): "r" (rA), "r" (rB));} 
#include "avp_nb.h"
#define MAX(a,b)        ((a) > (b) ? (a) : (b))
#define MIN(a,b)        ((a) < (b) ? (a) : (b))
#define ICLIPI(x, c)    MIN(MAX((int)(x), -(c)-1), (c))
//#define ICLIPI(a,b)     (((a)>(b)) ? (b) : (((a)<-(b)) ? -(b) : a))
#define UCLIPI(x, c)    MIN(MAX((x), 0), (c))
#define MUX(c, a, b)    ((c) ? (a) : (b))
#define MIN_QP 0
#define FACTOR_2(a) ((a)+(a))
typedef struct {
    uint8 intra_i16;
    uint8 intra;
    uint8 trans_8x8_flag;
    uint8 field_flag;
    uint8 cbp;
    uint8 qp;
} hdra_handle;
//typedef long long int64

int16 universal_iq_rv(int16 dc_ac_step, int16 scaler, int8 rounding, int8 shift_right) ;
int16 universal_iq_wmv3(int16 dc_ac_step, int16 scaler, int16 rounding, int16 clip_val);
int16 universal_iq_avc(int16 ac_step, int16 scale, int16 dq, uint8 shift_left, uint8 rounding, uint8 shift_right);
int16 universal_iq_iclip(int16 ac_step, uint8 qmatrix, int8 dq, int8 rounding, int8 shift_right, int16 clip_val);
int16 universal_iq_m2v_intra(uint16 ac_step, uint8 dq, uint8 qmatrix, uint8 shift_right);
#endif //NANOBLAZE
#endif
