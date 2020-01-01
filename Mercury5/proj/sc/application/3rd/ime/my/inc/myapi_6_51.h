/* v6.51 */
#ifndef __MYAPI__
#define __MYAPI__
#define MYCHAR    char
#define MYSHORT   short
#define MYLONG    long

#define MYBYTE  unsigned char
#define MYWORD  unsigned short
#define MYDWORD unsigned long
#define MYBOOL  unsigned char

#define MYTRUE      1
#define MYFALSE     0
#define CHAR_NULL   '\0'
#define CHAR_SPACE  ' '
#define MYNULL      0

#define MY_BASE_COMPONENT   0XEF00
#define MY_LAST_COMPONENT   0XEFFF

#define MY_BASE_ZHUYIN      128
#define MY_ZHUYIN_NUM       37

#define MYRC                            MYWORD
#define MYRC_OK                         ((MYWORD)0X0000)
#define MYRC_NONE                       ((MYWORD)0X0001)
#define MYRC_DEFINE_MODE                ((MYWORD)0X0002)

#define MYRC_ERROR                      ((MYWORD)0X0100)
#define MYRC_INVALID_LANGID             ((MYWORD)0X0101)
#define MYRC_INVALID_LANG_DATA          ((MYWORD)0X0102)
#define MYRC_INVALID_KEY                ((MYWORD)0X0103)
#define MYRC_INVALID_FUNCTION           ((MYWORD)0X0104)
#define MYRC_INVALID_ENTRY              ((MYWORD)0X0105)
#define MYRC_INVALID_MODE               ((MYWORD)0X0106)
#define MYRC_INVALID_STAT               ((MYWORD)0X0107)
#define MYRC_INVALID_PARAM              ((MYWORD)0X0108)
#define MYRC_NOT_COMPATIBLE_LANG_DATA   ((MYWORD)0X0109)
#define MYRC_INVALID_CHARACTER          ((MYWORD)0X010A)

#define MAX_PINYIN_CODE         30
#define NUM_LANG_DATA_BLOCKS    30
#define MAX_KEY_BUF_LEN         20
#define MAX_SELECTION_LEN       30
#define MAX_PINYIN_BUF_LEN      (MAX_PINYIN_CODE*15)

#define MY_STAT_MORE            (MYWORD) 0X0001
#define MY_STAT_END_INPUT       (MYWORD) 0X0002
#define MY_STAT_SHIFT           (MYWORD) 0X0004
#define MY_STAT_CAPS_LOCK       (MYWORD) 0X0008
#define MY_STAT_AUTO_DEFINE_WORD_1 (MYWORD) 0X0010
#define MY_STAT_AUTO_DEFINE_WORD_2 (MYWORD) 0X0020
#define MY_STAT_AUTO_DEFINE_WORD (MY_STAT_AUTO_DEFINE_WORD_1 | MY_STAT_AUTO_DEFINE_WORD_2)
#define MY_STAT_MANUAL_DEFINE_WORD      (MYWORD) 0X0040

#define MY_SEARCH_MODE_FULL_PINYIN  (MYBYTE) 0X00
#define MY_SEARCH_MODE_ABBR_PINYIN (MYBYTE) 0X01

typedef struct  MYLangData_s {
    MYBYTE  const *pPointer[NUM_LANG_DATA_BLOCKS];
} MYLangData;

typedef struct MYSelection_s {
    MYBYTE  bLangID;
    MYBYTE  bInputMode;
    MYBYTE  bKeyBufLen;
    MYBYTE  pbKeyBuf[MAX_KEY_BUF_LEN];
    MYWORD  pwKeyBuf[MAX_KEY_BUF_LEN];
    MYBYTE  bSpellCode;
    MYBYTE  bCurCharIndex;
    MYBYTE  pbPinyinBuf[MAX_PINYIN_BUF_LEN];
    MYWORD  pwSpellBuf[MAX_SELECTION_LEN];
    MYWORD  pwAuxSelection[MAX_SELECTION_LEN];
    MYWORD  pwComponent[5];
    MYBYTE  bSelectionNum;
    MYBYTE  bPageIndex;
    MYBYTE  bEntryLen;
    MYWORD  pwSelection[MAX_SELECTION_LEN];
    MYWORD  wState;
} MYSelection;

