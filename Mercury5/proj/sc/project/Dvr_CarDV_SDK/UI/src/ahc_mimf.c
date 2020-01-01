//==============================================================================
/**
 @file AHC_MIMF.c
 @brief Middleware of Index Mapping Functions
 @author Jerry Li
 @version 1.0
*/
/*===========================================================================
 * Include files
 *===========================================================================*/
#include "ahc_fs.h"
#include "ahc_uf.h"
#include "ahc_dcf.h"
#include "ahc_dcfdt.h"
#include "ahc_macro.h"
#include "ahc_utility.h"
#include "ahc_mempoolfixedsize.h"

#if (MIMF_CUSTOMIZED_SORT_TYPE != MIMF_CUSTOMIZED_SORT_NONE)
UINT32 m_uiBrowserMask = 0x1f;
UINT32 m_uiBrowserFileTypeMask = 0x3;
UINT32 m_uiMIMFCurIndex[DCFDT_CAM_NUM] = {0};
AHC_BOOL m_bSetFastBrowse = AHC_TRUE;
//use for Multi DB browse
PSMEMPOOLFIXEDSIZE hMIMFFileNodeMemPool;
SMIMFBROWSEDB m_MIMFBrowseDB = {0};
UINT32 m_ulMIMFBaseAddr;
//do not set mask in browser mode
void AHC_MIMF_SetBrowserMask(UINT32 uiBrowserMask)
{
    m_uiBrowserMask = uiBrowserMask;
}

void AHC_MIMF_GetBrowserMask(UINT32 *puiBrowserMask)
{
    *puiBrowserMask = m_uiBrowserMask;
}

void AHC_MIMF_SetBrowserTypeMask(UINT32 uiBrowserMask)
{
    m_uiBrowserFileTypeMask = uiBrowserMask;
}

void AHC_MIMF_GetBrowserTypeMask(UINT32 *puiBrowserMask)
{
    *puiBrowserMask = m_uiBrowserFileTypeMask;
}

//customized function
//------------------------------------------------------------------------------
//  Function    : AHC_MIMF_GetTotalFileCount
//  Description : get total filecount in spec. DB which UI want to browse
//  param[out]  total file count
//  retval AHC_TRUE Success.
//------------------------------------------------------------------------------
AHC_BOOL AHC_MIMF_GetTotalFileCountByDb(UINT32 *puiImgIndex)
{
    UINT32 uiFileCount = 0; 
    UINT32 uiCurTotalFileCount = 0;
    UINT32 i;
    UINT32 ret;
    UINT32 uiCurDB;
    
    uiCurDB = AHC_DCFDT_GetDB();
    if(m_uiBrowserMask == AHC_MIMF_BROWSER_MASK_REAR_CAM){
        printc("Not support only rear cam browser!!\r\n");
    }

    for( i = DCF_DB_TYPE_DB0_NORMAL; i < DCF_DB_COUNT; i++)
    {
        if(m_uiBrowserMask & (0x01 << i))
        {
            AHC_DCFDT_SelectDB(i);
            ret = AHC_DCFDT_GetTotalFileCountByCurrCamID(&uiFileCount);
            uiCurTotalFileCount += uiFileCount;
            if(ret == AHC_FALSE){
                printc("%s,%d  return False\r\n",__func__, __LINE__);
                return AHC_FALSE;
            }
            if(m_uiBrowserMask & AHC_MIMF_BROWSER_MASK_REAR_CAM)
            {
                ret = AHC_DCFDT_GetTotalFileCountByCurrCamID(&uiFileCount);
                uiCurTotalFileCount += uiFileCount;
                if(ret == AHC_FALSE){
                    printc("%s,%d  return False\r\n",__func__, __LINE__);
                    return AHC_FALSE;
                }
            }
        }
    }
    
    *puiImgIndex = uiCurTotalFileCount;
    AHC_DCFDT_SelectDB(uiCurDB);
    return AHC_TRUE;
}


AHC_BOOL AHC_MIMF_GetTotalFileCountByType(UINT32 *puiImgIndex)
{
    UINT32 uiFileCount = 0; 
    UINT32 uiCurTotalFileCount = 0;
    UINT32 i,j;
    UINT32 ret;
    UINT32 uiCurDB;
    AHC_BOOL bCurRearCam;
	UINT8 ubFileType;
	
    uiCurDB = AHC_DCFDT_GetDB();
    if(m_uiBrowserMask == AHC_MIMF_BROWSER_MASK_REAR_CAM){
        printc("Not support only rear cam browser!!\r\n");
    }

	i = DCF_DB_TYPE_DB0_NORMAL;
    {
        {
            AHC_DCFDT_SelectDB(i);
            ret = AHC_DCFDT_GetTotalFileCountByCurrCamID(&uiFileCount);
            //uiCurTotalFileCount += uiFileCount;
            if(ret == AHC_FALSE){
                printc("%s,%d  return False\r\n",__func__, __LINE__);
                return AHC_FALSE;
            }

			//
			for(j=0;j<uiFileCount;j++)
			{
				ret = AHC_DCFDT_GetFileTypebyIndex(j, &ubFileType);
				if((m_uiBrowserFileTypeMask & AHC_MIMF_BROWSER_MASK_MOV) &&
					( ( ubFileType == DCF_OBG_MOV ) ||
                      ( ubFileType == DCF_OBG_MP4 ) ||
                      ( ubFileType == DCF_OBG_AVI ) ||
                      ( ubFileType == DCF_OBG_3GP ) ||
                      ( ubFileType == DCF_OBG_TS  ) ||
                      ( ubFileType == DCF_OBG_WMV ) ))
				{
					uiCurTotalFileCount++;
				}
				else if((m_uiBrowserFileTypeMask & AHC_MIMF_BROWSER_MASK_JPG) &&
					( ubFileType == DCF_OBG_JPG ))
				{
					uiCurTotalFileCount++;
				}
			}

            if(m_uiBrowserMask & AHC_MIMF_BROWSER_MASK_REAR_CAM)
            {
                //ret = AHC_DCFDT_GetTotalRearFileCount(&uiFileCount);
				ret = AHC_DCFDT_GetTotalFileCountByCurrCamID(&uiFileCount);//Files in folder "F" more than folder "R" always.
                if(ret == AHC_FALSE){
                    printc("%s,%d  return False\r\n",__func__, __LINE__);
                    return AHC_FALSE;
                }

				AHC_DCFDT_GetRearCamPathFlag(&bCurRearCam);
        		AHC_DCFDT_SetRearCamPathFlag(AHC_TRUE);

				for(j=0;j<uiFileCount;j++)
				{
					ret = AHC_DCFDT_GetFileTypebyIndex(j, &ubFileType);
					if((m_uiBrowserFileTypeMask & AHC_MIMF_BROWSER_MASK_MOV) &&
						( ( ubFileType == DCF_OBG_MOV ) ||
	                      ( ubFileType == DCF_OBG_MP4 ) ||
	                      ( ubFileType == DCF_OBG_AVI ) ||
	                      ( ubFileType == DCF_OBG_3GP ) ||
                          ( ubFileType == DCF_OBG_TS  ) ||
	                      ( ubFileType == DCF_OBG_WMV ) ))
					{
						uiCurTotalFileCount++;
					}
					else if((m_uiBrowserFileTypeMask & AHC_MIMF_BROWSER_MASK_JPG) &&
						( ubFileType == DCF_OBG_JPG ))
					{
						uiCurTotalFileCount++;
					}
				}

				AHC_DCFDT_SetRearCamPathFlag(bCurRearCam);
            }
        }
    }
    
    *puiImgIndex = uiCurTotalFileCount;
    AHC_DCFDT_SelectDB(uiCurDB);
    return AHC_TRUE;
}

