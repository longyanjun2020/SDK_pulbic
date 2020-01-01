/*******************************************************************************
 *
 *   UartShell.c
 *
 *   Interface for the UartShell class.
 *
 *   Copyright 2010 by Caesar Chang.
 *
 *   AUTHOR : Caesar Chang
 *
 *   VERSION: 1.0
 *
 *
*******************************************************************************/


#if !defined(_UARTCMD2NAVI__INCLUDED_)
#define _UARTCMD2NAVI__INCLUDED_


#include <stdarg.h>
#include "mmpf_typedef.h"
#include "mmpf_uart.h"
#include "mempool.h"


/*******************************************************************************
 *
 *   NUMBER OF UART COMMAND LISTS
 *
*******************************************************************************/
#define MAX_NUMBER_OF_UART_CMD_LIST        16

/*******************************************************************************
 *
 *   UART COMMAND STRUCTURE
 *
*******************************************************************************/
#if 0
typedef struct sUART_COMMAND
{
	// Command Name
	char * szCommandString;
	
	// Comment of parameters 
	char * szParameter;	
	
	// Comment of function help.
	char * szHelp;
	
	// Function pointer of this command
    void  (*pFunc)(char* szParameter);

} *PUARTCOMMAND, UARTCOMMAND;
#endif

/*******************************************************************************
 *
 *   ESCAPE CODE FOR UART COLOR PRINT 
 *
*******************************************************************************/
#define ESC_ATR_COLOR_DEFAULT                        "\033[0m"
#define ESC_ATR_COLOR_BRIGHTER                       "\033[1m"
#define ESC_ATR_COLOR_UNDERLINED                     "\033[4m"
#define ESC_ATR_COLOR_FLASHING                       "\033[5m"
#define ESC_FG_COLOR_BLACK                          "\033[30m"
#define ESC_FG_COLOR_RED                            "\033[31m"
#define ESC_FG_COLOR_GREEN                          "\033[32m"
#define ESC_FG_COLOR_YELLOW                         "\033[33m"
#define ESC_FG_COLOR_BLUE                           "\033[34m"
#define ESC_FG_COLOR_PURPLE                         "\033[35m"
#define ESC_FG_COLOR_CYAN                           "\033[36m"
#define ESC_FG_COLOR_GRAY                           "\033[37m"
#define ESC_BG_COLOR_BLACK                          "\033[40m"
#define ESC_BG_COLOR_RED                            "\033[41m"
#define ESC_BG_COLOR_GREEN                          "\033[42m"
#define ESC_BG_COLOR_YELLOW                         "\033[43m"
#define ESC_BG_COLOR_BLUE                           "\033[44m"
#define ESC_BG_COLOR_PURPLE                         "\033[45m"
#define ESC_BG_COLOR_CYAN                           "\033[46m"
#define ESC_BG_COLOR_GRAY                           "\033[47m"

/*******************************************************************************
 *
 *   MARCO OF ESCAPE CODE FOR UART COLOR PRINT 
 *
*******************************************************************************/
#define AT_DEFAULT(X)             ESC_ATR_COLOR_DEFAULT        X
#define AT_BRIGHTER (X)           ESC_ATR_COLOR_BRIGHTER       X ESC_ATR_COLOR_DEFAULT
#define AT_UNDERLINED(X)          ESC_ATR_COLOR_UNDERLINED     X ESC_ATR_COLOR_DEFAULT
#define AT_FLASHING(X)            ESC_ATR_COLOR_FLASHING       X ESC_ATR_COLOR_DEFAULT
#define FG_BLACK(X)               ESC_FG_COLOR_BLACK           X ESC_ATR_COLOR_DEFAULT
#define FG_RED(X)                 ESC_FG_COLOR_RED             X ESC_ATR_COLOR_DEFAULT
#define FG_GREEN(X)               ESC_FG_COLOR_GREEN           X ESC_ATR_COLOR_DEFAULT
#define FG_YELLOW(X)              ESC_FG_COLOR_YELLOW          X ESC_ATR_COLOR_DEFAULT
#define FG_BLUE(X)                ESC_FG_COLOR_BLUE            X ESC_ATR_COLOR_DEFAULT
#define FG_PURPLE(X)              ESC_FG_COLOR_PURPLE          X ESC_ATR_COLOR_DEFAULT
#define FG_CYAN(X)                ESC_FG_COLOR_CYAN            X ESC_ATR_COLOR_DEFAULT
#define FG_GRAY(X)                ESC_FG_COLOR_GRAY            X ESC_ATR_COLOR_DEFAULT
#define BG_BLACK(X)               ESC_BG_COLOR_BLACK           X ESC_ATR_COLOR_DEFAULT
#define BG_RED(X)                 ESC_BG_COLOR_RED             X ESC_ATR_COLOR_DEFAULT
#define BG_GREEN(X)               ESC_BG_COLOR_GREEN           X ESC_ATR_COLOR_DEFAULT
#define BG_YELLOW(X)              ESC_BG_COLOR_YELLOW          X ESC_ATR_COLOR_DEFAULT
#define BG_BLUE(X)                ESC_BG_COLOR_BLUE            X ESC_ATR_COLOR_DEFAULT
#define BG_PURPLE(X)              ESC_BG_COLOR_PURPLE          X ESC_ATR_COLOR_DEFAULT
#define BG_CYAN(X)                ESC_BG_COLOR_CYAN            X ESC_ATR_COLOR_DEFAULT
#define BG_GRAY(X)                ESC_BG_COLOR_GRAY            X ESC_ATR_COLOR_DEFAULT



