#ifndef _MMPF_USBVEND_H
#define _MMPF_USBVEND_H

#include "lib_retina.h"

/*************************************************************/
/*                                                           */
/*                        MACROS                             */
/*                                                           */
/*************************************************************/
#define HIBYTE(v1)      ((MMP_UBYTE)((v1)>>8))
#define LOBYTE(v1)      ((MMP_UBYTE)((v1)&0xff))

#define MSSBYTE(v1)     ((MMP_UBYTE)((v1)>>24))
#define HISBYTE(v1)     ((MMP_UBYTE)((v1)>>16))
#define LOSBYTE(v1)     ((MMP_UBYTE)((v1)>>8))
#define LESBYTE(v1)     ((MMP_UBYTE)((v1)&0xff))  
#define WSTR(x)         size_t(x)
#define LE_CONST_W(x)   (x) & 0xff, ((x) >> 8) & 0xff
#define LE_CONST_DW(x)  (x) & 0xff, ((x) >> 8) & 0xff, \
                        ((x) >> 16) & 0xff, ((x) >> 24) & 0xff
/*************************************************************/
/*                                                           */
/*                        STRUCTURE                          */
/*                                                           */
/*************************************************************/
#if (MSDC_WR_FLOW_TEST_EN == 1)

#define MMPF_USB_W_DATA_BUFF_SIZE 0x10000
#define MMPF_USB_W_DATA_BUFF_DEPTH 0x14
#define USB_MSDC_Q_THRESHOLD 0xA

typedef struct {
    MMP_UBYTE isValid;  //0: free space, no valid data; 1: filled data
    MMP_ULONG startSec;
    MMP_ULONG secSize;
    MMP_UBYTE* dataBuf;
    MMP_ULONG ulMsdcLun;
} _st_usb_write_buff_queue;
#endif

#if (SUPPORT_MTP_FUNC==1)||(SUPPORT_DPS_FUNC==1)
typedef struct  {
    MMP_ULONG   TxBufAddr;
    MMP_ULONG   RxBufAddr;
    MMP_ULONG   RxTxBufSize;
    MMP_ULONG   InterruptBufAddr;
    MMP_ULONG	MBufAddr; //Andy++
    MMP_ULONG	MBufSize; //Andy++
} MTP_DMA_HANDLE;
#endif

typedef struct{
    MMP_UBYTE   bmRequestType;
    MMP_UBYTE   bRequest;
    MMP_USHORT  wValue;
    MMP_USHORT  wIndex;
    MMP_USHORT  wLength;
}USB_REQUEST_PAYLOAD;

typedef struct{
    MMP_UBYTE   *pDeviceDescriptor;
    MMP_USHORT  DeviceDescriptorSize;
    MMP_UBYTE   *pDeviceQualifierDescriptor;
    MMP_USHORT  DeviceQualifierDescriptorSize;
    MMP_UBYTE   *pConfigDescriptor;
    MMP_USHORT  ConfigDescriptorSize;
    MMP_UBYTE   *pOtherSpeedConfigDescriptor;
    MMP_USHORT  OtherSpeedConfigDescriptorSize;
    MMP_UBYTE   *pExtendedConfigData;
    MMP_USHORT  pExtendedConfigDataSize;
    MMP_UBYTE   *pStrDescriptor0;
    MMP_USHORT  StrDescriptor0Size;
    MMP_UBYTE   *pStrDescriptor1;
    MMP_USHORT  StrDescriptor1Size;
    MMP_UBYTE   *pStrDescriptor2;
    MMP_USHORT  StrDescriptor2Size;
    MMP_UBYTE   *pStrDescriptor3;
    MMP_USHORT  StrDescriptor3Size;
    MMP_UBYTE   *pStrDescriptor4;
    MMP_USHORT  StrDescriptor4Size;
    MMP_UBYTE   *pStrDescriptor5;
    MMP_USHORT  StrDescriptor5Size;
#if defined(SUPPORT_HID_FUNC) && (SUPPORT_HID_FUNC)
    MMP_UBYTE   *pReportDescriptor;
    MMP_USHORT  ReportDescriptorSize;
#endif    
}USB_DESCRIPTOR;

typedef enum _AIT_STORAGE_TYPE{
	AIT_STORAGE_MOVINAND = 0,
	AIT_STORAGE_ESD,
	AIT_STORAGE_EMMC,
	AIT_STORAGE_SIF,
	AIT_STORAGE_NAND,
	AIT_STORAGE_PCAM_SF
} AIT_STORAGE_TYPE;

/*************************************************************/
/*                                                           */
/*                        VARIABLE                           */
/*                                                           */
/*************************************************************/

/*************************************************************/
/*                                                           */
/*                        DEFINES                            */
/*                                                           */
/*************************************************************/

#define USB_DMA_MODE

#define ENABLE_USB_EJECT_FEATURE 	(1)
#define AIT_USB_DEBUG				3
#define AIT_MTP_PERFORMANCE_TEST	0

// Endpoints setting
#define MSDC_TX_EP_ADDR				(0x01)
#define MSDC_RX_EP_ADDR				(0x02)
//Wilson@101011: for Logitech chap8 test
#define MSDC_INT_EP_ADDR			(0x03)

#define PCCAM_TX_EP_ADDR			(0x01)
#define PCCAM_RX_EP_ADDR			(0x02)

#define MTP_TX_EP_ADDR				(0x01)
#define MTP_RX_EP_ADDR				(0x02)
#define MTP_INT_EP_ADDR				(0x03)

#define PCSYNC_TX_EP_ADDR			(0x01)
#define PCSYNC_RX_EP_ADDR			(0x02)

//Endpoint package size setting
#define MSDC_HS_TX_PKTSIZE			(0x0200)
#define MSDC_HS_RX_PKTSIZE			(0x0200)
#define MSDC_FS_TX_PKTSIZE			(0x0040)
#define MSDC_FS_RX_PKTSIZE			(0x0040)
//Wilson@101011: for Logitech chap8 test
#define MSDC_INT_PKTSIZE			(0x0020)

#define PCCAM_HS_TX_PKTSIZE			(0x0200)
#define PCCAM_HS_RX_PKTSIZE			(0x0200)
#define PCCAM_FS_TX_PKTSIZE			(0x0040)
#define PCCAM_FS_RX_PKTSIZE			(0x0040)

#define MTP_HS_TX_PKTSIZE			(0x0200)
#define MTP_HS_RX_PKTSIZE			(0x0200)
#define MTP_INT_PKTSIZE				(0x0020)
#define MTP_FS_TX_PKTSIZE			(0x0040)
#define MTP_FS_RX_PKTSIZE			(0x0040)
//#define MTP_FS_INT_PKTSIZE			(0x0020)

#define PCSYNC_HS_TX_PKTSIZE		(0x0200)
#define PCSYNC_HS_RX_PKTSIZE		(0x0200)
#define PCSYNC_FS_TX_PKTSIZE		(0x0040)
#define PCSYNC_FS_RX_PKTSIZE		(0x0040)

#define CBW_STATE		00
#define CSW_STATE		01
#define TX_STATE		02
#define RX_STATE		03
#define WP_STATE		04

#define VENDOR_REQUEST	0x10
#define USB_DUMMY		0x00

#define VENDOR_CMD		0x30
#define VENDOR_IN		0x31

#define MS_VENDOR_CODE	0x55

