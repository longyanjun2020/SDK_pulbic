
#ifndef __PARSER_SAXHANDLERS_H__
#define __PARSER_SAXHANDLERS_H__

#include <ncc_types.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * universal sax handlers structure design
 */

/* content handlers declaration */

/**
 * startDocumentSAXHandler:
 * @ctx:  the user data (XML parser context)
 *
 * Called when the document start being processed.
 */
typedef void (*startDocumentSAXHandler)(void *ctx);

/**
 * endDocumentSAXHandler:
 * @ctx:  the user data (XML parser context)
 *
 * Called when the document end has been detected.
 */
typedef void (*endDocumentSAXHandler)(void *ctx);

/**
 * startElementSAXHandler:
 * @ctx:  the user data (XML parser context)
 * @name:  The element name, including namespace prefix
 * @atts:  An array of name/value attributes pairs, NULL terminated
 *
 * Called when an opening tag has been processed.
 */
typedef void (*startElementSAXHandler)(void *ctx, const uint8_t *name, const uint8_t **atts);
/**
 * endElementSAXHandler:
 * @ctx:  the user data (XML parser context)
 * @name:  The element name
 *
 * Called when the end of an element has been detected.
 */
typedef void (*endElementSAXHandler)(void *ctx,const uint8_t *name);

/**
 * charactersSAXHandler:
 * @ctx:  the user data (XML parser context)
 * @ch:  a uint8_t string
 * @len: the number of uint8_t
 *
 * Receiving some chars from the parser.
 */
typedef void (*charactersSAXHandler)( void *ctx,
                                      const uint8_t *ch,
                                      int32_t len);

/**
 * get the document encoding bytes stream by Unicode value
 * \param    ctx  the user data (parser context)
 * \param    unicodeVal  the Unicode value of int8_t reference or predefined entity reference
 * \param    the bytes stream of document encoding corresponding with Unicode value
 * \param    the length of bytes stream
 */
typedef void (*referenceSAXHandler)( void *ctx,
                                     int16_t unicodeVal,
                                     uint8_t *docBytess,
                                     int32_t *bytesLen);

/**
 * cdata section handler
*/
typedef void (*startCdataSectionSAXHandler)(void *ctx);
typedef void (*endCdataSectionSAXHandler)(void *ctx);

typedef void (*cdataBlockSAXHandler)(void *ctx, const uint8_t *value, int32_t len);

/**
 * processingInstructionSAXHandler:
 * @ctx:  the user data (XML parser context)
 * @target:  the target name
 * @data: the PI data's
 *
 * A processing instruction has been parsed.
 */
typedef void (*processingInstructionSAXHandler)(void *ctx,
                                                const uint8_t *target,
                                                const uint8_t *data);
/**
 * commentSAXHandler:
 * @ctx:  the user data (XML parser context)
 * @value:  the comment content
 *
 * A comment has been parsed.
 */
typedef void (*commentSAXHandler)(void *ctx, const uint8_t *value);

/**
 * ignorableWhitespaceSAXHandler:
 * @ctx:  the user data (XML parser context)
 * @ch:  a uint8_t string
 * @len: the number of uint8_t
 *
 * Receiving some ignorable whitespaces from the parser.
 * UNUSED: by default the DOM building will use characters.
 */
typedef void (*ignorableWhitespaceSAXHandler)( void *ctx,
                                               const uint8_t *ch,
                                               int32_t len);

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
typedef void (*skippedEntitySAXHandler)(void *userData,
                                        const uint8_t *entityName,
                                        int32_t is_parameter_entity);

/**
 * Error Handlers
*/

/**
 * warningSAXHandler:
 * @ctx:  an XML parser context
 * @msg:  the message to display/transmit
 * @...:  extra parameters for the message display
 *
 * Display and format a warning messages, callback.
 */
typedef void (*warningSAXHandler)(void *ctx,
                                  const uint8_t *msg, ...);

/**
 * errorSAXHandler:
 * @ctx:  an XML parser context
 * @msg:  the message to display/transmit
 * @...:  extra parameters for the message display
 *
 * Display and format an error messages, callback.
 */
typedef void (*errorSAXHandler)(void *ctx,
                                const uint8_t *msg, ...);

/**
 * fatalErrorSAXHandler:
 * @ctx:  an XML parser context
 * @msg:  the message to display/transmit
 * @...:  extra parameters for the message display
 *
 * Display and format fatal error messages, callback.
 * Note: so far fatalError() SAX callbacks are not used, error()
 *       get all the callbacks for errors.
 */
