/*
*********************************************************************************************************
*                         AIT Multimedia Network -- HTTP Server
*                     (c) Copyright 2012, Alpha Imaging Technology Corp.
*               All rights reserved. Protected by international copyright laws.
*********************************************************************************************************
*
* Description: Car DV CGI or Camera Video Device CGI
*
*/
#include "amn_cgi.h"
#include "amn_module.h"
#include "mmp_lib.h"
#include "ahc_general.h"
#include "netapp.h"
#include "net_utility.h"

/*! a local dir which serves as webserver root */
extern membuffer gDocumentRootDir;

static struct cgi_handler_t *cgi   = NULL;
static struct cgi_handler_t *thumb = NULL;
#define IS_SPACE(c) ((c) == ' ' || (c) == '\t')
const char CGI_PATH[] = "/cdv";
const char MENU_TAG[] = "<menu";
const char ATTR_ID[]  = "id";
#define MENU_TAG_LEN    (sizeof(MENU_TAG) - 1)
#define ATTR_ID_LEN     (sizeof(ATTR_ID) - 1)
#define CONVERT_PATH_SEP(s) {   char *p;    \
                                for (p = (char*)(s); *p != 0; p++) \
                                    if (*p == '/') *p = '\\'; \
                            }

static int getline(char *data, unsigned int size)
{
    char    *tmp;

    if ((int)size <= 0) {
        return 0;
    }
    tmp = data;
    while (*tmp != '\0') {
        if ((*tmp == '\r' && *(tmp + 1) == '\n') ||
            (*tmp == '\n' && *(tmp + 1) == '\r')) {
            *tmp = '\0';
            return (int)(tmp + 2 - data);
        } else if ((*tmp == '\n') ||
                   (*tmp == '\r')) {
            *tmp = '\0';
            return (int)(tmp + 1 - data);
        }
        tmp++;
    }
    return 0;
}
static char* find_id_token(char *data)
{
    char    *p;
    p = strstr(data, ATTR_ID);
    if (p == NULL)
        return NULL;
    if ((p == data || IS_SPACE(*(p - 1))) &&
        (IS_SPACE(*(p + ATTR_ID_LEN)) || *(p + ATTR_ID_LEN) == '=')) {
        p = strchr(p + ATTR_ID_LEN, '"');
        if (p) {
            char *n;
            n = strchr(p + 1, '"');
            if (n) {
                *n = '\0';
                return p + 1;
            }
        }
    }
    return NULL;
}
int web_config_getEx(char *key, char *name, int size);
unsigned int process_file(char *file, char *buf, unsigned int size)
{
#define SEL_SIZE        1024
#define VALUE_SIZE      32
    void*           hf;
    unsigned int    fsize, rlen;
    int             off;
    char            *dat;
    char            *line, *dst;
    char            value[VALUE_SIZE];
    int             no;

    dat  = NULL;
    rlen = 0;
    hf = osal_fopen(file, "rb");
    if (hf == NULL) goto ERR_PROCESS;
    fsize = osal_getfilesize(hf);
    if (fsize == 0) goto ERR_PROCESS;
    dat = osal_malloc(fsize);
    if (dat == NULL) {
        goto ERR_PROCESS;
    }
    rlen = osal_fread(dat, sizeof(char), fsize, hf);
    if (rlen != fsize) {
        printc("Read File %s Error %d %d!\n", file, rlen, fsize);
        rlen = 0;
        goto ERR_PROCESS;
    }
    line = dat;
    dst = buf;
    no = 0;
    //printc(BG_RED("Data address 0x%08x\n"), dat);
    while ((off = getline(line, fsize)) != 0) {
        int     len;
        char    *p, *id;

        // Write to sel buffer
        no++;
        if (buf) strcpy(dst, line);
        dst += strlen(line);
        if (buf) strcpy(dst, "\n");
        dst += 1;
        // skip space
        for (p = line; IS_SPACE(*p); p++);
        line  += off;
        fsize -= off;
        if (strncmp(p, MENU_TAG, MENU_TAG_LEN) != 0 || !IS_SPACE(*(p + MENU_TAG_LEN))) {
            continue;
        }
        // get id
        id = find_id_token(p + MENU_TAG_LEN);
        if (id == NULL) continue;
        // Get Value
        len = web_config_getEx(id, value, VALUE_SIZE);
        if (len < VALUE_SIZE && len > 0) {
            int     l;
            // Write <sel>Value</sel>
            if (buf) {
                l = sprintf(dst, "<sel>%s</sel>\n", value);
            } else {
                l = strlen("<sel></sel>\n") + strlen(value);
            }
            dst += l;
        }
    }
    rlen = (unsigned int)(dst - buf);
ERR_PROCESS:
    //printc("Free data 0x%08x\n", dat);
    if (dat) osal_free(dat);
    if (hf) osal_fclose(hf);
    return rlen;
}
//*******************************************************************************************************
// get xml file by for cdv/cammenu.xml from root of www
static int web_get_info( struct cgi_handler_t *h, const char *filename, char **extra_head, struct File_Info *info)
{
    char    *p;
    char    filepath[64];

    p = strstr(filename, CGI_PATH);
    sprintf(filepath, "%s\\%s", gDocumentRootDir.buf, p + sizeof(CGI_PATH)); /* skip '/' */
    info->file_length = process_file(filepath, NULL, 0);
    if (info->file_length != 0) {
        info->last_modified = time(NULL);
        info->is_directory = 0;
        info->is_readable = 1;
        info->content_type = osal_strdup("text/xml");  // will be free'd
        return VHAND_OK__AUTHORIZED;
    }
    return VHAND_ERR__OUT_OF_SERVICE;
}

