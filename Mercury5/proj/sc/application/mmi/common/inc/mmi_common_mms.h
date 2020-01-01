/**
 *  @file   mmi_common_mms.h
 *  @brief  it is used for communination within different Applications/Services in mms utility functions.
 *  
 * @version $Id: mmi_common_mms.h 16008 2008-11-06 08:27:21Z joe.hsu $
 * @author	joe.hsu
 */
#ifndef __MMI_COMMON_MMS_H__
#define __MMI_COMMON_MMS_H__

#include "mmi_mae_common_def.h"
#include "mmi_common_custom.h"
#include "mmi_mae_shell.h"
//#include "mae_view.h"
#include "mmi_mae_vectormodel.h"

#define MMS_PATH  L".system/MMS"     // The path name should be same as MMSPATH which is defined in MMS_PARS.h

#define MMI_MMS_MAX_RECEIVE_LIST  312
#define MMI_MMS_FS_MAX_IMSI_LEN 10
#define MMI_MMS_MAX_SUBJECT_CHAR (40) // MAX  40 chars
#define MMI_MMS_MAX_SUBJECT_LEN (120) //for utf8 3*40 chinese
#define MMI_MMS_MAX_DISPLAY_SUBJECT_CHAR (40)
#define MMI_MMS_MAX_ADDR_INFO	  40
#define MMI_MMS_MAX_SLIDE_NUMBER (20)
#if defined(__APP_MMI_SMALLROM__)
#define MMI_MMS_MAX_AMOUNT		(30)
#else
#define MMI_MMS_MAX_AMOUNT		(100)
#endif

#define MMS_MMSC_MAX_LEN 66
#define MMS_GATEWAY_MAX_LEN 34
#define MMS_PROXY_LEN 40
#define MMS_APN_MAX_NUM 30
#define MMS_USERNAME_MAX_LEN 30
#define MMS_PASSWORD_MAX_LEN 30

#define MMS_1_HOUR 3600
#define MMS_6_HOUR 6*MMS_1_HOUR
#define MMS_12_HOUR 12*MMS_1_HOUR
#define MMS_24_HOUR 24*MMS_1_HOUR
#define MMS_72_HOUR 72*MMS_1_HOUR
#define MMS_1_WEEK 7*MMS_24_HOUR
#define MMS_LONGEST 0

#define MMS_FULLDATA_LIMIT_SIZE_KB	100
#define MMS_HEAD_LIMIT_SIZE_KB	1

#define MMI_MMS_MAX_EDITOR_TEXT_LEN (2000)

#define MMI_MMS_MAX_OBJECT_NAME_LEN	100
#define MMI_MMS_MAX_ATTACHMENTS_NUMBER	20

#define MMI_PROV_LENGTH_NAME 48 /**< the length(byte) of NAME */
#define MMI_PROV_LENGTH_NAP_ADDRESS 64 /**< the length(byte) of NAP-ADDRESS */
#define MMI_PROV_LENGTH_AUTHNAME 16 /**< the length(byte) of AUTHNAME */
#define MMI_PROV_LENGTH_AUTHSECRET 16 /**< the length(byte) of AUTHSECRET */
#define MMI_PROV_LENGTH_DNS_ADDR 45 /**< the length(byte) of DNS-ADDR */
#define MMI_PROV_LENGTH_ADDR 64 /**< the length(byte) of ADDR */
#define MMI_PROV_NAPAUTH_TYPE_PAP   1 /**< Password Authentication Protocol type */
#define MMI_PROV_NAPAUTH_TYPE_CHAP  2 /**< Challenge Handshake Authentication Protocol type */
#define MMI_PROV_NAPAUTH_TYPE_MD5   3 /**< The MD5 Message-Digest Algorithm authentication type */

/*mms message type*/
#define MMS_MMS_NOTIFY              0x01
#define MMS_DELIVERY_REPORT         0x02
#define MMS_READ_REPORT_PDU         0x03
#define MMS_MMS_PDU                 0x05
#define MMS_PROVISION_MESSAGE       0x0B

/*mms status type*/
#define MMS_STATUS_NEW              0x01
#define MMS_STATUS_OLD              0x02

