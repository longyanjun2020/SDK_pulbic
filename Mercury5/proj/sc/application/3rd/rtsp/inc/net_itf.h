/**
 * @file    net_itf.h
  */
#ifndef __NET_ITF_H__
#define __NET_ITF_H__

/*=============================================================*/
// include
/*=============================================================*/
#include "ven_std.h"
#include "cus_msg.hc"
#include "bufobj.h"
/*=============================================================*/
// types define
/*=============================================================*/


typedef void* NetItfIndex;
typedef u16 NetItf_Ret;

typedef struct _BufferBlock{
    u8 *pBeginPos;
    u32 nLen;
    bool bUsed;
    struct _BufferBlock *pNext;
}BufferBlock;

typedef struct{
    BufferObj_Data BufObj;
    u32 nBufThreshold;
    u8 nBufBlockCount;
    u8 nFreeBlk;
    BufferBlock *pBlockHead;
}NetItfBufferObj;



typedef void (*NotifyItf_OpenConnectCB)(NetItfIndex NetItfIdx, bool bSuccess,void* pUserdata);
typedef void (*NotifyItf_CloseConnectCB)(NetItfIndex NetItfIdx, bool bSuccess,void* pUserdata);
typedef void (*NotifyItf_SendCB)(NetItfIndex NetItfIdx, bool bSuccess, void* pUserdata);
typedef NetItf_Ret (*NotifyItf_CheckPacket)(NetItfIndex NetItfIdx, u8 *pData, u32 nLen, void* pUserdata);
typedef void (*NotifyItf_NotifyDatatoOwner)(NetItfIndex NetItfIdx, u8 *DataBuf, u32 DataLen, void* pUserdata);
typedef u32 (*NotifyItf_DataParser)(NetItfIndex NetItfIdx, u8 *pData, u32 nLen, void* pUserdata);
typedef void (*NotifyItf_FetchData)(NetItfIndex NetItfIdx, BufferObj *BufObj, u32 *pLen, void* pUserdata);


typedef NotifyItf_NotifyDatatoOwner NotifyItf_ProcessPacket;


typedef struct{
NotifyItf_CheckPacket pfCheckPacket;
NotifyItf_ProcessPacket pfProcessPacket;
NotifyItf_NotifyDatatoOwner pfNotifyData;
NotifyItf_FetchData pfFetchData;
}Data_Notify_Interface_t;

typedef struct{
NotifyItf_OpenConnectCB  pfOpenConnectcb;
NotifyItf_CloseConnectCB    pfCloseConnectcb;
NotifyItf_SendCB  pfSendcb;
NotifyItf_DataParser pfParser;
}Network_Notify_Interface_t;


typedef struct{
    ConnectionObj_Data ConnectObj;
    Network_Notify_Interface_t tNotifyItf;
    void *pHead;
}NetItfConnectObj;


enum{
    NETITF_SUCCESS,
    NETITF_CLOSING,
    NETITF_OPENNING,
    NETITF_SENDING,
    NETITF_NO_INSTANCE,
    //---Check packet use only----
    NETITF_KEEP_PACKET,
    NETITF_DROP_PACKET,
    NETITF_TRANSFER_ALL_PACKET,
    NETITF_FLUSH_ALL_PACKET,
    //-------------------------
    NETITF_FAIL,

};


void NetItfInit(void);
NetItf_Ret NetItfNew(NetItfIndex *pIdx, NetItfBufferObj* pBufObj, NetItfConnectObj *pConnectObj, Data_Notify_Interface_t *ptNotifyItf, void *pUserData);
NetItf_Ret NetItfDelete(NetItfIndex nIdx);
u32 NetItf_Get_Ven_Handle(void);
void NetItf_Free_Ven_Handle(void);
//TCP: Server IP and port, UDP: Local IP and port, pfopencb is need only by TCP
NetItf_Ret NetItfOpenConnection(NetItfIndex NetItfIdx, TRANS_PROTOCOL_E eProtocol, s8* pAddr, u16 nPort);
NetItf_Ret NetItfCloseConnection(NetItfIndex NetItfIdx);
NetItf_Ret NetItfSendRequest(NetItfIndex NetItfIdx, u8 *Cmd, s32 sCmdLen, s8* pDstAddr, u16 nDstPort);
NetItf_Ret NetItf_CreateConnectionObj(NetItfConnectObj **ppConnectObj, Network_Notify_Interface_t *ptNotifyItf);
void NetItf_DestroyConnectionObj(NetItfConnectObj *pConnectObj);
NetItf_Ret NetItf_CreateBufObj(u32 nBufThreshold, NetItfBufferObj **ppBufObj);
void NetItf_DestroyBufObj(NetItfBufferObj *pBufObj);
NetItf_Ret NetItf_NotifyDataDone(NetItfIndex NetItfIdx, u8 *pData);
void NetItfForceNotifyData(NetItfIndex NetItfIdx);
NetItf_Ret NetItfCheckBufferSize(NetItfIndex NetItfIdx, u32 IncomingDataLen);

#endif //__NET_ITF_H__
