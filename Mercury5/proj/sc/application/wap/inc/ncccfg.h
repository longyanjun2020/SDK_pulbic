
/**
 * @file ncccfg.h
 * cfg Module Service Layer
 *
 * Service API exposed by the cfg Module
 *
 * <!-- #interface list begin -->
 * \section ncccfg interface
 * - NCCBrw_cfg_initBrowserConfig();
 * - NCCBrw_cfg_saveBrowserConfig();
 * - NCCBrw_cfg_destroyBrowserConfig();
 * - NCCBrw_cfg_restoreDefaultCfg();
 * - NCCBrw_cfg_getInitStatus();
 * - NCCBrw_cfg_getCookieSize();
 * - NCCBrw_cfg_setCookieSize();
 * - NCCBrw_cfg_getCacheSize();
 * - NCCBrw_cfg_setCacheSize();
 * - NCCBrw_cfg_getFontMode();
 * - NCCBrw_cfg_setFontMode();
 * - NCCBrw_cfg_getEncodingTotalNum();
 * - NCCBrw_cfg_getCodepageHandle();
 * - NCCBrw_cfg_getCurCodepage();
 * - NCCBrw_cfg_setCurCodepage();
 * - NCCBrw_cfg_getScreenResolutionList();
 * - NCCBrw_cfg_getCurScreenResolution();
 * - NCCBrw_cfg_setCurScreenResolution();
 * - NCCBrw_cfg_getAdvanceOption();
 * - NCCBrw_cfg_setAdvanceOption();
 * - NCCBrw_cfg_unsetAdvanceOption();
 * - NCCBrw_cfg_resetAdvanceOption();
 * - NCCBrw_cfg_getNetSettingCount();
 * - NCCBrw_cfg_getCurNetSetting();
 * - NCCBrw_cfg_setCurNetSetting();
 * - NCCBrw_cfg_getNetMode();
 * - NCCBrw_cfg_getCurHomepage();
 * - NCCBrw_cfg_getNetSetting();
 * - NCCBrw_cfg_addNetSetting();
 * - NCCBrw_cfg_changeNetSetting();
 * - NCCBrw_cfg_deleteNetSetting();
 * - NCCBrw_cfg_setNetSettingProxyPort();
 * - NCCBrw_cfg_getNetSettingProxyPort();
 * - NCCBrw_cfg_setProtocolHeaderString();
 * - NCCBrw_cfg_getProtocolHeaderstring();
 * - NCCBrw_cfg_getProtocolHeadersCount();
 * - NCCBrw_cfg_getProtocolHeaderNameValue();
 * - NCCBrw_cfg_changeProtocolHeaderNameValue();
 * - NCCBrw_cfg_addProtocolHeaderNameValue();
 * - NCCBrw_cfg_deleteProtocolHeaderNameValue();
 * - NCCBrw_cfg_getFavoriteCount(void);
 * - NCCBrw_cfg_getFavoriteItem();
 * - NCCBrw_cfg_addFavoriteItem();
 * - NCCBrw_cfg_changeFavoriteItem();
 * - NCCBrw_cfg_delFavoriteItem();
 * - NCCBrw_cfg_getHistoryCountAndIndex();
 * - NCCBrw_cfg_getHistoryItem();
 * - NCCBrw_cfg_addHistoryItem();
 * - NCCBrw_cfg_clearHistoryItems();
 * <!-- #interface list end -->
 */

#ifndef __NCC_CFG_H__
#define __NCC_CFG_H__

#include "ncc_types.h"
#include <stdio.h>
#include <stdlib.h>
#ifndef _WIN32_WCE
#include <errno.h>
#endif
#include "wap_config.h"

