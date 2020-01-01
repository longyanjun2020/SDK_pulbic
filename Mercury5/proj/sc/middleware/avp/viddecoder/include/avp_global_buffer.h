#ifndef GLOBAL_BUFFER_H
#define GLOBAL_BUFFER_H

#include <stdint.h>
#include "avp_mvc_decoder.h"

#ifndef MAX_ALLOW_BUF_NUM
#define MAX_ALLOW_BUF_NUM    18
#endif

struct packet
{
    void *y;    // in/out
    void *u;    // in/out
    void *v;    // in/out
    void *aux;
    void *opq;
    int64_t pts;
};

typedef struct buf_pool_s
{
    int packets_in_queue;
    struct packet     packet_pool[MAX_ALLOW_BUF_NUM];
    struct packet   *packet_queue[MAX_ALLOW_BUF_NUM];
#ifndef NDEBUG
    uint32_t *freebuf;
    int freesize;
#endif
} buf_pool_st;

#if defined(__cplusplus)
extern "C" {
#endif

void gbufInit(buf_pool_st *bp, VID_SETUP *vidsetup, void *framebufY, void *framebufC, void *framebufAux, int bufsize);
void gbufAlloc(buf_pool_st *bp, VID_SETUP *vidsetup, void *framebufY, void *framebufC, void *framebufAux, int bufsize);
struct packet *gbufGetPacket(buf_pool_st *bp, VID_SETUP *vidsetup);
int gbufPutPacket(buf_pool_st *bp, struct packet *in);
void gbufCleanPackets(buf_pool_st *bp, VID_SETUP *vidsetup);
void gbufCleanFlags(buf_pool_st *bp, VID_SETUP *vidSetup);
void gbufFlushFlags(buf_pool_st *bp, VID_SETUP *vidSetup);
void gbufReportStatus(buf_pool_st *bp, VID_SETUP *vidSetup);

#if defined(__cplusplus)
}
#endif

#endif
