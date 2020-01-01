#ifndef ONCE_DISK_H
#define ONCE_DISK_H
////////////////////////////////////////////////////////////////////////////////
///@file io_disk.c
///@author MStar Semiconductor Inc.
///@brief
////////////////////////////////////////////////////////////////////////////////

#include <pkgconf_system.h>
#include <pkgconf_io_disk.h>
#include <infra_type.h>
#include <io_devtab.h>
#include <io_io.h>
#include <hal_drv_api.h>
#include <string.h> /* memset() */

// ---------------------------------------------------------------------------

typedef struct efat_disk_partition_t efat_disk_partition_t;
typedef struct efat_disk_info_t efat_disk_info_t;
typedef struct efat_disk_identify_t efat_disk_identify_t;
#if 0
typedef struct disk_channel    disk_channel;
typedef struct disk_controller disk_controller;
typedef struct disk_funs       disk_funs;
#endif
// ---------------------------------------------------------------------------
#if 0
// Pointers into upper-level driver
typedef struct {

    // Initialize the disk
    efat_bool (*disk_init)(struct efat_devtab_entry *tab);

    // Disk device has been connected
    Efat_ErrNo (*disk_connected)(struct efat_devtab_entry *tab,
                                efat_disk_identify_t     *ident);

    // Disk device has been disconnected
    Efat_ErrNo (*disk_disconnected)(struct disk_channel *chan);

    // Lookup disk device
    Efat_ErrNo (*disk_lookup)(struct efat_devtab_entry **tab,
                             struct efat_devtab_entry  *sub_tab,
                             const char               *name);

    // Asynchronous block transfer done
    void (*disk_transfer_done)(struct disk_channel *chan, Efat_ErrNo res);

} disk_callbacks_t;

#define DISK_CALLBACKS(_l,                      \
                       _init,                   \
                       _connected,              \
                       _disconnected,           \
                       _lookup,                 \
                       _transfer_done)          \
disk_callbacks_t _l = {                         \
    _init,                                      \
    _connected,                                 \
    _disconnected,                              \
    _lookup,                                    \
    _transfer_done                              \
};

extern disk_callbacks_t efat_io_disk_callbacks;
#endif
// ---------------------------------------------------------------------------
// Private data which describes a disk controller
#if 0
struct disk_controller {
    efat_drv_mutex_t     lock;           // Per-controller lock
    efat_drv_cond_t      queue;          // Access wait list
    efat_drv_cond_t      async;          // Async transfer waits here
    void                *priv;          // Private data
    volatile Efat_ErrNo  result;         // Last operation result
    efat_bool            init;           // Initialized?
    volatile efat_bool   busy;           // Busy?
};

#define DISK_CONTROLLER(_l, _priv)              \
disk_controller _l = {                          \
    priv:       &_priv,                         \
    init:       false,                          \
    busy:       false                           \
}
#endif
// ---------------------------------------------------------------------------
// Private data which describes this channel
#if 0
struct disk_channel {
    disk_funs               *funs;
    disk_callbacks_t        *callbacks;
    void                    *dev_priv;    // device private data
    disk_controller         *controller;  // pointer to controller
    efat_disk_info_t         *info;        // disk info
    efat_disk_partition_t    *partition;   // partition data
    efat_bool                 mbr_support; // true if disk has MBR
    efat_bool                 valid;       // true if device valid
    efat_bool                 init;        // true if initialized
    efat_ucount16             mounts;      // count of number of mounts
};

// Initialization macro for disk channel
#define DISK_CHANNEL(_l,                        \
                     _funs,                     \
                     _dev_priv,                 \
                     _controller,               \
                     _mbr_supp)                 \
efat_disk_info_t _l##_disk_info;                 \
disk_channel _l = {                             \
    &(_funs),                                   \
    &efat_io_disk_callbacks,                     \
    &(_dev_priv),                               \
    &(_controller),                             \
    &(_l##_disk_info),                          \
    NULL,                                       \
    _mbr_supp,                                  \
    false,                                      \
    false,                                      \
    0                                           \
};

// Initialization macro for disk channel allocated elsewhere.
#define DISK_CHANNEL_INIT(_dc,                  \
                     _funs,                     \
                     _dev_priv,                 \
                     _controller,               \
                     _disk_info,                \
                     _mbr_supp)                 \
    EFAT_MACRO_START                             \
    memset((_disk_info), 0, sizeof(efat_disk_info_t)); \
    (_dc).funs = &(_funs);                      \
    (_dc).callbacks = &efat_io_disk_callbacks;   \
    (_dc).dev_priv = (_dev_priv);               \
    (_dc).controller = &(_controller);          \
    (_dc).info = &(_disk_info);                 \
    (_dc).partition = NULL;                     \
    (_dc).mbr_support = (_mbr_supp);            \
    (_dc).valid = false;                        \
    (_dc).init = false;                         \
    (_dc).mounts = 0;                           \
    EFAT_MACRO_END
#endif
// ---------------------------------------------------------------------------
// Low level interface functions
#if 0

struct disk_funs {

    // Read block data into buf
    Efat_ErrNo (*read)(disk_channel *priv,
                        void         *buf,
                        efat_uint32    len,
                        efat_uint32    block_num);

    // Write block data from buf
    Efat_ErrNo (*write)(disk_channel *priv,
                        const void   *buf,
                        efat_uint32    len,
                        efat_uint32    block_num);

    // Get hardware configuration
    Efat_ErrNo (*get_config)(disk_channel *priv,
                            efat_uint32    key,
                            const void   *xbuf,
                            efat_uint32   *len);

    // Set hardware configuration
    Efat_ErrNo (*set_config)(disk_channel *priv,
                            efat_uint32    key,
                            const void   *xbuf,
                            efat_uint32   *len);
};
#define DISK_FUNS(_l,_read,_write,_get_config,_set_config)           \
disk_funs _l = {                                                     \
  _read,                                                             \
  _write,                                                            \
  _get_config,                                                       \
  _set_config                                                        \
};
#endif
extern efat_devio_table_t efat_io_disk_devio;

// ---------------------------------------------------------------------------

#include <io_diskio.h>

// ---------------------------------------------------------------------------
#endif // ONCE_DISK_H
