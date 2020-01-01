#ifndef __AMRNB_DECODER_FUNCTION_INCLUDE_FILE__
#define __AMRNB_DECODER_FUNCTION_INCLUDE_FILE__


void agc_reset (agcState *st);


void Lsp_Az( Word32 lsp[], Word32 a[] );
void D_plsf_reset (D_plsfState *st);
void D_plsf_5( D_plsfState *st, Word16 bfi, Word16 *indice, Word32 *lsp1_q, Word32 *lsp2_q );
void D_plsf_3( D_plsfState *st, Word16 mode, Word16 bfi, Word16 *indice, Word32 *lsp1_q );
      
void Init_D_plsf_3(D_plsfState *st, Word16 index );


void ec_gain_code_reset (ec_gain_codeState *state);
void Lsp_lsf( Word32 lsp[], Word32 lsf[] );


void ec_gain_code( ec_gain_codeState *st, gc_predState *pred_state,
      Word16 state, Word32 *gain_code );

void ec_gain_code_update( ec_gain_codeState *st, Word16 bfi,
      Word16 prev_bf, Word32 *gain_code );


void ec_gain_pitch_reset(ec_gain_pitchState *state);



void ec_gain_pitch( ec_gain_pitchState *st, Word16 state, Word32 *gain_pitch );

void ec_gain_pitch_update( ec_gain_pitchState *st, Word32 bfi,
      Word32 prev_bf, Word32 *gain_pitch );


void Cb_gain_average_reset (Cb_gain_averageState *st);


Word32 Cb_gain_average( Cb_gain_averageState *st, Word16 mode, Word32
      gain_code, Word32 lsp[], Word32 lspAver[], Word16 bfi, Word16 prev_bf,
      Word16 pdfi, Word16 prev_pdf, Word32 inBackgroundNoise, Word32
      voicedHangover );


void lsp_avg_reset (lsp_avgState *st);
void lsp_avg( lsp_avgState *st, Word32 *lsp );

void Bgn_scd_reset (Bgn_scdState *st);
Word16 Bgn_scd( Bgn_scdState *st, Word32 ltpGainHist[], Word32 speech[],
      Word32 *voicedHangover );
 
void ph_disp_reset (ph_dispState *state);

void ph_disp( ph_dispState *state, Word16 mode, Word32 x[],
                    Word32 cbGain, Word32 ltpGain, Word32 inno[],
                    Word32 pitch_fac, Word32 tmp_shift);

void Dec_lag3( Word32 index, Word32 t0_min, Word32 t0_max, Word32 i_subfr
      , Word32 T0_prev, Word32 *T0, Word32 *T0_frac, Word32 flag4 );

void Dec_lag6( Word32 index, Word32 pit_min, Word32 pit_max, Word32
      i_subfr, Word32 *T0, Word32 *T0_frac );

Word32 d_gain_pitch(Word16 mode, Word32 index );
void d_gain_code( gc_predState *pred_state, Word16 mode, Word32 index,
                        Word32 code[], Word32 *gain_code );
 
Word32 pseudonoise( Word32 *shift_reg, Word32 no_bits );

void Build_CN_code( Word32 *seed, Word32 cod[] );

void Build_CN_param (
    Word16 *seed,              /* i/o : Old CN generator shift register state */
    const Word16 n_param,            /* i : number of params     */  
    const Word16 param_size_table[], /* i : size of params       */   
    Word16 parm[]              /* o   : CN Generated Params*/
);

void Post_Filter_init (Post_FilterState *s);
void Post_Filter_reset (Post_FilterState *st);
void Post_Filter( Post_FilterState *st, Word16 mode, Word32 *syn,
      Word32 *Az_4 );
void Decoder_amr_init (Decoder_amrState *s);

void Decoder_amr_reset (Decoder_amrState *st,Word16 mode);


void Decoder_amr( Decoder_amrState *st, Word16 mode, Word16 parm[],
      Word16 frame_type, Word32 synth[], Word32 A_t[] );


void copy16_to32 (Word32 *y, const Word16 *x,Word32 L);