enum 
{
    MMS_OBJECT_NONE = 0x00,
    MMS_OBJECT_IMAGE =0x01,
    MMS_OBJECT_AUDIO =0x02,
    MMS_OBJECT_VIDEO =0x04,
    MMS_OBJECT_VCS   =0x08,    
    MMS_OBJECT_TEXT  =0x10,
    MMS_OBJECT_ATTACHMENT  =0x20,
};
typedef u8 MMI_MmsObjectType_e;


enum  {
	MMI_MMS_SUCCESS	= 0,
    MMI_MMS_FAIL,
	MMI_MMS_NEW_FILE,
	MMI_MMS_BOX_FULL,
	MMI_MMS_NO_BUF,
    MMI_MMS_PERMANENT_FAIL,
    MMI_MMS_ERROR_OVERSIZE,
    MMI_MMS_SUCCESS_BUT_FS_FATAL_ERROR,
    MMI_MMS_UNKNOWN
} ;
typedef u8 MMI_MmsStatus_e;

enum  {
	MMI_MMS_MM_Expired	= 0x80,
    MMI_MMS_MM_Retrieved,    
	MMI_MMS_MM_Rejected,
	MMI_MMS_MM_Deferred,
	MMI_MMS_MM_Unrecognised,
	MMI_MMS_MM_Indeterminate,
	MMI_MMS_MM_Forwarded,
	MMI_MMS_MM_Unreachable
} ;
typedef u8 MMI_MmsMmStatus_e;

/*mail box list*/
enum
{
    MMI_MMS_FS_INBOX = 0,
    MMI_MMS_FS_SENTBOX,
    MMI_MMS_FS_OUTBOX,
    MMI_MMS_FS_DRAFTBOX,
    MMI_MMS_FS_OTHERBOX,
    MMI_MMS_FS_PUSHBOX,
    MMI_MMS_FS_MAILBOX_MAX
};

typedef u8 MMI_MMS_FS_MAILBOX_e;

enum MMI_MMS_Region_Fit_Value {
    MMI_MMS_REGION_FIT_FILL = 0,        /**<Scale the object's height and width independently so that the content just touches all edges of the box*/
    MMI_MMS_REGION_FIT_HIDDEN,      /**<Has the following effect:
                                        If the intrinsic height (width) of the media object element is smaller than the height (width) defined in the region element,
                                            render the object starting from the top (left) edge and fill up the remaining height (width) with the background color.
                                        If the intrinsic height (width) of the media object element is greater than the height (width) defined in the region element,
                                            render the object starting from the top (left) edge until the height (width) defined in the region element is reached, and clip the parts of the object below (right of) the height (width). */
    MMI_MMS_REGION_FIT_MEET,            /**<Scale the visual media object while preserving its aspect ratio until its height or width is equal to the value specified by the
                                            height or width attributes, while none of the content is clipped. The object's left top corner is positioned at the top-left
                                            coordinates of the box, and empty space at the right or bottom is filled up with the background color*/
    MMI_MMS_REGION_FIT_SCROLL,      /**<A scrolling mechanism should be invoked when the element's rendered contents exceed its bounds*/
    MMI_MMS_REGION_FIT_SLICE            /**<Scale the visual media object while preserving its aspect ratio so that its height or width are equal to the value specified
                                            by the height and width attributes while some of the content may get clipped. Depending on the exact situation,
                                            either a horizontal or a vertical slice of the visual media object is displayed. Overflow width is clipped from the right of
                                            the media object. Overflow height is clipped from the bottom of the media object*/
};

/**
 * attach structure
 */
typedef struct MMI_MMS_Composer_Attach {
    u8 *AttBuf;                        /**<used to save attachment data*/
    s8 *Type;                        /**<used to save attachment's type  */
    s32 size;                            /**<used to save attachment's size*/
    s8 *Name;                        /**<used to save attachment's name*/
    s32 warningmode;                /**<used to save used to current create mode */
} MMI_MMS_Composer_Attach_t;

typedef struct MMI_MMS_Attach {
    u8 *AttBuf;                         /**<attachment data buffer*/
    s8 *Type;                           /**< attchment  type  */
    s8 *Name;                           /**< attchment name  */
    s32 size;                           /**<size of attchment data*/
} MMI_MMS_Attach_t;

/**
 * Structure Type that indicates region value.
 */
