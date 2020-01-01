/*******************************************************************************
 *
 *   UartShell_inc.c
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


#if !defined(_UARTSHELL_INC_H_)
#define _UARTSHELL_INC_H_
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

#endif
