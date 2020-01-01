
/**
 * @file
 *  browser stack management
 */

#ifndef _DBA_ANALYSISSTACK_
#define _DBA_ANALYSISSTACK_

#include <ncc_types.h>
#include <wap_struct.h>
#include <sa_tagattrlists.h>
#include <wap_config.h>

/** Defining the node state */
#define  DBA_PARSE_IN_DOCUMENT         0
#define  DBA_PARSE_IN_A                1
#define  DBA_PARSE_IN_TABLE            2
#define  DBA_PARSE_IN_FORM             3
#define  DBA_PARSE_IN_LIST             4
#define  DBA_PARSE_IN_P                5
#define  DBA_PARSE_IN_OPTION           6
#define  DBA_PARSE_IN_BODY             7
#define  DBA_PARSE_IN_HTML             8
#define  DBA_PARSE_IN_HEAD             9
#define  DBA_PARSE_IN_CAPTION          10
#define  DBA_PARSE_IN_TEXTAREA         11
#define  DBA_PARSE_IN_VIRTUAL_TABLE    12
#define  DBA_PARSE_IN_TITLE            13
#define  DBA_PARSE_IN_BUTTON           14
#define  DBA_PARSE_IN_MARQUEE          15

#ifdef __cplusplus
extern  "C" {
#endif

/**Defining the structs of analysis stack node data */
struct stackNode{
    void*               node;         /**<the content of node*/
    T_DBA_HTMLElement       element;      /**<element number */
    T_DB_ContentLinkIdx     posPtr;       /*the position of the stack element node in the analysis stack*/
    uint16_t                listNestLevels;
    int32_t                 state;        /**<parsing state*/
    struct{
        int16_t             clicked;
        int16_t             unclicked;
    }link;
    struct{
        int16_t             attr;
        uint16_t             len;
    }text;
    BoxAttribute            boxAttr;        /* The attribute of box, including padding, border, and margin. */
    T_DB_TextNode           visualAttr;     /**< the attr of text sach as text-indent */
    HTML_ListAttribute      listAttr;       /* The attribute of list, including list style */
#ifdef NCC_BROWSER_CSS2
    const int8_t *          className;
    const int8_t *          idName;
    int32_t                 inMarqee;       /**< TRUE--the following block is in maquee, else in none-marqee block */
    uint16_t                pseudo;
    uint16_t                unUsed;
#endif
};

typedef    struct stackNode           T_DBA_StackNode;
typedef    T_DBA_StackNode           *T_DBA_StackNodePtr;

/** Defining the structs of optgroup state*/
typedef struct _OptState{
    int8_t              isInOptGroup;       /**< If the option in group*/
    int8_t              isOptDisable;       /**< If optgroup is disable*/
    int16_t             unUsed;
    }T_OptState;

/**Defining the structs of analysis stack*/
struct analysisStack{
    T_DBA_StackNodePtr  data;
    int16_t             top;
    int16_t             pointer;
    int16_t             depth;
    int16_t             quotes;             /*count <q>*/
    int16_t             noScriptEnable;     /*if noscript enable*/
    int16_t             unUsed;
    T_OptState          optState;
};

typedef struct analysisStack           T_DBA_AnalysisStack;
typedef T_DBA_AnalysisStack           *T_DBA_AnalysisStackPtr;

/**Initiate the analysis stack
*set the default depth and other fields of the structure.
*/
void  fnDBA_StackInit( void );

/**Push a node and its data into the analysis stack
*   \param data   the node data we want to push into the stack
*/
void  fnDBA_Push(T_DBA_StackNode data );

/**Pop a node and its data from the analysis stack
*   \param  data   the node data we want to pop
*   \return <ul>
*           <li>TRUE, in case of success
*           <li>FALSE, in case of failure
*        </ul>
*/
int32_t fnDBA_Pop( T_DBA_StackNode* data );

/**
*Set current pointer to the top of the stack
*/
void fnDBA_TopMove(void);

/**
*Get the node pointer before current
*/
void fnDBA_PreMove(void);

/**
*Get the node pointer after current
*/
void fnDBA_NextMove(void);

/**Get node data from  current stack node
*   \param  data    the node data we want from stack
*   \return <ul>
*           <li>TRUE, in case of success
*           <li>FALSE, in case of failure
*        </ul>
*/
int32_t fnDBA_GetCurData( T_DBA_StackNode* data);

/**Get the top node infomation
*   \return  the top node in the stack
*/
T_DBA_StackNodePtr fnDBA_GetTop();

/**
 * Get a node at appointed position
 * \param index position of node
 * \return
 *      pointer to node if success
 *      NULL if failed
 */
T_DBA_StackNodePtr fnDBA_GetNodeAt(int32_t index);

/**
 * Get the size of stack
 * \param void
 * \return the size of stack
 */
int32_t fnDBA_GetStackSize();

/**Get the current node infomation
*   \return  the current node
*/
T_DBA_StackNodePtr fnDBA_GetCur( void );

/**
* To search the Element in stack from current element to stop element.
 * \param searchElmt The element to search.
 * \param stopElmt Stop search when meet stopElmt
 * \return If find, return pointer to the element, or NULL.
 */
T_DBA_StackNodePtr sa_searchElementInStack(T_DBA_HTMLElement searchElmt, T_DBA_HTMLElement stopElmt);

/**
 * To search the searchElmt in stack from current element to stopElmt,if success,pop elements untill searchElmt.
 * \param searchElmt    The element to search.
 * \param stopElmt      Stop search when meet stopElmt
 * \param node          The content of poped stack node
 * \return If find, return pointer to the element, or NULL.
 */
void sa_popElementsIfFound(T_DBA_HTMLElement searchElmt,T_DBA_HTMLElement stopElmt,T_DBA_StackNode *node);

/**
*Destroy the stack, this fuction must be called after function
*/
void fnDBA_Clear( void );

/**push and pop <q>
*  \param flag 1:push <q> 2:pop <q>
*/
void fnDBA_PushQuote(int32_t flag);

/**get current <q>
*  \return "'" or """
*/
int8_t* fnDBA_GetQuote(void);

/**set no script enable
*  \param enable 1:enabled 0: disabled
*/
void fnDBA_SetNoScriptEnable(int32_t enable);

/**if no script enable
*  \return 1:enabled 0: disabled
*/
int32_t fnDBA_GetNoScriptEnable(void);

/**
 *Get State of Optgroup when parsing
 * \param
 * \return State of Optgroup
 */
T_OptState * fnDBA_GetOptState(void);

/**
 *Clear State of Optgroup
 * \param
 * \return
 */
void fnDBA_ClearOptState(void);

#ifdef __cplusplus
}
#endif
#endif  /*_DBA_ANALYSISSTACK_*/
