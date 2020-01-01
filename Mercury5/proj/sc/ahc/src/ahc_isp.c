//==============================================================================
//
//  File        : AHC_ISP.c
//  Description : AHC ISP control function
//  Author      :
//  Revision    : 1.0
//
//==============================================================================

/*===========================================================================
 * Include files
 *===========================================================================*/

#include "ahc_isp.h"
#include "isp_if.h"
#include "MenuSetting.h"
#include "mmps_sensor.h"
#include "mmps_fs.h"
#include "isp_cfg.h"
#include "snr_cfg.h"
#include "ahc_config_dummy.h"
#include "mmp_usb_inc.h"
#include "ait_utility.h"

/*===========================================================================
 * Macro Define
 *===========================================================================*/

#define AHC_CONTRAST_MIN    (-128)
#define AHC_CONTRAST_MAX    (128)
#define AHC_SATURATION_MIN  (-128)
#define AHC_SATURATION_MAX  (128)
#define AHC_GAMMA_MIN       (-128)
#define AHC_GAMMA_MAX       (128)
#define AHC_SHARPNESS_MIN   (-128)
#define AHC_SHARPNESS_MAX   (128)

/*===========================================================================
 * Global variable
 *===========================================================================*/

static AHC_BOOL     m_bEnableFastAeAwb      = AHC_FALSE;

/*===========================================================================
 * Main body
 *===========================================================================*/

#if  (defined(SUPPORT_ISP_CALIBRATION) && (SUPPORT_ISP_CALIBRATION == 1))

#define ISP_CALI_PARTITION          "1"
#define ISP_CALI_FILENAME_PREFIX    "ISP_Calibration_"
#define ISP_CALI_FILENAME_EXT       ".bin"
#define ISP_CALI_FILE_NUM           2

#define ISP_CALI_HEADER 1
//#define   COLOR_TEMP 5100

#define LUX 800 //don't care
#define AWB_CALI_TABLE_SIZE 8
#define LS_CALI_TABLE_SIZE ((2*8)+(256*2*3))
#define CS_CALI_TABLE_SIZE ((2*7)+(41*2)+(31*2)+(42*32*2*3))

#define CALI_DATA_SIZE (28 + AWB_CALI_TABLE_SIZE+LS_CALI_TABLE_SIZE+CS_CALI_TABLE_SIZE)
//#define CALI_DATA_SIZE 0x2660 //0x265C used, 9824, 9 byte:migic word, 8byte:AWB, Luma table: 1552 byte, Chroma:8222 byte,....

ISP_UINT8 CaliDataBuf[CALI_DATA_SIZE+1]; //LAB
ISP_UINT8* CaliData; //LAB
MMP_USHORT temp_cali[10]; //LAB
MMP_USHORT m_usISPTempDataSize=CALI_DATA_SIZE; //calibration data size for one temperature
//------------------------------------------------------------------------------
//  Function    : AHC_WriteISPCalibData2SIF_CB
//  Description :
//------------------------------------------------------------------------------

extern MMP_ULONG glUvcIqTblBinSz;
extern MMP_UBYTE *gpUvcIqTblBinPtr;
extern MMP_UBYTE gubISPCaliIndex;

MMP_BYTE bISPFilePath[MAX_FULL_FILENAME_SIZE]={0};
void AHC_WriteISPCalibData2SIF_CB(MMP_USB_EVENT event)
{
#if defined(SUPPORT_UVC_ISP_EZMODE_FUNC) && (SUPPORT_UVC_ISP_EZMODE_FUNC)
    MMP_ULONG   ulFileId;
    MMP_ULONG   ulActualSize;
    INT8       StrIdx[4];

    printc("AHC_WriteISPCalibData2SIF_CB\r\n");

    MEMSET(bISPFilePath, 0, sizeof(bISPFilePath));

    STRCPY(bISPFilePath, "SF:");
    STRCAT(bISPFilePath, ISP_CALI_PARTITION);
    STRCAT(bISPFilePath,":\\");
    STRCAT(bISPFilePath, ISP_CALI_FILENAME_PREFIX);
    AHC_Utility_Int2Str(gubISPCaliIndex, StrIdx);
    STRCAT(bISPFilePath, StrIdx);
    STRCAT(bISPFilePath, ISP_CALI_FILENAME_EXT);

    printc("Write File name:%s  into SIF\r\n", bISPFilePath);

    if(MMP_ERR_NONE != MMPS_FS_FileOpen(bISPFilePath, strlen(bISPFilePath), "w+b", strlen("w+b"), &ulFileId)) {
        printc("AHC_WriteISPCalibData2SIF_CB  MMPS_FS_FileOpen err\r\n");
        MMPS_FS_FileClose(ulFileId);
        return;
    }

    printc("WR index %d size 0x%x  from DRAM addr 0x%x to SIF \r\n", gubISPCaliIndex, glUvcIqTblBinSz, gpUvcIqTblBinPtr);
    MMPS_FS_FileWrite(ulFileId, gpUvcIqTblBinPtr, glUvcIqTblBinSz, &ulActualSize);
    MMPS_FS_FileClose(ulFileId);
    #endif
}

