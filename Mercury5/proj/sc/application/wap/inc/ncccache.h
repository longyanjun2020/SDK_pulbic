/**
 * @file
 * Cache Module Service Layer
 *
 * Service API exposed by the cache module.
 *
 * <!-- #interface list begin -->
 * \section ncccache Interface
 * - NCCBrw_cache_init()
 * - NCCBrw_cache_close()
 * - NCCBrw_cache_add()
 * - NCCBrw_cache_delFile()
 * - NCCBrw_cache_getFile()
 * - NCCBrw_cache_getFileInForce()
 * - NCCBrw_cache_getFileInHistory()
 * - NCCBrw_cache_getGMTTime()
 * - NCCBrw_cache_countLocalExpireTime()
 * - NCCBrw_cache_addToFile()
 * - NCCBrw_cache_getFileInt()
 * - NCCBrw_cache_getFilePtr()
 * - NCCBrw_cache_setFileInt()
 * - NCCBrw_cache_judgeFile()
 * - NCCBrw_cache_parsePageInCache()
 * - NCCBrw_cache_Clear()
 * <!-- #interface list end -->
 */

#ifndef T_MOBILE_CACHE

#ifndef __NCC_CACHE_H__
#define __NCC_CACHE_H__

#ifdef __cplusplus
extern "C" {
#endif

typedef enum {
    CACHE_JS,
    CACHE_IMG,
    CACHE_WML,
    CACHE_HTML,
    CACHE_GZIP,
    CACHE_DEFLATE
    }CACHE_FILETYPE;

typedef enum {
    CACHE_FILENAME,
    CACHE_FILESIZE,
    CACHE_EXPIRATION,
    CACHE_LASTMODIFY,
    CACHE_REVALIDATE,
    CACHE_TYPEOFFILE,
    CACHE_URL,
    CACHE_ETAG,
    CACHE_LASTURL,
    CACHE_CHARSET
    }CACHE_FILEINFOTYPE;

/**
 * set cache Max Size in FS.
 * \param cacheSize length of max Size
 */
void NCCBrw_setCacheMaxSize(int32_t cacheSize);

/**
 * get the max cache size value
 * \return the max cache size value
 */
int32_t NCCBrw_getCacheMaxSize(void);

/**
 * Initialize cache when start browser.
 * \return
 *      -TRUE when success
 *      -FALSE when fail
 */
int32_t NCCBrw_cache_init(void);

/**
 * Close cache when close browser.
 * \return
 *      -TRUE when success
 *      -FALSE when fail
 */
int32_t NCCBrw_cache_close(void);

/**
 * Add file to cache.
 * \param bufLen length of Buf in parameter
 * \param Buf which store the context of file
 * \param URL the URL of file which is stored in Buf
 * \param ETag entity tag which defined in document "rfc2616"
 * \param expiration file's expiration time
 * \param lastModify file's last modified time
 * \param revalidate Cache-control: must-revalidate which defined in "rfc2616"
 * \param fileType file's type
 * \param charset pointer of this page's character set
 * \return void
 */
void NCCBrw_cache_add(int32_t bufLen,
                   int8_t *Buf,
                   int8_t *URL,
                   int8_t *LastURL,
                   int8_t *ETag,
                   int32_t expiration,
                   int32_t lastModify,
                   int8_t revalidate,
                   int8_t fileType,
                   int8_t *charset);

/**
 * Delete an appointed file.
 * \param URL file's URL
 * \param URLlen length of URL
 * \return void
 */
void NCCBrw_cache_delFile(int8_t *URL, int16_t URLlen);

/**
 * Get an appointed file's content.
 * \param URL file's URL
 * \param URLlen length of URL
 * \param ETag [out]use to return this file's Etag to browser
 * \param lastModify [out]to return this file's lastModify time to browser
 * \param fileLen [out]return this file's size
 * \param charset [out]return this file's charset
 * \return
 *      -file content when find file successfully
 *      -NULL when fail in findding file
 */
int8_t *NCCBrw_cache_getFile(int8_t *URL, int16_t URLlen, int8_t **ETag, int32_t *lastModify, int32_t *fileLen, int8_t **charset);

/**
 * Get an appointed file's content whether the file was expired.
 * \param URL file's URL
 * \param URLlen length of URL
 * \param fileLen [out]return this file's size
 * \param charset [out]return this file's charset
 * \return
 *      -file content when find file successfully
 *      -NULL when fail in findding file
 */
int8_t *NCCBrw_cache_getFileInForce(int8_t *URL, int16_t URLlen, int32_t *fileLen, int8_t **charset);

/**
 * Get an appointed file's content in history mechanism.
 * \param URL file's URL
 * \param URLlen length of URL
 * \param ETag [out]use to return this file's Etag to browser
 * \param lastModify [out]to return this file's lastModify time to browser
 * \param fileLen [out]return this file's size
 * \param charset [out]return this file's charset
 * \return
 *      -file content when find file successfully
 *      -NULL when fail in findding file
 */
int8_t *NCCBrw_cache_getFileInHistory(int8_t *URL, int16_t URLlen, int8_t **ETag, int32_t *lastModify, int32_t *fileLen, int8_t **charset);

/**
 * Converts a UTC time string to a GMT time string.
 * \param nowTime the time in elapsed seconds from 1970.1.1
 * \return
 *      -GMT time string when success
 *      -NULL when fail
 */
int8_t *NCCBrw_cache_getGMTTime(int32_t *nowTime);

/**
 * Count Expire time in local time.
 * \param no_cache Cache-Control : no-Cache means do not cache entity
 * \param Date_value is the value of the origin server's Date: header
 * \param max_age_value denote an appropriate value of the number of seconds carried by the "max-age" directive
 * \param Expire_value denote the value of the Expires header
 * \param Age_value is the value of Age: header received by the cache with the response
 * \param ETag pointer to this page's ETag
 * \param lastModify file's last modified time
 * \param revalidate Cache-control: must-revalidate which defined in "rfc2616"
 * \return
 *      -expire time in local time when success
 *      --1 means do not cache the entity
 */
int32_t NCCBrw_cache_countLocalExpireTime(int32_t no_cache,
                             int32_t Date_value,
                             int32_t max_age_value,
                             int32_t Expire_value,
                             int32_t Age_value,
                             int8_t *ETag,
                             int32_t lastModify,
                             int32_t revalidate);

/**
 * Add content to a existent file
 * \param fileContent the content which will be writed to file
 * \param fileLen length of the fileContent
 * \param fileName name of file
 * \param fileURL the URL of this file reference to the net page
 * \return
 *      -TRUE when success
 *      -FALSE when fail
 */
int32_t NCCBrw_cache_addToFile(int8_t *fileContent, int32_t fileLen, int32_t fileName, int8_t *fileURL);

/**
 * Get specified information of a file.
 * \param URL file's URL
 * \param infoType specify which information we will get, now support :
 *   CACHE_FILENAME,
 *   CACHE_FILESIZE,
 *   CACHE_EXPIRATION,
 *   CACHE_LASTMODIFY,
 *   CACHE_REVALIDATE,
 *   CACHE_TYPEOFFILE,
 * \return
 *      -specified information of the file when success
 *      --1 when fail in findding file
 */
int32_t NCCBrw_cache_getFileInt(int8_t *URL, int32_t infoType);

/**
 * Get specified information of a file.
 * \param URL file's URL
 * \param infoType specify which information we will get, now support :
 *   CACHE_URL,
 *   CACHE_ETAG,
 *   CACHE_LASTURL,
 *   CACHE_CHARSET
 * \return
 *      -specified information of the file when success
 *      -NULL when fail in findding file
 */
int8_t *NCCBrw_cache_getFilePtr(int8_t *URL, int32_t infoType);

/**
 * Set specified information of a file.
 * \param URL file's URL
 * \param infoType specify which information we will get
 * \param setValue
 * \return
 *      -TRUE when success
 *      -FALSE when fail
 */
int32_t NCCBrw_cache_setFileInt(int8_t *URL, int32_t infoType, int32_t setValue);

/**
 * Judge whether an appointed file is expired.
 * \param URL file's URL
 * \param URLlen length of URL
 * \param ETag [out]use to return this file's Etag to browser
 * \param lastModify [out]to return this file's lastModify time to browser
 * \param fileLen [out]return this file's size
 * \return
 *      -TRUE when the file is not expired
 *      -FALSE when the file is expired
 */
int32_t NCCBrw_cache_judgeFile(int8_t *URL, int16_t URLlen, int8_t **ETag, int32_t *lastModify, int32_t *fileLen);

/**
 * Parse a page which is stored in cache.
 * \param URL page's URL, use this URL to find the file which stores the content of that page.L
 * \param fileType specific page's type CACHE_WML : wml page; CACHE_HTML : html page
 * \return
 *      -TRUE when parse successfully
 *      -FALSE when the file is not exist in cache or parse fail
 */
int32_t NCCBrw_cache_parsePageInCache(int8_t *URL, int32_t fileType);

/**
 * Clear all files in cache.
 * \return void
 */
void NCCBrw_cache_Clear(void);

#ifdef __cplusplus
}
#endif