AHC_BOOL AHC_MIMF_GetTotalFileCount(UINT32 *puiImgIndex)
{
#if (MIMF_CUSTOMIZED_SORT_TYPE == MIMF_CUSTOMIZED_SORT_FILETYPE)
	return AHC_MIMF_GetTotalFileCountByDb(puiImgIndex);
#elif (MIMF_CUSTOMIZED_SORT_TYPE == MIMF_CUSTOMIZED_SORT_DECREASE)
    return AHC_DCFDT_GetTotalFileCountByCurrCamID(puiImgIndex);
#elif (MIMF_CUSTOMIZED_SORT_TYPE == MIMF_CUSTOMIZED_SORT_MULTI_DB_DECREASE)
    if(m_bSetFastBrowse){
        *puiImgIndex = m_MIMFBrowseDB.ulUFTotalFileNum;
    }
    else{
        AHC_DCFDT_GetTotalFileCountByCurrCamID(puiImgIndex);
    }
    return AHC_TRUE;
#else
	return AHC_FALSE; //Not implemented
#endif
    //disable it, because its not compatible for multicam DCFDT 
	//return AHC_MIMF_GetTotalFileCountByType(puiImgIndex);
}

//------------------------------------------------------------------------------
//  Function    : AHC_MIMF_IndexReverseMapping
//  Description : Thumb Index inverse mapping to dcf Index
//  param[in]  Thumb Index which from UF level
//  param[out] DCF Index in DB
//  param[out] DB type
//  param[out] IsRearCam
//  retval AHC_TRUE Success.
//------------------------------------------------------------------------------
AHC_BOOL AHC_MIMF_IndexReverseMappingByDB(UINT32 uiImgIndex, UINT32 *puiDcfIndex, UINT32 *sDB, AHC_BOOL *bIsRearCam)
{
    UINT32   i, j;
    UINT32   uiCurFileCount      = 0;  //filecount of current DB
    UINT32   uiRearFileCount     = 0;  //rear cam filecount of current DB
    UINT32   uiTotalCount        = 0;  //TotalCount of All DB
    UINT32   uiPreviousFileCount = 0;  //
    AHC_BOOL bRearCamEnable      = AHC_FALSE;
    UINT32   uiCurDB;
    UINT32   ret;
    AHC_BOOL bfound = AHC_FALSE;
    
    uiCurDB = AHC_DCFDT_GetDB();
    if(!AHC_MIMF_GetTotalFileCount(&uiTotalCount))
    {
        return AHC_FALSE;
    }
    if(uiImgIndex >= uiTotalCount)
    {
        printc("ImgIndex %d >= TotalCount %d %s\r\n", uiImgIndex, uiTotalCount, __func__);
        return AHC_FALSE;
    }
    if(m_uiBrowserMask == AHC_MIMF_BROWSER_MASK_REAR_CAM){
        printc("Not support only rear cam browser!!\r\n");
    }
    //check rearcam enable
    if(m_uiBrowserMask & AHC_MIMF_BROWSER_MASK_REAR_CAM){
        bRearCamEnable = AHC_TRUE;
    }

    for( i = DCF_DB_TYPE_DB0_NORMAL; i < DCF_DB_COUNT; i++)
    {
        if(bfound){
            break;
        }
        if(m_uiBrowserMask & (0x01 << i))
        {
            AHC_DCFDT_SelectDB(i);
            ret = AHC_DCFDT_GetTotalFileCountByCurrCamID(&uiCurFileCount);
            if(ret == AHC_FALSE){
                printc("%s,%d  return False\r\n",__func__, __LINE__);
                return AHC_FALSE;
            }
            if(bRearCamEnable){
                ret = AHC_DCFDT_GetTotalFileCountByCurrCamID(&uiRearFileCount);
                if(ret == AHC_FALSE){
                printc("%s,%d  return False\r\n",__func__, __LINE__);
                return AHC_FALSE;
                }
            }
            //if ImgIndex >= uiPreviousFileCount, Change to next DB
            uiPreviousFileCount += (uiCurFileCount + uiRearFileCount);
            if(uiImgIndex >= uiPreviousFileCount){
                continue;
            }else{   
                //find dcf Index in this DB 
                AHC_BOOL bRearFileExist;
                UINT32   uiFileCountPerNode = 1;
                INT32    iCounter = -1;
                INT32    iIndexInCurDB;
                //calculate Index in Current DB , iIndexInCurDB = index - (totalpreviousDBfilecount - curDBfilecount)  
                iIndexInCurDB = uiImgIndex - (uiPreviousFileCount - (uiCurFileCount + uiRearFileCount));
                //check if iIndexInCurDB out of range
                if(iIndexInCurDB < 0){
                    printc("uiImgIndex %d\r\n",uiImgIndex);
                    printc("uiPreviousFileCount %d\r\n",uiPreviousFileCount);
                    printc("uiCurFileCount %d\r\n",uiCurFileCount);
                    printc("uiRearFileCount %d\r\n",uiRearFileCount);
                    printc("Calculate Index error iIndexInCurDB %d %s\r\n", iIndexInCurDB, __func__);
                }
                //for each file node, find the Dcf Index 
                for( j = 0; j < (uiCurFileCount + uiRearFileCount); j++)
                {
                    //check filecount per node
                    if(bRearCamEnable)
                    {
                       // AHC_DCFDT_IsRearCamFileExistbyIndex( j, &bRearFileExist);
                        if(bRearFileExist){
                            uiFileCountPerNode = 2;
                        }else{
                            uiFileCountPerNode = 1;
                        }
                    }
                    iCounter += uiFileCountPerNode;
                    if(uiFileCountPerNode == 1)
                    {
                        //this node have only front cam file
                        if(iIndexInCurDB == iCounter)
                        {
                            *puiDcfIndex = j;
                            *sDB         = i;
                            *bIsRearCam  = AHC_FALSE;
                            bfound = AHC_TRUE;
                            break;
                        }
                    }else if(uiFileCountPerNode == 2)
                    {
                        //this node have both front/rear cam file
                        if(iIndexInCurDB == iCounter)
                        {
                            *puiDcfIndex = j;
                            *sDB         = i;
                            *bIsRearCam  = AHC_TRUE;
                            bfound = AHC_TRUE;
                            break;
                        }else if(iIndexInCurDB == (iCounter - 1))
                        {
                            *puiDcfIndex = j;
                            *sDB         = i;
                            *bIsRearCam  = AHC_FALSE;
                            bfound = AHC_TRUE;
                            break;
                        }
                    }                    
                }
            }            
        }
    }
    if(bfound == AHC_FALSE){
        printc("Error!!! IndexReverseMapping not found! %d %s\r\n", uiImgIndex, __func__);
    }
    AHC_DCFDT_SelectDB(uiCurDB);
    return bfound;
}

