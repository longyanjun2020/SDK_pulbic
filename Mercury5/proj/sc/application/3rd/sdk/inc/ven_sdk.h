/**
 *
 * @file    ven_sdk.h
 * @brief
 *
 * @author  Steve.Lee
 * @version $Id: ven_sdk.h 36460 2009-07-24 03:02:22Z code.lin $
 *
 */
#ifndef __VEN_SDK_H__
#define __VEN_SDK_H__

#include "ven_types.h"
#include "ven_std.h"
#include "ven_integration.h"

// Callback function prototype
typedef void (*VEN_CB_FUNC_PTR)(u32 param1, u32 param2);

typedef struct
{
    u32 Handle;
    u32 userData;
    VEN_CB_FUNC_PTR pfnCb;
    bool bSync;
} ven_req_data_t;

typedef struct
{
    u32 Handle;
    u32 retData;
} ven_rsp_data_t;

typedef u8 ven_common_sim_id_t;

#define __ENUM_VEN_APP_ID__
#include "ven_apptbl_pub.h"
#undef __ENUM_VEN_APP_ID__
typedef u8 ven_app_id_t;

/* system handle, for sending extend msg to system */
#define SYS_HANDLE 0x00000000

#endif /* __VEN_SDK_H__ */

