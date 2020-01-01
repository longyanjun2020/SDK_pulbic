#ifndef CCMMB_H
#define CCMMB_H

#include <stdint.h>
#include "avp_streaming.h"
#include "avp_cmmb_api.h"

#define MAX_AV_UNITNUM          (60)
#define MAX_DATA_UNITNUM        (90)
#define MAX_SUBFRAMENUM         (15)
#define MAX_PROGRAM_NUM         (30)
#define MAX_TIMESLOTNUM         (40)
#define MAX_DATAMSGLEN          (15*1024)
#define MAX_EMERGENCYLEN        (4*1024)
#define MAX_ESG_DATA_LEN        (60*1024)
#define MAX_ESG_PAYLOAD_LEN     (10*1024)
#define MAX_EMEGRENCY_DATA_LEN  (1*1024)
#define MAX_CAT_LEN             (128)
#define MAX_EMM_NUM             (8)
#define MAX_ECM_NUM             (8)
#define MAX_ECM_LEN             (300)

#define CMMB_NIT_TABLE          (0x01)
#define CMMB_CMCT_TABLE         (0x02)
#define CMMB_CSCT_TABLE         (0x03)
#define CMMB_SMCT_TABLE         (0x04)
#define CMMB_SSCT_TABLE         (0x05)
#define CMMB_ESG_DESC_TABLE     (0x06)
#define CMMB_ENTILE_DESC_TABLE  (0x07)
#define CMMB_EMERGENCY_TABLE    (0x10)

#define DATATYPE_XPE            (160)
#define DATATYPE_XPEFEC         (161)

#define NAGRA_CA_SYSTIME_ID     (0x1820)

#define SUPPORT_EMERGENCY_BROADCAST 0
#define SUPPORT_DATA_BROADCAST      0
#define SUPPORT_ESG_BACKUP          1
#define SUPPORT_EMERGENCY_BACKUP	0
#define SUPPORT_CAT_BACKUP          1

#define IDR_EXTRA_BYTES             (64)
#define VOL_SIZE                    (40+IDR_EXTRA_BYTES)
#define AOL_SIZE                    (20)
#define MAX_AVPAYLOAD               (30*1024)
#define MAX_SUBPAYLOAD              (4096)

typedef struct MuxFrameHeader_t {
    uint8_t  m_MFID;
    int8_t   m_ESGUpdateNo;
    int8_t   m_NITUpdateNo;
    int8_t   m_CMCTUpdateNo;
    int8_t   m_CSCTUpdateNo;
    int8_t   m_SMCTUpdateNo;
    int8_t   m_SSCTUpdateNo;
    int8_t   m_ESGPreviousNo;
    int8_t   m_NITPreviousNo;
    int8_t   m_CMCTPreviousNo;
    int8_t   m_CSCTPreviousNo;
    int8_t   m_SMCTPreviousNo;
    int8_t   m_SSCTPreviousNo;
    uint8_t  m_subframeNum;
	uint8_t  m_subframe_idx;
    uint32_t m_subframe_len[MAX_SUBFRAMENUM];
} MuxFrameHeader;

typedef struct MuxSubFrameHeader_t {
    uint8_t   m_encryption;
    uint8_t   m_packetMode;
    uint32_t  m_TimeStamp;
    uint32_t  m_VideoLen;
    uint32_t  m_AudioLen;
    uint32_t  m_DataLen;
    uint8_t   m_ECM;
    int8_t    m_videotype;
    int       m_v_bitrate;
    int       m_v_display_x;
    int       m_v_display_y;
    int       m_v_display_pri;
    int       m_v_height;
    int       m_v_width;
    int       m_v_fps;
    int8_t    m_audiotype;
    int       m_a_bitrate;
    int       m_a_sample_rate;
} MuxSubFrameHeader;

typedef struct VideoSectionHeader_t {
    long   m_video_frames;
    long   m_v_idx;
    uint16_t m_vunit_len[MAX_AV_UNITNUM];
    uint16_t m_vunit_pts[MAX_AV_UNITNUM];
    uint16_t m_frameType[MAX_AV_UNITNUM];
    uint32_t m_frameLen;  // to store the length of each whole frame
} VideoSectionHeader;


typedef struct AudioSectionHeader_t {
    long   m_audio_chunks;
    long   m_a_idx;
    uint16_t m_aunit_len[MAX_AV_UNITNUM];
    uint16_t m_aunit_pts[MAX_AV_UNITNUM];
    uint32_t m_consumed_size;
} AudioSectionHeader;

typedef struct DataSectionHeader_t {
    long   m_data_number;
    uint16_t m_dunit_len[MAX_DATA_UNITNUM];
    uint8_t  m_dunit_type[MAX_DATA_UNITNUM];
} DataSectionHeader;

