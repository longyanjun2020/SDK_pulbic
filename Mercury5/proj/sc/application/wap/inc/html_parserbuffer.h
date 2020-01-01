
/*
 * html_parserbuffer.h : describes the structures found in an tree resulting
 *          from an XML parsing.
 */

#ifndef __HTML_PARSERBUFFER_H__
#define __HTML_PARSERBUFFER_H__

#include <ncc_types.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * BAD_CAST:
 *
 * Macro to cast a string to an uint8_t * when one know its safe.
 */
#define BAD_CAST (uint8_t *)

/**
 * xmlBufferAllocationScheme:
 *
 * A buffer allocation scheme can be defined to either match exactly the
 * need or double it's allocated size each time it is found too small
 */
typedef enum {
    XML_BUFFER_ALLOC_DOUBLEIT,
    XML_BUFFER_ALLOC_EXACT
} xmlBufferAllocationScheme;

/**
 * xmlBuffer:
 *
 * A buffer structure
 */
typedef struct _xmlBuffer xmlBuffer;
typedef xmlBuffer *xmlBufferPtr;

struct _xmlBuffer {
    uint8_t *content;    /**< The buffer content UTF8 */
    int32_t use;         /**< The buffer size used */
    int32_t size;        /**< The buffer size */
    int32_t save;
    xmlBufferAllocationScheme alloc; /**< The realloc method */
};

/**
 * Handling Buffers.
 */
xmlBufferPtr
xmlBufferCreate(void *ctxt);

int32_t
xmlBufferResize(void *ctxt, xmlBufferPtr buf, uint32_t size);

void
xmlBufferFree(void *ctxt, xmlBufferPtr buf);

void
xmlBufferAdd(void *ctxt, xmlBufferPtr buf, const uint8_t *str, int32_t len);

int32_t
xmlBufferShrink(xmlBufferPtr buf, uint32_t len);

#ifdef __cplusplus
}
#endif

#endif /* __HTML_PARSERBUFFER_H__ */
