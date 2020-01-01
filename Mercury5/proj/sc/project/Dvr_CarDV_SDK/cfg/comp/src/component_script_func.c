//==============================================================================
//
//                              INCLUDE FILE
//
//==============================================================================

#include "cust_component_cfg.h"
#include "component_cfg.h"
#include "mmp_component_ctl.h"

#include "component_raws.h"
#include "component_dip.h"
#include "component_scl.h"
#include "component_display.h"
#include "component_mfe.h"
#include "component_mgr.h"
#include "component_jpe.h"
#include "component_jpemgr.h"
#include "component_jpd.h"
#include "component_aud.h"
#include "component_pip.h"
#include "component_hvd.h"
#include "component_HvdTimerCtl.h"
#include "component_adas.h"
#include "component_huvc.h"
#include "component_uvc.h"
#include "component_memhost.h"

//==============================================================================
//
//                              EXTERN VARIABLE
//
//==============================================================================

extern CUSTOMER_COMP_SCRIPT         m_stScriptCfg[] ;
extern CUSTOMER_COMP_PORT_SCRIPT    m_stPortScriptCfg[];

//==============================================================================
//
//                              FUNCTIONS
//
//==============================================================================

#if 0
void _____Script_Function_____(){}
#endif

//------------------------------------------------------------------------------
//  Function    : Component_Initial_Script
//  Description :
//------------------------------------------------------------------------------
static MMP_ERR Component_Initial_Script(COMPONENT_CFG *pCompCfgList, MMP_ULONG ulCompNum)
{
    MMP_ERR             eRetErr = MMP_ERR_NONE;
    MMP_ULONG           i, j;
    MMP_COMPONENT_BASE  *pComp = NULL;

    for (i = 0 ; i < ulCompNum; i++) {

        pComp = pCompCfgList[i].Component;

        // Initial in port
        if (pComp->pInPort) {
            if (pComp->pInPort->pfInit) {
                pComp->pInPort->pfInit((void *)pComp);
            }
        }

        pComp->ubOutputPortNum = pCompCfgList[i].ubOutPortNum;

        // Initial out port
        for (j = 0 ; j < pCompCfgList[i].ubOutPortNum; j++) {
            if (pComp->pOutPort[j].pfInit) {
                pComp->pOutPort[j].pfInit((void *)pComp);
            }
            pComp->pOutPort[j].State = PORT_INITIAL;
        }

        eRetErr = MMP_CompCtl_InitComponent(pComp);
        if (eRetErr) {
            UartSendTrace("[%s] InitComponent Fail\r\n", pComp->name);
            //return MMP_COMPONENT_ERR_CALL;
        }

        pComp->ulState      = MMP_COMPONENT_STATE_LOADED;
        pComp->bRegistered  = MMP_TRUE;
    }

    return MMP_ERR_NONE;
}

