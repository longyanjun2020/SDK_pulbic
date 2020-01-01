#ifndef __VML_FAKE_HEADER_H__
#define __VML_FAKE_HEADER_H__


//////////////////////////////////////////////////////////////////////////

/**
* \brief Constant :  VM_VML_MSL_AUTH_STRING_LEN
* Max length for authentication name and password strings
*/
#define VM_VML_MSL_AUTH_STRING_LEN    32


/**
* \brief Constant :  VM_VML_MSL_IP_ADDRESS_MAX_SIZE
* Length for an IP V4 address (like 123.56.34.22)
*/
#define VM_VML_MSL_IP_ADDRESS_MAX_SIZE 4


/**
* \brief Constant :  VM_VML_MSL_MAX_SOCKET_CTXT
* Max number of socket context
*/
#define VM_VML_MSL_MAX_SOCKET_CTXT     15   /* 4 */


/**
* \brief Constant :  VM_VML_CALLED_NB_SIZE_MAX
* Size max of data CALLED party
*/
#define VM_VML_CALLED_NB_SIZE_MAX  22

//////////////////////////////////////////////////////////////////////////

#define VM_VML_MSG_MSL_STATUS_IND (0X12345678)

//////////////////////////////////////////////////////////////////////////

typedef enum
{
	VM_VML_MSL_UDP_CLIENT, /**< Client socket, UDP mode */
	VM_VML_MSL_TCP_CLIENT, /**< Client socket, TCP mode */
	VM_VML_MSL_UDP_SERVER, /**< Server socket, UDP mode */
	VM_VML_MSL_TCP_SERVER  /**< Server socket, TCP mode */
}
vm_VmlMslSocketType_t;

typedef enum
{
	VM_VML_MSL_RESULT_OK,                          /**< Operation OK */
	VM_VML_MSL_RESULT_DEFAULT,                     /**< Cause not defined */
	VM_VML_MSL_RESULT_NB_MAX_CTXT_REACHED,         /**< Nb max MSL context reached */
	VM_VML_MSL_RESULT_DATA_LINK_ALREADY_ACTIVATED, /**< CSD/GPRS DATA com already active */
	VM_VML_MSL_RESULT_COM_CLOSE_BY_PEER,           /**< Communication closed by peer */
	VM_VML_MSL_RESULT_DATA_LINK_KO,                /**< Data link can't be activated */
	VM_VML_MSL_RESULT_IP_ERROR,                    /**< IP setup or sock opening failure */
	VM_VML_MSL_RESULT_NO_MORE_SOCKET,              /**< No more socket available */
	VM_VML_MSL_RESULT_BAD_SOCKET_ID,               /**< Bad socket identifier */
	VM_VML_MSL_RESULT_CONTCP_CLOSE,                /**< TCP connection to distant closed */
	VM_VML_MSL_RESULT_DNS_ERROR,                   /**< DNS error */
	VM_VML_MSL_RESULT_GPRS_NOT_PRESENT,            /**< GPRS feature not present */
	VM_VML_MSL_RESULT_KO_WRONG_STATE,               /**< Wrong MSL state */
	VM_VML_MSL_RESULT_KO_NO_MSL_CONTEXT_FOUND,     /**< Cannot find corresponding msl context */
	VM_VML_MSL_RESULT_SET_SOCKET_OPTION_ERROR,    /**< Set socket option failure */
	VM_VML_MSL_RESULT_GET_SOCKET_OPTION_ERROR,    /**< Get socket option failure */
	VM_VML_MSL_RESULT_SHUTDOWN_SOCKET_ERROR,      /**< Shutdown socket failure */
	VM_VML_MSL_RESULT_CONTCP_SYN_TIMEOUT,
	VM_VML_MSL_RESULT_CONTCP_AGAIN,
	VM_VML_MSL_RESULT_WIFI_LEASE_TIMEOUT,
	VM_VML_MSL_RESULT_CONTCP_NO_BUFFER_ERROR,
	VM_VML_MSL_RESULT_NUM,
}vm_VmlMslResult_t;

