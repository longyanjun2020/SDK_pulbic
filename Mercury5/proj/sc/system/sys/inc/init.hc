/******************************************************************/
/*  File    : INIT.HC                                             */
/*-------------------------------------------------------------   */
/*  Scope   :  INIT constants                                     */
/*                                                                */
/*  Changes    :                                                  */
/*--------------------------------------------------------------  */
/*   Date       | Author |      Err  |        Modification        */
/*--------------+--------+-----------+--------------------------  */
/*  15/02/1995  |  FCH   |           |        Creation            */
/*--------------+--------+-----------+--------------------------- */
/*  29/01/1996  |  PGU   |           | - reduce env.              */
/******************************************************************/

#ifndef __INIT_HC__
#define __INIT_HC__


#include "rtkini.h"

#define NB_MAX_TASK       17     /* including idle task */
#define NB_MAX_MBX        19
#define NB_MAX_SEM        11
#define NB_MAX_TIMER      50
#define NB_MAX_ENV        150    /* define Env system + Env queue */
#define NB_MAX_POOL       10

#define DATA_SIZE                                                          \
        NB_MAX_TASK * LEN_rtk_Task_t +                                     \
        (NB_MAX_MBX + NB_MAX_POOL) * LEN_rtk_Mailbox_t +                   \
        NB_MAX_SEM * LEN_rtk_Semaphor_t + NB_MAX_TIMER * LEN_rtk_Timer_t + \
        NB_MAX_ENV * LEN_rtk_Envelop_t +                                   \
        NB_MAX_POOL * LEN_rtk_Pool_t


#endif /* __INIT_HC__ */
