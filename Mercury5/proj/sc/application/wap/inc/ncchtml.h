
/**
 * @file
 * HTML Parser Service Layer
 *
 * Service API exposed by the HTML Parser.
 *
 * <!-- #interface list begin -->
 * \section ncchtml Interface
 * - NCCBrw_html_createPushParserCtxt()
 * - NCCBrw_html_freeParserContext()
 * - NCCBrw_html_parseChunk()
 * - NCCBrw_html_insertBuffer()
 * - NCCBrw_html_submitInsertedBuffers()
 * - NCCBrw_html_saveParserBuffer()
 * - NCCBrw_html_fetchParserBuffer()
 * - NCCBrw_html_pauseParser()
 * - NCCBrw_html_resumeParser()
 * <!-- #interface list end -->
 */

#ifndef __NCC_HTML_H__
#define __NCC_HTML_H__

#include <ncc_types.h>
#include <wap_config.h>
#include <html_parsersaxhandlers.h>
#include <html_parsermemory.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Max number of bytes to look up encoding infomation
 */
#define HTML_ENCODING_LOOUP_DEEP 8192

#ifndef T_HTML_INTERNAL
typedef void* htmlParserCtxtPtr;
typedef int32_t xmlCharEncoding;
#endif

struct __htmlParserCtxt__;
typedef struct __htmlParserCtxt__ htmlParserCtx;

typedef enum __Html_Parser_Status__ {
    T_HTML_PARSER_ERROR = 0, /**<there is a error when parsing*/
    T_HTML_PARSER_OK = 1,    /**<parse chunk with no error*/
    T_HTML_PARSER_SUSPENDED = 2,   /**<the parser is stopped*/
    T_HTML_PARSER_LAST_NOT_FINISHED = 3,   /**<there are some unparsed data although this is the last chunk*/
    T_HTML_PARSER_FINISHED = 4   /**<there are some unparsed data although this is the last chunk*/
} T_HTML_Parser_Status;

/**
 * create parser context
 * \param sax            sax handler
 * \param user_data      user data
 * \param chunk          chuck buffer
 * \param size           size of chuck
 * \param pMemHandlers   parser memory handling suite
 * \param charEncoding   char encoding
 * \return               parser context
 * \sa
 */
htmlParserCtxtPtr
 NCCBrw_html_createPushParserCtxt( htmlSAXHandlerPtr sax,
                              void *user_data,
                              const int8_t *chunk,
                              int32_t size,
                              T_Html_Parser_Memory_Handling_Suite *pMemHandlers,
                              int8_t *charEncoding,
                              int8_t *defEncoding);

/**
 * free parser context
 * \param ctxt            parser context pointer
 * \return                void
 * \sa  NCCBrw_parser_parseChunk  NCCBrw_parser_createContext
 */
void
 NCCBrw_html_freeParserContext(htmlParserCtxtPtr ctxt);

/**
 * parser chunk
 * \param ctxt            parser context pointer
 * \param chunk           chunk buffer
 * \param size            size of chunk
 * \param terminate       if the last block
 * \return                parser status
 * \sa
 */
T_HTML_Parser_Status
 NCCBrw_html_parseChunk( htmlParserCtxtPtr ctxt,
                    const int8_t *chunk,
                    int32_t size,
                    int32_t terminate );

/**
 * parser chunk
 * \param ctxt            parser context pointer
 * \param data            data buffer
 * \param size            size of chunk
 * \return                parser status
 * \sa
 */
T_HTML_Parser_Status
 NCCBrw_html_insertBuffer(htmlParserCtxtPtr ctxt, const uint8_t *data, int32_t size);

/**
 * submit inserted buffers to html parser and start parsing them,
 * mainly used for after document.write() of JS
 * \param   ctxt    html parser context it can not be null
 * \return  T_HtmlParser_Status
 */
void
 NCCBrw_html_submitInsertedBuffers(htmlParserCtxtPtr ctxt);

/**
 * save the buffers
 * \param   ctxt    html parser context it can not be null
 * \return  T_HtmlParser_Status
 */
T_HTML_Parser_Status
 NCCBrw_html_saveParserBuffer(htmlParserCtxtPtr ctxt);

/**
 * fetch the buffers
 * \param   ctxt    html parser context it can not be null
 * \return  T_HtmlParser_Status
 */
T_HTML_Parser_Status
 NCCBrw_html_fetchParserBuffer(htmlParserCtxtPtr ctxt);

/**
 * pause procession on parsing
 * \param ctxt            html parser context
 * \return                T_HTML_Parser_Status
 * \sa  NCCBrw_parser_resumeParser
 */
T_HTML_Parser_Status
 NCCBrw_html_pauseParser(htmlParserCtxtPtr ctxt);

/**
 * create a parser context
 * \param ctxt            html parser context
 * \return                T_HTML_Parser_Status
 * \sa  NCCBrw_html_pauseParser
 */
T_HTML_Parser_Status
 NCCBrw_html_resumeParser(htmlParserCtxtPtr ctxt);

#ifdef __cplusplus
}
#endif

#endif /* __NCC_HTML_H__ */
