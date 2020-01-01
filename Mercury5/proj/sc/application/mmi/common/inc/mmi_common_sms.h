/**
 *  @file   mmi_common_sms.h
 *  @brief  it is used for communination within different Applications/Services in sms utility functions.
 *
 * @version $Id: mmi_common_sms.h 41287 2009-09-24 06:22:46Z joe.hsu $
 * @author	joe.hsu
 */
#ifndef __MMI_COMMON_SMS_H__
#define __MMI_COMMON_SMS_H__


#include "mmi_mae_common_def.h"
#include "mmi_common_custom.h"
#include "mmi_common_sms_master.h"
#include "mmi_common_sms_tpdu.h"
#include "mmi_common_mms.h"
#include "mmi_mae_shell.h"

#include "mmi_mae_window.h"
#include "mmi_mae_widget.h"

#define SMS_CHANGE_LINE_CHAR 0x000A 
#define BREAKIF_DISPERROR_SMS(s,n)  \
                                if(MAE_RET_SUCCESS != n) \
                                {\
                                    LOG_ERROR(MMI_LEVEL_MESSAGE, s,n);\
                                    break; \
                                }

#define BREAKIF_NULL(n,p) \
                        if( NULL == (p))\
                        {\
                            n = MAE_RET_OUT_OF_MEMORY;\
                            break;\
                        }

#define BREAKIF_DISPNULL(s,n,p,e)\
                        if( NULL == (p))\
                        {\
                            n = e;\
                            LOG_ERROR(MMI_LEVEL_MESSAGE, s,n);\
                            break;\
                        }

#define BREAKIF_ERROR_NULL(s,n,p,e)\
                                    BREAKIF_DISPERROR_SMS(s,n);\
                                    BREAKIF_DISPNULL(s,n,p,e);


#define msg_token_semicolon 0x3b            //;
#define msg_token_comma 0x2c                //,
#define msg_token_colon 0x3a			   //:
#define msg_token_exclamation 0x21	   //!
#define msg_token_dollarsign 0x24		  //$
#define msg_token_and 0x26			  //&
#define msg_token_percentage 0x25		  //%
#define msg_token_starsign 0x2a             //*
#define msg_token_equalsign 0x3d           //=
#define msg_token_slash 0x2f                 //'/'
#define msg_token_antislash 0x5c		  //'\'
#define msg_token_wellsign 0x23		  //#
#define msg_token_plus 0x2b                   //+
#define msg_token_minus 0x2d                //-

#define MMS_MAX_ADDRESS_LEN     312
#define MCA_MSG_BLACKLIST_SUPPORT_MAX   20
#define SECAPP_BLACKLIST_KEYWORD_LENGTH	30


typedef struct
{
    u16      size;                      /*!< Size of the bytestream */
    u16      *pu16Data;                      /*!< Pointer to the start of the 16-bytestream */
    u8       *pu8Data;                      /*!< Pointer to the start of the bytestream */
} SMS_MESSAGE_PART_DATA_t;

typedef struct
{
    SMS_MESSAGE_PART_DATA_t     **ppMessageParts;   /*!< Address of array of pointers to individual parts */
    SMS_MESSAGE_PART_DATA_t     *pMessageParts; /*!< Address of array of pointers to individual parts */
    u32                         numMessageParts;    /*!< Number of SMS_MESSAGE_PART_DATA_t in this message */
} SMS_MESSAGE_BODY_t;

typedef struct
{
    void (*freeFunc)(void * block); /*Pointer to function used to free this block of memory*/

} RELEASE_MEM_HEADER;

typedef struct
{
    RELEASE_MEM_HEADER          memHdr;             /*!< Pointer to a cleanup function for this structure */
    SMI_MsgHdr_t                *pHeader;           /*!< Header information gfor this message */
    SMS_MESSAGE_BODY_t          *pBody;             /*!< Body data for this message */
} SMS_MESSAGE_t;

typedef struct
{
    u16               pduOffsetIdx[MAX_CONCATENATE_PACKAGE];	  // record the tpdu loc at file
    u8                pduLen[MAX_CONCATENATE_PACKAGE];			  // tpdu length
    u8                simIndex[MAX_CONCATENATE_PACKAGE];          // 8 bit array of SIM message index
    u8                resentPduIdx;								  // record the start resent pdu index
   	u8 				  imsi[MMI_MMS_FS_MAX_IMSI_LEN];
} SMS_MsgDataHdr;

