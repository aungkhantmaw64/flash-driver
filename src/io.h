#ifndef D_IO_H
#define D_IO_H

#include <stdint.h>

typedef uint32_t ioAddress;
typedef uint16_t ioData;

/**
 * @brief
 *
 * @param addr
 * @return ioData
 */
ioData uxIORead(ioAddress addr);

/**
 * @brief
 *
 * @param addr
 * @param data
 */
void vIOWrite(ioAddress addr, ioData data);

#endif