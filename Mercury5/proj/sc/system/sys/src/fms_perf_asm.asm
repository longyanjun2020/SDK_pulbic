
    AREA |.text|, CODE

loop_time         RN 0
base_addr         RN 1

fms_test_read_flash_new   FUNCTION
    EXPORT  fms_test_read_flash_new

    stmfd   sp!, {r4-r11}

    ; read data from flash
    LDR     base_addr,  =0x0C000004
    ; LDR     loop_time, =0x5746;

    ; g_ptW5SysTimer->u32_StdaConfig = 0x0;
    LDR   r2, =0x34002C40
    LDR   r3, =0x0
    STR   r3, [r2]; *0x34002C40 = 0
    ; g_ptW5SysTimer->u32_StdaConfig = 0x1;
    LDR   r3, =0x1
    STR   r3, [r2]; *0x34002C40 = 1

read_flash_n
    ldmia base_addr!, {r2}      ; copy 4 bytes into registers
    add   base_addr , base_addr, #28 ; shift 28 bytes
    ldmia base_addr!, {r2}      ; copy 4 bytes into registers
    add   base_addr , base_addr, #28 ; shift 28 bytes
    ldmia base_addr!, {r2}      ; copy 4 bytes into registers
    add   base_addr , base_addr, #28 ; shift 28 bytes
    ldmia base_addr!, {r2}      ; copy 4 bytes into registers
    add   base_addr , base_addr, #28 ; shift 28 bytes
    ldmia base_addr!, {r2}      ; copy 4 bytes into registers
    add   base_addr , base_addr, #28 ; shift 28 bytes
    ldmia base_addr!, {r2}      ; copy 4 bytes into registers
    add   base_addr , base_addr, #28 ; shift 28 bytes
    ldmia base_addr!, {r2}      ; copy 4 bytes into registers
    add   base_addr , base_addr, #28 ; shift 28 bytes
    ldmia base_addr!, {r2}      ; copy 4 bytes into registers
    add   base_addr , base_addr, #28 ; shift 28 bytes
    ldmia base_addr!, {r2}      ; copy 4 bytes into registers
    add   base_addr , base_addr, #28 ; shift 28 bytes
    ldmia base_addr!, {r2}      ; copy 4 bytes into registers
    add   base_addr , base_addr, #28 ; shift 28 bytes
    ldmia base_addr!, {r2}      ; copy 4 bytes into registers
    add   base_addr , base_addr, #28 ; shift 28 bytes
    ldmia base_addr!, {r2}      ; copy 4 bytes into registers
    add   base_addr , base_addr, #28 ; shift 28 bytes
    ldmia base_addr!, {r2}      ; copy 4 bytes into registers
    add   base_addr , base_addr, #28 ; shift 28 bytes
    ldmia base_addr!, {r2}      ; copy 4 bytes into registers
    add   base_addr , base_addr, #28 ; shift 28 bytes
    ldmia base_addr!, {r2}      ; copy 4 bytes into registers
    add   base_addr , base_addr, #28 ; shift 28 bytes
    ldmia base_addr!, {r2}      ; copy 4 bytes into registers
    add   base_addr , base_addr, #28 ; shift 28 bytes
    ldmia base_addr!, {r2}      ; copy 4 bytes into registers
    add   base_addr , base_addr, #28 ; shift 28 bytes
    ldmia base_addr!, {r2}      ; copy 4 bytes into registers
    add   base_addr , base_addr, #28 ; shift 28 bytes
    ldmia base_addr!, {r2}      ; copy 4 bytes into registers
    add   base_addr , base_addr, #28 ; shift 28 bytes
    ldmia base_addr!, {r2}      ; copy 4 bytes into registers
    add   base_addr , base_addr, #28 ; shift 28 bytes
    ldmia base_addr!, {r2}      ; copy 4 bytes into registers
    add   base_addr , base_addr, #28 ; shift 28 bytes
    ldmia base_addr!, {r2}      ; copy 4 bytes into registers
    add   base_addr , base_addr, #28 ; shift 28 bytes
    ldmia base_addr!, {r2}      ; copy 4 bytes into registers
    add   base_addr , base_addr, #28 ; shift 28 bytes
    ldmia base_addr!, {r2}      ; copy 4 bytes into registers
    add   base_addr , base_addr, #28 ; shift 28 bytes
    ldmia base_addr!, {r2}      ; copy 4 bytes into registers
    add   base_addr , base_addr, #28 ; shift 28 bytes
    ldmia base_addr!, {r2}      ; copy 4 bytes into registers
    add   base_addr , base_addr, #28 ; shift 28 bytes
    ldmia base_addr!, {r2}      ; copy 4 bytes into registers
    add   base_addr , base_addr, #28 ; shift 28 bytes
    ldmia base_addr!, {r2}      ; copy 4 bytes into registers
    add   base_addr , base_addr, #28 ; shift 28 bytes
    ldmia base_addr!, {r2}      ; copy 4 bytes into registers
    add   base_addr , base_addr, #28 ; shift 28 bytes
    ldmia base_addr!, {r2}      ; copy 4 bytes into registers
    add   base_addr , base_addr, #28 ; shift 28 bytes
    ldmia base_addr!, {r2}      ; copy 4 bytes into registers
    add   base_addr , base_addr, #28 ; shift 28 bytes
    ldmia base_addr!, {r2}      ; copy 4 bytes into registers
    add   base_addr , base_addr, #28 ; shift 28 bytes
    ldmia base_addr!, {r2}      ; copy 4 bytes into registers
    add   base_addr , base_addr, #28 ; shift 28 bytes
    ldmia base_addr!, {r2}      ; copy 4 bytes into registers
    add   base_addr , base_addr, #28 ; shift 28 bytes
    ldmia base_addr!, {r2}      ; copy 4 bytes into registers
    add   base_addr , base_addr, #28 ; shift 28 bytes
    ldmia base_addr!, {r2}      ; copy 4 bytes into registers
    add   base_addr , base_addr, #28 ; shift 28 bytes
    ldmia base_addr!, {r2}      ; copy 4 bytes into registers
    add   base_addr , base_addr, #28 ; shift 28 bytes
    ldmia base_addr!, {r2}      ; copy 4 bytes into registers
    add   base_addr , base_addr, #28 ; shift 28 bytes
    ldmia base_addr!, {r2}      ; copy 4 bytes into registers
    add   base_addr , base_addr, #28 ; shift 28 bytes
    ldmia base_addr!, {r2}      ; copy 4 bytes into registers
    add   base_addr , base_addr, #28 ; shift 28 bytes
    ldmia base_addr!, {r2}      ; copy 4 bytes into registers
    add   base_addr , base_addr, #28 ; shift 28 bytes
    ldmia base_addr!, {r2}      ; copy 4 bytes into registers
    add   base_addr , base_addr, #28 ; shift 28 bytes
    ldmia base_addr!, {r2}      ; copy 4 bytes into registers
    add   base_addr , base_addr, #28 ; shift 28 bytes
    ldmia base_addr!, {r2}      ; copy 4 bytes into registers
    add   base_addr , base_addr, #28 ; shift 28 bytes
    ldmia base_addr!, {r2}      ; copy 4 bytes into registers
    add   base_addr , base_addr, #28 ; shift 28 bytes
    ldmia base_addr!, {r2}      ; copy 4 bytes into registers
    add   base_addr , base_addr, #28 ; shift 28 bytes
    ldmia base_addr!, {r2}      ; copy 4 bytes into registers
    add   base_addr , base_addr, #28 ; shift 28 bytes
    ldmia base_addr!, {r2}      ; copy 4 bytes into registers
    add   base_addr , base_addr, #28 ; shift 28 bytes
    ldmia base_addr!, {r2}      ; copy 4 bytes into registers
    add   base_addr , base_addr, #28 ; shift 28 bytes
    ldmia base_addr!, {r2}      ; copy 4 bytes into registers
    add   base_addr , base_addr, #28 ; shift 28 bytes

    LDR   r2, =0x0CFFF000
    CMP   base_addr, r2
    LDRPL base_addr, =0x0C000004

    SUBS  loop_time, loop_time, #1  ; loop_time--- and set flags
    BNE   read_flash_n

    ;  return g_ptW5SysTimer->u32_StdaCounter
    LDR   r2, =0x34002C44
    LDR   r0, [r2]

    ; g_ptW5SysTimer->u32_StdaConfig = 0x0;
    LDR   r3, =0x0
    STR   r3, [r2, #-4]; *0x34002C40 = 0

    ldmfd   sp!, {r4-r11}
    bx      lr

    ENDFUNC


;
;
;
fms_test_read_psram_new   FUNCTION
    EXPORT  fms_test_read_psram_new

    stmfd   sp!, {r4-r11}

    ; read data from flash
    LDR     base_addr,  =0x10300004
    ; LDR     loop_time, =0x5746;

    ; g_ptW5SysTimer->u32_StdaConfig = 0x0;
    LDR   r2, =0x34002C40
    LDR   r3, =0x0
    STR   r3, [r2]; *0x34002C40 = 0
    ; g_ptW5SysTimer->u32_StdaConfig = 0x1;
    LDR   r3, =0x1
    STR   r3, [r2]; *0x34002C40 = 1

read_psram_n
    ldmia base_addr!, {r2}      ; copy 4 bytes into registers
    add   base_addr , base_addr, #28 ; shift 28 bytes
    ldmia base_addr!, {r2}      ; copy 4 bytes into registers
    add   base_addr , base_addr, #28 ; shift 28 bytes
    ldmia base_addr!, {r2}      ; copy 4 bytes into registers
    add   base_addr , base_addr, #28 ; shift 28 bytes
    ldmia base_addr!, {r2}      ; copy 4 bytes into registers
    add   base_addr , base_addr, #28 ; shift 28 bytes
    ldmia base_addr!, {r2}      ; copy 4 bytes into registers
    add   base_addr , base_addr, #28 ; shift 28 bytes
    ldmia base_addr!, {r2}      ; copy 4 bytes into registers
    add   base_addr , base_addr, #28 ; shift 28 bytes
    ldmia base_addr!, {r2}      ; copy 4 bytes into registers
    add   base_addr , base_addr, #28 ; shift 28 bytes
    ldmia base_addr!, {r2}      ; copy 4 bytes into registers
    add   base_addr , base_addr, #28 ; shift 28 bytes
    ldmia base_addr!, {r2}      ; copy 4 bytes into registers
    add   base_addr , base_addr, #28 ; shift 28 bytes
    ldmia base_addr!, {r2}      ; copy 4 bytes into registers
    add   base_addr , base_addr, #28 ; shift 28 bytes
    ldmia base_addr!, {r2}      ; copy 4 bytes into registers
    add   base_addr , base_addr, #28 ; shift 28 bytes
    ldmia base_addr!, {r2}      ; copy 4 bytes into registers
    add   base_addr , base_addr, #28 ; shift 28 bytes
    ldmia base_addr!, {r2}      ; copy 4 bytes into registers
    add   base_addr , base_addr, #28 ; shift 28 bytes
    ldmia base_addr!, {r2}      ; copy 4 bytes into registers
    add   base_addr , base_addr, #28 ; shift 28 bytes
    ldmia base_addr!, {r2}      ; copy 4 bytes into registers
    add   base_addr , base_addr, #28 ; shift 28 bytes
    ldmia base_addr!, {r2}      ; copy 4 bytes into registers
    add   base_addr , base_addr, #28 ; shift 28 bytes
    ldmia base_addr!, {r2}      ; copy 4 bytes into registers
    add   base_addr , base_addr, #28 ; shift 28 bytes
    ldmia base_addr!, {r2}      ; copy 4 bytes into registers
    add   base_addr , base_addr, #28 ; shift 28 bytes
    ldmia base_addr!, {r2}      ; copy 4 bytes into registers
    add   base_addr , base_addr, #28 ; shift 28 bytes
    ldmia base_addr!, {r2}      ; copy 4 bytes into registers
    add   base_addr , base_addr, #28 ; shift 28 bytes
    ldmia base_addr!, {r2}      ; copy 4 bytes into registers
    add   base_addr , base_addr, #28 ; shift 28 bytes
    ldmia base_addr!, {r2}      ; copy 4 bytes into registers
    add   base_addr , base_addr, #28 ; shift 28 bytes
    ldmia base_addr!, {r2}      ; copy 4 bytes into registers
    add   base_addr , base_addr, #28 ; shift 28 bytes
    ldmia base_addr!, {r2}      ; copy 4 bytes into registers
    add   base_addr , base_addr, #28 ; shift 28 bytes
    ldmia base_addr!, {r2}      ; copy 4 bytes into registers
    add   base_addr , base_addr, #28 ; shift 28 bytes
    ldmia base_addr!, {r2}      ; copy 4 bytes into registers
    add   base_addr , base_addr, #28 ; shift 28 bytes
    ldmia base_addr!, {r2}      ; copy 4 bytes into registers
    add   base_addr , base_addr, #28 ; shift 28 bytes
    ldmia base_addr!, {r2}      ; copy 4 bytes into registers
    add   base_addr , base_addr, #28 ; shift 28 bytes
    ldmia base_addr!, {r2}      ; copy 4 bytes into registers
    add   base_addr , base_addr, #28 ; shift 28 bytes
    ldmia base_addr!, {r2}      ; copy 4 bytes into registers
    add   base_addr , base_addr, #28 ; shift 28 bytes
    ldmia base_addr!, {r2}      ; copy 4 bytes into registers
    add   base_addr , base_addr, #28 ; shift 28 bytes
    ldmia base_addr!, {r2}      ; copy 4 bytes into registers
    add   base_addr , base_addr, #28 ; shift 28 bytes
    ldmia base_addr!, {r2}      ; copy 4 bytes into registers
    add   base_addr , base_addr, #28 ; shift 28 bytes
    ldmia base_addr!, {r2}      ; copy 4 bytes into registers
    add   base_addr , base_addr, #28 ; shift 28 bytes
    ldmia base_addr!, {r2}      ; copy 4 bytes into registers
    add   base_addr , base_addr, #28 ; shift 28 bytes
    ldmia base_addr!, {r2}      ; copy 4 bytes into registers
    add   base_addr , base_addr, #28 ; shift 28 bytes
    ldmia base_addr!, {r2}      ; copy 4 bytes into registers
    add   base_addr , base_addr, #28 ; shift 28 bytes
    ldmia base_addr!, {r2}      ; copy 4 bytes into registers
    add   base_addr , base_addr, #28 ; shift 28 bytes
    ldmia base_addr!, {r2}      ; copy 4 bytes into registers
    add   base_addr , base_addr, #28 ; shift 28 bytes
    ldmia base_addr!, {r2}      ; copy 4 bytes into registers
    add   base_addr , base_addr, #28 ; shift 28 bytes
    ldmia base_addr!, {r2}      ; copy 4 bytes into registers
    add   base_addr , base_addr, #28 ; shift 28 bytes
    ldmia base_addr!, {r2}      ; copy 4 bytes into registers
    add   base_addr , base_addr, #28 ; shift 28 bytes
    ldmia base_addr!, {r2}      ; copy 4 bytes into registers
    add   base_addr , base_addr, #28 ; shift 28 bytes
    ldmia base_addr!, {r2}      ; copy 4 bytes into registers
    add   base_addr , base_addr, #28 ; shift 28 bytes
    ldmia base_addr!, {r2}      ; copy 4 bytes into registers
    add   base_addr , base_addr, #28 ; shift 28 bytes
    ldmia base_addr!, {r2}      ; copy 4 bytes into registers
    add   base_addr , base_addr, #28 ; shift 28 bytes
    ldmia base_addr!, {r2}      ; copy 4 bytes into registers
    add   base_addr , base_addr, #28 ; shift 28 bytes
    ldmia base_addr!, {r2}      ; copy 4 bytes into registers
    add   base_addr , base_addr, #28 ; shift 28 bytes
    ldmia base_addr!, {r2}      ; copy 4 bytes into registers
    add   base_addr , base_addr, #28 ; shift 28 bytes
    ldmia base_addr!, {r2}      ; copy 4 bytes into registers
    add   base_addr , base_addr, #28 ; shift 28 bytes

    LDR   r2, =0x10308000
    CMP   base_addr, r2
    LDRPL base_addr, =0x10300004

    SUBS  loop_time, loop_time, #1  ; loop_time--- and set flags
    BNE   read_psram_n

    ;  return g_ptW5SysTimer->u32_StdaCounter
    LDR   r2, =0x34002C44
    LDR   r0, [r2]

    ; g_ptW5SysTimer->u32_StdaConfig = 0x0;
    LDR   r3, =0x0
    STR   r3, [r2, #-4]; *0x34002C40 = 0

    ldmfd   sp!, {r4-r11}
    bx      lr

    ENDFUNC


fms_test_write_psram_new   FUNCTION
    EXPORT  fms_test_write_psram_new

    stmfd   sp!, {r4-r11}

    ; write data to psram
    ; LDR     base_addr,  =0x10300004
    ; LDR     loop_time, =0x5746;
    MOV   r9, base_addr
    MOV   r10, base_addr
    ADD   base_addr, base_addr, #4
    ADD   r9, r9, #0x880
    ; g_ptW5SysTimer->u32_StdaConfig = 0x0;
    LDR   r2, =0x34002C40
    LDR   r3, =0x0
    STR   r3, [r2]; *0x34002C40 = 0
    ; g_ptW5SysTimer->u32_StdaConfig = 0x1;
    LDR   r3, =0x1
    STR   r3, [r2]; *0x34002C40 = 1

write_psram_n
    stmia base_addr!, {r2}      ; copy 4 bytes into registers
    add   base_addr , base_addr, #28 ; shift 28 bytes
    stmia base_addr!, {r2}      ; copy 4 bytes into registers
    add   base_addr , base_addr, #28 ; shift 28 bytes
    stmia base_addr!, {r2}      ; copy 4 bytes into registers
    add   base_addr , base_addr, #28 ; shift 28 bytes
    stmia base_addr!, {r2}      ; copy 4 bytes into registers
    add   base_addr , base_addr, #28 ; shift 28 bytes
    stmia base_addr!, {r2}      ; copy 4 bytes into registers
    add   base_addr , base_addr, #28 ; shift 28 bytes
    stmia base_addr!, {r2}      ; copy 4 bytes into registers
    add   base_addr , base_addr, #28 ; shift 28 bytes
    stmia base_addr!, {r2}      ; copy 4 bytes into registers
    add   base_addr , base_addr, #28 ; shift 28 bytes
    stmia base_addr!, {r2}      ; copy 4 bytes into registers
    add   base_addr , base_addr, #28 ; shift 28 bytes
    stmia base_addr!, {r2}      ; copy 4 bytes into registers
    add   base_addr , base_addr, #28 ; shift 28 bytes
    stmia base_addr!, {r2}      ; copy 4 bytes into registers
    add   base_addr , base_addr, #28 ; shift 28 bytes
    stmia base_addr!, {r2}      ; copy 4 bytes into registers
    add   base_addr , base_addr, #28 ; shift 28 bytes
    stmia base_addr!, {r2}      ; copy 4 bytes into registers
    add   base_addr , base_addr, #28 ; shift 28 bytes
    stmia base_addr!, {r2}      ; copy 4 bytes into registers
    add   base_addr , base_addr, #28 ; shift 28 bytes
    stmia base_addr!, {r2}      ; copy 4 bytes into registers
    add   base_addr , base_addr, #28 ; shift 28 bytes
    stmia base_addr!, {r2}      ; copy 4 bytes into registers
    add   base_addr , base_addr, #28 ; shift 28 bytes
    stmia base_addr!, {r2}      ; copy 4 bytes into registers
    add   base_addr , base_addr, #28 ; shift 28 bytes
    stmia base_addr!, {r2}      ; copy 4 bytes into registers
    add   base_addr , base_addr, #28 ; shift 28 bytes
    stmia base_addr!, {r2}      ; copy 4 bytes into registers
    add   base_addr , base_addr, #28 ; shift 28 bytes
    stmia base_addr!, {r2}      ; copy 4 bytes into registers
    add   base_addr , base_addr, #28 ; shift 28 bytes
    stmia base_addr!, {r2}      ; copy 4 bytes into registers
    add   base_addr , base_addr, #28 ; shift 28 bytes
    stmia base_addr!, {r2}      ; copy 4 bytes into registers
    add   base_addr , base_addr, #28 ; shift 28 bytes
    stmia base_addr!, {r2}      ; copy 4 bytes into registers
    add   base_addr , base_addr, #28 ; shift 28 bytes
    stmia base_addr!, {r2}      ; copy 4 bytes into registers
    add   base_addr , base_addr, #28 ; shift 28 bytes
    stmia base_addr!, {r2}      ; copy 4 bytes into registers
    add   base_addr , base_addr, #28 ; shift 28 bytes
    stmia base_addr!, {r2}      ; copy 4 bytes into registers
    add   base_addr , base_addr, #28 ; shift 28 bytes
    stmia base_addr!, {r2}      ; copy 4 bytes into registers
    add   base_addr , base_addr, #28 ; shift 28 bytes
    stmia base_addr!, {r2}      ; copy 4 bytes into registers
    add   base_addr , base_addr, #28 ; shift 28 bytes
    stmia base_addr!, {r2}      ; copy 4 bytes into registers
    add   base_addr , base_addr, #28 ; shift 28 bytes
    stmia base_addr!, {r2}      ; copy 4 bytes into registers
    add   base_addr , base_addr, #28 ; shift 28 bytes
    stmia base_addr!, {r2}      ; copy 4 bytes into registers
    add   base_addr , base_addr, #28 ; shift 28 bytes
    stmia base_addr!, {r2}      ; copy 4 bytes into registers
    add   base_addr , base_addr, #28 ; shift 28 bytes
    stmia base_addr!, {r2}      ; copy 4 bytes into registers
    add   base_addr , base_addr, #28 ; shift 28 bytes
    stmia base_addr!, {r2}      ; copy 4 bytes into registers
    add   base_addr , base_addr, #28 ; shift 28 bytes
    stmia base_addr!, {r2}      ; copy 4 bytes into registers
    add   base_addr , base_addr, #28 ; shift 28 bytes
    stmia base_addr!, {r2}      ; copy 4 bytes into registers
    add   base_addr , base_addr, #28 ; shift 28 bytes
    stmia base_addr!, {r2}      ; copy 4 bytes into registers
    add   base_addr , base_addr, #28 ; shift 28 bytes
    stmia base_addr!, {r2}      ; copy 4 bytes into registers
    add   base_addr , base_addr, #28 ; shift 28 bytes
    stmia base_addr!, {r2}      ; copy 4 bytes into registers
    add   base_addr , base_addr, #28 ; shift 28 bytes
    stmia base_addr!, {r2}      ; copy 4 bytes into registers
    add   base_addr , base_addr, #28 ; shift 28 bytes
    stmia base_addr!, {r2}      ; copy 4 bytes into registers
    add   base_addr , base_addr, #28 ; shift 28 bytes
    stmia base_addr!, {r2}      ; copy 4 bytes into registers
    add   base_addr , base_addr, #28 ; shift 28 bytes
    stmia base_addr!, {r2}      ; copy 4 bytes into registers
    add   base_addr , base_addr, #28 ; shift 28 bytes
    stmia base_addr!, {r2}      ; copy 4 bytes into registers
    add   base_addr , base_addr, #28 ; shift 28 bytes
    stmia base_addr!, {r2}      ; copy 4 bytes into registers
    add   base_addr , base_addr, #28 ; shift 28 bytes
    stmia base_addr!, {r2}      ; copy 4 bytes into registers
    add   base_addr , base_addr, #28 ; shift 28 bytes
    stmia base_addr!, {r2}      ; copy 4 bytes into registers
    add   base_addr , base_addr, #28 ; shift 28 bytes
    stmia base_addr!, {r2}      ; copy 4 bytes into registers
    add   base_addr , base_addr, #28 ; shift 28 bytes
    stmia base_addr!, {r2}      ; copy 4 bytes into registers
    add   base_addr , base_addr, #28 ; shift 28 bytes
    stmia base_addr!, {r2}      ; copy 4 bytes into registers
    add   base_addr , base_addr, #28 ; shift 28 bytes
    stmia base_addr!, {r2}      ; copy 4 bytes into registers
    add   base_addr , base_addr, #28 ; shift 28 bytes

    CMP   base_addr, r9
    MOVPL base_addr, r10

    SUBS  loop_time, loop_time, #1  ; loop_time--- and set flags
    BNE   write_psram_n

    ;  return g_ptW5SysTimer->u32_StdaCounter
    LDR   r2, =0x34002C44
    LDR   r0, [r2]

    ; g_ptW5SysTimer->u32_StdaConfig = 0x0;
    LDR   r3, =0x0
    STR   r3, [r2, #-4]; *0x34002C40 = 0

    ldmfd   sp!, {r4-r11}
    bx      lr

    ENDFUNC

fms_test_read_flash   FUNCTION
    EXPORT  fms_test_read_flash

    stmfd   sp!, {r4-r11}

    ; read data from flash
    LDR     base_addr,  =0x0C000000
    ; LDR     loop_time, =0x5746;

    ; g_ptW5SysTimer->u32_StdaConfig = 0x0;
    LDR   r2, =0x34002C40
    LDR   r3, =0x0
    STR   r3, [r2]; *0x34002C40 = 0
    ; g_ptW5SysTimer->u32_StdaConfig = 0x1;
    LDR   r3, =0x1
    STR   r3, [r2]; *0x34002C40 = 1

read_flash
    ldmia base_addr!, {r2-r12} ; copy 44 bytes into registers
    ldmia base_addr!, {r2-r12} ; copy 44 bytes into registers
    ldmia base_addr!, {r2-r12} ; copy 44 bytes into registers
    ldmia base_addr!, {r2-r12} ; copy 44 bytes into registers
    ldmia base_addr!, {r2-r12} ; copy 44 bytes into registers
    ldmia base_addr!, {r2-r12} ; copy 44 bytes into registers
    ldmia base_addr!, {r2-r12} ; copy 44 bytes into registers
    ldmia base_addr!, {r2-r12} ; copy 44 bytes into registers
    ldmia base_addr!, {r2-r12} ; copy 44 bytes into registers
    ldmia base_addr!, {r2-r12} ; copy 44 bytes into registers
    ldmia base_addr!, {r2-r12} ; copy 44 bytes into registers
    ldmia base_addr!, {r2-r12} ; copy 44 bytes into registers
    ldmia base_addr!, {r2-r12} ; copy 44 bytes into registers
    ldmia base_addr!, {r2-r12} ; copy 44 bytes into registers
    ldmia base_addr!, {r2-r12} ; copy 44 bytes into registers
    ldmia base_addr!, {r2-r12} ; copy 44 bytes into registers
    ldmia base_addr!, {r2-r12} ; copy 44 bytes into registers
    ldmia base_addr!, {r2-r12} ; copy 44 bytes into registers
    ldmia base_addr!, {r2-r12} ; copy 44 bytes into registers
    ldmia base_addr!, {r2-r12} ; copy 44 bytes into registers
    ldmia base_addr!, {r2-r12} ; copy 44 bytes into registers
    ldmia base_addr!, {r2-r12} ; copy 44 bytes into registers
    ldmia base_addr!, {r2-r12} ; copy 44 bytes into registers
    ldmia base_addr!, {r2-r12} ; copy 44 bytes into registers
    ldmia base_addr!, {r2-r12} ; copy 44 bytes into registers
    ldmia base_addr!, {r2-r12} ; copy 44 bytes into registers
    ldmia base_addr!, {r2-r12} ; copy 44 bytes into registers
    ldmia base_addr!, {r2-r12} ; copy 44 bytes into registers
    ldmia base_addr!, {r2-r12} ; copy 44 bytes into registers
    ldmia base_addr!, {r2-r12} ; copy 44 bytes into registers
    ldmia base_addr!, {r2-r12} ; copy 44 bytes into registers
    ldmia base_addr!, {r2-r12} ; copy 44 bytes into registers
    ldmia base_addr!, {r2-r12} ; copy 44 bytes into registers
    ldmia base_addr!, {r2-r12} ; copy 44 bytes into registers
    ldmia base_addr!, {r2-r12} ; copy 44 bytes into registers
    ldmia base_addr!, {r2-r12} ; copy 44 bytes into registers
    ldmia base_addr!, {r2-r12} ; copy 44 bytes into registers
    ldmia base_addr!, {r2-r12} ; copy 44 bytes into registers
    ldmia base_addr!, {r2-r12} ; copy 44 bytes into registers
    ldmia base_addr!, {r2-r12} ; copy 44 bytes into registers
    ldmia base_addr!, {r2-r12} ; copy 44 bytes into registers
    ldmia base_addr!, {r2-r12} ; copy 44 bytes into registers
    ldmia base_addr!, {r2-r12} ; copy 44 bytes into registers
    ldmia base_addr!, {r2-r12} ; copy 44 bytes into registers
    ldmia base_addr!, {r2-r12} ; copy 44 bytes into registers
    ldmia base_addr!, {r2-r12} ; copy 44 bytes into registers
    ldmia base_addr!, {r2-r12} ; copy 44 bytes into registers
    ldmia base_addr!, {r2-r12} ; copy 44 bytes into registers
    ldmia base_addr!, {r2-r12} ; copy 44 bytes into registers
    ldmia base_addr!, {r2-r12} ; copy 44 bytes into registers

    LDR   r2, =0x0CFFF000
    CMP   base_addr, r2
    LDRPL base_addr, =0x0C000000

    SUBS  loop_time, loop_time, #1  ; loop_time--- and set flags
    BNE   read_flash

    ;  return g_ptW5SysTimer->u32_StdaCounter
    LDR   r2, =0x34002C44
    LDR   r0, [r2]

    ; g_ptW5SysTimer->u32_StdaConfig = 0x0;
    LDR   r3, =0x0
    STR   r3, [r2, #-4]; *0x34002C40 = 0

    ldmfd   sp!, {r4-r11}
    bx      lr

    ENDFUNC

    LTORG
;
;
;
fms_test_read_psram   FUNCTION
    EXPORT  fms_test_read_psram

    stmfd   sp!, {r4-r11}

    ; read data from flash
    LDR     base_addr,  =0x10300000
    ; LDR     loop_time, =0x5746;

    ; g_ptW5SysTimer->u32_StdaConfig = 0x0;
    LDR   r2, =0x34002C40
    LDR   r3, =0x0
    STR   r3, [r2]; *0x34002C40 = 0
    ; g_ptW5SysTimer->u32_StdaConfig = 0x1;
    LDR   r3, =0x1
    STR   r3, [r2]; *0x34002C40 = 1

read_psram
    ldmia base_addr!, {r2-r12} ; copy 44 bytes into registers
    ldmia base_addr!, {r2-r12} ; copy 44 bytes into registers
    ldmia base_addr!, {r2-r12} ; copy 44 bytes into registers
    ldmia base_addr!, {r2-r12} ; copy 44 bytes into registers
    ldmia base_addr!, {r2-r12} ; copy 44 bytes into registers
    ldmia base_addr!, {r2-r12} ; copy 44 bytes into registers
    ldmia base_addr!, {r2-r12} ; copy 44 bytes into registers
    ldmia base_addr!, {r2-r12} ; copy 44 bytes into registers
    ldmia base_addr!, {r2-r12} ; copy 44 bytes into registers
    ldmia base_addr!, {r2-r12} ; copy 44 bytes into registers
    ldmia base_addr!, {r2-r12} ; copy 44 bytes into registers
    ldmia base_addr!, {r2-r12} ; copy 44 bytes into registers
    ldmia base_addr!, {r2-r12} ; copy 44 bytes into registers
    ldmia base_addr!, {r2-r12} ; copy 44 bytes into registers
    ldmia base_addr!, {r2-r12} ; copy 44 bytes into registers
    ldmia base_addr!, {r2-r12} ; copy 44 bytes into registers
    ldmia base_addr!, {r2-r12} ; copy 44 bytes into registers
    ldmia base_addr!, {r2-r12} ; copy 44 bytes into registers
    ldmia base_addr!, {r2-r12} ; copy 44 bytes into registers
    ldmia base_addr!, {r2-r12} ; copy 44 bytes into registers
    ldmia base_addr!, {r2-r12} ; copy 44 bytes into registers
    ldmia base_addr!, {r2-r12} ; copy 44 bytes into registers
    ldmia base_addr!, {r2-r12} ; copy 44 bytes into registers
    ldmia base_addr!, {r2-r12} ; copy 44 bytes into registers
    ldmia base_addr!, {r2-r12} ; copy 44 bytes into registers
    ldmia base_addr!, {r2-r12} ; copy 44 bytes into registers
    ldmia base_addr!, {r2-r12} ; copy 44 bytes into registers
    ldmia base_addr!, {r2-r12} ; copy 44 bytes into registers
    ldmia base_addr!, {r2-r12} ; copy 44 bytes into registers
    ldmia base_addr!, {r2-r12} ; copy 44 bytes into registers
    ldmia base_addr!, {r2-r12} ; copy 44 bytes into registers
    ldmia base_addr!, {r2-r12} ; copy 44 bytes into registers
    ldmia base_addr!, {r2-r12} ; copy 44 bytes into registers
    ldmia base_addr!, {r2-r12} ; copy 44 bytes into registers
    ldmia base_addr!, {r2-r12} ; copy 44 bytes into registers
    ldmia base_addr!, {r2-r12} ; copy 44 bytes into registers
    ldmia base_addr!, {r2-r12} ; copy 44 bytes into registers
    ldmia base_addr!, {r2-r12} ; copy 44 bytes into registers
    ldmia base_addr!, {r2-r12} ; copy 44 bytes into registers
    ldmia base_addr!, {r2-r12} ; copy 44 bytes into registers
    ldmia base_addr!, {r2-r12} ; copy 44 bytes into registers
    ldmia base_addr!, {r2-r12} ; copy 44 bytes into registers
    ldmia base_addr!, {r2-r12} ; copy 44 bytes into registers
    ldmia base_addr!, {r2-r12} ; copy 44 bytes into registers
    ldmia base_addr!, {r2-r12} ; copy 44 bytes into registers
    ldmia base_addr!, {r2-r12} ; copy 44 bytes into registers
    ldmia base_addr!, {r2-r12} ; copy 44 bytes into registers
    ldmia base_addr!, {r2-r12} ; copy 44 bytes into registers
    ldmia base_addr!, {r2-r12} ; copy 44 bytes into registers
    ldmia base_addr!, {r2-r12} ; copy 44 bytes into registers

    LDR   r2, =0x10308000
    CMP   base_addr, r2
    LDRPL base_addr, =0x10300000

    SUBS  loop_time, loop_time, #1  ; loop_time--- and set flags
    BNE   read_psram

    ;  return g_ptW5SysTimer->u32_StdaCounter
    LDR   r2, =0x34002C44
    LDR   r0, [r2]

    ; g_ptW5SysTimer->u32_StdaConfig = 0x0;
    LDR   r3, =0x0
    STR   r3, [r2, #-4]; *0x34002C40 = 0

    ldmfd   sp!, {r4-r11}
    bx      lr

    ENDFUNC


fms_test_write_psram   FUNCTION
    EXPORT  fms_test_write_psram

    stmfd   sp!, {r4-r11}

    ; write data to psram
    ; LDR     base_addr,  =0x10300000
    ; LDR     loop_time, =0x5746;
    MOV   r9, base_addr
    MOV   r10, base_addr
    ADD   r9, r9, #0x880

    ; g_ptW5SysTimer->u32_StdaConfig = 0x0;
    LDR   r2, =0x34002C40
    LDR   r3, =0x0
    STR   r3, [r2]; *0x34002C40 = 0
    ; g_ptW5SysTimer->u32_StdaConfig = 0x1;
    LDR   r3, =0x1
    STR   r3, [r2]; *0x34002C40 = 1

write_psram
    stmia base_addr!, {r2-r12} ; copy 44 bytes into registers
    stmia base_addr!, {r2-r12} ; copy 44 bytes into registers
    stmia base_addr!, {r2-r12} ; copy 44 bytes into registers
    stmia base_addr!, {r2-r12} ; copy 44 bytes into registers
    stmia base_addr!, {r2-r12} ; copy 44 bytes into registers
    stmia base_addr!, {r2-r12} ; copy 44 bytes into registers
    stmia base_addr!, {r2-r12} ; copy 44 bytes into registers
    stmia base_addr!, {r2-r12} ; copy 44 bytes into registers
    stmia base_addr!, {r2-r12} ; copy 44 bytes into registers
    stmia base_addr!, {r2-r12} ; copy 44 bytes into registers
    stmia base_addr!, {r2-r12} ; copy 44 bytes into registers
    stmia base_addr!, {r2-r12} ; copy 44 bytes into registers
    stmia base_addr!, {r2-r12} ; copy 44 bytes into registers
    stmia base_addr!, {r2-r12} ; copy 44 bytes into registers
    stmia base_addr!, {r2-r12} ; copy 44 bytes into registers
    stmia base_addr!, {r2-r12} ; copy 44 bytes into registers
    stmia base_addr!, {r2-r12} ; copy 44 bytes into registers
    stmia base_addr!, {r2-r12} ; copy 44 bytes into registers
    stmia base_addr!, {r2-r12} ; copy 44 bytes into registers
    stmia base_addr!, {r2-r12} ; copy 44 bytes into registers
    stmia base_addr!, {r2-r12} ; copy 44 bytes into registers
    stmia base_addr!, {r2-r12} ; copy 44 bytes into registers
    stmia base_addr!, {r2-r12} ; copy 44 bytes into registers
    stmia base_addr!, {r2-r12} ; copy 44 bytes into registers
    stmia base_addr!, {r2-r12} ; copy 44 bytes into registers
    stmia base_addr!, {r2-r12} ; copy 44 bytes into registers
    stmia base_addr!, {r2-r12} ; copy 44 bytes into registers
    stmia base_addr!, {r2-r12} ; copy 44 bytes into registers
    stmia base_addr!, {r2-r12} ; copy 44 bytes into registers
    stmia base_addr!, {r2-r12} ; copy 44 bytes into registers
    stmia base_addr!, {r2-r12} ; copy 44 bytes into registers
    stmia base_addr!, {r2-r12} ; copy 44 bytes into registers
    stmia base_addr!, {r2-r12} ; copy 44 bytes into registers
    stmia base_addr!, {r2-r12} ; copy 44 bytes into registers
    stmia base_addr!, {r2-r12} ; copy 44 bytes into registers
    stmia base_addr!, {r2-r12} ; copy 44 bytes into registers
    stmia base_addr!, {r2-r12} ; copy 44 bytes into registers
    stmia base_addr!, {r2-r12} ; copy 44 bytes into registers
    stmia base_addr!, {r2-r12} ; copy 44 bytes into registers
    stmia base_addr!, {r2-r12} ; copy 44 bytes into registers
    stmia base_addr!, {r2-r12} ; copy 44 bytes into registers
    stmia base_addr!, {r2-r12} ; copy 44 bytes into registers
    stmia base_addr!, {r2-r12} ; copy 44 bytes into registers
    stmia base_addr!, {r2-r12} ; copy 44 bytes into registers
    stmia base_addr!, {r2-r12} ; copy 44 bytes into registers
    stmia base_addr!, {r2-r12} ; copy 44 bytes into registers
    stmia base_addr!, {r2-r12} ; copy 44 bytes into registers
    stmia base_addr!, {r2-r12} ; copy 44 bytes into registers
    stmia base_addr!, {r2-r12} ; copy 44 bytes into registers
    stmia base_addr!, {r2-r12} ; copy 44 bytes into registers

    CMP   base_addr, r9
    MOVPL base_addr, r10

    SUBS  loop_time, loop_time, #1  ; loop_time--- and set flags
    BNE   write_psram

    ;  return g_ptW5SysTimer->u32_StdaCounter
    LDR   r2, =0x34002C44
    LDR   r0, [r2]

    ; g_ptW5SysTimer->u32_StdaConfig = 0x0;
    LDR   r3, =0x0
    STR   r3, [r2, #-4]; *0x34002C40 = 0

    ldmfd   sp!, {r4-r11}
    bx      lr

    ENDFUNC

fms_test_read_imi2   FUNCTION
    EXPORT  fms_test_read_imi2

    stmfd   sp!, {r4-r11}

    ; read data from flash
    LDR     base_addr,  =0x1C000004
    ; LDR     loop_time, =0x5746;

    ; g_ptW5SysTimer->u32_StdaConfig = 0x0;
    LDR   r2, =0x34002C40
    LDR   r3, =0x0
    STR   r3, [r2]; *0x34002C40 = 0
    ; g_ptW5SysTimer->u32_StdaConfig = 0x1;
    LDR   r3, =0x1
    STR   r3, [r2]; *0x34002C40 = 1

read_imi2
    ldmia base_addr!, {r2}      ; copy 4 bytes into registers
    add   base_addr , base_addr, #28 ; shift 28 bytes
    ldmia base_addr!, {r2}      ; copy 4 bytes into registers
    add   base_addr , base_addr, #28 ; shift 28 bytes
    ldmia base_addr!, {r2}      ; copy 4 bytes into registers
    add   base_addr , base_addr, #28 ; shift 28 bytes
    ldmia base_addr!, {r2}      ; copy 4 bytes into registers
    add   base_addr , base_addr, #28 ; shift 28 bytes
    ldmia base_addr!, {r2}      ; copy 4 bytes into registers
    add   base_addr , base_addr, #28 ; shift 28 bytes
    ldmia base_addr!, {r2}      ; copy 4 bytes into registers
    add   base_addr , base_addr, #28 ; shift 28 bytes
    ldmia base_addr!, {r2}      ; copy 4 bytes into registers
    add   base_addr , base_addr, #28 ; shift 28 bytes
    ldmia base_addr!, {r2}      ; copy 4 bytes into registers
    add   base_addr , base_addr, #28 ; shift 28 bytes
    ldmia base_addr!, {r2}      ; copy 4 bytes into registers
    add   base_addr , base_addr, #28 ; shift 28 bytes
    ldmia base_addr!, {r2}      ; copy 4 bytes into registers
    add   base_addr , base_addr, #28 ; shift 28 bytes
    ldmia base_addr!, {r2}      ; copy 4 bytes into registers
    add   base_addr , base_addr, #28 ; shift 28 bytes
    ldmia base_addr!, {r2}      ; copy 4 bytes into registers
    add   base_addr , base_addr, #28 ; shift 28 bytes
    ldmia base_addr!, {r2}      ; copy 4 bytes into registers
    add   base_addr , base_addr, #28 ; shift 28 bytes
    ldmia base_addr!, {r2}      ; copy 4 bytes into registers
    add   base_addr , base_addr, #28 ; shift 28 bytes
    ldmia base_addr!, {r2}      ; copy 4 bytes into registers
    add   base_addr , base_addr, #28 ; shift 28 bytes
    ldmia base_addr!, {r2}      ; copy 4 bytes into registers
    add   base_addr , base_addr, #28 ; shift 28 bytes
    ldmia base_addr!, {r2}      ; copy 4 bytes into registers
    add   base_addr , base_addr, #28 ; shift 28 bytes
    ldmia base_addr!, {r2}      ; copy 4 bytes into registers
    add   base_addr , base_addr, #28 ; shift 28 bytes
    ldmia base_addr!, {r2}      ; copy 4 bytes into registers
    add   base_addr , base_addr, #28 ; shift 28 bytes
    ldmia base_addr!, {r2}      ; copy 4 bytes into registers
    add   base_addr , base_addr, #28 ; shift 28 bytes
    ldmia base_addr!, {r2}      ; copy 4 bytes into registers
    add   base_addr , base_addr, #28 ; shift 28 bytes
    ldmia base_addr!, {r2}      ; copy 4 bytes into registers
    add   base_addr , base_addr, #28 ; shift 28 bytes
    ldmia base_addr!, {r2}      ; copy 4 bytes into registers
    add   base_addr , base_addr, #28 ; shift 28 bytes
    ldmia base_addr!, {r2}      ; copy 4 bytes into registers
    add   base_addr , base_addr, #28 ; shift 28 bytes
    ldmia base_addr!, {r2}      ; copy 4 bytes into registers
    add   base_addr , base_addr, #28 ; shift 28 bytes
    ldmia base_addr!, {r2}      ; copy 4 bytes into registers
    add   base_addr , base_addr, #28 ; shift 28 bytes
    ldmia base_addr!, {r2}      ; copy 4 bytes into registers
    add   base_addr , base_addr, #28 ; shift 28 bytes
    ldmia base_addr!, {r2}      ; copy 4 bytes into registers
    add   base_addr , base_addr, #28 ; shift 28 bytes
    ldmia base_addr!, {r2}      ; copy 4 bytes into registers
    add   base_addr , base_addr, #28 ; shift 28 bytes
    ldmia base_addr!, {r2}      ; copy 4 bytes into registers
    add   base_addr , base_addr, #28 ; shift 28 bytes
    ldmia base_addr!, {r2}      ; copy 4 bytes into registers
    add   base_addr , base_addr, #28 ; shift 28 bytes
    ldmia base_addr!, {r2}      ; copy 4 bytes into registers
    add   base_addr , base_addr, #28 ; shift 28 bytes
    ldmia base_addr!, {r2}      ; copy 4 bytes into registers
    add   base_addr , base_addr, #28 ; shift 28 bytes
    ldmia base_addr!, {r2}      ; copy 4 bytes into registers
    add   base_addr , base_addr, #28 ; shift 28 bytes
    ldmia base_addr!, {r2}      ; copy 4 bytes into registers
    add   base_addr , base_addr, #28 ; shift 28 bytes
    ldmia base_addr!, {r2}      ; copy 4 bytes into registers
    add   base_addr , base_addr, #28 ; shift 28 bytes
    ldmia base_addr!, {r2}      ; copy 4 bytes into registers
    add   base_addr , base_addr, #28 ; shift 28 bytes
    ldmia base_addr!, {r2}      ; copy 4 bytes into registers
    add   base_addr , base_addr, #28 ; shift 28 bytes
    ldmia base_addr!, {r2}      ; copy 4 bytes into registers
    add   base_addr , base_addr, #28 ; shift 28 bytes
    ldmia base_addr!, {r2}      ; copy 4 bytes into registers
    add   base_addr , base_addr, #28 ; shift 28 bytes
    ldmia base_addr!, {r2}      ; copy 4 bytes into registers
    add   base_addr , base_addr, #28 ; shift 28 bytes
    ldmia base_addr!, {r2}      ; copy 4 bytes into registers
    add   base_addr , base_addr, #28 ; shift 28 bytes
    ldmia base_addr!, {r2}      ; copy 4 bytes into registers
    add   base_addr , base_addr, #28 ; shift 28 bytes
    ldmia base_addr!, {r2}      ; copy 4 bytes into registers
    add   base_addr , base_addr, #28 ; shift 28 bytes
    ldmia base_addr!, {r2}      ; copy 4 bytes into registers
    add   base_addr , base_addr, #28 ; shift 28 bytes
    ldmia base_addr!, {r2}      ; copy 4 bytes into registers
    add   base_addr , base_addr, #28 ; shift 28 bytes
    ldmia base_addr!, {r2}      ; copy 4 bytes into registers
    add   base_addr , base_addr, #28 ; shift 28 bytes
    ldmia base_addr!, {r2}      ; copy 4 bytes into registers
    add   base_addr , base_addr, #28 ; shift 28 bytes
    ldmia base_addr!, {r2}      ; copy 4 bytes into registers
    add   base_addr , base_addr, #28 ; shift 28 bytes
    ldmia base_addr!, {r2}      ; copy 4 bytes into registers
    add   base_addr , base_addr, #28 ; shift 28 bytes


    LDR   r2, =0x1C040000
    CMP   base_addr, r2
    LDRPL base_addr, =0x1C000004

    SUBS  loop_time, loop_time, #1  ; loop_time--- and set flags
    BNE   read_imi2

    ;  return g_ptW5SysTimer->u32_StdaCounter
    LDR   r2, =0x34002C44
    LDR   r0, [r2]

    ; g_ptW5SysTimer->u32_StdaConfig = 0x0;
    LDR   r3, =0x0
    STR   r3, [r2, #-4]; *0x34002C40 = 0

    ldmfd   sp!, {r4-r11}
    bx      lr

    ENDFUNC

fms_test_write_imi2   FUNCTION
    EXPORT  fms_test_write_imi2

    stmfd   sp!, {r4-r11}

    ; write data to psram
    LDR     base_addr,  =0x1C000004
    ; LDR     loop_time, =0x5746;

    ; g_ptW5SysTimer->u32_StdaConfig = 0x0;
    LDR   r2, =0x34002C40
    LDR   r3, =0x0
    STR   r3, [r2]; *0x34002C40 = 0
    ; g_ptW5SysTimer->u32_StdaConfig = 0x1;
    LDR   r3, =0x1
    STR   r3, [r2]; *0x34002C40 = 1

write_imi2
    stmia base_addr!, {r2}      ; copy 4 bytes into registers
    add   base_addr , base_addr, #28 ; shift 28 bytes
    stmia base_addr!, {r2}      ; copy 4 bytes into registers
    add   base_addr , base_addr, #28 ; shift 28 bytes
    stmia base_addr!, {r2}      ; copy 4 bytes into registers
    add   base_addr , base_addr, #28 ; shift 28 bytes
    stmia base_addr!, {r2}      ; copy 4 bytes into registers
    add   base_addr , base_addr, #28 ; shift 28 bytes
    stmia base_addr!, {r2}      ; copy 4 bytes into registers
    add   base_addr , base_addr, #28 ; shift 28 bytes
    stmia base_addr!, {r2}      ; copy 4 bytes into registers
    add   base_addr , base_addr, #28 ; shift 28 bytes
    stmia base_addr!, {r2}      ; copy 4 bytes into registers
    add   base_addr , base_addr, #28 ; shift 28 bytes
    stmia base_addr!, {r2}      ; copy 4 bytes into registers
    add   base_addr , base_addr, #28 ; shift 28 bytes
    stmia base_addr!, {r2}      ; copy 4 bytes into registers
    add   base_addr , base_addr, #28 ; shift 28 bytes
    stmia base_addr!, {r2}      ; copy 4 bytes into registers
    add   base_addr , base_addr, #28 ; shift 28 bytes
    stmia base_addr!, {r2}      ; copy 4 bytes into registers
    add   base_addr , base_addr, #28 ; shift 28 bytes
    stmia base_addr!, {r2}      ; copy 4 bytes into registers
    add   base_addr , base_addr, #28 ; shift 28 bytes
    stmia base_addr!, {r2}      ; copy 4 bytes into registers
    add   base_addr , base_addr, #28 ; shift 28 bytes
    stmia base_addr!, {r2}      ; copy 4 bytes into registers
    add   base_addr , base_addr, #28 ; shift 28 bytes
    stmia base_addr!, {r2}      ; copy 4 bytes into registers
    add   base_addr , base_addr, #28 ; shift 28 bytes
    stmia base_addr!, {r2}      ; copy 4 bytes into registers
    add   base_addr , base_addr, #28 ; shift 28 bytes
    stmia base_addr!, {r2}      ; copy 4 bytes into registers
    add   base_addr , base_addr, #28 ; shift 28 bytes
    stmia base_addr!, {r2}      ; copy 4 bytes into registers
    add   base_addr , base_addr, #28 ; shift 28 bytes
    stmia base_addr!, {r2}      ; copy 4 bytes into registers
    add   base_addr , base_addr, #28 ; shift 28 bytes
    stmia base_addr!, {r2}      ; copy 4 bytes into registers
    add   base_addr , base_addr, #28 ; shift 28 bytes
    stmia base_addr!, {r2}      ; copy 4 bytes into registers
    add   base_addr , base_addr, #28 ; shift 28 bytes
    stmia base_addr!, {r2}      ; copy 4 bytes into registers
    add   base_addr , base_addr, #28 ; shift 28 bytes
    stmia base_addr!, {r2}      ; copy 4 bytes into registers
    add   base_addr , base_addr, #28 ; shift 28 bytes
    stmia base_addr!, {r2}      ; copy 4 bytes into registers
    add   base_addr , base_addr, #28 ; shift 28 bytes
    stmia base_addr!, {r2}      ; copy 4 bytes into registers
    add   base_addr , base_addr, #28 ; shift 28 bytes
    stmia base_addr!, {r2}      ; copy 4 bytes into registers
    add   base_addr , base_addr, #28 ; shift 28 bytes
    stmia base_addr!, {r2}      ; copy 4 bytes into registers
    add   base_addr , base_addr, #28 ; shift 28 bytes
    stmia base_addr!, {r2}      ; copy 4 bytes into registers
    add   base_addr , base_addr, #28 ; shift 28 bytes
    stmia base_addr!, {r2}      ; copy 4 bytes into registers
    add   base_addr , base_addr, #28 ; shift 28 bytes
    stmia base_addr!, {r2}      ; copy 4 bytes into registers
    add   base_addr , base_addr, #28 ; shift 28 bytes
    stmia base_addr!, {r2}      ; copy 4 bytes into registers
    add   base_addr , base_addr, #28 ; shift 28 bytes
    stmia base_addr!, {r2}      ; copy 4 bytes into registers
    add   base_addr , base_addr, #28 ; shift 28 bytes
    stmia base_addr!, {r2}      ; copy 4 bytes into registers
    add   base_addr , base_addr, #28 ; shift 28 bytes
    stmia base_addr!, {r2}      ; copy 4 bytes into registers
    add   base_addr , base_addr, #28 ; shift 28 bytes
    stmia base_addr!, {r2}      ; copy 4 bytes into registers
    add   base_addr , base_addr, #28 ; shift 28 bytes
    stmia base_addr!, {r2}      ; copy 4 bytes into registers
    add   base_addr , base_addr, #28 ; shift 28 bytes
    stmia base_addr!, {r2}      ; copy 4 bytes into registers
    add   base_addr , base_addr, #28 ; shift 28 bytes
    stmia base_addr!, {r2}      ; copy 4 bytes into registers
    add   base_addr , base_addr, #28 ; shift 28 bytes
    stmia base_addr!, {r2}      ; copy 4 bytes into registers
    add   base_addr , base_addr, #28 ; shift 28 bytes
    stmia base_addr!, {r2}      ; copy 4 bytes into registers
    add   base_addr , base_addr, #28 ; shift 28 bytes
    stmia base_addr!, {r2}      ; copy 4 bytes into registers
    add   base_addr , base_addr, #28 ; shift 28 bytes
    stmia base_addr!, {r2}      ; copy 4 bytes into registers
    add   base_addr , base_addr, #28 ; shift 28 bytes
    stmia base_addr!, {r2}      ; copy 4 bytes into registers
    add   base_addr , base_addr, #28 ; shift 28 bytes
    stmia base_addr!, {r2}      ; copy 4 bytes into registers
    add   base_addr , base_addr, #28 ; shift 28 bytes
    stmia base_addr!, {r2}      ; copy 4 bytes into registers
    add   base_addr , base_addr, #28 ; shift 28 bytes
    stmia base_addr!, {r2}      ; copy 4 bytes into registers
    add   base_addr , base_addr, #28 ; shift 28 bytes
    stmia base_addr!, {r2}      ; copy 4 bytes into registers
    add   base_addr , base_addr, #28 ; shift 28 bytes
    stmia base_addr!, {r2}      ; copy 4 bytes into registers
    add   base_addr , base_addr, #28 ; shift 28 bytes
    stmia base_addr!, {r2}      ; copy 4 bytes into registers
    add   base_addr , base_addr, #28 ; shift 28 bytes
    stmia base_addr!, {r2}      ; copy 4 bytes into registers
    add   base_addr , base_addr, #28 ; shift 28 bytes
    

    LDR   r2, =0x1C040000
    CMP   base_addr, r2
    LDRPL base_addr, =0x1C000004

    SUBS  loop_time, loop_time, #1  ; loop_time--- and set flags
    BNE   write_imi2

    ;  return g_ptW5SysTimer->u32_StdaCounter
    LDR   r2, =0x34002C44
    LDR   r0, [r2]

    ; g_ptW5SysTimer->u32_StdaConfig = 0x0;
    LDR   r3, =0x0
    STR   r3, [r2, #-4]; *0x34002C40 = 0

    ldmfd   sp!, {r4-r11}
    bx      lr

    ENDFUNC

fms_test_read_imi1   FUNCTION
    EXPORT  fms_test_read_imi1

    stmfd   sp!, {r4-r11}

    ; write data to psram
    LDR     base_addr,  =0x08000004
    ; LDR     loop_time, =0x5746;

    ; g_ptW5SysTimer->u32_StdaConfig = 0x0;
    LDR   r2, =0x34002C40
    LDR   r3, =0x0
    STR   r3, [r2]; *0x34002C40 = 0
    ; g_ptW5SysTimer->u32_StdaConfig = 0x1;
    LDR   r3, =0x1
    STR   r3, [r2]; *0x34002C40 = 1

read_imi1
    ldmia base_addr!, {r2}      ; copy 4 bytes into registers
    add   base_addr , base_addr, #28 ; shift 28 bytes
    ldmia base_addr!, {r2}      ; copy 4 bytes into registers
    add   base_addr , base_addr, #28 ; shift 28 bytes
    ldmia base_addr!, {r2}      ; copy 4 bytes into registers
    add   base_addr , base_addr, #28 ; shift 28 bytes
    ldmia base_addr!, {r2}      ; copy 4 bytes into registers
    add   base_addr , base_addr, #28 ; shift 28 bytes
    ldmia base_addr!, {r2}      ; copy 4 bytes into registers
    add   base_addr , base_addr, #28 ; shift 28 bytes
    ldmia base_addr!, {r2}      ; copy 4 bytes into registers
    add   base_addr , base_addr, #28 ; shift 28 bytes
    ldmia base_addr!, {r2}      ; copy 4 bytes into registers
    add   base_addr , base_addr, #28 ; shift 28 bytes
    ldmia base_addr!, {r2}      ; copy 4 bytes into registers
    add   base_addr , base_addr, #28 ; shift 28 bytes
    ldmia base_addr!, {r2}      ; copy 4 bytes into registers
    add   base_addr , base_addr, #28 ; shift 28 bytes
    ldmia base_addr!, {r2}      ; copy 4 bytes into registers
    add   base_addr , base_addr, #28 ; shift 28 bytes
    ldmia base_addr!, {r2}      ; copy 4 bytes into registers
    add   base_addr , base_addr, #28 ; shift 28 bytes
    ldmia base_addr!, {r2}      ; copy 4 bytes into registers
    add   base_addr , base_addr, #28 ; shift 28 bytes
    ldmia base_addr!, {r2}      ; copy 4 bytes into registers
    add   base_addr , base_addr, #28 ; shift 28 bytes
    ldmia base_addr!, {r2}      ; copy 4 bytes into registers
    add   base_addr , base_addr, #28 ; shift 28 bytes
    ldmia base_addr!, {r2}      ; copy 4 bytes into registers
    add   base_addr , base_addr, #28 ; shift 28 bytes
    ldmia base_addr!, {r2}      ; copy 4 bytes into registers
    add   base_addr , base_addr, #28 ; shift 28 bytes
    ldmia base_addr!, {r2}      ; copy 4 bytes into registers
    add   base_addr , base_addr, #28 ; shift 28 bytes
    ldmia base_addr!, {r2}      ; copy 4 bytes into registers
    add   base_addr , base_addr, #28 ; shift 28 bytes
    ldmia base_addr!, {r2}      ; copy 4 bytes into registers
    add   base_addr , base_addr, #28 ; shift 28 bytes
    ldmia base_addr!, {r2}      ; copy 4 bytes into registers
    add   base_addr , base_addr, #28 ; shift 28 bytes
    ldmia base_addr!, {r2}      ; copy 4 bytes into registers
    add   base_addr , base_addr, #28 ; shift 28 bytes
    ldmia base_addr!, {r2}      ; copy 4 bytes into registers
    add   base_addr , base_addr, #28 ; shift 28 bytes
    ldmia base_addr!, {r2}      ; copy 4 bytes into registers
    add   base_addr , base_addr, #28 ; shift 28 bytes
    ldmia base_addr!, {r2}      ; copy 4 bytes into registers
    add   base_addr , base_addr, #28 ; shift 28 bytes
    ldmia base_addr!, {r2}      ; copy 4 bytes into registers
    add   base_addr , base_addr, #28 ; shift 28 bytes
    ldmia base_addr!, {r2}      ; copy 4 bytes into registers
    add   base_addr , base_addr, #28 ; shift 28 bytes
    ldmia base_addr!, {r2}      ; copy 4 bytes into registers
    add   base_addr , base_addr, #28 ; shift 28 bytes
    ldmia base_addr!, {r2}      ; copy 4 bytes into registers
    add   base_addr , base_addr, #28 ; shift 28 bytes
    ldmia base_addr!, {r2}      ; copy 4 bytes into registers
    add   base_addr , base_addr, #28 ; shift 28 bytes
    ldmia base_addr!, {r2}      ; copy 4 bytes into registers
    add   base_addr , base_addr, #28 ; shift 28 bytes
    ldmia base_addr!, {r2}      ; copy 4 bytes into registers
    add   base_addr , base_addr, #28 ; shift 28 bytes
    ldmia base_addr!, {r2}      ; copy 4 bytes into registers
    add   base_addr , base_addr, #28 ; shift 28 bytes
    ldmia base_addr!, {r2}      ; copy 4 bytes into registers
    add   base_addr , base_addr, #28 ; shift 28 bytes
    ldmia base_addr!, {r2}      ; copy 4 bytes into registers
    add   base_addr , base_addr, #28 ; shift 28 bytes
    ldmia base_addr!, {r2}      ; copy 4 bytes into registers
    add   base_addr , base_addr, #28 ; shift 28 bytes
    ldmia base_addr!, {r2}      ; copy 4 bytes into registers
    add   base_addr , base_addr, #28 ; shift 28 bytes
    ldmia base_addr!, {r2}      ; copy 4 bytes into registers
    add   base_addr , base_addr, #28 ; shift 28 bytes
    ldmia base_addr!, {r2}      ; copy 4 bytes into registers
    add   base_addr , base_addr, #28 ; shift 28 bytes
    ldmia base_addr!, {r2}      ; copy 4 bytes into registers
    add   base_addr , base_addr, #28 ; shift 28 bytes
    ldmia base_addr!, {r2}      ; copy 4 bytes into registers
    add   base_addr , base_addr, #28 ; shift 28 bytes
    ldmia base_addr!, {r2}      ; copy 4 bytes into registers
    add   base_addr , base_addr, #28 ; shift 28 bytes
    ldmia base_addr!, {r2}      ; copy 4 bytes into registers
    add   base_addr , base_addr, #28 ; shift 28 bytes
    ldmia base_addr!, {r2}      ; copy 4 bytes into registers
    add   base_addr , base_addr, #28 ; shift 28 bytes
    ldmia base_addr!, {r2}      ; copy 4 bytes into registers
    add   base_addr , base_addr, #28 ; shift 28 bytes
    ldmia base_addr!, {r2}      ; copy 4 bytes into registers
    add   base_addr , base_addr, #28 ; shift 28 bytes
    ldmia base_addr!, {r2}      ; copy 4 bytes into registers
    add   base_addr , base_addr, #28 ; shift 28 bytes
    ldmia base_addr!, {r2}      ; copy 4 bytes into registers
    add   base_addr , base_addr, #28 ; shift 28 bytes
    ldmia base_addr!, {r2}      ; copy 4 bytes into registers
    add   base_addr , base_addr, #28 ; shift 28 bytes
    ldmia base_addr!, {r2}      ; copy 4 bytes into registers
    add   base_addr , base_addr, #28 ; shift 28 bytes
    ldmia base_addr!, {r2}      ; copy 4 bytes into registers
    add   base_addr , base_addr, #28 ; shift 28 bytes

    LDR   r2, =0x08008000
    CMP   base_addr, r2
    LDRPL base_addr, =0x08000004

    SUBS  loop_time, loop_time, #1  ; loop_time--- and set flags
    BNE   read_imi1

    ;  return g_ptW5SysTimer->u32_StdaCounter
    LDR   r2, =0x34002C44
    LDR   r0, [r2]

    ; g_ptW5SysTimer->u32_StdaConfig = 0x0;
    LDR   r3, =0x0
    STR   r3, [r2, #-4]; *0x34002C40 = 0

    ldmfd   sp!, {r4-r11}
    bx      lr

    ENDFUNC

fms_test_write_imi1   FUNCTION
    EXPORT  fms_test_write_imi1

    stmfd   sp!, {r4-r11}

    ; write data to psram
    ; LDR     base_addr,  =0x08000000
    ; LDR     loop_time, =0x5746;

    MOV	  r9, base_addr
    MOV	  r10, base_addr
    ADD   r9, r9, #0x0640
    ADD   base_addr, base_addr, #4
    ; g_ptW5SysTimer->u32_StdaConfig = 0x0;
    LDR   r2, =0x34002C40
    LDR   r3, =0x0
    STR   r3, [r2]; *0x34002C40 = 0
    ; g_ptW5SysTimer->u32_StdaConfig = 0x1;
    LDR   r3, =0x1
    STR   r3, [r2]; *0x34002C40 = 1

write_imi1
    stmia base_addr!, {r2}      ; copy 4 bytes into registers
    add   base_addr , base_addr, #28 ; shift 28 bytes
    stmia base_addr!, {r2}      ; copy 4 bytes into registers
    add   base_addr , base_addr, #28 ; shift 28 bytes
    stmia base_addr!, {r2}      ; copy 4 bytes into registers
    add   base_addr , base_addr, #28 ; shift 28 bytes
    stmia base_addr!, {r2}      ; copy 4 bytes into registers
    add   base_addr , base_addr, #28 ; shift 28 bytes
    stmia base_addr!, {r2}      ; copy 4 bytes into registers
    add   base_addr , base_addr, #28 ; shift 28 bytes
    stmia base_addr!, {r2}      ; copy 4 bytes into registers
    add   base_addr , base_addr, #28 ; shift 28 bytes
    stmia base_addr!, {r2}      ; copy 4 bytes into registers
    add   base_addr , base_addr, #28 ; shift 28 bytes
    stmia base_addr!, {r2}      ; copy 4 bytes into registers
    add   base_addr , base_addr, #28 ; shift 28 bytes
    stmia base_addr!, {r2}      ; copy 4 bytes into registers
    add   base_addr , base_addr, #28 ; shift 28 bytes
    stmia base_addr!, {r2}      ; copy 4 bytes into registers
    add   base_addr , base_addr, #28 ; shift 28 bytes
    stmia base_addr!, {r2}      ; copy 4 bytes into registers
    add   base_addr , base_addr, #28 ; shift 28 bytes
    stmia base_addr!, {r2}      ; copy 4 bytes into registers
    add   base_addr , base_addr, #28 ; shift 28 bytes
    stmia base_addr!, {r2}      ; copy 4 bytes into registers
    add   base_addr , base_addr, #28 ; shift 28 bytes
    stmia base_addr!, {r2}      ; copy 4 bytes into registers
    add   base_addr , base_addr, #28 ; shift 28 bytes
    stmia base_addr!, {r2}      ; copy 4 bytes into registers
    add   base_addr , base_addr, #28 ; shift 28 bytes
    stmia base_addr!, {r2}      ; copy 4 bytes into registers
    add   base_addr , base_addr, #28 ; shift 28 bytes
    stmia base_addr!, {r2}      ; copy 4 bytes into registers
    add   base_addr , base_addr, #28 ; shift 28 bytes
    stmia base_addr!, {r2}      ; copy 4 bytes into registers
    add   base_addr , base_addr, #28 ; shift 28 bytes
    stmia base_addr!, {r2}      ; copy 4 bytes into registers
    add   base_addr , base_addr, #28 ; shift 28 bytes
    stmia base_addr!, {r2}      ; copy 4 bytes into registers
    add   base_addr , base_addr, #28 ; shift 28 bytes
    stmia base_addr!, {r2}      ; copy 4 bytes into registers
    add   base_addr , base_addr, #28 ; shift 28 bytes
    stmia base_addr!, {r2}      ; copy 4 bytes into registers
    add   base_addr , base_addr, #28 ; shift 28 bytes
    stmia base_addr!, {r2}      ; copy 4 bytes into registers
    add   base_addr , base_addr, #28 ; shift 28 bytes
    stmia base_addr!, {r2}      ; copy 4 bytes into registers
    add   base_addr , base_addr, #28 ; shift 28 bytes
    stmia base_addr!, {r2}      ; copy 4 bytes into registers
    add   base_addr , base_addr, #28 ; shift 28 bytes
    stmia base_addr!, {r2}      ; copy 4 bytes into registers
    add   base_addr , base_addr, #28 ; shift 28 bytes
    stmia base_addr!, {r2}      ; copy 4 bytes into registers
    add   base_addr , base_addr, #28 ; shift 28 bytes
    stmia base_addr!, {r2}      ; copy 4 bytes into registers
    add   base_addr , base_addr, #28 ; shift 28 bytes
    stmia base_addr!, {r2}      ; copy 4 bytes into registers
    add   base_addr , base_addr, #28 ; shift 28 bytes
    stmia base_addr!, {r2}      ; copy 4 bytes into registers
    add   base_addr , base_addr, #28 ; shift 28 bytes
    stmia base_addr!, {r2}      ; copy 4 bytes into registers
    add   base_addr , base_addr, #28 ; shift 28 bytes
    stmia base_addr!, {r2}      ; copy 4 bytes into registers
    add   base_addr , base_addr, #28 ; shift 28 bytes
    stmia base_addr!, {r2}      ; copy 4 bytes into registers
    add   base_addr , base_addr, #28 ; shift 28 bytes
    stmia base_addr!, {r2}      ; copy 4 bytes into registers
    add   base_addr , base_addr, #28 ; shift 28 bytes
    stmia base_addr!, {r2}      ; copy 4 bytes into registers
    add   base_addr , base_addr, #28 ; shift 28 bytes
    stmia base_addr!, {r2}      ; copy 4 bytes into registers
    add   base_addr , base_addr, #28 ; shift 28 bytes
    stmia base_addr!, {r2}      ; copy 4 bytes into registers
    add   base_addr , base_addr, #28 ; shift 28 bytes
    stmia base_addr!, {r2}      ; copy 4 bytes into registers
    add   base_addr , base_addr, #28 ; shift 28 bytes
    stmia base_addr!, {r2}      ; copy 4 bytes into registers
    add   base_addr , base_addr, #28 ; shift 28 bytes
    stmia base_addr!, {r2}      ; copy 4 bytes into registers
    add   base_addr , base_addr, #28 ; shift 28 bytes
    stmia base_addr!, {r2}      ; copy 4 bytes into registers
    add   base_addr , base_addr, #28 ; shift 28 bytes
    stmia base_addr!, {r2}      ; copy 4 bytes into registers
    add   base_addr , base_addr, #28 ; shift 28 bytes
    stmia base_addr!, {r2}      ; copy 4 bytes into registers
    add   base_addr , base_addr, #28 ; shift 28 bytes
    stmia base_addr!, {r2}      ; copy 4 bytes into registers
    add   base_addr , base_addr, #28 ; shift 28 bytes
    stmia base_addr!, {r2}      ; copy 4 bytes into registers
    add   base_addr , base_addr, #28 ; shift 28 bytes
    stmia base_addr!, {r2}      ; copy 4 bytes into registers
    add   base_addr , base_addr, #28 ; shift 28 bytes
    stmia base_addr!, {r2}      ; copy 4 bytes into registers
    add   base_addr , base_addr, #28 ; shift 28 bytes
    stmia base_addr!, {r2}      ; copy 4 bytes into registers
    add   base_addr , base_addr, #28 ; shift 28 bytes
    stmia base_addr!, {r2}      ; copy 4 bytes into registers
    add   base_addr , base_addr, #28 ; shift 28 bytes
    stmia base_addr!, {r2}      ; copy 4 bytes into registers
    add   base_addr , base_addr, #28 ; shift 28 bytes

    CMP   base_addr, r9
    MOVPL base_addr, r10

    SUBS  loop_time, loop_time, #1  ; loop_time--- and set flags
    BNE   write_imi1

    ;  return g_ptW5SysTimer->u32_StdaCounter
    LDR   r2, =0x34002C44
    LDR   r0, [r2]

    ; g_ptW5SysTimer->u32_StdaConfig = 0x0;
    LDR   r3, =0x0
    STR   r3, [r2, #-4]; *0x34002C40 = 0

    ldmfd   sp!, {r4-r11}
    bx      lr

    ENDFUNC

    END

