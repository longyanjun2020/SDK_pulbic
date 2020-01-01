#ifndef __KERNEL_I2C_H__
#define __KERNEL_I2C_H__

/************************************************/
/* I2C interface registers definition           */
/************************************************/

typedef struct W5I2c_s
{
  u16 u16_Con;
  u16 Pad0;
  u16 u16_Tar;
  u16 Pad1;
  u16 u16_Sar;
  u16 Pad2;
  u16 u16_HsMaddr;
  u16 Pad3;
  u16 u16_DataCmd;
  u16 Pad4;
  u16 u16_SsSclHcnt;
  u16 Pad5;
  u16 u16_SsSclLcnt;
  u16 Pad6;
  u16 u16_FsSclHcnt;
  u16 Pad7;
  u16 u16_FsSclLcnt;
  u16 Pad8;
  u16 u16_HsSclHcnt;
  u16 Pad9;
  u16 u16_HsSclLcnt;
  u16 Pad10;
  u16 u16_RawIntrStat;
  u16 Pad11;
  u16 u16_IntrMask;
  u16 Pad12;
  u16 u16_IntrStat;
  u16 Pad13;
  u16 u16_RxTl;
  u16 Pad14;
  u16 u16_TxTl;
  u16 Pad15;
  u16 u16_ClrIntr;
  u16 Pad16;
  u16 u16_ClrRxUnder;
  u16 Pad17;
  u16 u16_ClrRxOver;
  u16 Pad18;
  u16 u16_ClrTxOver;
  u16 Pad19;
  u16 u16_ClrRdReq;
  u16 Pad20;
  u16 u16_ClrTxAbrt;
  u16 Pad21;
  u16 u16_ClrRxDone;
  u16 Pad22;
  u16 u16_ClrActivity;
  u16 Pad23;
  u16 u16_ClrStopDet;
  u16 Pad24;
  u16 u16_ClrStartDet;
  u16 Pad25;
  u16 u16_ClrGenAll;
  u16 Pad26;
  u16 u16_Enable;
  u16 Pad27;
  u16 u16_Status;
  u16 Pad28;
  u32 u32_Txflr;
  u32 u32_Rxflr;
  u16 u16_Sreset;
  u16 Pad29;
  u16 u16_TxAbrtSource;
  u16 Pad30;
} W5I2c_t;

/**** CON register ****/
#define I2C_SLAVE_DISABLE              (1<<6)
#define I2C_RESTART_EN                 (1<<5)
#define I2C_10BITADDR_MASTER           (1<<4)
#define I2C_10BITADDR_SLAVE            (1<<3)
#define I2C_SPEED_STD                  (1<<1)
#define I2C_SPEED_FAST                 (2<<1)
#define I2C_SPEED_HIGH                 (3<<1)
#define I2C_MASTER_ENABLE              (1<<0)

/**** TAR register ****/
#define I2C_SPECIAL                    (1<<11)
#define I2C_START                      (1<<10)
#define I2C_TAR_MSK                    0x003F

/**** SAR register ****/
#define I2C_SAR_MSK                    0x003F

/**** HS MADDR register ****/
#define I2C_HS_MAR_MSK                 0x0007

/**** DATA CMD register ****/
#define I2C_CMD_READ                   (1<<8)
#define I2C_CMD_WRITE                  (0<<8)
#define I2C_DATA_MSK                   0x00FF

/**** SS SCL HCNT register ****/
#define I2C_SS_SCL_HCNT_MSK            0xFFFF

/**** SS SCL LCNT register ****/
#define I2C_SS_SCL_LCNT_MSK            0xFFFF

/**** FS SCL HCNT register ****/
#define I2C_FS_SCL_HCNT_MSK            0xFFFF

/**** FS SCL LCNT register ****/
#define I2C_FS_SCL_LCNT_MSK            0xFFFF

/**** HS SCL HCNT register ****/
#define I2C_HS_SCL_HCNT_MSK            0xFFFF

/**** HS SCL LCNT register ****/
#define I2C_HS_SCL_LCNT_MSK            0xFFFF

