/**
 * \file    mae_font_bengali.h
 * \brief   The document describes the interface of Thai font
 * \author  
 * @version $Id: mae_font_bengali.h $
 */
#ifndef __MAE_FONT_BENGALI_H__
#define __MAE_FONT_BENGALI_H__
#ifdef __INDIC_FONT__
#ifdef __BENGALI_FONT__

#define __BENGALI_NON_LIGATED__

#define BENGALI_MASK 0x0980
#define BENGALI_BASE_WIDTH_CHAR 0x09BE

#define IS_BENGALI_RANGE(_char) (_char >= BENGALI_S_CHANDRA_BINDU && _char <= BENGALI_OS_ISSHAR)
#define IS_BENGALI_HALANT_CHAR(_char) (_char == BENGALI_S_HALANT)
#define IS_BENGALI_RA_CHAR(_char) (_char == BENGALI_C_RA)
#define IS_BENGALI_NUKTA_CHAR(_char) (_char == BENGALI_S_NUKTA)
#define IS_BENGALI_BINDU_CHAR(_char) (_char == BENGALI_S_CHANDRA_BINDU)
#define IS_BENGALI_WITH_NUKTA_CHAR(_char) (_char == BENGALI_C_RRA || _char == BENGALI_C_RHA || _char == BENGALI_C_YYA)
#define IS_BENGALI_NO_HALF_CHAR(_char) (_char == BENGALI_C_GHA || _char == BENGALI_C_CHA || _char == BENGALI_C_NYA || _char == BENGALI_C_YA || _char == BENGALI_C_SSA)
#define IS_BENGALI_POST_BASE_CON(_char) (_char == BENGALI_C_YA)
#define IS_BENGALI_DEPVOW_COMPOSING_CHAR(_char) ((_char >= BENGALI_DV_U && _char <= BENGALI_DV_VRR) || (_char >= BENGALI_S_VRR && _char <= BENGALI_S_VLL))

#define IS_BENGALI_PRIV_RANGE(_char) (_char >= BENGALI_L_KA_KA && _char <= BENGALI_L_YA_BA)
#define IS_BENGALI_PRIV_UP_RA_CHAR(_char) (_char == BENGALI_L_UP_RA )
#define IS_BENGALI_PRIV_DEPVOW_COMPOSING_CHAR(_char) (_char == BENGALI_L_UP_RA || _char == BENGALI_C_HA_BA_3 \
                                                      || (_char >= BENGALI_C_HA_YA && _char <= BENGALI_C_HA_TA) \
                                                      || (_char >= BENGALI_C_HA_BA_2 && _char <= BENGALI_C_HA_LA_2))
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
#define IS_BENGALI_PRIV_CENTER_T_POS_CHAR(_char) ((_char >= BENGALI_C_HA_BA_2 && _char <= BENGALI_C_HA_LA_2))
#define IS_BENGALI_CONST_NEED_DV_RIGHT_CHAR(_char) ( _char == 0x099B || _char == 0x09B9 || _char == 0x09DC || _char == 0x09DD)

