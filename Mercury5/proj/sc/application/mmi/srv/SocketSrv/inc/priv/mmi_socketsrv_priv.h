/**
* @file mmi_socketsrv_priv.h
*
* Class Id: CLSID_SOCKETSRV
*
* @version $Id:
*/
#ifndef __MMI_SOCKETSRV_PRIV_H__
#define __MMI_SOCKETSRV_PRIV_H__

/*-------------------------------------------------------------------------*/
#include "mmi_mae_common_def.h"
#include "mmi_socketsrv.h"

/*-------------------------------------------------------------------------*/

typedef struct SocketSrv_t_
{
    DECLARE_FUNCTBL(ISOCKETSRV); // function table pointer
    u32 nRefCnt;     // reference count
    //other Service Data
} SocketSrv_t;

/*-------------------------------------------------------------------------*/
#endif /* __MMI_SOCKETSRV_PRIV_H__ */
