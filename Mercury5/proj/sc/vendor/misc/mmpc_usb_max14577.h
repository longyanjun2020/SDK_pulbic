//==============================================================================
//
//  File        : MMPC_USB_MAX14577.h
//  Description : 
//  Author      : Bossino Huang
//  Revision    : 1.0
//
//==============================================================================
#ifndef	_MMPC_USB_MAX14577_H_
#define	_MMPC_USB_MAX14577_H_
#include "includes_fw.h"
//==============================================================================
//
//                              CONSTANTS
//
//==============================================================================

#define MAX14577_ADDR 				0x25
#define MAX14577_DeviceID			0x5D	//0x45
#define MAX14577_REG_MAX			0x16
//==============================================================================
//
//                              STRUCTURES
//
//==============================================================================
typedef enum
{
	MMPC_USB_Reg_DEVICEID = 0x00,		/* 00h		R */
	MMPC_USB_Reg_INT1,					/* 01h		R */
	MMPC_USB_Reg_INT2,					/* 02h		RW */
	MMPC_USB_Reg_INT3,					/* 03h		RW */
	MMPC_USB_Reg_STATUS1,				/* 04h		RW */
	MMPC_USB_Reg_STATUS2,				/* 05h		RW */
	MMPC_USB_Reg_STATUS3,				/* 06h		R */
	MMPC_USB_Reg_INTMASK1,				/* 07h		R */
	MMPC_USB_Reg_INTMASK2,				/* 08h		R */
	MMPC_USB_Reg_INTMASK3,				/* 09h		R */
	MMPC_USB_Reg_CDETCTRL1,				/* 0Ah		R */
	MMPC_USB_Reg_CDETCTRL2,				/* 0Bh		R */
	MMPC_USB_Reg_CONTROL1,				/* 0Ch		R */
	MMPC_USB_Reg_CONTROL2,				/* 0Dh		R */
	MMPC_USB_Reg_CONTROL3,				/* 0Eh		R */
	MMPC_USB_Reg_CHGCTRL1,				/* 0Fh		R */
	MMPC_USB_Reg_CHGCTRL2,				/* 10h		R */
	MMPC_USB_Reg_CHGCTRL3,				/* 11h		R */
	MMPC_USB_Reg_CHGCTRL4,				/* 12h		R */
	MMPC_USB_Reg_CHGCTRL5,				/* 13h		R */
	MMPC_USB_Reg_CHGCTRL6,				/* 14h		R */
	MMPC_USB_Reg_CHGCTRL7,				/* 15h		R */
	MMPC_USB_Reg_REGISTER_MAX
} MMPC_USB_Reg;

//==============================================================================
//
//                              FUNCTION PROTOTYPES
//
//==============================================================================
MMP_ERR MMPC_USB_Initialize(void);
MMP_ERR MMPC_USB_SetReg(MMPC_USB_Reg reg_addr, MMP_UBYTE reg_val);
MMP_ERR MMPC_USB_GetReg(MMPC_USB_Reg reg_addr, MMP_USHORT *reg_val);
MMP_ERR MMPC_USB_DetectVBus5V(MMP_USHORT *retVal);
#endif /* _MMPC_USB_MAX14577_H_ */

