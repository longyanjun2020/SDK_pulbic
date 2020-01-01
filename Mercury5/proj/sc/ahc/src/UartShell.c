/*******************************************************************************
 *
 *   UartShell.c
 *
 *   Implementation of UartShell.
 *
 *   Copyright 2010 by Caesar Chang.
 *
 *
 *   AUTHOR : Caesar Chang
 *
 *   VERSION: 1.0
 *
 *
*******************************************************************************/


#include <stdio.h>
#include "includes_fw.h"
#include "UartShell_inc.h"
#include "UartShell.h"


#include <stdarg.h>
#include "isp_if.h"
#include "lib_retina.h"
#include "mmpf_uart.h"
#include "mmpf_system.h"
#if (MEM_MONITOR_EN)
#include "mmps_dma.h"
#include "mmu.h"
#endif       
#include "AHC_Config_SDK.h"
#include "gui_global.h" //For MAX,MIN

#include "ahc_menu.h"
#include "ahc_message.h"
#include "ahc_general.h"
//
/*******************************************************************************
 *
 *   DEFINITIONS OF PRINTC
 *
*******************************************************************************/

// The max digits for a 32bit integer
#define DIGIT_STRING_LENGTH_OF_INT32     12
#define IS_A_DIGIT(x)                    ((x >='0') && (x <='9'))
#ifndef MAX_PRINTF_OUTPUT_STRING
#define MAX_PRINTF_OUTPUT_STRING         256
#endif
#ifndef PRINTC_STRNCMP_LEN
#define PRINTC_STRNCMP_LEN               128
#endif
#define SUPPORT_CHAR_FILL
//for Mem Monitor use
#define MEMORY_MONITOR_MAX_NUM            8

/*******************************************************************************
 *
 *   MARCOs
 *
*******************************************************************************/

#define IS_WHITE(x)                 ( (x) == ' ' || (x) == '\t' )
#define IS_SPACE(x)                 IS_WHITE(x)
#define EAT_WHITE(x)                while( IS_WHITE(*(x))) x++;
//#define EAT_NON_WHITE(x)        while( !IS_WHITE(*(x))) x++;
#define EAT_NON_WHITE(x)            while( *(x)&&!IS_WHITE(*(x))) x++;
#define IS_A_DIGIT(x)               ((x >='0') && (x <='9'))
#define EAT_NON_WHITE_NON_DIGIT(x)  while( *(x)&&!IS_WHITE(*(x)) && !IS_A_DIGIT(*(x))) x++;

#define EAT_REST_STRING(x)        while( (*x) != '\0' && *(x) != '\"'  ) x++;

/*******************************************************************************
 *
 *   UART COMMAND LIST ARRAY
 *
*******************************************************************************/
static PUARTCOMMAND sUartCmdListArray[MAX_NUMBER_OF_UART_CMD_LIST];
static int          uiUartCmdListNumber            = 0;


/*******************************************************************************
 *
 *   INTERGER TO STRING
 *
*******************************************************************************/
static char* Int32ToAscii(unsigned int uiVal, char* pbyBuffer, unsigned int uiBase, int iFill )
{                                                                                              
    // Starting from offset 32 as the worst case right hand side for binary radix
    unsigned int i = DIGIT_STRING_LENGTH_OF_INT32;

    char chFill = (char) iFill;

    iFill       = iFill >> 8;

    // NULL terminate the string
    pbyBuffer[i] = '\0'; 

    // Put the digit number 
    do                                                                                         
    {                                                                                          
        i--;                                                                                   
        iFill--;                                                                               
        pbyBuffer[i] = "0123456789ABCDEF"[uiVal % uiBase];                                     
        uiVal /= uiBase;                                                                       
    }                                                                                          
    while ((uiVal > 0) && (i > 0));                                                            

#ifdef SUPPORT_CHAR_FILL

    // Put the fill char. 
    while( iFill >0 && i>0 )
    {
        i--; iFill--;
        pbyBuffer[i] = chFill;
    }

#endif

    return &pbyBuffer[i];                                                                      
} 

void FloatToAscii(double uiVal, char* pbyBuffer, unsigned int uiBase, int iFill)
{                                                                                              
    int n,i=0,k=0, l;
    // NULL terminate the string
    //pbyBuffer[DIGIT_STRING_LENGTH_OF_INT32] = '\0'; 
     n=(int)uiVal;
     while(n>0)
      {
        uiVal/=uiBase;
        n=(int)uiVal;
        i++;
     }
     *(pbyBuffer+i) = '.';
     uiVal *= uiBase;
     n = (int)uiVal;
     uiVal = uiVal-n;
     l = i + 1;

     while(l > 0)
     {
       if(k == i) {
           k++;
           l = iFill;
       }
       *(pbyBuffer+k)=48+n;
       uiVal *= uiBase;
       n = (int)uiVal;
       uiVal = uiVal-n;
       k++;
       l--;
     }
     *(pbyBuffer+k) = '\0'; 
                                                                         
} 

