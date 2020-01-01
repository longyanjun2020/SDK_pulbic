
/****************************************************************************/
/*  File    : sys_sys_task_priority.h                                       */
/*--------------------------------------------------------------------------*/
/*  Scope   : define task priority                                          */
/*                                                                          */
/*  Contents:                                                               */
/*                                                                          */
/*                                                                          */
/*                                                                          */
/*                                                                          */
/*  Historical :                                                            */
/****************************************************************************/

#ifndef __SYS_SYS_TASK_PRIORITY_H__
#define __SYS_SYS_TASK_PRIORITY_H__


#include "sys_rtk_config.h"
#include "vm_osdef.hc"
#include "vm_types.ht"  /* __MSTAR_DUAL_SIM_REDUCE_CODE__ */

#ifndef __HWL_TINY__

/* !!!!!!!!!!! DO NOT CHANGE ANYTHING STARTING FROM HERE !!!!!!!!!!!!  */
#undef TASK_DEF
#define TASK_DEF(n, pfn, prio, ss, te) n##_TASK,

typedef enum {
	TASK_BEG = -1,
	#include "sys_sys_task_internal.h"
	__LAST_SYSYEM_TASK__
} TaskID_e;

// Customer tasks
#define CUS1           (__LAST_SYSYEM_TASK__ + 1)      /* previously used as BAT Customer Task */
#define CUS2           (__LAST_SYSYEM_TASK__ + 2)      /* previously used as DEV Customer Task */
#define CUS3           (__LAST_SYSYEM_TASK__ + 3)      /* previously used as MMI Customer Task */
#define CUS4           (__LAST_SYSYEM_TASK__ + 4)
#define CUS5           (__LAST_SYSYEM_TASK__ + 5)
#define CUS6           (__LAST_SYSYEM_TASK__ + 6)
#define CUS7           (__LAST_SYSYEM_TASK__ + 7)
#define CUS8           (__LAST_SYSYEM_TASK__ + 8)
#define CUS9           (__LAST_SYSYEM_TASK__ + 9)

#else //__HWL_TINY__

#define IDLE_TASK       0
#define SPV_TASK        1
#define V24_TASK        2

#endif //__HWL_TINY__


// this should no more be used
#define __LAST_TASK    (RTK_MAX_TASKS-1)

#define MMI            CUS3 /* Will deseapperead ! for trace in mmi files */

/* !!!!!!!!!!!!!!!!!!! CHANGES ALLOWED FROM THERE !!!!!!!!!!!!!!!!!! */






/******************************************************************************/
/******************************************************************************/
/* task proirity definition are move form cus_app.c to here since include the */
/* C file would make trouble to those modules which need using dynamic task   */
/******************************************************************************/
/******************************************************************************/



// tasks priority:  !!!! WARNING !!!! => Prio 9 is reserved for MDL !!!
//                  Only prio 11 & prio 10 can be used for customer applicative tasks
//                  to be higher than MDL task.
//                  All others priorities values are reserved exclusively for Core software tasks
//                  and have higher priority than all customer tasks, including MDL.

// big number is high priority

#define CUS1_PRIO          59 // DEV => CUS1 set with highest priority to let touch screen smooth
#define CUS2_PRIO          56 // EMA
#define CUS3_PRIO          11  // MMI
#define CUS4_PRIO          54  // MRL


#ifdef __DALVIK__
#define CUS5_PRIO          8  // DALVIK
	#else
		#if defined(__JAVA_OAKMONT__)
			#define CUS5_PRIO          6  // Java Aplix VM
		#elif defined(__JAVA_DELTA__)
			#define CUS5_PRIO          8  // Java
		#elif defined(__NCC_3RD_JAVA_PORTING_LAYER__)
			#ifndef __SDK_SIMULATION__
				#define CUS5_PRIO          8  // Java
			#else
				#define CUS5_PRIO          20  // Java
			#endif//__SDK_SIMULATION__
		#elif defined(__FEATURE_IPTV__)
			#define CUS5_PRIO          8 // IPTV
		#else
			#define CUS5_PRIO          20
	#endif
#endif //DALVIK

#define CUS6_PRIO          32 //53  // BT bluetooth
#define CUS7_PRIO          19  // MSRV Mservices
#define CUS8_PRIO          57 // VOC Audio (Voice, PCM, FM Radio)
#define CUS9_PRIO          60 // DSR high priority task
#define CUS10_PRIO         58 // GPD (General Peripheral Device)
#define CUS11_PRIO         9  // VFS task (priority should be adjust)

