#ifndef __VEN_PHB_MSGT_H__
#define __VEN_PHB_MSGT_H__

#ifndef __SDK_API_WAP_MMS_ONLY__

#include "ven_phb.h"
#include "ven_comdef_priv.h"
//@@~~ this might define in other common.h


/****************************************************************************/
/*  Message :       I_VEN_PHB_BROWSE_REQ                          */
/*--------------------------------------------------------------------------*/
/*                                                                          */
/*  From/to   : Vendor task to MMI                                          */
/*                                                                          */
/*  Scope     : The structure of the message with the purpose to launch a   */
/*              pbb browser for user to phone numbers(s) or email(s)        */
/*                                                                          */
/*  Structure : iVen_phb_browse_req_t                                       */
/*                                                                          */
/*--------------------------------------------------------------------------*/
/*  Field             |    Type   |  Description                            */
/*--------------------+-----------+-----------------------------------------*/
/*                    |           |                                         */
/****************************************************************************/
typedef struct
{
    iVen_AsyncReq_BodyBase_t ReqBase;
    u16* ptTitle;
    u8 titleLen;
    ven_phb_browser_type_t type;
    u8 maxMarkSize;
    u16 **pptOutData;
    u16 *ptOutDataLen;
    u8 *ptOutMarkedSize;
} iVen_phb_browse_req_t;

/****************************************************************************/
/*  Message :       I_VEN_PHB_BROWSE_RSP                                   */
/*--------------------------------------------------------------------------*/
/*                                                                          */
/*  From/to   : MMI to Vendor task                                          */
/*                                                                          */
/*  Scope     : The structure of the message with the result of             */
/*              user select phone numbers(s) or email(s)                    */
/*                                                                          */
/*  Structure : iVen_phb_browse_rsp_t                                       */
/*                                                                          */
/*--------------------------------------------------------------------------*/
/*  Field             |    Type   |  Description                            */
/*--------------------+-----------+-----------------------------------------*/
/*                    |           |                                         */
/****************************************************************************/
typedef struct
{
    iVen_AsyncRsp_BodyBase_t RspBase;
    u16* ptData;
    u16  dataLen;
    u8   nMarkedSize;
} iVen_phb_browse_rsp_t;

/****************************************************************************/
/*  Message :       I_VEN_PHB_SAVE_CONTACT_REQ                              */
/*--------------------------------------------------------------------------*/
/*                                                                          */
/*  From/to   : Vendor task to MMI                                          */
/*                                                                          */
/*  Scope     : The structure of the message with the purpose to save a     */
/*              contact to phonebook                                        */
/*                                                                          */
/*  Structure : iVen_phb_save_contact_req_t                                 */
/*                                                                          */
/*--------------------------------------------------------------------------*/
/*  Field             |    Type   |  Description                            */
/*--------------------+-----------+-----------------------------------------*/
/*                    |           |                                         */
/****************************************************************************/
typedef struct
{
    iVen_AsyncReq_BodyBase_t ReqBase;
    u8 *pName;
    u8 *pNumber;
    u8 nNameLen;
    u8 nNumberLen;
    ven_phb_phonebook_type_t PhbType;
    ven_phb_save_contact_rsp_t *pRsp; //for Sync
} iVen_phb_save_contact_req_t;

/****************************************************************************/
/*  Message :       I_VEN_PHB_ADD_CONTACT_RSP                              */
/*--------------------------------------------------------------------------*/
/*                                                                          */
/*  From/to   : MMI to Vendor task                                          */
/*                                                                          */
/*  Scope     : The structure of the message with the result of saving      */
/*              a contact to phonebook                                      */
/*                                                                          */
/*  Structure : iVen_phb_save_contact_rsp_t                                 */
/*                                                                          */
/*--------------------------------------------------------------------------*/
/*  Field             |    Type   |  Description                            */
/*--------------------+-----------+-----------------------------------------*/
/*                    |           |                                         */
/****************************************************************************/
typedef struct
{
    iVen_AsyncRsp_BodyBase_t RspBase;
    ven_phb_ret_t RetCode;
} iVen_phb_save_contact_rsp_t;

typedef struct
{
    iVen_AsyncReq_BodyBase_t ReqBase;
    ven_phb_phonebook_type_t phbBookType;
    ven_phb_contact_content_t tPhbContactContent;
    u16 *pu16PhysicalIdx;
    bool bNeedReturnIndex;
    ven_phb_add_new_contact_rsp_t *pRsp; //for Sync
} iVen_phb_write_contact_req_t;

