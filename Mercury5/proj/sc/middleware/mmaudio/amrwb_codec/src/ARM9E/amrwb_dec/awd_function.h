#ifndef AMR_DECODER_BITEXACT_FUNCTION_INCLUDE
#define AMR_DECODER_BITEXACT_FUNCTION_INCLUDE


Word16 Init_read_serial(RX_State * st);
Word16 Close_read_serial(RX_State *st);
void Reset_read_serial(RX_State * st);

Word16 Read_serial(unsigned char *inbuf, int len,Word16 prms[], Word16 * frame_type, Word16 * mode, RX_State *st, Word16 bitstreamformat);

unsigned int Serial_parm(Word16 no_of_bits,Decoder_State *st);


void pitch_enhancer(Word16 *exc2,Word16 *code,Word32 gain_pit,Word32 L_gain_code,Word16 voice_fac,Word16 Q_new);

/*--------------------------------------------------------------------------*
 *                         MATH_OP.H	                                    *
 *--------------------------------------------------------------------------*
 *       Mathematical operations					                        *
 *--------------------------------------------------------------------------*/

Word32 D_UTIL_Isqrt(                              /* (o) Q31 : output value (range: 0<=val<1)         */
     Word32 L_x                            /* (i) Q0  : input value  (range: 0<=val<=7fffffff) */
);

Word32 D_UTIL_Pow2(                               /* (o) Q0  : result       (range: 0<=val<=0x7fffffff) */
     Word16 exponant,                      /* (i) Q0  : Integer part.      (range: 0<=val<=30)   */
     Word16 fraction                       /* (i) Q15 : Fractionnal part.  (range: 0.0<=val<1.0) */
);
ATTR_NOMIPS16 Word32 Dot_product12(                      /* (o) Q31: normalized result (1 < val <= -1) */
     Word16 x[],                           /* (i) 12bits: x vector                       */
     Word16 y[],                           /* (i) 12bits: y vector                       */
     Word16 lg,                            /* (i)    : vector length                     */
     Word16 * exp                          /* (o)    : exponent of result (0..+30)       */
);



void dec_1p_N1(Word32 index, Word16 N, Word16 offset, Word16 pos[]);
void dec_2p_2N1(Word32 index, Word16 N, Word16 offset, Word16 pos[]);
void dec_3p_3N1(Word32 index, Word16 N, Word16 offset, Word16 pos[]);
void dec_4p_4N1(Word32 index, Word16 N, Word16 offset, Word16 pos[]);
void dec_4p_4N(Word32 index, Word16 N, Word16 offset, Word16 pos[]);
void dec_5p_5N(Word32 index, Word16 N, Word16 offset, Word16 pos[]);
void dec_6p_6N_2(Word32 index, Word16 N, Word16 offset, Word16 pos[]);



void Init_coder(void **spe_state);
void Close_coder(void *spe_state);

void coder(
     Word16 * mode,                        /* input :  used mode                             */
     Word16 speech16k[],                   /* input :  320 new speech samples (at 16 kHz)    */
     Word16 prms[],                        /* output:  output parameters           */
     Word16 * ser_size,                    /* output:  bit rate of the used mode   */
     void *spe_state,                      /* i/o   :  State structure                       */
     Word16 allow_dtx                      /* input :  DTX ON/OFF                            */
);
void Init_decoder(Decoder_State *st);
//void Close_decoder(Decoder_State *st);
//void Init_decoder(void **spd_state);
//void Close_decoder(void *spd_state);

void decoder(
     Word16 mode,                          /* input : used mode                     */
     Word16 prms[],                        /* input : parameter vector                     */
     Word16 synth16k[],                    /* output: synthesis speech              */
     Word16 * frame_length,                /* output:  lenght of the frame         */
     Decoder_State *st,                      /* i/o   : State structure                      */
     Word16 frame_type                     /* input : received frame type           */
);


//void Reset_decoder(void *st, Word16 reset_all);
void Reset_decoder(Decoder_State *st, Word16 reset_all);

Word16 awb_decoder_homing_frame_test(Decoder_State *st, Word16 mode);

Word16 awb_decoder_homing_frame_test_first(Decoder_State *st, Word16 mode);



