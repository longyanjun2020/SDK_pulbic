/**
 * \file    mae_font_thai.h
 * \brief   The document describes the interface of Thai font
 * \author  steve.lee@mstarsemi.com
 * @version $Id: mae_font_thai.h 1756 2009-09-10 14:13:56Z bill.pan $
 */
#ifndef __MAE_FONT_DEVANAGARI_PRIV_H__
#define __MAE_FONT_DEVANAGARI_PRIV_H__
#ifdef __INDIC_FONT__
#ifdef __DVNG_FONT__

#define DVNG_MASK 0x0900
#define DVNG_BASE_WIDTH_CHAR 0x093E

#define IS_DVNG_RANGE(_char) (_char >= DVNG_S_CHANDRA_BINDU && _char <= DVNG_S_RUPEE)
#define IS_DVNG_RA_CHAR(_char) (_char == DVNG_C_RA)
#define IS_DVNG_HALANT_CHAR(_char) (_char == DVNG_S_HALANT)
#define IS_DVNG_NUKTA_CHAR(_char) (_char == DVNG_S_NUKTA)
#define IS_DVNG_BINDU_CHAR(_char) (_char == DVNG_S_CHANDRA_BINDU || _char == DVNG_S_BINDU)
#define IS_DVNG_WITH_NUKTA_CHAR(_char) (_char == DVNG_C_NNNA || _char == DVNG_C_RRA || _char == DVNG_C_LLLA || (_char >= DVNG_AC_QA && _char <= DVNG_AC_YYA))
#define IS_DVNG_NO_HALF_CHAR(_char) (_char == DVNG_NIV_CE)
#define IS_DVNG_DEPVOW_COMPOSING_CHAR(_char) ((_char >= DVNG_DV_U && _char <= DVNG_DV_AI) || _char == DVNG_S_HALANT)

#define IS_DVNG_DEPVOW_LONG_DOWN_CHAR(_char) (_char == DVNG_C_HA)
#define IS_DVNG_DEPVOW_SMALL_CHAR(_char) (_char == DVNG_C_RA)

#define IS_DVNG_PRIV_RANGE(_char) (_char >= DVNG_L_KSHA && _char <= DVNG_H_KHA_RA)
#define IS_DVNG_PRIV_HALF_RA_CHAR(_char) (_char == DVNG_H_RA_RA)
#define IS_DVNG_PRIV_UP_RA_CHAR(_char) (_char == DVNG_SUP_RA || _char == DVNG_L_DVERA || _char == DVNG_L_DVAIRA || _char == DVNG_L_DVORA || _char == DVNG_L_DVAURA )
#define IS_DVNG_PRIV_CONJUNCT_CHAR(_char) (_char == DVNG_L_KSHA || _char == DVNG_L_GYA || _char == DVNG_L_TRA || _char == DVNG_L_SHRA || _char == DVNG_L_TTTA )
#define IS_DVNG_PRIV_DEPVOW_COMPOSING_CHAR(_char) (_char == DVNG_L_RABIN || _char == DVNG_SUP_RA || _char == DVNG_SUB_RA || (_char >= DVNG_L_ME && _char <= DVNG_L_DVAIBINRA))
#define IS_DVNG_PRIV_RIGHT_T_CHAR(_char) ((_char >= DVNG_L_KSHA && _char <= DVNG_L_SHRA) \
                                            || (_char >= DVNG_L_JRA && _char <= DVNG_L_JRA_N) \
	                                    	|| (_char >= DVNG_L_PRA && _char <= DVNG_L_SRA) \
	                                    	|| _char == DVNG_H_PHA || _char == DVNG_H_HA || _char == DVNG_L_DADHA || _char == DVNG_L_DA_GHA \
	                                    	|| (_char >= DVNG_L_DABHA && _char <= DVNG_L_DDYA) \
                                    		|| (_char >= DVNG_L_NNNA && _char <= DVNG_L_HYA) \
                                    		|| (_char >= DVNG_L_KHRA && _char <= DVNG_L_CHRA) \
                                    		|| (_char >= DVNG_L_JHRA && _char <= DVNG_L_BHRA) \
									        || _char == DVNG_L_YRA \
									        || (_char >= DVNG_H_TTAA && _char <= DVNG_H_PHA_N) \
		                                    || (_char >= DVNG_L_KSHA_RA && _char <= DVNG_L_GYA_RA) \
        		                            || (_char >= DVNG_L_KHA_NA && _char <= DVNG_L_TA_NA) \
                		                    || (_char >= DVNG_L_PA_TA && _char <= DVNG_L_SHA_VA) \
                        		            || _char == DVNG_L_SSA_RA || _char == DVNG_L_LLA_RA)

