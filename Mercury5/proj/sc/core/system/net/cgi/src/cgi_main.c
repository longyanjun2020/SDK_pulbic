/*
*********************************************************************************************************
*                         AIT Multimedia Network -- HTTP Server
*                     (c) Copyright 2012, Alpha Imaging Technology Corp.
*               All rights reserved. Protected by international copyright laws.
*********************************************************************************************************
*
* Description:
*
*/
#include "amn_cgi.h"
#include "auto_syscfg.h"
#include "amn_module.h"
#include "netapp.h"
#include "net_utility.h"
#include "mmpf_fs_api.h"
#include "ahc_uf.h"
#include "ahc_stream.h"
#include "__md5.h"
#include "snr_cfg.h"

#define UNUSED_VALUE(x) x = x

#define CGI_GET_HANDLER_IMPL_VER    (2) //1: existing  2: new, with std functions
#define CGI_DECRYPT_TYPE_PORPERTY   (1)
#define CGI_DECRYPT_TYPE_VALUE      (2)

const char* ncgi_get_video_res(void);
const char* ncgi_get_video_clip_time(void);//possible implementation but now ncgi_get_looping_video is used.
const char* ncgi_get_image_res(void);
const char* ncgi_get_wb(void);
const char* ncgi_get_flicker_hz(void);
const char* ncgi_get_mtd_level(void);
const char* ncgi_get_ev_level(void);
const char* ncgi_get_power_off_delay(void);
const char* ncam_get_gsensor_sensitivity(void);
const char* ncgi_get_did_token(void);
const char* ncgi_get_tv_system(void);
const char* ncgi_get_tv_status(void);
const char* ncgi_get_ui_state(void);
const char* ncgi_get_lcdpower(void);
const char* ncgi_get_filenum(void);
const char* ncgi_get_normaldbsize(void);
const char* ncgi_get_status(void);
#if((defined(DCF_GROUP_FUN) && DCF_GROUP_FUN)||(defined __CONFIG_SDK_LETV_CDV01__))
const char* ncgi_get_ui_state_by_id(int uId);
#endif
const char* ncgi_get_def_ui_state(void);
const char* ncgi_get_photo_burst(void);
const char* ncgi_get_timelapse(void);
const char* ncgi_get_up_side_down(void);
const char* ncgi_get_hdr(void);
const char* ncgi_get_looping_video(void);
const char* ncgi_get_spot_meter(void);
const char* ncgi_get_q_shot(void);
const char* ncgi_get_status_lights(void);
const char* ncgi_get_sound_indicator(void);
const char* ncgi_get_power_saving(void);

const char* ncam_get_ui_sd0_status(void);
int ncam_set_ui_sd0_status(int status); //not use yet.

#define CGI_RW //Using this to hint that this function is used only by netapp.c and cgi_main.c for CGI
//CGI_WO should be only defined and used in netapp.c
#define GET_ONLY (NULL)

CGI_RW ncgi_ret Handle_UIMode(char *key, char *val, PFN_WEBWAIT pfn_w, PFN_CGI_OP_CALLBACK pfn_s);
CGI_RW ncgi_ret Handle_DefMode(char *key, char *val, PFN_WEBWAIT pfn_w, PFN_CGI_OP_CALLBACK pfn_s);
//CGI_WO ncgi_ret Handle_VideoOperation(char *key, char *val, PFN_WEBWAIT pfn_w, PFN_CGI_OP_CALLBACK pfn_s);
CGI_RW ncgi_ret Handle_VideoResolution(char *key, char *val, PFN_WEBWAIT pfn_w, PFN_CGI_OP_CALLBACK pfn_s);
CGI_RW ncgi_ret Handle_ImageResolution(char *key, char *val, PFN_WEBWAIT pfn_w, PFN_CGI_OP_CALLBACK pfn_s);
CGI_RW ncgi_ret Handle_Flicker(char *key, char *val, PFN_WEBWAIT pfn_w, PFN_CGI_OP_CALLBACK pfn_s);
CGI_RW ncgi_ret Handle_WB(char *key, char *val, PFN_WEBWAIT pfn_w, PFN_CGI_OP_CALLBACK pfn_s);
//CGI_WO ncgi_ret Handle_TimeSettings(char *key, char *val, PFN_WEBWAIT pfn_w, PFN_CGI_OP_CALLBACK pfn_s);
//CGI_WO ncgi_ret Handle_Net(char *key, char *val, PFN_WEBWAIT pfn_w, PFN_CGI_OP_CALLBACK pfn_s);
//CGI_WO ncgi_ret Handle_MJPEG(char *key, char *val, PFN_WEBWAIT pfn_w, PFN_CGI_OP_CALLBACK pfn_s);
CGI_RW ncgi_ret Handle_EV(char *key, char *val, PFN_WEBWAIT pfn_w, PFN_CGI_OP_CALLBACK pfn_s);
CGI_RW ncgi_ret Handle_MTD(char *key, char *val, PFN_WEBWAIT pfn_w, PFN_CGI_OP_CALLBACK pfn_s);
CGI_RW ncgi_ret Handle_PhotoBurst(char *key, char *val, PFN_WEBWAIT pfn_w, PFN_CGI_OP_CALLBACK pfn_s);
CGI_RW ncgi_ret Handle_Timelapse(char *key, char *val, PFN_WEBWAIT pfn_w, PFN_CGI_OP_CALLBACK pfn_s);
CGI_RW ncgi_ret Handle_UpsideDown(char *key, char *val, PFN_WEBWAIT pfn_w, PFN_CGI_OP_CALLBACK pfn_s);
CGI_RW ncgi_ret Handle_SpotMeter(char *key, char *val, PFN_WEBWAIT pfn_w, PFN_CGI_OP_CALLBACK pfn_s);
CGI_RW ncgi_ret Handle_LoopingVideo(char *key, char *val, PFN_WEBWAIT pfn_w, PFN_CGI_OP_CALLBACK pfn_s);
//This function should be CGI_RW but getter not implemented
//CGI_RW ncgi_ret Handle_VideoQuality(char *key, char *val, PFN_WEBWAIT pfn_w, PFN_CGI_OP_CALLBACK pfn_s);
CGI_RW ncgi_ret Handle_HDR(char *key, char *val, PFN_WEBWAIT pfn_w, PFN_CGI_OP_CALLBACK pfn_s);
CGI_RW ncgi_ret Handle_Q_SHOT(char *key, char *val, PFN_WEBWAIT pfn_w, PFN_CGI_OP_CALLBACK pfn_s);
CGI_RW ncgi_ret Handle_StatusLights(char *key, char *val, PFN_WEBWAIT pfn_w, PFN_CGI_OP_CALLBACK pfn_s);
CGI_RW ncgi_ret Handle_SoundIndicator(char *key, char *val, PFN_WEBWAIT pfn_w, PFN_CGI_OP_CALLBACK pfn_s);
CGI_RW ncgi_ret Handle_PowerSaving(char *key, char *val, PFN_WEBWAIT pfn_w, PFN_CGI_OP_CALLBACK pfn_s);
CGI_RW ncgi_ret Handle_TVSystem(char *key, char *val, PFN_WEBWAIT pfn_w, PFN_CGI_OP_CALLBACK pfn_s);
//This function should be CGI_RW but getter not implemented
//CGI_RW ncgi_ret Handle_TimeFormat(char *key, char *val, PFN_WEBWAIT pfn_w, PFN_CGI_OP_CALLBACK pfn_s);
//This function should be CGI_RW but getter not implemented
//CGI_RW ncgi_ret Handle_LCDPowerSave(char *key, char *val, PFN_WEBWAIT pfn_w, PFN_CGI_OP_CALLBACK pfn_s);
CGI_RW ncgi_ret Handle_GsensorSensitivity(char *key, char *val, PFN_WEBWAIT pfn_w, PFN_CGI_OP_CALLBACK pfn_s);
CGI_RW ncgi_ret Handle_PowerOffDelay(char *key, char *val, PFN_WEBWAIT pfn_w, PFN_CGI_OP_CALLBACK pfn_s);
CGI_RW ncgi_ret Handle_SD0(char *key, char *val, PFN_WEBWAIT pfn_w, PFN_CGI_OP_CALLBACK pfn_s);
CGI_RW ncgi_ret Handle_SetDidToken(char *key, char *val, PFN_WEBWAIT pfn_w, PFN_CGI_OP_CALLBACK pfn_s);
CGI_RW ncgi_ret Handle_LCDPowerSave(char *key, char *val, PFN_WEBWAIT pfn_w, PFN_CGI_OP_CALLBACK pfn_s);
//CGI_WO ncgi_ret Handle_FactoryReset(char *key, char *val, PFN_WEBWAIT pfn_w, PFN_CGI_OP_CALLBACK pfn_s);
//CGI_WO ncgi_ret Handle_Playback(char *key, char *val, PFN_WEBWAIT pfn_w, PFN_CGI_OP_CALLBACK pfn_s);

int dcim_filter_fmt(PFFINST hinst, char *inout, void *attr, FF_ARG *arg);
ncgi_ret cgi_handle_getter_act(char *key, char *val, PFN_WEBWAIT pfn_w, PFN_CGI_OP_CALLBACK pfn_s);

//typedef struct _CGIGET_HANDLER CGIGET_HANDLER;
typedef int (*PFN_GET_HANDLER)(char *arg, struct amn_cfgspace_value_t **val, struct NS_ON_CGI_BUF_PARAM *cgi_param);
typedef int (*int_func)(void);
typedef const char* (*str_func)(void);

typedef struct _CGIGET_HANDLER{
    const char*         getArg;
    const int           getArgLen;
    PFN_GET_HANDLER     getHandler;
    //These 2 functions are used as standard value getting.
    //It's hard to use union initializer as 2nd member in C89.
    //It loses type-safety if using c type-casting.
    //So using extra empty functions here is considerably a good trade-off.
    int_func getIntFunc;
    str_func getStrFunc;
    PFN_CGI_HANDLER actFunc;
} CGIGET_HANDLER;

int web_config_handle(CGIGET_HANDLER *handers, char *key, struct amn_cfgspace_value_t **val, char **name,
        struct NS_ON_CGI_BUF_PARAM *cgi_param);
extern CGIGET_HANDLER get_Handler[];
//int get_Handler[];
//CGIGET_HANDLER get_Handler[];

