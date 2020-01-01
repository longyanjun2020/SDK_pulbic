//==============================================================================
//
//  File        : mmps_usb.c
//  Description : Usb User Application Interface
//  Author      : Hans Liu
//  Revision    : 1.0
//
//==============================================================================
/**
 @file mmps_usb.c
 @brief The USB control functions
 @author Hans Liu
 @version 1.0
*/


#include "lib_retina.h"
#include "mmps_usb.h"
#include "mmpd_usb.h"

/** @addtogroup MMPS_USB
@{
*/

//==============================================================================
//
//                              VARIABLES
//
//==============================================================================
#if (MSDC_WR_FLOW_TEST_EN == 1)
#define MMPS_USB_W_DATA_BUFF_SIZE   0x10000
#define MMPS_USB_W_DATA_BUFF_DEPTH  0x14
#endif

MMPS_USB_StatusMode gsUsbCurStatus = MMPS_USB_IDLE;

#if (SUPPORT_DPS_FUNC)
///DPS Print Information
static MMPS_USB_DPS_PRINT_INFO   m_DpsPrintInfo;
///DPS Buffer Size to Host
static MMP_ULONG        m_ulDPSBuf4host;
#endif

extern MMPS_USB_StatusMode  gsUsbCurStatus;

//please update it after FS_MS_API ready
#define FS_MS_ERROR_NONE    FS_MS_OK
#define FS_MS_ERROE_FAIL    FS_MS_ERROR

#if (SUPPORT_MSDC_SCSI_AIT_CMD_MODE)
MMP_ULONG mulMSDC_SCSI_Buf = 0, mulMSDC_Ctl_Buf = 0;
#endif

//==============================================================================
//
//                              FUNCTION PROTOTYPES
//
//==============================================================================
#if (MSDC_WR_FLOW_TEST_EN == 1)
extern MMP_ERR MMPD_USB_SetMSDCWriteBuf(MMP_ULONG ulBufAddr, MMP_ULONG ulBufSize);
#endif

#if (SUPPORT_MSDC_SCSI_AIT_CMD_MODE)
MMP_ERR MMPS_USB_GetMSDC_SCSIBufferSize(MMP_ULONG *pscsi_buf_size, MMP_ULONG *pctl_buf_size)
{
    *pscsi_buf_size = MSDC_RDWR_BUF_SIZE;
    *pctl_buf_size = MSDC_CTL_BUF_SIZE;
    
    return MMP_ERR_NONE;
}

MMP_ERR MMPS_USB_SetMSDC_SCSIBuffer(MMP_ULONG ulscsi_buf, MMP_ULONG ulctl_buf)
{
    mulMSDC_SCSI_Buf = ulscsi_buf;
    mulMSDC_Ctl_Buf = ulctl_buf;
    
    return MMP_ERR_NONE;
}

MMP_ERR MMPS_USB_SetDBGBuffer(MMP_ULONG uldbg_buf, MMP_ULONG uldbg_size)
{
    return MMPD_USB_SetDBGBuffer(uldbg_buf, uldbg_size);
}
#endif

