#ifndef __AMR_WB_ENCODER_FUNCTION_INCLUDE_FILE__
#define __AMR_WB_ENCODER_FUNCTION_INCLUDE_FILE__



void Isf_Extrapolation(Word16 HfIsf[]);

void Init_Lagconc(Word16 lag_hist[]);
void lagconc(
     Word16 gain_hist[],                   /* (i) : Gain history     */
     Word16 lag_hist[],                    /* (i) : Subframe size         */
     Word16 * T0,
     Word16 * old_T0,
     Word16 * seed,
     Word16 unusable_frame
);
ATTR_NOMIPS16 Word32 Dot_product12_c4(
     Word16 x[],
     Word16 y[],
     Word32 *mant1,
     Word32 * exp1,
     Word32 * exp2
);
void awb_agc2(
     Word16 * sig_in,                      /* input : postfilter input signal  */
     Word16 * sig_out,                     /* in/out: postfilter output signal */
     Word16 l_trm                          /* input : subframe size            */
);


Word16 median5(Word16 x[]);

void Autocorr(
     Word16 x[],                           /* (i)    : Input signal           */
     Word16 m,                             /* (i)    : LPC order              */
	  Word32 *r,                            /* Autocorrelations                */
     Word16 *y
);

ATTR_NOMIPS16 void AutoLag(
     Word16 x[],                           // (i): Input signal    Q0
     Word16 m,                             // (i): LPC order        
     Word32 *r,
     Word16 *y
);

void Lag_window(
     Word32 *r
);
void Init_Levinson(
     Word16 * mem                          /* output  :static memory (18 words) */
);


void awe_Levinson(
	  Word32 *R,
     Word16 A[],                           /* (o) Q12 : A[M]    LPC coefficients  (m = 16)       */
     Word16 * mem                          /* (i/o)   :static memory (18 words)                  */
);

void Az_isp(
     Word16 a[],                           /* (i) Q12 : predictor coefficients                 */
     Word16 isp[],                         /* (o) Q15 : Immittance spectral pairs              */
     Word16 old_isp[]                      /* (i)     : old isp[] (in case not found M roots)  */
);



void dec_Isp_Az(
     Word16 isp[],                         /* (i) Q15 : Immittance spectral pairs            */
     Word16 a[],                           /* (o) Q12 : predictor coefficients (order = M)   */
     Word16 m,
     Word32 adaptive_scaling               /* (i) 0   : adaptive scaling disabled */
                                           /*     1   : adaptive scaling enabled  */
);

void Isp_isf(
     Word16 *isp,                          // (i) Q15 : isp[m] (range: -1<=val<1)
     Word16 *isf,                          // (o) Q15 : isf[m] normalized (range: 0.0<=val<=0.5)
     Word16 *tmpisf,
     Word16 m,                             // (i)     : LPC order
     Word16 *mem,
     Word16 *past_isfq
);

void Isf_isp(
     Word16 isf[],                         /* (i) Q15 : isf[m] normalized (range: 0.0<=val<=0.5) */
     Word16 isp[],                         /* (o) Q15 : isp[m] (range: -1<=val<1)                */
     Word16 m                              /* (i)     : LPC order                                */
);
ATTR_NOMIPS16 void dec_Int_isp(
     Word16 isp_old[],                     /* input : isps from past frame              */
     Word16 isp_new[],                     /* input : isps from present frame           */
     Word16 frac[],                      /* input : fraction for 3 first subfr (Q15)  */
     Word16 Az[],                           /* output: LP coefficients in 4 subframes    */
     Word32 flag
);


ATTR_NOMIPS16 void Weight_a(
     Word16 a[],                           /* (i) Q12 : a[m+1]  LPC coefficients             */
     Word16 ap[],                          /* (o) Q12 : Spectral expanded LPC coefficients   */
     Word32 gamma,                         /* (i) Q15 : Spectral expansion factor.           */
     Word32 m                              /* (i)     : LPC order.                           */
);

/*-----------------------------------------------------------------*
 *                        isf quantizers                           *
 *-----------------------------------------------------------------*/

