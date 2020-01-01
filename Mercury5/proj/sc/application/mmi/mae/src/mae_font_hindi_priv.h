/**
 * \file    mae_font_thai.h
 * \brief   The document describes the interface of Thai font
 * \author  steve.lee@mstarsemi.com
 * @version $Id: mae_font_thai.h 1756 2009-09-10 14:13:56Z bill.pan $
 */
#ifndef __MAE_FONT_HINDI_PRIV_H__
#define __MAE_FONT_HINDI_PRIV_H__
	 
#ifdef __INDIC_FONT__

#ifdef __FEATURE_VECTOR_FONT__
#include "mae_le.h"
//#define __INDIC_FONT_RULE_CACHE__
#endif //__FEATURE_VECTOR_FONT__

#define __DVNG_FONT__
#define __BENGALI_FONT__
//#define __PUNJ_FONT__
//#define __GUJR_FONT__
//#define __ORYA_FONT__
#define __TAMIL_FONT__
#define __TELUGU_FONT__
//#define __KNDA_FONT__
//#define __MLYM_FONT__
//#define __SINH_FONT__

#define _HINDI_FILL_CLUSTER(_pCluster, _bufferSize, _clusterSize, _char, _consumed, _seq)\
{\
    if ( (_clusterSize) >= _bufferSize ) \
    {\
    break;\
    }\
    _pCluster[_clusterSize] = _char;\
    if ( _seq )\
    {\
    _seq[_clusterSize] = _clusterSize;\
    }\
    (_clusterSize)++;\
    (_consumed)++;\
}

#define _HINDI_VERLIFY_LEN(_pInputStr, _currentLen, _maxLen)\
{\
    if ( _currentLen >= _maxLen || (_FontHindiGetCharScript(_pInputStr[_currentLen]) >= HINDI_MAX_SCRIPT_NUM) )\
    {\
    break;\
    }\
}

enum
{
	HINDI_SCRIPT_DEVA,
	HINDI_SCRIPT_BENG,
	HINDI_SCRIPT_GUJR,
	HINDI_SCRIPT_ORYA,
	HINDI_SCRIPT_TAML,
	HINDI_SCRIPT_TELU,
	HINDI_SCRIPT_KNDA,
	HINDI_SCRIPT_MLYM,
	HINDI_SCRIPT_SINH,
	HINDI_MAX_SCRIPT_NUM
};
typedef u8 HindiScript_e;


#define _HindiLoclFeatureMask 0x80000000UL
#define _HindiNuktFeatureMask 0x40000000UL
#define _HindiAkhnFeatureMask 0x20000000UL
#define _HindiRphfFeatureMask 0x10000000UL
#define _HindiRkrfFeatureMask 0x08000000UL
#define _HindiBlwfFeatureMask 0x04000000UL
#define _HindiHalfFeatureMask 0x02000000UL
#define _HindiVatuFeatureMask 0x01000000UL
#define _HindiCjctFeatureMask 0x00800000UL
#define _HindiPresFeatureMask 0x00400000UL
#define _HindiAbvsFeatureMask 0x00200000UL
#define _HindiBlwsFeatureMask 0x00100000UL
#define _HindiPstsFeatureMask 0x00080000UL 
#define _HindiHalnFeatureMask 0x00040000UL
#define _HindiCaltFeatureMask 0x00020000UL
#define _HindiPrefFeatureMask 0x00010000UL
#define _HindiAbvmFeatureMask 0x00004000UL
#define _HindiBlwmFeatureMask 0x00002000UL
#define _HindiPstfFeatureMask 0x00001000UL
#define _HindiInitFeatureMask 0x00000800UL

#define _HindiPrivLeftJoinFeatureMask    0x00000001UL
#define _HindiPrivTwoPartJoinFeatureMask 0x00000002UL
#define _HindiPrivPreDottedFeatureMask   0x00000004UL
#define _HindiPrivPosDottedFeatureMask   0x00000008UL

