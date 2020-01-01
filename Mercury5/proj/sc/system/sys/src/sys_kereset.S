    //INCLUDE kernel_b3.i

        .extern  __BootEntry

        //AREA    ke_resets, CODE
        .section .text.ke_resets

/*;****************************************************************************
;* Function: asm_ke_Reset
;****************************************************************************
;* void asm_ke_Reset(void);
;*
;* This function makes a software warm reset of the baseband.
;* This is a mere branch to the firmware entry point.
;*
;****************************************************************************/
        .func   asm_ke_Reset
asm_ke_Reset:
        .global asm_ke_Reset

        B       __BootEntry

        .endfunc


     .end
