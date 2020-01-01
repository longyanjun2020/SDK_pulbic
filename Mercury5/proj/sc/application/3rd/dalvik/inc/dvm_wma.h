/*
 * Copyright 2010 MStarsemi, All Rights Reserved.
 * $Id$
 */

#ifndef DVM_WMA_HEADER__
#define DVM_WMA_HEADER__

#ifdef __cplusplus
extern "C" {
#endif

/*
 * Macros for Message Type.
 * Need to been kept consistent with MESSAGE_TYPE_XXX definitions
 * in com.mstar.j2me.io.messaging.TransportBase
 */

#undef      MESSAGE_TYPE_TEXT
#define     MESSAGE_TYPE_TEXT           0L
#undef      MESSAGE_TYPE_BINARY
#define     MESSAGE_TYPE_BINARY         1L

#undef      MESSAGE_CAT_SMS
#define     MESSAGE_CAT_SMS        0x10000L
#undef      MESSAGE_CAT_CBS
#define     MESSAGE_CAT_CBS        0x20000L
#undef      MESSAGE_CAT_MMS
#define     MESSAGE_CAT_MMS        0x40000L

#define     MESSAGE_CAT_MASK       0xffff0000L
#define     MESSAGE_TYPE_MASK      (~MESSAGE_CAT_MASK)

/* ERROR CODE VALUES */
#define E_WMA_OK        (0)
#define E_WMA_FAILED      (-1)
#define E_WMA_CATUNSUPPORT  (-2)
#define E_WMA_PORTRESTRICT  (-3)
#define E_WMA_OUTOFMEM      (-4)
#define E_WMA_AGAIN         (-11)
#define E_WMA_WOULDBLOCK    E_WMA_AGAIN
#define E_WMA_UNSUPPORT (-200)
#define E_WMA_NOIMPL    (-201)

// the general definition of messages in local buffer
typedef struct dvm_wma_msg_t dvm_wma_msg_t;
struct dvm_wma_msg_t {
    dvm_wma_msg_t *next;
    void *reserved; // reserved for double link
    int msgId;  // the id for message in platform.
    int type;   // the message type.
    char *sender; // zero terminated MSIDN. can be NULL in sending.
    int senderPort;
    char *receiver; // zero terminated MSIDN. can be NULL in receiving.
    int receiverPort;
    unsigned int timeStamp_hi; // timestamp is the seconds from 1st Jan, 1970 (in UTC)
    unsigned int timeStamp_lo; // here we represent it with two d-words.
    unsigned char *data; // pointer to data. if the message is a text message, the content
              // here is big-endian ucs2 buffer
    int dataLen;
};

/* init/finalize stub for dvm message functions */
int dvm_wma_init(void);
int dvm_wma_finalize(void);

/* create a message record */
int  dvm_wma_msg_create(dvm_wma_msg_t *msg, int type, const char *sender, int senderPort,
                       const char *receiver, int receiverPort,
                       const unsigned char *data, int dataLen);

/* destroy a message record */
int dvm_wma_msg_destroy(dvm_wma_msg_t *msg);

/*
 * register listening on the port for specified message type.
 * Interaction with PushRegistry: if the port/type previousl registered for
 * push, then we need to change the register status to a sub-state: the later
 * dvm_wma_unregister justs convert it back to push registered status.
 */
int dvm_wma_register(int port, int type);

/*
 * cease listening on specified port for specified message type
 */
int dvm_wma_unregister(int port, int type);

/* init/finalize point of push */
int dvm_wma_push_init(void);
int dvm_wma_push_finalize(void);

/*
 * register a port/type for push.
 * @param port
 * @param type
 * @suite the ams dependent suite identification
 * @midlet the midlet id
 */
int dvm_wma_push_register(int port, int type, const char *suite, int midlet);

/* unregister a port/type for push */
int dvm_wma_push_unregister(int port, int type, const char *suite, int midlet);

/*
 * check if the push on the port is available(message ready for hand-over) 
 * @return TRUE if message is available.
 */
int dvm_wma_push_avail(int type, int port);

/*
 * check if there is an available push event. if there is, 
 * return a handle to that event. the handle will be used in
 * later dvm_wma_push_drop.
 * @param pMsg the out buffer to receive the wma push message handle
 *             (if there are any messages available)
 * @return E_WMA_OK if there are push events available, the *pMsg
 *              include a valid push message handle.
 *         <0   something wrong or no push event available yet
 */
int dvm_wma_push_pull(void **pMsg);

/*
 * Drop a previously got handle of push event.
 * @param msgHandle the handle of push event to be thrown away. should be
 *        a value returned by dvm_wma_push_pull.
 * @param discard indicate whether we should discard the push message. 
 *        0 indicate to mark the message not as a push message any more
 *        (it can still been fetched by wma connection protocol)
 *        1 indicate that we should throw away the message entirely
 * @return E_WMA_OK if successed.
 *         < 0      if anything wrong.
 */
int dvm_wma_push_drop(void *msgHandle, int discard);

/* stop listening on any port for any message types. */
int dvm_wma_unregisterAll(void);

/* two forms of api for sending a message
 * if the port specified is -1, that means we don't expect ported messages been sent.
 * if the contents is of text, the data is represented by big-endian ucs2 buffer, actual
 * characters number is dataLen/2. if the content is binary, then dataLen is the exact byte
 * array length of contents.
 * @param sender reserved parameter for possibly future extension.
 * @return E_WMA_OK  sent successfully.
 *         < 0        failed for some reason.
 */
int dvm_wma_send0(int type, const char *sender, int senderPort,
                      const char *receiver, int receiverPort,
                      const unsigned char *data, int dataLen);

int dvm_wma_send(const dvm_wma_msg_t *msg);

/* receive a message,
 * @param blockingMode TRUE if we don't expect to return until a message availabe
 *                     FALSE if we allow return E_WMA_WOULDBLOCK when no message
 *                     available
 * @param msgBuf point to place where would hold the contents of message to be received.
 * @return  E_WMA_OK   if a message returned okay.
 *          E_WMA_FAIL if something wrong.
 *          E_WMA_WOULDBLOCK if no message available yet
 */
int dvm_wma_receive(dvm_wma_msg_t *msgBuf, int blockingMode);

/* get the buffer size of payload data of next available message
 * @return <0   if something wrong. error code is E_WMA_XXX.
 *         0    if nothing available
 *         >0   the content size in bytes of the protocol-dependent encoded
 *                    message body.
 */
int dvm_wma_nextAvailable();

/* get the number of message segments for a specified message before send it.
 * @param type the message types.
 * @param withPort whether the message will be sent with user port information
 * @return  <0  if something wrong. possible values are E_WMA_XXX
 *          >= 0 the number of segments for sending this message.
 */
int dvm_wma_getNumOfSegments(unsigned char *content, int contentLen,
                                 int type, int withPort);

/*
 * retrieve the current SMSC setting.
 * @return a 0-terminated constant char string with SMSC's MSIDN
 */
const char *dvm_wma_getSMSC(void);

/* check if next message available on registered listening ports.
 */
int dvm_wma_isNextMessageAvail(void);

#ifdef __cplusplus
}
#endif
#endif //DVM_WMA_HEADER__
/* vim: set tw=78 et nowrap: */
