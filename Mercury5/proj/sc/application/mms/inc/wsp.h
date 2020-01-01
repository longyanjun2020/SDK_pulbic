
#ifndef __WSP_H__
#define __WSP_H__

#include <wsp_pub.h>
#ifdef __cplusplus
extern  "C" {
#endif

#define WTP_INVOKE_PDU_HEAD         4
#define WTP_RESULT_PDU_HEAD         3
#define WTP_SEG_RESULT_PDU_HEAD 4
#define WTP_ACK_PDU_HEAD            3 /* omit variable TPI fields */
#define WTP_ABORT_PDU_HEAD      4
#define WSP_VERSION 0x10

/* See Table 34 */
enum WSP_PduTypes{
    PduConnect=0x01,
    PduConnectReply=0x02 ,
    PduRedirect=0x03,
    PduReply= 0x04,
    PduDisconnect=0x05 ,
    PduPush =0x06,
    PduConfirmedPush=0x07 ,
    PduSuspend =0x08,
    PduResume=0x09 ,
    PduGet=0x40 ,
    PduOptions=0x41,
    PduHead=0x42,
    PduDelete=0x43,
    PduNCC_KERNEL_DEBUG=0x44,
    PduPost=0x60 ,
    PduPut=0x61
};

/* See Table 35 */
enum WSP_AbortVal{
    WSP_ABORT_PROTOERR = 0xe0,
    WSP_ABORT_DISCONNECT = 0xe1,
    WSP_ABORT_SUSPEND = 0xe2,
    WSP_ABORT_RESUME = 0xe3,
    WSP_ABORT_CONGESTION = 0xe4,
    WSP_ABORT_CONNECTERR = 0xe5,
    WSP_ABORT_MRUEXCEEDED = 0xe6,
    WSP_ABORT_MOREXCEEDED = 0xe7,
    WSP_ABORT_PEERREQ = 0xe8,
    WSP_ABORT_NETERR = 0xe9,
    WSP_ABORT_USERREQ = 0xea,
    WSP_ABORT_USERRFS = 0xeb,
    WSP_ABORT_USERPND = 0xec,
    WSP_ABORT_USERDCR = 0xed,
    WSP_ABORT_USERDCU = 0xee
};

enum {
    S_Connect_Req=13 ,
    S_Disconnect_Req=14 ,
    DISCONNECT=15,
    S_Suspend_Req=16,
    S_Resume_Req=17,
    TR_Invoke_Ind =18,
    TR_Invoke_Cnf=19 ,
    TR_Result_Ind=20,
    TR_Abort_Ind=21 ,
    S_MethodInvoke_Req =22,
    S_MethodResult_Res=23 ,
    S_MethodAbort_Req =24,
    S_ComfirmedPush_Res=25 ,
    S_PushAbort_Req=26 ,
    ABORT=27,
    SUSPEND=28
};

enum{
    Session_Null,
    Connecting,
    Connected,
    Suspended,
    Resuming,
    Method_Null,
    Requesting,
    Waiting,
    Completing,
    Push_Null,
    Push_Receiving,

    /* Added for wsp Server Session */
    S_Session_NULL,
    S_Session_CONNECTING,
    S_Session_TERMINATING,
    S_Session_CONNECTING_2,
    S_Session_CONNECTED,
    S_Session_SUSPENDED,
    S_Session_RESUMING,
    S_Session_RESUMING_2
};

enum WSP_KnownCaps{
    WSP_CAPS_CLIENT_SDU_SIZE = 0,
    WSP_CAPS_SERVER_SDU_SIZE = 1,
    WSP_CAPS_PROTOCOL_OPTIONS = 2,
    WSP_CAPS_METHOD_MOR = 3,
    WSP_CAPS_PUSH_MOR = 4,
    WSP_CAPS_EXTENDED_METHODS = 5,
    WSP_CAPS_HEADER_CODE_PAGES = 6,
    WSP_CAPS_ALIASES = 7,
    WSP_CAPS_CLIENT_MESSAGE_SIZE=8,
    WSP_CAPS_SERVER_MESSAGE_SIZE=9,
    WSP_NUM_CAPS
};


/* Use bitflags for set values */
#define WSP_CSDU_SET    1
#define WSP_SSDU_SET    2
#define WSP_PO_SET      4
#define WSP_MMOR_SET    8
#define WSP_PMOR_SET    16
#define WSP_EM_SET      32
#define WSP_HCP_SET 64
#define WSP_A_SET       128


struct T_WAP_Capability {
    int8_t id;          /**< Capability type */
    uint8_t Boundary[3];/**< boundary */
    int32_t data;       /**< Capability value */
};

typedef struct T_WAP_Capability T_WAP_Capability;

extern  const struct T_WAP_EventArray gpWAP_Event[];

void fnWSP_Recv(void * hc,uint8_t event,T_WAP_MCB * ctl,T_WAP_MSG_P msg);

/**
 * Make a PDU packet.
 *
 *   \param  hc  a wsp instance handle.
 *   \param  pdu_type the type of PDU packet.
 *   \param   p where to store the PDU packet.
 *   \param   arg3 the session ID .when pdu_type is not
 *       PduDisconnect,this parameter does not take effect.
 *   \return  If no enough memory,return -1,or return 0.
 */
 int8_t fnWSP_MakePdu(void *hc,int16_t pdu_type,T_WAP_MSG_P *p,void * arg3);

/**
 * This function checks and sets proper capabilities of the client and connects.
 *
 *   \param  hc  a wsp instance handle.
 *   \param  caps the WAP capabilities .
 *   \param  caps_size the size of WAP capability structure.
 *   \return  Return -1 if no session wanted or exist,else return 0.
 */
 int8_t fnWSP_ConnectNull(void *hc,T_WAP_Capability  caps[],int16_t caps_size);

/**
 * To disconnect session at the session state of Connecting.
 *
 *   \param  hc  a wsp instance handle.
 *   \param   arg0 unused parameter now;
 *   \param   arg1 unused parameter now.
 *   \return
 */
 void fnWSP_SDisconnect_Connecting(void *hc,void * arg0,void * arg1);

/**
 * The handle of the event DISCONNECT at the session state of Connecting.
 *
 *   \param  hc  a wsp instance handle.
 *   \param   arg0 unused parameter now;
 *   \param   arg1 unused parameter now.
 *   \return
 */
 void fnWSP_DISCONNECT_Connecting(void *hc,void * arg0,void * arg1);

/**
 * The handle of the session Method Invoke event.
 *
 *   \param  hc  a wsp instance handle.
 *   \param   arg0 unused parameter now;
 *   \param   arg1 unused parameter now.
 *   \return
 */
 void fnWSP_SMethodInvoke(void *hc,void * arg0,void * arg1);

 /**
 * The handle of the session Method Abort event.
 *
 *   \param  hc  a wsp instance handle.
 *   \param   ctl the MCB.
 *   \param   arg1 unused parameter now.
 *   \return
 */
 void fnWSP_SMethodAbort(void *hc,void * ctl,void * arg1);

/**
 * The handle of the event at the session state of Connecting.
 *
 *   \param  hc  a wsp instance handle.
 *   \param   arg0 unused parameter now;
 *   \param   arg1 unused parameter now.
 *   \return
 */
 void fnWSP_SUSPEND_Connecting(void *hc,void * ctl,void * arg1);

/**
 * The handle of the event InvokeInd  at the  session state of Connecting.
 *
 *   \param  hc  a wsp instance handle.
 *   \param   arg0 unused parameter now;
 *   \param   arg1 unused parameter now.
 *   \return
 */
 void fnWSP_InvokeInd_Connecting(void *hc,void * ctl,void * arg1);

 /**The handle of the event ResultInd at the  session state of Connecting.
 *
 *   \param  hc  a wsp instance handle.
 *   \param  ctl the MCB.
 *   \param  msg the message.
 *   \return
 */
 void fnWSP_ResultInd_Connecting(void *hc,void * ctl,void * msg);

/**
 * The handle of the event InvokeCnf  at the  session state of Connecting.
 *
 *   \param  hc  a wsp instance handle.
 *   \param   arg0 unused parameter now;
 *   \param   arg1 unused parameter now.
 *   \return
 */
 void fnWSP_InvokeCnf_Connecting(void *hc,void * ctl,void * msg);

/**
 * The handle of the event AbortInd  at the  session state of Connecting.
 *
 *   \param  hc  a wsp instance handle.
 *   \param   ctl the MCB;
 *   \param   arg1 unused parameter.
 *   \return
 */
 void fnWSP_AbortInd_Connecting(void *hc,void * ctl,void * arg1);

/**
 * To disconnect session at the session state of connected.
 *
 *   \param  hc  a wsp instance handle.
 *   \param  ls the session list;
 *   \param  arg1 unused parameter.
 *   \return
 */
 void fnWSP_SDisconnect_Connected(void *hc,void * ls,void * arg1);

/**
 * The handle of the event DISCONNECT at the session state of Connected
 *
 *   \param  hc  a wsp instance handle.
 *   \param   arg0 unused parameter now;
 *   \param   arg1 unused parameter now.
 *   \return
 */
 void fnWSP_DISCONNECT_Connected(void *hc,void * arg0,void * arg1);

/**
 * The handle of the event SMethodResult  at the  session state of Connected
 *
 *   \param  hc  a wsp instance handle.
 *   \param   arg0 unused parameter now;
 *   \param   arg1 unused parameter now.
 *   \return
 */
 void fnWSP_SMethodResult_Connected(void *hc,void * arg0,void * arg1);

/**
 * The handle of the event SConfirmedPush   at the  session state of Connected.
 *
 *   \param  hc  a wsp instance handle.
 *   \param   arg0 unused parameter now;
 *   \param   arg1 unused parameter now.
 *   \return
 */
 void fnWSP_SConfirmedPush_Connected(void *hc,void * arg0,void * arg1);

/**
 * The handle of the event   S_PushAbort at the  session state of Connected.
 *
 *   \param  hc  a wsp instance handle.
 *   \param   arg0 unused parameter now;
 *   \param   arg1 unused parameter now.
 *   \return
 */
 void fnWSP_SPushAbort_Connected(void *hc,void * arg0,void * arg1);

/**
 * The handle of the event SSuspend  at the  session state of Connected.
 *
 *   \param  hc  a wsp instance handle.
 *   \param   arg0 unused parameter now;
 *   \param   arg1 unused parameter now.
 *   \return
 */
 void fnWSP_SSuspend_Connected(void *hc,void * arg0,void * arg1);

/**
 * The handle of the event   at the  session state of Connected.
 *
 *   \param  hc  a wsp instance handle.
 *   \param   arg0 unused parameter now;
 *   \param   arg1 unused parameter now.
 *   \return
 */
 void fnWSP_SUSPEND_Connected(void *hc,void * arg0,void * arg1);

/**
 * The handle of the event SResume  at the  session state of Connected.
 *
 *   \param  hc  a wsp instance handle.
 *   \param   arg0 unused parameter now;
 *   \param   arg1 unused parameter now.
 *   \return
 */
 void fnWSP_SResume_Connected(void *hc,void * arg0,void * arg1);

/**
 * The handle of the event InvokeInd  at the  session state of Connected.
 *
 *   \param  hc  a wsp instance handle.
 *   \param   arg0 unused parameter now;
 *   \param   arg1 unused parameter now.
 *   \return
 */
 void fnWSP_InvokeInd_Connected(void *hc,void * arg0,void * arg1);

/**
 * The handle of the event ResultInd  at the  session state of Connected.
 *
 *   \param  hc  a wsp instance handle.
 *   \param   ctl the MCB;
 *   \param   arg1 unused parameter.
 *   \return
 */
 void fnWSP_ResultInd_Connected(void *hc,void * ctl,void * arg1);

/**
 * The handle of the event InvokeCnf  at the  session state of Connected.
 *
 *   \param  hc  a wsp instance handle.
 *   \param   ctl the MCB;
 *   \param   arg1 unused parameter.
 *   \return
 */
 void fnWSP_InvokeCnf_Connected(void *hc,void * ctl,void * arg1);

/**
 * The handle of the event AbortInd  at the  session state of Connected.
 *
 *   \param  hc  a wsp instance handle.
 *   \param   ctl the MCB;
 *   \param   arg1 unused parameter.
 *   \return
 */
 void fnWSP_AbortInd_Connected(void *hc,void * ctl,void * arg1);

/**
 * The handle of the event SDisconnect at the session state of Suspended.
 *
 *   \param  hc  a wsp instance handle.
 *   \param   arg0 unused parameter now;
 *   \param   arg1 unused parameter now.
 *   \return
 */
 void fnWSP_SDisconnect_Suspended(void *hc,void * arg0,void * arg1);

/**
 * The handle of the event DISCONNECT at the session state of Suspended.
 *
 *   \param  hc  a wsp instance handle.
 *   \param   arg0 unused parameter now;
 *   \param   arg1 unused parameter now.
 *   \return
 */
 void fnWSP_Disconnect_Suspended(void *hc,void * arg0,void * arg1);

/**
 * The handle of the event SResume  at the  session state of Suspended.
 *
 *   \param  hc  a wsp instance handle.
 *   \param   arg0 unused parameter now;
 *   \param   arg1 unused parameter now.
 *   \return
 */
 void fnWSP_SResume_Suspended(void *hc,void * arg0,void * arg1);

/**
 * The handle of the event: InvokeInd in the state of Session CONNECTED.
 *
 *   \param  hc  a wsp instance handle.
 *   \param   arg0 unused parameter now;
 *   \param   arg1 unused parameter now.
 *   \return
 */
 void fnWSP_InvokeInd_Suspended(void *hc,void * arg0,void * arg1);

/**
 * The handle of the event InvokeCnf  at the  session state of Suspended.
 *
 *   \param  hc  a wsp instance handle.
 *   \param   arg0 unused parameter now;
 *   \param   arg1 unused parameter now.
 *   \return
 */
 void fnWSP_InvokeCnf_Suspended(void *hc,void * arg0,void * arg1);

/**
 * The handle of the event AbortInd  at the  session state of Suspended.
 *
 *   \param  hc  a wsp instance handle.
 *   \param   arg0 unused parameter now;
 *   \param   arg1 unused parameter now.
 *   \return
 */
 void fnWSP_AbortInd_Suspended(void *hc,void * arg0,void * arg1);

/**
 * The handle of the event SSuspend  at the  session state of Resuming.
 *
 *   \param  hc  a wsp instance handle.
 *   \param   arg0 unused parameter now;
 *   \param   arg1 unused parameter now.
 *   \return
 */
 void fnWSP_SSuspend_Resuming(void *hc,void * arg0,void * arg1);

/**
 * The handle of the event InvokeInd  at the  session state of Resuming.
 *
 *   \param  hc  a wsp instance handle.
 *   \param   arg0 unused parameter now;
 *   \param   arg1 unused parameter now.
 *   \return
 */
 void fnWSP_InvokeInd_Resuming(void *hc,void * arg0,void * arg1);

/**
 * The handle of the event Result.Ind   at the session state of Resuming.
 *
 *   \param  hc  a wsp instance handle.
 *   \param   arg0 unused parameter now;
 *   \param   arg1 unused parameter now.
 *   \return
 */
 void fnWSP_ResultInd_Resuming(void *hc,void * arg0,void * arg1);

/**
 * The handle of the event InvokeCnf  at the  session state of Resuming.
 *
 *   \param  hc  a wsp instance handle.
 *   \param   arg0 unused parameter now;
 *   \param   arg1 unused parameter now.
 *   \return
 */
 void fnWSP_InvokeCnf_Resuming(void *hc,void * arg0,void * arg1);

/**
 * The handle of the event   at the  session state of Resuming.
 *
 *   \param  hc  a wsp instance handle.
 *   \param   ctl the MCB;
 *   \param   arg1 unused parameter.
 *   \return
 */
 void fnWSP_AbortInd_Resuming(void *hc,void * arg0,void * arg1);

/**
 * Defult WSP handler
 *
 *   \param  hc  a wsp instance handle.
 *   \param   arg0 unused parameter now;
 *   \param   arg1 unused parameter now.
 *   \return
 */
 void fnWSP(void *hc,void * agr0,void *arg1);

/**
 * The handle of the event SConfirmedPush at the session state of Connected
 *
 *   \param  hc  a wsp instance handle.
 *   \param   arg0 unused parameter now;
 *   \param   arg1 unused parameter now.
 *   \return
 */
 void fnWSP_SPush_InvokeInd_Connected(void *hc,void * arg0,void * arg1);

#ifdef __cplusplus
}
#endif

#endif /* __WSP_H__ */

