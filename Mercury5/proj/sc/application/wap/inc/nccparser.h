
/**
 * @file
 * Parser Interface Service Layer
 *
 * Service API exposed by the Parser Interface.
 *
 * <!-- #interface list begin -->
 * \section nccparser_interface Interface
 * - NCCBrw_parser_createContext()
 * - NCCBrw_parser_parseChunk()
 * - NCCBrw_parser_getParserStatus()
 * - NCCBrw_parser_pauseParser()
 * - NCCBrw_parser_resumeParser()
 * - NCCBrw_parser_saveParserBuffer()
 * - NCCBrw_parser_fetchParserBuffer()
 * - NCCBrw_parser_insertBuffer()
 * - NCCBrw_parser_submitInsertedBuffers()
 * <!-- #interface list end -->
 */

#ifndef __NCC_PARSER_H__
#define __NCC_PARSER_H__

#include <ncc_types.h>
#include <parser_saxhandlers.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Macro for debug of parser's interface module.
 */
#define COMMON_PARSER_DEBUG

/**
 * Flag indicating whether it is the last chunk.
 */
#define T_PARSER_IS_LAST_CHUNK
#define T_PARSER_NOT_LAST_CHUNK

/**
 * Document type such html, xhtml, wml, etc.
 */
typedef enum __doc_type__ {
    PARSER_HTML_DOC = 1,
    PARSER_WML_DOC,
    PARSER_XHTML_DOC,
}T_Parser_Doc_Type;

/**
 * Parser type such html parser, xml parser.
 */
typedef enum __parser_type {
    HTML_PARSER,    /**<html parser type*/
    XML_PARSER      /**<xml parser type*/
}T_Parser_Type;

/**
 * Malloc function declaration used by parser.
 */
typedef void*(*parserMalloc)(uint32_t size);

/**
 * Free function declaration used by parser.
 */
typedef void(*parserFree)(void *ptr);

/**
 * Realloc function declaration used by parser.
 */
typedef void*(*parserRealloc)(void *ptr, uint32_t size);

/**
 * Memory manage handler suite structure, include malloc, free, realloc.
 */
typedef struct {
  parserMalloc  malloc_fcn;  /**<malloc function pointer*/
  parserFree    free_fcn;     /**<free function pointer*/
  parserRealloc realloc_fcn; /**<realloc function pointer*/
} Parser_Memory_Handling_Suite;

/**
 * Parser description structure.
 */
struct __Parser_Desc__ {
    T_Parser_Type                parserType;    /**<the type of parser, such as HTML_PARSER*/
    T_Parser_CommonSaxHandlersPtr   SAXHandlers;    /**<common sax handlers*/
    Parser_Memory_Handling_Suite *pMemHandlers;  /**<memory handlers suite*/
};
typedef struct __Parser_Desc__ T_Parser_Desc;
typedef T_Parser_Desc*   T_Parser_DescPtr;


typedef struct __Parser_Context__ {
    T_Parser_Type parserType;    /**<the type of parser, such as HTML_PARSER*/
    Parser_Memory_Handling_Suite memHandlers;  /**<memory handlers suite*/
    void *parser;                /**<the parser context pointer*/
} T_Parser_Context;
typedef T_Parser_Context* T_Parser_ContextPtr;

typedef enum __Parser_Status__ {
    T_PARSER_ERROR = 0, /**<there is a error when parsing*/
    T_PARSER_OK = 1,    /**<parse chunk with no error*/
    T_PARSER_SUSPEND = 2,   /**<the parser is stopped*/
    T_PARSER_LAST_NOT_FINISH = 3,   /**<there are some unparsed data although this is the last chunk*/
    T_PARSER_FINISHED = 4   /**<there are some unparsed data although this is the last chunk*/
} T_Parser_Status;

/**Get parser description information by document type.
 * \param  docType        document type
 * \return parser description information pointer
 */
T_Parser_DescPtr
fnDB_GetParserDesc(T_Parser_Doc_Type docType);

/**Create a parser context.
 * \param parserDescPtr   document description pointer
 * \param encoding        document character encoding
 * \param defEncoding     default character encoding
 * \param userData        user data used by upper lanyer
 * \return                parser context pointer
 * \sa  NCCBrw_parser_parseChunk
 */
T_Parser_ContextPtr
NCCBrw_parser_createContext( T_Parser_DescPtr parserDescPtr,
                          int8_t *encoding,
                          int8_t *defEncoding,
                          void   *userData );

/**Parse a chunk of document.
 * \param ctxt            parser context pointer
 * \param data            the first block of data for parse
 * \param size            the data length in bytes
 * \param finalFlag        a flag indicating whether this is the last chunk to parse
 *
 * \return    T_Parser_Status 0: error 1: success 2: suspend
 * \sa  NCCBrw_parser_createContext
 */
T_Parser_Status
NCCBrw_parser_parseChunk( T_Parser_ContextPtr ctxt,
                       uint8_t *data,
                       int32_t size,
                       int32_t finalFlag );

/**
 * Get current status of the parser.
 * \param ctxt            parser context it can not be null
 * \return                T_Parser_Status
 * \sa  NCCBrw_parser_createContext
 */
T_Parser_Status
NCCBrw_parser_getParserStatus(T_Parser_ContextPtr ctxt);

/**
 * Pause procession on parsing.
 * \param ctxt            parser context it can not be null
 * \return                T_Parser_Status
 * \sa  NCCBrw_parser_resumeParser
 */
T_Parser_Status
NCCBrw_parser_pauseParser(T_Parser_ContextPtr ctxt);

/**
 * Create a parser context.
 * \param ctxt            parser context it can not be null
 * \return                T_Parser_Status
 * \sa fnDBP_StopParser
 */
T_Parser_Status
NCCBrw_parser_resumeParser(T_Parser_ContextPtr ctxt);

/**
 * Conserve unparsed data of parser to parse later. after this operation,
 * the parser can receive new data to parse. it is mainly used iFrame or Frame.
 * \param ctxt            parser context it can not be null
 * \return                T_Parser_Status
 * \sa  NCCBrw_parser_pauseParser
 */
T_Parser_Status
NCCBrw_parser_saveParserBuffer(T_Parser_ContextPtr ctxt);

/**
 * Get conserved data of parser and be ready to parse again. after this operation,
 * it is mainly used iFrame or Frame.
 * \param ctxt            parser context it can not be null
 * \return                T_Parser_Status
 * \sa fnDBP_StopParser
 */
T_Parser_Status
NCCBrw_parser_fetchParserBuffer(T_Parser_ContextPtr ctxt);

/**
 * Insert some data into parser, mainly used for document.write() of JS.
 * \param   ctxt    parser context it can not be null
 * \param   data    the data to insert
 * \param   size    the length of data
 * \return  T_Parser_Status
 */
T_Parser_Status
NCCBrw_parser_insertBuffer(T_Parser_ContextPtr ctxt, const uint8_t *data, int32_t size);

/**
 * Submit inserted buffers to parser and start parsing them,
 * mainly used for after document.write() of JS.
 * \param   ctxt    parser context it can not be null
 * \return  void
 */
void
NCCBrw_parser_submitInsertedBuffers(T_Parser_ContextPtr ctxt);

#ifdef __cplusplus
}
#endif

#endif /* __NCC_PARSER_H__ */
