//==============================================================================
//
//  File        : ahc_parameter.h
//  Description : INCLUDE File for the AHC parameter definition and data types.
//  Author      :
//  Revision    : 1.0
//
//==============================================================================

#ifndef _AHC_PARAMETER_H_
#define _AHC_PARAMETER_H_

/*===========================================================================
 * Include files
 *===========================================================================*/

#include "ahc_common.h"
//#include "AHC_Config_SDK.h"

/*===========================================================================
 * Macro define
 *===========================================================================*/

#define AHC_STRING_MAX_LENGTH       32
#define AHC_LONG_STRING_MAX_LENGTH  256

#define AHC_AUDIO_PORT_LINEOUT      0x1
#define AHC_AUDIO_PORT_HP           0x2

#define AHC_MENU_FILENAME           "MenuSetting.bin"
#define AHC_ISP_FILENAME            "ISP.bin"
#define AHC_USER_SFBACKUP           (1) // 0:Disable SFUserBackup 1:Enable SFUserBackup

#if(AHC_USER_SFBACKUP)
#define USERCOPYSF2TOSF3            (0x02)
#define USERCOPYSF3TOSF2            (0x03)
#endif

#define READIDX                     (0x01)
#define WRITEIDX                    (0x02)

/*===========================================================================
 * Structure define
 *===========================================================================*/

typedef void AHC_AudioPcmCallBack(INT16 *inbuf, INT16 *outbuf, UINT32 numSamples, UINT16 channels);

