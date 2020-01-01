/**
 *
 * @file    ven_user.h
 * @brief   This file defines user extend interface
 *
 * @author  Christine.Tai
 * @version $Id: ven_user.h 15638 2008-10-28 06:56:50Z christine.tai $
 *
 */
#ifndef __VEN_USER_DEFINE_H_
#define __VEN_USER_DEFINE_H_


#include "ven_sdk.h"

typedef struct
{
    u32 Handle;
    u32 retData;
    u32 u32DataLen;
} Ven_user_extend_msg_t;

enum
{
    VEN_USER_SUCCESS,
    VEN_USER_BAD_PARAMS,
    VEN_USER_FAILED
};

typedef u8 ven_user_ret_t;

typedef void (*VEN_USER_PARSER_FUNC_PTR)(void * pData, u32 u32DataLen);


typedef struct ven_user_func_tag
{
    VEN_USER_PARSER_FUNC_PTR    pfnParser;
} ven_user_func_t;

ven_user_ret_t ven_user_regFuncs(u32 SdkHandle, ven_user_func_t *ptFuncs);
ven_user_ret_t ven_user_SendExtendMsg(Ven_user_extend_msg_t *ptVenRsp);

#endif //__VEN_USER_DEFINE_H_
