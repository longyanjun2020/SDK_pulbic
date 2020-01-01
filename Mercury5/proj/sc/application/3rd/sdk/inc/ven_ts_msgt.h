#ifndef __VEN_TS_MSGT_H__
#define __VEN_TS_MSGT_H__

#include "ven_ts.h"

/****************************************************************************/
/*  Message :       I_VEN_TS_INPUT_IND                                      */
/*--------------------------------------------------------------------------*/
/*                                                                          */
/*  From/to   : MMI to Vendor                                               */
/*                                                                          */
/*  Scope     : The structure of the message of touch event                 */
/*                                                                          */
/*  Structure : iVen_ts_input_ind_t                                         */
/*                                                                          */
/*--------------------------------------------------------------------------*/
/*  Field             |    Type   |  Description                            */
/*--------------------+-----------+-----------------------------------------*/
/*                    |           |                                         */
/****************************************************************************/
typedef struct
{
    ven_ts_evt_t      evt;
    u32               x;
    u32               y;
    iVen_App_ID       VenApId;
} iVen_ts_input_ind_t;

#endif //__VEN_TS_MSGT_H__

