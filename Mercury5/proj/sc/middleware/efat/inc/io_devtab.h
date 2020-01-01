#ifndef ONCE_IO_DEVTAB_H
#define ONCE_IO_DEVTAB_H
////////////////////////////////////////////////////////////////////////////////
///@file io_devtab.c
///@author MStar Semiconductor Inc.
///@brief
////////////////////////////////////////////////////////////////////////////////

#include <pkgconf_system.h>
#include <io_io.h>
#include <hal_drv_api.h>
#include <hal_hal_tables.h>

// Set of functions which handle top level I/O functions
typedef struct {
    Efat_ErrNo (*write)(efat_io_handle_t handle,
                       const void *buf,
                       efat_uint32 *len);
    Efat_ErrNo (*read)(efat_io_handle_t handle,
                      void *buf,
                      efat_uint32 *len);
    Efat_ErrNo (*bwrite)(efat_io_handle_t handle,
                       const void *buf,
                       efat_uint32 *len,
                       efat_uint32 pos);
    Efat_ErrNo (*bread)(efat_io_handle_t handle,
                      void *buf,
                      efat_uint32 *len,
                      efat_uint32 pos);
    efat_bool  (*select)(efat_io_handle_t handle,
                        efat_uint32 which,
                        EFAT_ADDRWORD info);
    Efat_ErrNo (*get_config)(efat_io_handle_t handle,
                            efat_uint32 key,
                            void *buf,
                            efat_uint32 *len);
    Efat_ErrNo (*set_config)(efat_io_handle_t handle,
                            efat_uint32 key,
                            const void *buf,
                            efat_uint32 *len);
} efat_devio_table_t;


// Default functions

__externC Efat_ErrNo efat_devio_cwrite(efat_io_handle_t handle,
                                     const void *buf, efat_uint32 *len);
__externC Efat_ErrNo efat_devio_cread(efat_io_handle_t handle,
                                    void *buf, efat_uint32 *len);

__externC Efat_ErrNo efat_devio_select(efat_io_handle_t handle,
                                     efat_uint32 which,
                                     EFAT_ADDRWORD info);

__externC Efat_ErrNo efat_devio_get_config(efat_io_handle_t handle,
                                         efat_uint32 key,
                                         void* buf,
                                         efat_uint32* len);

__externC Efat_ErrNo efat_devio_set_config(efat_io_handle_t handle,
                                         efat_uint32 key,
                                         void* buf,
                                         efat_uint32* len);

__externC Efat_ErrNo efat_devio_bwrite(efat_io_handle_t handle,
                                     const void *buf, efat_uint32 *len,
                                     efat_uint32 pos);
__externC Efat_ErrNo efat_devio_bread(efat_io_handle_t handle,
                                    void *buf, efat_uint32 *len,
                                    efat_uint32 pos);



// Initialization macros



#define BLOCK_DEVIO_TABLE(_l,_bwrite,_bread,_select,_get_config,_set_config)    \
efat_devio_table_t _l = {                                        \
    efat_devio_cwrite,                                           \
    efat_devio_cread,                                            \
    _bwrite,                                                    \
    _bread,                                                     \
    _select,                                                    \
    _get_config,                                                \
    _set_config,                                                \
};

#define CHAR_DEVIO_TABLE(_l,_write,_read,_select,_get_config,_set_config)    \
efat_devio_table_t _l = {                                        \
    _write,                                                     \
    _read,                                                      \
    efat_devio_bwrite,                                           \
    efat_devio_bread,                                            \
    _select,                                                    \
    _get_config,                                                \
    _set_config,                                                \
};

#define DEVIO_TABLE(_l,_write,_read,_select,_get_config,_set_config) CHAR_DEVIO_TABLE(_l,_write,_read,_select,_get_config,_set_config)

#define EFAT_DEVTAB_STATUS_AVAIL   0x0001
#define EFAT_DEVTAB_STATUS_CHAR    0x1000
#define EFAT_DEVTAB_STATUS_BLOCK   0x2000

typedef struct efat_devtab_entry {
    const char        *name;
    const char        *dep_name;
    efat_devio_table_t *handlers;
    efat_bool          (*init)(struct efat_devtab_entry *tab);
    Efat_ErrNo        (*lookup)(struct efat_devtab_entry **tab,
                               struct efat_devtab_entry *sub_tab,
                               const char *name);
    void              *priv;
    unsigned long     status;
    efat_uint32        MBR_offset;
} EFAT_HAL_TABLE_TYPE efat_devtab_entry_t;


extern efat_devtab_entry_t __DEVTAB__[], __DEVTAB_END__;

#define BLOCK_DEVTAB_ENTRY(_l,_name,_dep_name,_handlers,_init,_lookup,_priv)  \
efat_devtab_entry_t _l EFAT_HAL_TABLE_ENTRY(devtab) = {                   \
   _name,                                                               \
   _dep_name,                                                           \
   _handlers,                                                           \
   _init,                                                               \
   _lookup,                                                             \
   _priv,                                                               \
   EFAT_DEVTAB_STATUS_BLOCK                                              \
};

#define CHAR_DEVTAB_ENTRY(_l,_name,_dep_name,_handlers,_init,_lookup,_priv)  \
efat_devtab_entry_t _l EFAT_HAL_TABLE_ENTRY(devtab) = {                   \
   _name,                                                               \
   _dep_name,                                                           \
   _handlers,                                                           \
   _init,                                                               \
   _lookup,                                                             \
   _priv,                                                               \
   EFAT_DEVTAB_STATUS_CHAR                                               \
};

#define DEVTAB_ENTRY_NO_INIT(_l,_name,_dep_name,_handlers,_init,_lookup,_priv)  \
efat_devtab_entry_t _l = {                                                       \
   _name,                                                                       \
   _dep_name,                                                                   \
   _handlers,                                                                   \
   _init,                                                                       \
   _lookup,                                                                     \
   _priv,                                                                       \
   EFAT_DEVTAB_STATUS_CHAR                                                       \
};

#define DEVTAB_ENTRY(_l,_name,_dep_name,_handlers,_init,_lookup,_priv) CHAR_DEVTAB_ENTRY(_l,_name,_dep_name,_handlers,_init,_lookup,_priv)

#endif // ONCE_IO_DEVTAB_H
