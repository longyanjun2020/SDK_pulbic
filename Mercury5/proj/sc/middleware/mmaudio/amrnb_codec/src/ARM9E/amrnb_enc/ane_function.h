#ifndef __AMRNB_ENCODER_FUNCTION_INCLUDE_FILE__
#define __AMRNB_ENCODER_FUNCTION_INCLUDE_FILE__




void Levinson_reset (LevinsonState *st);

int Levinson (
    LevinsonState *st,
    Word16 Rh[],       /* i : Rh[m+1] Vector of autocorrelations (msb) */
    Word16 Rl[],       /* i : Rl[m+1] Vector of autocorrelations (lsb) */
    Word16 A[],        /* o : A[m]    LPC coefficients  (m = 10)       */
    Word16 rc[]        /* o : rc[4]   First 4 reflection coefficients  */
);


void lpc_reset (lpcState *st);


int lpc(
    lpcState *st,     /* i/o: State struct                */
    Word16 mode,   /* i  : coder mode                  */
    Word16 x[],       /* i  : Input signal           Q15  */
    Word16 x_12k2[],  /* i  : Input signal (EFR)     Q15  */
    Word16 a[]        /* o  : predictor coefficients Q12  */
);



int lsp_reset (lspState *st);
int lsp(lspState *st,        /* i/o : State struct                            */
        Word16 req_mode,  /* i   : requested coder mode                    */
        Word16 used_mode, /* i   : used coder mode                         */        
        Word16 az[],         /* i/o : interpolated LP parameters Q12          */
        Word16 azQ[],        /* o   : quantization interpol. LP parameters Q12*/
        Word16 lsp_new[],    /* o   : new lsp vector                          */ 
        Word16 **anap        /* o   : analysis parameters                     */
        );


void Q_plsf_3(
    Q_plsfState *st,    /* i/o: state struct                             */
    Word16 mode,     /* i  : coder mode                               */
    Word16 *lsp1,       /* i  : 1st LSP vector                      Q15  */
    Word16 *lsp1_q,     /* o  : quantized 1st LSP vector            Q15  */
    Word16 *indice,     /* o  : quantization indices of 3 vectors   Q0   */
    Word16 *pred_init_i /* o  : init index for MA prediction in DTX mode */
);

void Q_plsf_5 (
    Q_plsfState *st,
    Word16 *lsp1,      /* i  : 1st LSP vector,                     Q15 */
    Word16 *lsp2,      /* i  : 2nd LSP vector,                     Q15 */   
    Word16 *lsp1_q,    /* o  : quantized 1st LSP vector,           Q15 */
    Word16 *lsp2_q,    /* o  : quantized 2nd LSP vector,           Q15 */
    Word16 *indice     /* o  : quantization indices of 5 matrices, Q0  */
);

int ol_ltp(
    pitchOLWghtState *st, /* i/o : State struct                            */
    vadState *vadSt,      /* i/o : VAD state struct                        */
    Word16 mode,       /* i   : coder mode                              */
    Word16 wsp[],         /* i   : signal used to compute the OL pitch, Q0 */
                          /*       uses signal[-pit_max] to signal[-1]     */
    Word16 *T_op,         /* o   : open loop pitch lag,                 Q0 */
    Word16 old_lags[],    /* i   : history with old stored Cl lags         */
    Word16 ol_gain_flg[], /* i   : OL gain flag                            */
    Word16 idx,           /* i   : index                                   */
    Flag dtx              /* i   : dtx flag; use dtx=1, do not use dtx=0   */
);

void p_ol_wgh_reset (pitchOLWghtState *st);



Word16 Pitch_ol_wgh (     /* o   : open loop pitch lag                            */
    pitchOLWghtState *st, /* i/o : State struct                                   */
    vadState *vadSt,      /* i/o : VAD state struct                               */
    Word16 signal[],      /* i   : signal used to compute the open loop pitch     */
                          /*       signal[-pit_max] to signal[-1] should be known */
    Word16 pit_min,       /* i   : minimum pitch lag                              */
    Word16 pit_max,       /* i   : maximum pitch lag                              */
    Word16 L_frame,       /* i   : length of frame to compute pitch               */
    Word16 old_lags[],    /* i   : history with old stored Cl lags                */
    Word16 ol_gain_flg[], /* i   : OL gain flag                                   */
    Word16 idx,           /* i   : index                                          */
    Flag dtx              /* i   : dtx flag; use dtx=1, do not use dtx=0          */
    );


Word16 Pitch_fr (        /* o   : pitch period (integer)                    */
    cod_amrState *st,   /* i/o : State struct                              */
    Word16 mode,      /* i   : codec mode                                */
    Word16 T_op[],       /* i   : open loop pitch lags                      */
    Word16 exc[],        /* i   : excitation buffer                         */
    Word16 xn[],         /* i   : target vector                             */
    Word16 h[],          /* i   : impulse response of synthesis and   
                                  weighting filters                         */
    Word16 i_subfr,      /* i   : subframe offset                           */
    Word16 *pit_frac,    /* o   : pitch period (fractional)                 */
    Word16 *resu3,       /* o   : subsample resolution 1/3 (=1) or 1/6 (=0) */
    Word16 *ana_index    /* o   : index of encoding                         */
);



 
//int cl_ltp_reset (clLtpState *st);



