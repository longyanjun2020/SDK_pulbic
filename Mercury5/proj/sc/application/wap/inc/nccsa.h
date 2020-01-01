
/**
 * @file
 *  Semantic Analyser Service Layer
 *
 * Service API exposed by the Semantic Analyser.
 *
 * <!-- #interface list begin -->
 * \section nccsa_interface Interface
 * - NCCBrw_sa_stopParser()
 * - NCCBrw_sa_naviGetInvalidateState()
 * - NCCBrw_sa_naviSetInvalidateState()
 * - NCCBrw_sa_setNaviPageHeight()
 * - NCCBrw_sa_getNaviPageHeight()
 * - NCCBrw_sa_setNaviYpos()
 * - NCCBrw_sa_getNaviYpos()
 * - NCCBrw_sa_naviBack()
 * - NCCBrw_sa_naviForward()
 * - NCCBrw_sa_naviGo()
 * - NCCBrw_sa_naviRefresh()
 * - NCCBrw_sa_naviForceRefresh()
 * - NCCBrw_sa_naviStop()
 * - NCCBrw_sa_naviStart()
 * - NCCBrw_sa_naviStartMultiPart()
 * - NCCBrw_sa_naviGetRefreshUrl()
 * - NCCBrw_sa_naviSetRefreshFlag()
 * - NCCBrw_sa_naviGetCurUrl()
 * - NCCBrw_sa_naviState()
 * - NCCBrw_sa_naviGetCurUrl()
 * - NCCBrw_sa_naviSetCurUrl()
 * - NCCBrw_sa_naviGetCurFontSize()
 * - NCCBrw_sa_naviSetCurFontSize()
 * - NCCBrw_sa_hLength()
 * - NCCBrw_sa_initTextValue()
 * - NCCBrw_sa_getParseCtxt()
 * - NCCBrw_sa_browserActivated()
 * - NCCBrw_sa_printInfo()
 * - NCCBrw_sa_printInfoWithNumber()
 * - NCCBrw_sa_getCookieList()
 * - NCCBrw_sa_setBrowserCpmCtxt()
 * - NCCBrw_sa_triggerAreaHot()
 * - NCCBrw_sa_mmGet()
 * - NCCBrw_sa_mmGetLastNode()
 * - NCCBrw_sa_mmAppend()
 * - NCCBrw_sa_getAttribute()
 * - NCCBrw_sa_comnBufAppend()
 * - NCCBrw_sa_wtai()
 * - NCCBrw_sa_beginCollect()
 * - NCCBrw_sa_endCollect()
 * - NCCBrw_sa_getParseState()
 * - NCCBrw_sa_getHtmlParserDesc()
 * - NCCBrw_sa_setDefaultBase()
 * - NCCBrw_sa_colorParse()
 * - NCCBrw_sa_hexStr2Int()
 * - NCCBrw_sa_getPictogram()
 * - NCCBrw_sa_getMarquee()
 * - NCCBrw_sa_hInit()
 * - NCCBrw_sa_unLoadH()
 * - NCCBrw_sa_hReset()
 * - NCCBrw_sa_resetYpos()
 * - NCCBrw_sa_resetBox()
 * - NCCBrw_sa_wmlActVarParse()
 * - NCCBrw_sa_findTag()
 * - NCCBrw_sa_getFieldPtr()
 * - NCCBrw_sa_getOptionsLen()
 * - NCCBrw_sa_getOptionAt()
 * - NCCBrw_sa_delOpt()
 * - NCCBrw_sa_addOptByID()
 * - NCCBrw_sa_getImgesLength()
 * - NCCBrw_sa_getImgPtr()
 * - NCCBrw_sa_getImgPtrById()
 * - NCCBrw_sa_getAreaShapeStr()
 * - NCCBrw_sa_getAreaList()
 * - NCCBrw_sa_getLinksLength()
 * - NCCBrw_sa_getLinksElemPtr()
 * - NCCBrw_sa_BoxAttributeTable_getAttribute()
 * - NCCBrw_sa_rInit()
 * - NCCBrw_sa_unLoadR()
 * - NCCBrw_sa_getRecord()
 * - NCCBrw_sa_rReset()
 * <!-- #interface list end -->
 */

#ifndef __NCC_SA__
#define __NCC_SA__
#include "ncc_types.h"
#include "wap_config.h"
#include "wap_struct.h"
#include "sa_maparea.h"
#include "ncccommon_list.h"
#include "sa_urlhstack.h"
#include "sa_urlrstack.h"

