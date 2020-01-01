

/**
 * @file
 *  History stack management
 */


#ifndef _DBA_URLHSTACK_H_
#define _DBA_URLHSTACK_H_

#include <wap_struct.h>
#include <sa_mmanage.h>

/** length of the history page stack */
#define DBA_URLSTACK_DEEPTH     12

#ifdef __cplusplus
extern "C" {
#endif

struct hNode{
    T_DB_ParseCtxtPtr      ctxt;            /**< Page context */
    T_DBA_BrowserMMPtr      src;            /**< BMM context of browser*/
    int8_t      *URI;                       /**< origin url address*/
    int8_t      *postData;                  /**< post data*/
    int8_t      *contentType;               /**< content type of post data*/
    int32_t     postDataLen;                /**< length of post data*/
    int32_t     yPos;                       /**< y pos of this page*/
    int32_t     height;                     /**< height of this page*/
    uint8_t     fontSize;                   /**< font size*/
};/**< the stack item structure */

typedef struct hNode       T_DBA_HNode;
typedef T_DBA_HNode       *T_DBA_HNodePtr;

struct hStack{
    T_DBA_HNode stack[DBA_URLSTACK_DEEPTH]; /**< stack items*/
    int8_t      *URI;                       /**< origin url address*/
    int8_t      *postData;                  /**< post data*/
    int8_t      *contentType;               /**< content type of post data*/
    int32_t     postDataLen;                /**< length of post data*/
    int16_t         top;                    /**< top pointer of stack*/
    int16_t     bottom;                     /**< bottom pointer of stack*/
    int16_t         cur;                    /**< cur pointer of stack*/
    int8_t      isRefreshPage;              /**< if refresh the current page*/
    int8_t      isNeedReDisplay;            /**< if need redisplay current page*/
    uint8_t     fontSize;                   /**< font size*/
};/**< the stack structure */

typedef struct hStack      T_DBA_HStack;
typedef T_DBA_HStack      *T_DBA_HStackPtr;

/**Get the page we had explorer before current in history stack
*   \return
*/
int32_t  fnDBA_HPre(void);

/**Get the page we had explorer after current in history stack
*   \return
*/
int32_t  fnDBA_HNext(void);

/**Add current page  into history stack
*   \return
*/
void fnDBA_HPush(void);

/**Check the memory and close former pages if need
*   \return
*/
void fnDBA_HTrimMem(void);

/**Clear invalid pages
*   \return
*/
void fnDBA_HClearInvalid(void);

/**Clear data of current context if it is wml type.
*   \return
*/
void sa_UnloadMemOfCurNode(void);

#ifdef __cplusplus
}
#endif

#endif /*_DBA_URLHSTACK_H_*/
