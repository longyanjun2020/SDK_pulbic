/*
 * Copyright 2002,2003 Aplix Corporation. All rights reserved.
 */

/**
 * @file JcUtf8.h
 *  Character Code Conversion JBI (Unicode to UTF-8)
 *
 */

/**
 * @addtogroup Character_Code_Conversion_JBI
 * @{
 */

#ifndef ___JCUTF8_H
#define ___JCUTF8_H

#include "JkTypes.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 *   Converts a Unicode character string to a UTF-8 byte array.
 *   
 *   @param in
 *     A pointer to the memory area containing the Unicode character string.
 *   @param inChars
 *     The number of characters in the Unicode character string.
 *   @param out
 *     A pointer to the memory area for receiving the UTF-8 byte array resulting from 
 *     conversion.
 *   @param outBytes
 *     The number of bytes that can be output to the memory area designated in the 
 *     out parameter.<br>
 *     The number of characters resulting from conversion of a Unicode character 
 *     string to a UTF-8 byte array can be obtained by calling #JcUniToUtf8Size().
 *     When priority is given to speed of execution, the value designated in inChars 
 *     times 3 bytes is an estimate on the safe side and can be used here.
 *   @param outNextOff
 *     A pointer to the memory area for receiving the number of bytes converted to a 
 *     UTF-8 byte array.<br>
 *     If #JK_NULL is designated, nothing is put in the memory area.
 *   
 *   @return
 *     The number of Unicode characters converted to a UTF-8 byte array is returned.
<br>
 *     If the return value is identical to that designated in the inChars parameter, 
 *     this means the entire Unicode character string was converted.<br>
 *     If not all the Unicode character string could be processed due to lack of 
 *     output space, -1 is returned.<br>
 *     If NULL is designated for either the in or out parameters, or if a negative 
 *     value is designated for inChars or outBytes, -2 is returned indicating an 
 *     illegal parameter.<br>
 *   
 *   The processing results and the corresponding return values and values passed through parameters 
 *   in each case are as indicated below.
 *   
 *   <table border=1 cellspacing=3 cellpadding=3>
 *   <tr><td><b>Processing result</b></td>
 *       <td><b>Returns</b></td>
 *       <td><b><br>Value put in memory area designated by outNextOff</b></td></tr>
 *
 *   <tr><td>The entire Unicode character string was converted and N bytes were 
 *   output.</td>
 *       <td>Same value as inChars</td>
 *       <td>outNextOff : N  (N <= outBytes)</td></tr>
 *
 *   <tr><td>n characters of the Unicode character string were converted, but output
 *           space ran out when N bytes were output.</td>
 *       <td>-1</td>
 *       <td>outNextOff : N  (N = outBytes)</td></tr>
 *
 *   <tr><td>The Unicode character designated in the in parameter requires 2 bytes 
 *   for conversion to UTF-8, but 1 is designated in outBytes.</td>
 *     <td>-1</td>
 *     <td>outNextOff : 0</td></tr>
 *   </table>
 *   
 *   Even if the Unicode character string contains a termination character ('\0'), 
 *   the designated number of bytes are processed. '\0' is output as is.
 *   '\0' is not added at the end of the UTF-8 byte array after conversion.
 */
JKSint32 JcUniToUtf8(const JKWChar* in, JKSint32 inChars,
                     JKUint8* out, JKSint32 outBytes,
                     JKSint32* outNextOff);



/**
 *   Returns the number of bytes resulting from conversion of a Unicode character 
 *   string to a UTF-8 byte array.
 *   
 *   @param in
 *     A pointer to the memory area containing the Unicode character string.
 *   @param inChars
 *     The number of characters in the Unicode character string.
 *   
 *   @return
 *     The number of bytes resulting from conversion of a Unicode character string to 
 *     a UTF-8 byte array is returned.
 *     This byte count does not include '\0' termination.<br>
 *     If #JK_NULL is designated for the in parameter, or a negative value for 
 *     inChars, -1 is returned indicating an illegal parameter.
 *   
 */
JKSint32 JcUniToUtf8Size(const JKWChar* in, JKSint32 inChars);

