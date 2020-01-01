/**
 * @file
 * NCC mms protocol Service Layer
 *
 * Service API exposed by the NCC mms protocol module
 *
 * <!-- #interface list begin -->
 * \section nccmms_prot Interface
 * - NCCMms_prot_makeSendMessagePdu()
 * - NCCMms_prot_allocMessageMem()
 * - NCCMms_prot_freeMessageMem()
 * - NCCMms_prot_parseNotificationInd()
 * - NCCMms_prot_parseSendConf()
 * - NCCMms_prot_parseRetrieveConf()
 * - NCCMms_prot_parseDeliveryInd()
 * - NCCMms_prot_parseReadOrigInd()
 * - NCCMms_prot_parseForwardConf()
 * - NCCMms_prot_parseMBoxStoreConf()
 * - NCCMms_prot_parseMBoxViewConf()
 * - NCCMms_prot_parseMBoxUploadConf()
 * - NCCMms_prot_parseMBoxDeleteConf()
 * - NCCMms_prot_parseMBoxDescrPdu()
 * - NCCMms_prot_makeNotifyRespPdu()
 * - NCCMms_prot_makeAcknowledgePdu()
 * - NCCMms_prot_makeReadReportPdu()
 * - NCCMms_prot_makeReadRecPDU()
 * - NCCMms_prot_makeForwardingMessagePdu()
 * - NCCMms_prot_makeBoxStoreMessagePdu()
 * - NCCMms_prot_makeBoxViewMessagePdu()
 * - NCCMms_prot_makeBoxUploadReqPdu()
 * - NCCMms_prot_makeBoxDeleteReqPdu()
 * - NCCMms_prot_freeMadeMsgPduBuf()
 * - NCCMms_prot_recvSendConfData()
 * <!-- #interface list end -->
 */

#ifndef __NCC_MMS_PROT_H__
#define __NCC_MMS_PROT_H__

#include <ncc_types.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
   *=======define some constants for protocol module=======
   */

/**
   *\name delivery status value of delivery report
   */

/*@{*/

/**Status-value:Expired*/
#define MMS_EXPIRED                                          0x80
/**Status-value:Retrieved*/
#define MMS_RETRIEVED                                        0x81
/**Status-value:Rejected*/
#define MMS_REJECTED                                         0x82
/**Status-value:Deferred*/
#define MMS_DEFERRED                                         0x83
/**Status-value:Unrecognised*/
#define MMS_UNRECOGNISED                                     0x84

/*@}*/

/**PUSH message ID :  type of MMS PUSH message */
#define MMS_NOTIFICATION_IND                                 0x82   /**< Flag : m-notification-ind */
#define MMS_DELIVERY_IND                                     0x86   /**< Flag : M-Delivery.ind */
#define MMS_READ_ORIG_IND                                    0x88       /**< Flag :  M-Read-Orig.ind*/

/**
   *    \name values that indicate X-Mms-Priority fields of M-Retrieve.Conf PDU and M-Send.req PDU
   */

/*@{*/

/** Priority-value:LOW */
#define MMS_PRIORITY_LOW                                     0x80
/** Priority-value:NORMAL*/
#define MMS_PRIORITY_NORMAL                                  0x81
/** Priority-value:HIGH */
#define MMS_PRIORITY_HIGN                                    0x82

/*@}*/

/**
   *    \name   Response-Status-Value of X-Mms_Response-Status field
   */

/*@{*/

/**Response-status-value:OK */
#define MMS_OK                                               0x80
/**Response-status-value:Error-unspecified(obsolete) */
#define MMS_ERROR_UNSPECIFIED                                0x81
/**Response-status-value:Error-service-denied(obsolete) */
#define MMS_ERROR_SERVICE_DENIED                             0x82
/**Response-status-value:Error-format-corrupt(obsolete) */
#define MMS_ERROR_MESSAGE_FORMAT_CORRUPT                     0x83
/**Response-status-value:Error-address-unresolved(obsolete) */
#define MMS_ERROR_SENDING_ADDRESS_UNRESOLVED                 0x84
/**Response-status-value:Error-not-found(obsolete) */
#define MMS_ERROR_MESSAGE_NOT_FOUND                          0x85
/**Response-status-value:Error-network-problem(obsolete) */
#define MMS_ERROR_NETWORK_PROBLEM                            0x86
/**Response-status-value:Error-content-not-accept(obsolete)*/
#define MMS_ERROR_CONTENT_NOT_ACCEPTED                       0x87
/**Response-status-value:Error-unsupported-message*/
#define MMS_ERROR_UNSUPPORTED_MESSAGE                        0x88

/*@}*/

/**
   *    \name   Message-class-value of X-Mms-Message-Class field
   */

/*@{*/

/**Message-Class-Value:Personal*/
#define MMS_MESSAGE_CLASS_PERSONAL                           0x80
/**Message-Class-Value:Advertisement*/
#define MMS_MESSAGE_CLASS_ADVERTISEMENT                      0x81
/**Message-Class-Value:Information*/
#define MMS_MESSAGE_CLASS_INFORMATIONAL                      0x82
/**Message-Class-Value:Auto*/
#define MMS_MESSAGE_CLASS_AUTO                               0x83

/*@}*/

/**
   *    \name   Int Constant that indicates struct type
   */

/*@{*/

/**struct type:M-Send.req PDU*/
#define MMS_STRUCT_MMS_SEND_REQUEST                          0x1
/**struct type:M-Send.conf PDU*/
#define MMS_STRUCT_MMS_SEND_CONF                             0x2
/**struct type:M-Notification.ind PDU*/
#define MMS_STRUCT_MMS_NOTIFICATION_IND                      0x3
/**struct type:M-Retrieve.conf PDU*/
#define MMS_STRUCT_MMS_RETRIEVE_CONF                         0x4
/**struct type:M-Delivery.ind PDU*/
#define MMS_STRUCT_MMS_DELIVERY_IND                          0x5
/**struct type:M-Notifyresp.ind PDU*/
#define MMS_STRUCT_MMS_NOTIFYRESP_IND                        0x6
/**struct type:M-Acknowledge.ind PDU*/
#define MMS_STRUCT_MMS_ACKNOWLEDGE_IND                       0x7
/**struct type:M-Read.orig PDU*/
#define MMS_STRUCT_MMS_READORIG_IND                          0x8
/**struct type:M-Forward.conf PDU*/
#define MMS_STRUCT_MMS_FORWARD_CONF                          0x9
/**struct type:M-Store.conf PDU*/
#define MMS_STRUCT_M_MBOX_STORE_CONF                         0xA
/**struct type:M-View.conf PDU*/
#define MMS_STRUCT_M_MBOX_VIEW_CONF                          0xB
/**struct type:M-Upload.conf PDU*/
#define MMS_STRUCT_M_MBOX_UPLOAD_CONF                        0xC
/**struct type:M-Delete.conf PDU*/
#define MMS_STRUCT_M_MBOX_DELETE_CONF                        0xD
/**struct type:M-Read-rec.ind PDU*/
#define MMS_STRUCT_MMS_READREC_IND                           0xE

