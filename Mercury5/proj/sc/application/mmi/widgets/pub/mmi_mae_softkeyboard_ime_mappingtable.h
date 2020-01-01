/**
 * @file    mae_softkeyboard_ime_mappingtable.h
 * @brief   The document describes mapping table of SoftKeyboard Widget
 * @author  christoph.kuo@mstarsemi.com
 *
 * @version $Id: mae_softkeyboard_ime_mappingtable.h 35926 2009-07-16 13:31:03Z alison.chen $
 */
 
// for current ime
#ifndef __MMI_MAE_SOFTKEYBOARD_IME_MAPPINGTABLE_H__
#define __MMI_MAE_SOFTKEYBOARD_IME_MAPPINGTABLE_H__

#ifdef __TOUCH_SCREEN_MMI__


//Numeric
#define MAE_SKB_NUMERIC_DECIMAL_POINT    0x002E
#define MAE_SKB_NUMERIC_0                0x0030
#define MAE_SKB_NUMERIC_1                0x0031
#define MAE_SKB_NUMERIC_2                0x0032
#define MAE_SKB_NUMERIC_3                0x0033
#define MAE_SKB_NUMERIC_4                0x0034
#define MAE_SKB_NUMERIC_5                0x0035
#define MAE_SKB_NUMERIC_6                0x0036
#define MAE_SKB_NUMERIC_7                0x0037
#define MAE_SKB_NUMERIC_8                0x0038
#define MAE_SKB_NUMERIC_9                0x0039

#define MAE_SKB_DIALING_PAUSE						 0x0050
#define MAE_SKB_DIALING_STAR             0x002A
#define MAE_SKB_DIALING_POUND            0x0023
#define MAE_SKB_DIALING_WILD             0x003F
#define MAE_SKB_DIALING_INTERNATIONAL    0x002B


/******************
Thai Start
*******************/
#define MAE_SKB_THAI_KO_KAI	0x0E01
#define MAE_SKB_THAI_KHO_KHAI	0x0E02
#define MAE_SKB_THAI_KHO_KHUAT	0x0E03
#define MAE_SKB_THAI_KHO_KHWAI	0x0E04
#define MAE_SKB_THAI_KHO_KHON	0x0E05
#define MAE_SKB_THAI_KHO_RAKHANG	0x0E06
#define MAE_SKB_THAI_NGO_NGU	0x0E07
#define MAE_SKB_THAI_CHO_CHAN	0x0E08
#define MAE_SKB_THAI_CHO_CHING	0x0E09
#define MAE_SKB_THAI_CHO_CHANG	0x0E0A
#define MAE_SKB_THAI_SO_SO	0x0E0B
#define MAE_SKB_THAI_CHO_CHOE	0x0E0C
#define MAE_SKB_THAI_YO_YING	0x0E0D
#define MAE_SKB_THAI_DO_CHADA	0x0E0E
#define MAE_SKB_THAI_TO_PATAK	0x0E0F
#define MAE_SKB_THAI_THO_THAN	0x0E10
#define MAE_SKB_THAI_THO_NANGMONTHO	0x0E11
#define MAE_SKB_THAI_THO_PHUTHAO	0x0E12
#define MAE_SKB_THAI_NO_NEN	0x0E13
#define MAE_SKB_THAI_DO_DEK	0x0E14
#define MAE_SKB_THAI_TO_TAO	0x0E15
#define MAE_SKB_THAI_THO_THUNG	0x0E16
#define MAE_SKB_THAI_THO_THAHAN	0x0E17
#define MAE_SKB_THAI_THO_THONG	0x0E18
#define MAE_SKB_THAI_NO_NU	0x0E19
#define MAE_SKB_THAI_BO_BAIMAI	0x0E1A
#define MAE_SKB_THAI_PO_PLA	0x0E1B
#define MAE_SKB_THAI_PHO_PHUNG	0x0E1C
#define MAE_SKB_THAI_FO_FA	0x0E1D
#define MAE_SKB_THAI_PHO_PHAN	0x0E1E
#define MAE_SKB_THAI_FO_FAN	0x0E1F
#define MAE_SKB_THAI_PHO_SAMPHAO	0x0E20
#define MAE_SKB_THAI_MO_MA	0x0E21
#define MAE_SKB_THAI_YO_YAK	0x0E22
#define MAE_SKB_THAI_RO_RUA	0x0E23
#define MAE_SKB_THAI_RU	0x0E24
#define MAE_SKB_THAI_LO_LING	0x0E25
#define MAE_SKB_THAI_LU	0x0E26
#define MAE_SKB_THAI_WO_WAEN	0x0E27
#define MAE_SKB_THAI_SO_SALA	0x0E28
#define MAE_SKB_THAI_SO_RUSI	0x0E29
#define MAE_SKB_THAI_SO_SUA	0x0E2A
#define MAE_SKB_THAI_HO_HIP	0x0E2B
#define MAE_SKB_THAI_LO_CHULA	0x0E2C
#define MAE_SKB_THAI_O_ANG	0x0E2D
#define MAE_SKB_THAI_HO_NOKHUK	0x0E2E
#define MAE_SKB_THAI_PAIYANNOI	0x0E2F
#define MAE_SKB_THAI_SARA_A	0x0E30
#define MAE_SKB_THAI_MAI_HAN_AKAT	0x0E31
#define MAE_SKB_THAI_SARA_AA	0x0E32
#define MAE_SKB_THAI_SARA_AM	0x0E33
#define MAE_SKB_THAI_SARA_I	0x0E34
#define MAE_SKB_THAI_SARA_II	0x0E35
#define MAE_SKB_THAI_SARA_UE	0x0E36
#define MAE_SKB_THAI_SARA_UEE	0x0E37
#define MAE_SKB_THAI_SARA_U	0x0E38
#define MAE_SKB_THAI_SARA_UU	0x0E39
#define MAE_SKB_THAI_PHINTHU	0x0E3A
#define MAE_SKB_THAI_CURRENCY_SYMBOL_BAHT	0x0E3F
#define MAE_SKB_THAI_SARA_E	0x0E40
#define MAE_SKB_THAI_SARA_AE	0x0E41
#define MAE_SKB_THAI_SARA_O	0x0E42
#define MAE_SKB_THAI_SARA_AI_MAIMUAN	0x0E43
#define MAE_SKB_THAI_SARA_AI_MAIMALAI	0x0E44
#define MAE_SKB_THAI_LAKKHANGYAO	0x0E45
#define MAE_SKB_THAI_MAIYAMOK	0x0E46
#define MAE_SKB_THAI_MAITAIKHU	0x0E47
#define MAE_SKB_THAI_MAI_EK	0x0E48
#define MAE_SKB_THAI_MAI_THO	0x0E49
#define MAE_SKB_THAI_MAI_TRI	0x0E4A
#define MAE_SKB_THAI_MAI_CHATTAWA	0x0E4B
#define MAE_SKB_THAI_THANTHAKHAT	0x0E4C
#define MAE_SKB_THAI_NIKHAHIT	0x0E4D
#define MAE_SKB_THAI_YAMAKKAN	0x0E4E
#define MAE_SKB_THAI_FONGMAN	0x0E4F
#define MAE_SKB_THAI_DIGIT_ZERO	0x0E50
#define MAE_SKB_THAI_DIGIT_ONE	0x0E51
#define MAE_SKB_THAI_DIGIT_TWO	0x0E52
#define MAE_SKB_THAI_DIGIT_THREE	0x0E53
#define MAE_SKB_THAI_DIGIT_FOUR	0x0E54
#define MAE_SKB_THAI_DIGIT_FIVE	0x0E55
#define MAE_SKB_THAI_DIGIT_SIX	0x0E56
#define MAE_SKB_THAI_DIGIT_SEVEN	0x0E57
#define MAE_SKB_THAI_DIGIT_EIGHT	0x0E58
#define MAE_SKB_THAI_DIGIT_NINE	0x0E59
#define MAE_SKB_THAI_ANGKHANKHU	0x0E5A
#define MAE_SKB_THAI_KHOMUT	0x0E5B
/******************
Thai End
*******************/

