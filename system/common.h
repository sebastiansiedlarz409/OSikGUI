#pragma once

#include <stdint.h>

typedef struct _SystemContext{
    uint8_t window;
} SystemContext;

#define UNUSED(x) (void)(x)
typedef unsigned long long size_t;

SystemContext* GetSystemContext(void);
int32_t isqrt(int32_t num);