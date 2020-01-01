#ifndef __VEN_GRAPHICS_MSGT_H__
#define __VEN_GRAPHICS_MSGT_H__

#include "ven_file.h"
#include "ven_graphics.h"
#include "ven_common_def.h"

/****************************************************************************/
/*  Message :       I_VEN_GRAPHICS_SET_SBVIS_REQ                            */
/*                  I_VEN_GRAPHICS_SET_SKVIS_REQ                            */
/*--------------------------------------------------------------------------*/
/*                                                                          */
/*  From/to   : Vendor task to MMI                                          */
/*                                                                          */
/*  Scope     : The structure of the message with the purpose to change     */
/*              status bar / softkey visibility                             */
/*                                                                          */
/*  Structure : iVen_gra_set_sb_vis_req_t                                   */
/*                                                                          */
/*--------------------------------------------------------------------------*/
/*  Field             |    Type   |  Description                            */
/*--------------------+-----------+-----------------------------------------*/
/*                    |           |                                         */
/****************************************************************************/
typedef struct
{
    iVen_AsyncReq_BodyBase_t ReqBase;
    ven_graphics_ret_t *pRetCode;
    bool   bVis;
} iVen_gra_set_vis_req_t;

typedef struct
{
    iVen_AsyncRsp_BodyBase_t RspBase;
    ven_graphics_ret_t RetCode;
} iVen_gra_set_vis_rsp_t;

typedef struct
{
    iVen_AsyncReq_BodyBase_t ReqBase;
    ven_graphics_ret_t *pRetCode;
    bool   *pbVis;
} iVen_gra_get_vis_req_t;

typedef struct
{
    iVen_AsyncRsp_BodyBase_t RspBase;
    ven_graphics_ret_t RetCode;
    bool   bVis;
} iVen_gra_get_vis_rsp_t;

typedef struct
{
    iVen_AsyncReq_BodyBase_t ReqBase;
	ven_GraphicsDisplayMode_t nDispMode;
    ven_graphics_ret_t *pRetCode; //output: only useful if the ReqBase.bSync is TRUE
} iVen_gra_set_display_mode_req_t;

typedef struct
{
    iVen_AsyncRsp_BodyBase_t RspBase;
    ven_graphics_ret_t retCode;
} iVen_gra_set_display_mode_rsp_t;

#endif /*__VEN_GRAPHICS_MSGT_H__ */

