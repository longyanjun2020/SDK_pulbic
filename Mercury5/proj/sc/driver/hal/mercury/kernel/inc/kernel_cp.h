#ifndef __KERNEL_CP_H__
#define __KERNEL_CP_H__


/************************************************/
/* GEA coprocessor registers definition         */
/************************************************/

typedef struct W5Gea_s
{
  u16  au16_Kc[4];
  u16  u16_MsgKey0;
  u16  u16_MsgKey1;
  u16  u16_Ctrl;
  u16  u16_Status;
  u16  u16_S;
} W5Gea_t;

/*** GEA Ctrl register ***/
#define GEA_CTRL_STARTINIT    (0x0001<<0)
#define GEA_CTRL_DIRECTION    (0x0001<<1)

/*** GEA Status register ***/
#define GEA_STAT_STATUS       (0x0001<<0)

/*** GEA S register ***/
#define GEA_S_KEYSTRM_MSK     (0x00FF<<0)

/************************************************/
/* GEA2 coprocessor registers definition        */
/************************************************/

typedef struct W5Gea2_s
{
  //u32  u32_Cfg;
  u32  u32_MsgIn;
  u32  u32_MsgKey;
  u32  au32_SecretKey[2];
  u32  u32_Ctrl;
  u32  u32_MsgOut;
} W5Gea2_t;


/*** GEA Control register ***/
#define GEA2_SW_START          (0x0001<<0)
#define GEA2_UNDER_RUN         (0x0001<<1)
#define GEA2_UNRUN_RESET       (0x0001<<2)
#define GEA2_WORKING_STATUS    (0x0001<<3)

#define GEA2_CTRL_STARTINIT    (0x0001<<8)
#define GEA2_CTRL_DIRECTION    (0x0001<<9)
#define GEA2_MSG_SIZE_MSK      (0x0003<<10)
#define GEA2_MSG_SIZE_8BIT     (0x0000<<10)
#define GEA2_MSG_SIZE_16BIT    (0x0001<<10)
#define GEA2_MSG_SIZE_24BIT    (0x0002<<10)
#define GEA2_MSG_SIZE_32BIT    (0x0003<<10)
#define GEA2_START_AFTER_INIT  (0x0001<<12)

#define GEA2_DMA_EN             (0x0001<<16)
#define GEA2_DMA_BURST_EN       (0x0001<<18)
#define GEA2_MSG_IN_FIFO_EMPTY  (0x0001<<19)
#define GEA2_MSG_IN_FIFO_FULL   (0x0001<<20)
#define GEA2_MSG_OUT_FIFO_EMPTY (0x0001<<21)
#define GEA2_MSG_OUT_FIFO_FULL  (0x0001<<22)


/*** GEA MSG IN/OUT Masks ***/
#define GEA2_MSGIN_MSK         0x00000000
#define GEA2_MSGOUT_MSK        0x00000000


/************************************************/
/* FCS coprocessor registers definition         */
/************************************************/

typedef struct W5Fcs_s
{
  u32           u32_Gp;
  u32           u32_Fcs;
  u32           u16_DataByte;
  u16           u16_Init;
} W5Fcs_t;

/*** Init register ***/
#define FCS_DO_NOT_REVERSE_INPUT_DATA  (0x0001<<0)
#define FCS_GP_DEGREE_POS              1
#define FCS_GP_DEGREE_MSK              (0x001F<<1)
#define FCS_VALIDITY                   (0x0001<<6)


/************************************************/
extern volatile W5Gea_t *  const g_ptW5Gea;
extern volatile W5Gea2_t *  const g_ptW5Gea2;
extern volatile W5Fcs_t *  const g_ptW5Fcs;

#endif /*__KERNEL_CP_H__*/

