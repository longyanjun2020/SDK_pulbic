//------------------------------------------------------------------------------
//
//  File        : usb_cfg.c
//  Description : Source file of USB descriptors and configuration
//  Author      : Alterman
//  Revision    : 0.0
//
//------------------------------------------------------------------------------

//==============================================================================
//
//                              INCLUDE FILE
//
//==============================================================================

#include "usb_cfg.h"
#include "snr_cfg.h"
#include "mmpf_usbh_ctl.h"
#include "component_huvc.h"

//==============================================================================
//
//                              VARIABLES
//
//==============================================================================
//------------------------------------------------------------------------------
//                              Common
//------------------------------------------------------------------------------
/* String Descriptor Zero */
unsigned char   gubStrDescZero[STR_ZERO_LENGTH] = {
    STR_ZERO_LENGTH,    // bLength
    DESC_TYPE_STRING,   // bDescriptorType
    0x09, 0x04          // wLANGID[0]: UNICODE
};

/* Manufacturer UNICODE String Descriptor */
unsigned char   gubManufacturStrDesc[MFR_STR_LENGTH] = {
    MFR_STR_LENGTH,     // bLength
    DESC_TYPE_STRING,   // bDescriptorType
    'A',0,'l',0,'p',0,'h',0,'a',0,' ',0,
    'I',0,'m',0,'a',0,'g',0,'i',0,'n',0,'g',0,' ',0,
    'T',0,'e',0,'c',0,'h',0
};

/* Product UNICODE String Descriptor */
unsigned char   gubProductStrDesc[PROD_STR_LENGTH] = {
    PROD_STR_LENGTH,    // bLength
    DESC_TYPE_STRING,   // bDescriptorType
    'M',0,'M',0,'P',0,' ',0,
    'S',0,'D',0,'K',0
};

/* SerialNumber UNICODE String Descriptor */
unsigned char   gubSerialNumStrDesc[SN_STR_LENGTH] = {
    SN_STR_LENGTH,      // bLength
    DESC_TYPE_STRING,   // bDescriptorType
    '0',0,'1',0,'2',0,'3',0,
    '5',0,'6',0,'7',0,'8',0,
    '8',0,'9',0,'A',0,'B',0,
    'C',0,'D',0,'E',0,'F',0
};

/* For detecting USB charger mode,
 * set the timeout value (ms) to wait the 1st EP0 transfer */
unsigned int    gulUsbOpModeDtcTimeOut = USB_OP_DTC_TIMEOUT;

/* B device setting */
MMP_USBPHY_VREF         gususb_vref = MMP_USB_VREF_400mV;
MMP_USBPHY_BIAS_CURRENT gususb_bias_current = MMP_USB_BIAS_CURRENT_25uA;
MMP_USBPHY_TX_CUR       gususb_tx_cur = MMP_USB_TX_CUR_440mV;
MMP_USBPHY_TX_CUR_PLUS  gususb_tx_cur_plus = MMP_USB_TX_CUR_PLUS_00mV;
MMP_USBPHY_SQ           gususb_sq_level = MMP_USB_SQ_62d5mV;

//------------------------------------------------------------------------------
//                              Mass Storage Class
//------------------------------------------------------------------------------
/* MSC VID/PID in Device Descriptor */
unsigned short  gusMscVendorID = MSC_VENDOR_ID;
unsigned short  gusMscProductID = MSC_PRODUCT_ID;

/* MSC Manufacturer String Descriptor */
unsigned char   *gpMscMfrStrDesc = gubManufacturStrDesc;

/* MSC Product String Descriptor */
unsigned char   *gpMscProdStrDesc = gubProductStrDesc;

/* MSC SerialNumber String Descriptor */
unsigned char   *gpMscSnStrDesc = gubSerialNumStrDesc;

