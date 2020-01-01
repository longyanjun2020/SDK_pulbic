
/*===========================================================================
 * Include file
 *===========================================================================*/

#include "Config_SDK.h"
#include "config_fw.h"
#include "lib_retina.h"
#include "ahc_fs.h"
#include "GSensor_ctrl.h"
#include "ahc_gsensor.h"
#include "mmpf_gsensor.h"
#include "ahc_general.h"

// Add below define since too many header files have the define.
#ifdef GSENSOR_DATA_LEN
    #undef GSENSOR_DATA_LEN
    #define GSENSOR_DATA_LEN sizeof(GSNR_INFOCHUCK)
#endif

#if (GSENSOR_CONNECT_ENABLE)

#if 0  // For debug
#define DBG_GSENSOR_PRINT       UartSendTrace
#else
#define DBG_GSENSOR_PRINT(...)
#endif

/*===========================================================================
 * Global varible
 *===========================================================================*/

UINT32                  m_ulInfoFileId          = 0;
UINT32                  m_ulInfoFileByte        = 0;
UINT32                  m_ulInfoLastByte        = 0;
float                   GValueInNmea[3] = {0, 0, 0};
static MMP_UBYTE        m_ubStartVRWithGsnrInfo = MMP_FALSE;
static MMP_ULONG        m_ulGsnrCount_0         = 0;
static MMP_ULONG        m_ulGsnrCount_1         = 0;
static MMP_ULONG        m_ulGsnrCount_Last      = 0;
static MMP_ULONG        m_ulGsnrInfoChuckCnt_0  = 0;
static MMP_ULONG        m_ulGsnrInfoChuckCnt_1  = 0;
static MMP_UBYTE        m_ubGsnrBufIndex        = 0;
static MMP_UBYTE        m_ubGsnrBufIndex_Store  = 0;
static MMP_UBYTE        m_ubGsnrBufIndex_Last   = 0;
static MMP_UBYTE        m_ubGsnrBufIndex_Backup = 0;
static MMP_BOOL         m_bGsnrPingPongBufStart = MMP_FALSE;
static MMP_BOOL         m_bGsensor_TriggerRestorePreRecordInfo = MMP_FALSE;
static MMP_BOOL         m_bGsensor_FlushBackupBuffer[2] = {MMP_FALSE, MMP_FALSE};
static MMP_BOOL         m_bGsensor_UseLastData = MMP_FALSE;
static MMP_ULONG        m_ulGsnrPreRecordTime   = 0;
static MMP_UBYTE        m_ubGsnrBufCounter      = 0;
static GSNR_CHUCKHDR    GsnrChuckHdr[1];
static GSNR_CHUCKHDR    GsnrInfoChuckHdr[1];
static GSNR_INFOCHUCK   GsnrInfoChuckBuf_0[GSNR_MAX_INFONUM] = {0};
static GSNR_INFOCHUCK   GsnrInfoChuckBuf_1[GSNR_MAX_INFONUM] = {0};

MMPF_OS_FLAGID          GsensorCtrlFlag = MMPF_OS_CREATE_FLAG_INT_ERR;

#if (VR_VIDEO_TYPE == COMMON_VR_VIDEO_TYPE_3GP)
    static UINT32 Gsensor_Convert_Endian(UINT32 d);

    #define GSENSOR_BIGENDIAN(d)    Gsensor_Convert_Endian(d + 8) // 8 is FOURCC + sizeof(unsigned int) for 3GP container
#else
    #define GSENSOR_BIGENDIAN(d)    (d)
#endif

#if (AHC_SHAREENC_SUPPORT)
MMP_BOOL        m_bStartGsnr_SHARE      = MMP_FALSE;
MMP_ULONG       ulGsnrTCount_Pre_SHARE  = 0xFFFF;    // PreRec count bound
MMP_ULONG       ulGsnrCount_Pre_SHARE   = 0xFFFF;     // PreRec count
MMP_ULONG       ulGsnrCount_SHARE       = 0xFFFF;         // Normal count
GSNR_INFOCHUCK  GsnrInfoChuckBuf_Pre_SHARE[6*(DUAL_RECORD_WRITE_PRETIME+DUAL_RECORD_WRITE_PRETIME_LIMIT)] = {0};//gGsensor_Attribute.ubStoreFreq;
GSNR_INFOCHUCK  GsnrInfoChuckBuf_SHARE[6*(DUAL_RECORD_WRITE_PRETIME+DUAL_RECORD_WRITE_INTERVAL)] = {0};
#endif

/*===========================================================================
 * Main body
 *===========================================================================*/

#if 0
void _____AVI_Chunk_Function_________(){ruturn;} //dummy
#endif

static UINT32 Gsensor_Convert_Endian(UINT32 d)
{
    UINT32 t = d;   // 8 is FOURCC + sizeof(unsigned int) for 3GP container
    *((char*)&d + 3) = *((char*)&t + 0);
    *((char*)&d + 2) = *((char*)&t + 1);
    *((char*)&d + 1) = *((char*)&t + 2);
    *((char*)&d + 0) = *((char*)&t + 3);
    return d;
}

#if (AHC_SHAREENC_SUPPORT)
AHC_BOOL AHC_Gsensor_StartSHAREPreRec(MMP_ULONG PreRecTime)
{
    MEMSET(GsnrInfoChuckBuf_Pre_SHARE, 0, sizeof(GsnrInfoChuckBuf_Pre_SHARE));
    if (PreRecTime > 0)
    {
        ulGsnrTCount_Pre_SHARE = PreRecTime / 1000;
        ulGsnrCount_Pre_SHARE = 0;
    }

    return AHC_TRUE;
}