void Qpisf_2s_46b(
     Word16 * isf1,                        // (i) Q15 : ISF in the frequency domain (0..0.5)
     Word16 * isf_q,                       // (o) Q15 : quantized ISF               (0..0.5)
     Word16 * tmpisf,
     Word16 * past_isfq,                   // (io)Q15 : past ISF quantizer
     Word16 * indice                       // (o)     : quantization indices
);
void Qpisf_2s_36b(
     Word16 * isf1,                        // (i) Q15 : ISF in the frequency domain (0..0.5)
     Word16 * isf_q,                       // (o) Q15 : quantized ISF               (0..0.5)
     Word16 * tmpisf,
     Word16 * past_isfq,                   // (io)Q15 : past ISF quantizer
     Word16 * indice                       // (o)     : quantization indices
);
void Dpisf_2s_46b(
     Word16 * indice,                      /* input:  quantization indices                       */
     Word16 * isf_q,                       /* output: quantized ISF in frequency domain (0..0.5) */
     Word16 * past_isfq,                    /* i/0   : past ISF quantizer                    */
     Word16 * isfold,                      /* input : past quantized ISF                    */
     Word16 * isf_buf,                     /* input : isf buffer                                                        */
     Word16 bfi,                           /* input : Bad frame indicator                   */
     Word16 enc_dec
);
void Dpisf_2s_36b(
     Word16 * indice,                      /* input:  quantization indices                       */
     Word16 * isf_q,                       /* output: quantized ISF in frequency domain (0..0.5) */
     Word16 * past_isfq,                    /* i/0   : past ISF quantizer                    */
     Word16 * isfold,                      /* input : past quantized ISF                    */
     Word16 * isf_buf,                     /* input : isf buffer                                                        */
     Word16 bfi,                           /* input : Bad frame indicator                   */
     Word16 enc_dec
);



ATTR_NOMIPS16 Word16 Sub_VQ(                             /* output: return quantization index     */
     Word16 * x,                           /* input : ISF residual vector           */
     Word16 * dico,                        /* input : quantization codebook         */
     Word16 dim,                           /* input : dimention of vector           */
     Word16 dico_size,                     /* input : size of quantization codebook */
     Word32 * distance                     /* output: error of quantization         */
);
void Reorder_isf(
     Word16 * isf,                         /* (i/o) Q15: ISF in the frequency domain (0..0.5) */
     Word16 min_dist,                      /* (i) Q15  : minimum distance to keep             */
     Word16 n                              /* (i)      : number of ISF                        */
);

ATTR_NOMIPS16 Word32 Count_stab_fac(Word16 *isf, Word16 *old_isf);

ATTR_NOMIPS16 void Target_res_synth(
     Word16 *aq,
     Word16 *speech,
     Word16 *exc,
     Word16 *error,
     Word16 lg
);

ATTR_NOMIPS16 void Target_res_deemph2(
     Word16 *ap,
     Word16 *error,
     Word16 *xn,
     Word32 mu,
     Word16 lg,
     Word16 *mem
);

ATTR_NOMIPS16 void Comp_impulse(
     Word16 *aq,
     Word16 *coef,
     Word16 lg
);

void Impulse_deemph2(
     Word16 *h1, 
     Word16 *h2,
     Word16 *xn,
     Word16 shift 
);


ATTR_NOMIPS16 void Low_pass_exc(
    Word16 *exc,
    Word16 *x,
    Word16 lg
);

void Cn_preemph(
     Word16 *x,
     Word16 *y,
     Word32 mu
);

ATTR_NOMIPS16 void Cn_synth_res(
     Word16 *ap,
     Word16 *aq,
     Word16 *x,
     Word16 *y,
     Word16 *exc,
     Word16 lg  
);

void Cn_updt_scale(
     Word16 * x,
     Word16 * x2,
     Word16 * y,
     Word32 gain,
     Word16 shift
);

ATTR_NOMIPS16 Word16 Pitch_conv_gain(
     Word16 *exc,
     Word16 *h,
     Word16 *xn,
     Word16 *y,
     Word16 *g_coeff
);

