
/**
 * @file
 * Internal config interfaces and structure.
 */

#ifndef __CFG_INTERNAL_H__
#define __CFG_INTERNAL_H__

#include <ncccfg.h>
#define PROTOCOL_SETTING    0x00000001  /**< prototcol setting flag in config file */
#define FAVORITE_SETTING    0x00000002  /**< favorite setting flag in config file */
#define HISTORY_SETTING     0x00000003  /**< history setting flag in config file */

#ifdef NCC_DEBUG_ON
#define CFG_TRACE WAP_OS_PRINTF
#endif

#ifdef __cplusplus
extern "C"{
#endif

/** Favorite/Bookmark Item Structure Definition of Browser Config */
typedef struct _Favorite{
    char  *pName;         /**< Bookmark name */
    char  *pWebsite;      /**<  Bookmark website */
}T_FAVORITE_ITEM;

/** Favorite/Bookmark Folder Structure Definition of Browser Config */
typedef struct _FavorInfo{
    T_FAVORITE_ITEM favoriteItem[NCC_CFG_MAX_FAVORATEITEMS];
    int32_t			iTotal;         /**< Total items */
}T_FAVORITES;

/** History Item Structure Definition of Browser Config */
typedef struct _History{
	int8_t  *pName;
    int8_t  *pWebsite;
}T_HISTORY_ITEM;

/** History Folder Structure Definition of Browser Config */
typedef struct _HistoryInfo{
    T_HISTORY_ITEM  historyItem[NCC_CFG_MAX_HISTORYITEMS];
    int32_t			iTotal; /**< Total items */
}T_HISTORIES;

/** Concret structure of protocol setting */
typedef struct _NET_Setting
{
    int8_t          *pProfileName;    /**< profile name */
    E_CONN_MODE     connectMode;    /**< Connection mode */
    int8_t          *pProxyServer;  /**< Proxy server */
    int32_t         iPort;          /**< Proxy server port */
    int8_t          *pHomepage;     /**< Homepage for this mode */
    int8_t			*pApn;			/*Access point name */
    int8_t			*pUserName;
    int8_t			*pPass;
}T_NET_SETTING;

/** Protocol setting structure for HTTP or WAP connection */
typedef struct _PROTOCOL_Setting
{
    //struct _ProtocolForRW{
    int32_t     iTotalHttpHeader;   /**< total http protocol header number */
    int32_t     iTotalWspHeader;    /**< total wsp protocol header number */
    int32_t     iCurrentNetSetting;  /**< current selected profile, Not beyond max items */
    int32_t     iTotalNetSetting;    /**< total net setting number */
    //};  // delete struct in struct

    int8_t*     pDefaultHttpHead;   /**< Default HTTP name-value string */
    int8_t*     pDefaultWspHead;    /**< Default WSP name-value string */
    int8_t*     pHttpHeaders[NCC_CFG_PROTOCOLHEADER_MAXNUM];    /**< Pointer to array of HTTP name-value string */
    int8_t*     pWspHeaders[NCC_CFG_PROTOCOLHEADER_MAXNUM];     /**< Pointer to array of WSP name-value string */

    /** user can set more than one net profile and select one */
    T_NET_SETTING   *pNetSetting[NCC_CFG_MAX_NETSETTING_NUM];
}T_PROTOCOL_SETTING;
   struct _ProtocolForRW{
    int32_t     iTotalHttpHeader;   /**< total http protocol header number */
    int32_t     iTotalWspHeader;    /**< total wsp protocol header number */
    int32_t     iCurrentNetSetting;  /**< current selected profile, Not beyond max items */
    int32_t     iTotalNetSetting;    /**< total net setting number */
   };
// add new struct
/** codepage options */
typedef struct _CODEPAGE
{
    int32_t     iCurCodePageIndex;  /**< current codepage */
    int8_t**    ppCodepage;     /**< array of codepage string */
}T_CODEPAGE;

/** screen resolution options */
typedef struct _SCREEN_RESOLUTION
{
    /** resolution options: 176*260, 208*285 ... */
    int32_t     iResolution[NCC_CFG_RESOLUTION_MAXNUM];
    int32_t     iCurResolution; /**< current screen resolutin */
}T_SCREEN_RESOLUTION;

/** codepage options */
typedef struct _ADVANCE_OPTION
{
    /** one 32-bit size can set 32 options, if possible, define more than one 32-bit */
    int32_t     iAdvanceOption;
}T_ADVANCE_OPTION;

/** Structure of Browser config */
typedef struct _BrowserConfig
{
    //struct _ConfigForRW{
    int32_t             version;        /**< current config version */
    int32_t             browserCfgLen;  /**< browser config total malloc size */
    E_FONT_MODE         iFontMode;      /**< font options */
    E_LANG_MODE         iLangMode;      /**< current language of  MMI set */
    int32_t             nMaxImgInPage;  /**< max image in one page */
    T_CODEPAGE          codepage;       /**< codepage options */
    T_SCREEN_RESOLUTION screenResolution;   /**< resolution options: 176*260, 208*285 ... */
    T_ADVANCE_OPTION    advanceOption;  /**< Advance options for browser */
    int32_t             cookieSize;         /**< size of cookie */
    int32_t             cacheSize;          /**< size of cache */
    uint32_t            vectorFontHeight;   /**< vector font height*/
    //};  // delete struct in struct

    T_PROTOCOL_SETTING  netConnectSetting;  /**< Provide three modes for connecting internet */
    T_FAVORITES         favoriteFolder; /**< favorite floder */
    T_HISTORIES         historyFolder;  /**< history floder */
    int8_t  *pHeader;   /**< buffer for getting long string header */
    int32_t iHeaderLen; /**< indicate the buffer length for long header string */
    int32_t cfgStatus;
#ifdef _WIN32_WCE
    GUID guid[2];
#endif

}T_BROWSERCONFIG;
#if 1
    struct _ConfigForRW{
    int32_t             version;        /**< current config version */
    int32_t             browserCfgLen;  /**< browser config total malloc size */
    E_FONT_MODE         iFontMode;      /**< font options */
    E_LANG_MODE         iLangMode;      /**< current language of  MMI set */
    int32_t             nMaxImgInPage;  /**< max image in one page */
    T_CODEPAGE          codepage;       /**< codepage options */
    T_SCREEN_RESOLUTION screenResolution;   /**< resolution options: 176*260, 208*285 ... */
    T_ADVANCE_OPTION    advanceOption;  /**< Advance options for browser */
    int32_t             cookieSize;         /**< size of cookie */
    int32_t             cacheSize;          /**< size of cache */
    uint32_t            vectorFontHeight;   /**< vector font height*/
    };
#endif
// add new struct _ConfigForRW   for read&write
/** File storage */
#include <cfg_storage.h>

/** protocol setting */
#include <cfg_protocolsetting.h>

/** bookmark setting */
#include <cfg_bookmark.h>

/** history setting */
#include <cfg_history.h>

/** memory setting */
#include <cfg_mmanage.h>

/** view setting */
#include <cfg_viewsetting.h>

#ifdef __cplusplus
}
#endif

#endif /* __CFG_INTERNAL_H__ */
