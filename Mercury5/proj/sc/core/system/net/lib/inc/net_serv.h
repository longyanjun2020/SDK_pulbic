/*
*********************************************************************************************************
*                         AIT Multimedia Network - Server Daemons
*                     (c) Copyright 2012, Alpha Imaging Technology Corp.
*               All rights reserved. Protected by international copyright laws.
*********************************************************************************************************
*
* Description: 
*
*/

#ifndef __AMN_NETWORK_SERVERDAEMON_DEFINITIONS__
#define __AMN_NETWORK_SERVERDAEMON_DEFINITIONS__

#include "amn_osal.h"

#include "upnpapi.h"
#include "statcodes.h"
#include "upnp.h"
#include "VirtualDir.h"
#include "webserver.h"
#include "httpreadwrite.h"

//*******************************************************************************************************
#define NET_SERVICE_RTSP    0
#define NET_SERVICE_HTTPS   1
#define NET_SERVICE_HTTPW   2
#define NET_SERVICE_DBG     3
#define NET_SERVICES_TOTAL  4

struct resp_message_t;
typedef	int (*svr_prepare_f)( int, struct resp_message_t *);
typedef	int (*svr_handler_f)( int, struct resp_message_t *);
struct net_service_t {
	char *name;
	int port;
	int fd;
	svr_prepare_f	prepare;	
	svr_handler_f	handler;
};

struct resp_message_t {
	/// struct mserv_request_t
	SOCKET connfd;  /*! Connection handle. */
	struct sockaddr_storage foreign_sockaddr;

	http_parser_t  parser;
	http_message_t *req;
	SOCKINFO info;
	membuffer headers;
	http_header_t *cseq;
	int    persistant;    // equivalent to (NOT struct conn::drop_after), to keep connection after HTTP/RTSP request or not
	size_t content_len;   // http_SendMessage() will require this data type to be <size_t>
	char   *content;      // not using membuffer, for less porting effort
	void   *proto_state;  // struct rtsp_conn* OR struct ammo_session*
	struct net_service_t	*serv;
};

#if 0
#define conn_foreign_addr(resp)    ((resp)->info.foreign_sockaddr.ss_family == AF_INET ? \
		((struct sockaddr_in*)(&(resp)->info.foreign_sockaddr))->sin_addr : \
		((struct sockaddr_in6*)(&(resp)->info.foreign_sockaddr))->sin6_addr)

#define conn_foreign_port(resp)    ((resp)->info.foreign_sockaddr.ss_family == AF_INET ? \
		((struct sockaddr_in*)(&(resp)->info.foreign_sockaddr))->sin_port : \
		((struct sockaddr_in6*)(&(resp)->info.foreign_sockaddr))->sin6_port)
#else
#define conn_foreign_addr(resp)    ((struct sockaddr_in*)(&(resp)->foreign_sockaddr))->sin_addr
#define conn_foreign_port(resp)    ((struct sockaddr_in*)(&(resp)->foreign_sockaddr))->sin_port
#endif

//*******************************************************************************************************
#define AIT_COOKIE_SESS_NAME   "AIT_SESS_ID"
#define EXHEAD__CACHE_CTRL(a)  "Cache-Control: max-age=" #a "\r\n" // prevent CLIENT from caching the response

// Special Authentication return values for struct cgi_file_operations_t::get_info
enum vhand_authen_spec_t {
	VHAND_OK__NO_CHECK_AUTH = 0,       // up to vdir_handle_get_info() to authenticate
	VHAND_OK__AUTHORIZED,              // user authenticated and authorized to access
	VHAND_OK__AUTHENTICATOR,           // login CGIs / CHPs
	VHAND_ERR__NO_CHECK_AUTH = -99,    // up to vdir_handle_get_info() to authenticate
	VHAND_ERR__ILLEGAL_URL_PARAM,      // illegal URL parameters
	VHAND_ERR__REQUIRE_AUTHENTICATION, // no SESSION COOKIE in the HTTP request !!!
	VHAND_ERR__FAIL_AUTHENTICATION,    // user authentication failed (unknown user / wrong password / ...)
	VHAND_ERR__NO_AUTHORITY,           // user has no authority to perform required operation
	VHAND_ERR__EXCEED_SESS_LIMIT,      // Exceeds the maximum sessions limit
	VHAND_ERR__OUT_OF_SERVICE,         // The corresponding web service is out
	VHAND_ERR__INTERNAL,               // Internal error, such as out of memory
	VHAND_ERR__END                     // end mark, *ADD ITEM BEFORE HERE*
};

//*******************************************************************************************************
#define MAX_CGI_PARAM_BUFSZ             256
#define MAX_CGI_PATHNAME_SZ              64
#define MAX_CGI_REQ_URL_SZ              (MAX_CGI_PATHNAME_SZ + MAX_CGI_PARAM_BUFSZ)

struct cgi_virt_file_t;
struct cgi_handler_t;
struct amn_session_t;


struct cgi_param_t {
	struct list_head link;
	char  *value;
	char  *name;         // char name[];  // not supported by ARM-ADS compiler
};

struct cgi_file_operations_t {
	/** Called by the web server to query information on a file.
	 * The callback should return 0 on success or -1 on an error. */
	int (*get_info)( struct cgi_handler_t *h, const char *filename, char **extra_head, struct File_Info *info);

	/** Called by the web server to open a file.
	 * The callback should return 0 on success or -1 on an error. */
	int (*open)( struct cgi_virt_file_t *f );

