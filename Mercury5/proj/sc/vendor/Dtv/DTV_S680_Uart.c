/*===========================================================================
 * Include file
 *===========================================================================*/
#include "Customer_config.h"

#include "ait_utility.h"
#include "mmpf_uart.h"
#include "MenuSetting.h"
#include "ahc_os.h"
#include "ahc_parameter.h"
#include "AHC_message.h"
#include "ahc_general.h"
#include "DTV_S680_Uart.h"
#include "AIT_Init.h"
#include "ahc_menu.h"
#include "AHC_media.h"
#include "mediaplaybackctrl.h"
#include "MenuStateEditToolMenu.h"
#include "MenuStatePlayBackMenu.h"
#include "statevideofunc.h"
#include "UartCmd2Navi.h"
#include "ahc_version.h"
#include "ahc_general_cardv.h"
#if defined(__GNUC__)
#include "vm_types.ht"
#endif

/*===========================================================================
 * Macro define
 *===========================================================================*/

void printc(char* fmt, ...);

#ifdef _DEBUG_
#define DPRINT( ... )   printc( __VA_ARGS__);
#else
#define DPRINT( ... )   {}
#endif

/*===========================================================================
 * Global varible
 *===========================================================================*/

#ifdef ALL_FW
static int          m_bUartRxStrLen=0;
static MMP_BYTE     m_bUartString[Uart_RX_QUEUE_SIZE] = {0};
static MMP_BOOL     m_bUartRxSatus = AHC_FALSE;
UINT16 uCurHour,uCurMinute,uCurSecond;
UINT32 g_fileIdx = 0;

MMP_UBYTE g_Ack2NaviArg = NAVIACK_NULL;

extern AHC_BOOL Deleting_InBrowser;
extern UINT32 ObjSelect;
//extern AHC_BOOL bForceSwitchBrowser;
extern AHC_BOOL bMuteRecord;
#if (LIMIT_MAX_LOCK_FILE_NUM)
extern UINT32 m_ulLockFileNum;
extern UINT32 m_ulLockEventNum;
#endif
extern AHC_BOOL m_ubPlaybackRearCam;


static MMP_LONG DTV_Uart_MergePack(MMP_UBYTE *pBuff);
extern AHC_BOOL AHC_Thumb_IsFileProtect(UINT32 wDcfObjIdx);
#endif

#define JWD_HONDA_TOUCH     0





#if (TOUCH_UART_FUNC_EN)
extern MMPF_OS_FLAGID       UartCtrlFlag;
static const CMDKEY CmdKey[] =
{
    {KEY_CH_UP,     KEY_PRESS_UP,   "CH UP"     },
    {KEY_CH_DOWN,   KEY_PRESS_DOWN, "CH DOWN"   },
    {KEY_VOL_UP,    KEY_PRESS_UP,   "VOL UP"    },
    {KEY_VOL_DOWN,  KEY_REL_DOWN,   "VOL DOWN"  },
    {KEY_MENU,      KEY_REL_MENU,   "KEY MENU"  },
    {KEY_PAUSE,     KEY_REL_PLAY,   "KEY PAUSE" },
    {KEY_EXIT,      KEY_REL_FUNC1,  "KEY EXIT"  },
    {KEY_POWER,     KEY_REL_POWER,  "KEY POWER" },
    {KEY_MUTE,      KEY_PRESS_MUTE, "KEY MUTE"  },
    {KEY_PAGE_UP,   KEY_PRESS_LEFT, "PAGE UP"   },
    {KEY_PAGE_DOWN, KEY_PRESS_RIGHT,"PAGE DOWN" },
};

static MMP_UBYTE    gNumOfCMDIDKey = sizeof(CmdKey) / sizeof(CMDKEY);

/*===========================================================================
 * Main body
 *===========================================================================*/
#ifdef ALL_FW

//------------------------------------------------------------------------------
//  Function    : DTV_Uart_TouchPress
//  Description : Get the parsed UART information.
//------------------------------------------------------------------------------
#define offset_x  10
static void DTV_Uart_TouchPress(MMP_BYTE *pBuff)
{
    MMP_USHORT TemppX=0, TemppY=0;
    MMP_ULONG  ulParm;
    UINT32      curtick;
    static  UINT32 pretick;

    #if JWD_HONDA_TOUCH
    UINT32      curtick;
    static  UINT32 pretick;

    MMPF_OS_GetTime(&curtick);
    if(curtick - pretick < 300)
    {
        pretick = curtick;
        return;
    }
    pretick = curtick;
    #endif

    TemppX = (MMP_USHORT)pBuff[4]>>4&0x0F;
    TemppX = TemppX<<8 | pBuff[3] ;

    #if JWD_HONDA_TOUCH
    if(TemppX>720) TemppX = 0; //TBD
    #else
    if(TemppX<360)  TemppX += offset_x;
    #endif

    TemppY = (MMP_USHORT)pBuff[4]&0x0F;
    TemppY = TemppY<<8 | pBuff[5];
    ulParm = TemppY<<16 | TemppX;

    printc("ulParm %x\r\n",ulParm);
//  SetKeyPadEvent(TOUCH_PANEL_PRESS);
    AHC_SendAHLMessage(AHLM_UI_NOTIFICATION, TOUCH_PANEL_PRESS, ulParm);
}

static void DTV_Uart_TouchRelease(MMP_BYTE *pBuff)
{
    printc("DTV_Uart_TouchRelease  \r\n");
    SetKeyPadEvent(TOUCH_PANEL_REL);
}

//------------------------------------------------------------------------------
//  Function    : DTV_Uart_CheckSum
//  Description : return checksum
//------------------------------------------------------------------------------
//起始字符：
//0xFF 0xAA
//数据长度：
//1BYTE //数据种类+数据内容长度
//数据种类：
//      1BYTE (DVR发送0x01~0x9f, 主机发送0xA1~0xff)
//数据内容：
//        N个BYTE
//Checksum校验：
//数据长度 +数据种类 +数据内容相加---1BYTE

static MMP_UBYTE DTV_Uart_CheckSum(MMP_BYTE *pBuff)
{
    MMP_UBYTE sum = 0;
    MMP_UBYTE   i = 0;

    for(i=0;i<=(pBuff[0]);i++)
    {
        sum += pBuff[i];
    }

    return sum;
}

//data1:0x03  data2:分辨率
//data3:停车侦测
//data4:录音
//data5:重力感应
//data6:开机自动录像
static void DTV_Uart_SetParam(MMP_BYTE *pBuff)
{
    //MMP_BYTE data1 = pBuff[2];
    MMP_BYTE data2 = pBuff[3];
    MMP_BYTE data3 = pBuff[4];
    MMP_BYTE data4 = pBuff[5];
    MMP_BYTE data5 = pBuff[6];
    MMP_BYTE data6 = pBuff[7];
    MMP_UBYTE   ubRecordWithAudio = data4;

    if(VideoFunc_GetRecordStatus()){
        printc("ERR %s:current is recording, pls stop record first\r\n",__func__);
        return;
    }

    //resolution
    if(data2 == 1)
    {
        printc("%s: set 1080@30P\r\n",__func__);
        MenuSettingConfig()->uiMOVSize = MOVIE_SIZE_1080P;//MOVIE_SIZE_1080_30P;
    }
    else if(data2 == 0)
    {
        printc("%s: set 720@30P\r\n",__func__);
        MenuSettingConfig()->uiMOVSize = MOVIE_SIZE_720P;//MOVIE_SIZE_720_30P;
    }
    else
    {
        printc("%s:TODO \r\n",__func__);
    }
    Menu_SetMovieMode(MenuSettingConfig()->uiMOVSize);

    //parking on/off
    #if MENU_GENERAL_GSENSOR_EN
    if(data3 != Getpf_GSNR_THR() && data3 < GSENSOR_SENSITIVITY_NUM){
        printc("%s: set gsensor,old=%d,new=%d \r\n",__func__,__LINE__,Getpf_GSNR_THR,data3);
        Setpf_GSNR_THR();
    }
    #endif

    //MIC rec on/off
    AHC_Menu_SettingGetCB((char *)"RecordWithAudio", &ubRecordWithAudio);
    printc("%s: MIC rec %s\r\n",__func__,(ubRecordWithAudio? "on":"off"));

    //AHC_ToggleMute will change uiMOVSoundRecord  to next state, so set uiMOVSoundRecord to other state which not we wish.
    MenuSettingConfig()->uiMOVSoundRecord = ubRecordWithAudio? (MOVIE_SOUND_RECORD_OFF):(MOVIE_SOUND_RECORD_ON);
    AHC_ToggleMute();
    //MenuSettingConfig()->uiMOVSoundRecord = ubRecordWithAudio? (MOVIE_SOUND_RECORD_ON):(MOVIE_SOUND_RECORD_OFF);

    //开机自动录像
    if(data6)
        MenuSettingConfig()->uiAutoRec = AUTO_REC_ON;
    else
        MenuSettingConfig()->uiAutoRec = AUTO_REC_OFF;
    printc("%s: AUTO Vrec %s\r\n",__func__,(data6? "on":"off"));


    //data5:重力感应,保护灵敏度
   #if (GSENSOR_CONNECT_ENABLE)
    //#define MENU_GENERAL_GSENSOR_LEVEL0_EN              (1)
    //#define MENU_GENERAL_GSENSOR_LEVEL1_EN              (0)
    //#define MENU_GENERAL_GSENSOR_LEVEL2_EN              (1)
    //#define MENU_GENERAL_GSENSOR_LEVEL3_EN              (0)
    //#define MENU_GENERAL_GSENSOR_LEVEL4_EN              (1)
    if(data5 == 0X0A)
    {
        printc("%s:set gsensor sensitivity high\r\n",__func__);
        MenuSettingConfig()->uiGsensorSensitivity = GSENSOR_SENSITIVITY_L4;//高灵敏度
    }
    else if(data5 == 0X14)
    {
        printc("%s:set gsensor sensitivity mid\r\n",__func__);
        MenuSettingConfig()->uiGsensorSensitivity = GSENSOR_SENSITIVITY_L2;
    }
    else if(data5 == 0X1e)
    {
        printc("%s:set gsensor sensitivity low\r\n",__func__);
        MenuSettingConfig()->uiGsensorSensitivity = GSENSOR_SENSITIVITY_L0;
    }
    else
    {
        printc("%s: line%d param error \r\n",__func__,__LINE__);
    }

    AHC_Gsensor_UI_SetIntThreshold();
    #endif

    ResetCurrentMenu();
    Menu_ImportSetting();
}

//data1:0x03  data2:分辨率 data3:停车侦测 data4:录音 data5:重力感应
static MMP_BYTE DTV_Uart_GetParam(MMP_BYTE param)
{
    MMP_BYTE data = 0;
    switch(param)
    {

    }
    return data;
}


