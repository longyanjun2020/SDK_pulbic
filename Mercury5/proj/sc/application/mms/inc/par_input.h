
/**
 * @file
 * NCC mms parser input
 *
 * Input helper routines used in NCC mms smil data reading
 */

#ifndef __PAR_INPUT_H__
#define __PAR_INPUT_H__

#include <par_config.h>
#include <par_parse.h>

#ifdef __cplusplus
extern "C" {
#endif

#define SMIL_MAX_TAG_LENGTH                                  60 /* one tag string's length   */
#define SMIL_MAX_VALUE_LENGTH                                256
#define SMIL_MAX_NAME_LENGTH                                 256

#define SMIL_TABULATION_CHAR_SPACE                           0x20       /** */
#define SMIL_TABULATION_CHAR_LINE_BREAK                      0x0a       /**\n*/
#define SMIL_TABULATION_CHAR_ENTER                           0x0d       /**\r*/
#define SMIL_TABULATION_CHAR_TAB                             0x09       /**\t*/

#define SMIL_SPECIAL_TAG_EQUATION                            '='
#define SMIL_SPECIAL_TAG_SINGER_QUOTE                        '\''
#define SMIL_SPECIAL_TAG_DOUBLE_QUOTE                        '\"'
#define SMIL_SPECIAL_TAG_LEFT_SQUARE_BRACKET                 '<'
#define SMIL_SPECIAL_TAG_RIGHT_SQUARE_BRACKET                '>'
#define SMIL_SPECIAL_TAG_FORWARD_SLASH                       '/'
#define SMIL_SPECIAL_TAG_HYPHEN                              '-'

/**********************************************************************************************/
/*    API define   */
/**********************************************************************************************/
int32_t SmilGetChar(int8_t ** Smilbuf, int32_t * totalLen, int8_t * OneChar);   /* get one char from the smil data buffer */


/**
 * Copy some configuration of the MMS from the configuration file
 * \param  **Smilbuf       the point of the Smilbuf addres
 * \param  *Tag            the structure used to save the information of tag, in which the attribution is saved in adverse sequence.
 * \return <ul>
 *             <li> TRUE	if successful
 *             <li> FALSE	if failed
 *         </ul>
 */
int32_t SmilGetOneTag(int8_t ** Smilbuf, T_Parser_Tag_Value * Tag);

/**
 * Free the smil tag struct
 * \param pTag			point of tag structure
 * \return <ul>
 *		<li> None
 *	   </ul>
 */
void SmilClearTagStruct(T_Parser_Tag_Value * pTag);

#ifdef __cplusplus
}
#endif

#endif /* __PAR_INPUT_H__ */
