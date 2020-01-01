
#ifndef _MFE_IOS_H_
#define _MFE_IOS_H_

#include "mhve_ios.h"

typedef struct MfeIos_t
{
    mhve_ios    mios;
    void*       p_base;
    mfe6_reg*   p_regs;
} mfe6_ios;

#define BIT_ENC_DONE    (1<<0)
#define BIT_BUF_FULL    (1<<1)

#endif /*_MFE_IOS_H_*/
