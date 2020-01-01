/**
 * @file
 * NCC mms parser Service Layer
 *
 * Service API exposed by the parser module of NCC mms
 *
 * <!-- #interface list begin -->
 * \section nccmms_par Interface
 * - NCCMms_par_checkPdu()
 * - NCCMms_par_smilParserEntry()
 * - NCCMms_par_smilFree()
 * - NCCMms_par_initCurPar()
 * - NCCMms_par_proceedNextPar()
 * - NCCMms_par_proceedPrePar()
 * - NCCMms_par_getCurParImg()
 * - NCCMms_par_getCurParText()
 * - NCCMms_par_getCurParAudio()
 * - NCCMms_par_getCurParVideo()
 * - NCCMms_par_getCurParRef()
 * - NCCMms_par_getCurParDur()
 * - NCCMms_par_isParEmpty()
 * - NCCMms_par_getTotalAttach()
 * - NCCMms_par_getAttach()
 * <!-- #interface list end -->
 */

#ifndef __NCC_MMS_PAR_H__
#define __NCC_MMS_PAR_H__

#include <ncc_types.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
    *if user adopt DRM product of NCC ,please open following macro.
    */

/**
   *    \name define macros for some functions which are defined in  the C run-time libraries.
   */

/*@{*/

/* /\**The _stricmp function lexicographically compares lowercase versions of string1 and string2 and returns a value indicating their relationship*\/ */
#define MMS_STRICMP                                          MMS_Stricmp

/*@}*/

/**end tag of string*/
#define MMS_END_TAG                                          '\0'
/**the int constant that indicates the length of the bgcolor*/
#define MMS_BGCOLOR_LEN                                      0xC

/**MMS information structure*/
typedef struct T_MMS_HANDLE *MMS_Handle;

/**tag of charset type*/
/**
   *    \name   constant value that indicates charset type.
   */

/*@{*/

#define MMS_CHARSET_UTF8                                     0x6A   /**<current string is  UTF-8 code */
#define MMS_CHARSET_ASCII                                    0x03   /**<current string is us_ASCII code*/
#define MMS_CHARSET_GB2312                                   0x07E9 /**<current string is gb2312 code*/
/*@}*/

/**
 * one filed of the root-layout
 */
enum MMS_Region_Fit_Value {
    MMS_REGION_FIT_FILL = 0,        /**<Scale the object's height and width independently so that the content just touches all edges of the box*/
    MMS_REGION_FIT_HIDDEN,      /**<Has the following effect:
                                        If the intrinsic height (width) of the media object element is smaller than the height (width) defined in the region element,
                                            render the object starting from the top (left) edge and fill up the remaining height (width) with the background color.
                                        If the intrinsic height (width) of the media object element is greater than the height (width) defined in the region element,
                                            render the object starting from the top (left) edge until the height (width) defined in the region element is reached, and clip the parts of the object below (right of) the height (width). */
    MMS_REGION_FIT_MEET,            /**<Scale the visual media object while preserving its aspect ratio until its height or width is equal to the value specified by the
                                            height or width attributes, while none of the content is clipped. The object's left top corner is positioned at the top-left
                                            coordinates of the box, and empty space at the right or bottom is filled up with the background color*/
    MMS_REGION_FIT_SCROLL,      /**<A scrolling mechanism should be invoked when the element's rendered contents exceed its bounds*/
    MMS_REGION_FIT_SLICE            /**<Scale the visual media object while preserving its aspect ratio so that its height or width are equal to the value specified
                                            by the height and width attributes while some of the content may get clipped. Depending on the exact situation,
                                            either a horizontal or a vertical slice of the visual media object is displayed. Overflow width is clipped from the right of
                                            the media object. Overflow height is clipped from the bottom of the media object*/
};

/**
 * Structure Type that indicates region value.
 */
typedef struct _Parser_PosTp {
    int32_t xco;                    /**<Xcoordinate*/
    int32_t yco;                    /**<Ycoordinate*/
    int32_t width;                  /**<display width */
    int32_t height;                 /**<display height*/
    enum MMS_Region_Fit_Value fit;
} MMS_BasicRegion;


    /*
     *
     *
     *
     *
     */


