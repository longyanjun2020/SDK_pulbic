//==============================================================================
//
//  File        : AHC_Parameter.c
//  Description : Access AHC parameters
//  Author      : Ben Lu
//  Revision    : 1.0
//
//==============================================================================

/*===========================================================================
 * Include files
 *===========================================================================*/

#include "ahc_media.h"
#include "ahc_common.h"
#include "ahc_parameter.h"
#include "mmps_i2cm.h"
#include "ahc_uf.h"
#include "mmps_fs.h"
#include "ait_utility.h"
#include "aihc_gui.h"
#include "ahc_utility.h"
#include "mmps_audio.h"
#include "ahc_fs.h"
#include "ahc_menu.h"

/*===========================================================================
 * Global varible
 *===========================================================================*/

AHC_PARAM               glAhcParameter;
AHC_AudioPcmCallBack    *gAhc_AudioPcmCallBack[2];  // 0 : audio record, 1 : audio play
AHC_ISP_PARAM           *gISPsettings = (AHC_ISP_PARAM*)0x2F00000;// need to changed in the future

#if(AHC_USER_SFBACKUP)
//For SF:2 & SF:3 ping-pong partition
volatile AHC_USERFAT_PARTITION   ulSFUSERActiveNO = INVALID_USER_PARTITION;
#endif
/*===========================================================================
 * Extern varible
 *===========================================================================*/

AHC_MEMORY_LOCATION glAhcMemoryLocation[AHC_MEMORY_LOCATION_MAX];

 /*===========================================================================
 * Main body
 *===========================================================================*/

//------------------------------------------------------------------------------
//  Function    : AIHC_PARAM_Initialize
//  Description :
//------------------------------------------------------------------------------
/**
 @brief AHC parameters initailize
 @retval TRUE or FALSE. // TRUE: Success, FALSE: Fail
*/
AHC_BOOL AIHC_PARAM_Initialize(void) {

    gAhc_AudioPcmCallBack[0] = NULL;
    gAhc_AudioPcmCallBack[1] = NULL;

    glAhcParameter.ThumbBKLeft          = 0x0;  //The start region of the background of the thumbnail.
    glAhcParameter.ThumbBKTop           = 0x0;  //The start region of the background of the thumbnail.
    glAhcParameter.ThumbBKWidth         = 160;  //The width of the background of the thumbnail.
    glAhcParameter.ThumbBKHeight        = 120;  //The height of the background of the thumbnail.

    glAhcParameter.ThumbBKColorYU       = 0x0;  //Color of the background of the thumbnail. (msb:Y, lsb:U)
    glAhcParameter.ThumbBKColorYV       = 0x0;  //Color of the background of the thumbnail. (msb:Y, lsb:V)
    glAhcParameter.ThumbFrameThickH     = 0x0;  //Horizontal thickness of the border around a thumbnail.
    glAhcParameter.ThumbFrameThickV     = 0x0;  //Vertical thickness of the border around a thumbnail.
    glAhcParameter.ThumbDeafaultColorYU = 0x0;  //Default color of the thumbnail thickness. (msb:Y, lsb:U)
    glAhcParameter.ThumbDeafaultColorYV = 0x0;  //Default color of the thumbnail thickness. (msb:Y, lsb:V)
    glAhcParameter.ThumbSelectedColorYU = 0x0;  //Color of the selected thumbnail thickness. (msb:Y, lsb:U)
    glAhcParameter.ThumbSelectedColorYV = 0x0;  //Color of the selected thumbnail thickness. (msb:Y, lsb:V)
    glAhcParameter.ThumbTextColorYU     = 0x0;  //Color of the text on thumbnail. (msb:Y, lsb:U)
    glAhcParameter.ThumbTextColorYV     = 0x0;  //Color of the text on thumbnail. (msb:Y, lsb:V)
    glAhcParameter.ThumbShowIndexEnable = 0x0;  //Enable/disable display the thumbnail's DCF index number on the thumbnail icon.

    glAhcParameter.ThumbDrawMode        = 0x0;  //If 0, then all thumbnails will show up at once. If 1, thumbnails will be displayed one by one until draw completed.
    glAhcParameter.ThumbCompressRatio   = 0x0;  //Set the compression ratio for the main thumbnail.
    glAhcParameter.ThumbBigSize         = 0x0;  //Set the max size of thumbnail but it must be smaller than the size of maker note.
    glAhcParameter.StampOffsetX         = 0x0;  //The horizontal offset from the selected corner to the stamping text.
    glAhcParameter.StampOffsetY         = 0x0;  //The vertical offset from the selected corner to the stamping text.
    glAhcParameter.CardDetectPolarity   = 0x1;  //The polarity for card detection pin.
    glAhcParameter.I2cWaitTimeout       = 0x0;  //The wait time for getting I2C response. 0: no wait, 1~0xFFFF.
    glAhcParameter.ExifAutoTag          = 0x1;  //Select the source of EXIF tag.
                                                // 0: EXIF tags update from AHL, it's user's responsibility to set the EXIF via AHC_SetImageEXIF().
                                                // 1: Auto tag provide by AIT system.

    glAhcParameter.AgcForFlashStrobe    = 0x0;  //Set the AGC gain for flash strobe. This gain will be applied to sensor before trigger flash.
    glAhcParameter.UseRtc               = 0x0;  //Enable/disable RTC.
    glAhcParameter.MakerNoteSize        = 0x0;  //Define the size of maker note. If 0, system will not add it to the captured JPEG/TIFF.
    glAhcParameter.FlipLR               = 0x0;  //Enable left/right flipping in both preview and capture modes. If enable, the captured image will be flipped.
    glAhcParameter.FlipUD               = 0x0;  //Enable up/down flipping in both preview and capture modes. If enable, the captured image will be flipped.
    glAhcParameter.SensorMaxVideoWidth  = 0x0;  //Get the maximum width in sensor preview setting.
    glAhcParameter.SensorMaxStillWidth  = 0x0;  //Get the maximum width in sensor still capture setting.
    glAhcParameter.SensorMaxStillHeight = 0x0;  //Get the maximum height in sensor still capture setting.
    glAhcParameter.NightModeAE          = 0x0;  //Perform the night mode exposure in next captured frame.
    glAhcParameter.GrahpicWidth         = 0x0;  //Get the width of current display graphic context.
    glAhcParameter.GrahpicHeight        = 0x0;  //Get the height of current display graphic context.
    glAhcParameter.DisplayFlipLR        = 0x0;  //Enable left/right flipping of display in all modes. This flip will not affect the captured video and image.
    glAhcParameter.DisplayFlipUD        = 0x0;  //Enable up/down flipping of display in all modes. This flip will not affect the captured video and image.
    glAhcParameter.SetVolumeLabel       = 0x0;  //Set a label during media formatting or not. If yes, the label will be added during format operation. The label must be assigned prior to format.
    glAhcParameter.UartWriteBlocking    = 0x0;  //Set and get the status of UART write. 1: Blocking , 2: Non-blocking
    glAhcParameter.UartReadBlocking     = 0x0;  //Set and get the status of UART write. 1: Blocking , 2: Non-blocking
    glAhcParameter.LcdInputON           = 0x1;  //Enable the LCD data and control signal or not. If 0, both data and controls will be set to low and take no effect on LCD.
    glAhcParameter.CheckExifOrientation = 0x0;  //Determine if the image should be displayed according to orientation tag in playback and thumbnail mode.

    glAhcParameter.ImageOrientation     = 0x0;  //0: Disable image orientation. 1~N: Perform the specific orientations.
    glAhcParameter.CaptureMemoryCheck   = 0x0;  //Enable for checking if there has sufficient memory for next shot, if not sufficient, then the transition from capture
                                                //to view is delayed to for ensuring the capture completed.
    glAhcParameter.FreeMemoryCheck      = 0x0;  //Get the size of available buffer. User can know how many free bytes can be allocated.
    glAhcParameter.SensorDownSizeResolution = 0x0;  //Configure the sensor input size of half, quarter and full Resolution. The downsizing is processed on the input sensor data.
                                                //0: Disable    1: Half resolution  2: Quarter resolution

    glAhcParameter.PreviewHalfSizeThresh = 0x0; //System will downscale the display frame if it exceeds this value. The value is set upon hw blocks's capability.
    glAhcParameter.PreviewQuatSizeThresh = 0x0; //The purpose is like PreviewHalfSizeThresh, but this parameter performs quarter scale.
    glAhcParameter.RollingFlick         = 0x0;  //Configure current AE algorithm to work on 50Hz/60Hz. Once set, system should choose the correspond exposure setting to avoid the flicker problem.
    glAhcParameter.IgnoreAhlMessage     = 0x0;  //Set to 1 to ignore all AHL messages, instead of keeping the messages, those messages will be dropped.
    glAhcParameter.DpcEnable            = 0x0;  //Enable/disable the functionality of defective pixels correction.

    glAhcParameter.AhlMsgUnblock        = 0x0;  //Unblock the blocked AHL messages. The input of this parameter is an AHL message ID and be blocked previously.
    glAhcParameter.AhlMsgBlock          = 0x0;  //Block the assigned AHL message upon the input ID.
    glAhcParameter.PwmHightimeResolution = 0x0; //Setup the resolution for high time of PWM and must be set before calling AHC_ConfigPWM().

    glAhcParameter.QuickPreview         = 0x0;  //Enable the quick preview process.
    glAhcParameter.DebugPrintEnable     = 0x0;  //Enable/disable the debug Prints.
    glAhcParameter.QuickCaptureToView   = 0x0;  //Enable/disable the process of capture to view speed up.
    glAhcParameter.StillRawExtraTopLines = 0x0; //Set the number of extra lines in the top of captured raw buffer. The captured raw will be located with offset of this number of lines.
    glAhcParameter.StillRawExtraBottomLines = 0x0;  //Set the number of extra lines in the bottom of captured raw buffer. The captured raw will be located with offset of this number of lines.

    MEMSET(glAhcParameter.SDInfo, 0, sizeof(glAhcParameter.SDInfo));    //If SD card inserted and mounted, returns some information.

    glAhcParameter.StabWindowOffset     = 0x0;  //Set the left-top point of the window for video stabilizer.
    glAhcParameter.StabWindowSize       = 0x0;  //Set the size of the window for video stabilizer.
    glAhcParameter.HdSclGpioGroup       = 0x0;  //Specifies the GPIO group for HDMI serial line Scl.
    glAhcParameter.HdSdaGpioGroup       = 0x0;  //Specifies the GPIO group for HDMI serial line SDA.
    glAhcParameter.HdSdaGpioPin         = 0x0;  //Specifies the GPIO pin for HDMI serial line SDA.
    glAhcParameter.HdSclGpioPin         = 0x0;  //Specifies the GPIO pin for HDMI serial line Scl.
    glAhcParameter.CapYuvmanipScl       = 0x0;  //Specifies timing for the callback function of YUV manipulation during image compression process.
                                                // 0- Function will be called before thumbnail and QVGA image creation.
                                                // 1- Function will be called after the thumbnail/QVGA creation and prior to main image compression.

    glAhcParameter.DisplayBkgColor      = 0x0;  //Set the background color for the default display while there is nothing to show.

    glAhcParameter.MaxCustomMarkerSize  = 0x0;  //Set the maximum custom marker size of EXIF.
    glAhcParameter.SensorStillNumOfBits = 16;   //Set the number of bits per pixel saved in dram in sensor still mode (8/12/16).
    glAhcParameter.SensorVideoNumOfBits = 8;    //Set the number of bits per pixel saved in dram in sensor video mode (8/12/16).

    glAhcParameter.DisplayScaleRatioMethod = 0x0;   //Set the prefer way for display scaling.
                                                //0- Scale default.
                                                //1- Scaler finds out a ratio smaller or equal to the desire ratio.
                                                //2- Scaler finds out a ratio bigger or equal to the desire ratio.
                                                //3- Scaler finds out a ratio that most approximated to the desire ratio.

    glAhcParameter.SeamlessTransitionEnable = 0x1;  //Enable/disable seamless transition between system modes switch. By this feature, the screen won't display the black screen during modes switch.
    //glAhcParameter.Mainboardtype      = MMPC_System_GetMainBrardType();
    //glAhcParameter.DetectFlow         = MMPC_System_GetDetectFlow();

    //Group: MOVIE
    glAhcParameter.MovieAutoPlay        = 0x0;  //The normal playback of movie should be paused when entering the playback mode.
                                                //Set this parameter to let the playback will not be paused and start play automatically.
    glAhcParameter.MovieNumChunks       = 0x0;  //Get the number of chunks of current playing clip.
    glAhcParameter.MovieCurrentChunks   = 0x0;  //Get the current played chunk.
    glAhcParameter.MovieFrameRate       = 0x0;  //Get the frame rate of current playing clip.
    glAhcParameter.MovieSpecailHandle   = 0x0;  //Setup special handles for movie playback.
                                                //0- None
                                                //1- Skip index table when opening AVI files. With this flag, the fist frame can be displayed faster because system
                                                //   won't spend time to load the entire index table which is stored in the tail of the clip.

    glAhcParameter.MovieMaxFileSizeInkb = 0x0;  //Setup the limitation of size in KB for movie record.
    glAhcParameter.MovieNotifyIpbFrameType = 0x0;   //Enable the frame type notification, the information is included in AhlPlayBACK_CURR_CHUNK message. The position is bit 30~31.
                                                    //1 - I,  2 - P,  3 - B

    //Group: UI
    glAhcParameter.MenuScreenWidth      = 320;  //The width of the screen in menu mode. Can be used for scaling the display in menu mode.
    glAhcParameter.MenuScreenHeight     = 240;  //The height of the screen in menu mode. Can be used for scaling the display in menu mode.

    glAhcParameter.JpegDecodeXYThresh   = 0xFFFF;//Set the threshold for the dimensions width*Height. If current decoding JPEG size exceeds this parameter's value, then the image will be pre-scaled to fit the threshold limitation.

    glAhcParameter.OsdBufferShow        = 0x0;  //Set the ID of Osd buffer and shows it on display.
    glAhcParameter.OsdBufferDraw        = 0x0;  //Set the ID of Osd buffer to draw.
    glAhcParameter.OsdBufferNum         = 0x1;  //Get the number of Osd buffers that currently created.

    glAhcParameter.OsdWidth             = 0x0;  //Get the Osd width in pixels (current layer).
    glAhcParameter.OsdHeight            = 0x0;  //Get the Osd height in pixels (current layer).
    glAhcParameter.DrawFileKeepAspRatio = 0x0;  //Set the option of AHC_DrawFile and ask it keeps the aspect ratio of image.

    glAhcParameter.DisplayRotateEnable  = 0x0;  //Enable/disable the display image rotation.
    glAhcParameter.SetTransparentOpaque = 0x0;  //Setup the customized transparent opaque color.
    glAhcParameter.MenuReDraw           = 0x0;  //Setup the menu redraw method. If 1, whole Menu will be drawn at once. That means the menu can be prepared in the background and show it up entirely instead of one-by-one.

    //Group: File & STORAGE
    glAhcParameter.MountFlags           = 0x0;  //Configures the flags for media mount.
                                                //0- No flag
                                                //1- Remove all empty DCF objects (size=0) during mount.
                                                //2- Filter DCF files by date. System will only mount files from the date specified by FilterDcfFilesByDate.
                                                //3- Remove all files with the same file number during mount regardless file type.

    glAhcParameter.FilterDcfFilesByDate = 0x0;  //Set the date for media mount filter. If the flag enabled, DCF will mount the files from this assigned date.

    glAhcParameter.AsyncMount           = 0x0;  //Enable/disable asynchronous mount (no wait for DCF completed)
    glAhcParameter.StorageMediaProtectFlags = 0x0;  //Bit mask corresponds to the media number. The specific number of bit in the mask presents the state of write protection.
                                                    //If set the specific bit in the mask to 1, the corresponded media will be considered as write-protected.
    glAhcParameter.SdramStorageEnd      = 0x0;  //Set the end of the area allocated for SDRAM file system.
    glAhcParameter.DramDrive            = 0x0;  //Enable/disable the feature of DRAM Drive.
    glAhcParameter.SDCardType           = 0x0;  //This value is grabbed and stored during the SD/MMC mount. AHL can get current card type by this parameter. 0- MMC, 1- SD

    glAhcParameter.MsMedia              = 0x0;  //Select current media for Usb Mass Storage mode. 0- Resident, 1- External
    glAhcParameter.MsWpStatus           = 0x0;  //Read the current status of memory stick (MS) or memory stick Pro (MSPro).
                                                //0xFFFF- Access error.
                                                //0- MS,Non write-protect.
                                                //1- MS,Write-protected.
                                                //2- MSPro, Non write-protect.
                                                //3- MSPro, write-protected.

    glAhcParameter.QuickFormat          = 0x0;  //Enable/disable quick format. If enabled, system updates only FATs and boot sectors.
    glAhcParameter.QuickMount           = 0x0;  //Enable/disable quick mount. If enabled, system will not scan all blocks during mount.

    glAhcParameter.MediaFatType         = 0x0;  //Set the desired FAT type before mount or read out current mounted FAT type.  FAT12/FAT16/FAT32
    glAhcParameter.CallbackBadBlockEnable = 0x0;    //If enabled, system will process the assigned callback function to let AHL know that there are too many bad blocks on current media.

    glAhcParameter.CallbackUserDataErr  = 0x0;  //If enabled, system will process the assigned callback function to let AHL know that system discovered an error in user data.

    glAhcParameter.CallbackSystemDataErr = 0x0; //If enabled, system will process the assigned callback function to let AHL know that system discovered an error in system data. Such like root entry or FAT.

    glAhcParameter.CallbackAccessTimeout = 0x0; //If enabled, system will process the assigned callback function to let AHL handle the timeout during media access.

    glAhcParameter.NoMoreDcfObjs        = 0x0;  //To tell if there are no more available DCF that can be created on current media.

    glAhcParameter.IgnoreIllegalDcfObjs = 0x0;  //If set to enable, system will skip the DCF objects that aren't specified by configured DCF rule.

    glAhcParameter.DcfNumberingMode     = 0x0;  //Select the numbering rule for DCF object creation. If 1, next object will be created upon current highest number
    glAhcParameter.DcfCurrentKey        = 0x0;  //Get current key of DCF objects in a DWORD.
    glAhcParameter.DcfLastKey           = 0x0;  //Get last key of DCF objects in a DWORD.
    glAhcParameter.CurrentDcfObjectCount = 0x0; //Get the number of DCF objects in current DCF directory.
    glAhcParameter.MaxFilesInDir        = 999;  //Specify the maximum number of files in a directory.
    glAhcParameter.MaxDirInRoot         = 999;  //Specify the maximum number of Dirs in DCF root.
    glAhcParameter.DcfWindowSize        = 9999; //Set the size of mounting widows for DCF.
    glAhcParameter.DcfDelEmpty          = 0x0;  //If set to 1, the directories which include no DCF objects will be deleted.

    glAhcParameter.DcfCountHidden       = 0x0;  //If set to 1, DCF will not count the hidden objects.
    glAhcParameter.DcfAllowUserDirChar  = 0x0;  //Allow AHL to setup a specified folder which would out of the configured rule.
    glAhcParameter.DcfAllowUserDirCharAUTO = 0x0;   //Allow AHL saves files according to the Dir specified by DcfAllowUserDirChar after calling AHC_SetNextDcfKey() once.

    MEMSET(glAhcParameter.SetAccessFileName, 0, sizeof(glAhcParameter.SetAccessFileName));  //A full file path for a file would be accessed when some API configures AccessByFileName.

    glAhcParameter.AccessByFileName     = 0x0;  //If enable, the operations which are relevant to file access will use the specified name in SetAccessFileName.

    glAhcParameter.NandECCMode          = 0x0;  //Enable/disable the ECC mode in NAND.
    glAhcParameter.StoreTimeKbps        = 0x0;  //This parameter keeps the previous media writing speed in Kbytes per second.

    glAhcParameter.AudioVolume          = 0x3F; //Get or set current audio volume. This parameter affects digital gain only.

    glAhcParameter.DummyAudioInsert     = 0x0;  //Set the audio data to zero during record if this flag enabled
    //glAhcParameter.WavDataSize        = 0x0;  //Get the size of current playing WAV file.
    //glAhcParameter.WavCurrentOffset   = 0x0;  //Get the current offset of playing WAV file.
    glAhcParameter.AudioRecCutInTail    = 0x0;  //Set the number of millisecond of audio data to be truncated before record completed.
    glAhcParameter.AudioFilterSel       = 0x0;  //Determine which filer will be adopted on audio recording.
    glAhcParameter.AudioPort            = 0x1;  // Set the output port of audio unit.
                                                // Bit 0: Speaker ON/OFF
                                                // Bit 1: Line Out ON/OFF
                                                // Bit 2: Headphone ON/OFF
    // Set Audio default for A/D gain, in case no code to set, the audio will be muted.
    glAhcParameter.AudioInGain          = AHC_DEFAULT_VR_MIC_AGAIN; //Set the input gain of audio codec. This value must be set by following the DB range defined inside audio codec.
    glAhcParameter.AudioInDigitalGain   = AHC_DEFAULT_VR_MIC_DGAIN; //Set the input gain of audio codec. This value must be set by following the DB range defined inside audio codec.
    glAhcParameter.AudioOutGain         = 0x40; //Set the output gain of audio codec. This value must be set by following the DB range defined inside audio codec.

    glAhcParameter.AudioAlcCfg          = 0x0;  //Configure the setting of ALC.
    glAhcParameter.AudioRecMuteInHead   = 0x0;  //Set the number of millisecond of audio data need to be muted during record.

    glAhcParameter.AudioSwapChannel     = 0x0;  //Swapping L and R channel.
    glAhcParameter.AudioPreFilterCB     = 0x0;  //Setup a callback function, it will be called before audio compression during record.
    glAhcParameter.AudioPostFilterCB    = 0x0;  //Setup a callback function, it will be called after audio De-compressed during playback.
    //glAhcParameter.AudioForceMono     = 0x0;  //Set to enforce audio output as Mono. For debug and specific cases.

    //Group: Usb
    glAhcParameter.UsbDescVid           = 0x0;  //Set the vendor ID for Usb device descriptor. Set to zero if wants to use the configuration inside resource file.
    glAhcParameter.UsbDescPid           = 0x0;  //Set the product ID for Usb device descriptor. Set to zero if wants to use the configuration inside resource file.

    glAhcParameter.UsbUfiCustomProductIDSel = 0x0;      //Select the source of UFI custom ID. 0- From resource file.
                                                        //1- From the value in UfiInquiryCustomProductID

    MEMSET(glAhcParameter.UsbUfiInquiryCustomProductID, 0, sizeof(glAhcParameter.UsbUfiInquiryCustomProductID)); //Set the product ID for Usb UFI INQUIRY operation

    glAhcParameter.UsbUfiCustomVendorIDSel = 0x0;       //Select the source of UFI custom vendor ID.
                                                        //0 - From resource file.  1 - From the value in UfiInquiryCustomVendorID

    MEMSET(glAhcParameter.UsbUfiInquiryCustomVendorID, 0, sizeof(glAhcParameter.UsbUfiInquiryCustomVendorID)); //Set the vendor ID for Usb UFI INQUIRY operation

    glAhcParameter.UsbUfiCustomRevIDSel = 0x0;          //Select the source of UFI custom revision ID.
                                                        //0-From resource file.
                                                        //1-From the value in UfiInquiryCustomRevID

    MEMSET(glAhcParameter.UsbUfiInquiryCustomRevID, 0, sizeof(glAhcParameter.UsbUfiInquiryCustomRevID));    //Set the revision ID for Usb UFI INQUIRY operation

    glAhcParameter.UsbSerialDescriptorSel = 0x0;        //Select the source of Usb serial descriptor string.

    MEMSET(glAhcParameter.UsbSerialDescriptorString, 0, sizeof(glAhcParameter.UsbSerialDescriptorString));  //Set the Usb serial descriptor string.

    MEMSET(glAhcParameter.UsbManufactoryDescriptorString, 0, sizeof(glAhcParameter.UsbManufactoryDescriptorString));    //Set the Usb manufactory descriptor string.

    glAhcParameter.UsbManufactoryDescStringSel = 0x0;   //Select the source of Usb manufactory descriptor string.
    glAhcParameter.UsbProductDescStringSel = 0x0;       //Select the source of Usb product descriptor string.

    MEMSET(glAhcParameter.UsbProductDescriptorString, 0, sizeof(glAhcParameter.UsbProductDescriptorString)); //Set the Usb product descriptor string.

    glAhcParameter.UsbDescDevReleaseNum = 0x0;          //Set the 'bcdDevice' value in the Usb standard device descriptor.

    glAhcParameter.DpofCurrentStatus    = 0x0;  //Get the status (error code) of DPOF operation.
    glAhcParameter.DpofExpectFileSize   = 0x0;  //Set the expected DPOF file size in KB
    glAhcParameter.AudioOverUsb         = 0x0;  //Set the audio supported in Usb. 0- Not support
    glAhcParameter.RegisterMSWriteCallback = 0x0;   //Set a callback function to be triggered during data writing under Usb mass-storage mode.

    MEMSET(glAhcParameter.PtpManufactoryString, 0, sizeof(glAhcParameter.PtpManufactoryString));
    MEMCPY(glAhcParameter.PtpManufactoryString, "AIT", sizeof("AIT")); //Keeps the manufacturer string of DeviceInfor.

    MEMSET(glAhcParameter.PtpModelString, 0, sizeof(glAhcParameter.PtpModelString));
    MEMCPY(glAhcParameter.PtpModelString, "Camera", sizeof("Camera")); //Keeps the model string of DeviceInfor.

    MEMSET(glAhcParameter.PtpVersionString, 0, sizeof(glAhcParameter.PtpVersionString));
    MEMCPY(glAhcParameter.PtpVersionString, "1.00", sizeof("1.00")); //Keeps the version string of DeviceInfor.

    //glAhcParameter.PtpSerialNumString;    //Keeps the serial number string of DeviceInfor.
    glAhcParameter.PtpUsbMaxDataLen = 0x0;  //Set the maximum data length of Usb PTP standard.
    glAhcParameter.PtpUsbDbSize = 0x0;  //Set the size of PTP database.

    MEMSET(glAhcParameter.DpsVendorNameString, 0, sizeof(glAhcParameter.DpsVendorNameString));
    MEMCPY(glAhcParameter.DpsVendorNameString, "AIT", sizeof("AIT"));  //Keeps the vendor name of response to configurePrintService (DPS Command)

    MEMSET(glAhcParameter.DpsProductNameString, 0, sizeof(glAhcParameter.DpsProductNameString));
    MEMCPY(glAhcParameter.DpsProductNameString, "Camera", sizeof("Camera")); //Keeps the product name of response to configurePrintService (DPS Command)

    MEMSET(glAhcParameter.DpsVersion, 0, sizeof(glAhcParameter.DpsVersion));
    MEMCPY(glAhcParameter.DpsVersion, "1.00", sizeof("1.00")); //Keeps the dpsVersions of response to configurePrintService (DPS Command)

    glAhcParameter.DpsSerialNumber      = 0x0;  //Keeps the serialoNo of response to configurePrintService (DPS Command)

    MEMSET(glAhcParameter.DpsVendorSpecificVer, 0, sizeof(glAhcParameter.DpsVendorSpecificVer));    //Keeps the vendorSpecificVersoin of response to ConfigurePrintService.(DPS Command)

    glAhcParameter.DpsExtCapFlag        = 0x0;  //Set or get the extended capability flag of printer configuration.

    glAhcParameter.UsbDeviceSpeed       = 0x1;  //Set or get the speed of Usb device. To read, Usb must be disconnected.
                                                //0- Usb FULL Speed
                                                //1- Usb HIGH Speed

    glAhcParameter.UsbMsDetectReQ       = 0x0;  //Enable/disable detetion of device connected to Usb, if Devices connected to GPIO then a internal detection must be done.

    //Group: Sequential Still Capture
    glAhcParameter.SeqCaptureProfile    = 0x0;  //Decides the profiled sequence for capture.
    glAhcParameter.SeqCaptureImages     = 0x1;  //Number of images is going to be captured.

    //Group: Image Quality
    glAhcParameter.AEUseCustAlg         = 0x0;  //Enable to use customer AE algorithm and bypass the system AE.
    //Defalut value is defined by ISP
    glAhcParameter.AwbConvergenceThreshold = 0x0;   //The percentage of AWB convergence.
    //Defalut value is defined by ISP
    glAhcParameter.AEMaxStep            = 0x0;  //The maximum EV entry to move in a step. This affects the AE convergent speed.

    //Group: Calibration
    glAhcParameter.WBCalibAreaStartX    = 0x0;  //Start X of the white balance calibration area.
    glAhcParameter.WBCalibAreaStartY    = 0x0;  //Start Y of the white balance calibration area.

    //Group: JPEG
    glAhcParameter.JpegDecodeWidth      = 1024;
    glAhcParameter.JpegDecodeHeight     = 768;

    //Group: AUDIO
    glAhcParameter.AudioVolumeDB        = 0x54;

    //Group: LCD status
    #if (LCD_PLACEMENT_TYPE == LCD_DIR_1)
    glAhcParameter.LCDSataus            = 0x01; //0->Normal 1->LCD Flip
    #elif (LCD_PLACEMENT_TYPE == LCD_DIR_0)
    glAhcParameter.LCDSataus            = 0x00; //0->Normal 1->LCD Flip
    #endif

    return AHC_TRUE;
}

