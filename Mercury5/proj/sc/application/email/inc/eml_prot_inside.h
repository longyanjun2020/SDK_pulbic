/**
* @file eml_prot_inside.h
* NCC email protocol internal Layer
*
* Internal API unexposed by the NCC email protocol module
*/
#ifndef __EML_PROT_INSIDE_H__
#define __EML_PROT_INSIDE_H__
#include <nccemail_common.h>
#include <nccport_i18n.h>
#include <nccemail_prot.h>
#include <nccmultipart.h>

#ifdef __cplusplus
extern "C" {
#endif

/** define address type */


typedef enum {
    MONTH_ID_JANUARY,
    MONTH_ID_FEBRUARY,
    MONTH_ID_MARCH,
    MONTH_ID_APRIL,
    MONTH_ID_MAY,
    MONTH_ID_JUNE,
    MONTH_ID_JULY,
    MONTH_ID_AUGUST,
    MONTH_ID_SEPTEMBER,
    MONTH_ID_OCTOBER,
    MONTH_ID_NOVEMBER,
    MONTH_ID_DECEMBER
} MONTH_NAME_ID;

/** encode result */
#define EMAIL_ENCODE_SUCCESS        0
#define EMAIL_ENCODE_FAILED         -1

/** email system macros */
#define EMAIL_MAXATTACHMENTNO			5	//the maximum of attachment
#define EMAIL_MAXSUBJECTLENGTH		1000//the maximum length of the subject
#define EMAIL_DATETIMELENGTH			31	//the length of the time string
#define EMAIL_MAXSENDERLENGTH			50	//the maximum of address
#define EMAIL_MAXADDRESSEELENGTH		500	//the maximum length of all address
#define EMAIL_MAXRECEIVEDMAILSIZE		(30*1024)//the maximum of received email size
//#define EMAIL_CPS_HEADER_LENGTH 360

// /** esmtp header */
// #define EMAIL_CPS_HEADER_EHLO "EHLO mobilephone\r\n\0"
// #define EMAIL_CPS_HEADER_AUTH "AUTH LOGIN\r\n\0"
// #define EMAIL_CPS_HEADER_MAILFROM_BEGIN "MAIL FROM: <"
// #define EMAIL_CPS_HEADER_MAILFROM_END ">\r\n\0"
// #define EMAIL_CPS_HEADER_RCPTTO_BEGIN "RCPT TO: <"
// #define EMAIL_CPS_HEADER_RCPTTO_END ">\r\n\0"
// #define EMAIL_CPS_HEADER_DATA "DATA\r\n\0"
// #define EMAIL_CPS_HEADER_QUIT "QUIT\r\n\0"

// #define EMAIL_CPS_HEADER_DATE "Date: "
// #define EMAIL_CPS_HEADER_FROM_FORMAT_STR "From: %s"
// #define EMAIL_CPS_HEADER_TO "To: "
// #define EMAIL_CPS_HEADER_CC "Cc: "
// #define EMAIL_CPS_HEADER_BCC "Bcc: "
// #define EMAIL_CPS_HEADER_REPLY "Reply-To: "
// #define EMAIL_CPS_HEADER_SUBJECT "Subject: "
// #define EMAIL_CPS_HEADER_MIME "MIME-Version: 1.0\r\n\0"
// //#define EMAIL_CPS_HEADER_BOUNDARAY "\tboundary=\"=====mstarsemi.com=====\"\r\n\0"
// #define EMAIL_CPS_HEADER_BOUNDARAY "\tboundary=\""
// #define EMAIL_CPS_HEADER_CORPORATION "=====mstarsemi.com====="
// #define EMAIL_CPS_HEADER_BOUNDARAY_END "\"\r\n\0"
// #define EMAIL_CPS_HEADER_CHARSET "\tcharset=\"" //gb2312\"\r\n\0"
// #define EMAIL_CPS_HEADER_CHARSET_END "\"\r\n\0"
// #define EMAIL_CPS_HEADER_ENCODE "Content-Transfer-Encoding: base64\r\n\0"
// #define EMAIL_CPS_HEADER_ATTACH "Content-Disposition: attachment;\r\n\0"
// #define EMAIL_CPS_HEADER_CONTENTTYPE "Content-Type: "
// #define EMAIL_CPS_HEADER_CONTENT_TEXT "Content-Type: text/plain;\r\n\0"
// #define EMAIL_CPS_HEADER_CONTENT_MIXED "Content-Type: multipart/mixed;\r\n\0"

#define EMAIL_CPS_HEADER_CONTENT_TYPE_MULTIPART_MIXED   "multipart/mixed"
#define EMAIL_CPS_HEADER_CONTENT_TYPE_MULTIPART_ALTERNATIVE   "multipart/alternative"
#define EMAIL_CPS_HEADER_CONTENT_TYPE_TEXT_PLAIN "text/plain"
#define EMAIL_CPS_HEADER_CONTENT_TYPE_TEXT_HTML "text/html"
#define EMAIL_CPS_HEADER_CONTENT_TYPE_MESSAGE_RFC822 "message/rfc822"

#define EMAIL_CPS_MIMETYPE_TEXT_PLAIN "text/plain"
#define EMAIL_CPS_MIMETYPE_TEXT_PLAIN_EXT ".txt"
#define EMAIL_CPS_MIMETYPE_IMAGE_GIF "image/gif"
#define EMAIL_CPS_MIMETYPE_IMAGE_GIF_EXT ".gif"
#define EMAIL_CPS_MIMETYPE_IMAGE_JPEG "image/jpeg"
#define EMAIL_CPS_MIMETYPE_IMAGE_JPEG_EXT ".jpeg"
#define EMAIL_CPS_MIMETYPE_IMAGE_WBMP "image/vnd.wap.wbmp"
#define EMAIL_CPS_MIMETYPE_IMAGE_WBMP_EXT ".wbmp"
#define EMAIL_CPS_MIMETYPE_IMAGE_PNG "image/png"
#define EMAIL_CPS_MIMETYPE_IMAGE_PNG_EXT ".png"
#define EMAIL_CPS_MIMETYPE_IMAGE_BMP "image/bmp"
#define EMAIL_CPS_MIMETYPE_IMAGE_BMP_EXT ".bmp"
#define EMAIL_CPS_MIMETYPE_AUDIO_AMR "audio/amr"
#define EMAIL_CPS_MIMETYPE_AUDIO_AMR_EXT ".amr"
#define EMAIL_CPS_MIMETYPE_AUDIO_QCP "audio/vnd.qcelp"
#define EMAIL_CPS_MIMETYPE_AUDIO_QCP_EXT ".qcp"
#define EMAIL_CPS_MIMETYPE_AUDIO_3GPP "audio/3gpp"
#define EMAIL_CPS_MIMETYPE_AUDIO_3GPP_EXT ".3gp"
#define EMAIL_CPS_MIMETYPE_AUDIO_3GPP2 "audio/3gpp2"
#define EMAIL_CPS_MIMETYPE_AUDIO_3GPP2_EXT ".3g2"
#define EMAIL_CPS_MIMETYPE_AUDIO_MID "audio/mid"
#define EMAIL_CPS_MIMETYPE_AUDIO_MID_EXT ".mid"
#define EMAIL_CPS_MIMETYPE_AUDIO_MIDI "audio/midi"
#define EMAIL_CPS_MIMETYPE_AUDIO_MIDI_EXT ".midi"
#define EMAIL_CPS_MIMETYPE_AUDIO_X_MIDI "audio/x-midi"
#define EMAIL_CPS_MIMETYPE_AUDIO_SP_MIDI "audio/sp-midi"
#define EMAIL_CPS_MIMETYPE_AUDIO_WAV "audio/wav"
#define EMAIL_CPS_MIMETYPE_AUDIO_WAV_EXT ".wav"
#define EMAIL_CPS_MIMETYPE_AUDIO_XWAV "audio/x-wav"
#define EMAIL_CPS_MIMETYPE_AUDIO_IMELODY "audio/imelody"
#define EMAIL_CPS_MIMETYPE_AUDIO_IMELODY_EXT ".imy"
#define EMAIL_CPS_MIMETYPE_AUDIO_MP3 "audio/mp3"
#define EMAIL_CPS_MIMETYPE_AUDIO_MP3_EXT ".mp3"
#define EMAIL_CPS_MIMETYPE_AUDIO_MP4 "audio/mp4"
#define EMAIL_CPS_MIMETYPE_AUDIO_MP4_EXT ".mp4"
#define EMAIL_CPS_MIMETYPE_AUDIO_MPEG "audio/mpeg"
#define EMAIL_CPS_MIMETYPE_AUDIO_MPEG_EXT ".mpeg"
#define EMAIL_CPS_MIMETYPE_AUDIO_X_M4A "audio/x-m4a"
#define EMAIL_CPS_MIMETYPE_AUDIO_X_M4A_EXT ".m4a"
#define EMAIL_CPS_MIMETYPE_AUDIO_X_M4P "audio/x-m4p"
#define EMAIL_CPS_MIMETYPE_AUDIO_X_M4P_EXT ".m4p"
#define EMAIL_CPS_MIMETYPE_AUDIO_X_M4B "audio/x-m4b"
#define EMAIL_CPS_MIMETYPE_AUDIO_X_M4B_EXT ".m4b"
#define EMAIL_CPS_MIMETYPE_AUDIO_AAC "audio/aac"
#define EMAIL_CPS_MIMETYPE_AUDIO_AAC_EXT ".aac"
#define EMAIL_CPS_MIMETYPE_AUDIO_X_AAC "audio/x-aac"
#define EMAIL_CPS_MIMETYPE_VIDEO_3GP "video/3gpp"
#define EMAIL_CPS_MIMETYPE_VIDEO_3GP_EXT ".3gp"
#define EMAIL_CPS_MIMETYPE_VIDEO_3GPP2 "video/3gpp2"
#define EMAIL_CPS_MIMETYPE_VIDEO_3GPP2_EXT ".3g2"
#define EMAIL_CPS_MIMETYPE_VIDEO_MPEG "video/mpeg"
#define EMAIL_CPS_MIMETYPE_VIDEO_MPEG_EXT ".mpeg"
#define EMAIL_CPS_MIMETYPE_VIDEO_MP4 "video/mp4"
#define EMAIL_CPS_MIMETYPE_VIDEO_MP4_EXT ".mp4"
#define EMAIL_CPS_MIMETYPE_TEXT_CALENDAR "text/x-vCalendar"
#define EMAIL_CPS_MIMETYPE_TEXT_CALENDAR_EXT ".vcs"
#define EMAIL_CPS_MIMETYPE_TEXT_VCARD "text/x-vCard"
#define EMAIL_CPS_MIMETYPE_TEXT_VCARD_EXT ".vcf"
#define EMAIL_CPS_MIMETYPE_DRM_FORWADLOCK "application/vnd.oma.drm.message"
#define EMAIL_CPS_MIMETYPE_DRM_FORWADLOCK_EXT ".dm"
#define EMAIL_CPS_MIMETYPE_DRM_DCF "application/vnd.oma.drm.content"
#define EMAIL_CPS_MIMETYPE_DRM_DCF_EXT ".dcf"

// #define EMAIL_CPS_HEADER_CONTENTTYPE_MIXED "multipart/mixed;"

// #define EMAIL_CPS_HEADER_NAME "\tname=\""
// #define EMAIL_CPS_HEADER_NAME_END "\"\r\n\0"
// #define EMAIL_CPS_HEADER_FILENAME "\tfilename=\""
// #define EMAIL_CPS_HEADER_FILENAME_END "\"\r\n\r\n\0"
// #define EMAIL_CPS_HEADER_PRIORITY "X-Priority: "
// #define EMAIL_CPS_HEADER_MAIL_PRIORITY "X-Mail-Priority: "
// #define EMAIL_CPS_HEADER_MAIL_PRIORITY_HIGH "High"
// #define EMAIL_CPS_HEADER_MAIL_PRIORITY_NORMAL "Normal"
// #define EMAIL_CPS_HEADER_MAIL_PRIORITY_LOW "Low"
// #define EMAIL_CPS_HEADER_MAILER "X-Mailer: mstar mailer\r\n\0"
// #define EMAIL_CPS_HEADER_MIMEOLE "X-MimeOLE: Produced By MimeOLE V5.50.4522.1200\r\n\0"
// #define EMAIL_CPS_DEFAULT_ATTACHTYPE "application/octet-stream"

#define EMAIL_CPS_ENDLINE    "\r\n"
#define EMAIL_CPS_ENDLINE_LEN   2
#define EMAIL_CPS_ENDLINE2    "\n"
#define EMAIL_CPS_ENDLINE2_LEN   1

//#define EMAIL_CPS_HEADER_ENDLINE "\r\n"
//#define EMAIL_CPS_HEADER_ENDMAIL "\r\n.\r\n\0"

#define EMAIL_CPS_LINE_FOLDING_HTAB         "\r\n\t"
#define EMAIL_CPS_LINE_FOLDING_HTAB2         "\n\t"
#define EMAIL_CPS_LINE_FOLDING_WHITE_SPACE  "\r\n "
#define EMAIL_CPS_LINE_FOLDING_WHITE_SPACE2  "\n "
#define EMAIL_CPS_HEADER_BODY_SEPARATOR     "\r\n\r\n"
#define EMAIL_CPS_HEADER_BODY_SEPARATOR2     "\n\n"
#define EMAIL_CPS_HEADER_BODY_SEPARATOR_LEN 4
#define EMAIL_CPS_HEADER_BODY_SEPARATOR_LEN2 2
#define EMAIL_CPS_ADDRESS_LIST_SEPARATOR    ','

#define EMAIL_CPS_LEFT_ANGLE_BRACKETS       '<'
#define EMAIL_CPS_RIGHT_ANGLE_BRACKETS       '>'

#define EMAIL_CHARSET_NAME_STR_STR_MAX_LEN       16
#define EMAIL_CPS_COLON_SEPARATOR       ":"
#define EMAIL_CPS_RESPONSE_BUFFERLEN  512
#define EMAIL_CPS_REQUEST_BUFFERLEN   128
#define EMAIL_CPS_DATA_BUFFERLEN_EXTN 360
#define EMAIL_CPS_MAX_TIMEOUT 400

#define EMAIL_CONTENT_TRANSFER_ENCODING_7BIT                "7bit"
#define EMAIL_CONTENT_TRANSFER_ENCODING_8BIT                "8bit"
#define EMAIL_CONTENT_TRANSFER_ENCODING_BINARY              "binary"
#define EMAIL_CONTENT_TRANSFER_ENCODING_QUOTED_PRINTABLE    "quoted-printable"
#define EMAIL_CONTENT_TRANSFER_ENCODING_BASE64              "base64"

#define EMAIL_TEXT_HTML_FORMAT_STR          "<html>\r\n<head>\r\n</head>\r\n<body>\r\n%s</body>\r\n</html>"
#define EMAIL_TEXT_HTML_FORMAT_STR_LEN      49  // CRTL_strlen(EMAIL_TEXT_HTML_FORMAT_STR)

typedef enum {
    EMAIL_CONTENT_TRANSFER_ENCODING_TYPE_7BIT,
    EMAIL_CONTENT_TRANSFER_ENCODING_TYPE_8BIT,
    EMAIL_CONTENT_TRANSFER_ENCODING_TYPE_BASE64,
    EMAIL_CONTENT_TRANSFER_ENCODING_TYPE_BINARY,
    EMAIL_CONTENT_TRANSFER_ENCODING_TYPE_QUOTED_PRINTABLE,
    EMAIL_CONTENT_TRANSFER_ENCODING_TYPE_UNSUPPORT
} EMAIL_CONTENT_TRANSFER_ENCODING_TYPE;

#define EMAIL_CPS_DATE_STR_MAX_LEN      20 // YYYY-MM-DD HH:MM:SS

typedef struct _EMAIL_CONTENT {
    int8_t * contentType;
    int8_t * charset;
    int8_t * name;
    int8_t * encoding;
    int8_t * disposition;
    int8_t * filename;
    int32_t nameLen;
    int32_t filenameLen;
    int8_t * buffer;
    int32_t bufferlen;
    int8_t * buffer_plain;
    int32_t bufferlen_plain;
    struct _EMAIL_CONTENT *next;
}T_EMAIL_CONTENT;

typedef struct _T_EMAIL_Data {
    int8_t *pData;
    int32_t dataLen;
} T_EMAIL_Data;

typedef struct _T_EMAIL_ContentType {
    int8_t *pValue;
    int8_t *pParams;
} T_EMAIL_ContentType;

/** email handle struct */
typedef struct T_EMAIL_HANDLE {

    ///< Originator fields
    T_EMAIL_MailBox_List From;      // "From:" mailbox CRLF
    T_EMAIL_MailBox_List Sender;    // "Sender:" mailbox CRLF
    T_EMAIL_MailBox_List ReplyTo;   // "Reply-To:" address-list CRLF

    int32_t origDate;

    ///< Destination address fields
    T_EMAIL_MailBox_List To;
    T_EMAIL_MailBox_List Cc;
    T_EMAIL_MailBox_List Bcc;

    ///< Identification fields
    /**
         * The message identifier (msg-id) is similar in syntax to an angle-addr
         * construct without the internal CFWS.
         */
    T_EMAIL_Data MsgID;        ///<message-id = "Message-ID:" msg-id CRLF
    T_EMAIL_Data Reference;    ///<references = "References:" 1*msg-id CRLF
    T_EMAIL_Data InReplyTo;    ///in-reply-to = "In-Reply-To:" 1*msg-id CRLF

    ///<    Informational fields
    T_EMAIL_Data Subject;
    T_EMAIL_Data Comments;
    T_EMAIL_Data Keywords;

    ///<Resent fields
    T_EMAIL_MailBox_List ResentFrom;
    T_EMAIL_MailBox_List ResentSender;
    T_EMAIL_MailBox_List ResentTo;
    T_EMAIL_MailBox_List ResentCc;
    T_EMAIL_MailBox_List ResentBcc;
    T_EMAIL_Data ResentMsgID;
    int32_t ResentDate;// 

    //TODO: here should define a struct  T_EMAIL_Trace
    /**
        * typedef struct _T_EMAIL_Trace {
            Return-Path;
            Received;
        }
        */
    T_EMAIL_ContentType contentType; // Content-Type header

    T_EMAIL_Data contentTransferEncoding; // Content-Transfer-Encoding

    T_EMAIL_Data contentDisposition; // Content-Disposition

    EMAIL_PRIORITY Priority;
    T_EMAIL_Data textContent; // Content-Type: text/plain
    T_EMAIL_Data htmlContent; // Content-Type: text/html
    T_EMAIL_Data autoSign;

    T_EMAIL_Attachment_List Attachment;
}T_EMAIL_HANDLE;

/**
 * Declare function pointer for encode function
 */
typedef int32_t (*PEncodedFunc) (EMAIL_HANDLE EmailHandle, T_Multipart_BodyOrPart *pMultipart);

/**
 * Get the ID of field header by name
 *
 * \param pName [in]
 *          The name string of field
 *
 * \param nameLen [in]
 *          The length of field namef
 *
 * \return
 *  <ul>
 *      <li>#EMAIL_FIELD_TYPE, if found
 *      <li>#EMAIL_FIELD_TYPE::EMAIL_FIELD_TYPE_UNKNOWN, if not found
 *  </ul>
 */
int32_t cps_getFieldIDByFieldNameStr(const int8_t *pName, const uint32_t nameLen);

/**
 * Get the buffer and buffer length of email header and body
 *
 * \param pData [in]
 *          The email buffer contains header and body
 *
 * \param dataLen [in]
 *          The length of pData
 *
 * \param ppHeader [out]
 *          The pointer which point to the first byte of email header
 *
 * \param pHeaderLen [out]
 *          The length of email header
 *
 * \param ppBody [out]
 *          The pointer which point to the first byte of email body
 *
 * \param pBodyLen [out]
 *          The length of email body
 *
 * \return
 *      <ul>
 *          <li>#EMAIL_CPS_SUCCESS, if succeed
 *          <li>#EMAIL_CPS_PARAMETER_ERROR, if invalid parameter
 *          <li>#EMAIL_CPS_FAILED, invalid email pdu
 *      </ul>
 */
int32_t cps_getHeaderAndBodyPdu(const int8_t *pData, const int32_t dataLen,
    int8_t **ppHeader, int32_t *pHeaderLen, int8_t **ppBody, int32_t *pBodyLen);

/**
 * Unfolding line for email. Removing any CRLF that is immediately followed by WSP
 *
 * \param pData [in]
 *      The string pointer which point to the email data
 *
 * \param dataLen [in]
 *      The string length of email data
 *
 * \param onlyHeader [in]
 *      if only parse email header
 *
 * \param ppUnfoldingData [out]
 *      The out pointer which point to the unfolding email data
 *
 * \param pUnfoldingDataLen [out]
 *      The length of unfolding data
 *
 * \return
 *      <ul>
 *          <li>#EMAIL_CPS_SUCCESS, if succeed
 *          <li>#EMAIL_CPS_ALLOC_FAIL, if memory leak
 *          <li>#EMAIL_CPS_PARAMETER_ERROR, if invalid input parameter
 *      </ul>
 */
int32_t cps_unfoldingEmail(int8_t *pData, int32_t dataLen, int32_t onlyHeader,
    int8_t **ppUnfoldingData, int32_t *pUnfoldingDataLen);

int32_t checkEmail4Save(EMAIL_HANDLE CPSHandle);

/**
 * Insert new mailbox into the specified field by type
 *
 * \param CPSHandle [in, out]
 *          The structure pointer to save email information
 *
 * \param pAddrContent [in]
 *          The structure pointer to save mailbox infomation
 *
 * \param type [in]
 *          The type of field
 *
 * \return
 *      <ul>
 *          <li>#
 *          <li>#
 *      </ul>
 */
int32_t cps_addMailBoxIntoMailBoxList(EMAIL_HANDLE CPSHandle,
    const T_EMAIL_MailBox *pAddrContent, const EMAIL_FIELD_TYPE type);

/**
 * Parse mailbox list string and add into the mailbox list
 *
 * \param CPSHandle [in, out]
 *              The structure pointer which point to the email content
 *
 * \param pMailBoxListStr [in]
 *              The string pointer which point to the mailbox list string
 *
 * \param mailBoxListStrLen [in]
 *              The length of addrStrLen
 *
 * \param fieldType [in]
 *              The type of field
 *
 * \return
 *      <ul>
 *          <li>#
 *          <li>#
 *      </ul>
 */
int32_t cps_decodeMailBoxList(EMAIL_HANDLE CPSHandle, const int8_t *pMailBoxListStr,
    const int32_t mailBoxListStrLen, const EMAIL_FIELD_TYPE fieldType);

/**
 * Decode Date and Time (day-of-week , day month year FWS hour ":" minute [ ':' second]) into
 * seconds from midnight, January 1, 1970 in UTC
 *
 * \param pFieldDateBody [in]
 *          The field body of date header
 *
 * \param fieldDateBodyLen [in]
 *          The length of field date body
 *
 *
 * \return
 *      <ul>
 *          <li>The specified calendar time encoded as a value of type int32_t.
 *          <li>#EMAIL_CPS_ALLOC_FAIL
 *          <li>#EMAIL_CPS_PARAMETER_ERROR
 *      </ul>
 */
int32_t cps_decodeDateTime(const int8_t *pFieldDateBody, const int32_t fieldDateBodyLen);

/**
 *  Decode the encoded string and convert into utf8 from other charset
 *
 * \param pEncodedData [in]
 *          The encoded string
 *
 * \param encodedDataLen [in]
 *          The length of encoded string
 *
 * \param ppDecodedData [out]
 *          The string pointer to save the decoded string  in utf-8. Note: should free this memory block after used
 *
 * \param pDecodedDataLen [out]
 *          The length of decoded string in utf-8
 *
 * \param pDisplayNameCharset [out]
 *          The charset of display name, #NCCPort_NccCharset_t
 *
 * \return
 *      <ul>
 *          <li>#EMAIL_CPS_SUCCESS
 *          <li>#EMAIL_CPS_ALLOC_FAIL
 *          <li>#EMAIL_CPS_PARAMETER_ERROR
 *      </ul>
 */
int32_t cps_decodeEncodedData(const int8_t *pEncodedData, const int32_t encodedDataLen,
        int8_t **ppDecodedData, int32_t *pDecodedDataLen);

/**
 * Get display name and email address from mailbox
 *
 * \param pMailBoxStr [in]
 *          The string pointer which point to the mailbox string
 *
 * \param mailBoxStrLen [in]
 *          The string length of mailbox string
 *
 * \param ppDisplayName [out]
 *          The string pointer to save display name. NOTE: must free this memory block after used
 *
 * \param pDisplayNameLen [out]
 *          The string length of display name
 *
 * \param ppAddrValue [out]
 *          The email address string. NOTE: must free this memory block after used
 *
 * \param pAddrValueLen [out]
 *          The string length of email address
 *
 * \return
 *      <ul>
 *          <li>#EMAIL_CPS_SUCCESS
 *          <li>#EMAIL_CPS_ALLOC_FAIL
 *          <li>#EMAIL_CPS_PARAMETER_ERROR
 *      </ul>
 */
int32_t cps_decodeMailBox(const int8_t *pMailBoxStr, const int32_t mailBoxStrLen,
    int8_t **ppDisplayName, int32_t *pDisplayNameLen, int8_t **ppAddrValue, int32_t *pAddrValueLen);

/**
 * Get field name and body from one field line
 *
 * \param pFieldData [in]
 *          A field line which contains field name : field body CRLF
 *
 * \param fieldDatalen [in]
 *          The string length of field line
 *
 * \param pFieldName [out]
 *          The string pointer which point to the first char of field name. Note:don't need free this memory block
 *
 * \param pFieldNameLen [out]
 *          The length of field name
 *
 * \param pFieldBody [out]
 *          The string pointer which point to the first char of field body. Note: don't need free this memory block
 *
 * \param pFieldBodyLen [out]
 *          The string length of field body
 *
 * \return
 *      <ul>
 *          <li>#EMAIL_CPS_SUCCESS
 *          <li>#EMAIL_CPS_PARAMETER_ERROR
 *      </ul>
 */
int32_t cps_getFieldNameAndBody(int8_t *pFieldData, int32_t filedDataLen,
    int8_t **pFieldName, int32_t *pFieldNameLen, int8_t **pFieldBody, int32_t *pFieldBodyLen);

/**
 * Parse email header. convert binary pdu into email structure
 *
 * \param CPSHandle [in, out]
 *          The structure pointer to save email information
 *
 * \param pHeader [in]
 *          The string pointer of header pdu
 *
 * \param headerLen
 *          The string length of header pdu
 *
 * \return
 *      <ul>
 *          <li>#EMAIL_CPS_SUCCESS
 *          <li>#EMAIL_CPS_PARAMETER_ERROR
 *      </ul>
 */
int32_t cps_decodeEmailHeaders(EMAIL_HANDLE CPSHandle, int8_t *pHeader, int32_t headerLen);

/**
 * Decode Content-Type header field. split into value and parameters string
 *
 * \param pFieldBody [in]
 *          The string pointer for Content-Type field
 *
 * \param fieldBodyLen [in]
 *          The length of Content-Type field body
 *
 * \param pContentType [out]
 *          The structure pointer to save Content-Type value and Content-Type parameters
 *
 * \return
 *      <ul>
 *          <li>#EMAIL_CPS_SUCCESS
 *          <li>#EMAIL_CPS_PARAMETER_ERROR
 *          <li>#EMAIL_CPS_FAILED
 *      </ul>
 */
int32_t cps_decodeContentType(const int8_t *pFieldBody, const int32_t fieldBodyLen,
    T_EMAIL_ContentType *pContentType);

/**
 * Encapsulation NCCCommon_mbsToUtf8 APIs. Convert multi bytes string into UTF-8 String
 *
 * \param pMbs [in]
 *      The string pointer of multi bytes.
 *
 * \param mbslen [in]
 *      The string length of multi bytes
 *
 * \param charset [in]
 *      The charset value of multi bytes, #NCCPort_NccCharset_t
 *
 * \param ppUtf8 [out]
 *      The string pointer for UTF-8 string
 *
 * \param pUtf8Len [out]
 *      The length of UTF-8 string
 *
 * \return
 *      <ul>
 *          <li>#EMAIL_CPS_SUCCESS
 *          <li>#EMAIL_CPS_PARAMETER_ERROR
 *          <li>#EMAIL_CPS_ALLOC_FAIL
 *      </ul>
 */
int32_t cps_mbsToUtf8(const int8_t *pMbs, const int32_t mbsLen, NCCPort_NccCharset_t charset,
    int8_t **ppUtf8, int32_t *pUtf8Len);

/**
 * Decode email body binary data into email structure. Convert multipart list into email structure.
 *
 * \param CPSHandle [in, out]
 *      The structure pointer of email
 *
 * \param pMultipartRoot [in]
 *      Root multipart tree
 *
 * \return
 *      <ul>
 *          <li>#EMAIL_CPS_SUCCESS
 *          <li>#EMAIL_CPS_PARAMETER_ERROR
 *          <li>#EMAIL_CPS_ALLOC_FAIL
 *      </ul>
 */
int32_t cps_decodeEmailBody(EMAIL_HANDLE CPSHandle, T_Multipart_BodyOrPart *pMultipartRoot);

/**
 * Create T_Multipart_BodyOrPart structure
 *
 * \param pRoot [in]
 *	The root node for multipart tree, the pPart must be non-null.
 *
 */
void cps_createMultipartTree (T_Multipart_BodyOrPart *pRoot);

/**
 * Pack attachments into multipart tree for email
 *
 * \param CPSHandle [in]
 *	The email structure pointer
 *
 * \param pRoot [in, out]
 *	The multipart tree for current email
 *
 * \return
 * <ul>
 *	<li>#EMAIL_CPS_SUCCESS
 *	<li>#EMAIL_CPS_PARAMETER_ERROR
 *	<li>#EMAIL_CPS_FAILED
 * </ul>
 */
int32_t cps_encodeAttachments(EMAIL_HANDLE CPSHandle, T_Multipart_BodyOrPart *pRoot);

/**
 * Pack email body into multipart tree.
 *
 * \param CPSHandle [in]
 *	The structure pointer for email
 *
 * \param pRoot [in, out]
 *	The pointer for T_Multipart_BodyOrPart structure
 *
 * \return
 *	<ul>
 *		<li>#EMAIL_CPS_SUCCESS
 *		<li>#EMAIL_CPS_FAILED
 *		<li>#EMAIL_CPS_PARAMETER_ERROR
 *	</ul>
 */
int32_t cps_encodeEmailBody(EMAIL_HANDLE CPSHandle, T_Multipart_BodyOrPart *pRoot);

/**
 * Pack extra header into multipart node
 *
 * \param pRoot [in, out]
 *	The root pointer for T_Multipart_BodyOrPart structure
 *
 * \param fieldType [in]
 *	The type of extra header
 *
 * \param pFieldBody [in]
 *	The value of extra header
 *
 * \param fieldBodylen [in]
 *	The value length of extra header
 *
 * \return
 * 	<ul>
 *		<li>#EMAIL_CPS_SUCCESS
 *		<li>#EMAIL_CPS_PARAMETER_ERROR
 *		<li>#EMAIL_CPS_ALLOC_FAIL
 *		<li>#EMAIL_CPS_FAILED
 *    </ul>
 */
int32_t cps_encodeExtraHeader(T_Multipart_BodyOrPart *pRoot, EMAIL_FIELD_TYPE fieldType,
    int8_t *pFieldBody, int32_t fieldBodyLen);

/**
 * Pack Content-Type header into multipart tree
 *
 * \param CPSHandle [in]
 *	The structure pointer for email handle
 *
 * \param pRoot [in, out]
 *	The root node for email multipart tree
 *
 * \return
 *	<ul>
 *		<li>#EMAIL_CPS_SUCCESS
 *		<li>#EMAIL_CPS_FAILED
 *		<li>#EMAIL_CPS_PARAMETER_ERROR
 *	</ul>
 */
int32_t cps_encodeContentTypeHeader(EMAIL_HANDLE CPSHandle, T_Multipart_BodyOrPart *pRoot);

/**
 * Pack Mime-Version header into email multipart tree
 *
 * \param CPSHandle [in]
 *	The EMAIL_HANDLE structure pointer for email
 *
 * \param pRoot [in]
 *	The root node for email multipart tree
 *
 * \return
 *	<ul>
 *		<li>#EMAIL_CPS_SUCCESS
 *		<li>#EMAIL_CPS_FAILED
 *		<li>#EMAIL_CPS_PARAMETER_ERROR
 *	</ul>
 */
int32_t cps_encodeMimeVersionHeader(EMAIL_HANDLE CPSHandle, T_Multipart_BodyOrPart *pRoot);

/**
 * Encode mainbox list into string such as "=?utf8?B?R21haWwg0KHX6b60yc8?=" <mail-noreply@gmail.com>,
 * "=?utf8?B?R21haWwg0KHX6b60yc8?=" <mail-noreply@gmail.com>
 *
 * \param pMailboxList [in]
 *      The list header of mailbox
 *
 * \param ppAddrStr [out]
 *      The output parameter to save the mailbox list string buffer
 *
 *  \param pAddrStrLen [out]
 *      The length of mailbox list string (ppAddrStr).
 *
 * \return
 *      <ul>
 *          <li>#EMAIL_CPS_SUCCESS
 *          <li>#EMAIL_CPS_PARAMETER_ERROR
 *          <li>#EMAIL_CPS_ALLOC_FAIL
 *      </ul>
 */
int32_t cps_encodeMailboxList(T_EMAIL_MailBox_List *pMailboxList, int8_t **ppAddrStr, int32_t *pAddrStrLen);


/**
 * Pack From header into email multipart tree
 *
 * \param CPSHandle [in]
 *	The EMAIL_HANDLE structure pointer for email
 *
 * \param pRoot [in]
 *	The root node for email multipart tree
 *
 * \return
 *	<ul>
 *		<li>#EMAIL_CPS_SUCCESS
 *		<li>#EMAIL_CPS_FAILED
 *		<li>#EMAIL_CPS_PARAMETER_ERROR
 *	</ul>
 */
int32_t cps_encodeFromHeader(EMAIL_HANDLE CPSHandle, T_Multipart_BodyOrPart *pRoot);

/**
 * Pack To header into email multipart tree
 *
 * \param CPSHandle [in]
 *	The EMAIL_HANDLE structure pointer for email
 *
 * \param pRoot [in]
 *	The root node for email multipart tree
 *
 * \return
 *	<ul>
 *		<li>#EMAIL_CPS_SUCCESS
 *		<li>#EMAIL_CPS_FAILED
 *		<li>#EMAIL_CPS_PARAMETER_ERROR
 *	</ul>
 */
int32_t cps_encodeToHeader(EMAIL_HANDLE CPSHandle, T_Multipart_BodyOrPart *pRoot);

/**
 * Pack Cc header into email multipart tree
 *
 * \param CPSHandle [in]
 *	The EMAIL_HANDLE structure pointer for email
 *
 * \param pRoot [in]
 *	The root node for email multipart tree
 *
 * \return
 *	<ul>
 *		<li>#EMAIL_CPS_SUCCESS
 *		<li>#EMAIL_CPS_FAILED
 *		<li>#EMAIL_CPS_PARAMETER_ERROR
 *	</ul>
 */
int32_t cps_encodeCcHeader(EMAIL_HANDLE CPSHandle, T_Multipart_BodyOrPart *pRoot);

/**
 * Pack Bcc header into email multipart tree
 *
 * \param CPSHandle [in]
 *	The EMAIL_HANDLE structure pointer for email
 *
 * \param pRoot [in]
 *	The root node for email multipart tree
 *
 * \return
 *	<ul>
 *		<li>#EMAIL_CPS_SUCCESS
 *		<li>#EMAIL_CPS_FAILED
 *		<li>#EMAIL_CPS_PARAMETER_ERROR
 *	</ul>
 */
int32_t cps_encodeBccHeader(EMAIL_HANDLE CPSHandle, T_Multipart_BodyOrPart *pRoot);

/**
 * Pack Reply-To header into email multipart tree
 *
 * \param CPSHandle [in]
 *	The EMAIL_HANDLE structure pointer for email
 *
 * \param pRoot [in]
 *	The root node for email multipart tree
 *
 * \return
 *	<ul>
 *		<li>#EMAIL_CPS_SUCCESS
 *		<li>#EMAIL_CPS_FAILED
 *		<li>#EMAIL_CPS_PARAMETER_ERROR
 *	</ul>
 */
int32_t cps_encodeReplyToHeader(EMAIL_HANDLE CPSHandle, T_Multipart_BodyOrPart *pRoot);

/**
 * Pack Subject header into email multipart tree
 *
 * \param CPSHandle [in]
 *	The EMAIL_HANDLE structure pointer for email
 *
 * \param pRoot [in]
 *	The root node for email multipart tree
 *
 * \return
 *	<ul>
 *		<li>#EMAIL_CPS_SUCCESS
 *		<li>#EMAIL_CPS_FAILED
 *		<li>#EMAIL_CPS_PARAMETER_ERROR
 *	</ul>
 */
int32_t cps_encodeSubjectHeader(EMAIL_HANDLE CPSHandle, T_Multipart_BodyOrPart *pRoot);

/**
 * Pack X-Priority header into email multipart tree
 *
 * \param CPSHandle [in]
 *	The EMAIL_HANDLE structure pointer for email
 *
 * \param pRoot [in]
 *	The root node for email multipart tree
 *
 * \return
 *	<ul>
 *		<li>#EMAIL_CPS_SUCCESS
 *		<li>#EMAIL_CPS_FAILED
 *		<li>#EMAIL_CPS_PARAMETER_ERROR
 *	</ul>
 */
int32_t cps_encodePriorityHeader(EMAIL_HANDLE CPSHandle, T_Multipart_BodyOrPart *pRoot);

/**
 * Pack Date header into email multipart tree
 *
 * \param CPSHandle [in]
 *	The EMAIL_HANDLE structure pointer for email
 *
 * \param pRoot [in]
 *	The root node for email multipart tree
 *
 * \return
 *	<ul>
 *		<li>#EMAIL_CPS_SUCCESS
 *		<li>#EMAIL_CPS_FAILED
 *		<li>#EMAIL_CPS_PARAMETER_ERROR
 *	</ul>
 */
int32_t cps_encodeOriginDateHeader(EMAIL_HANDLE CPSHandle, T_Multipart_BodyOrPart *pRoot);

#ifdef __cplusplus
}
#endif

#endif /* __EML_PROT_INSIDE_H__ */
