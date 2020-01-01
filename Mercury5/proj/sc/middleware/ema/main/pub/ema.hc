/**
 *
 * @file    ema.hc
 *
 * @brief   This file defines the common constant of EMA
 *
 * @author  Pauli Leong
 * @version $Id: ema.hc 13420 2008-08-20 02:05:30Z kevin.chang $
 *
 */
#ifndef __EMA_HC__
#define __EMA_HC__


/*--------------------------------------------------------------------------*/
/* INCLUDE FILE                                                             */
/*--------------------------------------------------------------------------*/
#include "ema.ht"




/*--------------------------------------------------------------------------*/
/* PREPROCESSOR CONSTANT DEFINITION                                         */
/*--------------------------------------------------------------------------*/
#ifdef DefExtern
#undef DefExtern
#endif
#ifdef __EMA_PARSE__
#define DefExtern
#else
#define DefExtern extern
#endif

#define CUS_MBX_EMA_INT       (RTK_MAX_MAILBOXES - 1) /**< Use the last system mailbox as EMA internal mailbox */

/**
 *  @brief MMP Function state defintion using BIT set/reset value (1 << FUNC_AUD etc.)
 *         The constants also use to set the current state. As the MMP functions will be
 *         increased in the future, please guarantee ( FUNC_MAX < 29 )
 */
#define EMA_STATE_NOT_READY   (ema_StateMachine_t)(1u << 31)  /**< MMP in power down (Not Ready) stage (Equal to MMP 'BYPASS' Stage)*/
#define EMA_STATE_SETUP       (ema_StateMachine_t)(1 << 30)  /**< MMP in initialization stage */
#define EMA_STATE_IDLE        (ema_StateMachine_t)(0)        /**< MMP in idle (Ready to receive command) stage */
#define EMA_STATE_LIGHT_SLEEP (ema_StateMachine_t)(1 << 29)  /**< MMP in light sleep stage and only allow LCD update through BYPASS */
#define EMA_STATE_DEEP_SLEEP  (ema_StateMachine_t)(1 << 28)  /**< MMP in deep sleep stage and allow no command can be processed by MMP */
#define EMA_STATE_TIMEOUT     (ema_StateMachine_t)(1 << 27)  /**< MMP in timeout stage and don't accept any command */
#define EMA_STATE_SUSPEND     (ema_StateMachine_t)(1 << 26)  /**< MMP in suspend stage and only allow LCD update through BYPASS */

