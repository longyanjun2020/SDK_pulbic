#ifndef _RIU_ASM_MACROS_
#define _RIU_ASM_MACROS_

//#include "platform_c5.h"

//#define HAL_MSTAR_AEON_RIU_BASE			0xA0000000
//#define HAL_REGBANK_OFFSET(riu_offset)		((riu_offset)<<2)

//#define REG_UART_SEL				(HAL_MSTAR_AEON_RIU_BASE+HAL_REGBANK_OFFSET(REG_BANK_CHIPTOP+0x0C))
//#define REG_WATCHDOG_ENABLE			(HAL_MSTAR_AEON_RIU_BASE+HAL_REGBANK_OFFSET(REG_BANK_PIU_MISC_0+0x30))

//#define REG_MAILBOX_0				(HAL_MSTAR_AEON_RIU_BASE+HAL_REGBANK_OFFSET(REG_BANK_MAILBOX+0))
//#define REG_MAILBOX_1				(HAL_MSTAR_AEON_RIU_BASE+HAL_REGBANK_OFFSET(REG_BANK_MAILBOX+1))
//#define REG_MAILBOX_2				(HAL_MSTAR_AEON_RIU_BASE+HAL_REGBANK_OFFSET(REG_BANK_MAILBOX+2))
//#define REG_MAILBOX_3				(HAL_MSTAR_AEON_RIU_BASE+HAL_REGBANK_OFFSET(REG_BANK_MAILBOX+3))
//#define REG_MAILBOX_4				(HAL_MSTAR_AEON_RIU_BASE+HAL_REGBANK_OFFSET(REG_BANK_MAILBOX+4))
//#define REG_MAILBOX_5				(HAL_MSTAR_AEON_RIU_BASE+HAL_REGBANK_OFFSET(REG_BANK_MAILBOX+5))
//#define REG_MAILBOX_6				(HAL_MSTAR_AEON_RIU_BASE+HAL_REGBANK_OFFSET(REG_BANK_MAILBOX+6))
//#define REG_MAILBOX_7				(HAL_MSTAR_AEON_RIU_BASE+HAL_REGBANK_OFFSET(REG_BANK_MAILBOX+7))
//#define REG_MAILBOX_8				(HAL_MSTAR_AEON_RIU_BASE+HAL_REGBANK_OFFSET(REG_BANK_MAILBOX+8))
//#define REG_MAILBOX_9				(HAL_MSTAR_AEON_RIU_BASE+HAL_REGBANK_OFFSET(REG_BANK_MAILBOX+9))
//#define REG_MAILBOX_A				(HAL_MSTAR_AEON_RIU_BASE+HAL_REGBANK_OFFSET(REG_BANK_MAILBOX+0xA))
//#define REG_MAILBOX_B				(HAL_MSTAR_AEON_RIU_BASE+HAL_REGBANK_OFFSET(REG_BANK_MAILBOX+0xB))
//#define REG_MAILBOX_C				(HAL_MSTAR_AEON_RIU_BASE+HAL_REGBANK_OFFSET(REG_BANK_MAILBOX+0xC))
//#define REG_MAILBOX_D				(HAL_MSTAR_AEON_RIU_BASE+HAL_REGBANK_OFFSET(REG_BANK_MAILBOX+0xD))
//#define REG_MAILBOX_E				(HAL_MSTAR_AEON_RIU_BASE+HAL_REGBANK_OFFSET(REG_BANK_MAILBOX+0xE))
//#define REG_MAILBOX_F				(HAL_MSTAR_AEON_RIU_BASE+HAL_REGBANK_OFFSET(REG_BANK_MAILBOX+0xF))

#ifdef __ASSEMBLER__

// Access RIU register
// 1. Fast and continuous RIU read/writes, set RIU bank address base in a specified register
//    only ONCE, notice that the <reg_off> value is within 0x0 ~ 0x3fc, aligned by 4
//     Example : Use r3 as base and r4 as temporary register:
//             (1) set_riu_bank     r3, <reg_bank>
//             (2) bank_reg_writei  r3, <reg_off>, <value>, r4  // write immediate value
//             (3) bank_reg_write   r3, <reg_off>, r4           // write r4 into riu register
//             (4) bank_reg_zero    r3, <reg_off>
//             (5) bank_reg_read    r3, <reg_off>, r4   // read register into r4
//             * Notice 1: that if 'r3' got changed anytime, 'SET_RIU_BANK r3'
//               must be re-performed again.
//             * Notice 2: if <reg_off> range exceed [0x00~0x3fc], error occurs
// Notice that for MSTAR OpenRISC platforms with different RIU design, that platform must
// define its own RIU access macro set and define 'CYGPKG_HAL_OPENRISC_MSTAR_RIU_BANK_MACRO'
// to prevent using the following default macros.

