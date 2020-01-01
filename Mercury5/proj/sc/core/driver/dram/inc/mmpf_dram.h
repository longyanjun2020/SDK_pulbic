#ifndef _MMPF_DRAM_H_
#define _MMPF_DRAM_H_

#include "lib_retina.h"
#include "mmpf_typedef.h"

#ifdef __GNUC__
#include "vm_types.ht"
#endif

/// @ait_only
/** @addtogroup MMPF_System
 *  @{
 */
//==============================================================================
//
//                              COMPILER OPTION
//
//==============================================================================
#if(1)//NewCandidates
/* ulHeader, ulTail */
#define SCANRANGE_TABLE_HEADER   (0x3252434D)
#define SCANRANGE_TABLE_TAIL     (0x3252434D)
#define SECTOR_DDRINFO 		     (8195)//Physical=8195;Linear=3 
#define DDRINFO_HEADER      	 (0x4D435232)//MCR2
#define DDRINFO_TAIL        	 (0x4D435232)//MCR2
#endif


#define DRAM_SIZE_32_MB 	(32*1024*1024)
#define DRAM_SIZE_64_MB 	(64*1024*1024)
#define DRAM_SIZE_128_MB 	(128*1024*1024)
#define DRAM_SIZE_256_MB 	(256*1024*1024)
#define DRAM_SIZE_384_MB 	(384*1024*1024)
#define DRAM_SIZE_512_MB 	(512*1024*1024)
#define DRAM_SIZE_768_MB 	(768*1024*1024)
#define DRAM_SIZE_1024_MB 	(1024*1024*1024)

#define DRAM_DDR       (0)
#define DRAM_DDR2      (1)
#define DRAM_DDR3      (2)
#define DRAM_DDR_NA    (0xFF)

#define AUTO_DLL_LOCK   (1)

#define EN_SORTING_PLAN_A (0)
#define EN_SORTING_DBIST  (0)
#define EN_SORTING_PLAN_A_HALT_NG   (0)

//==============================================================================
//
//                              STRUCTURES
//
//==============================================================================

typedef enum _MMPF_DRAM_TYPE
{
    MMPF_DRAM_TYPE_NONE = 0,	// no stack memory
    MMPF_DRAM_TYPE_1,			// first used
    MMPF_DRAM_TYPE_2,			// second used
    MMPF_DRAM_TYPE_3,			// third used
    MMPF_DRAM_TYPE_EXT,
    MMPF_DRAM_TYPE_AUTO
} MMPF_DRAM_TYPE;
 
typedef enum _MMPF_DRAM_MODE
{
    MMPF_DRAM_MODE_SDRAM = 0,	// SD RAM
    MMPF_DRAM_MODE_DDR,			// DDR RAM
    MMPF_DRAM_MODE_DDR2,
    MMPF_DRAM_MODE_DDR3,
    MMPF_DRMA_MAX_MODE
} MMPF_DRAM_MODE;

typedef enum _MMPF_DRAM_ID
{
    MMPF_DRAM_256Mb_WINBOND = 0,
    MMPF_DRAM_256Mb_PIECEMK = 1,
    MMPF_DRAM_128Mb_WINBOND = 2,
    MMPF_DRAM_128Mb_FIDELIX = 4,
    MMPF_DRAM_512Mb_WINBOND = 3,
    MMPF_DRAM_512Mb_PIECEMK = 5
}MMPF_DRAM_ID;

#ifdef __GNUC__
typedef struct __packed _MMP_DRAM_CLK_DLY_SET
#else
__packed typedef struct _MMP_DRAM_CLK_DLY_SET
#endif
{
    MMP_USHORT ubClock;
    MMP_USHORT usDelay;
} MMP_DRAM_CLK_DLY_SET;

typedef struct {
	MMP_USHORT  usDQRD_DLY;	
	MMP_USHORT  usMIN_CLKDLY;
	MMP_USHORT  usMAX_CLKDLY;
} MMPF_DRAM_CHKDLYINFO;

typedef struct {
    MMP_ULONG   idx_low;
    MMP_ULONG   idx_up;
    MMP_ULONG   idx_opt;
    MMP_ULONG   idx_sel;
    MMP_ULONG   num;
} DDR3_DLY_DEBUG;

typedef struct _MMPF_DRAM_DMA_PARAM {
    MMP_ULONG ulSrcAddr;
    MMP_ULONG ulDstAddr;
    MMP_ULONG ulSize;
} MMPF_DRAM_DMA_PARAM;

typedef struct _MMPF_DRAM_SETTINGS {
    MMP_ULONG DRAM_SIZE;
    MMP_ULONG SEARCH_DLY_UPBD;
    MMP_ULONG SEARCH_DLY_LOWBD;
    MMP_ULONG SEARCH_DLY_STEP;
    MMP_ULONG SEARCH_DLY_SUB_STEP;
    MMP_UBYTE DRAMID;
    MMP_UBYTE SEARCH_DQDLY_NUM;
    MMP_UBYTE USE_LGT_DDR3_SETTING;
    MMP_UBYTE SEARCH_EARLY_STOP;//1: stop search while DMA time-out  0: continue search while DMA time-out
//    MMP_ULONG AUTO_DLL_LOCK;
} MMPF_DRAM_SETTINGS;

