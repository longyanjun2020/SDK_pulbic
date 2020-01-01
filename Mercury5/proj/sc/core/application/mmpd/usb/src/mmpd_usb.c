/// @ait_only
//==============================================================================
//
//  File        : mmpd_usb.c
//  Description : USB Control Driver Function
//  Author      : Hans Liu
//  Revision    : 1.0
//
//==============================================================================

#include "lib_retina.h"
#include "mmpd_usb.h"
#include "mmph_hif.h"
#include "mmpf_usbphy.h"
#if (SUPPORT_USB_HOST_FUNC)
#include "mmpf_usbh_ctl.h"
#endif

/** @addtogroup MMPD_USB
 *  @{
 */

//==============================================================================
//
//                              VARIABLES
//
//==============================================================================

static MMP_ULONG        m_ulPCSYNCHandshakeBuf;
static MMP_ULONG        m_ulPCSYNCInBuf;
static MMP_ULONG        m_ulPCSYNCOutBuf;

MMP_ULONG        gulMemDevCmdAddr;
MMP_ULONG        gulMemDevAckAddr;

//==============================================================================
//
//                              EXTERNAL FUNCTIONS
//
//==============================================================================

extern MMP_ERR MMPF_USB_RegisterCallback(MMP_USB_EVENT event,
                                         MMP_USB_Callback *callback);

//==============================================================================
//
//                              FUNCTION PROTOTYPES
//
//==============================================================================
//==============================================================================
//  Function    : MMPD_USB_AdjustVref
//==============================================================================
/**
    @brief  Adjust USB PHY signal by tuning BG Vref
    @param[in] Vref : BG Vref, @ref MMP_USB_VREF
    @return MMP_ERR_NONE for success, others for failure.
*/
MMP_ERR MMPD_USB_AdjustVref(MMP_ULONG Vref)
{
    return MMP_ERR_NONE;
}

//==============================================================================
//  Function    : MMPD_USB_AdjustBiasCurrent
//==============================================================================
/**
    @brief  Adjust USB PHY signal by tuning BG bias current
    @param[in] BiasCurrent : BG bias current, @ref MMP_USB_BIAS_CURRENT
    @return MMP_ERR_NONE for success, others for failure.
*/
MMP_ERR MMPD_USB_AdjustBiasCurrent(MMP_ULONG BiasCurrent)
{
    return MMP_ERR_NONE;
}

//==============================================================================
//  Function    : MMPD_USB_AdjustSignal
//==============================================================================
/**
    @brief  Adjust USB PHY signal by tuning HS Tx current & squelch level
    @param[in] txCur : HS Tx current, @ref MMPS_USB_TX_CUR
    @param[in] TxCurPlus : HS Tx current fine tune, @ref MMP_USB_TX_CUR_PLUS
    @param[in] SqLevel : Squelch Level, @ref MMPS_USB_SQ
    @return MMP_ERR_NONE for success, others for failure.
*/
MMP_ERR MMPD_USB_AdjustSignal(MMP_ULONG TxCur, MMP_ULONG TxCurPlus, MMP_ULONG SqLevel)
{
    return MMP_ERR_NONE;
}

//==============================================================================
//  Function    : MMPD_USB_RegisterCallback
//==============================================================================
/** @brief The function set callbacks for usb events

The function sets callbacks for the following events.
    * MSDC read   : in receiving MSDC read command
    * MSDC write  : in receiving MSDC write command

@param[in] Event    Specified the event for registered callback.
@param[in] CallBack The callback to be executed when the specified event happens.

@return It reports the status of the operation.

@warn The registered callback will not be auto deleted, please register a NULL
      to delete it.
*/
MMP_ERR MMPD_USB_RegisterCallback(MMP_USB_EVENT event, MMP_USB_Callback *callback)
{
    return MMPF_USB_RegisterCallback(event, callback);
}

//==============================================================================
//  Function    : MMPD_USB_SetMode
//==============================================================================
/**
    @brief  Set usb mode
    @param[in] ubMode : usb mode
    @return MMP_ERR_NONE
*/
MMP_ERR MMPD_USB_SetMode(MMP_UBYTE ubMode)
{
    MMPH_HIF_WaitSem(GRP_IDX_USB, 0);
    MMPH_HIF_SendCmd(GRP_IDX_USB, (ubMode<<8) | HIF_USB_CMD_SET_MODE);
    MMPH_HIF_ReleaseSem(GRP_IDX_USB);
    return MMP_ERR_NONE;
}