//------------------------------------------------------------------------------
//  Function    : Component_Open_Script
//  Description :
//------------------------------------------------------------------------------
static MMP_ERR Component_Open_Script(COMPONENT_CFG *pCompCfgList, MMP_ULONG ulCompNum)
{
    MMP_ERR             eRetErr = MMP_ERR_NONE;
    MMP_ULONG           i = 0, j = 0;
    MMP_COMPONENT_BASE  *pComp = NULL;
    MMP_UBYTE           ubMaxIdx = 0;
    MMP_UBYTE           ubMinIdx = 0xFF;
    for (i = 0 ; i < ulCompNum; i++) {

        pComp = pCompCfgList[i].Component;

        if (pComp->pInPort) {
            if (pComp->pInPort->pfOpen) {
                pComp->pInPort->pfOpen((void *)pComp);
            }
            pComp->pInPort->PrevComponent = pCompCfgList[i].InPortComponent;
            pComp->pInPort->pCurComponent = pComp;
            pComp->pInPort->State = PORT_OPEN;
        }

        pComp->ubOutputPortNum = pCompCfgList[i].ubOutPortNum;

        for (j = 0 ; j < pCompCfgList[i].ubOutPortNum; j++) {

            pComp->pOutPort[j].pCurComponent = pComp;
            pComp->pOutPort[j].NextComponent = pCompCfgList[i].OutPortComponent[j];
            pComp->pOutPort[j].bufInfo.ubBufOrder = pCompCfgList[i].ubOutPortOrder[j];
            if (ubMaxIdx <  pComp->pOutPort[j].bufInfo.ubBufOrder) {
                ubMaxIdx = pComp->pOutPort[j].bufInfo.ubBufOrder;
            }
            if (ubMinIdx >  pComp->pOutPort[j].bufInfo.ubBufOrder) {
                ubMinIdx = pComp->pOutPort[j].bufInfo.ubBufOrder;
            }

            if (pCompCfgList[i].bOutPortEn[j]) {
                if (pComp->pOutPort[j].pfOpen) {
                    pComp->pOutPort[j].pfOpen((void *)pComp);
                }
                pComp->pOutPort[j].State = PORT_OPEN;
            }
            else {
                pComp->pOutPort[j].State = PORT_CLOSE;
            }
        }

        eRetErr = MMP_CompCtl_InitMemoryInfo(pComp);
        if (eRetErr) {
            UartSendTrace("[%s] InitMemoryInfo Fail\r\n", pComp->name);
            return MMP_COMPONENT_ERR_CALL;
        }
        pComp->MemoryInfo->ulBufOrderInfo.ubMaxBufOrder = ubMaxIdx;
        pComp->MemoryInfo->ulBufOrderInfo.ubMinBufOrder = ubMinIdx;
        if (ubMaxIdx != ubMinIdx) {
            pComp->MemoryInfo->ulBufOrderInfo.bBurOder = 1;
        }
        else {
            pComp->MemoryInfo->ulBufOrderInfo.bBurOder = 0;
        }

        eRetErr = MMP_CompCtl_AllocateMemory((void *)pComp);
        if (eRetErr) {
            UartSendTrace("[%s] AllocateMemory Fail\r\n", pComp->name);
            return MMP_COMPONENT_ERR_CALL;
        }

        eRetErr = MMP_CompCtl_OpenComponent((void *)pComp);
        if (eRetErr) {
            UartSendTrace("[%s] OpenComponent Fail\r\n", pComp->name);
            return MMP_COMPONENT_ERR_CALL;
        }

        pComp->ulState = MMP_COMPONENT_STATE_IDLE;
    }
    return MMP_ERR_NONE;
}

//------------------------------------------------------------------------------
//  Function    : Component_Close_Script
//  Description :
//------------------------------------------------------------------------------
static MMP_ERR Component_Close_Script(COMPONENT_CFG *pCompCfgList, MMP_ULONG ulCompNum)
{
    MMP_ERR             eRetErr = MMP_ERR_NONE;
    MMP_ULONG           i = 0, j = 0;
    MMP_COMPONENT_BASE  *pComp = NULL;

    for (i = 0 ; i < ulCompNum; i++) {

        pComp = pCompCfgList[i].Component;

        pComp->ulState = MMP_COMPONENT_STATE_LOADED;

        // Close port first
        for (j = 0 ; j < pComp->ubOutputPortNum; j++) {
            pComp->pOutPort[j].State = PORT_CLOSE;
        }

        // Ensure all output buffer usage is free
        eRetErr = MMP_CompCtl_WaitMemoryFree((void *)pComp);
        if (eRetErr) {
            UartSendTrace("[%s] WaitMemoryUseDone Fail\r\n", pComp->name);
            return MMP_COMPONENT_ERR_CALL;
        }

        eRetErr = MMP_CompCtl_CloseComponent((void *)pComp);
        if (eRetErr) {
            UartSendTrace("[%s] CloseComponent Fail\r\n", pComp->name);
            return MMP_COMPONENT_ERR_CALL;
        }

        eRetErr = MMP_CompCtl_FreeMemory((void *)pComp);
        if (eRetErr) {
            UartSendTrace("[%s] FreeMemory Fail\r\n", pComp->name);
            return MMP_COMPONENT_ERR_CALL;
        }
    }
    return MMP_ERR_NONE;
}