/**** RAW INTR STAT register ****/
/**** INTR MASK register     ****/
/**** INTR STAT register     ****/
#define I2C_IT_GEN_CALL_POS            (1<<11)
#define I2C_IT_START_DET_POS           (1<<10)
#define I2C_IT_STOP_DET_POS            (1<<9)
#define I2C_IT_ACTIVITY_POS            (1<<8)
#define I2C_IT_RX_DONE_POS             (1<<7)
#define I2C_IT_TX_ABRT_POS             (1<<6)
#define I2C_IT_RD_REQ_POS              (1<<5)
#define I2C_IT_TX_EMPTY_POS            (1<<4)
#define I2C_IT_TX_OVER_POS             (1<<3)
#define I2C_IT_RX_FULL_POS             (1<<2)
#define I2C_IT_RX_OVER_POS             (1<<1)
#define I2C_IT_RX_UNDER_POS            (1<<0)

/**** RX TL register ****/
#define I2C_RX_TL_MSK                  0x00FF

/**** TX TL register ****/
#define I2C_TX_TL_MSK                  0x00FF

/**** CLR INTR register ****/
#define I2C_CLR_INTR_POS               (1<<0)

/**** CLR RX UNDER register ****/
#define I2C_CLR_RX_UNDER_POS           (1<<0)

/**** CLR RX OVER register ****/
#define I2C_CLR_RX_OVER_POS            (1<<0)

/**** CLR TX OVER register ****/
#define I2C_CLR_TX_OVER_POS            (1<<0)

/**** CLR RD REQ  register ****/
#define I2C_CLR_RD_REQ_POS             (1<<0)

/**** CLR TX ABRT register ****/
#define I2C_CLR_TX_ABRT_POS            (1<<0)

/**** CLR RX DONE register ****/
#define I2C_CLR_RX_DONE_POS            (1<<0)

/**** CLR ACTIVITY register ****/
#define I2C_CLR_ACTIVITY_POS           (1<<0)

/**** CLR STOP DET register ****/
#define I2C_CLR_STOP_DET_POS           (1<<0)

/**** CLR START DET register ****/
#define I2C_CLR_START_DET_POS          (1<<0)

/**** CLR GEN CALL register ****/
#define I2C_CLR_GEN_CALL_POS           (1<<0)

/**** ENABLE register ****/
#define I2C_ENABLE                     (1<<0)

/**** STATUS register ****/
#define I2C_RFF_POS                    (1<<4)
#define I2C_RFNE_POS                   (1<<3)
#define I2C_TFE_POS                    (1<<2)
#define I2C_TFNF_POS                   (1<<1)
#define I2C_ACTIVITY_POS               (1<<0)

/**** SRESET register ****/
#define I2C_SLAVE_SRST                 (1<<2)
#define I2C_MASTER_SRST                (1<<1)
#define I2C_SRST                       (1<<0)

/**** TX ABRT SOURCE register ****/
#define I2C_ABRT_SLVRD_INTX_POS        (1<<15)
#define I2C_ABRT_SLV_ARBLOST_POS       (1<<14)
#define I2C_ABRT_SLVFLUSH_TXFIFO_POS   (1<<13)
#define I2C_ARB_LOST_POS               (1<<12)
#define I2C_ARB_MASTER_DIS_POS         (1<<11)
#define I2C_ABRT_10B_RD_NORSTRT_POS    (1<<10)
#define I2C_ABRT_SBYTE_NORSTRT_POS     (1<<9)
#define I2C_ABRT_HS_NORSTRT_POS        (1<<8)
#define I2C_ABRT_SBYTE_ACKDET_POS      (1<<7)
#define I2C_ABRT_HS_ACKDET_POS         (1<<6)
#define I2C_ABRT_GCALL_READ_POS        (1<<5)
#define I2C_ABRT_GCALL_NOACK_POS       (1<<4)
#define I2C_ABRT_TXDATA_NOACK_POS      (1<<3)
#define I2C_ABRT_10ADDR2_NOACK_POS     (1<<2)
#define I2C_ABRT_10ADDR1_NOACK_POS     (1<<1)
#define I2C_ABRT_7B_ADDR_NOACK_POS     (1<<0)

extern volatile W5I2c_t* const W5I2c;

#endif /*__KERNEL_I2C_H__*/
