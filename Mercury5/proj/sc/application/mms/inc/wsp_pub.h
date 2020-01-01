
#ifndef __WSP_PUB_H__
#define __WSP_PUB_H__

#include <ncc_types.h>
#include <wsp_conf.h>
#include <wsp_osapi.h>

#ifdef __cplusplus
extern "C"{
#endif

/*Caculate array length*/
#define WAP_ARRAY_LEN(ch) sizeof(ch)/sizeof(ch[0])

typedef struct T_WAP_AddrTuple{
    uint32_t server_ip;  /**< Wap gateway ip address */
    uint32_t client_ip;  /**< Local ip address */
    uint16_t server_port;/**< Wap gateway port number */
    uint16_t client_port;/**< Local port number */
} T_WAP_AddrTuple;

struct Wap_Psn_List{
    uint8_t Resent_psn;        /**< Resent psn */
    uint8_t unUsed[3];
    struct Wap_Psn_List * next;/**< Next element */
};

typedef struct T_WAP_MSG {
    struct T_WAP_MSG * next;/**< Next message */
    uint8_t   *nb_buff;     /**< Data address of a message */
    uint32_t   nb_blen;     /**< Data size of a message*/
    uint8_t   *nb_prot;     /**< Data address of current protocal layer.it will be changed
    accordingly when move from one layer of WAP to another */
    uint32_t   nb_plen;     /**< Data size of current protocal layer */
    T_WAP_AddrTuple addr;   /**< Address tuple*/
    int8_t      is_method;  /**< The packet belong to a method */
    uint8_t     Boundary;   /**< Boundary */
    int16_t    iface;       /**< Boundary */
} * T_WAP_MSG_P;

typedef struct T_WAP_Sar_SegPacketResult{
    uint8_t FirstGroupFinishTag;/**< Indicate if the received packet is the the first group end packet */
    uint8_t RecvTTRTag;         /**< Indicate if receive the TTR packet */
    uint8_t GroupSize;          /**< Packet number of one group */
    uint8_t CurGroupPsn;        /**< Number of last packet of current group */
    uint8_t LastGroupEndNum;    /**< PSN number of end packet of the last received group */
    uint8_t Boundary[3];        /**< Boundary */
    T_WAP_MSG_P Packet[MAX_GROUP_NUMBER_RECV]; /**< Group receiving packet buffer*/
}T_WAP_Sar_SegPacketResult;

typedef struct T_WAP_MCB{
    uint16_t tid;           /**< Transaction ID */
    int8_t  wsp_state;      /**< WSP status */
    int8_t  wtp_state;      /**< WTP status */

    int8_t  tcl;            /**< WTP class type */
    int8_t  aec;            /**< Acknowledgment Expiration Counter */
    int8_t  rcr;            /**< Re-transmission Counter */
    int8_t  tid_verication; /**< TID Verification tag */

    int8_t  tid_new;        /**< Set this Tag when sent or receive a packet with tid_new is seted */
    int8_t  tid_send;       /**< Is the initiator send tidok? */
    int8_t  ack_pdu_send;   /**< Need to send an ack or not */
    int8_t  u_ack;          /**< User Acknowledgement tag */

    int8_t  rid;            /**< Re-transmission tag of received message */
    uint8_t abort_reason;   /**< Method abort reason. fill this element When T_abort.req is called */
    int8_t  abort_type;     /**< Method abort type */
    int8_t  hold_on;        /**< Hold on tag */

    int8_t  is_used;        /**< Is the MCB still used */
    int8_t  need_segment;   /**< For supporting WTP SAR */
    int8_t  con_with_tpi;   /**< Is there TPI header in a PDU */
    uint8_t  psn;           /**< Current packet sequence number */

    uint8_t  copy_psn;      /**< Bak of current sent psn when selective retransmintion is needed */
    uint8_t  last_psn;      /**< Last used psn */
    uint8_t  recv_psn;      /**< Current received psn */
    int8_t  gtr;            /**< GTR symbol */

    int8_t  ttr;            /**< TTR symbol */
    int8_t  SegAck;         /**< Segment Ack tag*/
    int8_t  ReSendSegInv;   /**< For resend packet acorrding to the psn we recieved */
    int8_t  ResendAckCount; /**< Number of resend ACK PDU.used for exception handle */

    int8_t  ErrorTag;       /**< Exception handle tag */
    uint8_t startpsn;       /**< The start psn of the segment data */
    uint8_t  Boundary[2];   /**< Boundary */

    uint8_t * seg_req;      /**< Segment request */
    int32_t   seg_req_size; /**< Lenth of segment_data */
    int32_t   bak_seg_req_size; /**< Lenth of segment_data */
    uint8_t * segment_data; /**< MMS content */
    int32_t segment_size;   /**< Lenth of segment_data */
    int32_t max_group;      /**< Maximum Group */

    /* Added  to support resend seg_invoke */
    uint8_t * copy_segment_data;/**< MMS content  */
    int32_t bak_segment_size;   /**< Lenth of segment_data */
    int32_t copy_segment_size;  /**< Lenth of segment_data */

    struct T_WTP_Timer * timer; /**< WTP timer list */
    T_WAP_MSG_P Result;         /**< Received packet */
    T_WAP_MSG_P resend_data;    /**< Resend packet */

    int32_t RecvDataCount;      /**< Received data count of one request */
    int32_t SendDataCount;      /**< Sending data count of one request */

    struct Wap_Psn_List *ReSendPsnList; /**< Missing packet list when POST method is used */
    T_WAP_Sar_SegPacketResult SegResult;/**< Segmented result */
    struct T_WAP_SessionIndex * psession;/**< Session index handler */
    struct T_WAP_MCB * next;            /**< Next MCB */

} T_WAP_MCB;

typedef struct T_WAP_SCB
{
    int8_t  wsp_state;      /**< WSP state */
    int8_t  enc_ver;        /**< Encoding version */
    uint8_t Boundary[2];    /**< Boundary */
    int32_t  n_methods;     /**< Current active Method number of one session */
    int32_t  n_push;        /**< Current active PUSH number of one session */

    int32_t  set_caps;      /**< Bit map of negotiated capabilities */
    int32_t  client_SDU_size;/**< Maximum Client SDU */
    int32_t  server_SDU_size;/**< Maximum Client SDU */
    int32_t  protocol_options;/**< Protocol options */
    int32_t  MOR_method;    /**< Max outstanding request number of method */
    int32_t  MOR_push;      /**< Max outstanding request number of PUSH */
    T_WAP_AddrTuple  * aliases;/**< Declares a list of alternate addresses for the sender.not used */
    void * extended_methods;/**< Extend method after Capability Negotiation.not used */
    void * header_code_pages;/**< Extend code pages after Capability Negotiation.not used */

    T_WAP_MCB * wsp_mcb;
    struct T_WAP_SessionIndex * psession;
} T_WAP_SCB;

typedef struct T_WAP_SessionIndex{
    uint32_t    session_id; /**< Session ID */
    T_WAP_AddrTuple  addr;  /**< Address Tuple */
    T_WAP_SCB *scb;         /**< Current SCB(session control block) */
    T_WAP_MCB *mcb;         /**< Current SCB(session control block) */

    struct T_WAP_SessionIndex * next;
} T_WAP_SIndex ;

struct T_WAP_EventArray{
    uint32_t len;               /**< The number of machine's state correspond to this event */
    const struct T_WAP_StatFun *element;/**< The base address of T_WAP_StatFun array */
};

typedef void (*T_WAP_Action)(void *hc,void *arg0,void *arg1);

struct T_WAP_StatFun{
    uint32_t state;     /**< The machine's state */
    T_WAP_Action act;   /**< The corressponding function */
};

/**
 * Call this function to create a new WAP message structure and its data buffer.
 *
 *   \param  len     data buffer size of WAP packet.
 *    \return    return pointer to the WAP message structure this function created.
 */
T_WAP_MSG_P fnOS_WapPktAlloc(uint32_t size);

/**
 * Call this function to free the resource spent by WAP message
 *   structure and its data buffer.
 *
 *   \param  pkt   WAP message structure to be freed
 *    \return
 */
void    fnOS_WapPktFree(T_WAP_MSG_P);

/**
 * Convert the IP address in string format to 32bit interger value.
 *   \param  hc  a wsp instance handle.
 *   \param  ipout   the output IP address.
 *   \param  stringin  the input IP address in string format.
 *   \return returns NULL if TRUE, else returns FALSE;
 */
int32_t fnPUB_ParseIp(uint32_t * ipout,int8_t * stringin);

/**
 * Compact a long value to multi-octet integer values.
 *
 *   \param  value    the input long value.
 *   \param  chvalue  the output octet integer array
 *   \return A count of the octet in the char string ;
 */
int8_t fnPUB_CompactUintVar (uint8_t * chvalue,int32_t value);

/**
 * Find a session with the specified T_WAP_AddrTuple from WAP session index.
 *
 *   \param  hc  a wsp instance handle.
 *   \param  addr    the  address tuple to find.
 *   \return return a pointer to T_WAP_SIndex structure.
 */
T_WAP_SIndex *fnPUB_IndexFind(void *hc,T_WAP_AddrTuple *addr);

/**
 * Create MCB and add it to the front of the Session index list.
 *
 *   \param  hc  a wsp instance handle.
 *   \param  index    the T_WAP_SIndex pointer.
 *   \return If no error occur,it return a T_WAP_MCB pointer to the MCB
 *           which just created ,or NULL if there is insufficient memory available.
 */
T_WAP_MCB *fnPUB_MCB_Creat(void *hc,T_WAP_SIndex *index);

/**
 * Fill MCB and response after get a packet,.
 *
 *   \param  hc  a wsp instance handle.
 *   \param  packet the packet to deal with.
 *   \return
 */
void fnPUB_MCB_Fill(void *hc,T_WAP_MSG_P packet);

/**
 * Find the MCB with the specified TID.
 *
 *   \param  hc  a wsp instance handle.
 *   \param  packet    the packet to deal with.
 *   \param  tid  the TID to find.
 *   \return If no session exist ,return NULL ,else  return the MCB it find .
 */
T_WAP_MCB *fnPUB_MCB_Find(void *hc,T_WAP_MSG_P packet,uint16_t tid);

/**
 * Destroy the MCB.
 *
 *   \param  hc  a wsp instance handle.
 *   \param  machine the MCB to destroy.
 *   \return
 */
void fnPUB_MCB_Destroy(void *hc,T_WAP_MCB *m);

/**
 * Free the unused MCB in every session.
 *
 *   \param  hc  a wsp instance handle.
 *   \param  force    if this tag is set ,the function will free all MCB it found.
 *   set it to 0 if you don't sure whether you want that function.
 *   \return
 */
void fnPUB_MCB_Free_Unused(void * hc,int8_t force);

/**
 * Empty function(it only free resource)
 *
 *   \param  hc  a wsp instance handle.
 *   \param  arg0    the void pointer.
 *   \param  arg1  the void pointer.it should be a T_WAP_MSG
 *       pointer in oder to let it work properly.
 *   \return
 */
void fnPUB_EmptyFunc(void *hc,void *arg0,void *arg1);

/**
 * Find corresponding handle of a event.
 *
 *   \param  event1  the pointer to struct T_WAP_EventArray,
 *   \param  key the machine's state want to find.
 *   \return if the machine's state correspond to a function then return
 *           the address and  execute it,else return the address of
 *           fnPUB_EmptyFunc;
 * \attention en is the length of array,key is the machine's state want to find,T_WAP_StatFun
 *   is the base address of T_WAP_StatFun arry,in this function,if the machine's state
 *   correspond to a function then execute it,eles do nothing
 */
T_WAP_Action fnPUB_SearchFunc(const struct T_WAP_EventArray *event,uint32_t key);

#ifdef __cplusplus
}
#endif

#endif /* ___WSP_PUB_H__ */
