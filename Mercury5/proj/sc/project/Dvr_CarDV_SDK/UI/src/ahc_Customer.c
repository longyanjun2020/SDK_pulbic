//==============================================================================
//
//  File        : Ahc_showlogo.c
//  Description :
//  Author      :
//  Revision    : 1.0
//
//==============================================================================

#include "includes_fw.h"
#include "disp_drv.h"
#include "mmpf_storage_api.h"
#include "mmpf_sf.h"
#include "ahc_common.h"
#include "mmp_display_inc.h"
#include "cam_os_wrapper.h"
#include "ahc_gui.h"
#include "mmp_graphics_inc.h"
#include "mmp_dma_inc.h"
#include "ColorDefine.h"
#include "IconDefine.h"
#include "cust_component_cfg.h"
#include "component_cfg.h"
#include "component_display.h"
#include "ahc_modectl.h"
#include "Config_SDK.h"

//==============================================================================
//
//                              COMPILING OPTIONS
//
//==============================================================================

#define BOOT_IMG_FMT_BMP    (0)
#define BOOT_IMG_FMT_JPG    (1)
#define BOOT_IMG_FORMAT     (BOOT_IMG_FMT_JPG) //(BMP:JPG)/(0:1)

//==============================================================================
//
//                              CONSTANT TYPE_DEF
//
//==============================================================================
#define SECTOR_SIZE         512
#define MBR_ADDRESS       ((u32)0)       /* Master Boot Record address   */
#define POWER_ON_IDX                    (0)
#define BATTERY_LOW_IDX                 (1)

// Partition 10 for SF:0    // Code Resource
// Partition 11 for SF:1    // Factory Resource
// Partition 12 for SF:2    // User Resource
// Partition 13 for SF:3    // User Resource
// ...
#define SPLASH_PARTITION_LOGO   (14) // Notice : Sync with DiskInfo.ini

#define GET_BYTE(p)     (*p); p += 1;
#define GET_WORD(p)     (*p) + (*(p + 1) << 8); p += 2;
#define GET_DWORD(p)    (*p) + (*(p + 1) << 8) + (*(p + 2) << 16) + (*(p + 3) << 24); p += 4;
#define GET_LONG(p)     (*p) + (*(p + 1) << 8) + (*(p + 2) << 16) + (*(p + 3) << 24); p += 4;

#define GET_WORD_BE(p)  (*p << 8) + (*(p + 1)); p += 2;
typedef unsigned short  WORD;
typedef unsigned int    DWORD;
typedef unsigned long   LONG;

#if (BOOT_IMG_FORMAT == BOOT_IMG_FMT_BMP)
#define BM              (0x424D)//('B') + ('M')
#define BITMAPFILEHEADER_SIZE   14
#define BITMAPINFOHEADER_SIZE   40

#define SET_BITMAPFILEHEADER(sp, b)     \
        b.bfType            = GET_WORD_BE(sp)   \
        b.bfSize            = GET_DWORD(sp) \
        b.bfReserved1       = GET_WORD(sp)  \
        b.bfReserved2       = GET_WORD(sp)  \
        b.bfOffBits         = GET_DWORD(sp) \

#define SET_BITMAPINFOHEADER(sp, b)     \
        b.biSize            = GET_DWORD(sp) \
        b.biWidth           = GET_LONG(sp)  \
        b.biHeight          = GET_LONG(sp)  \
        b.biPlanes          = GET_WORD(sp)  \
        b.biBitCount        = GET_WORD(sp)  \
        b.biCompression     = GET_DWORD(sp) \
        b.biSizeImage       = GET_DWORD(sp) \
        b.biXPelsPerMeter   = GET_LONG(sp)  \
        b.biYPelsPerMeter   = GET_LONG(sp)  \
        b.biClrUsed         = GET_DWORD(sp) \
        b.biClrImportant    = GET_DWORD(sp)

