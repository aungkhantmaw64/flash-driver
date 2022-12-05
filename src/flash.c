#include "flash.h"
#include "m28W160ecx.h"

int xFlashWrite(ioAddress offset, ioData data)
{
    ioData status;
    vIOWrite(CommandRegister, ProgramCommand);
    vIOWrite(offset, data);
    while ((status & ReadyBit) == 0)
    {
        status = uxIORead(StatusRegister);
    }
    uxIORead(offset);
    return FLASH_SUCCESS;
}