    AREA |.text|, CODE
;non sequential write
loop_time         RN 0
base_addr         RN 1

fms_test_write_nonseq_psram_1   FUNCTION
    EXPORT  fms_test_write_nonseq_psram_1

    stmfd   sp!, {r4-r11}

    ; read data from flash
    MOV     r7, base_addr 
    ; LDR     loop_time, =0x5746;

read_psram_1
    stmia base_addr!, {r2-r9} ; copy 32 bytes into stmia
    stmia base_addr!, {r2-r9} ; copy 32 bytes into stmia
    stmia base_addr!, {r2-r9} ; copy 32 bytes into stmia
    stmia base_addr!, {r2-r9} ; copy 32 bytes into stmia
    stmia base_addr!, {r2-r9} ; copy 32 bytes into stmia
    stmia base_addr!, {r2-r9} ; copy 32 bytes into stmia
    stmia base_addr!, {r2-r9} ; copy 32 bytes into stmia
    stmia base_addr!, {r2-r9} ; copy 32 bytes into stmia
    stmia base_addr!, {r2-r9} ; copy 32 bytes into stmia
    stmia base_addr!, {r2-r9} ; copy 32 bytes into stmia
    stmia base_addr!, {r2-r9} ; copy 32 bytes into stmia
    stmia base_addr!, {r2-r9} ; copy 32 bytes into stmia
    stmia base_addr!, {r2-r9} ; copy 32 bytes into stmia
    stmia base_addr!, {r2-r9} ; copy 32 bytes into stmia
    stmia base_addr!, {r2-r9} ; copy 32 bytes into stmia
    stmia base_addr!, {r2-r9} ; copy 32 bytes into stmia
    stmia base_addr!, {r2-r9} ; copy 32 bytes into stmia
    stmia base_addr!, {r2-r9} ; copy 32 bytes into stmia
    stmia base_addr!, {r2-r9} ; copy 32 bytes into stmia
    stmia base_addr!, {r2-r9} ; copy 32 bytes into stmia
    stmia base_addr!, {r2-r9} ; copy 32 bytes into stmia
    stmia base_addr!, {r2-r9} ; copy 32 bytes into stmia
    stmia base_addr!, {r2-r9} ; copy 32 bytes into stmia
    stmia base_addr!, {r2-r9} ; copy 32 bytes into stmia
    stmia base_addr!, {r2-r9} ; copy 32 bytes into stmia
    stmia base_addr!, {r2-r9} ; copy 32 bytes into stmia
    stmia base_addr!, {r2-r9} ; copy 32 bytes into stmia
    stmia base_addr!, {r2-r9} ; copy 32 bytes into stmia
    stmia base_addr!, {r2-r9} ; copy 32 bytes into stmia
    stmia base_addr!, {r2-r9} ; copy 32 bytes into stmia
    stmia base_addr!, {r2-r9} ; copy 32 bytes into stmia
    stmia base_addr!, {r2-r9} ; copy 32 bytes into stmia
    stmia base_addr!, {r2-r9} ; copy 32 bytes into stmia
    stmia base_addr!, {r2-r9} ; copy 32 bytes into stmia
    stmia base_addr!, {r2-r9} ; copy 32 bytes into stmia
    stmia base_addr!, {r2-r9} ; copy 32 bytes into stmia
    stmia base_addr!, {r2-r9} ; copy 32 bytes into stmia
    stmia base_addr!, {r2-r9} ; copy 32 bytes into stmia
    stmia base_addr!, {r2-r9} ; copy 32 bytes into stmia
    stmia base_addr!, {r2-r9} ; copy 32 bytes into stmia
    stmia base_addr!, {r2-r9} ; copy 32 bytes into stmia
    stmia base_addr!, {r2-r9} ; copy 32 bytes into stmia
    stmia base_addr!, {r2-r9} ; copy 32 bytes into stmia
    stmia base_addr!, {r2-r9} ; copy 32 bytes into stmia
    stmia base_addr!, {r2-r9} ; copy 32 bytes into stmia
    stmia base_addr!, {r2-r9} ; copy 32 bytes into stmia
    stmia base_addr!, {r2-r9} ; copy 32 bytes into stmia
    stmia base_addr!, {r2-r9} ; copy 32 bytes into stmia
    stmia base_addr!, {r2-r9} ; copy 32 bytes into stmia
    stmia base_addr!, {r2-r9} ; copy 32 bytes into stmia
    stmia base_addr!, {r2-r9} ; copy 32 bytes into stmia
    stmia base_addr!, {r2-r9} ; copy 32 bytes into stmia
    stmia base_addr!, {r2-r9} ; copy 32 bytes into stmia
    stmia base_addr!, {r2-r9} ; copy 32 bytes into stmia
    stmia base_addr!, {r2-r9} ; copy 32 bytes into stmia
    stmia base_addr!, {r2-r9} ; copy 32 bytes into stmia
    stmia base_addr!, {r2-r9} ; copy 32 bytes into stmia
    stmia base_addr!, {r2-r9} ; copy 32 bytes into stmia
    stmia base_addr!, {r2-r9} ; copy 32 bytes into stmia
    stmia base_addr!, {r2-r9} ; copy 32 bytes into stmia
    stmia base_addr!, {r2-r9} ; copy 32 bytes into stmia
    stmia base_addr!, {r2-r9} ; copy 32 bytes into stmia
    stmia base_addr!, {r2-r9} ; copy 32 bytes into stmia
    stmia base_addr!, {r2-r9} ; copy 32 bytes into stmia

    ADDS  r11, r7, #0x4000	
    CMP   base_addr, r11
    BLT   read_psram_1
    MOVEQ base_addr, r7

    ldmfd   sp!, {r4-r11}
    bx      lr

    ENDFUNC

    LTORG

SHIFT EQU 0

;para6 DCD 0x1C00BFDC
para6 DCD 0x1000BFFC
para7 DCD -4
para8 DCD 0x34002C44
para9 DCD 0x0
para10 DCD 0x1
para11 DCD -4

fms_test_write_nonseq_psram_2   FUNCTION
    EXPORT  fms_test_write_nonseq_psram_2

    stmfd   sp!, {r4-r11}

    ; write data to psram
    
    MOV   r7, base_addr
    SUBS  base_addr, base_addr, #4    
    MOV   r8, base_addr
    LDR   r9, para7
    LDR   r10, para11
    LDR   r4, para8
    LDR   r5, [r4]
    ;MOV   r7, base_addr
    ; g_ptW5SysTimer->u32_StdaConfig = 0x0;
    ;LDR   r2, para8
    ;LDR   r3, para9
    ;STR   r3, [r2]; =0x34002C40 = 0
    ; g_ptW5SysTimer->u32_StdaConfig = 0x1;
    ;LDR   r3, para10
    ;STR   r3, [r2]; =0x34002C40 = 1

