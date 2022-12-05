#include "fake_micro_time.h"

static uint32_t time;
static uint32_t increment;

void vFakeMicroTimeInit(uint32_t start, uint32_t inc)
{
    time = start;
    increment = inc;
}

uint32_t ulMicroTimeGet(void)
{
    uint32_t t = time;
    time += increment;
    return t;
}