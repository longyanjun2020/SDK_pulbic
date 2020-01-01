/*
********************************************************************************
*
*      GSM AMR-NB speech codec   R98   Version 7.6.0   December 12, 2001
*                                R99   Version 3.3.0                
*                                REL-4 Version 4.1.0                
*
********************************************************************************
*
*      File             : pred_lt.h
*      Purpose          : Compute the result of long term prediction.
*
*
********************************************************************************
*/
#ifndef dec_pred_lt_h
#define dec_pred_lt_h "$Id $"
 
/*
********************************************************************************
*                         INCLUDE FILES
********************************************************************************
*/
#include "typedef.h"
 
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
//#ifdef VC_CODE 
#if 1
void Decoder_Pred_lt_3or6 (
    Word16 exc[],     /* in/out: excitation buffer                         */
    Word16 T0,        /* input : integer pitch lag                         */
    Word16 frac,      /* input : fraction of lag                           */
    Word16 L_subfr,   /* input : subframe size                             */
    Word16 flag3      /* input : if set, upsampling rate = 3 (6 otherwise) */
);
#else
void Decoder_Pred_lt_3or6 (
    Word16 exc[],     /* in/out: excitation buffer                         */
    Word16 T0,        /* input : integer pitch lag                         */
    Word16 frac,      /* input : fraction of lag                           */
    Word16 flag3      /* input : if set, upsampling rate = 3 (6 otherwise) */
);
#endif

#endif
