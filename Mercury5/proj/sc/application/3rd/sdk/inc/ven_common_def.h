/**
 *
 * @file    ven_common_def.h
 * @brief   This file is the collection of common definitions
 *
 * @author  Jorena.Ku
 * @version $Id: ven_common_def.h 36460 2009-07-24 03:02:22Z code.lin $
 *
 */


#ifndef __VEN_COMMON_DEF_H__
#define __VEN_COMMON_DEF_H__

/******************************************/
/*           Include files                */
/******************************************/
#include "cus_os.hc"
#include "ven_types.h"
#include "ven_sdk.h"

/******************************************/
/*              Definitions               */
/******************************************/
typedef u16 ven_msg_t;

/******************************************/
/*         Function declarations          */
/******************************************/
void ven_msg_parser(ven_msg_t MsgID, vm_msg_t *pMessage);

#endif //__VEN_COMMON_DEF_H__
