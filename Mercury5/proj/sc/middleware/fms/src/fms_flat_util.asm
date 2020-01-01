;***************************************************************************
;*  $Workfile::   fms_flat_util.asm                                       $
;*--------------------------------------------------------------------------
;*  Scope: Fast assembly language routine to check the flash memory 
;*--------------------------------------------------------------------------
;*  $Revision::   1.1  $
;*-------------------------------+------------------------------------------
;*  $Author::   kod    $         |     $Date::   21 Sep 2005 14:11:14  $
;***************************************************************************
;* $Log:   U:/projet/gsm/pvcsarch/archives/fms/src/fms_flat_util.asm-arc  $
; 
;    Rev 1.1   21 Sep 2005 14:11:14   kod
; Resolution for 30293: AD volume state says 'ready' when the volume is dirty
; Version v1a21.
; 
;    Rev 1.0   16 Sep 2005 15:40:20   kod
; Initial revision.
;****************************************************************************/

    AREA |.text|, CODE

;****************************************************************************
;* Function: fms_FlatFastCheckTail
;****************************************************************************
;* BOOL fms_FlatFastCheckTail(u32 *i_pu32_DataEnd, u32 *i_pu32_VolumeEnd);
;*
;* The function checks that all the data in [DataEnd;VolumeEnd[
;* are equal to FF. This ensures that the free space in a volume
;* is actually erased and can safely be used for cell allocations.
;*
;* Note:
;*   - i_pu32_DataEnd is a pointer to a 32-bit integer, whose address
;*     must be dividable by 4.
;*   - i_pu32_VolumeEnd is the ceiling of a volume, it must
;*     be dividable by 16.
;*
;* Input parameter:
;*   r0 - (i_pu32_DataEnd) End of the occupied space in a volume
;*   r1 - (i_pu32_VolumeEnd) End of the volume
;*
;****************************************************************************

fms_FlatFastCheckTail   FUNCTION
    EXPORT  fms_FlatFastCheckTail
    
    stmfd   sp!, {r4-r7}

    ; initialise r7 to 0xFFFFFFFF
    mvn     r7, #0
    
    ; r0 = base address (must be /able by 4)
    ; r1 = end (must be /able by 16)
    
    ; try to line up on a 16-byte boundary
    ; get r0 mod 16
    ; r2 = (r0 mod 16) / 4
    mov     r2, r0, lsl #28
    movs    r2, r2, lsr #30
    beq     read16
    
    ; r2 == 1 when r0 mod 16 == 4
    ; r2 == 2 when r0 mod 16 == 8... and so on
    ; initialise r3-r6
    mvn     r3, #0
    mvn     r4, #0
    mvn     r5, #0
    mvn     r6, #0
    ; load as many registers as needed
    ; when the next instruction is executed,
    ; pc points 2 nops below.
    add     pc, pc, r2, lsl #2      ; pc - 8
    nop                             ; pc - 4
    nop                             ; pc
    ; next instruction is pc+4
    ; branch here if r2 == 1 (3 reads required)
    ldr     r4, [r0], #4
    ; branch here if r2 == 2 (2 reads required)
    ldr     r5, [r0], #4
    ; branch here if r2 == 3 (1 read required)
    ldr     r6, [r0], #4
    
    b       testRegs
    
read16
    ; reached end?
    cmp     r0, r1
    beq     exit
    
    ldmia   r0!, {r3-r6}

testRegs
    ; compute r3 & r4 & r5 & r6
    and     r3, r3, r4
    and     r5, r5, r6
    and     r3, r3, r5
    ; compare result with 0xFFFFFFFF
    cmp     r3, r7
    movne   r0, #0
    beq     read16
exit    
    ; Z flag is set when end has been reached
    moveq   r0, #1
    
    ldmfd   sp!, {r4-r7}
    bx      lr

    ENDFUNC

    END