//------------------------------------------------------------------------------
//  Function    : AHC_GetISPTmpDataSize
//  Description :
//------------------------------------------------------------------------------
MMP_USHORT AHC_GetISPTmpDataSize(void)
{
    return m_usISPTempDataSize;
}

//------------------------------------------------------------------------------
//  Function    : AHC_ReadISPTmpData
//  Description :
//------------------------------------------------------------------------------
AHC_BOOL AHC_ReadISPTmpData(void)
{
    MMP_ERR     err = MMP_ERR_NONE;
    MMP_ULONG   ulFileId;
    MMP_USHORT  usCalibISPDataSize;
    MMP_ULONG64 datasize;
    MMP_ULONG   read_out_bytes;
    MMP_UBYTE   isp_cali_header[10] ="ISP_CALI";
    MMP_ULONG   HeaderSize, ISPdataSize, ColorTemp, lux, sensorid, Offset=0;
    MMP_USHORT  index;
    INT8        StrIdx[4];
    INT8        i=0;

    for(i=0 ; i < ISP_CALI_FILE_NUM ;i++) {

        MEMSET(bISPFilePath, 0, sizeof(bISPFilePath));
        STRCPY(bISPFilePath, "SF:");
        STRCAT(bISPFilePath, ISP_CALI_PARTITION);
        STRCAT(bISPFilePath,":\\");
        STRCAT(bISPFilePath, ISP_CALI_FILENAME_PREFIX);
        AHC_Utility_Int2Str(i, StrIdx);
        STRCAT(bISPFilePath, StrIdx);
        STRCAT(bISPFilePath, ISP_CALI_FILENAME_EXT);

        usCalibISPDataSize= AHC_GetISPTmpDataSize();
        //load temp calibration data into ISP lib
        err = MMPS_FS_FileOpen(bISPFilePath, strlen(bISPFilePath), "rb", strlen("rb"), &ulFileId);
        if (err != MMP_ERR_NONE) {
            RTNA_DBG_Str(0, "ISP Calibration data open failed!!\r\n");
            MMPS_FS_FileClose(ulFileId);
            continue;
        }
        else
        {
            // file size check
            MMPS_FS_FileGetSize(ulFileId, &datasize);
            if(datasize != usCalibISPDataSize){
                MMPS_FS_FileClose(ulFileId);
                RTNA_DBG_Str(0, "ISP Calibration data size mismatch!!\r\n");
                continue;
            }
            memset(CaliDataBuf, 0, usCalibISPDataSize);
            MMPS_FS_FileRead(ulFileId, CaliDataBuf, datasize, &read_out_bytes);
            MMPS_FS_FileClose(ulFileId);
        }


        CaliData = CaliDataBuf;

        if(memcmp(CaliData, isp_cali_header, 8) != 0){
           RTNA_DBG_Str(0, "ISP Calibration Data Header error!!!\r\n");
        }
        else {
            Offset=8;
            HeaderSize      =   *(MMP_ULONG *)(CaliData + Offset);
            Offset += 4;
            ISPdataSize     =   *(MMP_ULONG *)(CaliData + Offset);
            Offset += 4;
            ColorTemp      =   *(MMP_ULONG *)(CaliData + Offset);
            Offset += 4;
            lux             =   *(MMP_ULONG *)(CaliData + Offset);
            Offset += 4;
            sensorid        =   *(MMP_ULONG *)(CaliData + Offset);
            Offset += 4;

            if(ColorTemp == 3000) {
                index=1;
                AHC_GetISPCalibData(CaliDataBuf, datasize, ColorTemp, index);
            }
            else if (ColorTemp == 5000) {
                index=0;
                AHC_GetISPCalibData(CaliDataBuf, datasize, ColorTemp, index);
                index=2;
                AHC_GetISPCalibData(CaliDataBuf, datasize, ColorTemp, index);
            }
            printc("Load ISP Calibration file %s done!!\r\n",bISPFilePath);
        }
    }

    #if 0
    //load temp calibration data into ISP lib
    if(MMP_ERR_NONE != MMPS_FS_FileOpen(ISP_CALI_1_FILE_NAME, strlen(ISP_CALI_1_FILE_NAME), "rb", strlen("rb"), &ulFileId))
        return AHC_FALSE;
    // file size check
    MMPS_FS_FileGetSize(ulFileId, &datasize);
    if(datasize != usCalibISPDataSize){
        RTNA_DBG_Str(0, "ISP Calibration data size mismatch!!\r\n");
        return AHC_FALSE;
    }
    memset(CaliDataBuf, 0, usCalibISPDataSize);
    MMPS_FS_FileRead(ulFileId, CaliDataBuf, datasize, &read_out_bytes);
    #if 1
    CaliData = CaliDataBuf;
    if(memcmp(CaliData, isp_cali_header, 8) != 0){
       RTNA_DBG_Str(0, "ISP Calibration Data Header error!!!\r\n");
       return AHC_FALSE;
    }
    Offset=8;
    HeaderSize      =   *(MMP_ULONG *)(CaliData + Offset);
    Offset += 4;
    ISPdataSize     =   *(MMP_ULONG *)(CaliData + Offset);
    Offset += 4;
    ColorTemp      =   *(MMP_ULONG *)(CaliData + Offset);
    Offset += 4;
    lux             =   *(MMP_ULONG *)(CaliData + Offset);
    Offset += 4;
    sensorid        =   *(MMP_ULONG *)(CaliData + Offset);
    Offset += 4;
    #endif

    if(ColorTemp == 3000) {
        index=1;
        AHC_GetISPCalibData(CaliDataBuf, datasize, ColorTemp, index);
    }
    else if (ColorTemp == 5000) {
        index=0;
        AHC_GetISPCalibData(CaliDataBuf, datasize, ColorTemp, index);
        index=2;
        AHC_GetISPCalibData(CaliDataBuf, datasize, ColorTemp, index);
    }

    MMPS_FS_FileClose(ulFileId);
    #endif
    return AHC_TRUE;
}

