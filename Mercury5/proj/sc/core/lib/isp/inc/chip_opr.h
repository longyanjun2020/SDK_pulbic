#ifndef _CHIP_OPR_H_
#define _CHIP_OPR_H_


/*************************************************************************************************/
/* Definition                                                                                    */
/*************************************************************************************************/
// BANK
#define OFST_R000						(gOprMap[gIspChip.OprOfst[ISP_OPR_OFFSET_R0]		>>8])
#define OFST_R100						(gOprMap[gIspChip.OprOfst[ISP_OPR_OFFSET_R1]		>>8])
#define OFST_R200						(gOprMap[gIspChip.OprOfst[ISP_OPR_OFFSET_R2]		>>8])
#define OFST_R300						(gOprMap[gIspChip.OprOfst[ISP_OPR_OFFSET_R3]		>>8])
#define OFST_R400						(gOprMap[gIspChip.OprOfst[ISP_OPR_OFFSET_R4]		>>8])
#define OFST_R500						(gOprMap[gIspChip.OprOfst[ISP_OPR_OFFSET_R5]		>>8])
#define OFST_R600						(gOprMap[gIspChip.OprOfst[ISP_OPR_OFFSET_R6]		>>8])
#define OFST_R700						(gOprMap[gIspChip.OprOfst[ISP_OPR_OFFSET_R7]		>>8])
#define OFST_R800						(gOprMap[gIspChip.OprOfst[ISP_OPR_OFFSET_R8]		>>8])
#define APICAL_OFFSET					(gOprMap[gIspChip.OprOfst[ISP_OPR_OFFSET_APICAL]	>>8])
#define LS_TAB_START					(gOprMap[gIspChip.OprOfst[ISP_OPR_OFFSET_LS]		>>8])
#define CS_TAB_START					(gOprMap[gIspChip.OprOfst[ISP_OPR_OFFSET_CS]		>>8])
#define VIF_OFFSET						(gOprMap[gIspChip.OprOfst[ISP_OPR_OFFSET_VIF]		>>8])
#define GNR_LUMA_TAB_START				(gOprMap[gIspChip.OprOfst[ISP_OPR_OFFSET_GNR_LUMA]	>>8])
#define YNRYEE_TAB_START				(gOprMap[gIspChip.OprOfst[ISP_OPR_OFFSET_YNRYEE]	>>8])
#define YNRYEE_W_TAB_START				(gOprMap[gIspChip.OprOfst[ISP_OPR_OFFSET_YNRYEE_W]	>>8])
#define SDC_TAB_START					(gOprMap[gIspChip.OprOfst[ISP_OPR_OFFSET_SDC]		>>8])
#define YMIX_TAB_START					(gOprMap[gIspChip.OprOfst[ISP_OPR_OFFSET_YMIX]		>>8])
#define HSVADJ_TAB_START				(gOprMap[gIspChip.OprOfst[ISP_OPR_OFFSET_HSVADJ]	>>8])

// BANK
#define HWOFST_R000						(gIspChip.OprOfst[ISP_OPR_OFFSET_R0]		)
#define HWOFST_R100						(gIspChip.OprOfst[ISP_OPR_OFFSET_R1]		)
#define HWOFST_R200						(gIspChip.OprOfst[ISP_OPR_OFFSET_R2]		)
#define HWOFST_R300						(gIspChip.OprOfst[ISP_OPR_OFFSET_R3]		)
#define HWOFST_R400						(gIspChip.OprOfst[ISP_OPR_OFFSET_R4]		)
#define HWOFST_R500						(gIspChip.OprOfst[ISP_OPR_OFFSET_R5]		)
#define HWOFST_R600						(gIspChip.OprOfst[ISP_OPR_OFFSET_R6]		)
#define HWOFST_R700						(gIspChip.OprOfst[ISP_OPR_OFFSET_R7]		)
#define HWOFST_R800						(gIspChip.OprOfst[ISP_OPR_OFFSET_R8]		)
#define HWAPICAL_OFFSET					(gIspChip.OprOfst[ISP_OPR_OFFSET_APICAL]	)
#define HWLS_TAB_START					(gIspChip.OprOfst[ISP_OPR_OFFSET_LS]		)
#define HWCS_TAB_START					(gIspChip.OprOfst[ISP_OPR_OFFSET_CS]		)
#define HWVIF_OFFSET					(gIspChip.OprOfst[ISP_OPR_OFFSET_VIF]		)
#define HWGNR_LUMA_TAB_START			(gIspChip.OprOfst[ISP_OPR_OFFSET_GNR_LUMA]	)
#define HWYNRYEE_TAB_START				(gIspChip.OprOfst[ISP_OPR_OFFSET_YNRYEE]	)
#define HWYNRYEE_W_TAB_START			(gIspChip.OprOfst[ISP_OPR_OFFSET_YNRYEE_W]	)
#define HWSDC_TAB_START					(gIspChip.OprOfst[ISP_OPR_OFFSET_SDC]		)
#define HWYMIX_TAB_START				(gIspChip.OprOfst[ISP_OPR_OFFSET_YMIX]		)
#define HWHSVADJ_TAB_START				(gIspChip.OprOfst[ISP_OPR_OFFSET_HSVADJ]	)





/*************************************************************************************************/
/* Opr Register                                                                                  */
/*************************************************************************************************/
#define OPR_ADDR						(gIspChip.BankAddr[ISP_BANK_ADDR_IQ])
#define OPR_XBYTE						((volatile ISP_UINT8*) OPR_ADDR)
#define OPR_XWORD						((volatile ISP_UINT16*)OPR_ADDR)
#define OPR_XLONG						((volatile ISP_UINT32*)OPR_ADDR)

#define SET_OPR_XBYTE(A,V)				OPR_XBYTE[(A)     ] = (V)
#define SET_OPR_XWORD(A,V)				OPR_XWORD[(A) >> 1] = (V)
#define SET_OPR_XLONG(A,V)				OPR_XLONG[(A) >> 2] = (V)

#define GET_OPR_XBYTE(A)				OPR_XBYTE[(A)     ]
#define GET_OPR_XWORD(A)				OPR_XWORD[(A) >> 1]
#define GET_OPR_XLONG(A)				OPR_XLONG[(A) >> 2]





/*************************************************************************************************/
/* HW Opr Register                                                                               */
/*************************************************************************************************/
#define HWOPR_ADDR						ISP_HDM_IF_LIB_OprAddrP2V(0x80000000)
#define HWOPR_XBYTE						((volatile ISP_UINT8*) HWOPR_ADDR)
#define HWOPR_XWORD						((volatile ISP_UINT16*)HWOPR_ADDR)
#define HWOPR_XLONG						((volatile ISP_UINT32*)HWOPR_ADDR)

#define SET_HWOPR_XBYTE(A,V)			HWOPR_XBYTE[(A)     ] = (V)
#define SET_HWOPR_XWORD(A,V)			HWOPR_XWORD[(A) >> 1] = (V)
#define SET_HWOPR_XLONG(A,V)			HWOPR_XLONG[(A) >> 2] = (V)

#define GET_HWOPR_XBYTE(A)				HWOPR_XBYTE[(A)     ]
#define GET_HWOPR_XWORD(A)				HWOPR_XWORD[(A) >> 1]
#define GET_HWOPR_XLONG(A)				HWOPR_XLONG[(A) >> 2]





#if CHIP_868_COMPATIBLE
/*************************************************************************************************/
/* Apical IP Register (NR + Color Matrix + WDR)                                                  */
/*************************************************************************************************/
#define APICAL_CTL_REG0					(APICAL_OFFSET + 0x20)
#define APICAL_CTL_REG1					(APICAL_OFFSET + 0x22)

#define SINTER_IN_WIDTH_L				(APICAL_OFFSET + 0x33)
#define SINTER_IN_WIDTH_H				(APICAL_OFFSET + 0x34)	// [3:0]
#define SINTER_IN_HEIGHT_L				(APICAL_OFFSET + 0x35)
#define SINTER_IN_HEIGHT_H				(APICAL_OFFSET + 0x36)	// [3:0]

#define SINTER_CTL_REG					(APICAL_OFFSET + 0x40)
		/*-DEFINE-----------------------------------------------------*/
		#define SINTER_ORG_SCALE_0        					0x00
		#define SINTER_ORG_SCALE_2       					0x01
		#define SINTER_ORG_SCALE_4     						0x02
		#define SINTER_FILTER_SCALE_0						0x00
		#define SINTER_FILTER_SCALE_02		     			0x04
		#define SINTER_FILTER_SCALE_024						0x08
		#define SINTER_FUN_EN								0x10
		/*------------------------------------------------------------*/

#define SINTER_TRESH_0_H				(APICAL_OFFSET + 0x41)	// [5:0]
#define SINTER_TRESH_2_H				(APICAL_OFFSET + 0x42)	// [5:0]
#define SINTER_TRESH_4_H				(APICAL_OFFSET + 0x43)	// [5:0]

#define SINTER_STRENGTH_0				(APICAL_OFFSET + 0x44)
#define SINTER_STRENGTH_2				(APICAL_OFFSET + 0x45)
#define SINTER_STRENGTH_4				(APICAL_OFFSET + 0x46)

#define SINTER_TRESH_0_V				(APICAL_OFFSET + 0x47)	// [5:0]
#define SINTER_TRESH_2_V				(APICAL_OFFSET + 0x48)	// [5:0]
#define SINTER_TRESH_4_V				(APICAL_OFFSET + 0x49)	// [5:0]

#define APICAL_PAGE_SEL					(APICAL_OFFSET + 0x8E)

/*--------------------------------------------------------------------*/
//PAGE0
/*--------------------------------------------------------------------*/
#define IRIDIX_CTL_REG0					(APICAL_OFFSET + 0x90)
		/*-DEFINE-----------------------------------------------------*/
		#define IRIDIX_FUN_EN								0x01
		#define IRIDIX_ALGORITHM_SEL						0x08
		#define IRIDIX_COLOR_CORR_EN		     			0x10
		/*------------------------------------------------------------*/

#define IRIDIX_CTL_REG1					(APICAL_OFFSET + 0x91)
#define IRIDIX_STRENGTH					(APICAL_OFFSET + 0x92)
#define IRIDIX_VARIANCE					(APICAL_OFFSET + 0x93)
#define IRIDIX_SLOPE_LMT				(APICAL_OFFSET + 0x94)
#define IRIDIX_BLACK_LVL_L				(APICAL_OFFSET + 0x9C)
#define IRIDIX_BLACK_LVL_H				(APICAL_OFFSET + 0x9D)	// [3:0]
#define IRIDIX_WHITE_LVL_L				(APICAL_OFFSET + 0x9E)
#define IRIDIX_WHITE_LVL_H				(APICAL_OFFSET + 0x9F)	// [3:0]

/*--------------------------------------------------------------------*/
//PAGE1
/*--------------------------------------------------------------------*/
#define IRIDIX_AMP_LMT					(APICAL_OFFSET + 0x93)
#define IRIDIX_LEFT_POS					(APICAL_OFFSET + 0x9E)
#define IRIDIX_TOP_POS					(APICAL_OFFSET + 0x9F)

/*--------------------------------------------------------------------*/
//PAGE2
/*--------------------------------------------------------------------*/
#define IRIDIX_ASYM_INDEX				(APICAL_OFFSET + 0x90)
#define IRIDIX_ASYM_VALUE_L				(APICAL_OFFSET + 0x91)
#define IRIDIX_ASYM_VALUE_H				(APICAL_OFFSET + 0x92)
#define IRIDIX_ALT_ASYM_INDEX			(APICAL_OFFSET + 0x93)
#define IRIDIX_ALT_ASYM_VALUE_L			(APICAL_OFFSET + 0x94)
#define IRIDIX_ALT_ASYM_VALUE_H			(APICAL_OFFSET + 0x95)
#define IRIDIX_COLOR_CORR_INDEX			(APICAL_OFFSET + 0x98)
#define IRIDIX_COLOR_CORR_VALUE_L		(APICAL_OFFSET + 0x99)
#define IRIDIX_COLOR_CORR_VALUE_H		(APICAL_OFFSET + 0x9A)
#define IRIDIX_ALT_COLOR_CORR_INDEX		(APICAL_OFFSET + 0x9B)
#define IRIDIX_ALT_COLOR_CORR_VALUE_L	(APICAL_OFFSET + 0x9C)
#define IRIDIX_ALT_COLOR_CORR_VALUE_H	(APICAL_OFFSET + 0x9D)

#define SINTER_NOISE1_INDEX				(APICAL_OFFSET + 0xA0)
#define SINTER_NOISE1_VALUE_L			(APICAL_OFFSET + 0xA1)
#define SINTER_NOISE1_VALUE_H			(APICAL_OFFSET + 0xA2)
#define SINTER_NOISE1_ALT_INDEX			(APICAL_OFFSET + 0xA3)
#define SINTER_NOISE1_ALT_VALUE_L		(APICAL_OFFSET + 0xA4)
#define SINTER_NOISE1_ALT_VALUE_H		(APICAL_OFFSET + 0xA5)
#define SINTER_NOISE2_INDEX				(APICAL_OFFSET + 0xA8)
#define SINTER_NOISE2_VALUE_L			(APICAL_OFFSET + 0xA9)
#define SINTER_NOISE2_VALUE_H			(APICAL_OFFSET + 0xAA)
#define SINTER_NOISE2_ALT_INDEX			(APICAL_OFFSET + 0xAB)
#define SINTER_NOISE2_ALT_VALUE_L		(APICAL_OFFSET + 0xAC)
#define SINTER_NOISE2_ALT_VALUE_H		(APICAL_OFFSET + 0xAD)

/*--------------------------------------------------------------------*/
//PAGE3
/*--------------------------------------------------------------------*/
#define APICAL_CCM_CTL_REG				(APICAL_OFFSET + 0xA2)
		/*-DEFINE-----------------------------------------------------*/
		#define APICAL_CCM_EN								0x01
		#define APICAL_CCM_DIS								0x00

		#define APICAL_CCM_COLOR_ID_MASK					0x06 // [2:1]
		#define APICAL_CCM_COLOR_ID_BASE					0x02 // [2:1]
		/*------------------------------------------------------------*/
#endif // CHIP_868_COMPATIBLE





/*************************************************************************************************/
/* OFST_R000 Register                                                                            */
/*************************************************************************************************/
#define ISP_SRC_CTL 					(OFST_R000 + 0x00)
#define HWISP_SRC_CTL 						(HWOFST_R000 + 0x00)
		/*-DEFINE-----------------------------------------------------*/
		#define ISP_LUMA_CHROMA_SRC_SEL_0					0x00
		#define ISP_LUMA_CHROMA_SRC_SEL_1					0x80

		#define ISP_BAYERGAMMA_SRC_SEL_0					0x00
		#define ISP_BAYERGAMMA_SRC_SEL_1					0x40

		#define ISP_COLOR_ID_MASK							0x30
		#define ISP_COLOR_ID_BASE							0x10 // [5:4]
		/*------------------------------------------------------------*/

#define ISP_DGAIN_L 					(OFST_R000 + 0x01)
#define HWISP_DGAIN_L 						(HWOFST_R000 + 0x01)

#define ISP_DEMOSAIC_LIMIT 				(OFST_R000 + 0x02)
#define HWISP_DEMOSAIC_LIMIT 				(HWOFST_R000 + 0x02)
		/*-DEFINE-----------------------------------------------------*/
		#define ISP_DEMOSAIC_LIMIT_BYPASS					0x00
		/*------------------------------------------------------------*/

#define ISP_AWB_PREGAIN_R_L				(OFST_R000 + 0x03)
#define ISP_AWB_PREGAIN_GR_L			(OFST_R000 + 0x04)
#define ISP_AWB_PREGAIN_GB_L			(OFST_R000 + 0x05)
#define ISP_AWB_PREGAIN_B_L				(OFST_R000 + 0x06)

#define ISP_AWB_GAIN_B_H				(OFST_R000 + 0x03)	// 848
#define ISP_AWB_GAIN_G_H				(OFST_R000 + 0x04)	// 848
#define ISP_AWB_GAIN_R_H				(OFST_R000 + 0x05)	// 848
#define ISP_AWB_GAIN_RGB_L				(OFST_R000 + 0x06)	// 848

#define ISP_BAYER_CTL 					(OFST_R000 + 0x07)
		/*-DEFINE-----------------------------------------------------*/
		#define ISP_BAYER_H_DN_SAMPLE_BY_2_EN				0x01
		#define ISP_BAYER_V_DN_SAMPLE_BY_2_EN				0x02

		#define ISP_BAYER_GAMMA_EN							0x08
		/*------------------------------------------------------------*/

