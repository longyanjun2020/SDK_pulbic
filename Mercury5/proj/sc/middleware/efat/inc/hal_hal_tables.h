#ifndef ONCE_HAL_TABLES_H
#define ONCE_HAL_TABLES_H
////////////////////////////////////////////////////////////////////////////////
///@file hal_tables.h
///@author MStar Semiconductor Inc.
///@brief
////////////////////////////////////////////////////////////////////////////////

#include <pkgconf_hal.h>
#include <infra_type.h>
//#include <hal_hal_arch.h>
#if 1
/*------------------------------------------------------------------------*/

#define __string(_x) #_x
#define __xstring(_x) __string(_x)

#ifndef EFAT_HAL_TABLE_BEGIN
#define EFAT_HAL_TABLE_BEGIN( _label, _name )                                 \
__asm__(".section \".ecos.table." __xstring(_name) ".begin\",\"aw\"\n"       \
    ".globl " __xstring(EFAT_LABEL_DEFN(_label)) "\n"                         \
    ".type    " __xstring(EFAT_LABEL_DEFN(_label)) ",object\n"                \
    ".p2align " __xstring(ARC_P2ALIGNMENT) "\n"                           \
__xstring(EFAT_LABEL_DEFN(_label)) ":\n"                                      \
    ".previous\n"                                                            \
       )
#endif

#ifndef EFAT_HAL_TABLE_END
#define EFAT_HAL_TABLE_END( _label, _name )                                   \
__asm__(".section \".ecos.table." __xstring(_name) ".finish\",\"aw\"\n"      \
    ".globl " __xstring(EFAT_LABEL_DEFN(_label)) "\n"                         \
    ".type    " __xstring(EFAT_LABEL_DEFN(_label)) ",object\n"                \
    ".p2align " __xstring(ARC_P2ALIGNMENT) "\n"                           \
__xstring(EFAT_LABEL_DEFN(_label)) ":\n"                                      \
    ".previous\n"                                                            \
       )
#endif

// This macro must be applied to any types whose objects are to be placed in
// tables
#ifndef EFAT_HAL_TABLE_TYPE
#define EFAT_HAL_TABLE_TYPE //BLD_ATTRIB_ALIGN( ARC_ALIGNMENT )
#endif

#ifndef EFAT_HAL_TABLE_EXTRA
#define EFAT_HAL_TABLE_EXTRA( _name ) \
        BLD_ATTRIB_SECTION(".ecos.table." __xstring(_name) ".extra")
#endif

#ifndef EFAT_HAL_TABLE_ENTRY
#define EFAT_HAL_TABLE_ENTRY( _name ) \
        BLD_ATTRIB_SECTION(".ecos.table." __xstring(_name) ".data")
#endif

#ifndef EFAT_HAL_TABLE_QUALIFIED_ENTRY
#define EFAT_HAL_TABLE_QUALIFIED_ENTRY( _name, _qual ) \
        BLD_ATTRIB_SECTION(".ecos.table." __xstring(_name) ".data." \
                              __xstring(_qual))
#endif

/*------------------------------------------------------------------------*/
/* EOF hal_tables.h                                                       */
#endif
#endif // ONCE_HAL_TABLES_H