/*-----------------------------------------------------------------*
 *                       filter prototypes                         *
 *-----------------------------------------------------------------*/

void Init_Decim_12k8(
     Word16 mem[]                          /* output: memory (2*NB_COEF_DOWN) set to zeros */
);
ATTR_NOMIPS16 void Decim_12k8(
     Word16 sig16k[],                      /* input:  signal to downsampling  */
     Word16 lg,                            /* input:  length of input         */
     Word16 sig12k8[],                     /* output: decimated signal        */
     Word32 lg_down,                       /* input:  length after downsampling */
     Word16 mem[],                         /* in/out: memory (2*NB_COEF_DOWN) */
     Word16 *signal
);

void Init_HP50_12k8(Word16 mem[]);
ATTR_NOMIPS16 void HP50_12k8(
     Word16 signal[],                      /* input/output signal */
     Word16 lg,                            /* lenght of signal    */
     Word16 mem[]                          /* filter memory [6]   */
);

void Init_HP400_12k8(Word16 mem[]);
ATTR_NOMIPS16 void HP400_12k8(
     Word16 signal[],                      /* input/output signal */
     Word16 lg,                            /* lenght of signal    */
     Word16 mem[]                          /* filter memory [6]   */
);

void Init_Filt_6k_7k(Word16 mem[]);


ATTR_NOMIPS16 void dtx_gen_white_noise(Word16 *seed,Word16 *exc2,Word16 log_e,Word16 log_m);
ATTR_NOMIPS16 void cal_conv_energy(Word16 *synth,Word16 *exp,Word16 *ener,Word16 *fac);
ATTR_NOMIPS16 Word32 D_UTIL_dot_product12_exc(Word16 x[], Word16 lg, Word16 *exp);
ATTR_NOMIPS16 Word32 D_UTIL_dot_product12_hf(Word16 x[], Word16 lg, Word16 *exp , Word16 * seed);
void pitch_enhancer(Word16 *exc2,Word16 *code,Word32 gain_pit,Word32 L_gain_code,Word16 voice_fac,Word16 Q_new);

ATTR_NOMIPS16 void LP_Decim2(
     Word16 x[],                           // in/out: signal to process
     Word16 mem[]                          // in/out: memory (size=3)
);

void dec_Preemph(
     Word16 x[],                           /* (i/o)   : input signal overwritten by the output */
     Word32 mu                            /* (i) Q15 : preemphasis coefficient                */
    );


Word32 Preem_max(
     Word16 *new_speech,
     Word16 last_preemph
);

void Scale_preem(
     Word16 *new_speech,
     Word16 *last_preemph,
     Word16 scale
);

void Deemph(
     Word16 x[],                           /* (i/o)   : input signal overwritten by the output */
     Word16 mu,                            /* (i) Q15 : deemphasis factor                      */
     Word16 L,                             /* (i)     : vector size                            */
     Word16 * mem                          /* (i/o)   : memory (y[-1])                         */
);

void Deemph_32(
     Word16 x_hi[],                        /* (i)     : input signal (bit31..16) */
     Word16 x_lo[],                        /* (i)     : input signal (bit15..4)  */
     Word16 y[],                           /* (o)     : output signal (x16)      */
     Word16 mu,                            /* (i) Q15 : deemphasis factor        */
     Word16 L,                             /* (i)     : vector size              */
     Word16 * mem                          /* (i/o)   : memory (y[-1])           */
);
void Deemph_32_2(Word32 x[], Word16 y[], Word16 mu, Word16 L, Word16 *mem);
ATTR_NOMIPS16 void Syn_filt_32_2(Word16 a[], Word16 exc[],Word16 Qnew, Word32 sig[],Word16 lg);


ATTR_NOMIPS16 void awe_Residu(
     Word16 a[],                           /* (i) Q12 : prediction coefficients                     */
     Word16 m,                             /* (i)     : order of LP filter                          */
     Word16 x[],                           /* (i)     : speech (values x[-m..-1] are needed         */
     Word16 y[],                           /* (o)     : residual signal                             */
     Word16 lg                             /* (i)     : size of filtering                           */
);



