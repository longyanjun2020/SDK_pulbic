    INCLUDE kernel_b3.i

        IMPORT  __BootEntry

        AREA    ke_resets, CODE
        
;****************************************************************************
;* Function: asm_ke_Reset
;****************************************************************************
;* void asm_ke_Reset(void);
;*
;* This function makes a software warm reset of the baseband.
;* This is a mere branch to the firmware entry point.
;*
;****************************************************************************

asm_ke_Reset    FUNCTION

        EXPORT  asm_ke_Reset

        B       __BootEntry

        ENDFUNC


     END
