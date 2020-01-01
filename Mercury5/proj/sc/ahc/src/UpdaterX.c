
//==============================================================================
//
//  File        : dsc_Charger.c
//  Description : 
//  Author      : Mark Chang
//  Revision    : 1.0
//
//==============================================================================
#include "UpdaterX.h"
#include "mmpf_typedef.h"
#include "ait_utility.h"
#include "mmpf_storage_api.h"
#include "SD_Updater.h"
#include "lib_retina.h"

#define UPDATER_DEBUG (0)

#define TEMP_BUF_LENGTH (0x200)//512

#if (UPDATERX_ENABLE)

FW_UPDATER_LOG m_sLog;

extern void MMPF_MMU_FlushDCache(void);

static UPDATERX_ERR UpdaterX_CheckFWBin(void)
{
    MMP_ERR eError;
    MMP_ULONG uiFileID;
    
    eError = MMPS_FS_FileOpen(SD_FW_UPDATER_BIN_NAME, 
                 STRLEN(SD_FW_UPDATER_BIN_NAME),
                 "rb", 
                 STRLEN("rb"), 
                 &uiFileID);
    
    if(eError == MMP_ERR_NONE){
    
        MMPS_FS_FileClose(uiFileID);
    
        return UPDATERX_ERR_EXISTED_FW;
        
    }else{
    
        return UPDATERX_ERR_NO_FW;
    }
}

static UPDATERX_ERR UpdaterX_CheckUpdaterLog(void)
{
    MMP_ERR eError;
    MMP_ULONG uiFileID;
    
    eError = MMPS_FS_FileOpen(SD_FW_UPDATER_LOG_NAME, 
                 STRLEN(SD_FW_UPDATER_LOG_NAME),
                 "rb", 
                 STRLEN("rb"), 
                 &uiFileID);
    
    if(eError == MMP_ERR_NONE){
    
        MMPS_FS_FileClose(uiFileID);
    
        return UPDATERX_ERR_EXISTED_LOG;
        
    }else{
    
        return UPDATERX_ERR_NO_LOG;
    }
}

UPDATERX_ERR UpdaterX_ShowLog(FW_UPDATER_LOG* psLog)
{
    RTNA_DBG_Str(0, "eExtraBootloaderX : ");
    RTNA_DBG_Long(0, psLog->eExtraBootloaderX);
    RTNA_DBG_Str(0, "\r\n");
    
    RTNA_DBG_Str(0, "eExtraALLFW : ");
    RTNA_DBG_Long(0, psLog->eExtraALLFW);
    RTNA_DBG_Str(0, "\r\n");
    
    RTNA_DBG_Str(0, "eBootloaderX : ");
    RTNA_DBG_Long(0, psLog->eBootloaderX);
    RTNA_DBG_Str(0, "\r\n");
    
    RTNA_DBG_Str(0, "eALLFW : ");
    RTNA_DBG_Long(0, psLog->eALLFW);
    RTNA_DBG_Str(0, "\r\n");
    
    return UPDATERX_ERR_NONE;
}

UPDATERX_ERR UpdaterX_DeleteLog(void)
{
    #if (UPDATER_DEBUG)
    RTNA_DBG_Str(0, "UpdaterX_DeleteLog\r\n");
    
    UpdaterX_ShowLog(&m_sLog);
    #endif
    
    if(MMPS_FS_FileRemove(SD_FW_UPDATER_LOG_NAME, STRLEN(SD_FW_UPDATER_LOG_NAME)) == MMP_ERR_NONE){
        return UPDATERX_ERR_NONE;
        
    }else{
        return UPDATERX_ERR_DEL_LOG_FAIL;
    }
}

static UPDATERX_ERR UpdaterX_SaveLog(FW_UPDATER_LOG* psLog)
{

    MMP_ULONG uiFileID;
    MMP_ERR eError;
    MMP_ULONG uiWriteCount;
    
    #if (UPDATER_DEBUG)
    RTNA_DBG_Str(0, "UpdaterX_SaveLog\r\n");
    #endif
    
    eError = MMPS_FS_FileOpen(  SD_FW_UPDATER_LOG_NAME, 
                                STRLEN(SD_FW_UPDATER_LOG_NAME),
                                "wb", 
                                STRLEN("wb"), 
                                &uiFileID);
    
    if(eError != MMP_ERR_NONE){
    
        return UPDATERX_ERR_NO_LOG;
    }
    
    if(MMPS_FS_FileWrite(uiFileID, (MMP_UBYTE*)psLog, sizeof(FW_UPDATER_LOG), &uiWriteCount) != MMP_ERR_NONE){
        MMPS_FS_FileClose(uiFileID);
        return UPDATERX_ERR_SAVE_LOG_FAIL;
    }
    
    
    if(sizeof(FW_UPDATER_LOG) != uiWriteCount){
        MMPS_FS_FileClose(uiFileID);
        return UPDATERX_ERR_SAVE_LOG_FAIL;
    }
    
    #if (UPDATER_DEBUG)
    UpdaterX_ShowLog(psLog);
    #endif
    
    MMPS_FS_FileClose(uiFileID);
    
    return UPDATERX_ERR_NONE;

}