//------------------------------------------------------------------------------
//  Function    : AHC_SetParamArray
//  Description : Set the array of variables to correspond parameter ID, it will be taken from the memory position assigned by AHC_SET_PARAMARRAY_MEM_LOCATION.
//------------------------------------------------------------------------------
/**
    @brief  Set the array of variables to correspond parameter ID
    @param[in] wPRMID  : Parameter ID
    @param[in] wOffset : The offset of the input array.
    @param[in] wSize : The size of data that stored in the array.
    @return  the status of the operation
*/
AHC_BOOL AHC_SetParamArray(AHC_PARAM_ID wPRMID, UINT32 wOffset, UINT32 wSize)
{
    switch(wPRMID) {

        case PARAM_ID_SD_INFO:
            //MEMSET0(glAhcParameter.SDInfo);
            if(wSize <= 24) {
                MEMCPY((glAhcParameter.SDInfo + wOffset), (MMP_BYTE*)(glAhcMemoryLocation[AHC_SET_PARAMARRAY_MEM_LOCATION].ulLocationAddr + wOffset), wSize);
            }
            else {
                RTNA_DBG_Str(0, "AHC Parameter Over Size Error @PARAM_ID_SD_INFO!\r\n");
                return AHC_FALSE;
            }
            break;
        /*
        case PARAM_ID_SET_ACCESS_FILE_NAME:
            if(wSize <= AHC_LONG_STRING_MAX_LENGTH) {
                //MEMSET0(glAhcParameter.SetAccessFileName);
                MEMCPY((glAhcParameter.SetAccessFileName + wOffset), (MMP_BYTE*)(glAhcMemoryLocation[AHC_SET_PARAMARRAY_MEM_LOCATION].ulLocationAddr + wOffset), wSize);
            }
            else {
                RTNA_DBG_Str(0, "AHC Parameter Over Size Error! @PARAM_ID_SET_ACCESS_FILE_NAME\r\n");
                return AHC_FALSE;
            }
            break;
        */
        case PARAM_ID_USB_UFI_INQUIRY_CUSTOM_PRODUCT_ID:
            if(wSize <= 16) {
                //MEMSET0(glAhcParameter.UsbUfiInquiryCustomProductID);
                MEMCPY((glAhcParameter.UsbUfiInquiryCustomProductID + wOffset), (MMP_BYTE*)(glAhcMemoryLocation[AHC_SET_PARAMARRAY_MEM_LOCATION].ulLocationAddr + wOffset), wSize);
            }
            else {
                RTNA_DBG_Str(0, "AHC Parameter Over Size Error @PARAM_ID_USB_UFI_INQUIRY_CUSTOM_PRODUCT_ID!\r\n");
                return AHC_FALSE;
            }
            break;
        case PARAM_ID_USB_UFI_INQUIRY_CUSTOM_VENDOR_ID:
            if(wSize <= 16) {
                //MEMSET0(glAhcParameter.UsbUfiInquiryCustomVendorID);
                MEMCPY((glAhcParameter.UsbUfiInquiryCustomVendorID + wOffset), (MMP_BYTE*)(glAhcMemoryLocation[AHC_SET_PARAMARRAY_MEM_LOCATION].ulLocationAddr + wOffset), wSize);
            }
            else {
                RTNA_DBG_Str(0, "AHC Parameter Over Size Error! @PARAM_ID_USB_UFI_INQUIRY_CUSTOM_VENDOR_ID\r\n");
                return AHC_FALSE;
            }
            break;
        case PARAM_ID_USB_UFI_INQUIRY_CUSTOM_REV_ID:
            if(wSize <= 16) {
                //MEMSET0(glAhcParameter.UsbUfiInquiryCustomRevID);
                MEMCPY((glAhcParameter.UsbUfiInquiryCustomRevID + wOffset), (MMP_BYTE*)(glAhcMemoryLocation[AHC_SET_PARAMARRAY_MEM_LOCATION].ulLocationAddr + wOffset), wSize);
            }
            else {
                RTNA_DBG_Str(0, "AHC Parameter Over Size Error! @PARAM_ID_USB_UFI_INQUIRY_CUSTOM_REV_ID\r\n");
                return AHC_FALSE;
            }
            break;
        case PARAM_ID_USB_SERIAL_DESCRIPTOR_STRING:
            if(wSize <= AHC_STRING_MAX_LENGTH) {
                //MEMSET0(glAhcParameter.UsbSerialDescriptorString);
                MEMCPY((glAhcParameter.UsbSerialDescriptorString + wOffset), (MMP_BYTE*)(glAhcMemoryLocation[AHC_SET_PARAMARRAY_MEM_LOCATION].ulLocationAddr + wOffset), wSize);
            }
            else {
                RTNA_DBG_Str(0, "AHC Parameter Over Size Error! @PARAM_ID_USB_SERIAL_DESCRIPTOR_STRING\r\n");
                return AHC_FALSE;
            }
            break;
        case PARAM_ID_USB_MANUFACTORY_DESCRIPTOR_STRING:
            if(wSize <= AHC_STRING_MAX_LENGTH) {
                //MEMSET0(glAhcParameter.UsbManufactoryDescriptorString);
                MEMCPY((glAhcParameter.UsbManufactoryDescriptorString + wOffset), (MMP_BYTE*)(glAhcMemoryLocation[AHC_SET_PARAMARRAY_MEM_LOCATION].ulLocationAddr + wOffset), wSize);
            }
            else {
                RTNA_DBG_Str(0, "AHC Parameter Over Size Error! @PARAM_ID_USB_MANUFACTORY_DESCRIPTOR_STRING\r\n");
                return AHC_FALSE;
            }
            break;
        case PARAM_ID_USB_PRODUCT_DESCRIPTOR_STRING:
            if(wSize <= AHC_STRING_MAX_LENGTH) {
                //MEMSET0(glAhcParameter.UsbProductDescriptorString);
                MEMCPY((glAhcParameter.UsbProductDescriptorString + wOffset), (MMP_BYTE*)(glAhcMemoryLocation[AHC_SET_PARAMARRAY_MEM_LOCATION].ulLocationAddr + wOffset), wSize);
            }
            else {
                RTNA_DBG_Str(0, "AHC Parameter Over Size Error! @PARAM_ID_USB_PRODUCT_DESCRIPTOR_STRING\r\n");
                return AHC_FALSE;
            }
            break;
        case PARAM_ID_PTP_MANUFACTORY_STRING:
            if(wSize <= AHC_STRING_MAX_LENGTH) {
                //MEMSET0(glAhcParameter.PtpManufactoryString);
                MEMCPY((glAhcParameter.PtpManufactoryString + wOffset), (MMP_BYTE*)(glAhcMemoryLocation[AHC_SET_PARAMARRAY_MEM_LOCATION].ulLocationAddr + wOffset), wSize);
            }
            else {
                RTNA_DBG_Str(0, "AHC Parameter Over Size Error! @PARAM_ID_PTP_MANUFACTORY_STRING\r\n");
                return AHC_FALSE;
            }
            break;
        case PARAM_ID_PTP_MODEL_STRING:
            if(wSize <= AHC_STRING_MAX_LENGTH) {
                //MEMSET0(glAhcParameter.PtpModelString);
                MEMCPY((glAhcParameter.PtpModelString + wOffset), (MMP_BYTE*)(glAhcMemoryLocation[AHC_SET_PARAMARRAY_MEM_LOCATION].ulLocationAddr + wOffset), wSize);
            }
            else {
                RTNA_DBG_Str(0, "AHC Parameter Over Size Error! @PARAM_ID_PTP_MODEL_STRING\r\n");
                return AHC_FALSE;
            }
            break;
        case PARAM_ID_PTP_VERSION_STRING:
            if(wSize <= AHC_STRING_MAX_LENGTH) {
                //MEMSET0(glAhcParameter.PtpVersionString);
                MEMCPY((glAhcParameter.PtpVersionString + wOffset), (MMP_BYTE*)(glAhcMemoryLocation[AHC_SET_PARAMARRAY_MEM_LOCATION].ulLocationAddr + wOffset), wSize);
            }
            else {
                RTNA_DBG_Str(0, "AHC Parameter Over Size Error! @PARAM_ID_PTP_VERSION_STRING\r\n");
                return AHC_FALSE;
            }
            break;
        case PARAM_ID_PTP_SERIAL_NUM_STRING:
            if(wSize <= AHC_STRING_MAX_LENGTH) {
                //MEMSET0(glAhcParameter.PtpSerialNumString);
                MEMCPY((glAhcParameter.PtpSerialNumString + wOffset), (MMP_BYTE*)(glAhcMemoryLocation[AHC_SET_PARAMARRAY_MEM_LOCATION].ulLocationAddr + wOffset), wSize);
            }
            else {
                RTNA_DBG_Str(0, "AHC Parameter Over Size Error! @PARAM_ID_PTP_SERIAL_NUM_STRING\r\n");
                return AHC_FALSE;
            }
            break;
        case PARAM_ID_DPS_VENDOR_NAME_STRING:
            if(wSize <= AHC_STRING_MAX_LENGTH) {
                //MEMSET0(glAhcParameter.DpsVendorNameString);
                MEMCPY((glAhcParameter.DpsVendorNameString + wOffset), (MMP_BYTE*)(glAhcMemoryLocation[AHC_SET_PARAMARRAY_MEM_LOCATION].ulLocationAddr + wOffset), wSize);
            }
            else {
                RTNA_DBG_Str(0, "AHC Parameter Over Size Error! @PARAM_ID_DPS_VENDOR_NAME_STRING\r\n");
                return AHC_FALSE;
            }
            break;
        case PARAM_ID_DPS_PRODUCT_NAME_STRING:
            if(wSize <= AHC_STRING_MAX_LENGTH) {
                //MEMSET0(glAhcParameter.DpsProductNameString);
                MEMCPY((glAhcParameter.DpsProductNameString + wOffset), (MMP_BYTE*)(glAhcMemoryLocation[AHC_SET_PARAMARRAY_MEM_LOCATION].ulLocationAddr + wOffset), wSize);
            }
            else {
                RTNA_DBG_Str(0, "AHC Parameter Over Size Error! @PARAM_ID_DPS_PRODUCT_NAME_STRING\r\n");
                return AHC_FALSE;
            }
            break;
        case PARAM_ID_DPS_VERSION:
            if(wSize <= AHC_STRING_MAX_LENGTH) {
                //MEMSET0(glAhcParameter.DpsVersion);
                MEMCPY((glAhcParameter.DpsVersion + wOffset), (MMP_BYTE*)(glAhcMemoryLocation[AHC_SET_PARAMARRAY_MEM_LOCATION].ulLocationAddr + wOffset), wSize);
            }
            else {
                RTNA_DBG_Str(0, "AHC Parameter Over Size Error! @PARAM_ID_DPS_VERSION\r\n");
                return AHC_FALSE;
            }
            break;
        case PARAM_ID_DPS_VENDOR_SPECIFIC_VER:
            if(wSize <= AHC_STRING_MAX_LENGTH) {
                //MEMSET0(glAhcParameter.DpsVendorSpecificVer);
                MEMCPY((glAhcParameter.DpsVendorSpecificVer + wOffset), (MMP_BYTE*)(glAhcMemoryLocation[AHC_SET_PARAMARRAY_MEM_LOCATION].ulLocationAddr + wOffset), wSize);
            }
            else {
                RTNA_DBG_Str(0, "AHC Parameter Over Size Error! @PARAM_ID_DPS_VENDOR_SPECIFIC_VER\r\n");
                return AHC_FALSE;
            }
            break;
        default:
            RTNA_DBG_Str(0, "AHC_SetParamArray : unsupported ID \r\n");
            RTNA_DBG_PrintLong(0, wPRMID);
            break;
    }
    return AHC_TRUE;
}

