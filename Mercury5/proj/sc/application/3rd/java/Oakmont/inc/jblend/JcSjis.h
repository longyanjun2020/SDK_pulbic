/*
 * Copyright 2000-2002 Aplix Corporation. All rights reserved.
 */

/**
 * @file JcSjis.h
 *  Character Code Conversion JBI (Unicode to SJIS)
 *
 */

/**
 * @addtogroup Character_Code_Conversion_JBI
 * @{
 */

#ifndef ___JCSJIS_H
#define ___JCSJIS_H

#include "JkTypes.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 *   Converts a Shift JIS character to Unicode.
 *   
 *   @param sj
 *     The Shift JIS character.<br>
 *     When a 2-byte character is designated, put the 1st byte in the high 8 bits 
 *     and the 2nd byte in the low 8 bits.
 *   
 *   @return
 *     The Unicode character corresponding to the Shift JIS character is returned.
 *     If there is no equivalent Unicode character, 0xFFFD is returned.
 */
JKWChar JcSjisToUniChar(unsigned short sj);



/**
 *   Converts a Shift JIS byte array to a Unicode character string.
 *   
 *   @param in
 *     A pointer to the memory area containing the Shift JIS byte array.
 *   @param inBytes
 *     The byte size of the Shift JIS byte array.
 *   @param out
 *     A pointer to the memory area for receiving the Unicode character string 
 *     resulting from conversion.
 *   @param outChars
 *     The number of characters that can be output to the memory area designated by the out 
 *     parameter.<br>
 *     The number of characters resulting from conversion of a Shift JIS byte array 
 *     to a Unicode character string can be obtained by calling #JcSjisToUniSize().
 *     When priority is given to speed of execution, the value designated in the 
 *     inBytes parameter is an estimate on the safe side and can be used here.
 *   @param outNextOff
 *     A pointer to the memory area for receiving the number of characters converted 
 *     to a Unicode character string.<br>
 *     If #JK_NULL is designated, nothing is put in the memory area.
 *   @param saveState
 *     A pointer to a memory area for receiving information for use the next time 
 *     conversion is performed.<br>
 *     If conversion was interrupted while processing a 2-byte character, the 1st 
 *     byte is stored.
 *     For the first time conversion is performed, clear this memory area to 0.
 *     If conversion is performed consecutively, for the second and subsequent times 
 *     designate the same pointer as the previous time. <br>
 *     If #JK_NULL is designated, nothing is put in the memory area.<br>
 *     #JK_NULL may be designated in the cases indicated below.<br>
 *     <ul>
 *      <li>When conversion ends with just a single time.
 *      <li>When the completion of 2-byte character conversion can be guaranteed.
 *      <li>When failure to complete 2-byte character conversion can be ignored.
 *          (The non-completed character will not be converted.)
 *     </ul>
 *   @param badChars
 *     A pointer to the memory area for receiving the number of characters that could 
 *     not be converted.<br>
 *     This parameter is incremented each time there is a Shift JIS character for 
 *     which no equivalent Unicode character was found.<br>
 *     If #JK_NULL is designated, nothing is put in the memory area.
 *   @param substitute
 *     A substitute character.<br>
 *     Designate a substitute Unicode character to be used in case a Shift JIS 
 *     character has no equivalent Unicode character.<br>
 *     If 0 is designated, 0xFFFD is used.
 *   
 *   @return
 *     The size (in bytes) of the Shift JIS byte array converted to a Unicode 
 *     character string is returned.<br>
 *     If the return value is identical to that designated in the inBytes parameter, 
 *     this means the entire Shift JIS byte array was converted.<br>
 *     If not all the Shift JIS byte array could be processed due to lack of output 
 *     space, -1 is returned.<br>
 *     If NULL is designated for either the in or out parameters, or if a negative 
 *     value is designated for inBytes or outChars, -2 is returned indicating an 
 *     illegal parameter.
 *   
 *   The processing results and the corresponding return values and values passed through parameters 
 *   in each case are as indicated below.
 *   
 *   <table border=1 cellspacing=3 cellpadding=3>
 *   <tr><td><b>Processing result</b></td>
 *       <td><b>Returns</b></td>
 *       <td><b><br>Values put in memory areas designated by outNextOff and 
 *       saveState</b></td></tr>
 *
 *   <tr><td>The entire Shift JIS byte array was converted and N characters were 
 *   output.</td>
 *       <td>Same value as inBytes</td>
 *       <td>outNextOff : N  (N <= outChars)<br>
 *           saveState : 0</td></tr>
 *
 *   <tr><td>The entire Shift JIS byte array was converted and N characters<br>
 *           were output, but conversion of a Shift JIS 2-byte character ended <br> 
 *           with the 1st byte.</td>
 *       <td>Same value as inBytes</td>
 *       <td>outNextOff : N  (N <= outChars)<br>
 *           saveState : 1st byte of Shift JIS 2-byte character</td></tr>
 *
 *   <tr><td>n bytes of the Shift JIS byte array were converted, but output space
 *           ran out when N characters were output.</td>
 *       <td>-1</td>
 *       <td>outNextOff : N  (N = outChars)<br>
 *           saveState : 0</td></tr>
 *   </table>
 *   
 *   Even if the Shift JIS byte array contains a termination character ('\0'), only 
 *   the designated number of bytes are processed. '\0' is output as is.
 *   '\0' is not added at the end of the Unicode character string after conversion.
 */
