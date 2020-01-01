
#ifndef __MDL_DISP_TASK_H__
#define __MDL_DISP_TASK_H__

#ifdef INTERFACE
#undef INTERFACE
#endif

#ifdef __MDL_DISP_TASK_C__
#define INTERFACE
#else
#define INTERFACE extern
#endif

#include "msgdidef.h"
#include "sys_sys_bootinit.h"

/*--------------------------------------------------------------------------*/
/* PREPROCESSOR CONSTANT DEFINITION                                         */
/*--------------------------------------------------------------------------*/

INTERFACE __ONCE_CALL_ON_BOOT__ void MdlDispTaskInit(void);
INTERFACE void MdlDispTaskParser(void *pMessage);
INTERFACE s32 MdlDispTaskUpdateScreenAppEx(u32 nPanelID, PMSUPDATE pParam);
INTERFACE s32 MdlDispTaskUpdateScreenApp(u32 nPanelID, PMSUPDATELAYER pParam);
INTERFACE s32 MdlDispTaskUpdateScreenMdl(u32 nPanelID, PMSUPDATELAYER pParam);
INTERFACE bool MdlDispTaskPollMdlUpdateFinish(u32 nPanelID);


#endif//__MDL_DISP_TASK_H__

