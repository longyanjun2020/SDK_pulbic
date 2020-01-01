/*
**  Important : This software is protected by Copyright and the information
**              contained herein is confidential. Distribution, reproduction
**              as well as exploitation and transmission of its contents is
**              not allowed except if expressly permitted. Infringments
**              result in damage claims.
**              Copyright VMTS S.A. (c) 2001
*/


#ifndef __PANEL_INFO_MMP_H__
#define __PANEL_INFO_MMP_H__

#include "vm_types.ht"
#include "msgdidef.h"

    u32     GetScreenWidthMmp(u32 nIndex);
    u32     GetScreenHeightMmp(u32 nIndex);
    void    PrePanelInitMmp(void);
    void    PostPanelInitMmp(void);
	u32     UpdateScreenMmp(u32 PanelID, PMSUPDATELAYER pParam);
    s32     UpdateScreenMLMmp(u32 uPanelID, PMSUPDATE pParam);


#endif //__PANEL_INFO_MMP_H__