/** FORM method*/
#define DBA_FORM_METHOD_GET                1
#define DBA_FORM_METHOD_POST               2

/** font mode*/
#define  DB_FONT_BIG        2
#define  DB_FONT_MIDDLE     1
#define  DB_FONT_SMALL      0

/** font size*/
#define  DB_FONT_SIZE1        1
#define  DB_FONT_SIZE2        2
#define  DB_FONT_SIZE3        3
#define  DB_FONT_SIZE4        4
#define  DB_FONT_SIZE5        5
#define  DB_FONT_SIZE6        6
#define  DB_FONT_SIZE7        7

/** MARQUEE scroll direction*/
#define DB_MARQUEE_LEFT     1
#define DB_MARQUEE_RIGHT    2
#define DB_MARQUEE_UP       3
#define DB_MARQUEE_DOWN     4

/** navigator state*/
#define DB_NAVISTATE_NOPAGE     1
#define DB_NAVISTATE_HEAD       2
#define DB_NAVISTATE_TAIL       3
#define DB_NAVISTATE_MIDDLE     4

/** align mode*/
#define ALIGN_LEFT   0x01                   /**< left align */
#define ALIGN_CENTER 0x02                   /**< center align*/
#define ALIGN_RIGHT  0x04                   /**< right align*/
#define ALIGN_TOP    0x08                   /**< top align*/
#define ALIGN_MIDDLE 0x10                   /**< middle align*/
#define ALIGN_BOTTOM 0x20                   /**< bottom align*/
#define ALIGN_INVALID -1                    /**< unset*/


