/*
*********************************************************************************************************
*              AIT Multimedia Network -- Configuration Manager for System Objects
*                     (c) Copyright 2012, Alpha Imaging Technology Corp.
*               All rights reserved. Protected by international copyright laws.
*********************************************************************************************************
*
* Description: Configuration manager
*
*/
#include "mmp_lib.h"
#define __AMN_DEFINES_FOR_CONFIGSPACE_STATICS__
#include "amn_sysobjs.h"
#include "auto_syscfg.h"
#include "amn_cgi.h"
#include "ahc_parameter.h"

#ifndef __AMN_CONFIG_SPACE_FOR_NETWORK_DEFINITIONS__
    #error Please run prelude_MCP.bat before build this MCP
#endif

//*******************************************************************************************************
static int init_config = 0;
static struct amn_config_space_storage_t gCurrSettingStorage;
static struct amn_config_space_storage_t gFactSettingStorage;
static struct amn_config_space_storage_t gStartUpSettingStorage;
struct amn_config_space_storage_t *amn_ConfigSpace_Storages[CONFIG_SPACE_NUMBER];
struct amn_config_space_handler_t amn_ConfigSpaceHandler[MAX_CONFIG_SPACE_HANDLER];
unsigned int export_net_config_file( int type, char* path );
#if(AHC_USER_SFBACKUP)
extern volatile AHC_USERFAT_PARTITION   ulSFUSERActiveNO;
#endif
// Authentication Manager
//*******************************************************************************************************
int amn_login( char *usr, char *pass )
{
    return 0;
}

int amn_logout( char *usr )
{
    return 0;
}



// Authority Manager
//*******************************************************************************************************
#if CFGSPACE_SUPPORT_AUTH
LIST_HEAD(authority_control_list);

static struct amn_authority_control_t *find_authority_obj(osal_thread_pid_t *pid)
{
    struct list_head *l;
    struct amn_authority_control_t *a;

    *pid = osal_thread_getpid();
    list_for_each( l, &authority_control_list ) {
        a = list_entry( l, struct amn_authority_control_t, link );
        if ( osal_thread_equal( *pid, a->pid ) ) {
            return a;
        }
    }
    return NULL;
}
#endif

int amn_register_authority( char *uname, int uclass )
{
#if CFGSPACE_SUPPORT_AUTH
    osal_thread_pid_t  pid;
    struct amn_authority_control_t *auth;

    auth = find_authority_obj(&pid);
    if (auth) {
        // to replace the current thread's USER context with the new one
        osal_dprint(VERBOSE, "AUTH.MAN: Task %d already registered: %s %d", (int)auth->pid, auth->uname, auth->uclass);
        auth->uname  = uname;
        auth->uclass = uclass;
        return 0;
    }

    osal_dprint(VERBOSE, "AUTH.MAN: Register Task=%d user=%s class=%d", (int)pid, uname, uclass);
    auth = osal_zmalloc( sizeof(struct amn_authority_control_t) );
    if (auth) {
        memcpy( &auth->pid, &pid, sizeof(osal_thread_pid_t) );
        auth->uname  = uname;
        auth->uclass = uclass;
        INIT_LIST_HEAD( &auth->link );
        list_add_tail( &auth->link, &authority_control_list );
        return 0;
    }
    return -1;
#else
    return 0;
#endif
}

int amn_unregister_authority()
{
#if CFGSPACE_SUPPORT_AUTH
    osal_thread_pid_t  pid;
    struct amn_authority_control_t *auth;

    auth = find_authority_obj(&pid);
    if (!auth) {
        osal_dprint(WARN, "AUTH.MAN: Task %d not registered before", (int)pid);
        return -1;
    }
    osal_dprint(VERBOSE, "AUTH.MAN: unregister Task=%d user=%s class=%d", (int)auth->pid, auth->uname, auth->uclass);
    list_del( &auth->link );
    osal_free( auth );
#endif
    return 0;
}