//==============================================================================
//  Function    : MMPD_USB_GetOpMode
//==============================================================================
MMP_ERR MMPD_USB_GetMode(MMP_UBYTE *UsbOpMode)
{
    MMP_ERR mmpstatus;

    MMPH_HIF_WaitSem(GRP_IDX_USB, 0);
    mmpstatus = MMPH_HIF_SendCmd(GRP_IDX_USB, HIF_USB_CMD_GET_MODE);

    if (mmpstatus == MMP_ERR_NONE) {
        *UsbOpMode = MMPH_HIF_GetParameterB(GRP_IDX_USB, 0);
    }
    MMPH_HIF_ReleaseSem(GRP_IDX_USB);

    return mmpstatus;
}
//==============================================================================
//  Function    : MMPD_USB_StopDevice
//==============================================================================
MMP_ERR MMPD_USB_StopDevice(void)
{
    MMPH_HIF_WaitSem(GRP_IDX_USB, 0);
    MMPH_HIF_SendCmd(GRP_IDX_USB, HIF_USB_CMD_STOPDEVICE);
    MMPH_HIF_ReleaseSem(GRP_IDX_USB);
    return MMP_ERR_NONE;
}
//==============================================================================
//  Function    : MMPD_USB_ConnectDevice
//==============================================================================
MMP_ERR MMPD_USB_ConnectDevice(void)
{
    MMPH_HIF_WaitSem(GRP_IDX_USB, 0);
    MMPH_HIF_SendCmd(GRP_IDX_USB, HIF_USB_CMD_CONNECTDEVICE);
    MMPH_HIF_ReleaseSem(GRP_IDX_USB);
    return MMP_ERR_NONE;
}

//==============================================================================
//  Function    : MMPD_USB_GetWriteFlag
//==============================================================================
MMP_ERR MMPD_USB_GetWriteFlag(MMP_UBYTE *USBIsWriting)
{
    MMP_ERR mmpstatus;

    MMPH_HIF_WaitSem(GRP_IDX_USB, 0);
    mmpstatus = MMPH_HIF_SendCmd(GRP_IDX_USB, HIF_USB_CMD_GET_RW_FLAG|HIF_USB_GET_W_FLAG);

    if (mmpstatus == MMP_ERR_NONE) {
        *USBIsWriting = MMPH_HIF_GetParameterB(GRP_IDX_USB, 0);
    }
    MMPH_HIF_ReleaseSem(GRP_IDX_USB);

    return mmpstatus;
}

//==============================================================================
//  Function    : MMPD_USB_GetReadFlag
//==============================================================================
MMP_ERR MMPD_USB_GetReadFlag(MMP_UBYTE *USBIsReading)
{
    MMP_ERR mmpstatus;

    MMPH_HIF_WaitSem(GRP_IDX_USB, 0);
    mmpstatus = MMPH_HIF_SendCmd(GRP_IDX_USB, HIF_USB_CMD_GET_RW_FLAG|HIF_USB_GET_R_FLAG);

    if (mmpstatus == MMP_ERR_NONE) {
        *USBIsReading = MMPH_HIF_GetParameterB(GRP_IDX_USB, 0);
    }
    MMPH_HIF_ReleaseSem(GRP_IDX_USB);

    return mmpstatus;
}

#if (SUPPORT_MSDC_SCSI_AIT_CMD_MODE)
MMP_ERR MMPD_USB_SetDBGBuffer(MMP_ULONG uldbg_buf, MMP_ULONG uldbg_size)
{
    MMPH_HIF_WaitSem(GRP_IDX_USB, 0);
    MMPH_HIF_SetParameterL(GRP_IDX_USB, 0, uldbg_buf);
    MMPH_HIF_SetParameterL(GRP_IDX_USB, 4, uldbg_size);

    MMPH_HIF_SendCmd(GRP_IDX_USB, HIF_USB_CMD_SET_MSDCBUF | SET_DBG_BUF);
    MMPH_HIF_ReleaseSem(GRP_IDX_USB);

    return MMP_ERR_NONE;
}
#endif

//==============================================================================
//  Function    : MMPD_USB_SetMSDCBuf
//==============================================================================
/**
    @brief  Set MSDC Buffer
    @param[in] ulBufAddr : buffer address
    @param[in] ulBufSize : buffer size
    @return MMP_ERR_NONE
*/
MMP_ERR MMPD_USB_SetMSDCBuf(MMP_ULONG ulBufAddr,MMP_ULONG ulBufSize)
{
    MMPH_HIF_WaitSem(GRP_IDX_USB, 0);
    MMPH_HIF_SetParameterL(GRP_IDX_USB, 0, ulBufAddr);
    MMPH_HIF_SetParameterL(GRP_IDX_USB, 4, ulBufSize);

    MMPH_HIF_SendCmd(GRP_IDX_USB, HIF_USB_CMD_SET_MSDCBUF);
    MMPH_HIF_ReleaseSem(GRP_IDX_USB);
    return MMP_ERR_NONE;
}

//==============================================================================
//  Function    : MMPD_USB_SetMSDCMaxUnits
//==============================================================================
/**
    @brief  Set the MSDC maximum units allowed to show up
    @param[in] ubMaxUnitCnt : The number of units to show up
    @return MMP_ERR_NONE
*/
MMP_ERR MMPD_USB_SetMSDCMaxUnits(MMP_UBYTE ubMaxUnitCnt)
{
    MMP_ERR err;

    MMPH_HIF_WaitSem(GRP_IDX_USB, 0);
    MMPH_HIF_SetParameterB(GRP_IDX_USB, 0, ubMaxUnitCnt);
    err = MMPH_HIF_SendCmd(GRP_IDX_USB, HIF_USB_CMD_SET_MSDC_UNIT);
    MMPH_HIF_ReleaseSem(GRP_IDX_USB);

    return err;
}