/**
   *=======Structured types that are used by parse module=======
   */

/**
   *    \name   define some structs that will be used by fnPAR_*** functions.
   */

/*@{*/

/**
 * Structure for parser module
 */
typedef struct MMS_Parser_BasicStructure {
    uint8_t *Buf;   /**< the basic string of the basic element */
    int8_t *Alt;        /**< the alt value of the basic element  */
    int32_t Size;   /**<the length of the basic element*/
    int32_t Begin;      /**< the begin time of the basic  element */
    int32_t End;        /**< the end time of the basic element*/
    int8_t *Type;   /**<the type of the basic element*/
    int8_t *Name;
} T_MMS_Parser_BasicStructure;

/**
 * Structure Type that defines some information of image resource.
 */
typedef struct T_SMIL_ImgStruct {           /**<record image info of MMS display which is in process*/
    MMS_BasicRegion graphPos;               /**<image display position ,may be needless*/
    T_MMS_Parser_BasicStructure ImageStruct;    /**<the common attribute and other media */
    uint8_t BGcolor[12];                        /**<the background-color of the Image*/
} T_SMIL_ImgStruct;

/**
 * Structure Type that defines some information of video resource.
 */
typedef struct T_SMIL_VideoStruct {         /**<record video info of MMS display which is in process*/
    MMS_BasicRegion VideoPos;               /**<video display position ,may be needless*/
    T_MMS_Parser_BasicStructure VideoStruct;    /**<the common attribute and other media*/
} T_SMIL_VideoStruct;

/**
 * Structure Type that defines some information of DRM resource.
 */
typedef struct T_SMIL_RefStruct {
    MMS_BasicRegion RefPos;                     /**< ref display position ,may be needless*/
    T_MMS_Parser_BasicStructure RefStruct;      /**<the basic attribute of the Ref*/
} T_SMIL_RefStruct;

/**
 * Structure Type that defines some information of Text resource.
 */
typedef struct T_SMIL_TextStruct {
    MMS_BasicRegion txtPos;                     /**<text show position ,may be need less*/
    T_MMS_Parser_BasicStructure TextStruct;     /**<the basic attribute of the Text*/
    uint8_t FG_color[12];                       /**<the foreground-color value of the text*/
    int8_t Textsize[8];                         /**<the size value of the text */
    int8_t Textattribute[12];                   /**<the attribute of the text*/
    uint8_t BGcolor[12];                        /**<the background-color of the text*/
} T_SMIL_TextStruct;

/**
 * Structure Type that defines some information of Audio resource.
 */
typedef struct T_SMIL_AudStruct {
    T_MMS_Parser_BasicStructure AudioStruct;    /**<the basic attribute of the Audio*/
} T_SMIL_AudStruct;

/**
 * Structure Type that defines some information of Attach resource.
 */
typedef struct T_MMS_Attach {
    uint8_t *AttBuf;                            /**<attachment data buffer*/
    int8_t *Type;                           /**< attchment  type  */
    int8_t *Name;                           /**< attchment name  */
    int32_t size;                               /**<size of attchment data*/
} T_MMS_Attach;

/**
 * Structure Type that defines some information of Text Element.
 */
typedef struct _Parser_Text {
    T_MMS_Parser_BasicStructure TextStruct;     /**<the basic attribute of the text*/
    uint8_t FG_color[12];                   /**<the foreground-color value of the text*/
    int8_t Textsize[8];                         /**<the size value of the text */
    int8_t Textattribute[12];                   /**<the attribute of the text*/
    uint8_t BGcolor[MMS_BGCOLOR_LEN];       /**<the background-color of the text*/
    MMS_BasicRegion Pos;                    /**<the position info the text element   */
    struct _Parser_Text *Next;                  /**<the next text element struct pointer */
} T_Parser_Text;

/**
 * Structure Type that defines some information of image Element.
 */
typedef struct _Parser_Image {
    T_MMS_Parser_BasicStructure ImageStruct;    /**<the basic attribute of the image*/
    uint8_t BGcolor[MMS_BGCOLOR_LEN];       /**<the background-color of the Image*/
    MMS_BasicRegion Pos;                    /**< the position info of the image  */
    struct _Parser_Image *Next;                 /**< the next image element struct   */
} T_Parser_Image;

