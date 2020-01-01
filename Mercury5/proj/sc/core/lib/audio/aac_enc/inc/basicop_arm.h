/*___________________________________________________________________________
 |                                                                           |
 |   Constants and Globals                                                   |
 |                                                                           |
 | $Id: basic_op.h,v 1.8 2005/02/20 12:07:26 ehr Exp $
 |___________________________________________________________________________|
*/

#ifndef __BASICOP_ARM_H
#define __BASICOP_ARM_H


#include "typedef.h"
#undef	__inline
#define	__inline	static inline
/*
 * Multiply two 16-bit signed integers, shift the result right by
 * 15 and saturate it. (Saturation is only necessary if both inputs
 * were -0x8000, in which case the result "should" be 0x8000 and is
 * saturated to 0x7FFF.)
 */
__inline Word16 mult_arm(Word16 x, Word16 y)
{
#ifdef	__GNUC__
	Word32 product;
	// asm("smulbb %[result], %[Rx], %[Ry]" : [result] "=r" (product)
										 // : [Rx] "r" (x), [Ry] "r" (y));

	asm ("smulbb %0, %1, %2" : "=r" (product) : "r" (x) , "r" (y));
	asm ("qadd %0, %0, %0" : "+r" (product));
	return (Word16)(product >> 16);
#else
#if 1	
    Word32 product;
    __asm {
        smulbb product, x, y;
        qadd product, product, product;
    		
    }
    return (Word16) (product >> 16);   /* the qadd added one to the 15 */
#else
		Word32 product;
    __asm {
        smulbb product, x, y;
    		
    }
    return (Word16) (product >> 15);   /* the qadd added one to the 15 */
		
#endif		
#endif	// __GNUC__
}

/*
 * Multiply two 16-bit signed integers to give a 32-bit signed
 * integer. Shift left by one, and saturate the result. (Saturation
 * is only necessary if both inputs were -0x8000, in which case the
 * result "should" be 0x40000000 << 1 = +0x80000000, and is
 * saturated to +0x7FFFFFFF.)
 */
__inline Word32 L_mult_arm(Word16 x, Word16 y)
{
#ifdef	__GNUC__
	Word32 product;
	asm ("smulbb %0, %1, %2" : "=r" (product) : "r" (x) , "r" (y));
	asm ("qadd %0, %0, %0" : "+r" (product));
	return product;
#else
	
    Word32 product;
    __asm {
        smulbb product, x, y;
        qadd product, product, product;
    }
    return product;
#endif
}    

/*
 * Divide a 32-bit signed integer by 2^16, rounding to the nearest
 * integer (round up on a tie). Equivalent to adding 0x8000 with
 * saturation, then shifting right by 16.
 */
__inline Word16 round_arm(Word32 x)
{
#if 0	
    __asm {
        qadd x, x, 0x8000;
    }
    return extract_h(x);
#else
		return extract_h(x);
#endif
}



/*
 * Multiply two 16-bit signed integers together to give a 32-bit
 * signed integer, shift left by one with saturation, and add to
 * another 32-bit integer with saturation.
 * 
 * Note the intermediate saturation operation in the definition:
 * 
 *    L_mac(-1, -0x8000, -0x8000)
 * 
 * will give 0x7FFFFFFE and not 0x7FFFFFFF:
 *    the unshifted product is:   0x40000000
 *    shift left with saturation: 0x7FFFFFFF
 *    add to -1 with saturation:  0x7FFFFFFE
 */
__inline Word32 L_mac_arm(Word32 accumulator, Word16 x, Word16 y)
{	
#ifdef	__GNUC__
    Word32 product;
	asm ("smulbb %0, %1, %2" : "=r" (product) : "r" (x) , "r" (y));
	asm ("qdadd %0, %0, %1" : "+r" (accumulator) : "r" (product));
	return accumulator;
#else
    Word32 product;
    __asm {
        smulbb product, x, y;
        qdadd accumulator, accumulator, product;
    }
    return accumulator;
#endif
}

