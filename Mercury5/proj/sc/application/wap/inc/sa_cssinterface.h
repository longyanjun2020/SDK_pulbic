
/**
 * @file
 * Interface For integration with Css Moudle
 */

#ifndef _DBA_CSSINTERFACE_H_
#define _DBA_CSSINTERFACE_H_

#include <ncc_types.h>
#include <wap_struct.h>

#ifdef __cplusplus
extern "C" {
#endif

#ifdef NCC_BROWSER_CSS2

#include <ncccss.h>
#include <sa_parsing_stack.h>

/**
 * Query for a style.
 * \param self the handle of current CSS manager
 * \param tagInfo the query parameters,including tag No.(tag name in xml),
 *        stack, id, class name, inline style and pseudo name
 * \return
 *      NULL for fail
 *      address of properties which are queried for success. Do not free anything returned.
 *      Every alloced resource will be freed in NCCBrw_css_destroyManager().
 */
 const CommonArray * NCCBrw_css_getTagStyle(CSS_Manager* self,
                                        HTMLTAG htmlTag,
                                        int8_t * idName,
                                        int8_t * className,
                                        int16_t  pseudo,
                                        MLParsing_Stack * stack,
                                        const int8_t* inlinestyle);

#endif /* for NCC_BROWSER_CSS2 */

#ifdef __cplusplus
}
#endif

#endif /*_DBA_CSSINTERFACE_H_*/
