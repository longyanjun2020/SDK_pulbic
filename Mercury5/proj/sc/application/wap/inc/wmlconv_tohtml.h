
#ifndef __WMLCONV_TOHTML_H__
#define __WMLCONV_TOHTML_H__

#include <wap_service.h>
#include <parser_saxhandlers.h>
#include <nccparser.h>
#include <wmlconv_struct.h>

#define TCONVERTCTX(ctx)  ((wmlTransContext *)ctx)

#define CDATAMAXLEN         2048
#define VAR_LEN_STRING      23

#define PMODE_WRAP  0
#define PMODE_NOWRAP 1

#define META_WITH_ENCODING      1
#define META_WITH_FORWARD       2
#define META_WITH_BACKWARD      3
#define META_WITH_TIMER         4

#define ATTRIBUTE_ONPICK_LEN    3
#define ADD_A_ATTRIBUTE         2
#define META_ATTRIBUTES_NUMBER  5   /* http-equiv="content-type", content="content", the other attrs has no business with us */

#define ENCTYPE_INCRS_LEN       6   /* !!!!!! */
#define SET_VARS_INCRS_LEN          4   /* !!!! */
#define SET_A_VAR_INCRS_LEN         2   /* & = */
#define POSTFIELD_VARS_INCRS_LEN    2   /* !! */
#define POSTFIELD_A_VAR_INCRS_LEN   2   /* & = */

#define METHOD_GET                  3   /* get */
#define METHOD_POST                 4   /* post */

#define TRANS_WORKSTACK     1
#define HTMLNAME_STACK      2

#define STACKDEPTH_STEP     16
#define POINTER_INVALID     -1

#define ELEMENT_START 1   /* start element*/
#define ELEMENT_END   2   /* end element*/
#define ELEMENT_CDATA 3   /* PCDATA*/
#define ELEMENT_ERROR 4   /* error message*/

#define ATTRIBUTE_NOT_FOUND -1

#define NOT_CDATA_BLOCK  1
#define IS_CDATA_BLOCK   2

#define ALIGN_LEN       10

/*Get attributes array length*/
int16_t fnDBT_GetAttributesLength(const uint8_t **atts);

/*Copy attributes*/
uint8_t ** fnDBT_AttributesDup(const uint8_t **atts);

/*Free attributes resource*/
void fnDBT_FreeAttributes(uint8_t **atts);

/*process character*/
void fnDBT_ProcessCharacters(wmlTransContextPtr ctx);

/*Process tag card attributes, such as title, event attributes*/
void fnDBT_ProcessStartCardAttributes(wmlTransContext *ctx, const uint8_t **atts);

/*Create meta element with type*/
T_DBT_ElementData * fnDBT_CreateMetaElment(
                                           wmlTransContext *ctx,
                                           int16_t metaType,
                                           const uint8_t *content
                                           );

/*Combine two attributes array to one*/
uint8_t ** fnDBT_CombineAttributes(uint8_t ** attsto, uint8_t **attsfrom);

/*Combine url prefix and suffix to integrated url*/
uint8_t * fnDBT_CombineUrl(uint8_t *preUrl, uint8_t *sufUrl);

void fnDBT_TransAnchor(wmlTransContext *ctx);

/*Trans wml block data in work stack*/
T_DBT_ElementData * fnDBT_TransBlock(wmlTransContext *ctx);

/*initialize  stack, allocate space.*/
T_DBT_WorkStack * fnDBT_InitStack(int32_t type);

/*Push a node and its data into the  stack.*/
void  fnDBT_Push(T_DBT_WorkStack *stack, void * node);

/*Pop a node and its data from the  stack.*/
void * fnDBT_Pop(T_DBT_WorkStack *stack);

/*free stack node resource*/
void fnDBT_FreeStackNode(T_DBT_StackNode *node);

/*free html name node*/
void fnDBT_FreeHtmlNameNode(T_DBT_HtmlNameNode *node);

/*Destroy stack*/
void fnDBT_DestroyStack(T_DBT_WorkStack *stack);

/*Clear context*/
void fnDBT_Clear(wmlTransContext *ctx);

/*get the align of each columns of table.*/
void fnDBT_getTdAlign(uint8_t * tableAlign, int16_t column, uint8_t * align);

#endif /* __WMLCONV_TOHTML_H__ */