typedef enum
{		
	/* Various signs */
    BENGALI_S_CHANDRA_BINDU	= 0x981,
    BENGALI_S_ANUSVARA		= 0x982,
    BENGALI_S_VISARGA		= 0x983,

	/*Independent vowels*/
    BENGALI_IV_A			= 0x985,
    BENGALI_IV_AA			= 0x986,
    BENGALI_IV_I			= 0x987,
    BENGALI_IV_II			= 0x988,
    BENGALI_IV_U			= 0x989,
    BENGALI_IV_UU			= 0x98a,
    BENGALI_IV_VR			= 0x98b,
    BENGALI_IV_VL			= 0x98c,
    
	BENGALI_IV_E			= 0x98f,
    BENGALI_IV_AI			= 0x990,
    BENGALI_IV_O			= 0x993,
    BENGALI_IV_AU			= 0x994,

    /* Consonants */
    BENGALI_C_KA			= 0x995,
    BENGALI_C_KHA			= 0x996,
    BENGALI_C_GA			= 0x997,
    BENGALI_C_GHA			= 0x998,
    BENGALI_C_NGA			= 0x999,
    BENGALI_C_CA			= 0x99a,
    BENGALI_C_CHA			= 0x99b,
    BENGALI_C_JA			= 0x99c,
    BENGALI_C_JHA			= 0x99d,
    BENGALI_C_NYA			= 0x99e,
    BENGALI_C_TTA			= 0x99f,  
    BENGALI_C_TTHA			= 0x9a0,
    BENGALI_C_DDA			= 0x9a1,
    BENGALI_C_DDHA			= 0x9a2,
    BENGALI_C_NNA			= 0x9a3,
    BENGALI_C_TA			= 0x9a4,
    BENGALI_C_THA			= 0x9a5,
    BENGALI_C_DA			= 0x9a6,
    BENGALI_C_DHA			= 0x9a7,
    BENGALI_C_NA			= 0x9a8,

    BENGALI_C_PA			= 0x9aa,
    BENGALI_C_PHA			= 0x9ab,
    BENGALI_C_BA			= 0x9ac,
    BENGALI_C_BHA			= 0x9ad,
    BENGALI_C_MA			= 0x9ae,
    BENGALI_C_YA			= 0x9af,
    BENGALI_C_RA			= 0x9b0,

    BENGALI_C_LA			= 0x9b2,
    
    BENGALI_C_SHA			= 0x9b6,
    BENGALI_C_SSA			= 0x9b7,
    BENGALI_C_SA			= 0x9b8,
    BENGALI_C_HA			= 0x9b9,

    /* Various signs */
    BENGALI_S_NUKTA			= 0x9bc,
    BENGALI_S_AVAGRAH		= 0x9bd,

    /* Dependent vowel signs*/
    BENGALI_DV_AA			= 0x9be,
    BENGALI_DV_I			= 0x9bf,
    BENGALI_DV_II			= 0x9c0,
    BENGALI_DV_U			= 0x9c1,
	BENGALI_DV_UU			= 0x9c2,
	BENGALI_DV_VR			= 0x9c3,
	BENGALI_DV_VRR			= 0x9c4,
    
	BENGALI_DV_E			= 0x9c7,
    BENGALI_DV_AI			= 0x9c8,

	/* Two-part dependent vowel signs*/
    BENGALI_DV_O			= 0x9cb,
    BENGALI_DV_AU			= 0x9cc,

    /* Virama */
    BENGALI_S_HALANT		= 0x9cd,
    
	/* Additional consonant */
    BENGALI_AD_TA			= 0x9ce,

    /*Signs*/
    BENGALI_AD_AU			= 0x9d7,

    /*Additional consonant*/
	BENGALI_C_RRA			= 0x9dc,
	BENGALI_C_RHA			= 0x9dd,
	BENGALI_C_YYA			= 0x9df,

	/*Additional vowels for Sanskrit*/
	BENGALI_C_VRR			= 0x9e0,
    BENGALI_C_VLL			= 0x9e1,
	BENGALI_S_VRR			= 0x9e2,
    BENGALI_S_VLL			= 0x9e3,
       
    /* Digits */
    BENGALI_D_ZERO		    = 0x9e6,
    BENGALI_D_ONE			= 0x9e7,
    BENGALI_D_TWO			= 0x9e8,
    BENGALI_D_THREE			= 0x9e9,
    BENGALI_D_FOUR		    = 0x9ea,
    BENGALI_D_FIVE		    = 0x9eb,
    BENGALI_D_SIX			= 0x9ec,
    BENGALI_D_SEVEN			= 0x9ed,
    BENGALI_D_EIGHT			= 0x9ee,
    BENGALI_D_NINE		    = 0x9ef,

	/*Bengali-spacific additions*/
	BENGALI_C_MRA 	  		= 0x9f0,
	BENGALI_C_LRA 	  		= 0x9f1,
	BENGALI_OS_RUPEE  		= 0x9f2,
	BENGALI_C_RUPEE_SIGN	= 0x9f3,
	BENGALI_C_CURONE 	    = 0x9f4,
	BENGALI_C_CURTWO 	    = 0x9f5,
    BENGALI_C_CURTHREE	    = 0x9f6,
    BENGALI_C_CURFOUR	    = 0x9f7,
    BENGALI_OS_CURLESSDEN	= 0x9f8,
    BENGALI_OS_CURDENSIXTEEN= 0x9f9,
	BENGALI_OS_ISSHAR		= 0x9fa
}BengaliChar_e;

