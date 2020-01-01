
/**
 * html_parser.h : inf=terface for an HTML 4.0 non-verifying parser
 */

#ifndef __HTML_PARSER_H__
#define __HTML_PARSER_H__

#include <html_parserbuffer.h>
#include <html_parserio.h>
#include <html_parsersaxhandlers.h>
#include <html_parsermemory.h>
#include <ncc_types.h>
#include <nccport_i18n.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Default character encoding for html document.
 */
#define HTML_PARSER_DEFAULT_ENCODING  NCC_CHARSET_LATIN1

/**
 * used to debug html parser
 */
#define HTML_PARSER_DEBUG  0

/**
 * Debug output file path for html parser.
 */
#define HTML_PARSER_DEBUG_FILE_PATH  "gen/uapp_wap_browser/targetfs/htmlParser/debug.html"

/**
 * used to debug html parser by trace its trip
 */
#define HTML_PARSER_TRACE  0

#define DEBUG_INPUT        0


/**
 * according to OMA Standard.
 * when parse "&#x000C", because 0x0c is not a valid value.
 * we should just skip them.
 * but when parse "&cat;", we should render "&cat;"
 */
#define NOT_RENDER_INVALID_CHAR_REF    0

#define T_HTML_CHARSET_UTF8            0x01
#define T_HTML_CHARSET_UTF16           0x02


#if HTML_PARSER_DEBUG
void *
html_debug_malloc(int32_t size);

void *
html_debug_realloc(void *ptr, int32_t size);

void
html_debug_free(void *ptr);
#endif /* HTML_PARSER_DEBUG */

/**
 * as less code as possible
 * such as PI, Comment, doctypedecl
 */
#define HTML_MINI_CORE     1

/**
 * Enable PI SAX Handler
 */
#define HTML_PI_ENABLED    1

#define STRING_POOL_ENABLE 1
#define NAME_POOL_ENABLE   1

#if STRING_POOL_ENABLE
#include <html_parserstringpool.h>
#endif

/** memory management functions defination */

#if HTML_PARSER_DEBUG

#define MALLOC(size)   html_debug_malloc(size)
#define FREE(ptr)     html_debug_free(ptr)
#define REALLOC(ptr, size)   html_debug_realloc(ptr, size)

#else

#define MALLOC(size)   ((htmlParserCtxtPtr)ctxt)->malloc_fcn(size)
#define FREE(ptr)   ((htmlParserCtxtPtr)ctxt)->free_fcn(ptr)
#define REALLOC(ptr, size)   ((htmlParserCtxtPtr)ctxt)->realloc_fcn(ptr, size)

#endif /* HTML_PARSER_DEBUG */

typedef enum _html_parsing_
{
    T_HTML_INITIALIZED = -1, /**<parser has been initialized*/
    T_HTML_PARSING = -2, /**<parser is on parsing*/
    T_HTML_FINISHED = -3, /**<parser has finished parsing*/
    T_HTML_SUSPENDED = -4 /**<parser has been suspended*/
} T_HTML_Parsing;

typedef struct _html_parsing_status_
{
  T_HTML_Parsing parsing;
  int16_t isFinalBuffer;
  int16_t hasSavedBuffer;
} T_HTML_ParsingStatus;

typedef  void*     htmlDocPtr;

/**
 * xmlParserInput:
 *
 * an htmlParserInput is an input flow for the XML processor.
 * Each entity parsed is associated an htmlParserInput (except the
 * few predefined ones). This is the case both for internal entities
 * - in which case the flow is already completely in memory - or
 * external entities - in which case we use the buf structure for
 * progressive reading and I18N conversions to the internal UTF-8 format.
 */
typedef void (*xmlParserInputDeallocate)(uint8_t *);

typedef struct _htmlParserInput htmlParserInput;
typedef htmlParserInput *htmlParserInputPtr;
struct _htmlParserInput {
    /** Input buffer */
    xmlParserInputBufferPtr buf;   /**< UTF-8 encoded buffer */