int cl_ltp(
    cod_amrState *st,    /* i/o : State struct                              */
    tonStabState *tonSt, /* i/o : State struct                              */
    Word16 mode,      /* i   : coder mode                                */
    Word16 frameOffset,  /* i   : Offset to subframe                        */
    Word16 T_op[],       /* i   : Open loop pitch lags                      */
    Word16 *h1,          /* i   : Impulse response vector               Q12 */
    Word16 *exc,         /* i/o : Excitation vector                      Q0 */
    Word16 res2[],       /* i/o : Long term prediction residual          Q0 */
    Word16 xn[],         /* i   : Target vector for pitch search         Q0 */
    Word16 lsp_flag,     /* i   : LSP resonance flag                        */
    Word16 xn2[],        /* o   : Target vector for codebook search      Q0 */
    Word16 y1[],         /* o   : Filtered adaptive excitation           Q0 */
    Word16 *T0,          /* o   : Pitch delay (integer part)                */
    Word16 *T0_frac,     /* o   : Pitch delay (fractional part)             */
    Word16 *gain_pit,    /* o   : Pitch gain                            Q14 */
    Word16 g_coeff[],    /* o   : Correlations between xn, y1, & y2         */
    Word16 **anap,       /* o   : Analysis parameters                       */
    Word16 *gp_limit     /* o   : pitch gain limit                          */
);

void gainQuant_init (gainQuantState *s);

#ifdef SUPPORT_HOMING
int gainQuant_reset (gainQuantState *st);
#endif



int gainQuant(
    gainQuantState *st,   /* i/o : State struct                      */
    Word16 mode,       /* i   : coder mode                        */
    Word16 res[],         /* i   : LP residual,                 Q0   */
    Word16 exc[],         /* i   : LTP excitation (unfiltered), Q0   */
    Word16 code[],        /* i   : CB innovation (unfiltered),  Q13  */
                          /*       (unsharpened for MR475)           */
    Word16 xn[],          /* i   : Target vector.                    */
    Word16 xn2[],         /* i   : Target vector.                    */
    Word16 y1[],          /* i   : Adaptive codebook.                */
    Word16 Y2[],          /* i   : Filtered innovative vector.       */
    Word16 g_coeff[],     /* i   : Correlations <xn y1> <y1 y1>      */
                          /*       Compute in G_pitch().             */
    Word16 even_subframe, /* i   : even subframe indicator flag      */
    Word16 gp_limit,      /* i   : pitch gain limit                  */
    Word16 *sf0_gain_pit, /* o   : Pitch gain sf 0.   MR475          */
    Word16 *sf0_gain_cod, /* o   : Code gain sf 0.    MR475          */
    Word16 *gain_pit,     /* i/o : Pitch gain.                       */
    Word16 *gain_cod,     /* o   : Code gain.                        */
                          /*       MR475: gain_* unquantized in even */
                          /*       subframes, quantized otherwise    */
    Word16 **anap         /* o   : Index of quantization             */
);


#ifdef SUPPORT_HOMING
int gain_adapt_reset (GainAdaptState *st);
#endif
void gain_adapt(
    GainAdaptState *st,  /* i  : state struct                  */
    Word16 ltpg,         /* i  : ltp coding gain (log2()), Q   */
    Word16 gain_cod,     /* i  : code gain,                Q13 */
    Word16 *alpha        /* o  : gain adaptation factor,   Q15 */
);







Word16
Qua_gain(                   /* o  : index of quantization.                 */   
    Word16 mode,         /* i  : AMR mode                               */
    Word16 exp_gcode0,      /* i  : predicted CB gain (exponent),      Q0  */
    Word16 frac_gcode0,     /* i  : predicted CB gain (fraction),      Q15 */
    Word16 frac_coeff[],    /* i  : energy coeff. (5), fraction part,  Q15 */
    Word16 exp_coeff[],     /* i  : energy coeff. (5), exponent part,  Q0  */
                            /*      (frac_coeff and exp_coeff computed in  */
                            /*       calc_filt_energies())                 */
    Word16 gp_limit,        /* i  : pitch gain limit                       */
    Word16 *gain_pit,       /* o  : Pitch gain,                        Q14 */
    Word16 *gain_cod,       /* o  : Code gain,                         Q1  */
    Word16 *qua_ener_MR122, /* o  : quantized energy error,            Q10 */
                            /*      (for MR122 MA predictor update)        */
    Word16 *qua_ener        /* o  : quantized energy error,            Q10 */
                            /*      (for other MA predictor update)        */
);

int pre_big(
    Word16 mode,            /* i  : coder mode                             */
    const Word16 gamma1[],     /* i  : spectral exp. factor 1                 */
    const Word16 gamma1_12k2[],/* i  : spectral exp. factor 1 for EFR         */
    const Word16 gamma2[],     /* i  : spectral exp. factor 2                 */
    Word16 A_t[],              /* i  : A(z) unquantized, for 4 subframes, Q12 */
    Word16 frameOffset,        /* i  : Start position in speech vector,   Q0  */
    Word16 speech[],           /* i  : speech,                            Q0  */
    Word16 mem_w[],            /* i/o: synthesis filter memory state,     Q0  */
    Word16 wsp[]               /* o  : weighted speech                    Q0  */
);