static int web_open( struct cgi_virt_file_t *f )
{
    return 0;
}

static int web_read(IN struct cgi_virt_file_t *f)
{
    int     len;
    char    *p;
    char    filepath[64];
    char    *buf = f->web_rwbuf;

    p = strstr(f->req_url, CGI_PATH);
    sprintf(filepath, "%s\\%s", gDocumentRootDir.buf, p + sizeof(CGI_PATH)); /* skip '/' */
    len = process_file(filepath, buf, f->web_rwlen);
    return len;
}

static int web_write(IN struct cgi_virt_file_t *f)
{
    return 0;
}

static int web_seek(IN struct cgi_virt_file_t *f, IN int offset, IN int whence)
{
    return 0;
}

static int web_close( IN struct cgi_virt_file_t *f)
{
    return 0;
}

/*******************************************************************************/
// Get thumbnail by url /thumb/DCIM/100__DSC/PICT0001.JPG
const char THUMB_PATH[] = "/thumb";

static int thumb_is_valid_ui_state(void)
{
    int ret;
    ret = ns_handle_event(NS_EVENT_QUERY_THUMB_STATE, (void*)NS_MEDIA_CMASK);
    if (ret == NSE_CB_NOT_FOUND) {
        if (ncam_get_streaming_mode() ||
                ncam_is_recording()  ||
                IS_CAMERA_IN_HDMI()) {
            // Not allow to get thumbnail of video when recording.
            osal_dprint(WARN, "Not allow to get thumbnail of video when recording.");
            return 0;
        }
    }
    else if (ANY_NS_ERR(ret)) {
        printc("Invalid UI State err:%d\r\n", ret);
        return 0;
    }
    return 1;
}

//called by vdir_handle_get_info() and most likely by process_request()
static int thumb_get_info( struct cgi_handler_t *h, const char *filename, char **extra_head, struct File_Info *info)
{
    char    *p;
    char    filepath[64];
    int     len;
    void    *hdl;
    int     vhand_err;

    if (!thumb_is_valid_ui_state()) {
        return VHAND_ERR__OUT_OF_SERVICE;
    }
    p = strstr(filename, THUMB_PATH);
    sprintf(filepath, "SD:\\%s", p + sizeof(THUMB_PATH)); /* skip '/' */
    CONVERT_PATH_SEP(filepath);

    hdl = miOpenThumbnail(filepath, &vhand_err);
    if (hdl == NULL) {
        return vhand_err;
    }

    //len = (int)miGetThumbnail(hdl, NULL);
    len = miGetThumbnailSize(hdl);
    if (len > 0)
        info->file_length = len;
    else
        return VHAND_ERR__ILLEGAL_URL_PARAM;
    //printc("JPEG size %d\n", len);

    h->control = hdl;
    info->last_modified = time(NULL);
    info->is_directory = 0;
    info->is_readable = 1;
    info->content_type = osal_strdup("image/jpeg");  // will be free'd
    return 0;
}

static int thumb_open( struct cgi_virt_file_t *f )
{
    return 0;
}

static int thumb_read(IN struct cgi_virt_file_t *f)
{
    int             len;
    char            *p;
    char            filepath[64];
    char            *buf = f->web_rwbuf;
    void            *hdl;

    p = strstr(f->req_url, THUMB_PATH);
    sprintf(filepath, "SD:\\%s", p + sizeof(THUMB_PATH)); /* skip '/' */
    CONVERT_PATH_SEP(filepath)
    hdl = f->hand->control;
    if (hdl == NULL)
        return VHAND_ERR__ILLEGAL_URL_PARAM;
    if (buf) {
        unsigned char   *jbuf;
        len = (int)miGetThumbnail(hdl, &jbuf);
        if (len <= 0 || len > f->web_rwlen)
            return VHAND_ERR__ILLEGAL_URL_PARAM;
        memcpy(buf, jbuf, f->web_rwlen);
    } else {
        //len = (int)miGetThumbnail(hdl, NULL);
        len = miGetThumbnailSize(hdl);
        if (len <= 0)
            return VHAND_ERR__ILLEGAL_URL_PARAM;
    }
    return len;
}

static int thumb_write(IN struct cgi_virt_file_t *f)
{
    return 0;
}

static int thumb_seek(IN struct cgi_virt_file_t *f, IN int offset, IN int whence)
{
    return 0;
}

static int thumb_close( IN struct cgi_virt_file_t *f)
{
    miCloseThumbnail(f->hand->control);
    return 0;
}

//*******************************************************************************************************
static struct cgi_file_operations_t cdv_cb = { web_get_info, web_open, web_read, web_write, web_seek, web_close };
static struct cgi_file_operations_t thumb_cb = { thumb_get_info, thumb_open, thumb_read, thumb_write, thumb_seek, thumb_close };
int init_cdv_cgi(loreq_t *loreq)
{
    if (cgi) return 0;  // already initialized before
    cgi   = register_vdir_handlers((char*)CGI_PATH, &cdv_cb );
    thumb = register_vdir_handlers((char*)THUMB_PATH, &thumb_cb );
    return 1;
}

#ifdef __ARMCC__
#pragma arm section rwdata = "netcgi_init", zidata = "netcgi_init"
#elif defined(__GNUC__)
__section__(netcgi_init)
#endif
netcgi_init_t   _netcgi_cdv_init_ = init_cdv_cgi;
#ifdef __ARMCC__
#pragma arm section code, rwdata,  zidata
#endif