static UPDATERX_ERR UpdaterX_LoadLog(FW_UPDATER_LOG* psLog)
{
    MMP_ULONG uiFileID;
    MMP_ERR eError;
    MMP_ULONG uiReadCount;
    
    #if (UPDATER_DEBUG)
    RTNA_DBG_Str(0, "UpdaterX_LoadLog\r\n");
    #endif
    
    eError = MMPS_FS_FileOpen(  SD_FW_UPDATER_LOG_NAME, 
                                STRLEN(SD_FW_UPDATER_LOG_NAME),
                                "rb", 
                                STRLEN("rb"), 
                                &uiFileID);
    
    if(eError != MMP_ERR_NONE){
    
        return UPDATERX_ERR_NO_LOG;
    }
    
    if(MMPS_FS_FileRead(uiFileID, (MMP_UBYTE*)psLog, sizeof(FW_UPDATER_LOG), &uiReadCount) != MMP_ERR_NONE){
        MMPS_FS_FileClose(uiFileID);
        return UPDATERX_ERR_LOAD_LOG_FAIL;
    }
    
    
    if(sizeof(FW_UPDATER_LOG) != uiReadCount){
        MMPS_FS_FileClose(uiFileID);
        return UPDATERX_ERR_LOAD_LOG_FAIL;
    }
    
    #if (UPDATER_DEBUG)
    UpdaterX_ShowLog(psLog);
    #endif
    
    MMPS_FS_FileClose(uiFileID);
    
    return UPDATERX_ERR_NONE;
    

}

static UPDATERX_ERR UpdaterX_CheckBootloader(void)
{    

    #if (UPDATER_DEBUG)
    RTNA_DBG_Str(0, "UpdaterX_CheckBootloader Start \r\n");
    #endif
    
    if(UpdaterX_CheckFWBin() == UPDATERX_ERR_NO_FW){
        /**
        There is no fw bin in the storage.
        */    
        return UPDATERX_ERR_ORIGINAL_BOOT;
    }
    /**
    
    Simplify the handler.
    */
    return UPDATERX_ERR_EXTRA_BOOT;
    
    
    
    if(UpdaterX_CheckUpdaterLog() == UPDATERX_ERR_NO_LOG){
    
        m_sLog.eUpdateProcess = FW_UPDATE_PROCESS_VERIFYING;
        m_sLog.eExtraBootloaderX = FW_UPDATER_STAGE_LOAD;
        m_sLog.eExtraALLFW       = FW_UPDATER_STAGE_NONE;
        m_sLog.eBootloaderX      = FW_UPDATER_STAGE_NONE;
        m_sLog.eALLFW            = FW_UPDATER_STAGE_NONE;
        
        UpdaterX_SaveLog(&m_sLog);
        
        return UPDATERX_ERR_EXTRA_BOOT;
    }
    
    if(UpdaterX_LoadLog(&m_sLog) != UPDATERX_ERR_NONE){
    
        UpdaterX_DeleteLog();
        m_sLog.eUpdateProcess = FW_UPDATE_PROCESS_VERIFYING;
        m_sLog.eExtraBootloaderX = FW_UPDATER_STAGE_LOAD;
        m_sLog.eExtraALLFW       = FW_UPDATER_STAGE_NONE;
        m_sLog.eBootloaderX      = FW_UPDATER_STAGE_NONE;
        m_sLog.eALLFW            = FW_UPDATER_STAGE_NONE;
        UpdaterX_SaveLog(&m_sLog);
        
        return UPDATERX_ERR_EXTRA_BOOT;
    
    }

    if( m_sLog.eUpdateProcess == FW_UPDATE_PROCESS_VERIFIED) {
        
        m_sLog.eBootloaderX      = FW_UPDATER_STAGE_LOAD;
        UpdaterX_SaveLog(&m_sLog);
        
        return UPDATERX_ERR_ORIGINAL_BOOT;
    }
    
    #if (UPDATER_DEBUG)
    RTNA_DBG_Str(0, "UpdaterX_CheckBootloader Fail \r\n");
    
    UpdaterX_ShowLog(&m_sLog);
    #endif
    
    
    
    return UPDATERX_ERR_ORIGINAL_BOOT;
}

