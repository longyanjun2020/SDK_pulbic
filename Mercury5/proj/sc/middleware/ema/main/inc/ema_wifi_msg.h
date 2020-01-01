/**
 *
 * @file    ema_wifi_msg.h
 *
 * @brief   This file defines the message related type of WiFi service
 *
 * @author  Cooper Chiou
 * @version $Id: ema_wifi_msg.h 4669 2009-08-05 07:28:12Z cooper.chiou $
 *
 */
#ifndef __EMA_WIFI_MSG_H__
#define __EMA_WIFI_MSG_H__


/*--------------------------------------------------------------------------*/
/* INCLUDE FILE                                                             */
/*--------------------------------------------------------------------------*/
#include "esl_wifi_itf.h"
#include "ema.h"


/*--------------------------------------------------------------------------*/
/* PREPROCESSOR CONSTANT DEFINITION                                         */
/*--------------------------------------------------------------------------*/
#ifdef DefExtern
#undef DefExtern
#endif
#ifdef __EMA_PARSE__
#define	DefExtern
#else
#define	DefExtern	extern
#endif


/*--------------------------------------------------------------------------*/
/* PREPROCESSOR MACRO DEFINITION                                            */
/*--------------------------------------------------------------------------*/


/*--------------------------------------------------------------------------*/
/* TYPE DEFINITION                                                          */
/*--------------------------------------------------------------------------*/

/**
 *  @brief The structure defines the WiFi message body for WiFi operation message
 */
typedef struct
{
    ema_TransType_t         transType;
    esl_WifiCb_t            *pWifiCb;

    union
    {
        esl_WifiReg_t           wifiReg;
        esl_WifiCmd_t           wifiCmd;
        esl_WifiEvent_t         wifiEvent;
        esl_WifiRegNotify_t     wifiRegNotify;
        esl_WifiUnReg_t         wifiUnReg;

    } cmdType;

} ema_WifiCmd_t;


/*--------------------------------------------------------------------------*/
/* GLOBAL VARIABLE DEFINITION                                               */
/*--------------------------------------------------------------------------*/


/*--------------------------------------------------------------------------*/
/* GLOBAL FUNCTION DEFINITION                                               */
/*--------------------------------------------------------------------------*/


#endif /* __EMA_WIFI_MSG_H__ */




