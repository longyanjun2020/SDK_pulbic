/*******************************************************************************
 *
 * Copyright (c) 2000-2003 Intel Corporation 
 * All rights reserved. 
 * Copyright (c) 2012 France Telecom All rights reserved. 
 *
 * Redistribution and use in source and binary forms, with or without 
 * modification, are permitted provided that the following conditions are met: 
 *
 * - Redistributions of source code must retain the above copyright notice, 
 * this list of conditions and the following disclaimer. 
 * - Redistributions in binary form must reproduce the above copyright notice, 
 * this list of conditions and the following disclaimer in the documentation 
 * and/or other materials provided with the distribution. 
 * - Neither name of Intel Corporation nor the names of its contributors 
 * may be used to endorse or promote products derived from this software 
 * without specific prior written permission.
 * 
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS 
 * "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT 
 * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR 
 * A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL INTEL OR 
 * CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, 
 * EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, 
 * PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR 
 * PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY 
 * OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING
 * NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS 
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 ******************************************************************************/

#ifndef GENLIB_NET_HTTP_HTTPPARSER_H
#define GENLIB_NET_HTTP_HTTPPARSER_H

/*!
 * \file
 */

#include "LinkedList.h"
#include "membuffer.h"
#include "uri.h"
#include "upnputil.h"

/* private types */

/* scanner */

/* Used to represent different types of tokens in input. */
typedef enum
{
	TT_IDENTIFIER, 
	TT_WHITESPACE, 
	TT_CRLF, 
	TT_CTRL,
	TT_SEPARATOR,
	TT_SENTANCE_SEPARATOR,
	TT_QUOTEDSTRING,
	TT_END
} token_type_t;

typedef struct
{
	/*! raw http msg. */
	membuffer* msg;
	/*! current position in buffer. */
	size_t cursor;
	/*! set this to TRUE if the entire msg is loaded in 'msg';
	 * else FALSE if only partial msg in 'msg' (default is FALSE). */
	int entire_msg_loaded;
} scanner_t;

typedef enum
{
	POS_REQUEST_LINE,
	POS_RESPONSE_LINE,
	POS_HEADERS,
	POS_ENTITY,
	POS_COMPLETE,
	POS_END
} parser_pos_t;

#define ENTREAD_DETERMINE_READ_METHOD	1
#define ENTREAD_USING_CLEN		2
#define ENTREAD_USING_CHUNKED		3
#define ENTREAD_UNTIL_CLOSE		4
#define ENTREAD_CHUNKY_BODY		5
#define ENTREAD_CHUNKY_HEADERS		6

/* end of private section. */

/* method in a HTTP request. */
typedef enum
{
	HTTPMETHOD_POST, 
	HTTPMETHOD_MPOST, 
	HTTPMETHOD_SUBSCRIBE, 
	HTTPMETHOD_UNSUBSCRIBE, 
	HTTPMETHOD_NOTIFY, 
	HTTPMETHOD_GET,
	HTTPMETHOD_HEAD, 
	HTTPMETHOD_MSEARCH, 
	HTTPMETHOD_UNKNOWN,
	SOAPMETHOD_POST,
	HTTPMETHOD_SIMPLEGET
} http_method_t;

/* different types of HTTP headers */
#define HDR_UNKNOWN			-1
#define HDR_CACHE_CONTROL		1
#define HDR_CALLBACK			2
#define HDR_CONTENT_LENGTH		3
#define HDR_CONTENT_TYPE		4
#define HDR_DATE			5
#define HDR_EXT				6
#define HDR_HOST			7
/*define HDR_IF_MODIFIED_SINCE		8 */
/*define HDR_IF_UNMODIFIED_SINCE	9 */
/*define HDR_LAST_MODIFIED		10 */
#define HDR_LOCATION			11
#define HDR_MAN				12
#define HDR_MX				13
#define HDR_NT				14
#define HDR_NTS				15
#define HDR_SERVER			16
#define HDR_SEQ				17
#define HDR_SID				18
#define HDR_SOAPACTION			19
#define HDR_ST				20
#define HDR_TIMEOUT			21
#define HDR_TRANSFER_ENCODING		22
#define HDR_USN				23
#define HDR_USER_AGENT			24