#ifdef __cplusplus
extern "C"{
#endif

#ifdef _WIN32_WCE
#define CFG_VERSION                     (0x1|0x0000)
#else
#define CFG_VERSION                     (0x1|0x0200)
#endif

enum{
CFG_INIT_CORRUPT = 1,
CFG_INIT_UPDATE =2
};

#define NCC_CFG_MAX_IPADDR_LENGTH       128     /**< max ip address length */
#define NCC_CFG_MAX_HEADERS_LENGTH      1024    /**< max protocol header length */

#define NCC_CFG_MAX_NETSETTING_NUM      10      /**< max net setting number */

#define NCC_CFG_MAX_FAVORATEITEMS       50      /**< max favorite items number */

#define NCC_CFG_MAX_HISTORYITEMS        20      /**< max history records number */
#define NCC_CFG_PROTOCOLHEADER_MAXNUM   50      /**< max protocol header (name/value) number */
#define NCC_CFG_COOKIE_SIZE             0x1000  /**< max cookie size */
#define NCC_CFG_CACHE_SIZE              0x2800  /**< max cache size */
#define NCC_CFG_VECTOR_FONT_SIZE        20      /**< default vector font size */

/** default advance options */
#define NCC_CFG_DEFAULT_ADVANCEOPTION    (  NCC_CFG_SUPPORT_SCRIPT | \
                                            NCC_CFG_SUPPORT_CSS    | \
                                            NCC_CFG_SUPPORT_TABLE  | \
                                            NCC_CFG_SUPPORT_IMAGE  | \
                                            NCC_CFG_SUPPORT_ALIGN  | \
                                            NCC_CFG_SUPPORT_COOKIE | \
                                            NCC_CFG_SUPPORT_CACHE  | \
                                            NCC_CFG_SUPPORT_SECURITY | \
                                            NCC_CFG_SUPPORT_BGSOUND | \
                                            NCC_CFG_SUPPORT_PUSH)
#define SCREEN_RESOLUTION_HIGH_BITS   16
enum {
NCC_CFG_RESOLUTION_AUTO,    /**< default screen resolution */
NCC_CFG_RESOLUTION_101_80,  /**< screen resolution 101 * 80 */
NCC_CFG_RESOLUTION_128_128, /**< screen resolution 128 * 128 */
NCC_CFG_RESOLUTION_160_120, /**< screen resolution 160 * 120 */
NCC_CFG_RESOLUTION_176_220, /**< screen resolution 176 * 220 */
NCC_CFG_RESOLUTION_208_285, /**< screen resolution 208 * 285 */
NCC_CFG_RESOLUTION_240_320, /**< screen resolution 240 * 320 */
NCC_CFG_RESOLUTION_228_248, /**< screen resolution 228 * 248 */
NCC_CFG_RESOLUTION_308_168, /**< screen resolution 308 * 168 */
NCC_CFG_RESOLUTION_640_480, /**< screen resolution 640 * 480 */
NCC_CFG_RESOLUTION_800_600, /**< screen resolution 800 * 600 */
NCC_CFG_RESOLUTION_1024_768,/**< screen resolution 1024* 768 */
NCC_CFG_RESOLUTION_MAXNUM /**< max screen resoltution selection number */
};