typedef struct MYListParam_s {
    MYBYTE *pbPhoneBook;
    MYWORD wNameFieldOffset;
    MYBYTE bNameFieldSize;
    MYWORD wEntrySize;
    MYWORD wEntries;
    MYBYTE bSearchMode;
    MYBYTE *pbSearchCode;
    MYWORD wLocation;
} MYListParam;

#define MY_MODE_STROKE          ((MYWORD) 0)
#define MY_MODE_PINYIN          ((MYWORD) 1)
#define MY_MODE_AMBIG           ((MYWORD) 2)
#define MY_MODE_SPELL           ((MYWORD) 3)
#define MY_MODE_NUMBER          ((MYWORD) 4)
#define MY_MODE_STRICT_PINYIN   ((MYWORD) 5)
#define MY_MODE_STRICT_ENG      ((MYWORD) 6)

#define MY_ALPHABETIC_STAT_NORMAL   ((MYBYTE) 0)
#define MY_ALPHABETIC_STAT_SHIFT    ((MYBYTE) 1)
#define MY_ALPHABETIC_STAT_CAPS     ((MYBYTE) 2)

#define MY_KEY_0        ((MYBYTE)0)
#define MY_KEY_1        ((MYBYTE)1)
#define MY_KEY_2        ((MYBYTE)2)
#define MY_KEY_3        ((MYBYTE)3)
#define MY_KEY_4        ((MYBYTE)4)
#define MY_KEY_5        ((MYBYTE)5)
#define MY_KEY_6        ((MYBYTE)6)
#define MY_KEY_7        ((MYBYTE)7)
#define MY_KEY_8        ((MYBYTE)8)
#define MY_KEY_9        ((MYBYTE)9)
#define MY_KEY_A        ((MYBYTE)10)
#define MY_KEY_B        ((MYBYTE)11)
#define MY_KEY_C        ((MYBYTE)12)
#define MY_KEY_D        ((MYBYTE)13)
#define MY_KEY_E        ((MYBYTE)14)
#define MY_KEY_F        ((MYBYTE)15)

#define MY_KEY_NEXT     ((MYBYTE)16)
#define MY_KEY_PREV     ((MYBYTE)17)
#define MY_KEY_SPACE    ((MYBYTE)18)
#define MY_KEY_CLEAR    ((MYBYTE)19)
#define MY_KEY_LEFT     ((MYBYTE)20)
#define MY_KEY_RIGHT    ((MYBYTE)21)
#define MY_KEY_STAR     ((MYBYTE)22)
#define MY_KEY_SHARP    ((MYBYTE)23)

#define MY_LANGID_None              0
#define MY_LANGID_Chinese_Simp      1
#define MY_LANGID_Chinese_Trad      2
#define MY_LANGID_English           3
#define MY_LANGID_German            4
#define MY_LANGID_Greek             5
#define MY_LANGID_Spanish           6
#define MY_LANGID_Finnish           7
#define MY_LANGID_French            8
#define MY_LANGID_Italian           9
#define MY_LANGID_Japanese          10
#define MY_LANGID_Korean            11
#define MY_LANGID_Dutch             12
#define MY_LANGID_Russian           13
#define MY_LANGID_Swedish           14
#define MY_LANGID_Thai              15
#define MY_LANGID_Arabic            16
#define MY_LANGID_Portuguese        17
#define MY_LANGID_Indonesian        18
#define MY_LANGID_Vietnamese        19
#define MY_LANGID_Malay             20
#define MY_LANGID_Hindi             21
#define MY_LANGID_Czech             22
#define MY_LANGID_Persian           23
#define MY_LANGID_Polish            24
#define MY_LANGID_Romanian          25
#define MY_LANGID_Turkish           26
#define MY_LANGID_Danish            27
#define MY_LANGID_Albanian          28
#define MY_LANGID_Bulgarian         29
#define MY_LANGID_Croatian          30
#define MY_LANGID_Farsi             31
#define MY_LANGID_Hebrew            32
#define MY_LANGID_Hungarian         33
#define MY_LANGID_Latvian           34
#define MY_LANGID_Yiddish           35
#define MY_LANGID_Urdu              36
#define MY_LANGID_Telugu			37
#define MY_LANGID_Bengali			38
#define MY_LANGID_Swahili			39
#define MY_LANGID_Tamil				40