//==============================================================================
//  Function    : MMPD_USB_SetCtlBuf
//==============================================================================
/**
    @brief  Set Usb Control Buffer
    @param[in] ulBufAddr : buffer address
    @param[in] ulBufSize : buffer size
    @return MMP_ERR_NONE
*/
MMP_ERR MMPD_USB_SetCtlBuf(MMP_ULONG ulBufAddr,MMP_ULONG ulBufSize)
{
    MMPH_HIF_WaitSem(GRP_IDX_USB, 0);
    MMPH_HIF_SetParameterL(GRP_IDX_USB, 0,ulBufAddr);
    MMPH_HIF_SetParameterL(GRP_IDX_USB, 4,ulBufSize);

    MMPH_HIF_SendCmd(GRP_IDX_USB, HIF_USB_CMD_SET_CONTROLBUF);
    MMPH_HIF_ReleaseSem(GRP_IDX_USB);
    return MMP_ERR_NONE;
}

#if (MSDC_WR_FLOW_TEST_EN == 1)
//==============================================================================
//  Function    : MMPD_USB_SetMSDCWriteBuf
//==============================================================================
/**
*/
MMP_ERR MMPD_USB_SetMSDCWriteBuf(MMP_ULONG ulBufAddr, MMP_ULONG ulBufSize)//, MMP_ULONG ulBufDepth)
{
    MMPH_HIF_WaitSem(GRP_IDX_USB, 0);
    MMPH_HIF_SetParameterL(GRP_IDX_USB, 0, ulBufAddr);
    MMPH_HIF_SetParameterL(GRP_IDX_USB, 4, ulBufSize);

    MMPH_HIF_SendCmd(GRP_IDX_USB, HIF_USB_CMD_SET_MSDCBUF|SET_MSDC_W_BUFF_QUEUE);
    MMPH_HIF_ReleaseSem(GRP_IDX_USB);
    return MMP_ERR_NONE;
}
#endif

//==============================================================================
//  Function    : MMPD_USB_SetPCSYNC_InBuf
//==============================================================================
/**
    @brief  Set PCSYNC In Buffer
    @param[in] ulBufAddr : buffer address
    @param[in] ulBufSize : buffer size
    @return MMP_ERR_NONE
*/
MMP_ERR MMPD_USB_SetPCSYNC_InBuf(MMP_ULONG ulBufAddr,MMP_ULONG ulBufSize)
{
    m_ulPCSYNCInBuf = ulBufAddr;

    MMPH_HIF_WaitSem(GRP_IDX_USB, 0);
    MMPH_HIF_SetParameterL(GRP_IDX_USB, 0, ulBufAddr);
    MMPH_HIF_SetParameterL(GRP_IDX_USB, 4, ulBufSize);

    MMPH_HIF_SendCmd(GRP_IDX_USB, SET_PCSYNC_IN_BUF | HIF_USB_CMD_SET_PCSYNCBUF);
    MMPH_HIF_ReleaseSem(GRP_IDX_USB);
    return MMP_ERR_NONE;
}
//==============================================================================
//  Function    : MMPD_USB_SetPCSYNC_OutBuf
//==============================================================================
/**
    @brief  Set PCSYNC Out Buffer
    @param[in] ulBufAddr : buffer address
    @param[in] ulBufSize : buffer size
    @return MMP_ERR_NONE
*/
MMP_ERR MMPD_USB_SetPCSYNC_OutBuf(MMP_ULONG ulBufAddr,MMP_ULONG ulBufSize)
{
    m_ulPCSYNCOutBuf = ulBufAddr;

    MMPH_HIF_WaitSem(GRP_IDX_USB, 0);
    MMPH_HIF_SetParameterL(GRP_IDX_USB, 0, ulBufAddr);
    MMPH_HIF_SetParameterL(GRP_IDX_USB, 4, ulBufSize);

    MMPH_HIF_SendCmd(GRP_IDX_USB, SET_PCSYNC_OUT_BUF|HIF_USB_CMD_SET_PCSYNCBUF);
    MMPH_HIF_ReleaseSem(GRP_IDX_USB);
    return MMP_ERR_NONE;
}

MMP_ERR MMPD_USB_SetMemDevBuf(MMP_ULONG ulBufAddr1,MMP_ULONG ulBufAddr2)
{
    MMPH_HIF_WaitSem(GRP_IDX_USB, 0);
    MMPH_HIF_SetParameterL(GRP_IDX_USB,0, ulBufAddr1);
    MMPH_HIF_SetParameterL(GRP_IDX_USB,4, ulBufAddr2);

    MMPH_HIF_SendCmd(GRP_IDX_USB, HIF_USB_CMD_SET_MEMDEV_BUF);
    MMPH_HIF_ReleaseSem(GRP_IDX_USB);
    return MMP_ERR_NONE;
}