/*******************************************************************************
 *
 *   FUNCTION
 *
 *      printc
 *
 *   DESCRIPTION
 *
 *      a lite printf command. Support %d , %x , %X , %u, %s, %c.
 *
 *   ARGUMENTS
 *
 *      N/A
 *
 *   RETURN
 *   
 *      String size include NULL char.
 *
*******************************************************************************/
int
vsprintc( char* szOutput, char* szFormat, va_list arg_list )
{

    // Temp buffer for integer print
    char  szDigitTmp[DIGIT_STRING_LENGTH_OF_INT32+1];

    char* pOutput;

    char* pFormat;

    pOutput = szOutput;
    pFormat = szFormat;

    while( *pFormat != NULL )
    {
        if( *pFormat == '%' )
        {
            int  base  = 10;
            int  bSign = FALSE;
            int  iFill=0;
            char chFill = ' ';

            pFormat++;

#ifdef SUPPORT_CHAR_FILL

            if( IS_A_DIGIT(*pFormat) )
            {
                // If start from '0', It means fill with '0'
                if( *pFormat == '0' )
                {
                    chFill = '0';
                    pFormat++;
                }

                while(IS_A_DIGIT(*pFormat))
                {
                    iFill = iFill * 10 + ( (*pFormat++) - '0');
                }

                if( iFill > DIGIT_STRING_LENGTH_OF_INT32 )
                {
                    iFill = DIGIT_STRING_LENGTH_OF_INT32;
                }
            }
#endif
            switch( *pFormat++ )
            {

                // Print hex number
                case 'X':
                case 'x':
                {
                    base = 16;
                }

                // Print signed DEC number
                case 'd':
                {
                    bSign = TRUE;
                }

                // Print unsigned DEC number
                case 'u':
                {
                    int   i    = va_arg(arg_list, int );
                    char* pTmp ;

                    if( base != 16    &&
                        bSign == TRUE &&
                        i < 0 )
                    {
                        i = -i;
                        *pOutput++ = '-';
                    }
                    
                    pTmp = Int32ToAscii( i, szDigitTmp, base, (iFill <<8) | chFill );
                    
                    while( *pTmp )
                    {
                        *pOutput++ = *pTmp++;
                    }

                }
                break;

                case 's':
                {
                    char* pTmp= va_arg(arg_list, char* );

                    if( pTmp )
                    {
                        while( *pTmp )
                        {
                            *pOutput++ = *pTmp++;
                        }
                    }
                    break;
                }

                case 'c':
                {
                    char ch = va_arg(arg_list, int );
                    *pOutput++ = ch;
                    break;
                }
                case 'f':
                {
                    
                    double i = va_arg(arg_list, double );
                    int j;
                    char pTmp[64]={0} ;

                    if( base != 16    &&
                        i < 0 )
                    {
                        i = -i;
                        *pOutput++ = '-';
                    }
                    FloatToAscii( i, pTmp, base,(iFill <<8) | chFill);
                    j = 0;
                    while( pTmp[j] && j<20)
                    {                       
                        *pOutput++ = pTmp[j];
                        j++;
                    }
                }
                default:
                {
                    // for %? case
                    *pOutput++ = '%';
                    *pOutput++ = *pFormat++;
                }
                break;
            }

        }
#if 1
        else if( *pFormat == '\n' )
        {
            //char* pPre = pFormat - 1;

            if( pFormat - szFormat == 0      ||
                *(pFormat-1)       !=   '\r'   )
            {
                *pOutput++ = '\r';
            }

            *pOutput++ = *pFormat++;
        }
#endif
        else
        {
            *pOutput++ = *pFormat++;
        }

    }

    // Put the NULL terminator at the end of the string;
    *pOutput++ = '\0';
   
    return pOutput - szOutput;

}

int
sprintc( char* szOutput, char* szFormat, ... )
{

    int n;

    va_list arg_list;


    va_start( arg_list, szFormat );

    n = vsprintc( szOutput, szFormat, arg_list );

    va_end( arg_list );
    
    return n;

}

/** Another version of printf
 *
 * printc eliminates duplicated lines and printd print out every line.
 * @param szFormat
 */
void printd( char* szFormat, ... )
{

    int n, i, j;
    va_list arg_list;

    // Output buffer to UART
    char  szOutput[MAX_PRINTF_OUTPUT_STRING];

    va_start( arg_list, szFormat );

    // n = vsprintc( szOutput, szFormat, arg_list );
    n = vsnprintf( szOutput, MAX_PRINTF_OUTPUT_STRING, szFormat, arg_list );

    va_end( arg_list );

    n = MAX( n, 0 );
    
    n = MIN( n, MAX_PRINTF_OUTPUT_STRING ); 

    j = 0;
    for (i=0; i<n; i++) {
        if ((szOutput[i] == '\n') && (szOutput[i-1] != '\r')) {
            MMPF_Uart_Write(DEBUG_UART_NUM, szOutput + j, i - j);
            MMPF_Uart_Write(DEBUG_UART_NUM, "\r\n", 2);
            j = i + 1;
        }
    }
    MMPF_Uart_Write(DEBUG_UART_NUM, szOutput + j, i - j + 1);
}

/** Another version of printf
 *
 * This version it only prints short message and would be executed as quick as possible.
 * The target would be < 1ms so that OS tick would not be missed
 * @param szFormat
 */
void print_dbg( char* szFormat, ... )
{
    unsigned int n;
    va_list arg_list;

    // Output buffer to UART
    #define MAX_PRINT_DBG_LEN 20
    char  szOutput[MAX_PRINT_DBG_LEN];
    OS_CRITICAL_INIT();

    va_start( arg_list, szFormat );

    n = (unsigned int)vsnprintf( szOutput, MAX_PRINT_DBG_LEN, szFormat, arg_list );

    va_end( arg_list );

    n = MIN( n, MAX_PRINT_DBG_LEN );

    OS_ENTER_CRITICAL();
    MMPF_Uart_Write(DEBUG_UART_NUM, szOutput, n);
    OS_EXIT_CRITICAL();
}

