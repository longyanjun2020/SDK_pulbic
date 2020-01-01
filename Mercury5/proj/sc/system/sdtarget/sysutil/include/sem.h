#ifndef __SEM_H__
#define __SEM_H__

#include "stdcomp.h"

#ifdef __SEM_C__
#define INTERFACE
#else
#define INTERFACE extern
#endif

typedef s32 sem_t;

INTERFACE s32 sem_init(sem_t *sem, s32 init_value);
INTERFACE s32 sem_try_lock(sem_t *sem);
INTERFACE s32 sem_unlock(sem_t *sem);

INTERFACE sem_t usb_lock;

#undef INTERFACE
#endif