//==============================================================================
//  Function    : MMPD_USB_SetPCSYNC_HansShakeBuf
//==============================================================================
/**
    @brief  Set PCSYNC HandShake Buffer
    @param[in] ulBufAddr : buffer address
    @param[in] ulBufSize : buffer size
    @return MMP_ERR_NONE
*/
MMP_ERR MMPD_USB_SetPCSYNC_HandShakeBuf(MMP_ULONG ulBufAddr,MMP_ULONG ulBufSize)
{
    m_ulPCSYNCHandshakeBuf = ulBufAddr;

    MMPH_HIF_WaitSem(GRP_IDX_USB, 0);
    MMPH_HIF_SetParameterL(GRP_IDX_USB, 0, ulBufAddr);
    MMPH_HIF_SetParameterL(GRP_IDX_USB, 4, ulBufSize);

    MMPH_HIF_SendCmd(GRP_IDX_USB, SET_PCSYNC_HANDSHAKE_BUF|HIF_USB_CMD_SET_PCSYNCBUF);
    MMPH_HIF_ReleaseSem(GRP_IDX_USB);
    return MMP_ERR_NONE;
}

//==============================================================================
//  Function    : MMPD_USB_SetMTPEPBuf
//==============================================================================
/**
    @brief Set MTP EP Buffer
    @param[in] ulRxBufAddr: buffer address for RX
    @param[in] ulTxBufAddr: buffer address for TX
    @param[in] ulBufSize: buffer size
    @return MMP_ERR_NONE
*/
MMP_ERR MMPD_USB_SetMTPEPBuf(MMP_ULONG ulRxBufAddr, MMP_ULONG ulTxBufAddr, MMP_ULONG ulBufSize, MMP_ULONG ulMBufAddr, MMP_ULONG ulMBufSize) //Andy++
{
    MMPH_HIF_WaitSem(GRP_IDX_USB, 0);
    MMPH_HIF_SetParameterL(GRP_IDX_USB, 0,  ulRxBufAddr);
    MMPH_HIF_SetParameterL(GRP_IDX_USB, 4, ulTxBufAddr);
    MMPH_HIF_SetParameterL(GRP_IDX_USB, 8,  ulBufSize);
    MMPH_HIF_SetParameterL(GRP_IDX_USB, 12, ulMBufAddr);
    MMPH_HIF_SetParameterL(GRP_IDX_USB, 16, ulMBufSize);

    MMPH_HIF_SendCmd(GRP_IDX_USB, SET_MTP_EP_BUF|HIF_USB_CMD_SET_MTPBUF);
    MMPH_HIF_ReleaseSem(GRP_IDX_USB);
    return MMP_ERR_NONE;
}

//==============================================================================
//  Function    : MMPD_USB_GetDpsHostBuf
//==============================================================================
/**
    @brief Get DPS HOST Buffer
    @return MMP_ERR_NONE
*/
MMP_ERR MMPD_USB_GetDpsBufAddr(MMP_UBYTE ubBufType, MMP_ULONG *ulAddr)
{
    MMP_ERR mmpstatus;

    MMPH_HIF_WaitSem(GRP_IDX_USB, 0);
    MMPH_HIF_SetParameterL(GRP_IDX_USB, 0, ubBufType);
    mmpstatus = MMPH_HIF_SendCmd(GRP_IDX_USB, DPS_GETBUFADDR|HIF_USB_CMD_DPS);

    if (mmpstatus == MMP_ERR_NONE) {
        *ulAddr = MMPH_HIF_GetParameterL(GRP_IDX_USB, 0);
    }
    MMPH_HIF_ReleaseSem(GRP_IDX_USB);

    return mmpstatus;
}

//==============================================================================
//  Function    : MMPD_DPS_GetPrinterStatus
//==============================================================================
/**
    @brief  Get printer status
    @param[out] usStatus : printer status
    @return MMP_ERR_NONE
*/
MMP_ERR MMPD_DPS_GetPrinterStatus(MMP_USHORT *usStatus)
{
    MMP_ERR mmpstatus;

    MMPH_HIF_WaitSem(GRP_IDX_USB, 0);
    mmpstatus = MMPH_HIF_SendCmd(GRP_IDX_USB, DPS_PRINTER_STATUS|HIF_USB_CMD_DPS);

    if (mmpstatus == MMP_ERR_NONE) {
        *usStatus = MMPH_HIF_GetParameterW(GRP_IDX_USB, 0);
    }
    MMPH_HIF_ReleaseSem(GRP_IDX_USB);

    return mmpstatus;
}

//==============================================================================
//  Function    : MMPD_DPS_StartJob
//==============================================================================
/**
    @brief  send start-print command
    @return MMP_ERR_NONE
*/
MMP_ERR MMPD_DPS_StartJob(void)
{
    MMPH_HIF_WaitSem(GRP_IDX_USB, 0);
    MMPH_HIF_SendCmd(GRP_IDX_USB, DPS_START_JOB|HIF_USB_CMD_DPS);
    MMPH_HIF_ReleaseSem(GRP_IDX_USB);
    return MMP_ERR_NONE;
}

//==============================================================================
//  Function    : MMPD_DPS_AbortPrint
//==============================================================================
/**
    @brief  send abort-print command
    @return MMP_ERR_NONE
*/
MMP_ERR MMPD_DPS_AbortPrint(void)
{
    MMPH_HIF_WaitSem(GRP_IDX_USB, 0);
    MMPH_HIF_SendCmd(GRP_IDX_USB, DPS_ABORT_JOB|HIF_USB_CMD_DPS);
    MMPH_HIF_ReleaseSem(GRP_IDX_USB);
    return MMP_ERR_NONE;
}

