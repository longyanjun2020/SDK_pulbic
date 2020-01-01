/*                                                                          */
/*  Important : This software is protected by Copyright and the information */
/*              contained herein is confidential. Distribution, reproduction*/
/*              as well as exploitation and transmission of its contents is */
/*              not allowed except if expressly permitted. Infringments     */
/*              result in damage claims.                                    */
/*              Copyright Wavecom S.A. (c) 2004                             */
/*                                                                          */
/*                                                                          */

//**************************************************************************//
/**
 *   @file    mux_v24.hc   
 *
 *@b Purpose:     
 *            structures used by the multiplexer internally 
 *            
 *--------------------------------------------------------------------------  
 *@b Content:     
 *                           
 *                                                                         
 *--------------------------------------------------------------------------
 * @date      03/11/2003
 * @author    MSE
 *
 *@b Historical:
 ***************************************************************************
 *   Date:      Author: Note:
 *
 *@n 03/11/2003 MSE     Creation
 *@n 06/12/2004 APH     MUX integration
 *
 */
//**************************************************************************//


#ifndef __MUX_V24_HC__
#define __MUX_V24_HC__

#include "sys_v24_mux.hi"  // v24_MuxRelTxDataBlock & v24_MuxHapcRxDataPtr

#define MUX_AT_START_REQ               0x00
#define MUX_AT_STOP_REQ                0x01
#define MUX_AT_OPEN_DLC_REQ            0x02
#define MUX_AT_OPEN_DLC_CNF            0x03
#define MUX_AT_CLOSE_DLC_REQ           0x04
#define MUX_AT_CLOSE_DLC_CNF           0x05


/**
 * link to v24_mux.C ghost interfaces
 */
#define mux_v24_RelTxDataPtr          v24_MuxRelTxDataBlock
#define mux_v24_HapcRxDataPtr         v24_MuxHapcRxDataPtr



#endif /* __MUX_V24_HC__ */
