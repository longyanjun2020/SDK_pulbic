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
 *   @file    mux_mux.hc 
 *
 *@b Purpose:     
 *            constants and different parameters in Mux
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

#ifndef __MUX_MUX_HC__
#define __MUX_MUX_HC__



/* frames */

#define MUX_FRAME_SABM 0x2f
#define MUX_FRAME_UA   0x63
#define MUX_FRAME_DM   0x0f
#define MUX_FRAME_DISC 0x43
#define MUX_FRAME_UIH  0xef
#define MUX_FRAME_UI   0x03


/* commands */	
#define	MUX_COMMAND_PN             0x81
#define	MUX_COMMAND_CLD            0xc1
#define	MUX_COMMAND_TEST           0x21	
#define	MUX_COMMAND_FCON           0xa1
#define	MUX_COMMAND_FCOFF          0x61
#define	MUX_COMMAND_MSC            0xe1
#define	MUX_COMMAND_PSC            0x41
#define	MUX_COMMAND_NON_SUPPORTED  0x11
#define	MUX_COMMAND_RLS            0x51
#define	MUX_COMMAND_RPN            0x91
#define	MUX_COMMAND_SNC            0xd1

/* states of the context mux_DataTx_t State*/

#define MUX_CLOSED                   0x00
#define MUX_CONNECTING_REMOTE_PDG    0x01
#define MUX_CONNECTING_APPLI_PDG     0x02
#define MUX_CONNECTED                0x03
#define MUX_DISCONNECTING_REMOTE_PDG 0x04
#define MUX_DISCONNECTING_APPLI_PDG  0x05
#define MUX_CONTROL_COMMAND_SENT     0x06
#define MUX_STOP_PDG                 0x07

/* Flags of the Queue */

#define MUX_QUEUE_NOFLAGS                   0x00
#define MUX_QUEUE_LOW_POWER                 0x01
#define MUX_QUEUE_REMOTE_FLOW_CONTROL       0x02
#define MUX_QUEUE_LOCAL_FLOW_CONTROL        0x04
#define MUX_QUEUE_LOW_POWER_LOCAL_WAKEUP    0x08
#define MUX_QUEUE_LOW_POWER_REMOTE_WAKEUP   0x10
#define MUX_QUEUE_LOW_POWER_WAKEUP_MASK     (MUX_QUEUE_LOW_POWER_LOCAL_WAKEUP | MUX_QUEUE_LOW_POWER_REMOTE_WAKEUP)
#define MUX_QUEUE_LOW_POWER_LOCAL_SLEEP     0x20
//#define MUX_QUEUE_DATA_FRAGMENT_PDG         0x08

/* Flag */
#define MUX_FLAG_BASIC           0xF9
#define MUX_FLAG_HDLC	         0x7e


/* size*/
#define MUX_SIZE_FRAME           6

#define MUX_SIZE_SABM            6
#define MUX_SIZE_UA              6
#define MUX_SIZE_DM              6
#define MUX_SIZE_DISC            6
#define MUX_SIZE_UIH             6


#define MUX_SIZE_CONTROL         2
#define MUX_SIZE_CLD             0
#define MUX_SIZE_NONSUPP         1

/**/
#define MUX_COMMAND_BIT          0x02
#define MUX_POLLING_BIT          0x10
#define MUX_EA_BIT               0x01

/* default and minimum values for T1, T2, N2 */
#define MUX_T1_DEFAULT           10   /*100 ms*/
#define MUX_T1_MIN                1   /*10 ms*/

#define MUX_T2_DEFAULT           30   /*300 ms*/
#define MUX_T2_MIN                2   /*20 ms*/

#define MUX_T3_DEFAULT           10   /*10 s*/
#define MUX_T3_MIN                1   /* 1 s*/

#define MUX_N2_DEFAULT            3   /*default number of retransmissions*/

#define MUX_N1_DEFAULT           31   /*default max frame size           */



#define MUX_MAX_DATA_CHANNEL      4
//#define MUX_MAX_CHANNEL           5
#define MUX_MAX_PHYPORT           3

#define MUX_MAX_DLCI              64

/* role */

#define MUX_ROLE_NOROLE             0x00
#define MUX_ROLE_INITIATOR          0x01
#define MUX_ROLE_RESPONDER          0x02


#define MUX_RESET_FORCED            0x01
#define MUX_RESET_NO_FORCED         0x00
/*CR bit*/
#define MUX_CRBIT_NOTSET            0xFD

/*P/F bit*/
#define MUX_PFBIT_NOTSET            0xEF



#define MUX_HYPERQUEUE_TRANSPARENT  0x00
#define MUX_HYPERQUEUE_MULTIPLEXING 0x01

