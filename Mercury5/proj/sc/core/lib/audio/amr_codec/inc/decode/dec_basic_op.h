/*___________________________________________________________________________
 |                                                                           |
 |   Constants and Globals                                                   |
 |                                                                           |
 | $Id $
 |___________________________________________________________________________|
*/
extern Flag Decoder_Overflow;
extern Flag Decoder_Carry;

#define MAX_32 (Word32)0x7fffffffL
#define MIN_32 (Word32)0x80000000L

#define MAX_16 (Word16)0x7fff
#define MIN_16 (Word16)0x8000


#define CODE_UNOPTIMIZED 0
#define GNU_ARM_ASM_SYNTAX 1
#define ARM_ASM_SYNTAX 2

#define AMR_BUILD_OPT CODE_UNOPTIMIZED
/*___________________________________________________________________________
 |                                                                           |
 |   Prototypes for basic arithmetic operators                               |
 |___________________________________________________________________________|
*/

Word16 Decoder_add (Word16 var1, Word16 var2);    /* Short add,           1   */
Word16 Decoder_sub (Word16 var1, Word16 var2);    /* Short sub,           1   */
Word16 Decoder_abs_s (Word16 var1);               /* Short abs,           1   */
Word16 Decoder_shl (Word16 var1, Word16 var2);    /* Short shift left,    1   */
Word16 Decoder_shr (Word16 var1, Word16 var2);    /* Short shift right,   1   */
Word16 Decoder_mult (Word16 var1, Word16 var2);   /* Short mult,          1   */
Word32 Decoder_L_mult (Word16 var1, Word16 var2); /* Long mult,           1   */
Word16 Decoder_negate (Word16 var1);              /* Short negate,        1   */

#ifdef VC_CODE
Word16 Decoder_extract_h (Word32 L_var1);         /* Extract high,        1   */
Word16 Decoder_extract_l (Word32 L_var1);         /* Extract low,         1   */
#else
#define Decoder_extract_h(L_var1)	(Word16)(L_var1 >> 16)
#define Decoder_extract_l(L_var1)	(Word16)(L_var1)
#endif

Word16 Decoder_round (Word32 L_var1);             /* Round,               1   */
Word32 Decoder_L_mac (Word32 L_var3, Word16 var1, Word16 var2);   /* Mac,  1  */
Word32 Decoder_L_msu (Word32 L_var3, Word16 var1, Word16 var2);   /* Msu,  1  */

Word32 Decoder_L_add (Word32 L_var1, Word32 L_var2);    /* Long add,        2 */
Word32 Decode_L_sub (Word32 L_var1, Word32 L_var2);    /* Long sub,        2 */
Word32 Decoder_L_negate (Word32 L_var1);                /* Long negate,     2 */
Word16 Decoder_mult_r (Word16 var1, Word16 var2);       /* Mult with round, 2 */
Word32 Decoder_L_shl (Word32 L_var1, Word16 var2);      /* Long shift left, 2 */
Word32 Decoder_L_shr (Word32 L_var1, Word16 var2);      /* Long shift right, 2*/
Word16 Decoder_shr_r (Word16 var1, Word16 var2);        /* Shift right with
                                                   round, 2           */

//Word32 L_deposit_h (Word16 var1);        /* 16 bit var1 -> MSB,     2 */
//Word32 L_deposit_l (Word16 var1);        /* 16 bit var1 -> LSB,     2 */

#define	Decoder_L_deposit_h(var1)	((Word32)(var1 << 16))
#define	Decoder_L_deposit_l(var1)	((Word32) var1)

Word32 Decoder_L_shr_r (Word32 L_var1, Word16 var2); /* Long shift right with
                                                round,  3             */
Word32 Decoder_L_abs (Word32 L_var1);            /* Long abs,              3  */
Word16 Decoder_norm_s (Word16 var1);             /* Short norm,           15  */
Word16 Decoder_div_s (Word16 var1, Word16 var2); /* Short division,       18  */
Word16 Decoder_norm_l (Word32 L_var1);           /* Long norm,            30  */   