void Residue_exc_Aq1(
     Word16 *aq,                          // (i) Q12 : prediction coefficients
     Word16 *speech,                      // (i)     : speech (values x[-m..-1] are needed
     Word16 *exc
);

ATTR_NOMIPS16 void Syn_filt_M(
     Word16 a[],                           /* (i) Q12 : a[m+1] prediction coefficients           */
     Word16 x[],                           /* (i)     : input signal                             */
     Word16 y[],                           /* (o)     : output signal                            */
     Word16 lg,                            /* (i)     : size of filtering                        */
     Word16 mem[],                         /* (i/o)   : memory associated with this filtering.   */
     Word16 update                         /* (i)     : 0=no update, 1=update of memory.         */
);


void Syn_filt_32(
     Word16 a[],                           /* (i) Q12 : a[m+1] prediction coefficients */

     Word16 exc[],                         /* (i) Qnew: excitation (exc[i] >> Qnew)    */
     Word16 Qnew,                          /* (i)     : exc scaling = 0(min) to 8(max) */
     Word16 sig_hi[],                      /* (o) /16 : synthesis high                 */
     Word16 sig_lo[],                      /* (o) /16 : synthesis low                  */
     Word16 lg                             /* (i)     : size of filtering              */
);

/*-----------------------------------------------------------------*
 *                       pitch prototypes                          *
 *-----------------------------------------------------------------*/


ATTR_NOMIPS16 Word16 Pitch_med_ol(                       /* output: open loop pitch lag                        */
     Word16 wsp[],                         /* input : signal used to compute the open loop pitch */
/* wsp[-pit_max] to wsp[-1] should be known   */
     Word16 L_min,                         /* input : minimum pitch lag                          */
     Word16 L_max,                         /* input : maximum pitch lag                          */
     Word16 L_frame,                       /* input : length of frame to compute pitch           */
     Word16 L_0,                           /* input : old_ open-loop pitch                       */
     Word16 * gain,                        /* output: normalize correlation of hp_wsp for the Lag */
     Word16 * hp_wsp_mem,                  /* i:o   : memory of the hypass filter for hp_wsp[] (lg=9)   */
     Word16 * old_hp_wsp,                  /* i:o   : hypass wsp[]                               */
     Word16 wght_flg                       /* input : is weighting function used                 */
);

void Init_Hp_wsp(Word16 mem[]);
void Scale_old_wsp_hpwsp(
     Word16 *old_wsp,
     Word16 *old_hp_wsp,
     Word16 lg,
     Word16 exp
);
void Scale_mem_Hp_wsp(Word16 mem[], Word16 exp);


Word16 Pitch_fr4(                          /* (o)     : pitch period.                         */
     Word16 exc[],                         /* (i)     : excitation buffer                     */
     Word16 xn[],                          /* (i)     : target vector                         */
     Word16 h[],                           /* (i) Q15 : impulse response of synth/wgt filters */
     Word16 t0_min,                        /* (i)     : minimum value in the searched range.  */
     Word16 t0_max,                        /* (i)     : maximum value in the searched range.  */
     Word16 * pit_frac,                    /* (o)     : chosen fraction (0, 1, 2 or 3).       */
     Word16 i_subfr,                       /* (i)     : indicator for first subframe.         */
     Word16 t0_fr2,                        /* (i)     : minimum value for resolution 1/2      */
     Word16 t0_fr1                        /* (i)     : minimum value for resolution 1        */

);
ATTR_NOMIPS16 void Pred_lt4(
     Word16 exc[],                         /* in/out: excitation buffer */
     Word32 T0,                            /* input : integer pitch lag */
     Word32 frac);                          /* input : fraction of lag   */


/*-----------------------------------------------------------------*
 *                       gain prototypes                           *
 *-----------------------------------------------------------------*/
