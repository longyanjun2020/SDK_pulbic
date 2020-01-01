#if 0
void __HEADER__(){}
#endif
/*===========================================================================
 * Include file 
 *===========================================================================*/ 
 
#include "ahc_fs.h"
//#include "ahc_general.h"
#include "ahc_parameter.h"
//#include "ahc_message.h"
//#include "ahc_menu.h"
#include "ahc_video.h"
#include "aihc_deletion.h"
//#include "ahc_version.h"
#include "ahc_media.h"
//#include "ahc_utility.h"
#include "ahc_uf.h"
//#include "aihc_dcf.h"
//#include "ahc_dcf.h"
//#include "ait_utility.h"

//#include "statevideofunc.h"
/*===========================================================================
 * Main body
 *===========================================================================*/

#define USE_DIR_BUFFER (1)

#if (USE_DIR_BUFFER)
#define VIDEO_DIR_BUFFER_SIZE    (500*1024*1024)
#define STILL_DIR_BUFFER_SIZE    (10*1024*1024)
#define MAX_NMEA_TOTAL_SIZE      (20*1024*1024)  
#endif

static AHC_BOOL AHC_Deletion_Remove_CarDV(AHC_BOOL bFirstTime)
{
	#define CHECK_CROSS_LINK	(0)

 	AHC_BOOL			ahc_ret = AHC_TRUE;
   	UINT32				MaxObjIdx		= 0;
    UINT32      		CurObjIdx		= 0;

	char                FilePathName[MAX_FULL_FILENAME_SIZE];
	AHC_BOOL            bReadOnly;
	AHC_BOOL            bProtectFile;
	UINT32              FileSize;
	
    UINT32      		StrLen;
    INT8       			DirName[32],FileName[32];
    UINT64      		ulFreeSpace 	= 0;
	UINT32 				ulAudBitRate 	= 128000;//128K
    UINT32      		ulVidBitRate	= 0;
	UINT32				ulTimelimit		= 0;
	UINT64      		ulSpaceNeeded 	= 0;
	UINT32				InitObjIdx 		= 0;
	INT16               DirLenCnt       = 0;
#if (CHECK_CROSS_LINK)	
	UINT64				ulFreeSpace1	= 0;
	UINT32				ulCluseterSize	= 0;
	AHC_FS_DISK_INFO 	volinfo;
		
	AHC_FS_GetVolumeInfo("SD:\\", strlen("SD:\\"), &volinfo);
	
	ulCluseterSize = (volinfo.usBytesPerSector)*(volinfo.usSecPerCluster);	
#endif	
	
	AHC_UF_SetFreeChar(0,DCF_SET_ALLOWED,(UINT8*)SEARCH_MOVIE);

	AHC_VIDEO_GetMovieCfg(AHC_VIDEO_USAGE_RECD, AHC_VIDEO_BITRATE, &ulVidBitRate); 
		
	ulTimelimit = AHC_VIDEO_GetRecTimeLimitEx();
		
	if(ulTimelimit==NON_CYCLING_TIME_LIMIT)
	{
		ulSpaceNeeded = 0x24000000;/* 576MB */
	}
	else
	{
        AHC_VIDEO_GetRecStorageSpaceNeed(ulVidBitRate, ulAudBitRate, ulTimelimit, &ulSpaceNeeded);
	
		if(bFirstTime)
			ulSpaceNeeded *= 2;
	}

    printc("Min free space %dMB is need\r\n", ulSpaceNeeded >> 20);

	#if (!CHECK_CROSS_LINK)
	AHC_Media_GetFreeSpace(&ulFreeSpace);
	#endif	
		
	do {
	
		#if (CHECK_CROSS_LINK)
		AHC_Media_GetFreeSpace(&ulFreeSpace);
		#endif
		
        printc("SD ulFreeSpace = %d KB\r\n",(ulFreeSpace>>10));
		
		if( ulFreeSpace >= ulSpaceNeeded )
		{
			printc(FG_BLUE("FreeSpace is Enough [SpaceNeeded %d KB]\r\n"),(ulSpaceNeeded>>10));
			return AHC_TRUE;
		}
		
	   	AHC_UF_GetTotalFileCount(&MaxObjIdx);

		if(MaxObjIdx == 0)
		{
			printc(FG_RED("No More DCF File for Delete!\r\n"));
			return AHC_FALSE;
		}
		
		if(InitObjIdx>=MaxObjIdx)
		{
			printc(FG_RED("All %d File Can't Delete!!\r\n"), MaxObjIdx);
			return AHC_FALSE;
		}
		
		AHC_UF_SetCurrentIndex(InitObjIdx); 
		AHC_UF_GetCurrentIndex(&CurObjIdx);

		MEMSET(FilePathName, 0, sizeof(FilePathName));
		if(AHC_FALSE == AHC_UF_GetFilePathNamebyIndex(CurObjIdx, FilePathName)) 
		{
			printc(FG_RED("AHC_UF_GetFilePathNamebyIndex Error\r\n"));
			return AHC_FALSE;
		}
		if(AHC_FALSE == AHC_UF_IsReadOnlybyIndex(CurObjIdx, &bReadOnly)) 
		{
			printc(FG_RED("AHC_UF_IsReadOnlybyIndex Error\r\n"));
			return AHC_FALSE;
		}
		if(AHC_FALSE == AHC_UF_GetFileSizebyIndex(CurObjIdx, &FileSize)) 
		{
			printc(FG_RED("AHC_UF_GetFileSizebyIndex Error\r\n"));
			return AHC_FALSE;
		}
		if(AHC_FALSE == AHC_UF_IsCharLockbyIndex(CurObjIdx, &bProtectFile)) 
		{
			printc(FG_RED("AHC_UF_IsReadOnlybyIndex Error\r\n"));
			return AHC_FALSE;
		}

		if(bReadOnly || bProtectFile)//Read Only File or Protect file
		{
			InitObjIdx++;
			continue;
		}
		
		StrLen = strlen(FilePathName);
	    DirLenCnt = StrLen;
		
	    for(DirLenCnt=(StrLen-1);DirLenCnt>=0;)
	    {
	        if(FilePathName[DirLenCnt] == '\\')
	       	{
				break;
	       	}
		    DirLenCnt--;
	    }

		MEMSET(DirName, 0, sizeof(DirName));
		MEMCPY(DirName, FilePathName, DirLenCnt);

		MEMSET(FileName, 0, sizeof(FileName));
		MEMCPY(FileName, (INT8 *) &FilePathName[DirLenCnt + 1], StrLen - DirLenCnt - 1);

		printc("Delete Min Key File %s\\%s \r\n",DirName, FileName);

		ahc_ret = AHC_UF_FileOperation((UINT8*)DirName,(UINT8*)FileName, DCF_FILE_DELETE_ALL_CAM, NULL,NULL);

	    if(ahc_ret==AHC_FALSE)
	    {
	    	printc(FG_RED("AHC_UF_FileOperation Delete Error\r\n"));
	    	return AHC_FALSE;
	    }
	    else
	    {
	    	#if (CHECK_CROSS_LINK)
			AHC_Media_GetFreeSpace(&ulFreeSpace1);
			
			if( ((ulFreeSpace + FileSize - ulCluseterSize) < ulFreeSpace1) &&
				((ulFreeSpace + FileSize + ulCluseterSize) > ulFreeSpace1) )
				;//Check Pass
			else
			{	
				printc("FS Cross Link!!!!!\r\n");
				AHC_WMSG_Draw(AHC_TRUE, WMSG_FORMAT_SD_CARD, 3);
				return AHC_FALSE;
			}
			#else
	    	ulFreeSpace += FileSize;
	    	#endif
	    }
	    
    } while(1);
    
	return ahc_ret;
}


