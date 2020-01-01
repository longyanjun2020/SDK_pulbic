
#ifndef __HTML_PARSERSAXHANDLER_H__
#define __HTML_PARSERSAXHANDLER_H__

#include <ncc_types.h>
#include <parser_saxhandlers.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * When we include the commonSAXHanlders.h, we just
 * typedef html sax handler declaration as common sax handler declaration
 */
#ifdef __PARSER_SAXHANDLERS_H__
#define xmlDelcSAXFunc               xmlDeclSAXHandler
#define startDocumentSAXFunc         startDocumentSAXHandler
#define endDocumentSAXFunc           endDocumentSAXHandler
#define startElementSAXFunc          startElementSAXHandler
#define endElementSAXFunc            endElementSAXHandler
#define charactersSAXFunc            charactersSAXHandler
#define referenceSAXFunc             referenceSAXHandler
#define ignorableWhitespaceSAXFunc   ignorableWhitespaceSAXHandler
#define processingInstructionSAXFunc processingInstructionSAXHandler
#define commentSAXFunc               commentSAXHandler
#define cdataBlockSAXFunc            cdataBlockSAXHandler
#define warningSAXFunc               warningSAXHandler
#define errorSAXFunc                 errorSAXHandler
#define fatalErrorSAXFunc            fatalErrorSAXHandler
#else
typedef uint8_t uint8_t;

typedef void (*startDocumentSAXFunc)(void *ctx);

typedef void (*endDocumentSAXFunc)(void *ctx);

typedef void (*startElementSAXFunc)( void *ctx,
                                       const uint8_t *name,
                                       const uint8_t **atts );

typedef void (*endElementSAXFunc)(void *ctx, const uint8_t *name);

typedef void (*charactersSAXFunc)( void *ctx,
                                     const uint8_t *ch,
                                     int32_t len );

/**
 * get the document encoding bytes stream by Unicode value
 * \param    ctx  the user data (parser context)
 * \param    unicodeVal  the Unicode value of int8_t reference or
 *                       predefined entity reference
 * \param    docBytes    the bytes stream of document encoding corresponding with
 *                       Unicode value
 * \param    the length of bytes stream
 */
typedef void (*referenceSAXFunc)( void *ctx,
                                    int32_t unicodeVal,
                                    uint8_t *docBytes,
                                    int32_t *pBytesLen );

typedef void (*ignorableWhitespaceSAXFunc)( void *ctx,
                                              const uint8_t *ch,
                                              int32_t len );

typedef void (*processingInstructionSAXFunc)( void *ctx,
                                                const uint8_t *target,
                                                const uint8_t *data );

typedef void (*commentSAXFunc)(void *ctx, const uint8_t *value);

typedef void (*cdataBlockSAXFunc)( void *ctx,
                                     const uint8_t *value,
                                     int32_t len );

typedef void (*warningSAXFunc)(void *ctx, const int8_t *msg, ...);

typedef void (*errorSAXFunc)(void *ctx, const int8_t *msg, ...);

typedef void (*fatalErrorSAXFunc)(void *ctx, const int8_t *msg, ...);

#endif /* __PARSER_SAXHANDLERS_H__ */

typedef struct _htmlSAXHandler htmlSAXHandler;
typedef htmlSAXHandler *htmlSAXHandlerPtr;
struct _htmlSAXHandler
{
    startDocumentSAXFunc startDocument;
    endDocumentSAXFunc   endDocument;
    startElementSAXFunc  startElement;
    endElementSAXFunc    endElement;

    charactersSAXFunc characters;
    cdataBlockSAXFunc cdataBlock;
    referenceSAXFunc  reference;

    ignorableWhitespaceSAXFunc   ignorableWhitespace;
    processingInstructionSAXFunc processingInstruction;
    commentSAXFunc comment;

    xmlDelcSAXFunc xmlDeclHandler;

    warningSAXFunc warning;
    errorSAXFunc error;
    fatalErrorSAXFunc fatalError;
};

#ifdef __cplusplus
}
#endif

#endif /* __HTML_PARSERSAXHANDLER_H__ */
