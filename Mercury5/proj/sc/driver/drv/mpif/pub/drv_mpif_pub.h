/*.===******************  MODULE   : me_spi.h   *******************************
*
* PROJECT:
*
*          Copyright 2003, AqTrack Technologies, Inc.
*
===============================================================================
*
* ABSTRACT :
* Module encapsulate the SPI related defines and declarations.
*
*            $Id: me_spi.h,v 1.9 2006/06/16 13:38:52 Ra Exp $
*
*************************************************************************===.*/
#ifndef DRV_MPIF_PUB_H
#define DRV_MPIF_PUB_H

/*=============================================================*/
// Include files
/*=============================================================*/
//#include "drv_mpif_pub.h"

//#include "hal_mpif_pub.h"
//#include "typedefs.h"
//#include "pif.h"
#include "pif_pub.h"

#define SUPPORT_INTERRUPT_MODE
#if 1  //2011.11.15

typedef enum
{
    LC1A = 0,
    LC2A,
    LC2B,
    LC3A,
    LC3B,
    LC4A,
    LC_SPI,
    LC_NUM
} MPIF_LOGICAL_CHANNEL_ID_et;
#if 1//Jerry
typedef enum
{
    NOOP = 0,
    HYDRA_INIT,
    HYDRA_RESET,
    MPIF_RESET,
    SPIF_RESET,
    SLAVE_SPI_HW_RESET,
    SLAVE0_CHANGE_TO_1BIT_MODE,
    SLAVE1_CHANGE_TO_1BIT_MODE,
    SLAVE2_CHANGE_TO_1BIT_MODE,
    SLAVE3_CHANGE_TO_1BIT_MODE,
    SLAVE0_CHANGE_TO_2BIT_MODE,
    SLAVE1_CHANGE_TO_2BIT_MODE,
    SLAVE2_CHANGE_TO_2BIT_MODE,
    SLAVE3_CHANGE_TO_2BIT_MODE,
    SLAVE0_CHANGE_TO_4BIT_MODE,
    SLAVE1_CHANGE_TO_4BIT_MODE,
    SLAVE2_CHANGE_TO_4BIT_MODE,
    SLAVE3_CHANGE_TO_4BIT_MODE,
    SLAVE0_CHANGE_TO_8BIT_MODE,
    SLAVE1_CHANGE_TO_8BIT_MODE,
    SLAVE2_CHANGE_TO_8BIT_MODE,
    SLAVE3_CHANGE_TO_8BIT_MODE,
    SLAVE_CHANGE_TO_3A_MIU_MODE,
    SLAVE_CHANGE_TO_3B_MIU_MODE,
    SET_MPIF_BUS_CLOCK_6M,
    SET_MPIF_BUS_CLOCK_11M,
    SET_MPIF_BUS_CLOCK_15M,
    SET_MPIF_BUS_CLOCK_18M,
    SET_MPIF_BUS_CLOCK_22M,
    SET_MPIF_BUS_CLOCK_26M,
    SET_MPIF_BUS_CLOCK_30M,
    SET_MPIF_BUS_CLOCK_39M,
    SET_MPIF_BUS_CLOCK_62M,
    SET_MPIF_BUS_CLOCK_78M
} MPIF_IOCONTROL_CODE_et;
#endif

#if 1 //Jerry
typedef enum
{
    MPIF_SUCCESS = 0,
    MPIF_CHANNEL_BUSY,
    MPIF_INTERRUPT_NOT_TRIGGERED,
    MPIF_INTERRUPT_NOT_CLEAR,
    MPIF_TRANSMISSION_FAILED,
    MPIF_BUSYWAIT_SUCCESS,
    MPIF_UNKNOWN_EVENT_TYPE,
    MPIF_UNKNOWN_BUS_TYPE,
    MPIF_UNKNOWN_SLAVE_ID,
    MPIF_UNKNOWN_MPIF_ID,
    MPIF_FETAL_ERROR,
    MPIF_INVALID_PARAMETER,
    MPIF_MMIOSPACE_ERROR,
    MPIF_OVER_64BYTES_MPIF_BUG,
    MPIF_SPI_WRITE_LAST_BYTE_ERROR,
    MPIF_UNKNOWN_ERROR
} MPIF_ERROR_CODE_et;
#endif

#if 1 //Jerry
typedef enum
{
    SLAVE_0 = 0,
    SLAVE_1,
    SLAVE_2,
    SLAVE_3,
    SLAVE_NUM
} MPIF_SLAVE_ID_et;
#endif

#if 1 //Jerry
typedef enum
{
    MPIF1 = 0,
    MPIF2,
    MPIF_NUM
} MPIF_DEVICE_ID_et;