AHC_BOOL AHC_Gsensor_SetSHAREIndex(void)
{
    MMP_ULONG idx_nor, idx_pre;

    //m_bStartGsnr_SHARE = (m_bStartGsnr_SHARE)?(MMP_FALSE):(MMP_TRUE);

    if (m_bStartGsnr_SHARE) // normal -> prerec
    {
        MEMSET(GsnrInfoChuckBuf_Pre_SHARE, 0, sizeof(GsnrInfoChuckBuf_Pre_SHARE));
        ulGsnrCount_Pre_SHARE = 0;
        //MEMSET(GsnrInfoChuckBuf_SHARE, 0, sizeof(GsnrInfoChuckBuf_SHARE));
        ulGsnrCount_SHARE = 0;
        m_bStartGsnr_SHARE = MMP_FALSE;
    }
    else if (m_bStartGsnr_SHARE == MMP_FALSE) // prerec -> normal
    {
        MEMSET(GsnrInfoChuckBuf_SHARE, 0, sizeof(GsnrInfoChuckBuf_SHARE));
        m_bStartGsnr_SHARE = MMP_TRUE;
    }

    if (m_bStartGsnr_SHARE)
    {
        if (ulGsnrCount_Pre_SHARE > 0)
        {
            ulGsnrCount_SHARE = ulGsnrTCount_Pre_SHARE * AHC_Gsensor_GetAttributeAddr()->ubStoreFreq;
            idx_pre = ulGsnrCount_Pre_SHARE - 1;
            idx_nor = ulGsnrCount_SHARE - 1;

            do {
                GsnrInfoChuckBuf_SHARE[idx_nor] = GsnrInfoChuckBuf_Pre_SHARE[idx_pre];
                if (idx_pre > 0)
                    idx_pre--;
                else
                    idx_pre = (ulGsnrTCount_Pre_SHARE * AHC_Gsensor_GetAttributeAddr()->ubStoreFreq) - 1;

                if (idx_nor > 0)
                    idx_nor--;
                else
                    break;
            } while (idx_pre != (ulGsnrCount_Pre_SHARE - 1));
        }
        else
        {
            ulGsnrCount_SHARE = 0;
        }
    }

    return AHC_TRUE;
}

void AHC_Gsensor_BackupGsnrInfoEx(MMP_ULONG ulCounter, GSNR_SBYTE Info)
{
    #if 0
    if (ulCounter < DUAL_RECORD_WRITE_INTERVAL)
    {
        GsnrInfoChuckBuf_SHARE[ulCounter].sbX = Info[0];
        GsnrInfoChuckBuf_SHARE[ulCounter].sbY = Info[1];
        GsnrInfoChuckBuf_SHARE[ulCounter].sbZ = Info[2];
    }
    #endif
}
#endif

void AHC_Gsensor_ResetBufCtrlVariable(void)
{
    m_ulGsnrCount_0         = 0;
    m_ulGsnrCount_1         = 0;
    m_ulGsnrInfoChuckCnt_0  = 0;
    m_ulGsnrInfoChuckCnt_1  = 0;
    m_ubGsnrBufIndex        = 0;
    m_bGsnrPingPongBufStart = MMP_FALSE;
    m_ubGsnrBufCounter      = 0;
#if (GSNR_USE_FILE_AS_DATABUF)
    m_ulInfoFileByte        = 0;
    m_ulInfoLastByte        = 0;
#endif
}

void AHC_Gsensor_OpenInfoFile(INT8 *ubFileName)
{
#if (GSNR_USE_FILE_AS_DATABUF)

    if (m_ulInfoFileId == 0)
    {
        // Change "w+b" to "a+b" Means to append the same file position.
        if (AHC_FS_FileOpen(ubFileName, AHC_StrLen(ubFileName), "a+b", AHC_StrLen("a+b"), &m_ulInfoFileId))
        {
            m_ulInfoFileId = 0;
            return;
        }
    }

    AHC_FS_FileSeek(m_ulInfoFileId, 0, AHC_FS_SEEK_SET);

    AHC_Gsensor_ResetBufCtrlVariable();
    DBG_GSENSOR_PRINT("%s: m_ulInfoFileId = 0x%X\r\n", __FUNCTION__, m_ulInfoFileId);
#endif
}

void AHC_Gsensor_CloseInfoFile(void)
{
#if (GSNR_USE_FILE_AS_DATABUF)
    if (m_ulInfoFileId != 0) {
        AHC_FS_FileClose(m_ulInfoFileId);
    }
    m_ulInfoFileId = 0;
#endif
}

void AHC_Gsensor_StartRecord(void)
{
    MMP_BOOL gsnr_inited = AHC_FALSE;
    // TBD
    MMPF_3RDParty_Gsensor_initiated(&gsnr_inited);
    m_ubStartVRWithGsnrInfo = gsnr_inited;

#if (GSNR_USE_FILE_AS_DATABUF)

    //AHC_FS_FileOpen(GSNR_TEMP_INFOFILE, AHC_StrLen(GSNR_TEMP_INFOFILE), "w+b", AHC_StrLen("w+b"), &m_ulInfoFileId);

    m_bGsnrPingPongBufStart = MMP_TRUE;

#else

    if(m_ubGsnrBufCounter)
        m_bGsnrPingPongBufStart = MMP_TRUE;
    else
        m_ubGsnrBufCounter++;

#endif

#if (AHC_SHAREENC_SUPPORT)
    MEMSET(GsnrInfoChuckBuf_Pre_SHARE, 0, sizeof(GsnrInfoChuckBuf_Pre_SHARE));
    ulGsnrCount_Pre_SHARE = 0;
#endif

}