int amn_check_authority( char *key, int action )
{
#if CFGSPACE_SUPPORT_AUTH
    osal_thread_pid_t  pid;
    struct amn_authority_control_t *auth;

    auth = find_authority_obj(&pid);
    if (!auth) {
        osal_dprint(VERBOSE, "AUTH.MAN: Task %d not registered before", (int)pid);
        return 0;
    }

    osal_dprint(DEBUG, "AUTH.MAN: check authority for Task %d (%s %d) : action %d on key %s",
                (int)auth->pid, auth->uname, auth->uclass, action, key);
#endif
    return 0;
}

// Configuration Manager
//*******************************************************************************************************
static int locate_config_handler( char *cfgname )
{
    int i;
    struct amn_config_space_handler_t *hand = &amn_ConfigSpaceHandler[CONFIG_SPACE_TYPE_CURRENT];
    for (i=0; i<MAX_CONFIG_SPACE_HANDLER; i++, hand++) {
        if (!strncasecmp( cfgname, hand->cfg_name, hand->namelen )) {
            return i;
        }
    }
    return -1;
}

int amn_config_register_handlers( char *cfgname, int (*setcb)(char* key, struct amn_cfgspace_value_t *cfg, char *val), int (*actcb)() )
{
    int i;

    if (amn_config_wlocate(cfgname) < 0) {
        osal_dprint(INFO, "CONFIG.MAN: unknown Config '%s'", cfgname);
        return -1;
    }
    amn_config_wlocate( "aAbBcCdD" );  // reset the static locals in this sub

    if (locate_config_handler(cfgname) >= 0) {
        osal_dprint(INFO, "CONFIG.MAN: already registered Config '%s'", cfgname);
        return -1;
    }

    for (i=0; i<MAX_CONFIG_SPACE_HANDLER; i++) {
        if (!amn_ConfigSpaceHandler[i].cfg_name) {
            amn_ConfigSpaceHandler[i].cfg_name = cfgname;
            amn_ConfigSpaceHandler[i].namelen  = strlen(cfgname);
            amn_ConfigSpaceHandler[i].set_cb   = setcb;
            amn_ConfigSpaceHandler[i].act_cb   = actcb;
            return 0;
        }
    }
    osal_dprint(WARN, "CONFIG.MAN: Config Space Handlers full");
    return -1;
}

static char* last_key = NULL;
void amn_config_reset_wlocate(void)
{
    last_key = NULL;
}

int amn_config_wlocate2( char *key )
{
    //static char *last_key = NULL;
    static int last_index = -1;
    static int key_len = -1;
    int i;

    if (last_key != key) {
        // initial search
        key_len  = strlen(key);
        last_key = key;
        if (*(key + key_len - 1) == '*' || *(key + key_len - 1) == '.') {
            if (*(key + key_len - 1) == '*')
                key_len--;
            last_index = i = amn_config_locate(key);
            if (i != -1) return last_index++;
            /*
            for (last_index=0; last_index < AMN_CONFIGSPACE_TOTAL_ENTRIES; last_index++) {
                if ( !strncasecmp( amn_ConfigSpaceDict[last_index], key, key_len ) ) {
                    return last_index++;
                }
            }*/
        } else {
            // not wildcard
            last_index = i = amn_config_locate(key);
            if (i != -1) return last_index++;
            /*
            for (last_index=0; last_index < AMN_CONFIGSPACE_TOTAL_ENTRIES; last_index++) {
                if ( !stricmp( amn_ConfigSpaceDict[last_index], key ) ) {
                    return last_index++;
                }
            }*/
        }
    }
    else {
        // continual search
        for (;last_index < AMN_CONFIGSPACE_TOTAL_ENTRIES; last_index++) {
            if (!strncasecmp( amn_ConfigSpaceDict[last_index], key, key_len)) {
                return last_index++;
            }
        }
    }

    amn_config_reset_wlocate();//last_key = NULL;  // reset for new search
    return -1;
}
//*******************************************************************************************************
// linear search, wildcard match
int amn_config_wlocate( char *key )
{
    //static char *last_key = NULL;
    static int last_index = -1;
    static int key_len = -1;

    if (last_key != key) {
        // initial search
        key_len  = strlen(key);
        last_key = key;
        if (*(key + key_len - 1) == '*' || *(key + key_len - 1) == '.') {
            if (*(key + key_len - 1) == '*')
                key_len--;
            for (last_index=0; last_index < AMN_CONFIGSPACE_TOTAL_ENTRIES; last_index++) {
                if ( !strncasecmp( amn_ConfigSpaceDict[last_index], key, key_len ) ) {
                    return last_index++;
                }
            }
        } else {
            // not wildcard
            for (last_index=0; last_index < AMN_CONFIGSPACE_TOTAL_ENTRIES; last_index++) {
                if ( !stricmp( amn_ConfigSpaceDict[last_index], key ) ) {
                    return last_index++;
                }
            }
        }
    }
    else {
        // continual search
        for (;last_index < AMN_CONFIGSPACE_TOTAL_ENTRIES; last_index++) {
            if (!strncasecmp( amn_ConfigSpaceDict[last_index], key, key_len)) {
                return last_index++;
            }
        }
    }

    amn_config_reset_wlocate();//last_key = NULL;  // reset for new search
    return -1;
}