/*@}*/

/**
   *    \name return code of NCCMms_prot_recvSendConfData function.
   */

/*@{*/

#define MMS_SEND_RESPONSE_OK                                 0x0        /**<Ok */
#define MMS_SEND_RESPONSE_ERROR_UNSPECIFIED                  0x1        /**<Error-unspecified */
#define MMS_SEND_RESPONSE_ERROR_SERVICE_DENIED               0x2        /**<Error- service-denied */
#define MMS_SEND_RESPONSE_ERROR_MESSAGE_FORMAT_CORRUPT       0x3        /**<Error-message-format-corrupt */
#define MMS_SEND_RESPONSE_ERROR_SENDING_ADDRESS_UNRESOLVED   0x4        /**<Error-sending-address-unresolved */
#define MMS_SEND_RESPONSE_ERROR_MESSAGE_NOT_FOUND            0x5        /**<Error-message-not-found */
#define MMS_SEND_RESPONSE_ERROR_NETWORK_PROBLEM              0x6        /**<Error-network-problem */
#define MMS_SEND_RESPONSE_ERROR_CONTENT_NOT_ACCEPTED         0x7        /**<Error- content-not-accepted */
#define MMS_SEND_RESPONSE_ERROR_UNSUPPORTED_MESSAGE          0x8        /**<Error-unsupported-message */
#define MMS_SEND_RESPONSE_ERROR_UNKNOW                       0x9        /**<Error-transient-failure */
#define MMS_SEND_RESPONSE_ERROR_FUNCTION_ERROR               0xA        /**<Error-transient-sending-address-unresolved */

/*@}*/

/**
   *    \name   Reply-charging-value of X-Mms-Reply-charging field.
   */

/*@{*/

/**Reply-charging-value:Requested*/
#define CHARGINH_REQUESTED                                   0x80
/**Reply-charging-value:Requested text only*/
#define CHARGING_REQUESTED_TEXT_ONLY                         0x81
/**Reply-charging-value:Accepted*/
#define CHARGING_REQUESTED_ACCEPTED                          0x82
/**Reply-charging-value:Accepted text only*/
#define CHARING_REQUESTED_ACCEPTED_TEXT_ONLY                 0x83

/*@}*/

/*not useful , only remain for different version*/
#define RESERVE_OK                                           0x80
#define ERROR_UNSUPPORTED_MESSAGE                            0x88
#define ERROR_TRANSIENT_FAILURE                              0xC0
#define ERROR_TRANSIENT_SENDING_ADDRESS_UNRESOLVED           0xC1
#define ERROR_TRANSIENT_MESSAGE_NOT_FOUND                    0xC2
#define ERROR_TRANSIENT_NETWORK_PROBLEM                      0xC3
#define ERROR_TRANSIENT_PARTIAL_SUCCESS                      0xC5
#define ERROR_PERMANENT_FAILURE                              0xE0
#define ERROR_PERMANENT_SERVICE_DENIED                       0xE1
#define ERROR_PERMANENT_MESSAGE_FORMAT_CORRUPT               0xE2
#define ERROR_PERMANENT_SENDING_ADDRESS_UNRESOLVED           0xE3
#define ERROR_PERMANENT_MESSAGE_NOT_FOUND                    0xE4
#define ERROR_PERMANENT_CONTENT_NOT_ACCEPTED                 0xE5
#define ERROR_PERMANENT_REPLY_CHARGING_LIMITATIONS_NOT_MET   0xE6
#define ERROR_PERMANENT_REPLY_CHARGING_REQUEST_NOT_ACCEPTED  0xE7
#define ERROR_PERMANENT_REPLY_CHARGING_FORWARDING_DENIED     0xE8
#define ERROR_PERMANENT_REPLY_CHARGING_NOT_SUPPORTED         0xE9
#define ERROR_PERMANENT_ADDRESS_HIDING_NOT_SUPPORTED         0xEA

/*not useful , only remain for different version*/
#define MMS_SUCCESS                                          0
#define MMS_ERROR_MALLOC_FAIL                                -1
#define MMS_LOAD_REQUEST_ERROR                               -2
#define MMS_RECEIVE_CONTENT_FAIL                             -3
#define MMS_RECEIVED_PARSE_ERROR                             -4
#define MMS_SEND_ERROR                                       -5
#define MMS_SEND_ACK_FAIL                                    -6
#define MMS_RECEIVED_HTTP_ERROR                              -7
#define MMS_RECEIVED_HTTP_CANNOT_FOUND                       -8
#define MMS_RECEIVED_HTTP_BAD_REQUEST                        -9
#define MMS_RECEIVED_HTTP_INTERNAL_SERVER_ERROR              -10
#define MMS_RECEIVED_HTTP_BAD_GATEWAY                        -11
#define MMS_RECEIVED_HTTP_GATEWAY_TIMEOUT                    -12
#define MMS_HTTP_OPERATION_FORBIDDEN                         -13
#define MMS_SEND_NOTIFY_RESPONSE_FAIL                        -14
#define MMS_SEND_CONF_STATUS_ERROR                           -15
#define MMS_PARAMETERS_ERROR                                 -20
#define MMS_WAP_IS_BUSY                                      -21
#define MMS_WAP_SEND_DATA_FAIL                               -22

/**
   *=======Structured types that are used by protocol module=======
   */

/**
   *    \name   define some structures that are used by fnMMS_*** functions.
   */

/*@{*/

/**
 * structure for mm flag action
 */
typedef enum T_MM_FLAG_ACTION {
    NoneFlag = 0,
    Add,
    Remove,
    Filter
} T_MM_FLAG_ACTION;

/**
 * indicates that MMS Client is requesting a total count of messages currently  stored in mmbox
 */
typedef struct T_Mms_Totals_Value {
    int32_t TotalNumber;
    int32_t TotalSize;
    int32_t Value;
} T_Mms_Totals_Value;

/**
 * indicates tha mms client is requesting an indication of the quotas defined for user's mmbox
 */
typedef struct T_Mms_Quotas_Value {
    int32_t MessagesQuota;
    int32_t SizeQuota;
    int32_t Value;
} T_Mms_Quotas_Value;

