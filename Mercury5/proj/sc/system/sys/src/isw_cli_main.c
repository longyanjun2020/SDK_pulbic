#ifdef __I_SW_OS_G1__
#include "sys_MsWrapper_cus_os.h"
#include "sys_MsWrapper_cus_os_util.h"
#include "cus_os_def.h"
#include "sys_MsWrapper_cus_os_sem.h"
#include "cus_os_event.h"
#include "sys_MsWrapper_cus_os_msg.h"
#include "sys_MsWrapper_cus_os_timer.h"
#include "sys_MsWrapper_cus_os_mem.h"
#else
#include <string.h>
#include <stdlib.h>
#include "vm_types.ht"
#include "i_sw_uart.h"
#include "sys_arm.h"
#include "sys.ho"
#include "drv_io_chip_pub_types.h"
#include "drv_io_chip_pub_api.h"
#endif
#include "ahc_parameter.h"
#include "isw_cli.h"
#include "sys_rtk_ho.h"
#include "kernel.h"
#include "hal_int_ctrl_pub.h"
#include "fs_test.h"
#include "sd_test.h"
#ifdef __INFINITY__
#include "sys_MsWrapper_cus_os.h"
#include "sys_MsWrapper_cus_os_util.h"
#include "sys_MsWrapper_cus_os_sem.h"
#include "sys_MsWrapper_cus_os_msg.h"
#include "sys_MsWrapper_cus_os_timer.h"
#include "sys_MsWrapper_cus_os_mem.h"
#include "sys_MsWrapper_cus_os_test.h"
#endif
#if (WIFI_PORT == 1)
#include "net_cfg.h"
#endif
#include "ahc_uf.h"
#include "drv_isp.h"
#include "ahc_menu_inc.h"

CLI_t _tCliMain;
static char _szOn[] = "on";
static char _szOff[] = "off";

static int _helpHandler(CLI_t *pCli, char *p);
static char _szHelpHelpTxt[] = "Print help message";
static char _szHelpUsageTxt[] = "";

static int _cdHandler(CLI_t *pCli, char *p);
static char _szCdHelpTxt[] = "Change the working space";
static char _szCdUsageTxt[] = "";

static int _quitHandler(CLI_t *pCli, char *p);
static char _szQuitHelpTxt[] = "Quit CLI";
static char _szQuitUsageTxt[] = "";

static int _memdumpHandler(CLI_t *pCli, char *p);
static char _szMemdumpHelpTxt[] = "dump memory";
static char _szMemdumpUsageTxt[] =
    "Usage: memdump addr size\n"
    "   addr and size must be multiple of 4\n";

static int _memsetHandler(CLI_t *pCli, char *p);
static char _szMemsetHelpTxt[] = "set memory";
static char _szMemsetUsageTxt[] =
    "Usage: memset dst pattern size\n"
    "   dst and size must be multiple of 4\n";

static int _memcpyHandler(CLI_t *pCli, char *p);
static char _szMemcpyHelpTxt[] = "memory copy";
static char _szMemcpyUsageTxt[] =
    "Usage: memcpy dst src size\n"
    "   dst, src and size must be multiple of 4\n";

static int _regsetHandler(CLI_t *pCli, char *p);
static char _szRegsetHelpTxt[] = "set register value";
static char _szRegsetUsageTxt[] =
    "Usage: regset addr value\n"
    "   addr must be multiple of 4\n";

static int _reggetHandler(CLI_t *pCli, char *p);
static char _szReggetHelpTxt[] = "get register value";
static char _szReggetUsageTxt[] =
    "Usage: regget addr\n"
    "   addr must be multiple of 4\n";

#ifndef __I_SW_OS_G1__
#ifdef __FIXME__
static int _sleepHandler(CLI_t *pCli, char *p);
static char _szSleepHelpTxt[] = "enter sleep test";
static char _szSleepUsageTxt[] =
    "Usage: sleep\n";

static int _testoutHandler(CLI_t *pCli, char *p);
static char _szTestoutHelpTxt[] = "set 24-bit test-out";
static char _szTestoutUsageTxt[] =
    "Usage: testout bus24b_sel pad_map(1~6)\n";

static int _clkoutHandler(CLI_t *pCli, char *p);
static char _szClkoutHelpTxt[] = "set single clk out";
static char _szClkoutUsageTxt[] =
    "Usage: clkout num(0~23) divider(1, 4, 8, 16, 32, 64)\n";

static int _delayHandler(CLI_t *pCli, char *p);
static char _szDelayHelpTxt[] = "Delay in usecs";
static char _szDelayUsageTxt[] =
    "Usage: delay usecs\n"
    "   Stop system execution for \"usecs\" micro seconds.\n";
#endif

static CliParseToken_t _atCacheTbl[];
static char _szCacheHelpTxt[] = "Menu Cache";
static char _szCacheUsageTxt[] = "";

static CliParseToken_t _atICacheTbl[];
static char _szICacheHelpTxt[] = "Menu ICache";
static char _szICacheUsageTxt[] = "";
#endif

#define IS_WHITE(x)                 ( (x) == ' ' || (x) == '\t' )
#define IS_SPACE(x)                 IS_WHITE(x)
#define EAT_WHITE(x)                while( IS_WHITE(*(x))) x++;
//#define EAT_NON_WHITE(x)        while( !IS_WHITE(*(x))) x++;
#define EAT_NON_WHITE(x)            while( *(x)&&!IS_WHITE(*(x))) x++;
#define IS_A_DIGIT(x)               ((x >='0') && (x <='9'))
#define EAT_NON_WHITE_NON_DIGIT(x)  while( *(x)&&!IS_WHITE(*(x)) && !IS_A_DIGIT(*(x))) x++;
#define EAT_REST_STRING(x)        while( (*x) != '\0' && *(x) != '\"'  ) x++;

#if (WIFI_PORT == 1)
extern int UartCmd_NETCommands(CLI_t *pCli, char* szParam);
extern int UartCmd_WifiCommands(CLI_t *pCli, char* szParam);
int UartCmd_V4l(void *pCli, char* szParam)
{
#if defined (__RTK_OS__)
    char * pDropToken;
    //Consume token
    do{
        pDropToken = CliTokenPop(pCli);
    }while(pDropToken);
#else
    //TBD
    void dbg_dump_v4l(MMP_M_STREAMCB_CODEC codec);
    dbg_dump_v4l(0/*JPEG*/);//take szParam as parameter later
#endif
    return eCLI_PARSE_OK;
}

#if(WIFI_DRIVER_TYPE == WIFI_DRIVER_RTK)
extern void rtk_wifi_iwpriv(void *pCli, char *szParam);
#endif

#endif

void UartCmd_3DNR(CLI_t * pCli, char * p)
{
    u32     ul3DNR = 0;

    if(CliTokenCount(pCli) == 1)
    {
        if (CliTokenPopNum(pCli, &ul3DNR, 0) == eCLI_PARSE_OK) {
            if(ul3DNR) {
                printc( "\n 3DNR ON \n");
                MS_CAM20_SetEnSysMcnrMemory(0, 1);
            }
            else {
                printc( "\n 3DNR OFF \n");
                MS_CAM20_SetEnSysMcnrMemory(0, 0);
            }
        }
    }
}


#if defined(__VER_USB__) || defined(__VER_USBHOST__)
#include "mdl_hostuvc.h"
extern void UsbTest(u32 nSelect);
//extern int chip_storage_init(int);
//extern int chip_storage_stop(int);
//extern int chip_storage_test(void);
static int _usbHandler(CLI_t *pCli, char *p);
static char _szUsbHelpTxt[] = "USBH 123-Menu gogogo";
static char _szUsbUsageTxt[] = "";
#define PARSE_TOKEN_USBH_TEST \
    {"usbh",         _szUsbHelpTxt,      _szUsbUsageTxt,     _usbHandler,     NULL},
#else
#define PARSE_TOKEN_USBH_TEST
#endif

#if defined(__VER_FCIE__)
static char _szFcieHelpTxt[] = "SD driver test";
static char _szFcieUsageTxt[] =
    "Usage: sdr secidx seccnt miuaddr\r\n"
    "       sdw secidx seccnt miuaddr\r\n"
    "       sdinit\r\n"
    "       sdcdz\r\n";
extern CliParseToken_t g_atFcieMenuTbl[];

#define PARSE_TOKEN_FCIE_TEST   {"fcie", _szFcieHelpTxt, _szFcieUsageTxt, NULL, g_atFcieMenuTbl},
#else
#define PARSE_TOKEN_FCIE_TEST
#endif

#if defined(__VER_TIMER__)
extern CliParseToken_t g_atTimerMenuTbl[];
static char _szTimerMenuHelpTxt[] = "Menu Timer";
static char _szTimerMenuUsageTxt[] = "";
#define PARSE_TOKEN_TIMER_MENU \
    {"timer",          _szTimerMenuHelpTxt,   _szTimerMenuUsageTxt,  NULL,            g_atTimerMenuTbl},
#else
#define PARSE_TOKEN_TIMER_MENU
#endif

#if defined(__VER_IO__)
extern CliParseToken_t g_atIoMenuTbl[];
static char _szIoMenuHelpTxt[] = "Menu IO";
static char _szIoMenuUsageTxt[] = "";
#define PARSE_TOKEN_IO_MENU \
    {"io",          _szIoMenuHelpTxt,   _szIoMenuUsageTxt,  NULL,            g_atIoMenuTbl},
#else
#define PARSE_TOKEN_IO_MENU
#endif

#if defined(__VER_GPIO__)
extern CliParseToken_t g_atIOMenuTbl[];
static char _szIOMenuHelpTxt[] = "Menu IO";
static char _szIOMenuUsageTxt[] = "";
#define PARSE_TOKEN_GPIO_MENU \
    {"io",          _szIOMenuHelpTxt,   _szIOMenuUsageTxt,  NULL,            g_atIOMenuTbl},
#else
#define PARSE_TOKEN_GPIO_MENU
#endif

/// misc
#if defined(__VER_MISC__)
extern CliParseToken_t g_atMiscMenuTbl[];
static char _szMiscMenuHelpTxt[] = "Menu Misc";
static char _szMiscMenuUsageTxt[] = "";
#define PARSE_TOKEN_MISC_MENU \
    {"misc",          _szMiscMenuHelpTxt,   _szMiscMenuUsageTxt,  NULL,            g_atMiscMenuTbl},
#else
#define PARSE_TOKEN_MISC_MENU
#endif

#if defined(__VER_PADCTRL__)
extern CliParseToken_t g_atPadCtrlMenuTbl[];
static char _szPadCtrlMenuHelpTxt[] = "Menu Pad Ctrl";
static char _szPadCtrlMenuUsageTxt[] = "";
#define PARSE_TOKEN_PADCTRL_MENU \
    {"padctrl", _szPadCtrlMenuHelpTxt, _szPadCtrlMenuUsageTxt, NULL, g_atPadCtrlMenuTbl},
#else
#define PARSE_TOKEN_PADCTRL_MENU
#endif

#if defined(__VER_PADCTRL__)
extern CliParseToken_t g_atDipbMenuTbl[];
static char _szDipbMenuHelpTxt[] = "Menu Digital IO Pad Bouncing";
static char _szDipbMenuUsageTxt[] = "";
#define PARSE_TOKEN_DIPB_MENU \
    {"dipb", _szDipbMenuHelpTxt, _szDipbMenuUsageTxt, NULL, g_atDipbMenuTbl},
#else
#define PARSE_TOKEN_DIPB_MENU
#endif

#if defined(__VER_DMA__)
extern CliParseToken_t g_atDMAMenuTbl[];
#define PARSE_TOKEN_DMA_MENU \
    {"dma",          "",   "",  NULL,            g_atDMAMenuTbl},
#else
#define PARSE_TOKEN_DMA_MENU
#endif

#if 0//defined(__VER_DMA__)
extern CliParseToken_t g_atBDMAMenuTbl[];
#define PARSE_TOKEN_BDMA_MENU \
    {"bdma",          "",   "",  NULL,            g_atBDMAMenuTbl},
#else
#define PARSE_TOKEN_BDMA_MENU
#endif

#if defined(__VER_ASURA_PMU__)
extern CliParseToken_t g_atAsuraPMUMenuTbl[];
static char _AsuraPMUHelpTxt[] = "ASURA PMU driver test";
#define PARSE_TOKEN_ASURA_PMU_MENU \
    {"asurapmu",     _AsuraPMUHelpTxt,   "",  NULL,            g_atAsuraPMUMenuTbl},
#else
#define PARSE_TOKEN_ASURA_PMU_MENU
#endif

#if defined(__VER_DMA2D__)
extern CliParseToken_t g_atDMA2DMenuTbl[];
#define PARSE_TOKEN_DMA2D_MENU \
    {"dma2d",          "",   "",  NULL,            g_atDMA2DMenuTbl},
#else
#define PARSE_TOKEN_DMA2D_MENU
#endif


#if defined(__VER_DISP__)

extern CliParseToken_t g_atDispMenuTbl[];
static char _szDispMenuHelpTxt[] = "Menu DISP";
static char _szDispMenuUsageTxt[] = "";
#define PARSE_TOKEN_DISP_MENU \
    {"disp",          _szDispMenuHelpTxt,   _szDispMenuUsageTxt,  NULL,            g_atDispMenuTbl},

#else
#define PARSE_TOKEN_DISP_MENU
#endif

#if defined(__VER_SENSOR_IF__)

extern CliParseToken_t g_atSensorIFMenuTbl[];
static char _szSensorIFMenuHelpTxt[] = "Menu Sensor IF";
static char _szSensorIFMenuUsageTxt[] = "";
#define PARSE_TOKEN_SENSOR_IF_MENU \
    {"sensorIF",          _szSensorIFMenuHelpTxt,   _szSensorIFMenuUsageTxt,  NULL,            g_atSensorIFMenuTbl},

#else
#define PARSE_TOKEN_SENSOR_IF_MENU
#endif


#if defined(__VER_IMAGE__)

extern CliParseToken_t g_atImageMenuTbl[];
static char _szImageMenuHelpTxt[] = "Menu IMAGE";
static char _szImageMenuUsageTxt[] = "";
#define PARSE_TOKEN_IMAGE_MENU \
    {"image",          _szImageMenuHelpTxt,   _szImageMenuUsageTxt,  NULL,            g_atImageMenuTbl},

#else
#define PARSE_TOKEN_IMAGE_MENU
#endif

#if defined(__VER_JPE__)
extern CliParseToken_t g_atJPEMenuTbl[];
#define PARSE_TOKEN_JPE_MENU \
    {"jpe",          "Menu JPE",   "",  NULL,            g_atJPEMenuTbl},
#else
#define PARSE_TOKEN_JPE_MENU
#endif

#if defined(__VER_JPEMID__)
extern CliParseToken_t g_atJPEMIDMenuTbl[];
static char _szJPEMIDMenuHelpTxt[] = "Menu JPEMID";
static char _szJPEMIDMenuUsageTxt[] = "";
#define PARSE_TOKEN_JPEMID_MENU \
    {"jpemid", "_szJPEMIDMenuHelpTxt", "_szJPEMIDMenuUsageTxt",  NULL, g_atJPEMIDMenuTbl},
#else
#define PARSE_TOKEN_JPEMID_MENU
#endif

#if defined(__VER_JPD__)
extern CliParseToken_t g_atJPDMenuTbl[];
#define PARSE_TOKEN_JPD_MENU \
    {"jpd",          "",   "",  NULL,            g_atJPDMenuTbl},
#else
#define PARSE_TOKEN_JPD_MENU
#endif

#if defined(__VER_SPI__)
extern CliParseToken_t g_atSpiMenuTbl[];
static char _szSpiMenuHelpTxt[] = "Menu SPI";
static char _szSpiMenuUsageTxt[] = "";
#define PARSE_TOKEN_SPI_MENU \
    {"spi",          _szSpiMenuHelpTxt,   _szSpiMenuUsageTxt,  NULL,            g_atSpiMenuTbl},
#else
#define PARSE_TOKEN_SPI_MENU
#endif

#if defined(__VER_SPINAND__)
extern CliParseToken_t g_atSpinandMenuTbl[];
static char _szSpinandMenuHelpTxt[] = "Menu SPINAND";
static char _szSpinandMenuUsageTxt[] = "";
#define PARSE_TOKEN_SPINAND_MENU \
    {"spinand",          _szSpinandMenuHelpTxt,   _szSpinandMenuUsageTxt,  NULL,            g_atSpinandMenuTbl},
#else
#define PARSE_TOKEN_SPINAND_MENU
#endif

#if defined(__VER_SCL__)
extern CliParseToken_t g_atSclMenuTbl[];
static char _szSclMenuHelpTxt[] = "Menu SCL";
static char _szSclMenuUsageTxt[] = "";

#define PARSE_TOKEN_SCL_MENU \
    {"scl",          _szSclMenuHelpTxt,  _szSclMenuUsageTxt,  NULL,            g_atSclMenuTbl},
#else
#define PARSE_TOKEN_SCL_MENU
#endif

#if defined(__VER_GOP__)
extern CliParseToken_t g_atGopMenuTbl[];
static char _szGopMenuHelpTxt[] = "Menu Gop";
static char _szGopMenuUsageTxt[] = "";

#define PARSE_TOKEN_GOP_MENU \
    {"gop",          _szGopMenuHelpTxt,  _szGopMenuUsageTxt,  NULL,            g_atGopMenuTbl},
#else
#define PARSE_TOKEN_GOP_MENU

#endif

#if defined(__VER_PNL__)
extern CliParseToken_t g_atPnlMenuTbl[];
static char _szPnlMenuHelpTxt[] = "Menu Pnl";
static char _szPnlMenuUsageTxt[] = "";

#define PARSE_TOKEN_PNL_MENU \
    {"pnl",          _szPnlMenuHelpTxt,  _szPnlMenuUsageTxt,  NULL,            g_atPnlMenuTbl},
#else
#define PARSE_TOKEN_PNL_MENU
#endif

#if defined(__VER_PNL__)
extern CliParseToken_t  g_atMVOPMenuTbl[];
static char _szMVOPMenuHelpTxt[] = "Menu MVOP";
static char _szMVOPMenuUsageTxt[] = "";

