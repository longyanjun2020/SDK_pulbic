		.text

        	
        	//#include     "dec_AMR_RAM.i"		

		.global	Decoder_Inv_sqrt

		.global	Decoder_Copy
		.global	Decoder_Set_zero

		.global	Decoder_Pred_lt_3or6
		.global	Decoder_Weight_Ai

		.global	Decoder_Lsf_lsp
		.global	Decoder_Lsp_lsf

		.global	Decoder_L_Comp

		.extern	Decoder_norm_l

ArgStack:        .space   16
VarStack:        .space   60
AzTemp:          .space   20

TempBuffer:      .space   480


/*        AREA    table,CODE,READONLY
;
;****************************************************************************
;
;      File             : AMR_TAB.s
;      Purpose          : Speech codec table
;                       :  (encoder, decoder, and postfilter)
;
;****************************************************************************

;
;==============================================================================
; Coefficient table for pre-process filter
;==============================================================================
*/
a_b:   .hword 4096, 7807, -3733
      .hword 1899, -3798, 1899

/*
;==============================================================================
;  Table of lag_window for autocorrelation.
;
;  noise floor = 1.0001   = (0.9999  on r[1] ..r[10])
;  Bandwitdh expansion = 60 Hz
;
;
;  lag_wind[0] =  1.00000000    (not stored)
;  lag_wind[1] =  0.99879038
;  lag_wind[2] =  0.99546897
;  lag_wind[3] =  0.98995781
;  lag_wind[4] =  0.98229337
;  lag_wind[5] =  0.97252619
;  lag_wind[6] =  0.96072036
;  lag_wind[7] =  0.94695264
;  lag_wind[8] =  0.93131179
;  lag_wind[9] =  0.91389757
;  lag_wind[10]=  0.89481968
;==============================================================================
*/

lag_h_l:     .hword 11904, 32728, 17280, 32619, 30720, 32438, 25856, 32187, 24192, 31867, \
                28992, 31480, 24384, 31029,  7360, 30517, 19520, 29946, 14784, 29321



grid:        .hword 32760, 32723, 32588, 32364, 32051, 31651, \
                31164, 30591, 29935, 29196, 28377, 27481, \
                26509, 25465, 24351, 23170, 21926, 20621, \
                19260, 17846, 16384, 14876, 13327, 11743, \
                10125, 8480, 6812, 5126, 3425, 1714, \
                0, -1714, -3425, -5126, -6812, -8480, \
                -10125, -11743, -13327, -14876, -16384, -17846, \
                -19260, -20621, -21926, -23170, -24351, -25465, \
                -26509, -27481, -28377, -29196, -29935, -30591, \
                -31164, -31651, -32051, -32364, -32588, -32723, \
                -32760


table1:      .hword 32767, 32729, 32610, 32413, 32138, 31786, 31357, 30853
            .hword 30274, 29622, 28899, 28106, 27246, 26320, 25330, 24279
            .hword 23170, 22006, 20788, 19520, 18205, 16846, 15447, 14010
            .hword 12540, 11039, 9512, 7962, 6393, 4808, 3212, 1608
            .hword 0, -1608, -3212, -4808, -6393, -7962, -9512, -11039
            .hword -12540, -14010, -15447, -16846, -18205, -19520, -20788, -22006
            .hword -23170, -24279, -25330, -26320, -27246, -28106, -28899, -29622
            .hword -30274, -30853, -31357, -31786, -32138, -32413, -32610, -32729
            .hword -32768


slope_tmp:       .hword -26887, -8812, -5323, -3813, -2979, -2444, -2081, -1811
            .hword -1608, -1450, -1322, -1219, -1132, -1059, -998, -946
            .hword -901, -861, -827, -797, -772, -750, -730, -713
            .hword -699, -687, -677, -668, -662, -657, -654, -652
            .hword -652, -654, -657, -662, -668, -677, -687, -699
            .hword -713, -730, -750, -772, -797, -827, -861, -901
            .hword -946, -998, -1059, -1132, -1219, -1322, -1450, -1608
            .hword -1811, -2081, -2444, -2979, -3813, -5323, -8812, -26887






