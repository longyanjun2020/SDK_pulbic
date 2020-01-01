#ifndef _MDL_VT_MSG_H_
#define _MDL_VT_MSG_H_

typedef struct
{
    MmlVideoUCParam_t           tVideoUCParam;  ///< Video use case parameters
    u32                         SenderUserData;   /* used for userdata from sender */
    u32                         InternalUserData;   /* used for internal user data */
    u8                          NoResponse;
    vt_t                        *vt;
} vm_msgBody_t;

#endif