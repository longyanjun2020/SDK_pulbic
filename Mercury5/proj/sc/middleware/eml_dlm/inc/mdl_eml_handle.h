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

#ifndef MDL_EMI_HANDLE_H
#define MDL_EMI_HANDLE_H

//#include "MML_Manager.h"
//#include "MML_Game.h"
//#include "vm_msgofs.hc"
#include "srv_resmgr_mmlgame_types.h"
#include "cus_msg.hc"
//#include "vm_msgt.ht"
/*=============================================================*/
// Extern definition
/*=============================================================*/


/*=============================================================*/
// Data type definition
/*=============================================================*/

typedef enum
{
    EML_GETINFO = 0,
    EML_PLAYCHECK,
    EML_PLAYSTART,
    EML_PLAYSTARTOK,
    EML_KEY,
    EML_STOPBEGIN,
    EML_STOPOK,
    EML_PLAYERROR,
    EML_GETCAPABILITY,
    EML_CLEANUP,
} MDLEML_TASK_MSGTYPE;

typedef enum
{
    EML_FROM_STATECTRL = 0,
    EML_FROM_PLAY,
    EML_FROM_MM,
} MDLEML_TASK_MSGSRC;

typedef struct _MDLEML_TASK_INTERNALINFO {
    MDLEML_TASK_MSGSRC      msgSrc;
    MDLEML_TASK_MSGTYPE     msgType;
    MmlGameUCParam_t        tGameUCParam;      ///< Game use case parameters
} MDLEML_TASK_INTERNALINFO;

typedef struct
{
    MDLEML_TASK_INTERNALINFO    info;
} vm_msgBody_t;

#include "vm_msgt.ht"

#ifdef __SDK_SIMULATION__
#define MDLEML_STATECTRL_MBX        VM_MBX_CUS44
#else
#define MDLEML_STATECTRL_MBX        VM_MBX_CUS44
#endif

/*=============================================================*/
// Macro definition
/*=============================================================*/
#ifndef VM_MSG_DEF
#define VM_MSG_DEF(_ENUM_, _UNION_)		_ENUM_,
#endif
enum
{
#include "mdl_eml_message_define__.hi"
};


/*=============================================================*/
// Data type definition
/*=============================================================*/
/**
 * @brief Internal msg ID for Game
 */
typedef enum
{
    MDLEML_MSGFROM_MM = (MDL_EML_CTL_DEVMSG),
    MDLEML_MSGFROM_INTER,
    MDLEML_CTL_TIMER,
} MdlEmlCtlMsgId_e;

//#define MDLEML_ROM_FROMLOCALMEM

#ifdef __VER_EML__                      //isw mode
#define MDLEML_EN_ISW
#define MDLEML_EN_DRVLAYER

    #ifndef MDLEML_ROM_FROMLOCALMEM
    #define MDLEML_ROM_FROMLOCALMEM
    #endif
#elif defined(__SDK_SIMULATION__)       //simulation mode

#else                                   //target mode
#define MDLEML_EN_DRVLAYER
#define MDLEML_EN_MIDLAYER
//#define MDLEML_EN_SENDTRACE
#endif



#endif //MDL_EMI_HANDLE_H
