//------------------------------------------------------------------------------
//
//  File        : NR_cfg.c
//  Description : Source file of NR configuration
//  Author      : Pohan Chen
//  Revision    : 0.0
//
//------------------------------------------------------------------------------

//==============================================================================
//
//                              INCLUDE FILE
//
//==============================================================================
#ifndef _EQ_CFG_H_
#define _EQ_CFG_H_

#include "lib_retina.h"  
#if (NR_EN || WNR_EN)
/*EQ tables are shared by WNR and NR */
extern  MMP_SHORT       m_bweight_x256_16K[];
extern  MMP_SHORT       m_bweight_x256_48K[];
extern  MMP_SHORT       m_bWeightx256[];
#endif

#endif // _EQ_CFG_H_