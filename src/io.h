#ifndef D_IO_H
#define D_IO_H

#include <stdint.h>

typedef uint32_t ioAddress;
typedef uint16_t ioData;

ioData uxIORead(ioAddress addr);
void vIOWrite(ioAddress addr, ioData data);

#endif