/* convergence layer types */

#define MUX_CONVERGENCE_LAYER_TYPE_1 0x00
#define MUX_CONVERGENCE_LAYER_TYPE_2 0x01
#define MUX_CONVERGENCE_LAYER_TYPE_3 0x02
#define MUX_CONVERGENCE_LAYER_TYPE_4 0x03

/* */
#define MUX_MUX_NO_COMMAND       0x00
#define MUX_MUX_PN_COMMAND       0x01
#define MUX_MUX_CLD_COMMAND      0x02
#define MUX_MUX_TEST_COMMAND     0x03
#define MUX_MUX_FCON_COMMAND     0x04
#define MUX_MUX_FCOFF_COMMAND    0x05
#define MUX_MUX_PSC_COMMAND      0x06
#define MUX_MUX_MSC_COMMAND      0x07
#define MUX_MUX_NONSUPP_COMMAND  0x08

#define MUX_MUX_COMMAND      0x00
#define MUX_MUX_RESPONSE     0x01

/* timers */

// APH : TimerId Base depends on V24 TimerIds
//       in order not to interfer with (see v24.hc)
#define MUX_TIMER_ID_BASE   0x08
#define MUX_TIMER_ID_T1     0x00
#define MUX_TIMER_ID_T2     0x01
#define MUX_TIMER_ID_T3     0x02
#define MUX_TIMER_ID_PSC    0x03 // delayed PSC timer

/**/
#define MUX_NO_DLCI         0xF0
#define MUX_NO_ID           0x0F

/*Uarts*/
#define MUX_NO_UART           0x00
#define MUX_PORT_UART1        0x01
#define MUX_PORT_UART2        0x02
#define MUX_PORT_USB          0x03

/*relay */
#define MUX_NO_RELAY          0x00

/* signals*/

#define MUX_SIG_FC            0x02
#define MUX_SIG_DTR_DSR       0x04
#define MUX_SIG_RTS_CTS       0x08
#define MUX_SIG_RI            0x40
#define MUX_SIG_DCD           0x80
#define MUX_SIG_ALL           0xCF

#define MUX_SIG_BRK           0x02
/* signals*/

#define MUX_MUX_SIG_DTR       0x01
#define MUX_MUX_SIG_RTS       0x02
#define MUX_MUX_SIG_DSR       0x03
#define MUX_MUX_SIG_CTS       0x04
#define MUX_MUX_SIG_RI        0x05
#define MUX_MUX_SIG_DCD       0x06
 

// _DEV xx to yy levels attributed for MUX


/**
 * Driver traces flags (levels 21 to 24 for MUX)
 */
#define _MUX_TRACE_FLAG         _DEV


// MUX Errors
#define MUX_TRACE_ID_ERR        ( _MUX_TRACE_FLAG | LEVEL_1 ) 
#define MUX_TRACE_ID_ERR_FATAL  ( MUX_TRACE_ID_ERR | FATAL ) 
#define MUX_TRACE_ID_ERR_STORE  ( MUX_TRACE_ID_ERR | STORE ) 


// System or external functions
#define MUX_TRACE_ID_SYS        ( _MUX_TRACE_FLAG | LEVEL_1 )

// MUX Layers
#define MUX_TRACE_ID_CTX        ( _MUX_TRACE_FLAG | LEVEL_21 )
#define MUX_TRACE_ID_MUX        ( _MUX_TRACE_FLAG | LEVEL_22 )
#define MUX_TRACE_ID_SND        ( _MUX_TRACE_FLAG | LEVEL_23 )
#define MUX_TRACE_ID_ITF        ( _MUX_TRACE_FLAG | LEVEL_24 )
#define MUX_TRACE_ID_UTIL       ( _MUX_TRACE_FLAG | LEVEL_21 )




// APH compil
#define V24_BLOCK_MAX_HEADER_SIZE  32
//#define V24_BLOCK_MAX_BODY_SIZE    256
#define V24_BLOCK_MAX_TAIL_SIZE    8

#define V24_BLOCK_INDEX_HEADER     0
#define V24_BLOCK_INDEX_BODY       1
#define V24_BLOCK_INDEX_TAIL       2



#define MUX_V24_BLOCK_INDEX_HEADER    V24_BLOCK_INDEX_HEADER 
#define MUX_V24_BLOCK_INDEX_BODY      V24_BLOCK_INDEX_BODY   
#define MUX_V24_BLOCK_INDEX_TAIL      V24_BLOCK_INDEX_TAIL   



  
#define mux_ReleaseMemory(__x__)  _mux_ReleaseMemory( (void **)(&(__x__)))

#endif /* __MUX_MUX_HC__ */
