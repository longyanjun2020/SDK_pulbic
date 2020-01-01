		.text

		.globl	Decoder_add
		.globl	Decoder_sub

		.globl	Decoder_mult

		.globl	Decoder_round

		.globl	Decoder_L_msu
		.globl	Decoder_L_negate

		.globl	Decoder_L_shl
		.globl	Decoder_abs_s
		.globl	Decoder_div_s

		.globl	Decoder_L_abs
		.globl	Decoder_L_mac
		.globl	Decoder_norm_l
		.globl	Decoder_norm_s

		.globl	Decoder_Mpy_32_16

		.globl	Decoder_negate	//2006-02-22, modify for fail to replace by asm code for MR795 mode.


		.globl	Decoder_L_add

//-------------------------------------------------------------------
//		EXPORT	L_mult	//2006-02-17, fail to replace by asm code.
//		EXPORT	shl	//2006-02-17, MAYBE fail to replace by asm code.
//		EXPORT	shr	//2006-02-20, MAYBE fail to replace by asm code.

//=============================================================================
//|                                                                           |
//|   Function Name : Word16 mult (Word16 var1, Word16 var2)                  |
//|                                                                           |
//|   Purpose :                                                               |
//|                                                                           |
//|    Performs the multiplication of var1 by var2 and gives a 16 bit result  |
//|    which is scaled i.e.:                                                  |
//|             mult(var1,var2) = extract_l(L_shr((var1 times var2),15)) and  |
//|             mult(-32768,-32768) = 32767.                                  |
//=============================================================================
Decoder_mult:
        SMULBB  r0,r0,r1
        MOV     r0,r0,ASR #15
        BX		lr


//=============================================================================
//|                                                                           |
//|   Function Name : Word32 L_msu (Word32 L_var3, Word16 var1, Word16 var2)  |
//|                                                                           |
//|   Purpose :                                                               |
//|                                                                           |
//|   Multiply var1 by var2 and shift the result left by 1. Subtract the 32   |
//|   bit result to L_var3 with saturation, return a 32 bit result:           |
//|        L_msu(L_var3,var1,var2) = L_sub(L_var3,L_mult(var1,var2)).         |
//=============================================================================
Decoder_L_msu:
        SMULBB  r1,r1,r2
        QDSUB   r0,r0,r1
        BX		lr


//=============================================================================
//|                                                                           |
//|   Function Name : Word16 round (Word32 L_var1)                            |
//|                                                                           |
//|   Purpose :                                                               |
//|                                                                           |
//|   Round the lower 16 bits of the 32 bit input number into the MS 16 bits  |
//|   with saturation. Shift the resulting bits right by 16 and return the 16 |
//|   bit number:                                                             |
//|               round(L_var1) = extract_h(L_add(L_var1,32768))              |
//=============================================================================
Decoder_round:
        STMFD   r13!, {r1,lr}
        MOV     r1,#0x8000
        QADD    r0,r0,r1
        MOV     r0,r0,ASR #16
        LDMFD   r13!, {r1,lr}
        BX		lr


//=============================================================================
//|                                                                           |
//|   Function Name : Word16 add (Word16 var1, Word16 var2)                   |
//|                                                                           |
//|   Purpose :                                                               |
//|                                                                           |
//|    Performs the addition (var1+var2) with overflow control and saturation//|
//|    the 16 bit result is set at +32767 when overflow occurs or at -32768   |
//|    when underflow occurs.                                                 |
//=============================================================================
Decoder_add:
        MOV     r0,r0,LSL #16
        MOV     r1,r1,LSL #16
        QADD    r0,r0,r1
        MOV     r0,r0,ASR #16
        BX		lr


