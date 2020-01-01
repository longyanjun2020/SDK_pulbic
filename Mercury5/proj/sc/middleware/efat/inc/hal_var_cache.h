#ifndef ONCE_VAR_CACHE_H
#define ONCE_VAR_CACHE_H
////////////////////////////////////////////////////////////////////////////////
///@file hal_var_cache.h
///@author MStar Semiconductor Inc.
///@brief
////////////////////////////////////////////////////////////////////////////////

#include <pkgconf_hal.h>
#include <pkgconf_system.h>
#include <infra_type.h>
#include <hal_mips-regs.h>
//#include <hal_hal_arch.h>
#include <hal_plf_cache.h>
#include <hal_var_arch.h>


//-----------------------------------------------------------------------------
// Cache dimensions

#ifndef HAL_MIPS_MIPS32_KSEG0_CACHE_ENABLE
#define HAL_MIPS_MIPS32_KSEG0_CACHE_ENABLE      3
#endif

#ifndef HAL_MIPS_MIPS32_KSEG0_CACHE_DISABLE
#define HAL_MIPS_MIPS32_KSEG0_CACHE_DISABLE     2
#endif

//-----------------------------------------------------------------------------
// General cache defines.
#ifndef HWR_HAL_MIPS_MIPS32_CORE_M4K
#define HAL_CLEAR_TAGLO()  asm volatile (" mtc0 $0, $28;" ASM_CLEAR_EHB )
#define HAL_CLEAR_TAGHI()  asm volatile (" mtc0 $0, $29;" ASM_CLEAR_EHB )
#else
#define HAL_CLEAR_TAGLO() EFAT_EMPTY_STATEMENT
#define HAL_CLEAR_TAGHI() EFAT_EMPTY_STATEMENT
#endif

#define HAL_CACHE_OP(which, op)             (which | (op << 2))

#define HAL_INDEX_INVALIDATE                0x0
#define HAL_INDEX_LOAD_TAG                  0x1
#define HAL_INDEX_STORE_TAG                 0x2
#define HAL_HIT_INVALIDATE                  0x4

#define HAL_ICACHE_FILL                     0x5
#define HAL_DCACHE_HIT_INVALIDATE           0x5
#define HAL_DCACHE_HIT_WRITEBACK            0x6
#define HAL_FETCH_AND_LOCK                  0x7

#define HAL_WHICH_ICACHE                    0x0
#define HAL_WHICH_DCACHE                    0x1

//-----------------------------------------------------------------------------
// Global control of data cache

#if (defined(HWR_HAL_MIPS_MIPS32_CORE_M4K))

#define HAL_DCACHE_ENABLE_DEFINED
#define HAL_DCACHE_ENABLE() EFAT_EMPTY_STATEMENT

#define HAL_DCACHE_DISABLE_DEFINED
#define HAL_DCACHE_DISABLE() EFAT_EMPTY_STATEMENT

#define HAL_DCACHE_INVALIDATE_ALL_DEFINED
#define HAL_DCACHE_INVALIDATE_ALL() EFAT_EMPTY_STATEMENT

#define HAL_DCACHE_IS_ENABLED_DEFINED
#define HAL_DCACHE_IS_ENABLED(_state_) 0

#define HAL_DCACHE_SYNC_DEFINED
#define HAL_DCACHE_SYNC() EFAT_EMPTY_STATEMENT

#define HAL_DCACHE_LOCK_DEFINED
#define HAL_DCACHE_LOCK(_base_, _asize_) EFAT_EMPTY_STATEMENT

#define HAL_DCACHE_UNLOCK_DEFINED
#define HAL_DCACHE_UNLOCK(_base_, _asize_) EFAT_EMPTY_STATEMENT

#define HAL_DCACHE_UNLOCK_ALL_DEFINED
#define HAL_DCACHE_UNLOCK_ALL() EFAT_EMPTY_STATEMENT

#define HAL_DCACHE_FLUSH_DEFINED
#define HAL_DCACHE_FLUSH( _base_ , _asize_ ) EFAT_EMPTY_STATEMENT

#define HAL_DCACHE_STORE_DEFINED
#define HAL_DCACHE_STORE( _base_ , _asize_ ) EFAT_EMPTY_STATEMENT

#define HAL_DCACHE_INVALIDATE_DEFINED
#define HAL_DCACHE_INVALIDATE( _base_ , _asize_ ) EFAT_EMPTY_STATEMENT

#define HAL_ICACHE_ENABLE_DEFINED
#define HAL_ICACHE_DISABLE_DEFINED
#define HAL_ICACHE_IS_ENABLED_DEFINED
#define HAL_ICACHE_ENABLE()            HAL_DCACHE_ENABLE()
#define HAL_ICACHE_DISABLE()           HAL_DCACHE_DISABLE()
#define HAL_ICACHE_IS_ENABLED(_state_) HAL_DCACHE_IS_ENABLED(_state_)

