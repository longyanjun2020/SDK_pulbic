;
; assembler include file for the SC registers and V2751
;

IRAM_STACK      EQU       0x08004000

;======================================================================
;              ARM7/9 definitions
;======================================================================

; The following mask are used to extract information from cpsr/spsr mask
Usr32Mode       EQU       2_10000
Fiq32Mode       EQU       2_10001
Irq32Mode       EQU       2_10010
Sup32Mode       EQU       2_10011
Abt32Mode       EQU       2_10111
Und32Mode       EQU       2_11011
Sys32Mode       EQU       2_11111

MODE_MASK       EQU       2_11111
IRQ_DISABLE     EQU       2_10000000
FIQ_DISABLE     EQU       2_01000000

    IF :DEF:__HW_WATCHDOG_FIQ__
INT_DISABLE     EQU       IRQ_DISABLE
    ELSE
INT_DISABLE     EQU       FIQ_DISABLE | IRQ_DISABLE
    ENDIF

Mode_USR        EQU 0x10        ; USR mode
Mode_FIQ        EQU 0x11        ; FIQ mode
Mode_IRQ        EQU 0x12        ; IRQ mode
Mode_SVC        EQU 0x13        ; SVC mode
Mode_ABORT      EQU 0x17        ; ABORT mode
Mode_UNDEF      EQU 0x1B        ; UNDEF mode

I_Bit           EQU 0x80        ; IRQ disable bit
F_Bit           EQU 0x40        ; FIQ disable bit
T_bit           EQU 0x20        ; Thumb bit

BigEndian_Bit   EQU 0x80        ; Big-endian bit (Control register)

Mode_IRQ_MIRQ   EQU 0x92        ; Mode IRQ and Mask IRQ
Mode_SVC_MIRQ   EQU 0x93        ; Mode SVC and Mask IRQ
Mode_SVC_UIRQ   EQU 0x13        ; Mode SVC and UnMask IRQ

Mode_mask       EQU 0x1F        ; mask to handle the processor modes

;======================================================================
;              V2751 definitions
;======================================================================
     ;--- offset of all registers
HardwareOfs       *       0xB4000000

BA_CMU		EQU 0x34000000
BA_MEM1		EQU 0x10000000
BA_EMI		EQU 0x2400
BA_GPIO		EQU 0x1000
BA_RTC          EQU 0x1400
BA_SYS_TIMER	EQU 0x2C00

OFF_EMI_MEM0_CFG1_OFFSET	EQU 0x00000004
OFF_EMI_MEM0_CFG2_OFFSET	EQU 0x00000008
OFF_EMI_MEM1_CFG1_OFFSET	EQU 0x0000000C
OFF_EMI_MEM1_CFG2_OFFSET	EQU 0x00000010
OFF_EMI_MEM2_CFG1_OFFSET	EQU 0x00000014
OFF_EMI_MEM2_CFG2_OFFSET	EQU 0x00000018
OFF_EMI_MEM3_CFG1_OFFSET	EQU 0x0000001C
OFF_EMI_MEM3_CFG2_OFFSET	EQU 0x00000020

OFF_RTC_STATUS_OFF	EQU 0x00000014
OFF_RTC_PWRCTRL_OFF	EQU 0x0000001C

OFF_SYS_TIMER_WD_CTRL0_OFFSET	EQU 0x0000000C

WATCHDOG_TIMEOUT_FLAG EQU 0x00100000 ; bit 20

