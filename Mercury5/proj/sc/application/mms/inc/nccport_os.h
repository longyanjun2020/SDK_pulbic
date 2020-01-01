#ifndef __NCCPort_OS_H__
#define __NCCPort_OS_H__

#include <ncc_types.h>
#include <nccmms_cps.h>
#include <nccmms_fs.h>

#if defined(__cplusplus)
extern "C" {
#endif

#define MAX_DEBUG_BUFFER_SIZE 1024

/*system time struct*/
typedef struct
{
    uint16_t year;
    uint16_t month;
    uint16_t day;
    uint16_t hour;
    uint16_t min;
    uint16_t sec;
}T_NCCPort_osTime;

void *NCCPort_os_malloc(int32_t size);

void *NCCPort_os_calloc(int32_t num, int32_t size);

void *NCCPort_os_realloc(void *ptr, int32_t size);

void NCCPort_os_free(void *ptr);

int32_t NCCPort_os_usedMemSize(void);

#ifdef NCC_DEBUG_ON
void NCCPort_os_traceStr(char *str, ...);
#endif

int8_t *NCCPort_os_itoa(uint32_t val, int8_t * buf, uint16_t radix);

void NCCPort_os_sec2date(uint32_t time, T_NCCPort_osTime *date);

void NCCPort_os_date2sec(uint32_t *sec, T_NCCPort_osTime *date, T_NCCPort_osTime *fromDate);

void NCCPort_os_ResetWatchDog(void);

int32_t NCCPort_os_getFreeHeapSize(void);

void NCCPort_os_setVenHandle(int32_t handle);

uint32_t NCCPort_os_getVenHandle(void);

void NCCPort_os_setVenHandle_ex(uint32_t handle, int32_t appId);

uint32_t NCCPort_os_getVenHandle_ex(int32_t appId);

#ifdef MEM_USING_MYMALLOC
typedef void* (* extMallocFunc)(uint32_t size);
typedef void (* extFreeFunc)(void *ptr);

void NCCPort_os_setExternalMemoryFunction(extMallocFunc extMalloc, extFreeFunc extFree);
void NCCPort_os_setCommonMemorySize(uint32_t size);
uint32_t NCCPort_os_getCommonMemorySize(void);
int32_t NCCPort_os_initCommonMemory(void);
int32_t NCCPort_os_finalizeCommonMemory(void);
#endif

#ifdef NCC_MEMORY_LEAK_CHECK
void Mem_test_printInfo(void);
#endif

#if defined(__cplusplus)
}
#endif

#endif /* __NCCPort_OS_H__ */