#define IS_DVNG_PRIV_CENTER_T_CHAR(_char) (_char == DVNG_L_KRA \
                                            || (_char >= DVNG_L_FRA && _char <= DVNG_L_FRA_N) \
                                            || (_char >= DVNG_L_RU && _char <= DVNG_L_RUU) \
											|| (_char >= DVNG_H_KA && _char <= DVNG_H_GHA) \
											|| _char == DVNG_H_JHA \
											|| (_char >= DVNG_H_MA && _char <= DVNG_H_YA) \
											|| _char == DVNG_H_SA \
											|| (_char >= DVNG_L_KKA && _char <= DVNG_L_DAGHA) \
											|| (_char >= DVNG_L_DYA && _char <= DVNG_L_DA_BA) \
											|| (_char >= DVNG_L_DVA && _char <= DVNG_L_DADDHA))

#define IS_DVNG_PRIV_DEPVOW_LEFT_JOINER_CHAR(_char) (_char == DVNG_L_DV_I_C)
#define IS_DVNG_PRIV_DEPVOW_RIGHT_JOINER_CHAR(_char) ((_char >= DVNG_L_NCAND && _char <= DVNG_L_NBINDU) \
                                                      || (_char >= DVNG_L_MII && _char <= DVNG_L_IIRAHALB) \
                                                      || (_char >= DVNG_L_MO && _char <= DVNG_L_DVAURA) \
                                                      || _char == DVNG_L_DVAUBINRA)

#define IS_DVNG_PRIV_CENTER_T_UP_POS_CHAR(_char) (_char == DVNG_L_RABIN || _char == DVNG_SUP_RA)
#define IS_DVNG_PRIV_CENTER_T_DOWN_POS_CHAR(_char) (_char == DVNG_SUB_RA)
#define IS_DVNG_PRIV_LEFT_T_POS_CHAR(_char) ((_char >= DVNG_L_ME && _char <= DVNG_L_DVAIBINRA))

