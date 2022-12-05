#ifndef D_FLASH_H
#define D_FLASH_H

#include "io.h"

/**
 * @brief
 *
 */
typedef enum
{
    FLASH_SUCCESS = 0,
    FLASH_VPP_ERROR,
    FLASH_PROGRAM_ERROR,
    FLASH_PROTECTED_BLOCK_ERROR,
    FLASH_UNKNOWN_PROGRAM_ERROR,
    FLASH_READ_BACK_ERROR,
    FLASH_TIMEOUT_ERROR
} FlashStatusType_t;

/**
 * @brief
 *
 */
void vFlashCreate(void);

/**
 * @brief
 *
 */
void vFlashDestroy(void);

/**
 * @brief
 *
 * @param offset
 * @param data
 * @return int
 */
int xFlashWrite(ioAddress offset, ioData data);

#endif