//------------------------------------------------------------------------------
//  Function    : AHC_ReadISPAWBData
//  Description :
//------------------------------------------------------------------------------
AHC_BOOL AHC_ReadISP_AWBData(void)
{
    MMP_ULONG   ulFileId;
    MMP_USHORT  usCalibISPDataSize;
    MMP_ULONG64 datasize;
    MMP_ULONG   read_out_bytes;
    MMP_UBYTE   isp_cali_header[10] ="ISP_CALI";
    MMP_ULONG   ColorTemp, Offset = 0;
    MMP_ULONG   sensorid = 0;
    INT8        StrIdx[4];
    INT8        i = 0;

    for (i = 0; i < ISP_CALI_FILE_NUM; i++) {

        MEMSET(bISPFilePath, 0, sizeof(bISPFilePath));
        STRCPY(bISPFilePath, "SF:");
        STRCAT(bISPFilePath, ISP_CALI_PARTITION);
        STRCAT(bISPFilePath,":\\");
        STRCAT(bISPFilePath, ISP_CALI_FILENAME_PREFIX);
        AHC_Utility_Int2Str(i, StrIdx);
        STRCAT(bISPFilePath, StrIdx);
        STRCAT(bISPFilePath, ISP_CALI_FILENAME_EXT);

        usCalibISPDataSize= AHC_GetISPTmpDataSize();

        // load temp calibration data into ISP lib
        if (MMP_ERR_NONE != MMPS_FS_FileOpen(bISPFilePath, strlen(bISPFilePath), "rb", strlen("rb"), &ulFileId)) {
            RTNA_DBG_Str(0, "ISP Calibration data open failed!!\r\n");
            MMPS_FS_FileClose(ulFileId);
            continue;
        }
        else
        {
            // file size check
            MMPS_FS_FileGetSize(ulFileId, &datasize);
            if (datasize != usCalibISPDataSize){
                MMPS_FS_FileClose(ulFileId);
                RTNA_DBG_Str(0, "ISP Calibration data size mismatch!!\r\n");
                continue;
            }

            memset(CaliDataBuf, 0, usCalibISPDataSize);
            MMPS_FS_FileRead(ulFileId, CaliDataBuf, datasize, &read_out_bytes);
            MMPS_FS_FileClose(ulFileId);
        }

        CaliData = CaliDataBuf;

        if (memcmp(CaliData, isp_cali_header, 8) != 0){
           RTNA_DBG_Str(0, "ISP Calibration Data Header error!!!\r\n");
        }
        else {
            Offset = 16;
            ColorTemp      =   *(MMP_ULONG *)(CaliData + Offset);
            Offset = 24;
            sensorid  =   *(MMP_ULONG *)(CaliData + Offset);

            if (ColorTemp == 5000)
            {
                AHC_GetISP_AWB_CalibData(CaliDataBuf, (MMP_UBYTE)sensorid);
                printc("Load ISP Calibration AWB file %s done!!\r\n",bISPFilePath);
            }
        }
    }

    return AHC_TRUE;
}