typedef struct
{
    u8 addr[SMI_MAX_ADDR_LEN*2+1];
} SMS_MsgRecipAddr;

typedef u16 SMS_MsgRecipSize;

typedef struct
{
    SMS_MsgRecipSize lstNum;
    SMS_MsgRecipAddr *pRecipAddr;
} SMS_MsgRecipLst;


typedef struct
{
    SMS_MsgDataHdr  msgDataHdr;
    SMS_MsgRecipLst msgRecipLst;
	u8              *pPduData;
} SMS_MsgData;		// message data file structure


enum
{
    SMS_SAVE_TYPE_NEW_CBMsg =0,
    SMS_SAVE_TYPE_Class0
};
typedef u8 SMS_SAVE_TYPE_e;

typedef struct
{
    MAE_WChar           cntMEno[MMI_MMS_MAX_DISPLAY_SUBJECT_CHAR+1]; /* 10 UCS2's or 20 ASCII's */
    u8                  bCntUcs2;
    u8                  bCntMore;
    u8                  mmsToAddr[MMS_MAX_ADDRESS_LEN+4];
    SMS_MsgRecipAddr    msgRecipAddr;
    u32                 mmsContentSize;
	u8 					imsi[MMI_MMS_FS_MAX_IMSI_LEN];
    MMI_MMS_FS_MAILBOX_e mailBox;
    s32                 mmsIndex;
	u8 au8Name[MMI_PHB_NAME_LEN];	// Sender Contact Name
} SMI_MmsHdr_t;

typedef struct
{
	SMI_MmsHdr_t		mmsHeader;
	SMI_MsgHdr_t		msgHeader;
} _MmsTempData_t;

typedef struct SMS_RESTORE_DATA_TAG
{
    u16* pMsgCnt;
    u16 nMsgCntStrlen;
    SMI_MsgHdr_t tSmHdr;
    SMI_SmEncoding_t encoding;
    SMS_MsgRecipLst tMsgRecipLst;
    u8 IMSI[MMI_MMS_FS_MAX_IMSI_LEN];

}SMS_StoreData_t; // for smi/mci store function

typedef enum
{
	MCA_DETAIL_VIEW_BEGIN=0x1200,
    MCA_DETAIL_SCROLLBAR,
    MCA_DETAIL_VIEWPORT,
    MCA_DETAIL_MAIN_CONTAINER,
    MCA_DETAIL_SUBJECT_TXT,
    MCA_DETAIL_TYPE_TXT,
    MCA_DETAIL_DATE_TXT,
    MCA_DETAIL_TIME_TXT,
    MCA_DETAIL_SIZE_TXT,
    MCA_DETAIL_FROM_TXT,
    MCA_DETAIL_TO_TXT,
    MCA_DETAIL_CC_TXT,
    MCA_DETAIL_BCC_TXT,
    MCA_DETAIL_VIEW_END
} McaDetailView_e;

typedef struct McaDetailViewWdgList_t_
{
	IWidget *pTitleWdg;
    IWidget *pScrollbarWdg;
    IWidget *pViewportWdg;
    IWidget *pMainContainer;
    IWidget *pSubjectTextWdg;
    IWidget *pTypeTextWdg;
    IWidget *pDateTextWdg;
    IWidget *pTimeTextWdg;
    IWidget *pSizeTextWdg;
    IWidget *pFromTextWdg;
    IWidget *pToTextWdg;
    IWidget *pCcTextWdg;
    IWidget *pBccTextWdg;
} McaDetailViewWdgList_t;

typedef struct MmiMsgBlackListMemberContent_t_
{
    u8 au8Number[MMI_PHB_NUMBER_LEN + 1];
} MmiMsgBlackListMemberContent_t;

typedef struct MmiMsgBlackListKeywordContent_t_
{
    MAE_WChar Keyword[SECAPP_BLACKLIST_KEYWORD_LENGTH + 1];
} MmiMsgBlackListKeywordContent_t;

