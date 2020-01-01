
#include "audions_api.h"
#include <string.h>
#include <stdio.h>

#define MAX(x,y)        ((x)>(y) ? (x) : (y))
#define MIN(x,y)        ((x)<(y) ? (x) : (y))
#define ABS(x)          ((x)> 0  ? (x) :-(x))

#define BANDS           8

#define _FIXED_POINT_
#if defined _FIXED_POINT_
typedef int             real_t;
#else
typedef float           real_t;
#endif

#if defined __AEONR2__
#define AMACR_KEEP      16   // keep
#define AMACR_CLR        8   // clear
#define AMACR_RND        4   // round
#define AMACR_SAT        2   // saturate
#define AMACR_SHR        1   // shift
typedef long long       S64;
#define MAX_SPRS_PER_GRP_BITS   (11)
#define SPRGROUP_MAC	        (5<<MAX_SPRS_PER_GRP_BITS)
#define SPR_AMACCFG             (SPRGROUP_MAC+13)
#define L_MTSPR1(spr,val)\
    __asm__ volatile("b.mtspr1 %0,%1"::"r"(val),"K"(spr))
#define ENABLE_AMAC()\
    L_MTSPR1(SPR_AMACCFG,1)
#else
typedef __int64         S64;
#define ENABLE_AMAC()
#endif

typedef struct
{
    short  *start,*tailp,*rdpos,*wrpos,*clear;
    real_t  gamma, kappa, scale;
    real_t *fftsp,*space,*power;
    real_t *sound,*signl,*noise;
    real_t  alpha[BANDS];
    real_t  delta[BANDS];
    int     bands[BANDS];
    int     sizeofctx;
}
AudioNsState_t;

extern void realDFT128(real_t*,real_t*);
extern void realIFT128(real_t*,real_t*);

extern void audioNsBlock(AudioNsState_t*);
extern void audioNsBuild(AudioNsState_t*);