AHC_BOOL AHC_Deletion_Confirm(DCF_DB_TYPE sDB, UINT32 uiTime)
{

    UINT64      ulFreeSpace 	= 0;
	UINT64      ulSpaceNeeded 	= 0;
	DCF_DB_TYPE sCurDB;
    UINT32 		ulAudBitRate 	= 128000;//128K
    UINT32      ulVidBitRate	= 0;
	UINT32      ulSpaceNeededInClusters;

    #define DELETION_DEBUG (1)
    
	AHC_UF_SetFreeChar(0,DCF_SET_ALLOWED,(UINT8*)SEARCH_PHOTO_MOVIE);
	
	AHC_VIDEO_GetMovieCfg(AHC_VIDEO_USAGE_RECD, AHC_VIDEO_BITRATE, &ulVidBitRate); 

	AHC_VIDEO_GetRecStorageSpaceNeed(ulVidBitRate, ulAudBitRate, uiTime, &ulSpaceNeeded);

	sCurDB = AHC_UF_GetDB();
	AHC_UF_SelectDB(sDB);
	
    #if(defined(DEVICE_GPIO_2NDSD_PLUG))

	#if(TWOSD_WORK_MODEL == TWOSD_WORK_MODEL_MASTER_SLAVE)
	if(AHC_IsSDInserted() && AHC_GetMountStorageMediaStatus() && AHC_SDMMC_IsSD1MountDCF() /*or AHC_SDMMC_IsSD2MountDCF???*/) 
	#elif(TWOSD_WORK_MODEL == TWOSD_WORK_MODEL_COMPLEMENTARY)
	if ( (AHC_IsSDInserted() || AHC_Is2ndSDInserted()) && AHC_GetMountStorageMediaStatus() && AHC_SDMMC_IsSD1MountDCF() /*or AHC_SDMMC_IsSD2MountDCF???*/)
	#endif
						
	#else//DEVICE_GPIO_2NDSD_PLUG
	if(AHC_IsSDInserted() && AHC_GetMountStorageMediaStatus() && AHC_SDMMC_IsSD1MountDCF() /*or AHC_SDMMC_IsSD2MountDCF???*/) 
	#endif//DEVICE_GPIO_2NDSD_PLUG
    {
		AHC_UF_UpdateLastFiles(sDB);
	}
	
    /**
    The original folder has enough space to be deleted.
    */
#if (USE_DIR_BUFFER)
    
    if( sDB == DCF_DB_TYPE_DB3_PHOTO )
    {
        ulSpaceNeededInClusters = STILL_DIR_BUFFER_SIZE /AHC_UF_GetClusterSize(sDB); 
    }
    else
    {
        ulSpaceNeededInClusters = ulSpaceNeeded /AHC_UF_GetClusterSize(sDB);
    }

    ulSpaceNeeded = ulSpaceNeededInClusters * AHC_UF_GetClusterSize(sDB);

    if( AHC_UF_GetFileCluster(sDB)+ ulSpaceNeededInClusters > AHC_UF_GetClusterTH(sDB) )
#else

    if(AHC_UF_GetFileCluster(sDB) > AHC_UF_GetClusterTH(sDB))
#endif		
	{
	    AHC_UF_SelectDB(sCurDB);
        return AHC_FALSE;        
    }

    AHC_Media_GetFreeSpace(&ulFreeSpace);

	AHC_UF_SelectDB(sCurDB);
	
	if( ulFreeSpace >= ulSpaceNeeded )
	{
        return AHC_TRUE;
        
    }else{
        return AHC_FALSE;
    }

}