// bDescriptorType: Ref. USB 2.0 spec Chap9
#define DEVICE_DESCRIPTOR                   (0x1)
#define CONFIG_DESCRIPTOR                   (0x2)
#define STRING_DESCRIPTOR                   (0x3)
#define INTERFACE_DESCRIPTOR                (0x4)
#define ENDPOINT_DESCRIPTOR                 (0x5)
#define DEVICE_QUALIFIER_DESCRIPTOR         (0x6)
#define OTHER_SPEED_CONFIG_DESCRIPTOR       (0x7)
#define INTERFACE_POWER_DESCRIPTOR          (0x8)
#define INTERFACE_ASSOCIATION_DESCRIPTOR    (0xB)
#define  REPORT_DESCRIPTOR             (0x22)

//class type
//(0x00): means the class information is carry by interface descriptor
#define USB_AUDIO_CLASS					(0x01)
#define USB_HID_CLASS					(0x03)	//human interface device
#define USB_IMAGE_CLASS					(0x06)
#define USB_PRINTER_CLASS			 	(0x07)
#define USB_MASS_STORAGE_CLASS 			(0x08)
#define USB_HUB_CLASS 					(0x09)
#define USB_VIDEO_CLASS 				(0x0E)
#define USB_MISC_CLASS					(0xEF)
#define USB_APP_SPECIFIC_CLASS			(0xFE)
#define USB_VENDOR_SPECIFIC_CLASS		(0xFF)


#if 0
void _UVC_RELATIVE_DEF_(void) {}
#endif

#if (SUPPORT_UVC_FUNC)

#define UVC_TEST
#define UVC_EXU
#define TX_ADD_FRAME_BITS(x)            ((x) << 11)
#define AUDIO_PACKET_SIZE(samprate,sampchannel) \
                                        (512) & 0xFF , \
                                        (512) >> 8

#define ENABLE_FRAME_BASE_H264

#if USB_UVC_SKYPE
    #define ENABLE_YUY2
#else
    #define ENABLE_YUY2
#endif
#define ENABLE_MJPEG
#define USING_OLD_H264_FILTER       (0)

/* Format index */
#ifdef ENABLE_YUY2
#define YUY2_FORMAT_INDEX               (1)
#else
#define YUY2_FORMAT_INDEX               (0)
#endif
#ifdef ENABLE_UYVY
#define UYVY_FORMAT_INDEX               (YUY2_FORMAT_INDEX + 1)
#else
#define UYVY_FORMAT_INDEX               (YUY2_FORMAT_INDEX)
#endif
#ifdef ENABLE_NV12
#define NV12_FORMAT_INDEX               (UYVY_FORMAT_INDEX + 1)
#else
#define NV12_FORMAT_INDEX               (UYVY_FORMAT_INDEX)
#endif
#ifdef ENABLE_MJPEG 
#define MJPEG_FORMAT_INDEX              (NV12_FORMAT_INDEX + 1)
#else
#define MJPEG_FORMAT_INDEX              (NV12_FORMAT_INDEX)
#endif
#ifdef ENABLE_FRAME_BASE_H264
#define FRAME_BASE_H264_INDEX           (MJPEG_FORMAT_INDEX + 1)
#else
#define FRAME_BASE_H264_INDEX           (MJPEG_FORMAT_INDEX)
#endif
#ifdef ENABLE_FRAME_BASE_AVC1
#define FRAME_BASE_AVC1_FORMAT_INDEX    (FRAME_BASE_H264_INDEX + 1)
#else
#define FRAME_BASE_AVC1_FORMAT_INDEX    (FRAME_BASE_H264_INDEX)
#endif

/* total numbers of video formats */
#define UVC_NUM_FORMATS                 (FRAME_BASE_AVC1_FORMAT_INDEX)

/* Endpoint number  */
#define UVC_TX_EP_ADDR				(0x01)
#define UVC_INT_EP_ADDR				(0x03)
#define UVC_AU_EP_ADDR				(0x02)
#define UVC_EX_EP_ADDR				(0x03)

#if 1//USB_UVC_BULK_EP
#define UVC_HS_TX_PKTSIZE           (512)
#define UVC_FS_TX_PKTSIZE           (64)
#else   
#define UVC_HS_TX_PKTSIZE           (1016)
#define UVC_FS_TX_PKTSIZE           (992)
#endif

#define UVC_INT_PKTSIZE				(0x0040)
#define UVC_EXEP_PKTSIZE			(8)
#define UVC_AUEP_PKTSIZE			(1016)

#define ENABLE_HS_HB_NOW            (1)

#if ENABLE_HS_HB_NOW==1
    #define TX_PER_FRAME            (3)
#else
	#define TX_PER_FRAME            (1)
#endif

//Video interface class code
#define CC_VIDEO                    (0x0E)

//vidoe interface protocol codes
#define PC_PROTOCOL_UNDEFINED       (0x00)

//terminal Types
//usb terminal types
#define TT_VENDOR_SPECIFIC          (0x0100)
#define TT_STREAMING                (0x0101)

//input terminal types
#define ITT_VENDOR_SPECIFIC         (0x0200)
#define ITT_CAMERA                  (0x0201)
#define ITT_MEDIA_TRANSPORT_INPUT   (0x0202)

//output terminal types
#define OTT_VENDOR_SPECIFIC         (0x0300)
#define OTT_DISPLAY                 (0x0301)
#define OTT_MEDIA_TRANSPORT_OUTPUT  (0x0302)

//**********************************************************************************
// descriptor length
//**********************************************************************************
/* Standard descriptors length */
#define USB_CONFIG_DESC_LEN         (0x09)
#define USB_IAD_DESC_LEN            (0x08)
#define USB_STD_INT_DESC_LEN        (0x09)
#define USB_EP_DESC_LEN             (0x07)

/* UVC related descriptors length */
#define UVC_VC_HDR_DESC_LEN         (0x0D)
#define UVC_OT_DESC_LEN             (0x09)
#define UVC_IT_DESC_LEN             (0x12)
#define UVC_XU_DESC_LEN             (0x1B)
#define UVC_PU_DESC_LEN             (0x0B)
#define UVC_EP_INTR_DESC            (0x05)
#define UVC_VS_HDR_DESC_LEN         (0x0D + UVC_NUM_FORMATS)
#define UVC_COLOR_DESC_LEN          (0x06)
// SKYPE XU descriptor
#if (USB_UVC_SKYPE)
#define UVC_SKYPE_XU_DESC_LEN       (UVC_XU_DESC_LEN)
#else
#define UVC_SKYPE_XU_DESC_LEN       (0)
#endif

#define UVC_VC_HDR_FULL_LEN         (UVC_VC_HDR_DESC_LEN +              \
                                     UVC_OT_DESC_LEN +                  \
                                     UVC_XU_DESC_LEN +                  \
                                     UVC_XU_DESC_LEN +                  \
                                     UVC_SKYPE_XU_DESC_LEN +            \
                                     UVC_IT_DESC_LEN +                  \
                                     UVC_PU_DESC_LEN)

#define UVC_YUY2_FMT_DESC_LEN       (0x1B)
#define UVC_YUY2_FRAME_DESC_LEN     (0x1E)
#define UVC_YUY2_ALL_FRAME_DESC_LEN (UVC_YUY2_FRAME_DESC_LEN * NUM_YUY2_VIDEO)
#if (USING_STILL_METHOD_1)
#define UVC_YUY2_STILL_DESC_LEN     (0)
#else
#define UVC_YUY2_STILL_DESC_LEN     (0x07 + (NUM_YUY2_STILL * 4))
#endif