void Speech_Decode_Frame_reset (Speech_Decode_FrameState *st);



Word16 UnpackBits (
    Word8  q,              /* i : Q-bit (i.e. BFI)        */
   Word16 ft,             /* i : frame type (i.e. mode)  */
    UWord8 packed_bits[],  /* i : sorted & packed bits    */
   Word16 *mode,       /* o : mode information        */
    Word16 bits[]          /* o : serial bits             */
);

Word32 Syn_filt( Word32 a[], Word32 x[], Word32 y[], Word32 lg, Word32 mem[]
      , Word32 update);
void Syn_filt_2( Word32 a[], Word32 x[], Word32 y[], Word32 lg, Word32 mem[]
      , Word32 update);

void Post_Process_reset (Post_ProcessState *st);

void Post_Process( Post_ProcessState *st, Word32 signal[] );
void decode_10i40_35bits( Word16 index[], Word32 cod[] );

void decode_4i40_17bits( Word32 sign, Word32 index, Word32 cod[] );

void Int_lsf( Word32 lsf_old[], Word32 lsf_new[], int i_subfr, Word32
      lsf_out[] );
Word16 Ex_ctrl( Word32 excitation[], Word32 excEnergy, Word32
      exEnergyHist[], Word32 voicedHangover, Word16 prevBFI, Word16 carefulFlag);

Word16 decoder_homing_frame_test (Word16 input_frame[], Word16 mode);
Word16 decoder_homing_frame_test_first (Word16 input_frame[], Word16 mode);
void A_Refl( Word32 a[], Word32 refl[] );

void decode_8i40_31bits( Word16 index[], Word32 cod[] );


void dtx_dec_reset (dtx_decState *st);


void dtx_dec( dtx_decState *st, Word32 *mem_syn, D_plsfState *lsfState,
      gc_predState *pred_state, Cb_gain_averageState *averState, 
      Word16 new_state, Word16 mode, Word16 parm[], Word32 synth[],
      Word32 A_t[] );

void dtx_dec_activity_update( dtx_decState *st, Word32 lsf[], Word32 frame[] );

Word16 rx_dtx_handler(dtx_decState *st,Word16 frame_type );

void Bits2prm (
    Word16 mode,
    Word16 bits[],   /* input : serial bits, (244 + bfi)               */
    Word16 prm[]     /* output: analysis parameters, (57+1 parameters) */
); 


void Dec_gain( gc_predState *pred_state, Word16 mode, Word32 index,
      Word32 code[], Word32 evenSubfr, Word32 *gain_pit, Word32 *gain_cod );

void gc_pred_average_limited( gc_predState *st, Word32 *ener_avg_MR122,
      Word32 *ener_avg );

void Lsf_lsp( Word32 lsf[], Word32 lsp[] );
void Int_lpc_1to3( Word32 lsp_old[], Word32 lsp_new[], Word32 Az[] );
void Int_lpc_1and3( Word32 lsp_old[], Word32 lsp_mid[], Word32 lsp_new[],
      Word32 Az[] );
void Pred_lt_3or6_40( Word32 exc[], Word32 T0, Word32 frac, Word32 flag3 );
void decode_2i40_9bits( Word32 subNr, Word32 sign, Word32 index, Word32 cod[] );
void decode_2i40_11bits( Word32 sign, Word32 index, Word32 cod[] );
void decode_3i40_14bits( Word32 sign, Word32 index, Word32 cod[] );
void agc2( Word32 *sig_in, Word32 *sig_out );
void Reorder_lsf( Word32 *lsf, Word32 min_dist );
Word32 gmed_n( Word32 ind[], Word32 n );
void gc_pred( gc_predState *st, Word16 mode, Word32 *code, Word32 *
      exp_gcode0, Word32 *frac_gcode0, Word32 *exp_en, Word32 *frac_en );
void gc_pred_update( gc_predState *st, Word32 qua_ener_MR122,
      Word32 qua_ener );
Word32 energy_new( Word32 in[] );



#endif