//==============================================================================
//  Function    : MMPD_DPS_ContinuePrint
//==============================================================================
/**
    @brief  send continue-print command
    @return MMP_ERR_NONE
*/
MMP_ERR MMPD_DPS_ContinuePrint(void)
{
    MMPH_HIF_WaitSem(GRP_IDX_USB, 0);
    MMPH_HIF_SendCmd(GRP_IDX_USB, DPS_CONTINUE_JOB|HIF_USB_CMD_DPS);
    MMPH_HIF_ReleaseSem(GRP_IDX_USB);
    return MMP_ERR_NONE;
}

//==============================================================================
//  Function    : MMPD_USB_GetPCSYNCInFlag
//==============================================================================
/**
    @brief  Get PCSYNC In Flag
    @param[out] *ulFlag: in flag
    @return MMP_ERR_NONE
*/
MMP_ERR MMPD_USB_GetPCSYNCInFlag(MMP_ULONG *ulFlag)
{
    *ulFlag = MMPH_HIF_MemGetB(m_ulPCSYNCHandshakeBuf+MMPD_USB_PCSYNC_INFLAG_OFFSET_B);

    return MMP_ERR_NONE;
}
//==============================================================================
//  Function    : MMPD_USB_SetPCSYNCInFlag
//==============================================================================
/**
    @brief  Set PCSYNC In Flag
    @param[in] ulFlag: in flag
    @return MMP_ERR_NONE
*/
MMP_ERR MMPD_USB_SetPCSYNCInFlag(MMP_ULONG ulFlag)
{
    MMPH_HIF_MemSetB(m_ulPCSYNCHandshakeBuf+MMPD_USB_PCSYNC_INFLAG_OFFSET_B,ulFlag);

    return MMP_ERR_NONE;
}
//==============================================================================
//  Function    : MMPD_USB_GetPCSYNCOutFlag
//==============================================================================
/**
    @brief  Get PCSYNC Out Flag
    @param[out] *ulFlag: out flag
    @return MMP_ERR_NONE
*/
MMP_ERR MMPD_USB_GetPCSYNCOutFlag(MMP_ULONG *ulFlag)
{
    *ulFlag = MMPH_HIF_MemGetB(m_ulPCSYNCHandshakeBuf+MMPD_USB_PCSYNC_OUTFLAG_OFFSET_B);

    return MMP_ERR_NONE;
}
//==============================================================================
//  Function    : MMPD_USB_SetPCSYNCOutFlag
//==============================================================================
/**
    @brief  Set PCSYNC Out Flag
    @param[in] ulFlag: out flag
    @return MMP_ERR_NONE
*/
MMP_ERR MMPD_USB_SetPCSYNCOutFlag(MMP_ULONG ulFlag)
{
    MMPH_HIF_MemSetB(m_ulPCSYNCHandshakeBuf+MMPD_USB_PCSYNC_OUTFLAG_OFFSET_B,ulFlag);

    return MMP_ERR_NONE;
}
//==============================================================================
//  Function    : MMPD_USB_GetPCSYNCInSize
//==============================================================================
/**
    @brief  Get PCSYNC In Size
    @param[out] *ulSize: return size
    @return MMP_ERR_NONE
*/
MMP_ERR MMPD_USB_GetPCSYNCInSize(MMP_ULONG *ulSize)
{
    *ulSize = MMPH_HIF_MemGetW(m_ulPCSYNCHandshakeBuf+MMPD_USB_PCSYNC_INSIZE_OFFSET_W);

    return MMP_ERR_NONE;
}
//==============================================================================
//  Function    : MMPD_USB_ReadPCSYNCInData
//==============================================================================
/**
    @brief  Transfer Pcsync Data From Firmware to Host
    @param[in] ubMemStart : pcsync in data start pointer
    @param[in] ulSize  : file size to transfer
    @return MMPD_AUDIO_SUCCESS
*/
MMP_ERR MMPD_USB_ReadPCSYNCInData(MMP_UBYTE *ubMemStart,MMP_ULONG ulSize)
{
    MMPH_HIF_MemCopyDevToHost(ubMemStart,m_ulPCSYNCInBuf,ulSize);

    return MMP_ERR_NONE;
}
//==============================================================================
//  Function    : MMPD_USB_WritePCSYNCOutData
//==============================================================================
/**
    @brief  Transfer Pcsync Data From Host to Firmware
    @param[in] ubMemStart : pcsync out data start pointer
    @param[in] ulSize  : file size to transfer
    @return MMPD_AUDIO_SUCCESS
*/
MMP_ERR MMPD_USB_WritePCSYNCOutData(MMP_UBYTE *ubMemStart,MMP_ULONG ulSize)
{
    MMPH_HIF_MemCopyHostToDev(m_ulPCSYNCOutBuf,ubMemStart,ulSize);

    return MMP_ERR_NONE;
}
//==============================================================================
//  Function    : MMPD_USB_SetPCSYNCOutSize
//==============================================================================
/**
    @brief  Set PCSYNC Out Size
    @param[in] ulSize: out size
    @return MMP_ERR_NONE
*/
MMP_ERR MMPD_USB_SetPCSYNCOutSize(MMP_ULONG ulSize)
{
    MMPH_HIF_MemSetW(m_ulPCSYNCHandshakeBuf+MMPD_USB_PCSYNC_OUTSIZE_OFFSET_W,ulSize);

    return MMP_ERR_NONE;
}
//==============================================================================
//  Function    : MMPD_USB_SetPCamCompressBuf
//==============================================================================
/**
    @brief  Set PCCAM Compress Buffer
    @param[in] ulBufAddr : buffer address
    @param[in] ulBufSize : buffer size
    @return MMP_ERR_NONE
*/
MMP_ERR MMPD_USB_SetPCamCompressBuf(MMP_ULONG ulBufAddr,MMP_ULONG ulBufSize)
{
    MMPH_HIF_WaitSem(GRP_IDX_USB, 0);
    MMPH_HIF_SetParameterL(GRP_IDX_USB, 0, ulBufAddr);
    MMPH_HIF_SetParameterL(GRP_IDX_USB, 4, ulBufSize);

    MMPH_HIF_SendCmd(GRP_IDX_USB, SET_PCCAM_COMPRESS_BUF|HIF_USB_CMD_SET_PCCAMBUF);
    MMPH_HIF_ReleaseSem(GRP_IDX_USB);
    return MMP_ERR_NONE;
}