//==============================================================================
//  Function    : MMPS_USB_SetMemoryMap
//==============================================================================
MMP_ERR MMPS_USB_SetMemoryMap(MMPS_USB_OP_MODE ubMode)
{
    MMP_ULONG   ulCurBufAddr = 0, ulBufSize = 0;
    MMP_ULONG*  pInUserPtr = NULL;
    //CamOsRet_e  eCamOsRet = CAM_OS_OK;

    switch (ubMode) {
    #if (SUPPORT_MSDC_SCSI_AIT_CMD_MODE)
    case MMPS_USB_MSDC_AIT_DEBUG_MODE:
        MMPD_USB_SetMSDCBuf((MMP_ULONG)mulMSDC_SCSI_Buf, MSDC_RDWR_BUF_SIZE);
        MMPD_USB_SetCtlBuf((MMP_ULONG)mulMSDC_Ctl_Buf, MSDC_CTL_BUF_SIZE);
        break;
    #endif
    case MMPS_USB_MSDC_MODE:
    case MMPS_USB_DETECT_MODE:
    	ulBufSize = MSDC_RDWR_BUF_SIZE * 2 + MSDC_CTL_BUF_SIZE;
        CamOsDirectMemAlloc("MSDC WR_Buffer",
                            ulBufSize,
                            (void**)&pInUserPtr,
                            NULL,
                            NULL);

        if (pInUserPtr == NULL) {
            UartSendTrace("USB Buffer Alloc Fail\r\n");
        }
        memset((void *)pInUserPtr, 0x00, ulBufSize);
        ulCurBufAddr = (MMP_ULONG)pInUserPtr;
        UartSendTrace("Allocate MSDC Write buffer: addr %x, size %d\r\n", ulCurBufAddr, ulBufSize);
        MMPD_USB_SetMSDCBuf(ulCurBufAddr, 0);
        ulCurBufAddr += MSDC_RDWR_BUF_SIZE;
        UartSendTrace("Allocate MSDC Read buffer: addr %x, size %d\r\n", ulCurBufAddr, ulBufSize);
        MMPD_USB_SetMSDCBuf(0, ulCurBufAddr);
        ulCurBufAddr += MSDC_RDWR_BUF_SIZE;
        MMPD_USB_SetCtlBuf(ulCurBufAddr, MSDC_CTL_BUF_SIZE);
        ulCurBufAddr += MSDC_CTL_BUF_SIZE;
        #if (MSDC_WR_FLOW_TEST_EN == 1)
        MMPD_USB_SetMSDCWriteBuf(buf_start, MMPS_USB_W_DATA_BUFF_SIZE);
        ulCurBufAddr += MMPS_USB_W_DATA_BUFF_SIZE * MMPS_USB_W_DATA_BUFF_DEPTH;
        #endif
        break;

    #if (SUPPORT_PCSYNC_FUNC)
    case MMPS_USB_PCSYNC_MODE:
        MMPD_USB_SetCtlBuf(ulCurBufAddr, PCSYNC_CTL_BUF_SIZE);
        ulCurBufAddr += PCSYNC_CTL_BUF_SIZE;
        MMPD_USB_SetPCSYNC_InBuf(ulCurBufAddr, PCSYNC_IN_BUF_SIZE);
        ulCurBufAddr += PCSYNC_IN_BUF_SIZE;
        MMPD_USB_SetPCSYNC_OutBuf(ulCurBufAddr, PCSYNC_OUT_BUF_SIZE);
        ulCurBufAddr += PCSYNC_OUT_BUF_SIZE;
        MMPD_USB_SetPCSYNC_HandShakeBuf(ulCurBufAddr, PCSYNC_HANDSHAKE_BUF_SIZE);
        ulCurBufAddr += PCSYNC_HANDSHAKE_BUF_SIZE;
        MMPD_FS_SetFileNameDmaAddr(ulCurBufAddr, PCSYNC_NAME_BUF_SIZE,
                        ulCurBufAddr + PCSYNC_NAME_BUF_SIZE, PCSYNC_PARAM_BUF_SIZE);
        ulCurBufAddr += PCSYNC_NAME_BUF_SIZE;
        ulCurBufAddr += PCSYNC_PARAM_BUF_SIZE;
        break;
    #endif

    #if (SUPPORT_DPS_FUNC)
    case MMPS_USB_DPS_MODE:
    #endif
        break;

    #if (SUPPORT_MTP_FUNC == 1)
    case MMPS_USB_MTP_MODE:
        MMPD_FS_SetFileNameDmaAddr(ulCurBufAddr, MTP_NAME_BUF_SIZE,
                            ulCurBufAddr + MTP_NAME_BUF_SIZE, MTP_PARAM_BUF_SIZE);
        ulCurBufAddr += MTP_NAME_BUF_SIZE;   //UTF8: name_buf_size;
        ulCurBufAddr += MTP_PARAM_BUF_SIZE;  //8*1024: parameter_buf_size;
        MMPD_USB_SetCtlBuf(ulCurBufAddr, MTP_CTL_BUF_SIZE);
        ulCurBufAddr += MTP_CTL_BUF_SIZE;
        MMPD_USB_SetPCSYNC_InBuf(ulCurBufAddr, MTP_PCSYNC_IN_BUF_SIZE);
        ulCurBufAddr += MTP_PCSYNC_IN_BUF_SIZE;
        MMPD_USB_SetPCSYNC_OutBuf(ulCurBufAddr, MTP_PCSYNC_OUT_BUF_SIZE);
        ulCurBufAddr += MTP_PCSYNC_OUT_BUF_SIZE;
        MMPD_USB_SetPCSYNC_HandShakeBuf(ulCurBufAddr, PCSYNC_HANDSHAKE_BUF_SIZE);
        ulCurBufAddr += PCSYNC_HANDSHAKE_BUF_SIZE;
        ulCurBufAddr = ALIGN512(ulCurBufAddr);
        MMPD_USB_SetMTPEPBuf(ulCurBufAddr, ulCurBufAddr + MTP_EP_BUF_SIZE, MTP_EP_BUF_SIZE,
                            ulCurBufAddr + (MTP_EP_BUF_SIZE << 1), MTP_DRM_BUF_SIZE);
        ulCurBufAddr += (MTP_EP_BUF_SIZE << 1);
        ulCurBufAddr += MTP_DRM_BUF_SIZE;
        break;
    #endif
    case MMPS_USB_PCCAM_MODE:
        break;
    default:
        RTNA_DBG_Str(0, "ERROR: UnSupport USB mode !!\r\n");
        return MMP_USB_ERR_UNSUPPORT_MODE;
    }

    return MMP_ERR_NONE;
}

