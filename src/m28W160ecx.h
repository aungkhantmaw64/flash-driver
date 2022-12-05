#ifndef D_M28W160ECX_H
#define D_M28W160ECX_H

#define BIT(x) (1 << x)

typedef enum
{
    CommandRegister = 0x0,
    StatusRegister = 0x0
} FlashRegisters;

typedef enum
{
    ProgramCommand = 0x40,
    Reset = 0xff
} FlashCommands;

typedef enum
{
    ReadyBit = BIT(7),
    VppErrorBit = BIT(3),
    ProgramErrorBit = BIT(4),
    ProtectedBlockErrorBit = BIT(1)
} StatusRegisterBits;

#endif