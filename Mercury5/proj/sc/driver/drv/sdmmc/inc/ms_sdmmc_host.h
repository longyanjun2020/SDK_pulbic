/***************************************************************************************************************
 *
 * FileName ms_sdmmc_host.h
 *     @author jeremy.wang (2017/08/10)
 * Desc:
 *     This file is the header file of ms_sdmmc_host.c.
 *
 ***************************************************************************************************************/
#ifndef __MS_SDMMC_HOST_H
#define __MS_SDMMC_HOST_H

#include "hal_card_base.h"
#include "hal_card_intr_v5.h"


//***********************************************************************************************************
// Config Setting (Externel)
//***********************************************************************************************************


//###########################################################################################################
#if (D_PROJECT == D_PROJECT__iNF)
//###########################################################################################################

    #define D_SDMMC1_IP                EV_IP_FCIE1                    //SDIO0
    #define D_SDMMC1_PORT              EV_PFCIE5_SDIO                 //Port Setting
    #define D_SDMMC1_PAD               EV_PAD1                        //PAD_SD0

    #define D_SDMMC2_IP                EV_IP_FCIE2                    //FCIE
    #define D_SDMMC2_PORT              EV_PFCIE5_FCIE                 //Port Setting
    #define D_SDMMC2_PAD               EV_PAD2                        //PAD_SD1

    #define D_SDMMC3_IP                EV_IP_FCIE3                    //Dummy Setting
    #define D_SDMMC3_PORT              EV_PFCIE5_FCIE                 //Dummy Setting
    #define D_SDMMC3_PAD               EV_PAD3                        //Dummy Setting

    #define V_SDMMC_CARDNUMS           1
    #define V_SDMMC1_MAX_CLK           48000000
    #define V_SDMMC2_MAX_CLK           48000000
    #define V_SDMMC3_MAX_CLK           48000000                       //Dummy Setting

    #define EN_SDMMC_CDZREV            (FALSE)

    #define WT_POWERUP                 20 //(ms)
    #define WT_POWERON                 60 //(ms)
    #define WT_POWEROFF                25 //(ms)


//###########################################################################################################
#elif (D_PROJECT == D_PROJECT__MV5)
//###########################################################################################################

    #define D_SDMMC1_IP                EV_IP_FCIE1                    //SDIO0
    #define D_SDMMC1_PORT              EV_PFCIE5_SDIO                 //Port Setting
    #define D_SDMMC1_PAD               EV_PAD1                        //PAD_SD0
    #define D_SDMMC1_BUSMODE           (EV_BUS_HS_SDR25/*|EV_BUS_SDR50|EV_BUS_SDR104_HS200|EV_BUS_DDR50*/)

    #define D_SDMMC2_IP                EV_IP_FCIE2                    //FCIE
    #define D_SDMMC2_PORT              EV_PFCIE5_FCIE                 //Port Setting
    #define D_SDMMC2_PAD               EV_PAD2                        //PAD_SD1
    #define D_SDMMC2_BUSMODE           (EV_BUS_HS_SDR25|EV_BUS_SDR50/*|EV_BUS_DDR50*/)

    #define D_SDMMC3_IP                EV_IP_FCIE3                    //Dummy Setting
    #define D_SDMMC3_PORT              EV_PFCIE5_FCIE                 //Dummy Setting
    #define D_SDMMC3_PAD               EV_PAD3                        //Dummy Setting
    #define D_SDMMC3_BUSMODE           (EV_BUS_HS_SDR25|EV_BUS_SDR50/*|EV_BUS_DDR50*/)

    #define V_SDMMC_CARDNUMS           1
    #define V_SDMMC1_MAX_CLK           48000000
    #define V_SDMMC2_MAX_CLK           48000000
    #define V_SDMMC3_MAX_CLK           48000000                       //Dummy Setting

    #define EN_SDMMC_CDZREV            (FALSE)

    #define WT_POWERUP                 20 //(ms)
    #define WT_POWERON                 60 //(ms)
    #define WT_POWEROFF                25 //(ms)