/* Standard INQUIRY Data */
unsigned char   gubMscInquiryData[MSDC_MAX_UNITS][INQ_DATA_SIZE] = {
{
    0x00,                   // Peripheral Device Type
    (1 << INQ_RMB_OFST),    // Removale Media Bit
    0x00,                   // ANSI/ECMA/ISO Version
    0x01,                   // Response Data Format
    0x1F, 0x00, 0x00, 0x00, // Additional Length
    'A', 'I', 'T', ' ',     // Vendor information, 8 bytes
    ' ', ' ', ' ', ' ',
    'C', 'a', 'r', 'd',     // Product Identification, 16 bytes
    ' ', 'R', 'e', 'a',
    'd', 'e', 'r', '_',
    '0', ' ', ' ', ' ',
    '0', '.', '0', '0'      // Product Revision Level
}
#if (MSDC_MAX_UNITS > 1)
,
{
    0x00,                   // Peripheral Device Type
    (1 << INQ_RMB_OFST),    // Removale Media Bit
    0x00,                   // ANSI/ECMA/ISO Version
    0x01,                   // Response Data Format
    0x1F, 0x00, 0x00, 0x00, // Additional Length
    'A', 'I', 'T', ' ',     // Vendor information, 8 bytes
    ' ', ' ', ' ', ' ',
    'C', 'a', 'r', 'd',     // Product Identification, 16 bytes
    ' ', 'R', 'e', 'a',
    'd', 'e', 'r', '_',
    '1', ' ', ' ', ' ',
    '0', '.', '0', '0'      // Product Revision Level
}
#endif
#if (MSDC_MAX_UNITS > 2)
,
{
    0x00,                   // Peripheral Device Type
    (1 << INQ_RMB_OFST),    // Removale Media Bit
    0x00,                   // ANSI/ECMA/ISO Version
    0x01,                   // Response Data Format
    0x1F, 0x00, 0x00, 0x00, // Additional Length
    'A', 'I', 'T', ' ',     // Vendor information, 8 bytes
    ' ', ' ', ' ', ' ',
    'C', 'a', 'r', 'd',     // Product Identification, 16 bytes
    ' ', 'R', 'e', 'a',
    'd', 'e', 'r', '_',
    '2', ' ', ' ', ' ',
    '0', '.', '0', '0'      // Product Revision Level
}
#endif
#if (MSDC_MAX_UNITS > 3)
,
{
    0x00,                   // Peripheral Device Type
    (1 << INQ_RMB_OFST),    // Removale Media Bit
    0x00,                   // ANSI/ECMA/ISO Version
    0x01,                   // Response Data Format
    0x1F, 0x00, 0x00, 0x00, // Additional Length
    'A', 'I', 'T', ' ',     // Vendor information, 8 bytes
    ' ', ' ', ' ', ' ',
    'C', 'a', 'r', 'd',     // Product Identification, 16 bytes
    ' ', 'R', 'e', 'a',
    'd', 'e', 'r', '_',
    '3', ' ', ' ', ' ',
    '0', '.', '0', '0'      // Product Revision Level
}
#endif
};

/* Unit Write protected configuration */
/*
 * Set to 1 if the unit has to be read-only;
 * Set to 0 then check device if write-protected by IO control command.
 */
unsigned char   gubMscUnitWriteProtect[MSDC_MAX_UNITS] = {
    0
#if (MSDC_MAX_UNITS > 1)
    ,
    0
#endif
#if (MSDC_MAX_UNITS > 2)
    ,
    0
#endif
#if (MSDC_MAX_UNITS > 3)
    ,
    0
#endif
};

//------------------------------------------------------------------------------
//                              USB Video Class
//------------------------------------------------------------------------------
#if (SUPPORT_UVC_FUNC)
/* UVC VID/PID in Device Descriptor */
unsigned short  gusUvcVendorID = UVC_VENDOR_ID;
unsigned short  gusUvcProductID = UVC_PRODUCT_ID;

/* UVC Manufacturer String Descriptor */
unsigned char   *gpUvcMfrStrDesc = gubManufacturStrDesc;

/* UVC Product String Descriptor */
unsigned char   *gpUvcProdStrDesc = gubProductStrDesc;

/* UVC Video Control Interface String Descriptor */
unsigned char   gubUvcVidCtrlStrDesc[UVC_VC_STR_LENGTH] = {
    UVC_VC_STR_LENGTH,  // bLength
    DESC_TYPE_STRING,   // bDescriptorType
    'V',0,'i',0,'d',0,'e',0,'o',0,' ',0,
    'C',0,'o',0,'n',0,'t',0,'r',0,'o',0,'l',0
};

/* UVC Video Stream Interface String Descriptor */
unsigned char   gubUvcVidStrmStrDesc[UVC_VS_STR_LENGTH] = {
    UVC_VS_STR_LENGTH,  // bLength
    DESC_TYPE_STRING,   // bDescriptorType
    'V',0,'i',0,'d',0,'e',0,'o',0,' ',0,
    'S',0,'t',0,'r',0,'e',0,'a',0,'m',0
};