/******************
Arabic Start
*******************/
#define MAE_SKB_ARABIC_DEC_POINT	0x066B
#define MAE_SKB_ARABIC_THOU_SEP		0x066C
#define MAE_SKB_ARABIC_QUE_MARK		0x061F
#define MAE_SKB_ARABIC_ZE			0x0632
#define MAE_SKB_ARABIC_ZAL			0x0630
#define MAE_SKB_ARABIC_DAL			0x062F
#define MAE_SKB_ARABIC_ZA			0x0638
#define MAE_SKB_ARABIC_TA			0x0637
#define MAE_SKB_ARABIC_JIM			0x062C
#define MAE_SKB_ARABIC_FULL_STOP	0x06D4
#define MAE_SKB_ARABIC_ZAD			0x0636
#define MAE_SKB_ARABIC_SAD			0x0635
#define MAE_SKB_ARABIC_SE			0x062B
#define MAE_SKB_ARABIC_QAF			0x0642
#define MAE_SKB_ARABIC_FE			0x0641
#define MAE_SKB_ARABIC_GHAIN		0x063A
#define MAE_SKB_ARABIC_AIN			0x0639
#define MAE_SKB_ARABIC_HE			0x0647
#define MAE_SKB_ARABIC_GLOTTAL_STOP	0x062E
#define MAE_SKB_ARABIC_HEH			0x062D
#define MAE_SKB_ARABIC_COMMA		0x060C
#define MAE_SKB_ARABIC_SHIN			0x0634
#define MAE_SKB_ARABIC_SIN			0x0633
#define MAE_SKB_ARABIC_LII			0x064A
#define MAE_SKB_ARABIC_BI			0x0628
#define MAE_SKB_ARABIC_LAM			0x0644
#define MAE_SKB_ARABIC_ALEF			0x0627
#define MAE_SKB_ARABIC_T			0x062A
#define MAE_SKB_ARABIC_NUN			0x0646
#define MAE_SKB_ARABIC_MIM			0x0645
#define MAE_SKB_ARABIC_KAF			0x0643
#define MAE_SKB_ARABIC_SEMICOLON	0x061B
#define MAE_SKB_ARABIC_IPA			0x0626
#define MAE_SKB_ARABIC_HAMZEH		0x0621
#define MAE_SKB_ARABIC_P			0x0624
#define MAE_SKB_ARABIC_RE			0x0631
#define MAE_SKB_ARABIC_YA			0x0649
#define MAE_SKB_ARABIC_BA			0x0629
#define MAE_SKB_ARABIC_WA			0x0648
/******************
Arabic End
*******************/


/******************
Hindi Start
*******************/
#define MAE_SKB_HINDI_S_CHANDRA		0x0901
#define MAE_SKB_HINDI_S_BINDU		0x0902
#define MAE_SKB_HINDI_S_VISARGA		0x0903
#define MAE_SKB_HINDI_NIV_A     	0x0904
#define MAE_SKB_HINDI_IV_A			0x0905
#define MAE_SKB_HINDI_IV_AA			0x0906
#define MAE_SKB_HINDI_IV_I			0x0907
#define MAE_SKB_HINDI_IV_II			0x0908
#define MAE_SKB_HINDI_IV_U			0x0909
#define MAE_SKB_HINDI_IV_UU			0x090A
#define MAE_SKB_HINDI_IV_R			0x090B
#define MAE_SKB_HINDI_NIV_L			0x090C
#define MAE_SKB_HINDI_NIV_CE		0x090D
#define MAE_SKB_HINDI_NIV_SE		0x090E
#define MAE_SKB_HINDI_IV_E			0x090F
#define MAE_SKB_HINDI_IV_AI			0x0910
#define MAE_SKB_HINDI_NIV_CO		0x0911
#define MAE_SKB_HINDI_NIV_SO		0x0912
#define MAE_SKB_HINDI_IV_O			0x0913
#define MAE_SKB_HINDI_IV_AU			0x0914
#define MAE_SKB_HINDI_C_KA			0x0915
#define MAE_SKB_HINDI_C_KHA			0x0916
#define MAE_SKB_HINDI_C_GA			0x0917
#define MAE_SKB_HINDI_C_GHA			0x0918
#define MAE_SKB_HINDI_C_NGA			0x0919
#define MAE_SKB_HINDI_C_CHA			0x091A
#define MAE_SKB_HINDI_C_CHHA		0x091B
#define MAE_SKB_HINDI_C_JA			0x091C
#define MAE_SKB_HINDI_C_JHA			0x091D
#define MAE_SKB_HINDI_C_NYA         0x091E
#define MAE_SKB_HINDI_C_TTA			0x091F
#define MAE_SKB_HINDI_C_TTHA		0x0920
#define MAE_SKB_HINDI_C_DDA			0x0921
#define MAE_SKB_HINDI_C_DDHA		0x0922
#define MAE_SKB_HINDI_C_NNA			0x0923
#define MAE_SKB_HINDI_C_TA			0x0924
#define MAE_SKB_HINDI_C_THA			0x0925
#define MAE_SKB_HINDI_C_DA			0x0926
#define MAE_SKB_HINDI_C_DHA			0x0927
#define MAE_SKB_HINDI_C_NA			0x0928
#define MAE_SKB_HINDI_C_NNNA		0x0929
#define MAE_SKB_HINDI_C_PA			0x092A
#define MAE_SKB_HINDI_C_PHA			0x092B
#define MAE_SKB_HINDI_C_BA			0x092C
#define MAE_SKB_HINDI_C_BHA			0x092D
#define MAE_SKB_HINDI_C_MA			0x092E
#define MAE_SKB_HINDI_C_YA			0x092F
#define MAE_SKB_HINDI_C_RA			0x0930
#define MAE_SKB_HINDI_C_RRA			0x0931
#define MAE_SKB_HINDI_C_LA			0x0932
#define MAE_SKB_HINDI_C_LLA			0x0933
#define MAE_SKB_HINDI_C_LLLA		0x0934
#define MAE_SKB_HINDI_C_VA			0x0935
#define MAE_SKB_HINDI_C_SHA			0x0936
#define MAE_SKB_HINDI_C_SSA			0x0937
#define MAE_SKB_HINDI_C_SA			0x0938
#define MAE_SKB_HINDI_C_HA			0x0939
#define MAE_SKB_HINDI_S_NUKTA		0x093C
#define MAE_SKB_HINDI_DV_AA			0x093E
#define MAE_SKB_HINDI_DV_I			0x093F
#define MAE_SKB_HINDI_DV_II			0x0940
#define MAE_SKB_HINDI_DV_U			0x0941
#define MAE_SKB_HINDI_DV_UU			0x0942
#define MAE_SKB_HINDI_DV_R			0x0943
#define MAE_SKB_HINDI_NDV_RR		0x0944
#define MAE_SKB_HINDI_DV_CE			0x0945
#define MAE_SKB_HINDI_NDV_E			0x0946
#define MAE_SKB_HINDI_DV_E			0x0947
#define MAE_SKB_HINDI_DV_AI			0x0948
#define MAE_SKB_HINDI_NDV_CO		0x0949
#define MAE_SKB_HINDI_NDV_O			0x094A
#define MAE_SKB_HINDI_DV_O			0x094B
#define MAE_SKB_HINDI_DV_AU			0x094C
#define MAE_SKB_HINDI_S_HALANT		0x094D
#define MAE_SKB_HINDI_AC_YYA		0x095F
#define MAE_SKB_HINDI_NG_D			0x0964

#define MAE_SKB_HINDI_D_ZERO		0x0966
#define MAE_SKB_HINDI_D_ONE			0x0967
#define MAE_SKB_HINDI_D_TWO			0x0968
#define MAE_SKB_HINDI_D_THREE		0x0969
#define MAE_SKB_HINDI_D_FOUR		0x096A
#define MAE_SKB_HINDI_D_FIVE		0x096B
#define MAE_SKB_HINDI_D_SIX			0x096C
#define MAE_SKB_HINDI_D_SEVEN		0x096D
#define MAE_SKB_HINDI_D_EIGHT		0x096E
#define MAE_SKB_HINDI_D_NINE		0x096F
#define MAE_SKB_HINDI_S_RUPEE   	0x20B9

#define MAE_SKB_HINDI_L_GYA 		0xE901
#define MAE_SKB_HINDI_L_TRA			0xE903
#define MAE_SKB_HINDI_L_KSHA 		0xE900
#define MAE_SKB_HINDI_L_SHRA 		0xE905

/******************
Hindi End
*******************/

