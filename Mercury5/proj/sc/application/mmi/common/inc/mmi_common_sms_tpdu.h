/**
 *  @file   mmi_common_sms_tpdu.h
 *  @brief  it is used for communination within different Applications/Services in sms utility functions.
 *  @version $Id: mmi_common_sms_tpdu.h 20629 2009-01-15 08:39:46Z joe.hsu $
 *  @author	joe.hsu
 *  
 */
#ifndef __MMI_COMMON_SMS_TPDU_H__
#define __MMI_COMMON_SMS_TPDU_H__

#define SEA_SMS_TOTAL_PAGES                         9
#define SEA_SINGLE_PAGE_SIZE_7BIT                   160
#ifdef __SMS_3GPP_R8_SUPPORT__
#define SEA_MULTI_PAGES_SIZE_7BIT                   146  //(160-(EMS_UDHL+IEI_Concat8bitRn_TotalLen+3+3)*8/7) 3 ==>National Language 
#else
#define SEA_MULTI_PAGES_SIZE_7BIT                   153 //(160-(EMS_UDHL+IEI_Concat8bitRn_TotalLen)*8/7) 3
#endif

#define SEA_SINGLE_PAGE_SIZE_UCS2                   70
#define SEA_MULTI_PAGES_SIZE_UCS2                   67  // 70- (EMS_UDHL+IEI_Concat8bitRn_TotalLen)/2
#define SEA_SINGLE_PAGE_SIZE_8BIT                   140
#define SEA_MULTI_PAGES_SIZE_8BIT                   134  // 140- (EMS_UDHL+IEI_Concat8bitRn_TotalLen)

#ifdef __SMART_MESSAGING_MMI_SUPPORT__
#define CONCATENATED_SMS_UDHL 5
#define SMART_MESSAGING_VCARD_UDHL 6
#endif

#define SMS_MAX_ADDR_LEN       20
#define SMS_SCA_LEN_MAX		   21
#define SMS_TPDU_BYTE_SIZE	   140
#define SMS_PDU_SIZE_MAX       175

/* SMS fields for static byte length */
/* SMS Header Fiels */

#define SMS_FO	      1
#define SMS_MR	      1
#define SMS_PID	      1
#define SMS_DCS	      1
#define SMS_VP_1B     1
#define SMS_VP_7B	  7
#define SMS_SCTS	  7
#define SMS_UDL		  1

//
//SMS TPDU First Byte

#define SMS_BYTE1_BASE_VALUE  0x00

//TP-SRR
#define SMS_SRR_OFF	0x00
#define SMS_SRR_ON	0x20

//TP-RD
#define SMS_RD_OFF  0x00
#define SMS_RD_ON   0x04

//TP-RP
#define SMS_RP_OFF  0x00
#define SMS_RP_ON   0x80

/* SMS: MTI mask in Fist Byte*/
#define SMS_MTI_DELIVER         0x00
#define SMS_MTI_SUBMIT          0x01
#define SMS_MTI_STATUS_REPORT   0x02
#define SMS_MTI_MASK            0x03

/* SMS: TP-Validity-Period-Format (TP-VPF) according to GSM 03.40 in Fist Byte*/
#define SMS_VPF_NOT_PRESENT		  0x00
#define SMS_SMS_VPF_ENHANCED      0x08
#define SMS_VPF_RELATIVE          0x10
#define SMS_VPF_ABSOLUTE          0x18
#define SMS_VPF_MASK              0x18

/* SMS: TP-User-Data-Header-Indicator (TP-UDHI) according to GSM 03.40 in Fist Byte*/
#define SMS_UDHI_MASK	 0x40
#define SMS_HAVE_UDHI    0x40
#define SMS_NO_UDHI		 0x00	

//
//SMS TPDU OA / DA
//
/* SMS: Address Field for static byte length*/
#define SMS_ADDR_LENTH	1
#define SMS_ADDR_TYPE	1
#define SMS_MAX_ADDR_VALUE  10


/* SMS: TON & NPI for address fields */
#define SMS_TON_MASK    0x70
#define SMS_TON_SHIFT   4
#define SMS_NPI_MASK    0x0F


#define SMS_TON_NATIONAL 129
#define SMS_TON_INTERNATIONAL 145

//
//SMS TPDU DCS
//
/* SMS: DCS mask */
#define SMS_CODING_MASK	 0x0C
#define SMS_CODING_7BIT	 0x00
#define SMS_CODING_8BIT	 0x04
#define SMS_CODING_UCS2	 0x08