#define PARSE_TOKEN_MVOP_MENU \
    {"MVOP",          _szMVOPMenuHelpTxt,  _szMVOPMenuUsageTxt,  NULL,            g_atMVOPMenuTbl},
#else
#define PARSE_TOKEN_MVOP_MENU
#endif



#if defined(__VER_MIPI_DSI__)

extern CliParseToken_t g_atMIPIDSIMenuTbl[];
static char _szDSIMenuHelpTxt[] = "Menu DISP";
static char _szDSIMenuUsageTxt[] = "";
#define PARSE_TOKEN_MIPI_DSI_MENU \
    {"mipi",          _szDSIMenuHelpTxt,   _szDSIMenuUsageTxt,  NULL,            g_atMIPIDSIMenuTbl},

#else
#define PARSE_TOKEN_MIPI_DSI_MENU
#endif


#if 1
extern CliParseToken_t  g_atDecSclMenuTbl[];
static char _szDecSclMenuHelpTxt[] = "Dec SCL";
static char _szDecSclMenuUsageTxt[] = "";
#define PARSE_TOKEN_DEC_SCL_MENU \
    {"decscl",          _szDecSclMenuHelpTxt,   _szDecSclMenuUsageTxt,  NULL,            g_atDecSclMenuTbl},
#else
#define PARSE_TOKEN_DEC_SCL_MENU
#endif

#if defined(__VER_SENSORIF__)
extern CliParseToken_t g_atSIFMenuTbl[];
#define PARSE_TOKEN_SIF_MENU \
    {"sif",          "",  "",  NULL,            g_atSIFMenuTbl},
#else
#define PARSE_TOKEN_SIF_MENU
#endif

#if defined(__VER_I2C__)
extern CliParseToken_t g_atI2cMenuTbl[];
#define PARSE_TOKEN_I2C_TEST \
    {"i2c", "Menu I2C",  "",  NULL, g_atI2cMenuTbl},
#else
#define PARSE_TOKEN_I2C_TEST
#endif

#if defined(__VER_VIF__)
extern CliParseToken_t g_atVifMenuTbl[];
#define PARSE_TOKEN_VIF_TEST \
    {"vif", "Menu Vif",  "",  NULL, g_atVifMenuTbl},
#else
#define PARSE_TOKEN_VIF_TEST
#endif


#if defined(__VER_AUX__)
extern CliParseToken_t g_atAuxMenuTbl[];
static char _szAuxMenuHelpTxt[] = "Menu AUX";
static char _szAuxMenuUsageTxt[] = "";
#define PARSE_TOKEN_AUX_MENU \
    {"aux", _szAuxMenuHelpTxt, _szAuxMenuUsageTxt, NULL, g_atAuxMenuTbl},
#else
#define PARSE_TOKEN_AUX_MENU
#endif

#if defined(__VER_RGBLED__)
extern CliParseToken_t g_atAsuraRGBLEDMenuTbl[];
#define PARSE_TOKEN_RGBLED_MENU \
    {"rgbled", "", "", NULL, g_atAsuraRGBLEDMenuTbl},
#else
#define PARSE_TOKEN_RGBLED_MENU
#endif

#if defined(__VER_B3_PMU__)
extern CliParseToken_t g_atB3PMUMenuTbl[];
#define PARSE_TOKEN_B3PMU_MENU \
    {"B3PMU", "", "", NULL, g_atB3PMUMenuTbl},
#else
#define PARSE_TOKEN_B3PMU_MENU
#endif


/* ++ 4579 B3 ISW_RTC 4579 ++ */
#if defined(__VER_RTC__)

extern CliParseToken_t g_atRtcMenuTbl[];
static char _szRtcMenuHelpTxt[] = "Menu RTC";
static char _szRtcMenuUsageTxt[] = "";
#define PARSE_TOKEN_RTC_MENU \
    {"rtc",          _szRtcMenuHelpTxt,   _szRtcMenuUsageTxt,  NULL,            g_atRtcMenuTbl},
#else
#define PARSE_TOKEN_RTC_MENU
#endif
/* -- 4579 B3 ISW_RTC 4579 -- */

#if defined(__VER_VDR__)
extern CliParseToken_t g_atVDRMenuTbl[];
static char _szVdrMenuHelpTxt[] = "VDR help";
static char _szVdrMenuUsageTxt[] = "Record H263I from sensor\n";
#define PARSE_TOKEN_VDR_MENU \
    {"vdr",          _szVdrMenuHelpTxt,   _szVdrMenuUsageTxt,  NULL,            g_atVDRMenuTbl},
#else
#define PARSE_TOKEN_VDR_MENU
#endif

#if defined(__VER_AUD__)
extern CliParseToken_t g_atAudMenuTbl[];
static char _szAudMenuHelpTxt[] = "Menu Audio";
static char _szAudMenuUsageTxt[] = "";
#define PARSE_TOKEN_AUD_MENU \
    {"audio",       _szAudMenuHelpTxt,   _szAudMenuUsageTxt,  NULL,            g_atAudMenuTbl},
#else
#define PARSE_TOKEN_AUD_MENU
#endif

#if defined(__VER_ZLIB__)
extern CliParseToken_t g_atZlibMenuTbl[];
static char _szZlibMenuHelpTxt[] = "Menu Zlib";
static char _szZlibMenuUsageTxt[] = "";
#define PARSE_TOKEN_ZLIB_MENU \
    {"zlib",       _szZlibMenuHelpTxt,   _szZlibMenuUsageTxt,  NULL,            g_atZlibMenuTbl},
#else
#define PARSE_TOKEN_ZLIB_MENU
#endif

#if defined(__VER_UART__)
extern CliParseToken_t g_atUartMenuTbl[];
static char _szUartMenuHelpTxt[] = "Menu UART";
static char _szUartMenuUsageTxt[] = "";
#define PARSE_TOKEN_UART_MENU \
    {"uart", _szUartMenuHelpTxt, _szUartMenuUsageTxt, NULL, g_atUartMenuTbl},
#else
#define PARSE_TOKEN_UART_MENU
#endif

#if defined(__VER_KEYPAD__)
extern CliParseToken_t g_atKeypadMenuTbl[];
static char _szKeypadMenuHelpTxt[] = "Menu Keypad";
static char _szKeypadMenuUsageTxt[] = "";
#define PARSE_TOKEN_KEYPAD_MENU \
    {"keypad",       _szKeypadMenuHelpTxt,   _szKeypadMenuUsageTxt,  NULL,            g_atKeypadMenuTbl},
#else
#define PARSE_TOKEN_KEYPAD_MENU
#endif

#if defined(__VER_FCS_GEA__)
extern CliParseToken_t g_atAsicMenuTbl[];
static char _szAsicMenuHelpTxt[] = "Menu ASIC";
static char _szAsicMenuUsageTxt[] = "";
#define PARSE_TOKEN_ASIC_MENU \
    {"asic",          _szAsicMenuHelpTxt,   _szAsicMenuUsageTxt,  NULL,            g_atAsicMenuTbl},
#else
#define PARSE_TOKEN_ASIC_MENU
#endif

#if defined(__VER_CMU__)
extern CliParseToken_t g_atCmuMenuTbl[];
#define PARSE_TOKEN_CMU_MENU \
    {"cmu", "",  "",  NULL, g_atCmuMenuTbl},
#else
#define PARSE_TOKEN_CMU_MENU
#endif

#if 0//defined(__VER_CLKGEN__)
extern CliParseToken_t g_atClkgenMenuTbl[];
#define PARSE_TOKEN_CLKGEN_MENU \
    {"clkgen", "Menu Clkgen",  "",  NULL, g_atClkgenMenuTbl},
#else
#define PARSE_TOKEN_CLKGEN_MENU
#endif

#if defined(__VER_PLL__)
extern CliParseToken_t g_atPllMenuTbl[];
#define PARSE_TOKEN_PLL_MENU \
    {"pll", "",  "",  NULL, g_atPllMenuTbl},
#else
#define PARSE_TOKEN_PLL_MENU
#endif

#if defined(__VER_DYNSCL__)
extern int DynSclTest(CLI_t * pCli, char * p);
#define PARSE_TOKEN_DYNSCK_TEST \
    {"dynscl", "",  "",  DynSclTest, NULL},
#else
#define PARSE_TOKEN_DYNSCK_TEST
#endif

#if defined(__VER_INTC__)
extern CliParseToken_t g_atIntcMenuTbl[];
#define PARSE_TOKEN_INTC_MENU \
    {"intc", "",  "",  NULL, g_atIntcMenuTbl},
#else
#define PARSE_TOKEN_INTC_MENU
#endif

#if defined(__VER_EXTINT__)
extern CliParseToken_t g_atExtintMenuTbl[];
#define PARSE_TOKEN_EXTINT_MENU \
    {"extint", "",  "",  NULL, g_atExtintMenuTbl},
#else
#define PARSE_TOKEN_EXTINT_MENU
#endif

#if defined(__VER_DMC__)
extern CliParseToken_t g_atDmcMenuTbl[];
#define PARSE_TOKEN_DMC_MENU \
    {"extint", "",  "",  NULL, g_atDmcMenuTbl},
#else
#define PARSE_TOKEN_DMC_MENU
#endif

#if !defined (__ISW_8533D__) && !defined(__ISW_8532B__) && !defined(__ISW_8556R__) && !defined(__ISW_INFINITY__)
#if defined(__VER_ASURA_ADC__)
extern CliParseToken_t g_atADCMenuTbl[];
#define PARSE_TOKEN_ASURA_ADC_TEST \
    {"asura_adc", "",  "",NULL, g_atADCMenuTbl},
#endif
#else
#define PARSE_TOKEN_ASURA_ADC_TEST
#endif

#if defined(__VER_FMRX__)
extern CliParseToken_t g_atFmrxMenuTbl[];
#define PARSE_TOKEN_FMRX_TEST \
    { "fmrx", "", "", NULL, g_atFmrxMenuTbl },
#else
#define PARSE_TOKEN_FMRX_TEST
#endif

#if defined(__VER_EMI__)
extern CliParseToken_t g_atEmiMenuTbl[];
#define PARSE_TOKEN_EMI_TEST \
    { "emi", "", "", NULL, g_atEmiMenuTbl },
#else
#define PARSE_TOKEN_EMI_TEST
#endif


#if defined(__VER_ROMPATCH__)
extern CliParseToken_t g_atRomPatchMenuTbl[];
#define PARSE_TOKEN_ROMPATCH_MENU \
    {"rompatch", "",  "",  NULL, g_atRomPatchMenuTbl},
#else
#define PARSE_TOKEN_ROMPATCH_MENU
#endif


#if defined(__VER_DSP__)
extern CliParseToken_t g_atDSPMenuTbl[];
static char _szDSPMenuHelpTxt[] = "Menu DSP";
static char _szDSPMenuUsageTxt[] = "";
#define PARSE_TOKEN_DSP_MENU \
    {"DSP",       _szDSPMenuHelpTxt,   _szDSPMenuUsageTxt,  NULL,            g_atDSPMenuTbl},
#else
#define PARSE_TOKEN_DSP_MENU
#endif

#if defined(__VER_SHARED_IF__)
extern CliParseToken_t g_atSharedIFMenuTbl[];
static char _szSharedIFMenuHelpTxt[] = "Menu SharedIF";
static char _szSharedIFUsageTxt[] = "SharedIF";
#define PARSE_TOKEN_SHAREDIF_MENU \
    {"SharedIF",       _szSharedIFMenuHelpTxt,   _szSharedIFUsageTxt,  NULL,            g_atSharedIFMenuTbl},
#else
#define PARSE_TOKEN_SHAREDIF_MENU
#endif

#if defined(__VER_SIM__)
extern CliParseToken_t g_atSimMenuTbl[];
static char _szSimMenuHelpTxt[] = "SIM Menu";
static char _szSimMenuUsageTxt[] = "";
#define PARSE_TOKEN_SIM_MENU \
    {"sim",         _szSimMenuHelpTxt,      _szSimMenuUsageTxt,     NULL,     g_atSimMenuTbl},
#else
#define PARSE_TOKEN_SIM_MENU
#endif

#if defined(__VER_ISP__)
extern CliParseToken_t g_atIspMenuTbl[];
static char _szIspMenuHelpTxt[] = "Menu ISP";
static char _szIspMenuUsageTxt[] = "";
#define PARSE_TOKEN_ISP_MENU \
    {"isp",          _szIspMenuHelpTxt,   _szIspMenuUsageTxt,  NULL,            g_atIspMenuTbl},
#else
#define PARSE_TOKEN_ISP_MENU
#endif

#if defined(__VER_DIP__)
extern CliParseToken_t g_atDipMenuTbl[];
static char _szDipMenuHelpTxt[] = "Menu DIP";
static char _szDipMenuUsageTxt[] = "";
#define PARSE_TOKEN_DIP_MENU \
        {"dip", _szDipMenuHelpTxt, _szDipMenuUsageTxt, NULL, g_atDipMenuTbl},
extern CliParseToken_t g_atDipCtlMenuTbl[];
static char _szDipCtlMenuHelpTxt[] = "Menu DIPCTL";
static char _szDipCtlMenuUsageTxt[] = "";
#define PARSE_TOKEN_DIPCTL_MENU \
        {"dipctl", _szDipCtlMenuHelpTxt, _szDipCtlMenuUsageTxt, NULL, g_atDipCtlMenuTbl},
#else
#define PARSE_TOKEN_DIP_MENU
#define PARSE_TOKEN_DIPCTL_MENU
#endif

extern CliParseToken_t g_atCompMenuTbl[];
static char _szCompMenuHelpTxt[] = "Menu Comp";
static char _szCompMenuUsageTxt[] = "";
#define PARSE_TOKEN_COMP_MENU   \
    {"comput", _szCompMenuHelpTxt, _szCompMenuUsageTxt, NULL, g_atCompMenuTbl},
//
static char _szCheckSDHelpTxt[] = "CheckBinTest";
static char _szCheckSDUsageTxt[] = "";

extern int MfeEncodeFlow(CLI_t * pCli, char * p);
extern int JPDFuncTest(CLI_t * pCli, char * p);
extern int FuncTestH264(CLI_t * pCli, char * p);
extern int SarADCTest(CLI_t * pCli, char * p);
extern int Uartcmd_DumpADASPara(CLI_t * pCli, char * p);

static char _szMfeMenuHelpTxt[] = "Mfe Menu";
static char _szAitMenuHelpTxt[] = "AIT Menu";
static char _szfsHelpTxt[] = "FSTest Menu";
static char _szdcfdumpHelpTxt[] = "DCFDump Menu";
static char _szcheckFPSHelpTxt[] = "checkFPS Menu";
static char _szIspBypassHelpTxt[] = "IspBypass Menu";
static char _szdumprawdataHelpTxt[] = "dumprawdata Menu";
static char _szUSBHelpTxt[] = "USBTest Menu";
static char _szAdasHelpTxt[] = "ADAS Test";
static char _szUartDisableTxt[] = "UART_TURNOFF";
static char _szFPGAPIUMenuHelpTxt[] = "FPGA PIU Menu";
static char _szJpdMenuHelpTxt[] = "JPD Menu";
static char _szVdecMenuHelpTxt[] = "VDEC Menu";
static char _szPbMenuHelpTxt[] = "PB Menu";
static char _szSarMenuHelpTxt[] = "Sar ADC";
static char _szRTCPWCMenuHelpTxt[] = "hint : setrtc 2017 01 01 01 01 01";
static char _szRTCPWCSetMenuHelpTxt[] = "getrtc";
static char _szCompHelpTxt[] = "Component Tese Entry";
static char _szJpegHelpTxt[] = "Component Tese Entry";
static char _szAudioHelpTxt[] = "Component Tese Entry";
static char _szMfeMenuUsageTxt[] = "";
static char _szAitMenuUsageTxt[] = "";
static char _szfsUsageTxt[] = "";
static char _szdcfdumpUsageTxt[] = "";
static char _szcheckFPSUsageTxt[] = "";
static char _szIspBypassUsageTxt[] = "";
static char _szdumprawdataUsageTxt[] = "";
static char _szUSBUsageTxt[] = "";
static char _szAdasUsageTxt[] = "";
static char _szUartUsageTxt[] = "";
static char _szFPGAPIUMenuUsageTxt[] = "";
static char _szCompUsageTxt[] = "";
static char _szJpegUsageTxt[] = "";
static char _szAudioUsageTxt[] = "";
static char _szJpdMenuUsageTxt[] = "";
static char _szVdecMenuUsageTxt[] = "";
static char _szPbMenuUsageTxt[] = "";
static char _szSarAdcMenuUsageTxt[] = "";
static char _szRTCPWCMenuUsageTxt[] = "hint : setrtc 2017 01 01 01 01 01";
static char _szRTCPWCSetMenuUsageTxt[] = "getrtc";

int AitFlow(CLI_t * pCli, char * p)
{
#if defined(__MV5_FPGA__)
    //imi sram(0xa000_0000)
#define IMI_SRAM_BASE (0xA0000000)

    U32 sz = 128; //kB
    U32 ulLoop = 0, usPattern = 0x13572468;

    UartSendTrace("IMI_bist_manually begin...\r\n");
    for(ulLoop = 0; ulLoop < (sz * 1024); ulLoop += sizeof(U32)){
        if((ulLoop % 0x100)==0){
            UartSendTrace("Wr Addr = :0x%x\r\n", IMI_SRAM_BASE + ulLoop);
        }

        *((volatile U32 *)((volatile void *)(IMI_SRAM_BASE + ulLoop))) = ulLoop;
    }

    UartSendTrace("Start to verify...\r\n");
    //Read each DRAM address and compare the value with pattern value.
    for(ulLoop = 0; ulLoop < (sz * 1024); ulLoop += sizeof(U32))
    {
        if((ulLoop % 0x100)==0){
            UartSendTrace("Rd Addr = :0x%x\r\n", IMI_SRAM_BASE + ulLoop);
        }

        if(*((volatile U32 *)((volatile void *)(IMI_SRAM_BASE + ulLoop))) != ulLoop)
        {
            UartSendTrace("\r\n Compare MIU fail and break...\r\n");
            UartSendTrace(" Break point : Addr = :0x%x\r\n", IMI_SRAM_BASE + ulLoop);
            break;
        }
    }

    if(ulLoop != ((sz * 1024))){
        UartSendTrace("IMI_bist_manually fail!\r\n");
    }

    UartSendTrace("IMI_bist_manually OK!\r\n");

#else
    return 0;
#endif
}