typedef struct _AHC_PARAM {

    //Group: SYSTEM
    UINT16 ThumbBKLeft;         //The start region of the background of the thumbnail.
    UINT16 ThumbBKTop;          //The start region of the background of the thumbnail.
    UINT16 ThumbBKWidth;        //The width of the background of the thumbnail.
    UINT16 ThumbBKHeight;       //The height of the background of the thumbnail.
    UINT16 ThumbBKColorYU;      //Color of the background of the thumbnail. (msb:Y, lsb:U)
    UINT16 ThumbBKColorYV;      //Color of the background of the thumbnail. (msb:Y, lsb:V)
    UINT16 ThumbFrameThickH;    //Horizontal thickness of the border around a thumbnail.
    UINT16 ThumbFrameThickV;    //Vertical thickness of the border around a thumbnail.
    UINT16 ThumbDeafaultColorYU;//Default color of the thumbnail thickness. (msb:Y, lsb:U)
    UINT16 ThumbDeafaultColorYV;//Default color of the thumbnail thickness. (msb:Y, lsb:V)
    UINT16 ThumbSelectedColorYU;//Color of the selected thumbnail thickness. (msb:Y, lsb:U)
    UINT16 ThumbSelectedColorYV;//Color of the selected thumbnail thickness. (msb:Y, lsb:V)
    UINT16 ThumbTextColorYU;    //Color of the text on thumbnail. (msb:Y, lsb:U)
    UINT16 ThumbTextColorYV;    //Color of the text on thumbnail. (msb:Y, lsb:V)
    UINT16 ThumbShowIndexEnable;//Enable/disable display the thumbnail's DCF index number on the thumbnail icon.
    UINT16 ThumbDrawMode;       //If 0, then all thumbnails will show up at once. If 1, thumbnails will be displayed one by one until draw completed.
    UINT16 ThumbCompressRatio;  //Set the compression ratio for the main thumbnail.
    UINT16 ThumbBigSize;        //Set the max size of thumbnail but it must be smaller than the size of maker note.
    UINT16 StampOffsetX;        //The horizontal offset from the selected corner to the stamping text.
    UINT16 StampOffsetY;        //The vertical offset from the selected corner to the stamping text.
    UINT16 CardDetectPolarity;  //The polarity for card detection pin.
    UINT16 I2cWaitTimeout;      //The wait time for getting I2C response. 0: no wait, 1~0xFFFF.
    UINT16 ExifAutoTag;         //Select the source of EXIF tag.
                                // 0: EXIF tags update from AHL, it's user's responsibility to set the EXIF via AHC_SetImageEXIF().
                                // 1: Auto tag provide by AIT system.
    UINT16 AgcForFlashStrobe;   //Set the AGC gain for flash strobe. This gain will be applied to sensor before trigger flash.
    UINT16 UseRtc;              //Enable/disable RTC.
    UINT16 MakerNoteSize;       //Define the size of maker note. If 0, system will not add it to the captured JPEG/TIFF.
    UINT16 FlipLR;              //Enable left/right flipping in both preview and capture modes. If enable, the captured image will be flipped.
    UINT16 FlipUD;              //Enable up/down flipping in both preview and capture modes. If enable, the captured image will be flipped.
    UINT16 SensorMaxVideoWidth; //Get the maximum width in sensor preview setting.
    UINT16 SensorMaxStillWidth; //Get the maximum width in sensor still capture setting.
    UINT16 SensorMaxStillHeight;//Get the maximum height in sensor still capture setting.
    UINT16 NightModeAE;         //Perform the night mode exposure in next captured frame.
    UINT16 GrahpicWidth;        //Get the width of current display graphic context.
    UINT16 GrahpicHeight;       //Get the height of current display graphic context.
    UINT16 DisplayFlipLR;       //Enable left/right flipping of display in all modes. This flip will not affect the captured video and image.
    UINT16 DisplayFlipUD;       //Enable up/down flipping of display in all modes. This flip will not affect the captured video and image.
    UINT16 SetVolumeLabel;      //Set a label during media formatting or not. If yes, the label will be added during format operation. The label must be assigned prior to format.
    UINT16 UartWriteBlocking;   //Set and get the status of UART write. 1: Blocking , 2: Non-blocking
    UINT16 UartReadBlocking;    //Set and get the status of UART write. 1: Blocking , 2: Non-blocking
    UINT16 LcdInputON;          //Enable the LCD data and control signal or not. If 0, both data and controls will be set to low and take no effect on LCD.
    UINT16 CheckExifOrientation;//Determine if the image should be displayed according to orientation tag in playback and thumbnail mode.

    UINT16 ImageOrientation;    //0: Disable image orientation. 1~N: Perform the specific orientations.
    UINT16 CaptureMemoryCheck;  //Enable for checking if there has sufficient memory for next shot, if not sufficient, then the transition from capture
                                //to view is delayed to for ensuring the capture completed.
    UINT32 FreeMemoryCheck;     //Get the size of available buffer. User can know how many free bytes can be allocated.
    UINT16 SensorDownSizeResolution;    //Configure the sensor input size of half, quarter and full Resolution. The downsizing is processed on the input sensor data.
                                        //0: Disable    1: Half resolution  2: Quarter resolution

    UINT16 PreviewHalfSizeThresh;//System will downscale the display frame if it exceeds this value. The value is set upon hw blocks's capability.
    UINT16 PreviewQuatSizeThresh;//The purpose is like PreviewHalfSizeThresh, but this parameter performs quarter scale.
    UINT16 RollingFlick;        //Configure current AE algorithm to work on 50Hz/60Hz. Once set, system should choose the correspond exposure setting to avoid the flicker problem.
    UINT16 IgnoreAhlMessage;    //Set to 1 to ignore all AHL messages, instead of keeping the messages, those messages will be dropped.
    UINT16 DpcEnable;           //Enable/disable the functionality of defective pixels correction.

    UINT16 AhlMsgUnblock;       //Unblock the blocked AHL messages. The input of this parameter is an AHL message ID and be blocked previously.

    UINT16 AhlMsgBlock;         //Block the assigned AHL message upon the input ID.
    UINT16 PwmHightimeResolution;//Setup the resolution for high time of PWM and must be set before calling AHC_ConfigPWM().

    UINT16 QuickPreview;        //Enable the quick preview process.
    UINT16 DebugPrintEnable;    //Enable/disable the debug Prints.
    UINT16 QuickCaptureToView;  //Enable/disable the process of capture to view speed up.
    UINT16 StillRawExtraTopLines;//Set the number of extra lines in the top of captured raw buffer. The captured raw will be located with offset of this number of lines.
    UINT16 StillRawExtraBottomLines;//Set the number of extra lines in the bottom of captured raw buffer. The captured raw will be located with offset of this number of lines.
    UINT8  SDInfo[24];          //If SD card inserted and mounted, returns some information.
    UINT32 StabWindowOffset;    //Set the left-top point of the window for video stabilizer.
    UINT32 StabWindowSize;      //Set the size of the window for video stabilizer.
    UINT16 HdSclGpioGroup;      //Specifies the GPIO group for HDMI serial line Scl.
    UINT16 HdSdaGpioGroup;      //Specifies the GPIO group for HDMI serial line SDA.
    UINT16 HdSdaGpioPin;        //Specifies the GPIO pin for HDMI serial line SDA.
    UINT16 HdSclGpioPin;        //Specifies the GPIO pin for HDMI serial line Scl.
    UINT16 CapYuvmanipScl;      //Specifies timing for the callback function of YUV manipulation during image compression process.
                                // 0- Function will be called before thumbnail and QVGA image creation.
                                // 1- Function will be called after the thumbnail/QVGA creation and prior to main image compression.

    UINT32 DisplayBkgColor;     //Set the background color for the default display while there is nothing to show.

    UINT32 MaxCustomMarkerSize; //Set the maximum custom marker size of EXIF.
    UINT16 SensorStillNumOfBits;//Set the number of bits per pixel saved in dram in sensor still mode (8/12/16).
    UINT16 SensorVideoNumOfBits;//Set the number of bits per pixel saved in dram in sensor video mode (8/12/16).

    UINT16 DisplayScaleRatioMethod; //Set the prefer way for display scaling.
                                    //0- Scale default.
                                    //1- Scaler finds out a ratio smaller or equal to the desire ratio.
                                    //2- Scaler finds out a ratio bigger or equal to the desire ratio.
                                    //3- Scaler finds out a ratio that most approximated to the desire ratio.

    UINT16 SeamlessTransitionEnable;//Enable/disable seamless transition between system modes switch. By this feature, the screen won't display the black screen during modes switch.
    //UINT8  Mainboardtype;         // The defined mainboardtype of FW.
    AHC_BOOL DetectFlow;            //DetectFlow enable/disable while boots up.

    //Group: MOVIE
    UINT16 MovieAutoPlay;       //The normal playback of movie should be paused when entering the playback mode.
                                //Set this parameter to let the playback will not be paused and start play automatically.
    UINT32 MovieNumChunks;      //Get the number of chunks of current playing clip.
    UINT32 MovieCurrentChunks;  //Get the current played chunk.
    UINT16 MovieFrameRate;      //Get the frame rate of current playing clip.
    UINT16 MovieSpecailHandle;  //Setup special handles for movie playback.
                                //0- None
                                //1- Skip index table when opening AVI files. With this flag, the fist frame can be displayed faster because system
                                //   won't spend time to load the entire index table which is stored in the tail of the clip.

    UINT32 MovieMaxFileSizeInkb;//Setup the limitation of size in KB for movie record.
    UINT16 MovieNotifyIpbFrameType; //Enable the frame type notification, the information is included in AhlPlayBACK_CURR_CHUNK message. The position is bit 30~31.
                                    //1 - I,  2 - P,  3 - B

    //Group: UI
    UINT16 MenuScreenWidth;     //The width of the screen in menu mode. Can be used for scaling the display in menu mode.
    UINT16 MenuScreenHeight;    //The height of the screen in menu mode. Can be used for scaling the display in menu mode.
    UINT16 JpegDecodeXYThresh;  //Set the threshold for the dimensions width*Height. If current decoding JPEG size exceeds this parameter's value, then the image will be pre-scaled to fit the threshold limitation.

    UINT16 OsdBufferShow;       //Set the ID of Osd buffer and shows it on display.
    UINT16 OsdBufferDraw;       //Set the ID of Osd buffer to draw.
    UINT16 OsdBufferNum;        //Get the number of Osd buffers that currently created.

    UINT16 OsdWidth;            //Get the Osd width in pixels (current layer).
    UINT16 OsdHeight;           //Get the Osd height in pixels (current layer).
    UINT16 DrawFileKeepAspRatio;//Set the option of AHC_DrawFile and ask it keeps the aspect ratio of image.

    UINT16 DisplayRotateEnable; //Enable/disable the display image rotation.
    UINT32 SetTransparentOpaque;//Setup the customized transparent opaque color.
    UINT16 MenuReDraw;          //Setup the menu redraw method. If 1, whole Menu will be drawn at once. That means the menu can be prepared in the background and show it up entirely instead of one-by-one.

    //Group: File & STORAGE
    UINT16 MountFlags;          //Configures the flags for media mount.
                                //0- No flag
                                //1- Remove all empty DCF objects (size=0) during mount.
                                //2- Filter DCF files by date. System will only mount files from the date specified by FilterDcfFilesByDate.
                                //3- Remove all files with the same file number during mount regardless file type.

    UINT32 FilterDcfFilesByDate;//Set the date for media mount filter. If the flag enabled, DCF will mount the files from this assigned date.

    UINT16 AsyncMount;          //Enable/disable asynchronous mount (no wait for DCF completed)
    UINT16 StorageMediaProtectFlags;//Bit mask corresponds to the media number. The specific number of bit in the mask presents the state of write protection.
                                    //If set the specific bit in the mask to 1, the corresponded media will be considered as write-protected.
    UINT16 SdramStorageEnd;     //Set the end of the area allocated for SDRAM file system.
    UINT16 DramDrive;           //Enable/disable the feature of DRAM Drive.
    UINT16 SDCardType;          //This value is grabbed and stored during the SD/MMC mount. AHL can get current card type by this parameter. 0- MMC, 1- SD

    UINT16 MsMedia;             //Select current media for Usb Mass Storage mode. 0- Resident, 1- External
    UINT16 MsWpStatus;          //Read the current status of memory stick (MS) or memory stick Pro (MSPro).
                                //0xFFFF- Access error.
                                //0- MS,Non write-protect.
                                //1- MS,Write-protected.
                                //2- MSPro, Non write-protect.
                                //3- MSPro, write-protected.

    UINT16 QuickFormat;         //Enable/disable quick format. If enabled, system updates only FATs and boot sectors.
    UINT16 QuickMount;          //Enable/disable quick mount. If enabled, system will not scan all blocks during mount.

    UINT16 MediaFatType;        //Set the desired FAT type before mount or read out current mounted FAT type.  FAT12/FAT16/FAT32
    UINT32 CallbackBadBlockEnable;  //If enabled, system will process the assigned callback function to let AHL know that there are too many bad blocks on current media.

    UINT32 CallbackUserDataErr; //If enabled, system will process the assigned callback function to let AHL know that system discovered an error in user data.

    UINT32 CallbackSystemDataErr;//If enabled, system will process the assigned callback function to let AHL know that system discovered an error in system data. Such like root entry or FAT.

    UINT32 CallbackAccessTimeout;//If enabled, system will process the assigned callback function to let AHL handle the timeout during media access.

    UINT16 NoMoreDcfObjs;       //To tell if there are no more available DCF that can be created on current media.

    UINT16 IgnoreIllegalDcfObjs;//If set to enable, system will skip the DCF objects that aren't specified by configured DCF rule.

    UINT16 DcfNumberingMode;    //Select the numbering rule for DCF object creation. If 1, next object will be created upon current highest number

    UINT32 DcfCurrentKey;       //Get current key of DCF objects in a DWORD.
    UINT32 DcfLastKey;          //Get last key of DCF objects in a DWORD.
    UINT16 CurrentDcfObjectCount;//Get the number of DCF objects in current DCF directory.
    UINT16 MaxFilesInDir;       //Specify the maximum number of files in a directory.
    UINT16 MaxDirInRoot;        //Specify the maximum number of Dirs in DCF root.
    UINT32 DcfWindowSize;       //Set the size of mounting widows for DCF.
    UINT16 DcfDelEmpty;         //If set to 1, the directories which include no DCF objects will be deleted.

    UINT16 DcfCountHidden;      //If set to 1, DCF will not count the hidden objects.
    UINT16 DcfAllowUserDirChar; //Allow AHL to setup a specified folder which would out of the configured rule.

    UINT16 DcfAllowUserDirCharAUTO; //Allow AHL saves files according to the Dir specified by DcfAllowUserDirChar after calling AHC_SetNextDcfKey() once.

    UINT8 SetAccessFileName[AHC_LONG_STRING_MAX_LENGTH];    //A full file path for a file would be accessed when some API configures AccessByFileName.

    UINT16 AccessByFileName;    //If enable, the operations which are relevant to file access will use the specified name in SetAccessFileName.

    UINT16 NandECCMode;         //Enable/disable the ECC mode in NAND.
    UINT16 StoreTimeKbps;       //This parameter keeps the previous media writing speed in Kbytes per second.

    UINT8  AudioVolume;         //Get or set current audio volume. This parameter affects digital gain only.

    UINT16 DummyAudioInsert;    //Set the audio data to zero during record if this flag enabled
    //UINT32 WavDataSize;       //Get the size of current playing WAV file.
    //UINT32 WavCurrentOffset;  //Get the current offset of playing WAV file.
    UINT16 AudioRecCutInTail;   //Set the number of millisecond of audio data to be truncated before record completed.
    UINT16 AudioFilterSel;      //Determine which filer will be adopted on audio recording.
    UINT16 AudioPort;           // Set the output port of audio unit.
                                // Bit 0: Speaker ON/OFF
                                // Bit 1: Line Out ON/OFF
                                // Bit 2: Headphone ON/OFF

    UINT16 AudioInGain;         //Set the input gain of audio codec. This value must be set by following the DB range defined inside audio codec.
    UINT16 AudioInDigitalGain;  //Set the input gain of audio codec. This value must be set by following the DB range defined inside audio codec.
    UINT8  AudioOutGain;        //Set the output gain of audio codec. This value must be set by following the DB range defined inside audio codec.

    UINT16 AudioAlcCfg;         //Configure the setting of ALC.
    UINT16 AudioRecMuteInHead;  //Set the number of millisecond of audio data need to be muted during record.

    UINT16 AudioSwapChannel;    //Swapping L and R channel.
    UINT16 AudioPreFilterCB;    //Setup a callback function, it will be called before audio compression during record.

    UINT16 AudioPostFilterCB;   //Setup a callback function, it will be called after audio De-compressed during playback.

    UINT16 AudioForceMono;      //Set to enforce audio output as Mono. For debug and specific cases.

    //Group: Usb
    UINT16 UsbDescVid;          //Set the vendor ID for Usb device descriptor. Set to zero if wants to use the configuration inside resource file.

    UINT16 UsbDescPid;          //Set the product ID for Usb device descriptor. Set to zero if wants to use the configuration inside resource file.

    UINT16 UsbUfiCustomProductIDSel;        //Select the source of UFI custom ID. 0- From resource file.
                                            //1- From the value in UfiInquiryCustomProductID

    UINT8  UsbUfiInquiryCustomProductID[16];    //Set the product ID for Usb UFI INQUIRY operation
    UINT16 UsbUfiCustomVendorIDSel;         //Select the source of UFI custom vendor ID.
                                            //0 - From resource file.  1 - From the value in UfiInquiryCustomVendorID

    UINT8  UsbUfiInquiryCustomVendorID[16]; //Set the vendor ID for Usb UFI INQUIRY operation
    UINT16 UsbUfiCustomRevIDSel;            //Select the source of UFI custom revision ID.
                                            //0-From resource file.
                                            //1-From the value in UfiInquiryCustomRevID

    UINT8  UsbUfiInquiryCustomRevID[16];    //Set the revision ID for Usb UFI INQUIRY operation
    UINT16 UsbSerialDescriptorSel;          //Select the source of Usb serial descriptor string.
    UINT8  UsbSerialDescriptorString[AHC_STRING_MAX_LENGTH];    //Set the Usb serial descriptor string.
    UINT8  UsbManufactoryDescriptorString[AHC_STRING_MAX_LENGTH];   //Set the Usb manufactory descriptor string.
    UINT16 UsbManufactoryDescStringSel;     //Select the source of Usb manufactory descriptor string.
    UINT16 UsbProductDescStringSel;         //Select the source of Usb product descriptor string.
    UINT8  UsbProductDescriptorString[AHC_STRING_MAX_LENGTH];   //Set the Usb product descriptor string.
    UINT16 UsbDescDevReleaseNum;            //Set the 'bcdDevice' value in the Usb standard device descriptor.

    UINT16 DpofCurrentStatus;               //Get the status (error code) of DPOF operation.
    UINT16 DpofExpectFileSize;              //Set the expected DPOF file size in KB
    UINT16 AudioOverUsb;                    //Set the audio supported in Usb. 0- Not support
    UINT16 RegisterMSWriteCallback;         //Set a callback function to be triggered during data writing under Usb mass-storage mode.

    UINT8  PtpManufactoryString[AHC_STRING_MAX_LENGTH]; //Keeps the manufacturer string of DeviceInfor.
    UINT8  PtpModelString[AHC_STRING_MAX_LENGTH];       //Keeps the model string of DeviceInfor.
    UINT8  PtpVersionString[AHC_STRING_MAX_LENGTH];     //Keeps the version string of DeviceInfor.
    UINT8  PtpSerialNumString[AHC_STRING_MAX_LENGTH];   //Keeps the serial number string of DeviceInfor.
    UINT32 PtpUsbMaxDataLen;    //Set the maximum data length of Usb PTP standard.
    UINT32 PtpUsbDbSize;        //Set the size of PTP database.
    UINT8  DpsVendorNameString[AHC_STRING_MAX_LENGTH];  //Keeps the vendor name of response to configurePrintService (DPS Command)
    UINT8  DpsProductNameString[AHC_STRING_MAX_LENGTH]; //Keeps the product name of response to configurePrintService (DPS Command)
    UINT8  DpsVersion[AHC_STRING_MAX_LENGTH];           //Keeps the dpsVersions of response to configurePrintService (DPS Command)

    UINT32 DpsSerialNumber;     //Keeps the serialoNo of response to configurePrintService (DPS Command)

    UINT16 DpsVendorSpecificVer[AHC_STRING_MAX_LENGTH]; //Keeps the vendorSpecificVersoin of response to ConfigurePrintService.(DPS Command)

    UINT16 DpsExtCapFlag;       //Set or get the extended capability flag of printer configuration.

    UINT16 UsbDeviceSpeed;      // Set or get the speed of Usb device. To read, Usb must be disconnected.
                                //0- Usb FULL Speed
                                //1- Usb HIGH Speed

    UINT16 UsbMsDetectReQ;      //Enable/disable detetion of device connected to Usb, if Devices connected to GPIO then a internal detection must be done.

    //Group: Sequential Still Capture
    UINT16 SeqCaptureProfile;   //Decides the profiled sequence for capture.
    UINT16 SeqCaptureImages;    //Number of images is going to be captured.

    //Group: Image Quality
    UINT16 AEUseCustAlg;        //Enable to use customer AE algorithm and bypass the system AE.
    UINT16 AwbConvergenceThreshold; //The percentage of AWB convergence.
    UINT16 AEMaxStep;           //The maximum EV entry to move in a step. This affects the AE convergent speed.

    //Group: Calibration
    UINT16 WBCalibAreaStartX;   //Start X of the white balance calibration area.
    UINT16 WBCalibAreaStartY;   //Start Y of the white balance calibration area.

    //Group: JPEG
    UINT32 JpegDecodeWidth;
    UINT32 JpegDecodeHeight;

    //GROUT: ADUIO
    UINT8  AudioVolumeDB;       //Audio Playback Volume in DB: 0~96

    //GROUP: LCD
    AHC_BOOL LCDSataus;

    //GROUP: STROBE
    #if (ENABLE_STROBE)
    AHC_BOOL bCalculated;
    UINT32 ulCalculatedNumber;

    AHC_BOOL bPreFlash;
    UINT32 ulPreFlashNumber;
    UINT32 ulWaitPreFlashTime;///<(us)
    UINT32 ulPreFlashTime;///<(us)
    UINT32 ulTimeBetweenTwoFlash;///<(us)

    AHC_BOOL bMainFlash;
    UINT32 ulWaitMainFlashTime;///<(us)
    UINT32 ulMainFlashTime;///<(us)
    #endif

    #if (ENABLE_MECHANICAL_SHUTTER)
    AHC_BOOL bMechanicalShutter;
    UINT32 ulMechanicalShutterTime;
    #endif

    UINT32 ulAdasFlags;       //Parameters to check if ADAS features are enabled or not. Refer to AHC_ADAS_PARAM_ID.

} AHC_PARAM;

