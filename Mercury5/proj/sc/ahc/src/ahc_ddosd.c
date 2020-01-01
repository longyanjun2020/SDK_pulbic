/*===========================================================================
 * Include files
 *===========================================================================*/ 
#include "Customer_config.h" 
#include "AHC_Config_SDK.h"
#include "ahc_message.h"
#include "ahc_gui.h"
#include "ahc_os.h"
#include "ahc_fs.h"
#include "ahc_ddosd.h"
#include "ahc_utility.h"
#include "ait_utility.h"



#if (DDOSD)
/*===========================================================================
 * Macro define
 *===========================================================================*/ 
#define  ICON_NAME_MAX_NUM 			(60)
#define  ICON_TABLE_MAX_NUM 		(20)
#define  COLOR_TEMP_BUFFER_SIZE 	(200)
#define  AC_TEMP_BUFFER_SIZE 		(80000)

#define  DDOSD_DBG_ENABLE       	(0)  

/*===========================================================================
 * Global variable
 *===========================================================================*/ 
unsigned char 	m_IconName[ICON_TABLE_MAX_NUM][ICON_NAME_MAX_NUM];
GUI_BITMAP  	m_IconTable[ICON_TABLE_MAX_NUM];
GUI_LOGPALETTE 	m_Pal[ICON_TABLE_MAX_NUM];
GUI_COLOR* 		m_Colors[ICON_TABLE_MAX_NUM];
GUI_COLOR 		m_Colors_TempBuffer[COLOR_TEMP_BUFFER_SIZE];
unsigned char* 	m_ac[ICON_TABLE_MAX_NUM];
unsigned char 	m_ac_TempBuffer[AC_TEMP_BUFFER_SIZE];
UINT            m_TotalIconNum;


/*===========================================================================
 * Extern variable
 *===========================================================================*/ 


/*===========================================================================
 * Extern function
 *===========================================================================*/ 


/*===========================================================================
 * Main body
 *===========================================================================*/ 
AHC_BOOL AHC_DDOSD_Init(void)
{
    UINT i;
	
	memset(m_IconName, 			0, sizeof(unsigned char)*ICON_TABLE_MAX_NUM*ICON_NAME_MAX_NUM);
	memset(m_IconTable, 		0, sizeof(GUI_BITMAP)*ICON_TABLE_MAX_NUM);
	memset(m_Pal, 				0, sizeof(GUI_LOGPALETTE)*ICON_TABLE_MAX_NUM);
	memset(m_Colors_TempBuffer, 0, sizeof(GUI_COLOR)*COLOR_TEMP_BUFFER_SIZE);
	memset(m_ac_TempBuffer, 	0, sizeof(unsigned char)*AC_TEMP_BUFFER_SIZE);
	
    for(i=0; i<ICON_TABLE_MAX_NUM; i++){
		m_Colors[i] = m_Colors_TempBuffer;
		m_ac[i] = m_ac_TempBuffer;
    }	

	m_TotalIconNum = 0;
	return AHC_TRUE;
}

