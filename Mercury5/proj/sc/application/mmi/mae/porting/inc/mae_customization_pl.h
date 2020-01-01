
#ifndef __MAE_CUSTOMIZATION_PL_H__
#define __MAE_CUSTOMIZATION_PL_H__

#include "mmi_mae_porting.h"


#define MAE_CUS_ALIGNMENT_SIZE		32
#define MAE_HEAP_ALIGNMENT_SIZE		32

#define MAE_CUS_DEFAULT_LOAD_SIZE	128
#define MAE_CUS_DEBUG_SIZE			200

enum
{
    MAE_CUS_THEME_MELODY_BASE_ID = 0,
    MAE_CUS_INSTALL_MELODY_BASE_ID,
    MAE_CUS_IMG_MEM_FULL,
    MAE_CUS_IMG_UNKNOW_IMG,
    MAE_CUS_AP_ID_COMMON,
    MAE_CUS_TXT_IMG_N_WALLPAPER,
    MAE_CUS_TXT_CCL_N_UNKNOW_ID,
    MAE_CUS_TXT_LIL_N_COMMON_MEMORY_FULL
};

typedef struct mae_memLink_s
{
	struct mae_memLink_s *psNextLink;
	u32 u32MemAddr;
	u32 u32MemSize;
} mae_memLink_ts;

typedef struct
{
	mae_memLink_ts *psLinkHeader;
	u8 *pu8Mem;
	u32 u32AddressInNand;
	u32 u32LoadSize;
} mae_cusLoader_ts;

typedef struct CusDbgErrorInfo_t_
{
	u8 *pu8Mem;
	u32 nNandAddr;
	u32 nSize;
}CusDbgErrorInfo_t;

/**
 *  MaePl_CusCreateCusLoader
 *  @brief  Create CUS loader for dynamic load
 *
 *  @return none.
 */
void MaePl_CusCreateCusLoader(void);

/**
 *  MaePl_CusFreeCusLoader
 *  @brief  Free CUS loader
 *
 *  @return none.
 */
void MaePl_CusFreeCusLoader(void);

/**
*  MaePl_FreeCusLoadToMem
*  @brief  Free the memory dynamic loaded previously.
*
*  @param  [in ]ptr		Point to the memory.
*
*  @return none.
*/
void MaePl_FreeCusLoadToMem( void *ptr );

/**
*  MaePl_CusLoadToMem
*  @brief  Load the content in NAND to RAM.
*
*  @param  [out]ppReturnPtr		Pointer to RAM address
*  @param  [in ]u32NandAddr		The NAND address to be loaded.
*  @param  [in ]u32Size			The size.
*  @param  [out]nLoadSize		Pointer to real load size.
*
*  @return MAE_RETURN_SUCCESS	Load the memory successfully
*          MAE_RETURN_FAILED	failed
*/
MAE_Ret MaePl_CusLoadToMem(u8** ppReturnPtr, u8* pPointer, u32 nSize, u32 *nLoadSize);

/**
*  MaePl_CusGetOneByteValue
*  @brief  Get one byte from NAND or ram
*
*  @param  [in ]pCusPointer		Pointer to the NAND or RAM address.
*  @param  [in ]nMemType		The NAND or RAM memory type.
*
*  @return u8	The read value.
*/
u8 MaePl_CusGetOneByteValue(const u8* pCusPointer, u8 nMemType);

/**
 *  MaePl_CusGetFourByteValue
 *  @brief  Gets the value from 4 continuous bytes
 *
 *  @param  [in ]pCusPointer   pointer to the starting byte
 *
 *  @return u32 the value of the 4 bytes
 */
u32 MaePl_CusGetFourByteValue(u8* pCusPointer, u8 nMemType);

/**
 *  MaePl_CusGetTwoByteValue
 *  @brief  Gets the value from 2 continuous bytes
 *
 *  @param  [in ]pCusPointer   pointer to the starting byte
 *
 *  @return u16 the value of the 2 bytes
 */
u16 MaePl_CusGetTwoByteValue(u8* pCusPointer, u8 nMemType);

/**
*  MaePl_CusCreateTextMemHandle
*  @brief  Create text memory handle.
*
*  @return none.
*/
void MaePl_CusCreateTextMemHandle(void);


/**
*  MaePl_CusFreeTextMemHandle
*  @brief  Free text memory handle
*
*  @return none.
*/
void MaePl_CusFreeTextMemHandle(void);