//------------------------------------------------------------------------------
//  Function    : AHC_GetISPCalibData
//  Description :
//------------------------------------------------------------------------------
AHC_BOOL AHC_GetISPCalibData(UINT8 *buf, UINT16 bufsize, UINT16 color_temp, UINT16 index)
{
        MMP_UBYTE isp_cali_header[10] ="ISP_CALI";
        MMP_USHORT scale;
        MMP_USHORT gain_r, gain_gr, gain_gb, gain_b;
        MMP_USHORT base_x, base_y, offset_x, offset_y, center_x, center_y, rate_x, rate_y;
        MMP_USHORT *table_r, *table_g, *table_b, *pos_x, *pos_y;
        MMP_USHORT Offset = 0;

        CaliData = buf;

        //AWB ============================================
        if(memcmp(CaliData, isp_cali_header, 8) != 0){
            RTNA_DBG_Str(3, "Not Support ISP Calibration Function!!!\r\n");
            return AHC_FALSE;
        }
        Offset = 28;
        gain_r  = *(MMP_USHORT *)(CaliData + Offset);
        Offset += 2;
        gain_gr = *(MMP_USHORT *)(CaliData + Offset);
        Offset += 2;
        gain_gb = *(MMP_USHORT *)(CaliData + Offset);
        Offset += 2;
        gain_b  = *(MMP_USHORT *)(CaliData + Offset);
        Offset += 2;

        temp_cali[0] = gain_r;
        temp_cali[1] = gain_gr;
        temp_cali[2] = gain_b;
        ISP_IF_CALI_SetAWB( index,
                            gain_r, gain_gr, gain_gr, gain_b,
                            color_temp, LUX);
        //LS =============================================
        base_x  = *(MMP_USHORT *)(CaliData + Offset);
        Offset += 2;
        base_y  = *(MMP_USHORT *)(CaliData + Offset);
        Offset += 2;
        offset_x= *(MMP_USHORT *)(CaliData + Offset);
        Offset += 2;
        offset_y= *(MMP_USHORT *)(CaliData + Offset);
        Offset += 2;
        center_x= *(MMP_USHORT *)(CaliData + Offset);
        Offset += 2;
        center_y= *(MMP_USHORT *)(CaliData + Offset);
        Offset += 2;
        rate_x  = *(MMP_USHORT *)(CaliData + Offset);
        Offset += 2;
        rate_y  = *(MMP_USHORT *)(CaliData + Offset);
        Offset += 2;
        table_r = (MMP_USHORT *)(CaliData + Offset);
        Offset += 256 * 2;
        table_g = (MMP_USHORT *)(CaliData + Offset);
        Offset += 256 * 2;
        table_b = (MMP_USHORT *)(CaliData + Offset);
        Offset += 256 * 2;

        ISP_IF_CALI_SetLS(  index,
                          base_x, base_y,
                          center_x, center_y,
                          offset_x, offset_y,
                         rate_x, rate_y,
                          (MMP_USHORT *)table_r, (MMP_USHORT *)table_g, (MMP_USHORT *)table_b,
                          color_temp, LUX);
        //CS =============================================
        base_x  = *(MMP_USHORT *)(CaliData + Offset);
        Offset += 2;
        base_y  = *(MMP_USHORT *)(CaliData + Offset);
        Offset += 2;
        offset_x= *(MMP_USHORT *)(CaliData + Offset);
        Offset += 2;
        offset_y= *(MMP_USHORT *)(CaliData + Offset);
        Offset += 2;
        center_x= *(MMP_USHORT *)(CaliData + Offset);
        Offset += 2;
        center_y= *(MMP_USHORT *)(CaliData + Offset);
        Offset += 2;
        scale   = *(MMP_USHORT *)(CaliData + Offset);
        Offset += 2;
        pos_x   = (MMP_USHORT *)(CaliData + Offset);
        Offset += 41 * 2;
        pos_y   = (MMP_USHORT *)(CaliData + Offset);
        Offset += 31 * 2;
        table_r = (MMP_USHORT *)(CaliData + Offset);
        Offset += 42 * 32 * 2;
        table_g = (MMP_USHORT *)(CaliData + Offset);
        Offset += 42 * 32 * 2;
        table_b = (MMP_USHORT *)(CaliData + Offset);
        Offset += 42 * 32 * 2;

        temp_cali[3] = pos_x[38];
        temp_cali[4] = base_y;
        temp_cali[5] = scale;
        temp_cali[6] = offset_y;

        ISP_IF_CALI_SetCS(  index,
                            base_x, base_y,
                            center_x, center_y,
                            offset_x, offset_y,
                            scale,
                            (MMP_USHORT *)pos_x, (MMP_USHORT *)pos_y,
                            (MMP_USHORT *)table_r, (MMP_USHORT *)table_g, (MMP_USHORT *)table_b,
                            color_temp, LUX);
     return AHC_TRUE;
}

//------------------------------------------------------------------------------
//  Function    : AHC_GetISP_AWB_CalibData
//  Description :
//------------------------------------------------------------------------------
AHC_BOOL AHC_GetISP_AWB_CalibData(UINT8 *buf, UINT8 sensorid)
{
    MMP_UBYTE isp_cali_header[10] ="ISP_CALI";
    MMP_USHORT gain_r, gain_gr, gain_gb, gain_b;
    MMP_USHORT Offset = 0;

    CaliData = buf;
    //AWB ============================================
    if (memcmp(CaliData, isp_cali_header, 8) != 0){
        RTNA_DBG_Str(3, "Not Support ISP Calibration Function!!!\r\n");
        return AHC_FALSE;
    }

    Offset = 28;
    gain_r  = *(MMP_USHORT *)(CaliData + Offset);
    Offset += 2;
    gain_gr = *(MMP_USHORT *)(CaliData + Offset);
    Offset += 2;
    gain_gb = *(MMP_USHORT *)(CaliData + Offset);
    Offset += 2;
    gain_b  = *(MMP_USHORT *)(CaliData + Offset);

    temp_cali[0] = gain_r << 2;
    temp_cali[1] = gain_gr << 2;
    temp_cali[2] = gain_b << 2;
    printc("sensorid %d R %x G %x B %x\r\n", sensorid, temp_cali[0], temp_cali[1], temp_cali[2]);

//    printc("Snr %d R 0x%x  0x%x\r\n", sensorid, temp_cali[0] >> 8, temp_cali[0] & 0xFF);
    gsSensorFunction->MMPF_Sensor_SetReg((MMP_UBYTE)sensorid, 0x500C, temp_cali[0] >> 8);
    gsSensorFunction->MMPF_Sensor_SetReg((MMP_UBYTE)sensorid, 0x500D, temp_cali[0] & 0xFF);
//    printc("Snr %d G 0x%x  0x%x\r\n", sensorid, temp_cali[1] >> 8, temp_cali[1] & 0xFF);
    gsSensorFunction->MMPF_Sensor_SetReg((MMP_UBYTE)sensorid, 0x500E, temp_cali[1] >> 8);
    gsSensorFunction->MMPF_Sensor_SetReg((MMP_UBYTE)sensorid, 0x500F, temp_cali[1] & 0xFF);
//    printc("Snr %d B 0x%x  0x%x\r\n", sensorid, temp_cali[2] >> 8, temp_cali[2] & 0xFF);
    gsSensorFunction->MMPF_Sensor_SetReg((MMP_UBYTE)sensorid, 0x5010, temp_cali[2] >> 8);
    gsSensorFunction->MMPF_Sensor_SetReg((MMP_UBYTE)sensorid, 0x5011, temp_cali[2] & 0xFF);

    return AHC_TRUE;
}
#endif