//==============================================================================
//  Function    : MMPS_USB_AdjustVref
//==============================================================================
/**
    @brief  Adjust USB PHY signal by tuning BG Vref
    @param[in] Vref : BG Vref, @ref MMP_USB_VREF
    @return MMP_ERR_NONE for success, others for failure.
*/
MMP_ERR MMPS_USB_AdjustVref(MMP_USBPHY_VREF Vref)
{
    return MMPD_USB_AdjustVref(Vref);
}

//==============================================================================
//  Function    : MMPS_USB_AdjustBiasCurrent
//==============================================================================
/**
    @brief  Adjust USB PHY signal by tuning BG bias current
    @param[in] BiasCurrent : BG bias current, @ref MMP_USB_BIAS_CURRENT
    @return MMP_ERR_NONE for success, others for failure.
*/
MMP_ERR MMPS_USB_AdjustBiasCurrent(MMP_USBPHY_BIAS_CURRENT BiasCurrent)
{
    return MMPD_USB_AdjustBiasCurrent(BiasCurrent);
}

//==============================================================================
//  Function    : MMPS_USB_AdjustSignal
//==============================================================================
/**
    @brief  Adjust USB PHY signal by tuning HS Tx current & squelch level
    @param[in] txCur : HS Tx current, @ref MMP_USB_TX_CUR
    @param[in] TxCurPlus : HS Tx current fine tune, @ref MMP_USB_TX_CUR_PLUS
    @param[in] SqLevel : Squelch Level, @ref MMP_USB_SQ
    @return MMP_ERR_NONE for success, others for failure.
*/
MMP_ERR MMPS_USB_AdjustSignal(MMP_USBPHY_TX_CUR TxCur,
                              MMP_USBPHY_TX_CUR_PLUS TxCurPlus,
                              MMP_USBPHY_SQ SqLevel)
{
    return MMPD_USB_AdjustSignal(TxCur, TxCurPlus, SqLevel);
}

//==============================================================================
//  Function    : MMPS_USB_RegisterCallback
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
MMP_ERR MMPS_USB_RegisterCallback(MMP_USB_EVENT event, MMP_USB_Callback *callback)
{
    return MMPD_USB_RegisterCallback(event, callback);
}

//==============================================================================
//  Function    : MMPS_USB_SetMode
//==============================================================================
/**
    @brief  Set usb mode
    @param[in] ubMode : usb mode(MSDC,PCSYNC,...)
    @return MMP_ERR_NONE
*/
MMP_ERR MMPS_USB_SetMode(MMPS_USB_OP_MODE ubMode)
{
	UartSendTrace("MMPS_USB_SetMode:%d\r\n", ubMode);
    MMPS_USB_SetMemoryMap(ubMode);
    MMPD_USB_SetMode(ubMode);

    return MMP_ERR_NONE;
}

