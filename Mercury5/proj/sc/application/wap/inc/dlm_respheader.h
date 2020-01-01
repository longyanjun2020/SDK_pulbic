
#ifndef __DLM_RESPHEADER_H__
#define __DLM_RESPHEADER_H__

///HTTP response header type.
typedef enum {
    DLM_RESP_PTR_CONTENT_TYPE = 0,
    DLM_RESP_PTR_ENCODING_TYPE,
    DLM_RESP_PTR_CHARSET,
    DLM_RESP_PTR_CONTENT_NAME,
    DLM_RESP_PTR_LOCATION,
    DLM_RESP_PTR_ETAG,
    DLM_RESP_PTR_LANGUAGE,
    DLM_RESP_INT_CONTENT_LENGTH,
    DLM_RESP_INT_RETURN_VALUE,
    DLM_RESP_INT_CACHE_EXPIRES,
    DLM_RESP_INT_CACHE_LASTMODIFY,
    DLM_RESP_INT_CACHE_MUST_REVALI_FLAG,
    DLM_RESP_INT_CACHE_AGE,
    DLM_RESP_INT_CACHE_DATE,
    DLM_RESP_INT_CACHE_MAXAGE,
    DLM_RESP_INT_CACHE_NOCACHE,
    DLM_RESP_INT_KEEPALIVE
} DLM_RESP_TYPE;

typedef struct T_DLM_ResponseHeader T_DLM_ResHeader ;

/// HTTP or WSP response header structure.
struct T_DLM_ResponseHeader
{
    int8_t * ContentType;	/**<Content Type*/
    int8_t * EncodingType;	/**<Encoding Type*/
    int8_t * CharSet;		/**<CharSet*/
    int8_t * ContentName;   /**<Content Name*/
    int8_t * Location;		/**<including Content-Location and Location*/
    int8_t * ETag;			/**<ETag*/
    int8_t * Language;		/**<Language*/

    int32_t Status;			/**<HTTP/WSP Status Code */
    int32_t ContentLength;	/**<Content Length*/
    int32_t Age;			/**<for cache control,"Age" header*/
    int32_t Date;			/**<for cache control,"Date" header*/
    int32_t MaxAge;			/**<for cache control,"Cache-control:max-age=xxx" header*/
    int32_t Expires;		/**<for cache control,"Expires" header*/
    int32_t LastModified;	/**<for cache control,"Last-Modified" header*/
    int32_t NoCache;			/**<for cache control,"Cache-control:no-cache" header*/
    int32_t CacheMustRevalidate;/**<for cache control,"Cache-control:must-revalidate" header*/
};

#endif /*__DLM_RESPHEADER_H__*/