/* Adding new header difinition */
#define HDR_ACCEPT			25
#define HDR_ACCEPT_ENCODING		26
#define HDR_ACCEPT_CHARSET		27
#define HDR_ACCEPT_LANGUAGE		28
#define HDR_ACCEPT_RANGE		29
#define HDR_CONTENT_ENCODING		30
#define HDR_CONTENT_LANGUAGE		31
#define HDR_CONTENT_LOCATION		32
#define HDR_CONTENT_RANGE		33
#define	HDR_CONTENT_DISPOSITION 34
#define HDR_IF_RANGE			35
#define HDR_RANGE			36
#define HDR_TE				37

/* method in a RTSP request. */
typedef enum
{
	RTSPMETHOD__START00 = 100,  // bigger than any HTTP method values, so that >100 will be RTSP ones
	RTSPMETHOD_OPTIONS,
	RTSPMETHOD_DESCRIBE,
	RTSPMETHOD_SETUP,
	RTSPMETHOD_PLAY,
	RTSPMETHOD_PAUSE,
	RTSPMETHOD_TEARDOWN,
	RTSPMETHOD_GET_PARAMETER,
	RTSPMETHOD_SET_PARAMETER
} Rtsp_method_t;

/* New header difinitions for RTSP (RFC-2326) */
#define HDR_ALLOW          50
#define HDR_AUTHORIZATION          51
#define HDR_BANDWIDTH          52
#define HDR_BLOCKSIZE          53
#define HDR_CONFERENCE          54
#define HDR_CONNECTION          55
#define HDR_CONTENT_BASE          56
#define HDR_CSEQ          57
#define HDR_EXPIRES          58
#define HDR_FROM          59
#define HDR_IF_MATCH          60
#define HDR_IF_MODIFIED_SINCE          61
#define HDR_LAST_MODIFIED          62
#define HDR_PROXY_AUTHENTICATE          63
#define HDR_PROXY_REQUIRE          64
#define HDR_PUBLIC          65
#define HDR_REFERER          66
#define HDR_RETRY_AFTER          67
#define HDR_REQUIRE          68
#define HDR_RTP_INFO          69
#define HDR_SCALE          70
#define HDR_SPEED          71
#define HDR_SESSION          72
#define HDR_TIMESTAMP          73
#define HDR_TRANSPORT          74
#define HDR_UNSUPPORTED          75
#define HDR_VARY          76
#define HDR_VIA          77
#define HDR_WWW_AUTHENTICATE          78

/*! status of parsing */
typedef enum {
	/*! msg was parsed successfully. */
	PARSE_SUCCESS = 0,
	/*! need more data to continue. */
	PARSE_INCOMPLETE,
	/*! for responses that don't have length specified. */
	PARSE_INCOMPLETE_ENTITY,
	/*! parse failed; check status code for details. */
	PARSE_FAILURE,
	/*! done partial. */
	PARSE_OK,
	/*! token not matched. */
	PARSE_NO_MATCH,
	/*! private. */
	PARSE_CONTINUE_1
} parse_status_t;

typedef struct {
	/*! header name as a string. */
	memptr name;
	/*! header name id (for a selective group of headers only). */
	int name_id;
	/*! raw-value; could be multi-lined; min-length = 0. */
	membuffer value;
	/* private. */
	membuffer name_buf;
} http_header_t;

typedef struct {
	#define NET_PROTO_TYPE__RTSP  0
	#define NET_PROTO_TYPE__HTTP  1
	/*! [AIT] Can be HTTP or RTSP */
	int proto_type;
	/*! [AIT] convenient pointer to method name */
	char *method_name;
	/*! [AIT] point to the enclosing object: struct resp_message_t */
	void *enclose_obj;

	int initialized;
	/*! request only. */
	http_method_t method;
	/*! request only. */
	uri_type uri;
	/*! response only. */
	http_method_t request_method;
	/*! response only. */
	int status_code;
	/*! response only. */
	membuffer status_msg;
       /*! response only. the amount of data that's been read by the user, that's no
        *  longer in the raw message buffer.
        */
       size_t amount_discarded;
	/* fields used in both request or response messages. */
	/*! if TRUE, msg is a request, else response. */
	int is_request;
	/* http major version. */
	int major_version;
	/* http minor version. */
	int minor_version;
	/*! . */
	LinkedList headers;
	/*! message body(entity). */
	memptr entity;
	/* private fields. */
	/*! entire raw message. */
	membuffer msg;
    /*! storage for url string. */
    char *urlbuf;
    /* Send Instruction for HTTP POST */
//	struct SendInstruction *pInst;
	/*! extra function. */
	int privatefunc;
} http_message_t;

