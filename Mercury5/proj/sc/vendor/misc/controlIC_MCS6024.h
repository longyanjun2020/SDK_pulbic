#ifndef _CONTROLIC_MCS6024_H_
#define _CONTROLIC_MCS6024_H_
#include "os_wrap.h"
#include "mmpf_pio.h"
#include "mmpf_i2cm.h"

//==============================================================================
//
//                              CONSTANTS
//
//==============================================================================
#define MCS6024_USE_SOFT_I2CM						0x0  //0x0 for using HW I2CM, 0x1 for using software I2CM
#define TOUTCH_QUEUE_SIZE   						300

/*===========================================================================

    TSI REGISTER TABLE

===========================================================================*/
#if (MCS6024_USE_SOFT_I2CM == 0x1)
#define MFS_I2C_SLAVE_ADDR                			0x40	//SW I2CM
#else
#define MFS_I2C_SLAVE_ADDR                			0x20	//HW I2CM
#endif

#define MFS_XCOORD_MASK								0x60
#define MFS_YCOORD_MASK								0x18
#define MFS_DEV_STATUS_MASK							0x07
#define TSI_RMI_ADDR_OPERATING_MODE                 0x01





#define TOUCHSCREEN_BURST_REG_NUM       			7
#define MAX_BURST_REG_NUM               			I2CM_RX_FIFO_DEPTH


//==============================================================================
//
//                              STRUCTURES
//
//==============================================================================
typedef enum  _TOUTCH_QUEUE_STATUS {
	TOUCH_QUEUE_NO_DATA = 0,
	TOUCH_QUEUE_DADA,
	TOUCH_QUEUE_FULL_DATA
}TOUTCH_QUEUE_STATUS;
typedef struct _sTouchScreenInfoType
{
  TOUTCH_QUEUE_STATUS queueStatus;
  MMP_USHORT x_coord;
  MMP_USHORT y_coord;
  MMP_UBYTE  z_posi;
  MMP_UBYTE  dev_status;
}sTouchScreenInfoType;
//==============================================================================
//
//                              FUNCTION PROTOTYPES
//
//==============================================================================
void touchScreen_Initial(void);
void touchScreen_GetRegister( MMP_UBYTE reg_addr, MMP_UBYTE *reg_val, MMP_UBYTE reg_len );
void touchScreen_SetRegister( MMP_UBYTE reg_addr, MMP_UBYTE *reg_val, MMP_UBYTE reg_len );
MMP_ERR touchScreen_ReadFromQueue( sTouchScreenInfoType *screenInfo);
MMP_ERR touchScreen_InsertToQueue( sTouchScreenInfoType *screenInfo);
MMP_ERR touchScreen_EmptyQueue(void);
MMP_ERR touchScreen_EnterFwUpg(void);
#endif