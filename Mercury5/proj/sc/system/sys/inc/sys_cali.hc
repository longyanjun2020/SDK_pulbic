/***************************************************************************/
/*  File       : sys_cali.hc                                               */
/*-------------------------------------------------------------------------*/
/*  Scope      :                                                           */
/*                                                                         */
/*  Content    :                                                           */
/*                                                                         */
/*  Change     :                                                           */
/***************************************************************************/
#ifndef __SYS_CALI_HC__
#define __SYS_CALI_HC__

/***************************************************************************/
/*           MS ORG CALL Calibration  parameters                           */
/***************************************************************************/
#define CAL_MS_ORG_CALL       0x16
#define CAL_MS_ORG_CALL_REQ   (CAL_MS_ORG_CALL | TYP_REQ)
#define CAL_MS_ORG_CALL_RSP   (CAL_MS_ORG_CALL | TYP_RSP)

/***************************************************************************/
/*                           FOR PROD                                      */
/***************************************************************************/
#define SYS_NO_CUST_TASKS       0x40
#define SYS_NO_CUST_TASKS_REQ   (SYS_NO_CUST_TASKS | TYP_REQ)
#define SYS_NO_CUST_TASKS_RSP   (SYS_NO_CUST_TASKS | TYP_RSP)

#define SYS_ALL_TASKS_ACT       0x41
#define SYS_ALL_TASKS_ACT_REQ   (SYS_ALL_TASKS_ACT | TYP_REQ)
#define SYS_ALL_TASKS_ACT_RSP   (SYS_ALL_TASKS_ACT | TYP_RSP)

#endif // __SYS_CALI_HC__