/**
* \brief Bearer service speed in GSM 07.07 (Mobile Originated).
*
* Values defined in 3GPP TS 07.07 ch 6.7 (Select Bearer Service Type +CBST)
*/
typedef enum
{
	VM_VML_CBST_SPEED_AUTO_BAUD  = 0 , /**< autobauding (automatic selection of the speed) */
	VM_VML_CBST_SPEED_V21_300    = 1 , /**< 300 bps (V.21) */
	VM_VML_CBST_SPEED_V22_1200   = 2 , /**< 1200 bps (V.22) */
	VM_VML_CBST_SPEED_V23_1200   = 3 , /**< 1200/75 bps (V.23) */
	VM_VML_CBST_SPEED_V22b_2400  = 4 , /**< 2400 bps (V.22bis) */
	VM_VML_CBST_SPEED_V26t_2400  = 5 , /**< 2400 bps (V.26ter) */
	VM_VML_CBST_SPEED_V32_4800   = 6 , /**< 4800 bps (V.32) */
	VM_VML_CBST_SPEED_V32_9600   = 7 , /**< 9600 bps (V.32) */
	VM_VML_CBST_SPEED_NET_SPEC   = 8 , /**<  */
	VM_VML_CBST_SPEED_V32b_7200  = 9 , /**<  */
	VM_VML_CBST_SPEED_V32b_12000 = 10, /**<  */
	VM_VML_CBST_SPEED_V32b_14400 = 11, /**<  */
	VM_VML_CBST_SPEED_V34_9600   = 12, /**< 9600 bps (V.34) */
	VM_VML_CBST_SPEED_V34_12000  = 13, /**<  */
	VM_VML_CBST_SPEED_V34_14400  = 14, /**< 14400 bps (V.34) */
	VM_VML_CBST_SPEED_V34_19200  = 15, /**< 19200 bps (V.34) */
	VM_VML_CBST_SPEED_V34_28800  = 16, /**< 28800 bps (V.34) */
	VM_VML_CBST_SPEED_V110_300   = 65, /**< 300 bps (V.110) */
	VM_VML_CBST_SPEED_V110_1200  = 66, /**< 1200 bps (V.110) */
	VM_VML_CBST_SPEED_V110_2400  = 68, /**< 2400 bps (V.110 or X.31 flag stuffing) */
	VM_VML_CBST_SPEED_V110_4800  = 70, /**< 4800 bps (V.110 or X.31 flag stuffing) */
	VM_VML_CBST_SPEED_V110_9600  = 71, /**< 9600 bps (V.110 or X.31 flag stuffing) */
	VM_VML_CBST_SPEED_V110_12000 = 74, /**< 12000 bps (V.110 or X.31 flag stuffing) */
	VM_VML_CBST_SPEED_V110_14400 = 75, /**< 14400 bps (V.110 or X.31 flag stuffing) */
	VM_VML_CBST_SPEED_V110_19200 = 79, /**< 19200 bps (V.110 or X.31 flag stuffing) */
	VM_VML_CBST_SPEED_V110_38400 = 81, /**< 38400 bps (V.110 or X.31 flag stuffing) */
} vm_VmlCbstSpeed_t;


/**
* \brief Bearer service name.
*
* Values defined in 3GPP TS 07.07 ch 6.7 (Select Bearer Service Type +CBST)
*/
typedef enum
{
	VM_VML_CBST_NAME_ASYNC_MODEM = 0,  /**< data circuit asynchronous */
	VM_VML_CBST_NAME_SYNC_MODEM  = 1,  /**< data circuit synchronous */
	VM_VML_CBST_NAME_PAD_ACCESS  = 2,  /**< PAD Access (asynchronous) */
	VM_VML_CBST_NAME_PACKET_ACC  = 3,  /**< Packet Access (synchronous)  */
} vm_VmlCbstName_t;


/**
* \brief Bearer service Connection element : (Not)Transparet_Preferred/Only.
*
* Values defined in 3GPP TS 07.07 ch 6.7 (Select Bearer Service Type +CBST)
*/
typedef enum
{
	VM_VML_CBST_CE_T_ONLY       = 0,   /**< transparent */
	VM_VML_CBST_CE_NT_ONLY      = 1,   /**< non-transparent */
	VM_VML_CBST_CE_T_PREFERRED  = 2,   /**< both, transparent preferred */
	VM_VML_CBST_CE_NT_PREFERRED = 3,   /**< both, non-transparent preferred */
} vm_VmlCbstCe_t;

/**
* \brief Data compression mode : None or V.42bis
*/
typedef enum
{
	VM_VML_COM_COMPRESS_NONE = 0,      /**< No compression */
	VM_VML_COM_COMPRESS_V42B = 2,      /**< V.42bis compression */
} vm_VmlModcCompress_t;

typedef enum
{
	VM_VML_MSL_DATA_ANALOGUE, /**< Analogue */
	VM_VML_MSL_DATA_ISDN      /**< ISDN */
}vm_VmlMslDataTypeCall_t;

typedef enum
{
	VM_VML_MSL_DATA_LINK_CSD, /**< CSD data com */
	VM_VML_MSL_DATA_LINK_GPRS, /**< GPRS data com */
	VM_VML_MSL_DATA_LINK_WIFI, /**< GPRS data com */
}vm_VmlMslDataLinkType_t;

