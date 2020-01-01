/**
 * @file mmi_mae_shell_memory_types.h
 *
 * This file defines the current version number of state machine engine
 * The version number is used to make sure that the application's data is right for current state machine engine
 * Compilation will fail if the version is mismatch with the application source code.
 *
 */

#ifndef __MMI_MAE_SHELL_MEMORY_TYPES_H__
#define __MMI_MAE_SHELL_MEMORY_TYPES_H__

#include "mmi_mae_common_def.h"
#include "mmi_mae_shell_memory_forward.h"

//It need to keep order (sync with _tMaeMemClusterInitTbl)
enum
{
    MAE_MEM_CLUSTER__MODEL = 0,
    MAE_MEM_CLUSTER__SIZE
};

typedef struct MAEClusterDesc_t_
{
    u16 nClusterNum;	    //the number of clusters
    u16 nClusterSize;	//the cluster size
} MAEClusterDesc_t;

typedef struct MAECluster_tbl_t_
{
    u32 nClusterSize;
    MAEClusterDesc_t *pPoolDesc; //gpDesc_t*
    u32 nPoolNum;
} MAECluster_tbl_t;

#endif /* __MMI_MAE_SHELL_MEMORY_TYPES_H__ */
