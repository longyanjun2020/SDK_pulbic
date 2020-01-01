#if (defined(WIFI_PORT) && WIFI_PORT == 1)
/*===========================================================================
 * Include files
 *===========================================================================*/
#include "Customer_config.h"

#include "ahc_common.h"
#include "ahc_general.h"
#include "ahc_stream.h"
#include "ahc_message.h"
#include "ahc_menu.h"
#include "mmpf_ringbuf.h"
#include "mmps_3gprecd.h"

//#include "ahc_stream.h"
#include "statenetstreamingfunc.h"
#include "keyparser.h"
#if defined(SPEECH_RECOGNIZE_EN) && (SPEECH_RECOGNIZE_EN)
#include "3rd_speech.h"
#include "mmpd_audio.h"
#endif
#include "amn_sysobjs.h"
#include "amnss.h"
#include "netapp.h"
/*===========================================================================
 * Macro define
 *===========================================================================*/

/*===========================================================================
 * Global variables
 *===========================================================================*/


/*===========================================================================
 * Extern variable
 *===========================================================================*/


/*===========================================================================
 * Extern function
 *===========================================================================*/


/*===========================================================================
 * Main body
 *===========================================================================*/

void STATE_NET_STREAMING_WIRELESS_SET_STREAMING_MODE(UINT32 ulEvent, UINT32 ulParam)
{
    AHC_BOOL ahcRet = AHC_TRUE;

    if(AHC_SetStreamingMode(ulParam)){
        nstreaming_op_feedback(NULL,0);
    }
    else{
        nstreaming_op_feedback(NULL,-1);
    }

    //Return video or camera mode.
    if(AHC_STREAM_OFF == AHC_GetStreamingMode()){
        ahcRet = StateDetachSubMode();
        if(ahcRet != AHC_TRUE){ AHC_PRINT_RET_ERROR(0/*gbAhcDbgBrk*/, ahcRet); /*return AHC_FALSE;*/}
    }
}

#define DBG_SC (0) //debug stream control
#if DBG_SC
#define DBGSC(...) printc(__VA_ARGS__)
#else
#define DBGSC(...)
#endif

struct StreamControlLevel
{
#define SCL_KEEP (0) //not change
    UINT32 bitrate;
    UINT16 w,h;
};

#if SC_CHANGE_RES
static struct StreamControlLevel m_sc_tcp_lvl[] = {
    {100000,  SCL_KEEP, SCL_KEEP},
    {500000,  320, 180},
    {1500000, 640, 360},
    {3000000,1280, 720},
};//must from small to big

//must from small to big
static struct StreamControlLevel m_sc_udp_lvl[] = {
    {200000,  SCL_KEEP, SCL_KEEP},
    {1000000, 320, 180},
    {3000000, 640, 360},
    {4000000,1280, 720},
};
#endif

#define SCORE_NUM (3)
struct StreamControl {
#if SC_CHANGE_RES
    struct StreamControlLevel *levels;
#endif
    struct StreamControlLevel conf;
    struct StreamControlLevel cur;
#if SC_CHANGE_RES
    UINT16 nLevels;
    UINT16 levelCur;
#endif
    UINT32 bitrateMin;
    struct {
        INT16  score[SCORE_NUM];
        INT16  Idx;
        //INT16  IdxNext;
        INT32  Sum;
    } stress;
} m_sc
#if SC_CHANGE_RES
= {m_sc_udp_lvl}
#endif
;

struct StreamControlConst {
    struct { INT16 min, max;} score;
        #define SET_SCORE(x) ((x)*SCORE_NUM)
    struct { INT16 m, n; } enlarge;
        #define shf_divisor_8 (3)
        #define shf_divisor_4 (2)
        #define shf_divisor_2 (1)
        #define shf_divisor_1 (0)
    struct { INT16 m, n; } shrink;
} const static m_scp =//Stream Control Parameter
{
    {SET_SCORE(40), SET_SCORE(72)},
    {5, shf_divisor_4}, //while the stream needs to be enlarged, bit rate * 5/4
    {1, shf_divisor_2}  //while the stream needs to be shrunk,   bit rate * 1/2
};