static int AHC_Remap(int v, int fromLow, int fromHigh, int toLow, int toHigh)
{
    return toLow + (v - fromLow) * (toHigh - toLow) / (fromHigh - fromLow);
}

//------------------------------------------------------------------------------
//  Function    : AHC_SetAwbFastMode
//  Description :
//------------------------------------------------------------------------------
AHC_BOOL AHC_SetAwbFastMode(UINT8 ubSnrSel, UINT8 byEnable)
{
    MMPS_Sensor_Set3AFunction(ubSnrSel, MMP_ISP_3A_FUNC_SET_AWB_FAST_MODE, byEnable);
    return AHC_TRUE;
}

//------------------------------------------------------------------------------
//  Function    : AHC_SetAeFastMode
//  Description :
//------------------------------------------------------------------------------
AHC_BOOL AHC_SetAeFastMode(UINT8 ubSnrSel, UINT8 byEnable)
{
    MMPS_Sensor_Set3AFunction(ubSnrSel, MMP_ISP_3A_FUNC_SET_AE_FAST_MODE, byEnable);
    return AHC_TRUE;
}

//------------------------------------------------------------------------------
//  Function    : AHC_SetAeIsoMode
//  Description :
//------------------------------------------------------------------------------
AHC_BOOL AHC_SetAeIsoMode(UINT8 ubSnrSel, AHC_AE_ISO byMode)
{
    UINT32 ulIso = MMP_AE_ISO_AUTO;

    switch(byMode) {
        case AHC_AE_ISO_AUTO:   ulIso = MMP_AE_ISO_AUTO;    break;
        case AHC_AE_ISO_100:    ulIso = MMP_AE_ISO_100;     break;
        case AHC_AE_ISO_200:    ulIso = MMP_AE_ISO_200;     break;
        case AHC_AE_ISO_400:    ulIso = MMP_AE_ISO_400;     break;
        case AHC_AE_ISO_800:    ulIso = MMP_AE_ISO_800;     break;
        case AHC_AE_ISO_1600:   ulIso = MMP_AE_ISO_1600;    break;
        case AHC_AE_ISO_3200:   ulIso = MMP_AE_ISO_3200;    break;
        default:                return AHC_FALSE;
    }

    if (MMPS_Sensor_Set3AFunction(ubSnrSel, MMP_ISP_3A_FUNC_SET_ISO, ulIso) != MMP_ERR_NONE) {
        return AHC_FALSE;
    }

    return AHC_TRUE;
}

//------------------------------------------------------------------------------
//  Function    : AHC_SetAeFlickerMode
//  Description :
//------------------------------------------------------------------------------
AHC_BOOL AHC_SetAeFlickerMode(UINT8 ubSnrSel, AHC_AE_FLICKER byMode)
{
    MMPS_Sensor_Set3AFunction(ubSnrSel, MMP_ISP_3A_FUNC_SET_AE_FLICKER_MODE, byMode);
    return AHC_TRUE;
}

//------------------------------------------------------------------------------
//  Function    : AHC_SetAeMeteringMode
//  Description :
//------------------------------------------------------------------------------
AHC_BOOL AHC_SetAeMeteringMode(UINT8 ubSnrSel, AHC_AE_METERING byMode)
{
    MMPS_Sensor_Set3AFunction(ubSnrSel, MMP_ISP_3A_FUNC_SET_AE_METER_MODE, byMode);
    return AHC_TRUE;
}

