/*
 * FWupload_cgi.c
 */
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
#include "mmp_lib.h"
#include "netapp.h"
#include "ahc_fs.h"
#include "aihc_dcf.h"

static struct cgi_handler_t *cgi = NULL;
static const char   fwupload_cgi[] = "/cgi-bin/FWupload.cgi";
#define MAX_BOUNDARY_LEN    128
#define MAX_FILENAME_LEN    128
#define MAX_GET_DATABUF_SIZE    ( 8*1024)
#define MAX_POST_DATABUF_SIZE   (64*1024)
typedef struct {
    http_parser_t* parser;
    http_method_t  method;
    char         boundary[MAX_BOUNDARY_LEN];
    char         filename[MAX_FILENAME_LEN];
    int          boundary_len;
    unsigned int content_length;
    char         *databuf;
    unsigned int size_databuf;
    unsigned int cur_datasize;
    unsigned int total_w;
    OSAL_FILE*   fd;
} fwupload_cgi_t;

static void free_fwupload_cgi(fwupload_cgi_t *fcgi)
{
    if (fcgi == NULL) return;
    if (fcgi->databuf)
        osal_free(fcgi->databuf);
    if (fcgi->fd)
        osal_fclose(fcgi->fd);
    fcgi->databuf = NULL;
    fcgi->fd      = NULL;
    osal_free(fcgi);
}

static unsigned int write_fwupload_cgi(fwupload_cgi_t *fcgi, char *data, unsigned int size)
{
    unsigned int    ws;

    if (size == 0)
        return fcgi->total_w;
    ws = size;

    if (fcgi->cur_datasize + ws >= fcgi->size_databuf) {
        unsigned int    cb;
        #define BOUNDARY_TOLERANCE  (2 * fcgi->boundary_len)

        cb = fcgi->size_databuf - fcgi->cur_datasize;
        if ((fcgi->total_w + cb) >
            (fcgi->content_length - BOUNDARY_TOLERANCE)) {
            // the data may have boundary mark that should not save in file,
            // After EOF may have more data then boundary mark,
            // so, give a tolerance that is BOUNDARY_TOLERANCE to protect!!
            cb = 0;
            printc("%s %d: WRITE DATA may has Boundary Mark!!\n", __func__, __LINE__);
        }
        memcpy(fcgi->databuf + fcgi->cur_datasize, data, cb);
        data += cb;
        ws   -= cb;
        fcgi->cur_datasize += cb;
		osal_flush_dcache(fcgi->databuf,fcgi->cur_datasize);
        osal_fwrite(fcgi->databuf, 1, fcgi->cur_datasize, fcgi->fd);
        fcgi->cur_datasize = 0;
    }
    memcpy(fcgi->databuf + fcgi->cur_datasize, data, ws);
    fcgi->cur_datasize += ws;
    fcgi->total_w += size;
    return fcgi->total_w;
}

