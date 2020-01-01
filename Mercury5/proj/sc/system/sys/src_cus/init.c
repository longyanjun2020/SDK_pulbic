/****************************************************************************/
/*  File    : init.c                                                    */
/*--------------------------------------------------------------------------*/
/*  Scope   : Definition of the tasks, the mailboxes and the                */
/*            semaphores                                                    */
/*  Contents:                                                               */
/*                                                                          */
/*  History:                                                                */
/*=============================  VMTS HISTORY  =============================*/
/*  Date  | Aut.|                  Description                              */
/*--------+-----+-----------------------------------------------------------*/
/*23.05.06| BLE |BUG FIX #420: CSN1 compiler upgrade integration            */
/*23.05.06| BLE |BUG_CSN1: Handler Exception RTK_STACK_OVERFLOW in task RR  */
/*        |     |occured with new CSN1 decoder and message HANDOVER Command */
/*        |     | (for example) Solution: increase the stack:               */
/*        |     |  cus_MarkerStackSize                                      */
/*--------+-----+-----------------------------------------------------------*/
/****************************************************************************/

#include "stdcomp.h"
#include "osdefs.hc"
#include "sys_traces.ho"
#include "sys_rm_trc.ho"
#include "sys_v24.hi"

#define __INIT_VAR__
#include "sys_sys_init.h"
#undef __INIT_VAR__

#ifdef __HWL_TINY__
#include "rr_simu.h"
#endif

#ifdef __WIRTI_USE__
#include "glob.h"
#endif

#if defined(__TIME_SLICE_SCHEDULE__)
#include "sys_sys_arm.h"
#if defined(__SYS_TIME_SLICE_TEST__)
#include "sys_task_test.h"
#endif
#endif

#include "config_fw.h"
#include "all_fw.h"

#include "i_sw_uart.h"
#include "sys_MsWrapper_cus_os_msg.h"
#include "sys_MsWrapper_cus_os_timer.h"

//==============================================================================
//
//                              Function Prototype
//
//==============================================================================

extern void i_sw_idle_Task (void);
extern void mdl_Task(void);
extern void menu_Task (void);
extern void timer_Task(void);
extern void v24_Task(void);
extern void SCLIRQ_DazaThread(void);
extern void SCL_Task(void);
extern void SCLPoll_Task(void);
extern void VIP_DazaIST(void);
extern void VIF_Task(void);
extern void ISP_HighTask(void);
extern void ISP_LowTask(void);
extern void ISP_RDMATask(void);
extern void DIP_Ctl_Task(void);

#if defined(ALL_FW) // CarDV tasks

extern void High_Work_Task(void);
extern void Mid_Work_Task(void);
extern void Low_Work_Task(void);
#if (!defined(MBOOT_FW)||defined(FAT_BOOT)||defined(MBOOT_EX_FW)||defined(MBOOT_SRAM_FW))
//In order to use FS in bootloader add defined(MBOOT_SRAM_FW)
extern void FS_Task(void);
#endif
#if defined(ALL_FW) && (SUPPORT_EIS)
extern void GYRO_TaskHandler(void);
//extern void EIS_Task(void);
#endif
extern void AhcTask(void);
#if defined(SPEECH_RECOGNIZE_EN) && (SPEECH_RECOGNIZE_EN)
extern void Speech_TaskHandler(void);
#endif
extern void SCLPoll_Task(void);

#if (VIDEO_R_EN)
extern void MMPF_VIDENC_DONE_Task(void);
extern void MMPF_VIDMGR_Task(void);
extern void MMPF_VIDENC_TRIG_Task(void);
extern void MMPF_VIDENC_DMAGEN_Task(void);
#if (SUPPORT_H264_WIFI_STREAM)
extern void MMPF_H264WifiStreamCB_Task(void);
#endif
#endif

#if (AUDIO_R_EN)||(VIDEO_R_EN)
extern void AUDIO_Record_Task(void);
#endif
#if (AUDIO_P_EN)||(VIDEO_P_EN)
extern void AUDIO_Play_Task(void);
#endif
#if ((AUDIO_P_EN)&&((AUDIO_STREAMING_EN)||(AUI_STREAMING_EN)))||(AUDIO_R_EN)
extern void AUDIO_Streaming_Task(void);
#endif