/* UVC Processing Unit bmControls field */
unsigned short  gusUvcPuControls = PU_CTLBIT_BRIGHTNESS |
                                   PU_CTLBIT_CONTRAST |
                                   PU_CTLBIT_HUE |
                                   PU_CTLBIT_SATURATION |
                                   PU_CTLBIT_SHARPNESS |
                                   PU_CTLBIT_GAMMA |
                                   PU_CTLBIT_WB_TEMP |
                                   PU_CTLBIT_BACKLIGHT_COMPENS |
                                   PU_CTLBIT_PWR_LINE_FREQ |
                                   PU_CTLBIT_AWB_TEMP;

unsigned short  gusUvcYUY2MaxWidth = 1280;
unsigned short  gusUvcYUY2MaxHeight = 720;
unsigned short  gusUvcMJPGMaxWidth = 1280;
unsigned short  gusUvcMJPGMaxHeight = 720;
#endif

//------------------------------------------------------------------------------
//                              USB Audio Class
//------------------------------------------------------------------------------
#if (SUPPORT_UVC_FUNC)&&(SUPPORT_UAC)
MMP_AUD_INOUT_PATH  gUacInPath = MMP_AUD_AFE_IN_DIFF; // now support AFE only
MMP_AUD_LINEIN_CH   gUacInCh = MMP_AUD_LINEIN_DUAL;
unsigned char       gbUacDefaultVol = 20;   // 20 dB
unsigned char       gbUacMaxVol = 28;       // 28 dB
unsigned char       gbUacMinVol = 0;        //  0 dB
#endif

#if (SUPPORT_USB_HOST_FUNC)
//------------------------------------------------------------------------------
//                              USB Host Related
//------------------------------------------------------------------------------
#if 1
/* USB 1M cable setting: */
//Bulk: NAKLIMIT 2^(m-1), value 0 or 1 disable NAK timeout function
//ISO: Rx polling interval 2^(m-1) frames/microframes, value between 1~16
unsigned char   gubusbh_ep0_tx_interval = 0;
unsigned char   gubusbh_ep0_rx_interval = 0;
unsigned char   gubusbh_ep_tx_interval = 0;
unsigned char   gubusbh_ep_rx_interval = 0;
//A device setting
MMP_USBPHY_VREF         gususbh_vref = MMP_USB_VREF_400mV;
MMP_USBPHY_BIAS_CURRENT gususbh_bias_current = MMP_USB_BIAS_CURRENT_25uA;
MMP_USBPHY_TX_CUR       gususbh_tx_cur = MMP_USB_TX_CUR_400mV;
MMP_USBPHY_TX_CUR_PLUS  gususbh_tx_cur_plus = MMP_USB_TX_CUR_PLUS_20mV;
MMP_USBPHY_SQ           gususbh_sq_level = MMP_USB_SQ_62d5mV;
#else // #if 1
/* USB 10M cable setting: */
//Bulk: NAKLIMIT 2^(m-1), value 0 or 1 disable NAK timeout function
//ISO: Rx polling interval 2^(m-1) frames/microframes, value between 1~16
unsigned char   gubusbh_ep0_tx_interval = 16;
unsigned char   gubusbh_ep0_rx_interval = 16;
unsigned char   gubusbh_ep_tx_interval = 16;
unsigned char   gubusbh_ep_rx_interval = 16;
//A device setting
MMP_USBPHY_VREF         gususbh_vref = MMP_USB_VREF_400mV;
MMP_USBPHY_BIAS_CURRENT gususbh_bias_current = MMP_USB_BIAS_CURRENT_25uA;
MMP_USBPHY_TX_CUR       gususbh_tx_cur = MMP_USB_TX_CUR_480mV;
MMP_USBPHY_TX_CUR_PLUS gususbh_tx_cur_plus = MMP_USB_TX_CUR_PLUS_00mV;
MMP_USBPHY_SQ           gususbh_sq_level = MMP_USB_SQ_62d5mV;
#endif

/* UVC YUV(preview) max support setting */
unsigned short  gusUsbhMaxYuvWidth = MAX_SUPPORT_YUV_WIDTH;
unsigned short  gusUsbhMaxYuvHeight = MAX_SUPPORT_YUV_HEIGHT;