#define HAL_ICACHE_INVALIDATE_ALL_DEFINED
#define HAL_ICACHE_INVALIDATE_ALL() EFAT_EMPTY_STATEMENT

#define HAL_ICACHE_SYNC_DEFINED
#define HAL_ICACHE_SYNC() EFAT_EMPTY_STATEMENT

#define HAL_ICACHE_LOCK_DEFINED
#define HAL_ICACHE_LOCK(_base_, _asize_) EFAT_EMPTY_STATEMENT

#define HAL_ICACHE_UNLOCK_DEFINED
#define HAL_ICACHE_UNLOCK(_base_, _asize_) EFAT_EMPTY_STATEMENT

#define HAL_ICACHE_UNLOCK_ALL_DEFINED
#define HAL_ICACHE_UNLOCK_ALL() EFAT_EMPTY_STATEMENT

#define HAL_ICACHE_INVALIDATE_DEFINED
#define HAL_ICACHE_INVALIDATE( _base_ , _asize_ ) EFAT_EMPTY_STATEMENT


#else // HWR_HAL_MIPS_MIPS32_CORE_M4K


__externC void hal_dcache_disable( void );
#define HAL_DCACHE_DISABLE_DEFINED
#define HAL_DCACHE_DISABLE() hal_dcache_disable()

__externC void hal_dcache_enable( void );
#define HAL_DCACHE_ENABLE_DEFINED
#define HAL_DCACHE_ENABLE() hal_dcache_enable()

__externC efat_uint32 hal_dcache_is_enabled( void );
#define HAL_DCACHE_IS_ENABLED_DEFINED
#define HAL_DCACHE_IS_ENABLED(_state_) (_state_) = hal_dcache_is_enabled()

#ifndef HAL_DCACHE_SUPPORTS_INDEX_INVALIDATE

// Invalidate the entire cache
__externC void hal_dcache_invalidate_all( void );
#define HAL_DCACHE_INVALIDATE_ALL_DEFINED
#define HAL_DCACHE_INVALIDATE_ALL() hal_dcache_invalidate_all()

// Synchronize the contents of the cache with memory.
__externC void hal_mips32_dcache_sync(void);
#define HAL_DCACHE_SYNC_DEFINED
#define HAL_DCACHE_SYNC() hal_mips32_dcache_sync()
#endif

__externC void hal_dcache_lock( EFAT_ADDRESS base, EFAT_WORD  asize);
#define HAL_DCACHE_LOCK_DEFINED
#define HAL_DCACHE_LOCK(_base_, _asize_) hal_dcache_lock( (EFAT_ADDRESS)_base_, _asize_ )

// Undo a previous lock operation
__externC void hal_dcache_unlock( EFAT_ADDRESS base, EFAT_WORD asize);
#define HAL_DCACHE_UNLOCK_DEFINED
#define HAL_DCACHE_UNLOCK(_base_, _asize_) hal_dcache_unlock( (EFAT_ADDRESS)_base_, _asize_ )

// Unlock entire cache
#define HAL_DCACHE_UNLOCK_ALL_DEFINED
#define HAL_DCACHE_UNLOCK_ALL() HAL_DCACHE_UNLOCK(0,HAL_DCACHE_SIZE)

#define HAL_DCACHE_FLUSH_DEFINED
#if HAL_DCACHE_WRITETHRU_MODE == 1
#define HAL_DCACHE_FLUSH( _base_ , _asize_ ) \
           HAL_DCACHE_INVALIDATE( _base_ , _asize_ )
#elif HAL_DCACHE_WRITEBACK_MODE == 1

#define HAL_DCACHE_FLUSH( _base_ , _asize_ )                                                \
    EFAT_MACRO_START                                                                         \
    register EFAT_ADDRESS _addr_  = HAL_DCACHE_START_ADDRESS((EFAT_ADDRESS)(_base_));         \
    register EFAT_ADDRESS _eaddr_ = HAL_DCACHE_END_ADDRESS((EFAT_ADDRESS)(_base_), _asize_);  \
    for( ; _addr_ < _eaddr_; _addr_ += HAL_DCACHE_LINE_SIZE )                               \
      asm volatile (" cache %0, 0(%1)"                                                      \
                    :                                                                       \
                    : "I" (HAL_CACHE_OP(HAL_WHICH_DCACHE, HAL_DCACHE_HIT_INVALIDATE)),      \
                      "r"(_addr_));                                                         \
    EFAT_MACRO_END
#else