/**
 *   Converts a UTF-8 byte array to a Unicode character string.
 *   
 *   @param in
 *     A pointer to the memory area containing the UTF-8 byte array.
 *   @param inBytes
 *     The number of bytes in the UTF-8 byte array.
 *   @param out
 *     A pointer to the memory area for receiving the Unicode character string 
 *     resulting from conversion.
 *   @param outChars
 *     The number of characters that can be output to the memory area designated by 
 *     the out parameter. <br>
 *     The number of characters resulting from conversion of a UTF-8 byte array to a 
 *     Unicode character string can be obtained by calling #JcUtf8ToUniSize().
 *     When priority is given to speed of execution, the value designated in inBytes 
 *     is an estimate on the safe side and can be used here.
 *   @param outNextOff
 *     A pointer to the memory area for receiving the number of characters to which the 
 *     Unicode character string was converted.<br>
 *     If #JK_NULL is designated, nothing is put in the memory area.
 *   @param badChars
 *     A pointer to the memory area for receiving the number of characters that could 
 *     not be converted.<br>
 *     This parameter is incremented each time there is a UTF-8 byte array for which 
 *     no equivalent Unicode character could be found.<br>
 *     If #JK_NULL is designated, nothing is put in the memory area.
 *   @param substitute
 *     A substitute character.<br>
 *     Designate a substitute Unicode character to be used in case a UTF-8 byte array 
 *     has no equivalent Unicode character.<br>
 *     If 0 is designated, 0xFFFD is used.
 *   
 *   @return
 *     The number of UTF-8 bytes converted to a Unicode character string is 
 *     returned.<br>
 *     If the return value is identical to that designated in the inBytes parameter, 
 *     this means the entire UTF-8 byte array was converted.<br>
 *     If not all the UTF-8 byte array could be processed due to lack of output 
 *     space, -1 is returned.<br>
 *     If NULL is designated for either the in or out parameters, or if a negative 
 *     value is designated for inBytes or outChars, -2 is returned indicating an 
 *     illegal parameter.<br>
 *   
 *   The processing results and the corresponding return values and values passed through parameters 
 *   in each case are as indicated below.
 *   
 *   <table border=1 cellspacing=3 cellpadding=3>
 *   <tr><td><b>Processing result</b></td>
 *       <td><b>Returns</b></td>
 *       <td><b><br>Value put in memory area indicated by outNextOff</b></td></tr>
 *
 *   <tr><td>The entire UTF-8 byte array was converted and N characters were 
 *   output.</td>
 *       <td>Same value as inBytes</td>
 *       <td>outNextOff : N  (N <= outChars)</td></tr>
 *
 *   <tr><td>n bytes of the UTF-8 byte array were converted, but output space
 *           ran out when N characters were output.</td>
 *       <td>-1</td>
 *       <td>outNextOff : N  (N = outChars)</td></tr>
 *   </table>
 *   
 *   Even if the UTF-8 byte array contains a termination character ('\0'),  
 *   the designated number of bytes are processed. '\0' is output as is.
 *   If the UTF-8 byte array contains UCS4 character codes of 0x10000 and above,
 *   these characters are not converted but are replaced by the alternate character 
 *   designated in the substitute parameter and counted in the characters that could 
 *   not be converted.<br>
 *   UTF-8 converted to an illegal byte length is considered an illegal code under 
 *   RFC2279, but conversion proceeds in this function nonetheless.
 *   Example:: U+0000 in UTF-8 is the 1 byte 0x00, but conversion processing takes 
 *   place even it is encoded as 2 or 3 bytes (0xC0 0x80 or 0xE0 0x80 0x80).
 *   
 *
 */
JKSint32 JcUtf8ToUni(const JKUint8* in, JKSint32 inBytes,
                     JKWChar* out, JKSint32 outChars,
                     JKSint32* outNextOff, /*JKUint32* saveState,*/
                     JKSint32* badChars, JKWChar substitute);



/**
 *   Returns the number of characters resulting from conversion of a UTF-8 byte array 
 *   to a Unicode character string.
 *   
 *   @param in
 *     A pointer to the memory area containing the UTF-8 byte array.
 *   @param inBytes
 *     The number of bytes in the UTF-8 byte array.
 *   
 *   @return
 *     The number of characters resulting from conversion of a UTF-8 byte array to a 
 *     Unicode character string is returned. 
 *     This character count does not include the '\0' terminating the converted Unicode 
 *     character string.
 *     If #JK_NULL is designated for the in parameter, or if a negative value is 
 *     designated for inBytes, -1 is returned indicating an illegal parameter.
 *   
 *   If conversion is interrupted while processing a multi-byte character, that 
 *   character is not included in the count.
 */
JKSint32 JcUtf8ToUniSize(const JKUint8* in, JKSint32 inBytes);

/**
 *   Determines from the 1st byte of UTF-8 how many bytes make up that character.
 *  
 *   @param c
 *     The 1st byte of UTF-8.
 *   
 *   @return
 *     The number of bytes making up the character is returned.
 */
#define JcUtf8ToUniCharSize(c) \
((((c)&0xC0)==0xC0)?(((c)&0x20)?(((c)&0x10)?(((c)&8)?(((c)&4)?(((c)&2)?6:1):5):4):3):2):1)

/**
 *   Determines from the 1st byte of UTF-8 how many bytes make up that character.
 *  
 *   @param c
 *     The 1st byte of UTF-8.
 *   
 *   @return
 *     The number of bytes making up the character is returned.
 */
#define JcUtf8ToUniCharSize(c) \
((((c)&0xC0)==0xC0)?(((c)&0x20)?(((c)&0x10)?(((c)&8)?(((c)&4)?(((c)&2)?6:1):5):4):3):2):1)

#ifdef __cplusplus
}
#endif

#endif /* ___JCUTF8_H */

/** @} end of group */