//=============================================================================
//|                                                                           |
//|   Function Name : Word16 sub (Word16 var1, Word16 var2)                   |
//|                                                                           |
//|   Purpose :                                                               |
//|                                                                           |
//|    Performs the subtraction (var1-var2) with overflow control and satu-   |
//|    ration// the 16 bit result is set at +32767 when overflow occurs or at  |
//|    -32768 when underflow occurs.                                          |
//=============================================================================
Decoder_sub:
        MOV     r0,r0,LSL #16
        MOV     r1,r1,LSL #16
        QSUB    r0,r0,r1
        MOV     r0,r0,ASR #16
        BX		lr


//=============================================================================
//|                                                                           |
//|   Function Name : Word32 L_negate (Word32 L_var1)                         |
//|                                                                           |
//|   Purpose :                                                               |
//|                                                                           |
//|   Negate the 32 bit variable L_var1 with saturation// saturate in the case |
//|   where input is -2147483648 (0x8000 0000).                               |
//=============================================================================
Decoder_L_negate:
        STMFD   r13!, {r1-r2,lr}
        MOV     r2,#0x7fffffff
        CMP     r0,#0x80000000
        BEQ     Decoder_L_negate_end
        MOV     r1,#0
        SUB     r2,r1,r0
Decoder_L_negate_end:
        MOV     r0,r2
        LDMFD   r13!, {r1-r2,lr}
        BX		lr



//=============================================================================
//|                                                                           |
//|   Function Name : L_shl                                                   |
//|                                                                           |
//|   Purpose :                                                               |
//|                                                                           |
//|   Arithmetically shift the 32 bit input L_var1 left var2 positions. Zero  |
//|   fill the var2 LSB of the result. If var2 is negative, arithmetically    |
//|   shift L_var1 right by -var2 with sign extension. Saturate the result in |
//|   case of underflows or overflows.                                        |
//|                                                                           |
//=============================================================================
//    if (shift <= 0)
//        return x >> (-shift)//
//    absx = (x < 0 ? -x : x)//
//    __asm {
//        clz lz, absx//
//    }
//    if (shift < lz || x == 0)
//        return x << shift//
//    if (x < 0)
//        return ARMDSP_WORD32_MIN//
//    else
//        return ARMDSP_WORD32_MAX//

Decoder_L_shl:
        STMFD   r13!, {r2-r4,lr}
        CMP     r1,#0
        RSBLE   r1,r1,#0
        MOVLE   r0,r0,ASR r1
//        BLE     Decoder_L_shl_end
        LDMLEFD r13!, {r2-r4,lr}
        BXLE    lr
        CMP     r0,#0
        RSBLT   r2,r0,#0
        MOVGE   r2,r0

        CLZ     r3,r2
        CMP     r1,r3
        MOVLT   r4,r0,LSL r1
//        BLT     Decoder_L_shl_end
        MOVLT   r0,r4
        LDMLTFD r13!, {r2-r4,lr}        
        BXLT    lr

        CMP     r0,#0
        MOVLT   r4,#0x80000000     
        MVNGE   r4,#0x80000000   

Decoder_L_shl_end:
        MOV     r0,r4
        LDMFD   r13!, {r2-r4,lr}
        BX      lr


//=============================================================================
//|                                                                           |
//|   Function Name : Word16 abs_s (Word16 var1)                              |
//|                                                                           |
//|   Purpose :                                                               |
//|                                                                           |
//|    Absolute value of var1// abs_s(-32768) = 32767.                         |
//|                                                                           |
//=============================================================================
Decoder_abs_s:
        STMFD   r13!, {r1-r2,lr}

        MOV     r1,#0x7f00
        ADD     r1,r1,#0x00ff
        MOV     r2,#0
        CMP     r0,#0xffff8000
        MOVEQ   r0,r1
        BEQ     Decoder_abs_s_end
        CMP     r0,#0
        SUBLT   r0,r2,r0
Decoder_abs_s_end:
        LDMFD   r13!, {r1-r2,lr}
        BX      lr