/**
 * smsAddrAsciiToBCD
 *  @ brief transfer telphone number from Ascii into LSB format bcd code. encoding.
 *  @ param pStr, pointer to u8 string
 *  @ param strLen, string length [word count]
 *  @ param pBcd, return pointer of bcd encoding string
*/
void smsAddrAsciiToBCD(u8 *pStr, u8 strLen, u8 *pBcd);

/**
 * smsAddrAsciiToBCD
 *  @ brief Convert SMSP SC bcd to ascii.
 *  @ param pSc, pointer to u8 string
 *  @ param strLen, string length [word count]
 *  @ param pStr, return pointer of bcd encoding string
*/
void smsSmspScToAscii(const u8 *pSc, u8 strLen, u8 *pStr);

/**
 * smsAsciiToSmspSc
 *  @ brief Convert ascii to SMSP SC bcd.
 *  @ param pStr, pointer to u8 string
 *  @ param strLen, string length [word count]
 *  @ param pSc, return pointer of bcd encoding string
*/
void smsAsciiToSmspSc(const u8 *pStr, u8 strLen, u8 *pSc);

/**
 * smsData7bitsTo8bits
 *  @ brief Convert 7-bits data to 8-bits data.
 *  @ param src, pointer to u8 string
 *  @ param source_len, string length [word count]
 *  @ param dest, return pointer of bcd encoding string
 *  @ param bit_offset, some first bits does not really encode into 7-bits

 *  @retval u8, output string length.
*/
u8 smsData7bitsTo8bits(u8 *src, u8 source_len, u8 *dest, u8 bit_offset);

/**
 * smsDataConvert8BitTo7Bit
 *  @ brief Convert 8-bits data to 7-bits data
 *  @ param inputData, pointer to u8 string
 *  @ param inputDataLen, string length [word count]
 *  @ param outputData, return pointer of bcd encoding string
 *  @ param offsetI,
 *  @ param smUDH_start_bit,
*/
void smsDataConvert8BitTo7Bit(u8 *inputData, u16 inputDataLen, u8 *outputData, s8 shift_bit);

/**
 * smsGetMsgInfo
 *  @ brief parse the SMS tpdu.
 *  @ param pu8SmsTpdu, pointer to sms tpdu
 *  @ param pu8HeaderByte1, return sms tpdu first byte
 *  @ param pu8AddrLen, return recipient/sender address length
 *  @ param pu8AddrTon, return recipient/sender type SMS_TON_NATIONAL/SMS_TON_INTERNATIONAL
 *  @ param pau8Addr,   return pointer of recipient/sender address
 *  @ param pu8Dcs,     return encoding code
 *  @ param pau8Scts,   return service center timestamp

 *  @retval SMS Type, SMS_MTI_DELIVER/SMS_MTI_SUBMIT/SMS_MTI_STATUS_REPORT
*/
u8 smsGetMsgInfo(const u8 *pu8SmsTpdu, u8 *pu8HeaderByte1, u8 *pu8AddrLen, u8 *pu8AddrTon, u8 *pau8Addr, u8 *pu8Dcs, u8 *pau8Scts);

/**
 * smsDecodeConcatMsgInfo
 *  @ brief check if the SMS is concatnated sms and return related information
 *  @ param pu8SmsTpdu, pointer to sms tpdu
 *  @ param pu16ConcatRefNum, return sms reference number
 *  @ param pu8ConcatMaxNum, return this sms max page number
 *  @ param pu8ConcatSeqNum, return this sms belong to which part number
 *  @ param pu8TpduHeaderLen,   return total tpdu header length

 *  @retval TRUE, this SMS is concatnated message. Otherwise. it is not.
*/
boolean smsDecodeConcatMsgInfo(const u8  *pu8SmsTpdu, u16 *pu16ConcatRefNum, u8 *pu8ConcatMaxNum, u8 *pu8ConcatSeqNum, u8 *pu8TpduHeaderLen);

/**
 * smsTpduParseDataCodingScheme
 *  @ brief parse sms tpdu coding scheme defined by SMI
 *  @ param dataCodingScheme, original coding scheme

 *  @retval SMI_SmEncoding_t, Encoding8BitASCII/EncodingGSM7Bit/EncodingUCS2
*/
SMI_SmEncoding_t smsTpduParseDataCodingScheme(u8 dataCodingScheme);