//###########################################################################################################
#else    //Templete Description
//###########################################################################################################
/*  #define D_SDMMC1_IP                EV_IP_FCIE1                    //SDIO0
    #define D_SDMMC1_PORT              EV_PORT_SDIO1                  //Port Setting
    #define D_SDMMC1_PAD               EV_PAD1                        //PAD_SD0

    #define D_SDMMC2_IP                EV_IP_FCIE1                    //SDIO0
    #define D_SDMMC2_PORT              EV_PORT_SDIO1                  //Port Setting
    #define D_SDMMC2_PAD               EV_PAD1

    #define D_SDMMC3_IP                EV_IP_FCIE1                    //SDIO0
    #define D_SDMMC3_PORT              EV_PORT_SDIO1                  //Port Setting
    #define D_SDMMC3_PAD               EV_PAD1

    #define EN_SDMMC_CDZREV            (FALSE)

    #define WT_POWERUP                 20 //(ms)
    #define WT_POWERON                 60 //(ms)
    #define WT_POWEROFF                25 //(ms)

*/
//###########################################################################################################
#endif
//###########################################################################################################


typedef enum
{
    EV_POWER_OFF = 0,
    EV_POWER_UP  = 1,
    EV_POWER_ON  = 2,

} PowerEmType;


typedef enum
{
    EV_BUS_3_3V  = 0,
    EV_BUS_1_8V  = 1,

} BusVddEmType;


struct msSt_SD_SlotInfo
{
    unsigned int    currClk;        //Current Clock
    unsigned int    currRealClk;    //Current Real Clock
    unsigned char   currPowrMode;
    unsigned char   currWidth;      //Current Bus Width
    unsigned char   currTiming;     //Current Bus Timning
    unsigned char   currPadVolt;    //Current Pad Voltage

    unsigned char   read_only;        //WP
    unsigned char   card_det;         //Card Detect

};


struct msSt_SD_IOS
{
    unsigned int    clock;          /* clock rate */
    unsigned char   power_mode;     /* power supply mode */

#define SD_POWER_OFF        0
#define SD_POWER_UP         1
#define SD_POWER_ON         2

    unsigned char   bus_width;      /* data bus width */

#define SD_BUS_WIDTH_1     0
#define SD_BUS_WIDTH_4     2

    unsigned char   timing;         /* timing specification used */

#define SD_TIMING_LOW            0
#define SD_TIMING_DEF_SDR12      1
#define SD_TIMING_HS_SDR25       (1<<1)
#define SD_TIMING_SDR50          (1<<2)  //1<<(2)UHS_SDR50_BUS_SPEED
#define SD_TIMING_SDR104_HS200   (1<<3)  //1<<(3)UHS_SDR104_BUS_SPEED
#define SD_TIMING_DDR50          (1<<4)  //1<<(4)UHS_DDR50_BUS_SPEED

    unsigned char   pad_volt;     /* pad voltage (1.8V or 3.3V) */

#define SD_PAD_VOLT_330  0
#define SD_PAD_VOLT_180  1

    unsigned char   drv_type;       /* driver type (A, B, C, D) */

#define SD_DRV_TYPE_B   0
#define SD_DRV_TYPE_A   1
#define SD_DRV_TYPE_C   2
#define SD_DRV_TYPE_D   3

};


struct msSt_SD_Cmd
{
    unsigned char  u8Slot;
    unsigned char  u8Cmd;
    unsigned int   u32Arg;
    unsigned short u16RspType;

#define SD_RSP_NO    0x0000
#define SD_RSP_R1    0x2105
#define SD_RSP_R1B   0x2205
#define SD_RSP_R2    0x3310
#define SD_RSP_R3    0x2405
#define SD_RSP_R4    0x2505
#define SD_RSP_R5    0x2605
#define SD_RSP_R6    0x2705
#define SD_RSP_R7    0x2805

    unsigned short u16Err;
    unsigned char  u8RspArr[0x10];


};


struct msSt_SD_Data
{
    unsigned short  u16IOFlags;

#define SD_FLAG_READ     1
#define SD_FLAG_WRITE    (1<<1)

    unsigned short  u16BlkCnt;
    unsigned short  u16BlkSize;
    volatile char   *pu8Buf;

    unsigned short  u16Err;

};


struct msSt_SD_Req
{
    struct msSt_SD_Cmd   *pstCmd;
    struct msSt_SD_Data  *pstData;
    struct msSt_SD_Cmd   *pstStop;

    unsigned short  u16ReqErr;

};



void MS_SD_Init(void);
void MS_SD_SET_IOS(unsigned char u8Slot, struct msSt_SD_IOS* pstSD_IOS, unsigned char bRefresh);
unsigned char MS_SD_Get_CD(unsigned char u8Slot);

unsigned short MS_SD_Request(U8_T u8Slot, struct msSt_SD_Req *pstReqest);







#endif // End of __MS_SDMMC_HOST_H
