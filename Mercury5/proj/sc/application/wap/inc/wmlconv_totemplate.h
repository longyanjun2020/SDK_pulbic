
#ifndef __WMLCONV_TOTEMPLATE_H__
#define __WMLCONV_TOTEMPLATE_H__

#include <wmlconv_tohtml.h>

#define TEMPLATE_BEGIN 1
#define TEMPLATE_END   2

/*To process the the attrs and element of template's, and save them*/
void fnDBT_ProcessTemplate(wmlTransContext *ctx, T_DBT_StackNode *tempNode);

/**
 * process the start tag in template
 * \param ctx the handle
 * \param node the current node in template
 */
void fnDBT_ProcessTemplateStartTag(wmlTransContext *ctx, T_DBT_StackNodePtr node);

/**
 *  process the end tag in template, there are two things we will do in this function.
 * 1.push end tag onto stack excluding it included in start TAG_DO which has the same
 *   name of do existed.
 * 2.if the end tag is do or on event, we will process the block of it. and append
 *    the processed node on the templateNode chain list
 * \param ctx the handle
 * \param node the current node in template
 */
void fnDBT_ProcessTemplateEndTag(wmlTransContext *ctx, T_DBT_StackNodePtr node);

/**
 * Match do element in template, if template contain the same do element,
 * remove it from template data.
 * \param ctx the handle
 * \param attrs the attributes of do element
 */
void fnDBT_MatchDoTag(wmlTransContext *ctx, const uint8_t **attrs);

/*get the name of Tag_do for shadow*/
uint8_t * fnDBT_CombineDoNameTypetoName(const uint8_t **attrs);

/**
 *  get the name attr of do tag. to find out whether there is a
 * templateNode with the same name of the param-node
 * \param ctx the handle
 * \param node the current node of do tag
 * \return if there is a name the same as the name of node,return NULL, otherwise return the name
 */
uint8_t * fnDBT_GetDoTagName(wmlTransContext *ctx, const uint8_t **attrs);

/*Append a template node into template chain list.*/
void fnDBT_templateNodeAppend(wmlTransContext *ctx, T_DBT_TemplateDoNodePtr appendNode);

/*add the HTML info of TAG_DO in the last node of templatNode chain list.*/
void fnDBT_templateNodeAddInfo(T_DBT_TemplateDoNodePtr head,T_DBT_ElementDataPtr doHtmlEle);

/*Malloc template node and initialize it.*/
T_DBT_TemplateDoNodePtr fnDBT_CreateTemplateNode(void);

/*free the template list chain*/
void fnDBT_templateDataFree(T_DBT_TemplateDoNodePtr cur);

#endif  /*  __WMLCONV_TOTEMPLATE_H__ */
