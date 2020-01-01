/**
 * @file ven_kpd.h
 *
 * @brief This file defines the keypad event to vendor
 *
 * @version $Id: ven_kpd.h 47224 2009-12-17 15:14:15Z kenny.wu $
 *
 */
#ifndef __VEN_KPD_H_
#define __VEN_KPD_H_

#include "ven_sdk.h"

/*--------------------------------------------------------------------------*/
/* Type Definition                                                          */
/*--------------------------------------------------------------------------*/

enum
{
    VEN_KPD_FAILED,
    VEN_KPD_SUCCESS
};

typedef u8 ven_kpd_ret_t;

enum
{
    VEN_KPD_ACT_PRESS = 1,
    VEN_KPD_ACT_RELEASE = 2
};

typedef u8 ven_kpd_act_t;

enum
{
    VEN_KEY_OK = 1,
    VEN_KEY_MEN,
    VEN_KEY_LEFT,
    VEN_KEY_PHB,
    VEN_KEY_RIGHT,
    VEN_KEY_ONOFF,
    VEN_KEY_CLR,
    VEN_KEY_PLUS,
    VEN_KEY_SEND,
    VEN_KEY_SEND2,
    VEN_KEY_END,
    VEN_KEY_MINUS,
    VEN_KEY_1,
    VEN_KEY_2,
    VEN_KEY_3,
    VEN_KEY_4,
    VEN_KEY_5,
    VEN_KEY_6,
    VEN_KEY_7,
    VEN_KEY_8,
    VEN_KEY_9,
    VEN_KEY_STAR,
    VEN_KEY_0,
    VEN_KEY_HASH,
    VEN_KEY_MSG,
    VEN_KEY_MAIL,
    VEN_KEY_FSTDL1,
    VEN_KEY_FSTDL2,
    VEN_KEY_FSTDL3,
    VEN_KEY_FSTDL4,
    VEN_KEY_REDIAL,
    VEN_KEY_HOOK,
    VEN_KEY_UP,
    VEN_KEY_DOWN,
    VEN_KEY_FLAPON,
    VEN_KEY_FLAPOFF,
    VEN_KEY_SIDE_UP,
    VEN_KEY_SIDE_DN,
    VEN_KEY_SKLEFT ,
    VEN_KEY_SKRIGHT,
    VEN_KEY_HEADSET,
    VEN_KEY_CLEAR,
    VEN_KEY_ACTION,
    VEN_KEY_CAMERA,
    VEN_KEY_MP3,
    VEN_KEY_POWERMODE,
    VEN_KEY_HOME,
    /* ===== Start of Qwerty keypad ===== */
    VEN_KEY_Q,
    VEN_KEY_A,
    VEN_KEY_Alt,
    VEN_KEY_SHIFTLEFT,
    VEN_KEY_ENTER,
    VEN_KEY_W,
    VEN_KEY_S,
    VEN_KEY_Z,
    VEN_KEY_E,
    VEN_KEY_D,
    VEN_KEY_X,
    VEN_KEY_SPACE,
    VEN_KEY_R,
    VEN_KEY_F,
    VEN_KEY_C,
    VEN_KEY_SYM,
    VEN_KEY_T,
    VEN_KEY_G,
    VEN_KEY_V ,
    VEN_KEY_SHIFTRIGHT,
    VEN_KEY_Y,
    VEN_KEY_H,
    VEN_KEY_B,
    VEN_KEY_DOLLAR,
    VEN_KEY_U,
    VEN_KEY_J,
    VEN_KEY_N,
    VEN_KEY_O,
    VEN_KEY_L,
    VEN_KEY_I,
    VEN_KEY_K,
    VEN_KEY_M,
    VEN_KEY_P,
    VEN_KEY_DEL,
    VEN_KEY_NEXT,
    VEN_KEY_DOT,
    VEN_KEY_SHIFT,
    VEN_KEY_COMMA,
    VEN_KEY_AT,
    VEN_KEY_EXCLAM,
    VEN_KEY_APOSTROPHE,
    /* ===== End of Qwerty keypad ===== */

    VEN_KEY_LAST,
    VEN_KEY_SAME = 0xFE,
    VEN_KEY_DUMMY = 0xFF
};

typedef u8 ven_kpd_key_code_t;

typedef void (*VEN_KPD_IND_FUNC_PTR)(ven_kpd_act_t act, ven_kpd_key_code_t code);

/*--------------------------------------------------------------------------*/
/* Public Function Definition                                               */
/*--------------------------------------------------------------------------*/

/**
 *  ven_kpd_subscribe
 *
 *  @brief  Subscribe to SDK for keypad event
 *
 *  @param  SdkHandle    [in] The handle of SDK get from ven_handle_open()
 *  @param  pfnKpdInd    [in] Pointer to the function to receive keypad event
 *
 *  @retval VEN_KPD_SUCCESS   Subscribe successfully
 *          VEN_KPD_FAILED    Subscribe failed
 *
 */
ven_kpd_ret_t ven_kpd_subscribe(u32 SdkHandle, VEN_KPD_IND_FUNC_PTR pfnKpdInd);


ven_kpd_ret_t ven_kpd_subscribe_ex(u32 SdkHandle, VEN_KPD_IND_FUNC_PTR pfnKpdInd);


/**
 *  ven_kpd_unsubscribe
 *
 *  @brief  Unsubscribe for keypad event
 *
 *  @param  SdkHandle    [in] The handle of SDK get from ven_handle_open()
 *
 *  @retval VEN_KPD_SUCCESS   Unsubscribe successfully
 *          VEN_KPD_FAILED    Unsubscribe failed
 *
 */
ven_kpd_ret_t ven_kpd_unsubscribe(u32 SdkHandle);

/**
 *  ven_kpd_enablePressTone
 *
 *  @brief  Enable keypad press tone
 *
 *  @param  SdkHandle    [in] The handle of SDK get from ven_handle_open()
 *
 *  @retval VEN_KPD_SUCCESS   Enable successfully
 *          VEN_KPD_FAILED    Enable failed
 *
 */
ven_kpd_ret_t ven_kpd_enablePressTone(u32 SdkHandle);

/**
 *  ven_kpd_disablePressTone
 *
 *  @brief  Disable keypad press tone
 *
 *  @param  SdkHandle    [in] The handle of SDK get from ven_handle_open()
 *
 *  @retval VEN_KPD_SUCCESS   Disable successfully
 *          VEN_KPD_FAILED    Disable failed
 *
 */
ven_kpd_ret_t ven_kpd_disablePressTone(u32 SdkHandle);

#endif //__VEN_KPD_H_