typedef struct _AHC_ISP_PARAM
{
    UINT32    CheckSum;
    UINT16    Version;
    UINT16    TurnkeyFwMajorVersion;
    UINT16    TurnkeyFwMediumVersion;
    UINT16    TurnkeyFwMinorVersion;

    UINT8     LsCsData[9778];   //LS and CS calibration value;
    INT16     INFPos[24]  ;     //INFPOS calibration value;
    UINT16    AeCali[6]    ;    //AE calibration value
    INT32     AwbData[18]  ;    //AWB calibration value;

    INT16     FocusMotorAddiShift;  // additional shift for Focus motor
}AHC_ISP_PARAM;

typedef struct _AHC_MEMORY_LOCATION
{
    UINT32 ulLocationAddr;
    UINT32 ulSize;
} AHC_MEMORY_LOCATION;

/*===========================================================================
 * Enum define
 *===========================================================================*/

typedef enum _AHC_PARAM_ID {
    PARAM_ID_NONE = 0x0000,

    //Group: SYSTEM
    PARAM_ID_STAMP_OFFSET_X,
    PARAM_ID_STAMP_OFFSET_Y,
    PARAM_ID_CARD_DETECT_POLARITY,
    PARAM_ID_I2C_WAIT_TIMEOUT,
    PARAM_ID_EXIF_AUTO_TAG,
    //PARAM_ID_TIMER_ID,
    PARAM_ID_AGC_FOR_FLASH_STROBE,
    PARAM_ID_USE_RTC,
    PARAM_ID_MAKER_NOTE_SIZE,
    PARAM_ID_FLIP_LR,
    PARAM_ID_FLIP_UD,
    PARAM_ID_SENSOR_MAX_VIDEO_WIDTH = 0x001E,
    PARAM_ID_SENSOR_MAX_STILL_WIDTH = 0x0020,
    PARAM_ID_SENSOR_MAX_STILL_HEIGHT,
    PARAM_ID_NIGHT_MODE_AE,
    PARAM_ID_GRAPHIC_WIDTH,
    PARAM_ID_GRAPHIC_HEIGHT,
    PARAM_ID_DISPLAY_FLIP_LR,
    PARAM_ID_DISPLAY_FLIP_UD,
    PARAM_ID_SET_VOLUME_LABEL,
    PARAM_ID_UART_WRITE_BLOCKING,
    PARAM_ID_UART_READ_BLOCKING,
    PARAM_ID_CHECK_EXIF_ORIENTATION,
    PARAM_ID_IMAGE_ORIENTATION,
    PARAM_ID_CAPTURE_MEMORY_CHECK,
    PARAM_ID_FREE_MEMORY_CHECK,
    PARAM_ID_SENSOR_DOWNSIZE_RESOLUTION,
    PARAM_ID_PREVIEW_HALF_SIZE_THRESH = 0x0030,
    PARAM_ID_PREVIEW_QUAT_SIZE_THRESH,
    PARAM_ID_ROLLING_FLICK,
    PARAM_ID_IGNORE_AHL_MESSAGE,
    PARAM_ID_DPC_ENABLE,
    PARAM_ID_AHL_MSG_UNBLOCK,
    PARAM_ID_AHL_MSG_BLOCK,
    PARAM_ID_PWM_HIGHTIME_RESOLUTION,
    PARAM_ID_QUICK_PREVIEW,
    PARAM_ID_DEBUG_PRINT_ENABLE,
    PARAM_ID_QUICK_CAPTURE_TO_VIEW,
    PARAM_ID_STILL_RAW_EXTRA_TOP_LINES,
    PARAM_ID_STILL_RAW_EXTRA_BOTTOM_LINES,
    PARAM_ID_SD_INFO,
    PARAM_ID_STAB_WINDOW_OFFSET,
    PARAM_ID_STAB_WINDOW_SIZE,
    PARAM_ID_HD_SCL_GPIO_GROUP = 0x0040,
    PARAM_ID_HD_SDA_GPIO_GROUP,
    PARAM_ID_HD_SDA_GPIO_PIN,
    PARAM_ID_HD_SCL_GPIO_PIN,
    PARAM_ID_CAP_YUVMANIP_SCL,
    PARAM_ID_DISPLAY_BKG_COLOR,
    PARAM_ID_MAX_CUSTOM_MARKER_SIZE,
    PARAM_ID_SENSOR_STILL_NUM_OF_BITS,
    PARAM_ID_SENSOR_VIDEO_NUM_OF_BITS,
    PARAM_ID_DISPLAY_SCALE_RATIO_METHOD = 0x0049,
    PARAM_ID_SEAMLESS_TRANSITION_ENABLE = 0x004A,
    PARAM_ID_MAINBOARD_TYPE = 0x004B,
    PARAM_ID_ENABLE_DETECT_FLOW = 0x004C,

    //Group: MOVIE
    PARAM_ID_MOVIE_AUTO_PLAY = 0x004D,
    PARAM_ID_MOVIE_FRAME_RATE,
    PARAM_ID_MOVIE_MAX_FILESIZE_INKB,
    PARAM_ID_ADAS,

    //Group: UI
    PARAM_ID_OSD_WIDTH = 0x005A,
    PARAM_ID_OSD_HEIGHT,
    PARAM_ID_DRAW_FILE_KEEP_ASP_RATIO,
    PARAM_ID_DISPLAY_ROTATE_ENABLE,

    //Group: FILE & STORAGE
    PARAM_ID_MOUNT_FLAGS = 0x0060,
    PARAM_ID_FILTER_DCF_FILES_BY_DATE,
    PARAM_ID_ASYNC_MOUNT,
    PARAM_ID_STORAGE_MEDIA_PROTECT_FLAGS,
    PARAM_ID_SDRAM_STORAGE_END,
    PARAM_ID_DRAM_DRIVE,
    PARAM_ID_SD_CARD_TYPE,
    PARAM_ID_MS_MEDIA,
    PARAM_ID_MS_WP_STATUS,
    PARAM_ID_QUICK_FORMAT,
    PARAM_ID_QUICK_MOUNT,
    PARAM_ID_MEDIA_FAT_TYPE,
    PARAM_ID_CALLBACK_BAD_BLOCK_ENABLE,
    PARAM_ID_CALLBACK_USER_DATA_ERR,
    PARAM_ID_CALLBACK_SYSTEM_DATA_ERR,
    PARAM_ID_CALLBACK_ACCESS_TIMEOUT,
    PARAM_ID_NO_MORE_DCF_OBJS = 0x0070,
    PARAM_ID_CURRENT_DCF_OBJECT_COUNT,
    PARAM_ID_MAX_FILES_IN_DIR,
    PARAM_ID_MAX_DIR_IN_ROOT,
    PARAM_ID_DCF_DEL_EMPTY,
    PARAM_ID_DCF_COUNT_HIDDEN,
    PARAM_ID_NAND_ECC_MODE,
    PARAM_ID_STORE_TIME_KBPS = 0x0080,
    PARAM_ID_AUDIO_VOLUME,
    PARAM_ID_DUMMY_AUDIO_INSERT,
    PARAM_ID_WAV_DATA_SIZE,
    PARAM_ID_WAV_CURRENT_OFFSET,
    PARAM_ID_AUDIO_REC_CUT_IN_TAIL,
    PARAM_ID_AUDIO_FILTER_SEL,
    PARAM_ID_AUDIO_PORT,
    PARAM_ID_AUDIO_IN_GAIN,
    PARAM_ID_AUDIO_IN_DIGITAL_GAIN,
    PARAM_ID_AUDIO_OUT_GAIN,
    PARAM_ID_AUDIO_ALC_CFG,
    PARAM_ID_AUDIO_REC_MUTE_IN_HEAD,
    PARAM_ID_AUDIO_SWAP_CHANNEL,
    PARAM_ID_AUDIO_PREFILTER_CB,
    PARAM_ID_AUDIO_POSTFILTER_CB,
    PARAM_ID_AUDIO_FORCE_MONO = 0x0090,

    //Group: USB
    PARAM_ID_USB_DESC_VID = 0x0091,
    PARAM_ID_USB_DESC_PID,
    PARAM_ID_USB_UFI_CUSTOM_PRODUCT_ID_SEL,
    PARAM_ID_USB_UFI_INQUIRY_CUSTOM_PRODUCT_ID,
    PARAM_ID_USB_UFI_CUSTOM_VENDOR_ID_SEL,
    PARAM_ID_USB_UFI_INQUIRY_CUSTOM_VENDOR_ID,
    PARAM_ID_USB_UFI_CUSTOM_REV_ID_SEL,
    PARAM_ID_USB_UFI_INQUIRY_CUSTOM_REV_ID,
    PARAM_ID_USB_SERIAL_DESCRIPTOR_SEL,
    PARAM_ID_USB_SERIAL_DESCRIPTOR_STRING,
    PARAM_ID_USB_MANUFACTORY_DESCRIPTOR_STRING,
    PARAM_ID_USB_MANUFACTORY_DESC_STRING_SEL,
    PARAM_ID_USB_PRODUCT_DESC_STRING_SEL,
    PARAM_ID_USB_PRODUCT_DESCRIPTOR_STRING,
    PARAM_ID_USB_DESC_DEV_RELEASE_NUM,
    PARAM_ID_DPOF_CURRENT_STATUS = 0x0100,
    PARAM_ID_DPOF_EXPECT_FILE_SIZE,
    PARAM_ID_AUDIO_OVER_USB,
    PARAM_ID_REGISTER_MS_WRITE_CALLBACK,
    PARAM_ID_PTP_MANUFACTORY_STRING,
    PARAM_ID_PTP_MODEL_STRING,
    PARAM_ID_PTP_VERSION_STRING,
    PARAM_ID_PTP_SERIAL_NUM_STRING,
    PARAM_ID_PTP_USB_MAX_DATA_LEN,
    PARAM_ID_PTP_USB_DB_SIZE,
    PARAM_ID_DPS_VENDOR_NAME_STRING,
    PARAM_ID_DPS_PRODUCT_NAME_STRING,
    PARAM_ID_DPS_VERSION,
    PARAM_ID_DPS_SERIAL_NUMBER,
    PARAM_ID_DPS_VENDOR_SPECIFIC_VER,
    PARAM_ID_DPS_EXT_CAP_FLAG,
    PARAM_ID_USB_DEVICE_SPEED = 0x0110,
    PARAM_ID_USB_MS_DETECT_REQ,

    //Group: Sequential Still Capture
    PARAM_ID_SEQ_CAPTURE_PROFILE = 0xD000,
    PARAM_ID_SEQ_CAPTURE_IMAGES,

    //Group: Image Quality
    PARAM_ID_AE_USE_CUST_ALG = 0xE000,
    PARAM_ID_AWB_CONVERGENCE_THRESHOLD,
    PARAM_ID_AE_MAX_STEP,

    //Group: Calibration
    PARAM_ID_WB_CALIB_AREA_START_X = 0xF000,
    PARAM_ID_WB_CALIB_AREA_START_Y,

    //Group: JPEG
    PARAM_ID_JPEG_DECODE_X_THRESH,
    PARAM_ID_JPEG_DECODE_Y_THRESH,

    //GROUP: AUDIO
    PARAM_ID_AUDIO_VOLUME_DB,

    //GROUP: LCD
    PARAM_ID_LCD_STATUS,

    //GROUP: STROBE
    #if ENABLE_STROBE
    PARAM_ID_STROBE_CALCULATED,
    PARAM_ID_STROBE_CALCULATED_NUMBER,

    PARAM_ID_STROBE_PREFLASH,
    PARAM_ID_STROBE_PREFLASH_NUMBER,
    PARAM_ID_STROBE_WAIT_PREFLASH_TIME,
    PARAM_ID_STROBE_PREFLASH_TIME,
    PARAM_ID_STROBE_TIME_BETWEEN_TWO_FLASH,

    PARAM_ID_STROBE_MAINFLASH,
    PARAM_ID_STROBE_WAIT_MAINFLASH_TIME,
    PARAM_ID_STROBE_MAINFLASH_TIME,
    #endif

    //GROUP: M shutter
    #if (ENABLE_MECHANICAL_SHUTTER)
    PARAM_ID_MECHANICAL_SHUTTER,
    PARAM_ID_MECHANICAL_SHUTTER_TIME,
    #endif

    PARAM_ID_MAX = 0xFFFF
} AHC_PARAM_ID;

