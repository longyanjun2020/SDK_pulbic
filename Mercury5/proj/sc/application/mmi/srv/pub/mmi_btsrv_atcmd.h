/**
 * @file mmi_btsrv_atcmd.h
 *
 * BTSRV structure definition
 *
 * $Id: $
 */
#ifndef __MMI_BTSRV_ATCMD_H__
#define __MMI_BTSRV_ATCMD_H__

#include "mmi_mae_shell.h"

typedef void (*BT_AT_FUNCTION)(IBase *pRecipient, const u8 *);

typedef struct BtATFuncTableTag
{
    const u8 *pAtCmd;
    BT_AT_FUNCTION pAtFunction;
    boolean bWithParm;
}BtATFuncTableS;

typedef enum
{
    BTSRV_ATA = 0
   ,BTSRV_ATD
   ,BTSRV_ATCHUP
   ,BTSRV_ATCHLD
   ,BTSRV_ATBLDN
   ,BTSRV_AT_NUM
} BTSRV_AudioATCmd_e;

typedef struct BtAtCmdTag
{
    BTSRV_AudioATCmd_e eCmdType;
    u8 *pCmdStr;
}BtAtCmd_t;

BT_AT_FUNCTION mmi_bt_ATCMD_function(const u8 *);
//void mmi_bt_ATCMD_AT(IBase* pRecipient, const u8 *);
void mmi_bt_ATCMD_ATA(IBase *pRecipient, const u8 *);
void mmi_bt_ATCMD_ATCHUP(IBase *pRecipient, const u8 *);
void mmi_bt_ATCMD_ATCHLD(IBase *pRecipient, const u8 *);
void mmi_bt_ATCMD_ATBLDN(IBase *pRecipient, const u8 *);
void mmi_bt_not_support(IBase *pRecipient, const u8 *);
void mmi_bt_ATCMD_ATCCWA(IBase *pRecipient, const u8 *ptInd);
void mmi_bt_ATCMD_ATD(IBase *pRecipient, const u8 *ptInd);

BtAtCmd_t* _ATCMD_CreateCmd(BTSRV_AudioATCmd_e eCmdType, const u8 *pCmdStr);
void _ATCMD_FreeCmd(BtAtCmd_t **ppBtAtCmd);

#endif /* __MMI_BTSRV_ATCMD_H__ */
