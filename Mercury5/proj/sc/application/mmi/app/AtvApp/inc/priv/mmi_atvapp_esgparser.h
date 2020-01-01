/**
* @file    mmi_atvapp_esgparser.h
* @version
* @brief   general television esgparser header file.
*
*/
#ifndef __MMI_ATVAPP_ESGPARSER_H__
#define __MMI_ATVAPP_ESGPARSER_H__

#include "mmi_mae_common_def.h"

#define MMI_ATV_ESG_XML_MAX_DATA_LEN	204800 //200k

#define MMI_ATV_ESG_DATA_TYPE_MAX_NUM		5
#define MMI_ATV_ESG_SERVICE_MAX_NUM		50
#define MMI_ATV_ESG_SERVICEAUX_MAX_NUM		50
#define MMI_ATV_ESG_SCHEDULE_MAX_NUM		1500
#define MMI_ATV_ESG_CONTENT_MAX_NUM		100
#define MMI_ATV_ESG_SERVICEPARA_MAX_NUM	50

#define MMI_ATV_ESG_SERVICE_NAME_LEN	50
#define MMI_ATV_ESG_TITLE_LEN			50
#define MMI_ATV_ESG_LANG_LEN			6
#define MMI_ATV_ESG_URI_LEN			128
#define MMI_ATV_ESG_SERVICE_DESCRIPTION_LEN	128
#define MMI_ATV_ESG_SERVICE_PROVIDER_LEN		128
#define MMI_ATV_ESG_SERVICE_LANGUAGE_LEN		128
#define MMI_ATV_ESG_CONTENTCLASS_LEN	20
#define MMI_ATV_ESG_MEDIADATA_MAX_BYTE_LEN	128
#define MMI_ATV_ESG_DATE_LEN	11
#define MMI_ATV_ESG_TIME_LEN	9
#define MMI_ATV_ESG_CADESCRIPTOR_LEN	MMI_ATV_ESG_URI_LEN
#define MMI_ATV_ESG_EXTENTINFO_LEN		MMI_ATV_ESG_URI_LEN
#define MMI_ATV_ESG_KEYWORD_LEN		    MMI_ATV_ESG_TITLE_LEN
#define MMI_ATV_ESG_DIGESTINFO_LEN		MMI_ATV_ESG_URI_LEN
#define MMI_ATV_ESG_AUDIOLANG_LEN		MMI_ATV_ESG_LANG_LEN
#define MMI_ATV_ESG_SUBTITLELANG_LEN	MMI_ATV_ESG_LANG_LEN
#define MMI_ATV_ESG_PARA_LEN			MMI_ATV_ESG_URI_LEN

#define ATVAPP_MAX_TIMESLOTNUM			(40)
#define ATVAPP_MAX_PROGRAM_NUM         (30)

typedef enum
{
	ATV_DATA_TYPE_RAI_INFO = 0,
	ATV_DATA_TYPE_RAI_CHANNEL_INFO,
	ATV_DATA_TYPE_ESG_SERVICE,
	ATV_DATA_TYPE_ESG_SERVICEAUX,
	ATV_DATA_TYPE_ESG_SCHEDULE,
	ATV_DATA_TYPE_ESG_CONTENT,
	ATV_DATA_TYPE_ESG_SERVICEPARA
} AtvDataType_e;


typedef struct
{
	u16			nServiceId;
	u8			nServiceClass; //0,8-255:Reservation, 1:TV, 2:Audio,.....
	u8			nServiceGenre;
	u16			nServiceParaId;
	MAE_WChar	pwcLang[MMI_ATV_ESG_LANG_LEN];
	MAE_WChar	pwcServiceNameStr[MMI_ATV_ESG_SERVICE_NAME_LEN];
	boolean		bForFree;
	MAE_WChar	pwcCADescriptor[MMI_ATV_ESG_CADESCRIPTOR_LEN];		//anyURI
} EsgServiceType_t;

typedef struct
{
	u8			nUsage;
	MAE_WChar	pwcContentClass[MMI_ATV_ESG_CONTENTCLASS_LEN];
	char		pcMediaData[MMI_ATV_ESG_MEDIADATA_MAX_BYTE_LEN]; ////base64Binary
	MAE_WChar	pwcMediaURI[MMI_ATV_ESG_URI_LEN];
} EsgMedia_t;

typedef struct
{
	u16			nServiceId;
	///////////////////////////
	//ServiceAuxLanguageSpecial
	///////////////////////////
	MAE_WChar	pwcLang[MMI_ATV_ESG_LANG_LEN];
	MAE_WChar	pwcServiceDescription[MMI_ATV_ESG_SERVICE_DESCRIPTION_LEN];
	MAE_WChar	pwcServiceProvider[MMI_ATV_ESG_SERVICE_DESCRIPTION_LEN];
	MAE_WChar	pwcServiceLanguage[MMI_ATV_ESG_SERVICE_DESCRIPTION_LEN];
	////////////////////////////
	EsgMedia_t	tMedia;		//esg:MediaType
	MAE_WChar	pwcExtentInfo[MMI_ATV_ESG_EXTENTINFO_LEN];	//anyURI

} EsgServiceAuxType_t;

