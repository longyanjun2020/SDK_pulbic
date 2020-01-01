/*
 * Copyright 2008-2009 NCC Inc. All Rights Reserved.
*/

#ifndef BNST_H
#define BNST_H

#ifdef __cplusplus
T_EXTERN "C"{
#endif

/*****************system configuration*******************/
#define THIRTY_TWO_BIT

/*****************************************************/
#ifdef THIRTY_TWO_BIT
#define ALG_BN_BITS		64
#define ALG_BN_BYTES	4
#define ALG_BN_BITS2	32
#define ALG_BN_BITS4	16
#define ALG_BN_MASK2	(0xffffffffL)
#define ALG_BN_MASK2l	(0xffff)
#define ALG_BN_MASK2h1	(0xffff8000L)
#define ALG_BN_MASK2h	(0xffff0000L)
#define ALG_BN_TBIT		(0x80000000L)
#endif

typedef struct 
{
	T_UINT32 *d;	/* Pointer to an array of 'ALG_BN_BITS2' bit chunks. */
	T_INT32 top;	/* Index of last used d +1. */
	T_INT32 dmax;	/* Size of the d array. */
	T_INT32 neg;	/* one if the number is negative */
	T_INT32 flags;
} T_ALG_BigNum;

typedef struct 
{
	T_INT32 ri;          /* number of bits in R */
	T_ALG_BigNum RR;     /* used to convert to montgomery form */
	T_ALG_BigNum N;      /* The modulus */
	T_ALG_BigNum Ni;     /* R*(1/R mod N) - N*Ni = 1 (Ni is only stored for bignum algorithm) */
	T_UINT32 n0;         /* least significant word of Ni */
	T_INT32 flags;
} T_ALG_BnMontCtx;

#ifdef  __cplusplus
}
#endif

#endif/*BNST_H*/