#define HEARD             '@'
#define END               '\r'
#define FLAG_RECORD_ON    'E'

#define CMD_ACK               "@cmd="
#define RECORD_VERSION        "@version"
 
#define STATUS_RECORD_RESTART    "@record-restart\r"
#define STATUS_RECORD_OFF        "@record-stop\r"
#define STATUS_RECORD_LOCK_END   "@lockrecord-end\r"
#define STATUS_RECORD_UNLOCK_END "@unlockrecord-end\r"
#define STATUS_RECORD_UNLOCK     "@record-unlock\r"   //自动录像创建下一个新的录像文件，默认是没有加锁的

#define STATUS_PHOTO_OFF      "@photo-stop\r"
#define STATUS_CARD_IN        "@card-plugin\r"
#define STATUS_CARD_OUT       "@card-plugout\r"
#define STATUS_FILE           "@file"            //@file-avi,5/88,256
#define STATUS_FILE_COUNT     "@file-count"
#define STATUS_TIME           "@playtime"
#define STATUS_VIDEO_PLAY     "@goto-videoplay\r"
#define STATUS_VIDEO_VIEW     "@goto-videoview\r"
#define STATUS_STILL_PLAY     "@goto-stillplay\r"
#define STATUS_STILL_VIEW     "@goto-stillview\r"
#define STATUS_CARD_REPLUG    "@dialog-please_plug_out_card\r"
#define STATUS_CARD_ERROR     "@dialog-card_error\r"
#define STATUS_CARD_MEMORY_FULL  "@dialog-memory_full\r"

#define STAUTS_FORMAT_NO_CARD  "@format-cardout\r"
#define STATUS_FORAMT_FAIL     "@format-fail\r"
#define STATUS_FORAMT_SUCC     "@format-succ\r"


//upgrade
#define STATUS_UPGRADE_NO_FILE 		"@upgrade-nofile\r"
#define STATUS_UPGRADE_ERASE   		"@upgrade-erase\r"

#define STATUS_UPGRADE_READ_FILE 	"@upgrade-read\r"
#define STATUS_UPGRADE_PROGRESS   	"@upgrade-pro-"//@upgrade-pro-xx//xx %
#define STATUS_UPGRADE_SUCC   		"@upgrade-succ\r"
#define STATUS_UPGRADE_FAIL   		"@upgrade-fail\r"



/*******************************************************************************
 *
 *   FUNCTION
 *
 *      SendCmd2Navi
 *
 *   DESCRIPTION
 *
 *      a lite printf command. send cmd by  MMP_UART_ID_2.
 *
 *   ARGUMENTS
 *
 *      N/A
 *
 *   RETURN
 *   
 *      N/A
 *
*******************************************************************************/
void
SendCmd2Navi( char* szFormat, ... );

#endif // !defined(_UARTSHELL_H__810F924F_40C9_4309_9ED6_80DCB4651F07__INCLUDED_)
