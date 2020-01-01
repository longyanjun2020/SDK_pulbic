#ifndef __AMRNB_COMMON_STRUCT_INCLUDE_FILE__
#define __AMRNB_COMMON_STRUCT_INCLUDE_FILE__



/* Struct for storing pseudo floating point exponent and mantissa */
struct _fp
{
    Word16 e;          /* exponent */
    Word16 m;          /* mantissa */
};

typedef struct _fp Pfloat;


typedef struct
{
   Word16 txdtx_ctrl;              /* Encoder DTX control word                */
   Word16 CN_excitation_gain;      /* Unquantized fixed codebook gain         */
   Word32 L_pn_seed_tx;            /* PN generator seed (encoder)             */
   Word16 txdtx_hangover;   /* Length of hangover period (VAD=0, SP=1) */
   Word16 txdtx_N_elapsed;  /* Measured time from previous SID frame   */
   Word16 old_CN_mem_tx[6]; /* The most recent CN parameters are stored*/
   Word16 buf_p_tx;         /* Circular buffer pointer for gain code history  update in tx                   */
   Word16 lsf_old_tx[DTX_HANGOVER][M]; /* Comfort noise LSF averaging buffer  */
   Word16 gain_code_old_tx[4 * DTX_HANGOVER]; /* Comfort noise gain averaging buffer                       */

#ifdef PURE_EFR_MODE 
   //for VAD
   Word16 rvad[9], scal_rvad;
   Pfloat thvad;
   Word32 L_sacf[27];
   Word32 L_sav0[36];
   Word16 pt_sacf, pt_sav0;
   Word32 L_lastdm;
   Word16 adaptcount;
   Word16 burstcount, hangcount;
   Word16 oldlagcount, veryoldlagcount, oldlag;

   Word16 ptch;
#endif   
   //----------------------
   Word16 lsf_p_CN[M];
   Word16 gcode0_CN;
}EFR_DTX_VAD_ENC_DATA;


typedef struct
{
   Word16 rxdtx_ctrl;              /* Decoder DTX control word*/
   Word32 L_pn_seed_rx;            /* PN generator seed (decoder)*/
   Word16 rx_dtx_state;            /* State of comfort noise insertion period */
   Word16 rxdtx_aver_period;/* Length of hangover period (VAD=0, SP=1) */
   Word16 rxdtx_N_elapsed;  /* Measured time from previous SID frame   */
   Word16 prev_SID_frames_lost; /* Counter for lost SID frames*/
   Word16 buf_p_rx;         /* Circular buffer pointer for gain code history update in rx*/
   Word16 lsf_old_rx[DTX_HANGOVER][M]; /* Comfort noise LSF averaging buffer  */   
   Word16 gain_code_old_rx[4 * DTX_HANGOVER]; /* Comfort noise gain averaging buffer*/   
   
   //------------------------------------------------------------
   Word16 dec_lsf_p_CN[M];
   Word16 lsf_old_CN[M], lsf_new_CN[M];
   Word16 dec_gcode0_CN, gain_code_old_CN, gain_code_new_CN, gain_code_muting_CN;   
}EFR_DTX_VAD_DEC_DATA;



typedef struct {
   Word16 past_qua_en[4];         /* normal MA predictor memory,         Q10 */
                                  /* (contains 20*log10(qua_err))            */
   Word16 past_qua_en_MR122[4];   /* MA predictor memory for MR122 mode, Q10 */
                                  /* (contains log2(qua_err))                */
} gc_predState;


extern const unsigned char unpacked_size[];
extern const Word16 T_dico1_lsf_3[];
extern const Word16 T_dico2_lsf_3[];
extern const Word16 T_mr515_3_lsf[];
extern const Word16 T_table_gain_lowrates[VQ_SIZE_LOWRATES*4];
extern const Word16 T_log2_table[33];
extern const Word16 T_pow2_table[33];
extern const Word16 T_lsp_init_data[M];





extern const Word8 T_startPos[2*4*2]; 


extern const Word16 T_table_gain_MR475[MR475_VQ_SIZE*4];
extern const Word16 T_window_200_40[L_WINDOW];
extern const unsigned char *const sort_ptr[];
extern const Word8 *const bitno[];
extern const Word16 prmno[];
extern const Word16 qua_gain_code[];
extern const Word16 qua_gain_pitch[];
extern const Word16 mean_lsf[];
extern const Word16 dico1_lsf[];
extern const Word16 dico2_lsf[];
extern const Word16 dico3_lsf[];
extern const Word16 dico4_lsf[];
extern const Word16 dico5_lsf[];
extern const Word16 q_plsf_3_mean_lsf[];
extern const Word16 pred_fac[];
extern const Word16 dico3_lsf_3[];
extern const Word16 mr795_1_lsf[];
extern const Word16 past_rq_init[];
extern const Word16 table_gain_highrates[]; 
extern const Word16 T_inv_sqrt_table[49];
extern const Word16 T_pred[NPRED];
extern const Word16 T_lsp_lsf_table[65];
extern const Word16 T_lsp_lsf_slope[64]; 
extern const Word16 T_pred_lt_inter_6[pred_lt_FIR_SIZE]; 
extern const Word16 T_sqrt_l_table[49];


extern const Word16 efrBitPosTableCRCProtected_AMR[POS_TABLE_SZ_CRC_PROTECTED];
extern const Word16 efrBitPosTableCRC_AMR[POS_TABLE_SZ_CRC];
extern const Word16 efrBitPosTableClassIbUnprotected_AMR[POS_TABLE_SZ_CLASS1B_UNPROTECTED];
extern const Word16 efrBitPosTableRepeatedBits_AMR[POS_TABLE_SZ_REPEATED_BITS];
extern const Word16 efrBitPosTableClassIIUnprotected_AMR[POS_TABLE_SZ_CLASS2_UNPROTECTED];
extern const Word8 paramNo_AMR[4];
extern const unsigned char crcMapTable_AMR[EFR_CRC_MAP_TABLE_LENGTH];
extern const Word8 SID_codeword_table[SID_CODE_TABLE_SZ];
extern const Word8 pred_MR122[NPRED];
#endif

