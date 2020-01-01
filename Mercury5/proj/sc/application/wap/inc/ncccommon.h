/**
 * @file ncccommon.h
 * Common Module Service Layer
 *
 * Service API exposed by the Common Module
 *
 * <!-- #interface list begin -->
 * \section ncccommon interface
 * - NCCCommon_wbmpToBmpMem()
 * - NCCCommon_getWbmpInfo()
 * - NCCCommon_getUcs2ValueFromGb2312()
 * - NCCCommon_encodeBase64()
 * - NCCCommon_decodeBase64()
 * - NCCCommon_encodeQuotedPrintable()
 * - NCCCommon_decodeQuotedPrintable()
 * - NCCCommon_encode7Bit()
 * - NCCCommon_decode7Bit()
 * - NCCCommon_winlatin1CharToWcs()
 * - NCCCommon_i18nDetectCharEncodingByBOM()
 * - NCCCommon_i18nGuessCharEncoding()
 * - NCCCommon_getCharsetFromName()
 * - NCCCommon_mbsToUtf8()
 * - NCCCommon_utf8ToMbs()
 * - NCCCommon_memoryInit()
 * - NCCCommon_memoryDestroy()
 * - NCCCommon_malloc()
 * - NCCCommon_freePtr()
 * - NCCCommon_free()
 * - NCCCommon_realloc()
 * - NCCCommon_strDup()
 * - NCCCommon_memDup()
 * - NCCCommon_memoryUsedMemSize()
 * - NCCCommon_bmmCreate()
 * - NCCCommon_bmmGet()
 * - NCCCommon_bmmGetLastBlock()
 * - NCCCommon_bmmiMalloc()
 * - NCCCommon_bmmiMallocStr()
 * - NCCCommon_bmmiMallocMult()
 * - NCCCommon_bmmiFree()
 * - NCCCommon_bmmDestroy()
 * - NCCCommon_getAbsoluteURL()
 * - NCCCommon_escapeURL()
 * - NCCCommon_resolveURL()
 * - NCCCommon_unescapeURL()
 * - NCCCommon_getURLComponent()
 * - NCCCommon_recombineURL()
 * - NCCCommon_parseDataContentType()
 * <!-- #interface list end -->
 */

#ifndef __NCC_COMMON_H__
#define __NCC_COMMON_H__


#include <ncc_types.h>
#include <nccport_i18n.h>

/** align type of platform */
#define DB_IS_LITTLE_ENDIAN

