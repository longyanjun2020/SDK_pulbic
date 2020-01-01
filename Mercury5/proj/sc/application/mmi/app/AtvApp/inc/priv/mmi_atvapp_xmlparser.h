/**
* @file    mmi_gtvapp_xmlparser.h
* @version
* @brief   general television xmlparser header file.
*
*/
#ifndef __MMI_ATVAPP_XMLPARSER_H__
#define __MMI_ATVAPP_XMLPARSER_H__

#include "mmi_mae_common_def.h"

struct XML_ParserStruct;
typedef struct XML_ParserStruct ATV_XMLParser_t;

/**
 * Result of Wonhot_XMLParser_Parse
 */
typedef enum
{
	ATV_XMLPARSER_STATUS_ERROR = 0,			/**< Some internal error happens */
	ATV_XMLPARSER_STATUS_OK,					/**< The parse is done and OK */
	ATV_XMLPARSER_STATUS_PARTIAL_DONE,		/**< Parse fail, and it seems that you give a partial input to parser */
	ATV_XMLPARSER_STATUS_WRONG_FORMAT,		/**< Wong XML format */
	ATV_XMLPARSER_STATUS_NOT_SUPPORTED		/**< The param, isDone is false */
}ATV_XMLParser_Status_e;

/**
 * Structure for XML Tag Attributes
 */
typedef struct XML_Attribute_tag
{
	const char *pName;	/**< pointer to the name of tag */
	const char *pValue;	/**< pointer to the value of tag */
	s16 nameLen;	/**< length in byte of the name */
	s16 valueLen;	/**< length in byte of the value */
}XML_Attribute_t;

/**
 * Functino prototype of start tag handler.
 * Note that the tag name and name/value in atts are not NULL terminated string.
 */
typedef void (*XML_StartElementHandler) (void *userData,
										 const char *name,
										 s32 nLen,
										 const XML_Attribute_t *atts,
										 s16 nAttsCount);

/**
 * Functino prototype of start tag handler.
 * Note that name is not NULL terminated.
 */
typedef void (*XML_EndElementHandler) (void *userData,
									   const char *name,
									   s32 nLen);


/**
 * Functino prototype of character data handler.
 * Note that s is not NULL terminated.
 */
typedef void (*XML_CharacterDataHandler) (void *userData,
										  const char *pChar,
										  s32 nLen);

/* Returns the last value set by XML_SetUserData or NULL. */
#define ATV_XMLParser_GetUserData(parser) (*(void **)(parser))

/**
 * Constructs a new parser
 *
 * @return pointer to the parser
 *         NULL if fail to create parser
 */
ATV_XMLParser_t* ATV_XMLParser_Create(void);

/**
 * Frees memory used by the parser.
 *
 * @param p pointer to the parser
 */
void ATV_XMLParser_ParserFree(ATV_XMLParser_t *p);

/**
 * Parse the conatin. You should give a valid XML format as input.
 * No partial contain is allowed.
 *
 * @param p pointer to the parser
 * @param s pointer to the contain
 * @param nLen length of the contain (in bytes)
 * @param isFinal SHOULD be TRUE, the parser parse the contain at once and do not support parse partial input.s
 * @return enum Wonhot_XMLParser_Status
 */
ATV_XMLParser_Status_e ATV_XMLParser_Parse(ATV_XMLParser_t *p, const char *s, s32 nLen, boolean isFinal);

/**
 * Set handlers for start and end tags.
 *
 * @param p pointer to the parser
 * @param start function of start tag handler
 * @param end function of end tag handler
 * @return void
 */
void ATV_XMLParser_SetElementHandler(ATV_XMLParser_t *p, XML_StartElementHandler start, XML_EndElementHandler end);

/**
 * Set handler for text.
 * Only text between STag and ETag will be handled by this handler.
 * (This is different from the behavior of the original expat XML parser)
 * e.g. Character appear after the STag and before another STag will be ignored.
 *
 * Example:
 * <tag>meow</tag> -> Character data handler will be called to process "meow"
 * <tag>xyz<a>bow</a>dark</tag> -> "xyz", "dark" will be ignored and "bow" will be processed
 *
 * @param p pointer to the parser
 * @param handler function of character handler
 * @return void
 */
void ATV_XMLParser_SetCharacterDataHandler(ATV_XMLParser_t *p, XML_CharacterDataHandler handler);

void ATV_XMLParser_SetUserData(ATV_XMLParser_t *p, void *userData);

#endif	//__MMI_ATVAPP_XMLPARSER_H__