/******************
Urdu Start
*******************/
//page 1
#define MAE_SKB_URDU_ARABIC_LETTER_TAHTA							0x0637
#define MAE_SKB_URDU_ARABIC_LETTER_SAD								0x0635
#define MAE_SKB_URDU_ARABIC_LETTER_HEH_DOACHASHMEE	0x06BE
#define MAE_SKB_URDU_ARABIC_LETTER_DAL								0x062F
#define MAE_SKB_URDU_ARABIC_LETTER_TTEH							0x0679
#define MAE_SKB_URDU_ARABIC_LETTER_PEH	 							0x067E
#define MAE_SKB_URDU_ARABIC_LETTER_TEH_MARBUTA_GOAL	0x06C3
#define MAE_SKB_URDU_ARABIC_LETTER_BEH								0x0628
#define MAE_SKB_URDU_ARABIC_LETTER_JEEM							0x062C
#define MAE_SKB_URDU_ARABIC_LETTER_HAH								0x062D
#define MAE_SKB_URDU_ARABIC_LETTER_MEEM							0x0645
#define MAE_SKB_URDU_ARABIC_LETTER_WAW							0x0648
#define MAE_SKB_URDU_ARABIC_LETTER_REH								0x0631
#define MAE_SKB_URDU_ARABIC_LETTER_NOON							0x0646
#define MAE_SKB_URDU_ARABIC_LETTER_LAM								0x0644
#define MAE_SKB_URDU_ARABIC_LETTER_HEH_GOAL				 	0x06C1
#define MAE_SKB_URDU_ARABIC_LETTER_ALEF							0x0627
#define MAE_SKB_URDU_ARABIC_LETTER_KEHEH							0x06A9
#define MAE_SKB_URDU_ARABIC_LETTER_FARSI_YEH					0x06CC
#define MAE_SKB_URDU_ARABIC_LETTER_QAF								0x0642
#define MAE_SKB_URDU_ARABIC_LETTER_FEH								0x0641
#define MAE_SKB_URDU_ARABIC_LETTER_YEH_BARREE				0x06D2
#define MAE_SKB_URDU_ARABIC_LETTER_SEEN							0x0633
#define MAE_SKB_URDU_ARABIC_LETTER_SHEEN							0x0634
#define MAE_SKB_URDU_ARABIC_LETTER_GHAIN							0x063A
#define MAE_SKB_URDU_ARABIC_LETTER_AIN								0x0639
//page 2
#define MAE_SKB_URDU_ARABIC_LETTER_ZAH							0x0638
#define MAE_SKB_URDU_ARABIC_LETTER_DAD							0x0636
#define MAE_SKB_URDU_ARABIC_LETTER_THAL	                        0x0630
#define MAE_SKB_URDU_ARABIC_LETTER_DDAL							0x0688
#define MAE_SKB_URDU_ARABIC_LETTER_THEH							0x062B
#define MAE_SKB_URDU_ARABIC_TATWEEL								0x0640
#define MAE_SKB_URDU_ARABIC_LETTER_TCHEH						0x0686
#define MAE_SKB_URDU_ARABIC_LETTER_KHAH							0x062E
#define MAE_SKB_URDU_ARABIC_LETTER_JEH							0x0698
#define MAE_SKB_URDU_ARABIC_LETTER_ZAIN							0x0632
#define MAE_SKB_URDU_ARABIC_LETTER_RREH							0x0691
#define MAE_SKB_URDU_ARABIC_LETTER_NOON_GHUNNA					0x06BA
#define MAE_SKB_URDU_ARABIC_LETTER_HEH_GOAL_WITH_HAMZA_ABOVE	0x06C2
#define MAE_SKB_URDU_ARABIC_LETTER_HAMZA				 	    0x0621
#define MAE_SKB_URDU_ARABIC_LETTER_ALEF_WITH_MADDA_ABOVE		0x0622
#define MAE_SKB_URDU_ARABIC_LETTER_GAF							0x06AF
#define MAE_SKB_URDU_ARABIC_LETTER_YEH					        0x064A
#define MAE_SKB_URDU_ARABIC_LETTER_YEH_BARREE_WITH_HAMZA_ABOVE	0x06D3
#define MAE_SKB_URDU_ARABIC_LETTER_WAW_WITH_HAMZA_ABOVE			0x0624
#define MAE_SKB_URDU_ARABIC_LETTER_YEH_WITH_HAMZA_ABOVE			0x0626
#define MAE_SKB_URDU_ARABIC_LETTER_TEH				            0x062A
/******************
Urdu End
*******************/

#define MAE_SKB_EN_A_UC            0x0041
#define MAE_SKB_EN_B_UC            0x0042
#define MAE_SKB_EN_C_UC            0x0043
#define MAE_SKB_EN_D_UC            0x0044
#define MAE_SKB_EN_E_UC            0x0045
#define MAE_SKB_EN_F_UC            0x0046
#define MAE_SKB_EN_G_UC            0x0047
#define MAE_SKB_EN_H_UC            0x0048
#define MAE_SKB_EN_I_UC            0x0049
#define MAE_SKB_EN_J_UC            0x004A
#define MAE_SKB_EN_K_UC            0x004B
#define MAE_SKB_EN_L_UC            0x004C
#define MAE_SKB_EN_M_UC            0x004D
#define MAE_SKB_EN_N_UC            0x004E
#define MAE_SKB_EN_O_UC            0x004F
#define MAE_SKB_EN_P_UC            0x0050
#define MAE_SKB_EN_Q_UC            0x0051
#define MAE_SKB_EN_R_UC            0x0052
#define MAE_SKB_EN_S_UC            0x0053
#define MAE_SKB_EN_T_UC            0x0054
#define MAE_SKB_EN_U_UC            0x0055
#define MAE_SKB_EN_V_UC            0x0056
#define MAE_SKB_EN_W_UC            0x0057
#define MAE_SKB_EN_X_UC            0x0058
#define MAE_SKB_EN_Y_UC            0x0059
#define MAE_SKB_EN_Z_UC            0x005A


/******************
Russian Capital Start
*******************/
#define MAE_SKB_LT_CYRILLIC_A_UC	0x0410
#define MAE_SKB_LT_CYRILLIC_BE_UC	0x0411
#define MAE_SKB_LT_CYRILLIC_VE_UC	0x0412
#define MAE_SKB_LT_CYRILLIC_GHE_UC	0x0413
#define MAE_SKB_LT_CYRILLIC_DE_UC	0x0414
#define MAE_SKB_LT_CYRILLIC_IE_UC	0x0415
#define MAE_SKB_LT_CYRILLIC_ZHE_UC	0x0416
#define MAE_SKB_LT_CYRILLIC_ZE_UC	0x0417
#define MAE_SKB_LT_CYRILLIC_I_UC	0x0418
#define MAE_SKB_LT_CYRILLIC_SHORT_I_UC	0x0419
#define MAE_SKB_LT_CYRILLIC_KA_UC	0x041A
#define MAE_SKB_LT_CYRILLIC_EL_UC	0x041B
#define MAE_SKB_LT_CYRILLIC_EM_UC	0x041C
#define MAE_SKB_LT_CYRILLIC_EN_UC	0x041D
#define MAE_SKB_LT_CYRILLIC_O_UC	0x041E
#define MAE_SKB_LT_CYRILLIC_PE_UC	0x041F
#define MAE_SKB_LT_CYRILLIC_ER_UC	0x0420
#define MAE_SKB_LT_CYRILLIC_ES_UC	0x0421
#define MAE_SKB_LT_CYRILLIC_TE_UC	0x0422
#define MAE_SKB_LT_CYRILLIC_U_UC	0x0423
#define MAE_SKB_LT_CYRILLIC_EF_UC	0x0424
#define MAE_SKB_LT_CYRILLIC_HA_UC	0x0425
#define MAE_SKB_LT_CYRILLIC_TSE_UC	0x0426
#define MAE_SKB_LT_CYRILLIC_CHE_UC	0x0427
#define MAE_SKB_LT_CYRILLIC_SHA_UC	0x0428
#define MAE_SKB_LT_CYRILLIC_SHCHA_UC	0x0429
#define MAE_SKB_LT_CYRILLIC_HARD_SIGN_UC	0x042A
#define MAE_SKB_LT_CYRILLIC_YERU_UC	0x042B
#define MAE_SKB_LT_CYRILLIC_SOFT_SIGN_UC	0x042C
#define MAE_SKB_LT_CYRILLIC_E_UC	0x042D
#define MAE_SKB_LT_CYRILLIC_YU_UC	0x042E
#define MAE_SKB_LT_CYRILLIC_YA_UC	0x042F
/******************
Russian Capital End
*******************/

/******************
Spanish Capital Start
*******************/
#define MAE_SKB_LT_A_ACUTE_UC      0x00C1
#define MAE_SKB_LT_E_ACUTE_UC      0x00C9
#define MAE_SKB_LT_I_ACUTE_UC      0x00CD
#define MAE_SKB_LT_O_ACUTE_UC      0x00D3
#define MAE_SKB_LT_U_ACUTE_UC      0x00DA
#define MAE_SKB_LT_U_DIAERESIS_UC  0x00DC
#define MAE_SKB_LT_N_TILDE_UC      0x00D1
#define MAE_SKB_LT_C_CEDILLA_UC    0x00C7
/******************
Spanish Capital End
*******************/

/******************
French Capital Start
*******************/
#define MAE_SKB_LT_A_GRAVE_UC	0X00C0
#define MAE_SKB_LT_A_CIRCUMFLEX_UC	0X00C2
#define MAE_SKB_LT_AE_LIGATURE_UC	0X00C6
#define MAE_SKB_LT_E_GRAVE_UC	0X00C8
//#define MAE_SKB_LT_E_ACUTE_UC	0X00C9 (See Spanish)
#define MAE_SKB_LT_E_CIRCUMFLEX_UC	0X00CA
#define MAE_SKB_LT_E_DIAERESIS_UC	0X00CB
#define MAE_SKB_LT_I_CIRCUMFLEX_UC	0X00CE
#define MAE_SKB_LT_I_DIAERESIS_UC	0X00CF
#define MAE_SKB_LT_O_CIRCUMFLEX_UC	0X00D4
#define MAE_SKB_LT_OE_LIGATURE_UC	0X0152
#define MAE_SKB_LT_U_GRAVE_UC	0X00D9
#define MAE_SKB_LT_U_CIRCUMFLEX_UC	0X00DB
//#define MAE_SKB_LT_U_DIAERESIS_UC	0X00DC (See Spanish)
#define MAE_SKB_LT_Y_DIAERESIS_UC	0X0178
//#define MAE_SKB_LT_C_CEDILLA_UC	0X00C7 (See Spanish)
/******************
French Capital End
*******************/

