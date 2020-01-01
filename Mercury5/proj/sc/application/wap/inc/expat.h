
#ifndef XmlParse_INCLUDED
#define XmlParse_INCLUDED 1

#ifdef __VMS
/*      0        1         2         3      0        1         2         3
        1234567890123456789012345678901     1234567890123456789012345678901 */
#define XML_SetProcessingInstructionHandler XML_SetProcessingInstrHandler
#define XML_SetUnparsedEntityDeclHandler    XML_SetUnparsedEntDeclHandler
#define XML_SetStartNamespaceDeclHandler    XML_SetStartNamespcDeclHandler
#define XML_SetExternalEntityRefHandlerArg  XML_SetExternalEntRefHandlerArg
#endif

#include <stdlib.h>
#include "expat_external.h"
//#ifdef NCC_BROWSER_XML
#include "expatXMLSAXHandlersWrapper.h" /* Sax handlers */
//#endif /* NCC_BROWSER_XML */

/* Should this be defined using stdbool.h when C99 is available? */
typedef unsigned char XML_Bool;
#define XML_TRUE   ((XML_Bool) 1)
#define XML_FALSE  ((XML_Bool) 0)

/* Constructs a new parser; encoding is the encoding specified by the
   external protocol or NULL if there is none specified.
*/
XMLPARSEAPI(XML_Parser)
XML_ParserCreate(const XML_Char *encoding);

/* Constructs a new parser and namespace processor.  Element type
   names and attribute names that belong to a namespace will be
   expanded; unprefixed attribute names are never expanded; unprefixed
   element type names are expanded only if there is a default
   namespace. The expanded name is the concatenation of the namespace
   URI, the namespace separator character, and the local part of the
   name.  If the namespace separator is '\0' then the namespace URI
   and the local part will be concatenated without any separator.
   When a namespace is not declared, the name and prefix will be
   passed through without expansion.
*/
XMLPARSEAPI(XML_Parser)
XML_ParserCreateNS(const XML_Char *encoding, XML_Char namespaceSeparator);

/* Prepare a parser object to be re-used.  This is particularly
   valuable when memory allocation overhead is disproportionatly high,
   such as when a large number of small documnents need to be parsed.
   All handlers are cleared from the parser, except for the
   unknownEncodingHandler. The parser's external state is re-initialized
   except for the values of ns and ns_triplets.

   Added in Expat 1.95.3.
*/
XMLPARSEAPI(XML_Bool)
XML_ParserReset(XML_Parser parser, const XML_Char *encoding);




/* This structure is filled in by the XML_UnknownEncodingHandler to
   provide information to the parser about encodings that are unknown
   to the parser.

   The map[b] member gives information about byte sequences whose
   first byte is b.

   If map[b] is c where c is >= 0, then b by itself encodes the
   Unicode scalar value c.

   If map[b] is -1, then the byte sequence is malformed.

   If map[b] is -n, where n >= 2, then b is the first byte of an
   n-byte sequence that encodes a single Unicode scalar value.

   The data member will be passed as the first argument to the convert
   function.

   The convert function is used to convert multibyte sequences; s will
   point to a n-byte sequence where map[(unsigned char)*s] == -n.  The
   convert function must return the Unicode scalar value represented
   by this byte sequence or -1 if the byte sequence is malformed.

   The convert function may be NULL if the encoding is a single-byte
   encoding, that is if map[b] >= -1 for all bytes b.

   When the parser is finished with the encoding, then if release is
   not NULL, it will call release passing it the data member; once
   release has been called, the convert function will not be called
   again.

   Expat places certain restrictions on the encodings that are supported
   using this mechanism.

   1. Every ASCII character that can appear in a well-formed XML document,
      other than the characters

      $@\^`{}~

      must be represented by a single byte, and that byte must be the
      same byte that represents that character in ASCII.

   2. No character may require more than 4 bytes to encode.

   3. All characters encoded must have Unicode scalar values <=
      0xFFFF, (i.e., characters that would be encoded by surrogates in
      UTF-16 are  not allowed).  Note that this restriction doesn't
      apply to the built-in support for UTF-8 and UTF-16.

   4. No Unicode character may be encoded by more than one distinct
      sequence of bytes.
*/


/* This can be called within a handler for a start element, end
   element, processing instruction or character data.  It causes the
   corresponding markup to be passed to the default handler.
*/
XMLPARSEAPI(void)
XML_DefaultCurrent(XML_Parser parser);

