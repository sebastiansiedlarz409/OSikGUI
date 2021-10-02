#include "common.h"
#include <stdint.h>

void KERN_Welcome(void* kernelEntryPointAddress, void* stackAddress)
{
    uint64_t KEPAddr = (uint64_t)kernelEntryPointAddress;
    uint64_t SAddr = (uint64_t)stackAddress;
}

void KERN_Start(void* kernelEntryPointAddress, void* stackAddress)
{
    for(;;);
}