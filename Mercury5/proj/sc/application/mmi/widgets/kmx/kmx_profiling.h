#ifndef KMX_PROFILING_H
#define KMX_PROFILING_H

#include "mmi_mae_log.h"
#include "mmi_log.h"

#ifdef __cplusplus 
extern "C"{ 
#endif 

#define MMI_IME_CSTAR_PROFILING		0

enum
{
	KMX_PROFILING_KMX_PEN_DOWN,
	KMX_PROFILING_KMX_PEN_UP,
	KMX_PROFILING_KMX_DRAW,

	KMX_PROFILING_DRAW_IMAGE,
	KMX_PROFILING_DRAW_IMAGE_HIGHLIGHT,
	KMX_PROFILING_LOAD_IMAGE,
	KMX_PROFILING_DRAW_TEXT,
	KMX_PROFILING_DRAW_RECT,
	KMX_PROFILING_MEASURE_TEXT
};

void kmx_start_profiling(int index);
void kmx_stop_profiling(int index);
void kmx_print_profiling(void);
unsigned int kmx_get_tick_count(void);

#ifdef __cplusplus 
} 
#endif 

#endif /* KMX_PROFILING_H */
