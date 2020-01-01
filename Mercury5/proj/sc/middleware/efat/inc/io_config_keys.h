#ifndef ONCE_CONFIG_KEYS_H
#define ONCE_CONFIG_KEYS_H
////////////////////////////////////////////////////////////////////////////////
///@file io_config_keys.h
///@author MStar Semiconductor Inc.
///@brief
////////////////////////////////////////////////////////////////////////////////


// ======== 0x0300 DSP =======================================================
#define EFAT_IO_GET_CONFIG_DSP_OUTPUT_DRAIN       0x0301
#define EFAT_IO_GET_CONFIG_DSP_OUTPUT_FLUSH       0x0302
#define EFAT_IO_GET_CONFIG_DSP_INPUT_FLUSH        0x0303
#define EFAT_IO_GET_CONFIG_DSP_ABORT              0x0304
#define EFAT_IO_GET_CONFIG_DSP_INPUT_OVERFLOW_RESET 0x0307


// ======== 0x700 DISK =======================================================

#define EFAT_IO_GET_CONFIG_DISK_INFO              0x700

#define EFAT_IO_SET_CONFIG_DISK_MOUNT             0x781
#define EFAT_IO_SET_CONFIG_DISK_UMOUNT            0x782

// ======== 0x600 FLASH =====================================================

#define EFAT_IO_GET_CONFIG_FLASH_ERASE            0x600
#define EFAT_IO_GET_CONFIG_FLASH_QUERY            0x601
#define EFAT_IO_GET_CONFIG_FLASH_LOCK             0x602
#define EFAT_IO_GET_CONFIG_FLASH_UNLOCK           0x603
#define EFAT_IO_GET_CONFIG_FLASH_VERIFY           0x604
#define EFAT_IO_GET_CONFIG_FLASH_DEVSIZE          0x605
#define EFAT_IO_GET_CONFIG_FLASH_BLOCKSIZE        0x606

#define EFAT_IO_SET_CONFIG_FLASH_FIS_NAME         0x680

// ======== 0x400 DSP =======================================================
#define EFAT_IO_GET_CONFIG_TERMIOS                0x0400
#define EFAT_IO_SET_CONFIG_TERMIOS                0x0401

// ======== 0x1000 Generic ===================================================

#define EFAT_IO_GET_CONFIG_READ_BLOCKING         0x1001
#define EFAT_IO_GET_CONFIG_WRITE_BLOCKING        0x1002

#define EFAT_IO_SET_CONFIG_READ_BLOCKING         0x1081
#define EFAT_IO_SET_CONFIG_WRITE_BLOCKING        0x1082

#define EFAT_IO_GET_CONFIG_DSP_READ_BLOCKING      EFAT_IO_GET_CONFIG_READ_BLOCKING
#define EFAT_IO_GET_CONFIG_DSP_WRITE_BLOCKING     EFAT_IO_GET_CONFIG_WRITE_BLOCKING
#define EFAT_IO_SET_CONFIG_DSP_READ_BLOCKING      EFAT_IO_SET_CONFIG_READ_BLOCKING
#define EFAT_IO_SET_CONFIG_DSP_WRITE_BLOCKING     EFAT_IO_SET_CONFIG_WRITE_BLOCKING

#define EFAT_IO_SET_CONFIG_CLOSE                 0x1100

// ======== 0x0200 TTY =======================================================

#define EFAT_IO_GET_CONFIG_SERIAL_ABORT                 0x0105
#define EFAT_IO_GET_CONFIG_SERIAL_BUFFER_INFO           0x0111
#define EFAT_IO_GET_CONFIG_SERIAL_FLOW_CONTROL_METHOD   0x0112

//separate
#define EFAT_IO_SET_CONFIG_SERIAL_FLOW_CONTROL_FORCE    0x0187
#define EFAT_IO_SET_CONFIG_SERIAL_STATUS_CALLBACK       0x0188
#define EFAT_IO_SET_CONFIG_SERIAL_HW_BREAK              0x0189


// ======== 0x0200 TTY =======================================================
#define EFAT_IO_GET_CONFIG_TTY_INFO       0x0201
#define EFAT_IO_SET_CONFIG_TTY_INFO       0x0281

//separate
#define EFAT_IO_SET_CONFIG_SERIAL_INFO                  0x0181
#define EFAT_IO_SET_CONFIG_SERIAL_HW_RX_FLOW_THROTTLE   0x0184
#define EFAT_IO_SET_CONFIG_SERIAL_HW_FLOW_CONFIG        0x0185
#define EFAT_IO_SET_CONFIG_SERIAL_FLOW_CONTROL_METHOD   0x0186



//separate

#define EFAT_IO_GET_CONFIG_SERIAL_INFO                  0x0101
#define EFAT_IO_GET_CONFIG_SERIAL_OUTPUT_DRAIN          0x0102
#define EFAT_IO_GET_CONFIG_SERIAL_OUTPUT_FLUSH          0x0103
#define EFAT_IO_SET_CONFIG_SERIAL_OUTPUT_FLUSH          EFAT_IO_GET_CONFIG_SERIAL_OUTPUT_FLUSH
#define EFAT_IO_GET_CONFIG_SERIAL_INPUT_FLUSH           0x0104
#define EFAT_IO_SET_CONFIG_SERIAL_INPUT_FLUSH           EFAT_IO_GET_CONFIG_SERIAL_INPUT_FLUSH


#endif  /* ONCE_CONFIG_KEYS_H */
/* EOF config_keys.h */