typedef struct {
    FS_DIR      *pdir;
    FS_DIRENT   *pent;
    int         pos;
} DIRPAIR;
//
//
#define RET_WGET (1) //set 1 to change a version which the caller could get return value
#define NCGI_PROCESSED (-1)
#if RET_WGET
#if 0
int _amn_webConfig_wget(char *key, struct amn_cfgspace_value_t **cfg_val, char **cfg_name,
        struct NS_ON_CGI_BUF_PARAM *cgi_param) {
    int i;
    i = web_config_wget(key, cfg_val, cfg_name, cgi_param);
    /*
    if (i >= 0) {
        *cfg_name = amn_ConfigSpaceDict[i];
        *cfg_val  = amn_config_get( CONFIG_SPACE_TYPE_CURRENT, *cfg_name );
    }*/
    return i;
}
#define amn_webConfig_wget(key,cfg_val, cfg_name, cgi_param) _amn_webConfig_wget(key, &cfg_val, &cfg_name, &cgi_param)
#else
#define amn_webConfig_wget(key,cfg_val, cfg_name, cgi_param) web_config_wget(key, &cfg_val, &cfg_name, cgi_param)
#endif
#else
#define amn_webConfig_wget(key,cfg_val, cfg_name)   0;\
        do { \
            int i = web_config_wget(key, &cfg_val, &cfg_name); \
            if (i >= 0) { \
                cfg_name = amn_ConfigSpaceDict[i]; \
                cfg_val  = amn_config_get( CONFIG_SPACE_TYPE_CURRENT, cfg_name ); \
            } \
} while (0)
#endif

int cgi_dir(IN struct cgi_virt_file_t *f, OUT char *buf, OUT char **endp, IN int maxlen);
int cgi_property(IN struct cgi_virt_file_t *f, OUT char *buf, OUT char **endp, IN int maxlen);
int cgi_delete_file(IN struct cgi_virt_file_t *f, OUT char *buf, OUT char **endp, IN int maxlen);
int cgi_play_file(IN struct cgi_virt_file_t *f, OUT char *buf, OUT char **endp, IN int maxlen);
int cgi_switch_camera(IN struct cgi_virt_file_t *f, OUT char *buf, OUT char **endp, IN int maxlen);

char galastdidtoken[128] = {0};

static int CGI_checkmd5(struct cgi_virt_file_t *f)
{
    struct __MD5_Context    c;
    int                     i,len;
    char                    *pBodyhead , *pBodytail, *pstrSignkey;
    unsigned char           digest[16];
    char                    digeststr[33];

    if(galastdidtoken[0] == 0) {
        NET_DID_ACCESS_CB pdid_token_cb = ncfg_get_didtoken_accessed_cb();

        //read from SIF
        if(pdid_token_cb){
            if(-1 == pdid_token_cb(0,galastdidtoken,sizeof(galastdidtoken))){
                return -1;
            }
            else{

                char *p;

                p = strchr(galastdidtoken,'+');
                if(p)
                    *p = 0;
                printc("galastdidtoken=%s\n",galastdidtoken);
            }
        }
        else
            return -1;
    }

    pBodyhead = strstr(f->req_url, "action");
    if(!pBodyhead){
        printc("Cannot find [action] in CGI\n");
        return -1;
    }

    pBodytail = strstr(f->req_url, "&signkey");
    if(!pBodytail){
        printc("Cannot find [signkey] in CGI\n");
        return -1;
    }

    len = pBodytail - pBodyhead;

    __MD5_Init(&c);
    __MD5_Update(&c, (unsigned char *)pBodyhead, len);
    __MD5_Update(&c, (unsigned char *)galastdidtoken, strlen(galastdidtoken));
    __MD5_Final(digest,&c);

    pstrSignkey = pBodytail + strlen("&signkey=");

    /*4-bit hex to string*/
    for(i = 0 ; i < 32 ; i++){
        unsigned char byte;

        if(i & 1)
            byte = digest[i>>1] & 0x0f;
        else
            byte = digest[i>>1] >> 4;

        if(byte <= 9)
            digeststr[i] = byte + 0x30;
        else
            digeststr[i] = byte - 10 + 0x41;
    }

    digeststr[32] = 0;

    if(strcmpi(digeststr,pstrSignkey) == 0){
        printc("EN OK\n");
        return 0;
    }
    else{
        printc("digeststr=%s\n",digeststr);
    }

    return -1;

}
//*******************************************************************************************************
// when readbuf is NULL, this routine will work in dry-run: facilitate the CONTENT-LENGTH calculation
int cgi_snprintf(OUT char *readbuf, IN int size, char *fmt, ...)
{
    int n;
    char *strbuf;
    va_list args;

    va_start(args, fmt);
    if (readbuf) {
        n = vsnprintf(readbuf, size + 1, fmt, args);
    }
    else {
        strbuf = osal_malloc(size);
        n = vsnprintf(strbuf, size + 1, fmt, args);
        osal_free(strbuf);
    }
    va_end(args);

    return n;
}

//return the code returned as cgi HTTP response from internal used enum cgi_err_t
int cgi_err_resp_code(enum cgi_err_t err_code)
{
    static const struct {
        enum cgi_err_t cgi;
        int http;
    } MAP[] = {
        {CGI_ERR_NONE,CGI_ERR__OK},
        {CGI_ERR_NO_CARD,CGI_ERR__NO_CARD},
        {CGI_ERR_CARD_LOCK,CGI_ERR__CARD_LOCK},
        {CGI_ERR_CARD_ERROR,CGI_ERR__CARD_ERR},
        {CGI_ERR_CARD_FULL,CGI_ERR__CARD_FULL},
        {CGI_ERR_SEAMLESS,CGI_ERR__SEAMLESS},
        {CGI_ERR_PERIPHERAL,CGI_ERR__PERIPHERAL},
        {CGI_ERR_INVALID_STATE,CGI_ERR__INVALID_STATE},
        {CGI_ERR_TIMEOUT,CGI_ERR__SYS_BUSY},
        {CGI_ERR_INVALID_PARAM, CGI_ERR__ILL_PARAM},
        {CGI_ERR_GENERAL,CGI_ERR__},
        {CGI_ERR_NOT_IMPLEMENTED,CGI_ERR__NOT_IMPLEMENTED},
    };
    int i;
    for (i = 0; i <  (sizeof(MAP)/sizeof((MAP)[0])); ++i) {
        if (err_code == MAP[i].cgi) {
            return MAP[i].http;
        }
    }
    if (CGI_ERR_NONE < err_code) {
        return CGI_ERR__OK;
    }

    return CGI_ERR__;
}

char *cgi_err_text(int err_code)
{
    switch(err_code) {
    case CGI_ERR__OK:
        return "OK";
    case CGI_ERR__SYS_BUSY:
        return "System Busy";
    case CGI_ERR__ILL_PARAM:
        return "Illegal Parameter";
    case CGI_ERR__UNKNOWN_ACTION:
        return "Unknown CGI-PARAM: Action";
    case CGI_ERR__UNKNOWN_PROPERTY:
        return "Unknown CGI-PARAM: Property";
    case CGI_ERR__UNKNOWN_PARAM:
        return "Unknown CGI-PARAM: extra parameter";
    case CGI_ERR__MISS_PARAM:
        return "Missing CGI-PARAM";
    case CGI_ERR__INTERNAL_ERROR:
        return "Internal Error";
    case CGI_ERR__NOT_IMPLEMENTED:
        return "Not implemented or CGI status not assigned.";
    case CGI_ERR__ILL_USER:
        return "Illegal User";
    case CGI_ERR__ERR_PASS:
        return "Error Password";
    case CGI_ERR__AUTHEN_FAIL:
        return "Authentication Failed";
    case CGI_ERR__NO_AUTHOR:
        return "User no authority for the requested operation";
    case CGI_ERR__REQUIRE_AUTHEN:
        return "Require authentication for the requested operation";
    case CGI_ERR__NO_CARD:
        return "No SD card";
    case CGI_ERR__CARD_LOCK:
        return "SD card is locked or busy";
    case CGI_ERR__CARD_ERR:
        return "SD card error";
    case CGI_ERR__CARD_FULL:
        return "SD card is full";
    case CGI_ERR__SEAMLESS:
        return "Seamless error";
    case CGI_ERR__PERIPHERAL:
        return "Device hardware error";
    case CGI_ERR__INVALID_STATE:
        return "Invalid state";
    }
    return "???";
}

void cgi_action_prepare( struct cgi_virt_file_t *f )
{
    struct cgi_param_t *prmAction;

    if (!f->param_buf) {
        cgi_set_state( f, CGI_ACTSTATE__NOT_READY );
        return;
    }
    else
        cgi_set_state( f, CGI_ACTSTATE__START );    // can proceed and will track the reading of N'th Config Name

    prmAction = cgi_param_nget( f, "action" );
    if (!prmAction) {
        cgi_set_error( f, CGI_ERR__ILL_PARAM );
        return;
    }

    if      ( !strcasecmp( prmAction->value, "get" ) )        cgi_set_action( f, CGI_ACTION_GET      );
    else if ( !strcasecmp( prmAction->value, "set" ) )        cgi_set_action( f, CGI_ACTION_SET      );
    else if ( !strcasecmp( prmAction->value, "EN1" ) )        cgi_set_action( f, CGI_ACTION_EN_GET   );
    else if ( !strcasecmp( prmAction->value, "EN2" ) )        cgi_set_action( f, CGI_ACTION_EN_SET   );
    else if ( !strcasecmp( prmAction->value, "add" ) )        cgi_set_action( f, CGI_ACTION_ADD      );
    else if ( !strcasecmp( prmAction->value, "del" ) )        cgi_set_action( f, CGI_ACTION_DEL      );
    else if ( !strcasecmp( prmAction->value, "play") )        cgi_set_action( f, CGI_ACTION_PLAY     );
    else if ( !strcasecmp( prmAction->value, "mod" ) )        cgi_set_action( f, CGI_ACTION_MOD      );
    else if ( !strcasecmp( prmAction->value, "dir" ) )        cgi_set_action( f, CGI_ACTION_DIR      );
    else if ( !strcasecmp( prmAction->value, "reardir" ) )    cgi_set_action( f, CGI_ACTION_REARDIR  );
    else if ( !strcasecmp( prmAction->value, "login" ) )      cgi_set_action( f, CGI_ACTION_LOGIN    );
    else if ( !strcasecmp( prmAction->value, "logout" ) )     cgi_set_action( f, CGI_ACTION_LOGOUT   );
    else if ( !strcasecmp( prmAction->value, "switch" ) )     cgi_set_action( f, CGI_ACTION_SWITCH   );
    else if ( !strcasecmp( prmAction->value, "sense" ) )      cgi_set_action( f, CGI_ACTION_SENSE    );
    else if ( !strcasecmp( prmAction->value, "flash" ) )      cgi_set_action( f, CGI_ACTION_FWUPDATE );
    else if ( !strcasecmp( prmAction->value, "log" ) )        cgi_set_action( f, CGI_ACTION_LOG      );
    else if ( !strcasecmp( prmAction->value, "setcamid" ) )   cgi_set_action( f, CGI_ACTION_CAMSWITCH);
    else                                                      cgi_set_error(  f, CGI_ERR__UNKNOWN_ACTION );
}

