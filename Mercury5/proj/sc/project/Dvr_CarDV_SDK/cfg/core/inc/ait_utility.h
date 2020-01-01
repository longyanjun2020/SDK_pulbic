/** @file ait_utility.h

@brief Header file of the utility
@author Truman Yang
@since 10-Jul-06
@version
- 1.0 Original version
*/

#ifndef _UTILITY_H_
#define _UTILITY_H_

#include <string.h>
#include <stdlib.h>

//==============================================================================
//
//                              FUNCTION PROTOTYPES
//
//==============================================================================

char    *uniStrcpy(char *dest, const char *src);
char    *strtoUCS(char *dest, const char *src);
char    *strfromUCS(char *dest, const char *src);
size_t  uniStrlen(const short *src);
char    *uniStrcat(char *str1, const char *str2);

#endif  //_UTILITY_H_