//==============================================================================
//  Function    : MMPD_USB_SetPCCamLineBuf
//==============================================================================
/**
    @brief  Set PCSYNC Line Buffer
    @param[in] ulBufAddr : buffer address
    @param[in] ulBufSize : buffer size
    @return MMP_ERR_NONE
*/
MMP_ERR MMPD_USB_SetPCCamLineBuf(MMP_ULONG ulBufAddr,MMP_ULONG ulBufSize)
{
    MMPH_HIF_WaitSem(GRP_IDX_USB, 0);
    MMPH_HIF_SetParameterL(GRP_IDX_USB, 0, ulBufAddr);
    MMPH_HIF_SetParameterL(GRP_IDX_USB, 4, ulBufSize);

    MMPH_HIF_SendCmd(GRP_IDX_USB, SET_PCCAM_LINE_BUF|HIF_USB_CMD_SET_PCCAMBUF);
    MMPH_HIF_ReleaseSem(GRP_IDX_USB);
    return MMP_ERR_NONE;
}

#if 0
void ____USBH_Function____(){ruturn;} //dummy
#endif

#if (SUPPORT_USB_HOST_FUNC)
//==============================================================================
//
//                USB HOST RELATED FUNCTION DEFINITION
//
//==============================================================================
//------------------------------------------------------------------------------
//  Function    : MMPD_USB_RegPollingCallBack
//  Description :
//------------------------------------------------------------------------------
/**
@brief The function sets UVC device following configs.
@param[in] pReadUSBIDTimeoutCallback The callback to be executed when read USB_ID timeout.
@param[in] pOtgSessionTimeoutCallback The callback to be executed when Otg session timeout.
@param[in] pDevConnCallback The callback to be executed when USB device connected.
@param[in] pDevDisconnCallback The callback to be executed when USB device disconnected.
@return It reports the status of the operation.
*/
MMP_ERR MMPD_USB_RegPollingCallBack(void *pReadUSBIDTimeoutCallback, void *pOtgSessionTimeoutCallback, void *pDevConnCallback, void *pDevDisconnCallback)
{
    return MMPF_USBH_RegPollingCallBack(pReadUSBIDTimeoutCallback,pOtgSessionTimeoutCallback,pDevConnCallback,pDevDisconnCallback);
}

//------------------------------------------------------------------------------
//  Function    : MMPD_USB_TriggerReadUSBID
//  Description :
//------------------------------------------------------------------------------
/**
 @brief Trigger to read USB_ID.
 @param[in] pulTimerId Fetch the timer ID that create by driver.
 @retval MMP_ERR_NONE Success.
 @retval MMP_USB_ERR_PARAMETER Unsupport parameters.
*/
MMP_ERR MMPD_USB_TriggerReadUSBID(MMP_ULONG *pulTimerId)
{
    return MMPF_USBH_TriggerReadUSBID(pulTimerId);
}

//------------------------------------------------------------------------------
//  Function    : MMPD_USB_ReadUSBID
//  Description :
//------------------------------------------------------------------------------
/**
 @brief Read USB_ID after trigger timeout.
 @param[in] pubDevType Fetch the device type(A or B).
 @retval MMP_ERR_NONE Success.
 @retval MMP_USB_ERR_PARAMETER Unsupport parameters.
*/
MMP_ERR MMPD_USB_ReadUSBID(MMP_UBYTE *pubDevType)
{
    return MMPF_USBH_ReadUSBID(pubDevType);
}