static UPDATERX_ERR UpdaterX_CheckBootloaderX(void)
{
    #if (UPDATER_DEBUG)
    RTNA_DBG_Str(0, "UpdaterX_CheckBootloaderX Start \r\n");
    #endif
    
    if(UpdaterX_CheckFWBin() == UPDATERX_ERR_NO_FW){
        /**
        There is no fw bin in the storage.
        */    
        return UPDATERX_ERR_ORIGINAL_BOOT;
    }
    /**
    
    Simplify the handler.
    */
    return UPDATERX_ERR_EXTRA_BOOT;
    
    
    if(UpdaterX_CheckUpdaterLog() == UPDATERX_ERR_NO_LOG){
        /**
        There is no log in the storage.
        */    
        
        return UPDATERX_ERR_ORIGINAL_BOOT;
    }
    
    if(UpdaterX_LoadLog(&m_sLog) != UPDATERX_ERR_NONE){

        return UPDATERX_ERR_SHUT_DOWN;
    
    }
    
    if( m_sLog.eUpdateProcess == FW_UPDATE_PROCESS_VERIFYING ){
        
        m_sLog.eExtraBootloaderX = FW_UPDATER_STAGE_SUCCESS;
        
        UpdaterX_SaveLog(&m_sLog);
        
        return UPDATERX_ERR_EXTRA_BOOT;
    }
    
    if( m_sLog.eUpdateProcess == FW_UPDATE_PROCESS_VERIFIED ){
        
        m_sLog.eBootloaderX = FW_UPDATER_STAGE_SUCCESS;
        m_sLog.eALLFW       = FW_UPDATER_STAGE_LOAD;
        
        UpdaterX_SaveLog(&m_sLog);
        
        return UPDATERX_ERR_ORIGINAL_BOOT;
    }
    

    #if (UPDATER_DEBUG)
    RTNA_DBG_Str(0, "UpdaterX_CheckBootloaderX Fail \r\n");
    
    UpdaterX_ShowLog(&m_sLog);
    #endif
    
    return UPDATERX_ERR_SHUT_DOWN;

}

static UPDATERX_ERR UpdaterX_CheckALLFW(void)
{
    #if (UPDATER_DEBUG)
    RTNA_DBG_Str(0, "UpdaterX_CheckALLFW Start \r\n");
    #endif
    
    if(UpdaterX_CheckFWBin() == UPDATERX_ERR_NO_FW){
        /**
        There is no fw bin in the storage.
        */    
        return UPDATERX_ERR_NONE;
    }
    /**
    
    Simplify the handler.
    */
    return UPDATERX_ERR_UPDATE;
    
    if(UpdaterX_CheckUpdaterLog() == UPDATERX_ERR_NO_LOG){
        /**
        There is no log in the storage.
        */   
                 
        return UPDATERX_ERR_NONE;
    }
    
    if(UpdaterX_LoadLog(&m_sLog) != UPDATERX_ERR_NONE){
    
        UpdaterX_DeleteLog();

        return UPDATERX_ERR_NONE;
    
    }
    
    if( m_sLog.eUpdateProcess == FW_UPDATE_PROCESS_VERIFYING ){
        
        m_sLog.eExtraALLFW = FW_UPDATER_STAGE_SUCCESS;
        
        UpdaterX_SaveLog(&m_sLog);
        
        return UPDATERX_ERR_UPDATE;
    }
    
    if( m_sLog.eUpdateProcess == FW_UPDATE_PROCESS_VERIFIED ){
        
        m_sLog.eALLFW       = FW_UPDATER_STAGE_SUCCESS;
        
        UpdaterX_DeleteLog();

        return UPDATERX_ERR_DONE;
    }
    

    #if (UPDATER_DEBUG)
    RTNA_DBG_Str(0, "UpdaterX_CheckALLFW Fail \r\n");
    
    UpdaterX_ShowLog(&m_sLog);
    #endif
    
    return UPDATERX_ERR_SHUT_DOWN;

}

UPDATERX_ERR UpdaterX_CheckFlow(FW_TYPE eCurType)
{

    if(eCurType == FW_TYPE_BOOTLOADER){
    
        return UpdaterX_CheckBootloader();
        
    }else if(eCurType == FW_TYPE_BOOTLOADERX){
    
        return UpdaterX_CheckBootloaderX();
    
    }else if(eCurType == FW_TYPE_ALLFW){
    
        return UpdaterX_CheckALLFW();
    }
    
    return UPDATERX_ERR_SHUT_DOWN;
}


