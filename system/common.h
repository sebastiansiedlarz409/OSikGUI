#pragma once

#include <stdint.h>

#include "windows.h"

typedef struct _SystemContext{
    uint8_t window;
    WindowContext mainWindow;
} SystemContext;

#define UNUSED(x) (void)(x)
typedef unsigned long long size_t;

SystemContext* GetSystemContext(void);
int32_t isqrt(int32_t num);

void WaitSeconds(uint64_t seconds);