ATTR_NOMIPS16 Word32 Dot_product12_twice(
     Word16 x1[], 
     Word16 y1[],
     Word16 x2[], 
     Word16 y2[],
     Word32 * mant1,
     Word32 * exp1,
     Word32 * exp2
);
Word16 G_pitch(                            /* (o) Q14 : Gain of pitch lag saturated to 1.2   */
     Word16 xn[],                          /* (i)     : Pitch target.                        */
     Word16 y1[],                          /* (i)     : filtered adaptive codebook.          */
     Word16 g_coeff[],                     /* : Correlations need for gain quantization. */
     Word16 L_subfr                        /* : Length of subframe.                  */
);
void Init_Q_gain2(
     Word16 * mem                          /* output  :static memory (2 words)      */
);
ATTR_NOMIPS16 Word16 Q_gain2(                            /* Return index of quantization.        */
     Word16 xn[],                          /* (i) Q_xn:Target vector.               */
     Word16 y1[],                          /* (i) Q_xn:Adaptive codebook.           */
     Word16 Q_xn,                          /* (i)     :xn and y1 format             */
     Word16 y2[],                          /* (i) Q9  :Filtered innovative vector.  */
     Word16 code[],                        /* (i) Q9  :Innovative vector.           */
     Word16 g_coeff[],                     /* (i)     :Correlations <xn y1> <y1 y1> */
/* Compute in G_pitch().        */
     Word16 nbits,                         /* (i)     : number of bits (6 or 7)     */
     Word32 * gain_pit,                    /* (i/o)Q14:Pitch gain.                  */
     Word32 * gain_cod,                    /* (o) Q16 :Code gain.                   */
     Word16 gp_clip,                       /* (i)     : Gp Clipping flag            */
     Word16 * mem                          /* (i/o)   :static memory (2 words)      */
);

void Init_D_gain2(
     Word16 * mem                          /* output  :static memory (4 words)      */
);


/*-----------------------------------------------------------------*
 *                       acelp prototypes                          *
 *-----------------------------------------------------------------*/

ATTR_NOMIPS16 void awe_cor_h_x(
     Word16 h[],                           /* (i) Q12 : impulse response of weighted synthesis filter */
     Word16 x[],                           /* (i) Q0  : target vector                                 */
     Word16 dn[]                           /* (o) <12bit : correlation between target and h[]         */
);
ATTR_NOMIPS16 void ACELP_2t64_fx(
     Word16 dn[],                          /* (i) <12b : correlation between target x[] and H[]      */
     Word16 cn[],                          /* (i) <12b : residual after long term prediction         */
     Word16 H[],                           /* (i) Q12: impulse response of weighted synthesis filter */
     Word16 code[],                        /* (o) Q9 : algebraic (fixed) codebook excitation         */
     Word16 y[],                           /* (o) Q9 : filtered fixed codebook excitation            */
     Word16 * index                        /* (o) : index (12): 5+1+5+1 = 11 bits.                     */
);
ATTR_NOMIPS16 void ACELP_4t64_fx(
     Word16 dn[],                          /* (i) <12b : correlation between target x[] and H[]      */
     Word16 cn[],                          /* (i) <12b : residual after long term prediction         */
     Word16 H[],                           /* (i) Q12: impulse response of weighted synthesis filter */
     Word16 code[],                        /* (o) Q9 : algebraic (fixed) codebook excitation         */
     Word16 y[],                           /* (o) Q9 : filtered fixed codebook excitation            */
     Word16 nbbits,                        /* (i) : 20, 36, 44, 52, 64, 72 or 88 bits                */
     Word16 ser_size,                      /* (i) : bit rate                                         */
     Word16 _index[]                       /* (o) : index (20): 5+5+5+5 = 20 bits.                   */
										   /* (o) : index (36): 9+9+9+9 = 36 bits.                   */
										   /* (o) : index (44): 13+9+13+9 = 44 bits.                 */
										   /* (o) : index (52): 13+13+13+13 = 52 bits.               */
										   /* (o) : index (64): 2+2+2+2+14+14+14+14 = 64 bits.       */
										   /* (o) : index (72): 10+2+10+2+10+14+10+14 = 72 bits.     */
										   /* (o) : index (88): 11+11+11+11+11+11+11+11 = 88 bits.   */
);
void Pit_shrp(
     Word16 * x,                           /* in/out: impulse response (or algebraic code) */
     Word32 pit_lag,                       /* input : pitch lag                            */
     Word32 sharp                         /* input : pitch sharpening factor (Q15)        */
);