#if (AHC_SHAREENC_SUPPORT)
void AHC_Gsensor_EndRecordEx(void)
{
    //printc("%s, %d\r\n", __FUNCTION__, __LINE__);
}
#endif

void AHC_Gsensor_EndRecord(void)
{
#if (GSNR_USE_FILE_AS_DATABUF)

    if (m_ulGsnrCount_0 != 0 && m_ulGsnrCount_0 < GSNR_MAX_INFONUM)
    {
        m_ulInfoLastByte = m_ulGsnrCount_0*GSENSOR_DATA_LEN;
        m_ubGsnrBufIndex_Store = 0;
        m_ubGsnrBufIndex = 1;
    }
    else if (m_ulGsnrCount_1 != 0 && m_ulGsnrCount_1 < GSNR_MAX_INFONUM)
    {
        m_ulInfoLastByte = m_ulGsnrCount_1*GSENSOR_DATA_LEN;
        m_ubGsnrBufIndex_Store = 1;
        m_ubGsnrBufIndex = 0;
    }

#else

    if(m_ubGsnrBufIndex)
    {
        m_ubGsnrBufIndex        = 0;
        m_ulGsnrInfoChuckCnt_1  = m_ulGsnrCount_1;
    }
    else
    {
        m_ubGsnrBufIndex        = 1;
        m_ulGsnrInfoChuckCnt_0  = m_ulGsnrCount_0;
    }

    if(m_bGsnrPingPongBufStart)
    {
        if(m_ubGsnrBufIndex)
            m_ulGsnrCount_1 = 0;
        else
            m_ulGsnrCount_0 = 0;
    }
#endif
    m_ubStartVRWithGsnrInfo = MMP_FALSE;
}

//------------------------------------------------------------------------------
//  Function    : AHC_Gsensor_EndRecord_Backup
//  Description : It will record G-Sensor data index for current video,
//                and keep recording G-Sensor data. (Reset nothing.)
//------------------------------------------------------------------------------
void AHC_Gsensor_EndRecord_Backup(void)
{
    if (m_ulGsnrCount_0 != 0 && m_ulGsnrCount_0 < GSNR_MAX_INFONUM)
    {
        m_ulInfoLastByte = m_ulGsnrCount_0*sizeof(GSNR_INFOCHUCK);
    }
    else if (m_ulGsnrCount_1 != 0 && m_ulGsnrCount_1 < GSNR_MAX_INFONUM)
    {
        m_ulInfoLastByte = m_ulGsnrCount_1*sizeof(GSNR_INFOCHUCK);
    }

    m_ubGsnrBufIndex_Backup = m_ubGsnrBufIndex;
}

//-------------------------------------------------------------------------------------------
//  Function    : AHC_Gsensor_RestorePreRecordInfo
//  Description : Copy Gsensor data from start of Pre-record to beginning of G-sensor buffer
//-------------------------------------------------------------------------------------------
void AHC_Gsensor_RestorePreRecordInfo( UINT32 ulPreRecordTime, MMP_BOOL bUseLastData )
{
    UINT32 ulPreRecordNumber = ( ulPreRecordTime * AHC_Gsensor_GetAttributeAddr()->ubStoreFreq ) / 1000;

    if (ulPreRecordNumber > GSNR_MAX_INFONUM )
    {
        printc(FG_RED("ERROR: Too many Pre-record data for G-sensor buffer (%d) !!!!!!!!!!!\r\n"), ulPreRecordNumber);
        return;
    }

    printc(FG_BLUE("-- AHC_Gsensor_RestorePreRecordInfo-- sec:%d, freq:%d, buffer:%d !!!!!!!!!!!\r\n"), ulPreRecordTime,AHC_Gsensor_GetAttributeAddr()->ubStoreFreq,ulPreRecordNumber);

    m_ulInfoFileByte = 0; // Reset m_ulInfoFileByte since it's not used

    if (m_ubGsnrBufIndex == 0)
    {
        if( m_ulGsnrCount_0 < ulPreRecordNumber ) // Need to copy data from ping-pong buffer
        {
            UINT32 ulCopyNumber = ulPreRecordNumber - m_ulGsnrCount_0;
            if( bUseLastData == MMP_TRUE )
            {
                if( m_ubGsnrBufIndex_Last == 0)
                {
                    memcpy( &GsnrInfoChuckBuf_1[0], &GsnrInfoChuckBuf_0[m_ulGsnrCount_Last - ulCopyNumber], ulCopyNumber*sizeof(GSNR_INFOCHUCK) );
                }
                else
                {
                    memcpy( &GsnrInfoChuckBuf_1[0], &GsnrInfoChuckBuf_1[m_ulGsnrCount_Last - ulCopyNumber], ulCopyNumber*sizeof(GSNR_INFOCHUCK) );
                }
            }
            else
            {
                memcpy( &GsnrInfoChuckBuf_1[0], &GsnrInfoChuckBuf_1[GSNR_MAX_INFONUM - ulCopyNumber], ulCopyNumber*sizeof(GSNR_INFOCHUCK) );
            }
            memcpy( &GsnrInfoChuckBuf_1[ulCopyNumber], &GsnrInfoChuckBuf_0[0], m_ulGsnrCount_0*sizeof(GSNR_INFOCHUCK) );
        }
        else
        {
            memcpy( &GsnrInfoChuckBuf_1[0], &GsnrInfoChuckBuf_0[m_ulGsnrCount_0 - ulPreRecordNumber], ulPreRecordNumber*sizeof(GSNR_INFOCHUCK) );
        }

        m_ubGsnrBufIndex = 1;
        m_ulGsnrCount_1 = ulPreRecordNumber;
        m_ulGsnrCount_0 = 0;
    }
    else //m_ubGsnrBufIndex == 1
    {
        if( m_ulGsnrCount_1 < ulPreRecordNumber ) // Need to copy data from ping-pong buffer
        {
            UINT32 ulCopyNumber = ulPreRecordNumber - m_ulGsnrCount_1;

            if (bUseLastData == MMP_TRUE)
            {
                if( m_ubGsnrBufIndex_Last == 0)
                {
                    memcpy( &GsnrInfoChuckBuf_0[0], &GsnrInfoChuckBuf_0[m_ulGsnrCount_Last - ulCopyNumber], ulCopyNumber*sizeof(GSNR_INFOCHUCK) );
                }
                else
                {
                    memcpy( &GsnrInfoChuckBuf_0[0], &GsnrInfoChuckBuf_1[m_ulGsnrCount_Last - ulCopyNumber], ulCopyNumber*sizeof(GSNR_INFOCHUCK) );
                }
            }
            else
            {
                memcpy( &GsnrInfoChuckBuf_0[0], &GsnrInfoChuckBuf_0[GSNR_MAX_INFONUM - ulCopyNumber], ulCopyNumber*sizeof(GSNR_INFOCHUCK) );
            }
            memcpy( &GsnrInfoChuckBuf_0[ulCopyNumber], &GsnrInfoChuckBuf_1[0], m_ulGsnrCount_1*sizeof(GSNR_INFOCHUCK) );
        }
        else
        {
            memcpy( &GsnrInfoChuckBuf_0[0], &GsnrInfoChuckBuf_1[m_ulGsnrCount_1 - ulPreRecordNumber], ulPreRecordNumber*sizeof(GSNR_INFOCHUCK) );
        }

        m_ubGsnrBufIndex = 0;
        m_ulGsnrCount_0 = ulPreRecordNumber;
        m_ulGsnrCount_1 = 0;
    }
}