/* If do_nst is non-zero, and namespace processing is in effect, and
   a name has a prefix (i.e. an explicit namespace qualifier) then
   that name is returned as a triplet in a single string separated by
   the separator character specified when the parser was created: URI
   + sep + local_name + sep + prefix.

   If do_nst is zero, then namespace information is returned in the
   default manner (URI + sep + local_name) whether or not the name
   has a prefix.

   Note: Calling XML_SetReturnNSTriplet after XML_Parse or
     XML_ParseBuffer has no effect.
*/

XMLPARSEAPI(void)
XML_SetReturnNSTriplet(XML_Parser parser, int do_nst);


/* Returns the last value set by XML_SetUserData or NULL. */
#define XML_GetUserData(parser) (*(void **)(parser))

/* This is equivalent to supplying an encoding argument to
   XML_ParserCreate. On success XML_SetEncoding returns non-zero,
   zero otherwise.
   Note: Calling XML_SetEncoding after XML_Parse or XML_ParseBuffer
     has no effect and returns XML_STATUS_ERROR.
*/
XMLPARSEAPI(enum XML_Status)
XML_SetEncoding(XML_Parser parser, const XML_Char *encoding);

/* If this function is called, then the parser will be passed as the
   first argument to callbacks instead of userData.  The userData will
   still be accessible using XML_GetUserData.
*/
XMLPARSEAPI(void)
XML_UseParserAsHandlerArg(XML_Parser parser);

/* If useDTD == XML_TRUE is passed to this function, then the parser
   will assume that there is an external subset, even if none is
   specified in the document. In such a case the parser will call the
   externalEntityRefHandler with a value of NULL for the systemId
   argument (the publicId and context arguments will be NULL as well).
   Note: For the purpose of checking WFC: Entity Declared, passing
     useDTD == XML_TRUE will make the parser behave as if the document
     had a DTD with an external subset.
   Note: If this function is called, then this must be done before
     the first call to XML_Parse or XML_ParseBuffer, since it will
     have no effect after that.  Returns
     XML_ERROR_CANT_CHANGE_FEATURE_ONCE_PARSING.
   Note: If the document does not have a DOCTYPE declaration at all,
     then startDoctypeDeclHandler and endDoctypeDeclHandler will not
     be called, despite an external subset being parsed.
   Note: If XML_DTD is not defined when Expat is compiled, returns
     XML_ERROR_FEATURE_REQUIRES_XML_DTD.
*/
XMLPARSEAPI(enum XML_Error)
XML_UseForeignDTD(XML_Parser parser, XML_Bool useDTD);


/* Sets the base to be used for resolving relative URIs in system
   identifiers in declarations.  Resolving relative identifiers is
   left to the application: this value will be passed through as the
   base argument to the XML_ExternalEntityRefHandler,
   XML_NotationDeclHandler and XML_UnparsedEntityDeclHandler. The base
   argument will be copied.  Returns XML_STATUS_ERROR if out of memory,
   XML_STATUS_OK otherwise.
*/
XMLPARSEAPI(enum XML_Status)
XML_SetBase(XML_Parser parser, const XML_Char *base);

XMLPARSEAPI(const XML_Char *)
XML_GetBase(XML_Parser parser);

/* Returns the number of the attribute/value pairs passed in last call
   to the XML_StartElementHandler that were specified in the start-tag
   rather than defaulted. Each attribute/value pair counts as 2; thus
   this correspondds to an index into the atts array passed to the
   XML_StartElementHandler.
*/
XMLPARSEAPI(int)
XML_GetSpecifiedAttributeCount(XML_Parser parser);

/* Returns the index of the ID attribute passed in the last call to
   XML_StartElementHandler, or -1 if there is no ID attribute.  Each
   attribute/value pair counts as 2; thus this correspondds to an
   index into the atts array passed to the XML_StartElementHandler.
*/
XMLPARSEAPI(int)
XML_GetIdAttributeIndex(XML_Parser parser);


XMLPARSEAPI(void *)
XML_GetBuffer(XML_Parser parser, int len);

XMLPARSEAPI(enum XML_Status)
XML_ParseBuffer(XML_Parser parser, int len, int isFinal);