typedef enum
{
    POLLING = 0,
    MPIF_M3_INTERRUPT
} MPIF_WAIT_TYPE_et;
#endif

#if 1 //Jerry
typedef enum
{
    FAST_MODE_DISABLE = 0,
    FAST_MODE_ENABLE
} MPIF_FAST_MODE_et;
#endif


#if 1 //Jerry
typedef struct
{
    BOOL bCheckSum;
    BOOL bReTX;
    U8 u8ReTXTimes;
    U8 u8TurnAroundCycle;
    U8 u8WaitCycle;
    //MPIF_RW_MODE_et eMode;
    MPIF_FAST_MODE_et eFastMode;
    U8 u8MaxWait;
    U32 u32MIUAddr;
    U8 u8PageSize;
    U32 u32DMAGuardingTime;
} MPIF_OPTIONS_st, *pMPIF_OPTIONS_st;
#endif

#if 1//Jerry
typedef struct
{
    MPIF_DEVICE_ID_et       device_id;                  //[IN] MPIF1, MPIF2
    MPIF_SLAVE_ID_et        slave_id;                       //[IN] SLAVE_0, SLAVE_1, SLAVE_2, SLAVE_3
    MPIF_WAIT_TYPE_et       wait_type;                  //[IN] POLLING, MPIF_M3_INTERRUPT
    void                    (*pservice_routine)(U32 status);            //[IN] For wait_type is MPIF_M3_INTERRUPT, if the transmission done, call the service_routine
    //MPIF_BIT_MODE_et      bit_mode;                   //[IN] ONE_BIT, TWO_BIT, FOUR_BITS
    MPIF_OPTIONS_st         sOption;                        //[IN] sOption for 3A/4A setting.
    U32                 DMA_buffer_size;
    U32                 handler;                                    //[OUT]
    U8                  *pput_data_buffer;              //[OUT]
    //U32                   put_max_length;                     //[OUT]
} pmstar_multi_pif_register_st;
#endif


void hal_mpif_disable_int(void);


#if 1 //Jerry
typedef struct
{
    U32 REG_LC1A_SETTINGS;                      // h00
    U32 REG_LC2A_REG_CONTROL;                   // h01
    U32 REG_LC2A_REG_ADDRESS;                   // h02
    U32 REG_LC2A_REG_DATA;                      // h03
    U32 REG_LC2B_REG_CONTROL;                   // h04
    U32 REG_LC2B_REG_ADDRESS;                   // h05
    U32 REG_LC2B_REG_DATA;                      // h06
    U32 REG_LC3A_PACKET_CONTROL;                    // h07
    U32 REG_LC3A_PACKET_LENGTH;                 // h08
    U32 REG_LC3A_PACKET_DATA[8];                // h09-h10
    U32 REG_LC3A_PACKET_MIU_BASE_ADDRESS_L;     // h11
    U32 REG_LC3A_PACKET_MIU_BASE_ADDRESS_H;     // h12
    U32 REG_LC3B_PACKET_CONTROL;                // h13
    U32 REG_LC3B_PACKET_LENGTH;                 // h14
    U32 REG_LC3B_PACKET_DATA[8];                // h15-h1C
    U32 REG_LC3B_PACKET_MIU_BASE_ADDRESS_L;     // h1D
    U32 REG_LC3B_PACKET_MIU_BASE_ADDRESS_H;     // h1E
    U32 REG_LC4A_STREAM_CONTROL;                // h1F
    U32 REG_LC4A_STREAM_LENGTH;                 // h20
    U32 REG_LC4A_STREAM_MIU_BASE_ADDRESS_L;     // h21
    U32 REG_LC4A_STREAM_MIU_BASE_ADDRESS_H;     // h22
    U32 REG_4WIRE_SPI_CONTROL;                  // h23
    U32 REG_3WIRE_SPI_CONTROL;                  // h24
    U32 REG_SPI_CONTROL;                        // h25
    U32 REG_SPI_COMMAND_VALUE_L;                // h26
    U32 REG_SPI_COMMAND_VALUE_H;                // h27
    U32 REG_SPI_DATA_LENGTH;                    // h28
    U32 REG_SPI_MIU_BASE_ADDRESS_L;             // h29
    U32 REG_SPI_MIU_BASE_ADDRESS_H;             // h2A
    U32 REG_CHANNEL_BUSY_STATUS;                    // h2B
    U32 REG_INTERRUPT_EVENT_MASK;               // h2C
    U32 REG_INTERRUPT_EVENT_STATUS;             // h2D
    U32 REG_BUSY_TIMEOUT_COUNTER;               // h2E
    U32 REG_BUSY_TIMEOUT_TO;                        // h2F
    U32 REG_MISC1;                                  // h30
    U32 REG_MISC2;                              // h31
#ifdef BIG2
    U32 REG_MISC3;                              // h32
    U32 REG_SYNC_CONTROL;                       // h33
#endif
    U32 REG_SPI_UCPLT_LENGTH;                   // h34      // h32
#ifdef BIG2
    U32 REG_MIU_WRITE_PROTECTION[5];                // h35~h39
    U32 REG_DUMMY[6];                           // h3A~h3F
#endif
    U32 REG_DEBUG_SELECTION;                    // h40      // h33
    U32 REG_DEBUG_CHECKSUM_L;                   // h41      // h34
    U32 REG_DEBUG_CHECKSUM_H;                   // h42      // h35
    U32 REG_DEBUG_STS_IF_CTRL0;                 // h43      // h36
    U32 REG_DEBUG_STS_IF_CTRL1;                 // h44      // h37
    U32 REG_DEBUG_STS_PKT3A_CNT;                // h45      // h38
    U32 REG_DEBUG_STS_PKT3B_CNT;                // h46      // h39
    U32 REG_DEBUG_STS_STM0_CNT;                 // h47      // h3A
    U32 REG_DEBUG_STS_LC2X_CNT;                 // h48      // h3B
    U32 REG_DEBUG_STS_LC3X_CNT;                 // h49      // h3C
    U32 REG_DEBUG_STS_LC4X_CNT;                 // h4A      // h3D
#ifdef BIG2
    U32 REG_DEBUG_BITFAIL;                      // h4B
    U32 REG_DEBUG_RECORD;                       // h4C
#endif
    U32 REG_MPIF_LASTDONEZ;                     //h4D
} REG_MPIF_st, *PREG_MPIF_st;
#endif