invsqrt_tab: .hword 32767, 31790, 30894, 30070, 29309, 28602, 27945, 27330, 26755, 26214
            .hword 25705, 25225, 24770, 24339, 23930, 23541, 23170, 22817, 22479, 22155
            .hword 21845, 21548, 21263, 20988, 20724, 20470, 20225, 19988, 19760, 19539
            .hword 19326, 19119, 18919, 18725, 18536, 18354, 18176, 18004, 17837, 17674
            .hword 17515, 17361, 17211, 17064, 16921, 16782, 16646, 16514, 16384


inter_6_tab: 
            .hword 29443, 28346, 25207, 20449, 14701, 8693, 3143
            .hword -1352, -4402, -5865, -5850, -4673, -2783
            .hword -672, 1211, 2536, 3130, 2991, 2259
            .hword 1170, 0, -1001, -1652, -1868, -1666
            .hword -1147, -464, 218, 756, 1060, 1099
            .hword 904, 550, 135, -245, -514, -634
            .hword -602, -451, -231, 0, 191, 308
            .hword 340, 296, 198, 78, -36, -120
            .hword -163, -165, -132, -79, -19, 34
            .hword 73, 91, 89, 70, 38, 0


inter_6:
            .hword 29519
            .hword 28316, 24906, 19838, 13896, 7945, 2755
            .hword -1127, -3459, -4304, -3969, -2899, -1561
            .hword -336, 534, 970, 1023, 823, 516
            .hword 220, 0, -131, -194, -215, 0
            
//==============================================================================
// ShiftAz
//==============================================================================
ShiftAz:
        LDR     r5,=AzTemp
        ADD     r6,r0,#2
        MOV     r7,#10
ShiftAz_loop:
        LDRH    r8,[r6],#2
        SUBS    r7,r7,#1        
        STRH    r8,[r5],#2

        BNE     ShiftAz_loop

        LDR     r0,=AzTemp
        MOV     pc,lr







//=============================================================================
//Word32 Decoder_Inv_sqrt (       /* (o) : output value   */
//    Word32 L_x          /* (i) : input value    */
//)
//=============================================================================
Decoder_Inv_sqrt:
        STMFD   r13!, {r1-r7,lr}

        CMP     r0,#0                       // if (L_x <= (Word32) 0)
        BLE     Decoder_Inv_sqrt_end1               // return ((Word32) 0x3fffffffL)//

//        CLZ     r1,r0
//        SUB     r1,r1,#1                    // r1 = exp = norm_l (L_x)//

		MOV		r2,r0
		BL 		Decoder_norm_l				// r1 = exp = norm_l (L_x)//
		MOV		r1,r0
		
        MOV     r0,r2,LSL r1                // L_x = (L_x<<exp)//     /* L_x is normalize */

        RSB     r1,r1,#30                   // exp = sub (30, exp)//

        ANDS    r2,r1,#1                    // if ((exp & 1) == 0) {
        MOVEQ   r0,r0,ASR #1                // L_x = L_x/2// }

        MOV     r1,r1,ASR #1                // exp = (exp >> 1)//
        MOV     r0,r0,ASR #9                // L_x = L_x >> 9//        
        ADD     r1,r1,#1                    // r1 = exp += 1//

        MOV     r2,r0,ASR #16               // r2 = i = extract_h (L_x)//        /* Extract b25-b31 */
        MOV     r0,r0,ASR #1                // L_x = L_x/2//

        MOV     r3,r0,LSL #16
        MVN     r4,#0x8000
        MOV     r3,r3,ASR #16               // r3 = a = extract_l (L_x)//