#define UVC_MJ_FMT_DESC_LEN         (0x0B)
#define UVC_MJ_FFAME_DESC_LEN       (0x1E)
#define UVC_MJ_ALL_FRAME_DESC_LEN   (UVC_MJ_FFAME_DESC_LEN * NUM_MJPG_VIDEO)
#if (USING_STILL_METHOD_1)
#define UVC_MJ_STILL_DESC_LEN       (0)
#else
#define UVC_MJ_STILL_DESC_LEN       (0x07 + (NUM_MJPG_STILL * 4))
#endif

#define UVC_FB_H264_FMT_DESC_LEN    (0x1C)
#define UVC_FB_H264_FRAME_DESC_LEN  (0x26)
#define UVC_FB_H264_ALL_FRAME_DESC_LEN (UVC_FB_H264_FRAME_DESC_LEN * NUM_H264_VIDEO)

/* UAC related descriptors length */
#define UAC_AC_HDR_DESC_LEN         (0x09)
#define UAC_IT_DESC_LEN             (0x0C)
#define UAC_OT_DESC_LEN             (0x09)
#define UAC_FEATURE_DESC_LEN        (0x08)
#define UAC_AS_HDR_DESC_LEN         (0x07)
#define UAC_I_FMT_DESC_LEN          (0x0B)
#define UAC_EP_DESC_LEN             (0x09)
#define UAC_ISO_EP_DESC_LEN         (0x07)

#if defined(SUPPORT_HID_FUNC) && (SUPPORT_HID_FUNC)
#define HID_EP_ADDR                                      (0x04) //(0x05)
#define HID_MAX_PK_SIZE                                  (0x08)
#define USB_IF_HID_DESC_SIZE                             (0x19)

#if (USB_HID_FUNC_USAGE_TABLE == USB_HID_FUNC_KEYBOARD) 
#define REPORT_DESCRIPTOR_LEN                            (0x2D)//mouse: (0x3E), keyboard:(0x3F)
#endif
#if (USB_HID_FUNC_USAGE_TABLE == USB_HID_FUNC_MOUSE) 
#define REPORT_DESCRIPTOR_LEN                            (0x3E)
#endif
#if (USB_HID_FUNC_USAGE_TABLE == USB_HID_FUNC_VENDOR_DEFINED)  
#define REPORT_DESCRIPTOR_LEN                            (28)
#endif

#else
#define USB_IF_HID_DESC_SIZE                             (0)
#endif

/* Sub-descriptors in configuration descriptor */
// YUY2 format descriptors
#ifdef ENABLE_YUY2
#define UVC_VS_YUY2_DESC_LEN        (UVC_YUY2_FMT_DESC_LEN +            \
                                     UVC_YUY2_ALL_FRAME_DESC_LEN +      \
                                     UVC_YUY2_STILL_DESC_LEN +          \
                                     UVC_COLOR_DESC_LEN)
#else
#define UVC_VS_YUY2_DESC_LEN        (0)
#endif
// MJPEG format descriptors
#ifdef ENABLE_MJPEG
#define UVC_VS_MJ_DESC_LEN          (UVC_MJ_FMT_DESC_LEN +              \
                                     UVC_MJ_ALL_FRAME_DESC_LEN +        \
                                     UVC_MJ_STILL_DESC_LEN +            \
                                     UVC_COLOR_DESC_LEN)
#else
#define UVC_VS_MJ_DESC_LEN          (0)
#endif
// Frame based H.264 format descriptors
#ifdef ENABLE_FRAME_BASE_H264
#define UVC_VS_FB_H264_DESC_LEN     (UVC_FB_H264_FMT_DESC_LEN +         \
                                     UVC_FB_H264_ALL_FRAME_DESC_LEN +   \
                                     UVC_COLOR_DESC_LEN)
#else
#define UVC_VS_FB_H264_DESC_LEN     (0)
#endif

#define UVC_VS_HDR_FULL_LEN         (UVC_VS_HDR_DESC_LEN +              \
                                     UVC_VS_YUY2_DESC_LEN +             \
                                     UVC_VS_MJ_DESC_LEN +               \
                                     UVC_VS_FB_H264_DESC_LEN)

// Standard interface descriptor for ISO mode alternate setting
#if 1//(USB_UVC_BULK_EP)
#define UVC_ISO_STD_INT_DESC_LEN   (0)
#else
#define UVC_ISO_STD_INT_DESC_LEN   (USB_STD_INT_DESC_LEN)
#endif

// UAC descriptors
#if (SUPPORT_UAC)
#define UAC_AC_HDR_FULL_LEN         (UAC_AC_HDR_DESC_LEN +              \
                                     UAC_IT_DESC_LEN +                  \
                                     UAC_OT_DESC_LEN +                  \
                                     UAC_FEATURE_DESC_LEN)
#define UAC_DESC_LEN                (USB_IAD_DESC_LEN +                 \
                                     USB_STD_INT_DESC_LEN +             \
                                     UAC_AC_HDR_FULL_LEN +              \
                                     USB_STD_INT_DESC_LEN +             \
                                     USB_STD_INT_DESC_LEN +             \
                                     UAC_AS_HDR_DESC_LEN +              \
                                     UAC_I_FMT_DESC_LEN +               \
                                     UAC_EP_DESC_LEN +                  \
                                     UAC_ISO_EP_DESC_LEN)
#else
#define UAC_DESC_LEN                (0)
#endif

// PCSYNC descriptors
#if (SUPPORT_PCSYNC)
#define PCSYNC_DESC_LEN             (USB_STD_INT_DESC_LEN +             \
                                     USB_EP_DESC_LEN +                  \
                                     USB_EP_DESC_LEN +                  \
                                     USB_STD_INT_DESC_LEN)
#else
#define PCSYNC_DESC_LEN             (0)
#endif

/* Configuration descriptor total lenth */
#define UVC_HS_CONFIG_DESC_LEN      (USB_CONFIG_DESC_LEN +              \
                                     USB_IAD_DESC_LEN +                 \
                                     USB_STD_INT_DESC_LEN +             \
                                     UVC_VC_HDR_FULL_LEN +              \
                                     USB_EP_DESC_LEN +                  \
                                     UVC_EP_INTR_DESC +                 \
                                     USB_STD_INT_DESC_LEN +             \
                                     UVC_VS_HDR_FULL_LEN +              \
                                     UVC_ISO_STD_INT_DESC_LEN +         \
                                     USB_EP_DESC_LEN +                  \
                                     UAC_DESC_LEN +                     \
                                     PCSYNC_DESC_LEN + \
                                     USB_IF_HID_DESC_SIZE)
#define UVC_FS_CONFIG_DESC_LEN      (USB_CONFIG_DESC_LEN +              \
                                     USB_IAD_DESC_LEN +                 \
                                     USB_STD_INT_DESC_LEN +             \
                                     UVC_VC_HDR_FULL_LEN +              \
                                     USB_EP_DESC_LEN +                  \
                                     UVC_EP_INTR_DESC +                 \
                                     USB_STD_INT_DESC_LEN +             \
                                     UVC_VS_HDR_FULL_LEN +              \
                                     UVC_ISO_STD_INT_DESC_LEN +         \
                                     USB_EP_DESC_LEN +                  \
                                     UAC_DESC_LEN + \
                                     PCSYNC_DESC_LEN + \
                                    USB_IF_HID_DESC_SIZE)
	
	/////////////////////////////////////////////////////////////////////////////////////

    extern  MMP_UBYTE UVC_DEVICE_QUALIFIER_DESCRIPTOR[0x0A];
    extern  MMP_UBYTE UVC_HIGH_SPEED_CONFIG_DESCRIPTOR[];
    extern  MMP_UBYTE UVC_DEVICE_DESCRIPTOR[0x12];
    extern  MMP_UBYTE UVC_FULL_SPEED_CONFIG_DESCRIPTOR[];