write_psram_t
    STR r2, [base_addr, r9, LSL #SHIFT]!
    STR r2, [base_addr, r9, LSL #SHIFT]!
    STR r2, [base_addr, r9, LSL #SHIFT]!
    STR r2, [base_addr, r9, LSL #SHIFT]!
    STR r2, [base_addr, r9, LSL #SHIFT]!
    STR r2, [base_addr, r9, LSL #SHIFT]!
    STR r2, [base_addr, r9, LSL #SHIFT]!
    STR r2, [base_addr, r10,LSL #SHIFT]!
    STR r2, [base_addr, r9, LSL #SHIFT]!
    STR r2, [base_addr, r9, LSL #SHIFT]!
    STR r2, [base_addr, r9, LSL #SHIFT]!
    STR r2, [base_addr, r9, LSL #SHIFT]!
    STR r2, [base_addr, r9, LSL #SHIFT]!
    STR r2, [base_addr, r9, LSL #SHIFT]!
    STR r2, [base_addr, r9, LSL #SHIFT]!
    STR r2, [base_addr, r10,LSL #SHIFT]!
    STR r2, [base_addr, r9, LSL #SHIFT]!
    STR r2, [base_addr, r9, LSL #SHIFT]!
    STR r2, [base_addr, r9, LSL #SHIFT]!
    STR r2, [base_addr, r9, LSL #SHIFT]!
    STR r2, [base_addr, r9, LSL #SHIFT]!
    STR r2, [base_addr, r9, LSL #SHIFT]!
    STR r2, [base_addr, r9, LSL #SHIFT]!
    STR r2, [base_addr, r10,LSL #SHIFT]!
    STR r2, [base_addr, r9, LSL #SHIFT]!
    STR r2, [base_addr, r9, LSL #SHIFT]!
    STR r2, [base_addr, r9, LSL #SHIFT]!
    STR r2, [base_addr, r9, LSL #SHIFT]!
    STR r2, [base_addr, r9, LSL #SHIFT]!
    STR r2, [base_addr, r9, LSL #SHIFT]!
    STR r2, [base_addr, r9, LSL #SHIFT]!
    STR r2, [base_addr, r10,LSL #SHIFT]!
    STR r2, [base_addr, r9, LSL #SHIFT]!
    STR r2, [base_addr, r9, LSL #SHIFT]!
    STR r2, [base_addr, r9, LSL #SHIFT]!
    STR r2, [base_addr, r9, LSL #SHIFT]!
    STR r2, [base_addr, r9, LSL #SHIFT]!
    STR r2, [base_addr, r9, LSL #SHIFT]!
    STR r2, [base_addr, r9, LSL #SHIFT]!
    STR r2, [base_addr, r10,LSL #SHIFT]!
    STR r2, [base_addr, r9, LSL #SHIFT]!
    STR r2, [base_addr, r9, LSL #SHIFT]!
    STR r2, [base_addr, r9, LSL #SHIFT]!
    STR r2, [base_addr, r9, LSL #SHIFT]!
    STR r2, [base_addr, r9, LSL #SHIFT]!
    STR r2, [base_addr, r9, LSL #SHIFT]!
    STR r2, [base_addr, r9, LSL #SHIFT]!
    STR r2, [base_addr, r10,LSL #SHIFT]!
    STR r2, [base_addr, r9, LSL #SHIFT]!
    STR r2, [base_addr, r9, LSL #SHIFT]!
    STR r2, [base_addr, r9, LSL #SHIFT]!
    STR r2, [base_addr, r9, LSL #SHIFT]!
    STR r2, [base_addr, r9, LSL #SHIFT]!
    STR r2, [base_addr, r9, LSL #SHIFT]!
    STR r2, [base_addr, r9, LSL #SHIFT]!
    STR r2, [base_addr, r10,LSL #SHIFT]!
    STR r2, [base_addr, r9, LSL #SHIFT]!
    STR r2, [base_addr, r9, LSL #SHIFT]!
    STR r2, [base_addr, r9, LSL #SHIFT]!
    STR r2, [base_addr, r9, LSL #SHIFT]!
    STR r2, [base_addr, r9, LSL #SHIFT]!
    STR r2, [base_addr, r9, LSL #SHIFT]!
    STR r2, [base_addr, r9, LSL #SHIFT]!
    STR r2, [base_addr, r10,LSL #SHIFT]!
    STR r2, [base_addr, r9, LSL #SHIFT]!
    STR r2, [base_addr, r9, LSL #SHIFT]!
    STR r2, [base_addr, r9, LSL #SHIFT]!
    STR r2, [base_addr, r9, LSL #SHIFT]!
    STR r2, [base_addr, r9, LSL #SHIFT]!
    STR r2, [base_addr, r9, LSL #SHIFT]!
    STR r2, [base_addr, r9, LSL #SHIFT]!
    STR r2, [base_addr, r10,LSL #SHIFT]!
    STR r2, [base_addr, r9, LSL #SHIFT]!
    STR r2, [base_addr, r9, LSL #SHIFT]!
    STR r2, [base_addr, r9, LSL #SHIFT]!
    STR r2, [base_addr, r9, LSL #SHIFT]!
    STR r2, [base_addr, r9, LSL #SHIFT]!
    STR r2, [base_addr, r9, LSL #SHIFT]!
    STR r2, [base_addr, r9, LSL #SHIFT]!
    STR r2, [base_addr, r10,LSL #SHIFT]!
    STR r2, [base_addr, r9, LSL #SHIFT]!
    STR r2, [base_addr, r9, LSL #SHIFT]!
    STR r2, [base_addr, r9, LSL #SHIFT]!
    STR r2, [base_addr, r9, LSL #SHIFT]!
    STR r2, [base_addr, r9, LSL #SHIFT]!
    STR r2, [base_addr, r9, LSL #SHIFT]!
    STR r2, [base_addr, r9, LSL #SHIFT]!
    STR r2, [base_addr, r10,LSL #SHIFT]!
    STR r2, [base_addr, r9, LSL #SHIFT]!
    STR r2, [base_addr, r9, LSL #SHIFT]!
    STR r2, [base_addr, r9, LSL #SHIFT]!
    STR r2, [base_addr, r9, LSL #SHIFT]!
    STR r2, [base_addr, r9, LSL #SHIFT]!
    STR r2, [base_addr, r9, LSL #SHIFT]!
    STR r2, [base_addr, r9, LSL #SHIFT]!
    STR r2, [base_addr, r10,LSL #SHIFT]!
    STR r2, [base_addr, r9, LSL #SHIFT]!
    STR r2, [base_addr, r9, LSL #SHIFT]!
    STR r2, [base_addr, r9, LSL #SHIFT]!
    STR r2, [base_addr, r9, LSL #SHIFT]!
    STR r2, [base_addr, r9, LSL #SHIFT]!
    STR r2, [base_addr, r9, LSL #SHIFT]!
    STR r2, [base_addr, r9, LSL #SHIFT]!
    STR r2, [base_addr, r10,LSL #SHIFT]!
    STR r2, [base_addr, r9, LSL #SHIFT]!
    STR r2, [base_addr, r9, LSL #SHIFT]!
    STR r2, [base_addr, r9, LSL #SHIFT]!
    STR r2, [base_addr, r9, LSL #SHIFT]!
    STR r2, [base_addr, r9, LSL #SHIFT]!
    STR r2, [base_addr, r9, LSL #SHIFT]!
    STR r2, [base_addr, r9, LSL #SHIFT]!
    STR r2, [base_addr, r10,LSL #SHIFT]!
    STR r2, [base_addr, r9, LSL #SHIFT]!
    STR r2, [base_addr, r9, LSL #SHIFT]!
    STR r2, [base_addr, r9, LSL #SHIFT]!
    STR r2, [base_addr, r9, LSL #SHIFT]!
    STR r2, [base_addr, r9, LSL #SHIFT]!
    STR r2, [base_addr, r9, LSL #SHIFT]!
    STR r2, [base_addr, r9, LSL #SHIFT]!
    STR r2, [base_addr, r10,LSL #SHIFT]!
    STR r2, [base_addr, r9, LSL #SHIFT]!
    STR r2, [base_addr, r9, LSL #SHIFT]!
    STR r2, [base_addr, r9, LSL #SHIFT]!
    STR r2, [base_addr, r9, LSL #SHIFT]!
    STR r2, [base_addr, r9, LSL #SHIFT]!
    STR r2, [base_addr, r9, LSL #SHIFT]!
    STR r2, [base_addr, r9, LSL #SHIFT]!
    STR r2, [base_addr, r10,LSL #SHIFT]!
    STR r2, [base_addr, r9, LSL #SHIFT]!
    STR r2, [base_addr, r9, LSL #SHIFT]!
    STR r2, [base_addr, r9, LSL #SHIFT]!
    STR r2, [base_addr, r9, LSL #SHIFT]!
    STR r2, [base_addr, r9, LSL #SHIFT]!
    STR r2, [base_addr, r9, LSL #SHIFT]!
    STR r2, [base_addr, r9, LSL #SHIFT]!
    STR r2, [base_addr, r10,LSL #SHIFT]!
    STR r2, [base_addr, r9, LSL #SHIFT]!
    STR r2, [base_addr, r9, LSL #SHIFT]!
    STR r2, [base_addr, r9, LSL #SHIFT]!
    STR r2, [base_addr, r9, LSL #SHIFT]!
    STR r2, [base_addr, r9, LSL #SHIFT]!
    STR r2, [base_addr, r9, LSL #SHIFT]!
    STR r2, [base_addr, r9, LSL #SHIFT]!
    STR r2, [base_addr, r10,LSL #SHIFT]!
    STR r2, [base_addr, r9, LSL #SHIFT]!
    STR r2, [base_addr, r9, LSL #SHIFT]!
    STR r2, [base_addr, r9, LSL #SHIFT]!
    STR r2, [base_addr, r9, LSL #SHIFT]!
    STR r2, [base_addr, r9, LSL #SHIFT]!
    STR r2, [base_addr, r9, LSL #SHIFT]!
    STR r2, [base_addr, r9, LSL #SHIFT]!
    STR r2, [base_addr, r10,LSL #SHIFT]!
    STR r2, [base_addr, r9, LSL #SHIFT]!
    STR r2, [base_addr, r9, LSL #SHIFT]!
    STR r2, [base_addr, r9, LSL #SHIFT]!
    STR r2, [base_addr, r9, LSL #SHIFT]!
    STR r2, [base_addr, r9, LSL #SHIFT]!
    STR r2, [base_addr, r9, LSL #SHIFT]!
    STR r2, [base_addr, r9, LSL #SHIFT]!
    STR r2, [base_addr, r10,LSL #SHIFT]!
    STR r2, [base_addr, r9, LSL #SHIFT]!
    STR r2, [base_addr, r9, LSL #SHIFT]!
    STR r2, [base_addr, r9, LSL #SHIFT]!
    STR r2, [base_addr, r9, LSL #SHIFT]!
    STR r2, [base_addr, r9, LSL #SHIFT]!
    STR r2, [base_addr, r9, LSL #SHIFT]!
    STR r2, [base_addr, r9, LSL #SHIFT]!
    STR r2, [base_addr, r10,LSL #SHIFT]!
    STR r2, [base_addr, r9, LSL #SHIFT]!
    STR r2, [base_addr, r9, LSL #SHIFT]!
    STR r2, [base_addr, r9, LSL #SHIFT]!
    STR r2, [base_addr, r9, LSL #SHIFT]!
    STR r2, [base_addr, r9, LSL #SHIFT]!
    STR r2, [base_addr, r9, LSL #SHIFT]!
    STR r2, [base_addr, r9, LSL #SHIFT]!
    STR r2, [base_addr, r10,LSL #SHIFT]!
    STR r2, [base_addr, r9, LSL #SHIFT]!
    STR r2, [base_addr, r9, LSL #SHIFT]!
    STR r2, [base_addr, r9, LSL #SHIFT]!
    STR r2, [base_addr, r9, LSL #SHIFT]!
    STR r2, [base_addr, r9, LSL #SHIFT]!
    STR r2, [base_addr, r9, LSL #SHIFT]!
    STR r2, [base_addr, r9, LSL #SHIFT]!
    STR r2, [base_addr, r10,LSL #SHIFT]!
    STR r2, [base_addr, r9, LSL #SHIFT]!
    STR r2, [base_addr, r9, LSL #SHIFT]!
    STR r2, [base_addr, r9, LSL #SHIFT]!
    STR r2, [base_addr, r9, LSL #SHIFT]!
    STR r2, [base_addr, r9, LSL #SHIFT]!
    STR r2, [base_addr, r9, LSL #SHIFT]!
    STR r2, [base_addr, r9, LSL #SHIFT]!
    STR r2, [base_addr, r10,LSL #SHIFT]!
    STR r2, [base_addr, r9, LSL #SHIFT]!
    STR r2, [base_addr, r9, LSL #SHIFT]!
    STR r2, [base_addr, r9, LSL #SHIFT]!
    STR r2, [base_addr, r9, LSL #SHIFT]!
    STR r2, [base_addr, r9, LSL #SHIFT]!
    STR r2, [base_addr, r9, LSL #SHIFT]!
    STR r2, [base_addr, r9, LSL #SHIFT]!
    STR r2, [base_addr, r10,LSL #SHIFT]!
    STR r2, [base_addr, r9, LSL #SHIFT]!
    STR r2, [base_addr, r9, LSL #SHIFT]!
    STR r2, [base_addr, r9, LSL #SHIFT]!
    STR r2, [base_addr, r9, LSL #SHIFT]!
    STR r2, [base_addr, r9, LSL #SHIFT]!
    STR r2, [base_addr, r9, LSL #SHIFT]!
    STR r2, [base_addr, r9, LSL #SHIFT]!
    STR r2, [base_addr, r10,LSL #SHIFT]!
    STR r2, [base_addr, r9, LSL #SHIFT]!
    STR r2, [base_addr, r9, LSL #SHIFT]!
    STR r2, [base_addr, r9, LSL #SHIFT]!
    STR r2, [base_addr, r9, LSL #SHIFT]!
    STR r2, [base_addr, r9, LSL #SHIFT]!
    STR r2, [base_addr, r9, LSL #SHIFT]!
    STR r2, [base_addr, r9, LSL #SHIFT]!
    STR r2, [base_addr, r10,LSL #SHIFT]!
    STR r2, [base_addr, r9, LSL #SHIFT]!
    STR r2, [base_addr, r9, LSL #SHIFT]!
    STR r2, [base_addr, r9, LSL #SHIFT]!
    STR r2, [base_addr, r9, LSL #SHIFT]!
    STR r2, [base_addr, r9, LSL #SHIFT]!
    STR r2, [base_addr, r9, LSL #SHIFT]!
    STR r2, [base_addr, r9, LSL #SHIFT]!
    STR r2, [base_addr, r10,LSL #SHIFT]!
    STR r2, [base_addr, r9, LSL #SHIFT]!
    STR r2, [base_addr, r9, LSL #SHIFT]!
    STR r2, [base_addr, r9, LSL #SHIFT]!
    STR r2, [base_addr, r9, LSL #SHIFT]!
    STR r2, [base_addr, r9, LSL #SHIFT]!
    STR r2, [base_addr, r9, LSL #SHIFT]!
    STR r2, [base_addr, r9, LSL #SHIFT]!
    STR r2, [base_addr, r10,LSL #SHIFT]!
    STR r2, [base_addr, r9, LSL #SHIFT]!
    STR r2, [base_addr, r9, LSL #SHIFT]!
    STR r2, [base_addr, r9, LSL #SHIFT]!
    STR r2, [base_addr, r9, LSL #SHIFT]!
    STR r2, [base_addr, r9, LSL #SHIFT]!
    STR r2, [base_addr, r9, LSL #SHIFT]!
    STR r2, [base_addr, r9, LSL #SHIFT]!
    STR r2, [base_addr, r10,LSL #SHIFT]!
    STR r2, [base_addr, r9, LSL #SHIFT]!
    STR r2, [base_addr, r9, LSL #SHIFT]!
    STR r2, [base_addr, r9, LSL #SHIFT]!
    STR r2, [base_addr, r9, LSL #SHIFT]!
    STR r2, [base_addr, r9, LSL #SHIFT]!
    STR r2, [base_addr, r9, LSL #SHIFT]!
    STR r2, [base_addr, r9, LSL #SHIFT]!
    STR r2, [base_addr, r10,LSL #SHIFT]!
    STR r2, [base_addr, r9, LSL #SHIFT]!
    STR r2, [base_addr, r9, LSL #SHIFT]!
    STR r2, [base_addr, r9, LSL #SHIFT]!
    STR r2, [base_addr, r9, LSL #SHIFT]!
    STR r2, [base_addr, r9, LSL #SHIFT]!
    STR r2, [base_addr, r9, LSL #SHIFT]!
    STR r2, [base_addr, r9, LSL #SHIFT]!
    STR r2, [base_addr, r10,LSL #SHIFT]!
    STR r2, [base_addr, r9, LSL #SHIFT]!
    STR r2, [base_addr, r9, LSL #SHIFT]!
    STR r2, [base_addr, r9, LSL #SHIFT]!
    STR r2, [base_addr, r9, LSL #SHIFT]!
    STR r2, [base_addr, r9, LSL #SHIFT]!
    STR r2, [base_addr, r9, LSL #SHIFT]!
    STR r2, [base_addr, r9, LSL #SHIFT]!
    STR r2, [base_addr, r10,LSL #SHIFT]!
    STR r2, [base_addr, r9, LSL #SHIFT]!
    STR r2, [base_addr, r9, LSL #SHIFT]!
    STR r2, [base_addr, r9, LSL #SHIFT]!
    STR r2, [base_addr, r9, LSL #SHIFT]!
    STR r2, [base_addr, r9, LSL #SHIFT]!
    STR r2, [base_addr, r9, LSL #SHIFT]!
    STR r2, [base_addr, r9, LSL #SHIFT]!
    STR r2, [base_addr, r10,LSL #SHIFT]!
    STR r2, [base_addr, r9, LSL #SHIFT]!
    STR r2, [base_addr, r9, LSL #SHIFT]!
    STR r2, [base_addr, r9, LSL #SHIFT]!
    STR r2, [base_addr, r9, LSL #SHIFT]!
    STR r2, [base_addr, r9, LSL #SHIFT]!
    STR r2, [base_addr, r9, LSL #SHIFT]!
    STR r2, [base_addr, r9, LSL #SHIFT]!
    STR r2, [base_addr, r10,LSL #SHIFT]!
    STR r2, [base_addr, r9, LSL #SHIFT]!
    STR r2, [base_addr, r9, LSL #SHIFT]!
    STR r2, [base_addr, r9, LSL #SHIFT]!
    STR r2, [base_addr, r9, LSL #SHIFT]!
    STR r2, [base_addr, r9, LSL #SHIFT]!
    STR r2, [base_addr, r9, LSL #SHIFT]!
    STR r2, [base_addr, r9, LSL #SHIFT]!
    STR r2, [base_addr, r10,LSL #SHIFT]!
    STR r2, [base_addr, r9, LSL #SHIFT]!
    STR r2, [base_addr, r9, LSL #SHIFT]!
    STR r2, [base_addr, r9, LSL #SHIFT]!
    STR r2, [base_addr, r9, LSL #SHIFT]!
    STR r2, [base_addr, r9, LSL #SHIFT]!
    STR r2, [base_addr, r9, LSL #SHIFT]!
    STR r2, [base_addr, r9, LSL #SHIFT]!
    STR r2, [base_addr, r10,LSL #SHIFT]!
    STR r2, [base_addr, r9, LSL #SHIFT]!
    STR r2, [base_addr, r9, LSL #SHIFT]!
    STR r2, [base_addr, r9, LSL #SHIFT]!
    STR r2, [base_addr, r9, LSL #SHIFT]!
    STR r2, [base_addr, r9, LSL #SHIFT]!
    STR r2, [base_addr, r9, LSL #SHIFT]!
    STR r2, [base_addr, r9, LSL #SHIFT]!
    STR r2, [base_addr, r10,LSL #SHIFT]!
    STR r2, [base_addr, r9, LSL #SHIFT]!
    STR r2, [base_addr, r9, LSL #SHIFT]!
    STR r2, [base_addr, r9, LSL #SHIFT]!
    STR r2, [base_addr, r9, LSL #SHIFT]!
    STR r2, [base_addr, r9, LSL #SHIFT]!
    STR r2, [base_addr, r9, LSL #SHIFT]!
    STR r2, [base_addr, r9, LSL #SHIFT]!
    STR r2, [base_addr, r10,LSL #SHIFT]!
    STR r2, [base_addr, r9, LSL #SHIFT]!
    STR r2, [base_addr, r9, LSL #SHIFT]!
    STR r2, [base_addr, r9, LSL #SHIFT]!
    STR r2, [base_addr, r9, LSL #SHIFT]!
    STR r2, [base_addr, r9, LSL #SHIFT]!
    STR r2, [base_addr, r9, LSL #SHIFT]!
    STR r2, [base_addr, r9, LSL #SHIFT]!
    STR r2, [base_addr, r10,LSL #SHIFT]!
    STR r2, [base_addr, r9, LSL #SHIFT]!
    STR r2, [base_addr, r9, LSL #SHIFT]!
    STR r2, [base_addr, r9, LSL #SHIFT]!
    STR r2, [base_addr, r9, LSL #SHIFT]!
    STR r2, [base_addr, r9, LSL #SHIFT]!
    STR r2, [base_addr, r9, LSL #SHIFT]!
    STR r2, [base_addr, r9, LSL #SHIFT]!
    STR r2, [base_addr, r10,LSL #SHIFT]!
    STR r2, [base_addr, r9, LSL #SHIFT]!
    STR r2, [base_addr, r9, LSL #SHIFT]!
    STR r2, [base_addr, r9, LSL #SHIFT]!
    STR r2, [base_addr, r9, LSL #SHIFT]!
    STR r2, [base_addr, r9, LSL #SHIFT]!
    STR r2, [base_addr, r9, LSL #SHIFT]!
    STR r2, [base_addr, r9, LSL #SHIFT]!
    STR r2, [base_addr, r10,LSL #SHIFT]!
    STR r2, [base_addr, r9, LSL #SHIFT]!
    STR r2, [base_addr, r9, LSL #SHIFT]!
    STR r2, [base_addr, r9, LSL #SHIFT]!
    STR r2, [base_addr, r9, LSL #SHIFT]!
    STR r2, [base_addr, r9, LSL #SHIFT]!
    STR r2, [base_addr, r9, LSL #SHIFT]!
    STR r2, [base_addr, r9, LSL #SHIFT]!
    STR r2, [base_addr, r10,LSL #SHIFT]!
    STR r2, [base_addr, r9, LSL #SHIFT]!
    STR r2, [base_addr, r9, LSL #SHIFT]!
    STR r2, [base_addr, r9, LSL #SHIFT]!
    STR r2, [base_addr, r9, LSL #SHIFT]!
    STR r2, [base_addr, r9, LSL #SHIFT]!
    STR r2, [base_addr, r9, LSL #SHIFT]!
    STR r2, [base_addr, r9, LSL #SHIFT]!
    STR r2, [base_addr, r10,LSL #SHIFT]!
    STR r2, [base_addr, r9, LSL #SHIFT]!
    STR r2, [base_addr, r9, LSL #SHIFT]!
    STR r2, [base_addr, r9, LSL #SHIFT]!
    STR r2, [base_addr, r9, LSL #SHIFT]!
    STR r2, [base_addr, r9, LSL #SHIFT]!
    STR r2, [base_addr, r9, LSL #SHIFT]!
    STR r2, [base_addr, r9, LSL #SHIFT]!
    STR r2, [base_addr, r10,LSL #SHIFT]!
    STR r2, [base_addr, r9, LSL #SHIFT]!
    STR r2, [base_addr, r9, LSL #SHIFT]!
    STR r2, [base_addr, r9, LSL #SHIFT]!
    STR r2, [base_addr, r9, LSL #SHIFT]!
    STR r2, [base_addr, r9, LSL #SHIFT]!
    STR r2, [base_addr, r9, LSL #SHIFT]!
    STR r2, [base_addr, r9, LSL #SHIFT]!
    STR r2, [base_addr, r10,LSL #SHIFT]!
    STR r2, [base_addr, r9, LSL #SHIFT]!
    STR r2, [base_addr, r9, LSL #SHIFT]!
    STR r2, [base_addr, r9, LSL #SHIFT]!
    STR r2, [base_addr, r9, LSL #SHIFT]!
    STR r2, [base_addr, r9, LSL #SHIFT]!
    STR r2, [base_addr, r9, LSL #SHIFT]!
    STR r2, [base_addr, r9, LSL #SHIFT]!
    STR r2, [base_addr, r10,LSL #SHIFT]!
    STR r2, [base_addr, r9, LSL #SHIFT]!
    STR r2, [base_addr, r9, LSL #SHIFT]!
    STR r2, [base_addr, r9, LSL #SHIFT]!
    STR r2, [base_addr, r9, LSL #SHIFT]!
    STR r2, [base_addr, r9, LSL #SHIFT]!
    STR r2, [base_addr, r9, LSL #SHIFT]!
    STR r2, [base_addr, r9, LSL #SHIFT]!
    STR r2, [base_addr, r10,LSL #SHIFT]!
    STR r2, [base_addr, r9, LSL #SHIFT]!
    STR r2, [base_addr, r9, LSL #SHIFT]!
    STR r2, [base_addr, r9, LSL #SHIFT]!
    STR r2, [base_addr, r9, LSL #SHIFT]!
    STR r2, [base_addr, r9, LSL #SHIFT]!
    STR r2, [base_addr, r9, LSL #SHIFT]!
    STR r2, [base_addr, r9, LSL #SHIFT]!
    STR r2, [base_addr, r10,LSL #SHIFT]!
    STR r2, [base_addr, r9, LSL #SHIFT]!
    STR r2, [base_addr, r9, LSL #SHIFT]!
    STR r2, [base_addr, r9, LSL #SHIFT]!
    STR r2, [base_addr, r9, LSL #SHIFT]!
    STR r2, [base_addr, r9, LSL #SHIFT]!
    STR r2, [base_addr, r9, LSL #SHIFT]!
    STR r2, [base_addr, r9, LSL #SHIFT]!
    STR r2, [base_addr, r10,LSL #SHIFT]!
    STR r2, [base_addr, r9, LSL #SHIFT]!
    STR r2, [base_addr, r9, LSL #SHIFT]!
    STR r2, [base_addr, r9, LSL #SHIFT]!
    STR r2, [base_addr, r9, LSL #SHIFT]!
    STR r2, [base_addr, r9, LSL #SHIFT]!
    STR r2, [base_addr, r9, LSL #SHIFT]!
    STR r2, [base_addr, r9, LSL #SHIFT]!
    STR r2, [base_addr, r10,LSL #SHIFT]!
    STR r2, [base_addr, r9, LSL #SHIFT]!
    STR r2, [base_addr, r9, LSL #SHIFT]!
    STR r2, [base_addr, r9, LSL #SHIFT]!
    STR r2, [base_addr, r9, LSL #SHIFT]!
    STR r2, [base_addr, r9, LSL #SHIFT]!
    STR r2, [base_addr, r9, LSL #SHIFT]!
    STR r2, [base_addr, r9, LSL #SHIFT]!
    STR r2, [base_addr, r10,LSL #SHIFT]!
    STR r2, [base_addr, r9, LSL #SHIFT]!
    STR r2, [base_addr, r9, LSL #SHIFT]!
    STR r2, [base_addr, r9, LSL #SHIFT]!
    STR r2, [base_addr, r9, LSL #SHIFT]!
    STR r2, [base_addr, r9, LSL #SHIFT]!
    STR r2, [base_addr, r9, LSL #SHIFT]!
    STR r2, [base_addr, r9, LSL #SHIFT]!
    STR r2, [base_addr, r10,LSL #SHIFT]!
    STR r2, [base_addr, r9, LSL #SHIFT]!
    STR r2, [base_addr, r9, LSL #SHIFT]!
    STR r2, [base_addr, r9, LSL #SHIFT]!
    STR r2, [base_addr, r9, LSL #SHIFT]!
    STR r2, [base_addr, r9, LSL #SHIFT]!
    STR r2, [base_addr, r9, LSL #SHIFT]!
    STR r2, [base_addr, r9, LSL #SHIFT]!
    STR r2, [base_addr, r10,LSL #SHIFT]!
    STR r2, [base_addr, r9, LSL #SHIFT]!
    STR r2, [base_addr, r9, LSL #SHIFT]!
    STR r2, [base_addr, r9, LSL #SHIFT]!
    STR r2, [base_addr, r9, LSL #SHIFT]!
    STR r2, [base_addr, r9, LSL #SHIFT]!
    STR r2, [base_addr, r9, LSL #SHIFT]!
    STR r2, [base_addr, r9, LSL #SHIFT]!
    STR r2, [base_addr, r10,LSL #SHIFT]!
    STR r2, [base_addr, r9, LSL #SHIFT]!
    STR r2, [base_addr, r9, LSL #SHIFT]!
    STR r2, [base_addr, r9, LSL #SHIFT]!
    STR r2, [base_addr, r9, LSL #SHIFT]!
    STR r2, [base_addr, r9, LSL #SHIFT]!
    STR r2, [base_addr, r9, LSL #SHIFT]!
    STR r2, [base_addr, r9, LSL #SHIFT]!
    STR r2, [base_addr, r10,LSL #SHIFT]!
    STR r2, [base_addr, r9, LSL #SHIFT]!
    STR r2, [base_addr, r9, LSL #SHIFT]!
    STR r2, [base_addr, r9, LSL #SHIFT]!
    STR r2, [base_addr, r9, LSL #SHIFT]!
    STR r2, [base_addr, r9, LSL #SHIFT]!
    STR r2, [base_addr, r9, LSL #SHIFT]!
    STR r2, [base_addr, r9, LSL #SHIFT]!
    STR r2, [base_addr, r10,LSL #SHIFT]!
    STR r2, [base_addr, r9, LSL #SHIFT]!
    STR r2, [base_addr, r9, LSL #SHIFT]!
    STR r2, [base_addr, r9, LSL #SHIFT]!
    STR r2, [base_addr, r9, LSL #SHIFT]!
    STR r2, [base_addr, r9, LSL #SHIFT]!
    STR r2, [base_addr, r9, LSL #SHIFT]!
    STR r2, [base_addr, r9, LSL #SHIFT]!
    STR r2, [base_addr, r10,LSL #SHIFT]!
    STR r2, [base_addr, r9, LSL #SHIFT]!
    STR r2, [base_addr, r9, LSL #SHIFT]!
    STR r2, [base_addr, r9, LSL #SHIFT]!
    STR r2, [base_addr, r9, LSL #SHIFT]!
    STR r2, [base_addr, r9, LSL #SHIFT]!
    STR r2, [base_addr, r9, LSL #SHIFT]!
    STR r2, [base_addr, r9, LSL #SHIFT]!
    STR r2, [base_addr, r10,LSL #SHIFT]!
    STR r2, [base_addr, r9, LSL #SHIFT]!
    STR r2, [base_addr, r9, LSL #SHIFT]!
    STR r2, [base_addr, r9, LSL #SHIFT]!
    STR r2, [base_addr, r9, LSL #SHIFT]!
    STR r2, [base_addr, r9, LSL #SHIFT]!
    STR r2, [base_addr, r9, LSL #SHIFT]!
    STR r2, [base_addr, r9, LSL #SHIFT]!
    STR r2, [base_addr, r10,LSL #SHIFT]!
    STR r2, [base_addr, r9, LSL #SHIFT]!
    STR r2, [base_addr, r9, LSL #SHIFT]!
    STR r2, [base_addr, r9, LSL #SHIFT]!
    STR r2, [base_addr, r9, LSL #SHIFT]!
    STR r2, [base_addr, r9, LSL #SHIFT]!
    STR r2, [base_addr, r9, LSL #SHIFT]!
    STR r2, [base_addr, r9, LSL #SHIFT]!
    STR r2, [base_addr, r10,LSL #SHIFT]!
    STR r2, [base_addr, r9, LSL #SHIFT]!
    STR r2, [base_addr, r9, LSL #SHIFT]!
    STR r2, [base_addr, r9, LSL #SHIFT]!
    STR r2, [base_addr, r9, LSL #SHIFT]!
    STR r2, [base_addr, r9, LSL #SHIFT]!
    STR r2, [base_addr, r9, LSL #SHIFT]!
    STR r2, [base_addr, r9, LSL #SHIFT]!
    STR r2, [base_addr, r10,LSL #SHIFT]!
    STR r2, [base_addr, r9, LSL #SHIFT]!
    STR r2, [base_addr, r9, LSL #SHIFT]!
    STR r2, [base_addr, r9, LSL #SHIFT]!
    STR r2, [base_addr, r9, LSL #SHIFT]!
    STR r2, [base_addr, r9, LSL #SHIFT]!
    STR r2, [base_addr, r9, LSL #SHIFT]!
    STR r2, [base_addr, r9, LSL #SHIFT]!
    STR r2, [base_addr, r10,LSL #SHIFT]!
    STR r2, [base_addr, r9, LSL #SHIFT]!
    STR r2, [base_addr, r9, LSL #SHIFT]!
    STR r2, [base_addr, r9, LSL #SHIFT]!
    STR r2, [base_addr, r9, LSL #SHIFT]!
    STR r2, [base_addr, r9, LSL #SHIFT]!
    STR r2, [base_addr, r9, LSL #SHIFT]!
    STR r2, [base_addr, r9, LSL #SHIFT]!
    STR r2, [base_addr, r10,LSL #SHIFT]!
    STR r2, [base_addr, r9, LSL #SHIFT]!
    STR r2, [base_addr, r9, LSL #SHIFT]!
    STR r2, [base_addr, r9, LSL #SHIFT]!
    STR r2, [base_addr, r9, LSL #SHIFT]!
    STR r2, [base_addr, r9, LSL #SHIFT]!
    STR r2, [base_addr, r9, LSL #SHIFT]!
    STR r2, [base_addr, r9, LSL #SHIFT]!
    STR r2, [base_addr, r10,LSL #SHIFT]!
    STR r2, [base_addr, r9, LSL #SHIFT]!
    STR r2, [base_addr, r9, LSL #SHIFT]!
    STR r2, [base_addr, r9, LSL #SHIFT]!
    STR r2, [base_addr, r9, LSL #SHIFT]!
    STR r2, [base_addr, r9, LSL #SHIFT]!
    STR r2, [base_addr, r9, LSL #SHIFT]!
    STR r2, [base_addr, r9, LSL #SHIFT]!
    STR r2, [base_addr, r10,LSL #SHIFT]!
    STR r2, [base_addr, r9, LSL #SHIFT]!
    STR r2, [base_addr, r9, LSL #SHIFT]!
    STR r2, [base_addr, r9, LSL #SHIFT]!
    STR r2, [base_addr, r9, LSL #SHIFT]!
    STR r2, [base_addr, r9, LSL #SHIFT]!
    STR r2, [base_addr, r9, LSL #SHIFT]!
    STR r2, [base_addr, r9, LSL #SHIFT]!
    STR r2, [base_addr, r10,LSL #SHIFT]!
    STR r2, [base_addr, r9, LSL #SHIFT]!
    STR r2, [base_addr, r9, LSL #SHIFT]!
    STR r2, [base_addr, r9, LSL #SHIFT]!
    STR r2, [base_addr, r9, LSL #SHIFT]!
    STR r2, [base_addr, r9, LSL #SHIFT]!
    STR r2, [base_addr, r9, LSL #SHIFT]!
    STR r2, [base_addr, r9, LSL #SHIFT]!
    STR r2, [base_addr, r10,LSL #SHIFT]!
    STR r2, [base_addr, r9, LSL #SHIFT]!
    STR r2, [base_addr, r9, LSL #SHIFT]!
    STR r2, [base_addr, r9, LSL #SHIFT]!
    STR r2, [base_addr, r9, LSL #SHIFT]!
    STR r2, [base_addr, r9, LSL #SHIFT]!
    STR r2, [base_addr, r9, LSL #SHIFT]!
    STR r2, [base_addr, r9, LSL #SHIFT]!
    STR r2, [base_addr, r10,LSL #SHIFT]!
    STR r2, [base_addr, r9, LSL #SHIFT]!
    STR r2, [base_addr, r9, LSL #SHIFT]!
    STR r2, [base_addr, r9, LSL #SHIFT]!
    STR r2, [base_addr, r9, LSL #SHIFT]!
    STR r2, [base_addr, r9, LSL #SHIFT]!
    STR r2, [base_addr, r9, LSL #SHIFT]!
    STR r2, [base_addr, r9, LSL #SHIFT]!
    STR r2, [base_addr, r10,LSL #SHIFT]!
    STR r2, [base_addr, r9, LSL #SHIFT]!
    STR r2, [base_addr, r9, LSL #SHIFT]!
    STR r2, [base_addr, r9, LSL #SHIFT]!
    STR r2, [base_addr, r9, LSL #SHIFT]!
    STR r2, [base_addr, r9, LSL #SHIFT]!
    STR r2, [base_addr, r9, LSL #SHIFT]!
    STR r2, [base_addr, r9, LSL #SHIFT]!
    STR r2, [base_addr, r10,LSL #SHIFT]!
    STR r2, [base_addr, r9, LSL #SHIFT]!
    STR r2, [base_addr, r9, LSL #SHIFT]!
    STR r2, [base_addr, r9, LSL #SHIFT]!
    STR r2, [base_addr, r9, LSL #SHIFT]!
    STR r2, [base_addr, r9, LSL #SHIFT]!
    STR r2, [base_addr, r9, LSL #SHIFT]!
    STR r2, [base_addr, r9, LSL #SHIFT]!
    STR r2, [base_addr, r10,LSL #SHIFT]!
    STR r2, [base_addr, r9, LSL #SHIFT]!
    STR r2, [base_addr, r9, LSL #SHIFT]!
    STR r2, [base_addr, r9, LSL #SHIFT]!
    STR r2, [base_addr, r9, LSL #SHIFT]!
    STR r2, [base_addr, r9, LSL #SHIFT]!
    STR r2, [base_addr, r9, LSL #SHIFT]!
    STR r2, [base_addr, r9, LSL #SHIFT]!
    STR r2, [base_addr, r10,LSL #SHIFT]!
    STR r2, [base_addr, r9, LSL #SHIFT]!
    STR r2, [base_addr, r9, LSL #SHIFT]!
    STR r2, [base_addr, r9, LSL #SHIFT]!
    STR r2, [base_addr, r9, LSL #SHIFT]!
    STR r2, [base_addr, r9, LSL #SHIFT]!
    STR r2, [base_addr, r9, LSL #SHIFT]!
    STR r2, [base_addr, r9, LSL #SHIFT]!
    STR r2, [base_addr, r10,LSL #SHIFT]!
    STR r2, [base_addr, r9, LSL #SHIFT]!
    STR r2, [base_addr, r9, LSL #SHIFT]!
    STR r2, [base_addr, r9, LSL #SHIFT]!
    STR r2, [base_addr, r9, LSL #SHIFT]!
    STR r2, [base_addr, r9, LSL #SHIFT]!
    STR r2, [base_addr, r9, LSL #SHIFT]!
    STR r2, [base_addr, r9, LSL #SHIFT]!
    STR r2, [base_addr, r10,LSL #SHIFT]!
    STR r2, [base_addr, r9, LSL #SHIFT]!
    STR r2, [base_addr, r9, LSL #SHIFT]!
    STR r2, [base_addr, r9, LSL #SHIFT]!
    STR r2, [base_addr, r9, LSL #SHIFT]!
    STR r2, [base_addr, r9, LSL #SHIFT]!
    STR r2, [base_addr, r9, LSL #SHIFT]!
    STR r2, [base_addr, r9, LSL #SHIFT]!
    STR r2, [base_addr, r10,LSL #SHIFT]!
    STR r2, [base_addr, r9, LSL #SHIFT]!
    STR r2, [base_addr, r9, LSL #SHIFT]!
    STR r2, [base_addr, r9, LSL #SHIFT]!
    STR r2, [base_addr, r9, LSL #SHIFT]!
    STR r2, [base_addr, r9, LSL #SHIFT]!
    STR r2, [base_addr, r9, LSL #SHIFT]!
    STR r2, [base_addr, r9, LSL #SHIFT]!
    STR r2, [base_addr, r10,LSL #SHIFT]!
    STR r2, [base_addr, r9, LSL #SHIFT]!
    STR r2, [base_addr, r9, LSL #SHIFT]!
    STR r2, [base_addr, r9, LSL #SHIFT]!
    STR r2, [base_addr, r9, LSL #SHIFT]!
    STR r2, [base_addr, r9, LSL #SHIFT]!
    STR r2, [base_addr, r9, LSL #SHIFT]!
    STR r2, [base_addr, r9, LSL #SHIFT]!
    STR r2, [base_addr, r10,LSL #SHIFT]!
    STR r2, [base_addr, r9, LSL #SHIFT]!
    STR r2, [base_addr, r9, LSL #SHIFT]!
    STR r2, [base_addr, r9, LSL #SHIFT]!
    STR r2, [base_addr, r9, LSL #SHIFT]!
    STR r2, [base_addr, r9, LSL #SHIFT]!
    STR r2, [base_addr, r9, LSL #SHIFT]!
    STR r2, [base_addr, r9, LSL #SHIFT]!
    STR r2, [base_addr, r10,LSL #SHIFT]!
    STR r2, [base_addr, r9, LSL #SHIFT]!
    STR r2, [base_addr, r9, LSL #SHIFT]!
    STR r2, [base_addr, r9, LSL #SHIFT]!
    STR r2, [base_addr, r9, LSL #SHIFT]!
    STR r2, [base_addr, r9, LSL #SHIFT]!
    STR r2, [base_addr, r9, LSL #SHIFT]!
    STR r2, [base_addr, r9, LSL #SHIFT]!
    STR r2, [base_addr, r10,LSL #SHIFT]!
    STR r2, [base_addr, r9, LSL #SHIFT]!
    STR r2, [base_addr, r9, LSL #SHIFT]!
    STR r2, [base_addr, r9, LSL #SHIFT]!
    STR r2, [base_addr, r9, LSL #SHIFT]!
    STR r2, [base_addr, r9, LSL #SHIFT]!
    STR r2, [base_addr, r9, LSL #SHIFT]!
    STR r2, [base_addr, r9, LSL #SHIFT]!
    STR r2, [base_addr, r10,LSL #SHIFT]!
    STR r2, [base_addr, r9, LSL #SHIFT]!
    STR r2, [base_addr, r9, LSL #SHIFT]!
    STR r2, [base_addr, r9, LSL #SHIFT]!
    STR r2, [base_addr, r9, LSL #SHIFT]!
    STR r2, [base_addr, r9, LSL #SHIFT]!
    STR r2, [base_addr, r9, LSL #SHIFT]!
    STR r2, [base_addr, r9, LSL #SHIFT]!
    STR r2, [base_addr, r10,LSL #SHIFT]!
    STR r2, [base_addr, r9, LSL #SHIFT]!
    STR r2, [base_addr, r9, LSL #SHIFT]!
    STR r2, [base_addr, r9, LSL #SHIFT]!
    STR r2, [base_addr, r9, LSL #SHIFT]!
    STR r2, [base_addr, r9, LSL #SHIFT]!
    STR r2, [base_addr, r9, LSL #SHIFT]!
    STR r2, [base_addr, r9, LSL #SHIFT]!
    STR r2, [base_addr, r10,LSL #SHIFT]!
    STR r2, [base_addr, r9, LSL #SHIFT]!
    STR r2, [base_addr, r9, LSL #SHIFT]!
    STR r2, [base_addr, r9, LSL #SHIFT]!
    STR r2, [base_addr, r9, LSL #SHIFT]!
    STR r2, [base_addr, r9, LSL #SHIFT]!
    STR r2, [base_addr, r9, LSL #SHIFT]!
    STR r2, [base_addr, r9, LSL #SHIFT]!
    STR r2, [base_addr, r10,LSL #SHIFT]!
    STR r2, [base_addr, r9, LSL #SHIFT]!
    STR r2, [base_addr, r9, LSL #SHIFT]!
    STR r2, [base_addr, r9, LSL #SHIFT]!
    STR r2, [base_addr, r9, LSL #SHIFT]!
    STR r2, [base_addr, r9, LSL #SHIFT]!
    STR r2, [base_addr, r9, LSL #SHIFT]!
    STR r2, [base_addr, r9, LSL #SHIFT]!
    STR r2, [base_addr, r10,LSL #SHIFT]!
    STR r2, [base_addr, r9, LSL #SHIFT]!
    STR r2, [base_addr, r9, LSL #SHIFT]!
    STR r2, [base_addr, r9, LSL #SHIFT]!
    STR r2, [base_addr, r9, LSL #SHIFT]!
    STR r2, [base_addr, r9, LSL #SHIFT]!
    STR r2, [base_addr, r9, LSL #SHIFT]!
    STR r2, [base_addr, r9, LSL #SHIFT]!
    STR r2, [base_addr, r10,LSL #SHIFT]!
    STR r2, [base_addr, r9, LSL #SHIFT]!
    STR r2, [base_addr, r9, LSL #SHIFT]!
    STR r2, [base_addr, r9, LSL #SHIFT]!
    STR r2, [base_addr, r9, LSL #SHIFT]!
    STR r2, [base_addr, r9, LSL #SHIFT]!
    STR r2, [base_addr, r9, LSL #SHIFT]!
    STR r2, [base_addr, r9, LSL #SHIFT]!
    STR r2, [base_addr, r10,LSL #SHIFT]!
    STR r2, [base_addr, r9, LSL #SHIFT]!
    STR r2, [base_addr, r9, LSL #SHIFT]!
    STR r2, [base_addr, r9, LSL #SHIFT]!
    STR r2, [base_addr, r9, LSL #SHIFT]!
    STR r2, [base_addr, r9, LSL #SHIFT]!
    STR r2, [base_addr, r9, LSL #SHIFT]!
    STR r2, [base_addr, r9, LSL #SHIFT]!
    STR r2, [base_addr, r10,LSL #SHIFT]!
    STR r2, [base_addr, r9, LSL #SHIFT]!
    STR r2, [base_addr, r9, LSL #SHIFT]!
    STR r2, [base_addr, r9, LSL #SHIFT]!
    STR r2, [base_addr, r9, LSL #SHIFT]!
    STR r2, [base_addr, r9, LSL #SHIFT]!
    STR r2, [base_addr, r9, LSL #SHIFT]!
    STR r2, [base_addr, r9, LSL #SHIFT]!
    STR r2, [base_addr, r10,LSL #SHIFT]!
    STR r2, [base_addr, r9, LSL #SHIFT]!
    STR r2, [base_addr, r9, LSL #SHIFT]!
    STR r2, [base_addr, r9, LSL #SHIFT]!
    STR r2, [base_addr, r9, LSL #SHIFT]!
    STR r2, [base_addr, r9, LSL #SHIFT]!
    STR r2, [base_addr, r9, LSL #SHIFT]!
    STR r2, [base_addr, r9, LSL #SHIFT]!
    STR r2, [base_addr, r10,LSL #SHIFT]!
    STR r2, [base_addr, r9, LSL #SHIFT]!
    STR r2, [base_addr, r9, LSL #SHIFT]!
    STR r2, [base_addr, r9, LSL #SHIFT]!
    STR r2, [base_addr, r9, LSL #SHIFT]!
    STR r2, [base_addr, r9, LSL #SHIFT]!
    STR r2, [base_addr, r9, LSL #SHIFT]!
    STR r2, [base_addr, r9, LSL #SHIFT]!
    STR r2, [base_addr, r10,LSL #SHIFT]!
    STR r2, [base_addr, r9, LSL #SHIFT]!
    STR r2, [base_addr, r9, LSL #SHIFT]!
    STR r2, [base_addr, r9, LSL #SHIFT]!
    STR r2, [base_addr, r9, LSL #SHIFT]!
    STR r2, [base_addr, r9, LSL #SHIFT]!
    STR r2, [base_addr, r9, LSL #SHIFT]!
    STR r2, [base_addr, r9, LSL #SHIFT]!
    STR r2, [base_addr, r10,LSL #SHIFT]!
    STR r2, [base_addr, r9, LSL #SHIFT]!
    STR r2, [base_addr, r9, LSL #SHIFT]!
    STR r2, [base_addr, r9, LSL #SHIFT]!
    STR r2, [base_addr, r9, LSL #SHIFT]!
    STR r2, [base_addr, r9, LSL #SHIFT]!
    STR r2, [base_addr, r9, LSL #SHIFT]!
    STR r2, [base_addr, r9, LSL #SHIFT]!
    STR r2, [base_addr, r10,LSL #SHIFT]!
    STR r2, [base_addr, r9, LSL #SHIFT]!
    STR r2, [base_addr, r9, LSL #SHIFT]!
    STR r2, [base_addr, r9, LSL #SHIFT]!
    STR r2, [base_addr, r9, LSL #SHIFT]!
    STR r2, [base_addr, r9, LSL #SHIFT]!
    STR r2, [base_addr, r9, LSL #SHIFT]!
    STR r2, [base_addr, r9, LSL #SHIFT]!
    STR r2, [base_addr, r10,LSL #SHIFT]!
    STR r2, [base_addr, r9, LSL #SHIFT]!
    STR r2, [base_addr, r9, LSL #SHIFT]!
    STR r2, [base_addr, r9, LSL #SHIFT]!
    STR r2, [base_addr, r9, LSL #SHIFT]!
    STR r2, [base_addr, r9, LSL #SHIFT]!
    STR r2, [base_addr, r9, LSL #SHIFT]!
    STR r2, [base_addr, r9, LSL #SHIFT]!
    STR r2, [base_addr, r10,LSL #SHIFT]!
    STR r2, [base_addr, r9, LSL #SHIFT]!
    STR r2, [base_addr, r9, LSL #SHIFT]!
    STR r2, [base_addr, r9, LSL #SHIFT]!
    STR r2, [base_addr, r9, LSL #SHIFT]!
    STR r2, [base_addr, r9, LSL #SHIFT]!
    STR r2, [base_addr, r9, LSL #SHIFT]!
    STR r2, [base_addr, r9, LSL #SHIFT]!
    STR r2, [base_addr, r10,LSL #SHIFT]!
    STR r2, [base_addr, r9, LSL #SHIFT]!
    STR r2, [base_addr, r9, LSL #SHIFT]!
    STR r2, [base_addr, r9, LSL #SHIFT]!
    STR r2, [base_addr, r9, LSL #SHIFT]!
    STR r2, [base_addr, r9, LSL #SHIFT]!
    STR r2, [base_addr, r9, LSL #SHIFT]!
    STR r2, [base_addr, r9, LSL #SHIFT]!
    STR r2, [base_addr, r10,LSL #SHIFT]!
    STR r2, [base_addr, r9, LSL #SHIFT]!
    STR r2, [base_addr, r9, LSL #SHIFT]!
    STR r2, [base_addr, r9, LSL #SHIFT]!
    STR r2, [base_addr, r9, LSL #SHIFT]!
    STR r2, [base_addr, r9, LSL #SHIFT]!
    STR r2, [base_addr, r9, LSL #SHIFT]!
    STR r2, [base_addr, r9, LSL #SHIFT]!
    STR r2, [base_addr, r10,LSL #SHIFT]!
    STR r2, [base_addr, r9, LSL #SHIFT]!
    STR r2, [base_addr, r9, LSL #SHIFT]!
    STR r2, [base_addr, r9, LSL #SHIFT]!
    STR r2, [base_addr, r9, LSL #SHIFT]!
    STR r2, [base_addr, r9, LSL #SHIFT]!
    STR r2, [base_addr, r9, LSL #SHIFT]!
    STR r2, [base_addr, r9, LSL #SHIFT]!
    STR r2, [base_addr, r10,LSL #SHIFT]!
    STR r2, [base_addr, r9, LSL #SHIFT]!
    STR r2, [base_addr, r9, LSL #SHIFT]!
    STR r2, [base_addr, r9, LSL #SHIFT]!
    STR r2, [base_addr, r9, LSL #SHIFT]!
    STR r2, [base_addr, r9, LSL #SHIFT]!
    STR r2, [base_addr, r9, LSL #SHIFT]!
    STR r2, [base_addr, r9, LSL #SHIFT]!
    STR r2, [base_addr, r10,LSL #SHIFT]!
    STR r2, [base_addr, r9, LSL #SHIFT]!
    STR r2, [base_addr, r9, LSL #SHIFT]!
    STR r2, [base_addr, r9, LSL #SHIFT]!
    STR r2, [base_addr, r9, LSL #SHIFT]!
    STR r2, [base_addr, r9, LSL #SHIFT]!
    STR r2, [base_addr, r9, LSL #SHIFT]!
    STR r2, [base_addr, r9, LSL #SHIFT]!
    STR r2, [base_addr, r10,LSL #SHIFT]!
    STR r2, [base_addr, r9, LSL #SHIFT]!
    STR r2, [base_addr, r9, LSL #SHIFT]!
    STR r2, [base_addr, r9, LSL #SHIFT]!
    STR r2, [base_addr, r9, LSL #SHIFT]!
    STR r2, [base_addr, r9, LSL #SHIFT]!
    STR r2, [base_addr, r9, LSL #SHIFT]!
    STR r2, [base_addr, r9, LSL #SHIFT]!
    STR r2, [base_addr, r10,LSL #SHIFT]!
    STR r2, [base_addr, r9, LSL #SHIFT]!
    STR r2, [base_addr, r9, LSL #SHIFT]!
    STR r2, [base_addr, r9, LSL #SHIFT]!
    STR r2, [base_addr, r9, LSL #SHIFT]!
    STR r2, [base_addr, r9, LSL #SHIFT]!
    STR r2, [base_addr, r9, LSL #SHIFT]!
    STR r2, [base_addr, r9, LSL #SHIFT]!
    STR r2, [base_addr, r10,LSL #SHIFT]!
    STR r2, [base_addr, r9, LSL #SHIFT]!
    STR r2, [base_addr, r9, LSL #SHIFT]!
    STR r2, [base_addr, r9, LSL #SHIFT]!
    STR r2, [base_addr, r9, LSL #SHIFT]!
    STR r2, [base_addr, r9, LSL #SHIFT]!
    STR r2, [base_addr, r9, LSL #SHIFT]!
    STR r2, [base_addr, r9, LSL #SHIFT]!
    STR r2, [base_addr, r10,LSL #SHIFT]!
    STR r2, [base_addr, r9, LSL #SHIFT]!
    STR r2, [base_addr, r9, LSL #SHIFT]!
    STR r2, [base_addr, r9, LSL #SHIFT]!
    STR r2, [base_addr, r9, LSL #SHIFT]!
    STR r2, [base_addr, r9, LSL #SHIFT]!
    STR r2, [base_addr, r9, LSL #SHIFT]!
    STR r2, [base_addr, r9, LSL #SHIFT]!
    STR r2, [base_addr, r10,LSL #SHIFT]!
    STR r2, [base_addr, r9, LSL #SHIFT]!
    STR r2, [base_addr, r9, LSL #SHIFT]!
    STR r2, [base_addr, r9, LSL #SHIFT]!
    STR r2, [base_addr, r9, LSL #SHIFT]!
    STR r2, [base_addr, r9, LSL #SHIFT]!
    STR r2, [base_addr, r9, LSL #SHIFT]!
    STR r2, [base_addr, r9, LSL #SHIFT]!
    STR r2, [base_addr, r10,LSL #SHIFT]!
    STR r2, [base_addr, r9, LSL #SHIFT]!
    STR r2, [base_addr, r9, LSL #SHIFT]!
    STR r2, [base_addr, r9, LSL #SHIFT]!
    STR r2, [base_addr, r9, LSL #SHIFT]!
    STR r2, [base_addr, r9, LSL #SHIFT]!
    STR r2, [base_addr, r9, LSL #SHIFT]!
    STR r2, [base_addr, r9, LSL #SHIFT]!
    STR r2, [base_addr, r10,LSL #SHIFT]!
    STR r2, [base_addr, r9, LSL #SHIFT]!
    STR r2, [base_addr, r9, LSL #SHIFT]!
    STR r2, [base_addr, r9, LSL #SHIFT]!
    STR r2, [base_addr, r9, LSL #SHIFT]!
    STR r2, [base_addr, r9, LSL #SHIFT]!
    STR r2, [base_addr, r9, LSL #SHIFT]!
    STR r2, [base_addr, r9, LSL #SHIFT]!
    STR r2, [base_addr, r10,LSL #SHIFT]!
    STR r2, [base_addr, r9, LSL #SHIFT]!
    STR r2, [base_addr, r9, LSL #SHIFT]!
    STR r2, [base_addr, r9, LSL #SHIFT]!
    STR r2, [base_addr, r9, LSL #SHIFT]!
    STR r2, [base_addr, r9, LSL #SHIFT]!
    STR r2, [base_addr, r9, LSL #SHIFT]!
    STR r2, [base_addr, r9, LSL #SHIFT]!
    STR r2, [base_addr, r10,LSL #SHIFT]!
    STR r2, [base_addr, r9, LSL #SHIFT]!
    STR r2, [base_addr, r9, LSL #SHIFT]!
    STR r2, [base_addr, r9, LSL #SHIFT]!
    STR r2, [base_addr, r9, LSL #SHIFT]!
    STR r2, [base_addr, r9, LSL #SHIFT]!
    STR r2, [base_addr, r9, LSL #SHIFT]!
    STR r2, [base_addr, r9, LSL #SHIFT]!
    STR r2, [base_addr, r10,LSL #SHIFT]!
    STR r2, [base_addr, r9, LSL #SHIFT]!
    STR r2, [base_addr, r9, LSL #SHIFT]!
    STR r2, [base_addr, r9, LSL #SHIFT]!
    STR r2, [base_addr, r9, LSL #SHIFT]!
    STR r2, [base_addr, r9, LSL #SHIFT]!
    STR r2, [base_addr, r9, LSL #SHIFT]!
    STR r2, [base_addr, r9, LSL #SHIFT]!
    STR r2, [base_addr, r10,LSL #SHIFT]!
    STR r2, [base_addr, r9, LSL #SHIFT]!
    STR r2, [base_addr, r9, LSL #SHIFT]!
    STR r2, [base_addr, r9, LSL #SHIFT]!
    STR r2, [base_addr, r9, LSL #SHIFT]!
    STR r2, [base_addr, r9, LSL #SHIFT]!
    STR r2, [base_addr, r9, LSL #SHIFT]!
    STR r2, [base_addr, r9, LSL #SHIFT]!
    STR r2, [base_addr, r10,LSL #SHIFT]!
    STR r2, [base_addr, r9, LSL #SHIFT]!
    STR r2, [base_addr, r9, LSL #SHIFT]!
    STR r2, [base_addr, r9, LSL #SHIFT]!
    STR r2, [base_addr, r9, LSL #SHIFT]!
    STR r2, [base_addr, r9, LSL #SHIFT]!
    STR r2, [base_addr, r9, LSL #SHIFT]!
    STR r2, [base_addr, r9, LSL #SHIFT]!
    STR r2, [base_addr, r10,LSL #SHIFT]!
    STR r2, [base_addr, r9, LSL #SHIFT]!
    STR r2, [base_addr, r9, LSL #SHIFT]!
    STR r2, [base_addr, r9, LSL #SHIFT]!
    STR r2, [base_addr, r9, LSL #SHIFT]!
    STR r2, [base_addr, r9, LSL #SHIFT]!
    STR r2, [base_addr, r9, LSL #SHIFT]!
    STR r2, [base_addr, r9, LSL #SHIFT]!
    STR r2, [base_addr, r10,LSL #SHIFT]!
    STR r2, [base_addr, r9, LSL #SHIFT]!
    STR r2, [base_addr, r9, LSL #SHIFT]!
    STR r2, [base_addr, r9, LSL #SHIFT]!
    STR r2, [base_addr, r9, LSL #SHIFT]!
    STR r2, [base_addr, r9, LSL #SHIFT]!
    STR r2, [base_addr, r9, LSL #SHIFT]!
    STR r2, [base_addr, r9, LSL #SHIFT]!
    STR r2, [base_addr, r10,LSL #SHIFT]!
    STR r2, [base_addr, r9, LSL #SHIFT]!
    STR r2, [base_addr, r9, LSL #SHIFT]!
    STR r2, [base_addr, r9, LSL #SHIFT]!
    STR r2, [base_addr, r9, LSL #SHIFT]!
    STR r2, [base_addr, r9, LSL #SHIFT]!
    STR r2, [base_addr, r9, LSL #SHIFT]!
    STR r2, [base_addr, r9, LSL #SHIFT]!
    STR r2, [base_addr, r10,LSL #SHIFT]!
    STR r2, [base_addr, r9, LSL #SHIFT]!
    STR r2, [base_addr, r9, LSL #SHIFT]!
    STR r2, [base_addr, r9, LSL #SHIFT]!
    STR r2, [base_addr, r9, LSL #SHIFT]!
    STR r2, [base_addr, r9, LSL #SHIFT]!
    STR r2, [base_addr, r9, LSL #SHIFT]!
    STR r2, [base_addr, r9, LSL #SHIFT]!
    STR r2, [base_addr, r10,LSL #SHIFT]!
    STR r2, [base_addr, r9, LSL #SHIFT]!
    STR r2, [base_addr, r9, LSL #SHIFT]!
    STR r2, [base_addr, r9, LSL #SHIFT]!
    STR r2, [base_addr, r9, LSL #SHIFT]!
    STR r2, [base_addr, r9, LSL #SHIFT]!
    STR r2, [base_addr, r9, LSL #SHIFT]!
    STR r2, [base_addr, r9, LSL #SHIFT]!
    STR r2, [base_addr, r10,LSL #SHIFT]!
    STR r2, [base_addr, r9, LSL #SHIFT]!
    STR r2, [base_addr, r9, LSL #SHIFT]!
    STR r2, [base_addr, r9, LSL #SHIFT]!
    STR r2, [base_addr, r9, LSL #SHIFT]!
    STR r2, [base_addr, r9, LSL #SHIFT]!
    STR r2, [base_addr, r9, LSL #SHIFT]!
    STR r2, [base_addr, r9, LSL #SHIFT]!
    STR r2, [base_addr, r10,LSL #SHIFT]!
    STR r2, [base_addr, r9, LSL #SHIFT]!
    STR r2, [base_addr, r9, LSL #SHIFT]!
    STR r2, [base_addr, r9, LSL #SHIFT]!
    STR r2, [base_addr, r9, LSL #SHIFT]!
    STR r2, [base_addr, r9, LSL #SHIFT]!
    STR r2, [base_addr, r9, LSL #SHIFT]!
    STR r2, [base_addr, r9, LSL #SHIFT]!
    STR r2, [base_addr, r10,LSL #SHIFT]!
    STR r2, [base_addr, r9, LSL #SHIFT]!
    STR r2, [base_addr, r9, LSL #SHIFT]!
    STR r2, [base_addr, r9, LSL #SHIFT]!
    STR r2, [base_addr, r9, LSL #SHIFT]!
    STR r2, [base_addr, r9, LSL #SHIFT]!
    STR r2, [base_addr, r9, LSL #SHIFT]!
    STR r2, [base_addr, r9, LSL #SHIFT]!
    STR r2, [base_addr, r10,LSL #SHIFT]!
    STR r2, [base_addr, r9, LSL #SHIFT]!
    STR r2, [base_addr, r9, LSL #SHIFT]!
    STR r2, [base_addr, r9, LSL #SHIFT]!
    STR r2, [base_addr, r9, LSL #SHIFT]!
    STR r2, [base_addr, r9, LSL #SHIFT]!
    STR r2, [base_addr, r9, LSL #SHIFT]!
    STR r2, [base_addr, r9, LSL #SHIFT]!
    STR r2, [base_addr, r10,LSL #SHIFT]!
    STR r2, [base_addr, r9, LSL #SHIFT]!
    STR r2, [base_addr, r9, LSL #SHIFT]!
    STR r2, [base_addr, r9, LSL #SHIFT]!
    STR r2, [base_addr, r9, LSL #SHIFT]!
    STR r2, [base_addr, r9, LSL #SHIFT]!
    STR r2, [base_addr, r9, LSL #SHIFT]!
    STR r2, [base_addr, r9, LSL #SHIFT]!
    STR r2, [base_addr, r10,LSL #SHIFT]!
    STR r2, [base_addr, r9, LSL #SHIFT]!
    STR r2, [base_addr, r9, LSL #SHIFT]!
    STR r2, [base_addr, r9, LSL #SHIFT]!
    STR r2, [base_addr, r9, LSL #SHIFT]!
    STR r2, [base_addr, r9, LSL #SHIFT]!
    STR r2, [base_addr, r9, LSL #SHIFT]!
    STR r2, [base_addr, r9, LSL #SHIFT]!
    STR r2, [base_addr, r10,LSL #SHIFT]!
    STR r2, [base_addr, r9, LSL #SHIFT]!
    STR r2, [base_addr, r9, LSL #SHIFT]!
    STR r2, [base_addr, r9, LSL #SHIFT]!
    STR r2, [base_addr, r9, LSL #SHIFT]!
    STR r2, [base_addr, r9, LSL #SHIFT]!
    STR r2, [base_addr, r9, LSL #SHIFT]!
    STR r2, [base_addr, r9, LSL #SHIFT]!
    STR r2, [base_addr, r10,LSL #SHIFT]!
    STR r2, [base_addr, r9, LSL #SHIFT]!
    STR r2, [base_addr, r9, LSL #SHIFT]!
    STR r2, [base_addr, r9, LSL #SHIFT]!
    STR r2, [base_addr, r9, LSL #SHIFT]!
    STR r2, [base_addr, r9, LSL #SHIFT]!
    STR r2, [base_addr, r9, LSL #SHIFT]!
    STR r2, [base_addr, r9, LSL #SHIFT]!
    STR r2, [base_addr, r10,LSL #SHIFT]!
    STR r2, [base_addr, r9, LSL #SHIFT]!
    STR r2, [base_addr, r9, LSL #SHIFT]!
    STR r2, [base_addr, r9, LSL #SHIFT]!
    STR r2, [base_addr, r9, LSL #SHIFT]!
    STR r2, [base_addr, r9, LSL #SHIFT]!
    STR r2, [base_addr, r9, LSL #SHIFT]!
    STR r2, [base_addr, r9, LSL #SHIFT]!
    STR r2, [base_addr, r10,LSL #SHIFT]!
    STR r2, [base_addr, r9, LSL #SHIFT]!
    STR r2, [base_addr, r9, LSL #SHIFT]!
    STR r2, [base_addr, r9, LSL #SHIFT]!
    STR r2, [base_addr, r9, LSL #SHIFT]!
    STR r2, [base_addr, r9, LSL #SHIFT]!
    STR r2, [base_addr, r9, LSL #SHIFT]!
    STR r2, [base_addr, r9, LSL #SHIFT]!
    STR r2, [base_addr, r10,LSL #SHIFT]!

    SUBS  r11, r7, #0x4000	
    CMP   base_addr, r11
    MOVLT base_addr, r8

    SUBS  loop_time, loop_time, #1  ; loop_time--- and set flags
    BNE   write_psram_t

    LDR   r6, [r4]
    SUB   r6, r5
    MOV   r0, r6
    ;  return g_ptW5SysTimer->u32_StdaCounter
    ;LDR   r2, =0x34002C44
    ;LDR   r0, [r2]

    ; g_ptW5SysTimer->u32_StdaConfig = 0x0;
    ;LDR   r3, =0x0
    ;STR   r3, [r2, #-4]; *0x34002C40 = 0

    ldmfd   sp!, {r4-r11}
    bx      lr

    ENDFUNC

    LTORG


    END