#elif (BOOT_IMG_FORMAT == BOOT_IMG_FMT_JPG)
#define JPG_SOI         (0xFFD8)
#define JPG_JFIF        (0xFFE0)
#define JPG_EXIF        (0xFFE1)
#define JPG_SOF         (0xFFC0)
#define JPG_EOI         (0xFFD9)
#endif

//==============================================================================
//
//                              STRUCTURE
//
//==============================================================================

typedef struct {
    int     img_w;
    int     img_h;
    int     img_clrs;
    int     img_Size;
} IMG;

typedef struct tagRGBQUAD {
    unsigned char rgbBlue;
    unsigned char rgbGreen;
    unsigned char rgbRed;
    unsigned char rgbReserved;
} RGBQUAD;

typedef struct tagBITMAPINFOHEADER {
    DWORD biSize;
    LONG  biWidth;
    LONG  biHeight;
    WORD  biPlanes;
    WORD  biBitCount;
    DWORD biCompression;
    DWORD biSizeImage;
    LONG  biXPelsPerMeter;
    LONG  biYPelsPerMeter;
    DWORD biClrUsed;
    DWORD biClrImportant;
} BITMAPINFOHEADER, *PBITMAPINFOHEADER;

typedef struct tagBITMAPFILEHEADER {
    WORD  bfType;
    DWORD bfSize;
    WORD  bfReserved1;
    WORD  bfReserved2;
    DWORD bfOffBits;
} BITMAPFILEHEADER, *PBITMAPFILEHEADER;

typedef struct tagBITMAPINFO {
    BITMAPINFOHEADER bmiHeader;
    RGBQUAD          bmiColors[1];
} BITMAPINFO, *PBITMAPINFO;

typedef struct {
    U16P XSize;
    U16P YSize;
    U16P BytesPerLine;
    U16P BitsPerPixel;
    U8 GUI_UNI_PTR * pData;
    GUI_LOGPALETTE GUI_UNI_PTR * pPal;
    GUI_BITMAP_METHODS * pMethods;
} GUI_BITMAP_VAR;

//==============================================================================
//
//                              Local varible
//
//==============================================================================

#if (BOOT_IMG_FORMAT == BOOT_IMG_FMT_BMP)
static BITMAPFILEHEADER bf;
static BITMAPINFOHEADER bi;
#endif

GUI_BITMAP_VAR bmwelcome320_16_VAR = {
  320, /* XSize */
  240, /* YSize */
  640, /* BytesPerLine */
  16, /* BitsPerPixel */
  (unsigned char *)NULL,  /* Pointer to picture data */
  NULL  /* Pointer to palette */
 ,GUI_DRAW_BMPM565//GUI_DRAW_BMP565
};

extern AHC_OSD_INSTANCE *m_OSD[];

//==============================================================================
//
//                              FUNCTION PROTOTYPES
//
//==============================================================================

static void ShowLowPowerWarning(AIT_STORAGE_INDEX_TABLE2 *bt, DISP_PROP *dp)
{
    int             x, y;
    unsigned char   *img;
    IMG             theimg;
#ifdef STARTUP_NEED_TO_SHOW_LOW_VOLTAGE
    OpenImage(bt, &theimg, &img, BATTERY_LOW_IDX);
    x = (dp->disp_w - theimg.img_w) >> 1;
    y = (dp->disp_h - theimg.img_h) >> 1;

    DrawPowerOnImage(dp, img, theimg.img_w, theimg.img_h, theimg.img_clrs, x, y);
#endif
}