typedef struct MMI_Parser_PosTp {
    s32 xco;                    /**<Xcoordinate*/
    s32 yco;                    /**<Ycoordinate*/
    s32 width;                  /**<display width */
    s32 height;                 /**<display height*/
    enum MMI_MMS_Region_Fit_Value fit;
} MMI_MMS_BasicRegion;

/*
typedef struct MMI_MMS_Attach_Link_t
{
    MMI_MMS_Composer_Attach        tca;
    struct MMI_MMS_Attach_Link_t*  pNextAttach;
}MMI_MMS_Attach_Link;
*/
typedef struct MMI_MMS_Slide_Link_TAG
{
    s32                   diSlideDur;  //the current slide duration    
    struct{
        u8*               		pText;      //text data buffer, should be UTF8 TXT
        s32               		diTextLen;  //text byte length		
        MMI_MMS_BasicRegion 	region;
    }TxtUnit;
    
    struct{
        u8*						pImage;      //image data buffer
        u8*						pImageType;  //image type
        s32						diImageLen;  //image byte length
		u8						name[MMI_MMS_MAX_OBJECT_NAME_LEN];
		MMI_MMS_BasicRegion 	region;
    }ImgUnit;

    struct{    
        u8*						pAudio;      //audio data buffer
        u8*						pAudioType;  //audio type
        s32						diAudioLen;  //audio byte length
		u8						name[MMI_MMS_MAX_OBJECT_NAME_LEN];
    }AudioUnit;

    struct{
        u8*						pVideo;      //video data buffer
        u8*						pVideoType;  //video type
        s32						diVideoLen;  //video byte length
		u8						name[MMI_MMS_MAX_OBJECT_NAME_LEN];
		MMI_MMS_BasicRegion 	region;
    }VideoUnit;
    
//    struct MMI_MMS_Slide_Link_t*  pNextSlide;  // the next slide key field
}MMI_MMS_Slide_Link_t;

typedef struct
{
    s32    diTo;        //the total number of To, if diTo < 0, stands for error number
    s32    diCc;        //the total number of cc, if diCc < 0, stands for error number
    s32    diBcc;       //the total number of Bcc,if diBcc< 0, stands for error number
    
    u8*    pToList;     //pointer to To list  in pListData, null terminate
    u8*    pCcList;     //pointer to Bc list  in pListData, null terminate
    u8*    pBccList;    //pointer to Bcc list in pListData, null terminate
    
    u8     pListData[MMI_MMS_MAX_RECEIVE_LIST+1];  
}MMI_MMS_Receiver_List_t;

typedef struct
{
    u8*    pSubject;   //UTF8 format
    s32    diSubLen;   //memory byte length
}MMI_MMS_Subject_t;

typedef struct
{
    IVectorModel             *pMal; // MMI_MMS_Composer_Attach
    IVectorModel             *pMsl; //MMI_MMS_Slide_Link_t
    MMI_MMS_Receiver_List_t    *pMrl;        
    MMI_MMS_Subject_t          *pMs;
	u8 						 eSIMModule; // for outbox saving to store imsi
    u8                      *pAppId;
    u8                      *pReplyToAppId;
	boolean                 isSDKMsg;
}MMI_MMS_Composer_Cntx;


/*mms pdu head info*/
typedef struct
{
    u32 deliveryReport;   /*if need delivery report*/
    u32 readReply;           /*if need read report*/
    u32 senderVisibility;  /*if the sender is visibility*/
    u8 *transactionId; /*the transaction id*/
    u8 *from;  /*the from field*/
    u8 *to;      /*the to field*/
    u8 *cc;      /*the cc field*/
    u8 *bcc;    /*the bcc field*/
    u8 *subject;
    u32 mmsExpiry;   /*the expire time*/
    u32 mmsDelieveryTime;  /*the delivery time*/
    u32 mmsPriority;             /*the priority*/
    u32 mmsMessageClass;   /*the message class*/
    u32 contentSize;              /*the content size*/
    u32 date;                          /*the parsed date*/
    u32 status;                       /*the status of mms report*/
}MMI_MmsFs_headInfo;

/*message information*/
typedef struct
{
    u8 status;  /*the item's status, see mms status type*/
    u8 type;     /*the item's type, see mms message type*/
    u8 flag;      /*flag*/
    u8 extension;  /*extension*/
    u32 time;           /*last modified time*/
    s32 itemLen;       /*the item's body buffer length*/
    u8 imsi[MMI_MMS_FS_MAX_IMSI_LEN];

 }MMI_MmsFs_itemInfo;

