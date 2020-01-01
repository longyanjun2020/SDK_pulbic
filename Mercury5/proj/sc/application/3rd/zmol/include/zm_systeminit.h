#ifndef _ZHANGM_SYSTEM_INIT_H_
#define _ZHANGM_SYSTEM_INIT_H_

#include "zm_typedef.h"

/*
 * 大拇指系统初始化mmi\Framework\Tasks\TasksSrc\MMITask.c 
 *						--> InitAllApplications 函数中调用
 */
zm_extern zm_void zm_start_init(zm_void);

/*
 * 设置IMSI, 在 mmi\MiscFramework\MiscFrameworkSrc\NetworkFunctions.c 
 *					--> RspToTestRoamingEnabled函数中调用
 */
zm_extern zm_void zm_set_imsi(const zm_int8* pImsi);

#endif//_ZHANGM_SYSTEM_INIT_H_