//==============================================================================
//  Function    : MMPS_USB_GetOpMode
//==============================================================================
MMP_ERR MMPS_USB_GetMode(MMPS_USB_OP_MODE *UsbCurMode)
{
    MMP_ERR     mmpstatus;
    MMP_UBYTE   UsbMode;

    mmpstatus = MMPD_USB_GetMode(&UsbMode);
    *UsbCurMode = UsbMode;

    return mmpstatus;
}
//==============================================================================
//  Function    : MMPS_USB_StopDevice
//==============================================================================
/**
    @brief Disable USB device.
    @return MMP_ERR_NONE.
*/
MMP_ERR MMPS_USB_StopDevice(void)
{
    return MMPD_USB_StopDevice();
}

//==============================================================================
//  Function    : MMPS_USB_SetConnect
//==============================================================================
MMP_ERR MMPS_USB_SetConnect(MMP_BOOL bSetConnect)
{
    if (bSetConnect == MMP_TRUE)
        return MMPD_USB_ConnectDevice();
    else
        return MMPS_USB_StopDevice();
}

//==============================================================================
//  Function    : MMPS_USB_ReadPCSYNCInData
//==============================================================================
/**
    @brief  Read PCSYNC In Data
    @param[in] ubMemStart : pcsync in data buffer
    @param[out] *ulReadSize  : return read size
    @return MMP_ERR_NONE
*/
MMP_ERR MMPS_USB_ReadPCSYNCInData(MMP_UBYTE *ubMemStart,MMP_ULONG *ulReadSize)
{
    MMP_ULONG in_flag,size;

    MMPD_USB_GetPCSYNCInFlag(&in_flag);

    *ulReadSize = 0;
    if (in_flag==MMPS_USB_PCSYNC_IN_DATA_READY) {
        MMPD_USB_GetPCSYNCInSize(&size);
        MMPD_USB_ReadPCSYNCInData(ubMemStart,size);

        *ulReadSize = size;
        MMPD_USB_SetPCSYNCInFlag(MMPS_USB_PCSYNC_IN_EMPTY);
    }
    return MMP_ERR_NONE;
}
//==============================================================================
//  Function    : MMPS_USB_WritePCSYNCOutData
//==============================================================================
/**
    @brief  Write PCSYNC Out Data
    @param[in] ubMemStart : pcsync out data buffer
    @param[in] ulWriteSize  : file size to write
    @return MMP_ERR_NONE
*/
MMP_ERR MMPS_USB_WritePCSYNCOutData(MMP_UBYTE *ubMemStart,MMP_ULONG ulWriteSize)
{
    MMP_ULONG out_flag;
    MMPD_USB_GetPCSYNCOutFlag(&out_flag);

    if (out_flag==MMPS_USB_PCSYNC_OUT_EMPTY) {
        MMPD_USB_SetPCSYNCOutFlag(MMPS_USB_PCSYNC_OUT_DATA_READY);
        MMPD_USB_WritePCSYNCOutData(ubMemStart,ulWriteSize);
        MMPD_USB_SetPCSYNCOutSize(ulWriteSize);

        return MMP_ERR_NONE;
    }
    return MMP_USB_ERR_PCSYNC_BUSY;
}

//==============================================================================
//  Function    : MMPS_USB_DetectVBus
//==============================================================================
/**
    @brief check if VBUS 5V plug-in or not
    @return TRUE: VBUS 5V plug-in,  FALSE: VBUS 5V plug-out
*/
MMP_BOOL MMPS_USB_DetectVBus5V(void)
{
#if defined(UPDATER_FW)
    return MMP_TRUE;
#else
#if (1)
    // TODO: How to detect Vbus vaild in MercuryV2? Alterman@2014/03/10
    return MMP_TRUE;
#endif
#endif
}