static unsigned int flush_fwupload_cgi(fwupload_cgi_t *fcgi)
{
    int  len = (int)fcgi->cur_datasize;
    if (fcgi->cur_datasize == 0) return 0;
    if (fcgi->cur_datasize > fcgi->boundary_len) {
        char *p1, *p2;
        int  i, j;
        p1 = fcgi->databuf;
        p2 = fcgi->boundary;
        // find boundary \r\n<boundary>\r\n
        for (i = 0; i <= len - fcgi->boundary_len; i++) {
            for (j = 0; (*(p1 + i + j) == *(p2 + j)) && (j < fcgi->boundary_len); j++);
            if (j == fcgi->boundary_len) {
                for (; i > 0; i--) {
                    if (*(p1 + i) == 0x0a && *(p1 + i - 1) == 0x0d) {
                        fcgi->cur_datasize = (i - 1);
                        break;
                    }
                }
                break;
            }
        }
    }
	osal_flush_dcache(fcgi->databuf,fcgi->cur_datasize);
    osal_fwrite(fcgi->databuf, 1, fcgi->cur_datasize, fcgi->fd);
    fcgi->cur_datasize = 0;
    printc("last %d write total %d content-length %d\n",
                    len,
                    fcgi->total_w,
                    fcgi->content_length);
    return fcgi->total_w;
}
// process HTTP POST
static int cgi_POST(struct cgi_handler_t *h, const char *filename, http_parser_t* parser, struct File_Info *info)
{
    struct cgi_virt_file_t* f;
    fwupload_cgi_t* fcgi = NULL;
    http_message_t* pmsg;
    http_header_t   *ctype;
    memptr          lptr, fptr, vptr;
    parse_status_t  status;
    unsigned int    clen;
    int             parser_cursor;

    f = h->curr_file;
    pmsg = (http_message_t*)f->req;
    // get_CONTENT-LENGTH
    ctype = httpmsg_find_hdr_str(pmsg, "Content-Length");
    if (ctype == NULL)
        return VHAND_ERR__ILLEGAL_URL_PARAM;
    printc("Content-Length:: %s\n", ctype->value.buf);
    clen = atol(ctype->value.buf);
    // get CONTENT-TYPE
    ctype = httpmsg_find_hdr_str(pmsg, "Content-Type");
    if (ctype == NULL)
        return VHAND_ERR__ILLEGAL_URL_PARAM;
    // Content-Type: multipart/form-data; boundary=----------------------98ee193e54ca
    parser_cursor = parser->scanner.cursor;
    printc("Content-Type:: %s, cursor %d\n", ctype->value.buf, parser_cursor);
    if ((status = matchstr(ctype->value.buf, ctype->value.length,
                            "%T%w%iboundary%w=%s", &fptr, &vptr)) == PARSE_OK) {
        int     l = min(vptr.length, MAX_BOUNDARY_LEN - 1);
        fcgi = (fwupload_cgi_t*)osal_malloc(sizeof(fwupload_cgi_t));
        if (fcgi == NULL)
            goto ERR_POST_getinfo;
        memcpy(fcgi->boundary, vptr.buf, l);
        fcgi->boundary[l] = 0;
        fcgi->boundary_len = l;
        fcgi->fd = NULL; //in case of free(fcgi) fail
        fcgi->databuf = NULL;//in case of free(fcgi) fail
        printc("Boundary(%d)%s\n", l, fcgi->boundary);
    }
    if (status != PARSE_OK) {
        goto ERR_POST_getinfo;
    }
    // find boundary
    while ((status = parser_matchstr(parser, "%R%c", &lptr)) == PARSE_OK) {
        int i;
        int  found;

        // for debug
        {
        char s;
        s = lptr.buf[lptr.length];
        lptr.buf[lptr.length] = 0;
        printc("Boundary(%d)%s\n", lptr.length, lptr.buf);
        lptr.buf[lptr.length] = s;
        }
        //
        if (lptr.length < fcgi->boundary_len) continue;
        found = 0;
        for (i = 0; (found == 0) && (i <= lptr.length - fcgi->boundary_len); i++) {
            if (memcmp(lptr.buf + i, fcgi->boundary, fcgi->boundary_len) == 0)
                found = 1;
        }
        if (found != 0)
            break;
    }
    if (status != PARSE_OK) {
        goto ERR_POST_getinfo;
    }
    /*
     * in curl, the boundary seems to send more two of "--" !!
     *------------------------------37cc6a86e060
     *Content-Disposition: form-data; name="fileupload"; filename="AITlogo.jpg"
     *Content-Type: image/jpeg
     */
    parser->position = POS_HEADERS;
    status = parser_parse(parser);
    if (status != PARSE_SUCCESS) {
        goto ERR_POST_getinfo;
    }
    ctype = httpmsg_find_hdr_str(pmsg, "Content-Disposition");
    printc("Content-Disposition:: %s\n", ctype->value.buf);
    if ((status = matchstr(ctype->value.buf, ctype->value.length,
                            "%S%w%iname%w=%q;%wfilename=%q", &lptr, &fptr, &vptr)) == PARSE_OK) {
        //remove quotes
        vptr.buf[vptr.length - 1] = 0;
        sprintf(fcgi->filename, "SD:\\%s", vptr.buf + 1);
    }
    ctype = httpmsg_find_hdr_str(pmsg, "Content-Type");
    printc("Content-Type:: %s\n", ctype->value.buf);
    fcgi->parser = parser;
    fcgi->method = pmsg->method;
    fcgi->databuf  = osal_malloc(MAX_POST_DATABUF_SIZE);
    if (fcgi->databuf == NULL) {
        printc(BG_RED("%s %d: ALLOC MEMORY(%d) FAIL!!\n"), __func__, __LINE__, MAX_POST_DATABUF_SIZE);
        goto ERR_POST_getinfo;
    }
    fcgi->size_databuf  = MAX_POST_DATABUF_SIZE;
    fcgi->cur_datasize = 0;
    fcgi->total_w      = parser->scanner.cursor - parser_cursor;
    printc("DATA from cursor %d %d %d\n", fcgi->total_w, parser->scanner.cursor, parser_cursor);
    fcgi->content_length = clen;
    h->control = fcgi;
    return 0;
ERR_POST_getinfo:
    free_fwupload_cgi(fcgi);
    h->control = NULL;
    return VHAND_ERR__ILLEGAL_URL_PARAM;
}
// process HTTP GET
// cgi-bin/FWupload.cgi?action=flash&property=filename
static int cgi_GET(struct cgi_handler_t *h, const char *filename, http_parser_t* parser, struct File_Info *info)
{
    fwupload_cgi_t* fcgi;
    struct cgi_virt_file_t* f;
    struct cgi_param_t *prmProperty;
    int  resp_code = CGI_ERR__OK;
    char    *buf, *ptr;
    int     ret;

    printc(FG_YELLOW("%s %d\r\n"), __func__, __LINE__);
    h->control = NULL;
    f = h->curr_file;
    cgi_action_prepare(f);
    fcgi = NULL;
    if (ncam_is_flashable() == 0) {
        ret = VHAND_ERR__OUT_OF_SERVICE;
        goto ERR_GET_getinfo;
    }
    if (!f->param_buf ||
        cgi_get_action(f) != CGI_ACTION_FWUPDATE) {
        ret = VHAND_ERR__OUT_OF_SERVICE;
        goto ERR_GET_getinfo;
    }
    //
    prmProperty = cgi_param_nget( f, "property" );
    if (!prmProperty) {
        // defaule fw file, go ahead
        ret = ncgi_flash_fw(NULL, webwait_uiproc, webwait_uisignal);
    } else {
        // go
        strncpy( cgi_get_property(f), prmProperty->value, max( MAX_VIRT_FILE_PRIVATE_BUFSZ, strlen(prmProperty->value)));
        ret = ncgi_flash_fw(cgi_get_property(f), webwait_uiproc, webwait_uisignal);
    }
    if (ret == NETAPP_FAIL) {
        ret = VHAND_ERR__OUT_OF_SERVICE;
        goto ERR_GET_getinfo;
    }
    // init fcgi
    fcgi = (fwupload_cgi_t*)osal_malloc(sizeof(fwupload_cgi_t));
    if (fcgi == NULL) {
        ret = VHAND_ERR__OUT_OF_SERVICE;
        goto ERR_GET_getinfo;
    }
    fcgi->method  = f->req->method;
    fcgi->databuf = osal_malloc(MAX_GET_DATABUF_SIZE);
    fcgi->fd      = NULL;
    if (fcgi->databuf == NULL) {
        printc(BG_RED("%s %d: ALLOC MEMORY(%d) FAIL!!\n"), __func__, __LINE__, MAX_GET_DATABUF_SIZE);
        ret = VHAND_ERR__OUT_OF_SERVICE;
        goto ERR_GET_getinfo;
    }
    fcgi->size_databuf = MAX_GET_DATABUF_SIZE;
    h->control = fcgi;
    // prepare return
    ptr = buf = fcgi->databuf;
    CGI_PRINTF(buf, ptr, fcgi->size_databuf, "%d\n%s\n", resp_code, cgi_err_text(resp_code) );
    info->file_length = ptr - buf;
    info->last_modified = time(NULL); // Thu Mar 7 15:27:04 CST 2013
    info->is_directory = 0;
    info->is_readable = 1;
    info->content_type = osal_strdup("text/plain");  // will be free'd
    cgi_set_state( f, CGI_ACTSTATE__EOF );
    return 0;
ERR_GET_getinfo:
    cgi_set_state( f, CGI_ACTSTATE__EOF );
    free_fwupload_cgi(fcgi);
    h->control = NULL;
    return ret;
}
//*******************************************************************************************************
// flash firmware cgi-bin/FWupload.cgi
static int fwupload_get_info(struct cgi_handler_t *h, const char *filename, char **extra_head, struct File_Info *info)
{
    struct cgi_virt_file_t *f;

    f = h->curr_file;
    switch (f->req->method) {
    case HTTPMETHOD_POST:
        return cgi_POST(h, filename, (http_parser_t*)extra_head, info);
    case HTTPMETHOD_GET:
        return cgi_GET(h, filename, (http_parser_t*)extra_head, info);
    default:
        break;
    }
    return VHAND_ERR__ILLEGAL_URL_PARAM;
}

