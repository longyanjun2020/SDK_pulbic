#ifndef __VEN_WAP_H_
#define __VEN_WAP_H_
/********************************************************************************/
/*  File : ven_wap.h                                                            */
/*  Scope: The definition of the data structure or enum for wap related messages*/
/********************************************************************************/

#include "ven_sdk.h"

/*--------------------------------------------------------------------------*/
/* Type Definition                                                          */
/*--------------------------------------------------------------------------*/
#define VEN_WAP_MAX_URL_LEN 256 ///< max byte len for input url

#define VEN_WAP_MAX_USERAGENT_LEN 100 ///max length of useragent


enum
{
    VEN_WAP_RET_SUCCESS = 0,
    VEN_WAP_RET_BAD_PARAM,
    VEN_WAP_RET_OUT_OF_MEMORY,
    VEN_WAP_RET_FAILED,
    VEN_WAP_RET_NOT_SUPPORT
};
typedef u32 ven_wap_ret_t;

enum
{
    VEN_WAP_BROWSER_OPEN = 0,
    VEN_WAP_BROWSER_DOWNLOAD,
    VEN_WAP_BROWSER_USER_STORAGE,
};
typedef u32 ven_wap_browser_mode_t;

enum
{
    VEN_WAP_DL_STORAGE_CARD=0,
    VEN_WAP_DL_STORAGE_CARD2,
    VEN_WAP_DL_STORAGE_PHONE,
    VEN_WAP_DL_STORAGE_SYS_DEFAULT = 0xFF,    
};
typedef u32 ven_wap_download_storage_t;

enum
{
    VEN_WAP_RSP_RET_SUCCESS = 0,
    VEN_WAP_RSP_RET_NETWORK_ERR,
    VEN_WAP_RSP_RET_DL_FAILED,
    VEN_WAP_RSP_RET_INIT_FAILED,
    VEN_WAP_RSP_RET_UNKNOWN_ERR,
};
typedef u32 ven_wap_rsp_ret_t;

typedef struct
{
    u16 *pURL;
    u16 nURLLen;
} ven_wap_open_browser_info_t;

typedef struct
{
    u16 struct_size;        //sizeof the struct, to make backward compatibility possible
    u16 *pURL;
    u16 nURLLen;
    ven_wap_download_storage_t eStorage;
    ven_wap_browser_mode_t eMode;
    u8 SimID;         //the SIM ID used to create datalink in browser (possible values are SIM_ONE, SIM_TWO, NO_SIM_SELECT)
    VEN_CB_FUNC_PTR pfnCb;  //for calling back while calling wap dowloading or browser status
} ven_wap_open_browser_info_ex_t;

typedef struct
{
    u32  semID;
	s8 **ppOutUserAgent;
	u32 *pLen;
    ven_wap_ret_t *pRetCode;
} ven_wap_get_currentUA_info_t;

typedef struct
{
    u32     type;                           /* Event type          */
    u32     x;                              /* Event x             */
    u32     y;                              /* Event y             */
    u32     DataLen;                        /* Event Data lenght   */
    void*   pData;                          /* Event Data pointer  */
} ven_wap_get_currentUA_userdata_t;

/*--------------------------------------------------------------------------*/
/* Public Function Definition                                               */
/*--------------------------------------------------------------------------*/

/*************************************************************/
/**
 *  ven_wap_open_browser
 *
 *  @brief  To launch WAP browser
 *
 *  @param  pURL           [in]  String to be shown on title bar
 *  @param  nURLLen          [in]  Charater length of title string
 *  @param  ptVenReq          [in]  Request data structure, including callback function and SDK handle, see ven_sdk.h for more information
 *
 *  @retval TRUE   Success
 *          FALSE   Failed
 *
 *  @note Synchronous function
 */
ven_wap_ret_t ven_wap_open_browser(ven_wap_open_browser_info_t* pBrowserInfo, ven_req_data_t* ptVenReq);

/*************************************************************/
/**
 *  ven_wap_open_browser_ex
 *
 *  @brief  To launch WAP browser. This is extended version, the functionalities depend on the parameters of pBrowserInfo.
 *
 *  @param  pBrowserInfoEx    [in]  refer to the ven_wap_open_browser_info_ex_t
 *  @param  ptVenReq          [in]  Request data structure, including callback function and SDK handle, see ven_sdk.h for more information
 *
 *  @retval TRUE   Success
 *          FALSE   Failed
 *
 *  @note Synchronous function
 */
ven_wap_ret_t ven_wap_open_browser_ex(ven_wap_open_browser_info_ex_t* pBrowserInfoEx, ven_req_data_t* ptVenReq);

/*************************************************************/
/**
 *  ven_wap_download_browser
 *
 *  @brief  wap browser
 *
 *  @param  pURL              [in]  String to be shown on title bar
 *  @param  nURLLen           [in]  Charater length of title string
 *  @param  ptVenReq          [in]  Request data structure, including callback function and SDK handle, see ven_sdk.h for more information
 *
 *  @retval TRUE   Success
 *          FALSE   Failed
 *
 *  @note Synchronous function
 */
ven_wap_ret_t ven_wap_download_browser(ven_wap_open_browser_info_t* pBrowserInfo, ven_req_data_t* ptVenReq);


/*************************************************************/
/**
 *  ven_wap_getCurrentUserAgent
 *
 *  @brief get current user agent ,only support sync
 *
 *  @param  pOutUserAgent       [Out]  String to be store user agent
 *  @param  pLen                [in]  The length that user what to get
 *  @param  handle          	[in]  SDK handle
 *
 *  @retval TRUE   Success
 *          FALSE   Failed
 *
 *  @note Synchronous function
 */
ven_wap_ret_t ven_wap_getCurrentUserAgent(s8** ppOutUserAgent, u32 *pLen,u32 handle);

#endif //__VEN_WAP_H_