#define ISP_AWB_PREGAIN_RGB_H			(OFST_R000 + 0x08)

#define ISP_HIST_GAIN					(OFST_R000 + 0x08)	// 848
#define HWISP_HIST_GAIN						(HWOFST_R000 + 0x08)

#define ISP_APICAL_IP_CTL				(OFST_R000 + 0x09)
		/*-DEFINE-----------------------------------------------------*/
		#define ISP_APICAL_IP_POWER_SAVING_EN				0x01 // [0]

		#define ISP_APICAL_IP_COLOR_ID_MASK					0x06 // [2:1]
		#define ISP_APICAL_IP_COLOR_ID_BASE					0x02 // [2:1]

		#define ISP_APICAL_IP_CCM_IN_FROM_RAW				0x00 // [3]
		#define ISP_APICAL_IP_CCM_IN_FROM_SINTER			0x08 // [3]

		#define ISP_APICAL_IP_WDR_IN_FROM_RAW				0x00 // [5:4]
		#define ISP_APICAL_IP_WDR_IN_FROM_CCM				0x10 // [5:4]
		#define ISP_APICAL_IP_WDR_IN_FROM_SINTER			0x20 // [5:4]

		#define ISP_APICAL_IP_OUT_FROM_RAW					0x00 // [7:6]
		#define ISP_APICAL_IP_OUT_FROM_WDR					0x40 // [7:6]
		#define ISP_APICAL_IP_OUT_FROM_SINTER				0x80 // [7:6]
		#define ISP_APICAL_IP_OUT_FROM_CCM					0xC0 // [7:6]
		/*------------------------------------------------------------*/

#define ISP_MISC_CONTROL				(OFST_R000 + 0x0A)
		/*-DEFINE-----------------------------------------------------*/
		#define ISP_MATRIX_LIGHT_TH_MASK					0x03 // [1:0]

		#define RGB2BAYER_COLOR_ID_MASK						0x18 // [4:3]	// 888
		#define RGB2BAYER_COLOR_ID_BASE						0x08 // [4:3]	// 888
		#define RAWFETCH_COLOR_ID_MASK						0x60 // [6:5]	// 888
		#define RAWFETCH_COLOR_ID_BASE						0x20 // [6:5]	// 888

		#define ISP_RAW_MODE_EN								0x80 // [7]
		/*------------------------------------------------------------*/

#define ISP_FILTER_NR_TH_R				(OFST_R000 + 0x0D)							// NR
#define ISP_FILTER_NR_TH_G				(OFST_R000 + 0x0E)							// NR
#define ISP_FILTER_NR_TH_B				(OFST_R000 + 0x0F)							// NR

#define RGB2BAYER_OFST_R				(OFST_R000 + 0x0D)	// 888
#define RGB2BAYER_OFST_G				(OFST_R000 + 0x0E)	// 888
#define RGB2BAYER_OFST_B				(OFST_R000 + 0x0F)	// 888

#define ISP_AWB_GAIN_R_L				(OFST_R000 + 0x10)
#define ISP_AWB_GAIN_GR_L				(OFST_R000 + 0x11)
#define ISP_AWB_GAIN_GB_L				(OFST_R000 + 0x12)
#define ISP_AWB_GAIN_B_L				(OFST_R000 + 0x13)
#define ISP_AWB_GAIN_RGB_H				(OFST_R000 + 0x14)

#define ISP_AWB_GAIN_R__H				(OFST_R000 + 0x14)	// VV3
#define ISP_AWB_GAIN_GR_H				(OFST_R000 + 0x15)	// VV3
#define ISP_AWB_GAIN_GB_H				(OFST_R000 + 0x16)	// VV3
#define ISP_AWB_GAIN_B__H				(OFST_R000 + 0x17)	// VV3

//HDR Frame0
#define ISP_MERCURY_AWB_GAIN_R_L		(OFST_R000 + 0x10)
#define ISP_MERCURY_AWB_GAIN_R_H		(OFST_R000 + 0x11)
#define ISP_MERCURY_AWB_GAIN_GR_L		(OFST_R000 + 0x12)
#define ISP_MERCURY_AWB_GAIN_GR_H		(OFST_R000 + 0x13)
#define ISP_MERCURY_AWB_GAIN_GB_L		(OFST_R000 + 0x14)
#define ISP_MERCURY_AWB_GAIN_GB_H		(OFST_R000 + 0x15)
#define ISP_MERCURY_AWB_GAIN_B_L		(OFST_R000 + 0x16)
#define ISP_MERCURY_AWB_GAIN_B_H		(OFST_R000 + 0x17)

//HDR Frame1
#define ISP_MERCURY_AWB_F1_GAIN_R_L		(OFST_R000 + 0x18)
#define ISP_MERCURY_AWB_F1_GAIN_R_H		(OFST_R000 + 0x19)
#define ISP_MERCURY_AWB_F1_GAIN_GR_L	(OFST_R000 + 0x1A)
#define ISP_MERCURY_AWB_F1_GAIN_GR_H	(OFST_R000 + 0x1B)
#define ISP_MERCURY_AWB_F1_GAIN_GB_L	(OFST_R000 + 0x1C)
#define ISP_MERCURY_AWB_F1_GAIN_GB_H	(OFST_R000 + 0x1D)
#define ISP_MERCURY_AWB_F1_GAIN_B_L		(OFST_R000 + 0x1E)
#define ISP_MERCURY_AWB_F1_GAIN_B_H		(OFST_R000 + 0x1F)

#define ISP_CCM_GRCM					(OFST_R000 + 0x16)
#define ISP_CCM_OFSTRCM					(OFST_R000 + 0x17)
#define ISP_CCM_GGCM					(OFST_R000 + 0x18)
#define ISP_CCM_OFSTGCM					(OFST_R000 + 0x19)
#define ISP_CCM_GBCM					(OFST_R000 + 0x1A)
#define ISP_CCM_OFSTBCM					(OFST_R000 + 0x1B)
#define ISP_CCM_WR						(OFST_R000 + 0x1C)
#define ISP_CCM_WG						(OFST_R000 + 0x1D)
#define ISP_CCM_WB						(OFST_R000 + 0x1E)

#define	ISP_BLC_SRC_SHIFT				(OFST_R000 + 0x20)
#define	ISP_BLC_OFST_R_L				(OFST_R000 + 0x21)
#define	ISP_BLC_OFST_GR_L				(OFST_R000 + 0x22)
#define	ISP_BLC_OFST_GB_L				(OFST_R000 + 0x23)
#define	ISP_BLC_OFST_B_L				(OFST_R000 + 0x24)
#define	ISP_BLC_OFST_RGB_H				(OFST_R000 + 0x25)

#define	C3A_HIST_WDR_GAIN_0				(OFST_R000 + 0x28)	//8451

#define ISP_COLOR_STG_CTL_0				(OFST_R000 + 0x38)
		/*-DEFINE-----------------------------------------------------*/
		#define ISP_LINE_HP_CHECK_EN						0x00 // [0]
		#define ISP_LINE_HP_CHECK_DIS						0x01 // [0]

		#define ISP_LINE_HP_EN								0x02 // [1]

		#define ISP_CCM_NEW_PATH_SEL_2						0x04 // [2]

		#define ISP_MEAN_EN									0x08 // [3]
		#define ISP_MEAN_EN_2								0x10 // [4]

		#define ISP_CCM_NEW_PATH_SEL						0x20 // [5]

		#define ISP_NR_EN									0x80 // [7]
		/*------------------------------------------------------------*/

#define ISP_NEW_EDGE_CTL				(OFST_R000 + 0x39)
		/*-DEFINE-----------------------------------------------------*/
		#define ISP_SLOPE_SEL_MASK							0x03 // [1:0]

		#define ISP_CANNY_FILTTER__ON_OLD_EDGE				0x10 // [4]
		/*------------------------------------------------------------*/

#define ISP_NEW_EDGE_PEAK_TH_L			(OFST_R000 + 0x3A)
#define ISP_NEW_EDGE_PEAK_TH_H			(OFST_R000 + 0x3B)

#define ISP_HP_CHECK_TH					(OFST_R000 + 0x3C)

#define ISP_HP_LINE_TH					(OFST_R000 + 0x3D)

#define ISP_HP_CORE_0					(OFST_R000 + 0x3E)							// edge
#define ISP_HP_CORE_1					(OFST_R000 + 0x3F)							// edge
		/*-DEFINE-----------------------------------------------------*/
		#define ISP_EMBOSS_MODE_1_EN						0x80 // [7]
		#define ISP_EMBOSS_MODE_2_EN						0x40 // [6]
		/*------------------------------------------------------------*/

#define ISP_HP_CORE_2					(OFST_R000 + 0x40)
		/*-DEFINE-----------------------------------------------------*/
		#define ISP_HP_CORE_NEG_SLOPE_MASK					0x0C // [3:2]
		#define ISP_HP_CORE_POS_SLOPE_MASK					0x03 // [1:0]
		/*------------------------------------------------------------*/

#define ISP_HP_TH						(OFST_R000 + 0x41)

#define ISP_HP_GAIN_H1					(OFST_R000 + 0x42)							// edge
#define ISP_HP_GAIN_H2					(OFST_R000 + 0x43)							// edge
#define ISP_HP_GAIN_V1					(OFST_R000 + 0x44)							// edge

#define ISP_HP_CORE_CONST				(OFST_R000 + 0x45)							// edge
#define ISP_HP_TH_CONST					(OFST_R000 + 0x46)							// edge

#define ISP_HP_TH_SUPPRESS_0			(OFST_R000 + 0x47)							// edge
#define ISP_HP_TH_SUPPRESS_1			(OFST_R000 + 0x48)							// edge

#define ISP_HP_CORE_GAIN_3				(OFST_R000 + 0x49)							// edge
		/*-DEFINE-----------------------------------------------------*/
		#define ISP_OIL_EFFECT_EN							0x80 // [7]
		/*------------------------------------------------------------*/

#define ISP_HP_CORE_GAIN_4				(OFST_R000 + 0x4A)							// edge

#define ISP_HP_V_CTL_0					(OFST_R000 + 0x4B)							// edge
		/*-DEFINE-----------------------------------------------------*/
		#define ISP_HP_H_HP									0x80 // [7]
		#define ISP_HP_H_BP									0x00 // [7]
		/*------------------------------------------------------------*/

#define ISP_HP_V_CTL_1					(OFST_R000 + 0x4C)							// edge
		/*-DEFINE-----------------------------------------------------*/
		#define ISP_HP_V_HP									0x80 // [7]
		#define ISP_HP_V_BP									0x00 // [7]
		/*------------------------------------------------------------*/

#define ISP_HP_V_CTL_2					(OFST_R000 + 0x4D)							// edge
#define ISP_HP_V_CTL_3					(OFST_R000 + 0x4E)							// edge

#define ISP_HP_CTL_4					(OFST_R000 + 0x4F)							// edge
		/*-DEFINE-----------------------------------------------------*/
		#define ISP_HP_10BITS_MODE_EN						0x01 // [0]
		#define ISP_HP_AVG_EN								0x02 // [1]
		#define ISP_EMBOSS_EFFECT_W_EN						0x04 // [2]
		#define ISP_HP_FALSE_W_EN							0x08 // [3]
		/*------------------------------------------------------------*/

#define ISP_EDGE_C1_H					(OFST_R000 + 0x50)							// edge
#define ISP_EDGE_C2_H					(OFST_R000 + 0x51)							// edge

#define ISP_GAMMA_BLOOM_SIGN			(OFST_R000 + 0x52)

#define ISP_EDGE_C0_V					(OFST_R000 + 0x53)							// edge
#define ISP_EDGE_C1_V					(OFST_R000 + 0x54)							// edge
#define ISP_EDGE_C2_V					(OFST_R000 + 0x55)							// edge

#define ISP_EDGE_EC						(OFST_R000 + 0x56)

#define ISP_SUPPRESS_LP_CTL				(OFST_R000 + 0x57)
		/*-DEFINE-----------------------------------------------------*/
		#define ISP_LP_FILTER_EN							0x01 // [0]
		#define ISP_CCM_UV_GAMMA_BYPASS						0x02 // [1]
		/*------------------------------------------------------------*/

#define ISP_SUPPRESS_U_OFST				(OFST_R000 + 0x58)
#define ISP_SUPPRESS_V_OFST				(OFST_R000 + 0x59)

#define ISP_CCM_TABLE11					(OFST_R000 + 0x5A) // 0x5A ~ 0x62
#define ISP_CCM_TABLE_HIGH11			(OFST_R000 + 0x63) // 0x63 ~ 0x65

#define ISP_COLOR_STG_CTL_1				(OFST_R000 + 0x66)
		/*-DEFINE-----------------------------------------------------*/
		#define ISP_GAMMA_OUT_INVERSE_EN					0x10 // [4]

		#define ISP_EDGE_AFTER_GAMMA_EN						0x20 // [5]

		#define ISP_EDGE_BEFORE_GAMMA_EN					0x40 // [6]

		#define ISP_GAMMA_EN								0x80 // [7]
		/*------------------------------------------------------------*/

#define ISP_WHITE_GAIN_R				(OFST_R000 + 0x67)
#define ISP_WHITE_GAIN_G				(OFST_R000 + 0x68)
#define ISP_WHITE_GAIN_B				(OFST_R000 + 0x69)

#define ISP_R_BLOOM						(OFST_R000 + 0x6A)
#define ISP_G_BLOOM						(OFST_R000 + 0x6B)
#define ISP_B_BLOOM						(OFST_R000 + 0x6C)

#define ISP_Y_CONTRAST_GAIN				(OFST_R000 + 0x6D)
#define ISP_Y_BRIGHT_GAIN				(OFST_R000 + 0x6E)

#define ISP_C_HP_GAIN					(OFST_R000 + 0x6F)
		/*-DEFINE-----------------------------------------------------*/
		#define ISP_C_HP_GAIN_DIS							0x10 // [4]
		/*------------------------------------------------------------*/

#define ISP_SRC_COR_U_TH				(OFST_R000 + 0x70)	// 888
#define ISP_SRC_COR_V_TH				(OFST_R000 + 0x71)	// 888

#define ISP_HUE_U_OFST					(OFST_R000 + 0x72)
#define ISP_HUE_V_OFST					(OFST_R000 + 0x73)
#define ISP_UV_CCM11_U_OFST					(OFST_R000 + 0x72) 	// VisionV2
#define ISP_UV_CCM11_V_OFST					(OFST_R000 + 0x73)	// VisionV2

#define ISP_FILTER_SEL_RB				(OFST_R000 + 0x74)							// NR

#define ISP_YUV2YCC_YGAIN				(OFST_R000 + 0x75) // 0x75 ~ 0x7A

#define ISP_L_SHADE_X_RATE				(OFST_R000 + 0x7C)							// luma shading
#define ISP_L_SHADE_Y_RATE				(OFST_R000 + 0x7D)							// luma shading
#define ISP_L_SHADE_X_CENTER			(OFST_R000 + 0x7E)							// luma shading
#define ISP_L_SHADE_Y_CENTER			(OFST_R000 + 0x80)							// luma shading

#define ISP_L_SHADE_CHANGE_R			(OFST_R000 + 0x82)	// 848					// luma shading
#define ISP_L_SHADE_CHANGE_G			(OFST_R000 + 0x83)	// 848					// luma shading
#define ISP_L_SHADE_CHANGE_B			(OFST_R000 + 0x84)	// 848					// luma shading

#define HWISP_L_SHADE_CHANGE_R				(HWOFST_R000 + 0x82)	// 848					// luma shading
#define HWISP_L_SHADE_CHANGE_G				(HWOFST_R000 + 0x83)	// 848					// luma shading
#define HWISP_L_SHADE_CHANGE_B				(HWOFST_R000 + 0x84)	// 848					// luma shading

#define ISP_L_SHADE_CTL					(OFST_R000 + 0x85)							// luma shading
#define ISP_L_SHADE_HWCTL					(HWOFST_R000 + 0x85)							// luma shading
		/*-DEFINE-----------------------------------------------------*/
		#define ISP_L_SHADE_CTL_ENABLE						0x01
		#define ISP_L_SHADE_CTL_RANDOM_TBL_ENABLE			0x02
		#define ISP_L_SHADE_CTL_ORIENTATION_BASE			0x04
		#define ISP_L_SHADE_CTL_ORIENTATION_MASK			0x0C
		#define ISP_L_SHADE_CTL_BANK_MASK					0x30
		#define ISP_L_SHADE_CTL_BANK_0						0x00
		#define ISP_L_SHADE_CTL_BANK_1						0x10
		#define ISP_L_SHADE_CTL_BANK_2						0x20
		#define ISP_L_SHADE_CTL_ACCESS_TBL_SEL				0x40	//mercury
		/*------------------------------------------------------------*/