/******************
Turkish Capital Start
*******************/
#define MAE_SKB_LT_S_CEDILLA_UC	    0x015E
#define MAE_SKB_LT_G_BREVE_UC	    0x011E
#define MAE_SKB_LT_O_DIAERESIS_UC   0x00D6

/******************
Turkish Capital End
*******************/

/******************
Portuguese Capital Start
*******************/
//#define MAE_SKB_LT_A_GRAVE_UC	0x00C0 (Please see above)
//#define MAE_SKB_LT_A_ACUTE_UC	0x00C1 (Please see above)
//#define MAE_SKB_LT_A_CIRCUMFLEX_UC	0x00C2 (Please see above)
#define MAE_SKB_LT_A_TILDE_UC	0x00C3 
//#define MAE_SKB_LT_E_ACUTE_UC	0x00C9 (Please see above)
//#define MAE_SKB_LT_E_CIRCUMFLEX_UC	0x00CA (Please see above)
//#define MAE_SKB_LT_I_ACUTE_UC	0x00CD (Please see above)
#define MAE_SKB_LT_O_GRAVE_UC	0x00D2
//#define MAE_SKB_LT_O_ACUTE_UC	0x00D3 (Please see above)
//#define MAE_SKB_LT_O_CIRCUMFLEX_UC	0x00D4 (Please see above)
#define MAE_SKB_LT_O_TILDE_UC	0x00D5
//#define MAE_SKB_LT_U_ACUTE_UC	0x00DA (Please see above)
//#define MAE_SKB_LT_U_DIAERESIS_UC	0x00DC (Please see above)
//#define MAE_SKB_LT_C_CEDILLA_UC	0x00C7 (Please see above)
/******************
Portuguese Capital End
*******************/


/******************
Vietnamese Capital Start
*******************/
//Modified A (total 17)
//#define MAE_SKB_LT_A_GRAVE_UC      0x00C0 (Please see above)
//#define MAE_SKB_LT_A_ACUTE_UC      0x00C1  (Please see above)
#define MAE_SKB_LT_A_HOOK_ABOVE_UC      0x1EA2
//#define MAE_SKB_LT_A_TILDE_UC      0x00C3 (Please see above)
#define MAE_SKB_LT_A_DOT_BELOW_UC      0x1EA0
#define MAE_SKB_LT_A_BREVE_UC      0x0102
#define MAE_SKB_LT_A_BREVE_AND_GRAVE_UC      0x1EB0
#define MAE_SKB_LT_A_BREVE_AND_ACUTE_UC      0x1EAE
#define MAE_SKB_LT_A_BREVE_AND_HOOK_ABOVE_UC      0x1EB2
#define MAE_SKB_LT_A_BREVE_AND_TILDE_UC      0x1EB4
#define MAE_SKB_LT_A_BREVE_AND_DOT_BELOW_UC      0x1EB6
//#define MAE_SKB_LT_A_CIRCUMFLEX_UC      0x00C2 (Please see above)
#define MAE_SKB_LT_A_CIRCUMFLEX_AND_GRAVE_UC      0x1EA6
#define MAE_SKB_LT_A_CIRCUMFLEX_AND_ACUTE_UC      0x1EA4
#define MAE_SKB_LT_A_CIRCUMFLEX_AND_HOOK_ABOVE_UC      0x1EA8
#define MAE_SKB_LT_A_CIRCUMFLEX_AND_TILDE_UC      0x1EAA
#define MAE_SKB_LT_A_CIRCUMFLEX_AND_DOT_BELOW_UC      0x1EAC

//Modified D (total 1)
#define MAE_SKB_LT_D_STROKE_UC      0x0110

//Modified E (total 11)
//#define MAE_SKB_LT_E_GRAVE_UC      0x00C8 (Please see above)
//#define MAE_SKB_LT_E_ACUTE_UC      0x00C9 (Please see above)
#define MAE_SKB_LT_E_HOOK_ABOVE_UC      0x1EBA
#define MAE_SKB_LT_E_TILDE_UC      0x1EBC
#define MAE_SKB_LT_E_DOT_BELOW_UC      0x1EB8
//#define MAE_SKB_LT_E_CIRCUMFLEX_UC      0x00CA (Please see above)
#define MAE_SKB_LT_E_CIRCUMFLEX_AND_GRAVE_UC      0x1EC0
#define MAE_SKB_LT_E_CIRCUMFLEX_AND_ACUTE_UC      0x1EBE
#define MAE_SKB_LT_E_CIRCUMFLEX_AND_HOOK_ABOVE_UC      0x1EC2
#define MAE_SKB_LT_E_CIRCUMFLEX_AND_TILDE_UC      0x1EC4
#define MAE_SKB_LT_E_CIRCUMFLEX_AND_DOT_BELOW_UC      0x1EC6

//Modified I (total 5)
#define MAE_SKB_LT_I_GRAVE_UC      0x00CC
//#define MAE_SKB_LT_I_ACUTE_UC      0x00CD (Please see above)
#define MAE_SKB_LT_I_HOOK_ABOVE_UC      0x1EC8
#define MAE_SKB_LT_I_TILDE_UC      0x0128
#define MAE_SKB_LT_I_DOT_BELOW_UC      0x1ECA

//Modified O (total 17)
//#define MAE_SKB_LT_O_GRAVE_UC      0x00D2 (Please see above)
//#define MAE_SKB_LT_O_ACUTE_UC      0x00D3 (Please see above)
#define MAE_SKB_LT_O_HOOK_ABOVE_UC      0x1ECE
//#define MAE_SKB_LT_O_TILDE_UC      0x00D5 (Please see above)
#define MAE_SKB_LT_O_DOT_BELOW_UC      0x1ECC
//#define MAE_SKB_LT_O_CIRCUMFLEX_UC      0x00D4 (Please see above)
#define MAE_SKB_LT_O_CIRCUMFLEX_AND_GRAVE_UC      0x1ED2
#define MAE_SKB_LT_O_CIRCUMFLEX_AND_ACUTE_UC      0x1ED0
#define MAE_SKB_LT_O_CIRCUMFLEX_AND_HOOK_ABOVE_UC      0x1ED4
#define MAE_SKB_LT_O_CIRCUMFLEX_AND_TILDE_UC      0x1ED6
#define MAE_SKB_LT_O_CIRCUMFLEX_AND_DOT_BELOW_UC      0x1ED8
#define MAE_SKB_LT_O_HORN_UC      0x01A0
#define MAE_SKB_LT_O_HORN_GRAVE_UC      0x1EDC
#define MAE_SKB_LT_O_HORN_ACUTE_UC      0x1EDA
#define MAE_SKB_LT_O_HORN_HOOK_ABOVE_UC      0x1EDE
#define MAE_SKB_LT_O_HORN_TILDE_UC      0x1EE0
#define MAE_SKB_LT_O_HORN_DOT_BELOW_UC      0x1EE2

//Modified U (total 11)
//#define MAE_SKB_LT_U_GRAVE_UC      0x00D9 (Please see above)
//#define MAE_SKB_LT_U_ACUTE_UC      0x00DA (Please see above)
#define MAE_SKB_LT_U_HOOK_ABOVE_UC      0x1EE6
#define MAE_SKB_LT_U_TILDE_UC      0x0168
#define MAE_SKB_LT_U_DOT_BELOW_UC      0x1EE4
#define MAE_SKB_LT_U_HORN_UC      0x01AF
#define MAE_SKB_LT_U_HORN_GRAVE_UC      0x1EEA
#define MAE_SKB_LT_U_HORN_ACUTE_UC      0x1EE8
#define MAE_SKB_LT_U_HORN_HOOK_ABOVE_UC      0x1EEC
#define MAE_SKB_LT_U_HORN_TILDE_UC      0x1EEE
#define MAE_SKB_LT_U_HORN_DOT_BELOW_UC      0x1EF0

//Modified Y (total 5)
#define MAE_SKB_LT_Y_GRAVE_UC      0x1EF2
#define MAE_SKB_LT_Y_ACUTE_UC      0x00DD
#define MAE_SKB_LT_Y_HOOK_ABOVE_UC      0x1EF6
#define MAE_SKB_LT_Y_TILDE_UC      0x1EF8
#define MAE_SKB_LT_Y_DOT_BELOW_UC      0x1EF4
/******************
Vietnamese Capital End
*******************/