//------------------------------------------------------------------------------
//  Function    : AHC_GetParamArray
//  Description : Get the array of data with correspond parameter ID, the will be filled into the memory position assigned by AHC_SET_PARAMARRAY_MEM_LOCATION.
//------------------------------------------------------------------------------
/**
    @brief  Get the array of variables to correspond parameter ID
    @param[in] wPRMID  : Parameter ID
    @param[in] wOffset : The offset of array where data will be taken.
    @param[in] wSize : The size of data to be read.
    @return  the status of the operation
*/
AHC_BOOL AHC_GetParamArray(AHC_PARAM_ID wPRMID, UINT32 wOffset, UINT32 wSize)
{
    switch(wPRMID) {

        case PARAM_ID_SD_INFO:
            //MEMSET0(glAhcParameter.SDInfo);
            if(wSize <= 24) {
                MEMCPY((MMP_BYTE*)glAhcMemoryLocation[AHC_SET_PARAMARRAY_MEM_LOCATION].ulLocationAddr, (glAhcParameter.SDInfo + wOffset), wSize);
            }
            else {
                RTNA_DBG_Str(0, "AHC Parameter Over Size Error @PARAM_ID_SD_INFO!\r\n");
                return AHC_FALSE;
            }
            break;
        /*
        case PARAM_ID_SET_ACCESS_FILE_NAME:
            if(wSize <= AHC_LONG_STRING_MAX_LENGTH) {
                //MEMSET0(glAhcParameter.SetAccessFileName);
                MEMCPY((MMP_BYTE*)glAhcMemoryLocation[AHC_SET_PARAMARRAY_MEM_LOCATION].ulLocationAddr, (glAhcParameter.SetAccessFileName + wOffset), wSize);
            }
            else {
                RTNA_DBG_Str(0, "AHC Parameter Over Size Error! @PARAM_ID_SET_ACCESS_FILE_NAME\r\n");
                return AHC_FALSE;
            }
            break;
        */
        case PARAM_ID_USB_UFI_INQUIRY_CUSTOM_PRODUCT_ID:
            if(wSize <= 16) {
                //MEMSET0(glAhcParameter.UsbUfiInquiryCustomProductID);
                MEMCPY((MMP_BYTE*)glAhcMemoryLocation[AHC_SET_PARAMARRAY_MEM_LOCATION].ulLocationAddr, (glAhcParameter.UsbUfiInquiryCustomProductID + wOffset), wSize);
            }
            else {
                RTNA_DBG_Str(0, "AHC Parameter Over Size Error @PARAM_ID_USB_UFI_INQUIRY_CUSTOM_PRODUCT_ID!\r\n");
                return AHC_FALSE;
            }
            break;
        case PARAM_ID_USB_UFI_INQUIRY_CUSTOM_VENDOR_ID:
            if(wSize <= 16) {
                //MEMSET0(glAhcParameter.UsbUfiInquiryCustomVendorID);
                MEMCPY((MMP_BYTE*)glAhcMemoryLocation[AHC_SET_PARAMARRAY_MEM_LOCATION].ulLocationAddr, (glAhcParameter.UsbUfiInquiryCustomVendorID + wOffset), wSize);
            }
            else {
                RTNA_DBG_Str(0, "AHC Parameter Over Size Error! @PARAM_ID_USB_UFI_INQUIRY_CUSTOM_VENDOR_ID\r\n");
                return AHC_FALSE;
            }
            break;
        case PARAM_ID_USB_UFI_INQUIRY_CUSTOM_REV_ID:
            if(wSize <= 16) {
                //MEMSET0(glAhcParameter.UsbUfiInquiryCustomRevID);
                MEMCPY((MMP_BYTE*)glAhcMemoryLocation[AHC_SET_PARAMARRAY_MEM_LOCATION].ulLocationAddr, (glAhcParameter.UsbUfiInquiryCustomRevID + wOffset), wSize);
            }
            else {
                RTNA_DBG_Str(0, "AHC Parameter Over Size Error! @PARAM_ID_USB_UFI_INQUIRY_CUSTOM_REV_ID\r\n");
                return AHC_FALSE;
            }
            break;
        case PARAM_ID_USB_SERIAL_DESCRIPTOR_STRING:
            if(wSize <= AHC_STRING_MAX_LENGTH) {
                //MEMSET0(glAhcParameter.UsbSerialDescriptorString);
                MEMCPY((MMP_BYTE*)glAhcMemoryLocation[AHC_SET_PARAMARRAY_MEM_LOCATION].ulLocationAddr, (glAhcParameter.UsbSerialDescriptorString + wOffset), wSize);
            }
            else {
                RTNA_DBG_Str(0, "AHC Parameter Over Size Error! @PARAM_ID_USB_SERIAL_DESCRIPTOR_STRING\r\n");
                return AHC_FALSE;
            }
            break;
        case PARAM_ID_USB_MANUFACTORY_DESCRIPTOR_STRING:
            if(wSize <= AHC_STRING_MAX_LENGTH) {
                //MEMSET0(glAhcParameter.UsbManufactoryDescriptorString);
                MEMCPY((MMP_BYTE*)glAhcMemoryLocation[AHC_SET_PARAMARRAY_MEM_LOCATION].ulLocationAddr, (glAhcParameter.UsbManufactoryDescriptorString + wOffset), wSize);
            }
            else {
                RTNA_DBG_Str(0, "AHC Parameter Over Size Error! @PARAM_ID_USB_MANUFACTORY_DESCRIPTOR_STRING\r\n");
                return AHC_FALSE;
            }
            break;
        case PARAM_ID_USB_PRODUCT_DESCRIPTOR_STRING:
            if(wSize <= AHC_STRING_MAX_LENGTH) {
                //MEMSET0(glAhcParameter.UsbProductDescriptorString);
                MEMCPY((MMP_BYTE*)glAhcMemoryLocation[AHC_SET_PARAMARRAY_MEM_LOCATION].ulLocationAddr, (glAhcParameter.UsbProductDescriptorString + wOffset), wSize);
            }
            else {
                RTNA_DBG_Str(0, "AHC Parameter Over Size Error! @PARAM_ID_USB_PRODUCT_DESCRIPTOR_STRING\r\n");
                return AHC_FALSE;
            }
            break;
        case PARAM_ID_PTP_MANUFACTORY_STRING:
            if(wSize <= AHC_STRING_MAX_LENGTH) {
                //MEMSET0(glAhcParameter.PtpManufactoryString);
                MEMCPY((MMP_BYTE*)glAhcMemoryLocation[AHC_SET_PARAMARRAY_MEM_LOCATION].ulLocationAddr, (glAhcParameter.PtpManufactoryString + wOffset), wSize);
            }
            else {
                RTNA_DBG_Str(0, "AHC Parameter Over Size Error! @PARAM_ID_PTP_MANUFACTORY_STRING\r\n");
                return AHC_FALSE;
            }
            break;
        case PARAM_ID_PTP_MODEL_STRING:
            if(wSize <= AHC_STRING_MAX_LENGTH) {
                //MEMSET0(glAhcParameter.PtpModelString);
                MEMCPY((MMP_BYTE*)glAhcMemoryLocation[AHC_SET_PARAMARRAY_MEM_LOCATION].ulLocationAddr, (glAhcParameter.PtpModelString + wOffset), wSize);
            }
            else {
                RTNA_DBG_Str(0, "AHC Parameter Over Size Error! @PARAM_ID_PTP_MODEL_STRING\r\n");
                return AHC_FALSE;
            }
            break;
        case PARAM_ID_PTP_VERSION_STRING:
            if(wSize <= AHC_STRING_MAX_LENGTH) {
                //MEMSET0(glAhcParameter.PtpVersionString);
                MEMCPY((MMP_BYTE*)glAhcMemoryLocation[AHC_SET_PARAMARRAY_MEM_LOCATION].ulLocationAddr, (glAhcParameter.PtpVersionString + wOffset), wSize);
            }
            else {
                RTNA_DBG_Str(0, "AHC Parameter Over Size Error! @PARAM_ID_PTP_VERSION_STRING\r\n");
                return AHC_FALSE;
            }
            break;
        case PARAM_ID_PTP_SERIAL_NUM_STRING:
            if(wSize <= AHC_STRING_MAX_LENGTH) {
                //MEMSET0(glAhcParameter.PtpSerialNumString);
                MEMCPY((MMP_BYTE*)glAhcMemoryLocation[AHC_SET_PARAMARRAY_MEM_LOCATION].ulLocationAddr, (glAhcParameter.PtpSerialNumString + wOffset), wSize);
            }
            else {
                RTNA_DBG_Str(0, "AHC Parameter Over Size Error! @PARAM_ID_PTP_SERIAL_NUM_STRING\r\n");
                return AHC_FALSE;
            }
            break;
        case PARAM_ID_DPS_VENDOR_NAME_STRING:
            if(wSize <= AHC_STRING_MAX_LENGTH) {
                //MEMSET0(glAhcParameter.DpsVendorNameString);
                MEMCPY((MMP_BYTE*)glAhcMemoryLocation[AHC_SET_PARAMARRAY_MEM_LOCATION].ulLocationAddr, (glAhcParameter.DpsVendorNameString + wOffset), wSize);
            }
            else {
                RTNA_DBG_Str(0, "AHC Parameter Over Size Error! @PARAM_ID_DPS_VENDOR_NAME_STRING\r\n");
                return AHC_FALSE;
            }
            break;
        case PARAM_ID_DPS_PRODUCT_NAME_STRING:
            if(wSize <= AHC_STRING_MAX_LENGTH) {
                //MEMSET0(glAhcParameter.DpsProductNameString);
                MEMCPY((MMP_BYTE*)glAhcMemoryLocation[AHC_SET_PARAMARRAY_MEM_LOCATION].ulLocationAddr, (glAhcParameter.DpsProductNameString + wOffset), wSize);
            }
            else {
                RTNA_DBG_Str(0, "AHC Parameter Over Size Error! @PARAM_ID_DPS_PRODUCT_NAME_STRING\r\n");
                return AHC_FALSE;
            }
            break;
        case PARAM_ID_DPS_VERSION:
            if(wSize <= AHC_STRING_MAX_LENGTH) {
                //MEMSET0(glAhcParameter.DpsVersion);
                MEMCPY((MMP_BYTE*)glAhcMemoryLocation[AHC_SET_PARAMARRAY_MEM_LOCATION].ulLocationAddr, (glAhcParameter.DpsVersion + wOffset), wSize);
            }
            else {
                RTNA_DBG_Str(0, "AHC Parameter Over Size Error! @PARAM_ID_DPS_VERSION\r\n");
                return AHC_FALSE;
            }
            break;
        case PARAM_ID_DPS_VENDOR_SPECIFIC_VER:
            if(wSize <= AHC_STRING_MAX_LENGTH) {
                //MEMSET0(glAhcParameter.DpsVendorSpecificVer);
                MEMCPY((MMP_BYTE*)glAhcMemoryLocation[AHC_SET_PARAMARRAY_MEM_LOCATION].ulLocationAddr, (glAhcParameter.DpsVendorSpecificVer + wOffset), wSize);
            }
            else {
                RTNA_DBG_Str(0, "AHC Parameter Over Size Error! @PARAM_ID_DPS_VENDOR_SPECIFIC_VER\r\n");
                return AHC_FALSE;
            }
            break;
        default:
            RTNA_DBG_Str(0, "AHC_GetParamArray : unsupported ID \r\n");
            RTNA_DBG_PrintLong(0, wPRMID);
            break;

    }
    return AHC_TRUE;
}