AHC_BOOL AHC_MIMF_IndexReverseMappingByFileType(UINT32 uiImgIndex, UINT32 *puiDcfIndex, UINT32 *sDB, AHC_BOOL *bIsRearCam)
{
    UINT32   i, j;
    UINT32   uiCurFileCount      = 0;  //filecount of current DB
    UINT32   uiRearFileCount     = 0;  //rear cam filecount of current DB
    UINT32   uiTotalCount        = 0;  //TotalCount of All DB
    AHC_BOOL bRearCamEnable      = AHC_FALSE;
    UINT32   uiCurDB;
    UINT32   ret;
    AHC_BOOL bfound = AHC_FALSE;
	AHC_BOOL bCurRearCam;
    UINT8	 ubFileType;
	UINT32	 uiCurTotalFileCount = 0;

	
    uiCurDB = AHC_DCFDT_GetDB();
    if(!AHC_MIMF_GetTotalFileCount(&uiTotalCount))
    {
        return AHC_FALSE;
    }
    if(uiImgIndex >= uiTotalCount)
    {
        printc("ImgIndex %d >= TotalCount %d %s\r\n", uiImgIndex, uiTotalCount, __func__);
        return AHC_FALSE;
    }
    if(m_uiBrowserMask == AHC_MIMF_BROWSER_MASK_REAR_CAM){
        printc("Not support only rear cam browser!!\r\n");
    }
	if(m_uiBrowserFileTypeMask == 0){
        printc("Not support, Must be set file type at first!!\r\n");
    }
	
    //check rearcam enable
    if(m_uiBrowserMask & AHC_MIMF_BROWSER_MASK_REAR_CAM){
        bRearCamEnable = AHC_TRUE;
    }

	i = DCF_DB_TYPE_DB0_NORMAL;
    {
        AHC_DCFDT_SelectDB(i);
        ret = AHC_DCFDT_GetTotalFileCountByCurrCamID(&uiCurFileCount);
        if(ret == AHC_FALSE){
            printc("%s,%d  return False\r\n",__func__, __LINE__);
            return AHC_FALSE;
        }

		for(j=0;j<uiCurFileCount;j++)
		{
			ret = AHC_DCFDT_GetFileTypebyIndex(j, &ubFileType);
			if((m_uiBrowserFileTypeMask & AHC_MIMF_BROWSER_MASK_MOV) &&
				( ( ubFileType == DCF_OBG_MOV ) ||
                  ( ubFileType == DCF_OBG_MP4 ) ||
                  ( ubFileType == DCF_OBG_AVI ) ||
                  ( ubFileType == DCF_OBG_3GP ) ||
                  ( ubFileType == DCF_OBG_TS  ) ||
                  ( ubFileType == DCF_OBG_WMV ) ))
			{
				uiCurTotalFileCount++;
			}
			else if((m_uiBrowserFileTypeMask & AHC_MIMF_BROWSER_MASK_JPG) &&
				( ubFileType == DCF_OBG_JPG ))
			{
				uiCurTotalFileCount++;
			}

			if((uiImgIndex+1) == uiCurTotalFileCount)
			{
				*puiDcfIndex = j;
				*sDB         = i;
				*bIsRearCam  = AHC_FALSE;
				bfound = AHC_TRUE;
				goto END_MAPPING;
			}
		}


        if(bRearCamEnable && bfound == AHC_FALSE)
		{
            //ret = AHC_DCFDT_GetTotalRearFileCount(&uiRearFileCount);
			ret = AHC_DCFDT_GetTotalFileCountByCurrCamID(&uiRearFileCount);
            if(ret == AHC_FALSE){
            	printc("%s,%d  return False\r\n",__func__, __LINE__);
            	return AHC_FALSE;
            }
			AHC_DCFDT_GetRearCamPathFlag(&bCurRearCam);
    		AHC_DCFDT_SetRearCamPathFlag(AHC_TRUE);
			
			for(j=0;j<uiRearFileCount;j++)
			{
				ret = AHC_DCFDT_GetFileTypebyIndex(j, &ubFileType);
				if((m_uiBrowserFileTypeMask & AHC_MIMF_BROWSER_MASK_MOV) &&
					( ( ubFileType == DCF_OBG_MOV ) ||
                      ( ubFileType == DCF_OBG_MP4 ) ||
                      ( ubFileType == DCF_OBG_AVI ) ||
                      ( ubFileType == DCF_OBG_3GP ) ||
                      ( ubFileType == DCF_OBG_TS  ) ||
                      ( ubFileType == DCF_OBG_WMV ) ))
				{
					uiCurTotalFileCount++;
				}
				else if((m_uiBrowserFileTypeMask & AHC_MIMF_BROWSER_MASK_JPG) &&
					( ubFileType == DCF_OBG_JPG ))
				{
					uiCurTotalFileCount++;
				}

				if((uiImgIndex+1) == uiCurTotalFileCount)//index[0~9], total=10
				{
					*puiDcfIndex = j;
					*sDB         = i;
					*bIsRearCam  = AHC_TRUE;
					bfound = AHC_TRUE;
					break;
				}
			}
			AHC_DCFDT_SetRearCamPathFlag(bCurRearCam);
        }
    }

END_MAPPING:	
    if(bfound == AHC_FALSE){
        printc("Error!!! IndexReverseMapping not found! %d %s\r\n", uiImgIndex, __func__);
    }
    AHC_DCFDT_SelectDB(uiCurDB);
    return bfound;
}