//------------------------------------------------------------------------------
//  Function    : Component_UnInitial_Script
//  Description :
//------------------------------------------------------------------------------
static MMP_ERR Component_UnInitial_Script(COMPONENT_CFG *pCompCfgList, MMP_ULONG ulCompNum)
{
    MMP_ERR             eRetErr = MMP_ERR_NONE;
    MMP_ULONG           i = 0;
    MMP_COMPONENT_BASE  *pComp = NULL;

    for (i = 0 ; i < ulCompNum; i++) {
        pComp = pCompCfgList[i].Component;

        pComp->ulState = MMP_COMPONENT_STATE_INVALID;

        eRetErr = MMP_CompCtl_UnInitComponent(pComp);
        if (eRetErr) {
            UartSendTrace("[%s] UnInitComponent Fail\r\n", pComp->name);
            return MMP_COMPONENT_ERR_CALL;
        }
    }
    return MMP_ERR_NONE;
}

//------------------------------------------------------------------------------
//  Function    : Component_Update_Script
//  Description :
//------------------------------------------------------------------------------
static MMP_ERR Component_Update_Script(COMPONENT_CFG *pCompCfgList, MMP_UBYTE ubIndex, MMP_UBYTE ubDevIdx)
{
    MMP_ERR             eRetErr = MMP_ERR_NONE;
    MMP_COMPONENT_BASE  *pComp = NULL;
    void                *pstMemInfo = NULL;
    void                *pstDevInfo = NULL;
    MMP_ULONG           ulDevInfoSize = 0;
    MMP_ULONG           ulMemInfoSize = 0;

    switch(pCompCfgList[ubIndex].Type) {
        case DEVICE_SCL0:
            pstDevInfo = (void *)&Component_SCL0_Handler[ubDevIdx];
            pstMemInfo = (void *)&Component_SCL0_Memory[ubDevIdx];
            ulDevInfoSize = sizeof(Component_SCL0_Handler[ubDevIdx]);
            ulMemInfoSize = sizeof(Component_SCL0_Memory[ubDevIdx]);
            break;
        case DEVICE_SCL1:
            pstDevInfo = (void *)&Component_SCL1_Handler[ubDevIdx];
            pstMemInfo = (void *)&Component_SCL1_Memory[ubDevIdx];
            ulDevInfoSize = sizeof(Component_SCL1_Handler[ubDevIdx]);
            ulMemInfoSize = sizeof(Component_SCL1_Memory[ubDevIdx]);
            break;
        case DEVICE_DISPLAY:
            pstDevInfo = (void *)&Component_Display_Handler[ubDevIdx];
            pstMemInfo = (void *)&Component_Display_Memory[ubDevIdx];
            ulDevInfoSize = sizeof(Component_Display_Handler[ubDevIdx]);
            ulMemInfoSize = sizeof(Component_Display_Memory[ubDevIdx]);
            break;
        case DEVICE_MFE:
            pstDevInfo = (void *)&Component_MFE_Handler[ubDevIdx];
            pstMemInfo = (void *)&Component_MFE_Memory[ubDevIdx];
            ulDevInfoSize = sizeof(Component_MFE_Handler[ubDevIdx]);
            ulMemInfoSize = sizeof(Component_MFE_Memory[ubDevIdx]);
            break;
        case DEVICE_MGR:
            pstDevInfo = (void *)&Component_MGR_Handler[ubDevIdx];
            pstMemInfo = (void *)&Component_MGR_Memory[ubDevIdx];
            ulDevInfoSize = sizeof(Component_MGR_Handler[ubDevIdx]);
            ulMemInfoSize = sizeof(Component_MGR_Memory[ubDevIdx]);
            break;
        case DEVICE_DIP_ROTATE:
            pstDevInfo = (void *)&Component_DIP_R_Handler[ubDevIdx];
            pstMemInfo = (void *)&Component_DIP_R_Memory[ubDevIdx];
            ulDevInfoSize = sizeof(Component_DIP_R_Handler[ubDevIdx]);
            ulMemInfoSize = sizeof(Component_DIP_R_Memory[ubDevIdx]);
            break;
        case DEVICE_DIP_MOVE:
            pstDevInfo = (void *)&Component_DIP_Move_Handler[ubDevIdx];
            pstMemInfo = (void *)&Component_DIP_Move_Memory[ubDevIdx];
            ulDevInfoSize = sizeof(Component_DIP_Move_Handler[ubDevIdx]);
            ulMemInfoSize = sizeof(Component_DIP_Move_Memory[ubDevIdx]);
            break;
        case DEVICE_DIP_SCALE:
            pstDevInfo = (void *)&Component_DIP_Scale_Handler[ubDevIdx];
            pstMemInfo = (void *)&Component_DIP_Scale_Memory[ubDevIdx];
            ulDevInfoSize = sizeof(Component_DIP_Scale_Handler[ubDevIdx]);
            ulMemInfoSize = sizeof(Component_DIP_Scale_Memory[ubDevIdx]);
            break;
        case DEVICE_DIP_CC:
            pstDevInfo = (void *)&Component_DIP_CC_Handler[ubDevIdx];
            pstMemInfo = (void *)&Component_DIP_CC_Memory[ubDevIdx];
            ulDevInfoSize = sizeof(Component_DIP_CC_Handler[ubDevIdx]);
            ulMemInfoSize = sizeof(Component_DIP_CC_Memory[ubDevIdx]);
            break;
        case DEVICE_DIP_OSDB:
            pstDevInfo = (void *)&Component_DIP_OSDB_Handler[ubDevIdx];
            pstMemInfo = (void *)&Component_DIP_OSDB_Memory[ubDevIdx];
            ulDevInfoSize = sizeof(Component_DIP_OSDB_Handler[ubDevIdx]);
            ulMemInfoSize = sizeof(Component_DIP_OSDB_Memory[ubDevIdx]);
            break;
        case DEVICE_PIP:
            pstDevInfo = (void *)&Component_PIP_Handler[ubDevIdx];
            pstMemInfo = (void *)&Component_PIP_Memory[ubDevIdx];
            ulDevInfoSize = sizeof(Component_PIP_Handler[ubDevIdx]);
            ulMemInfoSize = sizeof(Component_PIP_Memory[ubDevIdx]);
            break;
        case DEVICE_RAW_STORE:
            pstDevInfo = (void *)&Component_RAWS_Handler[ubDevIdx];
            pstMemInfo = (void *)&Component_RAWS_Memory[ubDevIdx];
            ulDevInfoSize = sizeof(Component_RAWS_Handler[ubDevIdx]);
            ulMemInfoSize = sizeof(Component_RAWS_Memory[ubDevIdx]);
            break;
        case DEVICE_JPE:
            pstDevInfo = (void *)&Component_JPE_Handler[ubDevIdx];
            pstMemInfo = (void *)&Component_JPE_Memory[ubDevIdx];
            ulDevInfoSize = sizeof(Component_JPE_Handler[ubDevIdx]);
            ulMemInfoSize = sizeof(Component_JPE_Memory[ubDevIdx]);
            break;
        case DEVICE_JPE_MGR:
            pstDevInfo = (void *)&Component_JPEMGR_Handler[ubDevIdx];
            pstMemInfo = (void *)&Component_JPEMGR_Memory[ubDevIdx];
            ulDevInfoSize = sizeof(Component_JPEMGR_Handler[ubDevIdx]);
            ulMemInfoSize = sizeof(Component_JPEMGR_Memory[ubDevIdx]);
            break;
        case DEVICE_JPD:
            pstDevInfo = (void *)&Component_JPD_Handler[ubDevIdx];
            pstMemInfo = (void *)&Component_JPD_Memory[ubDevIdx];
            ulDevInfoSize = sizeof(Component_JPD_Handler[ubDevIdx]);
            ulMemInfoSize = sizeof(Component_JPD_Memory[ubDevIdx]);
            break;
        case DEVICE_HVD:
            pstDevInfo = (void *)&Component_HVD_Handler[ubDevIdx];
            pstMemInfo = (void *)&Component_HVD_Memory[ubDevIdx];
            ulDevInfoSize = sizeof(Component_HVD_Handler[ubDevIdx]);
            ulMemInfoSize = sizeof(Component_HVD_Memory[ubDevIdx]);
            break;
        case DEVICE_TCL:
            pstDevInfo = (void *)&Component_TCL_Handler[ubDevIdx];
            pstMemInfo = (void *)&Component_TCL_Memory[ubDevIdx];
            ulDevInfoSize = sizeof(Component_TCL_Handler[ubDevIdx]);
            ulMemInfoSize = sizeof(Component_TCL_Memory[ubDevIdx]);
            break;
        case DEVICE_ADAS:
            pstDevInfo = (void *)&Component_Adas_Handler[ubDevIdx];
            pstMemInfo = (void *)&Component_Adas_Memory[ubDevIdx];
            ulDevInfoSize = sizeof(Component_Adas_Handler[ubDevIdx]);
            ulMemInfoSize = sizeof(Component_Adas_Memory[ubDevIdx]);
            break;
        case DEVICE_MDTC:
            pstDevInfo = (void *)&Component_Mdtc_Handler[ubDevIdx];
            pstMemInfo = (void *)&Component_Mdtc_Memory[ubDevIdx];
            ulDevInfoSize = sizeof(Component_Mdtc_Handler[ubDevIdx]);
            ulMemInfoSize = sizeof(Component_Mdtc_Memory[ubDevIdx]);
            break;
        case DEVICE_HUVC :
            pstDevInfo = (void *)&Component_HUVC_Handler[ubDevIdx];
            pstMemInfo = (void *)&Component_HUVC_Memory[ubDevIdx];
            ulDevInfoSize = sizeof(Component_HUVC_Handler[ubDevIdx]);
            ulMemInfoSize = sizeof(Component_HUVC_Memory[ubDevIdx]);
            break;
        case DEVICE_UVC :
            pstDevInfo = (void *)&Component_UVC_Handler[ubDevIdx];
            pstMemInfo = (void *)&Component_UVC_Memory[ubDevIdx];
            ulDevInfoSize = sizeof(Component_UVC_Handler[ubDevIdx]);
            ulMemInfoSize = sizeof(Component_UVC_Memory[ubDevIdx]);
            break;
        case DEVICE_MEMHOST:
            pstDevInfo = (void *)&Component_MemHost_Handler[ubDevIdx];
            pstMemInfo = (void *)&Component_MemHost_Memory[ubDevIdx];
            ulDevInfoSize = sizeof(Component_MemHost_Handler[ubDevIdx]);
            ulMemInfoSize = sizeof(Component_MemHost_Memory[ubDevIdx]);
            break;
        default:
            UartSendTrace("Component DevType Unknown\r\n");
            return eRetErr;
            break;
    }

    pComp = pCompCfgList[ubIndex].Component;

    //UartSendTrace("Update Comp Type %2d Idx %2d\r\n", pCompCfgList[ubIndex].Type, ubDevIdx);

    if ((pComp->DeviceInfo) && (pstDevInfo))
        memcpy(pComp->DeviceInfo, pstDevInfo, ulDevInfoSize);
    if ((pComp->MemoryInfo) && (pstMemInfo))
        memcpy(pComp->MemoryInfo, pstMemInfo, ulMemInfoSize);

    return eRetErr;
}