Word16 dtx_dec_init(dtx_decState * st, Word16 isf_init[]);
Word16 awb_dtx_dec_reset(dtx_decState * st, Word16 isf_init[]);
//void dtx_dec_exit(dtx_decState * st);

Word16 awb_dtx_dec(
     dtx_decState * st,                    /* i/o : State struct                                          */
     Word16 * exc2,                        /* o   : CN excitation                                          */
     Word16 new_state,                     /* i   : New DTX state                                          */
     Word16 isf[],                         /* o   : CN ISF vector                                          */
     Decoder_State *dst
);

void awb_dtx_dec_activity_update(
     dtx_decState * st,
     Word16 isf[],
     Word16 exc[], Word16 Q_new);


Word16 awb_rx_dtx_handler(
     dtx_decState * st,                    /* i/o : State struct     */
     Word16 frame_type                     /* i   : Frame type       */
);

void Disf_ns(
     Word16 * indice,                      /* input:  quantization indices                  */
     Word16 * isf_q                        /* input : ISF in the frequency domain (0..0.5)  */
);


void dec_Preemph(
     Word16 x[],                           /* (i/o)   : input signal overwritten by the output */
     Word32 mu                            /* (i) Q15 : preemphasis coefficient                */
);

void Pit_shrp(
     Word16 * x,                           /* in/out: impulse response (or algebraic code) */
     Word32 pit_lag,                       /* input : pitch lag                            */
     Word32 sharp                         /* input : pitch sharpening factor (Q15)        */
);



void D_UTIL_Log2 (
    Word32 L_x,         /* (i) : input value                                 */
    Word16 *exponent,   /* (o) : Integer part of Log2.   (range: 0<=val<=30) */
    Word16 *fraction    /* (o) : Fractional part of Log2. (range: 0<=val<1) */
);




Word16 dec_voice_factor(                       /* (o) Q15   : factor (-1=unvoiced to 1=voiced) */
     Word32 exc2_sum_square,               
     Word16 Q_exc,                         /* (i)       : exc format                       */
     Word32 gain_pit,                      /* (i) Q14   : gain of pitch                    */
     Word32 code_sum_square,                        /* (i) Q9    : Fixed codebook excitation        */
     Word32 gain_code,                     /* (i) Q0    : gain of code                     */
     Word16 L_subfr                        /* (i)       : subframe length                  */
);
ATTR_NOMIPS16 void cal_conv_energy(Word16 *synth,Word16 *exp,Word16 *ener,Word16 *fac);
ATTR_NOMIPS16 Word32 D_UTIL_dot_product12_exc(Word16 x[], Word16 lg, Word16 *exp);
ATTR_NOMIPS16 Word32 D_UTIL_dot_product12_hf(Word16 x[], Word16 lg, Word16 *exp , Word16 * seed);
ATTR_NOMIPS16 void awb_agc2(Word16 *sig_in, Word32 *sig_out);


void synthesis(
     Word16 Aq[],                          /* A(z)  : quantized Az               */
     Word16 exc[],                         /* (i)   : excitation at 12kHz        */
     Word16 Q_new,                         /* (i)   : scaling performed on exc   */
     Word16 synth16k[],                    /* (o)   : 16kHz synthesis signal     */
     Word16 prms,                          /* (i)   : parameter                  */
     Word16 HfIsf[],
     Word16 nb_bits,
     Word16 newDTXState,
     Decoder_State * st,                   /* (i/o) : State structure            */
     Word16 bfi                            /* (i)   : bad frame indicator        */
);
ATTR_NOMIPS16 void dtx_gen_white_noise(Word16 *seed,Word16 *exc2,Word16 log_e,Word16 log_m);


void D_UTIL_Isqrt_n(Word32 * frac, Word16 * exp);

void Deemph_32(Word16 x_hi[], Word16 x_lo[], Word16 y[],
                      Word16 mu, Word16 L, Word16 *mem);

void Deemph_32_2(Word32 x[], Word16 y[],
                      Word16 mu, Word16 L, Word16 *mem);


