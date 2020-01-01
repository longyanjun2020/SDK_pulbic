
/**
* @file    drv_uart_api.h
* @version
* @brief   Unified UART driver interface header file
*
*/

#ifndef __DRV_UART_API_H__
#define __DRV_UART_API_H__

#include "vm_types.ht"
#include "sys_wmh_v24.hi"

#define EIGHT_ALIGNMENT __attribute__((aligned(8)))

#define INFO_ISP_MSG_ON_PNL_C	(1)

#define UART_NB_RATES           13
#define	MSG_ON_PNL_LINE_NUM		(6)
#define	MSG_ON_PNL_BYTE_LINE	(256)

typedef enum {
    E_UART_1  = 1,
    E_UART_2  = 2,
    E_UART_3  = 3,
    E_FUART   = 4,
} UartChann_e;

/**
 * \brief Type of UART Indication
 *
 *  Used in \ref UartCallbackInd_t callback function to specify the type of UART Indication.
 */
typedef enum {
    UART_BREAK_IND = 0,
    UART_OVERRUN_IND,
    UART_MSR_CHANGE_IND,
    UART_RX_FLOW_CTRL_IND,
    UART_BUSY_IND
} Uart_Ind_t;

/**
 * \brief Data Callback function type
 *
 *  Used in \ref Uart_cfg_t structure to specify a callback for RX or TX data events.
 */
typedef void (* UartCallbackData_t)(u8 num, u8 *buffer, u32 size);

/**
 * \brief Indication Callback function type
 *
 *  Used in \ref UartCallbackInd_t callback function to specify the callback used for UART non data events.
 */
typedef void (* UartCallbackInd_t)(u8 num, Uart_Ind_t ind);

/**
 * \brief UART configuration type
 *
 *  Used in \ref uart_Open function to specify the parameters of the UART to use.
 */
typedef struct {
    vm_v24_SerialLength_t 	        length; 	        ///< length in number of bits
    vm_v24_SerialParity_t 	        parity; 	        ///< parity
    vm_v24_SerialStop_t 	        stop;	            ///< stop bit
    vm_v24_Rate_t		            rate;	            ///< bit rate
    vm_v24_FlowControl_t            RxFlowCtrlMethod; 	///< type of Rx flow control
    vm_v24_FlowControl_t            TxFlowCtrlMethod;	///< type of Tx flow control
    u8					            signal_mask;		///< signals to use
    UartCallbackData_t	    	    rxCallback;			///< callback called when data received in hardware FIFO
    UartCallbackData_t		        txCallback;			///< callback called when all data of software FIFO sent
    UartCallbackInd_t		        EvtCallback;		///< callback called when UART event raise of type \ref Uart_Ind_t
    u32                             dmaEnable;          ///< TX/RX by dma>
    u32                             autoCtsRts;
} Uart_cfg_t;

/**
 * \brief UART configuration type
 *
 *  Used in \ref uart_Open function to specify the parameters of the UART to use.
 */


/*--------------------------------------------------------------------------*/
/* GLOBAL FUNCTION DECLARATION                                              */
/*--------------------------------------------------------------------------*/
bool    DrvUartInit(void);

s32     DrvUartDebugTrace(const char *strFormat, ...);
s32     DrvUartSendMsg(char const *msg);
void    DrvUartSetPushPullMode(bool bEnable);

s8		UartSendTrace(const char *strFormat, ...);
s32		get_trace(char *para, int *ret_value);

#if defined(INFO_ISP_MSG_ON_PNL_C)&&(INFO_ISP_MSG_ON_PNL_C)
unsigned char*	ShowOnPnl_GetMsg(unsigned char idx);
signed char		ShowOnPnl_SendMsg(const char *strFormat, ...);
unsigned char	ShowOnPnl_GetMsgIdx(void);
void			ShowOnPnl_Reset(void);
void			ShowOnPnl_ForceUpdateSetFlag(unsigned char flag);
unsigned char	ShowOnPnl_ForceUpdateGetFlag(void);

#endif


#endif  /* __DRV_UART_API_H__ */