void DrawPowerOnImage2Osd0(DISP_PROP *dp, unsigned char* img, int w, int h, int clrs, int x, int y)
{
    UINT8               bID0 = 0;
    UINT8               bID1 = 0;
    GUI_BITMAP*         pStIconID;
    UINT16              temw, temh;
    UINT16              puiColorFormat;
    UINT32              pulBufferAddr;
    UINT8               bBytePerPixel;

    MMPS_Display_SetWinTransparent(MMP_DISPLAY_WIN_MAIN, MMP_FALSE, 0);

    OSDDraw_EnterDrawing(&bID0, &bID1);
    AHC_OSDSetActive(bID0, 0);

    AHC_OSDSetFlipDrawMode(bID0, OSD_FLIP_DRAW_NONE_ENABLE);

    OSDDraw_ClearPanel(bID0, OSD_COLOR_WHITE);

    AHC_OSDGetBufferAttr(bID0, &temw, &temh, &puiColorFormat, &pulBufferAddr);
    //bBytePerPixel = (puiColorFormat == OSD_COLOR_RGB565)? 2:3;
    //memset(pulBufferAddr,0xff,temw*temh*2);

    bmwelcome320_16_VAR.pData = (unsigned char *)img;
    bmwelcome320_16_VAR.BitsPerPixel = clrs;
    bmwelcome320_16_VAR.XSize = w;
    bmwelcome320_16_VAR.YSize = h;

    if (clrs == 24) {
        bmwelcome320_16_VAR.pMethods = GUI_DRAW_BMP24SW;//GUI_DRAW_BMP24;
        bmwelcome320_16_VAR.BytesPerLine = w*3;
    }
    else if (clrs > 24) {
        printc("%s:unsupport bmp format\r\n",__func__);
    }

    pStIconID = (GUI_BITMAP*)&bmwelcome320_16_VAR;
    AHC_OSDDrawBitmap(bID0, pStIconID, x, y);

    MMPF_MMU_FlushDCacheMVA(pulBufferAddr, temw*temh*2);

    AHC_OSDSetActive(bID0, 1);
    OSDDraw_ExitDrawing(&bID0, &bID1);
}

#if (BOOT_IMG_FORMAT == BOOT_IMG_FMT_BMP)
int OpenBmp(AIT_STORAGE_INDEX_TABLE2 *bt, IMG *img, unsigned char** pptr, int idx)
{
    unsigned char   *buf,*tmp;
    int             total;
    int             patno;

    patno = SPLASH_PARTITION_LOGO + idx;
    buf = (unsigned char*)CamOsMemAlloc(1024*SECTOR_SIZE);//AIT_SYS_MEDIA_START_ADDR;

    MMPF_MMU_FlushDCacheMVA((MMP_ULONG)buf, BITMAPFILEHEADER_SIZE + BITMAPINFOHEADER_SIZE);
    MMPF_SF_FastReadData((bt->it[patno].ulStartSec<<9),
                         (int)buf,
                         BITMAPFILEHEADER_SIZE + BITMAPINFOHEADER_SIZE);

    tmp = buf;
    SET_BITMAPFILEHEADER(tmp, bf);
    SET_BITMAPINFOHEADER(tmp, bi);
    CamOsMemRelease((void*)buf);

    if (bf.bfType != BM)
        return (0);

    total = (((bi.biWidth * bi.biBitCount + 31) >> 5) << 2) * bi.biHeight;
    buf = (unsigned char*)CamOsMemAlloc(total);

    MMPF_SF_FastReadData((bt->it[patno].ulStartSec<<9) + bf.bfOffBits,
                         (int)buf,
                         total);
    MMPF_MMU_InvalidateDCacheMVA((MMP_ULONG)buf, total);

    img->img_w    = bi.biWidth;
    img->img_h    = bi.biHeight;
    img->img_clrs = bi.biBitCount;
    img->img_Size = total;
    *pptr = buf;

    return total;
}
#else
int OpenJpg(AIT_STORAGE_INDEX_TABLE2 *bt, IMG *img, unsigned char** pptr, int idx)
{
    unsigned char   *buf = NULL;
    int             patno = 0;
    unsigned int    ulInterStoreLen = 0;
    MMP_ERR         eRetErr = MMP_ERR_NONE;
    MMP_DSC_JPEG_INFO stJpegInfo = {0};

    patno = SPLASH_PARTITION_LOGO + idx;
    buf = (unsigned char*)CamOsMemAlloc(1024*SECTOR_SIZE);

    ulInterStoreLen = (bt->it[patno].ulSecSize<<9);

    MMPF_MMU_FlushDCacheMVA((MMP_ULONG)buf, ulInterStoreLen);

    MMPF_SF_FastReadData((bt->it[patno].ulStartSec<<9),
                         (int)buf,
                         ulInterStoreLen);

    stJpegInfo.ulJpegBufAddr    = buf;
    stJpegInfo.ulJpegBufSize    = ulInterStoreLen;
    stJpegInfo.bDecodeThumbnail = MMP_FALSE;

    #if (VERTICAL_LCD == VERTICAL_LCD_DEGREE_90) || (VERTICAL_LCD == VERTICAL_LCD_DEGREE_270)
    eRetErr = MMPS_DSC_PlaybackJpeg(&stJpegInfo,
                                    RTNA_LCD_GetAttr()->usPanelH,
                                    RTNA_LCD_GetAttr()->usPanelW);
    #else
    eRetErr = MMPS_DSC_PlaybackJpeg(&stJpegInfo,
                                    RTNA_LCD_GetAttr()->usPanelW,
                                    RTNA_LCD_GetAttr()->usPanelH);
    #endif

    CamOsMemRelease((void*)buf);

    return ulInterStoreLen;
}

