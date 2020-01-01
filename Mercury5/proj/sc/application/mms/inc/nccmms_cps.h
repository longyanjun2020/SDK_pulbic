/**
 * @file
 * NCC mms composer Service Layer
 *
 * Service API exposed by the NCC mms composer module
 *
 * <!-- #interface list begin -->
 * \section nccmms_cps Interface
 * - NCCMms_initialize()
 * - NCCMms_getTypeofDrmObject()
 * - NCCMms_setScreenSize()
 * - NCCMms_cps_newMms()
 * - NCCMms_cps_reEditMms()
 * - NCCMms_cps_quit()
 * - NCCMms_cps_curMediaExist()
 * - NCCMms_cps_addImage()
 * - NCCMms_cps_addText()
 * - NCCMms_cps_addAudio()
 * - NCCMms_cps_addVideo()
 * - NCCMms_cps_addSlide()
 * - NCCMms_cps_setCurSlideDuration()
 * - NCCMms_cps_getCurSlideDuration()
 * - NCCMms_cps_deleteCurImage()
 * - NCCMms_cps_deleteCurText()
 * - NCCMms_cps_deleteCurAudio()
 * - NCCMms_cps_deleteCurVideo()
 * - NCCMms_cps_deleteCurSlide()
 * - NCCMms_cps_empty()
 * - NCCMms_cps_goNextSlide()
 * - NCCMms_cps_goPreSlide()
 * - NCCMms_cps_getCurImage()
 * - NCCMms_cps_getCurText()
 * - NCCMms_cps_getCurAudio()
 * - NCCMms_cps_getCurVideo()
 * - NCCMms_cps_getCurSlideIndex()
 * - NCCMms_cps_getTotalSlides()
 * - NCCMms_cps_addAttach()
 * - NCCMms_cps_getTotalAttachment()
 * - NCCMms_cps_getAttach()
 * - NCCMms_cps_delAttach()
 * - NCCMms_cps_getTotalSize()
 * - NCCMms_cps_getMmsContentPdu()
 * - NCCMms_cps_addAutoSign()
 * - NCCMms_cps_deleteAutoSign()
 * <!-- #interface list end -->
 */

#ifndef __NCC_MMS_CPS_H__
#define __NCC_MMS_CPS_H__

