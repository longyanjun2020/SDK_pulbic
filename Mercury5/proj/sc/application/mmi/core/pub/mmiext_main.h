/**
* @file mmi_ext_main.h
*
* @version $Id$
*/

#ifndef __MMI_EXT_MAIN_H__
#define __MMI_EXT_MAIN_H__

/**
* The entry function of MMI ext task.
*/
void MMIExt_Task_Init(void);

/**
* The exit function of MMI ext task.
*/
void MMIExt_Task_Terminate(void);

/** 
* The message parser function for MMI ext task.
*/
void MMIExt_Task_ParseMsg(void*);


#endif /* __MMI_EXT_MAIN_H__ */
