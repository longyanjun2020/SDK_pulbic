
#ifndef __MMI_MAE_CUSTOMIZATION_TYPES_H__
#define __MMI_MAE_CUSTOMIZATION_TYPES_H__
#include "mmi_mae_common_def.h"
#include "mmi_mae_customization_forward.h"

enum
{
	THEME_UNKNOW,
	THEME_SUPPORTED,
	THEME_NOT_SUPPORTED
};

enum
{
	MEM_TYPE_RAM = 0,
	MEM_TYPE_NAND
};

enum
{
    CUS_LANGUAGE_SYSTEM = 0,
    CUS_LANGUAGE_AP
};

#define SYSTEM_THEME  1
#define DEFAULT_THEME 1
#define ESSENTIAL_THEME (SYSTEM_THEME + DEFAULT_THEME)

#define CUS_AP_BIT				20
#define CUS_FORMAT_BIT			16
#define CUS_MEDIA_ID_MASK		0xFFFF	
#define CUS_TEXT_ID_MASK		0xFFFF	
#define CUS_CHECK_MEDIA_MASK	0x000F0000


struct SolutionHeader_t_
{
    u16 WCid;      // Wavecom identifier: 0x4357
    u16 VersionH;  // version: change to 32 bits after multi-theme 
    u16 Version;
    u8  Format;
    u8  ThemeAmount;    
    u32 SystemTheme;
    u32 DefaultTheme;
    u32 Reserved1;
};

struct ResourceGroupHeader_t_
{
    u16 WCid;      // Wavecom identifier: 0x4357
    u16 Version;
    u8  Format;
    u8  Reserved;
    u16 APamount;
    u32 ThemeNameID;
    u32 Reserved1[13]; //???
};


//CUS Header
struct CusHeader_t_
{
  u16 nWCid;      // Wavecom identifier: 0x4357
  u16 nHeaderLength;
  u8  nClass;
  u8  nFolderId;
  u8  nFormat;
  u8  nDataLocation;
  u8  nVersion;
  u8  nRelease;
  u16 nBackUpId;
  u32 nSize;

};

struct BootResourceHeader_t_
{
    u32 VersionInfo;
    u32 NoOfTotalBootRes;
    u32 Reserved;
    u32 OffsetTable;
};

struct BootResourceBlock_t_
{
    u16 ResourceFormat;
    u16 ImageFormat;
    u32 RawDataSize;
    u32 ImageWidth;
    u32 ImageHeight;
    u8  AlphaAndColorKey;
    u8  ColorKey[3];
    u8  ConstAlpha;
    u8  Reserved[3];
    u16 ImageRawData;
};

//////////////////////////////////////////////////////////////////
//Version
//////////////////////////////////////////////////////////////////

#define CUSID_SIZE 11 // NIC address + timestamp+'\0' ( 6+4+1 )

struct CusInfo_t_
{
	u8  *pCusID;
	u32 nVersion;
	u32 nTimestamp;
};

//////////////////////////////////////////////////////////////////
//Language
//////////////////////////////////////////////////////////////////

struct CusLangCodeIndexMapping_t_
{
	u16 nLangCode;                 //llanguage Code
	u16	nLangDisplayNameSize;  	//Size of Language Display Name
	u16 *pLangDisplayName;		//Language Display Name
	u16 nLangIdx;                //language Index

};

struct CusLangData_t_
{
	u16 nLangID;                 //language ID
	u16 *pOffsetTextLabels;     //pointer to the first offset
	u16 *pTextData;             //pointer to the first textdata

};


struct CusLangDataInfo_t_
{
    u32 nOffsetLangData;
    u32 nLangDataSize;
};

struct CusTextLabel_t_
{
    u8  nNumLangs;               //number of languages
    u8  nNumNoTrans;             //number of no translation textlabels
    u16 nNumLabels;	            //number of translation textlabels
    u16 nDefaultlangCode;       //default language Code
    CusLangDataInfo_t *pLangDataInfo;
    CusLangData_t *pLangData;   //Each Language TextData
    CusLangCodeIndexMapping_t *pLangCodeIndexTable;
    u8 **ppLangDataMem;
    u8 **ppDeCompBuf;
};

//////////////////////////////////////////////////////////////////
//Media:  Image/Melody
//////////////////////////////////////////////////////////////////
//Media Info
struct CusMediaInfo_t_
{
	u32 nSize;               //file nSize: embedded in raw data (4 bytes)
	u16* pFileName;         //also known as display name, including extension: embedded in raw data (n+1 bytes)
	u16* pPath;            //file path : generate on the fly  fs:\\PHONE\\PICTURES\\filename.ext or fs:\\PHONE\\SOUNDS\\filename.ext
	u16* pUrl;             //ad url: generate on the fly      ad:\\IMAGE\\ID   //UCS2
	u32 nTextID;            //textID;
	u32 nMimeType;         //mime type
} ;

