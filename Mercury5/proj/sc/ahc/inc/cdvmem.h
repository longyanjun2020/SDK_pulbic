
#ifndef _CDV_MEM_H_
#define _CDV_MEM_H_
 
#define	NONCAHE_SEG		0x90000000

#define	TO_PHYSICAL(p)	(p & 0x0fffffff)
#define	TO_NONCACHE(p)	((void*)((int)p + NONCAHE_SEG))

/**
	tbl[(NONCAHE_SEG + i) >> 20] =			\
        ( i      ) |		\// Physical Address
        ( 3 << 10) |		\// Access in supervisor mode, 3 = 0b11, Acces permission bits.
        (15 <<  5) |		\// Domain, 15 = 0xF, Domain control bits.
        ( 1 <<  4) |		\// Must be 1.
        0x2;				\// Set as 1 Mbyte section, 0x2 = 0b0010.  C = 0, B = 0. non-cacheable, non-bufferable.
	for (i = 0x01000000; i <0x05000000; i += 0x00100000) {	\
		tbl[(NONCAHE_SEG + i) >> 20] =	\
			( i      ) |				\// Physical Address 
			( 3 << 10) |				\// Access in supervisor mode, 3 = 0b11, Acces permission bits.
			(15 <<  5) |				\// Domain, 15 = 0xF, Domain control bits. 
			( 1 <<  4) |				\// Must be 1.
			0x2;						\// Set as 1 Mbyte section, 0x2 = 0b0010.  C = 0, B = 0. non-cacheable, non-bufferable.
	}				

*/

#define	SETUP_NONCACHE(tbl)	\
	i = 0x00100000;			\
	tbl[(NONCAHE_SEG + i) >> 20] =			\
        ( i      ) |		\
        ( 3 << 10) |		\
        (15 <<  5) |		\
        ( 1 <<  4) |		\
        0x2;				\
	for (i = 0x01000000; i <0x05000000; i += 0x00100000) {	\
		tbl[(NONCAHE_SEG + i) >> 20] =	\
			( i      ) |				\
			( 3 << 10) |				\
			(15 <<  5) |				\
			( 1 <<  4) |				\
			0x2;						\
	}									\


#endif//_CDV_MEM_H_