#include "mmpf_adas.h"
int adas_test(CLI_t * pCli, char * p)
{
    UartSendTrace("Start adas test\r\n");
    adas_main();
    return 0;
}

void uart_off(void)
{
    (*(U8 *)(0x1F203D4C)) = 0x00; //bank0x101e offset0x53
}

extern void MS_SD_Verify_Entry(void);
int fs_test(CLI_t * pCli, char * p)
{
    int num;
    //volatile int val;

    UartSendTrace("Start MV5 FileSystem/Storage test20170710\r\n");
    UartSendTrace("===============================\n");
    UartSendTrace("==            Menu           ==\n");
    UartSendTrace("===============================\n");
    UartSendTrace("=[1] mmpf_sf.c verify\n");
    UartSendTrace("=[2] sf_misc.c verify\n");
    UartSendTrace("=[3] FileSystem verify\n");
    UartSendTrace("=[4] SD driver layer verify\n");
    UartSendTrace("=[5] SD HAL layer verify\n");
    UartSendTrace("=[6] SPI-NandFlash verify\n");
    UartSendTrace("=[7] SD Health Info verify\n");
    UartSendTrace("=[8] SD CID Info verify\n");
    UartSendTrace("=[0] Quit\n");
    UartSendTrace("===============================\n");
    do
    {
        UartSendTrace("==>");
        num = vm_atoi(wait_for_command());
        UartSendTrace("num: %x\r\n", num);
        switch(num)
        {
            case 1:
                sf_test();
                break;
            case 2:
                sfmisc_test();
                break;
            case 3:
                fs_main();
                break;
            case 4:
                sd_test();
                break;
            case 5:
                MS_SD_Verify_Entry();
                break;
            case 6:
                usb_test();
                break;
            case 7:
                sd_health_info();
                /* sd_health_info source code
                {
                    tyDevSMART DevSMART = {0x00};
                    
                    if(!MMPF_SD_GetHealthInfo(m_SDMMCArg,&DevSMART))
                    {
                        UartSendTrace("\r\nlongsys SD card health info struct:\r\n");   
                        UartSendTrace("DevSMART.dwDevSMARTTag = %#08x\r\n",DevSMART.dwDevSMARTTag);  
                        UartSendTrace("DevSMART.dwDevSMARTVersions = %#08x\r\n",DevSMART.dwDevSMARTVersions);  
                        UartSendTrace("DevSMART.dwXorValue = %#08x\r\n",DevSMART.dwXorValue);  
                        UartSendTrace("DevSMART.dwSizeOfDevSMART = %#08x\r\n",DevSMART.dwSizeOfDevSMART);  
                        UartSendTrace("DevSMART.dwOriginalBadBlock = %#08x\r\n",DevSMART.dwOriginalBadBlock);  
                        UartSendTrace("DevSMART.dwIncreaseBadBlock = %#08x\r\n",DevSMART.dwIncreaseBadBlock);  
                        UartSendTrace("DevSMART.lwWriteAllSectNum = %#08x\r\n",DevSMART.lwWriteAllSectNum);  
                        UartSendTrace("DevSMART.dwReplaceBlockLeft = %#08x\r\n",DevSMART.dwReplaceBlockLeft);  
                        UartSendTrace("DevSMART.dwDegreOfWear = %#08x\r\n",DevSMART.dwDegreOfWear);  
                        UartSendTrace("DevSMART.dwSectorTotal = %#08x\r\n",DevSMART.dwSectorTotal);  
                        UartSendTrace("DevSMART.dwRemainLifeTime = %#08x\r\n",DevSMART.dwRemainLifeTime);  
                        UartSendTrace("DevSMART.dwRemainWrGBNum = %#08x\r\n",DevSMART.dwRemainWrGBNum);  
                        UartSendTrace("DevSMART.dwLifeTimeTotal = %#08x\r\n",DevSMART.dwLifeTimeTotal);  
                    }
                    else
                    {
                        UartSendTrace("\r\MMPF_SD_GetHealthInfo FAIL\r\n");
                    }
                }
                */
                break;
            case 8:
                {
                    MMP_BYTE CID[16] = {0x00};
                    int i = 0;
                    
                    if(!MMPS_FS_GetSDCID(AHC_SD_0,CID))
                    {
                        printc(FG_PURPLE("MMPS_FS_GetSDCID:"));
                        for(i = 0;i < 16;i++)
                        {
                            printc(FG_PURPLE("%02X "),CID[i]);
                        }
                        printc(FG_PURPLE("\r\n"));
                    }
                }
                break;
            default:
                break;
        }
    }while( 0 != num );
    return 0;
}

int usb_test(CLI_t * pCli, char * p)
{
    int num;

    UartSendTrace("Start MV5 USB Device test\r\n");
    UartSendTrace("===============================\n");
    UartSendTrace("==            Menu           ==\n");
    UartSendTrace("===============================\n");
    UartSendTrace("=[1] MSDC\n");
    UartSendTrace("=[2] UVC\n");
    UartSendTrace("=[0] Quit\n");
    UartSendTrace("===============================\n");
    do
    {
        UartSendTrace("==>");
        num = vm_atoi(wait_for_command());
        UartSendTrace("num: %x\r\n", num);
        switch(num)
        {
            case 1:
                AHC_USB_FunctionExit();
                UartSendTrace("====MSDC====\r\n");

                USBSelectModeMSDC(0,0);
                StateSwitchMode(UI_MSDC_STATE);
                break;
            case 2:
                AHC_USB_FunctionExit();
                UartSendTrace("====PCCAM====\r\n");

                USBSelectModePCam(0,0);         //about menu handle
                StateSwitchMode(UI_PCCAM_STATE);
                break;


            default:
                break;
        }
    }while( 0 != num );
    return 0;
}

extern MMP_ERR OpenScript(MMP_UBYTE ubIndex);
extern void MMPF_Sensor_AnaDecSrcTypeDetectTest(int nEnable);
extern void OpenJpgTest(void);

#include "component_cfg.h"

int Component_test(CLI_t * pCli, char * p)
{
    int num;

    UartSendTrace("Component test\r\n");
    UartSendTrace("===============================\n");
    UartSendTrace("==            Menu           ==\n");
    UartSendTrace("===============================\n");
    UartSendTrace("=[1] Preview start (Front cam)\n");
    UartSendTrace("=[2] Video record start\n");
    UartSendTrace("=[0] Quit\n");
    UartSendTrace("===============================\n");

    do
    {
        UartSendTrace("==>");
        num = vm_atoi(wait_for_command());
        UartSendTrace("num: %x\r\n", num);

        switch(num) {
            case 0:
                MMPF_Sensor_AnaDecSrcTypeDetectTest(0);
                break;
            case 1:
                MMPF_Sensor_AnaDecSrcTypeDetectTest(1);
                break;
            case 2:
                CloseScript(COMPO_SCRIPT_JPG_PB_R);
                OpenJpgTest();
                break;
            case 8://open DISPLAY only
                OpenScript(COMPO_SCRIPT_DISPLAY);
                break;
            default:
                break;
        }
    } while( 0 != num );

    return 0;
}
//
int MV5_CheckFPS_enable(CLI_t * pCli, char * p)
{
    u8 CH;
    int num;
    //volatile int val;

    UartSendTrace("Set channel\r\n");
    UartSendTrace("===============================\n");
    UartSendTrace("=[0] CH0\n");
    UartSendTrace("=[1] CH1\n");
    UartSendTrace("=[2] CH2\n");
    UartSendTrace("===============================\n");

    UartSendTrace("==>");
    CH = vm_atoi(wait_for_command());
    UartSendTrace("CH: %x\r\n", CH);

    UartSendTrace("CheckFPS_enable\r\n");
    UartSendTrace("===============================\n");
    UartSendTrace("=[0] disable FPS check\n");
    UartSendTrace("=[1] enable FPS check\n");
    UartSendTrace("===============================\n");

    UartSendTrace("==>");
    num = vm_atoi(wait_for_command());
    UartSendTrace("num: %x\r\n", num);
    switch(num)
    {
        case 0:
            SetCheckFPSEnable(CH, 0);
            break;
        case 1:
            SetCheckFPSEnable(CH, 1);
            break;
        default:
            break;
    }

    return 0;
}

int MV5_ispbypass(CLI_t * pCli, char * p)
{
    extern void ISP_BypassMode(void);
    ISP_BypassMode();
}


// dump raw data ver1.0, dump raw data from ISP input raw store, prm cam
int MV5_DumpRawData(CLI_t * pCli, char * p)
{
	#define RAWDATA_FILENAME_CH0 "SD:\\RawData_CH"
	#define RAWDATA_FILEEXT ".bin"
	int     err;
	u32     ulFileID;
	u32     u32RawStoreBufAddr = 0;
	int     ulch;
	u8      ubchstr;
	u8      ubFilename[64];
	
	UartSendTrace("Dump raw data Select channel\r\n");
    UartSendTrace("===============================\n");
    UartSendTrace("=[0] CH0\n");
    UartSendTrace("=[1] CH1\n");
    UartSendTrace("===============================\n");
	if(ulch > 2){
		return 1;
	}
	UartSendTrace("==>");
    ulch = vm_atoi(wait_for_command());
    UartSendTrace("ch: %x\r\n", ulch);
	MEMCPY( ubFilename, RAWDATA_FILENAME_CH0, STRLEN(RAWDATA_FILENAME_CH0));
	sprintf(&ubchstr, "%d", ulch);
	STRCAT(ubFilename, &ubchstr); 
	STRCAT(ubFilename, RAWDATA_FILEEXT);
	
	err = MMPS_FS_FileOpen((INT8 *)ubFilename, strlen(ubFilename), "a+b", strlen("a+b"), &ulFileID);

	if (err != MMP_ERR_NONE){
        UartSendTrace("ERR:file open fails...\r\n");
        return 1;
    }
    else{
        UartSendTrace("File open : %s\r\n", ubFilename);
    }
	u32RawStoreBufAddr = cameraGetRawStoreBufAddr(ulch);
	UartSendTrace("DumpRawData addr 0x%x\r\n", u32RawStoreBufAddr);
	if(err == AHC_ERR_NONE)
    {
        UINT32   ulWriteCount;
        //write
        MMPS_FS_FileWrite(ulFileID, (u8*)u32RawStoreBufAddr, 1952 * 1099 * 2, &ulWriteCount);
        //close
        MMPS_FS_FileClose(ulFileID);
    }

	return 0;
}
//
int MV5_JPE_test(CLI_t * pCli, char * p)
{
    int num;

    UartSendTrace("MV5_JPE_test\r\n");
    UartSendTrace("===============================\n");
    UartSendTrace("==            Menu           ==\n");
    UartSendTrace("===============================\n");
    UartSendTrace("=[1] JPE driver capture(1920x1080)\n");
    UartSendTrace("=[2] JPE component + JPE queue capture(1920x1080)\n");
    UartSendTrace("=[0] Quit\n");
    UartSendTrace("===============================\n");
    do
    {
        UartSendTrace("==>");
        num = vm_atoi(wait_for_command());
        UartSendTrace("num: %x\r\n", num);
        switch(num) {
            case 2:
                //Component_JPE_UnitTest();
                break;
            default:
                break;
        }
    } while( 0 != num );

    return 0;
}

int MV5_AUD_test(CLI_t * pCli, char * p)
{
    int num;

    UartSendTrace("MV5_AUD_test\r\n");
    UartSendTrace("===============================\n");
    UartSendTrace("==            Menu           ==\n");
    UartSendTrace("===============================\n");
    UartSendTrace("=[1] AUD component(AFE in with ADPCM codec)\n");
    UartSendTrace("=[2] AUD component(AFE out with ADPCM codec)\n");
    UartSendTrace("=[0] Quit\n");
    UartSendTrace("===============================\n");
    do
    {
        UartSendTrace("==>");
        num = vm_atoi(wait_for_command());
        UartSendTrace("num: %x\r\n", num);
        switch(num) {
            case 1:
                Component_AUD_UnitTest(1);
                break;
            case 2:
                Component_AUD_UnitTest(2);
                break;
            default:
                break;
        }
    } while( 0 != num );

    return 0;
}

int MV5_DT_TestCheckBinFileExist(CLI_t * pCli, char * p)
{
    int Err;

    Err = SDUpdateCheckFileExisted(SD_FW_UPDATER_BIN_NAME);

    return Err;
}

int MV5_PB_test(CLI_t * pCli, char * p)
{
    int num;

    UartSendTrace("MV5_PB_test\r\n");
    UartSendTrace("===============================\n");
    UartSendTrace("==            Menu           ==\n");
    UartSendTrace("===============================\n");
    UartSendTrace("=[1] PB_N(480x854)\n");
    UartSendTrace("=[2] PB_R(480x854)\n");
    UartSendTrace("=[0] Quit\n");
    UartSendTrace("===============================\n");

    do
    {
        UartSendTrace("==>");
        num = vm_atoi(wait_for_command());
        UartSendTrace("num: %x\r\n", num);
        switch(num) {
            case 1:
                OpenScript(COMPO_SCRIPT_MOVIE_PB_N);
                break;
            case 2:
                OpenScript(COMPO_SCRIPT_MOVIE_PB_R);
                break;
            default:
                break;
        }
    } while( 0 != num );

    return 0;
}

int RTCPWCGet(CLI_t * pCli, char * p)
{
    u16 uwYear,uwMonth,uwDay,uwDayInWeek,uwHour,uwMinute,uwSecond;
    bool success;
    u8 ubAmOrPm = 0;
    u8 b_12FormatEn = 0;

    MMPS_RTC_Initialize();
    AHC_RTC_UpdateTime();
    AHC_SetParam(PARAM_ID_USE_RTC,1);
    success = AHC_GetClock( &uwYear, &uwMonth, &uwDay, &uwDayInWeek, &uwHour, &uwMinute, &uwSecond, &ubAmOrPm, &b_12FormatEn);

    if(success)
    {
        UartSendTrace("Get RTC time yy/mm/dd h:min:sec: %d/%d/%d %d:%d:%d\r\n",uwYear,uwMonth,uwDay,uwHour,uwMinute,uwSecond);
    }
    else
    {
        UartSendTrace("Get RTC value Fail!\r\n");
    }
    return 0;
}

#if GSENSOR_CONNECT_ENABLE
#include "GSensor_ctrl.h"
extern AHC_BOOL  dump_GValues;
extern AHC_BOOL  dump_GValues_osd;
int UartCmd_Gsens(CLI_t * pCli, char * p)//or_Test( char* szParam )
{
    if(AHC_Gsensor_Module_Attached())
    {
        UINT8           i;
        UINT16          ubvalue;
        UINT16          ubReg, ubRegValue;

        if (CliTokenPopNum(pCli, &i, 0) != eCLI_PARSE_OK)
            goto GSENSOR_TEST_QUIT;
        if (CliTokenPopNum(pCli, &ubReg, 0) != eCLI_PARSE_OK)
            goto GSENSOR_TEST_QUIT;
        if (CliTokenPopNum(pCli, &ubRegValue, 0) != eCLI_PARSE_OK)
            goto GSENSOR_TEST_QUIT;

        printc("%d, %x, %x\r\n", i, ubReg, ubRegValue);
        switch(i)
        {
        case 0:
            //AHC_Gsensor_IOControl(GSNR_CMD_RESET, NULL);
        break;
        case 1:
            //AHC_Gsensor_Initial();
        break;
        case 2:
            AHC_Gsensor_WriteRegister(ubReg,ubRegValue);
            AHC_Gsensor_ReadRegister(ubReg,&ubvalue);
            printc("Set Gsensor Reg : 0x%x, Value: 0x%x",ubReg, ubvalue);
        break;
        case 3:
            AHC_Gsensor_ReadRegister(ubReg,&ubvalue);
            printc("Read Gsensor Reg : 0x%x, Value: 0x%x",ubReg, ubvalue);
        break;
        case 4:
            if(dump_GValues)
            dump_GValues = AHC_FALSE;
            else
            dump_GValues = AHC_TRUE;
        break;
        case 5:
            //AHC_Gsensor_Register();
            break;
        case 6:
            //AHC_Gsensor_UnRegister();
            break;
        case 7:
            if(dump_GValues_osd)
            dump_GValues_osd = AHC_FALSE;
            else
            dump_GValues_osd = AHC_TRUE;
        break;
        }
    }
    else
    {
GSENSOR_TEST_QUIT:
        printc("Support no Gsensor module in this project!\r\n");
    }

    return 0;
}
#endif

int RTCPWCSet(CLI_t * pCli, char * p)
{
    if(CliTokenCount(pCli) == 6)
    {
        u16 uwYear,uwMonth,uwDay,uwDayInWeek,uwHour,uwMinute,uwSecond;
        bool success;
        u8 b_12FormatEn = 0;
        u8 ubAmOrPm = 0;

        uwDayInWeek = 0;

        if (CliTokenPopNum(pCli, &uwYear, 0) != eCLI_PARSE_OK)
            goto RTCPWC_TEST_QUIT;
        if (CliTokenPopNum(pCli, &uwMonth, 0) != eCLI_PARSE_OK)
            goto RTCPWC_TEST_QUIT;
        if (CliTokenPopNum(pCli, &uwDay, 0) != eCLI_PARSE_OK)
            goto RTCPWC_TEST_QUIT;
        if (CliTokenPopNum(pCli, &uwHour, 0) != eCLI_PARSE_OK)
            goto RTCPWC_TEST_QUIT;
        if (CliTokenPopNum(pCli, &uwMinute, 0) != eCLI_PARSE_OK)
            goto RTCPWC_TEST_QUIT;
        if (CliTokenPopNum(pCli, &uwSecond, 0) != eCLI_PARSE_OK)
            goto RTCPWC_TEST_QUIT;

        MMPS_RTC_Initialize();
        AHC_SetParam(PARAM_ID_USE_RTC,1);
        success = AHC_SetClock(uwYear,  uwMonth,  uwDay, uwDayInWeek, uwHour,  uwMinute,  uwSecond, ubAmOrPm, b_12FormatEn);
        if(success)
        {
            UartSendTrace("Set RTC time yy/mm/dd h:min:sec: %d/%d/%d/ %d:%d:%d\r\n",uwYear,uwMonth,uwDay,uwHour,uwMinute,uwSecond);
        }
        else
        {
            UartSendTrace("RTC Setting Fail!\r\n");
        }
    }
    else
    {
RTCPWC_TEST_QUIT:
        UartSendTrace("Bad Parameters ,Correct : %s\r\n", _szRTCPWCMenuUsageTxt);
    }

    return 0;
}

