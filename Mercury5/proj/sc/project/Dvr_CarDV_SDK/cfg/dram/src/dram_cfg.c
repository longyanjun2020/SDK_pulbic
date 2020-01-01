//==============================================================================
//
//  File        : dram_cfg.c
//  Description : dram configure file
//  Author      : Rony Yeh
//  Revision    : 1.0
//==============================================================================


//==============================================================================
//
//                              INCLUDE FILE
//
//==============================================================================
#include "dram_cfg.h"

//==============================================================================
//
//                              Definition
//
//==============================================================================

//==============================================================================
//
//                              Global VARIABLES
//
//==============================================================================
#if (DRAM_ID == DRAM_DDR)
//MMP_ULONG   DRAMID = DRAMID1;
//MMP_ULONG   SEARCH_DLY_UPBD = SEARCH_DLY_UPBD_DDR1;
//MMP_ULONG   SEARCH_DLY_STEP = SEARCH_DLY_STEP_DDR1;
//MMP_ULONG   SEARCH_DLY_SUB_STEP = SEARCH_DLY_SUB_STEP_DDR1;
//MMP_ULONG   USE_LGT_DDR3_SETTING = USE_LGT_DDR3_SETTING_DDR1;
const MMPF_DRAM_SETTINGS m_DramSettings =
{
#ifdef MCR_V2_32MB
    DRAM_SIZE_32_MB,	//	    MMP_ULONG DRAM_SIZE;
#else
    DRAM_SIZE_64_MB,	//	    MMP_ULONG DRAM_SIZE;
#endif
    (0x00000200),		//	    MMP_ULONG SEARCH_DLY_UPBD;
    (0x00000000),		//	    MMP_ULONG SEARCH_DLY_LOWBD;
    (0x00000020),		//	    MMP_ULONG SEARCH_DLY_STEP;
    (0x00000010),		//	    MMP_ULONG SEARCH_DLY_SUB_STEP;
    DRAM_DDR,			//	    MMP_UBYTE DRAMID;
    (21),				//	    MMP_UBYTE SEARCH_DQDLY_NUM;
    (0x00),				//	    MMP_UBYTE USE_LGT_DDR3_SETTING;
    (0),				//	    MMP_UBYTE SEARCH_EARLY_STOP;
};
#elif (DRAM_ID == DRAM_DDR2)
//MMP_ULONG   DRAMID = DRAMID2;
//MMP_ULONG   SEARCH_DLY_UPBD = SEARCH_DLY_UPBD_DDR2;
//MMP_ULONG   SEARCH_DLY_STEP = SEARCH_DLY_STEP_DDR2;
//MMP_ULONG   SEARCH_DLY_SUB_STEP = INVALIDATEVALUE;
//MMP_ULONG   USE_LGT_DDR3_SETTING = USE_LGT_DDR3_SETTING_DDR2;
const MMPF_DRAM_SETTINGS m_DramSettings =
{
    DRAM_SIZE_128_MB,	//	    MMP_ULONG DRAM_SIZE;
    (0x00000100),		//	    MMP_ULONG SEARCH_DLY_UPBD;
    (0x00000000),		//	    MMP_ULONG SEARCH_DLY_LOWBD;
    (0x00000008),		//	    MMP_ULONG SEARCH_DLY_STEP;
    INVALIDATEVALUE,	//	    MMP_ULONG SEARCH_DLY_SUB_STEP;
    DRAM_DDR2,			//	    MMP_UBYTE DRAMID;
    (21),				//	    MMP_UBYTE SEARCH_DQDLY_NUM;
    (0x00),				//	    MMP_UBYTE USE_LGT_DDR3_SETTING;
    (0),				//	    MMP_UBYTE SEARCH_EARLY_STOP;
};
#elif (DRAM_ID == DRAM_DDR3)
const MMPF_DRAM_SETTINGS m_DramSettings =
{
    DRAM_SIZE_128_MB,	//	    MMP_ULONG DRAM_SIZE;
    (0x00000100),		//	    MMP_ULONG SEARCH_DLY_UPBD;
    (0x00000000),		//	    MMP_ULONG SEARCH_DLY_LOWBD;
    (0x00000008),		//	    MMP_ULONG SEARCH_DLY_STEP;
    INVALIDATEVALUE,	//	    MMP_ULONG SEARCH_DLY_SUB_STEP;
    DRAM_DDR3,			//	    MMP_UBYTE DRAMID;
    (21),				//	    MMP_UBYTE SEARCH_DQDLY_NUM;
    (0x01),				//	    MMP_UBYTE USE_LGT_DDR3_SETTING;
    (0),				//	    MMP_UBYTE SEARCH_EARLY_STOP;
};
#else
//MMP_ULONG   DRAMID = DRAMIDNA;
//MMP_ULONG   SEARCH_DLY_UPBD = INVALIDATEVALUE;
//MMP_ULONG   SEARCH_DLY_STEP = INVALIDATEVALUE;
//MMP_ULONG   SEARCH_DLY_SUB_STEP = INVALIDATEVALUE;
//MMP_ULONG   USE_LGT_DDR3_SETTING = INVALIDATEVALUE;
const MMPF_DRAM_SETTINGS m_DramSettings =
{
    INVALIDATEVALUE,	//	    MMP_ULONG DRAM_SIZE;
    INVALIDATEVALUE,	//	    MMP_ULONG SEARCH_DLY_UPBD;
    INVALIDATEVALUE,	//	    MMP_ULONG SEARCH_DLY_LOWBD;
    INVALIDATEVALUE,	//	    MMP_ULONG SEARCH_DLY_STEP;
    INVALIDATEVALUE,	//	    MMP_ULONG SEARCH_DLY_SUB_STEP;
    DRAM_DDR_NA,		//	    MMP_UBYTE DRAMID;
    (0xFF),				//	    MMP_UBYTE SEARCH_DQDLY_NUM;
    (0xFF),				//	    MMP_UBYTE USE_LGT_DDR3_SETTING;
    (0xFF),				//	    MMP_UBYTE SEARCH_EARLY_STOP;
};
#endif
/*
MMP_ULONG   SEARCH_DLY_UPBD = INVALIDATEVALUE;
MMP_ULONG   SEARCH_DLY_STEP = INVALIDATEVALUE;
MMP_ULONG   SEARCH_DLY_SUB_STEP = INVALIDATEVALUE;
MMP_ULONG   USE_LGT_DDR3_SETTING = INVALIDATEVALUE;
*/
//==============================================================================
//
//                              STRUCTURES
//
//==============================================================================
#if (AUTO_DRAM_LOCKCORE)
#if (DRAM_ID == DRAM_DDR3)
MMP_DRAM_CLK_DLY_SET m_delayTable[17] = {
    { 10, 0xE0}, { 20, 0xE0}, { 30, 0xD0}, { 40, 0x6A},
    { 45, 0x6C}, { 48, 0x6E}, {166, 0x52}, {180, 0x40},
    {192, 0x38}, {195, 0x32}, {198, 0x32}, {200, 0x32},
    {204, 0x32}, {396, 0x32}, {400, 0x32}, {528, 0x28},
    {533, 0x28}
};
#else
MMP_DRAM_CLK_DLY_SET m_delayTable[17] = {
    { 10, 0xE0}, { 20, 0xE0}, { 30, 0xD0}, { 40, 0x6A},
    { 45, 0x6C}, { 48, 0x6E}, {166, 0x52}, {180, 0x40},
    {192, 0x38}, {195, 0x32}, {198, 0x32}, {200, 0x32},
    {204, 0x32}, {300, 0x32}, {400, 0x32}, {528, 0x28},
    {533, 0x28}
};
#endif
//#if (DRAM_ID == DRAM_DDR)
MMPF_DRAM_DMA_PARAM m_DmaParam;
//#endif
#endif // (AUTO_DRAM_LOCKCORE)

