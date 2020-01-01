
#ifndef __WSP_SOCK2_H__
#define __WSP_SOCK2_H__

#include <ncc_types.h>
#include <wsp_pub.h>
#include <wsp_conf.h>
#include <wsp_sock.h>
#include <wsp_wdp.h>
#include <wsp_method.h>

typedef struct T_WSP_CTXT{
    int8_t      GatewayIp[16];  /**< WAP gateway ip address */
    int32_t     SessionType;    /**< WAP gateway port number. it has same value with the wsp session type */
    int32_t     SendCapsBuf[MAX_CAPS_BUF_SIZE];/**< Capability of a WSP session */
    int32_t     Mom;            /**< Maximum Outstanding Method Requests */
    T_WAP_SIndex * GSession;    /**< Session handler */
    int8_t *    ConnectHeader;  /**< Request header */
    T_TidPeer * TidPeerHead;    /**< Ready queue head */
    T_TidPeer * TidPeerTail;    /**< Ready queue tail */
    T_TidPeer *   AppDataHead;  /**< Active queue head */
    T_TidPeer *   AppDataTail;  /**< Active queue tail */
    int8_t      MaxRcr;         /**< Maximum retransmit number */
    int8_t      profWarning;    /**< x-profile-warning tag */
    int8_t      WaitConnectTag; /**< WAP gateway connect tag of CO session.If connected, set it to 1,else set it to 0 */
    int8_t      WaitSConnectTag;/**< WAP gateway connect tag of CO session with WTLS.If connected, set it to 1,else set it to 0 */
    uint16_t     SendPacketLen;  /**< Length of each sending packet  */
    uint16_t    LastUsedTid;    /**< Last used tid */

#ifdef WAP_USER_CANCEL_ENABLE
    int32_t StopByUser;         /**< Stop tag when you use wap in the block way */
#endif

    int32_t     TimeOut;                /**< Timer interval for retransmition */
    uint32_t    LastWaitTick;           /**< Last timer */
    struct T_WTP_Tid   *  TidCache;     /**< Cached tid list */
    struct T_WTP_Timer * TimerList;     /**< Timer list */
    int32_t Error;                      /**< Error number */

    struct T_WDP_Addr2Sap * AddrMap;    /**< Address List */
    struct T_WAP_MSG * ConnectPduCopy;  /**< Copy of Connect PDU */
    uint8_t *   RecvBuf;                /**< WDP receiving buffer */
    int32_t RecvDataCount;              /**< Received data count of one session */
    int32_t SendDataCount;              /**< Sent data count of one session */
    fnWSP_AuthGetFunc AuthGetFunc;      /**< Get user name and password.store in unencoded
                                          string format.we create our own one to get string
                                          format user and password */
    fnWSP_AuthAlertFunc  AuthAlertFunc; /**< Callback function to alert upper layer about authentication
                                          event,not needed because we will call  AuthGetFunc to let user
                                          enter the information */
    T_WSP_AUTH_LIST * authList;/**< Saved Authentication list */
}T_WSP_CTXT;

#endif /* __WSP_SOCK2_H__ */