typedef enum _AHC_DISPLAY_ROTATE_TYPE {
    AHC_DISPLAY_ROTATE_NO_ROTATE = 0,
    AHC_DISPLAY_ROTATE_RIGHT_90,
    AHC_DISPLAY_ROTATE_RIGHT_180,
    AHC_DISPLAY_ROTATE_RIGHT_270,
    AHC_DISPLAY_ROTATE_MAX
} AHC_DISPLAY_ROTATE_TYPE;

typedef enum _AHC_VALUE_ACCESS_PATH{
    AHC_DEFAULT_FACTORY_FAT = 0x01,
    AHC_DEFAULT_FACTORY_RAW = 0x02,
    AHC_DEFAULT_USER_FAT    = 0x04,
    AHC_DEFAULT_USER_RAW    = 0x08,
    AHC_DEFAULT_SD_FILE     = 0x10,
    AHC_DEFAULT_MAX         = 5
}AHC_VALUE_ACCESS_PATH;

typedef enum _AHC_ISP_PARAM_ID {
    AHC_ISP_CHECKSUM = 0,
    AHC_ISP_VERSION ,
    AHC_ISP_TKEYFW_MAJOR_VERSION ,
    AHC_ISP_TKEYFW_MEDIUM_VERSION ,
    AHC_ISP_TKEYFW_MINOR_VERSION ,
    AHC_ISP_LSCS,
    AHC_ISP_INFIPOS,
    AHC_ISP_AECALI,
    AHC_ISP_AWB,
    AHC_ISP_FOMOTOR_SHIFT,
    AHC_ISP_VALUE_MAX
} AHC_ISP_PARAM_ID;