void cgi_config_prepare( struct cgi_virt_file_t *f )
{
    struct cgi_param_t *prmProperty;

    cgi_action_prepare(f);
    if (!f->param_buf) return;

    prmProperty = cgi_param_nget( f, "property" );
    if (!prmProperty) {
        cgi_set_error( f, CGI_ERR__ILL_PARAM );
        return;
    }
    strncpy( cgi_get_property(f), prmProperty->value, max( MAX_VIRT_FILE_PRIVATE_BUFSZ, strlen(prmProperty->value) ) );
}

// when buf is NULL, this routine will work in dry-run mode
int cgi_processs_configs(IN struct cgi_virt_file_t *f, OUT char *buf, IN int maxlen)
{
    struct cgi_param_t *prmProperty;
    struct cgi_param_t *prmValue, *prmAttrs;
    struct amn_cfgspace_value_t *cfg_val = 0;
    #define CFG_READY_FOR_ACTION ((struct amn_cfgspace_value_t *)1) // give a dummy value to skip checking at below!!
    char *cfg_name;
    char *ptr = buf;
    int  resp_code = CGI_ERR__OK;
    ncgi_ret ret;
    struct NS_ON_CGI_BUF_PARAM cgi_param;
    int cgi_buf_len;

    ret.cgi = CGI_RET_UNASSIGNED;
    ret.netapp = NETAPP_DONE;

    #define exit_with_response(_res)  do { \
        resp_code = _res; \
        goto L_exit_simple_response; \
    } while (0)

    #define exit_more_config(_res)  do {    \
        resp_code = _res;   \
        goto L_exit_more_response;  \
    } while (0)

    #define exit_http_response(_res) do {   \
        resp_code = _res;   \
        goto L_exit_http_response;  \
    } while (0)

    #define exit_xml_response(_res) do {    \
        resp_code = _res;   \
        goto L_exit_xml_response;   \
    } while (0)

    //osal_dprint(VERBOSE, "CGI STATE %d %p", cgi_get_state(f), buf);
    switch(cgi_get_state(f)) {
    case CGI_ACTSTATE__EOF:
        if (!buf)  cgi_set_state( f, CGI_ACTSTATE__START );      // after DRY-RUN, we are ready for REAL-RUN
        return 0;  // EOF

    case CGI_ACTSTATE__NOT_READY:
        return 0;  // no URL's param in the HTTP-GET/POST request

    case CGI_ACTSTATE__START:
        // get the Config Name: the URL-Parameter 'Property'
        prmProperty = cgi_param_nget2( f, "property", cgi_get_param(f) );

        if (!prmProperty)
            exit_with_response( CGI_ERR__ILL_PARAM );

        if( cgi_get_action(f) == CGI_ACTION_EN_GET ||
            cgi_get_action(f) == CGI_ACTION_EN_SET){

            if(CGI_checkmd5(f)){
                exit_with_response( CGI_ERR__ILL_PARAM );
            }
        }

        osal_dprint(DEBUG, "ACTION %d %s", cgi_get_action(f), (prmProperty)? prmProperty->value : "(NULL)");


        strncpy( cgi_get_property(f), prmProperty->value, max( MAX_VIRT_FILE_PRIVATE_BUFSZ, strlen(prmProperty->value) ) );
        // If Camera is in HDMI not allow CGI command except action is get
        if (cgi_get_action(f) != CGI_ACTION_GET && IS_CAMERA_IN_HDMI()) {
            exit_with_response( CGI_ERR__ );
        }
        switch(cgi_get_action(f)) {
        case CGI_ACTION_EN_SET:
        case CGI_ACTION_SET:
        case CGI_ACTION_ADD:
            cfg_val = amn_webConfig_get( cgi_get_property(f) );
            break;
        case CGI_ACTION_DEL:
            cfg_val = amn_webConfig_get( cgi_get_property(f) );
            if (!cfg_val) {
                // an example of cgi to delete file.
                // cgi-bin/Config.cgi?action=del&property=DCIM$100__DSC$MOV_1163.AVI
                // the value of property not in config file, do deleting file!!
                cfg_val = CFG_READY_FOR_ACTION;
            }
            break;
        case CGI_ACTION_DIR:
        case CGI_ACTION_REARDIR:
            cfg_val = CFG_READY_FOR_ACTION;
            break;
        case CGI_ACTION_EN_GET:
        case CGI_ACTION_GET:
            if (!strcmp(cgi_get_property(f), NCFG_MENU_PROPERTY)) {
                cfg_val = CFG_READY_FOR_ACTION;
                //overwrite action with CGI_ACTION_GET_XML so that the string does not need to be compared multiple times.
                cgi_set_action(f, CGI_ACTION_GET_XML);
            }
            else {
                int  iRet;
                iRet = amn_webConfig_wget( cgi_get_property(f), cfg_val, cfg_name, NULL);
                if (iRet != NCGI_PROCESSED) {
                    resp_code = CGI_ACTION_GET_ERROR(iRet);
                    if (resp_code != 0) {
                        //reset internal state machine so that it could work if next command is identical.
                        amn_config_reset_wlocate();
                        goto L_exit_simple_response;
                    }
                }
            }
            break;

        case CGI_ACTION_PLAY:
            // an example of cgi to delete file.
            // cgi-bin/Config.cgi?action=play&property=DCIM$100__DSC$MOV_1163.MOV
            // the value of property not in config file, do deleting file!!
            cfg_val = CFG_READY_FOR_ACTION;
            break;
        case CGI_ACTION_CAMSWITCH:
            cfg_val = CFG_READY_FOR_ACTION;
            break;

        default:
            resp_code = cgi_get_error(f);
            if (resp_code != 0)
                goto L_exit_simple_response;
            exit_with_response( CGI_ERR__INTERNAL_ERROR );
            break;
        }

        // check if the Property exist or not !!
        if (!cfg_val)
            exit_with_response( CGI_ERR__UNKNOWN_PROPERTY );

        // now actual process the CGI action
        switch(cgi_get_action(f)) {
        case CGI_ACTION_EN_SET:
        case CGI_ACTION_SET:
            prmValue = cgi_param_nget2( f, "value", cgi_get_param(f) );
            if (!prmValue)
                exit_with_response( CGI_ERR__UNKNOWN_PARAM );

            osal_dprint(DEBUG, "CONFIG.CGI: State %d", cgi_get_state( f ));

            // Check and Do camera CGI first, if return 0, do AMN config set
            // Normally, return is -1 when the CGI is for camera and processed,
            // if it is -2 means the CGI processed but failed!
            // And WEB should return CGI_ERR__
            ret = web_config_act(cgi_get_property(f), prmValue->value, buf);
            if (ret.netapp == NETAPP_DONE || ret.netapp == NETAPP_CONT) {
                amn_config_set( CONFIG_SPACE_TYPE_CURRENT, cgi_get_property(f), prmValue->value);
            } else if (ret.netapp == NETAPP_FAIL) {
                exit_with_response( CGI_ERR__ );
            } else if (ret.netapp >= CGI_ERR__ILL_PARAM) {//FIXME
                exit_with_response(ret.netapp);
            }
            if (buf) osal_dprint(DEBUG, "CONFIG.CGI: Set %s = %s", cgi_get_property(f), prmValue->value);
            //osal_dprint(VERBOSE, "CONFIG.CGI: Set %s = %s", cgi_get_property(f), prmValue->value);
            cgi_inc_param(f);
            prmProperty = cgi_param_nget2( f, "property", cgi_get_param(f) );
            if (prmProperty) {
                exit_more_config( CGI_ERR__OK );
            } else {
                exit_with_response( CGI_ERR__OK );
            }
            break;

        case CGI_ACTION_ADD:
            prmAttrs = cgi_param_nget2( f, "attrs", cgi_get_param(f) );
            if (!prmAttrs)
                exit_with_response( CGI_ERR__UNKNOWN_PARAM );

            if (buf) osal_dprint(DEBUG, "CONFIG.CGI: Add %s = %s", cgi_get_property(f), prmAttrs->value);
            exit_with_response( CGI_ERR__OK );
            break;

        case CGI_ACTION_DEL:
            if (buf) osal_dprint(DEBUG, "CONFIG.CGI: Del %s", cgi_get_property(f));

            resp_code = cgi_delete_file(f, buf, &ptr, maxlen);

            if(buf == 0){
                /*
                *Titan :
                *I have encountered that stack will be modified here,and cuase removing file failed
                *so I tried using global array to keep the file path in function "cgi_delete_file"
                *This remains to be seen!
                */
                printc(FG_RED("buf has been modified!!\n"));
            }

            exit_with_response(resp_code);
            break;

        case CGI_ACTION_PLAY:
            if (buf) osal_dprint(DEBUG, "CONFIG.CGI: Play %s", cgi_get_property(f));
            exit_http_response(cgi_play_file(f, buf, &ptr, maxlen));
            break;

        case CGI_ACTION_CAMSWITCH:
            cfg_val = amn_webConfig_get( cgi_get_property(f) );
            if (!cfg_val)
                exit_with_response( CGI_ERR__UNKNOWN_PROPERTY );
            prmValue = cgi_param_nget2( f, "value", cgi_get_param(f) );
            if ((!prmValue)||(strcmp(prmValue->value,"front")&&strcmp(prmValue->value,"rear")))
                exit_with_response( CGI_ERR__UNKNOWN_PARAM );

            if ((!ncam_is_rear_cam_ready())&&(!strcmp(prmValue->value,"rear")))
                exit_with_response( CGI_ERR__ );
            if (buf) osal_dprint(DEBUG, "CONFIG.CGI: Play %s", cgi_get_property(f));{
                if (!strcmp(cfg_val->v.strVal,prmValue->value)) {
                    printc("same camera source\n");
                    exit_with_response( CGI_ERR__OK );
                }
                else
                    exit_http_response(cgi_switch_camera(f, buf, &ptr, maxlen));
            }
            break;

        case CGI_ACTION_GET_XML:
            exit_xml_response(cgi_property(f, buf, &ptr, maxlen));
            break;
        case CGI_ACTION_EN_GET:
        case CGI_ACTION_GET:
            //if (!strcmp(cgi_get_property(f),NCFG_MENU_PROPERTY))
            //  exit_xml_response(cgi_property(f, buf, &ptr, maxlen));
            //else
            {
                int iRet;
                CGI_PRINTF( buf, ptr, maxlen, "0\nOK\n" );
                if (cfg_val->attr & CFGSPACE_PLAIN) {
                    cgi_buf_len = ptr - buf;
                    cgi_param.curLen = &cgi_buf_len;
                    cgi_param.listBuf = buf;
                    cgi_param.maxlen = maxlen;
                    iRet = web_config_handle(get_Handler, cgi_get_property(f), &cfg_val, &cfg_name, &cgi_param);
                    UNUSED_VALUE(iRet);
                    ptr = buf + cgi_buf_len;
                    amn_config_wlocate(cgi_get_property(f));//reset the internal wild-card flow
                    exit_xml_response(CGI_ERR__OK);
                }
                goto L_process_getcfg;
            }
            break;
        case CGI_ACTION_DIR:
            if (1/*!NetApp_GetRecordStatus()*/)
                exit_xml_response(cgi_dir(f, buf, &ptr, maxlen));
            else
                exit_with_response( CGI_ERR__SYS_BUSY );
            break;
        case CGI_ACTION_REARDIR:
                if ((!CAM_CHECK_SCD(SCD_CAM_NONE) || !CAM_CHECK_USB(USB_CAM_NONE)))
                    exit_xml_response(cgi_dir(f, buf, &ptr, maxlen));
                else
                    exit_with_response( CGI_ERR__PERIPHERAL );
            break;
        }
        break;//break case CGI_ACTSTATE__START

    default:
        amn_webConfig_wget( cgi_get_property(f), cfg_val, cfg_name, &cgi_param);
L_process_getcfg:
        cgi_inc_state(f);
        switch(cgi_get_action(f)) {
        case CGI_ACTION_EN_GET:
        case CGI_ACTION_GET:
            if (cfg_val) {
                switch(cfg_val->type) {
                case CFGSPACE_VALTYP__INT:
                    CGI_PRINTF( buf, ptr, maxlen, "%s=%d\n", cfg_name, cfg_val->v.intVal );
                    if (buf) osal_dprint(DEBUG, "CONFIG.CGI: %s = %d, len=%d", cfg_name, cfg_val->v.intVal, (int)(ptr - buf));
                    break;
                case CFGSPACE_VALTYP__STR:
                    CGI_PRINTF( buf, ptr, maxlen, "%s=%s\n", cfg_name, cfg_val->v.strVal );
                    if (buf) osal_dprint(DEBUG, "CONFIG.CGI: %s = %s, len=%d", cfg_name, cfg_val->v.strVal, (int)(ptr - buf));
                    break;
                }
            }
            else {
                cgi_inc_param(f);
                prmProperty = cgi_param_nget2( f, "property", cgi_get_param(f) );
                if (prmProperty) {
                    strncpy( cgi_get_property(f), prmProperty->value, max( MAX_VIRT_FILE_PRIVATE_BUFSZ, strlen(prmProperty->value) ) );
                    exit_more_config( CGI_ERR__OK );
                } else {
                    if (!buf)  cgi_set_state( f, CGI_ACTSTATE__START );      // after DRY-RUN, we are ready for REAL-RUN
                    else       cgi_set_state( f, CGI_ACTSTATE__EOF );        // after REAL-RUN, simply disable it
                }
            }
            break;
        default:
            exit_with_response( CGI_ERR__INTERNAL_ERROR );
            break;
        }
        break;
    }

    return ptr - buf;