AHC_BOOL AHC_Deletion_ConfirmByNum(DCF_DB_TYPE sDB, UINT32 uiTime)
{
	UINT64      ulFreeSpace 	= 0;
	UINT64      ulSpaceNeeded 	= 0;
	DCF_DB_TYPE sCurDB;
    UINT32 		ulAudBitRate 	= 128000;//128K
    UINT32      ulVidBitRate	= 0;
  	UINT32		FileCount[4];
  	  
	AHC_UF_SetFreeChar(0,DCF_SET_ALLOWED,(UINT8*)SEARCH_PHOTO_MOVIE);

	AHC_VIDEO_GetMovieCfg(AHC_VIDEO_USAGE_RECD, AHC_VIDEO_BITRATE, &ulVidBitRate); 

	AHC_VIDEO_GetRecStorageSpaceNeed(ulVidBitRate, ulAudBitRate, uiTime, &ulSpaceNeeded);
	
	sCurDB = AHC_UF_GetDB();
	
	
    #if(defined(DEVICE_GPIO_2NDSD_PLUG))

	#if(TWOSD_WORK_MODEL == TWOSD_WORK_MODEL_MASTER_SLAVE)
	if(AHC_IsSDInserted() && AHC_GetMountStorageMediaStatus() && AHC_SDMMC_IsSD1MountDCF() /*or AHC_SDMMC_IsSD2MountDCF???*/) 
	#elif(TWOSD_WORK_MODEL == TWOSD_WORK_MODEL_COMPLEMENTARY)
	if ( (AHC_IsSDInserted() || AHC_Is2ndSDInserted()) && AHC_GetMountStorageMediaStatus() && AHC_SDMMC_IsSD1MountDCF() /*or AHC_SDMMC_IsSD2MountDCF???*/)
	#endif
						
	#else//DEVICE_GPIO_2NDSD_PLUG
	if(AHC_IsSDInserted() && AHC_GetMountStorageMediaStatus() && AHC_SDMMC_IsSD1MountDCF() /*or AHC_SDMMC_IsSD2MountDCF???*/) 
	#endif//DEVICE_GPIO_2NDSD_PLUG
    {
		AHC_UF_UpdateLastFiles(sDB);
	}
	
    AHC_UF_SelectDB(sDB);
	AHC_UF_GetTotalFileCount(&FileCount[sDB]);
    
    AHC_UF_SelectDB(sCurDB);
    
    if(sDB == DCF_DB_TYPE_DB2_EVENT)
    {
    	if(FileCount[DCF_DB_TYPE_DB2_EVENT] >= AHC_UF_GetFileTH(DCF_DB_TYPE_DB2_EVENT))
    	{
    		printc("Emer_File count is over threshold\r\n");
	   		return AHC_FALSE;
    	}
    }
       
    if(FileCount[sDB] > AHC_UF_GetFileTH(sDB))
	{   	
	   	printc("File count is over threshold\r\n");
	   	return AHC_FALSE;
	}else
	{
		AHC_Media_GetFreeSpace(&ulFreeSpace);
		if( ulFreeSpace >= ulSpaceNeeded )
		{
			printc("Space available\r\n");
			return AHC_TRUE;	
		}else
		{
			printc("File count is enougth, but no freespace\r\n");
			return AHC_FALSE;
		}
		
	}
   
	AHC_UF_SelectDB(sCurDB);
	
	if( ulFreeSpace >= ulSpaceNeeded )
	{
        return AHC_TRUE;
        
    }else{
        return AHC_FALSE;
    }
}