AHC_BOOL DTV_Uart_LockOne(AHC_BOOL bIsHover)
{
    AHC_BOOL ret;

    if(AHC_CheckCurSysMode(AHC_MODE_PLAYBACK))
    {

        if(bIsHover)
            ret = QuickFileOperation(DCF_FILE_READ_ONLY_ALL_CAM);
        else
            ret = QuickFileOperation(DCF_FILE_NON_READ_ONLY_ALL_CAM);

        if(ret!=EDIT_FILE_SUCCESS)
        {
            printc("WARN:Protect File Directly fail\r\n");
            return FALSE;
        }
    }
    else if(AHC_CheckCurSysMode(AHC_MODE_THUMB_BROWSER))
    {
        if(bIsHover)
            ret = QuickFileOperation(DCF_FILE_READ_ONLY_ALL_CAM);
        else
            ret = QuickFileOperation(DCF_FILE_NON_READ_ONLY_ALL_CAM);

        if(ret!=EDIT_FILE_SUCCESS)
        {
            printc("WARN:Protect File Directly fail\r\n");
            return FALSE;
        }
        else
        {
            //Protecting_InBrowser = 1;
            printc("INFO:Protect File Directly SUCCESS\r\n");
        }
    }

    return AHC_TRUE;
}

AHC_BOOL DTV_Uart_DeleteAll(int pItem, AHC_BOOL bIsHover)
{
    UINT32          MaxDcfObj, i;
    UINT32          CurObjIdx;

    if(pItem == ITEMID_DELETE_ALL_VIDEO_YES)
    {
        MaxDcfObj = AHC_GetMappingFileNum(FILE_MOVIE);
    }
    else if(pItem == ITEMID_DELETE_ALL_IMAGE_YES)
    {
        MaxDcfObj = AHC_GetMappingFileNum(FILE_PHOTO);
    }
    else
    {
        return AHC_TRUE;
    }

    if(AHC_SDMMC_BasicCheck()==AHC_FALSE)
        return AHC_TRUE;

    if(MaxDcfObj == 0)
        return AHC_TRUE;

    AHC_UF_SetCurrentIndex(0);

    for(i=0;i<MaxDcfObj;i++)
    {
        AHC_UF_GetCurrentIndex(&CurObjIdx);
        if(AHC_Thumb_IsFileProtect(CurObjIdx))
        {
            printc("WARN:cann`t delete a protect File %d\r\n",CurObjIdx);
            CurObjIdx++;
            AHC_UF_SetCurrentIndex(CurObjIdx);
            continue;
        }

        if(!AHC_UF_FileOperation_ByIdx(CurObjIdx, DCF_FILE_DELETE_ALL_CAM, NULL, NULL))
        {
            //AHC_WMSG_Draw(AHC_TRUE, WMSG_CANNOT_DELETE, 3);
            printc("ERR:Delete File %d fail\r\n",i);
            CurObjIdx++;
            AHC_UF_SetCurrentIndex(CurObjIdx);
        }
        else{
            //DrawProgressBar(i, MaxDcfObj, AHC_FALSE);
            printc("INFO:Delete File %d SUCCESS\r\n",i);
        }
    }

    if(AHC_CheckCurSysMode(AHC_MODE_THUMB_BROWSER))
    {
        if( JPGPB_MODE == GetCurrentOpMode())
        {
            AHC_UF_SetFreeChar(0, DCF_SET_ALLOWED, (UINT8 *) SEARCH_PHOTO);
        }
        else if ( MOVPB_MODE == GetCurrentOpMode() || AUDPB_MODE == GetCurrentOpMode())
        {
            AHC_UF_SetFreeChar(0, DCF_SET_ALLOWED, (UINT8 *) SEARCH_MOVIE);
        }
        else if ( JPGPB_MOVPB_MODE == GetCurrentOpMode())
        {
            AHC_UF_SetFreeChar(0, DCF_SET_ALLOWED, (UINT8 *) SEARCH_PHOTO_MOVIE);
        }
    }
    else if(AHC_CheckCurSysMode(AHC_MODE_PLAYBACK))
    {
        printc("Delete All File Complete\r\n");

        if(GetCurrentOpMode()==MOVPB_MODE)
        {
            if(pItem == ITEMID_DELETE_ALL_VIDEO_YES)
            {
                MovPBTimer_Stop();
                MovPlaybackParamReset();
            }
        }
        else if(GetCurrentOpMode()==JPGPB_MODE)
        {
            if(pItem == ITEMID_DELETE_ALL_IMAGE_YES)
            {
                PhotoPBTimer_Stop();
                JpgPlaybackParamReset();
                //Deleting_InBrowser = 1;
            }
        }
        else if(GetCurrentOpMode()==JPGPB_MOVPB_MODE)
        {
            if(pItem == ITEMID_DELETE_ALL_FILE_YES)
            {
                MovPBTimer_Stop();
                MovPlaybackParamReset();
                PhotoPBTimer_Stop();
                JpgPlaybackParamReset();
                //Deleting_InBrowser = 1;
            }
        }
        else if(GetCurrentOpMode()==AUDPB_MODE)
        {
            AudPBTimer_Stop();
            AudPlaybackParamReset();
            //Deleting_InBrowser = 1;
        }
    }

    //bForceSwitchBrowser =1;
    StateSwitchMode(UI_BROWSER_STATE);

    return AHC_TRUE;
}

AHC_BOOL DTV_Uart_DeleteOne(int pItem, AHC_BOOL bHover)
{
    UINT8   ret = EDIT_FILE_NO_FILE;
    UINT32 CurObjIdx;

    AHC_UF_GetCurrentIndex(&CurObjIdx);
    if(AHC_Thumb_IsFileProtect(CurObjIdx))
    {
        printc("ERR:cann`t delete a protect File %d\r\n",CurObjIdx);
        return AHC_FALSE;
    }

    if (pItem == ITEMID_DELETE_ONE)
    {
        if(AHC_CheckCurSysMode(AHC_MODE_PLAYBACK))
        {
            // in Playback mode
            ret = QuickFileOperation(DCF_FILE_DELETE_ALL_CAM);

            if(ret!=EDIT_FILE_SUCCESS)
            {
                //DrawFileOperationResult(ret);
                printc("ERR:Delete File Directly fail\r\n");
            }
            else
            {
                if(GetCurrentOpMode()==MOVPB_MODE)
                {
                    MovPBTimer_Stop();
                    MovPlaybackParamReset();
                }
                else if(GetCurrentOpMode()==JPGPB_MODE)
                {
                    PhotoPBTimer_Stop();
                    JpgPlaybackParamReset();
                }
                else if(GetCurrentOpMode()==AUDPB_MODE)
                {
                    AudPBTimer_Stop();
                    AudPlaybackParamReset();
                }
                else if(GetCurrentOpMode()==JPGPB_MOVPB_MODE)
                {
                    MovPBTimer_Stop();
                    MovPlaybackParamReset();
                    PhotoPBTimer_Stop();
                    JpgPlaybackParamReset();
                }

                //Deleting_InBrowser = 1;
                printc("in Playback mode,Delete File success\r\n");
            }
        }
        else if(AHC_CheckCurSysMode(AHC_MODE_THUMB_BROWSER))
        {
            // In Browser Mode
            ret = QuickFileOperation(DCF_FILE_DELETE_ALL_CAM);

            if(ret!=EDIT_FILE_SUCCESS)
            {
                //DrawFileOperationResult(ret);
                printc("ERR: browser mode Delete File Directly fail\r\n");
            }
            else
            {
                printc("In Browser Mode,Delete File success\r\n");
            }
        }

        if(ret == EDIT_FILE_SUCCESS){
            //bForceSwitchBrowser =1;
            StateSwitchMode(UI_BROWSER_STATE);
            return AHC_TRUE;
        }
    }
    return AHC_FALSE;
}

AHC_BOOL DTV_Uart_UnProtectAll(int pItem, AHC_BOOL bIsHover)
{
    UINT32          MaxDcfObj, i;

    if(pItem == ITEMID_UNPROTECT_ALL_VIDEO_YES)
    {
        MaxDcfObj = AHC_GetMappingFileNum(FILE_MOVIE);
    }
    else if(pItem == ITEMID_UNPROTECT_ALL_IMAGE_YES)
    {
        MaxDcfObj = AHC_GetMappingFileNum(FILE_PHOTO);
    }
    else
    {
        return AHC_TRUE;
    }

    if(AHC_SDMMC_BasicCheck()==AHC_FALSE)
        return AHC_TRUE;

    if(MaxDcfObj == 0)
        return AHC_TRUE;

    for(i=0;i<MaxDcfObj;i++)
    {
        if(!AHC_UF_FileOperation_ByIdx(i, DCF_FILE_NON_READ_ONLY_ALL_CAM, NULL, NULL))
            return AHC_FALSE;

        if(!AHC_UF_FileOperation_ByIdx(i, DCF_FILE_CHAR_UNLOCK_ALL_CAM, NULL, NULL))
            return AHC_FALSE;

        //DrawProgressBar(i, MaxDcfObj, AHC_FALSE);
        printc("INFO:%s: line%d unProtect %d files\r\n",__func__,__LINE__,i);
    }

    if( AHC_CheckCurSysMode(AHC_MODE_THUMB_BROWSER) )
    {
        if( JPGPB_MODE == GetCurrentOpMode())
        {
            MaxDcfObj = AHC_GetMappingFileNum(FILE_PHOTO);
        }
        else if ( MOVPB_MODE == GetCurrentOpMode() || AUDPB_MODE == GetCurrentOpMode() )
        {
            MaxDcfObj = AHC_GetMappingFileNum(FILE_MOVIE);
        }
        else if ( JPGPB_MOVPB_MODE == GetCurrentOpMode() )
        {
            MaxDcfObj = AHC_GetMappingFileNum(FILE_PHOTO_MOVIE);
        }

        if( ObjSelect > MaxDcfObj - 1)
            ObjSelect = MaxDcfObj - 1;

        AHC_UF_SetCurrentIndex(ObjSelect);

        AHC_Thumb_DrawPage(AHC_TRUE);
    }

#if(LIMIT_MAX_LOCK_FILE_NUM==1)
    if(pItem == ITEMID_UNPROTECT_ALL_VIDEO_YES)
    {
        m_ulLockFileNum  = 0;
        m_ulLockEventNum = 0;
    }
#endif

    return AHC_TRUE;
}

