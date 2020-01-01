#ifndef __MMI_CALC_QWERTY_LAYOUT_H__
#define __MMI_CALC_QWERTY_LAYOUT_H__

#define ID0			0
#define ID1			1
#define ID2			2
#define ID3			3
#define ID4			4
#define ID5			5
#define ID6			6
#define ID7			7
#define ID8			8
#define ID9			9
#define ID10		10
#define ID11		11
#define ID12		12
#define ID13		13
#define ID14		14
#define ID15		15
#define ID16		16
#define ID17		17
#define ID18		18
#define ID19		19
#define ID20		20
#define ID21		21
#define ID22		22
#define ID23		23

#if (defined( __LCM_HVGA_320_480_MMI__) || defined( __LCM_LANDSCAPE_HVGA_MMI__))
//	Landscape
//	WND_IMAGE_WDG infer to entire background
//**************************************************************//
//					WND_TEXT_WDG					       		//
//													       		//
//**************************************************************//
//							*									//
//							*									//
//							*									//
//							*		MENU_WDG1					//
//							*									//
//							*									//
//	MENU_WDG/MENU_WDG6	*									//
//							************************************//
//							*		MENU_WDG2		*			//
//							*						*MENU_WDG5	//
//							*************************			//
//							*MENU_WDG3	*MENU_WDG4	*			//
//							*			*			*			//
//**************************************************************//

//	WND_IMAGE_WDG
#define WND_IMAGE_WDG_X         0
#define WND_IMAGE_WDG_Y			0
//	MENU_WDG
#define MENU_WDG_POS_X			3
#define MENU_WDG_POS_Y			87
#define MENU_WDG_SIZE_W			232
#define MENU_WDG_SIZE_H			230
#define MENU_WDG_ITEM_W			52
#define MENU_WDG_ITEM_H			30
#define MENU_WDG_ITEM_ROW		10
#define MENU_WDG_ITEM_COL       8

//MENU_WDG1
#define MENU_WDG1_POS_X			245
#define MENU_WDG1_POS_Y			87
#define MENU_WDG1_SIZE_W		232
#define MENU_WDG1_SIZE_H		150
#define MENU_WDG1_ITEM_W		52
#define MENU_WDG1_ITEM_H		30
#define MENU_WDG1_ITEM_ROW		10
#define MENU_WDG1_ITEM_COL		8
//MENU_WDG2
#define MENU_WDG2_POS_X			245
#define MENU_WDG2_POS_Y			247
#define MENU_WDG2_SIZE_W		172
#define MENU_WDG2_SIZE_H		30
#define MENU_WDG2_ITEM_W		52
#define MENU_WDG2_ITEM_H		30
#define MENU_WDG2_ITEM_COL		8
//MENU_WDG3
#define MENU_WDG3_POS_X			245
#define MENU_WDG3_POS_Y			287
#define MENU_WDG3_SIZE_W		112
#define MENU_WDG3_SIZE_H		30
#define MENU_WDG3_ITEM_W		112
#define MENU_WDG3_ITEM_H		30
//MENU_WDG4
#define MENU_WDG4_POS_X			365
#define MENU_WDG4_POS_Y			287
#define MENU_WDG4_SIZE_W		52
#define MENU_WDG4_SIZE_H		30
#define MENU_WDG4_ITEM_W		52
#define MENU_WDG4_ITEM_H		30
//MENU_WDG5
#define MENU_WDG5_POS_X			425
#define MENU_WDG5_POS_Y			247
#define MENU_WDG5_SIZE_W		52
#define MENU_WDG5_SIZE_H		70
#define MENU_WDG5_ITEM_W		52
#define MENU_WDG5_ITEM_H		70
//MENU_WDG6
#define MENU_WDG6_POS_X			3
#define MENU_WDG6_POS_Y			87
#define MENU_WDG6_SIZE_W		232
#define MENU_WDG6_SIZE_H		230
#define MENU_WDG6_ITEM_W		52
#define MENU_WDG6_ITEM_H		30
#define MENU_WDG6_ITEM_Row		10
#define MENU_WDG6_ITEM_Col		8