/*
 * Multiply two 16-bit signed integers together to give a 32-bit
 * signed integer, shift left by one with saturation, and subtract
 * from another 32-bit integer with saturation.
 * 
 * Note the intermediate saturation operation in the definition:
 * 
 *    L_msu(1, -0x8000, -0x8000)
 * 
 * will give 0x80000002 and not 0x80000001:
 *    the unshifted product is:         0x40000000
 *    shift left with saturation:       0x7FFFFFFF
 *    subtract from 1 with saturation:  0x80000002
 */
__inline Word32 L_msu_arm(Word32 accumulator, Word16 x, Word16 y)
{
#ifdef	__GNUC__
    Word32 product;
	asm("smulbb %0, %1, %2" : "=r" (product) : "r" (x) , "r" (y));
	asm("qdsub %0, %0, %1" : "+r" (accumulator) : "r" (product));
    return accumulator;
#else
    Word32 product;
    __asm {
        smulbb product, x, y;
        qdsub accumulator, accumulator, product;
    }
    return accumulator;
#endif
}



/*
 * Add two 32-bit signed integers with saturation.
 */
__inline Word32 L_add_arm(Word32 x, Word32 y)
{
#ifdef	__GNUC__
    Word32 result;
	asm("qadd %0, %1, %2" : "=r" (result) : "r" (x) , "r" (y));
    return result;
#else
    Word32 result;
    __asm {
        qadd result, x, y;
    }
    return result;
#endif
}

/*
 * Subtract one 32-bit signed integer from another with saturation.
 */
__inline Word32 L_sub_arm(Word32 x, Word32 y)
{
#ifdef	__GNUC__
    Word32 result;
	asm("qsub %0, %1, %2" : "=r" (result) : "r" (x) , "r" (y));
	return result;
#else
    Word32 result;
    __asm {
        qsub result, x, y;
    }
    return result;
#endif
}

/*
 * Shift a 32-bit signed integer left (or right, if the shift count
 * is negative). Saturate on overflow.
 */
__inline Word32 L_shl_arm(Word32 x, Word16 shift)
{
    int lz;
    int absx;
    if (shift <= 0)
        return x >> (-shift);
#if 1        
    absx = (x < 0 ? -x : x);
#ifdef	__GNUC__
	asm("clz %0, %1" : "=r" (lz) : "r" (absx));
#else
    __asm {
        clz lz, absx;
    }
#endif
    if (shift < lz || x == 0)
        return x << shift;
    if (x < 0)
        return ARMDSP_WORD32_MIN;
    else
        return ARMDSP_WORD32_MAX;
#else
    __asm {
        sub      shift,shift,#1
        mov      x,x,lsl shift   
        qadd     x,x,x
   }     
   return x;     
#endif        
     
}

/*
 * Shift a 32-bit signed integer left (or right, if the shift count
 * is negative). Saturate on overflow.
 */
__inline Word32 L_shl_pos_arm(Word32 x, Word16 shift)
{
#ifdef	__GNUC__
	asm("sub %0, %0, #1" : "+r" (shift));
	asm("mov %0, %0, lsl %1" : "+r" (x) : "r" (shift));
	asm("qadd %0, %0, %0" : "+r" (x));
#else
    __asm {
        sub      shift,shift,#1
        mov      x,x,lsl shift   
        qadd     x,x,x
   }     
   return x;          
#endif
}

/*
 * Shift a 32-bit signed integer right (or left, if the shift count
 * is negative). Saturate on overflow.
 */
__inline Word32 L_shr_arm(Word32 x, Word16 shift)
{

    int lz;
    int absx;
    if (shift >= 0)
        return x >> shift;
    absx = (x < 0 ? -x : x);
#ifdef	__GNUC__
	asm("clz %0, %1" : "=r" (lz) : "r" (absx));
#else
    __asm {
        clz lz, absx;
    }
#endif
    if (-shift < lz)
        return x << (-shift);
    if (x < 0)
        return ARMDSP_WORD32_MIN;
    else
        return ARMDSP_WORD32_MAX;
}


/*
 * Shift a 32-bit signed integer right (or left, if the shift count
 * is negative). Saturate on overflow.
 */
