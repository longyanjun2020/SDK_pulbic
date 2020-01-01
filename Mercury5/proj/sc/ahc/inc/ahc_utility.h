/** @file ahc_utility.h

@brief Header file of the ahc_utility
@author 
@since 
@version
- 1.0 Original version
*/

#ifndef _AHC_UTILITY_H_
#define _AHC_UTILITY_H_

/*===========================================================================
 * Include files
 *===========================================================================*/

#include "ahc_common.h"
#include "mmp_gpio_inc.h"
#include "UartShell_inc.h"

/** @name API Portability
@{ */

/*===========================================================================
 * Macro define
 *===========================================================================*/

/* ESCAPE CODE FOR UART COLOR PRINT */
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

/* MARCO OF ESCAPE CODE FOR UART COLOR PRINT */
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

/*===========================================================================
 * Structure define
 *===========================================================================*/


/*===========================================================================
 * Function prototype
 *===========================================================================*/

int 		sscanfl( char* szInput, char* szFormat, ... );
void 		printc( char* szFormat, ... );

AHC_BOOL 	AHC_Uart_GetDebugString(MMP_UBYTE uart_id, MMP_BYTE *bDebugString, MMP_ULONG *ulDebugStringLength);
AHC_BOOL 	AHC_UartExecuteCommand( char* szCommand );
AHC_BOOL 	AHC_UartRegisterUartCmdList( PUARTCOMMAND pUartCmdList );
AHC_BOOL    AHC_UART_Write(char *pWrite_Str, UINT32 ulLength);
AHC_BOOL	DramToFile( INT8* szFilename, INT8* pbyBuffer, UINT32 ulSize );
AHC_BOOL 	FileToDram( INT8* szFilename, INT8* pbyBuffer, UINT32 ulFilePos, UINT32 ulSize );
AHC_BOOL 	AHC_IsFileExist( INT8* szFilename );
AHC_BOOL 	AHC_CheckEngineerMode( INT8* szFilename, MMP_GPIO_PIN pioKeyPress );
AHC_BOOL 	AHC_IsCalibrationMode(void);

void 		AHC_UTILITY_Int2Str(UINT32 value, INT8 *string);

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
void printc( char* szFormat, ... );

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
 *      sscanfl( const char *szInput, const char *szFormat [, argument ] ... );
 *
 *      szInput  - Stored data 
 *      szFormat - Format-control string 
 *      argument - Optional arguments 
 *
 *   RETURN
 *   
 *      Each of these functions returns the number of fields successfully converted 
 *     and assigned; the return value does not include fields that were read but not assigned.
 *
*******************************************************************************/
int sscanfl( char* szInput, char* szFormat, ... );

/*******************************************************************************
 *
 *   FUNCTION
 *
 *      AHC_StrLen
 *
 *   DESCRIPTION
 *
 *      Get the length of a string.
 *
 *   ARGUMENTS
 *
 *      string - Null-terminated string 
 *
 *   RETURN
 *   
 *       Each of these functions returns the number of characters in string, 
 *     excluding the terminal NULL. No return value is reserved to indicate an error.
 *
*******************************************************************************/
unsigned int AHC_StrLen( char *string );


/*******************************************************************************
 *
 *   FUNCTION
 *
 *      StrChrReverse
 *
 *   DESCRIPTION
 *
 *      Find the last occurrence of character in str. 
 *
 *   ARGUMENTS
 *
 *       str
 *          C null-end string.
 *       character
 *           Character to be located. It is passed as its int promotion, but it is internally converted back to char for the comparison. 
 *  
 *   RETURN
 *   
 *      pointer to the last occurrence of character in str.
 *      If the character is not found, the function returns a null pointer.
 *
*******************************************************************************/
char * StrChrReverse( char * str, char character );



/*******************************************************************************
 *
 *   FUNCTION
 *
 *      GetPathDirStr
 *
 *   DESCRIPTION
 *
 *      Get the dir part of the full Path
 *
 *   ARGUMENTS
 *
 *       szDirName
 *           Output dir path.
 *       nDirBuffMaxSize
 *           The buffer size of szDirName
 *       szFullPath
 *           Input file full Path
 *
 *   RETURN
 *   
 *      The dir part of the path name
 *
*******************************************************************************/
AHC_BOOL GetPathDirStr( char* szDirName, int nDirBuffMaxSize, char* szFullPath );
AHC_BOOL GetPathFileNameStr(char* szFileName, int nBuffMaxSize, char* szFullPath);
/*******************************************************************************
 *
 *   FUNCTION
 *
 *      AHC_Strcmp 
 *
 *   DESCRIPTION
 *
 *      Compare strings.
 *
 *   ARGUMENTS
 *
 *      string1, string2 - Null-terminated strings to compare.
 *
 *   RETURN
 *   
 *       The return value for each of these functions indicates the lexicographic relation of string1 to string2.
 *     relation of string1 to string2.
 *
 *     +--------------------------------------------------+
 *     |  Return Value   | Description                    |
 *     +--------------------------------------------------+
 *     |       < 0       | string1 less than string2      |
 *     |       0         | string1 identical to string2   |
 *     |       > 0       | string1 greater than string2   |
 *     +--------------------------------------------------+
 * 
*******************************************************************************/
int AHC_Strcmp( const char *string1, const char *string2 );

