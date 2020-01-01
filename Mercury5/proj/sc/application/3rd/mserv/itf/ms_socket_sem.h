#ifndef __MS_SOCKET_SEM_H__
#define __MS_SOCKET_SEM_H__

#include "sys_MsWrapper_cus_os_sem.h"

#define MSERV_INIT_SEM(SEM)	\
	do	\
	{	\
		MsInitSem(SEM, 1);\
	}while(FALSE);

#define MSERV_SS_UNINIT_SEM

#define MSERV_LOCK_SEM(SEM)	\
	do	\
	{	\
		MsConsumeSem(SEM);\
	}while(FALSE);

#define MSERV_UNLOCK_SEM(SEM)	\
	do	\
	{	\
		MsProduceSem(SEM);\
	}while(FALSE);

#endif //__MS_SOCKET_SEM_H__