__inline Word32 L_shr_arm_pos(Word32 x, Word16 shift)
{

    int lz;
    if (shift >= 0)
        return x >> shift;

#ifdef	__GNUC__
	asm("clz %0, %1" : "=r" (lz) : "r" (x));
#else
    __asm {
        clz lz, x;
    }
#endif
    if (-shift < lz)
        return x << (-shift);

    return ARMDSP_WORD32_MAX;
}

/*
 * Return the number of bits of left shift needed to arrange for a
 * 16-bit signed integer to have value >= 0x4000 or <= -0x4001.
 * 
 * Returns zero if x is zero.
 */
__inline Word16 norm_s_arm(Word16 x)
{
    int lz;

    x = (Word16) (x ^ (x >> 15));      /* invert x if it's negative */
#ifdef	__GNUC__
	asm("clz %0, %1" : "=r" (lz) : "r" (x));
#else
    __asm {
        clz lz, x;
    }
#endif
    return (Word16) (lz - 17);
}

/*
 * Divide one 16-bit signed integer by another, and produce a
 * 15-bit fixed point fractional result (by multiplying the true
 * mathematical result by 0x8000). The divisor (denominator) is
 * assumed to be non-zero and also assumed to be greater or equal
 * to the dividend (numerator). Hence the (unscaled) result is
 * necessarily within the range [0,1].
 * 
 * Both operands are assumed to be positive.
 * 
 * After division, the result is saturated to fit into a 16-bit
 * signed integer. (The only way this can happen is if the operands
 * are equal, so that the result would be 1, i.e. +0x8000 in 15-bit
 * fixed point.)
 */
__inline Word16 div_s_arm(Word16 x, Word16 y)
{
    Word32 quot;
   // assert(y > 0);
   // assert(x >= 0);
   // assert(x <= y);
    quot = 0x8000 * x;
    quot /= y;
    if (quot > ARMDSP_WORD16_MAX)
        return ARMDSP_WORD16_MAX;
    else
        return (Word16)quot;
}

/*
 * Return the number of bits of left shift needed to arrange for a
 * 32-bit signed integer to have value >= 0x40000000 (if 
 * 
 * Returns zero if x is zero.
 */
__inline Word16 norm_l_arm(Word32 x)
{
    int lz;

    x ^= (x >> 31);                    /* invert x if it's negative */
#ifdef	__GNUC__
	asm("clz %0, %1" : "=r" (lz) : "r" (x));
#else
    __asm {
        clz lz, x;
    }
#endif
    return (Word16) (lz - 1);
}
__inline Word32 fixmul_32x16b_arm (const Word32 a, const Word16 b)
{
#ifdef	__GNUC__
	Word32 rH;
	asm("smulwb %0, %1, %2" : "=r" (rH) : "r" (a) , "r" (b));
	asm("qadd %0, %0, %0" : "+r" (rH));
	return rH;
#else
  Word32 rH;

	__asm
		{
			   smulwb rH,a,b;
			   qadd    rH,rH,rH;
	  }	
 
  return rH;
#endif
}

