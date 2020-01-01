
#ifndef _AUDIOAEC_ECHOSUPPR_H_
#define _AUDIOAEC_ECHOSUPPR_H_

/* ===============================================================================================*/
//#define __PRINT_ECHOSUPPR__
/* ===============================================================================================*/
#include "audioaec_ccstubs.h"

#if defined(__PRINT_ECHOSUPPR__)
#include <stdio.h>
extern FILE *gn_lin, *gn_lg2;
extern FILE *ech_sm, *lms_sm, *ref_sm, *aec_sm;
extern FILE *ref_db, *ech_db, *lms_db;
#define _DATA_WRITE(addr,size,count,file)   fwrite(addr,size,count,file);
#else
#define _DATA_WRITE(addr,size,count,file)
#endif/*__PRINT_ECHOSUPPR__*/

#define _USE_NEW_AES_

#if defined(_USE_NEW_AES_)

#define AES_QUEUE_SIZE  64

typedef struct echosuppr_t
{
    U32 echosuppr_enable;
    S32 sinc4_idx, sinc4_loc, sinc4_pcm[4];
    S32 scale_loc, scale_ech, scale_ref;
    S32 lpass_loc, lpass_ech, lpass_ref;
    S32 bound_loc, bound_ech, bound_ref;
    S32 lpass_abs_loc[AES_QUEUE_SIZE];
    S32 lpass_abs_ech[AES_QUEUE_SIZE];
    S32 lpass_abs_ref[AES_QUEUE_SIZE];
    U32 delay_sum_ref[AES_QUEUE_SIZE];
    S16 clean_samples[AES_QUEUE_SIZE];
    S32 index_queue;
    S32 suppr_level, att_rate, rel_rate;
}
echosuppr_t;

extern int echosuppr_initialise(echosuppr_t*);
extern int echosuppr_set_config(echosuppr_t*,U32,S32,S32,S32,S32,S32,S32,S32,S32);
extern S16 echosuppr_apply_gain(echosuppr_t*,S16,S16,S16);

#endif/*_USE_NEW_AES_*/

#endif/*_AUDIOAEC_ECHOSUPPR_H_*/