void AHC_Gsensor_RestoreAviChuck(void)
{

    AHC_GSENSOR_DATA    sdata;
    GSNR_SBYTE      xyz[GSENSOR_DATA_LEN] = {0};
    MMP_UBYTE       dummy;
    UINT32          ulTimelimit;

    if(m_ubStartVRWithGsnrInfo)
    {
        #if (GSENSOR_DETECT_MODE == GSNESOR_DETECT_DIFF)
        AHC_Gsensor_Read_XYZ_WithCompensation(&sdata);
        #else
        AHC_Gsensor_Read_XYZ(&sdata);
        #endif

        xyz[0] = sdata.acc_val[0];
        xyz[1] = sdata.acc_val[1];
        xyz[2] = sdata.acc_val[2];

        AHC_VIDEO_GetCurRecordingTime(&ulTimelimit);

        if( AHC_Gsensor_NeedToRestorePreRecordInfo( &ulTimelimit ) == MMP_TRUE )
        {
            m_bGsensor_TriggerRestorePreRecordInfo = MMP_FALSE;

            AHC_Gsensor_RestorePreRecordInfo( ulTimelimit, m_bGsensor_UseLastData );
            m_bGsensor_UseLastData = MMP_FALSE;
        }

        if(m_ubGsnrBufIndex)
        {
            if((m_ulGsnrCount_1 + m_ulInfoFileByte/GSENSOR_DATA_LEN) < ulTimelimit/1000 * AHC_Gsensor_GetAttributeAddr()->ubStoreFreq)
            {
                dummy = ulTimelimit/1000 * (AHC_Gsensor_GetAttributeAddr()->ubStoreFreq) - (m_ulGsnrCount_1 + m_ulInfoFileByte/GSENSOR_DATA_LEN);
                do{
                    GsnrInfoChuckBuf_1[m_ulGsnrCount_1].sbX = xyz[0];
                    GsnrInfoChuckBuf_1[m_ulGsnrCount_1].sbY = xyz[1];
                    GsnrInfoChuckBuf_1[m_ulGsnrCount_1].sbZ = xyz[2];

                    m_ulGsnrCount_1++;
                    #if (AHC_SHAREENC_SUPPORT)
                    if (m_bStartGsnr_SHARE)
                    {
                        //AHC_Gsensor_BackupGsnrInfoEx(&xyz);
                        GsnrInfoChuckBuf_SHARE[ulGsnrCount_SHARE].sbX = xyz[0];
                        GsnrInfoChuckBuf_SHARE[ulGsnrCount_SHARE].sbY = xyz[1];
                        GsnrInfoChuckBuf_SHARE[ulGsnrCount_SHARE].sbZ = xyz[2];
                        ulGsnrCount_SHARE++;
                    }
                    else
                    {
                        GsnrInfoChuckBuf_Pre_SHARE[ulGsnrCount_Pre_SHARE].sbX = xyz[0];
                        GsnrInfoChuckBuf_Pre_SHARE[ulGsnrCount_Pre_SHARE].sbY = xyz[1];
                        GsnrInfoChuckBuf_Pre_SHARE[ulGsnrCount_Pre_SHARE].sbZ = xyz[2];

                        ulGsnrCount_Pre_SHARE = (ulGsnrCount_Pre_SHARE + 1) % (ulGsnrTCount_Pre_SHARE*AHC_Gsensor_GetAttributeAddr()->ubStoreFreq);
                    }
                    #endif
                    dummy--;

                }while((dummy > 0) && (m_ulGsnrCount_1 < GSNR_MAX_INFONUM));

            }
            else
            {
                GsnrInfoChuckBuf_1[m_ulGsnrCount_1].sbX = xyz[0];
                GsnrInfoChuckBuf_1[m_ulGsnrCount_1].sbY = xyz[1];
                GsnrInfoChuckBuf_1[m_ulGsnrCount_1].sbZ = xyz[2];
                m_ulGsnrCount_1++;
                #if (AHC_SHAREENC_SUPPORT)
                if (m_bStartGsnr_SHARE)
                {
                    //AHC_Gsensor_BackupGsnrInfoEx(xyz);
                    GsnrInfoChuckBuf_SHARE[ulGsnrCount_SHARE].sbX = xyz[0];
                    GsnrInfoChuckBuf_SHARE[ulGsnrCount_SHARE].sbY = xyz[1];
                    GsnrInfoChuckBuf_SHARE[ulGsnrCount_SHARE].sbZ = xyz[2];
                    ulGsnrCount_SHARE++;
                }
                else
                {
                    GsnrInfoChuckBuf_Pre_SHARE[ulGsnrCount_Pre_SHARE].sbX = xyz[0];
                    GsnrInfoChuckBuf_Pre_SHARE[ulGsnrCount_Pre_SHARE].sbY = xyz[1];
                    GsnrInfoChuckBuf_Pre_SHARE[ulGsnrCount_Pre_SHARE].sbZ = xyz[2];

                    ulGsnrCount_Pre_SHARE = (ulGsnrCount_Pre_SHARE + 1) % (ulGsnrTCount_Pre_SHARE*AHC_Gsensor_GetAttributeAddr()->ubStoreFreq);
                }
                #endif
            }
#if (GSNR_USE_FILE_AS_DATABUF)
            if(m_ulGsnrCount_1 == GSNR_MAX_INFONUM)
            {
                UINT32 ulWriteCount;

                DBG_GSENSOR_PRINT("%s - m_ulInfoFileId=0x%X\r\n", __func__, m_ulInfoFileId);

                AHC_FS_FileWrite(m_ulInfoFileId, (UINT8*)GsnrInfoChuckBuf_1, GSNR_MAX_INFONUM*GSENSOR_DATA_LEN, &ulWriteCount);

                m_ulInfoFileByte += ulWriteCount;

                m_ulGsnrCount_1     = 0;//Reset
                m_ubGsnrBufIndex    = 0;//Toggle
                DBG_GSENSOR_PRINT("Buf1-m_ulInfoFileByte %d\r\n",m_ulInfoFileByte);
            }
#endif
        }
        else
        {
            if((m_ulGsnrCount_0 + m_ulInfoFileByte/GSENSOR_DATA_LEN) < ulTimelimit/1000 * AHC_Gsensor_GetAttributeAddr()->ubStoreFreq)
            {
                dummy = ulTimelimit/1000 * (AHC_Gsensor_GetAttributeAddr()->ubStoreFreq) - (m_ulGsnrCount_0 + m_ulInfoFileByte/GSENSOR_DATA_LEN);
                do{
                    GsnrInfoChuckBuf_0[m_ulGsnrCount_0].sbX = xyz[0];
                    GsnrInfoChuckBuf_0[m_ulGsnrCount_0].sbY = xyz[1];
                    GsnrInfoChuckBuf_0[m_ulGsnrCount_0].sbZ = xyz[2];
                    m_ulGsnrCount_0++;
                    #if (AHC_SHAREENC_SUPPORT)
                    if (m_bStartGsnr_SHARE)
                    {
                        //AHC_Gsensor_BackupGsnrInfoEx(xyz);
                        GsnrInfoChuckBuf_SHARE[ulGsnrCount_SHARE].sbX = xyz[0];
                        GsnrInfoChuckBuf_SHARE[ulGsnrCount_SHARE].sbY = xyz[1];
                        GsnrInfoChuckBuf_SHARE[ulGsnrCount_SHARE].sbZ = xyz[2];
                        ulGsnrCount_SHARE++;
                    }
                    else
                    {
                        GsnrInfoChuckBuf_Pre_SHARE[ulGsnrCount_Pre_SHARE].sbX = xyz[0];
                        GsnrInfoChuckBuf_Pre_SHARE[ulGsnrCount_Pre_SHARE].sbY = xyz[1];
                        GsnrInfoChuckBuf_Pre_SHARE[ulGsnrCount_Pre_SHARE].sbZ = xyz[2];

                        ulGsnrCount_Pre_SHARE = (ulGsnrCount_Pre_SHARE + 1) % (ulGsnrTCount_Pre_SHARE*AHC_Gsensor_GetAttributeAddr()->ubStoreFreq);
                    }
                    #endif
                    dummy--;
                }while((dummy > 0) && (m_ulGsnrCount_0 < GSNR_MAX_INFONUM));
            }
            else
            {
                GsnrInfoChuckBuf_0[m_ulGsnrCount_0].sbX = xyz[0];
                GsnrInfoChuckBuf_0[m_ulGsnrCount_0].sbY = xyz[1];
                GsnrInfoChuckBuf_0[m_ulGsnrCount_0].sbZ = xyz[2];
                m_ulGsnrCount_0++;
                #if (AHC_SHAREENC_SUPPORT)
                if (m_bStartGsnr_SHARE)
                {
                    //AHC_Gsensor_BackupGsnrInfoEx(xyz);
                    GsnrInfoChuckBuf_SHARE[ulGsnrCount_SHARE].sbX = xyz[0];
                    GsnrInfoChuckBuf_SHARE[ulGsnrCount_SHARE].sbY = xyz[1];
                    GsnrInfoChuckBuf_SHARE[ulGsnrCount_SHARE].sbZ = xyz[2];
                    ulGsnrCount_SHARE++;
                }
                else
                {
                    GsnrInfoChuckBuf_Pre_SHARE[ulGsnrCount_Pre_SHARE].sbX = xyz[0];
                    GsnrInfoChuckBuf_Pre_SHARE[ulGsnrCount_Pre_SHARE].sbY = xyz[1];
                    GsnrInfoChuckBuf_Pre_SHARE[ulGsnrCount_Pre_SHARE].sbZ = xyz[2];

                    ulGsnrCount_Pre_SHARE = (ulGsnrCount_Pre_SHARE + 1) % (ulGsnrTCount_Pre_SHARE*AHC_Gsensor_GetAttributeAddr()->ubStoreFreq);
                }
                #endif
            }
#if (GSNR_USE_FILE_AS_DATABUF)
            if (m_ulGsnrCount_0 == GSNR_MAX_INFONUM)
            {
                UINT32 ulWriteCount;

                AHC_FS_FileWrite(m_ulInfoFileId, (UINT8*)GsnrInfoChuckBuf_0, GSNR_MAX_INFONUM*GSENSOR_DATA_LEN, &ulWriteCount);

                m_ulInfoFileByte += ulWriteCount;

                m_ulGsnrCount_0     = 0;//Reset
                m_ubGsnrBufIndex    = 1;//Toggle
                DBG_GSENSOR_PRINT("%s - Buf0-m_ulInfoFileByte %d\r\n", __func__, m_ulInfoFileByte);
            }
#endif
        }
    }
}