AHC_BOOL DTV_Uart_ProtectAll(int pItem, AHC_BOOL bIsHover)
{
    UINT32 MaxDcfObj, i;

    if(pItem == ITEMID_PROTECT_ALL_VIDEO_YES)
    {
        MaxDcfObj = AHC_GetMappingFileNum(FILE_MOVIE);
    }
    else if(pItem == ITEMID_PROTECT_ALL_IMAGE_YES)
    {
        MaxDcfObj = AHC_GetMappingFileNum(FILE_PHOTO);
    }
    else
    {
        return AHC_TRUE;
    }

    if(AHC_SDMMC_BasicCheck()==AHC_FALSE)
        return AHC_TRUE;

    if(MaxDcfObj == 0)
        return AHC_TRUE;

    for(i=0;i<MaxDcfObj;i++)
    {
        if(!AHC_UF_FileOperation_ByIdx(i, DCF_FILE_READ_ONLY_ALL_CAM, NULL, NULL))
            return AHC_FALSE;

        printc("INFO:%s: line%d Protect %d files\r\n",__func__,__LINE__,i);
    }

    if( AHC_CheckCurSysMode(AHC_MODE_THUMB_BROWSER) )
    {
        if( JPGPB_MODE == GetCurrentOpMode())
        {
            MaxDcfObj = AHC_GetMappingFileNum(FILE_PHOTO);
        }
        else if ( MOVPB_MODE == GetCurrentOpMode() || AUDPB_MODE == GetCurrentOpMode() )
        {
            MaxDcfObj = AHC_GetMappingFileNum(FILE_MOVIE);
        }
        else if ( JPGPB_MOVPB_MODE == GetCurrentOpMode() )
        {
            MaxDcfObj = AHC_GetMappingFileNum(FILE_PHOTO_MOVIE);
        }

        if( ObjSelect > MaxDcfObj - 1)
            ObjSelect = MaxDcfObj - 1;

        AHC_UF_SetCurrentIndex(ObjSelect);

        AHC_Thumb_DrawPage(AHC_TRUE);
    }

    return AHC_TRUE;
}

//data1:0x03  data2:  0x00单个加锁,
                    //0X01单个解锁
                    //0x02全部加锁
                    //0x03全部解锁
                    //0x04单个删除
                    //0x05删除所有
static void DTV_Uart_PhotoViewSetParam(MMP_BYTE *pBuff)
{
    MMP_BYTE data2 = pBuff[3];
    UINT32 CurSysMode;
    UINT8 ret;
    AHC_GetSystemStatus(&CurSysMode);

    CurSysMode >>= 16;
    printc("#########current sys mode is %x#######TODO###\r\n",CurSysMode);

    if(VideoFunc_GetRecordStatus()){
        printc("ERR %s:current is recording, pls stop record first\r\n",__func__);
        return;
    }

    switch(data2)
    {
        case 0:
            DTV_Uart_LockOne(TRUE);
            break;
        case 1:
            DTV_Uart_LockOne(FALSE);
            break;
        case 2:
            DTV_Uart_ProtectAll(ITEMID_PROTECT_ALL_IMAGE_YES,0);
            break;
        case 3:
            DTV_Uart_UnProtectAll(ITEMID_UNPROTECT_ALL_IMAGE_YES,0);
            break;
        case 4:
            DTV_Uart_DeleteOne(ITEMID_DELETE_ONE,0);
            break;
        case 5:
            DTV_Uart_DeleteAll(ITEMID_DELETE_ALL_IMAGE_YES,0);
            break;
        default:
            break;
    }
}

static void DTV_Uart_SwMode(MMP_BYTE *pBuff)
{
    //格式：0xFF 0xAA len(2\2\12) 0xA4 data checksum
    //Data :data1:01录像
    //                   02拍照
    //                   03回放mov
    //                   04回放jpg
    //                   05回放rear mov
    MMP_BYTE data1 = pBuff[2];
    printc("%s:%02x,%02x\r\n",__func__, pBuff[0],pBuff[1]);
    switch(data1)
    {
        case 1:
            printc("enter record mode\r\n");
            AHC_SendAHLMessage(AHLM_GPIO_BUTTON_NOTIFICATION, BUTTON_MODE_REL, (UINT32)data1);
            break;
        case 2:
            printc("enter capture mode\r\n");
            AHC_SendAHLMessage(AHLM_GPIO_BUTTON_NOTIFICATION, BUTTON_MODE_REL, (UINT32)data1);
            break;
        case 3:
            printc("enter pre mode SetCurrentOpMode(MOVPB_MODE)\r\n");//当前是什么模式，就进入对应模式的PB
            m_ubPlaybackRearCam = FALSE;
            //bForceSwitchBrowser = TRUE;
            AHC_UF_SetRearCamPathFlag(m_ubPlaybackRearCam);
            AHC_SendAHLMessage(AHLM_GPIO_BUTTON_NOTIFICATION, BUTTON_MODE_REL, (UINT32)data1);
            break;
        case 4:
            printc("enter pre mode SetCurrentOpMode(JPGPB_MODE)\r\n");
            m_ubPlaybackRearCam = FALSE;
            AHC_UF_SetRearCamPathFlag(m_ubPlaybackRearCam);
            AHC_SendAHLMessage(AHLM_GPIO_BUTTON_NOTIFICATION, BUTTON_MODE_REL, (UINT32)data1);
            break;
        case 5:
            printc("enter next mode SetCurrentOpMode(rear cam MOVPB_MODE)\r\n");
            m_ubPlaybackRearCam = TRUE;
            AHC_UF_SetRearCamPathFlag(m_ubPlaybackRearCam);
            //bForceSwitchBrowser = TRUE;
            AHC_SendAHLMessage(AHLM_GPIO_BUTTON_NOTIFICATION, BUTTON_MODE_REL, 3);
            break;
        default:
            printc("unsupported command!\r\n");
            break;
    }
}

//data1:0x01  data2:0x01 播放
//            data2:0x02 暂停
static void MMPlayHandle(MMP_BYTE data2)
{
    UINT32 uState;
    AHC_GetSystemStatus(&uState);

    switch(uState)
    {
        case STATE_MOV_IDLE :
            if(data2 == 1){
                printc("%s:current is STATE_MOV_IDLE, PLAYING\r\n",__func__);
                DrawStateMovPlaybackUpdate(EVENT_KEY_TELE_STOP);
                UpdateMovPBStatus(MOVIE_STATE_PLAY);
                MediaPlaybackConfig(PLAYBACK_CURRENT);
                MovPlayback_Play();
                DrawStateMovPlaybackUpdate(EVENT_MOVPB_PLAY_START/*EVENT_MOVPB_TOUCH_PLAY_PRESS*/);
                SendCmd2Navi(STATUS_VIDEO_PLAY);
            }
        break;
        case STATE_MOV_EXECUTE :
            if(data2 == 2){
                if(MOV_STATE_FF == GetMovConfig()->iState)
                {
                    printc("%s:current is MOV_STATE_FF, PLAYING\r\n",__func__);
                    UpdateMovPBStatus(MOVIE_STATE_PLAY);
                    MovPlayback_NormalSpeed();
                    DrawStateMovPlaybackUpdate(EVENT_MOVPB_PLAY_START/*EVENT_MOVPB_TOUCH_PLAY_PRESS*/);
                }
                else
                {
                    printc("%s:current is STATE_MOV_EXECUTE, MOVIE_STATE_PAUSE\r\n",__func__);
                    UpdateMovPBStatus(MOVIE_STATE_PAUSE);
                    MovPlayback_Pause();
                    DrawStateMovPlaybackUpdate(EVENT_MOVPB_PAUSE/*EVENT_MOVPB_TOUCH_PAUSE_PRESS*/);
                    SendCmd2Navi(STATUS_VIDEO_VIEW);
                }
            }
        break;
        case STATE_MOV_PAUSE   :
            if(data2 == 1){
                printc("%s:current is STATE_MOV_PAUSE, PLAYING\r\n",__func__);
                UpdateMovPBStatus(MOVIE_STATE_PLAY);
                MovPlayback_NormalSpeed();
                MovPlayback_Resume();
                DrawStateMovPlaybackUpdate(EVENT_MOVPB_PLAY_START/*EVENT_MOVPB_TOUCH_PLAY_PRESS*/);
                SendCmd2Navi(STATUS_VIDEO_PLAY);
            }
        break;

        default                :
            printc("ERR:%s:AHC_GetSystemStatus=%d\r\n",__func__,uState);
        break;
    }

}

static void DTV_Uart_EvtPlayHandle(MMP_BYTE *pBuff)
{
    #if 0
    //操作请求（video播放界面）：
    //格式：0xFF 0xAA len(3) 0xAA data checksum
    //data1:0x01  data2:0x01 播放暂停
    //data1:0x02  data2:时间    //设置进度条
                        //0x00 BKWD 快退
                        //0X01 FRWD 快进
    //data1:0x03  data2:  0x00单个加锁,
                        //0X01单个解锁
                        //0x02全部加锁
                        //0x03全部解锁
                        //0x04单个删除
                        //0x05删除所有
    #endif

    MMP_BYTE data1 = pBuff[2];
    MMP_BYTE data2 = pBuff[3];
    UINT32 uState;

    if((uiGetCurrentState() != UI_BROWSER_STATE) && (uiGetCurrentState() != UI_PLAYBACK_STATE)){
        printc("ERR:%s:uiGetCurrentState isn`t UI_BROWSER_STATE or UI_PLAYBACK_STATE\r\n",__func__);
        return;
    }


    printc("%s:%x,%x\r\n",__func__, pBuff[1],pBuff[2]);
    switch(data1)
    {
        case 1:
            if(uiGetCurrentState() == UI_PLAYBACK_STATE)
                MMPlayHandle(data2);
            break;
        case 2:
            if((MOVPB_MODE == GetCurrentOpMode()) && (uiGetCurrentState() == UI_PLAYBACK_STATE))
            {
                MMP_BYTE data2 = pBuff[3];
                if(data2 == 0x01)//快进
                    AHC_SendAHLMessage(AHLM_GPIO_BUTTON_NOTIFICATION, BUTTON_DOWN_LPRESS, 0);
                else            //快退
                    AHC_SendAHLMessage(AHLM_GPIO_BUTTON_NOTIFICATION, BUTTON_UP_LPRESS, 0);
            }
            else{
                printc("ERR::GetCurrentOpMode isn`t MOVPB_MODE\r\n");
            }
            break;
        case 3:
            if(MOVPB_MODE == GetCurrentOpMode())
            {
                DTV_Uart_PhotoViewSetParam(pBuff);
            }else{
                printc("ERR:Param or mode error\r\n");
            }
            break;
        default:
            printc("unsupported command!\r\n");
            break;
    }
}

