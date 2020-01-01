#if ( USE_SEC_MTP_DEV_FW == 1)
#ifndef USB_MTP_H
#define USB_MTP_H

#include "mmpf_usbvend.h"

extern MMPF_OS_FLAGID          MTP_Flag;
#define  MTP_FLAG_BULKOUT_DONE          0x00000001
#define  MTP_FLAG_BULKIN_DONE           0x00000002
#define  MTP_FLAG_CANCELREQUEST         0x00000004
#define  MTP_FLAG_EVENT_DONE            0x00000008


// PTP Response Codes
#define PTP_RC_UNDEFINED                                0x2000
#define PTP_RC_OK                                       0x2001
#define PTP_RC_GENERAL_ERROR                            0x2002
#define PTP_RC_Session_Not_Open                         0x2003
#define PTP_RC_INVALID_TRANSACTIONID                    0x2004
#define PTP_RC_OPERATION_NOT_SUPPORTED                  0x2005
#define PTP_RC_PARAMETER_NOT_SUPPORTED                  0x2006
#define PTP_RC_INCOMPLETE_TRANSFER                      0x2007
#define PTP_RC_Invalid_StorageID                        0x2008
#define PTP_RC_Invalid_ObjectHandle                     0x2009
#define PTP_RC_DeviceProp_Not_Supported                 0x200A
#define PTP_RC_Invalid_ObjectFormatCode                 0x200B
#define PTP_RC_STORE_FULL                               0x200C
#define PTP_RC_OBJECT_WRITE_PROTECTED                   0x200D
#define PTP_RC_Store_Read_Only                          0x200E
#define PTP_RC_Access_Denied                            0x200F
#define PTP_RC_NO_THUMBNAIL_PRESENT                     0x2010
#define PTP_RC_SELFTEST_FAILED                          0x2011
#define PTP_RC_PARTIAL_DELETION                         0x2012
#define PTP_RC_Store_Not_Available                      0x2013
#define PTP_RC_Specification_By_Format_Unsupported      0x2014
#define PTP_RC_NO_VALID_OBJECT_INFO                     0x2015
#define PTP_RC_Invalid_Code_Format                      0x2016
#define PTP_RC_UNKNOWN_VENDOR_CODE                      0x2017
#define PTP_RC_CAPTURE_ALREADY_TERMINATED               0x2018
#define PTP_RC_Device_Busy                              0x2019
#define PTP_RC_Invalid_ParentObject                     0x201A
#define PTP_RC_INVALID_DEV_PROP_FORMAT                  0x201B
#define PTP_RC_INVALID_DEV_PROP_VALUE                   0x201C
#define PTP_RC_Invalid_Parameter                        0x201D
#define PTP_RC_Session_Already_Open                     0x201E
#define PTP_RC_TRANSACTION_CANCELED                     0x201F
#define PTP_RC_Specification_of_Destination_Unsupported 0x2020


typedef enum _AIT_MTP_STATE{
    MTP_INIT=0,
    MTP_BULKOUT_GOING,
    MTP_BULKOUT_DONE,
    MTP_BULKIN_GOING,
    MTP_BULKIN_DONE,
    MTP_EVENT_DONE,
    MTP_CANCELREQUEST,
    MTP_IDLE
}AIT_MTP_STATE;

typedef struct _MTP_STILL_IMAGE_CLASS_CB
{
	void (* ResetDevice)(void);
	int (* GetDeviceStatus)(void);
	void (* MtpSetStatus)(char status);
	int (* GetCancelStatus)(void);
}MTP_STILL_IMAGE_CLASS_CB;


void MMPF_MTP_ResetDevice(void);
void MMPF_MTP_BulkOutDone(void);
void MMPF_MTP_BulkInDone(void);
void MMPF_MTP_InterruptInDone(void);
void MMPF_MTP_CancelRequest(void);
MMP_UBYTE MMPF_MTP_InitTransfer(void);
MMP_UBYTE MMPF_MTP_IsDataAvailable(void);
void MMPF_MTP_WakeupMTPTask(void);
MMP_UBYTE MMPF_MTP_TriggerRXTransfer(void * pBuffer, MMP_ULONG size);
MMP_UBYTE MMPF_MTP_TriggerTXTransfer(void * pBuffer, MMP_ULONG size);
MMP_UBYTE MMPF_MTP_TriggerEventTx(void * pBuffer, MMP_ULONG size);
void MMPF_MTP_Disconnect(void);
void    MMPF_MTP_StallRx(void);
void    MMPF_MTP_StallTx(void);
void    MMPF_MTP_UnStallRx(void);
void    MMPF_MTP_UnStallTx(void);
MMP_USHORT MMPF_MTP_GetDeviceState(void);
MMP_USHORT MMPF_MTP_GetRxFIFODataLength(void);


		#if 0 // for IDE function name list by section
		void _____MTP_DRIVER_HEADER_START_____(){}
		#endif
#endif
#else
#ifndef USB_MTP_H
#define USB_MTP_H

#include "mmpf_usbvend.h"