/**
 * Structure Type that defines some informations of M-Send.req PDU
 */
typedef struct T_MMS_Send_Request {
    /**
       *Specifies whether the originator MMS Client requests adelivery report from each recipient.
       */
    int32_t Delivery_Report;
    /**
       *Specifies whether the originator MMS Client wants a read report from each recipient
       */
    int32_t Read_Reply;
    /**
       *The originator of the MM may include her wish to show or hide her address.
       */
    int32_t Sender_Visibility;
    /**
       *A unique identifier for the PDU. This transaction ID identifies the M-Send.req
       *and the corresponding reply only.
       */
    int8_t *Transaction_Id;
    /**
       *Address of the recipient.
       */
    int8_t *To;
    /**
       *Address of the recipient.
       */
    int8_t *Cc;
    /**
       *Address of the recipient.
       */
    int8_t *Bcc;
    /**
       *Subject of the MM.
       */
    int8_t *Subject;
    /**
       *MMS Body PDU
       */
    uint8_t *ContentTypeAndBody;
    /**
       *Length of time the MM will be stored in MMS Proxy-Relay or time to delete the MM.
       *The field has two formats, either absolute or relative.
       */
    int32_t MMS_Expiry;
    /**
       *Time of desired delivery. Indicates the earliest possible delivery of the MM to the
       *recipient. The field has two formats, either absolute or relative.
       */
    int32_t MMS_Delivery_Time;
    /**
       *Priority of the MM assigned by the originator MMS Client
       */
    int32_t MMS_Priority;
    /**
       *Class of the MM. Value Auto indicates a MM that is automatically generated by the client.
       *If the field value is Auto, then the originating terminal SHALL NOT request Delivery-Report or Read-Report.
       */
    int32_t MMS_MessageClass;
    /**the length of MM Body*/
    int32_t ContentTypeAndBody_Len;
} T_MMS_Send_Request;

/**
 * Structure Type that defines some informations of M_Send.conf PDU
 */
typedef struct T_MMS_Send_Conf {
    /**
       *Specifies the PDU type.
       */
    uint8_t Message_Type;
    /**
       *The MMS version number.
       */
    uint8_t MMS_Version;
    /**
       *MMS specific status.
       */
    uint8_t Response_Status;
    uint8_t Boundary;
    /**
       *This transaction ID identifies the M-Send.conf and the corresponding M-Send.req only.
       */
    int8_t *Transaction_Id;
    /**
       *Description which qualifies the Response-status-value.
       */
    int8_t *Response_Text;
    /**
       *This is a unique reference assigned to the MM. This ID SHALL always be present after the MMS Proxy-Relay
       *accepted the corresponding M-Send.req PDU.
       */
    int8_t *Message_Id;
} T_MMS_Send_Conf;

/**
 * Structure Type that defines some informations of M-Forward.req PDU
 */
typedef struct T_MMS_Forward_Request {
    /**
       *A unique identifier for the forward transaction that provides linkage between the M-Forward.req and
       *corresponding M-Forward.conf message.
       */
    int8_t *Transaction_Id;
    /**
       *Address of the recipient.
       */
    int8_t *To;
    /**
       *Address of the recipient.
       */
    int8_t *Cc;
    /**
       *Address of the recipient.
       */
    int8_t *Bcc;
    /**
       *Address of the MMS Client that requests forwarding of the message
       */
    int8_t *From;
    /**
       *Period of time the message will be stored in MMS Proxy-Relay or time to delete the message. The field has
       *two formats, either absolute or relative.
       */
    int32_t MMS_Expiry;
    /**
       *Time of desired delivery. Indicates the earliest possible delivery of the message to the recipient. The field has
       *two formats, either absolute or relative.
       */
    int32_t MMS_Delivery_Time;
    /**
       *Sending of delivery report allowed to the previous sender of the message to be forwarded.
       */
    int32_t Report_allowed;
    /**
       *Specifies whether the user wants a delivery report from each recipient.
       */
    int32_t Delivery_Report;
    /**
       *Specifies whether the user wants a read report from each recipient.
       */
    int32_t Read_Report;
    /**
       *Specifies whether the originator MMS Client wants the submitted MM to be saved in the user's MMBox, in
       *addition to sending it.
       */
    int32_t MMS_Store;
    /**
       *Specifies a keyword to add or detract from the list of keywords associated with a stored MM, if X-Mms-Store
       *is present and its value is Yes. If the MMBox is not supported by the MMS Proxy-Relay then this field
       *SHOULD be ignored.
       */
    int8_t *MMS_Flags;
    /**
      *This field specifies the location of the message to be forwarded, as received in the M-Notification.ind
      *message.
      */
    int8_t *Content_Location;
} T_MMS_Forward_Request;

/**
 * Structure Type that defines some informations of M_NotifyResp.ind PDU
 */
typedef struct T_MMS_NotifyResp_Ind {
    /**
       *Specifies the PDU type.
       */
    uint8_t Message_Type;
    /**
       *The MMS version number.
       */
    uint8_t MMS_Version;
    /**
       *Message status. The status Retrieved SHALL be used only after successful retrieval of the MM.
       */
    uint8_t MMS_Status;
    /**
       *Indication whether or not the sending of delivery report is allowed by the recipient MMS Client.
       */
    uint8_t Report_Allowed;
    /**
       *Identifies the transaction started by MNotification.ind PDU.
       */
    int8_t *Transaction_Id;
} T_MMS_NotifyResp_Ind;

/**
 * Structure Type that defines some informations of M_Acknowledge.ind PDU
 */
typedef struct T_MMS_Acknowledge_Ind {
    /**
       *Specifies the PDU type.
       */
    uint8_t Message_Type;
    /**
       *The MMS version number.
       */
    uint8_t MMS_Version;
    /**
       *Sending of delivery report allowed to the user.
       */
    uint8_t Report_Allowed;
    /**
       *
       */
    uint8_t Boundary;           /* for align */
    /**
       *This transaction ID identifies the M-Acknowledge.ind PDU and the corresponding M-Retrieve.conf PDU
       */
    int8_t *Transaction_Id;
} T_MMS_Acknowledge_Ind;

/**
 * Structure Type that defines some informations of M-Mbox-Store.req PDU
 */
