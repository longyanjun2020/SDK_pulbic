/**
 * \file    mae_font_bengali.h
 * \brief   The document describes the interface of Thai font
 * \author  
 * @version $Id: mae_font_bengali.h $
 */
#ifndef __MAE_FONT_TAMIL_H__
#define __MAE_FONT_TAMIL_H__
#ifdef __INDIC_FONT__
#ifdef __TAMIL_FONT__


#define TAMIL_MASK 0x0B80
//#define TAMIL_BASE_WIDTH_CHAR 0x09BE

#define IS_TAMIL_RANGE(_char) (_char >= TAMIL_S_ANUSVARA && _char <= TAMIL_OS_NUMERNAL)
#define IS_TAMIL_HALANT_CHAR(_char) (_char == TAMIL_S_HALANT)
//#define IS_TAMIL_RA_CHAR(_char) (_char == TAMIL_C_RA)
//#define IS_TAMIL_NUKTA_CHAR(_char) (_char == BENGALI_S_NUKTA)
//#define IS_TAMIL_BINDU_CHAR(_char) (_char == BENGALI_S_CHANDRA_BINDU)
//#define IS_TAMIL_POST_BASE_CON(_char) (_char == TAMIL_C_YA)
//#define IS_BENGALI_DEPVOW_COMPOSING_CHAR(_char) ((_char >= BENGALI_DV_U && _char <= BENGALI_DV_VRR) || (_char >= BENGALI_S_VRR && _char <= BENGALI_S_VLL))

#define IS_TAMIL_PRIV_RANGE(_char) (_char >= TAMIL_L_KU && _char <= TAMIL_L_DV_UU)
//#define IS_BENGALI_PRIV_UP_RA_CHAR(_char) (_char == BENGALI_L_UP_RA )
#define IS_TAMIL_PRIV_DEPVOW_COMPOSING_CHAR(_char) ( (_char >= TAMIL_L_DV_U && _char <= TAMIL_L_DV_UU) )
/*
#define IS_BENGALI_PRIV_RIGHT_T_CHAR(_char) ( _char == 0xEA05 || _char == 0xEA07 || _char == 0xEA0F || _char == 0xEA10 \
	                                        || _char == 0xEA12 || _char == 0xEA13 || _char == 0xEA4A || _char == 0xEA62 \
	                                        || _char == 0xEA65 || _char == 0xEA67 || _char == 0xEA68 || _char == 0xEA6B \
                                            || _char == 0xEA6C || _char == 0xEA6D || _char == 0xEA71 || _char == 0xEA72 \
											|| _char == 0xEA75 || _char == 0xEA8A || _char == 0xEA8B || _char == 0xEAAC \
											|| _char == 0xEAB7 || _char == 0xEABC || _char == 0xEAC2 || _char == 0xEACA \
											|| _char == 0xEACB || _char == 0xEACC || _char == 0xEACB || _char == 0xEACE \
											|| _char == 0xEAD0 || _char == 0xEAD1) 
#define IS_BENGALI_PRIV_CENTER_T_CHAR(_char) ( _char == 0xEA00 || _char == 0xEA01 || _char == 0xEA03 || _char == 0xEA0B \
	                                        || _char == 0xEA18 || _char == 0xEA19 || _char == 0xEA1B || _char == 0xEA20 \
	                                        || _char == 0xEA23 || _char == 0xEA24 || _char == 0xEA38 \
                                            || _char == 0xEA16 || _char == 0xEA1A || _char == 0xEA1D || _char == 0xEA29 \
											|| _char == 0xEA33 || _char == 0xEA35 || _char == 0xEA39 || _char == 0xEA4E \
											|| _char == 0xEA70 || _char == 0xEABE || _char == 0xEAC7 || _char == 0xEACD \
											|| _char == 0xEA8E || _char == 0xEA91 || _char == 0xEA93 || _char == 0xEA94 || _char == 0xEAA2) 
#define IS_BENGALI_PRIV_RIGHT_POS_CHAR(_char) (_char == BENGALI_C_HA_YA)
#define IS_BENGALI_PRIV_LEFT_T_POS_CHAR(_char) ((_char >= BENGALI_C_HA_BA && _char <= BENGALI_C_HA_TA))
*/