typedef enum
{		
	/* Various signs*/
	DVNG_S_CHANDRA_BINDU=0x0901,
	DVNG_S_BINDU		=0x902,
	DVNG_S_VISARGA		=0x903,

	/* Independent vowels */
	DVNG_NIV_A			=0x904,
	DVNG_IV_A			=0x905,
	DVNG_IV_AA			=0x906,
	DVNG_IV_I			=0x907,
	DVNG_IV_II			=0x908,			
    DVNG_IV_U			=0x909,
	DVNG_IV_UU			=0x90a,
	DVNG_IV_R			=0x90b,
	DVNG_NIV_L			=0x90c,
	DVNG_NIV_CE			=0x90d,
	DVNG_NIV_SE			=0x90e,
	DVNG_IV_E			=0x90f,
	DVNG_IV_AI			=0x910,
	DVNG_NIV_CO			=0x911,
	DVNG_NIV_SO			=0x912,
	DVNG_IV_O			=0x913,
	DVNG_IV_AU			=0x914,
    
	/* Consonants */        
    DVNG_C_KA			=0x915,
	DVNG_C_KHA			=0x916,
	DVNG_C_GA			=0x917,
	DVNG_C_GHA			=0x918,
	DVNG_C_NGA			=0x919,
	DVNG_C_CHA			=0x91a,
	DVNG_C_CHHA			=0x91b,
	DVNG_C_JA			=0x91c,
	DVNG_C_JHA			=0x91d,
	DVNG_C_NYA			=0x91e,
	DVNG_C_TTA			=0x91f,
	DVNG_C_TTHA			=0x920,
	DVNG_C_DDA			=0x921,
	DVNG_C_DDHA			=0x922,
	DVNG_C_NNA			=0x923,
	DVNG_C_TA			=0x924,
	DVNG_C_THA			=0x925,
	DVNG_C_DA			=0x926,
	DVNG_C_DHA			=0x927,
	DVNG_C_NA			=0x928,
	DVNG_C_NNNA			=0x929,
	DVNG_C_PA			=0x92a,
	DVNG_C_PHA			=0x92b,
	DVNG_C_BA			=0x92c,
	DVNG_C_BHA			=0x92d,
	DVNG_C_MA			=0x92e,
	DVNG_C_YA			=0x92f,
	DVNG_C_RA			=0x930,
	DVNG_C_RRA			=0x931,
	DVNG_C_LA			=0x932,
	DVNG_C_LLA			=0x933,
	DVNG_C_LLLA			=0x934,
	DVNG_C_VA			=0x935,
	DVNG_C_SHA			=0x936,
	DVNG_C_SSA			=0x937,
	DVNG_C_SA			=0x938,
	DVNG_C_HA			=0x939,
    
	/* Various signs */
	DVNG_S_NUKTA		=0x93c,
	DVNG_NS_AVAGRAHA	=0x93d,
    
	/* Dependent vowel signs */
	DVNG_DV_AA			=0x93e,
	DVNG_DV_I			=0x93f,
	DVNG_DV_II			=0x940,
	DVNG_DV_U			=0x941,
	DVNG_DV_UU			=0x942,
	DVNG_DV_R			=0x943,
	DVNG_NDV_RR			=0x944,
	DVNG_DV_CE			=0x945,
	DVNG_NDV_E			=0x946,
	DVNG_DV_E			=0x947,
	DVNG_DV_AI			=0x948,
	DVNG_NDV_CO			=0x949,
	DVNG_NDV_O			=0x94a,
	DVNG_DV_O			=0x94b,
	DVNG_DV_AU			=0x94c,
    
	/* Various signs */
	DVNG_S_HALANT		=0x94d,
	DVNG_NS_RESERVED1	=0x94e,
	DVNG_NS_RESERVED2	=0x94f,
	DVNG_S_OM			=0x950,
	DVNG_NS_UDATTA		=0x951,
	DVNG_NS_ANUDATTA	=0x952,
	DVNG_NS_GACCENT		=0x953,
	DVNG_NS_AACCENT		=0x954,
	
	/* Additional consonants */
	DVNG_AC_QA			=0x958,
	DVNG_AC_KHHA		=0x959,
	DVNG_AC_GHHA		=0x95a,
	DVNG_AC_ZA			=0x95b,
	DVNG_AC_DDDHA		=0x95c,
	DVNG_AC_RHA			=0x95d,
	DVNG_AC_FA			=0x95e,
	DVNG_AC_YYA			=0x95f,
	
	/* Generic additions */
	DVNG_NG_RR			=0x960,
	DVNG_NG_LL			=0x961,
	DVNG_NG_L			=0x962,
	DVNG_NG_VLL			=0x963,
	DVNG_NG_D			=0x964,
	DVNG_NG_DD			=0x965,
	
	/* Digits */
	DVNG_D_ZERO			=0x966,
	DVNG_D_ONE			=0x967,
	DVNG_D_TWO			=0x968,
	DVNG_D_THREE		=0x969,
	DVNG_D_FOUR			=0x96a,
	DVNG_D_FIVE			=0x96b,
	DVNG_D_SIX			=0x96c,
	DVNG_D_SEVEN		=0x96d,
	DVNG_D_EIGHT		=0x96e,
	DVNG_D_NINE			=0x96f,
	
	/* Devanagari-specific additions */
	DVNG_S_ABBR			=0x970,
	DVNG_S_RUPEE		=0x971
}DevanagariChar_e;