/* Don't accept text / html if no html parser included  */
#ifdef DB_USING_HTML
#define NCC_CFG_DEFAULT_WAP_HEADER "Accept:application/vnd.wap.mms-message,application/vnd.wap.wmlscriptc,application/vnd.wap.wmlc,application/vnd.wap.wbxml,text/wnd.wap.wmlscript,text/vnd.sun.j2me.app-descriptor,application/java-archive,application/octet-stream,image/vnd.wap.wbmp;level=0,image/x-bmp,image/bmp,image/jpg,image/jpeg,image/pjpeg,image/gif,image/png,application/vnd.oma.drm.message,application/vnd.wap.connectivity-wbxml,application/vnd.oma.dd+xml,text/x-vCalendar,text/x-vCard,audio/midi,audio/x-midi,audio/mid,audio/x-mid,audio/sp-midi,audio/AMR,audio/x-amr,audio/wav,audio/x-wav,application/vnd.smaf,application/x-smaf,audio/mpeg,audio/x-mpeg,audio/mp3,audio/x-mp3,audio/mpeg3,audio/x-mpeg3,audio/mpg,audio/x-mpg,audio/x-mpegaudio,video/3gpp,application/vnd.wap.xhtml+xml,text/css,text/plain;q=0.8;q=0.8\r\nAccept-Charset:utf-8\r\nEncoding-Version:1.2\r\nUser-Agent:NokiaN90-1/2.0527.2.3 Series60/2.8 Profile/MIDP-2.0 Configuration/CLDC-1.1\r\n"
#else
#define NCC_CFG_DEFAULT_WAP_HEADER "Accept:application/vnd.wap.mms-message,application/vnd.wap.wmlscriptc,application/vnd.wap.wmlc,application/vnd.wap.wbxml,text/wnd.wap.wmlscript,text/vnd.sun.j2me.app-descriptor,application/java-archive,application/octet-stream,image/vnd.wap.wbmp;level=0,image/x-bmp,image/bmp,image/jpg,image/jpeg,image/pjpeg,image/gif,image/png,application/vnd.oma.drm.message,application/vnd.wap.connectivity-wbxml,application/vnd.oma.dd+xml,text/x-vCalendar,text/x-vCard,audio/midi,audio/x-midi,audio/mid,audio/x-mid,audio/sp-midi,audio/AMR,audio/x-amr,audio/wav,audio/x-wav,application/vnd.smaf,application/x-smaf,audio/mpeg,audio/x-mpeg,audio/mp3,audio/x-mp3,audio/mpeg3,audio/x-mpeg3,audio/mpg,audio/x-mpg,audio/x-mpegaudio,video/3gpp,application/vnd.wap.xhtml+xml,text/css,text/plain;q=0.8;q=0.8\r\nAccept-Charset:utf-8\r\nEncoding-Version:1.2\r\nUser-Agent:NokiaN90-1/2.0527.2.3 Series60/2.8 Profile/MIDP-2.0 Configuration/CLDC-1.1\r\n"
#endif
//#define NCC_CFG_DEFAULT_HTTP_HEADER "Accept:*/*,text/ecmascript,application/xhtml+xml,application/vnd.wap.wbxml,text/vnd.wap.wml,text/vnd.sun.j2me.app-descriptor,application/java-archive,application/vnd.wap.mms-message,application/vnd.wap.wmlc,text/vnd.sun.j2me.app-descriptor,application/java-archive,application/vnd.oma.drm.message,application/vnd.wap.connectivity-wbxml,text/x-vCalendar,text/x-vCard,audio/midi,audio/x-midi,audio/mid,audio/x-mid,audio/sp-midi,audio/AMR,audio/x-amr,audio/wav,audio/x-wav,application/vnd.smaf,application/x-smaf,audio/mpeg,audio/x-mpeg,audio/mp3,audio/x-mp3,audio/mpeg3,audio/x-mpeg3,audio/mpg,audio/x-mpg,audio/x-mpegaudio,video/3gpp,image/vnd.wap.wbmp,image/x-bmp,image/bmp,image/jpg,image/jpeg,image/pjpeg,image/gif,image/png,text/css,text/plain\r\nAccept-Encoding:gzip,deflate\r\nUser-Agent:NokiaN90-1/2.0527.2.3 Series60/2.8 Profile/MIDP-2.0 Configuration/CLDC-1.1\r\n"

#define NCC_CFG_HTTP_DIRECT_HOMEPAGE_DEFAULT    "http://www.baidu.com"
#define NCC_CFG_HTTP_PROXY_HOMEPAGE_DEFAULT     "http://wap.monternet.com"
#define NCC_CFG_HTTP_PROXY_DEFAULT          "10.0.0.172" /**< default wap gateway */
#define NCC_CFG_HTTP_PORT_DEFAULT           80      /**< default http gateway port */

#define NCC_CFG_WAP_HOMEPAGE_DEFAULT    "http://wap.monternet.com"
#define NCC_CFG_WAP_GATEWAY_DEFAULT     "10.0.0.172" /**< default wap gateway */
#define NCC_CFG_WAP_PORT_DEFAULT        9201    /**< default wap gateway port */
#define NCC_CFG_INVALID_INDEX           -1


// --------------------------------------------------------------------//
//          The User Agent and Http Header String is moved to WAP_Config.hi               //
// --------------------------------------------------------------------//