#if (AHC_SHAREENC_SUPPORT)
PGSNR_INFOCHUCK AHC_Gsensor_GetInfoChuckAddrEx(void)
{
    if (m_bStartGsnr_SHARE)
        return GsnrInfoChuckBuf_SHARE;

    return NULL;
}

MMP_ULONG AHC_Gsensor_GetInfoChuckSizeEx(void)
{
    MMP_ULONG ulReturnValue = 0;

    if (m_bStartGsnr_SHARE)
    {
        ulReturnValue = ulGsnrCount_SHARE * sizeof(GSNR_INFOCHUCK);
        #if 0
        RTNA_DBG_Str(0, "##Gsnr Info: ");
        RTNA_DBG_Long(0, ulReturnValue);
        RTNA_DBG_Str(0, "\r\n");
        #endif
        return ulReturnValue;
    }

    return 0;
}
#endif

PGSNR_INFOCHUCK AHC_Gsensor_GetInfoChuckAddr(void)
{
    if(m_bGsnrPingPongBufStart)
    {
        if(m_ubGsnrBufIndex)
            return GsnrInfoChuckBuf_0;
        else
            return GsnrInfoChuckBuf_1;
    }
    else
    {
        if(m_ubGsnrBufIndex)
            return GsnrInfoChuckBuf_0;
        else
            return GsnrInfoChuckBuf_1;
    }
}

