#ifndef __absExIf_H__
#define __absExIf_H__

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define LEN								13

#define IDC_NULL						99
#define TERMINATE                       100
#define IDD_DIALOG                      101
#define IDI_QP                          103
#define IDI_QP1                         104
#define IDC_BEGIN                       999
#define IDC_0                           1000
#define IDC_1                           1001
#define IDC_2                           1002
#define IDC_3                           1003
#define IDC_4                           1004
#define IDC_5                           1005
#define IDC_6                           1006
#define IDC_7                           1007
#define IDC_8                           1008
#define IDC_9                           1009
#define IDC_1_9                         1010
#define IDC_0_9                         1011
#define IDC_STATE                       1100
#define IDC_POINT                       1101
#define IDC_EQUAL                       1102
#define IDC_EQUALS                      1102
#define IDC_PLUS                        1103
#define IDC_MINUS                       1104
#define IDC_MULT                        1105
#define IDC_DIVIDE                      1106
#define IDC_OPER                        1107
#define IDC_PERCENT                     1108
#define IDC_C                           1109
#define IDC_CE                          1110
#define IDC_DISPLAY                     1111
#define IDC_BRACKET_L					2000
#define IDC_BRACKET_R					2001
#define IDC_AM                 			2002

#define IDC_1x                 			2003	// 1/X
#define IDC_x2                 			2004	// x2
#define IDC_x3                 			2005	// x3
#define IDC_yX                 			2006	// yX
#define IDC_Xf                 			2007	// X!
#define IDC_SQ                 			2008	// ^1/2
#define IDC_xY                 			2009	// ^1/3

#define IDC_Lo                 			2010	// log

#define IDC_Si                 			2011	// sin
#define IDC_Sh                 			2012	// sinh
#define IDC_SA	                 		2013	// sin-
#define IDC_SN	                 		2014	// sinh-

#define IDC_Co                 			2015	// cos
#define IDC_Ch                 			2016	// cosh
#define IDC_CA                  		2017	// cos-
#define IDC_CN	                 		2018	// cosh-

#define IDC_Ta                 			2019	// tan
#define IDC_Th	                 		2020	// tagh-
#define IDC_TA                  		2021	// tg-
#define IDC_TN	                 		2022	// tagh-

#define IDC_Ln                 			2023	// ln
#define IDC_eX                 			2024	// eX
#define IDC_2X                 			2025	// 2X-
#define IDC_L2               			2026	// log2-

#define IDC_Ra                 			2027	// Rand
#define IDC_PI                 			2028	// PI
#define IDC_EE                 			2029	// EE

#define IDC_MC                 			2030	// mc
#define IDC_MPLUS              			2031	// m+
#define IDC_MMINUS                 		2032	// m-
#define IDC_MR	                 		2033	// mr
#define IDC_2ND							2034

#define IDC_BKSPACE						2035	// back space

typedef unsigned char bool;
typedef enum _State {                     /* enumeration for Calc states */
	READY=1, OPERAND1, OPERAND2, OPENTERED, RESULT,BRACKET_R, DELIMITER ,NUL_STATE
} State;

typedef enum _ConstStatus {
	Normal_Status = 1,PI_Status, Rand_Status,Mem_Status, 
} ConstStatus;

typedef struct _CALC_QWERTY_PUBLIC
{
	bool bNumBegins;
	bool bIntDouble;
	double gldRandom;
	double gldMemNum;
	int iMemHavNum;
	int giDegRad;
	char degRad[4];
	char memStr[4];
	ConstStatus subStatus;
	State gState;
	State gSaveState;
	char showStr[LEN];
	char strOptr[4];
	unsigned short giOpe;
	int gIEvent;
}CALC_QWERTY_PUBLIC;

int EventHandle(int iState,int iEvent);
CALC_QWERTY_PUBLIC* GetExtVal(void);

#endif