#if (VIDEO_P_EN)
extern void MMPF_Parsr3GP_Task(void);
extern void MMPF_VideoDecoder_Task(void);
extern void MMPF_VidPlayer_Task(void);
#if (VIDEO_BGPARSER_EN == 1)
extern void MMPF_VIDPSR_BGTask(void);
#if (VIDEO_HIGHPRIORITY_FS == 1)
extern void MMPF_VISPSR_BGFSTask(void);
#endif
#endif
#endif

#if (DSC_R_EN)||(DSC_P_EN)
extern void MMPF_DSC_Task(void);
#if (DSC_R_EN)
extern void MMPF_JPEG_Dec_Task(void);
extern void MMPF_JPEG_Enc_Task(void);
#endif
#endif

#if (SENSOR_EN)
extern void MMPF_Sensor_Task(void);
#endif

#if (USB_EN)
extern void USB_Task(void);
#if (MSDC_WR_FLOW_TEST_EN == 1)
extern void USB_Write_Task(void);
#endif
#if (SUPPORT_USB_HOST_FUNC)
extern void MMPF_USBH_PostProcess_Task(void);
extern void MMPF_USBH_BulkIn_Task(void);
extern void ms_UhcTask0_rtk(void);
extern void ms_UhcTask1_rtk(void);
#endif
#endif

#if(WIFI_PORT)
extern void MMPF_Streaming_TaskHandler(void *p_arg);
#endif

#endif

//==============================================================================
//
//                              GLOBAL VARIABLES
//
//==============================================================================

#define V24_STACK_SIZE       (2000)
#define MDL_STACK_SIZE       (2048)

#if 0
void ____Task____(){ruturn;} //dummy
#endif

