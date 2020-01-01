//------------------------------------------------------------------------------
//
//  File        : component_dip.c
//  Description : Source file of dip component configuration
//  Author      : Eroy
//  Revision    : 0.1
//
//------------------------------------------------------------------------------

//==============================================================================
//
//                              INCLUDE FILE
//
//==============================================================================

#include "mmp_component_ctl.h"
#include "mmp_hif_cmd.h"
#include "component_aud.h"
#include "mmp_aud_inc.h"
#include "mmps_audio.h"
#include "mmps_aui.h"

//==============================================================================
//
//                              VARIABLES
//
//==============================================================================

/*Audio Encode*/
MMP_ERR Component_AudEnc_InitDevice (void *handler);
MMP_ERR Component_AudEnc_UnInitDevice (void *handler);
MMP_ERR Component_AudEnc_OpenDevice (void *handler);
MMP_ERR Component_AudEnc_EmptyBuffer (void *handler, MMP_ULONG ulSize, void *BufInfo);
MMP_ERR Component_AudEnc_EmptyBufferDone (void *handler, MMP_ULONG ulSize, void *BufInfo);
MMP_ERR Component_AudEnc_UpdateBuffer (void *handler, MMP_ULONG ulSize, void *BufInfo);
MMP_ERR Component_AudEnc_AllocateBuffer (void *handler);

MMP_COMPONENT_BUFFER_INFO Component_AudEnc_BufInfo[AUDENC_COMPONENT_MAX][COMP_MAX_OUTBUF_NUM];
MMP_COMPONENT_PORT_INFO Component_AudEnc_InPort[AUDENC_COMPONENT_MAX];
MMP_COMPONENT_PORT_INFO Component_AudEnc_OutPort[AUDENC_COMPONENT_MAX][MAX_OUTPUT_COMP_NUM];
MMP_COMPONENT_MEMORY_INFO Component_AudEnc_MemoryInfo[AUDENC_COMPONENT_MAX];
MMP_COMPONENT_HANDLER_AUD Component_AudEnc_DevInfo[AUDENC_COMPONENT_MAX];

/*Audio Decode*/
MMP_ERR Component_AudDec_InitDevice (void *handler);
MMP_ERR Component_AudDec_UnInitDevice (void *handler);
MMP_ERR Component_AudDec_OpenDevice (void *handler);
MMP_ERR Component_AudDec_EmptyBuffer (void *handler, MMP_ULONG ulSize, void *BufInfo);
MMP_ERR Component_AudDec_EmptyBufferDone (void *handler, MMP_ULONG ulSize, void *BufInfo);
MMP_ERR Component_AudDec_UpdateBuffer (void *handler, MMP_ULONG ulSize, void *BufInfo);
MMP_ERR Component_AudDec_AllocateBuffer (void *handler);

MMP_COMPONENT_BUFFER_INFO Component_AudDec_BufInfo[AUDDEC_COMPONENT_MAX][COMP_MAX_OUTBUF_NUM];
MMP_COMPONENT_PORT_INFO Component_AudDec_InPort[AUDDEC_COMPONENT_MAX];
MMP_COMPONENT_PORT_INFO Component_AudDec_OutPort[AUDDEC_COMPONENT_MAX][MAX_OUTPUT_COMP_NUM];
MMP_COMPONENT_MEMORY_INFO Component_AudDec_MemoryInfo[AUDDEC_COMPONENT_MAX];
MMP_COMPONENT_HANDLER_AUD Component_AudDec_DevInfo[AUDDEC_COMPONENT_MAX];