//void smsHandleClass0Msg(u8  *pu8SmsTpdu);
/**
 * smsGetSenderAddr
 *  @ brief get sender address
 *  @ param pSenderAddr, return pSenderAddr
 *  @ param AddressValue, original address
 *  @ param typeOfNumber, International, or not
 *  @ param addrLength, original address length
*/
void smsGetSenderAddr(u8 *pSenderAddr, u8 *AddressValue, u8 typeOfNumber, u8 addrLength);

/**
 * smsCbTpduParseDataCodingScheme
 *  @ brief parse CB tpdu coding scheme
 *  @ param dataCodingScheme,

 *  @retval SMI_SmEncoding_t, Encoding8BitASCII/EncodingGSM7Bit/EncodingUCS2
*/
SMI_SmEncoding_t smsCbTpduParseDataCodingScheme(u8 dataCodingScheme);

/*Check DCS Type Voice Waiting Ind
  Convert DCS to fit type */
void SMS_DECODE_DCS(SMS_DCS_t *ptDcs, u8 Dcs);

//Port related /*check if this SMS tpde is port message and return port number*/
boolean SMS_VerifyPortMessage(u8* pu8Tpdu, u16 *pMsgPort);

//WAP related /*check if this SMS tpde is WAP message*/
#ifdef __MMI_SMS_WAPPUSH__
boolean SMS_VerifyWapMessage(u8* pu8Tpdu,u8 *pMsgUDHLOrder, u8 *pMsgUDHLengh, u8 *pMsgDataLen);
#else
boolean SMS_VerifyWapMessage(u8* pu8Tpdu);
#endif

/*check if this SMS user data header is WAP UDH*/
boolean SMS_CHK_WAP_SMS_UDH(u8* pu8MsgData, u8 u8MsgDataLen);

/*check if this SMS user data header is port SMS UDH and return port number*/
boolean SMS_CHK_SMS_UDH(u8* pu8MsgData, u8 u8MsgDataLen, u16 *pMsgPort);

/*check if this SMS user data header is WAP */
boolean SMS_CHK_SMS_PP_WD(u8* pu8MsgData, u8 u8MsgDataLen, u8 u8DataCodeScheme);

boolean SMS_CHK_SMS_SCK(u8* pu8MsgData, u8 u8MsgDataLen, u8 u8DataCodeScheme);

void SMS_CVT_SCK_U8(u8* pu8MsgData, u8 u8MsgDataLen, u8* pu8AsciiStr, u8 u8DataCodeScheme);

#ifdef _MSIM_
/*post new message indication*/
void smsPostMTIndication(IBase *pThis, u8 SimModule);
#endif


/**
 * SMS_Create_MasterHdr
 *  @ brief generage SMI_MsgHdr_t message file header for any message stored at master file
 *  @ param type, type of SMS
 *  @ param msgFlag, sms status
 *  @ param msgLoc,sms location
 *  @ param pMsgHdr, return SMI_MsgHdr_t
 *  @ param pThis, requester instance

 *  @retval MAE_RET_SUCCESS, Success
 *  @retval MAE_RET_OUT_OF_MEMORY, Fail
 *  @retval MAE_RET_FAILED, Fail
*/
MAE_Ret SMS_Create_MasterHdr(SMI_MsgType_e type, SMI_MsgFlag msgFlag, SMI_MsgLocation_e msgLoc, SMI_MsgHdr_t **pMsgHdr, IBase*pThis);

/**
 * Message_GetDetailView
 *  @ brief generage SMI_MsgHdr_t message file header for any message stored at master file
 *  @ param type, type of SMS
 *  @ param msgFlag, sms status
 *  @ param msgLoc,sms location
 *  @ param pMsgHdr, return SMI_MsgHdr_t
 *  @ param pThis, requester instance

 *  @retval MAE_RET_SUCCESS, Success
 *  @retval MAE_RET_OUT_OF_MEMORY, Fail
 *  @retval MAE_RET_FAILED, Fail
*/
MAE_Ret SMS_GetContactName(MAE_WChar *pNumber, MAE_WChar **ppName, IBase *pOwner);

