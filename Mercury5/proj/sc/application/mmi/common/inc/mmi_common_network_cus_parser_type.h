
#ifndef __MMI_COMMON_NETWORK_SETTING_CUS_PARSER_TYPE_H__
#define __MMI_COMMON_NETWORK_SETTING_CUS_PARSER_TYPE_H__

enum
{
    SECTION_HEADER = 0,
    SECTION_DATA,
    SECTION_WAP,
    SECTION_MMS,
    SECTION_EMAIL,
    SECTION_QQ,
    SECTION_JAVA,
    SECTION_OTHER,
    SECTION_LBS,
    SECTION_MAX,
};

enum
{
    CONNECTION_ORIENTED = 0,
    CONNECTION_HTTP,
    CONNECTION_MAX,
};

typedef struct Column_struct_t_
{
    short nColumnNum;
    const short *pColumn; // Every record column length size;
} Column_struct_t;

typedef struct CusHeader_struct_t_
{
    char strVer[4]; // include '\0
    Column_struct_t tDataAccount;
#ifdef __WAP_MMI_CDWAP__
    Column_struct_t tWAP;
#endif
#ifdef __MMS_MMI_CDMMS__
    Column_struct_t tMMS;
#endif
#ifdef __EMAIL_MMI__
    Column_struct_t tEMAIL;
#endif
#ifdef __NCCQQ_MMI__
    Column_struct_t tQQ;
#endif
#ifdef __JAVA_MMI__
    Column_struct_t tJAVA;
#endif
#ifdef __WLAN_MMI__
    Column_struct_t tOther;
#endif
#ifdef __MAP_MMI_LBS__
    Column_struct_t tLBS;
#endif
} CusHeader_struct_t;

#define CONNECTION_ORIENTED_TXT    "CONNECTION_ORIENTED"
#define CONNECTION_HTTP_TXT        "HTTP"

#endif // __MMI_COMMON_NETWORK_SETTING_CUS_PARSER_TYPE_H__