typedef struct {
	http_message_t msg;
	/*! read-only; in case of parse error, this
	 * contains the HTTP error code (4XX or 5XX). */
	int http_error_code;
	/*! read-only; this is set to true if a NOTIFY request has no
	 * content-length. used to read valid sspd notify msg. */
	int valid_ssdp_notify_hack;
	/* private data -- don't touch. */
	parser_pos_t position;
	int ent_position;
	unsigned int content_length;
	size_t chunk_size;
       /*! offset in the the raw message buffer, which contains the message body.
        *  preceding this are the headers of the messsage. */
	size_t entity_start_position;
	scanner_t scanner;
} http_parser_t;

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/************************************************************************
*	Function :	httpmsg_init
*
*	Parameters :
*		INOUT http_message_t* msg ;	HTTP Message Object
*
*	Description :	Initialize and allocate memory for http message
*
*	Return : void ;
*
*	Note :
************************************************************************/
void httpmsg_init( INOUT http_message_t* msg );

/************************************************************************
*	Function :	httpmsg_destroy
*
*	Parameters :
*		INOUT http_message_t* msg ;	HTTP Message Object
*
*	Description :	Free memory allocated for the http message
*
*	Return : void ;
*
*	Note :
************************************************************************/
void httpmsg_destroy( INOUT http_message_t* msg );

/************************************************************************
*	Function :	httpmsg_find_hdr_str
*
*	Parameters :
*		IN http_message_t* msg ;	HTTP Message Object
*		IN const char* header_name ; Header name to be compared with	
*
*	Description :	Compares the header name with the header names stored 
*		in	the linked list of messages
*
*	Return : http_header_t* - Pointer to a header on success;
*			 NULL on failure
*	Note :
************************************************************************/
http_header_t* httpmsg_find_hdr_str( IN http_message_t* msg,
			IN const char* header_name );

/************************************************************************
*	Function :	httpmsg_find_hdr
*
*	Parameters :
*		IN http_message_t* msg ; HTTP Message Object
*		IN int header_name_id ;	 Header Name ID to be compared with
*		OUT memptr* value ;		 Buffer to get the ouput to.
*
*	Description :	Finds header from a list, with the given 'name_id'.
*
*	Return : http_header_t*  - Pointer to a header on success;
*		 NULL on failure
*
*	Note :
************************************************************************/
http_header_t* httpmsg_find_hdr( IN http_message_t* msg, 
			IN int header_name_id, OUT memptr* value );

/************************************************************************
* Function: parser_request_init											
*																		
* Parameters:															
*	OUT http_parser_t* parser ; HTTP Parser object									
*																
* Description: Initializes parser object for a request					
*																		
* Returns:																
*	 void																
************************************************************************/
void parser_request_init( OUT http_parser_t* parser );

/************************************************************************
* Function: parser_response_init										
*																		
* Parameters:															
*	OUT http_parser_t* parser	;	  HTTP Parser object
*	IN http_method_t request_method	; Request method 					
*																		
* Description: Initializes parser object for a response					
*																		
* Returns:																
*	 void																
************************************************************************/
void parser_response_init( OUT http_parser_t* parser, 
			   IN http_method_t request_method );

/************************************************************************
* Function: parser_parse												
*																		
* Parameters:															
*	INOUT http_parser_t* parser ; HTTP Parser object					
*																		
* Description: The parser function. Depending on the position of the 	
*	parser object the actual parsing function is invoked				
*																		
* Returns:																
*	 void																
************************************************************************/
parse_status_t parser_parse(INOUT http_parser_t * parser);

/************************************************************************
* Function: parser_parse_responseline									
*																		
* Parameters:															
*	INOUT http_parser_t* parser	; HTTP Parser object					
*																		
* Description: Get HTTP Method, URL location and version information.	
*																		
* Returns:																
*	PARSE_OK															
*	PARSE_SUCCESS														
*	PARSE_FAILURE														
************************************************************************/
parse_status_t parser_parse_responseline(INOUT http_parser_t *parser);

/************************************************************************
* Function: parser_parse_headers									
*																		
* Parameters:															
*	INOUT http_parser_t* parser	; HTTP Parser object										
*													
* Description: Get HTTP Method, URL location and version information.	
*																		
* Returns:																
*	PARSE_OK															
*	PARSE_SUCCESS														
*	PARSE_FAILURE														
************************************************************************/
parse_status_t parser_parse_headers(INOUT http_parser_t *parser);

