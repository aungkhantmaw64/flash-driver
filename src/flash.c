#include "flash.h"
#include "m28W160ecx.h"
#include "micro_time.h"

#define FLASH_WRITE_TIMEOUT_IN_MICROSECONDS 5000

// Private helper functions
static int prvWriteError(ioData status)
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

int xFlashWrite(ioAddress offset, ioData data)
{
    ioData status = 0;
    uint32_t timestamp = ulMicroTimeGet();
    vIOWrite(CommandRegister, ProgramCommand);
    vIOWrite(offset, data);
    status = uxIORead(StatusRegister);
    while ((status & ReadyBit) == 0)
    {
        if ((ulMicroTimeGet() - timestamp) >= FLASH_WRITE_TIMEOUT_IN_MICROSECONDS)
            return FLASH_TIMEOUT_ERROR;
        status = uxIORead(StatusRegister);
    }
    if (status != ReadyBit)
    {
        return prvWriteError(status);
    }
    if (uxIORead(offset) != data)
    {
        return FLASH_READ_BACK_ERROR;
    }
    else
    {
        return FLASH_SUCCESS;
    }
}