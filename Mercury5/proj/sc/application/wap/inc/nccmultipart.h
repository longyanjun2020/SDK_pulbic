
/**
 * @file
 * Multipart Service Layer
 *
 * Service API and structure exposed by the Multipart.
 *
 * <!-- #interface list begin -->
 * \section nccmultipart_api Interface
 * - NCCMultipart_initBody()
 * - NCCMultipart_initPart()
 * - NCCMultipart_addHeadField()
 * - NCCMultipart_addExtraHeadField()
 * - NCCMultipart_addContent()
 * - NCCMultipart_addBodyPart()
 * - NCCMultipart_pack()
 * - NCCMultipart_clean()
 * - NCCMultipart_unpack()
 * - NCCMultipart_getPartNum()
 * - NCCMultipart_getPartByIndex()
 * - NCCMultipart_parseParam()
 * - NCCMultipart_freeParamList()
 * - NCCMultipart_freeMulBuffer()
 * - NCCMultipart_isNestedPart()
 * - NCCMultipart_unpackNestedPart()
 * <!-- #interface list end -->
 */

#ifndef __NCC_MULTIPART_H__
#define __NCC_MULTIPART_H__

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

#include <ncc_types.h>

/* Multipart header's extra header */
typedef struct ExtraHeader{
    uint8_t *name;
    uint8_t *value;
    uint8_t *param;
    struct ExtraHeader *nextExtraHeader;
}T_Multipart_ExtraHeader;

/* Multipart header structure */
typedef struct Header{
    uint8_t *contentTypeValue;
    uint8_t *contentTypeParam;
    uint8_t *contentTransferEncodingValue;
    uint8_t *contentDispositionValue;
    uint8_t *contentDispositionParam;
    uint8_t *contentIDValue;
    uint8_t *contentDescriptionValue;
    T_Multipart_ExtraHeader  *extraHeader;
}T_Multipart_Header;

/* Multipart body and part structure */
typedef struct BodyOrPart{
    struct BodyOrPart *brotherPart;
    struct BodyOrPart *childPart;
    T_Multipart_Header *header;
    int8_t *boundary;
    uint8_t *content;
    int32_t contentLen;
    int32_t number;
    int8_t contentFlag;
}T_Multipart_BodyOrPart;

/* Multipart parameter structure */
typedef struct Parameter{
    uint8_t *name;
    uint8_t *value;
    struct Parameter *next;
}T_Multipart_Parameter;

/* Multipart output buffer */
typedef struct mul_buffer{
    uint8_t *buffer;
    int32_t bufferLen;
    int32_t freeLen;
}T_Multipart_Buffer;

typedef enum _multipart_format_type{
    MULTIPART_ENCODE = 1,
    MULTIPART_TEXT
}T_MULTIPART_FORMAT_TYPE;

typedef enum MULTIPART_TYPES {
        MULTIPART_BEGIN,
        MULTIPART_FORM_DATA = MULTIPART_BEGIN,      /* default */
        MULTIPART_MIXED,
        MULTIPART_RELATED,
        MULTIPART_ALTERNATIVE,
        MULTIPART_PARALLEL,
        MULTIPART_DIGEST,           /* for message/rfc822 only */
        MULTIPART_APP_MIXED,
        MULTIPART_APP_RELATED,
        MULTIPART_APP_ALTERNATIVE,
        MULTIPART_END = MULTIPART_APP_ALTERNATIVE
}T_MULTIPART_TYPES;

typedef enum HEADER_TYPES{
        HEADER_BEGIN,
        HEADER_CONTENT_TYPE = HEADER_BEGIN,
        HEADER_CONTENT_TRANSFER_ENCODING,
        HEADER_CONTENT_DISPOSITION,
        HEADER_CONTENT_DESCRIPTION,
        HEADER_CONTENT_ID,
        HEADER_END = HEADER_CONTENT_ID
}T_MULTIPART_HEADER_TYPES;

