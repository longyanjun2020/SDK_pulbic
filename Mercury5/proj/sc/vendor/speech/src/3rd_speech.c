
/*===========================================================================
 * Include file
 *===========================================================================*/
#define _3RD_SPEECH_C_

#include "ahc_common.h"
#include "ahc_os.h"
#include "ahc_version.h"
#include "ahc_parameter.h"
#include "AIT_Init.h"
#include "mmpf_system.h"
#include "3rd_speech.h"
#include "lock_queue.h"
#if defined(__RTK_OS__)
#include "cam_os_wrapper.h"
#endif
#if defined(SPEECH_RECOGNIZE_EN) && (SPEECH_RECOGNIZE_EN)

#define USE_SPEECH_AUTH_LIB      (0)//replace wtk.lib

#if defined(USE_SPEECH_AUTH_LIB)&&(USE_SPEECH_AUTH_LIB)
#include "aiengine.h"
#else
#include "api_wakeup.h"
#endif

/*===========================================================================
 * Global variable
 *===========================================================================*/
#if defined(USE_SPEECH_AUTH_LIB)&&(USE_SPEECH_AUTH_LIB)
struct aiengine         *instB = NULL;
int                     g_SpeechWakeUp = 0;
#else
static wakeup_t         *instB = NULL;
#endif
static lock_queue_t     msg_q;
static lock_queue_t     msg_q_empty;
static voice_msg_t      dummy_buff;
static MMP_SpeechRecogCbFunc    gpfSpeechCbFunc = NULL;

MMPF_OS_FLAGID          g_Speech_Flag;
/*===========================================================================
 * Extern variable
 *===========================================================================*/


/*===========================================================================
 * Extern function
 *===========================================================================*/


/*===========================================================================
 * Macro
 *===========================================================================*/

#define DEBUG_ROUTTINE          (0)
#define DEBUG_SPEECH_RECOG_CPUB (0)
#define WRITE_PCM_RAW_DATA      (1)
#define DEBUG_SPEECH_RESULT     (1)
#define DEBUG_PCM_WR_DATA_SEC   (25000)
#define DEBUG_STAT_TIME         (5000)

#define SPEECH_RECOG_PCM_DATA_WRITE_FILE    (0)

#define SPEECH_FLAG_RUN    (0x0001)

/*===========================================================================
 * Main body
 *===========================================================================*/
#if defined(USE_SPEECH_AUTH_LIB)&&(USE_SPEECH_AUTH_LIB)
int engine_cb(void *userdata, const char *id, int type, const void *message, int size) {
    int *wakeup = (int *)userdata;
    char msglog[200]={0};
    //*env = "words=wo yao pai zhao,wo yao lu xiang,da kai ping mu,guan bi ping mu;thresh=0.26,0.22,0.19,0.22;";
    char msginfo_1[] = "wo yao lu xiang";
    char msginfo_2[] = "wo yao pai zhao";
    char msginfo_3[] = "da kai lu yin";
    char msginfo_4[] = "guan bi lu yin";
    char msginfo_5[] = "da kai re dian";
    char msginfo_6[] = "guan bi re dian";
    char msginfo_7[] = "da kai ping mu";
    char msginfo_8[] = "guan bi ping mu";
    char msginfo_9[] ="qie huan hou lu";
    char msginfo_10[]="hui dao qian lu";
    MMP_ULONG   ulKeyId;

    *wakeup = 1;
    printf("result:%s userdata=0x%08x, id=%x, type=%x, size=%x\r\n", (char *)message,userdata,*id,type,size);

    if (g_SpeechWakeUp)
    {
        if (sizeof(msglog)>(size+2)) {
            memcpy(msglog,message,size);
            msglog[size]='\0';
            msglog[size+1]='\0';
            printc("#speech _handler: %s\r\n",msglog);
            ShowOnPnl_SendMsg("#speech : %s\r\n",msglog);
        }

        if (strstr(message,msginfo_1) != NULL)
        {
            ulKeyId = 1;
        }
        else if (strstr(message,msginfo_2) != NULL)
        {
            ulKeyId = 2;
        }
        else if (strstr(message,msginfo_3) != NULL)
        {
            ulKeyId = 3;
        }
        else if (strstr(message,msginfo_4) != NULL)
        {
            ulKeyId = 4;
        }
        else if (strstr(message,msginfo_5) != NULL)
        {
            ulKeyId = 5;
        }
        else if (strstr(message,msginfo_6) != NULL)
        {
            ulKeyId = 6;
        }
        else if (strstr(message,msginfo_7) != NULL)
        {
            ulKeyId = 7;
        }
        else if (strstr(message,msginfo_8) != NULL)
        {
            ulKeyId = 8;
        }
        else if (strstr(message,msginfo_9) != NULL)
        {
            ulKeyId = 9;
        }
        else if (strstr(message,msginfo_10) != NULL)
        {
            ulKeyId = 10;
        }
        else
        {
            printc("#SC_Log: is the invalidate wakeup word!%s\r\n",msglog);
        }

        if (NULL != gpfSpeechCbFunc)
            gpfSpeechCbFunc(ulKeyId);
    }

    g_SpeechWakeUp = 0;
    return 0;
}