const cus_InitTask_t cus_InitTask [] =
{   // Name         EntryPoint                      Priority                    StackSize                   TraceElement    TimeSliceMax    TimeSliceLeft
    { "IDLE",       i_sw_idle_Task,                 TASK_IDLE_PRIO,             2048,                       _HWL,           0,              0},
    { "MENU",       menu_Task,                      TASK_CMD_MENU_PRIO,         4096,                       _HWL,           0,              0},
    { "V24",        v24_Task,                       TASK_V24_PRIO,              V24_STACK_SIZE,             _HWL,           0,              0},
    { "MDL",        mdl_Task,                       TASK_MDL_PRIO,              MDL_STACK_SIZE,             _MDL,           0,              0},
    { "SCL_DAZA",   SCLIRQ_DazaThread,              TASK_SCL_IRQ_DAZA_PRIO,     4096,                       _HWL,           0,              0},
    { "VIP_DAZA",   VIP_DazaIST,                    TASK_VIP_DAZA_IST,          2048,                       _HWL,           0,              0},
    { "SCL",        SCL_Task,                       TASK_SCL_PRIO,              4096,                       _HWL,           0,              0},
    { "SCL_POLL",   SCLPoll_Task,                   TASK_SCL_POLL_PRIO,         5120,                       _HWL,           0,              0},
    { "VIF",        VIF_Task,                       TASK_VIF_PRIO,              4096,                       _HWL,           0,              0},
    { "ISPhigh",    ISP_HighTask,                   TASK_ISP_HIGH_PRIO,         4096,                       _HWL,           0,              0},
    { "ISPlow",     ISP_LowTask,                    TASK_ISP_LOW_PRIO,          4096,                       _HWL,           0,              0},
    { "ISP_RDMA",   ISP_RDMATask,                   TASK_ISP_RDMA_PRIO,         2048,                       _HWL,           0,              0},
#ifdef __FIXME__
    { "STG_MNT",    storage_monitor_Task,           12,                         4096,                       _HWL,           0,              0}, // VM_MBX_CUS1
#endif
    { "TIMER",      timer_Task,                     TASK_SYS_TIMER_PRIO,        2048,                       _RTK,           0,              0},
#if defined(__VER_VDR__)
    { "VDR",        MdlVdrVideoTask_isw,            24,                         4096,                       _RTK,           0,              0},
#endif
#if defined(__SYS_TIME_SLICE_TEST__)
    { "TEST1",      test1_Task,                     50,                         1024,                       _RTK,           RTK_MS_TO_TICK(25), RTK_MS_TO_TICK(25)},
    { "TEST2",      test2_Task,                     50,                         1024,                       _RTK,           RTK_MS_TO_TICK(25), RTK_MS_TO_TICK(25)},
#endif

#if defined(ALL_FW)
    { "DIPCTL",     DIP_Ctl_Task,                   TASK_DIP_CTL_PRIO,          DIP_CTL_STK_SIZE,           _RTK,           0,              0},
    { "HighWork",   High_Work_Task,                 TASK_HIGH_WORK_PRIO,        HIGH_WORK_STK_SIZE,         _RTK,           0,              0},

#if (VIDEO_R_EN)
    { "VID_DONE",   MMPF_VIDENC_DONE_Task,          TASK_VID_ENC_DONE_PRIO,     VIDENC_DONE_STK_SIZE,       _RTK,           0,              0},
    { "VIDMGR",     MMPF_VIDMGR_Task,               TASK_VIDMGR_PRIO,           VIDMGR_STK_SIZE,            _RTK,           0,              0},
    #if (SUPPORT_H264_WIFI_STREAM)
    { "H264WIFICB", MMPF_H264WifiStreamCB_Task,     TASK_H264WIFICB_PRIO,       WIFISTREAMCB_STK_SIZE,      _RTK,           0,              0},
    #endif
    { "VID_TRIG",   MMPF_VIDENC_TRIG_Task,          TASK_VID_ENC_TRIG_PRIO,     VIDENC_TRIG_STK_SIZE,       _RTK,           0,              0},
    { "VID_DMAGEN", MMPF_VIDENC_DMAGEN_Task,        TASK_VID_DMA_GEN_PRIO,      VIDENC_DMA_GEN_STK_SIZE,    _RTK,           0,              0},
#endif

#if (AUDIO_R_EN)||(VIDEO_R_EN)
    { "AUDIOREC",   AUDIO_Record_Task,              TASK_AUDIO_RECORD_PRIO,     AUDIO_RECORD_STK_SIZE,      _RTK,           0,              0},
#endif
#if (AUDIO_P_EN)||(VIDEO_P_EN)
    { "AUDIOPLAY",  AUDIO_Play_Task,                TASK_AUDIO_PLAY_PRIO,       AUDIO_PLAY_STK_SIZE,        _RTK,           0,              0},
#endif
#if ((AUDIO_P_EN)&&((AUDIO_STREAMING_EN)||(AUI_STREAMING_EN)))||(AUDIO_R_EN)
    { "AUDSTREAM",  AUDIO_Streaming_Task,           TASK_AUDIO_STREAM_PRIO,     AUDIO_WRITEFILE_STK_SIZE,   _RTK,           0,              0},
#endif

#if (VIDEO_P_EN)
    { "3GPPARSR",   MMPF_Parsr3GP_Task,             TASK_3GPPARSR_PRIO,         DEMUXER_STK_SIZE,           _RTK,           0,              0},
    { "VIDDEC",     MMPF_VideoDecoder_Task,         TASK_VIDDEC_PRIO,           DECODER_STK_SIZE,           _RTK,           0,              0},
    { "VIDPLAY",    MMPF_VidPlayer_Task,            TASK_VIDPLAY_PRIO,          PLAYER_STK_SIZE,            _RTK,           0,              0},
    #if (VIDEO_BGPARSER_EN == 1)
    { "VIDPSR_BG",  MMPF_VIDPSR_BGTask,             TASK_BG_PARSER_PRIO,        BG_PARSER_STK_SIZE,         _RTK,           0,              0},
    #if (VIDEO_HIGHPRIORITY_FS == 1)
    { "VIDPSR_BGFS", MMPF_VISPSR_BGFSTask,          TASK_HIGHFS_PRIO,           HIGH_PRIO_FS_STK_SIZE,      _RTK,           0,              0},
    #endif
    #endif
#endif

#if (DSC_R_EN)||(DSC_P_EN)
    { "DSC",        MMPF_DSC_Task,                  TASK_DSC_PRIO,              DSC_STK_SIZE,               _RTK,           0,              0},
    { "JPEGEnc",    MMPF_JPEG_Enc_Task,             TASK_JPEG_ENC_PRIO ,        JPEG_ENC_STK_SIZE,          _RTK,           0,              0},
    { "JPEGDec",    MMPF_JPEG_Dec_Task,             TASK_JPEG_DEC_PRIO,         JPEG_DEC_STK_SIZE,          _RTK,           0,              0},
#endif

#if (SENSOR_EN)
    { "SENSOR",     MMPF_Sensor_Task,               TASK_SENSOR_PRIO,           SENSOR_STK_SIZE,            _RTK,           0,              0},
#endif

#if (USB_EN)
    { "USB",        USB_Task,                       TASK_USB_PRIO,              USB_STK_SIZE,               _RTK,           0,              0},
    #if (MSDC_WR_FLOW_TEST_EN == 1)
    { "USB_Write",  USB_Write_Task,                 TASK_USB_WRITE_PRIO,        USB_STK_SIZE,               _RTK,           0,              0},
    #endif
    #if (SUPPORT_USB_HOST_FUNC)
    { "HUVC_PP",    MMPF_USBH_PostProcess_Task,     TASK_USBH_POSTPROCESS_PRIO, USB_UVCH_POSTPROC_STK_SIZE, _RTK,           0,              0},
    { "HUVC_Bulk",  MMPF_USBH_BulkIn_Task,          TASK_USBH_BULKIN_PRIO,      USB_UVCH_BULKIN_STK_SIZE,   _RTK,           0,              0},
    { "UHC_EHCI0",  ms_UhcTask0_rtk,                TASK_UHC_EHCI0_PRIO,        USB_UHC_EHCI_STK_SIZE,      _RTK,           0,              0},
    { "UHC_EHCI1",  ms_UhcTask1_rtk,                TASK_UHC_EHCI1_PRIO,        USB_UHC_EHCI_STK_SIZE,      _RTK,           0,              0},
    #endif
#endif
#if(WIFI_PORT)
    { "STREAMING",  MMPF_Streaming_TaskHandler,     TASK_WIFI_STREAMING_PRIO,   WIFI_STREAMING_STK_SIZE,    _RTK,           0,              0},
#endif
#if (!defined(MBOOT_FW)||defined(FAT_BOOT)||defined(MBOOT_EX_FW)||defined(MBOOT_SRAM_FW))
    { "FS",         FS_Task,                        TASK_FS_PRIO,               FS_STK_SIZE,                _RTK,           0,              0},
#endif
#if defined(ALL_FW) && (SUPPORT_EIS)
    { "GYRO",       GYRO_TaskHandler,               TASK_GYRO_PRIO,             GYRO_STK_SIZE,              _RTK,           0,              0},
    { "EIS",        EIS_TaskHandler,                TASK_EIS_PRIO,              EIS_STK_SIZE,               _RTK,           0,              0},
#endif

#if defined(SPEECH_RECOGNIZE_EN) && (SPEECH_RECOGNIZE_EN)
    { "SPEECH_AI",  Speech_TaskHandler,             TASK_SPEECH_RECOG_PRIO,     SPEECH_STK_SIZE,            _RTK,           0,              0},
#endif

    { "AHCTask",    AhcTask,                        TASK_AHC_INIT_PRIO,         AHC_STK_SIZE,               _RTK,           0,              0},
#endif
};