/*-----------------------------------------------------------------*
 *                        others prototypes                        *
 *-----------------------------------------------------------------*/
extern void Copy16(Word16 x[],Word16 y[]);
void Copy16_2(Word32 x[],Word32 y[]);
void Copy_R4(
     Word16 x[],                           /* (i)   : input vector   */
     Word16 y[],                           /* (o)   : output vector  */
     Word16 L                              /* (i)   : vector length  */
);
void awb_Copy(
     Word16 x[],                           /* (i)   : input vector   */
     Word16 y[],                           /* (o)   : output vector  */
     Word16 L                              /* (i)   : vector length  */
);

void awb_Set_zero(
     Word16 x[],                           /* (o)    : vector to clear     */
     Word16 L                              /* (i)    : length of vector    */
);


void Updt_tar(
     Word16 * x,                           /* (i) Q0  : old target (for pitch search)     */
     Word16 * x2,                          /* (o) Q0  : new target (for codebook search)  */
     Word16 * y,                           /* (i) Q0  : filtered adaptive codebook vector */
     Word32 gain                          /* (i) Q14 : adaptive codebook gain            */
);

Word16 voice_factor(                       /* (o) Q15 : factor (-1=unvoiced to 1=voiced) */
     Word16 exc[],                         /* (i) Q_exc: pitch excitation                */
     Word16 Q_exc,                         /* (i)     : exc format                       */
     Word32 gain_pit,                      /* (i) Q14 : gain of pitch                    */
     Word16 code[],                        /* (i) Q9  : Fixed codebook excitation        */
     Word32 gain_code                     /* (i) Q0  : gain of code                     */

);
void Scale_sig(
     Word16 x[],                           /* (i/o) : signal to scale               */
     Word16 lg,                            /* (i)   : size of x[]                   */
     Word16 exp                            /* (i)   : exponent: x = round(x << exp) */
);

void Scale_sig_l(
     Word16 x[],                           /* (i/o) : signal to scale               */
     Word16 lg,                            /* (i)   : size of x[]                   */
     Word16 exp                            /* (i)   : exponent: x = round(x << exp) */
);

void Scale_sig_r(
     Word16 x[],                           /* (i/o) : signal to scale               */
     Word16 lg,                            /* (i)   : size of x[]                   */
     Word16 exp                            /* (i)   : exponent: x = round(x << exp) */
);

void snr(Word16 x[], Word16 y[], Word16 l, Word16 Q_x);

Word16 Random(Word16 * seed);

void Init_gp_clip(
     Word16 mem[]                          /* (o) : memory of gain of pitch clipping algorithm */
);
Word16 Gp_clip(
     Word16 mem[]                          /* (i/o) : memory of gain of pitch clipping algorithm */
);

ATTR_NOMIPS16 void Gp_clip_test_gain_pit(
     Word32 gain_pit,                      /* (i)   : gain of quantized pitch                    */
     Word16 mem[]                          /* (i/o) : memory of gain of pitch clipping algorithm */
);

void Init_Phase_dispersion(
     Word16 disp_mem[]                     /* (i/o): static memory (size = 8) */
);


void Log2 (
    Word32 L_x,        /* (i) : input value                                 */
    Word16 *exponent,  /* (o) : Integer part of Log2.   (range: 0<=val<=30) */
    Word16 *fraction   /* (o) : Fractional part of Log2. (range: 0<=val<1)*/
);

void Log2_norm (
    Word32 L_x,         /* (i) : input value (normalized)                    */
    Word16 exp,         /* (i) : norm_l (L_x)                                */
    Word16 *exponent,   /* (o) : Integer part of Log2.   (range: 0<=val<=30) */
    Word16 *fraction    /* (o) : Fractional part of Log2. (range: 0<=val<1)  */
);