#if defined(__MV5_FPGA__)
//FPGA PIU test codeadas_test
int FPGA_PIU_Test(CLI_t * pCli, char * p)
{
#define RIU_BASE_ADDR           0x1F000000
#define MIU0_RIU_PMTOP                      0x001E   //Mercury5
#define MHal_MIU_ReadReg16(u32bank, u32reg ) *( ( volatile U16* ) (U32)(RIU_BASE_ADDR + (u32bank)*0x100*2 + ((u32reg) << 1)) )
#define MHal_MIU_WritReg16(u32bank, u32reg, u16val ) *( ( volatile U16* ) (U32)(RIU_BASE_ADDR + (u32bank)*0x100*2 + ((u32reg) << 1))  ) = (u16val)

    U16 u16RegMiuTop;
    U16 u16RegMiuOffset;
    U16 u16RegVal0;

    //MMP_ERR sRet;
    //sRet = MMPD_DSC_SetRingBuffer(0x10002000, 0x5000, 0x6000, 0x10);

    //Read Chip ID. The value is 0xD9.
    u16RegMiuTop = MIU0_RIU_PMTOP;
    u16RegMiuOffset = 0x00;
    u16RegVal0 = MHal_MIU_ReadReg16(u16RegMiuTop, u16RegMiuOffset);
    UartSendTrace("Chip ID:0x%x\r\n", u16RegVal0);

    //Read Chip Revision / Chip Version. The value is 0x00 on FPGA.
    u16RegMiuOffset = 0x01;
    u16RegVal0 = MHal_MIU_ReadReg16(u16RegMiuTop, u16RegMiuOffset);
    UartSendTrace("Chip Revision / Chip Version:0x%x\r\n", u16RegVal0);

    //Read dummy register for HW ECO only (default low).
    u16RegMiuTop = 0x1311;
    u16RegMiuOffset = 0x00;
    u16RegVal0 = MHal_MIU_ReadReg16(u16RegMiuTop, u16RegMiuOffset);
    UartSendTrace("dummy register init:0x%x\r\n", u16RegVal0);

    u16RegVal0 = 0xA301;
    MHal_MIU_WritReg16(u16RegMiuTop, u16RegMiuOffset, u16RegVal0);
    //u16RegVal0 = 0x0;
    u16RegVal0 = MHal_MIU_ReadReg16(u16RegMiuTop, u16RegMiuOffset);
    UartSendTrace("dummy register test:0x%x\r\n", u16RegVal0);

    return 0;
}

int GenericTimerTestFlow(CLI_t * pCli, char * p)
{
    int num;
    volatile int val;
    UartSendTrace("===============================\n");
    UartSendTrace("==            Menu           ==\n");
    UartSendTrace("===============================\n");
    UartSendTrace("=[1] Set Timer register\n");
    UartSendTrace("=[2] GetTime value\n");
    UartSendTrace("=[3] clear Time register\n");
    UartSendTrace("=[0] Quit\n");
    UartSendTrace("===============================\n");
    do
    {
        UartSendTrace("==>");
        num = vm_atoi(wait_for_command());
        UartSendTrace("num: %x\r\n", num);
        switch(num)
        {
            case 1:
                val = 0xAFFFFFF;
                __asm__("mcr p15,0,%0,c14,c2,0"::"r"(val):);
                __asm__("mcr p15,0,%0,c14,c3,0"::"r"(val):);
                val = 1;
                __asm__("mcr p15,0,%0,c14,c2,1"::"r"(val):);
                __asm__("mcr p15,0,%0,c14,c3,1"::"r"(val):);
                break;
            case 2:
                val = 0x55AA;
                __asm__("mrc p15,0,%0,c14,c2,0":"=r"(val)::);
                UartSendTrace("TVAL: %x\r\n", val);
                __asm__("mrc p15,0,%0,c14,c3,0":"=r"(val)::);
                 UartSendTrace("TVAL: %x\r\n", val);

                val = 0x55AA;
                __asm__("mrc p15,0,%0,c14,c2,1":"=r"(val)::);
                UartSendTrace("TCTL: %x\r\n", val);
                __asm__("mrc p15,0,%0,c14,c3,1":"=r"(val)::);
                UartSendTrace("TCTL: %x\r\n", val);

                break;
            case 3:
                val = 0x5;
                __asm__("mcr p15,0,%0,c14,c2,1"::"r"(val):);
                __asm__("mcr p15,0,%0,c14,c3,1"::"r"(val):);
                break;
            default:
                break;
        }
    }while( 0 != num );
    return 0;
}
#endif //#if defined(__MV5_FPGA__)


int KeyPadTest(CLI_t * pCli, char * p)
{
    u32 nPara0;

    if(CliTokenCount(pCli) == 1)
    {
        if (CliTokenPopNum(pCli, &nPara0, 0) == eCLI_PARSE_OK)
            SetKeyPadEvent(nPara0);
    }
    return 0;
}

int UartCmd_Test(CLI_t * pCli, char * p)
{
    int i;
    int iTokenCount = CliTokenCount(pCli);
    u32 uiParam[6] = {0};

    if ( iTokenCount > 6 ) {
        printc("Too many parameters!!\r\n");
        return 0;
    }

    for ( i=0; i<iTokenCount; i++ ) {
        CliTokenPopNum(pCli, &uiParam[i], 0);
    }

    printc("UartCmd_Test[%d]: %d %d %d %d %d %d\r\n", iTokenCount, uiParam[0], uiParam[1], uiParam[2], uiParam[3], uiParam[4], uiParam[5]);

    switch( uiParam[0] )
    {
        case 0:
            {
            }
            break;

        case 1:
            {
            }
            break;

        case 2:
            {
            }
            break;
        case 3:
            {
            }
            break;

        case 4:
            {
            }
            break;

        case 5:
            {
            }
            break;
    }

    return 0;
}

struct miu_client{
    char* name;
    short bw_client_id;
    short bw_enabled;
    short bw_max;
    short bw_avg;
    short effi_avg;
    short effi_min;
//    short bw_val_thread;
};
static struct miu_client miu0_clients[] = {
        {"OVERALL   ",0x00,1,0,0},
        {"VOP       ",0x01,0,0,0},
        {"DIP       ",0x02,0,0,0},
        {"DEC_GOP1  ",0x03,0,0,0},
        {"DEC_GOP2  ",0x04,0,0,0},
        {"DEC_GOP3  ",0x05,0,0,0},
        {"LCD_STAT  ",0x06,0,0,0},
        {"SC1_DBG   ",0x07,0,0,0},
        {"CMDQ0     ",0x08,0,0,0},
        {"DMAGEN0   ",0x09,0,0,0},
        {"DECGOP4   ",0x0A,0,0,0},
        {"NA        ",0x0B,0,0,0},
        {"NA        ",0x0C,0,0,0},
        {"NA        ",0x0D,0,0,0},
        {"NA        ",0x0E,0,0,0},
        {"MBIST     ",0x0F,0,0,0},
        {"ISP_RAW0  ",0x10,0,0,0},
        {"ISP_RAW1  ",0x11,0,0,0},
        {"ISP_RAW2  ",0x12,0,0,0},
        {"ISP_DNR   ",0x13,0,0,0},
        {"ISP_ROT   ",0x14,0,0,0},
        {"ISP_STAB  ",0x15,0,0,0},
        {"ISP_HIST  ",0x16,0,0,0},
        {"ISP_MENU  ",0x17,0,0,0},
        {"CMDQ1     ",0x18,0,0,0},
        {"DMAGEN1   ",0x19,0,0,0},
        {"MCU_IF    ",0x1A,0,0,0},
        {"NA        ",0x1B,0,0,0},
        {"NA        ",0x1C,0,0,0},
        {"NA        ",0x1D,0,0,0},
        {"NA        ",0x1E,0,0,0},
        {"NA        ",0x1F,0,0,0},
        {"SC1_DNR   ",0x20,0,0,0},
        {"SC1_STAS  ",0x21,0,0,0},
        {"SC1_LDC   ",0x22,0,0,0},
        {"SC1_FRM   ",0x23,0,0,0},
        {"SC1_SNAP  ",0x24,0,0,0},
        {"SC2_FRM   ",0x25,0,0,0},
        {"GOP       ",0x26,0,0,0},
        {"R2_CPUI   ",0x27,0,0,0},
        {"R2_CPUD   ",0x28,0,0,0},
        {"CMDQ2     ",0x29,0,0,0},
        {"MCU_BDMA  ",0x2A,0,0,0},
        {"AESDMA    ",0x2B,0,0,0},
        {"USB20     ",0x2C,0,0,0},
        {"USB20H    ",0x2D,0,0,0},
        {"MIIC1     ",0x2E,0,0,0},
        {"NA        ",0x2F,0,0,0},
        {"MFE_FRM   ",0x30,0,0,0},
        {"MFE_BIT   ",0x31,0,0,0},
        {"JPE_BIT   ",0x32,0,0,0},
        {"JPE_FRM   ",0x33,0,0,0},
        {"HVD       ",0x34,0,0,0},
        {"HVD_BBU   ",0x35,0,0,0},
        {"JPD       ",0x36,0,0,0},
        {"BACH      ",0x37,0,0,0},
        {"BACH2     ",0x38,0,0,0},
        {"SD30      ",0x39,0,0,0},
        {"SDIO30    ",0x3A,0,0,0},
        {"FCIE5     ",0x3B,0,0,0},
        {"MIIC2     ",0x3C,0,0,0},
        {"MIIC3     ",0x3D,0,0,0},
        {"NA        ",0x3E,0,0,0},
        {"DIAMOND   ",0x3F,0,0,0},
        {"CPU       ",0x70,0,0,0},
};
unsigned long gmonitor_duration = 1000;
unsigned long gmonitor_interval = 14;

static void measure_all_show(void)
{
    int i=0, temp_loop_time=0;

    short temp_val=0;
    unsigned long total_temp;
    unsigned long deadline;

    for(i=0; i<(sizeof(miu0_clients)/sizeof(miu0_clients[0]));i++)
    {
        miu0_clients[i].effi_min=0x3ff;
        miu0_clients[i].effi_avg=0;
        miu0_clients[i].bw_avg=0;
        miu0_clients[i].bw_max=0;
        if (strcmp(miu0_clients[i].name,"NA        "))
            miu0_clients[i].bw_enabled = 1;
    }

    for(i=0; i<(sizeof(miu0_clients)/sizeof(miu0_clients[0]));i++)
    {
        if(miu0_clients[i].bw_enabled)
        {
            total_temp = 0;
            temp_loop_time=0;
            *(volatile unsigned short *)(0x1F000000 +0x1012 *0x200 + 0xD *4) = (((miu0_clients[i].bw_client_id << 8) & 0xFF00) | 0x30);
            *(volatile unsigned short *)(0x1F000000 +0x1012 *0x200 + 0xD *4) = (((miu0_clients[i].bw_client_id << 8) & 0xFF00) | 0x35);
            // OUTREG16( (BASE_REG_MIU_PA+REG_ID_0D), ( ((miu0_clients[i].bw_client_id << 8) & 0xFF00) | 0x30)) ;//reset
            // OUTREG16( (BASE_REG_MIU_PA+REG_ID_0D), ( ((miu0_clients[i].bw_client_id << 8) & 0xFF00) | 0x35)) ;//set to read peak
            //deadline = jiffies + gmonitor_duration*HZ/1000;
            deadline = gmonitor_duration / gmonitor_interval;
            do{
                //if(gmonitor_interval>10)
                MsSleep(gmonitor_interval);
                //else
                //    mdelay(gmonitor_interval);

                // temp_val=INREG16((BASE_REG_MIU_PA+REG_ID_0E));
                temp_val=*(volatile unsigned short *)(0x1F000000 +0x1012 *0x200 + 0xE *4);
                total_temp += temp_val;
                if(miu0_clients[i].effi_min>temp_val)
                {
                    miu0_clients[i].effi_min=temp_val;
                }
                temp_loop_time++;
                deadline --;
            } while (deadline);

            // OUTREG16( (BASE_REG_MIU_PA+REG_ID_0D),0) ;//reset all
            *(volatile unsigned short *)(0x1F000000 +0x1012 *0x200 + 0xD *4) = 0;
            miu0_clients[i].effi_avg=total_temp/temp_loop_time;

            UartSendTrace( "%d:%s[0x%x] EFFI_avg=%d.%d%%  ",(short)i,
            miu0_clients[i].name,
            (short)miu0_clients[i].bw_client_id,
            miu0_clients[i].effi_avg*100/1024, (miu0_clients[i].effi_avg*10000/1024)%100);

            total_temp = 0;
            temp_loop_time=0;
            //OUTREG16( (BASE_REG_MIU_PA+REG_ID_0D), ( ((miu0_clients[i].bw_client_id << 8) & 0xFF00) | 0x40)) ;//reset
            //OUTREG16( (BASE_REG_MIU_PA+REG_ID_0D), ( ((miu0_clients[i].bw_client_id << 8) & 0xFF00) | 0x41)) ;//set to read peak
            *(volatile unsigned short *)(0x1F000000 +0x1012 *0x200 + 0xD *4) = (((miu0_clients[i].bw_client_id << 8) & 0xFF00) | 0x40);
            *(volatile unsigned short *)(0x1F000000 +0x1012 *0x200 + 0xD *4) = (((miu0_clients[i].bw_client_id << 8) & 0xFF00) | 0x41);
            //deadline = jiffies + gmonitor_duration*HZ/1000;
            deadline = gmonitor_duration / gmonitor_interval;
            do{
                MsSleep(gmonitor_interval); //mdelay(gmonitor_interval);

                //temp_val=INREG16((BASE_REG_MIU_PA+REG_ID_0E));
                temp_val=*(volatile unsigned short *)(0x1F000000 +0x1012 *0x200 + 0xE *4);
                total_temp += temp_val;
                if(miu0_clients[i].bw_max<temp_val)
                {
                    miu0_clients[i].bw_max=temp_val;
                }
                temp_loop_time++;
                deadline --;
            } while (deadline);
            //OUTREG16( (BASE_REG_MIU_PA+REG_ID_0D),0) ;//reset all
            *(volatile unsigned short *)(0x1F000000 +0x1012 *0x200 + 0xD *4) = 0;
            miu0_clients[i].bw_avg=total_temp/temp_loop_time;

            UartSendTrace( "BW_avg=%2d.%02d%%  BW_max=%2d.%02d%%  %2d.%02d%% %2d.%02d%%\n",
            miu0_clients[i].bw_avg*100/1024, (miu0_clients[i].bw_avg*10000/1024)%100,
            miu0_clients[i].bw_max*100/1024, (miu0_clients[i].bw_max*10000/1024)%100,
            miu0_clients[i].bw_avg*100/miu0_clients[i].effi_avg,
            (miu0_clients[i].bw_avg*10000/miu0_clients[i].effi_avg)%100,
            miu0_clients[i].bw_max*100/miu0_clients[i].effi_avg,
            (miu0_clients[i].bw_max*10000/miu0_clients[i].effi_avg)%100);

        }
    }

   // if (str > buf)  str--;

   // str += scnprintf(str, end - str, "\n");

  //  return (str - buf);
}

int ProcessStatus(CLI_t * pCli, char * p)
{
    rtk_Task_t *ptrTask, **pptrTask;
    u8 u8TaskId;
    u32 gu32isr_time_percentage;
    u32 u32total_percentage = 0;
    u32 u32total_time;

    u32 *pu32isr_count_time_in_task = NULL;
    u32 *pu32task_accumulated_time = NULL;
    u32 *pu32tasku32time_percentage = NULL;

    u32 u32isr_accumulated_time = 0;
    u32 u32task_count_start_time = 0;

    u32 u32task_array_size;

    extern u32 gu32isr_count_time_in_task[];
    extern u32 gu32task_accumulated_time[];
    extern u32 gu32isr_accumulated_time;
    extern u32 gu32task_count_start_time;

    u32task_array_size = RTK_MAX_TASKS * sizeof(u32);
    pu32isr_count_time_in_task = MsCallocateMem(u32task_array_size);
    pu32task_accumulated_time = MsCallocateMem(u32task_array_size);
    pu32tasku32time_percentage = MsCallocateMem(u32task_array_size);

    memcpy((void *)pu32isr_count_time_in_task, (void *)&gu32isr_count_time_in_task[0], u32task_array_size);
    memcpy((void *)pu32task_accumulated_time, (void *)&gu32task_accumulated_time[0], u32task_array_size);
    u32isr_accumulated_time = gu32isr_accumulated_time;
    u32task_count_start_time = gu32task_count_start_time;

    u32total_time = DrvTimerStdaTimerGetTick() - u32task_count_start_time;

    for(u8TaskId = 0; u8TaskId < RTK_MAX_TASKS; u8TaskId++){
        *(pu32task_accumulated_time + u8TaskId) -= *(pu32isr_count_time_in_task + u8TaskId);
        *(pu32tasku32time_percentage + u8TaskId) = (u32)(((u64)*(pu32task_accumulated_time + u8TaskId) * 10000) / (u64)u32total_time);
        u32total_percentage += *(pu32tasku32time_percentage + u8TaskId);
    }

    gu32isr_time_percentage = (u32)(((u64)u32isr_accumulated_time * 10000) / (u64)u32total_time);
    u32total_percentage += gu32isr_time_percentage;
    UartSendTrace("CPU Total: %2d.%02d %%\n", u32total_percentage / 100, u32total_percentage % 100);
    UartSendTrace("CPU ISR: %2d.%02d %%. Not count yet.\n", gu32isr_time_percentage / 100, gu32isr_time_percentage % 100);

    for(u8TaskId = 0; u8TaskId < RTK_MAX_TASKS; u8TaskId++){
        pptrTask = &rtk_Tasks[u8TaskId];
        ptrTask = *pptrTask;

        if((ptrTask) && (*(pu32tasku32time_percentage + u8TaskId) > 0)){
            UartSendTrace("CPU: %2d.%02d %%,  Id: %3d,  ", *(pu32tasku32time_percentage + u8TaskId) / 100, *(pu32tasku32time_percentage + u8TaskId) % 100, u8TaskId);
            UartSendTrace("Pri: %3d,  Task: %s\n", ptrTask->Priority, ptrTask->TaskName);
        }
    }

    MsReleaseMemory(pu32isr_count_time_in_task);
    MsReleaseMemory(pu32task_accumulated_time);
    MsReleaseMemory(pu32tasku32time_percentage);
    return 0;
}