void dec_synthesis(
     Word16 Aq[],                          /* A(z)  : quantized Az               */
     Word16 exc[],                         /* (i)   : excitation at 12kHz        */
     Word16 Q_new,                         /* (i)   : scaling performed on exc   */
     Word16 synth16k[],                    /* (o)   : 16kHz synthesis signal     */
     Word16 prms,                          /* (i)   : parameter                  */
     Word16 HfIsf[],
     Word16 nb_bits,
     Word16 newDTXState,
     Decoder_State * st,                   /* (i/o) : State structure            */
     Word16 bfi                            /* (i)   : bad frame indicator        */
);


ATTR_NOMIPS16 void Pred_lt4(Word16 exc[], Word32 T0, Word32 frac);


void dec_gain2(
     Word16 index,                         /* (i)     : index of quantization.      */
     Word16 nbits,                         /* (i)     : number of bits (6 or 7)     */
     Word16 code[],                        /* (i) Q9  : Innovative vector.          */
     Word16 L_subfr,                       /* (i)     : Subframe lenght.            */
     Word32 * gain_pit,                    /* (o) Q14 : Pitch gain.                 */
     Word32 * gain_cod,                    /* (o) Q16 : Code gain.                  */
     Word16 bfi,                           /* (i)     : bad frame indicator         */
     Word16 prev_bfi,                      /* (i)     : Previous BF indicator       */
     Word16 state,                         /* (i)     : State of BFH                */
     Word16 unusable_frame,                /* (i)     : UF indicator                */
     Word16 vad_hist,                      /* (i)     : number of non-speech frames */
     Word16 * mem                          /* (i/o)   : static memory (4 words)     */
);

void Phase_dispersion(
     Word32 gain_code,                     /* (i) Q0  : gain of code             */
     Word32 gain_pit,                      /* (i) Q14 : gain of pitch            */
     Word16 code[],                        /* (i/o)   : code vector              */
     Word16 mode,                          /* (i)     : level, 0=hi, 1=lo, 2=off */
     Word16 disp_mem[]                     /* (i/o)   : static memory (size = 8) */
);


ATTR_NOMIPS16 void Syn_filt_32_2(Word16 a[], Word16 exc[],Word16 Qnew, Word32 sig[],Word16 lg);

void Copy32(
     Word32 x[],                           /* (i)   : input vector   */
     Word32 y[],                           /* (o)   : output vector  */
     Word16 L                              /* (i)   : vector length  */
);
void Set_zero32(
     Word32 x[],                           /* (o)    : vector to clear     */
     Word16 L                              /* (i)    : length of vector    */
);

ATTR_NOMIPS16 void Oversamp_16k(Word16 sig12k8[], Word16 sig16k[],
                         Word16 mem[]);


void bit_convert(Word16 *prms,unsigned int *bs_buf, int no_of_bits);
void amr_dec_stream_reset(Decoder_State *st);


/*-----------------------------------------------------------------*
 *                        LPC prototypes                           *
 *-----------------------------------------------------------------*/

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


void Init_Filt_7k(Word16 mem[]);
ATTR_NOMIPS16 void Filt_7k(
     Word16 signal[],                      /* input:  signal                  */
     Word16 lg,                            /* input:  length of input         */
     Word16 mem[]                          /* in/out: memory (size=30)        */
);

Word16 median5(Word16 x[]);