void OpenJpgTest(void)
{
#define AHC_TEST_FILENAME "SD:\\001.JPG"
    extern MMP_ULONG64 m_ulJpegDecFileSize;

    MMP_ERR             eRetErr = MMP_ERR_NONE;
    MMP_DSC_JPEG_INFO   stJpegInfo = {0};
    const MMP_ULONG     ulJpgBufSize = SECTOR_SIZE*1024;
    void*               pvJpgBufVirt = NULL;
    static MMP_BYTE     path[256] = {0};

    MEMSET(path, 0, sizeof(path));
    STRCPY(path, AHC_TEST_FILENAME);

    AHC_DBG_ERR(1, "================POWER ON SHOW LOGO==============\r\n\r\n");

    pvJpgBufVirt = CamOsMemAlloc(ulJpgBufSize);

    MMPF_MMU_FlushDCacheMVA((MMP_ULONG)pvJpgBufVirt, ulJpgBufSize);

    MMPS_DSC_AllocFileNameBuf();

    MMPD_DSC_SetFileName(path, STRLEN(path));

    MMPF_JPEGD_ReadFileToMem(pvJpgBufVirt);

    MMPS_DSC_FreeFileNameBuf();

    stJpegInfo.ulJpegBufAddr    = (MMP_ULONG)pvJpgBufVirt;
    stJpegInfo.ulJpegBufSize    = m_ulJpegDecFileSize;//ulJpgBufSize;
    stJpegInfo.bDecodeThumbnail = MMP_FALSE;

    #if (VERTICAL_LCD == VERTICAL_LCD_DEGREE_90) || (VERTICAL_LCD == VERTICAL_LCD_DEGREE_270)
    eRetErr = MMPS_DSC_PlaybackJpeg(&stJpegInfo,
                                    RTNA_LCD_GetAttr()->usPanelH,
                                    RTNA_LCD_GetAttr()->usPanelW);
    #else
    eRetErr = MMPS_DSC_PlaybackJpeg(&stJpegInfo,
                                    RTNA_LCD_GetAttr()->usPanelW,
                                    RTNA_LCD_GetAttr()->usPanelH);
    #endif

    CamOsMemRelease(pvJpgBufVirt);
}
#endif //#if (BOOT_IMG_FORMAT == BOOT_IMG_FMT_BMP)