/*Audio Encode*/
MMP_COMPONENT_BASE Component_AUD_Encode[AUDENC_COMPONENT_MAX] = {
    {
    "AUDENC",
    MMP_COMPONENT_STATE_INVALID,            //  ulState
    MMP_TRUE,                               //  bRegistered
    MMP_FALSE,                              //  bByPass
    0,                                      //  ubOutputPortNum
    &Component_AudEnc_MemoryInfo[AUDENC_COMPONENT_FRONT],           //  MemoryInfo
    Component_AudEnc_BufInfo[AUDENC_COMPONENT_FRONT],                   //  BufferInfo
    NULL,               //  pInPort
    &Component_AudEnc_OutPort[AUDENC_COMPONENT_FRONT],                  //  pOutPort
    {
        &MMP_CompCtl_UpdateBuffer_Ring,
        &MMP_CompCtl_EmptyBuffer_Ring,
        NULL,
        &MMP_CompCtl_EmptyBufferDone_Ring,
    },

    Component_AudEnc_InitDevice,            //  pfInit
    Component_AudEnc_OpenDevice,            //  pfOpen
    Component_AudEnc_AllocateBuffer,           //  pfAllocateMemory
    NULL,                                   //  pfFreeMemory   
    Component_AudEnc_UnInitDevice,          //  pfUnInit
    NULL,                                   //  pfClose
    NULL,                                   //  pfSetParameter
    NULL,                                   //  pfGetParameter
    Component_AudEnc_UpdateBuffer,             //  pfUpdateBuffer
    Component_AudEnc_EmptyBuffer,           //  pfEmptyBuffer
    NULL,                                   //  pfEmptyBufferDone
    NULL,                                                   // pfGetBufferInfo
    &Component_AudEnc_DevInfo[AUDENC_COMPONENT_FRONT]       //  DeviceInfo
    },
};

MMP_COMPONENT_BASE Component_AUD_Decode[AUDDEC_COMPONENT_MAX] =
{
    {
    "AUDDEC",
    MMP_COMPONENT_STATE_INVALID,            //  ulState
    MMP_TRUE,                               //  bRegistered
    MMP_FALSE,                              //  bByPass
    0,                                      //  ubOutputPortNum
    &Component_AudDec_MemoryInfo[AUDDEC_COMPONENT_PLAYBACK],           //  MemoryInfo
    Component_AudDec_BufInfo[AUDDEC_COMPONENT_PLAYBACK],                    //  BufferInfo
    NULL,               //  pInPort
    &Component_AudDec_OutPort[AUDDEC_COMPONENT_PLAYBACK],                  //  pOutPort
    {
        &MMP_CompCtl_UpdateBuffer_Ring,
        &MMP_CompCtl_EmptyBuffer_Ring,
        NULL,
        &MMP_CompCtl_EmptyBufferDone_Ring,
    },

    Component_AudDec_InitDevice,            //  pfInit
    Component_AudDec_OpenDevice,            //  pfOpen
    Component_AudDec_AllocateBuffer,        //  pfAllocateMemory
    NULL,                                   //  pfFreeMemory
    Component_AudDec_UnInitDevice,          //  pfUnInit
    NULL,                                   //  pfClose
    NULL,                                   //  pfSetParameter
    NULL,                                   //  pfGetParameter
    Component_AudDec_UpdateBuffer,             //  pfUpdateBuffer
    Component_AudDec_EmptyBuffer,           //  pfEmptyBuffer
    NULL,                                   //  pfEmptyBufferDone
    NULL,                                   //  pfEmptyBufferDone
    &Component_AudDec_DevInfo[AUDDEC_COMPONENT_PLAYBACK]                    //  DeviceInfo
    },
};

//==============================================================================
//
//                              FUNCTIONS
//
//==============================================================================

/*Audio Encode*/
MMP_ERR Component_AudEnc_InitDevice(void *handler)
{
    return MMP_ERR_NONE;
}

MMP_ERR Component_AudEnc_UnInitDevice(void *handler)
{
    return MMP_ERR_NONE;
}