// binary tree search, exact match
int amn_config_locate( char *key )
{
    int cmp;
    int imax, imin, i;

    imin = 0;
    imax = AMN_CONFIGSPACE_TOTAL_ENTRIES - 1;
    while (imax >= imin) {
        i = (imax + imin) / 2;
        cmp = strcmp( amn_ConfigSpaceDict[i], key );  // The Config KEY is case-sensitive !!
        if (cmp == 0)  return i;
        if (cmp < 0)   imin = i + 1;
        else           imax = i - 1;
    }
    return -1;  // not found
}

struct amn_cfgspace_value_t *amn_config_get_f( int space_type, char *key, int i)
{
    int j;
    //int i = amn_config_locate( key );
    if (i < 0) {
        i = amn_config_locate( key );
    }

    if (i >= 0) {
        if (amn_check_authority( key, CGI_ACTION_GET ) < 0) {
            osal_dprint(VERBOSE, "CONFIG.MAN: unauthorized to GET the config key: %s", key);
            return NULL;
        }

        j = locate_config_handler( key );
        if (j >= 0 && amn_ConfigSpaceHandler[j].act_cb) {
            if (amn_ConfigSpaceHandler[j].act_cb(key) < 0) { // the handler can forbid accessing Config Space
                osal_dprint(VERBOSE, "CONFIG.MAN: forbid to GET the config key: %s", key);
                return NULL;
            }
        }
        if(!init_config)
            return NULL;
        return &amn_ConfigSpace_Storages[space_type]->cfg_values[i];
    }
    else {
        //osal_dprint(WARN, "CONFIG.MAN: unknown config key: %d:%s", i, key);
        return NULL;
    }
}

#if 1
struct amn_cfgspace_value_t *amn_config_get( int space_type, char *key )
{
    return amn_config_get_f(space_type, key, -1);
}
#else
struct amn_cfgspace_value_t *amn_config_get( int space_type, char *key )
{
    int j;
    int i = amn_config_locate( key );

    if (i >= 0) {
        if (amn_check_authority( key, CGI_ACTION_GET ) < 0) {
            osal_dprint(VERBOSE, "CONFIG.MAN: unauthorized to GET the config key: %s", key);
            return NULL;
        }

        j = locate_config_handler( key );
        if (j >= 0 && amn_ConfigSpaceHandler[j].act_cb) {
            if (amn_ConfigSpaceHandler[j].act_cb(key) < 0) { // the handler can forbid accessing Config Space
                osal_dprint(VERBOSE, "CONFIG.MAN: forbid to GET the config key: %s", key);
                return NULL;
            }
        }

        return &amn_ConfigSpace_Storages[space_type]->cfg_values[i];
    }
    else {
        //osal_dprint(WARN, "CONFIG.MAN: unknown config key: %d:%s", i, key);
        return NULL;
    }
}
#endif