typedef struct T_MMS_BoxStore_Request {
    /**
       *A unique identifier for the store/update transaction that provides linkage between the M-Mbox-Store.req and
       *corresponding M-Mbox-Store.conf PDUs. It originates from the M-Mbox-Store.req PDU.
       */
    int8_t *Transaction_Id;
    /**
       *This field specifies the location of the message to be stored or updated. This reference is obtained from either
       *the M-Notification.ind, M-Mbox-View.conf, or any transaction that stored a message to the user's MMBox.
       */
    int8_t *Content_Location;
    /**
       *The new value to give the state of the stored message.If X-Mms-Content-Location refers to a message to be
       *stored (i.e. a message reference that was obtained from an M-Notification.ind) then this shall default to New.
       *Otherwise, there is no default value.
       */
    int32_t MM_State;
    /**
       *Add,Remove,Filter
       */
    T_MM_FLAG_ACTION MM_Flags_action;
    /**
       *The keyword values to add or detract to the MM Flags of the stored message. There is no default.
       */
    int8_t *MM_Flags;
} T_MMS_BoxStore_Request;

/**
 * Structure Type that defines some informations of M-Mbox-View.req PDU
 */
typedef struct T_MMS_BoxView_Request {
    /**
       *A unique identifier for the viewing transaction that provides linkage between the M-Mbox-View.req and
       *corresponding M-Mbox-View.conf PDU.
       */
    int8_t *Transaction_Id;
    /**
       *A message reference obtained from any transaction that stored a message to the MMBox or a previous result
       *from the M-Mbox-View.conf. Attributes of the specific message that is referenced should be returned.
       */
    int8_t *Content_Location;
    /**
       *Specifies a MM State value to use in selecting the messages to return their information.
       */
    int32_t MM_State;
    /**
       *Specifies a MM Flags keyword to use in selecting the messages to return their information.
       */
    T_MM_FLAG_ACTION MM_Flags_action;
    /**
       *Specifies a MM Flags keyword to use in selecting the messages to return their information.
       */
    int8_t *MM_Flags;
    /**
       *A number, indicating the index of the first MM of those selected to have information returned in the response. If
       *this is absent, the first item selected SHALL be returned.
       */
    int32_t MMS_Start;
    /**
       *A number indicating the maximum number of selected MMs whose information SHALL be returned in the response.
       */
    int32_t MMS_Limit;
    /**
       *A list of information elements that should appear in the view for each selected message. If this field does not
       *appear then MMS Proxy-Relay SHOULD use a system default. If no system default is defined then the subset of
       *message fields that appear in the M-Notification.ind PDU SHALL be used.
       */
    int32_t MMS_Attributes;
    /**
       *Indicates that MMS Client is requesting a total count of messages currently stored in MMBox. Default is No.
       */
    int32_t MMS_Totals;
    /**
       *Indicates that MMS Client is requesting an indication of the quotas defined for user's MMBox. Default is No.
       */
    int32_t MMS_Quotas;
} T_MMS_BoxView_Request;

/**
 * Structure Type that defines some informations of M-Mbox-Upload.req PDU
 */
typedef struct T_MMS_BoxUpload_Request {
    /**
       *A unique identifier for the upload transaction that provides linkage between the M-Mbox-Upload.req and
       *corresponding M-Mbox-Upload.conf PDU.
       */
    int8_t *Transaction_Id;
    /**
       *Specifies the value to set in the MM State field of the stored MM. If the field does not appear then the MM
       *State defined in the M-Mbox-Descr PDU SHOULD be used. If no MM State appears in either this PDU or the
       *M-Mbox-Descr PDU then the value SHALL default to Draft.
       */
    int32_t MM_State;
    T_MM_FLAG_ACTION MM_Flags_action;
    /**
       *Specifies a keyword to add or delete from the list of keywords associated with a stored MM.
       */
    int8_t *MM_Flags;
    /**
       *the length of MM body
       */
    int32_t ContentTypeAndBody_Len;
    /**
       *MM Body
       */
    uint8_t *ContentTypeAndBody;        /**<MM body*/
} T_MMS_BoxUpload_Request;

/**
 * Structure Type that defines some informations of M-Mbox-Delete.req PDU
 */
typedef struct T_MMS_BoxDelete_Request {
    /**
       *A unique identifier for the deleting transaction that provides linkage between the M-Mbox-Delete.req and
       *corresponding M-Mbox-Delete.conf PDUs.
       */
    int8_t *Transaction_Id;
    /**
       *Specifies a reference to the stored MM that was obtained from any of the storing PDU, M-Notification.ind, or MMbox-
       *View.conf
       */
    int8_t *Content_Location;
} T_MMS_BoxDelete_Request;

/**
 * Structure Type that defines some informations of M_Notificaton.ind  PDU
 */
typedef struct T_MMS_Notification_Ind {
    /**
       *Class of the message.The MMS Proxy-Relay MUST provide the Personalmessage class if the original submission did not include
       *the X-Mms-Message-Class field.
       */
    uint8_t Message_Class;
    /**
       * The field has only one format, relative
       */
    uint8_t MMS_Expiry_TimeType;
    /**
       *Priority of the MM.
       */
    uint8_t MMS_Prioity;
    /**
       *If this field is present its value is set to"accepted" or "accepted text only"  and the MMS-version-value of the
       *M-Notification.ind PDU is higher than 1.0, this header field will indicate that a reply to this particular MM is
       *free of charge for the recipient.If the Reply-Charging service is offered and the request
       *for reply-charging has been accepted by the MMS service provider the value of this header field SHALL be
       *set to "accepted" or "accepted text only".
       */
    uint8_t Reply_charging;
    /**
       *This header field SHALL NOT be present if the X-Mms-Reply-Charging header field is not present.
       */
    uint8_t Charging_Deadline_Type;
    uint8_t Boundary[3];
    /**
       *Specifies whether the user wants a delivery report from each recipient. The absence of the field does not indicate
       *any default value.
       */
    int32_t Delivery_Report;
    /**
       *Size of the MM as defined in [TS23140] for 3GPP and [XS0016200] for 3GPP2.
       */
    int32_t Message_Size;
    /**
       *Length of time the message will be available. The field has only one format, relative.
       */
    int32_t MMS_Expiry;
    /**
       *This header field SHALL NOT be present if the X-Mms-Reply-Charging header field is not present.
       */
    int32_t Charging_Deadline;
    /**
       *This header field SHALL NOT be present if the X-Mms-Reply-Charging header field is not present. It specifies
       *the maximum size (number of octets) for the Reply-MM
       */
    int32_t Reply_Charging_Size;
    /**
       *This header field SHALL only be present in PDUs that notify a recipient about a Reply-MM.
       */
    int8_t *Reply_Charging_ID;
    /**
       *This transaction ID identifies the M-Notification.ind and the corresponding M-NotifyResp.ind
       */
    int8_t *Transaction_Id;
    /**
       *Address of the last MMS Client that handled the MM,
       */
    int8_t *From;
    /**
       *Subject of the message.
       */
    int8_t *Subject;
    /**
       *This field defines the location of the MM to be retrieved.
       */
    int8_t *Content_Location;
} T_MMS_Notification_Ind;

