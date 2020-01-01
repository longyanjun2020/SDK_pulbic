#ifndef SENSOR_LOG_H
#define SENSOR_LOG_H

#include "sys_sys_isw_uart.h"

//#define _DEBUG_

#ifdef _DEBUG_
    #define SENSOR_DMSG(args...) UartSendTrace("[D]"args)
    #define SENSOR_EMSG(args...) UartSendTrace("[E]"args)
    #define SENSOR_IMSG(args...) UartSendTrace("[I]"args)
#else
    #define SENSOR_DMSG(args...) do{}while(0)
    #define SENSOR_EMSG(args...) UartSendTrace("[E]"args)
    #define SENSOR_IMSG(args...) UartSendTrace("[I]"args)
#endif

#endif
