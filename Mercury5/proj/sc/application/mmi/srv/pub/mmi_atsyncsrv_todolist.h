/**
* @file mmi_atsyncsrv_todolist.h
*
*
* Class Id: CLSID_ATSYNCSRV
* 
*
* @version $Id: mmi_atsyncsrv_todolist.h 19566 2008-12-30 08:27:56Z elvis.chen $
*/
#ifndef __MMI_ATSYNCSRV_TDDOLIST_H__
#define __MMI_ATSYNCSRV_TDDOLIST_H__

MAE_Ret _AtyncSRV_TODOLIST_GetTodoListEvent(ATCmdSegmention_t *pATCmdSegment, void **ppTodoListEventOut);

ATSYNCSRV_TODDLIST_PREDATA_t *_AtyncSRV_TODOLIST_ComposeSegment(MMI_ATSYNCSRV *pThis, ATSYNCSRV_MultiSegmentCmd_t *ptodo_predata);

MAE_Ret _AtyncSRV_TODOLIST_DecodeStr(ATSYNCSRV_TODDLIST_PREDATA_t *ptodo_predata, ATSYNCSRV_TODDLIST_DATA_t *ptodo_data);

MAE_Ret _AtyncSRV_TODOLIST_Query(MMI_ATSYNCSRV *pThis, ATSYNCSRV_TODDLIST_DATA_t *ptodo_predata, ATSYNCSRV_MultiSegmentCmd_t *pMultiSegmentCmd);

MAE_Ret _AtyncSRV_TODOLIST_Read(MMI_ATSYNCSRV *pThis, ATSYNCSRV_TODDLIST_DATA_t *ptodo_predata, ATSYNCSRV_MultiSegmentCmd_t *pMultiSegmentCmd);

MAE_Ret _AtyncSRV_TODOLIST_Write(MMI_ATSYNCSRV *pThis, ATSYNCSRV_TODDLIST_DATA_t *ptodo_predata, ATSYNCSRV_MultiSegmentCmd_t *pMultiSegmentCmd);

MAE_Ret _AtyncSRV_TODOLIST_Clear(MMI_ATSYNCSRV *pThis, ATSYNCSRV_TODDLIST_DATA_t *ptodo_predata, ATSYNCSRV_MultiSegmentCmd_t *pMultiSegmentCmd);



#endif
