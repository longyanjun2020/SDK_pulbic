/**
* @file ResMgr_Task.h
*
* This header file defines the interfaces of resource manager task.
*
*/

#ifndef __RESMGR_TASK_H__
#define __RESMGR_TASK_H__

/*=============================================================*/
// Include Files
/*=============================================================*/

/*=============================================================*/
// Type Declarations
/*=============================================================*/

/*=============================================================*/
// Function Declarations
/*=============================================================*/

void ResMgrTask_Init(void);
void ResMgrTask_Parser(void *pMsg);
void ResMgrTask_IntParser(void *pMsg);

#endif //__RESMGR_TASK_H__