//=============================================================================
//|                                                                           |
//|   Function Name : Word16 Decoder_div_s (Word16 var1, Word16 var2)                 |
//|                                                                           |
//|   Purpose :                                                               |
//|                                                                           |
//|   Produces a result which is the fractional integer division of var1  by  |
//|   var2// var1 and var2 must be positive and var2 must be greater or equal  |
//|   to var1// the result is positive (leading bit equal to 0) and truncated  |
//|   to 16 bits.                                                             |
//|   If var1 = var2 then div(var1,var2) = 32767.                             |
//=============================================================================
Decoder_div_s:
        STMFD   r13!, {r2-r5,lr}
        MOV     r2,#15
        CMP     r0,#0
        BEQ     Decoder_div_s_end
        CMP     r0,r1
        BEQ     Decoder_div_s_end1

        MOV     r3,#0
Decoder_div_s_loop:
        MOV     r3,r3,LSL #1
        MOV     r0,r0,LSL #1
        CMP     r0,r1
        BLT     Decoder_div_s_chk
        SUB     r0,r0,r1
        ADD     r3,r3,#1
Decoder_div_s_chk:
        SUBS    r2,r2,#1
        BNE     Decoder_div_s_loop
        MOV     r0,r3
        LDMFD   r13!, {r2-r5,lr}
        BX      lr        

Decoder_div_s_end1:
        MOV     r0,#0x7f00
        ADD     r0,r0,#0x00ff
Decoder_div_s_end:
        LDMFD   r13!, {r2-r5,lr}
        BX      lr        




//=============================================================================
//|                                                                           |
//|   Function Name : Word32 L_abs (Word32 L_var1)                            |
//|                                                                           |
//|   Purpose :                                                               |
//|                                                                           |
//|    Absolute value of L_var1// Saturate in case where the input is          |
//|                                                               -214783648  |
//=============================================================================
Decoder_L_abs:
        STMFD   r13!, {r1-r2,lr}
        MOV     r2,#0x7fffffff
        CMP     r0,#0x80000000
        BEQ     Decoder_L_abs_end
        MOV     r1,#0
        CMP     r0,#0
        SUBLT   r0,r1,r0
        LDMFD   r13!, {r1-r2,lr}
        BX      lr        

Decoder_L_abs_end:
        MOV     r0,r2
        LDMFD   r13!, {r1-r2,lr}
        BX      lr


//=============================================================================
//|                                                                           |
//|   Function Name :  Word32 L_mac (Word32 L_var3, Word16 var1, Word16 var2) |
//|                                                                           |
//|   Purpose :                                                               |
//|                                                                           |
//|   Multiply var1 by var2 and shift the result left by 1. Add the 32 bit    |
//|   result to L_var3 with saturation, return a 32 bit result:               |
//|        L_mac(L_var3,var1,var2) = L_add(L_var3,L_mult(var1,var2)).         |
//=============================================================================
Decoder_L_mac:
        SMULBB  r1,r1,r2
        QDADD   r0,r0,r1
//        MOV     pc,lr
        BX      lr


//=============================================================================
//|                                                                           |
//|   Function Name : Word16 norm_l (Word32 L_var1)                           |
//|                                                                           |
//|   Purpose :                                                               |
//|                                                                           |
//|   Produces the number of left shifts needed to normalize the 32 bit varia-|
//|   ble L_var1 for positive values on the interval with minimum of          |
//|   1073741824 and maximum of 2147483647, and for negative values on the in-|
//|   terval with minimum of -2147483648 and maximum of -1073741824// in order |
//|   to normalize the result, the following operation must be done :         |
//|                   norm_L_var1 = L_shl(L_var1,norm_l(L_var1)).             |
//=============================================================================
Decoder_norm_l:
        STMFD   r13!, {r1-r2,lr}
        MOV     r1,#0
        CMP     r0,#0
        BEQ     Decoder_norm_l_end
        MOV     r1,#31
        CMP     r0,#0xffffffff
        BEQ     Decoder_norm_l_end
        CMP     r0,#0
        BGT     Decoder_norm_l_pos
        MOV     r2,#0
        SUB     r0,r2,r0