/**
*  MaePl_CusDecompressText
*  @brief  Decompress the text.
*
*  @param  [in ]pTextLabel		Point to the text data structure.
*  @param  [out]ppPointer		Pointer to the buffer address allocated for decompressed data.
*  @param  [in ]nSize			The compressed data size.
*
*  @return	MAE_RET_SUCCESS		Decompress the text successfully.
*			MAE_RET_FAILED		failed.
*/
MAE_Ret MaePl_CusDecompressText(CusTextLabel_t *pTextLabel, u16 nLanguageIndex, u8 **ppPointer, u32 nSize);

/**
*  MaePl_CusDynamicImageInit
*  @brief  The initialization function for dynamic load image.
*
*  @param  [out]pImageDataTable	Pointer to the image data structure.
*
*  @return	MAE_RET_SUCCESS		Initialization successfully.
*			MAE_RET_FAILED		failed.
*/
MAE_Ret MaePl_CusDynamicImageInit(CusImageData_t **pImagmakeeDataTable);

/**
*  MaePl_CusFreeDynamicMediaData
*  @brief  Free dynamic load media data
*
*  @param  [in ]nMediaID		The media ID.
*  @param  [in ]nFormatType		The format of the media
*  @param  [in ]pTheme			The theme
*
*  @return	none.
*/
void MaePl_CusFreeDynamicMediaData(u32 nMediaID, CUS_FORMAT_TYPE_e nFormatType, ThmHead_t *pTheme);

/**
*  MaePl_CusLoadImage
*  @brief  Dynamic load image.
*
*  @param  [out]ppMediaData			Pointer to the media data.
*  @param  [in ]pImageDataTable		Pointer to image data structure.
*  @param  [in ]nMediaID			The media ID.
*  @param  [in ]offsetAddr			The offset of the first image data.
*  @param  [out]bIsFound			The image is found and has been loaded
*
*  @return	MAE_RET_SUCCESS		Load the image successfully.
*			MAE_RET_FAILED		failed.
*/
MAE_Ret MaePl_CusLoadImage(u8 **ppMediaData, CusImageData_t* pImageDataTable, u32 nMediaID, u32 offsetAddr, boolean* bIsFound);


/**
*  MaePl_CusVerifyHeader
*  @brief  Verify CUS header.
*
*  @param  [in ]pHeader			The CUS header.
*  @param  [in ]nMemType		The memory type.
*
*  @return	MAE_RET_SUCCESS		The header is valid.
*			MAE_RET_FAILED		failed.
*/
MAE_Ret MaePl_CusVerifyHeader(CusHeader_t* pHeader, u8 nMemType);

/**
*  MaePl_CusInitAdPartition
*  @brief  Read CUS data and verify CUS header.
*
*  @param  [out]ppPointer			Pointer to CUS data.
*  @param  [out]ppEndCusAddress		Pointer to CUS end address.
*
*  @return	MAE_RET_SUCCESS		Initialization successfully.
*			MAE_RET_FAILED		failed.
*/
MAE_Ret MaePl_CusInitAdPartition(u8 **ppPointer, u8 **ppEndCusAddress);

/**
*  MaePl_CusGetMediaInfo
*  @brief  Get the media information.
*
*  @param  [in ]pMediaInfo			Pointer to media information.
*  @param  [in ]pImage				pointer to the image memory.
*
*  @return	none.
*/
void MaePl_CusGetMediaInfo(CusMediaInfo_t* pMediaInfo, u8 *pImage);

/**
*  MaePl_CusLoadImageData
*  @brief  Load the image data.
*
*  @param  [in ]pImageDataTable		Pointer to image data structure.
*  @param  [in ]pPointer			pointer to the memory to read the image.
*  @param  [in ]nSize				The size to be loaded.
*
*  @return	none.
*/
void MaePl_CusLoadImageData(CusImageData_t *pImageDataTable, u8* pPointer, u32 nSize);

/**
*  MaePl_CusGetMediaTextID
*  @brief  Get the text ID of the image.
*
*  @param  [out]nTextID				Pointer to the text ID.
*  @param  [in ]pImage				pointer to the image memory.
*
*  @return	none.
*/
void MaePl_CusGetMediaTextID(u32 *nTextID, u8 *pImage);

/**
*  MaePl_CusFreeImage
*  @brief  Free image relative memory.
*
*  @param  [in ]pImageDataTable		Pointer to image data structure.
*
*  @return	none.
*/
void MaePl_CusFreeImage(CusImageData_t *pImageDataTable);