/* UVC tx flow status */
unsigned char   gubUVCFrmFlowSts = USBH_UVC_FRM_TO_MGR;

/* UVC Rx EP buffer count */
unsigned short  gusUVCRxEpBufCnt = EP_RX_BUF_CNT_ISO;

/* UVC Rx EP buffer size */
unsigned short  gusUVCRxEpBufSz = EP_RX_BUF_SIZE;

/* UVC Rx EP full buffer size */
unsigned int    gulUVCRxEpFullBufSz = EP_RX_BUF_CNT_ISO * EP_RX_BUF_SIZE;

/* UVC record frame queue size */
unsigned short  gusUVCRecdFrmQSize = RECD_FRM_Q_SZ_ISO;

/* UVC record frame buffer count */
unsigned short  gusUVCRecdFrmBufCnt = RECD_FRM_BUF_CNT_ISO;

/* UVC record frame buffer size */
unsigned int    gulUVCRecdFrmBufSize = RECD_FRM_BUF_SZ_ISO;

/* Enable semaphore to isolate endpoint 0 and endpoint 1, prevent work together, 
   if disable, endpoint x (USB Rx DMA trigger) always at ISR */
unsigned char   gbUsbEpIsolationEnable = MMP_FALSE;   

/* UVC device parsed info. */
__align(4) USB_UVC_DEV_INFO        gUsbh_UvcDevInfo;
/*
 *                                                  Prevw   Prevw   Prevw   Prevw           Prevw
 *      PID     VID     VC  VS  EU  IT  PU  Typ Ep  FmtIdx  MaxW    MaxH    MaxResFrmIdx    FrmIntvl
 * 5256 0C45    64AB    0   1   3   1   2   1   81  2       500     2D0     1               61A80
 * 216  0C45    6300    0   1   4   1   3   1   81  2       280     1E0     1               51615
 * 8451 114D    8451    0   1   6   1   3   2   81  TBD     TBD     TBD     TBD             TBD
 * 8437 114D    8455    0   1   6   1   3   2   81  TBD     TBD     TBD     TBD             TBD
 */

/* UVC(rear cam) Mjpeg WiFi Stream info. */
USB_UVC_MJPEG_WIFI_CFG  gUsbh_UvcMjpegWifiCfg = {0};

USBH_CAM_CFG gsUsbhCamCfg =
{
    MMP_TRUE,   // bUseISOMode
    MMP_TRUE,   // bSyncTime
    MMP_TRUE,   // bDecMjpegToPreview
    MMP_TRUE,   // bDecMjpegToEncH264
};

//==============================================================================
//
//                              FUNCTIONS
//
//==============================================================================

#if 0
void _____USBH_Functions_____(){}
#endif