/**
 * SMS_GetPageNumberFromContent
 *  @ brief query total page number
 *  @ param nEncoding, encode scheme EncodingGSM7Bit/EncodingUCS2/Encoding8BitASCII
 *  @ param nSMSWordCount,word count
 *  @ param nRealPage, return page number
 *  @ param nRestChar, return the rest word count of last page

*/
void SMS_GetPageNumberFromContent(u32 nEncoding,u32 nSMSWordCount, u32 *nRealPage, u32 *nRestChar);

/**
* SMS_GetPageNumberFromVCardContent
*  @ brief query VCard message total page number
*  @ param nVCardSMSWordCount,word count
*  @ param nRealPage, return page number

*/
#ifdef __SMART_MESSAGING_MMI_SUPPORT__
void SMS_GetPageNumberFromVCardContent(u32 nVCardSMSWordCount, u32 *nRealPage);
#endif
/**
 *   SMS_SAVE_CBANDCLASS0
 *  @ brief save CB or class0 message
 *  @ param pData, Wchar string
 *  @ param nChannel,for CB channel, if class0 message ,nChannel =0
 *  @ param encoding, coding scheme
 *  @ param msgType, message type CB or class0
 *  @ param bRead, bRead = TRUE, it means message is read status.
 *  @ param MsgID, return saved message ID if success
 *  @ param pThis, requester instance

 *  @retval MAE_RET_SUCCESS, success
 *  @retval MAE_RET_FS_FULL, fail
 *  @retval MAE_RET_OUT_OF_MEMORY, fail
 *  @retval MAE_RET_FAILED, fail
*/
MAE_Ret SMS_SAVE_CBANDCLASS0( MAE_WChar *pData, u32 nChannel, SMI_SmEncoding_t encoding, SMS_SAVE_TYPE_e msgType, boolean bRead,SMI_MsgID_t *MsgID, IBase *pThis);

/**
 * Message_WriteTempRawDataFile
 *  @ brief write temp message data file
 *  @ param pMsgData, data
 *  @ param DataLen, data length
 *  @ param pOwner, requester instance

 *  @retval MAE_RET_SUCCESS, success
 *  @retval MAE_RET_FAILED, fail
*/
MAE_Ret Message_WriteTempRawDataFile(void *pMsgData, u32 DataLen, IBase *pOwner);


/**
 * Message_DeleteTempRawDataFile
 *  @ brief delete temp message data file
 *  @ param pOwner, pointer to u8 string

*/
void Message_DeleteTempRawDataFile(IBase *pOwner);

/**
 * Message_IsSeparator
 *  @ brief check if the wild char is the separator sign
 *  @ param wchar, wild character

 *  @retval TRUE, this char is separator. Otherwise, it is not.
*/
boolean Message_IsSeparator( MAE_WChar wchar );

/**
 * Message_IsURLSeparator
 *  @ brief check if the wild char is the URL separator sign, the different with Message_IsSeparator() is to remove "msg_token_colon"
 *  @ param wchar, wild character

 *  @retval TRUE, this char is URL separator. Otherwise, it is not.
*/
boolean Message_IsURLSeparator( MAE_WChar wchar );
boolean Message_isSafe(MAE_WChar ch);
boolean Message_isExtra(MAE_WChar ch);
boolean Message_isReserved(MAE_WChar ch);
boolean Message_IsValidURLChar( MAE_WChar wchar );
MAE_Ret SMS_OpenMessageDataFile(IBase *pThis, SMI_MsgID_t nMsgId,SMS_MsgRecipLst *pmsgRecipLst, SMS_MsgDataHdr *pmsgDataHdr,u8 **pPduData);
MAE_Ret SMS_ParsePDUTextUcs2(MAE_WChar **ppTextUcs2, size_t *pdestStrLen,boolean *pbCrashNotify,u8 *pu8MsgHead, u8 u8HeaderLen, u8 u8TPUDHeaderLen, u8 encoding, u8 **ppExtObjData);

/**
 * Message_IsNewerTimeStamp:
 *
 * Check if the NewTimeStamp is newer(later) then the OrgTimeStamp
 *
 * @param[in] OrgTimeStamp     Original time stamp
 * @param[in] NewTimeStamp     New time stamp
 *
 * @retval >0     The NewTimeStamp is newer(later) then the OrgTimeStamp
 * @retval <0     The OrgTimeStamp is newer(later) then the NewTimeStamp
 * @retval =0     Two timestamp is the same.
 */