typedef enum {
    NCC_CFG_SUPPORT_SCRIPT  = 0x00000001,   /**< support scritp */
    NCC_CFG_SUPPORT_CSS     = 0x00000002,   /**< support css */
    NCC_CFG_SUPPORT_TABLE   = 0x00000004,   /**< support table */
    NCC_CFG_SUPPORT_IMAGE   = 0x00000008,   /**< support image */
    NCC_CFG_SUPPORT_ALIGN   = 0x00000010,   /**< support align */
    NCC_CFG_SUPPORT_SMART_LAYOUT = 0x00000020,  /**< support smart layout */
    NCC_CFG_SUPPORT_COOKIE  = 0x00000040,   /**< support cookie */
    NCC_CFG_SUPPORT_CACHE   = 0x00000080,   /**< support cache */
    NCC_CFG_SUPPORT_SECURITY = 0x00000100,  /**< support security */
    NCC_CFG_SUPPORT_REALTIME_RAW_DATA_DISPLAY_AND_LOG = 0x00000200, /**< support realtime raw data display and log */
    NCC_CFG_SUPPORT_BGSOUND = 0x00000400,   /**< support background sound */
    NCC_CFG_SUPPORT_BACKGROUD = 0x00000800,  /**< support backgroud */
    NCC_CFG_SUPPORT_PUSH    = 0x00001000,     //add by bill
    NCC_CFG_PIC_SAVETO_SD    = 0x00002000,     //add by bill
    NCC_CFG_MUSIC_SAVETO_SD    = 0x00004000,     //add by bill
    NCC_CFG_VEDIO_SAVETO_SD  = 0x00008000    //add by bill
}E_ADVANCE_OPTION;

typedef enum {
    NCC_CFG_INVALID_MODE = -1,
    NCC_CFG_HTTP_DIRECT_MODE,   /**< http direction connection mode */
    NCC_CFG_HTTP_PROXY_MODE,    /**< http proxy connection mode */
    NCC_CFG_WAP_MODE            /**< wap connection mode */
}E_CONN_MODE;

/** Font mode for browser */
typedef enum {
    NCC_CFG_FONT_MODE_SMALLEST,
    NCC_CFG_FONT_MODE_SMALLER,
    NCC_CFG_FONT_MODE_MEDIUM,
    NCC_CFG_FONT_MODE_LARGEER,
    NCC_CFG_FONT_MODE_LARGEEST,
    NCC_CFG_FONT_MODE_DYNAMIC
}E_FONT_MODE;


/** LANG mode for browser */
typedef enum {
    NCC_CFG_LANG_MODE_ENU,
    NCC_CFG_LANG_MODE_CHS,
    NCC_CFG_LANG_MODE_CHT,
    NCC_CFG_LANG_MODE_OTHER
}E_LANG_MODE;

/** config functions return value */
typedef enum {
    NCC_CFG_RTN_FAILED = -1,
    NCC_CFG_RTN_SUCESSFUL = 1,
    NCC_CFG_RTN_EMPTY,
    NCC_CFG_RTN_FULL,
    NCC_CFG_RTN_SAME_NAME,
    NCC_CFG_RTN_NO_URL
}E_CFG_RTN_VALUE;


int32_t    NCCBrw_cfg_isInit(void);


/**
 * Open config file and init Browser running config.
 * \return  <ul>
 *              <li> TRUE   if sucessful.
 *              <li> FALSE  if failed.
 *          </ul>
 */
int32_t NCCBrw_cfg_initBrowserConfig(void);

/**
 * Save browser running config to config file.
 * \return  <ul>
 *              <li> TRUE   if sucessful.
 *              <li> FALSE  if failed.
 *          </ul>
 */
int32_t NCCBrw_cfg_saveBrowserConfig(void);

/**
 * Free all memory of browser running config.
 * \param   pBrowserConfig  Pointer to Browser running config structure.
 */
void NCCBrw_cfg_destroyBrowserConfig(void);

/**
 * Restore the default config.
 */
void NCCBrw_cfg_restoreDefaultCfg(void);

/**
* Get init status of configuration file.
* \return
*  <ul>
*       <li> 0   if nothing changed.
*       <li> other if file corrupted or updated according to the value you define.
*  </ul>
*/
int32_t NCCBrw_cfg_getInitStatus(void);

