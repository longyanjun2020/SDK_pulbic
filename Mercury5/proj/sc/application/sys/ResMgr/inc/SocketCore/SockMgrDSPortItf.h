#ifndef _SOCKMGR_DS_PORT_ITF_H_
#define _SOCKMGR_DS_PORT_ITF_H_

/*=============================================================*/
// Include Files
/*=============================================================*/

#include "PlatformDefines.h"

/*=============================================================*/
// Macro Definitions
/*=============================================================*/

/*=============================================================*/
// Type Declarations
/*=============================================================*/

typedef enum
{
	E_SOCKMGR_CTNR_DLIST = 0,
	E_SOCKMGR_CTNR_NUM,
}SockMgr_CtnrType_e;

typedef void* SockMgr_CtnrHdl_t;
typedef void* SockMgr_PosHdl_t ;
typedef void (*SockMgr_DataCtnr_FreeData)(void *pItem);
typedef bool (*SockMgr_CtnrCmpCb)(void *pvItem, void *pvUserData);
typedef void (*SockMgr_CtnrDoAction)(void *pvItem, void *pvUserData);

/*=============================================================*/
// Function Declarations
/*=============================================================*/

SockMgr_CtnrHdl_t SockMgr_Ctnr_Factory_Create(SockMgr_CtnrType_e eCtnrType) ;
void SockMgr_Ctnr_Factory_Destroy(SockMgr_CtnrHdl_t hCtnr) ;
bool SockMgr_DataCtnr_AddItemToHead(SockMgr_CtnrHdl_t hCtnr, void *pItem);
bool SockMgr_DataCtnr_AddItemToTail(SockMgr_CtnrHdl_t hCtnr, void *pItem);
bool SockMgr_DataCtnr_RemoveItem(SockMgr_CtnrHdl_t hCtnr, void *pItem);
bool SockMgr_DataCtnr_RemoveItemByIdx(SockMgr_CtnrHdl_t hCtnr, u16 idx);
void SockMgr_DataCtnr_RemoveAllItem(SockMgr_CtnrHdl_t hCtnr);
void SockMgr_DataCtnr_RemoveAllItemEx(SockMgr_CtnrHdl_t hCtnr, SockMgr_DataCtnr_FreeData cbFreeItem);
void* SockMgr_DataCtnr_RemoveItemByOrderFirst(SockMgr_CtnrHdl_t hCtnr);
void* SockMgr_DataCtnr_RemoveItemByOrderLast(SockMgr_CtnrHdl_t hCtnr);
void* SockMgr_DataCtnr_GetFirstItem(SockMgr_CtnrHdl_t hCtnr);
void* SockMgr_DataCtnr_GetLastItem(SockMgr_CtnrHdl_t hCtnr);
SockMgr_PosHdl_t SockMgr_DataCtnr_CreatePosHdl(SockMgr_CtnrHdl_t hCtnr);
bool SockMgr_DataCtnr_DestroyPosHdl(SockMgr_PosHdl_t hPos);
bool SockMgr_DataCtnr_SetPosToHead(SockMgr_PosHdl_t hPos);
bool SockMgr_DataCtnr_SetPosToTail(SockMgr_PosHdl_t hPos);
bool SockMgr_DataCtnr_SetPosToNext(SockMgr_PosHdl_t hPos);
bool SockMgr_DataCtnr_SetPosToPrev(SockMgr_PosHdl_t hPos);
void* SockMgr_DataCtnr_GetCurItemByPos(SockMgr_PosHdl_t hPos);
void* SockMgr_DataCtnr_GetNextItemByPos(SockMgr_PosHdl_t hPos);
void* SockMgr_DataCtnr_GetPrevItemByPos(SockMgr_PosHdl_t hPos);
void* SockMgr_DataCtnr_GetItemByIdx(SockMgr_CtnrHdl_t hCtnr, u16 idx);
bool SockMgr_DataCtnr_FindItem(SockMgr_CtnrHdl_t hCtnr, SockMgr_PosHdl_t hPos, void *pItem);
u16 SockMgr_DataCtnr_GetItemNum(SockMgr_CtnrHdl_t hCtnr);
bool SockMgr_DataCtnr_QueryItem(SockMgr_CtnrHdl_t hCtnr, SockMgr_CtnrCmpCb cbCmp, void *pvUserData, void **ppvFoundItem);
void SockMgr_DataCtnr_VisitItem(SockMgr_CtnrHdl_t hCtnr, SockMgr_CtnrDoAction cbDoAction, void *pvUserData);

#endif/* _SOCKMGR_DS_PORT_ITF_H_ */