/**
 * Structure Type that defines some informations of M_Retrieve.conf PDU
 */
typedef struct T_MMS_Retrieve_Conf {
    /**
       *Specifies whether the originator MMS Client requested a delivery report from each recipient.
       */
    int32_t Delivery_Report;
    /**
       *Specifies whether the originator MMS Client wants a read report from each recipient as a new message
       */
    int32_t Read_Reply;
    /**
       *Message class. If field is not present, the receiver interprets the MM as personal.
       */
    uint8_t Message_Class;
    uint8_t MMS_Prioity;            /**<Priority of the MM.*/
    uint8_t Retrived_Status;            /**<MMS specific status.*/
    /**
       *If this field is present its value is set to "accepted" or "accepted text only" and the MMS-version-value of the
       *M-Retrieve.conf PDU is higher than 1.0, this header field indicates that a reply to this particular MM is free
       *of charge for the recipient. If the Reply-Charging service is offered and the request for reply-charging has been accepted by the MMS
       *service provider the value of this header field SHALL be set to "accepted" or "accepted text only".
       */
    uint8_t Reply_charging;
    uint8_t Charging_Deadline_Type;
                                   /**<*/
    uint8_t Boundary[3];

    int32_t Date;                   /**<Date and time of latest submission or forwarding of the message by an MMS Client or reception of the MMS Proxy-Relay.*/
    int32_t Content_Size;           /**<This field shall only appear for an MM that is retrieved from the MMBox*/
    int32_t Charging_Deadline;      /**<This header field SHALL NOT be present if the X-Mms-Reply-Charging header field is not present.*/
    int32_t Reply_Charging_Size;    /**<It specifies the maximum size (number of octets) for the Reply-MM.*/
    int8_t *Reply_Charging_ID;      /**<The value of this header field SHALL be the same as the Message-ID of the Original-MM that is replied to.*/
    int8_t *pRetrived_Status_Txt;
                                    /**<Description which qualifies the retrieve status value.*/
    uint8_t *ContentTypeAndBody;    /**<MM Body Buffer*/
    int8_t *Transaction_Id;         /**<Identifies either the transaction that has been started by M-Notification.ind PDU without M-NotifyResp.ind PDU (immediate retrieval) or a new transaction when deferred retrieval was requested*/
    int8_t *Message_Id;             /**<This is an unique reference assigned to the MM.*/
    int8_t *From;                   /**<Address of the last MMS Client that handled the MM,*/
    int8_t *To;                     /**<Address of the recipient.*/
    int8_t *Cc;                     /**<Address of the recipient.*/
    int8_t *Subject;                    /**<Message subject*/
    int8_t *Previously_sender;      /**<Address of the MMS Client that forwarded or originally sent the message and a sequence number*/
    int8_t *PreviouslySentDate;     /**<Date and time of a forwarding or original send transaction of the message and a sequence number.*/
} T_MMS_Retrieve_Conf;

/**
 * Structure Type that defines some informations of M_Delivery.ind PDU
 */
typedef struct T_MMS_Delivery_Ind {
    uint8_t MMS_Status;             /**<The status of the message.*/
    uint8_t Boundary[3];                /**<*/
    int8_t *Message_Id;             /**<The ID enables an MMS Client to match delivery reports with previously sent or forwarded MMs.*/
    int8_t *To;                     /**<Needed for reporting in case of point-to-multipoint message.*/
    int32_t Date;                   /**<Date and time the message was handled (fetched, expired, etc.) by the recipient or MMS Proxy-Relay.*/
} T_MMS_Delivery_Ind;

/**
 * Structure Type that defines some informations of M_Read_Orig.ind PDU
 */
typedef struct T_MMS_Read_Orig_Ind {
    uint8_t Message_Type;           /**<Identifies the PDU type*/
    uint8_t MMS_Version;            /**<The MMS version number. According to this specification, the version is 1.2*/
    uint8_t Boundary[2];                /**<*/
    int8_t *Message_Id;             /**<The ID enables an MMS Client to match read report PDUs with previously sent or forwarded MMs.*/
    int8_t *To;                     /**<The address of the recipient of the Read Report, i.e. the originator of the original multimedia message.*/
    int8_t *From;                   /**<The insert-address-token MUST NOT be used as the value of the field.*/
    int32_t Date;                   /**<Time the message was handled by the recipient MMS Client.*/
    int32_t ReadStatus;                 /**<The status of the message.*/
} T_MMS_Read_Orig_Ind;

/**
 * Structure Type that defines some informations of M_Read_Rec.ind PDU
 */
typedef struct T_MMS_Read_Rec_Ind {
    uint8_t Message_Type;           /**<Identifies the PDU type*/
    uint8_t MMS_Version;            /**<The MMS version number. According to this specification, the version is 1.2*/
    uint8_t Boundary[2];                /**<*/
    int8_t *Message_Id;             /**<The ID enables an MMS Client to match read report PDUs with previously sent or forwarded MMs.*/
    int8_t *To;                     /**<The address of the recipient of the Read Report, i.e. the originator of the original multimedia message.*/
    int8_t *From;                   /**<The insert-address-token MUST NOT be used as the value of the field.*/
    int32_t Date;                   /**<Time the message was handled by the recipient MMS Client.*/
    int32_t ReadStatus;                 /**<The status of the message.*/
} T_MMS_Read_Rec_Ind;

/**
 * Structure Type that defines some informations of M_Forward.conf PDU
 */
typedef struct T_MMS_Forward_Conf {
    uint8_t Message_Type;           /**<Specifies the PDU type.*/
    uint8_t MMS_Version;            /**<The MMS version number. According to this specification, the version is 1.2*/
    uint8_t Boundary[2];                /**<*/
    int8_t *Transaction_Id;         /**<A unique identifier for the forward transaction that provides linkage between the M-Forward.req and corresponding M-Forward.conf PDU.*/
    int8_t *Message_Id;             /**<This is a unique reference assigned to message.*/
    int32_t Response_Status;        /**<MMS specific status.*/
    int8_t *Response_Text;          /**<Description which qualifies the response status value*/
    /**
       *This field SHALL appear only if the MMS Proxy-Relay supports the MMBox feature - the X-Mms-Store field
       *was present in the M-Forward.req and X-Mms-Store-Status indicates Success.If X-Mms-Content-Location appears then this specifies a
       *reference to the stored version of the MM that can be retrieved or can be used to obtain information about the MM using the M-Retrieve.req or M-Mbox-View.req.
       */
    int8_t *Content_Location;
    int32_t Mms_Store_Status;       /**<If the field appears it indicates if the submitted MM was successfully stored into the MMBox.*/
    int8_t *Mms_Store_Status_Text;
                                    /**<Description that qualifies the X- Mms-Store-Status field*/
} T_MMS_Forward_Conf;

