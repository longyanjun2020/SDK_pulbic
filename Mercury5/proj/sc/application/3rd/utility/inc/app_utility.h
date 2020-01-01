#ifndef __UTIL__ALL_H__
#define __UTIL__ALL_H__
extern const u8 *PYTable1[];
extern const u8 *PYTable2[];
extern const u8 *PYTable3[];

u8 Utl_getPinYinCode(u16 wc,u8 *buffer, u8 maxBufferSize);
u8 Utl_getBPMFCode(u16 wc,u16 *buffer, u8 maxBufferSize);
u8 Utl_CheckMultiPinYinFirstWord(u16 firstWC, u16 secondWC, u8 *buffer, u8 maxBufferSize);
u8 Utl_CheckMultiPinYinSecondWord(u16 firstWC, u16 secondWC, u8 *buffer, u8 maxBufferSize);
u16 Utl_atoi2(const char *str);
u16 Utl_octoi(const char *oct);
u16 Utl_hextoi(const char *hex);

extern u16 Utl_Big5ToUnicode (u16 code);

extern u16 Utl_GBToUnicode (u16 code);

extern u16 Utl_UnicodeToBig5 (u16 code);

extern u16 Utl_UnicodeToGB (u16 code);

#define MAX_VCARD_NAME_LENGTH (15)
#define MAX_VCARD_TEL_LENGTH  (25)
#define MAX_VCARD_INFOMATION_LENGTH (100)
#define TOKEN_ELIMINATE1 (0x0d)
#define TOKEN_ELIMINATE2 (0x0a)

static const u8 VCARD_START[12]="BEGIN:VCARD";
static const u8 VCARD_VERSION[9]="VERSION:";
static const u8 VCARD_NAME[3]="N:";
static const u8 VCARD_FULLNAME[4]="FN:";
static const u8 VCARD_ORG[5]="ORG:";
static const u8 VCARD_TITLE[7]="TITLE:";
static const u8 VCARD_TELWORK1[16]="TEL;WORK;VOICE:";
//static const u8 VCARD_TELWORK2[]="";
static const u8 VCARD_TELHOME1[16]="TEL;HOME;VOICE:";
//static const u8 VCARD_TELHOME2[]="";
static const u8 VCARD_TELCELL[16]="TEL;CELL;VOICE:";
static const u8 VCARD_TELPAGER[17]="TEL;PAGER;VOICE:";
static const u8 VCARD_FAX1[14]="TEL;WORK;FAX:";
//static const u8 VCARD_FAX2[]="";
static const u8 VCARD_ADDR[10]="ADR;WORK:";
static const u8 VCARD_URL[5]="URL:";
static const u8 VCARD_EMAIL[21]="EMAIL;PREF;INTERNET:";
static const u8 VCARD_END[9]="END:VCARD";

typedef struct
{
	u8 version[4];
	u8 lastName[MAX_VCARD_NAME_LENGTH];
	u8 firstName[MAX_VCARD_NAME_LENGTH];
	u8 name[MAX_VCARD_NAME_LENGTH];
	u8 nickname[MAX_VCARD_NAME_LENGTH];
	u8 org[MAX_VCARD_NAME_LENGTH];
	u8 title[MAX_VCARD_NAME_LENGTH];
	u8 telWork1[MAX_VCARD_TEL_LENGTH];
	u8 telWork2[MAX_VCARD_TEL_LENGTH];
	u8 telHome1[MAX_VCARD_TEL_LENGTH];
	u8 telHome2[MAX_VCARD_TEL_LENGTH];
	u8 telCell[MAX_VCARD_TEL_LENGTH];
	u8 telPager[MAX_VCARD_TEL_LENGTH];
	u8 faxWork[MAX_VCARD_TEL_LENGTH];
	u8 faxHome[MAX_VCARD_TEL_LENGTH];
	u8 addrWork[MAX_VCARD_INFOMATION_LENGTH];
	u8 addrHome[MAX_VCARD_INFOMATION_LENGTH];
	u8 URL1[MAX_VCARD_INFOMATION_LENGTH];
	u8 URL2[MAX_VCARD_INFOMATION_LENGTH];
	u8 Email[MAX_VCARD_INFOMATION_LENGTH];
}vcard_Record_t;

#endif
