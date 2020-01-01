//==============================================================================
//
//  File        : mmpf_hwcounter.c
//  Description : Firmware hw counter
//  Author      : Caesar Chang
//  Revision    : 1.0
//
//==============================================================================

#include "mmpf_hw_counter.h"

//==============================================================================
//
//                              INTERNAL DEFINITIONS
//
//==============================================================================

#define HW_COUNTER_TIMER_ADDR 		AITC_BASE_TC4

//==============================================================================
//
//                              VARIABLES
//
//==============================================================================

// timer input clock source = g0_slow = g0 / 2
static MMP_ULONG ulOsCounterMainClock       = 132000000; // g0 (264MHz) / 2 = 132MHz
static MMP_ULONG ulOsCounterMclkDiv         = 1;
static MMP_ULONG ulOsCounterSecDivider      = 132000000;
static MMP_ULONG ulOsCounterMiliSecDivider  = 132000000 / 1000;

//==============================================================================
//
//                              FUNCTIONS
//
//==============================================================================

//------------------------------------------------------------------------------
//  Function    : MMPF_OsCounterInit
//  Description : 
//------------------------------------------------------------------------------
void MMPF_OsCounterInit(int iDividerType, MMP_BOOL bReset)
{
	MMP_ULONG 	ulG0Clock = 1;

	// MCLK: CPU peripheral clock
	// ¡§0¡¨ : timer clock select MCLK/2
	// ¡§1¡¨ : timer clock select MCLK/8
	// ¡§2¡¨ : timer clock select MCLK/32
	// ¡§3¡¨ : timer clock select MCLK/128
	// ¡§4¡¨ : timer clock select MCLK/1024
	// ¡§5¡¨ : timer clock select MCLK/4
	// ¡§6¡¨ : timer clock select MCLK/16
	// ¡§7¡¨ : timer clock select MCLK/1

	switch (iDividerType)
	{
		case TIMER_CLOCK_SELECT_MCLK_DIV_2   : 	ulOsCounterMclkDiv = 2   ; 	break;
		case TIMER_CLOCK_SELECT_MCLK_DIV_8   : 	ulOsCounterMclkDiv = 8   ; 	break;
		case TIMER_CLOCK_SELECT_MCLK_DIV_32  : 	ulOsCounterMclkDiv = 32  ;  break;
		case TIMER_CLOCK_SELECT_MCLK_DIV_128 : 	ulOsCounterMclkDiv = 128 ; 	break;
		case TIMER_CLOCK_SELECT_MCLK_DIV_1024: 	ulOsCounterMclkDiv = 1024; 	break;
		case TIMER_CLOCK_SELECT_MCLK_DIV_4   : 	ulOsCounterMclkDiv = 4   ; 	break;
		case TIMER_CLOCK_SELECT_MCLK_DIV_16  : 	ulOsCounterMclkDiv = 16  ; 	break;
		case TIMER_CLOCK_SELECT_MCLK_DIV_1   : 	ulOsCounterMclkDiv = 1   ; 	break;
		default                              : 								break;
	}

	//MMPF_PLL_GetGroupFreq(CLK_GRP_GBL, &ulG0Clock);

	ulOsCounterMainClock 		= (ulG0Clock * 1000) >> 1;
	ulOsCounterSecDivider 		= ulOsCounterMainClock / ulOsCounterMclkDiv;
	ulOsCounterMiliSecDivider 	= ulOsCounterMainClock / ulOsCounterMclkDiv / 1000;
}

//------------------------------------------------------------------------------
//  Function    : MMPF_OsCounterGet
//  Description : 
//------------------------------------------------------------------------------
MMP_ULONG MMPF_OsCounterGet(void)
{
    return 0;
}

//------------------------------------------------------------------------------
//  Function    : MMPF_OsCounterGetFreqHz
//  Description : 
//------------------------------------------------------------------------------
MMP_ULONG MMPF_OsCounterGetFreqHz(void)
{
    return ulOsCounterSecDivider;
}

//------------------------------------------------------------------------------
//  Function    : MMPF_OsCounterGetFreqKhz
//  Description : 
//------------------------------------------------------------------------------
MMP_ULONG MMPF_OsCounterGetFreqKhz(void)
{
    return ulOsCounterMiliSecDivider;
}

//------------------------------------------------------------------------------
//  Function    : MMPF_OsCounterGetMs
//  Description : 
//------------------------------------------------------------------------------
MMP_ULONG MMPF_OsCounterGetMs(void)
{
    return 0;
}

//------------------------------------------------------------------------------
//  Function    : MMPF_OsCounterGetUs
//  Description : 
//------------------------------------------------------------------------------
MMP_ULONG MMPF_OsCounterGetUs(void)
{
    return (MMP_ULONG)0;
}

#if 0
#define CCC(X,Y) X##Y
#define DD CCC(CCC(y,f), 100)
#define FF CCC(yf, 100)
int CCC(a,10) = 10;
int CCC(a,b) = 3;
int FF = 6;
int DD = 5;;
void abcd(void)
{
	ab = 4;
	a10 = 2;
	yf100 = 100;
}
#endif