//.macro  set_riu_bank  bank_reg, bank_base
//	l.movhi	\bank_reg, (HAL_MSTAR_AEON_RIU_BASE >> 16)
//	l.ori	\bank_reg, \bank_reg, HAL_REGBANK_OFFSET(\bank_base)
//.endm

.macro  bank_reg_writei bank_reg, reg_off, value, tmp_reg
	.if (\reg_off & ~0x3ff)
		.error "Register offset \reg_off out of range [0x00~0x3ff]."
	.endif
	.if (\reg_off & 0x3)
		.error "Register offset \reg_off not aligned."
	.endif
	l.ori   \tmp_reg, r0, (\value)
	l.sh    ((\reg_off) & 0x3fc)(\bank_reg), \tmp_reg
.endm

.macro  bank_reg_write bank_reg, reg_off, val_reg
	.if (\reg_off & ~0x3ff)
		.error "Register offset \reg_off out of range [0x00~0x3ff]."
	.endif
	.if (\reg_off & 0x3)
		.error "Register offset \reg_off not aligned."
	.endif
	l.sh	((\reg_off) & 0x3fc)(\bank_reg), \val_reg
.endm

.macro  bank_reg_zero bank_reg, reg_off
	.if (\reg_off & ~0x3ff)
		.error "Register offset \reg_off out of range [0x00~0x3ff]."
	.endif
	.if (\reg_off & 0x3)
		.error "Register offset \reg_off not aligned."
	.endif
	l.sh	((\reg_off) & 0x3fc)(\bank_reg), r0
.endm

.macro  bank_reg_writebytei bank_reg, reg_off, value, tmp_reg
	.if (\reg_off & ~0x3ff)
		.error "Register offset \reg_off out of range [0x00~0x3ff]."
	.endif
	l.ori	\tmp_reg, r0, (\value)
	l.sb	((\reg_off) & 0x3ff)(\bank_reg), \tmp_reg
.endm

.macro  bank_reg_writebyte bank_reg, reg_off, val_reg
	.if (\reg_off & ~0x3ff)
		.error "Register offset \reg_off out of range [0x00~0x3ff]."
	.endif
	l.sb	((\reg_off) & 0x3ff)(\bank_reg), \val_reg
.endm

// Read RIU register into 'reg'
.macro  bank_reg_read  bank_reg, reg_off, reg
	.if (\reg_off & ~0x3ff)
		.error "Register offset \reg_off out of range [0x00~0x3ff]."
	.endif
	.if (\reg_off & 0x3)
		.error "Register offset \reg_off not aligned."
	.endif
	l.lhz	\reg, ((\reg_off) & 0x3fc)(\bank_reg)
.endm

// 2. Discontinuous RIU read/writes, set RIU base in a temporary register EVERYTIME
.macro  riu_writei  reg_addr, value, tmp_reg1, tmp_reg2
	l.movhi \tmp_reg2, hi(\reg_addr)
	l.ori   \tmp_reg2, \tmp_reg2, lo(\reg_addr)
	l.ori   \tmp_reg1, r0, (\value)
	l.sh    0x0(\tmp_reg2), \tmp_reg1
.endm

.macro  riu_write  reg_addr, val_reg, tmp_reg
	l.movhi	\tmp_reg, hi(\reg_addr)
	l.ori	\tmp_reg, \tmp_reg, lo(\reg_addr)
	l.sh	0x0(\tmp_reg), \val_reg
.endm

// Read RIU register into 'reg'
.macro  riu_read  reg_addr, reg
	l.movhi	\reg, hi(\reg_addr)
	l.ori	\reg, \reg, lo(\reg_addr)
	l.lhz	\reg,0x0(\reg)
.endm
#endif // __ASSEMBLER__

#endif