/**
*  MaePl_CusInitPLMNCompression
*  @brief  Initialization PLMN compression relative data
*
*  @param  [out]ppPointer			Pointer to PLMN memory address for decompression.
*  @param  [in ]nSize				The size of the compression data.
*
*  @return	MAE_RET_SUCCESS		Initialization successfully.
*			MAE_RET_FAILED		failed.
*/
MAE_Ret MaePl_CusInitPLMNCompression(u8** ppPointer, u32 nSize);

/**
*  MaePl_CusFreePLMNCompression
*  @brief  Free PLMN relative memory.
*
*  @return	none.
*/
void MaePl_CusFreePLMNCompression(void);

/**
*  MaePl_CusInitIMECompression
*  @brief  Initialization IME compression relative data
*
*  @param  [out]ppPointer			Pointer to IME memory address for decompression.
*  @param  [in ]nSize				The size of the compression data.
*
*  @return	MAE_RET_SUCCESS		Initialization successfully.
*			MAE_RET_FAILED		failed.
*/
MAE_Ret MaePl_CusInitIMECompression(u8** ppPointer, u32 nSize);

/**
*  MaePl_CusFreeIMECompression
*  @brief  Free IME relative memory.
*
*  @return	none.
*/
void MaePl_CusFreeIMECompression(void);

/**
*  MaePl_CusInitHandWriteCompression
*  @brief  Initialization HandWrite compression relative data
*
*  @param  [out]ppPointer			Pointer to HandWrite memory address for decompression.
*  @param  [in ]nSize				The size of the compression data.
*
*  @return	MAE_RET_SUCCESS		Initialization successfully.
*			MAE_RET_FAILED		failed.
*/
MAE_Ret MaePl_CusInitHandWriteCompression(u8** ppPointer, u32 nSize);

/**
*  MaePl_CusFreeHandWriteCompression
*  @brief  Free HandWrite relative memory.
*
*  @return	none.
*/
void MaePl_CusFreeHandWriteCompression(void);

/**
*  MaePl_CusGetInputArrayData
*  @brief  Get input array data
*
*  @param  [out]ppArrayData				Pointer to data.
*  @param  [in ]pBaseinputArray			The source we want to get.
*  @param  [in ]nSize					The nSize we want to get.
*
*  @return	MAE_RET_SUCCESS		Get data successfully.
*			MAE_RET_FAILED		failed.
*/
MAE_Ret MaePl_CusGetInputArrayData(u8** ppArrayData, u8* pBaseinputArray, u32 nSize);

/**
*  MaePl_CusFreeInputArrayDataWithIdx
*  @brief  Free input array data.
*
*  @param  [in ]pMem		The memory we want to free.
*
*  @return	none.
*/
void MaePl_CusFreeInputArrayDataWithIdx(void *pMem);

/**
*  MaePl_CusGetFontDataArray
*  @brief  Get font data
*
*  @param  [in ]u32FontCat					The font category.
*  @param  [out]ppArrayData					Pointer to data.
*  @param  [out]pu32ArrayFontSize			Pointer to the font size.
*  @param  [out]pu16ArraySize				Pointer to the array size.
*  @param  [in ]u16Size						The array size.
*
*  @return	MAE_RET_SUCCESS		Get data successfully.
*			MAE_RET_FAILED		failed.
*/
MAE_Ret MaePl_CusGetFontDataArray(u32 u32FontCat, const u8 **ppArrayData, u32 *pu32ArrayFontSize, u16 *pu16ArraySize, u16 u16Size);

/**
*  MaePl_CusDebugError
*  @brief  Save debug relative information for dynamic load
*
*  @param  [in ]nNANDAddress	The NAND address.
*  @param  [in ]nSize			The size.
*
*  @return	none.
*/
void MaePl_CusDebugError(u32 nNANDAddress, u32 nSize);


/**
*  MaePl_CusGetMappingResourceID
*  @brief  Check the mapping resource ID.
*
*  @param  [in ]nResourceID     The resource ID we want to get.
*  @param  [out]pMappingID		Pointer to the mapping resource ID.
*
*  @return	MAE_RET_SUCCESS		Get ID successfully.
*			MAE_RET_FAILED		unknown action.
*/
MAE_Ret MaePl_CusGetMappingResourceID(u32 nResourceID, u32 *pMappingID);

#endif //__MAE_CUSTOMIZATION_PL_H__



