
/**
 * @file
 * NCC mms protocol inside
 *
 * Protocl internal Macros of the NCC mms protocol module
 */

#ifndef __PROT_INSIDE_H__
#define __PROT_INSIDE_H__

#ifdef __cplusplus
extern "C" {
#endif

#define MMS_ABSOLUTE_TOKEN                                   0x80       /* Time flag:Absolute-token */
#define MMS_RELATIVE_TOKEN                                   0x81       /* Time flag:Relative-token */

/** Sender-visibility-value  */
#define MMS_HIDE                                             0x80           /**< */
#define MMS_SHOW                                             0x81           /**< */

/**flag of  delivery and read report*/
#define MMS_YES                                              0x80                       /**< Flag Yes */
#define MMS_NO                                               0x81                   /**< Flag No */

/* message struct type define  */
#define MMS_ADDRESS_PRESENT_TOKEN                            0x80       /* From field flag:Address-present-token */
#define MMS_INSERT_ADDRESS_TOKEN                             0x81       /* From field flag:Insert-address-token */

/*message type*/
#define MMS_SEND_REQ                                         0x80       /* Message-Type:m-send-req */
#define MMS_SEND_CONF                                        0x81       /* Message-Type:m-send-conf */
#define MMS_NOTIFYREP_IND                                    0x83       /* Message-Type:m-notifyresp-ind */
#define MMS_RETRIEVE_CONF                                    0x84       /* Message-Type:m-retieve-conf */
#define MMS_ACKNOWLEDGE_IND                                  0x85       /* Message-Type:m-acknowledge-ind */
#define MMS_READ_REC_IND                                     0x87       /*Message-type: m-read-rec-ind */
#define MMS_FORWARD_REQ                                      0x89       /*Message-type: m-forward-req */
#define MMS_FORWARD_CONF                                     0x8A       /*Message-type: m-forward-conf */
#define MMS_MBOX_STORE_REQ                                   0x8B       /*Message-type: m-mbox-store-req */
#define MMS_MBOX_STORE_CONF                                  0x8C       /*Message-type: m-mbox-store-conf */
#define MMS_MBOX_VIEW_REQ                                    0x8D       /*Message-type: m-mbox-view-req */
#define MMS_MBOX_VIEW_CONF                                   0x8E       /*Message-type: m-mbox-view-conf */
#define MMS_MBOX_UPLOAD_REQ                                  0x8F       /*Message-type: m-mbox-upload-req */
#define MMS_MBOX_UPLOAD_conf                                 0x90       /*Message-type: m-mbox-upload-conf */
#define MMS_MBOX_DELETE_REQ                                  0x91       /*Message-type: m-mbox-delete-req */
#define MMS_MBOX_DELETE_CONF                                 0x92       /*Message-type: m-mbox-delete-conf */
#define MMS_MBOX_DESCR                                       0x93       /*Message-type: m-mbox-descr */

/*  MMS field name assigned number  */
#define MMS_BCC_FIELD                                        0x81
#define MMS_CC_FIELD                                         0x82
#define MMS_CONTENT_LOCATION_FIELD                           0x83       /*X-Mms-Content-Location 0x03 */
#define MMS_CONTENT_TYPE_FIELD                               0x84
#define MMS_DATE_FIELD                                       0x85
#define MMS_DELIVERY_REPORT_FIELD                            0x86       /*X-Mms-Delivery-Report 0x06*/
#define MMS_DELIVERY_TIME_FIELD                              0x87       /*X-Mms-Delivery-Time 0x07 */
#define MMS_EXPIRY_FIELD                                     0x88       /*X-Mms-Expiry 0x08 */
#define MMS_FROM_FIELD                                       0x89
#define MMS_MESSAGE_CLASS_FIELD                              0x8A       /*X-Mms-Message-Class 0x0A */
#define MMS_MESSAGE_ID_FIELD                                 0x8B       
#define MMS_MESSAGE_TYPE_FIELD                               0x8C       /*X-Mms-Message-Type 0x0C */
#define MMS_VERSION_FIELD                                    0x8D       /*X-Mms-MMS-Version 0x0D */
#define MMS_MESSAGE_SIZE_FIELD                               0x8E       /*X-Mms-Message-Size 0x0E */
#define MMS_PRIORITY_FIELD                                   0x8F       /*X-Mms-Priority 0x0F */
#define MMS_READ_REPLAY_FIELD                                0x90       /*X-Mms-Read-Report 0x10 */
#define MMS_REPORT_ALLOWED_FIELD                             0x91       /*X-Mms-Report-Allowed 0x11 */
#define MMS_RESPONSE_STATUS_FIELD                            0x92       /*X-Mms-Response-Status 0x12 */
#define MMS_RESPONSE_TEXT_FIELD                              0x93       /*X-Mms-Response-Text 0x13 */
#define MMS_SENDER_VISIBILITY_FIELD                          0x94       /*X-Mms-Sender-Visibility 0x14 */
#define MMS_STATUS_FIELD                                     0x95       /*X-Mms-Status 0x15 */
#define MMS_SUBJECT_FIELD                                    0x96
#define MMS_TO_FIELD                                         0x97
#define MMS_TRANSACTION_ID_FIELD                             0x98       /*X-Mms-Transaction-Id 0x18 */
#define MMS_RETRIEVE_STATUS_FIELD                            0x99       /*X-Mms-Retrieve-Status 0x19 */
#define MMS_RETRIEVE_TEXT_FIELD                              0x9A       /*X-Mms-Retrieve-Text 0x1A */

#define MMS_READ_STATUS_FIELD                                0x9B       /*X-Mms-Read-Status 0x1B */
#define MMS_REPLY_CHARGING_FIELD                             0x9C       /*X-Mms-Reply-Charging 0x1C */
#define MMS_REPLY_CHARGING_DEADLINE_FIELD                    0x9D       /*X-Mms-Reply-Charging-Deadline 0x1D */
#define MMS_REPLY_CHARGING_ID                                0x9E       /*X-Mms-Reply-Charging-ID 0x1E */
#define MMS_REPLY_CHARGING_SIZE                              0x9F       /*X-Mms-Reply-Charging-Size 0x1F */
#define MMS_PREVIOUSLY_SENT_BY                               0xA0       /*X-Mms-Previously-Sent-By 0x20 */
#define MMS_PREVIOUSLY_SENT_DATE                             0xA1       /*X-Mms-Previously-Sent-Date 0x21 */

#define MMS_STORE_FIELD                                      0xA2       /*X-Mms-Store 0x22 */
#define MMS_MM_STATE_FIELD                                   0xA3       /*X-Mms-MM-State 0x23 */
#define MMS_MM_FLAGS_FIELD                                   0xA4       /*X-Mms-MM-Flags 0x24 */
#define MMS_STORE_STATUS_FIELD                               0xA5       /*X-Mms-Store-Status 0x25 */
#define MMS_STORE_STATUS_TEXT_FIELD                          0xA6       /*X-Mms-Store-Status-Text 0x26 */
#define MMS_STORED_FIELD                                     0xA7       /*X-Mms-Stored 0x27 */
#define MMS_ATTRIBUTES_FIELD                                 0xA8       /*X-Mms-Attributes 0x28 */
#define MMS_TOTALS_FIELD                                     0xA9       /*X-Mms-Totals 0x29 */
#define MMS_MBOX_TOTALS_FIELD                                0xAA       /*X-Mms-Mbox-Totals 0x2A */
#define MMS_QUOTAS_FIELD                                     0xAB       /*X-Mms-Quotas 0x2B */
#define MMS_MBOX_QUOTAS_FIELD                                0xAC       /*X-Mms-Mbox-Quotas 0x2C */
#define MMS_MESSAGE_COUNT_FIELD                              0xAD       /*X-Mms-Message-Count 0x2D */
#define CONTENT_FIELD                                        0xAE       
#define MMS_START_FIELD                                      0xAF       /*X-Mms-Start 0x2F */
#define ADDITIONAL_HEADER_FIELD                              0xB0       
#define MMS_DISTRIBUTION_INDICATOR_FIELD                     0xB1       /*X-Mms-Distribution-Indicator 0x31 */
#define MMS_ELEMENT_DESCRIPTOR_FIELD                         0xB2       /*X-Mms-Element-Descriptor 0x32 */
#define MMS_LIMIT_FIELD                                      0xB3       /*X-Mms-Limit 0x33 */
#define MMS_RECOMMENDED_RETRIEVAL_MODE_FIELD                 0xB4       /*X-Mms-Recommended-Retrieval-Mode 0x34 */
#define MMS_RECOMMENDED_RETRIEVAL_MODE_TEXT_FIELD            0xB5       /*X-Mms-Recommended-Retrieval-Mode-Text 0x35 */
#define MMS_STATUS_TEXT_FIELD                                0xB6       /*X-Mms-Status-Text 0x36 */
#define MMS_APPLIC_ID                                        0xB7       /*X-Mms-Applic-ID 0x37 */
#define MMS_REPLY_APPLIC_ID                                  0xB8       /*X-Mms-Reply-Applic-ID 0x38 */
#define MMS_AUX_APPLIC_INFO                                  0xB9       /*X-Mms-Aux-Applic-Info 0x39 */
#define MMS_CONTENT_CLASS                                    0xBA
#define MMS_DRM_CONTENT                                      0xBB
#define MMS_ADAPTATION_ALLOWED                               0xBC
#define MMS_REPLACE_ID                                       0xBD
#define MMS_CANCEL_ID                                        0xBE
#define MMS_CANCEL_STATUS                                    0xBF

/*store state of the stored MM in MMBox,Draft | Sent | New | Retrieved | Forwarded*/
#define MM_STATE_VALUE_DRAFT                                 0x80
#define MM_STATE_VALUE_SENT                                  0x81
#define MM_STATE_VALUE_NEW                                   0x82
#define MM_STATE_VALUE_RETRIEVED                             0x83
#define MM_STATE_VALUE_FORWARDED                             0x84

/*Mms-MM-Flags field*/
#define ADD_TOKEN                                            0x80
#define REMOVE_TOKEN                                         0x81
#define FILTER_TOKEN                                         0x82

/*  Well know parameter assignments */
#define MMS_PARAM_Q_FIELD                                    0x00
#define MMS_PARAM_CHARSET                                    0x01
#define MMS_PARAM_LEVEL                                      0x02
#define MMS_PARAM_TYPE                                       0x03
#define MMS_PARAM_NAME                                       0x05
#define MMS_PARAM_FILENAME                                   0x06
#define MMS_PARAM_DEFFERENCES                                0x07
#define MMS_PARAM_PADDING                                    0x08
#define MMS_PARAM_TYPE_WITH_MULTIPART                        0x09
#define MMS_PARAM_START                                      0x0A
#define MMS_PARAM_START_INFO                                 0x0B

/*X-Mms-Mbox-Totals field value*/
#define MESSAGE_TOTAL_TOKEN                                  0x80       //Message-total-token = <Octet 128>
#define SIZE_TOTAL_TOKEN                                     0x81       //Size-total-token = <Octet 129>

/*X-Mms-Mbox-Quotas field*/
#define MESSAGE_QUOTA_TOKEN                                  0x80       //Message-quota-token = <Octet 128>
#define SIZE_QUOTA_TOKEN                                     0x81       //Size-quota-token = <Octet 129>

/* WAP  Header field name assignment */
#define ACCEPT                                               0x00
#define ACCEPT_CHARSET                                       0x01
#define ACCEPT_ENCODING                                      0x02
#define ACCEPT_LANGUAGE                                      0x03
#define ACCEPT_RANGES                                        0x04
#define AGE                                                  0x05
#define ALLOW                                                0x06
#define AUTHORIZATION                                        0x07
#define CACHE_CONTROL                                        0x08
#define CONNECTION                                           0x09
#define CONTENT_BASE                                         0x0A
#define CONTENT_ENCODING                                     0x0B
#define CONTENT_LANGUAGE                                     0x0C
#define CONTENT_LENGTH                                       0x0D
#define CONTENT_LOCATION                                     0x0E
#define CONTENT_MD5                                          0x0F
#define CONTENT_RANGE                                        0x10
#define CONTENT_TYPE                                         0x11
#define DATE                                                 0x12
#define ETAG                                                 0x13
#define EXPIRES                                              0x14
#define FROM                                                 0x15
#define HOST                                                 0x16
#define IF_MODIFIED_SINCE                                    0x17
#define IF_MATCH                                             0x18
#define IF_NONE_MATCH                                        0x19
#define IF_RANGE                                             0x1A
#define IF_UNMODIFIED_SINCE                                  0x1B
#define LOCATION                                             0x1C
#define LAST_MODIFIED                                        0x1D
#define MAX_FORWARDS                                         0x1E
#define PRAGMA                                               0x1F
#define PROXY_AUTHENTICATE                                   0x20
#define PROXY_AUTHORIZATION                                  0x21
#define PUBLIC                                               0x22
#define RANGE                                                0x23
#define REFERER                                              0x24
#define RETRY_AFTER                                          0x25
#define SERVER                                               0x26
#define TRANSFER_ENCODING                                    0x27
#define UPGRADE                                              0x28
#define USER_AGENT                                           0x29
#define VARY                                                 0x2A
#define VIA                                                  0x2B
#define WARNING                                              0x2C
#define WWW_AUTHENTICATE                                     0x2D
#define CONTENT_DISPOSITION                                  0x2E
#define X_WAP_APPLICATION_ID                                 0x2F
#define X_WAP_CONTENT_URI                                    0x30
#define X_WAP_INITIATOR_URI                                  0x31
#define ACCEPT_APPLICATION                                   0x32
#define BEARER_INDICATION                                    0x33
#define PUSH_FLAG                                            0x34
#define PROFILE                                              0x35
#define PROFILE_DIFF                                         0x36
#define PROFILE_WARNING                                      0x37
#define EXPECT                                               0x38
#define TE                                                   0x39
#define TRAILER                                              0x3A
#define X_WAP_TOD                                            0x3F
#define CONTENT_ID                                           0x40
#define SET_COOKIE                                           0x41
#define COOKIE                                               0x42
#define ENCODING_VERSION                                     0x43
#define X_WAP_SECURITY                                       0x46

/*  charset assignment number */
#define BIG5                                                 0x07EA
#define ISO_10646_UCS_2                                      0x03E8
#define US_ASCII                                             0x03
#define ISO_8859_1                                           0x04
#define ISO_8859_2                                           0x05
#define ISO_8859_3                                           0x06
#define ISO_8859_4                                           0x07
#define ISO_8859_5                                           0x08
#define ISO_8859_6                                           0x09
#define ISO_8859_7                                           0x0A
#define ISO_8859_8                                           0x0B
#define ISO_8859_9                                           0x0C
#define SHIFT_JIS                                            0x11
#define UTF_8                                                0x6A

#define THE_LENGTH_OF_ELEMENT_TYPE     (4 * COMPOSER_FILENAME_LEN)

#ifdef __cplusplus
}
#endif

#endif /* __PROT_INSIDE_H__ */