#define ISP_VV2_L_SHADE_CTL				(OFST_R000 + 0x86)							// luma shading
		/*-DEFINE-----------------------------------------------------*/
		#define ISP_VV2_L_SHADE_CTL_ORIENTATION_BASE		0x01
		#define ISP_VV2_L_SHADE_CTL_ORIENTATION_MASK		0x07
		/*------------------------------------------------------------*/

#define ISP_DE_MOSAIC_T2				(OFST_R000 + 0x86)							// demosaic
#define ISP_DE_MOSAIC_T3				(OFST_R000 + 0x87)							// demosaic

#define ISP_L_SHADE_X_OFFSET			(OFST_R000 + 0x88) // 0x88 ~ 0x89
#define ISP_L_SHADE_Y_OFFSET			(OFST_R000 + 0x8A) // 0x8A ~ 0x8B

#define ISP_L_SHADE_RATE_RGAIN			(OFST_R000 + 0x8C)
#define ISP_L_SHADE_RATE_GGAIN			(OFST_R000 + 0x8D)
#define ISP_L_SHADE_RATE_BGAIN			(OFST_R000 + 0x8E)

#define ISP_MERCURY_L_SHADE_TABLE_CTL	(OFST_R000 + 0x8C) // mercury
		/*-DEFINE-----------------------------------------------------*/
		#define ISP_MERCURY_L_SHADE_TBL0_EN		0x01
		#define ISP_MERCURY_L_SHADE_TBL1_EN		0x02
		/*------------------------------------------------------------*/

#define ISP_MERCURY_L_SHADE_TABLE0_WEIGHT		(OFST_R000 + 0x8D) //mercury
#define ISP_MERCURY_L_SHADE_TABLE1_WEIGHT		(OFST_R000 + 0x8E) //mercury

#define ISP_L_SHADE_GAIN_R				(OFST_R000 + 0x95)
#define ISP_L_SHADE_GAIN_G				(OFST_R000 + 0x96)
#define ISP_L_SHADE_GAIN_B				(OFST_R000 + 0x97)

#define ISP_MATRIX_U_TABLE				(OFST_R000 + 0xA0) // 0xA0 ~ 0xAA
#define ISP_MATRIX_V_TABLE				(OFST_R000 + 0xAB) // 0xAB ~ 0xB5

#define ISP_CCM2_TABLE11				(OFST_R000 + 0xA0) // 0xA0 ~ 0xA8	// 888
#define ISP_CCM2_TABLE_HIGH11			(OFST_R000 + 0xA9) // 0xA9 ~ 0xAB	// 888

#define ISP_CCM_UV_ADJ					(OFST_R000 + 0xAC)	// 888
		/*-DEFINE-----------------------------------------------------*/
		#define ISP_CCM_UV_ADD_MASK							0x1F // [4:0]
		#define ISP_CCM_UV_SHIFT_MASK						0x60 // [6:5]
		#define ISP_CCM_UV_ADJ_EN							0x80 // [7]
		/*------------------------------------------------------------*/

#define ISP_CCM_Y_ADJ					(OFST_R000 + 0xAD)	// 888
		/*-DEFINE-----------------------------------------------------*/
		#define ISP_CCM_Y_ADD_MASK							0x1F // [4:0]
		#define ISP_CCM_Y_SHIFT_MASK						0x60 // [6:5]
		#define ISP_CCM_Y_ADJ_EN							0x80 // [7]
		/*------------------------------------------------------------*/

#define ISP_CCM_W						(OFST_R000 + 0xAE)	// 888
		/*-DEFINE-----------------------------------------------------*/
		#define ISP_CCM_UV_W								0x0F // [3:0]
		#define ISP_CCM_Y_W									0xF0 // [7:4]
		/*------------------------------------------------------------*/

#define ISP_CCM_CTL						(OFST_R000 + 0xAF)	// 888
		/*-DEFINE-----------------------------------------------------*/
		#define ISP_MULTICCM_EN								0x01 // [0]
		/*------------------------------------------------------------*/

#define ISP_EFFECT_CTL					(OFST_R000 + 0xB0)
		/*-DEFINE-----------------------------------------------------*/
		#define ISP_EFFECT_CTL_OFF							0x02 //[1]
		#define ISP_EFFECT_CTL_EN							0x01 //[0]
		/*------------------------------------------------------------*/

#define ISP_EFFECT_UV_CCM11				(OFST_R000 + 0xB2)

#define ISP_MATRIX_UV_CTL				(OFST_R000 + 0xB6)
		/*-DEFINE-----------------------------------------------------*/
		#define ISP_MATRIX_U_SIGN_CTL_MASK					0x03 // [1:0]
		#define ISP_MATRIX_V_SIGN_CTL_MASK					0x0C // [3:2]

		#define ISP_MATRIX_UV_BYPASS						0x10 // [4]

		#define ISP_COLOR_DEPTH_EN							0x20 // [5]
		#define MRGB_EN										0x20 // [5] // 888
		/*------------------------------------------------------------*/

#define ISP_EDGE_MAX_AMP				(OFST_R000 + 0xB7)							// edge

#define ISP_DFT_TH_SM					(OFST_R000 + 0xB8)							// defect

#define ISP_ANTI_CT_CTL					(OFST_R000 + 0xB9)
		/*-DEFINE-----------------------------------------------------*/
		#define ISP_ANTI_CROSSTALK_EN						0x01
		#define ISP_NEW_ANTI_CROSSTALK_EN					0x04

		#define ISP_DEMOSAIC_G_OPTION						0x10
		/*------------------------------------------------------------*/

#define ISP_ANTI_FLARE_CTL				(OFST_R000 + 0xB9)	// 888
		/*-DEFINE-----------------------------------------------------*/
		#define ISP_FIX_R_EN								0x01 // [0]
		#define ISP_FIX_G_EN								0x02 // [1]
		#define ISP_FIX_B_EN								0x04 // [2]
		/*------------------------------------------------------------*/

#define ISP_EXTRA_LINE_NUM				(OFST_R000 + 0xBA)

#define ISP_DE_MOSAIC_THRC				(OFST_R000 + 0xBB)	// 868					// demosaic
#define ISP_DE_MOSAIC_T0				(OFST_R000 + 0xBC)	// 868					// demosaic
#define ISP_DE_MOSAIC_T1				(OFST_R000 + 0xBD)	// 868					// demosaic

#define ISP_FIX_R_VAL					(OFST_R000 + 0xBB)	// 888
#define ISP_FIX_G_VAL					(OFST_R000 + 0xBC)	// 888
#define ISP_FIX_B_VAL					(OFST_R000 + 0xBD)	// 888

#define ISP_FILTER_NR_WEIGHT_RG			(OFST_R000 + 0xBE)							// NR
#define ISP_FILTER_NR_WEIGHT_B			(OFST_R000 + 0xBF)							// NR

#define ISP_FILTER_WEIGHT_N				(OFST_R000 + 0xC0)							// NR
#define ISP_FILTER_MDN_TH_R				(OFST_R000 + 0xC1)							// NR
#define ISP_FILTER_MDN_TH_G				(OFST_R000 + 0xC2)							// NR
#define ISP_FILTER_MDN_TH_B				(OFST_R000 + 0xC3)							// NR

#define ISP_INT_HOST_EN 				(OFST_R000 + 0xC4)
#define ISP_INT_HOST_SR 				(OFST_R000 + 0xC5)
#define ISP_INT_CPU_EN 					(OFST_R000 + 0xC6)
#define ISP_INT_CPU_SR 					(OFST_R000 + 0xC7)
		/*-DEFINE-----------------------------------------------------*/
		#define ISP_INT_FRAME_START							0x01
		#define ISP_INT_AE_ACC_CALC_DONE					0x02	// 888
		#define ISP_INT_AF_ACC_CALC_DONE					0x04	// 888
		#define ISP_INT_AWB_ACC_CALC_DONE					0x08
		#define ISP_INT_FRAME_END							0x10	// 888
		#define MERCURY_ISP_INT_FRAME_END					0x20    //mercury
		/*------------------------------------------------------------*/

#define ISP_ANTI_CROSSTALK_TH 			(OFST_R000 + 0xC8)
#define ISP_ANTI_CROSSTALK_SN 			(OFST_R000 + 0xC9)

#define ISP_DFT_SEL 					(OFST_R000 + 0xCA)
		/*-DEFINE-----------------------------------------------------*/
		#define ISP_DFT_G_SEL_MASK							0x0F
		#define ISP_DFT_RB_SEL_MASK							0xF0
		/*------------------------------------------------------------*/

#define ISP_3D_LUT						(OFST_R000 + 0xCE)
		/*-DEFINE-----------------------------------------------------*/
		#define ISP_3D_LUT_EN								0x01
		#define ISP_3D_LUT_DIS								0x00
		/*------------------------------------------------------------*/

#define ISP_DEMOSAIC_TH2 				(OFST_R000 + 0xE3)
#define ISP_DEMOSAIC_LIMIT3 			(OFST_R000 + 0xE4)

#define ISP_HP_GAIN_V2					(OFST_R000 + 0xE5)							// edge
#define ISP_HP_GAIN_V3					(OFST_R000 + 0xE6)							// edge

#define ISP_MATRIX_GAMMA_CTL			(OFST_R000 + 0xE7)
		/*-DEFINE-----------------------------------------------------*/
		#define ISP_MATRIX_RGB_BYPASS						0x01
		#define ISP_ONLY_YUV								0x02
		#define ISP_Y_GAMMA_ONLY							0x20
		#define ISP_MATRIX_G_SEL_NORMAL						0x00
		#define ISP_MATRIX_G_SEL_OPTION						0x40
		/*------------------------------------------------------------*/

#define ISP_FILTER_SEL_GG				(OFST_R000 + 0xE8)							// NR

#define ISP_DFT_CTL						(OFST_R000 + 0xE9)							// defect
		/*-DEFINE-----------------------------------------------------*/
		#define ISP_AUTO_DFT_EN								0x20
		#define ISP_BYPASS_INVALID_PIXELS					0x10
		/*------------------------------------------------------------*/

#define ISP_RGB2YUV_MASK_R 				(OFST_R000 + 0xEA)
#define ISP_RGB2YUV_MASK_G 				(OFST_R000 + 0xEB)
#define ISP_RGB2YUV_MASK_B 				(OFST_R000 + 0xEC)

#define ISP_DFT_TH_R					(OFST_R000 + 0xED)							// defect
#define ISP_DFT_TH_G					(OFST_R000 + 0xEE)							// defect
#define ISP_DFT_TH_B					(OFST_R000 + 0xEF)							// defect

#define ISP_VV2_ADJUST_UV_CTRL			(OFST_R000 + 0xF0)	// adjust uv : 8451 & 8453

#define ISP_RATE_AVG					(OFST_R000 + 0xF0)	// [3:0]  .0000
#define ISP_RATE_ORG					(OFST_R000 + 0xF1)	// [4:0] 1.0000

#define ISP_LOW_SNR_GAIN_RATIO			(OFST_R000 + 0xF2)	// [3:0]  .1111
#define ISP_LOW_SNR_GAIN_OFFSET			(OFST_R000 + 0xF3)	// [5:0] 000000

#define ISP_Y_OFFSET_BEFORE_GAMMA		(OFST_R000 + 0xF4)
		/*-DEFINE-----------------------------------------------------*/
		#define ISP_Y_OFFSET_BEFORE_GAMMA_POS  				0x00
		#define ISP_Y_OFFSET_BEFORE_GAMMA_NEG  				0x80
		#define ISP_Y_OFFSET_BEFORE_GAMMA_VALUE_MASK		0x7F
		/*------------------------------------------------------------*/

#define ISP_UV_CCM11_MSB				(OFST_R000 + 0xF4) // VisionV2

#define ISP_Y_GAIN_BEFORE_GAMMA			(OFST_R000 + 0xF5) // [6:0] 0x40 = 1x

#define ISP_UV_CCM11_BEFORE_GAMMA		(OFST_R000 + 0xF6) // 0xF6 ~ 0xF9

#define ISP_UV_CCM11_AFTER_GAMMA		(OFST_R000 + 0xFA) // 0xFA ~ 0xFD

#define ISP_CROSS_TALK_EDGE_CMP			(OFST_R000 + 0xFE) // 0x10 = 1x

#define ISP_C3A_AWB_TH					(OFST_R000 + 0xFF)





/*************************************************************************************************/
/* OFST_R100 Register                                                                            */
/*************************************************************************************************/
#define C3A_AF_CTL 						(OFST_R100 + 0x00)	// 848
#define C3A_AF_HWCTL 						(HWOFST_R100 + 0x00)	// 848
		/*-DEFINE-----------------------------------------------------*/
		#define C3A_AF_ACC_EN								0x01
		#define C3A_AF_ALL_WINDOW							0x02
		#define C3A_AF_WIN_READOUT_MASK  					0x70
		/*------------------------------------------------------------*/

#define C3A_ACC_FSYNC_EN				(OFST_R100 + 0x01)
		/*-DEFINE-----------------------------------------------------*/
		#define C3A_ACC_FSYNC_AWB_RAW_EN					0x01
		#define C3A_ACC_FSYNC_AWB_RGB_EN					0x02	// 848
		#define C3A_ACC_FSYNC_AE_EN							0x04	// 848 VV1 VV2
		#define C3A_ACC_FSYNC_AF_EN							0x08	// 848
		#define C3A_ACC_FSYNC_FLICKER_EN					0x08	// 888
		#define C3A_ACC_FSYNC_HIST_EN						0x10
		/*------------------------------------------------------------*/

#define C3A_AF_SUBN						(OFST_R100 + 0x02)	// 848

#define ISP_MXNR8CTL					(OFST_R100 + 0x02)	// vv3
		/*-DEFINE-----------------------------------------------------*/
		#define ISP_MXNR8CTL_EN								0x01
		/*------------------------------------------------------------*/

#define C3A_AF_WINDOW_8_MSB				(OFST_R100 + 0x03)	// 848

#define C3A_AF_WINDOW_8_LEFT			(OFST_R100 + 0x04)	// 848
#define C3A_AF_WINDOW_8_RIGHT			(OFST_R100 + 0x05)	// 848
#define C3A_AF_WINDOW_8_TOP				(OFST_R100 + 0x06)	// 848
#define C3A_AF_WINDOW_8_BOTTOM			(OFST_R100 + 0x07)	// 848

#define C3A_AF_WINDOW_0_MSB				(OFST_R100 + 0x08)	// 848
#define C3A_AF_WINDOW_1_MSB				(OFST_R100 + 0x09)	// 848
#define C3A_AF_WINDOW_2_MSB				(OFST_R100 + 0x0A)	// 848
#define C3A_AF_WINDOW_3_MSB				(OFST_R100 + 0x0B)	// 848
#define C3A_AF_WINDOW_4_MSB				(OFST_R100 + 0x0C)	// 848
#define C3A_AF_WINDOW_5_MSB 			(OFST_R100 + 0x0D)	// 848
#define C3A_AF_WINDOW_6_MSB				(OFST_R100 + 0x0E)	// 848
#define C3A_AF_WINDOW_7_MSB 			(OFST_R100 + 0x0F)	// 848
#define C3A_AF_WINDOW_SIZE 				(OFST_R100 + 0x10) // 0x10 ~ 0x2F	// 848

#define C3A_AE_ACC0_LOWBYTE_VV1			(OFST_R100 + 0x10)	// vision v1
#define C3A_AE_HWACC0_LOWBYTE_VV1			(HWOFST_R100 + 0x10)	// vision v1

#define ISP_UVGAMMA_B32					(OFST_R100 + 0x0F)
#define ISP_UVGAMMA						(OFST_R100 + 0x10) // 0x10 ~ 0x2F

#define BAYERSCALER_OUT_SATRT_X			(OFST_R100 + 0x18) //mercury
#define BAYERSCALER_OUT_END_X			(OFST_R100 + 0x1A)
#define BAYERSCALER_OUT_SATRT_Y			(OFST_R100 + 0x1C)
#define BAYERSCALER_OUT_END_Y			(OFST_R100 + 0x1E)

#define BAYERSCALER_OUT_HWSATRT_X			(HWOFST_R100 + 0x18)
#define BAYERSCALER_OUT_HWEND_X				(HWOFST_R100 + 0x1A)
#define BAYERSCALER_OUT_HWSATRT_Y			(HWOFST_R100 + 0x1C)
#define BAYERSCALER_OUT_HWEND_Y				(HWOFST_R100 + 0x1E)