__inline void
butterfly32a_16_arm( Word32 ro, Word32 io, Word16 rwh, Word16 iwh, Word32 *rx, Word32 *ix )
{
#ifdef	__GNUC__
	Word32 acc,temp1;
	asm("smulwb %0, %1, %2" : "=r" (acc) : "r" (ro) , "r" (rwh));
	asm("smulwb %0, %1, %2" : "=r" (temp1) : "r" (io) , "r" (iwh));
	asm("qsub %0, %0, %1" : "+r" (acc) : "r" (temp1));
	asm("qadd %0, %0, %0" : "+r" (acc));
	asm("mov %0, %1" : "=r" (*rx) : "r" (acc));
	asm("smulwb %0, %1, %2" : "=r" (acc) : "r" (ro) , "r" (iwh));
	asm("smlawb %0, %1, %2, %0" : "+r" (acc) : "r" (io) , "r" (rwh));
	asm("qadd %0, %0, %0" : "+r" (acc));
	asm("mov %0, %1" : "=r" (*ix) : "r" (acc));
#else
  Word32 acc,temp1;
  __asm{
  		
//
//  acc = L_mult(roh, rwh);
//  acc = L_msu(acc, ioh, iwh);
//  acc = L_mac(acc, mult(rol, rwh), 1);
//  acc = L_msu(acc, mult(iol, iwh), 1);
//  *rx = acc;   	
       smulwb acc,ro,rwh;
       smulwb temp1,io,iwh;
       qsub   acc,acc,temp1;
       qadd acc,acc,acc;
       mov  *rx,acc
  
//  acc = L_mult(roh, iwh);
//  acc = L_mac(acc, ioh, rwh);
//  acc = L_mac(acc, mult(rol, iwh), 1);
//  acc = L_mac(acc, mult(iol, rwh), 1);
//  *ix = acc;      
       smulwb acc,ro,iwh;
       smlawb acc,io,rwh,acc;
       qadd acc,acc,acc;
       mov  *ix,acc
  }                                         
#endif
}

__inline void
butterfly32b_16_arm( Word32 ro, Word32 io, Word16 ch, Word16 sh, Word32 *rx, Word32 *ix )
{
    Word32 acc,temp1;

#ifdef	__GNUC__
	asm("smulwb %0, %1, %2" : "=r" (acc) : "r" (ro), "r" (ch));
	asm("smlawb %0, %1, %2, %3" : "=r" (acc) : "r" (io), "r" (sh), "r"(acc));
	asm("qadd %0, %0, %0" : "+r" (acc));
	asm("mov %0, %1" : "=r" (*rx) : "r" (acc));

	asm("smulwb %0, %1, %2" : "=r" (acc) : "r" (io), "r" (ch));
	asm("smulwb %0, %1, %2" : "=r" (temp1) : "r" (ro), "r"(sh));
	asm("qsub %0, %0, %1" : "+r" (acc) : "r" (temp1));
	asm("qadd %0, %0, %0" : "+r" (acc));
	asm("mov %0, %1" : "=r" (*ix) : "r" (acc));
#else
//  
//  acc = (roh* ch);
//  acc = acc+ (ioh* sh);
//  acc = acc+ ((rol* ch)>>15);
//  acc = acc+ ((iol* sh)>>15);
//  acc = acc <<1;
//  *rx = acc;       
   __asm{
  		 
       smulwb acc,ro,ch;
       smlawb acc,io,sh,acc;
       qadd acc,acc,acc;
       mov  *rx,acc
       
//  acc = (ioh* ch);
//  acc = acc- (roh* sh);
//  acc = acc+((iol* ch)>>15);
//  acc = acc- ((rol* sh)>>15);
//  acc =acc<<1;
//  
//  *ix = acc;    
       smulwb acc,io,ch;
       smulwb temp1,ro,sh;
       qsub   acc,acc,temp1;
       qadd acc,acc,acc;
       mov  *ix,acc
  
  }                                           
#endif
                                        
}
__inline Word32 fixmuldiv2_32x16b_arm (const Word32 a, const Word16 b)
{
		Word32 rH;
#ifdef	__GNUC__
	asm("smulwb %0, %1, %2" : "=r" (rH) : "r" (a), "r" (b));
#else
	__asm
		{
			   smulwb rH,a,b;
	  }		
#endif
  return rH;
}

__inline Word32 fixmul_32x16t_arm (const Word32 a, const Word32 b)
{
  
	Word32 rH;
#ifdef	__GNUC__
	asm("smulwt %0, %1, %2" : "=r" (rH) : "r" (a), "r" (b));
	asm("qadd %0, %0, %0" : "+r" (rH));
#else
	__asm
		{
			   smulwt rH,a,b;
			   qadd   rH,rH,rH;
	  }		
#endif
  return rH;
}
 
__inline Word32 fixmuldiv2_32x16t_arm (const Word32 a, const Word32 b)
{
	Word32 rH;
#ifdef	__GNUC__
	asm("smulwt %0, %1, %2" : "=r" (rH) : "r" (a), "r" (b));
#else
	__asm
		{
			   smulwt rH,a,b;
	  }		
#endif
  return rH;
}
 
