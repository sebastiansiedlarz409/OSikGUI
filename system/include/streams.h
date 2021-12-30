#pragma once

#include <stdint.h>

typedef struct _Stream{
    uint16_t size;
    uint8_t buffer[100];
} Stream;

void PushInStream(uint8_t value);
uint8_t PopInStream(void);
uint16_t GetInStreamSize(void);
void FlushInStream(void);