//------------------------------------------------------------------------------
//  Function    : AHC_SetAeEvBiasMode
//  Description :
//------------------------------------------------------------------------------
AHC_BOOL AHC_SetAeEvBiasMode(UINT8 ubSnrSel, AHC_AE_EV_BIAS byMode)
{
    int lEv = 0;

    switch (byMode)
    {
        case AHC_AE_EV_BIAS_M200:
            //lEv = -200;
            lEv = MMP_AE_EV_M200;
            break;
        case AHC_AE_EV_BIAS_M166:
            //lEv = -166;
            lEv = MMP_AE_EV_M166;
            break;
        case AHC_AE_EV_BIAS_M133:
            //lEv = -133;
            lEv = MMP_AE_EV_M133;
            break;
        case AHC_AE_EV_BIAS_M100:
            //lEv = -100;
            lEv = MMP_AE_EV_M100;
            break;
        case AHC_AE_EV_BIAS_M066:
            //lEv = -66;
            lEv = MMP_AE_EV_M066;
            break;
        case AHC_AE_EV_BIAS_M033:
            //lEv = -33;
            lEv = MMP_AE_EV_M033;
            break;
        case AHC_AE_EV_BIAS_0000:
            //lEv = 0;
            lEv = MMP_AE_EV_0000;
            break;
        case AHC_AE_EV_BIAS_P033:
            //lEv = 33;
            lEv = MMP_AE_EV_P033;
            break;
        case AHC_AE_EV_BIAS_P066:
            //lEv = 66;
            lEv = MMP_AE_EV_P066;
            break;
        case AHC_AE_EV_BIAS_P100:
            //lEv = 100;
            lEv = MMP_AE_EV_P100;
            break;
        case AHC_AE_EV_BIAS_P133:
            //lEv = 133;
            lEv = MMP_AE_EV_P133;
            break;
        case AHC_AE_EV_BIAS_P166:
            //lEv = 166;
            lEv = MMP_AE_EV_P166;
            break;
        case AHC_AE_EV_BIAS_P200:
            //lEv = 200;
            lEv = MMP_AE_EV_P200;
            break;
        default:
            return AHC_FALSE;
    }

    if (MMPS_Sensor_Set3AFunction(ubSnrSel, MMP_ISP_3A_FUNC_SET_EV, lEv) != MMP_ERR_NONE) {
        return AHC_FALSE;
    }

    return AHC_TRUE;
}

//------------------------------------------------------------------------------
//  Function    : AHC_SetAeSceneMode
//  Description :
//------------------------------------------------------------------------------
AHC_BOOL AHC_SetAeSceneMode(AHC_SCENE byMode)
{
#if 0
    ISP_IF_F_SetScene(byMode);
#endif
    return AHC_TRUE;
}

//------------------------------------------------------------------------------
//  Function    : AHC_SetAwbMode
//  Description :
//------------------------------------------------------------------------------
AHC_BOOL AHC_SetAwbMode(UINT8 ubSnrSel, AHC_AWB_MODE byMode)
{
    INT32 mode;

    mode = (byMode == AHC_AWB_MODE_BYPASS) ? MMP_AWB_MODE_BYPASS :
           (byMode == AHC_AWB_MODE_AUTO) ? MMP_AWB_MODE_AUTO :
           (byMode == AHC_AWB_MODE_DAYLIGHT) ? MMP_AWB_MODE_DAYLIGHT :
           (byMode == AHC_AWB_MODE_CLOUDY) ? MMP_AWB_MODE_CLOUDY :
           (byMode == AHC_AWB_MODE_FLUORESCENT_WHITE) ? MMP_AWB_MODE_FLUORESCENT_WHITE :
           (byMode == AHC_AWB_MODE_FLUORESCENT_DAYLIGHT) ? MMP_AWB_MODE_FLUORESCENT_DAYLIGHT :
           (byMode == AHC_AWB_MODE_INCANDESCENT) ? MMP_AWB_MODE_INCANDESCENT :
           0xFFFFFFFF;

    if (mode == 0xFFFFFFFF) {
        return AHC_FALSE;
    }

    if (MMPS_Sensor_Set3AFunction(ubSnrSel, MMP_ISP_3A_FUNC_SET_AWB_MODE, mode) != MMP_ERR_NONE) {
        return AHC_FALSE;
    }

    return AHC_TRUE;
}

//------------------------------------------------------------------------------
//  Function    : AHC_SetFastAeAwbMode
//  Description :
//------------------------------------------------------------------------------
void AHC_SetFastAeAwbMode(AHC_BOOL bEnable)
{
    if (bEnable == AHC_TRUE)
    {
        AHC_SetAeFastMode(0, 1);
        AHC_SetAwbFastMode(0, 1);
        if(CAM_CHECK_SCD(SCD_CAM_BAYER_SENSOR)) {
            AHC_SetAeFastMode(1, 1);
            AHC_SetAwbFastMode(1, 1);
        }

        m_bEnableFastAeAwb = AHC_TRUE;
    }
    else
    {
        m_bEnableFastAeAwb = AHC_FALSE;

        AHC_SetAeFastMode(0, 0);
        AHC_SetAwbFastMode(0, 0);
        if(CAM_CHECK_SCD(SCD_CAM_BAYER_SENSOR)) {
            AHC_SetAeFastMode(1, 0);
            AHC_SetAwbFastMode(1, 0);
        }
    }
}

