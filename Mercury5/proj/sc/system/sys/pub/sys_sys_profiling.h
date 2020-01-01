/****************************************************************************/
/*  File    : sys_sys_profiling.h                                           */
/*--------------------------------------------------------------------------*/
/*  Scope   											*/
/*	      : 0. task base cpu usage profiling  (dump to tmt)               */
/*          : 1. task base cpu usage profiling  (for query)                 */
/*          : 2. disable interrupt profiling                                */
/*          : 3. function base profiling                                    */
/*          : 4.  light weighttask single task cpu usage profiling       */
/*                                                                          */
/*                                                                          */
/*  Contents:                                                               */
/*                                                                          */
/*                                                                          */
/*  Historical:                                                             */
/*--------------------------------------------------------------------------*/
/*  Date    | Author | Err  |  Modfification                                */
/*----------+--------+------+-----------------------------------------------*/
/* 17.03.11 |  Eric   |      |  Creation                                     */
/****************************************************************************/

#ifndef __SYS_SYS_PROFILING_H__
#define __SYS_SYS_PROFILING_H__



#include "sys_rtk_ho.h"



#if defined(__SOFTWARE_WATCHDOG_PROFILE__)
// profiling control block : swd_Profonlyile_Info_t only be used by Swd Profiling 
typedef struct swd_Profile_Info_
{
	u32 u32_StartStdaCount;
	u32 u32_QbCountSum;
	u32 u32_ScheduledCount;		// max: 2^32-1
	u32 u32_PreemptedSchedCount;	// max: 2^32-1
}swd_Profile_Info_t;
#endif 


/* It is transformation of swd_Profile_Info_t in order to save memory */
typedef struct Profile_Info_
{
	u32 u32_QbCountSum;
	u16 u16_ScheduledCount;		// max: 2^16-1
	u16 u16_PreemptedSchedCount;	// max: 2^16-1
}Profile_Info_t;

#define SYS_BOOTCHART_MAX_TASK (RTK_MAX_TASKS+1) 
typedef struct bootchart_profile_block_
{
    u8 bitmap[(SYS_BOOTCHART_MAX_TASK+7)/8];
    u8 cpu_usage;
    u8 mem_usage;
} bootchart_profile_block_t;

#define SYS_BOOTCHART_MAX_SLOT	500
#define SYS_BOOTCHART_SAMPLES_PER_SLOT	500
#define SYS_BOOTCHART_DEFAULT_PERIOD_MS 20

typedef struct bootchart_profile_control_
{
    u32 interval_ms;
    u32 timer_id;
    u32 samples_per_slot;
    u32 samples_curr;
    u32 slot_max;
    u32 slot_curr; 
    u32 timestamp_start;
    u32 total_memory;
    u32 cpu_idle;
    u32 cpu_other;
    bootchart_profile_block_t *slots[SYS_BOOTCHART_MAX_SLOT];
    bool enabled;
} bootchart_profile_control_t;

#if defined(__SOFTWARE_WATCHDOG_PROFILE__)
#define MAX_SWD_TIMEOUT     3       // Max software watchdog timeout tolerance
#endif

#define __CPU_PROFILE_MULTI_HANDLE__

#define MAX_PROFILE_HANDLE_NUM 16

typedef enum {
  SYS_PROFILING_OK= 10,                         ///< No error - the function call was successfull
  SYS_PROFILING_NOT_START,
  SYS_PROFILING_NOT_END,
  SYS_PROFILING_INVALID_HANDLE,
  SYS_PROFILING_OUT_OF_MEMORY,
  SYS_PROFILING_BAD_PARAM,
  SYS_PROFILING_OCCUPY,
} _SYS_Profiling_ErrCode_e;


//control block associate with bitmap index
typedef struct
{
	char handle_name[8]; 			//unique ASCII string ID
	Profile_Info_t *block_address; //working buffer address, for tasks
	Profile_Info_t INT_profile_info; // for interrupt
	u16 numOfProfileTasks;			// to record the num of max tasks
	u8 used; 						//denote buffer is still used or not
	u8 padding[1]; 				//to be added
}Profile_Register_t;


/* light weight profiling control block */
typedef struct
{
	char handle_name[8]; 			//unique ASCII string ID
	u32 totalTime;	
	u32 executeTime;
	u8 profileTaskID;				// the task ID which we track
	u8 used; 						//denote buffer is still used or not
	u8 padding[2]; 				//to be added
}Light_Weight_Profile_Register_t;