/**
 * Get size of browser cookie
 * \return the size of cookie in bytes.
 */
int32_t NCCBrw_cfg_getCookieSize(void);

/**
 * Set size of browser cookie
 * \param   size cookie size
 * \return  <ul>
 *              <li> TRUE   if sucessful.
 *              <li> FALSE  if failed.
 *          </ul>
 */
int32_t NCCBrw_cfg_setCookieSize(int32_t size);

/**
 * Get size of browser cache
 * \return the size of cache in bytes.
 */
int32_t NCCBrw_cfg_getCacheSize(void);

/**
 * Set size of browser cache
 * \param   size cache size
 * \return  <ul>
 *              <li> TRUE   if sucessful.
 *              <li> FALSE  if failed.
 *          </ul>
 */
int32_t NCCBrw_cfg_setCacheSize(int32_t size);

#ifdef _WIN32_WCE
/**
* Get current GUID according to current Internet mode.
*\param mode Mode of network connection.
*/
GUID* NCCBrw_cfg_getGuid(E_CONN_MODE mode);

/**
* Save current GUID according to current Internet mode.
*\param pGuid pointer to GUID which is saved.
*\param mode Mode of network connection.
* \return
*/
void NCCBrw_cfg_saveGuid(GUID *pGuid, E_CONN_MODE mode);
#endif

/**
 * Get font mode
 * \return  Font mode
 */
E_FONT_MODE NCCBrw_cfg_getFontMode(void);

/**
 * Set font mode
 * \param   fontMode        Font mode which will be set.
 * \return  <ul>
 *              <li> TRUE   if sucessful.
 *              <li> FALSE  if failed.
 *          </ul>
 */
int32_t NCCBrw_cfg_setFontMode(E_FONT_MODE fontMode);

/**
 * Get language mode
 * \return  Language mode
 */
E_LANG_MODE NCCBrw_cfg_getLanguageMode(void);

/**
 * Set language mode
 * \param   langMode        Language mode which will be set.
 * \return  <ul>
 *              <li> TRUE   if sucessful.
 *              <li> FALSE  if failed.
 *          </ul>
 */
int32_t NCCBrw_cfg_setLanguageMode(E_LANG_MODE langMode);

/**
 * Get max image in one page
 * \return  The number of max image in one page
 */
int32_t NCCBrw_cfg_getMaxImgInPage(void);

/**
 * Set max image in one page
 * \param   nMaxImgInPage   Max image in one page
 * \return  <ul>
 *              <li> TRUE   if sucessful.
 *              <li> FALSE  if failed.
 *          </ul>
 */
int32_t NCCBrw_cfg_setMaxImgInPage(int32_t nMaxImgInPage);

/**
 * Set vector font Height
 * \param   height        vector Font height which will be set.
 * \return  <ul>
 *              <li> TRUE   if sucessful.
 *              <li> FALSE  if failed.
 *          </ul>
 */
int32_t NCCBrw_cfg_setVectorFontHeight(uint32_t height);

/**
 * Get vector font Height
 * \return  <ul>
 *              <li> vector font height .
 *          </ul>
 */
uint32_t NCCBrw_cfg_getVectorFontHeight(void);

/**
 * Get max number of character encodings supported by browser.
 *
 * \return  Maximum of character encodings.
 */
int32_t NCCBrw_cfg_getEncodingTotalNum(void);

/**
 * Get handle of browser codepage setting
 *
 * \return  array of codepage string.
 */
int8_t **NCCBrw_cfg_getCodepageHandle(void);

/**
 * Get current codepage index.
 * \return  Index of current codepage string.
 */
int32_t NCCBrw_cfg_getCurCodepage(void);

/**
 * Set current codepage index.
 * \return  Index of current codepage string.
 */
int32_t NCCBrw_cfg_setCurCodepage(int32_t index);

/**
 * Get handle of screen Resolution setting.
 *
 * \return  Address of resolution array.
 *
 *\attention    one 32bit display a screen resolution
 */
int32_t *NCCBrw_cfg_getScreenResolutionList(void);