int SensorReset(CLI_t * pCli, char * p)
{
    DrvSensorIFHWReset(0, 0);
    DrvSensorIFHWReset(0, 1);
}
int MiuAnalysis(CLI_t * pCli, char * p)
{
    measure_all_show();
    return 0;
}

int AllocAnalysis(CLI_t * pCli, char * p)
{
    extern void DumpAllocArray(void);

    DumpAllocArray();
    return 0;
}

int CpuAnalysis(CLI_t * pCli, char * p)
{
    double freq;
    unsigned long regvalue = 0;

    *(volatile unsigned char *)(0x1F000000 + (0x102216 << 1))= 0x01;
    *(volatile unsigned char *)(0x1F000000 + (0x101EEE << 1))= 0x04;
    *(volatile unsigned char *)(0x1F000000 + (0x101EEA << 1))= 0x04;
    *(volatile unsigned char *)(0x1F000000 + (0x101EEA << 1)+1) =  0x40;
    *(volatile unsigned char *)(0x1F000000 + (0x101EEC  << 1)) =  0x01;
    *(volatile unsigned char *)(0x1F000000 + (0x101EE0  << 1)+1) = 0x00;
    *(volatile unsigned char *)(0x1F000000 + (0x101EE0  << 1)+1) = 0x80;
    MsSleep(1);
    regvalue = (*(volatile unsigned char *)(0x1F000000 + (0x101EE2  << 1))) | (*(volatile unsigned char *)(0x1F000000 + (0x101EE2  << 1)+1) << 8);
    freq = regvalue*4000/83333;

    UartSendTrace("freq: %f\n", freq);
    return 0;

}

int MemMonitor(void)
{
    typedef struct KmMemInfoTag
    {
        /** Magic number.
        * The magic number is used to check if the pool has been initialised
        * before it is used. I tcan also detect if the pool pointer is invalid. */
        u16 magicNumber;

    #if 1//def __GKI_GETINFO_NOWALK__
        u32 nFreeblockCount;
        u32 nUsedBlockCont;
        u32 nFreeSize;
        u32 nUsedSize;
        u32 nMaxUsedSize;
    #endif

        u8 *fenceStart;
        u8 *fenceEnd;
        u8 *biggest; /* a cache pointing to the biggest block */
        u32 nBiggestSize;
        u32 peekCount;

        /** Number of L1 ranges.
        * This holds the number of entries in the level1 array. This value is
        * calculated when the pool is initialised. The value can be from 0 to 31,
        * although a value of 0 is pointless. */
        u8 numL1Ranges;  /* 0 - 31, defines size of level1 */

        /** Bitmap of L1 ranges containing free blocks.
        * This is a bitmap of the L1 ranges that contain at least one free block. */
        u32 l1AvailBitmap;

        /** Size of memory used for the pool.
        * This is the byte size of the original memory used to hold this memory pool. */
        u32 memorySize;
    #if 0//
        /** Level 1 memory block size ranges.
        * This is an array of Level 1 free block size ranges. The number of entries
        * in this array is given by the numL1Ranges member. This must be the last
        * member of the structure as it is dynamically sized. */
        KmMemL1Range level1[2]; /* actual range depends on config */
                                                 /*
                                                 **                      sizes                      sub grain
                                                 ** level1[ 0] = 0 to 255             8 - special case
                                                 ** level1[ 1] = 256 to 511                 8
                                                 ** level1[ 2] = 512 to 1023          16
                                                 ** level1[ 3] = 1024 to 2047         32
                                                 ** level1[ 4] = 2048 to 4095         64
                                                 ** level1[ 5] = 4096 to 8191         128
                                                 ** level1[ 6] = 8192 to 16383        256
                                                 ** level1[ 7] = 16384 to 32767              512
                                                 ** level1[ 8] = 32768 to 65535              1024
                                                 ** level1[ 9] = 65536 to 131071        2048
                                                 ** level1[10] = 131072 to 262143      4096
                                                 ** level1[11] = 262144 to 524287      8192
                                                 ** level1[12] = 524288 to 1048575    16384
                                                 ** level1[13] = 1048576 to 2097151  32768
                                                 ** level1[14] = 2097152 to etc...       65536
        */
    #endif
    } KmMemInfo;

    KmMemInfo *memInfo;
    rtk_memoryContext_t *rtkCtxt;
    u32 i;

    UartSendTrace("%s\r\n",__FUNCTION__);

    rtkCtxt = &((pMemHandle_t)ms_memoryhandle)->rtkCtxt;
    memInfo = (KmMemInfo *)(rtkCtxt->rtk_HeapStart);

    UartSendTrace("MEM FBC:%d,UBC:%d,FSize:%d.%d MB,USize:%d.%d MB,max:%d.%d MB,Per:%d%%\r\n",
        memInfo->nFreeblockCount,memInfo->nUsedBlockCont,
        memInfo->nFreeSize>>20,(memInfo->nFreeSize&0xFFFFF)>>10,
        memInfo->nUsedSize>>20,(memInfo->nUsedSize&0xFFFFF)>>10,
        memInfo->nMaxUsedSize>>20,(memInfo->nMaxUsedSize&0xFFFFF)>>10,
        (((memInfo->nUsedSize>>20)*100)/((memInfo->nUsedSize+memInfo->nFreeSize)>>20)));

    UartSendTrace("\r\n***************************************************\r\n\r\n");

    return 0;
}

#if 0 // (DEBUG_LIVE_PCM)

#define RAW_PCM_DUMP_FILE_NAME          ("SD:\\RAW_PCM.pcm")//SD:\\PCM%d.pcm
#define DUMP_LIVE_PCM_SIZE              (320000*2)
MMP_ULONG m_DumpPcmFileID = 0;
extern MMP_UBYTE    m_ulDbgPcmOutBuf[];
extern MMP_ULONG    m_ulDbgPcmOutSize;
char FileName[256]={0};
static AHC_ERR RawPcm_OpenDumpFile(void)
{
    MMP_ULONG current_time = 0;

    MMPF_OS_GetTimeMs(&current_time);
    sprintf(FileName, "SD:\\RAW_PCM%d.pcm",current_time/1000);

    return AHC_FS_FileOpen(FileName, STRLEN(FileName),"wb", sizeof("wb"),&m_DumpPcmFileID);
}

static void RawPcm_WriteDumpFile(MMP_ULONG uiSeekPos, MMP_ULONG uiAddr, MMP_ULONG uiSize)
{
    MMP_ULONG uiWriteSize;

    AHC_FS_FileWrite(m_DumpPcmFileID, (UINT8*)uiAddr, uiSize, &uiWriteSize);
}

static void RawPcm_CloseDumpFile(void)
{
    AHC_FS_FileClose(m_DumpPcmFileID);
}

void RawPcm_Dump2SD(void)
{
    MMP_ULONG   ulFileID = 0;

    if(m_ulDbgPcmOutSize > (DUMP_LIVE_PCM_SIZE-2048) && AHC_ERR_NONE == RawPcm_OpenDumpFile())
    {
        printc(FG_GREEN("[INFO]%s dump raw pcm!%s\r\n"),__FUNCTION__,FileName);

        //SDUpdateReadNor(m_DumpPcmFileID);
        RawPcm_WriteDumpFile(0, m_ulDbgPcmOutBuf, m_ulDbgPcmOutSize);
        RawPcm_CloseDumpFile();
        m_ulDbgPcmOutSize = 0;

        printc(FG_GREEN("[INFO]%s dump raw pcm success!\r\n"),__FUNCTION__);
    }
}

int LivePcmProc(CLI_t * pCli, char * p)
{
    RawPcm_Dump2SD();
    return eCLI_PARSE_ERROR;
}

#define PARSE_TOKEN_DUMP_PCM_MENU \
        {"dumppcm",     "save pcm raw data",  "", LivePcmProc, NULL},
#else
#define PARSE_TOKEN_DUMP_PCM_MENU
#endif

int UartCmd_SetEmergAction(CLI_t * pCli, char * p)
{
    int num = 0;
    //volatile int val;

    if (VideoFunc_PreRecordStatus() || VideoFunc_GetRecordStatus()) {
        printc("Emerg Action Type can't be changed during recording.\r\n");
        return 0;
    }    

    UartSendTrace("\r\nSet Emergency Action Type: \r\n");
    UartSendTrace("===============================\n");
    UartSendTrace("=[0] MMP_3GPRECD_EMERG_NO_ACT\n");
    UartSendTrace("=[2] MMP_3GPRECD_EMERG_SWITCH_FILE\n");
    UartSendTrace("=[3] MMP_3GPRECD_EMERG_MOVE_FILE\n");
    UartSendTrace("=[4] MMP_3GPRECD_EMERG_DEFAULT_ACT\n");    
    UartSendTrace("===============================\n");

    UartSendTrace("==>");
    num = vm_atoi(wait_for_command());
    UartSendTrace("input: %d\r\n", num);

    if (VideoFunc_PreRecordStatus() || VideoFunc_GetRecordStatus()) {
        printc("Emerg Action Type can't be changed during recording.\r\n");
        return 0;
    }
    
    switch(num)
    {
        case 0: //MMP_3GPRECD_EMERG_NO_ACT
            MMPS_3GPRECD_SetEmergActionType(MMP_3GPRECD_EMERG_NO_ACT);            
            break;
        case 1: //MMP_3GPRECD_EMERG_DUAL_FILE, currently not support
            //MMPS_3GPRECD_SetEmergActionType(MMP_3GPRECD_EMERG_DUAL_FILE);
            break;
        case 2: //MMP_3GPRECD_EMERG_SWITCH_FILE
            MMPS_3GPRECD_SetEmergActionType(MMP_3GPRECD_EMERG_SWITCH_FILE);
            break;
        case 3: //MMP_3GPRECD_EMERG_MOVE_FILE
            MMPS_3GPRECD_SetEmergActionType(MMP_3GPRECD_EMERG_MOVE_FILE);
            break;
        case 4:
        default: //MMP_3GPRECD_EMERG_DEFAULT_ACT
            MMPS_3GPRECD_SetEmergActionType(MMP_3GPRECD_EMERG_DEFAULT_ACT);
            break;
    }

    printc("New Emerg Act Type: %d\r\n", MMPS_3GPRECD_GetEmergActionType());
    return 0;
}

int MicProc(CLI_t * pCli, char * p)
{
    char cmd[16];
    char gMonitorCliTmpBuf[128];
    int ret = 0;
    ULONG addr;

    CliReassembleToken(pCli,gMonitorCliTmpBuf);

    ret = sscanfl( gMonitorCliTmpBuf, "%s", cmd);

#if 0
    0x1502EA
    [15] REG_SINE_GEN_EN         1: enable
    [14] REG_SINE_GEN_L            1: L channel enable
    [13] REG_SINE_GEN_R           1: R channel enable
    [12]  REG_SINE_GEN_RD_WR 0:reader; 1:writer (set to "1")
    [11]  REG_DMA_TEST_SEL_H 0:low word; 1:high word (set to "0")
    [10:8] REG_DMA_TEST_SEL   DMA test bus selection (set to "0")
    [7:4] REG_SINE_GEN_GAIN     sine generator gain selection (set to "0")
    [3:0] REG_SINE_GEN_FREQ    sine generator frequency selection (set to "4")
#endif

    if(ret >= 1){
        addr = BACH0_DMA_TEST_CTRL5_REG;//(0x1F000000+0x150200<<1+0x75<<2);
        printc("reg write 0x%08x\r\n",addr);
        if (!strcmp(cmd, "enable")){
            *(volatile u32*)(BACH0_DMA_TEST_CTRL5_REG) = (0x7<<13)| (0x1<<12)| (0xf<<0);
        }else if(!strcmp(cmd, "disable")){
            *(volatile u32*)(BACH0_DMA_TEST_CTRL5_REG) &= 0x7fff;
        }
    }
    return eCLI_PARSE_OK;
HELP_EXIT:
    return eCLI_PARSE_ERROR;
}

int UuidProc(CLI_t * pCli, char * p)
{
    char cmd[16], subCMD[16],key[4];
    ULONG serial_num[4];
    char *subPARM;
    static char gMonitorCliTmpBuf[128];
    int ret = 0,i;

    CliReassembleToken(pCli,gMonitorCliTmpBuf);

    ret = sscanfl( gMonitorCliTmpBuf, "%s", cmd);

    if(ret >= 1){
        subPARM = strstr( gMonitorCliTmpBuf, cmd ) + strlen(cmd);

        if (!strcmp(cmd, "set")){

            if((ret >= 1) )//&& (!strncmp(subCMD,"-key",4)))
            {
                for (i=0;i<4;i++){
                    EAT_WHITE(subPARM)
                    ret = sscanfl(subPARM, "%s", subCMD );
                    //key[i] = atoi(subCMD);//need to check---->decimal
                    serial_num[i] = strtoul(subCMD,NULL,16);
                    subPARM = strstr( subPARM, subCMD ) + strlen(subCMD);
                }
                printc("\r\nSet serial_num:%08X,%08X,%08X,%08X\r\n",serial_num[0],serial_num[1],serial_num[2],serial_num[3]);
            }else{
                printc("Set uuid,Param ERROR!\r\n");
            }
        }else if(!strcmp(cmd, "get")){
            DrvEfuse_ReadUniqueID6B(key);
            printc("\r\nUUID:%02X,%02X,%02X,%02X,%02X,%02X\r\n",key[0],key[1],key[2],key[3],key[4],key[5]);
            printc("\r\n");
        }
    }
    return eCLI_PARSE_OK;
HELP_EXIT:
    return eCLI_PARSE_ERROR;
}

int MemAnalysis(CLI_t * pCli, char * p)
{
    u32 startup = 0;
    static MMPF_OS_TMRID    stMemMonitor = MMPF_OS_CREATE_TMR_INT_ERR;
    char cmd[16], subCMD[16];
    char *subPARM;
    static char gMonitorCliTmpBuf[128];
    u32 monitorFre = 5000;
    int ret = 0;

    CliReassembleToken(pCli,gMonitorCliTmpBuf);

    ret = sscanfl( gMonitorCliTmpBuf, "%s %s", cmd, subCMD );

    if(ret >= 1){
        subPARM = strstr( gMonitorCliTmpBuf, subCMD ) + strlen(subCMD);

        if (!strcmp(cmd, "on")){
            startup = 1;
        }

        if((ret == 2) && (!strncmp(subCMD,"-t",2))){
            //EAT_NON_WHITE(subPARM)
            EAT_WHITE(subPARM)
            monitorFre = atoi(subPARM);
            monitorFre = (monitorFre<1000)?(5000):(monitorFre>10000)?(5000):(monitorFre);
        }

        if(startup && stMemMonitor == MMPF_OS_CREATE_TMR_INT_ERR){
            stMemMonitor = MMPF_OS_StartTimer(monitorFre, MMPF_OS_TMR_OPT_PERIODIC, (MMPF_OS_TMR_CALLBACK)&MemMonitor, NULL);
        }else if((!startup) && (stMemMonitor != MMPF_OS_CREATE_TMR_INT_ERR)){
            MMPF_OS_StopTimer(stMemMonitor, NULL);
            stMemMonitor = MMPF_OS_CREATE_TMR_INT_ERR;
        }
    }
    return eCLI_PARSE_OK;
HELP_EXIT:
    return eCLI_PARSE_ERROR;
}