void print_static( char* szFormat, ... )
{

    static int n, i, j;
    static va_list arg_list;

    // Output buffer to UART
    static char  szOutput[MAX_PRINTF_OUTPUT_STRING];

    va_start( arg_list, szFormat );

    // n = vsprintc( szOutput, szFormat, arg_list );
    n = vsnprintf( szOutput, MAX_PRINTF_OUTPUT_STRING, szFormat, arg_list );

    va_end( arg_list );

    j = 0;
    for (i=0; i<n; i++) {
        if ((szOutput[i] == '\n') && (szOutput[i-1] != '\r')) {
            MMPF_Uart_Write(DEBUG_UART_NUM, szOutput + j, i - j);
            MMPF_Uart_Write(DEBUG_UART_NUM, "\r\n", 2);
            j = i + 1;
        }
    }
    MMPF_Uart_Write(DEBUG_UART_NUM, szOutput + j, i - j + 1);
}

/*******************************************************************************
 *
 *   FUNCTION
 *
 *      printc
 *
 *   DESCRIPTION
 *
 *      a lite printf command. Support %d , %x , %X , %u, %s, %c.
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
printc( char* szFormat, ... )
{

    //UartSendTrace(szFormat);
    int n, i;
    va_list arg_list;

    // Output buffer to UART
    static char szLast[MAX_PRINTF_OUTPUT_STRING+1] = {0};
    static int  rep_cnt;
    static char  szOutput[MAX_PRINTF_OUTPUT_STRING] = {0};

#if 1

    va_start( arg_list, szFormat );

    // n = vsprintc( szOutput, szFormat, arg_list );
    n = vsnprintf( szOutput, MAX_PRINTF_OUTPUT_STRING, szFormat, arg_list );

    va_end( arg_list );

    n = MAX( n, 0 );

    n = MIN( n, MAX_PRINTF_OUTPUT_STRING );

    if (strncmp(szLast, szOutput, PRINTC_STRNCMP_LEN)) {
#if 0
        if (rep_cnt) {
            int m;
            char szOutLast[MAX_PRINTF_OUTPUT_STRING];
            m = sprintf( szOutLast, "\r\n[[ x%d ]] >>>> %s\r\n", rep_cnt+1, szLast );
            MMPF_Uart_Write(DEBUG_UART_NUM, szOutLast, m );
        }
#endif
        for (i=0; i<n; i++) {
            if (szOutput[i] == '\n')
                MMPF_Uart_Write(DEBUG_UART_NUM, "\r\n", 2);
            else
                MMPF_Uart_Write(DEBUG_UART_NUM, szOutput+i, 1 );
        }
        strcpy( szLast, szOutput );
        rep_cnt = 0;
    }
    else {
        rep_cnt++;
    }

#else

    // Temp buffer for interger print
    char  szDigitTmp[DIGIT_STRING_LENGTH_OF_INT32+1];

    char* pOutput;

    char* pFormat;

    pOutput = szOutput;
    pFormat = szFormat;

    va_start( arg_list, szFormat );

    while( *pFormat != NULL )
    {
        if( *pFormat == '%' )
        {
            int  base  = 10;
            int  bSign = FALSE;
            int  iFill=0;
            char chFill = ' ';

            pFormat++;

#ifdef SUPPORT_CHAR_FILL

            if( IS_A_DIGIT(*pFormat) )
            {
                // If start from '0', It means fill with '0'
                if( *pFormat == '0' )
                {
                    chFill = '0';
                    pFormat++;
                }

                while(IS_A_DIGIT(*pFormat))
                {
                    iFill = iFill * 10 + ( (*pFormat++) - '0');
                }

                if( iFill > DIGIT_STRING_LENGTH_OF_INT32 )
                {
                    iFill = DIGIT_STRING_LENGTH_OF_INT32;
                }
            }
#endif
            switch( *pFormat++ )
            {

                // Print hex number
                case 'X':
                case 'x':
                {
                    base = 16;
                }

                // Print singend dec number
                case 'd':
                {
                    bSign = TRUE;
                }

                // Print unsingend dec number
                case 'u':
                {
                    int   i    = va_arg(arg_list, int );
                    char* pTmp ;

                    if( base != 16    &&
                        bSign == TRUE &&
                        i < 0 )
                    {
                        i = -i;
                        *pOutput++ = '-';
                    }
                    pTmp = Int32ToAscii( i, szDigitTmp, base, (iFill <<8) | chFill );

                    while( *pTmp )
                    {
                        *pOutput++ = *pTmp++;
                    }

                }
                break;

                case 's':
                {
                    char* pTmp= va_arg(arg_list, char* );
                    if( pTmp )
                    {
                        while( *pTmp )
                        {
                            *pOutput++ = *pTmp++;
                        }
                    }
                    break;
                }

                case 'c':
                {
                    char ch = va_arg(arg_list, int );
                    *pOutput++ = ch;
                    break;
                }

                case 'f':
                {
                    double   i    = va_arg(arg_list, double );
                    char* pTmp ;

                    if( base != 16    &&
                        bSign == TRUE &&
                        i < 0 )
                    {
                        i = -i;
                        *pOutput++ = '-';
                    }
                    //pTmp = Int32ToAscii( i, szDigitTmp, base, (iFill <<8) | chFill );
                    FloatToAscii( i, pTmp, base, (iFill <<8) | chFill );
                    while( *pTmp )
                    {
                        *pOutput++ = *pTmp++;
                    }
                }

                default:
                {
                    // for %? case
                    *pOutput++ = '%';
                    *pOutput++ = *pFormat++;
                }
            }

        }
#if 1
        else if( *pFormat == '\n' )
        {
            *pOutput++ = *pFormat++;
            *pOutput++ = '\r';
        }
#endif
        else
        {
            *pOutput++ = *pFormat++;
        }

    }

    // Put the NULL terminator at the end of the string;
    *pOutput++ = '\0';

    va_end( arg_list );

    MMPF_Uart_Write(DEBUG_UART_NUM, szOutput, pOutput - szOutput );

#endif



}


/** Yet another version of printf
 *
 * printc can't accommodate long length string, but this one can help.
 * @note Differ from MMPF_Uart_Write this function replace \n with \r\n due to printd
 * @param szStr the long string
 */
