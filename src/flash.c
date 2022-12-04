#include "flash.h"

int xFlashWrite(ioAddress offset, ioData data)
{
    ioData status;
    vIOWrite(0, 0x40);
    vIOWrite(offset, data);
    status = uxIORead(0x0);
    uxIORead(offset);
    if (status == (1 << 7))
    {
        return FLASH_SUCCESS;
    }
    else
    {
        return -1;
    }
}