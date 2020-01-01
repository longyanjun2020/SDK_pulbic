
    AREA |.text|, CODE
;sequential write
loop_time         RN 0
base_addr         RN 1

fms_test_read_seq_psram_1   FUNCTION
    EXPORT  fms_test_read_seq_psram_1 

    stmfd   sp!, {r4-r11}

    ; read data from flash
    LDR     base_addr,  =0x10000000
    ; LDR     loop_time, =0x5746;

read_psram_1
    ldmia base_addr!, {r2-r9} ; copy 32 bytes into registers
    ldmia base_addr!, {r2-r9} ; copy 32 bytes into registers
    ldmia base_addr!, {r2-r9} ; copy 32 bytes into registers
    ldmia base_addr!, {r2-r9} ; copy 32 bytes into registers
    ldmia base_addr!, {r2-r9} ; copy 32 bytes into registers
    ldmia base_addr!, {r2-r9} ; copy 32 bytes into registers
    ldmia base_addr!, {r2-r9} ; copy 32 bytes into registers
    ldmia base_addr!, {r2-r9} ; copy 32 bytes into registers
    ldmia base_addr!, {r2-r9} ; copy 32 bytes into registers
    ldmia base_addr!, {r2-r9} ; copy 32 bytes into registers
    ldmia base_addr!, {r2-r9} ; copy 32 bytes into registers
    ldmia base_addr!, {r2-r9} ; copy 32 bytes into registers
    ldmia base_addr!, {r2-r9} ; copy 32 bytes into registers
    ldmia base_addr!, {r2-r9} ; copy 32 bytes into registers
    ldmia base_addr!, {r2-r9} ; copy 32 bytes into registers
    ldmia base_addr!, {r2-r9} ; copy 32 bytes into registers
    ldmia base_addr!, {r2-r9} ; copy 32 bytes into registers
    ldmia base_addr!, {r2-r9} ; copy 32 bytes into registers
    ldmia base_addr!, {r2-r9} ; copy 32 bytes into registers
    ldmia base_addr!, {r2-r9} ; copy 32 bytes into registers
    ldmia base_addr!, {r2-r9} ; copy 32 bytes into registers
    ldmia base_addr!, {r2-r9} ; copy 32 bytes into registers
    ldmia base_addr!, {r2-r9} ; copy 32 bytes into registers
    ldmia base_addr!, {r2-r9} ; copy 32 bytes into registers
    ldmia base_addr!, {r2-r9} ; copy 32 bytes into registers
    ldmia base_addr!, {r2-r9} ; copy 32 bytes into registers
    ldmia base_addr!, {r2-r9} ; copy 32 bytes into registers
    ldmia base_addr!, {r2-r9} ; copy 32 bytes into registers
    ldmia base_addr!, {r2-r9} ; copy 32 bytes into registers
    ldmia base_addr!, {r2-r9} ; copy 32 bytes into registers
    ldmia base_addr!, {r2-r9} ; copy 32 bytes into registers
    ldmia base_addr!, {r2-r9} ; copy 32 bytes into registers
    ldmia base_addr!, {r2-r9} ; copy 32 bytes into registers
    ldmia base_addr!, {r2-r9} ; copy 32 bytes into registers
    ldmia base_addr!, {r2-r9} ; copy 32 bytes into registers
    ldmia base_addr!, {r2-r9} ; copy 32 bytes into registers
    ldmia base_addr!, {r2-r9} ; copy 32 bytes into registers
    ldmia base_addr!, {r2-r9} ; copy 32 bytes into registers
    ldmia base_addr!, {r2-r9} ; copy 32 bytes into registers
    ldmia base_addr!, {r2-r9} ; copy 32 bytes into registers
    ldmia base_addr!, {r2-r9} ; copy 32 bytes into registers
    ldmia base_addr!, {r2-r9} ; copy 32 bytes into registers
    ldmia base_addr!, {r2-r9} ; copy 32 bytes into registers
    ldmia base_addr!, {r2-r9} ; copy 32 bytes into registers
    ldmia base_addr!, {r2-r9} ; copy 32 bytes into registers
    ldmia base_addr!, {r2-r9} ; copy 32 bytes into registers
    ldmia base_addr!, {r2-r9} ; copy 32 bytes into registers
    ldmia base_addr!, {r2-r9} ; copy 32 bytes into registers
    ldmia base_addr!, {r2-r9} ; copy 32 bytes into registers
    ldmia base_addr!, {r2-r9} ; copy 32 bytes into registers

    LDR   r2, =0x10004000
    CMP   base_addr, r2
    BLT   read_psram_1
    LDRPL base_addr, =0x10000000

    ldmfd   sp!, {r4-r11}
    bx      lr

    ENDFUNC

    LTORG

SHIFT EQU 0

para6 DCD 0x1000BFDC
para7 DCD 4
para8 DCD 0x34002C44
para9 DCD 0x0
para10 DCD 0x1
para11 DCD -60

fms_test_read_seq_psram_2   FUNCTION
    EXPORT  fms_test_read_seq_psram_2

    stmfd   sp!, {r4-r11}

    ; write data to psram
    LDR     base_addr,  para6
    ; LDR     loop_time, =0x5746;
    LDR   r9, para7
    LDR   r10, para11 
    LDR   r4, para8
    LDR   r5, [r4]
    ; g_ptW5SysTimer->u32_StdaConfig = 0x0;
    ; LDR   r2, para8
    ; LDR   r3, para9
    ; STR   r3, [r2]; =0x34002C40 = 0
    ; g_ptW5SysTimer->u32_StdaConfig = 0x1;
    ; LDR   r3, para10
    ; STR   r3, [r2]; =0x34002C40 = 1