/*******************************************************************************
 *
 *   FUNCTION
 *
 *      AHC_Strncmp 
 *
 *   DESCRIPTION
 *
 *      Compare characters of two strings.
 *
 *   ARGUMENTS
 *
 *      string1, string2 - Strings to compare 
 *      count            - Number of characters to compare 
 *
 *   RETURN
 *   
 *       The return value indicates the relation of the substrings of string1 and string2 as follows.
 *     relation of string1 to string2:
 *     +--------------------------------------------------+
 *     |  Return Value   | Description                    |
 *     +--------------------------------------------------+
 *     |       < 0       | string1 less than string2      |
 *     |       0         | string1 identical to string2   |
 *     |       > 0       | string1 greater than string2   |
 *     +--------------------------------------------------+
 * 
*******************************************************************************/
int AHC_Strncmp( const char *string1, const char *string2, int count );

/*******************************************************************************
 *
 *   FUNCTION
 *
 *      AHC_LowCase 
 *
 *   DESCRIPTION
 *
 *      Convert a character to lower case.
 *
 *   ARGUMENTS
 *
 *      ch - input char to be conveted. 
 *
 *   RETURN
 *   
 *       The char converted. The input character is returned, if the input chart 
 *     is not between 'A' to 'Z'.
 * 
*******************************************************************************/
char AHC_LowCase( const char ch );

/*******************************************************************************
 *
 *   FUNCTION
 *
 *      AHC_UpperCase 
 *
 *   DESCRIPTION
 *
 *      Convert a character to upper case.
 *
 *   ARGUMENTS
 *
 *      ch - input char to be conveted. 
 *
 *   RETURN
 *   
 *       The character converted. The input character is returned, if the input character 
 *     is not between 'a' to 'z'.
 * 
*******************************************************************************/
char AHC_UpperCase( const char ch );

/*******************************************************************************
 *
 *   FUNCTION
 *
 *      AHC_Stricmp 
 *
 *   DESCRIPTION
 *
 *      Perform a lowercase comparison of strings.
 *
 *   ARGUMENTS
 *
 *      string1, string2 - Null-terminated strings to compare.
 *
 *   RETURN
 *   
 *       The return value indicates the relation of string1 to string2 as follows.
 *     relation of string1 to string2:
 *     +--------------------------------------------------+
 *     |  Return Value   | Description                    |
 *     +--------------------------------------------------+
 *     |       < 0       | string1 less than string2      |
 *     |       0         | string1 identical to string2   |
 *     |       > 0       | string1 greater than string2   |
 *     +--------------------------------------------------+
 * 
*******************************************************************************/
int AHC_Stricmp( const char *string1, const char *string2 );

/*******************************************************************************
 *
 *   FUNCTION
 *
 *      AHC_Strincmp 
 *
 *   DESCRIPTION
 *
 *      Perform a lowercase comparison of characters.
 *
 *   ARGUMENTS
 *
 *      string1, string2 - Strings to compare 
 *      count            - Number of characters to compare 
 *
 *   RETURN
 *   
 *       The return value indicates the relation of the substrings of string1 and string2 as follows
 *     relation of string1 to string2:
 *     +--------------------------------------------------+
 *     |  Return Value   | Description                    |
 *     +--------------------------------------------------+
 *     |       < 0       | string1 less than string2      |
 *     |       0         | string1 identical to string2   |
 *     |       > 0       | string1 greater than string2   |
 *     +--------------------------------------------------+
 * 
*******************************************************************************/
int AHC_Strincmp( const char *string1, const char *string2, int count );


/*******************************************************************************
 *
 *   FUNCTION
 *
 *      AHC_Strrchr 
 *
 *   DESCRIPTION
 *
 *      Locale the last occurence of the certain character c in the string pointed by s.
 *
 *   ARGUMENTS
 *
 *      s  - the string to be searched.
 *      C  - the char to find.
 *
 *   RETURN
 *   
 *      NULL     - Not found
 *      NON-NULL - the location of the found character
 * 
*******************************************************************************/
char *AHC_Strrchr(char *s, char c);

INT32 AHC_Strcasecmp(const INT8 *s1, const INT8 *s2);

#endif //_AHC_UTILITY_H_



