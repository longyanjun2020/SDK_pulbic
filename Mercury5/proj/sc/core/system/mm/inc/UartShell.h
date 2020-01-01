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


#if !defined(_UARTSHELL_H__810F924F_40C9_4309_9ED6_80DCB4651F07__INCLUDED_)
#define _UARTSHELL_H__810F924F_40C9_4309_9ED6_80DCB4651F07__INCLUDED_


#include <stdarg.h>
#include "mmpf_typedef.h"


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

/*******************************************************************************
 *
 *   APIs
 *
*******************************************************************************/

/*******************************************************************************
 *
 *   FUNCTION
 *
 *      UartCommandShell
 *
 *   DESCRIPTION
 *
 *      Uart command shell.  
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
void UartCommandShell(void);


/*******************************************************************************
 *
 *   FUNCTION
 *
 *      UartExecuteCommandEx
 *
 *   DESCRIPTION
 *
 *      Exexute a command string.
 *
 *   ARGUMENTS
 *
 *      szCommand - command & arguments string of this command to run.
 *
 *   RETURN
 *   
 *      TRUE   - Successful.
 *      FALSE  - Failed.
 *
*******************************************************************************/
MMP_BOOL UartExecuteCommandEx( char* szCommand );


/*******************************************************************************
 *
 *   FUNCTION
 *
 *      UartRegisterUartCmdList
 *
 *   DESCRIPTION
 *
 *      Register a command list into uart command set.
 *
 *   ARGUMENTS
 *
 *      pUartCmdList - Pointer of command arrays. The last command must be end of
 *                     a NULL command. 
 *                     For ex. {0,0,0,0}
 *
 *
 *   RETURN
 *   
 *      TRUE   - Successful.
 *      FALSE  - Failed.
 *
*******************************************************************************/
MMP_BOOL UartRegisterUartCmdList( PUARTCOMMAND pUartCmdList );


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

/*******************************************************************************
 *
 *   FUNCTION
 *
 *      printc
 *
 *   DESCRIPTION
 *
 *      a lite printf command. 
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
printc( char* szFormat, ... );
void
printd( char* szFormat, ... );
void print_dbg( char* szFormat, ... );

/*******************************************************************************
 *
 *   FUNCTION
 *
 *      sscanfl
 *
 *   DESCRIPTION
 *
 *      a lite sscanf command.
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
int
sscanfl( char* szInput, char* szFormat, ... );


/*******************************************************************************
 *
 *   FUNCTION
 *
 *      AsciiToInt
 *
 *   DESCRIPTION
 *
 *      char to interger.
 *
 *   ARGUMENTS
 *
 *      szNumber - Number in ASCII
 *      base     - Number base
 *      iMaxLength - Max length of digits
 *   RETURN
 *   
 *      N/A
 *
*******************************************************************************/
int
AsciiToInt( char** szNumber, int base );

#endif // !defined(_UARTSHELL_H__810F924F_40C9_4309_9ED6_80DCB4651F07__INCLUDED_)
