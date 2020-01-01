/*The header file to  the file system of MMS*/
/*define the parameters*/

#ifndef __MMS_FS_MANAGER_H__
#define __MMS_FS_MANAGER_H__

#include <ncc_types.h>

#ifdef __cplusplus
extern "C"{
#endif

#define MMS_FS_INBOX_DIR "/mailbox/inbox/"
#define MMS_FS_OUTBOX_DIR "/mailbox/outbox/"
#define MMS_FS_SENTBOX_DIR "/mailbox/sentbox/"
#define MMS_FS_DRAFTBOX_DIR "/mailbox/draftbox/"
#define MMS_FS_OTHERBOX_DIR "/mailbox/otherbox/"
#define MMS_FS_PUSHBOX_DIR "/mailbox/pushbox/"

#define MMS_FS_MM_SUFFIX ".mms"
#define MMS_FS_HEAD_SUFFIX ".head"
#define MMS_FS_TEMP_SUFFIX ".temp"
#define MMS_FS_BAK_SUFFIX ".bak"

#define MMS_FS_INDEX_NAME "index"
#define MMS_FS_CONFIG_NAME "/mms.config"
#define MMS_FS_DEFAULT_SYSTEM_DIR "/My Mms"

#define MMS_FS_DEFAULT_MMS_CERTER "http://mmsc.monternet.com/"
#define MMS_FS_DEFAULT_GATEWAY "10.0.0.172"
#define MMS_FS_DEFAULT_PORTNUMBER 9201
#define MMS_FS_DEFAULT_UP_LIMIT 300000
#define MMS_FS_DEFAULT_LOW_LIMIT 300000
#define MMS_FS_DEFAULT_APN "cmwap"
#define MMS_FS_DEFAULT_USER_NAME ""
#define MMS_FS_DEFAULT_PASSWORD ""

#define MMS_FS_INDEX_CHANGE_FLAG 0x01
#define MMS_FS_TMP_INDEX_CHANGE_FLAG 0x10

#define MMS_FS_EXTRA_BUF_LEN 1024

#ifdef MMS_DUAL_SIM_SUPPORT
#define MMS_FS_IMSI_LEN 9
#endif

#define MMS_FS_ENABLE_INDEX_PROTECT

#ifdef MMS_FS_ENABLE_INDEX_PROTECT
#define MMS_FS_MM_PROTECT_SUFFIX ".mms_temp_"
#define MMS_FS_TEMP_PROTECT_SUFFIX ".temp_temp_"
#endif

static int8_t fs_system_dir[MMS_FS_MAX_PATH_LEN] = MMS_FS_DEFAULT_SYSTEM_DIR;

#define  MMS_FS_MIN( _x, _y ) ( ((_x) < (_y)) ? (_x) : (_y) )

typedef struct
{
    int32_t index;
    uint32_t time;
}T_MmsFs_timeIndex;

typedef struct
{
    int32_t index;
    T_MmsFs_itemInfo itemInfo;
    T_MmsFs_headInfo headInfo;
    int32_t usedExtraSize;
    uint8_t extraBuf[MMS_FS_EXTRA_BUF_LEN];
}T_MmsFs_document;

typedef struct
{
    int32_t actNum;
    int32_t itemNum;
    int32_t pushNum;
    int32_t boxSize;
    T_MmsFs_document *document;
}T_MmsFs_boxIndex;

typedef struct T_mmsFs_Handle
{
    int32_t mailBox;
    int32_t inUseCount;
    T_MmsFs_tempInfo *tempIndex;
    T_MmsFs_boxIndex *boxIndex;
}T_MMSFS_HANDLE;

int32_t mmsfsCreateFile(int8_t *fileName);
void mmsfsSortIndex(T_MmsFs_timeIndex *timeIndex, int32_t totalNum, int32_t *sortIndex);
int32_t mmsfsGetName(int32_t mailBox, int32_t index, int8_t *suffix, int8_t *name);
int32_t mmsfsInitMailBox(int32_t mailBox, int32_t hasBoxIndex, int32_t hasTempIndex);
int32_t mmsfsReplaceIndex(MMS_Fs_Handle mmsFsHandle, int8_t * suffix, int32_t pduType);
int32_t mmsfsGetIndex(MMS_Fs_Handle mmsFsHandle, int8_t * suffix, int32_t pduType);
int32_t mmsfsSaveMailBox(MMS_Fs_Handle mmsFsHandle, int32_t changeFlag);
int32_t mmsfsCopyHeaderInfo(T_MmsFs_headInfo *org, T_MmsFs_headInfo *dst, T_MmsFs_document *document);
int32_t mmsGetItemHeadByBody(uint8_t *itemBody,
                             int32_t itemLen,
                             uint8_t itemType,
                             T_MmsFs_headInfo *headInfo);
int32_t mmsfsMakeReqest(int32_t index, MMS_Fs_Handle mmsFsHandle, void *pInput);
void mmsfsCleanRequest(void *pInput);
int32_t mmsfsCleanTemporaryStatus(int32_t mailBox, int32_t fromIndex, int32_t toIndex);
int32_t mmsfsCheckInBox(MMS_Fs_Handle mmsFsHandle, int32_t index);
int32_t mmsfsUaCheckOutBox(MMS_Fs_Handle mmsFsHandle, int32_t index);
int32_t mmsfsTransCheckOutBox(MMS_Fs_Handle mmsFsHandle, 
                                int32_t index, 
                                int32_t topHandle);
int32_t mmsfsCheckPushBox(MMS_Fs_Handle mmsFsHandle, int32_t index, int32_t topHandle);

#ifdef __cplusplus
}
#endif

#endif /*__MMS_FS_MANAGER_H__*/

