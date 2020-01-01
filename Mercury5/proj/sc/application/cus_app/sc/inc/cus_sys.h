#ifndef __CUS_SYS__
#define __CUS_SYS__

// include this file to know rtk constants related to customer resources
/**!
 *     \file cus_sys.h
 *
 *     interface between system and kernel
 *
 ****/

#include "sys_rtk_config.h"
#include "vm_app.ho"
#include "sys_sys_vm_sys.h"

/**!
 *    \brief maximum number of customer tasks
 ****/
#define CUS_TASK_MAX  RTK_MAX_CUSTOMER_TASKS

/**!
 *    \brief default stack size for a customer task
 ****/
#define CUS_DEFAULT_STACKSIZE 4096

/**!
 *    \brief minimal customer stack size
 ****/
#define CUS_MIN_STACKSIZE 512

// those requestID is to request system to change CPU profile.
#define SYSTEM_REQUEST_BY_PARSE_TASK   0x0001
#define SYSTEM_REQUEST_BY_BACKLIGHT    0x0002
#define SYSTEM_REQUEST_BY_MMPSE        0x0004
#define SYSTEM_REQUEST_BY_IMAGECODEC   0x0008
#define SYSTEM_REQUEST_BY_MMI          0x0010
#define SYSTEM_REQUEST_BY_NES          0x0020
#define SYSTEM_REQUEST_BY_ALL          0xFFFF





/* stack 23 porting -- begin */
extern const ascii cus_GsmHandsetName[];
//extern const ascii cus_MmiRelease[];
extern const char sw_verInfo[];
/* stack 23 porting -- end */

/**!
 *   \fn void cus_Main(void)
 *
 *   \brief function called by middleware to create customer system resources
 *
 *   This function is called during middleware initialisation to allow the
 *   customer to create all its system resources ( threads / semaphores / ...)
 *   It should be a brief function and MUST return to its caller as soon as
 *   possible so the middleware can finalize its initialisation.
 *   During this call no scheduling is allowed and the function implementation
 *   should not depend on the execution of the tasks it creates.
 *
 *   \return void
 *
 *****/
extern void cus_Main(void);

/**!
 *   \fn s32  vm_mdl_CustomTaskCreate(void        (*AppliInit) (vm_apmInitType_e ),
 *  				      void        (*AppliParser) (vm_msg_t* ),
 *                                    u32 prio,void *stackAddress,
 *				      u32 stackSize);
 *
 *   \brief Creates a customer task
 *
 *   This function creates a customer task.
 *   Customer tasks count is limited to \ref CUS_TASK_MAX
 *   the priority of customer tasks is always lower than system tasks
 *   priorities
 *
 *   \param AppliInit    the task initialisation function
 *   \param AppliParser  the task parser function
 *   \param prio         the priority of the task
 *   \param stackAddress the address of the stack to use (it is created if NULL)
 *   \param stackSize    the size of the stack to use (CUS_DEFAULT_STACKSIZE if stackSize is lower than  \ref CUS_MIN_STACKSIZE )
 *
 *   \return the task identifier or 0 if the task creation failed
 *
 *****/
extern s32  vm_CustomTaskCreate(char* pTaskName, 
                    void        (*AppliInit) (vm_apmInitType_e ),
				    void        (*AppliParser) (vm_msg_t* ),
				    u32 prio,
				    void *stackAddress,
				    u32 stackSize
#if defined(__TIME_SLICE_SCHEDULE__)
                   ,u32 TimeSliceLeft
                   ,u32 TimeSliceMax
#endif
				    );

/**!
 *   \fn s32  vm_DynamicCustomTaskDelete(u8 TaskId);
 *
 *   \brief delete a dynamic customer task
 *
 *   This function delete a dynamic customer task.
 *   Customer tasks count is limited to \ref CUS_TASK_MAX
 *
 *   \param TaskId    deleted tsak
 *
 *   \return RTK_OK or ERROR_ID
 *
 *****/
extern s32  vm_DynamicCustomTaskDelete(u8 TaskId);

/**!
 *   \fn s32  vm_DynamicCustomTaskCreate(void (*AppliInit) (void * ),
 *			     void (*AppliParser) (vm_msg_t * ),
 *			     u32 Priority,
 *			     u32 *pStackTop,
 *			     u32 StackSize,
 *			     void *pInitArgs,
 *			     u8 *TaskId);
 *
 *   \brief Creates a dynamic customer task
 *
 *   This function creates a dynamic customer task.
 *   Customer tasks count is limited to \ref CUS_TASK_MAX
 *   the priority of customer tasks is always lower than system tasks
 *   priorities
 *
 *   \param AppliInit    the task initialisation function
 *   \param AppliParser  the task parser function
 *   \param Priority         the priority of the task
 *   \param pStackTop the address of the stack to use (it is created if NULL)
 *   \param stackSize    the size of the stack to use (CUS_DEFAULT_STACKSIZE if stackSize is lower than  \ref CUS_MIN_STACKSIZE )
 *   \param pInitArgs   arguments of the task initialisation function
 *   \param TaskId    will be filled an ID if successfully created, otherwise *TaskId=NULL
 *
 *   \return the task identifier or 0 if the task creation failed
 *
 *****/
extern s32  vm_DynamicCustomTaskCreate(char* pTaskName,
                void (*AppliInit) (void * ),
			    void (*AppliParser) (vm_msg_t * ),
			    u32 Priority,
			    u32 *pStackTop,
			    u32 StackSize,
			    void *pInitArgs,
			    u8 *TaskId
#if defined(__TIME_SLICE_SCHEDULE__)
                ,u32 TimeSliceLeft
                ,u32 TimeSliceMax
#endif
			    );

/**!
 *      \brief get the mailbox id related to a task id
 ****/
#define CUSTOMER_TASK_MAILBOX(_taskid) ((_taskid-RTK_FIRST_CUSTOMER_TASKID)+RTK_FIRST_CUSTOMER_MAILBOXID)


/**@fn cus_DumpHighSpeedCPUUsage
 * @brief  When system detects illegal CPU profile behavior, call this product specific function to dump necessary stuff
 *         and trigger exception.
 */

void cus_DumpHighSpeedCPUUsage(void);

/**u32 *cus_ApmStackBase(void);
 * brief:  query the minimum address of custom task stack
 */
u32 *cus_ApmStackBase(void);

#endif //__CUS_SYS__
