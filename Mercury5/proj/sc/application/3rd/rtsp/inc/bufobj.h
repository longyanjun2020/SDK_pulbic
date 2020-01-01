/**
 * @file    bufobj.h
  */
#ifndef __BUFOBJ_H__
#define __BUFOBJ_H__

/*=============================================================*/
// include
/*=============================================================*/
#include "ven_std.h"
#include "ven_socket.h"
/*=============================================================*/
// types define
/*=============================================================*/

#define MAX_NUM_NETINTERFACE 10


typedef void* ConnectionObj;

typedef u32 BufObj_Ret;

enum{
    BUFOBJ_SUCCESS ,
    BUFOBJ_FAIL,
};

typedef enum{
    TCP_PROTOCOL = 1,
    UDP_PROTOCOL,
    TCP_INTERLEAVING,
}TRANS_PROTOCOL_E;

typedef struct{
    u32 nBufLength;
    u32 nHeaderSize;
    u32 nDataOffset;
    u8 *pDataBeginPos;
}BufferObj_Data;

typedef BufferObj_Data* BufferObj;
typedef void (*Notify_OpenConnectCB)(void* pUserdata, bool bSuccess);
typedef void (*Notify_CloseConnectCB)(void* pUserdata, bool bSuccess);
typedef void (*Notify_SendCB)(void* pUserdata, bool bSuccess);
typedef void (*Notify_RecvCB)(void* pUserdata, u8 *pData, u32 nLen);

typedef struct{
Notify_OpenConnectCB  pfOpenConnectcb;
Notify_CloseConnectCB    pfCloseConnectcb;
Notify_SendCB  pfSendcb;
Notify_RecvCB pfRecvcb;
}ConnectionObj_Notify;

typedef struct{
    ven_socket_t VenSocket;
    ConnectionObj_Notify tNotifyItf;
    u16 nStatus;
}ConnectionObj_Data;

BufObj_Ret BufferObj_AllocBuf(u32 nAllocSize, BufferObj pBufObj);
BufObj_Ret BufferObj_AllocBufEx(u32 nAllocSize, BufferObj pBufObj, u32 nHeaderSize);
void BufferObj_FreeBuf(BufferObj BuffObj);
BufObj_Ret BufferObj_GetBufSize(BufferObj BuffObj, u32 *pLen, bool bIncludeHeader);
BufObj_Ret BufferObj_GetBufRemainingSize(BufferObj BuffObj, u32 *pLen);
BufObj_Ret BufferObj_GetDataLength(BufferObj BuffObj, u32 *pLen);
BufObj_Ret BufferObj_GetBufBeginPos(BufferObj BuffObj, u8 **ppPos);
BufObj_Ret BufferObj_GetBufBeginPosEx(BufferObj BuffObj, u8 **ppPos , bool bIncludeHeader);
BufObj_Ret BufferObj_SetBufBeginPos(BufferObj pBufObj, u8 *pNewPos, u32 nSize);
BufObj_Ret BufferObj_SetBufBeginPosEx(BufferObj pBufObj, u8 *pNewPos, u32 nSize, u32 nHeaderSize);
void BufferObj_FlushData(BufferObj BuffObj);
BufObj_Ret BufferObj_FetchData(BufferObj BuffObj, u8 *pDstPos, u32 nLen);
BufObj_Ret BufferObj_FeedData(BufferObj BuffObj, u8 *pData, u32 nDataLen, bool bAutoRelloc);
BufObj_Ret BufferObj_FetchAndFeedData(BufferObj BuffObjDst, BufferObj BuffObjSrc, u32 nDataLen, bool bAutoRelloc);
BufObj_Ret BufferObj_CopyData(BufferObj BuffObj, u8 *pDstPos, u32 nLen);
BufObj_Ret BufferObj_CleanBufBeginPos(BufferObj pBufObj);
BufObj_Ret BufferObj_DropData(BufferObj BuffObj, u32 nLen);

BufObj_Ret ConnectObj_Add(ConnectionObj ConnectObj);
void ConnectObj_Remove(ConnectionObj ConnectObj);
BufObj_Ret ConnectObj_SendRequest(ConnectionObj pConnectObj, u8 *Cmd, s32 sCmdLen, s8* pDstAddr, u16 nDstPort, Notify_SendCB pFuncCB);
BufObj_Ret ConnectObj_OpenConnection(ConnectionObj pConnectObj, TRANS_PROTOCOL_E eProtocol, s8* pAddr, u16 nPort, Notify_OpenConnectCB pOpenCB, Notify_RecvCB pRecvCB);
BufObj_Ret ConnectObj_CloseConnection(ConnectionObj pConnectObj, Notify_CloseConnectCB pFuncCB);
BufObj_Ret ConnectObj_IsSocketEqual(ConnectionObj pConnectObj, ven_socket_t *pSkt);
void ConnectObj_Init(void);


#endif //__BUFOBJ_H__

