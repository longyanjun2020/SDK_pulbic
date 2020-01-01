
/**
 * @file
 * NCC mms composer common
 *
 * local function and macros declared by NCC mms composer
 *
 */

#ifndef __CPS_COMMON_H__
#define __CPS_COMMON_H__

#include <ncc_types.h>
#include <nccmms_par.h>
#include <nccmms_cps.h>

#ifdef __cplusplus
extern "C" {
#endif

#define CPS_MAX_SLIDE                                        0x15       /* Max slide supported */
#define CPS_DEFAULT_DURATION                                 0xBB8    /**<default timing of the every slide */

#define MMS_REGION_MIN_PERCENT                               0xA    /**<the min percent of the MMS region*/
#define MMS_REGION_MAX_PERCENT                               0x5A    /**<the max percent of the mms region*/

#define SMIL_CLASS_TEXT                                      0xF1    /**<Text*/
#define SMIL_CLASS_IMAGE                                     0xF2    /**<IMAGE*/
#define SMIL_CLASS_AUDIO                                     0xF3    /**<AUDIO*/
#define SMIL_CLASS_VIDEO                                     0xF4    /**<VIDEO*/
#define SMIL_CLASS_REF                                       0xF5    /**<REF*/
#define SMIL_CLASS_OTHER                                     0xF6    /**<OTHER*/
#define SMIL_CLASS_ATTACH                                    0xF7    /**<attach*/

#define SMIL_INVALID_VALUE                                   -0x01    /**<invalid value*/

#define Content_ArrayLen(arry)                               (sizeof(arry)/sizeof(arry[0]))        /**<count length of array*/

#define MMS_SMIL_RETRIVE_TIME(x,y) if((CRTL_strstr((x),"ms")) ||    \
                                    (CRTL_strstr((x),"MS")))        \
                                {                   \
                                    (y) = CRTL_atoi((x));       \
                                }                   \
                                else if((CRTL_strstr((x),"s"))||    \
                                    (CRTL_strstr((x),"S")))     \
                                {                   \
                                    (y) = (CRTL_atoi((x))) * 1000;  \
                                }                   \
                                else                    \
                                {                   \
                                    (y) = CRTL_atoi((x));       \
                                }

enum MMS_REGION_FLAG {
    MMS_TEXT_REGION = 0,
    MMS_IMAGE_REGION,
    MMS_REF_REGION
};

/** mms slide struct,stand for each slide of the mms  */
typedef struct T_CPS_SlideStruct {
    int32_t imageexist;     /**<save whether image is existed or not ,image exist:1 not exist:0 */
    int32_t textexist;         /**<save whether text is existed or not,exist:1    not exist:0 */
    int32_t audioexist;     /**<save whether audio is existed or not,exist:1    not exist:0 */
    int32_t videoexist;     /**<save whether video is existed or not,exist:1    not exist:0 */

    MMS_Composer_BasicStructure imagebasicatt;    /**<the basic information of the image*/
    uint8_t ImgBGcolor[12];             /**<used to save the bgcolor of the image*/
    MMS_BasicRegion ImgRect;            /**<used to image region */

    MMS_Composer_BasicStructure textbasicatt;        /**<the basic information of the text*/
    uint8_t TextFG_color[12];                 /**<used to save the color of the text*/
    int8_t Textsize[8];                       /**<the size of the Text*/
    int8_t Textattribute[12];                  /**<the type of the text*/
    uint8_t TextBGcolor[12];                 /**<the bgcolor of the Text*/
    MMS_BasicRegion TextRect;                /**<the region of the text */

    MMS_Composer_BasicStructure audiobasicatt;        /**<the basic information of the audio*/

    MMS_Composer_BasicStructure videobasicatt;        /**<the basic information of the video*/
    MMS_BasicRegion VideoRect;                /**<the region of the video */

    uint8_t backcolor[12];          /**< background color for every slide */
    int8_t ImageName[100];         /**<the name of the image*/
    int8_t AudioName[100];         /**<the name of the audio*/
    int8_t VideoName[100];         /**<the name of the video*/
} T_CPS_SlideStruct;

