
/**
 * @file ncciflayer.h
 * Interface Service Layer
 *
 * Service API exposed by the interface Layer.
 *
 * <!-- #interface list begin -->
 * \section ncciflayer Interface
 * - NCCBrw_iflayer_dlCheckSetCharset()
 * - NCCBrw_iflayer_init()
 * - NCCBrw_iflayer_close()
 * - NCCBrw_iflayer_clear()
 * - NCCBrw_iflayer_ctxtGetEncoding()
 * - NCCBrw_iflayer_ctxtSetEncoding()
 * - NCCBrw_iflayer_ctxtGetBase()
 * - NCCBrw_iflayer_ctxtGetTitle()
 * - NCCBrw_iflayer_ctxtSetTitle()
 * - NCCBrw_iflayer_ctxtGetOnLoad()
 * - NCCBrw_iflayer_ctxtGetOnUnload()
 * - NCCBrw_iflayer_ctxtGetTextColor()
 * - NCCBrw_iflayer_ctxtSetTextColor()
 * - NCCBrw_iflayer_ctxtGetBgColor()
 * - NCCBrw_iflayer_ctxtSetBgColor()
 * - NCCBrw_iflayer_ctxtGetLinkColor()
 * - NCCBrw_iflayer_ctxtSetLinkColor()
 * - NCCBrw_iflayer_ctxtGetVlinkColor()
 * - NCCBrw_iflayer_ctxtSetVlinkColor()
 * - NCCBrw_iflayer_ctxtGetBaseFont()
 * - NCCBrw_iflayer_ctxtGetRefresh()
 * - NCCBrw_iflayer_ctxtSetRefresh()
 * - NCCBrw_iflayer_ctxtSetBgSound()
 * - NCCBrw_iflayer_ctxtGetBgSoundSrc()
 * - NCCBrw_iflayer_ctxtSetBgSoundState()
 * - NCCBrw_iflayer_ctxtSetBgSoundData()
 * - NCCBrw_iflayer_ctxtGetBgSoundState()
 * - NCCBrw_iflayer_ctxtGetBgSoundData()
 * - NCCBrw_iflayer_ctxtPlayBgSound()
 * - NCCBrw_iflayer_ctxtSetBackward()
 * - NCCBrw_iflayer_ctxGetBackward()
 * - NCCBrw_iflayer_ctxtGetDomain()
 * - NCCBrw_iflayer_ctxtSetDomain()
 * - NCCBrw_iflayer_ctxtGetDocType()
 * - NCCBrw_iflayer_ctxtSetDocType()
 * - NCCBrw_iflayer_ctxtGetDocText()
 * - NCCBrw_iflayer_ctxtSetDocText()
 * - NCCBrw_iflayer_getNodeInterface()
 * - NCCBrw_iflayer_resetInterface()
 * - NCCBrw_iflayer_getNextFieldIdx()
 * - NCCBrw_iflayer_getPreFieldIdx()
 * - NCCBrw_iflayer_setFieldValueBySystemID()
 * - NCCBrw_iflayer_getFormValue()
 * - NCCBrw_iflayer_resetForm()
 * - NCCBrw_iflayer_setDisabled()
 * - NCCBrw_iflayer_getDisabled()
 * - NCCBrw_iflayer_pushYPos()
 * - NCCBrw_iflayer_getIndexByYPos()
 * - NCCBrw_iflayer_getNextBoxByYRange()
 * - NCCBrw_iflayer_pushBox()
 * - NCCBrw_iflayer_initALink()
 * - NCCBrw_iflayer_pushALink()
 * - NCCBrw_iflayer_cleanALink()
 * - NCCBrw_iflayer_getAByName()
 * - NCCBrw_iflayer_aClicked()
 * - NCCBrw_iflayer_aRelatedList()
 * - NCCBrw_iflayer_setRadioSelected()
 * - NCCBrw_iflayer_doRefresh()
 * - NCCBrw_iflayer_search()
 * - NCCBrw_iflayer_saveWebPage()
 * - NCCBrw_iflayer_viewSource()
 * - NCCBrw_iflayer_setSingleSelectIndex()
 * - NCCBrw_iflayer_doMultiSelect()
 * - NCCBrw_iflayer_handleTheSubmitMethod()
 * - NCCBrw_iflayer_getOptions()
 * - NCCBrw_iflayer_setNaviteEncoding()
 * - NCCBrw_iflayer_getNaviteEncoding()
 * - NCCBrw_iflayer_getStatusInfoByID()
 * - NCCBrw_iflayer_setStatusInfo()
 * - NCCBrw_iflayer_getStatusMessage()
 * - NCCBrw_iflayer_setUserStatusMessage()
 * - NCCBrw_iflayer_getStatusSize()
 * - NCCBrw_iflayer_setStatusSize()
 * - NCCBrw_iflayer_getStatusCode()
 * - NCCBrw_iflayer_setStatusCode()
 * - NCCBrw_iflayer_convertValue()
 * - NCCBrw_iflayer_getImageHref()
 * - NCCBrw_iflayer_copyImageData()
 * - NCCBrw_iflayer_setImageData()
 * - NCCBrw_iflayer_doPictoGram()
 * - NCCBrw_iflayer_relayout()
 * - NCCBrw_iflayer_urlResolve()
 * - NCCBrw_iflayer_stopTimer()
 * - NCCBrw_iflayer_doBackward()
 * - NCCBrw_iflayer_getNetMode()
 * - NCCBrw_iflayer_getScreenInfo()
 * - NCCBrw_iflayer_setScreenInfo()
 * - NCCBrw_iflayer_isBlankStr()
 * - NCCBrw_iflayer_setPrevSup()
 * - NCCBrw_iflayer_getPrevSup()
 * - NCCBrw_iflayer_dlAddUri()
 * - NCCBrw_iflayer_dlGetState()
 * - NCCBrw_iflayer_dlSetReferringUri()
 * - NCCBrw_iflayer_dlCheck()
 * - NCCBrw_iflayer_getDlProcess()
 * - NCCBrw_iflayer_dlGetCurUrl()
 * - NCCBrw_iflayer_dlGetDocType()
 * - NCCBrw_iflayer_isJs()
 * - NCCBrw_iflayer_doWmlUrl()
 * - NCCBrw_iflayer_parseWmlPage()
 * - NCCBrw_iflayer_dlSetCharset()
 * - NCCBrw_iflayer_dlGetCharset()
 * - NCCBrw_iflayer_dlDestroyList()
 * - NCCBrw_iflayer_dlAddImg()
 * - NCCBrw_iflayer_dlInitImgList()
 * - NCCBrw_iflayer_dlImgType()
 * - NCCBrw_iflayer_scriptDocWrite()
 * - NCCBrw_iflayer_dlGetBaseUrl()
 * - NCCBrw_iflayer_dlLoadPage()
 * - NCCBrw_iflayer_dlSetCurUrl()
 * - NCCBrw_iflayer_dlStopDownLoad()
 * - NCCBrw_iflayer_getPreCharset()
 * - NCCBrw_iflayer_getSingleSelectIndex()
 * - NCCBrw_iflayer_setBrowserFlag()
 * - NCCBrw_iflayer_unsetBrowserFlag()
 * - NCCBrw_iflayer_getBrowserFlag()
 * - NCCBrw_iflayer_getBrowserCpmCtxt()
 * - NCCBrw_iflayer_dlHaveJs()
 * <!-- #interface list end -->
 */

