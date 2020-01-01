/**
 *
 * @file    usb_cdc_fl.h
 *
 * @brief   This module defines structure and API for USB CDC function layer of EMA.
 *
 * @author  Kevin Chang
 * @version $Id:
 *
 */
#ifndef __USB_CDC_FL_H__
#define __USB_CDC_FL_H__

/*--------------------------------------------------------------------------*/
/* INCLUDE FILE                                                             */
/*--------------------------------------------------------------------------*/  
//#include "msmdrv.h"


/*--------------------------------------------------------------------------*/
/* TYPE DEFINITION                                                          */
/*--------------------------------------------------------------------------*/
/**
 *  @brief The USB link status
 */
typedef enum
{
   USB_ENUMERATED,
   USB_UNPLUGGED,
   USB_RESET
}eUsbStatus_t;

/**
 *  @brief The callback list the FL has to provide to the CL
 */
typedef struct 
{
   s32 (*pfOnUsbLinkStatus)(eUsbStatus_t eStatus);
   s32 (*pfOnClassRequest )(u8* pbReq,u8* pbRsp,s16* pwSzRsp);
   s32 (*pfOnRead         )(u8 bPipeId,u8* pbBuffer,s16 wAmount);
   s32 (*pfOnWrite        )(u8 bPipeId,u8** ppbBuffer,s16* pwAmount);
}sSignalCb_t, *psSignalCb_t;

enum _ePipeDir_t
{
   PIPE_R_O,  /* Read only from the host to the device */
   PIPE_W_O,  /* Write Only from the device to the host */
   PIPE_R_W   /* Read & Write */
};

enum _ePipeType_t
{
   MANAGEMENT_PIPE,   /* Mapped on CTRL ep Class/vendor requests processing */
   DATA_PIPE,         /* Mapped on BULK ep */
   NOTIFICATION_PIPE, /* Mapped on INTERRUPT ep */
   LAST_PIPE          /* Just a limit do not use this value */
};

/**
 *  @brief The sturcture defines pipe configuration.
 */
typedef struct
{
   /* Direction from the device point of view ... */
   enum _ePipeDir_t eDir;
   
   enum _ePipeType_t eType;
   
   u16 wPad;
}sPipeCreateIn_t, *psPipeCreateIn_t;

typedef enum _ePipeDir_t  ePipeDir_t;

typedef enum _ePipeType_t ePipeType_t;

typedef enum   /* The supported states of the CDC FSM */
{
   CDC_NULL_STATE,
   CDC_WAITING_FOR_LOWER_LAYERS_SETTING_STATE,
   CDC_LOWER_LAYERS_NOT_READY,
   CDC_LOWER_LAYERS_READY
}eCdcState_t;


/*--------------------------------------------------------------------------*/
/* GLOBAL FUNCTION DEFINITION                                               */
/*--------------------------------------------------------------------------*/
/** 
 * @brief CDC start function called from Task outside V24.
 *   
 * @param None
 * 
 * @return None
 */
extern void usb_cdc_external_start(void);

/** 
 * @brief CDC stop function called from Task outside V24.
 *   
 * @param None
 * 
 * @return None
 */
extern void usb_cdc_external_stop(void);

/** 
 * @brief Function called when we got USB CONNECT notification from M2
 *   
 * @param None
 * 
 * @return None
 */  
extern s32 usb_cdc_plugin_notification(void);

/** 
 * @brief Function called when we got USB REMOVE notification from M2
 *   
 * @param None
 * 
 * @return None
 */
extern s32 usb_cdc_plugout_notification(void);

/** 
 * @brief get the address of bufferToV24
 *   
 * @param bufPtr: pointer of rx buffer
 * 
 * @return None
 */
extern void addrOfBufferToV24( u8 **bufPtr);

/** 
 * @brief get the buffer size of bufferToV24
 *   
 * @param None
 * 
 * @return None
 */
extern u16 maxRxBufferSize(void);

/** 
 * @brief Set write done callback returned status from host
 *   
 * @param status: returned status
 * 
 * @return None
 */
//extern void setV24DoneCBStatus(MSMErrcode_e status);

/** 
 * @brief Get write done callback returned status from host
 *   
 * @param status: None
 * 
 * @return: Write done callback status
 */
//extern MSMErrcode_e getV24DoneCBStatus(void);

/** 
 * @brief Get Cdc status
 *   
 * @param status: returned status
 * 
 * @return None
 */
extern eCdcState_t getCdcState(void);


#endif   /* __USB_CDC_FL_H__ */

