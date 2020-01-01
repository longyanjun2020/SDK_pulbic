
#ifndef __CSS_FONT_VALUE_H__
#define __CSS_FONT_VALUE_H__

#ifdef __cplusplus
extern "C" {
#endif

#include <wap_struct.h>
#include <ncccss.h>
/**
 * compute css property to font size text attribute.
 * see 15.2.4 Font size
 */
typedef enum _ComputedFontSizeValueType{
    COMPUTED_FONT_INVALID_SIZE,
    COMPUTED_FONT_SIZE_XX_SMALL,
    COMPUTED_FONT_SIZE_X_SMALL,
    COMPUTED_FONT_SIZE_SMALL,
    COMPUTED_FONT_SIZE_MEDIUM,
    COMPUTED_FONT_SIZE_LARGE,
    COMPUTED_FONT_SIZE_X_LARGE,
    COMPUTED_FONT_SIZE_XX_LARGE,
}ComputedFontSizeValueType;

#ifdef NCC_BROWSER_CSS2

/**
 * convert the css property font size  to computed value
 *
 * \param prop the font property from css parser.
 * \param parent the parent node for compute relative value.
 *
 * \return computed font size
 */
void CSS_Property_setComputedFontSize(T_DB_ComnAttrPtr tagAttr, CSS_Property *prop, T_DBA_StackNode *parent);

/**
 * convert the css font style to computed value
 *
 * \param tagAttr the attribute of the tag
 * \param prop the font style property from css parser
 * \return void
 */
void CSS_Property_setComputedFontStyle(T_DB_ComnAttrPtr tagAttr, CSS_Property *prop);

/**
 * convert the css font weight  to computed value
 *
 * \param tagAttr the attribute of the tag
 * \param prop the font weight property from css parser
 * \param parent the stack node of the css parser
 * \return void
 */
void CSS_Property_setComputedFontWeight(T_DB_ComnAttrPtr tag, CSS_Property *prop, T_DBA_StackNode *parent);

/**
 * convert the css text align  to computed value
 *
 * \param tagAttr the attribute of the tag
 * \param prop the text align property from css parser
 * \param parent the stack node of the css parser
 * \return void
 */
void CSS_Property_setComputedTextAlign(T_DB_PNodePtr paraAttr, CSS_Property *prop);

/**
 * convert the css property style  to computed value
 *
 * \param tagAttr the attribute of the tag
 * \param prop the text indent property from css parser
 * \param parent the stack node of the css parser
 * \return void
 */
void CSS_Property_setComputedTextIndent(T_DB_TextNodePtr visualAttr, CSS_Property *prop, T_DBA_StackNode *parent);

/**
 * convert the css white space  to computed value
 *
 * \param tagAttr the attribute of the tag
 * \param prop the white space property from css parser
 * \param parent the stack node of the css parser
 * \return void
 */
void CSS_Property_setComputedWhiteSpace(T_DB_ComnAttrPtr textAttr, CSS_Property *prop);

/**
 * convert the css float style value  to computed value
 *
 * \param tagAttr the attribute of the tag
 * \param prop the float property from css parser
 * \param parent the stack node of the css parser
 * \return void
 */
void CSS_Property_setComputedFloat(T_DB_ComnAttrPtr textAttr, CSS_Property *prop);

/**
 * convert the css clear type value to computed value
 *
 * \param tagAttr the attribute of the tag
 * \param prop the clear property from css parser
 * \param parent the stack node of the css parser
 * \return void
 */
void CSS_Property_setComputedClear(BoxAttribute *boxAttr, CSS_Property *prop);

/**
 * convert the css width to computed value
 *
 * \param tagAttr the attribute of the tag
 * \param prop the width property from css parser
 * \param parent the stack node of the css parser
 * \return void
 */
void CSS_Property_setComputedWidth(BoxAttribute *boxAttr, CSS_Property *prop, T_DBA_StackNode *parent);

/**
 * convert the css height to computed value
 *
 * \param tagAttr the attribute of the tag
 * \param prop the height property from css parser
 * \param parent the stack node of the css parser
 * \return void
 */
void CSS_Property_setComputedHeight(BoxAttribute *boxAttr, CSS_Property *prop, T_DBA_StackNode *parent);

/**
 * convert the css display to computed value
 *
 * \param tagAttr the attribute of the tag
 * \param prop the display property from css parser
 * \param parent the stack node of the css parser
 * \return void
 */
void CSS_Property_setComputedDisplay(BoxAttribute *boxAttr, CSS_Property *prop);

/**
 * convert the css wap marquee style value to computed value
 *
 * \param tagAttr the attribute of the tag
 * \param prop the -wap-marquee-style property from css parser
 * \param parent the stack node of the css parser
 * \return void
 */
void CSS_Property_setComputedWapMarqueeStyle(BoxAttribute *boxAttr, CSS_Property *prop);

/**
 * convert the css wap marquee dir to computed value
 *
 * \param tagAttr the attribute of the tag
 * \param prop the -wap-marquee-dir property from css parser
 * \param parent the stack node of the css parser
 * \return void
 */
void CSS_Property_setComputedWapMarqueeDir(BoxAttribute *boxAttr, CSS_Property *prop);

/**
 * convert the css wap marquee loop value to computed value
 *
 * \param tagAttr the attribute of the tag
 * \param prop the -wap-marquee-loop property from css parser
 * \param parent the stack node of the css parser
 * \return void
 */
void CSS_Property_setComputedWapMarqueeLoop(BoxAttribute *boxAttr, CSS_Property *prop);

/**
 * convert the css wap input value to computed value
 *
 * \param tagAttr the attribute of the tag
 * \param prop the -wap-input-required property from css parser
 * \param parent the stack node of the css parser
 * \return void
 */
void CSS_Property_setComputedWapInputRequired(T_DB_FieldNodePtr fieldAttr, CSS_Property *prop);

/**
 * convert the css wap input value to computed value
 *
 * \param tagAttr the attribute of the tag
 * \param prop the -wap-input-format property from css parser
 * \param parent the stack node of the css parser
 * \return void
 */
void CSS_Property_setComputedWapInputFormat(T_DB_FieldNodePtr fieldAttr, CSS_Property *prop);

/**
 * convert the css margin value to computed value
 *
 * \param tagAttr the attribute of the tag
 * \param prop the margin property from css parser
 * \param parent the stack node of the css parser
 * \return void
 */
void CSS_Property_setComputedMargin(BoxAttribute *boxAttr, CSS_Property *prop, T_DBA_StackNode *parent);

/**
 * convert the css padding value to computed value
 *
 * \param tagAttr the attribute of the tag
 * \param prop the padding property from css parser
 * \param parent the stack node of the css parser
 * \return void
 */
void CSS_Property_setComputedPadding(BoxAttribute *boxAttr, CSS_Property *prop, T_DBA_StackNode *parent);

/**
 * convert the css list value to computed value
 *
 * \param attribute the destination for the computed value
 * \param prop the list property from css parser
 * \return void
 */
void CSS_Property_setComputedListStyleType(HTML_ListAttribute * attribute, const CSS_Property *prop);

/**
 * convert the css visibility value to computed value
 *
 * \param attribute the destination for the computed value
 * \param prop the visibility property from css parser
 * \return void
 */
void CSS_Property_setComputedVisibility(T_DB_TextNodePtr visualAttr, CSS_Property *prop, T_DBA_StackNode *parent);

/**
 * convert the css color value to computed value
 *
 * \param attribute the destination for the computed value
 * \param prop the visibility property from css parser
 * \return void
 */
void CSS_Property_setComputedColor(T_DB_ComnAttrPtr visualAttr, CSS_Property *prop, T_DBA_StackNode *parent);
//  void CSS_Property_setComputedColor(T_DB_TextNodePtr visualAttr, CSS_Property *prop, T_DBA_StackNode *parent);

#endif

#ifdef __cplusplus
}
#endif
#endif                          /* __CSS_FONT_VALUE_H__ */
