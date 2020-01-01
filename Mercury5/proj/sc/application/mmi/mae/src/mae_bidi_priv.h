/**
 * \file    mae_font_arabic_priv.h
 * \brief   The document describes the private data structure used in mae_font_arabic.c
 *
 * @version
 */

#ifndef __MAE_BIDI_PRIV_H__
#define __MAE_BIDI_PRIV_H__

#include "mmi_mae_common_def.h"

typedef enum
{
    // input types
    BIDI_ON = 0,  // Other Neutral
    BIDI_L,       // Left Letter
    BIDI_R,       // Right Letter
    BIDI_AN,      // Arabic Number
    BIDI_EN,      // European Number
    BIDI_AL,      // Arabic Letter (Right-to-left)
    BIDI_NSM,     // Non-spacing Mark
    BIDI_CS,      // Common Separator
    BIDI_ES,      // European Separator
    BIDI_ET,      // European Terminator (post/prefix e.g. $ and %)

    // resolved types
    BIDI_BN,      // Boundary neutral (type of RLE etc after explicit levels)

    // input types
    BIDI_S,       // Segment Separator (TAB)  // used only in L1
    BIDI_WS,      // White space              // used only in L1
    BIDI_B,       // Paragraph Separator (aka as PS)

    // types for explicit controls
    BIDI_RLO,     // these are used only in X1-X9
    BIDI_RLE,
    BIDI_LRO,
    BIDI_LRE,
    BIDI_PDF,

    // resolved types, also resolved directions
    BIDI_N = BIDI_ON  // alias, where ON, WS and S are treated the same
} Bidi_CharType_e;

//Possible states
typedef enum
{
    BIDI_WEAK_XA,  //  arabic letter
    BIDI_WEAK_XR,  //  right letter
    BIDI_WEAK_XL,  //  left letter

    BIDI_WEAK_AO,  //  arabic letter followed by ON
    BIDI_WEAK_RO,  //  right letter followed by ON
    BIDI_WEAK_LO,  //  left letter followed by ON

    BIDI_WEAK_RT,  //  ET following R
    BIDI_WEAK_LT,  //  ET following L

    BIDI_WEAK_CN,  //  EN, AN following AL
    BIDI_WEAK_RA,  //  arabic number followed R
    BIDI_WEAK_RE,  //  european number followed R
    BIDI_WEAK_LA,  //  arabic number followed L
    BIDI_WEAK_LE,  //  european number followed L

    BIDI_WEAK_AC,  //  CS following cn
    BIDI_WEAK_RC,  //  CS following ra (right arabic (NxA))
    BIDI_WEAK_RS,  //  CS,ES following re
    BIDI_WEAK_LC,  //  CS following la (left arabic (AxN))
    BIDI_WEAK_LS,  //  CS,ES following le

    BIDI_WEAK_RET, //  ET following re
    BIDI_WEAK_LET  //  ET following le
} Bidi_WeakState_e;

// state values
typedef enum
{
    // new temporary class
    BIDI_NEUTRAL_R,  // R and characters resolved to R
    BIDI_NEUTRAL_L,  // L and characters resolved to L
    BIDI_NEUTRAL_RN, // N preceded by right
    BIDI_NEUTRAL_LN, // N preceded by left
    BIDI_NEUTRAL_A,  // AN preceded by left (the abbrev 'la' is used up above)
    BIDI_NEUTRAL_NA  // N preceeded by a
} Bidi_NeutralState_e;

#define BIDI_LEVEL_MAX_SIZE      61

// possible actions

// primitives
#define BIDI_WEAK_ACT_IX 0x100   // increment
#define BIDI_WEAK_ACT_XX 0xF     // no-op

// actions
#define BIDI_WEAK_ACT_XXX  ((BIDI_WEAK_ACT_XX << 4) + BIDI_WEAK_ACT_XX) // no-op
#define BIDI_WEAK_ACT_XIX  ((BIDI_WEAK_ACT_IX) + BIDI_WEAK_ACT_XXX)     // increment run
#define BIDI_WEAK_ACT_XXN  ((BIDI_WEAK_ACT_XX << 4) + BIDI_ON)          // set current to N
#define BIDI_WEAK_ACT_XXE  ((BIDI_WEAK_ACT_XX << 4) + BIDI_EN)          // set current to EN
#define BIDI_WEAK_ACT_XXA  ((BIDI_WEAK_ACT_XX << 4) + BIDI_AN)          // set current to AN
#define BIDI_WEAK_ACT_XXR  ((BIDI_WEAK_ACT_XX << 4) + BIDI_R)           // set current to R
#define BIDI_WEAK_ACT_XXL  ((BIDI_WEAK_ACT_XX << 4) + BIDI_L)           // set current to L
#define BIDI_WEAK_ACT_NXX  ((BIDI_ON << 4) + 0xF)                       // set run to neutral
#define BIDI_WEAK_ACT_AXX  ((BIDI_AN << 4) + 0xF)                       // set run to AN
#define BIDI_WEAK_ACT_EXE  ((BIDI_EN << 4) + BIDI_EN)                   // set run to EN, set current to EN
#define BIDI_WEAK_ACT_NIX  ((BIDI_ON << 4) + 0xF + BIDI_WEAK_ACT_IX)    // set run to N, increment
#define BIDI_WEAK_ACT_NXN  ((BIDI_ON << 4) + BIDI_ON)                   // set run to N, set current to N
#define BIDI_WEAK_ACT_NXR  ((BIDI_ON << 4) + BIDI_R)                    // set run to N, set current to R
#define BIDI_WEAK_ACT_NXE  ((BIDI_ON << 4) + BIDI_EN)                   // set run to N, set current to EN