/**
 * Get current resolutin index of screen Resolution setting.
 * \return  current resolution index.
 */
int32_t NCCBrw_cfg_getCurScreenResolution(void);

/**
 * Get current resolutin index of screen Resolution setting.
 * \param   index           Index of screen resolution array.
 * \return  <ul>
 *              <li> TRUE   if sucessful.
 *              <li> FALSE  if failed.
 *          </ul>
 */
int32_t NCCBrw_cfg_setCurScreenResolution( int32_t index);

/**
 * Get certain advance option.
 * \param   advanceOpton    Advance option which you want to get.
 * \return  <ul>
 *              <li> TRUE   if the option is set.
 *              <li> FALSE  if the option is unset.
 *          </ul>
 */
int32_t NCCBrw_cfg_getAdvanceOption(E_ADVANCE_OPTION advanceOpton);

/**
 * Set certain advance option enable.
 * \param   advanceOpton    New advance options.
 */
void NCCBrw_cfg_setAdvanceOption( E_ADVANCE_OPTION advanceOpton);

/**
 * Disable certain advance option.
 */
void NCCBrw_cfg_unsetAdvanceOption(E_ADVANCE_OPTION advanceOpton);

/**
 * Revert to default advance options.
 */
void NCCBrw_cfg_resetAdvanceOption(void);

/**
 * Get total net setting items number from browser running config.
 * \return  total number of favorte items.
 */
int32_t NCCBrw_cfg_getNetSettingCount(void);

/**
 * Get index of current selected net setting.
 * \return index.
 */
int32_t NCCBrw_cfg_getCurNetSetting(void);

/**
 * Set index for current selected net setting.
 * \return index.
 */
int32_t NCCBrw_cfg_setCurNetSetting(int32_t index);

/**
 * Get current net mode
 */
E_CONN_MODE NCCBrw_cfg_getNetMode(void);

/**
 * Get current homepage.
 */
int8_t *NCCBrw_cfg_getCurHomepage(void);

int32_t NCCBrw_cfg_changeHomepage(int32_t index, int8_t *pHomepage);

/**
 * Get one net setting according to the index given from browser running config
 * \param   index           Index of net setting array
 * \param   pConnectMode    Pointer to connect mode
 * \param   ppProxyServer   Pointer to pointer to the string which describes proxy server.
 * \param   pPort           Pointer to port number.
 * \param   ppHomepage      Pointer to pointer to homepage of the net setting.
 * \return  <ul>
 *              <li> TRUE   if sucessful.
 *              <li> FALSE  if failed.
 *          </ul>
 *
 * \attention   Here ppProxyServer and ppHomepage is used to point to the address, don't give address of an array.
 */
int32_t NCCBrw_cfg_getNetSetting(
                              int32_t index,
                              int8_t **ppProfileName,
                              E_CONN_MODE *connectMode,
                              int8_t **pProxyServer,
                              int32_t *iPort,
                              int8_t **ppHomepage,
                              int8_t **ppApn,
                                int8_t **ppUserName,
                                int8_t **ppPass);
/**
 * Add one net setting into browser running config
 * \param   connectMode     connect mode
 * \param   pProxyServer    Pointer to the string which describes proxy server.
 * \param   iPort           port number.
 * \param   pHomepage       Pointer to homepage of the net setting.
 * \return  <ul>
 *              <li> TRUE   if sucessful.
 *              <li> FALSE  if failed.
 *          </ul>
 */
int32_t NCCBrw_cfg_addNetSetting(
                              int8_t *pProfileName,
                              E_CONN_MODE connectMode,
                              int8_t *pProxyServer,
                              int32_t iPort,
                              int8_t *pHomepage,
                              int8_t *pApn,
                                int8_t *pUserName,
                                int8_t *pPass);

/**
 * Add one net setting into browser running config
 * \param   index           Index of net setting array
 * \param   connectMode     connect mode
 * \param   pProxyServer    Pointer to the string which describes proxy server.
 * \param   iPort           port number.
 * \param   pHomepage       Pointer to homepage of the net setting.
 * \return  <ul>
 *              <li> TRUE   if sucessful.
 *              <li> FALSE  if failed.
 *          </ul>
 */