#if defined(SUPPORT_HID_FUNC) && (SUPPORT_HID_FUNC)
    extern  MMP_UBYTE   HID_REPORT_DSCR_DATA[];
#endif

	/////////////////////////////////////////////////////////////////////////////////////	
	#define     DEVICE_QUALIFIER_DESCRIPTOR_DATA0_ADDR   (0)
	#define     DEVICE_DESCRIPTOR_DATA0_ADDR             (DEVICE_QUALIFIER_DESCRIPTOR_DATA0_ADDR+0x0A)
	#define     CONFIG_DESCRIPTOR_DATA0_ADDR             (DEVICE_DESCRIPTOR_DATA0_ADDR+0x12)
	#define     DEVICE_QUALIFIER_DESCRIPTOR_DATA1_ADDR   (0)
	#define     DEVICE_DESCRIPTOR_DATA1_ADDR             (DEVICE_QUALIFIER_DESCRIPTOR_DATA1_ADDR+0x0A)
	#define     CONFIG_DESCRIPTOR_DATA1_ADDR             (DEVICE_DESCRIPTOR_DATA1_ADDR+0x12)
	#define     DEVICE_QUALIFIER_DESCRIPTOR_DATA2_ADDR   (0)
	#define     DEVICE_DESCRIPTOR_DATA2_ADDR             (DEVICE_QUALIFIER_DESCRIPTOR_DATA2_ADDR+0x0A)            
	#define     CONFIG_DESCRIPTOR_DATA2_ADDR             (DEVICE_DESCRIPTOR_DATA2_ADDR+0x12)          
	#define     DEVICE_QUALIFIER_DESCRIPTOR_DATA3_ADDR   (0)
	#define     DEVICE_DESCRIPTOR_DATA3_ADDR             (DEVICE_QUALIFIER_DESCRIPTOR_DATA3_ADDR+0x0A)            
	#define     CONFIG_DESCRIPTOR_DATA3_ADDR             (DEVICE_DESCRIPTOR_DATA3_ADDR+0x12)
	#define     DEVICE_QUALIFIER_DESCRIPTOR_DATA4_ADDR   (0)
	#define     DEVICE_DESCRIPTOR_DATA4_ADDR             (DEVICE_QUALIFIER_DESCRIPTOR_DATA4_ADDR+0x0A)
	#define     CONFIG_DESCRIPTOR_DATA4_ADDR             (DEVICE_DESCRIPTOR_DATA4_ADDR+0x12)
	#define     DEVICE_QUALIFIER_DESCRIPTOR_DATA5_ADDR   (0)
	#define     DEVICE_DESCRIPTOR_DATA5_ADDR             (DEVICE_QUALIFIER_DESCRIPTOR_DATA5_ADDR+0x0A)            
	#define     CONFIG_DESCRIPTOR_DATA5_ADDR             (DEVICE_DESCRIPTOR_DATA5_ADDR+0x12)

	#define     LANGUAGE_ID_DATA_ADDR                   (CONFIG_DESCRIPTOR_DATA1_ADDR+CONFIG_DESCRIPTOR_LEN)              
	#define     MANUFACTURER_STRING_DATA_ADDR           (LANGUAGE_ID_DATA_ADDR+0x04)           
	#define     PRODUCT_STRING_DATA_ADDR                (MANUFACTURER_STRING_DATA_ADDR+0x34/*0x1E*/)             
	#define     SERIALNUMBER_STRING_DATA_ADDR           (PRODUCT_STRING_DATA_ADDR+0x2A/*0x1E*/)            
	#define     DESCRIPTOR_TABLE_END_ADDR               (SERIALNUMBER_STRING_DATA_ADDR+0x1a)

	// ERROR_CODE
	#define CONTROL_NO_ERROR         0x00
	#define CONTROL_NOT_READY        0x01
	#define CONTROL_WRONG_STATE      0x02
	#define CONTROL_POWER            0x03
	#define CONTROL_OUT_OF_RANGE     0x04
	#define CONTROL_INVALID_UNIT     0x05
	#define CONTROL_INVALID_CONTROL  0x06
	#define CONTROL_INVALID_REQUEST  0x07
	#define CONTROL_UNKNOWN          0xFF
	
	//extern 
	extern void MMPF_USB_ResetUVCMode(void);
#endif  //#if (SUPPORT_UVC_FUNC)

typedef enum _MMPF_USB_OP_MODE
{
	USB_NONE_MODE = 0x0,
    USB_PCCAM_MODE,			///< PCCAM
    USB_MSDC_MODE,		    ///< MSDC
    USB_DPS_MODE,           ///< PICTURE BRIDGE
    USB_PTP_MODE,			///< PTP
	USB_PCSYNC_MODE,		///< PCSYNC
    USB_MTP_MODE,			///< MTP
    USB_DETECT_MODE,		///< For device detection
    USB_ISOTEST_MODE,		///< For test USB HB iso-mode
    USB_ADAPTER_MODE,		///< For USB Adapter or Charger used
#if (SUPPORT_MSDC_SCSI_AIT_CMD_MODE)
    USB_MSDC_AIT_DEBUG_MODE, //< For MSDC SCSI vendor command mode.
#endif	
	USB_MAX_MODE
} MMPF_USB_OP_MODE;

typedef MMP_ULONG (*MSDC_AIT_SCSI_CUSTOMER_CB) (const MMP_UBYTE *pCmd, MMP_UBYTE *pTxBuf, MMP_ULONG ulCmdLen, MMP_ULONG ulMaxTxBufLen);

// MSDC States relative variables
#define MSDC_CBW_STATE              (0x0)
#define MSDC_DATA_TRANSFER_STATE_RX (0x1)
#define MSDC_DATA_TRANSFER_STATE_TX (0x2)
#define MSDC_CSW_STATE              (0x3)

#define MSDC_CBW_SIZE               (0x1F)
#define MSDC_CSW_SIZE				(0x0D)

// MSDC mode command set
#define MSDC_TEST_UNIT_READY_CMD                (0x00)
#define MSDC_REZERO_CMD                         (0x01)
#define MSDC_REQUEST_SENSE_CMD                  (0x03)
#define MSDC_FORMAT_UNIT_CMD                    (0x04)
#define MSDC_INQUIRY_CMD                        (0x12)
#define MSDC_MODE_SELECT_15_CMD                 (0x15)
#define MSDC_MODE_SENSE_1A_CMD                  (0x1A)
#define MSDC_START_STOP_UNIT_CMD                (0x1B)
#define MSDC_SEND_DIAGNOSTIC_CMD                (0x1D)
#define MSDC_PREVENT_ALLOW_MEDIUM_REMOVAL_CMD   (0x1E)
#define MSDC_READ_FORMAT_CAPACITY_CMD           (0x23)
#define MSDC_READ_CAPACITY_CMD                  (0x25)
#define MSDC_READ_10_CMD                        (0x28)
#define MSDC_WRITE_10_CMD                       (0x2A)
#define MSDC_SEEK_10_CMD                        (0x2B)
#define MSDC_WRITE_AND_VERIFY_CMD               (0x2E)
#define MSDC_VERIFY_CMD                         (0x2F)
#define MSDC_MODE_SELECT_55_CMD                 (0x55)
#define MSDC_MODE_SENSE_5A_CMD                  (0x5A)
#define MSDC_READ_CAPACITY_16_CMD               (0x9E)
#define MSDC_READ_12_CMD                        (0xA8)
#define MSDC_WRITE_12_CMD                       (0xAA)