//MMPF_OS_FLAGID          MTP_Flag;
#define  MTP_FLAG_BULKOUT_DONE          0x00000001
#define  MTP_FLAG_BULKIN_DONE           0x00000002
#define  MTP_FLAG_CANCELREQUEST         0x00000004
#define  MTP_FLAG_EVENT_DONE            0x00000008

#define MTP_DBG_msg1
#define MTP_DBG_msg2
//#define MTP_WHILE1_DEBUG

#define WPD_StorageType_SD

#define NAND_FLASH  0
#define SD_CARD     1
#define DirCntMax   1//100
#define FileCntMax  1//400

#if 0
#define DRMdatabufStartAddr (0x3E000+0x400)//at pcsync host out buf
#define DealRxDataTmpAddr (0x3E000+0x400)//at pcsync host out buf
#define MetadataBufAddr (0x3E000+0x800)//size 0x200
#else

extern MMP_ULONG DRMdatabufStartAddr;
extern MMP_ULONG DealRxDataTmpAddr;
extern MMP_ULONG MetadataBufAddr;
/*
#define MTPBUFEND 0x2D320//must to be refer host side PcsyncOutBUFStart address
#define DRMdatabufStartAddr (MTPBUFEND+0x400)
#define DealRxDataTmpAddr (MTPBUFEND+0x400)
//#define MetadataBufAddr (MTPBUFEND+0x800)//size 0x200
#define MetadataBufAddr (MTPBUFEND)//size = 512bytes(per prop data) x 6 (MaxPropCntInInfoMem) = 3K
*/
#endif

#define Payload_bit8    1
#define Payload_bit16   2
#define Payload_bit32   4

//for FileIndexList[],FileIndexParentList[],DirIndexList[],DirIndexParentList[]
#define SD_ParentID     0xFFF1
#define NAND_ParentID   0xFFF0
#define isDeleted       0xFFFFFFFF



//global bool flag mask
#define mask_obj_Deleted            0x1
#define mask_prop_NonConsumable     0x2

#define MaxFullPathLen 265
#define MaxFilenameLen 265

#define PTP_StorageID_SD    0x00010001
#define PTP_StorageID_NAND  0x00020001

//for user define MTP directory architecture
#define NC_0_RootDepth  1//PlaysForSure
#define NC_1_RootDepth  2//Data

#define mtp_SN_StrLen 16


#define MTP_RootString_SD   ("SD:\\")   //must be indicated by mtp_fs_io.h
#define MTP_RootString_NAND ("SM:\\")   //must be indicated by mtp_fs_io.h


#define PTP_UNKNOWNBLOCK            (0x0000)
#define PTP_COMMANDBLOCK			(0x0001)
#define PTP_DATABLOCK				(0x0002)
#define PTP_RESPONSEBLOCK			(0x0003)
#define PTP_EVENTBLOCK				(0x0004)

// PTP Operation Code
#define PTP_OC_Undefined                    0x1000
#define PTP_OC_GetDeviceInfo                0x1001
#define PTP_OC_OpenSession                  0x1002
#define PTP_OC_CloseSession                 0x1003
#define PTP_OC_GetStorageIDs                0x1004
#define PTP_OC_GetStorageInfo               0x1005
#define PTP_OC_GetNumObjects                0x1006
#define PTP_OC_GetObjectHandles             0x1007
#define PTP_OC_GetObjectInfo                0x1008
#define PTP_OC_GetObject                    0x1009
#define PTP_OC_GetThumb                     0x100A
#define PTP_OC_DeleteObject                 0x100B
#define PTP_OC_SendObjectInfo               0x100C
#define PTP_OC_SendObject                   0x100D
#define PTP_OC_InitialCapture               0x100E
#define PTP_OC_FormatStore                  0x100F
#define PTP_OC_ResetDevice                  0x1010
#define PTP_OC_SelfTest                     0x1011
#define PTP_OC_SetObjectProtection          0x1012
#define PTP_OC_PowerDown                    0x1013
#define PTP_OC_GetDevicePropDesc            0x1014
#define PTP_OC_GetDevicePropValue           0x1015
#define PTP_OC_SetDevicePropValue           0x1016
#define PTP_OC_ResetDevicePropValue         0x1017
#define PTP_OC_TerminateOpenCapture         0x1018
#define PTP_OC_MoveObject                   0x1019
#define PTP_OC_CopyObject                   0x101A
#define PTP_OC_GetPartialObject             0x101B
#define PTP_OC_InitiateOpenCapture          0x101C

//MTP Operation Code
#define MTP_OC_Undefined                    0x9800
#define MTP_OC_GetObjectPropsSupported      0x9801
#define MTP_OC_GetObjectPropDesc            0x9802
#define MTP_OC_GetObjectPropValue           0x9803
#define MTP_OC_SetObjectPropValue           0x9804
#define MTP_OC_GetObjectReferences          0x9810
#define MTP_OC_SetObjectReferences          0x9811

//MTP Enhance operation
#define MTPe_OC_GetObjectPropList           0x9805
#define MTPe_OC_SetObjectPropList           0x9806
#define MTPe_OC_GetInterdependentPropDesc   0x9807
#define MTPe_OC_SendObjectPropList          0x9808
#define MTPe_OC_WMPMetadataRoundTrip        0x9201