typedef void (*fatalErrorSAXHandler)(void *ctx, const uint8_t *msg, ...);

/**
 * lexical handlers declaration
 */

/**
 * This is called for the start of the DOCTYPE declaration, before any DTD
 * or internal subset is parsed.
 * internalSubsetSAXHandler:
 * @ctx:  the user data (XML parser context)
 * @name:  the root element name
 * @ExternalID:  the external ID
 * @SystemID:  the SYSTEM ID (e.g. filename or URL)
 * @has_internal_subset
 *
 */
typedef void (*startDoctypeDeclSAXHandler)( void *userData,
                                            const uint8_t *doctypeName,
                                            const uint8_t *sysid,
                                            const uint8_t *pubid,
                                            int32_t has_internal_subset);

/**
 *  This is called for the start of the DOCTYPE declaration when the
 *  closing > is encountered, but after processing any external
 *  subset.
*/
typedef void (*endDoctypeDeclSAXHandler)(void *userData);

/**
 * The XML declaration handler is called for *both* XML declarations
 * and text declarations. The way to distinguish is that the version
 * parameter will be NULL for text declarations. The encoding
 * parameter may be NULL for XML declarations. The standalone
 * parameter will be -1, 0, or 1 indicating respectively that there
 * was no standalone parameter in the declaration, that it was given
 * as no, or that it was given as yes.
*/
typedef void (*xmlDeclSAXHandler)( void          *userData,
                                   const uint8_t *version,
                                   const uint8_t *encoding,
                                   int32_t       standalone);

enum Parser_XML_Content_Type {
  XML_CTYPE_EMPTY = 1,
  XML_CTYPE_ANY,
  XML_CTYPE_MIXED,
  XML_CTYPE_NAME,
  XML_CTYPE_CHOICE,
  XML_CTYPE_SEQ
};

enum Parser_XML_Content_Quant {
  XML_CQUANT_NONE,
  XML_CQUANT_OPT,
  XML_CQUANT_REP,
  XML_CQUANT_PLUS
};

/* If type == XML_CTYPE_EMPTY or XML_CTYPE_ANY, then quant will be
   XML_CQUANT_NONE, and the other fields will be zero or NULL.
   If type == XML_CTYPE_MIXED, then quant will be NONE or REP and
   numchildren will contain number of elements that may be mixed in
   and children point to an array of Parser_XML_Content cells that will be
   all of XML_CTYPE_NAME type with no quantification.

   If type == XML_CTYPE_NAME, then the name points to the name, and
   the numchildren field will be zero and children will be NULL. The
   quant fields indicates any quantifiers placed on the name.

   CHOICE and SEQ will have name NULL, the number of children in
   numchildren and children will point, recursively, to an array
   of Parser_XML_Content cells.

   The EMPTY, ANY, and MIXED types will only occur at top level.
*/

typedef struct Parser_XML_cp Parser_XML_Content;

struct Parser_XML_cp {
  enum Parser_XML_Content_Type  type;
  enum Parser_XML_Content_Quant quant;
  uint8_t                       *name;
  uint32_t                      numchildren;
  Parser_XML_Content            *children;
};

/* This is called for an element declaration. See above for
   description of the model argument. It's the caller's responsibility
   to free model when finished with it.
*/
typedef void (*elementDeclSAXHandler)( void *userData,
                                       const uint8_t *name,
                                       Parser_XML_Content    *model);

/* The Attlist declaration handler is called for *each* attribute. So
   a single Attlist declaration with multiple attributes declared will
   generate multiple calls to this handler. The "default" parameter
   may be NULL in the case of the "#IMPLIED" or "#REQUIRED"
   keyword. The "isrequired" parameter will be true and the default
   value will be NULL in the case of "#REQUIRED". If "isrequired" is
   true and default is non-NULL, then this is a "#FIXED" default.
*/
typedef void (*attlistDeclSAXHandler)( void           *userData,
                                       const uint8_t  *elname,
                                       const uint8_t  *attname,
                                       const uint8_t  *att_type,
                                       const uint8_t  *dflt,
                                       int32_t        isrequired);

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
typedef void (*entityDeclSAXHandler)( void *userData,
                                      const uint8_t *entityName,
                                      int32_t is_parameter_entity,
                                      const uint8_t *value,
                                      int32_t value_length,
                                      const uint8_t *base,
                                      const uint8_t *systemId,
                                      const uint8_t *publicId,
                                      const uint8_t *notationName);

