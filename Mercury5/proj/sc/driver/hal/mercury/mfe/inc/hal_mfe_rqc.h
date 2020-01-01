
#ifndef _MFE_RCTL_H_
#define _MFE_RCTL_H_

#include "mhve_rqct_ops.h"
#include "mhve_arqc_ops.h"

typedef struct MfeRctl_t
{
    rqct_ops    rqct;               /* RQCT Operations */
    rqct_att    attr;               /* RQCT Attribute */
    int         i_period;           /* GOP */
    int         i_pcount;           /* Encoded Picture Count (0, 1 ~ i_period) */
#define RCTL_CFG_MB_DQP      (1<<0)
#define RCTL_CFG_NIGHT       (1<<2)
    int         i_refcnt;           /* Reference Frame Count */
    int         i_config;           /* Not Used Now */
} mfe6_rqc;

#define QP_UPPER        (48)
#define QP_LOWER        (12)
#define QP_RANGE        (QP_UPPER-QP_LOWER)
#define QP_MAX          (51)
#define QP_MIN          (10)
#define QP_IFRAME_DELTA (-2)    //I-frame QP delta from P-frame

void* RqctMfeAcquire(int, int);
char* RqctMfeComment(int);

/* basic functions of mfe rate-controller */
int MrqcSetRqcf(rqct_ops* rqct, rqct_cfg* rqcf);
int MrqcGetRqcf(rqct_ops* rqct, rqct_cfg* rqcf);
int MrqcEncBuff(rqct_ops* rqct, rqct_buf* buff);
int MrqcRoiDraw(rqct_ops* rqct, mhve_job* mjob);

/* functions to insert/remove additional rate-controller */
int RqctMfeInsert(void*(*allc)(int), char*(*desc)(void));
int RqctMfeRemove(void);

#endif /*_MFE_RCTL_H_*/
