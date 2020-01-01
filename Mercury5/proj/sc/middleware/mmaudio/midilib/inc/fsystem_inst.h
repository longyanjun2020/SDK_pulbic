/*
 * Copyright (c) 2007 Faith, Inc. All rights reserved.
 *
 * $Id: fsystem_inst.h,v 1.4 2006/06/28 05:33:49 fujii Exp $
 */
#ifndef FSYSTEM_INST_H__
#define FSYSTEM_INST_H__

#include "fsystem_types.h"

//#if defined(WIN32) && defined(_MSC_VER)     //&& _MSC_VER < 1400
#if 0

#pragma warning( disable : 4035 ) 

static s_32 __fastcall _labs( s_32 x )
{
	__asm{
		mov			eax, ecx
		neg			ecx
		bt			eax, 31
		cmovb		eax, ecx
	}
}
static s_32 __fastcall MUL16x16s6( s_16 a, s_16 b )
{
	__asm{
		movsx		eax, cx
		movsx		edx, dx
		imul		eax, edx
		sar			eax, 6
	}
}
static s_32 __fastcall MUL16x16s12( s_16 a, s_16 b )
{
	__asm{
		movsx		eax, cx
		movsx		edx, dx
		imul		eax, edx
		sar			eax, 12
	}
}
static s_32 __fastcall MUL16x16s14( s_16 a, s_16 b )
{
	__asm{
		movsx		eax, cx
		movsx		edx, dx
		imul		eax, edx
		sar			eax, 14
	}
}
static s_32 __fastcall MUL16x16s15( s_16 a, s_16 b )
{
	__asm{
		movsx		eax, cx
		movsx		edx, dx
		imul		eax, edx
		sar			eax, 15
	}
}
static s_32 __fastcall MUL32x16s16( s_32 a, s_16 b )
{
	__asm{
		mov			eax, ecx
		movsx		edx, dx
		imul		edx
		shr			eax, 16
		sal			edx, 32-16
		or			eax, edx
	}
}
static s_32 __fastcall MUL32x16s15( s_32 a, s_16 b )
{
	__asm{
		mov			eax, ecx
		movsx		edx, dx
		imul		edx
		shr			eax, 15
		sal			edx, 32-15
		or			eax, edx
	}
}
static s_32 __fastcall MUL32x16s14( s_32 a, s_16 b )
{
	__asm{
		mov			eax, ecx
		movsx		edx, dx
		imul		edx
		shr			eax, 14
		sal			edx, 32-14
		or			eax, edx
	}
}
static s_32 __fastcall MUL32x16s13( s_32 a, s_16 b )
{
	__asm{
		mov			eax, ecx
		movsx		edx, dx
		imul		edx
		shr			eax, 13
		sal			edx, 32-13
		or			eax, edx
	}
}
static s_32 __fastcall MUL32x16s12( s_32 a, s_16 b )
{
	__asm{
		mov			eax, ecx
		movsx		edx, dx
		imul		edx
		shr			eax, 12
		sal			edx, 32-12
		or			eax, edx
	}
}
static s_32 __fastcall MUL32x16s10( s_32 a, s_16 b )
{
	__asm{
		mov			eax, ecx
		movsx		edx, dx
		imul		edx
		shr			eax, 10
		sal			edx, 32-10
		or			eax, edx
	}
}
static s_32 __fastcall MUL32x16s8( s_32 a, s_16 b )
{
	__asm{
		mov			eax, ecx
		movsx		edx, dx
		imul		edx
		shr			eax, 8
		sal			edx, 32-8
		or			eax, edx
	}
}
static s_32 __fastcall MUL32x16s6( s_32 a, s_16 b )
{
	__asm{
		mov			eax, ecx
		movsx		edx, dx
		imul		edx
		shr			eax, 6
		sal			edx, 32-6
		or			eax, edx
	}
}
static s_32 __fastcall MUL32x16s5( s_32 a, s_16 b )
{
	__asm{
		mov			eax, ecx
		movsx		edx, dx
		imul		edx
		shr			eax, 5
		sal			edx, 32-5
		or			eax, edx
	}
}
static s_32 __fastcall MUL32x32s12( s_32 a, s_32 b )
{
	__asm{
		mov			eax, ecx
		imul		edx
		shr			eax, 12
		sal			edx, 32-12
		or			eax, edx
	}
}
static s_32 __fastcall MUL32x32s15( s_32 a, s_32 b )
{
	__asm{
		mov			eax, ecx
		imul		edx
		shr			eax, 15
		sal			edx, 32-15
		or			eax, edx
	}
}
static s_32 __fastcall MUL32x32s16( s_32 a, s_32 b )
{
	__asm{
		mov			eax, ecx
		imul		edx
		shr			eax, 16
		sal			edx, 32-16
		or			eax, edx
	}
}
static s_32 __fastcall MUL32x32s30( s_32 a, s_32 b )
{
	__asm{
		mov			eax, ecx
		imul		edx
		shr			eax, 30
		sal			edx, 32-30
		or			eax, edx
	}
}
static s_32 __fastcall MUL32x32s32( s_32 a, s_32 b )
{
	__asm{
		mov			eax, ecx
		imul		edx
		mov			eax, edx
	}
}
static s_32 __fastcall MUL8x16( s_8 a, s_16 b )
{
	__asm{
		movsx		eax, cl
		movsx		edx, dx
		imul		eax, edx
	}
}
#pragma warning( default : 4035 ) 