typedef struct
{
    s32 deferDownload;                 /*if defer download or auto download*/
    s32 deliveryReport;                 /*if need delivery report*/
    s32 readReport;                       /*if need read report*/
    s32 senderVisibility;                 /*if the sender is visibility*/
    s32 mmsExpiry;                        /*the expire time of a mms notification*/
    s32 mmsPriority;                      /*the priority of a new mms*/
    s32 playSound;                         /*if play sound when preview and play mms*/
    s32 receiveAD;                         /*if accept reveive advertisement*/
    s32 autoSign;                            /*the auto signature is on or off*/
    s32 imageStoreDev;                 /*the image store device usb root or sd card*/
    s32 audioStoreDev;                 /*the audio store device usb root or sd card*/
    s32 videoStoreDev;                 /*the video store device usb root or sd card*/
    s32 protocol_mask;                  /**< used to select the suitable stack which is wap or http*/
    s8 mmsc_addr[MMS_MMSC_MAX_LEN];    /**< used to save the address of mms center*/
    s8 gateway[MMS_GATEWAY_MAX_LEN];        /**< used to save the address of gateway*/
    s32 gateway_port;                   /**< used to save the port number of gateway*/
    s8 proxy[MMS_PROXY_LEN];            /**< used to save the address of HTTP proxy when using http stack*/
    s32 proxy_port;                     /**< used to save the port number of gateway when using http stack*/
    s32 up_limit;                       /**< used to save the max transport bitrate*/
    s32 low_limit;                      /**< used to save the min transport bitrate*/
    s8 APN[MMS_APN_MAX_NUM];        /**< string buf used for saving APN name*/
    s8 user[MMS_USERNAME_MAX_LEN];       /**< string buf used for saving APN user name*/
    s8 passwd[MMS_PASSWORD_MAX_LEN];   /**< string buf used for saving APN user passward*/
}MMI_MmsFs_Config;

////////////////////////////////////////////For Get Slide //////////////////////////////////////



/**
 * Structure for parser module
 */

typedef struct MMI_MMS_Parser_BasicStructure {
    u8 *Buf;   /**< the basic string of the basic element */
    s8 *Alt;        /**< the alt value of the basic element  */
    s32 Size;   /**<the length of the basic element*/
    s32 Begin;      /**< the begin time of the basic  element */
    s32 End;        /**< the end time of the basic element*/
    s8 *Type;   /**<the type of the basic element*/
    s8 *Name;  /* file name*/
} MMI_MMS_Parser_BasicStructure;


/**
 * Structure Type that defines some information of Text resource.
 */
typedef struct MMI_MMS_SMIL_TextStruct {
    MMI_MMS_BasicRegion txtPos;                     /**<text show position ,may be need less*/
    MMI_MMS_Parser_BasicStructure TextStruct;     /**<the basic attribute of the Text*/
    u8 FG_color[12];                       /**<the foreground-color value of the text*/
    s8 Textsize[8];                         /**<the size value of the text */
    s8 Textattribute[12];                   /**<the attribute of the text*/
    u8 BGcolor[12];                        /**<the background-color of the text*/
} MMI_MMS_SMIL_TextStruct;

typedef struct
{
    MMI_MMS_SMIL_TextStruct  text;
    u8*                pUtf8String; //convert text.TextStruct.buf to UTF8 string
    s32                diUtf8Strlen;
}MMI_MMS_SMIL_TextCntx; 

/**
 * Structure Type that defines some information of image resource.
 */
typedef struct MMI_SMIL_ImgStruct {           /**<record image info of MMS display which is in process*/
    MMI_MMS_BasicRegion graphPos;               /**<image display position ,may be needless*/
    MMI_MMS_Parser_BasicStructure ImageStruct;    /**<the common attribute and other media */
    u8 BGcolor[12];                        /**<the background-color of the Image*/
} MMI_MMS_SMIL_ImgStruct;

/**
 * Structure Type that defines some information of Audio resource.
 */
typedef struct MMI_MMS_SMIL_AudStruct {
    MMI_MMS_Parser_BasicStructure AudioStruct;    /**<the basic attribute of the Audio*/
} MMI_MMS_SMIL_AudStruct;

