//==============================================================================
//
//  File        : mmph_hif.h
//  Description : INCLUDE File for the Host DSC Driver.
//  Author      : Penguin Torng
//  Revision    : 1.0
//
//==============================================================================

#ifndef _MMPH_HIF_H_
#define _MMPH_HIF_H_

//==============================================================================
//
//                              INCLUDE FILE
//
//==============================================================================

#include "mmp_lib.h"
#ifdef BUILD_CE
#include "config_fw.h"
#endif
#include "mmp_hif_cmd.h"

/** @addtogroup MMPH_reg
@{
*/

//==============================================================================
//
//                              EXTERN VARIABLE
//
//==============================================================================

extern MMP_ULONG    m_ulHifCmd[GRP_IDX_NUM];
extern MMP_ULONG    m_ulHifParam[GRP_IDX_NUM][MAX_HIF_ARRAY_SIZE];

//==============================================================================
//
//                              FUNCTION PROTOTYPES
//
//==============================================================================

MMP_UBYTE   Ind_RegGetB(MMP_ULONG ulAddr);
MMP_USHORT  Ind_RegGetW(MMP_ULONG ulAddr);
MMP_ULONG   Ind_RegGetL(MMP_ULONG ulAddr);
void        Ind_RegSetB(MMP_ULONG ulAddr, MMP_UBYTE ubData);
void        Ind_RegSetW(MMP_ULONG ulAddr, MMP_USHORT usData);
void        Ind_RegSetL(MMP_ULONG ulAddr, MMP_ULONG ulData);
MMP_UBYTE   Ind_MemGetB(MMP_ULONG ulAddr);
MMP_USHORT  Ind_MemGetW(MMP_ULONG ulAddr);
MMP_ULONG   Ind_MemGetL(MMP_ULONG ulAddr);
void        Ind_MemSetB(MMP_ULONG ulAddr, MMP_UBYTE ubData);
void        Ind_MemSetW(MMP_ULONG ulAddr, MMP_USHORT usData);
void        Ind_MemSetL(MMP_ULONG ulAddr, MMP_ULONG ulData);

MMP_ERR MMPH_HIF_SetInterface(void);

#ifdef  AIT_REG_FUNC_DECLARE
MMP_UBYTE   (*MMPH_HIF_RegGetB)(MMP_ULONG ulAddr);
MMP_USHORT  (*MMPH_HIF_RegGetW)(MMP_ULONG ulAddr);
MMP_ULONG   (*MMPH_HIF_RegGetL)(MMP_ULONG ulAddr);
void        (*MMPH_HIF_RegSetB)(MMP_ULONG ulAddr, MMP_UBYTE ubData);
void        (*MMPH_HIF_RegSetW)(MMP_ULONG ulAddr, MMP_USHORT usData);
void        (*MMPH_HIF_RegSetL)(MMP_ULONG ulAddr, MMP_ULONG ulData);

MMP_UBYTE   (*MMPH_HIF_MemGetB)(MMP_ULONG ulAddr);
MMP_USHORT  (*MMPH_HIF_MemGetW)(MMP_ULONG ulAddr);
MMP_ULONG   (*MMPH_HIF_MemGetL)(MMP_ULONG ulAddr);
void        (*MMPH_HIF_MemSetB)(MMP_ULONG ulAddr, MMP_UBYTE ubData);
void        (*MMPH_HIF_MemSetW)(MMP_ULONG ulAddr, MMP_USHORT usData);
void        (*MMPH_HIF_MemSetL)(MMP_ULONG ulAddr, MMP_ULONG ulData);
#else
extern  MMP_UBYTE   (*MMPH_HIF_RegGetB)(MMP_ULONG ulAddr);
extern  MMP_USHORT  (*MMPH_HIF_RegGetW)(MMP_ULONG ulAddr);
extern  MMP_ULONG   (*MMPH_HIF_RegGetL)(MMP_ULONG ulAddr);
extern  void        (*MMPH_HIF_RegSetB)(MMP_ULONG ulAddr, MMP_UBYTE ubData);
extern  void        (*MMPH_HIF_RegSetW)(MMP_ULONG ulAddr, MMP_USHORT usData);
extern  void        (*MMPH_HIF_RegSetL)(MMP_ULONG ulAddr, MMP_ULONG ulData);

extern  MMP_UBYTE   (*MMPH_HIF_MemGetB)(MMP_ULONG ulAddr);
extern  MMP_USHORT  (*MMPH_HIF_MemGetW)(MMP_ULONG ulAddr);
extern  MMP_ULONG   (*MMPH_HIF_MemGetL)(MMP_ULONG ulAddr);
extern  void        (*MMPH_HIF_MemSetB)(MMP_ULONG ulAddr, MMP_UBYTE ubData);
extern  void        (*MMPH_HIF_MemSetW)(MMP_ULONG ulAddr, MMP_USHORT usData);
extern  void        (*MMPH_HIF_MemSetL)(MMP_ULONG ulAddr, MMP_ULONG ulData);
#endif

MMP_ULONG   MMPH_HIF_GetParameterL(MMP_UBYTE ubGroup, MMP_UBYTE ubParamnum);
void    	MMPH_HIF_SetParameterL(MMP_UBYTE ubGroup, MMP_UBYTE ubParamnum, MMP_ULONG ulParamdata);
MMP_USHORT  MMPH_HIF_GetParameterW(MMP_UBYTE ubGroup, MMP_UBYTE ubParamnum);
void		MMPH_HIF_SetParameterW(MMP_UBYTE ubGroup, MMP_UBYTE ubParamnum, MMP_USHORT usParamdata);
MMP_UBYTE   MMPH_HIF_GetParameterB(MMP_UBYTE ubGroup, MMP_UBYTE ubParamnum);
void    	MMPH_HIF_SetParameterB(MMP_UBYTE ubGroup, MMP_UBYTE ubParamnum, MMP_UBYTE ubParamdata);
MMP_ERR		MMPH_HIF_SendCmd(MMP_UBYTE ubGroup, MMP_USHORT usCommand);
MMP_UBYTE   MMPH_HIF_WaitSem(MMP_UBYTE ubGroup, MMP_USHORT usTimeOut);
MMP_UBYTE   MMPH_HIF_ReleaseSem(MMP_UBYTE ubGroup);

void        MMPH_HIF_MemCopyHostToDev(MMP_ULONG ulDestaddr, MMP_UBYTE *usSrcaddr, MMP_ULONG ulLength);
void        MMPH_HIF_MemCopyDevToHost(MMP_UBYTE *ubDestaddr, MMP_ULONG ulSrcaddr, MMP_ULONG ulLength);

/// @}

#endif // _MMPH_HIF_H_