; -----------------------------------------------------------------------------
; Interrupt Controller (ITCTRL) registers
; -----------------------------------------------------------------------------
ITCTRL_Priority12   EQU 0xB4001800   ; INT0  to INT7 (0 highest, 7 lowest)
ITCTRL_Priority34   EQU 0xB4001804   ; INT8  to INT15
ITCTRL_Priority56   EQU 0xB4001808   ; INT16 to INT23
ITCTRL_Priority78   EQU 0xB400180C   ; INT24 to INT31
ITCTRL_Priority910  EQU 0xB4001810   ; INT24 to INT31
ITCTRL_Mapping0      EQU 0xB4001814   ; 0=IRQ0n         / 1=IRQ1n
ITCTRL_Mapping1      EQU 0xB4001818   ; 0=IRQ0n         / 1=IRQ1n
ITCTRL_Mask0         EQU 0xB400181C   ; 0=masked        / 1=not masked
ITCTRL_Mask1         EQU 0xB4001820   ; 0=masked        / 1=not masked
ITCTRL_Sensitivity0  EQU 0xB4001824   ; 0=edge          / 1=level
ITCTRL_Sensitivity1  EQU 0xB4001828   ; 0=edge          / 1=level
ITCTRL_Polarity0     EQU 0xB400182c   ; 0=low,neg       / 1=high,pos
ITCTRL_Polarity1     EQU 0xB4001830   ; 0=low,neg       / 1=high,pos
ITCTRL_Reentrant0    EQU 0xB4001834   ; 0=not reentrant / 1=reentrant
ITCTRL_Reentrant1    EQU 0xB4001838   ; 0=not reentrant / 1=reentrant
ITCTRL_Pending_0    EQU 0xB400183C   ; 16 bits, IRQ0n
ITCTRL_Level_0      EQU 0xB400183E   ; 16 bits, IRQ0n
ITCTRL_Pending_1    EQU 0xB4001840   ; 16 bits, IRQ1n
ITCTRL_Level_1      EQU 0xB4001842   ; 16 bits, IRQ1n
ITCTRL_RawStatus0    EQU 0xB4001844   ; 0=not pending   / 1=pending (before mask)
ITCTRL_RawStatus1    EQU 0xB4001848   ; 0=not pending   / 1=pending (before mask)
ITCTRL_Status0       EQU 0xB400184C   ; 0=not pending   / 1=pending
ITCTRL_Status1       EQU 0xB4001850   ; 0=not pending   / 1=pending
ITCTRL_Clear0        EQU 0xB4001854   ; 0=no effect     / 1=clear interrupt (EOI for an interrupt)
ITCTRL_Clear1        EQU 0xB4001858   ; 0=no effect     / 1=clear interrupt (EOI for an interrupt)
ITCTRL_Ack0          EQU 0xB400185C   ; 0=no effect     / 1=acknowledge interrupt
ITCTRL_Ack1          EQU 0xB4001860   ; 0=no effect     / 1=acknowledge interrupt
ITCTRL_Service0      EQU 0xB4001864   ; 0=not in service/ 1=ack but not cleared
ITCTRL_Service1      EQU 0xB4001868   ; 0=not in service/ 1=ack but not cleared
ITCTRL_WakeUpMask0   EQU 0xB400187C   ; 0=masked        / 1=not masked
ITCTRL_WakeUpMask1   EQU 0xB4001880   ; 0=masked        / 1=not masked
ITCTRL_Config       EQU 0xB4001884   ; clear all pending it (EOI) or autoack config

; Values
ITCTRL_ClearAll  		EQU 0x00000100
ITCTRL_AutoAck      EQU 0x00000001

ITCTRL_Prio_FIQ     EQU 0x00000000
ITCTRL_Prio_1       EQU 0x00000001  ; Max priority on IRQ
ITCTRL_Prio_2       EQU 0x00000002
ITCTRL_Prio_3       EQU 0x00000003
ITCTRL_Prio_4       EQU 0x00000004
ITCTRL_Prio_5       EQU 0x00000005
ITCTRL_Prio_6       EQU 0x00000006
ITCTRL_Prio_7       EQU 0x00000007  ; Min priority on IRQ

