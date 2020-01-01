#ifndef __ZLIB_ROM_API_H__
#define __ZLIB_ROM_API_H__

#if !defined(__SDK_SIMULATION__) && (ZLIB_USE_ROM==1)
#define ZLIB_FUN_TAB_SECTION __attribute__((section ("zlib_fun_tab_section")))
#define ZLIB_VAR_TAB_SECTION __attribute__((section ("zlib_var_tab_section")))
#else
#define ZLIB_FUN_TAB_SECTION
#define ZLIB_VAR_TAB_SECTION
#endif

#define ZLIB_ROM_EXTERN extern

#endif /* __ZLIB_ROM_API_H__ */