void Autocorr(
     Word16 x[],                           /* (i)    : Input signal                      */
     Word16 m,                             /* (i)    : LPC order                         */
     Word16 r_h[],                         /* (o)    : Autocorrelations  (msb)           */
     Word16 r_l[]                          /* (o)    : Autocorrelations  (lsb)           */
);
void Lag_window(
     Word16 r_h[],                         /* (i/o)   : Autocorrelations  (msb)          */
     Word16 r_l[]                          /* (i/o)   : Autocorrelations  (lsb)          */
);
void Init_Levinson(
     Word16 * mem                          /* output  :static memory (18 words) */
);
void Levinson(
     Word16 Rh[],                          /* (i)     : Rh[M+1] Vector of autocorrelations (msb) */
     Word16 Rl[],                          /* (i)     : Rl[M+1] Vector of autocorrelations (lsb) */
     Word16 A[],                           /* (o) Q12 : A[M]    LPC coefficients  (m = 16)       */
     Word16 rc[],                          /* (o) Q15 : rc[M]   Reflection coefficients.         */
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
     Word16 isp[],                         /* (i) Q15 : isp[m] (range: -1<=val<1)                */
     Word16 isf[],                         /* (o) Q15 : isf[m] normalized (range: 0.0<=val<=0.5) */
     Word16 m                              /* (i)     : LPC order                                */
);
void Isf_isp(
     Word16 isf[],                         /* (i) Q15 : isf[m] normalized (range: 0.0<=val<=0.5) */
     Word16 isp[],                         /* (o) Q15 : isp[m] (range: -1<=val<1)                */
     Word16 m                              /* (i)     : LPC order                                */
);
ATTR_NOMIPS16 void dec_Int_isp(
     Word16 isp_old[],                     /* input : isps from past frame              */
     Word16 isp_new[],                     /* input : isps from present frame           */
     Word16 frac[],                        /* input : fraction for 3 first subfr (Q15)  */
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
     Word16 * isf1,                        /* (i) Q15 : ISF in the frequency domain (0..0.5) */
     Word16 * isf_q,                       /* (o) Q15 : quantized ISF               (0..0.5) */
     Word16 * past_isfq,                   /* (io)Q15 : past ISF quantizer                   */
     Word16 * indice,                      /* (o)     : quantization indices                 */
     Word16 nb_surv                        /* (i)     : number of survivor (1, 2, 3 or 4)    */
);
void Qpisf_2s_36b(
     Word16 * isf1,                        /* (i) Q15 : ISF in the frequency domain (0..0.5) */
     Word16 * isf_q,                       /* (o) Q15 : quantized ISF               (0..0.5) */
     Word16 * past_isfq,                   /* (io)Q15 : past ISF quantizer                   */
     Word16 * indice,                      /* (o)     : quantization indices                 */
     Word16 nb_surv                        /* (i)     : number of survivor (1, 2, 3 or 4)    */
);
void Dpisf_2s_46b(
     Word16 * indice,                      /* input:  quantization indices                       */
     Word16 * isf_q,                       /* output: quantized ISF in frequency domain (0..0.5) */
     Word16 * past_isfq,                   /* i/0   : past ISF quantizer                    */
     Word16 * isfold,                      /* input : past quantized ISF                    */
     Word16 * isf_buf,                     /* input : isf buffer                                                        */
     Word16 bfi,                           /* input : Bad frame indicator                   */
     Word16 enc_dec
);
void Dpisf_2s_36b(
     Word16 * indice,                      /* input:  quantization indices                       */
     Word16 * isf_q,                       /* output: quantized ISF in frequency domain (0..0.5) */
     Word16 * past_isfq,                   /* i/0   : past ISF quantizer                    */
     Word16 * isfold,                      /* input : past quantized ISF                    */
     Word16 * isf_buf,                     /* input : isf buffer                                                        */
     Word16 bfi,                           /* input : Bad frame indicator                   */
     Word16 enc_dec
);

void Disf_ns(
     Word16 * indice,                      /* input:  quantization indices                  */
     Word16 * isf_q                        /* input : ISF in the frequency domain (0..0.5)  */
);

void Reorder_isf(
     Word16 * isf,                         /* (i/o) Q15: ISF in the frequency domain (0..0.5) */
     Word16 min_dist,                      /* (i) Q15  : minimum distance to keep             */
     Word16 n                              /* (i)      : number of ISF                        */
);
Word16 Serial_parm16(Word16 no_of_bits,Decoder_State *st);
/*-----------------------------------------------------------------*
 *                       filter prototypes                         *
 *-----------------------------------------------------------------*/

void Copy30(Word16 *src, Word16 *dst);
void Decim_12k8(
     Word16 sig16k[],                      /* input:  signal to downsampling  */
     Word16 lg,                            /* input:  length of input         */
     Word16 sig12k8[],                     /* output: decimated signal        */
     Word16 mem[]                          /* in/out: memory (2*NB_COEF_DOWN) */
);