extern volatile PREG_MPIF_st g_pMPIFRegs[2];  //Set Base Address for Two MPIF


#endif


#if 1
//UINT8 pif_init(UINT8 checksum);
//UINT8 pif_init(UINT8 checksum,UINT32 *u32hdl);
//UINT8 pif_deinit(void);
UINT8 pif_deinit(UINT32 u32hdl);
UINT8 bt_pif_slave_init(void);
UINT8 pif_slave_init(void);
UINT8 pif_slave_deinit(UINT8 *u8spifflag);
UINT8 pif_set_mpif_bit_mode(UINT8 u8Sid, UINT8 u8BitMode,UINT32 u32hdl);
UINT8 pif_set_mpif_clock(UINT8 u8Clock,UINT32 u32hdl);
UINT8 pif_set_spif_clk(void);
UINT8 pif_set_slave_id(UINT8 u8SlaveId);
UINT8 pif_slave_probe_id(void);



/* 1A */
UINT8 pif_read_RIU_1Astatus(UINT32 u32Addr, UINT32 *pu32Val,UINT32 u32hdl);
UINT8 pif_write_RIU_1Astatus(UINT32 u32Addr, UINT32 u32Val,UINT32 u32hdl);

/* 2A/2B */
/* SPIF register */
UINT8 pif_remote_reg_read(UINT32 u32Addr, UINT32 *pu32Val,UINT32 u32hdl,UINT8 *u8spifFlag);
UINT8 pif_remote_reg_write(UINT32 u32Addr, UINT32 u32Val,UINT32 u32hdl,UINT8 *u8spifFlag);
UINT8 pif_remote_reg_read32(UINT32 u32Addr, UINT32 *pu32Val,UINT32 u32hdl,UINT8 *u8spifFlag);
UINT8 pif_remote_reg_write32(UINT32 u32Addr, UINT32 u32Val,UINT32 u32hdl,UINT8 *u8spifFlag);
/* Tabasco register */
UINT8 pif_reg_read(UINT32 u32Addr, UINT32 *pu32Val,UINT8 *u8spifFlag);
UINT8 pif_reg_write(UINT32 u32Addr, UINT32 u32Val,UINT8 *u8spifFlag);
UINT8 pif_reg_read32(UINT32 u32Addr, UINT32 *pu32Val,UINT8 *u8spifFlag);
UINT8 pif_reg_write32(UINT32 u32Addr, UINT32 u32Val,UINT8 *u8spifFlag);

#ifdef __GPS_DUALSTAR_DRV__
/* RIU register access */
UINT8 pif_riu_reg_read(u32 u32Addr, u32 *pu32Val,UINT32 u32hdlUINT8,UINT8 *u8spifFlag);
UINT8 pif_riu_reg_write(u32 u32Addr, u32 u32Val,UINT32 u32hdlUINT8,UINT8 *u8spifFlag);
UINT8 pif_riu_reg_read32(u32 u32Addr, u32 *pu32Val,UINT32 u32hdl,UINT8 *u8spifflag);
UINT8 pif_riu_reg_write32(u32 u32Addr, u32 u32Val,UINT32 u32hdl,UINT8 *u8spifflag);
#endif

