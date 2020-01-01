/* $Id: ares_private.h,v 1.3 1998/09/22 01:46:11 ghudson Exp $ */

/* Copyright 1998 by the Massachusetts Institute of Technology.
 *
 * Permission to use, copy, modify, and distribute this
 * software and its documentation for any purpose and without
 * fee is hereby granted, provided that the above copyright
 * notice appear in all copies and that both that copyright
 * notice and this permission notice appear in supporting
 * documentation, and that the name of M.I.T. not be used in
 * advertising or publicity pertaining to distribution of the
 * software without specific, written prior permission.
 * M.I.T. makes no representations about the suitability of
 * this software for any purpose.  It is provided "as is"
 * without express or implied warranty.
 */

#include "rvstdio.h"

/* NOTE: we refer here to typedef rvQuery that was defined in
         ares.h by knowing that it is included always BEFORE this file */

#define TCP_LENWORD_SIZE 2  /* size in bytes of the length word */

#if !defined(RV_DNS_SANITY_CHECK)
#  define RV_DNS_SANITY_CHECK 0
#endif

#define RV_DNS_MAX_SENDBUF_SIZE (2 + HFIXEDSZ + NS_MAXCDNAME + QFIXEDSZ)

#ifndef RV_DNS_STATISTICS
#  define RV_DNS_STATISTICS 0
#endif

typedef struct {
    RvSelectFd fd;
    RvSocketProtocol protocol;
    int server;
    RvDnsEngine *channel;
} select_fd_args;

struct server_state {
    RvAddress addr;
    RvChar sAddr[RV_ADDRESS_MAXSTRINGSIZE]; /* server address as string, for logging */
    select_fd_args udp_socket;
    select_fd_args tcp_socket;

    /* Mini-buffer for reading the length word */
    RvUint8 tcp_lenbuf[TCP_LENWORD_SIZE];
    RvInt32 tcp_lenbuf_pos;
    RvInt32 tcp_length;

    /* Buffer for reading actual TCP data */
    RvUint8 *tcp_buffer;
    RvInt32  tcp_bufflen;
    RvInt32  tcp_buffer_pos;

    /* We use single TCP connection for server and multiplex all TCP queries
     * over this connection. So, there may be a problem when some query that is
     * currently transmitted is canceled by user. In this case we need to save unsent portion
     * of this query in temporary buffer
     *
     */
    RvUint8 deletedQueryBuf[RV_DNS_MAX_SENDBUF_SIZE];
    /* Points to the next unsent buffer in deletedQueryBuf */
    RvUint8 *pDeletedQuery;
    /* Size of unsent portion of deletedQueryBuf starting at pDeletedQuery */
    RvInt   nDeletedQueryLen;

    /* TCP output queue */
    rvQuery *qhead;
    rvQuery *qtail;
};

#define INTBITS (8 * sizeof(int))
#define SKIP_SERVER_SET(q, n) ((q)->skip_server[(n) / INTBITS] |= (1 << (n) % INTBITS))
#define SKIP_SERVER(q, n) ((q)->skip_server[(n) / INTBITS] & (1 << (n) % INTBITS))

struct query_struct {
    RvInt64 timeout;
    unsigned short qid;    /* Query ID from qbuf, for faster lookup, and current timeout */
    unsigned int user_qid;
    RvTimer timer;

    /* User callback to handle replies */
    RvDnsNewRecordCB newRecordCB;
    rvAresCallback user_callback;
    void *user_arg;
    
    /* Query status */
    int serversGeneration;
    int try_index;
    int server;
    int *skip_server;
    int using_tcp;
    int error_status;
    
    /* Arguments passed to ares_send() */
    char *qbuf;
    int qlen;
    
    /* Next query in chain */
    rvQuery *qnext;

    /* TCP output queue */
    char *tcp_data;
    int tcp_len;
    rvQuery *tcp_next;
#if RV_DNS_SANITY_CHECK    
    RvBool mark;
#endif
};

int ares__send_query(RvDnsEngine *channel, rvQuery *query, RvInt64 now);
void ares__close_sockets(RvDnsEngine *channel, int i, RvBool waitForCallbacks);
int ares__read_line(FILE *fp, char **buf, int *bufsize);

void rvAresAddQuery(RvDnsEngine *channel, rvQuery *query);
rvQuery* removeQueryByUqid(RvDnsEngine *channel, unsigned int qid);
rvQuery* findQueryByUqid(RvDnsEngine *channel, unsigned int qid);


#if RV_DNS_SANITY_CHECK
/* Assumes lock hold on 'channel' object */
RvBool rvDnsEngineSanityCheck(RvDnsEngine *channel);

#else

#define rvDnsEngineSanityCheck(channel) (RV_TRUE)

#endif