int32_t NCCBrw_cfg_changeNetSetting(
                             int32_t index,
                             int8_t *pProfileName,
                             E_CONN_MODE connectMode,
                             int8_t *pProxyServer,
                             int32_t iPort,
                             int8_t *pHomepage,
                             int8_t *pApn,
                               int8_t *pUserName,
                               int8_t *pPass);

/**
 * Delete one net setting into browser running config
 * \param   index           Index of net setting array
 * \return  <ul>
 *              <li> TRUE   if sucessful.
 *              <li> FALSE  if failed.
 *          </ul>
 */
int32_t NCCBrw_cfg_deleteNetSetting(int32_t index);

/**
 * Set current connect proxy and port.
 * \param   connectMode     connect mode
 * \param   pProxy        Proxy server.
 * \param   iPort         Proxy server port.
 */
int32_t NCCBrw_cfg_setNetSettingProxyPort(E_CONN_MODE connectMode, int8_t *pProxy, int32_t iPort);

/**
 * Get current connect proxy and port.
 * \param   connectMode   connect mode
 * \param   pProxy        Pointer to pointer to Proxy server.
 * \param   iPort         Pointer to proxy server port.
 */
int32_t NCCBrw_cfg_getNetSettingProxyPort(E_CONN_MODE connectMode, int8_t **ppProxy, int32_t *pPort);

/**
 * Set certain protocol name-value headers and
 * change a long sring seperate with "\r\n" into name and value string alone.
 * \param   type            Protocol type
 * \param   pHeader         Input long string of protocol headers.
 * \return  <ul>
 *              <li> TRUE   if sucessful.
 *              <li> FALSE  if failed.
 *          </ul>
 */
int32_t NCCBrw_cfg_setProtocolHeaderString(E_CONN_MODE type,
                                        int8_t *pHeader);

/**
 * Get certain protocol name-value headers and
 *
 * \return  <ul>
 *              <li> Pointer to header string  if header string exist.
 *              <li> "" if header string don't exist.
 *          </ul>
 */
int8_t *NCCBrw_cfg_getProtocolHeaderstring(void);

/**
 * Get certain protocol header name-value pairs total number
 * \param   type            Protocol type
 * \return  name-value pairs total number
 */
int32_t NCCBrw_cfg_getProtocolHeadersCount( E_CONN_MODE type);

/**
 * Get one name-value of certain protocol headers .
 *
 * \param   type            Protocol type
 * \param   index           Index of protocol header array.
 * \param   ppName          Pointer to pointer to the name of a name-value pair.
 * \param   ppValue         Pointer to pointer to the value of a name-value pair.
 * \return  <ul>
 *              <li> TRUE   if sucessful.
 *              <li> FALSE  if failed.
 *          </ul>
 * \attention   Index is for a name-value pair, not just for name or value.
 */
int32_t NCCBrw_cfg_getProtocolHeaderNameValue(E_CONN_MODE type,
                                           int32_t index,
                                           int8_t **ppName,
                                           int8_t **ppValue);
/**
 * Change one name-value of certain protocol headers.
 *
 * \param   type            Protocol type
 * \param   index           Index of protocol header array.
 * \param   pValue          Pointer to the value of a name-value pair.
 * \return  <ul>
 *              <li> TRUE   if sucessful.
 *              <li> FALSE  if failed.
 *          </ul>
 */
int32_t NCCBrw_cfg_changeProtocolHeaderNameValue(
                                              E_CONN_MODE type,
                                              int32_t index,
                                              int8_t *pValue);
/**
 * Add one name-value of certain protocol headers.
 *
 * \param   type            Protocol type
 * \param   pName           Input string as name of a name-value pair.
 * \param   pValue          Input string as value of a name-value pair.
 * \return  <ul>
 *              <li> TRUE   if sucessful.
 *              <li> FALSE  if failed.
 *          </ul>
 */
int32_t NCCBrw_cfg_addProtocolHeaderNameValue(E_CONN_MODE type,
                                           int8_t *pName,
                                           int8_t *pValue);