static void DTV_Uart_MMPlayHandle(MMP_BYTE *pBuff)
{
    #if 0
    //操作请求（video播放界面）：
    //格式：0xFF 0xAA len(3) 0xAA data checksum
    //data1:0x01  data2:0x01 播放暂停
                  data2:0x02 暂停

    //data1:0x02  data2:时间    //设置进度条
                        //0x00 BKWD 快退-->改为上一个影片
                        //0X01 FRWD 快进-->改为下一个影片播放
    //data1:0x03  data2:  0x01单个加锁或解锁
                        //0x02全部加锁
                        //0x03全部解锁
                        //0x04单个删除
                        //0x05删除所?
    #endif

    MMP_BYTE data1 = pBuff[2];
    MMP_BYTE data2 = pBuff[3];
    UINT32 uState;

    if((uiGetCurrentState() != UI_BROWSER_STATE) && (uiGetCurrentState() != UI_PLAYBACK_STATE)){
        printc("ERR:%s:uiGetCurrentState isn`t UI_BROWSER_STATE or UI_PLAYBACK_STATE\r\n",__func__);
        return;
    }


    printc("%s:%x,%x\r\n",__func__, pBuff[1],pBuff[2]);
    switch(data1)
    {
        case 1:
            if(uiGetCurrentState() == UI_PLAYBACK_STATE)
                MMPlayHandle(data2);
            break;
        case 2:
            if((MOVPB_MODE == GetCurrentOpMode()) && (uiGetCurrentState() == UI_PLAYBACK_STATE))
            {
                MMP_BYTE data2 = pBuff[3];

                MMPlayHandle(2);//pause first
                AHC_OS_SleepMs(1000);
                if(data2 == 0x01)//快进
                    AHC_SendAHLMessage(AHLM_GPIO_BUTTON_NOTIFICATION, BUTTON_DOWN_REL, 0);
                else            //快退
                    AHC_SendAHLMessage(AHLM_GPIO_BUTTON_NOTIFICATION, BUTTON_UP_REL, 0);
            }
            else{
                printc("ERR::GetCurrentOpMode isn`t MOVPB_MODE\r\n");
            }
            break;
        case 3:
            if(MOVPB_MODE == GetCurrentOpMode())
            {
                DTV_Uart_PhotoViewSetParam(pBuff);
            }else{
                printc("ERR:Param or mode error\r\n");
            }
            break;
        default:
            printc("unsupported command!\r\n");
            break;
    }
}

static void DTV_Uart_PhotoViewHandle(MMP_BYTE *pBuff)
{
    #if 0
    //格式：0xFF 0xAA len(3) 0xB0 data checksum
    //data1:0x01  data2:0x01上一张 0x02下一张  （DVR返回为JPG当前信息）
    //data1:0x02  data2:0x01退出 返回到文件夹界面
    //data1:0x03  data2:  0x01单个加锁或解锁
                        //0x02全部加锁
                        //0x03全部解锁
                        //0x04单个删除
                        //0x05删除所有
    #endif

    MMP_BYTE data1 = pBuff[2];

    if((uiGetCurrentState() != UI_BROWSER_STATE) && (uiGetCurrentState() != UI_PLAYBACK_STATE)){
        printc("ERR:%s:uiGetCurrentState isn`t UI_BROWSER_STATE or UI_PLAYBACK_STATE\r\n",__func__);
        return;
    }

    printc("%s:%x,%x\r\n",__func__, pBuff[1],pBuff[2]);
    switch(data1)
    {
        case 1:
            if(JPGPB_MODE == GetCurrentOpMode()||(uiGetCurrentState() == UI_BROWSER_STATE))
            {
                MMP_BYTE data2 = pBuff[3];
                UINT32 fileidx;
                AHC_UF_GetCurrentIndex(&fileidx);
                if(data2 == 1){
                    printc("prev picture fileidx=%d\r\n",fileidx);
                    AHC_SendAHLMessage(AHLM_GPIO_BUTTON_NOTIFICATION, BUTTON_UP_PRESS, 0);
                }
                else if(data2 == 2){
                    printc("Next picture fileidx=%d\r\n",fileidx);
                    AHC_SendAHLMessage(AHLM_GPIO_BUTTON_NOTIFICATION, BUTTON_DOWN_PRESS, 0);
                }
                else {
                    printc("%s param error\r\n",__func__);
                }
            }else{
                printc("ERR:Param or mode error\r\n");
            }
            break;
        case 2:
            {
                MMP_BYTE data2 = pBuff[3];
                UINT32  ObjSelect = 0;
                if(data2 == 1 && uiGetCurrentState() == UI_PLAYBACK_STATE)
                {
                    AHC_UF_GetCurrentIndex(&ObjSelect);
                    AHC_SendAHLMessage(AHLM_GPIO_BUTTON_NOTIFICATION, BUTTON_MODE_REL, 0);
                    printc("INFO:return to browser, current index %d\r\n",ObjSelect);
                }else{
                    printc("ERR:Param or mode error\r\n");
                }
            }
            break;
        case 3:
            if(JPGPB_MODE == GetCurrentOpMode())
            {
                DTV_Uart_PhotoViewSetParam(pBuff);
            }else{
                printc("ERR:Param or mode error\r\n");
            }
            break;
        default:
            printc("unsupported command!\r\n");
            break;
    }
}

void DTV_Uart_repeatPlay(UINT32 index)
{
    UINT32 ustatus;
    UINT32      ObjSelect   = 0;
    UINT32      MaxObjIdx   = 0;
    AHC_BOOL ahc_ret = AHC_TRUE;

    AHC_UF_GetTotalFileCount(&MaxObjIdx);
    if((MaxObjIdx != 0) && (index < MaxObjIdx)){

        //AHC_UF_GetCurrentIndex(&ObjSelect);
        AHC_UF_SetCurrentIndex(index);

    #if 0
        //if(ObjSelect != -1)
        {
            if(!AHC_CheckCurSysMode(AHC_MODE_THUMB_BROWSER))
            {
                printc("[repeatPlay]  no in browser mode \r\n");
            }
            else
            {
                ahc_ret = AHC_SetMode(AHC_MODE_IDLE);
                 SetCurrentOpMode(MOVPB_MODE);
                //ahc_ret = AHC_SetMode(AHC_MODE_PLAYBACK);

                 MovPlaybackParamReset();
                 MovPBFunc_CheckLCDstatus();

                 MediaPlaybackConfig(PLAYBACK_CURRENT);
                 MovPlayback_Play();
                 MovPBFunc_ResetPlaySpeed();
                 //MovPBTimer2_Start(200);
                 printc("[repeatPlay]   3\r\n");
            }
        }
    #else
        {
            if(!BrowserFunc_ThumbnailOption(BROWSER_PLAY))
            {
                ResetCurrentMenu();
                StateSwitchMode(UI_BROWSER_STATE);
                //AHC_WMSG_Draw(AHC_TRUE, WMSG_FILE_ERROR, 3);
            }
        }
#endif

    }
}

static void DTV_Uart_VReplayHandle(MMP_BYTE *pBuff)
{
#if 0
    //操作请求（video列表界面）：
    //格式：0xFF 0xAA len(4\3) 0xA9 data checksum
    //data1:0x01  data2-data3:第N条(<1000)  选中 （直接给第几条 相当于DVR idx）
    //data1:0x02  data2退出播放0进入播放1
#endif
    MMP_BYTE data1 = pBuff[2];
    UINT32 MaxObjIdx;

    if((uiGetCurrentState() != UI_BROWSER_STATE) && (uiGetCurrentState() != UI_PLAYBACK_STATE)){
        printc("ERR:%s:uiGetCurrentState isn`t UI_BROWSER_STATE or UI_PLAYBACK_STATE\r\n",__func__);
        return;
    }

    printc("%s:%x,%x\r\n",__func__, pBuff[1],pBuff[2]);
    switch(data1)
    {
        case 1:
        {
            MMP_BYTE data2 = pBuff[3];
            MMP_BYTE data3 = pBuff[4];

            AHC_UF_GetTotalFileCount(&MaxObjIdx);

            if(MaxObjIdx)
            {
                g_fileIdx = (data2<<8)|data3;
                if(g_fileIdx < MaxObjIdx)
                {
                    printc("set play index %d success\r\n",g_fileIdx);
                }
                else{
                    printc("set play index %d fail,over range0~%d\r\n",g_fileIdx,MaxObjIdx);
                    g_fileIdx = (MaxObjIdx>0)? (MaxObjIdx-1):0;
                }
                AHC_UF_SetCurrentIndex(g_fileIdx);
            }
        }
        break;
        case 2:
        {
            MMP_BYTE data2 = pBuff[3];
            if(data2)
            {
                AHC_UF_GetTotalFileCount(&MaxObjIdx);
                AHC_UF_GetCurrentIndex(&g_fileIdx);
                if(MaxObjIdx){
                    if(g_fileIdx >= MaxObjIdx)
                        g_fileIdx = (MaxObjIdx>0)? (MaxObjIdx-1):0;

                    printc("play index %d\r\n",g_fileIdx);
                    DTV_Uart_repeatPlay(g_fileIdx);
                }
            }
            else
            {
                if(uiGetCurrentState() == UI_PLAYBACK_STATE)
                {
                    AHC_SendAHLMessage(AHLM_GPIO_BUTTON_NOTIFICATION, BUTTON_MODE_REL, 0);
                    printc("TODO:stop playing index %d\r\n",g_fileIdx);
                }
            }
        }
        break;
        default:
            printc("unsupported command!\r\n");
        break;
    }
}

static void DTV_Uart_ReplayModeHandle(MMP_BYTE *pBuff)
{
#if 0
    //回放模式操作请求：
    //格式：0xFF 0xAA  len(3) 0xA7 data checksum
    //data1:0x01  data2:
                    //01 video       video browser thumbnail
                    //02 envent      event browser Thumbnail
                    //03 jeg         jpeg brower thumbnail
#endif

    MMP_BYTE data1 = pBuff[2];
    printc("%s:%x,%x\r\n",__func__, pBuff[1],pBuff[2]);
    switch(data1)
    {
        case 1:
        {
            MMP_BYTE data2 = pBuff[3];
            if(data2 == 1){
                printc("set replay mode as video\r\n");
                SystemSettingConfig()->byPlaybackVideoType = (ITEMID_VIDEO_TYPE_NORMAL - ITEMID_SHOW_VIDEO_TYPE-1);
                AHC_SendAHLMessage(AHLM_GPIO_BUTTON_NOTIFICATION, BUTTON_MODE_REL, 3);
                //bForceSwitchBrowser = AHC_TRUE;
            }
            else if(data2 == 2){
                printc("TODO:set replay mode as event\r\n");
                SystemSettingConfig()->byPlaybackVideoType = (ITEMID_VIDEO_TYPE_PARKING - ITEMID_SHOW_VIDEO_TYPE-1);
                AHC_SendAHLMessage(AHLM_GPIO_BUTTON_NOTIFICATION, BUTTON_MODE_REL, 3);
                //bForceSwitchBrowser = AHC_TRUE;
            }
            else if(data2 == 3){
                printc("set replay mode as jepg\r\n");
                AHC_SendAHLMessage(AHLM_GPIO_BUTTON_NOTIFICATION, BUTTON_MODE_REL, 4);
            }
        }
        break;
        default:
            printc("unsupported command!\r\n");
        break;
    }
}

