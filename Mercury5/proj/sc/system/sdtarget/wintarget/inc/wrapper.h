#ifndef __WRAPPER_H__
#define __WRAPPER_H__

#include "sysdwldrv.h"

#define dwl_GetCharTimeout(i__u32_Timeout, o__pu8_Received) \
	dwl_getChar_timeout(o__pu8_Received, i__u32_Timeout)

#define dwl_GetBufferTimeout(i__u32_Timeout, o__pu8_Received, i__u32_Length) \
	dwl_recvPacket_timeout(o__pu8_Received, i__u32_Length, i__u32_Timeout)

#define dwl_GetBuffer(o__pu8_Received, i__u32_Length) \
    dwl_recvPacket(o__pu8_Received, i__u32_Length)

#define dwl_SendBuffer(i__pu8_ToSend, i__u32_Length) \
    dwl_sendPacket(i__pu8_ToSend, i__u32_Length)

#define dwl_GetChar() \
    dwl_getChar()

#define dwl_SendChar(i__u8_ToSend) \
    dwl_sendChar(i__u8_ToSend)

// FIXME
#define dwl_RaiseRts()
#define dwl_DrainTxFifo()
#define dwl_UartHandshake()

#define dwl_Handshake() \
    do { \
        if (dwl_getDwldPath() == SELECT_PATH_CONSOLE) \
            dwl_UartHandshake(); \
    } while (0)

// FIXME
#define ke_LoaderReset()

#endif // __WRAPPER_H__