//        MOV     r4,#0x7f00
//        ADD     r4,r4,#0x00ff
        SUB     r2,r2,#16                   // i = sub (i, 16)//
        AND     r3,r3,r4                    // a = a & (Word16) 0x7fff//

        LDR     r4,=invsqrt_tab
        MOV     r2,r2,LSL #1        
        ADD     r4,r4,r2
        LDRSH   r5,[r4],#2                  // r5 = table[i]
        MOV     r7,r5,LSL #16               // r7 = L_y = L_deposit_h (table[i])//
        LDRSH   r6,[r4]                     // r6 = table[i+1]

        SUB     r5,r5,r6                    // r5 = tmp = sub (table[i], table[i + 1])//

        SMULBB  r6,r3,r5
        QDSUB   r7,r7,r6                    // L_y = L_msu (L_y, tmp, a)//  /* L_y -=  tmp*a*2         */

        MOV     r0,r7,ASR r1                // L_y = L_y >> exp//

        LDMFD   r13!, {r1-r7,lr}
        BX      lr

Decoder_Inv_sqrt_end1:

        MOV     r0,#0x3fffffff
        LDMFD   r13!, {r1-r7,lr}
        BX      lr






        .ltorg   //LTORG


//==============================================================================
//void Decoder_Copy (
//    const Word16 x[],   /* i : input vector (L)  */
//    Word16 y[],         /* o : output vector (L) */
//    Word16 L            /* i : vector length     */
//)
//{
//    Word16 i//
//
//    for (i = 0; i < L; i++)
//    {
//        y[i] = x[i];
//    }
//
//    return;
//}
//==============================================================================
Decoder_Copy:
        STMFD    r13!, {r3}
Decoder_Copy_loop:
        LDRH    r3,[r0],#2
        SUBS    r2,r2,#1        
        STRH    r3,[r1],#2
        BNE     Decoder_Copy_loop
        LDMFD   r13!, {r3}
        BX      lr


//==============================================================================
//void Decoder_Set_zero (
//    Word16 x[],         /* (o)    : vector to clear     */
//    Word16 L            /* (i)    : length of vector    */
//)
//{
//    Word16 i;
//
//    for (i = 0; i < L; i++)
//    {
//        x[i] = 0;
//    }
//
//    return;
//}
//==============================================================================
Decoder_Set_zero:
        STMFD    r13!, {r2,lr}
        MOV      r2,#0
Decoder_Set_zero_loop:
        STRH    r2,[r0],#2
        SUBS    r1,r1,#1
        BNE     Decoder_Set_zero_loop
        LDMFD   r13!, {r2,lr}
        BX      lr



//==============================================================================
//void Decoder_Pred_lt_3or6 (
//    Word16 exc[],     /* in/out: excitation buffer                         */
//    Word16 T0,        /* input : integer pitch lag                         */
//    Word16 frac,      /* input : fraction of lag                           */
//    Word16 flag3      /* input : if set, upsampling rate = 3 (6 otherwise) */
//)
//==============================================================================
Decoder_Pred_lt_3or6:
        STMFD   r13!, {r4-r12,lr}

        SUB     r4,r0,r1,LSL #1             // r4 = x0 = &exc[-T0];
        RSB     r2,r2,#0                    // r2 = frac = -frac
        CMP     r3,#0                       // if (flag3 != 0)
        MOVNE   r2,r2,LSL #1                //  frac = frac << 1;
        CMP     r2,#0                       // if (frac < 0) {
        ADDLT   r2,r2,#6                    //  frac = frac + UP_SAMP_MAX;
        SUBLT   r4,r4,#1                    //  r4 = x0--; }
        
        MOV     r3,#0x8000
        MOV     r5,#40                      // r5 = index j
Decoder_Pred_lt_3or6_loop_j:                         // for (j = 0// j < 40// j++) {
        MOV     r6,r4                       // r6 = x1 = x0++;
        ADD     r4,r4,#2                
        MOV     r10,#0                      // r10 = s = 0;        
        MOV     r7,r4                       // r7 = x2 = x0;
        
        LDR     r9,=inter_6_tab
        RSB     r1,r2,#6        
        ADD     r8,r9,r2,LSL #1             // r8 = c1 = &inter_6[frac];              
        ADD     r9,r9,r1,LSL #1             // r9 = c2 = &inter_6[UP_SAMP_MAX - frac];

        MOV     r1,#10                      // r1 = index i
