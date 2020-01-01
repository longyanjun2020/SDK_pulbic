#ifndef _MMPF_WD_H_
#define _MMPF_WD_H_

//==============================================================================
//
//                              INCLUDE FILE
//
//==============================================================================

//==============================================================================
//
//                              MACRO DEFINE
//
//==============================================================================

#define WD_SOFTWARE_CHECK_TIME (500) //ms

//==============================================================================
//
//                              ENUMERATION
//
//==============================================================================

typedef enum _WD_CLK_DIVIDER {
	WD_CLK_MCK_D8    = 0x00, 
	WD_CLK_MCK_D32,
	WD_CLK_MCK_D128,
	WD_CLK_MCK_D1024
} WD_CLK_DIVIDER;

//==============================================================================
//
//                              STRUCTURES
//
//==============================================================================

typedef void WdCallBackFunc(void);

//==============================================================================
//
//                              FUNCTION PROTOTYPES
//
//==============================================================================

void MMPF_WD_ISR(void);
MMP_ERR MMPF_WD_GetStatus(MMP_ULONG *status);
MMP_ERR MMPF_WD_Initialize(void);
MMP_ERR MMPF_WD_EnableWD(MMP_BOOL bEnable, MMP_BOOL bResetCPU, MMP_BOOL bEnableInterrupt, WdCallBackFunc *CallBackFunc, MMP_BOOL bRestetAllModules);
MMP_ERR MMPF_WD_SetTimeOut(MMP_UBYTE ubCounter, MMP_USHORT clockDiv);
MMP_ERR MMPF_WD_Kick(void);
void MMPF_WD_SW_Kick(void);
MMP_ERR MMPF_WD_SW_EnableWD(MMP_BOOL bEnable, MMP_ULONG ulTimeout);

#endif
