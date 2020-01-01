
/**
 * html_parserinternals.h : internals routines exported by the parser.
 */

#ifndef __HTML_PARSERINTERNALS_H__
#define __HTML_PARSERINTERNALS_H__

#include <ncc_types.h>
#include <html_parsererror.h>
#include <html_parser.h>

#ifdef __cplusplus
extern "C" {
#endif

#define ASCII_ALPHA            0x01
#define ASCII_DIGIT            0x02
#define BLANK                  0x04
#define CHAR_CH                0x08

extern const int8_t _charTypeDef[];

/**
 * IS_CHAR_CH:
 * @c: an uint8_t (usually an uint8_t)
 *
 * Behaves like IS_CHAR on single-byte value
 */
#define IS_CHAR_CH(x)        (_charTypeDef[x] & CHAR_CH)

/**
 * IS_ASCII_ALPHA:
 * @c: an uint8_t value
 *
 * Macro to check [a-zA-Z]
 *
 */
#define IS_ASCII_ALPHA(x)    (_charTypeDef[x] & ASCII_ALPHA)

/**
 * IS_ASCII_DIGIT:
 * @c: an uint8_t value
 *
 * Macro to check [0-9]
 *
 */
#define IS_ASCII_DIGIT(x)    (_charTypeDef[x] & ASCII_DIGIT)

/**
 * XML_MAX_NAMELEN:
 *
 * Identifiers can be longer, but this will be more costly
 * at runtime.
 */
#define HTML_MAX_NAMELEN 128
#define HTML_MAX_NAME_NUMBER   64

/**
 * the max length of predefined entity's name
 * if it exceed 0x0F, we don't consider it as a predefined entity
 */
#define HTML_REFERENCE_MAX_LEN   0x0D

/**
 * INPUT_CHUNK:
 *
 * The parser tries to always have that amount of input ready
 * one of the point is providing context when reporting errors
 */
#define INPUT_CHUNK    250

/**
 *
 * UNICODE version of the macros.
 *
 */

/**
 * IS_CHAR:
 * @c:  an UNICODE value (int32_t)
 *
 * Macro to check the following production in the XML spec
 *
 * [2] Char ::= #x9 | #xA | #xD | [#x20-#xD7FF] | [#xE000-#xFFFD]
 *                  | [#x10000-#x10FFFF]
 * any Unicode character, excluding the surrogate blocks, FFFE, and FFFF.
 */
#define IS_CHAR(c)        ( ((c) < 0x100) ?                                \
                          IS_CHAR_CH(c) :                                  \
                          ( ((0x100 <= (c)) && ((c) <= 0xd7ff) ) ||        \
                          ( (0xe000 <= (c)) && ((c) <= 0xfffd) ) ||        \
                          ( (0x10000 <= (c)) && ((c) <= 0x10ffff)) ) )

/**
 * IS_BLANK:
 * @c:  an UNICODE value (c must be less than 0x100)
 *
 * Macro to check the following production in the XML spec
 *
 * [3] S ::= (#x20 | #x9 | #xD | #xA)+
 */
#define IS_BLANK(c)            (_charTypeDef[c] & BLANK)

void
htmlMemoryErr(htmlParserCtxtPtr ctxt, const char *extra);

void
htmlParseErr( htmlParserCtxtPtr ctxt,
              xmlParserErrors error,
              const char *msg,
              const uint8_t *str1,
              const uint8_t *str2 );

htmlParserInputPtr
htmlNewInputStream(htmlParserCtxtPtr ctxt);

void
xmlParserInputShrink(htmlParserCtxtPtr ctxt);

void
xmlFreeInputStream(htmlParserCtxtPtr ctxt, htmlParserInputPtr input);

int32_t
inputPush(htmlParserCtxtPtr ctxt, htmlParserInputPtr value);

htmlParserInputPtr
inputPop(htmlParserCtxtPtr ctxt);

uint8_t *
namePop(htmlParserCtxtPtr ctxt);

int32_t
namePush(htmlParserCtxtPtr ctxt, uint8_t *value);

#ifdef __cplusplus
}
#endif

#endif /* __HTML_PARSERINTERNALS_H__ */