/* 3A/3B */
UINT8 pif_pkt_init_addr(UINT32 u32Addr, MPIF_LOGICAL_CHANNEL_ID_et eChan,UINT32 u32hdl,UINT8 *u8spifFlag);
UINT8 pif_pkt_init_length(UINT32 u32Len, MPIF_LOGICAL_CHANNEL_ID_et eChan,UINT32 u32hdl,UINT8 *u8spifFlag);
UINT8 pif_read_MIU_3A3Bstatus(UINT32 u32Addr, UINT32 u32Len, MPIF_LOGICAL_CHANNEL_ID_et eChan,UINT32 u32hdl);
UINT8 pif_pkt_send(UINT32 u32Addr, UINT32 u32Len, MPIF_LOGICAL_CHANNEL_ID_et eChan,UINT32 u32hdl);
UINT8 pif_read_RIU_3A3Bstatus(UINT32 u32Addr, UINT32 u32Len, MPIF_LOGICAL_CHANNEL_ID_et eChan,UINT32 u32hdl);
UINT8 pif_write_RIU_3A3Bstatus(UINT32 u32Addr, UINT32 u32Len, MPIF_LOGICAL_CHANNEL_ID_et eChan,UINT32 u32hdl);

/* 4A */
UINT8 pif_stream_init_addr(UINT32 u32Addr,UINT32 u32hdl,UINT8 *u8spifFlag);
UINT8 pif_stream_init_length(UINT16 u16Len,UINT32 u32hdl,UINT8 *u8spifFlag);
UINT8 pif_stream_send(UINT32 u32Addr, UINT16 u16Len,UINT32 u32hdl);
UINT8 pif_stream_recv(UINT32 u32Addr, UINT16 u16Len,UINT32 u32hdl);
#endif



#if 1
extern void hal_pif_set_misc1_slave3_datawidth(U8 data_wth,U8 dev_ID);
extern void hal_pif_set_cmdph_datawidth(U8 data_wth,U8 dev_ID);
UINT8 pif_set_spif_dar(UINT8 bEnable, UINT8 bForceWrite,UINT32 u32hdl,UINT8 *u8spifFlag);
UINT8 pif_read_RIU_2A2Bstatus(UINT32 u32Addr, UINT32 *pu32Val, MPIF_LOGICAL_CHANNEL_ID_et eCh,UINT32 u32hdl);
UINT8 pif_write_RIU_2A2Bstatus(UINT32 u32Addr, UINT32 u32Val, MPIF_LOGICAL_CHANNEL_ID_et eCh,UINT32 u32hdl);
UINT8 pif_write_MIU_3A3Bstatus(UINT32 u32Addr, UINT32 u32Len, MPIF_LOGICAL_CHANNEL_ID_et eChan,UINT32 u32hdl);
UINT8 Carina_pif_slave_init(UINT32 u32hdl,UINT8 *u8spifFlag);

void drv_multi_pif_interrupt_init( void );
void drv_multi_pif_init(void);
MPIF_ERROR_CODE_et drv_multi_pif_register(pmstar_multi_pif_register_st *pst);
void drv_multi_pif_reset(void);
MPIF_ERROR_CODE_et drv_multi_pif_deregister(UINT32 handler);
MPIF_ERROR_CODE_et drv_PollSpifMIUdoneviaLC1A(UINT32 u32hdl);
#endif



void drv_mstar_multi_pif_init(void);
void drv_mstar_set_mpif_data_len(u8 u8data, u8 u8pifDeviceID);
UINT8 drv_mstar_multi_pif_register(pmstar_multi_pif_register_st *pifhandler);
void drv_mstar_multi_pif_reset(void);
MPIF_ERROR_CODE_et drv_ConfigPIF(U32 hdl,MPIF_OPTIONS_st sOpt);
MPIF_ERROR_CODE_et drv_mstar_multi_pif_deregister(U32 hdl);
void drv_mstar_set_mpif_command_bit_len(u8 u8data, u8 u8pifDeviceID);


/*=============================================================*/
// Macro definition
/*=============================================================*/


/*=============================================================*/
// Data type definition
/*=============================================================*/


/*=============================================================*/
// Extern definition
/*=============================================================*/


/*=============================================================*/
// Global function definition
/*=============================================================*/

#endif /* DRV_MPIF_PUB_H */