// The <key> is in wildcard, we need to let known the current <cfgname>
struct amn_cfgspace_value_t *amn_config_wget( int space_type, char *key, char **cfg_name )
{
    int i = amn_config_wlocate( key );
    if (i >= 0) {
        *cfg_name = amn_ConfigSpaceDict[i];
        return amn_config_get( space_type, *cfg_name );
    }
    else
        return NULL;
}

int amn_config_set( int space_type, char *key, char *val )
{
    struct amn_cfgspace_value_t *cfg;
    int i = amn_config_locate( key );
    int j;

    if (i >= 0) {
        if (amn_check_authority( key, CGI_ACTION_SET ) < 0) {
            osal_dprint(VERBOSE, "CONFIG.MAN: unauthorized to SET the config key: %s val:%s", key, val);
            return -1;
        }

        cfg = &amn_ConfigSpace_Storages[space_type]->cfg_values[i];

        j = locate_config_handler( key );
        if (j >= 0 && amn_ConfigSpaceHandler[j].set_cb) {
            if (amn_ConfigSpaceHandler[j].set_cb(key, cfg, val) < 0) { // the handler can forbid accessing Config Space
                osal_dprint(VERBOSE, "CONFIG.MAN: forbid to SET the config key: %s", key);
                return -1;
            }
        }

        switch(cfg->type) {
        case CFGSPACE_VALTYP__INT:
            cfg->v.intVal = atoi(val);
            break;
        case CFGSPACE_VALTYP__STR:
            strncpy( cfg->v.strVal, val, cfg->max_strlen-1 );
            break;
        }
        return 0;
    }

    osal_dprint(WARN, "CONFIG.MAN: unknown config key: %s", key);
    return -1;
}

int amn_config_iset( int space_type, char *key, int val )
{
    char vbuf[32];
    sprintf( vbuf, "%d", val );
    return amn_config_set( space_type, key, vbuf );
}

//*******************************************************************************************************
void reset_config_manager( int space_type, struct amn_config_space_storage_t *pCfgSpace )
{
    int  offset, i;

    amn_ConfigSpace_Storages[space_type] = pCfgSpace;

    // This config space is completely empty
    if (pCfgSpace->amn_cfg_magic_identify != AMN_CONFIGSPACE_MAGIC_IDENTITY)
        memcpy( pCfgSpace, &amn_syscfg_factory, sizeof(struct amn_config_space_storage_t) );

    // align the String Buffer pointer to 'my' own space
    if (pCfgSpace->amn_pic_struct_base != pCfgSpace) {
        offset   = (char*)pCfgSpace - (char*)pCfgSpace->amn_pic_struct_base;
        for (i=0; i<AMN_CONFIGSPACE_TOTAL_ENTRIES; i++) {
            if (pCfgSpace->cfg_values[i].type == CFGSPACE_VALTYP__STR) {
                pCfgSpace->cfg_values[i].v.strVal += offset;
            }
        }
    }
}