/**
 * Structure Type that defines some information of video resource.
 */
typedef struct MMI_MMS_SMIL_VideoStruct {         /**<record video info of MMS display which is in process*/
    MMI_MMS_BasicRegion VideoPos;               /**<video display position ,may be needless*/
    MMI_MMS_Parser_BasicStructure VideoStruct;    /**<the common attribute and other media*/
} MMI_MMS_SMIL_VideoStruct;

typedef struct
{
    MMI_MMS_SMIL_TextCntx    text;
    MMI_MMS_SMIL_ImgStruct   image;
    MMI_MMS_SMIL_AudStruct   audio;
    MMI_MMS_SMIL_VideoStruct video;
    s32                diDuration;
}MMI_MMS_Slide_Cntx;

typedef struct
{
    void       *mmsFsParHandle;
	u32		   parHandle;
    //MMS_Handle  parHandle;      //as MMS_Handle
}MMI_MMS_Parse_Handle;

typedef struct
{
    s32                 SlideCount;
    MMI_MMS_Slide_Cntx**    pSlide;
    MMI_MMS_Parse_Handle    MMSParse;
}MMI_MMS_GET_SLIDES;

typedef struct MMI_MMS_AtchNames_List_t
{
    u8*                          pAtchName;
    struct MMI_MMS_AtchNames_List_t* pNextAtchName;
}MMI_MMS_AtchNames_List;

typedef struct
{
    s32                 AttachCount;
    MMI_MMS_Attach_t**  ppAttaches;  
	MMI_MMS_Parse_Handle    MMSParse;
}MMI_MMS_GET_ATTACHES_t;

typedef struct
{
	u8	type;
	s32	status;
	s32 msgIdx;
	MMI_MMS_FS_MAILBOX_e mailBox;
	u32 date;
	u32					mmsContentSize;
	u8 subjectInfo[MMI_MMS_MAX_SUBJECT_LEN+1];
	u8 addrInfo[MMI_MMS_MAX_ADDR_INFO+1];
	u8					mmsToAddr[MMI_MMS_MAX_RECEIVE_LIST+1];
	u8					mmsCcAddr[MMI_MMS_MAX_RECEIVE_LIST+1];
	u8					mmsBccAddr[MMI_MMS_MAX_RECEIVE_LIST+1];
	u8					imsi[MMI_MMS_FS_MAX_IMSI_LEN];
}MMI_MMS_CdMms_Info_t;

typedef struct
{
	u8 MMI_Common_SupportedFileType;
} MMS_support_mimetype_table_t;



enum {
    MMI_MMS_PRIORITY_LOW        = 0x80,
    MMI_MMS_PRIORITY_NORMAL     = 0x81,
    MMI_MMS_PRIORITY_HIGH       = 0x82
};
typedef u8 MMI_MmsPriority_e;

enum {
    MMI_MMS_CLASS_PERSONAL      = 0x80,
    MMI_MMS_CLASS_ADVERTISEMENT = 0x81,
    MMI_MMS_CLASS_INFORMATIONAL = 0x82,
    MMI_MMS_CLASS_AUTO          = 0x83
};
typedef u8 MMI_MmsClass_e;

enum {
    MMI_MMS_CONTENTTYPE_MULTIPARTRELATED,
    MMI_MMS_CONTENTTYPE_MULTIPARTMIXED,
    MMI_MMS_CONTENTTYPE_OTHERS
};
typedef u8 MMI_MmsContentType_e;


typedef struct
{
    u8                      *pFrom;
    u8                      *pTo;
    u8                      *pCc;
    u8                      *pBcc;
    u8                      *pSubject;
    MMI_MmsClass_e          messageClass;
    u32                     expiry;
    u32                     deliveryTime;
    MMI_MmsPriority_e       priority;
    boolean                 senderVisibility;
    boolean                 deliveryReport;
    boolean                 readReply;
    MMI_MmsContentType_e    contentType;
    u8                      *pType;
    u8                      *pStart;
} MMI_MMS_Header_t;

typedef struct
{
    MMI_MmsContentType_e    contentType;
    u8                      *pMIMEType;
    u8                      *pCharset;
    u8                      *pName;
    u8                      *pContentLoc;
    u8                      *pContentId;
    u32                     dataLen;
    void                    *pData;
} MMI_MMS_MsgPart_t;

