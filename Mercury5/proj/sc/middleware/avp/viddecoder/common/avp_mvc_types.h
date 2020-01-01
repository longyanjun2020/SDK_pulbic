#ifndef MVC_TYPES_H
#define MVC_TYPES_H

#include <stdint.h>

typedef uint8_t  uchar;
typedef int8_t   int8;
typedef uint8_t  uint8;
typedef int16_t  int16;
typedef uint16_t uint16;
typedef int32_t  int32;
typedef uint32_t uint32;
typedef int64_t  int64;
typedef uint64_t uint64;

typedef union vec32_u {
    uint32 u32;
    int32  i32;
    uint16 u16[2];
    int16  i16[2];
    uint8  u8 [4];
    int8   i8 [4];
} vec32_ut;

typedef union vec64_u {
    uint64 u64;
    int64  i64;
    uint32 u32[2];
    int32  i32[2];
    uint16 u16[4];
    int16  i16[4];
    uint8  u8 [8];
    int8   i8 [8];
} vec64_ut;


typedef struct {
    int8 val;
    int8 len;
} tab_type;

typedef struct {
    short val;
    int8 len;
} tab_type2;

typedef struct {
    short val;
    short len;
} tab_type3;

typedef struct {
    uint16 cmp;
} tab_type2b;

typedef struct {
    int16 cmp;
} tab_type2c;

typedef struct {
    uchar val;
    int8 len;
}
#ifdef __GNUC__
__attribute__ ((packed))
#endif
tab_type4;

typedef struct {
    union {
        struct {
            uchar val[3];
            int8 len;
        } x;
        uint32 cmp;
    } a;
} tab_type4b;

#endif /* MVC_TYPES_H */