/**
 * Delete one name-value pair of certain protocol headers.
 *
 * \param   type            Protocol type
 * \param   index
 * \return  <ul>
 *              <li> TRUE   if sucessful.
 *              <li> FALSE  if failed.
 *          </ul>
 */
int32_t NCCBrw_cfg_deleteProtocolHeaderNameValue(E_CONN_MODE type, int32_t index);

/**
 * Get total favorte items number from browser running config.
 * \return  total number of favorte items.
 */
int32_t NCCBrw_cfg_getFavoriteCount(void);

/**
 * Get one Favorte item according to the index given from browser running config
 * \param   index           index of the favorite items array in browser running config
 * \param   ppName          Pointer to pointer to the name of a favorite item.
 * \param   ppWebsite       Pointer to pointer to the website of a favorite item.
 * \return  <ul>
 *              <li> TRUE   if sucessful.
 *              <li> FALSE  if failed.
 *          </ul>
 * \attention   Here ppName and ppWebsite is used to point to the address, don't give address of an array.
 */
int32_t NCCBrw_cfg_getFavoriteItem(
                                int32_t index,
                                int8_t **ppName,
                                int8_t **ppWebsite);
/**
 * Add one Favorte item into browser running config
 * \param   pName           Pointer to the name which will be saved.
 * \param   pWebsite        Pointer to the website which will be saved.
 * \return  <ul>
 *              <li> TRUE   if sucessful.
 *              <li> FALSE  if failed.
 *          </ul>
 */
int32_t NCCBrw_cfg_addFavoriteItem(
                                int8_t *pName,
                                int8_t *pWebsite);
/**
 * Change one Favorte item which have saved in browser running config
 * \param   index           index of the favorite items array in browser running config
 * \param   pName           Pointer to the name which will be changed.
 * \param   pWebsite        Pointer to the website which will be changed.
 * \return  <ul>
 *              <li> TRUE   if sucessful.
 *              <li> FALSE  if failed.
 *          </ul>
 */
int32_t NCCBrw_cfg_changeFavoriteItem(
                                int32_t index,
                                int8_t *pName,
                                int8_t *pWebsite);

/**
 * Delete one Favorte item which have saved in browser running config
 *
 * \param   index           index of the favorite items array in browser running config
 * \return  <ul>
 *              <li> TRUE   if sucessful.
 *              <li> FALSE  if failed.
 *          </ul>
 */
int32_t NCCBrw_cfg_delFavoriteItem(int32_t index);



/**
 * Get one total history records number and current start index from browser running config
 *
 * \param   pIndex          Pointer to start index of the history record array in browser running config
 * \return  total number of history records
 */

int32_t NCCBrw_cfg_getHistoryCount(void);

/**
 * Get one history record according to the index given from browser running config
 * \param   pIndex          Pointer to start index of the history record array in browser running config
 * \param   ppWebsite       Pointer to pointer to the website of a history item.
 * \return  <ul>
 *              <li> TRUE   if sucessful.
 *              <li> FALSE  if failed.
 *          </ul>
 *
 * \attention   Here ppWebsite is used to point to the address, don't give address of an array.
 */
int32_t NCCBrw_cfg_getHistoryItem(
                                int32_t index,
                                int8_t **ppName,
                                int8_t **ppWebsite);
/**
 * Add one history record into browser running config
 * \param   ppWebsite       Pointer to pointer to the website of a history item.
 * \return  <ul>
 *              <li> TRUE   if sucessful.
 *              <li> FALSE  if failed.
 *          </ul>
 */
int32_t NCCBrw_cfg_addHistoryItem(int8_t *pName, int8_t *pWebsite);

int32_t NCCBrw_cfg_delHistoryItem(int32_t index);

/**
 * Clear all history records in browser running config
 */
void NCCBrw_cfg_clearHistoryItems(void);

/**
 *  Get Browser version
 */
int8_t *NCCBrw_version_brwVersion(void);


#define WAP_CFG_ENABLE_CSS_BEGIN if( NCCBrw_cfg_getAdvanceOption(NCC_CFG_SUPPORT_CSS) ){
#define WAP_CFG_ENABLE_CSS_END }

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

#endif /* __NCC_CFG_H__ */