static void DTV_Uart_RecModeHandle(MMP_BYTE *pBuff)
{
    #if 0
    //data1:0x01  data2:01录影 02取图 03加锁
    //data1:0x02  data2:0退菜单1进菜单

    //data1:0x03  data2:分辨率 data3:停车侦测
                //data4:录音 data5:重力感应
                //data6:开机自动录像

    //data1:0x04  恢复出厂设置
    //data1:0x05  格式化SD卡
    //data1:0x06  返回版本号
    //data1:0x07  sw to sensor0
    //data1:0x08  sw to sensor1
    //data1:0x09  Set contrast
    //data1:0x0a  Set brightness
    //data1:0x0b  Set saturation

    { "setcontrast",            "",      " Set contrast",                   UartCmd_SetContrast },
    { "setbrightness",          "",      " Set brightness",                 UartCmd_SetBrightness },
    { "setsaturation",          "",      " Set saturation",                 UartCmd_SetSaturation },
    { "set1603reg",             "",      " Set bit1603 reg",                UartCmd_SetBit1603 },

    #endif
    MMP_BYTE data1 = pBuff[2];
    MMP_BYTE data2 = pBuff[3];
    MMP_ERR     err = MMP_ERR_NONE;
    MMP_USHORT usData;

    printc("%s:%x,%x\r\n",__func__, pBuff[1],pBuff[2]);
    switch(data1)
    {
        case 1:
        {
            if(data2 == 1){
                printc("%s:EVENT_VIDEO_KEY_RECORD on\r\n",__func__);
                SetKeyPadEvent(KEY_REL_REC);
            }
            else if(data2 == 0){
                printc("%s:EVENT_VIDEO_KEY_RECORD off\r\n",__func__);
                SetKeyPadEvent(KEY_REL_REC);
            }
            else if(data2 == 2){
                printc("%s:capture photo\r\n",__func__);
                AHC_SendAHLMessage(AHLM_GPIO_BUTTON_NOTIFICATION, BUTTON_REC_LPRESS, 0);
            }
            else if(data2 == 3){
                printc("sos lock file\r\n");
                AHC_SendAHLMessage(AHLM_GPIO_BUTTON_NOTIFICATION, BUTTON_SOS_REL, 0);
            }
        }
        break;
        case 2:
            printc("%s:unsupported\r\n",__func__);
            break;
        case 3:
            DTV_Uart_SetParam(pBuff);
            break;
        case 4:
            printc("%s:reset setting\r\n",__func__);
            AHC_SendAHLMessage(AHLM_UI_NOTIFICATION, EVENT_TV_RESET_SETTING, (UINT32)data1);
            break;
        case 5:
        {
            MMP_UBYTE pAck = NAVIACK_SD_FORMAT_FAIL;
            printc("%s:format sd...\r\n",__func__);

            if(!VideoFunc_GetRecordStatus())
            {
                printc("doing format media!\r\n");

                if (AHC_FormatStorageMedia(AHC_MEDIA_MMC) &&
                    AHC_MountStorageMedia(AHC_MEDIA_MMC)  &&
                    AHC_RemountDevices(MenuSettingConfig()->uiMediaSelect))
                {
                    pAck = NAVIACK_SD_FORMAT_SUCC;
                }
                else
                {
                    pAck = NAVIACK_SD_FORMAT_FAIL;
                }
            }
            else
            {
                pAck = NAVIACK_SD_FORMAT_FAIL;
            }

            DTV_Uart_MergePack(&pAck);
            //AHC_SendAHLMessage(AHLM_UI_NOTIFICATION, EVENT_TV_FORMAT_MEDIA, (UINT32)data1);
            break;
        }
        case 6:
        {
            unsigned short  mj, mm, mi, mb, mt;
            char            *mp;
            AHC_GetFwVersion(&mj, &mm, &mi, &mb, &mt, &mp);
            printc("%s:get fw version...\r\n",__func__);
            SendCmd2Navi("@version-0x%02X-%02X-%04X-%d",mj,mm,mi,511);//RECORD_VERSION
            break;
        }
        case 7:
        {
            printc("%s:preview sensor0\r\n",__func__);
            MMPF_Display_SetCCIRActivePipeSnr(0);
            break;
        }
        case 8:
        {
            printc("%s:preview sensor1\r\n",__func__);
            MMPF_Display_SetCCIRActivePipeSnr(1);
            break;
        }
        case 9: //data1:0x09  Set contrast
        {
            if(data2 < 100 && data2 > 1){
                usData = 0x80-50+data2;

                err = MMPS_Sensor_SetSensorReg(SCD_SENSOR, 0x11, usData);
                if(err == MMP_ERR_NONE)
                    printc("%s:set contrast 0x%02x success\r\n",__func__,usData);
                else
                    printc("%s:set contrast 0x%02x fail\r\n",__func__,usData);
            }
            MMPS_Sensor_GetSensorReg(SCD_SENSOR, 0x11, &usData);
            data2 = usData+50-0x80;
            if(data2 <= 100 && data2 >= 1)
                SendCmd2Navi("@contrast=%d\r",data2);
            break;
        }
        case 0x0a:  //data1:0x0a  Set brightness
        {
            if(data2 < 100 && data2 > 1){
                usData = 0x80-50+data2;

                err = MMPS_Sensor_SetSensorReg(SCD_SENSOR, 0x10, usData);
                if(err == MMP_ERR_NONE)
                    printc("%s:set brightness 0x%02x success\r\n",__func__,usData);
                else
                    printc("%s:set brightness 0x%02x fail\r\n",__func__,usData);
            }
            MMPS_Sensor_GetSensorReg(SCD_SENSOR, 0x10, &usData);
            data2 = usData+50-0x80;
            if(data2 <= 100 && data2 >= 1)
                SendCmd2Navi("@brightness=%d\r",data2);

            break;
        }
        case 0x0b://data1:0x0b  Set saturation
        {
            if(data2 < 100 && data2 > 1){
                //saturation default is 0x40=64
                usData = (64-50+data2)|0x80;
                MMPS_Sensor_SetSensorReg(SCD_SENSOR, 0x17, usData&0XFF);
                err = MMPS_Sensor_SetSensorReg(SCD_SENSOR, 0x18, usData&0XFF);

                if(err == MMP_ERR_NONE)
                    printc("%s:set saturation 0x%02x success\r\n",__func__,usData);
                else
                    printc("%s:set saturation 0x%02x fail\r\n",__func__,usData);
            }
            MMPS_Sensor_GetSensorReg(SCD_SENSOR, 0x17, &usData);
            data2 = (usData&0x7f)+50-64;
            if(data2 <= 100 && data2 >= 1)
                SendCmd2Navi("@saturation=%d\r",data2);

            break;
        }
        default:
            printc("unsupported command!\r\n");
            break;
    }
}

static void DTV_Uart_SetKEY(MMP_BYTE *pBuff)
{
    MMP_UBYTE i = 0;

    printc("DTV_Uart_SetKEY  \r\n");
    for( i=0; i<gNumOfCMDIDKey ; i++ )
    {
        if(CmdKey[i].iCmdId == pBuff[3])
        {
            SetKeyPadEvent(CmdKey[i].ulkeyEvent);
            printc("%s \r\n",CmdKey[i].ubkeyname);
        }
    }
}

static void DTV_Uart_SetTime(MMP_BYTE *pBuff)
{
    if(pBuff[2]<24)
        uCurHour = pBuff[2];
    if(pBuff[3]<60)
        uCurMinute = pBuff[3];
    if(pBuff[4]<60)
        uCurSecond = pBuff[4];
}

static void DTV_Uart_SetDate(MMP_BYTE *pBuff)
{
    UINT16 uwYear,uwMonth,uwDay,uwDayInWeek,uwHour,uwMinute,uwSecond;
    UINT16 uCurYear,uCurMonth,uCurDay;
    UINT16 uCurHour,uCurMinute,uCurSecond;
    UINT8 ubAmOrPm, b_12FormatEn;
    static AHC_BOOL bWflag = AHC_FALSE;

    AHC_SetParam(PARAM_ID_USE_RTC,AHC_TRUE);
    AHC_GetClock(&uwYear,&uwMonth,&uwDay,&uwDayInWeek,&uwHour,&uwMinute,&uwSecond,&ubAmOrPm,&b_12FormatEn);

    printc("INFO get TIME:%d-%d-%d:%d-%d-%d\r\n",uwYear,uwMonth,uwDay,uwHour,uwMinute,uwSecond);

    if(pBuff[2]<99)
        uCurYear = 2000 + pBuff[2];
    if(pBuff[3]<12)
        uCurMonth = pBuff[3];
    if(pBuff[4]<32)
        uCurDay = pBuff[4];

    if(pBuff[2]<24)
        uCurHour = pBuff[5];
    if(pBuff[3]<60)
        uCurMinute = pBuff[6];
    if(pBuff[4]<60)
        uCurSecond = pBuff[7];

    if((uwYear == uCurYear)&&(uwMonth == uCurMonth)&&(uwDay == uCurDay)&&
        (uwHour == uCurHour)&&(uwMinute == uCurMinute)&&(uwSecond == uCurSecond))
        return ;

    printc("INFO NEW TIME:%d-%d-%d:%d-%d-%d\r\n",uCurYear,uCurMonth,uCurDay,uCurHour,uCurMinute,uCurSecond);

    //if(!bWflag)
    {
        AHC_SetClock(uCurYear, uCurMonth, uCurDay, uwDayInWeek, uCurHour, uCurMinute, uwSecond,ubAmOrPm, b_12FormatEn);
        bWflag = AHC_TRUE;
    }
    AHC_GetClock(&uwYear,&uwMonth,&uwDay,&uwDayInWeek,&uwHour,&uwMinute,&uwSecond,&ubAmOrPm,&b_12FormatEn);
}

//------------------------------------------------------------------------------
//  Function    : DTV_Uart_ParsePack
//  Description : Parse UART packet from buffer.
//------------------------------------------------------------------------------
/** @brief

@param[in] pBuff a character pointer of packets buffer.
@param[in] iBuff_sz buffer size.
@param[in] psPack a pointer of packet which will filled by function.
@return 1 (true) - if parsed successfully or 0 (false) - if fail.
*/

