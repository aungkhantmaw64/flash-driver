
#include "unity.h"
#include "flash.h"
#include "mock_io.h"
#include "m28W160ecx.h"

static ioAddress address;
static ioData data;
static int result;

void setUp(void)
{
    mock_io_Init();
    address = 0x1000;
    data = 0xBEEF;
    result = -1;
}

void tearDown(void)
{
    mock_io_Verify();
    mock_io_Destroy();
}

void test_WriteSucceeds_ReadyImmediately(void)
{

    vIOWrite_Expect(CommandRegister, ProgramCommand);
    vIOWrite_Expect(address, data);
    uxIORead_ExpectAndReturn(StatusRegister, ReadyBit);
    uxIORead_ExpectAndReturn(address, data);

    result = xFlashWrite(address, data);

    TEST_ASSERT_EQUAL_INT8(FLASH_SUCCESS, result);
}

void test_ProgramSucceeds_NotImmediatelyReady(void)
{

    vIOWrite_Expect(CommandRegister, ProgramCommand);
    vIOWrite_Expect(address, data);
    for (int i = 0; i < 3; i++)
    {
        uxIORead_ExpectAndReturn(StatusRegister, 0);
    }
    uxIORead_ExpectAndReturn(StatusRegister, ReadyBit);
    uxIORead_ExpectAndReturn(address, data);

    result = xFlashWrite(address, data);

    TEST_ASSERT_EQUAL_INT8(FLASH_SUCCESS, result);
}

void test_WriteFails_VppError(void)
{
    vIOWrite_Expect(CommandRegister, ProgramCommand);
    vIOWrite_Expect(address, data);
    uxIORead_ExpectAndReturn(StatusRegister, ReadyBit | VppErrorBit);
    vIOWrite_Expect(CommandRegister, Reset);

    result = xFlashWrite(address, data);

    TEST_ASSERT_EQUAL_INT8(FLASH_VPP_ERROR, result);
}

void test_WriteFails_ProgramError(void)
{
    vIOWrite_Expect(CommandRegister, ProgramCommand);
    vIOWrite_Expect(address, data);
    uxIORead_ExpectAndReturn(StatusRegister, ReadyBit | ProgramErrorBit);
    vIOWrite_Expect(CommandRegister, Reset);

    result = xFlashWrite(address, data);

    TEST_ASSERT_EQUAL_INT8(FLASH_PROGRAM_ERROR, result);
}

void test_WriteFails_ProtectedBlockError(void)
{
    vIOWrite_Expect(CommandRegister, ProgramCommand);
    vIOWrite_Expect(address, data);
    uxIORead_ExpectAndReturn(StatusRegister, ReadyBit | ProtectedBlockErrorBit);
    vIOWrite_Expect(CommandRegister, Reset);

    result = xFlashWrite(address, data);

    TEST_ASSERT_EQUAL_INT8(FLASH_PROTECTED_BLOCK_ERROR, result);
}