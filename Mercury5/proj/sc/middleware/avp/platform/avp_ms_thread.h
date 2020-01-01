////////////////////////////////////////////////////////////////////////////////
//
// Copyright (c) 2009-2011 MStar Semiconductor, Inc.
// All rights reserved.
//
// Unless otherwise stipulated in writing, any and all information contained
// herein regardless in any format shall remain the sole proprietary of
// MStar Semiconductor Inc. and be kept in strict confidence
// ("MStar Confidential Information") by the recipient.
// Any unauthorized act including without limitation unauthorized disclosure,
// copying, use, reproduction, sale, distribution, modification, disassembling,
// reverse engineering and compiling of the contents of MStar Confidential
// Information is unlawful and strictly prohibited. MStar hereby reserves the
// rights to any and all damages, losses, costs and expenses resulting therefrom.
//
////////////////////////////////////////////////////////////////////////////////


#ifndef MS_THREAD_H
#define MS_THREAD_H

#include <pthread.h>
#include <stdint.h>

/* Thread API */

typedef enum
{
    MS_THREAD_PRIORITY_HIGHEST = 0,
    MS_THREAD_PRIORITY_HIGH,
    MS_THREAD_PRIORITY_NORMAL,
    MS_THREAD_PRIORITY_LOW,
    MS_THREAD_PRIORITY_LOWEST
} ms_priority_et;

typedef pthread_t ms_thread_st;

typedef void *ms_thread_entry(void *);

int ms_thread_create(
                ms_thread_st           *handle,             /* returned thread handle    */
                ms_priority_et          priority,           /* scheduling info (eg pri)  */
                ms_thread_entry        *entry,              /* entry point function      */
                void                   *entry_data,         /* entry data                */
                char                   *name,               /* optional thread name      */
                uint32_t                stack_size          /* stack size, 0 = default   */
                );

void ms_thread_delete(
                ms_thread_st            handle
                );

int ms_thread_join(
                ms_thread_st            handle
                );

void ms_thread_set_priority(
                ms_thread_st            handle,
                ms_priority_et          priority
                );

#endif /* MS_THREAD_H */