//MTP extension operation for DRM
#define DRM_OC_GetSecureTimeChallenge       0x9101
#define DRM_OC_SetSecureTimeResponse        0x9102
#define DRM_OC_SetLicenseResponse           0x9103
#define DRM_OC_GetSyncList                  0x9104
#define DRM_OC_SendMeterChallengeQuery      0x9105
#define DRM_OC_GetMeterChallenge            0x9106
#define DRM_OC_SetMeterResponse             0x9107
#define DRM_OC_CleanDataStore               0x9108
#define DRM_OC_GetLicenseState              0x9109
#define DRM_OC_SendWMDRMPDCommand           0x910A
#define DRM_OC_SendWMDRMPDRequest           0x910B


// PTP Response Codes
#define PTP_RC_UNDEFINED                                0x2000
#define PTP_RC_OK                                       0x2001
#define PTP_RC_GENERAL_ERROR                            0x2002
#define PTP_RC_Session_Not_Open                         0x2003
#define PTP_RC_INVALID_TRANSACTIONID                    0x2004
#define PTP_RC_OPERATION_NOT_SUPPORTED                  0x2005
#define PTP_RC_PARAMETER_NOT_SUPPORTED                  0x2006
#define PTP_RC_INCOMPLETE_TRANSFER                      0x2007
#define PTP_RC_Invalid_StorageID                        0x2008
#define PTP_RC_Invalid_ObjectHandle                     0x2009
#define PTP_RC_DeviceProp_Not_Supported                 0x200A
#define PTP_RC_Invalid_ObjectFormatCode                 0x200B
#define PTP_RC_STORE_FULL                               0x200C
#define PTP_RC_OBJECT_WRITE_PROTECTED                   0x200D
#define PTP_RC_Store_Read_Only                          0x200E
#define PTP_RC_Access_Denied                            0x200F
#define PTP_RC_NO_THUMBNAIL_PRESENT                     0x2010
#define PTP_RC_SELFTEST_FAILED                          0x2011
#define PTP_RC_PARTIAL_DELETION                         0x2012
#define PTP_RC_Store_Not_Available                      0x2013
#define PTP_RC_Specification_By_Format_Unsupported      0x2014
#define PTP_RC_NO_VALID_OBJECT_INFO                     0x2015
#define PTP_RC_Invalid_Code_Format                      0x2016
#define PTP_RC_UNKNOWN_VENDOR_CODE                      0x2017
#define PTP_RC_CAPTURE_ALREADY_TERMINATED               0x2018
#define PTP_RC_Device_Busy                              0x2019
#define PTP_RC_Invalid_ParentObject                     0x201A
#define PTP_RC_INVALID_DEV_PROP_FORMAT                  0x201B
#define PTP_RC_INVALID_DEV_PROP_VALUE                   0x201C
#define PTP_RC_Invalid_Parameter                        0x201D
#define PTP_RC_Session_Already_Open                     0x201E
#define PTP_RC_TRANSACTION_CANCELED                     0x201F
#define PTP_RC_Specification_of_Destination_Unsupported 0x2020

// MTP Response Codes
#define MTP_RC_Undefined                            0xA800
#define MTP_RC_Invalid_ObjectPropCode               0xA801
#define MTP_RC_Invalid_ObjectProp_Format            0xA802
#define MTP_RC_Invalid_ObjectProp_Value             0xA803
#define MTP_RC_Invalid_ObjectReference              0xA804
#define MTP_RC_Invalid_Dataset                      0xA806
#define MTP_RC_Specification_By_Group_Unsupported   0xA808
#define MTP_RC_Object_Too_Large                     0xA809
#define MTP_RC_ObjectProp_Not_Supported             0xA80A