enum
{
	HINDI_FEATURE_LOCL = 0,
	HINDI_FEATURE_NUKT = 1,
	HINDI_FEATURE_AKHN = 2,
	HINDI_FEATURE_RPHF = 3,
	HINDI_FEATURE_BLWF = 4,
	HINDI_FEATURE_HALF = 5,
	HINDI_FEATURE_VATU = 6,
	HINDI_FEATURE_PRES = 7,
	HINDI_FEATURE_BLWS = 8,
	HINDI_FEATURE_ABVS = 9,
	HINDI_FEATURE_PSTS = 10,
	HINDI_FEATURE_HALN = 11,
	HINDI_FEATURE_BLWM = 12,
	HINDI_FEATURE_ABVM = 13,
	HINDI_FEATURE_RKRF = 14,
	HINDI_FEATURE_CJCT = 15,
	HINDI_FEATURE_CALT = 16,
	HINDI_FEATURE_PSTF = 17,
	HINDI_FEATURE_INIT = 18,
	HINDI_FEATURE_PREF = 19,
	HINDI_MAX_FEATURE_NUM,
	HINDI_PRIV_FEATURE_LEFT_JOIN,
	HINDI_PRIV_FEATURE_TWOPART_JOIN,
	HINDI_PRIV_FEATURE_PRE_DOTTED,
	HINDI_PRIV_FEATURE_POS_DOTTED
};
typedef u8 HindiFeature_e;

typedef struct
{
    HindiFeature_e eTag;
    u32 u32Mask;
} HindiFeatureRecord_t;

typedef struct
{
    u16 *pu16OutCode;
    u16 u16ReturnLen;
    u32 *pau32Consumed;
    u32 u32FeatureTags;
} HindiCodeCachNode_t;

#define HINDI_OUT_SPLIT_ONE_TO_ONE    		0x01
#define HINDI_OUT_SPLIT_ALL_IN_ONE    		0x02
#define HINDI_OUT_SPLIT_ONE_TWO       		0x03
#define HINDI_OUT_SPLIT_TWO_ONE       		0x04
#define HINDI_OUT_SPLIT_ONE_THREE     		0x05
#define HINDI_OUT_SPLIT_TWO_TWO       		0x06
#define HINDI_OUT_SPLIT_THREE_ONE     		0x07
#define HINDI_OUT_SPLIT_ONE_ONE_TWO   		0x08
#define HINDI_OUT_SPLIT_TWO_ONE_ONE   		0x09
#define HINDI_OUT_SPLIT_TWO_THREE     		0x0A
#define HINDI_OUT_SPLIT_THREE_TWO     		0x0B
#define HINDI_OUT_SPLIT_ONE_ONE_THREE 		0x0C
#define HINDI_OUT_SPLIT_ONE_ONE_TWO_ONE 	0x0D
#define HINDI_OUT_SPLIT_ONE_ONE_FOUR  		0x0E
#define HINDI_OUT_SPLIT_ONE_ONE_ONE_THREE 	0x0F

#define HINDI_CONVERT_MAX 15
	 
enum
{ 
	HINDI_INVALID	 = 0x00,
	HINDI_CON		 = 0x01,
	HINDI_INDVOW	 = 0x02,
	HINDI_DEPVOW	 = 0x03,
	HINDI_SIGN 	 	 = 0x04,
	HINDI_NUM		 = 0x05,
	HINDI_HALANT	 = 0x06
};
typedef u8 HindiCharacter_e;

	 
enum
{ 
	HINDI_SP_INVALID				 = 0x00,
	HINDI_SP_LEFT_JOINER             = 0x10,
	HINDI_SP_RIGHT_JOINER            = 0x20,
	HINDI_SP_TWOPART_JOINER          = 0x30,
	HINDI_SP_CENTER_T				 = 0x40,
	HINDI_SP_RIGHT_T				 = 0x50,
	HINDI_SP_DOUBLE_T				 = 0x60,
	HINDI_SP_NO_T                    = 0x70,
	HINDI_SP_SINGLE_INDVOW 		     = 0x80,
	HINDI_SP_CENTER_T_UP_POS		 = 0x90,
	HINDI_SP_CENTER_T_DOWN_POS		 = 0xA0,
	HINDI_SP_LEFT_T_UP_POS			 = 0xB0,
	HINDI_SP_LEFT_T_DOWN_POS         = 0xC0,
	HINDI_SP_RIGHT_T_DOWN_POS		 = 0xD0,
	HINDI_SP_RIGHT_POS				 = 0xE0,
};
typedef u8 HindiSpecialCharacter_e;