typedef enum
{
    /* Two conjunct Ligatutres */
    BENGALI_L_KA_KA			= 0xEA00,
    BENGALI_L_NGA_KA        = 0xEA01,
    BENGALI_L_LA_KA         = 0xEA02,
    BENGALI_L_SSA_KA        = 0xEA03,
    BENGALI_L_SA_KA         = 0xEA04,
    BENGALI_L_NGA_KHA       = 0xEA05,
    BENGALI_L_SA_KHA        = 0xEA06,
    BENGALI_L_NGA_GA        = 0xEA07,
    BENGALI_L_LA_GA         = 0xEA08,
    BENGALI_L_GA_GA         = 0xEA09,
    BENGALI_L_NGA_GHA       = 0xEA0A,
    BENGALI_L_NYA_CA        = 0xEA0B,
    BENGALI_L_DA_GA         = 0xEA0C,
    BENGALI_L_DA_GHA        = 0xEA0D,
    BENGALI_L_NYA_CHA       = 0xEA0E,
    BENGALI_L_JA_JA		    = 0xEA0F,
    BENGALI_L_NYA_JA        = 0xEA10,
    BENGALI_L_BA_JA         = 0xEA11,
    BENGALI_L_JA_JHA        = 0xEA12,
    BENGALI_L_NYA_JHA       = 0xEA13,
    BENGALI_L_JA_NYA        = 0xEA14,
    BENGALI_L_CA_NYA        = 0xEA15,
    BENGALI_L_KA_TTA        = 0xEA16,
    BENGALI_L_TTA_TTA       = 0xEA17,
    BENGALI_L_NNA_TTA       = 0xEA18,
    BENGALI_L_NA_TTA        = 0xEA19,
    BENGALI_L_PHA_TTA       = 0xEA1A,
    BENGALI_L_LA_TTA        = 0xEA1B,
    BENGALI_L_SSA_TTA       = 0xEA1C,
    BENGALI_L_SA_TTA        = 0xEA1D,
    BENGALI_L_RA_TTA        = 0xEA1E,
    BENGALI_L_NA_TTHA       = 0xEA1F,
    BENGALI_L_SSA_TTHA      = 0xEA20,
    BENGALI_L_DDA_DDA       = 0xEA21,
    BENGALI_L_NNA_DDA       = 0xEA22,
    BENGALI_L_NA_DDA        = 0xEA23,
    BENGALI_L_LA_DDA        = 0xEA24,
    BENGALI_L_NNA_DDHA      = 0xEA25,
    BENGALI_L_NA_DDHA       = 0xEA26,
    BENGALI_L_NNA_NNA       = 0xEA27,
    BENGALI_L_SSA_NNA       = 0xEA28,
    BENGALI_L_HA_NNA        = 0xEA29,
    BENGALI_L_KA_TA         = 0xEA2A,
    BENGALI_L_TA_TA         = 0xEA2B,
    BENGALI_L_LA_TA         = 0xEA2C,
    BENGALI_L_PA_TA		    = 0xEA2D,
    BENGALI_L_SHA_TA        = 0xEA2E,
    BENGALI_L_TA_THA        = 0xEA2F,
    BENGALI_L_NA_THA        = 0xEA30,
    BENGALI_L_SA_THA        = 0xEA31,
    BENGALI_L_DA_DA         = 0xEA32,
    BENGALI_L_NA_DA         = 0xEA33,
    BENGALI_L_BA_DA         = 0xEA34,
    BENGALI_L_GA_DHA        = 0xEA35,
    BENGALI_L_DA_DHA        = 0xEA36,
    BENGALI_L_NA_DHA        = 0xEA37,
    BENGALI_L_BA_DHA        = 0xEA38,
    BENGALI_L_LA_DHA        = 0xEA39,
    BENGALI_L_HA_NA         = 0xEA42,
    BENGALI_L_PA_PA         = 0xEA43,
    BENGALI_L_LA_PA         = 0xEA44,
    BENGALI_L_NA_DA_BA      = 0xEA45,
    BENGALI_L_MA_PHA        = 0xEA47,
    BENGALI_L_SSA_PHA       = 0xEA49,
    BENGALI_L_SA_PHA        = 0xEA4A,
    BENGALI_L_JA_RA         = 0xEA4D,
    BENGALI_L_KA_BA         = 0xEA4E,
    BENGALI_L_JA_BA         = 0xEA4F,

	BENGALI_L_KA_TTA_RA     = 0xEA51,
	BENGALI_L_GA_RA_DVU     = 0xEA52,
	BENGALI_L_GA_RA_DVUU    = 0xEA53,
	BENGALI_L_NNA_DDA_RA    = 0xEA54,
	BENGALI_L_TA_RA_DVU     = 0xEA55,
	BENGALI_L_TA_RA_DVUU    = 0xEA56,
	BENGALI_L_THA_RA_DVU    = 0xEA57,
	BENGALI_L_DA_DA_BA      = 0xEA58,
	BENGALI_L_DA_RA_DVU     = 0xEA59,
	
    BENGALI_L_HA_BA         = 0xEA5A,
    BENGALI_L_CA_BA         = 0xEA5B,
    BENGALI_L_CHA_BA        = 0xEA5C,
    BENGALI_L_MA_BHA        = 0xEA5D,
    BENGALI_L_DA_BHA        = 0xEA5E,
    BENGALI_L_KA_MA         = 0xEA5F,
    BENGALI_L_GA_MA         = 0xEA60,
    BENGALI_L_NGA_MA        = 0xEA61,
    BENGALI_L_TTA_MA        = 0xEA62,
    BENGALI_L_TA_MA         = 0xEA63,
    BENGALI_L_NA_MA         = 0xEA64,
    BENGALI_L_DDA_MA        = 0xEA65,
    BENGALI_L_LA_MA         = 0xEA66,
    BENGALI_L_DA_MA         = 0xEA67,
    BENGALI_L_DHA_MA        = 0xEA68,
    BENGALI_L_SA_MA         = 0xEA69,
    BENGALI_L_HA_MA         = 0xEA6A,
    BENGALI_L_PA_MA         = 0xEA6B,
    BENGALI_L_MA_MA         = 0xEA6C,
    BENGALI_L_SSA_MA        = 0xEA6D,
    BENGALI_L_NNA_MA        = 0xEA6E,
    BENGALI_L_SHA_MA        = 0xEA6F,
    BENGALI_L_DA_RA         = 0xEA70,
    BENGALI_L_DHA_RA        = 0xEA71,
    BENGALI_L_BHA_RA        = 0xEA72,
    BENGALI_L_HA_LA         = 0xEA74,
    BENGALI_L_BHA_LA        = 0xEA75,
	BENGALI_L_DA_RA_DVUU    = 0xEA76,
	BENGALI_L_DHA_RA_DVU    = 0xEA77,
    BENGALI_L_TTA_RA        = 0xEA78,
    BENGALI_L_HA_RA         = 0xEA7A,
	BENGALI_L_DHA_RA_DVUU   = 0xEA7B,
	BENGALI_L_NA_JA         = 0xEA7C, 
    BENGALI_L_MA_RA         = 0xEA7D,
	BENGALI_L_SSA_TTA_RA    = 0xEA7E,
	BENGALI_L_SA_TA_BA      = 0xEA7F,
	BENGALI_L_NA_TTA_RA     = 0xEA80,
	BENGALI_L_NA_TA_DVU     = 0xEA81,
	BENGALI_L_NA_DA_RA      = 0xEA82,
	BENGALI_L_NA_DA_RA_DVU  = 0xEA83,
	BENGALI_L_NA_DA_RA_DVUU = 0xEA84,
	BENGALI_C_BA_RA_DVU     = 0xEA85,
	BENGALI_C_H_MA_BA_RA    = 0xEA86,
    BENGALI_L_KA_SSA        = 0xEA88,
    BENGALI_L_KA_SA         = 0xEA89,
    BENGALI_L_NA_SA         = 0xEA8A,
    BENGALI_L_PA_SA         = 0xEA8B,
    /* Three conjunct Ligatutres */
    BENGALI_L_GA_ZWJ_DVU    = 0xEA8D,
    BENGALI_L_RA_ZWJ_DVU    = 0xEA8E,
    BENGALI_L_SHA_ZWJ_DVU   = 0xEA8F,
    BENGALI_L_HA_ZWJ_DVU    = 0xEA90,
    BENGALI_L_RA_ZWJ_DVUU   = 0xEA91,
    BENGALI_L_HA_ZWJ_DVVR   = 0xEA92,
    BENGALI_L_BHA_RA_DVU    = 0xEA93,
    BENGALI_L_BHA_RA_DVUU   = 0xEA94,
    BENGALI_L_KA_SSA_NNA    = 0xEA96,
    BENGALI_L_KA_TTA_BA     = 0xEA97,
    BENGALI_L_KA_SSA_MA     = 0xEA98,
    BENGALI_L_JA_JA_BA      = 0xEA99,
    BENGALI_L_SA_TA_RA      = 0xEA9A,
    BENGALI_L_SA_KA_RA      = 0xEA9B,
    BENGALI_L_SSA_KA_RA     = 0xEA9C,
    BENGALI_L_MA_BHA_RA     = 0xEA9D,
    BENGALI_L_NA_TA_BA      = 0xEA9E,
    BENGALI_L_NA_TA_RA      = 0xEA9F,
    
    BENGALI_L_DA_DHA_BA     = 0xEAA1,
    BENGALI_L_TA_TA_BA      = 0xEAA4,
    BENGALI_C_SHA_RA_DVU    = 0xEAA5,
    BENGALI_C_SHA_RA_DVUU   = 0xEAA6,
    BENGALI_L_JHA_RA        = 0xEAA7,
    BENGALI_L_JHA_BA        = 0xEAA8,
    BENGALI_L_NYA_BA        = 0xEAA9,
    BENGALI_L_UP_RA         = 0xEAAB,
    BENGALI_C_H_KHA         = 0xEAAC,
    BENGALI_C_H_TA0         = 0xEAAD,
    BENGALI_C_H_PA_2        = 0xEAB1,
    BENGALI_L_TA_BA         = 0xEAB2,
    BENGALI_L_GHA_BA        = 0xEAB3,
    BENGALI_L_BHA_BA        = 0xEAB4,
	
	BENGALI_C_H_NGA_2       = 0xEAB5,   
	    
    BENGALI_C_H_SHA         = 0xEAB6,
    BENGALI_C_H_NA	        = 0xEAB7,
    BENGALI_C_H_GA_0	    = 0xEAB8, // typical  form of  BENGALI_C_GA+BENGALI_S_HALANT
    BENGALI_C_H_PA	        = 0xEAB9,
    BENGALI_C_H_NNA	        = 0xEABA,
    BENGALI_C_H_LA	        = 0xEABB,
    BENGALI_C_H_SA	        = 0xEABC,
    BENGALI_C_H_SSA	        = 0xEABD,
    BENGALI_C_H_KA          = 0xEABE,
    BENGALI_C_H_NGA         = 0xEABF,
    BENGALI_C_H_CA          = 0xEAC0,
    BENGALI_C_H_JA	        = 0xEAC1,
    BENGALI_C_H_JHA  	    = 0xEAC2,
    BENGALI_C_H_TTA         = 0xEAC3,
    BENGALI_C_H_TTHA        = 0xEAC6,
	BENGALI_C_H_DDA         = 0xEAC7,
	BENGALI_C_H_DDHA        = 0xEAC8,
	BENGALI_C_H_TA          = 0xEAC9,
	BENGALI_C_H_THA         = 0xEACA,
	BENGALI_C_H_DA          = 0xEACB,
	BENGALI_C_H_DHA         = 0xEACC,
	BENGALI_C_H_PHA         = 0xEACD,
	BENGALI_C_H_BA          = 0xEACE,
	BENGALI_C_H_BHA         = 0xEACF,
	BENGALI_C_H_MA          = 0xEAD0,
	BENGALI_C_H_GA_1        = 0xEAD1, // special form of BENGALI_C_GA+BENGALI_S_HALANT
    BENGALI_L_DA_BHA_RA     = 0xEAD2,
	BENGALI_L_BA_DA_RA 		= 0xEAD3,
	BENGALI_C_H_GHA         = 0xEAD4,

	BENGALI_L_NA_DHA_RA     = 0xEAD5,
	BENGALI_L_NA_DDA_RA     = 0xEAD6,
	BENGALI_L_LA_DDA_RA     = 0xEAD7,
	BENGALI_L_SA_TTA_RA     = 0xEAD8,
	
	BENGALI_C_HA_YA         = 0xEAD9,
	BENGALI_C_HA_BA         = 0xEADA,
	BENGALI_C_HA_RA         = 0xEADB,
	BENGALI_C_HA_NA         = 0xEADC,
	BENGALI_C_HA_LA         = 0xEADD,
	BENGALI_C_HA_TA         = 0xEADE,

    BENGALI_L_KA_SSA_RA     = 0xEADF,

	BENGALI_L_KA_SSA_BA     = 0xEAE0,
	BENGALI_L_LA_PHA        = 0xEAE1,
	BENGALI_L_MA_PHA_RA 	= 0xEAE2,
	BENGALI_L_LA_PHA_RA     = 0xEAE3,
	BENGALI_L_SA_PA_LA_DV_U = 0xEAE4,
	BENGALI_L_SA_PA_LA_DV_UU = 0xEAE5,
	BENGALI_L_SA_PHA_RA     = 0xEAE6,
    BENGALI_DV_E2           = 0xEAE7,  // Init form of BENGALI_DV_E
    BENGALI_DV_AI_2         = 0xEAE8,  // Init form of BENGALI_DV_AI
    BENGALI_L_SA_TTA_LA     = 0xEAE9,
	BENGALI_C_HA_BA_2       = 0xEAEA, // short BENGALI_C_HA_BA for constant with center "T"
	BENGALI_C_HA_RA_2       = 0xEAEB, // short BENGALI_C_HA_RA for constant with center "T"
	BENGALI_C_HA_NA_2       = 0xEAEC, // short BENGALI_C_HA_NA for constant with center "T"
	BENGALI_C_HA_LA_2       = 0xEAED,  // short BENGALI_C_HA_LA for constant with center "T"
    BENGALI_C_HA_BA_3       = 0xEAEE,
    BENGALI_L_GA_RA         = 0xEAEF,
    BENGALI_C_CHA_RA        = 0xEAF0,
    BENGALI_L_BA_RA         = 0xEAF1,
    BENGALI_L_DDHA_BA       = 0xEAF2,
    BENGALI_L_PA_RA         = 0xEAF3,
	BENGALI_L_NGA_KA_RA     = 0xEAF4,
    BENGALI_L_KA_TA_BA      = 0xEAF5,
    BENGALI_L_KHA_BA        = 0xEAF6,
    BENGALI_L_SSA_BA        = 0xEAF7,
	BENGALI_L_NNA_TTHA      = 0xEAF8,
    BENGALI_L_NGA_BA        = 0xEAF9,
    BENGALI_L_TTHA_BA       = 0xEAFA,
    BENGALI_L_PHA_BA        = 0xEAFB,
    BENGALI_L_RRA_BA        = 0xEAFC,
   BENGALI_C_SA_TA_DV        = 0xEAFD,
    BENGALI_C_BA_2 = 0xEAFE, 
    BENGALI_L_YA_BA         = 0xEAFF
}BengaliLigatures_e;

u16 FontBengaliGetLigatedCluster( const u16 *pu16Txt, u32 u32InLen, u16 *pu16Cluster, u16 u16BufferSize, u16 u16ClusterSize, u16 *pu16ConsumedCount, u16 *pu16SeqInCluster);

u16 FontBengaliGetYAPHALAAClusterSize( const u16 *pu16Txt, u32 u32InLen, u16 u16ConsumedCount);
#endif //__INDIC_FONT__
#endif //__BENGALI_FONT__
#endif /* __MAE_FONT_BENGALI_H__ */