typedef struct
{
	vm_VmlCbstSpeed_t    Speed;     /**< Speed */
	vm_VmlCbstCe_t       Ce;        /**< T/NT/Tpref/NTpref */
	vm_VmlCbstName_t     Name;      /**< Bearer service name */
	vm_VmlModcCompress_t Compress;  /**< Data compression */
}vm_VmlMslDataBearer_t;

//////////////////////////////////////////////////////////////////////////

typedef struct
{
	u32						UserData ;
	u8                      ClientId;
	u8                      Ti;
	vm_VmlMslDataTypeCall_t DataTypeCall;
	vm_VmlMslDataBearer_t   DataBearer;
	u8                      DnsServer[VM_VML_MSL_IP_ADDRESS_MAX_SIZE];
	u8 						DnsServer2[VM_VML_MSL_IP_ADDRESS_MAX_SIZE];
	ascii                   ServerPhoneNb[VM_VML_CALLED_NB_SIZE_MAX];
	ascii                   Name[VM_VML_MSL_AUTH_STRING_LEN];
	ascii                   Passwd[VM_VML_MSL_AUTH_STRING_LEN];
	ascii                   Apn[VM_VML_MSL_AUTH_STRING_LEN];
	u8                      MsIpAddress[VM_VML_MSL_IP_ADDRESS_MAX_SIZE];
	u8 						MsIpSubMask[VM_VML_MSL_IP_ADDRESS_MAX_SIZE]; 
	u8 						GatewayAddress[VM_VML_MSL_IP_ADDRESS_MAX_SIZE];
	vm_VmlMslDataLinkType_t DataLinkType;
}vm_VmlMslCreateDataLinkReq_t;

typedef struct
{
	u32 UserData ;
	u8 ClientId;
	u8 Ti;
	vm_VmlMslResult_t Result;
	u32 LocalIpAddr;
}vm_VmlMslCreateDataLinkRsp_t;

typedef struct
{
	u32 UserData ;
	u8 ClientId;
	u8 Ti;
}vm_VmlMslCloseDataLinkReq_t;

typedef struct
{
	u32					  UserData ;
	u8                    ClientId;
	u8                    Ti;
	vm_VmlMslResult_t     Result;
}vm_VmlMslCloseDataLinkRsp_t;

typedef struct
{
	u32					  UserData ;
	u8                    ClientId;
	u8                    Ti;
	vm_VmlMslSocketType_t SocketType;
	u8                    Pad;
	u16                   LocalPort;
	u16                   ServerPort;
	u8    ServerAddress[VM_VML_MSL_IP_ADDRESS_MAX_SIZE];
}vm_VmlMslCreateSocketReq_t;

typedef struct
{
	u32		UserData ;
	u8      ClientId;
	u8      Ti;
	vm_VmlMslResult_t    Result;
	u8      SocketId;
	u8      Pad;
	u16    ClientPort;
}vm_VmlMslCreateSocketRsp_t;

typedef struct
{
	u32 UserData;
	u8 ClientId;
	u8 SocketId;
}vm_VmlMslCloseSocketReq_t;

typedef struct
{
	u32               UserData ;
	u8                ClientId;
	u8                SocketId;
	vm_VmlMslResult_t  Result;
}vm_VmlMslCloseSocketRsp_t;

typedef struct
{
	u32               UserData;
	u8                ClientId;
	u8                SocketId;
	vm_VmlMslResult_t Status;
	u8                Pad;
	u32               LocalIpAddr;
}vm_VmlMslStatusInd_t;

#define VML_MSG_COL	\
	VML_IN_MSG_COL	\
	VML_OUT_MSG_COL	\

#ifdef __3G_RIL_MMI__
	MSG_ITEM(SM_IP_CREATE_DATA_LINK_REQ, VmlMslRecVmlMslCreateDataLinkReq)	\
	MSG_ITEM(SM_IP_CLOSE_DATA_LINK_REQ, VmlMslRecVmlMslCloseDataLinkReq)	\
	MSG_ITEM(SM_IP_SOCKET_REQ ,VmlMslRecVmlMslCreateSocketReq)	\
	MSG_ITEM(SM_IP_SOCKET_CLOSE_REQ, VmlMslRecVmlMslCloseSocketReq)	\
	MSG_ITEM(VM_VML_MSG_MSL_DESTROY_THREAD_REQ,cbDestroyVMLTask)

