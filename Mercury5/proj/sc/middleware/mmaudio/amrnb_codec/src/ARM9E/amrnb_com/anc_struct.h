#ifndef __AMRNB_COMMON_STRUCT_INCLUDE_FILE__
#define __AMRNB_COMMON_STRUCT_INCLUDE_FILE__








typedef struct {
   Word16 past_qua_en[4];         /* normal MA predictor memory,         Q10 */
                                  /* (contains 20*log10(qua_err))            */
   Word16 past_qua_en_MR122[4];   /* MA predictor memory for MR122 mode, Q10 */
                                  /* (contains log2(qua_err))                */
} gc_predState;


extern const Word16 unpacked_size[];
extern const Word16 T_dico1_lsf_3[];
extern const Word16 T_dico2_lsf_3[];
extern const Word16 T_mr515_3_lsf[];
extern const Word16 T_table_gain_lowrates[VQ_SIZE_LOWRATES*4];
extern const Word16 T_log2_table[33];
extern const Word16 T_pow2_table[33];
extern const Word16 T_lsp_init_data[M];





extern const Word16 T_startPos[2*4*2]; 


extern const Word16 T_table_gain_MR475[MR475_VQ_SIZE*4];
extern const Word16 T_window_200_40[L_WINDOW];
extern const Word16 *sort_ptr[];
extern const Word16 *bitno[];
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



#endif

