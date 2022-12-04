
#include "unity.h"
#include "flash.h"
#include "mock_io.h"
#include "m28W160ecx.h"

static ioAddress address;
static ioData data;

void setUp(void)
{
    mock_io_Init();
    address = 0x1000;
    data = 0xBEEF;
}

void tearDown(void)
{
    mock_io_Verify();
    mock_io_Destroy();
}

void test_WriteSucceeds_ReadyImmediately()
{
    int result = 0;
    vIOWrite_Expect(CommandRegister, ProgramCommand);
    vIOWrite_Expect(address, data);
    uxIORead_ExpectAndReturn(StatusRegister, 1 << 7);
    uxIORead_ExpectAndReturn(address, data);

    result = xFlashWrite(address, data);

    TEST_ASSERT_EQUAL_INT8(0, result);
}