//==============================================================================
//  Function    : MMPS_USB_DetectAdaptorOrUSB
//==============================================================================
/**
    @brief check if VBUS or Adaptor. The function will set gsUsbCurStatus
    @return N/A
*/
void MMPS_USB_DetectAdaptorOrUSB(void)
{
    MMP_ULONG TimeOutThrd = 40, TimeOutCount = 0;
    MMP_USHORT tempStatus = 3;

    gsUsbCurStatus = tempStatus;
    MMPS_USB_SetMode(MMPS_USB_DETECT_MODE);
    while ((gsUsbCurStatus == tempStatus)) {
        MMPF_OS_Sleep(10);       //release cpu
        TimeOutCount++;
        if(TimeOutCount>TimeOutThrd){
            gsUsbCurStatus = MMPS_USB_ISADAPTER;
            break;
        }
    }
}

//==============================================================================
//  Function    : MMPS_USB_GetStatus
//==============================================================================
/**
    @brief Return USB device current status.
    @return gsUsbCurStatus
    @retval 0 normal,
    @retval 1 isAdapter,
    @retval 2 idle
*/
MMPS_USB_StatusMode MMPS_USB_GetStatus(void)
{
    //check if usb device is plugged;
    #if 1
    if (MMPS_USB_DetectVBus5V()) {//protection: if usb is not connected, the status will always be MMPS_USB_IDLE

        if (gsUsbCurStatus == MMPS_USB_IDLE){
            MMPS_USB_DetectAdaptorOrUSB();
        }
    }
    else
    #endif
        gsUsbCurStatus = MMPS_USB_IDLE;

    return gsUsbCurStatus;
}

//==============================================================================
//  Function    : MMPS_USB_GetLastStatus
//==============================================================================
/**
    @brief Return USB device Last status.
    @return gsUsbCurStatus
    @retval 0 normal,
    @retval 1 isAdapter,
    @retval 2 idle
*/
MMPS_USB_StatusMode MMPS_USB_GetLastStatus(void)
{
    return gsUsbCurStatus;
}

//==============================================================================
//  Function    : MMPS_USB_GetWriteFlag
//==============================================================================
/**
    @brief Return the flag which indicates if USB device is under write operation.
    @return gsMSDCStartWrite.
    @retval 0 USB device is doing write operation.
    @retval 1 USB device is not doing write operation.
*/
MMP_UBYTE MMPS_USB_GetWriteFlag(void)
{
    MMP_ERR status;
    MMP_UBYTE ubUSBWriting = 0;

    status = MMPD_USB_GetWriteFlag(&ubUSBWriting);
    if (!status) {
        return ubUSBWriting;
    }
    else {
        RTNA_DBG_Str(0, "USB ERROR: get write flag fail\r\n");
        return ubUSBWriting;
    }
}

//==============================================================================
//  Function    : MMPS_USB_GetReadFlag
//==============================================================================
/**
    @brief Return the flag which indicates if USB device is under read operation.
    @return gbMSDCStartRead
    @retval 0 USB device is doing read operation.
    @retval 1 USB device is not doing read operation.
*/
MMP_UBYTE MMPS_USB_GetReadFlag(void)
{
    MMP_ERR status;
    MMP_UBYTE ubUSBReading = 0;

    status = MMPD_USB_GetReadFlag(&ubUSBReading);

    if (!status) {
        return ubUSBReading;
    }
    else {
        RTNA_DBG_Str(0, "USB ERROR: get Read flag fail\r\n");
        return ubUSBReading;
    }
}

MMP_ERR MMPS_USB_DisconnectDevice(void)
{
    return MMP_ERR_NONE;
}

#if 0
void ____USB_MSDC_Func____(){ruturn;} //dummy
#endif

//==============================================================================
//  Function    : MMPS_USBMSDC_SetMaxUnitNum
//==============================================================================
/**
    @brief  Set the MSDC maximum units allowed to show up
    @param[in] ubMaxUnitCnt : The number of units to show up
    @return MMP_ERR_NONE
*/
MMP_ERR MMPS_USBMSDC_SetMaxUnitNum(MMP_UBYTE ubMaxUnitCnt)
{
    MMPD_USB_SetMSDCMaxUnits(ubMaxUnitCnt);

    return MMP_ERR_NONE;
}

#if 0
void ____USB_Host_Func____(){ruturn;} //dummy
#endif