/* Stops parsing, causing XML_Parse() or XML_ParseBuffer() to return.
   Must be called from within a call-back handler, except when aborting
   (resumable = 0) an already suspended parser. Some call-backs may
   still follow because they would otherwise get lost. Examples:
   - endElementHandler() for empty elements when stopped in
     startElementHandler(),
   - endNameSpaceDeclHandler() when stopped in endElementHandler(),
   and possibly others.

   Can be called from most handlers, including DTD related call-backs,
   except when parsing an external parameter entity and resumable != 0.
   Returns XML_STATUS_OK when successful, XML_STATUS_ERROR otherwise.
   Possible error codes:
   - XML_ERROR_SUSPENDED: when suspending an already suspended parser.
   - XML_ERROR_FINISHED: when the parser has already finished.
   - XML_ERROR_SUSPEND_PE: when suspending while parsing an external PE.

   When resumable != 0 (true) then parsing is suspended, that is,
   XML_Parse() and XML_ParseBuffer() return XML_STATUS_SUSPENDED.
   Otherwise, parsing is aborted, that is, XML_Parse() and XML_ParseBuffer()
   return XML_STATUS_ERROR with error code XML_ERROR_ABORTED.

   *Note*:
   This will be applied to the current parser instance only, that is, if
   there is a parent parser then it will continue parsing when the
   externalEntityRefHandler() returns. It is up to the implementation of
   the externalEntityRefHandler() to call XML_StopParser() on the parent
   parser (recursively), if one wants to stop parsing altogether.

   When suspended, parsing can be resumed by calling XML_ResumeParser().
*/
XMLPARSEAPI(enum XML_Status)
XML_StopParser(XML_Parser parser, XML_Bool resumable);

/* Resumes parsing after it has been suspended with XML_StopParser().
   Must not be called from within a handler call-back. Returns same
   status codes as XML_Parse() or XML_ParseBuffer().
   Additional error code XML_ERROR_NOT_SUSPENDED possible.

   *Note*:
   This must be called on the most deeply nested child parser instance
   first, and on its parent parser only after the child parser has finished,
   to be applied recursively until the document entity's parser is restarted.
   That is, the parent parser will not resume by itself and it is up to the
   application to call XML_ResumeParser() on it at the appropriate moment.
*/
XMLPARSEAPI(enum XML_Status)
XML_ResumeParser(XML_Parser parser);

enum XML_Parsing {
  XML_INITIALIZED,
  XML_PARSING,
  XML_FINISHED,
  XML_SUSPENDED
};

typedef struct {
  enum XML_Parsing parsing;
  XML_Bool finalBuffer;
} XML_ParsingStatus;

/* Returns status of parser with respect to being initialized, parsing,
   finished, or suspended and processing the final buffer.
   XXX XML_Parse() and XML_ParseBuffer() should return XML_ParsingStatus,
   XXX with XML_FINISHED_OK or XML_FINISHED_ERROR replacing XML_FINISHED
*/
XMLPARSEAPI(void)
XML_GetParsingStatus(XML_Parser parser, XML_ParsingStatus *status);

/* Creates an XML_Parser object that can parse an external general
   entity; context is a '\0'-terminated string specifying the parse
   context; encoding is a '\0'-terminated string giving the name of
   the externally specified encoding, or NULL if there is no
   externally specified encoding.  The context string consists of a
   sequence of tokens separated by formfeeds (\f); a token consisting
   of a name specifies that the general entity of the name is open; a
   token of the form prefix=uri specifies the namespace for a
   particular prefix; a token of the form =uri specifies the default
   namespace.  This can be called at any point after the first call to
   an ExternalEntityRefHandler so longer as the parser has not yet
   been freed.  The new parser is completely independent and may
   safely be used in a separate thread.  The handlers and userData are
   initialized from the parser argument.  Returns NULL if out of memory.
   Otherwise returns a new XML_Parser object.
*/
XMLPARSEAPI(XML_Parser)
XML_ExternalEntityParserCreate(XML_Parser parser,
                               const XML_Char *context,
                               const XML_Char *encoding);

enum XML_ParamEntityParsing {
  XML_PARAM_ENTITY_PARSING_NEVER,
  XML_PARAM_ENTITY_PARSING_UNLESS_STANDALONE,
  XML_PARAM_ENTITY_PARSING_ALWAYS
};

