;****************************************************************************
;*  $Workfile::   sys_boot_detectram.asm                                  $ *
;*--------------------------------------------------------------------------*
;*  Scope   :  RAM size detection function                                  *
;*--------------------------------------------------------------------------*
;*  $Revision::   1.1  $                                                    *
;*-------------------------------+------------------------------------------*
;*  $Author::   jlo    $         |     $Date::   May 05 2004 11:27:28 $     *
;****************************************************************************
;*   $LogWavecom: U:\projet\gsm\pvcsarch\archives\sys\src\sys_boot_detectram.asm-arc $
; --------------------------------------------------------------------------
;  Date     | Author | Revision       | Description
; ----------+--------+----------------+-------------------------------------
;  05.05.04 | jlo    | 1.1            | .  Resolution for 22095: System ini
;           |        |                | tialisation done in "C" language
; ----------+--------+----------------+-------------------------------------
;  11.03.04 | kod    | 1.0            | Initial revision.
; ----------+--------+----------------+-------------------------------------
;***************************************************************************

    AREA MemSizeArea, CODE, READONLY

  CODE32

;*******************************************************************************
; Function: sys_RAMSizeDetect
;*******************************************************************************
; Detects the size of the RAM device.
; This function does not alter the contents of the memory.
;
; Warning:
; *This function is not AAPCS compliant*
; It destroys registers (yfa to update) and should not be called outside the
; boot sequence
;
; Input parameter:
;   r0 - Base address of the memory
;
; Returns:
;   r0 - Size of the RAM
;*******************************************************************************
sys_RAMSizeDetect   PROC
    EXPORT  sys_RAMSizeDetect

  MOV   r2, r0        ; r2= MEM1 base addr from input parameter
  MOV   r0, #0x800000 ; r0=0x800000 = 8 MB
  ADD   r3, r2, r0    ; r3 = r2 + r0 => 0x10800000
  STR   r0, [r3, #-4] ; [r3 - 4] = r0 => *(0x10800000 - 4) =  0x800000
  MOV   r1, r0        ; r1 = r0 = 0x800000
RAM_Loop
  MOV   r0, r0, LSR #1; r0 = (r0 >>1) => r0 = (0x800000>>1)= 0x400000
  ADD   r3, r2, r0    ; r3 = r2 + r0 => r3 = 0x10000000 + 0x400000 = 0x10400000
  ADD   r4, r2, r1    ; r4 = r2 + r1 => r4 = 0x10000000 + 0x800000 = 0x10800000
  STR   r0, [r3, #-4] ; [r3 - 4] = r0 => *(0x10400000 - 4) = 0x400000
  LDR   r1, [r4, #-4] ; r1 = [r4 - 4] => r1 = *(0x10800000 - 4) => 0x800000
  CMP   r0, r1
  ADDNE r0, r0, r0    ; if(r0!=r1) r0=r0+r0 goto RAM_Found
  BNE   RAM_Found
  CMP   r0, #0x40000  ; if(r0!=0x40000) goto RAM_Loop... required more than 256Kbytes RAM Size
  BNE   RAM_Loop
RAM_Found
  BX    lr
        ENDP

;*******************************************************************************
; Function: sys_GetRamSize
;*******************************************************************************
; Detects the size of the RAM device.
; This function does not alter the contents of the memory.
; Works for OneC and WHAT2/3E basebands.
;
; This function is AAPCS compliant.
;
; Input parameter:
;   r0 - Base address of the memory
;
; Returns:
;   r0 - Size of the RAM
;*******************************************************************************
;yfa to be rewritten
;sys_GetRamSize  PROC
;        EXPORT  sys_GetRamSize
;
;        STMFD   sp!, {r4,r12,lr}
;        BL      sys_RAMSizeDetect
;        LDMFD   sp!, {r4,r12,lr}
;        BX      lr

;                ENDP
; afy

    END