L_exit_simple_response:
    if (ret.cgi != CGI_RET_UNASSIGNED) {
        resp_code = cgi_err_resp_code(ret.cgi);//override 709
    }
    CGI_PRINTF( buf, ptr, maxlen, "%d\n%s\n", resp_code, cgi_err_text(resp_code) );
    cgi_set_state( f, CGI_ACTSTATE__EOF );
    return ptr - buf;

L_exit_more_response:
    if (ret.cgi != CGI_RET_UNASSIGNED) {
        resp_code = cgi_err_resp_code(ret.cgi);//override 709
    }
    CGI_PRINTF( buf, ptr, maxlen, "%d\n%s\n", resp_code, cgi_err_text(resp_code) );
    return ptr - buf;

L_exit_http_response:
    if (ret.cgi != CGI_RET_UNASSIGNED) {
        resp_code = cgi_err_resp_code(ret.cgi);//override 709
    }
    if (resp_code != CGI_ERR__OK)
        CGI_PRINTF( buf, ptr, maxlen, "%d\n%s\n", resp_code, cgi_err_text(resp_code) );
    cgi_set_state( f, CGI_ACTSTATE__EOF );
    return ptr - buf;

L_exit_xml_response:
    cgi_set_state( f, CGI_ACTSTATE__EOF );
    return ptr - buf;
}

/*
 * do some action instead of value set
 * for example property=Net&value=reset
 * return == -1: this function take care the setting
 *        ==  0: this function ignore the setting, caller have to do
 */
#ifdef __AMN_OS_LINUX__
#define pseudo_cmd(c)
#else
//void pseudo_cmd(char* pcmd);
#endif

void acquire_streaming_and_cgi_op(void);
void release_streaming_and_cgi_op(void);
//A CGI with "action=set" and do the real command
ncgi_ret web_config_act(char *key, char *val, char *buf)
{
    ncgi_ret ret;

    ret.cgi = CGI_RET_UNASSIGNED;
    ret.netapp = NETAPP_DONE;

    if (buf==NULL) {
        ret.netapp = NETAPP_FAIL;
        return ret;
        //it was return -1; but it should be fail
    }

    acquire_streaming_and_cgi_op();

    ret = ncgi_send_ui_event(key, val, webwait_uiproc, webwait_uisignal);

    if (ret.netapp == NETAPP_CONT) {
        ret = cgi_handle_getter_act(key, val, webwait_uiproc, webwait_uisignal);
    }

    release_streaming_and_cgi_op();

    if (ret.netapp == NETAPP_CONT && ret.cgi == CGI_RET_UNASSIGNED) {
        printc("No action\r\n");
        return ret;
    }

    if (ret.cgi != CGI_ERR_NONE) {
        int err = cgi_err_resp_code(ret.cgi);
        ait_printf("web_config_act" "@%d, cgi:%d->%d %s\r\n", __LINE__, ret.cgi, err, cgi_err_text(err));
    }
    return ret; // tell caller to do something
}

// CGI GET property=Camera.Preview.MJPEG.status.record
static int cameraVideoStatus(char *arg, struct amn_cfgspace_value_t **val, struct NS_ON_CGI_BUF_PARAM *cgi_param)
{
    if(ncam_is_recording()) {
        strcpy((*val)->v.strVal,  "Recording");
    } else {
        strcpy((*val)->v.strVal,  "Standby");
    }
    return NCGI_PROCESSED;
}

// CGI GET property=Camera.Preview.MJPEG.TimeStamp.[year|month|day|hour|minute|second]
static int cameraTime(char *arg, struct amn_cfgspace_value_t **val, struct NS_ON_CGI_BUF_PARAM *cgi_param)
{
    char    *p;
    int     data;

    p = strrchr(arg, '.');
    if (p == NULL) return 0; // should not return 0;
    p++;
    if (strcmp(p, "year") == 0) {
        data = ncam_get_rtc_year();
    } else if (strcmp(p, "month") == 0) {
        data = ncam_get_rtc_month();
    } else if (strcmp(p, "day") == 0) {
        data = ncam_get_rtc_day();
    } else if (strcmp(p, "hour") == 0) {
        data = ncam_get_rtc_hour();
    } else if (strcmp(p, "minute") == 0) {
        data = ncam_get_rtc_minute();
    } else if (strcmp(p, "second") == 0) {
        data = ncam_get_rtc_second();
    } else {
        return 0;
    }
    (*val)->v.intVal = data;
    return NCGI_PROCESSED;
}

// CGI GET property=Camera.Menu.IsStreaming
static int cameraIsStreaming(char *arg, struct amn_cfgspace_value_t **val, struct NS_ON_CGI_BUF_PARAM *cgi_param)
{
    snprintf((*val)->v.strVal, (*val)->max_strlen-1, "%s",
                (ncam_get_streaming_mode())? "YES" : "NO");
    return NCGI_PROCESSED;
}
// CGI GET property=Camera.File.Total
static int cameraFileTotal(char *arg, struct amn_cfgspace_value_t **val, struct NS_ON_CGI_BUF_PARAM *cgi_param)
{
    (*val)->v.intVal = 0;
    AHC_UF_GetTotalFileCount((unsigned int*)&(*val)->v.intVal);
    return NCGI_PROCESSED;
}

// CGI GET property=Camera.Preview.MJPEG.WarningMSG
static int cameraWarning(char *arg, struct amn_cfgspace_value_t **val, struct NS_ON_CGI_BUF_PARAM *cgi_param)
{
    if (ncgi_has_warning_msg())
        if (ncgi_get_warning_msg())
            strcpy((*val)->v.strVal,  "NO CARD!\n");
    return NCGI_PROCESSED;
}

// CGI GET property=Camera.Record.*
// How does APP calculate the current video recording time?
// In APP, video_recording_time = Current MediaTimeStamp - Camera.Record.Start
static int cameraRecord(char *arg, struct amn_cfgspace_value_t **val, struct NS_ON_CGI_BUF_PARAM *cgi_param)
{
    char *p;
    int     data;

    p = strrchr(arg, '.');
    if (p == NULL) return 0; // should not return 0;
    p++;
    if (strcmp(p, "Avaliable") == 0) { //does not match .conf file
        data = ncam_get_rec_time_available();
    } else if (strcmp(p, "Remaining") == 0) {
        data = ncam_get_rec_time_remaining();
    } else if (strcmp(p, "Total") == 0) {
        data = ncam_get_rec_time_total();
    } else if (strcmp(p, "Start") == 0) {
        data = ncam_get_rec_time_start();
    } else {
        return NCGI_PROCESSED;
    }
    (*val)->v.intVal = data;
    return NCGI_PROCESSED;
}

// CGI GET property=status
static int cameraStatus(char *arg, struct amn_cfgspace_value_t **val, struct NS_ON_CGI_BUF_PARAM *cgi_param)
{
    int ret;
    char* string = NULL;

    //The pattern for long plain text response. It requires 2 passes here. 1st with cgi_param == NULL.
    if (cgi_param == NULL) {
        return NCGI_PROCESSED;
    }

    ret = ns_handle_event(NS_EVENT_GET_STATUS, (void*)cgi_param);
    if (ret == NSE_CB_NOT_FOUND) {
        (*val)->v.strVal = "798\n""Not implemented or CGI status not assigned.";
        return CGI_ACTION__ERROR(CGI_ERR__NOT_IMPLEMENTED);
    }
    if (ret == NSE_ERR) {
        return CGI_ACTION__ERROR(CGI_ERR__INTERNAL_ERROR);
    }
    (*val)->v.strVal = string;
    return NCGI_PROCESSED;
}