#define AWB_VV3_ACC_START_X				(OFST_R100 + 0x24) // awb_start_x			// in bayer domain
#define AWB_VV3_ACC_START_Y				(OFST_R100 + 0x26) // awb_start_y			// in bayer domain
#define AWB_VV3_ACC_VALID_X				(OFST_R100 + 0x28) // awb_valid_x[3:0]	// in bayer domain
#define AWB_VV3_ACC_VALID_Y				(OFST_R100 + 0x29) // awb_valid_y[3:0]	// in bayer domain
#define AWB_VV3_ACC_WIN_WIDTH			(OFST_R100 + 0x2A)						// in bayer domain
#define AWB_VV3_ACC_WIN_HEIGHT			(OFST_R100 + 0x2B)						// in bayer domain

#define AWB_VV3_CNT_ACC_ADDR			(OFST_R100 + 0x2C)	// vision
#define AWB_VV3_CH0_ACC_ADDR			(OFST_R100 + 0x30)
#define AWB_VV3_CH1_ACC_ADDR			(OFST_R100 + 0x34)
#define AWB_VV3_CH2_ACC_ADDR			(OFST_R100 + 0x38)
#define AWB_VV3_CH3_ACC_ADDR			(OFST_R100 + 0x3C)
#define HWAWB_VV3_CNT_ACC_ADDR				(HWOFST_R100 + 0x2C)	// vision
#define HWAWB_VV3_CH0_ACC_ADDR				(HWOFST_R100 + 0x30)
#define HWAWB_VV3_CH1_ACC_ADDR				(HWOFST_R100 + 0x34)
#define HWAWB_VV3_CH2_ACC_ADDR				(HWOFST_R100 + 0x38)
#define HWAWB_VV3_CH3_ACC_ADDR				(HWOFST_R100 + 0x3C)

#define C3A_AF_ACC0_LOWBYTE				(OFST_R100 + 0x30)	// 848
#define C3A_AF_HWACC0_LOWBYTE				(HWOFST_R100 + 0x30)	// 848

#define C3A_AWB_CTL						(OFST_R100 + 0x40)
#define C3A_AWB_HWCTL						(HWOFST_R100 + 0x40)
		/*-DEFINE-----------------------------------------------------*/
		#define C3A_AWB_ACC_EN								0x01
		#define C3A_AWB_ALL_WINDOW							0x02
		#define C3A_AWB_ACC_CLEAR    						0x04
		#define C3A_AWB_HI_TH_192							0x00
		#define C3A_AWB_HI_TH_200							0x10
		#define C3A_AWB_HI_TH_208							0x20
		#define C3A_AWB_HI_TH_216							0x30
		#define C3A_AWB_HI_TH_224							0x40
		#define C3A_AWB_HI_TH_232							0x50
		#define C3A_AWB_HI_TH_240							0x60
		#define C3A_AWB_HI_TH_248							0x70
		/*------------------------------------------------------------*/

#define C3A_AWB_DGR						(OFST_R100 + 0x41)
#define C3A_AWB_HWDGR						(HWOFST_R100 + 0x41)
#define C3A_AWB_DGG						(OFST_R100 + 0x42)
#define C3A_AWB_DGB						(OFST_R100 + 0x43)
#define C3A_AWB_UGAIN					(OFST_R100 + 0x44)
#define C3A_AWB_VGAIN					(OFST_R100 + 0x45)
#define C3A_AWB_LOWBND					(OFST_R100 + 0x46)

#define C3A_AWB_OPD_0					(OFST_R100 + 0x47) // 0x147 ~ 0x14A
#define C3A_AWB_HWOPD_0						(HWOFST_R100 + 0x47) // 0x147 ~ 0x14A

#define C3A_AWB_INPUT_DOMAIN			(OFST_R100 + 0x4B)
#define C3A_AWB_HWINPUT_DOMAIN				(HWOFST_R100 + 0x4B)
		/*-DEFINE-----------------------------------------------------*/
		#define C3A_AWB_INPUT_RAW							0x00
		#define C3A_AWB_INPUT_RAW0							0x00
		#define C3A_AWB_INPUT_RAW1							0x01
		#define C3A_AWB_INPUT_RAW2							0x02
		#define C3A_AWB_INPUT_RAW3							0x03
		#define C3A_AWB_INPUT_RAW4							0x04
		#define C3A_AWB_INPUT_RAW5							0x05
		#define C3A_AWB_INPUT_RAW6							0x06
		#define C3A_AWB_INPUT_RAW7							0x07
		#define C3A_AWB_INPUT_RGB							0x08
		#define C3A_FLICKER_ACC_READOUT_MASK				0xF0	// 888
		/*------------------------------------------------------------*/

#define C3A_AWB_OPD_1					(OFST_R100 + 0x4C) // 0x4C ~ 0x4F
#define C3A_AWB_HWOPD_1						(HWOFST_R100 + 0x4C) // 0x4C ~ 0x4F

#define C3A_AWB_WND_BNDL				(OFST_R100 + 0x50)
#define C3A_AWB_HWWND_BNDL					(HWOFST_R100 + 0x50)
#define C3A_AWB_WND_BNDR				(OFST_R100 + 0x51)
#define C3A_AWB_WND_BNDU				(OFST_R100 + 0x52)
#define C3A_AWB_WND_BNDD				(OFST_R100 + 0x53)

#define C3A_AWB_OPD_2					(OFST_R100 + 0x54) // 0x54 ~ 0x57
#define C3A_AWB_HWOPD_2						(HWOFST_R100 + 0x54) // 0x54 ~ 0x57

#define C3A_AWB_OPD_3					(OFST_R100 + 0x5C) // 0x5C ~ 0x5F
#define C3A_AWB_HWOPD_3						(HWOFST_R100 + 0x5C) // 0x5C ~ 0x5F

#define C3A_AWB_ACC_R					(OFST_R100 + 0x60)
#define C3A_AWB_ACC_G					(OFST_R100 + 0x64)
#define C3A_AWB_ACC_B					(OFST_R100 + 0x68)
#define C3A_AWB_ACC_PCNT				(OFST_R100 + 0x6C)

#define C3A_AWB_HWACC_R						(HWOFST_R100 + 0x60)
#define C3A_AWB_HWACC_G						(HWOFST_R100 + 0x64)
#define C3A_AWB_HWACC_B						(HWOFST_R100 + 0x68)
#define C3A_AWB_HWACC_PCNT					(HWOFST_R100 + 0x6C)

#define C3A_AWB_OPD_Y					(OFST_R100 + 0x60)	// 848
#define C3A_AWB_OPD_MG					(OFST_R100 + 0x64)	// 848
#define C3A_AWB_OPD_RB					(OFST_R100 + 0x68)	// 848
#define C3A_AWB_OPD_PIXEL_CNT			(OFST_R100 + 0x6C)	// 848

#define C3A_AWB_HWOPD_Y						(HWOFST_R100 + 0x60)	// 848
#define C3A_AWB_HWOPD_MG					(HWOFST_R100 + 0x64)	// 848
#define C3A_AWB_HWOPD_RB					(HWOFST_R100 + 0x68)	// 848
#define C3A_AWB_HWOPD_PIXEL_CNT				(HWOFST_R100 + 0x6C)	// 848

#define C3A_HIST_CTL 					(OFST_R100 + 0x70)
#define C3A_HIST_HWCTL 						(HWOFST_R100 + 0x70)
		/*-DEFINE-----------------------------------------------------*/
		#define C3A_HIST_ACC_EN								0x01 // [0] and [1] cannot be turned on at the same time
		#define C3A_HIST_FLICKER_ACC_EN						0x02 // [0] and [1] cannot be turned on at the same time
		#define C3A_HIST_ONLY_R_EN							0x04
		#define C3A_HIST_SRC_SEL_AFTER_GAMMA				0x04	// 888
		#define C3A_HIST_Y_EN								0x08    //mercury
		#define C3A_HIST_WIN_READOUT_MASK					0xF0
		#define C3A_WDR_EN									0x10
		/*------------------------------------------------------------*/

#define C3A_HIST_BAND_LINE_NUMBER		(OFST_R100 + 0x71)
#define C3A_FLICKER_OFFSET				(OFST_R100 + 0x72) // 0x72 ~ 0x73[4:0]	// 888

#define MERCURY_C3A_FLICKER_LINE_NUMBER	(OFST_R100 + 0x75) //mercury

#define C3A_FLICKER_DMA_ADDR			(OFST_R100 + 0x78) // Mercury
#define HWC3A_FLICKER_DMA_ADDR				(HWOFST_R100 + 0x78) // Mercury

#define C3A_HIST_WIN_BND				(OFST_R100 + 0x80) // 0x80 ~ 0x8F

//----------------------------------------------------------------------
#define C3A_HIST_WIN_X_STR				(OFST_R100 + 0x80) // 8451
#define C3A_HIST_WIN_X_END				(OFST_R100 + 0x82) // 8451
#define C3A_HIST_WIN_Y_STR				(OFST_R100 + 0x84) // 8451
#define C3A_HIST_WIN_Y_END				(OFST_R100 + 0x86) // 8451
#define C3A_HIST_DMA_ADDR				(OFST_R100 + 0x88) // 8451
#define HWC3A_HIST_DMA_ADDR					(HWOFST_R100 + 0x88) // 8451
#define C3A_HIST_WDR_GAIN_23			(OFST_R100 + 0x8C) // 8451
#define C3A_HIST_WDR_GAIN_32			(OFST_R100 + 0x9E) // 8451
//----------------------------------------------------------------------

#define C3A_HIST_ACC_ADDR				(OFST_R100 + 0x90) // 0x90 ~ 0x9F
#define C3A_HIST_HWACC_ADDR					(HWOFST_R100 + 0x90) // 0x90 ~ 0x9F

#define C3A_AE_CTL 						(OFST_R100 + 0xA0)	// 848
		/*-DEFINE-----------------------------------------------------*/
		#define C3A_AE_ACC_EN								0x01
		#define C3A_AE_ALL_WINDOW							0x02
		#define C3A_AE_RAW_SOURCE							0x00
		#define C3A_AE_SHADE_SOURCE							0x04
		#define C3A_AE_G_ONLY								0x08
		#define C3A_AE_SOURCE_DIV_BASE						0x10
		#define C3A_AE_SOURCE_DIV1							0x00
		#define C3A_AE_SOURCE_DIV2							0x10
		#define C3A_AE_SOURCE_DIV4							0x20
		#define C3A_AE_SOURCE_DIV8							0x30
		#define C3A_AE_HIST_ACC_REST						0x80
		/*------------------------------------------------------------*/

#define C3A_AE_SUBN 					(OFST_R100 + 0xA1)	// 848
		/*-DEFINE-----------------------------------------------------*/
		#define C3A_HIST_SUBN_MASK							0xF0
		#define C3A_AE_SUBN_MASK							0x0F
		/*------------------------------------------------------------*/

#define C3A_HIST_FLICKER_SUBN 			(OFST_R100 + 0xA1)	// vision v1
		/*-DEFINE-----------------------------------------------------*/
		#define C3A_HIST_SUBN_MASK							0xF0
		#define C3A_FLICKER_SUBN_MASK						0x0F
		/*------------------------------------------------------------*/

#define C3A_AE_SUBN_VV1 				(OFST_R100 + 0xA2)	// vision v1
		/*-DEFINE-----------------------------------------------------*/
		#define C3A_AE_SUBN_MASK_VV1						0x0F
		/*------------------------------------------------------------*/

#define C3A_AE_WINDOW_XSIZE				(OFST_R100 + 0xB0)	// 848
#define C3A_AE_WINDOW_YSIZE				(OFST_R100 + 0xB8)	// 848

#define AE_VV3_ACC_START_X				(OFST_R100 + 0xB1) // ae_start_x[7:0]						// in Y domain
#define AE_VV3_ACC_START_Y				(OFST_R100 + 0xB2) // ae_start_y[7:0]						// in Y domain
#define AE_VV3_ACC_START_XY_H			(OFST_R100 + 0xB3) // {ae_start_y[11:8],ae_start_x[11:8]}	// in Y domain
#define AE_VV3_ACC_VALID				(OFST_R100 + 0xB4) // {ae_valid_y[3:0],ae_valid_x[3:0]}
#define AE_VV3_ACC_WIN_WIDTH			(OFST_R100 + 0xB5)										// in Y domain
#define AE_VV3_ACC_WIN_HEIGHT			(OFST_R100 + 0xB6)										// in Y domain

#define AE_VV3_ACC_KR					(OFST_R100 + 0xB7)
#define AE_VV3_ACC_KGR					(OFST_R100 + 0xB8)
#define AE_VV3_ACC_KGB					(OFST_R100 + 0xB9)
#define AE_VV3_ACC_KB					(OFST_R100 + 0xBA)
#define AE_VV3_ACC_K_SBIT				(OFST_R100 + 0xBB) // ae_kr/kgr/kgb/kb sign bit

#define AE_VV3_ACC_ADDR					(OFST_R100 + 0xBC) // 0x0C ~ 0x0F
#define HWAE_VV3_ACC_ADDR					(HWOFST_R100 + 0xBC) // 0x0C ~ 0x0F

#define C3A_AE_ACC0_LOWBYTE				(OFST_R100 + 0xC0)	// 848
#define C3A_AE_HWACC0_LOWBYTE				(HWOFST_R100 + 0xC0)	// 848

#define C3A_FLICKER_ACC_ADDR			(OFST_R100 + 0xC0) // 0xC0 ~ 0xCF	// 888
#define C3A_FLICKER_HWACC_ADDR				(HWOFST_R100 + 0xC0) // 0xC0 ~ 0xCF	// 888

#define C3A_MERCURY_FLICKER_ACC_ADDR	(OFST_R100 + 0x78) // 0x78 ~ 0x7B	//
#define C3A_MERCURY_FLICKER_HWACC_ADDR		(HWOFST_R100 + 0x78) // 0x78 ~ 0x7B	//

#define C3A_AWB_OPD_4					(OFST_R100 + 0xE4) // 0xE4 ~ 0xE7
#define C3A_AWB_OPD_5					(OFST_R100 + 0xE8) // 0xE8 ~ 0xEB
#define C3A_AWB_OPD_6					(OFST_R100 + 0xEC) // 0xEC ~ 0xEF

#define C3A_AWB_HWOPD_4						(HWOFST_R100 + 0xE4) // 0xE4 ~ 0xE7
#define C3A_AWB_HWOPD_5						(HWOFST_R100 + 0xE8) // 0xE8 ~ 0xEB
#define C3A_AWB_HWOPD_6						(HWOFST_R100 + 0xEC) // 0xEC ~ 0xEF

#define C3A_AWB_SUBN					(OFST_R100 + 0xFB)
		/*-DEFINE-----------------------------------------------------*/
		#define C3A_AWB_SUBN_BASE							0x10
		/*------------------------------------------------------------*/

#define C3A_AWB_OPD_7					(OFST_R100 + 0xFC) // 0xFC ~ 0xFF
#define C3A_AWB_HWOPD_7						(HWOFST_R100 + 0xFC) // 0xFC ~ 0xFF





/*************************************************************************************************/
/* OFST_R200 Register                                                                            */
/*************************************************************************************************/
#define CS_SHADE_CTL					(OFST_R200 + 0x00)
#define CS_SHADE_HWCTL						(HWOFST_R200 + 0x00)
		/*-DEFINE-----------------------------------------------------*/
		#define	CS_SHADE_EN									0x01
		#define CS_SHADE_ORIENTATION_BASE					0x02
		#define CS_SHADE_ORIENTATION_MASK					0x06
		#define MERCURY_CS_SHADE_TBL0_EN					0x02
		#define MERCURY_CS_SHADE_TBL1_EN					0x04

		#define CS_SHADE_BANK_MASK							0x70
		#define CS_SHADE_BANK0								0x00
		#define CS_SHADE_BANK1								0x10
		#define CS_SHADE_BANK2								0x20
		#define CS_SHADE_BANK3								0x30
		#define CS_SHADE_BANK4								0x40
		#define CS_SHADE_BANK5								0x50
		#define CS_SHADE_BANK6								0x60
		#define CS_SHADE_BANK7								0x70

		#define CS_SHADE_CTL_ACCESS_TBL_SEL					0x80		//mercury

		#define CS_SHADE_ORIENTATION_BASE2					0x20
		#define CS_SHADE_ORIENTATION_MASK2					0x80
		#define CS_CHANGE_GAIN								0x08	// 848
		/*------------------------------------------------------------*/

#define CS_SHADE_SCALER_RATE 			(OFST_R200 + 0x01)

