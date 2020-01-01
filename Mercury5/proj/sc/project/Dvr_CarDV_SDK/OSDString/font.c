/*
 * font.c
 */
#include "Customer_Config.h"

// Keep this in SDK
#if defined(FONT_LARGE)
#include "Font_24_English.c"
#include "Font_20_West.c"
#include "Font_24_TChinese.c"
#include "Font_24_SChinese.c"
#include "Font_24_Japanese.c"
#include "Font_24_Korean.c"
#else
#include "Font_16_English.c"
#include "Font_16_West.c"
#include "Font_16_TChinese.c"
#include "Font_16_SChinese.c"
#include "Font_16_Japanese.c"
#include "Font_16_Korean.c"
#endif