typedef struct CMCT_SMCT_t {
    int8_t   m_timeslot[MAX_TIMESLOTNUM]; // to notify the time slot of selected channel
    int8_t   m_frameNum;
    uint8_t  available;
} CMCT_SMCT;

typedef struct ESGDescriptorTable_t {
    uint8_t dataTypeNum;
    uint8_t dataBlockNum[5];
} ESGDescriptorTable;

typedef struct DataMessage_t {
    uint16_t len;
	// ESG data is divided into 2~3 second data, so we need to keep payload
    uint8_t payload[MAX_ESG_PAYLOAD_LEN];
	uint8_t *esgptr;
	int valid_start;
	uint8_t dataBlockIdx[5];    // must be equal to ESGDescriptorTable.dataBlockNum
    uint8_t prvPartNo;          // for error handling
    uint8_t prvDataBlkID;       // for error handling
	uint8_t available;
} DataMessage;

typedef struct {
    uint8_t data[MAX_ESG_DATA_LEN];
    uint8_t *ptr;
    int8_t  available;
} Esg_t;

typedef struct {
    uint8_t data[MAX_EMEGRENCY_DATA_LEN];
    uint8_t *ptr;
    uint8_t  available;
} Emergency_t;

typedef struct {
    uint8_t data[MAX_CAT_LEN];
    uint8_t *ptr;
    uint8_t  available;
} CAT_t;

typedef struct EmergencyBroadcast_t {
    uint16_t len;
    //uint8_t payload[MAX_EMERGENCYLEN]; // share the buffer with avpayload
    uint16_t broadcastDate;
    uint32_t broadcastTIme;
    uint32_t lastTime;
    uint8_t type;
    uint8_t level;
} EmergencyBroadcast;

typedef struct EntilementManagement_t {
    EMM     cml[MAX_EMM_NUM];
    uint8_t total_number;
} EntilementManagement;


typedef struct EntilementControl_t {
    ECM     ccl[MAX_ECM_NUM];
    uint8_t total_number;
} EntilementControl;


typedef struct Program_t {
    uint8_t  mfID;
    uint8_t  msfID;
    uint16_t serviceID;
    uint8_t  encrypted;
} Program;


typedef struct APPUseCase_t {
    int  m_usermode;
    Program  m_channel1;
    Program  m_channel2;
    int8_t  m_keyframe;
    int8_t  m_channel_browsing;
    int8_t  m_allchannel;
	int8_t  m_init_mode;
} APPUseCase;


typedef struct ProgramID_t {
    Program prog[MAX_PROGRAM_NUM];
    uint8_t total_program;
} ProgramID;

#ifdef USE_NAGRA_CA
typedef struct decryptKey_t {
    int current_tableID;
    int next_tableID;
    int current_KI;
    int KI_changed;
    int table_changed;
    int notInit;
} decryptKey;

typedef struct ECMBackup_t {
    uint8_t ecmBuf[MAX_ECM_LEN];
    int     length;
    int     type;
    int     received;
} ECMBackup;
#endif

typedef struct CCMMB_t {
    int32_t buf_allocated;
    uint8_t *avpayload;
    uint8_t payload[MAX_SUBPAYLOAD];
    uint8_t vol[VOL_SIZE];
    int vol_size;
    uint8_t aol[AOL_SIZE];
    int aol_size;

    MuxFrameHeader      mfh;
    MuxSubFrameHeader   msfh;
    VideoSectionHeader  vsh;
    AudioSectionHeader  ash;
    DataSectionHeader   dsh;
    CMCT_SMCT           cmct_smct;
    ESGDescriptorTable  edt;
    DataMessage         dm;
    APPUseCase          auc;
#if SUPPORT_EMERGENCY_BACKUP
    Emergency_t			emergency;
#endif
#if SUPPORT_ESG_BACKUP
    Esg_t				esg;
#endif
#if SUPPORT_CAT_BACKUP
    CAT_t               cat;
#endif
#if SUPPORT_EMERGENCY_BROADCAST
    EmergencyBroadcast  eb;
#endif

    EntilementManagement emm;
    EntilementControl    ecm;
    ProgramID            progID;
    ProgInfo             curProg;
    ElementaryStream     eStream;

#ifdef USE_NAGRA_CA
    decryptKey          decrypt;
    ECMBackup           ECMBuf;
#endif

    uint8_t     g_resync;
    int         g_validStart; // set when video I frame is found
    int         g_found_first_video;
    int64_t     g_first_vpts;
    int64_t     g_last_vpts;
    int64_t     g_last_apts;
    int64_t     g_base_vpts;
    int64_t     g_base_updated;
    int64_t     g_pts_duration;

    cb_buffer_st cbuffer;

    uint16_t prog_timeslot[3];

    mvc_allocator_st    allocator;
    void               *alloc_ctx;
    void               *mem_ctx;
} CCMMB;

#endif