#define CS_SHADE_X_CENTER 				(OFST_R200 + 0x02)	// [5:0]
#define CS_SHADE_Y_CENTER 				(OFST_R200 + 0x03)	// [5:0]
#define CS_SHADE_OFFSET_X				(OFST_R200 + 0x04)	// 0x04 ~ 0x05
#define CS_SHADE_OFFSET_Y				(OFST_R200 + 0x06)	// 0x06 ~ 0x07

#define MERCURY_CS_SHADE_CTL			(OFST_R200 + 0x08)
#define MERCURY_CS_SHADE_HWCTL				(HWOFST_R200 + 0x08)
		/*-DEFINE-----------------------------------------------------*/
		#define MERCURY_CS_SHADE_ORIENTATION_BASE					0x01
		#define MERCURY_CS_SHADE_ORIENTATION_MASK					0x07
		/*------------------------------------------------------------*/

#define ISP_MERCURY_CS_SHADE_TABLE0_WEIGHT		(OFST_R200 + 0x09) // mercury
#define ISP_MERCURY_CS_SHADE_TABLE1_WEIGHT		(OFST_R200 + 0x0A) // mercury

#define CS_SHADE_X_INDEX_START 			(OFST_R200 + 0x10)	// 0x10 ~ 0x4F		// 32 * 2 bytes
#define CS_SHADE_Y_INDEX_START 			(OFST_R200 + 0x50)	// 0x50 ~ 0x7F		// 24 * 2 bytes

#define ISP_GAMMA_R 					(OFST_R200 + 0x80) // 0x80 ~ 0x9F
#define ISP_GAMMA_G 					(OFST_R200 + 0xA0) // 0xA0 ~ 0xBF
#define ISP_GAMMA_B 					(OFST_R200 + 0xC0) // 0xC0 ~ 0xDF

#define ISP_GAMMA_R00 					(ISP_GAMMA_R)
#define ISP_GAMMA_G00 					(ISP_GAMMA_G)
#define ISP_GAMMA_B00 					(ISP_GAMMA_B)
#define ISP_GAMMA_R32 					(OFST_R200 + 0xE0)
#define ISP_GAMMA_G32 					(OFST_R200 + 0xE1)
#define ISP_GAMMA_B32 					(OFST_R200 + 0xE2)

#define ISP_RGB_ACC_WIN_L				(OFST_R200 + 0xE8) // 0xE8 ~ 0xE9
#define ISP_RGB_ACC_WIN_R				(OFST_R200 + 0xEA) // 0xEA ~ 0xEB
#define ISP_RGB_ACC_WIN_T				(OFST_R200 + 0xEC) // 0xEC ~ 0xED
#define ISP_RGB_ACC_WIN_B				(OFST_R200 + 0xEE) // 0xEE ~ 0xEF

#define ISP_RGB_ACC_R					(OFST_R200 + 0xF0) // 0xF0 ~ 0xF3
#define ISP_RGB_ACC_G					(OFST_R200 + 0xF4) // 0xF4 ~ 0xF6
#define ISP_RGB_ACC_B					(OFST_R200 + 0xF8) // 0xF8 ~ 0xFA

#define ISP_BAYER_GAMMA					(OFST_R300 + 0x20) // 0x20 ~ 0xDB





/*************************************************************************************************/
/* OFST_R300 Register                                                                            */
/*************************************************************************************************/
#define CS_SHADE_X_INDEX_START2 		(OFST_R300 + 0x00)	// 0x00 ~ 0x11		// 9 * 2 bytes
#define CS_SHADE_Y_INDEX_START2 		(OFST_R300 + 0x12)	// 0x12 ~ 0x1F		// 7 * 2 bytes

#define DPCBNR_LIGHT_TH_ADD				(OFST_R300 + 0x20) // 0x20 ~ 0x3F	// 888
#define DPCBNR_DARK_TH_ADD				(OFST_R300 + 0x40) // 0x40 ~ 0x5F	// 888

#define HSVADJ_HUEADJ					(OFST_R300 + 0x60) // 0x60 ~ 0x6B	// 8589
#define HWHSVADJ_HUEADJ						(HWOFST_R300 + 0x60) // 0x60 ~ 0x6B	// 8589

#define HSV_CTL							(OFST_R300 + 0x7B) // 8589
		/*-DEFINE-----------------------------------------------------*/
		#define HSV_CTL_ENABLE								0x01	// 988, 8589

		#define HSV_CTL_TBL_ACCESS_MASK						0x0C	// 8589
		#define HSV_CTL_TBL_ACCESS_SAT_0					0x00	// 8589
		#define HSV_CTL_TBL_ACCESS_VAL_0					0x04	// 8589
		#define HSV_CTL_TBL_ACCESS_SAT_1					0x08	// 8589
		#define HSV_CTL_TBL_ACCESS_VAL_1					0x0C	// 8589

		#define HSV_CTL_TBL_USE_MASK						0x10	// 8589
		#define HSV_CTL_TBL_USE_0							0x00	// 8589
		#define HSV_CTL_TBL_USE_1							0x10	// 8589
		/*------------------------------------------------------------*/

#define RGB2YUV_R11						(OFST_R300 + 0xF0) // Vision V1
#define RGB2YUV_R12						(OFST_R300 + 0xF1)
#define RGB2YUV_R13						(OFST_R300 + 0xF2)
#define RGB2YUV_G21						(OFST_R300 + 0xF4)
#define RGB2YUV_G22						(OFST_R300 + 0xF5)
#define RGB2YUV_G23						(OFST_R300 + 0xF6)
#define RGB2YUV_B31						(OFST_R300 + 0xF8)
#define RGB2YUV_B32						(OFST_R300 + 0xF9)
#define RGB2YUV_B33						(OFST_R300 + 0xFA)
#define RGB2YUV_R_HIGH11				(OFST_R300 + 0xF3)
#define RGB2YUV_G_HIGH11				(OFST_R300 + 0xF7)
#define RGB2YUV_B_HIGH11				(OFST_R300 + 0xFB)

#define AE_ACC_CTL						(OFST_R300 + 0xE0)
#define AE_VV3_ACC_CTL					(OFST_R100 + 0xB0)
		/*-DEFINE-----------------------------------------------------*/
		#define AE_SUBSAMPLE_RATIO_MASK						0x0F

		#define AE_ACC_CTL_EN			  					0x10
		#define AE_ACC_CTL_DIS			  					0x00

		#define AE_ACC_SRC0_ORG								0x00
		#define AE_ACC_SRC1_AFTER_AEGAIN					0x20
		#define AE_ACC_SRC2_AFTER_AWBGAIN					0x40
		#define AE_ACC_SRC3_BEFORE_GAMMMA					0x80
		#define AE_ACC_SRC4_AFTER_GAMMA						0xA0
		/*------------------------------------------------------------*/

#define AE_ACC_START_X					(OFST_R300 + 0xE1) // ae_start_x[7:0]						// in Y domain
#define AE_ACC_START_Y					(OFST_R300 + 0xE2) // ae_start_y[7:0]						// in Y domain
#define AE_ACC_START_XY_H				(OFST_R300 + 0xE3) // {ae_start_y[11:8],ae_start_x[11:8]}	// in Y domain
#define AE_ACC_VALID					(OFST_R300 + 0xE4) // {ae_valid_y[3:0],ae_valid_x[3:0]}
#define AE_ACC_WIN_WIDTH				(OFST_R300 + 0xE5)										// in Y domain
#define AE_ACC_WIN_HEIGHT				(OFST_R300 + 0xE6)										// in Y domain

#define AE_ACC_KR						(OFST_R300 + 0xE7)
#define AE_ACC_KGR						(OFST_R300 + 0xE8)
#define AE_ACC_KGB						(OFST_R300 + 0xE9)
#define AE_ACC_KB						(OFST_R300 + 0xEA)
#define AE_ACC_K_SBIT					(OFST_R300 + 0xEB) // ae_kr/kgr/kgb/kb sign bit

#define AE_ACC_ADDR						(OFST_R300 + 0xEC) // 0x0C ~ 0x0F
#define HWAE_ACC_ADDR						(HWOFST_R300 + 0xEC) // 0x0C ~ 0x0F

#define IRIDIX_BLANK_H					(OFST_R300 + 0xFD) // [7:4]	// 888
#define IRIDIX_BLANK_L					(OFST_R300 + 0xFF) // [7:0]	// 888





/*************************************************************************************************/
/* OFST_R400 Register                                                                            */
/*************************************************************************************************/
#define AF_ACC_CTL						(OFST_R400 + 0x00)
		/*-DEFINE-----------------------------------------------------*/
		#define AF_ACC_IIR_H_EN			  					0x01
		#define AF_ACC_IIR_L_EN			  					0x02
		#define AF_ACC_LUMA_EN			  					0x04
		#define AF_ACC_AIT_V_EN			  					0x08
		#define AF_ACC_AIT_H_EN			  					0x10
		#define AF_ACC_FILTER1X11_EN			  			0x20
		#define AF_ACC_IIR_H_FRAME_CLR_EN			  		0x40
		#define AF_ACC_IIR_L_FRAME_CLR_EN			  		0x80
		#define AF_ACC_ALL_FILTERS_EN			  			0xFF
		#define AF_ACC_ALL_FILTERS_DIS			  			0x00
		/*------------------------------------------------------------*/

#define AF_ACC_SEL						(OFST_R400 + 0x01) // 845
#define HWAF_ACC_SEL						(HWOFST_R400 + 0x01) // 845

#define AF_ACC_ADDR						(OFST_R400 + 0x04) // 0x04 ~ 0x07
#define HWAF_ACC_ADDR						(HWOFST_R400 + 0x04) // 0x04 ~ 0x07

#define AF_ACC_K_SBIT					(OFST_R400 + 0x08) // af_kr/kgr/kgb/kb sign bit
		/*-DEFINE-----------------------------------------------------*/
		#define AF_ACC_SRC0									0x00	// 888
		#define AF_ACC_SRC1									0x20	// 888
		#define AF_ACC_SRC2									0x30	// 888
		/*------------------------------------------------------------*/

#define AF_ACC_KR						(OFST_R400 + 0x09)
#define AF_ACC_KGR						(OFST_R400 + 0x0A)
#define AF_ACC_KGB						(OFST_R400 + 0x0B)
#define AF_ACC_KB						(OFST_R400 + 0x0C)

#define AF_ACC_IIR_H_B1					(OFST_R400 + 0x10)
#define AF_ACC_IIR_H_B2					(OFST_R400 + 0x12)
#define AF_ACC_IIR_H_K					(OFST_R400 + 0x14)

#define MV1_AF_ACC_IIR_H_A0				(OFST_R400 + 0x10)
#define MV1_AF_ACC_IIR_H_A1				(OFST_R400 + 0x11)
#define MV1_AF_ACC_IIR_H_A2				(OFST_R400 + 0x12)
#define MV1_AF_ACC_IIR_H_B1				(OFST_R400 + 0x13)
#define MV1_AF_ACC_IIR_H_B2				(OFST_R400 + 0x14)

#define AF_ACC_IIR_H_IN_LC				(OFST_R400 + 0x16)
#define AF_ACC_IIR_H_IN_HC				(OFST_R400 + 0x18)
#define AF_ACC_IIR_H_OUT_LC				(OFST_R400 + 0x1A)
#define AF_ACC_IIR_H_OUT_HC				(OFST_R400 + 0x1C)

#define AF_ACC_IIR_L_B1					(OFST_R400 + 0x20)
#define AF_ACC_IIR_L_B2					(OFST_R400 + 0x22)
#define AF_ACC_IIR_L_K					(OFST_R400 + 0x24)

#define MV1_AF_ACC_IIR_L_A0				(OFST_R400 + 0x20)
#define MV1_AF_ACC_IIR_L_A1				(OFST_R400 + 0x21)
#define MV1_AF_ACC_IIR_L_A2				(OFST_R400 + 0x22)
#define MV1_AF_ACC_IIR_L_B1				(OFST_R400 + 0x23)
#define MV1_AF_ACC_IIR_L_B2				(OFST_R400 + 0x24)

#define AF_ACC_IIR_L_IN_LC				(OFST_R400 + 0x26)
#define AF_ACC_IIR_L_IN_HC				(OFST_R400 + 0x28)
#define AF_ACC_IIR_L_OUT_LC				(OFST_R400 + 0x2A)
#define AF_ACC_IIR_L_OUT_HC				(OFST_R400 + 0x2C)

#define AF_ACC_LUMA_LC					(OFST_R400 + 0x30)
#define AF_ACC_LUMA_HC					(OFST_R400 + 0x32)

#define AF_ACC_AIT_V_IN_LC				(OFST_R400 + 0x38)
#define AF_ACC_AIT_V_IN_HC				(OFST_R400 + 0x3A)
#define AF_ACC_AIT_V_OUT_LC				(OFST_R400 + 0x3C)
#define AF_ACC_AIT_V_OUT_HC				(OFST_R400 + 0x3E)

#define AF_ACC_AIT_H_IN_LC				(OFST_R400 + 0x40)
#define AF_ACC_AIT_H_IN_HC				(OFST_R400 + 0x42)
#define AF_ACC_AIT_H_OUT_LC				(OFST_R400 + 0x44)
#define AF_ACC_AIT_H_OUT_HC				(OFST_R400 + 0x46)

#define AF_ACC_FILTER1X11_IN_LC			(OFST_R400 + 0x48)
#define AF_ACC_FILTER1X11_IN_HC			(OFST_R400 + 0x4A)
#define AF_ACC_FILTER1X11_OUT_LC		(OFST_R400 + 0x4C)
#define AF_ACC_FILTER1X11_OUT_HC		(OFST_R400 + 0x4E)

// note: end points are not included
// ex. start_x=31 end_x=40 --> window width=9
// ex. start_y=11 end_y=40 --> window height=29
#define AF_ACC_WIN_START_END_H_V		(OFST_R400 + 0x50) // 0x50 ~ 0x9F // in Y domain
#define HWAF_ACC_WIN_START_END_H_V			(HWOFST_R400 + 0x50) // 0x50 ~ 0x9F // in Y domain

#define AF_ACC_FILTER1X11_COEF			(OFST_R400 + 0xA0) // 0xA0 ~ 0xB5
#define AF_ACC_FILTER1X11_SHIFT_N		(OFST_R400 + 0xB6) // 5 bits

#define CI_ORIENT						(OFST_R400 + 0xA0) // [1:0]	// 888
		/*-DEFINE-----------------------------------------------------*/
		#define CI_ORIENT_BASE								0x01
		#define CI_ORIENT_MASK								0x03
		/*------------------------------------------------------------*/

#define CI_OFST_X_L						(OFST_R400 + 0xA1)	// 888
#define CI_OFST_X_H						(OFST_R400 + 0xA2)	// 888
#define CI_OFST_Y_L						(OFST_R400 + 0xA3)	// 888
#define CI_OFST_Y_H						(OFST_R400 + 0xA4)	// 888
#define CI_CNTR_X_L						(OFST_R400 + 0xA5)	// 888
#define CI_CNTR_X_H						(OFST_R400 + 0xA6)	// 888
#define CI_CNTR_Y_L						(OFST_R400 + 0xA7)	// 888
#define CI_CNTR_Y_H						(OFST_R400 + 0xA8)	// 888
#define CI_RATE_X						(OFST_R400 + 0xA9)	// 888
#define CI_RATE_Y						(OFST_R400 + 0xAA)	// 888

#define C3A_AF_ACC_VV2					(OFST_R400 + 0xB0)	// 845
#define HWC3A_AF_ACC_VV2					(HWOFST_R400 + 0xB0)	// 845

#define NEWEDGE_ANTICT					(OFST_R400 + 0xB7)
		/*-DEFINE-----------------------------------------------------*/
		#define NEWEDGE_ANTICT_EN							0x01
		#define NEWEDGE_REF_DIR_EN							0x02
		/*------------------------------------------------------------*/

#define NEWEDGE_BPWH					(OFST_R400 + 0xB8)
#define NEWEDGE_BPWV					(OFST_R400 + 0xB9)
#define NEWEDGE_HPWH					(OFST_R400 + 0xBA)
#define NEWEDGE_HPWV					(OFST_R400 + 0xBB)

#define NEWEDGE_GAIN1					(OFST_R400 + 0xBC)
#define NEWEDGE_GAIN2					(OFST_R400 + 0xBD)
#define NEWEDGE_GAIN3					(OFST_R400 + 0xBE)
#define NEWEDGE_GAIN4					(OFST_R400 + 0xBF)