#if (SUPPORT_USB_HOST_FUNC)
//==============================================================================
//
//                USB HOST RELATED FUNCTION DEFINITION
//
//==============================================================================
//------------------------------------------------------------------------------
//  Function    : MMPS_USB_RegDetectCallBack
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
MMP_ERR MMPS_USB_RegDetectCallBack(void *pReadUSBIDTimeoutCallback, void *pOtgSessionTimeoutCallback, void *pDevConnCallback, void *pDevDisconnCallback)
{
	return MMPD_USB_RegPollingCallBack(pReadUSBIDTimeoutCallback,pOtgSessionTimeoutCallback,pDevConnCallback,pDevDisconnCallback);
}

//------------------------------------------------------------------------------
//  Function    : MMPS_USB_TriggerReadUSBID
//  Description :
//------------------------------------------------------------------------------
/**
 @brief Trigger to read USB_ID.
 @param[in] pulTimerId Fetch the timer ID that create by driver.
 @retval MMP_ERR_NONE Success.
 @retval MMP_USB_ERR_PARAMETER Unsupport parameters.
*/
MMP_ERR MMPS_USB_TriggerReadUSBID(MMP_ULONG *pulTimerId)
{
	return MMPD_USB_TriggerReadUSBID(pulTimerId);
}

//------------------------------------------------------------------------------
//  Function    : MMPS_USB_ReadUSBID
//  Description :
//------------------------------------------------------------------------------
/**
 @brief Read USB_ID after trigger timeout.
 @param[in] pubDevType Fetch the device type(A or B).
 @retval MMP_ERR_NONE Success.
 @retval MMP_USB_ERR_PARAMETER Unsupport parameters.
*/
MMP_ERR MMPS_USB_ReadUSBID(MMP_UBYTE *pubDevType)
{
	return MMPD_USB_ReadUSBID(pubDevType);
}

//------------------------------------------------------------------------------
//  Function    : MMPS_USB_StartOTGSession
//  Description :
//------------------------------------------------------------------------------
/**
 @brief Start OTG session.
 @param[in] pulTimerId Fetch the timer ID that create by driver.
 @retval MMP_ERR_NONE Success.
 @retval MMP_USB_ERR_PARAMETER Unsupport parameters.
*/
MMP_ERR MMPS_USB_StartOTGSession(MMP_ULONG *pulTimerId)
{
	return MMPD_USB_StartOTGSession(pulTimerId);
}

//------------------------------------------------------------------------------
//  Function    : MMPS_USB_StopOTGSession
//  Description :
//------------------------------------------------------------------------------
/**
 @brief Stop OTG session coercively [BE CAREFUL, MAY IMPACT CONNECTION SR].
 @retval MMP_ERR_NONE Success.
 @retval MMP_USB_ERR_UNSUPPORT_MODE Unsupport parameters.
*/
MMP_ERR MMPS_USB_StopOTGSession(void)
{
	return MMPD_USB_StopOTGSession();
}

//------------------------------------------------------------------------------
//  Function    : MMPS_USB_GetDevConnSts
//  Description :
//------------------------------------------------------------------------------
/**
 @brief Get device connection status.
 @param[in] pbStatus Fetch the connection status.
 @retval MMP_ERR_NONE Success.
 @retval MMP_USB_ERR_PARAMETER Unsupport parameters.
*/
MMP_ERR MMPS_USB_GetDevConnSts(MMP_BOOL *pbStatus)
{
	return MMPD_USB_GetDevConnSts(pbStatus);
}

//------------------------------------------------------------------------------
//  Function    : MMPS_USB_SetDevConnSts
//  Description :
//------------------------------------------------------------------------------
/**
 @brief BE CAREFUL, SPECIAL CASE! Forced set device connection status.
 @param[in] pbStatus Set the connection status.
 @retval MMP_ERR_NONE Success.
 @retval MMP_USB_ERR_PARAMETER Unsupport parameters.
*/
MMP_ERR MMPS_USB_SetDevConnSts(MMP_BOOL pbStatus)
{
	return MMPD_USB_SetDevConnSts(pbStatus);
}

//------------------------------------------------------------------------------
//  Function    : MMPS_USB_EnumUVC
//  Description :
//------------------------------------------------------------------------------
/**
 @brief Enumeration UVC device.
 @retval MMP_ERR_NONE Success.
 @retval MMP_USB_ERR_UNSUPPORT_MODE Unsupport parameters.
*/
MMP_ERR MMPS_USB_EnumUVC(void)
{
	return MMPD_USB_EnumUVC();
}

