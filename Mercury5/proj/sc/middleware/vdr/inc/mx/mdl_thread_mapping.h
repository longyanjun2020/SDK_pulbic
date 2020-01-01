#ifndef MDL_THREAD_MAPPING_H
#define MDL_THREAD_MAPPING_H

//#define __OS_RTK__

#ifdef __RTK_OS__
#else
  #include <semaphore.h> 
#endif

#if defined(__RTK_OS__)
#define SEM_INFO_T                  unsigned char
#define SEM_VDR_V_MUTEX             VDR_RING_V_SEM_MUTEX
#define SEM_VDR_A_MUTEX             VDR_RING_A_SEM_MUTEX
#define SEM_INIT(sem, init)         MsInitSem(*sem, init)
#define    SEM_PRODUCE(sem)         MsProduceSem(*sem)
#define SEM_CONSUME(sem)            MsConsumeSem(*sem)
#define SEM_DESTROY(sem)        
#else // __RTK_OS__
typedef sem_t                       SEM_INFO_T;
#define SEM_VDR_V_MUTEX             VDR_RING_V_SEM_MUTEX
#define SEM_VDR_A_MUTEX             VDR_RING_A_SEM_MUTEX
#define SEM_INIT(sem, init)         sem_init(sem, 0, init)
#define    SEM_PRODUCE(sem)         sem_post(sem)
#define SEM_CONSUME(sem)            (!sem_wait(sem))
#define SEM_DESTROY(sem)            sem_destroy(sem)
#endif

#endif

