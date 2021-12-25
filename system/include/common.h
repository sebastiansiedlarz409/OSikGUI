#pragma once

#include <stdint.h>

#include "windows.h"

#define UNUSED(x) (void)(x)
typedef unsigned long long size_t;

typedef struct _SystemContext{
    //general information
    uint64_t kernelAddress;
    uint64_t stackAddress;
    uint64_t heapSize;
    uint64_t heapAddress;
    uint64_t heapNextFree;
    //windows api
    uint8_t window;
    uint8_t windowsCount;
    WindowContext* mainWindow;
    WindowContext* currentWindow;
    uint32_t lastUsedWindowId;
    //streams api
    void(*PushInStream)(uint8_t);
    uint8_t(*PopInSteam)(void);
    uint16_t(*GetInStreamSize)(void);
} SystemContext;

SystemContext* GetSystemContext(void);
int32_t isqrt(int32_t num);

void WaitSeconds(uint64_t seconds);