#ifndef  __NCC_IFLAYER_H__
#define __NCC_IFLAYER_H__

#include "wap_config.h"
#include "wap_struct.h"

#define DB_DEFAULT_SUBMIT_STR "Submit"

/** Defining WML scheme*/
#define IFLAYER_SCHEME_PREV "prev://"
#define IFLAYER_SCHEME_REFRESH "refresh://"
#define IFLAYER_SCHEME_NOOP "noop://"

/** set type,used when call NCCBrw_iflayer_setFieldValueBySystemID*/
#define SET_TYPE_VALUE    0
#define SET_TYPE_CHECKED  1

/** bgsound state*/
typedef enum _Bgs_state
{
    BGS_STATE_FAIL = -1,
    BGS_STATE_PENDING,
    BGS_STATE_SUCCESS
}T_Bgs_State;

/** image type*/
#define IMG_MOREALT -2      /**< splited alt*/
#define IMG_FIRSTALT -1     /**< first alt*/
#define IMG_NOTLOAD 0
#define IMG_BMP 1
#define IMG_GIF 2
#define IMG_JPG 3
#define IMG_WBMP 4
#define IMG_PNG 5
#define IMG_UNKNOW 6

/** Max length of sound file*/
#define WAP_MAX_BGSOUND (1024 * 100)

/** Defining message code*/
#define BROWSERMSG_MIN                  99
#define BROWSERMSG_MEM_ERROR            100     /**< memory error*/
#define BROWSERMSG_GATEWAY_INTERRUPT    101     /**< gateway interrupt*/
#define BROWSERMSG_DOWNLOAD_COMPLETE    102     /**< download completed*/
#define BROWSERMSG_UNKNOWN_ERROR        103     /**< unkown error*/
#define BROWSERMSG_ADDR_ERROR           104     /**< address error*/
#define BROWSERMSG_DATA_OVERRUN         105     /**< target file too large*/
#define BROWSERMSG_GATEWAY_FAIL         106     /**< connecting gateway failed*/
#define BROWSERMSG_SEND_ERROR           107     /**< sending data failed*/
#define BROWSERMSG_UNKNOWN_SCHEME       108     /**< unkown scheme*/
#define BROWSERMSG_SENDING              109     /**< sending data*/
#define BROWSERMSG_CONTENT_ERROR        110     /**< Content error */
#define BROWSERMSG_CONTENT_EMPTY        111     /**< Content empty */
#define BROWSERMSG_HOST_FINDING         112     /**< finding hostname*/
#define BROWSERMSG_HOST_CONNECTING      113     /**< connecting host of page*/
//#define BROWSERMSG_14                   114     /**< nouse*/
#define BROWSERMSG_404_NOT_FOUND        114     /**< page not found*/
#define BROWSERMSG_15                   115     /**< nouse*/
#define BROWSERMSG_16                   116     /**< nouse*/
#define BROWSERMSG_IMGS_READING         117     /**< receiving image*/
#define BROWSERMSG_JS_RECVING           118     /**< receiving js*/
#define BROWSERMSG_BGS_RECVING          119     /**< receiving bgsound*/
#define BROWSERMSG_WEBPAGE_RECVING      120     /**< receiving content*/
#define BROWSERMSG_CSS_RECVING          121     /**< connecting resouce*/
#define BROWSERMSG_22                   122     /**< nouse*/
#define BROWSERMSG_23                   123     /**< nouse*/
#define BROWSERMSG_24                   124     /**< nouse*/
#define BROWSERMSG_25                   125     /**< nouse*/
#define BROWSERMSG_26                   126     /**< nouse*/
#define BROWSERMSG_27                   127     /**< nouse*/
#define BROWSERMSG_28                   128     /**< nouse*/
#define BROWSERMSG_29                   129     /**< nouse*/
#define BROWSERMSG_WEBPAGE_CONNECTED    130     /**< connecting success*/
#define BROWSERMSG_WEBPAGE_CONTIMEOUT   131     /**< connecting timeout*/
#define BROWSERMSG_WEBPAGE_CONFAILED    132     /**< connecting failed*/
#define BROWSERMSG_WEBPAGE_READTIMEOUT  133     /**< receiving timeout*/
#define BROWSERMSG_WEBPAGE_INVALID      134     /**< content type invalid*/
#define BROWSERMSG_WEBPAGE_COMPLETE     135     /**< content received*/
#define BROWSERMSG_WEBPAGE_INTERRUPT    136     /**< download interrupt*/
#define BROWSERMSG_37                   137     /**< nouse*/
#define BROWSERMSG_38                   138     /**< nouse*/
#define BROWSERMSG_39                   139     /**< nouse*/
#define BROWSERMSG_IMG_CONNECTED        140     /**< connecting image success*/
#define BROWSERMSG_IMG_CONTIMEOUT       141     /**< connecting image timeout*/
#define BROWSERMSG_IMG_CONFAILED        142     /**< connecting image failed*/
#define BROWSERMSG_IMG_READTIMEOUT      143     /**< receiving image timeout*/
#define BROWSERMSG_IMG_INVALID          144     /**< image invalid*/
#define BROWSERMSG_IMG_COMPLETE         145     /**< image received*/
#define BROWSERMSG_46                   146     /**< nouse*/
#define BROWSERMSG_47                   147     /**< nouse*/
#define BROWSERMSG_48                   148     /**< nouse*/
#define BROWSERMSG_49                   149     /**< nouse*/
#define BROWSERMSG_JS_CONNECTED         150     /**< connecting js success*/
#define BROWSERMSG_JS_CONTIMEOUT        151     /**< connecting js timeout*/
#define BROWSERMSG_JS_CONFAILED         152     /**< connecting js failed*/
#define BROWSERMSG_JS_READTIMEOUT       153     /**< receiving js timeout*/
#define BROWSERMSG_JS_INVALID           154     /**< js invalid*/
#define BROWSERMSG_JS_COMPLETE          155     /**< js received*/
#define BROWSERMSG_56                   156     /**< nouse*/
#define BROWSERMSG_57                   157     /**< nouse*/
#define BROWSERMSG_58                   158     /**< nouse*/
#define BROWSERMSG_59                   159     /**< nouse*/
#define BROWSERMSG_BGS_CONNECTED        160     /**< connecting bgsound success*/
#define BROWSERMSG_BGS_CONTIMEOUT       161     /**< connecting bgsound timeout*/
#define BROWSERMSG_BGS_CONFAILED        162     /**< connecting bgsound failed*/
#define BROWSERMSG_BGS_READTIMEOUT      163     /**< receiving bgsound timeout*/
#define BROWSERMSG_BGS_INVALID          164     /**< bgsound invalid*/
#define BROWSERMSG_BGS_COMPLETE         165     /**< bgsound received*/
#define BROWSERMSG_66                   166     /**< nouse*/
#define BROWSERMSG_67                   167     /**< nouse*/
#define BROWSERMSG_68                   168     /**< nouse*/
#define BROWSERMSG_69                   169     /**< nouse*/
#define BROWSERMSG_CSS_CONNECTED        170     /**< connecting css success*/
#define BROWSERMSG_CSS_CONTIMEOUT       171     /**< connecting css timeout*/
#define BROWSERMSG_CSS_CONFAILED        172     /**< connecting css failed*/
#define BROWSERMSG_CSS_READTIMEOUT      173     /**< receiving css timeout*/
#define BROWSERMSG_CSS_INVALID          174     /**< css invalid*/
#define BROWSERMSG_CSS_COMPLETE         175     /**< css received*/
#define BROWSERMSG_76                   176     /**< nouse*/
#define BROWSERMSG_77                   177     /**< nouse*/
#define BROWSERMSG_78                   178     /**< nouse*/
#define BROWSERMSG_79                   179     /**< nouse*/
#define BROWSERMSG_80                   180     /**< nouse*/
#define BROWSERMSG_81                   181     /**< nouse*/
#define BROWSERMSG_82                   182     /**< nouse*/
#define BROWSERMSG_83                   183     /**< nouse*/
#define BROWSERMSG_84                   184     /**< nouse*/
#define BROWSERMSG_85                   185     /**< nouse*/
#define BROWSERMSG_86                   186     /**< nouse*/
#define BROWSERMSG_87                   187     /**< nouse*/
#define BROWSERMSG_88                   188     /**< nouse*/
#define BROWSERMSG_89                   189     /**< nouse*/
#define BROWSERMSG_NOT_SUPPORT_TLS      190     /**< not support tls*/
#define BROWSERMSG_NOT_SUPPORT_HTML     191     /**< not support html*/
#define BROWSERMSG_MAX                  192