// Ted 100304: AIT SCSI special command
#define MSDC_AIT_SCSI_OPCODE	                (0xFA)
#define MSDC_AIT_SCSI_MAGIC_NUM0                (0x55)
#define MSDC_AIT_SCSI_MAGIC_NUM1                (0x66)

/*AIT BOOT command*/
#define MSDC_AIT_SCSI_GETINFO                   (0x01)
#define MSDC_AIT_SCSI_WRITEBOOTMEMORY           (0x02)
#define MSDC_AIT_SCSI_SWITCHCONTEXT             (0x03)
#define MSDC_AIT_SCSI_READREGISTER              (0x04)
#define MSDC_AIT_SCSI_WRITEREGISTER             (0x05)
#define MSDC_AIT_SCSI_SELECTSTORAGE             (0x06)
#define MSDC_AIT_SCSI_AITREAD                   (0x07)
#define MSDC_AIT_SCSI_AITWRITE                  (0x08)
#define MSDC_AIT_SCSI_SETBOOTSIZE               (0x09)
#define MSDC_AIT_SCSI_FORMATFS                  (0x0A)
#define MSDC_AIT_SCSI_ERASE_PARTITIONS          (0x0B)
#define MSDC_AIT_SCSI_ERASE_ALL_SECOTOR         (0x0C)
#define MSDC_AIT_SCSI_GET_NANDINFO				(0x0D)
#define MSDC_AIT_SCSI_QUERY_CMD                 (0x0E)
#define MSDC_AIT_SCSI_SET_PARAM                 (0x0F)
    #define MSDC_AIT_SCSI_PARAM_MAX_BYTE    (0x200)

#define MSDC_AIT_SCSI_MMC_RESET                 (0x11)
#define MSDC_AIT_SCSI_CUSTOMER					(0xFE)

#if (SUPPORT_MSDC_SCSI_AIT_CMD_MODE)
#define MSDC_AIT_SCSI_SYSTEM_FUNCTION (0x8001)
    #define MSDC_AIT_SCSI_GET_CHIP_INFO 			(0x0001)
    #define MSDC_AIT_SCSI_GET_CHIP_DRAM_SIZE 		(0x0002)
    #define MSDC_AIT_SCSI_GET_CHIP_FLASH_TYPE 		(0x0003)
    #define MSDC_AIT_SCSI_GET_CHIP_FW_VERSION 		(0x0004)
    #define MSDC_AIT_SCSI_GET_CHIP_FW_BUILD_DATE 	(0x0005)
    #define MSDC_AIT_SCSI_GET_CHIP_AIT_SCSI_STATUS 	(0x0006)    
    #define MSDC_AIT_SCSI_GET_CHIP_DEVICE_RESET 	(0x8001)   
    
#define MSDC_AIT_SCSI_AIT_LOG (0x8002)
    #define MSDC_AIT_SCSI_GET_LOG_LENGTH 			(0x0001)
    #define MSDC_AIT_SCSI_GET_LOG 					(0x0002)
    
#define MSDC_AIT_SCSI_RW_PERIPHERAL (0x8003)
    #define MSDC_AIT_SCSI_PERIPHERAL_TYPE_MOVINAND 	(0x0001)
    #define MSDC_AIT_SCSI_PERIPHERAL_TYPE_SD 		(0x0002)
    #define MSDC_AIT_SCSI_PERIPHERAL_TYPE_MMC 		(0x0003)
    #define MSDC_AIT_SCSI_PERIPHERAL_TYPE_SIF 		(0x0004)
    #define MSDC_AIT_SCSI_PERIPHERAL_TYPE_NAND 		(0x0005)
    #define MSDC_AIT_SCSI_PERIPHERAL_TYPE_SF 		(0x0006)    
    #define MSDC_AIT_SCSI_PERIPHERAL_TYPE_INTERNAL_MEMORY (0x0007)    
    #define MSDC_AIT_SCSI_PERIPHERAL_TYPE_POWERIC 	(0x0020)    
    #define MSDC_AIT_SCSI_PERIPHERAL_TYPE_SENSOR1 	(0x0021)    
    #define MSDC_AIT_SCSI_PERIPHERAL_TYPE_SENSOR2 	(0x0022)    
    #define MSDC_AIT_SCSI_PERIPHERAL_TYPE_EXTERNAL_DAC (0x0023)    
    #define MSDC_AIT_SCSI_PERIPHERAL_TYPE_LCD1 		(0x0024)    
    #define MSDC_AIT_SCSI_PERIPHERAL_TYPE_LCD2 		(0x0025)    
    #define MSDC_AIT_SCSI_PERIPHERAL_TYPE_GSENSOR 	(0x0040)    
    #define MSDC_AIT_SCSI_PERIPHERAL_TYPE_GPS 		(0x0041)    
    #define MSDC_AIT_SCSI_PERIPHERAL_TYPE_TOUCH 	(0x0042)        
    #define MSDC_AIT_SCSI_PERIPHERAL_TYPE_WIFI 		(0x0043)  

    #define MSDC_AIT_SCSI_PERIPHERAL_WRITE (0x00)  
    #define MSDC_AIT_SCSI_PERIPHERAL_READ (0x01)
    #define MSDC_AIT_SCSI_PERIPHERAL_SELECT_PARTITION (0x02)
    #define MSDC_AIT_SCSI_PERIPHERAL_READ_RESULT (0x81)

	#define MSDC_AIT_SCSI_PERIPHERAL_PARTITION_AREA_BOOT (0x01)
	#define MSDC_AIT_SCSI_PERIPHERAL_PARTITION_AREA_USER (0x02)

#define MSDC_AIT_SCSI_AUTO_TEST (0x8004)
    #define MSDC_AIT_SCSI_AUTO_TEST_RECORD_EVENT (0x0001)  
	#define MSDC_AIT_SCSI_AUTO_TEST_RECORD_START (0x01)
	#define MSDC_AIT_SCSI_AUTO_TEST_RECORD_STOP (0x00)
    #define MSDC_AIT_SCSI_AUTO_TEST_GET_EVENT_LOG_LENGTH (0x0002)
    #define MSDC_AIT_SCSI_AUTO_TEST_GET_EVENT_LOG (0x0003)
    #define MSDC_AIT_SCSI_AUTO_TEST_SEND_EVENT (0x0004)

#define MSDC_AIT_SCSI_SET_ISP (0x8005)
#define MSDC_AIT_SCSI_SET_DSC (0x8006)
#define MSDC_AIT_SCSI_SET_VIDEO (0x8007)
#define MSDC_AIT_SCSI_SET_AUDIO (0x8008)
#define MSDC_AIT_SCSI_SET_NETWORK (0x8009)
#define MSDC_AIT_SCSI_PROJECT_CMD (0x8FFF)	
#endif

// Wilson@101004: defines for MMi? need further check
#define GetROMByteCmd				0x06
#define GetDataCmd					0x15
#define SendDataCmd					0x16
#define SnapCmd						0x2D
#define UpdateFlashDataCmd			0x38
#define UpdateFWCmd					0x39
#define ATCmd						0x41
#define ChkIDCmd					0x55
#define SendIDCmd					0x56
#define SetRegCmd					0x81
#define SetResoCmd					0x8A
#define SetDevModeCmd				0x8C
#define SetBuffAccessAddrCmd		0xA0
#define GetBuffAccessSizeCmd		0xA1
#define GetRegCmd					0xF9


