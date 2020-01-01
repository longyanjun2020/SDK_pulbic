
#ifndef __WSP_HEADER_H__
#define __WSP_HEADER_H__

#include <ncc_types.h>
#include <stdio.h>
#include <dlm_respheader.h>
#include <wsp_code.h>

#ifdef __cplusplus
extern  "C" {
#endif

#define WAP_ARRAY_LEN(ch) sizeof(ch)/sizeof(ch[0])

#define RES_CONTINUE                        0x10
#define RES_SWITCHING_PROTOCOLS             0x11
#define RES_OK                              0x20
#define RES_CREATED                         0x21
#define RES_ACCEPTED                        0x22
#define RES_NON_AUTHORITATIVE_INFORMATION   0x23
#define RES_NO_CONTENT                      0x24
#define RES_RESET_CONTENT                   0x25
#define RES_PARTIAL_CONTENT                 0x26
#define RES_MULTIPLE_CHOICES                0x30
#define RES_MOVED_PERMANENTLY               0x31
#define RES_MOVED_TEMPORARILY               0x32
#define RES_SEE_OTHER                       0x33
#define RES_NOT_MODIFIED                    0x34
#define RES_USE_PROXY                       0x35
#define RES_TEMPORARY_REDIRECT              0x37
#define RES_BAD_REGUEST                     0x40
#define RES_UNAUTHORIZED                    0x41
#define RES_PAYMENT_REQUIRED                0x42
#define RES_FORBIDDEN                       0x43
#define RES_NOT_FOUND                       0x44
#define RES_METHOD_NOT_ALLOWED              0x45
#define RES_NOT_ACCEPTABLE                  0x46
#define RES_PROXY_AUTHENTICATION_REQUIRED   0x47
#define RES_REQUEST_TIMEOUT                 0x48
#define RES_CONFLICT                        0x49
#define RES_GONE                            0x4A
#define RES_LENGTH_REQUIRED                 0x4B
#define RES_PRECONDITION_FAILED             0x4C
#define RES_REQUEST_ENTITY_TOO_LARGE        0x4D
#define RES_REQUEST_URI_TOO_LARGE           0x4E
#define RES_UNSUPPORTED_MEDIA_TYPE          0x4F
#define RES_REQUESTED_RANGE_NOT_SATISFIABLE 0x50
#define RES_EXPECTATION_FAILED              0x51
#define RES_INTERNAL_SERVER_ERROR           0x60
#define RES_NOT_IMPLEMENTED                 0x61
#define RES_BAD_GATEWAY                     0x62
#define RES_SERVICE_UNAVAILABLE             0x63
#define RES_GATEWAY_TIMEOUT                 0x64
#define RES_HTTP_VERSION_NOT_SUPPORTED      0x65

#define WSP_SkipBlank(p,len) if(0x20==*p)  len=1;else len=0

#define WSP_FormatHdrValue(pbuf,num,pdes,error) \
do{ int32_t v_plen,v_off;               \
    WSP_SkipBlank(pbuf, v_off);         \
    v_plen=CRTL_strlen(pbuf)+1-v_off;            \
    pdes=(int8_t *)OS_MALLOC(v_plen);         \
    if(NULL != pdes){                           \
        CRTL_strcpy(pdes,pbuf+v_off);            \
        for(v_off=0,num=0;v_off < v_plen;v_off++){\
            if(','==pdes[v_off]){           \
                pdes[v_off]='\0';           \
                num++;                      \
            }                               \
        }                                   \
        num++;                              \
    }else{error=HDR_ERROR;}     \
}while(0)

/** To save HTTP header */
typedef struct T_HEADER_ResultStr{
    uint8_t *name;          /* Header name */
    uint8_t *value;         /* Header value */
    uint32_t length;        /* Length of header name and header value */
    struct T_HEADER_ResultStr *next;/*next element*/
     /*name buffer.we will malloc this buffer at same time when we call fnWSP_ResultosInit.
    so the T_HEADER_ResultStr structure must be 4 byte aligned*/
    /*value buffer.we will malloc this buffer at same time when we call fnWSP_ResultosInit
    so the T_HEADER_ResultStr structure must be 4 byte aligned*/

}T_HEADER_ResultStr;

/**
 * Return a the string length(including length of '\0') which the pointer buf point to.
 *
 *   \param  buf    the buffer pointer.
 *   \param  len   buffer length.
 *   \return return the length of the string if success,else return HDR_ERROR;
 */
 int32_t fnHeader_strlenN(int8_t *buf,int32_t len);

/**
 * Get Parameter Values' length.
 *
 *   \param   pPdu the pointer to the PDU packet to parse.
 *   \param   len the length of the HTTP header.
 *   \return return the length of the parameter values' length .
 *           including the size of the end-string char.
 */
 int32_t GetParaValueLength(uint8_t *pPdu,uint32_t len);

/**
 * Set encoding version.
 *
 *   \param  hc  a wsp instance handle.
 *   \param   ver encoding version.for example,if encoding version
 *                           is 1.2, you should set ver to 2.
 *   \return  Return a pointer to the new created T_HEADER_ResultStr.
 */
 int32_t fnWSP_SetEncodingVersion(int8_t ver);

/**
 * The function may implement  to initialize the struct T_HEADER_ResultStr.
 *
 *   \param  name_len the length of the header's name.
 *   \param  value_len the length of the header's value.
 *   \return  Return a pointer to the new created T_HEADER_ResultStr.
 */
 T_HEADER_ResultStr *fnWSP_ResultosInit(int32_t name_len,int32_t value_len);

/**
 * The function may implement  to destroy the struct T_HEADER_ResultStr.
 *
 *   \param  os  T_HEADER_ResultStr stucture to destroy.
 *   \return  Return 0.
 */
 int32_t fnWSP_ResultosExit(T_HEADER_ResultStr *os);

/**
 * Destroy header list.
 *
 *   \param  os a header list header pointer.
 *   \return  Return 0.
 */
 int32_t fnWSP_DestroyHeader(T_HEADER_ResultStr * os);

/**
 * Encode URL.
 *
 *   \param  url  a URL pointer.
 *   \return  If no error occur,return 0,else return HDR_ERROR.
 */
 int16_t fnWSP_EncodeUrl(int8_t *url);

/**
 * Encode HTTP Header.
 *
 *   \param  ost the HTTP header to encode.
 *   \param  len the length of the HTTP header.
 *   \return Return a pointer to the encoded HTTP header.
 */
 T_HEADER_ResultStr *fnWSP_EncodeHttpHeader(int8_t *ost[],int32_t len,int32_t uaprof);

 /**
 * Convert a WSP reponse status to the HTTP status.
 *
 *   \param  status  WSP response status.
 *   \return  Return the HTTP status if success;Otherwise return WSP_RES_STAT_RESERVED.
 */
 int32_t fnWSP_WapStatus2HTTP(int32_t status);

 /**
 * Decode HTTP header.
 *
 *   \param  pPdu the pointer to the PDU packet to parse.
 *   \param  pduLen the length of the HTTP header.
 *   \param  resp    the output response structure.
 *   \param  auth    the output authenticate tag.
 *   \return Return a pointer to the decoded header.
 */
 T_HEADER_ResultStr * fnWSP_DecodeHttpHeader(uint8_t *pPdu,uint32_t pduLen,T_DLM_ResHeader *resp,int32_t *auth);

 /**
 * Query the value of the specified header.
 *
 *   \param  hc  a wsp instance handle.
 *   \param  ost the HTTP header to encode.
 *   \param  format  result value format.if format is 0,return header value in text format.
 *   else return header's value in bin format.defaut value is 0.
 *   \return  Return a pointer to the T_HEADER_ResultStr.
 */
 T_HEADER_ResultStr * fnWSP_QueryHeader(T_HEADER_ResultStr * os,int8_t * str,int32_t format);

 #ifdef __cplusplus
 }
 #endif

 #endif /* __WSP_HEADER_H__ */