int subframePreProc(
    Word16 mode,            /* i  : coder mode                            */
    const Word16 gamma1[],     /* i  : spectral exp. factor 1                */
    const Word16 gamma1_12k2[],/* i  : spectral exp. factor 1 for EFR        */
    const Word16 gamma2[],     /* i  : spectral exp. factor 2                */
    Word16 *A,                 /* i  : A(z) unquantized for the 4 subframes  */
    Word16 *Aq,                /* i  : A(z)   quantized for the 4 subframes  */
    Word16 *speech,            /* i  : speech segment                        */
    Word16 *mem_err,           /* i  : pointer to error signal               */
    Word16 *mem_w0,            /* i  : memory of weighting filter            */
    Word16 *zero,              /* i  : pointer to zero vector                */
    Word16 ai_zero[],          /* o  : history of weighted synth. filter     */
    Word16 exc[],              /* o  : long term prediction residual         */
    Word16 h1[],               /* o  : impulse response                      */
    Word16 xn[],               /* o  : target vector for pitch search        */
    Word16 res2[],             /* o  : long term prediction residual         */
    Word16 error[]             /* o  : error of LPC synthesis filter         */
);

int subframePostProc(
    Word16 *speech,   /* i   : speech segment                        */
    Word16 mode,   /* i   : coder mode                            */
    Word16 i_subfr,   /* i   : Subframe nr                           */
    Word16 gain_pit,  /* i   : Pitch gain                       Q14  */
    Word16 gain_code, /* i   : Decoded innovation gain               */
    Word16 *Aq,       /* i   : A(z) quantized for the 4 subframes    */
    Word16 synth[],   /* i   : Local snthesis                        */
    Word16 xn[],      /* i   : Target vector for pitch search        */
    Word16 code[],    /* i   : Fixed codebook exitation              */
    Word16 y1[],      /* i   : Filtered adaptive exitation           */
    Word16 y2[],      /* i   : Filtered fixed codebook excitation    */
    Word16 *mem_syn,  /* i/o : memory of synthesis filter            */
    Word16 *mem_err,  /* o   : pointer to error signal               */
    Word16 *mem_w0,   /* o   : memory of weighting filter            */
    Word16 *exc,      /* o   : long term prediction residual         */
    Word16 *sharp     /* o   : pitch sharpening value                */
);

int cbsearch(Word16 x[],     /* i : target vector, Q0                      */
             Word16 h[],     /* i : impulse response of weighted synthesis */
                             /*     filter h[-L_subfr..-1] must be set to  */
                             /*    zero. Q12                               */
             Word16 T0,      /* i : Pitch lag                              */
             Word16 pitch_sharp, /* i : Last quantized pitch gain, Q14     */
             Word16 gain_pit,/* i : Pitch gain, Q14                        */ 
             Word16 res2[],  /* i : Long term prediction residual, Q0      */
             Word16 code[],  /* o : Innovative codebook, Q13               */
             Word16 y[],     /* o : filtered fixed codebook excitation, Q12 */
             Word16 **anap,  /* o : Signs of the pulses                    */
             Word16 mode, /* i : coder mode                             */
             Word16 subNr);   /* i : subframe number                        */
void Convolve (
    Word16 x[],        /* (i)  : input vector                               */
    Word16 h[],        /* (i)  : impulse response                           */
    Word16 y[]        /* (o)  : output vector                              */
);
 



void ton_stab_reset (tonStabState *st);

Word16 check_lsp(tonStabState *st, /* i/o : State struct            */
                 Word16 *lsp       /* i   : unquantized LSP's       */
);
Word16 check_gp_clipping(tonStabState *st, /* i/o : State struct            */
                         Word16 g_pitch    /* i   : pitch gain              */
);
void update_gp_clipping(tonStabState *st, /* i/o : State struct            */
                        Word16 g_pitch    /* i   : pitch gain              */
);


void cor_h_x (
    Word16 h[],     /* (i) : impulse response of weighted synthesis filter */
    Word16 x[],     /* (i) : target                                        */
    Word16 dn[],    /* (o) : correlation between target and h[]            */
    Word16 sf       /* (i) : scaling factor: 2 for 12.2, 1 for 7.4         */
);

void cor_h_x2 (
    Word16 h[],     /* (i) : impulse response of weighted synthesis filter */
    Word16 x[],     /* (i) : target                                        */
    Word16 dn[],    /* (o) : correlation between target and h[]            */
    Word16 sf,      /* (i) : scaling factor: 2 for 12.2, 1 for 7.4         */
    Word16 nb_track,/* (i) : the number of ACB tracks                      */
    Word16 step     /* (i) : step size from one pulse position to the next
                             in one track                                  */
);

void cor_h (
    Word16 h[],     /* (i) : impulse response of weighted synthesis filter */
    Word16 sign[],      /* (i) : sign of d[n]                              */
    Word16 rr[][L_CODE] /* (o) : matrix of autocorrelation                 */
);


void set_sign(Word16 dn[],   /* i/o : correlation between target and h[]    */
              Word16 sign[], /* o   : sign of dn[]                          */
              Word16 dn2[],  /* o   : maximum of correlation in each track. */
              Word16 n       /* i   : # of maximum correlations in dn2[]    */
);