// PTP Object Format Codes
#define PTP_OF_UNDEFINED                                0x3000
#define PTP_OF_ASSOCIATION                              0x3001
#define PTP_OF_SCRIPT                                   0x3002
#define PTP_OF_EXECUTABLE                               0x3003
#define PTP_OF_TEXT                                     0x3004
#define PTP_OF_HTML                                     0x3005
#define PTP_OF_DPOF                                     0x3006
#define PTP_OF_AIFF                                     0x3007
#define PTP_OF_WAV                                      0x3008
#define PTP_OF_MP3                                      0x3009
#define PTP_OF_AVI                                      0x300A
#define PTP_OF_MPEG                                     0x300B
#define PTP_OF_ASF                                      0x300C
#define PTP_OF_QT                                       0x300D
#define PTP_OF_UNDEFINED_IMAGE                          0x3800
#define PTP_OF_JPEG_EXIF                                0x3801
#define PTP_OF_TIFF_EP                                  0x3802
#define PTP_OF_FLASHPIX                                 0x3803
#define PTP_OF_BMP                                      0x3804
#define PTP_OF_CIFF                                     0x3805
#define PTP_OF_RSVD1                                    0x3806
#define PTP_OF_GIF                                      0x3807
#define PTP_OF_JFIF                                     0x3808
#define PTP_OF_PCD                                      0x3809
#define PTP_OF_PICT                                     0x380A
#define PTP_OF_PNG                                      0x380B
#define PTP_OF_RSVD2                                    0x380C
#define PTP_OF_TIFF                                     0x380D
#define PTP_OF_TIFF_IT                                  0x380E
#define PTP_OF_JP2                                      0x380F
#define PTP_OF_JPX                                      0x3810
// MTP Object Format Codes
#define MTP_OF_Undefined_Firmware               0xB802
#define MTP_OF_Windows_Image_Format             0xB881
#define MTP_OF_Undefined_Audio                  0xB900
#define MTP_OF_WMA                              0xB901
#define MTP_OF_OGG                              0xB902
#define MTP_OF_Undefined_Video                  0xB980
#define MTP_OF_WMV                              0xB981
#define MTP_OF_MP4_Container                    0xB982
#define MTP_OF_Undefined_Collection             0xBA00
#define MTP_OF_Abstract_Multimedia_Album        0xBA01
#define MTP_OF_Abstract_Image_Album             0xBA02
#define MTP_OF_Abstract_Audio_Album             0xBA03
#define MTP_OF_Abstract_Video_Album             0xBA04
#define MTP_OF_Abstract_Audio_Video_Playlist    0xBA05
#define MTP_OF_Abstract_Contact_Group           0xBA06
#define MTP_OF_Abstract_Message_Folder          0xBA07
#define MTP_OF_Abstract_Chaptered_Production    0xBA08
#define MTP_OF_WPL_Playlist                     0xBA10
#define MTP_OF_M3U_Playlist                     0xBA11
#define MTP_OF_MPL_Playlist                     0xBA12
#define MTP_OF_ASX_Playlist                     0xBA13
#define MTP_OF_PLS_Playlist                     0xBA14
#define MTP_OF_Undefined_Document               0xBA80
#define MTP_OF_Abstract_Document                0xBA81
#define MTP_OF_Undefined_Message                0xBB00
#define MTP_OF_Abstract_Message                 0xBB01
#define MTP_OF_Undefined_Contact                0xBB80
#define MTP_OF_Abstract_Contact                 0xBB81
#define MTP_OF_vCard_2                          0xBB82
#define MTP_OF_vCard_3                          0xBB83
#define MTP_OF_Undefined_Calender_Item          0xBE00
#define MTP_OF_Abstract_Calender_Item           0xBE01
#define MTP_OF_vCalendar_1                      0xBE02
#define MTP_OF_vCalendar_2                      0xBE03
#define MTP_OF_Undefined_Windows_Executable     0xBE80



// PTP Event Codes
#define PTP_EC_UNDEFINED                        0x4000
#define PTP_EC_CANCEL_TRANSACTION               0x4001
#define PTP_EC_OBJECT_ADDED                     0x4002
#define PTP_EC_OBJECT_REMOVED                   0x4003
#define PTP_EC_StoreAdded                       0x4004
#define PTP_EC_StoreRemoved                     0x4005
#define PTP_EC_DEV_PRPTP_OC_CHANGED             0x4006
#define PTP_EC_OBJECT_INFO_CHANGED              0x4007
#define PTP_EC_DEV_INFO_CHANGED                 0x4008
#define PTP_EC_REQUEST_OBJECT_TRANSFER          0x4009
#define PTP_EC_STORE_FULL                       0x400A
#define PTP_EC_DEV_RESET                        0x400B
#define PTP_EC_STORAGE_INFO_CHANGED             0x400C
#define PTP_EC_CAPTURE_COMPLETE                 0x400D
#define PTP_EC_UNREPORTED_STATUS                0x400E
// MTP Event Codes
#define MTP_EC_Undefined                        0xB800
#define MTP_EC_ObjectPropChanged                0xB801
#define MTP_EC_ObjectPropDescChanged            0xB802
#define MTP_EC_ObjectReferencesChanged          0xB803
#define MTP_EC_DevicePropDescChanged            0xB804


// PTP Device Prop Codes
#define PTP_DC_UNDEFINED                        0x5000
#define PTP_DC_BatteryLevel                     0x5001
#define PTP_DC_FUNCTIONAL_MODE                  0x5002
#define PTP_DC_IMAGE_SIZE                       0x5003
#define PTP_DC_COMPRESSION_SETTING              0x5004
#define PTP_DC_WHITE_BALANCE                    0x5005
#define PTP_DC_RGB_GAIN                         0x5006
#define PTP_DC_FNUMBER                          0x5007
#define PTP_DC_FOCAL_LENGTH                     0x5008
#define PTP_DC_FOCUS_DISTANCE                   0x5009
#define PTP_DC_FOCUS_MODE                       0x500A
#define PTP_DC_EXPOSURE_METERING_MODE           0x500B
#define PTP_DC_FLASH_MODE                       0x500C
#define PTP_DC_EXPOSURE_TIME                    0x500D
#define PTP_DC_EXPOSURE_PROGRAM_MODE            0x500E
#define PTP_DC_EXPOSURE_INDEX                   0x500F
#define PTP_DC_EXPOSURE_BIAS_COMPENSATION       0x5010
#define PTP_DC_DATE_TIME                        0x5011
#define PTP_DC_CAPTURE_DELAY                    0x5012
#define PTP_DC_STILL_CAPTURE_MODE               0x5013
#define PTP_DC_CONTRAST                         0x5014
#define PTP_DC_SHARPNESS                        0x5015
#define PTP_DC_DIGITAL_ZOOM                     0x5016
#define PTP_DC_EFFECT_MODE                      0x5017
#define PTP_DC_BURST_NUMBER                     0x5018
#define PTP_DC_BURST_INTERVAL                   0x5019
#define PTP_DC_TIMELAPSE_NUMBER                 0x501A
#define PTP_DC_TIMELAPSE_INTERVAL               0x501B
#define PTP_DC_FOCUS_METERING_MODE              0x501C
#define PTP_DC_UPLOAD_URL                       0x501D
#define PTP_DC_ARTIST                           0x501E
#define PTP_DC_COPYRIGHT_INFO                   0x501F
// MTP Device Prop Codes
#define MTP_DC_SynchronizationPartner           0xD401
#define MTP_DC_DeviceFriendlyName               0xD402
#define MTP_DC_DeviceIcon                       0xD405
//DRM Device Prop Codes
#define DRM_DC_SecureTime                       0xD101
#define DRM_DC_DeviceCertificate                0xD102