Decoder_Pred_lt_3or6_loop_i:                         // for (i = 0, k = 0; i < L_INTER10; i++, k += UP_SAMP_MAX) 
        LDRSH   r11,[r6],#-1*2              // {
        LDRSH   r12,[r8],#6*2
        SMLABB  r10,r11,r12,r10             // s = L_mac (s, x1[-i], c1[k]);
        LDRSH   r11,[r7],#1*2
        LDRSH   r12,[r9],#6*2        
        SMLABB  r10,r11,r12,r10             // s = L_mac (s, x2[i], c2[k]);

        LDRSH   r11,[r6],#-1*2
        LDRSH   r12,[r8],#6*2
        SMLABB  r10,r11,r12,r10             // s = L_mac (s, x1[-i], c1[k]);
        LDRSH   r11,[r7],#1*2
        LDRSH   r12,[r9],#6*2        
        SMLABB  r10,r11,r12,r10             // s = L_mac (s, x1[-i], c1[k]);
        
        SUBS    r1,r1,#2
        BNE     Decoder_Pred_lt_3or6_loop_i         // }   
        
        MOV     r10,r10,LSL #1
        QADD    r10,r10,r3
        MOV     r10,r10,ASR #16
        STRH    r10,[r0],#2                 // exc[j] = round (s);              
        
        SUBS    r5,r5,#1
        BNE     Decoder_Pred_lt_3or6_loop_j         // }

        LDMFD   r13!, {r4-r12,lr}
        BX      lr



//==============================================================================
//void Decoder_Weight_Ai (
//    Word16 a[],         /* (i)     : a[M+1]  LPC coefficients   (M=10)    */
//    const Word16 fac[], /* (i)     : Spectral expansion factors.          */
//    Word16 a_exp[]      /* (o)     : Spectral expanded LPC coefficients   */
//)
//==============================================================================
Decoder_Weight_Ai:
        STMFD   r13!, {r3-r12,lr}

        MOV     r7,#10

        LDRH    r3,[r0],#2
        MOV     r8,#0x8000        
        STRH    r3,[r2],#2                  // a_exp[0] = a[0];
Decoder_Weight_Ai_loop:                      //     for (i = 1; i <= M; i++) {
        LDRSH   r3,[r0],#2                  // r3 = a[i]
        LDRSH   r4,[r1],#2                  // r4 = fac[i-1]
        LDRSH   r9,[r0],#2                  // r9 = a[i]
        SMULBB  r5,r3,r4
        LDRSH   r10,[r1],#2                 // r10 = fac[i-1]                
        QDADD   r5,r8,r5
        SMULBB  r12,r9,r10        
        MOV     r5,r5,ASR #16
        QDADD   r12,r8,r12        
        STRH    r5,[r2],#2                  // a_exp[i] = round (L_mult (a[i], fac[i - 1]));

        MOV     r12,r12,ASR #16
        SUBS    r7,r7,#2        
        STRH    r12,[r2],#2                  // a_exp[i] = round (L_mult (a[i], fac[i - 1]));

        BNE     Decoder_Weight_Ai_loop       // }

        LDMFD   r13!, {r3-r12,lr}
        BX      lr


//==============================================================================
//void Decoder_Lsf_lsp (
//    Word16 lsf[],       /* (i) : lsf[m] normalized (range: 0.0<=val<=0.5) */
//    Word16 lsp[],       /* (o) : lsp[m] (range: -1<=val<1)                */
//    Word16 m            /* (i) : LPC order                                */
//==============================================================================
Decoder_Lsf_lsp:
        STMFD   r13!, {r3-r8}

        LDR     r6,=table1                  // r6 = table[]