typedef enum _AHC_ADAS_PARAM_ID {
    AHC_ADAS_ENABLED_LDWS = 0x01,
    AHC_ADAS_ENABLED_FCWS = 0x02,
    AHC_ADAS_ENABLED_SAG  = 0x04
} AHC_ADAS_PARAM_ID;

#if(AHC_USER_SFBACKUP)
//For SF:2 & SF:3 ping-pong partition
typedef enum _AHC_USERFAT_PARTITION {
    SF2_ACTIVE = 0x02,
    SF3_ACTIVE = 0x03,
    INVALID_USER_PARTITION = 0xFF,
} AHC_USERFAT_PARTITION;
#endif

/*===========================================================================
 * Function prototype
 *===========================================================================*/

AHC_BOOL AIHC_PARAM_Initialize(void);
AHC_BOOL AHC_GetParameter(AHC_PARAM_ID para_id, void** param1);
AHC_BOOL AHC_SetParameter(AHC_PARAM_ID para_id, void* param1);
AHC_BOOL AHC_SetParamArray(AHC_PARAM_ID wPRMID, UINT32 wOffset, UINT32 wSize);
AHC_BOOL AHC_GetParamArray(AHC_PARAM_ID wPRMID, UINT32 wOffset, UINT32 wSize);
AHC_BOOL AHC_SetParam(AHC_PARAM_ID wParamID, UINT32 wValue);
AHC_BOOL AHC_GetParam(AHC_PARAM_ID wParamID, UINT32 *wValue);
AHC_BOOL AHC_PARAM_ISP_Init(void);
AHC_BOOL AHC_PARAM_ISP_Read(AHC_ISP_PARAM *param,AHC_VALUE_ACCESS_PATH accesspath);
AHC_BOOL AHC_PARAM_ISP_Write(AHC_VALUE_ACCESS_PATH accesspath);
AHC_BOOL AHC_PARAM_Menu_WriteEx(char *filename);
AHC_BOOL AHC_PARAM_Menu_Write(AHC_VALUE_ACCESS_PATH accesspath);
AHC_BOOL AHC_PARAM_Menu_Read(UINT8 *readback, AHC_VALUE_ACCESS_PATH accesspath);
char*    AHC_PARAM_GetPathPrefix(AHC_VALUE_ACCESS_PATH accesspath, UINT8 RWidx);

void     AHC_SFUser_StartProc(void);
void     AHC_SFUser_EndProc(void);
void     AHC_Get_ActiveNumber(void);
void     AHC_Assign_ActivePartition(void);
void     AHC_Fix_UserPartition(void);
AHC_BOOL AHC_Update_ActiveNumber(UINT32 SFPartition, UINT32 ActiveNum);

#endif