#define MAE_SKB_EN_A_LC             0x0061
#define MAE_SKB_EN_B_LC             0x0062
#define MAE_SKB_EN_C_LC             0x0063
#define MAE_SKB_EN_D_LC             0x0064
#define MAE_SKB_EN_E_LC             0x0065
#define MAE_SKB_EN_F_LC             0x0066
#define MAE_SKB_EN_G_LC             0x0067
#define MAE_SKB_EN_H_LC             0x0068
#define MAE_SKB_EN_I_LC             0x0069
#define MAE_SKB_EN_J_LC             0x006A
#define MAE_SKB_EN_K_LC             0x006B
#define MAE_SKB_EN_L_LC             0x006C
#define MAE_SKB_EN_M_LC             0x006D
#define MAE_SKB_EN_N_LC             0x006E
#define MAE_SKB_EN_O_LC             0x006F
#define MAE_SKB_EN_P_LC             0x0070
#define MAE_SKB_EN_Q_LC             0x0071
#define MAE_SKB_EN_R_LC             0x0072
#define MAE_SKB_EN_S_LC             0x0073
#define MAE_SKB_EN_T_LC             0x0074
#define MAE_SKB_EN_U_LC             0x0075
#define MAE_SKB_EN_V_LC             0x0076
#define MAE_SKB_EN_W_LC             0x0077
#define MAE_SKB_EN_X_LC             0x0078
#define MAE_SKB_EN_Y_LC             0x0079
#define MAE_SKB_EN_Z_LC             0x007A

/******************
German Capital Start
*******************/
#define MAE_SKB_LT_A_DIAERESIS_UC  0x00C4
/******************
German Capital End
*******************/


/******************
Russian Lower Case Start
*******************/
#define MAE_SKB_LT_CYRILLIC_A_LC	0x0430
#define MAE_SKB_LT_CYRILLIC_BE_LC	0x0431
#define MAE_SKB_LT_CYRILLIC_VE_LC	0x0432
#define MAE_SKB_LT_CYRILLIC_GHE_LC	0x0433
#define MAE_SKB_LT_CYRILLIC_DE_LC	0x0434
#define MAE_SKB_LT_CYRILLIC_IE_LC	0x0435
#define MAE_SKB_LT_CYRILLIC_ZHE_LC	0x0436
#define MAE_SKB_LT_CYRILLIC_ZE_LC	0x0437
#define MAE_SKB_LT_CYRILLIC_I_LC	0x0438
#define MAE_SKB_LT_CYRILLIC_SHORT_I_LC	0x0439
#define MAE_SKB_LT_CYRILLIC_KA_LC	0x043A
#define MAE_SKB_LT_CYRILLIC_EL_LC	0x043B
#define MAE_SKB_LT_CYRILLIC_EM_LC	0x043C
#define MAE_SKB_LT_CYRILLIC_EN_LC	0x043D
#define MAE_SKB_LT_CYRILLIC_O_LC	0x043E
#define MAE_SKB_LT_CYRILLIC_PE_LC	0x043F
#define MAE_SKB_LT_CYRILLIC_ER_LC	0x0440
#define MAE_SKB_LT_CYRILLIC_ES_LC	0x0441
#define MAE_SKB_LT_CYRILLIC_TE_LC	0x0442
#define MAE_SKB_LT_CYRILLIC_U_LC	0x0443
#define MAE_SKB_LT_CYRILLIC_EF_LC	0x0444
#define MAE_SKB_LT_CYRILLIC_HA_LC	0x0445
#define MAE_SKB_LT_CYRILLIC_TSE_LC	0x0446
#define MAE_SKB_LT_CYRILLIC_CHE_LC	0x0447
#define MAE_SKB_LT_CYRILLIC_SHA_LC	0x0448
#define MAE_SKB_LT_CYRILLIC_SHCHA_LC	0x0449
#define MAE_SKB_LT_CYRILLIC_HARD_SIGN_LC	0x044A
#define MAE_SKB_LT_CYRILLIC_YERU_LC	0x044B
#define MAE_SKB_LT_CYRILLIC_SOFT_SIGN_LC	0x044C
#define MAE_SKB_LT_CYRILLIC_E_LC	0x044D
#define MAE_SKB_LT_CYRILLIC_YU_LC	0x044E
#define MAE_SKB_LT_CYRILLIC_YA_LC	0x044F
/******************
Russian Lower Case End
*******************/

/******************
Spanish Lower Case Start
*******************/
#define MAE_SKB_LT_A_ACUTE_LC      0x00E1
#define MAE_SKB_LT_E_ACUTE_LC      0x00E9
#define MAE_SKB_LT_I_ACUTE_LC      0x00ED
#define MAE_SKB_LT_O_ACUTE_LC      0x00F3
#define MAE_SKB_LT_U_ACUTE_LC      0x00FA
#define MAE_SKB_LT_U_DIAERESIS_LC  0x00FC
#define MAE_SKB_LT_N_TILDE_LC      0x00F1
#define MAE_SKB_LT_C_CEDILLA_LC    0x00E7
/******************
Spanish Lower Case Start
*******************/

/******************
French Lower Case Start
*******************/
#define MAE_SKB_LT_A_GRAVE_LC	0x00E0
#define MAE_SKB_LT_A_CIRCUMFLEX_LC	0x00E2
#define MAE_SKB_LT_AE_LIGATURE_LC	0x00E6
#define MAE_SKB_LT_E_GRAVE_LC	0x00E8
//#define MAE_SKB_LT_E_ACUTE_LC	0x00E9  (See Spanish)
#define MAE_SKB_LT_E_CIRCUMFLEX_LC	0x00EA
#define MAE_SKB_LT_E_DIAERESIS_LC	0x00EB
#define MAE_SKB_LT_I_CIRCUMFLEX_LC	0x00EE
#define MAE_SKB_LT_I_DIAERESIS_LC	0x00EF
#define MAE_SKB_LT_O_CIRCUMFLEX_LC	0x00F4
#define MAE_SKB_LT_OE_LIGATURE_LC	0x0153
#define MAE_SKB_LT_U_GRAVE_LC	0x00F9
#define MAE_SKB_LT_U_CIRCUMFLEX_LC	0x00FB
//#define MAE_SKB_LT_U_DIAERESIS_LC	0x00FC (See Spanish)
#define MAE_SKB_LT_Y_DIAERESIS_LC	0x00FF
//#define MAE_SKB_LT_C_CEDILLA_LC	0x00E7 (See Spanish)
/******************
French Lower Case End
*******************/

/******************
Turkish Lower Case Start
*******************/
#define MAE_SKB_LT_S_CEDILLA_LC	    0x015F
#define MAE_SKB_LT_G_BREVE_LC	    0x011F
#define MAE_SKB_LT_O_DIAERESIS_LC   0x00F6
/******************
Turkish Lower Case End
*******************/

/******************
Portuguese Lower Case Start
*******************/
//#define MAE_SKB_LT_A_GRAVE_LC	0x00E0 (Please see above)
//#define MAE_SKB_LT_A_ACUTE_LC	0x00E1 (Please see above)
//#define MAE_SKB_LT_A_CIRCUMFLEX_LC	0x00E2 (Please see above)
#define MAE_SKB_LT_A_TILDE_LC	0x00E3
//#define MAE_SKB_LT_E_ACUTE_LC	0x00E9
//#define MAE_SKB_LT_E_CIRCUMFLEX_LC	0x00EA (Please see above)
//#define MAE_SKB_LT_I_ACUTE_LC	0x00ED (Please see above)
#define MAE_SKB_LT_O_GRAVE_LC	0x00F2
//#define MAE_SKB_LT_O_ACUTE_LC	0x00F3 (Please see above)
//#define MAE_SKB_LT_O_CIRCUMFLEX_LC	0x00F4 (Please see above)
#define MAE_SKB_LT_O_TILDE_LC	0x00F5
//#define MAE_SKB_LT_U_ACUTE_LC	0x00FA
//#define MAE_SKB_LT_U_DIAERESIS_LC	0x00FC (Please see above)
//#define MAE_SKB_LT_C_CEDILLA_LC	0x00E7 (Please see above)
/******************
Portuguese Lower Case End
*******************/