/**
 * Structure Type that defines some informations of M_Mbox_Store.conf PDU
 */
typedef struct T_M_MBOX_STORE_CONF {
    int8_t *Transaction_Id;         /**<A unique identifier for the store/update transaction*/
    int8_t *Content_Location;       /**<This field SHALL appear only if X-Mms-Store-Status indicates Success.*/
    int32_t Mms_Store_Status;       /**<The status of the store/update request.*/
    int8_t *Mms_Store_Status_Text;
                                    /**<Description which qualifies the X-Mms-Store-Status.*/
} T_M_MBOX_STORE_CONF;

/**
 * Structure Type that defines some informations of M-Mbox-View.conf PDU
 */
typedef struct T_M_MBOX_VIEW_CONF {
    int8_t *Transaction_Id;             /**<Transaction ID*/
    int32_t Response_Status;            /**<Response_Status*/
    int8_t *Response_Text;              /**<Description that qualifies the Response-status-value.*/
    int8_t *Content_Location;           /**<The list of MM that were specified in the corresponding request.*/
    int32_t MM_State;                   /**<to set in the mm state field of the stored mm*/
    T_MM_FLAG_ACTION MM_Flags_action;
                                        /**<Add | Remove | Filter */
    int8_t *MM_Flags;                   /**<specify the keyword to add or detract from the list of keywords associated with a stored mm*/
    int32_t MMS_Start;                  /**<a number ,indicating the index of the first MM of those selected*/
    int32_t MMS_Limit;                  /**<a number indicating the maximum number of selected MMS*/
    int32_t MMS_Attributes;
    T_Mms_Totals_Value MMS_Totals;      /**<indicates that MMS Client is requesting a total count of messages currently stored in mmbox*/
    T_Mms_Quotas_Value MMS_Quotas;      /**<indicates tha mms client is requesting an indication of the quotas defined for user's mmbox*/
    int32_t MMS_Message_Count;          /**<Number of messages listed in content of the pdu*/
    int32_t Content_Size;
    uint8_t *ContentTypeAndBody;
} T_M_MBOX_VIEW_CONF;

/**
 * Structure Type that defines some informations of M-Mbox-Upload.conf PDU
 */
typedef struct T_M_MBOX_UPLOAD_CONF {
    int8_t *Transaction_Id;             /**<A unique identifier for the upload transaction that provides linkage between the M-Mbox-Upload.req and corresponding M-Mbox-Upload.conf PDUs.*/
    int8_t *Content_Location;           /**<Specifies a reference to the stored version of the MM that can be retrieved or can be used to obtain information about the MM using the M-Mbox-View.req.*/
    int32_t Mms_Store_Status;           /**<Indicates if the submitted MM was successfully stored into the MMBox.*/
    int8_t *Mms_Store_Status_Text;      /**<Description that qualifies the X- Mms-Store-Status field value.*/
} T_M_MBOX_UPLOAD_CONF;

/**
 * Structure Type that defines some informations of M-Mbox-Delete.conf PDU
 */
typedef struct T_M_MBOX_Delete_CONF {
    int8_t *Transaction_Id;             /**<A unique identifier for the deleting transaction that provides linkage between the M-Mbox-Delete.req and corresponding M-Mbox-Delete.conf PDUs.*/
    int8_t *Content_Location;           /**<Specifies a reference to the MM that was not successfully deleted.*/
    int32_t Response_Status;            /**<Indicates the status of the MM deletion operation*/
    int8_t *Response_Text;              /**<Descriptive text that qualifies the Response-status-value.*/
} T_M_MBOX_Delete_CONF;

/**
 * Structure Type that defines some informations of M-Mbox-Descr PDU
 */
typedef struct T_M_MBOX_Descr_Pdu {
    int8_t *Content_Location;           /**<This field shall only be used in conjunction with the M-Mbox-View.conf PDU.*/
    int8_t *Message_Id;                 /**<This field SHALL be present when included in the MMbox-View.conf PDU.*/
    int32_t MMS_Start;                  /**<a number ,indicating the index of the first MM of those selected*/
    T_MM_FLAG_ACTION MM_Flags_action;
                                        /**<Add | Remove | Filter */
    int8_t *MM_Flags;                   /**<specify the keyword to add or detract from the list of keywords associated with a stored mm*/
    int32_t Date;                       /**<This value SHALL appear only if requested as part of the Attributes-list in the request and is present in the associated MM.*/
    /**
       *This value SHALL appear only if requested as part of the Attributes-list in the request and is present in the associated MM. Note- the "Insert-address-token"is a
       *valid value but no meaning should be attached to this value
       */
    int8_t *From;
    int8_t *To;                         /**<This header field MAY appear multiple times.*/
    int8_t *Cc;                         /**<This header field MAY appear multiple times.*/
    int8_t *Bcc;                            /**<This header field MAY appear multiple times.*/
    int8_t *Subject;                        /**<This value SHALL appear only if requested as part of the Attributes-list in the request and is present in the associated MM.*/
    uint8_t Message_Class;              /**<This value SHALL appear only if requested as part of the Attributes-list in the request and is present in the associated MM.*/
    uint8_t MMS_Prioity;                /**<This value SHALL appear only if requested as part of the Attributes-list in the request and is present in the associated MM.*/
    uint8_t Boundary[2];                /**<*/
    int32_t MMS_Expiry;                     /**< expiry time,default use Relative-token value */
    int32_t MMS_Delivery_Time;          /**<Delivery time,default use Relative-token value  */
    int32_t Delivery_Report;                /**<This value SHALL appear only if requested as part of the Attributes-list in the request and is present in the associated MM.*/
    int32_t Read_Report;                /**<This value SHALL appear only if requested as part of the Attributes-list in the request and is present in the associated MM.*/
    int32_t Message_Size;               /**<This value SHALL appear only if requested as part of the Attributes-list in the request.*/
    uint32_t Reply_charging_value;          /**<This value SHALL appear only if requested as part of the Attributes-list in the request and is present in the associated MM.*/
    int32_t Reply_charging_deadline;        /**<Reply-charging-deadline-value*/
    uint8_t *Reply_Charging_ID;             /**<X-Mms-Reply-Charging-ID field*/
    int32_t Reply_Charging_Size;            /**<Reply-charging-size-value*/
    uint8_t *Previously_sent_by_value;      /**<X-Mms-Previously-Sent-By field*/
    int32_t Previously_sent_date_value;     /**<Previously-sent-date-value*/
    int32_t Content_Size;
    uint8_t *ContentTypeAndBody;
} T_M_MBOX_Descr_Pdu;
/*@}*/

