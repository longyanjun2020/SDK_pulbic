
//==============================================================================
// 
// Copyright (C) Alpha Imaging Technology Corp.
// 
//------------------------------------------------------------------------------
//
// File ID:        $Id: mmpf_usbcdc.h 2 2008-11-17 02:07:23Z patrick $
// File Revsion:   $Rev: 2 $
// Last Commit By: $Author: patrick $
//
//------------------------------------------------------------------------------
//
//                        EDIT HISTORY FOR MODULE
//
// when      who      what, where, why
// --------  -------  ----------------------------------------------------------
// 08/11/05  patrick  Created module
//==============================================================================

typedef struct
{
    MMP_ULONG  dwDTERate;
    MMP_UBYTE bCharFormat;
    MMP_UBYTE bParityType;
    MMP_UBYTE bDataBits;
}UART_LINE_CONTROL;

void MMPF_InitCDC(void);
void MMPF_PollingCDC(void);

void cdc_rx_cmd(void);
void cdc_ep2_rx_done(void);
void cdc_ep1_tx_done(void);
void cdc_ep3_tx_done(void);