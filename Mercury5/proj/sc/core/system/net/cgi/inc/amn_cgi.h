/*
*********************************************************************************************************
*                      AIT Multimedia Network -- CGI definitions header
*                     (c) Copyright 2012, Alpha Imaging Technology Corp.
*               All rights reserved. Protected by international copyright laws.
*********************************************************************************************************
*
* Description:  CGI definitions
*
*/
#ifndef __AMN_CGI_DEFINITIONS__
#define __AMN_CGI_DEFINITIONS__

#include "net_serv.h"
#include "amn_osal.h"
#include "amn_sysobjs.h"
#include "netapp.h"

//*******************************************************************************************************
//see cgi_err_text for text explanation
#define CGI_ERR__OK                            0
#define CGI_ERR__ILL_PARAM                     701
#define CGI_ERR__UNKNOWN_ACTION                702
#define CGI_ERR__UNKNOWN_PROPERTY              703
#define CGI_ERR__UNKNOWN_PARAM                 704
#define CGI_ERR__MISS_PARAM                    705
#define CGI_ERR__                              709
#define CGI_ERR__ILL_USER                      710
#define CGI_ERR__ERR_PASS                      711
#define CGI_ERR__REQUIRE_AUTHEN                712
#define CGI_ERR__AUTHEN_FAIL                   713
#define CGI_ERR__NO_AUTHOR                     714
#define	CGI_ERR__SYS_BUSY					   715
#define	CGI_ERR__NO_CARD					   716
#define	CGI_ERR__CARD_LOCK       			   717
#define	CGI_ERR__CARD_ERR                      718
#define	CGI_ERR__CARD_FULL					   719
#define CGI_ERR__SEAMLESS                      720
#define CGI_ERR__PERIPHERAL                    721
#define CGI_ERR__INVALID_STATE                 722
#define CGI_ERR__FILE_LOCK					   723
#define CGI_ERR__NOT_IMPLEMENTED               798
#define CGI_ERR__INTERNAL_ERROR                799

#define CGI_ACTION__ERROR(err)               (-100000 + err)
#define CGI_ACTION_NIL        0
#define CGI_ACTION_GET        1
#define CGI_ACTION_SET        2
#define CGI_ACTION_ADD        3
#define CGI_ACTION_DEL        4
#define CGI_ACTION_MOD        5
#define	CGI_ACTION_DIR        6
#define	CGI_ACTION_PLAY		  7
#define CGI_ACTION_LOGIN      10
#define CGI_ACTION_LOGOUT     11
#define CGI_ACTION_SWITCH     12
#define CGI_ACTION_SENSE      13
#define CGI_ACTION_FWUPDATE   14
#define CGI_ACTION_LOG        15
#define CGI_ACTION_SETSETTING 16
#define CGI_ACTION_GETSETTING 17
#define CGI_ACTION_GETSTATE 18
#define CGI_ACTION_GETINFO 19
#define CGI_ACTION_GETPROGRESS 20
#define CGI_ACTION_GETCONTENTINFO 21
#define CGI_ACTION_EDITCMD 22
#define CGI_ACTION_PLAYCMD 23
#define CGI_ACTION_CAMCMD 24
#define CGI_ACTION_STARTSTREAM 25
#define CGI_ACTION_STOPSTREAM 26
#define CGI_ACTION_SENDDATA 27
#define CGI_ACTION_STARTSENDDATA 28
#define	CGI_ACTION_CAMSWITCH		  29
#define CGI_ACTION_REARDIR		30
#define CGI_ACTION_LOCKED 31
#define CGI_ACTION_WIRELESS 32
#define CGI_ACTION_ACCCTRL 33
#define CGI_ACTION_GET_XML 34
#define CGI_ACTION_EN_GET 	35
#define CGI_ACTION_EN_SET 	36