static int fwupload_open( struct cgi_virt_file_t *f )
{
    fwupload_cgi_t  *fcgi;
    char        *buf;
    size_t      len;

    fcgi = (fwupload_cgi_t*)f->hand->control;
    if (fcgi == NULL || fcgi->method == HTTPMETHOD_GET) return 0;
    fcgi->fd = osal_fopen(fcgi->filename, "wb");
    if (fcgi->fd == NULL) {
        printc(BG_RED("%s %d:ERROR, Open file %s")"\r\n", __func__, __LINE__, fcgi->filename);
        free_fwupload_cgi(fcgi);
        f->hand->control = NULL;
        return -1;
    }
    buf = fcgi->parser->scanner.msg->buf    + fcgi->parser->scanner.cursor;
    len = fcgi->parser->scanner.msg->length - fcgi->parser->scanner.cursor;
    write_fwupload_cgi(fcgi, buf, len);
    return 0;
}

static int fwupload_read(IN struct cgi_virt_file_t *f)
{
    char *buf = f->web_rwbuf;
    fwupload_cgi_t  *fcgi;

    fcgi = (fwupload_cgi_t*)f->hand->control;
    if (fcgi->method != HTTPMETHOD_GET)
        return 0;
    memcpy(buf, fcgi->databuf, f->web_rwlen);
    return f->web_rwlen;
}