struct CusMediaDynamicInfo_t_
{
	u8 *paDynamicItemRefCount;		// pointer to an array of dynamic items reference count
	u32 *paDynamicItemMem;			// pointer to an array of dynamic items memory
};

//Media Data
struct CusMediaData_t_
{
	u32 nNumSystemItems;         //number of system items

	u32 nLocPredefinedItem;            //starting index of predefined items
	u32 nNumPredefinedItems;           //number of predefined items

	u32 nLocThemeItem;              //starting id location of theme item
	u32 nNumThemeItems;             //number of theme items

	u32 nTotalMediaItems;        //total media items (predefined + install + theme)

	u32 *pOffsetFirstMedia;   //pointer to the first media item offset
	u8 *pFirstMediaData;      //pointer to the first media item
    u8 *pu8Mem;
};

//Media Text Data
struct CusMediaTextData_t_
{
	u16 nLangID;             //Language ID
	u16 *pOffsetFirstText;  //pointer to the first text offset
	u16 *pFirstTextData;         //pointer to the first textdata
};

//Image Data
struct CusImageData_t_
{
	u32 nTotalNumImageType;				//Total number of Image types
	u32 nSingleImageType;				//Single Image type. eg. the start index of install image
	u32 nPredefinedImageType;			//Install Image type. eg. the start index of install image
	u32 *pLocImageType;					//Location of current Image type
	u32 *pStartIndex;					//Start Index
	u32 *pNumImageType;					//Number of current Image type
	u8 **ppImageMem;					//For dynamic load
	u32 *pRefcount;						//For dynamic load
	u32 nTotalImageItems;				//Number of Total Images

	u32 *pOffsetFirstImage;				//pointer to the first image item offset
	u8 *pFirstImageData;				//pointer to the first media item

	//The following is for single image (after install image type)
	CusMediaDynamicInfo_t *pSingleImageInfo;		//pointer to dynamic items info, include predefined items and theme items
	CusMediaDynamicInfo_t *pPredefinedImageInfo;	//Pointer to predefined image
};

//////////////////////////////////////////////////////////////////
//PLMN data
//////////////////////////////////////////////////////////////////
#define MAX_LONG_ENG_LEN    24
#define MAX_SHORT_ENG_LEN   17
#define MAX_LONG_LOCAL_LEN  24
#define MAX_SHORT_LOCAL_LEN 17

struct CusPLMNData_t_
{
	u32 nNumRecords;
	u32 *pOffsetFirstRecord;
	u8 *pFirstPLMNData;
    u8 *pu8Mem;
};

struct CusPLMNRecord_t_
{
	u8 nLangID1;   //langID for LocalName1
	u8 nLangID2;   //langID for LocalName2

    u16 nMcc;
    u16 nMnc;

	u8 nLongEngName[MAX_LONG_ENG_LEN];
    u8 nShortEngName[MAX_SHORT_ENG_LEN];

	u16 nLongLocalName1[MAX_LONG_LOCAL_LEN];
    u16 nShortLocalName1[MAX_SHORT_LOCAL_LEN];

	u16 nLongLocalName2[MAX_LONG_LOCAL_LEN];
    u16 nShortLocalName2[MAX_SHORT_LOCAL_LEN];
};

//////////////////////////////////////////////////////////////////
//Input
//////////////////////////////////////////////////////////////////

struct CusInputArrayData_t_
{
	u16 nArrayIdx;               //array Index
	//u8	arrayNameSize;  		//Size of array Name
	u32	nArraySize;  			//Size of array data
	//u8 *pArrayName;				//array Name
	u8 *pArraydata;				//array data
};

struct CusInputLangData_t_
{
	u16 nLangIdx;                //ime Index
	u16 nLangCode;               //ime Code
	u16	nLangDisplayNameSize;  	//Size of Language Display Name
	u16 *plangDisplayName;		//Language Display Name
	u16 nNumArray;				//default lang code
	u32 nOffsetLang;             //number of lang
	u32 u32Size;
};

struct CusIMEData_t_
{
	u8 nImeIdx;                //ime Index
	u8 nImeCode;               //ime Code
	u16 nDefaultLangCode;       //default lang code
	u16  nNumLang;               //number of lang
	u16  nIndexoffsetIME;        //index offset
	u32 nOffsetIME;             //offset
};

struct CusInput_t_
{
	u8  nNumIME;               //number of ime
	u8  nDefaultIME;             //default ime
	CusIMEData_t *pIMEData;   //Each IME Data
	CusInputLangData_t *pInputLang;
	u8 *pInputArrayStartAdr;
    u8 *pu8Mem;
};

//////////////////////////////////////////////////////////////////
//Handwrite
//////////////////////////////////////////////////////////////////

struct CusHandwriteArrayData_t_
{
	u16 nArrayIdx;               //array Index
	//u8	arrayNameSize;  		//Size of array Name
	u32	nArraySize;  			//Size of array data
	//u8 *pArrayName;				//array Name
	u8 *pArraydata;				//array data
};