JKSint32 JcSjisToUni(const JKUint8* in, JKSint32 inBytes,
                     JKWChar* out, JKSint32 outChars,
                     JKSint32* outNextOff, JKUint8* saveState,
                     JKSint32* badChars, JKWChar substitute);



/**
 *   Returns the number of characters resulting from conversion of a Shift JIS byte array
 *   to a Unicode character string.
 *   
 *   @param in
 *     A pointer to the memory area containing the Shift JIS byte array.
 *   @param inBytes
 *     The number of bytes in the Shift JIS byte array.
 *   
 *   @return
 *     The number of characters resulting from conversion of a Shift JIS byte array 
 *     to a Unicode character string is returned.
 *     This character count does not include the '\0' terminating the converted Unicode 
 *     character string.
 *     If #JK_NULL was designated for the in parameter, or if a negative value was
 *     designated for inBytes, -1 is returned to indicate an illegal parameter.
 *   
 *   If conversion of a 2-byte character was interrupted, the 1st byte is not 
 *   included in the character count.
 */
JKSint32 JcSjisToUniSize(const JKUint8* in, JKSint32 inBytes);



/**
 *   Converts a Unicode character to a Shift JIS character.
 *   
 *   @param uc
 *     The Unicode character
 *   
 *   @return
 *     The Shift JIS character equivalent to the Unicode character is returned.
 *     If conversion was to a 1-byte Shift JIS character, a value less than 0x100 is 
 *     returned.
 *     If conversion was to a 2-byte Shift JIS character, the 1st byte is returned in 
 *     the high 8 bits and the 2nd byte in the low 8 bits.
 *     If there is no equivalent Shift JIS character, 0xFFFD is returned.
 */
unsigned short JcUniToSjisChar(JKWChar uc);



/**
 *   Converts a Unicode character string to a Shift JIS byte array.
 *   
 *   @param in
 *     A pointer to the memory area containing the Unicode character string.
 *   @param inChars
 *     The number of characters in the Unicode character string.
 *   @param out
 *     A pointer to the memory area for receiving the Shift JIS byte array resulting 
 *     from conversion.
 *   @param outBytes
 *     The number of bytes that can be output to the area designated by the out 
 *     parameter.<br>
 *     The number of bytes resulting from conversion of a Unicode character string to 
 *     a Shift JIS byte array can be obtained by calling #JcUniToSjisSize().
 *     When priority is given to speed of execution, the value designated in inChars 
 *     times 2 bytes is an estimate on the safe side and can be used here.
 *   @param outNextOff
 *     A pointer to the memory area for receiving the number of bytes converted to a 
 *     Shift JIS byte array.<br>
 *     If #JK_NULL is designated, nothing is put in the memory area.
 *   @param badChars
 *     A pointer to the memory area for receiving the number of characters that could 
 *     not be converted.<br>
 *     This parameter is incremented each time there is a Unicode character for which 
 *     no equivalent Shift JIS character was found.<br>
 *     If #JK_NULL is designated, nothing is put in the memory area.
 *   @param substitute
 *     A substitute character.<br>
 *     Designate a substitute Shift JIS character to be used in case a Unicode 
 *     character has no  equivalent Shift JIS character.<br>
 *     If 0 is designated, '?' is used.
 *     
 *   @return
 *     The number of Unicode characters converted to a Shift JIS byte array is 
 *     returned.<br>
 *     If the return value is identical to that designated in the inChars parameter, 
 *     this means the entire Unicode character string was converted.<br>
 *     If not all the Unicode character string could be processed due to lack of 
 *     output space, -1 is returned.<br>
 *     If NULL is designated for either the in or out parameters, or if a negative 
 *     value is designated for inChar or outBytes, -2 is returned indicating an 
 *     illegal parameter.
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
 *   for conversion to Shift JIS, but 1 is designated in outBytes. </td>
 *       <td>-1</td>
 *       <td>outNextOff : 0</td></tr>
 *   </table>
 *     
 *   Even if the Unicode character string contains a termination character ('\0'), 
 *   the designated number of bytes are processed. '\0' is output as is.
 *   '\0' is not added at the end of the Shift JIS character string after conversion.
 */
JKSint32 JcUniToSjis(const JKWChar* in, JKSint32 inChars,
                     JKUint8* out, JKSint32 outBytes,
                     JKSint32* outNextOff,
                     JKSint32* badChars, unsigned short substitute);



/**
 *   Returns the number of bytes resulting from conversion of a Unicode character 
 *   string to a Shift JIS byte array.
 *   
 *   @param in
 *     A pointer to the memory area containing the Unicode character string.
 *   @param inChars
 *     The number of characters in the Unicode character string.
 *   @param substitute
 *     A substitute character.
 *     Designate a substitute Shift JIS character to be used in case a Unicode 
 *     character has no equivalent Shift JIS character.<br>
 *     If 0 is designated, '?' is used.<br>
 *     This is used to find out the number of bytes of characters that were 
 *     substituted for undefined characters.
 *   
 *   @return
 *     The number of bytes resulting from conversion of a Unicode character string to 
 *     a Shift JIS byte array is returned.
 *     This byte count does not include '\0' termination.<br>
 *     If #JK_NULL is designated for the in parameter, or if a negative value is 
 *     designated for inChars, -1 is returned indicating an illegal parameter.
 *   
 */
JKSint32 JcUniToSjisSize(const JKWChar* in, JKSint32 inChars, unsigned short substitute);

#ifdef __cplusplus
}
#endif

#endif

/** @} end of group */