unsigned int export_net_config_file( int type, char* path )
{
    int                             i = 0;
    OSAL_FILE *                     fileID;
    unsigned int                    err = 0;
    struct amn_cfgspace_value_t     *curcfg;
    struct amn_cfgspace_value_t     *orgcfg, *defcfg;
    char                            line[128];
    int                             ls = 0;
    int                             os = 0;
    int                             update = 0;

    if (init_config == 0) return 0;
    // compare with default settings.
    for(i = 0; i < AMN_CONFIGSPACE_TOTAL_ENTRIES && update == 0; i++) {
        curcfg = amn_config_get(type, amn_ConfigSpaceDict[i]);
        orgcfg = amn_config_get(CONFIG_SPACE_TYPE_STARTUP, amn_ConfigSpaceDict[i]);
        if (curcfg->attr & CFGSPACE_RUNTIME) continue;
        switch(curcfg->type) {
        case CFGSPACE_VALTYP__INT:
            if(curcfg->v.intVal != orgcfg->v.intVal) {
                update = 1;
            }
            break;
        case CFGSPACE_VALTYP__STR:
            if(strcmpi(curcfg->v.strVal, orgcfg->v.strVal) != 0) {
                update = 1;
            }
            break;
        }
    }
    // Nothing changed, return
    if (update == 0) return 0;
    // Something changed and find changed items and save int file
    fileID = osal_fopen(path,"wb");
    if(fileID == NULL) {
        osal_dprint(WARN,"Export: Open Config File Fail. File:%s", path);
        return 1;
    }
    for(i = 0; i < AMN_CONFIGSPACE_TOTAL_ENTRIES; i++) {
        curcfg = amn_config_get(type, amn_ConfigSpaceDict[i]);
        defcfg = amn_config_get(CONFIG_SPACE_TYPE_FACTORY, amn_ConfigSpaceDict[i]);
        if (curcfg->attr & CFGSPACE_RUNTIME) continue;
        switch(curcfg->type) {
        case CFGSPACE_VALTYP__INT:
            if(curcfg->v.intVal != defcfg->v.intVal) {
                ls = snprintf(line, sizeof(line) - 1, "%s=%d\r\n", amn_ConfigSpaceDict[i], curcfg->v.intVal);
                osal_dprint(DEBUG,"line %d:   %s", i, line);
                os = osal_fwrite(line, sizeof(char), ls, fileID);
                if (ls == os) {
                    orgcfg = amn_config_get(CONFIG_SPACE_TYPE_STARTUP, amn_ConfigSpaceDict[i]);
                    orgcfg->v.intVal = curcfg->v.intVal;
                }
            }
            break;
        case CFGSPACE_VALTYP__STR:
            if(strcmp(curcfg->v.strVal, defcfg->v.strVal) != 0) {
                ls =  snprintf(line, sizeof(line) - 1, "%s=\"%s\"\r\n", amn_ConfigSpaceDict[i], curcfg->v.strVal);
                osal_dprint(DEBUG,"line %d:   %s", i, line);
                os = osal_fwrite(line, sizeof(char), ls, fileID);
                if (ls == os) {
                    orgcfg = amn_config_get(CONFIG_SPACE_TYPE_STARTUP, amn_ConfigSpaceDict[i]);
                    strncpy(orgcfg->v.strVal, curcfg->v.strVal, orgcfg->max_strlen-1);
                }
            }
            break;
        }
        if(ls!=os) {
            osal_dprint(WARN,"Export: Write Config File Fail. File:%s", path);
            osal_dprint(WARN,"Export String:%s", line);
            osal_dprint(WARN,"Export Size:%d, Write Size:%d", ls, os);
            err = 1;
        }
    }
    osal_dprint(INFO,"Export Config File:%s", path);
    osal_fclose(fileID);
    {
        char    *curssid, *orgssid;
        char    *curpsk,  *orgpsk;

        orgssid = amn_config_get(CONFIG_SPACE_TYPE_STARTUP, "Net.WIFI_AP.SSID")->v.strVal;
        curssid = amn_config_get(CONFIG_SPACE_TYPE_CURRENT, "Net.WIFI_AP.SSID")->v.strVal;
        orgpsk  = amn_config_get(CONFIG_SPACE_TYPE_STARTUP, "Net.WIFI_AP.CryptoKey")->v.strVal;
        curpsk  = amn_config_get(CONFIG_SPACE_TYPE_CURRENT, "Net.WIFI_AP.CryptoKey")->v.strVal;
        if (strcmp(orgssid, curssid) || strcmp(orgpsk, curpsk)) {
            //extern int AHC_WriteSSIDPW2NFC(char * pszSSID ,char * pszPassword);
            printc(BG_BLUE("Write SSID/PSK to %s %sNFC\n"), curssid, curpsk);
            amn_config_set(CONFIG_SPACE_TYPE_STARTUP,
                            "Net.WIFI_AP.SSID", curssid);
            amn_config_set(CONFIG_SPACE_TYPE_STARTUP,
                            "Net.WIFI_AP.CryptoKey", curpsk);
            //AHC_WriteSSIDPW2NFC(curssid, curpsk);
        }
    }

    AHC_SFUser_EndProc();

    return err;
}

