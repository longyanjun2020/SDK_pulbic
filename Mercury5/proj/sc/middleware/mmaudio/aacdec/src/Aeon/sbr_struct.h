#ifndef __HE_AAC_DECODER_SBR_STRUCTS_H__
#define __HE_AAC_DECODER_SBR_STRUCTS_H__



#define QMF_RE(A) RE(A)
#define QMF_IM(A) IM(A)

typedef short complex_ts[2];
typedef int complex_t[2];

#define RE(A) A[0]
#define IM(A) A[1]
#define qmf_t complex_t
/* MAX_NTSRHFG: maximum of number_time_slots * rate + HFGen. 16*2+8 */
#define MAX_NTSRHFG 40
#define MAX_NTSR    32 /* max number_time_slots * rate, ok for DRM and not DRM mode */

/* MAX_M: maximum value for M */
#define MAX_M       49
/* MAX_L_E: maximum value for nEnvelopes */
#define MAX_L_E      5
/* MAX_NQ: maximum value for N_Q */
#define MAX_NQ 5

#define MAX_QMF_BANDS   48
#define MAX_NUM_PATCHES          5

#ifdef PS_DEC
/* type definitions */
typedef struct
{
   unsigned char resolution20[3];
   unsigned char resolution34[5];
   qmf_t *work;
   qmf_t (*buffer)[12];
   qmf_t (*temp)[12];
} hyb_info;

typedef struct
{
    /* bitstream parameters */
    unsigned char bEnableIid;
    unsigned char bEnableIcc;
    unsigned char bEnableExt;
    unsigned char freqResIid;
    unsigned char freqResIcc;
    unsigned char nr_iid_par;
    unsigned char nr_ipdopd_par;
    unsigned char nr_icc_par;
    unsigned char frame_class;
    unsigned char num_env;  // max 4

    unsigned char border_position[MAX_PS_ENVELOPES+1];

    unsigned char iid_dt[MAX_PS_ENVELOPES];
    unsigned char icc_dt[MAX_PS_ENVELOPES];

    unsigned char enable_ipdopd;
    unsigned char ipd_mode;
    unsigned char ipd_dt[MAX_PS_ENVELOPES];
    unsigned char opd_dt[MAX_PS_ENVELOPES];

    unsigned char phase_hist;
    unsigned char bPsHeaderValid;       // Indicates whether the ps header is ok 
    unsigned char bPrevPsHeaderValid;   // Indicates whether the ps header of the previous frame was ok
    unsigned char bPrevEnableIid; 
    unsigned char bPrevEnableIcc; 
    /* indices */
    schar iid_index_prev[34];
    schar icc_index_prev[34];
    schar ipd_index_prev[17];
    schar opd_index_prev[17];
    schar iid_index[MAX_PS_ENVELOPES][34];
    schar icc_index[MAX_PS_ENVELOPES][34];
    schar ipd_index[MAX_PS_ENVELOPES][17];
    schar opd_index[MAX_PS_ENVELOPES][17];

    schar ipd_index_1[17];
    schar opd_index_1[17];
    schar ipd_index_2[17];
    schar opd_index_2[17];

    /* ps data was correctly read */
    unsigned char bPsDataAvail;

    /* a header has been read */
    unsigned char header_read;

    /* hybrid filterbank parameters */
    unsigned char use34hybrid_bands;

    /**/
    unsigned char num_groups;
    unsigned char num_hybrid_groups;
    unsigned char nr_par_bands;
    //unsigned char nr_allpass_bands;
    unsigned char decay_cutoff;

    unsigned char *group_border;
    unsigned char *map_group2bk;

    /* filter delay handling */
    //unsigned char saved_delay;
    unsigned char delay_buf_index_ser[NO_ALLPASS_LINKS];
    unsigned char num_sample_delay_ser[NO_ALLPASS_LINKS];
    unsigned char delay14_buf_index;

    /* transients */
    //int alpha_decay;
    //int alpha_smooth;

    int P_PeakDecayNrg[34];
    int P_prev[34];
    int P_SmoothPeakDecayDiffNrg_prev[34];

    hyb_info hyb;

    /* mixing and phase */
    complex_t h11_prev[50];
    complex_t h12_prev[50];
    complex_t h21_prev[50];
    complex_t h22_prev[50];

    //complex_t ipd_prev[20][2];
    //complex_t opd_prev[20][2];
    short ipd_prev[20][2][2];
    short opd_prev[20][2][2];

    complex_t d1_Qmf[64-QMF_SHORT_DELAY_BAND]; /* 1 samples delay max, 35-63 QMF channels */
    complex_t d2_Qmf[2][QMF_ALLPASS_BAND-2]; /* 2 samples delay max, 3-22 QMF channels */    
    complex_t delay_SubQmf[2][32]; /* 2 samples delay max (SubQmf is always allpass filtered) */
    complex_t delay_Qmf[14][QMF_SHORT_DELAY_BAND-QMF_ALLPASS_BAND-1]; /* 14 samples delay max, 23-34 QMF channels */
    complex_t delay_Qmf_ser[5][NO_ALLPASS_LINKS][QMF_ALLPASS_BAND-2]; /* 5 samples delay max (table 8.34), 3-22 QMF channels */
    complex_t delay_SubQmf_ser[5][NO_ALLPASS_LINKS][32]; /* 5 samples delay max (table 8.34) */
    
} ps_info;
#endif