static int MiuProtHandler(CLI_t *pCli, char *p)
{
    u32 addr_start = 0, addr_end = 0, addr_start8k = 0, addr_end8k = 0, client_id = 0, rd_sts = 0, hit_fg = 0, i = 0;
    if (CliTokenCount(pCli) == 3) {
        if (CliTokenPopNum(pCli, &addr_start, 0) != eCLI_PARSE_OK)
            goto HELP_EXIT;
        if (CliTokenPopNum(pCli, &addr_end, 0) != eCLI_PARSE_OK)
            goto HELP_EXIT;
        if (CliTokenPopNum(pCli, &client_id, 0) != eCLI_PARSE_OK)
            goto HELP_EXIT;
        addr_start8k = (addr_start&0x0FFFFFFF)>>13;
        addr_end8k = (addr_end&0x0FFFFFFF)>>13;
        UartSendTrace( "client_id x%x [StAddr:EndAddr]/[x%x:x%x]/8K[x%x:x%x]\r\n", client_id, addr_start, addr_end, addr_start8k, addr_end8k);
        *(volatile unsigned short *)(0x1F000000+0x1012*0x200+0x17*4) = client_id;     //protect_id0 = Client g11
        *(volatile unsigned short *)(0x1F000000+0x1012*0x200+0x10*4) = 0x0001;        //protect0_id_enable[15:0] (per-bit enable id0~idf)
        *(volatile unsigned short *)(0x1F000000+0x1012*0x200+0x60*4) = addr_start8k;  //protect0_start[15:0] (unit : 8K-byte, "0x1fb05000" byte align to "0xfd82" 8k-byte)
        *(volatile unsigned short *)(0x1F000000+0x1012*0x200+0x61*4) = addr_end8k;    //protect0_end[15:0]   (unit : 8K-byte, "0x1ff6c000" byte align to "0xffb6" 8k-byte)
        *(volatile unsigned char *)(0x1F000000+0x1012*0x200+0xD0*2)  = 0x03 & (addr_start8k>>16); //protect0_start_17_16[17:16]
        *(volatile unsigned char *)(0x1F000000+0x1012*0x200+0xD0*2) |= 0x0C & (addr_end8k>>16);   //protect0_end_17_16[17:16]
        *(volatile unsigned char *)(0x1F000000+0x1012*0x200+0xD3*2)  = 0x00;        //{protect3_inv ,protect2_inv ,protect1_inv ,protect0_inv }
        *(volatile unsigned char *)(0x1F000000+0x1012*0x200+0xD2*2)  = 0x0F & 0x01; //{protect3_w_en,protect2_w_en,protect1_w_en,protect0_w_en}
        *(volatile unsigned char *)(0x1F000000+0x1012*0x200+0xD2*2) |= 0xF0 & 0x10; //{protect3_r_en,protect2_r_en,protect1_r_en,protect0_r_en}

        return eCLI_PARSE_OK;
    }
    else {
        rd_sts =  *(volatile unsigned short *)(0x1F000000+0x1012*0x200+0x6F*4);
        hit_fg = (rd_sts>>4) & 0xF;
        client_id = (rd_sts>>8);
        UartSendTrace("ProtSts:x%x[x%x x%x]\r\n", rd_sts, client_id, hit_fg);
        for(i=0; i<(sizeof(miu0_clients)/sizeof(miu0_clients[0]));i++) {
            if (hit_fg && (miu0_clients[i].bw_client_id == client_id)) {
                UartSendTrace("hit client id:%s\n", miu0_clients[i].name);
            }
        }

        return eCLI_PARSE_OK;
    }

HELP_EXIT:
    return eCLI_PARSE_ERROR;
}

#if (ISW_CLI_TEST_ENABLE == 1)
static CliParseToken_t _atRootTbl[] =
{
    {"help",        _szHelpHelpTxt,     _szHelpUsageTxt,    _helpHandler,    NULL},
    {"ls",          _szHelpHelpTxt,     _szHelpUsageTxt,    _helpHandler,    NULL},
    {"?",           _szHelpHelpTxt,     _szHelpUsageTxt,    _helpHandler,    NULL},
    {"quit",        _szQuitHelpTxt,     _szQuitUsageTxt,    _quitHandler,    NULL},
    {"cd",          _szCdHelpTxt,       _szCdUsageTxt,      _cdHandler,      NULL},
    {"memdump",     _szMemdumpHelpTxt,  _szMemdumpUsageTxt, _memdumpHandler, NULL},
    {"memset",      _szMemsetHelpTxt,   _szMemsetUsageTxt,  _memsetHandler,  NULL},
    {"memcpy",      _szMemcpyHelpTxt,   _szMemcpyUsageTxt,  _memcpyHandler,  NULL},
    {"regset",      _szRegsetHelpTxt,   _szRegsetUsageTxt,  _regsetHandler,  NULL},
    {"regget",      _szReggetHelpTxt,   _szReggetUsageTxt,  _reggetHandler,  NULL},
#if (WIFI_PORT == 1)
    { "net",        "perform NETWORK commands", "", UartCmd_NETCommands,    NULL},
    { "wifi",       "perform WIFI commands",    "", UartCmd_WifiCommands,   NULL},
    { "v4l",        "v4l debugging",            "", UartCmd_V4l,            NULL},
#endif
#if GSENSOR_CONNECT_ENABLE
    {"rwgss",      "Access Gsensor",   _szReggetUsageTxt,  UartCmd_Gsens,  NULL},
#endif
    {"test",        "Input OS test case num (999 for all)", "", KerTest,     NULL},
#ifndef __I_SW_OS_G1__
#ifdef __FIXME__
    {"sleep",       _szSleepHelpTxt,    _szSleepUsageTxt,   _sleepHandler,   NULL},
    {"testout",     _szTestoutHelpTxt,  _szTestoutUsageTxt, _testoutHandler, NULL},
    {"clkout",      _szClkoutHelpTxt,   _szClkoutUsageTxt,  _clkoutHandler,  NULL},
    {"delay",       _szDelayHelpTxt,    _szDelayUsageTxt,   _delayHandler,   NULL},
#endif
    {"cache",       _szCacheHelpTxt,    _szCacheUsageTxt,   NULL,            _atCacheTbl},
    {"icache",      _szICacheHelpTxt,   _szICacheUsageTxt,  NULL,            _atICacheTbl},
#endif
    {"mfe", _szMfeMenuHelpTxt,  _szMfeMenuUsageTxt, MfeEncodeFlow,   NULL},
    {"ait", _szAitMenuHelpTxt,  _szAitMenuUsageTxt, AitFlow,   NULL},
#if defined(__MV5_FPGA__)
    {"gtime", _szAitMenuHelpTxt,  _szAitMenuUsageTxt, GenericTimerTestFlow,   NULL},
#endif
    {"fs", _szfsHelpTxt,  _szfsUsageTxt, fs_test,   NULL},
    {"dumpdcf", _szdcfdumpHelpTxt,  _szdcfdumpUsageTxt, AHC_UF_DumpDB,   NULL},
    {"checkfps", _szcheckFPSHelpTxt, _szcheckFPSUsageTxt, MV5_CheckFPS_enable, NULL},
    {"ispbypass", _szIspBypassHelpTxt, _szIspBypassUsageTxt, MV5_ispbypass, NULL},
    {"dumpraw", _szdumprawdataHelpTxt, _szdumprawdataUsageTxt, MV5_DumpRawData, NULL},
    {"adas", _szAdasHelpTxt,  _szAdasUsageTxt, adas_test,   NULL},
    {"dump_adas", "dump ADAS para ",  "Dump ADAS Init params ", Uartcmd_DumpADASPara,   NULL},
    {"uartoff", _szUartDisableTxt,  _szUartUsageTxt, uart_off,  NULL},
#if defined(__MV5_FPGA__)
    {"fpgapiu", _szFPGAPIUMenuHelpTxt,  _szFPGAPIUMenuUsageTxt, FPGA_PIU_Test,   NULL},
#endif
    {"comp", _szCompHelpTxt,  _szCompUsageTxt, Component_test,   NULL},
    {"Jpeg", _szJpegHelpTxt,  _szJpegUsageTxt, MV5_JPE_test,   NULL},
    {"Aud", _szAudioHelpTxt,  _szAudioUsageTxt, MV5_AUD_test,   NULL},
    {"jpd", _szJpdMenuHelpTxt,  _szJpdMenuUsageTxt, JPDFuncTest,   NULL},
    {"vdec", _szVdecMenuHelpTxt,  _szVdecMenuUsageTxt, FuncTestH264,   NULL},
    {"pb", _szPbMenuHelpTxt,  _szPbMenuUsageTxt, MV5_PB_test,   NULL},
    {"saradc", _szSarMenuHelpTxt,  _szSarAdcMenuUsageTxt, SarADCTest,   NULL},
    {"key", _szSarMenuHelpTxt,  _szSarAdcMenuUsageTxt, KeyPadTest,   NULL},
    {"ucm",  "UART Cmd test template",  "", UartCmd_Test, NULL},
    {"setrtc", _szRTCPWCMenuHelpTxt,  _szRTCPWCMenuUsageTxt, RTCPWCSet,   NULL},
    {"getrtc", _szRTCPWCSetMenuHelpTxt,  _szRTCPWCSetMenuUsageTxt, RTCPWCGet,   NULL},
    {"ChkBin", _szCheckSDHelpTxt, _szCheckSDUsageTxt, MV5_DT_TestCheckBinFileExist, NULL},
    {"usb", _szUsbHelpTxt,  _szUSBUsageTxt, usb_test,   NULL},
    { "3dnr",    "3D NR",   "", UartCmd_3DNR, NULL},
    { "miu",     "miu analysis",  "", MiuAnalysis, NULL},
    { "alloc",   "alloc analysis","", AllocAnalysis, NULL},
    { "cpu",     "cpu analysis",  "", CpuAnalysis, NULL},
    { "sreset",  "sensor reset test",  "", SensorReset, NULL},
    {"memusage",     "mem analysis on -t 5000",  "", MemAnalysis, NULL},
    { "mprot", "miu protect",  "", MiuProtHandler, NULL},
    {"ps",     "process status",  "", ProcessStatus, NULL},
    {"uuid",     "process uuid",  "", UuidProc, NULL},
    {"sine-wave",     "mic input bypass",  "", MicProc, NULL},
    {"sea", "Set emergency action type", "", UartCmd_SetEmergAction, NULL},
    PARSE_TOKEN_DUMP_PCM_MENU
    PARSE_TOKEN_DIP_MENU
    PARSE_TOKEN_DIPCTL_MENU
    PARSE_TOKEN_COMP_MENU
    PARSE_TOKEN_RTC_MENU
    PARSE_TOKEN_SPINAND_MENU
    PARSE_TOKEN_FCIE_TEST
    PARSE_TOKEN_USBH_TEST
    PARSE_TOKEN_JPE_MENU
    PARSE_TOKEN_JPEMID_MENU
    PARSE_TOKEN_JPD_MENU
    PARSE_TOKEN_TIMER_MENU
    PARSE_TOKEN_IO_MENU
    PARSE_TOKEN_GPIO_MENU
    PARSE_TOKEN_PADCTRL_MENU
    PARSE_TOKEN_DIPB_MENU
    PARSE_TOKEN_SCL_MENU
    PARSE_TOKEN_GOP_MENU
    PARSE_TOKEN_PNL_MENU
    PARSE_TOKEN_MVOP_MENU
    PARSE_TOKEN_SIF_MENU
    PARSE_TOKEN_DMA_MENU
    PARSE_TOKEN_DMA2D_MENU
    PARSE_TOKEN_BDMA_MENU
    PARSE_TOKEN_SPI_MENU
    PARSE_TOKEN_ASURA_PMU_MENU
    PARSE_TOKEN_DISP_MENU
    PARSE_TOKEN_IMAGE_MENU
    PARSE_TOKEN_I2C_TEST
    PARSE_TOKEN_AUX_MENU
    PARSE_TOKEN_RTC_MENU
    PARSE_TOKEN_RGBLED_MENU
    PARSE_TOKEN_B3PMU_MENU
    PARSE_TOKEN_VDR_MENU
    PARSE_TOKEN_AUD_MENU
    PARSE_TOKEN_ZLIB_MENU
    PARSE_TOKEN_UART_MENU
    PARSE_TOKEN_KEYPAD_MENU
    PARSE_TOKEN_ASIC_MENU
    PARSE_TOKEN_CMU_MENU
    PARSE_TOKEN_CLKGEN_MENU
    PARSE_TOKEN_PLL_MENU
    PARSE_TOKEN_ASURA_ADC_TEST
    PARSE_TOKEN_DYNSCK_TEST
    PARSE_TOKEN_FMRX_TEST
    PARSE_TOKEN_EMI_TEST
    PARSE_TOKEN_MISC_MENU /// misc
    PARSE_TOKEN_INTC_MENU
    PARSE_TOKEN_EXTINT_MENU
    PARSE_TOKEN_DMC_MENU
    PARSE_TOKEN_DSP_MENU
    PARSE_TOKEN_SHAREDIF_MENU
    PARSE_TOKEN_SIM_MENU
    PARSE_TOKEN_ISP_MENU
    PARSE_TOKEN_SENSOR_IF_MENU
    PARSE_TOKEN_VIF_TEST
    PARSE_TOKEN_PNL_MENU
    PARSE_TOKEN_DEC_SCL_MENU
    PARSE_TOKEN_MIPI_DSI_MENU
    PARSE_TOKEN_DELIMITER
};
#else //#if (ISW_CLI_TEST_ENABLE == 1)
static CliParseToken_t _atRootTbl[] =
{
    {"regset",      _szRegsetHelpTxt,   _szRegsetUsageTxt,  _regsetHandler,  NULL},
    {"regget",      _szReggetHelpTxt,   _szReggetUsageTxt,  _reggetHandler,  NULL},
    {"key", _szSarMenuHelpTxt,  _szSarAdcMenuUsageTxt, KeyPadTest,   NULL},
#if (WIFI_PORT == 1)
    { "net",        "perform NETWORK commands", "", UartCmd_NETCommands,    NULL},
    { "wifi",       "perform WIFI commands",    "", UartCmd_WifiCommands,   NULL},
    { "v4l",        "v4l debugging",            "", UartCmd_V4l,            NULL},
#endif
    { "miu",        "miu analysis",             "", MiuAnalysis, NULL},
    { "mprot",      "miu protect",              "", MiuProtHandler, NULL},
    PARSE_TOKEN_DELIMITER
};
#endif //#if (ISW_CLI_TEST_ENABLE == 1)

#ifndef __I_SW_OS_G1__
static int _hCacheOn(CLI_t *pCli, char *p);
static char _szCacheOnHelpTxt[] = "Turn on I/D cache";
static char _szCacheOnUsageTxt[] = "";

static int _hCacheOff(CLI_t *pCli, char *p);
static char _szCacheOffHelpTxt[] = "Turn off I/D cache";
static char _szCacheOffUsageTxt[] = "";

static CliParseToken_t _atCacheTbl[] =
{
    {_szOn,         _szCacheOnHelpTxt,  _szCacheOnUsageTxt,     _hCacheOn,       NULL},
    {_szOff,        _szCacheOffHelpTxt, _szCacheOffUsageTxt,    _hCacheOff,      NULL},
    PARSE_TOKEN_DELIMITER
};

static int _hICacheOn(CLI_t *pCli, char *p);
static char _szICacheOnHelpTxt[] = "Turn on I-Cache";
static char _szICacheOnUsageTxt[] = "";

static int _hICacheOff(CLI_t *pCli, char *p);
static char _szICacheOffHelpTxt[] = "Turn off I-Cache";
static char _szICacheOffUsageTxt[] = "";

static CliParseToken_t _atICacheTbl[] =
{
    {_szOn,         _szICacheOnHelpTxt, _szICacheOnUsageTxt,    _hICacheOn,       NULL},
    {_szOff,        _szICacheOffHelpTxt,_szICacheOffUsageTxt,   _hICacheOff,      NULL},
    PARSE_TOKEN_DELIMITER
};
#endif

static int _helpHandler(CLI_t *pCli, char *p)
{
    char    *filter;

    cliPrintf("List of CLI commands:\n");

    if (CliTokenCount(pCli))
    {
        filter = CliTokenPop(pCli);
        if (eCLI_PARSE_HELP_NOT_FOUND == ClihelpCmdScan("", filter, 10))
            cliPrintf("   %s : NOT FOUND\n\n", filter);
    }
    else
        ClihelpCmdScan("", NULL, 0);
    return eCLI_PARSE_OK;
}

static int _cdHandler(CLI_t *pCli, char *p)
{
    char    *path;

    if (CliTokenCount(pCli) == 1)
    {
        path = CliTokenPop(pCli);
        return CliCdCmdScan(path);
    }
    return eCLI_PARSE_ERROR;
}

static int _quitHandler(CLI_t *pCli, char *p)
{
    return eCLI_PARSE_QUIT;
}


static void _memdump(u32 addr, u32 size)
{
    u32 i;
    u32 addr4;

    addr4=(addr/4)*4;
    size = (size+addr-addr4+3)/4*4;
    cliPrintf("addr=%d, size=%d\n", addr4, size);
    size/=4;
    for (i=0; i<size; i++)
    {
        cliPrintf("0x%08x ", *((u32*)(addr+(i<<2))));
        if (i % 4 == 3)
            cliPrintf("\n");
    }
    cliPrintf("\n");
}

static int _memdumpHandler(CLI_t *pCli, char *p)
{
    u32 addr, size;

    if (CliTokenCount(pCli) == 2)
    {
        if (CliTokenPopNum(pCli, &addr, 0) != eCLI_PARSE_OK)
            goto HELP_EXIT;
        if (CliTokenPopNum(pCli, &size, 0) != eCLI_PARSE_OK)
            goto HELP_EXIT;
        _memdump(addr, size);
        return eCLI_PARSE_OK;
    }

HELP_EXIT:
    return eCLI_PARSE_ERROR;
}

static int _memsetHandler(CLI_t *pCli, char *p)
{
    u32 dst, pattern, size;

    if (CliTokenCount(pCli) == 3)
    {
        if (CliTokenPopNum(pCli, &dst, 0) != eCLI_PARSE_OK)
            goto HELP_EXIT;
        if (CliTokenPopNum(pCli, &pattern, 0) != eCLI_PARSE_OK)
            goto HELP_EXIT;
        if (CliTokenPopNum(pCli, &size, 0) != eCLI_PARSE_OK)
            goto HELP_EXIT;
        if ((dst%4!=0) || (size%4!=0))
            goto HELP_EXIT;
        memset((void*)dst, pattern, size);
        return eCLI_PARSE_OK;
    }

HELP_EXIT:
    return eCLI_PARSE_ERROR;
}

static int _memcpyHandler(CLI_t *pCli, char *p)
{
    u32 dst, src, size;

    if (CliTokenCount(pCli) == 3)
    {
        if (CliTokenPopNum(pCli, &dst, 0) != eCLI_PARSE_OK)
            goto HELP_EXIT;
        if (CliTokenPopNum(pCli, &src, 0) != eCLI_PARSE_OK)
            goto HELP_EXIT;
        if (CliTokenPopNum(pCli, &size, 0) != eCLI_PARSE_OK)
            goto HELP_EXIT;
        if ((dst%4!=0) || (src%4!=0) || (size%4!=0))
            goto HELP_EXIT;
        memcpy((void*)dst, (void*)src, size);
        return eCLI_PARSE_OK;
    }

HELP_EXIT:
    return eCLI_PARSE_ERROR;
}