MMP_ULONG AHC_Gsensor_GetInfoChuckSize(void)
{
    MMP_ULONG ulReturnValue;

#if (GSNR_USE_FILE_AS_DATABUF)
    ulReturnValue = m_ulInfoFileByte + m_ulInfoLastByte;
#else
    if(m_bGsnrPingPongBufStart)
    {
        if(m_ubGsnrBufIndex)
            ulReturnValue = m_ulGsnrInfoChuckCnt_0;
        else
            ulReturnValue = m_ulGsnrInfoChuckCnt_1;
    }
    else
    {
        if(m_ubGsnrBufIndex)
            ulReturnValue = m_ulGsnrInfoChuckCnt_0;
        else
            ulReturnValue = m_ulGsnrInfoChuckCnt_1;
    }
    ulReturnValue *= sizeof(GSNR_INFOCHUCK);
#endif
    DBG_GSENSOR_PRINT("GSENSORINFO_SIZE:%d\r\n",ulReturnValue);
    return ulReturnValue;
}

PGSNR_CHUCKHDR AHC_Gsensor_GetChuckHeaderAddr(MMP_UBYTE ubSelection)
{
    if(ubSelection == 0)
        return GsnrInfoChuckHdr;
    else
        return GsnrChuckHdr;
}

#if (AHC_SHAREENC_SUPPORT)
void AHC_Gsensor_SetInfoChuckHeaderEx(void)
{
    GsnrChuckHdr[0].ulFourCC = GSENSOR_MAKE_FCC('g','s','e','n');
    GsnrChuckHdr[0].ulSize   = GSENSOR_BIGENDIAN(AHC_Gsensor_GetInfoChuckSizeEx());
}

PGSNR_INFOCHUCK AHC_Gsensor_GetLastDataAddrEx(void)
{
    if (m_bStartGsnr_SHARE)
        return GsnrInfoChuckBuf_SHARE;

    return NULL;
}
#endif