// CGI GET property=broadcast
static int cameraBroadcast(char *arg, struct amn_cfgspace_value_t **val, struct NS_ON_CGI_BUF_PARAM *cgi_param)
{
    int ret;
    static char str[] = "broadcasting";

    ret = ns_handle_event(NS_EVENT_BROADCAST, (void*)cgi_param);
    if (ret == NSE_CB_NOT_FOUND) {
        (*val)->v.strVal = "798\n""Not implemented or CGI status not assigned.";
        return CGI_ACTION__ERROR(CGI_ERR__NOT_IMPLEMENTED);
    }
    if (ret == NSE_ERR) {
        return CGI_ACTION__ERROR(CGI_ERR__INTERNAL_ERROR);
    }
    (*val)->v.strVal = str;//It's a run-time string and might not have enough space
    return NCGI_PROCESSED;
}

#define CGI_GET(k)  (k), sizeof(k) - 1
#define CGI_GET_STR(property,func) CGI_GET(property), NULL, NULL, func
#define CGI_GET_INT(property,func) CGI_GET(property), NULL, func, NULL
#define CGI_GETFUNC(property,func) CGI_GET(property), func, NULL, NULL

#if 0
typedef int (*PFN_GET_HANDLER)(char *arg, struct amn_cfgspace_value_t **val, struct NS_ON_CGI_BUF_PARAM *cgi_param);
typedef int (*int_func)(void);
typedef const char* (*str_func)(void);

typedef struct _CGIGET_HANDLER{
    const char*         getArg;
    const int           getArgLen;
    PFN_GET_HANDLER     getHandler;
    //These 2 functions are used as standard value getting.
    //It's hard to use union initializer as 2nd member in C89.
    //It loses type-safety if using c type-casting.
    //So using extra empty functions here is considerably a good trade-off.
    int_func getIntFunc;
    str_func getStrFunc;
    PFN_CGI_HANDLER actFunc;
} CGIGET_HANDLER;
#endif
const char* FWUpdatePercent(void);
static int cameraStdGetStr(char *arg, struct amn_cfgspace_value_t **val, str_func strFunc)
{
    snprintf((*val)->v.strVal, (*val)->max_strlen-1, "%s", strFunc());
    return -1;//this function handled(consumed) this config getting request
}
static int cameraStdGetInt(char *arg, struct amn_cfgspace_value_t **val, int_func intFunc)
{
    (*val)->v.intVal = intFunc();
    return -1;//this function handled(consumed) this config getting request
}

CGIGET_HANDLER get_Handler[] = {
    {CGI_GETFUNC("Camera.Record.",                      cameraRecord),                  GET_ONLY},
    {CGI_GET_INT("Camera.Capture.Remaining",            ncam_get_ui_cap_remaining),     GET_ONLY},
    {CGI_GET_INT("Camera.Battery.Level",                ncam_get_ui_power_level),       GET_ONLY},
    {CGI_GETFUNC("Camera.Preview.MJPEG.status.record",  cameraVideoStatus),             GET_ONLY},
    {CGI_GET_STR("Camera.Preview.MJPEG.status.mode",    ncam_get_sensor_status),        GET_ONLY},
    {CGI_GETFUNC("Camera.Preview.MJPEG.TimeStamp.",     cameraTime),                    GET_ONLY},
    {CGI_GET_STR("Camera.Menu.VideoRes",                ncgi_get_video_res),            Handle_VideoResolution},
    {CGI_GET_STR("Camera.Menu.ImageRes",                ncgi_get_image_res),            Handle_ImageResolution},
    {CGI_GET_STR("Camera.Menu.UIMode",                  ncgi_get_ui_state),             Handle_UIMode},
    {CGI_GET_STR("Camera.Menu.DefMode",                 ncgi_get_def_ui_state),         Handle_DefMode},
    {CGI_GET_STR("Camera.Menu.MTD",                     ncgi_get_mtd_level),            Handle_MTD},
    {CGI_GET_STR("Camera.Menu.AWB",                     ncgi_get_wb),                   Handle_WB},
    {CGI_GET_STR("Camera.Menu.Flicker",                 ncgi_get_flicker_hz),           Handle_Flicker},
    {CGI_GET_STR("Camera.Menu.EV",                      ncgi_get_ev_level),             Handle_EV},
    {CGI_GET_STR("Camera.Menu.PhotoBurst",              ncgi_get_photo_burst),          Handle_PhotoBurst},
    {CGI_GET_STR("Camera.Menu.Timelapse",               ncgi_get_timelapse),            Handle_Timelapse},
    {CGI_GET_STR("Camera.Menu.UpsideDown",              ncgi_get_up_side_down),         Handle_UpsideDown},
    {CGI_GET_STR("Camera.Menu.SpotMeter",               ncgi_get_spot_meter),           Handle_SpotMeter},
    {CGI_GET_STR("Camera.Menu.LoopingVideo",            ncgi_get_looping_video),        Handle_LoopingVideo},
    {CGI_GET_STR("Camera.Menu.VideoClipTime",           ncgi_get_looping_video),        Handle_LoopingVideo},
    {CGI_GET_STR("Camera.Menu.HDR",                     ncgi_get_hdr),                  Handle_HDR},
    {CGI_GET_STR("Camera.Menu.Q-SHOT",                  ncgi_get_q_shot),               Handle_Q_SHOT},
    {CGI_GET_STR("Camera.Menu.StatusLights",            ncgi_get_status_lights),        Handle_StatusLights},
    {CGI_GET_STR("Camera.Menu.SoundIndicator",          ncgi_get_sound_indicator),      Handle_SoundIndicator},
    {CGI_GET_STR("Camera.Menu.PowerSaving",             ncgi_get_power_saving),         Handle_PowerSaving},
    {CGI_GETFUNC("Camera.Menu.IsStreaming",             cameraIsStreaming),             GET_ONLY},
    {CGI_GET_STR("Camera.Menu.FWversion",               ncam_get_fw_version),           GET_ONLY},
    {CGI_GET_STR("Camera.Menu.PowerOffDelay",           ncgi_get_power_off_delay),      Handle_PowerOffDelay},
    {CGI_GET_STR("Camera.Menu.TVSystem",                ncgi_get_tv_system),            Handle_TVSystem},
    {CGI_GET_STR("Camera.Menu.TV",                      ncgi_get_tv_status),            GET_ONLY},
    {CGI_GET_STR("Camera.Menu.SD0",                     ncam_get_ui_sd0_status),        Handle_SD0},
    {CGI_GETFUNC("Camera.Preview.MJPEG.WarningMSG",     cameraWarning),                 GET_ONLY},
    {CGI_GETFUNC("Camera.File.Total",                   cameraFileTotal),               GET_ONLY},
    {CGI_GET_STR("Camera.FWupdate.Progress",            FWUpdatePercent),               GET_ONLY},
    {CGI_GET_STR("Camera.Menu.GSensor",                 ncam_get_gsensor_sensitivity),  Handle_GsensorSensitivity},
    {CGI_GET_STR("DidToken",                            ncgi_get_did_token),            Handle_SetDidToken},
    {CGI_GET_STR("Camera.Menu.LCDPower",                ncgi_get_lcdpower),             Handle_LCDPowerSave},
    {CGI_GET_STR("Camera.DBFileNum",                    ncgi_get_filenum),              GET_ONLY},
    {CGI_GET_STR("Camera.NormalDBSize",                 ncgi_get_normaldbsize),         GET_ONLY},
    {CGI_GETFUNC("status",                              cameraStatus),                  GET_ONLY},
    {CGI_GETFUNC("broadcast",                           cameraBroadcast),               GET_ONLY},
    {NULL}
};


int web_config_do_handler(int idx, char *key, struct amn_cfgspace_value_t **val, struct NS_ON_CGI_BUF_PARAM *cgi_param)
{
    CGIGET_HANDLER* handler = &(get_Handler[idx]);
    if (handler->getHandler) {
        return handler->getHandler(key, val, cgi_param);
    }
    else if (handler->getIntFunc) {
        if ((*val)->type != CFGSPACE_VALTYP__INT) {
            osal_dprint(ERR, "conf '%s' type (%d) is not INT", key, (*val)->type);
        }
        return cameraStdGetInt(key, val, handler->getIntFunc);
    }
    else if (handler->getStrFunc) {
        if ((*val)->type != CFGSPACE_VALTYP__STR) {
            osal_dprint(ERR, "conf '%s' type (%d) is not STR", key, (*val)->type);
        }
        return cameraStdGetStr(key, val, handler->getStrFunc);
    }
    else {
        return 1;//ignore this setting, do next conf
    }
}

int web_config_handle(CGIGET_HANDLER handers[], char *key, struct amn_cfgspace_value_t **val, char **name,
        struct NS_ON_CGI_BUF_PARAM *cgi_param)
{
    int idx;
    for (idx = 0; handers[idx].getArg != NULL; idx++) {
        if (wildstrcmp(*name, handers[idx].getArg, handers[idx].getArgLen) == 0) {
            return web_config_do_handler(idx, *name, val, cgi_param);
        }
    }
    return 1;
}

/*
 * get a runtime state
 * for example property=mj_w&property=mj_h
 * return == -1: this function take care the setting
 *        >=  0: this function ignore the setting, caller have to do next
 */
int web_config_wget(char *key, struct amn_cfgspace_value_t **val, char **name, struct NS_ON_CGI_BUF_PARAM *cgi_param)
{
    int     i, ret;

    i = amn_config_wlocate(key);
    if(i == -1) {
        *name = *val = NULL;
        //printc(FG_RED("%s : ignore key = %s!\n"),__FUNCTION__,key);
        return 0;
    }
    *name = amn_ConfigSpaceDict[i];
    *val  = amn_config_get(CONFIG_SPACE_TYPE_CURRENT, *name);
    // If it is a RUNTIME value, read it from specify API and return -1
    // or return i for further.
    if (((*val)->attr & CFGSPACE_PLAIN)) {
        //osal_dprint(ERR, "Plain!!!!");
    }
    else if (!((*val)->attr & CFGSPACE_RUNTIME)) {
        return i;
    }
    ret = web_config_handle(get_Handler, key, val, name, cgi_param);
    if (ret != 1/*ignore that result*/) {
        return ret;
    }
    return i;
}

int web_config_getEx(char *key, char *szval, int size)
{
    int idx;
    struct amn_cfgspace_value_t *cfg_val;

    for (idx = 0; get_Handler[idx].getArg != NULL; idx++) {
        const char  *tail;

        tail = strrchr(get_Handler[idx].getArg, '.');
        if (tail == NULL)
            tail = (char*)get_Handler[idx].getArg;
        else
            tail++;
        if (strcmpi(key, (char*)tail) == 0) {
            cfg_val = amn_webConfig_get(key);
            if (cfg_val == NULL)
                return 0;
            //if (get_Handler[idx].getHandler(key, &cfg_val) != -1) {
            if (web_config_do_handler(idx, key, &cfg_val, NULL) != -1) {
                break;  // Error
            }
            switch(cfg_val->type) {
            case CFGSPACE_VALTYP__INT:
                return sprintf(szval, "%d", cfg_val->v.intVal);
            case CFGSPACE_VALTYP__STR:
                strncpy(szval, cfg_val->v.strVal, size - 1);
                return strlen(cfg_val->v.strVal);
            }
        }
    }
    return 0;
}