/******************
Vietnamese Lower Case Start
*******************/
//Modified A (total 17)
//#define MAE_SKB_LT_A_GRAVE_LC      0x00E0 (Please see above)
//#define MAE_SKB_LT_A_ACUTE_LC      0x00E1 (Please see above)
#define MAE_SKB_LT_A_HOOK_ABOVE_LC      0x1EA3
//#define MAE_SKB_LT_A_TILDE_LC      0x00E3 (Please see above)
#define MAE_SKB_LT_A_DOT_BELOW_LC      0x1EA1
#define MAE_SKB_LT_A_BREVE_LC      0x0103
#define MAE_SKB_LT_A_BREVE_AND_GRAVE_LC      0x1EB1
#define MAE_SKB_LT_A_BREVE_AND_ACUTE_LC      0x1EAF
#define MAE_SKB_LT_A_BREVE_AND_HOOK_ABOVE_LC      0x1EB3
#define MAE_SKB_LT_A_BREVE_AND_TILDE_LC      0x1EB5
#define MAE_SKB_LT_A_BREVE_AND_DOT_BELOW_LC      0x1EB7
//#define MAE_SKB_LT_A_CIRCUMFLEX_LC      0x00E2 (Please see above)
#define MAE_SKB_LT_A_CIRCUMFLEX_AND_GRAVE_LC      0x1EA7
#define MAE_SKB_LT_A_CIRCUMFLEX_AND_ACUTE_LC      0x1EA5
#define MAE_SKB_LT_A_CIRCUMFLEX_AND_HOOK_ABOVE_LC      0x1EA9
#define MAE_SKB_LT_A_CIRCUMFLEX_AND_TILDE_LC      0x1EAB
#define MAE_SKB_LT_A_CIRCUMFLEX_AND_DOT_BELOW_LC      0x1EAD

//Modified D (total 1)
#define MAE_SKB_LT_D_STROKE_LC      0x0111

//Modified E (total 11)
//#define MAE_SKB_LT_E_GRAVE_LC      0x00E8 (Please see above)
//#define MAE_SKB_LT_E_ACUTE_LC      0x00E9 (Please see above)
#define MAE_SKB_LT_E_HOOK_ABOVE_LC      0x1EBB
#define MAE_SKB_LT_E_TILDE_LC      0x1EBD
#define MAE_SKB_LT_E_DOT_BELOW_LC      0x1EB9
//#define MAE_SKB_LT_E_CIRCUMFLEX_LC      0x00EA (Please see above)
#define MAE_SKB_LT_E_CIRCUMFLEX_AND_GRAVE_LC      0x1EC1
#define MAE_SKB_LT_E_CIRCUMFLEX_AND_ACUTE_LC      0x1EBF
#define MAE_SKB_LT_E_CIRCUMFLEX_AND_HOOK_ABOVE_LC      0x1EC3
#define MAE_SKB_LT_E_CIRCUMFLEX_AND_TILDE_LC      0x1EC5
#define MAE_SKB_LT_E_CIRCUMFLEX_AND_DOT_BELOW_LC      0x1EC7

//Modified I (total 5)
#define MAE_SKB_LT_I_GRAVE_LC      0x00EC
//#define MAE_SKB_LT_I_ACUTE_LC      0x00ED (Please see above)
#define MAE_SKB_LT_I_HOOK_ABOVE_LC      0x1EC9
#define MAE_SKB_LT_I_TILDE_LC      0x0129
#define MAE_SKB_LT_I_DOT_BELOW_LC      0x1ECB

//Modified O (total 17)
//#define MAE_SKB_LT_O_GRAVE_LC      0x00F2 (Please see above)
//#define MAE_SKB_LT_O_ACUTE_LC      0x00F3 (Please see above)
#define MAE_SKB_LT_O_HOOK_ABOVE_LC      0x1ECF
//#define MAE_SKB_LT_O_TILDE_LC      0x00F5 (Please see above)
#define MAE_SKB_LT_O_DOT_BELOW_LC      0x1ECD
//#define MAE_SKB_LT_O_CIRCUMFLEX_LC      0x00F4 (Please see above)
#define MAE_SKB_LT_O_CIRCUMFLEX_AND_GRAVE_LC      0x1ED3
#define MAE_SKB_LT_O_CIRCUMFLEX_AND_ACUTE_LC      0x1ED1
#define MAE_SKB_LT_O_CIRCUMFLEX_AND_HOOK_ABOVE_LC      0x1ED5
#define MAE_SKB_LT_O_CIRCUMFLEX_AND_TILDE_LC      0x1ED7
#define MAE_SKB_LT_O_CIRCUMFLEX_AND_DOT_BELOW_LC      0x1ED9
#define MAE_SKB_LT_O_HORN_LC      0x01A1
#define MAE_SKB_LT_O_HORN_GRAVE_LC      0x1EDD
#define MAE_SKB_LT_O_HORN_ACUTE_LC      0x1EDB
#define MAE_SKB_LT_O_HORN_HOOK_ABOVE_LC      0x1EDF
#define MAE_SKB_LT_O_HORN_TILDE_LC      0x1EE1
#define MAE_SKB_LT_O_HORN_DOT_BELOW_LC      0x1EE3

//Modified U (total 11)
//#define MAE_SKB_LT_U_GRAVE_LC      0x00F9 (Please see above)
//#define MAE_SKB_LT_U_ACUTE_LC      0x00FA (Please see above)
#define MAE_SKB_LT_U_HOOK_ABOVE_LC      0x1EE7
#define MAE_SKB_LT_U_TILDE_LC      0x0169
#define MAE_SKB_LT_U_DOT_BELOW_LC      0x1EE5
#define MAE_SKB_LT_U_HORN_LC      0x01B0
#define MAE_SKB_LT_U_HORN_GRAVE_LC      0x1EEB
#define MAE_SKB_LT_U_HORN_ACUTE_LC      0x1EE9
#define MAE_SKB_LT_U_HORN_HOOK_ABOVE_LC      0x1EED
#define MAE_SKB_LT_U_HORN_TILDE_LC      0x1EEF
#define MAE_SKB_LT_U_HORN_DOT_BELOW_LC      0x1EF1

//Modified Y (total 5)
#define MAE_SKB_LT_Y_GRAVE_LC      0x1EF3
#define MAE_SKB_LT_Y_ACUTE_LC      0x00FD
#define MAE_SKB_LT_Y_HOOK_ABOVE_LC      0x1EF7
#define MAE_SKB_LT_Y_TILDE_LC      0x1EF9
#define MAE_SKB_LT_Y_DOT_BELOW_LC      0x1EF5
/******************
Vietnamese Lower Case End
*******************/

#define MAE_SKB_FUNC_SYMBOL_PAGE1TOPAGE2  0x2191//0x25bd
#define MAE_SKB_FUNC_SYMBOL_PAGE2TOPAGE1  0x2193//0x25b3


/******************
German Lower Case Start
*******************/
#define MAE_SKB_LT_S_SHARP_LC  0x00DF
#define MAE_SKB_LT_A_DIAERESIS_LC  0x00E4
/******************
German Lower Case End
*******************/

//Function
#define MAE_SKB_FUNC_CLEAR						0x2190
#define MAE_SKB_FUNC_SHIFT						0x21E7
#define MAE_SKB_FUNC_SYMBOL						0x2048
#define MAE_SKB_FUNC_SYMBOL_OFF				0x21B6
#define MAE_SKB_FUNC_THAI_SHIFT 0x00AB //<<

//private area 0xe000 to 0xf8ff
typedef enum
{
	MAE_SKB_CODE_TYPE_SIGN,
	MAE_SKB_CODE_TYPE_TONE,
	MAE_SKB_CODE_TYPE_CHARACTER,
	MAE_SKB_CODE_TYPE_FUNCTION,
	MAE_SKB_CODE_TYPE_DISABLE_DISPLAY_TEXT
}MAE_SKB_CODE_TYPE_e;

//MAPPING TO KEY FUNCTION
#define MAE_SKB_FUNC_KEY_1                0xF831
#define MAE_SKB_FUNC_KEY_2                0xF832
#define MAE_SKB_FUNC_KEY_3                0xF833
#define MAE_SKB_FUNC_KEY_4                0xF834
#define MAE_SKB_FUNC_KEY_5                0xF835
#define MAE_SKB_FUNC_KEY_6                0xF836
#define MAE_SKB_FUNC_KEY_7                0xF837
#define MAE_SKB_FUNC_KEY_8                0xF838
#define MAE_SKB_FUNC_KEY_9                0xF839
#define MAE_SKB_FUNC_KEY_STAR             0xF83A
#define MAE_SKB_FUNC_KEY_0                0xF83B
#define MAE_SKB_FUNC_KEY_HASH             0xF83C


//Others
#define MAE_IME_BPMF_START			MAE_IME_MY_CODE_BPMF_B
#define MAE_IME_BPMF_END       		MAE_IME_MY_CODE_BPMF_IU
#define MAE_IME_STROKE_START		 MAE_IME_CODE_STROKE_OVER
#define MAE_IME_PINYIN_START		MAE_IME_CODE_PINYIN_A
#define MAE_IME_PINYIN_END			MAE_IME_CODE_PINYIN_Z
#define MAE_IME_EN_UC_START			 MAE_SKB_EN_A_UC
#define MAE_IME_EN_UC_END				 MAE_SKB_EN_Z_UC
#define MAE_IME_EN_LC_START			 MAE_SKB_EN_A_LC
#define MAE_IME_EN_LC_END				 MAE_SKB_EN_Z_LC

#endif //#ifdef __TOUCH_SCREEN_MMI__

