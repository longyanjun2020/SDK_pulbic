/**
* @file nccemail_common.h
* NCC email common Service Layer
*
* Service API exposed by the NCC email common module
*
* <!-- #interface list begin -->
* <!-- #interface list end -->
*/

#ifndef __NCCEMAIL_COMMON_H__
#define __NCCEMAIL_COMMON_H__
#include <ncc_types.h>

/**
* ======= CONSTANTS AND MACROS =======
*/
/*@{*/
#define EMAIL_DEFAULT_POP3_PORT     110
#define EMAIL_DEFAULT_SMTP_PORT     25

/**define the maximum length of server name*/
#define EMAIL_MAX_SERVER_NAME_LEN   64
/**define the maximum length of user name*/
#define EMAIL_MAX_USERNAME_LEN      64
/**define the maximum length of account id*/
#define EMAIL_MAX_ACCOUNTID_LEN     (EMAIL_MAX_SERVER_NAME_LEN + EMAIL_MAX_USERNAME_LEN)
/**define the maximum length of password*/
#define EMAIL_MAX_PASSWORD_LEN      64


/**define the maximum times of retry for FS*/
#define EMAIL_NET_MAX_RETRY_TIMES 3

/**
*    \name Return Values for transfer functions.
*/

/* network result */
/**Return code that indicates successful completion of an operation*/
#define EMAIL_NET_SUCCESS               0
/**Return code that indicates failed completion of an operation*/
#define EMAIL_NET_FAILED                -1
/**Return code that indicates failed because of time out*/
#define EMAIL_NET_TIMEOUT               -3
/**Return code that indicates failure completion of allocating memory*/
#define EMAIL_NET_ALLOC_FAIL            -4
/**Return code that indicates that this operation is successful and need go to next step*/
#define EMAIL_NET_GOON                  -6
/**Return code that indicates that this operation is pending and need do step again*/
#define EMAIL_NET_PENDING              -7
/**Return code that indicates failed because of invalid socket*/
#define EMAIL_NET_SOCKET_INVALID        -8
/**Return code that indicates failed to set the socket to NO block*/
#define EMAIL_NET_CANTSETNOBLOCK        -9
/**Return code that indicates failed to get host by name*/
#define EMAIL_NET_CANTGOTHOSTBYNAME     -10
/**Return code that indicates ERROR status*/
#define EMAIL_NET_STATUS_ERROR          -11
/**Return code that indicates other ERROR*/
#define EMAIL_NET_OTHER_ERROR           -12
/**Return code indicates that param error */
#define EMAIL_NET_PARAMETE_ERROR        -13
/**Return code indicates that fs save error, e.g. disk is full */
#define EMAIL_NET_FSSAVE_ERROR          -14

/**
*    \name define the type for the call back function, the comment describe the parameters means.
*/

/** email call back type */
//ERROR: buf contain the response message
#define EMAIL_CALLBACK_SMTP_ERROR           -100
//CONNECT: buf contain the response message
#define EMAIL_CALLBACK_SMTP_CONNECT         -101
//USER: buf contain the response message
#define EMAIL_CALLBACK_SMTP_USER            -102
//PASS: buf contain the response message
#define EMAIL_CALLBACK_SMTP_PASS            -103