typedef struct
{
    u32                     numParts;
    MMI_MMS_MsgPart_t       *pMsgParts;
} MMI_MMS_Body_t;

enum
{
    MMI_MMS_RESPONSESTATUS_OK = 0x80,
    MMI_MMS_RESPONSESTATUS_ERROR_UNSPECIFIED,
    MMI_MMS_RESPONSESTATUS_ERROR_SERVICEDENIED,
    MMI_MMS_RESPONSESTATUS_ERROR_FORMATCORRUPT,
    MMI_MMS_RESPONSESTATUS_ERROR_ADDRESSUNRESOLVED,
    MMI_MMS_RESPONSESTATUS_ERROR_MSGNOTFOUND,
    MMI_MMS_RESPONSESTATUS_ERROR_NETWORKPROBLEM,
    MMI_MMS_RESPONSESTATUS_ERROR_CONTENTNOTACCEPT,
    MMI_MMS_RESPONSESTATUS_ERROR_UNSUPPORTEDMSG,
    MMI_MMS_RESPONSESTATUS_ERROR_TRANSIENT_FAILURE = 0xC0,
    MMI_MMS_RESPONSESTATUS_ERROR_TRANSIENT_ADDRESSUNRESOLVED,
    MMI_MMS_RESPONSESTATUS_ERROR_TRANSIENT_MSGNOTFOUND,
    MMI_MMS_RESPONSESTATUS_ERROR_TRANSIENT_NETWORKPROBLEM,
    MMI_MMS_RESPONSESTATUS_ERROR_TRANSIENT_PARTIALSUCCESS,
    MMI_MMS_RESPONSESTATUS_ERROR_PERMANENT_FAILURE = 0xE0,
    MMI_MMS_RESPONSESTATUS_ERROR_PERMANENT_SERVICEDENIED,
    MMI_MMS_RESPONSESTATUS_ERROR_PERMANENT_FORMATCORRUPT,
    MMI_MMS_RESPONSESTATUS_ERROR_PERMANENT_ADDRESSUNRESOLVED,
    MMI_MMS_RESPONSESTATUS_ERROR_PERMANENT_MSGNOTFOUND,
    MMI_MMS_RESPONSESTATUS_ERROR_PERMANENT_CONTENTNOTACCEPT,
    MMI_MMS_RESPONSESTATUS_ERROR_PERMANENT_REPLYCHARGING_LIMITNOTMET,
    MMI_MMS_RESPONSESTATUS_ERROR_PERMANENT_REPLYCHARGING_REQNOTACCEPTED,
    MMI_MMS_RESPONSESTATUS_ERROR_PERMANENT_REPLYCHARGING_FORWARDDENIED,
    MMI_MMS_RESPONSESTATUS_ERROR_PERMANENT_REPLYCHARGING_NOTSUPPORTED,
    MMI_MMS_RESPONSESTATUS_ERROR_PERMANENT_ADDRESSHIDE_NOTSUPPORTED,
    MMI_MMS_RESPONSESTATUS_ERROR_PERMANENT_LACKOFPREPAID,
    
    MMI_MMS_RESPONSESTATUS_LOCAL_UNKNOWNERROR       = 0x00,
    MMI_MMS_RESPONSESTATUS_LOCAL_PARAMERROR         = 0x01,
    MMI_MMS_RESPONSESTATUS_LOCAL_UNSUPPORTED        = 0x02,
    MMI_MMS_RESPONSESTATUS_LOCAL_STORAGEFULL        = 0x03,
    MMI_MMS_RESPONSESTATUS_LOCAL_SERVICESUSPENDED   = 0x04
};
typedef u8 MMS_MmsResponseStatus_e;

void*       MMS_CLEAN_MALLOC( u32 nNumElems, u16 nElemSize );
u32         MMS_GetImageIdByMIME( const char *pMIMETypeStr );
boolean MMS_IsMimeTypeSupported(const char *pMIMEStr);
boolean Mms_IsSupportContentObject(const char *pMIMEStr, u8 *objectType);
MAE_WChar* MMS_GetDefaultName(char *pMIMETypeStr, u8 nIndex, boolean bIsSlideObject);
#endif /* __MMI_COMMON_MMS_H__ */