typedef struct
{
    int G_lim_boost[MAX_L_E][MAX_QMF_BANDS];
    int Q_M_lim_boost[MAX_L_E][MAX_QMF_BANDS];
    int S_M_boost[MAX_L_E][MAX_QMF_BANDS];
} sbr_hfadj_info;

typedef struct {
    int *x;
#ifdef OLD_X    
    int *x_bak;
#endif    
    short x_index;
    unsigned char channels;
    unsigned char reserved;
} qmfa_info;

typedef struct {
    int *v;
#ifdef OLD_V    
    int *v_bak;
#endif    
    short v_index;
    unsigned char channels;
    unsigned char reserved;
} qmfs_info;

typedef struct {
   int (*E_curr)[MAX_QMF_BANDS];
   int (*G_temp_prev)[MAX_QMF_BANDS];
   int (*Q_temp_prev)[MAX_QMF_BANDS];
   int *Gt_addr[MAX_L_E];
   int *Qt_addr[MAX_L_E];
   int bwVectorOld[MAX_L_E];  
   short sbrNoiseFloorLevel[MAX_NQ][2];  
   short iEnvelope_prev[MAX_QMF_BANDS];     // 48
   short iEnvelope[MAX_L_E][MAX_QMF_BANDS]; // 5 * 48 

   unsigned short index_noise_prev;
   qmfa_info qmfa;
   qmf_t Xsbr[T_HFGEN][64]; // 40
   unsigned char freqRes_prev;  //
   schar l_A;
   schar GQ_ringbuf_index;
   schar prevEnvIsShort;
    unsigned char psi_is_prev;
   unsigned char frameClass;  
   unsigned char bs_pointer;  //bs_pointer-1 ==tranEnv; exclude 1, 


   unsigned char nEnvelopes;     //max : 5
   unsigned char nNoiseEnvelopes;      // max : 2
   unsigned char bs_add_harmonic_flag;  //ms10 ddt has not use it
   unsigned char bs_add_harmonic_flag_prev;  //ms10 ddt has not use it

   unsigned char domain_vec_noise[3];  
   unsigned char t_Q[3];   // 3

   unsigned char sbr_invf_mode[MAX_L_E];    // 5 
   unsigned char borders2[MAX_L_E+1]; // 6
   unsigned char freqRes[MAX_L_E+1]; // 6    1 bit
   unsigned char borders[9]; // 9    //DBAAC borders[5+1]

   unsigned char domain_vec[9];   
   unsigned char addHarmonics[MAX_M]; // 49,  addHarmonics[48]
   unsigned char addHarmonics_prev[MAX_M]; //49

   unsigned char dont_process;
   int nScaleFactors;
   unsigned char bordersNoise[MAX_NOISE_ENVELOPES+1];
   schar   tranEnv;
   
   //------------------------------------------------
   //SBR_PREV_FRAME_DATA
   //------------------------------------------------
   //short sfb_nrg_prev[MAX_FREQ_COEFFS];
   short prevNoiseLevel[MAX_NOISE_COEFFS];
   unsigned char ampRes_prev;
   unsigned char stopPos;   
   //previous coupling 放在 sbr_info data structure named sbr_coupling_prev;
   unsigned char sbr_invf_mode_prev[MAX_L_E];    // 5    
   //------------------------------------------------
   //------------------------------------------------
   unsigned char coupling;
   unsigned char coupling_prev;
} sbr_ch_info;