/************************************************************************
* Function: parser_parse_entity											
*																		
* Parameters:															
*	INOUT http_parser_t* parser	; HTTP Parser object					
*																		
* Description: Determines method to read entity							
*																		
* Returns:																
*	 PARSE_OK															
* 	 PARSE_FAILURE														
*	 PARSE_COMPLETE	-- no more reading to do							
************************************************************************/
parse_status_t parser_parse_entity(INOUT http_parser_t *parser);

/************************************************************************
* Function: parser_get_entity_read_method								
*																		
* Parameters:															
*	INOUT http_parser_t* parser	; HTTP Parser object					
*																		
* Description: Determines method to read entity							
*																		
* Returns:																
*	 PARSE_OK															
* 	 PARSE_FAILURE														
*	 PARSE_COMPLETE	-- no more reading to do							
************************************************************************/
parse_status_t parser_get_entity_read_method( INOUT http_parser_t* parser );

/************************************************************************
* Function: parser_append												
*																		
* Parameters:															
*	INOUT http_parser_t* parser ;	HTTP Parser Object					
*	IN const char* buf	;	buffer to be appended to the parser
*					buffer
*	IN size_t buf_length ;		Size of the buffer
*																		
* Description: The parser function. Depending on the position of the 	
*	parser object the actual parsing function is invoked				
*																		
* Returns:																
*	 void																
************************************************************************/
parse_status_t parser_append( INOUT http_parser_t* parser, 
				 IN const char* buf,
				 IN size_t buf_length );

/************************************************************************
* Function: parser_matchstr													
*																		
* Parameters:															
*	INOUT http_parser_t * parser ;	HTTP Parser Object
*	IN const char* fmt ; Pattern format												
*	...																	
*																		
* Description: Matches a variable parameter list with a http_parser_t
*	and takes actions based on the data type specified.					
*																		
* Returns:																
*   PARSE_OK															
*   PARSE_NO_MATCH -- failure to match pattern 'fmt'					
*   PARSE_FAILURE	-- 'str' is bad input							
************************************************************************/
parse_status_t parser_matchstr( INOUT http_parser_t * parser, IN const char *fmt, ... );

/************************************************************************
* Function: matchstr													
*																		
* Parameters:															
*	IN char *str ;		 String to be matched
*	IN size_t slen ;     Length of the string
*	IN const char* fmt ; Pattern format												
*	...																	
*																		
* Description: Matches a variable parameter list with a string			
*	and takes actions based on the data type specified.					
*																		
* Returns:																
*   PARSE_OK															
*   PARSE_NO_MATCH -- failure to match pattern 'fmt'					
*   PARSE_FAILURE	-- 'str' is bad input							
************************************************************************/
parse_status_t matchstr( IN char *str, IN size_t slen, IN const char* fmt, ... );

/************************************************************************
* Function: raw_to_int													
*																		
* Parameters:															
*	IN memptr* raw_value ;	Buffer to be converted 					
*	IN int base ;			Base  to use for conversion
*																		
* Description: Converts raw character data to long-integer value					
*																		
* Returns:																
*	 int																
************************************************************************/
int raw_to_int( IN memptr* raw_value, int base );

/************************************************************************
* Function: raw_find_str
*
* Parameters:
*	IN memptr* raw_value ; Buffer containg the string
*	IN const char* str ;	Substring to be found
*
* Description: Find a substring from raw character string buffer
*
* Side effects: raw_value is transformed to lowercase.
*
* Returns:
*	 int - index at which the substring is found.						
************************************************************************/
int raw_find_str( IN memptr* raw_value, IN const char* str );

/************************************************************************
* Function: method_to_str												
*																		
* Parameters:															
* IN http_method_t method ; HTTP method						
*																		
* Description: A wrapper function that maps a method id to a method		
*	nameConverts a http_method id stored in the HTTP Method				
*																		
* Returns:																
*	 const char* ptr - Ptr to the HTTP Method
************************************************************************/
const char* method_to_str( IN http_method_t method );

/*!
 * \brief Print the HTTP headers.
 */
#ifdef HTTP_HEADER_DEBUG
void print_http_headers(
	/*! [in] HTTP Message object. */
	http_message_t *hmsg);
#else
static UPNP_INLINE void print_http_headers(http_message_t *hmsg)
{
	return;
	hmsg = hmsg;
}
#endif

#ifdef __cplusplus
}		/* extern "C" */
#endif	/* __cplusplus */

#endif /* GENLIB_NET_HTTP_HTTPPARSER_H */

