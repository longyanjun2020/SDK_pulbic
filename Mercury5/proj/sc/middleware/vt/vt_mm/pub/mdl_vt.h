#ifndef _MDL_VT_H_
#define _MDL_VT_H_

#include "MML_Manager.h"

/*  definitions */
#define MDL_VT_MBX_MAIN VM_MBX_CUS63
#define MDL_VT_HANDLE   0xABC12345
#define VT_TEST 0
#define TEST_VTMUX 0

//#define DISABLE_VDR_REG_CALLBACK
//#define DISABLE_VT_REG_CALLBACK

/* data structures */
typedef enum {
    VT_OK = 0,
    VT_ERR_FAIL = 1,
} vt_err_et;


/* function prototypes */
void *MdlVt_ParseMessage (void *par);
void MdlVt_Init(void);
vt_err_et
MdlVt_ResponseCallbackInvoke_1
(
    unsigned long     nUseCaseID,
    unsigned long     nErrCode,
    void    *pResponsePayload
);

MmlErrCode_e
MdlVt_ResponseCallbackInvoke
(
    u32     nUseCaseID,
    u32     nErrCode,
    void    *pResponsePayload
);


void
MdlVt_SendResponse (
    MmlUseCaseVideoId_e eId,
    MmlVideoState_e eState,
    u32 nHandle, MmlVideoResult_e eResult,
    MmlVideoState_e eNewState,
    MmlVideoEvent_e eEvent);


MmlErrCode_e
MdlVt_NotifyCallbackInvoke
(
    u32     nEvent,
    void    *pNotifyPayload
);

vt_err_et
MdlVt_NotifyCallbackInvoke_1
(
    unsigned long     nEvent,
    void    *pNotifyPayload
);

vt_err_et
MdlVt_Start (void);

vt_err_et
MdlVt_Stop (void);

vt_err_et
MdlVt_TestSetting (void);

void
MdlVt_SetLoopbackMode (int mode);

unsigned char
MdlVt_GetLoopbackMode (void);

void
MdlVt_SetFileLogging (int mode);

void
MdlVt_SetInternalTest (int mode);

vt_err_et
MdlVt_SendMsg(u32 MsgType, void *Msg, u32 MsgSize, u32 UserData);

void
MdlVt_NotifyStateChange(MmlVideoState_e eState, MmlVideoEvent_e eCause);

void
MdlVt_NotifyRuntimeError(MmlVideoResult_e eErrorCode);


#endif