/** Defining function pointer type from page charset to utf8*/
typedef void (*DoCharsetFunc_Def)(uint8_t * str_des, uint8_t * str_src,uint8_t * charset_name);

/** Defining function pointer type from utf8 to page charset*/
typedef void (*DoCharsetFunc_Reverse_Def)(uint8_t * str_des, uint8_t * str_src,uint8_t * charset_name);

typedef struct _ComputedBorderValue T_DB_ComputedBorderValue;
struct _ComputedBorderValue {
    T_DB_Pos    pos;                /**< pos info,including x;y;width;height*/
    int32_t     thickness[BOX_NUM_OF_DIMENSION];
    BorderStyleType style[BOX_NUM_OF_DIMENSION];
    ColorType   color[BOX_NUM_OF_DIMENSION];
};

/* Defining node interface struct */
struct _nodeInterface {
    int32_t         nodeType;       /**< node type*/
    T_DB_Pos        pos;                /**< pos info,including x;y;width;height*/
    int16_t         contentNodeIdx;     /**< index of block memory*/
    T_DB_FormNodeIdx formIdx;           /**< form index if this is a filed node*/
    int8_t          *id;                /**< id attribute*/
    int8_t          *name;              /**< name attribute*/
    int8_t          *value;             /**< value of this node*/
    int8_t          *origValue;         /**< origin value before changed*/
    uint8_t         fieldType;          /**< filed type if this is a form filed*/
    uint8_t         size;               /**< count of display characters,only for form filed*/
    uint8_t         rows;               /**< rows of multiple contrils,such as multiple select and textarea*/
    uint8_t         selectIndex;        /**< current selected item,used by single select;selected or not,used by radio or checkbox*/
    int16_t         maxsize;            /**< max input size of text box,used by input,password,textarea controls*/
    int16_t         selectList;         /**< first option index of select control*/
    int8_t          *formName;          /**< form name attribute if this is a form filed*/
    int8_t          *action;            /**< action attribute if this is a form filed*/
    int8_t          *encType;           /**< encType attribute if this is a form filed*/
    int8_t          *postdata;          /**< post data of form if this is a form filed*/
    int32_t          method;            /**< method of form if this is a form filed,DBA_FORM_METHOD_GET or DBA_FORM_METHOD_POST*/
    int8_t          *strPtr;            /**< content of this node*/
    int16_t         strLen;             /**< length of content*/
    int16_t         accessKey;          /**< accesskey of this node*/
    T_DB_ComnAttr   attr1;              /**< text attribute before clicked*/
    T_DB_ComnAttr   attr2;              /**< text attribute after clicked*/
    int8_t          *href;              /**< href attribute of hylink node*/
    int8_t          *alt;               /**< alt of image*/
    int8_t          *src;               /**< resource address of image*/
    uint8_t         *data;              /**< image data pointer*/
    int32_t         imgSize;            /**< length of image*/
    int16_t         state;              /**< image state IMG_MOREALT/IMG_FIRSTALT/IMG_NOTLOAD/IMG_BMP/IMG_GIF/IMG_JPG...*/
    int16_t         border;             /**< border of node,used to draw border of image*/
    T_DB_Pos        tdPos;              /**< pos info of td node,used to draw td of table*/
    int32_t         tdBgColor;          /**< background color of td.*/
    int32_t         imgDspReady;        /**< 1: img has been downloaded and relayouted.*/
    T_DB_ComputedBorderValue  computedBorderValue;/**< border attribute. */
    ColorType       bgColor;            /**< background color. */
    int8_t          *wapInputFormat;    /**< -wap-input-format */
    int32_t         wapInputRequired;   /**< for null string case of wapInputFormate */
    Box_DisplayType displayType;        /**< display: none,inline, -wap-marquee, ... */
    Box_Marquee     marquee;            /**< marquee context */
    VisibilityType  visibilityType;     /*< visiblity: */
    VerticalAlignType   verticalAlign;  /**< vertical-align: default value is baseline*/
};