#if(1)//NewCandidates
typedef struct _DDRIII_SCANRANGE_TABLE
{	//(0x4D435232)
	MMP_ULONG ulHeader;	// check unit for the correctness of the DDRIII_SCANRANGE_TABLE (0x'V''S''N''2')
	//MMP_ULONG ubTriangle;//0=default 1=left up traingle 2=right down triangle 
	MMP_ULONG ulSearchDirection;//0=default 1=lTOPtoDOWN  2=DOWNtoTOP
	
	MMP_UBYTE ubReserved0;
	MMP_UBYTE ubUpperBD;
	MMP_UBYTE ubUpperMIN;
	MMP_UBYTE ubUpperMAX;
	
	MMP_UBYTE ubReserved1;
	MMP_UBYTE ubDownBD;
	MMP_UBYTE ubDownMIN;
	MMP_UBYTE ubDownMAX;

	MMP_SHORT usBestAsyncRd;//Yaxis & DRAM_DQBLK0_RDAS_CTL & DRAM_DQBLK1_RDAS_CTL
	MMP_SHORT ubBestDLY;//Xaxis & DRAM_DDR_CLK_MACRO_DLY

    MMP_UBYTE ubDataEyeDlyBlk0; //DRAM_DDR_DQBLK0_SYNC_DLY_TUNE
    MMP_UBYTE ubDataEyeDlyBlk1; //DRAM_DDR_DQBLK1_SYNC_DLY_TUNE

    MMP_UBYTE ubAfeWRDQSDHL0; //DRAM_DDR3_AFE_WR_DQS_DH_L0
    MMP_UBYTE ubAfeWRDQSDHL1; //DRAM_DDR3_AFE_WR_DQS_DH_L1
    MMP_UBYTE ubAfeRWDlyUpdateEN; //DRAM_DDR3_AFE_RW_DLY_UPDATE_EN
    
	volatile MMP_ULONG ulSkipScan;//0:Need scan, 0xEFCD3412:Skip scan
	MMP_ULONG ulTail;  // check unit for the correctness of the DDRIII_SCANRANGE_TABLE (0x'V''S''N''2')
}DDRIII_SCANRANGE_TABLE;
#endif

//==============================================================================
//
//                              FUNCTION PROTOTYPES
//
//==============================================================================

MMP_ERR MMPF_DRAM_Initialize(MMPF_DRAM_TYPE dramtype, MMP_ULONG *ulSize, MMP_ULONG ulClock, MMPF_DRAM_MODE drammode);
MMP_ERR MMPF_DRAM1_Initialize(MMPF_DRAM_TYPE dramtype, MMP_ULONG *ulSize, MMP_ULONG ulClock, MMPF_DRAM_MODE drammode);
MMP_ERR MMPF_DRAM2_Initialize(MMPF_DRAM_TYPE dramtype, MMP_ULONG *ulSize, MMP_ULONG ulClock, MMPF_DRAM_MODE drammode);
MMP_ERR MMPF_DRAM3_Initialize(MMPF_DRAM_TYPE dramtype, MMP_ULONG *ulSize, MMP_ULONG ulClock, MMPF_DRAM_MODE drammode);
MMP_ERR MMPF_DRAM_SendCommand(MMP_USHORT usCmd);
void    MMPF_DRAM_InitSettings(void);
MMP_ERR MMPF_DRAM_GetStackSize(MMP_ULONG *ulSize);
MMP_ERR MMPF_DRAM_SetPowerDown(MMP_BOOL bEnterPowerDown);
MMP_ERR MMPF_DRAM_SetSelfRefresh(MMP_BOOL bEnterSelfRefresh);
MMP_ERR MMPF_DRAM_ConfigPad(MMP_BOOL bEnterPowerDown);
MMP_ERR MMPF_DRAM_ConfigClock(MMP_ULONG ulClock, MMP_ULONG ulWaitCnt);
void MMPF_DRAM_SendInitCmd(void);

#if (AUTO_DRAM_LOCKCORE)
MMP_ERR MMPF_DRAM_ScanNewLockCore(MMPF_DRAM_TYPE dramtype, MMP_ULONG *ulSize, MMP_ULONG ulClock, MMPF_DRAM_MODE drammode);
MMP_ERR MMPF_DRAM1_ScanNewLockCore(MMPF_DRAM_TYPE dramtype, MMP_ULONG *ulSize, MMP_ULONG ulClock, MMPF_DRAM_MODE drammode);
MMP_ERR MMPF_DRAM3_ScanNewLockCore(MMPF_DRAM_TYPE dramtype, MMP_ULONG *ulSize, MMP_ULONG ulClock, MMPF_DRAM_MODE drammode);
#endif

void MMPF_DRAM3_ShowSFRangeCheck(MMP_ULONG ulClock);
/// @}
#endif

/// @end_ait_only