void Init_Oversamp_16k(
     Word16 mem[]                          /* output: memory (2*NB_COEF_UP) set to zeros  */
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
extern void Copy16(Word16 x[],Word16 y[]);
void Init_Filt_6k_7k(Word16 mem[]);
ATTR_NOMIPS16 void Filt_6k_7k(
     Word16 signal[],                      /* input:  signal                  */
     Word16 mem[]                          /* in/out: memory (size=30)        */
);

void LP_Decim2(
     Word16 x[],                           /* in/out: signal to process         */
     Word16 l,                             /* input : size of filtering         */
     Word16 mem[]                          /* in/out: memory (size=3)           */
);

void Preemph(
     Word16 x[],                           /* (i/o)   : input signal overwritten by the output */
     Word16 mu,                            /* (i) Q15 : preemphasis coefficient                */
     Word16 lg,                            /* (i)     : lenght of filtering                    */
     Word16 * mem                          /* (i/o)   : memory (x[-1])                         */
);

void Deemph(
     Word16 x[],                           /* (i/o)   : input signal overwritten by the output */
     Word16 mu,                            /* (i) Q15 : deemphasis factor                      */
     Word16 L,                             /* (i)     : vector size                            */
     Word16 * mem                          /* (i/o)   : memory (y[-1])                         */
);



void Convolve(
     Word16 x[],                           /* (i)     : input vector                              */
     Word16 h[],                           /* (i) Q15    : impulse response                       */
     Word16 y[],                           /* (o) 12 bits: output vector                          */
     Word16 L                              /* (i)     : vector size                               */
);

void Residu(
     Word16 a[],                           /* (i) Q12 : prediction coefficients                     */
     Word16 m,                             /* (i)     : order of LP filter                          */
     Word16 x[],                           /* (i)     : speech (values x[-m..-1] are needed         */
     Word16 y[],                           /* (o)     : residual signal                             */
     Word16 lg                             /* (i)     : size of filtering                           */
);
ATTR_NOMIPS16 void Syn_filt_M16k(
     Word16 a[],                           /* (i) Q12 : a[m+1] prediction coefficients           */
     Word16 y[],                           /* (o)     : output signal                            */
     Word16 lg,                            /* (i)     : size of filtering                        */
     Word16 mem[],                         /* (i/o)   : memory associated with this filtering.   */
     Word16 update                         /* (i)     : 0=no update, 1=update of memory.         */
);
ATTR_NOMIPS16 void Syn_filt_M(
     Word16 a[],                           /* (i) Q12 : a[m+1] prediction coefficients           */
     Word16 x[],
     Word16 y[],                           /* (o)     : output signal                            */
     Word16 lg,                            /* (i)     : size of filtering                        */
     Word16 mem[],                         /* (i/o)   : memory associated with this filtering.   */
     Word16 update                         /* (i)     : 0=no update, 1=update of memory.         */
);
ATTR_NOMIPS16 void Syn_filt_32(
     Word16 a[],                           /* (i) Q12 : a[m+1] prediction coefficients */
     Word16 exc[],                         /* (i) Qnew: excitation (exc[i] >> Qnew)    */
     Word16 Qnew,                          /* (i)     : exc scaling = 0(min) to 8(max) */
     Word16 sig_hi[],                      /* (o) /16 : synthesis high                 */
     Word16 sig_lo[],                      /* (o) /16 : synthesis low                  */
     Word16 lg                             /* (i)     : size of filtering              */
);
ATTR_NOMIPS16 Word16 D_UTIL_norm_s(Word16 var1);
ATTR_NOMIPS16 Word16 D_UTIL_norm_l (Word32 L_var1);
/*-----------------------------------------------------------------*
 *                       pitch prototypes                          *
 *-----------------------------------------------------------------*/

Word16 Pitch_ol(                           /* output: open loop pitch lag                        */
     Word16 signal[],                      /* input : signal used to compute the open loop pitch */
/* signal[-pit_max] to signal[-1] should be known */
     Word16 pit_min,                       /* input : minimum pitch lag                          */
     Word16 pit_max,                       /* input : maximum pitch lag                          */
     Word16 L_frame                        /* input : length of frame to compute pitch           */
);

Word16 Pitch_med_ol(                       /* output: open loop pitch lag                        */
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
Word16 Med_olag(                           /* output : median of  5 previous open-loop lags       */
     Word16 prev_ol_lag,                   /* input  : previous open-loop lag                     */
     Word16 old_ol_lag[5]
);
void Init_Hp_wsp(Word16 mem[]);

void Hp_wsp(
     Word16 wsp[],                         /* i   : wsp[]  signal       */
     Word16 hp_wsp[],                      /* o   : hypass wsp[]        */
     Word16 lg,                            /* i   : lenght of signal    */
     Word16 mem[]                          /* i/o : filter memory [9]   */
);


/*-----------------------------------------------------------------*
 *                       gain prototypes                           *
 *-----------------------------------------------------------------*/

Word16 G_pitch(                            /* (o) Q14 : Gain of pitch lag saturated to 1.2   */
     Word16 xn[],                          /* (i)     : Pitch target.                        */
     Word16 y1[],                          /* (i)     : filtered adaptive codebook.          */
     Word16 g_coeff[],                     /* : Correlations need for gain quantization. */
     Word16 L_subfr                        /* : Length of subframe.                  */
);



void Init_D_gain2(
     Word16 * mem                          /* output  :static memory (4 words)      */
);



/*-----------------------------------------------------------------*
 *                       acelp prototypes                          *
 *-----------------------------------------------------------------*/

void cor_h_x(
     Word16 h[],                           /* (i) Q12 : impulse response of weighted synthesis filter */
     Word16 x[],                           /* (i) Q0  : target vector                                 */
     Word16 dn[]                           /* (o) <12bit : correlation between target and h[]         */
);
void ACELP_2t64_fx(
     Word16 dn[],                          /* (i) <12b : correlation between target x[] and H[]      */
     Word16 cn[],                          /* (i) <12b : residual after long term prediction         */
     Word16 H[],                           /* (i) Q12: impulse response of weighted synthesis filter */
     Word16 code[],                        /* (o) Q9 : algebraic (fixed) codebook excitation         */
     Word16 y[],                           /* (o) Q9 : filtered fixed codebook excitation            */
     Word16 * index                        /* (o) : index (12): 5+1+5+1 = 11 bits.                     */
);
void DEC_ACELP_2t64_fx(
     Word16 index,                         /* (i) :    12 bits index                                  */
     Word16 code[]                         /* (o) :Q9  algebraic (fixed) codebook excitation          */
);
void ACELP_4t64_fx(
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
void DEC_ACELP_4t64_fx(
     Word32 index[],                       /* (i) : index (20): 5+5+5+5 = 20 bits.                 */
										   /* (i) : index (36): 9+9+9+9 = 36 bits.                 */
										   /* (i) : index (44): 13+9+13+9 = 44 bits.               */
										   /* (i) : index (52): 13+13+13+13 = 52 bits.             */
										   /* (i) : index (64): 2+2+2+2+14+14+14+14 = 64 bits.     */
										   /* (i) : index (72): 10+2+10+2+10+14+10+14 = 72 bits.   */
										   /* (i) : index (88): 11+11+11+11+11+11+11+11 = 88 bits. */
     Word16 nbbits,                        /* (i) : 20, 36, 44, 52, 64, 72 or 88 bits              */
     Word16 code[]                         /* (o) Q9: algebraic (fixed) codebook excitation        */
);



/*-----------------------------------------------------------------*
 *                        others prototypes                        *
 *-----------------------------------------------------------------*/
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
     Word16 gain,                          /* (i) Q14 : adaptive codebook gain            */
     Word16 L                              /* (i)     : subframe size                     */
);

void Scale_sig(
     Word16 x[],                           /* (i/o) : signal to scale               */
     Word16 lg,                            /* (i)   : size of x[]                   */
     Word16 exp                            /* (i)   : exponent: x = round(x << exp) */
);


void Init_gp_clip(
     Word16 mem[]                          /* (o) : memory of gain of pitch clipping algorithm */
);
Word16 Gp_clip(
     Word16 mem[]                          /* (i/o) : memory of gain of pitch clipping algorithm */
);
void Gp_clip_test_isf(
     Word16 isf[],                         /* (i)   : isf values (in frequency domain)           */
     Word16 mem[]                          /* (i/o) : memory of gain of pitch clipping algorithm */
);


void Init_Phase_dispersion(
     Word16 disp_mem[]                     /* (i/o): static memory (size = 8) */
);



#endif