static int _regsetHandler(CLI_t *pCli, char *p)
{
    u32 addr, val;

    if (CliTokenCount(pCli) == 2)
    {
        if (CliTokenPopNum(pCli, &addr, 0) != eCLI_PARSE_OK)
            goto HELP_EXIT;
        if (CliTokenPopNum(pCli, &val, 0) != eCLI_PARSE_OK)
            goto HELP_EXIT;
        if ((addr%4!=0))
            goto HELP_EXIT;
        *((u32*)addr) = val;
        return eCLI_PARSE_OK;
    }

HELP_EXIT:
    return eCLI_PARSE_ERROR;
}

static int _reggetHandler(CLI_t *pCli, char *p)
{
    u32 addr;

    if (CliTokenCount(pCli) == 1)
    {
        if (CliTokenPopNum(pCli, &addr, 0) != eCLI_PARSE_OK)
            goto HELP_EXIT;
        if ((addr%4!=0))
            goto HELP_EXIT;
        cliPrintf(("register(%08x)= %08x\n"), addr, *((u32*)addr));
        return eCLI_PARSE_OK;
    }

HELP_EXIT:
    return eCLI_PARSE_ERROR;
}

#ifdef __FIXME__
#ifndef __I_SW_OS_G1__

#include "drv_clkgen_cmu.h"

#include "hal_pmu_itf.h"
#include "hal_asura_pmu.h"
#include "hal_b3_pmu.h"

typedef struct
{
    u32 addr;
    u16 value;
    u16 shadow;
} SleepEmiPadConfig;

__attribute__((section("emi_pad_sleep_data"))) SleepEmiPadConfig _gPadConfigTbl[27] =
{
    { 0x740076DC, 0xBABE, 0x00 },
    { 0x74007800, 0x9494, 0x00 }, // reg_emi_gpio0_pe=1 reg_emi_gpio0_mode=1 reg_emi_gpio1_pe=1 reg_emi_gpio1_mode=1
    { 0x74007804, 0x9494, 0x00 }, // reg_emi_gpio2_pe=1 reg_emi_gpio2_mode=1 reg_emi_gpio3_pe=1 reg_emi_gpio3_mode=1
    { 0x74007808, 0x9494, 0x00 }, // reg_emi_gpio4_pe=1 reg_emi_gpio4_mode=1 reg_emi_gpio5_pe=1 reg_emi_gpio5_mode=1
    { 0x7400780C, 0x9494, 0x00 }, // reg_emi_gpio6_pe=1 reg_emi_gpio6_mode=1 reg_emi_gpio7_pe=1 reg_emi_gpio7_mode=1
    { 0x74007810, 0x9494, 0x00 }, // reg_emi_gpio8_pe=1 reg_emi_gpio8_mode=1 reg_emi_gpio9_pe=1 reg_emi_gpio9_mode=1
    { 0x74007814, 0x9494, 0x00 }, // reg_emi_gpio10_pe=1 reg_emi_gpio10_mode=1 reg_emi_gpio11_pe=1 reg_emi_gpio11_mode=1
    { 0x74007818, 0x9494, 0x00 }, // reg_emi_gpio12_pe=1 reg_emi_gpio12_mode=1 reg_emi_gpio13_pe=1 reg_emi_gpio13_mode=1
    { 0x7400781C, 0x9494, 0x00 }, // reg_emi_gpio14_pe=1 reg_emi_gpio14_mode=1 reg_emi_gpio15_pe=1 reg_emi_gpio15_mode=1
    { 0x74007820, 0x9494, 0x00 }, // reg_emi_gpio16_pe=1 reg_emi_gpio16_mode=1 reg_emi_gpio17_pe=1 reg_emi_gpio17_mode=1
    { 0x74007824, 0x9492, 0x00 }, // reg_emi_gpio18_pe=1 reg_emi_gpio18_oen=0 reg_emi_gpio18_out=1 reg_emi_gpio18_mode=1 reg_emi_gpio19_pe=1 reg_emi_gpio19_mode=1
    { 0x74007828, 0x9494, 0x00 }, // reg_emi_gpio20_pe=1 reg_emi_gpio20_mode=1 reg_emi_gpio21_pe=1 reg_emi_gpio21_mode=1
    { 0x7400782C, 0x9494, 0x00 }, // reg_emi_gpio22_pe=1 reg_emi_gpio22_mode=1 reg_emi_gpio23_pe=1 reg_emi_gpio23_mode=1
    { 0x74007830, 0x9494, 0x00 }, // reg_emi_gpio24_pe=1 reg_emi_gpio24_ps=0 reg_emi_gpio24_mode=1 reg_emi_gpio25_pe=1 reg_emi_gpio25_mode=1
    { 0x74007834, 0x9494, 0x00 }, // reg_emi_gpio26_pe=1 reg_emi_gpio26_mode=1 reg_emi_gpio27_pe=1 reg_emi_gpio27_ps=0 reg_emi_gpio27_mode=1
    { 0x74007838, 0x9494, 0x00 }, // reg_emi_gpio28_pe=1 reg_emi_gpio28_ps=0 reg_emi_gpio28_mode=1 reg_emi_gpio29_pe=1 reg_emi_gpio29_mode=1
    { 0x7400783C, 0x9294, 0x00 }, // reg_emi_gpio30_pe=1 reg_emi_gpio30_mode=1 reg_emi_gpio31_pe=1 reg_emi_gpio31_oen=0 reg_emi_gpio31_out=1 reg_emi_gpio31_mode=1
    { 0x74007840, 0x9494, 0x00 }, // reg_emi_gpio32_pe=1 reg_emi_gpio32_mode=1 reg_emi_gpio33_pe=1 reg_emi_gpio33_ps=0 reg_emi_gpio33_mode=1
    { 0x74007844, 0x9494, 0x00 }, // reg_emi_gpio34_pe=1 reg_emi_gpio34_mode=1 reg_emi_gpio35_pe=1 reg_emi_gpio35_mode=1
    { 0x74007848, 0x9494, 0x00 }, // reg_emi_gpio36_pe=1 reg_emi_gpio36_mode=1 reg_emi_gpio37_pe=1 reg_emi_gpio37_mode=1
    { 0x7400784C, 0x9494, 0x00 }, // reg_emi_gpio38_pe=1 reg_emi_gpio38_mode=1 reg_emi_gpio39_pe=1 reg_emi_gpio39_mode=1
    { 0x74007850, 0x9494, 0x00 }, // reg_emi_gpio40_pe=1 reg_emi_gpio40_ps=0 reg_emi_gpio40_mode=1 reg_emi_gpio41_pe=1 reg_emi_gpio41_ps=0 reg_emi_gpio41_mode=1
    { 0x74007854, 0xB494, 0x00 }, // reg_emi_gpio42_pe=1 reg_emi_gpio42_ps=0 reg_emi_gpio42_mode=1 reg_emi_gpio43_pe=1 reg_emi_gpio43_ps=1 reg_emi_gpio43_mode=1
    { 0x74007858, 0x9494, 0x00 }, // reg_emi_gpio44_pe=1 reg_emi_gpio44_ps=0 reg_emi_gpio44_mode=1 reg_emi_gpio45_pe=1 reg_emi_gpio45_ps=0 reg_emi_gpio45_mode=1
    { 0x7400785C, 0x9494, 0x00 }, // reg_emi_gpio46_pe=1 reg_emi_gpio46_ps=0 reg_emi_gpio46_mode=1 reg_emi_gpio47_pe=1 reg_emi_gpio47_ps=0 reg_emi_gpio47_mode=1
    { 0x74007860, 0x9494, 0x00 }, // reg_emi_gpio48_pe=1 reg_emi_gpio48_ps=0 reg_emi_gpio48_mode=1 reg_emi_gpio49_pe=1 reg_emi_gpio49_ps=0 reg_emi_gpio49_mode=1
    { 0x74007864, 0x9494, 0x00 }, // reg_emi_gpio50_pe=1 reg_emi_gpio50_ps=0 reg_emi_gpio50_mode=1 reg_emi_gpio51_pe=1 reg_emi_gpio51_ps=0 reg_emi_gpio51_mode=1
};

extern u32 sys_inSleepMode;
extern u32 sys_wakeUpFromReset;

#define C0_ALWAYS_USE_XTAL_26M
#define SLEEP_SETTING_OF_CL_WU
#define DISABLE_UART
#define DISABLE_PLLS

#if defined(C0_ALWAYS_USE_XTAL_26M)
static void _C0RootFromMainClk(void)
{
    /* Set CPU source to MAIN_CLK (26 MHz), bit 0 cleared */
    g_ptKeCmu->cpuSysCtrl &= ~(CPU_INT_CLK_ON | CPU_INT_CLK_DIV_MASK);
    g_ptKeCmu->cpuSysCtrl |= (CPU_INT_CLK_DIV_1 << CPU_INT_CLK_DIV_POS);

    g_ptKeCmu->cpuSysCfg = 0x00UL;

    g_ptKeCmu->cpuPeriphCfg = 0x00;

    /* CPU Clock updated */
    g_ptKeCmu->cpuSysCtrl |= SYS_CLK_UPDATE;
}
#endif

#if !defined(__ISW_8533D__) && !defined(__ISW_8532B__) && !defined(__ISW_8556R__)
static void temp_B3(void)
{
    s32 pHandle;
    u16 nData;

    //_HalEnableOverWrite();

    HalAsuraRead(pHandle,MCP_FRO_CLK_ADJ, &nData);
    nData = nData & ~(0x0040);
    HalAsuraWrite(pHandle, MCP_FRO_CLK_ADJ, nData);

    HalEnableMasterStandby();
}
#else
static void temp_B3(void)
{
    /* Config MCP mode to disable?
    // Bravo not supported...
    s32 pHandle;
    u16 nData;
    nData = g_ptAsuraPMUReg->mcp_fro_clk_adj;
    nData = nData & ~(0x0040);
    g_ptAsuraPMUReg->mcp_fro_clk_adj = nData;
    */
    HalEnableMasterStandby();
}
#endif

#if !defined(__ISW_8533D__) && !defined(__ISW_8532B__) && !defined(__ISW_8556R__)
static int _sleepHandler(CLI_t *pCli, char *p)
{
    u32 ItMask;
    static bool bFirstTime = TRUE;

    if (bFirstTime != FALSE)
    {
        bFirstTime = FALSE;

#if defined(C0_ALWAYS_USE_XTAL_26M)
#if defined(SLEEP_SETTING_OF_CL_WU)
        /* do this before change C0ROOT to prevent glitch */
        g_ptKePll->reg_mpll_bypass = 0x01;
#endif /* SLEEP_SETTING_OF_CL_WU */

        /* change source of C0ROOT to XTAL */
        _C0RootFromMainClk();

#if !defined(__ISW_8533D__) && !defined(__ISW_8532B__) && !defined(__ISW_8556R__)
#ifdef DISABLE_PLLS
        HalClkgenBbtopSetClkSpeed(BBTOP_CLK_MIU, CLKGEN_26MHZ, CLKSRC_XTAL);
#endif /* DISABLE_PLLS */
#endif
        HalClkgenBbtopSetClkSpeed(BBTOP_CLK_XIU, CLKGEN_26MHZ, CLKSRC_XTAL);
        HalClkgenBbtopSetClkSpeed(BBTOP_CLK_DB_BUS, CLKGEN_26MHZ, CLKSRC_XTAL);
#else
        DrvClkgenInit(CLKGEN_156MHZ);
#endif /* C0_ALWAYS_USE_XTAL_26M */
    }

#ifndef DISABLE_UART
    cliPrintf("Before sleep\n");
#endif
    SYS_UDELAY(200000);

#ifdef DISABLE_PLLS
#if !defined(__ISW_8533D__) && !defined(__ISW_8532B__) && !defined(__ISW_8556R__)
    g_ptKePll->reg_pll21_enable = 0x00UL;
    g_ptKePll->reg_pll21_enable_ovrw = 0x01UL;
#endif
    g_ptKePll->reg_pll22_enable = 0x00UL;
    g_ptKePll->reg_pll22_enable_ovrw = 0x01UL;
#else
    // disable overwrite bit of PLL21 and PLL22
#if !defined(__ISW_8533D__) && !defined(__ISW_8532B__) && !defined(__ISW_8556R__)
    g_ptKePll->reg_pll21_enable = 0x01UL;
    g_ptKePll->reg_pll21_enable_ovrw = 0x00UL;
#endif
    g_ptKePll->reg_pll22_enable = 0x01UL;
    g_ptKePll->reg_pll22_enable_ovrw = 0x00UL;
#endif

    temp_B3();

    // ASURA_ACTIVE_MODE: enable LDO
    // ASURA_LQ_MODE:     enable LDO + LQ mode
    // ASURA_STDBY_MODE:  disable LDO

    // function parameters: (active state, active volts, standby state, standby volts)
    // p.s: 0x00 is pedding with no meaning

    // asura LDOs
    HalVABBControl( ASURA_ACTIVE_MODE, ASURA_VABB_3_2,        ASURA_LQ_MODE,    0x00);
    HalVtcxoControl(ASURA_ACTIVE_MODE, ASURA_VTCXO_2_6,       ASURA_STDBY_MODE, 0x00);
    HalVRF1Control( ASURA_ACTIVE_MODE, ASURA_VRF_2_8,         ASURA_LQ_MODE,    0x00);
    HalVRF2Control( ASURA_ACTIVE_MODE, ASURA_VRF_2_8,         ASURA_LQ_MODE,    0x00);
    HalVper1Control(ASURA_ACTIVE_MODE, ASURA_VPER1_2_8,       ASURA_STDBY_MODE, 0x00);
    HalVper2Control(ASURA_ACTIVE_MODE, ASURA_VPER2_2_8,       ASURA_STDBY_MODE, 0x00);
    HalVper3Control(ASURA_ACTIVE_MODE, ASURA_VPER3_1_8,       ASURA_STDBY_MODE, 0x00);
    HalVper4Control(ASURA_ACTIVE_MODE, ASURA_VPER4_2_8,       ASURA_STDBY_MODE, 0x00);
    HalVBuckControl(ASURA_ACTIVE_MODE, ASURA_VBUCK_1_20,      ASURA_STDBY_MODE, 0x00);
    HalVSTDControl( ASURA_ACTIVE_MODE, ASURA_VSTD_DIFF_300,   ASURA_LQ_MODE,    0x00);

    // big3 LDOs
    HalVMEMControl( ASURA_ACTIVE_MODE, ASURA_VOLT_NOT_CHANGE, ASURA_LQ_MODE,    ASURA_VOLT_NOT_CHANGE);
    HalVLCMControl( ASURA_ACTIVE_MODE, PMU_VLCM_2_8,          ASURA_LQ_MODE,    PMU_VLCM_2_8);
    HalVIO1Control( ASURA_ACTIVE_MODE, PMU_VIO1_2_8,          ASURA_LQ_MODE,    PMU_VIO1_2_8);
    HalVIO2Control( ASURA_ACTIVE_MODE, PMU_VIO2_1_8,          ASURA_LQ_MODE,    PMU_VIO2_1_8);
    HalVSIM1Control(ASURA_ACTIVE_MODE, PMU_VSIM1_1_8,         ASURA_STDBY_MODE, PMU_VSIM1_1_8);
    HalVSIM2Control(ASURA_ACTIVE_MODE, PMU_VSIM2_2_8,         ASURA_STDBY_MODE, PMU_VSIM2_2_8);

    // MTCMOS
    HalVMMPControl(ASURA_STDBY_MODE, 0x00, 0x00, 0x00);
    HalVIMIControl(ASURA_STDBY_MODE, 0x00, 0x00, 0x00);

    HalAudioInit();

    HalClkgenBbtopSetClkSpeed(BBTOP_CLK_EMI_32K,     CLKGEN_0HZ,      CLKSRC_NONE);
    HalClkgenBbtopSetClkSpeed(BBTOP_CLK_AUX_32K,     CLKGEN_0HZ,      CLKSRC_NONE);
    HalClkgenBbtopSetClkSpeed(BBTOP_CLK_AUX_16K,     CLKGEN_0HZ,      CLKSRC_NONE);
    HalClkgenBbtopSetClkSpeed(BBTOP_CLK_AUX_128,     CLKGEN_0HZ,      CLKSRC_NONE);
    HalClkgenBbtopSetClkSpeed(BBTOP_CLK_AUDIO_32K,   CLKGEN_0HZ,      CLKSRC_NONE);
    HalClkgenBbtopSetClkSpeed(BBTOP_CLK_AUDIO_128,   CLKGEN_0HZ,      CLKSRC_NONE);
    HalClkgenBbtopSetClkSpeed(BBTOP_CLK_GPS_32K,     CLKGEN_0HZ,      CLKSRC_NONE);
    HalClkgenBbtopSetClkSpeed(BBTOP_CLK_GPS1_32K,    CLKGEN_0HZ,      CLKSRC_NONE);

#if !defined(__ISW_8533D__) && !defined(__ISW_8532B__) && !defined(__ISW_8556R__)
#if defined(C0_ALWAYS_USE_XTAL_26M)
    HalPllAbbClkSwitchEnable(EN_PLL22_DIV2_DBB,   FALSE); // C0ROOT
#endif
    HalPllAbbClkSwitchEnable(EN_PLL22_DIV3_DBB,   FALSE); // Don't use UART before you enable A0ROOT
    HalPllAbbClkSwitchEnable(EN_PLL22_DIV5_DBB,   FALSE);
    HalPllAbbClkSwitchEnable(EN_PLL22_DIV6_DBB,   FALSE);
    HalPllAbbClkSwitchEnable(EN_PLL21_DBB,        FALSE);
    HalPllAbbClkSwitchEnable(EN_MMP_312M,         FALSE); // EMI_SCLK
#ifdef DISABLE_PLLS
    HalPllAbbClkSwitchEnable(EN_MMP_156M,         FALSE); // MIU
#endif
    HalPllAbbClkSwitchEnable(EN_MMP_104M,         FALSE);
    HalPllAbbClkSwitchEnable(EN_MMP_62P4M,        FALSE);
    HalPllAbbClkSwitchEnable(EN_MMP_60M12M,       FALSE);
    HalPllAbbClkSwitchEnable(EN_MMP_MCLK,         FALSE);
    HalPllAbbClkSwitchEnable(EN_RF_ANA_26M,       FALSE);
    HalPllAbbClkSwitchEnable(EN_RF_DIG_26M,       FALSE);
    HalPllAbbClkSwitchEnable(EN_SAR_2M,           FALSE);
    HalPllAbbClkSwitchEnable(EN_USB_24M,          FALSE);
    HalPllAbbClkSwitchEnable(EN_DDR48M,           FALSE);
    HalPllAbbClkSwitchEnable(EN_FM_26M,           FALSE);
    HalPllAbbClkSwitchEnable(EN_AUDIO_48M,        FALSE);
    HalPllAbbClkSwitchEnable(EN_EMI_624MD3,       FALSE);
    HalPllAbbClkSwitchEnable(EN_EMI_624MD5,       FALSE);
    HalPllAbbClkSwitchEnable(EN_EMI_624MD7,       FALSE);
    HalPllAbbClkSwitchEnable(EN_EMI_624MD9,       FALSE);
    HalPllAbbClkSwitchEnable(EN_EMI_624MD11,      FALSE);
    HalPllAbbClkSwitchEnable(EN_EMI_624MD13,      FALSE);
#else
    HalPllAbbClkSwitchEnable(EN_CLK_RF_ANA_26M,         FALSE);
    HalPllAbbClkSwitchEnable(EN_CLK_RF_DIG_26M,         FALSE);
    HalPllAbbClkSwitchEnable(EN_CLK_DDR48M,         FALSE);
    HalPllAbbClkSwitchEnable(EN_CLK_FM_26M,         FALSE);
    HalPllAbbClkSwitchEnable(EN_CLK_AUDIO_48M_3V,         FALSE);
    HalPllAbbClkSwitchEnable(EN_CLK_PLL_312M,         FALSE);
    HalPllAbbClkSwitchEnable(EN_CLK_PLL_156M,         FALSE);
    HalPllAbbClkSwitchEnable(EN_CLK_PLL_104M,         FALSE);
    HalPllAbbClkSwitchEnable(EN_CLK_PLL_62P4M,         FALSE);
    HalPllAbbClkSwitchEnable(EN_CLK_PLL_60M_12M,         FALSE);
    HalPllAbbClkSwitchEnable(EN_CLK_PLL_MCLK,         FALSE);
    HalPllAbbClkSwitchEnable(EN_CLK_PLL_208M,         FALSE);
    HalPllAbbClkSwitchEnable(EN_CLK_PLL_124P8M,         FALSE);
    HalPllAbbClkSwitchEnable(EN_CLK_PLL_89P1M,         FALSE);
    HalPllAbbClkSwitchEnable(EN_CLK_PLL_69P3M,         FALSE);
    HalPllAbbClkSwitchEnable(EN_CLK_PLL_56P7M,         FALSE);
    HalPllAbbClkSwitchEnable(EN_CLK_PLL_48M,         FALSE);
#endif


    // USB
    *(volatile int*)0x74003E00 = 0xFFC7UL;
    *(volatile int*)0x74003E10 = 0x0483UL;

#if !defined(C0_ALWAYS_USE_XTAL_26M)
    DrvClkgenChangeCpuClock(CLKGEN_26MHZ);
#endif

#if 0 /* sleep only */
    //(1) Disable SM_WAIT_CPU_PWD
    *(volatile int*)0x34000030 &= ~(0x0800UL);

    // (2) Set AWAKW for sleep mode cycle
    *(volatile int*)0x3400AD28 = 0x3FFFFUL;

    //(3) Request sleep mode SM32_req
    *(volatile int*)0x3400AD14 = 0x0800UL;

    //cp15_write_reg7_wait_for_interrupt(); // put CPU in power down
#else /* disable ARM MTCMOS */
    //NOT Wait CPU Pwdn before cut 13 Mhz
    g_ptKeCmu->gprCtrl0 |= (SM_WAIT_CPU_PWD);

    // Unmask CMU/TBU wakeup interrupt
    g_ptW5IrqControl->u32_WakeUpMask1 = (0x1<<(TBU_WAKEUP_CPU_IT_POS-32));
    g_ptW5IrqControl->u32_WakeUpMask0 = 0;
    g_ptW5IrqControl->u32_Mask1       = (0x1<<(TBU_WAKEUP_CPU_IT_POS-32));

    // clear TBU wakeup interrupt
    g_ptW5IrqControl->u32_Ack1       = (0x1<<(TBU_WAKEUP_CPU_IT_POS-32));
    g_ptW5IrqControl->u32_Clear1     = (0x1<<(TBU_WAKEUP_CPU_IT_POS-32));

    g_ptW5TbuC->u16_FrameLength = 0x0300;
    g_ptW5TbuC->u32_Control     = TBU_SOFTLATCH;

    g_ptW5TbuC->u32_SleepTimeDuration = 0x3FFFFUL; //nSleepTime(ms)*32(KHz) = # of 32K cycles
    g_ptW5TbuC->u32_LockTime          = 0x01040A05;
    // PLL lock 5*2 clk32K PERIOD (305us)
    // PLL start 10
    // Osc lock 4
    // Osc delay 1
    *(volatile u32*)(0x3400AD5C) |= (0x1<<24); //CPU_RECALL_SET
    *(volatile u32*)(0x3400AD5C) &= ~(0xFF);   //clear CPU_RECALL_TIME
    *(volatile u32*)(0x3400AD5C) |= (0xF);     //set CPU_RECALL_TIME

    ItMask = RTK2_DISABLE_K();

    // ASYNC_WU: Asynchronous Wake Up flag(Write '1' in the register to clear it)
    g_ptW5TbuC->u32_Control |= TBU_WKUP_ASYNC;
    // CPU_WAKE_UP_INT_MASK: Writing 0 to this bit masks the CPU_WAKE_UP_INT
    g_ptW5TbuC->u32_IntCtrl |= CPU_WAKE_UP_INT_ENA;
    // CPU_WAKE_UP_INT_CLEAR : Writing 1 to this bit reset the interrupt
    g_ptW5TbuC->u32_IntClear |= CPU_WAKE_UP_INT_ACK;

#if 0 /* disable testout for LCM current */
    if (Hal_IoChipTestOut24Bit(0x7, 0x6) == FALSE)
    {
        cliPrintf("Hal_IoChipTestOut24Bit fail\n");
    }

    g_tBbTop->reg_debug_sel = 0x2;
#endif

    sys_inSleepMode = 1;
    sys_wakeUpFromReset = 0;
    sys_inSleepMode = 0;

    RTK2_ENABLE_K(ItMask);
#endif

#if !defined(C0_ALWAYS_USE_XTAL_26M)
    DrvClkgenChangeCpuClock(CLKGEN_156MHZ);
#endif

#ifndef DISABLE_UART
    HalPllAbbClkSwitchEnable(EN_PLL22_DIV3_DBB,   TRUE); // Restore A0ROOT
#endif

    /* wait 1s */
    SYS_UDELAY(1000000);

#ifndef DISABLE_UART
    cliPrintf("After sleep\n");
#endif

    return eCLI_PARSE_OK;
}