// MTP Object Property Code
#define MTP_BPC_StorageID                           0xDC01
#define MTP_BPC_ObjectFormat                        0xDC02
#define MTP_BPC_ProtectionStatus                    0xDC03
#define MTP_BPC_ObjectSize                          0xDC04
#define MTP_BPC_AssociationType                     0xDC05
#define MTP_BPC_AssociationDesc                     0xDC06
#define MTP_BPC_ObjectFileName                      0xDC07
#define MTP_BPC_DateCreated                         0xDC08
#define MTP_BPC_DateModified                        0xDC09
#define MTP_BPC_Keywords                            0xDC0A
#define MTP_BPC_ParentObject                        0xDC0B
#define MTP_BPC_PersistentUniqueObjectIdentifier    0xDC41
#define MTP_BPC_SyncID                              0xDC42
#define MTP_BPC_PropertyBag                         0xDC43
#define MTP_BPC_Name                                0xDC44
#define MTP_BPC_CreatedBy                           0xDC45
#define MTP_BPC_Artist                              0xDC46
#define MTP_BPC_DateAuthored                        0xDC47
#define MTP_BPC_Description                         0xDC48
#define MTP_BPC_URL_Reference                       0xDC49
#define MTP_BPC_LanguageLocale                      0xDC4A
#define MTP_BPC_CopyrightInformation                0xDC4B
#define MTP_BPC_Source                              0xDC4C
#define MTP_BPC_OriginLocation                      0xDC4D
#define MTP_BPC_DateAdded                           0xDC4E
#define MTP_BPC_Non_Consumable                      0xDC4F
#define MTP_BPC_Corrupt_Unplayable                  0xDC50
#define MTP_BPC_RepresentativeSampleFormat          0xDC81
#define MTP_BPC_RepresentativeSampleSize            0xDC82
#define MTP_BPC_RepresentativeSampleHeight          0xDC83
#define MTP_BPC_RepresentativeSampleWidth           0xDC84
#define MTP_BPC_RepresentativeSampleDuration        0xDC85
#define MTP_BPC_RepresentativeSampleData            0xDC86
#define MTP_BPC_Width                               0xDC87
#define MTP_BPC_Height                              0xDC88
#define MTP_BPC_Duration                            0xDC89
#define MTP_BPC_Rating                              0xDC8A
#define MTP_BPC_Track                               0xDC8B
#define MTP_BPC_Genre                               0xDC8C
#define MTP_BPC_Credits                             0xDC8D
#define MTP_BPC_Lyrics                              0xDC8E
#define MTP_BPC_SubscriptionContentID               0xDC8F
#define MTP_BPC_ProducedBy                          0xDC90
#define MTP_BPC_UseCount                            0xDC91
#define MTP_BPC_SkipCount                           0xDC92
#define MTP_BPC_LastAccessed                        0xDC93
#define MTP_BPC_ParentalRating                      0xDC94
#define MTP_BPC_MetaGenre                           0xDC95
#define MTP_BPC_Composer                            0xDC96
#define MTP_BPC_EffectiveRating                     0xDC97
#define MTP_BPC_Subtitle                            0xDC98
#define MTP_BPC_OriginalReleaseDate                 0xDC99
#define MTP_BPC_AlbumName                           0xDC9A
#define MTP_BPC_AlbumArtist                         0xDC9B
#define MTP_BPC_Mood                                0xDC9C
#define MTP_BPC_DRM_Status                          0xDC9D
#define MTP_BPC_SubDescription                      0xDC9E
#define MTP_BPC_IsCropped                           0xDCD1
#define MTP_BPC_IsColourCorrected                   0xDCD2
#define MTP_BPC_TotalBitRate                        0xDE91
#define MTP_BPC_BitrateType                         0xDE92
#define MTP_BPC_SampleRate                          0xDE93
#define MTP_BPC_NumberOfChannels                    0xDE94
#define MTP_BPC_AudioBitDepth                       0xDE95
#define MTP_BPC_ScanType                            0xDE97
#define MTP_BPC_AudioWAVECodec                      0xDE99
#define MTP_BPC_AudioBitRate                        0xDE9A
#define MTP_BPC_VideoFourCCCodec                    0xDE9B
#define MTP_BPC_VideoBitRate                        0xDE9C
#define MTP_BPC_FramesPerThousandSeconds            0xDE9D
#define MTP_BPC_KeyFrameDistance                    0xDE9E
#define MTP_BPC_BufferSize                          0xDE9F
#define MTP_BPC_EncodingQuality                     0xDEA0