static MMP_LONG DTV_Uart_ParsePack(MMP_BYTE *pBuff )
{
    switch(pBuff[1]) //Command ID
    {
    case NAVICMD_SW_MODE :
        DTV_Uart_SwMode(pBuff);
        break;

    case NAVICMD_REC_MODE_OPREQ :
        DTV_Uart_RecModeHandle(pBuff);
        break;

    case NAVICMD_REP_MODE_OPREQ :
        DTV_Uart_ReplayModeHandle(pBuff);
        break;

    case NAVICMD_MOV_LIST_OPREQ :
    case NAVICMD_EVENT_REQ :
        DTV_Uart_VReplayHandle(pBuff);
        break;

    case NAVICMD_MOV_REP_OPREQ :
        DTV_Uart_MMPlayHandle(pBuff);
        break;

    case NAVICMD_EVENT_REP_REQ :
        DTV_Uart_EvtPlayHandle(pBuff);
        break;

    case NAVICMD_PHOTO_VIEW :
        DTV_Uart_PhotoViewHandle(pBuff);
        break;
    //case DTVCMD_TOUCH_PRESS:
    //    DTV_Uart_TouchPress(pBuff);
    //    break;

    //case DTVCMD_TOUCH_RELEASE:
    //    DTV_Uart_TouchRelease(pBuff);
    //    break;

    //case DTVCMD_KEY:
    //    DTV_Uart_SetKEY(pBuff);
    //    break;
    case NAVICMD_SET_TIME:
    case NAVICMD_SET_DATE:
        {
        MMP_UBYTE pAck=NAVIACK_CARD_STATUS;
        DTV_Uart_SetDate(pBuff);
        DTV_Uart_MergePack(&pAck);
        }
        break;
    default:
         printc("pBuff[2] %d\r\n",pBuff[1]);
          break;
    }

    SendCmd2Navi("@cmd=%d\r",pBuff[1]);//(CMD_ACK);//send ack to navi
    return 1;
}
static MMP_ERR DTV_Uart_HeartBeat(void)
{
    MMP_BYTE    pBuff[6] = {HEAD1_S680, HEAD2_S680, 0x2/*length*/, NAVIACK_HEART_BEAT, 0x01, 0};
    MMP_UBYTE   ublength = 6; // 2 + 1 + length + 1
    MMP_ERR     err      = MMP_ERR_NONE;

#if defined(ACK_USE_S680)&&(ACK_USE_S680)
    pBuff[ublength-1] = DTV_Uart_CheckSum(&pBuff[LEN_OFFSET_S680]);

    err = MMPF_Uart_Write(DTV_UART_NUM, pBuff, ublength);

    if (err)
        printc(FG_RED("%s: error 0x%x")"\n", __func__, err);
#else
    printc(FG_RED("%s: TODO")"\n", __func__);
#endif
    return err;
}

static MMP_ERR DTV_Uart_CardStatus(void)
{
    MMP_BYTE    pBuff[6] = {HEAD1_S680, HEAD2_S680, 0x2/*length*/, NAVIACK_CARD_STATUS, 0};
    MMP_UBYTE   ublength = 6; // 2 + 1 + length + 1
    MMP_ERR     err      = MMP_ERR_NONE;

#if defined(ACK_USE_S680)&& (ACK_USE_S680)
// jeff.li TBD ++++++++++
    if(!AHC_SDMMC_GetState())
        pBuff[DATA_OFFSET_S680] = 0x02; // no card

    else if(!AHC_SDMMC_IsSD1MountDCF())
        pBuff[DATA_OFFSET_S680] = 0x01; // card error
// jeff.li TBD ----------

    pBuff[ublength-1] = DTV_Uart_CheckSum(&pBuff[LEN_OFFSET_S680]);

    err = MMPF_Uart_Write(DTV_UART_NUM, pBuff, ublength);

    if (err)
        printc(FG_RED("%s: error 0x%x")"\n", __func__, err);
#else
    if(AHC_SDMMC_GetState() == SDMMC_OUT){
        SendCmd2Navi(STATUS_CARD_OUT);
        printc(FG_RED("%s: SDMMC_OUT ")"\n", __func__);
    }
    else{
        SendCmd2Navi(STATUS_CARD_IN);
        printc(FG_RED("%s: SDMMC_IN ")"\n", __func__);
    }
#endif

    return err;
}

static MMP_ERR DTV_Uart_PowerOnMsg(void)
{
    //开机信息：主要有DVR版本信息、DVR开机状态
    //格式：0xFF 0xAA len(7) 0x03 data checksum
    MMP_BYTE    pBuff[11] = {HEAD1_S680, HEAD2_S680, 0x7/*length*/, NAVIACK_PWRON_MSG, 0};
    MMP_UBYTE   ublength = 11; // 2 + 1 + length + 1
    MMP_ERR     err      = MMP_ERR_NONE;

#if defined(ACK_USE_S680)&& (ACK_USE_S680)
    //Data :录影状态1BYTE   不在录影 0， 录影1
    if(uiGetCurrentState() != UI_VIDEO_STATE || !VideoFunc_GetRecordStatus())
        pBuff[DATA_OFFSET_S680] = 0;
    else
        pBuff[DATA_OFFSET_S680] = 1;

    //加锁状态1BYTE     未加锁 0， 已加锁1
    if(VideoFunc_LockFileEnabled())
        pBuff[DATA_OFFSET_S680+1] = 1;
    else
        pBuff[DATA_OFFSET_S680+1] = 0;

    //版本号4BYTE    年月日V
    {
        printc(FG_RED("%s: get version TBD")"\n", __func__);
    }

    pBuff[ublength-1] = DTV_Uart_CheckSum(&pBuff[LEN_OFFSET_S680]);

    err = MMPF_Uart_Write(DTV_UART_NUM, pBuff, ublength);

    if (err)
        printc(FG_RED("%s: error 0x%x")"\n", __func__, err);
#else
    printc(FG_RED("%s: TODO")"\n", __func__);
#endif
    return err;
}

static MMP_ERR DTV_Uart_SwMode_ACK(void)
{
    MMP_BYTE    pBuff[16] = {HEAD1_S680, HEAD2_S680, 12/*length*/, NAVIACK_SW_MODE, 0};
    MMP_UBYTE   ublength = 16; // 2 + 1 + length + 1
    MMP_ERR     err      = MMP_ERR_NONE;

#if defined(ACK_USE_S680)&& (ACK_USE_S680)
    switch(uiGetCurrentState())
    {
        case UI_VIDEO_STATE:
            pBuff[DATA_OFFSET_S680] = 0x01;
            break;
        case UI_CAMERA_STATE:
            pBuff[DATA_OFFSET_S680] = 0x02;
            break;
        case UI_BROWSER_STATE: // TBD
            pBuff[DATA_OFFSET_S680] = 0x03;
            break;
    }

    //data2-3:video data4-5:envent  data6-7:jpg  data8-9:卡内存已用 data10-11:卡内存未用（11BYTE）
    //例：数据 15.32G  发送1532 =5FC = 0x05 0xFC
    {
        printc(FG_RED("%s: get card msg TBD")"\n", __func__);
    }

    if(pBuff[DATA_OFFSET_S680] == 0x01 || pBuff[DATA_OFFSET_S680] == 0x02)
    {
        pBuff[LEN_OFFSET_S680] = 2;
        ublength = 6;
    }

    pBuff[ublength-1] = DTV_Uart_CheckSum(&pBuff[LEN_OFFSET_S680]);

    err = MMPF_Uart_Write(DTV_UART_NUM, pBuff, ublength);

    if (err)
        printc(FG_RED("%s: error 0x%x")"\n", __func__, err);
#else
    printc(FG_RED("%s: TODO")"\n", __func__);
#endif
    return err;
}

static MMP_ERR DTV_Uart_RecModeAckHandle(MMP_UBYTE *pParam)
{
    MMP_BYTE    pBuff[10] = {HEAD1_S680, HEAD2_S680, 0x6/*length*/, NAVIACK_REC_MODE_OPREQ, 0};
    MMP_UBYTE   ublength = 10; // 2 + 1 + length + 1
    MMP_ERR     err      = MMP_ERR_NONE;

#if defined(ACK_USE_S680)&& (ACK_USE_S680)
    pBuff[DATA_OFFSET_S680] = pParam[0];

    switch(pParam[0])
    {
        //data1:0x01    data2:录影状态0不在录影, 1录影 data3:加锁状态0不加锁, 1加锁
        case 0x01:
            pBuff[DATA_OFFSET_S680+1] = VideoFunc_GetRecordStatus()    ? 1 : 0;
            pBuff[DATA_OFFSET_S680+2] = VideoFunc_LockFileEnabled() ? 1 : 0;
            pBuff[LEN_OFFSET_S680] = 4;
            break;
        //data1:0x02    data2:菜单状态0退菜单,   1进菜单
        case 0x02:
            pBuff[DATA_OFFSET_S680+1] = uiGetCurrentState() == UI_VIDEO_MENU_STATE ? 1 : 0;
            pBuff[LEN_OFFSET_S680] = 3;
            break;
        //data1:0x03    data2:分辨率 data3:停车侦测 data4:录音 data5:重力感应
        case 0x03:
            //分辨率（1080P、720P60、720P30）=>发送依次0、1、2代替
            pBuff[DATA_OFFSET_S680+1] = DTV_Uart_GetParam(PARAM_RESOLUTION);
            //停车侦测（关、开）=>发送依次0、1代替
            pBuff[DATA_OFFSET_S680+2] = DTV_Uart_GetParam(PARAM_PARKING_MODE);
            //录音（关、开）=>发送依次0、1代替
            pBuff[DATA_OFFSET_S680+3] = DTV_Uart_GetParam(PARAM_AUDIO_RECORD);
            //重力感应（低、中、高、关闭）=>发送依次0、1、2、3代替
            pBuff[DATA_OFFSET_S680+4] = DTV_Uart_GetParam(PARAM_GSENSOR_SENSITIVITY);
            pBuff[LEN_OFFSET_S680] = 6;
            break;
        //data1:0x04   恢复出厂设置
        case 0x04:
            pBuff[LEN_OFFSET_S680] = 2;
            break;
        //data1:0x05  date2: 1格式化SD卡开始，2格式化卡结束
        case 0x05:
            pBuff[DATA_OFFSET_S680+1] = pParam[1]; // jeff.li TBD
            pBuff[LEN_OFFSET_S680] = 3;
            break;
    }

    ublength = pBuff[LEN_OFFSET_S680] + 4;

    pBuff[ublength-1] = DTV_Uart_CheckSum(&pBuff[LEN_OFFSET_S680]);

    err = MMPF_Uart_Write(DTV_UART_NUM, pBuff, ublength);

    if (err)
        printc(FG_RED("%s: error 0x%x")"\n", __func__, err);
#else
    printc(FG_RED("%s: TODO")"\n", __func__);
#endif
    return err;
}

static MMP_ERR DTV_Uart_CapModeAckHandle(MMP_UBYTE *pParam)
{
    MMP_BYTE    pBuff[7] = {HEAD1_S680, HEAD2_S680, 0x3/*length*/, NAVIACK_CAP_MODE_OPREQ, 0};
    MMP_UBYTE   ublength = 7; // 2 + 1 + length + 1
    MMP_ERR     err      = MMP_ERR_NONE;

#if defined(ACK_USE_S680)&& (ACK_USE_S680)
    pBuff[DATA_OFFSET_S680] = pParam[0];

    switch(pParam[0])
    {
        //data1:0x01  data2:01拍照OK
        case 0x01:
            pBuff[DATA_OFFSET_S680+1] = 0x01;
            //pBuff[LEN_OFFSET_S680] = 3;
            break;
        //data1:0x02    data2:菜单状态0退菜单,   1进菜单
        case 0x02:
            pBuff[DATA_OFFSET_S680+1] = uiGetCurrentState() == UI_CAMERA_MENU_STATE ? 1 : 0;
            //pBuff[LEN_OFFSET_S680] = 3;
            break;
        //data1:0x03  data2:分辨率
        case 0x03:
            pBuff[DATA_OFFSET_S680+1] = 0;// TBD
            //pBuff[LEN_OFFSET_S680] = 3;
            break;
    }

    //ublength = pBuff[LEN_OFFSET_S680] + 4;

    pBuff[ublength-1] = DTV_Uart_CheckSum(&pBuff[LEN_OFFSET_S680]);

    err = MMPF_Uart_Write(DTV_UART_NUM, pBuff, ublength);

    if (err)
        printc(FG_RED("%s: error 0x%x")"\n", __func__, err);
#else
    printc(FG_RED("%s: TODO")"\n", __func__);
#endif
    return err;
}

