/**
*
* @file    adaptVendor.h
* @brief    This file is adapt vendor 
*
* @author	singzhang
* @Date		2011-01-14	  
*
*/ 
#ifndef _adaptVendor_h_
#define _adaptVendor_h_

#include "McfCommon.h"
#include "McfCommon_priv.h"

//Relation with MSTAR platform
#include "ven_socket.h"
#include "ven_wap.h"
#include "ven_sdk.h"
#include "ven_stc.h"
#include "ven_kpd.h"

#define MCF_NAND_FLASH_TO_RUN 				(0)
#define MCF_T_CARD_TO_RUN 					(1) // This type not support NAND Type terminal. Only support NOR Flash Terminal. by KEL

#define MCF_PORTING_TRACE   //Support porting Trace function. KEL.
/*
This mcaro is design for mutex Tencent Background apps. Fad.
*/
#ifdef __NAND__
#define MCF_MULTIBG_SUPPORT
#endif

// Fake MAX Key.
#define	MCF_ADA_KEY_MAX      (40) // equal to #define	MCF_KEY_MAX      (40)
/*
Key CallBack Value Internal Table.
#define	MCF_KEY_0   (0)
#define	MCF_KEY_1   (1)	 
#define	MCF_KEY_2   (2)
#define	MCF_KEY_3   (3)
#define	MCF_KEY_4   (4)
#define	MCF_KEY_5   (5)
#define	MCF_KEY_6   (6)
#define	MCF_KEY_7   (7)
#define	MCF_KEY_8   (8)
#define	MCF_KEY_9   (9)
#define	MCF_KEY_LSK  (10)
#define	MCF_KEY_RSK  (11)
#define	MCF_KEY_CSK  (12)
#define	MCF_KEY_ENTER       (13)
#define	MCF_KEY_UP_ARROW      (14)
#define	MCF_KEY_DOWN_ARROW      (15)
#define	MCF_KEY_LEFT_ARROW      (16)
#define	MCF_KEY_RIGHT_ARROW       (17)
#define	MCF_KEY_END     (18)
#define	MCF_KEY_STAR    (19)
#define	MCF_KEY_POUND   (20)
#define	MCF_KEY_SEND1     (21)
#define	MCF_KEY_SEND2     (22)
	//键个数最大个数40
#define	MCF_KEY_MAX      (40)
*/

ven_app_id_t getMCareAppID();

// 退出MCare
MVOID ExitMCare( MVOID* aData );

// MCare从前台切换到后台
MVOID ForeGroundMCare( MVOID* aData );

// MCare从后台切换到前台
MVOID BackGroundMCare( MVOID* aData );

//平台必须开放到.c的函数。
MUINT	McfCmn_GetVenNetworkProfileSize(MVOID);

MINT McfCmn_GetTerminalMemoryType(MVOID);

MBOOL McfCmn_GetDisplayMgrStatus(MVOID);


MBOOL McfCmn_HelpWapBrowser(MINT handle, MWCHAR *pwUrl, MUSHORT nURLLen);

MBOOL McfCmn_GetWLanStatus(MVOID);

MVOID McfAda_HelpVendorKeyEvent(ven_kpd_key_code_t* code);

MINT McfCmn_GetVenMediaFormat(MINT nEnum);

MBOOL McfCmn_GetMultiBGSupportStatus(MVOID);
#endif//#ifndef _adaptVendor_h_