MMP_ERR Component_AudEnc_OpenDevice(void *handler)
{
    MMP_COMPONENT_BASE *pComp = (MMP_COMPONENT_BASE *)handler;
    MMP_COMPONENT_HANDLER_AUD *pDev = (MMP_COMPONENT_HANDLER_AUD *)pComp->DeviceInfo;
    MMP_UBYTE   ubencodefmt;

    switch(pDev->AudOption)
    {
        case COMPONENT_AUD_AAC_16K_32K:
        case COMPONENT_AUD_ADPCM_16K_22K:
        case COMPONENT_AUD_PCM_16K:
            pDev->ulSampleRate = 16000;
            break;
        case COMPONENT_AUD_AAC_22d05K_64K:
        case COMPONENT_AUD_AAC_22d05K_128K:
            pDev->ulSampleRate = 22050;
            break;
        case COMPONENT_AUD_AAC_32K_64K:
        case COMPONENT_AUD_AAC_32K_128K:
        case COMPONENT_AUD_ADPCM_32K_22K:
        case COMPONENT_AUD_MP3_32K_128K:
        case COMPONENT_AUD_PCM_32K:
            pDev->ulSampleRate = 32000;
            break;
        case COMPONENT_AUD_AAC_44d1K_64K:
        case COMPONENT_AUD_AAC_44d1K_128K:
        case COMPONENT_AUD_ADPCM_44d1K_22K:
        case COMPONENT_AUD_MP3_44d1K_128K:
            pDev->ulSampleRate = 44100;
            break;
        case COMPONENT_AUD_AAC_48K_128K:
        case COMPONENT_AUD_ADPCM_48K_22K:
            pDev->ulSampleRate = 48000;
            break;
    }

    switch(pDev->AudOption)
    {
        case COMPONENT_AUD_ADPCM_16K_22K:
        case COMPONENT_AUD_ADPCM_32K_22K:
        case COMPONENT_AUD_ADPCM_44d1K_22K:
        case COMPONENT_AUD_ADPCM_48K_22K:
            pDev->ulBitRate = 22000;
            break;
        case COMPONENT_AUD_AAC_16K_32K:
            pDev->ulBitRate = 32000;
            break;

        case COMPONENT_AUD_AAC_22d05K_64K:
        case COMPONENT_AUD_AAC_32K_64K:
        case COMPONENT_AUD_AAC_44d1K_64K:
            pDev->ulBitRate = 64000;
            break;

        case COMPONENT_AUD_AAC_22d05K_128K:
        case COMPONENT_AUD_AAC_32K_128K:
        case COMPONENT_AUD_MP3_32K_128K:
        case COMPONENT_AUD_AAC_44d1K_128K:
        case COMPONENT_AUD_MP3_44d1K_128K:
        case COMPONENT_AUD_AAC_48K_128K:
            pDev->ulBitRate = 128000;
            break;
    }

    switch(pDev->AudFormat)
    {
        case COMPONENT_AUD_FORMAT_AAC:
            ubencodefmt = MMP_AUDIO_VAAC_ENCODE;
            break;
        case COMPONENT_AUD_FORMAT_AMR:
            ubencodefmt = MMP_AUDIO_VAMR_ENCODE;
            break;
        case COMPONENT_AUD_FORMAT_ADPCM:
            ubencodefmt = MMP_AUDIO_VADPCM_ENCODE; // Only support this format currently.
            break;
        case COMPONENT_AUD_FORMAT_MP3:
            ubencodefmt = MMP_AUDIO_VMP3_ENCODE;
            break;
        case COMPONENT_AUD_FORMAT_PCM:
            ubencodefmt = MMP_AUDIO_VPCM_ENCODE;
            break;
    }

    MMPD_AUDIO_SetEncodeFileSize(0xFFFFFFFF);

    //Set Record mode
    MMPF_Audio_SetEncodePath(1); //MMPF_AUDIO_DATAPATH_CARD

    //Set Audio gain
    if(pDev->AudPath == COMPONENT_AUD_RECORD_PATH_DIFF_STERO_MIC)
    {
        MMPF_Audio_SetVoiceInPath(MMP_AUD_AFE_IN_DIFF);
        MMPF_Audio_SetMicPreGain(pDev->pAudGain->ubMicPreGainLevel);
    }
    MMPF_Audio_SetVoiceInPath(MMP_AUD_AFE_IN_SING);
    MMPF_Audio_SetLineInChannel(MMP_AUD_LINEIN_L);
    MMPF_Audio_SetMicPreGain(pDev->pAudGain->ubMicPreGainLevel);
    MMPF_Audio_SetADCDigitalGain(pDev->pAudGain->sDpgaGain, MMP_TRUE);
    MMPF_Audio_SetADCAnalogGain(pDev->pAudGain->ubADCGainLevel, MMP_TRUE);

    //Set Audio Format
    MMPD_AUDIO_SetEncodeFormat(ubencodefmt);

    switch(ubencodefmt)
    {
        case MMP_AUDIO_VAAC_ENCODE:
            //MMPF_InitAACEncoder();
            break;
        case MMP_AUDIO_VAMR_ENCODE:
            //MMPF_InitAMREncoder();
            break;
        case MMP_AUDIO_VADPCM_ENCODE:
            MMPF_InitADPCMEncoder();// TBD // Only support this format currently.
            break;
        case MMP_AUDIO_VMP3_ENCODE:
            //MMPF_InitMP3Encoder();// TBD
            break;
        case MMP_AUDIO_VPCM_ENCODE:
            MMPF_InitWAVEncoder();
            MMPF_SetWAVRecMode(2);  //Samplerate = 8000
            break;
    }

    return MMP_ERR_NONE;
}