#define AWB_SUBSAMPLE_RATIO				(OFST_R400 + 0xC0)
#define AWB_VV3_SUBSAMPLE_RATIO			(OFST_R100 + 0x20)
		/*-DEFINE-----------------------------------------------------*/
		#define AWB_SUBSAMPLE_RATIO_MASK					0x0F
		/*------------------------------------------------------------*/

#define AWB_SRC_SEL						(OFST_R400 + 0xC1)
		/*-DEFINE-----------------------------------------------------*/
		#define AWB_SRC_THROUGH_OPD0_EN	  					0x01
		#define AWB_SRC_THROUGH_OPD0_DIS  					0x00
		#define AWB_SRC_MASK		  						0x06
		#define AWB_SRC_BEFORE_LS		  					0x04
		#define AWB_SRC_BEFORE_CS		  					0x06
		#define AWB_SRC_BEFORE_DPC		  					0x00
		/*------------------------------------------------------------*/

#define AWB_ACC_FORMAT					(OFST_R400 + 0xC2)
		/*-DEFINE-----------------------------------------------------*/
		#define AWB_ACC_4CH_FORMAT			  				0x01
		#define AWB_ACC_RGGB_FORMAT			  				0x00
		/*------------------------------------------------------------*/

#define AWB_ACC_CTL						(OFST_R400 + 0xC3)
#define AWB_VV3_ACC_CTL					(OFST_R100 + 0x21)
		/*-DEFINE-----------------------------------------------------*/
		#define AWB_CH0_ACC_CTL_EN			  				0x01
		#define AWB_CH1_ACC_CTL_EN			  				0x02
		#define AWB_CH2_ACC_CTL_EN			  				0x04
		#define AWB_CH3_ACC_CTL_EN			  				0x08
		#define AWB_CNT_ACC_CTL_EN			  				0x10	// 888
		#define AWB_ALL_ACC_CTL_EN			  				0x1F
		#define AWB_ALL_ACC_CTL_DIS			  				0x00
		/*------------------------------------------------------------*/

#define AWB_ACC_START_X					(OFST_R400 + 0xC4) // awb_start_x			// in bayer domain
#define AWB_ACC_START_Y					(OFST_R400 + 0xC6) // awb_start_y			// in bayer domain
#define AWB_ACC_VALID_X					(OFST_R400 + 0xC8) // awb_valid_x[3:0]	// in bayer domain
#define AWB_ACC_VALID_Y					(OFST_R400 + 0xC9) // awb_valid_y[3:0]	// in bayer domain
#define AWB_ACC_WIN_WIDTH				(OFST_R400 + 0xCA)						// in bayer domain
#define AWB_ACC_WIN_HEIGHT				(OFST_R400 + 0xCB)						// in bayer domain

#define AWB_CNT_ACC_ADDR				(OFST_R400 + 0xCC)	// 888
#define AWB_CH0_ACC_ADDR				(OFST_R400 + 0xD0)
#define AWB_CH1_ACC_ADDR				(OFST_R400 + 0xD4)
#define AWB_CH2_ACC_ADDR				(OFST_R400 + 0xD8)
#define AWB_CH3_ACC_ADDR				(OFST_R400 + 0xDC)
#define HWAWB_CNT_ACC_ADDR					(HWOFST_R400 + 0xCC)	// 888
#define HWAWB_CH0_ACC_ADDR					(HWOFST_R400 + 0xD0)
#define HWAWB_CH1_ACC_ADDR					(HWOFST_R400 + 0xD4)
#define HWAWB_CH2_ACC_ADDR					(HWOFST_R400 + 0xD8)
#define HWAWB_CH3_ACC_ADDR					(HWOFST_R400 + 0xDC)

#define CI_DIST_GAIN					(OFST_R400 + 0xE0) // 0xE0 ~ 0xFF	// 888

#define NEWEDGE_SMOOTH11				(OFST_R400 + 0xE0)
#define NEWEDGE_SMOOTH21				(OFST_R400 + 0xE1)
#define NEWEDGE_SMOOTH31				(OFST_R400 + 0xE2)
#define NEWEDGE_SMOOTH41				(OFST_R400 + 0xE3)
#define NEWEDGE_SMOOTH51				(OFST_R400 + 0xE4)
#define NEWEDGE_SMOOTH12				(OFST_R400 + 0xE5)
#define NEWEDGE_SMOOTH22				(OFST_R400 + 0xE6)
#define NEWEDGE_SMOOTH32				(OFST_R400 + 0xE7)
#define NEWEDGE_SMOOTH42				(OFST_R400 + 0xE8)
#define NEWEDGE_SMOOTH52				(OFST_R400 + 0xE9)
#define NEWEDGE_SMOOTH13				(OFST_R400 + 0xEA)
#define NEWEDGE_SMOOTH23				(OFST_R400 + 0xEB)
#define NEWEDGE_SMOOTH33				(OFST_R400 + 0xEC)
#define NEWEDGE_SMOOTH43				(OFST_R400 + 0xED)
#define NEWEDGE_SMOOTH53				(OFST_R400 + 0xEE)
#define NEWEDGE_SMOOTH14				(OFST_R400 + 0xEF)
#define NEWEDGE_SMOOTH24				(OFST_R400 + 0xF0)
#define NEWEDGE_SMOOTH34				(OFST_R400 + 0xF1)
#define NEWEDGE_SMOOTH44				(OFST_R400 + 0xF2)
#define NEWEDGE_SMOOTH54				(OFST_R400 + 0xF3)
#define NEWEDGE_SMOOTH15				(OFST_R400 + 0xF4)
#define NEWEDGE_SMOOTH25				(OFST_R400 + 0xF5)
#define NEWEDGE_SMOOTH35				(OFST_R400 + 0xF6)
#define NEWEDGE_SMOOTH45				(OFST_R400 + 0xF7)
#define NEWEDGE_SMOOTH55				(OFST_R400 + 0xF8)
#define NEWEDGE_SMOOTH_NORM				(OFST_R400 + 0xF9)

#define NEWEDGE_TLOW					(OFST_R400 + 0xFA) // 0xFA ~ 0xFB
#define NEWEDGE_THIGH					(OFST_R400 + 0xFC) // 0xFC ~ 0xFD





/*************************************************************************************************/
/* OFST_R500 Register                                                                            */
/*************************************************************************************************/
#define DPC_CTL							(OFST_R500 + 0x00)
		/*-DEFINE-----------------------------------------------------*/
		#define DPC_CTL_EN									0x01 // [0]
		#define DPC_CTL_MODE_MASK							0x06 // [2:1]
		#define DPC_CTL_LIGHT_EN							0x40 // [6]
		#define DPC_CTL_DARK_EN								0x80 // [7]
		/*------------------------------------------------------------*/

#define DPC_TH_R_L						(OFST_R500 + 0x01) // [7:0]
#define DPC_TH_R_H						(OFST_R500 + 0x02) // [3:0]
#define DPC_TH_GR_L						(OFST_R500 + 0x03) // [7:0]
#define DPC_TH_GR_H						(OFST_R500 + 0x04) // [3:0]
#define DPC_TH_GB_L						(OFST_R500 + 0x05) // [7:0]
#define DPC_TH_GB_H						(OFST_R500 + 0x06) // [3:0]
#define DPC_TH_B_L						(OFST_R500 + 0x07) // [7:0]
#define DPC_TH_B_H						(OFST_R500 + 0x08) // [3:0]

#define DPC_CLUSTER_CTL					(OFST_R500 + 0x09)
		/*-DEFINE-----------------------------------------------------*/
		#define DPC_CLUSTER_CTL_EN							0x01 // [0]
		#define DPC_CLUSTER_CTL_PID							0x02 // [1]
		#define DPC_CLUSTER_CTL_LID							0x04 // [2]
		/*------------------------------------------------------------*/

#define DPC_OTHER_COLOR_RATIO			(OFST_R500 + 0x0A)

#define DPC_ADJ_CTL						(OFST_R500 + 0x0B)
		/*-DEFINE-----------------------------------------------------*/
		#define DPC_TH_SEL_MASK								0x03 // [1:0]
		#define DPC_LIGHT_TH_ADJ							0x04 // [2]
		#define DPC_DARK_TH_ADJ								0x08 // [3]
		/*------------------------------------------------------------*/

#define DPC_LIGHT_CTL					(OFST_R500 + 0x0C)
		/*-DEFINE-----------------------------------------------------*/
		#define DPC_LIGHT_CTL_SRC_MASK						0x0F // [3:0]
		#define DPC_LIGHT_CTL_BASE_MASK						0xF0 // [7:4]
		/*------------------------------------------------------------*/

#define DPC_DARK_CTL					(OFST_R500 + 0x0D)
		/*-DEFINE-----------------------------------------------------*/
		#define DPC_DARK_CTL_SRC_MASK						0x0F // [3:0]
		#define DPC_DARK_CTL_BASE_MASK						0xF0 // [7:4]
		/*------------------------------------------------------------*/

#define BNR_CTL							(OFST_R500 + 0x10)
		/*-DEFINE-----------------------------------------------------*/
		#define BNR_CTL_EN									0x01 // [0]
		#define BNR_CTL_LPF_EN								0x02 // [1]
		/*------------------------------------------------------------*/

#define BNR_LW_L						(OFST_R500 + 0x11)
#define BNR_LW_H						(OFST_R500 + 0x12) // [3:0]

#define BNR_WD							(OFST_R500 + 0x13) // [3:0]

#define BNR_GAIN_ALL					(OFST_R500 + 0x14)
#define BNR_GAIN_DIR					(OFST_R500 + 0x15)

#define BNR_CLIP_L						(OFST_R500 + 0x16)
#define BNR_CLIP_H						(OFST_R500 + 0x17) // [3:0]

#define BNR_DETAIL_LW_L					(OFST_R500 + 0x18)
#define BNR_DETAIL_LW_H					(OFST_R500 + 0x19) // [3:0]

#define BNR_DETAIL_WD					(OFST_R500 + 0x1A)

#define CI_FC_REFEDGE_CTL				(OFST_R500 + 0x20)
		/*-DEFINE-----------------------------------------------------*/
		#define CI_FC_REFEDGE_EN							0x02 // [1]
		#define CI_LPFMODE_EN								0x10 // [4]	: 1 check boundary
		#define CI_LMTBYLUMA_EN								0x40 // [6]
		#define CI_DCRAW_EN									0x80 // [7]
		/*------------------------------------------------------------*/

#define CI_GGOFST						(OFST_R500 + 0x21)

#define CI_FCMSCL						(OFST_R500 + 0x22)
#define CI_FCHSCL						(OFST_R500 + 0x23)
#define MERCURYV2_CI_FCMSCL				(OFST_R500 + 0x23) //8428 mp
#define MERCURYV2_CI_FCHSCL				(OFST_R500 + 0x24) //8428 mp

#define CI_CTL							(OFST_R500 + 0x24)
		/*-DEFINE-----------------------------------------------------*/
		#define CI_CTL_XFC_EN								0x01 // [0]
		#define CI_CTL_YNR_EN								0x02 // [1]
		#define CI_CTL_CNR_EN								0x04 // [2]
		#define CI_CTL_YAA_EN								0x08 // [3]
		#define CI_CTL_LPF_EN								0x10 // [4]
		/*------------------------------------------------------------*/

#define CI_EDGE_TH_L					(OFST_R500 + 0x25)
#define CI_EDGE_TH_H					(OFST_R500 + 0x26) // [3:0]

#define CI_YM_COR						(OFST_R500 + 0x27)
#define CI_YH_COR						(OFST_R500 + 0x28)

#define CI_YM_GAIN						(OFST_R500 + 0x29)
#define CI_YH_GAIN						(OFST_R500 + 0x2A)

#define CI_COR_TBL_BASE					(OFST_R500 + 0x2B) // [3:0]
#define CI_YMHCLIM						(OFST_R500 + 0x2C)
#define CI_YMHCLIP						(OFST_R500 + 0x2D)
#define YNR_DIR_TH_W_L					(OFST_R500 + 0x30)
#define YNR_DIR_TH_W_H					(OFST_R500 + 0x31) // [3:0]

#define YNR_COF_DIR						(OFST_R500 + 0x32)
#define YNR_COF_ALL						(OFST_R500 + 0x33)

#define YNRYEE_YCLIP_L					(OFST_R500 + 0x34)
#define YNRYEE_YCLIP_H					(OFST_R500 + 0x35) // [3:0]

#define YEE_DIR_TH_L					(OFST_R500 + 0x36)
#define YEE_DIR_TH_W					(OFST_R500 + 0x37)

#define YEE_COR_PGAIN					(OFST_R500 + 0x38)
#define YEE_COR_MGAIN					(OFST_R500 + 0x39)

#define YEE_SCL_PGAIN					(OFST_R500 + 0x3A) // 0x3A ~ 0x3B [9:0]
#define YEE_SCL_MGAIN					(OFST_R500 + 0x3C) // 0x3C ~ 0x3D [9:0]

#define YEE_COF_ALL						(OFST_R500 + 0x3E) // 0x3E ~ 0x3F [9:0]
#define YEE_COF_DIR						(OFST_R500 + 0x40) // 0x40 ~ 0x41 [9:0]

#define YNRYEECNR_CTL					(OFST_R500 + 0x42)
		/*-DEFINE-----------------------------------------------------*/
		#define YEE_DTL_EN									0x01 // [0]
		#define EDGE_DETECT_MODE_EN							0x02 // [1]
		#define EYEE_EN                                     0x02 // [1] //Vision V1
		#define YNRYEE_EN									0x04 // [2]
		#define CNR_EN										0x08 // [3]
		/*------------------------------------------------------------*/

#define YEE_DTL_TH_L_L					(OFST_R500 + 0x43)
#define YEE_DTL_TH						(OFST_R500 + 0x44)
		/*-DEFINE-----------------------------------------------------*/
		#define YEE_DTL_TH_L_H_MASK							0x0F // [3:0]
		#define YEE_DTL_TH_W_MASK							0xF0 // [7:4]
		/*------------------------------------------------------------*/

#define CNR_COR_U_TH					(OFST_R500 + 0x45)
#define CNR_COR_V_TH					(OFST_R500 + 0x46)
#define CNR_COEFF_0						(OFST_R500 + 0x47)
#define CNR_COEFF_1						(OFST_R500 + 0x48)
#define CNR_COEFF_2						(OFST_R500 + 0x49)
#define CNR_COEFF_3						(OFST_R500 + 0x4A)
#define CNR_COEFF_4						(OFST_R500 + 0x4B)
#define CNR_COEFF_5						(OFST_R500 + 0x4C)
#define CNR_EDGE_TH						(OFST_R500 + 0x4D)
#define CNR_EDGE_P_RATIO				(OFST_R500 + 0x4E)
#define CNR_EDGE_M_RATIO				(OFST_R500 + 0x4F)

#define COLOR_EFFECT_CTL				(OFST_R500 + 0x50)
		/*-DEFINE-----------------------------------------------------*/
		#define COLOR_EFFECT_CTL_ACCENT_EN					0x01 // [0]
		#define COLOR_EFFECT_CTL_WEAKEN_EN					0x02 // [1]
		#define COLOR_EFFECT_CTL_SWAP_EN					0x04 // [2]
		#define COLOR_EFFECT_CTL_SWAP_Y_EN					0x08 // [3]
		/*------------------------------------------------------------*/

#define COLOR_EFFECT_ACCENT_R_REF		(OFST_R500 + 0x51)
#define COLOR_EFFECT_ACCENT_G_REF		(OFST_R500 + 0x52)
#define COLOR_EFFECT_ACCENT_B_REF		(OFST_R500 + 0x53)
#define COLOR_EFFECT_ACCENT_COS_TH		(OFST_R500 + 0x54)

#define EYEE_WEIGHT_A					(OFST_R500 + 0x54)  //vision v3
#define EYEE_WEIGHT_B					(OFST_R500 + 0x55)  //vision v3

#define COLOR_EFFECT_SWAP_R_REF			(OFST_R500 + 0x55)
#define COLOR_EFFECT_SWAP_G_REF			(OFST_R500 + 0x56)
#define COLOR_EFFECT_SWAP_B_REF			(OFST_R500 + 0x57)
#define COLOR_EFFECT_SWAP_COS_TH		(OFST_R500 + 0x58)

#define COLOR_EFFECT_SWAP_R_SWAP		(OFST_R500 + 0x59)
#define COLOR_EFFECT_SWAP_G_SWAP		(OFST_R500 + 0x5A)
#define COLOR_EFFECT_SWAP_B_SWAP		(OFST_R500 + 0x5B)

#define COLOR_EFFECT_SWAP_Y_TH			(OFST_R500 + 0x5C)