void printstr( char* szStr )
{
    //size_t i, len = strlen(szStr);
    int len = (int)strlen(szStr);
    char c, *ptr, *eos = szStr + len;

    //for (i=0; i<len; i+=MAX_PRINTF_OUTPUT_STRING, ptr+=MAX_PRINTF_OUTPUT_STRING) {
    for (ptr = szStr; ptr < eos; len-=MAX_PRINTF_OUTPUT_STRING-1, ptr += MAX_PRINTF_OUTPUT_STRING-1) {
        if (len > MAX_PRINTF_OUTPUT_STRING) {
            c = ptr[MAX_PRINTF_OUTPUT_STRING];
            ptr[MAX_PRINTF_OUTPUT_STRING] = 0;
            //--------------------------------
            printd( ptr );
            //--------------------------------
            ptr[MAX_PRINTF_OUTPUT_STRING] = c;
        } else {
            printd( ptr );
        }
    }
}


/*******************************************************************************
 *
 *   FUNCTION
 *
 *      MemoryDump
 *
 *   DESCRIPTION
 *
 *      Dump memory to UART.
 *
 *   ARGUMENTS
 *
 *      pbyBuffer  - Starg address.
 *      ulSize     - Size to dump.
 *
 *   RETURN
 *   
 *      N/A
 *
 *
*******************************************************************************/

void
MemoryDump( char* pbyBuffer, MMP_ULONG ulSize )
{
    MMP_ULONG i;
    char* pbyPtr = pbyBuffer;
    char  sz[17]={0};
    
    for( i=0; i< ulSize; i++)
    {
        int iOffset = i%16;
        if( iOffset == 0 )
        {
            sz[16]='\0';
            printd(" %s", sz );
            printd( ESC_FG_COLOR_PURPLE "\n0x%08X " ESC_FG_COLOR_BLUE, pbyPtr );
        }

        if( *pbyPtr >= 0x20 &&  *pbyPtr < 0x80 )
        {
            sz[iOffset] = *pbyPtr;
        }
        else
        {
            sz[iOffset] = '.';
        }

        printd( " %02X", *pbyPtr++ );

    }

    {
        
        if( i%16 == 0 )
        {
            sz[16]='\0';
        }
        else
        {
            sz[i%16]='\0';
        }

        printd(" %s", sz );
    }

    
    printd("\n\n" ESC_ATR_COLOR_DEFAULT );
}


static int
UartCmdRemoveBackSpace( char* szString )
{
    char*   ptr = szString;
    int     i=0;
    
    while(*ptr)
    {
        if( *ptr == 0x08 )
        {
            if( i>0 )
            {
                i--;
            }

            ptr++;
            continue;
        }
        szString[i] = *ptr;
        ptr++;
        i++;
    }
    szString[i] = '\0';
    
    return i;
}


void
UartCmdRemoveNextLine( char* szString )
{
    char*   ptr = szString;
    
    while(*ptr)
    {
        if( *ptr == '\n' )
        {
            *ptr ='\0';
            return;
        }
    }
}



int
AsciiToInt( char** szNumber, int base, int iMaxLength )
{
    char* pInputStart   = *szNumber;
    char* pInput        = *szNumber;
    int   iVal          = 0;
    int   bNegative     = FALSE;
    
    EAT_WHITE(pInput);
    
    if( *pInput == '-' )
    {
        bNegative   = TRUE;
        pInput++;
    }

    while( *pInput &&  (pInput-pInputStart<iMaxLength) )
    {
        int     iDigit;
        char    chDigit = *pInput;
        
        // Get the value of the digit
        if( chDigit >='0' && chDigit <= '9' )
        {
            iDigit = chDigit - '0';
        }
        else if( chDigit >='A' && chDigit <= 'F' )
        {
            iDigit = chDigit - 'A' + 10;
        }
        else if( chDigit >='a' && chDigit <= 'f' )
        {
            iDigit = chDigit - 'a' + 10;
        }
        else
        {
            // Unknown char.
            break;
        }

        iVal   = iVal*base + iDigit;

        pInput++;
    }

    if( bNegative )
    {
        iVal = -iVal;
    }

    // Set the pointer with offset back.
    *szNumber = pInput;

    return iVal;
}

