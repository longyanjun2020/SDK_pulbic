/*NCC MMS network header file*/
#ifndef __NCC_MMS_NETWORK_H__
#define __NCC_MMS_NETWORK_H__

#include <ncc_types.h>

#ifdef __cplusplus
extern "C"{
#endif

#define MMS_NETWORK_SUCCESS 0
#define MMS_NETWORK_NEW_MSG 1
#define MMS_NETWORK_SUCCESS_WITH_NO_TRANS_ID 2
#define MMS_NETWORK_FAILED -1
#define MMS_NETWORK_WOULDBLOCK -2
#define MMS_NETWORK_NO_BUF -3
#define MMS_NETWORK_NET_FAILED -4
#define MMS_NETWORK_INVALID_PARAMETER -5
#define MMS_NETWORK_PERMANENT_FAILED -6
#define MMS_NETWORK_LOCAL_FAILED -7
#define MMS_NETWORK_ERROR_OVERSIZE -8
#define MMS_NETWORK_SUCCESS_BUT_FS_FATAL_ERROR -9

//argc: 2    argv[0]: type    argv[1]: index
#define MMS_PUSH_RESULT_NEW_MSG 0
//argc: 1    argv[0]: index
#define MMS_PUSH_RESULT_TRY_DOWNLOAD 1
// arc:1 argv[0] :index
#define MMS_PUSH_RESULT_NEW_PROVISION 2
//argc: 0    argv: NULL
#define MMS_PUSH_RESULT_PARSE_ERROR -1
//argc: 0    argv: NULL
#define MMS_PUSH_RESULT_BOX_FULL -2
//argc: 0    argv: NULL
#define MMS_PUSH_RESULT_OTHER_ERROR -3
//argc: 0    argv: NULL
#define MMS_PUSH_RESULT_PROV_OK 1

#define MMS_NET_RESULT_SUCCESS 0
#define MMS_NET_RESULT_FAILED -1

#define MMS_NET_RESULT_TYPE_NEW 0
#define MMS_NET_RESULT_TYPE_DELETE 1
#define MMS_NET_RESULT_TYPE_UPDATE 2

#define MMS_REQ_RESULT_SUCCESS 0
#define MMS_REQ_RESULT_ERROR -1
#define MMS_REQ_RESULT_TIMEOUT -2
#define MMS_REQ_RESULT_USER_CANCEL -3
#define MMS_REQ_RESULT_ERROR_OVERSIZE -4


typedef struct T_mmsnet_Handle *MMS_Net_Handle;

typedef struct
{
    int32_t type; /*MMS_NET_RESULT_TYPE_NEW|
                    MMS_NET_RESULT_TYPE_DELETE|
                    MMS_NET_RESULT_TYPE_UPDATE*/
    int32_t result; /*MMS_NET_RESULT_SUCCESS|
                    MMS_NET_RESULT_FAILED*/
    int32_t mailbox;
    int32_t index;
}T_MmsNet_Result;

typedef void (*networkTimerFunc) (void);
typedef void (*PushResultCallBack) (int32_t result, int32_t argc, void *argv[]);
typedef void (*NetResultCallBack) (T_MmsNet_Result *result);

MMS_Net_Handle NCCMms_net_sendMmsByBuffer(
#ifdef MMS_DUAL_SIM_SUPPORT
                                        uint8_t *imsi,
#endif
                                        uint8_t *buffer,
                                        int32_t size,
                                        T_MmsFs_headInfo *headInfo);
                                        
MMS_Net_Handle NCCMms_net_sendMmsByMailBox(MMS_FS_MAILBOX mailBox,
                                        int32_t index);
                                        
MMS_Net_Handle NCCMms_net_downloadByBuffer(
#ifdef MMS_DUAL_SIM_SUPPORT
                                        uint8_t *imsi,
#endif
                                        uint8_t *buffer,
                                        int32_t size);
                                        
MMS_Net_Handle NCCMms_net_downloadByMailBox(MMS_FS_MAILBOX mailBox,
                                        int32_t index);

MMS_Net_Handle NCCMms_net_sendNotiResp(MMS_FS_MAILBOX mailBox,
                                        int32_t index);

MMS_Net_Handle NCCMms_net_sendReadRecInd(MMS_FS_MAILBOX mailBox,
                                        int32_t index);
int32_t NCCMms_net_setMaxRecvDataSize(MMS_Net_Handle netHandle, uint32_t datasize);

int32_t NCCMms_net_registerTimerFunc(MMS_Net_Handle netHandle, networkTimerFunc timerFunc);

int32_t NCCMms_net_runRequest(MMS_Net_Handle netHandle, int32_t *progress);

int32_t NCCMms_net_endRequest(MMS_Net_Handle netHandle,
                                int32_t requestResult,
                                NetResultCallBack callback);

int32_t NCCMms_net_receivePushMessage(uint8_t *msg,
                                    int32_t msgLen,
#ifdef MMS_DUAL_SIM_SUPPORT
                                    uint8_t *imsi,
#endif
                                    uint8_t *from,
                                    PushResultCallBack callback);

int8_t *NccMms_GetVersionInfo(void);

void NCCPush_manager_registerProvApp(
#ifdef MMS_DUAL_SIM_SUPPORT
                                    uint8_t *imsi,
#endif
                                    uint8_t *from,
                                    PushResultCallBack callback);


#ifdef __cplusplus
}
#endif

#endif //__NCC_MMS_NETWORK_H__
