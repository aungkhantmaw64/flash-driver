#include "flash.h"
#include "m28W160ecx.h"

int xFlashWrite(ioAddress offset, ioData data)
{
    ioData status = 0;
    vIOWrite(CommandRegister, ProgramCommand);
    vIOWrite(offset, data);
    while ((status & ReadyBit) == 0)
    {
        status = uxIORead(StatusRegister);
    }
    if (status != ReadyBit)
    {
        vIOWrite(CommandRegister, Reset);

        if (status & VppErrorBit)
        {
            return FLASH_VPP_ERROR;
        }
        else if (status & ProgramErrorBit)
        {
            return FLASH_PROGRAM_ERROR;
        }
        else if (status & ProtectedBlockErrorBit)
        {
            return FLASH_PROTECTED_BLOCK_ERROR;
        }
    }
    if (uxIORead(offset) != data)
    {
        return FLASH_READ_BACK_ERROR;
    }
    return FLASH_SUCCESS;
}