int
sscanfl( char* szInput, char* szFormat, ... )
{
    va_list arg_list;   
    char*   pFormat = szFormat;
    char*   pInput  = szInput;
    int     iVarParse = 0;

    va_start( arg_list, szFormat );
    while( *pFormat && *pInput )
    {
        // Eat leading while space
        EAT_WHITE(pFormat);
        EAT_WHITE(pInput);

        if( *pFormat == '%' )
        {
            int  base = 10;
            int  iMaxStringLength = 100;
            MMP_BOOL bStopByDigit = FALSE;            
            pFormat++;

            if( IS_A_DIGIT(*pFormat) )
            {
                iMaxStringLength = 0;
                while(IS_A_DIGIT(*pFormat))
                {
                    iMaxStringLength = iMaxStringLength * 10 + ( (*pFormat++) - '0');
                }
                //iMaxStringLength;
            }
            
            switch( *pFormat )
            {
                case 'X':
                case 'x':
                {
                    base = 16;
                    if( pInput[0] == '0' && ( pInput[1] == 'x' || pInput[1] == 'X') )
                    {
                        pInput += 2;
                    }
                }
                case 'd':
                {
                    int* piData= va_arg(arg_list, int* );
                    
                    int  iValue = AsciiToInt( &pInput, base, iMaxStringLength );

                    *piData   = iValue;

                    pFormat++;
                    iVarParse++;
                    break;
                }

                case 'z':
                    // stop right before any digit
                    bStopByDigit = TRUE;
                case 's':
                {               
                    char* sz =  (char*)va_arg(arg_list, int* );
                    int   i  = 0;
                    MMP_BOOL  bLong = FALSE;

                    iVarParse++;

                    if( *pInput == '\"' )
                    {
                        bLong = TRUE;
                        pInput++;
                    }

                    while(1)
                    {
                        char chCurrent = *pInput;

                        if( bLong == TRUE )
                        {
                            // TBD:: check i < max number of char                       
                            if( chCurrent == '\"' )
                            {
                                pInput++;
                                sz[i] = '\0';
                                break;
                            }   
                            else if( i < iMaxStringLength )
                            {
                                sz[i] = chCurrent;
                            }
                            else
                            {
                                EAT_REST_STRING(pInput);
                                if( *pInput == '\"' )
                                {
                                    pInput++;
                                }
                                sz[i] = '\0';
                                break;
                            }
                        }
                        else
                        {
                            if( bStopByDigit &&
                                IS_A_DIGIT(chCurrent) )
                            {
                                sz[i] = '\0';
                                break;
                            }
                            
                            if( IS_WHITE(chCurrent))
                            {
                                sz[i] = '\0';
                                pInput++;
                                break;
                            }
                            else if( chCurrent == '\0')
                            {
                                sz[i] = '\0';
                                break;
                            }

                            // TBD:: check i < max number of char                       
                            if( i < iMaxStringLength )
                            {
                                sz[i] = chCurrent;
                            }
                            else
                            {
//                              EAT_NON_WHITE(pInput);
                                sz[i] = '\0';
                                break;
                            }
                        }                       
                        pInput++;
                        i++;
                    }

                    pFormat++;

                    break;
                }
                default:
                    pFormat++;
            }
        }
        else if( *pFormat == *pInput )
        {
            pInput++;
            pFormat++;
        }
        else
        {
            pFormat++;
        }
    }

    va_end( arg_list );

    return iVarParse;
}



MMP_BOOL
UartRegisterUartCmdList( PUARTCOMMAND pUartCmdList )
{
    // Check if the array is full.
    if( uiUartCmdListNumber >= MAX_NUMBER_OF_UART_CMD_LIST )
    {
        return FALSE;
    }

    sUartCmdListArray[uiUartCmdListNumber++] = pUartCmdList;

    return TRUE;
}

const char divider[] = 
{
    ' ','\t','\0','\n'
};

MMP_BOOL
IsDivider( char ch )
{
    int i;
    for( i=0; i<sizeof(divider); i++ )
    {
        if( ch == divider[i] )
        {
            return TRUE;
        }
    }
    return FALSE;
}


int
UartCmdLenth( char* pCmd )
{
    int i=0;
    while( !IsDivider( *pCmd++ ) )
    {
        i++;
    }

    return i;
}

MMP_BOOL
UartCmdCompare( char* pSrcCmd, char* pDstCmd )
{

    int iLength = 0;
    int iLength2 = 0;

    iLength = UartCmdLenth( pDstCmd ) ;
    iLength2 = strlen( pSrcCmd ) ;
    if( iLength != iLength2 )
    {
        return FALSE;
    }

    if( strncmp( pSrcCmd, pDstCmd, iLength )==0 )
    {
        return TRUE;
    }

    return FALSE;
}

PUARTCOMMAND
UartFindCommand( char* szCommand )
{
    int i;

    EAT_WHITE(szCommand);

    for( i=0; i< uiUartCmdListNumber; i++)
    {
        PUARTCOMMAND psCmd = sUartCmdListArray[i];

        while( psCmd->szCommandString != NULL )
        {

            if ( UartCmdCompare( psCmd->szCommandString , szCommand)  )
            {
                return psCmd;
            }
            psCmd++;
        }

    }

    return NULL;

}


MMP_BOOL
UartExecuteCommandEx( char* szCommand )
{
    PUARTCOMMAND psCmd;
    MMP_BOOL  bFoundCommand = FALSE;

    EAT_WHITE(szCommand);

    psCmd = UartFindCommand( szCommand );

    if( psCmd != NULL )
    {
        int iCommandLength = UartCmdLenth( szCommand );

        bFoundCommand = TRUE;
    
        psCmd->pFunc( &szCommand[iCommandLength] );
    }

    return bFoundCommand;

}


MMP_BOOL
UartExecuteCommand2( char* szCommand )
{
    int i;
    MMP_BOOL  bFoundCommand = FALSE;

    EAT_WHITE(szCommand);

    for( i=0; i< uiUartCmdListNumber; i++)
    {
        PUARTCOMMAND psCmd = sUartCmdListArray[i];

        while( psCmd->szCommandString != NULL )
        {

            if ( UartCmdCompare( psCmd->szCommandString , szCommand)  )
            {
                int iCommandLength = strlen( psCmd->szCommandString );
                bFoundCommand = TRUE;

                psCmd->pFunc( &szCommand[iCommandLength] );
                break;
            }
            psCmd++;
        }

    }

    return bFoundCommand;
}

