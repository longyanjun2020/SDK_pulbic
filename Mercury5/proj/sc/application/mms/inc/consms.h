
#ifndef __CONSMS_H__
#define __CONSMS_H__

#include <consms_config.h>

/*hexadecimal number conversion,e.g. char *cs="0B" ->> bi=0x0b */
#define TwoChars_to_Hex(cs,bi) \
        if(*cs>='0' && *cs <='9') \
            bi=(*cs-'0')<<4; \
        else \
            bi=(*cs-'A'+10)<<4; \
        if(*(cs+1)>='0' && *(cs+1)<='9') \
            bi+=*(cs+1)-'0'; \
        else \
            bi+=*(cs+1)-'A'+10

#ifdef __cplusplus
extern "C"{
#endif

#define CONSMS_IS_NEW           0x01    /* it's concatenated sms */
#define CONSMS_IS_NOT_NEW       0x00    /* it's NOT concatenated sms */

#define CONSMS_TOTAL_SEQUENCE   4  /* total sequence of concatenated sms */
#define CONSMS_PDU_LEN              140 /*  length of sms pdu */
#define MAX_NUMBER_NOTIFY       4 /* support max number of notify message */
#define MAX_NOTIFY_MESSAGE_SIZE 500   /* max length of MMS notification*/

typedef struct T_SegmentData{
    uint8_t Data[CONSMS_PDU_LEN];   /* data buf's address pointer */
    int32_t Length;  /* data's length */
}T_SegmentData;

typedef struct T_ConcatenatedMessage_Struct{
    int16_t UseTag; /* indicate if the struct have been used 0:no use 1:used*/
    int32_t SequenceNum;     /*  current sequenceNum of short message group  */
    int32_t Total;   /*  the short message's total number of the cancatenated message  */
    //T_SegmentData **Data; /*  each short message's data struct ,current version it support 5 sms  */
    //not malloc the buffer, make it as static buffer
    T_SegmentData Data[CONSMS_TOTAL_SEQUENCE];/*  each short message's data struct ,current version it support 4 sms  */
}T_ConcatenatedMessage_struct;

typedef struct T_SMS_PDU{
    int32_t data_len;            /* user user data's length */
    uint8_t data[CONSMS_PDU_LEN];     /* the user data buffer's pointer */
    uint8_t pdu_type;  /* the type of the pdu  */
    uint8_t Boundary[3];
} T_SMS_PDU;

int8_t  CSmsRevSmsNotify(T_SMS_PDU *pSms);
int32_t  CSmsPDUString2MSG(int8_t*str,int32_t str_len,T_SMS_PDU *msg);

#ifdef __cplusplus
}
#endif

#endif