MMP_ERR Component_AudEnc_CloseDevice(void *handler)
{
    MMP_COMPONENT_BASE *pComp = (MMP_COMPONENT_BASE *)handler;
    MMP_COMPONENT_HANDLER_AUD *pDev = (MMP_COMPONENT_HANDLER_AUD *)pComp->DeviceInfo;
    printc("Component_AudEnc_CloseDevice\r\n");
    //Disable Capture
    //MMPF_Audio_DisableCapture();
    MMPF_SetWAVEncodeOp(ENCODE_OP_STOP);

    return MMP_ERR_NONE;
}

MMP_ERR Component_AudEnc_EmptyBuffer(void *handler, MMP_ULONG ulSize, void *BufInfo)
{
    MMP_COMPONENT_BASE *pComp = (MMP_COMPONENT_BASE *)handler;
    MMP_COMPONENT_HANDLER_AUD *pDev = (MMP_COMPONENT_HANDLER_AUD *)pComp->DeviceInfo;
    printc("Component_AudEnc_EmptyBuffer\r\n");

    MMPF_SetWAVEncodeOp(ENCODE_OP_START);

    return MMP_ERR_NONE;
}

MMP_ERR Component_AudEnc_EmptyBufferDone(void *handler, MMP_ULONG ulSize, void *BufInfo)
{
    return MMP_ERR_NONE;
}

extern MMP_ERR MMPF_Audio_AddPCM_TestData(MMP_ULONG ultime);
MMP_ERR Component_AudEnc_UpdateBuffer(void *handler, MMP_ULONG ulSize, void *BufInfo)
{
    MMP_COMPONENT_BASE *pComp = (MMP_COMPONENT_BASE *)handler;
    MMP_COMPONENT_MEMORY_INFO *pMem = pComp->MemoryInfo;
    MMP_COMPONENT_HANDLER_AUD *pDev = (MMP_COMPONENT_HANDLER_AUD *)pComp->DeviceInfo;
    // Inform MGR
    pMem->memctl.ring.ulWL = ALIGN32(pMem->memctl.ring.ulWL);

    return MMP_ERR_NONE;
}

MMP_ERR Component_AudEnc_AllocateBuffer (void *handler)
{
    MMP_COMPONENT_BASE *pComp = (MMP_COMPONENT_BASE *)handler;
    MMP_COMPONENT_BUFFER_INFO *pBuf = pComp->BufferInfo;
    MMP_COMPONENT_MEMORY_INFO *pMem = pComp->MemoryInfo;
    MMP_COMPONENT_HANDLER_AUD *pDev = (MMP_COMPONENT_HANDLER_AUD *)pComp->DeviceInfo;
    MMP_ULONG ulStartAddr;

    ulStartAddr = pBuf[0].ulBufAddr;
    printc("Component_AUD_AllocateBuffer ulStartAddr : 0x%x\r\n",ulStartAddr);
    printc("Component_AUD_AllocateBuffer ulBufSize : %d\r\n",pMem->ulBufSize);
    MMPF_Audio_SetEncodeBuffer(ulStartAddr, pMem->ulBufSize);

    return MMP_ERR_NONE;
}

// Audio Decode

MMP_ERR Component_AudDec_InitDevice(void *handler)
{
    return MMP_ERR_NONE;
}

MMP_ERR Component_AudDec_UnInitDevice(void *handler)
{
    return MMP_ERR_NONE;
}