Decoder_Lsf_lsp_loop:                        // for (i = 0; i < m; i++)
        LDRH    r3,[r0],#2                  //  {
        MOV     r5,#0x00ff        
        MOV     r4,r3,ASR #8                // ind = lsf[i] >> 8;
        AND     r3,r3,r5                    // offset = lsf[i] & 0x00ff;

        ADD     r8,r6,r4,LSL #1
        LDRSH   r5,[r8],#2
        LDRSH   r7,[r8]
        SUB     r7,r7,r5                    // L_tmp = table[ind + 1] - table[ind] ;

        SMULBB  r7,r7,r3
        MOV     r7,r7,ASR #8                // L_tmp *= (((Word32) offset)<<1);
        SUBS    r2,r2,#1        
        ADD     r7,r7,r5
        STRH    r7,[r1],#2                  // lsp[i] = table[ind] + (Word16) (L_tmp >> 9);

        BNE     Decoder_Lsf_lsp_loop

        LDMFD   r13!, {r3-r8}
        BX      lr


//==============================================================================
//void Decoder_Lsp_lsf (
//    Word16 lsp[],       /* (i)  : lsp[m] (range: -1<=val<1)                */
//    Word16 lsf[],       /* (o)  : lsf[m] normalized (range: 0.0<=val<=0.5) */
//    Word16 m            /* (i)  : LPC order                                */
//==============================================================================
Decoder_Lsp_lsf:
        STMFD   r13!, {r3-r12,lr}
        MOV     r4,#126                     // r4 = ind = 63
        
        LDR     r6,=table1                  // r6 = table[]
        SUB     r7,r2,#1
        LDR     r9,=slope_tmp                   // r9 = slope[]        
        ADD     r0,r0,r7,LSL #1             // r0 = pointer of lsp[]
        MOV     r10,#0x8000        
        ADD     r1,r1,r7,LSL #1
Decoder_Lsp_lsf_loop:
        LDRSH   r5,[r0],#-2                 // r5 = lsp[i]
compare_loop:
        LDRSH   r3,[r6,r4]                  // r3 = table[ind]
        CMP     r3,r5
//        BGE     Decoder_Lsp_lsf_1
        SUBLT   r4,r4,#2
        BLT     compare_loop
Decoder_Lsp_lsf_1:
        SUB     r7,r5,r3                    // r7 = L_tmp = (Word32) (lsp[i] - table[ind]);
        LDR     r8,[r9,r4]
        SMULBB  r7,r7,r8
        MOV     r7,r7,LSL #4                // L_tmp *= (((Word32) slope[ind])<<1)//  L_tmp <<= 3;
        MOV     r8,r4,ASR #1
        ADD     r7,r7,r10                    // L_tmp += (Word32) 0x00008000L;
        MOV     r7,r7,ASR #16               // lsf[i] = (Word16) (L_tmp>>16);
        SUBS    r2,r2,#1
        ADD     r7,r7,r8,LSL #8
        STRH    r7,[r1],#-2                 // lsf[i] = lsf[i] + (ind << 8);

        BNE     Decoder_Lsp_lsf_loop

        LDMFD   r13!, {r3-r12,lr}
        BX      lr



//=============================================================================
//*                                                                           *
//*  Function Word32 Decoder_L_Comp (Word16 hi, Word16 lo)                            *
//*                                                                           *
//*  Compose from two 16 bit DPF a 32 bit integer.                            *
//*                                                                           *
//*     L_32 = hi<<16 + lo<<1                                                 *
//*                                                                           *
//*  Arguments:                                                               *
//*                                                                           *
//*   hi        msb                                                           *
//*   lo        lsf (with sign)                                               *
//*                                                                           *
//*   Return Value :                                                          *
//*                                                                           *
//*             32 bit long signed integer (Word32) whose value falls in the  *
//*             range : 0x8000 0000 <= L_32 <= 0x7fff fff0.                   *
//*                                                                           *
//=============================================================================
Decoder_L_Comp:
        MOV     r0,r0,LSL #16               // (C)L_32 = L_deposit_h (hi);
        MOV     r1,r1,LSL #1
        QADD    r0,r0,r1                    // (C) return(L_mac (L_32, lo, 1))

        BX      lr

	.end
