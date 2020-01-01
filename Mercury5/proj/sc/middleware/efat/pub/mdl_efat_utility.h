////////////////////////////////////////////////////////////////////////////////
/// @file   mdl_efat_pub.h
/// @author MStar Semiconductor Inc.
/// @brief  Shell command parser state machine
////////////////////////////////////////////////////////////////////////////////
#ifndef MDL_EFAT_UTILITY_H
#define MDL_EFAT_UTILITY_H

s32   uStrcat(u16 * dst, u16 * src);
u32   uStrlen(u16 * str);
s32   uStrcmp(u16 * dst, u16 * src);
s32   uStrncmp(u16 * dst, u16 * src, u32 n);
s32   uStrcasecmp(u16 * dst, u16 * src);
s32   uStrncasecmp(u16 * dst, u16 * src, u32 n);
s32   uStrcpy(u16 * dst, u16 * src);
s32   uStrncpy(u16 * dst, u16 * src, u32 n);
u16 * uStrchr(u16 * dst, u16 ch);
u16 * uStrrchr(u16 * dst, u16 ch);
u16 * uStrnchr(u16 * dst, u16 ch, u32 occur);
u16 * uStrstr(u16 * dst, u16 * src);
s32   uStrAddChar(u16 * dst, u16 ch);
s32   uStrTo8bitStr(u8 * dst, u16 * src);
s32   u8bitStrTouStr(u16 * dst, u8 * src);
s32   uStrToUcs2Str(u8 * dst, u16 * src);
s32   Ucs2StrToUstr(u16 * dst, u8 * src);

#endif // end of mdl_efat_pub.h