    const int8_t *filename;      /**< The file analyzed, if any */
    const int8_t *directory;     /**< the directory/base of the file */
    const uint8_t *base;         /**< Base of the array to parse */
    const uint8_t *cur;          /**< Current int8_t being parsed */
    const uint8_t *end;          /**< end of the array to parse */
    int32_t length;                /**< length if known */
    int32_t line;                  /**< Current line */
    int32_t col;                   /**< Current column */
    int32_t consumed;              /**< How many xmlChars already consumed */
    xmlParserInputDeallocate free; /**< function to deallocate the base */
    const uint8_t *encoding;     /**< the encoding string for entity */
    const uint8_t *version;      /**< the version string for entity */
    int32_t standalone;            /**< Was that entity marked standalone */
};

/**
 * xmlParserInputState:
 *
 * The parser is now working also as a state based parser
 * The recursive one use the stage info for entities processing
 */
typedef enum {
    XML_PARSER_EOF = -1,        /**< nothing is to be parsed */
    XML_PARSER_START = 0,       /**< nothing has been parsed */
    XML_PARSER_MISC,            /**< Misc* before intsubset */
    XML_PARSER_PI,              /**< within a processing instruction */
    XML_PARSER_DTD,             /**< within some DTD content */
    XML_PARSER_PROLOG,          /**< Misc* after internal subset */
    XML_PARSER_COMMENT,         /**< within a comment */
    XML_PARSER_ABBR_COMMENT,    /**< within a comment */
    XML_PARSER_START_TAG,       /**< within a start tag */
    XML_PARSER_CONTENT,         /**< within the content */
    XML_PARSER_CDATA_SECTION,   /**< within a CDATA section */
    XML_PARSER_END_TAG,         /**< within a closing tag */
    XML_PARSER_ENTITY_DECL,     /**< within an entity declaration */
    XML_PARSER_ENTITY_VALUE,    /**< within an entity value in a decl */
    XML_PARSER_ATTRIBUTE_VALUE, /**< within an attribute value */
    XML_PARSER_SYSTEM_LITERAL,  /**< within a SYSTEM value */
    XML_PARSER_EPILOG,          /**< the Misc* after the last end tag */
    XML_PARSER_IGNORE           /**< within an IGNORED section */
} xmlParserInputState;

typedef struct html_parser_startclose_hash_node {
    const int8_t **ppStartClose;
    struct html_parser_startclose_hash_node *next;
} T_HTML_PARSER_START_CLOSE_HASH_NODE;

/**
 * xmlParserCtxt:
 *
 * The parser context.
 * NOTE This doesn't completely defines the parser state, the (current ?)
 *      design of the parser uses recursive function calls since this allow
 *      and easy mapping from the production rules of the specification
 *      to the actual code. The drawback is that the actual function call
 *      also reflect the parser state. However most of the parsing routines
 *      takes as the only argument the parser context pointer, so migrating
 *      to a state based parser for progressive parsing shouldn't be too hard.
 */
typedef struct _htmlParserCtxt htmlParserCtxt;
typedef htmlParserCtxt *htmlParserCtxtPtr;
struct _htmlParserCtxt
{
    htmlSAXHandler       *sax;             /**< The SAX handler */
    int32_t              disableSAX;       /**< SAX callbacks are disabled */
    int32_t              restartFlag;      /**< the flag whether the parser should restart parsing */
    int32_t              hasStarted;       /**< startDocument have been called*/
    void                 *userData;        /**< For SAX interface only, used by DOM build */

    uint8_t              *savedBuffer;     /**<used to save unparsed data and parse it later*/
    int32_t              savedBufferSize;  /**<length of saved buffer*/

    /** Input stream stack */
    htmlParserInputPtr   input;         /**< Current input stream */
    int32_t              inputNr;       /**< Number of current input streams */
    int32_t              inputMax;      /**< Max number of input streams */
    htmlParserInputPtr   *inputTab;     /**< stack of inputs */

    T_HTML_ParsingStatus parsingStatus; /**<parsing status*/
    xmlParserInputState  instate;       /**< current type of input */
    xmlParserInputState  nextState;     /**< next type of input */
    int32_t              token;         /**< next int8_t look-ahead */