extern int hack_reset_report;
static void ResetStreamControl(short reset_type)
{
    //Since while RTSP SETUP, it's not streaming yet. the reset function does not get
    if (hack_reset_report != 0) {
        reset_type = hack_reset_report;
        hack_reset_report = 0;
    }
    if (reset_type >= OSAL_TXF_RESET) {
        int w, h;
        int i;

        MEMSET0(&m_sc);
        m_sc.conf.bitrate = ncfg_get_h264_bitrate();
        //m_sc.stress.IdxNext = 1;
        if (ncfg_get_h264_res(&w, &h) != 0) {
            printd(BG_RED("Unable to get H.264 resolution %dx%d")"\r\n", m_sc.conf.w, m_sc.conf.h);
            return;
        }
        m_sc.conf.w = (UINT16)w;
        m_sc.conf.h = (UINT16)h;
        m_sc.cur = m_sc.conf;
        //reset the default value to 50 so that it could shrink stream faster in the beginning.
        for (i = 0; i < SCORE_NUM; ++i) {
            m_sc.stress.score[i] = 50;
        }
        m_sc.stress.Sum = 50 * SCORE_NUM;

        DBGSC("Reset to Stream Control\r\n");

#if SC_CHANGE_RES
        //reset levels
        if (reset_type == OSAL_TXF_RESET_TCP) {
            m_sc.levels = m_sc_tcp_lvl;
            m_sc.nLevels = ARRAY_SIZE(m_sc_tcp_lvl);
            DBGSC("Reset as TCP\r\n");
        }
        else {
            m_sc.levels = m_sc_udp_lvl;
            m_sc.nLevels = ARRAY_SIZE(m_sc_udp_lvl);
        }
        m_sc.bitrateMin = m_sc.levels[0].bitrate;
        m_sc.levelCur = m_sc.nLevels - 1;
#else
        m_sc.bitrateMin = 100 * 1000;
#endif
        DBGSC("Reset min to %d\r\n", m_sc.bitrateMin);
    }
}

static void RecordScore(short score)
{
    //remove the earliest score
    m_sc.stress.Sum -= m_sc.stress.score[m_sc.stress.Idx];
    m_sc.stress.Idx = m_sc.stress.Idx;

    //record the latest score
    m_sc.stress.score[m_sc.stress.Idx] = score;
    m_sc.stress.Sum += score;

    DBGSC("Sum:%d (%d~%d)\r\n", m_sc.stress.Sum, m_scp.score.min, m_scp.score.max);

    //m_sc.stress.Idx = m_sc.stress.IdxNext;
    m_sc.stress.Idx++;
    if (m_sc.stress.Idx == SCORE_NUM)
        m_sc.stress.Idx = 0;
}

static void UpdateBitrate(void)
{
    MMP_ERR err;
#if DBG_SC
    printd(BG_RED("Set bitrate to %d")"\r\n", m_sc.cur.bitrate);
#else
    printc("Update bit rate to %d""\r\n", m_sc.cur.bitrate);
#endif
    err = MMPS_3GPRECD_UpdateParameter(VIDENC_STREAM_WIFI_PRM, MMPS_3GPRECD_PARAMETER_BITRATE,
            (void*)m_sc.cur.bitrate);
    if (err != MMP_ERR_NONE) {
        printc("Error on setting streaming bit rate %X\r\n", err);
        return;
    }
}

#if SC_CHANGE_RES
static void UpdateRes(void)
{
    AHC_STREAM_ID ahcSrcStreamId;
    UINT16 res;
    UINT16 cropB, cropR;

    ahcSrcStreamId = (AHC_STREAM_ID)ncam_get_cam_src((unsigned int)AHC_STREAM_H264);
    if (AHC_TRUE == AIHC_Video_MapResToIdx(m_sc.cur.w, m_sc.cur.h, &res, &cropB, &cropR)) {
        if (AHC_TRUE == AHC_ChangeH264StreamRes(res)) {
        #if DBG_SC
            printd(FG_GREEN("Set resolution to %dx%d")"\r\n", m_sc.cur.w, m_sc.cur.h);
        #else
            printd("Set resolution to %dx%d""\r\n", m_sc.cur.w, m_sc.cur.h);
        #endif
            return;
        }
    }
    printd(BG_RED("Fail to set resolution to %dx%d")"\r\n", m_sc.cur.w, m_sc.cur.h);
}
#endif