#define EYEE_HPF_GAIN					(OFST_R500 + 0x50) //Vision V1
#define EYEE_BPF_GAIN					(OFST_R500 + 0x51)
#define EYEE_GBL_P_GAIN					(OFST_R500 + 0x52)
#define EYEE_GBL_M_GAIN					(OFST_R500 + 0x53)
#define EYEE_Wa_GAIN					(OFST_R500 + 0x54)
#define EYEE_Wb_GAIN					(OFST_R500 + 0x55)
#define EYEE_EYEE_SFT					(OFST_R500 + 0x56)
#define EYEE_SBL_SFT_X					(OFST_R500 + 0x58)
#define EYEE_SBL_LUT_Y					(OFST_R500 + 0x60)
#define EYEE_COR_SFT_X					(OFST_R500 + 0x68)
#define EYEE_COR_LUT_PY					(OFST_R500 + 0x70)
#define EYEE_COR_LUT_MY					(OFST_R500 + 0x78)
#define EYEE_SCL_SFT_X					(OFST_R500 + 0x80)
#define EYEE_SCL_LUT_PY					(OFST_R500 + 0x88)
#define EYEE_SCL_LUT_MY					(OFST_R500 + 0x90)

#define EDGEACC_CTL						(OFST_R500 + 0x60)
		/*-DEFINE-----------------------------------------------------*/
		#define EDGEACC_CTL_ENABLE							0x01
		/*------------------------------------------------------------*/

#define EDGEACC_START_X_LW				(OFST_R500 + 0x61) // 0x61 ~ 0x62 [12:0]
#define EDGEACC_START_X_HI				(OFST_R500 + 0x62)
#define EDGEACC_END_X_LW				(OFST_R500 + 0x63) // 0x63 ~ 0x64 [12:0]
#define EDGEACC_END_X_HI				(OFST_R500 + 0x64)
#define EDGEACC_START_Y_LW				(OFST_R500 + 0x65) // 0x65 ~ 0x66 [12:0]
#define EDGEACC_START_Y_HI				(OFST_R500 + 0x66)
#define EDGEACC_END_Y_LW				(OFST_R500 + 0x67) // 0x67 ~ 0x68 [12:0]
#define EDGEACC_END_Y_HI				(OFST_R500 + 0x68)

#define EDGEACC_CLIP_IN_HI				(OFST_R500 + 0x69)
#define EDGEACC_CLIP_IN_LW				(OFST_R500 + 0x6A)
#define EDGEACC_CLIP_OUT_HI				(OFST_R500 + 0x6B)
#define EDGEACC_CLIP_OUT_LW				(OFST_R500 + 0x6C)

#define EDGEACC_SUB						(OFST_R500 + 0x6D)
		/*-DEFINE-----------------------------------------------------*/
		#define EDGEACC_SUB_X_MASK							0x0F
		#define EDGEACC_SUB_Y_MASK							0xF0
		/*------------------------------------------------------------*/

#define EDGEACC_H_VAL_LW				(OFST_R500 + 0x70) // 0x70 ~ 0x74
#define EDGEACC_H_VAL_HI				(OFST_R500 + 0x74)
#define HWEDGEACC_H_VAL_LW					(HWOFST_R500 + 0x70)
#define HWEDGEACC_H_VAL_HI					(HWOFST_R500 + 0x74)
#define EDGEACC_V_VAL_LW				(OFST_R500 + 0x78) // 0x78 ~ 0x7C
#define EDGEACC_V_VAL_HI				(OFST_R500 + 0x7C)
#define HWEDGEACC_V_VAL_LW					(HWOFST_R500 + 0x78)
#define HWEDGEACC_V_VAL_HI					(HWOFST_R500 + 0x7C)


#define MERCURYV2_CI_FCCSCL				(OFST_R500 + 0x80) //8428 mp
#define MERCURYV2_CI_FCHSCLP			(OFST_R500 + 0x81) //8428 mp
#define MERCURYV2_CI_FCMSCLP			(OFST_R500 + 0x82) //8428 mp
#define MERCURYV2_CI_FCCSCLP			(OFST_R500 + 0x83) //8428 mp

#define YNRYEE_ORIENT					(OFST_R500 + 0xB0) // [1:0]
		/*-DEFINE-----------------------------------------------------*/
		#define YNRYEE_ORIENT_BASE							0x01
		#define YNRYEE_ORIENT_MASK							0x03
		/*------------------------------------------------------------*/

#define YNRYEE_OFST_X_L					(OFST_R500 + 0xB1)
#define YNRYEE_OFST_X_H					(OFST_R500 + 0xB2) // [4:0]
#define YNRYEE_OFST_Y_L					(OFST_R500 + 0xB3)
#define YNRYEE_OFST_Y_H					(OFST_R500 + 0xB4) // [4:0]
#define YNRYEE_CNTR_X_L					(OFST_R500 + 0xB5)
#define YNRYEE_CNTR_X_H					(OFST_R500 + 0xB6) // [4:0]
#define YNRYEE_CNTR_Y_L					(OFST_R500 + 0xB7)
#define YNRYEE_CNTR_Y_H					(OFST_R500 + 0xB8) // [4:0]
#define YNRYEE_RATE_X					(OFST_R500 + 0xB9)
#define YNRYEE_RATE_Y					(OFST_R500 + 0xBA)

#define YNRYEE_DIST_TBL					(OFST_R500 + 0xC0) // 0xC0 ~ 0xDF (32)

#define MERCURY_ISP_MXNR8CTL			(OFST_R500 + 0xD0) // mercury

#define CNR_SRC_COR_U_TH				(OFST_R500 + 0xE0)
#define CNR_SRC_COR_V_TH				(OFST_R500 + 0xE1)


#define OPR_COLOR_DMA					(OFST_R500 + 0xF0) //Vision V2
#define HWOPR_COLOR_DMA						(HWOFST_R500 + 0xF0) //Vision V2

		/*-DEFINE-----------------------------------------------------*/
		#define OPR_DMA_LS_EN							0x01
		#define OPR_DMA_CS_EN							0x02
		#define OPR_DMA_R0_EN							0x04
		#define OPR_DMA_R1_EN							0x08
		#define OPR_DMA_R2_EN							0x10
		#define OPR_DMA_R3_EN							0x20
		#define OPR_DMA_R4_EN							0x40
		#define OPR_DMA_R5_EN							0x80
		/*------------------------------------------------------------*/

#define OPR_COLOR_DMA1					(OFST_R500 + 0xF1) //Vision V3
#define HWOPR_COLOR_DMA1						(HWOFST_R500 + 0xF1) //Vision V3
		/*-DEFINE-----------------------------------------------------*/
		#define OPR_DMA1_R0_EN							0x01
		#define OPR_DMA1_R1_EN							0x02
		#define OPR_DMA1_R2_EN							0x04
		#define OPR_DMA1_R3_EN							0x08
		#define OPR_DMA1_R4_EN							0x10
		#define OPR_DMA1_R5_EN							0x20
		#define OPR_DMA1_R6_EN							0x40
		#define OPR_DMA1_R7_EN							0x80
		/*------------------------------------------------------------*/

#define LS_DMA_START_ADDR				(OFST_R500 + 0xF4) //Vision V2
#define CS_DMA_START_ADDR				(OFST_R500 + 0xF8) //Vision V2
#define IQ_DMA_START_ADDR				(OFST_R500 + 0xFC) //Vision V2

#define HWLS_DMA_START_ADDR					(HWOFST_R500 + 0xF4) //Vision V2
#define HWCS_DMA_START_ADDR					(HWOFST_R500 + 0xF8) //Vision V2
#define HWIQ_DMA_START_ADDR					(HWOFST_R500 + 0xFC) //Vision V2


/*************************************************************************************************/
/* OFST_R600 Register                                                                            */
/*************************************************************************************************/
#define GNR_CTL 						(OFST_R600 + 0x00)
#define GNR_VV3_CTL 					(OFST_R600 + 0x80)
		/*-DEFINE-----------------------------------------------------*/
		#define GNR_EN										0x01 // [0]
		#define XNR_EN										0x02 // [1]
		#define GNR_GAMMA_EN								0x04 // [2]
		#define GNR_LUMA_GAIN_EN							0x08 // [3]
		#define GNR_ORIENT_BASE								0x10
		#define GNR_ORIENT_MASK								0x30 // [5:4]
		#define GNR_VV3_ORIENT_MASK							0x70 // [6:4]
		#define GNR_DIST_GAIN_EN							0x80 // [7]
		/*------------------------------------------------------------*/

#define MERCURY_WDR_CTL 				(OFST_R600 + 0x00)
		/*-DEFINE-----------------------------------------------------*/
		#define WDR_GAIN_EN									0x01 // [0]
		#define WDR_LGAIN_EN								0x02 // [1]
		#define WDR_VGAIN_EN								0x04 // [2]
		/*------------------------------------------------------------*/

#define MERCURYV2_WDR_CTL 				(OFST_R600 + 0x00)
		/*-DEFINE-----------------------------------------------------*/
		#define WDR_GGAIN_EN								0x01 // [0]
		#define WDR_GGAIN_SMOOTH							0x02 // [1]
		#define WDR_VGAIN_EN								0x04 // [2]
		#define WDR_SGAIN_EN								0x08 // [3]
		/*------------------------------------------------------------*/


#define XNR_TH_U						(OFST_R600 + 0x01)
#define XNR_TH_V						(OFST_R600 + 0x02)
#define XNR_TH_Y						(OFST_R600 + 0x03)
#define CI_FCMSCLP						(OFST_R600 + 0x00) // vv3
#define CI_FCHSCLP						(OFST_R600 + 0x01) // vv3
#define CI_FCCSCL						(OFST_R600 + 0x02) // vv3
#define CI_FCCSCLP						(OFST_R600 + 0x03) // vv3

#define MERCURY_WDR_LGAIN_HI 			(OFST_R600 + 0x02) // 0x02 ~ 0x03
#define MERCURY_WDR_LGAIN_LW 			(OFST_R600 + 0x04) // 0x04 ~ 0x05

#define MERCURY_WDR_VGAIN_UP 			(OFST_R600 + 0x06)
#define MERCURY_WDR_VGAIN_DN 			(OFST_R600 + 0x07)

#define	MERCURY_WDR_GGAIN_0				(OFST_R600 + 0x08) // 0x08 ~ 0x28

#define	MERCURYV2_WDR_GGAIN_0			(OFST_R600 + 0x0E) // 0x0E ~ 0x2F

#define XNR_VV3_TH_U					(OFST_R600 + 0x81)
#define XNR_VV3_TH_V					(OFST_R600 + 0x82)
#define XNR_VV3_TH_Y					(OFST_R600 + 0x83)

#define XNR_SIZE						(OFST_R600 + 0x04)
#define XNR_VV3_SIZE					(OFST_R600 + 0x84)
		/*-DEFINE-----------------------------------------------------*/
		#define XNR_SIZE_MASK								0x0F // [3:0]
		#define XNR_SEL_SIZE_MASK							0xF0 // [7:4]
		/*------------------------------------------------------------*/

#define GNR_DIST_OFST_X_L				(OFST_R600 + 0x05) // [7:0]
#define GNR_DIST_OFST_X_H				(OFST_R600 + 0x06) // [4:0]
#define GNR_DIST_OFST_Y_L				(OFST_R600 + 0x07) // [7:0]
#define GNR_DIST_OFST_Y_H				(OFST_R600 + 0x08) // [4:0]
#define GNR_VV3_DIST_OFST_X_L			(OFST_R600 + 0x85) // [7:0]
#define GNR_VV3_DIST_OFST_X_H			(OFST_R600 + 0x86) // [4:0]
#define GNR_VV3_DIST_OFST_Y_L			(OFST_R600 + 0x87) // [7:0]
#define GNR_VV3_DIST_OFST_Y_H			(OFST_R600 + 0x88) // [4:0]

#define GNR_DIST_CNTR_X_L				(OFST_R600 + 0x09) // [7:0]
#define GNR_DIST_CNTR_X_H				(OFST_R600 + 0x0A) // [4:0]
#define GNR_DIST_CNTR_Y_L				(OFST_R600 + 0x0B) // [7:0]
#define GNR_DIST_CNTR_Y_H				(OFST_R600 + 0x0C) // [4:0]
#define GNR_VV3_DIST_CNTR_X_L			(OFST_R600 + 0x89) // [7:0]
#define GNR_VV3_DIST_CNTR_X_H			(OFST_R600 + 0x8A) // [4:0]
#define GNR_VV3_DIST_CNTR_Y_L			(OFST_R600 + 0x8B) // [7:0]
#define GNR_VV3_DIST_CNTR_Y_H			(OFST_R600 + 0x8C) // [4:0]

#define GNR_DIST_RATE_X					(OFST_R600 + 0x0D)
#define GNR_DIST_RATE_Y					(OFST_R600 + 0x0E)
#define GNR_VV3_DIST_RATE_X				(OFST_R600 + 0x8D)
#define GNR_VV3_DIST_RATE_Y				(OFST_R600 + 0x8E)

#define GNR_DIST_GAIN_0					(OFST_R600 + 0x10) // 0x10 ~ 0x2F

#define GNR_GAMMA_X_0					(OFST_R600 + 0x30) // 0x30 ~ 0x6F
#define GNR_GAMMA_Y_0					(OFST_R600 + 0x70) // 0x70 ~ 0xAF

#define GNR_TRANS_TH					(OFST_R600 + 0xB6) // 0xB6 ~ 0xB7

#define	MERCURY_WDR_LGAIN_MIN_0			(OFST_R600 + 0xB0) // 0xB0 ~ 0xBF
#define	MERCURY_WDR_LGAIN_MAX_0			(OFST_R600 + 0xC0) // 0xC0 ~ 0xCF

#define MERCURY_EYEE_WEIGHT_A			(OFST_R600 + 0xE4) // mercury
#define MERCURY_EYEE_WEIGHT_B			(OFST_R600 + 0xE5) // mercury

#define GNR_TRANS_TBLTH					(OFST_R600 + 0xF0) // 0xF0 ~ 0xF7 vv3




/*************************************************************************************************/
/* OFST_R700 Register                                                                            */
/*************************************************************************************************/
#define CI_W_FC_REFEDGE_CTL				(OFST_R700 + 0x00)
		/*-DEFINE-----------------------------------------------------*/
		#define CI_W_FC_REFEDGE_EN							0x02 // [1]
		/*------------------------------------------------------------*/

#define HSVADJ_SATADJ					(OFST_R700 + 0x00) // 0x00 ~ 0x17	// mv2
#define HWHSVADJ_SATADJ						(HWOFST_R700 + 0x00) // 0x00 ~ 0x17	// mv2
#define HSVADJ_VALADJ					(OFST_R700 + 0x18) // 0x18 ~ 0x2f	// mv2
#define HWHSVADJ_VALADJ						(HWOFST_R700 + 0x18) // 0x18 ~ 0x2f	// mv2
#define CI_W_GGOFST						(OFST_R700 + 0x01)

#define CI_W_FCMSCL						(OFST_R700 + 0x02)
#define CI_W_FCHSCL						(OFST_R700 + 0x03)

#define CI_W_CTL						(OFST_R700 + 0x04)
		/*-DEFINE-----------------------------------------------------*/
		#define CI_W_CTL_XFC_EN								0x01 // [0]
		#define CI_W_CTL_YNR_EN								0x02 // [1]
		#define CI_W_CTL_CNR_EN								0x04 // [2]
		#define CI_W_CTL_YAA_EN								0x08 // [3]
		/*------------------------------------------------------------*/

#define CI_W_EDGE_TH_L					(OFST_R700 + 0x05)
#define CI_W_EDGE_TH_H					(OFST_R700 + 0x06) // [3:0]

#define CI_W_YM_COR						(OFST_R700 + 0x07)
#define CI_W_YH_COR						(OFST_R700 + 0x08)

#define CI_W_YM_GAIN					(OFST_R700 + 0x09)
#define CI_W_YH_GAIN					(OFST_R700 + 0x0A)

#define CI_W_COR_TBL_BASE				(OFST_R700 + 0x0B) // [3:0]
#define CI_W_YMHCLIP					(OFST_R700 + 0x0C)

#define CI_W_ORIENT						(OFST_R700 + 0x10) // [1:0]
		/*-DEFINE-----------------------------------------------------*/
		#define CI_W_ORIENT_BASE							0x01
		#define CI_W_ORIENT_MASK							0x03
		/*------------------------------------------------------------*/

