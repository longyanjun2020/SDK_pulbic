////////////////////////////////////////////////////////////////////////////////
//
// Copyright (c) 2006-2009 MStar Semiconductor, Inc.
// All rights reserved.
//
// Unless otherwise stipulated in writing, any and all information contained
// herein regardless in any format shall remain the sole proprietary of
// MStar Semiconductor Inc. and be kept in strict confidence
// (¡§MStar Confidential Information¡¨) by the recipient.
// Any unauthorized act including without limitation unauthorized disclosure,
// copying, use, reproduction, sale, distribution, modification, disassembling,
// reverse engineering and compiling of the contents of MStar Confidential
// Information is unlawful and strictly prohibited. MStar hereby reserves the
// rights to any and all damages, losses, costs and expenses resulting therefrom.
//
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
///@file       mdl_vdr_cus_os.h
///@author  MStar Semiconductor Inc.
///@brief
////////////////////////////////////////////////////////////////////////////////

#ifndef __MDL_VDR_CUS_OS_H__
#define __MDL_VDR_CUS_OS_H__

#define __OS_RTK__

//-----------------------------------------------------------------------------
// Include Files
//-----------------------------------------------------------------------------


//-----------------------------------------------------------------------------
// Extern Definition
//-----------------------------------------------------------------------------


//-----------------------------------------------------------------------------
//Macros Defines
//-----------------------------------------------------------------------------


//-----------------------------------------------------------------------------
// Data Type Definition
//-----------------------------------------------------------------------------
#if defined (__OS_RTK__)
#define MBOX_HANDLE_T					MsMailbox_e
#define MBOX_INFO_T						void *
#endif
//-----------------------------------------------------------------------------
// Variable Definition
//-----------------------------------------------------------------------------


//-----------------------------------------------------------------------------
// Global Function Definition
//-----------------------------------------------------------------------------


#endif	// __MDL_VDR_CUS_OS_H__

