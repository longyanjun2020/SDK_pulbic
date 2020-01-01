#if !defined(__MSMSRV_H__)
#define __MSMSRV_H__

#include "msmglobal.h"
#include "msmcomm.h"

#define MAX_STRING_LEN      64

/* Service Descriptor */
typedef struct devService_s_
{
    U8          name_a[MAX_STRING_LEN]; /* name */
    U16         devServ_n;          /* id */
    Boolean     (*devServ_fxp)(U16 appID_n, void *data_sp, U32 size, void* devContext_sp);
    U16         appPriority_n;      /* application priority */
    U16         appType_n;
} DevService_s;


typedef Boolean (*MSMService)
(
    U16     appID_n,
    void    *data_sp,
    U32     dataLen,
    void    *devContext_sp
);


#endif  /* __MSMSRV_H__ */