// PTP extended ERROR codes
#define PTP_ERROR_IO                                0x2FF
#define PTP_ERROR_DATA_EXPECTED                     0x2FE
#define PTP_ERROR_RESP_EXPECTED                     0x2FD
#define PTP_ERROR_BADPARAM                          0x2fC
#define PTP_REQ_DATALEN                             16384

// PTP ObjectInfo ProtectionStatus codes
#define PTP_OBJINFO_NO_PROTECTION                   0x0000
#define PTP_OBJINFO_READ_ONLY                       0x0001
#define PTP_OBJINFO_UPLOAD_DONE                     0x0002

// DRM Response Code
#define DRM_REP_OK                              (0x2001)
#define DRM_REP_UNDEFINED                       (0xA100)
#define DRM_REP_WMDRMPD_FAIL                    (0xA101)

//#define SYNCH_PARTENER_STR_LEN                  (0x30)  //Andy--
#define SYNCH_PARTENER_STR_LEN                  (0xFF)//(0x30)	//copy : change max length  Andy++


#define NO_PROTECTION                           (0x0000)
#define READ_ONLY                               (0x0001)
#define READ_ONLY_DATA                          (0x8002)
#define NON_TRANSFER_DATA                       (0x8003)

#define DEFAULTY_SYNCH_PARTENER                 ("Sync Partner")

#define FILE_LIST_INFO_NAME                     ("SD:\\FileListInfo")
#define HDS_NAME                                ("SD:\\jazz1.hds")
#define INFO_FILE_NAME  (0)

#define DELETE_FLAG_MASK (0x01)

#define MTP_MAX_OBJECT  (1500)

#define OBJ_PROPERTY_STR_LEN  (256)
#define MAX_OBJ_REFERENCE_NUM  (400)
#define MAX_FILE_NAME_LEGTH   (260)
typedef struct{
    MMP_USHORT Signature;
    MMP_USHORT FileName[MAX_FILE_NAME_LEGTH+1];

    MMP_ULONG  UniqueIdentifier[4];
    MMP_ULONG  StorageID;
    MMP_ULONG  ObjSize;
    MMP_ULONG  SampleRate;
    MMP_ULONG  AudioWAVECodec;
    MMP_ULONG  UseCount;
    MMP_ULONG  Duration;
    MMP_ULONG  AudioBitRate;
    MMP_USHORT ParentHandle;
    MMP_USHORT FileFmt;
    MMP_USHORT NumberOfChannels;
    MMP_USHORT AssociationType;
    MMP_USHORT NonConsumable;
    MMP_USHORT ProtectionStatus;
    MMP_USHORT Track;
    MMP_USHORT Rating;
    MMP_USHORT ObjReference[MAX_OBJ_REFERENCE_NUM+1];
    MMP_UBYTE  Flag;
    MMP_UBYTE  RoundTrip;
    MMP_USHORT Dummy2[74];

    MMP_USHORT Artist[OBJ_PROPERTY_STR_LEN];
    MMP_USHORT Genre[OBJ_PROPERTY_STR_LEN];
    MMP_USHORT AlbumName[OBJ_PROPERTY_STR_LEN];
    MMP_USHORT Name[OBJ_PROPERTY_STR_LEN];
}FILE_HANDLE;

typedef struct{
    MMP_ULONG  FileInfoFileID;
    MMP_USHORT ObjCnt;
    MMP_USHORT RoundTripHandle[10];
    MMP_USHORT ParentHandle[MTP_MAX_OBJECT];
    MMP_USHORT FileFmt[MTP_MAX_OBJECT];
    MMP_UBYTE  Flag[MTP_MAX_OBJECT];
    FILE_HANDLE ObjectPrp;
    MMP_USHORT CurObjHandle;
}FILE_LIST_INFO;

typedef struct{
    MMP_ULONG ObjCnt;
    MMP_ULONG ObjCntCheck;
    MMP_ULONG MagicNum;
}MTP_OBJECT_LIST_HEADER;

#define MTP_OBJECT_LIST_HEADERSIZE     (sizeof(MTP_OBJECT_LIST_HEADER))

typedef struct{
    MTP_OBJECT_LIST_HEADER ObjHeader;
    MMP_UBYTE Dummy[512-MTP_OBJECT_LIST_HEADERSIZE];
}FILE_LIST_HEADER;

#define FILE_LIST_MAGIC_NUM     0xAA5555AA


//Phase step
#define _None       0
#define O_Get       1
#define O_Drx       2
#define O_Dtx       3
#define O_R         4
#define Drx_rxOut   5
#define Dtx_txOut   6
#define rxOut_R     7
#define txOut_R     8
#define R_Out       9
#define DPS_E_out   10