#define EMA_STATE_CAM         (ema_StateMachine_t)(1 << FUNC_CAM)          /**< MMP Camera active flag */
#define EMA_STATE_CAM_VC      (ema_StateMachine_t)(1 << FUNC_CAM_VC)       /**< MMP Camera Video Chat flag*/
#define EMA_STATE_AUD         (ema_StateMachine_t)(1 << FUNC_AUD)          /**< MMP Audio active flag */
#define EMA_STATE_AUD_MP      (ema_StateMachine_t)(1 << FUNC_AUD_MP)       /**< MMP Audio Meida Playback active flag */
#define EMA_STATE_AUD_STM     (ema_StateMachine_t)(1 << FUNC_AUD_STM)      /**< MMP Audio streaming active flag */
#define EMA_STATE_VDO         (ema_StateMachine_t)(1 << FUNC_VDO)          /**< MMP hardware Video playback active flag */
#define EMA_STATE_VDO_SP      (ema_StateMachine_t)(1 << FUNC_VDO_SP)       /**< MMP Video special case command flag */
#define EMA_STATE_USB         (ema_StateMachine_t)(1 << FUNC_USB)          /**< MMP USB active flag */
#define EMA_STATE_USB_MSC     (ema_StateMachine_t)(1 << FUNC_USB_MSC)      /**< MMP USB Mass Storage Class active flag */
#define EMA_STATE_USB_CDC     (ema_StateMachine_t)(1 << FUNC_USB_CDC)      /**< MMP USB Communication Device Class active flag */
#define EMA_STATE_IP          (ema_StateMachine_t)(1 << FUNC_IP)           /**< MMP Image Processing active flag */
#define EMA_STATE_DISP        (ema_StateMachine_t)(1 << FUNC_DISP)         /**< MMP Display active flag */
#define EMA_STATE_GSS_RENDER  (ema_StateMachine_t)(1 << FUNC_GSS_RENDER)   /**< MMP Image Processing active flag */
#define EMA_STATE_FS          (ema_StateMachine_t)(1 << FUNC_FS)           /**< MMP File System active flag */
#define EMA_STATE_SYS         (ema_StateMachine_t)(1 << FUNC_SYS)          /**< MMP System active flag */
#define EMA_STATE_TV          (ema_StateMachine_t)(1 << FUNC_TV)           /**< MMP TV active flag */
#define EMA_STATE_FMR         (ema_StateMachine_t)(1 << FUNC_FMR)          /**< MMP FMR active flag */
#define EMA_STATE_GPS         (ema_StateMachine_t)(1 << FUNC_GPS)          /**< MMP GPS active flag */
#define EMA_STATE_IPTV        (ema_StateMachine_t)(1 << FUNC_IPTV)         /**< MMP IPTV flag */
#define EMA_STATE_PERIPHERAL  (ema_StateMachine_t)(1 << FUNC_PERIPHERAL)   /**< MMP PERIPHERAL flag */
#define EMA_STATE_NANDSERV    (ema_StateMachine_t)(1 << FUNC_NANDSERV)     /**< MMP NAND Service active flag */
#define EMA_STATE_RFID        (ema_StateMachine_t)(1 << FUNC_RFID)         /**< MMP RFID active flag */
#define EMA_STATE_NRAI        (ema_StateMachine_t)(1 << FUNC_NRAI)         /**< MMP NAND RAI active flag */
#define EMA_STATE_WIFI        (ema_StateMachine_t)(1 << FUNC_WIFI)         /**< MMP WIFI actice flag */

/**
 *  @brief EMA device command ID base definition
 */
#define EMA_CAM_DEVICE    0x00  /**< Camera device command ID base */
#define EMA_AUD_DEVICE    0x20  /**< Audio device command ID base */
#define EMA_DISP_DEVICE   0x40  /**< Display device command ID base */
#define EMA_EFS_DEVICE    0x60  /**< File System device command ID base */
#define EMA_IP_DEVICE     0x88  /**< Image Processing device command ID base */
#define EMA_REC_DEVICE    0x90  /**< Recorder device command ID base */
#define EMA_WIFI_DEVICE   0x98  /**< WIFI device command ID base */
#define EMA_VDO_DEVICE    0xA0  /**< Video device command ID base */
#define EMA_USB_DEVICE    0xB0  /**< USB device command ID base */
#define EMA_SYS_DEVICE    0xC0  /**< SYS command ID base */
#define EMA_NRAI_DEVICE   0xC8  /**< SYS command ID base */
#define EMA_TV_DEVICE     0xD0  /**< TV device command ID base */
#define EMA_FMR_DEVICE    0xE0  /**< FMR device command ID base */
#define EMA_GPS_DEVICE    0xF0  /**< GPS device command ID base */
#define EMA_RFID_DEVICE   0xF8  /**< RFID device command ID base */
#define EMA_DEVICE_MASK   0xFF  /**< Device command ID mask */


/*--------------------------------------------------------------------------*/
/* PREPROCESSOR MACRO DEFINITION                                            */
/*--------------------------------------------------------------------------*/


/*--------------------------------------------------------------------------*/
/* TYPE DEFINITION                                                          */
/*--------------------------------------------------------------------------*/


/*--------------------------------------------------------------------------*/
/* GLOBAL VARIABLE DEFINITION                                               */
/*--------------------------------------------------------------------------*/


/*--------------------------------------------------------------------------*/
/* GLOBAL FUNCTION DEFINITION                                               */
/*--------------------------------------------------------------------------*/


#endif /*__EMA_HC__ */