/**attach struct*/
typedef struct T_CPS_Attach {
    uint8_t *AttBuf;            /**<attach data buffer*/
    int8_t *Type;            /**< attach type  */
    int32_t size;            /**<size of attachment data*/
    int8_t *Name;            /**<name of attachment*/
    struct T_CPS_Attach *next;        /**<the point of the next attach*/
    struct T_CPS_Attach *prior;        /**<the point of the prior attach*/
} T_CPS_Attach;

/** used for create one mms and store the information of the mms */
typedef struct T_CPS_NewMM {
    int32_t newmmsize;                    /**<the size of the mms */
    int32_t TotalSlide;                    /**<total slides of the mms  */
    int32_t currentslide;                /**<the index of the current slide */
    int32_t TotalAttachment;                /**<the total number of the attach*/
    T_CPS_Attach *attach;                   /**<the point of the list of the mm's attach*/
    int32_t slideexist[CPS_MAX_SLIDE];            /**<FLAG array of the mm exist;0:not exist    1:exist*/
    int32_t slidetiming[CPS_MAX_SLIDE];            /**< the timing array of the mm's slide   */
    T_CPS_SlideStruct slidestruct[CPS_MAX_SLIDE];    /**<the array of the mm's slide struct */
} T_CPS_NewMM;

/** region struct define */
typedef struct _Parser_Region {
    int8_t *id;                    /**< indentify */
    MMS_BasicRegion pos;            /**< area value */
    int8_t *fit;                     /**< fill  hidden  meet    slice */
    int8_t BGColor[MMS_BGCOLOR_LEN];           /**<the bgcolor of the region*/
    struct _Parser_Region *next;
} T_Parser_Region;

/** smil par struct */
typedef struct _Parser_SmilPar {
    int32_t dur;                               /**< the duration of the slide  */
    T_Parser_Text *Text;                            /**< the text element pointer   */
    T_Parser_Image *Image;                    /**<the Image element pointer  */
    T_Parser_Audio *Audio;                       /**< the Audio element pointer  */
    T_Parser_Video *Video;                      /**< the Video element pointer */
    T_Parser_Ref *Ref;                         /**<the Ref element pointer*/
    struct _Parser_SmilPar *Next;                  /**< the next par struct pointer   */
    struct _Parser_SmilPar *Pre;                   /**< the pre par struct pointer   */
} T_Parser_SmilPar;

/** smil view struct  */
typedef struct _Parser_SmilView {
    int32_t Width;                               /**< the width of the view  */
    int32_t Height;                               /**<  the heigtht of the view  */
    T_Parser_Region *Region;                   /**< the region struct pointer  */
    T_Parser_SmilPar *Par;                      /**< the par struct pointer list  */
    T_Parser_SmilPar *CurPar;                  /**< the current par struct  */
    T_Parser_Attach *Attach;                     /**<the Attachment struct pointer link*/
} T_Parser_SmilView;

/**handle struct*/
typedef struct T_MMS_HANDLE {
    T_CPS_NewMM *CPS_NewMM;                    /**< malloc when MM is composed or when MM is reedited*/
    T_MMS_ScreenSize ScreenSize;                 /**< copy value of global variable tCPS_ScreenSize*/
    T_MMS_InitInformation InitInfor;                 /**< copy value of global variable gMMS_InitInfo*/
    T_Parser_SmilView *SMIL_ViewStruct;        /**<malloc when MM is parsed or when MM is reedited*/
} T_MMS_HANDLE;
//typedef struct T_MMS_HANDLE *MMS_Handle;

/**  MMS media element struct */
/** MMS presentation part struct  */
typedef struct T_MMS_Presentation {
    int8_t *ContentType;
    int8_t *DataBuf;
    int32_t Data_Size;
} T_MMS_Presentation;