Decoder_norm_l_pos:
        CLZ     r0,r0
        SUB     r0,r0,#1
        LDMFD   r13!, {r1-r2,lr}
        BX      lr        

Decoder_norm_l_end:
        MOV     r0,r1
        LDMFD   r13!, {r1-r2,lr}
        BX      lr        


//=============================================================================
//|                                                                           |
//|   Function Name : Word16 norm_s (Word16 L_var1)                           |
//|                                                                           |
//|   Purpose :                                                               |
//|                                                                           |
//|   Produces the number of left shift needed to normalize the 16 bit varia- |
//|   ble var1 for positive values on the interval with minimum of 16384 and  |
//|   maximum of 32767, and for negative values on the interval with minimum  |
//|   of -32768 and maximum of -16384// in order to normalize the result, the  |
//|   following operation must be done :                                      |
//|                    norm_var1 = shl(var1,norm_s(var1)).                    |
//=============================================================================
Decoder_norm_s:
        STMFD   r13!, {r1-r3,lr}
        MOV     r1,#0
        CMP     r0,#0
        BEQ     Decoder_norm_s_end
        MOV     r1,#15
        SUBS    r3,r0,#0x00ff
        SUBS    r3,r3,#0xff00
        BEQ     Decoder_norm_s_end
        CMP     r0,#0
        BGT     Decoder_norm_s_pos
        MOV     r2,#0
        SUB     r0,r2,r0
Decoder_norm_s_pos:
        CLZ     r0,r0
        SUB     r0,r0,#17
        LDMFD   r13!, {r1-r3,lr}
        BX      lr        

Decoder_norm_s_end:
        MOV     r0,r1
        LDMFD   r13!, {r1-r3,lr}
        BX      lr



//=============================================================================
//* Function Word32 Mpy_32_16 (Word16 hi, Word16 lo, Word16 n)                *
//*                                                                           *
//*   Multiply a 16 bit integer by a 32 bit (DPF). The result is divided      *
//*   by 2**15                                                                *
//*                                                                           *
//*                                                                           *
//*   L_32 = (hi1*lo2)<<1 + ((lo1*lo2)>>15)<<1                                *
//*                                                                           *
//* Arguments:                                                                *
//*                                                                           *
//*  hi          hi part of 32 bit number.                                    *
//*  lo          lo part of 32 bit number.                                    *
//*  n           16 bit number.                                               *
//*                                                                           *
//=============================================================================
Decoder_Mpy_32_16:
        SMULBB  r0,r0,r2                    //
        MOV     r0,r0,LSL #1                // (C)L_32 = L_mult (hi, n)//

        SMULBB  r1,r1,r2
        MOV     r1,r1,ASR #15               // r6=mult(lo,n)
        QDADD   r0,r0,r1                    // (C)L_32 = L_mac (L_32, mult (lo, n), 1)//

//        MOV     pc,lr
        BX      lr


//=============================================================================
//|                                                                           |
//|   Function Name : Word16 negate (Word16 var1)                             |
//|                                                                           |
//|   Purpose :                                                               |
//|                                                                           |
//|   Negate var1 with saturation, saturate in the case where input is -32768:|
//|                negate(var1) = sub(0,var1).                                |
//=============================================================================
Decoder_negate:
        STMFD   r13!, {r1-r2,lr}

        MOV     r2,#0x7f00
        ADD     r2,r2,#0x00ff
//        CMP     r0,#0x8000
        CMP     r0,#0xffff8000
        BEQ     Decoder_negate_end
        MOV     r1,#0
        SUB     r2,r1,r0
Decoder_negate_end:
        MOV     r0,r2
        LDMFD   r13!, {r1-r2,lr}
        BX      lr



//=============================================================================
//|                                                                           |
//|   Function Name : Word32 L_add (Word32 L_var1, Word32 L_var2)             |
//|                                                                           |
//=============================================================================
Decoder_L_add:
		QADD	r0,r0,r1
        BX		lr


    	.end
