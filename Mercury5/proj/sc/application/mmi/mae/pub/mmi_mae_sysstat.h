/**
 * @file    mmi_mae_sysstat.h
 * @brief   The document describes the interface of ISysStat
 * @author  sam.chen@mstarsemi.com
 * @version $Id: mmi_mae_sysstat.h 291 2009-02-27 13:08:01Z kenny.wu $
 */

#ifndef __MMI_MAE_SYSSTAT_H__
#define __MMI_MAE_SYSSTAT_H__
#include "mmi_mae_common_def.h"
#include "mmi_mae_handler.h"

#define INHERIT_ISysStat(IName) \
	INHERIT_IHandler(IName)

DEFINE_INTERFACE(ISysStat);

/**
 *  ISYSTEM_QueryInterface
 *  @brief  Inherit addref from IBase to query interface. It only support the interface of ISystem.
 *
 *  @param  pISystem         Pointer to the ISystem interface
 *  @param  id              Interface ID. In this function, only IID_SYSTEM is supported.
 *  @param  pp              Reference to a pointer to a function table if this interface is supported
 *  @param  pOwner			Instance of the object who uses this interface, for reference check.
 *  @retval MAE_RET_SUCCESS Success
 *  @retval MAE_RET_NOT_SUPPORTED Not support this interface
 *
 */
#define ISYSTEM_QueryInterface(pISysStat,id,pp,pOwner)      GET_FUNCTBL(pISysStat,ISystem)->QueryInterface(pISysStat,id,pp,pOwner)

/**
 * Functions
 */
MAE_Ret MAESysStat_New(MAE_ClsId nClsID, void **ppObj);

#endif /* __MAE_SYSSTAT_H__ */
