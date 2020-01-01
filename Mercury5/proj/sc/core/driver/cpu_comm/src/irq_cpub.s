            PRESERVE8 ; For RealView Assembler
;--------------------------------------------
;- Export assembly symbols for C function to call
;- Import C function symbols for assembly to call
;--------------------------------------------

			INCLUDE irq.mac

            EXPORT  cpu_isr_b

            IMPORT  OSTCBCur
            IMPORT  OSIntNesting
            IMPORT  OSIntExit
            IMPORT  CpuComm_SwapISR

            AREA        AIT_IRQ, CODE, READONLY

;--------------------------------------------
;- Add ISR handler for A-I-T here
;--------------------------------------------

cpu_isr_b
cpu        OS_IRQ_ENTRY

            ldr         r0, = CpuComm_SwapISR
            mov         r14, pc
            bx          r0

cpu        OS_IRQ_EXIT

            END