//------------------------------------------------------------------------------
//  Function    : AHC_SetImageEffect
//  Description :
//------------------------------------------------------------------------------
AHC_BOOL AHC_SetImageEffect(UINT8 ubSnrSel, AHC_IMAGE_EFFECT byMode)
{
    #define INVALID_IMAGE_EFFECT_MODE   0xFFFFFFFF
    UINT32 uiImageEffect = 0;

    uiImageEffect = (byMode == AHC_IMAGE_EFFECT_NORMAL) ? MMP_IMG_EFFECT_NORMAL :
                    (byMode == AHC_IMAGE_EFFECT_GREY) ? MMP_IMG_EFFECT_GREY :
                    (byMode == AHC_IMAGE_EFFECT_SEPIA) ? MMP_IMG_EFFECT_SEPIA :
                    (byMode == AHC_IMAGE_EFFECT_NEGATIVE) ? MMP_IMG_EFFECT_NEGATIVE :
                    (byMode == AHC_IMAGE_EFFECT_ANTIQUE) ? MMP_IMG_EFFECT_ANTIQUE :
                    (byMode == AHC_IMAGE_EFFECT_WATERCOLOR) ? MMP_IMG_EFFECT_WATERCOLOR :
                    (byMode == AHC_IMAGE_EFFECT_PORTRAIT) ? MMP_IMG_EFFECT_PORTRAIT :
                    (byMode == AHC_IMAGE_EFFECT_LANDSCAPE) ? MMP_IMG_EFFECT_LANDSCAPE :
                    (byMode == AHC_IMAGE_EFFECT_SUNSET) ? MMP_IMG_EFFECT_SUNSET :
                    (byMode == AHC_IMAGE_EFFECT_DUSK) ? MMP_IMG_EFFECT_DUSK :
                    (byMode == AHC_IMAGE_EFFECT_DAWN) ? MMP_IMG_EFFECT_DAWN :
                    (byMode == AHC_IMAGE_EFFECT_RED) ? MMP_IMG_EFFECT_RED :
                    (byMode == AHC_IMAGE_EFFECT_GREEN) ? MMP_IMG_EFFECT_GREEN :
                    (byMode == AHC_IMAGE_EFFECT_BLUE) ? MMP_IMG_EFFECT_BLUE :
                    (byMode == AHC_IMAGE_EFFECT_YELLOW) ? MMP_IMG_EFFECT_YELLOW :
                    (byMode == AHC_IMAGE_EFFECT_EMBOSS) ? MMP_IMG_EFFECT_EMBOSS :
                    (byMode == AHC_IMAGE_EFFECT_OIL) ? MMP_IMG_EFFECT_OIL :
                    (byMode == AHC_IMAGE_EFFECT_BW) ? MMP_IMG_EFFECT_BW :
                    (byMode == AHC_IMAGE_EFFECT_SKETCH) ? MMP_IMG_EFFECT_SKETCH :
                    (byMode == AHC_IMAGE_EFFECT_CRAYONE) ? MMP_IMG_EFFECT_CRAYONE :
                    (byMode == AHC_IMAGE_EFFECT_WHITEBOARD) ? MMP_IMG_EFFECT_WHITEBOARD :
                    (byMode == AHC_IMAGE_EFFECT_BLACKBOARD) ? MMP_IMG_EFFECT_BLACKBOARD :
                    (byMode == AHC_IMAGE_EFFECT_VIVID) ? MMP_IMG_EFFECT_VIVID :
                    (byMode == AHC_IMAGE_EFFECT_PALE) ? MMP_IMG_EFFECT_PALE :
                    INVALID_IMAGE_EFFECT_MODE;

    if (uiImageEffect == INVALID_IMAGE_EFFECT_MODE) {
        return AHC_FALSE;
    }

    if (MMPS_Sensor_SetIQFunction(ubSnrSel, MMP_ISP_IQ_FUNC_SET_EFFECT, byMode) != MMP_ERR_NONE) {
        return AHC_FALSE;
    }

    return AHC_TRUE;
}

//------------------------------------------------------------------------------
//  Function    : AHC_SetColorSaturateLevel
//  Description : -128~128
//------------------------------------------------------------------------------
AHC_BOOL AHC_SetColorSaturateLevel(UINT8 ubSnrSel, INT16 iLvl)
{
    INT32 iSaturateVal;

    if (iLvl < AHC_SATURATION_MIN ||
        iLvl > AHC_SATURATION_MAX) {
        return AHC_FALSE;
    }

    //MV2: -128~128

    #if 1 //RTK
    //M5: 0~100
    iSaturateVal = AHC_Remap(iLvl, AHC_SATURATION_MIN, AHC_SATURATION_MAX, 0, 100);
    #endif

    if (MMPS_Sensor_SetIQFunction(ubSnrSel, MMP_ISP_IQ_FUNC_SET_SATURATION, iSaturateVal) != MMP_ERR_NONE) {
        return AHC_FALSE;
    }

    return AHC_TRUE;
}

//------------------------------------------------------------------------------
//  Function    : AHC_SetColorSaturateLevel
//  Description : -128~128
//------------------------------------------------------------------------------
AHC_BOOL AHC_GetColorSaturateRange(INT16* min, INT16* max)
{
    *min = AHC_SATURATION_MIN;
    *max = AHC_SATURATION_MAX;

    return AHC_TRUE;
}

