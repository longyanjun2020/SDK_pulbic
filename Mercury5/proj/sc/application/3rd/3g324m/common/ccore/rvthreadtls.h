#ifndef RV_THREAD_TLS_H
#define RV_THREAD_TLS_H

#ifdef __cplusplus
extern "C" {
#endif


typedef struct {
    RvInt32 nFindRequests;
    RvInt32 nTotalIters;
} RvThreadTLSStats;

RVCOREAPI
void RvThreadTLSGetStats(RvThreadTLSStats *stats);

RvStatus RvThreadTLSInit(void);

void RvThreadTLSEnd(void);

RvStatus 
RvThreadTLSSetupThreadPtr(RvThreadId id, RvThread *th);

RvStatus
RvThreadTLSRemoveThreadPtr(RvThreadId id);

RvStatus
RvThreadTLSGetThreadPtr(RvThreadId id, RvThread **pth);



#ifdef __cplusplus
}
#endif 

#endif /* RV_THREAD_TLS_H */