void AHC_Gsensor_SetInfoChuckHeader(void)
{
    GsnrChuckHdr[0].ulFourCC = GSENSOR_MAKE_FCC('g','s','e','n');
    GsnrChuckHdr[0].ulSize   = GSENSOR_BIGENDIAN(AHC_Gsensor_GetInfoChuckSize());
}

void AHC_Gsensor_SetAttribChuckHeader(void)
{
    GsnrInfoChuckHdr[0].ulFourCC = GSENSOR_MAKE_FCC('g','s','e','a');
    GsnrInfoChuckHdr[0].ulSize   = GSENSOR_BIGENDIAN(sizeof(GSNR_ATTRIBUTE));
}

PGSNR_ATTRIBUTE AHC_Gsensor_GetAttributeAddr(void)
{
    return MMPF_3RDParty_Gsensor_GetAttribute();
}

PGSNR_INFOCHUCK AHC_Gsensor_GetLastDataAddr(void)
{
    if( m_ubGsnrBufIndex_Store == 0 )
    {
        m_ulGsnrCount_Last    = m_ulGsnrCount_0;
        m_ubGsnrBufIndex_Last = 0;
        DBG_GSENSOR_PRINT("Flush Buffer0 size %d\r\n",m_ulInfoLastByte);
        m_ulGsnrCount_0 = 0;
        return GsnrInfoChuckBuf_0;
    }
    else if( m_ubGsnrBufIndex_Store == 1 )
    {
        m_ulGsnrCount_Last    = m_ulGsnrCount_1;
        m_ubGsnrBufIndex_Last = 1;
        DBG_GSENSOR_PRINT("Flush Buffer1 size %d\r\n",m_ulInfoLastByte);
        m_ulGsnrCount_1 = 0;
        return GsnrInfoChuckBuf_1;
    }
    return 0;
}

PGSNR_INFOCHUCK AHC_Gsensor_GetBackupDataAddr(void)
{
    if( m_ubGsnrBufIndex_Backup == 0 )
    {
        return GsnrInfoChuckBuf_0;
    }
    else
    {
        return GsnrInfoChuckBuf_1;
    }
}

#endif

#if 0
void _____RAW_Write_Function_________(){ruturn;} //dummy
#endif

#if ((GSENSOR_RAW_FILE_ENABLE == 1) && ((GPS_RAW_FILE_ENABLE == 1) || (GPS_RAW_FILE_EMER_EN == 1)))
extern int          sprintf(char * /*s*/, const char * /*format*/, ...);
extern AHC_GSENSOR_DATA TempGValue;
extern MMP_ULONG    ulGPSRawEmerStartAddr ;

MMP_BOOL AHC_Gsensor_RawWrite(MMP_BOOL bWriteFile)//(MMP_BYTE *pBuff, MMP_USHORT usLength)
{
    AHC_BOOL            err = AHC_FALSE;
    AHC_GSENSOR_DATA    sdata;
    MMP_UBYTE           i;
    //MMP_ULONG     ulWriteSize = 0;
    MMP_ULONG           ulFileId       = 0;
    MMP_ULONG           ulFileId_Emer  = 0;
    char                buffer[32] = {0}, temp[10] = {0};

    #if (GSENSOR_MODULE == GSENSOR_MODULE_LIS3DH)

        #if (GSENSOR_DETECT_MODE == GSNESOR_DETECT_DIFF)
        sdata.acc_val[0] = TempGValue.acc_val[0];
        sdata.acc_val[1] = TempGValue.acc_val[1];
        sdata.acc_val[2] = TempGValue.acc_val[2];

        TempGValue.acc_val[0] = 0;
        TempGValue.acc_val[1] = 0;
        TempGValue.acc_val[2] = 0;
        #else
        err = AHC_Gsensor_Read_XYZ(&sdata);
        #endif

    #elif ((GSENSOR_MODULE == GSENSOR_MODULE_GMA305)||(GSENSOR_MODULE == GSENSOR_MODULE_DMARD)||
    (GSENSOR_MODULE == GSENSOR_MODULE_GMA301) || (GSENSOR_MODULE == GSENSOR_MODULE_GMA302))
        err = AHC_Gsensor_Read_XYZ_WithCompensation(&sdata);
    #elif ((GSENSOR_MODULE == GSENSOR_MODULE_RT3000)||(GSENSOR_MODULE == GSENSOR_MODULE_MC3256) ||
    (GSENSOR_MODULE == GSENSOR_MODULE_DA312)||(GSENSOR_MODULE == GSENSOR_MODULE_DA380ANDSC7A30E)||
    (GSENSOR_MODULE == GSENSOR_MODULE_SC7A30E))
        err = AHC_Gsensor_Read_XYZ(&sdata);
    #endif

    //if(dump_GValues)
        //printc("x=%5.3f, y=%5.3f, z=%5.3f\r\n", sdata.acc_val[0], sdata.acc_val[1], sdata.acc_val[2]);

    //AHC_FS_FileWrite(ulFileId, (UINT8 *)GSENSOR_RAW_HEADER, sizeof(GSENSOR_RAW_HEADER), &ulWriteSize);
    STRCPY(buffer,GSENSOR_RAW_HEADER);
    GPSCtrl_Scanf(temp,9, "%5.3f,", sdata.acc_val[0]/1000.0);
    STRCAT(buffer,temp);
    //STRCAT(buffer, ",");
    MEMSET0(temp);
    GPSCtrl_Scanf(temp, 9, "%5.3f,", sdata.acc_val[1]/1000.0);
    STRCAT(buffer,temp);
    //STRCAT(buffer, ",");
    MEMSET0(temp);
    GPSCtrl_Scanf(temp, 9, "%5.3f", sdata.acc_val[2]/1000.0);
    STRCAT(buffer, temp);
    STRCAT(buffer, "\r");
    STRCAT(buffer, "\n");
    //printc("sizeof(buffer) : %d\r\n", sizeof(buffer));

    GValueInNmea[0] = sdata.acc_val[0];
    GValueInNmea[1] = sdata.acc_val[1];
    GValueInNmea[2] = sdata.acc_val[2];

    for (i = 0; i < 32; i++)
    {
        if (STRCMP(buffer + i, "\n") == 0)
            break;
    }
    if (bWriteFile)
    {
        #if (SUPPORT_PARKINGMODE != PARKINGMODE_NONE)
        if (!uiGetParkingModeEnable())
        #endif
        {
            ulFileId_Emer = GPSCtrl_GetGPSRawFileId_Emer();
            if (ulFileId_Emer != 0)
            {
                {
                    GPSCtrl_GPSRawWriteFlushBuf_Emer();
                    if (ulGPSRawEmerStartAddr != 0)
                    {
                        ulGPSRawEmerStartAddr = 0;
                    }
                }

                if (MMPS_3GPRECD_GetEmergActionType() == MMP_3GPRECD_EMERG_SWITCH_FILE)
                {
                    GPSCtrl_GPSRawResetBuffer();
                }
            }
        }
        ulFileId = GPSCtrl_GetGPSRawFileId();
        if (ulFileId != 0)
        {
            {
                GPSCtrl_GPSRawFlushBuf();
            }
        }
    }
    else
    {
        #if (SUPPORT_PARKINGMODE != PARKINGMODE_NONE)
        if(uiGetParkingModeRecord() || !uiGetParkingModeEnable())
        #endif
        {
            GPSCtrl_GPSRawWriteBuffer(buffer, i + 1);
            GPSCtrl_GPSRawWriteBuffer_Emer(buffer, i + 1);
        }

        if (MMPS_3GPRECD_GetEmergActionType() == MMP_3GPRECD_EMERG_SWITCH_FILE)
        {
            GPSCtrl_GPSRawWriteBuffer_Normal(buffer, i + 1);
        }
    }
    return TRUE;
}
#endif