#define StdCmd						0x60
#define GetStatusCmd				0x60
#define ClearFeatureCmd				0x61
#define SetFeatureCmd				0x63
#define SetAddressCmd				0x65
#define GetDescriptorCmd			0x66
#define SetDescriptorCmd        	0x67
#define GetConfigCmd            	0x68
#define SetConfigCmd            	0x69
#define GetInterfaceCmd         	0x6A
#define SetInterfaceCmd         	0x6B
#define SynchFrameCmd           	0x6C

#define GetDevDescrCmd          	0x6D
#define GetConfigDescrCmd       	0x6E
#define GetStringDescrCmd       	0x6F

#define DEVICE_REMOTE_WAKEUP		0x01
#define ENDPOINT_STALL				0x00

#define ClassCmd					0xF0
#define BotResetCmd					0xFF
#define BotGetMaxLunCmd				0xFE
#define CANCEL_REQUEST_COMMAND		0x64
#define GET_DEVICE_STATUS_COMMAND	0x67
#define CancelRequestCmd			0xF2
#define GetDeviceStatusCmd			0xF3

/*************************************************************/
/*                                                           */
/*             USB Vendor Command for PC Sync                */
/*                                                           */
/*************************************************************/
#define VCMD_READ_REGISTER			0x00
#define VCMD_WRITE_REGISTER			0x01
#define VCMD_GET_MODE				0x10
#define VCMD_SET_BULK_IN			0x20
#define VCMD_SET_BULK_OUT			0x22
#define VCMD_SIZE_BULK_IN			0x24
#define VCMD_SIZE_BULK_OUT			0x26
#define VCMD_NOTIFY_BULK_IN_OK		0x30
#define VCMD_NOTIFY_BULK_OUT_OK		0x32

// for pcsync directly
#define VCMD_READ_PCSYNC			0x52
#define VCMD_WRITE_PCSYNC			0x54

/*************************************************************/
/*                                                           */
/*                        REGISTER                           */
/*                                                           */
/*************************************************************/

#define USB_BASE_ADDR				0x80001000

#define USB_BASE_B		((volatile unsigned char *)USB_BASE_ADDR)
#define USB_BASE_L		((volatile unsigned long *)USB_BASE_ADDR)
#define FB_BASE_B		((volatile unsigned char *)0)
#define FB_BASE_W		((volatile unsigned short *)0)
#define FB_BASE_L		((volatile unsigned long *)0)


//Wilson@101004: defines for MMi? need further check
#define USBHOSTINTENABLE1       0x00     // USB interrupt enable register 1
#define USBHOSTINTENABLE2       0x01   // USB interrupt enable register 2
#define USBHOSTINTSTATUS1       0x02   // USB interrupt status register 1
#define USBHOSTINTSTATUS2       0x03   // USB interrupt status register 2
#define USBARMINTENABLE1        0x04     // USB interrupt enable register 1
#define USBARMINTENABLE2        0x05   // USB interrupt enable register 2
#define USBARMINTSTATUS1        0x06   // USB interrupt status register 1
#define USBARMINTSTATUS2        0x07   // USB interrupt status register 2

#define USBEP0TXDMAEn           0x08     // USB DMA Enable register
#define USBEP0RXDMAEn           0x09     // USB DMA Enable register
#define USBEP1TXDMAEn           0x0A     // USB DMA Enable register
#define USBEP2RXDMAEn           0x0B     // USB DMA Enable register

#define USBDEVICEADDR           0x0C     // USB device address register
#define USBDEVICECTRL           0x0D     // USB device control register

#define USBTESTMODE             0x0E    // USB test mode control register

#define USBINTSEL               0x0F   // USB Every/Last Packet interrupt Select register
#define USBEP0CTRL              0x10   // USB endpoint control register
#define USBEP0TXSTATUS          0x11   // USB endpoint tx status
#define USBEP0RXSTATUS          0x12   // USB endpoint rx status
#define USBEP1CTRL              0x14   // USB endpoint control register
#define USBEP1TXSTATUS          0x15   // USB endpoint tx status
#define USBEP1RXSTATUS          0x16   // USB endpoint rx status
#define USBEP2CTRL              0x18   // USB endpoint control register
#define USBEP2TXSTATUS          0x19   // USB endpoint tx status
#define USBEP2RXSTATUS          0x1A   // USB endpoint rx status
#define USBEP3CTRL              0x1C   // USB endpoint control register
#define USBEP3TXSTATUS          0x1D   // USB endpoint tx status
#define USBEP3RXSTATUS          0x1E   // USB endpoint rx status

#define USBEP0TXSTARTADDR0      (0x20>>2)   // USB tx start address Low
//#define   USBEP0TXSTARTADDR1      0x21   // USB tx start address High
//#define   USBEP0TXSTARTADDR2      0x22   // USB tx start address Low
//#define   USBEP0TXSTARTADDR3      0x23   // USB tx start address High
#define USBEP0RXSTARTADDR0      (0x24>>2)   // USB rx start address Low
//#define   USBEP0RXSTARTADDR1      0x25   // USB rx start address High
//#define   USBEP0RXSTARTADDR2      0x26   // USB rx start address Low
//#define   USBEP0RXSTARTADDR3      0x27   // USB rx start address High
#define USBEP1TXSTARTADDR0      (0x28>>2)   // USB tx start address Low
//#define   USBEP1TXSTARTADDR1      0x29   // USB tx start address High
//#define   USBEP1TXSTARTADDR2      0x2A   // USB tx start address Low
//#define   USBEP1TXSTARTADDR3      0x2B   // USB tx start address High
#define USBEP2RXSTARTADDR0      (0x2C>>2)   // USB rx start address Low
//#define   USBEP2RXSTARTADDR1      0x2D   // USB rx start address High
//#define   USBEP2RXSTARTADDR2      0x2E   // USB rx start address Low
//#define   USBEP2RXSTARTADDR3      0x2F   // USB rx start address High

#define USBEP0TXPACKCNTLO       0x30   // USB tx packet count Low
#define USBEP0TXPACKCNTHI       0x31   // USB tx packet count High
#define USBEP0RXPACKCNTLO       0x32   // USB Rx packet count Low
#define USBEP0RXPACKCNTHI       0x33   // USB Rx packet count High
#define USBEP1TXPACKCNTLO       0x34   // USB tx packet count Low
#define USBEP1TXPACKCNTHI       0x35   // USB tx packet count High
#define USBEP2RXPACKCNTLO       0x36   // USB Rx packet count Low
#define USBEP2RXPACKCNTHI       0x37   // USB Rx packet count High
#define USBEP0TXLASTPACKSIZE    0x38   // USB TX Last Packet Size register
#define USBEP1TXLASTPACKSIZE    0x39   // USB TX Last Packet Size register
#define USBEP3TXLASTPACKSIZE    0x3A   // USB TX Last Packet Size register

#define USBREQTYPE              0x40    // USB request type
#define USBREQCODE              0x41    // USB request code
#define USBREQVALUE             0x42    // USB request value low byte
#define USBREQINDEX             0x44    // USB request index low byte
#define USBREQLENGTH            0x46    // USB request length low byte