#define CI_W_OFST_X_L					(OFST_R700 + 0x11)
#define CI_W_OFST_X_H					(OFST_R700 + 0x12)
#define CI_W_OFST_Y_L					(OFST_R700 + 0x13)
#define CI_W_OFST_Y_H					(OFST_R700 + 0x14)
#define CI_W_CNTR_X_L					(OFST_R700 + 0x15)
#define CI_W_CNTR_X_H					(OFST_R700 + 0x16)
#define CI_W_CNTR_Y_L					(OFST_R700 + 0x17)
#define CI_W_CNTR_Y_H					(OFST_R700 + 0x18)
#define CI_W_RATE_X						(OFST_R700 + 0x19)
#define CI_W_RATE_Y						(OFST_R700 + 0x1A)

#define CI_W_DIST_GAIN					(OFST_R700 + 0x20) // 0x20 ~ 0x3F

#define YNR_W_DIR_TH_W_L				(OFST_R700 + 0x40)
#define YNR_W_DIR_TH_W_H				(OFST_R700 + 0x41) // [3:0]

#define YNR_W_COF_DIR					(OFST_R700 + 0x42)
#define YNR_W_COF_ALL					(OFST_R700 + 0x43)

#define YNRYEE_W_YCLIP_L				(OFST_R700 + 0x44)
#define YNRYEE_W_YCLIP_H				(OFST_R700 + 0x45) // [3:0]

#define YEE_W_DIR_TH_L					(OFST_R700 + 0x46)
#define YEE_W_DIR_TH_W					(OFST_R700 + 0x47)

#define YEE_W_COR_PGAIN					(OFST_R700 + 0x48)
#define YEE_W_COR_MGAIN					(OFST_R700 + 0x49)

#define YEE_W_SCL_PGAIN					(OFST_R700 + 0x4A) // 0x3A ~ 0x3B [9:0]
#define YEE_W_SCL_MGAIN					(OFST_R700 + 0x4C) // 0x3C ~ 0x3D [9:0]

#define YEE_W_COF_ALL					(OFST_R700 + 0x4E) // 0x3E ~ 0x3F [9:0]
#define YEE_W_COF_DIR					(OFST_R700 + 0x50) // 0x40 ~ 0x41 [9:0]

#define BYAERSCALER_IN_START_H			(OFST_R700 + 0x50)
#define BYAERSCALER_IN_END_H			(OFST_R700 + 0x52)
#define BYAERSCALER_IN_START_V			(OFST_R700 + 0x54)
#define BYAERSCALER_IN_END_V			(OFST_R700 + 0x56)
#define BYAERSCALER_OUT_START_H			(OFST_R700 + 0x58)
#define BYAERSCALER_OUT_END_H			(OFST_R700 + 0x5a)
#define BYAERSCALER_OUT_START_V			(OFST_R700 + 0x5c)
#define BYAERSCALER_OUT_END_V			(OFST_R700 + 0x5e)
#define BYAERSCALER_M_H					(OFST_R700 + 0x60)
#define BYAERSCALER_N_H					(OFST_R700 + 0x62)
#define BYAERSCALER_M_V					(OFST_R700 + 0x64)
#define BYAERSCALER_N_V					(OFST_R700 + 0x66)
#define BYAERSCALER_OFFSET_H			(OFST_R700 + 0x68)
#define BYAERSCALER_OFFSET_V			(OFST_R700 + 0x6A)
#define BYAERSCALER_CTL					(OFST_R700 + 0x6F)
		/*-DEFINE-----------------------------------------------------*/
		#define BYAERSCALER_BYPASS							0x01 // [0]
		/*------------------------------------------------------------*/

#define YNRYEECNR_W_CTL					(OFST_R700 + 0x52)
		/*-DEFINE-----------------------------------------------------*/
		#define YEE_W_DTL_EN								0x01 // [0]
		#define YNRYEE_W_EDGE_DETECT_MODE_EN				0x02 // [1]
		#define YNRYEE_W_EN									0x04 // [2]
		#define YNRYEE_W_YB_DLINE_EN						0x08 // [3]
		#define YNRYEE_W_EDGELVBASE_MASK					0x70 // [6:4]
		/*------------------------------------------------------------*/

#define YEE_W_DTL_TH_L_L				(OFST_R700 + 0x53)
#define YEE_W_DTL_TH					(OFST_R700 + 0x54)
		/*-DEFINE-----------------------------------------------------*/
		#define YEE_W_DTL_TH_L_H_MASK						0x0F // [3:0]
		#define YEE_W_DTL_TH_W_MASK							0xF0 // [7:4]
		/*------------------------------------------------------------*/

#define YNRYEE_W_ORIENT					(OFST_R700 + 0x60) // [1:0]
		/*-DEFINE-----------------------------------------------------*/
		#define YNRYEE_W_ORIENT_BASE						0x01
		#define YNRYEE_W_ORIENT_MASK						0x03
		/*------------------------------------------------------------*/

#define MERCURYV2_FCC_CTL					(OFST_R700 + 0x60) // [0]  //mercuryv2

#define YNRYEE_W_OFST_X_L				(OFST_R700 + 0x61)
#define YNRYEE_W_OFST_X_H				(OFST_R700 + 0x62) // [4:0]
#define YNRYEE_W_OFST_Y_L				(OFST_R700 + 0x63)
#define YNRYEE_W_OFST_Y_H				(OFST_R700 + 0x64) // [4:0]
#define YNRYEE_W_CNTR_X_L				(OFST_R700 + 0x65)
#define YNRYEE_W_CNTR_X_H				(OFST_R700 + 0x66) // [4:0]
#define YNRYEE_W_CNTR_Y_L				(OFST_R700 + 0x67)
#define YNRYEE_W_CNTR_Y_H				(OFST_R700 + 0x68) // [4:0]
#define YNRYEE_W_RATE_X					(OFST_R700 + 0x69)
#define YNRYEE_W_RATE_Y					(OFST_R700 + 0x6A)

#define YNRYEE_W_DIST_TBL				(OFST_R700 + 0x70) // 0x70 ~ 0x8F (32)

#define YDPC_CTL						(OFST_R700 + 0x90)
		/*-DEFINE-----------------------------------------------------*/
		#define YDPC_EN										0x01 // [0]
		#define YDPC_LIGHT_EN								0x02 // [1]
		#define YDPC_DARK_EN								0x04 // [2]
		#define YDPC_BYPASS_DLINE_EN						0x08 // [3]
		#define YDPC_TH_SEL_MASK							0x30 // [5:4]
		#define YDPC_LIGHT_TH_ADJ							0x40 // [6]
		#define YDPC_DARK_TH_ADJ							0x80 // [7]
		/*------------------------------------------------------------*/

#define YDPC_LIGHT_TH					(OFST_R700 + 0x92) // 0x92 ~ 0x93
#define YDPC_DARK_TH					(OFST_R700 + 0x94) // 0x94 ~ 0x95

#define YDPC_COLOR_RATIO				(OFST_R700 + 0x96) // 0x96 ~ 0x97

#define YDPC_LIGHT_CTL					(OFST_R700 + 0x98)
		/*-DEFINE-----------------------------------------------------*/
		#define YDPC_LIGHT_CTL_SRC_MASK						0x0F // [3:0]
		#define YDPC_LIGHT_CTL_BASE_MASK					0xF0 // [7:4]
		/*------------------------------------------------------------*/

#define YDPC_DARK_CTL					(OFST_R700 + 0x99)
		/*-DEFINE-----------------------------------------------------*/
		#define YDPC_DARK_CTL_SRC_MASK						0x0F // [3:0]
		#define YDPC_DARK_CTL_BASE_MASK						0xF0 // [7:4]
		/*------------------------------------------------------------*/

#define YDPC_LIGHT_TH_ADD				(OFST_R700 + 0xA0) // 0xA0 ~ 0xBF
#define YDPC_DARK_TH_ADD				(OFST_R700 + 0xC0) // 0xC0 ~ 0xDF

#define YMIX_CTL						(OFST_R700 + 0xE0)
		/*-DEFINE-----------------------------------------------------*/
		#define YMIX_EN										0x01 // [0]
		#define YMIX_REF_EN									0x02 // [1]
		#define YMIX_LUMA_EN								0x04 // [2]
		#define YMIX_ETC_EN									0x08 // [3]
		/*------------------------------------------------------------*/

#define YMIX_REF_BASE					(OFST_R700 + 0xE1)

#define YMIX_LUMA_SFT					(OFST_R700 + 0xE2)

#define YMIX_WEIGHT						(OFST_R700 + 0xE3)

#define YMIX_WLBD						(OFST_R700 + 0xE4)

#define YMIX_ETC_BASE					(OFST_R700 + 0xE5)
#define YMIX_ETC_SRCBASE				(OFST_R700 + 0xE6)





/*************************************************************************************************/
/* OFST_R800 Register                                                                            */
/*************************************************************************************************/
#define MERCURY_GNR_CTL					(OFST_R800 + 0x00)
		/*-DEFINE-----------------------------------------------------*/
		#define MERCURY_GNR_ORIENT_BASE						0x10
		#define MERCURY_GNR_ORIENT_MASK						0x70
		/*------------------------------------------------------------*/

#define MERCURY_XNR_CTL					(OFST_R800 + 0x01)
		/*-DEFINE-----------------------------------------------------*/
		#define MERCURY_XNR_SEL_SIZE_MASK					0x40 // [6:4]
		/*------------------------------------------------------------*/

#define MERCURY_GNR_BLF_CTL				(OFST_R800 + 0x02)
		/*-DEFINE-----------------------------------------------------*/
		#define MERCURY_BLF_EN							0x01 // [0] mv
		#define MERCURYV2_BLF_DIR_EN					0x01 // [0] mv2 
		#define MERCURYV2_BLF_DIR_DBG					0x02 // [0] mv2 
		/*------------------------------------------------------------*/
#define MERCURYV2_BLF_MASK_SIZE				(OFST_R800 + 0x03)
		/*-DEFINE-----------------------------------------------------*/
		#define MERCURYV2_BLF_MASK_1X1					0x00
		#define MERCURYV2_BLF_MASK_3X3					0x01
		#define MERCURYV2_BLF_MASK_5X5					0x02
		#define MERCURYV2_BLF_MASK_7X7					0x03						
		#define MERCURYV2_BLF_MASK_9X9					0x04								
		/*------------------------------------------------------------*/

#define GNR_MV1_DIST_OFST_X_L			(OFST_R800 + 0x08)
#define GNR_MV1_DIST_OFST_X_H			(OFST_R800 + 0x09)
#define GNR_MV1_DIST_OFST_Y_L			(OFST_R800 + 0x0A)
#define GNR_MV1_DIST_OFST_Y_H			(OFST_R800 + 0x0B)
#define GNR_MV1_DIST_CNTR_X_L			(OFST_R800 + 0x0C)
#define GNR_MV1_DIST_CNTR_X_H			(OFST_R800 + 0x0D)
#define GNR_MV1_DIST_CNTR_Y_L			(OFST_R800 + 0x0E)
#define GNR_MV1_DIST_CNTR_Y_H			(OFST_R800 + 0x0F)
#define GNR_MV1_DIST_RATE_X				(OFST_R800 + 0x15)
#define GNR_MV1_DIST_RATE_Y				(OFST_R800 + 0x16)

#define GNR_TRANSFORM_G					(OFST_R800 + 0x58)  //0x58 ~ 0x5f

#define XNR_MERCURY_TH_U				(OFST_R800 + 0x61)
#define XNR_MERCURY_TH_V				(OFST_R800 + 0x62)
#define XNR_MERCURY_TH_U_BND			(OFST_R800 + 0x63)
#define XNR_MERCURY_TH_V_BND			(OFST_R800 + 0x64)
#define XNR_MERCURY_TH_U_DILATE			(OFST_R800 + 0x65)
#define XNR_MERCURY_TH_V_DILATE			(OFST_R800 + 0x66)


#define XNR_MERCURYV2_TH_Y				(OFST_R800 + 0x72) //mercuryv2mp
#define XNR_MERCURYV2_TH_U				(OFST_R800 + 0x73) //mercuryv2mp
#define XNR_MERCURYV2_TH_V				(OFST_R800 + 0x74) //mercuryv2mp
#define XNR_MERCURYV2_MEDTH_Y			(OFST_R800 + 0x78) //mercuryv2mp
#define XNR_MERCURYV2_MEDTH_U			(OFST_R800 + 0x7A) //mercuryv2mp
#define XNR_MERCURYV2_MEDTH_V			(OFST_R800 + 0x7C) //mercuryv2mp

#define HDR_CTL							(OFST_R800 + 0xD0)
        /*-DEFINE-----------------------------------------------------*/
		#define HDR_FS_CHANGE_FRAME_IDX     0x10
        #define HDR_ACC_SELECT		        0x08	//0: vc0, 1: vc1
        #define HDR_INTERLACE_MODE_EN       0x04
        #define HDR_FRAME_IDX_EN       		0x02	//stagger mode, turn on
        #define HDR_ENABLE        			0x01 
		/*------------------------------------------------------------*/
#define HDR_GAP_PARAM					(OFST_R800 + 0xD1)
        /*-DEFINE-----------------------------------------------------*/
        #define HDR_GAP_PARAM_MASK			0x0F
        /*------------------------------------------------------------*/
#define HDR_THD_PARAM					(OFST_R800 + 0xD2) // 0xD2 ~ 0xD3
        /*-DEFINE-----------------------------------------------------*/
        #define HDR_THD_PARAM_MASK			0x03FF
        /*------------------------------------------------------------*/
#define HDR_RATIO_PARAM					(OFST_R800 + 0xD4) // 0xD4 ~ 0xD5
#define HDR_MAX_X_THD_PARAM				(OFST_R800 + 0xD6) // 0xD6 ~ 0xD7
#define HDR_MAX_Y_THD_PARAM				(OFST_R800 + 0xD8) // 0xD8 ~ 0xD9
#define HDR_MERGE_WIDTH					(OFST_R800 + 0xDA) // 0xDA ~ 0xDB
        /*-DEFINE-----------------------------------------------------*/
        #define HDR_MERGE_WIDTH_MASK		0x1FFF
        /*------------------------------------------------------------*/


/*************************************************************************************************/
/* HSVADJ Register                                                                               */
/*************************************************************************************************/
#define HSVADJ_VAL_ADJ_L				(HSVADJ_TAB_START + 0)
#define HWHSVADJ_VAL_ADJ_L					(HWHSVADJ_TAB_START + 0)
#define HSVADJ_VAL_ADJ_H				(HSVADJ_TAB_START + 48*1)
#define HWHSVADJ_VAL_ADJ_H					(HWHSVADJ_TAB_START + 48*1)
#define HSVADJ_SAT_ADJ_V				(HSVADJ_TAB_START + 48*2)
#define HWHSVADJ_SAT_ADJ_V					(HWHSVADJ_TAB_START + 48*2)
#define HSVADJ_SAT_ADJ_U				(HSVADJ_TAB_START + 48*3)
#define HWHSVADJ_SAT_ADJ_U					(HWHSVADJ_TAB_START + 48*3)
#define HSVADJ_HUE_ADJ					(HSVADJ_TAB_START + 48*4)
#define HWHSVADJ_HUE_ADJ					(HWHSVADJ_TAB_START + 48*4)





#if CHIP_848_COMPATIBLE || CHIP_868_COMPATIBLE || CHIP_988_COMPATIBLE
/*************************************************************************************************/
/* Video-In-Interface (VIF) Register                                                             */
/*************************************************************************************************/
#define VIF_SDC_CTL 					(VIF_OFFSET + 0x12)
		/*-DEFINE-----------------------------------------------------*/
		#define VIF_SDC_EN									0x01
		/*------------------------------------------------------------*/

#define VIF_SENSR_CTL 					(VIF_OFFSET + 0x22)
		/*-DEFINE-----------------------------------------------------*/
		#define VIF_COLOR_ID_MASK							0x0C // [3:2]
		#define VIF_COLOR_ID_BASE							0x04 // [3:2]
		/*------------------------------------------------------------*/

#define VIF_00_ADJST 					(VIF_OFFSET + 0x48)
#define VIF_01_ADJST 					(VIF_OFFSET + 0x49)
#define VIF_10_ADJST 					(VIF_OFFSET + 0x4A)
#define VIF_11_ADJST 					(VIF_OFFSET + 0x4B)

#define VIF_BL_FILTER_CTL				(VIF_OFFSET + 0x70)
		/*-DEFINE-----------------------------------------------------*/
		#define VIF_BL_FILTER_EN							0x01
		/*------------------------------------------------------------*/
#endif // CHIP_848_COMPATIBLE || CHIP_868_COMPATIBLE || CHIP_988_COMPATIBLE





#endif 	// _CHIP_OPR_H_
