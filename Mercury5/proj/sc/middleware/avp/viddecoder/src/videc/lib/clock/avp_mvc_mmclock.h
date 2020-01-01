#ifndef MVC_MMCLOCK_H
#define MVC_MMCLOCK_H

/**
 * @file mvc_mmclock.h
 * Provides abstract layer for audio/video synchronization and performance measurement.
 */

#include <stdint.h>

typedef struct mm_clock_s {
    int64_t start_time;
    int64_t pause_time;
} mm_clock_st;

#ifdef __cplusplus
extern "C" {
#endif

void mm_clock_init    (mm_clock_st *ctx);
void mm_clock_start   (mm_clock_st *ctx, int64_t start);
void mm_clock_wait    (mm_clock_st *ctx, int64_t pts);
void mm_clock_pause   (mm_clock_st *ctx);
void mm_clock_resume  (mm_clock_st *ctx);
void mm_clock_close   (mm_clock_st *ctx);
int64_t mm_clock_duration(mm_clock_st *ctx);

#ifdef __cplusplus
}
#endif

#endif /* MVC_MMCLOCK_H */