ITCTRL_INT0         EQU 0x00000001       ; bit  0
ITCTRL_INT1         EQU 0x00000002       ; bit  1
ITCTRL_INT2         EQU 0x00000004       ; bit  2
ITCTRL_INT3         EQU 0x00000008       ; bit  3
ITCTRL_INT4         EQU 0x00000010       ; bit  4
ITCTRL_INT5         EQU 0x00000020       ; bit  5
ITCTRL_INT6         EQU 0x00000040       ; bit  6
ITCTRL_INT7         EQU 0x00000080       ; bit  7
ITCTRL_INT8         EQU 0x00000100       ; bit  8
ITCTRL_INT9         EQU 0x00000200       ; bit  9
ITCTRL_INT10        EQU 0x00000400       ; bit 10
ITCTRL_INT11        EQU 0x00000800       ; bit 11
ITCTRL_INT12        EQU 0x00001000       ; bit 12
ITCTRL_INT13        EQU 0x00002000       ; bit 13
ITCTRL_INT14        EQU 0x00004000       ; bit 14
ITCTRL_INT15        EQU 0x00008000       ; bit 15
ITCTRL_INT16        EQU 0x00010000       ; bit 16
ITCTRL_INT17        EQU 0x00020000       ; bit 17
ITCTRL_INT18        EQU 0x00040000       ; bit 18
ITCTRL_INT19        EQU 0x00080000       ; bit 19
ITCTRL_INT20        EQU 0x00100000       ; bit 20
ITCTRL_INT21        EQU 0x00200000       ; bit 21
ITCTRL_INT22        EQU 0x00400000       ; bit 22
ITCTRL_INT23        EQU 0x00800000       ; bit 23
ITCTRL_INT24        EQU 0x01000000       ; bit 24
ITCTRL_INT25        EQU 0x02000000       ; bit 25
ITCTRL_INT26        EQU 0x04000000       ; bit 26
ITCTRL_INT27        EQU 0x08000000       ; bit 27
ITCTRL_INT28        EQU 0x10000000       ; bit 28
ITCTRL_INT29        EQU 0x20000000       ; bit 29
ITCTRL_INT30        EQU 0x40000000       ; bit 30
ITCTRL_INT31        EQU 0x80000000       ; bit 31

; CMU Programming model
; Offsets to registers from BA_CMU

OFF_CMU_FIX_PLL_CTRL        EQU 0x00000000
OFF_CMU_CPU_PLL_CTRL        EQU 0x00000004
OFF_CMU_DSP_PLL_CTRL        EQU 0x00000008
OFF_CMU_AUX_SYS_CTRL0       EQU 0x0000000C
OFF_CMU_AUX_SYS_CFG0        EQU 0x00000010
OFF_CMU_FIX_SYS_CTRL0       EQU 0x00000014
OFF_CMU_FIX_SYS_CFG0        EQU 0x00000018
OFF_CMU_CPU_SYS_CTRL0       EQU 0x0000001C
OFF_CMU_CPU_SYS_CFG0        EQU 0x00000020
OFF_CMU_DSP_SYS_CTRL0       EQU 0x00000024
OFF_CMU_DSP_SYS_CFG0        EQU 0x00000028
OFF_CMU_RTC_SYS_CTRL0       EQU 0x0000002C
OFF_CMU_GPR_CTRL0           EQU 0x00000030
OFF_CMU_CPU_PERIPH_CFG0     EQU 0x00000034
OFF_CMU_CPU_PERIPH_PWD0     EQU 0x00000038
OFF_CMU_CPU_PERIPH_SW_RST0  EQU 0x0000003C
OFF_CMU_CPU_PERIPH_SM_WAIT0 EQU 0x00000040
OFF_CMU_GRAPHIC_PWD0        EQU 0x00000044
OFF_CMU_GRAPHIC_SW_RST0     EQU 0x00000048
OFF_CMU_GRAPHIC_SM_WAIT0    EQU 0x0000004C
OFF_CMU_RADIO_PWD0          EQU 0x00000050
OFF_CMU_RADIO_SW_RST0       EQU 0x00000054
OFF_CMU_RADIO_SM_WAIT0      EQU 0x00000058
OFF_CMU_SHARED_IF_PWD0      EQU 0x0000005C
OFF_CMU_SHARED_IF_SW_RST0   EQU 0x00000060
OFF_CMU_SHARED_IF_SM_WAIT0  EQU 0x00000064
OFF_CMU_SPARE               EQU 0x00000078
OFF_CMU_IRQ_MASK            EQU 0x00000068
OFF_CMU_IRQ_STATUS          EQU 0x0000006C
OFF_CMU_IRQ_CLEAR           EQU 0x00000070
OFF_CMU_IRQ_RAW_STATUS      EQU 0x00000074    

; Useful constants
FIX_PLL_LOCK_SHIFT      EQU     0
CPU_PLL_LOCK_SHIFT      EQU     1
DSP_PLL_LOCK_SHIFT      EQU     2
FIX_PLL_UNLOCK_SHIFT    EQU     3
CPU_PLL_UNLOCK_SHIFT    EQU     4
DSP_PLL_UNLOCK_SHIFT    EQU     5

    END