typedef struct
{
	char	pcDate[MMI_ATV_ESG_DATE_LEN];		//"2008-07-28"
	char	pcTime[MMI_ATV_ESG_TIME_LEN];	    //"00:00:00"
} EsgUtcDateTimeType_t;

typedef struct
{
	u16			nScheduleId;
	u16			nServiceId;
	u16			nContentId;
	MAE_WChar	pwcTitleStr[MMI_ATV_ESG_TITLE_LEN];
	MAE_WChar	pwcLang[MMI_ATV_ESG_LANG_LEN];
	EsgUtcDateTimeType_t	tStartTime;
	boolean		bForFree;
	boolean		bLive;
	boolean		bRepeat;
	MAE_WChar	pwcCADescriptor[MMI_ATV_ESG_CADESCRIPTOR_LEN];
	u16			nYear;
	u16			nMonth;
	u16			nDay;
	u16			nHour;
	u16			nMinute;
	u16			nSecond;
} EsgScheduleType_t;

typedef struct XML_ContentType_tag
{
	u16			nContentId;
	MAE_WChar	pwcContentClass[MMI_ATV_ESG_CONTENTCLASS_LEN];
	u8			nContentGenre;
	u16			nDuration;
	EsgMedia_t	tMedia;
	////////////////////////
	//ContentLanguageSpecial
	////////////////////////
	MAE_WChar	pwcLang[MMI_ATV_ESG_LANG_LEN];	 //Attribute
	MAE_WChar	pwcTitle[MMI_ATV_ESG_TITLE_LEN];
	MAE_WChar	pwcKeyword[MMI_ATV_ESG_TITLE_LEN];
	MAE_WChar	pwcDigestInfo[MMI_ATV_ESG_SERVICE_DESCRIPTION_LEN];
	MAE_WChar	pwcAutoLang[MMI_ATV_ESG_LANG_LEN];
	MAE_WChar	pwcSubTitleLang[MMI_ATV_ESG_LANG_LEN];
	////////////////////////
	u16			nServiceParaId;
	MAE_WChar	pwcExtentInfo[MMI_ATV_ESG_EXTENTINFO_LEN];	//Any URI.
} EsgContentType_t;

typedef struct
{
	u16			nServiceParaId;
	MAE_WChar	pwcPara[MMI_ATV_ESG_URI_LEN];	//Any Type.
} EsgServiceParaType_t;

typedef struct
{
	EsgServiceType_t		tService;
	EsgServiceAuxType_t		tServiceAux;
	EsgScheduleType_t		tSchedule;
	EsgContentType_t		tContent;
	EsgServiceParaType_t	tServicePara;
	EsgUtcDateTimeType_t	tPublishTime;
	const char				*pPublisher;
	const char				*pRightsOwner;
	//const char			*pVer;			//esg:VerType
} EsgData_t;

typedef struct
{
	EsgServiceType_t	*pServiceCurr;
	EsgServiceType_t	tServiceData;
	EsgServiceType_t	*pServiceNext;
} EsgServiceNode_t;

typedef struct
{
	//EsgServiceNode_t *pServiceNodes;
	//u16 u16Count;
	//u16 u16CountInXML;
	EsgServiceType_t	tServices[MMI_ATV_ESG_SERVICE_MAX_NUM];
	u16					nUsedCnt;
} EsgServiceList_t;

typedef struct
{
	//EsgServiceAuxType_t *pServiceAux;
	//u16 u16Count;
	//u16 u16CountInXML;
	EsgServiceAuxType_t	tServiceAuxs[MMI_ATV_ESG_SERVICE_MAX_NUM];
	u16					nUsedCnt;
} EsgServiceAuxList_t;

typedef struct
{
	//EsgScheduleType_t *pSchedule;
	//u16 u16Count;
	//u16 u16CountInXML;
	EsgScheduleType_t	tSchedules[MMI_ATV_ESG_SCHEDULE_MAX_NUM];
	u16					nUsedCnt;
} EsgScheduleList_t;

typedef struct
{
	//EsgContentType_t *pContent;
	//u16 u16Count;
	//u16 u16CountInXML;
	EsgContentType_t	tContents[MMI_ATV_ESG_CONTENT_MAX_NUM];
	u16					nUsedCnt;
} EsgContentList_t;

typedef struct
{
	//EsgServiceParaType_t *pServicePara;
	//u16 u16Count;
	//u16 u16CountInXML;
	EsgServiceParaType_t	tServiceParas[MMI_ATV_ESG_SERVICEPARA_MAX_NUM];
	u16						nUsedCnt;
} EsgServiceParaList_t;



//////////////////////////////////////////////////////////////////

EsgServiceList_t * EsgParseServiceType(const char *pXMLSource, s32 nLen);
EsgServiceAuxList_t * EsgParseServiceAuxType(const char *pXMLSource, s32 nLen);
EsgScheduleList_t * EsgParseScheduleType(const char *pXMLSource, s32 nLen);
EsgContentList_t * EsgParseContentType(const char *pXMLSource, s32 nLen);
EsgServiceParaList_t * EsgParseServiceParaType(const char *pXMLSource, s32 nLen);


#endif	//__MMI_GTVAPP_ESGPARSER_H__


