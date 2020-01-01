
#ifndef __PARSER_XML_H__
#define __PARSER_XML_H__

#include <ncc_types.h>
#include <expat_interface.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef T_Parser_Status T_XmlParser_Status;

void* fnDBP_XMLCreateParserCtxt(T_Parser_DescPtr parserDesc, int8_t *encoding, void *userData);

T_XmlParser_Status fnDBP_XMLParseChunk(XML_Parser parser,
                            uint8_t *data,
                            int32_t size,
                            int32_t terminate);

#ifdef __cplusplus
}
#endif

#endif /* __PARSER_XML_H__ */