static void ShinkStream(void)
{
#if SC_CHANGE_RES
    struct StreamControlLevel *lvl;
    UINT16 targetLvl;
#endif
    UINT32 bitrate;

    DBGSC("Shrink\r\n");

    bitrate = m_sc.cur.bitrate;
    m_sc.cur.bitrate *= m_scp.shrink.m;
    m_sc.cur.bitrate >>= m_scp.shrink.n;
    if (m_sc.cur.bitrate < m_sc.bitrateMin) {
        m_sc.cur.bitrate = m_sc.bitrateMin;
    }
    if (bitrate != m_sc.cur.bitrate)
        UpdateBitrate();

#if SC_CHANGE_RES
    DBGSC("from level %d\r\n", m_sc.levelCur);
    targetLvl = m_sc.levelCur - 1;
    if (m_sc.levelCur == 0) {
        targetLvl = 0;
    }
    lvl = m_sc.levels + targetLvl;
    if (m_sc.cur.bitrate < lvl->bitrate) {
        if (lvl->w != SCL_KEEP && (lvl->h != SCL_KEEP) && //a valid level setting
            ((lvl->w < m_sc.cur.w) || (lvl->h < m_sc.cur.h))    ) {//need to shink
            m_sc.cur.w = lvl->w;
            m_sc.cur.h = lvl->h;
            m_sc.levelCur = targetLvl;
            UpdateRes();
        }
    }
#endif
}

static void EnlargeStream(void)
{
#if SC_CHANGE_RES
    struct StreamControlLevel *lvl;
    UINT16 targetLvl;
#endif
    UINT32 bitrate;

    DBGSC("Enlarge\r\n");

    bitrate = m_sc.cur.bitrate;
    m_sc.cur.bitrate *= m_scp.enlarge.m;
    m_sc.cur.bitrate >>= m_scp.enlarge.n;
    if (m_sc.cur.bitrate > m_sc.conf.bitrate) {
        m_sc.cur.bitrate = m_sc.conf.bitrate;
    }
    if (bitrate != m_sc.cur.bitrate)
        UpdateBitrate();

#if SC_CHANGE_RES
    DBGSC("from level %d\r\n", m_sc.levelCur);
    targetLvl = m_sc.levelCur + 1;
    if (targetLvl >= m_sc.nLevels) {
        targetLvl--;
    }
    lvl = m_sc.levels + targetLvl;
    if (m_sc.cur.bitrate > lvl->bitrate) {
        if ((lvl->w != SCL_KEEP)    && (lvl->h != SCL_KEEP) &&    //a valid level setting
            (lvl->w <= m_sc.conf.w) && (lvl->h <= m_sc.conf.h) && //level RES not exceed CONF RES
            ((lvl->w > m_sc.cur.w) || (lvl->h > m_sc.cur.h))  ) { //need to enlarge
            m_sc.cur.w = lvl->w;
            m_sc.cur.h = lvl->h;
            m_sc.levelCur = targetLvl;
            UpdateRes();
        }
    }
#endif
}

static void AdjustStream(void)
{
    if (m_sc.stress.Sum > m_scp.score.max) {
        ShinkStream();
    }
    else if (m_sc.stress.Sum < m_scp.score.min) {
        EnlargeStream();
    }
}