void set_sign12k2 (
    Word16 dn[],      /* i/o : correlation between target and h[]         */
    Word16 cn[],      /* i   : residual after long term prediction        */
    Word16 sign[],    /* o   : sign of d[n]                               */
    Word16 pos_max[], /* o   : position of maximum correlation            */
    Word16 nb_track,  /* i   : number of tracks tracks                    */        
    Word16 ipos[],    /* o   : starting position for each pulse           */
    Word16 step       /* i   : the step size in the tracks                */        
);

void search_10and8i40 (
    Word16 nbPulse,      /* i : nbpulses to find                       */
    Word16 step,         /* i :  stepsize                              */
    Word16 nbTracks,     /* i :  nbTracks                              */
    Word16 dn[],         /* i : correlation between target and h[]     */
    Word16 rr[][L_CODE], /* i : matrix of autocorrelation              */
    Word16 ipos[],       /* i : starting position for each pulse       */
    Word16 pos_max[],    /* i : position of maximum of dn[]            */
    Word16 codvec[]      /* o : algebraic codebook vector              */
);
Word16 code_2i40_9bits(
    Word16 subNr,       /* i : subframe number                               */
    Word16 x[],         /* i : target vector                                 */
    Word16 h[],         /* i : impulse response of weighted synthesis filter */
                        /*     h[-L_subfr..-1] must be set to zero.          */
    Word16 T0,          /* i : Pitch lag                                     */
    Word16 pitch_sharp, /* i : Last quantized pitch gain                     */
    Word16 code[],      /* o : Innovative codebook                           */
    Word16 y[],         /* o : filtered fixed codebook excitation            */
    Word16 * sign       /* o : Signs of 2 pulses                             */
);



Word16 code_2i40_11bits(
    Word16 x[], /* i : target vector                                 */
    Word16 h[], /* i : impulse response of weighted synthesis filter */
                /*     h[-L_subfr..-1] must be set to zero.          */
    Word16 T0,  /* i : Pitch lag                                     */
    Word16 pitch_sharp, /* i : Last quantized pitch gain             */
    Word16 code[],      /* o : Innovative codebook                   */
    Word16 y[],         /* o : filtered fixed codebook excitation    */
    Word16 * sign       /* o : Signs of 2 pulses                     */
);

void code_10i40_35bits (
    Word16 x[],        /* (i)   : target vector                             */
    Word16 cn[],       /* (i)   : residual after long term prediction       */
    Word16 h[],        /* (i)   : impulse response of weighted synthesis
                                  filter                                    */
    Word16 cod[],      /* (o)   : algebraic (fixed) codebook excitation     */
    Word16 y[],        /* (o)   : filtered fixed codebook excitation        */
    Word16 indx[]      /* (o)   : index of 10 pulses (sign + position)      */
);

Word16 code_3i40_14bits(
    Word16 x[], /* (i)   : target vector                                 */
    Word16 h[], /* (i)   : impulse response of weighted synthesis filter */
                /*         h[-L_subfr..-1] must be set to zero.          */
    Word16 T0,  /* (i)   : Pitch lag                                     */
    Word16 pitch_sharp, /* (i)   : Last quantized pitch gain             */
    Word16 code[],      /* (o)   : Innovative codebook                   */
    Word16 y[],         /* (o)   : filtered fixed codebook excitation    */
    Word16 * sign       /* (o)   : Signs of 3 pulses                     */
);






Word16 q_gain_pitch (   /* Return index of quantization                      */
    Word16 mode,     /* i  : AMR mode                                     */
    Word16 gp_limit,    /* i  : pitch gain limit                             */
    Word16 *gain,       /* i/o: Pitch gain (unquant/quant),              Q14 */
    Word16 gain_cand[], /* o  : pitch gain candidates (3),   MR795 only, Q14 */ 
    Word16 gain_cind[]  /* o  : pitch gain cand. indices (3),MR795 only, Q0  */ 
);
 
Word16 G_pitch     (    /* o : Gain of pitch lag saturated to 1.2       */
    Word16 mode,     /* i : AMR mode                                 */
    Word16 xn[],        /* i : Pitch target.                            */
    Word16 y1[],        /* i : Filtered adaptive codebook.              */
    Word16 g_coeff[],   /* i : Correlations need for gain quantization.
                               (7.4 only). Pass NULL if not needed      */
    Word16 L_subfr      /* i : Length of subframe.                      */
);




void calc_unfilt_energies(
    Word16 res[],     /* i  : LP residual,                               Q0  */
    Word16 exc[],     /* i  : LTP excitation (unfiltered),               Q0  */
    Word16 code[],    /* i  : CB innovation (unfiltered),                Q13 */
    Word16 gain_pit,  /* i  : pitch gain,                                Q14 */
    Word16 L_subfr,   /* i  : Subframe length                                */

    Word16 frac_en[], /* o  : energy coefficients (3), fraction part,    Q15 */
    Word16 exp_en[],  /* o  : energy coefficients (3), exponent part,    Q0  */
    Word16 *ltpg      /* o  : LTP coding gain (log2()),                  Q13 */
);


