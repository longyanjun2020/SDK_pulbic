
;=======================================================================
;               ARM Architecture Standard Definitions
;=======================================================================
CPSR_Mode_USR	EQU	0x10
CPSR_Mode_FIQ	EQU	0x11
CPSR_Mode_IRQ	EQU	0x12
CPSR_Mode_SVC	EQU	0x13
CPSR_Mode_UNDEF	EQU	0x1B
CPSR_Mode_SYS	EQU	0x1F
CPSR_Mode_Bits	EQU	0x1F
CPSR_THUMB_Bit	EQU	0x20
CPSR_F_Bit	EQU	0x40
CPSR_I_Bit	EQU	0x80
CPSR_INT_DISABLE	EQU	CPSR_I_Bit:OR:CPSR_F_Bit
CP15_C1C0_MMU_BIT	EQU	1:SHL:0
CP15_C1C0_DCACHE_BIT	EQU	1:SHL:2
CP15_C1C0_WRBUF_BIT	EQU	1:SHL:3
CP15_C1C0_SYSTEM_BIT	EQU	1:SHL:8
CP15_C1C0_ROM_BIT	EQU	1:SHL:9
CP15_C1C0_ICACHE_BIT	EQU	1:SHL:12
SYSNUM_ARM_VECTOR_RESET	EQU	0x00
SYSNUM_ARM_VECTOR_UNDEF	EQU	0x01
SYSNUM_ARM_VECTOR_SWI	EQU	0x02
SYSNUM_ARM_VECTOR_ABORT_PREFETCH	EQU	0x03
SYSNUM_ARM_VECTOR_ABORT_DATA	EQU	0x04
SYSNUM_ARM_VECTOR_RSVD	EQU	0x05
SYSNUM_ARM_VECTOR_IRQ	EQU	0x06
SYSNUM_ARM_VECTOR_FIQ	EQU	0x07

;=======================================================================
;               Program Stack Manipulation
;=======================================================================
Exception_Stack_Len	EQU	0x20
Exception_Stack_Offset	EQU	0x00
System_Stack_Offset	EQU	Exception_Stack_Offset + Exception_Stack_Len

;=======================================================================
;               ARM Save Registers List
;=======================================================================
armreg_r0	EQU	0x0000
armreg_r4	EQU	0x0010
armreg_r8	EQU	0x0020
armreg_r9	EQU	0x0024
armreg_r10	EQU	0x0028
armreg_fp	EQU	0x002C
armreg_ip	EQU	0x0030
armreg_sp	EQU	0x0034
armreg_lr	EQU	0x0038
armreg_pc	EQU	0x003C
armreg_cpsr	EQU	0x0040
armreg_vector	EQU	0x0044
armreg_svclr	EQU	0x0048
armreg_svcsp	EQU	0x004C
ARMREG_SIZE	EQU	0x0050
	END