#if (GSENSOR_CONNECT_ENABLE)
void AHC_Gsensor_TriggerRestorePreRecordInfo( MMP_BOOL bTrigger, UINT32 ulPreRecordTime, MMP_BOOL bUseLastData )
{
    m_bGsensor_TriggerRestorePreRecordInfo = bTrigger;
    m_ulGsnrPreRecordTime = ulPreRecordTime;
    m_bGsensor_UseLastData = bUseLastData;
}

MMP_BOOL AHC_Gsensor_NeedToRestorePreRecordInfo( UINT32* ulPreRecordTime )
{
    if( m_ulGsnrPreRecordTime != GSENSOR_DEFAULT_PRERECORD_TIME )
    {
        *ulPreRecordTime = m_ulGsnrPreRecordTime;
    }

    return m_bGsensor_TriggerRestorePreRecordInfo;
}

void AHC_Gsensor_FlushBackupBuffer(MMP_UBYTE ubID, MMP_BOOL bEnable)
{
    m_bGsensor_FlushBackupBuffer[ubID] = bEnable;
}

MMP_BOOL AHC_Gsensor_NeedToFlushBackupBuffer(MMP_UBYTE ubID)
{
    return m_bGsensor_FlushBackupBuffer[ubID];
}
#endif

#if 0
void _____Gsensor_Task_Function_________(){ruturn;} //dummy
#endif

#if (GSENSOR_CONNECT_ENABLE)
void GsensorCtrlTask_init(void)
{
    //Nop
    UartSendTrace("GsensorCtrlTask_init\n\r");
}

void GsensorCtrlTask(void)
{
    MMPF_OS_FLAGS       flags;
    MMPF_OS_FLAGS       waitFlags;

    #if (GSENSOR_CONNECT_ENABLE)
    waitFlags = GSENSOR_FLAG_GSNRINFO2CHUCK;
    #endif

    // waitFlags can not be 0.
    waitFlags |= GSENSOR_CTL_FLAG_MAX;

    while(1)
    {
        MMPF_OS_WaitFlags( GsensorCtrlFlag, waitFlags, MMPF_OS_FLAG_WAIT_SET_ANY | MMPF_OS_FLAG_CONSUME, 0, &flags);

        if ( flags & GSENSOR_FLAG_GSNRINFO2CHUCK )
        {
            if(AHC_Gsensor_Module_Attached())
            {
                AHC_Gsensor_RestoreAviChuck();
            }
        }
    }
}

void GsensorCtrl_TaskHandler_init(void *p_arg)
{
    GsensorCtrlFlag = MMPF_OS_CreateEventFlagGrp(0);
    if (GsensorCtrlFlag >= MMPF_OS_ERR_FLAG_ID_EXCEED_MAX) {
        AHC_DBG_MSG(1, "Error:GsensorCtrlFlag Failed\r\n");
    }
    GsensorCtrlTask_init();
}

void GsensorCtrl_TaskHandler(void *p_arg)
{
    GsensorCtrlTask();
}
#endif