/**
 * @file mmi_mae_shell_memory.h
 *
 * This file defines the current version number of state machine engine
 * The version number is used to make sure that the application's data is right for current state machine engine
 * Compilation will fail if the version is mismatch with the application source code.
 *
 */

#ifndef __MMI_MAE_SHELL_MEMORY_H__
#define __MMI_MAE_SHELL_MEMORY_H__

#include "mmi_mae_common_def.h"
#include "mmi_mae_shell_memory_forward.h"

#if defined(__MAE_INTERNAL_BUILD__) || defined(VC_MEM_DBG)
#define SHELL_MEMORY_MALLOC(nClusterId, size) MAE_ClusterMalloc(nClusterId, size)
#define SHELL_MEMORY_REALLOC(nClusterId, ptr, size) MAE_ClusterRealloc(nClusterId, ptr, size)
#define SHELL_MEMORY_FREE(nClusterId, ptr) MAE_ClusterFree(nClusterId, ptr)
#elif (defined __PC_SIMULATOR__)
#define SHELL_MEMORY_MALLOC(nClusterId, size) MAE_ClusterMalloc(nClusterId, size, __LINE__, __MFILE__)
#define SHELL_MEMORY_REALLOC(nClusterId, ptr, size) MAE_ClusterRealloc(nClusterId, ptr, size, __LINE__, __MFILE__)
#define SHELL_MEMORY_FREE(nClusterId, ptr) MAE_ClusterFree(nClusterId, ptr)
#else /* target */
#define SHELL_MEMORY_MALLOC(nClusterId, size) MAE_ClusterMalloc(nClusterId, size)
#define SHELL_MEMORY_REALLOC(nClusterId, ptr, size) MAE_ClusterRealloc(nClusterId, ptr, size)
#define SHELL_MEMORY_FREE(nClusterId, ptr) MAE_ClusterFree(nClusterId, ptr)
#endif

#ifdef __SDK_SIMULATION__
void *MAE_ClusterMalloc(MaeMenCluster_e nClusterId, u32 nSize, int __nMline__, char *__nMfile__);
void *MAE_ClusterRealloc(MaeMenCluster_e nClusterId, void *ptr, u32 nSize, int __nMline__, char *__nMfile__);
#else
void *MAE_ClusterMalloc(MaeMenCluster_e nClusterId, u32 nSize);
void *MAE_ClusterRealloc(MaeMenCluster_e nClusterId, void *ptr, u32 nSize);
#endif // __SDK_SIMULATION__

s32 MAE_ClusterFree(MaeMenCluster_e nClusterId, void *ptr);
void MAE_MemClusterInit(void);
void MAE_MemClusterUnInit(void);

#endif /* __MMI_MAE_SHELL_MEMORY_H__ */