MMP_ERR Component_AudDec_OpenDevice (void *handler)
{
    MMP_COMPONENT_BASE *pComp = (MMP_COMPONENT_BASE *)handler;
    MMP_COMPONENT_HANDLER_AUD *pDev = (MMP_COMPONENT_HANDLER_AUD *)pComp->DeviceInfo;
    MMP_UBYTE   ubencodefmt;
    MMPS_AUDIO_FILEINFO fileinfo = {0};
    MMPS_AUDIO_WAV_INFO  wavinfo = {0};

    switch(pDev->AudOption)
    {
        case COMPONENT_AUD_AAC_16K_32K:
        case COMPONENT_AUD_ADPCM_16K_22K:
        case COMPONENT_AUD_PCM_16K:
            pDev->ulSampleRate = 16000;
            break;
        case COMPONENT_AUD_AAC_22d05K_64K:
        case COMPONENT_AUD_AAC_22d05K_128K:
            pDev->ulSampleRate = 22050;
            break;
        case COMPONENT_AUD_AAC_32K_64K:
        case COMPONENT_AUD_AAC_32K_128K:
        case COMPONENT_AUD_ADPCM_32K_22K:
        case COMPONENT_AUD_MP3_32K_128K:
        case COMPONENT_AUD_PCM_32K:
            pDev->ulSampleRate = 32000;
            break;
        case COMPONENT_AUD_AAC_44d1K_64K:
        case COMPONENT_AUD_AAC_44d1K_128K:
        case COMPONENT_AUD_ADPCM_44d1K_22K:
        case COMPONENT_AUD_MP3_44d1K_128K:
            pDev->ulSampleRate = 44100;
            break;
        case COMPONENT_AUD_AAC_48K_128K:
        case COMPONENT_AUD_ADPCM_48K_22K:
            pDev->ulSampleRate = 48000;
            break;
    }
    switch(pDev->AudOption)
    {
        case COMPONENT_AUD_ADPCM_16K_22K:
        case COMPONENT_AUD_ADPCM_32K_22K:
        case COMPONENT_AUD_ADPCM_44d1K_22K:
        case COMPONENT_AUD_ADPCM_48K_22K:
            pDev->ulBitRate = 22000;
            break;
        case COMPONENT_AUD_AAC_16K_32K:
            pDev->ulBitRate = 32000;
            break;

        case COMPONENT_AUD_AAC_22d05K_64K:
        case COMPONENT_AUD_AAC_32K_64K:
        case COMPONENT_AUD_AAC_44d1K_64K:
            pDev->ulBitRate = 64000;
            break;

        case COMPONENT_AUD_AAC_22d05K_128K:
        case COMPONENT_AUD_AAC_32K_128K:
        case COMPONENT_AUD_MP3_32K_128K:
        case COMPONENT_AUD_AAC_44d1K_128K:
        case COMPONENT_AUD_MP3_44d1K_128K:
        case COMPONENT_AUD_AAC_48K_128K:
            pDev->ulBitRate = 128000;
            break;
    }

    switch(pDev->AudFormat)
    {
        case COMPONENT_AUD_FORMAT_AAC:
            ubencodefmt = MMP_AUDIO_VAAC_ENCODE;
            break;
        case COMPONENT_AUD_FORMAT_AMR:
            ubencodefmt = MMP_AUDIO_VAMR_ENCODE;
            break;
        case COMPONENT_AUD_FORMAT_ADPCM:
            ubencodefmt = MMP_AUDIO_VADPCM_ENCODE; // Only support this format currently.
            break;
        case COMPONENT_AUD_FORMAT_MP3:
            ubencodefmt = MMP_AUDIO_VMP3_ENCODE;
            break;
        case COMPONENT_AUD_FORMAT_PCM:
            ubencodefmt = MMP_AUDIO_VPCM_ENCODE;
            break;
    }

    STRCPY(fileinfo.bFileName, "SD:0:\\Test.wav");
    fileinfo.usFileNameLength = STRLEN("SD:0:\\Test.wav");
    MMPS_AUI_SetMediaPath(MMPS_AUI_MEDIA_PATH_CARD);
    MMPS_AUI_InitializeWAVPlay(&fileinfo, &wavinfo);
    //Set Audio gain
    MMPD_AUDIO_SetPlayVolume(0, (MMP_UBYTE)pDev->pAudGain->sDpgaGain,0, MMP_FALSE);
    //MMPF_Audio_SetVoiceOutPath(MMP_AUD_AFE_OUT_LINE);
    //MMPF_Audio_SetPlayFormat(MMP_AUDIO_WAV_PLAY);
    MMPF_Audio_SetDACDigitalGain(pDev->pAudGain->sDpgaGain);

    return MMP_ERR_NONE;
}