//ERROR: buf contain the response message
#define EMAIL_CALLBACK_POP3_ERROR           -110
//CONNECT: buf contain the response message
#define EMAIL_CALLBACK_POP3_CONNECT         -111
//USER: buf contain the response message
#define EMAIL_CALLBACK_POP3_USER            -112
//PASS: buf contain the response message
#define EMAIL_CALLBACK_POP3_PASS            -113
//STAT: num1 is the message number and num2 is the octet count
#define EMAIL_CALLBACK_POP3_STAT            -114
//TOPSTART: num1 is the message number
#define EMAIL_CALLBACK_POP3_TOPSTART        -115
//TOP: buf is the email header PDU and the len is the PDU length, num1 is the index and str is the uid
#define EMAIL_CALLBACK_POP3_TOP             -116
//UIDLISTSTART: no parameter
#define EMAIL_CALLBACK_POP3_UIDLISTSTART    -117
//UIDLIST: num1 is the message number and buf is the uid string
#define EMAIL_CALLBACK_POP3_UIDLIST         -118
//UIDLOVER: no parameter
#define EMAIL_CALLBACK_POP3_UIDLOVER        -119
//LISTSTART: no parameter
#define EMAIL_CALLBACK_POP3_LISTSTART       -120
//LIST: num1 is the message number and num2 is the octet count
#define EMAIL_CALLBACK_POP3_LIST            -121
//LISTOVER: no parameter
#define EMAIL_CALLBACK_POP3_LISTOVER        -122
//RETRIVESTART: num1 is the message number and num2 is the octet count
#define EMAIL_CALLBACK_POP3_RETRIVESTART    -123
//RETRIVE: buf is the email PDU and the len is the PDU length, num1 is the index and str is the uid
#define EMAIL_CALLBACK_POP3_RETRIVE         -124
//RETRIVEOVER: no parameter
#define EMAIL_CALLBACK_POP3_RETRIVEOVER     -125
//DELE: buf contain the response message
#define EMAIL_CALLBACK_POP3_DELE            -126
//NOOP: no parameter
#define EMAIL_CALLBACK_POP3_NOOP            -127
//QUIT: buf contain the response message
#define EMAIL_CALLBACK_POP3_QUIT            -128
//RESET: buf contain the response message
#define EMAIL_CALLBACK_POP3_RESET           -129
//SENDCOMMANDSTART: no parameter
#define EMAIL_CALLBACK_POP3_SENDCOMMANDSTART    -130
//SENDCOMMAND: buf contain the response message
#define EMAIL_CALLBACK_POP3_SENDCOMMAND     -131
//SENDCOMMANDOVER: no parameter
#define EMAIL_CALLBACK_POP3_SENDCOMMANDOVER -132
//XAUTHLISTSTART: no parameter
#define EMAIL_CALLBACK_POP3_XAUTHLISTSTART  -133
//XAUTHLIST: num1 is the message number and buf is the response message
#define EMAIL_CALLBACK_POP3_XAUTHLIST       -134
//XAUTHLISTOVER: no parameter
#define EMAIL_CALLBACK_POP3_XAUTHLISTOVER   -135
//XSENDER: buf is the email address
#define EMAIL_CALLBACK_POP3_XSENDER         -136

//define the notifier call back result value
/** FS result */
/**Return code that indicates successful completion of an operation*/
#define EMAIL_FS_SUCCESS            0
/**Return code that indicates the current operation is failed*/
#define EMAIL_FS_FAILED             -1
/**Return code that indicates failure completion of allocating memory*/
#define EMAIL_FS_ALLOC_FAIL         -2
/**Return code indicates that param error */
#define EMAIL_FS_PARAMETER_ERROR    -3

#define EMAIL_CALLBACK_RESULT_OK            EMAIL_FS_SUCCESS

#define EMAIL_LIVE_HOST_STR ".live.com"

/*@}*/

/**
*    \name Structure Types that are used by Email setting
*/

/*@{*/
enum
{
    SECURITYOFF = 0,
    SECURITYON
};
typedef uint8_t Email_SecurityType_e;

enum
{
    POP3 = 0,
    IMAP,
};
typedef uint8_t Email_IncomeServerType_e;