enum mtp_process_set{
    go_init=0,
    mtpbulkoutdone,
    mtpbulkindone,
    mtpINTindone,
    mtpcancelrequest,
    none_prs,
    mtpbulkoutgoing,
    mtpbulkingoing
};

typedef struct{
    MMP_BYTE    NumChars;
    MMP_BYTE    StringChar[16];
}PTP_String_Struct;


typedef struct{
    MMP_ULONG   ContainerLen;
    MMP_USHORT  ContainerType;
    MMP_USHORT  Code;
    MMP_ULONG   TransactionID;
    MMP_ULONG   Para[5];
}ContainerStruct;

typedef struct{
    MMP_USHORT  Code;
    MMP_ULONG   SesstionID;
    MMP_ULONG   TransactionID;
    MMP_ULONG   Para[5];
}OP_RP_dataset;

typedef struct{
    MMP_USHORT  level;
    MMP_USHORT  DirCnt;
    MMP_USHORT FileCnt;
}PathLvInfo;

typedef struct{
    MMP_UBYTE   NumChar;
    MMP_USHORT  StrChar[MaxFullPathLen];//sync with "MAX_FILE_NAME_LEN" defined in mtp_fs_fat.h
} MtpString;

typedef struct{
    MMP_ULONG       StorageID;
    MMP_USHORT      ObjectFormat;
    MMP_USHORT      ProtectionStatus;
    MMP_ULONG64     ObjectCompressSize;
    // 2bytes Thumb Format
    // 4bytes Thumb CompressSize
    // 4bytes Thumb PixWidth
    // 4bytes Thumb PixHight
    // 4bytes Image PixWidth
    // 4bytes Image PixHight
    // 4bytes Image BitDepth
    MMP_ULONG       ParentObject;
    MMP_USHORT      AssociationType;
    // 4bytes AssociationDesc
    // 4bytes SequenceNumber
    MMP_BYTE        Filename[MaxFilenameLen];
    MMP_BYTE        CaptureDate[19];//"20050101T120101.1"
    MMP_BYTE        ModificationDate[19];//"20050101T120101.1"
    MMP_BYTE        Keywords[20];
    //-----extension info for other functions
    MMP_ULONG       ObjectHandle;
    MtpString   UniFilename;
}ObjectInfoStruct;

typedef struct{
    MMP_USHORT DirFileIdx;//InDirFileList;
    MMP_USHORT hdl;
}emptyHdlstruct;

typedef struct{
    MMP_USHORT      hdl;
    MMP_ULONG       PSUID[2];
    MtpString   lstr;//sync with "MAX_FILE_NAME_LEN" defined in mtp_fs_fat.h
}Del100_LongName;

typedef struct{
    MMP_USHORT  usOpCode;   //Operation Code
    MMP_ULONG   ulPar[5];   //Operation Parameter
}DRM_OC_HANDLE;

typedef struct{
    MMP_UBYTE   *pBufAddr;
    MMP_ULONG   ulTxTotalSize;  //Total Size to be Tx
    MMP_ULONG   ulRxTotalSize;  //Total Size to be Rx
    MMP_USHORT  usTxBufSize;    //Available Tx Buffer size
    MMP_USHORT  usRxDataSize;   //Valid Rx Data size
    MMP_ULONG   ulAlreadyTxSize;//Accumulated TX size
    MMP_ULONG   ulAlreadyRxSize;//Accumulated RX size
}DRM_DATA_HANDLE;

typedef struct{
    MMP_USHORT  usRpCode;   //Response Code
    MMP_ULONG   ulPar[5];   //Responese Parameter
}DRM_RC_HANDLE;

extern void Mtp_DrmProcess(DRM_OC_HANDLE OCHandle,DRM_DATA_HANDLE *pDataHandle,DRM_RC_HANDLE *pRCHandle);

extern MMP_UBYTE mtpFlag_GetDRMData;
extern MMP_BYTE SerialNumberString[16];
extern MMP_UBYTE mtpFlag_isSDexist;
extern MMP_UBYTE mtpFlag_checkStoreafterMtpInit;
extern MMP_UBYTE gflag_OpenSessionReEnumAllObj;
extern OP_RP_dataset curOPinfo,curRPinfo;
extern MMP_UBYTE mtp_H2D_CancelRequset;
extern MMP_USHORT mtp_DevStatus;
extern MMP_UBYTE MTPCurPhase;
extern MMP_ULONG mtpRXbufAddr;
extern MMP_UBYTE mtp_fs_test_on;
extern MMP_UBYTE gflag_Muti_Write;
extern MMP_BYTE gPathTmp[];//for path temp
extern MMP_UBYTE gflag_DelinMainloop;
extern MMP_UBYTE gflag_DelinMainloop_File0_Dir1;
#ifdef P4S_PerformanceTest_100Object //brian060613
extern MMP_UBYTE gflag_PerfTest_100Obj_DelinMain;
extern MMP_UBYTE gflag_PerfTest_100Obj_Del_ON;
#endif
extern MMP_UBYTE MTPprocess;
//brian061025,add for DPS
extern MMP_UBYTE gflag_SessionOpened;
extern MMP_UBYTE mtpTotalStorageNumber;
extern MMP_ULONG ParentHandleTmp;
extern ObjectInfoStruct CurObjInfo;
extern MMP_ULONG FileIndexList[FileCntMax];
extern MMP_USHORT preFileCnt;


