/**
 * @file    mmi_req_rtk.h
 *
 * @brief   This file defines the interface to access VM_RTK functions.
 * @author	steve.hsu@mstatsemi.com
 *
 */
 #ifndef __MMI_REQ_RTK_H__
#define __MMI_REQ_RTK_H__

#include "mmi_mae_common_def.h"

typedef enum 
{
   MMI_RTK_POOL_GROUP_STK,
   MMI_RTK_POOL_GROUP_CUS
} MMI_RTK_POOL_GROUP_e;

typedef enum 
{
   MMI_RTK_RESULT_SUCCESS,
   MMI_RTK_RESULT_FAIL
} MMI_RTK_RESULT_e;

 
/** MMI_RTK_QueryPoolNumber()
 * @brief get pool number in each pool group.
 * @param ePoolGroup	identify pool group.  
 * @retval value of pool number.
 */
u8 MMI_RTK_QueryPoolNumber (MMI_RTK_POOL_GROUP_e ePoolGroup);

/** MMI_RTK_QueryPoolStatus()
 * @brief get pool status like cluster size, total clusters, current used clusters and max used clusters.
 * @param ePoolGroup		identify pool group.  
 * @param poolId			identify which pool in pool group.  
 * @param pClusterSize		get memory size of each cluster.
 * @param pTotalClusters	get total clusters count in this pool.
 * @param pCurrUsedClusters	get current used clusters.
 * @param pMaxUsedClusters	get max used clusters.
 * @retval MMI_RTK_RESULT_SUCCESS
 * @retval MMI_RTK_RESULT_FAIL
 */
MMI_RTK_RESULT_e MMI_RTK_QueryPoolStatus (MMI_RTK_POOL_GROUP_e ePoolGroup, u8 poolId, u16 *pClusterSize, u16 *pTotalClusters, u16 *pCurrUsedClusters, u16 *pMaxUsedClusters);

#endif /*__MMI_REQ_RTK_H__*/
