
#ifndef __HTML_ENCODING_H__
#define __HTML_ENCODING_H__

#include <ncc_types.h>
#include <html_parserbuffer.h>
#include <nccport_i18n.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Take a block of chars in the original encoding and try to convert
 * it to an UTF-8 block of chars out.
 * \param out:  a pointer to an array of bytes to store the UTF-8 result
 * \param outlen:  the length of out buffer
 * \param in:  a pointer to an array of chars in the original encoding
 * \param inlen:  the length of in buffer
 *
 * \return <li>the number of bytes written
 *         <li>I18N_INVALID_PARAM if lack of space
 *         <li>I18N_FAILED if the transcoding failed.
 * \attention
 * The value of inlen after return is the number of octets consumed
 * if the return value is positive, else unpredictiable.
 * The value of outlen after return is the number of octets consumed.
 */
typedef int32_t (*htmlCharEncodingInputFunc)( void *ctxt,
                                              uint8_t *out,
                                              int32_t *outlen,
                                              const uint8_t *in,
                                              int32_t *inlen );


/**
 * Take a block of UTF-8 chars in and try to convert it to another
 * encoding.
 * \param out:  a pointer to an array of bytes to store the result
 * \param outlen:  the length of out buffer
 * \param in:  a pointer to an array of UTF-8 chars
 * \param inlen:  the length of in buffer
 *
 * \return <li>the number of bytes written
 *         <li>I18N_INVALID_PARAM if lack of space
 *         <li>I18N_FAILED if the transcoding failed.
 * \attention
 * The value of inlen after return is the number of octets consumed
 * if the return value is positive, else unpredictiable.
 * The value of outlen after return is the number of octets consumed.
 */
typedef int32_t (*htmlCharEncodingOutputFunc)( void *ctxt,
                                               uint8_t *out,
                                               int32_t *outlen,
                                               const uint8_t *in,
                                               int32_t *inlen );

typedef struct _htmlCharEncodingHandler htmlCharEncodingHandler;
typedef htmlCharEncodingHandler *htmlCharEncodingHandlerPtr;

struct _htmlCharEncodingHandler {
    int8_t                           *name;         /**<encoding name*/
    NCCPort_NccCharset_t                codePage;      /**<code page*/
    htmlCharEncodingInputFunc        inputFun;      /**<transcoder to utf-8*/
    htmlCharEncodingOutputFunc       outputFun;     /**<transcoder from utf-8*/
};

/**
 * \param out:  a pointer to an array of bytes to store the result
 * \param outlen:  the length of out
 * \param in:  a pointer to an array of UTF-8 chars
 * \param inlen:  the length of in in UTF-8 chars
 *
 * \return the number of bytes written, or -1 if lack of space.
 *     The value of *inlen after return is the number of octets consumed
 *     if the return value is positive, else unpredictable.
 */
int32_t
defaultinputFun( uint8_t *out,
                 int32_t *outlen,
                 const uint8_t *in,
                 int32_t *inlen );

/**
 * Init html input stream's encoder by encoding name.
 * \ctxt  current parser context pointer
 * \param encName:  document character encoding name
 *
 */
void
htmlInitInputEncoder( void *cxt,
                      const int8_t *encName );

/**
 * Encode raw buffer's content to utf-8 and add into ctxt->buf->buffer
 * when document encoding is detected by META or XML Declaration.
 * \ctxt  current parser context pointer
 * \param encName:  document character encoding name
 *
 * \return 1 if success, or
 *         -1 general error
 */
int32_t
htmlSwitchEncoding( void *ctxt,
                    const int8_t *encName );

/**
 * Encode raw buffer's content to utf-8 and add into ctxt->buf->buffer.
 * \ctxt  current parser context pointer
 * \param inputFun: char encoding transformation data structure
 * \param out an buffer for the output.
 * \param in an raw buffer for add
 *
 * \return the number of byte written if success, or
 *         -1 general error
 *         -2 if  failed
 */
int32_t
htmlPushRawBuffer( void *ctxt,
                   htmlCharEncodingHandlerPtr encoder,
                   xmlBufferPtr out,
                   xmlBufferPtr in );

#ifdef __cplusplus
}
#endif

#endif /* __HTML_ENCODING_H__ */
