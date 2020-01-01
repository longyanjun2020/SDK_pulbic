/*
 * @file cus_os_ver.h
 *
 * This file defines the current version number of Mstar OS wrapper (MS wrapper)
 *
 * CUS_OS_VER Format: XYYZZ
 * X:  Major Version (ex: underlying OS change. RTK=1, eCos=2)
 * YY: Minor Version (ex: interface change)
 * ZZ: patch (ex: wrapper internal bug fix, enhancement...etc)
 *
 * @Creator: ericyk.wu at 20100406
 */
#ifndef __SYS_MSWRAPPER_CUS_OS_VER_H__
#define __SYS_MSWRAPPER_CUS_OS_VER_H__

//#define MS_OS_VER	10000	/* 20100406, create for B2 EMMI draft version */

//#define MS_OS_VER	10201	/* 20100406, create for B3 draft version */
                                                 /* MsSend with threshold: new interface since 02 */
                                                 /* __IRAM_ALLOC__: 	  new interface since 01 */
                                                 /* MsMboxStatus: 	  new interface since 01 */
                                                 /* MsInitSemExtend: 	  new interface since 01 */
                                                 /* MsGetSemCount: 	  new interface since 01 */
                                                 /* Callback style timer:  new interface since 01 */
                                                 /* MsResumeTask/MsSuspendTask/MsCheckOsReady: new interface since 01 */
                                                 /* cus_os_flag.c/h: 	  new interface since 01 */

//#define MS_OS_VER	10300	/* 20100526, create for Uncached malloc & dynamic task priority new API */

//#define MS_OS_VER	10400	/* 20100805, create MsSleepExt -> run-time: MsSleep -> exception: pure SYS_UDELAY   */

#define MS_OS_VER	10600	/* 20110725, create C-series APIs   */
							/* MsCallocateMem */
							/* MsCallocateMemLr */
							/* MsGetCPoolMemory */
							/* MsGetCPoolMemoryLr */
							/* MsGetCPoolIdMemory */
							/* MsGetCPoolIdMemoryLr */
							/* MsGetCHeapMemory */
							/* MsGetCHeapMemoryLr */

//#define MS_OS_VER	20000	/* 20100406, create for G1 draft version porting on eCos */

#endif /* __SYS_MSWRAPPER_CUS_OS_VER_H__ */
