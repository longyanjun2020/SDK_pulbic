/****************************************************************************/
/*  File    : ms_data.h                                                     */
/*--------------------------------------------------------------------------*/
/*  Scope   : MSERVICES's global variables                                  */
/*                                                                          */
/*  Contents:                                                               */
/*                                                                          */
/****************************************************************************/
/*
* --------------------------------------------------------------------------
*  Date     | Author | Revision       | Description
* ----------+--------+----------------+-------------------------------------
*/

#ifndef __MS_DATA_H__
#define __MS_DATA_H__

#ifdef __MSERVICES__

#include "sys_rtk_vmrtkho.h"
#include "ms_stmsg.hi"
#include "ms_task.hi"
#include "ms_head.h"
#include "ms_task.h"

#ifdef DECL_RES
#define EXT
#else
#define EXT extern
#endif


/****************************************************************************/
/*                                                                          */
/*                                                                          */
/*                            CONSTANTS                                     */
/*                                                                          */
/*                                                                          */
/****************************************************************************/

#ifdef __TOUCH_SCREEN_MMI__
/****************************************************************************/
/*  Structure : Mserv_Gle_ItemCoordonates_t                                 */
/*--------------------------------------------------------------------------*/
/*									    */
/*  Scope     : y1 y2 coordonates for an browsing menu item    		    */
/*                                                                          */
/*--------------------------------------------------------------------------*/
/****************************************************************************/
typedef struct Mserv_Gle_ItemCoordonates_t_
{
	u16 x1;
	u16 y1;
	u16 x2;
	u16 y2;
} Mserv_Gle_ItemCoordonates_t;
#endif /* __TOUCH_SCREEN_MMI__ */


/****************************************************************************/
/*                                                                          */
/*                                                                          */
/*                       BEGIN OF GLOBAL DATA                               */
/*                                                                          */
/*                                                                          */
/****************************************************************************/
GLOB_DATA_TOP( mserv )

GLOB_DATA(iMserv_3rd_Application_Type_t,Mserv_AP_Running);
/*
** -------------------------------------------------------------------------
**   MIC GENERAL VARIABLES
** -------------------------------------------------------------------------
*/
GLOB_DATA( u8                , Mserv_Mic_ClientId);  /* Mservices client identifier */
GLOB_DATA( iMserv_Mic_TaskState_t, Mserv_Mic_TaskState); /* State of Mservices Task */
///GLOB_DATA( iMserv_Mic_TaskState_t, Mserv_Mic_TaskStatePush); /* State of Push */
///GLOB_DATA( u8, Mserv_Mic_NbClient); /* number of MIC clients */
///GLOB_DATA( u8, Mserv_Mic_DefMdl); /* default VM_MBX_MDL */
GLOB_DATA( u8, Mserv_Mic_CurUseGPRSModId); /* default VM_MBX_MDL */
GLOB_DATA( u8, Mserv_Mic_SubscribeId[2]); /* IDs to subscribe two MDL */

/*
** -------------------------------------------------------------------------
**   CONFIGURATION VARIABLES
** -------------------------------------------------------------------------
*/
///GLOB_DATA( u16  , Mserv_Mic_ProfileToStore); /* Indicates which profile must be stored when parsing provisioning document */
///GLOB_DATA( u8   , Mserv_Mic_CustoProfileReading); /* if we are reading profiles from custo */

/*
** -------------------------------------------------------------------------
**   NET API VARIABLES
** -------------------------------------------------------------------------
*/
/// GLOB_DATA( Mserv_Mic_Net_SessionInfo_t  , Mserv_Mic_NetSession[MSERV_MIC_NET_MAX_SESSION]); /* Session contexts in net api */
/// GLOB_DATA( iMserv_Mic_Net_ComState_t    , Mserv_Mic_NetComState);     /* State of the Net API */
/// GLOB_DATA( vm_VmlMslDataLinkType_t, Mserv_Mic_NetDataLinkType); /* type of the com */

/*
** -------------------------------------------------------------------------
**   PUSH VARIABLES
** -------------------------------------------------------------------------
*/

//// GLOB_DATA(u16,Mserv_Mic_PushSocketIdSms2948);
//// GLOB_DATA(u16,Mserv_Mic_PushSocketIdSms2949);
//// GLOB_DATA(u16,Mserv_Mic_PushChannelSms);
//// GLOB_DATA(bool,Mserv_Mic_PushIsBearerSms);


