
#ifndef __PROV_XML_H__
#define __PROV_XML_H__
#ifndef UAPP_PUSH_PROV
//#error "PROV had been disabled"
#endif /* UAPP_PUSH_PROV */

#include <ncc_types.h>

/************************************************************************/
/*     Enable or disable the features                                   */
/************************************************************************/
#define AVT_XML_PARSER
#define AVT_XML_SAX_PARSER
#define AVT_WBXML_PARSER
#define AVT_WBXML_SAX_PARSER
#define XML_TREE_STRUTURE
#ifdef NCC_DEBUG_ON
#define XML_DEBUG_MODE
#endif
#define XML_ENABLE_ERRNO

/************************************************************************/
/* Global var & define                                                  */
/************************************************************************/

#define XML_EOF         -1

#define XML_OK      0
#define XML_ERROR   -1

#define XML_TRUE        1
#define XML_FALSE       0

#define XML_MAX_PROPERTY_LEN    256
#define XML_MAX_ATTR_NAME_LEN   256
#define XML_MAX_ATTR_VALUE_LEN  256
#define XML_MAX_VALUE_LEN       256

typedef int32_t XML_BOOL;

#ifdef XML_ENABLE_ERRNO
extern int32_t xml_errno;  //weelee add extern 
#endif

#ifdef XML_TREE_STRUTURE
typedef struct _XML_TREE_ATTR XML_TREE_ATTR;
struct _XML_TREE_ATTR
{
  int8_t name[XML_MAX_ATTR_VALUE_LEN];
  int8_t value[XML_MAX_ATTR_VALUE_LEN];
  XML_TREE_ATTR *next;
};

typedef struct _XML_TREE XML_TREE;
struct _XML_TREE
{
  int8_t tag[XML_MAX_PROPERTY_LEN];
  int8_t value[XML_MAX_VALUE_LEN];
  XML_TREE_ATTR *attr;
  XML_TREE_ATTR *last_attr;
  XML_TREE *sibling;
  XML_TREE *last_sibling;
  XML_TREE *child;
  XML_TREE *parent;
};

void XML_freeTree (XML_TREE * pTree);
#endif

/************************************************************************/
/* AVT_WBXML_PARSER                                                     */
/************************************************************************/
#ifdef AVT_WBXML_PARSER
#define WBXML_WITH_ATTR     0x80
#define WBXML_WITH_CONTENT  0x40
#define WBXML_END_TAG       0x01

#define WBXML_SWITCH_PAGE   0x00
#define WBXML_STR_I         0x03
#define WBXML_END           0x00
#define WBXML_OPAUE         0xC3
#define WBXML_STR_T         0x83
#define WBXML_OPAQUE        0xC3

#define WBXML_GET_TAG(x)        ((uint8_t)((x) & 0x3F))  /* get 6-digits */
#define WBXML_HAS_ATTR(x)       ((x) & WBXML_WITH_ATTR)
#define WBXML_HAS_CONTENT(x)    ((x) & WBXML_WITH_CONTENT)

typedef XML_BOOL WBXML_GetTagHandler (int32_t codePage, int8_t tagChar,
                      int8_t *name);

typedef XML_BOOL WBXML_GetAttrHandler (int codePage, int8_t tagChar,
                       int8_t attrChar, int8_t *name,
                       int8_t *value);

typedef struct _WBXML
{
  uint8_t version;
  uint32_t publicid;
  uint32_t charset;
  int32_t strTableLen;
  uint8_t *strTable;
  uint8_t *Content;
  uint8_t *End;
  uint8_t *curPtr;
  uint32_t depth;
  int32_t codePage;
  WBXML_GetTagHandler *getTag;
  WBXML_GetAttrHandler *getAttr;
} WBXML;

XML_BOOL WBXML_Init (WBXML * pWbxml, int8_t *buffer, int32_t bufferLen,
             WBXML_GetTagHandler * getTag,
             WBXML_GetAttrHandler * getAttr);
XML_BOOL WBXML_Eof (WBXML * pWbxml);
int32_t WBXML_GetTag (WBXML * pWbxml);
int32_t WBXML_GetChar (WBXML * pWbxml);
int32_t WBXML_ReadChar (WBXML * pWbxml);
int32_t WBXML_GetUIntVar (WBXML * pWbxml);
XML_BOOL WBXML_Rewind (WBXML * pWbxml);
XML_BOOL WBXML_Seek (WBXML * pWbxml, int32_t offset);
int32_t WBXML_GetUintVar (const int8_t *const buffer, int32_t *len);

#ifdef XML_TREE_STRUTURE
XML_TREE *WBXML_makeTree (WBXML * pWbxml);
#endif

#endif

/************************************************************************/
/* AVT_XML_PARSER                                                       */
/************************************************************************/
#ifdef AVT_XML_PARSER
#define XML_TAG_START       0
#define XML_TAG_END     1
#define XML_TAG_SELF        2

#define XML_ERROR_OK                0
#define XML_ERROR_BUFFER_NULL           -1
#define XML_ERROR_ATTR_NAME         -2
#define XML_ERROR_ATTR_MISSED_EQUAL     -3
#define XML_ERROR_PROPERTY_NAME         -4
#define XML_ERROR_ATTR_VALUE            -5
#define XML_ERROR_ENDTAG            -6
#define XML_ERROR_NO_SUCH_NODE          -7
#define XML_ERROR_PROPERTY_END          -8
#define XML_ERROR_VALUE             -9
#define XML_ERROR_NO_START_TAG          -14
#define XML_ERROR_NOVALUE           -15

#ifdef XML_TREE_STRUTURE
XML_TREE *XML_makeTree (int8_t *buf);
#endif

#endif

/************************************************************************/
/* XML_SAX_COMMAN                                                       */
/************************************************************************/
#if defined(AVT_XML_SAX_PARSER) || defined(AVT_WBXML_SAX_PARSER)
typedef XML_BOOL XML_StartElementHandler (int8_t *name);
typedef XML_BOOL XML_AttrHandler (int8_t *name, int8_t *value);
typedef XML_BOOL XML_EndElementHandler (int8_t *name);
typedef XML_BOOL XML_ElementValueHandler (int8_t *value);
#endif

/************************************************************************/
/* AVT_XML_SAX_PARSER                                                   */
/************************************************************************/
#ifdef AVT_XML_SAX_PARSER
XML_BOOL XML_SAX_Parser (int8_t *buffer, XML_StartElementHandler * func_start,
             XML_EndElementHandler * func_end,
             XML_AttrHandler * func_attr,
             XML_ElementValueHandler * func_value);
#endif

/************************************************************************/
/* AVT_WBXML_SAX_PARSER                                                 */
/************************************************************************/
#ifdef AVT_WBXML_SAX_PARSER
XML_BOOL WBXML_SAX_Parser (int8_t *buffer, int32_t bufferLen,
               WBXML_GetTagHandler * getTag,
               WBXML_GetAttrHandler * getAttr,
               XML_StartElementHandler * func_start,
               XML_EndElementHandler * func_end,
               XML_AttrHandler * func_attr,
               XML_ElementValueHandler * func_value);
#endif
/************************************************************************/
/* XML_DEBUG_MODE                                                       */
/************************************************************************/
#ifdef XML_DEBUG_MODE
void XML_DEBUG_mallocInfo (void);
#endif

#endif /* __PROV_XML_H__ */
