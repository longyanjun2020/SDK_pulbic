/**
*Copyright Statement:
*
*
* @file    mms_pars.h
* @author  joe <joe.hsu@mstarsemi.com>
* @date    2008/12/21
*
* function declaration & macro definition for 3rd party porting
*
\verbatim
Copyright Statement:
  Mstar Semiconductor
History(version):
  2008.12.21 joe.hsu created the first version
\endverbatim
*/
#ifndef     __MMS_PORTING_H__ //to prevent from re-including
#define    __MMS_PORTING_H__

#ifdef __cplusplus
extern "C" {
#endif

#include "vm_types.ht"
#include "sys_vm_dbg.ho"
#include "vm_stdio.ho"
#include "cus_os.hc"
#include "ms_defs.h"
//#include "vendor_task.hi"
#include "vm_msgof.hc"

#include "ncc_types.h"
#include "nccsms_push.h"
#include "nccconsms.h"
//#include "nccpush_co.h"
#include "nccpush_common.h"
#include "nccpush_manager.h"
//#include "nccpush_si.h"
//#include "nccpush_sl.h"
#include "nccmms.h"
#include "nccmms_charset.h"
#include "nccmms_cps.h"
#include "nccmms_par.h"
#include "nccmms_prot.h"
#include "nccmms_fs.h"
#include "nccmms_network.h"
#include "nccport_mms_fs.h"
#include "nccwsp.h"
//#include "cdmmsMsg.h"

#define _TRACE_MMS  (_MSERV28)

#define IMSI_LEN    9

#define VENDOR_TIMER_ID_0                   0
#define VENDOR_TIMER_ID_1                   1
#define VENDOR_TIMER_ID_2                   2

#define SCREEN_WIDTH                        240
#define SCREEN_HEIGHT                       320
#define MMS_POLLING_TIMER                   VENDOR_TIMER_ID_0
#define MMS_TIMEOUT_TIMER                   VENDOR_TIMER_ID_1
#define MMS_DATALINK_TIMEOUT_TIMER          VENDOR_TIMER_ID_2
#define MMS_POLLING_ELAPSE                  200
#define MMS_TIMEOUT_ELAPSE                  600*1000 //240*1000 // extand time out 240-->600, some operators need more time to retrieve.
#define MMS_DATALINK_TIMEOUT_ELAPSE           5*1000
#define MMS_MAX_RECEIVE_LIST                312

#define MMS_MAX_ADDR_INFO	                40
#define MMS_MAX_SUBJECT_LEN                 120 // byte length
#define MMS_MAX_FILEPATH_LEN                128
#define MMS_MAX_COMMAND_QUEUE_LEN           5

typedef enum
{
    MMS_CMD_NONE =0,
    MMS_CMD_CreateDataLink,
    MMS_CMD_Cancel,
    MMS_CMD_CloseDataLink
    
}MMS_CMD;

    typedef enum
    {
        NET_TRANS_IDLE,
        NET_TRANS_BUFR,        //sending buffer
        NET_TRANS_BOX,       //sending mail with id
        NET_TRANS_RECEIVING,   //receiving mail
        NET_TRANS_NOTI_RESP,   //delivery report response
#ifdef __MMS_READ_REPORT__
        NET_TRANS_READ_REPLY   //read reply
#endif
    }T_NET_STATUS;

	typedef enum
    {
        MMS_TRANS_NONE,
        MMS_TRANS_SENDING,       //sending mail with id
        MMS_TRANS_RECEIVING,   //receiving mail
        MMS_TRANS_NOTI_RESP,	//send notificaion rsp
#ifdef __MMS_READ_REPORT__
        MMS_TRANS_READ_REPLY
#endif
    }MMS_TRANS_STATUS;

    typedef struct //return Send or Receive mms state and event
    {
        //MMS_event_t ev;
        bool        bWaitEndDataLink;
    }MMS_WaitEndDataLink_Info;
    typedef struct //according to MMS_FS_MAILBOX to name, don't modify it
    {
        s32    diInbox;
        s32    diSentbox;
        s32    diOutbox;
        s32    diDraftbox;
        s32    diOtherbox;
        s32    diPushbox;
        s32    diUnread;
    }MMS_MBox_Info;

    typedef struct
    {
        s32    diTo;        //the total number of To, if diTo < 0, stands for error number
        s32    diCc;        //the total number of cc, if diCc < 0, stands for error number
        s32    diBcc;       //the total number of Bcc,if diBcc< 0, stands for error number

        u8*    pToList;     //pointer to To list  in pListData, null terminate
        u8*    pCcList;     //pointer to Bc list  in pListData, null terminate
        u8*    pBccList;    //pointer to Bcc list in pListData, null terminate

        u8     pListData[MMS_MAX_RECEIVE_LIST+1];
    }MMS_Receiver_List;

    typedef struct
    {
        void       *mmsFsParHandle;
        MMS_Handle  parHandle;      //as MMS_Handle
    }MMS_Parse_Handle;

    typedef struct
    {
        T_SMIL_TextStruct  text;
        u8*                pUtf8String; //convert text.TextStruct.buf to UTF8 string
        s32                diUtf8Strlen;
    }T_SMIL_TextCntx;

    typedef struct
    {
        T_SMIL_TextCntx    text;
        T_SMIL_ImgStruct   image;
        T_SMIL_AudStruct   audio;
        T_SMIL_VideoStruct video;
        s32                diDuration;
    }MMS_Slide_Cntx;

    typedef struct MMS_Slide_Link_t
    {
        s32                   diSlideDur;  //the current slide duration
        struct
        {
            u8*					pText;      //text data buffer, should be UTF8 TXT
            s32					diTextLen;  //text byte length
            MMS_BasicRegion		region;
        }TxtUnit;

        struct
        {
            u8*					pImage;      //image data buffer
            u8*					pImageType;  //image type
            s32					diImageLen;  //image byte length
            u8					name[100];
			MMS_BasicRegion		region;
        }ImgUnit;

        struct
        {
            u8*					pAudio;      //audio data buffer
            u8*					pAudioType;  //audio type
            s32					diAudioLen;  //audio byte length
            u8					name[100];
        }AudioUnit;

        struct
        {
            u8*					pVideo;      //video data buffer
            u8*					pVideoType;  //video type
            s32					diVideoLen;  //video byte length
            u8					name[100];
			MMS_BasicRegion		region;
        }VideoUnit;

        struct MMS_Slide_Link_t*  pNextSlide;  // the next slide key field
    }MMS_Slide_Link;

    typedef struct  MMS_AtchNames_List_t
    {
        u8*                          pAtchName;
        struct MMS_AtchNames_List_t* pNextAtchName;
    }MMS_AtchNames_List;


    typedef struct MMS_Attach_Link_t
    {
        T_Composer_Attach        tca;
        struct MMS_Attach_Link_t*  pNextAttach;
    }MMS_Attach_Link;

    typedef struct
    {
        u8*    pSubject;   //UTF8 format
        s32    diSubLen;   //memory byte length
    }MMS_Subject;
    typedef struct
    {
        MMS_Attach_Link      *pMal;
        MMS_Slide_Link       *pMsl;
        MMS_Receiver_List    *pMrl;
        MMS_Subject          *pMs;
    }MMS_Composer_Cntx;

    typedef struct
    {
        s32                 SlideCount;
        MMS_Slide_Cntx**    pSlide;
        MMS_Parse_Handle    MMSParse;
    }MMS_GET_SLIDES;

    typedef struct
    {
        s32                 AttachCount;
        T_MMS_Attach**      ppAttaches;
        MMS_Parse_Handle    MMSParse;
    }MMS_GET_ATTACHES_t;

    typedef struct
    {
        s32                             itemIndex;
        MMS_FS_MAILBOX    mailboxIdx;
    }MMS_DelMail;

    typedef struct
    {
        s32                             itemIndex;
    }MMS_RecvMail;

    typedef struct
    {
        u8             type;
        s32            status;
        s32            msgIdx;
        MMS_FS_MAILBOX mailBox;
        u32            date;
        u32            mmsContentSize;
        u8             subjectInfo[MMS_MAX_SUBJECT_LEN+1];
        u8             addrInfo[MMS_MAX_ADDR_INFO+1];
        u8             mmsToAddr[MMS_MAX_RECEIVE_LIST+1];
        u8             mmsCcAddr[MMS_MAX_RECEIVE_LIST+1];
        u8             mmsBccAddr[MMS_MAX_RECEIVE_LIST+1];
		u8			   imsi[MMS_FS_MAX_IMSI_LEN];
    }MMS_CdMms_Info_t;

	typedef struct
    {
        s32 status;
    }MMS_BootupCnf_t;

    typedef struct
    {
        s32 				msgIdx;
        MMS_FS_MAILBOX 		mailBox;
        MMS_Composer_Cntx 	mmsComposerCntx;
 	  	u8  imsi[MMS_FS_MAX_IMSI_LEN];
        u8                  *pAppId;
        u8                  *pReplyToAppId;
	    bool                isSDKMsg;
    }MMS_SaveMmsReq_t;

    typedef struct
    {
        s32  index;
        s32 status;
		s32 contentSize;
		MMS_FS_MAILBOX 	mailBox;
        bool            isSDKMsg;
    } MMS_SaveMmsCnf_t;

    typedef struct
    {
        s32 msgIdx;
        MMS_FS_MAILBOX mailBox;
    }MMS_GetMmsReceiverListReq_t;

    typedef struct
    {
        s32 status;
        MMS_Receiver_List mmsRecvList;
    }MMS_GetMmsReceiverListCnf_t;

    typedef struct
    {
        s32 msgIdx;
        MMS_FS_MAILBOX mailBox;
    }MMS_GetMmsSenderAddrReq_t;

    typedef struct
    {
        s32 status;
        u8 senderNum[MMS_MAX_RECEIVE_LIST+1];
    }MMS_GetMmsSenderAddrCnf_t;

    typedef struct
    {
        s32 msgIdx;
        MMS_FS_MAILBOX mailBox;
    }MMS_GetMmsItemInfoReq_t;

    typedef struct
    {
        s32 status;
        T_MmsFs_itemInfo mmsItemInfo;
    }MMS_GetMmsItemInfoCnf_t;

    typedef struct
    {
        s32 msgIdx;
        MMS_FS_MAILBOX mailBox;
    }MMS_GetMmsSubjectInfoReq_t;

    typedef struct
    {
        s32 status;
        u8 subjectInfo[MMS_MAX_SUBJECT_LEN+1];
    }MMS_GetMmsSubjectInfoCnf_t;

    typedef struct
    {
        s32 msgIdx;
        MMS_FS_MAILBOX mailBox;
    }MMS_GetMmsStatusInfoReq_t;

    typedef struct
    {
        s32 status;
        u8 mmsStatus;
    }MMS_GetMmsStatusInfoCnf_t;

    typedef struct
    {
        s32 msgIdx;
        MMS_FS_MAILBOX mailBox;
    }MMS_GetMmsAllSlidesReq_t;

    typedef struct
    {
        s32 status;
        MMS_GET_SLIDES *pSlideData;
    }MMS_GetMmsAllSlidesCnf_t;

    typedef struct
    {
        s32 attachIdx;
        MMS_Parse_Handle mmsHandle;
    }MMS_GetAttachCntxReq_t;

    typedef struct
    {
        s32 msgIdx;
        u8 SimModule;
		u8 imsi[MMS_FS_MAX_IMSI_LEN];
        MMS_FS_MAILBOX mailBox;
        T_MmsFs_Config mmsCnfg;
    }MMS_SendMmsByBoxReq_t;

    typedef struct
    {
        s32 status;
        s32 index;
        u32 time;
        MMS_FS_MAILBOX mailBox;
    }MMS_SendMmsByBoxCnf_t;

    typedef struct
    {
        s32 status;
    }MMS_TransCancelCnf_t;

    typedef struct
    {
		T_MmsFs_Config mmsCnfg;
        s32 msgIdx;
        MMS_FS_MAILBOX mailBox;  
#ifdef __MMS_DOWNLOAD_LIMIT__
        u32 nMaxDlmSize;
#endif
        u8 SimModule;
    }MMS_RecvMmsBodyReq_t;

    typedef struct
    {
        MMS_CdMms_Info_t  pCdMmsInfo;
    }MMS_RecvMmsBodyCnf_t;

    typedef struct
    {
        s32 msgIdx;
        MMS_FS_MAILBOX mailBox;
    }MMS_DelMmsByIdReq_t;

    typedef struct
    {
        s32 status;
    }MMS_DelMmsByIdCnf_t;

    typedef struct
    {
        MMS_FS_MAILBOX mailBox;
    }MMS_DelMmsByBoxReq_t;

    typedef struct
    {
        s32 status;
    }MMS_DelMmsByBoxCnf_t;

    typedef struct
    {
        s32 msgIdx;
        MMS_FS_MAILBOX mailBox;
    }MMS_GetMmsAllAttachesReq_t;

    typedef struct
    {
        s32     status;
        MMS_GET_ATTACHES_t  *pAttachData;
    }MMS_GetMmsAllAttachesCnf_t;

    typedef struct
    {
        s32 DataLength;
        u8  imsi[MMS_FS_MAX_IMSI_LEN];
        u8  PduData[175*9]; //for WAP push data
        u8  from[MMS_FS_MAX_NUMBER_LEN + 1];
		u8  allowAnon;
    }MMS_NewMmsNote_t;

    typedef struct
    {
        s32 msgIdx;
        MMS_FS_MAILBOX mailBox;
        T_MmsFs_headInfo headInfo;
        T_MmsFs_itemInfo itemInfo;
    }MMS_NewMmsNoteCnf_t;

    typedef struct
    {
        MMS_FS_MAILBOX mailBox;
    }MMS_RetrvCdMmsReq_t;

    typedef struct
    {
        s32     boxSum;
        MMS_CdMms_Info_t  *pCdMmsInfo;
    }MMS_RetrvCdMmsCnf_t;

	typedef struct
    {
        T_MmsFs_Config mmsCnfg;
        s32 msgIdx;
        MMS_FS_MAILBOX mailBox;
        u8 SimModule;
    }MMS_SendNotiRespReq_t;

    typedef struct
    {
        s32 status;
    }MMS_SendNotiRespCnf_t;
#ifdef __MMS_READ_REPORT__
	typedef struct
    {
        T_MmsFs_Config mmsCnfg;
        s32 msgIdx;
        MMS_FS_MAILBOX mailBox;
        u8 SimModule;
    }MMS_SendReadReplyReq_t;

    typedef struct
    {
        s32 status;
    }MMS_SendReadReplyCnf_t;
#endif
	typedef struct
    {
        s32 msgIdx;
        MMS_FS_MAILBOX SourceMailBox;
		MMS_FS_MAILBOX DesMailBox;
    }MMS_MoveMmsReq_t;


    typedef struct
    {
	    s32 newMsgIdx;
        s32 status;
		MMS_FS_MAILBOX DesMailBox;
    }MMS_MoveMmsCnf_t;

	typedef struct
    {
        u8 nPathLen;
        u8 pPath[MMS_MAX_FILEPATH_LEN+1];
        u8 devType;
    }MMS_SetStorePathInd_t;
#ifdef __MMS_MMI_CDMMS_STORAGE_SWITCH__
    typedef struct
    {
        s32                 msgIdx;
        MMS_FS_MAILBOX      mailBox;
    } MMS_GetRawItemReq_t;

    typedef struct
    {
        s32                 status;
        T_MmsFs_headInfo    *headInfo;
        T_MmsFs_itemInfo    *itemInfo;
        uint8_t             *buffer;
        int32_t             bufferLen;
    } MMS_GetRawItemCnf_t;

    typedef struct
    {
        T_MmsFs_headInfo    *headInfo;
        T_MmsFs_itemInfo    *itemInfo;
        uint8_t             *buffer;
        int32_t             bufferLen;
        MMS_FS_MAILBOX      mailBox;
    } MMS_SaveRawItemReq_t;

    typedef struct
    {
        s32                 status;
        s32                 msgIdx;
    } MMS_SaveRawItemCnf_t;
#endif

void MMS_CallBack(void *pMessage);
void MmsDataLinkTimeOut(void);
void MmsPollingTransStatus(void);
void MmsTransTimeOut(void);

#ifdef __cplusplus
}
#endif

#endif  //__MMS_PORTING_H__