#define BIDI_WEAK_ACT_AXA  ((BIDI_AN << 4) + BIDI_AN)                   // set run to AN, set current to AN
#define BIDI_WEAK_ACT_NXL  ((BIDI_ON << 4) + BIDI_L)                    // set run to N, set current to L
#define BIDI_WEAK_ACT_LXL  ((BIDI_L << 4) + BIDI_L)                     // set run to L, set current to L

// action to resolve previous input
#define BIDI_NEUTRAL_ACT_NL  (BIDI_L)                 // resolve EN to L
#define BIDI_NEUTRAL_ACT_EN  (3 << 4)                 // resolve neutrals run to embedding level direction
#define BIDI_NEUTRAL_ACT_RN  (BIDI_R << 4)            // resolve neutrals run to strong right
#define BIDI_NEUTRAL_ACT_LN  (BIDI_L << 4)            // resolved neutrals run to strong left
#define BIDI_NEUTRAL_ACT_IN  (1 << 8)                 // increment count of deferred neutrals
#define BIDI_NEUTRAL_ACT_LNL ((BIDI_L << 4) + BIDI_L) // set run and EN to L

typedef struct
{
    boolean bRight2Left;
    u32 nOffset;
    u32 nLength;
} Bidi_LineData_t;

typedef struct
{
    u32 nMaxLines;
    u32 nLines;
} Bidi_TableData_t;

typedef struct
{
    Bidi_TableData_t tTableInf;
    Bidi_LineData_t *pLines;
 } Bidi_LineTable_t;

typedef struct
{
    MAE_WChar *pOrderStr;
    u16 *pLogicalPosInLine;
    u8 *pCharLevel;
    u32 nStrLen;
    boolean bUserTable;
    boolean bIsDisplayRTL;
    Bidi_LineTable_t *pLineTable;
} Bidi_Handler_t;

#define BIDI_GET_LINE( _pTable_,_i_ ) (((Bidi_LineData_t *)&((_pTable_)->pLines)) + _i_)

#ifdef __BIDI_TEXT__
static void _BidiConvertCharType( MAE_WChar *pString, u16 *pCharTypes, u32 *pStrLen, boolean bReportWsType );
static void _BidiResolveExplicit( u8 nBaseLevel, u16 *pCharTypes, u8 *pCharLevels, u32 nStrLen );
static void _BidiResolveWeak( u8 u8Baselevel, u16 *pCharTypes, u8 *pCharLevels, u32 nStrLen );
static void _BidiResolveNeutrals( u8 u8Baselevel, u16 *pCharTypes, u8 *pCharLevels, u32 nStrLen );
static void _BidiResolveImplicit( u16 *pCharTypes, u8 *pCharLevels, u32 nStrLen );
static void _BidiOrderLine( MAE_WChar *pString, u16 *pCharTypes, u8 *pCharLevels, u16 *pu16LogicPos, u32 nStrLen, u8 nBaseLevel );
static void _BidiResolveWhitespace( u8 nBaseLevel, u16 *pCharTypes, u8 *pCharLevels, u32 nStrLen );
static void _BidiMirrorStr( MAE_WChar *pString, u8 *pCharLevels, u32 nStrLen );
static boolean _BidiDoMirror( MAE_WChar *pChar, s32 nStartIndex, s32 nEndIndex );
static u32 _BidiReorderLevel( u8 nLevel, MAE_WChar *pText, u8 *pCharlevels, u32 nStrLen, u32 nOffset, u32 nSubLen, boolean bReverse, u16 *pRealPos );
static void _BidiOrderCharLevel( u16 *pPosInLine, u32 u32Len, u8 *pCharLevels );
static Bidi_CharType_e _BidiGetCharType( MAE_WChar wChar, boolean bReportWsType );
#endif //__BIDI_TEXT__

static boolean _BidiOrderString( MAE_WChar *pString, u16 *pPosInLine, u32 nOffset, u32 nSubStrLen, boolean bRight2Left, Bidi_LineTable_t *pTable, u32 *pStartIndex, u32 *pStartOffset, u8 **ppCharLevel );
static void _BidiInitLogicalPos( u16 *pStrPos, u32 nStrLen );
__SLDPM_FREE__ static Bidi_LineTable_t* _BidiTableAlloc( u32 nLineSize );
static void _BidiTableFree( Bidi_LineTable_t *pLineTable );
static boolean _BidiTableAddLine( Bidi_LineTable_t **ppLineTable, u32 nOffset, u32 nSubLen, boolean bRight2Left );
static void _BidiTableDefaultMeasureLines( Bidi_LineTable_t **ppTable, MAE_WChar *pString, u32 u16StrLen, boolean bRight2Left );
__SLDPM_FREE__ static u32 _BidiResolveParagraph( const MAE_WChar *pString, u32 nStrLen, u32 nOffset );

#endif //__MAE_BIDI_PRIV_H__
