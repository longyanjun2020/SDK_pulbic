/**
* @file    mmi_mae_logdbmgr.h
* @brief   The document describes the interface of ILogDBMgr
* @author  mark.yang@mstarsemi.com
* @version $Id: mmi_mae_logdbmgr.h 1560 2009-08-09 09:38:44Z mark.yang $
*/
#ifndef __MMI_MAE_LOGDBMGR_H__
#define __MMI_MAE_LOGDBMGR_H__
#include "mmi_mae_common_def.h"
#include "mmi_mae_logdb.h"

/**
* ILogDBMgr interface definition
*/
#define INHERIT_ILogDBMgr(IName) \
	INHERIT_IBase(IName); \
	u32 (*AddLogdb)					(IName *pILogdb, ILogdb *att);\
	u32 (*DeleteLogdb)				(IName *pILogdb, ILogdb *att);\
	u32 (*DeleteLogdbByID)			(IName *pILogdb, u32 LogdbID);\
	u32 (*DeleteLogdbByType)		(IName *pILogdb, u8 LogdbType);\
	u32 (*DeleteLogdbAll)			(IName *pILogdb);\
	u32 (*GetLogdbByType)			(IName *pILogdb, u8 LogdbType,u32 *RetCountNumber, ILogdb **ret, IBase *Owner);\
	u32 (*GetLogdbALL)				(IName *pILogdb, u32 *RetCountNumber, ILogdb **ret, IBase *Owner)

DEFINE_INTERFACE(ILogDBMgr);

#define ILogDBMgr_AddRef(p)								GET_FUNCTBL(p, ILogDBMgr)->AddRef(p)
#define ILogDBMgr_Release(p)							GET_FUNCTBL(p, ILogDBMgr)->Release(p)
#define ILogDBMgr_QueryInterface(p,s,t)					GET_FUNCTBL(p, ILogDBMgr)->QueryInterface(p,s,t)

/**
 * Add new logdb record into database
 *
 * Current implementation note:
 * If there already exist a logdb record with the same ID, the record will be replaced by new one.
 * 
 * @param p pointer of ILogDBMgr instance 
 * @param s pointer of ILogdb instance to be added 
 */
#define ILogDBMgr_AddLogdb(p,s)							GET_FUNCTBL(p, ILogDBMgr)->AddLogdb(p,s)

/**
 * Remove a existing logdb record from database
 * 
 * The same as ILogDBMgr_DeleteLogdbByID() and pass the logdb id as the parameter.
 * 
 * @param p pointer of ILogDBMgr instance 
 * @param s pointer of ILogdb instance to be removed
 */
#define ILogDBMgr_DeleteLogdb( p,s)						GET_FUNCTBL(p, ILogDBMgr)->DeleteLogdb(p,s)

/**
 * Remove a existing logdb record from database
 *
 * @see ILogDBMgr_DeleteLogdb
 * @param p pointer of ILogDBMgr instance 
 * @param s id of logdb to be removed
 */
#define ILogDBMgr_DeleteLogdbByID( p,s)					GET_FUNCTBL(p, ILogDBMgr)->DeleteLogdbByID(p,s)

/**
 * Remove all logdb records for a specific type
 * 
 * @param p pointer of ILogDBMgr instance 
 * @param s type of logdb
 */
#define ILogDBMgr_DeleteLogdbByType( p,s)				GET_FUNCTBL(p, ILogDBMgr)->DeleteLogdbByType(p,s)

/**
 * Remove all logdb records
 * 
 * @param p pointer of ILogDBMgr instance 
 */
#define ILogDBMgr_DeleteLogdbAll(p)						GET_FUNCTBL(p, ILogDBMgr)->DeleteLogdbAll(p)

/**
 * Get all logdb records for a specific type from database
 *
 * @param pILogDBMgr pointer of ILogDBMgr instance 
 * @param t type of logdb
 * @param u [out] number of logdb records match the type
 * @param v [out] pointer of pointer of ILogdb for getting the returning ILogdb address
 * @param w owner instance for ADDREF for the output ILogdb object
 */
#define ILogDBMgr_GetLogdbByType(pILogDBMgr,t,u,v,w)	GET_FUNCTBL(pILogDBMgr,ILogDBMgr)->GetLogdbByType(pILogDBMgr,t,u,v,w)

/**
 * Get all logdb records from database
 * 
 * @param pILogDBMgr pointer of ILogDBMgr instance 
 * @param t [out] number of logdb records match the type
 * @param u [out] pointer of pointer of ILogdb for getting the returning ILogdb address
 * @param v owner instance for ADDREF for the output ILogdb object
 */
#define ILogDBMgr_GetLogdbALL(pILogDBMgr,t,u,v)			GET_FUNCTBL(pILogDBMgr,ILogDBMgr)->GetLogdbALL(pILogDBMgr,t,u,v)

/*-------------------------------------------------------------------------*/
#endif /* __MAE_LOGDBMGR_H__ */