//symbol
#define MAE_IME_SYMBOL_SPACE_VALUE			0x0020
#define MAE_IME_SYMBOL_LINEFEED_VALUE		0x000A
#define MAE_IME_SYMBOL_SPACE				    0x2423
#define MAE_IME_SYMBOL_LINEFEED				  0x21B5
#define MAE_IME_SYMBOL_QUESTION				0x003F	//?
#define MAE_IME_SYMBOL_EXCLAMATION			0x0021	//!
#define MAE_IME_SYMBOL_SEMI_COLON			0x003B	//;
#define MAE_IME_SYMBOL_COMMA				0x002C	//,
#define MAE_IME_SYMBOL_FULL_STOP			0x002E	//.
#define MAE_IME_SYMBOL_APOSTROPHE			0x0027	//'
#define MAE_IME_SYMBOL_QUOTATION			0x0022	//"
#define MAE_IME_SYMBOL_HYPHEN_MINUS			0x002D	//-
#define MAE_IME_SYMBOL_LEFT_PARENTHESIS		0x0028 //(
#define MAE_IME_SYMBOL_RIGHT_PARENTHESIS	0x0029	//)
#define MAE_IME_SYMBOL_COMMERCIAL_AT		0x0040	//@
#define MAE_IME_SYMBOL_SOLIDUS				0x002F	// '/'
#define MAE_IME_SYMBOL_COLON			    0x003A	//:
#define MAE_IME_SYMBOL_LOW_LINE				0x005F	//_
#define MAE_IME_SYMBOL_PLUS					0x002B	//+
#define MAE_IME_SYMBOL_AMPERSAND  			0x0026	//&
#define MAE_IME_SYMBOL_PERCENT				0x0025	//%
#define MAE_IME_SYMBOL_ASTERISK				0x002A	//"*"
#define MAE_IME_SYMBOL_NUMBER				0x0023	//#
#define MAE_IME_SYMBOL_EQUALS				0x003D	//=
#define MAE_IME_SYMBOL_LESS_THAN			0x003C	//<
#define MAE_IME_SYMBOL_GREATER_THAN			0x003E	//>
#define MAE_IME_SYMBOL_POUND				0x00A3	//pound
#define MAE_IME_SYMBOL_EURO					0x20AC	//
#define MAE_IME_SYMBOL_DOLLAR				0x0024	//$
#define MAE_IME_SYMBOL_RUPEE				0x20B9	//Indian Rupee currency sign
#define MAE_IME_SYMBOL_YEN	  				0x00A5	//Y
#define MAE_IME_SYMBOL_LEFT_SQUARE_BRACKET	0x005B	//[
#define MAE_IME_SYMBOL_RIGHT_SQUARE_BRACKET	0x005D	//]
#define MAE_IME_SYMBOL_REVERSE				0x005C	//"\"
#define MAE_IME_SYMBOL_GRAVE_ACCENT			0x0060	//"`"
#define MAE_IME_SYMBOL_TILDE				0x007E	//~
#define MAE_IME_SYMBOL_CIRCUMFLEX			0x005E	//^
#define MAE_IME_SYMBOL_INVERTED_QUESTION	0x00BF	//inverted "?"
#define MAE_IME_SYMBOL_INVERTED_EXCLAMATION	0x00A1	//inverted "!"
#define MAE_IME_SYMBOL_VERTICAL_LINE		0x007C	//|
#define MAE_IME_SYMBOL_CURRENCY				0x00A4	//
#define MAE_IME_SYMBOL_SECTION				0x00A7	//

#define MAE_IME_SYMBOL_LEFT_CURLY_BRACKET	0x007B	//{
#define MAE_IME_SYMBOL_RIGHT_CURLY_BRACKET	0x007D	//}

#define MAE_IME_SYMBOL_ARRAWLEFT			0x2190
#define MAE_IME_SYMBOL_ARRAWUP				0x2191
#define MAE_IME_SYMBOL_ARRAWRIGHT			0x2192
#define MAE_IME_SYMBOL_ARRAWDOWN			0x2193
#define MAE_IME_SYMBOL_LEFTDOUBLEBRACKET	0x300A
#define MAE_IME_SYMBOL_RIGHTDOUBLEBRACKET	0x300B
#define MAE_IME_SYMBOL_SUSPENSION	        0x2026
#define MAE_IME_SYMBOL_FAHRENHEIT		    0x2109	//
#define MAE_IME_SYMBOL_CENTIGRADE		    0x2103	//

#define MAE_IME_LT_SYMBOL_GRAVE				    0x0300	//
#define MAE_IME_LT_SYMBOL_ACUTE				    0x0301	//
#define MAE_IME_LT_SYMBOL_CIRCUMFLEX		    0x0302	//
#define MAE_IME_LT_SYMBOL_HOOK_ABOVE		    0x0309	//
#define MAE_IME_LT_SYMBOL_TILDE		            0x0303	//
#define MAE_IME_LT_SYMBOL_DOT_ABOVE		        0x0307	//
#define MAE_IME_LT_SYMBOL_DIAERESIS		        0x0308	//
#define MAE_IME_LT_SYMBOL_DOT_BELOW		        0x0323	//
//#define MAE_IME_LT_SYMBOL_MODIFIER_LETTER_MACRON 0x02C9	//

#define MAE_SKB_LT_SYMBOL_DONG     0x20AB //Vietnamese currency


/******************************************************/
/*           for Chinese                              */
/******************************************************/
#define MAE_IME_STROKE_BASE 0xEF00
#define MAE_IME_BPMF_BASE	0x3105
#define MAE_IME_PINYIN_BASE 0x0000
#define MAE_IME_TONE_BASE   0xF331

//BPMF
#define MAE_IME_CODE_BPMF_B       (MAE_IME_BPMF_BASE + 0)  
#define MAE_IME_CODE_BPMF_P       (MAE_IME_BPMF_BASE + 1)
#define MAE_IME_CODE_BPMF_M       (MAE_IME_BPMF_BASE + 2)
#define MAE_IME_CODE_BPMF_F       (MAE_IME_BPMF_BASE + 3)
#define MAE_IME_CODE_BPMF_D       (MAE_IME_BPMF_BASE + 4)
#define MAE_IME_CODE_BPMF_T       (MAE_IME_BPMF_BASE + 5)
#define MAE_IME_CODE_BPMF_N       (MAE_IME_BPMF_BASE + 6)
#define MAE_IME_CODE_BPMF_L       (MAE_IME_BPMF_BASE + 7)
#define MAE_IME_CODE_BPMF_G       (MAE_IME_BPMF_BASE + 8)
#define MAE_IME_CODE_BPMF_K       (MAE_IME_BPMF_BASE + 9)
#define MAE_IME_CODE_BPMF_H       (MAE_IME_BPMF_BASE + 10)
#define MAE_IME_CODE_BPMF_J       (MAE_IME_BPMF_BASE + 11)
#define MAE_IME_CODE_BPMF_Q       (MAE_IME_BPMF_BASE + 12)
#define MAE_IME_CODE_BPMF_X       (MAE_IME_BPMF_BASE + 13)
#define MAE_IME_CODE_BPMF_ZH      (MAE_IME_BPMF_BASE + 14)
#define MAE_IME_CODE_BPMF_CH      (MAE_IME_BPMF_BASE + 15)
#define MAE_IME_CODE_BPMF_SH      (MAE_IME_BPMF_BASE + 16)
#define MAE_IME_CODE_BPMF_R       (MAE_IME_BPMF_BASE + 17)
#define MAE_IME_CODE_BPMF_Z       (MAE_IME_BPMF_BASE + 18)
#define MAE_IME_CODE_BPMF_C       (MAE_IME_BPMF_BASE + 19)
#define MAE_IME_CODE_BPMF_S       (MAE_IME_BPMF_BASE + 20)
#define MAE_IME_CODE_BPMF_A       (MAE_IME_BPMF_BASE + 21)
#define MAE_IME_CODE_BPMF_O       (MAE_IME_BPMF_BASE + 22)
#define MAE_IME_CODE_BPMF_E       (MAE_IME_BPMF_BASE + 23)
#define MAE_IME_CODE_BPMF_EH      (MAE_IME_BPMF_BASE + 24)
#define MAE_IME_CODE_BPMF_AI      (MAE_IME_BPMF_BASE + 25)
#define MAE_IME_CODE_BPMF_EI      (MAE_IME_BPMF_BASE + 26)
#define MAE_IME_CODE_BPMF_AU      (MAE_IME_BPMF_BASE + 27)
#define MAE_IME_CODE_BPMF_OU      (MAE_IME_BPMF_BASE + 28)
#define MAE_IME_CODE_BPMF_AN      (MAE_IME_BPMF_BASE + 29)
#define MAE_IME_CODE_BPMF_EN      (MAE_IME_BPMF_BASE + 30)
#define MAE_IME_CODE_BPMF_ANG     (MAE_IME_BPMF_BASE + 31)
#define MAE_IME_CODE_BPMF_ENG     (MAE_IME_BPMF_BASE + 32)
#define MAE_IME_CODE_BPMF_ER      (MAE_IME_BPMF_BASE + 33)
#define MAE_IME_CODE_BPMF_I       (MAE_IME_BPMF_BASE + 34)
#define MAE_IME_CODE_BPMF_U       (MAE_IME_BPMF_BASE + 35)
#define MAE_IME_CODE_BPMF_IU      (MAE_IME_BPMF_BASE + 36)