#if 0
void _____Port_Script_Function_____(){}
#endif

//------------------------------------------------------------------------------
//  Function    : Component_Open_PortScript
//  Description :
//------------------------------------------------------------------------------
static MMP_ERR Component_Open_PortScript(COMPONENT_PORT_CFG *pPortCfg)
{
    MMP_COMPONENT_BASE  *pComp = NULL;
    MMP_ULONG           i = 0;
    MMP_UBYTE           ubPortIdx = pPortCfg[i].ubOutPortEnIdx;

    pComp = pPortCfg[i].Component;

    if (pPortCfg[i].bOutPortEn[ubPortIdx]) {
        pComp->pOutPort[ubPortIdx].State = PORT_OPEN;
    }

    return MMP_ERR_NONE;
}

//------------------------------------------------------------------------------
//  Function    : Component_Close_PortScript
//  Description :
//------------------------------------------------------------------------------
static MMP_ERR Component_Close_PortScript(COMPONENT_PORT_CFG *pPortCfg)
{
    MMP_COMPONENT_BASE  *pComp = NULL;
    MMP_ULONG           i = 0;
    MMP_UBYTE           ubPortIdx = pPortCfg[i].ubOutPortEnIdx;

    pComp = pPortCfg[i].Component;

    if (pPortCfg[i].bOutPortEn[ubPortIdx]) {
        pComp->pOutPort[ubPortIdx].State = PORT_CLOSE;
    }

    return MMP_ERR_NONE;
}

