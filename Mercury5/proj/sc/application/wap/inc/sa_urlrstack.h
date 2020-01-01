#ifndef _DBA_URLRSTACK_H_
#define _DBA_URLRSTACK_H_

#include <wap_struct.h>
#include <sa_mmanage.h>
#include <sa_urlhstack.h>

#define DBA_RECORDSTACK_DEEPTH     10

#ifdef __cplusplus
extern "C" {
#endif

//--- for Record ---
struct parseRCtxt{
    int8_t                  *base;      /**<base path of the page*/
    int8_t                  *title;     /**<title of the page*/
};
typedef struct parseRCtxt      T_DB_ParseRCtxt;
typedef T_DB_ParseRCtxt       *T_DB_ParseRCtxtPtr;

struct rStack{
    T_DB_ParseRCtxt stack[DBA_RECORDSTACK_DEEPTH+1]; /**< stack items, using additional 1 for buffer*/
    int32_t     bIsContextRotated;    
    int16_t         top;                    /**< top pointer of stack*/
};/**< the stack structure */

typedef struct rStack      T_DBA_RStack;
typedef T_DBA_RStack      *T_DBA_RStackPtr;

/**Push a record into record stack.
*   \return
*/
void fnDBA_RPush(void);

/**Remove a record from record stack.
*   \return
*/
void fnDBA_RPop(int8_t tPos);

/**Compare pURL with every element of record stack.
*   \return -1, if failed to find any.
*   \return i, if find i-th URL is the same with pURL.
*/
int16_t fnDBA_RCompare(int8_t* pURL);

/**Rotate context of top record stack (shell).
*   \return
*/
void fnDBA_RContextRotate(void);

/**Rotate context of top record stack (real api implementation).
*   \return
*/
void fnDBA_RContextRotateEx(T_DB_ParseCtxt *ctxt, T_DBA_RStack *pRStackPointer);

/**Empty record stack.
*   \return
*/
void fnDBA_REmpty(void);

/**unload the base and title of the node "nodePtr" in the record stack
*   \param nodePtr pointer to the node to be unloaded
*/
void fnDBA_UnLoadANodeR( T_DB_ParseRCtxtPtr nodePtr );

/**
 * Init record stack
 * \return
 */
int32_t NCCBrw_sa_rInit( void );

/**
 * Destoy record stack
 * \return
 */
void NCCBrw_sa_unLoadR( void );

/**
 * Return record pointer
 * \return
 */
T_DBA_RStackPtr NCCBrw_sa_getRecord(void);

/**Reset the history stack
*   \return
*/
void NCCBrw_sa_rReset( void );

/**
 * Initialize record stack by reading data from history.dat.
 */
int32_t NCCBrw_sa_initRecordDataToStack(int8_t *recordFilePath);

/**
 * Save record stack to history.dat.
 */
void NCCBrw_sa_saveRecordStackToData(int8_t *recordFilePath);

/**
 * Raise flag of protecting history.dat.
 */
void NCCBrw_sa_setToProtectRecordFile(void);


#ifdef __cplusplus
}
#endif

#endif /*_DBA_URLRSTACK_H_*/