s8 Message_IsNewerTimeStamp(SMI_TimeStamp_t OrgTimeStamp, SMI_TimeStamp_t NewTimeStamp);

/**
 * Message_IsSimSmsID:
 *
 * Check if the msg ID is belong to SIM SMS ID
 *
 * @param[in] MsgID      Msg ID
 * @param[in] SimModule  SIM module
 *
 * @retval TRUE/FALSE
 */
boolean Message_IsSimSmsID(SMI_MsgID_t MsgID, u8 SimModule);

/**

Specify the SMS receive storage

@param nSimModule
       The SIM module id

@return
       Return the result of method call.

*/
MAE_Ret SMS_SetRecvStorage( IBase *pThis, u8 nSimModule );

/**

Specify the SMS receive capacity

@param nSimModule
       The SIM module id

@return
       Return the result of method call.

*/
MAE_Ret SMS_SetRecvCapacity( IBase *pThis, u8 nSimModule );

/**

Update the SMS receive storage

@return
       Return the result of method call.

*/
MAE_Ret SMS_UpdateRecvStorage( IBase *pThis );

/**

Update the SMS receive capacity

@return
       Return the result of method call.

*/
MAE_Ret SMS_UpdateRecvCapacity( IBase *pThis );

/**
* SMS_GetEncodingByContent
*  @ brief get the proper encoding according to the SMS content
*  @ param pSMSContent SMS content string in UCS2
*  @ param nStrLen     the string length of the SMS content
*
*  @retval MAE_RET_SUCCESS,   success
*  @retval MAE_RET_BAD_PARAM, fail
*/
MAE_Ret SMS_GetEncodingByContent(MAE_WChar *pSMSContent, u16 nStrLen, SMI_SmEncoding_t *pEncoding);

/**
* Message_CreateMmsTempFile
*  @ brief create temp MMS data file for range between "MIN_MMS_MSG_ID" and "MAX_MMS_MSG_ID"
*  @ param pOwner, requester instance

*  @retval MAE_RET_SUCCESS, success
*  @retval MAE_RET_FAILED, fail
*/
MAE_Ret Message_CreateMmsTempFile(IBase *pOwner);

/**
* Message_GetMatchedSIMModuleByMsgID
*  @ brief get the matched SIM module by a specified msdid
*  @ param nMsgID, the message id
*  @ param pSimModule, return value of the matched SIM module

*  @retval MAE_RET_SUCCESS, success
*  @retval MAE_RET_FAILED, fail
*/
MAE_Ret Message_GetMatchedSIMModuleByMsgID(SMI_MsgID_t nMsgID, u8 *pSimModule);

/**
* Message_WriteMmsRawDataFile
*  @ brief write temp message data file
*  @ param pMsgData, data
*  @ param DataLen, data length
*  @ param msgId,	the message id
*  @ param pOwner, requester instance

*  @retval MAE_RET_SUCCESS, success
*  @retval MAE_RET_FAILED, fail
*/
MAE_Ret Message_WriteMmsRawDataFile(void *pMsgData, u32 DataLen, SMI_MsgID_t msgId, IBase *pOwner);

/**
* Message_RecycleMmsTempFile
*  @ brief Recycle the message data file
*  @ param msgId,	the message id
*  @ param pOwner, requester instance

*  @retval MAE_RET_SUCCESS, success
*  @retval MAE_RET_FAILED, fail
*/
MAE_Ret Message_RecycleMmsTempFile(SMI_MsgID_t msgId, IBase *pOwner);

MAE_Ret SMS_InsertContactDetail(void *pContactDetals, MAE_WChar **ppContent); // MmiPhbContactContent_t
MAE_Ret SMS_InsertContactItem(MAE_WChar **ppNewData, u32 *pnTotalLen, u32 FieldTextID, u8 *pData, u16 nDataLen);
MAE_Ret SMS_AppendItemString(MAE_WChar **ppNewData, u32 *pnTotalLen, MAE_WChar *pItem, u32 nItemLen, boolean bFieldItem);
/** 
 *   SMS_ParsePushSMSPDU
 *  @ brief Parse input SMS push PDU and return the push type 
 *  @ param pPushData, push data buffer(input)
 *  @ param nPushLen, push data length(input)
 
 *  @retval SMS_PushType_e, type of the push PDU
 */
