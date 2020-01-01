/**
 *
 * @file    ema_sys_msg.h
 *
 * @brief   This module defines the EMA camera message struct type for system service
 *
 * @author  Pauli Leong
 * @version $Id: ema_sys_msg.h 11919 2008-06-23 06:37:09Z gary.lu $
 *
 */
#ifndef __EMA_SYS_MSG_H__
#define __EMA_SYS_MSG_H__


/*--------------------------------------------------------------------------*/
/* INCLUDE FILE                                                             */
/*--------------------------------------------------------------------------*/
#include "esl_sys_itf.h"


/*--------------------------------------------------------------------------*/
/* PREPROCESSOR CONSTANT DEFINITION                                         */
/*--------------------------------------------------------------------------*/
#ifdef DefExtern
#undef DefExtern
#endif
#ifdef __EMA_PARSE__
#define	DefExtern
#else
#define	DefExtern	extern
#endif


/*--------------------------------------------------------------------------*/
/* PREPROCESSOR MACRO DEFINITION                                            */
/*--------------------------------------------------------------------------*/


/*--------------------------------------------------------------------------*/
/* TYPE DEFINITION                                                          */
/*--------------------------------------------------------------------------*/
typedef struct {
  u32		info;
  u32   userData;
  u32   activeState;
} ema_IntInfo_t;

typedef struct {
  esl_SysFW_e sysFW;
} ema_LoadFW_t;

typedef struct {
  isl_SysMmpVer_t *sysMmpVer;
} ema_MmpVer_t;

typedef struct {
  esl_SysGetDateTimeCB pfnSysGetDateTime;
} ema_RegDateTime_t;

typedef struct {
  esl_SysDateTime_t *pSysDateTime;
} ema_SetDateTime_t;

typedef struct {
  esl_SysMmpStatus_e sysMmpStatus;
} ema_SetMmpStatus_t;

typedef struct {
  esl_SysDbgInfo_t *pDbgInfo;
} ema_DbgInfo_t;

typedef struct {
  esl_SysBistInfo_t *pBistInfo;
} ema_BistInfo_t;


typedef struct{
  esl_SysNotifyCb_t    notify;
  esl_SysNotifyType_e  notifyTyp;
} ema_sysNotifyCmd_t;

typedef struct {
  isl_SysErrCode_e *pStatus;
  isl_SysReadCus_t sysCus;
} ema_SysReadCusCmd_t;

typedef struct {
  esl_SysCapInfo_t sysCapInfo;
} ema_CapCmd_t;

typedef struct {
	ema_TransType_t	TransType;
  esl_SysCb_t     *pSysDoneCB;
	union	{
    ema_IntInfo_t      IntInfo;
    ema_LoadFW_t       loadFW;
    ema_MmpVer_t       MmpVer;
    ema_RegDateTime_t  regDateTime;
    ema_SetDateTime_t  setDateTime;
    ema_SetMmpStatus_t MmpStatus;
    ema_DbgInfo_t      dbgInfo;
    ema_BistInfo_t     bistInfo;
    ema_sysNotifyCmd_t notifyCmd;
    ema_SysReadCusCmd_t sysReadCusCmd;
    bool                enableMMPTimeout;
    ema_CapCmd_t        getCapCmd;
	} param;
} ema_SysCmd_t;

typedef struct{
	u16								prim;
	u16             	sender;
	ema_TransType_t	  TransType;
	ema_ErrCode_e 		errorStatus;
} ema_SysRsp_t;

/**
 *  @brief Notification function, Application needs to provide the function entry
 *
 * @param msmInfo         : Host driver send information (address) for msm streaming mechanism
 * @param userData_n      : Reference value for indicating different sender in same task or check msg response.
 *
 * @return None
 */
typedef void (*emaStreamCb)(u32 msmInfo, u32 userData_n);

typedef struct {
    emaStreamCb pStreamCb;  /*call back function pointer*/
    u32         userData_n; /*user data (the same as ema return call back)*/
    u32         msmInfo;
    u8          type;       /*for identity msm command type (audio or video ...)*/
} ema_msmPrim_t;


/*--------------------------------------------------------------------------*/
/* GLOBAL VARIABLE DEFINITION                                               */
/*--------------------------------------------------------------------------*/


/*--------------------------------------------------------------------------*/
/* GLOBAL FUNCTION DEFINITION                                               */
/*--------------------------------------------------------------------------*/


#endif /* __EMA_SYS_MSG_H__ */


