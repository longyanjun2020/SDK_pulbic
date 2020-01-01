
#ifndef  __IFLAYER_DLMAIN_H__
#define  __IFLAYER_DLMAIN_H__

#include <ncc_types.h>
#include <ncccommon_list.h>
#include <nccdlm.h>
#include <iflayer_dlbdparser.h>
#include <iflayer_dlimg.h>
#include <ncciflayer.h>
#ifdef DB_USING_CACHE
#include <ncccache.h>
#endif /* DB_USING_CACHE */

/** defining if convert wbmp to bmp*/
//#define DB_DL_CONVERTWBMP 1
#define DB_DL_CONVERTWBMP 0

/** defining each block size when reading data*/
#define DB_DL_READ_BLOCKSIZE 51200

/** defining each block size when unzip data*/
#define DB_DL_READ_BLOCKSIZE_UNZIP 512

/** defining each block size when parse data*/
#define DB_DL_PARSE_BLOCKSIZE 512


/** defining timeout when download,unit second*/
#define DB_DL_TIMEOUT 30

/** defining unkown file download support*/
#define DB_DL_FILE_DOWNLOAD

/** defining step size of download*/
#ifdef NCC_WAP_SUPPORT_WIFI
#define DB_DL_SETP_SIZE 40960
#else
#define DB_DL_SETP_SIZE 4096
#endif

/** defining invalid index cache file*/
#define DB_DL_NOCACHEFILE -1
#define DB_DL_DONOTCACHEFILE -2

#ifdef DB_USING_CACHE
#define CACHE_AVAILABE_JS
#define CACHE_AVAILABE_IMG
#define CACHE_AVAILABE_PAGE
#define HEADER_ADD_LEN 100 /*length of "If-None-Match: " and "\r\n" and "If-Modified-Since: Sun, 06 Nov 1994 08:49:37 GMT\r\nRange: bytes=2147483648-\r\n"*/
#endif

typedef enum {
    DB_DL_URI_ITEM_TYPE_NORMAL,
    DB_DL_URI_ITEM_TYPE_OMA_DD,
    DB_DL_URI_ITEM_TYPE_OMA_DD_NOTIFY
} DB_DL_URI_ITEM_Type;

/** defining URI Item*/
typedef struct _DB_DL_URI_Item
{
    int8_t * url;               /**< url of resource*/
    int32_t  nRangeStart;
    int8_t * data;              /**< post data would sent*/
    int8_t * contentType;       /**< contenttype of post data*/
    //union    {
        int32_t length;         /**< length of post data*/
        int32_t  notFirst;      /**< if it is first check contenttype.used in js*/
    //};
    //int32_t  isDownload;            /**< if it is omadownlaod.used in oma download*/
    T_DLM_ReqNodeHandle reqHandle;          /**< handle for DLM*/
    DB_DL_URI_ITEM_Type type;
}T_DB_DL_URI_Item;

/** defining the pointer of URI item*/
typedef T_DB_DL_URI_Item * T_DB_DL_URI_ItemPtr;


/**defining img queue*/
typedef struct _DB_DL_Img_Queue
{
    T_DLM_ReqNodeHandle reqHandle;  /**< handle for DLM request*/
    int16_t inPos;                  /**< last index,use for add img index*/
    int16_t outPos;                 /**< used index,use for add img getting*/
    int16_t imgType;                /**< img type of current img*/
    int16_t imgCount;               /**< how many imgs loaded*/
    int16_t hasSearchFlag;          /**< has searched before*/
    int16_t nouse;
    T_DB_ImgNodeIdx imgQueue[DB_MAXIMGINPAGE];
}T_DB_DL_Img_Queue;

/** defining the pointer of img queue*/
typedef T_DB_DL_Img_Queue * T_DB_DL_Img_QueuePtr;

/** defining download list*/
typedef struct _DB_DL_List
{
    CommonList * pageQueue;     /**< web page queue list*/
    CommonList * frameQueue;    /**< frame page queue list*/
    CommonList * jsQueue;       /**< js file queue list*/
    CommonList * cssQueue;      /**< css file queue list*/
    CommonList * objectQueue;   /**< object file queue list*/
    CommonList * imgOfPage;     /**< data list for img*/
    CommonList * docFromScript;     /**< data list for data of wml file*/
    int8_t * referringUrl;  /**< refering url*/
    int8_t * charset;       /**< charset from protocol*/
    int8_t * curUrl;        /**< current url,maybe different because of relocation*/
    int8_t * baseUrl;       /**< base url*/
    int8_t * data;          /**< download data*/
    T_DL_DD * dd;           /**< dd handle*/
    int32_t  dataLength;            /**< length of download data*/
    int32_t  dlLength;              /**< length of origianl non-decompress download data*/
    T_DLM_SessionHandle dlmHandle;  /**< handle for DLM session*/
    T_DLM_ReqNodeHandle bgReqHandle; /**< handle of dlm request*/
    int32_t notBgFirst;             /**<  if first reading state of bgsound*/
    int16_t loadState;              /**< loaded state*/
    int16_t docType;                /**< loaded state*/
#ifdef DB_USING_CACHE
    int32_t cacheFileIndex;         /**< The file index in cache to be appended*/
    int32_t cacheParseOk;           /**< parsed by cache data*/
#endif
    int32_t backWard;               /**< if it is prev://*/
    int32_t netMode;                /**< net mode/*/
    T_DB_DL_Img_Queue imgQueue;     /**< img queue*/
    int8_t  recvBuffer[DB_DL_READ_BLOCKSIZE];
}T_DB_DL_List;

/** defining handle of DL*/
typedef T_DB_DL_List * T_DB_DL_Handle;