AHC_BOOL AHC_MIMF_IndexReverseMappingDecreaseSort(UINT32 uiImgIndex, UINT32 *puiDcfIndex, UINT32 *sDB, AHC_BOOL *bIsRearCam)
{
    UINT32 uiFileCount;
    
    AHC_DCFDT_GetTotalFileCountByCurrCamID(&uiFileCount);
    
    if( (uiFileCount == 0) || (uiImgIndex > (uiFileCount-1)) ){
        printc("Given a incorrect Index!!\r\n");
        return AHC_FALSE;
    }
    
    *puiDcfIndex = ((uiFileCount - 1) - uiImgIndex);
    *sDB         = AHC_DCFDT_GetDB();
    AHC_DCFDT_GetRearCamPathFlag(bIsRearCam);
    
    return AHC_TRUE;
}
AHC_BOOL AHC_MIMF_IndexReverseMapping(UINT32 uiImgIndex, UINT32 *puiDcfIndex, UINT32 *sDB, AHC_BOOL *bIsRearCam)
{
    //disable it, because its not compatible for multicam DCFDT 
	//return AHC_MIMF_IndexReverseMappingByDB(uiImgIndex, puiDcfIndex, sDB, bIsRearCam);
#if (MIMF_CUSTOMIZED_SORT_TYPE == MIMF_CUSTOMIZED_SORT_FILETYPE)
	return AHC_MIMF_IndexReverseMappingByFileType(uiImgIndex, puiDcfIndex, sDB, bIsRearCam);
#elif (MIMF_CUSTOMIZED_SORT_TYPE == MIMF_CUSTOMIZED_SORT_DECREASE)
    return AHC_MIMF_IndexReverseMappingDecreaseSort(uiImgIndex, puiDcfIndex, sDB, bIsRearCam);
#elif (MIMF_CUSTOMIZED_SORT_TYPE == MIMF_CUSTOMIZED_SORT_MULTI_DB_DECREASE)
    return AHC_MIMF_IndexReverseMappingMultiDB_De_Sort(uiImgIndex, puiDcfIndex, sDB, bIsRearCam);
#else
	return AHC_FALSE; //Not implemented
#endif
}
//------------------------------------------------------------------------------
//  Function    : AHC_MIMF_IndexMappingDecreaseSort
//  Description : dcf Index mapping to Thumb Index
//  param[in] DCF Index in DB
//  param[in] DB type
//  param[in] IsRearCam
//  param[out]  Thumb Index which from UF level
//  retval AHC_TRUE Success.
//------------------------------------------------------------------------------
AHC_BOOL AHC_MIMF_IndexMappingDecreaseSort(UINT32 puiDcfIndex, UINT32 sDB, AHC_BOOL bIsRearCam, UINT32 *uiImgIndex)
{
	UINT32 uiFileCount;
    
    AHC_DCFDT_GetTotalFileCountByCurrCamID(&uiFileCount);
    
    if( (uiFileCount == 0) || (puiDcfIndex > (uiFileCount-1)) ){
        printc("Given a incorrect Index!!\r\n");
        return AHC_FALSE;
    }
    
    *uiImgIndex = ((uiFileCount - 1) - puiDcfIndex);
    //*sDB         = AHC_DCFDT_GetDB();
    //AHC_DCFDT_GetRearCamPathFlag(bIsRearCam);
    
    return AHC_TRUE;	
}
//------------------------------------------------------------------------------
//  Function    : AHC_MIMF_IndexMapping
//  Description : dcf Index mapping to Thumb Index
//  param[in] DCF Index in DB
//  param[in] DB type
//  param[in] IsRearCam
//  param[out]  Thumb Index which from UF level
//  retval AHC_TRUE Success.
//------------------------------------------------------------------------------
AHC_BOOL AHC_MIMF_IndexMapping(UINT32 puiDcfIndex, UINT32 sDB, AHC_BOOL bIsRearCam, UINT32 *uiImgIndex)
{
#if(MIMF_CUSTOMIZED_SORT_TYPE == MIMF_CUSTOMIZED_SORT_DECREASE)
	return AHC_MIMF_IndexMappingDecreaseSort(puiDcfIndex, sDB, bIsRearCam, uiImgIndex);
#endif	
	return AHC_FALSE;
}
AHC_BOOL AHC_MIMF_SetCurrentIndex(UINT32 uiImgIndex)
{
    UINT32 uiTotalCount; 
	UINT8  ubCurrCamID;
	UINT32 uiSyncIndex;
    if( !AHC_MIMF_GetTotalFileCount(&uiTotalCount))
    {
        return AHC_FALSE;
    }
    if(uiImgIndex >= uiTotalCount)
    {
        printc("ImgIndex %d >= TotalCount %d %s\r\n", uiImgIndex, uiTotalCount, __func__);
        return AHC_FALSE;
    }
	
	AHC_DCFDT_GetRearCamPathFlag(&ubCurrCamID);
    m_uiMIMFCurIndex[ubCurrCamID] = uiImgIndex;
    //transfer Index and set it to other cam by Chuni Li
    {
    	UINT32   sDB;
    	UINT32   uiSrcIndex;
    	UINT32   uiDstIndex;
    	AHC_BOOL bIsRearCam;
    	UINT8    ubCurrCamID;
    	UINT32   i;

    	AHC_DCFDT_GetRearCamPathFlag(&ubCurrCamID);
    	for(i = 0; i < DCFDT_CAM_NUM; i++)
    	{
    		if(i != ubCurrCamID)
    		{
    			AHC_MIMF_IndexReverseMapping(uiImgIndex, &uiSrcIndex, &sDB, &bIsRearCam);
    			AHC_DCFDT_TransferIndexbyCamID(uiSrcIndex, i, &uiDstIndex);
    			AHC_MIMF_IndexMapping(uiDstIndex, sDB, bIsRearCam, &uiSyncIndex);
    			m_uiMIMFCurIndex[i] = uiSyncIndex;
    		}
    	}
    }
    //end of transfer
    return AHC_TRUE; 
}