/**
 * Structure Type that defines some information of audio element.
 */
typedef struct _Parser_Audio {
    T_MMS_Parser_BasicStructure AudioStruct;    /**<the basic attribute of the audio*/
    struct _Parser_Audio *Next;             /**< the next audio struct  */
} T_Parser_Audio;

/**
 * Structure Type that defines some information of video element.
 */
typedef struct _Parser_Video {
    T_MMS_Parser_BasicStructure VideoStruct;    /**<the basic attribute of the video*/
    MMS_BasicRegion Pos;                    /**< the position info the text element   */
    uint8_t BGcolor[MMS_BGCOLOR_LEN];       /**<the background-color of the Video*/
    struct _Parser_Video *Next;                 /**< the next video struct  */
} T_Parser_Video;

/**
 * Structure Type that defines some information of attach element.
 */
typedef struct T_Parser_Attach {
    uint8_t *AttBuf;                            /**<attach data buffer*/
    int8_t *Type;                           /**< attach type  */
    int8_t *Name;                           /**< attach name  */
    int32_t size;                               /**<size of attachment data*/
    struct T_Parser_Attach *next;               /**<the point of next struct*/
} T_Parser_Attach;

/**
 * Structure Type that defines some information of DRM element.
 */
typedef struct _Parser_Ref {
    T_MMS_Parser_BasicStructure RefStruct;      /**<the basic attribute of the ref*/
    MMS_BasicRegion Pos;                    /**< the position info of the ref*/
    struct _Parser_Ref *Next;                   /**< the next ref element struct   */
} T_Parser_Ref;

/*@}*/

/**
   *=======define some API that are used by parse module=======
   */

/**
   *    \name   define some API that are used by parse module
   */

/*@{*/

/**
 * Used to check MMS pdu which we will forward
 * \param  *pBodyPdu       the point of the pdu
 * \param  length          the length of the pdu
 * \return <ul>
 *              <li> #COMPOSER_ALLOWFORWARD     if success
 *              <li> if fail,return
 *                  <ul>
 *                      <li>#COMPOSER_INITPARSERERROR
 *                      <li>#COMPOSER_OVERSIZE
 *                      <li>#COMPOSER_MEDIAILLEGAL
 *                      <li>#COMPOSER_DRMRESTRICTED
 *                      <li>#TRUE(forbiden to forward)
 *                  </ul>
 *          </ul>
 */
int32_t NCCMms_par_checkPdu(uint8_t * pBodyPdu, int32_t length);

/**
 * The entry of MMS parser module.It used to parse SMIL PDU.
 * \param  *MMSHandle      the point of the mms structure
 * \param  *pBodyPdu       the point of the pdu
 * \param  length          the lenth of the pdu
 * \return <ul>
 *             <li> #TRUE   if successful
 *             <li> #FALSE  if failed
 *         </ul>
 */
int32_t NCCMms_par_smilParserEntry(MMS_Handle * MMSHandle, uint8_t * pBodyPdu,
                                   int32_t length);

/**
 * Free the memory which is used by smil
 * \param  *MMSHandle      the point of new mm
 * \return <ul>
 *             <li> #TRUE   if successful
 *             <li> #FALSE  if failed
 *         </ul>
 */
int32_t NCCMms_par_smilFree(MMS_Handle * MMSHandle);

/**
 * Init current page of MMS data which will be previewed
 * \param  MMSHandle   the struct of the new mm
 * \return <ul>
 *             <li> #TRUE   if successful
 *             <li> #FALSE  if failed
 *         </ul>
 */
int32_t NCCMms_par_initCurPar(MMS_Handle MMSHandle);

/**
 * Go to  next slide of MMS data which will be previewed
 * \param  MMSHandle   the struct of the new mm
 * \return <ul>
 *             <li> #TRUE   if successful
 *             <li> #FALSE  if failed
 *         </ul>
 */
int32_t NCCMms_par_proceedNextPar(MMS_Handle MMSHandle);

/**
 * Go to  prior slide of MMS data which will be previewed
 * \param  MMSHandle   the struct of the new mm
 * \return <ul>
 *             <li> #TRUE   if successful
 *             <li> #FALSE  if failed
 *         </ul>
 */