/**
   *======= define Protocol Module APIs=======
   */
/**
   *    \name   some functions that will be used by protocol module.
   */

/*@{*/

/**
 * Encode the sendrequest struct into binary data.
 * \param  *Msg        the MM's struct of m-send.req.
 * \param  *length     the length of the pdu.
 * \return <ul>
 *             <li> pdu buffer's pointer            if success
 *             <li> NULL                    if failed
 *         </ul>
 *
 */
uint8_t *NCCMms_prot_makeSendMessagePdu(T_MMS_Send_Request * Msg,
                                        int32_t * length);

/**
 * According to the message struct type to alloc mem for the message.
 * \param  Type        the struct type value
 * \return <ul>
 *                <li> address of the struct            if success
 *                <li> NULL                 if failed
 *         </ul>
 */
void *NCCMms_prot_allocMessageMem(uint8_t Type);

/**
 * According to the message struct type to free the mem used by the message struct
 * \param  *pAddr      the address of the mem which will be freed.
 * \param  Type        the struct type value
 * \return void
 */
void NCCMms_prot_freeMessageMem(void *pAddr, uint8_t Type);

/**
 * Receive the notification information from the proxy relay
 * \param  *Buf            the push content data  pointer.
 * \param  Content_len the buf's length
 * \return <ul>
 *                <li> notificaiton ind struct pointer      if success
 *                <li> NULL                 if failed
 *         </ul>
 */
T_MMS_Notification_Ind *NCCMms_prot_parseNotificationInd(uint8_t * Buf,
                                                         int32_t Content_len);

/**
 * Parse M-Send.conf pdu and return a struct
 * \param  *Buf            the point of the M-Send.conf pdu
 * \param  Content_len the length of M-Send.conf pdu
 * \return <ul>
 *             <li> point of T_MMS_Send_Conf struct     if success
 *             <li> NULL                    if failed
 *         </ul>
 * \sa NCCMms_prot_recvSendConfData
 */
T_MMS_Send_Conf *NCCMms_prot_parseSendConf(uint8_t * Buf, int32_t Content_len);

/**
 * Parse M-Retrieve.conf PDU into M-Retrieve.conf struct
 * \param  *Buf            the encode MM data content's pointer
 * \param  Content_len the length of the pdu
 * \return <ul>
 *                <li> retrieve.conf struct pointer     if success
 *                <li> NULL                 if failed
 *         </ul>
 */
T_MMS_Retrieve_Conf *NCCMms_prot_parseRetrieveConf(uint8_t * Buf,
                                                   int32_t Content_len);

/**
 * Receive the delivery Indication from the proxy relay .
 * \param  *Buf            the push content data filed's pointer
 * \param  Content_len the length of the pdu
 * \return <ul>
 *                <li> deliver ind struct pointer       if success
 *                <li> NULL                 if failed
 *         </ul>
 */
T_MMS_Delivery_Ind *NCCMms_prot_parseDeliveryInd(uint8_t * Buf,
                                                 int32_t Content_len);

/**
 * Receive the read-orig Indication from the proxy relay .
 * \param  *Buf            the push content data filed's pointer
 * \param  Content_len the lenght of the pdu
 * \return <ul>
 *                <li> deliver ind struct pointer       if success
 *                <li> NULL                 if failed
 *         </ul>
 */
T_MMS_Read_Orig_Ind *NCCMms_prot_parseReadOrigInd(uint8_t * Buf,
                                                  int32_t Content_len);

/**
 * Receive the forward-conf Indication from the proxy relay .
 * \param  *Buf            the push content data filed's pointer
 * \param  Content_len the length of the pdu
 * \return <ul>
 *                <li> deliver ind struct pointer       if success
 *                <li> NULL                 if failed
 *         </ul>
 */
T_MMS_Forward_Conf *NCCMms_prot_parseForwardConf(uint8_t * Buf,
                                                 int32_t Content_len);

/**
 * Receive the  m-mbox-store.con  from the proxy relay .
 * \param  *Buf            the push content data filed's pointer
 * \param  Content_len the length of the pdu
 * \return <ul>
 *                <li> m-mbox-store.conf struct pointer     if success
 *                <li> NULL                 if failed
 *         </ul>
 */
T_M_MBOX_STORE_CONF *NCCMms_prot_parseMBoxStoreConf(uint8_t * Buf,
                                                    int32_t Content_len);

/**
 * Receive the  m-mbox-store.con  from the proxy relay .
 * \param  *Buf            the push content data filed's pointer
 * \param  Content_len the length of the push content data
 * \return <ul>
 *                <li> m-mbox-view.conf struct pointer      if success
 *                <li> #NULL                    if failed
 *         </ul>
 */
T_M_MBOX_VIEW_CONF *NCCMms_prot_parseMBoxViewConf(uint8_t * Buf,
                                                 int32_t Content_len);

/**
 * Receive the  m-mbox-Upload.con  from the proxy relay .
 * \param  *Buf            the push content data filed's pointer
 * \param  Content_len the length of the push content data
 * \return <ul>
 *                <li> the m-mbox-view.conf struct pointer  if success
 *                <li> #NULL                    if failed
 *         </ul>
 */
T_M_MBOX_UPLOAD_CONF *NCCMms_prot_parseMBoxUploadConf(uint8_t * Buf,
                                                      int32_t Content_len);

/**
 * Receive the  m-mbox-Delete.con  from the proxy relay .
 * \param  *Buf            the content data filed's pointer.
 * \param  Content_len the length of the push content data
 * \return <ul>
 *                <li> the m-mbox-Delete.conf struct pointer    if success
 *                <li> #NULL                    if failed
 *         </ul>
 */
T_M_MBOX_Delete_CONF *NCCMms_prot_parseMBoxDeleteConf(uint8_t * Buf,
                                                      int32_t Content_len);

/**
 * Receive the  m-mbox-Descr  from the proxy relay .
 * \param  *Buf            the content data filed's pointer.
 * \param  Content_len the length of the push content data
 * \return <ul>
 *                <li> the m-mbox-Descr struct pointer      if success
 *                <li> #NULL                    if failed
 *         </ul>
 */
