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
#include "amn_module.h"

static struct cgi_handler_t *cgi = NULL;

// testcase: /cgi-bin/Config.cgi?action=get&property=Sys.*
// testcase: /cgi-bin/Config.cgi?action=get&property=Net.*
// testcase: /cgi-bin/Config.cgi?action=get&property=Ass.*
//*******************************************************************************************************
static int web_get_info( struct cgi_handler_t *h, const char *filename, char **extra_head, struct File_Info *info)
{
    int len = 0, n;
    retbuf_t    *rb;

    cgi_config_prepare( h->curr_file );
    cgi_rst_param( h->curr_file );
    rb = (retbuf_t*)osal_malloc(MAX_CGI_RESPONSE_SIZE);
    h->control = rb;
    if (rb == NULL) {
        info->file_length = 0;
        printc("%s %d: memory not enough\n", __func__, __LINE__);
        return 0;
    }
    rb->size = MAX_CGI_RESPONSE_SIZE - sizeof(retbuf_t);
    rb->off  = 0;
    rb->copyfn  = NULL;
    rb->closefn = NULL;
    while ((n=cgi_processs_configs( h->curr_file, rb->buf + len, rb->size - len )) != 0)
        len += n;
    rb->used = len;
    info->file_length = len;
#if 0
    info->file_length = 1000;
    info->file_length = UPNP_INFINITE;
    info->file_length = UPNP_USING_CHUNKED;
    info->file_length = UPNP_UNTIL_CLOSE;
#endif

    info->last_modified = 1362641224; // Thu Mar 7 15:27:04 CST 2013
    info->is_directory = 0;
    info->is_readable = 1;
    if (cgi_get_action(h->curr_file) == CGI_ACTION_PLAY)
        info->content_type = osal_strdup("text/html");  // will be free'd
    else if (cgi_get_action(h->curr_file) == CGI_ACTION_DIR)
        info->content_type = osal_strdup("text/xml");  // will be free'd
    else if (cgi_get_action(h->curr_file) == CGI_ACTION_GET_XML)
    //else if (!strcmp(cgi_get_property(h->curr_file), NCFG_MENU_PROPERTY))
        info->content_type = osal_strdup("text/xml");
    else
        info->content_type = osal_strdup("text/plain");  // will be free'd

    return 0;
}

static int web_open( struct cgi_virt_file_t *f )
{
    return 0;
}

static int web_read(IN struct cgi_virt_file_t *f)
{
    int len = 0;
    retbuf_t *rb = (retbuf_t*)f->hand->control;

    if (rb->copyfn) {
        len = rb->copyfn(f->web_rwbuf, rb, f->web_rwlen);
    } else {
        len = min(f->web_rwlen, rb->used - rb->off);
        if (len != 0) {
            memcpy(f->web_rwbuf, rb->buf + rb->off, f->web_rwlen);
            rb->off += len;
        }
    }
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
    retbuf_t *rb = (retbuf_t*)f->hand->control;

    if (rb->closefn) {
        rb->closefn(rb);
    } else {
        osal_free(rb);
    }
    return 0;
}

//*******************************************************************************************************
static struct cgi_file_operations_t cgi_cb = { web_get_info, web_open, web_read, web_write, web_seek, web_close };

int init_config_cgi(loreq_t *loreq)
{
    if (cgi) return 0;  // already initialized before
    cgi = register_vdir_handlers( "/cgi-bin/Config.cgi", &cgi_cb );
    return 1;
}

#ifdef __ARMCC__
#pragma arm section rwdata = "netcgi_init", zidata = "netcgi_init"
#elif defined(__GNUC__)
__section__(netcgi_init)
#endif
netcgi_init_t   _netcgi_config_init_ = init_config_cgi;
#ifdef __ARMCC__
#pragma arm section code, rwdata,  zidata
#endif