void STATE_NET_STREAMING_WIRELESS_TX_REPORT(UINT32 ulEvent, UINT32 ulParam)
{
    struct osal_ev_tx_rpt *rpt = (struct osal_ev_tx_rpt*)ulParam;
#if DBG_UI_NET_EVENT
    printd(FG_RED("in STATE_NET_STREAMING_WIRELESS_TX_REPORT")"\r\n");
    if (ulEvent == WIRELESS_TX_REPORT) {
        //DBGSC("Get event = WIRELESS_TX_REPORT\r\n");
    }
#endif
    if (rpt) {
        DBGSC("Get report score:%d overflow:%d\r\n", rpt->stress, rpt->overflow);
        ResetStreamControl(rpt->reset);
        if (rpt->overflow == OSAL_TXF_OVERFLOW) {
            DBGSC(BG_RED("Panic!")"\r\n");
            ShinkStream();
        }
        if (rpt->stress != TX_RPT_NA) {
            RecordScore(rpt->stress);
            AdjustStream();
        }
        CGI_SET_STATUS(ulEvent, CGI_ERR_NONE);
    } else {
        CGI_SET_STATUS(ulEvent, CGI_ERR_INVALID_PARAM);
    }
}

AHC_BOOL StateNetStreamingModeInit(void* pData)
{
    AHC_BOOL ahcRet = AHC_TRUE;

    UartSendTrace("%s,%d \n", __FUNCTION__, __LINE__);

    MMPF_FrameRing_SetMoveCallback(VideoRecordStreamCallback);

    #if defined(SPEECH_RECOGNIZE_EN)&&(SPEECH_RECOGNIZE_EN)//avoid conflicting with speech function
	MMPD_Streaming_Enable(AUDIO_RING_STREAM, MMP_FALSE, MMP_FALSE);
    if (MMP_ERR_NONE != MMPS_LiveAudio_StopRecord()) {
        UartSendTrace(FG_RED("[ERR] Unable to stop audio encode\r\n"));
    }
    #endif

    return ahcRet;
}

AHC_BOOL StateNetStreamingModeShutDown(void* pData)
{
    UartSendTrace("%s,%d \n", __FUNCTION__, __LINE__);

    //samon,temporary solution,need to be confirmed
    if(AHC_GetStreamingMode() != AHC_STREAM_NONE)
    {
        AHC_SetStreamingMode(AHC_STREAM_OFF);
    }

    MMPF_FrameRing_SetMoveCallback(NULL);

#if defined(SPEECH_RECOGNIZE_EN)&&(SPEECH_RECOGNIZE_EN)//avoid conflicting with speech function
    MMPS_AUDIO_InitLiveRecord(MMP_AUDIO_PCM_ENCODE, 0, 16000, (MMP_LivePCMCB)Speech_PCMTransferCB);
    MMPS_LiveAudio_StartRecord();
    MMPD_Streaming_Enable(AUDIO_RING_STREAM, MMP_TRUE, MMP_TRUE);
#endif

    return AHC_TRUE;
}

AHC_BOOL StateSelectFuncNetStreamingMode(void)
{
    AHC_BOOL    ahcRet = AHC_TRUE;

    ahcRet = StateModeSetOperation(UI_NET_STREAMING_STATE, StateNetStreamingModeInit, StateNetStreamingModeShutDown, StateNetStreamingModeHandler);

    uiStateRegisterNetEventHandler(WIRELESS_SET_STREAMING_MODE, STATE_NET_STREAMING_WIRELESS_SET_STREAMING_MODE);
    //Key Event will be dropped
    RegisterEventCb(EVENT_DROP, STATE_COMMON_DROP_EVENT);
    //Net Streaming mode can support CGI cmd also.
    uiStateRegisterCommonCgiHandlers();

    uiStateRegisterNetEventHandler(WIRELESS_TX_REPORT, STATE_NET_STREAMING_WIRELESS_TX_REPORT);

    return ahcRet;
}


UINT32 StateNetStreamingModeHandler(UINT32 ulMsgId, UINT32 ulEvent, UINT32 ulParam)
{
    return uiStateNetProcessMsg(KeyParser_NetStreamingEvent, ulMsgId, ulEvent, ulParam);
}

#endif //#if (defined(WIFI_PORT) && WIFI_PORT == 1)