#include <ncc_types.h>
#include <nccmms.h>
#ifdef __cplusplus
extern "C" {
#endif

/**
   * ======= CONSTANTS AND MACROS =======
   */

/**
   *    \name Return Values for fnCPS_*** functions.
   */

/*@{*/

/**define the length of MIME TYPE*/
#define MMS_MIME_TYPE_LENGTH                                 0x32
/**Return code that indicates successful completion of an operation*/
#define COMPOSER_SUCCESS                                     0x0
/**Return code that indicates failure completion of allocating memory*/
#define COMPOSER_MEMORY_ALLOC_FAIL                           -1
/**Return code that indicates module's status*/
#define COMPOSER_MODULE_IS_USING                             -2
/**Return code that indicates resource has existed*/
#define COMPOSER_MEDIA_HAS_EXIST                             -3
/**Return code that indicates video has existed*/
#define COMPOSER_MEDIA_EXIST_VIDEO                           -4
/**Return code indicates that audio or image has existed*/
#define COMPOSER_MEDIA_EXIST_IMG_AUD                         -5
/**Return code indicates that slide number has reached to the max slide */
#define COMPOSER_REACH_MAX_SLIDE                             -6
/**Return code indicates that only empty slide in the MMS  */
#define COMPOSER_JUST_ONE_EMPTY_SLIDE                        -7
/**Return code indicates that resource has not existed */
#define COMPOSER_MEDIA_NOT_EXIST                             -8
/**Return code indicates that current slide is the last slide*/
#define COMPOSER_GOTO_THE_END                                -9
/**Return code indicates that current slide is the first slide*/
#define COMPOSER_GOTO_THE_FIRST                              -10
/**Return code indicates that global variable error*/
#define COMPOSER_GLOBE_VAR_ERROR                             -11
/**Return code indicates that input param error */
#define COMPOSER_INPUT_PARAM_ERROR                           -12
/**Return code indicates that current slide is not existed*/
#define COMPOSER_CURRENT_SLIDE_NOT_EXIST                     -13
/**Return code indicates that current error is unknown*/
#define COMPOSER_UNKNOWN_ERROR                               -16
/**Return code indicates that param error */
#define COMPOSER_PARAMETER_ERROR                             -17

/**
 *The following macros will be used by create mode module.
 */
/**Illegal code returned by ComposerCheckMMContentClass functions.*/
#define COMPOSER_MEDIAILLEGAL                                -18
/**Indicates the MMS pdu is oversize relative to current content class.*/
#define COMPOSER_CREATE_MODE_OVERSIZE                        -19
/**Indicates the MMS pdu is restricted by DRM resource,because current content class can not support drm resource.*/
#define COMPOSER_CREATE_MODE_DRMRESTRICTED                   -20
/**Indicates the media type is NULL.*/
#define COMPOSER_CREATE_MODE_MEDIATYPENULL                   -21
/**Init Param Error code returned by fnPAR_CheckPdu functions.*/
#define COMPOSER_CREATE_MODE_INITPARSERERROR                 -22
/**Indicates the operation of parsing MMS that have been existed is incorrect.*/
#define COMPOSER_PARSE_MMS_PDU_ERROR                         -23
/**Indicates the text region is not existed in the MMS that will be reedited.*/
#define COMPOSER_REEDIT_TEXT_REGION_NOT_EXIST                -24
/*Indicates the text region is not correct.*/
#define COMPOSER_REEDIT_TEXT_REGION_ERROR                    -25
/*Indicates the operation of reedit attach is unsuccessful.*/
#define COMPOSER_REEDIT_ATTACH_ERROR                         -26
#define COMPOSER_GET_DRM_MIME_TYPE_ERROR                     -27
#define COMPOSER_REEDIT_REF_ERROR                            -28

/*@}*/

/**
 *define some macros for reedit function.
 */
#define COMPOSER_REEDIT_MMS_WITH_DEFAULT_REGION              0x01 /**<indicates that the received MMS will be reedited with default region.*/
#define COMPOSER_REEDIT_MMS_WITH_APPOINTED_REGION            0x02 /**<indicates that the received MMS will be reedited with the region appointed by MMI.*/

/**
 *define default percent about NO smil.
 */
#define COMPOSER_NO_SMIL_TOP_IMAGE_BELOW_TEXT_IMAGE_DEFALUT_PERCENT 60

/**
   *=======define some macro for content type=======
   */

/**
   *     \name MM Content Type constants
   */

 /*@{ */

/**
   *=======define some macro for text type=======
   */

/**text type string constant:plain*/
#define COMPOSER_TEXT_PLAIN                                  "text/plain"
/**attach type string constant:calendar*/
#define COMPOSER_TEXT_CALENDAR                               "text/x-vCalendar"
/**attach type string constant:vcard*/
#define COMPOSER_TEXT_VCARD                                  "text/x-vCard"

/**
   *=======define some macro for image type=======
   */

/**image type string constant:gif*/
#define COMPOSER_IMAGE_GIF                                   "image/gif"
/**image type string constant:jpeg*/
#define COMPOSER_IMAGE_JPEG                                  "image/jpeg"
/**image type string constant:png*/
#define COMPOSER_IMAGE_PNG                                   "image/png"
/**image type string constant:wbmp*/
#define COMPOSER_IMAGE_WBMP                                  "image/vnd.wap.wbmp"
/**image type string constant:bmp*/
#define COMPOSER_IMAGE_BMP                                    "image/bmp"

/**image type string constant:jpg*/

/**
   *=======define some macro for audio type=======
   */
/**audio type string constant:wav*/
/**audio type string constant:amr*/
#define COMPOSER_AUDIO_AMR                                   "audio/amr"
#define COMPOSER_AUDIO_3GPP                                  "audio/3gpp"
#define COMPOSER_AUDIO_3GPP2                                 "audio/3gpp2"
/**audio type string constant:qcp*/
#define COMPOSER_AUDIO_QCP                                   "audio/vnd.qcelp"

#define COMPOSER_AUDIO_WAV                                   "audio/wav"
#define COMPOSER_AUDIO_XWAV                                  "audio/x-wav"
/**audio type string constant:imelody*/
#define COMPOSER_AUDIO_IMELODY                               "audio/imelody"
/**audio type string constant:mp3*/
#define COMPOSER_AUDIO_MP3                                   "audio/mp3"

#define COMPOSER_AUDIO_MP4                                   "audio/mp4"
#define COMPOSER_AUDIO_X_M4A                                 "audio/x-m4a"
#define COMPOSER_AUDIO_X_M4P                                 "audio/x-m4p"
#define COMPOSER_AUDIO_X_M4B                                 "audio/x-m4b"
#define COMPOSER_AUDIO_AAC                                   "audio/aac"
#define COMPOSER_AUDIO_X_AAC                                 "audio/x-aac"
#define COMPOSER_AUDIO_MPEG                                  "audio/mpeg"
#define COMPOSER_AUDIO_MIDI                                  "audio/midi"
#define COMPOSER_AUDIO_MID                                   "audio/mid"
#define COMPOSER_AUDIO_X_MIDI                                "audio/x-midi"
#define COMPOSER_AUDIO_SP_MIDI                               "audio/sp-midi"

/**
   *=======define some macros for video type=======
   */

/**video type string constant:mpeg*/
#define COMPOSER_VIDEO_3GP                                   "video/3gpp"
/**video type string constant:3gpp2*/
#define COMPOSER_VIDEO_3GPP2                                 "video/3gpp2"
/**video type mp4*/
#define COMPOSER_VIDEO_MP4                                   "video/mp4"
/**video type string constant:mpeg*/
#define COMPOSER_VIDEO_MPEG                                  "video/mpeg"

/**
   *=======define some macros for DRM type=======
   */

/**drm type string constant:message*/
#define COMPOSER_DRM_FORWADLOCK                              "application/vnd.oma.drm.message"
/**drm type string constant:content*/
#define COMPOSER_DRM_DCF                                     "application/vnd.oma.drm.content"

/*@}*/

/**
   *    \name    Text Attribute constant for Text Content
   */

/*@{*/

/**Text Size:small*/
#define COMPOSER_TXTSIZE_SMALL                               "small"
/**Text Size:normal*/
#define COMPOSER_TXTSIZE_NORMAL                              "normal"
/**Text Size:large*/
#define COMPOSER_TXTSIZE_LARGE                               "large"

/** Text attribute:bold*/
#define COMPOSER_TXTATTR_BOLD                                "bold"
/** Text attribute:italic*/
#define COMPOSER_TXTATTR_ITALIC                              "italic"
/** Text attribute:underline*/
#define COMPOSER_TXTATTR_UNDERLINE                           "underline"

/*@}*/

/**
 *    \name    default values for ComposerCreateSmilHead function.
 */

/*@{*/

/**default scale of Text region*/
#define COMPOSER_DEFAULT_TXTREGIONSCALE                      40
/**default scale of Image region*/
#define COMPOSER_DEFAULT_IMGREGIONSCALE                      60
/**default  x coordinate */
#define COMPOSER_DEFAULT_XCO                                 0
/**default  y coordinate */
#define COMPOSER_DEFAULT_YCO                                 0
/**default: not exist*/
#define COMPOSER_DEFAULT_EXIST                               0x0
/**default size of the media resource*/
#define COMPOSER_DEFAULT_LEN                                 0x0

/*@}*/

/**
   *    \name    constants are used by fnCPS_*** functions.
   */

/*@{*/

/**Media Type:Text*/
#define COMPOSER_MEDIA_TEXT                                  0x1
/**Media Type:Image*/
#define COMPOSER_MEDIA_IMAGE                                 0x2
/**Media Type:Audio*/
#define COMPOSER_MEDIA_AUDIO                                 0x3
/**Media Type:Video*/
#define COMPOSER_MEDIA_VIDEO                                 0x4
/**Media Type:Attach*/
#define COMPOSER_MEDIA_ATTACH                                0x5

/*@}*/

/**
   *=======define somes constant macro for create mode module.=======
   */

/**
 *Constant indicates the max length of media filename.
 */
#define COMPOSER_FILENAME_LEN                            100

/**
   *    \name Return values for the creation mode
   */

/*@{*/

/**OK code returned by ComposerCheckMMSize functions.*/
#define COMPOSER_MEDIASIZERIGHT                              0x0
/**OK code returned by NCCMms_par_checkPdu functions.*/
#define COMPOSER_ALLOWFORWARD                                0x0

/**
   *three creation modes are defined as follows:
   *    RESTRICTED:In this mode, a terminal SHALL only create and submit MMs belonging to the Core MM Content Domain.
   *    WARNING:In this mode, a terminal SHALL guide the user to create and submit only MMs belonging to the Core MM Content Domain.
   *             This guidance may, for instance, be implemented as warnings to the user.
   *    FREE:In this mode, a terminal MAY allow the user to add any content to the MM.
   */

/**creation mode:RESTRICTED.*/
#define COMPOSER_RESTRICTED                                  0x0
/**creation mode:WARNING.*/
#define COMPOSER_WARING                                      0x1
/**creation mode:FREE*/
#define COMPOSER_FREE                                        0x2        /**<current create mode is free*/

/**
   *=======MM Content Classes=======
   */

/**Current MM Content Class:Text.*/
#define COMPOSER_TEXTCLASS                                   0x0
/**Current MM Content Class:Image Basic.*/
#define COMPOSER_IMAGEBASIC                                  0x1
/**Current MM Content Class:Image Rich*/
#define COMPOSER_IMAGERICH                                   0x2
/**Current MM Class:Video Basic.*/
#define COMPOSER_VIDEOBASIC                                  0x3
/**Current MM Class:Video Rich.*/
#define COMPOSER_VIDEORICH                                   0x4

/**
   *=======whether to only create and submit MMs belonging to the Core MM Content Domain.=======
   */
 /**only allow to create and submit MMs belonging to the MM Content Domain*/
#define COMPOSER_COREDOMAIN                                  0x01
/**a terminal MAY allow the user to add any content to the MM.*/
#define COMPOSER_EXTENSION                                   0x00

/**
   *=======define media type=======
   */

/**Media Type:Text*/
#define COMPOSER_TEXTMEDIA                                   0x0
/**Media Type:Image*/
#define COMPOSER_IMAGEMEDIA                                  0x1
/**Media Type:Audio*/
#define COMPOSER_AUDIOMEDIA                                  0x2
/**Media Type:Video*/
#define COMPOSER_VIDEOMEDIA                                  0x3
/**The Total Number of Media Type*/
#define COMPOSER_TOTALMEDIA                                  0x4

/**
   *String Constant Array is used by ComposerCheckMMContentClass functions.
   */

/*@}*/

/**
   *=======Data Structures are used by Composer Module=======
   */

/**
   *    \name Structure Types that are used by Composer Module
   */

/*@{*/

    /**
     *  Structured Type that defines Basic information for media resource,it is used by Composer Module
     */
typedef struct MMS_Composer_BasicStructure {
    uint8_t *Buffer;         /**<data point used to save Media Data*/
    int32_t begin;           /**<beginning time used to save beginning time of media play*/
    int32_t end;           /**<ending time of used to save ending time of media play*/
    int32_t size;            /**<the length of media data*/
    int8_t *Type;         /**<the data point used to save media's type*/
} MMS_Composer_BasicStructure;

/**
    *=======Data Structure is used by creation mode=======
    */

    /**
     * structure that indicates some create mode information
     */
typedef struct T_MMS_InitInformation {
    /**
       *MM Content Classes defines as follow:
       *COMPOSER_TEXTCLASS:Text
       *COMPOSER_IMAGEBASIC:ImageBasic
       *COMPOSER_IMAGERICH:ImageRich
       *COMPOSER_VIDEOBASIC:VideoBasic
       *COMPOSER_VIDEORICH:VideoRich
       */
    uint8_t ContentClass;
    /**
       *value that indicates current creation Mode
       *COMPOSER_RESTRICTED:Creation Mode RESTRICTED.
       *COMPOSER_WARING:Creation Mode WARNING.
       *COMPOSER_FREE:Creation Mode FREE.
       */
    uint8_t CreateMode;
    /**
        *values that indicates whether to only allow to create and submit MMs belonging to the Core MM Content Domain.
        *COMPOSER_COREDOMAIN:only allow to create and submit MMs belonging to the Core MM Contetn Domain.
        *COMPOSER_EXTENSION:allow to create and submit any content to MM.
        */
    uint8_t Extension;           /**<0:COMPOSER_COREDOMAIN support CoreDomain    1:COMPOSER_EXTENSION suppor Extension*/
    uint8_t temp;               /**<bit byte align*/
} T_MMS_InitInformation;

    /**
     * Structure Type that defines Screen Size
     */
typedef struct {
    /**value that used to save width of screen*/
    int32_t width;
    /**value that used to save height of screen*/
    int32_t height;
} T_MMS_ScreenSize;

    /**
     * Structure Type that defines Image information,which used to save some information of image resource.
     */
typedef struct T_Composer_Image {
    MMS_Composer_BasicStructure basicatt; /**<used to save some basic information for several medias*/
    uint8_t BGcolor[12];                     /**<used to save the background-color of the Image*/
    MMS_BasicRegion region;                  /**<used to save image's region   */
    int8_t name[100];                    /**<used to save image's name*/
    int32_t warningmode;                /**<used to save used to current create mode */
} T_Composer_Image;

    /**
     * Structure Type that defines Text information,which is used to save some information of Text resource.
     */
typedef struct T_Composer_Text {
    MMS_Composer_BasicStructure basicatt;     /**<used to save some basic information for several medias*/
    uint8_t FG_color[12];                   /**<used to save the foreground-color value of the text*/
    int8_t Textsize[8];                        /**<used to save the size value of the text */
    int8_t Textattribute[12];                /**<used to save the attribute of the text*/
    uint8_t BGcolor[12];                      /**<used to save the background-color of the text*/
    MMS_BasicRegion region;                  /**<used to save text's region  */
    int32_t warningmode;                /**<used to save used to current create mode */
} T_Composer_Text;

    /**
     * Structure Type that defines Audio information,which is used to save some information of Audio resource.
     */
typedef struct T_Composer_Audio {
    MMS_Composer_BasicStructure basicatt; /**<used to save some basic information for several medias*/
    int8_t name[100];                     /**<used to save audio's name*/
    int32_t warningmode;                /**<used to save used to current create mode */
} T_Composer_Audio;

    /**
     * Structure Type that defines Video information,which is used to save some information of Video resource.
     */
typedef struct T_Composer_Video {
    MMS_Composer_BasicStructure basicatt;     /**<used to save some basic information for several medias*/
    MMS_BasicRegion region;                  /**<used to save video's region  */
    int8_t name[100];                     /**<used to save video's name*/
    int32_t warningmode;                /**<used to save used to current create mode */
} T_Composer_Video;

/**
 * attach structure
 */
typedef struct T_Composer_Attach {
    uint8_t *AttBuf;                        /**<used to save attachment data*/
    int8_t *Type;                        /**<used to save attachment's type  */
    int32_t size;                            /**<used to save attachment's size*/
    int8_t *Name;                        /**<used to save attachment's name*/
    int32_t warningmode;                /**<used to save used to current create mode */
} T_Composer_Attach;

/**
* Structure Type that defines read report information,which is used to save some information of read report.
*/
typedef struct T_Composer_ReadReport
{
    int8_t *to;                             /**used to save the address of MM acceptor, using UTF8 code*/
    int8_t *subject;                        /**used to save the subject of MM that was already read , using UTF8 code*/
    int8_t *messID;                         /**used to save the message ID of MM that was already read,  using UTF8 code*/
    int8_t *senttime;                       /**used to save the sent time of MM that was already read, Format: "1/21/2000 1:29 PM"  using UTF8 code*/
    int8_t *readtime;                       /**used to save the read time of MM that was already read, Format: "1/21/2000 2:29 PM" using UTF8 code*/
    int32_t readflag;                       /**used to indicates if the MM have been read,Expected value:true and false*/
}T_Composer_ReadReport;

/*@}*/

/*=============================================================================
 *     API Defines
 *=============================================================================*/

/**
 * Init mms: copy screen and creation mode information from the configuration file into MMS Core
 * \param    *ScreenSize        the size of the Screen
 * \param    *GradeSetting        the information of the Createmode
 * \return    <ul>
 *                <li>when successful, return#COMPOSER_SUCCESS
 *                <li>when fail,return#COMPOSER_PARAMETER_ERROR
 *            </ul>
 */
int32_t NCCMms_initialize(T_MMS_ScreenSize * ScreenSize,
                           T_MMS_InitInformation * GradeSetting);

/**
 * Invoke DRM LIB Function get DRM Object's type
 * \param    *DrmBuf        the data of the DRM object
 * \param     *DrmMIME    DRM MIME TYPE
 * \param    BufSize        the size  of the DRM object
 * \param    *DrmType    the type of the Drm Object
 * \return     <ul>
 *                <li>when successful,return#TRUE.
 *                <li>when fail,return#FALSE.
 *            </ul>
 */
int32_t NCCMms_getTypeofDrmObject(uint8_t * DrmBuf, int8_t * DrmMIME,
                                   uint32_t BufSize, int8_t * DrmType);

/**
 * Set screen size according to configuration information
 * \param    CPSHandle    the handle of the current mms
 * \param    *ScreenSize    the size of the screen
 * \return     <ul>
 *                <li>when successful,return#COMPOSER_SUCCESS
 *                <li>when fail,return#COMPOSER_PARAMETER_ERROR
 *            </ul>
 */
int32_t NCCMms_setScreenSize(MMS_Handle CPSHandle,
                              T_MMS_ScreenSize * ScreenSize);

/**
 * Create a new mms handle,alloc memory space for the MMS Handle
 * \param *CPSHandle    the handle of the mms
 * \return    <ul>
 *                <li>when successful,return#COMPOSER_SUCCESS
 *                <li>when fail,return
 *                    <ul>
 *                        <li>#COMPOSER_MEMERY_ALLOC_FAIL
 *                        <li>#COMPOSER_PARAMETER_ERROR
 *                    </ul>
 *            </ul>
 * \sa    ComposerNewMMStruct
 */
int32_t NCCMms_cps_newMms(MMS_Handle * CPSHandle);

/**
 * Reedit a mms which has existed,fill cur mm's struct with current MM pdu
 * \param    CPSHandle    the handle of the mms
 * \param    *Pdu         the pdu of the mms which we want to reedit
 * \param    Size         the size of the pdu
 * \param    txtregion    pointer of basic region
 * \param    tactic       how to edit (default region or appointed region)
 * \return    <ul>
 *                <li>when successful,return#COMPOSER_SUCCESS
 *                <li>when fail,return
 *                    <ul>
 *                        <li>#COMPOSER_PARAMETER_ERROR
 *                        <li>#COMPOSER_OVERSIZE
 *                        <li>#COMPOSER_UNKNOWN_ERROR
 *                        <li>#COMPOSER_DRMRESTRICTED
 *                        <li>#COMPOSER_INPUT_PARAM_ERROR
 *                    </ul>
 *            </ul>
 */
int32_t NCCMms_cps_reEditMms(MMS_Handle CPSHandle, uint8_t * Pdu, int32_t Size,
                             MMS_BasicRegion * txtregion, int32_t tactic);

/**
 * Clear resource when we quit the composer module,free memory of the CPSHandle
 * \param    *CPSHandle    the handle of the current mms
 * \return    <ul>
 *                <li>when successful,return#COMPOSER_SUCCESS
 *                <li>when fail,return
 *                    <ul>
 *                        <li>#COMPOSER_PARAMETER_ERROR
 *                        <li>#COMPOSER_OVERSIZE
 *                        <li>#COMPOSER_UNKNOWN_ERROR
 *                    </ul>
 *            </ul>
 */
int32_t NCCMms_cps_quit(MMS_Handle * CPSHandle);

/**
 * Judge current media exist or not in the current slide
 * \param    CPSHandle    the handle of the MMS
 * \param    MEDIATYPE    the type of the media
 * \return    <ul>
 *                <li>when successful,return
 *                    <ul>
 *                        <li>#TRUE:current media is exist.
 *                        <li>#FALSE:current media is not exist.
 *                    </ul>
 *            </ul>
 *
 */
int32_t NCCMms_cps_curMediaExist(MMS_Handle CPSHandle, uint32_t MEDIATYPE);

/**
 * Add one image into mms struct
 * \param    CPSHandle    the handle of the mms
 * \param    *Image        the point of the image
 * \return    <ul>
 *                <li>when successful,return#COMPOSER_SUCCESS
 *                <li>when fail,return
 *                    <ul>
 *                        <li>#COMPOSER_INPUT_PARAM_ERROR
 *                        <li>#COMPOSER_MEDIA_EXIST_VIDEO
 *                        <li>#COMPOSER_MEDIA_HAS_EXIST
 *                        <li>#COMPOSER_MEMERY_ALLOC_FAIL
 *                        <li>#COMPOSER_GLOBE_VAR_ERROR
 *                    </ul>
 *            </ul>
 * \sa    NCCMms_cps_curMediaExist
 */
int32_t NCCMms_cps_addImage(MMS_Handle CPSHandle, T_Composer_Image * Image);

/**
 * Add text object into mms struct
 * \param    CPSHandle    the handle of the mms
 * \param    *Text        the point of the Text object
 * \return <ul>
 *                <li>when successful,return#COMPOSER_SUCCESS
 *                <li>when fail,return
 *                    <ul>
 *                        <li>#COMPOSER_INPUT_PARAM_ERROR
 *                        <li>#COMPOSER_MEMERY_ALLOC_FAIL
 *                        <li>#COMPOSER_GLOBE_VAR_ERROR
 *                    </ul>
 *            </ul>
 * \sa    NCCMms_cps_curMediaExist
 */
int32_t NCCMms_cps_addText(MMS_Handle CPSHandle, T_Composer_Text * Text);

/**
 * Add audio object into mms struct
 * \param    CPSHandle    the handle of the mms
 * \param    *Audio        the point of the Audio object
 * \return <ul>
 *                <li>when successful,return#COMPOSER_SUCCESS
 *                <li>when fail,return
 *                    <ul>
 *                        <li>#COMPOSER_INPUT_PARAM_ERROR
 *                        <li>#COMPOSER_MEDIA_EXIST_VIDEO
 *                        <li>#COMPOSER_MEDIA_HAS_EXIST
 *                        <li>#COMPOSER_MEMERY_ALLOC_FAIL
 *                        <li>#COMPOSER_GLOBE_VAR_ERROR
 *                    </ul>
 *            </ul>
 * \sa    NCCMms_cps_curMediaExist
 */
int32_t NCCMms_cps_addAudio(MMS_Handle CPSHandle, T_Composer_Audio * Audio);

/**
 * Add video object into mms struct
 * \param    CPSHandle    the handle of the mms
 * \param    *Video        the point of the Video object
 * \return <ul>
 *                <li>when successful,return#COMPOSER_SUCCESS
 *                <li>when fail,return
 *                    <ul>
 *                        <li>#COMPOSER_INPUT_PARAM_ERROR
 *                        <li>#COMPOSER_MEDIA_EXIST_IMG_AUD
 *                        <li>#COMPOSER_MEDIA_HAS_EXIST
 *                        <li>#COMPOSER_MEMERY_ALLOC_FAIL
 *                        <li>#COMPOSER_GLOBE_VAR_ERROR
 *                    </ul>
 *            </ul>
 * \sa    NCCMms_cps_curMediaExist
 */
int32_t NCCMms_cps_addVideo(MMS_Handle CPSHandle, T_Composer_Video * Video);

/**
 * Add a new empty slide behind current slide
 * \param    CPSHandle    the handle of the current mms
 * \return    <ul>
 *                <li>when successful,return#COMPOSER_SUCCESS
 *                <li>when fail,return
 *                    <ul>
 *                        <li>#COMPOSER_INPUT_PARAM_ERROR
 *                        <li>#COMPOSER_REACH_MAX_SLIDE
 *                        <li>#COMPOSER_GLOBE_VAR_ERROR
 *                    </ul>
 *            </ul>
 */
int32_t NCCMms_cps_addSlide(MMS_Handle CPSHandle);

/**
 * Set current slide's delay time
 * \param    CPSHandle    the handle of the MMS
 * \param    delay        the delay time
 * \return    <ul>
 *                <li>when successful,return#COMPOSER_SUCCESS
 *                <li>when fail,return#COMPOSER_INPUT_PARAM_ERROR
 *            </ul>
 */
int32_t NCCMms_cps_setCurSlideDuration(MMS_Handle CPSHandle, int32_t delay);

/**
 * Get current slide's delay time
 * \param    CPSHandle    the handle of the MMS
 * \return    <ul>
 *                <li>when successful,return#delay
 *                <li>when fail,return#COMPOSER_INPUT_PARAM_ERROR
 *            </ul>
 */
int32_t NCCMms_cps_getCurSlideDuration(MMS_Handle CPSHandle);

/**
 * Delete current slide's image from current slide's struct
 * \param CPSHandle        the handle of the mms
 * \return    <ul>
 *                <li>when successful,return#COMPOSER_SUCCESS
 *                <li>when fail,return
 *                    <ul>
 *                        <li>#COMPOSER_INPUT_PARAM_ERROR
 *                        <li>#COMPOSER_MEDIA_NOT_EXIST
 *                    </ul>
 *            </ul>
 */
int32_t NCCMms_cps_deleteCurImage(MMS_Handle CPSHandle);

/**
 * Delete current slide's Text from current slide's struct
 * \param CPSHandle        the handle of the mms
 * \return    <ul>
 *                <li>when successful,return#COMPOSER_SUCCESS
 *                <li>when fail,return
 *                    <ul>
 *                        <li>#COMPOSER_INPUT_PARAM_ERROR
 *                        <li>#COMPOSER_MEDIA_NOT_EXIST
 *                    </ul>
 *            </ul>
 */
int32_t NCCMms_cps_deleteCurText(MMS_Handle CPSHandle);

/**
 * Delete current slide's Audio from current slide's struct
 * \param CPSHandle        the handle of the mms
 * \return    <ul>
 *                <li>when successful,return#COMPOSER_SUCCESS
 *                <li>when fail,return
 *                    <ul>
 *                        <li>#COMPOSER_INPUT_PARAM_ERROR
 *                        <li>#COMPOSER_MEDIA_NOT_EXIST
 *                    </ul>
 *            </ul>
 */
int32_t NCCMms_cps_deleteCurAudio(MMS_Handle CPSHandle);

/**
 * Delete current slide's Video from current slide's struct
 * \param CPSHandle        the handle of the mms
 * \return    <ul>
 *                <li>when successful,return#COMPOSER_SUCCESS
 *                <li>when fail,return
 *                    <ul>
 *                        <li>#COMPOSER_INPUT_PARAM_ERROR
 *                        <li>#COMPOSER_MEDIA_NOT_EXIST
 *                    </ul>
 *            </ul>
 */
int32_t NCCMms_cps_deleteCurVideo(MMS_Handle CPSHandle);

/**
 * Delete current slide from the current mms from current mm's struct
 * \param CPSHandle        the handle of the mms
 * \return    <ul>
 *                <li>when successful,return#COMPOSER_SUCCESS
 *                <li>when fail,return#COMPOSER_INPUT_PARAM_ERROR
 *            </ul>
 * \sa    NCCMms_cps_deleteCurAudio NCCMms_cps_deleteCurVideo NCCMms_cps_deleteCurImage NCCMms_cps_deleteCurText
 */
int32_t NCCMms_cps_deleteCurSlide(MMS_Handle CPSHandle);

/**
 * Clear current composer module,free the memory of the CPSHandle
 * \param    CPSHandle    the handle of the current mms
 * \return    void
*/
void NCCMms_cps_empty(MMS_Handle CPSHandle);

/**
 * Goto the next slide from the current slide
 * \param    CPSHandle    the handle of the current mms
 * \return    <ul>
 *                <li>when successful,return#COMPOSER_SUCCESS
 *                <li>when fail,return
 *                    <ul>
 *                        <li>#COMPOSER_GOTO_THE_END
 *                        <li>#COMPOSER_INPUT_PARAM_ERROR
 *                    </ul>
 *            </ul>
 */
int32_t NCCMms_cps_goNextSlide(MMS_Handle CPSHandle);

/**
 * Goto the previous slide from the current slide
 * \param    CPSHandle    the handle of the current mms
 * \return    <ul>
 *                <li>when successful,return#COMPOSER_SUCCESS
 *                <li>when fail,return
 *                    <ul>
 *                        <li>#COMPOSER_GOTO_THE_FIRST
 *                        <li>#COMPOSER_INPUT_PARAM_ERROR
 *                    </ul>
 *            </ul>
 */
int32_t NCCMms_cps_goPreSlide(MMS_Handle CPSHandle);

/**
 * Get current slide's image information and save the data into *Image
 * \param    CPSHandle    the handle of the mms
 * \param    *Image        the point of the Image
 * \return    <ul>
 *                <li>when successful,return#COMPOSER_SUCCESS
 *                <li>when fail,return
 *                    <ul>
 *                        <li>#COMPOSER_INPUT_PARAM_ERROR
 *                        <li>#COMPOSER_MEDIA_NOT_EXIST
 *                    </ul>
 *            </ul>
 * \sa    NCCMms_cps_curMediaExist
 */
int32_t NCCMms_cps_getCurImage(MMS_Handle CPSHandle, T_Composer_Image * Image);

/**
 * Get current slide's text information and save the data into *Text
 * \param    CPSHandle    the handle of the mms
 * \param    *Text        the point of the Text
 * \return    <ul>
 *                <li>when successful,return#COMPOSER_SUCCESS
 *                <li>when fail,return
 *                    <ul>
 *                        <li>#COMPOSER_INPUT_PARAM_ERROR
 *                        <li>#COMPOSER_MEDIA_NOT_EXIST
 *                    </ul>
 *            </ul>
 * \sa    NCCMms_cps_curMediaExist
 */
int32_t NCCMms_cps_getCurText(MMS_Handle CPSHandle, T_Composer_Text * Text);

/**
 * Get current slide's Audio information and save the data into *Audio
 * \param    CPSHandle    the handle of the mms
 * \param    *Audio        the point of the Audio
 * \return    <ul>
 *                <li>when successful,return#COMPOSER_SUCCESS
 *                <li>when fail,return
 *                    <ul>
 *                        <li>#COMPOSER_INPUT_PARAM_ERROR
 *                        <li>#COMPOSER_MEDIA_NOT_EXIST
 *                    </ul>
 *            </ul>
 * \sa    NCCMms_cps_curMediaExist
 */
int32_t NCCMms_cps_getCurAudio(MMS_Handle CPSHandle, T_Composer_Audio * Audio);

/**
 * Get current slide's video information and save the data into *Video
 * \param    CPSHandle    the handle of the mms
 * \param    *Video        the point of the Video
 * \return    <ul>
 *                <li>when successful,return#COMPOSER_SUCCESS
 *                <li>when fail,return
 *                    <ul>
 *                        <li>#COMPOSER_INPUT_PARAM_ERROR
 *                        <li>#COMPOSER_MEDIA_NOT_EXIST
 *                    </ul>
 *            </ul>
 * \sa    NCCMms_cps_curMediaExist
 */
int32_t NCCMms_cps_getCurVideo(MMS_Handle CPSHandle, T_Composer_Video * Video);

/**
 * Get the index of the current slide
 * \param    CPSHandle    the handle of the current mms
 * \return    <ul>
 *                <li>when successful,return#the index of current slide
 *                <li>when fail,return#COMPOSER_INPUT_PARAM_ERROR
 *            </ul>
 */
int32_t NCCMms_cps_getCurSlideIndex(MMS_Handle CPSHandle);

/**
 * Get the slide number of the current mms
 * \param    CPSHandle    the handle of the current mms
 * \return    <ul>
 *                <li>when successful,return#the number of slides
 *                <li>when fail,return#COMPOSER_INPUT_PARAM_ERROR
 *            </ul>
 */
int32_t NCCMms_cps_getTotalSlides(MMS_Handle CPSHandle);

/**
 * Add a attach into the current mms
 * \param    CPSHandle    the handle of the mms
 * \param    *Attach        the point of attach resource
 * \return    <ul>
 *                <li>when successful,return#COMPOSER_SUCCESS
 *                <li>when fail,return
 *                    <ul>
 *                        <li>#COMPOSER_INPUT_PARAM_ERROR
 *                        <li>#COMPOSER_MEMERY_ALLOC_FAIL
 *                        <li>#COMPOSER_UNKNOWN_ERROR
 *                    </ul>
 *            </ul>
 */
int32_t NCCMms_cps_addAttach(MMS_Handle CPSHandle, T_Composer_Attach * Attach);

/**
 * Get the number of the current mms's attachment
 * \param    CPSHandle    the handle of the mms
 * \return    <ul>
 *                <li>when successful,return#the total number of the attachment
 *                <li>when fail,return#COMPOSER_INPUT_PARAM_ERROR
 *            </ul>
 */
int32_t NCCMms_cps_getTotalAttachment(MMS_Handle CPSHandle);

/**
 * Get attach from the current mms and save the data into *Attach
 * \param    CPSHandle    the handle of the mms
 * \param    Pos            the index of the attach which we want to get
 * \param    *Attach        the point of attach.
 * \return    <ul>
 *                <li>when successful,return#COMPOSER_SUCCESS
 *                <li>when fail,return
 *                    <ul>
 *                        <li>#COMPOSER_MEDIA_NOT_EXIST
 *                        <li>#COMPOSER_INPUT_PARAM_ERROR
 *                    </ul>
 *            </ul>
 */
int32_t NCCMms_cps_getAttach(MMS_Handle CPSHandle, int32_t Pos,
                             T_Composer_Attach * Attach);

/**
 * Del attach from the current mms
 * \param    CPSHandle    the handle of the mms
 * \param    *name        the point of the attach's name
 * \return    <ul>
 *                <li>when successful,return#COMPOSER_SUCCESS
 *                <li>when fail,return
 *                    <ul>
 *                        <li>#COMPOSER_MEDIA_NOT_EXIST
 *                        <li>#COMPOSER_INPUT_PARAM_ERROR
 *                    </ul>
 *            </ul>
 */
int32_t NCCMms_cps_delAttach(MMS_Handle CPSHandle, int8_t * name);

/**
 * Get the size of the current mms
 * \param    CPSHandle        the handle of the mms
 * \return    <ul>
 *                <li>when successful,return#the size of new mm
 *                <li>when fail,return#COMPOSER_INPUT_PARAM_ERROR
 *            </ul>
 */
int32_t NCCMms_cps_getTotalSize(MMS_Handle CPSHandle);

/**
 * Get the pdu of the current mms and return the size of the pdu and pdu
 * \param    CPSHandle    the handle of the MMS
 * \param    *Size        the size of the mms
 * \return    <ul>
 *                <li>when successful,return#pdu
 *                <li>when fail,return#NULL
 *            </ul>
 * \sa fnMMS_MakeContentBodyPdu. CRTL_free
 */
uint8_t *NCCMms_cps_getMmsContentPdu(MMS_Handle CPSHandle, int32_t * Size);

/**
* Create the body of MM Read report and return the size of the PDU and length
* \param    Readreport    the point of the MM read report info
* \param    *Size        the size of the MM read report's body
* \return    <ul>
*                <li>when successful,return#COMPOSER_SUCCESS
*                <li>when fail,return
*                    <ul>
*                        <li>#COMPOSER_MEMORY_ALLOC_FAIL
*                        <li>#COMPOSER_INPUT_PARAM_ERROR
*                        <li>#COMPOSER_GLOBE_VAR_ERROR
*                        <li>#COMPOSER_UNKNOWN_ERROR
*                    </ul>
*            </ul>
* \sa NCCMms_cps_getReadReportBody. CRTL_free
*/
int32_t NCCMms_cps_getReadReportBody(T_Composer_ReadReport *Readreport,uint8_t **pdu,int32_t * Size);

/**
 * Add a text of sign in last slide
 * \param    CPSHandle    the handle of the mms
 * \param    *Image        the point of the Image
 * \param    *Text        the point of the Text
 * \param    *Audio        the point of the Audio
 * \return    <ul>
 *                <li>when successful,return#COMPOSER_SUCCESS
 *                <li>when fail,return#COMPOSER_INPUT_PARAM_ERROR
 *            </ul>
 * \sa    NCCMms_cps_goNextSlide NCCMms_cps_addSlide NCCMms_cps_addImage NCCMms_cps_addText NCCMms_cps_addAudio
 */
int32_t NCCMms_cps_addAutoSign(MMS_Handle CPSHandle, T_Composer_Image * Image,
                               T_Composer_Text * Text,
                               T_Composer_Audio * Audio);

/**
 * Delete a text of sign in last slide
 * \param    CPSHandle    the handle of the current mms
 *
 * \return    <ul>
 *                <li>when success,return#COMPOSER_SUCCESS
 *                <li>when fail,return#COMPOSER_INPUT_PARAM_ERROR
 *            </ul>
 * \sa    NCCMms_cps_deleteCurSlide NCCMms_cps_goNextSlide
 */
int32_t NCCMms_cps_deleteAutoSign(MMS_Handle CPSHandle);

#ifdef MMS_SUPPORT_JSR205
/**
*Encode the MMS body into the pdu
* \param    CPSHandle    The handle of MMS.
*  \param  *appId  the pointer of application-id parameter for content-type field.
*  \param  *replyToAppId   the pointer of Reply-To-Application-Id  parameter for content-type field.
* \param    *pLength     An integer to save the length of pdu.
*
* \return <ul>
*             <li>Success,return#An pointer to specify the content pdu.
*             <li>Otherwise,return#NULL
*         </ul>
*/
uint8_t *NCCMms_cps_GetSmilMmsContentPduWithAppId(MMS_Handle CPSHandle,
                                                  uint8_t *appId,
                                                  uint8_t *replyToAppId,
                                                  uint8_t *startContentId,
                                                  int32_t *pLength);

uint8_t *NCCMms_cps_GetNoSmilMmsContentPduWithAppId(MMS_Handle CPSHandle,
                                                    uint8_t *appId,
                                                    uint8_t *replyToAppId,
                                                    int32_t *pLength);
#endif

#ifdef __cplusplus
}
#endif

#endif /* __NCC_MMS_CPS_H__ */
