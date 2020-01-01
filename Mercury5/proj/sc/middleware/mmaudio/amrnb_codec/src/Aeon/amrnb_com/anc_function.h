#ifndef __AMRNB_COMMON_FUNCTION_INCLUDE_FILE__
#define __AMRNB_COMMON_FUNCTION_INCLUDE_FILE__



void amrnb_Log2 (
    Word32 L_x,        /* (i) : input value                                 */
    Word32 *exponent,  /* (o) : Integer part of Log2.   (range: 0<=val<=30) */
    Word32 *fraction   /* (o) : Fractional part of Log2. (range: 0<=val<1)*/
);


Word32 amrnb_Inv_sqrt (      /* (o) : output value   (range: 0<=val<1)            */
    Word32 L_x           /* (i) : input value    (range: 0<=val<=7fffffff)    */
);



Word32 amrnb_Pow2 (          /* (o) : result       (range: 0<=val<=0x7fffffff)    */
    Word16 exponent,   /* (i) : Integer part.      (range: 0<=val<=30)      */
    Word16 fraction    /* (i) : Fractional part.  (range: 0.0<=val<1.0)     */
);


void gc_pred_reset (gc_predState *st);



Word32 amrnb_sqrt_l_exp (/* o : output value,                        Q31 */
    Word32 L_x,    /* i : input value,                         Q31 */
    Word32 *exp    /* o : right shift to be applied to result, Q0  */
);



void amrnb_Log2_norm (
    Word32 L_x,         /* (i) : input value (normalized)                    */
    Word32 exp,         /* (i) : norm_l (L_x)                                */
    Word32 *exponent,   /* (o) : Integer part of Log2.   (range: 0<=val<=30) */
    Word32 *fraction    /* (o) : Fractional part of Log2. (range: 0<=val<1)  */
);
 

Word32 pseudonoise( Word32 *shift_reg, Word32 no_bits );

void amrnb_Copy (Word16 x[], Word16 y[], int L);
void amrnb_CopyM(Word16 x[], Word16 y[], int L);
void amrnb_Copy8(Word16 x[], Word16 y[], int L);
//--------------------------------------------
//EFR mode DTX and VAD flag
#ifdef PURE_EFR_MODE 
void efr_vad_reset (EFR_DTX_VAD_ENC_DATA *st);

Word16 vad_computation (EFR_DTX_VAD_ENC_DATA *st,
    Word16 r_h[],
    Word16 r_l[],
    Word16 scal_acf,
    Word16 rc[],
    Word16 ptch
);
#endif




void efr_reset_tx_dtx (EFR_DTX_VAD_ENC_DATA *st);       /* Reset tx dtx variables */
void efr_reset_rx_dtx (EFR_DTX_VAD_DEC_DATA *st);       /* Reset rx dtx variables */

void tx_dtx (EFR_DTX_VAD_ENC_DATA *st,
    Word16 VAD_flag,
    Word16 *txdtx_ctrl
);

void rx_dtx (EFR_DTX_VAD_DEC_DATA *st,
    Word16 *rxdtx_ctrl,
    Word16 TAF,
    Word16 bfi,
    Word16 SID_flag
);

void CN_encoding (EFR_DTX_VAD_ENC_DATA *st,
    Word16 params[],
    Word16 txdtx_ctrl
);

void sid_codeword_encoding (
    Word16 ser2[]
);


void update_lsf_history (
    Word16 lsf1[M],
    Word16 lsf2[M],
    Word16 lsf_old[DTX_HANGOVER][M]
);
void update_lsf_history32 (
    Word32 lsf1[M],
    Word32 lsf2[M],
    Word16 lsf_old[DTX_HANGOVER][M]
);
void update_lsf_p_CN (
    Word16 lsf_old[DTX_HANGOVER][M],
    Word16 lsf_p_CN[M]
);

void aver_lsf_history (
    Word16 lsf_old[DTX_HANGOVER][M],
    Word16 lsf1[M],
    Word16 lsf2[M],
    Word16 lsf_aver[M]
);

void update_gain_code_history_tx (EFR_DTX_VAD_ENC_DATA *st,
    Word16 new_gain_code,
    Word16 gain_code_old_tx[4 * DTX_HANGOVER]
);

void update_gain_code_history_rx (EFR_DTX_VAD_DEC_DATA *st,
    Word16 new_gain_code,
    Word16 gain_code_old_rx[4 * DTX_HANGOVER]
);

Word16 compute_CN_excitation_gain (
    Word16 res2[L_SUBFR]
);

Word16 update_gcode0_CN (
    Word16 gain_code_old_tx[4 * DTX_HANGOVER]
);

Word16 aver_gain_code_history (
    Word16 CN_excitation_gain,
    Word16 gain_code_old[4 * DTX_HANGOVER]
);



Word16 interpolate_CN_param (
    Word16 old_param,
    Word16 new_param,
    Word16 rx_dtx_state
);

void interpolate_CN_lsf (
    Word16 lsf_old_CN[M],
    Word16 lsf_new_CN[M],
    Word32 lsf_interp_CN[M],
    Word16 rx_dtx_state
);
//--------------------------------------------

unsigned short efrCalculateCRCAmr ( unsigned short *crcCompressedData );
 


#endif