//------------------------------------------------------------------------------
//  Function    : MMPS_USB_GetUVCStreamSts
//  Description :
//------------------------------------------------------------------------------
/**
 @brief Get UVC device stream status.
 @param[in] pbStatus Fetch the stream status.
 @retval MMP_ERR_NONE Success.
 @retval MMP_USB_ERR_UNSUPPORT_MODE Unsupport parameters.
*/
MMP_ERR MMPS_USB_GetUVCStreamSts(MMP_BOOL *pbStatus)
{
	return MMPD_USB_GetUVCStreamSts(pbStatus);
}

//------------------------------------------------------------------------------
//  Function    : MMPS_USB_RegUVCMDCallBack
//  Description :
//------------------------------------------------------------------------------
/**
@brief The function sets UVC device following configs.
@param[in] pDevTriggerMDCallback The callback to be executed when UVC device MD triggered.
@return It reports the status of the operation.
*/
MMP_ERR MMPS_USB_RegUVCMDCallBack(void *pDevTriggerMDCallback)
{
    return MMPD_USB_RegUVCMDCallBack(pDevTriggerMDCallback);
}

//------------------------------------------------------------------------------
//  Function    : MMPS_USB_EnableUVCMD
//  Description :
//------------------------------------------------------------------------------
/**
 @brief Enable UVC MD.
 Enable to inform USBH, and driver will execute callback(pDevTriggerMDCallback) when MD triggered frame received.
 @retval MMP_ERR_NONE Success.
 @retval MMP_3GPRECD_ERR_GENERAL_ERROR Not allowed procedure.
*/
MMP_ERR MMPS_USB_EnableUVCMD(void)
{
	return MMPD_USB_EnableUVCMD();
}

//------------------------------------------------------------------------------
//  Function    : MMPS_USB_DisableUVCMD
//  Description :
//------------------------------------------------------------------------------
/**
 @brief Stop UVC video recording.
 Disable and do not execute callback(pDevTriggerMDCallback) even  MD triggered frame received.
 @retval MMP_ERR_NONE Success.
 @retval MMP_3GPRECD_ERR_GENERAL_ERROR Not allowed procedure.
*/
MMP_ERR MMPS_USB_DisableUVCMD(void)
{
	return MMPD_USB_DisableUVCMD();
}

//------------------------------------------------------------------------------
//  Function    : MMPS_USB_SetCheckDevAliveCFG
//  Description :
//------------------------------------------------------------------------------
/**
@brief The function register following configs for error handle.
@param[in] pulCheckDevAliveInterval The timer interval to check device alive.
@param[in] pDevNoResponseCallback The callback will be executed when device no response.
@return It reports the status of the operation.
*/
MMP_ERR MMPS_USB_SetCheckDevAliveCFG(MMP_ULONG pulCheckDevAliveInterval, void *pDevNoResponseCallback)
{
	return MMPD_USB_SetCheckDevAliveCFG(pulCheckDevAliveInterval,pDevNoResponseCallback);
}

//------------------------------------------------------------------------------
//  Function    : MMPS_USB_SetTranTimeoutCFG
//  Description :
//------------------------------------------------------------------------------
/**
@brief The function register following configs for error handle.
@param[in] pulTranTimeoutInterval The timer interval to check transaction timeout.
@param[in] pDevTranTimeoutCallback The callback will be executed when transaction timeout.
@return It reports the status of the operation.
*/
MMP_ERR MMPS_USB_SetTranTimeoutCFG(MMP_ULONG pulTranTimeoutInterval, void *pDevTranTimeoutCallback)
{
	return MMPD_USB_SetTranTimeoutCFG(pulTranTimeoutInterval,pDevTranTimeoutCallback);
}