typedef enum HEADER_PARAM_TYPES{
        HEADER_PARAM_BEGIN = 1,
        HEADER_PARAM_CHARSET = HEADER_PARAM_BEGIN,
        HEADER_PARAM_BOUNDARY,
        HEADER_PARAM_TYPE,
        HEADER_PARAM_START,
        HEADER_PARAM_START_INFO,
        HEADER_PARAM_NAME,
        HEADER_PARAM_END = HEADER_PARAM_NAME
}T_MULTIPART_HEADER_PARAM_TYPES;

typedef enum TRANSFER_ENCODING_TYPES{
        TRANSFER_ENCODING_BEGIN = 1,
        TRANSFER_ENCODING_7BIT = TRANSFER_ENCODING_BEGIN,
        TRANSFER_ENCODING_8BIT,
        TRANSFER_ENCODING_BASE64,
        TRANSFER_ENCODING_QUOTED_PRINTABLE,
        TRANSFER_ENCODING_BINARY,
        TRANSFER_ENCODING_END = TRANSFER_ENCODING_BINARY
}T_MULTIPART_TRANSFER_ENCODING_TYPES;

typedef enum MUL_CONTENT_COPY{
    CONTENT_UNCOPY,
    CONTENT_COPY
}T_MULTIPART_CONTENT_COPY;

typedef enum MULTIPART_ERRORS {
        MULTIPART_NO_ERROR,
        MULTIPART_ALLOC_FAIL,
        MULTIPART_OTHER_ERROR
}T_MULTIPART_ERRORS;

/**
 * Create a body structure, it will auto create a boundary.
 * \param multipartType it shows the multipart package's type, now support:
 *        MULTIPART_FORM_DATA,
 *        MULTIPART_MIXED,
 *        MULTIPART_RELATED,
 *        MULTIPART_ALTERNATIVE,
 *        MULTIPART_PARALLEL,
 *        MULTIPART_DIGEST,
 *        MULTIPART_APP_MIXED,
 *        MULTIPART_APP_RELATED,
 *        MULTIPART_APP_ALTERNATIVE
 * \return
 *      -a pointer of T_Multipart_BodyOrPart when success
 *      -NULL when fail
 */
T_Multipart_BodyOrPart *NCCMultipart_initBody(T_MULTIPART_TYPES multipartType);

/**
 * Create a part structure.
 * \return
 *      -a pointer of T_Multipart_BodyOrPart when success
 *      -NULL when fail
 */
T_Multipart_BodyOrPart *NCCMultipart_initPart(void);

/**
 * Create a header of a part or a body and add content in it.
 * \param pbp a pointer of a part or a body
 * \param fieldType header field type, now support:
 *        HEADER_CONTENT_TYPE,
 *        HEADER_CONTENT_TRANSFER_ENCODING,
 *        HEADER_CONTENT_DISPOSITION,
 *        HEADER_CONTENT_DESCRIPTION,
 *        HEADER_CONTENT_ID
 * \param fieldValue value of header field, for example, if you want to add
 *        "Content-Type:multipart/mixed", you can use
 *        "NCCMultipart_addHeadField(pbp, HEADER_CONTENT_TYPE, "multipart/mixed", 0, NULL);"
 * \param fieldParamType type of header field's parameter, now support:
 *        HEADER_PARAM_CHARSET,
 *        HEADER_PARAM_BOUNDARY,
 *        HEADER_PARAM_TYPE,
 *        HEADER_PARAM_START,
 *        HEADER_PARAM_START_INFO,
 *        HEADER_PARAM_NAME
 * \param fieldParamValue value of header field's parameter, for example:
 *        1.if you want to add parameter "Charset=utf-8" to Content-Type, you can use:
 *        "NCCMultipart_addHeadField(pbp, HEADER_CONTENT_TYPE, NULL, HEADER_PARAM_CHARSET, "Charset=utf-8");"
 *        2.if you want to add parameter "Charset=utf-8; Start=<AAAA>", you can use:
 *        "NCCMultipart_addHeadField(pbp, HEADER_CONTENT_TYPE, NULL, 0, "Charset=utf-8; Start=<AAAA>");"
 *        or
 *        "NCCMultipart_addHeadField(pbp, HEADER_CONTENT_TYPE, NULL, HEADER_PARAM_CHARSET, "Charset=utf-8");"
 *        "NCCMultipart_addHeadField(pbp, HEADER_CONTENT_TYPE, NULL, HEADER_PARAM_START, "Start=<AAAA>");"
 *        3.But, HEADER_PARAM_BOUNDARY is especial, if you want to add boundary please use:
 *        "NCCMultipart_addHeadField(pbp, HEADER_CONTENT_TYPE, NULL, HEADER_PARAM_BOUNDARY, "-=next_0000.example");"
 *        not
 *        "NCCMultipart_addHeadField(pbp, HEADER_CONTENT_TYPE, NULL, HEADER_PARAM_BOUNDARY, "boundary=-=next_0000.example");"
 *        and do not use it like this
 *        "NCCMultipart_addHeadField(pbp, HEADER_CONTENT_TYPE, NULL, HEADER_PARAM_BOUNDARY,
 *                                    "boundary=-=next_0000.example;Start=<AAAA>");"
 *        Actually, the fieldParamType is not necessary(except HEADER_PARAM_BOUNDARY), it's just kept to extend this
 *        method's function in the future, such as to judge validity of the added parameter.
 * \return
 *      -TRUE when add successfully
 *      -FALSE when fail
 */
