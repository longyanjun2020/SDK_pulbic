/*                                                                          */
/*  Important : This software is protected by Copyright and the information */
/*              contained herein is confidential. Distribution, reproduction*/
/*              as well as exploitation and transmission of its contents is */
/*              not allowed except if expressly permitted. Infringments     */
/*              result in damage claims.                                    */
/*              Copyright Wavecom S.A. (c) 2004                             */
/*                                                                          */
/*                                                                          */

/****************************************************************************/
/*  File    : v24.hc                                                        */
/*--------------------------------------------------------------------------*/
/*  Scope   : Constants of the V.24 serial link handler                     */
/*                                                                          */
/* Content  :                                                               */
/*                                                                          */
/*--------------------------------------------------------------------------*/
/* Date     | Author | Modification                                         */
/*----------+--------+------------------------------------------------------*/
/* 08/10/04 |  APH   | New V24: PortId, Ctxt, FctPtr v8a03_aph              */
/*----------+--------+------------------------------------------------------*/
/* 25/10/04 |  APH   | Ident                                                */
/****************************************************************************/
/*$LogWavecom: U:\projet\gsm\pvcsarch\archives\v24\inc\v24.hc-arc $
 *--------------------------------------------------------------------------
 * Date     | Author | Revision       | Description
 *----------+--------+----------------+-------------------------------------
 * 05.01.06 | mpr    | 1.3.1.0        | Resolution for 31090: SMS: Back Tra
 *          |        |                | ce when writing 160 characters SMS 
 *          |        |                |  .                                 
 *----------+--------+----------------+-------------------------------------
*/

#ifndef __SYS_V24_HC__
#define __SYS_V24_HC__

#include "v24.hi"

#define  V24_PHY_CHANNEL_MAX            (V24_ALL_UART-1)  //add one for usb composite
#define  V24_LOG_CHANNEL_MAX            4
#define  V24_MAX_PORT_CONNECTED         (V24_PHY_CHANNEL_MAX + V24_LOG_CHANNEL_MAX)
#define  V24_IDX_UNKNOWN                0xFF

//#define  V24_GET_ERROR_RSP              0xFF // a changer
#define  V24_GET_ERROR_RSP              0    // a changer

#define  V24_GET_TX_FLOW_CONTROL_METHOD 0
#define  V24_GET_RX_FLOW_CONTROL_METHOD 1


#define  V24_GET_DSR_MASK(X)     ((X) & (1 << V24_SIGNAL_DSR))
#define  V24_GET_CTS_MASK(X)     ((X) & (1 << V24_SIGNAL_CTS))
#define  V24_GET_RI_MASK(X)      ((X) & (1 << V24_SIGNAL_RI))
#define  V24_GET_DCD_MASK(X)     ((X) & (1 << V24_SIGNAL_DCD))

#define  V24_SET_SIG_RTS_ON(X)   ((X) |= (1 << V24_SIGNAL_RTS))
#define  V24_SET_SIG_DSR_ON(X)   ((X) |= (1 << V24_SIGNAL_DSR))
#define  V24_SET_SIG_CTS_ON(X)   ((X) |= (1 << V24_SIGNAL_CTS))
#define  V24_SET_SIG_RI_ON(X)    ((X) |= (1 << V24_SIGNAL_RI))
#define  V24_SET_SIG_DCD_ON(X)   ((X) |= (1 << V24_SIGNAL_DCD))
#define  V24_SET_SIG_DTR_ON(X)   ((X) |= (1 << V24_SIGNAL_DTR))
#define  V24_SET_SIG_BRK_ON(X)   ((X) |= (1 << V24_SIGNAL_BRK))

#define  V24_SET_SIG_RTS_OFF(X)  ((X) &= (0xFF - (1 << V24_SIGNAL_RTS)))
#define  V24_SET_SIG_DSR_OFF(X)  ((X) &= (0xFF - (1 << V24_SIGNAL_DSR)))
#define  V24_SET_SIG_CTS_OFF(X)  ((X) &= (0xFF - (1 << V24_SIGNAL_CTS)))
#define  V24_SET_SIG_RI_OFF(X)   ((X) &= (0xFF - (1 << V24_SIGNAL_RI)))
#define  V24_SET_SIG_DCD_OFF(X)  ((X) &= (0xFF - (1 << V24_SIGNAL_DCD)))
#define  V24_SET_SIG_DTR_OFF(X)  ((X) &= (0xFF - (1 << V24_SIGNAL_DTR)))
#define  V24_SET_SIG_BRK_OFF(X)  ((X) &= (0xFF - (1 << V24_SIGNAL_BRK)))



// masks used to uncover the proper part for the port variable
#define V24_HAPC_MASK            0x7f000000
#define V24_MUX_MASK             0x007f0000
#define V24_REL_MASK             0x00007f00
#define V24_PAL_MASK             0x0000000f
#define V24_LOGICAL_MASK         (V24_MUX_MASK | V24_REL_MASK)
#define V24_PORT_MASK            (V24_LOGICAL_MASK | V24_PAL_MASK)


#define V24_HAPC_EN_MASK         0x80000000
#define V24_MUX_EN_MASK          0x00800000
#define V24_REL_EN_MASK          0x00008000

// timers and their Id's
#define V24_TIMER_ESC_GT_MIN     100 // 100 ms 
#define V24_TIMER_ESC_GT_MAX     1   // 1 s 
#define V24_TIMER_ESC_GT_STOP    700 // 700 ms 
#define V24_TIMER_GUARD_TIME     1000 // 1s 

#define V24_TIMER_ESC_GT_MIN_ID   1 
#define V24_TIMER_ESC_GT_MAX_ID   2
#define V24_TIMER_ESC_GT_STOP_ID  3 
#define V24_TIMER_GUARD_TIME_ID   4

#endif /* __SYS_V24_HC__ */