#else

int _handler(void *obj, wakeup_status_t status, char *json, int bytes)
{
    #if DEBUG_SPEECH_RESULT
    char msglog[200]={0};
    //*env = "words=wo yao pai zhao,wo yao lu xiang,da kai ping mu,guan bi ping mu;thresh=0.26,0.22,0.19,0.22;";
    char msginfo_1[] = "wo yao lu xiang";
    char msginfo_2[] = "wo yao pai zhao";
    char msginfo_3[] = "da kai lu yin";
    char msginfo_4[] = "guan bi lu yin";
    char msginfo_5[] = "da kai re dian";
    char msginfo_6[] = "guan bi re dian";
    char msginfo_7[] = "da kai ping mu";
    char msginfo_8[] = "guan bi ping mu";
    char msginfo_9[] ="qie huan hou lu";
    char msginfo_10[]="hui dao qian lu";
    MMP_ULONG   ulKeyId;

    if (status == 0) {
        printc("not wakeup.\r\n");
    }
    else {
        if (sizeof(msglog)>(bytes+2)) {
            memcpy(msglog,json,bytes);
            msglog[bytes]='\0';
            msglog[bytes+1]='\0';
            printc("#speech _handler: %s\r\n",msglog);
            ShowOnPnl_SendMsg("#speech : %s\r\n",msglog);
        }

        if (strstr(json,msginfo_1) != NULL)
        {
            ulKeyId = 1;
        }
        else if (strstr(json,msginfo_2) != NULL)
        {
            ulKeyId = 2;
        }
        else if (strstr(json,msginfo_3) != NULL)
        {
            ulKeyId = 3;
        }
        else if (strstr(json,msginfo_4) != NULL)
        {
            ulKeyId = 4;
        }
        else if (strstr(json,msginfo_5) != NULL)
        {
            ulKeyId = 5;
        }
        else if (strstr(json,msginfo_6) != NULL)
        {
            ulKeyId = 6;
        }
        else if (strstr(json,msginfo_7) != NULL)
        {
            ulKeyId = 7;
        }
        else if (strstr(json,msginfo_8) != NULL)
        {
            ulKeyId = 8;
        }
        else if (strstr(json,msginfo_9) != NULL)
        {
            ulKeyId = 9;
        }
        else if (strstr(json,msginfo_10) != NULL)
        {
            ulKeyId = 10;
        }
        else
        {
            printc("#SC_Log: is the invalidate wakeup word!%s\r\n",msglog);
        }

        if (NULL != gpfSpeechCbFunc)
            gpfSpeechCbFunc(ulKeyId);
    }
#endif

    return 0;
}
#endif

//------------------------------------------------------------------------------
//  Function    : MMPF_VMD_ProcRequest
//  Description :
//------------------------------------------------------------------------------
/** @brief The function processes the request from master core
*/

void _myprint( char* str, ... )
{
    printc("\r\n something wakeup.",str);
}

MMP_ERR Speech_SetCB(MMP_SpeechRecogCbFunc  CB)
{
    gpfSpeechCbFunc = CB;
    return MMP_ERR_NONE;
}

void LivePCMReadOut(AUTL_RINGBUF pPCMOutRing,MMP_SHORT *target, MMP_ULONG samples)
{
    MMP_BYTE *ring_data;
    MMP_ULONG  ring_end_ofst;

    ring_data = (MMP_BYTE *)pPCMOutRing.buf + pPCMOutRing.ptr.rd;
    ring_end_ofst = pPCMOutRing.size - pPCMOutRing.ptr.rd;

    if (ring_end_ofst >= samples) {
        MEMCPY(target, ring_data, samples << 1);
    }
    else {
        MEMCPY(target, ring_data, ring_end_ofst << 1);
        samples  -= ring_end_ofst;
        target   += ring_end_ofst;
        ring_data = (MMP_BYTE *)pPCMOutRing.buf;
        MEMCPY(target, ring_data, samples << 1);
    }

}