int32_t NCCMultipart_addHeadField(T_Multipart_BodyOrPart *pbp,
                          T_MULTIPART_HEADER_TYPES fieldType,
                          int8_t *fieldValue,
                          T_MULTIPART_HEADER_PARAM_TYPES fieldParamType,
                          int8_t *fieldParamValue);

/**
 * Add extra header to a part or a body
 * \param pbp pointer of a part or a body
 * \param value extra content, for example:
 *        if you want to add "Content-Location:location; Start=<AAAA>\r\nX-Application:exe", use:
 *        "NCCMultipart_addExtraHeadField(pbp, "Content-Location:location; Start=<AAAA>\r\nX-Application:exe")"
 *        or
 *        "NCCMultipart_addExtraHeadField(pbp, "Content-Location:location; Start=<AAAA>")"
 *        "NCCMultipart_addExtraHeadField(pbp, "X-Application:exe")"
 * \return
 *      -TRUE when add successfully
 *      -FALSE when fail
 */
int32_t NCCMultipart_addExtraHeadField(T_Multipart_BodyOrPart *pbp, int8_t *value);

/**
 * Add data content to a part.
 * \param pbp pointer of a part
 * \param pContent pointer of the data content, please pay more attention, before pack successfully, do not
 *        free this pointer, because this method will not copy data!
 * \param contentLen length of the content
 * \param codingType coding type, now support:
 *                                      TRANSFER_ENCODING_7BIT ,
 *                                      TRANSFER_ENCODING_8BIT,
 *                                      TRANSFER_ENCODING_BASE64,
 *                                      TRANSFER_ENCODING_QUOTED_PRINTABLE,
 *                                      TRANSFER_ENCODING_BINARY
 *        if codingType is TRANSFER_ENCODING_BINARY means do not decode the data.
 * \param copyFlag CONTENT_UNCOPY : do not copy the pContent; CONTENT_COPY : copy pContent
 *        Note: if the codingType is TRANSFER_ENCODING_7BIT or TRANSFER_ENCODING_BASE64
 *              or TRANSFER_ENCODING_QUOTED_PRINTABLE, the pContent will always be copied.
 * \return
 *      -TRUE when add successfully
 *      -FALSE when fail
 */
int32_t NCCMultipart_addContent(T_Multipart_BodyOrPart *pbp,
                                 uint8_t *pContent,
                                 uint32_t contentLen,
                                 T_MULTIPART_TRANSFER_ENCODING_TYPES codingType,
                                 T_MULTIPART_CONTENT_COPY copyFlag);