#define PROFILING_BUFFER_USED 0xFE
#define PROFILING_BUFFER_NOTUSED 0xFB

/************************************************/
/*  Scope   : 1. task base cpu usage profiling  (for query)          */
/************************************************/

/* pls follw below rule to use (to avoid memory leakage)		
 * 1. start ("name")											
 * 2. end ("name")											
 * 3. query or dump (give "name" and whether buffer should be free)	
 * p.s. buffer life cycle is controlled by user, if profiling is on going		
 *      the buffer won't be freed.                                          
 */

 /**
 * \brief Start or restart CPU profile usage
 * \param[in] handle_name: ASCII string identify the client name
 * \return _SYS_Profiling_ErrCode_e
 */
_SYS_Profiling_ErrCode_e sys_startProfiling(char *handle_name);

/**
 * \brief Stop profile CPU usage
 * \param[in] handle_name: ASCII string identify the client name
 * \return _SYS_Profiling_ErrCode_e
 */
_SYS_Profiling_ErrCode_e sys_endProfiling(char *handle_name);

/**
 * \brief dump all profiling stats
 * \param[in] handle_name: ASCII string identify the client name
 * \param[in] u8 terminate identify whether buffer is used or not later after this call
 *\  			Note: If profiling on-going, buffer won't be freed.
 * \return none
 */
void sys_dumpProfileInfo(char *handle_name, u8 terminate);

/**
 * \brief Query profile is start or not
 * \return TURE/FALSE
 */
bool sys_queryProfileState(void);

/**
 * \brief query CPU usage of the given task ID
 * \param[in] handle_name: ASCII string identify the client name
 * \param[in] u8 terminate identify whether buffer is used or not later after this call
 * \  			Note: If profiling on-going, buffer won't be freed.
 * \param[in] u32 Task ID
 * \param[out] u32 *totalTime : pointer to a u32 which contain total CPU tick
 * \param[out] u32 *executeTime : pointer to a u32 whichthe executed executed CPU tick of given TaskID
 * \return Result and _SYS_Profiling_ErrCode_e
 */
_SYS_Profiling_ErrCode_e sys_queryCPUusage(char *handle_name, u8 terminate, u32 taskID, u32 *totalTime, u32 *executeTime);

/************************************************/
/*  Scope   : 2. disable interrupt profiling                                   */
/************************************************/



/************************************************/
/*  Scope   : 3. function base profiling                                       */
/************************************************/



/************************************************/
/*  Scope   : 4.  light weighttask single task cpu usage profiling  */
/************************************************/

/* pls follw below rule to use (to avoid memory leakage)		
 * 1. start ("name")											
 * 2. end("name")											
 * 3. query (give "name" and whether buffer should be free)	
 * p.s. buffer life cycle is controlled by user, if profiling is on going		
 *      the buffer won't be freed.                                          
 */

 /**
 * \brief Start or restart light weight CPU usage profile 
 * \param[in] handle_name: ASCII string identify the client name
 * \param[in] TaskID: Specified the task id of the task needed to be profile
 * \return _SYS_Profiling_ErrCode_e
 */
_SYS_Profiling_ErrCode_e sys_startLightWeightProfiling(char *handle_name, u8 TaskID);

/**
 * \brief Stop light weight CPU usage profile 
 * \param[in] handle_name: ASCII string identify the client name
 * \return _SYS_Profiling_ErrCode_e
 */
_SYS_Profiling_ErrCode_e sys_endLightWeightProfiling(char *handle_name);

/**
 * \brief query CPU usage of the given handle name
 * \param[in] handle_name: ASCII string identify the client name
 * \param[in] u8 terminate identify whether buffer is used or not later after this call
 * \  			Note: If profiling on-going, buffer won't be freed.
 * \param[out] u32 *totalTime : pointer to a u32 which contain total CPU tick
 * \param[out] u32 *executeTime : pointer to a u32 whichthe executed executed CPU tick of given TaskID
 * \return Result and _SYS_Profiling_ErrCode_e
 */
_SYS_Profiling_ErrCode_e sys_queryLightWeightCPUusage(char *handle_name, u8 terminate, u32 *totalTime, u32 *executeTime);

_SYS_Profiling_ErrCode_e sys_bootchart_profile_start(u32 interval_ms);
_SYS_Profiling_ErrCode_e sys_bootchart_profile_stop(void);
bool sys_bootchart_profile_get_state(void);

#endif /* __SYS_SYS_PROFILING_H__ */