static int OpenImage(AIT_STORAGE_INDEX_TABLE2 *bt, IMG *img, unsigned char** pptr, int idx)
{
    unsigned char   *buf, *tmp;
    int             total = 0;
    int             patno;
    unsigned short  bwSOIType;

    patno   = SPLASH_PARTITION_LOGO;
    buf     = (unsigned char*)CamOsMemAlloc(SECTOR_SIZE);

    //Read 2byte(SOI) to judge format
    MMPF_MMU_FlushDCacheMVA((MMP_ULONG)buf, SECTOR_SIZE);
    MMPF_SF_FastReadData((bt->it[patno].ulStartSec<<9),(int)buf,SECTOR_SIZE);

    tmp = buf;
    bwSOIType = GET_WORD_BE(tmp);

    #if (BOOT_IMG_FORMAT == BOOT_IMG_FMT_JPG)
    if (bwSOIType == JPG_SOI) {
        total = OpenJpg(bt, img, pptr, idx);
    }
    #else
    if (bwSOIType == BM) {
        RTNA_DBG_Str(0, FG_YELLOW("BMP!\r\n"));
        total = OpenBmp(bt, img, pptr, idx);
    }
    #endif

    CamOsMemRelease((void*)buf);
    return total;
}

void Customer_CheckBattery(void)
{
    DISP_PROP       dp;
    MMPF_PANEL_ATTR *panel;
    AIT_STORAGE_INDEX_TABLE2 *pIndexTable = (AIT_STORAGE_INDEX_TABLE2 *)CamOsMemAlloc(SECTOR_SIZE);

    panel = RTNA_LCD_GetAttr();

    dp.disp_w = panel->usPanelW;
    dp.disp_h = panel->usPanelH;
    dp.disp_type = panel->ubDevType;

    if (0x00/*RGB_D24BIT_RGB888*/ == panel->ubRgbFmt) {
        dp.disp_clrs = 24;
    }
    else {
        dp.disp_clrs = 16;
    }

    if(m_OSD[0]){
        dp.disp_h = m_OSD[0]->height;
        dp.disp_w = m_OSD[0]->width;
        if( m_OSD[0]->Color == OSD_COLOR_RGB565)
            dp.disp_clrs = 16;//16bit
        else
            dp.disp_clrs = 24;//24
    }

    if(gbLCDRotate){
        dp.disp_type = DISP_LCDV;
        dp.disp_w = m_OSD[0]->height;;
        dp.disp_h = m_OSD[0]->width;
    }
    else{
        dp.disp_type = DISP_LCD;
    }

    MMPF_SF_ReadData(MBR_ADDRESS, (MMP_ULONG)pIndexTable, SECTOR_SIZE);
    if (pIndexTable->ulHeader == INDEX_TABLE_HEADER && pIndexTable->ulTail   == INDEX_TABLE_TAIL)
    {
        ShowLowPowerWarning(pIndexTable, &dp);
    }

    CamOsMemRelease((void*)pIndexTable);
}

void Customer_MeasureBattery(void)
{
#if POWER_ON_BATTERY_DETECTION
    MMP_USHORT uLoop = 0;
    MMP_ULONG uLevelSum = 0;
    MMP_USHORT level;

    #define BATTERY_MEASURE_TIMES       6
    printc("%s:Get battery voltage, customize your boot flow ++\r\n",__func__);

    for (uLoop = 0; uLoop < BATTERY_MEASURE_TIMES; ++uLoop)
    {
        AHC_SARADC_ReadData(BATTERY_DETECT_ADC_CHANNEL, &level);
        //PMUCtrl_ADC_Measure_Key(&level, &source, BATTERY_DETECT_ADC_CHANNEL);
        uLevelSum += level * REAL_BAT_VOLTAGE_RATIO_M / REAL_BAT_VOLTAGE_RATIO_N;
        RTNA_WAIT_MS(5);
    }

    uLevelSum /= BATTERY_MEASURE_TIMES;

    RTNA_DBG_Str(0, "Booting battery voltage = ");
    RTNA_DBG_Dec(0, uLevelSum);
    RTNA_DBG_Str(0, "mV\r\n");

    if (uLevelSum < BATTERY_LOW_BOOT_VOLT)
    {
        RTNA_DBG_Str(0, "Low Power!!!\r\n");
        Customer_CheckBattery();
        RTNA_WAIT_MS(BATTERY_LOW_BOOT_WARNING_TIME);
        PMUCtrl_Power_Off();
        while(1);
    }
#endif

}

