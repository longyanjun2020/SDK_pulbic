#ifndef AEON_GCC_H
#define AEON_GCC_H

#define SH_PLUS32(a)    (a)

#define CMOV_ALWAYS_WITH_O      __attribute__((cmov))

#define CMOV_NEVER              __attribute__((nocmov))

#define SHORT_BRANCH_ALWAYS     __attribute__((short_branch))

#define SHORT_BRANCH_NEVER      __attribute__((noshort_branch))

#define L_PREFETCH(p, ofs)              \
{   unsigned _p_ = (unsigned)(p);       \
    asm volatile ( "l.prefetch %0(%1)"  \
        :                               \
        : "I"(ofs), "r"(_p_)          \
    );}

#define v00 v0
#define v01 v1
#define v02 v2
#define v03 v3
#define v04 v4
#define v05 v5
#define v06 v6
#define v07 v7
#define v08 v8
#define v09 v9

#endif