MMP_BOOL Speech_AuthPass(void)
{
    return (instB != NULL);
}

MMP_ULONG Speech_PCMTransferCB(AUTL_RINGBUF *pPCMOutRing, MMP_ULONG ulUnReadSampleCnt)
{
    static MMP_LONG sSumdata = 0;
    voice_msg_t *msg_buff;

    #if DEBUG_ROUTTINE
    //printc("\r\nSpeechPCMTransferCB: %d (0x%x)\r\n", ulUnReadSampleCnt, pPCMOutRing);
    #endif

    if (pPCMOutRing == NULL) {
        return  0;
    }

    if (ulUnReadSampleCnt > 0)
    {
        msg_buff = Speech_GetBuffer();
        if (NULL != msg_buff /*&& msg_buff->bytes >= PCM_SAMPLE_CNT*/)
        {
            MMP_ULONG ulLenByte,ulLenShort;

            ulLenByte = MIN(ulUnReadSampleCnt*2, msg_buff->bytes);//ulUnReadSampleCnt->short, pbuff->byte
            ulLenShort = ulLenByte>>1;

            LivePCMReadOut(*pPCMOutRing, (MMP_SHORT *)msg_buff->data, ulLenShort);
            msg_buff->bytes = ulLenByte;

            #if defined(SPEECH_RECOG_PCM_DATA_WRITE_FILE)&&(SPEECH_RECOG_PCM_DATA_WRITE_FILE)
            {
                MMP_ERR ErrResult = MMP_ERR_NONE;
                static char FileName[256];
                static MMP_ULONG ulFileID = NULL;
                MMP_ULONG ulWriteSize;
                static MMP_ULONG last_time = 0;
                static MMP_ULONG Write_time = 0;
                MMP_ULONG current_time = 0;

                sSumdata += ulLenByte;
                MMPF_OS_GetTimeMs(&current_time);
                if (Write_time == 0)
                    Write_time = current_time;

                #if WRITE_PCM_RAW_DATA
                if (((current_time - Write_time)>= DEBUG_PCM_WR_DATA_SEC) && NULL != ulFileID)
                {
                    ErrResult = MMPF_FS_FClose(ulFileID);
                    ulFileID = NULL;
                    printc("Speech data:FClose %s,T=%d\r\n",FileName,current_time);
                    Write_time = current_time;
                }
                else if (current_time - Write_time < DEBUG_PCM_WR_DATA_SEC)
                {
                    if (ulFileID == NULL) {
                        sprintf(FileName, "SD:\\PCM%d.pcm",current_time/1000);
                        ErrResult = MMPF_FS_FOpen(FileName, "wb", &ulFileID);
                        if (MMP_ERR_NONE == ErrResult) {
                            Write_time = current_time;
                            printc("Speech data:FOpen %s\r\n",FileName);
                        }
                    }
                    else{
                        ErrResult = MMPF_FS_FWrite(ulFileID,(void *)msg_buff->data,ulLenByte,&ulWriteSize);
                        if (ErrResult || ulLenByte != ulWriteSize)
                            printc("write speech err: w=%d,act=%d\r\n", ulLenByte,ulWriteSize);
                    }
                }
                #endif
                #if DEBUG_ROUTTINE
                if ((current_time - last_time)>= 2000)
                {
                    last_time = current_time;
                    printc("Speech data:(0x%x)@pSec,T%d\r\n", sSumdata,last_time);
                    sSumdata = 0;
                }
                #endif
            }
            #endif

            Speech_SetVoiceData(msg_buff);

            return  (ulLenShort);
        }
        else {
            printc("SpeechPCMTransferCB: get buff fail,Total samples:(0x%x)\r\n", pPCMOutRing->size);
        }
    }

    return  0;
}