AHC_BOOL AHC_MIMF_GetCurrentIndex(UINT32 *puiImgIndex)
{
    UINT32 uiTotalCount; 
	UINT8  ubCurrCamID;
    if( !AHC_MIMF_GetTotalFileCount(&uiTotalCount))
    {
        return AHC_FALSE;
    }
    AHC_DCFDT_GetRearCamPathFlag(&ubCurrCamID);
    *puiImgIndex = m_uiMIMFCurIndex[ubCurrCamID];
    if(*puiImgIndex >= uiTotalCount)
    {
        printc("*puiImgIndex %d >= TotalCount %d %s\r\n", *puiImgIndex, uiTotalCount, __func__);
        return AHC_FALSE;
    }

    return AHC_TRUE;
}

AHC_BOOL AHC_MIMF_GetFilePathNamebyIndex(UINT32 uiIndex, char* FilePathName) 
{
    UINT32   uiDcfIndex;
    UINT32   sDB;
    AHC_BOOL bIsRearCam;
    UINT32   uiCurDB;
    AHC_BOOL ret;
    AHC_BOOL bCurRearCam;
    
    uiCurDB = AHC_DCFDT_GetDB();
    AHC_MIMF_IndexReverseMapping(uiIndex, &uiDcfIndex, &sDB, &bIsRearCam);
    AHC_DCFDT_SelectDB(sDB);
    
    if(bIsRearCam == AHC_TRUE){
        AHC_DCFDT_GetRearCamPathFlag(&bCurRearCam);
        AHC_DCFDT_SetRearCamPathFlag(AHC_TRUE);
    }
    
	ret = AHC_DCFDT_GetFilePathNamebyIndex(uiDcfIndex, FilePathName); 
    
    if(bIsRearCam == AHC_TRUE){
        AHC_DCFDT_SetRearCamPathFlag(bCurRearCam);
    }
    AHC_DCFDT_SelectDB(uiCurDB);
    return ret;
}

AHC_BOOL AHC_MIMF_GetFileSizebyIndex(UINT32 uiIndex, UINT32* uiFileSize) 
{
    UINT32   uiDcfIndex;
    UINT32   sDB;
    AHC_BOOL bIsRearCam;
    UINT32   uiCurDB;
    AHC_BOOL ret;
    AHC_BOOL bCurRearCam;
    
    uiCurDB = AHC_DCFDT_GetDB();
    AHC_MIMF_IndexReverseMapping(uiIndex, &uiDcfIndex, &sDB, &bIsRearCam);
    AHC_DCFDT_SelectDB(sDB);
    
    if(bIsRearCam == AHC_TRUE){
        AHC_DCFDT_GetRearCamPathFlag(&bCurRearCam);
        AHC_DCFDT_SetRearCamPathFlag(AHC_TRUE);
    }
    
	ret = AHC_DCFDT_GetFileSizebyIndex(uiDcfIndex, uiFileSize); 
    
    if(bIsRearCam == AHC_TRUE){
        AHC_DCFDT_SetRearCamPathFlag(bCurRearCam);
    }
    AHC_DCFDT_SelectDB(uiCurDB);
    return ret;
}

AHC_BOOL AHC_MIMF_GetFileTypebyIndex(UINT32 uiIndex, UINT8 *ubFileType) 
{
    UINT32   uiDcfIndex;
    UINT32   sDB;
    AHC_BOOL bIsRearCam;
    UINT32   uiCurDB;
    AHC_BOOL ret;
    AHC_BOOL bCurRearCam;
    
    uiCurDB = AHC_DCFDT_GetDB();
	
    AHC_MIMF_IndexReverseMapping(uiIndex, &uiDcfIndex, &sDB, &bIsRearCam);
	
    AHC_DCFDT_SelectDB(sDB);
    
    if(bIsRearCam == AHC_TRUE){
        AHC_DCFDT_GetRearCamPathFlag(&bCurRearCam);
        AHC_DCFDT_SetRearCamPathFlag(AHC_TRUE);
    }
    
	ret = AHC_DCFDT_GetFileTypebyIndex(uiDcfIndex, ubFileType); 
    
    if(bIsRearCam == AHC_TRUE){
        AHC_DCFDT_SetRearCamPathFlag(bCurRearCam);
    }
	
    AHC_DCFDT_SelectDB(uiCurDB);
    return ret;
}

AHC_BOOL AHC_MIMF_IsReadOnlybyIndex(UINT32 uiIndex, AHC_BOOL *bReadOnly) 
{
    UINT32   uiDcfIndex;
    UINT32   sDB;
    AHC_BOOL bIsRearCam;
    UINT32   uiCurDB;
    AHC_BOOL ret;
    AHC_BOOL bCurRearCam;
    
    uiCurDB = AHC_DCFDT_GetDB();
    AHC_MIMF_IndexReverseMapping(uiIndex, &uiDcfIndex, &sDB, &bIsRearCam);
    AHC_DCFDT_SelectDB(sDB);
    
    if(bIsRearCam == AHC_TRUE){
        AHC_DCFDT_GetRearCamPathFlag(&bCurRearCam);
        AHC_DCFDT_SetRearCamPathFlag(AHC_TRUE);
    }
    
	ret = AHC_DCFDT_IsReadOnlybyIndex(uiDcfIndex, bReadOnly); 
    
    if(bIsRearCam == AHC_TRUE){
        AHC_DCFDT_SetRearCamPathFlag(bCurRearCam);
    }
    AHC_DCFDT_SelectDB(uiCurDB);
    return ret;
}

AHC_BOOL AHC_MIMF_GetFileTimebyIndex(UINT32 uiIndex, AHC_RTC_TIME *pRtcTime)
{
    UINT32   uiDcfIndex;
    UINT32   sDB;
    AHC_BOOL bIsRearCam;
    UINT32   uiCurDB;
    AHC_BOOL ret;
    AHC_BOOL bCurRearCam;
    
    uiCurDB = AHC_DCFDT_GetDB();
    AHC_MIMF_IndexReverseMapping(uiIndex, &uiDcfIndex, &sDB, &bIsRearCam);
    AHC_DCFDT_SelectDB(sDB);
    
    if(bIsRearCam == AHC_TRUE){
        AHC_DCFDT_GetRearCamPathFlag(&bCurRearCam);
        AHC_DCFDT_SetRearCamPathFlag(AHC_TRUE);
    }
    ret = AHC_DCFDT_GetFileTimebyIndex(uiDcfIndex, pRtcTime);

    if(bIsRearCam == AHC_TRUE){
        AHC_DCFDT_SetRearCamPathFlag(bCurRearCam);
    }
    AHC_DCFDT_SelectDB(uiCurDB);

    return ret;
}