/** define the email setting informations*/
typedef struct _EMAIL_Account_Config {
//     int8_t * charset;       /**<the charset for the setting strings, MUST be UTF8*/
    int8_t accountStr[EMAIL_MAX_ACCOUNTID_LEN + 1];   /**<the point of the account string, UTF8 encoding*/
//     int8_t * usernameStr;  /**<the point of the user name, UTF8 encoding*/
    int8_t username[EMAIL_MAX_USERNAME_LEN + 1];     /**<the point of account name, UTF8 encoding*/
    int8_t password[EMAIL_MAX_PASSWORD_LEN*2 + 1];     /**<the point of account password, UTF8 encoding*/
    int8_t smtpServer[EMAIL_MAX_SERVER_NAME_LEN*2 + 1];   /**<the point of SMTP server name, UTF8 encoding*/
    int8_t pop3Server[EMAIL_MAX_SERVER_NAME_LEN*2 + 1 ];   /**<the point of POP3 server name, UTF8 encoding*/
    int8_t padd[3] ;                 
    Email_IncomeServerType_e     IncomeType;            ///POP3, read only
    Email_SecurityType_e         IncomeSecurity;        ///OFF , read only
    Email_SecurityType_e         APOPSecurityLogin;         ///OFF , read only
    Email_SecurityType_e         OutgoSecurity;                ///OFF , read only

    int32_t smtpPort;       /**<the SMTP server port value*/
    int32_t pop3Port;       /**<the POP3 server port value*/
    int32_t maxInbox;       /**<the maximum count of the Inbox*/
    int32_t maxOut;         /**<the maximum count of the outbox*/
    int32_t maxSent;        /**<the maximum count of the sent box*/
    int32_t maxDraft;       /**<the maximum count of the draft box*/
    int32_t deleSeverBak;   /**<whether delete the server backup file*/
}T_EMAIL_Account_Config;

enum
{
    EMAIL_RETRIEVAL_HEADERS_ONLY = 0,
    EMAIL_RETRIEVAL_SIZE_LIMIT = 1,
    EMAIL_RETRIEVAL_ALL_RETRIEVE = 2,
} ;
typedef uint8_t EMAIL_TO_Retrieve_Menu_e;

enum
{
    EMAIL_SETTING_AUTOMATIC_RETRIVAL_OFF = 0,
    EMAIL_SETTING_AUTOMATIC_RETRIVAL_ON = 1,
} ;
typedef uint8_t EMAIL_Automatic_Retrieval_Menu_e;


enum
{
    EMAIL_SETTING_USER_SIGNATURE_OFF = 0,
    EMAIL_SETTING_USER_SIGNATURE_1 = 1,
    EMAIL_SETTING_USER_SIGNATURE_2 = 2,
} ;
typedef uint8_t EMAIL_Signature_Menu_e;

enum
{
    EMAIL_SETTING_SIM_1 = 0,
    EMAIL_SETTING_SIM_2 = 1,
} ;
typedef uint8_t EMAIL_SIM_Setting_Menu_e;

typedef struct SettingSave_Tag
{
    int8_t      *pMyName;
    uint32_t    MyNameLen;
    int8_t      *pSignature1;
    uint32_t    Signature1Len;
    int8_t      *pSignature2;
    uint32_t    Signature2Len;
    EMAIL_Signature_Menu_e      SignatureType;       //read Signature Type
    EMAIL_TO_Retrieve_Menu_e    ToRetrieveType;       //read EMAIL to Retrieve Type
    EMAIL_Automatic_Retrieval_Menu_e    AutoRetrievalType;       //read Automatic_Retrieval Type
    EMAIL_SIM_Setting_Menu_e    SIMSettingType;         //read SIM Type
    uint32_t      SizeLimit;
    uint32_t     RetrievalAmount;
    uint32_t      AutoRetrieval;
}T_EMAIL_Account_Setting; //structure of RAI ID uses

/*@}*/

typedef int32_t (*FUNC_EMAIL_Notifier) (int32_t type, int8_t * buf, int32_t len, int32_t num1, int32_t num2, int8_t * str);

#ifdef __cplusplus
extern "C" {
#endif

#ifdef __cplusplus
}
#endif

#endif /* __NCCEMAIL_COMMON_H__ */