#if (SUPPORT_MTP_FUNC==1)||(SUPPORT_DPS_FUNC==1)
extern void mtp_bulk_in_done(MTP_DMA_HANDLE/* DMAHandle*/);
extern void mtp_bulk_out_done(MTP_DMA_HANDLE /*DMAHandle*/);
extern void mtp_interrupt_in_done(MTP_DMA_HANDLE /*DMAHandle*/);
extern void mtp_cancel_request(void);
#endif

extern void mtp_bulk_out(int RxByte);
extern MMP_UBYTE PtpContainerParser(void);
extern void MtpRpInfo2TxBuf(MMP_UBYTE ParaAmt);
extern MMP_ULONG ConPayloadAdd(MMP_ULONG * pt,MMP_ULONG type ,MMP_ULONG val);
extern MMP_ULONG ConPayloadAddString(MMP_ULONG * pt,MMP_UBYTE StrNum,MMP_BYTE * Str);
extern void SendDataAIT2BB(MMP_ULONG size);
extern MMP_UBYTE MtpOPprocess(void);
extern MMP_UBYTE MtpResponsePhase(void);
extern MMP_UBYTE MtpDataPhaseTX(void);
extern void DPSEventTx(MMP_USHORT EventCode,MMP_UBYTE P_Amt,MMP_ULONG P1,MMP_ULONG P2,MMP_ULONG P3);
//extern MMP_ULONG GetTotalObjectHandleNum(void);
extern MMP_ULONG GetPathListIndexNum(void);

extern void mtpGetObjectInfo(MMP_ULONG handle);

extern MMP_USHORT GetObjectFmt(MMP_ULONG handle);
extern void GetObjectFilename(MMP_ULONG handle,MMP_BYTE * filename);
extern MMP_ULONG GetObjectStorageID(MMP_ULONG handle);
extern MMP_ULONG GetObjectDepth(MMP_ULONG handle);
extern MMP_ULONG GetObjectParent(MMP_ULONG handle);
extern MMP_ULONG GetObjectDepthFromTopHdl(MMP_ULONG curHdl,MMP_ULONG topHdl);

extern MMP_ULONG GetDataFromAddr(MMP_UBYTE * pt,MMP_ULONG type ,void* val);

extern void MTPGetDRMDataHandler(void);

//extern MMP_ULONG Num2Char(MMP_ULONG addr,MMP_UBYTE num);
//extern MMP_BYTE * getFullPathbyBufidx(MMP_ULONG idx);
extern MMP_USHORT getFullPathbyBufidx(MMP_ULONG idx,MMP_BYTE *rtpath);
//extern void getLongNamebyBufidx(MMP_ULONG idx,MtpString *unistr);
extern void ShowAllListInfo(void);
//extern void iChildIdxArrayUpadte(MMP_ULONG idx,MMP_USHORT objfmt);
extern void mtpUSBplugoutInRxPahse(void);
extern void MTPInit(void);
extern void Load_dat_2_infoMem(MMP_ULONG handle);
//extern void get_LongName_from_InfoMem(MtpString * UniStr);
extern void get_Meta_from_InfoMem(MMP_USHORT ObjProp, MtpString * UniStr);
extern MMP_ULONG  get_pinpon_addr(MMP_ULONG pre_addr);
extern void get_PUObjID_from_InfoMem(MMP_ULONG* PUObjID);
extern MMP_USHORT del100obj(void);
extern void MtpRpInfo2TxBuf(MMP_UBYTE ParaAmt);
extern void mtpbulkoutdone_process(void );
extern void mtpbulkindone_process(void );
extern void mtpinterruptindone_process(void );
//extern MMP_UBYTE pre_cancel_done(void);
extern void mtpCopyMem2Mem(MMP_ULONG dntaddr,MMP_ULONG srcaddr,MMP_ULONG size);
extern void ptp_ep_config(void);
extern void MtpGetDeviceStatus(MMP_USHORT *status);
extern void mtpcancelrequest_process(void);
extern void MtpTxEvent(MMP_USHORT wEventCode, MMP_ULONG dwPara);
//extern void MtpSetDevicePropertyValue(MMP_ULONG property_code); //Andy--
extern void MtpSetDevicePropertyValue(MMP_ULONG property_code,MMP_ULONG addr_tmp,MMP_ULONG size);  //Andy++
extern void InitFileListInfoFile(void);
extern void EnumObjFromFileListInfo(void);
extern void LoadFileHandleByHandle(MMP_ULONG handle);
extern void UpdateFileHandleByHandle(MMP_ULONG handle,MMP_ULONG wr_list_header);
extern void ChkFileListFile(void);
extern MMP_USHORT GetProptectStatusByHandle(MMP_ULONG handle);
extern void MtpResetDevice(void);
extern void MtpSendObjectInfo(void);
extern MMP_USHORT GetParentPathByHandle(MMP_ULONG handle);
extern void MtpMetaRoundTrip(void);
extern void MtpResetState(void);

#endif

#endif