	/** Called by the web server to perform a sequential read from an open
	 *  file.  The callback should copy \b buflen bytes from the file into
	 *  the buffer.
	 *  @return An integer representing one of the following:
	 *      \li <tt>   0</tt>:  The file contains no more data (EOF).
	 *      \li <tt> > 0</tt>: A successful read of the number of bytes in the
	 *      	return code.
	 *      \li <tt> < 0</tt>: An error occurred reading the file.
	 */
	int (*read)( struct cgi_virt_file_t *f );

	/** Called by the web server to perform a sequential write to an open
	 *  file.  The callback should write \b buflen bytes into the file from
	 *  the buffer.  It should return the actual number of bytes written, 
	 *  which might be less than \b buflen in the case of a write error.
	 */
	int (*write)( struct cgi_virt_file_t *f );

	/** Called by the web server to move the file pointer, or offset, into
	 *  an open file.  The \b origin parameter determines where to start
	 *  moving the file pointer.  A value of \c SEEK_CUR moves the
	 *  file pointer relative to where it is.  The \b offset parameter can
	 *  be either positive (move forward) or negative (move backward).  
	 *  \c SEEK_END moves relative to the end of the file.  A positive 
	 *  \b offset extends the file.  A negative \b offset moves backward 
	 *  in the file.  Finally, \c SEEK_SET moves to an absolute position in 
	 *  the file. In this case, \b offset must be positive.  The callback 
	 *  should return 0 on a successful seek or a non-zero value on an error.
	 */
	int (*seek)( struct cgi_virt_file_t *f, int offset, int whence );

	/** Called by the web server to close a file opened via the \b open
	 *  callback.  It should return 0 on success, or a non-zero value on an 
	 *  error.
	 */
	int (*close)( struct cgi_virt_file_t *f );
};

struct cgi_handler_t {  // object of this class, is persistent per CGI-PATH
	struct list_head link;

	// callback functions: get_info / open / seek / close / read / write
	struct cgi_file_operations_t cb;

	// generic pointer of each CGI's specific control structure
	void   *control;

	// Virtual pathname & filename for this CGI handler
	char   cgi_filePath[MAX_CGI_PATHNAME_SZ];
	short  len_cgifile;

	struct cgi_virt_file_t *curr_file;
};

#define MAX_VIRT_FILE_PRIVATE_BUFSZ   128
// like fopen's FILE struct
struct cgi_virt_file_t {  // object of this class, lives dynamically across the span of OPEN and CLOSE
	struct cgi_handler_t *hand;

	struct resp_message_t *resp;
	http_message_t *req;
	char   req_url[MAX_CGI_REQ_URL_SZ];
	enum UpnpOpenFileMode mode;

	struct amn_session_t *sess;  // the associated user session
	
	// html file for cgi
	char	cgi_html_file[MAX_CGI_PATHNAME_SZ];
	// Request parameters
	void *param_buf;  // simply points to area of all param list, convenience for mem-free
	int  n_params;
	int  i_param;     // current index to process
	struct list_head param_list;

	// Generic control variables
//	int    ivar1;
//	int    ivar2;
//	char  *pvar1;
//	char   buf1[MAX_VIRT_FILE_PRIVATE_BUFSZ];

	int    cgi_wread_state;
	int    cgi_action_code;
	char   cgi_action_property[MAX_VIRT_FILE_PRIVATE_BUFSZ];
	char   *web_extra_header;

	// web_read( buf, ptr, maxlen ) / web_write( buf, ptr, maxlen )
	char   *web_rwbuf;
	char   *web_rwptr;
	int    web_rwlen;

	// fileseek
	int  fread_ptr;
	int  fwrite_ptr;

	// Content buffer for HTTP-send
	int  content_len;
	char *content_buf;
};


// prototypes for API-functions provided by common/ modules
//*******************************************************************************************************
struct cgi_handler_t *find_vdir_handlers( const char *filePath );
struct cgi_handler_t *register_vdir_handlers( char *filePath, struct cgi_file_operations_t *cb );

struct cgi_param_t *cgi_param_iget(IN struct cgi_virt_file_t *f, IN int index);
struct cgi_param_t *cgi_param_nget(IN struct cgi_virt_file_t *f, IN char *name);
struct cgi_param_t *cgi_param_nget2(IN struct cgi_virt_file_t *f, IN char *name, IN int idx);

char *http_get_cookie(struct cgi_virt_file_t *f, char *name);
char *http_set_cookie(struct cgi_virt_file_t *f, char *name, char *val, int age);
char *http_create_session( struct cgi_virt_file_t *f );
char *http_load_session( struct cgi_virt_file_t *f );
int   http_kill_session( struct amn_session_t *sess, char *reason );

struct net_service_t *netserver_new( int port, int serv_type, svr_prepare_f prepare, svr_handler_f handler);
void tcp_send_message( struct resp_message_t *resp );
void init_web_virt_handlers(void);

// prototypes for external functions to be linked into common/ modules
//*******************************************************************************************************
void prepare_response(struct resp_message_t *resp);
int prepare_HTTP_response(int method, struct resp_message_t *resp);

struct snkNode_liveRTSP *find_rtsp_location( char *uri, char *base, int *track );
int rtsp_handle_OPTIONS( struct resp_message_t *resp );
int rtsp_handle_DESCRIBE( struct resp_message_t *resp );
int rtsp_handle_SETUP( struct resp_message_t *resp );
int rtsp_handle_PLAY( struct resp_message_t *resp );
int rtsp_handle_PAUSE( struct resp_message_t *resp );
int rtsp_handle_TEARDOWN( struct resp_message_t *resp );
int rtsp_handle_GET_PARAMETER( struct resp_message_t *resp );
int rtsp_handle_SET_PARAMETER( struct resp_message_t *resp );
int rtsp_handle_unknown( struct resp_message_t *resp );

//*******************************************************************************************************
#endif