void cgi_printf(char* buf, char** ptr, int size, char *fmt, ...)
{
    int n;
    char *strbuf;
    va_list args;

    va_start(args, fmt);
    if (buf) {
        n = vsnprintf(*ptr, size + 1, fmt, args);
    }
    else {
        strbuf = osal_malloc(size);
        n = vsnprintf(strbuf, size + 1, fmt, args);
        osal_free(strbuf);
    }
    va_end(args);
    *ptr += n;

}

//*******************************************************************************************************
#if !defined(__RTK_OS__)
#ifdef __ARMCC__
#pragma arm section rwdata = "netcgi_init", zidata = "netcgi_init"
#elif defined(__GNUC__)
__section__(netcgi_init)
#endif
unsigned int    netcgi_header = NC_HEADER_ID;
#ifdef __ARMCC__
#pragma arm section code, rwdata,  zidata
#endif
#endif

void init_cgi_handlers( )
{
    loreq_t lr;
    amn_setup_loreq(&lr, NC_HEADER_ID, 0, 0);
    amn_load_module(&lr, (netmo_t*)SECTION_START(NETCGI_INIT),
                                   SECTION_END(NETCGI_INIT));
}

/*
 * arg:
 *   0: JPEG
 *   2: AVI
 *   3: MOV
 *   4: MP4
 *   5: 3GP
 *  -1: ALL
 * refer AHC_DCF.c m_DcfSupportFileType
 */
int dcim_filter_fmt(PFFINST hinst, char *inout, void *attr, FF_ARG *arg)
{
    char            *p;
    int             fmt = (int)attr;
    //unsigned char req = (((unsigned char)(int)arg) & (~(GROUP_FLAG)));
    unsigned char   req = arg->format & (~(GROUP_FLAG));
    //PFFINST           pffi;

    if (!hinst)
        return 0;
    //pffi = (PFFINST)(hinst);

    //printc("File %s fmt %d arg %d\r\n", inout, fmt, (int)arg);
    if (fmt != req && req != ALL_TYPE)
        return 0;
    if ((req != ALL_TYPE) && (arg->format & GROUP_FLAG)) {
        // Get the first member of group
        FILE_GRPINFO    ginf;
        FindFileGroup(hinst, &ginf);
        if (ginf.grpno != 1)
            return 0;
    }
    p = strchr(inout, '\\');
    if (p) {
        int     i;
        for (i = 0; *p != '\0'; p++, i++) {
            *(inout + i) = (*p == '\\')? *p = '/' : *p;
        }
        *(inout + i) = '\0';
    }
    return 1;
}
#define CGIID(a, b, c, d)   ((a) + (b << 8) + (c << 16) + (d << 24))
#define CGIID_DIR           CGIID('d','i','r',' ')
#define MAX_FILE_LEN    80
typedef struct {
        int             cgiid;
        int             retco;
        char            filename[256];
        unsigned int    used;
        int             bufsize;
        char            *buf;
} XMLBUF;
/*
 * dir_copy
 */
int dir_copy(void *dst, void *src, int size)
{
    retbuf_t    *rb;
    XMLBUF      *xmlb;
    int         len;
    XMLBUF ** pp;

    rb = (retbuf_t*)src;
    pp = (XMLBUF**)rb->buf;
    //xmlb = *(XMLBUF**)&rb->buf[0];
    xmlb = *pp;
    len = min(size, xmlb->used - rb->off);
    memcpy(dst, xmlb->buf + rb->off, len);
    rb->off += len;
    return len;
}

int dir_close(void *rb)
{
    XMLBUF      *xmlb;
    XMLBUF ** pp = (XMLBUF**)(((retbuf_t*)rb)->buf);

    xmlb = *pp;
    //xmlb = *(XMLBUF**)&((retbuf_t*)rb)->buf[0];
    osal_free(xmlb);
    osal_free(rb);
    return 0;
}

#if USE_THREAD_SAFE_DCF_API && (MIMF_CUSTOMIZED_SORT_TYPE == MIMF_CUSTOMIZED_SORT_MULTI_DB_DECREASE)
//Due to current implementation. Multi DB traverse does not support thread-safe APIs
    //#error USE_THREAD_SAFE_DCF_API and MIMF_CUSTOMIZED_SORT_MULTI_DB_DECREASE are exclusive.
#endif

/*
 * output XML format of file list
 * cgi-bin/Config.cgi?action=dir&property=DCIM&format=[all[_group]|avi|jpeg[_group]|mov|3gp|mp4]&count=[<number items>]{&from=<from>}
 */