void calc_filt_energies(
    Word16 mode,     /* i  : coder mode                                   */
    Word16 xn[],        /* i  : LTP target vector,                       Q0  */
    Word16 xn2[],       /* i  : CB target vector,                        Q0  */
    Word16 y1[],        /* i  : Adaptive codebook,                       Q0  */
    Word16 Y2[],        /* i  : Filtered innovative vector,              Q12 */
    Word16 g_coeff[],   /* i  : Correlations <xn y1> <y1 y1>                 */
                        /*      computed in G_pitch()                        */

    Word16 frac_coeff[],/* o  : energy coefficients (5), fraction part,  Q15 */
    Word16 exp_coeff[], /* o  : energy coefficients (5), exponent part,  Q0  */
    Word16 *cod_gain_frac,/* o: optimum codebook gain (fraction part),   Q15 */
    Word16 *cod_gain_exp  /* o: optimum codebook gain (exponent part),   Q0  */
);


void calc_target_energy(
    Word16 xn[],     /* i: LTP target vector,                       Q0  */
    Word16 *en_exp,  /* o: optimum codebook gain (exponent part),   Q0  */
    Word16 *en_frac  /* o: optimum codebook gain (fraction part),   Q15 */
);

void MR475_update_unq_pred(
    gc_predState *pred_st, /* i/o: gain predictor state struct            */
    Word16 exp_gcode0,     /* i  : predicted CB gain (exponent),      Q0  */
    Word16 frac_gcode0,    /* i  : predicted CB gain (fraction),      Q15 */
    Word16 cod_gain_exp,   /* i  : optimum codebook gain (exponent),  Q0  */
    Word16 cod_gain_frac   /* i  : optimum codebook gain (fraction),  Q15 */
);


Word16 MR475_gain_quant(              /* o  : index of quantization.                 */
    gc_predState *pred_st,     /* i/o: gain predictor state struct            */
      
                               /* data from subframe 0 (or 2) */
    Word16 sf0_exp_gcode0,     /* i  : predicted CB gain (exponent),      Q0  */
    Word16 sf0_frac_gcode0,    /* i  : predicted CB gain (fraction),      Q15 */
    Word16 sf0_exp_coeff[],    /* i  : energy coeff. (5), exponent part,  Q0  */
    Word16 sf0_frac_coeff[],   /* i  : energy coeff. (5), fraction part,  Q15 */
                               /*      (frac_coeff and exp_coeff computed in  */
                               /*       calc_filt_energies())                 */
    Word16 sf0_exp_target_en,  /* i  : exponent of target energy,         Q0  */
    Word16 sf0_frac_target_en, /* i  : fraction of target energy,         Q15 */
      
                               /* data from subframe 1 (or 3) */
    Word16 sf1_code_nosharp[], /* i  : innovative codebook vector (L_SUBFR)   */
                               /*      (whithout pitch sharpening)            */
    Word16 sf1_exp_gcode0,     /* i  : predicted CB gain (exponent),      Q0  */
    Word16 sf1_frac_gcode0,    /* i  : predicted CB gain (fraction),      Q15 */
    Word16 sf1_exp_coeff[],    /* i  : energy coeff. (5), exponent part,  Q0  */
    Word16 sf1_frac_coeff[],   /* i  : energy coeff. (5), fraction part,  Q15 */
                               /*      (frac_coeff and exp_coeff computed in  */
                               /*       calc_filt_energies())                 */
    Word16 sf1_exp_target_en,  /* i  : exponent of target energy,         Q0  */
    Word16 sf1_frac_target_en, /* i  : fraction of target energy,         Q15 */

    Word16 gp_limit,           /* i  : pitch gain limit                       */

    Word16 *sf0_gain_pit,      /* o  : Pitch gain,                        Q14 */
    Word16 *sf0_gain_cod,      /* o  : Code gain,                         Q1  */
      
    Word16 *sf1_gain_pit,      /* o  : Pitch gain,                        Q14 */
    Word16 *sf1_gain_cod       /* o  : Code gain,                         Q1  */
);

void MR795_gain_quant(
    GainAdaptState *adapt_st, /* i/o: gain adapter state structure       */
    Word16 res[],             /* i  : LP residual,                  Q0   */
    Word16 exc[],             /* i  : LTP excitation (unfiltered),  Q0   */
    Word16 code[],            /* i  : CB innovation (unfiltered),   Q13  */
    Word16 frac_coeff[],      /* i  : coefficients (5),             Q15  */
    Word16 exp_coeff[],       /* i  : energy coefficients (5),      Q0   */
                              /*      coefficients from calc_filt_ener() */
    Word16 exp_code_en,       /* i  : innovation energy (exponent), Q0   */
    Word16 frac_code_en,      /* i  : innovation energy (fraction), Q15  */
    Word16 exp_gcode0,        /* i  : predicted CB gain (exponent), Q0   */
    Word16 frac_gcode0,       /* i  : predicted CB gain (fraction), Q15  */
    Word16 L_subfr,           /* i  : Subframe length                    */
    Word16 cod_gain_frac,     /* i  : opt. codebook gain (fraction),Q15  */
    Word16 cod_gain_exp,      /* i  : opt. codebook gain (exponent), Q0  */
    Word16 gp_limit,          /* i  : pitch gain limit                   */
    Word16 *gain_pit,         /* i/o: Pitch gain (unquant/quant),   Q14  */
    Word16 *gain_cod,         /* o  : Code gain,                    Q1   */
    Word16 *qua_ener_MR122,   /* o  : quantized energy error,       Q10  */
                              /*      (for MR122 MA predictor update)    */
    Word16 *qua_ener,         /* o  : quantized energy error,       Q10  */
                              /*      (for other MA predictor update)    */
    Word16 **anap             /* o  : Index of quantization              */
                              /*      (first gain pitch, then code pitch)*/
);