#define HAL_DCACHE_FLUSH( _base_ , _asize_ ) EFAT_MACRO_START EFAT_MACRO_END

#endif

// Write dirty cache lines to memory for the given address range.
#define HAL_DCACHE_STORE_DEFINED
#if HAL_DCACHE_WRITETHRU_MODE == 1
// No need to store a writethrough cache
#define HAL_DCACHE_STORE( _base_ , _asize_ ) EFAT_MACRO_START EFAT_MACRO_END

#elif HAL_DCACHE_WRITEBACK_MODE == 1
// Luke Lee 05/16/2006 ins
#define HAL_DCACHE_STORE(_base_, _asize_)                                               \
    EFAT_MACRO_START                                                                     \
    register EFAT_ADDRESS _baddr_ = (EFAT_ADDRESS)(_base_);                               \
    register EFAT_ADDRESS _addr_ = (EFAT_ADDRESS)(_base_);                                \
    register EFAT_WORD _size_ = (_asize_);                                               \
    for( ; _addr_ <= _baddr_+_size_; _addr_ += HAL_DCACHE_LINE_SIZE )                   \
      asm volatile (" cache %0, 0(%1)"                                                  \
                    :                                                                   \
                    : "I" (HAL_CACHE_OP(HAL_WHICH_DCACHE, HAL_DCACHE_HIT_WRITEBACK)),   \
                      "r"(_addr_));                                                     \
    EFAT_MACRO_END

#else
#define HAL_DCACHE_STORE( _base_ , _asize_ ) EFAT_EMPTY_STATEMENT
#endif

// Invalidate cache lines in the given range without writing to memory.
__externC void hal_dcache_invalidate( EFAT_ADDRESS base , EFAT_WORD asize );
#define HAL_DCACHE_INVALIDATE_DEFINED
#define HAL_DCACHE_INVALIDATE( _base_ , _asize_ ) hal_dcache_invalidate( (EFAT_ADDRESS)_base_, _asize_ )


//-----------------------------------------------------------------------------
// Global control of Instruction cache

// We can only enable/disable cacheability for a region, and not choose what type,
// so in line with the way UCACHE macros work, we just map to the DCACHE ones.
#define HAL_ICACHE_ENABLE_DEFINED
#define HAL_ICACHE_DISABLE_DEFINED
#define HAL_ICACHE_IS_ENABLED_DEFINED
#define HAL_ICACHE_ENABLE()            HAL_DCACHE_ENABLE()
#define HAL_ICACHE_DISABLE()           HAL_DCACHE_DISABLE()
#define HAL_ICACHE_IS_ENABLED(_state_) HAL_DCACHE_IS_ENABLED(_state_)

#ifndef HAL_ICACHE_SUPPORTS_INDEX_INVALIDATE

// Invalidate the entire cache
__externC void hal_icache_invalidate_all( void );
#define HAL_ICACHE_INVALIDATE_ALL_DEFINED
#define HAL_ICACHE_INVALIDATE_ALL() hal_icache_invalidate_all()

// Synchronize the contents of the cache with memory.
__externC void hal_icache_sync(void);
#define HAL_ICACHE_SYNC_DEFINED
#define HAL_ICACHE_SYNC() hal_icache_sync()
#endif

__externC void hal_icache_lock( EFAT_ADDRESS base, EFAT_WORD asize);
#define HAL_ICACHE_LOCK_DEFINED
#define HAL_ICACHE_LOCK(_base_, _asize_) hal_icache_lock( (EFAT_ADDRESS)_base_, _asize_ )

// Undo a previous lock operation
__externC void hal_icache_unlock( EFAT_ADDRESS base, EFAT_WORD asize);
#define HAL_ICACHE_UNLOCK_DEFINED
#define HAL_ICACHE_UNLOCK(_base_, _asize_) hal_icache_unlock( (EFAT_ADDRESS)_base_, _asize_ )

// Unlock entire cache
#define HAL_ICACHE_UNLOCK_ALL_DEFINED
#define HAL_ICACHE_UNLOCK_ALL() HAL_ICACHE_UNLOCK(0,HAL_ICACHE_SIZE)

//-----------------------------------------------------------------------------
// Instruction cache line control

// Invalidate cache lines in the given range without writing to memory.
__externC void hal_icache_invalidate( EFAT_ADDRESS base , EFAT_WORD asize );
#define HAL_ICACHE_INVALIDATE_DEFINED
#define HAL_ICACHE_INVALIDATE( _base_ , _asize_ ) hal_icache_invalidate( (EFAT_ADDRESS)_base_, _asize_ )

#endif // HWR_HAL_MIPS_MIPS32_CORE_M4K

//-----------------------------------------------------------------------------
#endif // ifndef ONCE_VAR_CACHE_H
// End of var_cache.h