MMP_ERR Component_AudDec_CloseDevice (void *handler)
{
    MMP_COMPONENT_BASE *pComp = (MMP_COMPONENT_BASE *)handler;
    MMP_COMPONENT_HANDLER_AUD *pDev = (MMP_COMPONENT_HANDLER_AUD *)pComp->DeviceInfo;
    printc("Component_AudDec_CloseDevice\r\n");
        //Disable PlayBack
    MMPF_Aui_SetWAVDecodeOp(DECODE_OP_STOP);

    return MMP_ERR_NONE;
}

MMP_ERR Component_AudDec_EmptyBuffer (void *handler, MMP_ULONG ulSize, void *BufInfo)
{
    MMP_COMPONENT_BASE *pComp = (MMP_COMPONENT_BASE *)handler;
    MMP_COMPONENT_HANDLER_AUD *pDev = (MMP_COMPONENT_HANDLER_AUD *)pComp->DeviceInfo;
    printc("Component_AudDec_EmptyBuffer\r\n");
        //Enable Playback
    //MMPF_Aui_SetWAVDecodeOp(DECODE_OP_START, MMP_AUD_PLAYER_TYPE_AUDIO);
    MMPS_AUI_StartWAVPlay();
    return MMP_ERR_NONE;
}

MMP_ERR Component_AudDec_EmptyBufferDone (void *handler, MMP_ULONG ulSize, void *BufInfo)
{
    return MMP_ERR_NONE;
}

extern MMP_ERR MMPF_Audio_AddPCM_TestData(MMP_ULONG ultime);
MMP_ERR Component_AudDec_UpdateBuffer(void *handler, MMP_ULONG ulSize, void *BufInfo)
{
    MMP_COMPONENT_BASE *pComp = (MMP_COMPONENT_BASE *)handler;
    MMP_COMPONENT_MEMORY_INFO *pMem = pComp->MemoryInfo;
    MMP_COMPONENT_HANDLER_AUD *pDev = (MMP_COMPONENT_HANDLER_AUD *)pComp->DeviceInfo;

    MMPF_Audio_AddPCM_TestData(2);// For Component test

    return MMP_ERR_NONE;
}

MMP_ERR Component_AudDec_AllocateBuffer (void *handler)
{
    MMP_COMPONENT_BASE *pComp = (MMP_COMPONENT_BASE *)handler;
    MMP_COMPONENT_BUFFER_INFO *pBuf = pComp->BufferInfo;
    MMP_COMPONENT_MEMORY_INFO *pMem = pComp->MemoryInfo;
    MMP_COMPONENT_HANDLER_AUD *pDev = (MMP_COMPONENT_HANDLER_AUD *)pComp->DeviceInfo;
    MMP_ULONG ulStartAddr;

    ulStartAddr = pBuf[0].ulBufAddr;
    MMPF_Audio_SetPlayBuffer(ulStartAddr, pMem->ulBufSize);

    return MMP_ERR_NONE;
}

MMP_COMPONENT_HANDLER_AUD_GAIN AudGainTest[1] =
{
    {MMP_AUD_GAIN_MIC_PREGAIN_13dB, MMP_AUD_GAIN_MIC_ADC_ANALOG_P6dB, 3}
};