//------------------------------------------------------------------------------
//  Function    : MMPD_USB_StartOTGSession
//  Description :
//------------------------------------------------------------------------------
/**
 @brief Start OTG session.
 @param[in] pulTimerId Fetch the timer ID that create by driver.
 @retval MMP_ERR_NONE Success.
 @retval MMP_USB_ERR_PARAMETER Unsupport parameters.
*/
MMP_ERR MMPD_USB_StartOTGSession(MMP_ULONG *pulTimerId)
{
    return MMPF_USBH_StartOTGSession(pulTimerId);
}

//------------------------------------------------------------------------------
//  Function    : MMPD_USB_StopOTGSession
//  Description :
//------------------------------------------------------------------------------
/**
 @brief Stop OTG session coercively [BE CAREFUL, MAY IMPACT CONNECTION SR].
 @retval MMP_ERR_NONE Success.
 @retval MMP_USB_ERR_UNSUPPORT_MODE Unsupport parameters.
*/
MMP_ERR MMPD_USB_StopOTGSession(void)
{
    return MMPF_USBH_StopOTGSession();
}

//------------------------------------------------------------------------------
//  Function    : MMPD_USB_GetDevConnSts
//  Description :
//------------------------------------------------------------------------------
/**
 @brief Get device connection status.
 @param[in] pbStatus Fetch the connection status.
 @retval MMP_ERR_NONE Success.
 @retval MMP_USB_ERR_PARAMETER Unsupport parameters.
*/
MMP_ERR MMPD_USB_GetDevConnSts(MMP_BOOL *pbStatus)
{
    return MMPF_USBH_GetDeviceConnectedSts(pbStatus);
}

//------------------------------------------------------------------------------
//  Function    : MMPD_USB_SetDevConnSts
//  Description :
//------------------------------------------------------------------------------
/**
 @brief BE CAREFUL, SPECIAL CASE! Forced set device connection status.
 @param[in] pbStatus Set the connection status.
 @retval MMP_ERR_NONE Success.
 @retval MMP_USB_ERR_PARAMETER Unsupport parameters.
*/
MMP_ERR MMPD_USB_SetDevConnSts(MMP_BOOL pbStatus)
{
    return MMPF_USBH_SetDeviceConnectedSts(pbStatus);
}

//------------------------------------------------------------------------------
//  Function    : MMPD_USB_EnumUVC
//  Description :
//------------------------------------------------------------------------------
/**
 @brief Enumeration UVC device.
 @retval MMP_ERR_NONE Success.
 @retval MMP_USB_ERR_UNSUPPORT_MODE Unsupport parameters.
*/
MMP_ERR MMPD_USB_EnumUVC(void)
{
    MMP_ERR err = MMP_ERR_NONE;

    err = MMPF_USBH_ResetPort();

    if (err == MMP_ERR_NONE)
        err = MMPF_USBH_RootHubEnum();

    return err;
}

//------------------------------------------------------------------------------
//  Function    : MMPD_USB_GetUVCStreamSts
//  Description :
//------------------------------------------------------------------------------
/**
 @brief Get UVC device stream status.
 @param[in] pbStatus Fetch the stream status.
 @retval MMP_ERR_NONE Success.
 @retval MMP_USB_ERR_UNSUPPORT_MODE Unsupport parameters.
*/
MMP_ERR MMPD_USB_GetUVCStreamSts(MMP_BOOL *pbStatus)
{
    return MMPF_USBH_GetUVCStreamSts(pbStatus);
}

//------------------------------------------------------------------------------
//  Function    : MMPD_USB_RegUVCMDCallBack
//  Description :
//------------------------------------------------------------------------------
/**
@brief The function sets UVC device following configs.
@param[in] pDevTriggerMDCallback The callback to be executed when UVC device MD triggered.
@return It reports the status of the operation.
*/
MMP_ERR MMPD_USB_RegUVCMDCallBack(void *pDevTriggerMDCallback)
{
    return MMPF_USBH_RegUVCMDCallBack(pDevTriggerMDCallback);
}

//------------------------------------------------------------------------------
//  Function    : MMPD_USB_EnableUVCMD
//  Description :
//------------------------------------------------------------------------------
/**
 @brief Enable UVC MD.
 Enable to inform USBH, and driver will execute callback(pDevTriggerMDCallback) when MD triggered frame received.
 @retval MMP_ERR_NONE Success.
 @retval MMP_3GPRECD_ERR_GENERAL_ERROR Not allowed procedure.
*/
MMP_ERR MMPD_USB_EnableUVCMD(void)
{
    return MMPF_USBH_EnableUVCMD();
}

//------------------------------------------------------------------------------
//  Function    : MMPD_USB_DisableUVCMD
//  Description :
//------------------------------------------------------------------------------
/**
 @brief Stop UVC video recording.
 Disable and do not execute callback(pDevTriggerMDCallback) even  MD triggered frame received.
 @retval MMP_ERR_NONE Success.
 @retval MMP_3GPRECD_ERR_GENERAL_ERROR Not allowed procedure.
*/
MMP_ERR MMPD_USB_DisableUVCMD(void)
{
    return MMPF_USBH_DisableUVCMD();
}

