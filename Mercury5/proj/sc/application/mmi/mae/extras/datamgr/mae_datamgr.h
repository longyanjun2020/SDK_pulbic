/**
* @file MAE_DataMgr.h
* @brief
*
*
* @author  coco.chiang@mstarsemi.com
*/
#ifndef __MAE_DATAMGR_H__
#define __MAE_DATAMGR_H__
///////////////////////////////////////////////////////////////////////////////////////////////////////
#include "mmi_mae_common_def.h"

//#define DATA_MGR_STANDALONE_DEBUG
#define DATA_MGR_SORTING_IN_MEM
#define DATA_MGR_SUPPORT_MULTI_SORT

#if defined(DATA_MGR_STANDALONE_DEBUG)
#define mmi_fs_raiWrite UT_mmi_fs_raiWrite
#define mmi_fs_raiDelete UT_mmi_fs_raiDelete
#define mmi_fs_raiRead UT_mmi_fs_raiRead
#define mmi_fs_raiInfo UT_mmi_fs_raiInfo
#define mmi_fs_raiInit UT_mmi_fs_raiInit
#define mmi_raiInfo_t UT_mmi_raiInfo_t
#define mmi_adHandle_t UT_mmi_adHandle_t
#include "ut_datamgr_utility.h"
#define __MAE_UTIL_FS_H__
#endif

///////////////////////////////////////////////////////////////////////////////////////////////////////
typedef struct
{
	u32 nResultNum;
	u32 *pUID;
} QueryResult_t;

typedef struct
{
	u32 nUID;
	u32 nRaiIndex;
} UIDMapping_t;

typedef enum
{
	TABLE_EVENT,
	TABLE_EVENT_EXCEPTION,
	TABLE_LOG,
	TABLE_TASK,
#ifdef __MMI_OMA_DRM_V1__
	TABLE_RO,
#endif
	TABLE_NUM
} Table_e;

typedef struct
{
	u16 nColSize;
} Column_t;


typedef struct
{
	Table_e eTableId;
	u16 nPrimaryKeyColIndex;
	u16 nRecordSize;
	u16 nColNum;
    Column_t *pColumn;
} Table_t;

typedef struct
{
	u16 nOffset;
	u16 nSize;
} RawData_t;

typedef struct
{
	u16 nTableSize;
	u32 nRaiStartAddress;
	UIDMapping_t *pMappingTable;
	u16 nUsedNum;
} MappingTableAttr_t;

typedef u8 TableID_e;

typedef s32 (*DataMgrSort) (void *pBaseRecord, void *pRefRecord);
typedef boolean (*DataMgrFilter) (void *pRecord, void *pData);
typedef boolean (*DataMgrInit) (void *pRecord, u32 *pUID, u16 *pSize);
typedef void (*DataMgrUpdate) (void *pRecord, void *pData);

typedef struct
{
	DataMgrSort *pDataMgrSortFn;
	u16 nSortNum;
} SortFn_t;
///////////////////////////////////////////////////////////////////////////////////////////////////////
/** MAEDataMgrInit
@brief  The Data Manager initialization function.

@param[in]      pTable			point to the table which content is to be initialized.

@retval MAE_RET_SUCCESS         If successful.
@retval MAE_RET_FAILED			failed.
*/
MAE_Ret MAEDataMgrInit(Table_t *pTable);

/** MAEDataMgrInsertData
@brief  Insert one record to the table.

@param[in]      eTableId		The table ID.
@param[in]      pRecord			The record to be inserted.

@retval MAE_RET_SUCCESS         If successful.
@retval MAE_RET_FAILED			failed.
*/
MAE_Ret MAEDataMgrInsertData(Table_e eTableId, void *pRecord);

/** MAEDataMgrUpdateData
@brief  Update one record to the table.

@param[in]      eTableId		The table ID.
@param[in]      nUID			The primary key.
@param[in]      pUpdate			The callback function to update the data
@param[in]      pData			The data to be updated (the input paramter for pUpdate).

@retval MAE_RET_SUCCESS         If successful.
@retval MAE_RET_FAILED			failed.
*/
MAE_Ret MAEDataMgrUpdateData(Table_e eTableId, u32 nUID, DataMgrUpdate pUpdate, void *pData);

/** MAEDataMgrCreateQuery
@brief  Query the record with/without sorting

@param[in]      eTableId			The table ID.
@param[in]      pDataMgrFilterFn	The callback function to filter the record.
@param[in]      pDataMgrSortFn		The callback function to sort the record.
@param[out]		pQueryResult		Save the query result here.
@param[in]		pFilterParam		The parameter for filter function.

@retval			MAE_RET_SUCCESS		If successful.
@retval			MAE_RET_FAILED		failed.
*/
MAE_Ret MAEDataMgrCreateQuery(Table_e eTableId, DataMgrFilter pDataMgrFilterFn, DataMgrSort pDataMgrSortFn, QueryResult_t *pQueryResult, void *pFilterParam);