unsigned char  parser_net_setting(int type, OSAL_FILE* fileId)
{
#define KEY_SIZE    68
#define LNE_SIZE    512
#define INP_SIZE    256
#define _CR_        0x0d
#define _LF_        0x0a
    unsigned int                szRemain = 0;
    unsigned int                szRead;
    char                        bufRead[LNE_SIZE];
    char                        key[KEY_SIZE];
    char                        val[KEY_SIZE];
    char                        rs;
    int                         j;

    szRemain = osal_getfilesize(fileId);
    if (szRemain == 0)
        return 1;
    bufRead[0] = 0;
    rs = 0;
    while(szRemain > 0) {
        char    *ptr, *ln;
        unsigned int    sz;

        szRead = 0;
        sz = ((LNE_SIZE - rs) > INP_SIZE)? INP_SIZE : LNE_SIZE - rs - 1;

        szRead = osal_fread(bufRead + rs, sizeof(char), sz, fileId);
        if(szRead == 0)
            return 1;
        *(bufRead + rs + szRead) = 0;
        ln = bufRead;
        // find _CR_ or _LF_
        for (ptr = ln; *ptr != _CR_ && *ptr != _LF_ && *ptr != 0; ptr++);
        if (*ptr == 0) ptr = NULL;
        while (ptr) {
            char    *p;

            *ptr++ = 0;
            if (*ptr == _LF_ || *ptr == _CR_) ptr++;
            p = ln;
            // skip space
            for (; *p == ' ' || *p == '\t'; p++);
            // the line is a comment
            if (*p == '#') goto _next_line;
            // get key
            for (j = 0; *p != '=' &&
                        *p != ' ' &&
                        *p != '\t'&&
                        *p != '\0'&&
                        j < KEY_SIZE - 1; p++) {
                key[j++] = *p;
            }
            key[j] = 0;
            for (; *p != '=' && *p != '\0'; p++);
            if (*p == '\0') goto _next_line;
            if (*p == '=') p++;
            for (; *p == ' ' || *p == '\t'; p++);
            // get value
            for (j = 0; *p != '\0' && j < KEY_SIZE - 1; p++) {
                if (*p != '\"')
                    val[j++] = *p;
            }
            val[j] = 0;
            if (j == 0) goto _next_line;
            if (amn_ConfigSpace_Storages[type]->cfg_values[amn_config_locate( key )].type ==
                                                                        CFGSPACE_VALTYP__INT) {
                if (strcmpi(val, "YES") == 0) {
                    strcpy(val, "1");
                } else if (strcmpi(val, "NO") == 0) {
                    strcpy(val, "0");
                }
            }
            if(amn_config_set(type, key, val)) {
                osal_dprint(WARN ,"NetConf: key=%s, val=%s", key, val);
            }
#ifdef __AMNSS_DEBUG__
            else
            {
                struct amn_cfgspace_value_t *cfg;
                cfg=&amn_ConfigSpace_Storages[type]->cfg_values[amn_config_locate( key )];
                switch(cfg->type) {
                    case CFGSPACE_VALTYP__INT:
                        osal_dprint(DEBUG,"Read val=%d", cfg->v.intVal);
                        break;
                    case CFGSPACE_VALTYP__STR:
                        osal_dprint(DEBUG,"Read String=%s", cfg->v.strVal);
                        break;
                }
            }
#endif
_next_line:
            ln  = ptr;
            //ptr = strchr(ln, _CR_);
            for (ptr = ln; *ptr != _CR_ && *ptr != _LF_ && *ptr != 0; ptr++);
            if (*ptr == 0) ptr = NULL;
        }
        if (*ln == _LF_ || *ln == _CR_) ln++;
        if (*ln != '\0') {
            strcpy(bufRead, ln);
            rs = strlen(bufRead);
        } else {
            rs = 0;
        }
        szRemain -= szRead;
    }
    return 0;
}