#if 0
void _____Public_Script_Function_____(){}
#endif

//------------------------------------------------------------------------------
//  Function    : OpenScript
//  Description :
//------------------------------------------------------------------------------
MMP_ERR OpenScript(MMP_UBYTE ubScriptIdx)
{
    CUSTOMER_COMP_SCRIPT    *pstCfg = &m_stScriptCfg[ubScriptIdx];
    MMP_UBYTE               ubNum = pstCfg->ubNum;
    MMP_UBYTE               i = 0;

    if (pstCfg->ubScriptId >= COMPO_SCRIPT_TYPE_NUM) {
        return MMP_COMPONENT_ERR_PARAMETER;
    }
    if (pstCfg->ScriptCfg == NULL || ubNum == 0) {
        return MMP_COMPONENT_ERR_PARAMETER;
    }
    if (pstCfg->bOpened) {
        return MMP_COMPONENT_ERR_OPEN;
    }

    pstCfg->bOpened = MMP_TRUE;

    UartSendTrace(FG_YELLOW("=> OpenScript [%d][%s]\r\n"), ubScriptIdx, pstCfg->ubName);

    for (i = 0 ; i < ubNum; i++) {
        Component_Update_Script(pstCfg->ScriptCfg, i, pstCfg->ubUpdIdx[i]);
    }

    Component_Initial_Script(pstCfg->ScriptCfg, ubNum);
    Component_Open_Script(pstCfg->ScriptCfg,  ubNum);

    return MMP_ERR_NONE;
}