#if 0
void ____MailBox____(){ruturn;} //dummy
#endif

const cus_InitMbx_t cus_InitMbx[] =
{
    /* Name    , ID     */
    {"LAPD"    , LAPD1_MBX},
    {"MSR"     , MSR1_MBX},
    {"RR"      , RR1_MBX},
    {"L1C"     , L1C1_MBX},
    {"HAC"     , HACTIM_MBX},
    {"SIM"     , SIM_MBX},
    {"SIM HD"  , SIM_HAND_MBX},
    {"CC"      , CC1_MBX},
    {"MM"      , MM1_MBX},
    {"SMS"     , SMS1_MBX},
    {"SS"      , SS1_MBX},
    {"DAT"     , DATA_MBX},
    {"HWL"     , HWL_MBX},  // even if task hwl doesn't exist
    #ifdef __WIRTI_USE__
    {"WIRTI"   , HWL_MBX},  // even if task WIRTI doesn't exist
    #endif
    {"IR"      , IR_MBX},
    {"IP"      , IP1_MBX},
    {"BATT"    , BAT_MBX},
    {"OBX"     , OBX_MBX},
    {"V24"     , V24_MBX},
    {"MDL"     , MDL1_MBX},
    /* GPRS mail boxes */
    {"PPS"     , PPS1_MBX},
    {"SM"      , SM1_MBX},
    {"SNDCP"   , SNDCP1_MBX},
    {"LLC"     , LLC1_MBX},
    {"RLD"     , RLD1_MBX},
    {"RLU"     , RLU1_MBX},
    {"ABB"     , ABB_MBX}, // Analog BaseBand Task Mailbox
    {"TIMER"  , TIMER_MBX},
    /* Customer Mailboxes */
    {"CUS1"    , CUS1_MBX},
    {"CUS2"    , CUS2_MBX},
    {"CUS3"    , CUS3_MBX},
    {"CUS4"    , CUS4_MBX},
    {"CUS5"    , CUS5_MBX},
    {"CUS6"    , CUS6_MBX},
    {"CUS7"    , CUS7_MBX},
    {"CUS8"    , CUS8_MBX},
    {"CUS9"    , CUS9_MBX},
    {"CUS10"   , CUS10_MBX},
    {"CUS11"   , CUS11_MBX},
    {"CUS12"   , CUS12_MBX},
    {"CUS13"   , CUS13_MBX},
    {"CUS14"   , CUS14_MBX},
    {"CUS15"   , CUS15_MBX},
    {"CUS16"   , CUS16_MBX},
    {"CUS17"   , CUS17_MBX},
    {"CUS18"   , CUS18_MBX},
    {"CUS19"   , CUS19_MBX},
    {"CUS20"   , CUS20_MBX},
    {"CUS21"   , CUS21_MBX},
    {"CUS22"   , CUS22_MBX},
    {"CUS23"   , CUS23_MBX},
    {"CUS24"   , CUS24_MBX},
    {"CUS25"   , CUS25_MBX},
    {"CUS26"   , CUS26_MBX},
    {"CUS27"   , CUS27_MBX},
    {"CUS28"   , CUS28_MBX},
    {"CUS29"   , CUS29_MBX},
    {"CUS30"   , CUS30_MBX},
    {"CUS31"   , CUS31_MBX},
    {"CUS32"   , CUS32_MBX},
    {"CUS33"   , CUS33_MBX},
    {"CUS34"   , CUS34_MBX},
    {"CUS35"   , CUS35_MBX},
    {"CUS36"   , CUS36_MBX},
    {"CUS37"   , CUS37_MBX},
    {"CUS38"   , CUS38_MBX},
    {"CUS39"   , CUS39_MBX},
    {"CUS40"   , CUS40_MBX},
    {"CUS41"   , CUS41_MBX},
    {"CUS42"   , CUS42_MBX},
    {"CUS43"   , CUS43_MBX},
    {"CUS44"   , CUS44_MBX},
    {"CUS45"   , CUS45_MBX},
    {"CUS46"   , CUS46_MBX},
    {"CUS47"   , CUS47_MBX},
    {"CUS48"   , CUS48_MBX},
    {"CUS49"   , CUS49_MBX},
    {"CUS50"   , CUS50_MBX},
    {"CUS51"   , CUS51_MBX},
    {"CUS52"   , CUS52_MBX},
    {"CUS53"   , CUS53_MBX},
    {"CUS54"   , CUS54_MBX},
    {"CUS55"   , CUS55_MBX},
    {"CUS56"   , CUS56_MBX},
    {"CUS57"   , CUS57_MBX},
    {"CUS58"   , CUS58_MBX},
    {"CUS59"   , CUS59_MBX},
    {"CUS60"   , CUS60_MBX},
    {"CUS61"   , CUS61_MBX},
    {"CUS62"   , CUS62_MBX},
    {"CUS63"   , CUS63_MBX},
    {"CUS64"   , CUS64_MBX},
    {"CUS65"   , CUS65_MBX},
    {"CUS66"   , CUS66_MBX},
    {"CUS67"   , CUS67_MBX},
    {"CUS68"   , CUS68_MBX},
    {"CUS69"   , CUS69_MBX},
    {"CUS70"   , CUS70_MBX},
    {"CUS71"   , CUS71_MBX},
    {"CUS72"   , CUS72_MBX},
    {"CUS73"   , CUS73_MBX},
    {"CUS74"   , CUS74_MBX},
    {"CUS75"   , CUS75_MBX},
    {"CUS76"   , CUS76_MBX},
    {"CUS77"   , CUS77_MBX},
    {"CUS78"   , CUS78_MBX},
    #ifdef __MSTAR_DUAL_SIM__
    {"CC2"     , CC2_MBX},
    {"SS2"     , SS2_MBX},
    {"SMS2"    , SMS2_MBX},
    {"MM2"     , MM2_MBX},
    {"RR2"     , RR2_MBX},
    {"SPV2"    , SPV2_MBX},
    {"SM2"     , SM2_MBX},
    {"SNDCP2"  , SNDCP2_MBX},
    {"MDL2"    , MDL2_MBX},
    {"CE"      , CE_MBX},
    {"MSR2"    , MSR2_MBX},
    {"LLC2"    , LLC2_MBX},
    {"RLD2"    , RLD2_MBX},
    {"RLU2"    , RLU2_MBX},
    {"LAPD2"   , LAPD2_MBX},
    {"PPS2"    , PPS2_MBX},
    {"IP2"     , IP2_MBX},
    #ifdef __MSTAR_DUAL_SIM_SIM_DUO__
    {"SIM2"    , SIM2_MBX},
    {"SIM2HD"  , SIM2_HAND_MBX},
    #endif
    {"ML EXT"  , MDL_EXT_MBX},
    #endif
    {"DIPCTL"  , DIP_CTL_MBX},
};