AHC_BOOL AHC_MIMF_IsCharLockbyIndex(UINT32 uiIndex, AHC_BOOL *bCharLock)
{
    printc("Does not support!!\r\n");
    return AHC_FALSE;
}

AHC_BOOL AHC_MIMF_GetFileNamebyIndex(UINT32 uiIndex, char* FileName) 
{
    UINT32   uiDcfIndex;
    UINT32   sDB;
    AHC_BOOL bIsRearCam;
    UINT32   uiCurDB;
    AHC_BOOL ret;
    AHC_BOOL bCurRearCam;
    
    uiCurDB = AHC_DCFDT_GetDB();
    AHC_MIMF_IndexReverseMapping(uiIndex, &uiDcfIndex, &sDB, &bIsRearCam);
    AHC_DCFDT_SelectDB(sDB);
    
    if(bIsRearCam == AHC_TRUE){
        AHC_DCFDT_GetRearCamPathFlag(&bCurRearCam);
        AHC_DCFDT_SetRearCamPathFlag(AHC_TRUE);
    }
    ret = AHC_DCFDT_GetFileNamebyIndex(uiDcfIndex, FileName);

    if(bIsRearCam == AHC_TRUE){
        AHC_DCFDT_SetRearCamPathFlag(bCurRearCam);
    }
    AHC_DCFDT_SelectDB(uiCurDB);

    return ret;
}
AHC_BOOL AHC_MIMF_MoveFileByIndex(DCF_DB_TYPE sFromType, DCF_DB_TYPE sToType, UINT32 uiIndex, AHC_BOOL bReadOnly)
{
    UINT32   uiDcfIndex;
    UINT32   sDB;
    AHC_BOOL bIsRearCam;
    UINT32   uiCurDB;
    AHC_BOOL ret;
    AHC_BOOL bCurRearCam;
    
    uiCurDB = AHC_DCFDT_GetDB();
    AHC_MIMF_IndexReverseMapping(uiIndex, &uiDcfIndex, &sDB, &bIsRearCam);
    AHC_DCFDT_SelectDB(sDB);
    
    if(bIsRearCam == AHC_TRUE){
        AHC_DCFDT_GetRearCamPathFlag(&bCurRearCam);
        AHC_DCFDT_SetRearCamPathFlag(AHC_TRUE);
    }
    ret = AHC_DCFDT_MoveFileByIndex(sFromType, sToType, uiDcfIndex, bReadOnly);

    if(bIsRearCam == AHC_TRUE){
        AHC_DCFDT_SetRearCamPathFlag(bCurRearCam);
    }
    AHC_DCFDT_SelectDB(uiCurDB);
    
    return AHC_TRUE;  
}

AHC_BOOL AHC_MIMF_CheckFileCamStatus(UINT32 uiIndex, UINT8 *status)
{
    UINT32   uiDcfIndex;
    UINT32   sDB;
    AHC_BOOL bIsRearCam;
    UINT32   uiCurDB;
    AHC_BOOL ret;
    AHC_BOOL bCurRearCam;
    
    uiCurDB = AHC_DCFDT_GetDB();
    AHC_MIMF_IndexReverseMapping(uiIndex, &uiDcfIndex, &sDB, &bIsRearCam);
    AHC_DCFDT_SelectDB(sDB);
    
    if(bIsRearCam == AHC_TRUE){
        AHC_DCFDT_GetRearCamPathFlag(&bCurRearCam);
        AHC_DCFDT_SetRearCamPathFlag(AHC_TRUE);
    }
    ret = AHC_DCFDT_CheckFileCamStatus(uiDcfIndex, status);

    if(bIsRearCam == AHC_TRUE){
        AHC_DCFDT_SetRearCamPathFlag(bCurRearCam);
    }
    AHC_DCFDT_SelectDB(uiCurDB);    
    
    return AHC_TRUE;   
}
void AHC_MIMF_RegisterCusCallback(void)
{
    AHC_UF_MappingFuncRegisterCallBack(AHC_UFCB_GETTOTALFILECOUNT, (void*)AHC_MIMF_GetTotalFileCount);
    AHC_UF_MappingFuncRegisterCallBack(AHC_UFCB_SETCURRENTINDEX, (void*)AHC_MIMF_SetCurrentIndex);
    AHC_UF_MappingFuncRegisterCallBack(AHC_UFCB_GETCURRENTINDEX, (void*)AHC_MIMF_GetCurrentIndex);
    AHC_UF_MappingFuncRegisterCallBack(AHC_UFCB_GETFILEPATHNAMEBYINDEX, (void*)AHC_MIMF_GetFilePathNamebyIndex);
    AHC_UF_MappingFuncRegisterCallBack(AHC_UFCB_GETFILESIZEBYINDEX, (void*)AHC_MIMF_GetFileSizebyIndex);
    AHC_UF_MappingFuncRegisterCallBack(AHC_UFCB_GETFILETYPEBYINDEX, (void*)AHC_MIMF_GetFileTypebyIndex);
    AHC_UF_MappingFuncRegisterCallBack(AHC_UFCB_ISREADONLYBYINDEX, (void*)AHC_MIMF_IsReadOnlybyIndex);
    AHC_UF_MappingFuncRegisterCallBack(AHC_UFCB_GETFILETIMEBYINDEX, (void*)AHC_MIMF_GetFileTimebyIndex);
    AHC_UF_MappingFuncRegisterCallBack(AHC_UFCB_ISCHARLOCKBYINDEX, (void*)AHC_MIMF_IsCharLockbyIndex);
    AHC_UF_MappingFuncRegisterCallBack(AHC_UFCB_GETFILENAMEBYINDEX, (void*)AHC_MIMF_GetFileNamebyIndex);
    AHC_UF_MappingFuncRegisterCallBack(AHC_UFCB_MOVEFILEBYINDEX, (void*)AHC_MIMF_MoveFileByIndex);
    AHC_UF_MappingFuncRegisterCallBack(AHC_UFCB_CHECKFILECAMSTATUS, (void*)AHC_MIMF_CheckFileCamStatus);
}

