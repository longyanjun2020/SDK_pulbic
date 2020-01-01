#ifndef __DWL_CUSFILES_ACTIONS_H__
#define __DWL_CUSFILES_TBL_H__

#include "stdcomp.h"
#include "dwl_medium.h"

#ifdef __DWL_CUSFILES_TBL_C__
#define INTERFACE
#else
#define INTERFACE extern
#endif

typedef s32 (*pf_action_t)(void *param);

typedef struct
{
    u8 type;
    pf_action_t exec;
    u32 param;
} cus_action_t;

typedef struct
{
    u8 *prolog;
    u8 prolog_max_size;
    dwl_handle_t handle;
    const cus_action_t *pAction;
} cus_action_param_t;

/**
 * Function prototype for CUS action functions
 *
 * @param param Input paramter pointer
 * @retval >= 0   success
 * @retval < 0 failure code
 */
#define CUS_ACTION_PROTO(fn)    static s32 fn(void *input_param)

cus_action_t const *dwl_get_cus_actions(void);

#endif

