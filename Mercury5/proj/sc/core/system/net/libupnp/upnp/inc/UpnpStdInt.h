#ifndef UPNPSTDINT_H
#define UPNPSTDINT_H

#if !defined(UPNP_USE_BCBPP)

/* Sized integer types. */
#ifndef __ARMGCC__
#include <stdint.h>
#else //compilation error for cygWin <stdint.h>
//from ADS1.2
/*
 * 'signed' is redundant below, except for 'signed char' and if
 * the typedef is used to declare a bitfield.
 * '__int64' is used instead of 'long long' so that this header
 * can be used in -strict mode.
 */

    /* 7.18.1.1 */
#define __int64 long long

    /* exact-width signed integer types */
typedef   signed          char int8_t;
typedef   signed short     int int16_t;
typedef   signed           int int32_t;
typedef   signed       __int64 int64_t;

    /* exact-width unsigned integer types */
typedef unsigned          char uint8_t;
typedef unsigned short     int uint16_t;
typedef unsigned           int uint32_t;
typedef unsigned       __int64 uint64_t;

    /* 7.18.1.2 */

    /* smallest type of at least n bits */
    /* minimum-width signed integer types */
typedef   signed          char int_least8_t;
typedef   signed short     int int_least16_t;
typedef   signed           int int_least32_t;
typedef   signed       __int64 int_least64_t;

    /* minimum-width unsigned integer types */
typedef unsigned          char uint_least8_t;
typedef unsigned short     int uint_least16_t;
typedef unsigned           int uint_least32_t;
typedef unsigned       __int64 uint_least64_t;

    /* 7.18.1.3 */

    /* fastest minimum-width signed integer types */
typedef   signed           int int_fast8_t;
typedef   signed           int int_fast16_t;
typedef   signed           int int_fast32_t;
typedef   signed       __int64 int_fast64_t;

    /* fastest minimum-width unsigned integer types */
typedef unsigned           int uint_fast8_t;
typedef unsigned           int uint_fast16_t;
typedef unsigned           int uint_fast32_t;
typedef unsigned       __int64 uint_fast64_t;

    /* 7.18.1.4 integer types capable of holding object pointers */
typedef   signed           int intptr_t;
typedef unsigned           int uintptr_t;

    /* 7.18.1.5 greatest-width integer types */
typedef   signed       __int64 intmax_t;
typedef unsigned       __int64 uintmax_t;

#endif

#ifdef UPNP_USE_MSVCPP
	/* no ssize_t defined for VC */
	#ifdef  _WIN64
		typedef int64_t ssize_t;
	#else
		typedef int32_t ssize_t;
	#endif
#endif

#endif /* !defined(UPNP_USE_BCBPP) */

#endif /* UPNPSTDINT_H */