static int fwupload_write(IN struct cgi_virt_file_t *f)
{
    fwupload_cgi_t  *fcgi;
    unsigned int    cursize;

    fcgi = (fwupload_cgi_t*)f->hand->control;
    if (fcgi == NULL || fcgi->method == HTTPMETHOD_GET) return 0;
    cursize = write_fwupload_cgi(fcgi, f->web_rwbuf, f->web_rwlen);
    ncam_upload_progress(cursize >> 10, fcgi->content_length >> 10);
    return cursize;
}

static int fwupload_seek(IN struct cgi_virt_file_t *f, IN int offset, IN int whence)
{
    return 0;
}


#define SD_CARDV_FILENAME "SD:\\SD_CarDV.bin"
#define OTA_READ_SIZE   10*1024
static int fwupload_close( IN struct cgi_virt_file_t *f)
{
    fwupload_cgi_t  *fcgi;
    int index=0;
    char cnt[2];
    int total=0;
    char filename[40];
    UINT32 fileId;
    UINT32 mainfileId;
    UINT32 filesize;
    UINT8 databuf[OTA_READ_SIZE];
    UINT32 read_cnt;
    UINT32 write_cnt;

    fcgi = (fwupload_cgi_t*)f->hand->control;
    if (fcgi == NULL) return 0;
    if (fcgi->method == HTTPMETHOD_POST)
        flush_fwupload_cgi(fcgi);
    free_fwupload_cgi(fcgi);
    f->hand->control = NULL;
    ncam_upload_progress(fcgi->content_length >> 10, fcgi->content_length >> 10);

#undef AHC_DCF_FileRemove
#define AHC_DCF_FileRemove(a,b)

    if (fcgi->parser->http_error_code == HTTP_PARTIAL_CONTENT) {
        printc(BG_RED("POST Remove Partial File:%s")"\r\n", fcgi->filename);
        AHC_DCF_FileRemove(fcgi->filename,strlen(fcgi->filename));
        return 0;
    }

    printc(BG_RED("POST Get file %s")"\r\n", fcgi->filename);
    if (!strncmp(fcgi->filename+strlen(fcgi->filename)-3,"end",3)){

        strncpy(cnt,fcgi->filename+strlen(fcgi->filename)-5,2);
        total = atoi(cnt);

        AHC_DCF_FileOpen(SD_CARDV_FILENAME,strlen(SD_CARDV_FILENAME),"wb", strlen("wb"),&mainfileId);
        AHC_DCF_FileSeek(mainfileId, 0, AHC_FS_SEEK_SET);

        for(index =0;index <= total;index++) {
            //CGI_PRINTF( str, ptr, maxlen, "<amount>%d</amount>\n", rc);
            strcpy(filename, SD_CARDV_FILENAME);
            if (index != total)
                if (index < 10)
                    sprintf(filename+strlen(SD_CARDV_FILENAME), "0%d", index);
                else
                    sprintf(filename+strlen(SD_CARDV_FILENAME), "%d", index);
            else
                if (index < 10)
                    sprintf(filename+strlen(SD_CARDV_FILENAME), "0%d%s", index,"end");
                else
                    sprintf(filename+strlen(SD_CARDV_FILENAME), "%d%s", index,"end");
            filename[strlen(filename)] = '\0';

            AHC_DCF_FileOpen(filename,strlen(filename),"rb", strlen("rb"),&fileId);
            if (fileId == 0) {
                printc("ERR Open Fail:%s\n", filename);
                AHC_DCF_FileClose(mainfileId);
                AHC_DCF_FileRemove(SD_CARDV_FILENAME, strlen(SD_CARDV_FILENAME));
                return 0;
            }

            AHC_DCF_FileGetSize(fileId, &filesize);
            while(filesize > 0)
            {
                AHC_DCF_FileRead(fileId, databuf, OTA_READ_SIZE, &read_cnt);
                AHC_DCF_FileWrite(mainfileId, databuf, read_cnt, &write_cnt);
                if (read_cnt != write_cnt) {
                    printc(BG_RED("File write fail, read:%d,write:%d\n"), read_cnt,write_cnt);
                    return -1;
                }
                filesize -= write_cnt;
            }

            printc(BG_RED("POST Merge file %s")"\r\n", filename);
            //printc("File size:%d\n", filesize);
            AHC_DCF_FileClose(fileId);
            AHC_DCF_FileRemove(filename,strlen(filename));
        }
        AHC_DCF_FileClose(mainfileId);
    }
    return 0;
}

static struct cgi_file_operations_t flash_cb = { fwupload_get_info,
                                                 fwupload_open,
                                                 fwupload_read,
                                                 fwupload_write,
                                                 fwupload_seek,
                                                 fwupload_close };
int init_fwupload_cgi(loreq_t *loreq)
{
    if (cgi) return 0;  // already initialized before
    cgi   = register_vdir_handlers((char*)fwupload_cgi, &flash_cb );
    return 1;
}

#ifdef __ARMCC__
#pragma arm section rwdata = "netcgi_init", zidata = "netcgi_init"
#elif defined(__GNUC__)
__section__(netcgi_init)
#endif
netcgi_init_t   _netcgi_fwupload_init_ = init_fwupload_cgi;
#ifdef __ARMCC__
#pragma arm section code, rwdata,  zidata
#endif