/* Controls parsing of parameter entities (including the external DTD
   subset). If parsing of parameter entities is enabled, then
   references to external parameter entities (including the external
   DTD subset) will be passed to the handler set with
   XML_SetExternalEntityRefHandler.  The context passed will be 0.

   Unlike external general entities, external parameter entities can
   only be parsed synchronously.  If the external parameter entity is
   to be parsed, it must be parsed during the call to the external
   entity ref handler: the complete sequence of
   XML_ExternalEntityParserCreate, XML_Parse/XML_ParseBuffer and
   XML_ParserFree calls must be made during this call.  After
   XML_ExternalEntityParserCreate has been called to create the parser
   for the external parameter entity (context must be 0 for this
   call), it is illegal to make any calls on the old parser until
   XML_ParserFree has been called on the newly created parser.
   If the library has been compiled without support for parameter
   entity parsing (ie without XML_DTD being defined), then
   XML_SetParamEntityParsing will return 0 if parsing of parameter
   entities is requested; otherwise it will return non-zero.
   Note: If XML_SetParamEntityParsing is called after XML_Parse or
      XML_ParseBuffer, then it has no effect and will always return 0.
*/
XMLPARSEAPI(int)
XML_SetParamEntityParsing(XML_Parser parser,
                          enum XML_ParamEntityParsing parsing);


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

/* Return the number of bytes in the current event.
   Returns 0 if the event is in an internal entity.
*/
XMLPARSEAPI(int)
XML_GetCurrentByteCount(XML_Parser parser);

/* If XML_CONTEXT_BYTES is defined, returns the input buffer, sets
   the integer pointed to by offset to the offset within this buffer
   of the current parse position, and sets the integer pointed to by size
   to the size of this buffer (the number of input bytes). Otherwise
   returns a NULL pointer. Also returns a NULL pointer if a parse isn't
   active.

   NOTE: The character pointer returned should not be used outside
   the handler that makes the call.
*/
XMLPARSEAPI(const char *)
XML_GetInputContext(XML_Parser parser,
                    int *offset,
                    int *size);

/* For backwards compatibility with previous versions. */
#define XML_GetErrorLineNumber   XML_GetCurrentLineNumber
#define XML_GetErrorColumnNumber XML_GetCurrentColumnNumber
#define XML_GetErrorByteIndex    XML_GetCurrentByteIndex

/* Frees the content model passed to the element declaration handler */
XMLPARSEAPI(void)
XML_FreeContentModel(XML_Parser parser, XML_Content *model);

/* Exposing the memory handling functions used in Expat */
XMLPARSEAPI(void *)
XML_MemMalloc(XML_Parser parser, size_t size);

XMLPARSEAPI(void *)
XML_MemRealloc(XML_Parser parser, void *ptr, size_t size);

XMLPARSEAPI(void)
XML_MemFree(XML_Parser parser, void *ptr);



/* Return a string containing the version number of this expat */
XMLPARSEAPI(const XML_LChar *)
XML_ExpatVersion(void);

typedef struct {
  int major;
  int minor;
  int micro;
} XML_Expat_Version;

/* Return an XML_Expat_Version structure containing numeric version
   number information for this version of expat.
*/
XMLPARSEAPI(XML_Expat_Version)
XML_ExpatVersionInfo(void);

/* Added in Expat 1.95.5. */
enum XML_FeatureEnum {
  XML_FEATURE_END = 0,
  XML_FEATURE_UNICODE,
  XML_FEATURE_UNICODE_WCHAR_T,
  XML_FEATURE_DTD,
  XML_FEATURE_CONTEXT_BYTES,
  XML_FEATURE_MIN_SIZE,
  XML_FEATURE_SIZEOF_XML_CHAR,
  XML_FEATURE_SIZEOF_XML_LCHAR
  /* Additional features must be added to the end of this enum. */
};

typedef struct {
  enum XML_FeatureEnum  feature;
  const XML_LChar       *name;
  long int              value;
} XML_Feature;

XMLPARSEAPI(const XML_Feature *)
XML_GetFeatureList(void);


/* Expat follows the GNU/Linux convention of odd number minor version for
   beta/development releases and even number minor version for stable
   releases. Micro is bumped with each release, and set to 0 with each
   change to major or minor version.
*/
#define XML_MAJOR_VERSION 1
#define XML_MINOR_VERSION 95
#define XML_MICRO_VERSION 8

#ifdef __cplusplus
}
#endif

#endif /* not XmlParse_INCLUDED */
