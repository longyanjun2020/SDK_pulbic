
#ifndef __PARSER_HTML_H__
#define __PARSER_HTML_H__

#include <ncc_types.h>
#include <nccparser.h>
#include <ncchtml.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef T_Parser_Status T_HtmlParser_Status;

void*
fnDBP_htmlCreateParserCtxt(T_Parser_DescPtr parserDesc, int8_t *encoding, int8_t *defEncoding);

T_HtmlParser_Status
fnDBP_htmlParseChunk(htmlParserCtxtPtr ctxt,
                     uint8_t *data,
                     int32_t size,
                     int32_t terminate);

#ifdef __cplusplus
}
#endif

#endif /* __PARSER_HTML_H__ */