typedef enum
{
    HINDI_OTYPE_INVALID				  = 0x00,
	HINDI_OTYPE_DEPVOW_LONG_DOWN_CHAR = 0x01,
	HINDI_OTYPE_CON_SMALL_CHAR        = 0x02
}HindiOtherCharacterType_e;
	 
typedef enum
{ 
	HINDI_ORDER_CRA_SHALANT = 0,
	HINDI_ORDER_DVI,
	HINDI_ORDER_CON_DEPVOW,
	HINDI_ORDER_CON_SHALANT,
	HINDI_ORDER_ZWJ_SHALANT,
	HINDI_ORDER_TWOPART_DEPVOW
}HindiOrderType_e;
	 
typedef struct
{
	u8 u8IsFitMatch;/* transfer when all input string matched*/
	u8 u8InputLen; /*no. of input unicode values*/
	u8 u8OutputLen; /*no, of output values*/
	u8 u8SplitType;
	u16 u16InputGlyph[HINDI_CONVERT_MAX]; /*no. of input glyph used to make conjunct */
	u16 u16OutputGlyph[HINDI_CONVERT_MAX];/*no. of output glyph that has to be rendered */
} HindiGlyphInfo_t;
	 
typedef struct
{
	const HindiGlyphInfo_t *psGlyphinfo;/*pointer to individual table*/
	u16 u16Size;/* size of individual character's array*/
	u8 u8MaxInputGlyphSize;/*max input of glyph it can handle*/
} HindiMainTable_t ;
	 
typedef struct
{
	const HindiMainTable_t *pMainTable;
	const u8 *pCharTypes;
} HindiLangTable_t;

typedef u16 (*pfnGetCluster)( HindiScript_e eScript, const u16 *pu16Txt, u32 u32InLen, u16 *pu16Cluster, u16 u16BufferSize, u16 *pu16ConsumedCount, u16 *pu16SeqInCluster, boolean bIsDispStr, u32 *pu32FeatureTags );
typedef u16 (*pfnRefineCluster)( HindiScript_e eScript, const u16 *pu16InTxt, u32 u32InLen, u32 u32Offset, u16 *pu16Cluster, u16 *pu16CluserSize, u16 u16ClusterOffset, boolean bIsDispStr, u32 *pu32Features, const u16 *pu16OriginTxt, u32 u32OriginOffset);
typedef boolean (*pfnGetNextCodeXOffset)(u16 *pu16CurrentRefChar, u16 *pu16CurrentCharRefWidth, u16 u16NextChar, u16 u16NextCharWidth, s16 *ps16XOffset, u16 u16BaseWidth, u16 u16PreChar, boolean bFirstCharInCluster);
typedef boolean (*pfnCharIsPrivUpRA)(u16 u16Character);
typedef boolean (*pfnCharIsPrivHalfRA)(u16 u16Character);
typedef boolean (*pfnCharIsRA)(u16 u16Character);
typedef boolean (*pfnCharIsHalant)(u16 u16Character);
typedef boolean (*pfnCharIsNukta)(u16 u16Character);
typedef boolean (*pfnCharIsBindu)(u16 u16Character);
typedef boolean (*pfnCharWithNukta)(u16 u16Character);
typedef boolean (*pfnCharIsNoHalfCon)(u16 u16Character);
typedef boolean (*pfnCharIsFollowingZWJ)(u16 u16Character);
typedef u16 (*pfnGetTwoWordLeftChar)(u16 u16Character);
typedef u16 (*pfnGetTwoWordRightChar)(u16 u16Character);
typedef HindiCharacter_e (*pfnGetCharType)(u16 u16Character);
typedef HindiSpecialCharacter_e (*pfnGetCharSpecialType)(u16 u16Character);
typedef HindiOtherCharacterType_e (*pfnGetCharOtherType)(u16 u16Character);
typedef boolean (*pfnCharIsBlwf)(u16 u16FirstChar, u16 u16SecondChar);
typedef boolean (*pfnCharIsPstf)(u16 u16FirstChar, u16 u16SecondChar);
typedef boolean (*pfnCharIsLigated)(u16 u16FirstChar, u16 u16SecondChar, boolean withZWJ);
typedef const HindiMainTable_t* (*pfnGetCharRuleTable)(u16 u16Character);
typedef boolean (*pfnReplaceOutputChar)(u16 *pu16Cluster, u16 u16ClusterSize, u16 u16ClustIndex, u16 *pu16Index, u16 u16MatchedLen, u16 *pu16RemainSize, u16 *pu16OutGlyph, u16 *pu16OutGlyphLen, u16 u16OffsetInConcatenation, u16 *pu16OffsetInConcatenation, u16 *pu16OffsetInComposed, u16 *pu16ConcatenationComposedSize);
typedef u32 (*pfnSetFeature)(u32 u32FeatureTags, HindiFeature_e eFeature);
typedef u16 (*pfnGetFeatureMap)(const HindiFeatureRecord_t **ppasFeatureMap);
typedef boolean (*pfnStrWithAkhand)(u16 *pu16Str, u32 u32StrLen, u16 u16Offset);

