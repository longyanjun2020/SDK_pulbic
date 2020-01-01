
/**
 * html_parserio.h : interface for the I/O interfaces used by the parser
 */

#ifndef __HTML_PARSERIO_H__
#define __HTML_PARSERIO_H__

#include <ncc_types.h>
#include <html_parserbuffer.h>
#include <html_encoding.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef struct _xmlParserInputBuffer xmlParserInputBuffer;
typedef xmlParserInputBuffer *xmlParserInputBufferPtr;
struct _xmlParserInputBuffer {
    void*                  context;

    htmlCharEncodingHandler encoder; /**< I18N conversions to UTF-8 */
    xmlBufferPtr buffer;    /**< Local buffer encoded in UTF-8 */
    xmlBufferPtr raw;       /**< if encoder != NULL buffer for raw input */
};

/**
 * Interfaces for input
 */
xmlParserInputBufferPtr
xmlAllocParserInputBuffer(void *ctxt);

int32_t
xmlParserInputBufferPush(void *ctxt, int32_t len, const uint8_t *buf);

void
xmlFreeParserInputBuffer(void *ctxt, xmlParserInputBufferPtr in);

#ifdef __cplusplus
}
#endif

#endif /* __HTML_PARSERIO_H__ */