#ifdef __TOUCH_SCREEN_MMI__
/*
** -------------------------------------------------------------------------
**   TOUCHSCREEN VARIABLES
** -------------------------------------------------------------------------
*/
GLOB_DATA( Mserv_Gle_ItemCoordonates_t*    , Mserv_Gle_TS_ItemZone_Array );
GLOB_DATA( bool                            , Mserv_Gle_TS_Out_Of_Sensitive_Zone );
GLOB_DATA( u8                            , Mserv_Gle_Max_TS_Evts_Dwn );
#endif /* __TOUCH_SCREEN_MMI__ */


/****************************************************************************/
/*                                                                          */
/*                                                                          */
/*                        END OF GLOBAL DATA                                */
/*                                                                          */
/*                                                                          */
/****************************************************************************/
GLOB_DATA_END( mserv );




#define Mserv_AP_Running                 ACCESS_TO( mserv, Mserv_AP_Running)
/* 
** -------------------------------------------------------------------------
**   MIC GENERAL VARIABLES
** -------------------------------------------------------------------------
*/
#define Mserv_Mic_ClientId                 ACCESS_TO( mserv, Mserv_Mic_ClientId)
#define Mserv_Mic_TaskState                ACCESS_TO( mserv, Mserv_Mic_TaskState)
/// #define Mserv_Mic_TaskStatePush            ACCESS_TO( mserv, Mserv_Mic_TaskStatePush)
/// #define Mserv_Mic_NbClient                 ACCESS_TO( mserv, Mserv_Mic_NbClient)
///#define Mserv_Mic_DefMdl                   ACCESS_TO( mserv, Mserv_Mic_DefMdl)
#define Mserv_Mic_CurUseGPRSModId          ACCESS_TO( mserv, Mserv_Mic_CurUseGPRSModId)
#define Mserv_Mic_SubscribeId              ACCESS_TO( mserv, Mserv_Mic_SubscribeId)

/*
** -------------------------------------------------------------------------
**   CONFIGURATION VARIABLES
** -------------------------------------------------------------------------
*/
///#define Mserv_Mic_CfgChannelsNb               ACCESS_TO( mserv, Mserv_Mic_CfgChannelsNb)
///#define Mserv_Mic_CfgNapDefIndex              ACCESS_TO( mserv, Mserv_Mic_CfgNapDefIndex)
///#define Mserv_Mic_CfgCurrentBearer            ACCESS_TO( mserv, Mserv_Mic_CfgCurrentBearer)
///#define Mserv_Mic_CfgChannels                 ACCESS_TO( mserv, Mserv_Mic_CfgChannels)
///#define Mserv_Mic_ProfileToStore              ACCESS_TO( mserv, Mserv_Mic_ProfileToStore)
///#define Mserv_Mic_CustoProfileReading         ACCESS_TO( mserv, Mserv_Mic_CustoProfileReading)

/*
** -------------------------------------------------------------------------
**   NET API VARIABLES
** -------------------------------------------------------------------------
*/
#define Mserv_Mic_NetSession			 ACCESS_TO( mserv, Mserv_Mic_NetSession )
/// #define Mserv_Mic_NetComState			 ACCESS_TO( mserv, Mserv_Mic_NetComState)
/// #define Mserv_Mic_NetDataLinkType        ACCESS_TO( mserv, Mserv_Mic_NetDataLinkType)

/*
** -------------------------------------------------------------------------
**   PUSH VARIABLES
** -------------------------------------------------------------------------
*/

/// #define Mserv_Mic_PushSocketIdSms2948         ACCESS_TO( mserv, Mserv_Mic_PushSocketIdSms2948 )
/// #define Mserv_Mic_PushSocketIdSms2949         ACCESS_TO( mserv, Mserv_Mic_PushSocketIdSms2949 )
/// #define Mserv_Mic_PushChannelSms                ACCESS_TO( mserv, Mserv_Mic_PushChannelSms )
/// #define Mserv_Mic_PushIsBearerSms               ACCESS_TO( mserv, Mserv_Mic_PushIsBearerSms )


/*
** -------------------------------------------------------------------------
**   DOWNLOAD VARIABLES
** -------------------------------------------------------------------------
*/


#undef EXT

#endif  /* __MSERVICES__ */
#endif  /* __MS_DATA_H__ */