typedef boolean (*pfnCharIsSign)(u16 u16Character);
typedef boolean (*pfnCharIsComposed)(u16 u16Character);
typedef u16 (*pfnGetBaseWidthChar)(void);
typedef boolean (*pfnFeatureWithRphf)( u32 u32FeatureTags, HindiSpecialCharacter_e *peSpType );
typedef boolean (*pfnFeatureWithBlwf)( u32 u32FeatureTags, HindiSpecialCharacter_e *peSpType );

typedef	struct
{
	HindiScript_e eScript;
	u16 u16FirstChar;
    u16 u16LastChar;
    u16 u16PrivFirstChar;
	u16 u16PrivLastChar;
    pfnGetCluster fnGetCluster;
    pfnRefineCluster fnRefineCluster;
	pfnGetNextCodeXOffset fnGetNextCodeXOffset;
	pfnCharIsPrivUpRA fnCharIsPrivUpRA;
	pfnCharIsPrivHalfRA fnCharIsPrivHalfRA;
	pfnCharIsRA fnCharIsRA;
	pfnCharIsHalant fnCharIsHalant;
	pfnCharIsNukta fnCharIsNukta;
	pfnCharIsBindu fnCharIsBindu;
	pfnCharWithNukta fnCharWithNukta;
	pfnCharIsNoHalfCon fnCharIsNoHalfCon;
	pfnCharIsFollowingZWJ fnCharIsFollowingZWJ;
	pfnGetTwoWordLeftChar fnGetTwoWordLeftChar;
	pfnGetTwoWordRightChar fnGetTwoWordRightChar;
	pfnGetCharType fnGetCharType;
	pfnGetCharSpecialType fnGetCharSpecialType;
	pfnGetCharOtherType fnGetCharOtherType;
	pfnCharIsBlwf fnCharIsBlwf;
	pfnCharIsPstf fnCharIsPstf;
	pfnCharIsLigated fnCharIsLigated;
	pfnGetCharRuleTable fnGetCharRuleTable;
	pfnReplaceOutputChar fnReplaceOutputChar;
	pfnStrWithAkhand fnStrWithAkhand;
	pfnSetFeature fnSetFeature;
	pfnGetFeatureMap fnGetFeatureMap;
	pfnCharIsSign fnCharIsSign;
	pfnCharIsComposed fnCharIsComposed;
	pfnGetBaseWidthChar fnGetBaseWidthChar;
	pfnFeatureWithRphf fnStrWithRphf;
	pfnFeatureWithBlwf fnStrWithBlwf;
} HindiTable_t;
	 