Word16 code_4i40_17bits(
    Word16 x[], /* (i)   : target vector                                 */
    Word16 h[], /* (i)   : impulse response of weighted synthesis filter */
                /*         h[-L_subfr..-1] must be set to zero.          */
    Word16 T0,  /* (i)   : Pitch lag                                     */
    Word16 pitch_sharp, /* (i)   : Last quantized pitch gain             */
    Word16 code[],      /* (o)   : Innovative codebook                   */
    Word16 y[],         /* (o)   : filtered fixed codebook excitation    */
    Word16 * sign       /* (o)   : Signs of 4 pulses                     */
);


void code_8i40_31bits (
    Word16 x[],        /* i : target vector                                  */
    Word16 cn[],       /* i : residual after long term prediction            */
    Word16 h[],        /* i : impulse response of weighted synthesis
                              filter                                         */
    Word16 cod[],      /* o : algebraic (fixed) codebook excitation          */
    Word16 y[],        /* o : filtered fixed codebook excitation             */
    Word16 indx[]      /* o : 7 Word16, index of 8 pulses (signs+positions)  */
    );
Word16 G_code (        /* out      : Gain of innovation code.               */
    Word16 xn[],       /* in       : target vector                          */
    Word16 y2[]        /* in       : filtered inovation vector              */
);
Word16 q_gain_code (        /* o  : quantization index,            Q0  */
    Word16 mode,         /* i  : AMR mode                           */
    Word16 exp_gcode0,      /* i  : predicted CB gain (exponent),  Q0  */
    Word16 frac_gcode0,     /* i  : predicted CB gain (fraction),  Q15 */
    Word16 *gain,           /* i/o: quantized fixed codebook gain, Q1  */
    Word16 *qua_ener_MR122, /* o  : quantized energy error,        Q10 */
                            /*      (for MR122 MA predictor update)    */
    Word16 *qua_ener        /* o  : quantized energy error,        Q10 */
                            /*      (for other MA predictor update)    */
);

Word32 Div_32 (Word32 L_num, Word16 denom_hi, Word16 denom_lo);
Word16 Autocorr (
    Word16 x[],        /* (i)    : Input signal (L_WINDOW)             */
    Word16 m,          /* (i)    : LPC order                           */
    Word16 r_h[],      /* (o)    : Autocorrelations  (msb)  (MP1)      */
    Word16 r_l[],      /* (o)    : Autocorrelations  (lsb)  (MP1)      */
    const Word16 wind[]/* (i)    : window for LPC analysis. (L_WINDOW) */
);



void Int_lpc_1and3_2 (
    Word16 lsp_old[],  /* i : LSP vector at the 4th subfr. of past frame (M) */
    Word16 lsp_mid[],  /* i : LSP vector at the 2nd subframe of
                             present frame (M)                                  */
    Word16 lsp_new[],  /* i : LSP vector at the 4th subframe of
                             present frame (M)                                  */
    Word16 Az[]        /* o :interpolated LP parameters
                             in subframes 1 and 3 (AZ_SIZE)                     */
);




void Int_lpc_1to3_2 (
    Word16 lsp_old[],  /* i : LSP vector at the 4th SF of past frame (M) */
    Word16 lsp_new[],  /* i : LSP vector at the 4th SF present frame (M) */
    Word16 Az[]        /* o :interpolated LP parameters in SFs 1, 2, 3 
                             (AZ_SIZE)                                   */
);

void Az_lsp (
    Word16 a[],        /* (i)  : predictor coefficients (MP1)              */
    Word16 lsp[],      /* (o)  : line spectral pairs (M)                   */
    Word16 old_lsp[]   /* (i)  : old lsp[] (in case not found 10 roots) (M)*/
);

Word16 Pitch_ol (      /* o   : open loop pitch lag                         */
    vadState *vadSt,   /* i/o : VAD state struct                            */
    Word16 mode,    /* i   : coder mode                                  */
    Word16 signal[],   /* i   : signal used to compute the open loop pitch  */
                       /*    signal[-pit_max] to signal[-1] should be known */
    Word16 pit_min,    /* i   : minimum pitch lag                           */
    Word16 pit_max,    /* i   : maximum pitch lag                           */
    Word16 L_frame,    /* i   : length of frame to compute pitch            */
    Word16 idx,        /* i   : frame index                                 */
    Flag dtx           /* i   : dtx flag; use dtx=1, do not use dtx=0       */
    );
 
void comp_corr (Word16 scal_sig[],  /* i   : scaled signal.                     */
                Word16 L_frame,     /* i   : length of frame to compute pitch   */
                Word16 lag_max,     /* i   : maximum lag                        */
                Word16 lag_min,     /* i   : minimum lag                        */
                Word32 corr[]       /* o   : correlation of selected lag        */
                );


Word16 Interpol_3or6 (  /* (o)  : interpolated value                        */
    Word16 *x,          /* (i)  : input vector                              */
    Word16 frac,        /* (i)  : fraction  (-2..2 for 3*, -3..3 for 6*)    */
    Word16 flag3        /* (i)  : if set, upsampling rate = 3 (6 otherwise) */
);