typedef struct _nodeInterface            T_DB_NodeInterface;
typedef T_DB_NodeInterface*              T_DB_NodeInterfacePtr;

/**  */
typedef enum _DB_SaveWebPage_Type
{
    DB_SAVE_HTM_ALL = 1,     /**< save all of web page*/
    DB_SAVE_HTM_ONLY,    /**< save web page only as htm file */
    DB_SAVE_TXT          /**< save web page only as txt file*/
}T_DB_SaveWebPage_Type;

/** queue type of DL module*/
typedef enum _DB_DL_Queue_Type
{
    DB_QUEUE_PAGE,      /**< queue of web page*/
    DB_QUEUE_SCRIPT,    /**< queue of js file*/
    DB_QUEUE_CSS,       /**< queue of css file*/
    DB_QUEUE_FRAME,     /**< queue of frame page*/
    DB_QUEUE_OBJECT     /**< queue of object file*/
}T_DB_DL_Queue_Type;

/** download state of DL module*/
typedef enum _DB_DL_State
{
    DB_LOAD_IDLE,       /**< idle*/
    DB_LOAD_PAGE,       /**< loading web page*/
    DB_LOAD_SCRIPT,     /**< loading js file*/
    DB_LOAD_CSS,        /**< loading css file*/
    DB_LOAD_FRAME,      /**< loading frame page*/
    DB_LOAD_BGSOUND,    /**< loading bgsound file*/
    DB_LOAD_OBJECT,     /**< loading object file*/
    DB_LOAD_IMG         /**< loading img file*/
}T_DB_DL_State;

#define ON_CLICK_SINGLELIST_ST_FALSE      0
#define ON_CLICK_SINGLELIST_ST_SUCCESS    1
#define ON_CLICK_SINGLELIST_ST_ACCESS_URL 2

