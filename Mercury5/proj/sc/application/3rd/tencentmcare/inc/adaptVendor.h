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

#include "mcr_typedef.h"
#include "McfCommon_priv.h"

//Relation with MSTAR platform
#include "ven_socket.h"
#include "ven_wap.h"
#include "ven_sdk.h"
#include "ven_stc.h"
#include "ven_kpd.h"
/*
MCF_T_CARD_TO_RUN, 
This macro can not using on 33n terminal, otherwise system browser downloaded TMZ will not be scan.
*/
#define MCF_NAND_FLASH_TO_RUN 				(0)
#define MCF_T_CARD_TO_RUN 					(1) // This type not support NAND Type terminal. Only support NOR Flash Terminal. by KEL
#define MCF_HAVING_NAND_FLASH_USING_T_CARD 	(2) //Because MStar system browser will default to store files to Nand Flash.

/*Start of KEL on 2011-6-20 21:21 MCARE_3.0

THIS MACRO ONLY FOR MSTAR 2.04.02M2 PROJECT.
if your project version is 2.04.02M2,
please open this macro.

OTHERWISE PLEASE MARK THIS MACRO.*/
//#define __TENCENT_WAP_SELECTION__
/*End of KEL on 2011-6-20 21:21 MCARE_3.0*/


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

MINT McfAda_HelpVendorKeyEvent(ven_kpd_key_code_t code);

MINT McfCmn_GetVenMediaFormat(MINT nEnum);

#endif//#ifndef _adaptVendor_h_