/**the list of the media element*/
typedef struct T_MMS_Media_Element {
    int8_t *Location;
    int8_t *Content_ID;
    int8_t *Name;                    /**<the name of the media elemet*/
    uint8_t *DataBuf;
    int32_t Data_Size;
    int32_t Charset;
    uint8_t HasCharSet;
    uint8_t Boundary[3];               /**<byte align  */
    int8_t *Content_Type;
    int32_t IsUsed;                      /**<mark whether the element has been used.*/
    struct T_MMS_Media_Element *Next;
} T_MMS_Media_Element;

/** the whole mms body content  struct  */
typedef struct T_MMS_Content_Union {
    T_MMS_Presentation *pSmil;        /**<the point of the smil pdu*/
    T_MMS_Media_Element *pElement;    /**<the point of the element*/
} T_MMS_Content_Union;

int32_t SMILDispatchByMediaType(int8_t * ElementType);

/**
 * Simulation c function:MMS_STRICMP
 * \param  *const char *s1     the point of the first string
 * \param  *const char *s2     the point of the second string
 * \return <ul>
 *             <li> >0          if greater
 *             <li> =0          if equal
 *             <li> <0          if less
 *         </ul>
 */
int32_t MMS_Stricmp(const char *s1, const char *s2);

int32_t SmilAnalyseRegionData(MMS_BasicRegion * DesPos,
                              T_Parser_SmilView * SmilView,
                              T_MMS_ScreenSize * ScreenSize,
                              enum MMS_REGION_FLAG region_flag);

/**
 * Get a result about the media which we will insert whether to
 * belong to CURContent Class search ContentClass
 * \param CPSHandle     composer handle
 * \param MediaTypeName     pointer of media type name
 * \return <ul>
 *      <li> COMPOSER_CREATE_MODE_MEDIATYPENULL if invalid parameter
 *      <li> COMPOSER_MEDIAILLEGAL  if invalid media type
 *      <li> media type         if success
 *     </ul>
 */
int8_t ComposerCheckMMContentClass(MMS_Handle CPSHandle,
                                   int8_t * MediaTypeName);

/**
 * According to the Location to get the element's content from the pdu .
 * \param    *pPduData        the MMS ContentTypeAndBody value's pointer
 * \param    *DataSize        the size of the pdu
 * \return    <ul>
 *                <li> pointer of element union     if success
 *                <li> NULL             if fail
 *            </ul>
 * \sa    GetContentType()
 */
T_MMS_Content_Union *fnMMS_GetMediaDataFromPdu(uint8_t * pPduData,
                                               int32_t DataSize);

/**
 * Encode the content type and the MMS body into the pdu
 * \param    *pUion        the MMS body struct ,include presentation and multimedia
 * \param    *Length        the length of the body's pdu
 * \return    <ul>
 *                <li> the pdu's pointer        if success
 *                <li> NULL             if failed
 *            </ul>
 */
uint8_t *fnMMS_MakeContentBodyPdu(T_MMS_Content_Union * pUion,
                                  int32_t * Length);

/**
 * Free all the resource used by the struct of T_MMS_Content_Union.
 * \param    *pContent    the MMS body struct ,include presentation and multimedia
 * \return <ul>
 *      <li> NONE
 *     </ul>
 */
void fnMMS_FreeContentUnion(T_MMS_Content_Union * pContent);

/**
 * Free all the resource used by the struct of T_MMS_Content_Union,buf some of the data is need not to
 * be free ,it memery is belong to the mms pdu.
 * \param    *pContent    the MMS body struct ,include presentation and multimedia.
 * \return <ul>
 *      <li> NONE
 *     </ul>
 */
void fnMMS_FreeMediaData(T_MMS_Content_Union * pContent);

/**
 *Encode the MMS body into the pdu
 * \param    CPSHandle    The handle of MMS.
 * \param    *pLength     An integer to save the length of pdu.
 *
 * \return <ul>
 *             <li>Success,return#An pointer to specify the content pdu.
 *             <li>Otherwise,return#NULL
 *         </ul>
 */
uint8_t *fnMMS_GetNoSmilMmsContentPdu(MMS_Handle CPSHandle, int32_t *pLength);

#ifdef __cplusplus
}
#endif

#endif /* __CPS_COMMON_H__ */
