/**
 * @file
 * NCC mms charset Service Layer
 *
 * Service API exposed by the NCC mms charset module
 *
 * <!-- #interface list begin -->
 * \section nccmms_charset Interface
 * - NCCMms_charset_decodeString2Local()
 * - NCCMms_charset_encodeLocalString2UTF8()
 * - NCCMms_charset_freeStringBuf()
 * <!-- #interface list end -->
 */

#ifndef __NCC_MMS_CHARSET_H__
#define __NCC_MMS_CHARSET_H__

#include <ncc_types.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
   *    \name constant values of charset module
   */
/**the tag of ucs2*/
#define MMS_CHARSET_ISO_10646_UCS_2                          0x03E8
#define MMS_CHARSET_UTF16_BE    0x03f5
#define MMS_CHARSET_UTF16_LE1   0x03f6
#define MMS_CHARSET_UTF16_LE2   0x03f7
/**the tag of BIG5*/
#define MMS_CHARSET_BIG5                                     0x07EA

/**the first tag for UTF-8*/
#define MMS_CHARSET_UTF8_TAG_ONE                             0xef
/**the second tag for UTF-8*/
#define MMS_CHARSET_UTF8_TAG_TWO                             0xbb
/**the third tag for UTF-8*/
#define MMS_CHARSET_UTF8_TAG_THREE                           0xbf

/**the first TAG for UCS2:LITTLE*/
#define MMS_CHARSET_UCS2_LITTLE_TAG_ONE                      0xfe
/**the second TAG for UCS2:LITTLE*/
#define MMS_CHARSET_UCS2_LITTLE_TAG_TWO                      0xff

/**the first TAG for UCS2:BIG*/
#define MMS_CHARSET_UCS2_BIG_TAG_ONE                         0xff
/**the second TAG for UCS2:BIG*/
#define MMS_CHARSET_UCS2_BIG_TAG_TWO                         0xfe

/**
 * According to the string's charset to decode the string to gb2312.
 * the return string's address must be CharSetFree by the user.it is CharSetMalloc in the functions.
 * \param    CharSet        the type of Text string(MMS_CHARSET_UTF8;MMS_CHARSET_ASCII;MMS_CHARSET_ISO_10646_UCS_2)
 * \param    *Text        the string which we will exchange , and the buffer must be fully filled with the data , '\0' is the end of the buffer.
 * \param    *len            the length of the buffer that  *Text  point to .
 * \return    <ul>
 *                <li>when successful,return#the point of the gb2312 string
 *                <li>when fail,return#NULL
 *            </ul>
 *
 */
uint8_t *NCCMms_charset_decodeString2Local(int32_t CharSet, uint8_t * Text,
                                           int32_t * len);

/**
 * Translate local text gb2312, UCS2 ,UTF8 string into UTF-8
 * \param    *Text    the point of the string which we will translate. and if the Text is UTF8 or UCS2, the text should have the head of UTF8 or UCS2.
 * \param    *len        the length of the buffer that the "Text" point to
 * \return    <ul>
 *                <li>when successful,return#the point of the gb2312 string
 *                <li>when fail,return#NULL
 *            </ul>
 *
 */
uint8_t *NCCMms_charset_encodeLocalString2UTF8(uint8_t * Text, int32_t * len);

/**
 * Free the memory
 * \param    *pbuf        the point of the string which we will free
 * \return    void
 */
void NCCMms_charset_freeStringBuf(void *pbuf);

#ifdef __cplusplus
}
#endif

#endif /* __NCC_MMS_CHARSET_H__ */
