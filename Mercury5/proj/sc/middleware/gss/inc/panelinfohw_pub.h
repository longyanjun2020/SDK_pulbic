/*
**  Important : This software is protected by Copyright and the information
**              contained herein is confidential. Distribution, reproduction
**              as well as exploitation and transmission of its contents is
**              not allowed except if expressly permitted. Infringments
**              result in damage claims.
**              Copyright VMTS S.A. (c) 2001
*/


#ifndef __PANEL_INFO_HW_H__
#define __PANEL_INFO_HW_H__

#include "vm_types.ht"
#include "msgdidef.h"
#include "sys_sys_bootinit.h"


    void    PrePanelInitHW(void);
    __ONCE_CALL_ON_BOOT__ void    PostPanelInitHW(void);
	u32     UpdateScreenHW(u32 PanelID, PMSUPDATELAYER pParam);
    s32     UpdateScreenMLHW(u32 uPanelID, PMSUPDATE pParam);


#endif //__PANEL_INFO_HW_H__