struct CusHandwriteData_t_
{
	u8 nHandwriteIdx;                //handwrite Index
	u8 nHandwriteCode;               //handwrite Code
	u16  nNumArray;               //number of array
	u32 nOffsetHandwrite;             //number of handwrite
};

struct CusHandwrite_t_
{
	u8  nNumHandwrite;               //number of Handwrite
	u8  nDefaultHandwrite;            //default Handwrite
	CusHandwriteData_t *pHandwriteData;   //Each Handwrite Data
	u8 *pHandwriteArrayStartAdr;
    u8 *pu8Mem;
};
//////////////////////////////////////////////////////////////////
//RC
//////////////////////////////////////////////////////////////////

struct CusWndRC_t_
{
   u16 WndId;
   u8 *RSdata;
};


struct CusAppRC_t_
{
	u16 ApId;                     //AP ID
	u16 nNumWndRC;                //number of Wnd
	CusWndRC_t *tWndRC;           //Each Wnd Data
};

struct CusRCHead_t_
{
	u16 ThmID;
	u32 nThmName;
	u16  nNumAppRC;               //number of App
    CusAppRC_t* tAppRC;           //Each app data
};

struct CusThmHead_t_
{
	u16 nNumThmRC;               //number of Theme
	CusRCHead_t* tThmRC;           //Each app data
    u8 *pu8Mem;
};


//////////////////////////////////////////////////////////////////
//Append Data
//////////////////////////////////////////////////////////////////
struct CusAppendHead_t_
{
	u8* pPointer;
	u32 nSize;
};


//////////////////////////////////////////////////////////////////
//3rd Data
//////////////////////////////////////////////////////////////////
struct CusThirdData_t_
{
	u32 nOffset;
	u32 nSize;
};

struct CusThirdHead_t_
{
	u16 nNumThird;
	CusThirdData_t *pThirdData;
};

//////////////////////////////////////////////////////////////////
//Project Resource
//////////////////////////////////////////////////////////////////
struct APHead_t_
{
	boolean bExist;
	u16 nVersion;
	u16 ApID;
	u32 Size;
	CusImageData_t *ImgList;
	CusMediaData_t *MelodyList;
	CusTextLabel_t* NTPtr;
	CusTextLabel_t *TxtList;
	CusThmHead_t* RSPtr;
#ifdef __MMI_CUSVERIFIER_SUPPORT__
    u32 nImgListSize;
    u32 nMelodyListSize;
    u32 nTxtListSize;
    u32 nTxtListDecompressedSize;
    u32 nRSSize;
#endif
};

struct ThmHead_t_
{
	u16 nWCid;
	u16 nVersion;
	u16 ApAmount;
	u32 ThmNameId;
	u16 nGroupId;
	u16 nAngle;
	u16 *pRS_Layout;
	u32 *pApOffset;
	APHead_t* CommonList;
	APHead_t* ApList;
	u8 *pThmApSupported;
	u32 *pRS_ThemeColor;
};

struct SystemHead_t_
{
	u16 nWCid;
	u16 nVersion;
	CusInfo_t* BootPtr;
	CusPLMNData_t* PlmnPtr;
	u8* FontPtr;
	u8* KMXFontPtr;
	CusHandwrite_t* HandWritePtr;
	CusInput_t* ImePtr;
	CusImageData_t *ImgList;
	CusMediaData_t *MelodyList;
	CusTextLabel_t* NTPtr;
	CusTextLabel_t *TxtList;
	CusAppendHead_t *Append;
	CusThirdHead_t *Third;
#ifdef __MMI_CUSVERIFIER_SUPPORT__
    u32 nBootSize;
    u32 nPlmnSize;
    u32 nPlmnDeCompressedSize;
    u32 nFontSize;
    u32 nFontDeCompressedSize;
    u32 nHandWriteSize;
    u32 nHandWriteDeCompressedSize;
    u32 nImeSize;
    u32 nImeDeCompressedSize;
    u32 nImgListSize;
    u32 nMelodyListSize;
    u32 nTxtListSize;
    u32 nTxtListDecompressedSize;
    u32 nAppendSize;
    u32 nThirdSize;
    u32 nKMXFontSize;
    u32 nKMXFontDeCompressedSize;
#endif
};

struct PrjHead_t_
{
	u16 nWCid;
	u32 nVersion;
	u16 ThmAmount;
	u32 *pThmOffset;
	SystemHead_t* SystemPtr;
	ThmHead_t* DefaultThmPtr;
	ThmHead_t* DefLThmPtr;
	ThmHead_t** ThmList;
#ifdef __MMI_CUSVERIFIER_SUPPORT__
	u32 nCusDecompressedSize;
#endif
};

#endif //__MMI_MAE_CUSTOMIZATION_TYPES_H__