#define USBPROBECTRL            0x50    // USB Probe Control register
#define USBPROBEREAD            0x51    // USB Probe read out data register
#define USBEP3TXENABLE       0x70//EP3 TX enable
#define USBEX3TXDATABYTE0            0x80 //EP3 TX DATA BYTE0


//descriptor table address
#if (SUPPORT_DPS_FUNC==1)
#define     DPS_LANGUAGE_ID_DATA_ADDR               CONFIG_DESCRIPTOR_DATA5_ADDR+0x27
#define     DPS_MANUFACTURER_STRING_DATA_ADDR       DPS_LANGUAGE_ID_DATA_ADDR+0x04
#define     DPS_PRODUCT_STRING_DATA_ADDR            DPS_MANUFACTURER_STRING_DATA_ADDR+0x1E
#define     DPS_SERIALNUMBER_STRING_DATA_ADDR       DPS_PRODUCT_STRING_DATA_ADDR+0x1E
#define     DPS_DESCRIPTOR_TABLE_END_ADDR           DPS_SERIALNUMBER_STRING_DATA_ADDR+0x12
#endif
#if (SUPPORT_MTP_FUNC==1)
#define     MTP_LANGUAGE_ID_DATA_ADDR               CONFIG_DESCRIPTOR_DATA4_ADDR+0x27
#define     MTP_MANUFACTURER_STRING_DATA_ADDR       MTP_LANGUAGE_ID_DATA_ADDR+0x04
#define     MTP_PRODUCT_STRING_DATA_ADDR            MTP_MANUFACTURER_STRING_DATA_ADDR+0x1E
#define     MTP_FRAME0_STRING_DATA_ADDR             MTP_PRODUCT_STRING_DATA_ADDR+0x1E
#define     MTP_FRAME1_STRING_DATA_ADDR             MTP_FRAME0_STRING_DATA_ADDR+0x0E
#define     MTP_DESCRIPTOR_TABLE_END_ADDR           MTP_FRAME1_STRING_DATA_ADDR+0x0E
#endif

#define PCSYNC_HANDSHAKE_BUF_SIZE           (16)
#define PCSYNC_OUTFLAG_OFFSET_B             (0)
#define PCSYNC_INFLAG_OFFSET_B              (1)
#define PCSYNC_INSIZE_OFFSET_W              (2)
#define PCSYNC_OUTSIZE_OFFSET_W             (4)

#define USB_CONTROL_IDLE            (0x0)
#define USB_CONTROL_TX              (0x1)
#define USB_CONTROL_RX              (0x2)

/* Request Direction */
#define USB_REQUEST_DIRECTION_BIT   (0x80)
#define USB_IN_DIR                  (0x80)
#define USB_OUT_DIR                 (0x00)

/* Endpoint Transfer Type */
#define USB_CTL_XFER_TYPE           (0x00)
#define USB_ISO_XFER_TYPE           (0x01)
#define USB_BULK_XFER_TYPE          (0x02)
#define USB_INT_XFER_TYPE           (0x03)

#define USB_REQUEST_TYPE_MASK       (0x60)
#define USB_REQUEST_RECEIVER_MASK   (0x1F)
#define USB_ENDPOINT_ADDRESS_MASK   (0x7F)

#define USB_STANDARD_REQUEST        (0x00)
#define USB_CLASS_REQUEST           (0x20)
#define USB_VENDOR_REQUEST          (0x40)

//wilson@110704 for uvc porting
#define  STD_CMD                   0x60
#define  GET_STATUS_CMD            0x60
#define  CLEAR_FEATURE_CMD         0x61
#define  SET_FEATURE_CMD           0x62
#define  SET_ADDRESS_CMD           0x63
#define  GET_DESCRIPTOR_CMD        0x64
#define  SET_DESCRIPTOR_CMD        0x65
#define  GET_CONFIG_CMD            0x66
#define  SET_CONFIG_CMD            0x67
#define  GET_INTERFACE_CMD         0x68
#define  SET_INTERFACE_CMD         0x69
#define  SYNCH_FRAME_CMD           0x6A

//#define  GET_HIDREPORT_DESCR_CMD    0x70

#define  CLASS_CMD					0xF0
#define  BOT_RESET_CMD				0xFF
#define  BOT_GET_MAX_LUN_CMD		0xFE

#define  GET_DEV_DESCR_CMD          0x6B
#define  GET_CONFIG_DESCR_CMD       0x6C
#define  GET_STRING_DESCR_CMD       0x6D
#define  GET_DEVQUA_DESCR_CMD       0x6E
#define  GET_OTHERSP_DESCR_CMD      0x6F
#define  GET_HIDREPORT_DESCR_CMD    0x70


#define STD_GET_STATUS_CMD          (0x0)
#define STD_CLEAR_FEATURE_CMD       (0x1)
#define STD_SET_FEATURE_CMD         (0x3)
#define STD_SET_ADDRESS_CMD         (0x5)
#define STD_GET_DESCRIPTOR_CMD      (0x6)
#define STD_SET_DESCRIPTOR_CMD      (0x7)
#define STD_GET_CONFIGURATION_CMD   (0x8)
#define STD_SET_CONFIGURATION_CMD   (0x9)
#define STD_GET_INTERFACE_CMD       (0xA)
#define STD_SET_INTERFACE_CMD       (0xB)
#define STD_SYNCH_FRAME_CMD         (0xC)

#define REQUEST_RECIVER_DEVICE      (0x0)
#define REQUEST_RECIVER_INTERFACE   (0x1)
#define REQUEST_RECIVER_ENDPOINT    (0x2)

#define MAX_INTERFACE_NUM           (0x1)
#define MAX_RX_ENDPOINT_NUM         (0x4)//(0x3) wilson@101011 for Logitech chap8 test
#define MAX_TX_ENDPOINT_NUM         (0x4)//(0x3)

#define CLEAR_WAKEUP_FEATURE        (0xFD)
#define SET_WAKEUP_FEATURE          (0x02)
#define CLEAR_HALT_FEATURE          (0xFE)
#define SET_HALT_FEATURE            (0x01)

#define ENDPOINT_HALT_FEATURE           (0x0)
#define DEVICE_REMOTE_WAKEUP_FEATURE    (0x1)
#define TEST_MODE_FEATURE               (0x2)

#define TEST_J                          (0x1)
#define TEST_K                          (0x2)
#define TEST_SE0_NAK                    (0x3)
#define TEST_PACKET                     (0x4)
#define TEST_FORCE_ENABLE               (0x5)

#define CBW_CBWSIGNATURE_INDEX          (0x0)
#define CBW_CBWTAG_INDEX                (CBW_CBWSIGNATURE_INDEX + 0x04)
#define CBW_CBWDATATRANSFERLENGTH_INDEX (CBW_CBWTAG_INDEX   + 0x04)
#define CBW_CBWFLAGS_INDEX              (CBW_CBWDATATRANSFERLENGTH_INDEX + 0x04)
#define CBW_CBWLUN_INDEX                (CBW_CBWFLAGS_INDEX     + 0x01)
#define CBW_CBWLENGTH_INDEX             (CBW_CBWLUN_INDEX   + 0x01)
#define CBW_CBWCB_INDEX                 (CBW_CBWLENGTH_INDEX    + 0x01)

#define CSW_CSWSIGNATURE_INDEX          (0x0)
#define CSW_CSWTAG_INDEX                (CSW_CSWSIGNATURE_INDEX + 0x04)
#define CSW_CSWDATARESIDUE_INDEX        (CSW_CSWTAG_INDEX + 0x04)
#define CSW_CSWSTATUS_INDEX             (CSW_CSWDATARESIDUE_INDEX + 0x04)