//MENU_WDG7
#define MENU_WDG7_POS_X			3
#define MENU_WDG7_POS_Y			287
#define MENU_WDG7_SIZE_W		52
#define MENU_WDG7_SIZE_H		30
#define MENU_WDG7_ITEM_W		52
#define MENU_WDG7_ITEM_H		30
#define MENU_WDG7_ITEM_Row		0
#define MENU_WDG7_ITEM_Col		0

//WND_TEXT_WDG
#define WND_TEXT_WDG_POS_X			58
#define WND_TEXT_WDG_POS_Y			24
#define WND_TEXT_WDG_SIZE_W			416
#define WND_TEXT_WDG_SIZE_H			52

//WND_TEXT_WDG2
#define WND_TEXT_WDG2_POS_X			6
#define WND_TEXT_WDG2_POS_Y			51
#define WND_TEXT_WDG2_SIZE_W		52
#define WND_TEXT_WDG2_SIZE_H		24

//WND_TEXT_MEM_WDG2
#define WND_TEXT_MEM_WDG2_POS_X		6
#define WND_TEXT_MEM_WDG2_POS_Y		5
#define WND_TEXT_MEM_WDG2_SIZE_W	52
#define WND_TEXT_MEM_WDG2_SIZE_H	40

//	PORTRAIT
//	CALC_IMG_COL_BG infer to entire background
//CALCQWERTY_WND_MENU_WDG_COL1
//**************************************************************//
//						WND_TEXT_WDG				       		//
//													       		//
//**************************************************************//
//																//
//																//
//																//
//						MENU_WDG1								//
//																//
//																//
//																//
//**************************************************************//
//						MENU_WDG2		*						//
//										*						//
//***************************************		MENU_WDG5		//
//		MENU_WDG3		* MENU_WDG4		*						//
//						*				*						//
//**************************************************************//

// CALCQWERTY_WND_IMAGE_WDG_COL
#define IMG_COL_BG_POS_X	0
#define IMG_COL_BG_POS_Y	0

//	CALCQWERTY_WND_MENU_WDG_COL1
#define MENU_WDG1_COL_POS_X			10
#define MENU_WDG1_COL_POS_Y			121
#define MENU_WDG1_COL_SIZE_W		300
#define MENU_WDG1_COL_SIZE_H		224
#define MENU_WDG1_COL_ITEM_W		66
#define MENU_WDG1_COL_ITEM_H		41
#define MENU_WDG1_COL_ITEM_ROW		20
#define MENU_WDG1_COL_ITEM_COL		12


//	CALCQWERTY_WND_MENU_WDG_COL2
#define MENU_WDG2_COL_POS_X			10
#define MENU_WDG2_COL_POS_Y			365
#define MENU_WDG2_COL_SIZE_W		222
#define MENU_WDG2_COL_SIZE_H		41
#define MENU_WDG2_COL_ITEM_W		66
#define MENU_WDG2_COL_ITEM_H		41
#define MENU_WDG2_COL_ITEM_COL		12

//	CALCQWERTY_WND_MENU_WDG_COL3
#define MENU_WDG3_COL_POS_X			10
#define MENU_WDG3_COL_POS_Y			426
#define MENU_WDG3_COL_SIZE_W		144
#define MENU_WDG3_COL_SIZE_H		41
#define MENU_WDG3_COL_ITEM_W		144
#define MENU_WDG3_COL_ITEM_H		41

//	CALCQWERTY_WND_MENU_WDG_COL4
#define MENU_WDG4_COL_POS_X			166
#define MENU_WDG4_COL_POS_Y			426
#define MENU_WDG4_COL_SIZE_W		66
#define MENU_WDG4_COL_SIZE_H		41
#define MENU_WDG4_COL_ITEM_W		66
#define MENU_WDG4_COL_ITEM_H		41

//	CALCQWERTY_WND_MENU_WDG_COL5
#define MENU_WDG5_COL_POS_X		244
#define MENU_WDG5_COL_POS_Y		365
#define MENU_WDG5_COL_SIZE_W		66
#define MENU_WDG5_COL_SIZE_H		102
#define MENU_WDG5_COL_ITEM_W			66
#define MENU_WDG5_COL_ITEM_H			102

//	CALCQWERTY_WND_TEXT_WDG_COL1
#define TEXT_WDG_COL_POS_X		26
#define TEXT_WDG_COL_POS_Y		20
#define TEXT_WDG_COL_SIZE_W		270
#define TEXT_WDG_COL_SIZE_H		80