static MMP_ERR DTV_Uart_PBModeAckHandle(MMP_UBYTE *pParam)
{
    MMP_BYTE    pBuff[7] = {HEAD1_S680, HEAD2_S680, 0x3/*length*/, NAVIACK_PB_MODE_OPREQ, 0};
    MMP_UBYTE   ublength = 7; // 2 + 1 + length + 1
    MMP_ERR     err      = MMP_ERR_NONE;

#if defined(ACK_USE_S680)&& (ACK_USE_S680)
    pBuff[DATA_OFFSET_S680] = 0x01;

    printc(FG_RED("%s TBD\n"), __func__);


    //ublength = pBuff[LEN_OFFSET_S680] + 4;

    pBuff[ublength-1] = DTV_Uart_CheckSum(&pBuff[LEN_OFFSET_S680]);

    err = MMPF_Uart_Write(DTV_UART_NUM, pBuff, ublength);

    if (err)
        printc(FG_RED("%s: error 0x%x")"\n", __func__, err);
#else
    printc(FG_RED("%s: TODO")"\n", __func__);
#endif
    return err;
}

static MMP_ERR DTV_Uart_VideoListHandle(MMP_UBYTE *pParam)
{
    MMP_BYTE    pBuff[7] = {HEAD1_S680, HEAD2_S680, 0x3/*length*/, 0, 0};
    MMP_UBYTE   ublength = 7; // 2 + 1 + length + 1
    MMP_ERR     err      = MMP_ERR_NONE;

#if defined(ACK_USE_S680)&& (ACK_USE_S680)
    pBuff[DATA_TYPE_OFFSET_S680] = pParam[0];

    printc(FG_RED("%s TBD\n"), __func__);


    //ublength = pBuff[LEN_OFFSET_S680] + 4;

    pBuff[ublength-1] = DTV_Uart_CheckSum(&pBuff[LEN_OFFSET_S680]);

    err = MMPF_Uart_Write(DTV_UART_NUM, pBuff, ublength);

    if (err)
        printc(FG_RED("%s: error 0x%x")"\n", __func__, err);
#else
    printc(FG_RED("%s: TODO")"\n", __func__);
#endif
    return err;
}

static MMP_ERR DTV_Uart_VReplayAckHandle(MMP_UBYTE *pParam)
{
    MMP_BYTE    pBuff[7] = {HEAD1_S680, HEAD2_S680, 0x3/*length*/, 0, 0};
    MMP_UBYTE   ublength = 7; // 2 + 1 + length + 1
    MMP_ERR     err      = MMP_ERR_NONE;
    MMP_BYTE    data1    = pParam[1];

#if defined(ACK_USE_S680)&& (ACK_USE_S680)
    pBuff[DATA_TYPE_OFFSET_S680] = pParam[0];
    pBuff[DATA_OFFSET_S680] = data1;

    switch(data1)
    {
        case 0x01:
            pBuff[DATA_OFFSET_S680+1] = (g_fileIdx&0xFF00)>>8;
            pBuff[DATA_OFFSET_S680+2] = g_fileIdx&0x00FF;
            pBuff[DATA_OFFSET_S680+3] = 0;//TBD
            printc(FG_RED("%s TBD\n"), __func__);
            break;

        case 0x02:
            pBuff[DATA_OFFSET_S680+1] = uiGetCurrentState() == UI_PLAYBACK_STATE ? 1 : 0;
            pBuff[LEN_OFFSET_S680] = 3;
            break;

    }

    ublength = pBuff[LEN_OFFSET_S680] + 4;

    pBuff[ublength-1] = DTV_Uart_CheckSum(&pBuff[LEN_OFFSET_S680]);

    err = MMPF_Uart_Write(DTV_UART_NUM, pBuff, ublength);

    if (err)
        printc(FG_RED("%s: error 0x%x")"\n", __func__, err);
#else
    printc(FG_RED("%s: TODO")"\n", __func__);
#endif
    return err;
}

static MMP_ERR DTV_Uart_MMPlayaAckHandle(MMP_UBYTE *pParam)
{
    MMP_BYTE    pBuff[7] = {HEAD1_S680, HEAD2_S680, 0x3/*length*/, 0, 0};
    MMP_UBYTE   ublength = 7; // 2 + 1 + length + 1
    MMP_ERR     err      = MMP_ERR_NONE;
    MMP_BYTE    data1    = pParam[1];

#if defined(ACK_USE_S680)&& (ACK_USE_S680)
    pBuff[DATA_TYPE_OFFSET_S680] = pParam[0];
    pBuff[DATA_OFFSET_S680] = data1;

    switch(data1)
    {
        case 0x01:
            pBuff[DATA_OFFSET_S680+1] = GetMovConfig()->iState == MOV_STATE_PLAY ? 0x01 : 0x02;
            break;
        case 0x02:
            {
                UINT32 ultime;
                GetMovCurrPlayTime(&ultime);
                pBuff[DATA_OFFSET_S680+1] = ultime&0xFF; // TBD
                printc(FG_RED("%s TBD\n"), __func__);
            }
            break;
        case 0x03:
            pBuff[DATA_OFFSET_S680+1] = pParam[2];
            break;
    }

    //ublength = pBuff[LEN_OFFSET_S680] + 4;

    pBuff[ublength-1] = DTV_Uart_CheckSum(&pBuff[LEN_OFFSET_S680]);

    err = MMPF_Uart_Write(DTV_UART_NUM, pBuff, ublength);

    if (err)
        printc(FG_RED("%s: error 0x%x")"\n", __func__, err);
#else
    printc(FG_RED("%s: TODO")"\n", __func__);
#endif
    return err;
}

static MMP_ERR DTV_Uart_WarningMsgHandle(MMP_UBYTE *pParam)
{
    MMP_BYTE    pBuff[6] = {HEAD1_S680, HEAD2_S680, 0x2/*length*/, NAVIACK_WARNING_MSG, 0};
    MMP_UBYTE   ublength = 6; // 2 + 1 + length + 1
    MMP_ERR     err      = MMP_ERR_NONE;

    pBuff[DATA_OFFSET_S680] = pParam[0];

    //ublength = pBuff[LEN_OFFSET_S680] + 4;

    pBuff[ublength-1] = DTV_Uart_CheckSum(&pBuff[LEN_OFFSET_S680]);

    err = MMPF_Uart_Write(DTV_UART_NUM, pBuff, ublength);

    if (err)
        printc(FG_RED("%s: error 0x%x")"\n", __func__, err);

    return err;
}

//------------------------------------------------------------------------------
//  Function    : DTV_Uart_MergePack
//  Description : Merge UART packet to buffer.
//------------------------------------------------------------------------------
/** @brief

@param[in] pBuff a character pointer of packets buffer.
@param[in] iBuff_sz buffer size.
@param[in] psPack a pointer of packet which will filled by function.
@return 1 (true) - if parsed successfully or 0 (false) - if fail.
*/

static MMP_LONG DTV_Uart_MergePack(MMP_UBYTE *pBuff)
{
    switch(pBuff[0]) //Command ID
    {
    case NAVIACK_HEART_BEAT :
        DTV_Uart_HeartBeat();
        break;

    case NAVIACK_CARD_STATUS:
        DTV_Uart_CardStatus();
        break;

    case NAVIACK_PWRON_MSG:
        DTV_Uart_PowerOnMsg();
        break;

    case NAVIACK_SW_MODE:
        DTV_Uart_SwMode_ACK();
        break;

    case NAVIACK_REC_MODE_OPREQ:
        DTV_Uart_RecModeAckHandle(&pBuff[1]);
        break;

    case NAVIACK_CAP_MODE_OPREQ:
        DTV_Uart_CapModeAckHandle(&pBuff[1]);
        break;

    case NAVIACK_PB_MODE_OPREQ:
        DTV_Uart_PBModeAckHandle(&pBuff[1]);
        break;

    case NAVIACK_MOV_LIST_MSG:
    case NAVIACK_EVENT_LIST_MSG:
        DTV_Uart_VideoListHandle(&pBuff[1]);
        break;

    case NAVIACK_MOV_LIST_OPREQ:
    case NAVIACK_EVENT_REQ:
        DTV_Uart_VReplayAckHandle(pBuff);
        break;

    case NAVIACK_MOV_PB_OPREQ:
    case NAVIACK_EVENT_REP_REQ:
    case NAVIACK_PHOTO_VIEW:
        DTV_Uart_MMPlayaAckHandle(pBuff);
        break;

    case NAVIACK_PHOTO_MSG:
        break;

    case NAVIACK_WARNING_MSG:
        break;

    case NAVIACK_FILE_COUNT:
        SendCmd2Navi(STATUS_FILE_COUNT);
        SendCmd2Navi("%d\r",6);
        break;

    case NAVIACK_FILE_UNLOCK:
        SendCmd2Navi(STATUS_RECORD_UNLOCK);
        break;

    case NAVIACK_FILE_UNLOCK_END:
        SendCmd2Navi(STATUS_RECORD_UNLOCK_END);
        break;

    case NAVIACK_FILE_LOCK_END:
        SendCmd2Navi(STATUS_RECORD_LOCK_END);
        break;

    case NAVIACK_FILE_RECORD_RESTART:
        SendCmd2Navi(STATUS_RECORD_RESTART);
        break;

    case NAVIACK_FILE_RECORD_STOP:
        SendCmd2Navi(STATUS_RECORD_OFF);
        break;

    case NAVIACK_SD_FORMAT_FAIL:
        SendCmd2Navi(STATUS_FORAMT_FAIL);
        break;
    case NAVIACK_SD_FORMAT_SUCC:
        SendCmd2Navi(STATUS_FORAMT_SUCC);
        break;
    case NAVIACK_SD_FORMAT_NOCARD:
        SendCmd2Navi(STAUTS_FORMAT_NO_CARD);
        break;

    case NAVIACK_FILE_STATUS:
        {
            AHC_BOOL bReadOnly;
            UINT8   FileType;
            UINT32  uwFocusIndex,uiFileCount;
            INT8    FilePathName[MAX_FULL_FILENAME_SIZE];
            INT8    fileType[8]={0};

            if( m_ubPlaybackRearCam == AHC_TRUE && AHC_MULTI_TRACK_EN == 0 ){
                AHC_UF_SetRearCamPathFlag(AHC_TRUE);
            }
            AHC_UF_GetTotalFileCount(&uiFileCount);
            AHC_UF_GetCurrentIndex(&uwFocusIndex);
            AHC_UF_GetFilePathNamebyIndex(uwFocusIndex, FilePathName);
            if((uiFileCount > 0) && (uwFocusIndex < uiFileCount)){
                AHC_UF_IsReadOnlybyIndex(uwFocusIndex, &bReadOnly);
                AHC_UF_GetFileTypebyIndex(uwFocusIndex, &FileType);

                if(FileType == 3)
                    STRCAT(fileType,"avi");
                else
                    STRCAT(fileType,"jpg");

                SendCmd2Navi("$@file-%s,%d/%d,%d,filename:%s\r",fileType,uwFocusIndex+1,uiFileCount,bReadOnly,FilePathName);// //@file-avi,5/88,256,filename:xxx
                //SendCmd2Navi("@@file-%s,%d/%d,%d\r",fileType,uwFocusIndex+1,uiFileCount,bReadOnly);// //@file-avi,5/88,256,filename:xxx
                //SendCmd2Navi("@filename:%s\r",FilePathName);// //@file-avi,5/88,256,filename:xxx
            }
            else
            {
                printc("current focus index error[0] %d\r\n",uwFocusIndex);
            }
            if( m_ubPlaybackRearCam == AHC_TRUE && AHC_MULTI_TRACK_EN == 0 ){
                AHC_UF_SetRearCamPathFlag(AHC_FALSE);
            }
        }
        break;
    default:
         printc("pBuff[0] %d\r\n",pBuff[0]);
          break;
    }

    return 1;
}