typedef	enum
{
	/*various half forms,ligature etc */
	DVNG_L_KSHA			=0xE900,
	DVNG_L_GYA			=0xE901,
	DVNG_L_TTTA			=0xE902,
	DVNG_L_TRA			=0xE903,
	DVNG_L_SHRA			=0xE905,
	DVNG_L_KRA			=0xE907,
	DVNG_L_JRA			=0xE908,
	DVNG_L_JRA_N		=0xE909,
	DVNG_L_FRA			=0xE90A,
	DVNG_L_FRA_N		=0xE90B,
	DVNG_L_PRA			=0xE90C,
	DVNG_L_SRA			=0xE90D,
	DVNG_L_RU			=0xE90E,
	DVNG_L_RUU			=0xE90F,
	DVNG_H_KA			=0xE915,
	DVNG_H_KHA			=0xE916,
	DVNG_H_GA			=0xE917,
	DVNG_H_GHA			=0xE918,
	DVNG_H_CHA			=0xE91A,
	DVNG_H_CHHA			=0xE91B,
	DVNG_H_JA			=0xE91C,
	DVNG_H_JHA			=0xE91D,
	DVNG_H_NYA			=0xE91E,
	DVNG_H_ANNA			=0xE923,
	DVNG_H_TA			=0xE924,
	DVNG_H_THA			=0xE925,
	DVNG_H_DHA			=0xE927,
	DVNG_H_NA			=0xE928,
	DVNG_H_NNNA			=0xE929,
	DVNG_H_PA			=0xE92A,
	DVNG_H_PHA			=0xE92B,
	DVNG_H_BA			=0xE92C,
	DVNG_H_BHA			=0xE92D,
	DVNG_H_MA			=0xE92E,
	DVNG_H_YA			=0xE92F,
	DVNG_H_RA			=0xE930,
	DVNG_H_LA			=0xE932,
	DVNG_H_LLA			=0xE933,
	DVNG_H_LLLA			=0xE934,
	DVNG_H_VA			=0xE935,
	DVNG_H_SHA			=0xE936,
	DVNG_H_SSA			=0xE937,
	DVNG_H_SA			=0xE938,
	DVNG_H_HA			=0xE939,
	DVNG_L_KKA			=0xE940,
	DVNG_L_KTA			=0xE941,
	DVNG_L_DAKA			=0xE942,
	DVNG_L_DAKHA		=0xE943,
	DVNG_L_DAGA			=0xE944,
	DVNG_L_DAGHA		=0xE945,
	DVNG_L_DADHA		=0xE947,
	DVNG_L_DYA			=0xE948, //new
	DVNG_L_DA_GHA		=0xE949,
	DVNG_L_DA_BA		=0xE94A,
	DVNG_L_DABHA		=0xE94B,
	DVNG_L_DAMA			=0xE94C,
	DVNG_L_DDYA			=0xE94D, //new
	DVNG_L_DVA			=0xE94E, //new
	DVNG_L_TTTTA		=0xE94F,
	DVNG_L_TTHA			=0xE950,
	DVNG_L_TTTHA		=0xE951,
	DVNG_L_DDAGA		=0xE952,
	DVNG_L_DADA			=0xE953,
	DVNG_L_DADDHA		=0xE954,
	DVNG_L_NNNA			=0xE955,
	DVNG_L_HMMA			=0xE956,
	DVNG_L_HYA			=0xE957,
	DVNG_H_LLLA_RA		=0xE95B,
	DVNG_H_AC_QA_RA		=0xE95C,
	DVNG_H_AC_KHHA_RA	=0xE95D,
	DVNG_H_AC_GHHA_RA	=0xE95E,
	DVNG_H_AC_ZA_RA		=0xE95F,
	DVNG_H_AC_YYA_RA	=0xE960,
	DVNG_H_SHA_CHA		=0xE961,
	DVNG_H_SHA_LA		=0xE962,
	DVNG_H_KHA_NA		=0xE963,
	DVNG_H_TA_NA		=0xE964,
	DVNG_H_PA_TA		=0xE965,
	DVNG_L_DA_MR		=0xE966,
	DVNG_H_KHSA			=0xE970,
	DVNG_H_GYAA			=0xE971,
	DVNG_H_TTA			=0xE972,
	DVNG_H_TRA			=0xE973,
	DVNG_H_SHA_VA		=0xE974,
	DVNG_H_SHRA			=0xE975,
	DVNG_H_SHA_NA		=0xE976,
	DVNG_L_RABIN		=0xE97B,
	DVNG_H_EYLASH		=0xE97D,
	DVNG_SUP_RA			=0xE97E,
	DVNG_SUB_RA			=0xE97F,
	DVNG_L_NCAND		=0xE980,
	DVNG_L_NBINDU		=0xE981,
	DVNG_L_DV_I_C       =0xE983,
	DVNG_L_IRAHAL		=0xE985,
	DVNG_L_IRAHALB		=0xE986,
	DVNG_L_MII			=0xE987, //new matra ligature
	DVNG_L_MIIRA		=0xE988,
	DVNG_L_IIRAHALB		=0xE989,
	DVNG_L_ME			=0xE98B, //new matra ligature
	DVNG_L_DVERA		=0xE98C,
	DVNG_L_DVEBINRA		=0xE98D,
	DVNG_L_MAI			=0xE98E,
	DVNG_L_DVAIRA		=0xE98F,
	DVNG_L_DVAIBINRA	=0xE990,
	DVNG_L_MO			=0xE991, //new matra ligature
	DVNG_L_DVORA		=0xE992,
	DVNG_L_DVOBINRA		=0xE993,
	DVNG_L_MAU			=0xE994,
	DVNG_L_DVAURA		=0xE995,
	DVNG_L_KHRA			=0xE996,
	DVNG_L_GRA			=0xE997,
	DVNG_L_GHRA			=0xE998,
	DVNG_L_CHRA			=0xE999,
	DVNG_L_JHRA			=0xE99B,
	DVNG_L_THRA			=0xE99C,
	DVNG_L_DRA			=0xE99D,
	DVNG_L_DHRA			=0xE99E,
	DVNG_L_NRA			=0xE99F,
	DVNG_L_MRA			=0xE9A0,
	DVNG_L_BRA			=0xE9A1,
	DVNG_L_BHRA			=0xE9A2,
	DVNG_L_HRA			=0xE9A3,
	DVNG_L_YRA			=0xE9A4,
	DVNG_H_TTAA			=0xE9A6,
	DVNG_H_PHA_N		=0xE9A7,
	DVNG_H_GYA			=0xE9A8,
	DVNG_H_JA_N			=0xE9A9,
	DVNG_L_VRA			=0xE9AA,
	DVNG_L_YA_N			=0xE9AB,
	DVNG_L_KA_N			=0xE9AC,
	DVNG_L_DVAUBINRA	=0xE9AD,
	DVNG_L_KHA_N		=0xE9AE,
	DVNG_L_GA_N			=0xE9AF,
	DVNG_L_KRA_N		=0xE9B0,
	DVNG_L_KHRA_N		=0xE9B1,
	DVNG_L_GRA_N		=0xE9B2,
	DVNG_L_YRA_N		=0xE9B3,
	DVNG_L_SSAGA		=0xE9BE,
	DVNG_L_SSA_TTA_RA	=0xE9C1,
	DVNG_L_KSHA_RA		=0xE9C2,
	DVNG_L_GYA_RA		=0xE9C3,
	DVNG_H_S_TA			=0xE9C4,
	DVNG_L_KHA_NA		=0xE9C5,
	DVNG_L_NGA_MA		=0xE9C6,
	DVNG_L_NYA_RA		=0xE9C7,
	DVNG_L_NNA_RA		=0xE9C8,
	DVNG_L_TA_NA		=0xE9C9,
	DVNG_L_DA_GA		=0xE9CA,
	DVNG_L_DA_NA		=0xE9CB,
	DVNG_L_PA_TA		=0xE9CC,
	DVNG_L_LA_RA		=0xE9CD,
	DVNG_L_SHA_CHA		=0xE9CE,
	DVNG_L_SHA_NA		=0xE9CF,
	DVNG_L_SHA_LA		=0xE9D0,	
	DVNG_L_SHA_VA		=0xE9D1,
	DVNG_L_SSA_TTHA		=0xE9D2,
	DVNG_L_SSA_RA		=0xE9D3,
	DVNG_L_HA_NNA		=0xE9D4,
	DVNG_L_HA_NA		=0xE9D5,
	DVNG_L_HA_LA		=0xE9D6,
	DVNG_L_HA_VA		=0xE9D7,
	DVNG_L_LLA_RA		=0xE9D8,
	DVNG_L_TTHA_RA_S	=0xE9D9,
	DVNG_L_NGA_RA_S		=0xE9DA,
	DVNG_L_CHHA_RA_S	=0xE9DB,
	DVNG_L_DDA_RA_S		=0xE9DC,
	DVNG_L_TTA_RA_S		=0xE9DD,
	DVNG_H_GA_RA		=0xE9DE,
	DVNG_H_GHA_RA		=0xE9DF,
	DVNG_H_CHA_RA		=0xE9E0,
	DVNG_H_JA_RA		=0xE9E1,
	DVNG_H_JHA_RA		=0xE9E2,
	DVNG_H_NYA_RA		=0xE9E3,
	DVNG_H_NNA_RA		=0xE9E4,
	DVNG_H_TA_RA		=0xE9E5,
	DVNG_H_THA_RA		=0xE9E6,
	DVNG_H_DHA_RA		=0xE9E7,
	DVNG_H_NA_RA		=0xE9E8,
	DVNG_H_NNNA_RA		=0xE9E9,
	DVNG_H_PA_RA		=0xE9EA,
	DVNG_H_PHA_RA		=0xE9EB,
	DVNG_H_BA_RA		=0xE9EC,
	DVNG_H_BHA_RA		=0xE9ED,
	DVNG_H_MA_RA		=0xE9EE,
	DVNG_H_YA_RA		=0xE9EF,
	DVNG_H_RA_RA		=0xE9F0,
	DVNG_H_LA_RA		=0xE9F1,
	DVNG_H_VA_RA		=0xE9F2,
	DVNG_H_SSA_RA		=0xE9F4,
	DVNG_H_SA_RA		=0xE9F5,
	DVNG_H_HA_RA		=0xE9F6,
	DVNG_H_KSHA_RA		=0xE9F7,
	DVNG_H_GYA_RA		=0xE9F8,
	DVNG_H_KA_RA		=0xE9F9,
	DVNG_H_KHA_RA		=0xE9FA
}DevanagariLigatures_e;

#endif //__DVNG_FONT__
#endif //__INDIC_FONT__
#endif /* __MAE_FONT_HINDI_PRIV_H__ */