MMP_BOOL
UartExecuteCommand( char* szCommand )
{
    int i;
    MMP_BOOL  bFoundCommand = FALSE;


    for( i=0; i< uiUartCmdListNumber; i++)
    {
        PUARTCOMMAND psCmd = sUartCmdListArray[i];

        while( psCmd->szCommandString != NULL )
        {
            int iCommandLength = strlen( psCmd->szCommandString );

            //TBD: EAT WHITE TAB

            if ( strncmp( psCmd->szCommandString , szCommand, iCommandLength ) == 0 )
            {
                if( szCommand[iCommandLength] == ' '  || 
                    szCommand[iCommandLength] == '\t' ||
                    szCommand[iCommandLength] == '\0'  )
                {
                    bFoundCommand = TRUE;
                    psCmd->pFunc( &szCommand[iCommandLength] );
                    break;
                }
            }
            psCmd++;
        }

    }

    return bFoundCommand;
}

MMP_BOOL UartCommandGetLine( char* byStringBuffer, MMP_ULONG* pulLength )
{
    RTNA_DBG_Gets(byStringBuffer, pulLength);
    return TRUE;
}


void UartCommandShell(void)
{
    MMP_BYTE    str[128]={0};
    MMP_ULONG   len;
    MMP_BOOL        bCommandFound = FALSE;
    MMP_BOOL        bExitShell    = FALSE;
    while(1)
    {
        printc( FG_BLUE("UART>"));

        UartCommandGetLine(str, &len);

        str[len] = '\0';

        // Remove next line
        {
            int n;
            for( n=0; n<len; n++ )
            {
                if( str[n] == 0x0D )
                    str[n] = '\0';
            }
        }
        UartCmdRemoveBackSpace(str);

        printc( "\n" );

        if( strlen(str) == 0 )
        {
            continue;
        }

        if( str[0] == 'x' )
        {
            bExitShell = TRUE;
        }

        if( bExitShell )
        {
            break;
        }

        bCommandFound  = UartExecuteCommandEx( str );
        if( !bCommandFound )
        {
            printc( FG_RED("\'%s\' (%d) is a invalid command!\n"), str, len );
            MemoryDump( str, len+1 );
        }
    }

}

//------------------------------------------------------------------------------
//
//  UART command
//
//------------------------------------------------------------------------------

void
UartCmdWriteRegister( char* szParam )
{
    MMP_ULONG uiAddress;
    MMP_ULONG uiValue;
    sscanfl( szParam, "%X %d", &uiAddress, &uiValue );

    *(volatile MMP_ULONG*)(uiAddress) = uiValue;

    printc( "0x%08X = 0x%08X \n", uiAddress, *(volatile MMP_ULONG*)(uiAddress) );

}

void
UartCmdReadRegister( char* szParam )
{
    MMP_ULONG uiAddress;
    MMP_ULONG uiValue;
    sscanfl( szParam, "%X", &uiAddress );

    uiValue = *(MMP_ULONG*)uiAddress;

    printc( "0x%08X = 0x%08X \n", uiAddress, uiValue );
}

// CarDV
void
UartCmdWriteRegisterByte( char* szParam )
{
    MMP_ULONG uiAddress;
    MMP_UBYTE ubValue;
    sscanfl( szParam, "%X %X", &uiAddress, &ubValue );

    *(volatile MMP_UBYTE*)(uiAddress) = ubValue;
    printc( "0x%08X set to 0x%08X \n", uiAddress, ubValue );
    printc( "0x%08X = 0x%08X \n", uiAddress, *(volatile MMP_UBYTE*)(uiAddress) );
}

// CarDV
void
UartCmdReadRegisterByte( char* szParam )
{
    MMP_ULONG uiAddress;
    MMP_UBYTE ubValue;
    sscanfl( szParam, "%X", &uiAddress );

    ubValue = *(MMP_UBYTE*)uiAddress;

    printc( "0x%08X = 0x%02X \n", uiAddress, ubValue );
}

void UartCmdDumpRegister( char* szParam )
{
    MMP_ULONG ulAddress;    
    MMP_ULONG reg_address;
    MMP_USHORT i,j;
    
    sscanfl( szParam, "%X", &ulAddress);
        
    printc("     reg   _0 _1 _2 _3 . _4 _5 _6 _7 . _8 _9 _A _B . _C _D _E _F\n");
    for (i=0;i<0x10;i++) {
        reg_address = ulAddress + (i << 4);
        printd(" %02Xh",reg_address);
        for (j=0;j<0x10;j++) {
            if ((j % 4) == 0)
                printd("  ");
            reg_address |= 0x80000000;
            printd("%02X ",(*(MMP_UBYTE *)(reg_address+j)) & 0xFF);
        }   
        printd("\n");
    }   
}

void UartCmdDumpISPinfo( char* szParam )
{
#if 0   
    printc("IQ  : gid=%d. eid=%d, tid=%d\n", 
            ISP_IF_IQ_GetID(0), //gid
            ISP_IF_IQ_GetID(1), //eid
            ISP_IF_IQ_GetID(2));    //tid
    
    printc("AE  : Shutter=0x%X(Base:0x%X) (%d)FPS, Again=0x%X, Dgain=0x%X, Lux=0x%X\n",
            ISP_IF_AE_GetShutter(),
            ISP_IF_AE_GetBaseShutter(),
            ISP_IF_AE_GetRealFPS(),
            ISP_IF_AE_GetAGain(),
            ISP_IF_AE_GetDGain(),
            ISP_IF_AE_GetLightCond());
    
    printc("AWB : GainR=0x%X, GainGr=0x%X, GainB=0x%X\n", 
            ISP_IF_AWB_GetGainR(),
            ISP_IF_AWB_GetGainG(),
            ISP_IF_AWB_GetGainB());
            
    printc("AF  : AFPos=0x%X, AFMODE=0x%X\n",
            ISP_IF_AF_GetPos(0), //Rogers:***
            ISP_IF_AF_GetDbgData(0));
#endif
}