//==============================================================================
//
//                              API Declaration
//
//==============================================================================
//Initialize value for valuable, DRAMID dependently
/*
void InitializeVariableForDram(void){
	if (DRAMID == DRAMID1){
		SEARCH_DLY_UPBD = SEARCH_DLY_UPBD_DDR1;
		SEARCH_DLY_STEP = SEARCH_DLY_STEP_DDR1;
		SEARCH_DLY_SUB_STEP = SEARCH_DLY_SUB_STEP_DDR1;
		USE_LGT_DDR3_SETTING = USE_LGT_DDR3_SETTING_DDR1;
	}
	else if(DRAMID == DRAMID2){
		SEARCH_DLY_UPBD = SEARCH_DLY_UPBD_DDR2;
		SEARCH_DLY_STEP = SEARCH_DLY_STEP_DDR2;
		USE_LGT_DDR3_SETTING = USE_LGT_DDR3_SETTING_DDR2;
	}
	else if(DRAMID == DRAMID3){
		SEARCH_DLY_UPBD = SEARCH_DLY_UPBD_DDR3;
		SEARCH_DLY_STEP = SEARCH_DLY_STEP_DDR3;
		USE_LGT_DDR3_SETTING = USE_LGT_DDR3_SETTING_DDR3;
	}
}
*/
/*
int DRAM_Module_Init(void)
{
	InitializeVariableForDram();
    return 0;
}
*/
/*
#pragma arm section code = "initcall6", rodata = "initcall6", rwdata = "initcall6",  zidata = "initcall6" 
#pragma O0
ait_module_init(DRAM_Module_Init);
#pragma
#pragma arm section rodata, rwdata, zidata
*/