#ifdef __cplusplus
extern "C" {
#endif

#define NCC_BROWSER_VERSION     "1.0.0.0"
#define NCC_COMMON_VERSION      "1.0.0.0"
#define NCC_MMS_VERSION         "1.0.0.0"

/* url module macro definition*/
#define URI_BAD        FALSE
#define URI_OK          TRUE

/*next macros are defined to a bit of a word*/
#define URL_STORE_SCHEME      0x01
#define URL_STORE_HOSTINFO    0x02
#define URL_STORE_HOSTNAME    0x04
#define URL_STORE_PORT        0x08
#define URL_STORE_PATH        0x10
#define URL_STORE_FRAGMENT    0x20
#define URL_STORE_QUERY       0x40
#define URL_STORE_USER        0x80
#define URL_STORE_PASSWORD    0x100
#define URL_STORE_PARAMETER   0x200
/* next two macros are defined for program using */
/* scheme://user:pass@hostname:port/path?query#fragment;parameter */
#define URL_STORE_HOSTNAME_ALL    URL_STORE_SCHEME | URL_STORE_USER | \
    URL_STORE_PASSWORD | URL_STORE_HOSTNAME | URL_STORE_PORT |  \
    URL_STORE_PATH | URL_STORE_QUERY | URL_STORE_FRAGMENT |URL_STORE_PARAMETER
/* scheme://hostinfo/path?query#fragment */
#define URL_STORE_HOSTINFO_ALL    URL_STORE_SCHEME | URL_STORE_HOSTINFO |\
    URL_STORE_PATH | URL_STORE_QUERY | URL_STORE_FRAGMENT |URL_STORE_PARAMETER

#define URL_MASK_ALL_CONVERT      1<<0    /* convert all reserved & special characters*/
#define URL_MASK_SP_CONVERT       1<<1    /* URL_MASK_ALL_CONVERT,but convert space to plus,plus to %2b*/
#define URL_MASK_NSLASH_CONVERT   1<<2    /* URL_MASK_ALL_CONVERT,but not convert specail such as:'/' '+' ';' and so on*/

/** defining dynamic memory functions */
typedef void   *(*pubMallocFunc)(uint32_t);
typedef void   *(*pubReallocFunc)(void *, uint32_t);
typedef void    (*pubFreeFunc)(void *);

/** \name BMM_MACRO
  * config macro
  */
#define BMM_DEFAULT_ALGINBYTE   4   /**< if sizeof each block can't be divisibility by DMM_ALGIN_BYTE,will compensates it */
#define BMM_FREE_SUPPORT        0   /**< 1 is invalid this time */
#define BMM_INVALID_IPTR        -1  /**< invalid iptr */
#define BMM_BLOCKARRAY_STEP     5   /**< invalid iptr */
#define BMM_DEFAULT_ZERO        1   /**< init the data block to 0 */

struct commMBlock
{
    int8_t **       mBlockArray;        /**< pointer arrays to each block group */
#if BMM_FREE_SUPPORT
    int32_t *       mBlockUseState;     /**< when ifree enable,a bit refer to a item */
#endif
    pubMallocFunc   mMalloc;            /**< malloc function pointer */
    pubReallocFunc  mRealloc;           /**< malloc function pointer */
    pubFreeFunc     mFree;              /**< malloc function pointer */
    int32_t         mBlockNum;          /**< amount of pointer arrays */
    int32_t         mCuriPtr;           /**< last block used */
    int32_t         mTotaliPtr;         /**< last block used */
    int16_t         mFirstBlockSize;    /**< amount of first block group */
    int16_t         mEachBlockSize;     /**< amount of other block group */
    int16_t         mItemSize;          /**< size of block item */
}; /**< defining struct of block memory management */

typedef struct commMBlock T_Comm_MBlock;    /**< defining struct of block memory management */
typedef T_Comm_MBlock * T_Comm_MBlockPtr;   /**< defining struct pointer of block memory management */

/**
 * Convert code from UCS2 to GB2312.
 * \param des           Gb2312 codes store into
 * \param src           Ucs2 codes from
 * \param len           Count of character in ucs2
 * \return
 *     <li>Return a pointer to des if data is valid;</li>
 *     <li>Return NULL if the data is invalid.</li>
 * \attention Size of des should not be smaller than len * 2 + 1.
 */
uint8_t * NCCCommon_ucs2ToGb2312(uint8_t * des, uint16_t * src, uint16_t len);

/**
 * Convert code from UTF8 to UCS2.
 * \param des           UCS2 codes store into
 * \param src           UTF8 codes from
 * \param len           length of character in UTF8
 * \return
 *     <li>Return a pointer to des if data is valid;</li>
 *     <li>Return NULL if the data is invalid.</li>
 * \attention Size of des should not be smaller than (len + 1) * 2.
 */
uint16_t * NCCCommon_utf8ToUcs2(uint16_t * des, uint8_t * src, uint16_t * len);

/**
 * Convert code from GB2312 to UCS2.
 * \param des           UCS2 codes store into
 * \param src           GB2312 codes from
 * \param len           Count of character in UCS2.
 * \return
 *     <li>Return a pointer to des if data is valid;</li>
 *     <li>Return NULL if the data is invalid.</li>
 * \attention Size of des should not be smaller than (len + 1) * 2.
 */
uint16_t * NCCCommon_gb2312ToUcs2(uint16_t * des, uint8_t * src, uint16_t * len);

/**
 * Convert code from UCS2 to UTF8.
 * \param des           UTF8 codes store into
 * \param src           UCS2 codes from
 * \param len           Count of character in UCS2.
 * \return
 *     <li>Return a pointer to des if data is valid;</li>
 *     <li>Return NULL if the data is invalid.</li>
 * \attention Size of des should not be smaller than len * 4 + 1.
 */
uint8_t * NCCCommon_ucs2ToUtf8(uint8_t * des, uint16_t * src, uint16_t len);

/**
 * Convert wbmp to bmp
 * \param mfunc         the function pointer to malloc.
 * \param pData         wbmp buffer.
 * \param size          As input,it save size of wbmp; As output it return the size of transfered bmp data.
 * \return              Return a pointer to bmp buffer if success;otherwise return NULL.
 * \attention The 3th parameter will be modfiy if tranfermation is success.
 */
int8_t * NCCCommon_wbmpToBmpMem(pubMallocFunc mfunc, int8_t * pData, int32_t * size);

/**
 * Get width and height of wbmp.
 * \param pwbmp         wbmp buffer.
 * \param width         pointer to width .
 * \param height        pointer to height .
 * \return              Return a pointer to wbmp buffer if success;otherwise return NULL.
 */
uint8_t * NCCCommon_getWbmpInfo(uint8_t * pwbmp, uint16_t * width, uint16_t * height);

/**
 * Convert GB2312 char sequence into unicode value.
 * \param mchar         GB2312 word.
 * \return              Return the unicode value in Small Endian.
 */
uint16_t NCCCommon_getUcs2ValueFromGb2312(uint8_t * mchar);

/**
 * Encode base64
 * \param dest          dest buffer to save encode base64 data
 * \param destLen       dest buffer length
 * \param src           source data to be encoded
 * \param srcLen        source buffer length, and when return, give out how many bytes has been encoded
 * \return
 *        -when success, return a positive integer of dest buffer length,
 *                       if input dest buffer is NULL or destLen is 0,
 *                       return dest buffer length that user should allocate to save encoding data
 *        -when failed, return -1
 */
int32_t NCCCommon_encodeBase64(uint8_t * dest, int32_t destLen, uint8_t * src, int32_t * srcLen);

/**
 * Decode base64
 * \param dest          dest buffer to save decode base64 data
 * \param destLen       dest buffer length
 * \param src           source data to be decoded
 * \param srcLen        source buffer length, and when return, give out how many bytes has been decoded
 * \return
 *        -when success, return a positive integer of dest buffer length,
 *                       if input dest buffer is NULL or destLen is 0,
 *                       return dest buffer length that user should allocate to save decoding data
 *        -when failed, return -1
 */
int32_t NCCCommon_decodeBase64(uint8_t * dest, int32_t destLen, uint8_t * src, int32_t * srcLen);

/**
 * Encode quoted-printable
 * \param dest          dest buffer to save encode quoted-printable data
 * \param destLen       dest buffer length
 * \param src           source data to be encoded
 * \param srcLen        source buffer length, and when return, give out how many bytes has been encoded
 * \return
 *        -when success, return a positive integer of dest buffer length,
 *                       if input dest buffer is NULL or destLen is 0,
 *                       return dest buffer length that user should allocate to save encoding data
 *        -when failed, return -1
 */
int32_t NCCCommon_encodeQuotedPrintable(uint8_t * dest, int32_t destLen, uint8_t * src, int32_t * srcLen);

/**
 * Decode quoted-printable
 * \param dest          dest buffer to save decode quoted-printable data
 * \param destLen       dest buffer length
 * \param src           source data to be decoded
 * \param srcLen        source buffer length, and when return, give out how many bytes has been decoded
 * \return
 *        -when success, return a positive integer of dest buffer length,
 *                       if input dest buffer is NULL or destLen is 0,
 *                       return dest buffer length that user should allocate to save decoding data
 *        -when failed, return -1
 */
int32_t NCCCommon_decodeQuotedPrintable(uint8_t * dest, int32_t destLen, uint8_t * src, int32_t * srcLen);

/**
 * Encode 7bit
 * \param dest          dest buffer to save encode 7bit data
 * \param destLen       dest buffer length
 * \param src           source data to be encoded
 * \param srcLen        source buffer length, and when return, give out how many bytes has been encoded
 * \return
 *        -when success, return a positive integer of dest buffer length,
 *                       if input dest buffer is NULL or destLen is 0,
 *                       return dest buffer length that user should allocate to save encoding data
 *        -when failed, return -1
 */
int32_t NCCCommon_encode7Bit(uint8_t * dest, int32_t destLen, uint8_t * src, int32_t * srcLen);

/**
 * Decode 7bit
 * \param dest          dest buffer to save decode 7bit data
 * \param destLen       dest buffer length
 * \param src           source data to be decoded
 * \param srcLen        source buffer length, and when return, give out how many bytes has been decoded
 * \return
 *        -when success, return a positive integer of dest buffer length,
 *                       if input dest buffer is NULL or destLen is 0,
 *                       return dest buffer length that user should allocate to save decoding data
 *        -when failed, return -1
 */
int32_t NCCCommon_decode7Bit(uint8_t * dest, int32_t destLen, uint8_t * src, int32_t * srcLen);

/**
 * Get relevant Unicode value for winLatin1 character.
 * \param winLatin1Char the winLatin1 character's code.
 * \return the relevant Unicode value.
 */
uint16_t NCCCommon_winlatin1CharToWcs(const uint32_t winLatin1Char);

/**
 * Detect the encoding of the buffer using the first bytes.
 * reference: http://www.unicode.org/faq/utf_bom.html#22.
 *
 * \param in:  a pointer to the first bytes of the document buffer,
 *             must be at least 2 bytes long
 *             (at least 4 if encoding is UTF4 variant).
 * \param len:  the length of the buffer
 * \return the preferred character encoding name (const string)
 *         NULL will be returned if detect nothing.
 */
const int8_t *
NCCCommon_i18nDetectCharEncodingByBOM(const uint8_t *in, int32_t len);

/**
 * Guess the encoding of the buffer using the first bytes.
 * \param in:  a pointer to the first bytes of the document buffer,
 *             must be at least 2 bytes long.
 * \param len:  the length of the buffer.
 * \return the preferred character encoding name (const string).
 */
const int8_t *
NCCCommon_i18nGuessCharEncoding(const uint8_t *in, int32_t len);

/**
 * Get charset value from charset name
 *
 * \param name Charset name.
 * \return charset value or NCC_CHARSET_UNSUPPORTED (-1) if charset is not supported
 */
NCCPort_NccCharset_t NCCCommon_getCharsetFromName(const uint8_t * name);

/**
 * Convert multibyte string of specified charset to UTF-8 string.
 * Note NO terminating '\0' will be appended to the output unicode string.
 *
 * @param charset Charset of mbs.
 * @param mbs  Multibyte string to be converted.
 * @param mbsLen Number of bytes (in mbs) to be converted.
 * @param utfBuf  Buffer for converted UTF-8 string.
 *                If utfBuf is NULL, bytesConsumed (see below) will still be updated but no actual conversion will be done.
 * @param bufSize The size (number of bytes) of utfBuf
 * @param bytesConsumed The number of bytes in mbs that have been successfully converted.
 *
 * @return The number of UTF-8 bytes converted.
 */
int32_t NCCCommon_mbsToUtf8( NCCPort_NccCharset_t charset,
                              const uint8_t *mbs,
                              int32_t mbsLen,
                              uint8_t *utfBuf,
                              int32_t bufSize,
                              int32_t *bytesConsumed );

/**
 * Convert UTF-8 string to multibyte string with specified charset.
 * Note NO terminating '\0' will be appended to the output multibyte string.
 *
 * @param charset  Charset of mbsBuf.
 * @param utf UTF-8 string to be converted.
 * @param utfLen Number of bytes (in UTF-8 string) to be converted.
 * @param mbsBuf  Buffer to hold converted multibyte characters.
 *                If mbsBuf is NULL, utfBytesConverted will still be updated but no actual conversion will be done.
 * @param bufSize The size (number of bytes) of mbsBuf
 * @param bytesConsumed The number of bytes in mbs that have been successfully converted.
 *
 * @return The number of converted bytes.
 */
int32_t NCCCommon_utf8ToMbs( NCCPort_NccCharset_t charset,
                              const uint8_t *utf,
                              int32_t utfLen,
                              uint8_t *mbsBuf,
                              int32_t bufSize,
                              int32_t *bytesConsumed );

typedef struct _memBlock
{
    void * memContext;  /*context of common malloc management*/
    void * memPtr;      /*address of memeory block*/
    int32_t minSize;    /*minimal block size to malloc*/
    int32_t maxSize;    /*maximal block size to malloc*/
    int32_t size;       /*size of the memory block*/
}T_memBlock;

typedef struct _memoryMgr
{
   T_memBlock * memBlocks;
   int32_t memBlocksCount;
   int32_t used;

}T_memoryMgr;

#ifdef MEM_USING_MYMALLOC
/**
 * Init memory manager
 * \param   memBlocks         Define all memory block info and allocated memory by caller
                              .The caller should fill the fields except "memContext"
                              .The caller should not free the memory block and the "memBlocks"
                              before call NCCCommon_memoryInit.
 * \param   memBlocksCount    Start address of memory block.
 * \return
 */
void  NCCCommon_memoryInit(
                            T_memBlock * memBlocks
                            ,int32_t memBlocksCount
                            );

/**
 * Unload memory manager of browser
 * \return
 */
void  NCCCommon_memoryDestroy(void);

/**
 * init memory manager
 * \return
 */
void NCCCommon_initCommonMemory(void);

/**
 * finalize memory manager
 * \return
 */
void NCCCommon_finalizeCommonMemory(void);
#endif

/**
 * Malloc function of browser.
 * \param size malloc size
 * \return If success,return a pointer to the allocated memorty block;
 *      otherwise return NULL.
 */
void * NCCCommon_lr_malloc(uint32_t size, uint32_t lr);
void * NCCCommon_malloc(uint32_t size);

/**
 * Calloc function of browser.
 * \param number malloc block number
 * \param size malloc size
 * \return If success,return a pointer to the allocated memorty block;
 *      otherwise return NULL.
 */
void* NCCCommon_calloc(uint32_t number, uint32_t size);

/**
 * Free function of browser using address of pointer.
 * \param mem [in/out] pointer address of memory address
 * \return
 */
void NCCCommon_freePtr(void ** mem);

/**
 * Free function of browser using pointer directly.
 * \param mem  pointer to memory address
 * \return
 */
void NCCCommon_free(void * mem);

/**
 * Realloc function of browser.
 * \param memblock the pointer to memory address
 * \param size size of new buffer
 * \return   Return a void pointer to the reallocated memory block if success;otherwise return NULL.
 */
void* NCCCommon_lr_realloc(void* memblock, uint32_t size, uint32_t lr);
void* NCCCommon_realloc(void* memblock,uint32_t  size);

/**
 * String duplication.
 * \param src  pointer to string
 * \return      If success,return a pointer to duplicated string.otherwise return NULL.
 */
int8_t * NCCCommon_strDup(  const int8_t*   src);

/**
 * Memory duplication.
 * \param src pointer to memory
 * \param size  size of memory to replicate
 * \return      If success,return a pointer to duplicated memory blcok.otherwise return NULL.
 */
void * NCCCommon_memDup(  const void*   src,int32_t  size);


/**
 * Create a instance of block memory management
 * \param  firstsize   amount of first block group
 * \param  eachSize    amount of other block group
 * \param  itemSize    size of block item
 * \param  alignByte   align byte,0:default
 * \param  userMalloc  malloc func pointer
 * \param  userRealloc realloc func pointer
 * \param  userFree    free func pointer
 * \return <ul>
 *         <li>return instance pointer if success
 *         <li>return 0 if fail
 *         </ul>
 * \sa NCCCommon_bmmDestroy()
 */
T_Comm_MBlockPtr NCCCommon_bmmCreate(int16_t firstSize
                             ,int16_t eachSize
                             ,int16_t itemSize
                             ,int16_t alignByte
                             ,pubMallocFunc userMalloc
                             ,pubReallocFunc userRealloc
                             ,pubFreeFunc userFree
                             );

/**
 * Get pointer of a block by index
 * \param  mPtr    instance pointer of BMM
 * \param  index   index of block
 * \return <ul>
 *         <li>return block pointer if success
 *         <li>return 0 if fail
 *         </ul>
 * \sa
 */
void * NCCCommon_bmmGet(T_Comm_MBlockPtr mPtr
                ,int32_t index
                );

/**
 * Get last block pointer
 * \param  mPtr    instance pointer of BMM
 * \return <ul>
 *         <li>return block pointer if success
 *         <li>return 0 if fail
 *         </ul>
 * \sa
 */
void * NCCCommon_bmmGetLastBlock(T_Comm_MBlockPtr mPtr);

/**
 * \param  mPtr    instance pointer of BMM
 * \param  index   index of block
 * \return <ul>
 *         <li>return block pointer if success
 *         <li>return 0 if fail
 *         </ul>
 * \sa NCCCommon_bmmiFree
 */
void * NCCCommon_bmmiMalloc(T_Comm_MBlockPtr mPtr
                    ,int32_t * index
                    );

/**
 * Assign a string block from BMM
 * \param  mPtr    instance pointer of BMM
 * \param  str     string buffer pointer
 * \param  length  length of string
 * \return <ul>
 *         <li>return block pointer if success
 *         <li>return 0 if fail
 *         </ul>
 * \sa NCCCommon_bmmiFree
 */
int8_t * NCCCommon_bmmiMallocStr(T_Comm_MBlockPtr mPtr
                         ,int8_t * str
                         ,int16_t length
                         );

/**
 * Assign a multiple block from BMM
 * \param  mPtr        instance pointer of BMM
 * \param  src         buffer pointer
 * \param  length      length of buffer
 * \param  alignbyte   align byte
 * \return <ul>
 *         <li>return block pointer if success
 *         <li>return 0 if fail
 *         </ul>
 * \sa NCCCommon_bmmiFree
 */
int8_t * NCCCommon_bmmiMallocMult(T_Comm_MBlockPtr mPtr
                          ,int8_t * src
                          ,int16_t length
                          ,int16_t alignByte
                          );

#if BMM_FREE_SUPPORT

/**
 * Free a block to BMM
 * \param  T_Comm_MBlockPtr    instance pointer of BMM
 * \param  index               index of block
 * \return
 * \sa NCCCommon_bmmiMalloc
 */
int32_t NCCCommon_bmmiFree(T_Comm_MBlockPtr mPtr
                   ,int16_t index
                   );

#endif /* BMM_FREE_SUPPORT */

/**
 * Destroy a instance of BMM
 * \param  T_Comm_MBlockPtr    instance pointer of BMM
 * \return
 * \sa NCCCommon_bmmCreate
 */
void NCCCommon_bmmDestroy(T_Comm_MBlockPtr mPtr);

/**
 * Make the url absoluted
 * \param url           the url gave
 * \param result_url        the result string
 * \return  Return URI_OK if success;otherwise return URI_BAD.
 */
int32_t NCCCommon_getAbsoluteURL(
    int8_t *url,
    int8_t *result_url);

/**
 * Encode the string
 * \param str           the string being coded
 * \param result_str        the string been coded
 * \param smask---the mask digned for space and slash,can be
 *              URL_MASK_ALL_CONVERT,URL_MASK_SP_CONVERT,URL_MASK_NSLASH_CONVERT
 * \return  Return URI_OK if success;otherwise return URI_BAD.
 */
int32_t NCCCommon_escapeURL(
    int8_t *str,
    int8_t *result_str,
    uint8_t smask);

/**
 * Resolve the url      all cases must allocate space for the
 * \param urlbase       the base url
 * \param url           the current url
 * \param result_url        the result string
 * \return  Return URI_OK if success;otherwise return URI_BAD.
 */
int32_t NCCCommon_resolveURL(
    int8_t *urlbase,
    int8_t * url,
    int8_t *result_url);

/**
 * Decode the url by escape mode.
 * \param str           the string to decode.
 * \param result_str        the string to decode.
 * \return  Return URI_OK if success;otherwise return URI_BAD.
 */
int32_t NCCCommon_unescapeURL(int8_t *str,
                                  int8_t *result_str);

/**
 * Get one part of url by compType.
 * \param url        the base string
 * \param compType  the type of the part ,see header file.
 * \param result_comp   the part string been got,note:space must be allocated
 * \param pmalloc       malloc function pass to here
 * \param pfree     free function pass to here
 * \return  Return URI_OK if success;otherwise return URI_BAD.
 */
int32_t NCCCommon_getURLComponent(
    int8_t *url,
    int32_t compType,
    int8_t *result_comp);

/**
 * Modify corresponding part of the url.
 * \param url           the base string
 * \param compType  the type of the part of url ,see header file.
 * \param newComp   the new content of the part of url .
 * \param result_url        the string been modified
 * \return  Return URI_OK if success;otherwise return URI_BAD.
 */
int32_t NCCCommon_recombineURL(
    int8_t *url,
    int32_t compType,
    int8_t *newComp,
    int8_t *result_url);

/**
 * Free memory get from URL module.
 * \param url  pointer to memory address
 * \return Return TRUE if success;otherwise return FALSE.
 */
int32_t NCCCommon_freeURL(int8_t *url);

int8_t *NCCCommon_parseDataContentType(uint8_t *data, int32_t len);

#define NCCBrw_sa_malloc NCCCommon_malloc
#define NCCBrw_sa_free NCCCommon_freePtr
#define NCCBrw_sa_free2 NCCCommon_free
#define NCCBrw_sa_strDup NCCCommon_strDup
#define NCCBrw_sa_realloc NCCCommon_realloc
#define NCCBrw_sa_memDup NCCCommon_memDup
#ifdef __cplusplus
}
#endif

/*The meaning of __SLDPM_FREE etc are in mmi_common_def.h*/
#if defined(__TARGET__) && defined(__arm)
#define __SLDPM_FREE__  __attribute__((section(".sldpm_free")))
#define __SLDPM_WAP_SECTION__  __attribute__((section(".wap_section")))
#else
#define __SLDPM_FREE__
#define __SLDPM_WAP_SECTION__  
#endif


#endif /* __NCC_COMMON_H__ */