#if 0
void ____Semaphore____(){ruturn;} //dummy
#endif

#define SEM_INIT_TABLE
#include "sys_sys_semaphore_init_table.h"
#undef SEM_INIT_TABLE

#if 0
void ____Size____(){ruturn;} //dummy
#endif

u8          cus_NbTask   = sizeof(cus_InitTask) / sizeof(cus_InitTask_t);
const u8    cus_NbMbx    = sizeof(cus_InitMbx)  / sizeof(cus_InitMbx_t);
const u16   cus_NbSem    = sizeof(cus_InitSem)  / sizeof(cus_InitSem_t);

/*+ BLE 23May2006 BUB FIX #420: BUG_CSN1:
** Handler Exception RTK_STACK_OVERFLOW in task RR occured with new CSN1 decoder and
** message HANDOVER Command (for example) */
const u16 cus_MarkerStackSize = 8000;

/*  PCI 28.01.03: 150 envelops increase to stop trap in 144 in OPEN MMI (Tracker 6967)
    2 kbytes decrease in RAM size
    WARNING with OPEN STACK 550 with ROM/RAM 16/2
*/
const u16 cus_NbEnv           = 400;
const u16 cus_NbTimer         = 60;
const u16 cus_NbCoarseTimer   = CUS_COARSE_TIMER_INIT_NB;