u16 _FontHindiRules( HindiScript_e eScript, u16 *pu16Cluster, u16 u16ClusterSize, u16 u16ClustIndex, u16 *pu16Glyph, u16 *pu16OffsetInConcatenation, u16 *pu16OffsetInComposed, u16 *pu16ConcatenationComposedSize, u32 *pu32Features );
u16 _FontHindiGetClusterStartOffset(HindiScript_e eScript, const u16 *pu16InTxt, u32 u32InLen, u32 u32Offset, u16 *pu16Cluster, u16 *pu16CluserSize, boolean bIsDispStr, u32 *pu32FeatureTags );
u16 _FontHindiRefineCluster( HindiScript_e eScript, const u16 *pu16InTxt, u32 u32InLen, u32 u32Offset, u16 *pu16Cluster, u16 *pu16CluserSize, u16 u16ClusterOffset, boolean bIsDispStr, u32 *pu32Features, const u16 *pu16OriginTxt, u32 u32OriginOffset);
u16 _FontHindiGetNextCodes( HindiScript_e eScript, const u16 *pu16InTxt, u32 u32InLen, u32 u32Offset, u32 u32SubLen, u16 *pu16OutCode, u32 u32OutLen, u32 *pu32Consumed, boolean bIsDispStr, u32 *pu32Features, const u16 *pu16OriginTxt, u32 u32OriginOffset);
boolean _FontHindiGetNextCodeXOffset( HindiScript_e eScript, u16 *pu16CurrentRefChar, u16 *pu16CurrentCharRefWidth, u16 u16NextChar, u16 u16NextCharWidth, s16 *ps16XOffset, u16 u16BaseWidth, u16 u16PreChar, boolean bFirstCharInCluster);
boolean _FontHindiGetCodeDrawWidth( HindiScript_e eScript, u32 nLen, u16 u16Character, u16 u16CharWidth, u16 u16NextChar, u16 u16BaseWidth, u16 *pu16Width );
boolean _FontHindiReorderStr( HindiScript_e eScript, const u16 *pu16Str, u16 u16StrLen, u16 u16StrIndex, const u16 *pu16Seq, u16 **ppu16OrderSeg, u16 *pu16InOrderOffset, boolean bIsDispStr );
boolean _FontHindiNextComposedChars( HindiScript_e eScript, const u16 *pString, u32 nStrLen, u32 nOffset, u16 *pwComposedStr, u32 *pComposedLen, u32 *paConsumed, boolean bDispStr, u16 u16OutBufferSize );
boolean _FontHindiPreComposedChars( HindiScript_e eScript, const u16 *pString, u32 nStrLen, u32 nOffset, u16 *pwComposedStr, u32 *pComposedLen, u32 *paConsumed, boolean bDispStr, u16 u16OutBufferSize );
boolean _FontHindiClusterIsOrderingString( const u16 *pu16String, u16 u16StrLen );
boolean _FontHindiStrWithUpRA( HindiScript_e eScript, u16 *pu16Str, u32 nStrLen );
HindiScript_e _FontHindiGetCharScript( u16 u16Character );
boolean _FontHindiFeatureWithLJoin( HindiScript_e eScript, u32 u32FeatureTags, boolean *pIsTwoPart );
boolean _FontHindiFeatureWithDotted( HindiScript_e eScript, u32 u32FeatureTags, boolean *pIsPreDotted );
const HindiMainTable_t* _FontHindiGetCharRuleTable( HindiScript_e eScript, u16 u16Char );

#ifdef __FEATURE_VECTOR_FONT__
boolean _FontHindiVectorGetNextOffset( HindiScript_e eScript, u16 *pu16InGlyphs, u16 u16GlyphLen, u16 u16NextOffset, u16 *pu16BaseOffset, s16 *ps16XOffset, u32 u32FeatureTags );
#endif //__FEATURE_VECTOR_FONT__

/*=======================================================*/
/*================Common porting functions======================*/
/*=======================================================*/
boolean _FontHindiCharIsSign( HindiScript_e eScript, u16 u16Character );
boolean _FontHindiCharIsComposed( HindiScript_e eScript, u16 u16Character );
u16 _FontHindiGetBaseWidthChar( HindiScript_e eScript );
boolean _FontHindiFeatureWithRphf( HindiScript_e eScript, u32 u32FeatureTags, HindiSpecialCharacter_e *peSpType );
boolean _FontHindiFeatureWithBlwf( HindiScript_e eScript, u32 u32FeatureTags, HindiSpecialCharacter_e *peSpType );

#endif //__INDIC_FONT__
#endif /* __MAE_FONT_HINDI_PRIV_H__ */