//------------------------------------------------------------------------------
//  Function    : CloseScript
//  Description :
//------------------------------------------------------------------------------
MMP_ERR CloseScript(MMP_UBYTE ubScriptIdx)
{
    CUSTOMER_COMP_SCRIPT    *pstCfg = &m_stScriptCfg[ubScriptIdx];
    MMP_UBYTE               ubNum = pstCfg->ubNum;

    if (pstCfg->ubScriptId >= COMPO_SCRIPT_TYPE_NUM) {
        return MMP_COMPONENT_ERR_PARAMETER;
    }
    if (pstCfg->ScriptCfg == NULL || ubNum == 0) {
        return MMP_COMPONENT_ERR_PARAMETER;
    }
    if (!pstCfg->bOpened) {
        return MMP_COMPONENT_ERR_OPEN;
    }

    UartSendTrace(FG_YELLOW("=> CloseScript [%d][%s]\r\n"), ubScriptIdx, pstCfg->ubName);

    Component_Close_Script(pstCfg->ScriptCfg, ubNum);
    Component_UnInitial_Script(pstCfg->ScriptCfg, ubNum);

    pstCfg->bOpened = MMP_FALSE;

    return MMP_ERR_NONE;
}

//------------------------------------------------------------------------------
//  Function    : OpenPortScript
//  Description :
//------------------------------------------------------------------------------
MMP_ERR OpenPortScript(MMP_UBYTE ubPortScriptIdx)
{
    CUSTOMER_COMP_PORT_SCRIPT    *pPortSrciptList = &m_stPortScriptCfg[ubPortScriptIdx];
    COMPONENT_PORT_CFG           *pPortCfg = pPortSrciptList->ScriptCfg;

    if (pPortSrciptList->ubScriptId >= PORT_SCRIPT_TYPE_NUM) {
        return MMP_COMPONENT_ERR_PARAMETER;
    }
    if (pPortSrciptList->ScriptCfg == NULL) {
        return MMP_COMPONENT_ERR_PARAMETER;
    }

    #if 0
    if (ubPortScriptIdx != PORT_SCRIPT_VR_PRM_BAYER_THUMB &&
        ubPortScriptIdx != PORT_SCRIPT_VR_SHARE_THUMB &&
        ubPortScriptIdx != PORT_SCRIPT_VR_SCD_BAYER_THUMB &&
        ubPortScriptIdx != PORT_SCRIPT_VR_PRM_ANADEC_THUMB_RAW1 &&
        ubPortScriptIdx != PORT_SCRIPT_VR_SCD_ANADEC_THUMB &&
        ubPortScriptIdx != PORT_SCRIPT_VR_USBH_THUMB) {
        UartSendTrace(FG_BLUE("=> OpenPortScript [%d][%s]\r\n"), ubPortScriptIdx, pPortSrciptList->ubName);
    }
    #endif

    Component_Open_PortScript(pPortCfg);

    return MMP_ERR_NONE;
}

