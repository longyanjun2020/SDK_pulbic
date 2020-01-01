#ifndef _ASSEMBLY_H
#define _ASSEMBLY_H


#if defined(__GNUC__) && defined(ARM)

static __inline int MULSHIFT32(int x, int y)
{
    int zlow;

	//UartSendTrace("x =%d y= %d", x,y)
	#if 0
    __asm {
    	smull zlow,y,x,y
   	}
	#else
	asm("smull %0,%1,%2,%1":"+r"(zlow),"+r"(y):"r"(x));
	#endif
    return y;
}

/* 
 multiply y[31:0] with x[31:16], return top 32bits of 48bits result
*/
static __inline int SMULWT(int x, int y)
{
    int ret;

	#if 0
    __asm {
    	smulwt ret,y,x
   	}
	#else
	asm("smulwt %0,%1,%2":"+r"(ret):"r"(y), "r"(x));
	#endif
    return ret;
}


static __inline int FASTABS(int x) 
{
	int t;

	#if 0
	__asm {
		eor	t, x, x, asr #31
		sub	t, t, x, asr #31
	}
	#else
	asm("eor	%0, %1, %1, asr #31":"+r"(t):"r"(x));
	asm("sub	%0, %0, %1, asr #31":"+r"(t):"r"(x));
	#endif
	return t;
}

static __inline int CLZ(int x)
{
	int numZeros;

	#if 0
	__asm {
		cmp		x, #0
		mvnlt	x, x
		clz		numZeros, x
		sub		numZeros, numZeros, #1
		moveq	numZeros, #0
	} 
	#else
	asm("cmp	%0,  #0"::"r"(x));
	asm("mvnlt	%0, %0":"+r"(x));
	asm("clz	%0, %1":"=r"(numZeros):"r"(x));
	asm("sub	%0, %0, #1":"+r"(numZeros));
	asm("moveq	%0, #0":"=r"(numZeros));
	#endif
	return numZeros;
}

#else
static __inline int MULSHIFT32(int x, int y)	
{
	//if( (x!=0) && (y!=0))
	//UartSendTrace("x =%d  y = %d, x*y= %d\n", x, y, ((int)(((long long)(x) * (long long)(y))>>32)));
	return ((int)(((long long)(x) * (long long)(y))>>32));
}


static __inline short CLIPTOSHORT(int x)
{
	int sign;

	/* clip to [-32768, 32767] */
	sign = x >> 31;
	if (sign != (x >> 15))
		x = sign ^ ((1 << 15) - 1);

	return (short)x;
}

static __inline int FASTABS(int x) 
{
	int sign;

	sign = x >> (sizeof(int) * 8 - 1);
	x ^= sign;
	x -= sign;

	return x;
}

static __inline int CLZ(int x)
{
	int numZeros;

	if (!x)
		return (sizeof(int) * 8);

	numZeros = 0;
	while (!(x & 0x80000000)) {
		numZeros++;
		x <<= 1;
	} 

	return numZeros;
}
#endif

#endif /* _ASSEMBLY_H */