void
UartCmdRepeatCmd( char* szParam )
{
     int iRepeatCount = 1;
     int iDelayInMs = 1;
     printc( "%s\n", szParam );

     sscanfl( szParam, "%d %d", &iRepeatCount ,&iDelayInMs);

     EAT_WHITE(szParam)
     EAT_NON_WHITE(szParam)
     EAT_WHITE(szParam)
     EAT_NON_WHITE(szParam)
     EAT_WHITE(szParam)
     
     while( iRepeatCount-- > 0 )
     {
      MMPF_OS_Sleep(iDelayInMs);
      UartExecuteCommand2( szParam );
     }
}

void
UartCmdListAll( char* szParam )
{
    int i;

    for( i=0; i< uiUartCmdListNumber; i++)
    {
        PUARTCOMMAND psCmd = sUartCmdListArray[i];

        while( psCmd->szCommandString != NULL )
        {
            if( psCmd->szHelp == NULL )
            {
            
            }
            printc( "%s\t- %s\n", psCmd->szCommandString, psCmd->szHelp );
            psCmd++;
        }

    }

}



void
UartCmdHelp( char* szParam )
{
    PUARTCOMMAND psCmd;

    psCmd = UartFindCommand( szParam );

    if( psCmd != NULL )
    {
        printc( "Command Name:\n\t%s\n", psCmd->szCommandString );
        printc( "Description:\n\t%s\n", psCmd->szHelp );
        printc( "Usage:\n\t%s %s\n", psCmd->szCommandString, psCmd->szParameter );
    }

}

void
UartCmdMemoryDump( char* szParam )
{
    MMP_ULONG ulAddress;
    MMP_ULONG ulSize=512;
    sscanfl( szParam, "%X %d", &ulAddress, &ulSize );

    MemoryDump( (char*)ulAddress, ulSize );

}

void
UartCmdMemoryFill( char* szParam )
{
    MMP_ULONG ulAddress;
    MMP_ULONG ulSize = 16;
    char*     pbyPtr;
    MMP_ULONG i;
    MMP_ULONG len;
    
    sscanfl( szParam, "%X %d", &ulAddress, &ulSize );

    pbyPtr = (char*)ulAddress;

    for( i=0; i< ulSize; i++ )
    {
        MMP_ULONG ulValue;

        printc( "\n0x%08X  %02X:", pbyPtr, *pbyPtr );

        RTNA_DBG_Gets(szParam, &len);
        
        sscanfl( szParam, "%X", &ulValue );

        *pbyPtr = (char) ulValue;

        pbyPtr++;
    }
    printc( "\n" );

}

#include "mmps_sensor.h"

extern void RTNA_LCD_GetReg(MMP_ULONG reg, MMP_ULONG *value);
extern void RTNA_LCD_SetReg(MMP_ULONG reg, MMP_UBYTE value);

void UartCmdReadSensorRegister( char* szParam )
{
    MMP_ERR ret_val;
    MMP_USHORT uiAddress, uiValue;
    
    sscanfl( szParam, "%X", &uiAddress );
    ret_val = MMPS_Sensor_GetSensorReg(PRM_SENSOR, uiAddress, &uiValue);
    if(MMP_ERR_NONE == ret_val){
        printc( "Sensor[0x%04X] = 0x%04X \n", uiAddress, uiValue );
    }
    else{
        printc( "Read sensor register error.\n");
    }    
}

void UartCmdReadSensor2Register( char* szParam )
{
    MMP_ERR ret_val;
    MMP_USHORT uiAddress, uiValue;

    sscanfl( szParam, "%X", &uiAddress );
    ret_val = MMPS_Sensor_GetSensorReg(SCD_SENSOR, uiAddress, &uiValue);
    if(MMP_ERR_NONE == ret_val){
        printc( "Sensor2[0x%04X] = 0x%04X \n", uiAddress, uiValue );
    }
    else{
        printc( "Read sensor2 register error.\n");
    }
}

void UartCmdWriteSensorRegister( char* szParam)
{
    MMP_ERR ret_val;
    MMP_USHORT uiAddress, uiValue;

    sscanfl( szParam, "%X %X", &uiAddress, &uiValue );
    ret_val = MMPS_Sensor_SetSensorReg(PRM_SENSOR, uiAddress, uiValue);
    if(MMP_ERR_NONE == ret_val){
        printc( "Sensor[0x%04X] = 0x%04X \n", uiAddress, uiValue );
    }
    else{
        printc( "Write sensor register error.\n");
    }
}

void UartCmdWriteSensor2Register( char* szParam)
{
    MMP_ERR ret_val;
    MMP_USHORT uiAddress, uiValue;

    sscanfl( szParam, "%X %X", &uiAddress, &uiValue );
    ret_val = MMPS_Sensor_SetSensorReg(SCD_SENSOR, uiAddress, uiValue);
    if(MMP_ERR_NONE == ret_val){
        printc( "Sensor[0x%04X] = 0x%04X \n", uiAddress, uiValue );
    }
    else{
        printc( "Write sensor register error.\n");
    }
}

void UartCmdReadLCDRegister( char* szParam )
{
    MMP_USHORT uiAddress;
    MMP_ULONG uiValue;
    
    sscanfl( szParam, "%X", &uiAddress );    
    RTNA_LCD_GetReg(uiAddress, &uiValue);      
    printc( "LCD[0x%04X] = 0x%04X \n", uiAddress, uiValue );
}