UPDATERX_ERR UpdaterX_GetExtraFWInfo(FW_TYPE eType, MMP_ULONG *puiPos, MMP_ULONG *puiSize)
{
    MMP_ULONG uiTempBuf[TEMP_BUF_LENGTH>>2];
    MMP_ERR eError;
    MMP_ULONG uiFileID, uiReadCount;
    MMP_ULONG i;    
    MMP_ULONG uiFilePos;
    
    
    AIT_STORAGE_INDEX_TABLE* pIndexTable = (AIT_STORAGE_INDEX_TABLE *)uiTempBuf;
        
    eError = MMPS_FS_FileOpen(SD_FW_UPDATER_BIN_NAME, 
                 STRLEN(SD_FW_UPDATER_BIN_NAME),
                 "rb", 
                 STRLEN("rb"), 
                 &uiFileID);
                
    uiFilePos = sizeof(SDBIN)+MBR_OFFSET;
     
	MMPS_FS_FileSeek(uiFileID, uiFilePos, 0);	
		
	RTNA_DBG_Str(0,"Index Pos : ");
	RTNA_DBG_Long(0, uiFilePos);
	RTNA_DBG_Str(0,"\r\n");
			
	eError = MMPS_FS_FileRead(uiFileID, (MMP_UBYTE*)uiTempBuf, TEMP_BUF_LENGTH, &uiReadCount);

    #if 1
    for(i = 0; i < MAX_STORAGE_NUM; i++){

        if(pIndexTable->it[i].ulStartSec != 0xFFFFFFFF){
    		RTNA_DBG_Str(0,"PART : ");
    		RTNA_DBG_Long(0, i);
    		RTNA_DBG_Str(0,", \t");
    		RTNA_DBG_Str(0,"Start Address : ");
    		RTNA_DBG_Long(0,(pIndexTable->it[i].ulStartSec<<9));
    		RTNA_DBG_Str(0,", \t");
    		RTNA_DBG_Str(0,"Size : ");
    		RTNA_DBG_Long(0,(pIndexTable->it[i].ulSecSize<<9));
    		RTNA_DBG_Str(0,"\r\n");
		}
    }
    #endif
    
    if(eType == FW_TYPE_BOOTLOADERX){
        i = 1;
    }else if(eType == FW_TYPE_ALLFW){
        i = 2;
    }else{
        i = 1;
    }
    
	RTNA_DBG_Str(0,"LOAD PART : ");
	RTNA_DBG_Long(0, i);
	RTNA_DBG_Str(0,", \t");
	RTNA_DBG_Str(0,"Start Address : ");
	RTNA_DBG_Long(0,(pIndexTable->it[i].ulStartSec<<9));
	RTNA_DBG_Str(0,", \t");
	RTNA_DBG_Str(0,"Size : ");
	RTNA_DBG_Long(0,(pIndexTable->it[i].ulSecSize<<9));
	RTNA_DBG_Str(0,"\r\n");
	
    uiFilePos += ((pIndexTable->it[i].ulStartSec<<9) - (pIndexTable->it[0].ulStartSec<<9) + TEMP_BUF_LENGTH);
    *puiPos = uiFilePos;
    *puiSize = (pIndexTable->it[i].ulSecSize<<9);
    
    MMPS_FS_FileClose(uiFileID);
    
    return UPDATERX_ERR_NONE;
}

UPDATERX_ERR UpdaterX_LoadExtraFW(MMP_ULONG uiAddr, MMP_ULONG uiPos, MMP_ULONG uiSize)
{

    MMP_ERR eError;
    MMP_ULONG uiFileID, uiReadCount;
        
    eError = MMPS_FS_FileOpen(SD_FW_UPDATER_BIN_NAME, 
                 STRLEN(SD_FW_UPDATER_BIN_NAME),
                 "rb", 
                 STRLEN("rb"), 
                 &uiFileID);
     
	MMPS_FS_FileSeek(uiFileID, uiPos, 0);
	
	eError = MMPS_FS_FileRead(uiFileID, (MMP_UBYTE*)uiAddr, uiSize, &uiReadCount);
	
    MMPS_FS_FileClose(uiFileID);
    
    MMPF_MMU_FlushDCache();
    
    return UPDATERX_ERR_NONE;
}

#endif///< #if (UPDATERX_ENABLE)