#ifndef ONCE_KERNEL_KTYPES_H
#define ONCE_KERNEL_KTYPES_H

///////////////////////////////////////////////////////////////////////////////////////////////////
/// @file   kernel_ktypes.h
/// @author MStar Semiconductor Inc.
/// @brief  video application header file
///////////////////////////////////////////////////////////////////////////////////////////////////


#ifndef ONCE_PKGCONF_KERNEL_H
//#error "No Configuration file included"
#endif

// -------------------------------------------------------------------------
#include <infra_type.h>
#include <stddef.h>              // for size_t

// -------------------------------------------------------------------------
// Integer types:

typedef efat_uint32      efat_vector;     // vector number/descriptor

typedef efat_uint64      efat_tick_count; // clock tick count value

typedef efat_int32       efat_code;       // General return/error/status code

typedef efat_count32     efat_priority;   // priority value


// -------------------------------------------------------------------------

#define EFAT_CLASSFROMFIELD(_type_,_member_,_ptr_)\
    ((_type_ *)((char *)(_ptr_)-((char *)&(((_type_ *)0)->_member_))))

#ifdef __cplusplus

#define EFAT_OFFSETOFBASE(_type_,_base_)\
    ((char *)((_base_ *)((_type_ *)4)) - (char *)4)

# define EFAT_CLASSFROMBASE(_class_,_base_,_ptr_)\
    ((_class_ *)((char *)(_ptr_) - EFAT_OFFSETOFBASE(_class_,_base_)))

#endif

// -------------------------------------------------------------------------
#endif // ONCE_KERNEL_KTYPES_H
// EOF ktypes.h