//------------------------------------------------------------------------------
//  Function    : AHC_SetParam
//  Description : This function sets a value to a specific variable. The description of the specific variable is defined in the document of parameter.
//------------------------------------------------------------------------------
/**
    @brief  This function sets a value to a specific variable.
    @param[in] wParamID : ID of parameters, refer to its description.
    @param[in] wValue : Refer to document for detail usages
    @return  the status of the operation
*/
AHC_BOOL AHC_SetParam(AHC_PARAM_ID wParamID, UINT32 wValue)
{
    MMP_I2CM_ATTR   tempI2cAttribute;
    MMP_ULONG       i = 0;
    UINT32          ret_value = AHC_TRUE;

    switch(wParamID) {

        //Group: SYSTEM
        case PARAM_ID_STAMP_OFFSET_X:
            glAhcParameter.StampOffsetX = wValue;
            break;
        case PARAM_ID_STAMP_OFFSET_Y:
            glAhcParameter.StampOffsetY = wValue;
            break;
        case PARAM_ID_CARD_DETECT_POLARITY:
            glAhcParameter.CardDetectPolarity = wValue;
            break;
        case PARAM_ID_I2C_WAIT_TIMEOUT:
            glAhcParameter.I2cWaitTimeout = wValue;
            for(i = 0; i < I2CM_HW_CNT; i++) {
                tempI2cAttribute.i2cmID = (MMP_I2CM0 + i);
                //MMPS_I2cm_SetRxTimeout(&tempI2cAttribute, glAhcParameter.I2cWaitTimeout);
            }
            break;
        case PARAM_ID_EXIF_AUTO_TAG:
            glAhcParameter.ExifAutoTag = wValue;
            break;
        case PARAM_ID_AGC_FOR_FLASH_STROBE:
            glAhcParameter.AgcForFlashStrobe = wValue;
            break;
        case PARAM_ID_USE_RTC:
            glAhcParameter.UseRtc = wValue;
            break;
        case PARAM_ID_MAKER_NOTE_SIZE:
            glAhcParameter.MakerNoteSize = wValue;
            break;
        case PARAM_ID_FLIP_LR:
            glAhcParameter.FlipLR = wValue;
            break;
        case PARAM_ID_FLIP_UD:
            glAhcParameter.FlipUD = wValue;
            break;
        case PARAM_ID_SENSOR_MAX_VIDEO_WIDTH:
            glAhcParameter.SensorMaxVideoWidth = wValue;
            break;
        case PARAM_ID_SENSOR_MAX_STILL_WIDTH:
            glAhcParameter.SensorMaxStillWidth = wValue;
            break;
        case PARAM_ID_SENSOR_MAX_STILL_HEIGHT:
            glAhcParameter.SensorMaxStillHeight = wValue;
            break;
        case PARAM_ID_NIGHT_MODE_AE:
            glAhcParameter.NightModeAE = wValue;
            break;
        case PARAM_ID_GRAPHIC_WIDTH:
            glAhcParameter.GrahpicWidth = wValue;
            break;
        case PARAM_ID_GRAPHIC_HEIGHT:
            glAhcParameter.GrahpicHeight = wValue;
            break;
        case PARAM_ID_DISPLAY_FLIP_LR:
            glAhcParameter.DisplayFlipLR = wValue;
            break;
        case PARAM_ID_DISPLAY_FLIP_UD:
            glAhcParameter.DisplayFlipUD = wValue;
            break;
        case PARAM_ID_SET_VOLUME_LABEL:
            glAhcParameter.SetVolumeLabel = wValue;
            break;
        case PARAM_ID_UART_WRITE_BLOCKING:
            glAhcParameter.UartWriteBlocking = wValue;
            break;
        case PARAM_ID_UART_READ_BLOCKING:
            glAhcParameter.UartReadBlocking = wValue;
            break;
        case PARAM_ID_CHECK_EXIF_ORIENTATION:
            glAhcParameter.CheckExifOrientation = wValue;
            break;
        case PARAM_ID_IMAGE_ORIENTATION:
            glAhcParameter.ImageOrientation = wValue;
            break;
        case PARAM_ID_CAPTURE_MEMORY_CHECK:
            glAhcParameter.CaptureMemoryCheck = wValue;
            break;
        case PARAM_ID_FREE_MEMORY_CHECK:
            glAhcParameter.FreeMemoryCheck = wValue;
            break;
        case PARAM_ID_SENSOR_DOWNSIZE_RESOLUTION:
            glAhcParameter.SensorDownSizeResolution = wValue;
            break;
        case PARAM_ID_PREVIEW_HALF_SIZE_THRESH:
            glAhcParameter.PreviewHalfSizeThresh = wValue;
            break;
        case PARAM_ID_PREVIEW_QUAT_SIZE_THRESH:
            glAhcParameter.PreviewQuatSizeThresh = wValue;
            break;
        case PARAM_ID_ROLLING_FLICK:
            glAhcParameter.RollingFlick = wValue;
            break;
        case PARAM_ID_IGNORE_AHL_MESSAGE:
            glAhcParameter.IgnoreAhlMessage = wValue;
            break;
        case PARAM_ID_DPC_ENABLE:
            glAhcParameter.DpcEnable = wValue;
            break;
        case PARAM_ID_AHL_MSG_UNBLOCK:
            glAhcParameter.AhlMsgUnblock = wValue;
            break;
        case PARAM_ID_AHL_MSG_BLOCK:
            glAhcParameter.AhlMsgBlock = wValue;
            break;
        case PARAM_ID_PWM_HIGHTIME_RESOLUTION:
            glAhcParameter.PwmHightimeResolution = wValue;
            break;
        case PARAM_ID_QUICK_PREVIEW:
            glAhcParameter.QuickPreview = wValue;
            break;
        case PARAM_ID_DEBUG_PRINT_ENABLE:
            glAhcParameter.DebugPrintEnable = wValue;
            break;
        case PARAM_ID_QUICK_CAPTURE_TO_VIEW:
            glAhcParameter.QuickCaptureToView = wValue;
            break;
        case PARAM_ID_STILL_RAW_EXTRA_TOP_LINES:
            glAhcParameter.StillRawExtraTopLines = wValue;
            break;
        case PARAM_ID_STILL_RAW_EXTRA_BOTTOM_LINES:
            glAhcParameter.StillRawExtraBottomLines = wValue;
            break;
        //case PARAM_ID_SD_INFO:
        case PARAM_ID_STAB_WINDOW_OFFSET:
            glAhcParameter.StabWindowOffset = wValue;
            break;
        case PARAM_ID_STAB_WINDOW_SIZE:
            glAhcParameter.StabWindowSize = wValue;
            break;
        case PARAM_ID_HD_SCL_GPIO_GROUP:
            glAhcParameter.HdSclGpioGroup = wValue;
            break;
        case PARAM_ID_HD_SDA_GPIO_GROUP:
            glAhcParameter.HdSdaGpioGroup = wValue;
            break;
        case PARAM_ID_HD_SDA_GPIO_PIN:
            glAhcParameter.HdSdaGpioPin = wValue;
            break;
        case PARAM_ID_HD_SCL_GPIO_PIN:
            glAhcParameter.HdSclGpioPin = wValue;
            break;
        case PARAM_ID_CAP_YUVMANIP_SCL:
            glAhcParameter.CapYuvmanipScl = wValue;
            break;
        case PARAM_ID_DISPLAY_BKG_COLOR:
            glAhcParameter.DisplayBkgColor = wValue;
            break;
        case PARAM_ID_MAX_CUSTOM_MARKER_SIZE:
            glAhcParameter.MaxCustomMarkerSize = wValue;
            break;
        case PARAM_ID_SENSOR_STILL_NUM_OF_BITS:
            glAhcParameter.SensorStillNumOfBits = wValue;
            break;
        case PARAM_ID_SENSOR_VIDEO_NUM_OF_BITS:
            glAhcParameter.SensorVideoNumOfBits = wValue;
            break;
        case PARAM_ID_DISPLAY_SCALE_RATIO_METHOD:
            glAhcParameter.DisplayScaleRatioMethod = wValue;
            break;
        case PARAM_ID_SEAMLESS_TRANSITION_ENABLE:
            glAhcParameter.SeamlessTransitionEnable = wValue;
            break;
        case PARAM_ID_MAINBOARD_TYPE:
            //glAhcParameter.Mainboardtype = wValue;
            break;
        case PARAM_ID_ENABLE_DETECT_FLOW:
            //glAhcParameter.DetectFlow = wValue;
            break;

        //Group: MOVIE
        case PARAM_ID_MOVIE_AUTO_PLAY:
            glAhcParameter.MovieAutoPlay = wValue;
            break;
        case PARAM_ID_MOVIE_MAX_FILESIZE_INKB:
            if ( wValue >= 32 * 1024 ) {
                glAhcParameter.MovieMaxFileSizeInkb = wValue;

                ret_value = MMPS_3GPRECD_SetFileSizeLimit(wValue);
            }
            else {
                ret_value = AHC_FALSE;
            }
            break;
        case PARAM_ID_DRAW_FILE_KEEP_ASP_RATIO:
            glAhcParameter.DrawFileKeepAspRatio = wValue;
            break;
        case PARAM_ID_DISPLAY_ROTATE_ENABLE:
            glAhcParameter.DisplayRotateEnable = wValue;
            break;

        //Group: FILE & STORAGE
        case PARAM_ID_MOUNT_FLAGS:
            glAhcParameter.MountFlags = wValue;
            break;
        case PARAM_ID_FILTER_DCF_FILES_BY_DATE:
            glAhcParameter.FilterDcfFilesByDate = wValue;
            break;
        case PARAM_ID_ASYNC_MOUNT:
            glAhcParameter.AsyncMount = wValue;
            break;
        case PARAM_ID_STORAGE_MEDIA_PROTECT_FLAGS:
            glAhcParameter.StorageMediaProtectFlags = wValue;
            break;
        case PARAM_ID_SDRAM_STORAGE_END:
            glAhcParameter.SdramStorageEnd = wValue;
            break;
        case PARAM_ID_DRAM_DRIVE:
            glAhcParameter.DramDrive = wValue;
            break;
        case PARAM_ID_SD_CARD_TYPE:
            glAhcParameter.SDCardType = wValue;
            break;
        case PARAM_ID_MS_MEDIA:
            glAhcParameter.MsMedia = wValue;
            break;
        case PARAM_ID_MS_WP_STATUS:
            glAhcParameter.MsWpStatus = wValue;
            break;
        case PARAM_ID_QUICK_FORMAT:
            glAhcParameter.QuickFormat = wValue;
            break;
        case PARAM_ID_QUICK_MOUNT:
            glAhcParameter.QuickMount = wValue;
            break;
        case PARAM_ID_MEDIA_FAT_TYPE:
            glAhcParameter.MediaFatType = wValue;
            break;
        case PARAM_ID_CALLBACK_BAD_BLOCK_ENABLE:
            glAhcParameter.CallbackBadBlockEnable = wValue;
            break;
        case PARAM_ID_CALLBACK_USER_DATA_ERR:
            glAhcParameter.CallbackUserDataErr = wValue;
            break;
        case PARAM_ID_CALLBACK_SYSTEM_DATA_ERR:
            glAhcParameter.CallbackSystemDataErr = wValue;
            break;
        case PARAM_ID_CALLBACK_ACCESS_TIMEOUT:
            glAhcParameter.CallbackAccessTimeout = wValue;
            break;
        case PARAM_ID_MAX_FILES_IN_DIR:
            ret_value = AHC_UF_SetParam(PARAM_ID_MAX_FILES_IN_DIR, wValue);
            glAhcParameter.MaxFilesInDir = wValue;
            break;
        case PARAM_ID_MAX_DIR_IN_ROOT:
            ret_value = AHC_UF_SetParam(PARAM_ID_MAX_DIR_IN_ROOT , wValue);
            glAhcParameter.MaxDirInRoot = wValue;
            break;
        case PARAM_ID_DCF_DEL_EMPTY:
            glAhcParameter.DcfDelEmpty = wValue;
            ret_value = AHC_UF_SetParam(PARAM_ID_DCF_DEL_EMPTY , wValue);
            break;
        case PARAM_ID_DCF_COUNT_HIDDEN:
            glAhcParameter.DcfCountHidden = wValue;
            ret_value = AHC_UF_SetParam(PARAM_ID_DCF_COUNT_HIDDEN , wValue);
            break;
        case PARAM_ID_NAND_ECC_MODE:
            glAhcParameter.NandECCMode = wValue;
            break;
        case PARAM_ID_AUDIO_VOLUME:
            glAhcParameter.AudioVolume = wValue;
            MMPS_AUDIO_SetPlayDigitalGain(glAhcParameter.AudioVolume);
            break;
        case PARAM_ID_DUMMY_AUDIO_INSERT:
            if(glAhcParameter.DummyAudioInsert != wValue) {
                glAhcParameter.DummyAudioInsert = wValue;
                MMPS_AUDIO_EnableDummyRecord(glAhcParameter.DummyAudioInsert);
            }
            break;
        case PARAM_ID_AUDIO_REC_CUT_IN_TAIL:
            if(glAhcParameter.AudioRecCutInTail != wValue) {
                glAhcParameter.AudioRecCutInTail = wValue;
                MMPS_AUDIO_SetRecordTailCutTime(glAhcParameter.AudioRecCutInTail);
            }
            break;
        case PARAM_ID_AUDIO_FILTER_SEL:
            glAhcParameter.AudioFilterSel = wValue;
            break;
        case PARAM_ID_AUDIO_PORT:
            glAhcParameter.AudioPort = wValue;
            if(glAhcParameter.AudioPort & AHC_AUDIO_PORT_LINEOUT) {
                MMPS_Audio_GetConfig()->AudioOutPath |= MMPS_AUDIO_OUT_AFE_LINE;
            }
            else {
                MMPS_Audio_GetConfig()->AudioOutPath &= (~MMPS_AUDIO_OUT_AFE_LINE);

            }

            //if(glAhcParameter.AudioPort & AHC_AUDIO_PORT_HP) {
            //  MMPS_Audio_GetConfig()->AudioOutPath |= MMPS_AUDIO_OUT_AFE_HP;
            //}
            //else {
            //  MMPS_Audio_GetConfig()->AudioOutPath &= (~MMPS_AUDIO_OUT_AFE_HP);
            //}
            break;
        case PARAM_ID_AUDIO_IN_GAIN:
            glAhcParameter.AudioInGain = wValue;
            MMPS_AUDIO_SetRecordAnalogGain(glAhcParameter.AudioInGain, MMP_TRUE);
            break;
        case PARAM_ID_AUDIO_IN_DIGITAL_GAIN:
            glAhcParameter.AudioInDigitalGain = wValue;
            MMPS_AUDIO_SetRecordDigitalGain(glAhcParameter.AudioInDigitalGain);
            break;
        case PARAM_ID_AUDIO_OUT_GAIN:
            glAhcParameter.AudioOutGain = wValue;
            MMPS_AUDIO_SetPlayAnalogGain(glAhcParameter.AudioOutGain);
            break;
        case PARAM_ID_AUDIO_ALC_CFG:
            glAhcParameter.AudioAlcCfg = wValue;
            break;
        case PARAM_ID_AUDIO_REC_MUTE_IN_HEAD:
            if(glAhcParameter.AudioRecMuteInHead != wValue) {
                glAhcParameter.AudioRecMuteInHead = wValue;
                MMPS_AUDIO_SetRecordHeadMuteTime(glAhcParameter.AudioRecMuteInHead);
            }
            break;
        case PARAM_ID_AUDIO_SWAP_CHANNEL:
            glAhcParameter.AudioSwapChannel = wValue;
            if (glAhcParameter.AudioSwapChannel == MMP_TRUE) {
                MMPS_AUDIO_SetLineInChannel(MMPS_AUDIO_LINEIN_SWAP);
            }
            break;
        case PARAM_ID_AUDIO_PREFILTER_CB:
            glAhcParameter.AudioPreFilterCB = wValue;
            gAhc_AudioPcmCallBack[0] = (AHC_AudioPcmCallBack *)glAhcParameter.AudioPreFilterCB;
            break;
        case PARAM_ID_AUDIO_POSTFILTER_CB:
            glAhcParameter.AudioPostFilterCB = wValue;
            gAhc_AudioPcmCallBack[1] = (AHC_AudioPcmCallBack *)glAhcParameter.AudioPostFilterCB;
            break;

        //Group: USB
        case PARAM_ID_USB_DESC_VID:
            glAhcParameter.UsbDescVid = wValue;
            break;
        case PARAM_ID_USB_DESC_PID:
            glAhcParameter.UsbDescPid = wValue;
            break;
        case PARAM_ID_USB_UFI_CUSTOM_PRODUCT_ID_SEL:
            glAhcParameter.UsbUfiCustomProductIDSel = wValue;
            break;
        //case PARAM_ID_USB_UFI_INQUIRY_CUSTOM_PRODUCT_ID:

        case PARAM_ID_USB_UFI_CUSTOM_VENDOR_ID_SEL:
            glAhcParameter.UsbUfiCustomRevIDSel = wValue;
            break;
        //case PARAM_ID_USB_UFI_INQUIRY_CUSTOM_VENDOR_ID:

        case PARAM_ID_USB_UFI_CUSTOM_REV_ID_SEL:
            glAhcParameter.UsbUfiCustomRevIDSel = wValue;
            break;
        //case PARAM_ID_USB_UFI_INQUIRY_CUSTOM_REV_ID:

        case PARAM_ID_USB_SERIAL_DESCRIPTOR_SEL:
            glAhcParameter.UsbSerialDescriptorSel = wValue;
            break;
        //case PARAM_ID_USB_SERIAL_DESCRIPTOR_STRING:
        //case PARAM_ID_USB_MANUFACTORY_DESCRIPTOR_STRING:

        case PARAM_ID_USB_MANUFACTORY_DESC_STRING_SEL:
            glAhcParameter.UsbManufactoryDescStringSel = wValue;
            break;
        case PARAM_ID_USB_PRODUCT_DESC_STRING_SEL:
            glAhcParameter.UsbProductDescStringSel = wValue;
            break;
        //case PARAM_ID_USB_PRODUCT_DESCRIPTOR_STRING:

        case PARAM_ID_USB_DESC_DEV_RELEASE_NUM:
            glAhcParameter.UsbDescDevReleaseNum = wValue;
            break;
        case PARAM_ID_DPOF_CURRENT_STATUS:
            glAhcParameter.DpofCurrentStatus = wValue;
            break;
        case PARAM_ID_DPOF_EXPECT_FILE_SIZE:
            glAhcParameter.DpofExpectFileSize = wValue;
            break;
        case PARAM_ID_AUDIO_OVER_USB:
            glAhcParameter.AudioOverUsb = wValue;
            break;
        case PARAM_ID_REGISTER_MS_WRITE_CALLBACK:
            glAhcParameter.RegisterMSWriteCallback = wValue;
            break;
        //case PARAM_ID_PTP_MANUFACTORY_STRING:
        //case PARAM_ID_PTP_MODEL_STRING:
        //case PARAM_ID_PTP_VERSION_STRING:
        //case PARAM_ID_PTP_SERIAL_NUM_STRING:

        case PARAM_ID_PTP_USB_MAX_DATA_LEN:
            glAhcParameter.PtpUsbMaxDataLen = wValue;
            break;
        case PARAM_ID_PTP_USB_DB_SIZE:
            glAhcParameter.PtpUsbDbSize = wValue;
            break;
        //case PARAM_ID_DPS_VENDOR_NAME_STRING:
        //case PARAM_ID_DPS_PRODUCT_NAME_STRING:
        //case PARAM_ID_DPS_VERSION:

        case PARAM_ID_DPS_SERIAL_NUMBER:
            glAhcParameter.DpsSerialNumber = wValue;
            break;
        //case PARAM_ID_DPS_VENDOR_SPECIFIC_VER:

        case PARAM_ID_DPS_EXT_CAP_FLAG:
            glAhcParameter.DpsExtCapFlag = wValue;
            break;
        case PARAM_ID_USB_DEVICE_SPEED:
            glAhcParameter.UsbDeviceSpeed = wValue;
            break;
        case PARAM_ID_USB_MS_DETECT_REQ:
            glAhcParameter.UsbMsDetectReQ = wValue;
            break;

        //Group: Sequential Still Capture
        case PARAM_ID_SEQ_CAPTURE_PROFILE:
            glAhcParameter.SeqCaptureProfile = wValue;
            break;
        case PARAM_ID_SEQ_CAPTURE_IMAGES:
            glAhcParameter.SeqCaptureImages = wValue;
            break;

        //Group: Image Quality
        case PARAM_ID_AE_USE_CUST_ALG:
            glAhcParameter.AEUseCustAlg = wValue;
            break;
        case PARAM_ID_AWB_CONVERGENCE_THRESHOLD:
            glAhcParameter.AwbConvergenceThreshold = wValue;
            break;
        case PARAM_ID_AE_MAX_STEP:
            glAhcParameter.AEMaxStep = wValue;
            break;

        //Group: Calibration
        case PARAM_ID_WB_CALIB_AREA_START_X:
            glAhcParameter.WBCalibAreaStartX = wValue;
            break;
        case PARAM_ID_WB_CALIB_AREA_START_Y:
            glAhcParameter.WBCalibAreaStartY = wValue;
            break;

        //Group: JPEG
        case PARAM_ID_JPEG_DECODE_X_THRESH:
            glAhcParameter.JpegDecodeWidth = wValue;
            break;
        case PARAM_ID_JPEG_DECODE_Y_THRESH:
            glAhcParameter.JpegDecodeHeight = wValue;
            break;
        case PARAM_ID_AUDIO_VOLUME_DB:
            glAhcParameter.AudioVolumeDB = wValue;
            break;
        case PARAM_ID_LCD_STATUS:
            glAhcParameter.LCDSataus = wValue;
            break;
        case PARAM_ID_ADAS:
            glAhcParameter.ulAdasFlags = wValue;
            break;
        default:
            RTNA_DBG_Str(0, "AHC_SetParameter: Error PARAM_ID \r\n");
            RTNA_DBG_PrintLong(0, wParamID);
            return AHC_FALSE;
            break;
    };
    return ret_value;
}

