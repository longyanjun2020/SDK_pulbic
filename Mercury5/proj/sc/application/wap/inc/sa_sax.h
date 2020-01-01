#ifndef __SA_SAX_H__
#define __SA_SAX_H__

#define T_DBA_SAX_DEBUG 0

#if T_DBA_SAX_DEBUG
#define ONLY_TAG_MATCH_DEBUG 0

#define SAX_OPEN()   parser_sax_debug_open()
#define SAX_CLOSE()  parser_sax_debug_close()
#define SAX_END_ELEMENT_DEBUG(name) parser_sax_debug_end_element(name)
#define SAX_START_ELEMENT_DEBUG(name, atts) parser_sax_debug_start_element(name, atts)
#define SAX_CHARACTERS_DEBUG(ch, len) parser_sax_debug_characters(ch, len)
#define SAX_CDATA_DEBUG(cdata, len)   parser_sax_debug_cdata(cdata, len)
#else /* T_DBA_SAX_DEBUG */
#define SAX_OPEN()
#define SAX_CLOSE()
#define SAX_END_ELEMENT_DEBUG(name)
#define SAX_START_ELEMENT_DEBUG(name, atts)
#define SAX_CHARACTERS_DEBUG(ch)
#define SAX_CDATA_DEBUG(cdata)
#endif /* T_DBA_SAX_DEBUG */

#endif /* __SA_SAX_H__ */