//	CALCQWERTY_WND_TEXT_MEM_WDG_COL1
#define TEXT_MEM_WDG_COL_POS_X		10
#define TEXT_MEM_WDG_COL_POS_Y		20
#define TEXT_MEM_WDG_COL_SIZE_W		16
#define TEXT_MEM_WDG_COL_SIZE_H		80

#elif (defined( __LCM_QVGA_MMI__) || defined( __LCM_LANDSCAPE_QVGA_MMI__))
//	Landscape
//	WND_IMAGE_WDG infer to entire background
//**************************************************************//
//					WND_TEXT_WDG					       		//
//													       		//
//**************************************************************//
//							*									//
//							*									//
//							*									//
//							*		MENU_WDG1					//
//							*									//
//							*									//
//	MENU_WDG/MENU_WDG6	*									//
//							************************************//
//							*		MENU_WDG2		*			//
//							*						*MENU_WDG5	//
//							*************************			//
//							*MENU_WDG3	*MENU_WDG4	*			//
//							*			*			*			//
//**************************************************************//

//	WND_IMAGE_WDG
#define WND_IMAGE_WDG_X         0
#define WND_IMAGE_WDG_Y			0
//	MENU_WDG
#define MENU_WDG_POS_X			2
#define MENU_WDG_POS_Y			54
#define MENU_WDG_SIZE_W			156
#define MENU_WDG_SIZE_H			184
#define MENU_WDG_ITEM_W			36
#define MENU_WDG_ITEM_H			24
#define MENU_WDG_ITEM_ROW		8
#define MENU_WDG_ITEM_COL       4

//MENU_WDG1
#define MENU_WDG1_POS_X			162
#define MENU_WDG1_POS_Y			54
#define MENU_WDG1_SIZE_W		156
#define MENU_WDG1_SIZE_H		120
#define MENU_WDG1_ITEM_W		36
#define MENU_WDG1_ITEM_H		24
#define MENU_WDG1_ITEM_ROW		8
#define MENU_WDG1_ITEM_COL		4
//MENU_WDG2
#define MENU_WDG2_POS_X			162
#define MENU_WDG2_POS_Y			182
#define MENU_WDG2_SIZE_W		116
#define MENU_WDG2_SIZE_H		24
#define MENU_WDG2_ITEM_W		36
#define MENU_WDG2_ITEM_H		24
#define MENU_WDG2_ITEM_COL		4
//MENU_WDG3
#define MENU_WDG3_POS_X			162
#define MENU_WDG3_POS_Y			214
#define MENU_WDG3_SIZE_W		76
#define MENU_WDG3_SIZE_H		24
#define MENU_WDG3_ITEM_W		76
#define MENU_WDG3_ITEM_H		24
//MENU_WDG4
#define MENU_WDG4_POS_X			242
#define MENU_WDG4_POS_Y			214
#define MENU_WDG4_SIZE_W		36
#define MENU_WDG4_SIZE_H		24
#define MENU_WDG4_ITEM_W		36
#define MENU_WDG4_ITEM_H		24
//MENU_WDG5
#define MENU_WDG5_POS_X			282
#define MENU_WDG5_POS_Y			182
#define MENU_WDG5_SIZE_W		36
#define MENU_WDG5_SIZE_H		56
#define MENU_WDG5_ITEM_W		36
#define MENU_WDG5_ITEM_H		56
//MENU_WDG6
#define MENU_WDG6_POS_X			2
#define MENU_WDG6_POS_Y			54
#define MENU_WDG6_SIZE_W		156
#define MENU_WDG6_SIZE_H		184
#define MENU_WDG6_ITEM_W		36
#define MENU_WDG6_ITEM_H		24
#define MENU_WDG6_ITEM_Row		8
#define MENU_WDG6_ITEM_Col		4

//MENU_WDG7
#define MENU_WDG7_POS_X			2
#define MENU_WDG7_POS_Y			214
#define MENU_WDG7_SIZE_W		36
#define MENU_WDG7_SIZE_H		24
#define MENU_WDG7_ITEM_W		36
#define MENU_WDG7_ITEM_H		24
#define MENU_WDG7_ITEM_Row		0
#define MENU_WDG7_ITEM_Col		0