AHC_BOOL AHC_DDOSD_AddIcon(char *String, UINT StringLen)
{
	unsigned char IconPathName[ICON_NAME_MAX_NUM+10];
	UINT32 ulFileId;
    UINT32 ulActualSize;
	DDOSD_OFFSET DDOSD_Offset;
#if (DDOSD_DBG_ENABLE)	
	UINT i;
#endif	

	if(m_TotalIconNum > ICON_TABLE_MAX_NUM) {
	    printc("DDOSD Error: m_TotalIconNum > %d.\r\n", ICON_TABLE_MAX_NUM);
		return AHC_FALSE;
	}	
	
	if(STRLEN(String) > ICON_NAME_MAX_NUM) {
	    printc("DDOSD Error: Icon string len > %d.\r\n", ICON_NAME_MAX_NUM); 
		return AHC_FALSE;
	}
	
	MEMSET(IconPathName, 0, ICON_NAME_MAX_NUM+10);
	MEMCPY(IconPathName, "SF:0\\", STRLEN("SF:0\\"));
    MEMCPY(IconPathName+5, String, StringLen);

#if (DDOSD_DBG_ENABLE)
    printc("AHC_DDOSD_AddIcon: %s\r\n", IconPathName);
#endif

    if (AHC_FS_FileOpen((INT8 *)IconPathName, AHC_StrLen((char *)IconPathName), "rb", AHC_StrLen("rb"),  &ulFileId )) {
         printc("DDOSD Error: AHC_FS_FileOpen.\r\n");
        return AHC_FALSE;
    }

	//---------------------------------------------------------------------------------------------------------------------------
	//Get m_IconTable. XSize/YSize/BytesPerLine/BitsPerPixel
	if( AHC_ERR_NONE != AHC_FS_FileSeek(ulFileId, 8, AHC_FS_SEEK_SET) ){
	    printc("DDOSD Error: AHC_FS_FileSeek.\r\n");
		AHC_FS_FileClose(ulFileId) ;
		return AHC_FALSE;
	}
    if( AHC_ERR_NONE != AHC_FS_FileRead(ulFileId, (UINT8 *)&m_IconTable[m_TotalIconNum], 8, &ulActualSize) ){
        printc("DDOSD Error: AHC_FS_FileRead for m_IconTable.\r\n");
		AHC_FS_FileClose(ulFileId) ;
		return AHC_FALSE;
    }
   
#if (DDOSD_DBG_ENABLE)	
	printc("AHC_DDOSD_AddIcon: m_IconTable[%d].XSize = %d\r\n", m_TotalIconNum, m_IconTable[m_TotalIconNum].XSize);
    printc("AHC_DDOSD_AddIcon: m_IconTable[%d].YSize = %d\r\n", m_TotalIconNum, m_IconTable[m_TotalIconNum].YSize);    
	printc("AHC_DDOSD_AddIcon: m_IconTable[%d].BytesPerLine = %d\r\n", m_TotalIconNum, m_IconTable[m_TotalIconNum].BytesPerLine);
	printc("AHC_DDOSD_AddIcon: m_IconTable[%d].BitsPerPixel = %d\r\n", m_TotalIconNum, m_IconTable[m_TotalIconNum].BitsPerPixel);
#endif

    //---------------------------------------------------------------------------------------------------------------------------
	//Get m_Pal. NumEntries/HasTrans
    if( AHC_ERR_NONE != AHC_FS_FileRead(ulFileId, (UINT8 *)&m_Pal[m_TotalIconNum], 5, &ulActualSize) ){
        printc("DDOSD Error: AHC_FS_FileRead for m_Pal.\r\n");
		AHC_FS_FileClose(ulFileId) ;
		return AHC_FALSE;
    }	
	
#if (DDOSD_DBG_ENABLE)	
    printc("AHC_DDOSD_AddIcon: m_Pal[%d].NumEntries = %d\r\n", m_TotalIconNum, m_Pal[m_TotalIconNum].NumEntries);
    printc("AHC_DDOSD_AddIcon: m_Pal[%d].HasTrans = %d\r\n", m_TotalIconNum, m_Pal[m_TotalIconNum].HasTrans);    
#endif

    //---------------------------------------------------------------------------------------------------------------------------
	//Get Offset. IconNameLen/IconNameOffset/ColorsOffset/PictureDataOffset
    if( AHC_ERR_NONE != AHC_FS_FileRead(ulFileId, (UINT8 *)&DDOSD_Offset, 8, &ulActualSize) ){
        printc("DDOSD Error: AHC_FS_FileRead for Offset.\r\n");
		AHC_FS_FileClose(ulFileId) ;
		return AHC_FALSE;
    }	

#if (DDOSD_DBG_ENABLE)	
    printc("AHC_DDOSD_AddIcon: DDOSD_Offset.IconNameLen = %d\r\n", DDOSD_Offset.IconNameLen);
    printc("AHC_DDOSD_AddIcon: DDOSD_Offset.IconNameOffset = %d\r\n", DDOSD_Offset.IconNameOffset);
    printc("AHC_DDOSD_AddIcon: DDOSD_Offset.ColorsOffset = %d\r\n", DDOSD_Offset.ColorsOffset);
    printc("AHC_DDOSD_AddIcon: DDOSD_Offset.PictureDataOffset = %d\r\n", DDOSD_Offset.PictureDataOffset);
#endif

	//---------------------------------------------------------------------------------------------------------------------------
	//Get IconName.
    if( AHC_ERR_NONE != AHC_FS_FileRead(ulFileId, (UINT8 *)m_IconName[m_TotalIconNum], DDOSD_Offset.IconNameLen, &ulActualSize) ){
        printc("DDOSD Error: AHC_FS_FileRead for IconName.\r\n");
		AHC_FS_FileClose(ulFileId) ;
		return AHC_FALSE;
    }

#if (DDOSD_DBG_ENABLE)	
	printc("AHC_DDOSD_AddIcon: m_IconName[%d] = %s\r\n", m_TotalIconNum, m_IconName[m_TotalIconNum]);
#endif

    //---------------------------------------------------------------------------------------------------------------------------
	//Get Colors.
    if(m_TotalIconNum == 0) {
		m_Colors[m_TotalIconNum] = m_Colors_TempBuffer;
    }	
	else {
		m_Colors[m_TotalIconNum] = m_Colors[m_TotalIconNum-1] + m_Pal[m_TotalIconNum-1].NumEntries;
	}	
	
	if((m_Colors[m_TotalIconNum] + m_Pal[m_TotalIconNum].NumEntries*4) > (m_Colors_TempBuffer + COLOR_TEMP_BUFFER_SIZE)) {
        printc("DDOSD Error: m_Colors size is small.\r\n");
		AHC_FS_FileClose(ulFileId) ;
		return AHC_FALSE;
    }	
    
    if( AHC_ERR_NONE != AHC_FS_FileRead(ulFileId, (UINT8 *)m_Colors[m_TotalIconNum], m_Pal[m_TotalIconNum].NumEntries*4, &ulActualSize) ){
        printc("DDOSD Error: AHC_FS_FileRead for Colors.\r\n");
		AHC_FS_FileClose(ulFileId) ;	
		return AHC_FALSE;
    }
	m_Pal[m_TotalIconNum].pPalEntries = m_Colors[m_TotalIconNum];
	m_IconTable[m_TotalIconNum].pPal = &m_Pal[m_TotalIconNum];

#if (DDOSD_DBG_ENABLE)	
    for(i=0; i<m_Pal[m_TotalIconNum].NumEntries ; i++){
		printc("AHC_DDOSD_AddIcon: Color[%d] = 0x%X\r\n", i, (GUI_COLOR)*(m_Colors[m_TotalIconNum]+i));
    }
#endif
	
	//---------------------------------------------------------------------------------------------------------------------------
	//Get PictureData.
    if(m_TotalIconNum == 0) {
		m_ac[m_TotalIconNum] = m_ac_TempBuffer;
    }	
	else {
		m_ac[m_TotalIconNum] = m_ac[m_TotalIconNum-1] + m_IconTable[m_TotalIconNum-1].BytesPerLine*m_IconTable[m_TotalIconNum-1].YSize;
	}	
	
	if((m_ac[m_TotalIconNum] + m_IconTable[m_TotalIconNum].BytesPerLine*m_IconTable[m_TotalIconNum].YSize) > (m_ac_TempBuffer + AC_TEMP_BUFFER_SIZE)) {
        printc("DDOSD Error: m_ac_TempBuffer size is small.\r\n");
		AHC_FS_FileClose(ulFileId) ;
		return AHC_FALSE;
    }	
    
    if( AHC_ERR_NONE != AHC_FS_FileRead(ulFileId, (UINT8 *)m_ac[m_TotalIconNum], m_IconTable[m_TotalIconNum].BytesPerLine*m_IconTable[m_TotalIconNum].YSize, &ulActualSize) ){
		printc("DDOSD Error: AHC_FS_FileRead for PictureData.\r\n");
		AHC_FS_FileClose(ulFileId) ;
		return AHC_FALSE;
    }
	m_IconTable[m_TotalIconNum].pData = m_ac[m_TotalIconNum];
    
	
   //---------------------------------------------------------------------------------------------------------------------------
	 
	AHC_FS_FileClose(ulFileId) ;
	
	m_TotalIconNum ++;

	return AHC_TRUE;
}


AHC_BOOL AHC_DDOSD_Check(char *IconName, UINT *IconIntex)
{
	UINT i;

	for(i=0; i<m_TotalIconNum; i++) {	
		if( STRCMP((INT8*)IconName, (INT8*)m_IconName[i]) == 0 ) 
		{
			*IconIntex = i;
			return AHC_TRUE;
		}
	}	

	printc("Error: %s doesn't at Icon Table.\r\n", IconName);
	return AHC_FALSE;
}	

AHC_BOOL AHC_DDOSD_DrawBitmap(UINT16 uwDisplayID, char *IconName, UINT16 uwX, UINT16 uwY) 
{
	UINT IconIntex;
	
    if(AHC_DDOSD_Check(IconName, &IconIntex)) {
		AHC_OSDDrawBitmap(uwDisplayID, &m_IconTable[IconIntex], uwX, uwY); 
		return AHC_TRUE;
    }
	return AHC_FALSE;
}

AHC_BOOL	AHC_DDSOD_UnInit(void)
{

	return AHC_TRUE;
}

#endif

