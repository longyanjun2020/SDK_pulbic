////////////////////////////////////////////////////////////////////////////////
//
// Copyright (c) 2006-2009 MStar Semiconductor, Inc.
// All rights reserved.
//
// Unless otherwise stipulated in writing, any and all information contained
// herein regardless in any format shall remain the sole proprietary of
// MStar Semiconductor Inc. and be kept in strict confidence
// (¡§MStar Confidential Information¡¨) by the recipient.
// Any unauthorized act including without limitation unauthorized disclosure,
// copying, use, reproduction, sale, distribution, modification, disassembling,
// reverse engineering and compiling of the contents of MStar Confidential
// Information is unlawful and strictly prohibited. MStar hereby reserves the
// rights to any and all damages, losses, costs and expenses resulting therefrom.
//
////////////////////////////////////////////////////////////////////////////////

/**
* @file    mdl_storage.h
* @version
* @brief   This module defines the General Peripheral Device Driver API layer
*
*/



/*--------------------------------------------------------------------------*/
/* INCLUDE FILE                                                             */
/*--------------------------------------------------------------------------*/
#if !defined(__SDK_SIMULATION__)
#include "mdl_stg2gpd.h"
#endif


/*--------------------------------------------------------------------------*/
/* PREPROCESSOR CONSTANT DEFINITION                                         */
/*--------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------*/
/* PREPROCESSOR MACRO DEFINITION                                            */
/*--------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------*/
/* TYPE DEFINITION                                                          */
/*--------------------------------------------------------------------------*/


/*--------------------------------------------------------------------------*/
/* GLOBAL FUNCTION DEFINITION                                               */
/*--------------------------------------------------------------------------*/
#if !defined(__SDK_SIMULATION__)
MdlGpdErrCode_e MdlGpdFireAnotherEvent(MsTimerId_e timerId);


MdlGpdErrCode_e MdlGpdTriggerRetryTimer(MDL_STG_IP ip, MDL_STG_TYPE type, MDL_STG_EVENT event);


MdlGpdErrCode_e MdlGpdCancelRetryTimer(MDL_STG_IP ip);
#endif /* !defined(__SDK_SIMULATION__)  */

