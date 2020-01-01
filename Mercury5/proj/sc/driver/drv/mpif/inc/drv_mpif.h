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
#ifndef ME_SPI_H
#define ME_SPI_H

/*=============================================================*/
// Include files
/*=============================================================*/
//#include "drv_mpif_pub.h"

//#include "hal_mpif.h"
//#include "typedefs.h"
//#include "pif.h"


#if 0
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

#endif /* ME_SPI_H */