write_psram_t
    LDR r2, [base_addr, r9, LSL #SHIFT]!
    LDR r2, [base_addr, r9, LSL #SHIFT]!
    LDR r2, [base_addr, r9, LSL #SHIFT]!
    LDR r2, [base_addr, r9, LSL #SHIFT]!
    LDR r2, [base_addr, r9, LSL #SHIFT]!
    LDR r2, [base_addr, r9, LSL #SHIFT]!
    LDR r2, [base_addr, r9, LSL #SHIFT]!
    LDR r2, [base_addr, r10,LSL #SHIFT]!
    LDR r2, [base_addr, r9, LSL #SHIFT]!
    LDR r2, [base_addr, r9, LSL #SHIFT]!
    LDR r2, [base_addr, r9, LSL #SHIFT]!
    LDR r2, [base_addr, r9, LSL #SHIFT]!
    LDR r2, [base_addr, r9, LSL #SHIFT]!
    LDR r2, [base_addr, r9, LSL #SHIFT]!
    LDR r2, [base_addr, r9, LSL #SHIFT]!
    LDR r2, [base_addr, r10,LSL #SHIFT]!
    LDR r2, [base_addr, r9, LSL #SHIFT]!
    LDR r2, [base_addr, r9, LSL #SHIFT]!
    LDR r2, [base_addr, r9, LSL #SHIFT]!
    LDR r2, [base_addr, r9, LSL #SHIFT]!
    LDR r2, [base_addr, r9, LSL #SHIFT]!
    LDR r2, [base_addr, r9, LSL #SHIFT]!
    LDR r2, [base_addr, r9, LSL #SHIFT]!
    LDR r2, [base_addr, r10,LSL #SHIFT]!
    LDR r2, [base_addr, r9, LSL #SHIFT]!
    LDR r2, [base_addr, r9, LSL #SHIFT]!
    LDR r2, [base_addr, r9, LSL #SHIFT]!
    LDR r2, [base_addr, r9, LSL #SHIFT]!
    LDR r2, [base_addr, r9, LSL #SHIFT]!
    LDR r2, [base_addr, r9, LSL #SHIFT]!
    LDR r2, [base_addr, r9, LSL #SHIFT]!
    LDR r2, [base_addr, r10,LSL #SHIFT]!
    LDR r2, [base_addr, r9, LSL #SHIFT]!
    LDR r2, [base_addr, r9, LSL #SHIFT]!
    LDR r2, [base_addr, r9, LSL #SHIFT]!
    LDR r2, [base_addr, r9, LSL #SHIFT]!
    LDR r2, [base_addr, r9, LSL #SHIFT]!
    LDR r2, [base_addr, r9, LSL #SHIFT]!
    LDR r2, [base_addr, r9, LSL #SHIFT]!
    LDR r2, [base_addr, r10,LSL #SHIFT]!
    LDR r2, [base_addr, r9, LSL #SHIFT]!
    LDR r2, [base_addr, r9, LSL #SHIFT]!
    LDR r2, [base_addr, r9, LSL #SHIFT]!
    LDR r2, [base_addr, r9, LSL #SHIFT]!
    LDR r2, [base_addr, r9, LSL #SHIFT]!
    LDR r2, [base_addr, r9, LSL #SHIFT]!
    LDR r2, [base_addr, r9, LSL #SHIFT]!
    LDR r2, [base_addr, r10,LSL #SHIFT]!
    LDR r2, [base_addr, r9, LSL #SHIFT]!
    LDR r2, [base_addr, r9, LSL #SHIFT]!
    LDR r2, [base_addr, r9, LSL #SHIFT]!
    LDR r2, [base_addr, r9, LSL #SHIFT]!
    LDR r2, [base_addr, r9, LSL #SHIFT]!
    LDR r2, [base_addr, r9, LSL #SHIFT]!
    LDR r2, [base_addr, r9, LSL #SHIFT]!
    LDR r2, [base_addr, r10,LSL #SHIFT]!
    LDR r2, [base_addr, r9, LSL #SHIFT]!
    LDR r2, [base_addr, r9, LSL #SHIFT]!
    LDR r2, [base_addr, r9, LSL #SHIFT]!
    LDR r2, [base_addr, r9, LSL #SHIFT]!
    LDR r2, [base_addr, r9, LSL #SHIFT]!
    LDR r2, [base_addr, r9, LSL #SHIFT]!
    LDR r2, [base_addr, r9, LSL #SHIFT]!
    LDR r2, [base_addr, r10,LSL #SHIFT]!
    LDR r2, [base_addr, r9, LSL #SHIFT]!
    LDR r2, [base_addr, r9, LSL #SHIFT]!
    LDR r2, [base_addr, r9, LSL #SHIFT]!
    LDR r2, [base_addr, r9, LSL #SHIFT]!
    LDR r2, [base_addr, r9, LSL #SHIFT]!
    LDR r2, [base_addr, r9, LSL #SHIFT]!
    LDR r2, [base_addr, r9, LSL #SHIFT]!
    LDR r2, [base_addr, r10,LSL #SHIFT]!
    LDR r2, [base_addr, r9, LSL #SHIFT]!
    LDR r2, [base_addr, r9, LSL #SHIFT]!
    LDR r2, [base_addr, r9, LSL #SHIFT]!
    LDR r2, [base_addr, r9, LSL #SHIFT]!
    LDR r2, [base_addr, r9, LSL #SHIFT]!
    LDR r2, [base_addr, r9, LSL #SHIFT]!
    LDR r2, [base_addr, r9, LSL #SHIFT]!
    LDR r2, [base_addr, r10,LSL #SHIFT]!
    LDR r2, [base_addr, r9, LSL #SHIFT]!
    LDR r2, [base_addr, r9, LSL #SHIFT]!
    LDR r2, [base_addr, r9, LSL #SHIFT]!
    LDR r2, [base_addr, r9, LSL #SHIFT]!
    LDR r2, [base_addr, r9, LSL #SHIFT]!
    LDR r2, [base_addr, r9, LSL #SHIFT]!
    LDR r2, [base_addr, r9, LSL #SHIFT]!
    LDR r2, [base_addr, r10,LSL #SHIFT]!
    LDR r2, [base_addr, r9, LSL #SHIFT]!
    LDR r2, [base_addr, r9, LSL #SHIFT]!
    LDR r2, [base_addr, r9, LSL #SHIFT]!
    LDR r2, [base_addr, r9, LSL #SHIFT]!
    LDR r2, [base_addr, r9, LSL #SHIFT]!
    LDR r2, [base_addr, r9, LSL #SHIFT]!
    LDR r2, [base_addr, r9, LSL #SHIFT]!
    LDR r2, [base_addr, r10,LSL #SHIFT]!
    LDR r2, [base_addr, r9, LSL #SHIFT]!
    LDR r2, [base_addr, r9, LSL #SHIFT]!
    LDR r2, [base_addr, r9, LSL #SHIFT]!
    LDR r2, [base_addr, r9, LSL #SHIFT]!
    LDR r2, [base_addr, r9, LSL #SHIFT]!
    LDR r2, [base_addr, r9, LSL #SHIFT]!
    LDR r2, [base_addr, r9, LSL #SHIFT]!
    LDR r2, [base_addr, r10,LSL #SHIFT]!
    LDR r2, [base_addr, r9, LSL #SHIFT]!
    LDR r2, [base_addr, r9, LSL #SHIFT]!
    LDR r2, [base_addr, r9, LSL #SHIFT]!
    LDR r2, [base_addr, r9, LSL #SHIFT]!
    LDR r2, [base_addr, r9, LSL #SHIFT]!
    LDR r2, [base_addr, r9, LSL #SHIFT]!
    LDR r2, [base_addr, r9, LSL #SHIFT]!
    LDR r2, [base_addr, r10,LSL #SHIFT]!
    LDR r2, [base_addr, r9, LSL #SHIFT]!
    LDR r2, [base_addr, r9, LSL #SHIFT]!
    LDR r2, [base_addr, r9, LSL #SHIFT]!
    LDR r2, [base_addr, r9, LSL #SHIFT]!
    LDR r2, [base_addr, r9, LSL #SHIFT]!
    LDR r2, [base_addr, r9, LSL #SHIFT]!
    LDR r2, [base_addr, r9, LSL #SHIFT]!
    LDR r2, [base_addr, r10,LSL #SHIFT]!
    LDR r2, [base_addr, r9, LSL #SHIFT]!
    LDR r2, [base_addr, r9, LSL #SHIFT]!
    LDR r2, [base_addr, r9, LSL #SHIFT]!
    LDR r2, [base_addr, r9, LSL #SHIFT]!
    LDR r2, [base_addr, r9, LSL #SHIFT]!
    LDR r2, [base_addr, r9, LSL #SHIFT]!
    LDR r2, [base_addr, r9, LSL #SHIFT]!
    LDR r2, [base_addr, r10,LSL #SHIFT]!
    LDR r2, [base_addr, r9, LSL #SHIFT]!
    LDR r2, [base_addr, r9, LSL #SHIFT]!
    LDR r2, [base_addr, r9, LSL #SHIFT]!
    LDR r2, [base_addr, r9, LSL #SHIFT]!
    LDR r2, [base_addr, r9, LSL #SHIFT]!
    LDR r2, [base_addr, r9, LSL #SHIFT]!
    LDR r2, [base_addr, r9, LSL #SHIFT]!
    LDR r2, [base_addr, r10,LSL #SHIFT]!
    LDR r2, [base_addr, r9, LSL #SHIFT]!
    LDR r2, [base_addr, r9, LSL #SHIFT]!
    LDR r2, [base_addr, r9, LSL #SHIFT]!
    LDR r2, [base_addr, r9, LSL #SHIFT]!
    LDR r2, [base_addr, r9, LSL #SHIFT]!
    LDR r2, [base_addr, r9, LSL #SHIFT]!
    LDR r2, [base_addr, r9, LSL #SHIFT]!
    LDR r2, [base_addr, r10,LSL #SHIFT]!
    LDR r2, [base_addr, r9, LSL #SHIFT]!
    LDR r2, [base_addr, r9, LSL #SHIFT]!
    LDR r2, [base_addr, r9, LSL #SHIFT]!
    LDR r2, [base_addr, r9, LSL #SHIFT]!
    LDR r2, [base_addr, r9, LSL #SHIFT]!
    LDR r2, [base_addr, r9, LSL #SHIFT]!
    LDR r2, [base_addr, r9, LSL #SHIFT]!
    LDR r2, [base_addr, r10,LSL #SHIFT]!
    LDR r2, [base_addr, r9, LSL #SHIFT]!
    LDR r2, [base_addr, r9, LSL #SHIFT]!
    LDR r2, [base_addr, r9, LSL #SHIFT]!
    LDR r2, [base_addr, r9, LSL #SHIFT]!
    LDR r2, [base_addr, r9, LSL #SHIFT]!
    LDR r2, [base_addr, r9, LSL #SHIFT]!
    LDR r2, [base_addr, r9, LSL #SHIFT]!
    LDR r2, [base_addr, r10,LSL #SHIFT]!
    LDR r2, [base_addr, r9, LSL #SHIFT]!
    LDR r2, [base_addr, r9, LSL #SHIFT]!
    LDR r2, [base_addr, r9, LSL #SHIFT]!
    LDR r2, [base_addr, r9, LSL #SHIFT]!
    LDR r2, [base_addr, r9, LSL #SHIFT]!
    LDR r2, [base_addr, r9, LSL #SHIFT]!
    LDR r2, [base_addr, r9, LSL #SHIFT]!
    LDR r2, [base_addr, r10,LSL #SHIFT]!
    LDR r2, [base_addr, r9, LSL #SHIFT]!
    LDR r2, [base_addr, r9, LSL #SHIFT]!
    LDR r2, [base_addr, r9, LSL #SHIFT]!
    LDR r2, [base_addr, r9, LSL #SHIFT]!
    LDR r2, [base_addr, r9, LSL #SHIFT]!
    LDR r2, [base_addr, r9, LSL #SHIFT]!
    LDR r2, [base_addr, r9, LSL #SHIFT]!
    LDR r2, [base_addr, r10,LSL #SHIFT]!
    LDR r2, [base_addr, r9, LSL #SHIFT]!
    LDR r2, [base_addr, r9, LSL #SHIFT]!
    LDR r2, [base_addr, r9, LSL #SHIFT]!
    LDR r2, [base_addr, r9, LSL #SHIFT]!
    LDR r2, [base_addr, r9, LSL #SHIFT]!
    LDR r2, [base_addr, r9, LSL #SHIFT]!
    LDR r2, [base_addr, r9, LSL #SHIFT]!
    LDR r2, [base_addr, r10,LSL #SHIFT]!
    LDR r2, [base_addr, r9, LSL #SHIFT]!
    LDR r2, [base_addr, r9, LSL #SHIFT]!
    LDR r2, [base_addr, r9, LSL #SHIFT]!
    LDR r2, [base_addr, r9, LSL #SHIFT]!
    LDR r2, [base_addr, r9, LSL #SHIFT]!
    LDR r2, [base_addr, r9, LSL #SHIFT]!
    LDR r2, [base_addr, r9, LSL #SHIFT]!
    LDR r2, [base_addr, r10,LSL #SHIFT]!
    LDR r2, [base_addr, r9, LSL #SHIFT]!
    LDR r2, [base_addr, r9, LSL #SHIFT]!
    LDR r2, [base_addr, r9, LSL #SHIFT]!
    LDR r2, [base_addr, r9, LSL #SHIFT]!
    LDR r2, [base_addr, r9, LSL #SHIFT]!
    LDR r2, [base_addr, r9, LSL #SHIFT]!
    LDR r2, [base_addr, r9, LSL #SHIFT]!
    LDR r2, [base_addr, r10,LSL #SHIFT]!
    LDR r2, [base_addr, r9, LSL #SHIFT]!
    LDR r2, [base_addr, r9, LSL #SHIFT]!
    LDR r2, [base_addr, r9, LSL #SHIFT]!
    LDR r2, [base_addr, r9, LSL #SHIFT]!
    LDR r2, [base_addr, r9, LSL #SHIFT]!
    LDR r2, [base_addr, r9, LSL #SHIFT]!
    LDR r2, [base_addr, r9, LSL #SHIFT]!
    LDR r2, [base_addr, r10,LSL #SHIFT]!
    LDR r2, [base_addr, r9, LSL #SHIFT]!
    LDR r2, [base_addr, r9, LSL #SHIFT]!
    LDR r2, [base_addr, r9, LSL #SHIFT]!
    LDR r2, [base_addr, r9, LSL #SHIFT]!
    LDR r2, [base_addr, r9, LSL #SHIFT]!
    LDR r2, [base_addr, r9, LSL #SHIFT]!
    LDR r2, [base_addr, r9, LSL #SHIFT]!
    LDR r2, [base_addr, r10,LSL #SHIFT]!
    LDR r2, [base_addr, r9, LSL #SHIFT]!
    LDR r2, [base_addr, r9, LSL #SHIFT]!
    LDR r2, [base_addr, r9, LSL #SHIFT]!
    LDR r2, [base_addr, r9, LSL #SHIFT]!
    LDR r2, [base_addr, r9, LSL #SHIFT]!
    LDR r2, [base_addr, r9, LSL #SHIFT]!
    LDR r2, [base_addr, r9, LSL #SHIFT]!
    LDR r2, [base_addr, r10,LSL #SHIFT]!
    LDR r2, [base_addr, r9, LSL #SHIFT]!
    LDR r2, [base_addr, r9, LSL #SHIFT]!
    LDR r2, [base_addr, r9, LSL #SHIFT]!
    LDR r2, [base_addr, r9, LSL #SHIFT]!
    LDR r2, [base_addr, r9, LSL #SHIFT]!
    LDR r2, [base_addr, r9, LSL #SHIFT]!
    LDR r2, [base_addr, r9, LSL #SHIFT]!
    LDR r2, [base_addr, r10,LSL #SHIFT]!
    LDR r2, [base_addr, r9, LSL #SHIFT]!
    LDR r2, [base_addr, r9, LSL #SHIFT]!
    LDR r2, [base_addr, r9, LSL #SHIFT]!
    LDR r2, [base_addr, r9, LSL #SHIFT]!
    LDR r2, [base_addr, r9, LSL #SHIFT]!
    LDR r2, [base_addr, r9, LSL #SHIFT]!
    LDR r2, [base_addr, r9, LSL #SHIFT]!
    LDR r2, [base_addr, r10,LSL #SHIFT]!
    LDR r2, [base_addr, r9, LSL #SHIFT]!
    LDR r2, [base_addr, r9, LSL #SHIFT]!
    LDR r2, [base_addr, r9, LSL #SHIFT]!
    LDR r2, [base_addr, r9, LSL #SHIFT]!
    LDR r2, [base_addr, r9, LSL #SHIFT]!
    LDR r2, [base_addr, r9, LSL #SHIFT]!
    LDR r2, [base_addr, r9, LSL #SHIFT]!
    LDR r2, [base_addr, r10,LSL #SHIFT]!
    LDR r2, [base_addr, r9, LSL #SHIFT]!
    LDR r2, [base_addr, r9, LSL #SHIFT]!
    LDR r2, [base_addr, r9, LSL #SHIFT]!
    LDR r2, [base_addr, r9, LSL #SHIFT]!
    LDR r2, [base_addr, r9, LSL #SHIFT]!
    LDR r2, [base_addr, r9, LSL #SHIFT]!
    LDR r2, [base_addr, r9, LSL #SHIFT]!
    LDR r2, [base_addr, r10,LSL #SHIFT]!
    LDR r2, [base_addr, r9, LSL #SHIFT]!
    LDR r2, [base_addr, r9, LSL #SHIFT]!
    LDR r2, [base_addr, r9, LSL #SHIFT]!
    LDR r2, [base_addr, r9, LSL #SHIFT]!
    LDR r2, [base_addr, r9, LSL #SHIFT]!
    LDR r2, [base_addr, r9, LSL #SHIFT]!
    LDR r2, [base_addr, r9, LSL #SHIFT]!
    LDR r2, [base_addr, r10,LSL #SHIFT]!
    LDR r2, [base_addr, r9, LSL #SHIFT]!
    LDR r2, [base_addr, r9, LSL #SHIFT]!
    LDR r2, [base_addr, r9, LSL #SHIFT]!
    LDR r2, [base_addr, r9, LSL #SHIFT]!
    LDR r2, [base_addr, r9, LSL #SHIFT]!
    LDR r2, [base_addr, r9, LSL #SHIFT]!
    LDR r2, [base_addr, r9, LSL #SHIFT]!
    LDR r2, [base_addr, r10,LSL #SHIFT]!
    LDR r2, [base_addr, r9, LSL #SHIFT]!
    LDR r2, [base_addr, r9, LSL #SHIFT]!
    LDR r2, [base_addr, r9, LSL #SHIFT]!
    LDR r2, [base_addr, r9, LSL #SHIFT]!
    LDR r2, [base_addr, r9, LSL #SHIFT]!
    LDR r2, [base_addr, r9, LSL #SHIFT]!
    LDR r2, [base_addr, r9, LSL #SHIFT]!
    LDR r2, [base_addr, r10,LSL #SHIFT]!
    LDR r2, [base_addr, r9, LSL #SHIFT]!
    LDR r2, [base_addr, r9, LSL #SHIFT]!
    LDR r2, [base_addr, r9, LSL #SHIFT]!
    LDR r2, [base_addr, r9, LSL #SHIFT]!
    LDR r2, [base_addr, r9, LSL #SHIFT]!
    LDR r2, [base_addr, r9, LSL #SHIFT]!
    LDR r2, [base_addr, r9, LSL #SHIFT]!
    LDR r2, [base_addr, r10,LSL #SHIFT]!
    LDR r2, [base_addr, r9, LSL #SHIFT]!
    LDR r2, [base_addr, r9, LSL #SHIFT]!
    LDR r2, [base_addr, r9, LSL #SHIFT]!
    LDR r2, [base_addr, r9, LSL #SHIFT]!
    LDR r2, [base_addr, r9, LSL #SHIFT]!
    LDR r2, [base_addr, r9, LSL #SHIFT]!
    LDR r2, [base_addr, r9, LSL #SHIFT]!
    LDR r2, [base_addr, r10,LSL #SHIFT]!
    LDR r2, [base_addr, r9, LSL #SHIFT]!
    LDR r2, [base_addr, r9, LSL #SHIFT]!
    LDR r2, [base_addr, r9, LSL #SHIFT]!
    LDR r2, [base_addr, r9, LSL #SHIFT]!
    LDR r2, [base_addr, r9, LSL #SHIFT]!
    LDR r2, [base_addr, r9, LSL #SHIFT]!
    LDR r2, [base_addr, r9, LSL #SHIFT]!
    LDR r2, [base_addr, r10,LSL #SHIFT]!
    LDR r2, [base_addr, r9, LSL #SHIFT]!
    LDR r2, [base_addr, r9, LSL #SHIFT]!
    LDR r2, [base_addr, r9, LSL #SHIFT]!
    LDR r2, [base_addr, r9, LSL #SHIFT]!
    LDR r2, [base_addr, r9, LSL #SHIFT]!
    LDR r2, [base_addr, r9, LSL #SHIFT]!
    LDR r2, [base_addr, r9, LSL #SHIFT]!
    LDR r2, [base_addr, r10,LSL #SHIFT]!
    LDR r2, [base_addr, r9, LSL #SHIFT]!
    LDR r2, [base_addr, r9, LSL #SHIFT]!
    LDR r2, [base_addr, r9, LSL #SHIFT]!
    LDR r2, [base_addr, r9, LSL #SHIFT]!
    LDR r2, [base_addr, r9, LSL #SHIFT]!
    LDR r2, [base_addr, r9, LSL #SHIFT]!
    LDR r2, [base_addr, r9, LSL #SHIFT]!
    LDR r2, [base_addr, r10,LSL #SHIFT]!
    LDR r2, [base_addr, r9, LSL #SHIFT]!
    LDR r2, [base_addr, r9, LSL #SHIFT]!
    LDR r2, [base_addr, r9, LSL #SHIFT]!
    LDR r2, [base_addr, r9, LSL #SHIFT]!
    LDR r2, [base_addr, r9, LSL #SHIFT]!
    LDR r2, [base_addr, r9, LSL #SHIFT]!
    LDR r2, [base_addr, r9, LSL #SHIFT]!
    LDR r2, [base_addr, r10,LSL #SHIFT]!
    LDR r2, [base_addr, r9, LSL #SHIFT]!
    LDR r2, [base_addr, r9, LSL #SHIFT]!
    LDR r2, [base_addr, r9, LSL #SHIFT]!
    LDR r2, [base_addr, r9, LSL #SHIFT]!
    LDR r2, [base_addr, r9, LSL #SHIFT]!
    LDR r2, [base_addr, r9, LSL #SHIFT]!
    LDR r2, [base_addr, r9, LSL #SHIFT]!
    LDR r2, [base_addr, r10,LSL #SHIFT]!
    LDR r2, [base_addr, r9, LSL #SHIFT]!
    LDR r2, [base_addr, r9, LSL #SHIFT]!
    LDR r2, [base_addr, r9, LSL #SHIFT]!
    LDR r2, [base_addr, r9, LSL #SHIFT]!
    LDR r2, [base_addr, r9, LSL #SHIFT]!
    LDR r2, [base_addr, r9, LSL #SHIFT]!
    LDR r2, [base_addr, r9, LSL #SHIFT]!
    LDR r2, [base_addr, r10,LSL #SHIFT]!
    LDR r2, [base_addr, r9, LSL #SHIFT]!
    LDR r2, [base_addr, r9, LSL #SHIFT]!
    LDR r2, [base_addr, r9, LSL #SHIFT]!
    LDR r2, [base_addr, r9, LSL #SHIFT]!
    LDR r2, [base_addr, r9, LSL #SHIFT]!
    LDR r2, [base_addr, r9, LSL #SHIFT]!
    LDR r2, [base_addr, r9, LSL #SHIFT]!
    LDR r2, [base_addr, r10,LSL #SHIFT]!
    LDR r2, [base_addr, r9, LSL #SHIFT]!
    LDR r2, [base_addr, r9, LSL #SHIFT]!
    LDR r2, [base_addr, r9, LSL #SHIFT]!
    LDR r2, [base_addr, r9, LSL #SHIFT]!
    LDR r2, [base_addr, r9, LSL #SHIFT]!
    LDR r2, [base_addr, r9, LSL #SHIFT]!
    LDR r2, [base_addr, r9, LSL #SHIFT]!
    LDR r2, [base_addr, r10,LSL #SHIFT]!
    LDR r2, [base_addr, r9, LSL #SHIFT]!
    LDR r2, [base_addr, r9, LSL #SHIFT]!
    LDR r2, [base_addr, r9, LSL #SHIFT]!
    LDR r2, [base_addr, r9, LSL #SHIFT]!
    LDR r2, [base_addr, r9, LSL #SHIFT]!
    LDR r2, [base_addr, r9, LSL #SHIFT]!
    LDR r2, [base_addr, r9, LSL #SHIFT]!
    LDR r2, [base_addr, r10,LSL #SHIFT]!
    LDR r2, [base_addr, r9, LSL #SHIFT]!
    LDR r2, [base_addr, r9, LSL #SHIFT]!
    LDR r2, [base_addr, r9, LSL #SHIFT]!
    LDR r2, [base_addr, r9, LSL #SHIFT]!
    LDR r2, [base_addr, r9, LSL #SHIFT]!
    LDR r2, [base_addr, r9, LSL #SHIFT]!
    LDR r2, [base_addr, r9, LSL #SHIFT]!
    LDR r2, [base_addr, r10,LSL #SHIFT]!
    LDR r2, [base_addr, r9, LSL #SHIFT]!
    LDR r2, [base_addr, r9, LSL #SHIFT]!
    LDR r2, [base_addr, r9, LSL #SHIFT]!
    LDR r2, [base_addr, r9, LSL #SHIFT]!
    LDR r2, [base_addr, r9, LSL #SHIFT]!
    LDR r2, [base_addr, r9, LSL #SHIFT]!
    LDR r2, [base_addr, r9, LSL #SHIFT]!
    LDR r2, [base_addr, r10,LSL #SHIFT]!
    LDR r2, [base_addr, r9, LSL #SHIFT]!
    LDR r2, [base_addr, r9, LSL #SHIFT]!
    LDR r2, [base_addr, r9, LSL #SHIFT]!
    LDR r2, [base_addr, r9, LSL #SHIFT]!
    LDR r2, [base_addr, r9, LSL #SHIFT]!
    LDR r2, [base_addr, r9, LSL #SHIFT]!
    LDR r2, [base_addr, r9, LSL #SHIFT]!
    LDR r2, [base_addr, r10,LSL #SHIFT]!
    LDR r2, [base_addr, r9, LSL #SHIFT]!
    LDR r2, [base_addr, r9, LSL #SHIFT]!
    LDR r2, [base_addr, r9, LSL #SHIFT]!
    LDR r2, [base_addr, r9, LSL #SHIFT]!
    LDR r2, [base_addr, r9, LSL #SHIFT]!
    LDR r2, [base_addr, r9, LSL #SHIFT]!
    LDR r2, [base_addr, r9, LSL #SHIFT]!
    LDR r2, [base_addr, r10,LSL #SHIFT]!
    LDR r2, [base_addr, r9, LSL #SHIFT]!
    LDR r2, [base_addr, r9, LSL #SHIFT]!
    LDR r2, [base_addr, r9, LSL #SHIFT]!
    LDR r2, [base_addr, r9, LSL #SHIFT]!
    LDR r2, [base_addr, r9, LSL #SHIFT]!
    LDR r2, [base_addr, r9, LSL #SHIFT]!
    LDR r2, [base_addr, r9, LSL #SHIFT]!
    LDR r2, [base_addr, r10,LSL #SHIFT]!
    LDR r2, [base_addr, r9, LSL #SHIFT]!
    LDR r2, [base_addr, r9, LSL #SHIFT]!
    LDR r2, [base_addr, r9, LSL #SHIFT]!
    LDR r2, [base_addr, r9, LSL #SHIFT]!
    LDR r2, [base_addr, r9, LSL #SHIFT]!
    LDR r2, [base_addr, r9, LSL #SHIFT]!
    LDR r2, [base_addr, r9, LSL #SHIFT]!
    LDR r2, [base_addr, r10,LSL #SHIFT]!
    LDR r2, [base_addr, r9, LSL #SHIFT]!
    LDR r2, [base_addr, r9, LSL #SHIFT]!
    LDR r2, [base_addr, r9, LSL #SHIFT]!
    LDR r2, [base_addr, r9, LSL #SHIFT]!
    LDR r2, [base_addr, r9, LSL #SHIFT]!
    LDR r2, [base_addr, r9, LSL #SHIFT]!
    LDR r2, [base_addr, r9, LSL #SHIFT]!
    LDR r2, [base_addr, r10,LSL #SHIFT]!
    LDR r2, [base_addr, r9, LSL #SHIFT]!
    LDR r2, [base_addr, r9, LSL #SHIFT]!
    LDR r2, [base_addr, r9, LSL #SHIFT]!
    LDR r2, [base_addr, r9, LSL #SHIFT]!
    LDR r2, [base_addr, r9, LSL #SHIFT]!
    LDR r2, [base_addr, r9, LSL #SHIFT]!
    LDR r2, [base_addr, r9, LSL #SHIFT]!
    LDR r2, [base_addr, r10,LSL #SHIFT]!
    LDR r2, [base_addr, r9, LSL #SHIFT]!
    LDR r2, [base_addr, r9, LSL #SHIFT]!
    LDR r2, [base_addr, r9, LSL #SHIFT]!
    LDR r2, [base_addr, r9, LSL #SHIFT]!
    LDR r2, [base_addr, r9, LSL #SHIFT]!
    LDR r2, [base_addr, r9, LSL #SHIFT]!
    LDR r2, [base_addr, r9, LSL #SHIFT]!
    LDR r2, [base_addr, r10,LSL #SHIFT]!
    LDR r2, [base_addr, r9, LSL #SHIFT]!
    LDR r2, [base_addr, r9, LSL #SHIFT]!
    LDR r2, [base_addr, r9, LSL #SHIFT]!
    LDR r2, [base_addr, r9, LSL #SHIFT]!
    LDR r2, [base_addr, r9, LSL #SHIFT]!
    LDR r2, [base_addr, r9, LSL #SHIFT]!
    LDR r2, [base_addr, r9, LSL #SHIFT]!
    LDR r2, [base_addr, r10,LSL #SHIFT]!
    LDR r2, [base_addr, r9, LSL #SHIFT]!
    LDR r2, [base_addr, r9, LSL #SHIFT]!
    LDR r2, [base_addr, r9, LSL #SHIFT]!
    LDR r2, [base_addr, r9, LSL #SHIFT]!
    LDR r2, [base_addr, r9, LSL #SHIFT]!
    LDR r2, [base_addr, r9, LSL #SHIFT]!
    LDR r2, [base_addr, r9, LSL #SHIFT]!
    LDR r2, [base_addr, r10,LSL #SHIFT]!
    LDR r2, [base_addr, r9, LSL #SHIFT]!
    LDR r2, [base_addr, r9, LSL #SHIFT]!
    LDR r2, [base_addr, r9, LSL #SHIFT]!
    LDR r2, [base_addr, r9, LSL #SHIFT]!
    LDR r2, [base_addr, r9, LSL #SHIFT]!
    LDR r2, [base_addr, r9, LSL #SHIFT]!
    LDR r2, [base_addr, r9, LSL #SHIFT]!
    LDR r2, [base_addr, r10,LSL #SHIFT]!
    LDR r2, [base_addr, r9, LSL #SHIFT]!
    LDR r2, [base_addr, r9, LSL #SHIFT]!
    LDR r2, [base_addr, r9, LSL #SHIFT]!
    LDR r2, [base_addr, r9, LSL #SHIFT]!
    LDR r2, [base_addr, r9, LSL #SHIFT]!
    LDR r2, [base_addr, r9, LSL #SHIFT]!
    LDR r2, [base_addr, r9, LSL #SHIFT]!
    LDR r2, [base_addr, r10,LSL #SHIFT]!
    LDR r2, [base_addr, r9, LSL #SHIFT]!
    LDR r2, [base_addr, r9, LSL #SHIFT]!
    LDR r2, [base_addr, r9, LSL #SHIFT]!
    LDR r2, [base_addr, r9, LSL #SHIFT]!
    LDR r2, [base_addr, r9, LSL #SHIFT]!
    LDR r2, [base_addr, r9, LSL #SHIFT]!
    LDR r2, [base_addr, r9, LSL #SHIFT]!
    LDR r2, [base_addr, r10,LSL #SHIFT]!
    LDR r2, [base_addr, r9, LSL #SHIFT]!
    LDR r2, [base_addr, r9, LSL #SHIFT]!
    LDR r2, [base_addr, r9, LSL #SHIFT]!
    LDR r2, [base_addr, r9, LSL #SHIFT]!
    LDR r2, [base_addr, r9, LSL #SHIFT]!
    LDR r2, [base_addr, r9, LSL #SHIFT]!
    LDR r2, [base_addr, r9, LSL #SHIFT]!
    LDR r2, [base_addr, r10,LSL #SHIFT]!
    LDR r2, [base_addr, r9, LSL #SHIFT]!
    LDR r2, [base_addr, r9, LSL #SHIFT]!
    LDR r2, [base_addr, r9, LSL #SHIFT]!
    LDR r2, [base_addr, r9, LSL #SHIFT]!
    LDR r2, [base_addr, r9, LSL #SHIFT]!
    LDR r2, [base_addr, r9, LSL #SHIFT]!
    LDR r2, [base_addr, r9, LSL #SHIFT]!
    LDR r2, [base_addr, r10,LSL #SHIFT]!
    LDR r2, [base_addr, r9, LSL #SHIFT]!
    LDR r2, [base_addr, r9, LSL #SHIFT]!
    LDR r2, [base_addr, r9, LSL #SHIFT]!
    LDR r2, [base_addr, r9, LSL #SHIFT]!
    LDR r2, [base_addr, r9, LSL #SHIFT]!
    LDR r2, [base_addr, r9, LSL #SHIFT]!
    LDR r2, [base_addr, r9, LSL #SHIFT]!
    LDR r2, [base_addr, r10,LSL #SHIFT]!
    LDR r2, [base_addr, r9, LSL #SHIFT]!
    LDR r2, [base_addr, r9, LSL #SHIFT]!
    LDR r2, [base_addr, r9, LSL #SHIFT]!
    LDR r2, [base_addr, r9, LSL #SHIFT]!
    LDR r2, [base_addr, r9, LSL #SHIFT]!
    LDR r2, [base_addr, r9, LSL #SHIFT]!
    LDR r2, [base_addr, r9, LSL #SHIFT]!
    LDR r2, [base_addr, r10,LSL #SHIFT]!
    LDR r2, [base_addr, r9, LSL #SHIFT]!
    LDR r2, [base_addr, r9, LSL #SHIFT]!
    LDR r2, [base_addr, r9, LSL #SHIFT]!
    LDR r2, [base_addr, r9, LSL #SHIFT]!
    LDR r2, [base_addr, r9, LSL #SHIFT]!
    LDR r2, [base_addr, r9, LSL #SHIFT]!
    LDR r2, [base_addr, r9, LSL #SHIFT]!
    LDR r2, [base_addr, r10,LSL #SHIFT]!
    LDR r2, [base_addr, r9, LSL #SHIFT]!
    LDR r2, [base_addr, r9, LSL #SHIFT]!
    LDR r2, [base_addr, r9, LSL #SHIFT]!
    LDR r2, [base_addr, r9, LSL #SHIFT]!
    LDR r2, [base_addr, r9, LSL #SHIFT]!
    LDR r2, [base_addr, r9, LSL #SHIFT]!
    LDR r2, [base_addr, r9, LSL #SHIFT]!
    LDR r2, [base_addr, r10,LSL #SHIFT]!
    LDR r2, [base_addr, r9, LSL #SHIFT]!
    LDR r2, [base_addr, r9, LSL #SHIFT]!
    LDR r2, [base_addr, r9, LSL #SHIFT]!
    LDR r2, [base_addr, r9, LSL #SHIFT]!
    LDR r2, [base_addr, r9, LSL #SHIFT]!
    LDR r2, [base_addr, r9, LSL #SHIFT]!
    LDR r2, [base_addr, r9, LSL #SHIFT]!
    LDR r2, [base_addr, r10,LSL #SHIFT]!
    LDR r2, [base_addr, r9, LSL #SHIFT]!
    LDR r2, [base_addr, r9, LSL #SHIFT]!
    LDR r2, [base_addr, r9, LSL #SHIFT]!
    LDR r2, [base_addr, r9, LSL #SHIFT]!
    LDR r2, [base_addr, r9, LSL #SHIFT]!
    LDR r2, [base_addr, r9, LSL #SHIFT]!
    LDR r2, [base_addr, r9, LSL #SHIFT]!
    LDR r2, [base_addr, r10,LSL #SHIFT]!
    LDR r2, [base_addr, r9, LSL #SHIFT]!
    LDR r2, [base_addr, r9, LSL #SHIFT]!
    LDR r2, [base_addr, r9, LSL #SHIFT]!
    LDR r2, [base_addr, r9, LSL #SHIFT]!
    LDR r2, [base_addr, r9, LSL #SHIFT]!
    LDR r2, [base_addr, r9, LSL #SHIFT]!
    LDR r2, [base_addr, r9, LSL #SHIFT]!
    LDR r2, [base_addr, r10,LSL #SHIFT]!
    LDR r2, [base_addr, r9, LSL #SHIFT]!
    LDR r2, [base_addr, r9, LSL #SHIFT]!
    LDR r2, [base_addr, r9, LSL #SHIFT]!
    LDR r2, [base_addr, r9, LSL #SHIFT]!
    LDR r2, [base_addr, r9, LSL #SHIFT]!
    LDR r2, [base_addr, r9, LSL #SHIFT]!
    LDR r2, [base_addr, r9, LSL #SHIFT]!
    LDR r2, [base_addr, r10,LSL #SHIFT]!
    LDR r2, [base_addr, r9, LSL #SHIFT]!
    LDR r2, [base_addr, r9, LSL #SHIFT]!
    LDR r2, [base_addr, r9, LSL #SHIFT]!
    LDR r2, [base_addr, r9, LSL #SHIFT]!
    LDR r2, [base_addr, r9, LSL #SHIFT]!
    LDR r2, [base_addr, r9, LSL #SHIFT]!
    LDR r2, [base_addr, r9, LSL #SHIFT]!
    LDR r2, [base_addr, r10,LSL #SHIFT]!
    LDR r2, [base_addr, r9, LSL #SHIFT]!
    LDR r2, [base_addr, r9, LSL #SHIFT]!
    LDR r2, [base_addr, r9, LSL #SHIFT]!
    LDR r2, [base_addr, r9, LSL #SHIFT]!
    LDR r2, [base_addr, r9, LSL #SHIFT]!
    LDR r2, [base_addr, r9, LSL #SHIFT]!
    LDR r2, [base_addr, r9, LSL #SHIFT]!
    LDR r2, [base_addr, r10,LSL #SHIFT]!
    LDR r2, [base_addr, r9, LSL #SHIFT]!
    LDR r2, [base_addr, r9, LSL #SHIFT]!
    LDR r2, [base_addr, r9, LSL #SHIFT]!
    LDR r2, [base_addr, r9, LSL #SHIFT]!
    LDR r2, [base_addr, r9, LSL #SHIFT]!
    LDR r2, [base_addr, r9, LSL #SHIFT]!
    LDR r2, [base_addr, r9, LSL #SHIFT]!
    LDR r2, [base_addr, r10,LSL #SHIFT]!
    LDR r2, [base_addr, r9, LSL #SHIFT]!
    LDR r2, [base_addr, r9, LSL #SHIFT]!
    LDR r2, [base_addr, r9, LSL #SHIFT]!
    LDR r2, [base_addr, r9, LSL #SHIFT]!
    LDR r2, [base_addr, r9, LSL #SHIFT]!
    LDR r2, [base_addr, r9, LSL #SHIFT]!
    LDR r2, [base_addr, r9, LSL #SHIFT]!
    LDR r2, [base_addr, r10,LSL #SHIFT]!
    LDR r2, [base_addr, r9, LSL #SHIFT]!
    LDR r2, [base_addr, r9, LSL #SHIFT]!
    LDR r2, [base_addr, r9, LSL #SHIFT]!
    LDR r2, [base_addr, r9, LSL #SHIFT]!
    LDR r2, [base_addr, r9, LSL #SHIFT]!
    LDR r2, [base_addr, r9, LSL #SHIFT]!
    LDR r2, [base_addr, r9, LSL #SHIFT]!
    LDR r2, [base_addr, r10,LSL #SHIFT]!
    LDR r2, [base_addr, r9, LSL #SHIFT]!
    LDR r2, [base_addr, r9, LSL #SHIFT]!
    LDR r2, [base_addr, r9, LSL #SHIFT]!
    LDR r2, [base_addr, r9, LSL #SHIFT]!
    LDR r2, [base_addr, r9, LSL #SHIFT]!
    LDR r2, [base_addr, r9, LSL #SHIFT]!
    LDR r2, [base_addr, r9, LSL #SHIFT]!
    LDR r2, [base_addr, r10,LSL #SHIFT]!
    LDR r2, [base_addr, r9, LSL #SHIFT]!
    LDR r2, [base_addr, r9, LSL #SHIFT]!
    LDR r2, [base_addr, r9, LSL #SHIFT]!
    LDR r2, [base_addr, r9, LSL #SHIFT]!
    LDR r2, [base_addr, r9, LSL #SHIFT]!
    LDR r2, [base_addr, r9, LSL #SHIFT]!
    LDR r2, [base_addr, r9, LSL #SHIFT]!
    LDR r2, [base_addr, r10,LSL #SHIFT]!
    LDR r2, [base_addr, r9, LSL #SHIFT]!
    LDR r2, [base_addr, r9, LSL #SHIFT]!
    LDR r2, [base_addr, r9, LSL #SHIFT]!
    LDR r2, [base_addr, r9, LSL #SHIFT]!
    LDR r2, [base_addr, r9, LSL #SHIFT]!
    LDR r2, [base_addr, r9, LSL #SHIFT]!
    LDR r2, [base_addr, r9, LSL #SHIFT]!
    LDR r2, [base_addr, r10,LSL #SHIFT]!
    LDR r2, [base_addr, r9, LSL #SHIFT]!
    LDR r2, [base_addr, r9, LSL #SHIFT]!
    LDR r2, [base_addr, r9, LSL #SHIFT]!
    LDR r2, [base_addr, r9, LSL #SHIFT]!
    LDR r2, [base_addr, r9, LSL #SHIFT]!
    LDR r2, [base_addr, r9, LSL #SHIFT]!
    LDR r2, [base_addr, r9, LSL #SHIFT]!
    LDR r2, [base_addr, r10,LSL #SHIFT]!
    LDR r2, [base_addr, r9, LSL #SHIFT]!
    LDR r2, [base_addr, r9, LSL #SHIFT]!
    LDR r2, [base_addr, r9, LSL #SHIFT]!
    LDR r2, [base_addr, r9, LSL #SHIFT]!
    LDR r2, [base_addr, r9, LSL #SHIFT]!
    LDR r2, [base_addr, r9, LSL #SHIFT]!
    LDR r2, [base_addr, r9, LSL #SHIFT]!
    LDR r2, [base_addr, r10,LSL #SHIFT]!
    LDR r2, [base_addr, r9, LSL #SHIFT]!
    LDR r2, [base_addr, r9, LSL #SHIFT]!
    LDR r2, [base_addr, r9, LSL #SHIFT]!
    LDR r2, [base_addr, r9, LSL #SHIFT]!
    LDR r2, [base_addr, r9, LSL #SHIFT]!
    LDR r2, [base_addr, r9, LSL #SHIFT]!
    LDR r2, [base_addr, r9, LSL #SHIFT]!
    LDR r2, [base_addr, r10,LSL #SHIFT]!
    LDR r2, [base_addr, r9, LSL #SHIFT]!
    LDR r2, [base_addr, r9, LSL #SHIFT]!
    LDR r2, [base_addr, r9, LSL #SHIFT]!
    LDR r2, [base_addr, r9, LSL #SHIFT]!
    LDR r2, [base_addr, r9, LSL #SHIFT]!
    LDR r2, [base_addr, r9, LSL #SHIFT]!
    LDR r2, [base_addr, r9, LSL #SHIFT]!
    LDR r2, [base_addr, r10,LSL #SHIFT]!
    LDR r2, [base_addr, r9, LSL #SHIFT]!
    LDR r2, [base_addr, r9, LSL #SHIFT]!
    LDR r2, [base_addr, r9, LSL #SHIFT]!
    LDR r2, [base_addr, r9, LSL #SHIFT]!
    LDR r2, [base_addr, r9, LSL #SHIFT]!
    LDR r2, [base_addr, r9, LSL #SHIFT]!
    LDR r2, [base_addr, r9, LSL #SHIFT]!
    LDR r2, [base_addr, r10,LSL #SHIFT]!
    LDR r2, [base_addr, r9, LSL #SHIFT]!
    LDR r2, [base_addr, r9, LSL #SHIFT]!
    LDR r2, [base_addr, r9, LSL #SHIFT]!
    LDR r2, [base_addr, r9, LSL #SHIFT]!
    LDR r2, [base_addr, r9, LSL #SHIFT]!
    LDR r2, [base_addr, r9, LSL #SHIFT]!
    LDR r2, [base_addr, r9, LSL #SHIFT]!
    LDR r2, [base_addr, r10,LSL #SHIFT]!
    LDR r2, [base_addr, r9, LSL #SHIFT]!
    LDR r2, [base_addr, r9, LSL #SHIFT]!
    LDR r2, [base_addr, r9, LSL #SHIFT]!
    LDR r2, [base_addr, r9, LSL #SHIFT]!
    LDR r2, [base_addr, r9, LSL #SHIFT]!
    LDR r2, [base_addr, r9, LSL #SHIFT]!
    LDR r2, [base_addr, r9, LSL #SHIFT]!
    LDR r2, [base_addr, r10,LSL #SHIFT]!
    LDR r2, [base_addr, r9, LSL #SHIFT]!
    LDR r2, [base_addr, r9, LSL #SHIFT]!
    LDR r2, [base_addr, r9, LSL #SHIFT]!
    LDR r2, [base_addr, r9, LSL #SHIFT]!
    LDR r2, [base_addr, r9, LSL #SHIFT]!
    LDR r2, [base_addr, r9, LSL #SHIFT]!
    LDR r2, [base_addr, r9, LSL #SHIFT]!
    LDR r2, [base_addr, r10,LSL #SHIFT]!
    LDR r2, [base_addr, r9, LSL #SHIFT]!
    LDR r2, [base_addr, r9, LSL #SHIFT]!
    LDR r2, [base_addr, r9, LSL #SHIFT]!
    LDR r2, [base_addr, r9, LSL #SHIFT]!
    LDR r2, [base_addr, r9, LSL #SHIFT]!
    LDR r2, [base_addr, r9, LSL #SHIFT]!
    LDR r2, [base_addr, r9, LSL #SHIFT]!
    LDR r2, [base_addr, r10,LSL #SHIFT]!
    LDR r2, [base_addr, r9, LSL #SHIFT]!
    LDR r2, [base_addr, r9, LSL #SHIFT]!
    LDR r2, [base_addr, r9, LSL #SHIFT]!
    LDR r2, [base_addr, r9, LSL #SHIFT]!
    LDR r2, [base_addr, r9, LSL #SHIFT]!
    LDR r2, [base_addr, r9, LSL #SHIFT]!
    LDR r2, [base_addr, r9, LSL #SHIFT]!
    LDR r2, [base_addr, r10,LSL #SHIFT]!
    LDR r2, [base_addr, r9, LSL #SHIFT]!
    LDR r2, [base_addr, r9, LSL #SHIFT]!
    LDR r2, [base_addr, r9, LSL #SHIFT]!
    LDR r2, [base_addr, r9, LSL #SHIFT]!
    LDR r2, [base_addr, r9, LSL #SHIFT]!
    LDR r2, [base_addr, r9, LSL #SHIFT]!
    LDR r2, [base_addr, r9, LSL #SHIFT]!
    LDR r2, [base_addr, r10,LSL #SHIFT]!
    LDR r2, [base_addr, r9, LSL #SHIFT]!
    LDR r2, [base_addr, r9, LSL #SHIFT]!
    LDR r2, [base_addr, r9, LSL #SHIFT]!
    LDR r2, [base_addr, r9, LSL #SHIFT]!
    LDR r2, [base_addr, r9, LSL #SHIFT]!
    LDR r2, [base_addr, r9, LSL #SHIFT]!
    LDR r2, [base_addr, r9, LSL #SHIFT]!
    LDR r2, [base_addr, r10,LSL #SHIFT]!
    LDR r2, [base_addr, r9, LSL #SHIFT]!
    LDR r2, [base_addr, r9, LSL #SHIFT]!
    LDR r2, [base_addr, r9, LSL #SHIFT]!
    LDR r2, [base_addr, r9, LSL #SHIFT]!
    LDR r2, [base_addr, r9, LSL #SHIFT]!
    LDR r2, [base_addr, r9, LSL #SHIFT]!
    LDR r2, [base_addr, r9, LSL #SHIFT]!
    LDR r2, [base_addr, r10,LSL #SHIFT]!
    LDR r2, [base_addr, r9, LSL #SHIFT]!
    LDR r2, [base_addr, r9, LSL #SHIFT]!
    LDR r2, [base_addr, r9, LSL #SHIFT]!
    LDR r2, [base_addr, r9, LSL #SHIFT]!
    LDR r2, [base_addr, r9, LSL #SHIFT]!
    LDR r2, [base_addr, r9, LSL #SHIFT]!
    LDR r2, [base_addr, r9, LSL #SHIFT]!
    LDR r2, [base_addr, r10,LSL #SHIFT]!
    LDR r2, [base_addr, r9, LSL #SHIFT]!
    LDR r2, [base_addr, r9, LSL #SHIFT]!
    LDR r2, [base_addr, r9, LSL #SHIFT]!
    LDR r2, [base_addr, r9, LSL #SHIFT]!
    LDR r2, [base_addr, r9, LSL #SHIFT]!
    LDR r2, [base_addr, r9, LSL #SHIFT]!
    LDR r2, [base_addr, r9, LSL #SHIFT]!
    LDR r2, [base_addr, r10,LSL #SHIFT]!
    LDR r2, [base_addr, r9, LSL #SHIFT]!
    LDR r2, [base_addr, r9, LSL #SHIFT]!
    LDR r2, [base_addr, r9, LSL #SHIFT]!
    LDR r2, [base_addr, r9, LSL #SHIFT]!
    LDR r2, [base_addr, r9, LSL #SHIFT]!
    LDR r2, [base_addr, r9, LSL #SHIFT]!
    LDR r2, [base_addr, r9, LSL #SHIFT]!
    LDR r2, [base_addr, r10,LSL #SHIFT]!
    LDR r2, [base_addr, r9, LSL #SHIFT]!
    LDR r2, [base_addr, r9, LSL #SHIFT]!
    LDR r2, [base_addr, r9, LSL #SHIFT]!
    LDR r2, [base_addr, r9, LSL #SHIFT]!
    LDR r2, [base_addr, r9, LSL #SHIFT]!
    LDR r2, [base_addr, r9, LSL #SHIFT]!
    LDR r2, [base_addr, r9, LSL #SHIFT]!
    LDR r2, [base_addr, r10,LSL #SHIFT]!
    LDR r2, [base_addr, r9, LSL #SHIFT]!
    LDR r2, [base_addr, r9, LSL #SHIFT]!
    LDR r2, [base_addr, r9, LSL #SHIFT]!
    LDR r2, [base_addr, r9, LSL #SHIFT]!
    LDR r2, [base_addr, r9, LSL #SHIFT]!
    LDR r2, [base_addr, r9, LSL #SHIFT]!
    LDR r2, [base_addr, r9, LSL #SHIFT]!
    LDR r2, [base_addr, r10,LSL #SHIFT]!
    LDR r2, [base_addr, r9, LSL #SHIFT]!
    LDR r2, [base_addr, r9, LSL #SHIFT]!
    LDR r2, [base_addr, r9, LSL #SHIFT]!
    LDR r2, [base_addr, r9, LSL #SHIFT]!
    LDR r2, [base_addr, r9, LSL #SHIFT]!
    LDR r2, [base_addr, r9, LSL #SHIFT]!
    LDR r2, [base_addr, r9, LSL #SHIFT]!
    LDR r2, [base_addr, r10,LSL #SHIFT]!
    LDR r2, [base_addr, r9, LSL #SHIFT]!
    LDR r2, [base_addr, r9, LSL #SHIFT]!
    LDR r2, [base_addr, r9, LSL #SHIFT]!
    LDR r2, [base_addr, r9, LSL #SHIFT]!
    LDR r2, [base_addr, r9, LSL #SHIFT]!
    LDR r2, [base_addr, r9, LSL #SHIFT]!
    LDR r2, [base_addr, r9, LSL #SHIFT]!
    LDR r2, [base_addr, r10,LSL #SHIFT]!
    LDR r2, [base_addr, r9, LSL #SHIFT]!
    LDR r2, [base_addr, r9, LSL #SHIFT]!
    LDR r2, [base_addr, r9, LSL #SHIFT]!
    LDR r2, [base_addr, r9, LSL #SHIFT]!
    LDR r2, [base_addr, r9, LSL #SHIFT]!
    LDR r2, [base_addr, r9, LSL #SHIFT]!
    LDR r2, [base_addr, r9, LSL #SHIFT]!
    LDR r2, [base_addr, r10,LSL #SHIFT]!
    LDR r2, [base_addr, r9, LSL #SHIFT]!
    LDR r2, [base_addr, r9, LSL #SHIFT]!
    LDR r2, [base_addr, r9, LSL #SHIFT]!
    LDR r2, [base_addr, r9, LSL #SHIFT]!
    LDR r2, [base_addr, r9, LSL #SHIFT]!
    LDR r2, [base_addr, r9, LSL #SHIFT]!
    LDR r2, [base_addr, r9, LSL #SHIFT]!
    LDR r2, [base_addr, r10,LSL #SHIFT]!
    LDR r2, [base_addr, r9, LSL #SHIFT]!
    LDR r2, [base_addr, r9, LSL #SHIFT]!
    LDR r2, [base_addr, r9, LSL #SHIFT]!
    LDR r2, [base_addr, r9, LSL #SHIFT]!
    LDR r2, [base_addr, r9, LSL #SHIFT]!
    LDR r2, [base_addr, r9, LSL #SHIFT]!
    LDR r2, [base_addr, r9, LSL #SHIFT]!
    LDR r2, [base_addr, r10,LSL #SHIFT]!
    LDR r2, [base_addr, r9, LSL #SHIFT]!
    LDR r2, [base_addr, r9, LSL #SHIFT]!
    LDR r2, [base_addr, r9, LSL #SHIFT]!
    LDR r2, [base_addr, r9, LSL #SHIFT]!
    LDR r2, [base_addr, r9, LSL #SHIFT]!
    LDR r2, [base_addr, r9, LSL #SHIFT]!
    LDR r2, [base_addr, r9, LSL #SHIFT]!
    LDR r2, [base_addr, r10,LSL #SHIFT]!
    LDR r2, [base_addr, r9, LSL #SHIFT]!
    LDR r2, [base_addr, r9, LSL #SHIFT]!
    LDR r2, [base_addr, r9, LSL #SHIFT]!
    LDR r2, [base_addr, r9, LSL #SHIFT]!
    LDR r2, [base_addr, r9, LSL #SHIFT]!
    LDR r2, [base_addr, r9, LSL #SHIFT]!
    LDR r2, [base_addr, r9, LSL #SHIFT]!
    LDR r2, [base_addr, r10,LSL #SHIFT]!
    LDR r2, [base_addr, r9, LSL #SHIFT]!
    LDR r2, [base_addr, r9, LSL #SHIFT]!
    LDR r2, [base_addr, r9, LSL #SHIFT]!
    LDR r2, [base_addr, r9, LSL #SHIFT]!
    LDR r2, [base_addr, r9, LSL #SHIFT]!
    LDR r2, [base_addr, r9, LSL #SHIFT]!
    LDR r2, [base_addr, r9, LSL #SHIFT]!
    LDR r2, [base_addr, r10,LSL #SHIFT]!
    LDR r2, [base_addr, r9, LSL #SHIFT]!
    LDR r2, [base_addr, r9, LSL #SHIFT]!
    LDR r2, [base_addr, r9, LSL #SHIFT]!
    LDR r2, [base_addr, r9, LSL #SHIFT]!
    LDR r2, [base_addr, r9, LSL #SHIFT]!
    LDR r2, [base_addr, r9, LSL #SHIFT]!
    LDR r2, [base_addr, r9, LSL #SHIFT]!
    LDR r2, [base_addr, r10,LSL #SHIFT]!
    LDR r2, [base_addr, r9, LSL #SHIFT]!
    LDR r2, [base_addr, r9, LSL #SHIFT]!
    LDR r2, [base_addr, r9, LSL #SHIFT]!
    LDR r2, [base_addr, r9, LSL #SHIFT]!
    LDR r2, [base_addr, r9, LSL #SHIFT]!
    LDR r2, [base_addr, r9, LSL #SHIFT]!
    LDR r2, [base_addr, r9, LSL #SHIFT]!
    LDR r2, [base_addr, r10,LSL #SHIFT]!
    LDR r2, [base_addr, r9, LSL #SHIFT]!
    LDR r2, [base_addr, r9, LSL #SHIFT]!
    LDR r2, [base_addr, r9, LSL #SHIFT]!
    LDR r2, [base_addr, r9, LSL #SHIFT]!
    LDR r2, [base_addr, r9, LSL #SHIFT]!
    LDR r2, [base_addr, r9, LSL #SHIFT]!
    LDR r2, [base_addr, r9, LSL #SHIFT]!
    LDR r2, [base_addr, r10,LSL #SHIFT]!
    LDR r2, [base_addr, r9, LSL #SHIFT]!
    LDR r2, [base_addr, r9, LSL #SHIFT]!
    LDR r2, [base_addr, r9, LSL #SHIFT]!
    LDR r2, [base_addr, r9, LSL #SHIFT]!
    LDR r2, [base_addr, r9, LSL #SHIFT]!
    LDR r2, [base_addr, r9, LSL #SHIFT]!
    LDR r2, [base_addr, r9, LSL #SHIFT]!
    LDR r2, [base_addr, r10,LSL #SHIFT]!
    LDR r2, [base_addr, r9, LSL #SHIFT]!
    LDR r2, [base_addr, r9, LSL #SHIFT]!
    LDR r2, [base_addr, r9, LSL #SHIFT]!
    LDR r2, [base_addr, r9, LSL #SHIFT]!
    LDR r2, [base_addr, r9, LSL #SHIFT]!
    LDR r2, [base_addr, r9, LSL #SHIFT]!
    LDR r2, [base_addr, r9, LSL #SHIFT]!
    LDR r2, [base_addr, r10,LSL #SHIFT]!
    LDR r2, [base_addr, r9, LSL #SHIFT]!
    LDR r2, [base_addr, r9, LSL #SHIFT]!
    LDR r2, [base_addr, r9, LSL #SHIFT]!
    LDR r2, [base_addr, r9, LSL #SHIFT]!
    LDR r2, [base_addr, r9, LSL #SHIFT]!
    LDR r2, [base_addr, r9, LSL #SHIFT]!
    LDR r2, [base_addr, r9, LSL #SHIFT]!
    LDR r2, [base_addr, r10,LSL #SHIFT]!
    LDR r2, [base_addr, r9, LSL #SHIFT]!
    LDR r2, [base_addr, r9, LSL #SHIFT]!
    LDR r2, [base_addr, r9, LSL #SHIFT]!
    LDR r2, [base_addr, r9, LSL #SHIFT]!
    LDR r2, [base_addr, r9, LSL #SHIFT]!
    LDR r2, [base_addr, r9, LSL #SHIFT]!
    LDR r2, [base_addr, r9, LSL #SHIFT]!
    LDR r2, [base_addr, r10,LSL #SHIFT]!
    LDR r2, [base_addr, r9, LSL #SHIFT]!
    LDR r2, [base_addr, r9, LSL #SHIFT]!
    LDR r2, [base_addr, r9, LSL #SHIFT]!
    LDR r2, [base_addr, r9, LSL #SHIFT]!
    LDR r2, [base_addr, r9, LSL #SHIFT]!
    LDR r2, [base_addr, r9, LSL #SHIFT]!
    LDR r2, [base_addr, r9, LSL #SHIFT]!
    LDR r2, [base_addr, r10,LSL #SHIFT]!
    LDR r2, [base_addr, r9, LSL #SHIFT]!
    LDR r2, [base_addr, r9, LSL #SHIFT]!
    LDR r2, [base_addr, r9, LSL #SHIFT]!
    LDR r2, [base_addr, r9, LSL #SHIFT]!
    LDR r2, [base_addr, r9, LSL #SHIFT]!
    LDR r2, [base_addr, r9, LSL #SHIFT]!
    LDR r2, [base_addr, r9, LSL #SHIFT]!
    LDR r2, [base_addr, r10,LSL #SHIFT]!
    LDR r2, [base_addr, r9, LSL #SHIFT]!
    LDR r2, [base_addr, r9, LSL #SHIFT]!
    LDR r2, [base_addr, r9, LSL #SHIFT]!
    LDR r2, [base_addr, r9, LSL #SHIFT]!
    LDR r2, [base_addr, r9, LSL #SHIFT]!
    LDR r2, [base_addr, r9, LSL #SHIFT]!
    LDR r2, [base_addr, r9, LSL #SHIFT]!
    LDR r2, [base_addr, r10,LSL #SHIFT]!
    LDR r2, [base_addr, r9, LSL #SHIFT]!
    LDR r2, [base_addr, r9, LSL #SHIFT]!
    LDR r2, [base_addr, r9, LSL #SHIFT]!
    LDR r2, [base_addr, r9, LSL #SHIFT]!
    LDR r2, [base_addr, r9, LSL #SHIFT]!
    LDR r2, [base_addr, r9, LSL #SHIFT]!
    LDR r2, [base_addr, r9, LSL #SHIFT]!
    LDR r2, [base_addr, r10,LSL #SHIFT]!
    LDR r2, [base_addr, r9, LSL #SHIFT]!
    LDR r2, [base_addr, r9, LSL #SHIFT]!
    LDR r2, [base_addr, r9, LSL #SHIFT]!
    LDR r2, [base_addr, r9, LSL #SHIFT]!
    LDR r2, [base_addr, r9, LSL #SHIFT]!
    LDR r2, [base_addr, r9, LSL #SHIFT]!
    LDR r2, [base_addr, r9, LSL #SHIFT]!
    LDR r2, [base_addr, r10,LSL #SHIFT]!
    LDR r2, [base_addr, r9, LSL #SHIFT]!
    LDR r2, [base_addr, r9, LSL #SHIFT]!
    LDR r2, [base_addr, r9, LSL #SHIFT]!
    LDR r2, [base_addr, r9, LSL #SHIFT]!
    LDR r2, [base_addr, r9, LSL #SHIFT]!
    LDR r2, [base_addr, r9, LSL #SHIFT]!
    LDR r2, [base_addr, r9, LSL #SHIFT]!
    LDR r2, [base_addr, r10,LSL #SHIFT]!
    LDR r2, [base_addr, r9, LSL #SHIFT]!
    LDR r2, [base_addr, r9, LSL #SHIFT]!
    LDR r2, [base_addr, r9, LSL #SHIFT]!
    LDR r2, [base_addr, r9, LSL #SHIFT]!
    LDR r2, [base_addr, r9, LSL #SHIFT]!
    LDR r2, [base_addr, r9, LSL #SHIFT]!
    LDR r2, [base_addr, r9, LSL #SHIFT]!
    LDR r2, [base_addr, r10,LSL #SHIFT]!
    LDR r2, [base_addr, r9, LSL #SHIFT]!
    LDR r2, [base_addr, r9, LSL #SHIFT]!
    LDR r2, [base_addr, r9, LSL #SHIFT]!
    LDR r2, [base_addr, r9, LSL #SHIFT]!
    LDR r2, [base_addr, r9, LSL #SHIFT]!
    LDR r2, [base_addr, r9, LSL #SHIFT]!
    LDR r2, [base_addr, r9, LSL #SHIFT]!
    LDR r2, [base_addr, r10,LSL #SHIFT]!
    LDR r2, [base_addr, r9, LSL #SHIFT]!
    LDR r2, [base_addr, r9, LSL #SHIFT]!
    LDR r2, [base_addr, r9, LSL #SHIFT]!
    LDR r2, [base_addr, r9, LSL #SHIFT]!
    LDR r2, [base_addr, r9, LSL #SHIFT]!
    LDR r2, [base_addr, r9, LSL #SHIFT]!
    LDR r2, [base_addr, r9, LSL #SHIFT]!
    LDR r2, [base_addr, r10,LSL #SHIFT]!
    LDR r2, [base_addr, r9, LSL #SHIFT]!
    LDR r2, [base_addr, r9, LSL #SHIFT]!
    LDR r2, [base_addr, r9, LSL #SHIFT]!
    LDR r2, [base_addr, r9, LSL #SHIFT]!
    LDR r2, [base_addr, r9, LSL #SHIFT]!
    LDR r2, [base_addr, r9, LSL #SHIFT]!
    LDR r2, [base_addr, r9, LSL #SHIFT]!
    LDR r2, [base_addr, r10,LSL #SHIFT]!
    LDR r2, [base_addr, r9, LSL #SHIFT]!
    LDR r2, [base_addr, r9, LSL #SHIFT]!
    LDR r2, [base_addr, r9, LSL #SHIFT]!
    LDR r2, [base_addr, r9, LSL #SHIFT]!
    LDR r2, [base_addr, r9, LSL #SHIFT]!
    LDR r2, [base_addr, r9, LSL #SHIFT]!
    LDR r2, [base_addr, r9, LSL #SHIFT]!
    LDR r2, [base_addr, r10,LSL #SHIFT]!
    LDR r2, [base_addr, r9, LSL #SHIFT]!
    LDR r2, [base_addr, r9, LSL #SHIFT]!
    LDR r2, [base_addr, r9, LSL #SHIFT]!
    LDR r2, [base_addr, r9, LSL #SHIFT]!
    LDR r2, [base_addr, r9, LSL #SHIFT]!
    LDR r2, [base_addr, r9, LSL #SHIFT]!
    LDR r2, [base_addr, r9, LSL #SHIFT]!
    LDR r2, [base_addr, r10,LSL #SHIFT]!
    LDR r2, [base_addr, r9, LSL #SHIFT]!
    LDR r2, [base_addr, r9, LSL #SHIFT]!
    LDR r2, [base_addr, r9, LSL #SHIFT]!
    LDR r2, [base_addr, r9, LSL #SHIFT]!
    LDR r2, [base_addr, r9, LSL #SHIFT]!
    LDR r2, [base_addr, r9, LSL #SHIFT]!
    LDR r2, [base_addr, r9, LSL #SHIFT]!
    LDR r2, [base_addr, r10,LSL #SHIFT]!
    LDR r2, [base_addr, r9, LSL #SHIFT]!
    LDR r2, [base_addr, r9, LSL #SHIFT]!
    LDR r2, [base_addr, r9, LSL #SHIFT]!
    LDR r2, [base_addr, r9, LSL #SHIFT]!
    LDR r2, [base_addr, r9, LSL #SHIFT]!
    LDR r2, [base_addr, r9, LSL #SHIFT]!
    LDR r2, [base_addr, r9, LSL #SHIFT]!
    LDR r2, [base_addr, r10,LSL #SHIFT]!
    LDR r2, [base_addr, r9, LSL #SHIFT]!
    LDR r2, [base_addr, r9, LSL #SHIFT]!
    LDR r2, [base_addr, r9, LSL #SHIFT]!
    LDR r2, [base_addr, r9, LSL #SHIFT]!
    LDR r2, [base_addr, r9, LSL #SHIFT]!
    LDR r2, [base_addr, r9, LSL #SHIFT]!
    LDR r2, [base_addr, r9, LSL #SHIFT]!
    LDR r2, [base_addr, r10,LSL #SHIFT]!
    LDR r2, [base_addr, r9, LSL #SHIFT]!
    LDR r2, [base_addr, r9, LSL #SHIFT]!
    LDR r2, [base_addr, r9, LSL #SHIFT]!
    LDR r2, [base_addr, r9, LSL #SHIFT]!
    LDR r2, [base_addr, r9, LSL #SHIFT]!
    LDR r2, [base_addr, r9, LSL #SHIFT]!
    LDR r2, [base_addr, r9, LSL #SHIFT]!
    LDR r2, [base_addr, r10,LSL #SHIFT]!
    LDR r2, [base_addr, r9, LSL #SHIFT]!
    LDR r2, [base_addr, r9, LSL #SHIFT]!
    LDR r2, [base_addr, r9, LSL #SHIFT]!
    LDR r2, [base_addr, r9, LSL #SHIFT]!
    LDR r2, [base_addr, r9, LSL #SHIFT]!
    LDR r2, [base_addr, r9, LSL #SHIFT]!
    LDR r2, [base_addr, r9, LSL #SHIFT]!
    LDR r2, [base_addr, r10,LSL #SHIFT]!
    
    LDR   r3, =0x10008000
    CMP   base_addr, r3
    LDRLT base_addr, =0x1000BFDC

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

