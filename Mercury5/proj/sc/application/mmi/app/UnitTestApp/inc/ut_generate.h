// ut_generate.h
#ifndef __UT_GENERATE_H_
#define __UT_GENERATE_H_

#include "ven_types.h"

extern bool generateBool(void);
extern u32 generateU32(u32 max);
extern u16 generateU16(u16 max);
extern u8 generateU8(u8 max);
extern bool generate_number_string(u32 min_length, u32 max_length, char *str);
extern bool generate_string(u32 min_length, u32 max_length, char *str);
extern bool generate_wstring(u32 min_length, u32 max_length, u16 *str);

#endif