#endif /* __NCC_CACHE_H__ */

#else /* T_MOBILE_CACHE */


/**
 * @item
 * Cache Module Service Layer
 *
 * Service API exposed by the cache module.
 *
 * <!-- #interface list begin -->
 * \section ncccache Interface
 * - NCCBrw_cache_init()
 * - NCCBrw_cache_destory()
 * - NCCBrw_cache_setCacheSize()
 * - NCCBrw_cache_clearItem()
 * - NCCBrw_cache_openItem()
 * - NCCBrw_cache_writeItem()
 * - NCCBrw_cache_readItem()
 * - NCCBrw_cache_closeItem()
 * - NCCBrw_cache_deleteItem()
 * - NCCBrw_cache_checkItem()
 * <!-- #interface list end -->
 */

#ifndef __NCC_CACHE_H__
#define __NCC_CACHE_H__

#ifdef __cplusplus
extern "C" {
#endif

/** Indicates that visit item failed. */
#define CACHE_ITEM_VISIT_FAILURE -1

typedef enum Cache_ItemStatus {
    CACHE_ITEM_COMPLETE,
    CACHE_ITEM_UNCOMPLETE
}T_CACHE_ITEMSTATUS;

typedef enum Cache_OpenMode {
    CACHE_NORMAL_READ,
    CACHE_FORCE_READ,
    CACHE_HISTORY_READ,
    CACHE_WRITE,
    CACHE_APPEND
}T_CACHE_OPENMODE;

/* define cache context */
struct t_cache_context;
typedef struct t_cache_context * T_Cache_Context;

/* define source information structure */
struct t_cache_sourceinfo{
    uint8_t *url; /* source url */
    uint8_t *lasturl; /* source lasturl */
    uint8_t *etag; /* source etag */
    uint8_t *charset; /* source charset */
    uint8_t *mimetype; /* source mimetype */
    int32_t nocache; /* 1 when http header has "Control-cache: no-cache" */
    int32_t data; /* data value in http header, if not 0 */
    int32_t maxage; /* max-age value in http header, if not -1 */
    int32_t age; /* age value in http header, if not 0 */
    int32_t expiration; /* expired value in http header, if not 0 */
    int32_t lastmodify; /* source lastmodify */
    int32_t revalidate; /* 1 when http header has "revalidate" information, if not 0 */
};
typedef struct t_cache_sourceinfo * T_Cache_SourceInfoPtr;

/* define cache context */
struct t_cache_item;
typedef struct t_cache_item * T_Cache_ItemPtr;

/* define cache item information structure */
struct t_cache_itemproperty{
    int32_t needrevalidate; /* specifies the item is needed to revalidate(TRUE) or not(FALSE) */
    int32_t itemstatus; /* specifies the item is completed or not */
    int32_t itemsize; /* size of the item */
    int32_t lastmodify; /* lastmodify flag */
    uint8_t *url; /* item url */
    uint8_t *lasturl; /* item lasturl */
    uint8_t *etag; /* etag string */
    uint8_t *charset; /* character set */
    uint8_t *mimetype; /* MIME type */
};
typedef struct t_cache_itemproperty T_Cache_ItemProperty;
typedef struct t_cache_itemproperty * T_Cache_ItemPropertyPtr;

/**
 * Initialize cache and return the cache context.
 *\param cacheSize specify cache size
 *\return <ul>
 *              <li>cache context when success
 *              <li>NULL when fail
 *              </ul>
 */
T_Cache_Context NCCBrw_cache_init(int32_t cacheSize);

/**
 * Destory cache context and close cache.
 *\param cx cache context
 *\return <ul>
 *              <li>TRUE when success
 *              <li>FALSE when fail
 *              </ul>
 */
int32_t NCCBrw_cache_destory(T_Cache_Context *cx);

/**
 * Set cache size.
 *\param cx the current cache context
 *\param size cache size
 *\return <ul>
 *              <li>TRUE when success
 *              <li>FALSE when fail
 *              </ul>
 */
int32_t NCCBrw_cache_setCacheSize(T_Cache_Context cx, int32_t size);


/**
 * Delete all items in cache.
 *\param cx the current cache context
 *\return <ul>
 *              <li>TRUE when success
 *              <li>FALSE when fail
 *              </ul>
 */
int32_t NCCBrw_cache_clear(T_Cache_Context *cx);

/**
 * Open an item in cache.
 *\param cx the current cache context
 *\param si pointer to T_Cache_SourceInfoPtr structure
 *\param openmode type of access permitted, as follows:
 * CACHE_NORMAL_READ : Opens for reading in normal state.
 *                     If the item does not exist or cannot be found or is expired, the function call fails.
 * CACHE_FORCE_READ : Opens for reading. If the item does not exist or cannot be found, the function call fails.
 * CACHE_HISTORY_READ : Opens for reading in history mechanism(rfc2616 13.13)
 * CACHE_WRITE : Opens an empty item for writing. If the given item exists, its contents are destroyed.
 * CACHE_APPEND : Opens for writing at the end of the item (appending) without removing
 *                the EOF marker before writing new data to the item; creates the item first if it doesn't exist.
 * Note: in read mode, in the parameter "si" structure only "url" is meaningful, and in write and append mode,  other items are needed.
 *\return <ul>
 *              <li>pointer to T_Cache_ItemPtr structure when success
 *              <li>NULL when fail
 *              </ul>
 */
T_Cache_ItemPtr NCCBrw_cache_openItem(T_Cache_Context cx,
                                   T_Cache_SourceInfoPtr si,
                                   T_CACHE_OPENMODE openmode);

/**
 * Writes data to a cache item.
 *\param cx the current cache context
 *\param ip pointer to T_Cache_ItemPtr structure
 *\param buffer pointer to data to be written
 *\param length maximum number of bytes to be written
 *\return <ul>
 *              <li>the number of full items actually write when success
 *              <li>#CACHE_ITEM_VISIT_FAILURE when fail
 *              </ul>
 */
int32_t NCCBrw_cache_writeItem(T_Cache_Context cx,
                            T_Cache_ItemPtr ip,
                            const int8_t *buffer,
                            int32_t length);

/**
 * Reads data from a cache item.
 *\param cx the current cache context
 *\param ip pointer to T_Cache_ItemPtr structure
 *\param buffer storage location for data
 *\param length maximum number of bytes to be read
 *\param readType the reading type, as follow:
 * CACHE_READ_NORMAL : if the cache item is expired the function will not return the item data
 * CACHE_READ_FORCE : read item data whatever
 * CACHE_READ_HISTORY : read item in history mechanism(rfc2616 13.13)
 *\return <ul>
 *              <li>the number of full items actually read when success when success
 *              <li>#CACHE_ITEM_VISIT_FAILURE when fail
 *              </ul>
 */
int32_t NCCBrw_cache_readItem(T_Cache_Context cx,
                           T_Cache_ItemPtr ip,
                           int8_t *buffer,
                           int32_t length);

/**
 * Close a cache item.
 *\param cx the current cache context
 *\param ip pointer to pointer to T_Cache_ItemPtr structure
 *\param status specifies a cache item status, as follow:
 * CACHE_ITEM_COMPLETE : specifies the item is not a whole source data
 * CACHE_ITEM_UNCOMPLETE : specifies the item is a partial source data
 * Only if the item was opened by "w" and "a" mode this parameter is significative.
 *\return <ul>
 *              <li>TRUE when successfully closed
 *              <li>FALSE when fail
 *              </ul>
 */
int32_t NCCBrw_cache_closeItem(T_Cache_Context cx, T_Cache_ItemPtr *ip, T_CACHE_ITEMSTATUS status);

/**
 * Delete a item in cache.
 *\param cx the current context
 *\param url specifies the item by its url
 *\return <ul>
 *              <li>TRUE when successfully deleted
 *              <li>FALSE when fail
 *              </ul>
 */
int32_t NCCBrw_cache_deleteItem(T_Cache_Context cx, int8_t *url);

/**
 * Get an item's properties.
 *\param cx cache current context
 *\param ip pointer to a cache item
 *\param itempro pointer to t_cache_itemproperty structure
 *\return<ul>
 *       <li>TRUE when success
 *       <li>FALSE when fail
 *       </ul>
 */
int32_t NCCBrw_cache_getItemProperty(T_Cache_Context cx, T_Cache_ItemPtr ip, T_Cache_ItemPropertyPtr itempro);

#ifdef __cplusplus
}
#endif

#endif /* __NCC_CACHE_H__ */

#endif /* T_MOBILE_CACHE */