#else

static int _sleepHandler(CLI_t *pCli, char *p)

{
    //u32 nSleepTime = 1; //For BT timer wakeup
    u32 nSleepTime = 0x800; //For OSTick2 timer wakeup
    u32 nWakeupTime;
    u32 ItMask;

g_ptAsuraRtcReg->spare0 = 0x4321;
    //*(volatile u32*)(0x3400002C) = 0x03;
    //No PAD power cut
    //*(volatile u32*)(0x34000030) &= 0xFFFFFFFD;
    //Enable clock during sleep mode
    //*(volatile u32*)(0x34000030) |= 0x01000000;

    //Just make sure standby_en is on
    g_ptAsuraPMUReg->pmu_top_1 = 0x01;

    //NOT Wait CPU Pwdn before cut 13 Mhz
    g_ptKeCmu->gprCtrl0 |= (SM_WAIT_CPU_PWD);

    // Unmask CMU/TBU wakeup interrupt
    g_ptW5IrqControl->u32_WakeUpMask1 = (0x1<<(TBU_WAKEUP_CPU_IT_POS-32));
    g_ptW5IrqControl->u32_Mask1       = (0x1<<(TBU_WAKEUP_CPU_IT_POS-32));
    //g_ptW5IrqControl->u32_WakeUpMask0 = 0x1 << 7;
    //g_ptW5IrqControl->u32_Mask0       = 0x1 << 7;
    *(volatile u32*)(0x3400187c) = (0x01UL<<OSTICK2_IT_POS);
      *(volatile u32*)(0x3400181c) = (0x01UL<<OSTICK2_IT_POS);


    // clear TBU wakeup interrupt
    g_ptW5IrqControl->u32_Ack1       = (0x1<<(TBU_WAKEUP_CPU_IT_POS-32));
    g_ptW5IrqControl->u32_Clear1     = (0x1<<(TBU_WAKEUP_CPU_IT_POS-32));
    //g_ptW5IrqControl->u32_Ack0       = 0x1 << 7;
    //g_ptW5IrqControl->u32_Clear0     = 0x1 << 7;
    *(volatile u32*)(0x3400185c) = (0x01UL<<OSTICK2_IT_POS);
      *(volatile u32*)(0x34001854) = (0x01UL<<OSTICK2_IT_POS);

    g_ptW5TbuC->u16_FrameLength = 0x0300;
    g_ptW5TbuC->u32_Control = TBU_SOFTLATCH;
    g_ptW5TbuC->u32_SleepTimeDuration = 0xFFFFF;//((nSleepTime+2)*10*32); //nSleepTime(ms)*32(KHz) = # of 32K cycles
    g_ptW5TbuC->u32_LockTime          = 0x01040A05;

    // PLL lock 5*2 clk32K PERIOD (305us)
    // PLL start 10
    // Osc lock 4
    // Osc delay 1
    *(volatile u32*)(0x3400AD5C) &= ~(0x1<<24); //clear CPU_RECALL_SET

    //*(volatile u32*)(0x3400002C) = 0x03;//Can't wakeup
    //cliPrintf("Sleep time is %d(ms).. \n", nSleepTime);
    //SYS_UDELAY(200000);
    //*(volatile u32*)(0x3400002C) = 0x03;//Can't wakeup
    cliPrintf("Entering sleep mode... \n\n");
    //SYS_UDELAY(20000);

    /*
    { //BT timer block for wakeup event
            *(volatile int*)0x74006E8C= (nSleepTime+2)*32;
            *(volatile int*)0x74006E9C |= 0x1;
            //SYS_UDELAY(2000);
    }
    */
    {//Enable OsTick2 Timer (Unit:4.615 ms)
    cliPrintf("Config OsTick2 Timer wakeup...:%d X4.615ms\n", nSleepTime);
    g_ptW5SysTimer->u32_OsTick2Config  = 0x0; //LENGTH[23:0] ENABLE[28]
    g_ptW5SysTimer->u32_IntMask |= SYSTIMER_OSTICK2_MSK;
    g_ptW5SysTimer->u32_IntClear |= SYSTIMER_OSTICK2_MSK;
    g_ptW5SysTimer->u32_OsTick2Config  = 0x10000000 | nSleepTime; //LENGTH[23:0] ENABLE[28]
  }

    g_ptW5SysTimer->u32_OsTickConfig  = 0x0; //LENGTH[23:0] ENABLE[28]
    g_ptW5SysTimer->u32_OsTickConfig  = 0x10FFFFFF; //LENGTH[23:0] ENABLE[28]

    ItMask = RTK2_DISABLE_K();

    // ASYNC_WU: Asynchronous Wake Up flag(Write '1' in the register to clear it)
    g_ptW5TbuC->u32_Control |= TBU_WKUP_ASYNC;

    // CPU_WAKE_UP_INT_MASK: Writing 0 to this bit masks the CPU_WAKE_UP_INT
    g_ptW5TbuC->u32_IntCtrl |= CPU_WAKE_UP_INT_ENA;
    // CPU_WAKE_UP_INT_CLEAR : Writing 1 to this bit reset the interrupt
    g_ptW5TbuC->u32_IntClear |= CPU_WAKE_UP_INT_ACK;
    sys_wakeUpFromReset = 0;
    g_ptW5TbuC->u32_Control |= TBU_SM32K_REQ;   // Go to sleep mode
    //cp15_write_reg7_wait_for_interrupt(); // put CPU in power down
    HalPmSleepWaitForInterrupt(); // put CPU in power down

    //Init SoftTimer for SYS_UDELAY()
    //DRV_TIMSOFT32K_START(DRV_TIMSOFT_MAX_COUNT);
    g_ptW5SysTimer->u32_SoftTimerCfg = 0x0;
    g_ptW5SysTimer->u32_SoftTimerCfg = 0x00FFFFFF;  //LENGTH[23:0]
    g_ptW5SysTimer->u32_SoftTimerCfg |= 0x10000000; //ENABLE[28]
    {//Stop OsTick2 timer
          g_ptW5SysTimer->u32_OsTick2Config  = 0x00; //LENGTH[23:0] ENABLE[28]
        g_ptW5SysTimer->u32_IntMask &= ~SYSTIMER_OSTICK2_MSK;
        g_ptW5SysTimer->u32_IntClear |= SYSTIMER_OSTICK2_MSK;
    }

    nWakeupTime = g_ptW5SysTimer->u32_OsTickCounter;//OSTICK2 counter
    g_ptW5SysTimer->u32_OsTickConfig  = 0x00FFFFFF; //LENGTH[23:0] ENABLE[28]

    cliPrintf("wakeup from sleep mode %d... \n", sys_wakeUpFromReset);
    cliPrintf("sleep duration %d(ms)\n", (nWakeupTime)*12*5/13);
g_ptAsuraRtcReg->spare0 = 0xAACC;
    RTK2_ENABLE_K(ItMask);

    return eCLI_PARSE_OK;

HELP_EXIT:
    return eCLI_PARSE_ERROR;

HELP_EXIT1:
    return eCLI_PARSE_ERROR;

}
#endif

int SleepTest(void)
{
    _sleepHandler(NULL, NULL);
}

static int _testoutHandler(CLI_t *pCli, char *p)
{
    u32 bus24b_sel, test_out_mode;

    if (CliTokenCount(pCli) == 2)
    {
        if (CliTokenPopNum(pCli, &bus24b_sel, 0) != eCLI_PARSE_OK)
            goto HELP_EXIT;
        if (CliTokenPopNum(pCli, &test_out_mode, 0) != eCLI_PARSE_OK)
            goto HELP_EXIT;

        if (Hal_IoChipTestOut24Bit(bus24b_sel, test_out_mode) == FALSE)
        {
            cliPrintf("Hal_IoChipTestOut24Bit fail\n");
            goto HELP_EXIT;
        }

        return eCLI_PARSE_OK;
    }

HELP_EXIT:
    return eCLI_PARSE_ERROR;
}


static int _clkoutHandler(CLI_t *pCli, char *p)
{
    u32 out_bit, divider;

    if (CliTokenCount(pCli) == 2)
    {
        if (CliTokenPopNum(pCli, &out_bit, 0) != eCLI_PARSE_OK)
            goto HELP_EXIT;
        if (CliTokenPopNum(pCli, &divider, 0) != eCLI_PARSE_OK)
            goto HELP_EXIT;

        if (out_bit > 23)
        {
            cliPrintf(("invalid out_bit= %08x\n"), out_bit);
            goto HELP_EXIT;
        }

        if (Hal_IoChipTestOutSingleClock(out_bit, divider) == FALSE)
        {
            cliPrintf(("Hal_IoChipTestOutSingleClock fail\n"));
            goto HELP_EXIT;
        }

        return eCLI_PARSE_OK;
    }

HELP_EXIT:
    return eCLI_PARSE_ERROR;
}

static int _delayHandler(CLI_t *pCli, char *p)
{
    u32 delay_usecs;

    if (CliTokenCount(pCli) == 1)
    {
        if (CliTokenPopNum(pCli, &delay_usecs, 0) != eCLI_PARSE_OK)
            goto HELP_EXIT;
        SYS_UDELAY(delay_usecs);
        return eCLI_PARSE_OK;
    }

HELP_EXIT:
    return eCLI_PARSE_ERROR;
}
#endif
#endif //__FIXME__

#if defined(__VER_USB__) || defined(__VER_USBHOST__)
static int _usbHandler(CLI_t *pCli, char *p)
{
    u32 nUsbClass;

    if (CliTokenCount(pCli) == 1)
    {
        if (CliTokenPopNum(pCli, &nUsbClass, 0) != eCLI_PARSE_OK)
            goto HELP_EXIT;
        cliPrintf("Test USBHost driver:\n");
        if (nUsbClass == 200) {
            cliPrintf("-> MApi_USBHost_Init():\n");
            MApi_USBHost_Init();
        }
        else if (nUsbClass == 300) {
            cliPrintf("-> uvcl_init():\n");
            uvcl_init();
        }
        else {
            //cliPrintf("-> chip_storage_init(%d):\n", nUsbClass);
            //chip_storage_init(nUsbClass);
            //chip_storage_stop(nUsbClass);
        }
        //UsbTest(nUsbClass);
        return eCLI_PARSE_OK;
    }

HELP_EXIT:
    return eCLI_PARSE_ERROR;
}
#endif

#ifndef __I_SW_OS_G1__
static int _hCacheOn(CLI_t *pCli, char *p)
{
    sys_Enable_cache();
    return eCLI_PARSE_OK;
}

static int _hCacheOff(CLI_t *pCli, char *p)
{
    sys_Disable_cache();
    return eCLI_PARSE_OK;
}

static int _hICacheOn(CLI_t *pCli, char *p)
{
    sys_Enable_icache();
    return eCLI_PARSE_OK;
}

static int _hICacheOff(CLI_t *pCli, char *p)
{
    sys_Disable_icache();
    return eCLI_PARSE_OK;
}
#endif

/*
 * cli - main entry point.  Should be spawned as a task.
 */

void isw_cli_main(void)
{
#ifdef __TEST_LOAD__
        cli_test_load(&_tCliMain, _atRootTbl);
#else
        cli(&_tCliMain, _atRootTbl);
#endif
}