T_M_MBOX_Descr_Pdu *NCCMms_prot_parseMBoxDescrPdu(uint8_t * Buf,
                                                  int32_t Content_len);

/**
 * Encode the notify response pdu.
 * \param  *Trans_ID   the ID of notification
 * \param  SendDevRep  whether to send thd delivery ind
 * \param  Status       the status of the mms.
 * \param  *len    the length of the pdu.
 * \return <ul>
 *                <li> the pdu buffer's pointer     if success
 *                <li> #NULL                if failed
 *         </ul>
 */
uint8_t *NCCMms_prot_makeNotifyRespPdu(int8_t * Trans_ID,
                                       int32_t SendDevRep, uint8_t Status,
                                       int32_t * len);

/**
 * Encode the acknowledge pdu
 * \param  *Trans_Id   the Id of notification
 * \param  SendDevRep  whether to send the delivery ind
 * \param  *len            the length of acknowledge pdu.
 * \return <ul>
 *                <li> the pdu buffer's pointer     if success
 *                <li> #NULL                if failed
 *         </ul>
 */
uint8_t *NCCMms_prot_makeAcknowledgePdu(int8_t * Trans_Id,
                                        int32_t SendDevRep, int32_t * len);

/**
 * Encode the mms read report pdu
 * \param  *Trans_Id   the Id of new mm
 * \param  *From       the sender of the received mm
 * \param  *Subject        the subject of the received mm
 * \param  *len            the length of read report pdu in form of mms
 * \return <ul>
 *                <li> the read report pdu buffer's pointer if success
 *                <li> #NULL                    if failed
 *         </ul>
 */
uint8_t *NCCMms_prot_makeReadReportPdu(int8_t * Trans_Id, int8_t * From,
                                       int8_t * Subject, int32_t * len);

/**
 * Encode the PDU read report .
 * \param  *Message_Id     the Id of new mm .
 * \param  *From           the sender of the received mm .
 * \param  ReadFlag            the subject of the received mm.
 * \param  *len                the length of read report in form of PDU
 * \return <ul>
 *                <li> the read report pdu buffer's pointer if success
 *                <li> #NULL                    if failed
 *         </ul>
 */
uint8_t *NCCMms_prot_makeReadRecPDU(int8_t * Message_Id, int8_t * From, int32_t ReadFlag,
                                    int32_t * len);

/**
 * Encode the forward message pdu.
 * \param  *Msg        the  mm pdu struct of m-forward.req
 * \param  *length     the length of the pdu.
 * \return <ul>
 *                <li> the pdu buffer's pointer     if success
 *                <li> #NULL                if failed
 *         </ul>
 */
uint8_t *NCCMms_prot_makeForwardingMessagePdu(T_MMS_Forward_Request * Msg,
                                              int32_t * length);

/**
 * Encode the m-m-box-store.req message pdu
 * \param  *Msg        the  mm pdu struct of m-mbox-store.req
 * \param  *length     the length of the pdu.
 * \return <ul>
 *                <li> the pdu buffer's pointer     if success
 *                <li> #NULL                if failed
 *         </ul>
 */
uint8_t *NCCMms_prot_makeBoxStoreMessagePdu(T_MMS_BoxStore_Request * Msg,
                                            int32_t * length);

/**
 * Encode the m-mbox-view.req message pdu
 * \param      *Msg    the  mm pdu struct of m-mbox-view.req
 * \param      *length the length of the pdu
 * \return <ul>
 *                <li> the pdu buffer's pointer     if success
 *                <li> #NULL                if failed
 *         </ul>
  */
uint8_t *NCCMms_prot_makeBoxViewMessagePdu(T_MMS_BoxView_Request * Msg,
                                           int32_t * length);

/**
 * Encode the M-Mbox-Upload.req message pdu
 * \param  *Msg        the  mm pdu struct of M-Mbox-Upload.req
 * \param  *length     the length of the pdu
 * \return <ul>
 *                <li> the pdu buffer's pointer     if success
 *                <li> #NULL                if failed
 *         </ul>
 */
uint8_t *NCCMms_prot_makeBoxUploadReqPdu(T_MMS_BoxUpload_Request * Msg,
                                         int32_t * length);

/**
 * Encode the M-Mbox-Delete.req message pdu
 * \param  *Msg        the  mm pdu struct of M-Mbox-Delete.req
 * \param  *length     the length of the pdu.
 * \return <ul>
 *                <li> the pdu buffer's pointer     if success
 *                <li> #NULL                if failed
 *         </ul>
 */
uint8_t *NCCMms_prot_makeBoxDeleteReqPdu(T_MMS_BoxDelete_Request * Msg,
                                         int32_t * length);

/**
 * Free the pdu buffer which get from fnMMS_Make* Api,these pdu buffer is malloc in protocol module.
 * \param  *pMsgPdu         the message pdu's buffer.
 * \return void
 */
void NCCMms_prot_freeMadeMsgPduBuf(void *pMsgPdu);

/**
 * Deal with the send response data
 * \param  *pData      the received data buffer.
 * \param  Size            the buffer's size.
 * \return <ul>
 *                <li> the send response's status value     if success
 *                <li> #MMS_SEND_RESPONSE_ERROR_FUNCTION_ERROR  if failed
 *            </ul>
 *
 */
int16_t NCCMms_prot_recvSendConfData(uint8_t * pData, int32_t Size);

#ifdef MMS_SUPPORT_JSR205
/**
*Get the application-id and reply-to-application-id parameters for content-type,This requirement is just for JSR205 project.
*  \param  uint8_t *pPduData   the pointer of content-type and body(T_MMS_Retrieve_Conf::ContentTypeAndBody).
*  \param  int32_t DataSize    the length of ContentTypeAndBody(T_MMS_Retrieve_Conf::Content_Size)
*  \param  uint8_t **appId     the pointer of Application-id parameter.The memory don't need to free, Because it doesn't do memory copy.
*  \param  uint8_t **replyToAppId  the pointer of Reply-To-Application-Id parameter.The memory don't need to free, Because it doesn't do memory copy.
*  return
*      <ul>
*          <li>return#TRUE,If successful.
*          <li>return#FALSE,If failed.
*      </ul>
*/
int32_t NCCMms_prot_getAppIdAndReplyAppId(uint8_t *pPduData,
                                          int32_t DataSize,
                                          uint8_t **appId,
                                          uint8_t **replyToAppId,
                                          uint8_t **startContentId);
#endif

/*@}*/

#ifdef __cplusplus
}
#endif

#endif /* __NCC_MMS_PROT_H__ */