//------------------------------------------------------------------------------
//  Function    : AHC_GetParam
//  Description : This function gets a value from a specific variable. The description of the specific variable is defined in the document of parameter.
//------------------------------------------------------------------------------
/**
    @brief  This function gets a value from a specific variable.
    @param[in] wParamID : ID of parameters, refer to its description.
    @param[in] *wValue : Point for getting the variable back.
    @return  the status of the operation
*/
AHC_BOOL AHC_GetParam(AHC_PARAM_ID wParamID, UINT32 *wValue)
{
    UINT32 value, ret = AHC_TRUE;

    switch(wParamID) {

        //Group: SYSTEM
        case PARAM_ID_STAMP_OFFSET_X:
            *wValue = glAhcParameter.StampOffsetX;
            break;
        case PARAM_ID_STAMP_OFFSET_Y:
            *wValue = glAhcParameter.StampOffsetY;
            break;
        case PARAM_ID_CARD_DETECT_POLARITY:
            *wValue = glAhcParameter.CardDetectPolarity;
            break;
        case PARAM_ID_I2C_WAIT_TIMEOUT:
            *wValue = glAhcParameter.I2cWaitTimeout;
            break;
        case PARAM_ID_EXIF_AUTO_TAG:
            *wValue = glAhcParameter.ExifAutoTag;
            break;
        /*case PARAM_ID_TIMER_ID:
            *wValue = glAhcParameter.TimerID;
            break;*/
        case PARAM_ID_AGC_FOR_FLASH_STROBE:
            *wValue = glAhcParameter.AgcForFlashStrobe;
            break;
        case PARAM_ID_USE_RTC:
            *wValue = glAhcParameter.UseRtc;
            break;
        case PARAM_ID_MAKER_NOTE_SIZE:
            *wValue = glAhcParameter.MakerNoteSize;
            break;
        case PARAM_ID_FLIP_LR:
            *wValue = glAhcParameter.FlipLR;
            break;
        case PARAM_ID_FLIP_UD:
            *wValue = glAhcParameter.FlipUD;
            break;
        case PARAM_ID_SENSOR_MAX_VIDEO_WIDTH:
            *wValue = glAhcParameter.SensorMaxVideoWidth;
            break;
        case PARAM_ID_SENSOR_MAX_STILL_WIDTH:
            *wValue = glAhcParameter.SensorMaxStillWidth;
            break;
        case PARAM_ID_SENSOR_MAX_STILL_HEIGHT:
            *wValue = glAhcParameter.SensorMaxStillHeight;
            break;
        case PARAM_ID_NIGHT_MODE_AE:
            *wValue = glAhcParameter.NightModeAE;
            break;
        case PARAM_ID_GRAPHIC_WIDTH:
            *wValue = glAhcParameter.GrahpicWidth;
            break;
        case PARAM_ID_GRAPHIC_HEIGHT:
            *wValue = glAhcParameter.GrahpicHeight;
            break;
        case PARAM_ID_DISPLAY_FLIP_LR:
            *wValue = glAhcParameter.DisplayFlipLR;
            break;
        case PARAM_ID_DISPLAY_FLIP_UD:
            *wValue = glAhcParameter.DisplayFlipUD;
            break;
        case PARAM_ID_SET_VOLUME_LABEL:
            *wValue = glAhcParameter.SetVolumeLabel;
            break;
        case PARAM_ID_UART_WRITE_BLOCKING:
            *wValue = glAhcParameter.UartWriteBlocking;
            break;
        case PARAM_ID_UART_READ_BLOCKING:
            *wValue = glAhcParameter.UartReadBlocking;
            break;
        //case PARAM_ID_LCD_INPUT_ON:
        //  *wValue = glAhcParameter.LcdInputON;
        //    break;
        case PARAM_ID_CHECK_EXIF_ORIENTATION:
            *wValue = glAhcParameter.CheckExifOrientation;
            break;
        case PARAM_ID_IMAGE_ORIENTATION:
            *wValue = glAhcParameter.ImageOrientation;
            break;
        case PARAM_ID_CAPTURE_MEMORY_CHECK:
            *wValue = glAhcParameter.CaptureMemoryCheck;
            break;
        case PARAM_ID_FREE_MEMORY_CHECK:
            *wValue = glAhcParameter.FreeMemoryCheck;
            break;
        case PARAM_ID_SENSOR_DOWNSIZE_RESOLUTION:
            *wValue = glAhcParameter.SensorDownSizeResolution;
            break;
        case PARAM_ID_PREVIEW_HALF_SIZE_THRESH:
            *wValue = glAhcParameter.PreviewHalfSizeThresh;
            break;
        case PARAM_ID_PREVIEW_QUAT_SIZE_THRESH:
            *wValue = glAhcParameter.PreviewQuatSizeThresh;
            break;
        case PARAM_ID_ROLLING_FLICK:
            *wValue = glAhcParameter.RollingFlick;
            break;
        case PARAM_ID_IGNORE_AHL_MESSAGE:
            *wValue = glAhcParameter.IgnoreAhlMessage;
            break;
        case PARAM_ID_DPC_ENABLE:
            *wValue = glAhcParameter.DpcEnable;
            break;
        case PARAM_ID_AHL_MSG_UNBLOCK:
            *wValue = glAhcParameter.AhlMsgUnblock;
            break;
        case PARAM_ID_AHL_MSG_BLOCK:
            *wValue = glAhcParameter.AhlMsgBlock;
            break;
        case PARAM_ID_PWM_HIGHTIME_RESOLUTION:
            *wValue = glAhcParameter.PwmHightimeResolution;
            break;
        case PARAM_ID_QUICK_PREVIEW:
            *wValue = glAhcParameter.QuickPreview;
            break;
        case PARAM_ID_DEBUG_PRINT_ENABLE:
            *wValue = glAhcParameter.DebugPrintEnable;
            break;
        case PARAM_ID_QUICK_CAPTURE_TO_VIEW:
            *wValue = glAhcParameter.QuickCaptureToView;
            break;
        case PARAM_ID_STILL_RAW_EXTRA_TOP_LINES:
            *wValue = glAhcParameter.StillRawExtraTopLines;
            break;
        case PARAM_ID_STILL_RAW_EXTRA_BOTTOM_LINES:
            *wValue = glAhcParameter.StillRawExtraBottomLines;
            break;
        case PARAM_ID_SD_INFO:
            //MEMCPY(param1, glAhcParameter.SDInfo, strlen((const MMP_BYTE*)glAhcParameter.SDInfo));
            //break;
        case PARAM_ID_STAB_WINDOW_OFFSET:
            *wValue = glAhcParameter.StabWindowOffset;
            break;
        case PARAM_ID_STAB_WINDOW_SIZE:
            *wValue = glAhcParameter.StabWindowSize;
            break;
        case PARAM_ID_HD_SCL_GPIO_GROUP:
            *wValue = glAhcParameter.HdSclGpioGroup;
            break;
        case PARAM_ID_HD_SDA_GPIO_GROUP:
            *wValue = glAhcParameter.HdSdaGpioGroup;
            break;
        case PARAM_ID_HD_SDA_GPIO_PIN:
            *wValue = glAhcParameter.HdSdaGpioPin;
            break;
        case PARAM_ID_HD_SCL_GPIO_PIN:
            *wValue = glAhcParameter.HdSclGpioPin;
            break;
        case PARAM_ID_CAP_YUVMANIP_SCL:
            *wValue = glAhcParameter.CapYuvmanipScl;
            break;
        case PARAM_ID_DISPLAY_BKG_COLOR:
            *wValue = glAhcParameter.DisplayBkgColor;
            break;
        case PARAM_ID_MAX_CUSTOM_MARKER_SIZE:
            *wValue = glAhcParameter.MaxCustomMarkerSize;
            break;
        case PARAM_ID_SENSOR_STILL_NUM_OF_BITS:
            *wValue = glAhcParameter.SensorStillNumOfBits;
            break;
        case PARAM_ID_SENSOR_VIDEO_NUM_OF_BITS:
            *wValue = glAhcParameter.SensorVideoNumOfBits;
            break;
        case PARAM_ID_DISPLAY_SCALE_RATIO_METHOD:
            *wValue = glAhcParameter.DisplayScaleRatioMethod;
            break;
        case PARAM_ID_SEAMLESS_TRANSITION_ENABLE:
            *wValue = glAhcParameter.SeamlessTransitionEnable;
            break;
        case PARAM_ID_MAINBOARD_TYPE:
            //*wValue = glAhcParameter.Mainboardtype;
            break;
        case PARAM_ID_ENABLE_DETECT_FLOW:
            //*wValue = glAhcParameter.DetectFlow;
            break;

        //Group: MOVIE
        case PARAM_ID_MOVIE_AUTO_PLAY:
            *wValue = glAhcParameter.MovieAutoPlay;
            break;
        case PARAM_ID_MOVIE_FRAME_RATE:
            *wValue = glAhcParameter.MovieFrameRate;
            break;
        case PARAM_ID_OSD_WIDTH:
            AIHC_OSDGetParam(PARAM_ID_OSD_WIDTH, &value);

            *wValue = value;
            break;
        case PARAM_ID_OSD_HEIGHT:
            AIHC_OSDGetParam(PARAM_ID_OSD_HEIGHT, &value);

            *wValue = value;
            break;
        case PARAM_ID_DISPLAY_ROTATE_ENABLE:
            *wValue = glAhcParameter.DisplayRotateEnable;
            break;

        //Group: FILE & STORAGE
        case PARAM_ID_MOUNT_FLAGS:
            *wValue = glAhcParameter.MountFlags;
            break;
        case PARAM_ID_FILTER_DCF_FILES_BY_DATE:
            *wValue = glAhcParameter.FilterDcfFilesByDate;
            break;
        case PARAM_ID_ASYNC_MOUNT:
            *wValue = glAhcParameter.AsyncMount;
            break;
        case PARAM_ID_STORAGE_MEDIA_PROTECT_FLAGS:
            *wValue = glAhcParameter.StorageMediaProtectFlags;
            break;
        case PARAM_ID_SDRAM_STORAGE_END:
            *wValue = glAhcParameter.SdramStorageEnd;
            break;
        case PARAM_ID_DRAM_DRIVE:
            *wValue = glAhcParameter.DramDrive;
            break;
        case PARAM_ID_SD_CARD_TYPE:
            *wValue = glAhcParameter.SDCardType;
            break;
        case PARAM_ID_MS_MEDIA:
            *wValue = glAhcParameter.MsMedia;
            break;
        case PARAM_ID_MS_WP_STATUS:
            *wValue = glAhcParameter.MsWpStatus;
            break;
        case PARAM_ID_QUICK_FORMAT:
            *wValue = glAhcParameter.QuickFormat;
            break;
        case PARAM_ID_QUICK_MOUNT:
            *wValue = glAhcParameter.QuickMount;
            break;
        case PARAM_ID_MEDIA_FAT_TYPE:
            *wValue = glAhcParameter.MediaFatType;
            break;
        case PARAM_ID_CALLBACK_BAD_BLOCK_ENABLE:
            *wValue = glAhcParameter.CallbackBadBlockEnable;
            break;
        case PARAM_ID_CALLBACK_USER_DATA_ERR:
            *wValue = glAhcParameter.CallbackUserDataErr;
            break;
        case PARAM_ID_CALLBACK_SYSTEM_DATA_ERR:
            *wValue = glAhcParameter.CallbackSystemDataErr;
            break;
        case PARAM_ID_CALLBACK_ACCESS_TIMEOUT:
            *wValue = glAhcParameter.CallbackAccessTimeout;
            break;
        case PARAM_ID_NO_MORE_DCF_OBJS:
            AHC_UF_GetParam(PARAM_ID_NO_MORE_DCF_OBJS, &value);

            *wValue = value;
            break;
        case PARAM_ID_CURRENT_DCF_OBJECT_COUNT:
            AHC_UF_GetParam(PARAM_ID_CURRENT_DCF_OBJECT_COUNT, &value);

            *wValue = value;

            break;
        case PARAM_ID_STORE_TIME_KBPS:
            *wValue = glAhcParameter.StoreTimeKbps;
            break;
        case PARAM_ID_AUDIO_VOLUME:
            *wValue = glAhcParameter.AudioVolume;
            break;
        case PARAM_ID_DUMMY_AUDIO_INSERT:
            *wValue = glAhcParameter.DummyAudioInsert;
            break;
        case PARAM_ID_AUDIO_REC_CUT_IN_TAIL:
            *wValue = glAhcParameter.AudioRecCutInTail;
            break;
        case PARAM_ID_AUDIO_FILTER_SEL:
            *wValue = glAhcParameter.AudioFilterSel;
            break;
        case PARAM_ID_AUDIO_PORT:
            *wValue = glAhcParameter.AudioPort;
            break;
        case PARAM_ID_AUDIO_IN_GAIN:
            *wValue = glAhcParameter.AudioInGain;
            break;
        case PARAM_ID_AUDIO_IN_DIGITAL_GAIN:
            *wValue = glAhcParameter.AudioInDigitalGain;
            break;
        case PARAM_ID_AUDIO_OUT_GAIN:
            *wValue = glAhcParameter.AudioOutGain;
            break;
        case PARAM_ID_AUDIO_ALC_CFG:
            *wValue = glAhcParameter.AudioAlcCfg;
            break;
        case PARAM_ID_AUDIO_REC_MUTE_IN_HEAD:
            *wValue = glAhcParameter.AudioRecMuteInHead;
            break;
        case PARAM_ID_AUDIO_SWAP_CHANNEL:
            *wValue = glAhcParameter.AudioSwapChannel;
            break;
        case PARAM_ID_AUDIO_PREFILTER_CB:
            *wValue = glAhcParameter.AudioPreFilterCB;
            break;
        case PARAM_ID_AUDIO_POSTFILTER_CB:
            *wValue = glAhcParameter.AudioPostFilterCB;
            break;

        //Group: USB
        case PARAM_ID_USB_DESC_VID:
            *wValue = glAhcParameter.UsbDescVid;
            break;
        case PARAM_ID_USB_DESC_PID:
            *wValue = glAhcParameter.UsbDescPid;
            break;
        case PARAM_ID_USB_UFI_CUSTOM_PRODUCT_ID_SEL:
            *wValue = glAhcParameter.UsbUfiCustomProductIDSel;
            break;
        case PARAM_ID_USB_UFI_INQUIRY_CUSTOM_PRODUCT_ID:
            //MEMCPY(param1, glAhcParameter.UsbUfiInquiryCustomProductID, strlen((const MMP_BYTE*)glAhcParameter.UsbUfiInquiryCustomProductID));
            //break;
        case PARAM_ID_USB_UFI_CUSTOM_VENDOR_ID_SEL:
            *wValue = glAhcParameter.UsbUfiCustomRevIDSel;
            break;
        case PARAM_ID_USB_UFI_INQUIRY_CUSTOM_VENDOR_ID:
            //MEMCPY(param1, glAhcParameter.UsbUfiInquiryCustomVendorID, strlen((const MMP_BYTE*)glAhcParameter.UsbUfiInquiryCustomVendorID));
            //break;
        case PARAM_ID_USB_UFI_CUSTOM_REV_ID_SEL:
            *wValue = glAhcParameter.UsbUfiCustomRevIDSel;
            break;
        case PARAM_ID_USB_UFI_INQUIRY_CUSTOM_REV_ID:
            //MEMCPY(param1, glAhcParameter.UsbUfiInquiryCustomRevID, strlen((const MMP_BYTE*)glAhcParameter.UsbUfiInquiryCustomRevID));
            //break;
        case PARAM_ID_USB_SERIAL_DESCRIPTOR_SEL:
            *wValue = glAhcParameter.UsbSerialDescriptorSel;
            break;
        case PARAM_ID_USB_SERIAL_DESCRIPTOR_STRING:
            //MEMCPY(param1, glAhcParameter.UsbSerialDescriptorString, strlen((const MMP_BYTE*)glAhcParameter.UsbSerialDescriptorString));
            //break;
        case PARAM_ID_USB_MANUFACTORY_DESCRIPTOR_STRING:
            //MEMCPY(param1, glAhcParameter.UsbManufactoryDescriptorString, strlen((const MMP_BYTE*)glAhcParameter.UsbManufactoryDescriptorString));
            //break;
        case PARAM_ID_USB_MANUFACTORY_DESC_STRING_SEL:
            *wValue = glAhcParameter.UsbManufactoryDescStringSel;
            break;
        case PARAM_ID_USB_PRODUCT_DESC_STRING_SEL:
            *wValue = glAhcParameter.UsbProductDescStringSel;
            break;
        case PARAM_ID_USB_PRODUCT_DESCRIPTOR_STRING:
            //MEMCPY(param1, glAhcParameter.UsbProductDescriptorString, strlen((const MMP_BYTE*)glAhcParameter.UsbProductDescriptorString));
            //break;
        case PARAM_ID_USB_DESC_DEV_RELEASE_NUM:
            *wValue = glAhcParameter.UsbDescDevReleaseNum;
            break;
        case PARAM_ID_DPOF_CURRENT_STATUS:
            *wValue = glAhcParameter.DpofCurrentStatus;
            break;
        case PARAM_ID_DPOF_EXPECT_FILE_SIZE:
            *wValue = glAhcParameter.DpofExpectFileSize;
            break;
        case PARAM_ID_AUDIO_OVER_USB:
            *wValue = glAhcParameter.AudioOverUsb;
            break;
        case PARAM_ID_REGISTER_MS_WRITE_CALLBACK:
            *wValue = glAhcParameter.RegisterMSWriteCallback;
            break;
        case PARAM_ID_PTP_MANUFACTORY_STRING:
            //MEMCPY(param1, glAhcParameter.PtpManufactoryString, strlen((const MMP_BYTE*)glAhcParameter.PtpManufactoryString));
            //break;
        case PARAM_ID_PTP_MODEL_STRING:
            //MEMCPY(param1, glAhcParameter.PtpModelString, strlen((const MMP_BYTE*)glAhcParameter.PtpModelString));
            //break;
        case PARAM_ID_PTP_VERSION_STRING:
            //MEMCPY(param1, glAhcParameter.PtpVersionString, strlen((const MMP_BYTE*)glAhcParameter.PtpVersionString));
            //break;
        case PARAM_ID_PTP_SERIAL_NUM_STRING:
            //MEMCPY(param1, glAhcParameter.PtpSerialNumString, strlen((const MMP_BYTE*)glAhcParameter.PtpSerialNumString));
            //break;
        case PARAM_ID_PTP_USB_MAX_DATA_LEN:
            *wValue = glAhcParameter.PtpUsbMaxDataLen;
            break;
        case PARAM_ID_PTP_USB_DB_SIZE:
            *wValue = glAhcParameter.PtpUsbDbSize;
            break;
        case PARAM_ID_DPS_VENDOR_NAME_STRING:
            //MEMCPY(param1, glAhcParameter.DpsVendorNameString, strlen((const MMP_BYTE*)glAhcParameter.DpsVendorNameString));
            //break;
        case PARAM_ID_DPS_PRODUCT_NAME_STRING:
            //MEMCPY(param1, glAhcParameter.DpsProductNameString, strlen((const MMP_BYTE*)glAhcParameter.DpsProductNameString));
            //break;
        case PARAM_ID_DPS_VERSION:
            //MEMCPY(param1, glAhcParameter.DpsVersion, strlen((const MMP_BYTE*)glAhcParameter.DpsVersion));
            //break;
        case PARAM_ID_DPS_SERIAL_NUMBER:
            *wValue = glAhcParameter.DpsSerialNumber;
            break;
        case PARAM_ID_DPS_VENDOR_SPECIFIC_VER:
            //MEMCPY(param1, glAhcParameter.DpsVendorSpecificVer, strlen((const MMP_BYTE*)glAhcParameter.DpsVendorSpecificVer));
            //break;
        case PARAM_ID_DPS_EXT_CAP_FLAG:
            *wValue = glAhcParameter.DpsExtCapFlag;
            break;
        case PARAM_ID_USB_DEVICE_SPEED:
            *wValue = glAhcParameter.UsbDeviceSpeed;
            break;
        case PARAM_ID_USB_MS_DETECT_REQ:
            *wValue = glAhcParameter.UsbMsDetectReQ;
            break;

        //Group: Sequential Still Capture
        case PARAM_ID_SEQ_CAPTURE_PROFILE:
            *wValue = glAhcParameter.SeqCaptureProfile;
            break;
        case PARAM_ID_SEQ_CAPTURE_IMAGES:
            *wValue = glAhcParameter.SeqCaptureImages;
            break;

        //Group: Image Quality
        case PARAM_ID_AE_USE_CUST_ALG:
            *wValue = glAhcParameter.AEUseCustAlg;
            break;
        case PARAM_ID_AWB_CONVERGENCE_THRESHOLD:
            *wValue = glAhcParameter.AwbConvergenceThreshold;
            break;
        case PARAM_ID_AE_MAX_STEP:
            *wValue = glAhcParameter.AEMaxStep;
            break;

        //Group: Calibration
        case PARAM_ID_WB_CALIB_AREA_START_X:
            *wValue = glAhcParameter.WBCalibAreaStartX;
            break;
        case PARAM_ID_WB_CALIB_AREA_START_Y:
            *wValue = glAhcParameter.WBCalibAreaStartY;
            break;

        //Group: JPEG
        case PARAM_ID_JPEG_DECODE_X_THRESH:
            *wValue = glAhcParameter.JpegDecodeWidth;
            break;
        case PARAM_ID_JPEG_DECODE_Y_THRESH:
            *wValue = glAhcParameter.JpegDecodeHeight;
            break;
        case PARAM_ID_AUDIO_VOLUME_DB:
            *wValue = glAhcParameter.AudioVolumeDB;
            break;
        case PARAM_ID_LCD_STATUS:
            *wValue = glAhcParameter.LCDSataus;
            break;
        case PARAM_ID_ADAS:
            *wValue = glAhcParameter.ulAdasFlags;
            break;

        default:
            RTNA_DBG_Str(0, "AHC_GetParameter: error PARAM ID !\r\n");
            RTNA_DBG_PrintLong(0, wParamID);
            return AHC_FALSE;
            break;
    };

    return ret;
}