//WND_TEXT_WDG
#define WND_TEXT_WDG_POS_X			48
#define WND_TEXT_WDG_POS_Y			15
#define WND_TEXT_WDG_SIZE_W			264
#define WND_TEXT_WDG_SIZE_H			32

//WND_TEXT_WDG2
#define WND_TEXT_WDG2_POS_X			8
#define WND_TEXT_WDG2_POS_Y			25
#define WND_TEXT_WDG2_SIZE_W		40
#define WND_TEXT_WDG2_SIZE_H		20

//WND_TEXT_MEM_WDG2
#define WND_TEXT_MEM_WDG2_POS_X		6
#define WND_TEXT_MEM_WDG2_POS_Y		8
#define WND_TEXT_MEM_WDG2_SIZE_W	52
#define WND_TEXT_MEM_WDG2_SIZE_H	20


//	PORTRAIT
//	CALC_IMG_COL_BG infer to entire background
//CALCQWERTY_WND_MENU_WDG_COL1
//**************************************************************//
//						WND_TEXT_WDG				       		//
//													       		//
//**************************************************************//
//																//
//																//
//																//
//						MENU_WDG1								//
//																//
//																//
//																//
//**************************************************************//
//						MENU_WDG2		*						//
//										*						//
//***************************************		MENU_WDG5		//
//		MENU_WDG3		* MENU_WDG4		*						//
//						*				*						//
//**************************************************************//

// CALCQWERTY_WND_IMAGE_WDG_COL
#define IMG_COL_BG_POS_X	0
#define IMG_COL_BG_POS_Y	0

//	CALCQWERTY_WND_MENU_WDG_COL1
#define MENU_WDG1_COL_POS_X			8
#define MENU_WDG1_COL_POS_Y			86
#define MENU_WDG1_COL_SIZE_W		224
#define MENU_WDG1_COL_SIZE_H		150
#define MENU_WDG1_COL_ITEM_W		50
#define MENU_WDG1_COL_ITEM_H		33
#define MENU_WDG1_COL_ITEM_ROW		6
#define MENU_WDG1_COL_ITEM_COL		8


//	CALCQWERTY_WND_MENU_WDG_COL2
#define MENU_WDG2_COL_POS_X			8
#define MENU_WDG2_COL_POS_Y			242
#define MENU_WDG2_COL_SIZE_W		166
#define MENU_WDG2_COL_SIZE_H		33
#define MENU_WDG2_COL_ITEM_W		50
#define MENU_WDG2_COL_ITEM_H		33
#define MENU_WDG2_COL_ITEM_COL		8

//	CALCQWERTY_WND_MENU_WDG_COL3
#define MENU_WDG3_COL_POS_X			8
#define MENU_WDG3_COL_POS_Y			281
#define MENU_WDG3_COL_SIZE_W		108
#define MENU_WDG3_COL_SIZE_H		33
#define MENU_WDG3_COL_ITEM_W		108
#define MENU_WDG3_COL_ITEM_H		33

//	CALCQWERTY_WND_MENU_WDG_COL4
#define MENU_WDG4_COL_POS_X			124
#define MENU_WDG4_COL_POS_Y			281
#define MENU_WDG4_COL_SIZE_W		50
#define MENU_WDG4_COL_SIZE_H		33
#define MENU_WDG4_COL_ITEM_W		50
#define MENU_WDG4_COL_ITEM_H		33

//	CALCQWERTY_WND_MENU_WDG_COL5
#define MENU_WDG5_COL_POS_X		    182
#define MENU_WDG5_COL_POS_Y		    242
#define MENU_WDG5_COL_SIZE_W		50
#define MENU_WDG5_COL_SIZE_H		72
#define MENU_WDG5_COL_ITEM_W		50
#define MENU_WDG5_COL_ITEM_H	    72

//	CALCQWERTY_WND_TEXT_WDG_COL1
#define TEXT_WDG_COL_POS_X		8
#define TEXT_WDG_COL_POS_Y		10
#define TEXT_WDG_COL_SIZE_W		220
#define TEXT_WDG_COL_SIZE_H		64

