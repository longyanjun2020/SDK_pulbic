/*******************************************************************************
 * File     : usb_cdc_api.h                                                    
 *------------------------------------------------------------------------------
 * Scope    : Interface of the USB CDC (Communication Device Class) for V24
 *                                                                          
 ******************************************************************************/
#ifndef __SYS_USB_CDC_API_H__
#define __SYS_USB_CDC_API_H__

#include "stdcomp.h"

/*
** The callback list the SW client has to provide to the CDC FL (when it starts
** or stops the CDC)
*/
typedef struct 
{
   s32  (*pfOnTxDataSent)     (u8** ppbTxData, s16* pwAmount);
   void (*pfOnRxDataAvailable)(void);
   s32  (*pfOnLineStateChange)(s16 wLineState);
}sUsbCdcSignalCb_t, *psUsbCdcSignalCb_t;
#define USB_CDC_SIGNAL_CALL_BACK_SZ sizeof(sUsbCdcSignalCb_t)
#define USB_CDC_SIGNAL_CALL_BACK  3

/* The Line State definitions */
enum
{
   DTE_ABSENT_LINE_STATE,
   DTE_PRESENT_LINE_STATE,
   UNKNOWN_LINE_STATE = (s16)-1
};

/*******************************************************************************
 * Function : usb_cdc_api_get_dte_indicator
 *------------------------------------------------------------------------------
 * Scope    : To read the DTE indicator                               
 *          
 * Return   : DTE_ABSENT_LINE_STATE,
 *            DTE_PRESENT_LINE_STATE,
 *            UNKNOWN_LINE_STATE
 *           
 *    
 *------------------------------------------------------------------------------
 * Interface:             | IN|OUT|GLB| Use
 *------------------------+---+---+---+-----------------------------------------
 * swLineStateIn          |   | x | x | The stored DTE indicator's value -static
 ******************************************************************************/
extern s16 usb_cdc_api_get_dte_indicator(void);


/*******************************************************************************
 * Function : usb_cdc_api_start
 *------------------------------------------------------------------------------
 * Scope    : To start the USB stack in CDC mode                               
 *          
 * Return   : 0: Operation successfully completed
 *           -1: Operation aborted
 *    
 *------------------------------------------------------------------------------
 * Interface:             | IN|OUT|GLB| Use
 *------------------------+---+---+---+-----------------------------------------
 * psClientSwCb           | X |   |   | @ of the signal's manager supported by 
 *                        |   |   |   | the SW client. SHALL NOT BE NULL        
 ******************************************************************************/
extern s32 usb_cdc_api_start(psUsbCdcSignalCb_t psClientSwCb);


/*******************************************************************************
 * Function : usb_cdc_api_stop
 *------------------------------------------------------------------------------
 * Scope    : To stop the USB stack in CDC mode. Only the SW client having 
 *            started the CDC is allowed to stop it.
 *          
 * Return   : 0: Operation successfully completed
 *           -1: Operation aborted
 *    
 *------------------------------------------------------------------------------
 * Interface:             | IN|OUT|GLB| Use
 *------------------------+---+---+---+-----------------------------------------
 * psClientSwCb           | X |   |   | @ of the signal's manager provided when  
 *                        |   |   |   | the CDC was started  NOT BE NULL        
 ******************************************************************************/
extern s32 usb_cdc_api_stop(psUsbCdcSignalCb_t psClientSwCb);


/* 
** Supported signal for the Serial State Notification function
*/
typedef enum
{
   CARRIER_INDICATOR,      
   DATA_READY_INDICATOR,   
   BREAK_INDICATOR,
   RING_INDICATOR,
   LAST_INDICATOR,
   BYTE_ALIGNED_INDICATOR = 0xFF
}eUsbFlCdcSsSig_t;

/*
 * Type of operation applying to the signal defined in the eUsbFlCdcSerialState_t
 */
typedef enum
{
   SS_RESET,   /* for the CARRIER and DATA_READY indicators */
   SS_SET,     /* All signals (caution BREAK and RING indicators are reset by the CDC) */
   SS_LAST
}eUsbFlCdcSsOp_t;