//------------------------------------------------------------------------------
//  Function    : AHC_SetISPParam
//  Description : This function gets a value from a specific variable. The description of the specific variable is defined in the document of parameter.
//------------------------------------------------------------------------------
/**
    @brief  This function sets a value to a specific variable.
    @param[in] wParamID : ID of parameters, refer to its description.
    @param[in] wValue : Refer to document for detail usages
    @return  the status of the operation
*/
AHC_BOOL AHC_SetISPParam(AHC_ISP_PARAM_ID wParamID, UINT8* wAddr)
{
    UINT32 ret = AHC_TRUE;

    switch(wParamID) {

        //Group: SYSTEM
        case AHC_ISP_CHECKSUM:
            MEMCPY(&(gISPsettings->CheckSum),wAddr,sizeof(gISPsettings->CheckSum));
            break;
        case AHC_ISP_VERSION:
            MEMCPY(&(gISPsettings->Version),wAddr,sizeof(gISPsettings->Version));
            break;
        case AHC_ISP_TKEYFW_MAJOR_VERSION:
            MEMCPY(&(gISPsettings->TurnkeyFwMajorVersion),wAddr,sizeof(gISPsettings->TurnkeyFwMajorVersion));
            break;
        case AHC_ISP_TKEYFW_MEDIUM_VERSION:
            MEMCPY(&(gISPsettings->TurnkeyFwMediumVersion),wAddr,sizeof(gISPsettings->TurnkeyFwMediumVersion));
            break;
        case AHC_ISP_TKEYFW_MINOR_VERSION:
            MEMCPY(&(gISPsettings->TurnkeyFwMinorVersion),wAddr,sizeof(gISPsettings->TurnkeyFwMinorVersion));
            break;
        case AHC_ISP_LSCS:
            MEMCPY(gISPsettings->LsCsData,wAddr,sizeof(gISPsettings->LsCsData));
            break;
        case AHC_ISP_INFIPOS:
            MEMCPY(gISPsettings->INFPos,wAddr,sizeof(gISPsettings->INFPos));
            break;
        //add by casio
        case AHC_ISP_AECALI:
            MEMCPY(gISPsettings->AeCali,wAddr,sizeof(gISPsettings->AeCali));
            break;
        case AHC_ISP_AWB:
            MEMCPY(gISPsettings->AwbData,wAddr,sizeof(gISPsettings->AwbData));
            break;
        case AHC_ISP_FOMOTOR_SHIFT:
            MEMCPY(&(gISPsettings->FocusMotorAddiShift),wAddr,sizeof(gISPsettings->FocusMotorAddiShift));
            break;
        default:
            RTNA_DBG_Str(0, "AHC_SetDefaultParam: error PARAM ID !\r\n");
            RTNA_DBG_PrintLong(0, wParamID);
            return AHC_FALSE;
            break;
    }
    return ret;
}