#ifdef __cplusplus
extern  "C" {
#endif

/**Initial browser core.*/
int32_t NCCBrw_iflayer_init(int8_t *sysPath);

/**Free browser core.*/
void NCCBrw_iflayer_close(void);

/**Empty browser and reset.*/
void NCCBrw_iflayer_clear(void);

/**Interface of Context functions*/

/**
* Get encoding of current page.
 * \return charset type of current page.
 */
int8_t *NCCBrw_iflayer_ctxtGetEncoding(void);

/**
 * Set encoding of current page.
 * \param encoding CHARSET type of current page.
 * \return
 */
void NCCBrw_iflayer_ctxtSetEncoding(int8_t * encoding);

/**
 * Get base URL of current.
 * \return Base URL of current.
 */
int8_t *NCCBrw_iflayer_ctxtGetBase(void);

/**
 * Get title of page.
 * \return Page title.
 */
int8_t *NCCBrw_iflayer_ctxtGetTitle(void);

/**
 * Set title of page.
 * \param title Page title.
 */
void NCCBrw_iflayer_ctxtSetTitle(int8_t * title);

#ifdef DB_USING_SCRIPT

/**
 * Get script of onload event of body
 *\return return Script of onload event of body
 */
int8_t *NCCBrw_iflayer_ctxtGetOnLoad(void);

/**
 * Get script of onunload event of body
 *\return return Script of onunload event of body
 */
int8_t *NCCBrw_iflayer_ctxtGetOnUnload(void);
#endif

/**
 * Get font color.
 * \return font color.
 */
int32_t NCCBrw_iflayer_ctxtGetTextColor(void);

/**
 * Set font color.
 * \param textColor Font color.
 * \return
 */
void NCCBrw_iflayer_ctxtSetTextColor(int32_t textColor);

/**
 * Get background color.
 * \return background color.
 */
int32_t NCCBrw_iflayer_ctxtGetBgColor(void);

/**
 * Set background color.
 * \param bgColor background color.
 * \return
  */
void NCCBrw_iflayer_ctxtSetBgColor(int32_t bgColor);

/**
 * Get hot link color.
 * \return Hot link color.
 */
int32_t NCCBrw_iflayer_ctxtGetLinkColor(void);

/**
 * Set hot link color.
 * \param linkColor Hot link color.
 */
void NCCBrw_iflayer_ctxtSetLinkColor(int32_t linkColor);

/**
 *Get visited link color.
 * \return visited link color.
 */
int32_t NCCBrw_iflayer_ctxtGetVlinkColor(void);

/**
 * Set visited link color.
 * \param vlinkColor visited link color.
 */
void NCCBrw_iflayer_ctxtSetVlinkColor(int32_t vlinkColor);

/**
 * Get base Font.
  * \return Base font.
 */
int32_t NCCBrw_iflayer_ctxtGetBaseFont(void);

/**
 * Get refresh URL.
 * \return refresh URL.
 */
int8_t *NCCBrw_iflayer_ctxtGetRefresh(void);

/**
  * Set refresh URL needed.
  * \param url Refresh URL needed.
 * \return
 */
void NCCBrw_iflayer_ctxtSetRefresh(int8_t * url);

/**
 * Set data of background music.
 * \param src URL of music.
 * \param loop Times of loop.
  * \return
 */
void NCCBrw_iflayer_ctxtSetBgSound(int8_t * src,int32_t loop);

/**
 * Get URL of background music data source.
 * \return URL of background music data source.
 */
int8_t * NCCBrw_iflayer_ctxtGetBgSoundSrc(void);

/**
 * Set status of download of background music.
 * \param state  state number.Following state is supported:
 *  #BGS_STATE_SUCESS,#BGS_STATE_PENDING,#BGS_STATE_FAIL
 *  \return
 */
void NCCBrw_iflayer_ctxtSetBgSoundState(T_Bgs_State state);

/**
 * Set data of background music downloaded.
 * \param data Data of the music file
 * \param len Length of the music file
 * \param contentType Content type of the music file
 *  \return
 */
void NCCBrw_iflayer_ctxtSetBgSoundData(int8_t * data,int32_t len,const int8_t * contentType);

/**
 * Get status of download of background music.
 * \return return background state:#BGS_STATE_SUCESS,#BGS_STATE_PENDING,#BGS_STATE_FAIL
 */
T_Bgs_State NCCBrw_iflayer_ctxtGetBgSoundState(void)   ;

/**
 * Get data of background music downloaded.
 * \param len Length of the music data
 * \param contentType Content type of the music data
 * \return Return a pointer to the backgroud sound data if success;otherwise return NULL.
 */
int8_t * NCCBrw_iflayer_ctxtGetBgSoundData(int32_t *len,int8_t ** contentType);

/**
 * Judge whether going on playing music.
 * \return <ul>
 *          <li>true: Go on
 *          <li>false: Stop
 *         </ul>
 */
int32_t NCCBrw_iflayer_ctxtPlayBgSound(void);

/**
 * Set onenterbackward event of wml.
 * \param url URL of onterbackward event.
 *  \return
 */
void NCCBrw_iflayer_ctxtSetBackward(int8_t * url);

/**
 * Get onenterbackward event of wml.
 * \return URL of onterbackward event.
 */
int8_t *NCCBrw_iflayer_ctxGetBackward(void);

/**
 * Get domain of current page.
 * \return Domain attribute of the page
 */
int8_t * NCCBrw_iflayer_ctxtGetDomain(void);

/**
 * Set domain of current page.
 * \param domain Domain attribute of the page.
 */
void NCCBrw_iflayer_ctxtSetDomain(int8_t * domain);

/** Interface of visit browser data*/
/**
 * Get node info.
 * \param iNode Node no.
 * \param pNodeInterface Pointer to store node info.
 * \return Return the NO. of next valid node.
 */
T_DB_ContentLinkIdx NCCBrw_iflayer_getNodeInterface(T_DB_ContentLinkIdx iNode,T_DB_NodeInterfacePtr pNodeInterface);

/**Reset var of table info.*/
void NCCBrw_iflayer_resetInterface(void);

/**
 * Get next no. of form control.
 * \param iField Index of form control.
 * \return The  NO. of the node.
 */
T_DB_FieldNodeIdx NCCBrw_iflayer_getNextFieldIdx( T_DB_FieldNodeIdx iField);

/**
 * Get pre no. of form control.
 * \param iField Index of form control.
 * \return The  NO. of the node.
 */
T_DB_FieldNodeIdx NCCBrw_iflayer_getPreFieldIdx( T_DB_FieldNodeIdx iField);

/**
 * Set field value based on index of field.
 * \param iField Index of field.
 * \param valueType Type of value: SET_TYPE_VALUE or SET_TYPE_CHECKED
 * \param value Value will be set. It has a different mean based on valueType.<ul>
 *           <li>If valueType is  SET_TYPE_CHECKED, it should be 0 or 1; </li>
 *          <li>if valueType is  SET_TYPE_VALU, it shoud be a string.</li></ul>
 * \return Return TRUE if success;otherwise return FALSE.
 */
int32_t NCCBrw_iflayer_setFieldValueBySystemID(T_DB_ContentLinkIdx iField,int16_t valueType,int8_t *value);

/**
 * Get value of form.
 * \param iForm Index of form.
 * \param pface The interface struct pointer of the node.
 * \param length The length of the form value
 * \param pConType A pointer to pointer of content type header field.
 * \return Value of form in pairs
 */
int8_t *NCCBrw_iflayer_getFormValue(T_DB_FormNodeIdx iForm, T_DB_NodeInterface *pface,int32_t *length, int8_t **pConType);

/**
 * Reset form, reset to default.
 * \param iForm Index of form.
 * \return
 */
void NCCBrw_iflayer_resetForm( T_DB_FormNodeIdx iForm );

/**
 * Set whether disabled of a form node.
 * \param nodeid Index of node.
 * \param flag disable flag.It should be TRUE or FALSE.
  * \return
  */
void NCCBrw_iflayer_setDisabled(T_DB_ContentLinkIdx nodeid,int32_t flag);

/**
 * Get disabled or not of a form node.
 * \param nodeid Index of node.
 * \return Return TRUE if disabled;otherwise return FALSE.
 */
int32_t NCCBrw_iflayer_getDisabled(T_DB_ContentLinkIdx nodeid);

/**Interface of anchor chain and YPOS chain*/

/**
 * Add node to y chain.
 * \param y Y-position.
 * \param iNode Node no.
 *\return
 */
void NCCBrw_iflayer_pushYPos( int32_t y, T_DB_ContentLinkIdx iNode );

/**
 * Get the first node which is immediately  after y-position.
 * \param y Y-position.
 * \return Return the Node no.
 */
T_DB_ContentLinkIdx NCCBrw_iflayer_getIndexByYPos( int32_t y );

/**
 * Get node whose body is in the range while displaying as a box or block.
 * \param top The top position of the range.
 * \param bottom The bottom position of the range.
 * \param boxIdx
 *          <li>[in]: Start box index when search the node. *boxIdx = 1 when first call this interface.
 *          <li>[out]:return next start point to search the node.
 * \return The node index when find success or 0 when find failed.
 */
T_DB_ContentLinkIdx NCCBrw_iflayer_getNextBoxByYRange(int32_t top, int32_t bottom, int32_t *boxIdx);

/**
 * Add node to box chain.
 * \param iNode Node index.
 */
void NCCBrw_iflayer_pushBox(T_DB_ContentLinkIdx iNode);

/**
 * Initial a chain of anchor.
 * \return Return a pointer to a anchor chain.
 */
void * NCCBrw_iflayer_initALink(void);

/**
 * Add anchor to anchor chain.
 * \param iA No. of link node.
 * \param paa Return a pointer to link attributes.
 *\return
 */
void NCCBrw_iflayer_pushALink( T_DB_ANodeIdx iA, T_DB_AAttrPtr paa );

/**
 * Clean chain of anchor.
 * \param pfd  the pointer to chain of anchor.If sucess
 *\return
 */
void NCCBrw_iflayer_cleanALink(void *pfd);

/**
 * Get the NO. of hot link by name.
 * \param name anchor name.
 * \return Return the Node NO. of hot link.
 */
T_DB_ANodeIdx NCCBrw_iflayer_getAByName( int8_t *name );

/**< Interface of message proccession*/

/**
 * Change attributes of hot link when clicked.
 * \param sysid Index of hot link.
 */
void NCCBrw_iflayer_aClicked(T_DB_ContentLinkIdx sysid);

/**
 * Find out hot links whose attributes equal to this.
 * \param sysid Index of this hot link.
 * \param ytop Y-position of top of current csreen.
 * \param ybottom Y-position of bottom of current csreen.
 * \return Return the Hot link array.
 */
int32_t* NCCBrw_iflayer_aRelatedList(T_DB_ContentLinkIdx sysid,int32_t ytop ,int32_t ybottom);

/**
 * Set selected flag to a radio box.
 * \param nodeindex Return the nodeindex Index of radio box.
 * \return
 */
void NCCBrw_iflayer_setRadioSelected(T_DB_ContentLinkIdx nodeindex);

/**
 * Process refresh.
 * \return Return the URL address need to jump to if success;otherwise return NULL.
 * \attention The returned buffer should be freed by the caller of the function.
 */
int8_t * NCCBrw_iflayer_doRefresh(void);

/**
 * Search string in current page.
 * \param xpos X-postion absoluted.
 * \param ypos Y-postion absoluted.
 * \param searchstr String wanted to search.
 * \param pNodeInterface Data interface search from.
 * \return Return TRUE if success;otherwise return FALSE.
 */
int32_t NCCBrw_iflayer_search(int16_t xpos
                      ,int32_t ypos
                      ,uint8_t * searchstr
                      ,T_DB_NodeInterfacePtr pNodeInterface
                      );

/**
 * Convert current page to html
 * \return buffer of html document
 */
int8_t *NCCBrw_iflayer_saveToHtmlBuffer(void);

/**
 * Convert current page to text
 * \return buffer of text document
 */
int8_t *NCCBrw_iflayer_saveToTextBuffer(void);

/**
 * Convert part of current page to html
 * \param   y1  y pos of begin
 * \param   y2  y pos of end
 * \return buffer of html document
 */
int8_t *NCCBrw_iflayer_savePartToTextBuffer(int32_t y1,int32_t y2);

/**
 * Set current selected item of a single select list, if the index of selected Item is invalid, selected the first.
 * \param sysid Index of single select list.
 * \param index Index of item selected.
 * \return Return TRUE if success;otherwise return FALSE.
 */
int32_t NCCBrw_iflayer_setSingleSelectIndex(T_DB_ContentLinkIdx sysid
                                    ,int16_t index
                                    );

/**
 * Set multi list select status.
 * \param sysid Index of check box.
 * \param index Index of item changed.
 * \param select Is selected.
 * \return Return TRUE if success;otherwise return FALSE.
 */
int32_t NCCBrw_iflayer_setMultiSelectIndex(T_DB_ContentLinkIdx sysid,int16_t index, uint8_t select);

/**
 * Synchronize name to iname of check box.
 * \param sysid Index of check box.
 */
void NCCBrw_iflayer_doMultiSelect(T_DB_ContentLinkIdx sysid);

/**
 * Process submit of form.
 * \param pface Info of button node submited.
  * \return Return a pointer to the URL address if success;otherwise return NULL.
  */
int8_t * NCCBrw_iflayer_handleTheSubmitMethod(T_DB_NodeInterface *pface);

/**
 *Translate info of options of a select from chain to array.
 *
 * \param selectlist Index of select. A chain of options can be got by this Index.
 * \param len Amount of options will be stored in.
 * \return Return the Option array.
 */
int8_t** NCCBrw_iflayer_getOptions(T_DB_OptionNodeIdx selectlist,int32_t * len);

/**< Interface of charset proccession */

/**
 * Set local charset.
 * \param encode Name of local charset.
 * \return Return TRUE if success;otherwise return FALSE.
 */
int32_t NCCBrw_iflayer_setNaviteEncoding(int8_t * encode);

/**
 * Get local charset.
 * \return Name of local charset.
 */
int8_t* NCCBrw_iflayer_getNaviteEncoding(void);

/** Interface of other kinds */

/**
 * Get status info based on ID appointed.
 * \param ID ID got info from.
 * \return Status info.
 */
uint8_t * NCCBrw_iflayer_getStatusInfoByID(int32_t ID);

/**
 * Set status info of pointer array of string.
 * \param StatusInfos a point to pointer of statusinfo array.
 */
void NCCBrw_iflayer_setStatusInfo(uint8_t ** StatusInfos);

/**
 * Get status info of .
 * \return Status  info.
 */
uint8_t * NCCBrw_iflayer_getStatusMessage(void);

/**
 * Set user status message.
 * \param code Index of message.
 * \param str  Message
 * \return
 */
void NCCBrw_iflayer_setUserStatusMessage(int32_t code,uint8_t * str);

/**
 * Get downloaded size.
 * \return  downloaded size of download file
 */
int32_t NCCBrw_iflayer_getStatusSize(void);

/**
 * Set length of download.
 * \param size Length of download will be set.
 * \return
 */
void NCCBrw_iflayer_setStatusSize(int32_t size);

/**
 * Get status code of download.
 * \return  status code of download
 */
int32_t NCCBrw_iflayer_getStatusCode(void);

/**
 * Set status info based on code.
 * \param code Index of message.
 * \return
 */
void NCCBrw_iflayer_setStatusCode(int32_t code);

/**
 * Conver code of charactors and codify URL in escape.
 * \param value source codes
 * \return codes converted.
 */
uint8_t * NCCBrw_iflayer_convertValue(uint8_t * value);

/**
 * Get URL of a img downloaded.
 * \param imageindex Index of image.
 * \return URL of the image.
 */
int8_t * NCCBrw_iflayer_getImageHref(T_DB_ImgNodeIdx imageindex);

/**
 * Copy data of image. If the img was downloaded,  it would avoid downloading again.
 * \param imageindex1 Index of image coyp to.
 * \param imageindex2 Index of image coyp from.
 * \return
 */
int32_t NCCBrw_iflayer_copyImageData(T_DB_ImgNodeIdx imageindex1,T_DB_ImgNodeIdx imageindex2);

/**
 * Set data of image when downloaded success.
 * \param imageindex Index of image node.
 * \param data pointer to img data.
 * \param type Type of img.
 * \param len Length of img data.
 * \param width Width of img.
 * \param height Height of img.
 * \return
 */
void NCCBrw_iflayer_setImageData(T_DB_ImgNodeIdx imageindex
                           ,int8_t * data
                           ,int32_t type
                           ,int32_t len
                           ,int16_t width
                           ,int16_t height
                           );

/**
 * Set data of image when downloaded success.
 * \param imageindex Index of image node.
 * \param localsrc flag of img locate.
 * \return Return TRUE if success;otherwise return FALSE.
 */
int32_t NCCBrw_iflayer_doPictoGram(T_DB_ImgNodeIdx imageindex,int8_t * localsrc);

/**
 * Re layout.
 * \return
*/
void NCCBrw_iflayer_relayout(void);

/**
 * Get file type of current doc.
 * \return Doc type.
 */
int32_t NCCBrw_iflayer_ctxtGetDocType(void);

/**
 * Set file type of current doc.
 * \param type Doc type.
 * \return
 */
void NCCBrw_iflayer_ctxtSetDocType(int32_t type);

/**
 * Get a wml page from wml cache.
 * \param docText Content of doc.
 * \return Return a pointer to the wml page buffer.
 */
int8_t * NCCBrw_iflayer_ctxtGetDocText(void);

/**
 * Save doc of current page to wml cache.
 * \param docText Content of doc.
 * \return
 */
void NCCBrw_iflayer_ctxtSetDocText(int8_t *docText);

/**
 * Processing URL.
 * \param newurl Current relative url input.
 * \return Return Absoluted URL.
 */
void * NCCBrw_iflayer_urlResolve(int8_t * newurl);

/**
 * Stop timer.
 * \return
 */
void NCCBrw_iflayer_stopTimer(void);

/**
 * Proccess backward envent.
 * \return
 */
void NCCBrw_iflayer_doBackward(void);

/**
 * Get net mode.
 * \return Net mode.
 */
T_DB_NetMode NCCBrw_iflayer_getNetMode(void);

/**
 * Get the screen info of the current process .
 * \return the pointer to the screen info.
 */
T_DB_Pos * NCCBrw_iflayer_getScreenInfo(void);

/**
 * Set the screen info of the current process
 * \param width the specific width of the screen
 * \param height the specific height of the screen
 * \return
 */
void NCCBrw_iflayer_setScreenInfo(int16_t width, int16_t height);

/**
 * Check whether a white string.
 * \param str String to be checked.
 * \return Return FALSE if the string is NULL or all character is white character;otherwise return TRUE.
 */
int32_t NCCBrw_iflayer_isBlankStr(int8_t * str);

/**
* Set prev state
* \param state state.It should be TRUE or FALSE.
* \return
*/
void NCCBrw_iflayer_setPrevSup(int32_t state);

/**
 * Get prev state.
 * \return Return the prev state.Its value is  TRUE or FALSE.
 */
int32_t NCCBrw_iflayer_getPrevSup(void);

/**
*  Add uri to different queue
*   \param   url            url of uri
*   \param   data           data of uri
*   \param   contentType    contentType of uri
*   \param   length         length of uri
*   \param   queueType      defined by T_DB_DL_Queue_Type
*   \return  Return TRUE if success;otherwise return FALSE.
*/
extern int32_t NCCBrw_iflayer_dlAddUri(int8_t * url
                     ,int32_t nRangeStart
                     ,int8_t * data
                     ,int8_t * contentType
                     ,int32_t length
                     ,T_DB_DL_Queue_Type queueType
                     );

/** Add to js download queue*/
#define fnDB_DLAddJs(a) NCCBrw_iflayer_dlAddUri(a,NULL,NULL,0,DB_QUEUE_SCRIPT)

/** Add to css download queue*/
#define fnDB_DLAddCss(a) NCCBrw_iflayer_dlAddUri(a,NULL,NULL,0,DB_QUEUE_CSS)

/**Add to page download queue*/
#define fnDB_DLAddPage(a,b) NCCBrw_iflayer_dlAddUri((a),(b),NULL,(b)?CRTL_strlen((char *)(b)):0,DB_QUEUE_PAGE)

/**
* Get status of DL
*   \return   DL status,defined by T_DB_DL_State
*/
T_DB_DL_State NCCBrw_iflayer_dlGetState(void);

/**
* Set referring uri
*   \param  url  referring uri
*   \return
*/
void NCCBrw_iflayer_dlSetReferringUri(int8_t * url);

/**
* Driving DL module
*   \return
*/
void NCCBrw_iflayer_dlCheck(void);

/**
*  Get download process
*   \return     download percent
*/
double NCCBrw_iflayer_getDlProcess(void);

/**
* Get current url by DL
*   \return   Return current url by DL
*/
int8_t * NCCBrw_iflayer_dlGetCurUrl(void);

/**
 * Get document type of last downloaded page
 *   \return   Return the document type of last downloaded page.
 */
int32_t NCCBrw_iflayer_dlGetDocType(void);

/**
 * Get source code  of web page
 * \return   Return the buf of source code. The caller should free buf after using the buf.
 */
int8_t * NCCBrw_iflayer_viewSource(void);

/**
 * Save web page
 * \param  saveName the name of txt file to be saved
 * \param  option the mode of save web page
 * \return
 */
int32_t NCCBrw_iflayer_saveWebPage(int8_t * saveName, T_DB_SaveWebPage_Type option ,int32_t freeSpaceLen);

/**
 * Check contentType whether it is js file.
 * \param  contentType
 * \return  <ul>
 *          <li>TRUE</li>
 *          <li>FALSE</li>
 *          </ul>
 */
int32_t NCCBrw_iflayer_isJs(int8_t * contentType);

/**
 * Convert from multi-bytes encoding into UTF8.
 * \param   encName multi-bytes encoding name
 * \param   in multi-bytes encoding buffer
 * \param   inOutlen input & output param, the bytes size of in or result buffer
 * \return  the converted utf-8 buffer if if success; otherwise return NULL.
 * \attention the return utf-8 buffer is NCCBrw_sa_malloc.
 */
uint8_t*
NCCBrw_iflayer_mbsToUtf8( const uint8_t *encName,
                       const uint8_t *in,
                       int32_t *inOutlen );
/**
 * Convert from UTF8 into multi-bytes encoding.
 * \param   encName multi-bytes encoding name
 * \param   in utf-8 encoding buffer
 * \param   inlen the bytes size of in
 * \return  the converted multi-bytes buffer if if success; otherwise return NULL.
 * \attention the return utf-8 buffer is NCCBrw_sa_malloc.
 */
uint8_t*
NCCBrw_iflayer_utf8ToMbs( const uint8_t *encName,
                       const uint8_t *in,
                       int32_t inlen );

/**
 * Proccess url of wml.
 * \param wmlUrl Url of wml.
 * \return
 */
void NCCBrw_iflayer_doWmlUrl(int8_t * wmlUrl);

/**
 * parsing wml buffer.
 * \param url       Url of wml.
 * \param wmlBuffer buffer of wml.
 * \return          TRUE:success;FALSE:failed
 */
int32_t NCCBrw_iflayer_parseWmlPage(int8_t * url,int8_t * wmlBuffer);

/**
 * Set current charset.
 * \param charset       current charset.
 * \return
 */
void NCCBrw_iflayer_dlSetCharset(int8_t * charset);

/**
 * Get current charset by DL
 * \return  charset by DL
 */
int8_t * NCCBrw_iflayer_dlGetCharset(void);

/**
*  unload data list of img, free data list and img data
*   \param  list    data list of img
*/
void NCCBrw_iflayer_dlDestroyList(void * list);

/**
* add index of one img to img queue
*   \param index    index of one img
*/
void NCCBrw_iflayer_dlAddImg( T_DB_ImgNodeIdx index );

/**
*  init data list of img
*   \return     header pointer of data list of img,failed if return NULL
*/
void *NCCBrw_iflayer_dlInitImgList(void);

/**
* Get supported image type from contentType
*   \param  contentType     MIME type string
*   \return type of image support,defined in ncciflayer.h
*/
int32_t NCCBrw_iflayer_dlImgType(uint8_t *contentType);

#ifdef DB_USING_SCRIPT
/**
*  Excute document.write
*   \param   docWriteBuf document.write of js
*/
void NCCBrw_iflayer_scriptDocWrite(int8_t *DocWriteBuf);
#endif

/**
* get base url by DL
*   \return  base url by DL
*/
int8_t * NCCBrw_iflayer_dlGetBaseUrl(void);

/**
* new a web page download session, the former download should be reseted
*   \param url  url of web page
*   \param url  data of web page
*   \param url  contentType of web page
*   \param url  length of web page
*/
int8_t NCCBrw_iflayer_dlLoadPage(int8_t * url
                         ,int32_t nRangeStart
                         ,int8_t * data
                         ,int8_t * contentType
                         ,int32_t length
                         );

/**
* set current charset by DL
*   \param url url of web page
*/
void NCCBrw_iflayer_dlSetCurUrl(int8_t * url);

/**
* stop DL
*   \return
*/
void NCCBrw_iflayer_dlStopDownLoad(void);

/**
* get charset before parsing
*/
int8_t * NCCBrw_iflayer_getPreCharset(void);

/**
 * Get current selected item of a single select list, if none, get the first item.
 * \param selectlist Index of single select list.
 * \return Index of item selected.
 */
int16_t NCCBrw_iflayer_getSingleSelectIndex(T_DB_OptionNodeIdx selectlist);

/**
 * Set browser flag.
 * \param   flag    the browser flag to be setted. The following flag is supported:<ul>
 *          <li>BROWSER_FLAG_ISSTOP </li>
 *          <li>BROWSER_FLAG_TABLESUPPORT</li>
 *          <li>BROWSER_FLAG_IMGSUPPORT</li>
 *          <li>BROWSER_FLAG_ISALIGN</li></ul>
 * \return
 */
void NCCBrw_iflayer_setBrowserFlag(int32_t flag);

/**
 * Unset browser flag.
 * \param   flag    the browser flag to be unsetted. The following flag is supported:
 *          <ul>
 *          <li>BROWSER_FLAG_ISSTOP</li>
 *          <li>BROWSER_FLAG_TABLESUPPORT</li>
 *          <li>BROWSER_FLAG_IMGSUPPORT</li>
 *          <li>BROWSER_FLAG_ISALIGN</li>
 *          </ul>
 * \return
 */
void NCCBrw_iflayer_unsetBrowserFlag(int32_t flag);

/**
 * Call this function to determine if the specified browser flag is setted.
 * \param   flag    the browser flag to be determined. The following flag is supported:
 *          <ul>
 *          <li>BROWSER_FLAG_ISSTOP</li>
 *          <li>BROWSER_FLAG_TABLESUPPORT</li>
 *          <li>BROWSER_FLAG_IMGSUPPORT</li>
 *          <li>BROWSER_FLAG_ISALIGN</li>
 *          </ul>
 * \return   Return If setted,return TRUE; otherwise return FALSE.
 */
int32_t NCCBrw_iflayer_getBrowserFlag(int32_t flag);

void NCCBrw_iflayer_setBrowserErrorFlag(int32_t flag);
void NCCBrw_iflayer_unsetBrowserErrorFlag(int32_t flag);
int32_t NCCBrw_iflayer_getBrowserErrorFlag(int32_t flag);

/**
 * Get current parsing context.
 * \return Return the current parsing context
 */
void * NCCBrw_iflayer_getBrowserCpmCtxt(void);

/**
 * Get first uri in certain queue
 */
int32_t NCCBrw_iflayer_dlHaveJs(void);

/**
 * Get Browser lib version
 */
int8_t *NccBrowser_GetVersionInfo(void);

/**
 * Get Common lib version
 */
int8_t *NccCommon_GetVersionInfo(void);

/**
 * NccBrowser_SetOMADDReq
 */
void NccBrowser_SetOMADDReq(u32 isDownload);

/**
 * NccBrowser_CancelOMADownloadReq
 */
void NccBrowser_CancelOMADownloadReq(void);

#ifdef __cplusplus
}
#endif

#endif /*_DBA_IF_INTERFACE_*/