#define MAE_IME_CODE_BPMF_TONE_1   MAE_IME_TONE_BASE
#define MAE_IME_CODE_BPMF_TONE_2   (MAE_IME_TONE_BASE + 1)                  
#define MAE_IME_CODE_BPMF_TONE_3   (MAE_IME_TONE_BASE + 2)       
#define MAE_IME_CODE_BPMF_TONE_4   (MAE_IME_TONE_BASE + 3)              
#define MAE_IME_CODE_BPMF_TONE_5   (MAE_IME_TONE_BASE + 4)            


//PINYIN
#define MAE_IME_CODE_PINYIN_A	   (MAE_IME_PINYIN_BASE + 0x0061)
#define MAE_IME_CODE_PINYIN_B     (MAE_IME_PINYIN_BASE + 0x0062)
#define MAE_IME_CODE_PINYIN_C     (MAE_IME_PINYIN_BASE + 0x0063)
#define MAE_IME_CODE_PINYIN_D     (MAE_IME_PINYIN_BASE + 0x0064)
#define MAE_IME_CODE_PINYIN_E     (MAE_IME_PINYIN_BASE + 0x0065)
#define MAE_IME_CODE_PINYIN_F     (MAE_IME_PINYIN_BASE + 0x0066)
#define MAE_IME_CODE_PINYIN_G     (MAE_IME_PINYIN_BASE + 0x0067)
#define MAE_IME_CODE_PINYIN_H     (MAE_IME_PINYIN_BASE + 0x0068)
#define MAE_IME_CODE_PINYIN_I     (MAE_IME_PINYIN_BASE + 0x0069)
#define MAE_IME_CODE_PINYIN_J     (MAE_IME_PINYIN_BASE + 0x006A)
#define MAE_IME_CODE_PINYIN_K     (MAE_IME_PINYIN_BASE + 0x006B)
#define MAE_IME_CODE_PINYIN_L     (MAE_IME_PINYIN_BASE + 0x006C)
#define MAE_IME_CODE_PINYIN_M     (MAE_IME_PINYIN_BASE + 0x006D)
#define MAE_IME_CODE_PINYIN_N     (MAE_IME_PINYIN_BASE + 0x006E)
#define MAE_IME_CODE_PINYIN_O     (MAE_IME_PINYIN_BASE + 0x006F)
#define MAE_IME_CODE_PINYIN_P     (MAE_IME_PINYIN_BASE + 0x0070)
#define MAE_IME_CODE_PINYIN_Q     (MAE_IME_PINYIN_BASE + 0x0071)
#define MAE_IME_CODE_PINYIN_R     (MAE_IME_PINYIN_BASE + 0x0072)
#define MAE_IME_CODE_PINYIN_S     (MAE_IME_PINYIN_BASE + 0x0073)
#define MAE_IME_CODE_PINYIN_T     (MAE_IME_PINYIN_BASE + 0x0074)
#define MAE_IME_CODE_PINYIN_U     (MAE_IME_PINYIN_BASE + 0x0075)
#define MAE_IME_CODE_PINYIN_V     (MAE_IME_PINYIN_BASE + 0x0076)
#define MAE_IME_CODE_PINYIN_W     (MAE_IME_PINYIN_BASE + 0x0077)
#define MAE_IME_CODE_PINYIN_X     (MAE_IME_PINYIN_BASE + 0x0078)
#define MAE_IME_CODE_PINYIN_Y     (MAE_IME_PINYIN_BASE + 0x0079)
#define MAE_IME_CODE_PINYIN_Z     (MAE_IME_PINYIN_BASE + 0x007A)

//stroke
#define MAE_IME_CODE_STROKE_WILDCARD     	(MAE_IME_STROKE_BASE + 0)
#define MAE_IME_CODE_STROKE_DOWN         	(MAE_IME_STROKE_BASE + 1)
#define MAE_IME_CODE_STROKE_DOT          	(MAE_IME_STROKE_BASE + 2)
#define MAE_IME_CODE_STROKE_OVER         	(MAE_IME_STROKE_BASE + 4)
#define MAE_IME_CODE_STROKE_OVER_DOWN    	(MAE_IME_STROKE_BASE + 5)
#define MAE_IME_CODE_STROKE_LEFT         	(MAE_IME_STROKE_BASE + 7)

#define MAE_IME_CODE_STROKE_CURVED_HOOK  	(MAE_IME_STROKE_BASE + 3)
#define MAE_IME_CODE_STROKE_DOWN_OVER    	(MAE_IME_STROKE_BASE + 6)
#define MAE_IME_CODE_STROKE_OVER_DOWN_OVER	(MAE_IME_STROKE_BASE + 8)

#define MAE_IME_CH_SYMBOL_FULL_STOP			0x3002	//¡C
#define MAE_IME_CH_SYMBOL_COMMA				0xFF0C	//¡A
#define MAE_IME_CH_SYMBOL_SET_OFF			0x3001	//¡B
#define MAE_IME_CH_SYMBOL_QUESTION			0xFF1F	//¡H
#define MAE_IME_CH_SYMBOL_EXCLAMATION		0xFF01	//¡I
#define MAE_IME_CH_SYMBOL_SOLIDUS			0xFF0F	// ¡þ
#define MAE_IME_CH_SYMBOL_COLON				0xFF1A	//¡G
#define MAE_IME_CH_SYMBOL_SEMI_COLON		0xFF1B	//¡F
#define MAE_IME_CH_SYMBOL_LESS_THAN			0x300A	// ¡m
#define MAE_IME_CH_SYMBOL_GREATER_THAN		0x300B	//¡n
#define MAE_IME_CH_SYMBOL_LEFT_QUOTATION	0x201C	//¡§
#define MAE_IME_CH_SYMBOL_RIGHT_QUOTATION	0x201D	//¡¨

#define MAE_IME_CH_SYMBOL_LEFT_SQUARE_BRACKET	0x3010	//¡¾
#define MAE_IME_CH_SYMBOL_RIGHT_SQUARE_BRACKET	0x3011	//¡¿
#define MAE_IME_CH_SYMBOL_LEFT_PARENTHESIS		0x3014 //(
#define MAE_IME_CH_SYMBOL_RIGHT_PARENTHESIS	0x3015	//)
#define MAE_IME_CH_SYMBOL_PLUS					0xfe62	//+
#define MAE_IME_CH_SYMBOL_PERCENT				0xfe6a	//%
#define MAE_IME_CH_SYMBOL_EQUALS				0xfe66	//=
#define MAE_IME_CH_SYMBOL_LEFT_HALFSQUARE_BRACKET	0x300e	//¡¾
#define MAE_IME_CH_SYMBOL_RIGHT_HALFSQUARE_BRACKET	0x300f	//¡¿
#define MAE_IME_SYMBOL_DOUBLELESS_THAN			0x00ab	//<<
#define MAE_IME_SYMBOL_DOUBLEGREATER_THAN			0x00bb	//>>

/******************************************************/
/*           for MY Chinese input Engine use only                       */
/******************************************************/
#define MAE_IME_MY_BPMF_BASE	0xF305
#define MAE_IME_MY_BPMF_BASE_SUB_MAE_IME_BPMF_BASE	0xC200

//BPMF
#define MAE_IME_MY_CODE_BPMF_B       (MAE_IME_MY_BPMF_BASE + 0)
#define MAE_IME_MY_CODE_BPMF_IU      (MAE_IME_MY_BPMF_BASE + 36)

/******************************************************/
/*           for Chinese Softkeyboard Stroke Unicode use                          */
/******************************************************/
//stroke
#define MAE_IME_UNICODE_STROKE_WILDCARD     	0xFF1F
#define MAE_IME_UNICODE_STROKE_DOWN         	0x4E28
#define MAE_IME_UNICODE_STROKE_DOT          	0x4E36
#define MAE_IME_UNICODE_STROKE_OVER         	0x4E00
#define MAE_IME_UNICODE_STROKE_OVER_DOWN    	0x4E59
#define MAE_IME_UNICODE_STROKE_LEFT         	0x4E3F

//#define MAE_IME_UNICODE_STROKE_CURVED_HOOK  	0xFF1F
//#define MAE_IME_UNICODE_STROKE_DOWN_OVER    	0xFF1F
//#define MAE_IME_UNICODE_STROKE_OVER_DOWN_OVER	0xFF1F

#endif //__MAE_SOFTKEYBOARD_IME_MAPPINGTABLE_H__
