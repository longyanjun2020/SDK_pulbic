#ifndef __AMRNB_COMMON_STRUCT_INCLUDE_FILE__
#define __AMRNB_COMMON_STRUCT_INCLUDE_FILE__








typedef struct {
   Word16 past_qua_en[4];         /* normal MA predictor memory,         Q10 */
                                  /* (contains 20*log10(qua_err))            */
   Word16 past_qua_en_MR122[4];   /* MA predictor memory for MR122 mode, Q10 */
                                  /* (contains log2(qua_err))                */
} gc_predState;


extern const Word16 unpacked_size_e[];
extern const Word16 T_dico1_lsf_3_e[];
extern const Word16 T_dico2_lsf_3_e[];
extern const Word16 T_mr515_3_lsf_e[];
extern const Word16 T_table_gain_lowrates_e[VQ_SIZE_LOWRATES*4];
extern const Word16 T_log2_table_e[33];
extern const Word16 T_pow2_table_e[33];
extern const Word16 T_lsp_init_data_e[M];





extern const Word16 T_startPos_e[2*4*2]; 


extern const Word16 T_table_gain_MR475_e[MR475_VQ_SIZE*4];
extern const Word16 T_window_200_40_e[L_WINDOW];
extern const Word16 *sort_ptr_e[];
extern const Word16 *bitno_e[];
extern const Word16 prmno_e[];
extern const Word16 qua_gain_code_e[];
extern const Word16 qua_gain_pitch_e[];
extern const Word16 mean_lsf_e[];
extern const Word16 dico1_lsf_e[];
extern const Word16 dico2_lsf_e[];
extern const Word16 dico3_lsf_e[];
extern const Word16 dico4_lsf_e[];
extern const Word16 dico5_lsf_e[];
extern const Word16 q_plsf_3_mean_lsf_e[];
extern const Word16 pred_fac_e[];
extern const Word16 dico3_lsf_3_e[];
extern const Word16 mr795_1_lsf_e[];
extern const Word16 past_rq_init_e[];
extern const Word16 table_gain_highrates_e[]; 
extern const Word16 T_inv_sqrt_table_e[49];
extern const Word16 T_pred_e[NPRED];
extern const Word16 T_lsp_lsf_table_e[65];
extern const Word16 T_lsp_lsf_slope_e[64]; 
extern const Word16 T_pred_lt_inter_6_e[pred_lt_FIR_SIZE]; 
extern const Word16 T_sqrt_l_table_e[49];



#endif