#define VML_OUT_MSG_COL	\
	MSG_ITEM(SM_IP_CREATE_DATA_LINK_CNF, VmlMslDscCreateDataLinkRsp)	\
	MSG_ITEM(SM_IP_CLOSE_DATA_LINK_CNF, VmlMslDscCloseDataLinkRsp)	\
	MSG_ITEM(SM_IP_SOCKET_CNF, VmlMslDscCreateSocketRsp)	\
	MSG_ITEM(SM_IP_SOCKET_CLOSE_CNF, VmlMslDscCloseSocketRsp)	\
	MSG_ITEM(VM_VML_MSG_MSL_DESTROY_THREAD_RSP, NULL)
#else //__3G_RIL_MMI__
#define VML_IN_MSG_COL	\
	MSG_ITEM(VM_VML_MSG_MSL_CREATE_DATA_LINK_REQ, VmlMslRecVmlMslCreateDataLinkReq)	\
	MSG_ITEM(VM_VML_MSG_MSL_CLOSE_DATA_LINK_REQ, VmlMslRecVmlMslCloseDataLinkReq)	\
	MSG_ITEM(VM_VML_MSG_MSL_CREATE_SOCKET_REQ ,VmlMslRecVmlMslCreateSocketReq)	\
	MSG_ITEM(VM_VML_MSG_MSL_CLOSE_SOCKET_REQ, VmlMslRecVmlMslCloseSocketReq)	\
	MSG_ITEM(VM_VML_MSG_MSL_DESTROY_THREAD_REQ,cbDestroyVMLTask)

#define VML_OUT_MSG_COL	\
	MSG_ITEM(VM_VML_MSG_MSL_CREATE_DATA_LINK_RSP, VmlMslDscCreateDataLinkRsp)	\
	MSG_ITEM(VM_VML_MSG_MSL_CLOSE_DATA_LINK_RSP, VmlMslDscCloseDataLinkRsp)	\
	MSG_ITEM(VM_VML_MSG_MSL_CREATE_SOCKET_RSP, VmlMslDscCreateSocketRsp)	\
	MSG_ITEM(VM_VML_MSG_MSL_CLOSE_SOCKET_RSP, VmlMslDscCloseSocketRsp)	\
	MSG_ITEM(VM_VML_MSG_MSL_DESTROY_THREAD_RSP, NULL)
#endif //__3G_RIL_MMI__

#undef  MSG_ITEM
#define MSG_ITEM(MSG,CBFUC) MSG,
typedef enum
{
	VM_VML_MSG_MSL_BEGIN = 0,
	VML_MSG_COL
	VM_VML_MSG_MSL_END,
}Vml_Msg_e;

void Mserv_Mic_NetRecMslCreateDataLinkRsp(const void *PtrMsgRec);
void Mserv_Mic_NetRecMslCloseDataLinkRsp(const void *PtrMsgRec);
void Mserv_Mic_NetRecMslCreateSocketRsp(const void *PtrMsgRec);
void Mserv_Mic_NetRecMslCloseSocketRsp(const void *PtrMsgRec);

void* MakeVmlReqCreateDataLink
(
  u8 uClientID,
  u8 (*puDNSServer)[VM_VML_MSL_IP_ADDRESS_MAX_SIZE],
  u8 (*puServerNb)[VM_VML_CALLED_NB_SIZE_MAX],
  u8 (*puName)[VM_VML_MSL_AUTH_STRING_LEN],
  u8 (*puPasswd)[VM_VML_MSL_AUTH_STRING_LEN],
  u8 (*puAPN)[VM_VML_MSL_AUTH_STRING_LEN],
  u8 (*puIpAddr)[VM_VML_MSL_IP_ADDRESS_MAX_SIZE],
  vm_VmlMslDataLinkType_t eDataLink,
  void *pvUserData
);
void* MakeVmlReqCloseDataLink(void);
void* MakeVmlReqCreateSocket
(
  u8 uClientId,
  u8 uTi,
  vm_VmlMslSocketType_t SocketType,
  u16 uLocalPort,
  u16 uServerPort,
  u8  (*puServerAddress)[VM_VML_MSL_IP_ADDRESS_MAX_SIZE],
  void *pvUserData
);
void* MakeVmlReqCloseSokcet(void);

void* MakeVmlRspCreateDataLink(u32 uUserData, vm_VmlMslResult_t uResult);
void* MakeVmlRspCloseDataLink(u32 uUserData, vm_VmlMslResult_t uResult);
void* MakeVmlRspCreateSocket(u32 uUserData, vm_VmlMslResult_t uResult);
void* MakeVmlRspCloseSocket(u32 uUserData, vm_VmlMslResult_t uResult);

void *MakeVmlIndStatusChange(u32 uUserData, u8 uSocketId, vm_VmlMslResult_t uResult);

//////////////////////////////////////////////////////////////////////////

#endif/* __VML_FAKE_HEADER_H__ */