//------------------------------------------------------------------------------
//  Function    : AHC_GetISPParam
//  Description : This function gets a value from a specific variable. The description of the specific variable is defined in the document of parameter.
//------------------------------------------------------------------------------
/**
    @brief  This function gets a value from a specific variable.
    @param[in] wParamID : ID of parameters, refer to its description.
    @param[in] *wValue : Point for getting the variable back.
    @return  the status of the operation
*/
AHC_BOOL AHC_GetISPParam(AHC_ISP_PARAM_ID wParamID, UINT32 *wValue)
{
    UINT32 ret = AHC_TRUE;

    switch(wParamID) {

        //Group: SYSTEM
        case AHC_ISP_CHECKSUM:
            *wValue = gISPsettings->CheckSum;
            break;
        case AHC_ISP_VERSION:
            *wValue = gISPsettings->Version;
            break;
        case AHC_ISP_TKEYFW_MAJOR_VERSION:
            *wValue = gISPsettings->TurnkeyFwMajorVersion;
            break;
        case AHC_ISP_TKEYFW_MEDIUM_VERSION:
            *wValue = gISPsettings->TurnkeyFwMediumVersion;
            break;
        case AHC_ISP_TKEYFW_MINOR_VERSION:
            *wValue = gISPsettings->TurnkeyFwMinorVersion;
            break;
        case AHC_ISP_LSCS:
            wValue = (UINT32 *)gISPsettings->LsCsData;
            break;
        case AHC_ISP_INFIPOS:
            wValue = (UINT32 *)gISPsettings->INFPos;
            break;
        //add by casio
        case AHC_ISP_AECALI:
            wValue = (UINT32 *)gISPsettings->AeCali;
            break;
        case AHC_ISP_AWB:
            wValue = (UINT32 *)gISPsettings->AwbData;
            break;
        case AHC_ISP_FOMOTOR_SHIFT:
            *wValue = gISPsettings->FocusMotorAddiShift;
            break;
        default:
            RTNA_DBG_Str(0, "AHC_GetDefaultParam: error PARAM ID !\r\n");
            RTNA_DBG_PrintLong(0, wParamID);
            return AHC_FALSE;
            break;
    }
    return ret;
}

//------------------------------------------------------------------------------
//  Function    : AHC_PARAM_ISP_Init
//  Description : Write default value to storage device
//------------------------------------------------------------------------------
AHC_BOOL AHC_PARAM_ISP_Init()
{
    gISPsettings->CheckSum              = 0;
    gISPsettings->Version               = 0xFFFF;
    gISPsettings->TurnkeyFwMajorVersion = 0;
    gISPsettings->TurnkeyFwMediumVersion = 0;
    gISPsettings->TurnkeyFwMinorVersion = 0;
    MEMSET(gISPsettings->LsCsData, 0, sizeof(gISPsettings->LsCsData));
    MEMSET(gISPsettings->INFPos, 0, sizeof(gISPsettings->INFPos));

    return AHC_TRUE;
}

//------------------------------------------------------------------------------
//  Function    : AHC_PARAM_ISP_Write2SIF
//  Description : Write default value to storage device
//------------------------------------------------------------------------------

#include "mmpf_storage_api.h"

#define BURN_BUFFER_SIZE           8192
#define AIT_FW_SD_BUFFER_SIZE      2048
#define AIT_BOOT_HEADER_SIZE       512
#define AIT_BURN_HEADER_SIZE       1024
#define AIT_BURN_CONFIG_SIZE       1024
#define AIT_FW_NAND_BUFFER_SIZE    2048
#define AIT_FW_SM_BUFFER_SIZE      2048
#define AIT_FW_SRC_BUFFER_SIZE     BURN_BUFFER_SIZE
#define AIT_FW_DEST_BUFFER_SIZE    BURN_BUFFER_SIZE

#define AIT_FW_SD_BUFFER_ADDR      0x2200000
#define AIT_FW_NAND_BUFFER_ADDR    (AIT_FW_SD_BUFFER_ADDR + AIT_FW_SD_BUFFER_SIZE)
#define AIT_FW_SM_BUFFER_ADDR      (AIT_FW_NAND_BUFFER_ADDR+AIT_FW_NAND_BUFFER_SIZE)
#define AIT_FW_SIF_BUFFER_ADDR     (AIT_FW_SM_BUFFER_ADDR+AIT_FW_SM_BUFFER_SIZE)

extern const FS_DEVICE_TYPE    FS_SFLASH_Driver;

AHC_BOOL AHC_PARAM_ISP_Write2SIF(void)
{
    FS_SFLASH_Driver.pfIoCtl(0, FS_CMD_SET_SDMMC_BUFFER, AIT_FW_SIF_BUFFER_ADDR, 0 );
    FS_SFLASH_Driver.pfInitDevice(0);
    FS_SFLASH_Driver.pfInitMedium(0);

    FS_SFLASH_Driver.pfWriteBurst(0, 128, (sizeof(AHC_ISP_PARAM)/FS_MAX_SECTOR_SIZE)+1,(INT8*)gISPsettings);
    printc("===write SIF ok\n" );

    #if 0 // test debug
    {
        INT8* temp_addr1 = (INT8*)0x3100000;
        INT8* temp_addr2 = (INT8*)gISPsettings;
        int i=0,j=0;

        FS_SFLASH_Driver.pfReadBurst(0, 128, (sizeof(AHC_ISP_PARAM)/FS_MAX_SECTOR_SIZE)+1,(INT8*)temp_addr1);

        for(i=0;i<sizeof(AHC_ISP_PARAM);i++)
        {
            if((temp_addr1[i] - temp_addr2[i]) != 0)
                printc("Error in check!! #%d: %d - %d \n",i,temp_addr1[i],temp_addr2[i]);
        }
    }
    #endif

    return AHC_FALSE;
}

//------------------------------------------------------------------------------
//  Function    : AHC_PARAM_ISP_Write
//  Description : Write default value to storage device
//------------------------------------------------------------------------------
AHC_BOOL AHC_PARAM_ISP_Write(AHC_VALUE_ACCESS_PATH accesspath)
{
    char    path[50] = {0};

    #if (STORAGE_FOR_FACTORY_INFO == INFO_NAND_FLASH)
    STRCPY(path, "SM:");
    #elif (STORAGE_FOR_FACTORY_INFO == INFO_SERIAL_FLASH)
    if(accesspath == AHC_DEFAULT_USER_FAT)
    STRCPY(path,"SF:0:\\");
    else if (accesspath == AHC_DEFAULT_FACTORY_FAT)
    STRCPY(path,"SF:1:\\");
    STRCAT(path,AHC_ISP_FILENAME);
    goto Label_FileProc;
    #else
    STRCPY(path,"SD:");
    #endif
    switch(accesspath)
    {
        case AHC_DEFAULT_FACTORY_FAT:
            STRCAT(path,"3:\\");
        break;
        case AHC_DEFAULT_FACTORY_RAW:
            STRCAT(path,"4:\\");
        break;
        case AHC_DEFAULT_USER_FAT:
            STRCAT(path,"5:\\");
        break;
        case AHC_DEFAULT_USER_RAW:
            STRCAT(path,"6:\\");
        break;

    }
    STRCAT(path,AHC_ISP_FILENAME);

Label_FileProc :

    DramToFile(path, (INT8*)gISPsettings,sizeof(AHC_ISP_PARAM));

    // write ISP.bin to SIF
    AHC_PARAM_ISP_Write2SIF();

    return AHC_TRUE;
}

//------------------------------------------------------------------------------
//  Function    : AHC_PARAM_ISP_Read
//  Description : Read default value from storage device
//------------------------------------------------------------------------------
AHC_BOOL AHC_PARAM_ISP_Read(AHC_ISP_PARAM *readback,AHC_VALUE_ACCESS_PATH accesspath)
{
    #define AHC_PARAM_ISP_READ_DEBUG (0)

    char    path[50] = {0};
    AHC_ERR err;
    UINT32  ulFileId;
    UINT32  ulFileSize;
    UINT32  ulActualSize;

    #if (STORAGE_FOR_FACTORY_INFO == INFO_NAND_FLASH)
    STRCPY(path, "SM:");
    #elif (STORAGE_FOR_FACTORY_INFO == INFO_SERIAL_FLASH)
    if(accesspath == AHC_DEFAULT_USER_FAT)
    STRCPY(path,"SF:0:\\");
    else if (accesspath == AHC_DEFAULT_FACTORY_FAT)
    STRCPY(path,"SF:1:\\");
    STRCAT(path,AHC_ISP_FILENAME);
    goto Label_FileProc;
    #else
    STRCPY(path,"SD:");
    #endif
    switch(accesspath)
    {
        case AHC_DEFAULT_FACTORY_FAT:
            STRCAT(path,"3:\\");
        break;
        case AHC_DEFAULT_FACTORY_RAW:
            STRCAT(path,"4:\\");
        break;
        case AHC_DEFAULT_USER_FAT:
            STRCAT(path,"5:\\");
        break;
        case AHC_DEFAULT_USER_RAW:
            STRCAT(path,"6:\\");
        break;

    }
    STRCAT(path,AHC_ISP_FILENAME);

Label_FileProc :
    err = AHC_FS_FileOpen(path,AHC_StrLen(path),"rb",AHC_StrLen("rb"),&ulFileId);

    #if (AHC_PARAM_ISP_READ_DEBUG == 1)
    if(err)
        printc("AHC_FS_FileOpen error\n");
    #endif

    err = AHC_FS_FileGetSize(ulFileId,&ulFileSize);

    #if (AHC_PARAM_ISP_READ_DEBUG == 1)
    if(err)
        printc("AHC_FS_FileGetSize error\n");
    #endif

    err = AHC_FS_FileRead(ulFileId,(UINT8 *)readback,sizeof(AHC_ISP_PARAM),&ulActualSize);

    #if (AHC_PARAM_ISP_READ_DEBUG == 1)
    if(err)
        printc("AHC_FS_FileWrite error\n");
    #endif

    err = AHC_FS_FileClose(ulFileId);

    if(err)
        printc("AHC_FS_FileClose error\n");

    if(err)
        return AHC_FALSE;
    else
        return AHC_TRUE;
}


const char txtDefFile[] = "SF:1:\\defset.txt";
#if(AHC_USER_SFBACKUP)
//For SF:2 & SF:3 ping-pong partition
const char txtSetFileSF2[] = "SF:2:\\useset.txt";
const char txtSetFileSF3[] = "SF:3:\\useset.txt";
const char ActiveNUMSF2[] = "SF:2:\\SFActiveNum.txt";
const char ActiveNUMSF3[] = "SF:3:\\SFActiveNum.txt";
const char WifiSetFileSF2[] = "SF:2:\\usernetconf.txt";
const char WifiSetFileSF3[] = "SF:3:\\usernetconf.txt";
const char WifiIPSF2[] = "SF:2:\\ddippool.bin";
const char WifiIPSF3[] = "SF:3:\\ddippool.bin";
const char WifiCfgSF2[] = "SF:2:\\ddsvrcfg.bin";
const char WifiCfgSF3[] = "SF:3:\\ddsvrcfg.bin";
UINT32     glSFACTNUM[2] = {0};
#else
const char txtSetFile[] = "SF:2:\\useset.txt";
#endif

void AHC_SFUser_StartProc(void)//Notice:Read from Active,Write to NonActive
{
#if (AHC_USER_SFBACKUP)
    //printc("@ AHC_SFUser_StartProc @\r\n");

    //printc("ulSFUSERActiveNO:%x\r\n",ulSFUSERActiveNO);

    AHC_Fix_UserPartition();
    AHC_Get_ActiveNumber();
    AHC_Assign_ActivePartition();
#endif
}

void AHC_SFUser_EndProc(void)//Notice:Read from Active,Write to NonActive, execure EndProce each time in the end of ExportMenuAtom
{
#if (AHC_USER_SFBACKUP)
    //printc("@ AHC_SFUser_EndProc @\r\n");

    //printc("ulSFUSERActiveNO:%x\r\n",ulSFUSERActiveNO);

    if(ulSFUSERActiveNO == SF2_ACTIVE)
        AHC_Update_ActiveNumber(SF3_ACTIVE, (glSFACTNUM[0] + 1) );
    else if(ulSFUSERActiveNO == SF3_ACTIVE)
        AHC_Update_ActiveNumber(SF2_ACTIVE, (glSFACTNUM[1] + 1) );
    else if(ulSFUSERActiveNO == INVALID_USER_PARTITION)
        printc("Error(AHC_SFUser_EndProc): ulSFUSERActiveNO = INVALID_USER_PARTITION\r\n");
#endif
}

