
#ifndef __CACHE_INNERAPI_H__
#define __CACHE_INNERAPI_H__

#ifdef __cplusplus
extern "C" {
#endif

#ifndef T_MOBILE_CACHE

#include <time.h>
#include <stdio.h>
#include <cache_struct.h>

/* Initialization and free functions */

/**
 * Initialize FileListHead which is the head of filelist.
 * \param conFile pointer of configuration files
 * \return
 *      -pointer of FileLIstHead when success
 *      -NULL when fail
 */
FileListHead *recordFileHead(int32_t conFile);

/**
 * Initialize filelist.
 * \param listsize size of the filelist
 * \param filenum number of files which are stored in cache
 * \param conFile pointer of configuration files
 * \return
 *      -pointer of filelist when success
 *      -NULL when fail
 */
FileList *recordFileList(int32_t listsize, int32_t filenum, int32_t confile);

/**
 * Initialize freelist of filelist.
 * \ param listsize size of the filelist
 * \param filenum number of files which are stored in cache
 * \return
 *      -pointer of freelist when success
 *      -NULL when fail
 */
FreeListHead *recordFreeList(int32_t listsize, int32_t filenum);

/**
 * Initialize sortlist of filelist.
 * \param filenum number of files which are stored in cache
 * \param filelist pointer of filelist
 * \return
 *      -pointer of sortlist when success
 *      -NULL when fail
 */
SortHead *recordSortList(int32_t filenum, FileList *filelist);

/**
 * Write the information of filelist and head of filelist into configuration file.
 * \param conFile pointer of configuration file
 * \return
 *      -TRUE when success
 *      -FALSE when fail
 */
int32_t recordConFile(int32_t conFile);

/**
 * Initialize configuration file when start cache in first time.
 * \return
 *      -TRUE when initialize successfully
 *      -FALSE when fail
 */
int32_t firstInit();

/* Adding function */
#define REALLOCSIZE 20

/**
 * Creat file and record the file's information.
 * \param bufLen length of Buf in parameter
 * \param Buf which store the context of file
 * \param fileName the name of file
 * \param URLlen length of URL
 * \param URL the URL of file which is stored in Buf
 * \param ETaglen length of ETag
 * \param ETag entity tag which defined in document "rfc2616"
 * \param expiration file's expiration time
 * \param lastModify file's last modified time
 * \param revalidate Cache-control: must-revalidate which defined in "rfc2616"
 * \param fileType file's type
 * \param charset pointer of this page's character set
 * \return void
 */
void addFile(int32_t bufLen,
               int8_t *Buf,
               int32_t fileName,
               int16_t URLlen,
               int8_t *URL,
               int16_t LastURLlen,
               int8_t *LastURL,
               int16_t ETaglen,
               int8_t *ETag,
               int32_t expiration,
               int32_t lastModify,
               int8_t revalidate,
               int8_t fileType,
               int8_t *charset);

/* Searching function */

/**
 * Search the head pointer of link whose URLlen is the same as URLlen in the parameter.
 * \param URLlen length of URL
 * \param count length of FileListSort
 * \param position [out]the position in SortList which is we last found
 * \return
 *      -pointer of FileListSort when success
 *      -NULL when fail
 */
FileListSort *searchSameURLlen(int16_t URLlen, int32_t count, int32_t *position);

/**
 * Find file in FileList according to its URL.
 * \param URL searching file's URL
 * \param isFind head pointer of link whose elements have the same length of URL
 * \return
 *      -file's position in filelist when success
 *      --1 when fail
 */
int32_t searchSameURLFile(int8_t *URL, FileListSort *isFind);

/**
 * Find the last element of link whose elements have the same length of URL.
 * \param isFind head pointer of link whose elements have the same length of URL
 * \return
 *      -pointer of the last element when success
 *      -NULL when fail
 */
FileList *findSameURLlenLast(FileListSort *isFind);

/* Delete function */
#define FILEEXPIRATION 0
#define FILEHOLDTIME 1
#define FILEBESTSIZE 2

/**
 * Delete a file from cache.
 * \param delMode delete mode:
 *          -FILEEXPIRATION delete file by its expiration time
 *          -FILEHOLDTIME delete file by file-resident time
 *          -FILEBESTSIZE delete file by file's size
 */
int32_t deleteFile(int8_t delMode, int32_t filesize);

/**
 * Delete the appointed file in FileList and SortList but not add the space to FreeList.
 * \param sortlistPos the position in SortList
 * \param preDelFile the pointer of file which is the front of appointed file
 * \param pDelFile the pointer of file which will be deleted
 * \return void
 */
void clearFileInList(int32_t sortlistPos, FileList *preDelFile, FileList *pDelFile);

/**
 * Delete the appointed file in FileList and SortList and add the space to FreeList.
 * \param sortlistPos the position in SortList
 * \param preDelFile the pointer of file which is the front of appointed file
 * \param pDelFile the pointer of file which will be deleted
 * \return void
 */
void deleteFileInList(int32_t sortlistPos, FileList *preDelFile, FileList *pDelFile);

/**
 * Judge a file whether is expired.
 * \param nowTime the local time now
 * \param pFile pointer of file which will be judged
 * \return
 *      -TRUE when the file is expired
 *      -FALSE when the file is now expried
 */
int32_t judgeExpired(int32_t nowTime, FileList *judgeFile);

#else /* T_MOBILE_CACHE */
#include <cache_struct.h>
#include <ncccache.h>

#define REALLOCSIZE 20
#define ITEMNAMELEN CRTL_strlen(CACHEDIRECTORY)+15

/**
 * Count an item's expiration time.
 *\param si pointer to T_Cache_SourceInfo structure
 *\return<ul>
 *       <li>item's expiration time when cache should cache this source
 *       <li>-1 means do not cache this source
 *       </ul>
 */
int32_t cache_countExpireTime(T_Cache_SourceInfoPtr si);

/**
 * Set an item's informations.
 *\param cx cache context
 *\param item pointer to T_Cache_ItemList structure
 *\param si pointer to t_cache_sourceinfo structure
 *\return<ul>
 *       <li>TRUE when success
 *       <li>FALSE when fail
 *       </ul>
 */
int32_t cache_setItemInfo(T_Cache_CX cx,
                          T_Cache_ItemList *item,
                          T_Cache_SourceInfoPtr si);

/**
 * Create item in cache and record informations about the item in the itemlist.
 * \param cx the pointer to cache context
 * \param item pointer to T_Cache_ItemList structure
 * \param buf which store the content of item
 * \param buflen length of buf in parameter
 * \return
 *      -the number of full items actually write when success
 *      -FALSE when fail
 */
int32_t cache_addContentToItem(T_Cache_CX cx,
                               T_Cache_ItemList *item,
                               const int8_t *buf,
                               int32_t buflen);

/**
 * Reading item.
 * \param cx the pointer to cache context
 * \param item pointer to T_Cache_ItemList structure
 * \param buf which store the content
 * \param length reading length
 * \return
 *      -the number of full items actually read when success
 *      -0 when fail
 */
int32_t cache_readContentFromItem(T_Cache_CX cx,
                                  T_Cache_ItemList *item,
                                  int8_t *buf,
                                  int32_t length);

/**
 * Add an item to IndexTable.
 * \param cx cache context
 * \param urllen length of item's url
 * \param itempos item's position in itemlist
 * \return void
 */
void cache_addItemToIndexTable(T_Cache_CX cx, uint16_t urllen, int32_t itempos);

/**
 * Create an item.
 *\param cx cache context
 *\param si pointer to t_cache_sourceinfo structure
 */
T_Cache_ItemList * cache_createItem(T_Cache_CX cx, T_Cache_SourceInfoPtr si);

/**
 * Clean an item and remove it form the IndexTable.
 *\param cx cache context
 *\param indextablepos item position in IndexTable
 *\param preitem forward item
 *\param item pointer to the item will be deleted
 *\return void
 */
void cache_cleanItem(T_Cache_CX cx, int32_t indextablepos, T_Cache_ItemList *preitem, T_Cache_ItemList *item);

/**
 * Delete an item.
 *\param cx cache context
 *\param indextablepos the item position in IndexTable
 *\param preitem forward item
 *\param item pointer to the item will be deleted
 *\return void
 */
void cache_deleteItem(T_Cache_CX cx, int32_t indextablepos, T_Cache_ItemList *preitem, T_Cache_ItemList *item);

/* See cache_innerapi.h */
/**
 * Delete an item whose storing time is the longest.
 *\param cx cache context
 *\return void
 */
void cache_deleteFirstComer(T_Cache_CX cx);

/**
 * Search the head pointer of link whose URLlen is the same as URLlen in the parameter.
 * \param cx cache context
 * \param urllen length of url
 * \param count length of IndexTable
 * \param position [out]the position in IndexTable which is we last found
 * \return
 *      -pointer of T_Cache_IndexTable when success
 *      -NULL when fail
 */
T_Cache_IndexTable *cache_searchIndexTable(T_Cache_CX cx, uint16_t urllen, int32_t count, int32_t *position);

/**
 * Find item in ItemList according to its url.
 * \param cx cache context
 * \param url searching item's url
 * \param it pointer to T_Cache_IndexTable structure, it->length == urllen
 * \param preItem [out] pointer to the preitem
 * \return
 *      -item's position in ItemList when success
 *      --1 when fail
 */
int32_t cache_searchItemList(T_Cache_CX cx, uint8_t *url, T_Cache_IndexTable *it, T_Cache_ItemList **preItem);

/**
 * Find the last element of link whose elements have the same length of URL.
 * \param cx cache context
 * \param it pointer to T_Cache_IndexTable structure, it->length == urllen
 * \return
 *      -pointer of the last element when success
 *      -NULL when fail
 */
T_Cache_ItemList *cache_findLastItem(T_Cache_CX cx, T_Cache_IndexTable *it);

/**
 * First startup cache.
 *\param cachesize cache size
 *\return<ul>
 *       <li>TRUE when success
 *       <li>FALSE when fail
 *       </ul>
 */
int32_t cache_firstStartUp(int32_t cachesize);

/**
 * Create cache context when cache startup.
 *\param handle configuration file handle
 *\return<ul>
 *       <li>pointer to cache context when success
 *       <li>NULL when fail
 *       </ul>
 */
T_Cache_CX cache_createCX(int32_t handle);

/**
 * Create ItemList when cache startup.
 *\param listsize size of the ItemList
 *\param itemnum number of item
 *\param handle configuration file handle, if handle == 0 means just create a default ItemList
 *\return<ul>
 *       <li>pointer to T_Cache_ItemList structure when success
 *       <li>NULL when fail
 *       </ul>
 */
T_Cache_ItemList *cache_createItemList(int32_t listsize, int32_t itemnum, int32_t handle);

/**
 * Create FreeList header when cache startup.
 *\param listsize size of ItemList
 *\param itemnum number of item
 *\return<ul>
 *       <li>pointer to T_Cache_FreeListHead structure when success
 *       <li>NULL when fail
 *       </ul>
 */
T_Cache_FreeListHead *cache_createFreeListHead(int32_t listsize, int32_t itemnum);

/**
 * Create IndexTable when cache startup.
 *\param cx cache context
 *\param itemlist current itemlist in cache
 *\return<ul>
 *       <li>pointer to T_Cache_IndexTableHead structure when success
 *       <li>NULL when fail
 *       </ul>
 */
T_Cache_IndexTableHead *cache_createIndexTable(T_Cache_CX cx, T_Cache_ItemList *itemlist);

/**
 * Set cache size.
 *\param cx cache context
 *\param cacheSize cache size
 *\return<ul>
 *       <li>TRUE when success
 *       <li>FALSE when fail
 *       </ul>
 */
int32_t cache_setCacheSize(T_Cache_CX cx, int32_t cacheSize);

/**
 * Free cache's ItemList, IndexTable and FreeList.
 *\param cx cache context
 *\return void
 */
void cache_freeEachList(T_Cache_CX cx);

/**
 * Free cache context.
 *\param cx cache context
 *\return void
 */
void cache_freeContext(T_Cache_CX *cx);

/**
 * Write cache information into configuration file.
 *\param cx cache context
 *\return<ul>
 *       <li>TRUE when success
 *       <li>FALSE when fail
 *       </ul>
 */
int32_t cache_createConFile(T_Cache_CX cx);

/**
 * Get an item's properties.
 *\param item pointer to a cache item
 *\param itempro pointer to t_cache_itemproperty structure
 *\return<ul>
 *       <li>TRUE when success
 *       <li>FALSE when fail
 *       </ul>
 */
int32_t cache_getItemProperty(T_Cache_ItemPropertyPtr itempro, T_Cache_ItemList *item);

#endif /* T_MOBILE_CACHE */

#ifdef __cplusplus
}
#endif

#endif /* __CACHE_INNERAPI_H__ */