//------------------------------------------------------------------------------
//  Function    : MMPS_USB_SetFrmRxTimeoutCFG
//  Description :
//------------------------------------------------------------------------------
/**
@brief The function register following configs for error handle.
@param[in] pulFrmRxLostTH The lost frame count of threshold to be trigger callback.
@param[in] pulFrmRxFirstAddGap The first frame additional gap of the lost frame count of threshold to be trigger callback.
@param[in] pDevFrmRxLostTHCallback The callback will be executed when frame lost reach pulFrmRxLostTH.
@return It reports the status of the operation.
*/
MMP_ERR MMPS_USB_SetFrmRxTimeoutCFG(MMP_ULONG pulFrmRxLostTH, MMP_ULONG pulFrmRxFirstAddGap, void *pDevFrmRxLostTHCallback)
{
	return MMPD_USB_SetFrmRxTimeoutCFG(pulFrmRxLostTH,pulFrmRxFirstAddGap,pDevFrmRxLostTHCallback);
}

//------------------------------------------------------------------------------
//  Function    : MMPS_USB_SetFrmRxTimeout2CFG
//  Description :
//------------------------------------------------------------------------------
/**
@brief The function register following configs for error handle.
@param[in] pulFrmRxLostTH2 The 2nd lost frame count of threshold to be trigger callback.
@param[in] pDevFrmRxLostTH2Callback The callback will be executed when frame lost reach pulFrmRxLostTH2.
@return It reports the status of the operation.
*/
MMP_ERR MMPS_USB_SetFrmRxTimeout2CFG(MMP_ULONG pulFrmRxLostTH2, void *pDevFrmRxLostTH2Callback)
{
	return MMPD_USB_SetFrmRxTimeout2CFG(pulFrmRxLostTH2,pDevFrmRxLostTH2Callback);
}

//------------------------------------------------------------------------------
//  Function    : MMPS_USB_SetFrmSeqNoLostCFG
//  Description :
//------------------------------------------------------------------------------
/**
@brief The function register following configs for error handle.
@param[in] pulSeqNoLostTH The lost frame seq. no of threshold to be trigger callback.
@param[in] pDevSeqNoLostTHCallback The callback will be executed when frame seq no lost reach pulSeqNoLostTH.
@return It reports the status of the operation.
*/
MMP_ERR MMPS_USB_SetFrmSeqNoLostCFG(MMP_ULONG pulSeqNoLostTH, void *pDevSeqNoLostTHCallback)
{
	return MMPD_USB_SetFrmSeqNoLostCFG(pulSeqNoLostTH,pDevSeqNoLostTHCallback);
}

//------------------------------------------------------------------------------
//  Function    : MMPS_USB_StopFrmRxClrFIFO
//  Description :
//------------------------------------------------------------------------------
/**
@brief BE CAREFUL, forced to stop USB frame Rx and clear FIFO.
@param[in] None.
@return It reports the status of the operation.
*/
MMP_ERR MMPS_USB_StopFrmRxClrFIFO(void)
{
	return MMPD_USB_StopFrmRxClrFIFO();
}

//------------------------------------------------------------------------------
//  Function    : MMPS_USB_SetDropRxFrmCFG
//  Description :
//------------------------------------------------------------------------------
/**
@brief The function register following configs for error handle.
@param[in] ulTotalCnt
@param[in] ulContinCnt
@param[in] *pDropRxFrmCallback
@return It reports the status of the operation.
*/
MMP_ERR MMPS_USB_SetDropRxFrmCFG(MMP_ULONG ulTotalCnt, MMP_ULONG ulContinCnt, void *pDropRxFrmCallback)
{
    return MMPD_USB_SetDropRxFrmCFG(ulTotalCnt, ulContinCnt, pDropRxFrmCallback);
}

#else

MMP_ERR MMPS_USB_TriggerReadUSBID(MMP_ULONG *pulTimerId)
{
    return MMP_ERR_NONE;
}

MMP_ERR MMPS_USB_ReadUSBID(MMP_UBYTE *pubDevType)
{
    *pubDevType = GPIO_HIGH; //Not connected.
    return MMP_ERR_NONE;
}

MMP_ERR MMPS_USB_StartOTGSession(MMP_ULONG *pulTimerId)
{
    return MMP_ERR_NONE;
}

MMP_ERR MMPS_USB_GetDevConnSts(MMP_BOOL *pbStatus)
{
    *pbStatus = MMP_FALSE;
    return MMP_ERR_NONE;
}

#endif

///@end_ait_only
/// @}