unsigned char apply_user_net_setting(int type, char* path)
{
    MMP_ERR                 status;
    OSAL_FILE*              fileId;

    fileId = osal_fopen(path,"rb");
    if(fileId == NULL)
    {
        osal_dprint(WARN, "No User Network Setting File. File:%s, Type:%d", path, type);
        return 1;
    }

    status = parser_net_setting(type, fileId);

    if(status)
    {
        osal_dprint(WARN, "Apply Network User Setting Failed. File:%s, Type:%d", path, type);
        osal_fclose(fileId);
        return 1;
    }
    osal_fclose(fileId);

    return 0;
}

int web_config_wget(char *key, struct amn_cfgspace_value_t **val, char **name, struct NS_ON_CGI_BUF_PARAM *cgi_param);
void init_config_manager()
{
    if (init_config == 1)
        return;
    amn_register_authority( "admin",   USER_CLASS__ADMIN );
    amn_register_authority( "AIT-AMN", USER_CLASS__AIT );
    osal_dprint(VERBOSE, "CONFIG.MAN: Config Space Storage %d", (int)sizeof(amn_syscfg_factory));
    memset( amn_ConfigSpaceHandler, 0, sizeof(amn_ConfigSpaceHandler) );
    memset( &gCurrSettingStorage, 0, sizeof(gCurrSettingStorage) );
    memset( &gFactSettingStorage, 0, sizeof(gFactSettingStorage) );
    memset( &gStartUpSettingStorage, 0, sizeof(gStartUpSettingStorage) );
    reset_config_manager( CONFIG_SPACE_TYPE_CURRENT, &gCurrSettingStorage);
    reset_config_manager( CONFIG_SPACE_TYPE_FACTORY, &gFactSettingStorage);
    reset_config_manager( CONFIG_SPACE_TYPE_STARTUP, &gStartUpSettingStorage);

    apply_user_net_setting(CONFIG_SPACE_TYPE_FACTORY, NCFG_DEFSET_FILE_NAME);
    apply_user_net_setting(CONFIG_SPACE_TYPE_CURRENT, NCFG_DEFSET_FILE_NAME);
    #if(AHC_USER_SFBACKUP)
    if(ulSFUSERActiveNO == SF2_ACTIVE)
        apply_user_net_setting(CONFIG_SPACE_TYPE_CURRENT, NCFG_USERSET_SF2);
    else if(ulSFUSERActiveNO == SF3_ACTIVE)
        apply_user_net_setting(CONFIG_SPACE_TYPE_CURRENT, NCFG_USERSET_SF3);
    else
        osal_dprint(VERBOSE, "Abnormal SF active partition");
    #else
    apply_user_net_setting(CONFIG_SPACE_TYPE_CURRENT, NCFG_USERSET_FILE_NAME);
    #endif
    apply_user_net_setting(CONFIG_SPACE_TYPE_STARTUP, NCFG_DEFSET_FILE_NAME);
    #if(AHC_USER_SFBACKUP)
    if(ulSFUSERActiveNO == SF2_ACTIVE)
        apply_user_net_setting(CONFIG_SPACE_TYPE_STARTUP, NCFG_USERSET_SF2);
    else if(ulSFUSERActiveNO == SF3_ACTIVE)
        apply_user_net_setting(CONFIG_SPACE_TYPE_STARTUP, NCFG_USERSET_SF3);
    else
        osal_dprint(VERBOSE, "Abnormal SF active partition");
    #else
    apply_user_net_setting(CONFIG_SPACE_TYPE_STARTUP, NCFG_USERSET_FILE_NAME);
    #endif

    //temp hacking before perl script update for more attributes.
    {
        struct amn_cfgspace_value_t *cfg_val = NULL;
        char* cfg_name;
        int  iRet;
        iRet = web_config_wget( NCFG_STATUS, &cfg_val, &cfg_name, NULL);
        if (iRet != -1/*NCGI_PROCESSED*/) {
            //printd(BG_RED("unable to get ")NCFG_STATUS"\r\n");
        }
        else {
            //printd(BG_GREEN("name:%s")"\r\n", cfg_name);
            cfg_val->attr |= CFGSPACE_PLAIN;
        }
        //osal_dprint(ERR, "iRet=%d", iRet);
    }
    init_config = 1;
}