int cgi_dir(IN struct cgi_virt_file_t *f, OUT char *buf, OUT char **endp, IN int maxlen)
{
    static PFFINST hinst = NULL;
    struct cgi_param_t *prmProperty;
    struct cgi_param_t *prmValue;
    int  resp_code = CGI_ERR__OK;
    char            *ptr, *str;
    int             rlen;
    unsigned int    flen;
    int             from, cnt, rc;
    int             rd;
    int             new_file;
    char            *fmt;
    FS_FILETIME     tim;
    FFFILTER_FN     filter;
    char            *filename, *sz;
    XMLBUF          *xmlb, **tmp;
    retbuf_t        *rb;
#if USE_THREAD_SAFE_DCF_API == 0
    DCF_DB_TYPE     old_dcfdb;
    AHC_BOOL        bSwitchDb = AHC_FALSE;
#endif
#if(MIMF_CUSTOMIZED_SORT_TYPE == MIMF_CUSTOMIZED_SORT_MULTI_DB_DECREASE)
    AHC_BOOL        bEnableMultiDb;
#endif

#ifdef __CONFIG_SDK_LETV_CDV01__
    unsigned int idx=0;
#endif
    if (buf == NULL)
        return CGI_ERR__;

    // init DIR XML
    #define MAX_XML_BUFFER  (64*1024)
    xmlb = (XMLBUF*)osal_malloc(MAX_XML_BUFFER);
    if (xmlb == NULL) {
        return CGI_ERR__;
    }
    xmlb->cgiid   = CGIID_DIR;
    xmlb->used    = 0;
    xmlb->bufsize = MAX_XML_BUFFER - sizeof(XMLBUF);
    xmlb->buf     = (char*)xmlb + sizeof(XMLBUF);
    maxlen = xmlb->bufsize;
    ptr  = str = xmlb->buf;
    rb   = (retbuf_t*)f->hand->control;
    tmp  = (XMLBUF**)&rb->buf[0];
    *tmp = xmlb;
    rb->copyfn  = dir_copy;
    rb->closefn = dir_close;
    rb->off    = 0;
    // the property is path
    filename = &xmlb->filename[0];
    prmProperty = cgi_param_nget( f, "property");

    // FileName is by DCF
    {
        struct cgi_param_t *prmStorage;
        prmStorage = cgi_param_nget( f, "storage");
        if (prmStorage) {
            if (!stricmp(prmStorage->value, "SD1")) {
                strcpy(filename, "SD1:");
                sz = filename + 4;
            }
            else {
                strcpy(filename, "SD:");
                sz = filename + 3;
            }
        }
        else
        {
            strcpy(filename, "SD:");
            sz = filename + 3;
        }
    }

    prmValue = cgi_param_nget( f, "format");
    if (prmValue) {
        filter.ffn = dcim_filter_fmt;
        if (!stricmp(prmValue->value, "all")) {
            filter.arg.format = ALL_TYPE;
        } else if (!stricmp(prmValue->value, "jpeg")) {
            filter.arg.format = DCF_TYPE_JPEG;
        } else if (!stricmp(prmValue->value, "avi")) {
            //filter.arg = (void*)2;
            filter.arg.format = DCF_TYPE_AVI;
        } else if (!stricmp(prmValue->value, "mov")) {
            //filter.arg = (void*)3;
            filter.arg.format = DCF_TYPE_MOV;
        } else if (!stricmp(prmValue->value, "mp4")) {
            //filter.arg = (void*)4;
            filter.arg.format = DCF_TYPE_MP4;
        } else if (!stricmp(prmValue->value, "3gp")) {
            //filter.arg = (void*)5;
            filter.arg.format = DCF_TYPE_3GP;
        } else {
            resp_code = CGI_ERR__UNKNOWN_PROPERTY;
            goto __end_dir;
        }
    } else {
        resp_code = CGI_ERR__UNKNOWN_PROPERTY;
        goto __end_dir;
    }
    // Get group option
    prmValue = cgi_param_nget( f, "group");
    if (prmValue) {
        if (!stricmp(prmValue->value, "all")) {
            filter.arg.format = filter.arg.format | GROUP_FLAG;
        }
    }

    //new
    prmValue = cgi_param_nget( f, "new");
    if (prmValue) {
        filter.arg.new_file = FF_ATTR_NEW;
    } else {
        filter.arg.new_file = FF_ATTR_ANY;//don't care
    }

    //new
    prmValue = cgi_param_nget( f, "backward");
    if (prmValue) {
        filter.arg.order = FF_BACKWARD;
    } else {
        filter.arg.order = FF_FORWARD;
    }

    ///
#if USE_THREAD_SAFE_DCF_API == 0
    old_dcfdb = AHC_UF_GetDB(); ///This is used in one of CGI tasks. Is DB lock needed?
#endif
    AHC_UF_SetFreeChar(0, DCF_SET_ALLOWED, (UINT8 *)"MP4,MOV,JPG,AVI");
#if(MIMF_CUSTOMIZED_SORT_TYPE == MIMF_CUSTOMIZED_SORT_MULTI_DB_DECREASE)
    bEnableMultiDb = AHC_MIMF_GetMultiDBBrowseEnable();
    AHC_MIMF_SetMultiDBBrowseEnable(AHC_FALSE);
#endif


    filter.arg.db = DCF_DB_TYPE_DB0_NORMAL;
    if ((!stricmp(prmProperty->value, "DCIM")) || (!stricmp(prmProperty->value, DCFDT_DB0_COMMON_FOLDER_PATH))) {
        //filter.arg->db = DCF_DB_TYPE_DB0_NORMAL;
        //bSwitchDb = AHC_UF_SelectDB(DCF_DB_TYPE_DB0_NORMAL);
    } else if (!strcmp(prmProperty->value, DCFDT_DB1_COMMON_FOLDER_PATH)) {
        #if ( DCF_DB_COUNT >= 2)
            filter.arg.db = DCF_DB_TYPE_DB1_PARKING;
            //bSwitchDb = AHC_UF_SelectDB(DCF_DB_TYPE_DB1_PARKING);
        #else
            //bSwitchDb = AHC_UF_SelectDB(DCF_DB_TYPE_DB0_NORMAL);
        #endif
    } else if (!stricmp(prmProperty->value,DCFDT_DB2_COMMON_FOLDER_PATH)) {
        #if ( DCF_DB_COUNT >= 3)
            filter.arg.db = DCF_DB_TYPE_DB2_EVENT;
            //bSwitchDb = AHC_UF_SelectDB(DCF_DB_TYPE_DB2_EVENT);
        #else
            //bSwitchDb = AHC_UF_SelectDB(DCF_DB_TYPE_DB0_NORMAL);
        #endif
    } else if (!stricmp(prmProperty->value,DCFDT_DB3_COMMON_FOLDER_PATH)) {
        #if ( DCF_DB_COUNT >= 4)
            filter.arg.db = DCF_DB_TYPE_DB3_PHOTO;
            //bSwitchDb = AHC_UF_SelectDB(DCF_DB_TYPE_DB3_PHOTO);
        #else
            //bSwitchDb = AHC_UF_SelectDB(DCF_DB_TYPE_DB0_NORMAL);
        #endif
    } else if (!stricmp(prmProperty->value,DCFDT_DB4_COMMON_FOLDER_PATH)) {
        #if ( DCF_DB_COUNT >= 5)
            filter.arg.db = DCF_DB_TYPE_DB4_SHARE;
            //bSwitchDb = AHC_UF_SelectDB(DCF_DB_TYPE_DB4_SHARE);
        #else
            //bSwitchDb = AHC_UF_SelectDB(DCF_DB_TYPE_DB0_NORMAL);
        #endif
    }
#if(MIMF_CUSTOMIZED_SORT_TYPE == MIMF_CUSTOMIZED_SORT_MULTI_DB_DECREASE)
    else if (!stricmp(prmProperty->value, DCFDT_DBM_MULTI_FOLDER_PATH)) {
        //bSwitchDb = AHC_UF_SelectDB(DCF_DB_TYPE_DB0_NORMAL);
        AHC_MIMF_SetMultiDBBrowseEnable(AHC_TRUE);
    }
#endif
#if USE_THREAD_SAFE_DCF_API
    if (cgi_get_action(f) == CGI_ACTION_REARDIR) {
        filter.arg.cam = FF_CAM_REAR;
    } else {
        filter.arg.cam = FF_CAM_FRONT;
    }
#else
    bSwitchDb = AHC_UF_SelectDB(filter.arg.db);
    if (bSwitchDb == AHC_FALSE) {
        resp_code = CGI_ERR__UNKNOWN_PROPERTY;
        goto __end_dir;
    }
#endif

    if (AHC_FALSE == AHC_SDMMC_IsSD1MountDCF()) {
        resp_code = CGI_ERR__NO_CARD;
        goto __end_dir;
    }

    // Get read from
    prmValue = cgi_param_nget( f, "from");
    from = (prmValue)? atol(prmValue->value) : -1;//-1, continuous list
    // Get get count
    prmValue = cgi_param_nget( f, "count");
    cnt = (prmValue)? atol(prmValue->value) : 20;
    rc = 0;     // amount
    CGI_PRINTF( str, ptr, maxlen, "<?xml version=\"1.0\" encoding=\"UTF-8\" ?>\n");
    CGI_PRINTF( str, ptr, maxlen, "<%s>\n",prmProperty->value);
    //CGI_PRINTF( str, ptr, maxlen, "<DCIM>\n");
    if (from == 0 || hinst == NULL) {
        if ((hinst = FindFirstFile(sz, MAX_FILE_LEN, &rlen, &filter)) == NULL)
            goto __ffgetend;
        if (from < 0) {
            from = 0;//if it's the first time running continuous list, then don't get next file.
        }
    }
    if (from > 0) {
        FindFileSetPosition(hinst, from - 1, &filter);
        if (FindNextFile(hinst, sz, MAX_FILE_LEN, &rlen, &filter) == 0) {
            goto __ffgetend;
        }
    } else if (from < 0) {//-1, continuous list
        if (FindNextFile(hinst, sz, MAX_FILE_LEN, &rlen, &filter) == 0) {
            goto __ffgetend;
        }
    }
    do {
        FILE_GRPINFO ginf;
        MI_INFO      miInfo;

        FindFileAttr(hinst, sz, &flen, &fmt, &rd, &tim, &new_file);
        FindFileGroup(hinst, &ginf);
        CGI_PRINTF( str, ptr, maxlen, "<file>\n");
#ifdef __CONFIG_SDK_LETV_CDV01__  //remove /SD from real path for customer app
        CGI_PRINTF( str, ptr, maxlen, "\t<name>%s</name>\n", sz);
#else
        CGI_PRINTF( str, ptr, maxlen, "\t<name>/SD%s</name>\n", sz);
#endif
        if (miGetMediaInfo(filename, &miInfo)) {
            if (miInfo.type == 1 /* VIDEO*/) {
                int     fpsX10;
                int     tmlX10;

                fpsX10 = (int)(((long long)(miInfo.timescale) * (long long)miInfo.samplecount) * 10 /
                                miInfo.duration);
                tmlX10 = miInfo.duration * 10 / miInfo.timescale;
                CGI_PRINTF( str, ptr, maxlen,
                            "\t<format size=\"%dx%d\" fps=\"%d\" time=\"%d.%d\">%s</format>\n",
                            miInfo.width, miInfo.height, (fpsX10 + 5) / 10, tmlX10 / 10, tmlX10 % 10, fmt);
            } else if (miInfo.type == 2 /* Still Image */) {
                CGI_PRINTF( str, ptr, maxlen, "\t<format size=\"%dx%d\">%s</format>\n",
                                miInfo.width, miInfo.height, fmt);
            } else {
                CGI_PRINTF( str, ptr, maxlen, "\t<format>%s</format>\n", fmt);
            }
        } else {
            CGI_PRINTF( str, ptr, maxlen, "\t<format>%s</format>\n", fmt);
        }
        CGI_PRINTF( str, ptr, maxlen, "\t<size>%u</size>\n", flen);
        CGI_PRINTF( str, ptr, maxlen, "\t<attr>%s</attr>\n", (rd & FS_ATTR_READ_ONLY)? "RO" : "RW");
        CGI_PRINTF( str, ptr, maxlen, "\t<time>%02d-%02d-%02d %02d:%02d:%02d</time>\n",
                    tim.Year, tim.Month, tim.Day, tim.Hour, tim.Minute, tim.Second);
        #if((defined(DCF_GROUP_FUN) && DCF_GROUP_FUN)||(defined __CONFIG_SDK_LETV_CDV01__))
            #ifdef __CONFIG_SDK_LETV_CDV01__ //set tmp group idx for Demo
                CGI_PRINTF( str, ptr, maxlen, "\t<group mode='%s' key='%d' id='%d' total='%d' no='%d'/>\n",
                    ncgi_get_ui_state_by_id(ginf.grpmo), ginf.dkey, /*ginf.grpid*/idx, ginf.grpto, ginf.grpno);
            #else
        CGI_PRINTF( str, ptr, maxlen, "\t<group mode='%s' key='%d' id='%d' total='%d' no='%d'/>\n",
                    ncgi_get_ui_state_by_id(ginf.grpmo), ginf.dkey, ginf.grpid, ginf.grpto, ginf.grpno);
        #endif
        #endif
        CGI_PRINTF( str, ptr, maxlen, "</file>\n");
        rc++;
        if (rc == cnt)
            break;
#ifdef __CONFIG_SDK_LETV_CDV01__
        idx ++;
#endif
    } while (FindNextFile(hinst, sz, MAX_FILE_LEN, &rlen, &filter) != 0);
__ffgetend:
    CGI_PRINTF( str, ptr, maxlen, "<amount>%d</amount>\n", rc);
    CGI_PRINTF( str, ptr, maxlen, "</%s>\n",prmProperty->value);
    //CGI_PRINTF( str, ptr, maxlen, "</DCIM>\n");
    resp_code = CGI_ERR__OK;
__end_dir:
    ptr = buf + (ptr - str);
    xmlb->retco = resp_code;
    xmlb->used  = (unsigned int)(ptr - buf);
    *endp       = (char*)ptr;

#if(MIMF_CUSTOMIZED_SORT_TYPE == MIMF_CUSTOMIZED_SORT_MULTI_DB_DECREASE)
    AHC_MIMF_SetMultiDBBrowseEnable(bEnableMultiDb);
#endif

#if USE_THREAD_SAFE_DCF_API == 0
    AHC_UF_SelectDB(old_dcfdb);
#endif
    return resp_code;
}

/* camproperty: response to App for generate menu
    example:
        "<camera xmlns=\"urn:schemas-ait-dvr:device-1-0\">\n"
        "   <version>0.1</version>\n"
        "   <camtype>CarCam</camtype>\n"
        "   <filefolder type=\"Standard\">\n"
        "       <folder>Normal</folder>\n"
        "       <folder>Photo</folder>\n"
        "       <folder>Event</folder>\n"
        "       <folder>Parking</folder>\n"
        "   </filefolder>\n"
        "</camera>\n"
    note:
    <folder> arttribute us generated by DCF define
*/
int cgi_property(IN struct cgi_virt_file_t *f, OUT char *buf, OUT char **endp, IN int maxlen)
{
    int  resp_code = CGI_ERR__OK;
    char            *ptr = buf;

    CGI_PRINTF( buf, ptr, maxlen, "<?xml version=\"1.0\" encoding=\"UTF-8\" ?>              \
                                  \n<camera xmlns=\"urn:schemas-mstar-dvr:device-1-0\"> \
                                  \n    <version>0.1</version>      \
                                  \n    <camtype>CarCam</camtype>   \
                                  \n    <filefolder>\n");

    CGI_PRINTF( buf, ptr, maxlen, "        <folder>%s</folder>\n",DCFDT_DB0_COMMON_FOLDER_PATH );
    #if ( DCF_DB_COUNT >= 2)
    CGI_PRINTF( buf, ptr, maxlen, "        <folder>%s</folder>\n",DCFDT_DB1_COMMON_FOLDER_PATH );
    #endif
    #if ( DCF_DB_COUNT >= 3)
    CGI_PRINTF( buf, ptr, maxlen, "        <folder>%s</folder>\n",DCFDT_DB2_COMMON_FOLDER_PATH );
    #endif
    #if ( DCF_DB_COUNT >= 4)
    CGI_PRINTF( buf, ptr, maxlen, "        <folder>%s</folder>\n",DCFDT_DB3_COMMON_FOLDER_PATH );
    #endif
    #if ( DCF_DB_COUNT >= 5)
    CGI_PRINTF( buf, ptr, maxlen, "        <folder>%s</folder>\n",DCFDT_DB4_COMMON_FOLDER_PATH );
    #endif
#if(MIMF_CUSTOMIZED_SORT_TYPE == MIMF_CUSTOMIZED_SORT_MULTI_DB_DECREASE)
    CGI_PRINTF( buf, ptr, maxlen, "        <folder>%s</folder>\n",DCFDT_DBM_MULTI_FOLDER_PATH );
#endif

    CGI_PRINTF( buf, ptr, maxlen, "    </filefolder>        \
                                  \n</camera>\n");
    *endp = ptr;
    return resp_code;
}