MMP_ERR Speech_Init(void)
{
    MMP_BYTE    *env = "words=wo yao pai zhao,wo yao lu xiang,da kai ping mu,guan bi ping mu;thresh=0.26,0.22,0.19,0.22;";
    MMP_LONG    ret = -1;
    MMP_LONG    uiStrlen = 0;
    #if defined(USE_SPEECH_AUTH_LIB)&&(USE_SPEECH_AUTH_LIB)
    char *engineCfg = NULL;
    char *engineParam = NULL;
    char id[64];
    char *err_info = NULL;
    #endif

    if (NULL == instB) {
        ret = lock_queue_init(&msg_q, 0);
        ret |= lock_queue_init(&msg_q_empty, 0);
        printc("create mutext msg_q = %p, ret = %d, msg_q->lock = %d\r\n", &msg_q, ret, msg_q.lock);

    #if defined(USE_SPEECH_AUTH_LIB)&&(USE_SPEECH_AUTH_LIB)
        engineCfg = "{\
                        \"appKey\":\"xxxxx\",\
                        \"secretKey\":\"xxxxx\",\
                        \"provision\":\"SD:\\\\aiengine-2.9.4-xxxxx.provision\",\
                        \"serialNumber\":\"SD:\\\\aiengine-2.9.4-xxxxx.serialNumber\",\
                        \"version\":\"aiengine-2.9.4\",\
                        \"native\":{\
                            \"cn.wakeup\":{\
                                \"resBinPath\":\"\"\
                            }\
                        }\
                    }";

        engineParam =
        "{\
            \"request\":{\
                \"env\":\"words=wo yao pai zhao,wo yao lu xiang,da kai ping mu,guan bi ping mu;thresh=0.26,0.22,0.19,0.22;\"\
            }\
        }";

        ret = aiengine_check_auth(engineCfg, &err_info);
        if (ret != 0) {
            printc("check auth error: %s\n", err_info);
            ret = -1;
        }
        else {
            printc("check auth success");
        }

        instB = aiengine_new(engineCfg);
        if (!instB) {
            printc("create engine error\n");
            ret = -1;
        }
        else {
            printc("create engine success\n");
        }

        g_SpeechWakeUp = 0;
        ret = aiengine_start(instB, engineParam, id, engine_cb, &g_SpeechWakeUp);
        if (ret == -1) {
            printc("start engine error\n");
        }
        else {
            printc("start engine success\n");
        }
    #else
        instB = wakeup_new(NULL, NULL);
        wakeup_register_handler(instB, instB, _handler);
        uiStrlen = strlen(env);
        printc("uiStrlen = %d\r\n",uiStrlen);

        wakeup_start(instB, env, uiStrlen);
        //instB = 1;//for test
    #endif
    }

    return ((ret == 0)&&(NULL != instB))?(MMP_ERR_NONE):(MMP_USER_ERR_INIT);
}

 //------------------------------------------------------------------------------
 //  Function    : Speech_Task
 //  Description :
 //------------------------------------------------------------------------------
 void Speech_Task(void)
 {
    MMPF_OS_FLAGS   sFlags;
    voice_msg_t     *msg = NULL;
    int             ret = -1;
    MMP_ULONG       start_time,end_time;
    static MMP_ULONG    ulLastTime = 0, ulStatBytes = 0, ulStatTime = 0;
    CamOsRet_e      eRet = CAM_OS_OK;
    MMPF_OS_FLAGS   wait_flags, flags;

    g_Speech_Flag = MMPF_OS_CreateEventFlagGrp(0);
    if (g_Speech_Flag >= MMPF_OS_ERR_FLAG_ID_EXCEED_MAX) {
        RTNA_DBG_Str(0, "Error:g_Speech_Flag Failed\r\n");
        return;
    }

    if (MMP_ERR_NONE != Speech_Init()) {
        RTNA_DBG_Str(0, "Speech_Task() Init failure\r\n");
        //goto ERR_EXIT_SPEECH;
    }
    else{
        RTNA_DBG_Str(0, "Speech_Task() running\r\n");
    }

    wait_flags = SPEECH_FLAG_RUN;

    while (1) {

        if (NULL == instB) {
            MMPF_OS_Sleep_MS(50);
            continue;
        }

        MMPF_OS_WaitFlags(g_Speech_Flag, wait_flags, MMPF_OS_FLAG_WAIT_SET_ANY | MMPF_OS_FLAG_CONSUME, 0, &flags);

        if (flags & SPEECH_FLAG_RUN) {
            // Drop Pre PCM Data
            while (lock_queue_query(&msg_q) > 1) {
                msg = (voice_msg_t*)lock_queue_pop(&msg_q);
                if (msg)
                    lock_queue_push(&msg_q_empty, &(msg->n));
            }

            msg = (voice_msg_t*)lock_queue_pop(&msg_q);

            if (msg == NULL) {
                //MMPF_OS_Sleep_MS(50);
                continue;
            }

            switch (msg->type) {
                case VOICE_MSG_DATA:
                    #if DEBUG_ROUTTINE
                    MMPF_OS_GetTimeMs(&start_time);
                    #endif

                    #if defined(USE_SPEECH_AUTH_LIB)&&(USE_SPEECH_AUTH_LIB)
                    ret = aiengine_feed(instB, (char *)msg->data, msg->bytes);
                    #else
                    ret = wakeup_feed(instB, (char *)msg->data, msg->bytes);
                    #endif

                    if (ret != 0) {
                        printc("feed data error\n");
                        //goto ERR_EXIT_SPEECH;
                    }

                    #if DEBUG_ROUTTINE
                    MMPF_OS_GetTimeMs(&end_time);
                    ulStatBytes += msg->bytes;
                    ulStatTime += end_time-start_time;
                    //(100*ulStatTime)/(Time Total)
                    //Time Total:   1000*ulStatCnt/32000-->ulStatCnt/32
                    //(100*ulStatTime)/(ulStatCnt/32)-->(100*ulStatTime*32)/(ulStatCnt)
                    if ((end_time - ulLastTime) > DEBUG_STAT_TIME) {
                        ulLastTime = end_time;
                        printc("\r\npop:cnt=%d,Dlen=%d,cpu:%d%%\r\n",msg_q.length,msg->bytes,((100*ulStatTime*32)/ulStatBytes));
                        ulStatBytes = ulStatTime = 0;
                    }
                    #endif
                break;
                default:
                    printc("[%s,%d] unsupported.\n",__FUNCTION__, __LINE__);
                break;
            }

            if (msg != NULL) {
                #if 1
                if (lock_queue_push(&msg_q_empty, &(msg->n))) {
                    printc("lock_queue_push error.#%d\n", __LINE__);
                }
                #else
                MsReleaseMemory(msg);
                msg = NULL;
                #endif
            }
        }
    }

ERR_EXIT_SPEECH:
    #if defined(USE_SPEECH_AUTH_LIB)&&(USE_SPEECH_AUTH_LIB)
    aiengine_stop(instB);
    if (instB)
        aiengine_delete(instB);
    #else
    wakeup_end(instB);
    #endif

    MMPF_OS_DeleteEventFlagGrp(g_Speech_Flag);
    printc("[ERR]MMPF_SpeechRecog_Routine exit!\r\n");
 }

 //------------------------------------------------------------------------------
 //  Function    : Speech_TaskHandler
 //  Description :
 //------------------------------------------------------------------------------
