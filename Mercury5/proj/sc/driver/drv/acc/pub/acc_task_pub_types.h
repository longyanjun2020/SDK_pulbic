/**
 * \file acc_task_pub_types.h
 * Description:  acc task public types
*/

#ifndef __ACC_TASK_PUB_TYPES_H__
#define __ACC_TASK_PUB_TYPES_H__

#define DEV_AT_WCUS_PARSER_PARA_LEN     128

struct tAtCmdFuncParam_
{
    /* Original parameter string for TC*/    
    u8 parameter[DEV_AT_WCUS_PARSER_PARA_LEN];
    /* Whole string for TCR, ex: AT+WCUSTCR="BB",0,0,0,0 */
    ascii *     string;
    /* Paramter string for TCR */
    ascii *     OutputString;
    /* item index for TC */
    u8          item_index;
    /* function index for TC */
    u8          function_index;
    /* parameter count for TC */  
    u8          parameter_count;
    /* largest parameter length for TC, ex : 2,3,"123456" (ParaLenMax = 6) */ 
    s8          ParaLenMax; 
    /* 0: success, 1: not support, 2: fail */
    u8          status;
    /* parameter count for TCR */
    u8          OutputCount;
    /* parameter length , ex: "123456789", length = 9 */
    s8          OutputLen;
    /* 1: read 1 number at a time, ex: "1 2 3 4 5 6 7"; 2 : read 2 number at a time, ex: "03 1f 24 a0 b0" */
    u8          ReadByte;
    /* temporary parameter buffer for TCR */  
    u8 *        ReadBuf;
    /* temporary parameter buffer for TCR */  
    u16        ReadBuf_16[10];
    /* default: FALSE,  TRUE:  do not print out the TCR at  acc_task.c*/
    bool        bNeedPrintOut;              
};

opaque_enum(dev_DeviceInfoType_t_)
{
    DEV_IC_INFO,
    DEV_DSP_INFO,
    DEV_LCD_INFO,
    DEV_GSENSOR_INFO,
    DEV_BACKLIGHT_INFO,
    DEV_TOUCHSCREEN_INFO,
    DEV_OFN_INFO,
    DEV_MCP_INFO,
    DEV_RF_INFO,
    DEV_CAMSENSOR_INFO,
    DEV_BT_INFO,
    DEV_WIFI_INFO,
    DEV_MN_INFO,
};

extern bool dev_ChargeEnable;

#endif  /* __ACC_TASK_PUB_TYPES_H__ */