/*
 * delete file
 * example: cgi-bin/Config.cgi?action=del&property=$DCIM$100__DSC$MOV_1163.AVI
 *          or
 *          cgi-bin/Config.cgi?action=del&property=key&value=<dkey>&property=group&value=<id>
 */
#define CGI_DIRSEP          '$'
#define MAX_PATH_LEN        64
const char  fileroot[] = "SD:\\";
static char gadelfile[MAX_PATH_LEN] ;
int cgi_delete_file(IN struct cgi_virt_file_t *f, OUT char *buf, OUT char **endp, IN int maxlen)
{
    int     i, len;
    char    *path, *ptr;

    if (!buf) return CGI_ERR__OK;   // dry run
    path = cgi_get_property(f);
    if (strcmp(path, "key") == 0) {
        #if(defined(DCF_GROUP_FUN) && DCF_GROUP_FUN)
        struct cgi_param_t *prmValue;
        unsigned short      dkey, grpid;
        // Delete group
        //   get dir key
        prmValue = cgi_param_nget2( f, "value", cgi_get_param(f));
        dkey = atoi(prmValue->value);
        //   get group id
        cgi_inc_param(f);
        prmValue = cgi_param_nget2( f, "value", cgi_get_param(f));
        grpid = atoi(prmValue->value);
        printc("Delete Group File DIRKEY %d GRPID %d\n", dkey, grpid);
        AHC_DCF_DelOneGrp(dkey, grpid);
        #endif

        return CGI_ERR__OK;
    }
    len = strlen(fileroot);
    // support $DCIM.. or DCIM...
    // $SD$PATH$FILE
    ptr = path;
    if ((path[0] == CGI_DIRSEP || path[0] == '/') && path[1] == 'S' && path[2] == 'D')
        ptr = path + 3;
    if (*ptr == CGI_DIRSEP || *ptr == '/') len--;
    strncpy(gadelfile, fileroot, len);
    for (i = len; ptr[i - len] != 0 && i < MAX_PATH_LEN - 1; i++) {
        gadelfile[i] = (ptr[i - len] == CGI_DIRSEP || ptr[i - len] == '/')? '\\' : ptr[i - len];
    }
    gadelfile[i] = 0;
    //printc("DELETE %s\r\n", gadelfile);
    // Check is wildcard *.*, *.jpg, *.avi
    ptr = strrchr(gadelfile, '\\');

    while (ptr) {
        FFFILTER_FN     filter;
        void            *hinst;
        int             rlen;
        int             delcnt;

        ptr++;
        if (*ptr != '*') break;
        // Delete files
        filter.ffn = dcim_filter_fmt;
        if (!stricmp(ptr, "*.*")) {
            //filter.arg = (void*)-1;
            filter.arg.format = DCF_TYPE_ALL;
        } else if (!stricmp(ptr, "*.jpg")) {
            //filter.arg = (void*)0;
            filter.arg.format = DCF_TYPE_JPEG;
        } else if (!stricmp(ptr, "*.avi")) {
            //filter.arg = (void*)2;
            filter.arg.format = DCF_TYPE_AVI;
        } else if (!stricmp(ptr, "*.mov")) {
            //filter.arg = (void*)3;
            filter.arg.format = DCF_TYPE_MOV;
        } else if (!stricmp(ptr, "*.mp4")) {
            //filter.arg = (void*)4;
            filter.arg.format = DCF_TYPE_MP4;
        } else if (!stricmp(ptr, "*.3gp")) {
            //filter.arg = (void*)5;
            filter.arg.format = DCF_TYPE_3GP;
        } else {
            return CGI_ERR__OK;
        }
        do {
            // delete all files until no files can be deleted! (read only)
            delcnt = 0;
            strcpy(gadelfile, "SD:");
            if ((hinst = FindFirstFile(gadelfile + strlen(gadelfile), MAX_PATH_LEN, &rlen, &filter)) == NULL)
                break;
            do {
                int     i;
                if (GetFrontFilename(gadelfile))
                    AHC_UF_SetRearCamPathFlag(AHC_FALSE);
                for (i = 0; *(gadelfile + i) != 0; i++)
                    if (*(gadelfile + i) == '/') *(gadelfile + i) = '\\';
                if (ncam_del_file((char*)gadelfile) == 0) delcnt++;
                strcpy(gadelfile, "SD:");
            } while(FindNextFile(hinst, gadelfile + strlen(gadelfile), MAX_FILE_LEN, &rlen, &filter) != 0);
        } while (delcnt != 0);
        return CGI_ERR__OK;
    }

    if (GetFrontFilename(gadelfile))
        AHC_UF_SetRearCamPathFlag(AHC_FALSE);
    if (ncam_check_filelock((char*)gadelfile))
        return CGI_ERR__FILE_LOCK;
    if (ncam_del_file((char*)gadelfile))
        return CGI_ERR__;
    return CGI_ERR__OK;
}

/*
 * generate a HTML5 page
 */
static char html5[] =
"<!DOCTYPE html>\r\n"
"<html>\r\n"
"<body>\r\n"
"<video width=\"%d\" height=\"%d\" controls>\r\n"
"  <source src=\"%s\" type=\"video/mp4\">\r\n"
"</video>\r\n"
"</body>\r\n"
"</html>\r\n";
/*
 * URL example:
 * /cgi-bin/Config.cgi?action=play&property=DCIM$100__DSC$MOV_0001.MOV
 */
int cgi_play_file(IN struct cgi_virt_file_t *f, OUT char *buf, OUT char **endp, IN int maxlen)
{
    int     i, len;
    char    *path;
    char    vfn[MAX_PATH_LEN];
    MI_INFO miInfo;
    //int       width, height;

    path = cgi_get_property(f);
    len = strlen(fileroot);
    if (path[0] == CGI_DIRSEP) len--;
    strncpy(vfn, fileroot, len);
    for (i = len; path[i - len] != 0 && i < MAX_PATH_LEN - 1; i++) {
        vfn[i] = (path[i - len] == CGI_DIRSEP || path[i - len] == '/')? '\\' : path[i - len];
    }
    vfn[i] = 0;
    printc("%s %d: Play File %s\r\n", vfn);
    // Get width/height
    if (miGetMediaInfo(vfn, &miInfo) == 0) {
        return CGI_ERR__;
    }
    CGI_PRINTF( buf, *endp, maxlen, html5, miInfo.width, miInfo.height, vfn + len); // support $DCIM.. or DCIM...
    return CGI_ERR__OK;
}

int cgi_switch_camera(IN struct cgi_virt_file_t *f, OUT char *buf, OUT char **endp, IN int maxlen)
{
    struct cgi_param_t *prmProperty;
    struct cgi_param_t *prmValue;

    struct amn_cfgspace_value_t *cfg_val;

    prmProperty = cgi_param_nget2( f, "property", cgi_get_param(f));
    prmValue = cgi_param_nget2( f, "value", cgi_get_param(f));

    if (!stricmp(prmValue->value, "front"))
        amn_config_set(CONFIG_SPACE_TYPE_CURRENT,prmProperty->value, "front");
    else if (!stricmp(prmValue->value, "rear"))
        amn_config_set(CONFIG_SPACE_TYPE_CURRENT,prmProperty->value, "rear");

    cfg_val  = amn_config_get( CONFIG_SPACE_TYPE_CURRENT, prmProperty->value);
    printc("prmProperty=%s,value=%s\n",prmProperty->value,cfg_val->v.strVal);
    //ncam_switch_cam();

    CGI_PRINTF( buf, *endp, maxlen, "0\nOK\n" );

    return CGI_ERR__OK;
}


/*
 * the command has not processed yet -> return NETAPP_CONT (0)
 * the command processes failed      -> return NETAPP_FAIL (-2)
 * the command processed             -> return NETAPP_DONE (-1)
 */
ncgi_ret cgi_handle_net_cmd(CGI_HANDLER cmds[], char *key, char *val, PFN_WEBWAIT pfn_w, PFN_CGI_OP_CALLBACK pfn_s)
{
    int i;
    ncgi_ret    ret;
    ret.cgi = CGI_RET_UNASSIGNED;
    ret.netapp = NETAPP_DONE; // finish job, not to do any more after return.

    for (i = 0; cmds[i].cmdKey != NULL; i++) {
        if (wildstrcmp(key, cmds[i].cmdKey, cmds[i].cmdKeyLen) == 0 &&
            cmds[i].cgiHandler != NULL) {
            ret = cmds[i].cgiHandler(key, val, pfn_w, pfn_s);
            return ret;
        }
    }
    //SetKey_Unprocessed:
    //printc("unprocessed key:%s value:%s\r\n", key, val);
    //ret = 0;  // not finish yet, do something after exit this function.
    ret.netapp = NETAPP_CONT;   // not finish yet, do something after exit this function.
    return ret;
}

/* Try to call act handler in getter handler setting (get_Handler)
 * Act here means a Config.cgi?action=set CGI with action handler rather than simply set the value to NET CONF.
 *
 * the command has not processed yet -> return NETAPP_CONT (0)
 * the command processes failed      -> return NETAPP_FAIL (-2)
 * the command processed             -> return NETAPP_DONE (-1)
 */
ncgi_ret cgi_handle_getter_act(char *key, char *val, PFN_WEBWAIT pfn_w, PFN_CGI_OP_CALLBACK pfn_s)
{
    ncgi_ret ret;
    ret.cgi = CGI_RET_UNASSIGNED;
    ret.netapp = NETAPP_DONE;
    {
        int idx;
        for (idx = 0; get_Handler[idx].getArg != NULL; idx++) {
            if (wildstrcmp(key, get_Handler[idx].getArg, get_Handler[idx].getArgLen) == 0) {
                PFN_CGI_HANDLER actFunc;
                actFunc = get_Handler[idx].actFunc;
                if (actFunc == NULL)
                    break;
                return actFunc(key, val, pfn_w, pfn_s);
            }
        }

        //SetKey_Unprocessed:
        //printc("unprocessed property:%s value:%s\r\n", key, val);
        ret.netapp = NETAPP_CONT;   // not finish yet, do something after exit this function.
        return ret;
    }
    return ret;
}

