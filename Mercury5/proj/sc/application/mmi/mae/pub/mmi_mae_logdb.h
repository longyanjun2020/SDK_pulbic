/**
 * @file mmi_mae_logdb.h
 * @brief   The document describes the interface of ILogdb
 * ILogdb represent system message(s) such as missing call,
 * unchecked alarm, battery status notification etc.
 *
 * @author  nick.chou@mstarsemi.com
 * @version $Id: mmi_mae_logdb.h 633 2009-04-15 06:08:09Z mark.yang $
 */
#ifndef __MMI_MAE_LOGDB_H__
#define __MMI_MAE_LOGDB_H__
/*-------------------------------------------------------------------------*/

#include "mmi_mae_common_def.h"
#include "mmi_mae_interface_def.h"
#include "mmi_mae_logdb_forward.h"

/**
 * ILogdb Interfaces
 */
#define INHERIT_ILogdb(IName) \
	INHERIT_IBase(IName); \
	u32 (*Init)		( IName *pILogdb, MAELogdb_t *cl ); \
	u32 (*MoveNext)	( IName *pILogdb ); \
	u32 (*MovePre)	( IName *pILogdb ); \
	u32 (*MoveLast)	( IName *pILogdb ); \
	u32 (*MoveFirst)( IName *pILogdb ); \
    u32 (*GetAttr)	( IName *pILogdb,u32 FieldID, void **Ret);\
    u32 (*SetAttr)	( IName *pILogdb,u32 FieldID, void *NewValue)

DEFINE_INTERFACE(ILogdb);

typedef struct
{
    DECLARE_FUNCTBL(ILogdb);	/* struct of interface function pointers */
    u32 nRefCnt;					/* reference count */
	MAELogdb_t *pMc;
	MAELogdb_t *pFirst;
	MAELogdb_t *pLast;
}_mae_logdb_t;

#define ILogdb_AddRef(p)				GET_FUNCTBL(p, ILogdb)->AddRef(p)
#define ILogdb_Release(p)				GET_FUNCTBL(p, ILogdb)->Release(p)
#define ILogdb_QueryInterface(p,s,t)	GET_FUNCTBL(p, ILogdb)->QueryInterface(p,s,t)

/**
* (internal function, to be moved to private area)
*/
#define ILogdb_Init(p,s)				GET_FUNCTBL(p, ILogdb)->Init(p,s)

/**
 * Switch the logdb object to next one.
 *
 * Change to next contain in the list. If the current is the latest one,
 * it should return MAE_RET_CONTENT_NOMOREITEM and nothing happens.
 *
 * There may more than one log inside the object because there may exist
 * many records when you are using ILogDBMgr_GetLogdbByType or ILogDBMgr_GetLogdbALL
 * to query logs in the database.
 *
 * The client can use the following interface to go through the result:
 *   ILogdb_MoveNext - Move to next record
 *   ILogdb_MovePre - Move to previous record
 *   ILogdb_MoveLast - Move to last record
 *   ILogdb_MoveFirst - Move to fist record
 *
 * This interface will affect the result of the following interfaces:
 * (Because current data inside the object is switched)
 *   ILogdb_SetAttr (and related getter interface)
 *   ILogdb_GetAttr (and related setter interface)
 *
 * @param p pointer to instance of ILogdb
 * @return MAE_RET_SUCCESS Switch to next record success
 *         MAE_RET_CONTENT_NOMOREITEM current item is the last one, no more next items.
 */
#define ILogdb_MoveNext(p)				GET_FUNCTBL(p, ILogdb)->MoveNext(p)

/**
 * Switch the logdb object to previous one.
 *
 * Change to previous contain in the list. If the current is the first one,
 * it should return MAE_RET_CONTENT_NOMOREITEM and nothing happens.
 *
 * This interface will affect the result of the following interfaces:
 * (Because current data inside the object is switched)
 *   ILogdb_SetAttr (and related getter interface)
 *   ILogdb_GetAttr (and related setter interface)
 *
 * @see ILogdb_MoveNext
 * @param p pointer to instance of ILogdb
 * @return MAE_RET_SUCCESS Switch to previous record success
 *         MAE_RET_CONTENT_NOMOREITEM current item is the fist one, no more previous items.
 */
#define ILogdb_MovePre(p)				GET_FUNCTBL(p, ILogdb)->MovePre(p)

/**
 * Switch the logdb object to last one.
 *
 * If there exist only one logdb in list, or current logdb is
 * already the last one, nothing happens and MAE_RET_SUCCESS returns.
 *
 * @see ILogdb_MoveNext
 * @param p pointer to instance of ILogdb
 * @return MAE_RET_SUCCESS Move to last ILogdb record success
 */
#define ILogdb_MoveLast( p )			GET_FUNCTBL(p, ILogdb)->MoveLast(p)

/**
 * Switch the logdb object to fist one.
 *
 * If there exist only one logdb in list, or current logdb is
 * already the first one, nothing happens and MAE_RET_SUCCESS returns.
 *
 * @see ILogdb_MoveNext
 * @param p pointer to instance of ILogdb
 * @return MAE_RET_SUCCESS Move to first ILogdb record success
 */
#define ILogdb_MoveFirst( p )			GET_FUNCTBL(p, ILogdb)->MoveFirst(p)

/**
 * Get attributes for current logdb
 *
 * @param p pointer to instance of ILogdb
 * @param s attribute id, begins from LOGDBATTR_BASE end to LOGDBATTR_MAX
 * @param t pointer to pointer to get the output
 * @return MAE_RET_SUCCESS Get attribute ok
 *         MAE_RET_BAD_PARAM Unknown attribute id
 */
#define ILogdb_GetAttr(p,s,t)			GET_FUNCTBL(p, ILogdb)->GetAttr(p,s,t)

/**
 * Set attributes for current logdb
 *
 * @param p pointer to instance of ILogdb
 * @param s attribute id, begins from LOGDBATTR_BASE end to LOGDBATTR_MAX
 * @param t pointer to the new value for this attribute
 * @return MAE_RET_SUCCESS Get attribute ok
 *         MAE_RET_BAD_PARAM Unknown attribute id
 */
#define ILogdb_SetAttr(p,s,t)			GET_FUNCTBL(p, ILogdb)->SetAttr(p,s,t)
/*-------------------------------------------------------------------------*/

#endif /* __MMI_MAE_LOGDB_H__ */

