#ifndef __DRV_UART_INTF_H__
#define __DRV_UART_INTF_H__

/*
 *  UART HAL API ID
 */
typedef enum
{
    HUC_API_ID_GET_CHAR = 0,
    HUC_API_ID_PUT_CHAR,
    HUC_API_ID_WRT_BUF,
    HUC_API_ID_READ_BUF,
    HUC_API_ID_WAKEUP,
    HUC_API_ID_SLEEP,
}HUC_API_ID_et;

/*
 *  API Function Prototype
 */
typedef void (*FP_HAL_UART_API)(void);

/*
 * UART HAL API Prototype
 */
typedef s32 (*FP_HAL_UART_GET_CHAR) (int uart_num, char* c);
typedef s32 (*FP_HAL_UART_PUT_CHAR) (int uart_num, char  c);
typedef s32 (*FP_HAL_UART_WRT_BUF)  (int uart_num, char* szBuf, int len);
typedef s32 (*FP_HAL_UART_READ_BUF) (int uart_num, char* szBuf, int len);
typedef s32 (*FP_HAL_UART_WAKEUP)   (int uart_num);
typedef s32 (*FP_HAL_UART_SLEEP)    (int uart_num);

/*
 * UART HAL TABLE
 */
typedef struct UART_HAL_API_TBL_s
{
    int              hal_api_id;
    FP_HAL_UART_API  hal_api;
}UART_HAL_API_TBL_st;

#endif /* __DRV_UART_INTF_H__ */