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


#include "includes_fw.h"
#include "UartCmd2Navi.h"
#include "MemPool.h"

/*******************************************************************************
 *
 *   DEFINITIONS OF PRINTC
 *
*******************************************************************************/
// The max digits for a 32bit integer
#define DIGIT_STRING_LENGTH_OF_INT32     12
#define IS_A_DIGIT(x)					 ((x >='0') && (x <='9'))
#define MAX_PRINTF_OUTPUT_STRING         128
#define SUPPORT_CHAR_FILL

/*******************************************************************************
 *
 *   MARCOs
 *
*******************************************************************************/
#define IS_WHITE(x)             ( (x) == ' ' || (x) == '\t' )
#define EAT_WHITE(x)            while( IS_WHITE(*(x))) x++;
#define EAT_NON_WHITE(x)        while( !IS_WHITE(*(x))) x++;
#define IS_A_DIGIT(x)					 ((x >='0') && (x <='9'))
#define EAT_REST_STRING(x)        while( (*x) != '\0' && *(x) != '\"'  ) x++;

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


void
SendCmd2Navi( char* szFormat, ... )
{
    va_list arg_list;

	// Output buffer to UART 
	char  szOutput[MAX_PRINTF_OUTPUT_STRING];

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

    MMPF_Uart_Write(MMP_UART_ID_2, szOutput, pOutput - szOutput );

}

