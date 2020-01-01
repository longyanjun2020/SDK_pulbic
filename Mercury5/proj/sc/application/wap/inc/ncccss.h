
/**
 * @file
 * CSS2 parse and query.
 *
 * Service API exposed by css2 module
 *
 * <!-- #interface list begin -->
 * \section ncccss interface
 * -NCCBrw_css_createManager()
 * -NCCBrw_css_destroyManager()
 * -NCCBrw_css_parse()
 * -NCCBrw_css_parseInlineStyle()
 * -NCCBrw_SA_cssAssignCSSStyleToTag()
 * <!-- #interface list end -->
 */

#ifndef _NCC_CSS_H_
#define _NCC_CSS_H_

#ifdef __cplusplus
extern "C" {
#endif

#include <ncc_types.h>
#include <common_array.h>
#include <html_tag.h>
#include <css_value.h>
#include <css_sac.h>
#include <css_property.h>
#include <css_selector.h>
#include <css_ruleset.h>
#include <css_stylesheet.h>

/**
 * The type of the document which uses CSS.
 */
typedef enum _CSS_AttachDocType
{
    CSS_DOC_HTML,
    CSS_DOC_XML,
    CSS_DOC_UNKNOWN
} CSS_AttachDocType;

typedef struct _CSS_Manager CSS_Manager;

struct _CSS_Manager {
    SAC_Parser *sacParser;
    CSS_AttachDocType attachDocType;
    const CSS_StyleSheet *styleSheetRef;        /* For efficient use of style sheet. */
    CommonArray * propTable;                    /* property table to store the CSS_PropertyItem, which is used for save querying result */
};

/**
 * The source of CSS.
 */
typedef enum _CSS_SourceType
{
    CSS_SOURCE_GLOBAL,         /**< style sheet in \<style\> tag. */
    CSS_SOURCE_LINK,           /**< style sheet included by \<link\> tag. */
    CSS_SOURCE_IMPORT,         /**< style sheet included by import rule in a style sheet. */
    CSS_SOURCE_DEFAULT,        /**< style sheet used by browser by default */
    CSS_SOURCE_USER_SPECIFIED, /**< user specified style sheet */
    CSS_SOURCE_UNKNOWN         /**< unknown source */
} CSS_SourceType;

#define CSS_SET_PSEUDO_FIRSTCHILD(a)    ((a) |= 0x00000001)
#define CSS_SET_PSEUDO_LINK(a)          ((a) |= 0x00000002)
#define CSS_SET_PSEUDO_VISITED(a)       ((a) |= 0x00000004)
#define CSS_SET_PSEUDO_HOVER(a)         ((a) |= 0x00000008)
#define CSS_SET_PSEUDO_ACTIVE(a)        ((a) |= 0x00000010)
#define CSS_SET_PSEUDO_FOCUS(a)         ((a) |= 0x00000020)
#define CSS_SET_PSEUDO_LANG(a)          ((a) |= 0x00000040)

const CommonArray * NCCBrw_css_parseInlineStyle(CSS_Manager * self,
                                        const int8_t * cssContent);

/**
 * Create a new CSS manager.
 * \param docType The type of docment which uses CSS, such as HTML, XML etc.
 * \return
 *      the pointer of a new CSS handle if success
 *      NULL if fail
 */
CSS_Manager * NCCBrw_css_createManager(CSS_AttachDocType docType);

/**
 * Destroy a CSS manager.
 * \param self the handle to be destroyed
 * \return void
 */
void NCCBrw_css_destroyManager(CSS_Manager * self);

/**
 * Parse CSS rules which defined in tags \<style\> or \<link\> or import rule in AT rule.
 * \param self the handle of current CSS manager
 * \param cssContent the CSS style sheet content
 * \param len the length of the style sheet
 * \param srcType the source of CSS
 * \return
 *      TRUE if success
 *      FALSE if false
 */
int32_t NCCBrw_css_parse(CSS_Manager * self,
                    const int8_t * cssContent,
                    int32_t len,
                    CSS_SourceType srcType);

/**
 * set the handlers for parsing inline style
 * \param self, the ref to the CSS_Manager
 * \return void
 */
void NCCBrw_css_unsetInlineStyleHandlers(CSS_Manager * self);

/**
 * set the handlers for parsing inline style
 * \param self, the ref to the CSS_Manager
 * \return void
 */
void NCCBrw_css_setInlineStyleHandlers(CSS_Manager * self);

typedef enum _WapInputMatchType{
    WAP_INPUT_COMPLETE_MATCH,
    WAP_INPUT_PART_MATCH,
    WAP_INPUT_DONT_MATCH,
    WAP_INPUT_FORMAT_ERROR,
}WapInputMatchType;

/**
 * Check if the buffer match the require format.
 *
 * \param buffer the input string
 * \param format the require format
 *
 * \return
 *      WAP_INPUT_COMPLETE_MATCH    if complete matching.
 *      WAP_INPUT_PART_MATCH        if the context is matching but not complete.
 *      WAP_INPUT_DONT_MATCH        if not matching.
 *      WAP_INPUT_FORMAT_ERROR      if format error.
 */
int32_t NCCBrw_css_isValidWapInput(const int16_t * buffer, const int8_t * format);

#ifdef __cplusplus
}
#endif

#endif  /* _NCC_CSS_H_ */
