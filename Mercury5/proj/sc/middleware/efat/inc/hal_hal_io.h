#ifndef ONCE_HAL_HAL_IO_H
#define ONCE_HAL_HAL_IO_H
////////////////////////////////////////////////////////////////////////////////
///@file hal_io.h
///@author MStar Semiconductor Inc.
///@brief
////////////////////////////////////////////////////////////////////////////////

#include <pkgconf_hal.h>
#include <infra_type.h>
#include <hal_plf_io.h>

//-----------------------------------------------------------------------------
typedef volatile EFAT_ADDRWORD HAL_IO_REGISTER;

//-----------------------------------------------------------------------------
#ifndef HAL_MEMORY_BARRIER_DEFINED
#define HAL_MEMORY_BARRIER() __asm__ volatile ("sync;")
#endif

#ifndef HAL_IO_BARRIER_DEFINED
#define HAL_IO_BARRIER() HAL_MEMORY_BARRIER()
#endif

//-----------------------------------------------------------------------------
// HAL IO macros.
#ifndef HAL_IO_MACROS_DEFINED

//-----------------------------------------------------------------------------


#define HAL_WRITE_UINT8( _register_, _value_ ) (*((volatile EFAT_BYTE *)(_register_)) = (_value_))
#define HAL_READ_UINT8( _register_, _value_ ) ((_value_) = *((volatile EFAT_BYTE *)(_register_)))

#define HAL_WRITE_UINT8_VECTOR( _register_, _buf_, _count_, _step_ )    \
    EFAT_MACRO_START                                                     \
    efat_count32 _i_,_j_;                                                \
    for( _i_ = 0, _j_ = 0; _i_ < (_count_); _i_++, _j_ += (_step_))     \
        ((volatile EFAT_BYTE *)(_register_))[_j_] = (_buf_)[_i_];        \
    EFAT_MACRO_END

#define HAL_READ_UINT8_VECTOR( _register_, _buf_, _count_, _step_ )     \
        EFAT_MACRO_START                                                     \
        efat_count32 _i_,_j_;                                                \
        for( _i_ = 0, _j_ = 0; _i_ < (_count_); _i_++, _j_ += (_step_))     \
            (_buf_)[_i_] = ((volatile EFAT_BYTE *)(_register_))[_j_];        \
        EFAT_MACRO_END

//-----------------------------------------------------------------------------
#define HAL_WRITE_UINT16( _register_, _value_ ) (*((volatile EFAT_WORD16 *)(_register_)) = (_value_))
#define HAL_READ_UINT16( _register_, _value_ ) ((_value_) = *((volatile EFAT_WORD16 *)(_register_)))

#define HAL_WRITE_UINT16_VECTOR( _register_, _buf_, _count_, _step_ )   \
    EFAT_MACRO_START                                                     \
    efat_count32 _i_,_j_;                                                \
    for( _i_ = 0, _j_ = 0; _i_ < (_count_); _i_++, _j_ += (_step_))     \
        ((volatile EFAT_WORD16 *)(_register_))[_j_] = (_buf_)[_i_];      \
    EFAT_MACRO_END
    
#define HAL_READ_UINT16_VECTOR( _register_, _buf_, _count_, _step_ )    \
            EFAT_MACRO_START                                                     \
            efat_count32 _i_,_j_;                                                \
            for( _i_ = 0, _j_ = 0; _i_ < (_count_); _i_++, _j_ += (_step_))     \
                (_buf_)[_i_] = ((volatile EFAT_WORD16 *)(_register_))[_j_];      \
            EFAT_MACRO_END

//-----------------------------------------------------------------------------
#define HAL_WRITE_UINT32( _register_, _value_ ) (*((volatile EFAT_WORD32 *)(_register_)) = (_value_))
#define HAL_READ_UINT32( _register_, _value_ ) ((_value_) = *((volatile EFAT_WORD32 *)(_register_)))

#define HAL_WRITE_UINT32_VECTOR( _register_, _buf_, _count_, _step_ )   \
    EFAT_MACRO_START                                                     \
    efat_count32 _i_,_j_;                                                \
    for( _i_ = 0, _j_ = 0; _i_ < (_count_); _i_++, _j_ += (_step_))     \
        ((volatile EFAT_WORD32 *)(_register_))[_j_] = (_buf_)[_i_];      \
    EFAT_MACRO_END

#define HAL_READ_UINT32_VECTOR( _register_, _buf_, _count_, _step_ )    \
        EFAT_MACRO_START                                                     \
        efat_count32 _i_,_j_;                                                \
        for( _i_ = 0, _j_ = 0; _i_ < (_count_); _i_++, _j_ += (_step_))     \
            (_buf_)[_i_] = ((volatile EFAT_WORD32 *)(_register_))[_j_];      \
        EFAT_MACRO_END

#define HAL_IO_MACROS_DEFINED

#endif


//-----------------------------------------------------------------------------
#endif // ifndef ONCE_HAL_HAL_IO_H
// End of hal_io.h