void UartCmdWriteLCDRegister( char* szParam)
{
    MMP_USHORT uiAddress, uiValue;

    sscanfl( szParam, "%X %X", &uiAddress, &uiValue );
    RTNA_LCD_SetReg(uiAddress, (MMP_UBYTE)(uiValue & 0xFF));
    printc( "LCD[0x%04X] = 0x%04X \n", uiAddress, uiValue );
}
/*******************************************************************************
 *
 *   FUNCTION
 *
 *      UartCmdMemoryMonitor
 *
 *   DESCRIPTION
 *
 *      Enable/Disable Memory Monitor
 *      To set each parameter(Memory up/low BD) in MemoryMonitorSetPara 
 *
 *   ARGUMENTS
 *
 *      Cmd : 1:enanble / 0:disable
 *
 *   RETURN
 *   
 *      N/A
 *
 *
*******************************************************************************/
void UartCmdMemoryMonitor( char* szParam )
{
}

#if (UVC_HOST_VIDEO_ENABLE)
void UartCmdHostUVCReverseGearDetection( char* szParam )
{
    //AHC_HostUVCSonixReverseGearDetection();
}
#endif

#if defined(CCIR656_OUTPUT_ENABLE)&&(CCIR656_OUTPUT_ENABLE)

//#include "ahc_menu.h"
//#include "ahc_message.h"
void UartCmdPND_ModeKey( char* szParam )
{
    MMP_ULONG ulDSCCmd = 0;
    MMP_ULONG      ulNow;

    sscanfl( szParam, "%X", &ulDSCCmd);        
    printc( "PND_DSC,Cmd:0x%x \n", ulDSCCmd);

    //AHC_SendAHLMessage(AHLM_GPIO_BUTTON_NOTIFICATION, BUTTON_MODE_REL, ulDSCCmd);
    //SetKeyPadEvent(KEY_VIDEO_RECORD);
}

void UartCmdPND_SnrSel( char* szParam )
{
    MMP_ULONG ulDSCCmd = 0;
    MMP_ULONG      ulNow;

    sscanfl( szParam, "%X", &ulDSCCmd);        
    printc( "PND_SNR SEL,Cmd:0x%x \n", ulDSCCmd);

    //if(ulDSCCmd)
    //  MMPF_Display_SetCCIRActivePipeSnr(1);
    //else
    //  MMPF_Display_SetCCIRActivePipeSnr(0);
}

void UartCmdPND_RecKey( char* szParam )
{
    MMP_ULONG ulDSCCmd = 0;
    MMP_ULONG      ulNow;
    sscanfl( szParam, "%X", &ulDSCCmd);
    printc( "PND_DSC,Cmd:0x%x \n", ulDSCCmd);

    MMPF_OS_GetTime(&ulNow);
    AHC_SendAHLMessage(AHLM_GPIO_BUTTON_NOTIFICATION, BUTTON_REC_REL, ulDSCCmd);
}
#endif

void UartCmdSPI_ReadFile( char* szParam )
{
    MMP_ULONG   ulDSCCmd = 0;

    sscanfl( szParam, "%X", &ulDSCCmd);        
    printc( "SPI_ReadFile,Cmd:0x%x \n", ulDSCCmd);

    //AHC_SendAHLMessage(AHLM_GPIO_BUTTON_NOTIFICATION, KEY_REL_FUNC2, ulDSCCmd);
    //SetKeyPadEvent(BUTTON_FUNC2_PRESS);
}

static 
UARTCOMMAND sUartCommand[] =
{

    { "rr",          " HexAddr",         "read register",       UartCmdReadRegister  },
    { "wr",          " HexAddr value",   "write  register",     UartCmdWriteRegister },
    { "mm",          " BoolCmd",         "memory monitor test", UartCmdMemoryMonitor },   
    // CarDV
    { "rrb",         " HexAddr",         "read register",       UartCmdReadRegisterByte},
    { "wrb",         " HexAddr value",   "write  register",     UartCmdWriteRegisterByte},
    { "rep",         "time uartcommand", "Repeat uart command",       UartCmdRepeatCmd     },
    { "ls",          "",                 "Show command list." , UartCmdListAll       },
    { "help",        "",                 "Show command Help." , UartCmdHelp          },
    { "md",          "<HexAddr> <Size>", "Memory Dump.",        UartCmdMemoryDump    },
    { "mf",          "<HexAddr> <Size>", "Memory Fill.",        UartCmdMemoryFill    },
    { "rrs" ,         " HexAddr",        "read sensor register",       UartCmdReadSensorRegister  },
    { "rr2s" ,         " HexAddr",       "read sensor2 register",       UartCmdReadSensor2Register  },
    { "wrs",          " HexAddr value",   "write  sensor register",     UartCmdWriteSensorRegister },
    { "wrs2",          " HexAddr value",   "write  sensor2 register",     UartCmdWriteSensor2Register },
    { "rrl",          " HexAddr value",   "read LCD register",     UartCmdReadLCDRegister },
    { "wrl",          " HexAddr value",   "write LCD register",     UartCmdWriteLCDRegister },
    { "rrd",          " HexAddr",        "dump 256 registers",   UartCmdDumpRegister  },
    { "ispinfo",      "",                "get ISP Info",        UartCmdDumpISPinfo  },
#if (UVC_HOST_VIDEO_ENABLE) 
    { "sonix",      "",              "get Sonix Info",          UartCmdHostUVCReverseGearDetection  },
#endif  
#if defined(CCIR656_OUTPUT_ENABLE)&&(CCIR656_OUTPUT_ENABLE)
    { "pndmode",      "",                "PND mode",        UartCmdPND_ModeKey  },
    { "pndrec",      "",                 "PND rec",         UartCmdPND_RecKey  },
    { "pndsnr",      "",                 "PND sensor select",  UartCmdPND_SnrSel  },
#endif
    { "spirf",   "HexAddr value",   "send a jpg file via spi",  UartCmdSPI_ReadFile},
    {0,0,0,0}
};

void
UartRegisterDefaultCmds(void)
{
    UartRegisterUartCmdList(sUartCommand);
}