Word16 Med_olag(                           /* output : median of  5 previous open-loop lags       */
     Word16 prev_ol_lag,                   /* input  : previous open-loop lag                     */
     Word16 old_ol_lag[5]
);
ATTR_NOMIPS16 void Hp_wsp(
     Word16 wsp[],                         /* i   : wsp[]  signal       */
     Word16 hp_wsp[],                      /* o   : hypass wsp[]        */
     Word16 lg,                            /* i   : lenght of signal    */
     Word16 mem[]                          /* i/o : filter memory [9]   */
);



Word16 Init_write_serial(TX_State * st);
void Reset_write_serial(TX_State * st);
int Write_serial(unsigned char *outbuf, Word16 prms[], Word16 coding_mode, Word16 mode, TX_State *st, Word16 bitstreamformat);



void Reset_encoder(Coder_State *st, Word16 reset_all);
int awb_encoder_homing_frame_test(Word16 input_frame[]);


void Parm_serial_breakpoint(
     Word16 value,                         /* input : parameter value */
     Word16 no_of_bits,                    /* input : number of bits  */
     Word16 ** prms
);
void Parm_serial(
     Word16 value,                         /* input : parameter value */
     Word16 no_of_bits,                    /* input : number of bits  */
     Word16 ** prms
);
Word16 Serial_parm(                        /* Return the parameter    */
     Word16 no_of_bits,                    /* input : number of bits  */
     Word16 ** prms
);


Word32 quant_1p_N1(                        /* (o) return (N+1) bits           */
     Word16 pos,                           /* (i) position of the pulse       */
     Word16 N);                            /* (i) number of bits for position */

Word32 quant_2p_2N1(                       /* (o) return (2*N)+1 bits         */
     Word16 pos1,                          /* (i) position of the pulse 1     */
     Word16 pos2,                          /* (i) position of the pulse 2     */
     Word16 N);                            /* (i) number of bits for position */

Word32 quant_3p_3N1(                       /* (o) return (3*N)+1 bits         */
     Word16 pos1,                          /* (i) position of the pulse 1     */
     Word16 pos2,                          /* (i) position of the pulse 2     */
     Word16 pos3,                          /* (i) position of the pulse 3     */
     Word16 N);                            /* (i) number of bits for position */

Word32 quant_4p_4N1(                       /* (o) return (4*N)+1 bits         */
     Word16 pos1,                          /* (i) position of the pulse 1     */
     Word16 pos2,                          /* (i) position of the pulse 2     */
     Word16 pos3,                          /* (i) position of the pulse 3     */
     Word16 pos4,                          /* (i) position of the pulse 4     */
     Word16 N);                            /* (i) number of bits for position */

Word32 quant_4p_4N(                        /* (o) return 4*N bits             */
     Word16 pos[],                         /* (i) position of the pulse 1..4  */
     Word16 N);                            /* (i) number of bits for position */

Word32 quant_5p_5N(                        /* (o) return 5*N bits             */
     Word16 pos[],                         /* (i) position of the pulse 1..5  */
     Word16 N);                            /* (i) number of bits for position */

Word32 quant_6p_6N_2(                      /* (o) return (6*N)-2 bits         */
     Word16 pos[],                         /* (i) position of the pulse 1..6  */
     Word16 N);                            /* (i) number of bits for position */



Word16 wb_vad_init(VadVars * st);
Word16 wb_vad_reset(VadVars * st);

void wb_vad_tone_detection(VadVars * st, Word16 p_gain);
ATTR_NOMIPS16 Word16 wb_vad(VadVars * st, Word16 in_buf[]);


/*****************************************************************************
 *
 * DEFINITION OF DATA TYPES
 *****************************************************************************/



Word16 dtx_enc_init(dtx_encState * st, Word16 isf_init[]);
Word16 awb_dtx_enc_reset(dtx_encState * st, Word16 isf_init[]);


ATTR_NOMIPS16 Word16 awb_dtx_enc(
     dtx_encState * st,                    /* i/o : State struct                                         */
     Word16 isf[M],                        /* o   : CN ISF vector                                        */
     Word16 * exc2,                        /* o   : CN excitation                                        */
     Word16 ** prms
);

