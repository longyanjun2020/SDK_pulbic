
#ifndef __MANAGER_H__
#define __MANAGER_H__

#ifdef __cplusplus
extern "C"{
#endif

#include <ncc_types.h>
#include <manager_adapter.h>
#include <nccpush_manager.h>

#define PUSH_GET_CONTENT_TYPE_ERROR                 -31 /**<Return value:Indicate Get Content-Type Field error.*/

typedef struct T_PUSH_APP_NODE{
    T_PUSH_APP APP;
    struct T_PUSH_APP_NODE *next;
}T_PUSH_APP_NODE;

typedef struct T_PUSH_APP_LIST
{
    int32_t total;
    struct T_PUSH_APP_NODE *next;
}T_PUSH_APP_LIST;

int32_t PUSH_InitAPPNode(T_PUSH_APP *App,T_PUSH_APP_NODE **App_Node);

int32_t PUSH_Dispatch(PUSH_HANDLE PushHandle,T_PUSH_PO_UNIT *POUnit);

int32_t PUSH_GetALLPushHeader(uint8_t *pHeaderPdu,int32_t pduLen,T_PUSH_HEADER_LIST **pHeaderList);

void PUSH_FreePushHeaderList(T_PUSH_HEADER_LIST *pList);

#ifdef __cplusplus
}
#endif

#endif
