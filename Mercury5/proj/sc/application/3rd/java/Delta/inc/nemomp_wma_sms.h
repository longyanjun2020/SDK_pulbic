#ifndef __NEMOMP_WMA_SMS_H__
#define __NEMOMP_WMA_SMS_H__

#include "nemomp.h"
#include "nemomp_standard.h"

typedef enum NM_WMA_REGISTER_ENUM
{
  NM_WMA_TYPE,
  NM_PUSH_TYPE,
  NM_TOTAL_TYPE
} nm_wma_register_enum;


typedef enum
{
  NM_TEXT_SMS = 0,
  NM_BINARY_SMS,
  NM_TOTAL_SMS_FORMAT
} nm_sms_format_enum;

typedef enum
{
    NM_SMS_PORT_IN_USED = -5,              /* Port is used by other applications */
    NM_SMS_EXCEED_SIZE = -4,               /* Message content size exceeds the sms limitation */
    NM_SMS_PORT_NOT_FOUND = -3,            /* Port has never been used */
    NM_SMS_WAIT = -2,                      /* Wait for result */
	NM_SMS_ERROR = -1,					   /* Error */
    NM_SMS_OK = 0,                         /* Success */
    NM_SMS_ERROR_TOTAL
} nm_wma_error_code_enum;


typedef enum
{
    NM_MSG_SMS_SEND_MESSAGE = 1,
    NM_MSG_SMS_CHECK_INCOMING,
    NM_MSG_SMS_RECEIVE_MESSAGE,
    NM_MSG_SMS_REGISTER_PORT,
    NM_MSG_SMS_UNREGISTER_PORT,
    NM_MSG_SMS_TOTAL
} nm_wma_reponse_enum;

/* Any resources that are required for the wma-sms operations may be created here. */
extern void nemomp_wma_sms_initialize(void);
/* Un-register all ports which registered by Java task. */
extern void nemomp_wma_sms_finalize(void);
/* register sms port */
extern nm_int32 nemomp_wma_sms_register(nm_int32 port, nm_wma_register_enum type, nm_char* storageName, nm_int32 midletID);  // 20090226: Changed; // 20090224: Changed
/* unregister sms port */
extern nm_int32 nemomp_wma_sms_unregister(nm_int32 port, nm_wma_register_enum type);
/* send text message */
extern nm_int32 nemomp_wma_sms_send_text_message(nm_wchar *addr, nm_wchar *content, nm_int32 length, nm_int32 port);
/* send binary message */
extern nm_int32 nemomp_wma_sms_send_binary_message(nm_wchar *addr, nm_char *buffer, nm_int32 length, nm_int32 port);
/* calculate the number of segment by text message */
extern nm_int32 nemomp_wma_sms_text_segments(nm_wchar *content, nm_int32 length, nm_int32 port);
/* calculate the number of segment by binary message */
extern nm_int32 nemomp_wma_sms_binary_segments(nm_char *buffer, nm_int32 length, nm_int32 port);

/* check incoming sms message */
nm_int32 nemomp_wma_sms_check_message(nm_int32 port);
/* get timestamp from incoming sms message */
nm_uint64 nemomp_wma_sms_get_timestamp(nm_int32 port);
/* get sender address from incoming sms message */
nm_wchar* nemomp_wma_sms_get_address(nm_int32 port, nm_int32 *length);
/* get text message from incoming sms message */
nm_wchar* nemomp_wma_sms_receive_text_message(nm_int32 port, nm_int32 *length);
/* get binary message from incoming sms message */
nm_char* nemomp_wma_sms_receive_binary_message(nm_int32 port, nm_int32 *length);

/* asynchronous used, java layer repeatedly called if NM_SMS_WAIT */
nm_int32 nemomp_wma_sms_waiting_response(nm_wma_reponse_enum msg, nm_int32 port);

/* get smsc address */
nm_char* nemomp_wma_sms_get_smsc_address(void);

#endif /* __NEMOMP_WMA_SMS_H__ */
