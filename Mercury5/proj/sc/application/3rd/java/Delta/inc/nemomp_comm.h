#ifndef __NEMOMP_COMM_H__
#define __NEMOMP_COMM_H__

#include "nemomp.h"

extern int nemomp_comm_open(int port, int baudRate);
extern int nemomp_comm_close(int handle);
extern void nemomp_comm_config(int osHandle, int baudrate, int bitsPerChar, int stopBits, int parity, nm_bool autoRTS, nm_bool autoCTS);
extern int nemomp_comm_read(int handle, char* buffer, int len);
extern int nemomp_comm_write(int handle, char* buffer, int len);
extern int nemomp_comm_available(int handle);
extern int nemomp_comm_get_default_port(void);
extern void nemomp_set_baud(int handle, int baudrate);

#endif /* __NEMOMP_COMM_H__ */