/**
* init DL module, called when init browser
*/
void * fnDB_DLInit(void);


/**
* reset DL module, called when one download ended.
*/
void  fnDB_DLReset(void);


/**
* unload DL module called when unload browser.
*/
void  fnDB_DLUnInit(void);

/**
* set status of DL
*   \param  status defined by T_DB_DL_State
*/
void fnDB_DLSetState(T_DB_DL_State state);


/**
* get current DLM handle
*   \return  DLM handle inited when init browser
*/
T_DLM_SessionHandle fnDB_DLGetDLMHandle(void);

/**
* get current DLM handle
*   \return  DLM handle inited when init browser
*/
void fnDB_DLUnInitAList( T_DB_DL_Queue_Type queueType);

/**
* get first uri in certain queue
*   \param   queueType      defined by T_DB_DL_Queue_Type
*   \return  pointer of uri item,failed if return NULL
*/
T_DB_DL_URI_ItemPtr fnDB_DLGetFirstUri(T_DB_DL_Queue_Type queueType);

/**
* delete first uri in certain queue
*   \param   queueType      defined by T_DB_DL_Queue_Type
*/
void fnDB_DLDeleteFirstUri(T_DB_DL_Queue_Type queueType);

/**
* get first index of imgs
*   \return     index of imgs
*/
T_DB_ImgNodeIdx  fnDB_DLGetFirstImg(void );

/**
* delete first index of imgs
*   \return
*/
void fnDB_DLDeleteFirstImg(void );

/**
* delete all imgs
*   \return
*/
void fnDB_DLDeleteAllImg(void );

/**
* get pointer of img queue
*   \return     pointer of img queue
*/
T_DB_DL_Img_QueuePtr fnDB_DLGetImgQueue(void);

/**
*  get DL handle
*   \return  DL handle
*/
T_DB_DL_Handle fnDB_DLGetDLHandle(void);

/** declare browser context*/
extern T_DB_BrowserCtxtPtr browserCtxt;

/** clear wml cache,same operation as NCCBrw_iflayer_dlDestroyList*/
#define iflayer_dlDestroyWmlCache NCCBrw_iflayer_dlDestroyList

/** clear document cache,same operation as NCCBrw_iflayer_dlDestroyList*/
#define iflayer_dlDestroyDocumentCache NCCBrw_iflayer_dlDestroyList

/**
* check first data block,and set doc charset
*   \return  TRUE:have document to wroten   FALSE:NO
*/
int32_t fnDB_DoScriptDocWrite(void);

/**
* Add URI for oma download
*   \param  url URI of file to download
*   \return TRUE:SUCCESS;FALSE:FAILED
*/
int32_t fnDB_DLAddUriForOmaDL(int8_t * url, int8_t *data, int8_t *contentType, int32_t length, DB_DL_URI_ITEM_Type type);

/**
* Get referring uri
*   \return referring uri
*/
int8_t *  fnDB_DLGetReferringUri(void);

/**< add to js download queue*/
#define fnDB_DLAddJs(a) NCCBrw_iflayer_dlAddUri(a,0,NULL,NULL,0,DB_QUEUE_SCRIPT)

/**< add to page download queue*/
#define fnDB_DLAddPage(a,b) NCCBrw_iflayer_dlAddUri((a),0,(b),NULL,(b)?CRTL_strlen((char *)(b)):0,DB_QUEUE_PAGE)

#ifdef DB_USING_CACHE

/**
 * Save download file to cache
 * \param  drh          handle of dlm request
 * \param  dataBuf      pointer of data buffer
 * \param  dataLen      length of data buffer
 * \param  itemUrl      url of the resource
 * \param  curUrl       url after redirect
 * \param  cacheType    type of file,see CACHE_FILETYPE
 * \param  charset      charset of file,see CACHE_FILETYPE
 * \return
 *      -TRUE  success
 *      -FALSE fail
 */
int32_t iflayer_cachesave(T_DLM_ReqNodeHandle drh
                          ,int8_t * dataBuf
                          ,int32_t dataLen
                          ,int8_t * itemUrl
                          ,int8_t * curUrl
                          ,CACHE_FILETYPE cacheType
                          ,int8_t * charset
                          );

/**
 * Check if the resource expired , return data buffer if not expired(after alternation)
 * \param  drh          handle of dlm request
 * \param  itemUrl      url of the resource
 * \param  fileSize     size of the resource
 * \param  charset      charset of the resource
 * \return
 *      -!=NULL  Data buffer,need be freed by caller
 *      -NULL    Failed
 */
int8_t * iflayer_getunexpireddata(T_DLM_ReqNodeHandle drh
                              ,int8_t * itemUrl
                              ,int32_t *fileSize
                              ,int8_t ** charset
                              );

/**
 * Check cache before download , return data buffer if not expired(before alternation)
 * \param  url          url of the resource
 * \param  addHeader    additional header if need download
 * \param  fileSize     size of the resource
 * \param  charset      charset of the resource
 * \return
 *      ->NULL  Data buffer,need be freed by caller
 *      -NULL   Need download
 *      --1     Failed
 */
int8_t * iflayer_checkcachestate(int8_t * url
                                 ,int8_t ** addHeader
                                 ,int32_t * fileSize
                                 ,int8_t ** charset
                                 );

/*
 * Check a url to determine if it is a file path
 * \param url       Url for check
 * \param defmode   Default mode
 * \param outUrl    Native url
 * \return          net mode: see enum T_DB_NetMode
 */
int32_t iflayer_checkNetMode(int8_t * url
                             ,T_DB_NetMode defMode
                             );

#endif

#endif