#ifdef __DALVIK__
#define CUS12_PRIO         20 //DALVIK
#else
	#if defined(__JAVA_OAKMONT__)
		#define CUS12_PRIO         20  // Java Aplix Main
	#elif defined(__JAVA_DELTA__)
		#define CUS12_PRIO         20
	#elif defined(__NCC_3RD_JAVA_PORTING_LAYER__) // NCC
		#ifndef __SDK_SIMULATION__
			#define CUS12_PRIO         20  // Java
		#else
			#define CUS12_PRIO          8 // Java
		#endif//__SDK_SIMULATION__
	#elif defined(__FEATURE_IPTV__)
		#define CUS12_PRIO         20
	#else
		#define CUS12_PRIO         8
	#endif
#endif //__DALVIK__

#define CUS13_PRIO         21  // WAP
#define CUS14_PRIO         1
#define CUS15_PRIO         4
#define CUS16_PRIO         52  // ResMgr
#define CUS17_PRIO         10  // FileMgr
#define CUS18_PRIO         55  //EFS
#define CUS19_PRIO         17  // FileMgrTest
#define CUS20_PRIO         18 // FT auto test
#define CUS21_PRIO         69 //mdl audio read
#define CUS22_PRIO         70 //mdl audio decode
#define CUS23_PRIO         72 //mdl audio control
#define CUS24_PRIO         68 //mdl audio record
#define CUS25_PRIO         67 //mdl audio record write
#define CUS26_PRIO         32
#define CUS27_PRIO         37 // Main
#define CUS28_PRIO         36 // Video
#define CUS29_PRIO         35 // Audio
#define CUS30_PRIO         34 // Write
#define CUS31_PRIO         33 //image decoder statecontrol
#define CUS32_PRIO         24 //image decoder main thread
#define CUS33_PRIO         41
#define CUS34_PRIO         40
#define CUS35_PRIO         42  // TVCTL
#define CUS36_PRIO         43  // MDLTV
#define CUS37_PRIO         45  // wifi driver
#define CUS38_PRIO         30  // wifi driver
#define CUS39_PRIO         43  // supplicant
#define CUS40_PRIO         7   // MdlEfatTask
#define CUS41_PRIO         48
#define CUS42_PRIO         49
#define CUS43_PRIO         50
#define CUS44_PRIO         51
#define CUS45_PRIO         61 // mdl audio getinfo
#define CUS46_PRIO         62 // mdl audio midi conv
#define CUS47_PRIO         63
#define CUS48_PRIO         64
#define CUS49_PRIO         65
#define CUS50_PRIO         23 // MdwComm
#define CUS51_PRIO         69 // 3G CL
#define CUS52_PRIO         46 // 3G MDLUT
#define CUS53_PRIO         67
#define CUS54_PRIO         (CUS5_PRIO+2) //E2P (NAND) must higher than Java
#define CUS55_PRIO         15 // SD1
#define CUS56_PRIO         15 // SD2
#define CUS57_PRIO         73
#define CUS58_PRIO         74
#define CUS59_PRIO         75 // MtMgr
#define CUS60_PRIO         76
#define CUS61_PRIO         14 // NAND background Task
#define CUS62_PRIO         65 // VT Task
#define CUS63_PRIO         25 // VT Manager
#define CUS64_PRIO         80
#define CUS65_PRIO         40 // play DTMF tone task
#define CUS66_PRIO         72 // AEC PLAY
#define CUS67_PRIO         12 // NQQ MUX
#define CUS68_PRIO         60 // 65 //AEC process
#define CUS69_PRIO         85
#define CUS70_PRIO         69 // MdlEfatTask2
#define CUS71_PRIO         39 // DualStar GPS Communication Task
#define CUS72_PRIO         38 // DualStar GPS Host Driver Task
#define CUS73_PRIO         29 // DualStar GPS Middleware Task
#define CUS74_PRIO         61
#define CUS75_PRIO         44 // 3G IP
#define CUS76_PRIO         45 // 3G CM
#define CUS77_PRIO         68 // 3G MUX
#define CUS78_PRIO         67 // 3G PPP

#define CUS79_PRIO         22 // RTSP


#define DYN_DX_PRIO        43
#define DYN_VD_PRIO        44
#define DYN_AD_PRIO        45
#define DYN_VO_PRIO        46

#endif /* __SYS_SYS_TASK_PRIORITY_H__ */