AHC_BOOL AHC_Deletion_RemoveEx(DCF_DB_TYPE sDB, UINT32 uiTime)
{

 	AHC_BOOL	uiResult        = AHC_FALSE;
    UINT64      ulFreeSpace 	= 0;
	UINT64      ulSpaceNeeded 	= 0;
    DCF_DB_TYPE sCurDB;
    UINT32 		ulAudBitRate 	= 128000;//128K
    UINT32      ulVidBitRate	= 0;
    UINT32      i;
	UINT32      ulSpaceNeededInClusters; 

    #define DELETION_DEBUG (1)

    #if (FS_FORMAT_FREE_ENABLE)
    return AHC_TRUE;      //For Format Free, we don't need to check if free space is enough or not
    #endif
    
	AHC_UF_SetFreeChar(0,DCF_SET_ALLOWED,(UINT8*)SEARCH_PHOTO_MOVIE);
	
	AHC_VIDEO_GetMovieCfg(AHC_VIDEO_USAGE_RECD, AHC_VIDEO_BITRATE, &ulVidBitRate); 

#if (defined(VIDEO_REC_TIMELAPSE_EN) && VIDEO_REC_TIMELAPSE_EN)
    {
        int slVRTimelapse;
        if ((AHC_Menu_SettingGetCB(COMMON_KEY_VR_TIMELAPSE, &slVRTimelapse) == AHC_TRUE) && (slVRTimelapse != PRJ_VR_TIMELAPSE_OFF)){
            UINT32      Framerate, Frate;

            AHC_VIDEO_GetMovieCfg(AHC_VIDEO_USAGE_RECD, AHC_FRAME_RATE, &Frate);
            Framerate = AHC_VIDEO_GetVideoRealFpsX1000(Frate) / AHC_VIDRECD_TIME_INCREMENT_BASE;
            AHC_VIDEO_GetTimeLapseBitrate(Framerate, slVRTimelapse, &ulVidBitRate, &ulAudBitRate);
        }
    }
#endif

	AHC_VIDEO_GetRecStorageSpaceNeed(ulVidBitRate, ulAudBitRate, uiTime, &ulSpaceNeeded);
	
    sCurDB = AHC_UF_GetDB();
	AHC_UF_SelectDB(sDB);
#if (DELETION_BY_FILE_NUM)
    //Add check for delete file by num 
    {
        UINT32 uiDeleteNum = 0;
        UINT32 FileCount   = 0;
        AHC_UF_GetTotalFileCount(&FileCount);
        if(FileCount >= AHC_UF_GetFileTH(sDB))
    	{
    		uiDeleteNum  = FileCount - AHC_UF_GetFileTH(sDB) + 1;
		    if(AHC_UF_DeleteFilebyNum(uiDeleteNum) == AHC_TRUE)
            {
		        //uiResult = AHC_TRUE;
		    }
    	}
    }
#endif
    /**
    The original folder has enough space to be deleted.
    */
#if (USE_DIR_BUFFER)
    
    if( sDB == DCF_DB_TYPE_DB3_PHOTO )
    {
        ulSpaceNeededInClusters = STILL_DIR_BUFFER_SIZE /AHC_UF_GetClusterSize(sDB); 
    }
    else
    {
        ulSpaceNeededInClusters = ulSpaceNeeded /AHC_UF_GetClusterSize(sDB);
    }

    ulSpaceNeeded = ulSpaceNeededInClusters * AHC_UF_GetClusterSize(sDB);

    if( AHC_UF_GetFileCluster(sDB)+ ulSpaceNeededInClusters > AHC_UF_GetClusterTH(sDB) )
#else
    if(AHC_UF_GetFileCluster(sDB) > AHC_UF_GetClusterTH(sDB))
#endif
	{
        UINT32 uiSpaceToDelete;

        #if DELETION_DEBUG
        //printc("DeletionEx 0x1 \n");
        #endif
        
        //AHC_UF_SelectDB(sDB);

		if( AHC_UF_GetFileCluster(sDB) > AHC_UF_GetClusterTH(sDB) )
        {
            // file size is over threshold
            ulSpaceNeededInClusters += ( AHC_UF_GetFileCluster(sDB) - AHC_UF_GetClusterTH(sDB) );
        }
        else
        {
            ulSpaceNeededInClusters -=  (AHC_UF_GetClusterTH(sDB) - AHC_UF_GetFileCluster(sDB));
        }

        uiSpaceToDelete = ulSpaceNeededInClusters * AHC_UF_GetClusterSize(sDB);

#if 0
        if(sDB == DCF_DB_TYPE_DB3_PHOTO){
            UINT16 uwBytesPerSec;
            UINT16 uwSecPerCluster;
            UINT32 uiTotalCluster;
            UINT32 uiFreelCluster;
            
            AHC_GetStorageMediaGeometry(&uwBytesPerSec, &uwSecPerCluster, &uiTotalCluster, &uiFreelCluster);
            //printc("PIC Cluster0 : %d \n", AHC_UF_GetFileCluster(sDB));
            //printc("PIC Cluster1 : %d \n", AHC_UF_GetClusterTH(sDB));
            //printc("PIC Cluster2 : %d \n", ulStillDirBufferClusterNum);
            
            ulSpaceNeeded = AHC_UF_GetFileCluster(sDB) - AHC_UF_GetClusterTH(sDB) + ulStillDirBufferClusterNum;
            //printc("PIC Cluster : %d \n", ulSpaceNeeded);
            ulSpaceNeeded = ulSpaceNeeded*uwBytesPerSec*uwSecPerCluster;
            //printc("PIC Byte : %d \n", ulSpaceNeeded);
    
        }
#endif

        if(AHC_UF_DeleteCyclicFilebySize(uiSpaceToDelete) == AHC_TRUE){
            uiResult = AHC_TRUE;
            goto Final;
        }
    }

    AHC_Media_GetFreeSpace(&ulFreeSpace);
    
	if( ulFreeSpace >= ulSpaceNeeded )
	{
        #if DELETION_DEBUG
        //printc("DeletionEx 0x2 \n");
        #endif
        uiResult = AHC_TRUE;
        goto Final;
        
    }else{
    
        #if DELETION_DEBUG
        //printc("DeletionEx 0x3 \n");
        #endif

		#if 1
		i = DCF_DB_TYPE_DB0_NORMAL;
		#else
        for(i = DCF_DB_TYPE_DB0_NORMAL; i < DCF_DB_TYPE_MAX_NUMBER; i++)
		#endif	
		{
        
            #if DELETION_DEBUG
            //printc("DeletionEx 0x4 : %d \n", i);
            #endif
            
            AHC_Media_GetFreeSpace(&ulFreeSpace);
            
            AHC_UF_SelectDB(i);
            
            if( ulFreeSpace >= ulSpaceNeeded ){
                    goto Final;            
            }else{
            
                if(AHC_UF_DeleteCyclicFilebySize(ulSpaceNeeded) == AHC_TRUE){
                    uiResult = AHC_TRUE;
                    goto Final;
                }
            }        
        }
    }
	
Final:
    
    AHC_UF_SelectDB(sCurDB);
	
	return uiResult;
}

AHC_BOOL AHC_Deletion_Romove_Before(AHC_BOOL bFirstTime)
{
    return AHC_TRUE;
}
AHC_BOOL AHC_Deletion_Romove(AHC_BOOL bFirstTime)
{
    if(DCF_DB_COUNT>=2)
    {
        return AHC_Deletion_RemoveEx(DCF_DB_TYPE_DB0_NORMAL, AHC_VIDEO_GetRecTimeLimitEx());
    }
    else
    {
        return AHC_Deletion_Remove_CarDV(bFirstTime);
    }
}