/*******************************************************************************
 * Function : usb_cdc_api_serial_state
 *------------------------------------------------------------------------------
 * Scope    : Set (or reset) emulated serial signal state.
 *          
 * Return   : N/A
 *    
 *------------------------------------------------------------------------------
 * Interface:             | IN|OUT|GLB| Use
 *------------------------+---+---+---+-----------------------------------------
 * eOp                    | x |   |   | The operation's selector [RESET,SET]
 * eSig                   | x |   |   | The signal's selector
 ******************************************************************************/
extern s32 usb_cdc_api_serial_state(eUsbFlCdcSsSig_t eSig,eUsbFlCdcSsOp_t eOp);


/*******************************************************************************
 * Function : usb_cdc_api_read
 *------------------------------------------------------------------------------
 * Scope    : To retrieve the data received from the HOST.
 *          
 * Return   : N/A
 *
 * Note     : The client must call this function until it return 0 in the 
 *            *pwAmount output parameter.
 *
 *------------------------------------------------------------------------------
 * Interface:             | IN|OUT|GLB| Use
 *------------------------+---+---+---+-----------------------------------------
 * pbOut                  |   | x |   | Where to copy the received data
 * pwAmount               |   | x |   | Amount of copied byte
 * wMax                   | x |   |   | Maximum amount of byte the client can
 *                        |   |   |   | accept.
 ******************************************************************************/
extern void usb_cdc_api_read(u8* pbOut, u16* pwAmount, u16 wMax);
                            

/*******************************************************************************
 * Function : usb_cdc_api_write
 *------------------------------------------------------------------------------
 * Scope    : To send data to the HOST.
 *          
 * Return   : 0: The lower layers accept the submitted data
 *           -1: The caller must released the submitted data
 *
 *------------------------------------------------------------------------------
 * Interface:             | IN|OUT|GLB| Use
 *------------------------+---+---+---+-----------------------------------------
 * pbIn                   | x |   |   | Where are the data to be sent
 * wAmount                | x |   |   | The amount of data into pbIn
 ******************************************************************************/
extern s32 usb_cdc_api_write(u8* pbIn, u16 wAmount);


typedef struct /* the parameters of the usb_cdc_api_get_line_coding function */
{
   u32 dwDteRate;
   u8  bCharFormat;  /* Stop bits: [0: 1 bit,1: 1.5 bits ,2: 2 bits] */
   u8  bParityType;  /* [0:None, 1:Odd, 2:Even, 3:Space, 4:Mark] */
   u8  bDataBits;    /* [5,6,7,8,16] */
}sUsbCdcLineCoding_t, *pssUsbCdcLineCoding_t;
#define USB_CDC_SZ_LINE_CODING_T   7



/*******************************************************************************
 * Function : usb_cdc_api_get_line_coding
 *------------------------------------------------------------------------------
 * Scope    : Retrieve the line coding parameter
 *          
 * Return   : 0: psOut successfully set (the content may be used)
 *           -1: The psOut content is not valid
 *
 *------------------------------------------------------------------------------
 * Interface:             | IN|OUT|GLB| Use
 *------------------------+---+---+---+-----------------------------------------
 * psOut                  | x |   |   | @ of the output parameter
 ******************************************************************************/
extern s32 usb_cdc_api_get_line_coding(pssUsbCdcLineCoding_t psOut);


/*******************************************************************************
 * Function : usb_cdc_api_pause
 *------------------------------------------------------------------------------
 * Scope    : To pause RX transferring.
 *
 * Return   : 0: pause successfully
 *           -1: pause failed
 *
 *------------------------------------------------------------------------------
 * Interface:             | IN|OUT|GLB| Use
 *------------------------+---+---+---+-----------------------------------------
 * pbIn                   | x |   |   | Where is the data block to be sent
 * wAmount                | x |   |   | Amount of byte to be transmitted
 ******************************************************************************/
extern s32 usb_cdc_api_pause(void);

/*******************************************************************************
 * Function : usb_cdc_api_resume
 *------------------------------------------------------------------------------
 * Scope    : To resume RX transferring.
 *
 * Return   : 0: resume successfully
 *           -1: resume failed
 *
 *------------------------------------------------------------------------------
 * Interface:             | IN|OUT|GLB| Use
 *------------------------+---+---+---+-----------------------------------------
 * pbIn                   | x |   |   | Where is the data block to be sent
 * wAmount                | x |   |   | Amount of byte to be transmitted
 ******************************************************************************/
extern s32 usb_cdc_api_resume(void);

#endif   /* __SYS_USB_CDC_API_H__ */