typedef enum
{
	/* VARIOUS SIGNS + INDEPENDENT VOWEL */
	  TAMIL_S_ANUSVARA = 0xb82,
    TAMIL_S_VISARGA = 0xb83,
    TAMIL_IV_A = 0xb85,
    TAMIL_IV_AA = 0xb86,
    TAMIL_IV_I = 0xb87,
    TAMIL_IV_II = 0xb88,
    TAMIL_IV_U = 0xb89,
    TAMIL_IV_UU = 0xb8a,

    TAMIL_IV_E = 0xb8e,
    TAMIL_IV_EE = 0xb8f,
    TAMIL_IV_AI = 0xb90,
    TAMIL_IV_O = 0xb92,
    TAMIL_IV_OO = 0xb93,
    TAMIL_IV_AU = 0xb94,

    /* CONSONANTS */
    TAMIL_C_KA = 0xb95,
    TAMIL_C_NGA = 0xb99,
    TAMIL_C_CHA = 0xb9a,
    TAMIL_C_JA = 0xb9c,
    TAMIL_C_NYA = 0xb9e,
    TAMIL_C_TTA = 0xb9f,
    TAMIL_C_NNA = 0xba3,
    TAMIL_C_TA = 0xba4,
    TAMIL_C_NA = 0xba8,
    TAMIL_C_NNNA = 0xba9,
    TAMIL_C_PA = 0xbaa,
    TAMIL_C_MA = 0xbae,
    TAMIL_C_YA = 0xbaf,
    TAMIL_C_RA = 0xbb0,
    TAMIL_C_RRA = 0xbb1,
    TAMIL_C_LA = 0xbb2,
    TAMIL_C_LLA = 0xbb3,
    TAMIL_C_LLLA = 0xbb4,
    TAMIL_C_VA = 0xbb5,
    TAMIL_C_SHA = 0xbb6,
    TAMIL_C_SSA = 0xbb7,
    TAMIL_C_SA = 0xbb8,
    TAMIL_C_HA = 0xbb9,

    /* DEPENDENT VOWELS */
    TAMIL_DV_AA = 0xbbe,
    TAMIL_DV_I = 0xbbf,
    TAMIL_DV_II = 0xbc0,
    TAMIL_DV_U = 0xbc1,
    TAMIL_DV_UU = 0xbc2,
    TAMIL_DV_E = 0xbc6,
    TAMIL_DV_EE = 0xbc7,
    TAMIL_DV_AI = 0xbc8,
    TAMIL_DV_O = 0xbca,
    TAMIL_DV_OO = 0xbcb,
    TAMIL_DV_AU = 0xbcc,

    /* SIGNS */
    TAMIL_S_HALANT = 0xbcd,

    /* APPEND DEPENDENT VOWEL */
    TAMIL_AD_AU = 0xbd7,

    TAMIL_S_DANDA = 0xbe4,
    TAMIL_S_DDANDA = 0xbe5,
    /* DIGITS */
    TAMIL_D_ZERO = 0xbe6,
    TAMIL_D_ONE = 0xbe7,
    TAMIL_D_TWO = 0xbe8,
    TAMIL_D_THREE = 0xbe9,
    TAMIL_D_FOUR = 0xbea,
    TAMIL_D_FIVE = 0xbeb,
    TAMIL_D_SIX = 0xbec,
    TAMIL_D_SEVEN = 0xbed,
    TAMIL_D_EIGHT = 0xbee,
    TAMIL_D_NINE = 0xbef,

    /* TAMIL NUMERICS */
    TAMIL_D_TEN = 0xbf0,
    TAMIL_D_HUNDRED = 0xbf1,
    TAMIL_D_THOUSAND = 0xbf2,

    /* TAMIL SYMBOLS */
    TAMIL_OS_DAY = 0xbf3,
    TAMIL_OS_MONTH = 0xbf4,
    TAMIL_OS_YEAR = 0xbf5,
    TAMIL_OS_DEBIT = 0xbf6,
    TAMIL_OS_CREDIT = 0xbf7,
    TAMIL_OS_ABOVE = 0xbf8,

    /* CURRENCY SYMBOL */
    TAMIL_OS_RUPEE = 0xbf9,

    /* TAMIL SYMBOLS */
    TAMIL_OS_NUMERNAL = 0xbfa
} tamil_characters_enum;