void AHC_Fix_UserPartition(void)
{
#if (AHC_USER_SFBACKUP)
    AHC_ERR err = AHC_ERR_NONE, SFSTS[8] = {AHC_ERR_NONE};
    UINT32  ulFileId = 0, TempU32 = 0;
    char *SFCheck[8] = {NULL};

    /*
    if(ulSFUSERActiveNO == SF2_ACTIVE)
    {
        SFCheck[0] = txtSetFileSF2;
        SFCheck[1] = WifiSetFileSF2;
        SFCheck[2] = WifiIPSF2;
        SFCheck[3] = WifiCfgSF2;
    }
    else if(ulSFUSERActiveNO == SF3_ACTIVE)
    {
        SFCheck[0] = txtSetFileSF3;
        SFCheck[1] = WifiSetFileSF3;
        SFCheck[2] = WifiIPSF3;
        SFCheck[3] = WifiCfgSF3;
    }
    */
    SFCheck[0] = txtSetFileSF2;
    SFCheck[1] = WifiSetFileSF2;
    SFCheck[2] = WifiIPSF2;
    SFCheck[3] = WifiCfgSF2;
    SFCheck[4] = txtSetFileSF3;
    SFCheck[5] = WifiSetFileSF3;
    SFCheck[6] = WifiIPSF3;
    SFCheck[7] = WifiCfgSF3;

    //printc("@ AHC_Fix_UserPartition @\r\n");
    for(TempU32 = 0;TempU32 < 8;TempU32++)
    {
        err = AHC_FS_FileOpen(SFCheck[TempU32], AHC_StrLen(SFCheck[TempU32]), "rb", AHC_StrLen("rb"), &ulFileId);
        if(err)
        {
            SFSTS[TempU32] = AHC_FS_ERR_SFUSER_FAIL;
            break;
        }
        else
            AHC_FS_FileClose(ulFileId);
    }

    if( (TempU32 >= 0) && (TempU32 <= 3) )//SF2 Bad Partition
    {
        RTNA_DBG_Str(0, "Raw copy SF3 TO SF2\r\n");
        err = FS_SFLASH_Driver.pfIoCtl(SF3_ACTIVE, FS_CMD_SF_USERCOPY, 0, 0 );
        if(err)
            RTNA_DBG_Str(0, "Fail=>Raw copy SF3 TO SF2\r\n");
    }

    if( (TempU32 >= 4) && (TempU32 <= 7) )//SF3 Bad Partition
    {
        RTNA_DBG_Str(0, "Raw copy SF2 TO SF3\r\n");
        err = FS_SFLASH_Driver.pfIoCtl(SF2_ACTIVE, FS_CMD_SF_USERCOPY, 0, 0 );
        if(err)
            RTNA_DBG_Str(0, "Fail=>Raw copy SF2 TO SF3\r\n");
    }

    #if(0)
    AHC_ERR err = AHC_ERR_NONE, SFSTS[2] = {AHC_ERR_NONE};//SF2sts = AHC_ERR_NONE, SF3sts = AHC_ERR_NONE;
    UINT8   ErrRet = 0;
    UINT32  ulFileId = 0, TempU32 = 0;
    UINT32  u32OSTick = 0;
    char *SFUserFile[2] = {NULL};
    MMP_ULONG m_ulCurTime1 = 0,m_ulCurTime2 = 0;

    SFUserFile[0] = txtSetFileSF2;
    SFUserFile[1] = txtSetFileSF3;

    printc("@ AHC_Fix_UserPartition @\r\n");
    for(TempU32 = 0;TempU32 < 2;TempU32++)
    {
        err = AHC_FS_FileOpen(SFUserFile[TempU32], AHC_StrLen(SFUserFile[TempU32]), "rb", AHC_StrLen("rb"), &ulFileId);
        if(err)
            SFSTS[TempU32] = AHC_FS_ERR_SFUSER_FAIL;
        else
            AHC_FS_FileClose(ulFileId);
    }

    #if(0) //Test Code for partition fail simulation
    if(1)//(u32OSTick % 2)
    {
        SFSTS[0] = AHC_FS_ERR_SFUSER_FAIL;
        RTNA_DBG_Str(0, "SF2=>Bad\r\n");
    }
    else
    {
        SFSTS[1] = AHC_FS_ERR_SFUSER_FAIL;
        RTNA_DBG_Str(0, "SF3=>Bad\r\n");
    }
    #endif
    MMPF_OS_GetTimeMs(&m_ulCurTime1);
    //Backup User Partition for NG-partition
    if( (SFSTS[0] == AHC_ERR_NONE) && (SFSTS[1] == AHC_FS_ERR_SFUSER_FAIL) ){
        //RTNA_DBG_Str(0, "Raw copy SF2 TO SF3\r\n");
        ErrRet = FS_SFLASH_Driver.pfIoCtl(SF2_ACTIVE, FS_CMD_SF_USERCOPY, 0, 0 );
        if(ErrRet)
            RTNA_DBG_Str(0, "Fail=>Raw copy SF2 TO SF3\r\n");
    }
    else if( (SFSTS[0] == AHC_FS_ERR_SFUSER_FAIL) && (SFSTS[1] == AHC_ERR_NONE) ){
        //RTNA_DBG_Str(0, "Raw copy SF3 TO SF2\r\n");
        ErrRet = FS_SFLASH_Driver.pfIoCtl(SF3_ACTIVE, FS_CMD_SF_USERCOPY, 0, 0 );
        if(ErrRet)
            RTNA_DBG_Str(0, "Fail=>Raw copy SF3 TO SF2\r\n");
    }
    else if( (SFSTS[0] == AHC_FS_ERR_SFUSER_FAIL) && (SFSTS[1] == AHC_FS_ERR_SFUSER_FAIL) )
        RTNA_DBG_Str(0, "Both SF:2 & SF:3 NG\r\n");
    MMPF_OS_GetTimeMs(&m_ulCurTime2);
    if(m_ulCurTime2 >= m_ulCurTime1)
    {
        RTNA_DBG_Str(0,"CopyTime:");
        RTNA_DBG_Dec(0,(m_ulCurTime2 - m_ulCurTime1) );
        RTNA_DBG_Str(0,"(ms)\r\n");
    }
    else
    {
        RTNA_DBG_Str(0,"CopyTime:");
        RTNA_DBG_Dec(0,(0xFFFFFFFF - (m_ulCurTime1 - m_ulCurTime2) ) );
        RTNA_DBG_Str(0,"(ms)\r\n");
    }
    #endif
#endif
}

void AHC_Get_ActiveNumber(void)
{
#if (AHC_USER_SFBACKUP)
    UINT32 ActiveNO = 0;//, SFACTNUM[2] = {0};
    AHC_ERR err = 0;
    UINT32  ulFileId = 0, ulActualSize = 0, TempU32 = 0;
    char *SFUserFile[2] = {NULL};

    SFUserFile[0] = ActiveNUMSF2;
    SFUserFile[1] = ActiveNUMSF3;

    //printc("@ AHC_Get_ActiveNumber @\r\n");
    //Get Active Number
    for(TempU32 = 0;TempU32 < 2;TempU32++)
    {
        err = AHC_FS_FileOpen(SFUserFile[TempU32], AHC_StrLen(SFUserFile[TempU32]), "rb", AHC_StrLen("rb"), &ulFileId);
        if(err){
              RTNA_DBG_Str(0, "SF:");
              RTNA_DBG_Dec(0, (TempU32 + 2) );
              RTNA_DBG_Str(0, " access fail\r\n");
              return INVALID_USER_PARTITION;
        }
        else{
            AHC_FS_FileSeek(ulFileId, 0, AHC_FS_SEEK_SET);
            AHC_FS_FileRead(ulFileId,(&ActiveNO),sizeof(ActiveNO),&ulActualSize);
            AHC_FS_FileClose(ulFileId);
            glSFACTNUM[TempU32] = ActiveNO;
        }
    }
    /*
    RTNA_DBG_Str(0, "Active Number=>SF2:");
    RTNA_DBG_Dec(0, glSFACTNUM[0]);
    RTNA_DBG_Str(0, " SF3:");
    RTNA_DBG_Dec(0, glSFACTNUM[1]);
    RTNA_DBG_Str(0, "\r\n");
    */
#endif
}

/* Return SF User-Active-Partition SF2 or SF3 */
void AHC_Assign_ActivePartition(void)
{
#if (AHC_USER_SFBACKUP)
    //printc("@ AHC_Assign_ActivePartition @\r\n");
    if( (glSFACTNUM[0] == 0xFFFFFFFF) || (glSFACTNUM[1] == 0xFFFFFFFF) ) //avoid overflow reassign activenum
    {
        if(glSFACTNUM[1] > glSFACTNUM[0]){
            AHC_Update_ActiveNumber(SF2_ACTIVE, 0);
            AHC_Update_ActiveNumber(SF3_ACTIVE, 1);
            glSFACTNUM[0] = 0;
            glSFACTNUM[1] = 1;
        }
        else{
            AHC_Update_ActiveNumber(SF2_ACTIVE, 1);
            AHC_Update_ActiveNumber(SF3_ACTIVE, 0);
            glSFACTNUM[0] = 1;
            glSFACTNUM[1] = 0;
        }
    }

    if(glSFACTNUM[0] >= glSFACTNUM[1]) //For first pwron or abnormal condition
        ulSFUSERActiveNO = SF2_ACTIVE;
    else
        ulSFUSERActiveNO = SF3_ACTIVE;

    //printc("ulSFUSERActiveNO:%x\r\n",ulSFUSERActiveNO);
#endif
}

/* Return value = AHC_TRUE(FAIL) & AHC_FALSE(OK) */
/* Only apply After the last time Write SF-USER partition */
AHC_BOOL AHC_Update_ActiveNumber(UINT32 SFPartition, UINT32 ActiveNum)
{
#if (AHC_USER_SFBACKUP)
    AHC_ERR err = 0;
    UINT32  ulFileId = 0, ulActualSize = 0;
    char *SFUserFile;

    //printc("@ AHC_Update_ActiveNumber @\r\n");
    if(SFPartition == SF2_ACTIVE)
        SFUserFile = ActiveNUMSF2;
    else if(SFPartition == SF3_ACTIVE)
        SFUserFile = ActiveNUMSF3;

    err = AHC_FS_FileOpen(SFUserFile, AHC_StrLen(SFUserFile), "w", AHC_StrLen("w"), &ulFileId);
    if(err){
        RTNA_DBG_Str(0, SFUserFile);
        RTNA_DBG_Str(0, " access fail \r\n");
        return AHC_TRUE;
    }
    else{
        AHC_FS_FileSeek(ulFileId, 0, AHC_FS_SEEK_SET);
        AHC_FS_FileWrite(ulFileId, (&ActiveNum), sizeof(ActiveNum), &ulActualSize);
        AHC_FS_FileClose(ulFileId);
    }

    return AHC_FALSE;
#endif
}

char* AHC_PARAM_GetPathPrefix(AHC_VALUE_ACCESS_PATH accesspath, UINT8 RWidx)//RWidx: Read(0x01),Write(0x02)
{
    #if (STORAGE_FOR_FACTORY_INFO == INFO_NAND_FLASH)
    switch(accesspath)
    {
        case AHC_DEFAULT_FACTORY_FAT:
            return "SM:3:\\";
        case AHC_DEFAULT_USER_FAT:
            return "SM:5\\";

        case AHC_DEFAULT_FACTORY_RAW:
        case AHC_DEFAULT_USER_RAW:
        default:
            return NULL;
    }
    #elif (STORAGE_FOR_FACTORY_INFO == INFO_SERIAL_FLASH)
    #if(AHC_USER_SFBACKUP)
    if( (RWidx == READIDX) && (ulSFUSERActiveNO == SF2_ACTIVE))
    return "SF:2:\\";
    else if( (RWidx == READIDX) && (ulSFUSERActiveNO == SF3_ACTIVE))
        return "SF:3:\\";
    else if( (RWidx == WRITEIDX) && (ulSFUSERActiveNO == SF2_ACTIVE))
        return "SF:3:\\";
    else if( (RWidx == WRITEIDX) && (ulSFUSERActiveNO == SF3_ACTIVE))
        return "SF:2:\\";
    else
        return "SF:2:\\";
    #else
    return "SF:2:\\";
    #endif
    #else
    switch(accesspath)
    {
        case AHC_DEFAULT_FACTORY_FAT:
            return "SD:3:\\";
        case AHC_DEFAULT_USER_FAT:
            return "SD:3:\\";
        case AHC_DEFAULT_FACTORY_RAW:
        case AHC_DEFAULT_USER_RAW:
        default:
            return NULL;
    }
    #endif
}

AHC_BOOL AHC_PARAM_Menu_Read(UINT8* readback,AHC_VALUE_ACCESS_PATH accesspath)
{
    char*   path    ="SF:1:\\MenuSetting.bin";
    char*   defpath ="SF:1:\\DefaultMenuSetting.bin";
    AHC_ERR err;
    UINT32  ulFileId, ulActualSize;
    #if(AHC_USER_SFBACKUP)
    char *SFUserPart = {NULL};
    #endif

    #if(AHC_USER_SFBACKUP)
    //printc("&1&\r\n");
    //printc("ulSFUSERActiveNO:%x\r\n",ulSFUSERActiveNO);
    #endif

    if(accesspath==AHC_DEFAULT_USER_FAT)
    {
        #if(AHC_USER_SFBACKUP)
        //printc("&2&\r\n");
        if(ulSFUSERActiveNO == SF2_ACTIVE){
            //printc("&3&\r\n");
            SFUserPart = txtSetFileSF2;
        }
        else if(ulSFUSERActiveNO == SF3_ACTIVE){
            //printc("&4&\r\n");
            SFUserPart = txtSetFileSF3;
        }
        else {
            //printc("Error(1):Invlaid SF-USER-Partition\n");
            return AHC_FALSE;
        }
        //printc("+-+-+-+-ParseMenuSet:%s\r\n",SFUserPart);
        #endif

        #if(AHC_USER_SFBACKUP)
        if (ParseMenuSet((char*)SFUserPart, (MenuInfo*)readback, MENU_FILTER_NONE)) {
            return AHC_TRUE;
        }
        #else
        if (ParseMenuSet((char*)txtSetFile, (MenuInfo*)readback, MENU_FILTER_NONE)) {
            return AHC_TRUE;
        }
        #endif

        /* Not find txt file, try to read .bin */
        err = AHC_FS_FileOpen(path, AHC_StrLen(path), "rb", AHC_StrLen("rb"), &ulFileId);
    }
    else if(accesspath==AHC_DEFAULT_FACTORY_FAT)
    {
        #if(AHC_USER_SFBACKUP)
        //printc("&5&\r\n");
        //printc("******++++++ParseMenuSet:%s\r\n",SFUserPart);
        #endif
        if (ParseMenuSet((char*)txtDefFile, (MenuInfo*)readback, MENU_FILTER_NONE)) {
            return AHC_TRUE;
        }
        /* Not find txt file, try to read .bin */
        err = AHC_FS_FileOpen(defpath, AHC_StrLen(defpath), "rb", AHC_StrLen("rb"), &ulFileId);
    }

    if(err) {
        return AHC_FALSE;
    }
    AHC_FS_FileRead(ulFileId,(UINT8 *)readback,sizeof(MenuInfo),&ulActualSize);
    if (err) {
        printc("BIN error\n");
    } else {
        ImportMenuInfo((MenuInfo*)readback);
    }
    AHC_FS_FileClose(ulFileId);
    if(err)
        return AHC_FALSE;
    else
        return AHC_TRUE;
}

AHC_BOOL AHC_PARAM_Menu_WriteEx(char *filename)
{
    ImportMenuInfo(MenuSettingConfig());

    #if defined(TXT_MENU_WRITE_TO_SD)
    ExportMenuAtom((char*)"SD:0:\\usercfg_WriteEx.txt", TXT_COMMENT | TXT_VERSION | TXT_MENU_ACT);
    #endif

    return ExportMenuAtom(filename, TXT_COMMENT | TXT_MENU_ALL | TXT_VERSION);
}

AHC_BOOL AHC_PARAM_Menu_Write(AHC_VALUE_ACCESS_PATH accesspath)
{
    #if(AHC_USER_SFBACKUP)
    char *SFUserPart = {NULL};
    #endif

    MenuSettingConfig()->uiBatteryVoltage = BATTERY_VOLTAGE_FULL;

    // Old way, for debug
    ImportMenuInfo(MenuSettingConfig());

    if (accesspath & AHC_DEFAULT_USER_FAT) {
        #if(AHC_USER_SFBACKUP)
        if(ulSFUSERActiveNO == SF2_ACTIVE)
            SFUserPart = txtSetFileSF3;
        else if(ulSFUSERActiveNO == SF3_ACTIVE)
            SFUserPart = txtSetFileSF2;
        else {
            printc("Error(2):Invlaid SF-USER-Partition\n");
            return AHC_FALSE;
        }
        ExportMenuAtom((char*)SFUserPart, TXT_COMMENT | TXT_MENU_ALL | TXT_VERSION);
        #else
        ExportMenuAtom((char*)txtSetFile, TXT_COMMENT | TXT_MENU_ALL | TXT_VERSION);
        #endif
    }

    #if defined(TXT_MENU_WRITE_TO_SD)
    if (accesspath & AHC_DEFAULT_SD_FILE) {
        ExportMenuAtom((char*)"SD:0:\\usercfg_Write.txt", TXT_COMMENT | TXT_VERSION | TXT_MENU_ACT);
    }
    #endif

    return AHC_TRUE;
}