/**
 * Add a part or a body to a body.
 * \param pBody pointer of body
 * \param pbp pointer of a part or a body which will be inserted to a body
 * \param index inserting position, index must >= 1
 * \return
 *      -TRUE when insert successfully
 *      -FALSE when fail
 */
int32_t NCCMultipart_addBodyPart(T_Multipart_BodyOrPart *pBody, T_Multipart_BodyOrPart *pbp, int32_t index);

/**
 * Collect all data and pack into a multipart package.
 * \param pBody pointer of the first body in multipart link
 * \param packType pack type: MULTIPART_ENCODE : encoding format; MULTIPART_TEXT : plaintext format
 * \return
 *      -pointer of T_Multipart_Buffer structure when success
 *      -NULL when fail
 */
T_Multipart_Buffer *NCCMultipart_pack(T_Multipart_BodyOrPart *pBody, T_MULTIPART_FORMAT_TYPE packType);

/**
 * Clean up the multipart link.
 * \param pBody pointer of the first body in multipart link.
 * \return
 *      -TRUE when clean successfully
 *      -FALSE when fail
 */
int32_t  NCCMultipart_clean(T_Multipart_BodyOrPart *pBody);

/**
 * Unpack the multipart package.
 * \param pData              the data to parse
 * \param dataLen            length of data
 * \param unpackType unpack type: MULTIPART_ENCODE : encoding format; MULTIPART_TEXT : plaintext format
 * \return
 *       -a structure which contain all the result of the data
 *       -NULL, when failed
 */
T_Multipart_BodyOrPart * NCCMultipart_unpack(uint8_t * pData, int32_t dataLen, T_MULTIPART_FORMAT_TYPE unpackType);

/**
 * Get the part number of a body.
 * \param pBody pointer of the body
 * \return
 *      -part number when success
 *      --1 when fail
 */
int32_t NCCMultipart_getPartNum(T_Multipart_BodyOrPart * pBody);

/**
 * Get a specific part of a body.
 * \param pBody pointer of the body
 * \param index show part's index
 * \return
 *      -pointer of the part when success
 *      -NULL when fail
 */
T_Multipart_BodyOrPart * NCCMultipart_getPartByIndex(T_Multipart_BodyOrPart * pBody, int32_t index);

/**
 * Parse parameters, include text plain format and encode format.
 * \param param string of the parameter
 * \param paramType parameter type: MULTIPART_ENCODE : encoding format; MULTIPART_TEXT : plaintext format
 * \return
 *      -a structure which contain all the result of the data and length
 *      -NULL, when failed
 */
T_Multipart_Parameter * NCCMultipart_parseParam(uint8_t * param, T_MULTIPART_FORMAT_TYPE paramType);

/**
 * Free param structure list
 * \param pParamHeader the header pointer of the parameter structure
 * \return
 *      -void
 */
void NCCMultipart_freeParamList(T_Multipart_Parameter * pParamHeader);

/**
 * Free T_Multipart_Buffer structure.
 * \param buffer pointer to pointer of T_Multipart_Buffer structure which will be freed
 * \return
 *      -TRUE when success
 *      -FALSE when fail
 */
int32_t NCCMultipart_freeMulBuffer(T_Multipart_Buffer *buffer);

/**
 * Chech whether a part is a nested part
 * \param pPart A pointer of the part
 * \return
 *      -TRUE when it is a nested part
 *      -FALSE when it is a body or it is not a nested part
 */
int32_t NCCMultipart_isNestedPart(T_Multipart_BodyOrPart *pPart);

/**
 * Unpack the nested part in case of text plain format.
 * \param pPart     A pointer of the part
 * \return
 *      -TRUE when it is a nested part and unpack it successfully.
 *      -FALSE when otherwise.
 */
int32_t NCCMultipart_unpackNestedPart(T_Multipart_BodyOrPart *pPart);

int32_t NCCMultipart_initErrorNum(int32_t num);
int32_t NCCMultipart_getLastErrorNum(void);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* __NCC_MULTIPART_H__ */