typedef enum
{
    /* various ligature etc */
    TAMIL_L_KU = 0xee01,
    TAMIL_L_KUU = 0xee02,
    TAMIL_L_NGU = 0xee03,
    TAMIL_L_NGUU = 0xee04,
    TAMIL_L_CHU = 0xee05,
    TAMIL_L_CHUU = 0xee06,
    TAMIL_L_NYU = 0xee07,
    TAMIL_L_TTI = 0xee08,
    TAMIL_L_TTII = 0xee09,
    TAMIL_L_TTU = 0xee0A,
    TAMIL_L_TTUU = 0xee0B,
    TAMIL_L_NNU = 0xee0C,
    TAMIL_L_TU = 0xee0D,
    TAMIL_L_NU = 0xee0E,
    TAMIL_L_NNNU = 0xee0F,
    TAMIL_L_PU = 0xee10,
    TAMIL_L_PUU = 0xee11,
    TAMIL_L_MU = 0xee12,
    TAMIL_L_MUU = 0xee13,
    TAMIL_L_YU = 0xee14,
    TAMIL_L_YUU = 0xee15,
    TAMIL_L_RI = 0xee16,
    TAMIL_L_RII = 0xee17,
    TAMIL_L_RU = 0xee18,
    TAMIL_L_RUU = 0xee19,
    TAMIL_L_RRU = 0xee1A,
    TAMIL_L_LU = 0xee1B,
    TAMIL_L_LLU = 0xee1C,
    TAMIL_L_LLUU = 0xee1D,
    TAMIL_L_LLLU = 0xee1E,
    TAMIL_L_LLLUU = 0xee1F,
    TAMIL_L_VU = 0xee20,
    TAMIL_L_VUU = 0xee21,
    TAMIL_L_SHREE = 0xee22,
    TAMIL_L_RA_HALANT = 0xee23,
    TAMIL_L_APP_UU = 0xee24,
    TAMIL_L_PA_HALANT = 0xee25,
    TAMIL_L_RRA_HALANT = 0xee26,
    TAMIL_L_KSHA = 0xee27,
    TAMIL_L_KI = 0xEE28,
    TAMIL_L_KII = 0xee29,
    TAMIL_L_NGI = 0xee2a,
    TAMIL_L_NGII = 0xee2b,
    TAMIL_L_CHI = 0xee2c,
    TAMIL_L_CHII = 0xee2d,
    TAMIL_L_JI = 0xee2e,
    TAMIL_L_JII = 0xee2f,
    TAMIL_L_NYI = 0xee30,
    TAMIL_L_NYII = 0xee31,
    TAMIL_L_NNI = 0xee32,
    TAMIL_L_NNII = 0xee33,
    TAMIL_L_TI = 0xee34,
    TAMIL_L_TII = 0xee35,
    TAMIL_L_NI = 0xee36,
    TAMIL_L_NII = 0xee37,
    TAMIL_L_NNNI = 0xee38,
    TAMIL_L_NNNII = 0xee39,
    TAMIL_L_PI = 0xee3a,
    TAMIL_L_PII = 0xee3b,
    TAMIL_L_MI = 0xee3c,
    TAMIL_L_MII = 0xee3d,
    TAMIL_L_YI = 0xee3e,
    TAMIL_L_YII = 0xee3f,
    TAMIL_L_RRI = 0xee40,
    TAMIL_L_RRII = 0xee41,
    TAMIL_L_LI = 0xee42,
    TAMIL_L_LII = 0xee43,
    TAMIL_L_LLI = 0xee44,
    TAMIL_L_LLII = 0xee45,
    TAMIL_L_LLLI = 0xee46,
    TAMIL_L_LLLII = 0xee47,
    TAMIL_L_VI = 0xee48,
    TAMIL_L_VII = 0xee49,
    TAMIL_L_KSHI = 0xee4a,
    TAMIL_L_KSHII = 0xee4b,
    TAMIL_L_SSI = 0xee4c,
    TAMIL_L_SSII = 0xee4d,
    TAMIL_L_SI = 0xee4e,
    TAMIL_L_SII = 0xee4f,
    TAMIL_L_HI = 0xee50,
    TAMIL_L_HII = 0xee51,
    TAMIL_L_DV_U = 0xee52,
    TAMIL_L_DV_UU = 0xee53
} tamil_ligatures_enum;


#endif //__INDIC_FONT__
#endif //__TAMIL_FONT__
#endif /* __MAE_FONT_TAMIL_H__ */
