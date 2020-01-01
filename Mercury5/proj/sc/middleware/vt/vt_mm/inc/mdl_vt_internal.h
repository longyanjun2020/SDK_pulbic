#ifndef _MDL_VT_INTERNAL_H_
#define _MDL_VT_INTERNAL_H_

#define VT_DBG_UART 0
#define VT_DBG_LINE VT_MSG("%s(%d)\n", __FUNCTION__, __LINE__)
#define VT_MSG_FUNCTION_IN VT_MSG("%s() In\n", __FUNCTION__)

#if VT_DBG_UART
    //#define VT_MSG(fmt, ...) UartSendTrace("[VT] "fmt, ##__VA_ARGS__)
    #define VT_MSG(fmt, ...) DrvUartDebugTrace("[VT] "fmt, ##__VA_ARGS__)
    #define VT_MSG_INFO(fmt, ...) DrvUartDebugTrace("[VT] "fmt, ##__VA_ARGS__)
    #define VT_MSG_ERROR(fmt, ...) DrvUartDebugTrace("[VT]Error: "fmt, ##__VA_ARGS__)
#else
    #define VT_MSG(fmt, ...) mdl_vt_printf(1, "[VT] "fmt, ##__VA_ARGS__)
    #define VT_MSG_INFO(fmt, ...) mdl_vt_printf(2, "[VT] "fmt, ##__VA_ARGS__)
    #define VT_MSG_ERROR(fmt, ...) mdl_vt_printf(2, "[VT]Error: "fmt, ##__VA_ARGS__)
    //#define VT_MSG(fmt, ...) vm_dbgTrace(_CUS1|LEVEL_30, fmt, ##__VA_ARGS__)
#endif

#endif
