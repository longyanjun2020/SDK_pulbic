
#ifndef __WAP_CONFIG_H__
#define __WAP_CONFIG_H__

#include "ncc_types.h"
/*Enable this MACRO if using T-MOBILE version*/
//#define NCC_BROWSER_TMOBILE

/*Enable this MACRO if DEBUG mode is needed.*/
//#define   DBA_DEBUG

/** Enable this MACRO if strict XHTML is needed*/
//#define DB_USING_XHTML_LIMIT

/** Align type of platform */
#define DB_IS_LITTLE_ENDIAN
//#define DB_IS_BIG_ENDIAN

/** Defining MACRO "DB_IS_BIG_ENDIAN" if the platform is big endian*/

/** Enable this MACRO if wap1.2 is choose*/
#ifndef NCC_BROWSER1_2

/** Enable this MACRO if ECMASCRIPT is needed*/
#ifdef NCC_BROWSER_ESMPCLIENT
#define   DB_USING_SCRIPT
#endif

/** Enable this MACRO if JS download is needed*/
#ifdef DB_USING_SCRIPT
#define   DB_USING_JS_FILE
#endif

/** Enable this MACRO if gzip is needed. */
#ifdef NCC_BROWSER_ZLIB
#define DB_USING_GZIP
#endif

/** Enable this MACRO if css is needed */
#if defined(NCC_BROWSER_CSS)
#define DB_USING_CSS
#endif

/** Enable this MACRO if the HTML is needed */
#ifdef      __NCC_BROWSER_HTML__
#define     DB_USING_HTML
#define     DB_USING_HTML_ERROR_PAGE
#else
#define     NCC_DISABLE_HTML_PAGE
#endif

#define DB_USING_FRAME

/** Enable this MACRO if Object is needed*/
#define     DB_USING_OBJECT

/** Enable this MACRO if pictogram is needed*/
//#define     DB_USING_PICTOGRAM

/** Enable this MACRO if map-area is needed*/
#ifdef DB_USING_SCRIPT
#define	DB_USING_AREA
#endif

/** Enable this MACRO if marquee is needed*/
#define     DB_USING_MARQUEE

/** Enable this MACRO if OMA download is needed*/
//#define     DB_USING_OMA_DOWNLOAD

/**Enable this MACRO if memory collect is needed*/
#define DB_USING_MCOLLECT

/** Enable this MACRO if background sound is needed*/
#define     DB_USING_BGSOUND

#endif /* NCC_BROWSER1_2 */

/** Enable this MACRO if TABLE is needed*/
//undefine DB_USING_TABLE to fixed india ft test issue(when access http://www.songs.pk display a empty page), table can render well
//#define   DB_USING_TABLE

/** It will cut the overtoped part when width of img larger than width of screen if enable this MACRO.*/
#define   DB_BIGIMG_RESIZEMODE_CUT  0

/** It will shrink to width of screen when width of img larger than width of screen if enable this MACRO.*/
#define   DB_BIGIMG_RESIZEMODE_SHRINK   1

/** Enable this MACRO if want to save cookie into file in HTTP module*/
#define DB_USING_FILE_COOKIE

/** Enable this MACRO if Record feature is needed*/
#ifdef __NCC_BROWSER_RECORD__
#define DB_USING_RECORD
#endif

/** Enable this MACRO if want to use authorication function in HTTP module*/
#ifdef NCC_WHTTP
#define DB_USING_HTTP_AUTH
#endif

#define SHORT_OF_MEMORY_SIZE (700 * 1024)
#define MIN_MEMORY_WHENNEW_SIZE (500 * 1024)
/**Result of file system*/
#define DB_FILE_SUCCESS     0   /**<Open file success.*/
#define DB_FILE_FAIL        -1  /**<Open file failed.*/
#define DB_FILE_EXIST       -2  /**<File already exist.*/

/**Mode of file open*/
#define DB_FILE_OPEN_READ   0   /**<File open for read.*/
#define DB_FILE_OPEN_WRITE   1  /**<File open for write.*/

/**Document  type*/
#define DOC_UNKNOW 0    /**<Unkown doc*/
#define DOC_HTML    1   /**<HTML doc*/
#define DOC_WML     2   /**<WML doc*/
#define DOC_WBXML   3   /**<WBXML doc*/
#define DOC_DD      4   /**<OMA download describe doc*/
#define DOC_INVALID -1  /**<Invalid doc*/

/**Max header pairs*/
#define DB_WAPHEADER_MAXNUM 150

#ifdef NCC_BROWSER_CACHE
#define DB_USING_CACHE
#endif /* NCC_BROWSER_CACHE */

#ifdef __NCC_BROWSER_TLS__
#define DB_USING_HTTP_TLS
#endif /* __NCC_BROWSER_TLS__ */

#ifdef NCC_MULTIPART
#define DB_USING_MULTIPART
#endif /* NCC_MULTIPART */

#define USE_OLD_OPENSSL

#endif /* __WAP_CONFIG_H__ */