#include "sys_sys.h"

//==============================================================================
//
//                              Functions
//
//==============================================================================

void i_sw_idle_Task(void)
{
    static u8 cmd_loops = 0;
    static bool bCustomerTask = FALSE;

    while(1)
    {
        if (v24_SerialOn != 0)
        {
            // Treat the quick trace buffer
            trc_PurgeQuickTrcBuf();
            while (v24_PollRxTx()){}
        }

        sys_CustomIdleProc2();
        
        do {
            cmd_loops++;
            if (cmd_loops > 3){
                cmd_loops = 0;
                continue;
            }
        } while (sys_CustomIdleProc());

#if defined(__CHIPDRV_R2_WDT__) || defined(__CHIPDRV_INFINITY_WDT__) //__G1__
        sys_DelayWatchDogReset();
#else
        WDogCountRstExpected = TRUE;
#endif
        if (bCustomerTask == FALSE)
        {
            bCustomerTask = TRUE;
            AHC_SWPACK_TaskInit();
        }
        // do nothing but just keep waiting
    }
}

void isw_cli_main(void);
void menu_Task (void)
{
    u32 choice;
    
    UartSendTrace("\n\r\n\r\n\r");
    UartSendTrace("--------------------------\n\r");
#ifdef __I_SW_OS__
    UartSendTrace("I_SW_OS bootup menu_Task\n\r");
#else
    UartSendTrace("I_SW_NOS bootup menu_Task\n\r");
#endif
    UartSendTrace("--------------------------\n\r");
    
    isw_cli_main();
    
    while(1)
    {
        #define TEST_SEQ_NUM_DUMMY  0
        #define TEST_SEQ_NUM_FMRX   1
        #define TEST_SEQ_NUM_EMI    2
        #define TEST_SEQ_NUM_USB    3
        #define TEST_SEQ_NUM_SDIO   4
        #define TEST_SEQ_NUM_FCIE   5
        
        UartSendTrace("\n\r");
        UartSendTrace("--------------------------\n\r");
        UartSendTrace("Software Datecode :%s : %s\n\r",__DATE__,__TIME__);
        UartSendTrace("--------------------------\n\r");
        UartSendTrace("Function to test : \n\r");
        UartSendTrace("%d)\tDummy test\n\r",   TEST_SEQ_NUM_DUMMY);
        #if defined(__VER_FMRX__)
        UartSendTrace("%d)\tFMRX test\n\r",    TEST_SEQ_NUM_FMRX);
        #endif
        #if defined(__VER_EMI__)
        UartSendTrace("%d)\tEMI test\n\r",     TEST_SEQ_NUM_EMI);
        #endif
        #if defined(__VER_USB__)
        UartSendTrace("%d)\tUSB test\n\r",     TEST_SEQ_NUM_USB);
        #endif
        #if defined(__VER_SDIO__)
        UartSendTrace("%d)\tSDIO test\n\r",     TEST_SEQ_NUM_SDIO);
        #endif
        #if defined(__VER_FCIE__)
        UartSendTrace("%d)\tFCIE test\n\r",     TEST_SEQ_NUM_FCIE);
        #endif
        
        UartSendTrace("X)\tNot supported\n\r");
        
        choice = vm_atoi(wait_for_command());

        switch(choice)
        {
#if defined(__VER_FMRX__)
        case TEST_SEQ_NUM_FMRX:
            fmrx_test();
            break;
#endif
#if defined(__VER_EMI__)
        case TEST_SEQ_NUM_EMI:
            emi_test();
            break;
#endif
#if defined(__VER_USB__)
        case TEST_SEQ_NUM_USB:
            UsbTest(0);
            break;
#endif
#if defined(__VER_SDIO__)
        case TEST_SEQ_NUM_SDIO:
            DrvSdioTest();
            break;
#endif
#if defined(__VER_FCIE__)
        case TEST_SEQ_NUM_FCIE:
            MDrvStorageInitial();
            break;
#endif
        default :
            UartSendTrace("BAD command \n\r");
            break;
        }
    }
}

void timer_Task(void)
{
    extern bool MsReceiveEx(MsMailbox_e eMailbox, MsObj_t *pMsg);
    MsObj_t  Obj;
    MsCbTimer_t cbtimer;
    
    Obj.Msg = (void*)&cbtimer;
    
    while (1)
    {
        cbtimer.eTimerID = 0;
        cbtimer.pfCB = NULL;
        cbtimer.UserData = 0;
        MsReceiveEx(TIMER_MBX, &Obj);
        
        if (cbtimer.pfCB)
        {
            cbtimer.pfCB(cbtimer.eTimerID, cbtimer.UserData);
        }
    }
}
