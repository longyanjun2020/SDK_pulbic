/**
 * @file ven_ts.h
 *
 * @brief This file defines the touch screen response to vendor
 *
 * @version $Id: ven_ts.h 27910 2009-04-09 09:10:00Z steve.lee $
 *
 */
#ifndef __VEN_TS_H_
#define __VEN_TS_H_

#include "ven_sdk.h"

/*--------------------------------------------------------------------------*/
/* Type Definition                                                          */
/*--------------------------------------------------------------------------*/

enum
{
    VEN_TS_FAILED,
    VEN_TS_SUCCESS
};

typedef u8 ven_ts_ret_t;

enum
{
    VEN_TS_EVENT_PRESS,
    VEN_TS_EVENT_RELEASE,
    VEN_TS_EVENT_MOVE,
    VEN_TS_EVENT_LONGPRESS,
    VEN_TS_EVENT_CLICK
};

typedef s8 ven_ts_evt_t;

typedef void (*VEN_TS_INPUT_IND_FUNC_PTR)(ven_ts_evt_t type, u32 x, u32 y);

/*--------------------------------------------------------------------------*/
/* Public Function Definition                                               */
/*--------------------------------------------------------------------------*/
/**
 *  ven_ts_subscribe
 *
 *  @brief  Subscribe to SDK for touch screen event
 *
 *  @param  SdkHandle    [in] The handle of SDK get from ven_handle_open()
 *  @param  pfnTsInd     [in] Pointer to the function to receive touch screen event
 *
 *  @retval VEN_TS_SUCCESS   Subscribe successfully
 *          VEN_TS_FAILED    Subscribe failed
 *
 *  @note   Subscribe will also call ven_ts_enable() automatically
 */
ven_ts_ret_t ven_ts_subscribe(u32 SdkHandle, VEN_TS_INPUT_IND_FUNC_PTR pfnTsInd);

/**
 *  ven_ts_unsubscribe
 *
 *  @brief  Unsubscribe for touch screen event
 *
 *  @param  SdkHandle    [in] The handle of SDK get from ven_handle_open()
 *
 *  @retval VEN_TS_SUCCESS   Unsubscribe successfully
 *          VEN_TS_FAILED    Unsubscribe failed
 *
 *  @note   Unsubscribe will also call ven_ts_disable() automatically
 */
ven_ts_ret_t ven_ts_unsubscribe(u32 SdkHandle);

/**
 *  ven_ts_enable
 *
 *  @brief  Enable touch screen event
 *
 *  @param  SdkHandle    [in] The handle of SDK get from ven_handle_open()
 *
 *  @retval VEN_TS_SUCCESS   Successfully
 *          VEN_TS_FAILED    Failed
 */
ven_ts_ret_t ven_ts_enable(u32 SdkHandle);

/**
 *  ven_ts_disable
 *
 *  @brief  Disable touch screen event
 *
 *  @param  SdkHandle    [in] The handle of SDK get from ven_handle_open()
 *
 *  @retval VEN_TS_SUCCESS   Subscribe successfully
 *          VEN_TS_FAILED    Subscribe failed
 */
ven_ts_ret_t ven_ts_disable(u32 SdkHandle);

#endif //__VEN_TS_H_