#define CBWCB_12_AllOC_LENGTH_INDEX             (CBW_CBWCB_INDEX + 0x04)

#define CBWCB_28_LBA3_INDEX                     (CBW_CBWCB_INDEX + 0x02)
#define CBWCB_28_LBA2_INDEX                     (CBW_CBWCB_INDEX + 0x03)
#define CBWCB_28_TxLen_MSB_INDEX                (CBW_CBWCB_INDEX + 0x07)
#define CBWCB_28_TxLen_LSB_INDEX                (CBW_CBWCB_INDEX + 0x08)

#define CBWCB_2A_LBA3_INDEX                     (CBW_CBWCB_INDEX + 0x02)
#define CBWCB_2A_LBA2_INDEX                     (CBW_CBWCB_INDEX + 0x03)
#define CBWCB_2A_RXLEN_MSB_INDEX                (CBW_CBWCB_INDEX + 0x07)
#define CBWCB_2A_RxLEN_LSB_INDEX                (CBW_CBWCB_INDEX + 0x08)

#define CLASS_CANCEL_REQUEST_CMD                (0x64)
#define CLASS_RESET_DEVICE_CMD                  (0x66)
#define CLASS_GET_DEVICE_STATUS_CMD             (0x67)
#define CLASS_MASS_STORAGE_RESET_CMD            (0xFF)
#define CLASS_GET_MAXLUN_CMD                    (0xFE)

#define PCCAM_SETDEVMODE_VCMD                   (0x8C)

#define PCSYNC_READREG_VCMD                     (0x00)
#define PCSYNC_BULKINSIZE_VCMD                  (0x24)
#define PCSYNC_BULKOUTSIZE_VCMD                 (0x26)

/*************************************************************/
/*                                                           */
/*                  Function Prototype                       */
/*                                                           */
/*************************************************************/

extern void usb_notify_bulkinok( void );
extern void usb_notify_bulkoutok( void );

extern void    UsbWriteTxMaxP(MMP_ULONG endpoint,MMP_ULONG size);
extern void    UsbWriteRxMaxP(MMP_ULONG endpoint,MMP_ULONG size);
extern void    UsbMSDCModeReset(void);
extern void    UsbPCCAMModeReset(void);
extern void    UsbMTPModeReset(void);
extern void    UsbPCSYNCModeReset(void);
extern void    UsbIntHandler(void);
extern void    UsbEp1RxIntHandler(MMP_ULONG ulRxPktCnt);
extern void    UsbEp1TxIntHandler(void);
extern void    UsbEp0IntHandler(void);
extern void    UsbEp0ClassCmdHandler(void);
extern void    UsbCtlRxMode(void);
extern void    UsbCtlTxMode(void);
extern void    UsbStdCmdRx(void);
extern void    UsbStdCmdTx(void);
extern void    UsbCtlIdleMode(void);
extern void    UsbCtlProcessRequest(void);
extern void    UsbProcessStdCmd(void);
extern void    UsbCtlNoDataPhaseMode(void);
extern void    UsbStdCmdNoDataPhase(void);
extern void    UsbResetIntHandler(void);
extern void    UsbWriteRxEpCSR(MMP_ULONG endpoint,MMP_USHORT csr);
extern void    UsbWriteTxEpCSR(MMP_ULONG endpoint,MMP_USHORT csr);
extern void    UsbWriteEp0CSR(MMP_USHORT csr);
extern MMP_USHORT    UsbReadRxEpCSR(MMP_ULONG endpoint);
extern MMP_USHORT    UsbReadTxEpCSR(MMP_ULONG endpoint);
extern MMP_USHORT    UsbReadEp0CSR(void);
extern MMP_USHORT    UsbReadRxEpCOUNT(MMP_ULONG endpoint);
extern MMP_USHORT    UsbReadEp0COUNT(void);
extern void    UsbDmaTxConfig(MMP_ULONG endpoint,MMP_ULONG fb_addr,MMP_ULONG pkt_byte,MMP_USHORT last_pkt_byte,MMP_ULONG pkt_sum,MMP_ULONG zero_end);
extern void    UsbDmaRxConfig(MMP_ULONG endpoint,MMP_ULONG fb_addr,MMP_ULONG pkt_byte,MMP_USHORT last_pkt_byte,MMP_ULONG pkt_sum);
extern void    UsbDmaStop(void);

extern void    UsbVendorCmdRx(void);
extern void    UsbVendorCmdTx(void);
extern void    UsbProcessVendorCmd(void);
extern void    UsbVendorCmdNoDataPhase(void);

extern void    UsbClassCmdRx(void);
extern void    UsbClassCmdTx(void);
extern void    UsbProcessClassCmd(void);
extern void    UsbClaseeCmdNoDataPhase(void);

extern void    UsbMSDCModeReset(void);
extern void    UsbMSDCRxIntHandler(void);
extern void    UsbMSDCTxIntHandler(void);
extern void    MMPF_MSDC_TriggerUsbTX(MMP_ULONG size,MMP_ULONG offset);
extern void    MMPF_MSDC_TriggerUsbRX(MMP_ULONG fb_addr,MMP_ULONG rx_byte);
extern void    MMPF_MSDC_SetCswHeader(MMP_UBYTE cCSWStatus);
extern void    MMPF_MSDC_SendCsw(void);
extern void    MMPF_MSDC_ProcessCmd(void);
extern void    MMPF_MSDC_TransfreStateRXHandle(void);
extern void    MMPF_MSDC_TransfreStateTXHandle(void);
extern void    MMPF_MSDC_StallRx(void);

extern void    PCSYNCBulkOutOk(void);
extern void    PCSYNCBulkInOk(void);

extern void    MMPF_MSDC_ProcessAITSpecialCmd(void);
extern void    MMPF_MSDC_EnableAITSpecialCmdFlag(void);
extern void    MMPF_MSDC_ClrAITSpecialCmdFlag(void);
extern MMP_UBYTE MMPF_MSDC_GetAITSpecialCmdFlag(void);

extern void MMPF_USB_StallTxEp(MMP_UBYTE endpoint);
extern void MMPF_USB_StallRxEp(MMP_UBYTE endpoint);

#if (SUPPORT_UVC_FUNC)
void MMPF_USB_InitUVCDesc(void);
#endif

void MMPF_USB_EnableEx(MMP_UBYTE endpoint);
void MMPF_USB_AddrAssigned(MMP_UBYTE addr);
void MMPF_SetUSBChangeMode(MMPF_USB_OP_MODE mode);
MMP_ERR MMPF_USB_StopDevice(void);
MMP_BOOL MMPF_USB_IsAdapter(void);

void MMPF_USB_HandleError(void);
void MMPF_USB_HandleEp0In(void);
void MMPF_USB_ResetEpSeq(MMP_UBYTE endpoint);
void MMPF_USB_FinishEp0NullOut(void);
void MMPF_USB_HandleStdReq(void);
void MMPF_USB_FinishEp0NullIn(void);
void MMPF_USBSTD_HandleReqOut(void);
void MMPF_USBSTD_HandleReqIn(void);
#if (MSDC_SUPPORT_AIT_CUSTOMER_SCSI_CMD)
void MMPF_MSDC_AITSCSI_Customer_Register_CB(MSDC_AIT_SCSI_CUSTOMER_CB cb);
#endif

#endif //_MMPF_USBVEND_H