typedef struct
{
   sbr_ch_info *sbr_ch[2];
#ifdef PS_DEC
    ps_info *ps;
#endif
#if defined(PS_DEC)
    unsigned char ps_used;
    unsigned char psResetFlag;
#endif
   unsigned int sample_rate;

   unsigned int header_count;
   unsigned char sbr_header_flag;
   unsigned char ampResolution;  
   unsigned char startFreq;  
   unsigned char stopFreq;  
   unsigned char xover_band;  
   unsigned char freqScale;  
   unsigned char alterScale;  
   unsigned char noise_bands;  
   unsigned char limiterBands;  
   unsigned char limiterGains;  
   unsigned char interpolFreq;  
   unsigned char smoothingLength;  
   unsigned char sbr_extension_id;

   unsigned char just_seeked;

   unsigned char ret;
   unsigned char k0;
   //sbr->kx and sbr->M 對應到 lowSubband and highSubband的, lowSubband 和highSubband-lowSubband
   unsigned char kx;
   unsigned char M;     // max : 49
   unsigned char numMaster;  
   unsigned char noPatches;
   unsigned char nInvfBands;      // 5  
   unsigned char nNfb;
   schar kx_prev;
   unsigned char M_prev;
   unsigned char Reset;

   unsigned char startFreq_prev;
   unsigned char stopFreq_prev;
   unsigned char xover_band_prev;
   unsigned char freqScale_prev;
   unsigned char alterScale_prev;
   unsigned char noise_bands_prev;
   unsigned char sr_index;
   unsigned char ampResolutionCurrentFrame[2];  //[2] for each channel 
   unsigned char nSfb[2];   //[2] mean LOW_FREQ and HI_FREQ //nSfb[], its index is general f[]
   unsigned char N_L[4];
   int *p_sbr_stack;
   sbr_hfadj_info *adj;
   unsigned char f_table_noise[5+1]; //6  
   unsigned char numBandsInPatch[MAX_NUM_PATCHES+1];//6
   unsigned char sourceStartBand[MAX_NUM_PATCHES+1];//6
   unsigned char f_table_lo[MAX_QMF_BANDS/2+1]; //30  //freqBandTable[LOW_RES]
   unsigned char f_table_lim[4][MAX_QMF_BANDS/2 + 5];//34
   unsigned char f_table_hi[64+1]; //[MAX_QMF_BANDS+1]; //49 coverity, freqBandTable[HIGH_RES]
   //unsigned char f_table_hi[MAX_QMF_BANDS+1]; //49
   unsigned char table_map_k_to_g[64];
   qmfs_info qmfs[2];
   
   unsigned char sbr_coupling_prev;     
   unsigned char frameErrorFlag;
   unsigned char prevFrameErrorFlag;
   int syncState;
} sbr_info;

extern const unsigned char qmf_stop_min_tab[12];
extern const schar qmf_stop_offset[12][14];

extern const schar qmf_offset[7][16];
extern const unsigned char qmf_start_min_tab[12];
extern const unsigned char qmf_offset_index_tab[12];
extern const int c_sbr_V1[];
extern const short c_sbr_t_h_env_1_5dB[174];
extern const short c_sbr_f_h_env_1_5dB[166];
extern const short c_sbr_t_h_env_bal_1_5dB[90];
extern const short c_sbr_f_h_env_bal_1_5dB[100];
extern const short c_sbr_t_h_env_3_0dB[112];
extern const short c_sbr_f_h_env_3_0dB[110];
extern const short c_sbr_t_h_env_bal_3_0dB[64];
extern const short c_sbr_f_h_env_bal_3_0dB[62];
extern const short c_sbr_t_h_noise_3_0dB[118];
extern const short c_sbr_t_h_noise_bal_3_0dB[48];

extern const int c_sbr_cos_tab[46];
extern const int c_sbr_sin_tab[44];

extern const int c_sbr_qmf_c[320];
extern const complex_ts c_sbr_qmf32_pre_twiddle[];
extern const int c_sbr_chirp_coef[2];
extern const int c_sbr_mapNewBwtbl[4][4];
extern const short c_sbr_logTable[65];
extern const int c_sbr_pow2_tab[65];
extern const int c_sbr_log2_tab[65];
extern const int c_sbr_log2_int_tab[64];
extern const int c_sbr_pan_log2_tab[18];
extern const int c_sbr_log_Qplus1_pan[31][13];
extern const int c_sbr_log_Qplus1[31];
extern const int c_sbr_limGain[];
extern const short c_sbr_h_smooth[];
extern const short c_sbr_N_inv_tbl[];
#ifdef PS_DEC
extern const int c_ps_Phi_Fract_Qmf[];
extern const int c_ps_Q_Fract_allpass_Qmf[][3] ;
extern const int c_ps_Phi_Fract_SubQmf20[];
extern const int c_ps_Phi_Fract_SubQmf34[];
extern const int c_ps_Q_Fract_allpass_SubQmf20[][3];
extern const int c_ps_Q_Fract_allpass_SubQmf34[][3];
extern const int c_ps_cos_alphas[];
extern const int c_ps_sin_alphas[];
extern const short c_ps_cos_betas_normal[][8];
extern const short c_ps_cos_betas_fine[][8];
extern const short c_ps_sin_betas_normal[][8] ;
extern const short c_ps_sin_betas_fine[][8] ;
extern const int c_ps_sincos_alphas_B_normal[][8];
extern const int c_ps_sincos_alphas_B_fine[][8];
extern const short c_ps_cos_gammas_normal[][8];
extern const short c_ps_cos_gammas_fine[][8];
extern const short c_ps_sin_gammas_normal[][8];
extern const short c_ps_sin_gammas_fine[][8];
extern const short c_ps_sf_iid_normal[];
extern const short c_ps_sf_iid_fine[];
extern const short c_ps_filter_a[NO_ALLPASS_LINKS];
extern const short c_ps_ipdopd_cos_tabS16[];
extern const short c_ps_ipdopd_sin_tabS16[];

extern const short c_ps_huff_ipd_df[14];
extern const short c_ps_huff_opd_df[14];
extern const short c_ps_huff_ipd_dt[14];
extern const short c_ps_huff_opd_dt[14];
#endif


#endif