#ifdef __cplusplus
extern  "C" {
#endif

#ifdef DB_USING_SCRIPT
#define SA_LINK_NODE  0x00
#define SA_AREA_NODE  0x01

struct __sa_linksElem__ {
    int32_t type;
    union {
        T_DB_ANodePtr link;
        AreaStruct *area;
    }linksElem;
};

typedef struct __sa_linksElem__ T_DB_LinksElem;
typedef T_DB_LinksElem *T_DB_LinksElemPtr;
#endif /* DB_USING_SCRIPT */

/**
 * Stop parse.
 * \return
 */
void  NCCBrw_sa_stopParser(void);

/**
 * Determines whether page is need to been redrawed.
 * \return      Return TRUE if redraw page is needed;otherwise return FALSE.
 */
int32_t NCCBrw_sa_naviGetInvalidateState(void);

/**
 * Set the status of page redraw tag.
 * \param flag  additonal size. This value shoud be TRUE or FALSE.
 * \return If success,return TRUE; otherwise,FALSE.
 */
void NCCBrw_sa_naviSetInvalidateState(int32_t flag);

/**
 * Set logic height of current page.
 * \return
 */
void NCCBrw_sa_setNaviPageHeight(void);

/**
 * Get logic height of current page.
 * \return   Return the scroll bar height of current webpage.
 */
int32_t NCCBrw_sa_getNaviPageHeight(void);

/**
 * Set current ypos.
 * \param   pos
 * \return
 */
void NCCBrw_sa_setNaviYpos(int32_t pos);

/**
 * Get ypos.
 * \return  ypos of current page.
 */
int32_t NCCBrw_sa_getNaviYpos(void);

/**
 * Navigate back.
 * \return   Return the current url of current page.
 */
int8_t * NCCBrw_sa_naviBack(void);

/**
 * Navigate forward.
 * \return   current url of current page.
 */
int8_t * NCCBrw_sa_naviForward(void);

/**
 * Navigate steps.
 * \param    step  go forward or back steps,>0:forward;<0:back.
 * \return
 */
int8_t * NCCBrw_sa_naviGo(int32_t step);

/**
 * Navigate refreash.
 * \return
 */
void NCCBrw_sa_naviRefresh(void);

/**
 * Force Navigate to get the page form server.
 * \return
 */
void NCCBrw_sa_naviForceRefresh(void);

/**
 * Navigate stop.
 * \return
 */
void NCCBrw_sa_naviStop(void);

/**
 * Navigate to url(simple).
 * \param   pUrl        url address
 * \param   postData    post data
 * \return
 */
void NCCBrw_sa_naviStart(int8_t *pUrl, int8_t *postData);

/**
 * Navigate to url(simple).
 * \param   pUrl        url address
 * \param   nRangeStart
 * \param   postData    post data
 * \return
 */
void NCCBrw_sa_naviStartEx(int8_t *pUrl, int32_t nRangeStart, int8_t *postData);

/**
 * Navigate to url(complicated).
 * \param   pUrl        url address
 * \param   postData    post data
 * \param   contentType The content type of the post data.
 * \param   dataLen The length of the post data
 * \return
 */
void NCCBrw_sa_naviStartMultiPart(int8_t *pUrl
                        ,int8_t *postData
                        ,int8_t * contentType
                        ,int32_t dataLen
                        );
void NCCBrw_sa_naviStartMultiPartEx(int8_t *pUrl
                        ,int32_t nRangeStart
                        ,int8_t *postData
                        ,int8_t * contentType
                        ,int32_t dataLen
                        );

/**
 * Get url of auto-refresh.
 * \return  the refresh URL
 */
int8_t * NCCBrw_sa_naviGetRefreshUrl(void);

/**
 * Set Navigation refresh flag.
 * \param   flag    the browser refresh flag.The value should be TRUE or FALSE.
 * \return
 */
void NCCBrw_sa_naviSetRefreshFlag(int32_t flag);

/**
 * Get the URL of current page.
 * \return  the URL of current page
 */
int8_t * NCCBrw_sa_naviGetCurUrl(void);

/**
 * Get navigator state.
 * \return
 *      <ul>
 *      <li>#define DB_NAVISTATE_NOPAGE     1</li>
 *      <li>#define DB_NAVISTATE_HEAD       2</li>
 *      <li>#define DB_NAVISTATE_TAIL       3</li>
 *      <li>#define DB_NAVISTATE_MIDDLE     4</li>
 *      </ul>
 */
int32_t NCCBrw_sa_naviGetState(void);

/**
 * Get the current url.
 * \return  the URL of current page
 */
int8_t * NCCBrw_sa_naviGetCurUrl(void);

/**
 * Set the current url.
 * \param url the URL of current page
 * \return
 */
void NCCBrw_sa_naviSetCurUrl(  int8_t *url);

/**
 * Get the current font size.
 * \return  the font size of current page
 */
uint8_t NCCBrw_sa_naviGetCurFontSize(void);

/**
 * Set the current font size.
 * \param fontSize the font size of current page
 * \return
 */
void NCCBrw_sa_naviSetCurFontSize(uint8_t fontSize);

/**
 * Duplicate current navi params
 * \return
 */
void NCCBrw_sa_dupNaviParams(void);

/**
 * Get length of history stack.
 * \return      length of history stack
 */
int32_t NCCBrw_sa_getHistoryLength(void);


/**
 * Init text buffer using wml vars.
 * \param   textBuf     buffer pointer to text
 * \param   bufLen      length of text buffer
 * \return    Return a pointer to textBuf if success;otherwise return NULL.
 */
int8_t * NCCBrw_sa_initTextValue(uint8_t * textBuf,int32_t bufLen);

/**
 * Get context of the current page.
 * \return   a context handle of current page.
 */
T_DB_ParseCtxtPtr NCCBrw_sa_getParseCtxt(void);

/**
 * Call this function to determine if the current page is exist.
 * \return   Return If exist,return TRUE; otherwise return FALSE.
 */
int32_t NCCBrw_sa_isBrowserActivated(void);

/**
 * Clear actively parsed context
 */
void NCCBrw_sa_clearParseContext(void);

#ifdef DBA_DEBUG
/**
 * Print href info.
 * \param   href    the href to save.
 * \return
 */
void NCCBrw_sa_printInfo(int8_t * href);

/**
 * Print data.
 * \param   str the href to save.
 * \param   num the number to save
 * \return
 */

void NCCBrw_sa_printInfoWithNumber(int8_t * str,int32_t num);
#endif

/**
 * Get the cookie list.
 * \return Return a pointer to cookie list
 */
void * NCCBrw_sa_getCookieList(void);

/**
 * Set current parsing context.
 * \param   ctxt    current parsing context.
 * \return
 */
void NCCBrw_sa_setBrowserCpmCtxt(void * ctxt);

/**
 * Trigger area hylink.
 * \param   imgIndex    index of image.
 * \param   xpos        xpos of the click.
 * \param   ypos        ypos of the click.
 * \return  Return hylink URL.
 */
int8_t * NCCBrw_sa_triggerAreaHot(T_DB_ImgNodeIdx imgIndex
                              ,int32_t xpos
                              ,int32_t ypos
                              );

/**
* Get node pointer
* \param  id      the node id for block memory management
* \param  index   index number
* \return Return a pointer to the node if the node is found;otherwise return NULL.
*/
void* NCCBrw_sa_mmGet(
    int16_t id,
    int32_t index
    );

/**
 * Get last node pointer
 * \param  id      the node id for block memory management
 * \return Return a pointer to the node if the node is found;otherwise return NULL.
 */
void* NCCBrw_sa_mmGetLastNode(
    int16_t id
);

/**
 * Append a node,get node pointer and index
 * \param  id      the node id for block memory management
 * \param  index   pointer to index number
 * \return Return a pointer to the node if success;otherwise return NULL.
 */
void* NCCBrw_sa_mmAppend(
    int16_t id,
    int32_t *index
    );

/**
 * Get Attribute node pointer
 * \param  index   index number of Attribute
 * \return Return a pointer to the node if success;otherwise return NULL.
 */
const T_DB_ComnAttr * NCCBrw_sa_getAttribute( int16_t index );

/**
 * Alloc memory from the block.
 * \param  buf     string buffer pointer
 * \param  len length of string
 * \return <ul>
 *         <li>return block pointer if success
 *         <li>return 0 if fail
 *         </ul>
 */
uint8_t*  NCCBrw_sa_comnBufAppend(uint8_t* buf, int16_t len);

/**
 * Execute public wtai
 * \param  url address
 * \return <ul>
 *         <li>TRUE  WTAI address
 *         <li>FALSE Not WTAI address
 *         </ul>
 */
int32_t NCCBrw_sa_wtai(int8_t * url);

/**
 * Execute streaming
 * \param  url address
 * \param  contentType
 * \return <ul>
 *         <li>TRUE  address/content-type is RTSP/HTTP streaming available
 *         <li>FALSE Not RTSP/HTTP streaming address/content-type
 *         </ul>
 */
int32_t NCCBrw_sa_streaming(int8_t * url, int8_t * contentType);

/**
 * Begin collect
 * \return
 */
void NCCBrw_sa_beginCollect(void);

/**
 * End collect
 * \return
 */
void NCCBrw_sa_endCollect(void);

/**
 * Get parse state
 * \return <ul>
 *           <li>the parse state when success
 *           <li>0, otherwise
 *         </ul>
 */
int32_t NCCBrw_sa_getParseState(void);

/**
 * Get sax handle of html parser
 * \return sax handle
 */
void* NCCBrw_sa_getHtmlParserDesc(void);

/**
 * Set base of current page
 * \param base current page's base
 * \return
 */
void NCCBrw_sa_setDefaultBase( int8_t *base );

/**
 * Convert color value
 * \param clr the color value
 * \return <ul>
 *           <li>the initiated color when success
 *           <li>DBA_COLOR_NULL, otherwise
 *         </ul>
 */
int32_t NCCBrw_sa_colorParse(const int8_t *clr);

/**
 * Convert the hex string to int32_t
 * \param stirng pointer of the string to be converted
 * \return <ul>
 *           <li>int32_t value when success
 *           <li>-1, otherwise
 *         </ul>
 */
int32_t NCCBrw_sa_hexStr2Int(const int8_t *string);

/**
 * Get pictogram data
 * \param localsrc pathname of the picture
 * \param data pointer to the picture content
 * \param len picture content length
 * \return <ul>
 *           <li>TRUE when success
 *           <li>FALSE when fail
 *         </ul>
 */
int32_t NCCBrw_sa_getPictogram(int8_t * localsrc,int8_t **data,int32_t * len);

/**
 * get struct pointer of marquee
 * \param index index of marquee
 * \return
 */
MarqueeStruct * NCCBrw_sa_getMarquee(int16_t index);

/**
 * Init history stack
 * \return
 */
int32_t NCCBrw_sa_hInit( void );

/**
 * Destoy history stack
 * \return
 */
void NCCBrw_sa_unLoadH( void );

/**
 * Reset history stack
 * \return
 */
void NCCBrw_sa_hReset(void);

/**
 * reset ypos block memory
 * \return
 */
void NCCBrw_sa_resetYpos(void);

/**
 * reset box block memory.
 * \return
 */
void NCCBrw_sa_resetBox(void);

/**
 * Parsing wml url
 * \param href the wml url
 * \return <ul>
 *           <li>the namevalue when success
 *           <li>NULL when fail
 *         </ul>
 */
int8_t ** NCCBrw_sa_wmlActVarParse(int8_t *href);


/**
 * Get the tag number using the result finding Tag in DTD tag list.
 * \param string  the tag name we want to index in the tag list.
 * \return <ul>
 *           <li>the tag number when tag is found
 *           <li>-1, otherwise
 *         </ul>
 */
int32_t  NCCBrw_sa_findTag(const int8_t* string);

/**Option struct add, delete or modify functions*/
#ifdef DB_USING_SCRIPT

/**
 * Get field node's pointer by field node's index.
 * \param iField Index of field node.
 * \return field node's pointer.
 */
T_DB_FieldNodePtr NCCBrw_sa_getFieldPtr(T_DB_FieldNodeIdx iField);

/**
 * Get field options number.
 * \param pFirstOption first option node of the field.
 * \return field options number.
 */
int32_t NCCBrw_sa_getOptionsLen(T_DB_OptionNodePtr pFirstOption);

/**
 * Get relevant option pointer by its position of select.
 * \param iFirstOption Index of first option.
 * \param pFirstOption pointer of first option.
 * \param index position of the option, start with zero.
 * \param piOption Index of the relevant option.
 * \return the relevant option pointer.
 */
T_DB_OptionNodePtr NCCBrw_sa_getOptionAt( T_DB_OptionNodeIdx iFirstOption,
                                       T_DB_OptionNodePtr pFirstOption,
                                       uint32_t index,
                                       T_DB_OptionNodeIdx *piOption);

/**
 * Remove a option node from it's parent select.
 * \param pOption pointer of deleting option.
 * \param pField the parent select node pointer.
 * \param delFlag flag whether delete all items of the deleting options.
 */
void NCCBrw_sa_delOpt( T_DB_OptionNodePtr pOption,
                    T_DB_FieldNodePtr pField,
                    int32_t delFlag );

/**
 * Add one option into a select.
 * \param iOption Index of the option to insert.
 * \param iBefOption Index of the before option. INULL means append to tail.
 * \param iField Index of field node to insert.
 */
void NCCBrw_sa_addOptByID( T_DB_OptionNodeIdx iOption,
                        T_DB_OptionNodeIdx iBefOption,
                        T_DB_FieldNodeIdx iField );

/**
 * Get images' number of current document.
 * \return Get images' number of current document.
 */
uint32_t NCCBrw_sa_getImgesLength(void);

/**
 * Get image node pointer by index which start with zero.
 * \param index image index in the document.images array.
 * \return the image node pointer.
 */
T_DB_ImgNodePtr NCCBrw_sa_getImgPtr(uint32_t index);

/**
 * Get image node pointer by its id.
 * \param Id the id of this image element.
 * \return the image node pointer.
 */
T_DB_ImgNodePtr NCCBrw_sa_getImgPtrById(const uint8_t *Id);

/**
 * Get area node's shape in string format by shape type.
 * \param shapeType the shape type of the area node.
 * \return the area node's shape in string format.
 */
const uint8_t * NCCBrw_sa_getAreaShapeStr(uint32_t shapeType);

#ifdef DB_USING_SCRIPT	//added by will.wang
/**
* Get image node index by its node pointer.
* \param pImgNode the image node pointer.
* \return the id of this image element.
*/
T_DB_ImgNodeIdx NCCBrw_sa_getImgIndexByPtr(const T_DB_ImgNodePtr pImgNode);


/**
 * Get area node's shape in string format by shape type.
 * \param shape in string format.
 * \return shapeType the shape type of the area node.
 */
int32_t NCCBrw_sa_getAreaShapeType(uint8_t *areaStr);

#endif

/**
 * Get map's arealist by map name.
 * \param mapname the name of the map element.
 * \return map's arealist.
 */
CommonList * NCCBrw_sa_getAreaList(const uint8_t *mapName);

/**
 * Get link and area number for document.links.length.
 * \return link and area number.
 */
uint32_t NCCBrw_sa_getLinksLength(void);

/**
 * Get linksElem pointer by index which start with zero.
 * \param index link or area index in the document.links array.
 * \return the linksElem node pointer.
 */
T_DB_LinksElemPtr NCCBrw_sa_getLinksElemPtr(uint32_t index);

#endif /* DB_USING_SCRIPT */

/**
 * get a attribute item from the table
 * \param table the ref of AttributeTable
 * \param index the index of attribute
 * \return the pointer to attribute if success, NULL if failed
 */
const BoxAttribute * NCCBrw_sa_BoxAttributeTable_getAttribute(BoxAttributeTable *table, int32_t index);

#ifdef __cplusplus
}
#endif

#endif /*_DBA_ANALYSIS_INTERFACE_*/