/* Decode DCS */
#define SMS_MSG_DEFAULT_BIT				0x00
#define SMS_MSG_CLASS2_BIT				0x02
#define SMS_MSG_CLASS_BIT				0x03
#define SMS_MSG_WAIT_IND_ACTIVE_BIT		0x08
#define SMS_MSG_CODING_BIT				0x0c
#define SMS_MSG_CLASS_MEAN_BIT			0x10
#define SMS_MSG_COMPRESS_BIT			0x20
#define SMS_MSG_WAIT_STORE_BIT			0x30
#define SMS_MSG_WAIT_IND_BIT			0xC0
#define SMS_MSG_CODING_GROUP_BIT		0xF0
#define SMS_MSG_CODING_SHIFT_BIT		2

//TP-Status
#define SMS_ST_SUCCESS                  0x00
#define SMS_ST_UNABLE_CONFIRM			0x01	
#define SMS_ST_REPLACED_BY_SC			0x02
#define SMS_ST_FAIL                     0xFF


#define SMS_MSG_DISCARD               0
#define SMS_MSG_DEFAULT_ALPHABET      1
#define SMS_MSG_UNCOMPRESS_UCS2       2

typedef enum
{
	SMS_MSG_CS_NOT_PRESENT	=  -1,
	SMS_MSG_CS_GSM_DEF		=  0,       //7-bits
	SMS_MSG_CS_GSMINT		=  1,		//8-bits
	SMS_MSG_CS_UCS2			=  2		//16-bits
} SMS_MsgCodeScheme_e;

typedef enum
{
	SMS_MSG_CLASS0				=	0,
	SMS_MSG_CLASS1				=	1,
	SMS_MSG_CLASS2				=	2,
	SMS_MSG_CLASS3				=	3,
	SMS_MSG_CLASS_NOT_GIVEN		=	4
} SMS_MsgClass_e;

/* Voice Waiting Indication Type */
typedef enum
{
	SMS_IND_VOICE_MESSAGE_WAITING  = 0x0,           /* SMS_IND_VOICE_MESSAGE_WAITING  */
	SMS_IND_FAX_MESSAGE_WAITING    = 0x1,           /* SMS_IND_FAX_MESSAGE_WAITING    */
	SMS_IND_EMAIL_MESSAGE_WAITING  = 0x2,           /* SMS_IND_EMAIL_MESSAGE_WAITING  */
	SMS_IND_OTHER_MESSAGE_WAITING  = 0x3,           /* SMS_IND_OTHER_MESSAGE_WAITING  */
	SMS_IND_NUM_OF_INDS            = 0x4            /* SMS_IND_NUM_OF_INDS            */
}SMS_IND_TYPE_e;

/* SMS Msg Voice Indication */
typedef struct
{
	SMS_IND_TYPE_e	    tIndType;       /* T_indType SmsIndType */
	u8					u8StoreMessage; /* storeMessage */
	u8					u8IndActive;    /* indActive */	
} SMS_MSG_WAITING_IND;

typedef struct
{
  SMS_MSG_WAITING_IND		    tMsgWaitingInd;            /*<8> SmsMsgWaitingInd                                   */
  SMS_MsgCodeScheme_e			tMsgCoding;                /*<4> (enum=32bit)<->T_msgCoding Msg Coding              */
  SMS_MsgClass_e				tMsgClass;                 /*<4> (enum=32bit)<->T_msgClass Msg Class                */
  u8							u8CompressedText;          /*<1> compressedText                                     */
  u8							u8MsgWaitingIndPresent;    /*<1> msgWaitingIndPresent                               */ 
} SMS_DCS_t;

//
//SMS TPDU User Data Header
//

#define e7bits                  7
#define e8bits                  8
#define e16bitPacketChars      70
#define e8bitPacketBytes      140
#define e7bitPacketChars      160	


/* IEI for User Data Header */
#define SMS_IEI_Concat8bitRn	0x00
#define SMS_IEI_Concat16bitRn   0x08
#define SMS_IEI_AddrPort8bit    0x04
#define SMS_IEI_AddrPort16bit   0x05
#define SMS_IEI_WCMP			0x09
#define SMS_IEI_ExtendedObject  0x14
#define SMS_IEI_NLSingleShift   0x24
#define SMS_IEI_NLLockShift     0x25

