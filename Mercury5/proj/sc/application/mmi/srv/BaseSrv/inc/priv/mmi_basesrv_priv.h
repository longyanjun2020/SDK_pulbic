/**
* @file mmi_BaseSrv_priv.h
*
* This header file defines the data structure of base service.
*
*/

#ifndef __MMI_BASESRV_PRIV_H__
#define __MMI_BASESRV_PRIV_H__

/*=============================================================*/
// Include Files
/*=============================================================*/
#include "mmi_BaseSrv.h"
#include "mmi_mae_shell.h"
#include "mmi_mae_class.h"
#include "mmi_log.h"
#include "mmi_mediasrvutil_common.h"
/*=============================================================*/
// Macro Declarations
/*=============================================================*/
#define MMI_LEVEL_BASESRV MAE_LEVEL_SM
/*=============================================================*/
// Type Declarations
/*=============================================================*/
typedef struct BaseSrv_t_
{
	SERVICE_BASE_ELEMENTS;
} BaseSrv_t;
/*=============================================================*/
// Private Function Declaration
/*=============================================================*/
#endif //__MMI_BASESRV_PRIV_H__