/* OBSOLETE -- OBSOLETE -- OBSOLETE
   This handler has been superceded by the EntityDeclHandler above.
   It is provided here for backward compatibility.

   This is called for a declaration of an unparsed (NDATA) entity.
   The base argument is whatever was set by XML_SetBase. The
   entityName, systemId and notationName arguments will never be
   NULL. The other arguments may be.
*/
typedef void (*unparsedEntitySAXDeclHandler)( void *userData,
                                              const uint8_t *entityName,
                                              const uint8_t *base,
                                              const uint8_t *systemId,
                                              const uint8_t *publicId,
                                              const uint8_t *notationName);

/* This is called for a declaration of notation.  The base argument is
   whatever was set by XML_SetBase. The notationName will never be
   NULL.  The other arguments can be.
*/
typedef void (*notationDeclSAXHandler)( void *userData,
                                        const uint8_t *notationName,
                                        const uint8_t *base,
                                        const uint8_t *systemId,
                                        const uint8_t *publicId);

/**
 * When namespace processing is enabled, these are called once for
 * each namespace declaration. The call to the start and end element
 * handlers occur between the calls to the start and end namespace
 * declaration handlers. For an xmlns attribute, prefix will be
 * NULL.  For an xmlns="" attribute, uri will be NULL.
*/
typedef void (*startNamespaceDeclSAXHandler)( void *userData,
                                              const uint8_t *prefix,
                                              const uint8_t *uri);

typedef void (*endNamespaceDeclSAXHandler)( void *userData,
                                            const uint8_t *prefix);

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
typedef int32_t (*externalEntitySAXRefHandler)( void*          parser,
                                                const uint8_t *context,
                                                const uint8_t *base,
                                                const uint8_t *systemId,
                                                const uint8_t *publicId);

typedef struct __common_sax_handlers__ {
    /*
     *universal content sax handlers
     */
    startDocumentSAXHandler startDocumentHandler; /**<start document sax handler*/
    endDocumentSAXHandler endDocumentHandler; /**<end document sax handler*/
    startElementSAXHandler startElementHandler; /**<start element sax handler*/
    endElementSAXHandler endElementHandler; /**<end element sax handler*/
    charactersSAXHandler charactersHandler;    /**<characters sax handler*/
    referenceSAXHandler  referenceHandler; /**<int8_t or predefined entity reference sax handler*/
    startCdataSectionSAXHandler startCdataSectionHandler; /**<start CDATA section sax handler*/
    endCdataSectionSAXHandler endCdataSectionHandler; /**<end CDATA section sax handler*/
    cdataBlockSAXHandler cdataSectionHandler; /**<CDATA section sax handler*/

    /* universal lexical handler */
    processingInstructionSAXHandler PIHandler; /**<PI sax handler*/
    commentSAXHandler comment; /**<comment sax handler*/

    /* items relative with concrete parser */
    skippedEntitySAXHandler skippedEntityHandler; /**<unrecognazed entity sax handler*/
    ignorableWhitespaceSAXHandler ignorableWhiteSpaceHandler; /**<ignorable whitespace sax handler*/

    /* declaration */
    startDoctypeDeclSAXHandler startDoctypeDeclHandler; /**<start doctype declaration sax handler*/
    endDoctypeDeclSAXHandler endDoctypeDeclHandler; /**<end doctype declaration sax handler*/
    xmlDeclSAXHandler xmlDeclhandler; /**<xml declaration sax handler*/

    elementDeclSAXHandler elementDeclHandler; /**<element declaration sax handler*/
    attlistDeclSAXHandler attlistDeclHandler; /**<attribute list declaration sax handler*/
    notationDeclSAXHandler notationDeclHandler; /**<notation declaration sax handler*/
    entityDeclSAXHandler entityDeclHandler; /**<entity declaration sax handler*/
    unparsedEntitySAXDeclHandler unparsedEntityDeclHandler; /**<unparsed entity declaration sax handler*/

    externalEntitySAXRefHandler externalEntityHandler; /**<external entity sax handler*/

    /* name space handlers */
    startNamespaceDeclSAXHandler startNamespaceHandler; /**<start namespace declaration sax handler*/
    endNamespaceDeclSAXHandler endNamespaceHandler; /**<end namespace declaration sax handler*/

    /* error handlers */
    warningSAXHandler warning; /**<warning sax handler*/
    errorSAXHandler error; /**<error sax hanlder*/
    fatalErrorSAXHandler fatalError; /**<fatal error sax handler*/
} T_Parser_CommonSaxHandlers;

typedef T_Parser_CommonSaxHandlers* T_Parser_CommonSaxHandlersPtr;

#ifdef __cplusplus
}
#endif

#endif /* __PARSER_SAXHANDLERS_H__ */