void Speech_TaskHandler(void *p_arg)
{
    Speech_Task();
}

voice_msg_t* Speech_GetBuffer(void)
{
    MMP_ERR         ret = MMP_ERR_NONE;
    voice_msg_t     *pbuf = NULL;
    void*           BufAddr_Virt;
    MMP_ULONG64     BufAddr_Phys;
    CamOsRet_e      eRet = CAM_OS_OK;
    static MMP_BYTE bMemCnt = 0;

    pbuf = (voice_msg_t*)lock_queue_pop(&msg_q_empty);
    if (NULL == pbuf && bMemCnt < 10) {
        pbuf = MsAllocateMem(sizeof(voice_msg_t));
        bMemCnt ++;
        //printc("speech malloc =%p,livepcm bMemCnt=%d\r\n",pbuf,bMemCnt);
    }

    if (pbuf != NULL) {

        pbuf->bytes = MSG_LENGTH;
        pbuf->type = VOICE_MSG_DATA;

        #if DEBUG_SPEECH_RECOG_CPUB
        printc("speech malloc =%p,size=%d\r\n",pbuf,sizeof(voice_msg_t));
        #endif
    }
    else {
        //printc("#speech: GET_BUFF err\r\n");
        ret = MMP_SYSTEM_ERR_MALLOC;
    }

    return (ret == MMP_ERR_NONE)?(pbuf):(NULL);
}

MMP_ERR Speech_SetVoiceData(void *buf)
{
    MMP_ULONG   pmsg;
    voice_msg_t *msg;
    int         ret = -1;

    if (NULL != instB) {
        msg = (voice_msg_t*)buf;

#if DEBUG_SPEECH_RECOG_CPUB
        printc("push:Q cnt=%d,msg =%p,len=%d\r\n", msg_q.length,msg,msg->bytes);
#endif
        ret = lock_queue_push(&msg_q, &(msg->n));
        MMPF_OS_SetFlags(g_Speech_Flag, SPEECH_FLAG_RUN, MMPF_OS_FLAG_SET);
    }

    return (ret == 0) ? (MMP_ERR_NONE):(MMP_SYSTEM_ERR_PARAMETER);
}

#endif
#undef  _3RD_SPEECH_C_