Word16
Enc_lag3(                /* o  : Return index of encoding     */
    Word16 T0,           /* i  : Pitch delay                          */
    Word16 T0_frac,      /* i  : Fractional pitch delay               */
    Word16 T0_prev,      /* i  : Integer pitch delay of last subframe */
    Word16 T0_min,       /* i  : minimum of search range              */
    Word16 T0_max,       /* i  : maximum of search range              */
    Word16 delta_flag,   /* i  : Flag for 1st (or 3rd) subframe       */
    Word16 flag4         /* i  : Flag for encoding with 4 bits        */
);

Word16 Enc_lag6 (        /* o  : Return index of encoding             */
    Word16 T0,           /* i  : Pitch delay                          */
    Word16 T0_frac,      /* i  : Fractional pitch delay               */
    Word16 T0_min,       /* i  : minimum of search range              */
    Word16 delta_flag    /* i  : Flag for 1st (or 3rd) subframe       */
);




void Lsf_wt (
    Word16 *lsf,         /* input : LSF vector                  */
    Word16 *wf);         /* output: square of weighting factors */
 


void sid_sync_init (sid_syncState *s);
void sid_sync_reset (sid_syncState *st);
int sid_sync_set_handover_debt (sid_syncState *st, /* i/o: sid_sync state  */
                                Word16 debtFrames);
void sid_sync(sid_syncState *st , /* i/o: sid_sync state      */
              Word16 mode,
              Word16 *tx_frame_type); 

int Pre_Process_reset (Pre_ProcessState *st);


 
int Pre_Process (
    Pre_ProcessState *st,
    Word16 signal[],   /* Input/output signal                               */
    Word16 lg          /* Lenght of signal                                  */
);

void Prm2bits (
    Word16 mode,    /* i : AMR mode */
    Word16 prm[],      /* input : analysis parameters                       */
    Word16 bits[]      /* output: serial bits                               */
);



void Speech_Encode_Frame_reset (Speech_Encode_FrameState *st);

int Speech_Encode_Frame (
    Speech_Encode_FrameState *st, /* i/o : encoder states         */
    Word16 *new_speech,           /* i   : input speech           */
    Word16 *serial,Word16 amr_mode               /* o   : serial bit stream      */
);

Word16 PackBits(
    Word16 used_mode,       /* i : actual AMR mode             */
    Word16 mode,            /* i : requested AMR (speech) mode */
    Word16 fr_type,  /* i : frame type                  */
    Word16 bits[],             /* i : serial bits                 */
    UWord8 packed_bits[]       /* o : sorted&packed bits          */
);

void cod_amr_init(cod_amrState *s); //, Flag dtx);
void cod_amr_reset (cod_amrState *st);
int cod_amr_first(cod_amrState *st,     /* i/o : State struct            */
                  Word16 new_speech[]   /* i   : speech input (L_FRAME)  */
);

Word16 encoder_homing_frame_test (Word16 input_frame[]);
int dtx_enc_reset (dtx_encState *st);

 
int cod_amr(cod_amrState *st,         /* i/o : State struct                 */
            Word16 new_speech[],      /* i   : speech input (L_FRAME)       */
            Word16 ana[],             /* o   : Analysis parameters          */
            Word16 synth[],Word16 amr_mode,Word16 *usedMode            /* o   : Local synthesis              */
);

#if OPT_DTX

void vad_complex_detection_update (vadState1 *st,      /* i/o : State struct     */
                                   Word16 best_corr_hp /* i   : best Corr Q15    */
                                   );

void vad_tone_detection (vadState1 *st, /* i/o : State struct            */
                         Word32 t0,     /* i   : autocorrelation maxima  */
                         Word32 t1      /* i   : energy                  */
                         );

void vad_tone_detection_update (
                vadState1 *st,             /* i/o : State struct              */
                Word16 one_lag_per_frame   /* i   : 1 if one open-loop lag is
                                              calculated per each frame,
                                              otherwise 0                     */
                );

void vad_pitch_detection (vadState1 *st,  /* i/o : State struct                  */
                          Word16 lags[]   /* i   : speech encoder open loop lags */
                          );

Word16 vad1 (vadState1 *st,Word16 in_buf[]);
int dtx_enc(dtx_encState *st,        /* i/o : State struct                    */
            Word16 computeSidFlag,   /* i   : compute SID                     */
       Q_plsfState *qSt,        /* i/o : Qunatizer state struct          */
            gc_predState* predState, /* i/o : State struct                    */
       Word16 **anap            /* o   : analysis parameters             */
       );
#endif

Word16 tx_dtx_handler(dtx_encState *st,       /* i/o : State struct          */
                      Word16 vadFlag,         /* i   : vad control variable  */
                      Word16 *usedMode     /* o   : mode changed or not   */
                      );


int dtx_buffer(dtx_encState *st,   /* i/o : State struct                    */
          Word16 lsp_new[],   /* i   : LSP vector                      */
          Word16 speech[]     /* i   : speech samples                  */
          );
int vad1_reset (vadState1 *st);

#if OPT_DTX
Word16 hp_max (   
    Word32 corr[],      /* i   : correlation vector.                      */
    Word16 scal_sig[],  /* i   : scaled signal.                           */
    Word16 L_frame,     /* i   : length of frame to compute pitch         */
    Word16 lag_max,     /* i   : maximum lag                              */
    Word16 lag_min,     /* i   : minimum lag                              */
    Word16 *cor_hp_max  /* o   : max high-pass filtered norm. correlation */
    );