#define SMS_IEID_NLIdTurkish     0x01
#define SMS_IEID_NLIdSpanish     0x02
#define SMS_IEID_NLIdPortuguese  0x03
#define SMS_IEID_NLIdBengali     0x04
#define SMS_IEID_NLIdGujarati    0x05
#define SMS_IEID_NLIdHindi       0x06
#define SMS_IEID_NLIdKannada     0x07 
#define SMS_IEID_NLIdMalayalam   0x08 
#define SMS_IEID_NLIdOriya       0x09
#define SMS_IEID_NLIdPunjabi     0x0a
#define SMS_IEID_NLIdTamil       0x0b
#define SMS_IEID_NLIdTelugu      0x0c
#define SMS_IEID_NLIdUrdu        0x0d


/* IEI Data Extended Object Type Identifier*/
#define SMS_IEID_EO_TypeIdentifier_VCard 0x09


/* IEI data byte length for Data Header */
#define UDHL_LEN  0x01
// byte len of IEI ID field
#define IEI_ID_LEN 0x01
// byte len of IEI data length field
#define IEI_IEDL_LEN 0x01
   
#define IEI_NL_TotalLen (IEI_ID_LEN+IEI_IEDL_LEN+1)
// msg reference number
#define IEI_Concat8bitRn_MR 0x01
// max total msg num of this concatenated msg
#define IEI_Concat8bitRn_MN 0x01
// current sequence number
#define IEI_Concat8bitRn_SN 0x01
//for concatenate SMS IED length
#define IEI_Concat8bitRn_IEDL 0x03
#define IEI_Concat8bitRn_TotalLen (IEI_ID_LEN+IEI_IEDL_LEN+IEI_Concat8bitRn_IEDL)
// 16 bit port, including send and receive
#define IEI_AddrPort16bit_IEDL 0x04
#define IEI_AddrPort16bit_TotalLen (IEI_ID_LEN+IEI_IEDL_LEN+IEI_AddrPort16bit_IEDL)
// 8 bit port, including send and receive. Decrepate now.   
#define IEI_AddrPort8bit_IEDL 0x02


#define SMS_CONCAT_SMS_IND_8BIT 0x00
#define SMS_CONCAT_SMS_IND_16BIT 0x08

#define SMS_CONCAT_IEI_LENGTH_8BIT 0x03
#define SMS_CONCAT_IEI_LENGTH_16BIT 0x04

//PID
#define SMS_PID_IMPLICIT                0
#define SMS_PID_TELEX                   1
#define SMS_PID_TELEFAX_G3              2
#define SMS_PID_TELEFAX_G4              3
#define SMS_PID_VOICE_MAIL              4
#define SMS_PID_ERMES                   5
#define SMS_PID_PAGING                  6
#define SMS_PID_VIDEOTEX                7
#define SMS_PID_TELETEX_UNSPECIFIED     8
#define SMS_PID_TELETEX_PSPDN           9
#define SMS_PID_TELETEX_CSPDN           10
#define SMS_PID_TELETEX_PSTN            11
#define SMS_PID_TELETEX_ISDN            12
#define SMS_PID_UCI                     13
#define SMS_PID_MESSAGE_SC              16
#define SMS_PID_MESSAGE_X400            17
#define SMS_PID_EMAIL                   18
#define SMS_PID_CONVERT_DEFAULT         31
#define SMS_PID_BASE_VALUE              0

#define SMS_SUBMIT_DCS_BASE_VALUE       16

/* CB fields for static byte length */
/* CB Header Fiels */
//Serial Number
#define CB_SN	      2
//Message Identifier
#define CB_MI	      2
//Data Coding Scheme
#define CB_DCS	      1
//Page Parameter    
#define CB_PP	      1

#define CB_GS_MASK	   0xC0
#define CB_GS_ICW	   0x00
#define CB_GS_PLMNW	   0x40
#define CB_GS_LAW	   0x80
#define CB_GS_NCW	   0xC0


typedef enum
{
	SMS_CB_GS_ICW,	
	SMS_CB_GS_PLMNW,
	SMS_CB_GS_LAW,
	SMS_CB_GS_NCW
}SMS_CB_GS;

#define CB_8bitsDataSize  82
#define CB_7bitsDataSize  93  

/* Wap Push Inline String (WBXML) */
#define WapPush_InlineStringFollows  0x03
#define WapPush_EndofInlineString    0x00

#endif  /*__MMI_COMMON_SMS_TPDU_H__*/