    int32_t              wellFormed;   /**< is the document well formed */
    int32_t              errNo;        /**< error code */

    /** Node name stack */
    uint8_t            *name;          /**< Current parsed Node */
    int32_t            nameNr;         /**< Depth of the parsing stack */
    int32_t            nameMax;        /**< Max depth of the parsing stack */
    uint8_t            **nameTab;      /**< array of nodes */

    int32_t            consumed;       /**< number of bytes have consumed */
    int32_t            nbChars;        /**< number of bytes processed */
    int32_t            checkIndex;     /**< used by progressive parsing lookup */
    int32_t            isInSingleQuot; /**< mainly used for lookup '>' of start tag */
    int32_t            isInDoubleQuot; /**< mainly used for lookup '>' of start tag */

    /** html parser memory handlers */
    htmlParserMalloc   malloc_fcn;
    htmlParserFree     free_fcn;
    htmlParserRealloc  realloc_fcn;

    /** html parser string pools */
    STRING_POOL        tempPool;
    T_Common_FixedSizeUnitsPool namePool;

    T_HTML_PARSER_START_CLOSE_HASH_NODE *startCloseHashTable;
    int32_t            startCloseHashTableSize;

    uint8_t            *docEncoding; /**<confirmed document encoding*/
    uint8_t            *defEncoding; /**<native encoding*/
    uint8_t            *guessEncoding; /**<guessed encoding by the starting bytes*/
};

/**
 * uint8_t handling
 */
uint8_t *
htmlNameDup(htmlParserCtxt *ctxt, const uint8_t *cur, int32_t len);

#define htmlNameFree(name)  freeFixedSizeUnit(&(ctxt->namePool), name)

void
htmlnamePopAndFree(htmlParserCtxtPtr ctxt);

void
htmlParserDestroyStartCloseHashTable(htmlParserCtxtPtr ctxt);

const uint8_t *
xmlStrcasestr(const uint8_t *str, uint8_t *val);

int32_t
xmlStrlen(const uint8_t *str);

/**
 * Internal description of an HTML element
 */
typedef struct _htmlElemDesc htmlElemDesc;
typedef htmlElemDesc *htmlElemDescPtr;
struct _htmlElemDesc {
    const char *name; /**< The tag name */
    int8_t startTag;      /**< Whether the start tag can be implied */
    int8_t endTag;        /**< Whether the end tag can be implied */
    int8_t saveEndTag;    /**< Whether the end tag should be saved */
    int8_t empty;         /**< Is this an empty element ? */
    int8_t depr;          /**< Is this a deprecated element ? */
    int8_t dtd;           /**< 1: only in Loose DTD, 2: only frame-set one */
    int8_t isinline;      /**< is this a block 0 or inline 1 element */
    int8_t unUsed;
    #if 0 //unused, reduce RO size
    const char *CHAR; /**< the description */
    #endif
};

/**
 * Internal description of an HTML entity
 */
typedef struct _htmlEntityDesc htmlEntityDesc;
typedef htmlEntityDesc *htmlEntityDescPtr;
struct _htmlEntityDesc {
    uint32_t     value; /**< the UNICODE value for the character */
    const char *name; /**< The entity name */
    #if 0 //unused, reduce RO size
    const char *desc; /**< the description */
    #endif
};

/**
 * There is only few public functions.
 */
const htmlElemDescPtr
htmlTagLookup(const uint8_t *tag);

const htmlEntityDescPtr
htmlEntityLookup(const uint8_t *name);

const htmlEntityDescPtr
htmlEntityValueLookup(uint32_t value);

htmlEntityDescPtr
htmlParseEntityRef(htmlParserCtxtPtr ctxt, uint8_t **str);

int32_t
htmlParseCharRef(htmlParserCtxtPtr ctxt);

int32_t
htmlIsScriptAttribute(const uint8_t *name);

#ifdef __cplusplus
}
#endif

#endif /* __HTML_PARSER_H__ */