//------------------------------------------------------------------------------
//  Function    : MMPD_USB_SetCheckDevAliveCFG
//  Description :
//------------------------------------------------------------------------------
/**
@brief The function register following configs for error handle.
@param[in] pulCheckDevAliveInterval The timer interval to check device alive.
@param[in] pDevNoResponseCallback The callback will be executed when device no response.
@return It reports the status of the operation.
*/
MMP_ERR MMPD_USB_SetCheckDevAliveCFG(MMP_ULONG pulCheckDevAliveInterval, void *pDevNoResponseCallback)
{
    return MMPF_USBH_SetCheckDevAliveCFG(pulCheckDevAliveInterval,pDevNoResponseCallback);
}

//------------------------------------------------------------------------------
//  Function    : MMPD_USB_SetTranTimeoutCFG
//  Description :
//------------------------------------------------------------------------------
/**
@brief The function register following configs for error handle.
@param[in] pulTranTimeoutInterval The timer interval to check transaction timeout.
@param[in] pDevTranTimeoutCallback The callback will be executed when transaction timeout.
@return It reports the status of the operation.
*/
MMP_ERR MMPD_USB_SetTranTimeoutCFG(MMP_ULONG pulTranTimeoutInterval, void *pDevTranTimeoutCallback)
{
    return MMPF_USBH_SetTranTimeoutCFG(pulTranTimeoutInterval,pDevTranTimeoutCallback);
}

//------------------------------------------------------------------------------
//  Function    : MMPD_USB_SetFrmRxTimeoutCFG
//  Description :
//------------------------------------------------------------------------------
/**
@brief The function register following configs for error handle.
@param[in] pulFrmRxLostTH The lost frame count of threshold to be trigger callback.
@param[in] pulFrmRxFirstAddGap The first frame additional gap of the lost frame count of threshold to be trigger callback.
@param[in] pDevFrmRxLostTHCallback The callback will be executed when frame lost reach pulFrmRxLostTH.
@return It reports the status of the operation.
*/
MMP_ERR MMPD_USB_SetFrmRxTimeoutCFG(MMP_ULONG pulFrmRxLostTH, MMP_ULONG pulFrmRxFirstAddGap, void *pDevFrmRxLostTHCallback)
{
    return MMPF_USBH_SetFrmRxTimeoutCFG(pulFrmRxLostTH,pulFrmRxFirstAddGap,pDevFrmRxLostTHCallback);
}

//------------------------------------------------------------------------------
//  Function    : MMPD_USB_SetFrmRxTimeout2CFG
//  Description :
//------------------------------------------------------------------------------
/**
@brief The function register following configs for error handle.
@param[in] pulFrmRxLostTH2 The 2nd lost frame count of threshold to be trigger callback.
@param[in] pDevFrmRxLostTH2Callback The callback will be executed when frame lost reach pulFrmRxLostTH2.
@return It reports the status of the operation.
*/
MMP_ERR MMPD_USB_SetFrmRxTimeout2CFG(MMP_ULONG pulFrmRxLostTH2, void *pDevFrmRxLostTH2Callback)
{
    return MMPF_USBH_SetFrmRxTimeout2CFG(pulFrmRxLostTH2,pDevFrmRxLostTH2Callback);
}

//------------------------------------------------------------------------------
//  Function    : MMPD_USB_SetFrmSeqNoLostCFG
//  Description :
//------------------------------------------------------------------------------
/**
@brief The function register following configs for error handle.
@param[in] pulSeqNoLostTH The lost frame seq. no of threshold to be trigger callback.
@param[in] pDevSeqNoLostTHCallback The callback will be executed when frame seq no lost reach pulSeqNoLostTH.
@return It reports the status of the operation.
*/
MMP_ERR MMPD_USB_SetFrmSeqNoLostCFG(MMP_ULONG pulSeqNoLostTH, void *pDevSeqNoLostTHCallback)
{
    return MMPF_USBH_SetFrmSeqNoLostCFG(pulSeqNoLostTH,pDevSeqNoLostTHCallback);
}

//------------------------------------------------------------------------------
//  Function    : MMPD_USB_StopFrmRxClrFIFO
//  Description :
//------------------------------------------------------------------------------
/**
@brief BE CAREFUL, forced to stop USB frame Rx and clear FIFO.
@param[in] None.
@return It reports the status of the operation.
*/
MMP_ERR MMPD_USB_StopFrmRxClrFIFO(void)
{
    return MMPF_USBH_StopFrmRxClrFIFO();
}

//------------------------------------------------------------------------------
//  Function    : MMPD_USB_SetDropRxFrmCFG
//  Description :
//------------------------------------------------------------------------------
/**
@brief The function register following configs for error handle.
@param[in] ulTotalCnt.
@param[in] ulContinCnt.
@param[in] *pRxBufFull2Callback.
@return It reports the status of the operation.
*/
MMP_ERR MMPD_USB_SetDropRxFrmCFG(MMP_ULONG ulTotalCnt, MMP_ULONG ulContinCnt, void *pDropRxFrmCallback)
{
    return MMPF_USBH_SetDropRxFrmCFG(ulTotalCnt, ulContinCnt, pDropRxFrmCallback);
}

#endif //end of (SUPPORT_USB_HOST_FUNC)

/// @}
/// @end_ait_only