#ifdef __cplusplus
#define MYFUNCTION extern "C"
#else
#define MYFUNCTION extern
#endif

MYFUNCTION MYSelection *MYInitialize(MYBYTE bLangID);
MYFUNCTION MYRC MYReset(void);
MYFUNCTION MYRC MYTerminate(void);

MYFUNCTION MYWORD MYGetVersion(void);
MYFUNCTION MYCHAR *MYGetOEMID(void);

MYFUNCTION MYLangData *MYGetLangDataPtr(MYBYTE bLangID);
MYFUNCTION MYRC MYSetLang(MYBYTE bLangID);
MYFUNCTION MYRC MYSetMaxStrokeNum(MYBYTE bNum,MYBOOL bMerge);
MYFUNCTION MYRC MYSetMaxPinyinNum(MYBYTE bNum1,MYBYTE nNum2,MYBYTE bNum3,MYBYTE bNum4);

MYFUNCTION MYRC MYGetSelection(void);
MYFUNCTION MYRC MYKeyProc(MYBYTE bKey);
MYFUNCTION MYRC MYKeyProcU(MYWORD wKey);
MYFUNCTION MYRC MYPitchOn(MYBYTE n);
MYFUNCTION MYRC MYSetInputBuf(MYWORD *pwInputBuf);
MYFUNCTION MYRC MYSetSpellCode(MYBYTE bSpell);
MYFUNCTION MYRC MYSetCurCharIndex(MYBYTE bIndex);
MYFUNCTION MYRC MYSetMode(MYBYTE bMode);
MYFUNCTION MYRC MYSetCapsState(MYBYTE bStat);

MYFUNCTION MYWORD MYComponent2HZ(MYWORD wComponent);
MYFUNCTION MYBOOL MYIsComponent(MYWORD wCode);

MYFUNCTION MYRC MYEnableIntelligence(void);
MYFUNCTION MYRC MYDisableIntelligence(void);
MYFUNCTION MYRC MYDeleteUserEntry(MYBYTE n);
MYFUNCTION MYRC MYStartDefineWord(void);
MYFUNCTION MYRC MYEndDefineWord(void);

MYFUNCTION MYRC MYEnableCharSelect(void);
MYFUNCTION MYRC MYDisableCharSelect(void);

MYFUNCTION MYBYTE *MYGetUserDataPtr(MYDWORD *pdwLen);
MYFUNCTION MYRC MYSaveUserData(MYBYTE *pbUserData,MYDWORD dwLen);

MYFUNCTION MYRC MYGetCharInfo(MYWORD wChar,MYBYTE *pbKeybuf,MYBYTE *pbPinyinBuf,MYBYTE *pbKeyBufLen,MYBYTE bMode);
MYFUNCTION MYRC MYSearchList(MYListParam *pListParam);

MYFUNCTION MYRC MYZY2UCS(MYBYTE bZy);

MYFUNCTION MYWORD MYAsciiToUnicode(MYBYTE bCode);
#include "mmi_mae_resource.h"
MAE_Ret MYInitLangPack(void);
void MYFreeLangPack(void);
#endif