int32_t NCCMms_par_proceedPrePar(MMS_Handle MMSHandle);

/**
 * Get image data from cur par and save the data into *CurImg
 * \param  MMSHandle   the struct of the mms
 * \param  *CurImg     the point of the image
 * \return <ul>
 *             <li> #TRUE   if successful
 *             <li> #FALSE  if failed
 *         </ul>
 */
int32_t NCCMms_par_getCurParImg(MMS_Handle MMSHandle,
                                T_SMIL_ImgStruct * CurImg);

/**
 * Get text data from current slide of MMS  and save the data into *CurTxt
 * \param  MMSHandle   the struct of the mms
 * \param  *CurTxt     the point of the Text
 * \return <ul>
 *             <li> #TRUE   if successful
 *             <li> #FALSE  if failed
 *         </ul>
 */
int32_t NCCMms_par_getCurParText(MMS_Handle MMSHandle,
                                 T_SMIL_TextStruct * CurTxt);

/**
 * Get audio data from current slide of MMS and save the data into *CurAud
 * \param  MMSHandle   the struct of the mms
 * \param  *CurAud     the point of the Audio
 * \return <ul>
 *             <li> #TRUE   if successful
 *             <li> #FALSE  if failed
 *         </ul>
 */
int32_t NCCMms_par_getCurParAudio(MMS_Handle MMSHandle,
                                  T_SMIL_AudStruct * CurAud);

/**
 * Get Video data from current slide of MMS and save the data into CurVideo
 * \param  MMSHandle   the struct of the mms
 * \param  *CurVideo   the point of the Video
 * \return <ul>
 *             <li> #TRUE   if successful
 *             <li> #FALSE  if failed
 *         </ul>
 */
int32_t NCCMms_par_getCurParVideo(MMS_Handle MMSHandle,
                                  T_SMIL_VideoStruct * CurVideo);

/**
 * Get Ref data from current slide of MMS and save the data into *CurRef
 * \param  MMSHandle   the struct of the mms
 * \param  *CurRef     the point of the Ref
 * \return <ul>
 *             <li> #TRUE   if successful
 *             <li> #FALSE  if failed
 *         </ul>
 */
int32_t NCCMms_par_getCurParRef(MMS_Handle MMSHandle,
                                T_SMIL_RefStruct * CurRef);

/**
 * Get time duration during one page of MMS preview
 * \param  MMSHandle   the struct of the mms
 * \return <ul>
 *             <li> the dur time of the slide .micro second if successful
 *             <li> #FALSE                  if failed
 *         </ul>
 */
int32_t NCCMms_par_getCurParDur(MMS_Handle MMSHandle);

/**
 * Judge  the current slide of MMS preview is empty
 * \param  MMSHandle   the struct of new mm
 * \return <ul>
 *             <li> #TRUE   if successful
 *             <li> #FALSE  if failed
 *         </ul>
 */
int32_t NCCMms_par_isParEmpty(MMS_Handle MMSHandle);

/**
 * Get the total number of the Attachment
 * \param  MMSHandle       the struct of the mms
 * \return <ul>
 *             <li> total number of attachments     if successful
 *             <li> #FALSE              if failed
 *         </ul>
 */
int32_t NCCMms_par_getTotalAttach(MMS_Handle MMSHandle);

/**
 * Get attachment data
 * \param  MMSHandle       the struct of the mms
 * \param  Pos             the position of the attachment which we will get
 * \param  *pAttach            the point of the attach
 * \return <ul>
 *             <li> #TRUE   if successful
 *             <li> #FALSE  if failed
 *         </ul>
 */
int32_t NCCMms_par_getAttach(MMS_Handle MMSHandle, int32_t Pos, T_MMS_Attach * pAttach);        /*get one Attachment */

int32_t NCCMms_par_getTotalSlides(MMS_Handle MMSHandle);

int32_t NCCMms_par_getCurSlideIndex(MMS_Handle MMSHandle);

/*@}*/

#ifdef __cplusplus
}
#endif

#endif /* __NCC_MMS_PAR_H__ */
