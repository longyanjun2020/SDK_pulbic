#ifndef CRC_H
#define CRC_H

#include <stdint.h>

void ConstructCRC8Tab(void);
int getCRC8(uint8_t *data, int len);

#endif // CRC_H