__inline void fixmadd_32x16t_arm (Word32 *a, const Word32 x, const Word32 y)
{
#ifdef	__GNUC__
	asm("smlawt %0, %1, %2, %0" : "+r" (*a) : "r" (x), "r" (y));
#else
	__asm
		{
			   smlawt *a,x,y,*a;
	  }		
#endif
}

__inline Word32 fixmul_arm (const Word32 a, const Word32 b)
{
  Word32 RdLo,RdHi;
#ifdef	__GNUC__
	asm("smull %0, %1, %2, %3" : "=&r" (RdLo), "=&r" (RdHi) : "r" (a), "r" (b));
	asm("qadd %0, %0, %0" : "+r" (RdHi));

#else
	__asm
		{
			   smull RdLo,RdHi,a,b;
	  		 qadd  RdHi,RdHi,RdHi;	
	  }		
#endif
  return RdHi;
}

__inline Word32 fixmuldiv2_arm (const Word32 a, const Word32 b)
{
  Word32 RdLo,RdHi;
#ifdef	__GNUC__
	asm("smull %0, %1, %2, %3" : "=&r" (RdLo) , "=&r" (RdHi) : "r" (a), "r" (b));
#else
	__asm
		{
			   smull RdLo,RdHi,a,b;
	  		
	  }		
#endif
	 return RdHi; 
}

__inline void fixmadd_arm (Word32 *a, const Word32 x, const Word32 y)
{
	Word32 RdLo=0;
	
#ifdef	__GNUC__
	// asm("smlal %0, %1, %2, %3" : "=&r" (RdLo) , "=&r" (*a) : "r" (x), "r" (y));
	asm("smlal %0, %1, %2, %3" : "+r" (RdLo) , "+r" (*a) : "r" (x), "r" (y));
#else
	__asm
		{
			   smlal RdLo,*a,x,y;
	  }		
#endif
	
}
__inline Word16 ffr_norm32_arm(Word32 x)
{
	int lz;
    x ^= (x >> 31);                    /* invert x if it's negative */
#ifdef	__GNUC__
	asm("clz %0, %1" : "=r" (lz) : "r" (x));
#else
    __asm {
        clz lz, x;
    }
#endif
    return (Word16) (lz - 1);
}	

__inline Word32 ffr_norm32_arm_pos(Word32 x)
{
	int lz;

#ifdef	__GNUC__
	asm("clz %0, %1" : "=r" (lz) : "r" (x));
#else
    __asm {
        clz lz, x;
    }
#endif
    return (lz - 1);
}	

/*
 * Shift a 16-bit signed integer right (or left, if the shift count
 * is negative). Saturate on overflow.
 */
__inline Word16 shr_arm(Word16 x, Word16 shift)
{
    if (shift >= 0 || x == 0)
        return (Word16) (x >> shift);
//    if (shift < -15)
//        shift = -16;
//    return saturate(x << (-shift));
#ifdef	__GNUC__
	asm("rsb %0, %0, #0" : "+r" (shift));
	asm("mov %0, %0, lsl %1" : "+r" (x) : "r" (shift));
#else
    __asm {
        rsb     shift,shift,#0   
        mov     x,x,lsl shift
    }
#endif
    return  x;
}

__inline Word32 EXPAND_arm(Word16 x)
{
    Word32 hi, lo;
#ifdef	__GNUC__
	asm("and %0, %1, #0xff00" : "=r" (hi) : "r" (x));
	asm("and %0, %1, #0x00ff" : "=r" (lo) : "r" (x));
	asm("mov %0, %0, lsl #8"  : "+r" (hi));
	asm("orr %0, %0, %1" : "+r" (hi) : "r" (lo));
#else
    __asm {
       and      hi,x,#0xff00
       and      lo,x,#0x00ff
       mov      hi,hi,lsl #8
       orr      hi,hi,lo    
    }
#endif

    return  hi;
}

#undef	__inline

#endif