MMP_ERR Component_AUD_UnitTest(MMP_UBYTE ubCase)
{
#if 0 // Save Bin Size
    //__align(64) static unsigned char CompBuffer[1024*1024];
    static unsigned char CompBuffer[1024*1024];
    MMP_ULONG   counter = 0;
    MMP_ULONG   nOverrunTh, nUnderrunTh, nDataSize, nActualSize, nTimes, eDmaChannel =1;
    MMP_BOOL    bOverrun, bUnderrun;

    printc("Component_AUD_UnitTest\r\n");

    switch (ubCase)
    {
        case 1:
        {
            Component_AUD_Encode[AUDENC_COMPONENT_FRONT].BufferInfo->ulBufAddr = &CompBuffer[0];
            Component_AUD_Encode[AUDENC_COMPONENT_FRONT].BufferInfo->ulSize = 1024*1024;
            Component_AUD_Encode[AUDENC_COMPONENT_FRONT].MemoryInfo->ulBufSize = 1024*1024;
            printc("Component_AudEnc_InitDevice\r\n");
            Component_AudEnc_InitDevice((void *)&Component_AUD_Encode[AUDENC_COMPONENT_FRONT]);
            Component_AudEnc_AllocateBuffer((void *)&Component_AUD_Encode[AUDENC_COMPONENT_FRONT]);

            Component_AudEnc_OpenDevice((void *)&Component_AUD_Encode[AUDENC_COMPONENT_FRONT]);

            MMPF_ClkSync_SetInFrameRate(1000, 30000);
            MMPF_ClkSync_SetOutFrameRate(1000, 30000);
            MMPF_ClkSync_RefreshClk(1, 1);

            Component_AudEnc_EmptyBuffer((void *)&Component_AUD_Encode[AUDENC_COMPONENT_FRONT], 0 , NULL);

            while(counter < 500000)
            {
                counter++;
                //SYS_UDELAY(100);
                MMPF_OS_SleepMs(1);
                if(counter % 5000 == 0)
                {
                    //printc("&");
                    Component_AudEnc_UpdateBuffer((void *)&Component_AUD_Encode[AUDENC_COMPONENT_FRONT], 0 , NULL);

                }
            }
            Component_AudEnc_CloseDevice((void *)&Component_AUD_Encode[AUDENC_COMPONENT_FRONT]);
            Component_AudEnc_UnInitDevice((void *)&Component_AUD_Encode[AUDENC_COMPONENT_FRONT]);
        }
        break;

        case 2:
        {
            printc("Component_AUD_InitDevice\r\n");
            //Init device info
            Component_AudDec_DevInfo[AUDDEC_COMPONENT_PLAYBACK].AudPath = COMPONENT_AUD_PLAYBACK_PATH_SINGLE_LINEOUT;
            Component_AudDec_DevInfo[AUDDEC_COMPONENT_PLAYBACK].AudFormat = COMPONENT_AUD_FORMAT_PCM;
            Component_AudDec_DevInfo[AUDDEC_COMPONENT_PLAYBACK].AudOption = COMPONENT_AUD_PCM_16K;
            Component_AudDec_DevInfo[AUDDEC_COMPONENT_PLAYBACK].pAudGain = &AudGainTest[0];
            Component_AudDec_DevInfo[AUDDEC_COMPONENT_PLAYBACK].ulSampleRate = 16000;


            Component_AUD_Decode[AUDDEC_COMPONENT_PLAYBACK].BufferInfo->ulBufAddr = &CompBuffer[0];
            Component_AUD_Decode[AUDDEC_COMPONENT_PLAYBACK].BufferInfo->ulSize = 1024*1024;
            Component_AUD_Decode[AUDDEC_COMPONENT_PLAYBACK].MemoryInfo->ulBufSize = 1024*1024;
            Component_AudDec_InitDevice((void *)&Component_AUD_Decode[AUDDEC_COMPONENT_PLAYBACK]);
            Component_AudDec_AllocateBuffer((void *)&Component_AUD_Decode[AUDDEC_COMPONENT_PLAYBACK]);

            Component_AudDec_OpenDevice((void *)&Component_AUD_Decode[AUDDEC_COMPONENT_PLAYBACK]);

            MMPS_AUDIO_SetPlayVolumeDb(70);
            // Turn on Speaker
            //Enable GPIO mode for GPIO nNum
            DrvGPIOPadSet(89/*DRV_IO_SPI0_GPIO3*/,1);
            //Configure GPIO nNum as output PIN
            DrvGPIOOutputEnable(89/*DRV_IO_SPI0_GPIO3*/,1);
            //Set GPIO nNum to High
            DrvGPIOSetOutputData(89/*DRV_IO_SPI0_GPIO3*/,1);

            MMPS_AUI_StartWAVPlay();
            //Component_AudDec_CloseDevice((void *)&Component_AUD_Decode[AUDDEC_COMPONENT_PLAYBACK]);
            Component_AudDec_UnInitDevice((void *)&Component_AUD_Decode[AUDDEC_COMPONENT_PLAYBACK]);
            break;
        }
    default:
        break;
    }
#endif
    return MMP_ERR_NONE;
}