//New Feature for Multi DB Browse
#if(MIMF_CUSTOMIZED_SORT_TYPE == MIMF_CUSTOMIZED_SORT_MULTI_DB_DECREASE)
void AHC_MIMF_SetMIMFMemStartAddr(UINT32 addr) 
{
    m_ulMIMFBaseAddr = addr;
}

void AHC_MIMF_GetMIMFMemStartAddr(UINT32 *addr) 
{
    *addr = m_ulMIMFBaseAddr;
}
AHC_BOOL AHC_MIMF_MemPoolFSInit(UINT32 uiMaxMemSize)
{
    AHC_BOOL bInit = AHC_FALSE;
    AHC_BOOL bRet  = AHC_FALSE;
	UINT32 ulMIMFMem;
	
	AHC_MIMF_GetMIMFMemStartAddr(&ulMIMFMem);
    if( !bInit )
    { 
        hMIMFFileNodeMemPool = AHC_MemPoolFS_InitPool((PBYTE)ulMIMFMem, uiMaxMemSize, sizeof(SINDEXMAPNODE) );

	    if( hMIMFFileNodeMemPool != NULL )
	    {
	        bRet = AHC_TRUE;
	    }

    }

    return bRet;
}

AHC_BOOL AHC_MIMF_MemPoolFSUninit(void)
{
    if( hMIMFFileNodeMemPool )
    {
        AHC_MemPoolFS_UninitPool(hMIMFFileNodeMemPool);
        hMIMFFileNodeMemPool = NULL;
        return AHC_TRUE;
    }
    return AHC_FALSE;
}

void* AHC_MIMF_FileNodeAlloc( void )
{
    return AHC_MemPoolFS_Calloc(hMIMFFileNodeMemPool);
}

AHC_BOOL AHC_MIMF_FileNodeFree( void* pbyBuff )
{
    MEMSET(pbyBuff, 0xFF, hMIMFFileNodeMemPool->uiChunkSize);
    return AHC_MemPoolFS_Free(hMIMFFileNodeMemPool,pbyBuff);
}

//this func is use for DCFDT callback when MIMF node need to sync with DCFDT node
AHC_BOOL AHC_MIMF_NodeOperation(UINT8 byDB,
                                SFILENAME_INFO FileNameInfo,
                                UINT8 byOperation)
{
    //if not select DB return true, do nothing
    if(!((0x01 << byDB) & MIMF_MULTI_DB_DECREASE_SELECT_DB))
    {
        return AHC_TRUE;
    }
    //{
        //PSINDEXMAPNODE psNodeCurr = m_MIMFBrowseDB.pFileHead;
        //printc("===========before\r\n");
        //while(psNodeCurr)
        //{
        //    printc("====DB %d nDateTime %d\r\n", psNodeCurr->byDB, psNodeCurr->nDateTime);
        //    psNodeCurr = psNodeCurr->pNext;
        //}
    //}
    switch(byOperation)
    {
        case DCFDT_NODE_INSERT:
        {
            //printc("Insert byDB %d nDateTime %d\r\n", byDB, nDateTime);
            // if it's the first node
            if(m_MIMFBrowseDB.pFileHead == NULL)
            {
                PSINDEXMAPNODE psNode;
                psNode = (PSINDEXMAPNODE)AHC_MIMF_FileNodeAlloc();
                if(psNode == NULL)
                {
                    printc("%s: Failed!!DCFDT_NODE_INSERT\r\n", __func__);
                    return AHC_FALSE;
                }
                //Insert the first
                m_MIMFBrowseDB.pFileHead = psNode;
                m_MIMFBrowseDB.pFileTail = psNode;
                m_MIMFBrowseDB.ulUFTotalFileNum++;
                psNode->FileNameInfo = FileNameInfo;
                psNode->byDB      = byDB;
            }
            else
            {
                //Search from tail to head
                PSINDEXMAPNODE psNodeCurr = m_MIMFBrowseDB.pFileTail;
                //printc("pFileTail 0x%x\r\n", m_MIMFBrowseDB.pFileTail);
                while(psNodeCurr)
                {                 
                    //printc("psNodeCurr DB %d nDateTime %d\r\n", psNodeCurr->byDB, psNodeCurr->nDateTime);
                    //duplicate node
                    if(FileNameInfo.uiFileIndex == psNodeCurr->FileNameInfo.uiFileIndex && 
					   FileNameInfo.nDateTime == psNodeCurr->FileNameInfo.nDateTime && 
					   byDB == psNodeCurr->byDB)
                    {
                        //do nothing
                        printc("%s, Duplicate Node Insert!\r\n", __func__);
                        return AHC_TRUE;
                    }
                    //sort index first,than sort date time, sort by DB count third 
                    else if((FileNameInfo.uiFileIndex != DCFDT_FILEINDEX_INVALID && FileNameInfo.uiFileIndex > psNodeCurr->FileNameInfo.uiFileIndex) ||
						    (FileNameInfo.uiFileIndex == psNodeCurr->FileNameInfo.uiFileIndex && FileNameInfo.nDateTime > psNodeCurr->FileNameInfo.nDateTime) ||
						    (FileNameInfo.uiFileIndex == psNodeCurr->FileNameInfo.uiFileIndex && FileNameInfo.nDateTime == psNodeCurr->FileNameInfo.nDateTime && byDB > psNodeCurr->byDB))
                    {
                        PSINDEXMAPNODE psNode;
                        psNode = (PSINDEXMAPNODE)AHC_MIMF_FileNodeAlloc();
                        if(psNode == NULL)
                        {
                            printc("%s: Failed!!DCFDT_NODE_INSERT\r\n", __func__);
                            return AHC_FALSE;
                        }
                        
                        psNode->pPrev = psNodeCurr;
                        if(psNodeCurr == m_MIMFBrowseDB.pFileTail)
                        {
                            //Insert at tail
                            m_MIMFBrowseDB.pFileTail = psNode;
                        }
                        else
                        {
                            psNode->pNext = psNodeCurr->pNext;
                            psNodeCurr->pNext->pPrev = psNode;
                        }
                        psNodeCurr->pNext = psNode;
                        m_MIMFBrowseDB.ulUFTotalFileNum++;
                        psNode->FileNameInfo = FileNameInfo;
                        psNode->byDB      = byDB;
                        break;
                    }
                    psNodeCurr = psNodeCurr->pPrev;
                }
                //if not found, add a new node at head 
                if(psNodeCurr == NULL)
                {
                    PSINDEXMAPNODE psNode;
                    psNode = (PSINDEXMAPNODE)AHC_MIMF_FileNodeAlloc();
                    if(psNode == NULL)
                    {
                        printc("%s: Failed!!DCFDT_NODE_INSERT\r\n", __func__);
                        return AHC_FALSE;
                    }
                    psNode->pPrev = NULL;
                    psNode->pNext = m_MIMFBrowseDB.pFileHead;
                    if(m_MIMFBrowseDB.pFileHead == NULL){
                        m_MIMFBrowseDB.pFileHead = psNode;
                    }
                    else{
                        m_MIMFBrowseDB.pFileHead->pPrev = psNode;
                    }
                    m_MIMFBrowseDB.pFileHead = psNode;
                    m_MIMFBrowseDB.ulUFTotalFileNum++;
                    psNode->FileNameInfo = FileNameInfo;
                    psNode->byDB      = byDB;
                }
            }
        }
        break;
        case DCFDT_NODE_DELETE_PARENT:
        {
            //printc("delete byDB %d nDateTime %d\r\n", byDB, nDateTime);
            if(m_MIMFBrowseDB.pFileHead ==NULL)
            {
                printc("%s Failed, pFileHead == NULL", __func__);
            }
            else
            {
                PSINDEXMAPNODE psNodeCurr = m_MIMFBrowseDB.pFileHead;
                AHC_BOOL bFound = AHC_FALSE;
                while(psNodeCurr)
                {
                    if(FileNameInfo.uiFileIndex == psNodeCurr->FileNameInfo.uiFileIndex && 
					   FileNameInfo.nDateTime == psNodeCurr->FileNameInfo.nDateTime && 
					   byDB == psNodeCurr->byDB)
                    {
                        //unlink node
                        PSINDEXMAPNODE psNodePrev = psNodeCurr->pPrev;
                        PSINDEXMAPNODE psNodeNext = psNodeCurr->pNext;
                        bFound = AHC_TRUE;
                        //Head
                        if(psNodePrev == NULL)
                        {
                            m_MIMFBrowseDB.pFileHead = psNodeNext;
                            if(psNodeNext){
                                psNodeNext->pPrev = NULL;
                            }
                        }
                        //Tail
                        else if(psNodeNext == NULL)
                        {
                            m_MIMFBrowseDB.pFileTail = psNodePrev;
                            psNodePrev->pNext = NULL;
                        }
                        else
                        {
                            psNodePrev->pNext = psNodeNext;
                            if(psNodeNext){
                                psNodeNext->pPrev = psNodePrev;
                            }
                        }
                        
                        AHC_MIMF_FileNodeFree((void*)psNodeCurr);
                        m_MIMFBrowseDB.ulUFTotalFileNum--;
                        break;
                    }
                    psNodeCurr = psNodeCurr->pNext;
                }
                if(!bFound)
                {
                     printc("[Warning] %s Node not found!! %d\r\n", __func__);
                    return AHC_FALSE;
                }
            }
        }
        break;
          default:
            printc("%s Illegal para\r\n",__func__);
          break;
    }

    //{
    //    PSINDEXMAPNODE psNodeCurr = m_MIMFBrowseDB.pFileHead;
    //    printc("===========after\r\n");
    //    while(psNodeCurr)
    //    {
    //        printc("====DB %d nDateTime %d\r\n", psNodeCurr->byDB, psNodeCurr->nDateTime);
    //        psNodeCurr = psNodeCurr->pNext;
    //    }
    //}
    return AHC_TRUE;
}

