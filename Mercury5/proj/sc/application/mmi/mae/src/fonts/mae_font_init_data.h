#ifndef _SUPPORT_FONT_CUS_

#ifdef __MAE_FONT_BASE_C__

#ifndef WIN32
#if defined(__arm__) && defined(__ARMCC_VERSION)
	#define __MAE_ALIGN(_n_) __align(_n_)
#elif defined(__GNUC__)
	#define __MAE_ALIGN(_n_) __attribute__ ((aligned (_n_)))
#else
	#define __MAE_ALIGN(_n_)
#endif
#else
	#define __MAE_ALIGN(_n_)
#endif

__MAE_ALIGN(4)
//static const u8 _font_supersmall_en[] =
static const u8 _nFontSupersmallEn[]=
{
	#include "mae_font_en_supersmall.h"
};

__MAE_ALIGN(4)
//static const u8 _font_supersmall_ch[] =
static const u8 _nFontSupersmallCh[] =
{
	#include "mae_font_ch_supersmall.h"
};

__MAE_ALIGN(4)
//static const u8 _font_small_en[] =
static const u8 _nFontSmallEn[] =
{
	#include "mae_font_en_small.h"
};

__MAE_ALIGN(4)
//static const u8 _font_normal_en[] =
static const u8 _nFontNormalEn[] =
{
	#include "mae_font_en_normal.h"
};

__MAE_ALIGN(4)
//static const u8 _font_normal_ch[] =
static const u8 _nFontNormalCh[] =
{
	#include "mae_font_ch_normal.h"
};

__MAE_ALIGN(4)
//static const u8 _font_normal_ime[] =
static const u8 _nFontNormalIme[] =
{
	#include "mae_font_ch_zi8.h"
};

__MAE_ALIGN(4)
//static const u8 _font_supersmall_ime[] =
static const u8 _nFontSupersmallIme[] =
{
	#include "mae_font_ch_zi8.h"
};

__MAE_ALIGN(4)
//static const u8 _font_superlarge_num[] =
static const u8 _nFontSuperlargeNum[] =
{
	#include "mae_font_num_superlarge.h"
};

__MAE_ALIGN(4)
//static const u8 _font_superlarge_numsym[] =
static const u8 _FontSuperLargeNumSys[] =
{
	#include "mae_font_numsym_superlarge.h"
};

__MAE_ALIGN(4)
//static const u8 _font_large_num[] =
static const u8 _nFontLargeNum[] =
{
	#include "mae_font_num_large.h"
};

__MAE_ALIGN(4)
//static const u8 _font_large_numsym[] =
static const u8  _nFontLargeNumSys[] =
{
	#include "mae_font_numsym_large.h"
};

__MAE_ALIGN(4)
//static const u8 _font_normal_num[] =
static const u8 _nFontNormalNum[] =
{
	#include "mae_font_num_normal.h"
};

__MAE_ALIGN(4)
//static const u8 _font_normal_numsym[] =
static const u8 _nFontNormalNumSys[] =
{
	#include "mae_font_numsym_normal.h"
};

__MAE_ALIGN(4)
//static const u8 _font_small_num[] =
static const u8 _nFontSmallNum[] =
{
	#include "mae_font_num_small.h"
};

__MAE_ALIGN(4)
//static const u8 _font_supersmall_num[] =
static const u8 _nFontSupersmallNum[] =
{
	#include "mae_font_num_supersmall.h"
};

__MAE_ALIGN(4)
//static const u8 _font_supersmall_numsym[] =
static const u8 _nFontSupersmallNumSys[] =
{
	#include "mae_font_numsym_supersmall.h"
};

__MAE_ALIGN(4)
//static const u8 _font_normal_symbol[] =
static const u8 _nFontNormalSymbol[] =
{
	#include "mae_font_symbol_normal.h"
};

__MAE_ALIGN(4)
//static const u8 _font_supersmall_symbol[] =
static const u8 _nFontSupersmallSymbol[] =
{
	#include "mae_font_symbol_supersmall.h"
};

__MAE_ALIGN(4)
//static const u8 _font_small_date[] =
static const u8 _nFontSmallDate[] =
{
	#include "mae_font_ch_date.h"
};

__MAE_ALIGN(4)
//static const u8 _font_supersmall_date[] =
static const u8 _nFontSupersmallDate[] =
{
	#include "mae_font_ch_date_supersmall.h"
};

