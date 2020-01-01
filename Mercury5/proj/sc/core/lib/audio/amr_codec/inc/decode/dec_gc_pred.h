/*
********************************************************************************
*
*      GSM AMR-NB speech codec   R98   Version 7.6.0   December 12, 2001
*                                R99   Version 3.3.0                
*                                REL-4 Version 4.1.0                
*
********************************************************************************
*
*      File             : gc_pred.h
*      Purpose          : codebook gain MA prediction
*
********************************************************************************
*/

#ifndef dec_gc_pred_h
#define dec_gc_pred_h "$Id $"
 
/*
********************************************************************************
*                         INCLUDE FILES
********************************************************************************
*/
#include "typedef.h"
#include "mode.h"

#include "common.h"

/*
********************************************************************************
*                         LOCAL VARIABLES AND TABLES
********************************************************************************
*/
 
/*
********************************************************************************
*                         DEFINITION OF DATA TYPES
********************************************************************************
*/
 
/*
********************************************************************************
*                         DECLARATION OF PROTOTYPES
********************************************************************************
*/
int Decoder_gc_pred_init (gc_predState *st);
/* initialize one instance of codebook gain MA predictor
   Stores pointer to state struct in *st. This pointer has to
   be passed to gc_pred in each call.
   returns 0 on success
 */
 
int Decoder_gc_pred_reset (gc_predState *st);
/* reset of codebook gain MA predictor state (i.e. set state memory to zero)
   returns 0 on success
 */
void Decoder_gc_pred_exit (gc_predState *st);
/* de-initialize codebook gain MA predictor state (i.e. free state struct)
   stores NULL in *st
 */

void
Decoder_gc_pred_copy(
    gc_predState *st_src,  /* i : State struct                           */
    gc_predState *st_dest  /* o : State struct                           */
);

/*************************************************************************
 *
 * FUNCTION:  gc_pred()
 *
 * PURPOSE: MA prediction of the innovation energy
 *          (in dB/(20*log10(2))) with mean  removed).
 *
 *************************************************************************/
void Decoder_gc_pred(
    gc_predState *st,   /* i/o: State struct                           */
    enum Mode dec_mode,     /* i  : AMR mode                               */
    Word16 *code,       /* i  : innovative codebook vector (L_SUBFR)   */
                        /*      MR122: Q12, other modes: Q13           */
    Word16 *exp_gcode0, /* o  : exponent of predicted gain factor, Q0  */
    Word16 *frac_gcode0,/* o  : fraction of predicted gain factor  Q15 */
    Word16 *exp_en,     /* o  : exponent of innovation energy,     Q0  */
                        /*      (only calculated for MR795)            */
    Word16 *frac_en     /* o  : fraction of innovation energy,     Q15 */
                        /*      (only calculated for MR795)            */
);

/*************************************************************************
 *
 * FUNCTION:  gc_pred_update()
 *
 * PURPOSE: update MA predictor with last quantized energy
 *
 *************************************************************************/
void Decoder_gc_pred_update(
    gc_predState *st,      /* i/o: State struct                     */
    Word16 qua_ener_MR122, /* i  : quantized energy for update, Q10 */
                           /*      (log2(qua_err))                  */
    Word16 qua_ener        /* i  : quantized energy for update, Q10 */
                           /*      (20*log10(qua_err))              */
);

/*************************************************************************
 *
 * FUNCTION:  gc_pred_average_limited()
 *
 * PURPOSE: get average of MA predictor state values (with a lower limit)
 *          [used in error concealment]
 *
 *************************************************************************/
void Decoder_gc_pred_average_limited(
    gc_predState *st,       /* i: State struct                    */
    Word16 *ener_avg_MR122, /* o: averaged quantized energy,  Q10 */
                            /*    (log2(qua_err))                 */
    Word16 *ener_avg        /* o: averaged quantized energy,  Q10 */
                            /*    (20*log10(qua_err))             */
);

#endif