//This function is used for index reverse mapping
AHC_BOOL AHC_MIMF_GetDBandDCFIndexbyThumbIndex(UINT32 ThumbIndex,UINT8* byDB,UINT32* DCFIndex)
{
    PSINDEXMAPNODE psNodeCurr = m_MIMFBrowseDB.pFileHead;
    UINT32         ulFileCount = 0;
    AHC_BOOL       bFound = AHC_FALSE;
    while(psNodeCurr && ulFileCount <= ThumbIndex)
    {
        //search from head to tail
        //check FileCount
        if(ulFileCount == ThumbIndex)
        {
            //get DB
            *byDB = psNodeCurr->byDB;
            AHC_DCFDT_GetIndexbyDBandFileNameInfo(psNodeCurr->byDB, psNodeCurr->FileNameInfo, DCFIndex);
            bFound = AHC_TRUE;
        }
        ulFileCount++;
        psNodeCurr = psNodeCurr->pNext;
    }
    if(!bFound){
        printc("%s Thumb Index %d not found\r\n", __func__, ThumbIndex);
        return AHC_FALSE;
    }
    return AHC_TRUE;
}

//index reverse mapping for multi DB browse
AHC_BOOL AHC_MIMF_IndexReverseMappingMultiDB_De_Sort(UINT32 uiImgIndex, UINT32 *puiDcfIndex, UINT32 *sDB, AHC_BOOL *bIsRearCam)
{
    UINT32 uiFileCount = m_MIMFBrowseDB.ulUFTotalFileNum;
    UINT32 uiTmpImgIndex;
    if(m_bSetFastBrowse)
    {
        //check uiImgIndex is correct 
        if((uiFileCount == 0) || (uiImgIndex > (uiFileCount - 1))){
            printc("Given incorrect ThumbIndex %d\r\n", uiImgIndex);
            return AHC_FALSE;
        }
        //change increase index to decrease index
        uiTmpImgIndex = ((uiFileCount - 1) - uiImgIndex);
        //get DCF index and DB, assign bIsRearCam as false
        AHC_MIMF_GetDBandDCFIndexbyThumbIndex(uiTmpImgIndex, (UINT8*)sDB, puiDcfIndex);
        *bIsRearCam = DCF_CAM_FRONT;
    }
    else
    {
    	AHC_DCFDT_GetTotalFileCountByCurrCamID(&uiFileCount);
        *puiDcfIndex = (uiFileCount - 1) - uiImgIndex;
        *sDB         = AHC_DCFDT_GetDB();
        *bIsRearCam  = DCF_CAM_FRONT;
    }
    return AHC_TRUE;
}

void AHC_MIMF_SetMultiDBBrowseEnable(AHC_BOOL bSetMultiDBBrowse)
{
    m_bSetFastBrowse = bSetMultiDBBrowse;
}

AHC_BOOL AHC_MIMF_GetMultiDBBrowseEnable(void)
{
	return m_bSetFastBrowse;
}
#endif
//End of New Feature for Multi DB Browse
#endif//end of AHC_MIMF