//------------------------------------------------------------------------------
//  Function    : ClosePortScript
//  Description :
//------------------------------------------------------------------------------
MMP_ERR ClosePortScript(MMP_UBYTE ubPortScriptIdx)
{
    CUSTOMER_COMP_PORT_SCRIPT    *pPortSrciptList = &m_stPortScriptCfg[ubPortScriptIdx];
    COMPONENT_PORT_CFG           *pPortCfg = pPortSrciptList->ScriptCfg;

    if (pPortSrciptList->ubScriptId >= PORT_SCRIPT_TYPE_NUM) {
        return MMP_COMPONENT_ERR_PARAMETER;
    }
    if (pPortSrciptList->ScriptCfg == NULL) {
        return MMP_COMPONENT_ERR_PARAMETER;
    }

    #if 0
    if (ubPortScriptIdx != PORT_SCRIPT_VR_PRM_BAYER_THUMB &&
        ubPortScriptIdx != PORT_SCRIPT_VR_SHARE_THUMB &&
        ubPortScriptIdx != PORT_SCRIPT_VR_PRM_ANADEC_THUMB_RAW1 &&
        ubPortScriptIdx != PORT_SCRIPT_VR_SCD_BAYER_THUMB &&
        ubPortScriptIdx != PORT_SCRIPT_VR_SCD_ANADEC_THUMB &&
        ubPortScriptIdx != PORT_SCRIPT_VR_USBH_THUMB) {
        UartSendTrace(FG_BLUE("=> ClosePortScript [%d][%s]\r\n"), ubPortScriptIdx, pPortSrciptList->ubName);
    }
    #endif

    Component_Close_PortScript(pPortCfg);

    return MMP_ERR_NONE;
}