typedef enum
{
    SMS_PUSH_TYPE_NONE                     = 0x00,
    SMS_PUSH_TYPE_MMS_M_NOTIFICATION_IND   = 0x01,
    SMS_PUSH_TYPE_MMS_M_DELIVERY_IND       = 0x02,
    SMS_PUSH_TYPE_MMS_M_READORIG_IND       = 0x03,
#ifdef __MMI_SMS_WAPPUSH__
    SMS_PUSH_TYPE_SMS_M_SERVICELOAD        = 0x04,
    SMS_PUSH_TYPE_SMS_M_SERVICEINDICATION  = 0x05,
#endif 
    SMS_PUSH_TYPE_OTA_PROVISIONING         = 0x06
    /* other push types to be supported */
} SMS_PushType_e;

SMS_PushType_e SMS_ParsePushSMSPDU(u8* pPushData, u32 nPushLen);

#ifdef __ANTI_STEAL_REMOTE_CONTROL_MMI__
#define REMOTECONTROLAPP_SET_CONTROL_FUNCTION_STATUS(queue, bit) {                       \
                                                                    queue |= (1 << bit); \
                                                                 }
#define REMOTECONTROLAPP_CLEAR_CONTROL_FUNCTION_STATUS(queue, bit) {                             \
                                                                        if(queue & (1 << bit))   \
                                                                        {                        \
                                                                            queue ^= (1 << bit); \
                                                                        }                        \
                                             }
#define REMOTECONTROLAPP_CHECK_CONTROL_FUNCTION_STATUS(queue, bit) ((queue & (1 << bit)) ? TRUE : FALSE)
enum
{
    RC_CONTROL_FUNCTION_POPWER_OFF = 0,
    RC_CONTROL_FUNCTION_CALL_TRANSFER,
    RC_CONTROL_FUNCTION_SMS_TRANSFER,
    RC_CONTROL_FUNCTION_PHONE_BLOCK,
    RC_CONTROL_FUNCTION_FETCH_PHB,
    RC_CONTROL_FUNCTION_FETCH_SMS,
    RC_CONTROL_FUNCTION_DELETE_PHB,
    RC_CONTROL_FUNCTION_DELETE_SMS,
    RC_CONTROL_FUNCTION_DELETE_CALLLOG,
    RC_CONTROL_FUNCTION_FORMAT_STORAGE,
    RC_CONTROL_FUNCTION_MAX_COUNT,
};
typedef u32 RemoteControlControlFunction_e;
enum
{
    RC_CONTROL_RET_NOT_RC_MSG = 0,
    RC_CONTROL_RET_IS_RC_MSG,    
    RC_CONTROL_RET_POPWER_OFF,
    RC_CONTROL_RET_PHONE_BLOCK,
};
typedef u8 RemoteControlCmdRet_e;
enum
{
    RC_NUMBER_ANY_NUMBER = 0,
    RC_NUMBER_FIXED_NUMBER,
};
typedef u32 RemoteControlSelectNumberType_e;
typedef struct
{
    MAE_WChar Cmd[8];
    MAE_WChar Operation[RC_CONTROL_FUNCTION_MAX_COUNT][16];
    MAE_WChar Cancel[8];
}RemoteControlAllCmd;
void SMS_RemoteControl_GetAllCmd(RemoteControlAllCmd *p);
#endif //__ANTI_STEAL_REMOTE_CONTROL_MMI__

/** 
 *  SMS_GetAndAdvanceMsgReference(void)
 *  @brief Get and advance TP-MR that will be encoded in SMS-SUBMIT TPDU
 *  @retval TP-MR value
 */
u8 SMS_GetAndAdvanceMsgReference(void);

/** 
 *  SMS_IsAddressEqual(const MAE_WChar* RecentContact, const MAE_WChar* Contact)
 *  @brief Compare 2 address to verify if they are equal
 *  @retval boolean
 */
boolean SMS_IsAddressEqual(const MAE_WChar* RecentContact, const MAE_WChar* Contact);

#endif /* __MMI_COMMON_SMS_H__ */

