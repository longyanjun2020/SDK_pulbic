/**
 *
 * @file    ven_handle.h
 * @brief   This file is used to provide handle operations by SDK function request.
 *
 * @author  Ray.Lee
 * @version $Id: ven_handle.h 47127 2009-12-10 14:30:38Z steve.lee $
 *
 */

#ifndef __VEN_HANDLE_H__
#define __VEN_HANDLE_H__

#include "ven_sdk.h"

/*--------------------------------------------------------------------------*/
/* Private Function Definition                                              */
/*--------------------------------------------------------------------------*/
void ven_handle_setAppId(ven_app_id_t appId, u32 handle);
ven_app_id_t ven_handle_getAppId(u32 handle);

/*--------------------------------------------------------------------------*/
/* Public Function Definition                                               */
/*--------------------------------------------------------------------------*/
u32 ven_handle_open(ven_app_id_t appId);
void ven_handle_close(u32 handle);

#endif