#define cgi_set_action( f, act )               f->cgi_action_code = act
#define cgi_get_action( f )                    f->cgi_action_code
#define cgi_set_error( f, err )                f->cgi_action_code = CGI_ACTION__ERROR(err)
#define CGI_ACTION_GET_ERROR(ret)              ((ret) >= 0 ? 0 : ((ret) - CGI_ACTION__ERROR(0)))
//#define cgi_get_error( f )                     (f->cgi_action_code >= 0 ? 0 : (f->cgi_action_code - CGI_ACTION__ERROR(0)))
#define cgi_get_error( f )                     CGI_ACTION_GET_ERROR(f->cgi_action_code)

#define CGI_ACTSTATE__NOT_READY                -1
#define CGI_ACTSTATE__EOF                      -2
#define CGI_ACTSTATE__START                     0

#define cgi_set_state( f, st )                 f->cgi_wread_state = st
#define cgi_get_state( f )                     f->cgi_wread_state
#define cgi_inc_state( f )                     f->cgi_wread_state++

#define cgi_get_property( f )                  f->cgi_action_property
#define cgi_get_param( f )                     f->i_param
#define	cgi_inc_param( f )                     f->i_param++
#define	cgi_rst_param( f )                     f->i_param = 0


// _buf NULL for dry-run: facilitate the calculation of CONTENT-LENGTH
#define CGI_COPY_READ_BUF( _buf, _ptr, _str )  do { \
	if (_buf) strcpy( _ptr, _str ); \
	_ptr += strlen( _str ); \
} while (0)

#ifdef __AMN_OS_LINUX__
#define CGI_PRINTF( _buf, _ptr, _size, _fmt, ... )  do { \
	int n; \
	if (_buf) n = cgi_snprintf( _ptr, _size, _fmt,  ##__VA_ARGS__ ); \
	else      n = cgi_snprintf( NULL, _size, _fmt,  ##__VA_ARGS__ ); \
	_ptr += n; \
} while (0)
#else
#if 1
#define CGI_PRINTF( _buf, _ptr, _size, ... )  do { \
	int n; \
	if (_buf) n = cgi_snprintf( _ptr, _size, __VA_ARGS__ ); \
	else      n = cgi_snprintf( NULL, _size, __VA_ARGS__ ); \
	_ptr += n; \
} while (0)
#else
void cgi_printf(char* buf, char** ptr, int size, char *fmt, ...);
#define CGI_PRINTF( _buf, _ptr, _size, ... ) cgi_printf(_buf, &_ptr, _size, __VA_ARGS__)
#endif
#endif

int cgi_snprintf(OUT char *readbuf, IN int size, char *fmt, ...);
char *cgi_err_text(int err_code);
int cgi_err_resp_code(enum cgi_err_t err_code);
void cgi_action_prepare( struct cgi_virt_file_t *f );
void cgi_config_prepare( struct cgi_virt_file_t *f );
int cgi_processs_configs(IN struct cgi_virt_file_t *f, OUT char *buf, IN int maxlen);
void init_cgi_handlers(void);
typedef ncgi_ret (*PFN_CGI_HANDLER)(char *key, char *val, PFN_WEBWAIT pfn_w, PFN_CGI_OP_CALLBACK pfn_s);
typedef struct {
	const char*		cmdKey;
	const int		cmdKeyLen;
	PFN_CGI_HANDLER	cgiHandler;
} CGI_HANDLER;
ncgi_ret cgi_handle_net_cmd(CGI_HANDLER cmds[], char *key, char *val, PFN_WEBWAIT pfn_w, PFN_CGI_OP_CALLBACK pfn_s);
ncgi_ret web_config_act(char *key, char *val, char *buf);

//*******************************************************************************************************
void cgi_config_prepare_s( struct cgi_virt_file_t *f );
int cgi_processs_configs_s(IN struct cgi_virt_file_t *f, OUT char *buf, IN int maxlen, BOOL p);
// CGI Response buffer
#define	MAX_CGI_RESPONSE_SIZE	(8 * 1024)

typedef int (*copy_fn)(void *dst, void *src, int size);
typedef int (*close_fn)(void *rb);
typedef struct {
	int		size;
	int		used;
	int		off;
	copy_fn		copyfn;
	close_fn	closefn;
	char	buf[1];
} retbuf_t;

#endif