/** MAEDataMgrDestroyQuery
@brief  Query the record with/without sorting

@param[out]		pQueryResult		Point to the query result get from MAEDataMgrCreateQuery

@retval			MAE_RET_SUCCESS		If successful.
@retval			MAE_RET_FAILED		failed.
*/
MAE_Ret MAEDataMgrDestroyQuery(QueryResult_t *pQueryResult);

/** MAEDataMgrGetRecord
@brief  Get one record from the table.

@param[in]      eTableId			The table ID.
@param[in]      nUID				The primary key.
@param[out]		ppRecord			Save the record here.

@retval			MAE_RET_SUCCESS		If successful.
@retval			MAE_RET_FAILED		failed.
*/
MAE_Ret MAEDataMgrGetRecord(Table_e eTableId, u32 nUID, void **ppRecord);

/** MAEDataMgrDelete
@brief  Delete one record from the table.

@param[in]      eTableId			The table ID.
@param[in]      nUID				The primary key.

@retval			MAE_RET_SUCCESS		If successful.
@retval			MAE_RET_FAILED		failed.
*/
MAE_Ret MAEDataMgrDelete(Table_e eTableId, u32 nUID);

/** MAEDataMgrDeleteAll
@brief  Delete all record from the table.

@param[in]      eTableId			The table ID.

@retval			MAE_RET_SUCCESS		If successful.
@retval			MAE_RET_FAILED		failed.
*/
MAE_Ret MAEDataMgrDeleteAll(Table_e eTableId);

/** MAEDataMgrBindData
@brief  To bind the data according to the column index.

@param[in]      eTableId			The table ID.
@param[out]		pRecord				Copy the binding reault here.
@param[in]      nColIndex			The column index.
@param[in]      pData				The data to be binded.

@retval			MAE_RET_SUCCESS		If successful.
@retval			MAE_RET_FAILED		failed.
*/
MAE_Ret MAEDataMgrBindData(Table_e eTableId, void *pRecord, u16 nColIndex, void *pData);

/** MAEDataMgrRelease
@brief  To release table.

@param[in]      eTableId			The table ID.

@retval			MAE_RET_SUCCESS		If successful.
@retval			MAE_RET_FAILED		failed.
*/
MAE_Ret MAEDataMgrRelease(Table_e eTableId);

/** MAEDataMgrGetRawData
@brief  Get raw data and store it in pData

@param[in]      eTableId			The table ID.
@param[in]      nColIndex			The column index.
@param[in]      pRecord				The record.
@param[out]     pData				Store the raw data here.

@retval			MAE_RET_SUCCESS		If successful.
@retval			MAE_RET_FAILED		failed.
*/
MAE_Ret MAEDataMgrGetRawData(Table_e eTableId, u16 nColIndex, void *pRecord, void *pData);

int GetWSize(const MAE_WChar *cc ); //This function is just for compatibility for sqlite3_util.c

/** MAEDataMgrReleaseRecord
@brief  Release the record.

@param[out]		ppRecord			Pointer of the record address to be released.

@retval			MAE_RET_SUCCESS		If successful.
@retval			MAE_RET_FAILED		failed.
*/
MAE_Ret MAEDataMgrReleaseRecord(void **ppRecord);

/** MAEDataMgrCreateQueryMultiSort
@brief  Query the record with/without sorting. The sorting supports multi-sort.

@param[in]      eTableId			The table ID.
@param[in]      pDataMgrFilterFn	The callback function to filter the record.
@param[in]      pSortFn				Point to the sort function structure to sort the record.
@param[out]		pQueryResult		Save the query result here.
@param[in]		pFilterParam		The parameter for filter function.

@retval			MAE_RET_SUCCESS		If successful.
@retval			MAE_RET_FAILED		failed.
*/
MAE_Ret MAEDataMgrCreateQueryMultiSort(Table_e eTableId, DataMgrFilter pDataMgrFilterFn, SortFn_t *pSortFn, QueryResult_t *pQueryResult, void *pFilterParam);



/** MAEDataMgrGetUsageInfo
@brief  Query the usage info by table ID

@param[in]      eTableId			The table ID.
@param[out]		pSize		        Point to the table size.
@param[out]		pUsedNum		    Point to the used number.

@retval			MAE_RET_SUCCESS		If successful.
@retval			MAE_RET_FAILED		failed.
*/
MAE_Ret MAEDataMgrGetUsageInfo(Table_e eTableId, u16 *pSize, u16 *pUsedNum);
///////////////////////////////////////////////////////////////////////////////////////////////////////

#endif //__MAE_DATAMGR_H__
