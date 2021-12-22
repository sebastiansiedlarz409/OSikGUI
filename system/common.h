#pragma once

#include <stdint.h>

#include "windows.h"

typedef struct _SystemContext{
    uint64_t kernelAddress;
    uint64_t stackAddress;
    uint64_t heapSize;
    uint64_t heapAddress;
    uint64_t heapNextFree;
    uint8_t window;
    uint8_t windowsCount;
    WindowContext* mainWindow;
} SystemContext;

#define UNUSED(x) (void)(x)
typedef unsigned long long size_t;

SystemContext* GetSystemContext(void);
int32_t isqrt(int32_t num);

void WaitSeconds(uint64_t seconds);