//	CALCQWERTY_WND_TEXT_MEM_WDG_COL1
#define TEXT_MEM_WDG_COL_POS_X		10
#define TEXT_MEM_WDG_COL_POS_Y		10
#define TEXT_MEM_WDG_COL_SIZE_W		16
#define TEXT_MEM_WDG_COL_SIZE_H		40

#elif __LCM_WQVGA_240_400_MMI__

//	Landscape
//	WND_IMAGE_WDG infer to entire background
//**************************************************************//
//					WND_TEXT_WDG					       		//
//													       		//
//**************************************************************//
//							*									//
//							*									//
//							*									//
//							*		MENU_WDG1					//
//							*									//
//							*									//
//	MENU_WDG/MENU_WDG6	*									//
//							************************************//
//							*		MENU_WDG2		*			//
//							*						*MENU_WDG5	//
//							*************************			//
//							*MENU_WDG3	*MENU_WDG4	*			//
//							*			*			*			//
//**************************************************************//

//	WND_IMAGE_WDG
#define WND_IMAGE_WDG_X                 0
#define WND_IMAGE_WDG_Y                 0
//	MENU_WDG
#define MENU_WDG_POS_X			10
#define MENU_WDG_POS_Y			54
#define MENU_WDG_SIZE_W			188
#define MENU_WDG_SIZE_H			184
#define MENU_WDG_ITEM_W			44
#define MENU_WDG_ITEM_H			24
#define MENU_WDG_ITEM_ROW		8
#define MENU_WDG_ITEM_COL       4

//MENU_WDG1
#define MENU_WDG1_POS_X			202
#define MENU_WDG1_POS_Y			54
#define MENU_WDG1_SIZE_W        188
#define MENU_WDG1_SIZE_H        120
#define MENU_WDG1_ITEM_W	    44
#define MENU_WDG1_ITEM_H	    24
#define MENU_WDG1_ITEM_ROW		8
#define MENU_WDG1_ITEM_COL		4
//MENU_WDG2
#define MENU_WDG2_POS_X			202
#define MENU_WDG2_POS_Y			182
#define MENU_WDG2_SIZE_W		140
#define MENU_WDG2_SIZE_H		24
#define MENU_WDG2_ITEM_W		44
#define MENU_WDG2_ITEM_H		24
#define MENU_WDG2_ITEM_COL		4
//MENU_WDG3
#define MENU_WDG3_POS_X			202
#define MENU_WDG3_POS_Y			214
#define MENU_WDG3_SIZE_W		92
#define MENU_WDG3_SIZE_H		24
#define MENU_WDG3_ITEM_W		92
#define MENU_WDG3_ITEM_H		24
//MENU_WDG4
#define MENU_WDG4_POS_X			298
#define MENU_WDG4_POS_Y			214
#define MENU_WDG4_SIZE_W		44
#define MENU_WDG4_SIZE_H		24
#define MENU_WDG4_ITEM_W		44
#define MENU_WDG4_ITEM_H		24
//MENU_WDG5
#define MENU_WDG5_POS_X			346
#define MENU_WDG5_POS_Y			182
#define MENU_WDG5_SIZE_W		44
#define MENU_WDG5_SIZE_H		58
#define MENU_WDG5_ITEM_W		44
#define MENU_WDG5_ITEM_H		58
//MENU_WDG6
#define MENU_WDG6_POS_X			10
#define MENU_WDG6_POS_Y			54
#define MENU_WDG6_SIZE_W		188
#define MENU_WDG6_SIZE_H		184
#define MENU_WDG6_ITEM_W		44
#define MENU_WDG6_ITEM_H		24
#define MENU_WDG6_ITEM_Row		8
#define MENU_WDG6_ITEM_Col		4

//MENU_WDG7
#define MENU_WDG7_POS_X			10
#define MENU_WDG7_POS_Y			214
#define MENU_WDG7_SIZE_W		44
#define MENU_WDG7_SIZE_H		24
#define MENU_WDG7_ITEM_W		44
#define MENU_WDG7_ITEM_H		24
#define MENU_WDG7_ITEM_Row		0
#define MENU_WDG7_ITEM_Col		0

//WND_TEXT_WDG
#define WND_TEXT_WDG_POS_X			56
#define WND_TEXT_WDG_POS_Y			15
#define WND_TEXT_WDG_SIZE_W			328
#define WND_TEXT_WDG_SIZE_H			30