Word16 awb_dtx_buffer(
     dtx_encState * st,                    /* i/o : State struct                    */
     Word16 isf_new[],                     /* i   : isf vector                      */
     Word32 enr,                           /* i   : residual energy (in L_FRAME)    */
     Word16 codec_mode
);

void awb_tx_dtx_handler(dtx_encState * st,     /* i/o : State struct           */
     Word16 vad_flag,                      /* i   : vad decision           */
     Word16 * usedMode                     /* i/o : mode changed or not    */
);

void Qisf_ns(
     Word16 * isf1,                        /* input : ISF in the frequency domain (0..0.5) */
     Word16 * isf_q,                       /* output: quantized ISF                        */
     Word16 * indice                       /* output: quantization indices                 */
);


void Disf_ns(
     Word16 * indice,                      /* input:  quantization indices                  */
     Word16 * isf_q                        /* input : ISF in the frequency domain (0..0.5)  */
);


Word16 awe_synthesis(
     Word16 Aq[],                          /* A(z)  : quantized Az               */
     Word16 exc[],                         /* (i)   : excitation at 12kHz        */
     Word16 Q_new,                         /* (i)   : scaling performed on exc   */
     Word16 synth16k[],                    /* (o)   : 16kHz synthesis signal     */
     Coder_State * st                      /* (i/o) : State structure            */
);


void Weight_subfr_a(
     Word16 *a,                           // (i) Q12 : a[m+1]  LPC coefficients
     Word16 *ap                           // (o) Q12 : Spectral expanded LPC coefficients
);
ATTR_NOMIPS16 void enc_Isp_Az(
     Word16 *isp,                         // (i) Q15 : Immittance spectral pairs            
     Word16 *a,                           // (o) Q12 : predictor coefficients (order = M)   
     Word16 m,
     Word16 adaptive_scaling              // (i) 0   : adaptive scaling disabled 
                                          //     1   : adaptive scaling enabled  
);
ATTR_NOMIPS16 void Filt_Deemph2_Ap(
     Word16 *ap,                           // (i) Q12 : prediction coefficients
     Word16 m,                             // (i)     : order of LP filter
     Word16 *speech,                       // (i)     : speech (values x[-m..-1] are needed
     Word16 *wsp,                          // (o) x2  : residual signal
     Word16 *mem
);
ATTR_NOMIPS16 void enc_Int_isp(
     Word16 isp_old[],                     // input : isps from past frame             
     Word16 isp_new[],                     // input : isps from present frame          
     Word16 Az[]                           // output: LP coefficients in 4 subframes   
);
#if 1
ATTR_NOMIPS16 void Filt_6k_7k(Word16 signal[], Word16 mem[]);
ATTR_NOMIPS16 int calc_mantissa_exp(Word16 signal[], Word16 *exp);
#else
ATTR_NOMIPS16 int Filt_6k_7k_HF(Word16 signal[], Word16 mem[],Word16 *exp);
#endif

Word32 D_UTIL_Isqrt(                              /* (o) Q31 : output value (range: 0<=val<1)         */
     Word32 L_x                            /* (i) Q0  : input value  (range: 0<=val<=7fffffff) */
);


ATTR_NOMIPS16 int Filt_6k_7k_synth(Word16 signal[], Word16 mem[],Word16 *exp);
void Copy30(Word16 *src, Word16 *dst);

Word32 D_UTIL_Square(Word32 val);
ATTR_NOMIPS16 Word16 D_UTIL_norm_l(Word32 L_var1);
ATTR_NOMIPS16 Word16 D_UTIL_norm_s (Word16 var1);
ATTR_NOMIPS16 Word32 sat_shl(Word32 L_tmp, Word16 var2);
Word32 D_UTIL_Pow2(Word16 exponant, Word16 fraction);
void D_UTIL_Log2(int L_x,Word16 *exponent,Word16 *fraction);
void D_UTIL_Isqrt_n(Word32 * frac, Word16 * exp);

ATTR_NOMIPS16 Word32 D_UTIL_Div_32 (Word32 L_num, Word32 L_denom);


#endif


