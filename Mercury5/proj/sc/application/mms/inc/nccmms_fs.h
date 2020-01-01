/*mms filesystem extern header file*/

#ifndef __NCC_MMS_FS_H__
#define __NCC_MMS_FS_H__

#include <ncc_types.h>

#ifdef __cplusplus
extern "C"{
#endif

/*return value*/
#define MMS_FS_OK 0
#define MMS_FS_FAILED -1
#define MMS_FS_NEW_FILE -2
#define MMS_FS_BOX_FULL -3
#define MMS_FS_NO_BUF -4
#define MMS_FS_PATH_TOOLONG -5
#define MMS_FS_SYSTEM_BUSY -6
#define MMS_FS_INVALID_PARAM -7
#define MMS_FS_NO_MESSAGE -8
#define MMS_FS_EOF -9
#define MMS_FS_FATAL_ERROR -10

/*mms message type*/
#define MMS_FS_MMS_NOTIFY 0x01 /*inbox{body+head}*/
#define MMS_FS_DELIVERY_REPORT 0x02 /*inbox{body+head}*/
#define MMS_FS_READ_REPORT_PDU 0x03 /*inbox{body+head}*/
#define MMS_FS_READ_REPORT_MMS 0x04 /*inbox{body+head}*/
#define MMS_FS_MMS_PDU 0x05 /*inbox{body+head}, outbox{body+head}, sendbox{body+head}, draftbox{body+head}, otherbox{body+head}*/
#define MMS_FS_REJECT_PDU 0x06 /*outbox{body}*/
#define MMS_FS_FORWARD_PDU 0x07 /*outbox{body}*/
#define MMS_FS_DEFERED_PDU 0x08 /*oubbox{body}*/
#define MMS_FS_READREPORT_PDU 0x09 /*outbox{body}*/
#define MMS_FS_PUSH_MESSAGE 0x0a /*pushbox{body}*/
#define MMS_FS_PROVISION_MESSAGE 0x0b /*inbox*/

/*mms status type*/
#define MMS_FS_STATUS_NULL 0x00
#define MMS_FS_STATUS_NEW 0x01
#define MMS_FS_STATUS_OLD 0x02
#define MMS_FS_STATUS_WAIT 0x03
#define MMS_FS_STATUS_FINISH 0x04
#define MMS_FS_STATUS_FAILED 0x05
#define MMS_FS_STATUS_CANCLE 0x06
#define MMS_FS_STATUS_CANCLED 0x07
#define MMS_FS_STATUS_DELETE 0x08
#define MMS_FS_STATUS_DELETED 0x09
#define MMS_FS_STATUS_RETRY 0x0a

#define MMS_FS_MAX_ITEM 200
#define MMS_FS_MAX_MMS_NUM 100
#define MMS_FS_MAX_PUSH_NUM (MMS_FS_MAX_ITEM - MMS_FS_MAX_MMS_NUM)
#define MMS_FS_MAX_PATH_LEN 128
#define MMS_FS_MAX_FILEPATH_LEN 128
#define MMS_FS_MAX_TRANS_ID_LEN 30
#define MMS_FS_MAX_SUBJECT_LEN (31*3+4) //+4 include the UTF8-flag and '\0' /*the subject field*/
#define MMS_FS_MMSC_MAX_LEN 66
#define MMS_FS_GATEWAY_MAX_LEN 34
#define MMS_FS_PORT_MAX_NUM 4
#define MMS_FS_PROXY_LEN 40
#define MMS_FS_APN_MAX_NUM 30
#define MMS_FS_USERNAME_MAX_LEN 30
#define MMS_FS_PASSWORD_MAX_LEN 30
#define MMS_FS_MAX_NAME_COUNT 10
#define MMS_FS_ONE_NAME_LEN 41  // modified......
#define MMS_FS_MAX_NAME_LEN (MMS_FS_MAX_NAME_COUNT * MMS_FS_ONE_NAME_LEN)
#define MMS_FS_MAX_IMSI_LEN 10
#define MMS_FS_MAX_NUMBER_LEN 40

#define MMS_FS_DEVICE_USER 0x01
#define MMS_FS_DEVICE_SDCARD 0x02

#define MMS_FS_1_HOUR 3600
#define MMS_FS_6_HOUR 6*MMS_FS_1_HOUR
#define MMS_FS_12_HOUR 12*MMS_FS_1_HOUR
#define MMS_FS_24_HOUR 24*MMS_FS_1_HOUR
#define MMS_FS_72_HOUR 72*MMS_FS_1_HOUR
#define MMS_FS_1_WEEK 7*MMS_FS_24_HOUR
#define MMS_FS_LONGEST 0

/** Priority-value:LOW */
#define MMS_FS_PRIORITY_LOW                                     0x80
/** Priority-value:NORMAL*/
#define MMS_FS_PRIORITY_NORMAL                                  0x81
/** Priority-value:HIGH */
#define MMS_FS_PRIORITY_HIGN                                    0x82

#define MMS_FS_PROTOCOL_WAP 0x00
#define MMS_FS_PROTOCOL_HTTP 0x01

#define MMS_FS_RETRY_TIME 3 // the times to retry the transmission request except send request

typedef struct T_mmsFs_Handle *MMS_Fs_Handle;

/*mail box list*/
typedef enum
{
    MMS_FS_INBOX = 0,
    MMS_FS_SENTBOX,
    MMS_FS_OUTBOX,
    MMS_FS_DRAFTBOX,
    MMS_FS_OTHERBOX,
    MMS_FS_PUSHBOX,
    MMS_FS_MAILBOX_MAX
}MMS_FS_MAILBOX;

/*system time struct*/
typedef struct
{
    uint16_t year;
    uint16_t month;
    uint16_t day;
    uint16_t hour;
    uint16_t min;
    uint16_t sec;
}T_MmsFs_sysTime;

typedef struct
{
    int32_t deferDownload;                 /*if defer download or auto download*/
    int32_t deliveryReport;                 /*if need delivery report*/
    int32_t readReport;                       /*if need read report*/
    int32_t senderVisibility;                 /*if the sender is visibility*/
    int32_t mmsExpiry;                        /*the expire time of a mms notification*/
    int32_t mmsPriority;                      /*the priority of a new mms*/
    int32_t playSound;                         /*if play sound when preview and play mms*/
    int32_t receiveAD;                         /*if accept reveive advertisement*/
    int32_t autoSign;                            /*the auto signature is on or off*/
    int32_t imageStoreDev;                 /*the image store device usb root or sd card*/
    int32_t audioStoreDev;                 /*the audio store device usb root or sd card*/
    int32_t videoStoreDev;                 /*the video store device usb root or sd card*/
    int32_t protocol_mask;                  /**< used to select the suitable stack which is wap or http*/
    int8_t mmsc_addr[MMS_FS_MMSC_MAX_LEN];    /**< used to save the address of mms center*/
    int8_t gateway[MMS_FS_GATEWAY_MAX_LEN];        /**< used to save the address of gateway*/
    int32_t gateway_port;                   /**< used to save the port number of gateway*/
    int8_t proxy[MMS_FS_PROXY_LEN];            /**< used to save the address of HTTP proxy when using http stack*/
    int32_t proxy_port;                     /**< used to save the port number of gateway when using http stack*/
    int32_t up_limit;                       /**< used to save the max transport bitrate*/
    int32_t low_limit;                      /**< used to save the min transport bitrate*/
    int8_t APN[MMS_FS_APN_MAX_NUM];        /**< string buf used for saving APN name*/
    int8_t user[MMS_FS_USERNAME_MAX_LEN];       /**< string buf used for saving APN user name*/
    int8_t passwd[MMS_FS_PASSWORD_MAX_LEN];   /**< string buf used for saving APN user passward*/
}T_MmsFs_Config;

/*box temporary info*/
typedef struct
{
    uint8_t status;   /*the temp item's status, see mms status type*/
    uint8_t type;      /*the temp item's type, see mms message type*/
#ifdef MMS_DUAL_SIM_SUPPORT
    uint8_t imsi[MMS_FS_MAX_IMSI_LEN];
#endif
    uint32_t time;      /*last modified time*/
    int32_t itemLen;  /*the temp item's body buffer length*/
}T_MmsFs_tempInfo;

/*mms pdu head info*/
typedef struct
{
    int32_t deliveryReport;   /*if need delivery report*/
    int32_t readReply;           /*if need read report*/
    int32_t senderVisibility;  /*if the sender is visibility*/
    int8_t *transactionId; /*the transaction id*/
    int8_t *from;  /*the from field*/
    int8_t *to;      /*the to field*/
    int8_t *cc;      /*the cc field*/
    int8_t *bcc;    /*the bcc field*/
    int8_t *subject;
    int32_t mmsExpiry;   /*the expire time*/
    int32_t mmsDelieveryTime;  /*the delivery time*/
    int32_t mmsPriority;             /*the priority*/
    int32_t mmsMessageClass;   /*the message class*/
    int32_t contentSize;              /*the content size*/
    int32_t date;                          /*the parsed date*/
    int32_t status;                       /*the status of mms report*/
}T_MmsFs_headInfo;

/*message information*/
typedef struct
{
    uint8_t status;  /*the item's status, see mms status type*/
    uint8_t type;     /*the item's type, see mms message type*/
    uint8_t flag;      /*flag*/
    uint8_t extension;  /*extension*/
    uint32_t time;           /*last modified time*/
    int32_t itemLen;       /*the item's body buffer length*/
#ifdef MMS_DUAL_SIM_SUPPORT
    uint8_t imsi[MMS_FS_MAX_IMSI_LEN];
#endif
 }T_MmsFs_itemInfo;

#define NCCMms_fs_makeUniqueID(time, index) time+index //make the transmission unique id by item index
#define NCCMms_fs_analyseUniqueID(id, time) id-time//analyse the transmission unique id to item index

extern int32_t NCCPort_file_regVolume(int32_t appId, uint16_t * volumeStr);

/**
 * Init file system and mms mail box
 * \param    sysPath    the root path of mail box
 * \param    mmsConfig    the mms config, if it's NULL, it will load the config from file system
 * \return    <ul>
 *                <li>when successful,return#MMS_FS_OK
 *                <li>when fail,return
 *                    <ul>
 *                        <li>a negative to explain the error reason
 *                    </ul>
 *            </ul>
 */
int32_t NCCMms_fs_initMailBox(int8_t *sysPath, T_MmsFs_Config *mmsConfig);

/**
 * Set the config to default config. It will not save the config to file system
 * \param    defaultConfig    The structure buffer to save the default config
 * \return    None
 */
void NCCMms_fs_setDefaultConfig(T_MmsFs_Config *defaultConfig);

/**
 * Get the config from file system
 * \param    mmsConfig    The structure buffer to save the config
 * \return    <ul>
 *                <li>when successful,return#MMS_FS_OK
 *                <li>when fail,return
 *                    <ul>
 *                        <li>a negative to explain the error reason
 *                    </ul>
 *            </ul>
 */
int32_t NCCMms_fs_getConfig(T_MmsFs_Config *mmsConfig);

/**
 * Save the config to file system
 * \param    mmsConfig    The structure of config
 * \return    <ul>
 *                <li>when successful,return#MMS_FS_OK
 *                <li>when fail,return
 *                    <ul>
 *                        <li>a negative to explain the error reason
 *                    </ul>
 *            </ul>
 */
int32_t NCCMms_fs_saveConfig(T_MmsFs_Config *mmsConfig);

/**
 * Open the mail box
 * \param    mmsFsHandle    The handle to record the opened mail box
 * \param    mailBox    To explain which mail box will be opened
 * \return    <ul>
 *                <li>when successful,return#MMS_FS_OK
 *                <li>when fail,return
 *                    <ul>
 *                        <li>a negative to explain the error reason
 *                    </ul>
 *            </ul>
 */
int32_t NCCMms_fs_openMailBox(MMS_Fs_Handle *mmsFsHandle, MMS_FS_MAILBOX mailBox);

/**
 * Close the mail box which has beed opened
 * \param    mmsFsHandle    The handle to record the opened mail box
 * \return    <ul>
 *                <li>when successful,return#MMS_FS_OK
 *                <li>when fail,return
 *                    <ul>
 *                        <li>a negative to explain the error reason
 *                    </ul>
 *            </ul>
 */
int32_t NCCMms_fs_closeMailBox(MMS_Fs_Handle *mmsFsHandle);

/**
 * Get the current opened mail box through the handle
 * \param    mmsFsHandle    The handle to record the opened mail box
 * \return    <ul>
 *                <li>when successful,return#MMS_FS_MAILBOX
 *                <li>when fail,return
 *                    <ul>
 *                        <li>#MMS_FS_MAILBOX_MAX
 *                    </ul>
 *            </ul>
 */
MMS_FS_MAILBOX NCCMms_fs_curMailBox(MMS_Fs_Handle mmsFsHandle);

/**
 * Save a mms item to mail box by the certain index
 * \param    mmsFsHandle    The handle to record the opened mail box, which the item will be saved to
 * \param    itemIndex    The certain index
 * \param    itemInfo      The information of item, like type, status, etc.
 * \param    bodyBuf      The body of item
 * \param    headInfo      The information of header
 * \return    <ul>
 *                <li>when successful,return saved index, it must be itemIndex
 *                <li>when fail,return
 *                    <ul>
 *                        <li>a negative to explain the error reason
 *                    </ul>
 *            </ul>
 */
int32_t NCCMms_fs_saveItemToIndex(MMS_Fs_Handle mmsFsHandle, 
                                    int32_t itemIndex, 
                                    T_MmsFs_itemInfo *itemInfo, 
                                    uint8_t * bodyBuf, 
                                    T_MmsFs_headInfo *headInfo);

int32_t NCCMms_fs_moveItemCus(MMS_Fs_Handle SoHandle,
                              MMS_Fs_Handle DeHandle,
                              int32_t itemIndex,
                              T_MmsFs_itemInfo *itemInfo);

int32_t NCCMms_fs_renameItemToIndex(MMS_Fs_Handle orgMmsFsHandle,
                                    MMS_Fs_Handle desMmsFsHandle,
                                    int32_t orgItemIndex,
                                    int32_t desItemIndex,
                                    T_MmsFs_itemInfo *itemInfo,
                                    T_MmsFs_headInfo *headInfo);

/**
 * Save a mms item to mail box
 * \param    mmsFsHandle    The handle to record the opened mail box, which the item will be saved to
 * \param    itemInfo      The information of item, like type, status, etc.
 * \param    bodyBuf      The body of item
 * \param    headInfo      The information of header
 * \return    <ul>
 *                <li>when successful,return the index of item in the mail box 
 *                <li>when fail,return
 *                    <ul>
 *                        <li>a negative to explain the error reason
 *                    </ul>
 *            </ul>
 */
int32_t NCCMms_fs_saveItem(MMS_Fs_Handle mmsFsHandle, 
                             T_MmsFs_itemInfo *itemInfo, 
                             uint8_t * bodyBuf, 
                             T_MmsFs_headInfo *headInfo);

/**
 * Rename a mms item to mail box
 * \param    mmsFsHandle    The handle to record the opened mail box, which the item will be saved to
 * \param    itemInfo      The information of item, like type, status, etc.
 * \param    bodyBuf      The body of item
 * \param    headInfo      The information of header
 * \return    <ul>
 *                <li>when successful,return the index of item in the mail box 
 *                <li>when fail,return
 *                    <ul>
 *                        <li>a negative to explain the error reason
 *                    </ul>
 *            </ul>
 */
int32_t NCCMms_fs_renameItem(MMS_Fs_Handle SoHandle,
                            MMS_Fs_Handle DeHandle,
                            int32_t itemIndex,
                            T_MmsFs_itemInfo *itemInfo);

                            
int32_t NCCMms_fs_renameRealItem(MMS_Fs_Handle orgMmsFsHandle,
								 MMS_Fs_Handle desMmsFsHandle,
                            	 T_MmsFs_itemInfo *itemInfo,
    	                         T_MmsFs_headInfo *headInfo, 
    	                         int32_t orgItemIndex);

int32_t NCCMms_fs_getNeedDeleteBox(void);

/**
 * Get the index of the first mms item in the mail box
 * \param    mmsFsHandle    The handle to record the opened mail box
 * \return    <ul>
 *                <li>when successful,return the index of the first  mms item
 *                <li>when fail,return
 *                    <ul>
 *                        <li>#MMS_FS_FAILED
 *                    </ul>
 *            </ul>
 */
int32_t NCCMms_fs_getFirstItemIndex(MMS_Fs_Handle mmsFsHandle);

/**
 * Get the next index of mms item in the mail box
 * \param    mmsFsHandle    The handle to record the opened mail box
 * \param    preIndex    The previous index of mms item 
 * \return    <ul>
 *                <li>when successful,return the index of the next  mms item
 *                <li>when fail,return
 *                    <ul>
 *                        <li>#MMS_FS_FAILED
 *                    </ul>
 *            </ul>
 */
int32_t NCCMms_fs_getNextItemIndex(MMS_Fs_Handle mmsFsHandle, int32_t preIndex);

/**
 * Get the head buffer of mms item by a certain index
 * \param    mmsFsHandle    The handle to record the opened mail box, which the mms item is in
 * \param    itemIndex      The certain index of the mms item
 * \param    headInfo         The point of header structure 
 * \return    <ul>
 *                <li>when successful,return#MMS_FS_OK
 *                <li>when fail,return
 *                    <ul>
 *                        <li>a negative to explain the error reason
 *                    </ul>
 *            </ul>
 */
int32_t NCCMms_fs_getItemHeader(MMS_Fs_Handle mmsFsHandle,
                               int32_t itemIndex,
                               T_MmsFs_headInfo *headInfo);

/**
 * make the head buffer, which buffer should be free by
 * NCCMms_fs_freeHeader() or NCCMms_fs_makeHeadBuffer
 * \param    len    The length of the buffer
 * \return    <ul>
 *                <li>when successful,return a pointer to the buffer
 *                <li>when fail,return
 *                    <ul>
 *                        <li>NULL
 *                    </ul>
 *            </ul>
 */
void *NCCMms_fs_makeHeadBuffer(int32_t len);

/**
 * free the head buffer, which buffer should be made by NCCMms_fs_makeHeadBuffer()
 * \param    buf    The buffer to be free
 * \return    <ul>
 *                <li>when successful,return a pointer to the buffer
 *                <li>when fail,return
 *                    <ul>
 *                        <li>NULL
 *                    </ul>
 *            </ul>
 */
void NCCMms_fs_freeHeadBuffer(void *buf);

/**
 * free the head buffer
 * \param    T_MmsFs_headInfo    The point of head buffer
 * \return    <ul>
 *                <li>when successful,return#MMS_FS_OK
 *                <li>when fail,return
 *                    <ul>
 *                        <li>a negative to explain the error reason
 *                    </ul>
 *            </ul>
 */
int32_t NCCMms_fs_freeHeader(T_MmsFs_headInfo *mmsHeadInfo);

/**
 * Get the body buffer of mms item by a certain index
 * \param    mmsFsHandle    The handle to record the opened mail box, which the mms item is in
 * \param    itemIndex      The certain index of the mms item
 * \param    buffer         The point of body buffer 
 * \param    bufferLen      The length of the body buffer 
 * \return    <ul>
 *                <li>when successful,return#MMS_FS_OK
 *                <li>when fail,return
 *                    <ul>
 *                        <li>a negative to explain the error reason
 *                    </ul>
 *            </ul>
 */
int32_t NCCMms_fs_getItemBody(MMS_Fs_Handle mmsFsHandle,
                               int32_t itemIndex,
                               uint8_t *buffer,
                               int32_t bufferLen);

/**
 * Get the file path name of the mms item body
 * \param    mmsFsHandle    The handle to record the opened mail box, which the mms item is in
 * \param    itemIndex      The certain index of the mms item
 * \return    <ul>
 *                <li>when successful,return the body file path name
 *                <li>when fail,return
 *                    <ul>
 *                        <li>NULL
 *                    </ul>
 *            </ul>
 */
int8_t * NCCMms_fs_getBodyPath(MMS_Fs_Handle mmsFsHandle, int32_t itemIndex);

/**
 * Get the file path name of the mms item head
 * \param    mmsFsHandle    The handle to record the opened mail box, which the mms item is in
 * \param    itemIndex      The certain index of the mms item
 * \return    <ul>
 *                <li>when successful,return the head file path name
 *                <li>when fail,return
 *                    <ul>
 *                        <li>NULL
 *                    </ul>
 *            </ul>
 */
int8_t * NCCMms_fs_getHeadPath(MMS_Fs_Handle mmsFsHandle, int32_t itemIndex);

/**
 * Delete the mms item by a certain index 
 * \param    mmsFsHandle    The handle to record the opened mail box, which the mms item is in
 * \param    itemIndex      The certain index of the mms item
 * \return    <ul>
 *                <li>when successful,return#MMS_FS_OK
 *                <li>when fail,return
 *                    <ul>
 *                        <li>a negative to explain the error reason
 *                    </ul>
 *            </ul>
 */
int32_t NCCMms_fs_deleteItem(MMS_Fs_Handle mmsFsHandle, int32_t itemIndex);

/**
 * Delete all mms item in the mail box
 * \param    mmsFsHandle    The handle to record the opened mail box, which the mms item is in
 * \return    <ul>
 *                <li>when successful,return#MMS_FS_OK
 *                <li>when fail,return
 *                    <ul>
 *                        <li>a negative to explain the error reason
 *                    </ul>
 *            </ul>
 */
int32_t NCCMms_fs_deleteAllItem(MMS_Fs_Handle mmsFsHandle);

/**
 * Move a mms item from SoHandle to DeHandle by a certain index
 * \param    SoHandle    The handle of mailbox stored the certain item
 * \param    DeHandle    The handle of mailbox moved to
 * \param     itemIndex   The certain index of the mms item
 * \param     itemInfo      The new information of the mms item stored in DeHandle
 * \return    <ul>
 *                <li>when successful,return#the certain index in DeHandle
 *                <li>when fail,return
 *                    <ul>
 *                        <li>a negative to explain the error reason
 *                    </ul>
 *            </ul>
 */
int32_t NCCMms_fs_moveItem(MMS_Fs_Handle SoHandle,
                            MMS_Fs_Handle DeHandle,
                            int32_t itemIndex,
                            T_MmsFs_itemInfo *itemInfo);

/**
 * Copy a mms item from SoHandle to DeHandle by a certain index
 * \param    SoHandle    The handle of mailbox stored the certain item
 * \param    DeHandle    The handle of mailbox copyed to
 * \param     itemIndex   The certain index of the mms item
 * \param     itemInfo      The new information of the mms item stored in DeHandle
 * \return    <ul>
 *                <li>when successful,return#the certain index in DeHandle
 *                <li>when fail,return
 *                    <ul>
 *                        <li>a negative to explain the error reason
 *                    </ul>
 *            </ul>
 */
int32_t NCCMms_fs_copyItem(MMS_Fs_Handle SoHandle,
                            MMS_Fs_Handle DeHandle,
                            int32_t itemIndex,
                            T_MmsFs_itemInfo *itemInfo);

/**
 * Get the information of mms item by a certain index
 * \param    mmsFsHandle    The handle to record the opened mail box, which the mms item is in
 * \param     itemIndex   The certain index of the mms item
 * \param     itemInfo      The buffer store the item information
 * \return    <ul>
 *                <li>when successful,return#MMS_FS_OK
 *                <li>when fail,return
 *                    <ul>
 *                        <li>a negative to explain the error reason
 *                    </ul>
 *            </ul>
 */
int32_t NCCMms_fs_getItemInfo(MMS_Fs_Handle mmsFsHandle, 
                                int32_t itemIndex, 
                                T_MmsFs_itemInfo *itemInfo);

/**
 * Get the lowest priority message (mms item) in a certain mailbox
 * \param    mmsFsHandle    The handle to record the opened mail box, which the mms item is in
 * \return    <ul>
 *                <li>when successful,return#the certain index of the lowest priority message
 *                <li>when fail,return
 *                    <ul>
 *                        <li>a negative to explain the error reason
 *                    </ul>
 *            </ul>
 */
int32_t NCCMms_fs_getLowestPriorityMsg(MMS_Fs_Handle mmsFsHandle);

/**
 * Save the information of mms item by a certain index
 * \param    mmsFsHandle    The handle to record the opened mail box, which the mms item is in
 * \param     itemIndex   The certain index of the mms item
 * \param     itemInfo      The buffer store the item information
 * \return    <ul>
 *                <li>when successful,return#MMS_FS_OK
 *                <li>when fail,return
 *                    <ul>
 *                        <li>a negative to explain the error reason
 *                    </ul>
 *            </ul>
 */
int32_t NCCMms_fs_saveItemInfo(MMS_Fs_Handle mmsFsHandle,
                               int32_t itemIndex,
                               T_MmsFs_itemInfo *itemInfo);

/**
 * Get unread message number of a certain mailbox, just for MMS_FS_INBOX
 * \param    mmsFsHandle    The handle to record the opened mail box, which the mms item is in
 * \return    <ul>
 *                <li>when successful,return#The unread message number
 *                <li>when fail,return
 *                    <ul>
 *                        <li>a negative to explain the error reason
 *                    </ul>
 *            </ul>
 */
int32_t NCCMms_fs_getUnreadMsgNum(MMS_Fs_Handle mmsFsHandle);

/**
 * Get the item number in a certainn mailbox
 * \param    mmsFsHandle    The handle to record the opened mail box, which the mms item is in
 * \return    <ul>
 *                <li>when successful,return#The total item number
 *                <li>when fail,return
 *                    <ul>
 *                        <li>a negative to explain the error reason
 *                    </ul>
 *            </ul>
 */
int32_t NCCMms_fs_getBoxItemNum(MMS_Fs_Handle mmsFsHandle);

/**
 * Get the push message number in the certain mailbox, just for MMS_FS_INBOX
 * \param    mmsFsHandle    The handle to record the opened mail box, which the mms item is in
 * \return    <ul>
 *                <li>when successful,return#The push message number
 *                <li>when fail,return
 *                    <ul>
 *                        <li>a negative to explain the error reason
 *                    </ul>
 *            </ul>
 */
int32_t NCCMms_fs_getBoxPushNum(MMS_Fs_Handle mmsFsHandle);

/**
 * Get the box size of a certain mailbox
 * \param    mmsFsHandle    The handle to record the opened mail box, which the mms item is in
 * \return    <ul>
 *                <li>when successful,return#box total size
 *                <li>when fail,return
 *                    <ul>
 *                        <li>a negative to explain the error reason
 *                    </ul>
 *            </ul>
 */
int32_t NCCMms_fs_getBoxTotalSize(MMS_Fs_Handle mmsFsHandle);

/**
 * Save a temp item to a mailbox by a certain index, the temp item is tobe checked for a mms item
 * \param    mmsFsHandle    The handle to record the opened mail box, which the temp item is in
 * \param     index                The certain index
 * \param     tempInfo           The information of the temp item
 * \param     buffer                The body buffer of the temp item
 * \return    <ul>
 *                <li>when successful,return#the saved index
 *                <li>when fail,return
 *                    <ul>
 *                        <li>a negative to explain the error reason
 *                    </ul>
 *            </ul>
 */
int32_t NCCMms_fs_saveTempItemToIndex(MMS_Fs_Handle mmsFsHandle,
                                      int32_t index,
                                      T_MmsFs_tempInfo *tempInfo,
                                      uint8_t *buffer);

/**
 * Save a temp item to mailbox
 * \param    mmsFsHandle    The handle to record the opened mail box, which the temp item is in
 * \param     tempInfo           The information of the temp item
 * \param     buffer                The body buffer of the temp item
 * \return    <ul>
 *                <li>when successful,return#the saved index
 *                <li>when fail,return
 *                    <ul>
 *                        <li>a negative to explain the error reason
 *                    </ul>
 *            </ul>
 */
int32_t NCCMms_fs_saveTempItem(MMS_Fs_Handle mmsFsHandle,
                                 T_MmsFs_tempInfo *tempInfo, 
                                 uint8_t *buffer);

/**
 * Get the first available temp item's index
 * \param    mmsFsHandle    The handle to record the opened mail box, which the temp item is in
 * \return    <ul>
 *                <li>when successful,return#the temp item's index
 *                <li>when fail,return
 *                    <ul>
 *                        <li>a negative to explain the error reason
 *                    </ul>
 *            </ul>
 */
int32_t NCCMms_fs_getAvailableTempItemIndex(MMS_Fs_Handle mmsFsHandle);

/**
 * Get the next available temp item's index through the previous index
 * \param    mmsFsHandle    The handle to record the opened mail box, which the temp item is in
 * \param    preIndex           The previous index
 * \return    <ul>
 *                <li>when successful,return#the temp item's index
 *                <li>when fail,return
 *                    <ul>
 *                        <li>a negative to explain the error reason
 *                    </ul>
 *            </ul>
 */
int32_t NCCMms_fs_getNextAvailableTempItemIndex(MMS_Fs_Handle mmsFsHandle, int32_t preIndex);

/**
 * Get the temp item's body buffer by a certain index
 * \param    mmsFsHandle    The handle to record the opened mail box, which the temp item is in
 * \param    index                The certain index
 * \param    buffer               The buffer store the item's body
 * \param    bufferLen          The buffer's length
 * \param    
 * \return    <ul>
 *                <li>when successful,return#MMS_FS_OK
 *                <li>when fail,return
 *                    <ul>
 *                        <li>a negative to explain the error reason
 *                    </ul>
 *            </ul>
 */
int32_t NCCMms_fs_getTempItem(MMS_Fs_Handle mmsFsHandle,
                               int32_t index,
                               uint8_t *buffer,
                               int32_t bufferLen);

/**
 * Get the path of temp item's body by a certain index
 * \param    mmsFsHandle    The handle to record the opened mail box, which the temp item is in
 * \param    itemIndex         The certain index
 * \return    <ul>
 *                <li>when successful,return#the path string
 *                <li>when fail,return
 *                    <ul>
 *                        <li>NULL
 *                    </ul>
 *            </ul>
 */
int8_t * NCCMms_fs_getTempItemPath(MMS_Fs_Handle mmsFsHandle, int32_t itemIndex);

/**
 * Delete a temp item in the mail box, just delete the body file, not modify the information
 * \param    mmsFsHandle    The handle to record the opened mail box, which the temp item is in
 * \return    <ul>
 *                <li>when successful,return#MMS_FS_OK
 *                <li>when fail,return
 *                    <ul>
 *                        <li>a negative to explain the error reason
 *                    </ul>
 *            </ul>
 */
int32_t NCCMms_fs_deleteTempItem(MMS_Fs_Handle mmsFsHandle, int32_t index);

/**
 * Delete all temp item in the mail box
 * \param    mmsFsHandle    The handle to record the opened mail box, which the temp item is in
 * \return    <ul>
 *                <li>when successful,return#MMS_FS_OK
 *                <li>when fail,return
 *                    <ul>
 *                        <li>a negative to explain the error reason
 *                    </ul>
 *            </ul>
 */
int32_t NCCMms_fs_deleteAllTempItem(MMS_Fs_Handle mmsFsHandle);

/**
 * Get the temp item's information by a certain index
 * \param    mmsFsHandle    The handle to record the opened mail box, which the temp item is in
 * \param    index                The certain index
 * \param    tempInfo           The buffer of the information
 * \return    <ul>
 *                <li>when successful,return#MMS_FS_OK
 *                <li>when fail,return
 *                    <ul>
 *                        <li>a negative to explain the error reason
 *                    </ul>
 *            </ul>
 */
int32_t NCCMms_fs_getTempInfo(MMS_Fs_Handle mmsFsHandle,
                               int32_t index,
                               T_MmsFs_tempInfo *tempInfo);

/**
 * Save the temp item's information by a certain index
 * \param    mmsFsHandle    The handle to record the opened mail box, which the temp item is in
 * \param    index                The certain index
 * \param    tempInfo           The buffer of the information
 * \param    mmsFsHandle    The handle to record the opened mail box, which the mms item is in
 * \return    <ul>
 *                <li>when successful,return#MMS_FS_OK
 *                <li>when fail,return
 *                    <ul>
 *                        <li>a negative to explain the error reason
 *                    </ul>
 *            </ul>
 */
int32_t NCCMms_fs_saveTempInfo(MMS_Fs_Handle mmsFsHandle,
                                  int32_t index,
                                  T_MmsFs_tempInfo *tempInfo);

/**
 * Check the temp items in a mailbox, get the temp item's total number or total size
 * \param    mmsFsHandle    The handle to record the opened mail box, which the temp item is in
 * \param    totalNum           The buffer saved the number, if NULL, indicate not get the number
 * \param    totalSize            The buffer saved the size, if NULL, indicate not get the size
 * \return    <ul>
 *                <li>when successful,return#MMS_FS_OK
 *                <li>when fail,return
 *                    <ul>
 *                        <li>a negative to explain the error reason
 *                    </ul>
 *            </ul>
 */
int32_t NCCMms_fs_CheckTemporary(MMS_Fs_Handle mmsFsHandle,
                                    int32_t *totalNum,
                                    int32_t *totalSize);

/**
 * Sort the indexs in a mailbox, sort by the unread flag and create time
 * \param    mmsFsHandle    The handle to record the opened mail box
 * \param    sortIndex          The buffer saved the sorted index
 * \return    <ul>
 *                <li>when successful,return#MMS_FS_OK
 *                <li>when fail,return
 *                    <ul>
 *                        <li>a negative to explain the error reason
 *                    </ul>
 *            </ul>
 */
int32_t NCCMms_fs_sortIndex(MMS_Fs_Handle mmsFsHandle, int32_t *sortIndex);

/**
 * Convert seconds to date time
 * \param    time           The total seconds from 'date' to the convert time
 * \param    date           <in>
                                       The date time of second from
                                    <out>
                                       The date time converted to
 * \return    <ul>
 *                <li>None
 *            </ul>
 */
void NCCMms_fs_sec2date(uint32_t time, T_MmsFs_sysTime *date);

/**
 * Convert date time to seconds
 * \param    sec           The buffer of the converted second
 * \param    date          The date tobe convert
 * \param    fromDate   Convert from which date time
 * \return    <ul>
 *                <li>None
 *            </ul>
 */
void NCCMms_fs_date2sec(uint32_t *sec, T_MmsFs_sysTime *date, T_MmsFs_sysTime *fromDate);

/**
 * Get the send pdu buffer and length by mms body and mms header
 * \param    msgBody    Mms body buffer
 * \param    msgLen      Mms body length
 * \param    headInfo    Mms header information
 * \param    pduLen       send pdu buffer length
 * \return    <ul>
 *                <li>when successful,return the pointer of send message buffer
 *                <li>when fail,return
 *                    <ul>
 *                        <li>NULL
 *                    </ul>
 *            </ul>
 */
uint8_t *NCCMms_fs_GetSendPdu(uint8_t *msgBody,
                                               int32_t msgLen,
                                               T_MmsFs_headInfo *headInfo,
                                               int32_t *pduLen);

/**
 * Check the inbox by a certain index, or check all item. This will parse the temp item to mms item
 * \param    mmsFsHandle    The handle to record the opened mail box, just for MMS_FS_INBOX
 * \param    index                The certain index, if (-1 == index), it means check all item in inbox
 * \return    <ul>
 *                <li>when successful,return#if a certain index, return the new item index, or MMS_FS_OK
 *                <li>when fail,return
 *                    <ul>
 *                        <li>a negative to explain the error reason
 *                    </ul>
 *            </ul>
 */
int32_t NCCMms_fs_checkInBox(MMS_Fs_Handle mmsFsHandle, int32_t index);

/**
 * User agent (MMI) check the outbox by a certain index, or check all item. This will check if the 
 * network operation of the item is failed or success or other response.
 * \param    mmsFsHandle    The handle to record the opened mail box, just for MMS_FS_OUTBOX
 * \param    index                The certain index, if (-1 == index), it means check all item in outbox
 * \return    <ul>
 *                <li>when successful,return#MMS_FS_OK
 *                <li>when fail,return
 *                    <ul>
 *                        <li>a negative to explain the error reason
 *                    </ul>
 *            </ul>
 */
int32_t NCCMms_fs_uaCheckOutBox(MMS_Fs_Handle mmsFsHandle, int32_t index);

/**
 * Save new message to mailbox
 * \param    mmsFsHandle    The handle to record the opened mail box, which the new message will store
 * \param    type                 The message type
 * \param    pduBuffer          The message's buffer
 * \param    pduLen              The message's length
 * \param    directly              Save it directly or save as temp item, then need to check the mailbox, just for MMS_FS_INBOX
 * \return    <ul>
 *                <li>when successful,return#the temp item index, or the item index if (TRUE == directly)
 *                <li>when fail,return
 *                    <ul>
 *                        <li>a negative to explain the error reason
 *                    </ul>
 *            </ul>
 */
int32_t NCCMms_fs_saveNewMsg(MMS_Fs_Handle mmsFsHandle,
                              uint8_t type,
                              uint8_t *pduBuffer,
                              int32_t pduLen,
#ifdef MMS_DUAL_SIM_SUPPORT
                              uint8_t *imsi,
#endif
                              int32_t directly);

/**
 * Analyze the push message 's type
 * \param    push_buf    the push message's buffer
 * \param    push_len    the push message's buffer length
 * \param    push_type  the push message's type
 * \return    <ul>
 *                <li>when successful,return#MMS_FS_OK
 *                <li>when fail,return
 *                    <ul>
 *                        <li>a negative to explain the error reason
 *                    </ul>
 *            </ul>
 */
int32_t NCCMms_fs_analyzePush(uint8_t * push_buf, int32_t push_len, int32_t * push_type);

/**
 * Start to re-edit the mms from mail box
 * \param    mailBox    Re-edit from which mail box
 * \param    index             The certain index
 * \param    mmsCpsHandle      The hanlde to record the re-edit mms
 * \return    <ul>
 *                <li>when successful,return#MMS_FS_OK
 *                <li>when fail,return
 *                    <ul>
 *                        <li>a negative to explain the error reason
 *                    </ul>
 *            </ul>
 */
int32_t NCCMms_fs_reEditMms(MMS_FS_MAILBOX mailBox, int32_t index, MMS_Handle mmsCpsHandle);

/**
 * Start to parse the mms from mail box, should call NCCMms_fs_quitParseMms() to free handle
 * \param    mailBox    Parse from which mail box
 * \param    index             The certain index
 * \param    mmsFsParHandle    Filesystem Related handle
 * \param    mmsParseHandle   The hanlde to record the parsed mms
 * \return    <ul>
 *                <li>when successful,return#MMS_FS_OK
 *                <li>when fail,return
 *                    <ul>
 *                        <li>a negative to explain the error reason
 *                    </ul>
 *            </ul>
 */
int32_t NCCMms_fs_parseMms(MMS_FS_MAILBOX mailBox,
                            int32_t index,
                            void **mmsFsParHandle,
                            MMS_Handle *mmsParseHandle);

/**
 * Quit the re-edit from mail box
 * \param    mmsFsParHandle    Filesystem Related handle
 * \param    mmsParseHandle   The hanlde to record the parsed mms
 * \return    <ul>
 *                <li>when successful,return#MMS_FS_OK
 *                <li>when fail,return
 *                    <ul>
 *                        <li>a negative to explain the error reason
 *                    </ul>
 *            </ul>
 */
int32_t NCCMms_fs_freeParseMms(void **mmsFsParHandle, MMS_Handle *mmsParseHandle);

#ifdef MMS_SUPPORT_JSR205
/**
* get the APP ID and Reply APP ID from mail box
* \param    mailBox     Parse from which mail box
* \param    index       The certain index
* \param    appId       application ID, this pointer should be free by CRTL_MMS_Free.
* \param    replyToAppId    Reply application ID, this pointer should be free by CRTL_MMS_Free.
* \param    startContentId  start content ID, this pointer should be free by CRTL_MMS_Free.
* \return    <ul>
*                <li>when successful,return#MMS_FS_OK
*                <li>when fail,return
*                    <ul>
*                        <li>a negative to explain the error reason
*                    </ul>
*            </ul>
*/
int32_t NCCMms_fs_getAppIdAndReplyAppId(MMS_FS_MAILBOX mailBox,
                                        int32_t index,
                                        uint8_t **appId,
                                        uint8_t **replyToAppId,
                                        uint8_t **startContentId);

#endif /* MMS_SUPPORT_JSR205 */

#ifdef __cplusplus
}
#endif

#endif /*__NCC_MMS_FS_H__*/

