/**
  @file ait_utility.c
  @brief It contains the utility functions need to be ported to the customer platform.
  @author Rogers Chen, Truman

  We should implement regular functions (MMP initialization),
  callback functions (LCD, Audio CODEC initlization) &
  retarget functions (memset, strcat... etc.)

  @version
- 2.0 Add customization functions, such as Bypass pin controller, LCD Initializer
- 1.0 Original version
 */
#ifdef BUILD_CE
#undef BUILD_FW
#endif

//==============================================================================
//
//                              INCLUDE FILE
//
//==============================================================================

#include "lib_retina.h"
#include "ait_utility.h"

//==============================================================================
//                              RETARGET FUNCTIONS
//==============================================================================
/** @brief Convert Unicode encoding string to ASCII string.
*/
char *strfromUCS(char *dest, const char *src)
{
    char *dst = dest;

    while(*src != '\0') {
        *dest = *src;
        dest++;
        src+=2;
    }
    *dest = '\0';

    return dst;
}
/** @brief Convert ASCII string to Unicode encoding string.
*/
char *strtoUCS(char *dest, const char *src)
{
    char *dst = dest;

    while(*src != '\0') {
        *dest++ = *src++;
        *dest++ = '\0';
    }
    *dest++ = '\0';
    *dest = '\0';

    return dst;
}
/** @brief Copy a Unicode encoding string.

Copies the string pointed to by src (including the terminating '\0\0')
to the array pointed to by dest. The strings may not overlap,
and the destination string dest must be large enough to receive the copy.
*/
char *uniStrcpy(char *dest, const char *src)
{
    short *s = (short *)src, *d = (short *)dest;

    while(*s != 0) {
        *d++ = *s++;
    }
    *d = 0;

    return dest;
}
/** @brief Calculate the length of a Unicode encoding string.

Calculates the length (in byte) of the Unicode encoding string src,
not including the terminating '\0' character.
*/
size_t uniStrlen(const short *src)
{
    size_t ulLen=0;

    while(*src != '\0') {
        src++;
        ulLen++;
    }

    return (ulLen << 1);
}
/** @brief Concatenate two strings

Appends the Unicode encoding src2 string to the Unicode encoding str1 string
overwriting the '\0\0' at the end of dest, and then adds a terminating '\0\0'.
The strings may not overlap, and the str1 string must have enough space for the result.
*/
char *uniStrcat(char *str1, const char *str2)
{
    short *s = (short *)str2, *d = (short *)str1;

    while(*d != 0) {
        d++;
    }
    while(*s != 0) {
        *d++ = *s++;
    }
    *d = 0;

    return str1;
}

/** @brief Convert an integer number to an ASIC string.

@param[in] value an integer to be converted.
@param[out] string the converted out string.
@retval none.
*/
void MMP_Int2Str(MMP_ULONG value, MMP_BYTE *string)
{
    MMP_ULONG   i,j;
    MMP_BYTE    temp[16];

    for (i = 0; i < 16; i++)
    {
        if ((value / 10) != 0 ) {
            temp[i] = '0' + value % 10;
            value = value / 10;
        }
        else {
            temp[i] = '0' + value % 10;
            break;
        }
    }

    for (j = 0; j < (i+1); j++) {
        string[j] = temp[i - j];
    }

    string[j] = 0;
}

void MMP_TransfomTime2Stamp(int YY, int MM, int DD, int hh, int mm, int ss, MMP_BYTE* pDate)
{
    MMP_BYTE StrYear[8], StrMonth[8], StrDay[8], StrHour[8], StrMinute[8], StrSecond[8];

    MMP_Int2Str(YY, StrYear);
    MMP_Int2Str(MM, StrMonth);
    MMP_Int2Str(DD, StrDay);
    MMP_Int2Str(hh, StrHour);
    MMP_Int2Str(mm, StrMinute);
    MMP_Int2Str(ss, StrSecond);

    MEMSET(pDate, 0, 20);

    STRCPY(pDate, StrYear);
    STRCAT(pDate, ":");

    if (MM < 10)
        STRCAT(pDate, "0");

    STRCAT(pDate, StrMonth);
    STRCAT(pDate, ":");

    if (DD < 10)
        STRCAT(pDate, "0");

    STRCAT(pDate, StrDay);

    STRCAT(pDate, " ");

    if (hh < 10)
        STRCAT(pDate, "0");

    STRCAT(pDate, StrHour);
    STRCAT(pDate, ":");

    if (mm < 10)
        STRCAT(pDate, "0");

    STRCAT(pDate, StrMinute);
    STRCAT(pDate, ":");

    if (ss < 10)
        STRCAT(pDate, "0");

    STRCAT(pDate, StrSecond);
}


#ifdef BUILD_CE
#define BUILD_FW
#endif
