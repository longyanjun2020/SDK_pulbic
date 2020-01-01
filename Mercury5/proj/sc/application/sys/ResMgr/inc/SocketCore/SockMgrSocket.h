#ifndef __SOCKMGR_SOCKET_H__
#define __SOCKMGR_SOCKET_H__

#include "SockMgrRes.h"
#include "SockMgrSocketItf.h"

/*=============================================================*/
// Include Files
/*=============================================================*/

/*=============================================================*/
// Macro Definitions
/*=============================================================*/

#define SOCKMGR_PROXYADDRESS_LEN	(4)

/*=============================================================*/
// Type Declarations
/*=============================================================*/
typedef struct _SockMgr_Socket_t_
{
	/// Information for socket manager
	SockMgr_Res_t sRes;
	SockMgr_DataLinkHdl_t hParentDataLink;
	bool bIsNonExpired;
	bool bIsWaitRsp;
	ResMgr_AppId_e eAp; /// fill when create
                        /// Use for check old or new sdk
	bool bUseExtAPI;    /// fill when create
	u8 uAttribute;      /// fill when create
    /// Information for socket session 
    u8 server_address[SOCKMGR_PROXYADDRESS_LEN];
    u16 server_port;        
    u16 client_port;        
    s32 address_len;        
    u8 socket_type;        
	u8 socket_id;          
	u8 Ti;
    u8  send_ready_ind;     /// MSL_SEND_READY_IND, 1 for ready, 0 for not ready 
    u8  create_socket_rsp;  /// MSL_CREATE_SOCKET_RSP, 1 for socket created, 0 for negative 
    s16 err_no;             /// errno 
    u32 src_addr;  
    u16 src_port;           
	u8 remote_close;       
	u8 socket_retry; 
    /// Information for socket (winsock.c)
	u8 sdk_ver;
	u16 data_idx;
	u16 data_len;
	void *pReceiveInd;
	void *pData[SOCKETREQ_TOTAL_NO]; 
	void *pCBFunc[SOCKETREQ_TOTAL_NO];
	void *hConn;
	void *pvInterruptedCmd;
    void *pvSocketWrapper;
    bool bStopRetry;
#ifndef RES_MGR_STANDALONE_DEBUG
	void *fsmPtr;            
#endif
}SockMgr_Socket_t;

/*=============================================================*/
// Function Declarations
/*=============================================================*/

#endif/* __SOCKMGR_SOCKET_H__ */