//small font
//static const u8* aSmall[] =
static const u8* _pSmall[] =
{
	_nFontSmallEn,        //_font_small_en,
	_nFontNormalCh,     //_font_normal_ch,
	_nFontNormalSymbol //_font_normal_symbol,
};

// normal font
//static const u8* aNormal[] =
static const u8* _pNormal[] =
{
	_nFontNormalEn,     //_font_normal_en,
	_nFontNormalCh,     //_font_normal_ch,
	_nFontNormalIme,    //_font_normal_ime,
	_nFontNormalSymbol  //_font_normal_symbol,
};

// large font
//static const u8* aLarge[] =
static const u8* _pLarge[] =
{
	_nFontLargeNum,     //_font_large_num,
	_nFontLargeNumSys   //_font_large_numsym,
};

// super small font
//static const u8* aSuperSmall[] =
static const u8* _pSuperSmall[] =
{
	_nFontSupersmallEn,         //_font_supersmall_en,
	_nFontSupersmallCh,         //_font_supersmall_ch,
	_nFontSupersmallSymbol,  //_font_supersmall_symbol,
	_nFontSupersmallDate       //_font_supersmall_date,
};

// ime normal font
//static const u8* aIMENormal[] =
static const u8* _pImeNormal[] =
{
	_nFontNormalIme,    //_font_normal_ime,
};

// ime supersmall font
//static const u8* aIMESuperSmall[] =
static const u8* _pImeSupersmall[] =
{
	_nFontSupersmallIme,    //_font_supersmall_ime,
};

// datd small font
//static const u8* aDateSmall[] =
static const u8* _pDateSmall[] =
{
	_nFontSmallEn, //_font_small_en,
	_nFontSmallDate //_font_small_date,
};

// number super larget font
//static const u8* aNumSuperLarge[] =
static const u8* _pNumSuperLarge[] =
{
	_nFontSuperlargeNum, //_font_superlarge_num,
	_nFontSupersmallNumSys //_font_superlarge_numsym,
};

// number larget font
//static const u8* aNumLarge[] =
static const u8* _pNumLarge[] =
{
	_nFontLargeNum //_font_large_num,
	_nFontLargeNumSys, //_font_large_numsym,
};

// number normal font
//static const u8* aNumNormal[] =
static const u8* _pNumNormal[] =
{
	_nFontNormalNum, //_font_normal_num,
	_nFontNormalNumSys, //_font_normal_numsym,
};

// number small font
//static const u8* aNumSmall[] =
static const u8* _pNumSmall[] =
{
	_nFontSmallNum //_font_small_num
};

// number small font
//static const u8* aNumSuperSmall[] =
static const u8* _pNumSuperSmall[] =
{
	_nFontSupersmallNum, //_font_supersmall_num,
	_nFontSupersmallNumSys //_font_supersmall_numsym
};


////
// all categories
typedef struct
{
	const u8** ppFonts;
	const u8   nCount;
}CatInitData_t;

static const CatInitData_t aCat[] =
{
	{_pSmall, sizeof(_pSmall)/sizeof(u8*)},
	{_pNormal, sizeof(_pNormal)/sizeof(u8*)},
	{_pLarge, sizeof(_pLarge)/sizeof(u8*)},
	{_pSuperSmall,sizeof(_pSuperSmall)/sizeof(u8*)},
//	{_pImeNormal,sizeof(_pImeNormal)/sizeof(u8*)},
//	{_pImeSuperSmall,sizeof(_pImeSuperSmall)/sizeof(u8*)},
	{_pDateSmall,sizeof(_pDateSmall)/sizeof(u8*)},
	{_pNumSuperLarge,sizeof(_pNumSuperLarge)/sizeof(u8*)},
	{_pNumLarge,sizeof(_pNumLarge)/sizeof(u8*)},
	{_pNumNormal,sizeof(_pNumNormal)/sizeof(u8*)},
	{_pNumSmall,sizeof(_pNumSmall)/sizeof(u8*)},
	{_pNumSuperSmall,sizeof(_pNumSuperSmall)/sizeof(u8*)}
};

#endif /* __MAE_FONT_C__ */
#endif /* _SUPPORT_FONT_CUS_ */ 