//------------------------------------------------------------------------------
//  Function    : AHC_SetColorSharpnessLevel
//  Description : -128~128
//------------------------------------------------------------------------------
AHC_BOOL AHC_SetColorSharpnessLevel(UINT8 ubSnrSel, INT16 iLvl)
{
    INT32 iSharpVal = 0;

    if (iLvl < AHC_SHARPNESS_MIN ||
        iLvl > AHC_SHARPNESS_MAX) {
        return AHC_FALSE;
    }

    //MV2: -128~128

    #if 1 //RTK
    //M5: 0~100
    iSharpVal = AHC_Remap(iLvl, AHC_SHARPNESS_MIN, AHC_SHARPNESS_MAX, 0, 100);
    #endif

    if (MMPS_Sensor_SetIQFunction(ubSnrSel, MMP_ISP_IQ_FUNC_SET_SHARPNESS, iSharpVal) != MMP_ERR_NONE) {
        return AHC_FALSE;
    }

    return AHC_TRUE;
}

//------------------------------------------------------------------------------
//  Function    : AHC_GetColorSharpnessRange
//  Description : -128~128
//------------------------------------------------------------------------------
void AHC_GetColorSharpnessRange(INT16* min, INT16* max)
{
    *min = AHC_SHARPNESS_MIN;
    *max = AHC_SHARPNESS_MAX;
}

//------------------------------------------------------------------------------
//  Function    : AHC_SetColorGammaLevel
//  Description : -128~128
//------------------------------------------------------------------------------
AHC_BOOL AHC_SetColorGammaLevel(UINT8 ubSnrSel, INT16 iLvl)
{
    INT32 iGammaVal;

    if (iLvl < AHC_GAMMA_MIN ||
        iLvl > AHC_GAMMA_MAX) {
        return AHC_FALSE;
    }

    #if 1 //RTK
    //M5: 0~100
    iGammaVal = AHC_Remap(iLvl, AHC_GAMMA_MIN, AHC_GAMMA_MAX, 0, 100);
    #endif

    if (MMPS_Sensor_SetIQFunction(ubSnrSel, MMP_ISP_IQ_FUNC_SET_GAMMA, iGammaVal) != MMP_ERR_NONE) {
        return AHC_FALSE;
    }

    return AHC_TRUE;
}

//------------------------------------------------------------------------------
//  Function    : AHC_GetColorGammaRange
//  Description : -128~128
//------------------------------------------------------------------------------
AHC_BOOL AHC_GetColorGammaRange(INT16* min, INT16* max)
{
    *min = AHC_GAMMA_MIN;
    *max = AHC_GAMMA_MAX;

    return AHC_TRUE;
}

//------------------------------------------------------------------------------
//  Function    : AHC_SetColorContrastLevel
//  Description : -128~128
//------------------------------------------------------------------------------
AHC_BOOL AHC_SetColorContrastLevel(UINT8 ubSnrSel,INT16 iLvl)
{
    INT32 iContrastVal = 0;

    if (iLvl < AHC_CONTRAST_MIN ||
        iLvl > AHC_CONTRAST_MAX) {
        return AHC_FALSE;
    }

    #if 1 //RTK
    //M5: 0~100
    iContrastVal = AHC_Remap(iLvl, AHC_CONTRAST_MIN, AHC_CONTRAST_MAX, 0, 100);
    #endif

    if (MMPS_Sensor_SetIQFunction(ubSnrSel, MMP_ISP_IQ_FUNC_SET_CONTRAST, iContrastVal) != MMP_ERR_NONE) {
        return AHC_FALSE;
    }

    return AHC_TRUE;
}

//------------------------------------------------------------------------------
//  Function    : AHC_GetColorContrastRange
//  Description : -128~128
//------------------------------------------------------------------------------
AHC_BOOL AHC_GetColorContrastRange(INT16* min, INT16* max)
{
    *min = AHC_CONTRAST_MIN;
    *max = AHC_CONTRAST_MAX;

    return AHC_TRUE;
}

//------------------------------------------------------------------------------
//  Function    : AHC_SetAeWDRMode
//  Description :
//------------------------------------------------------------------------------
AHC_BOOL AHC_SetAeWDRMode(UINT8 ubSnrSel,AHC_AE_WDR byMode)
{
    MMPS_Sensor_SetIQFunction(ubSnrSel, MMP_ISP_IQ_FUNC_SET_WDR, byMode);
    return AHC_TRUE;
}

//------------------------------------------------------------------------------
//  Function    : MMP_SensorDrv_PostInitISP
//  Description : This function will be called in MMPS_Sensor_Initialize()
//                which will reset ISP settings earlier.
//                It's used to reset ISP settings after sensor init.
//------------------------------------------------------------------------------
void MMP_SensorDrv_PostInitISP(void)
{
    // Re-set ISP settings in AHC_PostInitISP()
    if (AHC_PostInitISP != NULL)
    {
        AHC_PostInitISP();
    }
}

//------------------------------------------------------------------------------
//  Function    : MMP_SensorDrv_FirstInitISPCB
//  Description :
//------------------------------------------------------------------------------
void MMP_SensorDrv_FirstInitISPCB(void)
{
    #if  (defined(SUPPORT_ISP_CALIBRATION) && (SUPPORT_ISP_CALIBRATION == 1))
    if (AHC_FirstInitISPCB != NULL)
    {
        AHC_FirstInitISPCB();
    }
    #endif
}
