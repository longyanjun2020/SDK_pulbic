
#ifndef __expat_interface_h__
#define __expat_interface_h__

#include <ncc_types.h>
#include <stdio.h>
#include <stdlib.h>

#ifdef __cplusplus
extern "C" {
#endif

/* External API definitions */

#ifndef XML_STATIC
#define XML_STATIC
#endif

#if defined(_MSC_EXTENSIONS) && !defined(__BEOS__) && !defined(__CYGWIN__)
#define XML_USE_MSC_EXTENSIONS 0
#endif

/* Expat tries very hard to make the API boundary very specifically
   defined.  There are two macros defined to control this boundary;
   each of these can be defined before including this header to
   achieve some different behavior, but doing so it not recommended or
   tested frequently.

   XMLCALL    - The calling convention to use for all calls across the
                "library boundary."  This will default to cdecl, and
                try really hard to tell the compiler that's what we
                want.

   XMLIMPORT  - Whatever magic is needed to note that a function is
                to be imported from a dynamically loaded library
                (.dll, .so, or .sl, depending on your platform).

   The XMLCALL macro was added in Expat 1.95.7.  The only one which is
   expected to be directly useful in client code is XMLCALL.

   Note that on at least some Unix versions, the Expat library must be
   compiled with the cdecl calling convention as the default since
   system headers may assume the cdecl convention.
*/
#define XMLIMPORT
#define XMLCALL
#define XMLPARSEAPI(type) type

#ifdef XML_UNICODE_WCHAR_T
#define XML_UNICODE
#endif

#ifdef XML_UNICODE     /* Information is UTF-16 encoded. */
#ifdef XML_UNICODE_WCHAR_T
typedef wchar_t XML_Char;
typedef wchar_t XML_LChar;
#else
typedef unsigned short XML_Char;
typedef char XML_LChar;
#endif /* XML_UNICODE_WCHAR_T */
#else                  /* Information is UTF-8 encoded. */
typedef char XML_Char;
typedef char XML_LChar;
#endif /* XML_UNICODE */

/* just for debug information */
#define XML_PARSER_DEBUG

/* The XML_Status enum gives the possible return values for several
   API functions.  The preprocessor #defines are included so this
   stanza can be added to code that still needs to support older
   versions of Expat 1.95.x:

   #ifndef XML_STATUS_OK
   #define XML_STATUS_OK    1
   #define XML_STATUS_ERROR 0
   #endif

   Otherwise, the #define hackery is quite ugly and would have been
   dropped.
*/

enum XML_Status {
  XML_STATUS_ERROR = 0,
#define XML_STATUS_ERROR XML_STATUS_ERROR
  XML_STATUS_OK = 1,
#define XML_STATUS_OK XML_STATUS_OK
  XML_STATUS_SUSPENDED = 2,
#define XML_STATUS_SUSPENDED XML_STATUS_SUSPENDED
};

enum XML_Error {
  XML_ERROR_NONE,
  XML_ERROR_NO_MEMORY,
  XML_ERROR_SYNTAX,
  XML_ERROR_NO_ELEMENTS,
  XML_ERROR_INVALID_TOKEN,
  XML_ERROR_UNCLOSED_TOKEN,
  XML_ERROR_PARTIAL_CHAR,
  XML_ERROR_TAG_MISMATCH,
  XML_ERROR_DUPLICATE_ATTRIBUTE,
  XML_ERROR_JUNK_AFTER_DOC_ELEMENT,
  XML_ERROR_PARAM_ENTITY_REF,
  XML_ERROR_UNDEFINED_ENTITY,
  XML_ERROR_RECURSIVE_ENTITY_REF,
  XML_ERROR_ASYNC_ENTITY,
  XML_ERROR_BAD_CHAR_REF,
  XML_ERROR_BINARY_ENTITY_REF,
  XML_ERROR_ATTRIBUTE_EXTERNAL_ENTITY_REF,
  XML_ERROR_MISPLACED_XML_PI,
  XML_ERROR_UNKNOWN_ENCODING,
  XML_ERROR_INCORRECT_ENCODING,
  XML_ERROR_UNCLOSED_CDATA_SECTION,
  XML_ERROR_EXTERNAL_ENTITY_HANDLING,
  XML_ERROR_NOT_STANDALONE,
  XML_ERROR_UNEXPECTED_STATE,
  XML_ERROR_ENTITY_DECLARED_IN_PE,
  XML_ERROR_FEATURE_REQUIRES_XML_DTD,
  XML_ERROR_CANT_CHANGE_FEATURE_ONCE_PARSING,
  /* Added in 1.95.7. */
  XML_ERROR_UNBOUND_PREFIX,
  /* Added in 1.95.8. */
  XML_ERROR_UNDECLARING_PREFIX,
  XML_ERROR_INCOMPLETE_PE,
  XML_ERROR_XML_DECL,
  XML_ERROR_TEXT_DECL,
  XML_ERROR_PUBLICID,
  XML_ERROR_SUSPENDED,
  XML_ERROR_NOT_SUSPENDED,
  XML_ERROR_ABORTED,
  XML_ERROR_FINISHED,
  XML_ERROR_SUSPEND_PE
};

typedef struct {
  void *(*malloc_fcn)(size_t size);
  void *(*realloc_fcn)(void *ptr, size_t size);
  void (*free_fcn)(void *ptr);
} XML_Memory_Handling_Suite;

struct XML_ParserStruct;
typedef struct XML_ParserStruct *XML_Parser;

/*
 ####################### API #############################
 */

/* Constructs a new parser using the memory management suite referred to
   by memsuite. If memsuite is NULL, then use the standard library memory
   suite. If namespaceSeparator is non-NULL it creates a parser with
   namespace processing as described above. The character pointed at
   will serve as the namespace separator.

   All further memory operations used for the created parser will come from
   the given suite.
*/
XMLPARSEAPI(XML_Parser)
XML_ParserCreate_MM(const XML_Char *encoding,
                    const XML_Memory_Handling_Suite *memsuite,
                    const XML_Char *namespaceSeparator);

/* Frees memory used by the parser. */
XMLPARSEAPI(void)
XML_ParserFree(XML_Parser parser);

/* This value is passed as the userData argument to callbacks. */
XMLPARSEAPI(void)
XML_SetUserData(XML_Parser parser, void *userData);

/* Parses some input. Returns XML_STATUS_ERROR if a fatal error is
   detected.  The last call to XML_Parse must have isFinal true; len
   may be zero for this call (or any other).

   Though the return values for these functions has always been
   described as a Boolean value, the implementation, at least for the
   1.95.x series, has always returned exactly one of the XML_Status
   values.
*/
XMLPARSEAPI(enum XML_Status)
XML_Parse(XML_Parser parser, const char *s, int len, int isFinal);

/* Returns a string describing the error. */
XMLPARSEAPI(const XML_LChar *)
XML_ErrorString(enum XML_Error code);

/* If XML_Parse or XML_ParseBuffer have returned XML_STATUS_ERROR, then
   XML_GetErrorCode returns information about the error.
*/
XMLPARSEAPI(enum XML_Error)
XML_GetErrorCode(XML_Parser parser);


/* These functions return information about the current parse
   location.  They may be called from any callback called to report
   some parse event; in this case the location is the location of the
   first of the sequence of characters that generated the event.  When
   called from callbacks generated by declarations in the document
   prologue, the location identified isn't as neatly defined, but will
   be within the relevant markup.  When called outside of the callback
   functions, the position indicated will be just past the last parse
   event (regardless of whether there was an associated callback).

   They may also be called after returning from a call to XML_Parse
   or XML_ParseBuffer.  If the return value is XML_STATUS_ERROR then
   the location is the location of the character at which the error
   was detected; otherwise the location is the location of the last
   parse event, as described above.
*/
XMLPARSEAPI(int) XML_GetCurrentLineNumber(XML_Parser parser);
XMLPARSEAPI(int) XML_GetCurrentColumnNumber(XML_Parser parser);
XMLPARSEAPI(long) XML_GetCurrentByteIndex(XML_Parser parser);

/* For backwards compatibility with previous versions. */
#define XML_GetErrorLineNumber   XML_GetCurrentLineNumber
#define XML_GetErrorColumnNumber XML_GetCurrentColumnNumber
#define XML_GetErrorByteIndex    XML_GetCurrentByteIndex

//struct XML_ParserStruct;
//typedef struct XML_ParserStruct *XML_Parser;

typedef struct {
  int map[256];
  void *data;
  int (XMLCALL *convert)(void *data, const char *s);
  void (XMLCALL *release)(void *data);
} XML_Encoding;

/* |---------------------------------------------|
   |            XML_*handler --> *handler        |
   |---------------------------------------------|

   if you have included commonSAXHandler.h, use it as declarition

*/

#ifdef __PARSER_SAXHANDLERS_H__

#define XML_Content_Type    Parser_XML_Content_Type
#define XML_Content_Quant   Parser_XML_Content_Quant
#define XML_Content         Parser_XML_Content

/**
 * startDocumentSAXHandler:
 * @ctx:  the user data (XML parser context)
 *
 * Called when the document start being processed.
 */
#define XML_StartDocHandler                 startDocumentSAXHandler
#define XML_EndDocHandler                   endDocumentSAXHandler
/*
   #### universal content sax handlers ####
*/
#define XML_StartDoctypeDeclHandler         startDoctypeDeclSAXHandler
#define XML_EndDoctypeDeclHandler           endDoctypeDeclSAXHandler
//#define startDocumentSAXHandler startDocumentHandler; /**<start document sax handler*/
//#define endDocumentSAXHandler endDocumentHandler; /**<end document sax handler*/
#define XML_StartElementHandler             startElementSAXHandler
#define XML_EndElementHandler               endElementSAXHandler
#define XML_CharacterDataHandler            charactersSAXHandler
//#define referenceSAXFunc                  referenceSAXHandler
#define XML_StartCdataSectionHandler        startCdataSectionSAXHandler
#define XML_EndCdataSectionHandler          endCdataSectionSAXHandler
//#define cdataBlockSAXHandler cdataSectionHandler; /**<CDATA section sax handler*/

/*
   #### universal lexical handler ####
*/
#define XML_ProcessingInstructionHandler    processingInstructionSAXHandler
#define XML_CommentHandler                  commentSAXHandler

/*
   #### items relative with concrete parser ####
*/
#define XML_SkippedEntityHandler            skippedEntitySAXHandler
//#define ignorableWhitespaceSAXFunc        ignorableWhitespaceSAXHandler

/*
   #### declaration ####
*/
//#define startDoctypeDeclSAXHandler startDoctypeDeclHandler; /**<start doctype declaration sax handler*/
//#define endDoctypeDeclSAXHandler endDoctypeDeclHandler; /**<end doctype declaration sax handler*/
#define XML_XmlDeclHandler                  xmlDeclSAXHandler

#define XML_ElementDeclHandler              elementDeclSAXHandler
#define XML_AttlistDeclHandler              attlistDeclSAXHandler
#define XML_NotationDeclHandler             notationDeclSAXHandler
#define XML_EntityDeclHandler               entityDeclSAXHandler
#define XML_UnparsedEntityDeclHandler       unparsedEntitySAXDeclHandler
#define XML_ExternalEntityRefHandler        externalEntitySAXRefHandler

/*
   #### name space handlers ####
*/
#define XML_StartNamespaceDeclHandler       startNamespaceDeclSAXHandler
#define XML_EndNamespaceDeclHandler         endNamespaceDeclSAXHandler

//#define warningSAXFunc                    warningSAXHandler
//#define errorSAXFunc                      errorSAXHandler
#define XML_FatalErrorHandler               fatalErrorSAXHandler
//fatalErrorSAXFunc fatalErrorSAXHandler

#else /* __PARSER_SAXHANDLERS_H__ */
enum XML_Content_Type {
  XML_CTYPE_EMPTY = 1,
  XML_CTYPE_ANY,
  XML_CTYPE_MIXED,
  XML_CTYPE_NAME,
  XML_CTYPE_CHOICE,
  XML_CTYPE_SEQ
};

enum XML_Content_Quant {
  XML_CQUANT_NONE,
  XML_CQUANT_OPT,
  XML_CQUANT_REP,
  XML_CQUANT_PLUS
};
/* If type == XML_CTYPE_EMPTY or XML_CTYPE_ANY, then quant will be
   XML_CQUANT_NONE, and the other fields will be zero or NULL.
   If type == XML_CTYPE_MIXED, then quant will be NONE or REP and
   numchildren will contain number of elements that may be mixed in
   and children point to an array of XML_Content cells that will be
   all of XML_CTYPE_NAME type with no quantification.

   If type == XML_CTYPE_NAME, then the name points to the name, and
   the numchildren field will be zero and children will be NULL. The
   quant fields indicates any quantifiers placed on the name.

   CHOICE and SEQ will have name NULL, the number of children in
   numchildren and children will point, recursively, to an array
   of XML_Content cells.

   The EMPTY, ANY, and MIXED types will only occur at top level.
*/

typedef struct XML_cp XML_Content;

struct XML_cp {
  enum XML_Content_Type         type;
  enum XML_Content_Quant        quant;
  XML_Char *                    name;
  unsigned int                  numchildren;
  XML_Content *                 children;
};

/**
 * startDocumentSAXHandler:
 * @ctx:  the user data (XML parser context)
 *
 * Called when the document start being processed. --Dylan, 20050823
 */
typedef void (XMLCALL *XML_StartDocHandler) (void *userData);
typedef void (XMLCALL *XML_EndDocHandler) (void *userData);


/* This is called for the start of the DOCTYPE declaration, before
   any DTD or internal subset is parsed.
*/
typedef void (XMLCALL *XML_StartDoctypeDeclHandler) (
                                            void *userData,
                                            const XML_Char *doctypeName,
                                            const XML_Char *sysid,
                                            const XML_Char *pubid,
                                            int has_internal_subset);

/* This is called for the start of the DOCTYPE declaration when the
   closing > is encountered, but after processing any external
   subset.
*/
typedef void (XMLCALL *XML_EndDoctypeDeclHandler)(void *userData);

/* atts is array of name/value pairs, terminated by 0;
   names and values are 0 terminated.
*/
typedef void (XMLCALL *XML_StartElementHandler) (void *userData,
                                                 const XML_Char *name,
                                                 const XML_Char **atts);

typedef void (XMLCALL *XML_EndElementHandler) (void *userData,
                                               const XML_Char *name);


/* s is not 0 terminated. */
typedef void (XMLCALL *XML_CharacterDataHandler) (void *userData,
                                                  const XML_Char *s,
                                                  int len);

/* target and data are 0 terminated */
typedef void (XMLCALL *XML_ProcessingInstructionHandler) (
                                                void *userData,
                                                const XML_Char *target,
                                                const XML_Char *data);

/* data is 0 terminated */
typedef void (XMLCALL *XML_CommentHandler) (void *userData,
                                            const XML_Char *data);

typedef void (XMLCALL *XML_StartCdataSectionHandler) (void *userData);
typedef void (XMLCALL *XML_EndCdataSectionHandler) (void *userData);

/* This is called in two situations:
   1) An entity reference is encountered for which no declaration
      has been read *and* this is not an error.
   2) An internal entity reference is read, but not expanded, because
      XML_SetDefaultHandler has been called.
   Note: skipped parameter entities in declarations and skipped general
         entities in attribute values cannot be reported, because
         the event would be out of sync with the reporting of the
         declarations or attribute values
*/
typedef void (XMLCALL *XML_SkippedEntityHandler) (
                                    void *userData,
                                    const XML_Char *entityName,
                                    int is_parameter_entity);

/* The XML declaration handler is called for *both* XML declarations
   and text declarations. The way to distinguish is that the version
   parameter will be NULL for text declarations. The encoding
   parameter may be NULL for XML declarations. The standalone
   parameter will be -1, 0, or 1 indicating respectively that there
   was no standalone parameter in the declaration, that it was given
   as no, or that it was given as yes.
*/
typedef void (XMLCALL *XML_XmlDeclHandler) (void           *userData,
                                            const XML_Char *version,
                                            const XML_Char *encoding,
                                            int             standalone);

/* This is called for an element declaration. See above for
   description of the model argument. It's the caller's responsibility
   to free model when finished with it.
*/
typedef void (XMLCALL *XML_ElementDeclHandler) (void *userData,
                                                const XML_Char *name,
                                               XML_Content *model);

/* The Attlist declaration handler is called for *each* attribute. So
   a single Attlist declaration with multiple attributes declared will
   generate multiple calls to this handler. The "default" parameter
   may be NULL in the case of the "#IMPLIED" or "#REQUIRED"
   keyword. The "isrequired" parameter will be true and the default
   value will be NULL in the case of "#REQUIRED". If "isrequired" is
   true and default is non-NULL, then this is a "#FIXED" default.
*/
typedef void (XMLCALL *XML_AttlistDeclHandler) (
                                    void            *userData,
                                    const XML_Char  *elname,
                                    const XML_Char  *attname,
                                    const XML_Char  *att_type,
                                    const XML_Char  *dflt,
                                    int              isrequired);

/* This is called for a declaration of notation.  The base argument is
   whatever was set by XML_SetBase. The notationName will never be
   NULL.  The other arguments can be.
*/
typedef void (XMLCALL *XML_NotationDeclHandler) (
                                    void *userData,
                                    const XML_Char *notationName,
                                    const XML_Char *base,
                                    const XML_Char *systemId,
                                    const XML_Char *publicId);


/* This is called for entity declarations. The is_parameter_entity
   argument will be non-zero if the entity is a parameter entity, zero
   otherwise.

   For internal entities (<!ENTITY foo "bar">), value will
   be non-NULL and systemId, publicID, and notationName will be NULL.
   The value string is NOT nul-terminated; the length is provided in
   the value_length argument. Since it is legal to have zero-length
   values, do not use this argument to test for internal entities.

   For external entities, value will be NULL and systemId will be
   non-NULL. The publicId argument will be NULL unless a public
   identifier was provided. The notationName argument will have a
   non-NULL value only for unparsed entity declarations.

   Note that is_parameter_entity can't be changed to XML_Bool, since
   that would break binary compatibility.
*/
typedef void (XMLCALL *XML_EntityDeclHandler) (
                              void *userData,
                              const XML_Char *entityName,
                              int is_parameter_entity,
                              const XML_Char *value,
                              int value_length,
                              const XML_Char *base,
                              const XML_Char *systemId,
                              const XML_Char *publicId,
                              const XML_Char *notationName);


/* OBSOLETE -- OBSOLETE -- OBSOLETE
   This handler has been superceded by the EntityDeclHandler above.
   It is provided here for backward compatibility.

   This is called for a declaration of an unparsed (NDATA) entity.
   The base argument is whatever was set by XML_SetBase. The
   entityName, systemId and notationName arguments will never be
   NULL. The other arguments may be.
*/
typedef void (XMLCALL *XML_UnparsedEntityDeclHandler) (
                                    void *userData,
                                    const XML_Char *entityName,
                                    const XML_Char *base,
                                    const XML_Char *systemId,
                                    const XML_Char *publicId,
                                    const XML_Char *notationName);

/* This is called for a reference to an external parsed general
   entity.  The referenced entity is not automatically parsed.  The
   application can parse it immediately or later using
   XML_ExternalEntityParserCreate.

   The parser argument is the parser parsing the entity containing the
   reference; it can be passed as the parser argument to
   XML_ExternalEntityParserCreate.  The systemId argument is the
   system identifier as specified in the entity declaration; it will
   not be NULL.

   The base argument is the system identifier that should be used as
   the base for resolving systemId if systemId was relative; this is
   set by XML_SetBase; it may be NULL.

   The publicId argument is the public identifier as specified in the
   entity declaration, or NULL if none was specified; the whitespace
   in the public identifier will have been normalized as required by
   the XML spec.

   The context argument specifies the parsing context in the format
   expected by the context argument to XML_ExternalEntityParserCreate;
   context is valid only until the handler returns, so if the
   referenced entity is to be parsed later, it must be copied.
   context is NULL only when the entity is a parameter entity.

   The handler should return XML_STATUS_ERROR if processing should not
   continue because of a fatal error in the handling of the external
   entity.  In this case the calling parser will return an
   XML_ERROR_EXTERNAL_ENTITY_HANDLING error.

   Note that unlike other handlers the first argument is the parser,
   not userData.
*/
typedef int (XMLCALL *XML_ExternalEntityRefHandler) (
                                    XML_Parser parser,
                                    const XML_Char *context,
                                    const XML_Char *base,
                                    const XML_Char *systemId,
                                    const XML_Char *publicId);

/* When namespace processing is enabled, these are called once for
   each namespace declaration. The call to the start and end element
   handlers occur between the calls to the start and end namespace
   declaration handlers. For an xmlns attribute, prefix will be
   NULL.  For an xmlns="" attribute, uri will be NULL.
*/
typedef void (XMLCALL *XML_StartNamespaceDeclHandler) (
                                    void *userData,
                                    const XML_Char *prefix,
                                    const XML_Char *uri);

typedef void (XMLCALL *XML_EndNamespaceDeclHandler) (
                                    void *userData,
                                    const XML_Char *prefix);

/**
 * fatalErrorSAXHandler:
 * @ctx:  an XML parser context
 * @msg:  the message to display/transmit
 * @...:  extra parameters for the message display
 *
 * Display and format fatal error messages, callback.
 * Note: so far fatalError() SAX callbacks are used to
 *       get all the callbacks for errors.
 */
typedef void (XMLCALL *XML_FatalErrorHandler) (void *userData,
                const XML_Char *msg, ...);


#endif  /* __PARSER_SAXHANDLERS_H__ */

/*|------------------------------------------------------------|*/

XMLPARSEAPI(void)
XML_SetElementDeclHandler(XML_Parser parser,
                          XML_ElementDeclHandler eldecl);


XMLPARSEAPI(void)
XML_SetAttlistDeclHandler(XML_Parser parser,
                          XML_AttlistDeclHandler attdecl);


XMLPARSEAPI(void)
XML_SetXmlDeclHandler(XML_Parser parser,
                      XML_XmlDeclHandler xmldecl);

/* This is called for any characters in the XML document for which
   there is no applicable handler.  This includes both characters that
   are part of markup which is of a kind that is not reported
   (comments, markup declarations), or characters that are part of a
   construct which could be reported but for which no handler has been
   supplied. The characters are passed exactly as they were in the XML
   document except that they will be encoded in UTF-8 or UTF-16.
   Line boundaries are not normalized. Note that a byte order mark
   character is not passed to the default handler. There are no
   guarantees about how characters are divided between calls to the
   default handler: for example, a comment might be split between
   multiple calls.
*/
typedef void (XMLCALL *XML_DefaultHandler) (void *userData,
                                            const XML_Char *s,
                                            int len);



XMLPARSEAPI(void)
XML_SetEntityDeclHandler(XML_Parser parser,
                         XML_EntityDeclHandler handler);




/* This is called if the document is not standalone, that is, it has an
   external subset or a reference to a parameter entity, but does not
   have standalone="yes". If this handler returns XML_STATUS_ERROR,
   then processing will not continue, and the parser will return a
   XML_ERROR_NOT_STANDALONE error.
   If parameter entity parsing is enabled, then in addition to the
   conditions above this handler will only be called if the referenced
   entity was actually read.
*/
typedef int (XMLCALL *XML_NotStandaloneHandler) (void *userData);

/* This is called for an encoding that is unknown to the parser.

   The encodingHandlerData argument is that which was passed as the
   second argument to XML_SetUnknownEncodingHandler.

   The name argument gives the name of the encoding as specified in
   the encoding declaration.

   If the callback can provide information about the encoding, it must
   fill in the XML_Encoding structure, and return XML_STATUS_OK.
   Otherwise it must return XML_STATUS_ERROR.

   If info does not describe a suitable encoding, then the parser will
   return an XML_UNKNOWN_ENCODING error.
*/
typedef int (XMLCALL *XML_UnknownEncodingHandler) (
                                    void *encodingHandlerData,
                                    const XML_Char *name,
                                    XML_Encoding *info);

XMLPARSEAPI(void)
XML_SetElementHandler(XML_Parser parser,
                      XML_StartElementHandler start,
                      XML_EndElementHandler end);

XMLPARSEAPI(void)
XML_SetStartElementHandler(XML_Parser parser,
                           XML_StartElementHandler handler);

XMLPARSEAPI(void)
XML_SetEndElementHandler(XML_Parser parser,
                         XML_EndElementHandler handler);

XMLPARSEAPI(void)
XML_SetCharacterDataHandler(XML_Parser parser,
                            XML_CharacterDataHandler handler);

XMLPARSEAPI(void)
XML_SetProcessingInstructionHandler(XML_Parser parser,
                                    XML_ProcessingInstructionHandler handler);
XMLPARSEAPI(void)
XML_SetCommentHandler(XML_Parser parser,
                      XML_CommentHandler handler);

XMLPARSEAPI(void)
XML_SetCdataSectionHandler(XML_Parser parser,
                           XML_StartCdataSectionHandler start,
                           XML_EndCdataSectionHandler end);

XMLPARSEAPI(void)
XML_SetStartCdataSectionHandler(XML_Parser parser,
                                XML_StartCdataSectionHandler start);

XMLPARSEAPI(void)
XML_SetEndCdataSectionHandler(XML_Parser parser,
                              XML_EndCdataSectionHandler end);

/* This sets the default handler and also inhibits expansion of
   internal entities. These entity references will be passed to the
   default handler, or to the skipped entity handler, if one is set.
*/
XMLPARSEAPI(void)
XML_SetDefaultHandler(XML_Parser parser,
                      XML_DefaultHandler handler);

/* This sets the default handler but does not inhibit expansion of
   internal entities.  The entity reference will not be passed to the
   default handler.
*/
XMLPARSEAPI(void)
XML_SetDefaultHandlerExpand(XML_Parser parser,
                            XML_DefaultHandler handler);

XMLPARSEAPI(void)
XML_SetDoctypeDeclHandler(XML_Parser parser,
                          XML_StartDoctypeDeclHandler start,
                          XML_EndDoctypeDeclHandler end);

XMLPARSEAPI(void)
XML_SetStartDoctypeDeclHandler(XML_Parser parser,
                               XML_StartDoctypeDeclHandler start);

XMLPARSEAPI(void)
XML_SetEndDoctypeDeclHandler(XML_Parser parser,
                             XML_EndDoctypeDeclHandler end);

XMLPARSEAPI(void)
XML_SetUnparsedEntityDeclHandler(XML_Parser parser,
                                 XML_UnparsedEntityDeclHandler handler);

XMLPARSEAPI(void)
XML_SetNotationDeclHandler(XML_Parser parser,
                           XML_NotationDeclHandler handler);

XMLPARSEAPI(void)
XML_SetNamespaceDeclHandler(XML_Parser parser,
                            XML_StartNamespaceDeclHandler start,
                            XML_EndNamespaceDeclHandler end);

XMLPARSEAPI(void)
XML_SetStartNamespaceDeclHandler(XML_Parser parser,
                                 XML_StartNamespaceDeclHandler start);

XMLPARSEAPI(void)
XML_SetEndNamespaceDeclHandler(XML_Parser parser,
                               XML_EndNamespaceDeclHandler end);

XMLPARSEAPI(void)
XML_SetNotStandaloneHandler(XML_Parser parser,
                            XML_NotStandaloneHandler handler);

XMLPARSEAPI(void)
XML_SetExternalEntityRefHandler(XML_Parser parser,
                                XML_ExternalEntityRefHandler handler);

/* If a non-NULL value for arg is specified here, then it will be
   passed as the first argument to the external entity ref handler
   instead of the parser object.
*/
XMLPARSEAPI(void)
XML_SetExternalEntityRefHandlerArg(XML_Parser parser,
                                   void *arg);

XMLPARSEAPI(void)
XML_SetSkippedEntityHandler(XML_Parser parser,
                            XML_SkippedEntityHandler handler);

XMLPARSEAPI(void)
XML_SetUnknownEncodingHandler(XML_Parser parser,
                              XML_UnknownEncodingHandler handler,
                              void *encodingHandlerData);

/* 000000000000000000000000000000000000000000000000000000000000000000 */
/*
 *  Set error callback for up layer. --Dylan, 20050813
 */
XMLPARSEAPI(void)
XML_SetXmlFatalErrorHandler(XML_Parser parser,
                            XML_FatalErrorHandler handler);
/*
 *  call fatal error handler for extenal caller. --Dylan, 20050816
 */
void
callXmlFatalErrorHandler(XML_Parser parser,
                         const XML_Char *errorMsg, ...);
/*
 *  Set start and end handler for external caller. --Dylan, 20050823
 */
XMLPARSEAPI(void)
XML_SetXmlDocHandler(XML_Parser parser,
                     XML_StartDocHandler start,
                     XML_EndDocHandler end);

void
callXmlEndDocHandler(XML_Parser parser);

#ifdef __cplusplus
}
#endif

#endif /* __expat_interface_h__ */