//WND_TEXT_WDG2
#define WND_TEXT_WDG2_POS_X			16
#define WND_TEXT_WDG2_POS_Y			25
#define WND_TEXT_WDG2_SIZE_W		40
#define WND_TEXT_WDG2_SIZE_H		20

//WND_TEXT_MEM_WDG2
#define WND_TEXT_MEM_WDG2_POS_X		12
#define WND_TEXT_MEM_WDG2_POS_Y		12
#define WND_TEXT_MEM_WDG2_SIZE_W	52
#define WND_TEXT_MEM_WDG2_SIZE_H	20

//	PORTRAIT
//	CALC_IMG_COL_BG infer to entire background
//CALCQWERTY_WND_MENU_WDG_COL1
//**************************************************************//
//						WND_TEXT_WDG				       		//
//													       		//
//**************************************************************//
//																//
//																//
//																//
//						MENU_WDG1								//
//																//
//																//
//																//
//**************************************************************//
//						MENU_WDG2		*						//
//										*						//
//***************************************		MENU_WDG5		//
//		MENU_WDG3		* MENU_WDG4		*						//
//						*				*						//
//**************************************************************//

// CALCQWERTY_WND_IMAGE_WDG_COL
#define IMG_COL_BG_POS_X	0
#define IMG_COL_BG_POS_Y	0

//	CALCQWERTY_WND_MENU_WDG_COL1
#define MENU_WDG1_COL_POS_X			8
#define MENU_WDG1_COL_POS_Y			118
#define MENU_WDG1_COL_SIZE_W		224
#define MENU_WDG1_COL_SIZE_H		176
#define MENU_WDG1_COL_ITEM_W		50
#define MENU_WDG1_COL_ITEM_H		35
#define MENU_WDG1_COL_ITEM_ROW		12
#define MENU_WDG1_COL_ITEM_COL		8


//	CALCQWERTY_WND_MENU_WDG_COL2
#define MENU_WDG2_COL_POS_X			8
#define MENU_WDG2_COL_POS_Y			306
#define MENU_WDG2_COL_SIZE_W		166
#define MENU_WDG2_COL_SIZE_H		35
#define MENU_WDG2_COL_ITEM_W		50
#define MENU_WDG2_COL_ITEM_H		35
#define MENU_WDG2_COL_ITEM_COL		8

//	CALCQWERTY_WND_MENU_WDG_COL3
#define MENU_WDG3_COL_POS_X			8
#define MENU_WDG3_COL_POS_Y			353
#define MENU_WDG3_COL_SIZE_W		108
#define MENU_WDG3_COL_SIZE_H		35
#define MENU_WDG3_COL_ITEM_W		108
#define MENU_WDG3_COL_ITEM_H		35

//	CALCQWERTY_WND_MENU_WDG_COL4
#define MENU_WDG4_COL_POS_X			124
#define MENU_WDG4_COL_POS_Y			353
#define MENU_WDG4_COL_SIZE_W		50
#define MENU_WDG4_COL_SIZE_H		35
#define MENU_WDG4_COL_ITEM_W		50
#define MENU_WDG4_COL_ITEM_H		35

//	CALCQWERTY_WND_MENU_WDG_COL5
#define MENU_WDG5_COL_POS_X		    182
#define MENU_WDG5_COL_POS_Y		    306
#define MENU_WDG5_COL_SIZE_W		50
#define MENU_WDG5_COL_SIZE_H		82
#define MENU_WDG5_COL_ITEM_W		50
#define MENU_WDG5_COL_ITEM_H		82

//	CALCQWERTY_WND_TEXT_WDG_COL1
#define TEXT_WDG_COL_POS_X		16
#define TEXT_WDG_COL_POS_Y		26
#define TEXT_WDG_COL_SIZE_W		208
#define TEXT_WDG_COL_SIZE_H		64

//	CALCQWERTY_WND_TEXT_MEM_WDG_COL1
#define TEXT_MEM_WDG_COL_POS_X		12
#define TEXT_MEM_WDG_COL_POS_Y		12
#define TEXT_MEM_WDG_COL_SIZE_W		16
#define TEXT_MEM_WDG_COL_SIZE_H		40
#endif

#endif