void Customer_ShowLogo(void)
{
    DISP_PROP       dp;
    MMPF_PANEL_ATTR *panel;
    unsigned char   *img = NULL;
    IMG             theimg;
    int             x, y;
    AIT_STORAGE_INDEX_TABLE2 *pIndexTable = (AIT_STORAGE_INDEX_TABLE2 *)CamOsMemAlloc(SECTOR_SIZE);

    panel = RTNA_LCD_GetAttr();

    dp.disp_w = panel->usPanelW;
    dp.disp_h = panel->usPanelH;
    dp.disp_type = panel->ubDevType;

    if (0x00/*RGB_D24BIT_RGB888*/ == panel->ubRgbFmt) {
        dp.disp_clrs = 24;
    }
    else {
        dp.disp_clrs = 16;
    }

    if (m_OSD[0]) {
        dp.disp_h = m_OSD[0]->height;
        dp.disp_w = m_OSD[0]->width;
        if (m_OSD[0]->Color == OSD_COLOR_RGB565)
            dp.disp_clrs = 16;//16bit
        else
            dp.disp_clrs = 24;//24
    }

    if (gbLCDRotate) {
        dp.disp_type = DISP_LCDV;
        dp.disp_w = m_OSD[0]->height;;
        dp.disp_h = m_OSD[0]->width;
    }
    else {
        dp.disp_type = DISP_LCD;
    }

    MMPF_SF_ReadData(MBR_ADDRESS, (MMP_ULONG)pIndexTable, SECTOR_SIZE);

    if (pIndexTable->ulHeader == INDEX_TABLE_HEADER &&
        pIndexTable->ulTail   == INDEX_TABLE_TAIL)
    {
        // Show at Center of SCREEN
        if (OpenImage(pIndexTable, &theimg, &img, POWER_ON_IDX)) {

            #if (BOOT_IMG_FORMAT == BOOT_IMG_FMT_BMP)
            RTNA_DBG_Str(0, "##############################\r\n");
            RTNA_DBG_Str(0, "### PowerOnImage - LCD Out\r\n");
            RTNA_DBG_Str(0, "##############################\r\n");

            x = (dp.disp_w - theimg.img_w) >> 1;
            y = (dp.disp_h - theimg.img_h) >> 1;

            //trans~ color format
            if ((dp.disp_clrs == 16) && (theimg.img_clrs == 24))
            {
                RTNA_DBG_Str(0, "### SHOWLOGO:Need to trans~ color format!\r\n");
            }

            if (x >= 0 && y >= 0) {
                DrawPowerOnImage2Osd0(&dp, img, theimg.img_w, theimg.img_h, theimg.img_clrs, x, y);
            }

            CamOsMemRelease((void*)img);
            #endif
        }
    }

    CamOsMemRelease((void*)pIndexTable);
}

void Customer_ShowLogo_Exit(void)
{
#if (BOOT_IMG_FORMAT == BOOT_IMG_FMT_JPG)
    MMPS_DSC_ExitJpegPlayback();
#endif
}

void Customer_init(void)
{
    //Confirm the voltage is above the safe value.
    Customer_MeasureBattery();

    if ((AHC_GetBootingSrc() & PWR_ON_BY_GSENSOR) != PWR_ON_BY_GSENSOR) {
        MMP_USHORT usPanelW = RTNA_LCD_GetAttr()->usPanelW;
        MMP_USHORT usPanelH = RTNA_LCD_GetAttr()->usPanelH;

        Customer_ShowLogo();

        MMPS_Display_SetDispCompAttr(   0, 0, usPanelW, usPanelH,
                                        0, 0, usPanelW, usPanelH,
                                        0, 0, usPanelW, usPanelH,
                                        0, 0, usPanelW, usPanelH,
                                        MMP_FALSE, MMP_FALSE);

        OpenScript(COMPO_SCRIPT_DISPLAY);

        DrvLCDRefresh();

        RTNA_LCD_Backlight(MMP_TRUE);
    }

    #if (SUPPORT_SECURITY_IC)
    PassIc_Detect();
    #endif
}