#else /* WIN32 */

#define _labs( x )              ( ((x)>0) ? (x) : -(x) )

#define MUL16x16s6( a , b )     ((((s_32)(a))*((s_32)(b)))>>6)
#define MUL16x16s12( a , b )    ((((s_32)(a))*((s_32)(b)))>>12)
#define MUL16x16s14( a , b )    ((((s_32)(a))*((s_32)(b)))>>14)
#define MUL16x16s15( a , b )    ((((s_32)(a))*((s_32)(b)))>>15)

#define MUL32x16s16( a , b )    (s_32)((((s_64)(a))*((s_64)(b)))>>16)
#define MUL32x16s15( a , b )    (s_32)((((s_64)(a))*((s_64)(b)))>>15)
#define MUL32x16s14( a , b )    (s_32)((((s_64)(a))*((s_64)(b)))>>14)
#define MUL32x16s13( a , b )    (s_32)((((s_64)(a))*((s_64)(b)))>>13)
#define MUL32x16s12( a , b )    (s_32)((((s_64)(a))*((s_64)(b)))>>12)
#define MUL32x16s10( a , b )    (s_32)((((s_64)(a))*((s_64)(b)))>>10)
#define MUL32x16s8( a , b )     (s_32)((((s_64)(a))*((s_64)(b)))>>8)
#define MUL32x16s6( a , b )     (s_32)((((s_64)(a))*((s_64)(b)))>>6)
#define MUL32x16s5( a , b )     (s_32)((((s_64)(a))*((s_64)(b)))>>5)

#define MUL32x32s12( a , b )    (s_32)((((s_64)(a))*((s_64)(b)))>>12)
#define MUL32x32s15( a , b )    (s_32)((((s_64)(a))*((s_64)(b)))>>15)
#define MUL32x32s16( a , b )    (s_32)((((s_64)(a))*((s_64)(b)))>>16)
#define MUL32x32s30( a , b )    (s_32)((((s_64)(a))*((s_64)(b)))>>30)
#define MUL32x32s32( a , b )    (s_32)((((s_64)(a))*((s_64)(b)))>>32)

#define MUL8x16( a , b )        ((s_32)(a))*((s_32)(b))

#endif /* WIN32 */

#endif /* FSYSTEM_INST_H__ */