typedef struct
{
    iVen_AsyncRsp_BodyBase_t RspBase;
    u16 u16Index;
    bool bNeedReturnIndex;
    ven_phb_ret_t RetCode;
} iVen_phb_write_contact_rsp_t;

typedef struct
{
    iVen_AsyncReq_BodyBase_t ReqBase;
    ven_phb_phonebook_type_t s32PhbBookType;
    u16 u16PhysicalIdx;
    ven_phb_delete_contact_rsp_t *pRsp; //for Sync
} iVen_phb_delete_contact_req_t;

typedef struct
{
    iVen_AsyncRsp_BodyBase_t RspBase;
    ven_phb_ret_t RetCode;
} iVen_phb_delete_contact_rsp_t;

typedef struct
{
    iVen_AsyncReq_BodyBase_t ReqBase;
    ven_phb_phonebook_type_t s32PhbBookType;
    ven_phb_contact_content_t tPhbContactContent;
    u16 u16PhysicalIdx;
    u16 *pu16NewPhysicalIdx;
    bool bNeedReturnIndex;
    ven_phb_modify_one_contact_rsp_t *pRsp; //for Sync
} iVen_phb_save_contact_by_handle_req_t;

typedef struct
{
    iVen_AsyncRsp_BodyBase_t RspBase;
    ven_phb_ret_t RetCode;
    u16 u16NewIndex;
    bool bNeedReturnIndex;
} iVen_phb_save_contact_by_handle_rsp_t;

typedef struct
{
    iVen_AsyncReq_BodyBase_t ReqBase;
    ven_phb_phonebook_type_t s32PhbBookType;
    u16 *pwcSearchStr;
    ven_phb_handle phbHandle; //for Sync
    ven_phb_contact_content_t *ptContent;//for Sync
} iVen_phb_find_first_req_t;

typedef struct
{
	iVen_AsyncRsp_BodyBase_t RspBase;
	ven_phb_handle phbHandle;
	ven_phb_contact_content_t ptContent;
} iVen_phb_find_first_rsp_t;

typedef struct
{
    iVen_AsyncReq_BodyBase_t ReqBase;
    ven_phb_phonebook_type_t s32PhbBookType;
    u16 u16PhysicalIdx;
    ven_phb_contact_content_t *ptContent; //for Sync
} iVen_phb_find_next_req_t;

typedef struct
{
	iVen_AsyncRsp_BodyBase_t RspBase;
	ven_phb_contact_content_t ptContent;
} iVen_phb_find_next_rsp_t;

typedef struct
{
    iVen_AsyncReq_BodyBase_t ReqBase;
    ven_phb_phonebook_type_t s32PhbBookType;
    ven_phb_get_mem_status_rsp_t *ptStatus; //for Sync
} iVen_phb_get_mem_status_req_t;

typedef struct
{
	iVen_AsyncRsp_BodyBase_t RspBase;
	ven_phb_get_mem_status_rsp_t tStatus;
} iVen_phb_get_mem_status_rsp_t;

typedef struct
{
    iVen_AsyncReq_BodyBase_t ReqBase;
    ven_phb_number_fuzzy_search_req_t *pMWPSearchReq;
	ven_phb_handle phbHandle;
    ven_phb_number_fuzzy_search_rsp_t *pRspSearchResult; //for Sync
} iVen_phb_number_fuzzy_search_req_t;

typedef struct
{
	iVen_AsyncRsp_BodyBase_t RspBase;
	ven_phb_number_fuzzy_search_rsp_t RspSearchResult;
} iVen_phb_number_fuzzy_search_rsp_t;

typedef struct
{
    iVen_AsyncReq_BodyBase_t ReqBase;
	bool *pReady;
    ven_phb_ret_t *pRetCode; //output: only useful if the ReqBase.bSync is TRUE
} iVen_phb_query_ready_req_t;

typedef struct
{
    iVen_AsyncReq_BodyBase_t ReqBase;
	void* pReadyIndFunc;
	u32 usrData;
    ven_phb_ret_t *pRetCode; //output: only useful if the ReqBase.bSync is TRUE
} iVen_phb_register_ready_req_t;

typedef struct
{
    iVen_AsyncRsp_BodyBase_t RspBase;
	u32 readyInfo;
} iVen_phb_register_ready_ind_t;

#endif //#ifndef __SDK_API_WAP_MMS_ONLY__

#endif //__VEN_PHB_MSGT_H__