//------------------------------------------------------------------------------
//  Function    : DTV_Uart_CheckSum
//  Description :
//起始字符：
//0xFF 0xAA
//数据长度：
//1BYTE //数据种类+数据内容长度
//数据种类：
//      1BYTE (DVR发送0x01~0x9f, 主机发送0xA1~0xff)
//数据内容：
//        N个BYTE
//Checksum校验：
//数据长度 +数据种类 +数据内容相加---1BYTE

static MMP_BOOL DTV_Uart_CheckSum_Cmp(MMP_BYTE *pBuff, MMP_ULONG iBuff_sz)
{
    MMP_UBYTE sum = 0,bsum = pBuff[pBuff[0]+1];
    MMP_UBYTE  i = 0;

    for(i=0;i<=(pBuff[0]);i++)
    {
        sum += pBuff[i];
    }

    if(sum == bsum)
        return AHC_TRUE;
    else{
        printc(FG_RED("%s: Check sum err sum:bsum=%x:%x")"\r\n", __func__,sum,bsum);
        return AHC_FALSE;
   }
}

void DTV_Uart_DumpData(MMP_BYTE *pBuff, MMP_ULONG iBuff_length)
{
    MMP_BYTE i;
    for(i=0;i<iBuff_length;i++)
    {
        printc("%02x ",pBuff[i]);
        if(i == 10)
            printc("\r\n");
    }
    printc("\r\n");
}

//------------------------------------------------------------------------------
//  Function    : DTV_Uart_PaeserMain
//  Description : Entry of DTV_Parser
//------------------------------------------------------------------------------
//一、通信协议格式：
//起始字符：
//0xFF 0xAA
//数据长度：
//1BYTE //数据种类+数据内容长度
//数据种类：
//      1BYTE (DVR发送0x01~0x9f, 主机发送0xA1~0xff)
//数据内容：
//        N个BYTE
//Checksum校验：
//数据长度 +数据种类 +数据内容相加1BYTE

static void DTV_Uart_ParserMain(MMP_BYTE *pBuff, MMP_ULONG iBuff_length)
{
    MMP_BYTE temp[128]={0};;

    if( iBuff_length < (pBuff[0]+1+1))
    {
        printc(FG_RED("%s: iBuff_length err %d")"\r\n", __func__, iBuff_length);
        return;
    }

    //dumpdata
    DTV_Uart_DumpData(pBuff,iBuff_length);

    if(DTV_Uart_CheckSum_Cmp(pBuff,iBuff_length))
        DTV_Uart_ParsePack(pBuff);
    else
        printc(FG_RED("CheckSum Error %#x/%#x\n"), DTV_Uart_CheckSum(pBuff), pBuff[iBuff_length-2]);

}

 void DTV_Uart_String_RxCallback(MMP_UBYTE size, volatile MMP_UBYTE *fifo)
{
    MMP_BYTE chUartchar,i;
    //MMP_BYTE lastchar;

    for(i = 0; i < size; i++) {
        chUartchar = *fifo;
        m_bUartString[(m_bUartRxStrLen + i) % Uart_RX_QUEUE_SIZE] = chUartchar;
        // Uart Echo
        //printc("%02x",chUartchar);
    }

    m_bUartRxStrLen += size;
    if (m_bUartRxStrLen >= Uart_RX_QUEUE_SIZE) {
        RTNA_DBG_Str(0, "Error: S680 UART RX overflow\r\n");
    }

    if(chUartchar == TAIL1_S680)
    {
        m_bUartRxSatus  = AHC_TRUE;
        MMPF_OS_SetFlags(UartCtrlFlag, Touch_Uart_FLAG_GETPACK, MMPF_OS_FLAG_SET);
    }
    return;
}

MMP_ERR DTV_Uart_InitPathUART(struct _3RD_PARTY_TOUCH_UART *pthis,MMP_UART_ATTR uartattribute)
{
    MMP_LONG error;

    printc("%s: \r\n", __func__);

    uartattribute.bParityEn         = MMP_FALSE;
    uartattribute.parity            = MMP_UART_PARITY_NONE;
    uartattribute.bFlowCtlEn        = MMP_FALSE;
    uartattribute.ubFlowCtlSelect   = 1;
    uartattribute.padset            = DTV_UART_PADSET;
    uartattribute.ulMasterclk       = DTV_UART_CLK * 1000 ;
    uartattribute.ulBaudrate        = DTV_UART_BAUD_RATE;

    error = MMPF_Uart_Open(DTV_UART_NUM, &uartattribute);
    if(error)
        printc("Uart Open Error : %d\r\n",error);

    MMPF_Uart_EnableRx(DTV_UART_NUM, 1,(UartCallBackFunc *)&DTV_Uart_String_RxCallback);

    if(error)
        printc("Uart UseRxDMA : %d\r\n",error);
    return MMP_ERR_NONE;
}

MMP_ERR DTV_Uart_GetString_UART(struct _3RD_PARTY_TOUCH_UART *pthis,MMP_BYTE *bUTString, MMP_ULONG *ulUTStringLength)
{
#if (UART_RXINT_MODE_EN == 1)
    MMP_LONG j=0,i;
    int nLen0,nLen;
    MMP_BOOL Parse_flag = AHC_FALSE;
    MMP_ULONG ulStartPosition =0;

    if(m_bUartRxStrLen < 6) //at less 6 byte
        return MMP_ERR_NONE;

    //AHC_OS_SleepMs(10);

    m_bUartRxSatus  = AHC_FALSE;
    nLen =  m_bUartRxStrLen;
    nLen0 =  m_bUartRxStrLen;
    printc("nLen = %d\n", nLen );

    while(nLen>0)
    {
        char chUartchar1 =  m_bUartString[ulStartPosition];
        char chUartchar2 =  m_bUartString[ulStartPosition+1];
        printc("head:%x,%x\r\n",chUartchar1,chUartchar2);
        if(chUartchar1 == HEAD1_S680 && chUartchar2 == HEAD2_S680)
        {
            char dataLen;
            dataLen = m_bUartString[ulStartPosition+2];
            if((nLen-2-1-1) < dataLen)//chUartchar1+chUartchar2+cunt+checksum
            {
                goto RECWARN;
            }

            ulStartPosition += 2;
            i = ulStartPosition;
            for(;i<nLen0;i++)
            {
                bUTString[j++] = m_bUartString[ulStartPosition];
                ulStartPosition ++;
            }
            Parse_flag = AHC_TRUE;
            break;
        }
        ulStartPosition++;
        nLen--;
    }

    *ulUTStringLength = j;
    bUTString[j] = '\0';

    if(Parse_flag){
        m_bUartRxStrLen = 0;
        DTV_Uart_ParserMain(bUTString,j);
    }
#endif
    return MMP_ERR_NONE;

RECWARN:
    *ulUTStringLength = 0;
    printc("unknow packet!\r\n");
    return MMP_HIF_ERR_PARAMETER;
}

MMP_ERR DTV_Uart_Setstring(struct _3RD_PARTY_TOUCH_UART *pthis,MMP_BYTE *data,MMP_ULONG length)
{
#if 0
    char        chCommand[10];
    MMP_UBYTE   ublength = 0;
    MMP_ERR     err;

    MEMSET(chCommand, 0, sizeof(chCommand));

    err = MMPF_Uart_Write(DTV_UART_NUM, chCommand, ublength);
    if (err)
        printc(FG_RED("%s: Send TPMS Tx error 0x%x")"\r\n", __func__, err);
#else
    printc(FG_RED("%s: TBD")"\r\n", __func__);
#endif
}

MMP_BOOL DTV_Uart_ModuleAttached(struct _3RD_PARTY_TOUCH_UART *pthis)
{
    //printc("%s: TBD\r\n", __func__);
    return MMP_TRUE;
}

MMP_ERR DTV_Uart_IOControl(struct _3RD_PARTY_TOUCH_UART *pthis, MMP_UBYTE cmd,MMP_UBYTE *arg)
{
    switch(cmd)
    {
        case UART_CMD_WRITE_IOCTL:
        default:
            DTV_Uart_MergePack(arg);
        break;
    }

    return MMP_ERR_NONE;
}

static struct _3RD_PARTY_TOUCH_UART Touch_Uart_Obj =
{
    DTV_Uart_InitPathUART,
    DTV_Uart_GetString_UART,
    DTV_Uart_Setstring,
    DTV_Uart_ModuleAttached,
    DTV_Uart_IOControl,
};

int Touch_Uart_Module_Init(void)
{
    printc(FG_GREEN("[Touch_Uart_Module_Init]\r\n"));
    Touch_Uart_Ctrl_Register(&Touch_Uart_Obj);
    return 0;
}

#if defined(__GNUC__)
__section__(initcall6)
#else //#if defined(__GNUC__)
#pragma arm section code = "initcall6", rodata = "initcall6", rwdata = "initcall6",  zidata = "initcall6"
#pragma O0
#endif
ait_module_init(Touch_Uart_Module_Init);
#if defined(__GNUC__)
__section__(initcall6)
#else //#if defined(__GNUC__)
#pragma
#pragma arm section rodata, rwdata ,  zidata
#endif
#endif      // ALL_FW
#endif //TOUCH_UART_FUNC_EN