void MMP_InitUSBHConfig(MMP_UBYTE ubCamSel)
{
	MMP_ULONG ulCompPar;

    if (ubCamSel == USB_CAM_SONIX_MJPEG ||
        ubCamSel == USB_CAM_AIT) {
        gubUVCFrmFlowSts = USBH_UVC_FRM_TO_MGR;
    }
    else {
        gubUVCFrmFlowSts = USBH_UVC_FRM_TO_PIPE;
    }
    
    if (ubCamSel == USB_CAM_AIT) {
        gsUsbhCamCfg.bSyncTime = MMP_TRUE;
    }
    else {
        gsUsbhCamCfg.bSyncTime = MMP_FALSE;
    }
    
    if (ubCamSel == USB_CAM_SONIX_MJPEG ||
        ubCamSel == USB_CAM_SONIX_MJPEG2H264) {
        gsUsbhCamCfg.bUseISOMode = MMP_TRUE;
        gsUsbhCamCfg.bDecMjpegToPreview = MMP_TRUE;
        
        gusUVCRxEpBufCnt = EP_RX_BUF_CNT_ISO;
        gusUVCRxEpBufSz = EP_RX_BUF_SIZE;
        gulUVCRxEpFullBufSz = gusUVCRxEpBufCnt * gusUVCRxEpBufSz;
        
        gusUVCRecdFrmQSize = RECD_FRM_Q_SZ_ISO;
        gusUVCRecdFrmBufCnt = RECD_FRM_BUF_CNT_ISO;
        gulUVCRecdFrmBufSize = RECD_FRM_BUF_SZ_ISO;
        
        gbUsbEpIsolationEnable = MMP_FALSE;
        gubusbh_ep_rx_interval = 1; // 1 for 10M cable

        MMPF_USBH_SetITransferMode(MMP_TRUE);
        ulCompPar = HUVC_COMP_USB_MODE_ISO;
        Component_HUVC_SetParam(&Component_HUVC[HUVC_COMP_UVC],HUVC_COMP_PARAM_USB_MODE,&ulCompPar);
        ulCompPar = ISO_MJPEG_MAX_VIDEO_FRM_SIZE;
        Component_HUVC_SetParam(&Component_HUVC[HUVC_COMP_UVC],HUVC_COMP_PARAM_BUF_SIZE,&ulCompPar);
        ulCompPar = PREVW_FRM_BUF_CNT;
        Component_HUVC_SetParam(&Component_HUVC[HUVC_COMP_UVC],HUVC_COMP_PARAM_BUF_NUM,&ulCompPar);
    }
    else {
        gsUsbhCamCfg.bUseISOMode = MMP_FALSE;
        gsUsbhCamCfg.bDecMjpegToPreview = MMP_FALSE;
        
        if (ubCamSel == USB_CAM_AIT && 
            MMP_GetAitCamStreamType() == AIT_REAR_CAM_STRM_MJPEG_H264) {
            gsUsbhCamCfg.bDecMjpegToPreview = MMP_TRUE;
        }
        
        gusUVCRxEpBufCnt = EP_RX_BUF_CNT_BULK;
        gusUVCRxEpBufSz = EP_RX_BUF_SIZE;
        gulUVCRxEpFullBufSz = gusUVCRxEpBufCnt * gusUVCRxEpBufSz;
        
        gusUVCRecdFrmQSize = RECD_FRM_Q_SZ_BULK;
        gusUVCRecdFrmBufCnt = RECD_FRM_BUF_CNT_BULK;
        gulUVCRecdFrmBufSize = RECD_FRM_BUF_SZ_BULK;
        
        gbUsbEpIsolationEnable = MMP_TRUE;
        gubusbh_ep_rx_interval = 0; // 16 for 10M cable
        
        MMPF_USBH_SetITransferMode(MMP_FALSE);        

        ulCompPar = HUVC_COMP_USB_MODE_BULK;
        Component_HUVC_SetParam(&Component_HUVC[HUVC_COMP_UVC],HUVC_COMP_PARAM_USB_MODE,&ulCompPar);
        ulCompPar = AIT_MJPEG_MAX_VIDEO_FRM_SIZE;
        Component_HUVC_SetParam(&Component_HUVC[HUVC_COMP_UVC],HUVC_COMP_PARAM_BUF_SIZE,&ulCompPar);
        ulCompPar = PREVW_FRM_BUF_CNT;
        Component_HUVC_SetParam(&Component_HUVC[HUVC_COMP_UVC],HUVC_COMP_PARAM_BUF_NUM,&ulCompPar);
    }
    
    if (ubCamSel == USB_CAM_SONIX_MJPEG2H264) {
        gsUsbhCamCfg.bDecMjpegToEncH264 = MMP_TRUE;
    }
    else if (ubCamSel == USB_CAM_AIT) {
        if (MMP_GetAitCamStreamType() == AIT_REAR_CAM_STRM_MJPEG_H264)
            gsUsbhCamCfg.bDecMjpegToEncH264 = MMP_TRUE;
        else
            gsUsbhCamCfg.bDecMjpegToEncH264 = MMP_FALSE;
    }
    else {
        gsUsbhCamCfg.bDecMjpegToEncH264 = MMP_FALSE;
    }
}

MMP_BOOL MMP_IsUSBCamIsoMode(void)
{
    return gsUsbhCamCfg.bUseISOMode;
}

MMP_BOOL MMP_IsSupportSyncUVCTime(void)
{
    return gsUsbhCamCfg.bSyncTime;
}

MMP_BOOL MMP_IsSupportDecMjpegToPreview(void)
{
    return gsUsbhCamCfg.bDecMjpegToPreview;
}

MMP_BOOL MMP_IsSupportDecMjpegToEncH264(void)
{
    return gsUsbhCamCfg.bDecMjpegToEncH264;
}

#endif // SUPPORT_USB_HOST_FUNC