#endif


Word16   vad2 (Word16 *farray_ptr, vadState2 *st);
int vad2_reset (vadState2 *st);
void  r_fft (Word16 *farray_ptr);
void  LTP_flag_update (vadState2 *st, Word16 mode);

Word16 add (Word16 var1, Word16 var2);    /* Short add, 1   */
void Int_lpc_1to3_enc (
    Word16 lsp_old[], /* i : LSP vector at the 4th SF of past frame (M)      */
    Word16 lsp_new[], /* i : LSP vector at the 4th SF of present frame (M)   */
    Word16 Az[]       /* o : interpolated LP parameters in all SFs (AZ_SIZE) */
);
void Int_lpc_1and3_enc (
    Word16 lsp_old[],  /* i : LSP vector at the 4th subfr. of past frame (M) */
    Word16 lsp_mid[],  /* i : LSP vector at the 2nd subfr. of
                              present frame (M)                              */
    Word16 lsp_new[],  /* i : LSP vector at the 4th subfr. of
                              present frame (M)                              */
    Word16 Az[]        /* o : interpolated LP parameters in all subfr.
                              (AZ_SIZE)                                      */
);
void Weight_Ai (
    Word16 a[],        /* (i)  : a[m+1]  LPC coefficients   (m=10)          */
    const Word16 fac[],/* (i)  : Spectral expansion factors.                */
    Word16 a_exp[]     /* (o)  : Spectral expanded LPC coefficients         */
);
void Pred_lt_3or6 (
    Word16 exc[],     /* in/out: excitation buffer                         */
    Word16 T0,        /* input : integer pitch lag                         */
    Word16 frac,      /* input : fraction of lag                           */
    Word16 L_subfr,   /* input : subframe size                             */
    Word16 flag3      /* input : if set, upsampling rate = 3 (6 otherwise) */
);

void Lsp_lsf_enc (
    Word16 lsp[],      /* (i)    : lsp[m] (range: -1<=val<1)                */
    Word16 lsf[],      /* (o)    : lsf[m] normalized (range: 0.0<=val<=0.5) */
    Word16 m           /* (i)    : LPC order                                */
);
void Lsp_Az_enc (
    Word16 lsp[],      /* (i)    : line spectral frequencies                */
    Word16 a[]         /* (o)    : predictor coefficients (order = 10)      */
);
void gc_pred_update_enc(
    gc_predState *st,      /* i/o: State struct                     */
    Word16 qua_ener_MR122, /* i  : quantized energy for update, Q10 */
                           /*      (log2(qua_err))                  */
    Word16 qua_ener        /* i  : quantized energy for update, Q10 */
                           /*      (20*log10(qua_err))              */
);

Word16 gmed_n_enc (   /* o : index of the median value (0...N-1)      */
    Word16 ind[], /* i : Past gain values                         */
    Word16 n      /* i : The number of gains; this routine        */
                  /*     is only valid for a odd number of gains  */ 
);
void gc_pred_enc(
    gc_predState *st,   /* i/o: State struct                           */
    Word16 mode,     /* i  : AMR mode                               */
    Word16 *code,       /* i  : innovative codebook vector (L_SUBFR)   */
                        /*      MR122: Q12, other modes: Q13           */
    Word16 *exp_gcode0, /* o  : exponent of predicted gain factor, Q0  */
    Word16 *frac_gcode0,/* o  : fraction of predicted gain factor  Q15 */
    Word16 *exp_en,     /* o  : exponent of innovation energy,     Q0  */
                        /*      (only calculated for MR795)            */
    Word16 *frac_en     /* o  : fraction of innovation energy,     Q15 */
                        /*      (only calculated for MR795)            */
);

void Reorder_lsf_enc (
    Word16 *lsf,       /* (i/o)  : vector of LSFs   (range: 0<=val<=0.5)    */
    Word16 min_dist   /* (i)    : minimum required distance                */
);

void Lsf_lsp_enc (
    Word16 lsf[],      /* (i)    : lsf[m] normalized (range: 0.0<=val<=0.5) */
    Word16 lsp[],      /* (o)    : lsp[m] (range: -1<=val<1)                */
    Word16 m           /* (i)    : LPC order                                */
);

void Copy (
    const Word16 x[],  /* i : input vector (L)    */
    Word16 y[],        /* o : output vector (L)   */
    Word16 L           /* i : vector length       */
);
void Residu_enc(
    Word16 a[],        /* (i)  : prediction coefficients                    */
    Word16 x[],        /* (i)  : speech signal                              */
    Word16 y[],        /* (o)  : residual signal                            */
    Word16 lg          /* (i)  : size of filtering                          */
);
void Set_zero (
    Word16 x[],        /* (o)  : vector to clear                            */
    Word16 L           /* (i)  : length of vector                           */
);

Word32  Dotproduct40Self( Word16 *x );
Word32  Dotproduct40_conv( Word16 *x, Word16 *y, int *s2);

int Norm_Corr(Word16 exc[], Word16 xn[], Word16 h[],
              Word16 t_min, Word16 t_max, Word16 corr_norm[]);
#endif


